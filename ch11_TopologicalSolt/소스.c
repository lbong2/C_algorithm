#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable : 4996)
#define MAX_NODE 100
#define INDEX 100
int top;
int stack[INDEX];
#define init_stack() (top = -1)
#define push(data) (stack[++top] = (data))
#define pop() (stack[top--])
#define stack_empty() (top < 0)

typedef struct node {
	int vertex;	// 이름 
	struct node* next;
}node;
typedef struct _head {
	int count;	// 진입차수 
	struct node* next;
}head;
head network[MAX_NODE];
int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}
FILE* fp;
void print_adjlist(head net[], int V)
{          /* print network */
	int i;
	node* t;
	for (i = 0; i < V; i++)
	{
		printf("\n%c:%d | ", int2name(i), net[i].count);
		for (t = net[i].next; t != NULL; t = t->next)
			printf("-> %c ", int2name(t->vertex));
	}
}
void set_count_indegree(head net[], int V)
{         
	int i, j;
	int count;
	node* t;
	for (i = 0; i < V; i++)
	{
		count = 0;
		for (j = 0; j < V; j++)
			for (t = net[j].next; t; t = t->next)
				if (t->vertex == i) count++;
		net[i].count = count;
	}
}
void topsort(head net[], int V)
{
	int i, j, k;
	node* ptr;

	init_stack();

	set_count_indegree(net, V);
	for (i = 0; i < V; i++)
		if (!net[i].count)
			push(i);
	for (i = 0; i < V; i++)
	{

		if (stack_empty())
		{
			return -1;
		}
		else
		{
			j = pop();
			printf("%c, ", int2name(j));
			for (ptr = net[j].next; ptr; ptr = ptr->next)
			{
				k = ptr->vertex;
				net[k].count--;
				if (!net[k].count)
					push(k);
			}
		}
	}
}
void set_count_zero(head net[], int V)
{
	int i;
	for (i = 0; i < V; i++)
		net[i].count = 0;
}
void input_adjlist(head net[], int* V, int* E)
{     /* input network */
	int i, j;
	char edge[3];
	node* t;
	printf("\nInput number of Vertex & Edge\n");
	fscanf(fp, "%d %d", V, E);  /* input no of Vertex & Edge */

	set_count_zero(net, *V);

	for (i = 0; i < *V; i++)
		net[i].next = NULL;

	for (j = 0; j < *E; j++)
	{
		printf("\nInput two Vertex consist of Edge -> ");
		fscanf(fp, "%s", edge);

		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(edge[1]);
		t->next = net[name2int(edge[0])].next;
		net[name2int(edge[0])].next = t;
	}
}

void set_count_outdegree(head net[], int V)
{
	int i, count;
	node* t;
	for (i = 0; i < V; i++) {
		count = 0;
		for (t = net[i].next; t; t = t->next)
			count++;
		net[i].count = count;
	}
}
void revtopsort(head net[], int V)
{
	int i, j, k;
	node* ptr;
	init_stack();
	set_count_outdegree(net, V);
	for (i = 0; i < V; i++)
		if (!net[i].count) push(i);
	for (i = 0; i < V; i++) {
		if (stack_empty()) return -1;
		else {
			j = pop();
			printf("%c, ", int2name(j));
			for (k = 0; k < V; k++)
				for (ptr = net[k].next; ptr; ptr = ptr->next)
					if (ptr->vertex == j) {
						net[k].count--;
						if (!net[k].count)
							push(k);
					}
		}
	}
}

void main() {
	int V, E;

	fp = fopen("node.txt", "rt");

	input_adjlist(network, &V, &E);
	printf("\n");
	print_adjlist(network, V);
	printf("\n");
	topsort(network, V);
	
	printf("\n");
	revtopsort(network, V);
	fclose(fp);

	
	
}
// AB BC CD CE CF CG FH FI FJ HK IK JK KL EK