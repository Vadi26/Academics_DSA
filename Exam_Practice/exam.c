#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int data;
    struct node *left, *right;
    int height;
}node;

// returns pointer to the node which contains the data
node *findData(node *root, int data) {
    if (root == NULL) return NULL;
    node *temp = root;
    if (temp->data == data) return temp;
    else if (temp->data < data) temp = findData(temp->right, data);
    else temp = findData(temp->left, data);

    return temp;
}

node *findParent(node *root, node *child_node) {
    if (root == NULL) return NULL;
    node *temp = root;
    if (temp->left == child_node || temp->right == child_node) return temp;
    else if (temp->data < child_node->data) temp = findParent(temp->right, child_node);
    else temp = findParent(temp->left, child_node);

    return temp;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getHeight(node *tree_node) {
    if (tree_node == NULL) return 0;
    else return tree_node->height;
}

int getBalanceFactor(node *tree_node) {
    if (tree_node == NULL) return 0;
    else return getHeight(tree_node->left) - getHeight(tree_node->right);
}

node *createNode(int data) {
    node *p = NULL;
    p = (node *)malloc(sizeof(node));
    p->data = data;
    p->height = 1;
    p->left = p->right = NULL;
    return p;
}

node *leftRotate(node *y) {
    node *x = y->right;
    node *x_leftchild = x->left;

    x->left = y;
    y->right = x_leftchild;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return x;
}

node *rightRotate(node *y) {
    node *x = y->left;
    node *x_rightchild = x->right;

    x->right = y;
    y->left = x_rightchild;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return x;
}

node *insert(node *root, int data) {
    if (root == NULL) return createNode(data);

    if (data < root->data) root->left = createNode(data);
    else root->right = createNode(data);

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int bf = getBalanceFactor(root);

    // Right Right condition
    if (bf < -1 && data > root->right->data) root = leftRotate(root);

    // Left Left condition
    if (bf > 1 && data < root->left->data) root = rightRotate(root);

    // Left Right condition
    if (bf > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    }

    // Right Left condition
    if (bf < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }

    return root;
}

void inorder(node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d{%d}", root->data, root->height);
    inorder(root->right);
}

node *findMin(node *root) {
	node *p = NULL;
	p = root;
	while (p->left != NULL) p = p->left;
	return p;
}

node *delete_node(node *root, int data) {
    if (root == NULL) return root;
    
    if (data < root->data) root->left = delete_node(root->left, data);
    else if (data > root->data) root->right = delete_node(root->right, data);

    else {
        if((root->left == NULL) || (root->right == NULL)) {
            node *temp = root->left ? root->left : root->right;
            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            // One child case
            else {
                root = temp;
                free(temp);
            }
        }
        else {
            node *temp = findMin(root->right);
            root->data = temp->data;
            root->right = delete_node(root->right, temp->data);
        }
    }

    // Update height of current node 
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // check for imbalance
    int bf = getBalanceFactor(root);

    // Right Right condition
    if (bf < -1 && data > root->right->data) root = leftRotate(root);

    // Left Left condition
    if (bf > 1 && data < root->left->data) root = rightRotate(root);

    // Left Right condition
    if (bf > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        root = rightRotate(root);
    }

    // Right Left condition
    if (bf < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        root = leftRotate(root);
    }

    return root;
}

int main() {
    node *root = NULL;
    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 3);
    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 6);

    inorder(root);

    root = delete_node(root, 4);

    printf("\n");
    inorder(root);

    return 0;
}