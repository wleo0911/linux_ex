#include <stdio.h>                                                              
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFSIZE 100



int main(int argc, char *argv[]){

    int fdIn, fdOut;
	int count;   
    char buf[BUFSIZE];
	char err1[BUFSIZE]="usage : copy file1 file2";

	// 인자 값이 3개가 아닌 경우
	if(argc<3){
		//printf("%s", err1);
		//fflush(stdout); // buf에 있는 내용을 stdout으로 출력시키기 위함

		//ssize_t write(int fd, const void *buf, size_t count);
		// fd는 open 한 파일의 기술자 
		// *buf는 fd에 덮어쓸 데이터
		// count는 fd에 쓸 테이터의 크기
		
		write(1, err1, strlen(err1));
		return -1;
	}

	// 원본 파일이 열리지 않은 경우
	if((fdIn = open (argv[1], O_RDONLY)) <0){
		perror(argv[1]); // stderr 에 출력
		return -1;
	}

	// 대상 파일이 열리지 않은 경우
	if((fdOut = open (argv[2], O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR)) < 0 ){
		perror(argv[2]); // 
		return -1;
	}
	
	while((count = read(fdIn, buf, sizeof(buf))) > 0 )
		write(fdOut, buf, count);

	close(fdIn);
	close(fdOut);

	return 0;
}




