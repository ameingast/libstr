#include "strlib.h"

#include <string.h>

#ifndef STR_SIZE
  #define STR_SIZE 16
#endif

#ifndef FREE
  #define FREE(x) do { free(x); x = NULL; } while (0)
#endif

struct str_t_ {
  char *s;
  size_t len;
  size_t actual;
};

inline str_t *str_alloc(void)
{
	str_t *str = NULL;
	
	if (NULL == (str = malloc(sizeof(str_t)))) {
		return NULL;
	}
	if (NULL == (str->s = calloc(STR_SIZE, sizeof(char)))) {
		FREE(str);
		return NULL;
	}
	str->len = STR_SIZE;
	str->actual = 0;
	return str;
}

inline str_t *str_alloc_with(const char *s)
{
  str_t *str;
  
  if (NULL == (str = str_alloc())) {
    return NULL;
  }
  str_set(s, str);
  return str;
}

inline void str_free(str_t *str)
{
	if (NULL != str) {
		if (NULL != str->s) {
			FREE(str->s);
		}
		FREE(str);
	}
}

inline str_t *str_set(const char *s, str_t *str)
{
	size_t len;
	
	if (NULL == str) {
		return NULL;
	}
	if (NULL == s) {
		return str;
	}
	len = strlen(s);
	if (0 == len) {
		return str;
	}
	FREE(str->s);
	if (NULL == (str->s = calloc(len, sizeof(char)))) {
		str_free(str);
		return NULL;
	}
	strncpy(str->s, s, len);
	str->len = len;
	str->actual = len;
	return str;
}

inline const char *str_get(str_t *str)
{
  return NULL == str ? NULL : str->s;
}

static inline char *resize(size_t len, str_t *str)
{
	if (NULL == (str->s = realloc(str->s, len))) {
		return NULL;
	}
	str->len = len;
	return str->s;
}

inline str_t *str_append(const char *add, str_t *dst)
{
	size_t add_len;
	
	if (NULL == add || 0 == strlen(add) || NULL == dst) {
		return dst;
	}
	add_len = strlen(add);
	if (dst->actual + add_len > dst->len) {
		if (NULL == (dst->s = resize(dst->actual + add_len, dst))) {
			return NULL;
		}
	}
	strncat(dst->s, add, dst->len);
  dst->actual += add_len;
	return dst;
}

inline str_t *str_append_str(str_t *add, str_t *dst)
{
	if (NULL == add || NULL == dst) {
		return NULL;
	}
	return str_append(add->s, dst);
}

inline size_t str_length(str_t *str)
{
	return str == NULL ? 0 : str->actual;
}