// #include<stdio.h>
// #include<stdlib.h>
#include<iostream>
#include"header.h"
using namespace std;

void listLeafNodes(node *root) {
    if(root == NULL) return;
    Enqueue(root);
    while (!isEmpty())
    {
        if ((FRONT->element)->left == NULL && (FRONT->element)->right == NULL) cout << (FRONT->element)->data << " ";
        if ((FRONT->element)->left != NULL) Enqueue((FRONT->element)->left);
        if ((FRONT->element)->right != NULL)Enqueue((FRONT->element)->right);
        Dequeue();
    }  
}

void listNonLeafNodes(node *root) {
    if(root == NULL) return;
    Enqueue(root);
    while (!isEmpty())
    {
        if (!((FRONT->element)->left == NULL && (FRONT->element)->right == NULL)) cout << (FRONT->element)->data << " ";
        if ((FRONT->element)->left != NULL) Enqueue((FRONT->element)->left);
        if ((FRONT->element)->right != NULL)Enqueue((FRONT->element)->right);
        Dequeue();
    }  
}

void printLevelofNodes(node *root) {
    cout << root->data << "->" << "L-0" << endl;
    if(root == NULL) return;
    Enqueue(root);
    while (!isEmpty())
    {
        
        if ((FRONT->element)->left != NULL) Enqueue((FRONT->element)->left);
        if ((FRONT->element)->right != NULL)Enqueue((FRONT->element)->right);
        Dequeue();
    }  
} 

int main() {
    node *root = NULL;
    root = CreateTree();
    listNonLeafNodes(root);

    return 0;
}