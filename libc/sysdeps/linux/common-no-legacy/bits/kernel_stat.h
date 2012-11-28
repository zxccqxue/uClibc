#ifndef _BITS_STAT_STRUCT_H
#define _BITS_STAT_STRUCT_H

#include <sys/stat.h>

/*
 * The stat structure defined in
 * libc/sysdeps/linux/common-no-legacy/bits/stat.h
 * is the same as the kernel one for new architectures
 */
#define kernel_stat64	stat

#endif	/*  _BITS_STAT_STRUCT_H */

