#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)
#define MAX_NODE 100
int check[MAX_NODE];
int order;
int son_of_root;

typedef struct _node {
	int vertex;
	struct _node* next;
}node;
node* GL[MAX_NODE];
int name2int(char c) {
	return c - 'A';
}
char int2name(int i) {
	return i + 'A';
}
void input_adjlist(node* a[], int* V, int* E) {
	char vertex[3];
	int i, j;
	node* t;
	printf("\nInput number of node & edge\n");
	scanf("%d %d", V, E);
	for (i = 0; i < *V; i++)
		a[i] = NULL;
	for (j = 0; j < *E; j++) {
		printf("\nInput two node consist of edge →");
		scanf("%s", vertex);
		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->next = a[i];
		a[i] = t;
		i = name2int(vertex[1]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[0]);
		t->next = a[i];
		a[i] = t;
	}


}
void print_adjlist(node* a[], int V) {
	node* t;
	printf("\n");
	for (int i = 0; i < V; i++)
	{
		t = a[i];
		printf("%c", int2name(i));
		while (1)
		{
			printf("->%c", int2name(t->vertex));
			if (t->next == NULL)
				break;
			t = t->next;
		}
		printf("\n");
	}
}
/*
A->B
B->D->C->A
C->B
D->B
*/
void visit(int i) {
	printf("%c is visited\n", int2name(i));
}
/*int AP_recur(node* a[], int i)
{
	node* t;
	int min, m;
	check[i] = min = ++order; //check[0] = 1 min = 1, order = 1 
	for (t = a[i]; t != NULL; t = t->next) { // t = a[0]	// t = a[1]
		printf("go to %c\n", int2name(t->vertex));
		if (i == 0 && check[name2int(t->vertex)] == 0) // i = 0 맞음, check[0] = 1 아님 // i는 0맞음 check[1] = 0맞음
			son_of_root++; // son_of_root = 1	// son_of_root = 2
		if (check[name2int(t->vertex)] == 0) { // check[0] = 0 맞음	// check[1] = 0 맞음
			m = AP_recur(a, name2int(t->vertex));	// AP_recur(a, 1) // check[1] = 2 min = 2 order = 2 // check[3] = 3 min = 3 order = 3	// m에 2값이 들어옴
			if (m < min) min = m;	// min = 2이였어서 넘어감
			// 여기가 단절점 판별하는 조건문
			if (m >= check[i] && i != 0)	// m = 2 check[1] = 2 그리고 i = 1임 
				printf("* %c %2d : %d\n", int2name(i), check[i], m);	// * B  1 : 2
			else
				printf("%c %2d : %d\n", int2name(i), check[i], m);
		}
		else // check[3] 돌던중 여기로 옴 그래서 t가 D다음에 연결되어있는 B가 되고 check[1]은 2 이므로 min = 3보다 작다.
			if (check[name2int(t->vertex)] < min)	// check[0] < 1 아님
				min = check[name2int(t->vertex)];	// min = 2가된다. 
	}
	return min;	// min 리턴
}*/
int AP_recur(node* a[], int i)
{
	node* t;
	int min, m;
	check[i] = min = ++order;
	for (t = a[i]; t != NULL; t = t->next) {
		if (i == 0 && check[t->vertex] == 0)
			son_of_root++;
		if (check[t->vertex] == 0) {
			m = AP_recur(a, t->vertex);
			if (m < min) min = m;
			if (m >= check[i] && i != 0)
				printf("* %c %2d : %d\n", int2name(i),
					check[i], m);
			else
				printf("%c %2d : % d\n", int2name(i),
					check[i], m);
		}
		else
			if (check[t->vertex] < min)
				min = check[t->vertex];
	}
	return min;
}

void AP_search(node* a[], int V)
{
	int i, n = 0; 
	node* t;
	for (i = 0; i < V; i++) check[i] = 0;
	order = son_of_root = 0; // order = 0, son_of_root = 0
	AP_recur(a, 0);
	if (son_of_root > 1) printf("* ");
	else printf(" ");
	printf("%c son : %d\n", int2name(0), son_of_root);
}
void main() {
	int V, E;
	input_adjlist(GL, &V, &E);
	print_adjlist(GL, V);

	AP_search(GL, V);
}