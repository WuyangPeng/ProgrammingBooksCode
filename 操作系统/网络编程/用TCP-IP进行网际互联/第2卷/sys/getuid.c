/* getuid.c - getuid */

#include <conf.h>
#include <kernel.h>
#include <user.h>

/*------------------------------------------------------------------------
 * getuid - return user information for login 
 *------------------------------------------------------------------------
 */
getuid(login)
char	*login;
{
	struct user	*pue;

	for (pue = &utab[0]; pue->ue_login != 0; ++pue)
		if (strcmp(login, pue->ue_login) == 0)
			return pue->ue_uid;
	return -1;
}
