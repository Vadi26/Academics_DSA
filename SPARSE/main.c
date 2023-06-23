#include<stdio.h>
#include<stdlib.h>
#include"sparse.h"
int main(){
	sparse s1 , s2 , s3 , s4 , s5;
	init_matrix(&s1 , "M1.txt");
	init_matrix(&s2 , "M2.txt");
	printf("Matrix 1 : \n");
	display(s1);
	printf("Matrix 2 : \n");
	display(s2);
	printf("Symmetric check for M2 : \n");
	printf("%d\n",checksymmetric(s2));
	printf("Addition : \n");
	s4 = addsparse(s1,s2);
	display(s4);
	printf("Subtraction of M1 - M2 : \n");
	s5 = subtractsparse(s1,s2);
	display(s5);
	printf("Transpose of M1 : \n");
	s3 = transpose(s1);
	display(s3);
	return 0 ;
}
