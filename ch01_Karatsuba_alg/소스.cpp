#include<stdio.h>
#pragma warning (disable : 4996)



int main() {

	int x = 12345;
	int y = 6789;
	const int B = 100;

	int z0 = (x % B) * (y % B);//4005
	int z2 = (x / B) * (y / B);//8241
	int z1 = ((x / B) + (x % B)) * ((y % B) + (y / B)) - z0 - z2;//13962

	printf("z0 = %d\nz1 = %d\nz2 = %d\n", z0, z1, z2);
	printf("x * y = %d\n", (z2*B*B + z1*B + z0));

	return 0;
}