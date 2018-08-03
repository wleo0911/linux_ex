#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "shm_com.h"

int main()
{
	int running = 1;
	void *shared_memory = (void *)0;     // 보이드형 포인터, null pointer
	struct shared_use_st *shared_stuff;  // 구조체를 바라보는 포인터
	int shmid;
	
	printf("%p, %p, %p", shared_memory, shared_memory, shared_memory); 

	srand((unsigned int)getpid());

/*	
	shmid
	주어진 인자 key를 접근 번호로 하는 공유 메모리 공간할당을 커널에 요청한다.
	즉, 물리 메모리에 공유 메몰ㅣ 주소 할당

		1. 사용법
			
			int shmget(key_t key, size_t size, int shmflg)

	 	2. return
	 		
			성공 : 공유된 메모리 식별자 = shmid 
			실패 : -1
*/	

	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	if (shmid == -1)
	{
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

/*
	shmat
	공유메모리 식별자(shmid)에 공유 메모리 세그먼트를 붙이기 위해 사용. 
	즉, 프로세스에 생성된 공유 메모리 연동

		1. 사용법
			
			void *shmat(int shmid, const void *shmaddr, int shmflg);
			
			int shmdt(const void *shmaddr);

		2. return

			성공 : shared memory segment
			실패 : -1
 
 */

	shared_memory = shmat(shmid, (void *)0, 0); // 특별한 주소를 얻기가 어렵다 따라서 null 값
	if (shared_memory == (void *)-1)
	{
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
	}

	printf("Memory attached at %p\n", (int*)shared_memory);

	shared_stuff = (struct shared_use_st *)shared_memory;
	shared_stuff->written_by_you = 0;

	while(running)
	{
		if(shared_stuff->written_by_you)
		{
			printf("You wrote : %s", shared_stuff->some_text);
			sleep(rand() % 4);
			shared_stuff->written_by_you = 0;
			if(strncmp(shared_stuff->some_text, "end", 3) == 0)
			{
				running = 0;	
			}

		}

	}

	if(shmdt(shared_memory) == -1)
	{
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}

	if(shmctl(shmid, IPC_RMID, 0) == -1)
	{
		fprintf(stderr, "shmctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	*/
	exit(EXIT_FAILURE);
}
