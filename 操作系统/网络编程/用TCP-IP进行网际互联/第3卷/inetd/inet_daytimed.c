/* inet_daytimed.c - main */

#include <sys/types.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------------------------------------
 * main - inetd client for DAYTIME service
 *------------------------------------------------------------------------
 */
int
main(int argc, char *argv[])
{
        char    *pts;                   /* pointer to time string       */
        time_t  now;                    /* current time                 */
        char    *ctime();

        (void) time(&now);
        pts = ctime(&now);
        (void) write(0, pts, strlen(pts));
	exit(0);
}
