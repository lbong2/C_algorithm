#include<stdio.h>
#include<stdlib.h>
#pragma warning (disable : 4996)

void upheap(int* a, int k)	// like push a = �迭, k�� index
{
	int v;	
	v = a[k];	// �ε����� �� ����
	a[0] = INT_MAX;	// 
	while (a[k / 2] <= v && k / 2 > 0) { // a[k]�� �θ����� ���� v���� ���� �۰ų� ���� �׸��� k/2�� 0���� ũ��
		a[k] = a[k / 2];	// a[k]�� �θ����� ���� a[k]�� ����.
		k /= 2;
	}
	a[k] = v; // ó���� �����ߴ� v���� �ٲ� �ε����� ���� �ٲ� ��忡 �����Ѵ�.
}
void downheap(int* a, int N, int k)	// a�� �迭 N�� �� ũ�� k�� �ε���
{
	int i, v;
	v = a[k];		// a[k]�� ����
	while (k <= N / 2) {	// k�� N/2(N�� �θ� ���)���� �۴ٸ�? = k�� index ���� �ִٸ�,
		i = k << 1;	// i�� 2*k(k�� �ڽĳ��)
		if (i < N && a[i] < a[i + 1]) i++;	// ���� i�� N ���� �۰� a[i](k�ڽĳ��1)�� a[i+1](k�ڽĳ��2)���� �۴ٸ� i++
		if (v >= a[i]) break;	// a[k]���� a[k]�ڽĳ�� �� �� ū��� ���� ũ�ٸ� �ٷ� ���ͼ� �״�� ������
		a[k] = a[i];	// a[k]���� a[i]�� �ֱ� 
		k = i;	// k �� i��  = �ε��� ���� 
	}
	a[k] = v;
}
void insert(int* a, int* N, int v) // ���԰� ���ÿ� ���ڸ��� ã�ư��� ����
{
	a[++(*N)] = v;
	upheap(a, *N);
}
int extract(int* a, int* N)	// a[1] = ������ ���� �����ϱ�
{
	int v = a[1];
	a[1] = a[(*N)--];
	downheap(a, *N, 1);
	return v;
}
void heap_sort(int* a, int N) // a�� �迭 N�� ũ��
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