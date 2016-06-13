#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc, char *argv[])
{
    int     input_fd, output_fd, open_flags;
    mode_t  file_perms;
    ssize_t num_read;
    char    buf[BUF_SIZE];

    if (argc !=3 || strcmp(argv[1], "--help") == 0) {
        printf("%s old-file new-file\n", argv[0]);
        exit(1);
    }

    /* Open input files */
    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1) {
        printf("opening file %s\n", argv[1]);
        exit(1);
    }

    /* Open output files */
    open_flags = O_CREAT | O_WRONLY | O_TRUNC;
    file_perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
        S_IROTH | S_IWOTH; /* rw-rw-rw- */
    output_fd = open(argv[2], open_flags, file_perms);
    if (output_fd == -1) {
        printf("opening file %s\n", argv[2]);
        exit(1);
    }

    /* Transfer data until we encounter eof or an error */
    while ((num_read = read(input_fd, buf, BUF_SIZE)) > 0) {
        if (write(output_fd, buf, num_read) != num_read) {
            perror("couldn't write whole buffer");
            exit(2);
        }

    }

    if (num_read == -1) {
        perror("read error");
        exit(1);
    }

    /* close the opened file descriptor */
    if (close(input_fd) == -1) {
        perror("close error");
        exit(1);
    }
    if (close(output_fd) == -1) {
        perror("close error");
        exit(1);
    }
    
    return 0;
}
