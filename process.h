/* process.h -- process definitions.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Jun  7 13:44:52 EEST 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#ifndef _PROCESS_H
#define _PROCESS_H

/**** CHAR SEQUENCES TO DRAW THE TREE ********************/

extern char *cs_neck[];
extern char *cs_neck_right[];
extern char *cs_right[];
extern char *cs_shoulder[];
extern char *cs_empty[];
extern int cs;

/*********************************************************/

/**
 * process is a recursive routine to process each node of the
 * filesystem tree.  It uses an internal buffer to print the node
 * dependencies and calls itself to process children of this
 * node.
 *
 * @param fd Is a file descriptor for a directory in order to
 *           call the f* versions (fstat, fdopendir, etc.) of the
 *           system calls to accelerate the tree navigation.
 * @param name is the name of the node we are dealing with.
 * @param pfx1 is the prefix to append to the tree link graph to
 *             print in front of this node.
 * @param pfx2 is the prefix to append to the buffer to print in
 *             front of all this child's children.
 * @param stbuf is the stat(2) of the path we are searching. We
 *              receive it from the parent.
 */
void
process(char *name, char *pfx1, char *pfx2);

#endif /* _PROCESS_H */
