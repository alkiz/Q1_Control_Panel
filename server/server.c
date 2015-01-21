#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>	/* read(), write(), close() */
#include <fcntl.h>	/* open(), O_RDONLY */
#include <sys/stat.h>	/* S_IRUSR */



#define TCPSERVER_PORT 27000
#define DATAGRAM_MAXLENGTH 1024
#define DATA_DIR "./control/"



// мои пользовательские функции
short isSet(const char *str);
short findEndOfString(const char *str);
void substring(char *subline, const char *str, short begin, short count);
int msleep(int msec);
void writeMyPort(int port);
void writeClientIp(char * ip);

int main (int argc, char ** argv){
	// инициализация необходимых для работы сокетов
	
	char key[DATAGRAM_MAXLENGTH]="";
	char value[DATAGRAM_MAXLENGTH]="";
	char buf[DATAGRAM_MAXLENGTH];
	char eq_position,end_position;
	char str_length=0;
	int tcpserver_port=27000;
	int bytes_read;
	
	// получаю номер порта по которому будет происходить связь
	const char PORT_ARGUMENT=1;
	tcpserver_port = atoi(argv[PORT_ARGUMENT]);
	writeMyPort(tcpserver_port);
	
	// инициализация TCP сокета===========================================
	int tcpsock,new_sock;
	struct sockaddr_in tcpaddr,peer;
	int ready_to_recieve;
	
	tcpsock =socket(AF_INET, SOCK_STREAM, 0); // создаём TCP-сокет
	//fcntl(tcpsock, F_SETFL, O_NONBLOCK);
	if(tcpsock < 0) // если сокет не смог создаться, возвращается -1
	{
		perror("cannot create tcpsocket");
		exit(1);
	}
	
	
	tcpaddr.sin_family = AF_INET; // тип сокета
	tcpaddr.sin_port = htons(tcpserver_port); // указываю порт
	tcpaddr.sin_addr.s_addr = htonl(INADDR_ANY); //  с каких адресов принимать соединение [с любых адресов]
	
	if(bind(tcpsock, (struct sockaddr *)&tcpaddr, sizeof(tcpaddr)) < 0) // если сокет на забиндился - вывожу ошибку и вырубаю сервер.
	{
		perror("cannot bind tcpsocket");
		exit(2);
	}
	
	//printf("UDP-socket initialized");
	ready_to_recieve=listen(tcpsock, 1); // говорю tcp-сокету слушать порт
	// конец инициализации TCP-сокета=====================================
	
	
	while(1)
	{
		
		//================================TCP - Часть=========================================
		if(ready_to_recieve==0){
			int size = sizeof(peer);
			new_sock = accept(tcpsock, (struct sockaddr*)&peer, (socklen_t*)&size);
			if(new_sock < 0)
			{
				perror("accept");
				exit(3);
			}
			//printf("ADDRES: %s \n", inet_ntoa(peer.sin_addr));
			writeClientIp(inet_ntoa(peer.sin_addr));
			system("./feedback");
			while(1)
			{
				bytes_read = recv(new_sock, buf, DATAGRAM_MAXLENGTH, 0);
				//printf("%d", bytes_read);
				if(bytes_read <= 0) break;
				
				// buf - то что пришло с клиента
				char filename[DATAGRAM_MAXLENGTH]="";
				char output[DATAGRAM_MAXLENGTH];
				
				eq_position=isSet(buf);
				end_position = findEndOfString(buf);
				str_length=end_position-eq_position;
				strncpy(key,buf,eq_position);
				substring(value, buf,eq_position+1, str_length);
				key[eq_position]='\0';
				value[str_length]='\0';
				printf("KEY: '%s' - VALUE: '%s'; BYTES_READ: %d\n", key, value, bytes_read);
				
				strcat(filename,DATA_DIR);
				strcat(filename,key);
				FILE *file;
				if((file = fopen(filename, "w"))==NULL) {
					perror("Cannot open file.");
					exit (1);
				}
				fwrite(value, strlen(value), 1, file);
				fclose(file);
				
				//send(new_sock, buf, bytes_read, 0);
			}

			close(new_sock);
		}
		//================================TCP - Часть=========================================		
	}
	
	return 0;

}

short isSet(const char *str) { // функция смотрит на строку и ищет в ней знак РАВНО. если найдёт - возвращает номер символа равно, иначе - 0
	const short str_length=strlen(str);
	short i=0;
	for(i; i<str_length; i++){
		if(str[i]=='=') return i; // да, действительна строка задающая
	}
	return 0; // строка запрашивающая
}
short findEndOfString(const char *str){// функция смотрит на строку и ищет в ней знак \n. если найдёт - возвращает номер символа перевода строки, иначе - 0
	const short str_length=strlen(str);
	short i=0;
	for(i; i<str_length; i++){
		if(str[i]=='\n') return i-1;
	}
	return 0; // строка запрашивающая
}


void substring(char *subline,const char *str, short begin, short count){
	short i=0;
	for(i; i<count; i++){
		subline[i]=str[begin+i];
	}
	return;
}

int msleep(int msec)
//msec-задержка в милисекунда
{
	return usleep(1000*msec);
}
void writeMyPort(int port){
	char filename[DATAGRAM_MAXLENGTH]="";
	//char port_string[6]="";
	strcat(filename,DATA_DIR);
	strcat(filename,"port");
	FILE *file;
	if((file = fopen(filename, "w"))==NULL) {
		perror("Cannot open file.");
		exit (1);
	}
	fprintf(file,"%d", port);
	printf("\n%d\n", port);
	fclose(file);
	//fwrite(port_string, strlen(port_string), 1, file);

}
void writeClientIp(char * ip){
	char filename[DATAGRAM_MAXLENGTH]="";
	//char port_string[6]="";
	strcat(filename,DATA_DIR);
	strcat(filename,"client_ip");
	FILE *file;
	if((file = fopen(filename, "w"))==NULL) {
		perror("Cannot open file.");
		exit (1);
	}
	fprintf(file,"%s", ip);
	printf("\n%s\n", ip);
	fclose(file);
	//fwrite(port_string, strlen(port_string), 1, file);

}

