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
#include "tree.h"
#include "stinfo.h"
#include "link.h"

#define MAX_PREFIX      (65536)
#define DEFCAP          (10)
#define DEF_PATH_CAP    (16)

static char buffer[MAX_PREFIX];
static char *buffer_pos   = buffer;
static int  buffer_remain = sizeof buffer;

/**** CHAR SEQUENCES TO DRAW THE TREE ********************/
char *cs_neck[]        = { "---", "\u2500\u2500" };
char *cs_neck_right[]  = { " +-", " \u251c" };
char *cs_right[]       = { " | ", " \u2502" };
char *cs_shoulder[]    = { " `-", " \u2514" };
char *cs_empty[]       = { "   ", "  " };
int cs = 1;
/*********************************************************/

/* functions to allow ordering of names in a directory, on name,
 * in ascending or descending collation order.  */
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

/* the following growable array is used to save path component
 * names in a stack in order to be able to print them when an
 * error is found. As the process() function is recursive, only
 * an array to the pointers of the names is needed.  An iteration
 * over the array in index order permits to reconstruct the
 * complete file name, from the command line argument. */
static char **path;
static size_t path_n;
static size_t path_cap;

/* prints the above path list of names in the specified buffer.
 * The function returns a pointer to the buffer, to allow to use
 * it directly in the printf parameter list.  */
static char *
print_path(char *buf, size_t sz)
{
    char *sep = "", *saved_buf = buf;
    size_t n;
    for (int i = 0; i < path_n; i++) {
        n = snprintf(buf, sz, "%s%s", sep, path[i]);
        sep = "/";
        if (n > 0) {
            buf += n;
            sz -= n;
        }
    }
    return saved_buf;
} /* print_path */

/* The node processing function.  */
void
process(char *name,
        char *pfx1,
        char *pfx2)
{

    /* strip trailing '/' (only if name is not "/") */
    if (strcmp(name, "/") != 0){
        int l = strlen(name);
        while (l > 1 && name[--l] == '/')
            name[l] = '\0';
    }

    /* work buffer to build the complete path name, in case we
     * have to signal an error.  */
    static char work_buffer[65536];

    if (path == NULL) {
        path_cap = DEF_PATH_CAP;
        path = calloc(path_cap, sizeof *path);
        path_n = 0;
    }
    if (path_n == path_cap) {
        path_cap <<= 1;
        path = realloc(path, path_cap * sizeof *path);
    }

    path[path_n++] = strcmp(name, "/")
            ? name          /* non-root directory */
            : "";           /* root directory */

    struct stat stbuf_node;
    int res = lstat(name, &stbuf_node);

    /* print the stat info (we use another line) */
    if (flags & FLAG_SHOW_STAT_INFO) {
        print_stat_info(flags, &stbuf_node);
    }

    /* print our own prefix and name */
    printf("%s%s %s", buffer, pfx1, name);

    if ((flags & FLG_SHOW_LINK) && S_ISLNK(stbuf_node.st_mode)) {
        printf(" -> %s", link_info(name,
                work_buffer, sizeof work_buffer));
    }
    puts(""); /* end of line */

    /* if is dir, recurse, with all of its children. */
    if (S_ISDIR(stbuf_node.st_mode)) {

        /* ... and add the prefix for children to the buffer */
        int n = snprintf(buffer_pos, buffer_remain, "%s", pfx2);

        /* save both to restore later */
        char *saved_pos       = buffer_pos;
        int   saved_remain    = buffer_remain;

        /* position to the end of the buffer */
        buffer_pos           += n;
        buffer_remain        -= n;

        DIR *d = opendir(name);
        if (!d) {
            WARN("opendir '%s'",
                print_path(work_buffer, sizeof work_buffer));
            goto restore;
        }

        if (chdir(name) < 0) {
            WARN("chdir to '%s'",
                print_path(work_buffer, sizeof work_buffer));
            closedir(d);
            goto restore;
        }

        /* read directory entries */
        struct dirent *de     = NULL;
        char **list           = calloc(DEFCAP, sizeof *list);
        size_t list_cap       = DEFCAP;
        size_t list_len       = 0;
        while ((de = readdir(d)) != NULL) {

            if ( (strcmp(de->d_name, ".")  == 0)
               ||(strcmp(de->d_name, "..") == 0))
            {
                continue;
            }
            if ( (flags & FLG_NOSHOW_HIDDEN)
              && (de->d_name[0] == '.') )
            {
                continue;
            }

            /* if we are full, grow the array. */
            if (list_len == list_cap) {
                list_cap    <<= 1;
                list          = realloc(
                        list, list_cap * sizeof *list);
            }

            if (flags & FLG_SHOW_DIR) {
                struct stat stbuf_chld;
                int res = lstat(de->d_name, &stbuf_chld);
                if (res < 0) {
                    WARN("lstat: %s: %s\n",
                            print_path(work_buffer, sizeof work_buffer),
                            strerror(errno));
                    continue;
                }
                if (!S_ISDIR(stbuf_chld.st_mode)) {
                    continue;
                }
            }
            list[list_len++] = strdup(de->d_name);
        }
        closedir(d);

        if (flags & FLG_SORT) {
            qsort(list, list_len, sizeof *list,
                    flags & FLG_REVERSE ? desc : asc);
        }

        /* process each entry */
        for (int i = 0; i < list_len; i++) {
            process(list[i],
                (i < list_len - 1
                    ? cs_neck_right     /* " |- " */
                    : cs_shoulder)[cs], /* " `- " */
                (i < list_len - 1
                    ? cs_right          /* " |  " */
                    : cs_empty)[cs]);   /* "    " */
        }

        /* free used memory */
        for (int i = 0; i < list_len; i++)
            free(list[i]);
        free(list);

        /* return back */
        chdir("..");

restore:
        /* restore the position of prefix */
        buffer_pos = saved_pos;
        buffer_remain = saved_remain;
        *buffer_pos = '\0';
    }

end: /* clean path */

    --path_n;
    if (path_n == 0) {
        free(path);
        path = NULL;
    }
} /* process */
