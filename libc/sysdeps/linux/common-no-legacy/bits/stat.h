/* Copyright (C) 1992, 1995-2001, 2002, 2009 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef _SYS_STAT_H
# error "Never include <bits/stat.h> directly; use <sys/stat.h> instead."
#endif

#include <endian.h>

/* Versions of the `struct stat' data structure.  */
#define _STAT_VER_LINUX_OLD	1
#define _STAT_VER_KERNEL	1
#define _STAT_VER_SVR4		2
#define _STAT_VER_LINUX		3
#define _STAT_VER		_STAT_VER_LINUX	/* The one defined below.  */

/* Versions of the `xmknod' interface.  */
#define _MKNOD_VER_LINUX	1
#define _MKNOD_VER_SVR4		2
#define _MKNOD_VER		_MKNOD_VER_LINUX /* The bits defined below.  */

/*
 * Architectures may require different alignment for 64-bit
 * members.
 */
#define __ARCH_64BIT_ALIGNMENT __attribute__(( aligned(sizeof(long long)) ))

/*
 * For 32-bit architectures, this struct is similar to the stat64 but it
 * uses 32-bit members along with 32-bit padding. For 64-bit architectures
 * this struct is exactly the same with the stat64 one
 */
struct stat
  {
#ifndef __USE_FILE_OFFSET64
#if __BYTE_ORDER == __LITTLE_ENDIAN
    unsigned long st_dev;			/* Device.  */
    unsigned long __pad1;
    unsigned long st_ino;			/* 32bit file serial number.	*/
    unsigned long __pad2;
    unsigned int st_mode;			/* File mode.  */
    unsigned int st_nlink;			/* Link count.  */
    unsigned int st_uid;			/* User ID of the file's owner.	*/
    unsigned int st_gid;			/* Group ID of the file's group.*/
    unsigned long st_rdev;			/* Device number, if device.  */
    unsigned long __pad3;
    unsigned long long __pad4;
    long st_size;				/* SIze of file, in bytes.  */
    long __pad5;
    int st_blksize;				/* Optimal block size for I/O. */
    int __pad6;
    long st_blocks;				/* Number 512-byte blocks allocated */
    long __pad7;
#else
    unsigned long __pad1;
    unsigned long st_dev;			/* Device. */
    unsigned long __pad2;
    unsigned long st_ino;			/* 32bit file serial number. */
    unsigned int st_mode;			/* File mode.  */
    unsigned int st_nlink;			/* Link count.  */
    unsigned int st_uid;			/* User ID of the file's owner.	*/
    unsigned int st_gid;			/* Group ID of the file's group.*/
    unsigned long __pad3;
    unsigned long st_rdev			/* Device number, if device.  */
    unsigned long long __pad4;
    long __pad5;
    long st_size;				/* Size of file, in bytes. */
    int __pad6;
    int st_blksize;				/* Optimal block size for I/O. */
    long __pad7;
    long st_blocks;				/* Number 512-byte blocks allocated */
#endif /* __LITTLE_ENDIAN */
#else
    unsigned long long st_dev;			/* Device. */
    unsigned long long st_ino;			/* 32bit file serial number. */
    unsigned int st_mode;			/* File mode.  */
    unsigned int st_nlink;			/* Link count.  */
    unsigned int st_uid;			/* User ID of the file's owner.	*/
    unsigned int st_gid;			/* Group ID of the file's group.*/
    unsigned long long st_rdev;			/* Device number, if device.  */
    unsigned long long _pad1;
    long long st_size;				/* SIze of file, in bytes. */
    int st_blksize;				/* Optimal block size for I/O. */
    int __pad2;
    long long st_blocks;			/* Number 512-byte blocks allocated */
#endif
    int st_atime;				/* Time of last access. */
    unsigned int st_atime_nsec;
    int st_mtime;				/* Time of last modification. */
    int st_mtime_nsec;
    int st_ctime;				/* Time of last status change. */
    unsigned int st_ctime_nsec;
    unsigned int __unused4;
    unsigned int __unused5;
} __ARCH_64BIT_ALIGNMENT;


struct stat64
  {
    unsigned long long st_dev;			/* Device. */
    unsigned long long st_ino;			/* 32bit file serial number. */
    unsigned int st_mode;			/* File mode.  */
    unsigned int st_nlink;			/* Link count.  */
    unsigned int st_uid;			/* User ID of the file's owner.	*/
    unsigned int st_gid;			/* Group ID of the file's group.*/
    unsigned long long st_rdev;			/* Device number, if device.  */
    unsigned long long __pad3;
    long long st_size;				/* Size of file, in bytes. */
    int st_blksize;				/* Optimal block size for I/O. */
    int __pad4;
    long long st_blocks;			/* Number 512-byte blocks allocated */
    int st_atime;				/* Time of last access. */
    unsigned int st_atime_nsec;
    int st_mtime;				/* Time of last modification. */
    int st_mtime_nsec;
    int st_ctime;				/* Time of last status change. */
    unsigned int st_ctime_nsec;
    unsigned int __unused4;
    unsigned int __unused5;
};

/* Tell code we have these members.  */
#define	_STATBUF_ST_BLKSIZE
#define _STATBUF_ST_RDEV
/* Nanosecond resolution time values are supported.  */
#define _STATBUF_ST_NSEC

/* Encoding of the file mode.  */

#define	__S_IFMT	0170000	/* These bits determine file type.  */

/* File types.  */
#define	__S_IFDIR	0040000	/* Directory.  */
#define	__S_IFCHR	0020000	/* Character device.  */
#define	__S_IFBLK	0060000	/* Block device.  */
#define	__S_IFREG	0100000	/* Regular file.  */
#define	__S_IFIFO	0010000	/* FIFO.  */
#define	__S_IFLNK	0120000	/* Symbolic link.  */
#define	__S_IFSOCK	0140000	/* Socket.  */

/* POSIX.1b objects.  Note that these macros always evaluate to zero.  But
   they do it by enforcing the correct use of the macros.  */
#define __S_TYPEISMQ(buf)  ((buf)->st_mode - (buf)->st_mode)
#define __S_TYPEISSEM(buf) ((buf)->st_mode - (buf)->st_mode)
#define __S_TYPEISSHM(buf) ((buf)->st_mode - (buf)->st_mode)

/* Protection bits.  */

#define	__S_ISUID	04000	/* Set user ID on execution.  */
#define	__S_ISGID	02000	/* Set group ID on execution.  */
#define	__S_ISVTX	01000	/* Save swapped text after use (sticky).  */
#define	__S_IREAD	0400	/* Read by owner.  */
#define	__S_IWRITE	0200	/* Write by owner.  */
#define	__S_IEXEC	0100	/* Execute by owner.  */

#ifdef __USE_ATFILE
# define UTIME_NOW	((1l << 30) - 1l)
# define UTIME_OMIT	((1l << 30) - 2l)
#endif
