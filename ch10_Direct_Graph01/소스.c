#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable : 4996)
#define MAX_NODE 50
FILE* fp;
typedef struct node {
	int vertex;
	struct node* next;
}node;
node* GL[MAX_NODE];
int GM[MAX_NODE][MAX_NODE];
int check[MAX_NODE]; // for storing the weight
int parent[MAX_NODE];
int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}
#define INDEX 100

int top;
int stack[INDEX];
#define init_stack() (top = -1)
#define push(data) (stack[++top] = (data))
#define pop() (stack[top--])
#define stack_empty() (top < 0)
void visit(int i) {
	printf("%c ", int2name(i));
}
void input_adjmatrix(int g[][MAX_NODE], int* V, int* E) {
	char vertex[3];
	int i, j, k;
	printf("\nInput number of nodes & edges\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			g[i][j] = 0;
	for (i = 0; i < *V; i++)
		g[i][i] = 0;
	for (k = 0; k < *E; k++) {
		printf("\nInput two nodes consisting of edge ¡æ ");
		fscanf(fp, "%s", vertex);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		g[i][j] = 1;
	}
}
void input_adjlist(node* a[], int* V, int* E) {
	char vertex[3];
	int i, j;
	node* t;
	printf("\nInput number of nodes & edges\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		a[i] = NULL;
	for (j = 0; j < *E; j++) {
		printf("\nInput two nodes consisting of edge ¡æ ");
		fscanf(fp, "%s", vertex);
		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->next = a[i];
		a[i] = t;
	}
}
void DFS_directed(node* a[], int V) {
	int i, j;
	node* t;
	init_stack();
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++)
			check[j] = 0;
		push(i);
		check[i] = 1;
		printf("\n %c : ", int2name(i));
		while (!stack_empty()) {
			j = pop();
			visit(j);
			for (t = a[j]; t != NULL; t = t->next) {
				if (check[t->vertex] == 0) {
					push(t->vertex);
					check[t->vertex] = 1;
				}
			}
		}
	}
}
void warshall(int GM[][MAX_NODE], int V) {
	int x, y, k;
	for (y = 0; y < V; y++) {
		for (x = 0; x < V; x++) {
			if (GM[x][y] == 1) {
				for (k = 0; k < V; k++) {
					if (GM[y][k] == 1)
					{
						GM[x][k] = 1;
					}
				}
			}
		}
	}
}
void main() {
	int V, E;
	int V1, E1;
	fp = fopen("node.txt", "rt");
	input_adjlist(GL, &V, &E);
	input_adjmatrix(GM, &V1, &E1);

	DFS_directed(GL, V);
}