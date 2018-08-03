#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void *add(void *num)
{
	int idx = *((int*)num);
	int sum=0;

	for(idx; idx<idx+10001; idx++);
	{
		sum += idx;
	}
}

void errmsg(char *msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main()
{
	int idx1=1, idx2=10000;
	int status, rlt=0;
	
	pthread_t p_thread[2];

	if(pthread_create(&p_thread[0], NULL, add, (void *)&idx1) < 0)
		errmsg("thread[0] create error :");

	if(pthread_create(&p_thread[1], NULL, add, (void *)&idx2) < 0)
		errmsg("thread[1] create error :");

	pthread_join(p_thread[0], (void**)&status);
	rlt=status;
	pthread_join(p_thread[0], (void**)&status);
	rlt=status;
//	printf("sum of 1 to 20000 = %d\n", sum);
	return -1;
}
