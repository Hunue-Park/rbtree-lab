#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  node_t *d = (node_t *)calloc(1, sizeof(node_t));
  // TODO: initialize struct if needed
  p->nil = d;
  p->root = d;
  d->color = RBTREE_BLACK;
  return p;
}

void freenode(node_t *p, rbtree *t) {

    if (p == t->nil) return;
 
    freenode(p->left,t);
    freenode(p->right,t);
    free(p);
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  freenode(t->root,t);
  free(t);
}

void left_rotate(rbtree *t, node_t *x) {
    node_t *y = x->right;
    x->right = y->left;
    if (y->left != t->nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == t->nil) {
        t->root = y;
    } 
    else if (x == x->parent->left) {
        x->parent->left = y;    
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return;

}

void right_rotate(rbtree *t, node_t *x) {
    node_t *y = x->left;
    x->left = y->right;
    if (y->right != t->nil) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == t->nil) {
        t->root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
    return;
}

void rb_insert_Fixup(rbtree *t, node_t *z){
    node_t *parent_pt = t->nil;
    node_t *grand_parent_pt = t->nil;
    //node_t *uncle;
    while ((z != t->root) && (z->color != RBTREE_BLACK) && (z->parent->color == RBTREE_RED)){
        parent_pt = z->parent;
        grand_parent_pt = z->parent->parent;
        node_t *uncle;
        if(z->parent == z->parent->parent->left){
            uncle = z->parent->parent->right;
            //경우1
            if ((uncle != t->nil) && (uncle->color == RBTREE_RED)){
                z->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            }
            //경우2
            else if(z == z->parent->right){
                z = z->parent;
                left_rotate(t,z);
            }
            if (z != t->root && z->parent != t->root) {
                z->parent->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                right_rotate(t, z->parent->parent);
            }
        }
        //반대로
        else{
            uncle = z->parent->parent->left;
            //경우1
            if (uncle != t->nil && uncle->color == RBTREE_RED){
                z->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                z->parent->parent->color = RBTREE_RED;
                z = z->parent->parent;
            }
            //경우2
            else if(z == z->parent->left){
                z = z->parent;
                right_rotate(t,z);
            }
            if (z != t->root && z->parent != t->root) {
                //경우3
                z->parent->color = RBTREE_BLACK;
                
                z->parent->parent->color = RBTREE_RED;
                left_rotate(t, z->parent->parent);
            }
        }
    }
    t->root->color = RBTREE_BLACK;
    return;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
  //t->nil = NULL;
  node_t *parent = t->nil;
  node_t *p = t->root;
  //새 노드가 들어갈 자리 찾기
  while (p != t->nil)
  {
      parent = p;
      if (p->key > key)
      {
          p = p->left;
      }
      else
      {
          p = p->right;
      }
  }
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  new_node->parent = parent;
  // 트리의 첫 노드일 때 - 루트가 된다
  if (parent == t->nil)
  {
      t->root = new_node;
      new_node->color = RBTREE_BLACK;
  }
  //찾은 부모노드보다 새로운 노드가 작을때 - 왼쪽 자식으로
  else if (key < parent->key)
  {
      parent->left = new_node;
      new_node->color = RBTREE_RED;
  }
  //크거나 같을때 - 오른쪽 자식으로
  else
  {
      parent->right = new_node;
      new_node->color = RBTREE_RED;
  }
  //새로운 노드 설정
  new_node->key = key;
  new_node->left = t->nil;
  new_node->right = t->nil;
  rb_insert_Fixup(t, new_node); 
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *r = t->root;
  while (r != t->nil) {
    if (r->key == key) return r;
    else if (r->key < key)
      r = r->right;
    else
      r = r->left;
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}
