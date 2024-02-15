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

  /**
   * \brief Removes an element given by an index from the array.
   * \param array This array.
   * \param index The index of the element to remove.
   * \return The removed element. If the element is not in the
   *         array or the index is invalid, returns NULL.
   * \warning It is up to the caller to free the removed element.
   */
  void *(*removeAt)(struct Array *array, size_t index);

  /**
   * \brief Removes all element in the array.
   * \param array This array.
   * \param destroyElementFn The function used to free each element.
   * \warning The destroy element function is mandatory to prevent memory leaks.
   */
  void (*removeAll)(struct Array *array, void (*destroyElementFn)(void *element));

  /**
   * \brief Inserts an element in the array.
   *
   * If the index is greater than the size of the array, insert at the end.
   * Normally I'd say that if the index is less than 0 then insert at the
   * beginning but I'm using a size_t so no.
   *
   * \param array This array.
   * \param element The new element to insert.
   * \param index The index where to insert the element.
   */
  void (*insertAt)(struct Array *array, void *element, size_t index);

  /**
   * \brief Returns the element at the given index in the array.
   *
   * Why would you want to use this function? To not get yelled at by the memory
   * that you're trying to access an element outside the bounds of the array.
   *
   * Though, this is unnecessary if you want anyway.
   *
   * \param array This array.
   * \param index The index of the element to return.
   * \return The element at the given index, if the index is invalid,
   *         returns NULL.
   */
  void *(*at)(struct Array *array, size_t index);

  /**
   * \brief Stringifies the array.
   *
   * The stringifyFn must return the string version of each element for this
   * function to be able to stringify the whole array. The string returned by
   * stringifyFn is freed internally.
   *
   * \param array This array.
   * \param stringifyFn A function pointer on how to handle stringifying each
   *                    element.
   * \return The stringified array.
   * \warning It is up to the caller to free the stringified array.
   */
  char *(*toString)(struct Array *array, char *(*stringifyFn)(void *element));
} Array;

Array *createArray();

#endif // COLLECTIONS_ARRAY_H
