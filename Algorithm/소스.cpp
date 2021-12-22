#include<stdio.h>
#pragma warning ( disable : 4996 )

int main() {

	int n1, n2;
	int ans;

	printf("Input two number(normal) >> ");
	scanf("%d %d", &n1, &n2);

	ans = n1 * (n2 / 10 * 10) + n1 * (n2 % 10);

	printf("answer = %d\n", ans);

	return 0;
}