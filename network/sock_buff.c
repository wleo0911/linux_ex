#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

void error_handling(char *message)
{
	fputs(message, stderr);
	fputs('\n', stderr);
	exit(1)
}

int main(int argc, char *argv[])
{
	int tcp_sock, udp_sock;
	int snd_buf, rcv_buf;
	soklen_t optlen;
	int state;

	optlen = sizeof(snd_buf);
	
	// TCP socket
	tcp_sock = socket(PF_INET, SOCK_STREAM, 0);

	// TCP Read : snd_buf

	state = hetsockopt(tcp_sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &optlen);
	if(state)
		error_handling("getsocket() snf_buf error");

	printf("Socket output buffer size : %d\n", snd_buf);

	snd_buf = (snd_buf << 1);
	state = setsockopt(tcp_sock, SOL_SOCKET, SO_SNDBUF, (void*)&snd_buf, &optlen);
	if(state)
		error_handling("setsocket() snf_buf error");
}
