#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
    char character;
    struct node *left, *right;
}node;

typedef struct stack_element {
    node *tree_node;
    struct stack_element *next;
}stack_element;

stack_element *TOP = NULL;

void *createStackelement(node *tree_node) {
    stack_element *p = NULL;
    p = (stack_element *)malloc(sizeof(stack_element));
    p->tree_node = tree_node;
    p->next = NULL;

    return p;
}

void push(node *tree_node) {
    stack_element *p = NULL;
    p = createStackelement(tree_node);
    if (TOP == NULL) TOP = p;
    else {
        p->next = TOP;
        TOP = p;
    }
}

node *pop() {
    stack_element *temp = TOP;
    TOP = TOP->next;
    return temp->tree_node;
}

node *createNode(char c) {
    node *p = NULL;
    p = (node *)malloc(sizeof(node));
    p->character = c;
    p->left = p->right = NULL;
    return p;
}

void printStack() {
    stack_element *p = NULL;
    p = TOP;
    while(p != NULL) {
        printf("%c \n", (p->tree_node)->character);
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

node *postfix_to_Btree(node *root, char character_array[], int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        char token = character_array[i];
        if(token >= '0' && token <= '9') {
            node *ptr = createNode(token);
            push(ptr);
        }
        else {
            node *ptr = createNode(token);
            ptr->right = pop();
            ptr->left = pop();
            push(ptr);
        }
    }
    root = pop();
    return root;
}

int eval(node *root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return root->character - '0';
    }

    int left = eval(root->left);
    int right = eval(root->right);

    switch (root->character) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
        case '%': return left % right;
        default: return 0;
    }
}

int main() {
    char character[7] = {'4','5','2','7','+','-','*'};
    node *root = NULL;
    root = postfix_to_Btree(root, character, 7);
    inorder_traversal(root);
    printf("\n  %d    \n", eval(root));

    return 0;
}