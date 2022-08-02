/* memset.c - memset */

/*------------------------------------------------------------------------
 * memset - set buffer b, length len to value c; return pointer to b
 *------------------------------------------------------------------------
 */
void *
memset(void *b, int c, unsigned len)
{
	while (len-- > 0)
		*(unsigned char *)b = (unsigned char) c;
	return b;
}
