/**
 *   \file ex01_repdigit.c
 *   \brief Which digit is repeated
 *
 *  Detailed description
 *
 */

#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define N 9

typedef int Bool;

int main(int argc, char *argv[])
{
    Bool     digit_seen[10] = {0};
	int      found_digit[10] = {0};
	int      digit;
	int      i;
	long int n;

	printf("Enter a number: ");
	scanf("%ld", &n);

	while (n > 0) {
		digit = n % 10;
		if (digit_seen[digit]) {
			digit_seen[digit] += 1;
		} else {
			digit_seen[digit] = TRUE;
		}
		n /= 10;
	}

	for (i = 0; i < N; i++) {
		if (digit_seen[i] > 1) {
			printf("Repeated digit(s):");
			printf(" %d", digit_seen[i] + 1);
		}
	}

    return 0;
}
