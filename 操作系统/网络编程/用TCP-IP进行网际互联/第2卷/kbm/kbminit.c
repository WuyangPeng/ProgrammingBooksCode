/* kbminit.c -- kbminit */

#include <conf.h>
#include <kernel.h>
#include <tty.h>
#include <io.h>
#include <kbd.h>

struct tty	kbmtty;

int		set_evec(unsigned, void (handler)());
unsigned char	inb(void *);
void		outb(void *, unsigned char);

/*------------------------------------------------------------------------
 *  kbminit -- initialize the PC keyboard
 *------------------------------------------------------------------------
 */
int
kbminit(struct devsw *pdev)
{
	set_evec(pdev->dvivec, (void (*)())kbmint);

	while (inb(KB_CSR) & KBS_NRDY);	/* wait for input buffer empty */
	outb(KB_CSR, 0x60);		/* next write is a command */
	while (inb(KB_CSR) & KBS_NRDY);
	outb(KB_DAT, 0x69);
	while (inb(KB_CSR) & KBS_NRDY);
	outb(KB_DAT, 0xff);		/* reset */
	while ((inb(KB_CSR) & KBS_HASDAT) == 0);
	pdev->dvioblk = 0;
{
unsigned char c = inb(KB_DAT);
/*
	if (inb(KB_DAT) != 0xAA)
		panic("keyboard initialization error\n");
*/
}
}
