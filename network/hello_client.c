#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFSIZE 50

// ./hello_client [PORT] 

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int sock;  // fd
	
/*
 
struct sockaddr_in
{
	sa_family_t     sin_family		// 주소 체계
	uint16_t 	    sin_port		// port 번호
	struct in_addr  sin_addr		// 32비트 ip 주소
	char    	    sin_zero[8]		// 사용하지 않음
};

struct in_addr
{
 	in_addr_t 	    s_addr ; 		// 32비트 ipv4 인터넷 주소
};

                                                                                                                                                                                                        
struct sockaddr
{
	sa_family_t     sin_family;  	// 주소 체계
	cha		r       sa_data[14]; 	// 주소 정보
};


*/

	struct sockaddr_in serv_addr;
	char message[BUFSIZE];
	int str_len;

	if(argc!=3)
	{
		printf("Usage : %s [IP] [port]\n", argv[0]);
		exit(1);
	}

	
	// 1. socket()

/*
	socket() - 소켓 생성

	1. 사용법

		int socket(int domain, int type, int protocol);

			domain : protocol(address) famil [PF(AF)_UNIX, PF(AF)_INET ...etc)을 선택

			type : [SOCK_STREAM(TPC), SOCK_DGRAM(UDP) ...etc]
			
			protocol : domain과 type으로 protocol이 사실상 결정되므로 그냥 0을 전달해도 됨

	2. return

		성공 : fd

		실패 : -1 (errno)

	3. example

		serv_sock = socket(PF_INET, SOCK_STREAM, 0);

		domain은 IPv4 인터넷 프로토콜 체계로 type은 TPC로, protocol은 0을 인자로 전달하여 생성하는 소켓의 fd를 serv_sock에 할당한다. 
*/

	sock = socket(PF_INET, SOCK_STREAM, 0); //
	if(sock == -1)
		error_handling("socket() error");
	

	// 2. 주소(ip, port) 설정

/*
    inetaddr() - 
	
	1. 사용법
   
		in_addr_t inet_addr(const char *cp);

			*cp : ip주소를 담고 있는 포인터
			 
	2. return

		문자열 포인터에 담긴 문자열을 int형(16진수 형)으로 출력

	3. example

		char *addr1="127.212.124.78";
                      7f  4d  7c  4e
		inet_add(addr1);

		0x4e7c4d7f

		*addr가 가지고 있는 문자열 "x.x.x.x"을 little endian 의 형태로 출력. 이때 출력형은 16진수
*/
	
	memset(&serv_addr, 0, sizeof(serv_addr));       // serv_addr 즉 struct sockaddr_in을 모두  0으로 초기화
	serv_addr.sin_family = AF_INET;					// AF_INET - 
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);  // ip            host to network long
	serv_addr.sin_port = htons(atoi(argv[2]));      // port			 host to network short 


	// 3. connect() 
/*
   	connect() - *addr를 socket의 fd에 연결

	1. 사용법

		int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

			sockdf : 생성된 소켓의 file descriptor 

			*addr : struct sockaddr *addr의 주소값, 접속하기 위한 addr 설정

			addrlen : *addr의 크기

	2. return

		성공 : 0

		실패 : -1 (errno)

	3. example

		connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

		sock을 fd로 갖는 소켓에 구조체 포인터serv_addr를 (struct sockaddr*)으로 형변환하여 그 안에 담고 있는 주소값을 연결시켜준다. 이때 포인터serv_addr의 크기는 sizeof(serv_addr)와 같다.  	
*/	
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)  
		error_handling("connect() error");


	// 4. data transfer

/*
    read() - socket, open, pipe 등으로 열린(fd가 만들어진) 파일에서 데이터를 읽는다

    1. 사용법                                                                                        

        ssize_t read(int fd, void *buf, size_t count);

            fd : file descriptor(파일 서술자)

            *buf : fd에 읽을 데이터가 있다면 buf에 담아서 가져온다

            count : buf에서 한번에 가져올 데이터의 크기를 나타낸다

    2. return

        성공 : 0 이상의 값(0 = 파일의 끝, 0 < 읽어 들인 buf의 크기)

        실패 : -1(errno)

    3. example

        read(sock, message, sizeof(message));

        서버 입장 -

        sock의 fd에 접속해서(이때 fd는 accept를 통해서 serv_sock과 connect된 clnt_sock를 의미한다) client에서 내용을 출력한 *buf가 있다면 server에서 message라는 *buf로 읽어들인다. 이때 한번에 sizeof(message)의 크기씩 읽어들인다.

        client 입장 -

        sock의 fd에 접속해서(이때 fd는 connect를 통해서 주어진 clnt_sock를 의미한다) server에서 내용을 출력한 *buf가 있으면 client에서 message라는 *buf로 읽어들인다. 이때 한번에 sizeof(message)의 크기씩 읽어들인다.
*/

/*
    write() - socket, open, pipe 등으로 열린(fd가 만들어진) 파일에서 데이터를 쓴다.

    1. 사용법

        ssize_t write(int fd, void *buf, size_t cunt);                                           

            fd : file descriptor(파일 서술자)

            *buf : fd에 쓸 데이터

            count : *buf의 크기

    2. return

        성공 : 0 이상의 값(0 = 파일의 끝, 0 < 쓰여진 buf의 크기 바이트)

        실패 : -1(errno)

    3. example

        write(clnt_sock, message, sizeof(message));

        서버 입장 -
        
        sock의 fd에 접속해서(이때 fd는 accept를 통해서 serv_sock과 connect된 clnt_sock를 의미한다) client에 sizeof(message)만한 크기의 *buf인 message를 출력한다.

        client 입장 -

        sock의 fd에 접속해서(이때 fd는 connect를 통해서 주어진 clnt_sock를 의미한다) server에 sizeof(message)만한 크기의 *buf인 message를 출력한다.
*/   



	str_len = read(sock, message, sizeof(message)-1);
	if(str_len == -1)
		error_handling("read() error");

	printf("Message from server : %s\n", message);


	// 5. close
/*
	shutdown() -
*/

	close(sock);

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}


