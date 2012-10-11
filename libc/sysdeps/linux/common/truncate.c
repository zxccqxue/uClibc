/* vi: set sw=4 ts=4: */
/*
 * truncate() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <unistd.h>


#if defined(__NR_truncate64) && !defined(__NR_truncate)
int truncate(const char *path, __off_t length)
{
	return truncate64(path, length);
}
libc_hidden_def(truncate);

#else
_syscall2(int, truncate, const char *, path, __off_t, length)
libc_hidden_def(truncate)
#endif
