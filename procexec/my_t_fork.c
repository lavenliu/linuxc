#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int idata = 111;

int main(int argc, char *argv[])
{
    int   istack = 222;
    pid_t child_pid;

    switch (child_pid = fork()) {
    case -1: {
        perror("fork error");
        exit(1);
        break;
    }
        
    case 0: {
        idata *= 3;
        istack *= 3;
        break;
    }
        
    default:
        sleep(3);
        break;
    }

    /* Both parent and child come here */
    printf("PID=%ld %s idata=%d istack=%d\n", (long)getpid(),
           (child_pid == 0) ? "(child) " : "(parent)", idata, istack);
    
    exit(EXIT_SUCCESS);
}
