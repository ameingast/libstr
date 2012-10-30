#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "strlib.h"

#define ASSERT(c) do {                                                       \
  if (!(c)) printf("%s:%d: Assertion failed: <"#c">\n", __FILE__, __LINE__); \
} while (0)

#define ASSERT_EQUAL(x, y) ASSERT(x == y)

#define ASSERT_NOT_EQUAL(x, y) ASSERT(x != y)
  
static void test_append(void)
{
	str_t *s = str_alloc();
	
	str_append("", s);
	ASSERT_EQUAL(0, strcmp("", str_get(s)));	
	
	str_append("foo", s);
	ASSERT_EQUAL(0, strcmp("foo", str_get(s)));
	
	str_append("123456789123456789123456789123456789123456789", s);
	ASSERT_EQUAL(0, strcmp("foo123456789123456789123456789123456789123456789", str_get(s)));
	
	str_free(s);
}

static void test_set_length(void)
{
	str_t *s = str_alloc();
	
	str_set("abc", s);
	ASSERT_EQUAL(0, strcmp("abc", str_get(s)));
	ASSERT_EQUAL(3, str_length(s));
	
	str_free(s);
}

int main(int argc, char **argv)
{
	test_append();
	test_set_length();
	
	return 0;
}