                                                                              
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>


void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char *argv[])
{
	int idx;
	struct hostent *host;
	
	if(argc != 2)
	{
		printf("Usage : %s [addr]\n", argv[0]);
		exit(1);
	}
	host = gethostbyname(argv[1]);
	
	printf("offical name : %s\n", host->h_name);
	
	for(idx=0; host->h_aliases[idx]; idx++)
		printf("Alias %d : %s\n", idx+1, host->h_aliases[idx]);

	printf("Address type :  %s\n", host->h_addrtype == AF_INET ? "AF_INET" : "AF_INET6");


	for(idx=0; host->h_addr_list; idx++)
		printf("IP addr %d : %s\n", idx+1, inet_ntoa(*(struct in_addr*)host->h_addr_list[idx]));

	return 0;

}
