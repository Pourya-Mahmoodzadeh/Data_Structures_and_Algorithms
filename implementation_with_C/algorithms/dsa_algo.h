// #ifndef DSA_ALGO_H
#define DSA_ALGO_H

#include <stddef.h>

/**
 * The function compares the first parameter a and the second one b.and returns an int x:
 * if a > b: x > 0
 * if a < b: x < 0
 * if a == b: x = 0 
 */
typedef int (*dsa_algo_compare_func) (const void*, const void*);

/**  Sort an array using insertion sort algorithm using:
 * @param: base A pointer to the array is wanted to be sorted.
 * @param: size The size of each element in bytes.
 * @param: count The number of elements of the array.
 * @param: compare_func A typical compare function.
*/
void dsa_algo_insertion_sort (
    void* base,
    const size_t count,
    const size_t size,
    dsa_algo_compare_func cmp_func
);















// #endif

