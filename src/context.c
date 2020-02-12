#include <string.h>
#include <stdlib.h>

#include "context.h"

isokat_ctx_t *isokat_ctx_new(void)
{
	isokat_ctx_t *ctx = malloc(sizeof(isokat_ctx_t));
	if(ctx != NULL)
		memset(ctx, 0, sizeof(isokat_ctx_t));
	return ctx;
}

void isokat_ctx_free(isokat_ctx_t *ctx)
{
	free(ctx);
}