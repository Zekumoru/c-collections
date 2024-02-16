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
  LinkedList *list = createLinkedList();

  Integer *one = createInteger(1);
  Integer *two = createInteger(2);
  Integer *three = createInteger(3);
  Integer *four = createInteger(4);
  Integer *five = createInteger(5);
  Integer *six = createInteger(6);
  Integer *seven = createInteger(7);

  list->append(list, one);
  list->append(list, two);
  list->append(list, three);
  list->append(list, four);
  list->append(list, five);
  list->append(list, six);
  list->append(list, seven);

  char *str = list->toString(list, (char *(*)(void *))stringifyInteger);
  printf("List: %s\n", str);
  free(str);

  printf("List from tail: [");
  for (LinkedNode *current = list->tail; current != NULL; current = current->prev)
  {
    printf("%d", ((Integer *)current->value)->value);
    if (current->prev != NULL)
      printf(", ");
  }
  printf("]\n");

  list->destroy(list, (void (*)(void *))destroyInteger);
  return 0;
}
