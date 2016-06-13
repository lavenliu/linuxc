#include <stdio.h>

int main(int argc, char *argv[])
{
    int hoge = 5;
	void *hoge_p;

	hoge_p = &hoge;
	// printf("%d\n", *hoge_p);
	printf("%d\n", *(int *)hoge_p);
	
    return 0;
}
