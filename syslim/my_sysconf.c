#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static void
pr_sysconf(const char *msg, int name)
{
    long lim;

    errno = 0;
    lim = sysconf(name);
    if (lim != -1) {
        printf("%s %ld\n", msg, lim);
    } else {
        if (errno == 0) {
            printf("%s (indeterminate)\n", msg);
        } else {
            perror("sysconf error");
            exit(1);
        }
    }
}

int main(int argc, char *argv[])
{
    pr_sysconf("_SC_ARG_MAX:        ", _SC_ARG_MAX);
    pr_sysconf("_SC_LOGIN_NAME_MAX: ", _SC_LOGIN_NAME_MAX);
    pr_sysconf("_SC_OPEN_MAX:       ", _SC_OPEN_MAX);
    pr_sysconf("_SC_NGROUPS_MAX:    ", _SC_NGROUPS_MAX);
    pr_sysconf("_SC_PAGESIZE:       ", _SC_PAGESIZE);
    pr_sysconf("_SC_RTSIG_MAX:      ", _SC_RTSIG_MAX);
    
    return 0;
}

