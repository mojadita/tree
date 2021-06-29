/* prmod.c -- routine to print the mode of a file 'a la' ls(1).
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Jun  7 11:52:10 EEST 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <stddef.h>
#include <sys/stat.h>

#include "prmod.h"

char *
prmod(
        int          mod,
        char        *buff,
        size_t       bufsz)
{
    char *saved = buff;

#define PR(_ch) do {            \
        if (bufsz > 1) {        \
            *buff++ = (_ch);    \
            bufsz--;            \
        }                       \
    } while(0)

    switch (mod & S_IFMT) {
#define CASE(_c, _ch) case _c: PR(_ch); break;
    CASE( S_IFIFO,  'p');
    CASE( S_IFCHR,  'c');
    CASE( S_IFDIR,  'd');
    CASE( S_IFBLK,  'b');
    CASE( S_IFREG,  '-');
    CASE( S_IFLNK,  'l');
    CASE( S_IFSOCK, 's');
#ifdef S_IFWHT
    CASE( S_IFWHT,  'w');
#endif
#undef CASE
    }

    /* user, read write & exec/suid */
    PR(mod & S_IRUSR ? 'r' : '-');
    PR(mod & S_IWUSR ? 'w' : '-');
    switch(mod & (S_ISUID | S_IXUSR)) {
    case 0: PR('-'); break;
    case S_IXUSR: PR('x'); break;
    case S_ISUID: PR('S'); break;
    case S_IXUSR | S_ISUID:
                  PR('s'); break;
    }

    /* group, read write & exec/guid */
    PR(mod & S_IRGRP ? 'r' : '-');
    PR(mod & S_IWGRP ? 'w' : '-');
    switch(mod & (S_ISGID | S_IXGRP)) {
    case 0: PR('-'); break;
    case S_IXGRP: PR('x'); break;
    case S_ISGID: PR('S'); break;
    case S_IXGRP | S_ISGID:
                  PR('s'); break;
    }

    /* others, read write & exec/sticky bit */
    PR(mod & S_IROTH ? 'r' : '-');
    PR(mod & S_IWOTH ? 'w' : '-');
    switch(mod & (S_ISVTX | S_IXOTH)) {
    case 0: PR('-'); break;
    case S_IXOTH: PR('x'); break;
    case S_ISVTX: PR('T'); break;
    case S_IXOTH | S_ISVTX:
                  PR('t'); break;
    }
    *buff = '\0';
    return saved;
} /* prmod */
