/* link.c -- implementation of module link.c
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Tue Jun  9 23:17:28 EEST 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <unistd.h>

#include "link.h"
#include "tree.h"

char *
link_info(
        char        *name,
        char        *buf,
        size_t       sz)
{
    ssize_t res = readlink(name, buf, --sz);

    if (res < 0) {
        return NULL;
    }
    buf[res] = '\0';

    return buf;

} /* link_info */
