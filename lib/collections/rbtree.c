#include "rbtree.h"
#include <stdlib.h>

RBNode *createRBNode(void *value, RBColor color);
void *destroyRBNode(RBNode *node);

void *search_RBTree(struct RBTree *tree, void *element);
bool insert_RBTree(struct RBTree *tree, void *element);
void *remove_RBTree(struct RBTree *tree, void *element);
void removeAll_RBTree(struct RBTree *tree, void (*destroyElementFn)(void *element));
void destroy_RBTree(struct RBTree *tree, void (*destroyElementFn)(void *element));

RBTree *createRBTree(int (*compareFn)(void *e1, void *e2))
{
  RBTree *tree = malloc(sizeof(RBTree));
  tree->root = NULL;
  tree->size = 0;
  tree->compareFn = compareFn;
  tree->insert = NULL;
  tree->insert = NULL;
  tree->remove = NULL;
  return tree;
}

RBNode *createRBNode(void *value, RBColor color)
{
  RBNode *node = malloc(sizeof(RBNode));
  node->value = value;
  node->color = color;
  node->parent = NULL;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void *destroyRBNode(RBNode *node)
{
  // Stub!
  return NULL;
}

void *search_RBTree(struct RBTree *tree, void *element)
{
  // Stub!
  return NULL;
}

bool insert_RBTree(struct RBTree *tree, void *element)
{
  // Stub!
  return false;
}

void *remove_RBTree(struct RBTree *tree, void *element)
{
  // Stub!
  return NULL;
}

void removeAll_RBTree(struct RBTree *tree, void (*destroyElementFn)(void *element))
{
  // Stub!
}

void destroy_RBTree(struct RBTree *tree, void (*destroyElementFn)(void *element))
{
  // Stub!
}
