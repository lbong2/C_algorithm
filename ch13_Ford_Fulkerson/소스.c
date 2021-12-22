#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)

#define MAX_NODE 100
#define SOURCE 'S'
#define SINK 'T'
FILE* fp;

int name2int(char c) {
	if (c == SOURCE) return 0;
	if (c == SINK) return 1;
	return c - 'A' + 2;
}
char int2name(int i) {
	if (i == 0) return SOURCE;
	if (i == 1) return SINK;
	return i + 'A' - 2;
}
int Capacity[MAX_NODE][MAX_NODE]; // for capacity
int Flow[MAX_NODE][MAX_NODE]; // for flow
int Residual[MAX_NODE][MAX_NODE]; // for residual network

int check[MAX_NODE]; // for checking the visit
int parent[MAX_NODE]; // for BFS-based tree
int path[MAX_NODE];
int queue[MAX_NODE];
int front, rear;
void init_queue() {
	front = rear = 0;
}
int queue_empty() {
	if (front == rear)
		return 1;
	else
		return 0;
}
void put(int k) {
	queue[rear] = k;
	rear = ++rear % MAX_NODE;
}
int get() {
	int i;
	i = queue[front];
	front = ++front % MAX_NODE;
	return i;
}
void set_path()
{
	int* temp;
	int i, count = 0;
	temp = (int*)calloc(MAX_NODE, sizeof(int));
	i = name2int(SINK);
	while (i >= 0) {
		temp[count] = i;
		i = parent[i];
		count++;
	}
	for (i = 0; i < count; i++)
		path[i] = temp[count - i - 1];
	path[i] = -1;
	free(temp);
}
int get_augment_path(int a[][MAX_NODE],
	int V, int S, int T)
{
	int i, j;
	init_queue();
	for (i = 0; i < V; i++) {
		check[i] = 0;
		parent[i] = -1;
	}
	i = name2int(S);
	if (check[i] == 0) {
		put(i);
		check[i] = 1;
		while (!queue_empty()) {
			i = get();
			if (i == name2int(T)) break;
			for (j = 0; j < V; j++) {
				if (a[i][j] != 0) {
					if (check[j] == 0) {
						put(j);
						check[j] = 1;
						parent[j] = i;
					}
				}
			}
		} // while
	} // if
	set_path();
	if (i == name2int(T)) return 1;
	else return 0;
}
void construct_residual(int c[][MAX_NODE],
	int f[][MAX_NODE],
	int r[][MAX_NODE], int V) {
	int i, j;
	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			r[i][j] = c[i][j] - f[i][j];
}

void clear_matrix(int f[][MAX_NODE], int V) {
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			f[i][j] = 0;
		}
	}
}
void network_flow(int c[][MAX_NODE], int f[][MAX_NODE],
	int r[][MAX_NODE], int V, int S, int T) {
	int i, min;
	clear_matrix(f, V); // f is set to 0
	clear_matrix(r, V); // r is set to 0
	construct_residual(c, f, r, V);
	while (get_augment_path(r, V, S, T)) {
		min = INT_MAX;
		for (i = 1; path[i] >= 0; i++)
			if (min > r[path[i - 1]][path[i]]) 
				min = r[path[i - 1]][path[i]];
		for (i = 1; path[i] >= 0; i++) {
			f[path[i - 1]][path[i]] = f[path[i - 1]][path[i]] + min;
			f[path[i]][path[i - 1]] = -f[path[i - 1]][path[i]];
		}
		construct_residual(c, f, r, V);
	}
}
void input_adjmatrix(int g[][MAX_NODE], int* V, int* E) {
	char vertex[3];
	int i, j, k;
	int tmp;
	printf("\nInput number of nodes & edges\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			g[i][j] = 0;
	for (i = 0; i < *V; i++)
		g[i][i] = 0;
	for (k = 0; k < *E; k++) {
		printf("\nInput two nodes consisting of edge ¡æ ");
		fscanf(fp, "%s %d", vertex, &tmp);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		g[i][j] = tmp;
	}
}
void print_matrix(int c[][MAX_NODE], int V) {

	
	for (int i = 0; i < V; i++) {
		printf("%3c", int2name(i));
	}
	printf("\n");
	for (int i = 0; i < V; i++) {
		printf("%c ", int2name(i));
		for (int j = 0; j < V; j++) {
			printf("%3d", c[i][j]);
		}
		printf("\n");
	}
}
void main() {
	int V, E;
	fp = fopen("capacity.txt", "rt");
	input_adjmatrix(Capacity, &V, &E);
	printf("\n*****Print Capacity*****\n  ");
	print_matrix(Capacity, V);
	network_flow(Capacity, Flow, Residual, V, SOURCE, SINK);
	printf("\n*****Print Flow*****\n  ");
	print_matrix(Flow, V);
	printf("\n*****Print Residual*****\n  ");
	print_matrix(Residual, V);
	printf("\n*****Print Parents*****\n  ");

}