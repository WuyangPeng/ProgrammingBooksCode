/*	$NetBSD: getopt.c,v 1.4 1997/10/19 02:16:59 lukem Exp $	*/

#include <sys/cdefs.h>
#ifndef lint
__RCSID("$NetBSD: getopt.c,v 1.4 1997/10/19 02:16:59 lukem Exp $");
#endif /* not lint */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int	main __P((int, char **));

int
main(argc, argv)
	int argc;
	char *argv[];
{
	int c;
	int status = 0;

	optind = 2;	/* Past the program name and the option letters. */
	while ((c = getopt(argc, argv, argv[1])) != -1)
		switch (c) {
		case '?':
			status = 1;	/* getopt routine gave message */
			break;
		default:
			if (optarg != NULL)
				printf(" -%c %s", c, optarg);
			else
				printf(" -%c", c);
			break;
		}
	printf(" --");
	for (; optind < argc; optind++)
		printf(" %s", argv[optind]);
	printf("\n");
	exit(status);
}
