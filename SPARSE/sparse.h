typedef struct node{
	int data;
	int i,j;
	struct node *right , *down;
}node;
typedef struct sparse{
	node **row, **col;
	int r,c;
}sparse;

void init_matrix(sparse *s , char *filename);
void insertnode(sparse *s, node *n , int i , int j);
void display(sparse s);
sparse addsparse(sparse s1 , sparse s2);
sparse subtractsparse(sparse s1 , sparse s2);
sparse transpose(sparse s);
int checksymmetric(sparse s);
