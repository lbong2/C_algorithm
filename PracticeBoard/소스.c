#include<stdio.h>
#pragma warning (disable : 4996)

void right_hand_on_wall(int *dir) {
	return dir;
}
void main()
{
	int dir = 0;

	right_hand_on_wall(&dir);

}