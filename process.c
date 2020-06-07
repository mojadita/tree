/* process.c -- process a path element.  This routine is
 * recursive and calls to itself on directories to get and
 * process the info from them.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Jun  7 13:42:33 EEST 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "process.h"
#include "stinfo.h"
#include "tree.h"

#define MAX_PREFIX      (8192)
#define DEFCAP          10

static char buffer[MAX_PREFIX];
static char *buffer_pos   = buffer;
static int  buffer_remain = sizeof buffer;

static int asc(const void *a, const void *b)
{
	char *const *A = a, * const *B = b;
	return strcmp(*A, *B);
}

static int desc(const void *a, const void *b)
{
	char *const *A = a, *const *B = b;
	return strcmp(*B, *A);
}

void
process(char *name, char *pfx1, char *pfx2)
{
    /* stat the file, if fd == -1, then we are at a root
     * node, and we don't have a directory file descriptor
     * yet, just use normal stat for it.  Otherwise, use
     * the fstat(2) call using the file descriptor of the
     * parent directory. */
	struct stat stbuf;
	int res = stat(name, &stbuf);
	if (res < 0) {
		WARN("cannot stat %s: ERROR %d: %s\n",
			name, errno, strerror(errno));
		return;
	}

	/* print the stat info */
	print_stat_info(flags, &stbuf);

    /* print our own prefix */
	printf("%s%s ", buffer, pfx1);

	/* print the name of the file */
	printf("%s", name);

    puts("");

	/* if is dir, recurse, with all of its children. */
	if (S_ISDIR(stbuf.st_mode)) {

		/* ... and add the prefix for children to the buffer */
		int n = snprintf(buffer_pos, buffer_remain, "%s", pfx2);

		DIR *d = opendir(name);
		if (!d) {
			WARN("cannot read directory %s: ERROR %d: %s\n",
				name, errno, strerror(errno));
			return;
		}
		if (chdir(name) < 0) {
			WARN("cannot chdir to %s: ERROR %d: %s\n",
				name, errno, strerror(errno));
		}

		/* save both to restore later */
		char *saved_pos       = buffer_pos;
		int   saved_remain    = buffer_remain;

		/* position to the end of the buffer */
		buffer_pos           += n;
		buffer_remain        -= n;

		/* read directory entries */
		struct dirent *de     = NULL;
		char **list           = calloc(DEFCAP, sizeof *list);
		size_t list_cap       = DEFCAP;
		size_t list_size      = 0;
		while ((de = readdir(d)) != NULL) {
			/* skip . and .. */
			if (strcmp(de->d_name, ".") == 0 ||
				strcmp(de->d_name, "..") == 0)
				continue;

			/* if we are full, grow the array. */
			if (list_size == list_cap) {
				list_cap    <<= 1;
				list          = realloc(list, list_cap * sizeof *list);
			}

			/* add element */
			list[list_size++] = strdup(de->d_name);
		}
		closedir(d);

		/* TODO: sorting */
		qsort(list, list_size, sizeof *list, asc);

		/* process each entry */
		for (int i = 0; i < list_size; i++) {
			process(list[i],
				i < list_size - 1 ? "  \u251c\u2500" : "  \u2514\u2500",
				i < list_size - 1 ? "  \u2502 " : "    ");
		}
			

		/* return back */
		chdir("..");
		buffer_pos = saved_pos;
		buffer_remain = saved_remain;
		*buffer_pos = '\0';
	}
} /* process */
