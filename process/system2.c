#include <stdlib.h>
#include <stdio.h>

int main()
{
	printf("Running ps whih system\n");
	system("ps -ax &"); // "&"를 추가하면  ps -ax 실행 후 system이 끝나기 전에
	printf("Done.\n");  // 여기도 바로 실행
						
	exit(0);
}

