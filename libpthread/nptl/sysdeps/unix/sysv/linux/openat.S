#include <sysdep-cancel.h>

/*
extern int __openat_nocancel (const char *, int, ...) attribute_hidden;
*/
#if !defined NOT_IN_libc || defined IS_IN_libpthread || defined IS_IN_librt

#if defined(__NR_openat)
PSEUDO (__libc_openat, openat, 4)
ret
PSEUDO_END(__libc_openat)

libc_hidden_def (__openat_nocancel)
libc_hidden_def (__libc_openat)
weak_alias (__libc_openat, __openat)
libc_hidden_weak (__openat)
weak_alias (__libc_openat, openat)
libc_hidden_weak (openat)

#endif

#endif
