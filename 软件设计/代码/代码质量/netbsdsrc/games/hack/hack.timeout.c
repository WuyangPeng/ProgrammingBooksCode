/*	$NetBSD: hack.timeout.c,v 1.4 1997/10/19 16:59:08 christos Exp $	*/

/*
 * Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985.
 */

#include <sys/cdefs.h>
#ifndef lint
__RCSID("$NetBSD: hack.timeout.c,v 1.4 1997/10/19 16:59:08 christos Exp $");
#endif				/* not lint */

#include "hack.h"
#include "extern.h"

void
timeout()
{
	struct prop    *upp;
	if (Stoned)
		stoned_dialogue();
	for (upp = u.uprops; upp < u.uprops + SIZE(u.uprops); upp++)
		if ((upp->p_flgs & TIMEOUT) && !--upp->p_flgs) {
			if (upp->p_tofn)
				(*upp->p_tofn) ();
			else
				switch (upp - u.uprops) {
				case STONED:
					killer = "cockatrice";
					done("died");
					break;
				case SICK:
					pline("You die because of food poisoning.");
					killer = u.usick_cause;
					done("died");
					break;
				case FAST:
					pline("You feel yourself slowing down.");
					break;
				case CONFUSION:
					pline("You feel less confused now.");
					break;
				case BLIND:
					pline("You can see again.");
					setsee();
					break;
				case INVIS:
					on_scr(u.ux, u.uy);
					pline("You are no longer invisible.");
					break;
				case WOUNDED_LEGS:
					heal_legs();
					break;
				}
		}
}

/* He is being petrified - dialogue by inmet!tower */
char           *stoned_texts[] = {
	"You are slowing down.",/* 5 */
	"Your limbs are stiffening.",	/* 4 */
	"Your limbs have turned to stone.",	/* 3 */
	"You have turned to stone.",	/* 2 */
	"You are a statue."	/* 1 */
};

void
stoned_dialogue()
{
	long            i = (Stoned & TIMEOUT);

	if (i > 0 && i <= SIZE(stoned_texts))
		pline(stoned_texts[SIZE(stoned_texts) - i]);
	if (i == 5)
		Fast = 0;
	if (i == 3)
		nomul(-3);
}
