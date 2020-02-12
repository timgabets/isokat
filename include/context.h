#pragma once

typedef struct isokat_context {
	const char* listen_host;
	const char* listen_service;
} isokat_ctx_t;

isokat_ctx_t *isokat_ctx_new(void);
void isokat_ctx_free(isokat_ctx_t*);
