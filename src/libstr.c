#include <string.h>
#include <alloca.h>

#include "libstr.h"

#define STR_SIZE 16
#define HEAP 0
#define STACK 1

#define FREE(x) do { if (x != NULL) { free(x); x = NULL; } } while (0)

struct str_t_ {
  char *s;
  size_t len;
  size_t actual;
  char mem_type;
};

inline str_t *str_alloc(void)
{
	str_t *str;
	
	if (NULL == (str = malloc(sizeof(str_t)))) {
		return NULL;
	}
	if (NULL == (str->s = calloc(STR_SIZE, sizeof(char)))) {
		FREE(str);
		return NULL;
	}
	str->len = STR_SIZE;
	str->actual = 0;
  str->mem_type = HEAP;
	return str;
}

inline str_t *str_alloca(void)
{
  volatile str_t *str;
	
	if (NULL == (str = alloca(sizeof(str_t)))) {
		return NULL;
	}
	if (NULL == (str->s = alloca(STR_SIZE * sizeof(char)))) {
		return NULL;
	}
	str->len = STR_SIZE;
	str->actual = 0;
  str->mem_type = STACK;
	return (str_t *)str;
}

inline str_t *str_alloc_with(const char *s)
{
  str_t *str;
  
  if (NULL == (str = str_alloc())) {
    return NULL;
  }
  if (NULL == str_set(s, str)) {
    return NULL;
  }
  return str;
}

str_t *str_alloca_with(const char *s)
{
  volatile str_t *str;
  
  if (NULL == (str = str_alloca())) {
    return NULL;
  }
  if (NULL == str_set(s, (str_t *)str)) {
    return NULL;
  }
  return (str_t *)str;
}

inline void str_free(str_t *str)
{
  if (str->mem_type == HEAP && NULL != str) {
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
	if (len > str->len) {
	  FREE(str->s);
	  if (str->mem_type == HEAP) {
  	  if (NULL == (str->s = calloc(len + 1, sizeof(char)))) {
  		  str_free(str);
  		  return NULL;
  	  }	    
	  } else {
	    if (NULL == (str->s = alloca((len + 1) * sizeof(char)))) {
		    return NULL;
	    }
    }
	  str->len = len;
  }
	strncpy(str->s, s, len);
	str->actual = len;
	return str;
}

inline const char *str_get(str_t *str)
{
  return NULL == str ? NULL : str->s;
}

static inline char *resize(size_t len, str_t *str)
{
  if (str->mem_type == HEAP) {
	  if (NULL == (str->s = realloc(str->s, len))) {
		  return NULL;
	  }
  } else {
    char *ptr = str->s;
    if (str->len * 2 + 1 < len) {
      str->len = len;
    } else {
      str->len *= 2;
      str->len += 1;
    }
    if (NULL == (str->s = alloca(str->len * sizeof(char)))) {
      return NULL;
    }
    strncat(str->s, ptr, strlen(ptr));
  }
	return str->s;
}

inline str_t *str_append(const char *add, str_t *dst)
{
	size_t add_len;
	
	if (NULL == add || 0 == strlen(add) || NULL == dst) {
		return dst;
	}
	add_len = strlen(add) + 1;
	if (dst->actual + add_len > dst->len) {
		if (NULL == (dst->s = resize(dst->actual + add_len, dst))) {
      FREE(dst);
			return NULL;
		}
	}
	strncat(dst->s, add, dst->len);
  dst->actual += add_len;
	return dst;
}

inline str_t *str_join(str_t *add, str_t *dst)
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