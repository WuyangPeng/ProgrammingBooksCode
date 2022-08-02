/*	$NetBSD: refclock_ptbacts.c,v 1.2 1998/01/09 06:07:10 perry Exp $	*/

/*
 * crude hack to avoid hard links in distribution
 * and keep only one ACTS type source for different
 * ACTS refclocks
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#if defined(REFCLOCK) && defined(PTBACTS)
# define KEEPPTBACTS
# include "refclock_acts.c"
#else /* not (REFCLOCK && PTBACTS) */
int refclock_ptbacts_bs;
#endif /* not (REFCLOCK && PTBACTS) */
