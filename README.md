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

To be written.

Check the collections' header files for the documentation of the available functions/methods.

## Changelogs

### v0.0.240215
 - Create Array collection
