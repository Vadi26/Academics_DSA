#include<iostream>
#include<stdlib.h>
#include"header.h"
using namespace std;

// Inorder : 9 3 15 20 7
// Preorder : 3 9 20 15 7

// \brief Finds the provided data and returns its index. returns -1 if not found
int findData(int arr[], int data, int size) { 
    int i;
    for (i = 0; i < size - 1; i++)
    {
        if (arr[i] == data) return i;
    }
    return -1;
}
/*
There is an index pointer which keeps track of index of the preorder array. 
1st element of preorder is the God root node of the tree.
We will locate that element in inorder array and get that index.
Then we will divide the inorder array into left and right parts at the obtained index.
Then we will increase the preorder ka index waala pointer.
Locate that element in the inorder array.
If the obtained index lies in the left part of the array, then that index waala element becomes the next node and will join the God root as its left child.
Else it will join as right child of the God root node.
*/

node *formBT(node *root, int inorder[], int preorder[], int pcurr, int inorder_size, int preorder_size) {
    if(pcurr == 0) {
        root = createNode(preorder[pcurr]);
        pcurr++;
    }

    if(root == NULL) {
        root = createNode(preorder[pcurr]);
        return root;
    }

    while(pcurr < preorder_size){
        int i = findData(inorder, preorder[pcurr], inorder_size);
        int left_size, right_size;
        left_size = i;
        right_size = inorder_size - i - 1;
        int *left_Tree = new int[left_size], *right_Tree = new int[right_size];
        for(i = 0; i < left_size; i++) left_Tree[i] = inorder[i];
        for(i = left_size + 1; i < inorder_size; i++) right_Tree[i - left_size - 1] = inorder[i];
        if(findData(left_Tree, preorder[pcurr], left_size) != -1) {
            root->left = formBT(root->left, left_Tree, preorder, pcurr, left_size, preorder_size);
            pcurr++;
        }

        if(findData(right_Tree, preorder[pcurr], right_size) != -1) {
            root->right = formBT(root->right, right_Tree, preorder, pcurr, right_size, preorder_size);
            pcurr++;
        }
    }
    // root = createNode(preorder[pcurr]);
    // int i = findData(inorder, preorder[pcurr]);
    // int left_size = i;
    // int right_size = size - i - 1;
    // int left_Tree[left_size], right_Tree[right_size];
    // for (int j = 0; j < left_size; j++) {
    //     left_Tree[j] = inorder[j];
    // }
    // for (int j = i + 1; j < size; j++) {
    //     right_Tree[j - i - 1] = inorder[j];
    // }
    // root->left = formBT(root->left, left_Tree, preorder, pcurr + 1, left_size);
    // root->right = formBT(root->right, right_Tree, preorder, pcurr + left_size + 1, right_size);
    return root;
}

// node *createBT(node *root, int inorder[], int preorder[], int pcurr) {
//     if(pcurr < sizeof(preorder) - 1) {
//         int icurr;
//         if(root == NULL) {
//             root = createNode(preorder[pcurr]);
//             icurr = findData(inorder, preorder[pcurr]);
//             pcurr++;
//         }
//         if(findData(inorder, preorder[pcurr]) < icurr){
//             root->left = createBT(root->left, inorder, preorder, pcurr);
//             // return root->left;
//         }
//         if(findData(inorder, preorder[pcurr]) > icurr) {
//             root->right = createBT(root->right, inorder, preorder, pcurr);
//             // return root->right;
//         }
//     }
//     return root;
// }

void InorderTraversal(node *root) {
    if (root == NULL) return;
    InorderTraversal(root->left);
    cout << root->data << " ";
    InorderTraversal(root->right);
}

int main() {
    node *root = NULL;
    int inorder[] = {9,3,15,20,7};
    int preorder[] = {3,9,20,15,7};
    int size = sizeof(inorder) / sizeof(inorder[0]);

    root = formBT(root, inorder, preorder, 0, size, size);
    InorderTraversal(root);

    return 0;
}