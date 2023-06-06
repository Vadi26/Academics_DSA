#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

void BFS(Graph* graph, int startVertex) {
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    int i;
    for (i = 0; i < graph->numVertices; i++) {
        visited[i] = false;
    }

    visited[startVertex] = true;

    printf("BFS Traversal starting from vertex %d: ", startVertex);

    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0;
    int rear = 0;

    queue[rear++] = startVertex;

    while (front != rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node* currentNode = graph->array[currentVertex];
        while (currentNode != NULL) {
            int adjacentVertex = currentNode->vertex;
            if (!visited[adjacentVertex]) {
                visited[adjacentVertex] = true;
                queue[rear++] = adjacentVertex;
            }
            currentNode = currentNode->next;
        }
    }

    printf("\n");

    free(visited);
    free(queue);
}

void DFSUtil(Graph* graph, int vertex, bool* visited) {
    visited[vertex] = true;
    printf("%d ", vertex);

    Node* currentNode = graph->array[vertex];
    while (currentNode != NULL) {
        int adjacentVertex = currentNode->vertex;
        if (!visited[adjacentVertex]) {
            DFSUtil(graph, adjacentVertex, visited);
        }
        currentNode = currentNode->next;
    }
}

void DFS(Graph* graph, int startVertex) {
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    int i;
    for (i = 0; i < graph->numVertices; i++) {
        visited[i] = false;
    }

    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFSUtil(graph, startVertex, visited);
    printf("\n");

    free(visited);
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

    int startVertex = 0;

    BFS(graph, startVertex);

    DFS(graph, startVertex);

    return 0;
}

