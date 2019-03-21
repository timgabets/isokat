#include <criterion/criterion.h>
#include <criterion/new/assert.h>

Test(test_common, dummy)
{
	cr_assert(eq(int, 0, 0));
}