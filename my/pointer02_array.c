#include <stdio.h>

int main(int argc, char *argv[])
{
    // initialize an array of ints
	int numbers[5] = {1,2,3,4,5};
	int i = 0;

	// print the address of the array variable
	printf("numbers = %p\n", numbers);

	// print addresses of each array index
	do {
		printf("numbers[%u] = %p\n", i, (void *)(&numbers[i]));
		i++;
	} while(i < 5);

	// print the size of the array
	printf("sizeof(numbers) = %lu\n", sizeof(numbers));
	
    return 0;
}
