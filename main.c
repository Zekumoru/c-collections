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

int compareIntegers(Integer *a, Integer *b)
{
  return a->value - b->value;
}

int main()
{
  RBTree *tree = createRBTree((int (*)(void *, void *))compareIntegers);

  Integer *i50 = createInteger(50);
  Integer *i10 = createInteger(10);
  Integer *i30 = createInteger(30);
  Integer *i40 = createInteger(40);
  Integer *i35 = createInteger(35);
  Integer *i32 = createInteger(32);

  tree->insert(tree, i50);
  tree->insert(tree, i10);
  tree->insert(tree, i30);
  tree->insert(tree, i40);
  tree->insert(tree, i35);
  tree->insert(tree, i32);

  return 0;
}
