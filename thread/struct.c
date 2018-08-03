/*
   컴파일 과정 새로운 option을 추가

	gcc -o pthread_basic pthread_basic.c -lpthread
	gcc -pthread -o pthread_basic pthread_basic.c 
	
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define DEBUG

struct NUM
{
	int start;
	int end;
};


void *t_function(void *num)
{
	int id=0;
	int idx;
	int sum=0;
	struct NUM *f_num=(void *)num;

	 //쓰레드 id를 나타내는 data type : pthread_t

	for(idx=f_num->start;idx<f_num->end;idx++);
	{
		sum+=idx;
	}
	
	printf("start = %d, end = %d, sum = %d\n", f_num->start, f_num->end, sum);

	sleep(2);

	return (void*)(id*id);
}

int main()
{
	pthread_t p_thread[2]; 
	struct NUM *num1;
	struct NUM *num2;
	int err;
	int status;

	num1 = (struct NUM *)malloc(sizeof(struct NUM)*5);
	num2 = (struct NUM *)malloc(sizeof(struct NUM)*5);

	num1->start=1;
	num1->end=10000;
	
	num2->start=10000;
	num2->end=20000;


	printf("start = %d, end = %d\n", num1->start, num1->end);

/*
	pThread_create() 쓰레드를 생성

	1. 사용법
		
		int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
		
		
 		*thread - 쓰레드 id를 저장할 포인터

		*arrt - 쓰레드의 attribute 설정
			보통 NULL을 사용하여 default attribute를 가지는 쓰레드를 생성한다
		
 		*start_routine - start_rtn 함수 
			새로 생성된 쓰레드가 실행할 함수
		*arg - start_rtn에 전달할 argument

	2. return 

		성공 : 0

		실패 : 에러코드 값
*/

	if((err = pthread_create(&p_thread[0], NULL, t_function, (void*)num1)) < 0)
	{
		perror("thread create error :");
		exit(1);
	}


	if((err = pthread_create(&p_thread[1], NULL, t_function, (void*)num2)) < 0)
	{
		perror("thread create error :");
		exit(2);
	}

/*
	pthread_join() 쓰레드가 종료되는 걸 기다림

	1. 사용법
		
		int pthread_join(pthread_t th, void **thread_return);


		th - 종료하려는 쓰레드 id

		thread_return - start_rtn 함수의 리턴값
			th로 들어가니 * , th에서 start_rtn()로 들어가니 **
	
	2. return

		성공 : 0

		실패 : 에러코드 값
*/


	pthread_join(p_thread[0], (void **)&status);
	printf("thread join : %d\n", status);
	pthread_join(p_thread[1], (void **)&status);
	printf("thread join : %d\n", status);


	return 0;
}	
