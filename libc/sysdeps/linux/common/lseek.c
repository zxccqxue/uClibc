/* vi: set sw=4 ts=4: */
/*
 * lseek() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef __NR_lseek
_syscall3(__off_t, lseek, int, fildes, __off_t, offset, int, whence)
#else

__off_t lseek(int fildes, __off_t offset, int whence)
{
#ifdef __UCLIBC_HAS_LFS__
	return lseek64(fildes, offset, whence);
#elif __WORDSIZE == 32
	loff_t result;
#if !defined __NR__llseek && defined __NR_llseek
# define __NR__llseek __NR_llseek
#endif
	off_t high = offset & (1<<31) ? 0xffffffff : 0;

	return (loff_t)(INLINE_SYSCALL(_llseek, 5, fildes, high, (off_t) offset,
				       &result, whence) ?: result);
#endif
}
#endif
#ifndef __LINUXTHREADS_OLD__
libc_hidden_def(lseek)
#else
libc_hidden_weak(lseek)
strong_alias(lseek,__libc_lseek)
#endif
