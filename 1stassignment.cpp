#include<iostream>
#include<stdlib.h>
// #include"header.h"
using namespace std;

typedef struct node {
    int data;
    struct node *left, *right;
}node;

node *createNode(int data) {
	node *p = (node *)malloc(sizeof(node));
	p->data = data;
	p->left = p->right = NULL;
	return p;
}

// Inorder : 9 3 15 20 7
// Preorder : 3 9 20 15 7

int findData(int arr[], int data) { 
    int i = 0;
    while (arr[i] != data)
    {
        i++;
    }
    return i;
}

node* formBT(int preorder[], int inorder[], int inorder_start, int inorder_end, int preorder_Index) {
    if (inorder_start > inorder_end) {
        return NULL;
    }

    node* newNode = createNode(preorder[preorder_Index]);

    preorder_Index++;

    if (inorder_start == inorder_end) {
        return newNode;
    }

    int inIndex = findData(inorder, newNode->data);

    newNode->left = formBT(preorder, inorder, inorder_start, inIndex - 1, preorder_Index);
    newNode->right = formBT (preorder, inorder, inIndex + 1, inorder_end, preorder_Index);

    return newNode;
}

void inorder_traversal(node *root) {
    node *p = root;
    if(p == NULL) return;
    inorder_traversal(root->left);
    printf("%d ", p->data);
    inorder_traversal(root->right);
}

int main() {
    node *root = NULL;
    // int inorder[] = {9,3,15,20,7};
    // int preorder[] = {3,9,20,15,7};
    int inorder[] = {-1};
    int preorder[] = {-1};
    int size = sizeof(preorder) / sizeof(int);
    int i_left_index = 0, i_right_index = sizeof(inorder)/sizeof(inorder[0]) - 1;
    int i_curr = i_left_index;
    int p_left_index = 0, p_right_index = sizeof(preorder)/sizeof(preorder[0]) - 1;

    root = formBT(preorder, inorder, 0, size - 1, 0);
    inorder_traversal(root);

    return 0;
}