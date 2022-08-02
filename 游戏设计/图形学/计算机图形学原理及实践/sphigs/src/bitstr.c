/* -------------------------------------------------------------------------
 * sph_bitstr.c
 *
 *	More bit string manipulations
 * ------------------------------------------------------------------------- */

#include "sphigslocal.h"
#include <string.h>

/* --------------------------- Internal Routines --------------------------- */

/* -------------------------------------------------------------------------
 * DESCR   :	Sets all bits in the bitstring to zero.
 * ------------------------------------------------------------------------- */
void
SPH__clearBitstring (
   substruct_bitstring *B)
{
   if (*B == NULL) 
      *B = (unsigned char*) malloc(BYTES_PER_BITSTRING);
   bzero (*B,BYTES_PER_BITSTRING);
}

/* -------------------------------------------------------------------------
 * DESCR   :	Checks each byte in a bitstring to verify all bits are off. 
 *
 * DETAILS :	I wish I could have made this a macro, but it wasn't
 * 		possible.   
 * ------------------------------------------------------------------------- */
boolean
SPH__bitstringIsClear (
   substruct_bitstring B)
{
   register int i; 

   for (i=0; i<BYTES_PER_BITSTRING; i++)
      if (B[i])
	 return FALSE;
   return TRUE;
}
