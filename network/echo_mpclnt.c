#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFSIZE 30

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc, char *argv[])
{
	int sock;  // fd
 	int str_len;
	struct sockaddr_in serv_addr;

	char message[BUFSIZE];

	if(argc!=3)
	{
		printf("Usage : %s [IP] [port]\n", argv[0]);
		exit(1);
	}

	// 1. socket()	

	if((sock = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		error_handling("socket() error");
	
	// 2. addr(ip, port) 

	memset(&serv_addr, 0, sizeof(serv_addr));       
	serv_addr.sin_family = AF_INET;				 
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]); 
	serv_addr.sin_port = htons(atoi(argv[2]));      


	// 3. connect() 
	
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)  
		error_handling("connect() error");
	else
		printf("connected ...\n");

	while(1)
	{
		printf("Input message(Q to quit);");
		fgets(message, sizeof(message), stdin);

		if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;

		write(sock, message, sizeof(message));
		if((str_len = read(sock, message, sizeof(message)-1)) == -1);
			error_handling("read() error");

		printf("Message form server : %s\n", message);
	}

	// 5. close

	close(sock);
	return 0;
}
