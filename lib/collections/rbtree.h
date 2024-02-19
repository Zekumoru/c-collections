#ifndef RBTREE_H
#define RBTREE_H

#include <stddef.h>
#include <stdbool.h>

typedef enum RBColor
{
  RB_BLACK,
  RB_RED,
} RBColor;

typedef struct RBNode
{
  void *value;
  RBColor color;
  struct RBNode *parent;
  struct RBNode *left;
  struct RBNode *right;
} RBNode;

typedef struct RBTree
{
  RBNode *root;
  size_t size;
  int (*compareFn)(void *e1, void *e2);
  void *(*search)(struct RBTree *tree, void *element);
  bool (*insert)(struct RBTree *tree, void *element);
  void *(*remove)(struct RBTree *tree, void *element);
  void (*removeAll)(struct RBTree *tree, void (*destroyElementFn)(void *element));
  void (*destroy)(struct RBTree *tree, void (*destroyElementFn)(void *element));
} RBTree;

RBTree *createRBTree(int (*compareFn)(void *e1, void *e2));

#endif // RBTREE_H