#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "retcodes.h"

typedef enum channel_type {
	XML,
	VISA,
	MASTERCARD
} channel_type_t;

typedef enum connection_type {
	SERVER,
	CLIENT
} connection_type_t;

typedef struct channel {
	channel_type_t type;
	char* name;
	connection_type_t remote_host_is;
	char* host;
	char* port;
	bool synchronous;
	double timeout;
} channel_t;

typedef struct isokat_context {
	char* host;
	char* service;
	size_t n_channels;
	channel_t **channels;
} isokat_ctx_t;

isokat_ctx_t *isokat_ctx_new(void);
void isokat_ctx_free(isokat_ctx_t*);

channel_t *channel_new(void);
void channel_free(channel_t *);

isokat_rc_t ctx_add_channel(isokat_ctx_t *ctx, channel_t *ch);

