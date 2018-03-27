#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#define MAXBUFLEN 1024

int main(int argc, char* argv[])
{
	const char* srv_name = "localhost";
	const int port = 1337;

	struct sockaddr_in srv_addr;
	bzero(&srv_addr, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;

	inet_pton(AF_INET, srv_name, &srv_addr.sin_addr);
	srv_addr.sin_port = htons(port);

	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		fprintf(stderr, "Socket error: %s", strerror(errno));
		return -1;
	}

	if(connect(sockfd, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) < 0){
		fprintf(stderr, "Error connecting to %s:%d : %s", srv_name, port, strerror(errno));
		return -1;
	}

	const char* data = "iddqd";
	send(sockfd, data, strlen(data), 0);

	char buf[MAXBUFLEN];
	recv(sockfd, buf, MAXBUFLEN, 0);

	close(sockfd);
}
