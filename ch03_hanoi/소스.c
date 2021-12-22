#include <stdio.h>
#define INDEX 100

int top;
int stack[INDEX];
#define init_stack() (top = -1)
#define push(data) (stack[++top] = (data))
#define pop() (stack[top--])
#define is_stack_empty() (top < 0)


void hanoi(int n, int from, int by, int to) {
	if (n == 1) {
		printf("move from %d to %d\n", from, to);
	}
	else {
		hanoi(n - 1, from, to, by);
		printf("move from %d to %d\n", from, to);
		hanoi(n - 1, by, from, to);
	}
}
void move(int a, int c)
{
	printf("move from %d to %d\n", a, c);
}


void nr_hanoi(int n, int from, int by, int to)
{
    int done = 0;
    init_stack();   
    while (!done)
    {
        while (n > 1)
        {
            push(to); 
            push(by);
            push(from);
            push(n);
            n--;
            push(to); 
            to = by;
            by = pop();
        }


        move(from, to);  
        if (!is_stack_empty())
        {
            n = pop();
            from = pop();
            by = pop();
            to = pop();
            move(from, to);
            n--;
            push(from); 
            from = by;
            by = pop();
        }
        else
            done = 1; 
    }
}


void main() {
    printf("===Reculsive===\n");
	hanoi(4, 1, 2, 3);
    printf("\n===non-Reculsive===\n");
	nr_hanoi(4, 1, 2, 3);
}