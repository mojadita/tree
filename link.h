/* link.h -- definitions of module link.c
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Tue Jun  9 23:13:02 EEST 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#ifndef _LINK_H
#define _LINK_H

/**
 * This function reads the symbolic link destination and prints
 * it in the output buffer, returning a pointer to it, so it can be
 * used with printf(3).
 *
 * @param name is the name of the symbolic link.
 * @param buf  is the reference to the buffer to store the data
 *             into.
 * @param sz   is the number of bytes available on the buffer.
 * @return     the buffer pointer to be able to chain this call
 *             to a printf() call.
 */
char *link_info(char *name, char *buf, size_t sz);

#endif /* _LINK_H */
