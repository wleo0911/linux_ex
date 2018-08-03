#include <stdlib.h>
#include <stdio.h>

int main()
{
	printf("Running ps whih system\n");
	system("ps -ax");  // system의 ps -ax가 다 끝난 후에 알아서 system 종료 
	printf("Done.\n"); // system()이 끝난 후에 done 출력

	exit(0);
	// exit()는 프로그램을 정상 종료 시킨다. 이때 종료 값으로 status를 부모 프로세스의 status &0377로 넘겨준다.

}

