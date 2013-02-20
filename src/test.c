#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "libstr.h"

#define ASSERT(msg, c) do {                                                         \
    if (!(c)) printf("%s:%d:%s: Assertion failed: "#c"\n", __FILE__, __LINE__, msg);  \
} while (0)

#define ASSERT_EQUAL(msg, x, y) ASSERT(msg, x == y)

#define ASSERT_NOT_EQUAL(msg, x, y) ASSERT(msg, x != y)

static void test_append(void)
{
    str_t *s;

    s = str_alloc();
    str_append("", s);
    ASSERT_EQUAL("str_append()", 0, strcmp("", str_get(s)));	
    str_append("foo", s);
    ASSERT_EQUAL("str_append()", 0, strcmp("foo", str_get(s)));
    str_append("123456789123456789123456789123456789123456789", s);
    ASSERT_EQUAL("str_append()", 0, strcmp("foo123456789123456789123456789123456789123456789", str_get(s)));
    str_free(s);
}

static void test_alloc_with(void)
{
    str_t *s;

    s = str_alloc_with("foo");
    ASSERT_EQUAL("str_alloc_with()", 0, strcmp("foo", str_get(s)));
    str_free(s);
}

static void test_set(void)
{
    str_t *s;

    s = str_alloc();
    str_set("abc", s);
    ASSERT_EQUAL("str_set()", 0, strcmp("abc", str_get(s)));
    ASSERT_EQUAL("str_set()", 3, str_length(s));
    str_free(s);
}

int main(int argc, char **argv)
{
    test_alloc_with();
    test_append();
    test_set();

    return 0;
}
