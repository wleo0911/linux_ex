#include <stdio.h>
#include <stdlib.h>

extern char **environ;

int main(){
	setenv("MYDIR", "/home/shin", 0);

	printf("MYDIR = %s\n", getenv("MYDIR"));

	 
	while(*environ)
		printf("%s\n", *environ++);
	

	return 0;
}

