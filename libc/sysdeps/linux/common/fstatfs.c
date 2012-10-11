/* vi: set sw=4 ts=4: */
/*
 * fstatfs() for uClibc
 *
 * Copyright (C) 2000-2006 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include <sys/syscall.h>
#include <sys/vfs.h>
#include <string.h>

#if ! defined(__USE_FILE_OFFSET64)
extern int fstatfs (int __fildes, struct statfs *__buf)
     __THROW __nonnull ((2));
#else
# ifdef __REDIRECT_NTH
extern int __REDIRECT_NTH (fstatfs, (int __fildes, struct statfs *__buf),
	fstatfs64) __nonnull ((2));
# else
#  define fstatfs fstatfs64
# endif
#endif

extern __typeof(fstatfs) __libc_fstatfs attribute_hidden;
#ifdef __NR_fstatfs
#define __NR___libc_fstatfs __NR_fstatfs
_syscall2(int, __libc_fstatfs, int, fd, struct statfs *, buf)
#else
/* Backwards compatibility for __libc_fstatfs */
int __libc_fstatfs (int __fildes, struct statfs *__buf)
{
	struct statfs64 b;
	int err;

	err = INLINE_SYSCALL(fstatfs64, 3, __fildes, sizeof(b), &b);

	if (err < 0)
		return -1;

	memset(__buf, 0x00, sizeof(*__buf));
	__buf->f_type = b.f_type;
	__buf->f_bsize = b.f_bsize;
	__buf->f_blocks = b.f_blocks;
	__buf->f_bfree = b.f_bfree;
	__buf->f_bavail = b.f_bavail;
	__buf->f_files = b.f_files;
	__buf->f_ffree = b.f_ffree;
	__buf->f_namelen = b.f_namelen;
	__buf->f_frsize = b.f_frsize;
	__buf->f_fsid = b.f_fsid;
	memcpy(__buf->f_spare, b.f_spare, sizeof(b.f_spare));
	return err;
};
/* Redefined fstatfs because we need it for backwards compatibility */
#endif /* __NR_fstatfs */

#if defined __UCLIBC_LINUX_SPECIFIC__
weak_alias(__libc_fstatfs,fstatfs)
#endif
