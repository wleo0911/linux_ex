#include <stdio.h>

int main(int argc, char **argv)
{
	int count;
	int temp;
	int *test;
	FILE *in, *out;
	char buf[BUFSIZ];
	//printf("BUFSIZE=%d\n", BUFSIZ); // stdio.h에서 지원하는 예약어 bufsiz 

	if(argc<3)
	{
		perror(stderr);
		return -1;
	}


	// 원본 파일 열기
	if((in = fopen(argv[1], "r")) == NULL) // 구조체 in의 값은 초기화를 시키지 않아도 null?? 
										   // 시스템 마다 다르다
	{
		perror(argv[1]);
		return -1;
	}

	temp = in->_fileno;
	printf("temp= %d\n in=\n", temp); 

	// 대상 파일 열기
	if((out = fopen(argv[2], "w")) == NULL) 
	{
	    perror(argv[2]);
	    return -1;
	}

	//원본 파일의 내용을 읽어서 대상 파일에 쓰기
	while((count = fread(buf, sizeof(char), BUFSIZ, in)) > 0 )
			fwrite(buf, sizeof(char), count, out);

	fclose(out);
	fclose(in);

	return 0;
}
