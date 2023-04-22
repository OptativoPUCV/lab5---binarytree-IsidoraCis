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

  tree->current = tree->root;
  TreeNode* nuevoNodo = createTreeNode(key,value);
  
  if(tree->root == NULL) tree->root = nuevoNodo;
  
  while(tree->current != NULL)
      {
        if(is_equal(tree,tree->current->pair->key, key) == 1) return;
        if(tree->lower_than(tree->current->pair->key, key)){
          //HACIA LA DERECHA
          if(tree->current->right==NULL)
          {
            tree->current->right = nuevoNodo;
            tree->current->right->parent = tree->current;
            tree->current = tree->current->right;
            return;
          }
          tree->current=tree->current->right;
          }
        else{//HACIA LA IZQUIERDA
          if(tree->current->left==NULL)
          {
            tree->current->left = nuevoNodo;
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
    while(x->left != NULL) x = x->left;
    return x;
}

void removeNode(TreeMap * tree, TreeNode* node) {
  if(node == NULL) return;
  //Caso en el que el nodo a eliminar no tenga hijos
  if(node->left==NULL && node->right == NULL)
  {
    if(tree->lower_than(node->pair->key, node->parent->pair->key) == 0)        node->parent->right = NULL;
    else node->parent->left = NULL;
    free(node);
    return;
  }
  //Caso en el que solo tenga un hijo
  else if(node->left == NULL || node->right == NULL){
    //Si el hijo está hacia la derecha
    if(node->left == NULL)
    {
      TreeNode * hijo = node->right;
      if(node->parent->left == node) node->parent->left = hijo;
      else node->parent->right = hijo;
      hijo->parent= node->parent;
      free(node);
      return;
    }//Si el hijo está hacia la izq
    else if(node->right == NULL)
    {
      TreeNode * hijo = node->left;
      if(node->parent->right == node) node->parent->right = hijo;
      else node->parent->left = hijo;
      hijo->parent= node->parent;
      free(node);
      return;
    }
  }
  //Caso en el que tenga más de un hijo
  else{
    TreeNode* minimo = minimum(node->right);
    node->pair->key = minimo->pair->key;
    node->pair->value = minimo->pair->value;
    removeNode(tree, minimo);
  }
  return;
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
  if(tree == NULL) return NULL;
  
  TreeNode* ub = NULL;
  tree->current = tree->root;
  while(tree->current !=NULL)
    { 
      if(is_equal(tree, tree->current->pair->key, key) == 1) return                         tree->current->pair;
      else if(tree->lower_than(key, tree->current->pair->key) == 1)
      {
        ub = tree->current;
        tree->current = tree->current->left;
        
      }
      else{
        tree->current = tree->current->right;
        
      }
    }
    if(ub != NULL) return ub->pair;
  
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
  if(tree->root == NULL) return NULL;
  tree->current = tree->root;
  while(tree->current->left != NULL)
    {
      tree->current = tree->current->left;
    }
    return tree->current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  //Si no hay current
    if(tree->current == NULL) return NULL;
  
  if(tree->current->right != NULL)
  {
    TreeNode* actual = tree->current->right;
    while(actual->left != NULL)
      {
        actual= actual->left;
      }
    tree->current = actual;
    return(actual->pair);
  }

  TreeNode* padre= tree->current->parent;
  while(padre!= NULL && padre->right == tree->current)
    {
        tree->current = padre;
        padre = padre->parent;
    }
  tree->current = padre;
  if(padre==NULL) return NULL;
  return(padre->pair);
}
