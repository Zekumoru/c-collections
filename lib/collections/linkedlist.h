#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stddef.h>

/**
 * \struct LinkedNode
 * \brief A data structure representing a node in a doubly linked list.
 */
typedef struct LinkedNode
{
  void *value;             /**< Pointer to the data stored in the node. */
  struct LinkedNode *next; /**< Pointer to the next node in the linked list. */
  struct LinkedNode *prev; /**< Pointer to the previous node in the linked list. */
} LinkedNode;

/**
 * \struct LinkedList
 * \brief A data structure representing a linked list.
 */
typedef struct LinkedList
{
  LinkedNode *head; /**< Pointer to the head (first node) of the linked list. */
  LinkedNode *tail; /**< Pointer to the tail (last node) of the linked list. */
  size_t size;      /**< Number of elements in the linked list. */

  /**
   * \brief Appends an element to the end of the linked list.
   * \param list This list.
   * \param element The element to be appended.
   */
  void (*append)(struct LinkedList *list, void *element);

  /**
   * \brief Prepends an element to the beginning of the linked list.
   * \param list This list.
   * \param element The element to be prepended.
   */
  void (*prepend)(struct LinkedList *list, void *element);

  /**
   * \brief Inserts an element at the specified index in the linked list.
   * \param list This list.
   * \param element The element to be inserted.
   * \param index The index at which to insert the element.
   */
  void (*insertAt)(struct LinkedList *list, void *element, size_t index);

  /**
   * \brief Retrieves the index of the first occurrence of the given element in
   *        the linked list.
   * \param list This list.
   * \param element The element to search for.
   * \return The index of the element, or -1 if not found.
   * \note -1 in size_t is the SIZE_MAX
   */
  size_t (*indexOf)(struct LinkedList *list, void *element);

  /**
   * \brief Removes and returns the first element of the linked list.
   * \param list This list.
   * \return The removed element, or NULL if the list is empty.
   * \warning It is up to the caller to free the returned removed element
   *          from memory.
   */
  void *(*removeBeg)(struct LinkedList *list);

  /**
   * \brief Removes and returns the last element of the linked list.
   * \param list This list.
   * \return The removed element, or NULL if the list is empty.
   * \warning It is up to the caller to free the returned removed element
   *          from memory.
   */
  void *(*removeEnd)(struct LinkedList *list);

  /**
   * \brief Removes the first occurrence of the specified element from the
   *        linked list.
   * \param list This list.
   * \param element The element to be removed.
   * \return The removed element, or NULL if not found.
   * \warning It is up to the caller to free the returned removed element
   *          from memory.
   */
  void *(*remove)(struct LinkedList *list, void *element);

  /**
   * \brief Removes and returns the element at the specified index in the
   *        linked list.
   * \param list This list.
   * \param index The index of the element to be removed. If the index is
   *              greater than the list's size, removes the last node.
   * \return The removed element.
   * \warning It is up to the caller to free the returned removed element
   *          from memory.
   */
  void *(*removeAt)(struct LinkedList *list, size_t index);

  /**
   * \brief Removes all elements from the linked list.
   * \param list This list.
   * \param destroyElementFn A function to free each element from memory.
   * \warning destroyElementFn is mandatory to avoid memory leaks, however,
   *          it can be NULL.
   */
  void (*removeAll)(struct LinkedList *list, void (*destroyElementFn)(void *element));

  /**
   * \brief Converts the linked list to a string representation using the
   *        provided stringify function.
   * \param list This list.
   * \param stringifyFn A function to convert each element to a string.
   * \return A dynamically allocated string representation of the linked list.
   * \warning It is up to the caller to free the returned string from memory.
   */
  char *(*toString)(struct LinkedList *list, char *(*stringifyFn)(void *element));

  /**
   * \brief Destroys the linked list, freeing all resources, and optionally
   *        destroying each element (which must be mandatory to avoid memory
   *        leaks).
   * \param list This list.
   * \param destroyElementFn A function to free each element from memory.
   * \warning destroyElementFn is mandatory to avoid memory leaks, however,
   *          it can be NULL.
   */
  void (*destroy)(struct LinkedList *list, void (*destroyElementFn)(void *element));
} LinkedList;

/**
 * \brief Creates and returns a new empty linked list.
 * \return A pointer to the created linked list.
 */
LinkedList *createLinkedList();

#endif // LINKEDLIST_H
