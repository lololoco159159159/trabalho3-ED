#include "BinaryTree.h"
#include <stdlib.h>
#include <stdio.h>

//===structs===//

struct Node{
    void *key;
    void *value;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
};

struct BinaryTree{
    Node *root;
    CmpFn cmp_fn;
    KeyDestroyFn key_destroy_fn;
    ValDestroyFn val_destroy_fn;
};

//===functions node===//
Node *node_construct(void *key, void *value, Node *left, Node *right){
    Node *node = (Node*) malloc(sizeof(Node));
    node->key = key;
    node->value = value;

    node->parent = NULL;
    node->left = left;
    node->right = right;
    return node;
}

void node_destroy(Node *node){
    if (node == NULL) return;
    free(node);
}

//===functions key_val_pair===//
KeyValPair *key_val_pair_construct(void *key, void *val){
    KeyValPair *kvp = (KeyValPair*) malloc(sizeof(KeyValPair));
    kvp->key = key;
    kvp->value = val;
    return kvp;
}

void key_val_pair_destroy(KeyValPair *kvp){
    if (kvp == NULL) return;
    free(kvp);
}

//===functions BinaryTree===//
BinaryTree *binary_tree_construct(CmpFn cmp_fn, KeyDestroyFn key_destroy_fn,ValDestroyFn val_destroy_fn){
    BinaryTree *bt = (BinaryTree*) malloc(sizeof(BinaryTree));
    bt->root = NULL;
    bt->cmp_fn = cmp_fn;
    bt->key_destroy_fn = key_destroy_fn;
    bt->val_destroy_fn = val_destroy_fn;
    return bt;
}

void *binary_tree_add(BinaryTree *bt, void *key, void *value){
    int *idx = binary_tree_get(bt, key);
    if (idx == NULL){
        Node *node = node_construct(key, value, NULL, NULL);
        if (bt->root == NULL){
            bt->root = node;
            return NULL;
        }
      
        Node *current = bt->root;
        while(1){
            if (bt->cmp_fn(key, current->key) < 0){
                if (current->left == NULL){
                    current->left = node;
                    node->parent = current;
                    return NULL;
                }
                else current = current->left;
            }
            else{
                if (current->right == NULL){
                    current->right = node;
                    node->parent = current;
                    return NULL;
                }
                else current = current->right;
            }
        }
        return NULL;
    }
    else{
        Node *current = bt->root;
        while(1){
            if (bt->cmp_fn(key, current->key) == 0){
                void *tmp = current->value;
                current->value = value;
                bt->val_destroy_fn(tmp);
                return key;
            }
            else if (bt->cmp_fn(key, current->key) < 0) current = current->left;
            else current = current->right;
        }
    }
}


int binary_tree_empty(BinaryTree *bt){
    if (bt->root == NULL) return 1;
    return 0;
}

void *binary_tree_get(BinaryTree *bt, void *key){
    Node *current = bt->root;
    while(current != NULL){
        if (bt->cmp_fn(key, current->key) == 0) return current->value;
        else if (bt->cmp_fn(key, current->key) < 0) current = current->left;
        else current = current->right;
    }
    return NULL;
}

void binary_tree_destroy(BinaryTree *bt){
    if (bt == NULL) return;
    Node *current = bt->root;
    while(current != NULL){
        if (current->left != NULL) current = current->left;
        else if (current->right != NULL) current = current->right;
        else{
            Node *parent = current->parent;
            if (parent == NULL){
                bt->key_destroy_fn(current->key);
                bt->val_destroy_fn(current->value);
                node_destroy(current);
                bt->root = NULL;
                break;;
            }
            if (parent->left == current) parent->left = NULL;
            else parent->right = NULL;
            bt->key_destroy_fn(current->key);
            bt->val_destroy_fn(current->value);
            node_destroy(current);
            current = parent;
        }
    }
    free(bt);
}

//====BinaryTreePrint====//
Vector *binary_tree_levelorder_traversal(BinaryTree *bt){
    Vector *v = vector_construct();
    if (bt->root == NULL) return v;
    Queue *q = queue_construct();
    queue_push(q, bt->root);
    while(!queue_empty(q)){
        Node *node = queue_pop(q);
        vector_push_back(v, key_val_pair_construct(node->key, node->value));
        if (node->left != NULL) queue_push(q, node->left);
        if (node->right != NULL) queue_push(q, node->right);
    }
    queue_destroy(q);
    return v;
}
