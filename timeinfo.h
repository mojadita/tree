/* timeinfo.h -- print time info to buffer.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Jun  7 17:23:10 EEST 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#ifndef _TIMEINFO_H
#define _TIMEINFO_H

char *timeinfo(time_t t, time_t now, char *buf, size_t sz);

#endif /* _TIMEINFO_H */
