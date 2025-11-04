#include "dsa.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stddef.h>



#define ARRAY_ACCESS(base, index, size) ((char*)(base) + (index) * (size))

#define ALLOCATE_TEMPORARY_MEMORY(size, key, buf, use_heap_flag)     \
    const bool use_heap_flag = (size) > DSA_STACK_ALLOC_THRESHOLD; \
    (key) = use_heap_flag ? malloc(size) : (buf); \

#define FREE_TEMPORARY_MEMORY(key, use_heap_flag) do{ if(use_heap_flag){free(key);} } while(0);

static inline void dsa_swap(void*, void*, size_t size, void*);



int dsa_insertion_sort (
    void* base,
    const size_t count,
    const size_t size,
    dsa_compare cmp_func
    )
{
    if (!base || !cmp_func || count == 0)
        return DSA_ERR_NULL_POINTER;

    
    unsigned char buf[DSA_STACK_ALLOC_THRESHOLD];
    void* key = NULL;

    ALLOCATE_TEMPORARY_MEMORY(size, key, buf, use_heap);

    if (!key)
        return DSA_ERR_ALLOC;

    for (size_t i = 1; i < count; i++)
    {
        memcpy(key, ARRAY_ACCESS(base, i, size), size);

        size_t j = i;

        while (j > 0 && cmp_func(key, ARRAY_ACCESS(base, j - 1, size)) < 0)
        {
            memcpy(ARRAY_ACCESS(base, j, size), ARRAY_ACCESS(base, j - 1, size), size);
            j--;
        }
        memcpy(ARRAY_ACCESS(base, j, size), key, size);
    }
    
    FREE_TEMPORARY_MEMORY(key, use_heap);

    return DSA_OK;
}



int dsa_sum_array (
    void* const base,
    const size_t size,
    const size_t start,
    const size_t end,
    void * const sum,
    dsa_sum sum_func
)
{
    if (!sum || !sum_func)
        return DSA_ERR_NULL_POINTER;

    if (start == end)
    {
        sum_func(ARRAY_ACCESS(base, start, size), NULL, sum);
        return DSA_OK;
    }

    sum_func(ARRAY_ACCESS(base, start, size), ARRAY_ACCESS(base, start + 1, size), sum);

    for (size_t i = start + 2; i <= end; i++)
    {
        sum_func(ARRAY_ACCESS(base, i, size), sum, sum);
    }

    return DSA_OK;
}



static inline void dsa_swap (void* a, void* b, size_t size, void* scratch)
{
    #if DSA_OPTIMAL_SMALL_SWAP
    switch (size)
    {
        case 4:
        {
            uint32_t tmp = *(uint32_t*) a;
            *(uint32_t*) a = *(uint32_t*) b;
            *(uint32_t*) b = tmp;
            return;
        }

        case 8:
        {
            uint64_t tmp = *(uint64_t*) a;
            *(uint64_t*) a = *(uint64_t*) b;
            *(uint64_t*) b = tmp;
            return;
        }
    }
    #endif
        memcpy(scratch, a, size);
        memcpy(a, b, size);
        memcpy(b, scratch, size);
}



int dsa_bubble_sort (
    void* base,
    const size_t count,
    const size_t size,
    dsa_compare cmp_func
)
{
    if (!base || !cmp_func || (count == 0))
        return DSA_ERR_NULL_POINTER;

    void* key;
    unsigned char buf[DSA_STACK_ALLOC_THRESHOLD];

    ALLOCATE_TEMPORARY_MEMORY(size, key, buf, use_heap);

    if (!key)
        return DSA_ERR_ALLOC;

    for (size_t i = count; i-- > 0;)
    {
        for (size_t j = 0; j < i; j++)
        {
            if (cmp_func(ARRAY_ACCESS(base, j, size), ARRAY_ACCESS(base, j + 1, size)) > 0)
            {
                dsa_swap(ARRAY_ACCESS(base, j, size), ARRAY_ACCESS(base, j + 1, size), size, key);
            }
        }
    }
    
    FREE_TEMPORARY_MEMORY(key, use_heap);
    
    return DSA_OK;
}

