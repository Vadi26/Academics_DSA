#include<stdio.h>>
#include<stdlib.h>
#include<stdbool.h>

typedef struct node {
    int data;
    struct node *left, *right;
}node;

int isHeap(node *root) {
    if (root->left != NULL && root->right != NULL) return true;
    if(root->right == NULL) return root->data >= root->left->data;

    else {
        if (root->data >= root->left->data && root->data >= root->right->data) return (isHeap(root->left) && isHeap(root->right));
        else return false;
    }
}