#include "dsa_algo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_ACCESS(base, index, size) ((char*)(base) + (index) * (size))

void dsa_algo_insertion_sort (
    void* base,
    const size_t count,
    const size_t size,
    dsa_algo_compare_func cmp_func
    )
{
    void* key = NULL;
    key = malloc (size);
    if (!key)
        return;

    for (size_t i = 1; i < count; i++)
    {
        memcpy (key, ARRAY_ACCESS(base, i, size), size);

        size_t j = i;

        while (j > 0 && cmp_func(key, ARRAY_ACCESS(base, j - 1, size)) < 0)
        {
            memcpy (ARRAY_ACCESS(base, j, size), ARRAY_ACCESS(base, j - 1, size), size);
            j--;
        }
        memcpy(ARRAY_ACCESS(base, j, size), key, size);
    }
    free (key);
}
