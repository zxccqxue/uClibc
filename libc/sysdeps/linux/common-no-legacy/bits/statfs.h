/* Copyright (C) 1997, 1998, 2000, 2002, 2003 Free Software Foundation, Inc.
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

#ifndef _SYS_STATFS_H
# error "Never include <bits/statfs.h> directly; use <sys/statfs.h> instead."
#endif

#include <endian.h>
#include <bits/types.h>

/*
 * Architectures may require different alignment for 64-bit
 * members.
 */
#define __ARCH_64BIT_ALIGNMENT __attribute__(( aligned(sizeof(long long)) ))

struct statfs
  {
    __U32_TYPE f_type;
    __U32_TYPE f_bsize;
#ifndef __USE_FILE_OFFSET64
#if __BYTE_ORDER == __LITTLE_ENDIAN
    __U32_TYPE f_blocks;
    __U32_TYPE __pad1;
    __U32_TYPE f_bfree;
    __U32_TYPE __pad2;
    __U32_TYPE f_bavail;
    __U32_TYPE __pad3;
    __U32_TYPE f_files;
    __U32_TYPE __pad4;
    __U32_TYPE f_ffree;
    __U32_TYPE __pad5;
#else
    __U32_TYPE __pad1;
    __U32_TYPE f_blocks;
    __U32_TYPE __pad2;
    __U32_TYPE f_bfree;
    __U32_TYPE __pad3;
    __U32_TYPE f_bavail;
    __U32_TYPE __pad4;
    __U32_TYPE f_files;
    __U32_TYPE __pad5;
    __U32_TYPE f_ffree;
#endif /* __LITTLE_ENDIAN */
#else
    __U64_TYPE f_blocks;
    __U64_TYPE f_bfree;
    __U64_TYPE f_bavail;
    __U64_TYPE f_files;
    __U64_TYPE f_ffree;
#endif /* __USE_FILE_OFFSET64 */
    __fsid_t f_fsid;
    __U32_TYPE f_namelen;
    __U32_TYPE f_frsize;
    __U32_TYPE f_spare[5];
  } __ARCH_64BIT_ALIGNMENT;

#ifdef __USE_LARGEFILE64
struct statfs64
  {
    __U32_TYPE f_type;
    __U32_TYPE f_bsize;
    __U64_TYPE f_blocks;
    __U64_TYPE f_bfree;
    __U64_TYPE f_bavail;
    __U64_TYPE f_files;
    __U64_TYPE f_ffree;
    __fsid_t f_fsid;
    __U32_TYPE f_namelen;
    __U32_TYPE f_frsize;
    __U32_TYPE f_spare[5];
  };
#endif

/* Tell code we have these members.  */
#define _STATFS_F_NAMELEN
#define _STATFS_F_FRSIZE
