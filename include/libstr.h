#ifndef _STRLIB_H_
#define _STRLIB_H_

#include <stdlib.h>

typedef struct str_t_ str_t;

str_t *str_alloc(void);
str_t *str_alloca(void);
str_t *str_alloc_with(const char *s);
str_t *str_alloca_with(const char *s);

void str_free(str_t *str);

str_t *str_set(const char *s, str_t *dst);
const char *str_get(str_t *str);

str_t *str_append(const char *src, str_t *dst);
str_t *str_join(str_t *src, str_t *dst);

size_t str_length(str_t *str);

#endif /* _STRLIB_H_ */
