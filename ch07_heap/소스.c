#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable : 4996)

void upheap(int* a, int k)	// like push a = 배열, k는 index
{
	int v;	
	v = a[k];	// 인덱스의 값 저장
	a[0] = INT_MAX;	// 
	while (a[k / 2] <= v && k / 2 > 0) { // a[k]의 부모노드의 값이 v보다 값이 작거나 같다 그리고 k/2가 0보다 크다
		a[k] = a[k / 2];	// a[k]의 부모노드의 값은 a[k]로 들어간다.
		k /= 2;
	}
	a[k] = v; // 처음에 저장했던 v값을 바뀐 인덱스로 인한 바뀐 노드에 저장한다.
}
void downheap(int* a, int N, int k)	// a는 배열 N은 힙 크기 k는 인덱스
{
	int i, v;
	v = a[k];		// a[k]값 저장
	while (k <= N / 2) {	// k가 N/2(N의 부모 노드)보다 작다면? = k가 index 내에 있다면,
		i = k << 1;	// i는 2*k(k의 자식노드)
		if (i < N && a[i] < a[i + 1]) i++;	// 만약 i가 N 보다 작고 a[i](k자식노드1)가 a[i+1](k자식노드2)보다 작다면 i++
		if (v >= a[i]) break;	// a[k]값이 a[k]자식노드 중 젤 큰노드 보다 크다면 바로 나와서 그대로 나오기
		a[k] = a[i];	// a[k]값에 a[i]값 넣기 
		k = i;	// k 를 i로  = 인덱스 증가 
	}
	a[k] = v;
}
void insert(int* a, int* N, int v) // 삽입과 동시에 제자리를 찾아가게 만듦
{
	a[++(*N)] = v;
	upheap(a, *N);
}
int extract(int* a, int* N)	// a[1] = 맨위거 빼고 정렬하기
{
	int v = a[1];
	a[1] = a[(*N)--];
	downheap(a, *N, 1);
	return v;
}
void heap_sort(int* a, int N) // a는 배열 N은 크기
{
	int i;
	int hn = 0; // # of heap nodes
	for (i = 1; i <= N; i++)
		insert(a, &hn, a[i]);
	for (i = hn; i >= 1; i--)
		a[i] = extract(a, &hn);
}
void main() {
	int buf[16] = { 0, 'T', 'O', 'S', 'O', 'R', 'T', 'A', 'L', 'G', 'O', 'R', 'I', 'T', 'H', 'M' };
	heap_sort(buf, 15);
	for (int i = 1; i <= 15; i++) {
		printf("%c ", buf[i]);
	}
}