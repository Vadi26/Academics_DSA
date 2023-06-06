#include<stdio.h>
#include<stdlib.h>

/*
for 0th index of array as NULL and we start inserting from 1st index :
Parent : i/2
Leftchild : i*2
Rightchild : i*2 + 1

for inserting elements right from the 0th index : 
Parent : (i - 2)/2
Leftchild : i*2 + 1
Rightchild : i*2 + 2    
*/

typedef struct node{
    int *tree;
    int latest_index;
}node;

node *init_heap(node *root) {
    root = malloc(sizeof(node));
    if (root == NULL) {
        printf("Memory allocation failed!");
        return NULL;
    }
    root->tree = NULL;
    root->latest_index = 0;
    return root;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

node *Heapify(node *root, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < root->latest_index - 1 && root->tree[left] > root->tree[largest])
    largest = left;

    if (right < root->latest_index - 1 && root->tree[right] > root->tree[largest])
    largest = right;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
        swap(&root->tree[i], &root->tree[largest]);
        Heapify(root, largest);
    }
}

node *heapify(node *root) {
    int current_index = root->latest_index - 1;
    int parent_index = (current_index - 1)/2;
    while ((root->tree[current_index] > root->tree[parent_index]) && parent_index >= 0) {
        swap(&root->tree[current_index], &root->tree[parent_index]);
        current_index = parent_index;
        parent_index = (parent_index - 1)/2;
    }

    return root;
}

// For max heap
void insert(node *root, int data) {
    if (root->tree == NULL) {
        root->tree = (int *)malloc(sizeof(int));
        root->tree[root->latest_index] = data;
        root->latest_index++;
        return;
    }
    else{
        root->tree = (int *)realloc(root->tree, (root->latest_index + 1)*sizeof(int));
        root->tree[root->latest_index] = data;
        root->latest_index++;
        root = Heapify(root, 0);
        return;
    }
}

int findIndex(node *root, int data) {
    for (int i = 0; i < root->latest_index; i++)
    {
        if (root->tree[i] == data) return i;
    }
}

void deletenode(node *root, int data){
    int index = findIndex(root, data);
    if (index == 0) {
        swap(&root->tree[0], &root->tree[root->latest_index - 1]);
        root->latest_index--;
        root = Heapify(root, 0);
        return;
    }
    else {
        swap(&root->tree[index], &root->tree[root->latest_index - 1]);
        root->latest_index--;
        
        // Check if heap property is violated
        if (root->tree[index] > root->tree[(index - 1)/2]) {
            root = Heapify(root, 0);
        }
    }
}


void display_heap(node *root) {
    for (int i = 0; i < root->latest_index; i++) {
        printf("%d ", root->tree[i]);
    }
}

int main() {
    node *root = NULL;
    root = init_heap(root);
    insert(root, 50);
    insert(root, 30);
    insert(root, 40);
    insert(root, 10);
    insert(root, 5);
    insert(root, 20);
    insert(root, 30);
    insert(root, 60);
    insert(root, 15);
    insert(root, 6);
    display_heap(root);
    printf("\n");
    deletenode(root, 30);
    display_heap(root);

    return 0;
}