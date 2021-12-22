#include<stdio.h>
#pragma warning (disable : 4996)
#define INDEX 100
#define MAX_NODE 100

int GM[MAX_NODE][MAX_NODE];
int check[MAX_NODE];
int top;
int stack[INDEX];

#define init_stack() (top = -1)
#define push(data) (stack[++top] = (data))
#define pop() (stack[top--])
#define stack_empty() (top < 0)

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
void visit(int i) {
	printf("%c is visited\n", int2name(i));
}
void DFS_recur_matrix(int a[][MAX_NODE], int V, int i)
{
	int j;
	check[i] = 1;
	visit(i);
	for (j = 0; j < V; j++)
		if (a[i][j] != 0)
			if (check[j] == 0)
				DFS_recur_matrix(a, V, j);
}
void DFS_adjmatrix(int a[][MAX_NODE], int V) {
	int i;
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++)
		if (check[i] == 0) DFS_recur_matrix(a, V, i);
}
void nrDFS_adjmatrix(int a[][MAX_NODE], int V)
{
	int i, j;
	init_stack();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			push(i);
			check[i] = 1;
			while (!stack_empty()) {
				i = pop();
				visit(i);
				for (j = 0; j < V; j++)
					if (a[i][j] != 0)
						if (check[j] == 0) {
							push(j);
							check[j] = 1;
						}
			}
		}
	}
}
void DFS_recur_list(node* a[], int V, int i)
{
	node* t;
	check[i] = 1;
	visit(i);
	for (t = a[i]; t != NULL; t = t->next)
		if (check[t->vertex] == 0)
			DFS_recur_list(a, V, t->vertex);
}
void DFS_adjlist(node* a[], int V)
{
	int i;
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++)
		if (check[i] == 0) DFS_recur_list(a, V, i);
}
void nrDFS_adjlist(node* a[], int V)
{
	int i, j;
	node* t;
	init_stack();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		t = a[i];
		if (check[i] == 0) {
			push(i);
			check[i] = 1;
			while (!stack_empty()) {
				i = pop();
				visit(i);
				for (t = a[i]; t != NULL; t = t->next)
					if (check[t->vertex] == 0) {
						push(t->vertex);
						check[t->vertex] = 1;
					}
			}
		}
	}
}


void main()
{
	int V, E;

	input_adjmatrix(GM, &V, &E);
	print_adjmatrix(GM, V);

	DFS_adjmatrix(GM, V);
	nrDFS_adjmatrix(GM, V);

	input_adjlist(GL, &V, &E);
	print_adjlist(GL, V);

	DFS_adjlist(GL, V);
	nrDFS_adjlist(GL, V);
}