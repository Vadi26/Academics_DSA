#include <stdio.h>
#include <stdlib.h>
#include "sparseMatrix.h"

void matrixInit(sparseMatrix *m, char name[])
{
	int val;
	FILE *fp = fopen(name, "r");
	node *n;
	fscanf(fp, "%d\n", &(m->r));
	fscanf(fp, "%d\n", &(m->c));
	m->row = malloc(sizeof(node *) * m->r);
	m->col = malloc(sizeof(node *) * m->c);
	for (int i = 0; i < m->r; i++)
	{
		m->row[i] = NULL;
	}
	for (int i = 0; i < m->c; i++)
	{
		m->col[i] = NULL;
	}
	for (int i = 0; i < m->r; i++)
	{
		for (int j = 0; j < m->c; j++)
		{
			fscanf(fp, "%d ", &val);
			if (val)
			{
				n = malloc(sizeof(node));
				n->data = val;
				n->right = NULL;
				n->down = NULL;
				append(m, i, j, n);
			}
		}
	}
}
void append(sparseMatrix *m, int i, int j, node *n)
{
	node *r, *c;
	r = m->row[i];
	c = m->col[j];
	if (r)
	{
		while (r->right)
		{
			r = r->right;
		}
		r->right = n;
	}
	else
	{
		m->row[i] = n;
	}
	if (c)
	{
		while (c->down)
		{
			c = c->down;
		}
		c->down = n;
	}
	else
	{
		m->col[j] = n;
	}
}
/*void display(sparseMatrix m){
	node *n;
	int prevJ;
	for(int i = 0; i < m.r; i++){
		n = m.row[i];
		prevJ = -1;
		if(!n){
			for(int j = 0; j < m.c; j++){
				printf("0 ");
			}
			printf("\n");
		}
		else{
			while(n){
				while(n->j - prevJ - 1){
					printf("0 ");
					prevJ++;
				}
				printf("%d ", n->data);
				prevJ = n->j;
				if(!n->right && (n->j != (m.c - 1))){
					while(m.c - prevJ - 1){
						printf("0 ");
						prevJ++;
					}
				}
				n = n->right;
			}
			printf("\n");
		}

	}
}*/
void displayNew(sparseMatrix m)
{
	if (!m.r || !m.c)
	{
		return;
	}
	node *rp, *cp;
	int k;
	int flag;
	for (int i = 0; i < m.r; i++)
	{
		rp = m.row[i];
		if (!rp)
		{
			for (int j = 0; j < m.c; j++)
			{
				printf("0 ");
			}
			printf("\n");
		}
		else
		{
			for (int j = 0; j < m.c; j++)
			{
				cp = m.col[j];
				flag = 1;

				while (cp)
				{
					if (rp == cp)
					{
						printf("%d ", rp->data);
						rp = rp->right;
						flag = 0;
						break;
					}
					cp = cp->down;
				}
				if (flag)
				{
					printf("0 ");
				}
			}
			printf("\n");
		}
	}
}

