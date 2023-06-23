#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int vertex;
    int weight;
    struct node *next;
} node;

typedef struct Graph
{
    int num_of_vertices;
    node **adjLists;
} Graph;

node *FRONT = NULL, *REAR = NULL;

node *createNode(int data)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->vertex = data;
    newNode->next = NULL;
    newNode->weight = 0;
    return newNode;
}

Graph *createGraph(int vertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->num_of_vertices = vertices;
    graph->adjLists = malloc(sizeof(node *) * vertices);
    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

void addEdge(Graph *graph, int source, int destination, int weight)
{
    node *newNode = createNode(destination);
    newNode->weight = weight;
    newNode->next = graph->adjLists[source];
    graph->adjLists[source] = newNode;

    newNode = createNode(source);
    newNode->weight = weight;
    newNode->next = graph->adjLists[destination];
    graph->adjLists[destination] = newNode;
}

void printGraph(Graph *graph)
{
    for (int v = 0; v < graph->num_of_vertices; v++)
    {
        node *temp = graph->adjLists[v];
        printf("\n Vertex : %d \n", v);
        while (temp)
        {
            printf("%d(%d) -> ", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

void BFS(Graph *graph, int startVertex)
{
    int *visited = (int *)malloc(graph->num_of_vertices * sizeof(int));
    int i;
    for (i = 0; i < graph->num_of_vertices; i++)
    {
        visited[i] = 0;
    }

    visited[startVertex] = 1;

    printf("BFS Traversal starting from vertex %d: ", startVertex);

    int *queue = (int *)malloc(graph->num_of_vertices * sizeof(int));
    int front = 0;
    int rear = 0;

    queue[rear++] = startVertex;

    while (front != rear)
    {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        node *currentNode = graph->adjLists[currentVertex];
        while (currentNode != NULL)
        {
            int adjacentVertex = currentNode->vertex;
            if (!visited[adjacentVertex])
            {
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

void DFS(Graph *graph, int vertex, int *visited)
{
    visited[vertex] = 1;
    printf("%d ", vertex);
    node *currentNode = graph->adjLists[vertex];
    while (currentNode != NULL)
    {
        int adjacentNode = currentNode->vertex;
        if (!visited[adjacentNode])
            DFS(graph, adjacentNode, visited);
        currentNode = currentNode->next;
    }
}

void DFS_traversal(Graph *graph, int startVertex)
{
    int *visited = (int *)malloc(graph->num_of_vertices * sizeof(int));
    int i;
    for (i = 0; i < graph->num_of_vertices; i++)
    {
        visited[i] = 0;
    }
    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFS(graph, startVertex, visited);
    printf("\n");
    free(visited);
}

void Remove_Edge(Graph *graph, int source, int destination)
{
    node *temp1 = graph->adjLists[source];
    node *temp = graph->adjLists[source];
    node *temp2 = graph->adjLists[destination];

    if (temp->vertex == destination)
    {
        graph->adjLists[source] = temp->next;
        free(temp);
    }
    else
    {
        while (temp->next->vertex != destination)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        free(temp->next);
    }

    temp = graph->adjLists[destination];
    if (temp->vertex == source)
    {
        graph->adjLists[destination] = temp->next;
        free(temp);
    }
    else
    {
        while (temp->next->vertex != source)
        {
            temp = temp->next;
        }
        temp->next = temp->next->next;
        free(temp->next);
    }
}

int does_edge_exist(Graph *graph, int source, int destination)
{
    node *temp = graph->adjLists[source];
    while (temp != NULL)
    {
        if (temp->vertex == destination)
            return 1;
        temp = temp->next;
    }
    return 0;
}

bool isCyclicUtil(Graph *graph, int v, bool visited[], int parent)
{
    visited[v] = true;

    node *temp = graph->adjLists[v];
    while (temp)
    {
        int adjacentVertex = temp->vertex;

        if (!visited[adjacentVertex])
        {
            if (isCyclicUtil(graph, adjacentVertex, visited, v))
                return true;
        }
        else if (adjacentVertex != parent)
        {
            return true;
        }

        temp = temp->next;
    }

    return false;
}

bool isCyclic(Graph *graph)
{
    bool *visited = malloc(sizeof(bool) * graph->num_of_vertices);
    for (int i = 0; i < graph->num_of_vertices; i++)
        visited[i] = false;

    for (int v = 0; v < graph->num_of_vertices; v++)
    {
        if (!visited[v])
        {
            if (isCyclicUtil(graph, v, visited, -1))
                return true;
        }
    }

    return false;
}

Graph *Prims_Algorithm(Graph *original_graph)
{
    Graph *MST = createGraph(original_graph->num_of_vertices);
    int open_index = 0, source = 0, new_connected_vertex = 0, new_source = 0, min_weight = 9999999, connected_vertex = 0, i = 0;
    node *temp = original_graph->adjLists[0];

    int open_vertices[original_graph->num_of_vertices];
    for (i = 0; i < original_graph->num_of_vertices; i++)
        open_vertices[i] = 0;

    open_vertices[0] = 1;
    for (i = 0; i < original_graph->num_of_vertices - 1; i++)
    {
        min_weight = 9999999;
        connected_vertex = 0;
        for (open_index = 0; open_index < original_graph->num_of_vertices; open_index++)
        {
            if (open_vertices[open_index])
            {
                temp = original_graph->adjLists[open_index];
                while (temp != NULL)
                {
                    if (!does_edge_exist(MST, open_index, temp->vertex))
                    {
                        if (temp->weight < min_weight)
                        {
                            min_weight = temp->weight;
                            source = open_index;
                            connected_vertex = temp->vertex;
                        }
                    }
                    temp = temp->next;
                }
            }
        }
        addEdge(MST, source, connected_vertex, min_weight);
        open_vertices[connected_vertex] = 1;
    }
    return MST;
}

int *indegrees(Graph *g)
{
    int *Indegrees = (int *)malloc(sizeof(int) * g->num_of_vertices);
    for (int i = 0; i < g->num_of_vertices; i++)
        Indegrees[i] = 0;
    for (int i = 0; i < g->num_of_vertices; i++)
    {
        node *temp = g->adjLists[i];
        while (temp != NULL)
        {
            switch (temp->vertex)
            {
            case 0:
                Indegrees[0]++;
                break;

            case 1:
                Indegrees[1]++;
                break;

            case 2:
                Indegrees[2]++;
                break;

            case 3:
                Indegrees[3]++;
                break;

            case 4:
                Indegrees[4]++;
                break;

            case 5:
                Indegrees[5]++;
                break;

            case 6:
                Indegrees[6]++;
                break;

            case 7:
                Indegrees[7]++;
                break;

            case 8:
                Indegrees[8]++;
                break;

            default:
                break;
            }
            temp = temp->next;
        }
    }
    return Indegrees;
}

void insert_heap(Graph *G, int *heap, node *edge)
{
    for (int i = 0; i < G->num_of_vertices; i++)
    {
        node *temp = G->adjLists[i];
        while (temp != NULL)
        {

            temp = temp->next;
        }
    }
}

// int* Dijkstra(Graph G,int s){
//   //from s to every others vertex shortest distance
//   int* cost=(int*)malloc(sizeof(int)*G.num_of_vertices);
//   if(!cost)
//     return 0;
//   int* visited=(int*)calloc(G.num_of_vertices,sizeof(int));
//   if(!visited)
//   {
//     free(cost);
//     return 0;
//   }
//   for(int i=0;i<G.n;i++){
//     //copy the row of vertex from which we want shortest distance from all other vertices
//     cost[i]=G.A[s][i];
//   }
//   visited[s]=1;
//   int min;int min_i;
//   for(int i=0;i<G.n;i++){
//     min=3000;
//     ///get minumum distance from source to some vertex from cost array which hasnt been chosen before
//     for(int j=0;j<G.n;j++){
//       if(!visited[j]&&cost[j]<min){
//         min=cost[j];
//         min_i=j;
//       }
//     }
//     //mark minumum distance from source as visited
//     visited[min_i]=1;
//     //relaxation
//     for(int k=0;k<G.n;k++){
//       if(!visited[k]){
//         if(cost[k]>min+G.A[min_i][k])
//           cost[k]=min+G.A[min_i][k];
//       }
//     }
//   }
//   return cost;
// }

int main()
{
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

    // printf("                        %d                      \n", isCyclic(hehe));
    Graph *newGraph = Prims_Algorithm(graph);
    printf("                        %d                      \n", isCyclic(newGraph));
    printGraph(newGraph);

    int *arr = indegrees(graph);
    for (int i = 0; i < graph->num_of_vertices; i++) printf("%d ", arr[i]);
    

    return 0;
}