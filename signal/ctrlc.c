#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
	/*

	handler 주소값 호출을 통하여 들어온다 이때 매개변수-parameter(int sig)로 받는 것이 SIGINT이다. 
	parameter는 variable로 보기 때문에 항상 data type을 지정해주어야 한다.

	대부분의 parameter는 call by value의 형태로 동작하게 되는데 
	이 경우에는 parameter-매개변수의 값이 변하더라고 argument-인자의 값은 변하지 않는다.

	call by reference의 경우에는 argument도 변한다. 

	*/

void sigHandler(int sig)
{
	static int count=0;
	switch (sig)
	{
	case 2:
		if (count==5){
			signal(SIGINT, SIG_DFL);
			exit(0);
		} else {
			printf("OUCH - I got signal %d and count = %d \n", sig, count+1);
			count++;
		}
		break;
	case 3:
		if (count==5){
			signal(SIGQUIT, SIG_DFL);
			exit(0);
		} else {
			printf("OUCH - I got signal %d and count = %d \n", sig, count+1);
			count++;
		 }
		break;
	default :
		break;
	}
}



int main()
{
	/*
                         arugment1 - 전달인자 
	sighandler_t signal(int signum, sighandler_t handler);

	signum를 입력 받았을 때 handler라는 주소값을 호출한다.

	전달인자는 value-값으로로 보기 때문에 data-type을 알려줄 필요가 없다.
	*/
	
	signal(SIGINT, sigHandler);	
	signal(SIGQUIT, sigHandler);

	while(1) {
		printf("Hello World!\n");
		sleep(1);
	}
	
}

