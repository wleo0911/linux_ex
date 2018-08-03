/*보내는 놈*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 512

struct my_msg_st // 보내고 받을 때의 단위는 구조체 
{
	long int my_msg_type; 		// 무조건 선언해야 하는 것
	char some_text[MAX_TEXT];	/* 보내고자 하는 데이터, 구조체의 크기는 선언한 배열의 크기
	                             [512] -> 512bytes */
};

struct person // 새롭게 만들 구조체  총 20 + 1 + 4 byte
{
	long int my_msg_type; // 필수
	char name[20];  // 20byte
	unsigned char age; /* 숫자를 다루기 위해 char type을 사용할 경우 signed char : -127~127
						  unsigned char : 0 ~255,       1byte*/
	int id; //4byte 
};

int main()
{
	int running=1;
	struct my_msg_st some_data;	
	int msgid; 
	char buffer[BUFSIZ];

	struct person person[5];

	
 	/* 
	   	msgget(key_t key, int msgflg);

		key 값을 가지는 메시지 큐를 생성한다. (이미 존재시 접근)

		2. return

		성공 -> 큐 식별자
		실패 -> -1

	*/

	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	if (msgid==-1)
	{
		fprintf(stderr, "msgget failed with error : %d\n", errno);
		exit(EXIT_FAILURE);
	}

	while(running)
	{
		printf("Enter some text :");
		printf("큐 식별자는 %d\n", msgid);
		fgets(buffer, BUFSIZ, stdin);
		some_data.my_msg_type=1;
		strcpy(some_data.some_text, buffer);

    	if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0)==-1) // sizeof(some_text)로 하면 구조체의 크기만큼만 보낸다
		{
			fprintf(stderr, "msgsnd failed\n");
			exit(EXIT_FAILURE);
		}
		if(strncmp(buffer, "end", 3)==0)
		{
			running=0;
		}
	}   
	exit(EXIT_SUCCESS);
}
