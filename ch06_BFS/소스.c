#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable : 4996)
#define INDEX 100
#define MAX_NODE 100
#define init_stack() (top = -1)
#define push(data) (stack[++top] = (data))
#define pop() (stack[top--])
#define stack_empty() (top < 0)
int top;
int stack[INDEX];
int GM[MAX_NODE][MAX_NODE];
int check[MAX_NODE];
int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}
void visit(int i) {
	printf("%c is visited\n", int2name(i));
}
typedef struct _dnode
{
	int key;
	struct _dnode* prev;
	struct _dnode* next;
}dnode;
dnode* GL[MAX_NODE];
dnode* head, * tail;
void init_queue()
{
	head = (dnode*)calloc(1, sizeof(dnode));
	tail = (dnode*)calloc(1, sizeof(dnode));
	head->prev = head;
	head->next = tail;
	tail->prev = head;
	tail->next = tail;
}
int put(int k)
{
	dnode* t;
	if ((t = (dnode*)malloc
	(sizeof(dnode))) == NULL)
	{
		printf("Out of memory !\n");
		return -1;
	}
	t->key = k;
	tail->prev->next = t;
	t->prev = tail->prev;
	tail->prev = t;
	t->next = tail;
	return k;
}
int get()
{
	dnode* t;
	int k;
	t = head->next;
	if (t == tail)
	{
		printf("Queue underflow\n");
		return -1;
	}
	k = t->key;
	head->next = t->next;
	t->next->prev = head;
	free(t);
	return k;
}
int queue_empty() {
	if (head->next == tail)
		return 1;
	else
		return 0;
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
	printf("\n");
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			printf("%-2d", a[i][j]);
		}
		printf("\n");
	}
}
void input_adjlist(dnode* a[], int* V, int* E) {
	char vertex[3];
	int i, j;
	dnode* t;
	printf("\nInput number of node & edge\n");
	scanf("%d %d", V, E);
	for (i = 0; i < *V; i++)
		a[i] = NULL;
	for (j = 0; j < *E; j++) {
		printf("\nInput two node consist of edge ¡æ");
		scanf("%s", vertex);
		i = name2int(vertex[0]);
		t = (dnode*)malloc(sizeof(dnode));
		t->key = name2int(vertex[1]);
		t->next = a[i];
		a[i] = t;
		i = name2int(vertex[1]);
		t = (dnode*)malloc(sizeof(dnode));
		t->key = name2int(vertex[0]);
		t->next = a[i];
		a[i] = t;
	}


}
void print_adjlist(dnode* a[], int V) {
	dnode* t;
	for (int i = 0; i < V; i++)
	{
		t = a[i];
		printf("%c", int2name(i));
		while (1)
		{
			printf("->%c", int2name(t->key));
			if (t->next == NULL)
				break;
			t = t->next;
		}
		printf("\n");
	}
}
void BFS_adjmatrix(int a[][MAX_NODE], int V)
{
	int i, j;
	init_queue();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			put(i);
			check[i] = 1;
			while (!queue_empty()) {
				i = get();
				visit(i);
				for (j = 0; j < V; j++)
					if (a[i][j] != 0)
						if (check[j] == 0) {
							put(j);
							check[j] = 1;
						}
			}
		}
	}
}
void BFS_adjlist(dnode* a[], int V)
{
	int i;
	dnode* t;
	init_queue();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			put(i);
			check[i] = 1;
			while (!queue_empty()) {
				i = get();
				visit(i);
				for (t = a[i]; t != NULL; t = t->next)
					if (check[t->key] == 0) {
						put(t->key);
						check[t->key] = 1;
					}
			}
		}
	}
}
void count_components(int a[][MAX_NODE], int V)
{
	int cnt = 0;
	int i, j;
	init_stack();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			++cnt;
			push(i);
			check[i] = 1;
			while (!stack_empty()) {
				i = pop();
				printf("%c", int2name(i));
			}
			
			for (j = 0; j < V; j++) {
				if (a[i][j] != 0)
					if (check[j] == 0) {
							push(j);
							check[j] = 1;
					}
			}
		}
	}

	printf("# of CC : %d\n", cnt);
}
void main()
{
	int V, E;
	// for adjacency matrix
	input_adjmatrix(GM, &V, &E);
	print_adjmatrix(GM, V);
	// traverse the given graph
	BFS_adjmatrix(GM, V);
}