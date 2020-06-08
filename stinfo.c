/* stinfo.c -- routine to print the stat info for a file.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Jun  7 13:24:53 EEST 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <stdio.h>
#include <string.h>

#include "stinfo.h"
#include "prmod.h"
#include "timeinfo.h"

void print_stat_info(int flags, struct stat *st)
{
    char *sep = "[";
    char buff[80];
    if (flags & FLG_SHOW_INODE) {
        printf("%s%9lu", sep,
            (unsigned long) st->st_ino);
        sep = " ";
    }
    if (flags & FLG_SHOW_PERMS) {
        printf("%s%s", sep,
            prmod(st->st_mode, buff, sizeof buff));
        sep = " ";
    }
    if (flags & FLG_SHOW_LINKS) {
        printf("%s%2lu", sep,
            (unsigned long) st->st_nlink);
        sep = " ";
    }
    if (flags & FLG_SHOW_OWNER) {
        printf("%s%7d", sep,
            st->st_uid);
        sep = " ";
    }
    if (flags & FLG_SHOW_GROUP) {
        printf("%s%7d", sep,
            st->st_gid);
        sep = " ";
    }
    if (flags & FLG_SHOW_SIZE) {
        printf("%s%9llu", sep,
            (unsigned long long)st->st_size);
        sep = " ";
    }
    if (flags & FLG_SHOW_ATIME) {
        printf("%s%12s", sep,
            timeinfo(st->st_atime, time(NULL),
                    buff, sizeof buff));
        sep = " ";
    }
    if (flags & FLG_SHOW_MTIME) {
        printf("%s%12s", sep,
            timeinfo(st->st_mtime, time(NULL),
                    buff, sizeof buff));
        sep = " ";
    }
    if (flags & FLG_SHOW_CTIME) {
        printf("%s%12s", sep,
            timeinfo(st->st_ctime, time(NULL),
                    buff, sizeof buff));
        sep = " ";
    }
    fputs("]", stdout);
} /* print_stat_info */
