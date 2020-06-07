/* help.c -- print a help screen.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Jun  7 14:16:53 EEST 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <stdio.h>
#include <stdlib.h>

#include "help.h"

void
do_help(                    /* prints a help message and exits.  */
        int     code,       /* exit code, if 0, function call
                             * returns, instead of exit(3).  */
        char   *progname)   /* program name. */
{
    printf(
            "Usage: %s [ opts ] [ path ... ]\n"
            "Opts:\n"
            "  -h  This help screen is shown.\n"
            "  path A directory or file to be shown, each directory is shown\n"
            "     with a tree starting down on path as its root, and showing\n"
            "     all directory/files underneath.\n",
            progname);
    if (code)
        exit(code);
} /* do_help */
