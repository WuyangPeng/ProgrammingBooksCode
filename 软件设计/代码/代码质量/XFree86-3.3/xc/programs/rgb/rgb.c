/* $XConsortium: rgb.c,v 11.20 94/11/28 23:39:21 gildea Exp $ */
/* $XFree86: xc/programs/rgb/rgb.c,v 3.3 1996/10/03 08:49:25 dawes Exp $ */
/*

Copyright (c) 1985  X Consortium

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from the X Consortium.

*/


/* reads from standard input lines of the form:
	red green blue name
   where red/green/blue are decimal values, and inserts them in a database.
 */

#ifdef NDBM
#include <ndbm.h>
#else
#if defined(SVR4) && !defined(SCO325)
#include <rpcsvc/dbm.h>
#else
#include <dbm.h>
#endif
#define dbm_open(name,flags,mode) (!dbminit(name))
#define dbm_store(db,key,content,flags) (store(key,content))
#define dbm_close(db) dbmclose()
#endif

#undef NULL
#include <stdio.h>
#include <X11/Xos.h>
#include "rgb.h"
#include "site.h"
#include <ctype.h>

#include <errno.h>

#ifdef X_NOT_STDC_ENV
extern int errno;
#endif

char *ProgramName;

char *SysError ()
{
    register char *s = strerror(errno);
    return s ? s : "?";
}

main(argc, argv)
    int argc;
    char **argv;
{
    char *dbname;
    char line[512];
    int red, green, blue;
    RGB rgb;
    datum key, content;
    char name[512];
    int items;
    int lineno;
    int i, n;
    int fd;
#ifdef NDBM
    DBM *rgb_dbm;
#else
    int rgb_dbm;
#endif

    ProgramName = argv[0];

    if (argc == 2)
	dbname = argv[1];
    else
	dbname = RGB_DB;

    strcpy (name, dbname);
    strcat (name, ".dir");
    fd = open (name, O_WRONLY|O_CREAT, 0666);
    if (fd < 0) {
	fprintf (stderr, 
		 "%s:  unable to create dbm file \"%s\" (error %d, %s)\n",
		 ProgramName, name, errno, strerror(errno));
	exit (1);
    }
    (void) close (fd);

    strcpy (name, dbname);
    strcat (name, ".pag");
    fd = open (name, O_WRONLY|O_CREAT, 0666);
    if (fd < 0) {
	fprintf (stderr, 
		 "%s:  unable to create dbm file \"%s\" (error %d, %s)\n",
		 ProgramName, name, errno, strerror(errno));
	exit (1);
    }
    (void) close (fd);

    rgb_dbm = dbm_open (dbname, O_RDWR|O_CREAT, 0666);
    if (!rgb_dbm) {
	fprintf (stderr,
		 "%s:  unable to open dbm database \"%s\" (error %d, %s)\n",
		 ProgramName, dbname, errno, strerror(errno));
	exit (1);
    }

    key.dptr = name;
    content.dptr = (char *) &rgb;
    content.dsize = sizeof (rgb);
    lineno = 0;
    while (fgets (line, sizeof (line), stdin)) {
	lineno++;
	if (line[0] == '!')
	    continue;
	items = sscanf (line, "%d %d %d %[^\n]\n", &red, &green, &blue, name);
	if (items != 4) {
	    fprintf (stderr, "syntax error on line %d\n", lineno);
	    fflush (stderr);
	    continue;
	}
	if (red < 0 || red > 0xff ||
	    green < 0 || green > 0xff ||
	    blue < 0 || blue > 0xff) {
	    fprintf (stderr, "value for %s out of range\n", name);
	    fflush (stderr);
	    continue;
	}
	n = strlen (name);
	for (i = 0; i < n; i++) {
	    if (isupper (name[i]))
		name[i] = tolower (name[i]);
	}
	key.dsize = n;
	rgb.red = (red * 65535) / 255;
	rgb.green = (green * 65535) / 255;
	rgb.blue = (blue * 65535) / 255;
	if (dbm_store (rgb_dbm, key, content, DBM_REPLACE)) {
	    fprintf (stderr, "%s:  store of entry \"%s\" failed\n",
		     ProgramName, name);
	    fflush (stderr);
	}
    }

    dbm_close(rgb_dbm);

    exit(0);
}
