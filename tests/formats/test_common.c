#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "formats/common.h"
#include "cJSON.h"

Test(test_common, json_to_common_nullptr)
{
	msg_common_t* msg = json_to_common(NULL);
	cr_assert(eq(ptr, msg, NULL), "json_to_common() should return NULL when NULL passed in");
}

Test(test_common, json_to_common)
{
	const char* data = "{\"i000\":\"0100\",\"i002\":\"521324000000\",\"i003\":\"310000\"}";
	cJSON *parsed = cJSON_Parse(data);
	cr_assert(ne(ptr, parsed, NULL));

	msg_common_t* msg = json_to_common(parsed);
	cr_assert(ne(ptr, msg, NULL));

	cr_assert(ne(ptr, msg->element[0], NULL));
	cr_expect(eq(str, msg->element[0], (char*) "0100"));
/*
	cr_assert(ne(ptr, msg->element[2], NULL));
	cr_assert(eq(str, msg->element[2], (char*) "521324000000");

	cr_assert(ne(ptr, msg->element[3], NULL));
	cr_assert(eq(str, msg->element[3], (char*) "310000"));
*/
	common_msg_free(msg);
}