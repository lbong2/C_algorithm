#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable : 4996)
#define MAX_NODE 100
#define UNSEEN (-INT_MAX)
typedef struct node {
	int vertex;
	int weight;
	struct node* next;
}node;
node* G[MAX_NODE]; // for storing the graph
int check[MAX_NODE]; // for storing the weight
int parent[MAX_NODE]; // for preserving the tree structure 
FILE* fp;
int nheap = 0; // # of elements in the heap
int heap[MAX_NODE];
int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}
void visit(int i) {
	printf(" �� %c\n", int2name(i));
}
void pq_init() {
	nheap = 0;
}
void print_heap(int h[]) {
	int i;
	printf("\n");
	for (i = 1; i <= nheap; i++)
		printf("%c:%d ", int2name(h[i]), check[h[i]]);
}

void upheap(int h[], int k)// ��, nheap
{
	int v;
	v = h[k];	// h[1]�� v��
	while (check[h[k / 2]] <= check[v] && k / 2 > 0) { // check[h[k]�� �θ� ���] <= check[h[k]] �׸��� k/2 > 0
		h[k] = h[k / 2];	// h[k]�� h[k]�� �θ� ��� ��
		k /= 2;
	}
	h[k] = v;
}
void downheap(int h[], int k)
{
	int i, v;
	v = h[k];
	while (k <= nheap / 2) {	// ���⼭ ���ѷ��� ��ġ��
		i = k << 1;
		if (i < nheap && check[h[i]] < check[h[i + 1]]) 
			i++;
		if (check[v] >= check[h[i]]) 
			break;
		h[k] = h[i];
		k = i;
	}
	h[k] = v;
}
void adjust_heap(int h[], int n) {
	int k;
	for (k = n; k >= 1; k--)
		downheap(h, k);
}
void PFS_adjlist(node* g[], int V)
{
	int i;
	node* t;
	pq_init();
	for (i = 0; i < V; i++) {
		check[i] = UNSEEN; // ��� ��带 unseen ���� �ʱ�ȭ ���ѳ���
		parent[i] = 0; // �� ����� �θ� �ʱ�ȭ ���ѳ���
	}
	for (i = 0; i < V; i++) {
		if (check[i] == UNSEEN) { // i�� unseen �̶�� �װ��� root��� ��
			parent[i] = -1; // root�� �θ�� ������ -1 �� ����
			pq_update(heap, i, UNSEEN); // 
			while (!pq_empty()) {
				print_heap(heap);
				i = pq_extract(heap);
				check[i] = -check[i];
				visit(i);
				for (t = g[i]; t != NULL; t = t->next) {
					if (check[t->vertex] < 0)
						if (pq_update(heap, t->vertex, -t->weight))
							parent[t->vertex] = i;
				}
			}
		}
	}
}
int pq_update(int h[], int v, int p) // ��, i, Unseen
{
	if (check[v] == UNSEEN) { // ��� i�� ���°� Unseen�̸� root��� ��
		h[++nheap] = v;	// h[1] �� root�� �ʱ�ȭ 
		check[v] = p;	// check ���� -IntMax�� �ʱ�ȭ
		upheap(h, nheap);	// 
		return 1;
	}
	else {
		if (check[v] < p) {
			check[v] = p;
			adjust_heap(h, nheap);
			return 1;
		}
		else
			return 0;
	}
}
int pq_empty() {
	if (nheap == 0) return 1;
	return 0;
}
int pq_extract(int h[]) {
	int v = h[1];
	h[1] = h[nheap--];
	downheap(h, 1);
	return v;
}
void print_tree(int h[], int size) {
	printf("Son    >> ");
	for (int i = 'A'; i < size + 'A'; i++) {
		printf("%c ", i);
	}

	printf("\nParent >> ");
	for (int i = 0; i < size; i++) {
		printf("%c ", int2name(h[i]));
	}
	printf("\n");
}
void print_cost(int c[], int V) {
	int sum = 0;
	for (int i = 1; i <= V; i++) {
		sum += check[i];
	}
	printf(" %d\n", sum);
}
void input_adjlist(node* g[], int* V, int* E)
{
	char vertex[3];
	int i, j, w;
	node* t;
	printf("\nInput number of nodes & edges\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		g[i] = NULL;
	for (j = 0; j < *E; j++) {
		printf("\nInput two nodes of edge and weight �� ");
		fscanf(fp, "%s %d", vertex, &w);
		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->weight = w;
		t->next = g[i];
		g[i] = t;
		i = name2int(vertex[1]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[0]);
		t->weight = w;
		t->next = g[i];
		g[i] = t;
	}
}
void print_adjlist(node* g[], int V){
	int i;
	node* t;
	for (i = 0; i < V; i++) {
		printf("\n %c : ", int2name(i));
		for (t = g[i]; t != NULL; t = t->next) {
			printf("�� %c:%d ", int2name(t->vertex), t->weight);
		}
	}
}

void main()
{
	int V, E;
	fp = fopen("graph.txt", "rt");
	input_adjlist(G, &V, &E);		// ����Ʈ �Է�
	printf("\nOriginal graph\n");
	print_adjlist(G, V);			// ����Ʈ ���
	printf("\nVisit order of Minimum Spanning Tree\n");
	PFS_adjlist(G, V);				// 
	print_tree(parent, V);
	printf("\nMinimum Cost is ");
	print_cost(check, V);
	fclose(fp);
}
