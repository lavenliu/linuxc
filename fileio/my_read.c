#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUF_SIZE 20

int main(int argc, char *argv[])
{
    int     input_fd;
    ssize_t num_read;
    char    buffer[BUF_SIZE+1];

    if (argc != 2 || strcmp(argv[1], "--help") == 0) {
        printf("%s file\n", argv[0]);
        exit(1);
    }

    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1) {
        perror("open error");
        exit(1);
    }
    
    while ((num_read = read(input_fd, buffer, BUF_SIZE)) > 0) {
        buffer[num_read] = '\0';
        printf("The input data was: %s\n", buffer);
        sleep(1);
    }

    if (close(input_fd == -1)) {
        perror("close file fd error");
        exit(1);
    }
    
    return 0;
}
