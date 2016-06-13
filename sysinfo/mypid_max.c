#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_LINE 100

int main(int argc, char *argv[])
{
    int     fd;
	char    line[MAX_LINE];
	ssize_t n;

	fd = open("/proc/sys/kernel/pid_max", (argc > 1) ? O_RDWR : O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit(1);
	}
	
	n = read(fd, line, MAX_LINE);
	if (n == -1) {
		perror("read");
		exit(1);
	}

	if (argc > 1) {
		printf("Old value: ");
	}
	printf("%.*s", (int) n, line);

	if (argc > 1) {
		if (lseek(fd, 0, SEEK_SET) == -1) {
			perror("lseek");
			exit(1);
		}

		if (write(fd, argv[1], strlen(argv[1])) != strlen(argv[1])) {
			perror("write() failed");
			exit(1);
		}

		system("echo /proc/sys/kernel/pid_max now contains "
			   "`cat /proc/sys/kernel/pid_max`");
	}

    exit(EXIT_SUCCESS);
}
