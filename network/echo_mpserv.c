#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFSIZE 30
#define TRUE 1
#define FALSE 0

void error_handling(char *message)
{
	fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


void read_childproc(int sig)
{
	pid_t pid;
	int status;
	pid = waitpid(-1, &status, WNOHANG);
	printf("removed PID : %d\n", pid);
}


int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t adr_sz;

	int option, str_len;
	socklen_t optlen;
	
	struct sigaction act;
	pid_t pid;
	
	int state;
	
	char buf[BUFSIZE];

	if(argc != 2){
		printf("Usage : %s [PORT]\n", argv[0]);
		exit(1);
	}

	// signal handler 

	act.sa_handler = read_childproc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	state = sigaction(SIGCHLD, &act, 0);

	// 1. socket()

	if((serv_sock = socket(PF_INET, SOCK_STREAM, 0)) == -1 )
		error_handling("socket() error");
	

	// 2. addr(ip, port)

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	// 3. bind()
	/*
	optlen = sizeof(option);
	option = TRUE;
	setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, optlen);     
    */
	/*
	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");
*/
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
		        error_handling("bind() error");  


	// 4. listen

	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	// 5. accept()
	
	while(1)
	{
		adr_sz = sizeof(clnt_addr);
		if(clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &adr_sz) == -1)
			continue;
		else
			printf("new client connected ...\n");
		
		// 6. fork()

		if((pid = fork()) == -1)
		{
			close(clnt_sock);
			continue;
		}  
		// 자식 생성 : serv_sock는 부모의 역할이니 자식은 필요 없음
		else if(pid == 0)
		{
			close(serv_sock);
			while((str_len = read(clnt_sock, buf, sizeof(buf))) != 0); // EOF를 받으면 탈출
				write(clnt_sock, buf, str_len);
			close(clnt_sock); // shutdown(clnt_sock, SHUT_WR);
			printf("client disconnected ... \n");
			return 0;
		}
		// 부모 생성 : 자식이 clnt_sock를 가져갔으니 부모는 더이상 필요 없음
		else
		{
			close(clnt_sock);
		}
	}
	close(serv_sock);
	return 0;
}



