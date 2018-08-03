#define _CRT_SECURE_NO_WARNINGS // strtok 보안 경고로 인한 컴파일 에러 방지

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mul();

struct CAL
{
	char data[BUFSIZ]; 	// 전체식
	char oL[BUFSIZ]; 	// 왼쪽 피연산자
	char oR[BUFSIZ]; 	// 오른쪽 피연산자
	int rlt;
};



int main()
{
	struct CAL cal;
    char data[BUFSIZ] = "2+3*3+4";
	strcpy(cal.data, data);
	mul(cal);
}


	// *로 문자열 자르기

void mul(struct CAL *cal) 						
{
	cal = malloc(sizeof(cal));
	strcpy(cal->oL, strtok(cal->data, "*")); 		// *에 NULL을 채우고, *좌측의 값을 리턴
	strcpy(cal->oR, strtok(NULL, "*")); 			// 위에서 NULL로 채워진 다음의 문자에서 다시 검색
	printf("oL= %s, oR = %s\n", cal->oL, cal->oR);   
}



