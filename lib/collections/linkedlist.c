#include "linkedlist.h"
#include <stdlib.h>
#include <string.h>

LinkedNode *createLinkedNode(void *value);
void append_LinkedList(LinkedList *list, void *element);
void prepend_LinkedList(LinkedList *list, void *element);
void insertAt_LinkedList(LinkedList *list, void *element, size_t size);
size_t indexOf_LinkedList(LinkedList *list, void *element);
void *removeBeg_LinkedList(LinkedList *list);
void *removeEnd_LinkedList(LinkedList *list);
void *remove_LinkedList(LinkedList *list, void *element);
void *removeAt_LinkedList(LinkedList *list, size_t index);
void removeAll_LinkedList(LinkedList *list, void (*destroyElementFn)(void *element));
char *toString_LinkedList(LinkedList *list, char *(*stringifyFn)(void *element));
void destroy_LinkedList(LinkedList *list, void (*destroyElementFn)(void *element));

LinkedList *createLinkedList()
{
  LinkedList *list = malloc(sizeof(LinkedList));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;

  list->append = append_LinkedList;
  list->prepend = prepend_LinkedList;
  list->insertAt = insertAt_LinkedList;
  list->indexOf = indexOf_LinkedList;
  list->removeBeg = removeBeg_LinkedList;
  list->removeEnd = removeEnd_LinkedList;
  list->remove = remove_LinkedList;
  list->removeAt = removeAt_LinkedList;
  list->removeAll = removeAll_LinkedList;
  list->toString = toString_LinkedList;
  list->destroy = destroy_LinkedList;
  return list;
}

LinkedNode *createLinkedNode(void *value)
{
  LinkedNode *node = malloc(sizeof(LinkedNode));
  node->value = value;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

void append_LinkedList(LinkedList *list, void *element)
{
  // Case: no elements
  if (list->head == NULL && list->tail == NULL && list->size == 0)
  {
    prepend_LinkedList(list, element);
    return;
  }

  LinkedNode *node = createLinkedNode(element);

  // Case: has one element
  if (list->size == 1 && list->head == list->tail)
  {
    list->tail = node;
    list->head->next = node;
    node->prev = list->head;
    list->size++;
    return;
  }

  // Case: has two or more elements
  LinkedNode *prevTail = list->tail;
  list->tail = node;
  prevTail->next = node;
  node->prev = prevTail;
  list->size++;
}

void prepend_LinkedList(LinkedList *list, void *element)
{
  LinkedNode *node = createLinkedNode(element);

  // Case: no elements
  if (list->head == NULL && list->tail == NULL && list->size == 0)
  {
    list->head = node;
    list->tail = node;
    list->size++;
    return;
  }

  // Case: has one element
  if (list->size == 1 && list->head == list->tail)
  {
    list->head = node;
    list->tail->prev = node;
    node->next = list->tail;
    list->size++;
    return;
  }

  // Case: has two or more elements
  LinkedNode *prevHead = list->head;
  list->head = node;
  prevHead->prev = node;
  node->next = prevHead;
  list->size++;
}

void insertAt_LinkedList(LinkedList *list, void *element, size_t size)
{
  // Case: no elements
  if (list->head == NULL && list->tail == NULL && list->size == 0)
  {
    append_LinkedList(list, element);
    return;
  }

  // Case: size is out of bounds
  if (size >= list->size)
  {
    append_LinkedList(list, element);
    return;
  }

  if (size == 0)
  {
    prepend_LinkedList(list, element);
    return;
  }

  // Case: has two or more elements
  LinkedNode *node = createLinkedNode(element);
  LinkedNode *current = list->head;
  for (size_t i = 0; current->next != NULL && i != size; i++)
    current = current->next;
  node->prev = current->prev;
  node->next = current;
  current->prev = node;
  node->prev->next = node;
  list->size++;
}

size_t indexOf_LinkedList(LinkedList *list, void *element)
{
  size_t index = 0;
  for (LinkedNode *current = list->head; current != NULL; current = current->next, index++)
    if (current->value == element)
      return index;
  return -1;
}

void *removeBeg_LinkedList(LinkedList *list)
{
  // stub!
  return NULL;
}

void *removeEnd_LinkedList(LinkedList *list)
{
  // stub!
  return NULL;
}

void *remove_LinkedList(LinkedList *list, void *element)
{
  // stub!
  return NULL;
}

void *removeAt_LinkedList(LinkedList *list, size_t index)
{
  // stub!
  return NULL;
}

void removeAll_LinkedList(LinkedList *list, void (*destroyElementFn)(void *element))
{
  // stub!
}

char *toString_LinkedList(LinkedList *list, char *(*stringifyFn)(void *element))
{
  if (stringifyFn == NULL)
    return NULL;

  // '[', ']', '\0' plus ", " for each element exluding the last element
  size_t length = 1 + 1 + 1 + 2 * (list->size - 1);

  // extract each stringified version of the elements
  LinkedList *elementStrings = createLinkedList();
  for (LinkedNode *current = list->head; current != NULL; current = current->next)
  {
    elementStrings->append(elementStrings, stringifyFn(current->value));
    if (elementStrings->tail->value != NULL)
      length += strlen(elementStrings->tail->value);
  }

  // build string list and also free the elements' strings
  char *stringified = malloc(length);
  strcpy(stringified, "[");
  for (LinkedNode *current = elementStrings->head; current != NULL; current = current->next)
  {
    if (current->value != NULL)
    {
      strcat(stringified, current->value);
      free(current->value);
    }

    if (current->next != NULL)
      strcat(stringified, ", ");
  }
  strcat(stringified, "]");
  free(elementStrings); // TODO: use the destroy function when it's done

  return stringified;
}

void destroy_LinkedList(LinkedList *list, void (*destroyElementFn)(void *element))
{
  // stub!
}
