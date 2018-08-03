#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int s, sig;
	int cnt;

	//사용법을 틀렸을 경우 대비

	if (argc !=3 || strcmp(argv[1], "--help") == 0)
		printf("%s pid sig-num\n", argv[0]);
	
	// sig를 알아야 kill()의 argument 값을 지정할 수 있으므로 argv[2]를 먼저 실행

	sig = atoi(argv[2]);
	
	printf("argv[1] = %d\n", sig);
		   
	/*
		1. 사용법 

		#include <sys/types.h>
		#incldue <signal.h>

		int kill(pid_t pid, int sig);

		2. ruturn

		성공 0
		실패 -1
	*/
		
		s = kill(atoi(argv[1]), sig); // 일단 kill을 한번 보내서 s값 받기 

	if(sig != 0) // 
	{
		if(s == -1)
			printf("Error : system call kill()\n");
		else if(s == 0)
		{ 
			for (cnt=0;cnt<5;cnt++)
			{
				s = kill(atoi(argv[1]), sig);
				printf("Process exitst and we can sent it a signal\n");
	   	  	    sleep(1); // ##include <unistd.h>
			}
		}
		      
	} else
			   // break : 반복문을 벗어난다.
			   // continue : 이후 문장을 실행하지 않고 루프의 조건 체크 부분으로 옮긴다. 
	
	return 0;
}

