#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void pr_exit(int status);

int main(void)
{
	int status;
	pid_t pid;
	
	// 자신의 PID 값을 확인
	printf("Process ID = %d\n", getpid());

	// 부모의 PID 값을 확인
	printf("Parent Process ID = %d\n", getppid());
	
	pid = fork();

	// fork를 통해 자식 프로세스 생성 실패
	
	if(pid < 0)
	{
		printf("Error : fork()\n");
		return -1;
	} 
	// 자식일 경우 실행
	else if (pid==0)
	{
		printf("Child : Hello!!\n");
		return 0;
	} 
	// 부모일 경우 실행
	else
	{
		printf("Parent : Hi!!\n");
		printf("Child PID : %d\n", pid);
	}

/*
	// if문을  switch 문으로 변경 했을 경우  -- 아직 미완성
    switch(pid)
{
	case -1 :
		perror("fork faild");
		exit(1);
	case 0 :
	    message = "This is the child";
	    n=5;
		break;
	default :
		message = "This is the parent";
		n=3;
		break;
}
*/

	// wait은 자식의 pid를 반환한다  
	printf("EXIT : Child pid = %d\n", pid= wait(&status));
	pr_exit(status);

	return 0;
}


void pr_exit(int status)
{
	// 자식 프로세스가 정상적으로 종료 
	if (WIFEXITED(status))
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
	// 자식 프로세스가 시그널에 의해 종료
	else if (WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status), \
				WCOREDUMP(status) ? "(Core file generated" : "");
 	// 자식 프로세스가 시그널에 의해 잠시 정지
	else if (WIFSTOPPED(status))  
		printf("child stopped, signal number = %d\n", WSTOPSIG(status));
		   
}

