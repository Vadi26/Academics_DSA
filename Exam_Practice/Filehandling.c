#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int count(char *Filename, char *Author) {
    char *charray[20];
    int i = 0;
    FILE * file=fopen(Filename,"r");
	while(fscanf(file, "%s ", charray[i]) == 1) i++;
	fclose(file);
    for (int i=0;i<16;i++) printf("%s ", charray[i]);
}

int main() {
    count("file.dat", "Author");

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_WORDS 100
// #define MAX_LENGTH 50

// void printWords(char words[][MAX_LENGTH], int numWords) {
//     for (int i = 0; i < numWords; i++) {
//         printf("%s\n", words[i]);
//     }
// }

// int main() {
//     char words[MAX_WORDS][MAX_LENGTH];
//     int numWords = 0;
//     char *Filename = "file.dat"; 

//     FILE* file = fopen(Filename, "r");
//     if (file == NULL) {
//         printf("Failed to open the file.\n");
//         return 1;
//     }

//     while (numWords < MAX_WORDS && fscanf(file, "%s", words[numWords]) == 1) {
//         numWords++;
//     }

//     fclose(file);

//     printWords(words, numWords);

//     return 0;
// }
