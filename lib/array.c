#include "array.h"
#include "dalloc.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

void dallocArray(Array *array);
void add_Array(Array *array, void *element);
size_t indexOf_Array(Array *array, void *element);
void *remove_Array(Array *array, void *element);
void *removeAt_Array(Array *array, size_t index);
void removeAll_Array(Array *array, void (*destroyElementFn)(void *element));
void insertAt_Array(Array *array, void *element, size_t index);
void *at_Array(Array *array, size_t index);
char *toString_Array(Array *array, char *(*stringifyFn)(void *element));
void destroy_Array(Array *array, void (*destroyElementFn)(void *element));

Array *createArray()
{
  Array *array = malloc(sizeof(Array));
  array->size = 0;
  dallocArray(array);
  array->add = add_Array;
  array->indexOf = indexOf_Array;
  array->remove = remove_Array;
  array->removeAt = removeAt_Array;
  array->removeAll = removeAll_Array;
  array->insertAt = insertAt_Array;
  array->at = at_Array;
  array->toString = toString_Array;
  array->destroy = destroy_Array;
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
    array->elements[array->size] = NULL;
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

void removeAll_Array(Array *array, void (*destroyElementFn)(void *element))
{
  // FYI: if a size_t is decremented below 0, it becomes -1
  for (size_t i = array->size - 1; i != -1; i--)
  {
    if (destroyElementFn != NULL)
      destroyElementFn(array->elements[i]);
    removeAt_Array(array, i);
  }
}

void insertAt_Array(Array *array, void *element, size_t index)
{
  dallocArray(array);
  array->size++;

  if (index >= array->size)
    index = array->size - 1;

  // FYI: if a size_t is decremented below 0, it becomes -1
  for (size_t i = array->size - 1; i != -1; i--)
  {
    if (i == index)
    {
      array->elements[i] = element;
      break;
    }

    // shift the array until the new element is inserted
    array->elements[i] = array->elements[i - 1];
  }
}

void *at_Array(Array *array, size_t index)
{
  if (index >= array->size)
    return NULL;
  return array->elements[index];
}

char *toString_Array(Array *array, char *(*stringifyFn)(void *element))
{
  if (stringifyFn == NULL)
    return NULL;

  // '[', ']', '\0' plus ", " for each element exluding the last element
  size_t length = 1 + 1 + 1 + 2 * (array->size - 1);

  // extract each stringified version of the elements
  char **elementStrings = malloc(sizeof(char *) * array->size);
  for (size_t i = 0; i < array->size; i++)
  {
    elementStrings[i] = stringifyFn(array->elements[i]);
    if (elementStrings[i] != NULL)
      length += strlen(elementStrings[i]);
  }

  // build string array and also free the elements' strings
  char *stringified = malloc(length);
  strcpy(stringified, "[");
  for (size_t i = 0; i < array->size; i++)
  {
    if (elementStrings[i] != NULL)
    {
      strcat(stringified, elementStrings[i]);
      free(elementStrings[i]);
    }

    if (i != (array->size - 1))
      strcat(stringified, ", ");
  }
  strcat(stringified, "]");
  free(elementStrings);

  return stringified;
}

void destroy_Array(Array *array, void (*destroyElementFn)(void *element))
{
  removeAll_Array(array, destroyElementFn);
  free(array->elements);
  free(array);
}
