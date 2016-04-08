#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void usage(char *progname);

int main(int argc, char *argv[])
{
    int opt;

	if (argc < 2) {
		usage(argv[0]);
		exit(1);
	}

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
			usage(argv[0]);
			break;
		}
	}

	for (; optind < argc; optind++)
		printf("argument: %s\n", argv[optind]);
	
    exit(0);
}


void usage(char *progname)
{
	printf("usage: %s --help to get more information\n", progname);
	printf("\t-i interactive\n");
	printf("\t-l list files\n");
	printf("\t-r read files\n");
	printf("\t-f config file\n");
}
