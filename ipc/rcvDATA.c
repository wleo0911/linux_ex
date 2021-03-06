/*받는 놈*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msg_st // 보낸 구조체를 받기 위해서 같은 구조체 선언
{
	long int my_msg_type; // 필수
	char some_text[BUFSIZ]; //
};

int main()
{
	int running = 1;
	int msgid;
	struct my_msg_st some_data;
	long int msg_to_receive = 0;

	/* First, we set up the message queue*/

	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error : %d\n", errno);
		exit(EXIT_FAILURE);
	}
	/*
	   exit(0) or exit(EXIT_SUCCESS) -> exit() implimentation에 정의된 성공적인 상태의 마침을 반환
	   exit(EXIT_FAILURE) -> implimentation에 정의된 실패한 상태의 마침을 반환
	*/

		/*then the messagers are retrieved from the queue, intil an end message is encountered. Lastly, the message queue is deleted. */
	

	while(running)
	{
		if(msgrcv(msgid, (void *)&some_data, BUFSIZ, msg_to_receive, 0)==-1)
		{
			fprintf(stderr, "msgrcv failed with error : %d\n", errno);
			exit(EXIT_FAILURE);
		}
		if(some_data.my_msg_type!=3){
			printf("You wrote : %s", some_data.some_text);
		} else {
			running=0;
		}
	
	}
	if (msgctl(msgid, IPC_RMID, 0)==-1)
	{
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
	
