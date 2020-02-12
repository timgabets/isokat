#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "conf.h"

Test(parse_config, null_ptr)
{
	isokat_ctx_t ctx; 
	const char* filename = "iddqd";

	cr_assert(eq(int, parse_config(&ctx, NULL), VALUE_ERROR));
	cr_assert(eq(int, parse_config(NULL, filename), VALUE_ERROR));
}

Test(parse_config, inexistent_file, .disabled=true)
{
	isokat_ctx_t *ctx = isokat_ctx_new();
	const char* filename = "inexistent_file";

	cr_assert(eq(int, parse_config(ctx, filename), PARSE_ERROR));
	isokat_ctx_free(ctx);
}

Test(parse_config, ok, .disabled=true)
{
	isokat_ctx_t *ctx = isokat_ctx_new();
	const char* filename = "data/isokat.conf";

	cr_assert(eq(int, parse_config(ctx, filename), OK));
	isokat_ctx_free(ctx);
}
