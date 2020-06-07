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

extern int flags; /* config flags */

#endif /* _TREE_H */
