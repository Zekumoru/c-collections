#include "dalloc.h"
#include <stdlib.h>
#include <stdbool.h>

void *_dalloc(void *memory, size_t elementSize, size_t currentSize, size_t *allocSize)
{
  bool toReallocate = false;

  // dynamically reallocate by O(log n)
  while (currentSize >= *allocSize)
  {
    if (*allocSize == 0)
      *allocSize = 1;
    else
      (*allocSize) *= 2;
    toReallocate = true;
  }

  // reallocate minimizing space if possible
  for (size_t newAllocSize = (*allocSize) / 2; currentSize < newAllocSize; newAllocSize /= 2)
  {
    *allocSize = newAllocSize;
    toReallocate = true;
  }

  if (toReallocate)
    return realloc(memory, elementSize * (*allocSize));

  return memory;
}