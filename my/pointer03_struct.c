#include <stdio.h>

int main(int argc, char *argv[])
{
    struct measure {
		char category;
		int width;
		int height;
	};

	// declare and populate the struct
	struct measure ball;
	ball.category = 'C';
	ball.width = 5;
	ball.height = 3;

	// print the addresses of the struct and its members
	printf("address of ball = %p\n", (void *)(&ball));
	printf("address of ball.category = %p\n", (void *)(&ball.category));
	printf("address of ball.width = %p\n", (void *)(&ball.width));
	printf("address of ball.height = %p\n", (void *)(&ball.height));

	// print the size of the struct
	printf("sizeof(ball) = %lu\n", sizeof(ball));
	
    return 0;
}
