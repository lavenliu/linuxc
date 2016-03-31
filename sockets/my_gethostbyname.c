#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	struct hostent  *h;
	char           **pp;
	char             str[INET6_ADDRSTRLEN];

	if (argc < 2) {
		printf("usage: %s <domain-name>...\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	for (argv++; *argv != NULL; argv++)	{
		h = gethostbyname(*argv);
		if (h == NULL) {
			fprintf(stderr, "gethostname() failed for '%s': %s\n",
					*argv, hstrerror(h_errno));
			continue;
		}

		printf("Canonical name: %s\n", h->h_name);

		printf("        alias(es):     ");
		for (pp = h->h_aliases; *pp != NULL; pp++)
			printf(" %s", *pp);
		printf("\n");

		printf("        address type:   %s\n",
			   (h->h_addrtype == AF_INET) ? "AF_INET" :
			   (h->h_addrtype == AF_INET6) ? "AF_INET6" : "???");

		if (h->h_addrtype == AF_INET || h->h_addrtype == AF_INET6) {
			printf("        address(es):   ");
			for (pp = h->h_addr_list; *pp != NULL ; pp++)
				printf(" %s", inet_ntop(h->h_addrtype, *pp,
										str, INET6_ADDRSTRLEN));
			printf("\n");
		}
	}

	exit(EXIT_SUCCESS);
}
