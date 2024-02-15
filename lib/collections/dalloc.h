#ifndef DALLOC_H
#define DALLOC_H

#include <stddef.h>

/**
 * \brief A macro to the original dalloc function to avoid using '&' for the
 *        allocation size.
 *
 * Uses a technique to reallocate an array by the multiple of 2 effectively
 * making reallocation have a time-complexity of O(log n).
 *
 * If the array's size is less than the half of the allocation size then
 * this function also accounts for that reallocating to save space.
 *
 * Parameters: memory (the array to reallocate), elementSize (the size of each
 * element in the array), currentSize (the current size of the array), and
 * allocSize (the current allocation size of the array, this is MODIFIED!).
 *
 * Returns the reallocated array.
 */
#define dalloc(memory, elementSize, currentSize, allocSize) _dalloc(memory, elementSize, currentSize, &allocSize);

/**
 * \brief Dynamically reallocate an array.
 *
 * Uses a technique to reallocate an array by the multiple of 2 effectively
 * making reallocation have a time-complexity of O(log n).
 *
 * If the array's size is less than the half of the allocation size then
 * this function also accounts for that reallocating to save space.
 *
 * \param memory The array to reallocate.
 * \param elementSize The size of each element in the array.
 * \param currentSize The current size of the array.
 * \param allocSize A pointer to the allocation size of the array.
 * \return The reallocated array.
 * \warning The current size is not incremented, it is up to the caller to
 *          increment it.
 */
void *_dalloc(void *memory, size_t elementSize, size_t currentSize, size_t *allocSize);

#endif // DALLOC_H
