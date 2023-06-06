#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

// int array[0][0];
int size = 5;

void display_Graph(int array[][size]){
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

void display_degrees(int array[][size]) {
    int i, j, count = 0, degrees[size];
    for(i = 0; i < size; i++) degrees[i] = 0;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (array[i][j] != 0) count++;
        }
        degrees[i] = count;
        count = 0;
    }
    for (i = 0; i < size; i++) printf("%d ", degrees[i]);
}

bool isConnected(int array[][size]) {
    int i, j, count = 0;
    for (i = 0; i < size; i++) {
        count = 0;
        for (j = 0; j < size; j++) if (array[i][j] == 0) count++;
        if (count == size) return false;
    }
    return true;
}

bool isAdjacent(int v1, int v2, int array[][size]) {
    if (array[v1 - 1][v2 - 1] != 0) return true;
    else return false;
}

int main() {
    int source, destination, weight;
    int array[5][5];
    FILE * file=fopen("file.txt","r");
	for (int i=0;i<5;i++) {
		for (int j=0;j<5;j++) {
			fscanf(file, "%d", &array[i][j]);
        }
    }
	fclose(file);
    // for(int i = 0; i < 5; i++) for (int j = 0; j < 5; j++) array[i][j] = 0;
    display_Graph(array);
    display_degrees(array);
    printf("\n");
    if (isConnected(array)) printf("The graph is connected. \n");
    else printf("The graph is not connected. \n");
    if (isAdjacent(3, 4, array)) printf("The given nodes are adjacent \n");
    else printf("The nodes 3 & 4 are not adjacent \n");

    return 0;
}