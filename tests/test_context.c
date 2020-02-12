#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "context.h"

Test(context, new_free)
{
	isokat_ctx_t *ctx = isokat_ctx_new();	
	cr_assert(ne(ptr, ctx, NULL));

	ctx->host = strdup("localhost");
	ctx->service = strdup("8888n");

	isokat_ctx_free(ctx);
}

Test(channels, new_free)
{
	channel_t *ch = channel_new();	
	cr_assert(ne(ptr, ch, NULL));

	ch->name = strdup("ACQ1");
	ch->host = strdup("localhost");
	ch->port = strdup("22334");

	channel_free(ch);
}

Test(channels, add)
{
	isokat_ctx_t *ctx = isokat_ctx_new();	
	cr_assert(ne(ptr, ctx, NULL));

	ctx->host = strdup("localhost");
	ctx->service = strdup("8888n");

	channel_t *visa = channel_new();	
	cr_assert(ne(ptr, visa, NULL));

	visa->name = strdup("VIS1");
	visa->host = strdup("10.20.30.40");
	visa->port = strdup("22334");

	cr_expect(eq(int, ctx_add_channel(ctx, visa), OK));

	channel_t *mast = channel_new();	
	cr_assert(ne(ptr, mast, NULL));

	mast->name = strdup("MAS1");
	mast->host = strdup("50.60.70.80");
	mast->port = strdup("21653");

	cr_expect(eq(int, ctx_add_channel(ctx, mast), OK));

	cr_expect(eq(str, ctx->channels[0]->name, (char*) "VIS1"));
	cr_expect(eq(str, ctx->channels[0]->host, (char*) "10.20.30.40"));
	cr_expect(eq(str, ctx->channels[0]->port, (char*) "22334"));

	cr_expect(eq(str, ctx->channels[1]->name, (char*) "MAS1"));
	cr_expect(eq(str, ctx->channels[1]->host, (char*) "50.60.70.80"));
	cr_expect(eq(str, ctx->channels[1]->port, (char*) "21653"));

	isokat_ctx_free(ctx);
}