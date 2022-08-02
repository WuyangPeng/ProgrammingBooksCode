/* main.c - main */

#include <rtcp.h>

/*-----------------------------------------------------------------------
 * main - initialize and begin to play audio
 *-----------------------------------------------------------------------
 */
int
main(int argc, char **argv)
{  
	rtpinit(inet_addr(argv[1]), atoi(argv[2]));
	playaudio();
	return 0;
}
