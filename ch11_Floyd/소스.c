#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable : 4996)
#define MAX_NODE 50
FILE* fp;
int GM[MAX_NODE][MAX_NODE];
int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}
void input_adjmatrix(int g[][MAX_NODE], int* V, int* E) {
	char vertex[3];
	int i, j, k;
	int tmp;
	printf("\nInput number of nodes & edges\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			g[i][j] = 5000;
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
void floyd(int a[][MAX_NODE], int V){
int x, y, k;
for (y = 0; y < V; y++)
	for (x = 0; x < V; x++)
		for (k = 0; k < V; k++)
			if (a[x][y] + a[y][k] < a[x][k])
				a[x][k] = a[x][y] + a[y][k];
}
void main() {
	int V, E;
	fp = fopen("node.txt", "rt");
	input_adjmatrix(GM, &V, &E);
	floyd(GM, V);
	printf("\n");
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			printf("%4d ", GM[i][j]);
		}
		printf("\n");
	}
}