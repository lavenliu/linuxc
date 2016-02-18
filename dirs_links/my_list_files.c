#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

typedef enum { FALSE, TRUE } Boolean;

static void
list_files(const char *dirpath)
{
    DIR *dirp;
    struct drient *dp;
    Boolean is_current;

    is_current = strcmp(dirpath, ".") == 0;

    dirp = opendir(dirpath);
    if (dirp == NULL) {
        perror("opendir error");
        exit(EXIT_FAILURE);
    }

    /* for each entry in this directory, print directory + filename */
    for ( ;; ) {
        errno = 0;
        dp = readdir(dirp);
        if (dp == NULL) {
            break;
        }

        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            continue;
        }

        if (!is_current) {
            printf("%s/", dirpath);
        }
        printf("%s\n", dp->d_name);
    }

    if (errno != 0) {
        perror("readdir error");
        exit(EXIT_FAILURE);
    }

    if (closedir(dirp) == -1) {
        perror("closedir error");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[])
{
    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        printf("%s [dir-path...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (argc == 1) {
        list_files(".");
    } else {
        for (argv++; *argv; argv++) {
            list_files(*argv);
        }
    }
    
    return 0;
}
