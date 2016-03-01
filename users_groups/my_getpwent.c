#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>

int main(int argc, char *argv[])
{
    struct passwd *pwd;

    while ((pwd = getpwent()) != NULL) {
        printf("%-15s %-5ld %-15s\n", pwd->pw_name, (long)pwd->pw_uid, pwd->pw_shell);
    }
    endpwent();
    
    return 0;
}

