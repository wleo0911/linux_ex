#include <stdio.h>                                                          
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#define BUFSIZE 30

#define DEBUG

/* 프로세스 생성, IPC(pipe), SIGNAL */

int idx, sum=0;
int fd[2];


void errmsg(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);           
}

void sigHandler(int sig)
{
	close(fd[1]);
	read(fd[0], &sum, sizeof(sum));
	printf("sum of 1 to 10000 =  %d\n", sum);
}


int main()
{
	int status; 
	pid_t pid;  		// process 관련
	
	// 1. pipe()
	if(pipe(fd) == -1) // fd[0] 읽기 전용 , fd[1] 쓰기 전용
		errmsg("pipe error");

	// 2. fork() 
	switch(fork())
	{
		case -1: // fork()실패 시 -1 리턴
			errmsg("fork error");
			break;
		
		case 0: // 성공 시 자식은 0 리턴
			close(fd[0]); // 자식은 보내기용 
			for(idx=0; idx<10001; idx++)
			{
				sum += idx;
			}
			write(fd[1], &sum, sizeof(sum)); // pipe로 보내기
			exit(status); // 자식 프로세스 종료 - 프로세스가 사용한 자원 재할당, status값 리턴
			break;

		default: // 성공 시 부모는 자식의 pid 리턴 --- 부모 영역
			close(fd[1]); // 부모는 받기용
			signal(SIGCHLD, sigHandler);// status 리턴 == SIGCHLD
			pause();
			//wait(&status); // 자식이 진행중이면 부모 대기, 종료되었다면(status 리턴o) 부모 재개 
			read(fd[0], &sum, sizeof(sum)); // pipe 받기
			for(idx=10001; idx<20001; idx++) // 부모에서 계산
			{
				sum += idx;
			}
			printf("sum of 1 to 20000 = %d\n", sum);
			break;
	}
	return 0;
}


