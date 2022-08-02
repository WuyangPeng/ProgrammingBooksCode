/* ttyiin.c - ttyiin */

#include <conf.h>
#include <kernel.h>
#include <tty.h>

static	iputchar(), delchar(), delword(), reprint();
static int echo(struct tty *, unsigned char);

/*------------------------------------------------------------------------
 * ttyiin - handle interrupt-level input for a tty
 *------------------------------------------------------------------------
 */
void
ttyiin(struct devsw *pdev, unsigned char ch)
{
	struct tty	*ptty = (struct tty *)pdev->dvioblk;
	struct tchars	*ptc;
	static unsigned char	lastc;

	if (ch == '\n' && lastc == '\r')
		return;
	lastc = ch;
	if (ptty->tty_iflags & TIF_RAW) {
		iputchar(ptty, ch);
		if (scount(ptty->tty_isema) <= 0)
			signal(ptty->tty_isema);
		return;
	}
	if (ch == '\r')
		ch = '\n';
	ptc = &ptty->tty_tchars;
	if (ch == ptc->tc_erase) {
		delchar(ptty);
		return;
	} else if (ch == ptc->tc_werase) {
		delword(ptty);
		return;
	} else if (ch == ptc->tc_reprint) {
		reprint(ptty);
		return;
	} else if (ch == ptc->tc_intr) {
		send(ptty->tty_cpid, INTRMSG);
		return;
	} else if (ch == ptc->tc_eof) {
		ptty->tty_iflags |= TIF_EOF;
	} else if (ch == ptc->tc_status) {
		x_ps(CONSOLE, CONSOLE, CONSOLE, 0);
	}
	iputchar(ptty, ch);
	if ((ptty->tty_iflags & (TIF_CBREAK|TIF_RAW)) ||
	    ch == ptty->tty_tchars.tc_eol ||
	    ch == ptty->tty_tchars.tc_eof)
		if (scount(ptty->tty_isema) <= 0)
			signal(ptty->tty_isema);
}

/*------------------------------------------------------------------------
 * iputchar - put a character on a tty's input queue
 *------------------------------------------------------------------------
 */
static int
iputchar(ptty, ch)
struct tty	*ptty;
unsigned char	ch;
{
	struct devsw	*pdev = ptty->tty_pdev;
	int		pos;

	if (ptty->tty_icount >= IBLEN) {
		ttyputc(pdev, '\007');
		return;
	}
	pos = ptty->tty_istart + ptty->tty_icount;
	if (pos >= IBLEN)
		pos -= IBLEN;
	ptty->tty_in[pos] = ch;
	ptty->tty_icount++;
	if (ptty->tty_iflags & TIF_NOECHO)
		return;
	echo(ptty, ch);
}

/*------------------------------------------------------------------------
 * echo - echo an input character on a tty's output
 *------------------------------------------------------------------------
 */
static int
echo(struct tty *ptty, unsigned char ch)
{
	struct devsw	*pdev = ptty->tty_pdev;

	if ((ptty->tty_iflags & TIF_RAW) == 0) {
		if (ch > 127) {
			ttyputc(pdev, 'M');
			ttyputc(pdev, '-');
			ch -= 128;
		}
		if (ch < ' ' &&
		  !(ch == '\n' || ch == '\b' || ch == '\f' ||
		    ch == '\r' || ch == '\t')) {
			ttyputc(pdev, '^');
			ch += 64;	/* make it printable */
		} else if (ch == 127) {
			ttyputc(pdev, '^');
			ch = '?';
		}
	}
	ttyputc(pdev, ch);
}

#define RUBOUT(pdev) {		\
	ttyputc(pdev, '\b');	\
	ttyputc(pdev, ' ');	\
	ttyputc(pdev, '\b');	\
}

/*------------------------------------------------------------------------
 * delchar - delete a character from the input queue
 *------------------------------------------------------------------------
 */
static int
delchar(ptty)
struct tty	*ptty;
{
	struct devsw	*pdev = ptty->tty_pdev;
	unsigned int	ch;
	int		pos;

	if (ptty->tty_icount == 0)
		return;
	pos = ptty->tty_istart + ptty->tty_icount - 1;
	if (pos >= IBLEN)
		pos -= IBLEN;
	if (ptty->tty_in[pos] == '\n')
		return;
	ptty->tty_icount--;
	if (ptty->tty_iflags & TIF_NOECHO)
		return;
	/* update display, including multi-character sequences */
	ch = ptty->tty_in[pos];
	if (ch > 127) {
		RUBOUT(pdev);	/* also remove "M-" */
		RUBOUT(pdev);
	}
	if (ch == 127 || ch < ' ')
		RUBOUT(pdev);	/* also remove "^" */
	RUBOUT(pdev);
}

#define	KIND(ch) ( ((ch) == ' ' || (ch == '\t')) ? 0 : (((ch) == '/') + 1))

/*------------------------------------------------------------------------
 * delword - delete a word from the input buffer
 *------------------------------------------------------------------------
 */
static int
delword(ptty)
struct tty	*ptty;
{
	unsigned char	ch;
	int		firstkind, kind, pos;

	if (ptty->tty_icount == 0)
		return;
	pos = ptty->tty_istart + ptty->tty_icount - 1;
	if (pos >= IBLEN)
		pos -= IBLEN;
	ch = ptty->tty_in[pos];
	kind = firstkind = KIND(ch);
	while (ptty->tty_icount && kind == firstkind) {
		delchar(ptty);
		if (pos-- == 0)
			pos = IBLEN - 1;
		ch = ptty->tty_in[pos];
		if (ch == '\n')
			break;
		kind = KIND(ch);
	}
}

/*------------------------------------------------------------------------
 * reprint - reprint a line from the input buffer
 *------------------------------------------------------------------------
 */
static int
reprint(ptty)
struct tty	*ptty;
{
	int	i, pos, count;

	pos = ptty->tty_istart + ptty->tty_icount;
	if (pos > IBLEN)
		pos -= IBLEN;
	count = 0;
	for (i=ptty->tty_icount; i > 0; --i) {
		if (ptty->tty_in[pos] == '\n')
			break;
		if (pos-- == 0)
			pos = IBLEN - 1;
		count++;
	}
	if (ptty->tty_in[pos] == '\n')	/* if newline, one too far */
		if (++pos >= IBLEN)
			pos -= IBLEN;
	echo(ptty, ptty->tty_tchars.tc_reprint);
	echo(ptty, '\n');
	for (i=count; i > 0; --i) {
		echo(ptty, ptty->tty_in[pos]);
		if (++pos >= IBLEN)
			pos = 0;
	}
}
