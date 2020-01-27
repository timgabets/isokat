#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "http.h"
#include "http_parser.h"

#include "zf_log.h"

http_msg_ctx_t *http_msg_ctx_new(void)
{
	http_msg_ctx_t *msg_ctx = malloc(sizeof(http_msg_ctx_t));
	if(msg_ctx == NULL) {
		ZF_LOGE("alloc error");
		return NULL;
	}
	memset(msg_ctx, 0, sizeof(http_msg_ctx_t));
	return msg_ctx;
}

void http_msg_ctx_free(http_msg_ctx_t *ctx)
{
	if(ctx->data != NULL)
		free(ctx->data);
	free(ctx);
}

static int header_field_cb(http_parser* p, const char *at, size_t length)
{
	/* FIXME: 
	==5397==ERROR: AddressSanitizer: global-buffer-overflow on address 0x00000042288d at pc 0x7f8498d2bfdd bp 0x7fff71261570 sp 0x7fff71260d18
	READ of size 14 at 0x00000042288d thread T0
	    #0 0x7f8498d2bfdc  (/lib64/libasan.so.5+0xbcfdc)
	    #1 0x40e084 in header_field_cb ../src/http.c:31
	    #2 0x414a73 in http_parser_execute ../src/http_parser.c:1376
	    #3 0x40e387 in process_http_request ../src/http.c:72
	    #4 0x40227c in http_get_impl ../tests/test_http.c:18
	*/
	http_msg_ctx_t *msg_ctx = (http_msg_ctx_t *) p->data;
	if(memcmp(at, "Content-Type", length) == 0)
		msg_ctx->has_content_type = true;
	return 0;
}

static int header_value_cb(http_parser* p, const char *at, size_t length)
{
	return 0;
	http_msg_ctx_t *msg_ctx = (http_msg_ctx_t *) p->data;
	if(msg_ctx->has_content_type == true && msg_ctx->content_is_json == false) {
		if(memcmp(at, "application/json", length) == 0)
			msg_ctx->content_is_json = true;
	}
	return 0;
}

int body_cb(http_parser* p, const char *at, size_t length)
{
	http_msg_ctx_t *msg_ctx = (http_msg_ctx_t *) p->data;
	msg_ctx->len = length;
	msg_ctx->data = malloc(length + 1);
	memcpy(msg_ctx->data, at, length);
	return 0;
}

http_msg_ctx_t* process_http_request(const char* buf, size_t n_bytes)
{
	http_msg_ctx_t *msg_ctx = http_msg_ctx_new();
	if(msg_ctx == NULL)
		return NULL;

	http_parser_settings settings;
	memset(&settings, 0, sizeof(http_parser_settings));
	settings.on_header_field = header_field_cb;
	settings.on_header_value = header_value_cb;
	settings.on_body = body_cb;

	http_parser *p = malloc(sizeof(http_parser));
	http_parser_init(p, HTTP_REQUEST);
	p->data = msg_ctx;

	http_parser_execute(p, &settings, buf, n_bytes);
	if(p->http_errno){
		ZF_LOGE("Error processing request: %d", p->http_errno);
	} else {
		if(p->method != HTTP_GET) {
			ZF_LOGE("%s method is not supported (yet)", http_method_str(p->method));
			free(p);
			http_msg_ctx_free(msg_ctx);
			return NULL;
		}
		ZF_LOGE("Processing %s request...", http_method_str(p->method));
	}
	free(p);
	return msg_ctx;
}