/* ugid_functions.h

   Header file for ugid_functions.c.
*/
#ifndef UGID_FUNCTIONS_H
#define UGID_FUNCTIONS_H

#include "tlpi_hdr.h"

char *username_from_id(uid_t uid);

uid_t userid_from_name(const char *name);

char *groupname_from_id(gid_t gid);

gid_t groupid_from_name(const char *name);

#endif
