#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "http_parser.h"
#include "zf_log.h"

#define MAXBUFLEN 4096

int process_http_request(const char* buf, size_t n_bytes)
{
	http_parser_settings settings;
	memset(&settings, 0, sizeof(settings));

	http_parser *p = malloc(sizeof(http_parser));
	http_parser_init(p, HTTP_REQUEST);

	http_parser_execute(p, &settings, buf, n_bytes);
	if(p->http_errno){
		ZF_LOGE("Error processing request: %d", p->http_errno);
	} else {
		if(p->method != HTTP_GET) {
			ZF_LOGE("%s method is not supported (yet)", http_method_str(p->method));
			free(p);
			return -1;
		}
		ZF_LOGE("Processing %s HTTP request...", http_method_str(p->method));
	}
	free(p);
	return 0;
}

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
	int n_bytes = recv(conn_sock, buf, MAXBUFLEN, 0);
	if(n_bytes == -1) {
		ZF_LOGF("recv() error: %s", strerror(errno));
		return -1;
	} else
		ZF_LOGI_MEM(buf, n_bytes, "%d bytes received", n_bytes);

	process_http_request(buf, n_bytes);

	/* Writing response */
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

