/* vi: set sw=4 ts=4: */
/*
 * utimes() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <sys/time.h>
#include <fcntl.h>
#include <utime.h>
#include <stddef.h>


#if defined(__NR_utimensat) && !defined(__NR_utimes)
int utimes(const char *file, const struct timeval tvp[2])
{
	struct timespec ts[2], *times;
	if (tvp) {
		times = ts;
		times[0].tv_sec = tvp[0].tv_sec;
		times[0].tv_nsec = tvp[0].tv_usec * 1000;
		times[1].tv_sec = tvp[1].tv_sec;
		times[1].tv_nsec = tvp[1].tv_usec * 1000;
	} else {
		times = NULL;
	}

	return utimensat(AT_FDCWD, file, times, 0);
}

#elif defined(__NR_utimes)
_syscall2(int, utimes, const char *, file, const struct timeval *, tvp)
#else
#include <stdlib.h>


int utimes(const char *file, const struct timeval tvp[2])
{
	struct utimbuf buf, *times;

	if (tvp) {
		times = &buf;
		times->actime = tvp[0].tv_sec;
		times->modtime = tvp[1].tv_sec;
	} else {
		times = NULL;
	}
	return utime(file, times);
}
#endif
libc_hidden_def(utimes)
