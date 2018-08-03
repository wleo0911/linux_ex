#include "mysum.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char oper[5];
	char left[11];
	char right[11];
	int result;

	memset(left, 0x00, 11);
	memset(right, 0x00, 11);

	// 표준 입력(키보드)로부터 문자를 입력 받는다
	// 100+20, 100-20과 같이 연산자와 피연산자 사이에 공백을 두지 않아야 한다.

	fscanf(stdin, "%[0-9]%[^0-9]%[0-9]", left, oper, right);

	if (oper[0] == '-')
	{
		printf("%s %s %s = %d\n", left, oper, right, ydiff(atoi(left), atoi(right)));
	}
	if (oper[0] == '+')
	{
		printf("%s %s %s = %d\n", left, oper, right, ysum(atoi(left), atoi(right)));
	}

}

