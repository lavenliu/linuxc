#if ! defined(__sun)
#define _BSD_SOURCE     /* Get getpass() declaration from <unistd.h> */
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE   /* Get crypt() declaration from <unistd.h> */
#endif
#endif
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h>


int main(int argc, char *argv[])
{
    char          *username, *password *encrypted, *p;
    struct passwd *pwd;
    struct spwd   *spwd;

    
    return 0;
}

