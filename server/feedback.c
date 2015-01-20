#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

#define TCPSERVER_PORT 4548

#define DATAGRAM_MAXLENGTH 32


int main(int argc, char ** argv)
{
	int sock;
	const short IP_ARGUMENT=1;
	const short ACT_ARGUMENT=2;
	const short KEY_ARGUMENT=3;
	const short VALUE_ARGUMENT=4;
	const char *set="set";
	const char *get="get";
	char msg[DATAGRAM_MAXLENGTH];
	char buf[sizeof(msg)];
	struct sockaddr_in addr;
	// printf(argv[ACT_ARGUMENT]);
	
	if(!strcasecmp(argv[ACT_ARGUMENT],set)) // отправка данных на сервер
	{
		//strcpy(buf, str);
		// передаваемая строка должна иметь вид "key=value"
		strcpy(msg, argv[KEY_ARGUMENT]); // сначала загоняю key
		
		strcat(msg,"=");
		strcat(msg, argv[VALUE_ARGUMENT]);
		strcat(msg,"\n");

		//printf("%s",msg);
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if(sock < 0)
		{
			perror("socket");
			exit(1);
		}

		addr.sin_family = AF_INET;
		addr.sin_port = htons(TCPSERVER_PORT );
		addr.sin_addr.s_addr = inet_addr(argv[IP_ARGUMENT]); // в качестве первого аргумента в программу передаётся ип адрес сервер
		if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
		{
			perror("connect");
			exit(2);
		}
		//sleep(1);
		//sendto(sock, msg, DATAGRAM_MAXLENGTH, 0, (struct sockaddr *)&addr, sizeof(addr));
		send(sock, msg, sizeof(msg), 0);
		
		//recv(sock, buf, sizeof(msg), 0);
		
		
		printf("I sent: %s",msg);
		//printf("Server said: %s", buf);
		close(sock);
	}
	else if (!strcasecmp(argv[ACT_ARGUMENT],get)){
		printf("Coming soon...");
	
	}
	return 0;
}
