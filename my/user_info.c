#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    uid_t          uid;
    struct passwd *pwd;

    /* return the effective user id of the calling process */
    uid = geteuid();
    printf("effective user id is: %u\n", uid);

    /* return the real user id of the calling process */
    uid = getuid();
    printf("real user id is     : %u\n", uid);

    if ((pwd = getpwuid(uid)) != NULL) {
        printf("User's login name is         : %s\n", pwd->pw_name);
        printf("User's user id is            : %u\n", pwd->pw_uid);
        printf("User's group id is           : %u\n", pwd->pw_gid);
        printf("User's initial working dir is: %s\n", pwd->pw_dir);
        printf("User's login shell is        : %s\n", pwd->pw_shell);
    } else {
        printf("errno is %d\n", errno);
    }
    return 0;
}
