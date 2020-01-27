#pragma once

#define MAXBUFLEN 4096

typedef struct {
	size_t len;
	char* data;
	bool has_content_type;
	bool content_is_json;
} http_msg_ctx_t;

http_msg_ctx_t *http_msg_ctx_new(void);
void http_msg_ctx_free(http_msg_ctx_t *ctx);

http_msg_ctx_t* process_http_request(const char* buf, size_t n_bytes);
