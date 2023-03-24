#include<iostream>
#include<stdlib.h>
#include"header.h"
using namespace std;

// Inorder : 9 3 15 20 7
// Preorder : 3 9 20 15 7

int findData(int arr[], int data, int size) { 
    int i = 0;
    while (arr[i] != data)
    {
        i++;
    }
    return i;
}

node *formBT(node *root, int inorder[], int preorder[],int size, int i_left_index, int i_right_index, int p_left_index, int p_right_index) {
    // if(p_left_index == 0) root = createNode(preorder[p_left_index]);
    
    if(p_left_index == p_right_index){
        root = createNode(preorder[p_left_index]);
        return root;
    }

    while(p_left_index <= p_right_index) {
        int i = findData(inorder, preorder[p_left_index++], size);
        root->left = formBT(root->left, inorder, preorder, size, i, i, p_left_index, p_right_index);
        p_left_index++;
        root->right = formBT(root->right, inorder, preorder, size, i + 1, size - i, p_left_index, p_right_index);
        p_left_index++;
    }

    return root;
}

int main() {
    node *root = NULL;
    int inorder[] = {9,3,15,20,7};
    int preorder[] = {3,9,20,15,7};
    int size = sizeof(preorder) / sizeof(int);
    int i_left_index = 0, i_right_index = sizeof(inorder)/sizeof(inorder[0]) - 1;
    int i_curr = i_left_index;
    int p_left_index = 0, p_right_index = sizeof(preorder)/sizeof(preorder[0]) - 1;

    cout << findData(inorder, 20, size) << endl;

    formBT(root, inorder, preorder, size, i_left_index, i_right_index, p_left_index, p_right_index);

    return 0;
}