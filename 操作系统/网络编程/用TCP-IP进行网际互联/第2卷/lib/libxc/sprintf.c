/* sprintf.c - sprintf */

#include <stdarg.h>

static sprntf();

/*------------------------------------------------------------------------
 *  vsprintf  --  format arguments and place output in a string (varargs)
 *------------------------------------------------------------------------
 */
int
vsprintf(char *str, const char *fmt, va_list ap)
{
        char    *s;
	
        s = str;
        _doprnt(fmt, ap, sprntf, &s);
        *s++ = '\0';

        return((int)str);
}

/*------------------------------------------------------------------------
 *  sprintf  --  format arguments and place output in a string
 *------------------------------------------------------------------------
 */
sprintf(char *str, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vsprintf(str, fmt, ap);
	va_end(ap);
}

/*------------------------------------------------------------------------
 *  sprntf  --  routine called by doprnt to handle each character
 *------------------------------------------------------------------------
 */

static	sprntf(cpp, c)
        char    **cpp;
        char    c;
{
        return(*(*cpp)++ = c);
}


