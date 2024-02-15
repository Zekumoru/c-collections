#include <stdio.h>
#include <stdlib.h>
#include "lib/collections/collections.h"

typedef struct Integer
{
  int value;
} Integer;

Integer *createInteger(int value)
{
  Integer *integer = malloc(sizeof(Integer));
  integer->value = value;
  return integer;
}

void destroyInteger(Integer *integer)
{
  free(integer);
}

char *stringifyInteger(Integer *integer)
{
  size_t length = snprintf(NULL, 0, "%d", integer->value);
  char *integerString = malloc(length);
  sprintf(integerString, "%d", integer->value);
  return integerString;
}

int main()
{
  Array *array = createArray();

  array->insertAt(array, createInteger(4), 100);
  array->add(array, createInteger(1));
  array->add(array, createInteger(2));
  array->insertAt(array, createInteger(5), 2);
  array->add(array, createInteger(3));

  destroyInteger(array->removeAt(array, 1));

  char *arrayString = array->toString(array, (char *(*)(void *))stringifyInteger);
  printf("%s\n", arrayString);
  free(arrayString);

  array->destroy(array, (void (*)(void *))destroyInteger);

  return 0;
}
