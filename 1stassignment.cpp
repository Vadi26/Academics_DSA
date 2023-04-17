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

// node *formBT(node *root, int inorder[], int preorder[], int i_left_index, int i_right_index, int p_left_index, int p_right_index) {
//     if(p_left_index == 0) root = createNode(preorder[p_left_index]);
    
//     if(i_left_index == i_right_index){
//         root = createNode(preorder[p_left_index]);
//         return root;
//     }

//     while(p_left_index <= p_right_index) {
//         int i = findData(inorder, preorder[p_left_index], 5);
//         root->left = formBT(root->left, inorder, preorder, 0, i, p_left_index++, p_right_index);
//         p_left_index++;
//         root->right = formBT(root->right, inorder, preorder, i + 1, 5 - i, p_left_index, p_right_index);
//         p_left_index++;
//     }

//     return root;
// }

node* buildTree(int preorder[], int inorder[], int start, int end, int *preIndex) {
    if (start > end) {
        return NULL;
    }

    node* newNode = createNode(preorder[*preIndex]);

    (*preIndex)++;

    if (start == end) {
        return newNode;
    }

    int inIndex = findData(inorder, newNode->data);

    newNode->left = buildTree(preorder, inorder, start, inIndex - 1, preIndex);
    newNode->right = buildTree(preorder, inorder, inIndex + 1, end, preIndex);

    return newNode;
}

// Function to construct a binary tree from its preorder and inorder traversals
node* buildTreeFromTraversal(int preorder[], int inorder[], int size) {
    int preIndex = 0;
    return buildTree(preorder, inorder, 0, size - 1, &preIndex);
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

    root = buildTreeFromTraversal(preorder, inorder, size);
    inorder_traversal(root);

    return 0;
}