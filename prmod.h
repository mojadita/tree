/* prmod.c -- routine to print the mode of a file 'a la' ls(1).
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Jun  7 11:52:10 EEST 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#ifndef _PRMOD_H
#define _PRMOD_H

#include <sys/types.h>

/**
 * prmod prints a mode_t in a format similar to the one used in
 * ls -l.
 *
 * @param mod   is the mode bitset to be printed.
 * @param buff  is the buffer pointer address, wher the string is
 *              constructed.
 * @param bufsz is the size of buffer buff.
 */
char *prmod(int mod, char *buff, size_t bufsz);

#endif /* _PRMOD_H */
