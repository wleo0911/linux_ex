#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	int fd, s, sig;
	int cnt;
	char rbuf[100];

	// 올바른 사용법 $ ./auto 2 

	if (argc !=2 || strcmp(argv[1], "--help") == 0)
	
	printf("%s sig-num\n", argv[0]);
	
	// sig는 받고

	system("ps -ef | grep .killReceiver > ps.txt");
	sleep(2);	
	/*
		1. open 사용법

		#include <sys/types.h>
		#include <sys/stat.h>
		#incldue <fcntl.h>

		int open(const char *pathname, int flags, mode_t mode);

		ex)

		fd = open("./ps.txt", O_WRONLY, S_IRUSR | SIWUSR);

		2. return
		error -1
		성공  새로운 파일 지시자
 
	*/

	fd = open("./vim ps.txt", O_WRONLY, S_IRUSR | S_IWUSR);

	if ( fd == -1 )
		printf("Error : file open\n");
	/*
		1. lseek 사용법 
	
		#include <sys/types.h>
		#include <unistd.h>

		off_t lseek(int fildes, off_t offset, int whence);

		whence 
			SEEK_SET 파일의 처음 기준
			SEEK_CUR 현재 위치 기준
			SEEK_END 마지막 기준

		2. return
		error -1
		성공 파일의 시작부터 떨어진 byte만큼 offset을 리턴

	 
	*/

	/*
		1. read 사용법

		#include <unistd.h>

		ssize_t read(int fd, void *buf, size_t count);

		2. return
		error -1 에러가 발생할 경우 errno는 적당한 값으로 설정되며 파일 포인터의 위치는 랜덤
		성공 0 이상의 값 반환
	*/

	lseek(fd, 11, SEEK_SET);
	
	if (read(fd, rbuf, sizeof(int)) < 0);
			printf("Error : read\n");

	sig = atoi(argv[1]);
	printf(".killRecive PID = %d  sig-num = %d\n", atoi(rbuf), sig);

		   
	/*
		1. kill 사용법 

		#include <sys/types.h>
		#incldue <signal.h>

		int kill(pid_t pid, int sig);


		2. ruturn

		성공 0
		실패 -1
	*/
		
		s = kill(atoi(rbuf), sig); // 일단 kill을 한번 보내서 s값 받기 

	if(sig != 0) // 
	{
		if(s == -1)
			printf("Error : system call kill()\n");
		else if(s == 0)
		{ 
			for (cnt=0;cnt<5;cnt++)
			{
				s = kill(atoi(rbuf), sig);
				printf("Process exitst and we can sent it a signal\n");
	   	  	    sleep(1); // ##include <unistd.h>
			}
		}
		      
	} else
			   // break : 반복문을 벗어난다.
			   // continue : 이후 문장을 실행하지 않고 루프의 조건 체크 부분으로 옮긴다. 
	close(fd);	
	return 0;
}

