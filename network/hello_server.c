#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define TRUE 1
#define FALSE 0

// ./hello_server [PORT] 

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock;  // 서버 socket의 fd
	int clnt_sock;	// 서버에 들어올 client socket의 fd
	int option;
	socklen_t clnt_addr_size;
	socklen_t optlen;
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
	struct sockaddr_in clnt_addr;
				
	char message[]="Hello world!";
	char *ipaddr; 

	if(argc!=2)
	{
		printf("Usage : %s [port]\n", argv[0]);
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

	serv_sock = socket(PF_INET, SOCK_STREAM, 0); 
	if(serv_sock == -1)
		error_handling("socket() error");
	

	// 2. 주소(ip, port) 설정

/*
    memset() - 구조체의 메모리 채우기
	
    1. 사용법
   
		void *memset(void *s, int c, size_t n);

			*s : *s가 가르키는 메모리 영역의 처음 n 바이트를

			c :  상수 c로 채운다

			n : 

	2. return

		메모리 영역 s에 대한 포인터를 반환

	3. example

		memset(&serv_addr, 0, sizeof(serv_addr));

		*serv_addr가 가지고 있는 주소값의 메모리 영역의 sizeof(serv_addr) 바이트를 상수 0 으로 채운다
*/
	
	memset(&serv_addr, 0, sizeof(serv_addr));       // serv_addr 즉 struct sockaddr_in을 모두  0으로 초기화
	serv_addr.sin_family = AF_INET;					// AF_INET - 
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // ip            host to network long (INADDR_ANY - )
	serv_addr.sin_port = htons(atoi(argv[1]));      // port			 host to network short 


	// 3. bind() 

/*
	bind() - 소켓에 주소(ip, port) 할당

	1. 사용법

		int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

			sockdf : 생성된 소켓의 file descriptor 

			*addr : h에 포함된 struct sockaddr 형을 가지는 *의 주소값 이 주소로 들어오는 데이터는 나에게 다 보내거라.

			addrlen : *addr의 크기

	2. return

		성공 : 0

		실패 : -1 (errno)

	3. example

		bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

		serv_sock을 fd로 갖는 소켓에 구조체 포인터serv_addr를 (struct sockaddr*)으로 형변환하여 그 안에 담고 있는 주소값을 넣어준다. 이때 포인터serv_addr의 크기는 sizeof(serv_addr)와 같다.  	
*/	
	optlen = sizeof(option);
	option = TRUE;
	setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, optlen);


	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)  // 형 변환 필요 (struct sockaddr*)
		error_handling("blid() error");

	// 4. listen()

/*
	listen() - accept()를 통하여 들어오는 연결 요청을 수락하기 위한 소켓 설정

	1. 사용법

		int listen(int sockfd, int backlog);

			sockfd : 생성된 소켓의 fd

			backlof : 접속할 수 있는 client fd를 담을 큐의 최대 크기를 지정

	2. return

		성공 : 0

		실패 : -1 (errno)

	3. example

		listen(serv_sock, 5);

		serv_sock을 fd로 갖는 소켓의 backlog를 5로 지정
*/

	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	clnt_addr_size = sizeof(clnt_addr);



	// 5. accept()

/*
	accept() - client socket의 connection()을 받아들인다 

	1. 사용법

		int accept(int s, struct sockaddr *addr, socklen_t *addrlen);

			s : server soketd fd

			*addr : client socket의 addr

			*addrlen : client socket의 addr size

	2. return

		성공 : 받아들인 소켓을 위한 파일 지정번호(0보다 큼)

		실패 : -1

	3. example

		accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

		listen 해 놓았던 server socket의 fd를 넣어주고 client의 주소와 주소 사이즈를 받아온다
		이때 새로운 socket 즉 연동된 socket이 생기면 그 소켓의 fd를 반환한다.
*/



	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
	if(clnt_sock == -1)
		error_handling("accept() error");

	// 6. data transfer

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
        
        sock의 fd에 접속해서(이때 fd는 accept를 통해서 serv_sock과 connect된 clnt_sock를 의미한다)   client에 sizeof(message)만한 크기의 *buf인 message를 출력한다.

        client 입장 -

        sock의 fd에 접속해서(이때 fd는 connect를 통해서 주어진 clnt_sock를 의미한다) server에        sizeof(message)만한 크기의 *buf인 message를 출력한다.
*/   


	write(clnt_sock, message, sizeof(message)); // accept()를 통해 받은 client addr를 담은 socket의 fd

/*
   inet_ntoa() - 정렬된 ip주소정보를 문자열의 형태로 변환

   1. 사용법

   2. return

   3. example
*/
	
	shutdown(clnt_sock, SHUT_WR);
	
	ipaddr = inet_ntoa(clnt_addr.sin_addr);
	printf("client ip addr : %s\n", ipaddr);

	while(read(clnt_sock, message, sizeof(message)) != 0)
	shutdown(clnt_sock, SHUT_RD);

	//close(clnt_sock);

	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}


