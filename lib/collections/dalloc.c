#include "dalloc.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void *_dalloc(void *memory, size_t elementSize, size_t currentSize, size_t *allocSize)
{
  bool toReallocate = false;

  if (currentSize == 0)
  {
    *allocSize = 1;
    toReallocate = true;
  }

  // dynamically reallocate by O(log n)
  // first condition: reallocate minimizing space if possible
  // second condition: reallocate maximizing space to contain new size limit
  if (currentSize < ((*allocSize) / 2) || currentSize >= *allocSize)
  {
    *allocSize = pow(2, ceil(log2(currentSize)));
    toReallocate = true;
  }

  if (toReallocate)
    return realloc(memory, elementSize * (*allocSize));

  return memory;
}