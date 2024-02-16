#include "linkedlist.h"
#include <stdlib.h>

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
  // stub!
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
}

void insertAt_LinkedList(LinkedList *list, void *element, size_t size)
{
  // stub!
}

size_t indexOf_LinkedList(LinkedList *list, void *element)
{
  // stub!
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
  // stub!
  return NULL;
}

void destroy_LinkedList(LinkedList *list, void (*destroyElementFn)(void *element))
{
  // stub!
}
