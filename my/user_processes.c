#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define FILENAME_MAX_LEN         64
#define READ_MAX_LEN            512
#define TOKEN_MAX_LEN            20
#define CMDLINE_FLIENAME_MAX_LEN 64

void err_exit(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
}

void print_proc_by_login(char *login)
{
    char           filename[FILENAME_MAX_LEN];
    char           read_buf[READ_MAX_LEN};
    char          *line;
    char           token[TOKEN_MAX_LEN];
    char           token1[TOKEN_MAX_LEN];
    char           cmdline_file[CMDLINE_FLIENAME_MAX_LEN];
    struct passwd *pwd;
    DIR           *dirp;
    struct dirent *direntp;
    int            fd, i;
    size_t         num_bytes_read;
    uid_t          uid;
    char           uid_str[] = "Uid:";

    if ((pwd = getpwnam(login)) != NULL) {
        printf("Processes run by %s\n", login);
        printf("\nPID COMMAND\n");

        uid = pwd->pw_uid;
        
        dirp = opendir("/proc");
        if (dirp != NULL) {
            while ((direntp = readdir(dirp)) != NULL) {
                if (atoi(direntp->d_name) != 0) {
                    sprintf(filename, "/proc/%s/status", direntp->d_name);
                    fd = open(filename, O_RDONLY);
                }
            }
        }
    }
}
