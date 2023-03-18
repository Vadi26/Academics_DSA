#include<iostream>
#include<stdlib.h>
#include"header.h"
using namespace std;

// Inorder : 4 2 5 1 6 3 7
// Preorder : 1 2 4 5 3 6 7

// \brief Finds the provided data and returns its index. returns -1 if not found
int findData(int arr[], int data) { 
    for (int i = 0; i < sizeof(arr) - 1; i++)
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

node *createBT(node *root, int inorder[], int preorder[], int pcurr) {
    if(pcurr < sizeof(preorder) - 1) {
        int icurr;
        if(root == NULL) {
            root = createNode(preorder[pcurr]);
            icurr = findData(inorder, preorder[pcurr]);
            pcurr++;
        }
        if(findData(inorder, preorder[pcurr]) < icurr){
            root->left = createBT(root->left, inorder, preorder, pcurr);
            // return root->left;
        }
        if(findData(inorder, preorder[pcurr]) > icurr) {
            root->right = createBT(root->right, inorder, preorder, pcurr);
            // return root->right;
        }
    }
    return root;
}

void InorderTraversal(node *root) {
    if (root == NULL) return;
    InorderTraversal(root->left);
    cout << root->data << " ";
    InorderTraversal(root->right);
}

int main() {
    node *root = NULL;
    int inorder[] = {4,2,5,1,3};
    int preorder[] = {1,2,4,5,3};

    root = createBT(root, inorder, preorder, 0);
    InorderTraversal(root);

    return 0;
}