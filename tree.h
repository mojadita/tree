/* tree.h -- global definitions for all modules.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Jun  7 14:08:45 EEST 2020
 * Copyright: (C) 2020 Luis colorado.  All rights reserved.
 * License: BSD.
 */
#ifndef _TREE_H
#define _TREE_H

#define F(_fmt) __FILE__":%d:%s:"_fmt,__LINE__,__func__

#define WARN(_fmt, ...) fprintf(stderr,         \
            F(_fmt),##__VA_ARGS__)

#define ERR(_code, _fmt, ...)                   \
    do {                                        \
        fprintf(stderr,                         \
                F(_fmt),##__VA_ARGS__);         \
        exit(_code);                            \
    } while(0)

#define FLG_SHOW_ATIME      (1 <<  0)
#define FLG_SHOW_CTIME      (1 <<  1)
#define FLG_SHOW_GROUP      (1 <<  2)
#define FLG_SHOW_INODE      (1 <<  3)
#define FLG_SHOW_LINKS      (1 <<  4)
#define FLG_SHOW_MTIME      (1 <<  5)
#define FLG_SHOW_OWNER      (1 <<  6)
#define FLG_SHOW_PERMS      (1 <<  7)
#define FLG_SHOW_SIZE       (1 <<  8)
#define FLG_SHOW_LINK		(1 <<  9)

#define FLG_NUMERICAL       (1 << 10)
#define FLG_REVERSE         (1 << 11)
#define FLG_SORT            (1 << 12)

#define FLAG_SHOW_STAT_INFO (FLG_SHOW_ATIME | FLG_SHOW_CTIME \
                           | FLG_SHOW_GROUP | FLG_SHOW_INODE \
                           | FLG_SHOW_LINKS | FLG_SHOW_MTIME \
                           | FLG_SHOW_OWNER | FLG_SHOW_PERMS \
                           | FLG_SHOW_SIZE )

extern int flags; /* config flags */

#endif /* _TREE_H */
