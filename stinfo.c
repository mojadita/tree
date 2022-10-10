/* stinfo.c -- routine to print the stat info for a file.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Jun  7 13:24:53 EEST 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#include "stinfo.h"
#include "prmod.h"
#include "timeinfo.h"
#include "pwinfo.h"
#include "tree.h"

void print_stat_head(int flags)
{
	if (	(flags & FLG_SHOW_HDR) &&
			(flags & FLAG_SHOW_STAT_INFO))
	{
		const char *sep = "";
		const char *const sep2 = ", ";
		char buff[80];
		putchar('[');
		if (flags & FLG_SHOW_INODE) {
			printf("%s%9s", sep, "inode");
			sep = sep2;
		}
		if (flags & FLG_SHOW_PERMS) {
			printf("%s%10s", sep, "perms");
			sep = sep2;
		}
		if (flags & FLG_SHOW_LINKS) {
			printf("%s%4s", sep, "lnks");
			sep = sep2;
		}
		if (flags & FLG_SHOW_OWNER) {
			printf("%s%6s", sep, "owner");
			sep = sep2;
		}
		if (flags & FLG_SHOW_GROUP) {
			printf("%s%6s", sep, "grp");
			sep = sep2;
		}
		if (flags & FLG_SHOW_SIZE) {
			printf("%s%10s", sep, "size");
			sep = sep2;
		}
		if (flags & FLG_SHOW_ATIME) {
			printf("%s%12s", sep, "atime");
			sep = sep2;
		}
		if (flags & FLG_SHOW_MTIME) {
			printf("%s%12s", sep, "mtime");
			sep = sep2;
		}
		if (flags & FLG_SHOW_CTIME) {
			printf("%s%12s", sep, "ctime");
			sep = sep2;
		}
		fputs("]\n", stdout);
	}
} /* print_stat_head */

void print_stat_info(int flags, struct stat *st)
{
    if (flags & FLAG_SHOW_STAT_INFO) {
		const char *sep = "";
		const char *const sep2 = ", ";
		char buff[80];

		putchar('[');
		if (flags & FLG_SHOW_INODE) {
			printf("%s%9lu", sep,
				(unsigned long) st->st_ino);
			sep = sep2;
		}
		if (flags & FLG_SHOW_PERMS) {
			printf("%s%s", sep,
				prmod(st->st_mode, buff, sizeof buff));
			sep = sep2;
		}
		if (flags & FLG_SHOW_LINKS) {
			printf("%s%4lu", sep,
				(unsigned long) st->st_nlink);
			sep = sep2;
		}
		if (flags & FLG_SHOW_OWNER) {
			printf("%s%6s", sep,
				get_user_name(st->st_uid,
						buff, sizeof buff));
			sep = sep2;
		}
		if (flags & FLG_SHOW_GROUP) {
			printf("%s%6s", sep,
				get_group_name(st->st_gid,
						buff, sizeof buff));
			sep = sep2;
		}
		if (flags & FLG_SHOW_SIZE) {
			printf("%s%10llu", sep,
				(unsigned long long)st->st_size);
			sep = sep2;
		}
		if (flags & FLG_SHOW_ATIME) {
			printf("%s%12s", sep,
				timeinfo(st->st_atime, time(NULL),
						buff, sizeof buff));
			sep = sep2;
		}
		if (flags & FLG_SHOW_MTIME) {
			printf("%s%12s", sep,
				timeinfo(st->st_mtime, time(NULL),
						buff, sizeof buff));
			sep = sep2;
		}
		if (flags & FLG_SHOW_CTIME) {
			printf("%s%12s", sep,
				timeinfo(st->st_ctime, time(NULL),
						buff, sizeof buff));
			sep = sep2;
		}
		fputs("]", stdout);
	}
} /* print_stat_info */
