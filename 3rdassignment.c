#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
    char character;
    struct node *left, *right;
}node;

typedef struct stack_element {
    char symbol;
    struct stack_element *next;
}stack_element;

stack_element *TOP = NULL;

void *createStackelement(char symbol) {
    stack_element *p = NULL;
    p = (stack_element *)malloc(sizeof(stack_element));
    p->symbol = symbol;
    p->next = NULL;

    return p;
}

void push(char character) {
    stack_element *p = NULL;
    p = createStackelement(character);
    if (TOP == NULL) TOP = p;
    else {
        p->next = TOP;
        TOP = p;
    }
}

void pop() {
    stack_element *temp = TOP;
    TOP = TOP->next;
    free(temp);
}

node *createNode(char c) {
    node *p = NULL;
    p = (node *)malloc(sizeof(node));
    p->character = c;
    p->left = p->right = NULL;
    return p;
}

void array_to_stack(char arr[], int size) {
    node *ptr = NULL;
    for (int i = 0; i < size; i++)
    {
        push(arr[i]);
    }
}

void printStack() {
    stack_element *p = NULL;
    p = TOP;
    while(p != NULL) {
        printf("%c \n", p->symbol);
        p = p->next;
    }
}

int isEmpty() {
    if (TOP == NULL) return 1;
    else return 0;
}

// s = ["3","4","+","2","*","7","/"]

void inorder_traversal(node *root) {
    node *p = root;
    if(p == NULL) return;
    inorder_traversal(root->left);
    printf("%c ", p->character);
    inorder_traversal(root->right);
}

node *FindParent(node *root, node *child) {
    node *temp = root;
    if ((temp->left)->character == child->character || (temp->right)->character == child->character) return temp;
    
    if (temp->character < child->character) temp = FindParent(temp->right, child);
    else temp = FindParent(temp->left, child);
}

node *postfix_to_Btree(node *root) {
    if (root == NULL) {
        root = createNode(TOP->symbol);
        pop();
    }
    node *p = root;
    node *latest = NULL;
    while(!isEmpty()) {
        while ((TOP->symbol == 42) || (TOP->symbol == 43) || (TOP->symbol == 45) || (TOP->symbol == 47)) {
            p->left = createNode(TOP->symbol);
            p = p->left;
            latest = p;
            pop();
        }
        node *temp = NULL;
        while ((TOP->symbol != 42) && (TOP->symbol != 43) && (TOP->symbol != 45) && (TOP->symbol != 47)) {
            if((latest->left == NULL) && (latest->right == NULL)) {
                latest->left = createNode(TOP->symbol);
                pop();
                latest->right = createNode(TOP->symbol);
                pop();
                continue;
            }
            temp = FindParent(p, latest);
            temp->right = createNode(TOP->symbol);
            pop();
        }
        latest = FindParent(p, latest);
    }
    return root;
}

int main() {
    char character[7] = {'3','4','+','2','*','7','/'};
    array_to_stack(character, 7);
    node *root = NULL;
    root = postfix_to_Btree(root);
    inorder_traversal(root);

    return 0;
}