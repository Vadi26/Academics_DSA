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

// heapify function for insert
node *HEAPIFY(node *root) {
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
        root = HEAPIFY(root);
        return;
    }
}

// heapify function for heap sort
void heapify(int arr[], int n, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != index) {
        swap(&arr[index], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    // Build max heap
    for (int i = n - 1; i >= 0; i--) heapify(arr, n, i);
    
    // Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
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
    insert(root, 15);
    insert(root, 60);
    display_heap(root);

    heapSort(root->tree, 8);
    printf("\n");
    display_heap(root);

    return 0;
}