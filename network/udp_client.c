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
	int sock;
	char message[BUFSIZE];
	int str_len;
	socklen_t addr_sz;
	struct sockaddr_in to_addr, from_addr; 

	if(argc != 3)
	{
		printf("Usage : %s [IP] [PORT]\n", argv[0]);
		exit(1);
	}


	// 1. socket() - socket 생성(ipv4, upd)

	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock == -1)
		error_handling("socket() error");


	// 2. 주소(ip, port) 생성

	memset(&to_addr, 0, sizeof(to_addr));
	to_addr.sin_family = AF_INET;
	to_addr.sin_addr.s_addr = inet_addr(argv[1]); // "192.168.1.32" -> 0x......
	to_addr.sin_port = htons(atoi(argv[2]));		  // "5000" -> 5000 -> 0x......

	// 3. data trnasfer

	while(1)
	{
		printf("Insert message(q to quit):");

		fgets(message, sizeof(message), stdin);
		if(!strcmp(message, "q\n")||(!strcmp(message, "Q\n")))
			break;
		
		sendto(sock, message, strlen(message), 0, (struct sockaddr*)&to_addr, sizeof(to_addr));  //strlen -> 지금 들어있는 문자열의 크기(null까지)  sizeof -> 전체 크기
		
		addr_sz = sizeof(from_addr);
		
		str_len = recvfrom(sock, message, sizeof(message), 0, (struct sockaddr*)&from_addr, &addr_sz);

		message[str_len] = 0;
		printf("Message from : %s", message);
	}
	close(sock);
	return 0;
}
