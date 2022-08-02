/*
 * Written by J.T. Conklin <jtc@netbsd.org>.
 * Public domain.
 */

#include <sys/types.h>

#if BYTE_ORDER == LITTLE_ENDIAN
char __infinity[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x7f };
#else
char __infinity[] = { 0x7f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
#endif
