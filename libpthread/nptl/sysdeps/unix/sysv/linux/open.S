#include <sysdep-cancel.h>

/*
extern int __open_nocancel (const char *, int, ...) attribute_hidden;
*/
#if !defined NOT_IN_libc || defined IS_IN_libpthread || defined IS_IN_librt

/*
 * override the hidden open symbol with this one when
 * we don't have openat() defined. Otherwise we will use
 * the common wrapper
 */
#if defined(__NR_open)
PSEUDO (__libc_open, open, 3)
ret
PSEUDO_END(__libc_open)

libc_hidden_def (__open_nocancel)
libc_hidden_def (__libc_open)
weak_alias (__libc_open, __open)
libc_hidden_weak (__open)
weak_alias (__libc_open, open)
libc_hidden_weak (open)

#endif

#endif
