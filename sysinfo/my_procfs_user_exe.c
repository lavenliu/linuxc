#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <limits.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>

#define MAX_LINE 1000
typedef enum {FALSE, TRUE} Boolean;


char *username_from_id(uid_t uid)
{
	struct passwd *pwd;

	pwd = getpwuid(uid);
	return (pwd == NULL) ? NULL : pwd->pw_name;
}

uid_t userid_from_name(const char *name)
{
	struct passwd  *pwd;
	uid_t           u;
	char           *endptr;

	if (name == NULL || *name == '\0') {
		return -1;
	}

	u = strtol(name, &endptr, 10);
	if (*endptr == '\0') {
		return u;
	}

	pwd = getpwnam(name);
	if (pwd == NULL) {
		return -1;
	}

	return pwd->pw_uid;
}

int main(int argc, char *argv[])
{
	DIR            *dirp;
	struct dirent  *dp;
	char            path[PATH_MAX];
	char            line[MAX_LINE], cmd[MAX_LINE];
	FILE           *fp;
	char           *p;
	uid_t           uid, checked_uid;
	Boolean         got_name, got_uid;
	

	if (argc < 2 || strcmp(argv[1], "--help") == 0) {
		printf("%s <username>\n", argv[0]);
		exit(1);
	}

	checked_uid = userid_from_name(argv[1]);
	if (checked_uid == -1) {
		printf("Bad username: %s\n", argv[1]);
		exit(1);
	}

	dirp = opendir("/proc");
	if (dirp == NULL) {
		perror("opendir");
		exit(1);
	}

	/* scan entries unser /proc directory */
	for ( ;; ) {
		errno = 0;
		dp = readdir(dirp);
		if (dp == NULL) {
			if (errno != 0) {
				perror("readdir");
				exit(1);
			} else {
				break;
			}
		}

		/* since we are looking for /proc/PID directories, skip
		   entries that are not directories, or don't begin with a
		   digit*/
		if (dp->d_type != DT_DIR || !isdigit((unsigned char) dp->d_name[0])) {
			continue;
		}

		snprintf(path, PATH_MAX, "/proc/%s/status", dp->d_name);
		fp = fopen(path, "r");
		if (fp == NULL) {
			continue;
		}

		got_name = FALSE;
		got_uid = FALSE;
		while (!got_name || !got_uid) {
			if (fgets(line, MAX_LINE, fp) == NULL) {
				break;
			}

			/* The "Name:" line contains the name of the command that
			   this process is running */
			if (strncmp(line, "Name:", 5) == 0) {
				for (p = line + 5; *p != '\0' && isspace((unsigned char) *p); ) {
					p++;
				}
				strncpy(cmd, p, MAX_LINE - 1);
				cmd[MAX_LINE -1] = '\0';        /* Ensure null-terminated */

				got_name = TRUE;
			}

			/* The "Uid:" line contains the real, effective, saved set-,
               and file-system user IDs */

			if (strncmp(line, "Uid:", 4) == 0) {
				uid = strtol(line + 4, NULL, 10);
				got_uid = TRUE;
			}
		}
		fclose(fp);

		/* If we found a username and a UID, and the UID matches,
           then display the PID and command name */

		if (got_name && got_uid && uid == checked_uid)
			printf("%5s %s", dp->d_name, cmd);
	}

    return 0;
}
