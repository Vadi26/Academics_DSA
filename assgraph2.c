#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    Node** array;
    int numVertices;
} Graph;

Node* createNode(int vertex, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    graph->array = (Node**)malloc(numVertices * sizeof(Node*));
    int i;
    for (i = 0; i < numVertices; i++) {
        graph->array[i] = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src];
    graph->array[src] = newNode;

    newNode = createNode(src, weight);
    newNode->next = graph->array[dest];
    graph->array[dest] = newNode;
}

void displayGraph(Graph* graph) {
    int i;
    for (i = 0; i < graph->numVertices; i++) {
        Node* currentNode = graph->array[i];
        printf("Vertex %d: ", i);
        while (currentNode != NULL) {
            printf("(%d, %d) ", currentNode->vertex, currentNode->weight);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}

int getMinKey(int* key, bool* mstSet, int numVertices) {
    int min = INT_MAX;
    int minIndex, v;
    for (v = 0; v < numVertices; v++) {
        if (mstSet[v] == false && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void printMST(int* parent, int** graph, int numVertices) {
    printf("Edge \tWeight\n");
    int i;
    for (i = 1; i < numVertices; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}

void primMST(Graph* graph) {
    int numVertices = graph->numVertices;
    int** adjacencyMatrix = (int**)malloc(numVertices * sizeof(int*));
    int i, j;
    for (i = 0; i < numVertices; i++) {
        adjacencyMatrix[i] = (int*)malloc(numVertices * sizeof(int));
    }

    
    for (i = 0; i < numVertices; i++) {
        Node* currentNode = graph->array[i];
        while (currentNode != NULL) {
            adjacencyMatrix[i][currentNode->vertex] = currentNode->weight;
            adjacencyMatrix[currentNode->vertex][i] = currentNode->weight;
            currentNode = currentNode->next;
        }
    }

    int* parent = (int*)malloc(numVertices * sizeof(int));
    int* key = (int*)malloc(numVertices * sizeof(int));
    bool* mstSet = (bool*)malloc(numVertices * sizeof(bool));

    for (i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        mstSet[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    int count;
    for (count = 0; count < numVertices - 1; count++) {
        int u = getMinKey(key, mstSet, numVertices);
        mstSet[u] = true;

        for (j = 0; j < numVertices; j++) {
            if (adjacencyMatrix[u][j] && mstSet[j] == false && adjacencyMatrix[u][j] < key[j]) {
                parent[j] = u;
                key[j] = adjacencyMatrix[u][j];
            }
        }
    }

    printMST(parent, adjacencyMatrix, numVertices);

    for (i = 0; i < numVertices; i++) {
        free(adjacencyMatrix[i]);
    }
    free(adjacencyMatrix);
    free(parent);
    free(key);
    free(mstSet);
}

int main() {
    int numVertices = 9;
    Graph* graph = createGraph(numVertices);

    addEdge(graph, 0, 1, 2);
    addEdge(graph, 0, 2, 4);
    addEdge(graph, 0, 3, 6);
    addEdge(graph, 3, 7, 4);
    addEdge(graph, 1, 2, 5);
    addEdge(graph, 2, 3, 1);
    addEdge(graph, 3, 5, 3);
    addEdge(graph, 4, 5, 1);
    addEdge(graph, 4, 2, 2);
    addEdge(graph, 4, 8, 3);
    addEdge(graph, 4, 6, 5);
    addEdge(graph, 5, 6, 4);

    printf("Graph:\n");
    displayGraph(graph);
    printf("\n");

    printf("Minimum Spanning Tree:\n");
    primMST(graph);

    return 0;
}

