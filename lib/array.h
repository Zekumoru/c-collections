#ifndef COLLECTIONS_ARRAY_H
#define COLLECTIONS_ARRAY_H

#include <stddef.h>

typedef struct Array
{
  void **elements;
  size_t size;
  size_t allocSize;

  /**
   * \brief Adds a new element to the array.
   * \param array This array.
   * \param element The new element to add.
   */
  void (*add)(struct Array *array, void *element);

  /**
   * \brief Finds the index of the given element in the array.
   * \param array This array.
   * \param element The element to find the index of.
   * \return The index of the given element, otherwise -1.
   */
  size_t (*indexOf)(struct Array *array, void *element);

  /**
   * \brief Removes an element from the array.
   * \param array This array.
   * \param element The element to remove.
   * \return The removed element. If the element is not in the
   *         array, returns NULL.
   * \warning It is up to the caller to free the removed element.
   */
  void *(*remove)(struct Array *array, void *element);
  void *(*insertAt)(struct Array *array, size_t index);
  void *(*removeAt)(struct Array *array, size_t index);
  void (*removeAll)(struct Array *array, void (*destroyElementFn)(void *element));
  void *(*at)(struct Array *array, size_t index);
  char *(*toString)(struct Array *array, char *(*stringifyFn)(void *element));
} Array;

Array *createArray();

#endif // COLLECTIONS_ARRAY_H
