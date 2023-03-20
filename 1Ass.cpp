// #include<stdio.h>
// #include<stdlib.h>
#include<iostream>
#include"header.h"
using namespace std;

node *findMax(node *root) {
	node *p = NULL;
	p = root;
	while (p->right != NULL) p = p->right;
	// cout << p->data << " ";
	// printf(" %d \n", p->data);
	return p;
}
node *SearchData(node *root, int data) {
	if(root == NULL) return NULL;
    Enqueue(root);
    while ((FRONT->element)->data != data)
    {
        if ((FRONT->element)->left != NULL) Enqueue((FRONT->element)->left);
        if ((FRONT->element)->right != NULL)Enqueue((FRONT->element)->right);
        Dequeue();
    }
	return FRONT->element;
}

void preorderTraversalwithoutrecursion(node *root) {
	if (root == NULL) return;
	node *temp = root;
	push(temp);
	// while (!isStackEmpty()) {
	// 	cout << (top->element)->data << " ";
	// 	pop();
	// 	push(root->left);
	// 	push(root->right);
	// }
	while(temp->left != NULL) {
		temp = temp->left;
		push(temp);
	}
	if (temp->right != NULL) {
		push(temp->right);
	}
}

void printTree(node *root, int space) {
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

int main() {
	node *root = NULL;
	root = CreateTree();
	
	preorderTraversalwithoutrecursion(root);

	/* 
                                  20
                            16          24
                        12      18  21      26
                    10      14          23
                                    22                                                 
    */

	return 0;
}