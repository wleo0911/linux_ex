#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigHandler(int sig)
{
	static int cnt=0;
	if (cnt==4)
		signal(SIGINT, SIG_DFL);
	printf("killTest : I got signal %d\n", sig);
	cnt++;
}

int main(void)
{
	signal(SIGINT, sigHandler);
	while(1)
	{
		printf("Hello, Hell\n");
		sleep(1);
	}
}

