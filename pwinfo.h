/* pwinfo.h -- get username and group name.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Mon Jun  8 12:53:11 EEST 2020
 * Copyright: (C) Luis Colorado.  All rights reserved.
 * License: BSD.
 */


/* writes a string representation of the user name of a user
 * (given the uid) in the buffer pointed by buf of size sz.
 *
 * @param uid is the user id of the user.
 * @param buf pointer to a buffer area where to print the name of
 *            the user.
 * @param sz  size of the buffer. 
 * @return    the buffer pointer, to be used directly in
 *            printf().
 */
char *get_user_name(
		int uid, char *buf, size_t sz);

/* writes a string representing the name of the group (given the
 * gid) in the buffer of size sz pointed to by buf.
 *
 * #param gid is the group id of the group.
 * @param buf pointer to a buffer area where to print the result
 *            to.
 * @param sz  size of the buffer pointed to by buf.
 * @return    the buffer pointer, to be able to use it directly
 *            in printf().
 */
char *get_group_name(int gid, char *buf, size_t sz);
