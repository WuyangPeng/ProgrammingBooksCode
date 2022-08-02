/* getuser.c - getuser */

#include <conf.h>
#include <kernel.h>
#include <user.h>

extern struct user	utab[];

/*------------------------------------------------------------------------
 * getuser - return user information for uid
 *------------------------------------------------------------------------
 */
struct user *
getuser(unsigned long uid)
{
	struct user	*pue;

	for (pue = &utab[0]; pue->ue_login != 0; ++pue)
		if (uid == pue->ue_uid)
			return pue;
	return 0;
}
