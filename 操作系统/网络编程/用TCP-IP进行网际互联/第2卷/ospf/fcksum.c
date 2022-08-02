/* fcksum.c - fcksum */

/*------------------------------------------------------------------------
 * fcksum - compute the fletcher checksum of a buffer
 *------------------------------------------------------------------------
 */
unsigned int
fcksum(unsigned char *buf, unsigned len)
{
	int		x, y;
	unsigned int	c0, c1, i;

	c0 = c1 = 0;
	for (i=0; i<len; ++i) {
		c0 += buf[i];
		c1 += c0;
	}
	c0 %= 255;
	c1 %= 255;
	x = (len - 8) * c0 - c1;
	x %= 255;
	y = (len - 7) * (-c0) + c1;
	y %= 255;
	if (x < 0)
		x += 255;
	if (y < 0)
		y += 255;
	if (x == 0)
		x = 255;
	if (y == 0)
		y = 255;
	return (x<<8) | y;
}
