#include<iostream>
#include<stdlib.h>
#include"header.h"
using namespace std;



node *deleteNode(node *root, int data) {
    node *temp = SearchNode(root, data);
    node *parent = FindParent(root, temp);
    if(temp->left == NULL && temp->right == NULL) {
        if(parent->left == temp) parent->left = NULL;
        else parent->right = NULL;
        free(temp);
        return root;
    }
    else if(temp->left == NULL ^ temp->right == NULL) {
        if(parent->left == temp) {
            if(temp->left != NULL) {
                parent->left = temp->left;
                free(temp);
            }
            else {
                parent->left = temp->right;
                free(temp);
            }
        }
        else {
            if(temp->left != NULL) {
                parent->right = temp->left;
                free(temp);
            }
            else {
                parent->right = temp->right;
                free(temp);
            }
        }
    }
    return root;
}

int main() {
    node *root = NULL;
    root = CreateTree();
    cout << "Level order traversal : \n" << endl;
    LevelOrderTraversal(root);
    root = deleteNode(root, 14);
    cout << "After deletion : \n" << endl;
    LevelOrderTraversal(root);
    cout << endl;
	/* 
                                  20
                            16          24
                        12      18  21      26
                    10      14          23
                                    22                                                 
    */
    return 0;
}