/* help.h -- definitions for the module help.o
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Jun  7 14:10:29 EEST 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#ifndef _HELP_H
#define _HELP_H

/**
 * Shows help page on stdout and exits with exit code.
 *
 * @param code if not zero, it calls exit(3) with code as exit
 *             status to the parent process.  If zero, just shows
 * 			   the page, but returns to calling code.
 * @param progname is the name of the program.  The routine
 *                 inserts the program name in the first message,
 *				   so in case you rename the program or make
 *				   several links to it, it shows the right name.
 */
void do_help(int code, char *progname);

#endif /* _HELP_H */
