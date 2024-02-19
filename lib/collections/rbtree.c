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
  tree->search = search_RBTree;
  tree->insert = insert_RBTree;
  tree->remove = remove_RBTree;
  tree->removeAll = removeAll_RBTree;
  tree->destroy = destroy_RBTree;
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

void fixPointersRotate_RBTree(RBTree *tree, RBNode *n1, RBNode *n2)
{
  n2->parent = n1->parent;
  n1->parent = n2;

  // If n1 was the root
  if (n1 == tree->root)
    tree->root = n2;

  // Fix grandparent pointer (if exists)
  RBNode *grandparent = n2->parent;
  if (grandparent == NULL)
    return;

  if (grandparent->left == n1)
    grandparent->left = n2;
  else
    grandparent->right = n2;
}

void leftRotate_RBTree(RBTree *tree, RBNode *n1, RBNode *n2)
{
  if (n1 == NULL || n2 == NULL)
    return;

  n1->right = n2->left;
  n2->left = n1;
  fixPointersRotate_RBTree(tree, n1, n2);
}

void rightRotate_RBTree(RBTree *tree, RBNode *n1, RBNode *n2)
{
  if (n1 == NULL || n2 == NULL)
    return;

  n1->left = n2->right;
  n2->right = n1;
  fixPointersRotate_RBTree(tree, n1, n2);
}

bool insert_RBTree(struct RBTree *tree, void *element)
{
  // No compare function to identify its position to the tree
  if (tree->compareFn == NULL)
    return false;

  RBNode *node = createRBNode(element, RB_RED);

  // Case: No root yet
  if (tree->root == NULL)
  {
    node->color = RB_BLACK;
    tree->root = node;
    tree->size++;
    return true;
  }

  // Find its parent in the tree
  RBNode *parent = NULL;
  for (RBNode *current = tree->root; current != NULL;)
  {
    parent = current;
    if (tree->compareFn(element, current->value) < 0)
      current = current->left; // go left
    else
      current = current->right; // go right
  }

  // Insert new node
  if (tree->compareFn(element, parent->value) < 0)
  {
    // element goes to left of parent
    parent->left = node;
    node->parent = parent;
  }
  else
  {
    // element goes to right of parent
    parent->right = node;
    node->parent = parent;
  }

  // recoloring logic
  RBNode *grandparent = parent->parent;

  // Case: no grandparent
  if (grandparent == NULL)
  {
    tree->size++;
    return true;
  }

  RBNode *sibling;

  // Handle situations where node's parent is the left child of its parent
  if (grandparent->left == parent)
  {
    sibling = grandparent->right;

    // Case: its parent's sibling is red
    // Note: the 'its' here is referring to the new node
    if (sibling != NULL && sibling->color == RB_RED)
    {
      // recolor grandparent's children to black
      grandparent->left->color = RB_BLACK;
      grandparent->right->color = RB_BLACK;
      // recolor grandparent to red (if not the root node)
      if (grandparent != tree->root)
        grandparent->color = RB_RED;
    }
    // Case: its parent's sibling is black
    else
    {
      // Case: and the node is on the right of the parent
      if (parent->right == node)
      {
        leftRotate_RBTree(tree, parent, node);
        // swap node and parent to invoke the next case to fix rb violations
        RBNode *temp = node;
        node = parent;
        parent = temp;
      }

      // Case: and the node is on the left of the parent
      rightRotate_RBTree(tree, grandparent, parent);
      grandparent->color = RB_RED;
      parent->color = RB_BLACK;
    }
  }
  // Handle situations where node's parent is the right child of its parent
  else
  {
    sibling = grandparent->left;

    // Case: its parent's sibling is red
    // Note: the 'its' here is referring to the new node
    if (sibling != NULL && sibling->color == RB_RED)
    {
      // recolor grandparent's children to black
      grandparent->right->color = RB_BLACK;
      grandparent->left->color = RB_BLACK;
      // recolor grandparent to red (if not the root node)
      if (grandparent != tree->root)
        grandparent->color = RB_RED;
    }
    // Case: its parent's sibling is black
    else
    {
      // Case: and the node is on the left of the parent
      if (parent->left == node)
      {
        rightRotate_RBTree(tree, parent, node);
        // swap node and parent to invoke the next case to fix rb violations
        RBNode *temp = node;
        node = parent;
        parent = temp;
      }

      // Case: and the node is on the right of the parent
      leftRotate_RBTree(tree, grandparent, parent);
      grandparent->color = RB_RED;
      parent->color = RB_BLACK;
    }
  }

  tree->size++;
  return true;
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
