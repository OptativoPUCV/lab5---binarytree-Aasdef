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
//recibe la función de comparación de claves y crea un mapa (TreeMap) inicializando sus variables.
  TreeMap*map=(TreeMap*)malloc(sizeof(TreeMap));

  if (map==NULL){
    //error de asignacion de memoria
    return NULL;
  }
  map->lower_than=lower_than;
  map->root=NULL;
  return map;
  

}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
// inserta un nuevo dato (key,value) en el árbol y hace que el current apunte al nuevo nodo.
  if (tree==NULL){
    return;//o crear un nuevo arbol
  }
  //buscar ubicacion
  TreeNode*padre=NULL;
  TreeNode*actual=tree->root;

  while (actual !=NULL){
    int aux = is_equal(tree, key, actual->pair->key);

    if (aux==0){
      //Existe
      return;
    }
    else if(aux<0){
      padre=actual;
      actual=actual->left;
    }
    else{
      padre=actual;
      actual=actual->right;
    }
  }

  //crear un nodo para el nuev0
  TreeNode*nuevo=createTreeNode(key,value);
  if (padre==NULL){
    tree->root =nuevo;//si esta vacio el nuevo sera raiz
  }else{
    int aux=is_equal(tree, key , actual->pair->key);
    if(aux==0){
      return;//clave repetida
    }
    else if (aux<0){
      padre->left=nuevo;
      
    }else{
      padre->right=nuevo;
    }
  }
  tree->current=nuevo;
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
  //busca el nodo con clave igual a key y retorna el Pair asociado al nodo. 
  if (tree==NULL || tree->root ==NULL){
    return NULL;//el arbol esta vacío
  }

  TreeNode*node = tree->root;//nodo va a ser igual al padre
  while (node !=NULL){
    int aux=tree->lower_than(key, node->pair->key);// retorna 1 si key1<key2.
    if (aux==0){
      //actualizar el puntero
      tree->current=node;
      return node->pair;
      
    }
    else if (aux<0){//buscar en la otra "rama"
      node=node->left;
    }else{//buscar en el otro subarbol
      node=node->right;
    }
  }
  tree->current =NULL;
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
