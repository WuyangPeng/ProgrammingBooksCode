/* kbscan.c - kbscan */

#include <kernel.h>
#include <tty.h>
#include <kbd.h>

static	int	extchar(unsigned char);
static	int	state;

unsigned char	kbcode[] = { 0,
	  27,  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',
	 '0',  '-',  '=', '\b', '\t',  'q',  'w',  'e',  'r',  't',
	 'y',  'u',  'i',  'o',  'p',  '[',  ']', '\n',    0,  'a',
	 's',  'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';', '\'',
	 '`',    0, '\\',  'z',  'x',  'c',  'v',  'b',  'n',  'm',
	 ',',  '.',  '/',    0,    0,    0,  ' ' };

unsigned char	kbshift[] = { 0,
	   0,  '!',  '@',  '#',  '$',  '%',  '^',  '&',  '*',  '(',
	 ')',  '_',  '+', '\b', '\t',  'Q',  'W',  'E',  'R',  'T',
	 'Y',  'U',  'I',  'O',  'P',  '{',  '}', '\n',    0,  'A',
	 'S',  'D',  'F',  'G',  'H',  'J',  'K',  'L',  ':',  '"',
	 '~',    0,  '|',  'Z',  'X',  'C',  'V',  'B',  'N',  'M',
	 '<',  '>',  '?',    0,    0,    0,  ' ' };

unsigned char	kbctl[] = { 0,
 	   0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    
	   0,   31,    0, '\b', '\t',   17,   23,    5,   18,   20,
	  25,   21,    9,   15,   16,   27,   29, '\n',    0,    1,
	  19,    4,    6,    7,    8,   10,   11,   12,    0,    0,
	   0,    0,   28,   26,   24,    3,   22,    2,   14,   13 };

/*------------------------------------------------------------------------
 * kbtoa - convert keyboard scan keys to ASCII characters
 *------------------------------------------------------------------------
 */
unsigned int
kbtoa(unsigned char code)
{
	unsigned int	ch;

	if (state & EXTENDED)
		return extchar(code);
	if (code & BREAK) {
		switch (code & 0x7f) {
		case LSHIFT:
		case RSHIFT:
			state &= ~INSHIFT;
			break;
		case LCTL:
			state &= ~INCTL;
			break;
		case LMETA:
			state &= ~INMETA;
			break;
		}
		return NOCHAR;
	}
	/* check for special keys */
	switch (code) {
	case LSHIFT:
	case RSHIFT:
		state |= INSHIFT;
		return NOCHAR;
	case LCTL:
		state |= INCTL;
		return NOCHAR;
	case LMETA:
		state |= INMETA;
		return NOCHAR;
	case EXTESC:
		state |= EXTENDED;
		return NOCHAR;
	}
	/* special key combinations */
	if ((state & (INSHIFT|INCTL)) == (INSHIFT|INCTL)) {
		if (code == 0x3)
			return 0;	/* CTL-@ == '\0' */
		if (code == 0x35)
			return 127;	/* CTL-? == DEL */
	}

	ch = NOCHAR;
	if (code < sizeof(kbcode))
		ch = kbcode[code];
	if (state & INSHIFT) {
		if (code >= sizeof(kbshift))
			return NOCHAR;
		ch =  kbshift[code];
	}
	if (state & INCTL) {
		if (code >= sizeof(kbctl))
			return NOCHAR;
		ch = kbctl[code];
	}
	if (state & INMETA)
		ch += 0x80;
	return ch;
}

static int
extchar(unsigned char code)
{
	state &= ~EXTENDED;
	return NOCHAR;
}
