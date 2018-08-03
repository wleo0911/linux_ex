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
	struct sockaddr_in serv_addr, from_addr; 

	if(argc != 2)
	{
		printf("Usage : %s [PORT]\n", argv[0]);
		exit(1);
	}


	// 1. socket() - socket 생성(ipv4, upd)

	sock = socket(PF_INET, SOCK_DGRAM, 0);
	if(sock == -1)
		error_handling("socket() error");


	// 2. 주소(ip, port) 생성

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY 주소는 아무렇게나
	serv_addr.sin_port = htons(atoi(argv[1]));		  // "5000" -> 5000 -> 0x......

	// 3. bind() - 1.에 2.할당

	if(bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");

	// 4. data trnasfer

/*
	send(), sendto() - write와 유사한 기능이지만 flags 활용이 가능 
					   send는 TCP만, sendto는 TCP, UDP 둘 다 사용 가능

	1. 사용법

		ssize_t send(int sockfd, const void *buf, size_t len, int flags);
		ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, sockle_t addrlen)
		
			sockfd : fd
			*buf : 전송하고자 하는 내용
			len : *buf의 크기
			flags : send, recv의 사용 의미
			
				MSG_CONFIRM :

				MSG_DONTROUTE :

			 	MSG_DONTWAIT :

				MSG_EOR :

				MSG_MORE :

				MSG_NOSIGNAL :

				MSG_OOB :

			dest_addr : UDP의 경우 주소 연결이 안 되어 있기 때문에 여기서 주소를 알려줘야 함
			addrlen : dest_addr의 크기

	2. return 

		성공 : 보낸 데이터의 바이트 수 만큼

		실패 : -1(errno)

	3. example

		sendto(sock, message, strlen(message), 0, (struct sockaddr*)&from_addr, addr_sz);

		strlen(message)의 크기의 message를 가진 sock fd를 보낸다. from_addr 주소로. 
*/

/*
    recv(), recvfrom() - read와 비슷한 기능이지만 flags 활용 가능
                       recv는 TCP만 recvfrom는 TCP, UDP 둘 다 사용 가능

    1. 사용법

        ssize_t send(int sockfd, const void *buf, size_t len, int flags);
        ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *  src_addr, sockle_t addrlen)
        
            sockfd : fd
            *buf : 전송하고자 하는 내용
            len : *buf의 크기
            flags : option

                MSG_CMSG_CLOEXEC :

                MSG_DONTWAIT :

                MSG_ERRQUEUE :

                MSG_WAITALL :

                MSG_TRUNC :

                MSG_PEEK :

                MSG_OOB :
            
            dest_addr : UDP의 경우 주소 연결이 안 되어 있기 때문에 여기서 주소를 알려줘야 함
            addrlen : dest_addr의 크기

    2. return

        성공 : 

        실패 : -1(errno)

    3. example

        recvfrom(sock, message, strlen(message), 0, (struct sockaddr*)&from_addr, addr_sz);
        strlen(message)의 크기의 message를 가진 sock fd에 받는다. from_addr 주소로부터.                  
*/

	while(1)
	{
		addr_sz = sizeof(from_addr);
		str_len = recvfrom(sock, message, sizeof(message), 0, (struct sockaddr*)&from_addr, &addr_sz);
		
		sendto(sock, message, strlen(message), 0, (struct sockaddr*)&from_addr, addr_sz);  //strlen -> 지금 들어있는 문자열의 크기(null까지)  sizeof -> 전체 크기
		
	}
	close(sock);
	return 0;
}
