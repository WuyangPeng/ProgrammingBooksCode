/*	$NetBSD: ntp_io.h,v 1.2 1998/01/09 06:06:09 perry Exp $	*/

/*
 * POSIX says use <fnct.h> to get O_* symbols and 
 * SEEK_SET symbol form <unistd.h>.
 */
#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <stdio.h>
#ifdef HAVE_SYS_FILE_H
# include <sys/file.h>
#endif
#ifdef HAVE_FCNTL_H
# include <fcntl.h>
#endif
#if !defined(SEEK_SET) && defined(L_SET)
# define SEEK_SET L_SET
#endif
#ifdef SYS_WINNT
# include <io.h>
#endif
