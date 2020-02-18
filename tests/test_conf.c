#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "conf.h"
#include "config.h"

Test(parse_config, null_ptr)
{
	isokat_ctx_t ctx; 
	const char* filename = "iddqd";

	cr_assert(eq(int, parse_config(&ctx, NULL), VALUE_ERROR));
	cr_assert(eq(int, parse_config(NULL, filename), VALUE_ERROR));
}

Test(parse_config, inexistent_file)
{
	isokat_ctx_t *ctx = isokat_ctx_new();
	const char* filename = "inexistent_file";

	cr_assert(eq(int, parse_config(ctx, filename), VALUE_ERROR));
	isokat_ctx_free(ctx);
}

Test(parse_config, ok)
{
	isokat_ctx_t *ctx = isokat_ctx_new();
	const char* filename = TOPDIR "/tests/data/isokat.conf";

	cr_assert(eq(int, parse_config(ctx, filename), OK));
	cr_assert(eq(int, ctx->n_channels, 3));	

	channel_t *ch = ctx->channels[0];
	cr_assert(ne(ptr, ch, NULL));
	cr_expect(eq(int, ch->type, XML));
	cr_expect(eq(str, ch->name, (char*) "ACQ7"));
	cr_expect(eq(int, ch->remote_host_is, SERVER));
	cr_expect(eq(str, ch->host, (char*) "xml-host-test.tinkoff.ru"));
	cr_expect(eq(int, ch->port, 10302));
	cr_expect(eq(int, ch->asynchronous, true));
	cr_expect(eq(dbl, ch->timeout, 10));

	ch = ctx->channels[1];
	cr_assert(ne(ptr, ch, NULL));
	cr_expect(eq(int, ch->type, VISA));
	cr_expect(eq(str, ch->name, (char*) "VIS1"));
	cr_expect(eq(int, ch->remote_host_is, CLIENT));
	cr_expect(eq(str, ch->host, (char*) "visa-host-test.tinkoff.ru"));
	cr_expect(eq(int, ch->port, 10305));
	cr_expect(eq(int, ch->asynchronous, true));
	cr_expect(eq(dbl, ch->timeout, 1.5));


	ch = ctx->channels[2];
	cr_assert(ne(ptr, ch, NULL));
	cr_expect(eq(int, ch->type, MASTERCARD));
	cr_expect(eq(str, ch->name, (char*) "MAS3"));
	cr_expect(eq(int, ch->remote_host_is, SERVER));
	cr_expect(eq(str, ch->host, (char*) "mc-host-test.tinkoff.ru"));
	cr_expect(eq(int, ch->port, 10306));
	cr_expect(eq(int, ch->asynchronous, false), "Must be async by default");
	cr_expect(eq(dbl, ch->timeout, 0), "Timeout must be zero if not specified");

	isokat_ctx_free(ctx);
}
