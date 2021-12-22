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
	printf(" → %c\n", int2name(i));
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

void upheap(int h[], int k)// 힙, nheap
{
	int v;
	v = h[k];	// h[1]을 v에
	while (check[h[k / 2]] <= check[v] && k / 2 > 0) { // check[h[k]의 부모 노드] <= check[h[k]] 그리고 k/2 > 0
		h[k] = h[k / 2];	// h[k]에 h[k]의 부모 노드 값
		k /= 2;
	}
	h[k] = v;
}
void downheap(int h[], int k)
{
	int i, v;
	v = h[k];
	while (k <= nheap / 2) {	// 여기서 무한루프 고치기
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
		check[i] = UNSEEN; // 모든 노드를 unseen 으로 초기화 시켜놓기
		parent[i] = 0; // 각 노드의 부모도 초기화 시켜놓기
	}
	for (i = 0; i < V; i++) {
		if (check[i] == UNSEEN) { // i가 unseen 이라면 그것은 root라는 뜻
			parent[i] = -1; // root의 부모는 없으니 -1 로 설정
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
int pq_update(int h[], int v, int p) // 힙, i, Unseen
{
	if (check[v] == UNSEEN) { // 노드 i의 상태가 Unseen이면 root라는 뜻
		h[++nheap] = v;	// h[1] 를 root로 초기화 
		check[v] = p;	// check 값을 -IntMax로 초기화
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
		printf("\nInput two nodes of edge and weight → ");
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
			printf("→ %c:%d ", int2name(t->vertex), t->weight);
		}
	}
}

void main()
{
	int V, E;
	fp = fopen("graph.txt", "rt");
	input_adjlist(G, &V, &E);		// 리스트 입력
	printf("\nOriginal graph\n");
	print_adjlist(G, V);			// 리스트 출력
	printf("\nVisit order of Minimum Spanning Tree\n");
	PFS_adjlist(G, V);				// 
	print_tree(parent, V);
	printf("\nMinimum Cost is ");
	print_cost(check, V);
	fclose(fp);
}
