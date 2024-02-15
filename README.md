# C Collections

## Introduction

This is my own implementations of the collections' data structures.

To use this library, copy the whole `collections` folder in to your C projects and finally include it!

```c
#include "collections/collections.h"
```

## Concepts

### Allocation size

You will notice the variable `allocSize` inside of the collections like the `Array` collection but what is it exactly?

The allocation size is the **actual** size of the array in the memory (or, _heap_ if you prefer). It is used for dynamic reallocation of the array if the current size of the array exceeds it.

For example, the array currently has 4 elements and the allocation size is also 4 but we need to add a new element. Uh oh, not enough space! Therefore we multiply the allocation size by 2 to get 4 more available spaces then we add the new element. Hooray!

But why multiply by 2? This is a common strategy to dynamically reallocate an array because if we were to reallocate for every each new element, C's `realloc()` might end up performing multiple copy of memory blocks. (In other words, creating a new array with the new size then copying over the elements from the old array to the new array. Okay... If this is still not clear to you, research about how memory works! Specifically that arrays are contiguous.)

### Members-like functions

You'll notice that the way I made the functions of the collections work are like methods in OOP (Object-Oriented Programming).

```c
array->add(array, newElement);
```

Of course, since C doesn't really have the concepts of _"objects"_, specifically _"methods"_, we have to pass the `array` itself as shown above, otherwise the `add()` function won't know the array we're working with.

_"Why not just use functions like you'd normally do in C like `addElement(array, newElement)`?"_

Good question and I've honestly been asked about this, the reason why is that I don't like writing long function names for each collection like `addElementArray()` and we won't be polluting Intellisense with a lot of function names (I said Intellisense because really under the hood, the original functions for the methods are still available globally in the program except of course, Intellisense in VSCode).

> Still not convinced? It really just boils down to my preference so live with it.

Of course, you might have thought that you can pass any array in the `add()` function and yes you can! Matter of fact, it'll modify the array **you passed**. Remember the `add()` is not a method!

```c
array->(anotherArray, newElement);
```

## Collections

### Array Collection

To create an array collection, use the `createArray()` function.

```c
Array *array = createArray();
```

Do not forget to free the array after.

```c
array->destroy(array, destroyElementFn);
```

> `destroyElementFn` is a function that you might need to pass to handle the freeing of each element in the array. It can be `NULL` but beware of memory leaks!

#### Fields

##### elements

A void pointer array which contains the array's elements.

##### size

The size of the array.

##### allocSize

The allocation size of the array.

#### Functions

> Yea I'm lazy to rewrite all of those down.

```c
/**
 * \brief Create a new Array collection.
 * \return The new Array collection.
 */
Array *createArray();

/**
 * An Array collection.
 */
typedef struct Array
{
  void **elements;  /**< Pointer to the array elements. */
  size_t size;      /**< Number of elements in the array. */
  size_t allocSize; /**< Total allocated size for the array. */

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

  /**
   * \brief Frees the array from memory.
   *
   * Freeing the array from memory might cause memory leaks if the
   * destroyElementFn is not passed to handle the freeing of each element
   * from memory.
   *
   * That being said, destroyElementFn can be null.
   *
   * \param array This array.
   * \param destroyElementFn The function used to free each element.
   * \warning Pass the destroy element function to prevent memory leaks.
   */
  void (*destroy)(struct Array *array, void (*destroyElementFn)(void *element));
} Array;
```

## Changelogs

### v0.0.240215
 - Create Array collection