int getValue(sparseMatrix m, int i, int j)
{
	node *r = m.row[i];
	node *c = m.col[j];
	int flag = 0;
	if (!r || !c)
	{
		return 0;
	}
	while (r)
	{
		c = m.col[j];
		while (c)
		{
			if (r == c)
			{
				flag = 1;
				break;
			}
			c = c->down;
		}
		if (flag)
		{
			break;
		}
		r = r->right;
	}
	if (flag)
		return r->data;
	else
		return 0;
}
void addMatrices(sparseMatrix m1, sparseMatrix m2, sparseMatrix *m3)
{
	if ((m1.r != m2.r) || (m1.c != m2.c))
	{
		m3->row = NULL;
		m3->col = NULL;
		m3->r = 0;
		m3->c = 0;
		return;
	}
	int value;
	node *n;
	m3->r = m1.r;
	m3->c = m1.c;
	m3->row = malloc(sizeof(node *) * (m1.r));
	m3->col = malloc(sizeof(node *) * (m1.c));
	for (int i = 0; i < m1.r; i++)
		m3->row[i] = NULL;
	for (int i = 0; i < m1.c; i++)
		m3->col[i] = NULL;
	for (int i = 0; i < m1.r; i++)
	{
		for (int j = 0; j < m1.c; j++)
		{
			value = getValue(m1, i, j) + getValue(m2, i, j);
			if (value)
			{
				n = malloc(sizeof(node));
				n->data = value;
				n->right = NULL;
				n->down = NULL;
				append(m3, i, j, n);
			}
		}
	}
}
void subMatrices(sparseMatrix m1, sparseMatrix m2, sparseMatrix *m3)
{
	if ((m1.r != m2.r) || (m1.c != m2.c))
	{
		m3->row = NULL;
		m3->col = NULL;
		m3->r = 0;
		m3->c = 0;
		return;
	}
	int value;
	node *n;
	m3->r = m1.r;
	m3->c = m1.c;
	m3->row = malloc(sizeof(node *) * (m1.r));
	m3->col = malloc(sizeof(node *) * (m1.c));
	for (int i = 0; i < m1.r; i++)
		m3->row[i] = NULL;
	for (int i = 0; i < m1.c; i++)
		m3->col[i] = NULL;
	for (int i = 0; i < m1.r; i++)
	{
		for (int j = 0; j < m1.c; j++)
		{
			value = getValue(m1, i, j) - getValue(m2, i, j);
			if (value)
			{
				n = malloc(sizeof(node));
				n->data = value;
				n->right = NULL;
				n->down = NULL;
				append(m3, i, j, n);
			}
		}
	}
}
void transposeMatrix(sparseMatrix ms, sparseMatrix *md)
{
	if (!ms.r || !ms.c)
	{
		md->row = NULL;
		md->col = NULL;
		md->r = 0;
		md->c = 0;
		return;
	}
	int value;
	node *n;
	md->r = ms.c;
	md->c = ms.r;
	md->row = malloc(sizeof(node *) * md->r);
	md->col = malloc(sizeof(node *) * md->c);
	for (int i = 0; i < md->r; i++)
		md->row[i] = NULL;
	for (int i = 0; i < md->c; i++)
		md->col[i] = NULL;
	for (int i = 0; i < md->r; i++)
	{
		for (int j = 0; j < md->c; j++)
		{
			value = getValue(ms, j, i);
			if (value)
			{
				n = malloc(sizeof(node));
				n->right = NULL;
				n->down = NULL;
				n->data = value;
				append(md, i, j, n);
			}
		}
	}
}
int multiplyMatrices(sparseMatrix m1, sparseMatrix m2, sparseMatrix *md)
{
	if (m1.c != m2.r)
	{
		return 1;
	}
	int value;
	node *n;
	md->r = m1.r;
	md->c = m2.c;
	md->row = malloc(sizeof(node *) * md->r);
	md->col = malloc(sizeof(node *) * md->c);
	for (int i = 0; i < md->r; i++)
		md->row[i] = NULL;
	for (int i = 0; i < md->c; i++)
		md->col[i] = NULL;
	for (int i = 0; i < md->r; i++)
	{
		for (int j = 0; j < md->c; j++)
		{
			value = 0;
			for (int k = 0; k < m1.c; k++)
				value += getValue(m1, i, k) * getValue(m2, k, j);
			if (value)
			{
				n = malloc(sizeof(node));
				n->data = value;
				n->right = NULL;
				n->down = NULL;
				append(md, i, j, n);
			}
		}
	}
	return 0;
}
int concatenateMatrix(sparseMatrix *m1, sparseMatrix m2)
{
	if (m1->r != m2.r)
		return 1;
	m1->col = realloc(m1->col, (m1->c + m2.c) * sizeof(node *));
	int cPrev = m1->c;
	int value;
	node *n;
	m1->c += m2.c;
	for (int i = cPrev; i < m1->c; i++)
	{
		m1->col[i] = NULL;
	}
	for (int i = 0; i < m1->r; i++)
	{
		for (int j = cPrev; j < m1->c; j++)
		{
			value = getValue(m2, i, j - cPrev);
			if (value)
			{
				n = malloc(sizeof(node *));
				n->data = value;
				n->right = NULL;
				n->down = NULL;
				append(m1, i, j, n);
			}
		}
	}
	return 0;
}

int main()
{
	sparseMatrix matrix1, matrix2, additionM, transM, mulM, concM, subM;
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
