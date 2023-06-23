#include<iostream>
// #include<stdio.h>
#include<stdlib.h>
using namespace std;

typedef struct Node{
	int data;
	struct Node *left, *right;
}node;

node* CreateNode(int data){
    node *p;
    p = (node *)malloc(sizeof(node));
    p->left = p->right = NULL;
    p->data = data;

    return p;
}

node* Insert(node *root, int data){
    node *temp = NULL;
    temp = root;
    if (root == NULL)
    {
        root = CreateNode(data);
        return root;
    }
    else{
        if (root->data < data)
        {
            root->right = Insert(root->right, data);
        }
        else{
            root->left = Insert(root->left, data);
        }
    }

    return root;
}

node *CreateTree(){
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

    /* 
                                  20
                            16          24
                        12      18  21      26
                    10      14          23
                                    22                                                 
    */

    return root;
}

/* \brief It will return a pointer to the node which contains the given data */
node* SearchNode(node *root, int data){
    if (root == NULL) return 0;
	node *temp = root;
    if (temp->data == data)
    {
        return temp;
    }
    else if (temp->data < data)
    {
        temp = SearchNode(temp->right, data);
    }
    else{
        temp = SearchNode(temp->left, data);
    }

    return temp;
}

/* \brief Returns the Greatest element of the tree */
node *FindMax(node *root){
    if (root == NULL) return NULL;
    node *p;
    p = root;
    while (p->right != NULL)
    {
        p = p->right;
    }
    return p;
}

/* \brief Returns the Least element of the tree */
node *FindMin(node *root){
    if (root == NULL) return NULL;
    node *p;
    p = root;
    while (p->left != NULL)
    {
        p = p->left;
    }
    return p;
}

void PreorderTraversal(node *root) {
    if (root == NULL) return;
    cout << root->data << " ";
    PreorderTraversal(root->left);
    PreorderTraversal(root->right);
}

void InorderTraversal(node *root) {
    if (root == NULL) return;
    InorderTraversal(root->left);
    cout << root->data << " ";
    InorderTraversal(root->right);
}

void PostorderTraversal(node *root) {
    if (root == NULL) return;
    PostorderTraversal(root->left);
    PostorderTraversal(root->right);
    cout << root->data << " ";
}