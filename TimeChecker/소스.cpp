#include<Windows.h>
#include<stdio.h>
#pragma warning (disable : 4996)

int main(){
	LARGE_INTEGER freq, start, stop;
	double diff;



	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);


	QueryPerformanceCounter(&stop);
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
	printf("%lf", diff);

	return 0;
}