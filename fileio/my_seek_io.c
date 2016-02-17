#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>

/* file permission rw-rw-rw- */
#define FILE_PERMISSION S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
#define GN_ANY_BASE   0100
#define GN_BASE_8     0200      /* Value is expressed in octal */
#define GN_BASE_16    0400      /* Value is expressed in hexadecimal */
#define GN_NONNEG       01      /* Value must be >= 0 */
#define GN_GT_0         02      /* Value must be > 0 */

long getLong(const char *arg, int flags, const char *name);

static void
gnFail(const char *fname, const char *msg, const char *arg, const char *name)
{
    fprintf(stderr, "%s error", fname);
    if (name != NULL)
        fprintf(stderr, " (in %s)", name);
    fprintf(stderr, ": %s\n", msg);
    if (arg != NULL && *arg != '\0')
        fprintf(stderr, "        offending text: %s\n", arg);

    exit(EXIT_FAILURE);
}

static long
getNum(const char *fname, const char *arg, int flags, const char *name)
{
    long res;
    char *endptr;
    int base;

    if (arg == NULL || *arg == '\0')
        gnFail(fname, "null or empty string", arg, name);

    base = (flags & GN_ANY_BASE) ? 0 : (flags & GN_BASE_8) ? 8 :
        (flags & GN_BASE_16) ? 16 : 10;

    errno = 0;
    res = strtol(arg, &endptr, base);
    if (errno != 0)
        gnFail(fname, "strtol() failed", arg, name);

    if (*endptr != '\0')
        gnFail(fname, "nonnumeric characters", arg, name);

    if ((flags & GN_NONNEG) && res < 0)
        gnFail(fname, "negative value not allowed", arg, name);

    if ((flags & GN_GT_0) && res <= 0)
        gnFail(fname, "value must be > 0", arg, name);

    return res;
}


int
getInt(const char *arg, int flags, const char *name)
{
    long res;

    res = getNum("getInt", arg, flags, name);

    if (res > INT_MAX || res < INT_MIN)
        gnFail("getInt", "integer out of range", arg, name);

    return (int) res;
}


int main(int argc, char *argv[])
{
    size_t  len;
    off_t   offset;
    int     fd, ap, j;
    char   *buf;
    ssize_t num_read, num_written;

    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        printf("%s file {r<length>|R<length>|w<string>|s<offset>}...\n",
               argv[0]);
        exit(1);
    }

    fd = open(argv[1], O_RDWR | O_CREAT, FILE_PERMISSION);
    if (fd == -1) {
        perror("open error");
        exit(1);
    }

    for (ap = 2; ap < argc; ap++) {
        switch (argv[ap][0]) {
        case 'r': /* Display bytes at current offset, at text */
        case 'R': /* Display bytes at current offset, in hex */
            len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
            buf = malloc(len);
            if (buf == NULL) {
                perror("malloc");
                exit(1);
            }
            num_read = read(fd, buf, len);
            if (num_read == -1) {
                perror("read error");
                exit(1);
            }

            if (num_read == 0) {
                printf("%s: end-of-file\n", argv[ap]);
            } else {
                printf("%s: ", argv[ap]);
                for (j = 0; j < num_read; j++) {
                    if (argv[ap][0] == 'r') {
                        printf("%c", isprint((unsigned char) buf[j]) ?
                               buf[j]: '?');
                    } else {
                        printf("%02x ", (unsigned int) buf[j]);
                    }
                }
                printf("\n");
            }

            free(buf);
            break;

        case 'w': /* Write string at current offset */
            num_written = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
            if (num_written == -1) {
                perror("write error");
                exit(1);
            }
            printf("%s wrote %ld bytes\n", argv[ap], (long) num_written);
            break;

        case 's':
            offset = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
            if (lseek(fd, offset, SEEK_SET) == -1) {
                perror("lseek error");
                exit(1);
            }
            printf("%s: seek successed\n", argv[ap]);
            break;
        
        default:
            printf("Argument must start with [rRws]: %s\n", argv[ap]);
            break;
        }
    }

    return 0;
}


long
getLong(const char *arg, int flags, const char *name)
{
    return getNum("getLong", arg, flags, name);
}

