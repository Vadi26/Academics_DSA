#include<stdio.h>
#include<stdlib.h>

typedef struct node {
    int vertex;
    int weight;
    struct node *next;
}node;

typedef struct Graph {
    int num_of_vertices;
    node **adjLists;
}Graph;

node *FRONT = NULL, *REAR = NULL;

node *createNode (int data) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->vertex = data;
    newNode->next = NULL;
    newNode->weight = 0;
    return newNode;
}

Graph *createGraph(int vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->num_of_vertices = vertices;
    graph->adjLists = malloc(sizeof(node *) * vertices);
    for (int i = 0; i < vertices; i++) graph->adjLists[i] = NULL;
    
    return graph;
}

void addEdge(Graph *graph, int source, int destination, int weight) {
    node *newNode = createNode(destination);
    newNode->weight = weight;
    newNode->next = graph->adjLists[source];
    graph->adjLists[source] = newNode;

    newNode = createNode(source);
    newNode->weight = weight;
    newNode->next = graph->adjLists[destination];
    graph->adjLists[destination] = newNode;
}

void printGraph(Graph *graph) {
    for (int v = 0; v < graph->num_of_vertices; v++) {
        node *temp = graph->adjLists[v];
        printf("\n Vertex : %d \n", v);
        while(temp) {
            printf("%d(%d) -> ", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

void BFS(Graph* graph, int startVertex) {
    int* visited = (int *)malloc(graph->num_of_vertices * sizeof(int));
    int i;
    for (i = 0; i < graph->num_of_vertices; i++) {
        visited[i] = 0;
    }

    visited[startVertex] = 1;

    printf("BFS Traversal starting from vertex %d: ", startVertex);

    int* queue = (int*)malloc(graph->num_of_vertices * sizeof(int));
    int front = 0;
    int rear = 0;

    queue[rear++] = startVertex;

    while (front != rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        node* currentNode = graph->adjLists[currentVertex];
        while (currentNode != NULL) {
            int adjacentVertex = currentNode->vertex;
            if (!visited[adjacentVertex]) {
                visited[adjacentVertex] = 1;
                queue[rear++] = adjacentVertex;
            }
            currentNode = currentNode->next;
        }
    }

    printf("\n");

    free(visited);
    free(queue);
}

void DFS (Graph *graph, int vertex, int *visited) {
    visited[vertex] = 1;
    printf("%d ", vertex);
    node *currentNode = graph->adjLists[vertex];
    while (currentNode != NULL) {
        int adjacentNode = currentNode->vertex;
        if (!visited[adjacentNode]) DFS(graph, adjacentNode, visited);
        currentNode = currentNode->next;
    }
}

void DFS_traversal (Graph *graph, int startVertex) {
    int* visited = (int *)malloc(graph->num_of_vertices * sizeof(int));
    int i;
    for (i = 0; i < graph->num_of_vertices; i++) {
        visited[i] = 0;
    }
    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFS(graph, startVertex, visited);
    printf("\n");
    free(visited);
}

void Remove_Edge(Graph *graph, int source, int destination) {
    node *temp1 = graph->adjLists[source];
    node *temp = graph->adjLists[source];
    node *temp2 = graph->adjLists[destination];

    if (temp->vertex == destination) {
        graph->adjLists[source] = temp->next;
        free(temp);
    } else {
        while (temp->next->vertex != destination) {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        free(temp->next);
    }

    temp = graph->adjLists[destination];
    if (temp->vertex == source) {
        graph->adjLists[destination] = temp->next;
        free(temp);
    } else {
        while (temp->next->vertex != source) {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        free(temp->next);
    }
}

Graph *Prims_Algorithm(Graph *graph) {
    Graph* Minimum_cost_Spanning_Tree = createGraph(graph->num_of_vertices);
    int open[graph->num_of_vertices], i;
    node *temp = NULL, *vertex_pointer = NULL;
    int min_weight = 99999999, destination = 0;
    for (i = 0; i < graph->num_of_vertices; i++) open[i] = 0;
    int currentIndex = 0;
    for (int i = 0; i < graph->num_of_vertices; i++) {
        temp = graph->adjLists[i];
        while (temp != NULL) {
            if (temp->weight < min_weight) {
                min_weight = temp->weight;
                vertex_pointer = temp;
                currentIndex = i;
            }
            temp = temp->next;
        }
    }
    open[currentIndex] = open[temp->vertex] = 1;
    addEdge(Minimum_cost_Spanning_Tree, currentIndex, vertex_pointer->vertex, min_weight);
    for (i = 0; i < graph->num_of_vertices; i++) {
        if (open[i]) {
            temp = graph->adjLists[i];
            while (temp != NULL) {
                if (temp->weight < min_weight) {
                    min_weight = temp->weight;
                    vertex_pointer = temp;
                    currentIndex = i;
                }
            }
        }
    }
}

Graph* Kruskals_Algorithm(Graph* graph) {
    Graph* Minimum_cost_Spanning_Tree = createGraph(graph->num_of_vertices);
    node* temp = NULL;
    node* vertex_pointer = NULL;
    int min_weight = 99999999;
    int index = 0;
    
    for (int j = 0; j < graph->num_of_vertices - 1; j++) {
        min_weight = 99999999; // Reset min_weight for each iteration
        vertex_pointer = NULL;
        
        for (int i = 0; i < graph->num_of_vertices; i++) {
            temp = graph->adjLists[i];
            while (temp != NULL) {
                if (temp->weight < min_weight) {
                    min_weight = temp->weight;
                    vertex_pointer = temp;
                    index = i;
                }
                temp = temp->next;
            }
        }
        
        if (vertex_pointer != NULL) {
            addEdge(Minimum_cost_Spanning_Tree, index, vertex_pointer->vertex, min_weight);
            Remove_Edge(graph, index, vertex_pointer->vertex);
        }
    }

    return Minimum_cost_Spanning_Tree;
}


// Graph *Kruskals_Algorithm(Graph *graph) {
//     Graph *Minimum_cost_Spanning_Tree = createGraph(graph->num_of_vertices);
//     node *temp = graph->adjLists[0], *vertex_pointer = NULL;
//     int min_weight = 99999999, index = 0, prev_min_weight;
//     for (int j = 0; j < graph->num_of_vertices - 1; j++) {
//         for (int i = 0; i < graph->num_of_vertices; i++) {
//             temp = graph->adjLists[i];
//             while (temp != NULL) {
//                 if (temp->weight < min_weight) {
//                     min_weight = temp->weight;
//                     vertex_pointer = temp;
//                     index = i;
//                 }
//                 temp = temp->next;
//             }
//         }
//         addEdge(Minimum_cost_Spanning_Tree, index, vertex_pointer->vertex, min_weight);
//         Remove_Edge(graph, index, vertex_pointer->vertex);
//         min_weight = 99999999;
//     }
//     return Minimum_cost_Spanning_Tree;
// }

int main() {
    Graph *graph = createGraph(9);  
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

    printGraph(graph);
    Graph *newGraph = Kruskals_Algorithm(graph);
    printGraph(newGraph);

    return 0;
}