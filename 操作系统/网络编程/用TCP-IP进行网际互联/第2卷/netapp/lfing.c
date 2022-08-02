/* lfing.c - lfing */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <tty.h>
#include <user.h>
#include <date.h>

static char *pidle(int);

/*------------------------------------------------------------------------
 *  lfing  -  print local FINGER info on the given descriptor
 *------------------------------------------------------------------------
 */
int
lfing(char *nam, int output)
{
	struct user	*pue;
	int		tt, uc;
	u_long		now;
	char		*p, buf[128];

	gettime(&now);
	sprintf(buf, "%-9s%-21s%3s%6s  %-12s\n", "Login", "Name", "TTY",
		"Idle", "Login Time");
	if (nam == NULL || *nam == '\0' || *nam == '\r') {
		uc = 0;
		for (tt=0; tt<Ntty; ++tt) {
			struct tty	*ptty = &ttytab[tt];

			if (ptty->tty_state == TTYS_FREE)
				continue;
			if (ptty->tty_uid < 0)
				continue;
			pue = getuser(ptty->tty_uid);
			if (pue == 0)
				continue;
			if (uc++ == 0)
				write(output, buf, strlen(buf));
			sprintf(buf, "%-9s%-21s%2s%c%6s  ",
				pue->ue_login, pue->ue_name,
				tt ? "tt" : " c", tt ? tt + '0' : 'o',
				pidle(now - ptty->tty_ctime));
			p = buf + strlen(buf);
			ascdate(ptty->tty_ltime, p);
			strcat(p, "\n");
			write(output, buf, strlen(buf));
		}
		if (uc == 0)
			write(output, "no one logged in\n", 17);
		return OK;
	}
write(output, "Not implemented\n", 16);
	/* not implemented (yet) */
	return SYSERR;
}

static char	idlebuf[6];

static char	*
pidle(int secs)
{
	int	days, hours, minutes;

	idlebuf[0] = '\0';

	minutes = secs / 60;
	secs %= 60;
	hours = minutes / 60;
	minutes %= 60;
	days = hours / 24;
	hours %= 24;
	if (days)
		sprintf(idlebuf, "%dd", days);
	else if (hours)
		sprintf(idlebuf, "%2d:%02d", hours, minutes);
	else if (minutes)
		sprintf(idlebuf, "%d", minutes);
	
	return idlebuf;
}
