#include <stdio.h>
#include "sparseMatrix.h"
int main(){
	sparseMatrix matrix1, matrix2, additionM, transM, mulM, concM,subM;
	matrixInit(&matrix1, "sparseM.txt");
	printf("Matrix 1 is :-\n");
	displayNew(matrix1);
	matrixInit(&matrix2, "sparseM2.txt");
	printf("Matrix 2 is :-\n");
	displayNew(matrix2);
	addMatrices(matrix1, matrix2, &additionM);
	printf("Addition of Matrix 1 and matrix2 is :-\n");
	displayNew(additionM);
	subMatrices(matrix1, matrix2, &subM);
	printf("Substraction of matrix2 from matrix 1 is :- \n");
	displayNew(subM);
	printf("Transpose of additionM is :-\n");
	transposeMatrix(additionM, &transM);
	displayNew(transM);
	multiplyMatrices(matrix1, matrix2, &mulM);
	printf("Multiplication of  matrix1 and matrix2 is :-\n");
	displayNew(mulM);
	matrixInit(&concM, "sparseM3.txt");
	printf("Matrix before concatenation is :-\n");
	displayNew(concM);
	concatenateMatrix(&concM, matrix2);
	printf("Matrix after concatenation is :-\n");
	displayNew(concM);
	return 0;
}
