#include<stdio.h>
#pragma warning ( disable : 4996 )

int main() {
	int A, B, C;
	int ans = 0;

	printf("Input two number(a la russe) >> ");
	scanf("%d %d", &A, &B);

	while (A >= 1) {
		
		if (A % 2) {
			C = B;
			ans += C;
		}
		A >>= 1;
		B <<= 1;
	}
	printf("answer = %d\n", ans);

	return 0;
}