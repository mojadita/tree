/* tree.c -- tree like directory listing.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Jun  7 09:40:04 EEST 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "help.h"
#include "process.h"
#include "stinfo.h"
#include "tree.h"

/* this variable is global. */
int flags = FLG_NOSHOW_HIDDEN
		  | FLG_SORT
		  | FLG_SHOW_LINK;

int
main(int argc, char **argv)
{
    int opt;

    while((opt = getopt(argc, argv, ".AacdgHhilmnoprSsy")) >= 0) {
        switch(opt) {
            /* illegal option */
        case '?': do_help(1, argv[0]);
            /* NOTREACHED */
		case '.': flags ^= FLG_NOSHOW_HIDDEN; break;
		case 'A': cs    ^= 1;                 break;
		case 'a': flags ^= FLG_SHOW_ATIME;    break;
		case 'c': flags ^= FLG_SHOW_CTIME;    break;
        case 'd': flags ^= FLG_SHOW_DIR;      break;
        case 'g': flags ^= FLG_SHOW_GROUP;    break;
        case 'H': flags ^= FLG_SHOW_HDR;      break;
        case 'h': do_help(0, argv[0]);        break;
        case 'i': flags ^= FLG_SHOW_INODE;    break;
        case 'l': flags ^= FLG_SHOW_LINKS;    break;
        case 'm': flags ^= FLG_SHOW_MTIME;    break;
        case 'n': flags ^= FLG_NUMERICAL;     break;
        case 'o': flags ^= FLG_SHOW_OWNER;    break;
        case 'p': flags ^= FLG_SHOW_PERMS;    break;
        case 'r': flags ^= FLG_REVERSE;       break;
        case 'S': flags ^= FLG_SORT;          break;
        case 's': flags ^= FLG_SHOW_SIZE;     break;
        case 'y': flags ^= FLG_SHOW_LINK;     break;
        } /* switch */
    } /* while */

    argc -= optind;
    argv += optind;

    switch(argc) {

    case 0:
        print_stat_head(flags);
		process(".", cs_neck[cs], cs_empty[cs]);
		break;

    case 1:
        print_stat_head(flags);
		process(*argv, cs_neck[cs], cs_empty[cs]);
		break;

    default: {
            /* save current dir */
            DIR* d = opendir(".");

            for (int i = 0; i < argc; i++) {

                print_stat_head(flags);

                process(argv[i],
                    cs_neck[cs], cs_empty[cs]);

                /* return to saved dir,
                 * to continue */
                fchdir(dirfd(d));
            } /* for */

            closedir(d);
            break;
        } /* default: */
    } /* switch */

    exit(0);
} /* main */
