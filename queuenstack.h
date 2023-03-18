// #include<stdio.h>
// #include<stdlib.h>
#include<iostream>
using namespace std;
// #include"header.h"

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
}node;

typedef struct ele
{
    node *element;
    struct ele *next;
}ele;

ele *top = NULL;

int isEmpty() {
    if (top == NULL) return 1;
    else return 0;
}

void push(node *element) {
    ele *p = NULL;
    p = (ele *)malloc(sizeof(ele));
    p->element = element;
    p->next = NULL;
    if (isEmpty) top = p;
    else{
        p->next = top;
        top = p;
    }
}

int pop() {
    ele *temp = top;
    int i = (temp->element)->data;
    top = top->next;
    free(temp);

    return i;
}

void displayStack() {
    ele *temp = top;
    while (temp != NULL)
    {
        cout << (temp->element)->data << " ";
        temp = temp->next;
    }
}