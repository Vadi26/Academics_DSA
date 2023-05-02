#include<stdio.h>
#include<stdlib.h>

int max(int a, int b) {
    if (a > b) return a;
    else return b;
}

typedef struct node {
    int data;
    struct node *left, *right;
    int height;
}node;

int getHeight(node *tree_node) {
    if (tree_node == NULL) return 0;
    else return tree_node->height;
}

node *createNode(int data) {
	node *p = (node *)malloc(sizeof(node));
	p->data = data;
	p->left = p->right = NULL;
    p->height = 1;
	return p;
}

int getBalanceFactor(node *tree_node) {
    if (tree_node == NULL) return 0;
    return getHeight(tree_node->left) - getHeight(tree_node->right);
}

node *rightRotate(node *y) {
    node *x = y->left;
    node *x_rightchild = x->right;

    x->right = y;
    y->left = x_rightchild;

    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;

    return x;
}

node *leftRotate(node *x) {
    node *y = x->right;
    node *y_leftchild = y->left;

    y->left = x;
    x->right = y_leftchild;

    y->height = max(getHeight(y->right), getHeight(y->left)) + 1;
    x->height = max(getHeight(x->right), getHeight(x->left)) + 1;

    return y;
}

node *insert(node *root, int data) {
    if (root == NULL) return createNode(data);

    if(data < root->data) root->left = insert(root->left, data);
    else root->right = insert(root->right, data);

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bf = getBalanceFactor(root);

    // Right Right
    if (bf > 1 && data < root->left->data) return root = rightRotate(root);

    // Left Left
    if (bf < -1 && data > root->right->data) return root = leftRotate(root);

    // Left Right
    if (bf > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left
    if (bf < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder_traversal (node *root) {
    if (root == NULL) return;
    inorder_traversal(root->left);
    printf("%d ", root->data);
    inorder_traversal(root->right);
}

node *findNode(node *root, int data) {
    node *temp = root;
    if (temp->data == data) return temp;

    if(temp->data < data) temp = findNode(temp->right, data);
    else temp = findNode(temp->left, data);

    return temp;
}

node *FindParent(node *root, node *child) {
    node *temp = root;
    if ((temp->left)->data == child->data || (temp->right)->data == child->data) return temp;
    
    if (temp->data < child->data) temp = FindParent(temp->right, child);
    else temp = FindParent(temp->left, child);
}

void inorder_traversal (node *root) {
    if (root == NULL) return;
    inorder_traversal(root->left);
    printf("%d{%d} ", root->data, root->height - 1);
    inorder_traversal(root->right);
}

node *initAVL(int data) {
    node *root = NULL;
    root = createNode(data);
    return root;
}

int main() {
    node *root = NULL;
    int x, y, z;
    while(1) {
        printf("\nEnter the number you want to insert : ");
        scanf("%d", &x);
        root = insert(root, x);
        printf("\nDo you want to insert another element?(1-yes, 0-no)");
        scanf("%d", &y);
        if(y == 1) continue;
        else {
            printf("Do you want to display the tree?(1-yes, 0-no)");
            scanf("%d", &z);
            if (z == 1) inorder_traversal(root);
            else break;
        }
    }
    printf("\n");
    return 0;
}