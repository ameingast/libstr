#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "libstr.h"

#ifndef BM_CNT
#define BM_CNT 100000
#endif

#define BM(NAME, FUN) BMI(NAME, __i, FUN)

#define BMI(NAME, I, FUN) do {                                  \
    clock_t t0 = clock();                                         \
    for (int I = 0; I < BM_CNT; I ++) {FUN}                       \
    clock_t t1 = clock();                                         \
    (void)printf("%s:\t%Fms\n", NAME, (double)(t1 - t0)/BM_CNT);  \
} while (0)

static inline void bm_str_alloc(void)
{
    str_t *ss[BM_CNT] = { NULL };

    BMI("str_alloc()", i, { ss[i] = str_alloc(); });
    for (int i = 0; i < BM_CNT; i++) str_free(ss[i]);
}

static inline void bm_str_alloca()
{
    str_t *ss[BM_CNT] = { NULL };

    BMI("str_alloca()", i, { ss[i] = str_alloca(); });
}

static inline void bm_str_alloc_with()
{
    str_t *ss[BM_CNT] = { NULL };

    BMI("str_alloc_with()", i, { ss[i] = str_alloc_with("foo"); });
    for (int i = 0; i < BM_CNT; i++) str_free(ss[i]);
}

static inline void bm_str_alloca_with()
{
    str_t *ss[BM_CNT] = { NULL };

    BMI("str_alloca_with()", i, { ss[i] = str_alloca_with("foo"); });
}

static inline void bm_str_free(void)
{
    str_t *ss[BM_CNT] = { NULL };

    for (int i = 0; i < BM_CNT; i++) ss[i] = str_alloc();
    BMI("str_free()", i, { str_free(ss[i]); });
}

static inline void bm_str_set(void)
{
    str_t *ss[BM_CNT] = { NULL };

    for (int i = 0; i < BM_CNT; i++) ss[i] = str_alloc();
    BMI("str_set(small)", i, { str_set("foo", ss[i]); });
    BMI("str_set(big)", i, { str_set("123456789123456789123456789123456789123456789", ss[i]); });
    for (int i = 0; i < BM_CNT; i++) str_free(ss[i]);
}

static inline void bm_str_append(void)
{
    str_t *ss[BM_CNT] = { NULL };

    for (int i = 0; i < BM_CNT; i++) ss[i] = str_alloc();
    BMI("str_append(small)", i, { str_append("foo", ss[i]); });
    BMI("str_append(big)", i, { str_append("123456789123456789123456789123456789123456789", ss[i]); });
    BMI("str_append(loop/10)", i, { for (int j = 0; j < 10; j++) str_append("123456789123456789123456789123456789123456789", ss[i]); });
    for (int i = 0; i < BM_CNT; i++) str_free(ss[i]);
}

static inline void bm_str_append_alloca(void)
{
    str_t *ss[BM_CNT] = { NULL };

    for (int i = 0; i < BM_CNT; i++) ss[i] = str_alloca();
    BMI("A str_append(small)", i, { str_append("foo", ss[i]); });
    BMI("A str_append(big)", i, { str_append("123456789123456789123456789123456789123456789", ss[i]); });
    BMI("A str_append(loop/10)", i, { for (int j = 0; j < 10; j++) str_append("123456789123456789123456789123456789123456789", ss[i]); });
}

static inline void bm_str_join(void)
{
    str_t *ss[BM_CNT] = { NULL }, *aux[BM_CNT] = { NULL };

    for (int i = 0; i < BM_CNT; i++) { ss[i] = str_alloc(); str_set("foo", ss[i]); aux[i] = str_alloc(); str_set("foo", aux[i]); }
    BMI("str_join(small)", i, { str_join(aux[i], ss[i]); });
    for (int i = 0; i < BM_CNT; i++) { str_free(ss[i]); str_free(aux[i]); }
}

static inline void bm_str_length(void)
{
    str_t *ss[BM_CNT] = { NULL };
    long cnt = 0;

    for (int i = 0; i < BM_CNT; i++) ss[i] = str_alloc_with("foo");
    BMI("str_length()", i, { cnt += str_length(ss[i]); });
    for (int i = 0; i < BM_CNT; i++) str_free(ss[i]);
}

int main(int argc, char **argv)
{
    bm_str_alloc();
    bm_str_alloca();
    bm_str_free();
    bm_str_set();
    bm_str_length();
    bm_str_alloc_with();
    bm_str_alloca_with();
    bm_str_append();
    bm_str_join();
    // bm_str_append_alloca();

    return 0;
}
