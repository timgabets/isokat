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
		fprintf(stderr, "Socket error: %s\n", strerror(errno));
		return -1;
	}

	if(connect(sockfd, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) < 0){
		fprintf(stderr, "Error connecting to %s:%d : %s\n", srv_name, port, strerror(errno));
		return -1;
	}

	const char* data = "00039" "0800" "\x82\x20\x00\x00\x00\x00\x00\x00\x04\x00\x00\x00\x00\x00\x00\x00" "0314161430000030001";
	int data_len = 44;
	send(sockfd, data, data_len, 0);
	fprintf(stdout, "%d bytes sent\n", data_len);

	char buf[MAXBUFLEN];
	int nbytes = recv(sockfd, buf, MAXBUFLEN, 0);
	fprintf(stdout, "%d bytes received\n", nbytes);

	close(sockfd);
}
