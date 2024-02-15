#include "array.h"
#include "dalloc.h"
#include <stdlib.h>
#include <math.h>

void dallocArray(Array *array);
void add_Array(Array *array, void *element);
size_t indexOf_Array(Array *array, void *element);
void *remove_Array(Array *array, void *element);
void *removeAt_Array(Array *array, size_t index);

Array *createArray()
{
  Array *array = malloc(sizeof(Array));
  array->size = 0;
  dallocArray(array);
  array->add = add_Array;
  array->indexOf = indexOf_Array;
  array->remove = remove_Array;
  array->removeAt = removeAt_Array;
  array->removeAll = NULL;
  array->insertAt = NULL;
  array->at = NULL;
  array->toString = NULL;
  return array;
}

void dallocArray(Array *array)
{
  array->elements = dalloc(array->elements, sizeof(void *), array->size, array->allocSize);
}

void add_Array(Array *array, void *element)
{
  dallocArray(array);
  array->elements[array->size] = element;
  array->size++;
}

size_t indexOf_Array(Array *array, void *element)
{
  for (size_t i = 0; i < array->size; i++)
    if (element == array->elements[i])
      return i;
  return -1;
}

void *remove_Array(Array *array, void *element)
{
  void *removedElement = NULL;

  for (size_t i = 0, j = -1; i < array->size; i++)
  {
    if (array->elements[i] == element)
    {
      removedElement = element;
      j = i;
      continue;
    }

    // shift array to overwrite the removed element
    if (j != -1)
    {
      array->elements[j] = array->elements[i];
      j++;
    }
  }

  if (removedElement != NULL)
  {
    array->size--;
    dallocArray(array);
  }

  return removedElement;
}

void *removeAt_Array(Array *array, size_t index)
{
  if (index >= array->size)
    return NULL;
  return remove_Array(array, array->elements[index]);
}
