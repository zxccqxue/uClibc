/* vi: set sw=4 ts=4: */
/*
 * access() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <fcntl.h>
#include <unistd.h>

#if defined(__NR_faccessat) && !defined(__NR_access)
int access(const char *pathname, int mode)
{
	return faccessat(AT_FDCWD, pathname, mode, 0);
}

#else
_syscall2(int, access, const char *, pathname, int, mode)
#endif
