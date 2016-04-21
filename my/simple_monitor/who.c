#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/* A template for the HTML page this module generates.  */
static char *page_template =
    "<html>\n"
    " <head>\n"
    "  <meta http-equiv=\"refresh\" content=\"5\">\n"
    " </head>\n"
    " <body>\n"
    "  <p>Node name: <b>%s</b>.</p>\n"
	"  <p>System name: <b>%s</b>.</p>\n"
	"  <p>Release: %s.</p>\n"
	"  <p>Version: %s.</p>\n"
	"  <p>Machine: %s.</p>\n"
	"  <p>Domain name: %s.</p>\n"	
    " </body>\n"
	"</html>\n";

void module_generate(int fd)
{
	;
}
