#include<stdio.h>
#pragma warning(disable : 4996)

#define MAX_NODE 100
int GM[MAX_NODE][MAX_NODE];
typedef struct _node {
	int vertex;
	struct _node* next;
}node;
node* GL[MAX_NODE];
int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}
void input_adjlist(node* a[], int* V, int* E) {
		char vertex[3];
		int i, j;
		node* t;
		printf("\nInput number of node & edge\n");
		scanf("%d %d", V, E);
		for (i = 0; i < *V; i++)
			a[i] = NULL;
		for (j = 0; j < *E; j++) {
			printf("\nInput two node consist of edge ¡æ");
			scanf("%s", vertex);
			i = name2int(vertex[0]);
			t = (node*)malloc(sizeof(node));
			t->vertex = name2int(vertex[1]);
			t->next = a[i];
			a[i] = t;
			i = name2int(vertex[1]);
			t = (node*)malloc(sizeof(node));
			t->vertex = name2int(vertex[0]);
			t->next = a[i];
			a[i] = t;
		}
	
	
}
void print_adjlist(node* a[], int V) {
	node* t;
	for (int i = 0; i < V; i++)
	{
		t = a[i];
		printf("%c", int2name(i));
		while (1) 
		{
			printf("->%c", int2name(t->vertex));
			if (t->next == NULL)
				break;
			t = t->next;
		}
		printf("\n");
	}
}
void input_adjmatrix(int a[][MAX_NODE], int* V, int* E) 
{
	char vertex[3];
	int i, j, k;
	printf("\nInput number of node & edge\n");
	scanf("%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			a[i][j] = 0;
	for (i = 0; i < *V; i++)
		a[i][i] = 1;
	for (k = 0; k < *E; k++) 
	{
		printf("\nInput two node consist of edge ¡æ");
		scanf("%s", vertex);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		a[i][j] = 1;
		a[j][i] = 1;
	}
}

void print_adjmatrix(int a[][MAX_NODE], int V) 
{
	for (int i = 0; i < V; i++) 
	{
		for (int j = 0; j < V; j++) 
		{
			printf("%-2d", a[i][j]);
		}
		printf("\n");
	}
}

void main()
{
	int V, E;
	input_adjmatrix(GM, &V, &E);
	print_adjmatrix(GM, V);

}
	//input_adjlist(GL, &V, &E);
	//print_adjlist(GL, V);

