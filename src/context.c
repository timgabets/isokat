#include <string.h>
#include <stdlib.h>

#include "context.h"

channel_t *channel_new(void) 
{
	channel_t *ch = malloc(sizeof(channel_t)); 
	if(ch != NULL)
		memset(ch, 0, sizeof(channel_t));
	return ch;
}

void channel_free(channel_t *ch)
{
	if(ch == NULL)
		return;
	if(ch->name != NULL)
		free(ch->name);
	if(ch->host != NULL)
		free(ch->host);
	free(ch);
}

isokat_ctx_t *isokat_ctx_new(void)
{
	isokat_ctx_t *ctx = malloc(sizeof(isokat_ctx_t));
	if(ctx != NULL)
		memset(ctx, 0, sizeof(isokat_ctx_t));
	return ctx;
}

void isokat_ctx_free(isokat_ctx_t *ctx)
{
	if(ctx == NULL)
		return;
	if(ctx->port != NULL)
		free(ctx->port);
	if(ctx->channels != NULL) {
		for(size_t i = 0 ; i < ctx->n_channels; i++)
			channel_free(ctx->channels[i]);
		free(ctx->channels);
	}

	free(ctx);
}

isokat_rc_t ctx_add_channel(isokat_ctx_t *ctx, channel_t *ch)
{
	if(ctx == NULL || ch == NULL)
		return VALUE_ERROR;

	ctx->channels = realloc(ctx->channels, (ctx->n_channels + 1) * sizeof(void*));
	if(ctx->channels == NULL)
		return ALLOC_ERROR;
	ctx->channels[ctx->n_channels++] = ch;
	return OK;
}
