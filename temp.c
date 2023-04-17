#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *left, *right;
}node;

// Stack implementation for building the expression tree
typedef struct Stack {
    int top;
    node *items[100];
} Stack;

void push(Stack *stack, node *item) {
    if (stack->top == 99) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack->items[++stack->top] = item;
}

node* pop(Stack *stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->items[stack->top--];
}

// Function to build the expression tree from postfix tokens
node* ExpressionTree(char postfix[], int length) {
    Stack stack;
    stack.top = -1;

    for (int i = 0; i < length; i++) {
        char token = postfix[i];

        if (token >= '0' && token <= '9') {
            node *newnode = (node*) malloc(sizeof(node));
            newnode->data = token;
            newnode->left = newnode->right = NULL;
            push(&stack, newnode);
        } else {
            node *newnode = (node*) malloc(sizeof(node));
            newnode->data = token;
            newnode->right = pop(&stack);
            newnode->left = pop(&stack);
            push(&stack, newnode);
        }
    }

    return pop(&stack);
}

// Function to evaluate the expression tree
int evaluate(node *root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return root->data - '0';
    }

    int left = evaluate(root->left);
    int right = evaluate(root->right);

    switch (root->data) {
        case '+': return left + right;
        case '-': return left - right;
        case '*': return left * right;
        case '/': return left / right;
        case '%': return left % right;
        default: return 0;
    }
}

void inorder_traversal(node *root) {
    node *p = root;
    if(p == NULL) return;
    inorder_traversal(root->left);
    printf("%d ", p->data);
    inorder_traversal(root->right);
}

// Main function
int main() {
    char postfix[] = {'4', '5', '7', '2', '+', '-', '*'};
    int length = strlen(postfix);

    node *root = ExpressionTree(postfix, length);
    inorder_traversal(root);

    printf("\n The result is %d\n", evaluate(root));

    return 0;
}
