#include<stdio.h>
#include<stdlib.h>

typedef struct element {
    int row;
    int column;
    int value;
}element;

typedef struct Sparse {
    int num_of_rows;
    int num_of_columns;
    int num_of_non_zero_values;
    element *e;
}Sparse;

void init_matrix(Sparse *S, int numofrows, int numofcolumns, int numofnonzeroelements){
    S->num_of_rows = numofrows;
    S->num_of_columns = numofcolumns;
    S->num_of_non_zero_values = numofnonzeroelements;
    S->e = (element *)malloc(numofnonzeroelements * sizeof(element));
}

void add_elements(Sparse *S) {
    printf("Enter all the elements : \n");
    for (int i = 0; i < S->num_of_non_zero_values; i++) scanf("%d %d %d", &S->e[i].row, &S->e[i].column, &S->e[i].value);
}

Sparse *Add_matrices(Sparse *m1, Sparse *m2) {
    Sparse *Addition = (Sparse *)malloc(sizeof(Sparse));
    init_matrix(Addition, m1->num_of_rows, m1->num_of_columns, m1->num_of_non_zero_values + m2->num_of_non_zero_values);
    int i = 0, j = 0, index = 0;
    while (i < m1->num_of_non_zero_values || j < m2->num_of_non_zero_values) {
        if (m1->e[i].row == m2->e[j].row && m1->e[i].column == m2->e[j].column) {
            Addition->e[index] = m1->e[i];
            Addition->e[index].value = m1->e[i].value + m2->e[j].value;
            i++;
            j++;
            index++;
        }
        if (m1->e[i].column == m2->e[j].column) {
            if (m1->e[i].row < m2->e[j].row) Addition->e[index++] = m1->e[i++];
            else Addition->e[index++] = m2->e[j++];
        }

        if (m1->e[i].row == m2->e[j].column){
            if (m1->e[i].column < m2->e[i].column) Addition->e[index++] = m1->e[i++];
            else Addition->e[index++] = m1->e[i++]; 
        }

        if (m1->e[i].row < m2->e[j].row) Addition->e[index++] = m1->e[i++];
        else Addition->e[index++] = m2->e[j++];

        if (m1->e[i].column < m2->e[i].column) Addition->e[index++] = m1->e[i++];
        else Addition->e[index++] = m1->e[i++]; 
    }

    return Addition;
}

Sparse *Transpose(Sparse *s) {
    Sparse *newmatrix;
    init_matrix(newmatrix, s->num_of_columns, s->num_of_rows, s->num_of_non_zero_values);
    for (int i = 0; i < s->num_of_non_zero_values; i++) {
        newmatrix->e[i].column = s->e[i].column;
        newmatrix->e[i].row = s->e[i].column;
        newmatrix->e[i].column = s->e[i].row;
    }  

    return newmatrix;
}

// void MUL(int m, int n, int *M1[][n], int x, int y, int *M2[][y]) {
//     if (n != x) return;
//     int **M3 = (int **)malloc(m * sizeof(int *));
//     for (int i = 0; i < m; i++) {
//         M3[i] = (int *)malloc(y * sizeof(int));
//     }
//     int m2_col = 0, m2_row = 0, sum = 0;
//     for (int m1_row = 0; m1_row < m; m1_row++) {
//         for (m2_col = 0; m2_col < y; m2_col++){
//             for (int m1_col = 0; m1_col < n; m1_col++){
//                 sum += ((*M1[m1_row][m1_col]) * (*M2[m2_row][m2_col]));
//                 m2_row++;
//             }
//             M3[m1_row][m2_col] = sum;
//             m2_row = 0;
//         }
//     }

//     for(int i = 0; i < m; i++) {
//         for (int j = 0; j < y; j++) printf("%d \t", M3[i][j]);
//         printf("\n");
//     }
// }

void MUL(int m, int n, int (*M1)[n], int x, int y, int (*M2)[y]) {
    if (n != x) return;
    int **M3 = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        M3[i] = (int *)malloc(y * sizeof(int));
    }
    int m2_col = 0, m2_row = 0, sum = 0;
    for (int m1_row = 0; m1_row < m; m1_row++) {
        for (m2_col = 0; m2_col < y; m2_col++){
            for (int m1_col = 0; m1_col < y; m1_col++){
                sum += (M1[m1_row][m1_col] * M2[m2_row][m2_col]);
                m2_row++;
            }
            M3[m1_row][m2_col] = sum;
            sum = 0; // Reset sum for the next iteration
            m2_row = 0;
        }
    }

    for(int i = 0; i < m; i++) {
        for (int j = 0; j < y; j++) printf("%d \t", M3[i][j]);
        printf("\n");
    }
}


void display_matrix(Sparse *S) {
    for (int i = 0; i < S->num_of_non_zero_values; i++) printf("   %d %d %d \n", S->e[i].row, S->e[i].column, S->e[i].value);
}

int main() {
    // Sparse *S1 = (Sparse *)malloc(sizeof(Sparse));   
    // init_matrix(S1, 2, 2, 2);
    // add_elements(S1);
    // display_matrix(S1);

    // Sparse *S2 = (Sparse *)malloc(sizeof(Sparse));   
    // init_matrix(S2, 2, 2, 2);
    // add_elements(S2);
    // display_matrix(S2);

    // Sparse *new = Transpose(S1);

    int M1[3][2] = {{1,2}, {2,1}, {3,3}};
    int M2[2][2] = {{1,2}, {2,1}};

    MUL(3, 2, M1, 2, 2, M2);

    // Sparse *Addition = Add_matrices(S1, S2);

    // display_matrix(Addition);

    return 0;
}