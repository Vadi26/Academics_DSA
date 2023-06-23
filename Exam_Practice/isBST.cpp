#include<iostream>
#include<stdlib.h>
#include"header.h"
using namespace std;

bool IsBstUtil(node *root, int minValue, int maxValue) {
    if (root == NULL) return true;

    if (root->data > minValue && root->data < maxValue && IsBstUtil(root->left, minValue, root->data) && IsBstUtil(root->right, root->data, maxValue)) {
        return true;
    }
    else return false;
}

bool IsBST(node *root){
    return IsBstUtil(root, -999999999, 999999999);
}

int main(){
    node *root = NULL;

    root = Insert(root, 20);
    root = Insert(root, 16);
    root = Insert(root, 24);
    root = Insert(root, 18);
    root = Insert(root, 12);
    root = Insert(root, 14);
    root = Insert(root, 10);
    root = Insert(root, 26);
    root = Insert(root, 21);
    root = Insert(root, 23);
    root = Insert(root, 22);

    bool x = IsBST(root);
    cout << x << endl;
    // printf("%d ", IsBST(root));
    /* 
                                  20
                            16          24
                        12      18  21      26
                    10      14          23
                                    22                                                 
    */
    free(root);
    return 0;
}