#include<stdio.h>
#include<stdlib.h>

#define SIDE 7
int canvas[SIDE][SIDE] = {{ 0, 0, 0, 0, 0, 0, 0 },
						   {0, 0, 0, 0, 0, 0, 0},
					       {0, 0, 0, 1, 0, 0, 0},
						   {0, 1, 1, 1, 1, 0, 0},
						   {0, 0, 0, 0, 0, 1, 0},
						   {0, 0, 0, 0, 0, 0, 0},
						   {0, 0, 0, 0, 0, 0, 0}};

void fill(int x, int y) {
	if (canvas[x][y] > 0 || x < 0 || y < 0 || x >= SIDE || y >= SIDE)
		return;
	canvas[x][y] = 2;
	fill(x - 1, y);
	//fill(x - 1, y - 1);
	fill(x, y - 1);
	//fill(x + 1, y - 1);
	fill(x + 1, y);
	//fill(x + 1, y + 1);
	fill(x, y + 1);
	//fill(x - 1, y + 1);
}
void main() {
	fill(1, 3);
	for (int i = 0; i < SIDE; i++) {
		for (int j = 0; j < SIDE; j++) {
			printf("%-2d", canvas[i][j]);
		}
		printf("\n");
	}
}