#include<stdio.h>
#include<stdlib.h>

//주석을 추가합니다

int main(int argc, char *argv[]){

	int value;

	printf("argc=%d\n", argc);
	printf("argv[0]=%s\n", argv[0]);
	printf("argv[1]=%s\n", argv[1]);
	
	value=atoi(argv[1]);
	printf("value=%d\n", value);

	printf("argv[2]=%s\n", argv[2]);


	return 0;
}
