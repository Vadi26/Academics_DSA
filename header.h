// #include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

typedef struct node {
	int data;
	int Level;
	struct node *left;
	struct node *right;
}node;

int MaxLevel = 0;

node *createNode(int data) {
	node *p = (node *)malloc(sizeof(node));
	p->data = data;
	p->left = p->right = NULL;
	return p;
}

node *Insert(node *root, int data);

void PreorderDFSTraversal(node *root) {
    if (root == NULL) return;
    cout << root->data << " ";
    PreorderDFSTraversal(root->left);
    PreorderDFSTraversal(root->right);
}

node *findMin(node *root) {
	node *p = NULL;
	p = root;
	while (p->left != NULL) p = p->left;
	// cout << p->data << " ";
	// printf(" %d \n", p->data);
	return p;
}

node *findMax(node *root);

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

typedef struct ele
{
    node *element;
    struct ele *next;
}ele;

ele *top = NULL;

int isStackEmpty() {
    if (top == NULL) return 1;
    else return 0;
}

// \brief For stack implementation
void push(node *element) {
    ele *p = NULL;
    p = (ele *)malloc(sizeof(ele));
    p->element = element;
    p->next = NULL;
    if (isStackEmpty()) top = p;
    else{
        p->next = top;
        top = p;
    }
}

// \brief For stack implementation
void pop() {
    ele *temp = top;
    top = top->next;
    free(temp);
}

ele *FRONT = NULL, *REAR = NULL;

// \brief For queue implementation
void Enqueue(node *element) {
	ele *p = NULL;
    p = new ele;
    p->element = element;
    p->next = NULL;
    if (FRONT == NULL) FRONT = REAR = p;
    else {
        REAR->next = p;
        REAR = p;
    }
}

int isEmpty() {
    if (FRONT == NULL) return 1;
    else return 0;
}

void Dequeue() {
	ele *temp = FRONT;
    if (FRONT == REAR) {
        FRONT = REAR = NULL;
        delete temp;
    }
    else {
        FRONT = FRONT->next;
        delete temp;
    }
}

void displayStack() {
    ele *temp = top;
    while (temp != NULL)
    {
        cout << (temp->element)->data << " ";
        temp = temp->next;
    }
}

void preorderTraversalwithoutrecursion(node *root);

void LevelOrderTraversal(node *root) {
	if(root == NULL) return;
    Enqueue(root);
    while (!isEmpty())
    {
        cout << (FRONT->element)->data << " ";
        if ((FRONT->element)->left != NULL) Enqueue((FRONT->element)->left);
        if ((FRONT->element)->right != NULL)Enqueue((FRONT->element)->right);
        Dequeue();
    }  
}

node* SearchNode(node *root, int data);

void listLeafNodes(node *root);

void listNonLeafNodes(node *root);

void printLevelofNodes(node *root);

node *FindParent(node *root, node *child) {
    node *temp = root;
    if ((temp->left)->data == child->data || (temp->right)->data == child->data) return temp;
    
    if (temp->data < child->data) temp = FindParent(temp->right, child);
    else temp = FindParent(temp->left, child);
}