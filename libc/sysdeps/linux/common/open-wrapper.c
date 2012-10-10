/* vi: set sw=4 ts=4: */
/*
 * open() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <string.h>
#include <sys/param.h>

#if defined(__NR_open)
#define __NR___syscall_open __NR_open
static __inline__ _syscall3(int, __syscall_open, const char *, file,
		int, flags, __kernel_mode_t, mode)
#endif

/* NPTL has its own implementation */
#if ! defined(__UCLIBC_HAS_THREADS_NATIVE__)
int open(const char *file, int oflag, ...)
{
	mode_t mode = 0;

	if (oflag & O_CREAT) {
		va_list arg;
		va_start(arg, oflag);
		mode = va_arg(arg, mode_t);
		va_end(arg);
	}
#if defined(__NR_openat) && !defined(__NR_open)
	return openat(AT_FDCWD, file, oflag, mode);
#else
	return __syscall_open(file, oflag, mode);
#endif
}

#else
#if defined(__NR_openat) && !defined(__NR_open)
/*
 * Arches that don't support the open() syscall, need to
 * define a symbol for that so other packages that rely
 * on it, can build and run successfully
 */
int open(const char *file, int oflag, ...)
{
	mode_t mode = 0;

	va_list arg;
	va_start(arg, oflag);
	mode = va_arg(arg, mode_t);
	va_end(arg);

	return openat(AT_FDCWD, file, oflag, mode);
}

#else
/*
 * The implementation for open() is defined in the NTPL source files.
 * We must not define it here, to avoid symbol collisions
 */
#endif

#endif /* __UCLIBC_HAS_THREADS_NATIVE__ */

#ifdef __LINUXTHREADS_NEW__
libc_hidden_def(open)
#elif defined(__LINUXTHREADS_OLD__) || \
( defined(__UCLIBC_HAS_THREADS_NATIVE__) && defined(__NR_openat) \
&& !defined(__NR_open) )
libc_hidden_weak(open)
strong_alias(open, __libc_open)
#endif
