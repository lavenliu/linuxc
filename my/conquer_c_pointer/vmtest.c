#include <stdio.h>

int main(int argc, char *argv[])
{
    int  laven;
	char buf[256];

	printf("&laven... %p\n", &laven);

	printf("Input Intial value.\n");
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%d", &laven);

	for ( ;; ) {
		printf("laven... %d\n", laven);
		getchar();
		laven++;
	}
	
    return 0;
}
