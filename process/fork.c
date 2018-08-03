#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>



int glob=6;

	/*
	   buf[]를 *buf로 바꾸니깐 a write 만 출력되었다. 

	   */

char *buf="a write to stdout\n";

int main(void)
{
	int var;
	pid_t pid;
	var = 88;

	/* stdout의 fd는 1이므로 1로 치환 가능
	 1에 buf의 내용을 쓰겠다.
	 이때 buf의 크기는 sizeof(buf) -1로 정하는데
	
	 Q. buf에 -1을 하는 이유는???  
	  
	  buf[] : -1을 해도 안 해도 똑같이 출력
	        : a write to stdout
			: befor fork
	  
	  *buf : buf -1  -> a writebefore fork 
	  	   : buf     -> a write before fork 
	 A.
	  
	 */
	

	if(write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
		perror("write error");
	
	// 
	printf("before fork\n");

	
	if((pid=fork() == 0))
	{
	// 자식은 부모로부터 가져온 변수의 값을 변경
		glob++;
		var++;
	} else 
	{
	// 부모는 처음 전역 영역에서 가져온 변수의 값은 변화 x
	sleep(2);
	}

	// 출력 한 방에 부모와 자식의 변수값이 각각 나왔다 
	// 부모와 자식 모두 wait이 없으니 그대로 같이 넘어감
	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
	
	// 이때 부모와 자식이 모두 동시에 exit되는 것인가? 
	// exit의 의미를 더 자세히 부모와 자식 proc의 상태를 그려보자
	exit(0);
}

