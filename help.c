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
        "NAME\n"
        "     %1$s -- tree listing of filesystem paths.\n"
        "\n"
        "SYNOPSIS\n"
        "     %1$s [-AacgHhilmnoprsy] [path ...]\n"
        "\n"
        "DESCRIPTION\n"
        "     The %1$s prints a listing of files as a tree, using box drawing charac-\n"
        "     ters from the UTF set, or the ASCII characters '-', '+', '`' and '|'.\n"
        "     The program also can include the fields of a long listing directory (as\n"
        "     option -l of ls command does) The field are printed depending on the op-\n"
        "     tions used, but they are ordered in the same positions they appear int\n"
        "     the long ls listing.  This is\n"
        "\n"
        "     inode   The inode number is printed using a 9 character field (to main-\n"
        "             tain the alignment so the tree doesn't get garbled)\n"
        "\n"
        "     permissions\n"
        "             The permissions, as they appear in the ls command.\n"
        "\n"
        "     links   The number of hard links pointing to the file/directory inode.\n"
        "\n"
        "     user    The user name is printed (or if the option -n is used, only the\n"
        "             user id number)\n"
        "\n"
        "     group   The group name (or the gid number if the option -n is used)\n"
        "             printed)\n"
        "\n"
        "     size    The size of the file in bytes.\n"
        "\n"
        "     last modification timestamp\n"
        "             The time of the last modification.\n"
        "\n"
        "     last access timestmp\n"
        "             The time of last access.\n"
        "\n"
        "     last inode change\n"
        "             The time of the last inode change.\n"
        "\n"
        "     the file name\n"
        "             This is always printed.\n"
        "\n"
        "OPTIONS\n"
        "     -A      Toggles the switch between using utf-8 box drawing\n"
        "             characters and ASCII characters.  Default is utf-8.\n"
        "\n"
        "     -a      Toggles the inclusion of the last access time of the\n"
        "             file in the listing.\n"
        "\n"
        "     -c      Toggles the inclusion of the last inode modification\n"
        "             to the file in the listing.\n"
        "\n"
        "     -g      Toggles the inclusion of the group name of the file\n"
        "             to the file in the listing.\n"
        "\n"
        "     -H      Toggles the show of hidden files and directories.\n"
        "\n"
        "     -h      Toggles the display of the help screen.\n"
        "\n"
        "     -i      Toggles the inclusion of the i-node number of the\n"
        "             file in the listing.\n"
        "\n"
        "     -l      Toggles the inclusion of the number of links pointing\n"
        "             to this inode in the listing.\n"
        "\n"
        "     -m      Toggles the inclusion of the last modification time\n"
        "             of the file in the listing.\n"
        "\n"
        "     -n      Toggles numerical output (for user id and group id)\n"
        "             of the file in the listing.\n"
        "\n"
        "     -o      Toggles the inclusion of the owner of the file in the\n"
        "             listing.\n"
        "\n"
        "     -p      Toggles the inclusion of the permissions field in the\n"
        "             listing.\n"
        "\n"
        "     -r      Toggles the sorting in reverse collation order of the\n"
        "             files in the listing.\n"
        "\n"
        "     -s      Toggles the inclusion of the size field in the list-\n"
        "             ing.\n"
        "\n"
        "     -y      Toggles symbolic links to print also the pointed\n"
        "             target.\n"
        "\n"
        "AUTHOR\n"
        "     Luis Colorado <luiscoloradourcola@gmail.com>\n"
        "\n",
        progname);
    exit(code);
} /* do_help */
