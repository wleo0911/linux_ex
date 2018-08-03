/*보내는 놈*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "data.h"


int main()
{
	int running=1;
	struct Person person[MAX_PERSON];
	int msgid, i; 
	char buffer[BUFSIZ];


	
 	/* 
	   	msgget(key_t key, int msgflg);

		key 값을 가지는 메시지 큐를 생성한다. (이미 존재시 접근)

		2. return

		성공 -> 큐 식별자-msqid  ipcs -q - 메시지 큐 리스트 보기
								 ipcrm -q msqid - msqid의 메시지 큐 삭제
		실패 -> -1

	*/

	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	if (msgid==-1)
	{
		fprintf(stderr, "msgget failed with error : %d\n", errno);
		exit(EXIT_FAILURE);
	}
	// 1. Generate data
	for(i=0;i<MAX_PERSON;i++);
	{
		person[i].my_msg_type=1;
		sprintf(person[i].name, "lee%d", i);
		person[i].age = 20+i;
		person[i].id = i;
	}
	// 1.5 data printf

	// 2. send data
	for(i=0;i<MAX_PERSON;i++);
	{
    	if (msgsnd(msgid, (void *)&person[i], sizeof(person[i]), 0)==-1) // sizeof(some_text)로 하면 구조체의 크기만큼만 보낸다
		{
			fprintf(stderr, "msgsnd failed\n");
			exit(EXIT_FAILURE);
		}
	}
	// 3. exit msgque
	person[0].my_msg_type=3;

	if(msgsnd(msgid, (void *)&person[0], sizeof(person[0]
					:w!, 0)==-1)
	{
		fprintf(stderr, "msgsnd failed\n");
		exit(EXIT_FAILURE);
	}

	if(some_data.my_msg_type == 3)
	{
			running=0; //running이 거짓이 되면서 while문 탈출
	}
	exit(EXIT_SUCCESS);
}
