/* timeinfo.c -- print time info to buffer.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Jun  7 17:23:10 EEST 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <time.h>

#include "timeinfo.h"

static struct tab_times {
	time_t age;
	char *fmt;
} tab[] = {
	{.age = 86400UL,      .fmt = "%X"          },
	{.age = 7*86400UL,    .fmt = "%a-%H:%M"    },
	{.age = 30*86400UL,   .fmt = "%b/%d-%H:%M" },
	{.age = 365*86400UL,  .fmt = "%Y/%b/%d"    },
	{.age = 3653*86400UL, .fmt = "%Y/%b"       },
	{.age = 0UL,          .fmt = NULL          },
};

char *timeinfo(time_t t, time_t now, char *buf, size_t sz)
{
	struct tm *ts = localtime(&t);	
	struct tab_times *p;
	time_t age = now - t;
	for (p = tab; p->fmt; p++) {
		if (age < p->age) break;
	}
	strftime(buf, sz, p->fmt ? p->fmt : "%Y", ts);
	return buf;
}
