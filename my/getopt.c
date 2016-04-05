#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void usage(void);

int main(int argc, char *argv[])
{
    int opt;

	while ((opt = getopt(argc, argv, ":if:lr")) != -1) {
		switch (opt) {
		case 'i':
		case 'l':
		case 'r':
			printf("option: %c\n", opt);
			break;
			
		case 'f':
			printf("filename: %s\n", optarg);
			break;
			
		case ':':
			printf("option needs a value\n");
			break;

		case '?':
			printf("unknown option: %c\n", optopt);
			usage();
			break;
		}
	}

	for (; optind < argc; optind++)
		printf("argument: %s\n", argv[optind]);
	
    exit(0);
}


void usage(void)
{
	printf("usage: getopt --help to get more information\n");
	exit(1);
}
