#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap* map = (TreeMap*) malloc(sizeof(TreeMap));
    if(map == NULL) return NULL;
    map->root =NULL;
    map->current = NULL;
    map->lower_than = lower_than;
    return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {

  if(tree->root == NULL)
  {
    tree->root =createTreeNode(key, value);
    return;
  }
  tree->current = tree->root;
  if(searchTreeMap(tree,key)!=NULL) return;
  while(tree->current != NULL)
      {
        if(is_equal(tree, ))
        if(tree->lower_than(tree->current->pair->key, key)){
          //HACIA LA DERECHA
          if(tree->current->right==NULL)
          {
            tree->current->right = createTreeNode(key,value);
            tree->current->right->parent = tree->current;
            tree->current = tree->current->right;
            return;
          }
          tree->current=tree->current->right;
          }
        else{//HACIA LA IZQUIERDA
          if(tree->current->left==NULL)
          {
            tree->current->left = createTreeNode(key,value);
            tree->current->left->parent = tree->current;
            tree->current = tree->current->left;
            return;
          }
          tree->current=tree->current->left;
        }
      }
  
  return;
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) {
    tree->current = tree->root;
    //RETORNA NULL SI NO TIENE DATOS EL ARBOL
    if(tree->root == NULL) return NULL;
  
    while(tree->current != NULL)
      {//retorna el dato si existe
        if(is_equal(tree, tree->current->pair->key,key)){
          return(tree->current->pair);
        }
        if(tree->lower_than(tree->current->pair->key, key)){
          //HACIA LA DERECHA
          tree->current = tree->current->right;
        }
        else{//HACIA LA IZQUIERDA
         tree->current = tree->current->left;
        }
      }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
