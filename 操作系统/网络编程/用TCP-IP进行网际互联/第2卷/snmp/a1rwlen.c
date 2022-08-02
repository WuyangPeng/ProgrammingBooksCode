/* a1rwlen.c - a1readlen, a1writelen */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

#include <snmp.h>
#include <asn1.h>

/*------------------------------------------------------------------------
 * a1readlen - read and return the length of an ASN.1 encoded object
 *------------------------------------------------------------------------
 */
int
a1readlen(unsigned char *pack, unsigned *lenlen)
{
	unsigned	i, totlen;

	/* if the high bit is NOT set, then len is in short form */
	if (!((*pack) & CHAR_HIBIT)) {
		*lenlen = 1;
		return (*pack) & ~CHAR_HIBIT;	/* use only low bits */
	}
	/*
	 * else, using long form where bit 7 = 1, and bits 6 - 0 encode
	 * the number of subsequent octets that specify the length
	 */
	*lenlen = (*pack++ & ~CHAR_HIBIT) + 1;

	for (i = 0, totlen = 0; i < (*lenlen) - 1; i++)
		totlen = (totlen << CHAR_BITS) | (int) *pack++;
	return totlen;
}

/*------------------------------------------------------------------------
 * a1writelen - write the length of an object in ASN.1 encoded form
 *------------------------------------------------------------------------
 */
int
a1writelen(unsigned char *pp, unsigned len)
{
	/* if len < 128 then use short form */
	if (len < CHAR_HIBIT) {
		*pp = len;
		return 1;
	}
	/* use long form, where bit 7 = 1, and bits 6 - 0 encode the
		number of subsequent octets that specify the length */
	if (len <= 255) {
		*pp++ = CHAR_HIBIT | 1;
		*pp = len & 0xff;
		return 2;
	}
	/* else, assume len <= 65535 (2^16 - 1) */
	*pp++ = CHAR_HIBIT | 2;
	*pp++ = len >> CHAR_BITS;
	*pp = len & 0xff;
	return 3;
}
#endif	/* SNMP */
