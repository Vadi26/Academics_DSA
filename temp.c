#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int array[5][5];
    FILE * file=fopen("file.txt","r");
	for (int i=0;i<4;i++) {
		for (int j=0;j<4;j++) {
			fscanf(file, "%d", &array[i][j]);
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}
