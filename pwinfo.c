/* pwinfo.c -- get username and group name.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Mon Jun  8 12:53:11 EEST 2020
 * Copyright: (C) Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <stdio.h>
#include <pwd.h>
#include <grp.h>

#include "pwinfo.h"
#include "tree.h"

char *get_user_name(int uid, char *buf, size_t sz)
{
    struct passwd *pw = getpwuid(uid);
    if (pw && !(flags & FLG_NUMERICAL)) {
        snprintf(buf, sz, "%s", pw->pw_name);
    } else {
        snprintf(buf, sz, "%d", uid);
    }
    return buf;
} /* get_user_name */

char *get_group_name(int gid, char *buf, size_t sz)
{
    struct group *gr = getgrgid(gid);
    if (gr && !(flags & FLG_NUMERICAL)) {
        snprintf(buf, sz, "%s", gr->gr_name);
    } else {
        snprintf(buf, sz, "%d", gid);
    }
    return buf;
} /* get_group_name */
