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

#define MAXBUFLEN 4096

int main(int argc, char* argv[])
{
	int s = socket(PF_INET, SOCK_STREAM, 0);
	if(s < 0) {
		ZF_LOGF("socket() error: %s", strerror(errno));
		return -1;
	}

	int optval = 1;
	if(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) != 0)
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

	if(bind(s, res->ai_addr, res->ai_addrlen) != 0) {
		ZF_LOGF("Error binding socket: %s", strerror(errno));
		return -1;
	}

	freeaddrinfo(res);

	if(listen(s, SOMAXCONN) != 0) {
		ZF_LOGF("listen() error: %s", strerror(errno));
		return -1;
	}

	ZF_LOGI("Listening to %s:%s", host, service);

	struct sockaddr addr;
	socklen_t addrlen = sizeof(addr);
	int conn_sock = accept(s, &addr, &addrlen);
	if(conn_sock == -1) {
		ZF_LOGF("Error accepting new connection: %s", strerror(errno));
		return -1;
	}

	ZF_LOGI("New connected client"); // TODO: show IP connected

	char buf[MAXBUFLEN] = {0};
	int n_bytes = read(conn_sock, buf, MAXBUFLEN);
	if(n_bytes == -1) {
		ZF_LOGF("read() error: %s", strerror(errno));
		return -1;
	} else
		ZF_LOGI_MEM(buf, n_bytes, "%d bytes received", n_bytes);

	strcpy(buf, "HTTP/1.1 200 OK\r\n");
	n_bytes = write(conn_sock, buf, strlen(buf));

	if(n_bytes == -1) {
		ZF_LOGF("write() error: %s", strerror(errno));
		return -1;
	} else
		ZF_LOGI_MEM(buf, n_bytes, "%d bytes written", n_bytes);

	if(close(s) == 0)
		ZF_LOGI("Connection closed.");
	else
		ZF_LOGE("Error closing socket: %s", strerror(errno));

	return 0;
}

