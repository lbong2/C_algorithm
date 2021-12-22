#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable:4996)
#define MAX_NODE 100
#define INDEX 100
int top;
int stack[INDEX];
#define init_stack() (top = -1)
#define push(data) (stack[++top] = (data))
#define pop() (stack[top--])
#define stack_empty() (top < 0)
FILE* fp;

typedef struct node {
	int vertex;	// ÀÌ¸§ 
	struct node* next;
}node;
node* GL[MAX_NODE];
int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}
int check[MAX_NODE];
int order;
int strong_recur(node* g[], int i)
{
	int m, min, k, flag;
	node* t;
	check[i] = min = ++order;
	push(i);
	for (t = g[i]; t != NULL; t = t->next) {
		if (check[t->vertex] == 0)
			m = strong_recur(g, t->vertex);
		else
			m = check[t->vertex];
			if (m < min) min = m;
	}
	if (min == check[i]) { // check for cycle
		flag = 0;
	
			while ((k = pop()) != i) {
				printf("%c ", int2name(k));
				check[k] = MAX_NODE + 1;
				flag = 1;
			}
		if (flag) printf("%c\n", int2name(k));
	}
	return min;
}
void strong(node* a[], int V)
{
	int x, y;
	
	for (y = 0; y < V; y++) check[y] = 0;
	order = 0; 
	for(y = 0; y < V; y++)
		if(check[y] == 0)
			strong_recur(a, y);
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

void main() {
	int V, E;
	
	fp = fopen("node.txt", "rt");
	
	input_adjlist(GL, &V, &E);
	printf("\n");
	strong(GL, V);
	fclose(fp);
}