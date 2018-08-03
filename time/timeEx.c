#include <stdio.h>
#include <time.h>     // time() 호출
#include <sys/time.h> // gettimeofday() 호출 
#include <stdlib.h>

int main(int argc, char *argv[])
{
	time_t UTCtime;
	struct tm *tm;
	char buf[BUFSIZ];
	struct timeval UTCtime_u; // 

	// 1. time()

	time(&UTCtime); // UTCtime = time(); 
	printf("time : %u\n", (unsigned)UTCtime); //UTC 현재 시작 출력

	tm = localtime(&UTCtime); // 연 월 일 시 분 초

	printf("year = %d\n", tm->tm_year);
	printf("asctime : %s\n", asctime(tm));

	strftime(buf, sizeof(buf), "%Y-%m-%e %H:%M:%S %A", tm);
	printf("strftime : %s\n", buf);

	// 2. gettimeofdat()
	gettimeofday(&UTCtime_u, NULL);
	printf("gettimeofday : %ld/%ld\n", UTCtime_u.tv_sec, UTCtime_u.tv_usec);
	




	return 0;
}

