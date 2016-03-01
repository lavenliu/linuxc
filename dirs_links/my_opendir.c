#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>


int my_readdir(const char *path)
{
    DIR           *dir;
    struct dirent *ptr;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir error");
        return -1;
    }

    while ((ptr = readdir(dir)) != NULL) {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) {
            continue;
        } else {
            printf("file name: %s\n", ptr->d_name);            
        }
    }

    closedir(dir);

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("usage: %s <target path>\n", argv[0]);
        exit(1);
    }

    if (my_readdir(argv[1]) < 0) {
        exit(1);
    }
    
    return 0;
}

