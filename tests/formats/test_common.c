#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "formats/common.h"
#include "cJSON.h"


Test(get_de_index_from_string, error)
{
	cr_expect(eq(int, get_de_index_from_string(""), -1));
	cr_expect(eq(int, get_de_index_from_string("i"), -1));
	cr_expect(eq(int, get_de_index_from_string("x0"), -1));
	cr_expect(eq(int, get_de_index_from_string("de02"), -1));
	cr_expect(eq(int, get_de_index_from_string("ix03"), -1));
}

Test(get_de_index_from_string, ok)
{
	cr_expect(eq(int, get_de_index_from_string("i000"), 0));
	cr_expect(eq(int, get_de_index_from_string("i001"), 1));
	cr_expect(eq(int, get_de_index_from_string("i002"), 2));
	cr_expect(eq(int, get_de_index_from_string("i096"), 96));
	cr_expect(eq(int, get_de_index_from_string("i999"), 999));
}

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

	cr_assert(ne(ptr, msg->elements[0], NULL));
	cr_expect(eq(str, msg->elements[0], (char*) "0100"));

	cr_assert(ne(ptr, msg->elements[2], NULL));
	cr_assert(eq(str, msg->elements[2], (char*) "521324000000"));

	cr_assert(ne(ptr, msg->elements[3], NULL));
	cr_assert(eq(str, msg->elements[3], (char*) "310000"));

	cJSON_Delete(parsed);
	common_msg_free(msg);
}

