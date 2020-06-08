/* stinfo.h -- definitions for stinfo.c module.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Jun  7 13:26:52 EEST 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#ifndef _STINFO_H
#define _STINFO_H

#include <sys/stat.h>

/**
 * This routine prints the stat info in ls order, depending on
 * the flags passed to the routine.
 *
 * @param flags are the flags with the fields to be printed.  See
 *              above the flag definitions.
 *
 * @param st    is the struct stat info about the file.
 */
void print_stat_info(int flags, struct stat *st);

#endif /* _STINFO_H */
