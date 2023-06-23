typedef struct node{
	int data;
	struct node *right;
	struct node *down;
}node;
typedef struct sparseMatrix{
	int r, c;
	struct node **row, **col;
}sparseMatrix;
void matrixInit(sparseMatrix *m, char name[]);
void append(sparseMatrix *m, int i, int j, node *n);//insert node
void displayNew(sparseMatrix m);

int getValue(sparseMatrix m, int i, int j);
void addMatrices(sparseMatrix m1, sparseMatrix m2, sparseMatrix *m3);
void transposeMatrix(sparseMatrix ms, sparseMatrix *md);
int multiplyMatrices(sparseMatrix m1, sparseMatrix m2, sparseMatrix *md);
int concatenateMatrix(sparseMatrix *m1, sparseMatrix m2);
void subMatrices(sparseMatrix m1, sparseMatrix m2, sparseMatrix *m3);
