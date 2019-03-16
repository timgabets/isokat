#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <zf_log.h>

int main(int argc, char* argv[])
{
	int sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		ZF_LOGF("socket() error: %s", strerror(errno));
		return -1;
	}

	int optval = 1;
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) != 0)
		ZF_LOGW("Error setting SO_REUSEADDR: %s", strerror(errno));

	const char* host = "localhost";
	const char* service = "8080";
	struct addrinfo hint;
	memset(&hint, 0, sizeof(hint));

	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = IPPROTO_TCP;
	struct addrinfo *res;

	if(getaddrinfo(host, service, &hint, &res) != 0) {
		ZF_LOGF("getaddrinfo() error: %s", strerror(errno));
		return -1;
	}

	if(bind(sockfd, res->ai_addr, res->ai_addrlen) != 0) {
		ZF_LOGF("Error binding socket: %s", strerror(errno));
		return -1;
	}

	freeaddrinfo(res);

	if(listen(sockfd, SOMAXCONN) != 0) {
		ZF_LOGF("listen() error: %s", strerror(errno));
		return -1;
	}

	ZF_LOGI("Listening to %s:%s", host, service);


	ZF_LOGI("Hello, world!");
	close(sockfd);
}

