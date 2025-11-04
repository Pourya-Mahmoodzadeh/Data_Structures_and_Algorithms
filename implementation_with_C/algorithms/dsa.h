#ifndef DSA_H
#define DSA_H

#include <stddef.h>


#define DSA_STACK_ALLOC_THRESHOLD 1024
#define DSA_STACK_BUFFER_SIZE DSA_STACK_ALLOC_THRESHOLD
#define DSA_OPTIMAL_SMALL_SWAP 1

/**
 * Error codes as enums
 */
typedef enum
{
    DSA_OK = 0,
    DSA_ERR_GENERAL,
    DSA_ERR_NULL_POINTER,
    DSA_ERR_ALLOC
} dsa_error_code;

/**
 * The function compares the first parameter a and the second one b.and returns an int x:
 * if a > b: x > 0
 * if a < b: x < 0
 * if a == b: x = 0 
 */
typedef int (*dsa_compare) (const void*, const void*);

/**
 * Takes 3 pointers and stores the sum of the first two in the last one.
 * Enough space should be allocated for for the last pointer before this function is called, in other words, the last pointer shouldn't be NULL.
 * Note that sum should be written in a way that it can handle receiving a result type (The third argument is considered the result.) and perfome a sum on it.
 * dsa_algo_sum (null, non-null, non-null), dsa_algo_sum (non-null, null, non-null), dsa_algo_sum (non-null, non-null, non-null) must be defined.
 */
typedef void (*dsa_sum) (const void*, const void*, void *);

/**  Sort an array using insertion sort algorithm
 * @param: base A pointer to the array is wanted to be sorted.
 * @param: size The size of each element in bytes.
 * @param: count The number of elements of the array.
 * @param: compare_func A typical compare function.
*/
int dsa_insertion_sort (
    void* base,
    const size_t count,
    const size_t size,
    dsa_compare cmp_func
);

/**
 * Find the sum of all elements of an array from "start" index till "end" index.
 * Start and end are also included. The behavior is undefined if "start" and "end" are not in the range they should be.
 * @param base A pointer to the array
 * @param size Size of each element of the array in bytes
 * @param start The index of the starting index
 * @param end The index of the last element, the element is also included in the result
 * @param sum Where the results should be stored
 * @param sum_func a dsa_algo_sum
 * @return 0 if everything went fine, 1 if a problem occured
 */
int dsa_sum_array (
    void* const base,
    const size_t size,
    const size_t start,
    const size_t end,
    void * const sum,
    dsa_sum sum_func
);



/**  Sort an array using bubble sort algorithm
 * @param: base A pointer to the array is wanted to be sorted.
 * @param: size The size of each element in bytes.
 * @param: count The number of elements of the array.
 * @param: compare_func A typical compare function.
*/
int dsa_bubble_sort (
    void* base,
    const size_t count,
    const size_t size,
    dsa_compare cmp_func
);


















#endif

