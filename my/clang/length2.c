/* Determines the length of a message */

#include <stdio.h>

int main(int argc, char *argv[])
{
    char ch;
	int len = 0;

	printf("Enter your messages: ");
	while ((ch = getchar()) !='\n') {
		len++;
	}

	printf("Your message was %d length long.\n", len);
	
    return 0;
}
