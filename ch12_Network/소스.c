#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable : 4996)
#define MAX_NODE 100
#define INDEX 100
int top;
int stack[INDEX];
int earliest[MAX_NODE];
int latest[MAX_NODE];
#define init_stack() (top = -1)
#define push(data) (stack[++top] = (data))
#define pop() (stack[top--])
#define stack_empty() (top < 0)

typedef struct node {
	int weight;	
	int vertex;
	struct node* next;
}node;
typedef struct _head {
	int count;	// 진입차수 
	node* next;
}head;
head network[MAX_NODE];
node* GL[MAX_NODE];
void set_count_indegree(head net[], int V)
{
	int i, j;
	int count;
	node* t;
	for (i = 0; i < V; i++){
		count = 0;
		for (j = 0; j < V; j++)
			for (t = net[j].next; t; t = t->next)
				if (t->vertex == i) count++;
		net[i].count = count;
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
void forward_state(head net[], int V)
{
	int i, j, k;
	node* ptr;
	init_stack();
	set_count_indegree(net, V);
	for (i = 0; i < V; i++) earliest[i] = 0;
	for (i = 0; i < V; i++)
		if (!net[i].count) push(i);
	for (i = 0; i < V; i++) {
		if (!stack_empty()) {
			j = pop();
			for (ptr = net[j].next; ptr; ptr = ptr->next) {
				k = ptr->vertex;
				net[k].count--;
				if (!net[k].count)
					push(k);
				if (earliest[k] < earliest[j] + ptr->weight)
					earliest[k] = earliest[j] + ptr->weight;
			} // for
		} // if
	} // for
}
void backward_state(head net[], int V)
{
	int i, j, k, l;
	node* ptr;
	init_stack();
	set_count_outdegree(net, V);
	for (i = 0; i < V; i++)
		latest[i] = earliest[V - 1];
	for (i = 0; i < V; i++)
		if (!net[i].count) push(i);
	for (i = 0; i < V; i++) {
		if (!stack_empty()) {
			j = pop();
			for (l = 0; l < V; l++) {
				for (ptr = net[l].next; ptr; ptr = ptr->next) {
					if (ptr->vertex == j) {
						k = l;
						net[k].count--;
						if (!net[k].count)
							push(k);
						if (latest[k] > latest[j] - ptr->weight)
							latest[k] = latest[j] - ptr->weight;
					}
				}
			}
		}
	}
}
int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}
FILE* fp;
void set_count_zero(head net[], int V)
{
	int i;
	for (i = 0; i < V; i++)
		net[i].count = 0;
}

void input_adjlist(node* a[], int* V, int* E)
{     /* input network */
	int i, j, w;
	char edge[3];
	node* t;
	printf("\nInput number of Vertex & Edge\n");
	fscanf(fp, "%d %d", V, E);  /* input no of Vertex & Edge */

	set_count_zero(network, *V);

	for (i = 0; i < *V; i++)
		network[i].next = NULL;
	for (i = 0; i < *V; i++)
		a[i] = NULL;
	for (j = 0; j < *E; j++)
	{
		printf("\nInput two Vertex consist of Edge -> ");
		fscanf(fp, "%s %d", edge, &w);

		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(edge[1]);
		t->weight = w;
		t->next = a[name2int(edge[0])];
		
		a[name2int(edge[0])] = t;
	}
}
void print_adjlist(node* a[], int V)
{          /* print network */
	int i;
	node* t;
	for (i = 0; i < V; i++)
	{
		printf("\n%c: ", int2name(i));
		for (t = a[i]; t != NULL; t = t->next) {
			printf("→ %c:%d ", int2name(t->vertex), t->weight);
		}
	}
}

void print_critical_activity(head net[], int V) {
	int i;
	node* t;
	printf("\n");
	char b;
	for (i = 0; i < V; i++)
	{
		t = net[i].next;
		while (t != NULL) {
			printf("<%c, %c>\t%4d %4d %4d\t%c\n",int2name(i), int2name(t->vertex), 
				earliest[i], latest[t->vertex] - t->weight, latest[t->vertex] - t->weight - earliest[i]
			,b = (latest[t->vertex] - t->weight - earliest[i] > 0) ? 'N':'Y');
			t = t->next;
		}
	}
}
void main() {
	int k, V, E;
	fp = fopen("graph_AOE.txt", "rt");
	input_adjlist(GL, &V, &E);
	print_adjlist(GL, V);
	for (k = 0; k < V; k++)
		network[k].next = GL[k];
	forward_state(network, V);
	backward_state(network, V);
	print_critical_activity(network, V);
	fclose(fp);
}