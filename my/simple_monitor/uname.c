#ifdef __linux__
#define _GNU_SOURCE
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

#include "server.h"

/* A template for the HTML page this module generates.  */
static char *page_template =
    "<html>\n"
    " <head>\n"
    "  <meta http-equiv=\"refresh\" content=\"5\">\n"
    " </head>\n"
    " <body>\n"
    "  <p>Node name: <b>%s</b>.</p>\n"
	"  <p>System name: <b>%s</b>.</p>\n"
	"  <p>Release: <b>%s</b>.</p>\n"
	"  <p>Version: <b>%s</b>.</p>\n"
	"  <p>Machine: <b>%s</b>.</p>\n"
	"  <p>Domain name: <b>%s</b>.</p>\n"	
    " </body>\n"
	"</html>\n";


void module_generate(int fd)
{
	struct utsname  uts;
	FILE           *fp;

	if (uname(&uts) == -1) {
        perror("uname");
        exit(1);
    }
	
	fp = fdopen(fd, "w");
	assert(fp != NULL);
	fprintf(fp, page_template,
			uts.nodename,
			uts.sysname,
			uts.release,
			uts.version,
			uts.machine,
			uts.domainname);
	fflush(fp);
}
