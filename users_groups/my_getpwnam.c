#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>


int main(int argc, char *argv[])
{
    struct passwd *pwd;

    if (argc < 2) {
        printf("Usage: %s <username>\n", argv[0]);
        exit(1);
    }
    
    pwd = getpwnam(argv[1]);
    if (pwd == NULL) {
        printf("could not get %s record\n", argv[1]);
        exit(1);
    } else {
        printf("find [ %s ] record, the following is the info:\n", argv[1]);
        printf("Username: %s\n", pwd->pw_name);
        printf("Uid     : %ld\n", (long)pwd->pw_uid);
        printf("Shell   : %s\n", pwd->pw_shell);
    }
    
    return 0;
}
