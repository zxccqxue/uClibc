/* vi: set sw=4 ts=4: */
/*
 * statfs() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <string.h>
#include <sys/param.h>
#include <sys/vfs.h>

#if defined(__NR_statfs64) && !defined(__NR_statfs)
extern __typeof(statfs) __libc_statfs attribute_hidden;

int __libc_statfs(const char *path, struct statfs *buf)
{
	struct statfs64 b;
	int err;

	err = INLINE_SYSCALL(statfs64, 3, path, sizeof(b), &b);

	if (err < 0)
		return -1;

	buf->f_type = b.f_type;
	buf->f_bsize = b.f_bsize;
	buf->f_blocks = b.f_blocks;
	buf->f_bfree = b.f_bfree;
	buf->f_bavail = b.f_bavail;
	buf->f_files = b.f_files;
	buf->f_ffree = b.f_ffree;
	buf->f_namelen = b.f_namelen;
	buf->f_frsize = b.f_frsize;
	buf->f_fsid = b.f_fsid;
	memcpy(buf->f_spare, b.f_spare, sizeof(b.f_spare));

	return err;
}
#if defined __UCLIBC_LINUX_SPECIFIC__ || defined __UCLIBC_HAS_THREADS_NATIVE__
/* statfs is used by NPTL, so it must exported in case */
weak_alias(__libc_statfs, statfs)
#endif

/* For systems which have both, prefer the old one */
#else
extern __typeof(statfs) __libc_statfs attribute_hidden;

#define __NR___libc_statfs __NR_statfs
_syscall2(int, __libc_statfs, const char *, path, struct statfs *, buf)

#if defined __UCLIBC_LINUX_SPECIFIC__ || defined __UCLIBC_HAS_THREADS_NATIVE__
/* statfs is used by NPTL, so it must exported in case */
weak_alias(__libc_statfs, statfs)
#endif

#endif
libc_hidden_def(statfs)
