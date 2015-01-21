#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

#define TCPSERVER_PORT 28001

#define DATAGRAM_MAXLENGTH 32
#define DATA_DIR "./control/"
#define SOURCE_DIR "./navigation/"


void sendPitch();
void sendRoll();
void sendYaw();
void sendThrust();
int sock;
FILE *file;
int msleep(int msec);

int main(int argc, char ** argv)
{
	
	const char *set="set";
	const char *get="get";
	int feedback_port=0;
	char feedback_ip[16]="192.168.240.1";
	
	char msg[DATAGRAM_MAXLENGTH];
	char buf[sizeof(msg)];
	struct sockaddr_in addr;
	// printf(argv[ACT_ARGUMENT]);
	
	// Сначала узнаю, на каком порту мне следует работать
	char filename[DATAGRAM_MAXLENGTH]="";
	//char port_string[6]="";
	strcat(filename,DATA_DIR);
	strcat(filename,"port");
	if((file = fopen(filename, "r"))==NULL) {
		perror("Cannot open file.");
		exit (1);
	}
	fscanf(file, "%d", &feedback_port);
	feedback_port++; // Порт обратной связи на единичку больше
	fclose(file);
	//printf("PORT: %d \n", feedback_port);
	
	
	//Теперь узнаю адрес, куда отправлять данные
	char ip_filename[DATAGRAM_MAXLENGTH]="";
	//char port_string[6]="";
	strcat(ip_filename,DATA_DIR);
	strcat(ip_filename,"client_ip");
	if((file = fopen(ip_filename, "r"))==NULL) {
		perror("Cannot open file.");
		exit (1);
	}
	fscanf(file, "%s", &feedback_ip);
	fclose(file);
	
	//printf("What now in &feedback_ip %%s:%s \n", &feedback_ip);

	
	printf("I'm sending to: %s:%d ....\n", &feedback_ip, feedback_port);
	//return 0;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(feedback_port );
	addr.sin_addr.s_addr = inet_addr(feedback_ip); // в качестве первого аргумента в программу передаётся ип адрес сервер
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("connect");
		exit(2);
	}
	// отправка данных на сервер
	while(1)
	{
		
		sendYaw();
		sendPitch();
		sendRoll();
		msleep(100);
		//printf("I sent: %s",msg);
		//printf("Server said: %s", buf);
	}
	close(sock);
	return 0;
}

void sendPitch() {
	float pitch=0.0;
	int int_pitch=0;
	char str_pitch[7]="000000";
	char filename[DATAGRAM_MAXLENGTH]="";
	//char port_string[6]="";
	strcat(filename,SOURCE_DIR);
	strcat(filename,"pitch");
	if((file = fopen(filename, "r"))==NULL) {
		perror("Cannot open file.");
		exit (1);
	}
	fscanf(file, "%f", &pitch);
	
	fclose(file);
	//printf("%f", pitch);
	int_pitch = (int) (pitch*1000);
	sprintf(str_pitch,"%d", int_pitch);

	char msg[DATAGRAM_MAXLENGTH];
	strcpy(msg, "pitch"); // сначала загоняю key
	strcat(msg,"=");
	strcat(msg, str_pitch);
	send(sock, msg, sizeof(msg), 0);
	msleep(2);
	return;
}
void sendRoll() {
	float roll=0.0;
	int int_roll=0;
	char str_roll[7]="000000";
	char filename[DATAGRAM_MAXLENGTH]="";
	//char port_string[6]="";
	strcat(filename,SOURCE_DIR);
	strcat(filename,"roll");
	if((file = fopen(filename, "r"))==NULL) {
		perror("Cannot open file.");
		exit (1);
	}
	fscanf(file, "%f", &roll);
	
	fclose(file);
	//printf("%f", roll);
	int_roll = (int) (roll*1000);
	sprintf(str_roll,"%d", int_roll);


	char msg[DATAGRAM_MAXLENGTH];
	strcpy(msg, "roll"); // сначала загоняю key
	strcat(msg,"=");
	strcat(msg, str_roll);
	send(sock, msg, sizeof(msg), 0);
	msleep(2);
	return;
}
void sendYaw() {

	float yaw=0.0;
	int int_yaw=0;
	char str_yaw[8]="0000000";
	char filename[DATAGRAM_MAXLENGTH]="";
	//char port_string[6]="";
	strcat(filename,SOURCE_DIR);
	strcat(filename,"yaw");
	if((file = fopen(filename, "r"))==NULL) {
		perror("Cannot open file.");
		exit (1);
	}
	fscanf(file, "%f", &yaw);
	
	fclose(file);
	//printf("%f", yaw);
	int_yaw = (int) (yaw*1000);
	sprintf(str_yaw,"%d", int_yaw);
	char msg[DATAGRAM_MAXLENGTH];
	strcpy(msg, "yaw"); // сначала загоняю key
	strcat(msg,"=");
	strcat(msg, str_yaw);
	send(sock, msg, sizeof(msg), 0);
	msleep(2);
	//printf("I sent: %s",msg);
	return;
}
void sendThrust() {
	char msg[DATAGRAM_MAXLENGTH];
	strcpy(msg, "throttle"); // сначала загоняю key
	strcat(msg,"=");
	strcat(msg, "128");
	send(sock, msg, sizeof(msg), 0);
	return;
}
int msleep(int msec){
	return usleep(1000*msec);
}

