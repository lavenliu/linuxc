#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    struct servent  *servent;
    char           **pp;

    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        printf("%s service [protocol]\n", argv[0]);
        exit(1);
    }

    servent = getservbyname(argv[1], argv[2]);
    if (servent == NULL) {
        printf("getservbyname() could not find a matching record\n");
        exit(1);
    }

    printf("Offical name: %s\n", servent->s_name);
    printf("Aliases:       ");
    for (pp = servent->s_aliases; *pp != NULL; pp++) {
        printf(" %s", *pp);
    }

    printf("\n");
    printf("Port:           %u\n", ntohs(servent->s_port));
    printf("Protocol:       %s\n", servent->s_proto);
    
    return 0;
}
