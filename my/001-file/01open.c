#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILENAME "open.c"

int main(int argc, char *argv[])
{
    int fd = open(FILENAME, O_RDONLY);
	if (fd < 0) {
		perror("open failed");
		goto err_open;
	}

	printf("fd = %d\n", fd);
	close(fd);

	return 0;

 err_open:
	return -1;
}
