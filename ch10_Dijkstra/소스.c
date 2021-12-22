#include<stdio.h>
#include<stdlib.h>
#define INFINITE 1000 
#pragma warning(disable : 4996)
#define MAX_NODE 11
int parent[MAX_NODE];
int GM[MAX_NODE][MAX_NODE] = {{ 0, 4, 1, 2, 3, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE },
				{4, 0, INFINITE, INFINITE, INFINITE, 4 ,INFINITE, INFINITE, INFINITE, INFINITE, INFINITE },
				{1, INFINITE, 0, 2, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE },
				{ 2, INFINITE, 2, 0, INFINITE, 4, 4, INFINITE, INFINITE, INFINITE, INFINITE },
				{ 3, INFINITE, INFINITE, INFINITE, 0, 4, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE},
				{ INFINITE, 4, INFINITE, 4, 4, 0, INFINITE, INFINITE, INFINITE, 2, 4},
				{ INFINITE, INFINITE, INFINITE, 4, INFINITE, INFINITE, 0, 3, 3, 4, INFINITE },
				{ INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 3, 0, 2, INFINITE, INFINITE },
				{ INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 3, 2, 0, 2, INFINITE },
				{ INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 2, 4, INFINITE, 2, 0, 1},
				{ INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 4, INFINITE, INFINITE, INFINITE, 1, 0}};

int distance[MAX_NODE];
int check[MAX_NODE];
int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
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


void print_distance(int* distance, int x, int V) {
	printf("%c ", int2name(x));
	for (int i = 0; i < V; i++) {
		printf("%4d ", distance[i]);
	}
	printf("\n");
}
void dijkstra(int a[][MAX_NODE], int s, int V) {
	int x = 0, y, d;
	int i, checked = 0;
	for (x = 0; x < V; x++) {
		distance[x] = a[s][x];
		if (x != s) parent[x] = s;
	}
	check[s] = 1;
	checked++;
	print_distance(distance, s, V);
	while (checked < V) {
		x = 0;
		while (check[x]) x++;
		for (i = x; i < V; i++)
			if (check[i] == 0 && distance[i] < distance[x]) x = i;
		check[x] = 1;
		checked++;
		for (y = 0; y < V; y++) {
			if (x == y || a[x][y] >= INFINITE || check[y]) continue;
			d = distance[x] + a[x][y];
			if (d < distance[y]) {
				distance[y] = d;
				parent[y] = x;
			}
	}
	print_distance(distance, x, V);
	}
}
void main()
{

	dijkstra(GM, name2int('F'), MAX_NODE);
	printf("\n");
	for (int i = 0; i < MAX_NODE; i++) {
		printf("%c, %c \n", int2name(i),int2name(parent[i]));
	}
	for (int i = 0; i < MAX_NODE; i++) {
		printf("%c ", int2name(i));
	}
	printf("\n");
	for (int i = 0; i < MAX_NODE; i++) {
		printf("%d ", distance[i]);
	}
}