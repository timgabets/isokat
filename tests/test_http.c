#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "http.h"

Test(http, dummy)
{
	const char* buf = "iddqd";
	http_msg_ctx_t *ctx = process_http_request(buf, strlen(buf));
	cr_assert(ne(ptr, ctx, NULL), "Should not segfault on random data");
	http_msg_ctx_free(ctx);
}

Test(http, get)
{
	const char* buf = "GET / HTTP/1.1\r\nHost: localhost:8080\r\nUser-Agent: curl/7.59.0\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: 41\r\n\r\n{\"i000\":\"0100\",\"i002\":\"4444000011112222\"}";

	http_msg_ctx_t *ctx = process_http_request(buf, strlen(buf));
	cr_assert(ne(ptr, ctx, NULL), "Should not segfault on random data");
	http_msg_ctx_free(ctx);
}
