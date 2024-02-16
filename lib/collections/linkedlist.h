#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stddef.h>

typedef struct LinkedNode
{
  void *value;
  struct LinkedNode *next;
  struct LinkedNode *prev;
} LinkedNode;

typedef struct LinkedList
{
  LinkedNode *head;
  LinkedNode *tail;
  size_t size;

  void (*append)(struct LinkedList *list, void *element);
  void (*prepend)(struct LinkedList *list, void *element);
  void (*insertAt)(struct LinkedList *list, void *element, size_t index);
  size_t (*indexOf)(struct LinkedList *list, void *element);
  void *(*removeBeg)(struct LinkedList *list);
  void *(*removeEnd)(struct LinkedList *list);
  void *(*remove)(struct LinkedList *list, void *element);
  void *(*removeAt)(struct LinkedList *list, size_t size);
  void (*removeAll)(struct LinkedList *list, void (*destroyElementFn)(void *element));
  char *(*toString)(struct LinkedList *list, char *(*stringifyFn)(void *element));
  void (*destroy)(struct LinkedList *list, void (*destroyElementFn)(void *element));
} LinkedList;

LinkedList *createLinkedList();

#endif // LINKEDLIST_H
