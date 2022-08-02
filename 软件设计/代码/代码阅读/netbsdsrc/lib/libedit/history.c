/*	$NetBSD: history.c,v 1.7 1997/10/14 15:05:54 christos Exp $	*/

/*-
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Christos Zoulas of Cornell University.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#if !defined(lint) && !defined(SCCSID)
#if 0
static char sccsid[] = "@(#)history.c	8.1 (Berkeley) 6/4/93";
#else
__RCSID("$NetBSD: history.c,v 1.7 1997/10/14 15:05:54 christos Exp $");
#endif
#endif /* not lint && not SCCSID */

/*
 * hist.c: History access functions
 */
#include "sys.h"

#include <string.h>
#include <stdlib.h>
#ifdef __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

static const char hist_cookie[] = "_HiStOrY_V1_\n";

#include "histedit.h"

typedef int	(*history_gfun_t) __P((ptr_t, HistEvent *));
typedef int	(*history_efun_t) __P((ptr_t, HistEvent *, const char *));
typedef void 	(*history_vfun_t) __P((ptr_t, HistEvent *));

struct history {
    ptr_t	   h_ref;		/* Argument for history fcns	*/
    history_gfun_t h_first;		/* Get the first element	*/
    history_gfun_t h_next;		/* Get the next element		*/
    history_gfun_t h_last;		/* Get the last element		*/
    history_gfun_t h_prev;		/* Get the previous element	*/
    history_gfun_t h_curr;		/* Get the current element	*/
    history_vfun_t h_clear;		/* Clear the history list	*/ 
    history_efun_t h_enter;		/* Add an element		*/
    history_efun_t h_add;		/* Append to an element		*/
};

#define	HNEXT(h, ev)  	(*(h)->h_next)((h)->h_ref, ev)
#define	HFIRST(h, ev) 	(*(h)->h_first)((h)->h_ref, ev)
#define	HPREV(h, ev)  	(*(h)->h_prev)((h)->h_ref, ev)
#define	HLAST(h, ev) 	(*(h)->h_last)((h)->h_ref, ev)
#define	HCURR(h, ev) 	(*(h)->h_curr)((h)->h_ref, ev)
#define	HCLEAR(h, ev) 	(*(h)->h_clear)((h)->h_ref, ev)
#define	HENTER(h, ev, str)	(*(h)->h_enter)((h)->h_ref, ev, str)
#define	HADD(h, ev, str)	(*(h)->h_add)((h)->h_ref, ev, str)

#define h_malloc(a)	malloc(a)
#define h_free(a)	free(a)


private int	history_set_num		__P((History *, HistEvent *, int));
private int	history_get_size	__P((History *, HistEvent *));
private int	history_set_fun		__P((History *, History *));
private int 	history_load		__P((History *, const char *));
private int 	history_save		__P((History *, const char *));
private int	history_prev_event	__P((History *, HistEvent *, int));
private int	history_next_event	__P((History *, HistEvent *, int));
private int	history_next_string	__P((History *, HistEvent *, const char *));
private int	history_prev_string	__P((History *, HistEvent *, const char *));


/***********************************************************************/

/*
 * Builtin- history implementation
 */
typedef struct hentry_t {
    HistEvent ev;		/* What we return		*/
    struct hentry_t *next;	/* Next entry			*/
    struct hentry_t *prev;	/* Previous entry		*/
} hentry_t;

typedef struct history_t {
    hentry_t  list;		/* Fake list header element	*/
    hentry_t *cursor;		/* Current element in the list	*/
    int	max;			/* Maximum number of events	*/
    int cur;			/* Current number of events	*/
    int	eventid;		/* For generation of unique event id	*/ 
} history_t;

private int	history_def_first  __P((ptr_t, HistEvent *));
private int	history_def_last   __P((ptr_t, HistEvent *));
private int	history_def_next   __P((ptr_t, HistEvent *));
private int	history_def_prev   __P((ptr_t, HistEvent *));
private int	history_def_curr   __P((ptr_t, HistEvent *));
private int	history_def_enter  __P((ptr_t, HistEvent *, const char *));
private int	history_def_add    __P((ptr_t, HistEvent *, const char *));
private void	history_def_init   __P((ptr_t *, HistEvent *, int));
private void	history_def_clear  __P((ptr_t, HistEvent *));
private int	history_def_insert __P((history_t *, HistEvent *,const char *));
private void	history_def_delete __P((history_t *, HistEvent *, hentry_t *));

#define history_def_set(p, num)	(void) (((history_t *) p)->max = (num))
#define history_def_getsize(p)  (((history_t *) p)->cur)

#define he_strerror(code)	he_errlist[code]
#define he_seterrev(evp, code)	{\
				    evp->num = code;\
				    evp->str = he_strerror(code);\
				}
					
/* error messages */
static const char *const he_errlist[] = {
	"OK",
	"malloc() failed",
	"first event not found",
	"last event not found",
	"empty list",
	"no next event",
	"no previous event",
	"current event is invalid",
	"event not found",
	"can't read history from file",
	"can't write history",
	"required parameter(s) not supplied",
	"history size negative",
	"function not allowed with other history-functions-set the default",
	"bad parameters"
};

/* error codes */
#define _HE_OK                   0
#define _HE_UNKNOWN		 1
#define _HE_MALLOC_FAILED        2
#define _HE_FIRST_NOTFOUND       3
#define _HE_LAST_NOTFOUND        4
#define _HE_EMPTY_LIST           5
#define _HE_END_REACHED          6
#define _HE_START_REACHED	 7
#define _HE_CURR_INVALID	 8
#define _HE_NOT_FOUND		 9
#define _HE_HIST_READ		10
#define _HE_HIST_WRITE		11
#define _HE_PARAM_MISSING	12
#define _HE_SIZE_NEGATIVE	13
#define _HE_NOT_ALLOWED		14
#define _HE_BAD_PARAM		15

/* history_def_first():
 *	Default function to return the first event in the history.
 */
private int
history_def_first(p, ev)
    ptr_t p;
    HistEvent *ev;
{
    history_t *h = (history_t *) p;

    h->cursor = h->list.next;
    if (h->cursor != &h->list)
	*ev = h->cursor->ev;
    else {
	he_seterrev(ev, _HE_FIRST_NOTFOUND);
	return -1;
    }

    return 0;
}

/* history_def_last():
 *	Default function to return the last event in the history.
 */
private int
history_def_last(p, ev)
    ptr_t p;
    HistEvent *ev;
{
    history_t *h = (history_t *) p;

    h->cursor = h->list.prev;
    if (h->cursor != &h->list)
	*ev =  h->cursor->ev;
    else {
	he_seterrev(ev, _HE_LAST_NOTFOUND);
	return -1;
    }

    return 0;
}

/* history_def_next():
 *	Default function to return the next event in the history.
 */
private int
history_def_next(p, ev)
    ptr_t p;
    HistEvent *ev;
{
    history_t *h = (history_t *) p;

    if (h->cursor != &h->list)
	h->cursor = h->cursor->next;
    else {
	he_seterrev(ev, _HE_EMPTY_LIST);
	return -1;
    }

    if (h->cursor != &h->list)
	*ev = h->cursor->ev;
    else {
	he_seterrev(ev, _HE_END_REACHED);
	return -1;
    }

    return 0;
}


/* history_def_prev():
 *	Default function to return the previous event in the history.
 */
private int
history_def_prev(p, ev)
    ptr_t p;
   HistEvent *ev;
{
    history_t *h = (history_t *) p;

    if (h->cursor != &h->list)
	h->cursor = h->cursor->prev;
    else {
	he_seterrev(ev, (h->cur > 0) ? _HE_END_REACHED : _HE_EMPTY_LIST);
	return -1;
   }

    if (h->cursor != &h->list)
	*ev = h->cursor->ev;
    else {
	he_seterrev(ev, _HE_START_REACHED);
	return -1;
    }

    return 0;
}


/* history_def_curr():
 *	Default function to return the current event in the history.
 */
private int
history_def_curr(p, ev)
    ptr_t p;
   HistEvent *ev;
{
    history_t *h = (history_t *) p;

    if (h->cursor != &h->list)
	*ev = h->cursor->ev;
    else {
	he_seterrev(ev, (h->cur > 0) ? _HE_CURR_INVALID : _HE_EMPTY_LIST);
	return -1;
   }

    return 0;
}

/* history_def_add():
 *	Append string to element
 */
private int
history_def_add(p, ev, str)
    ptr_t p;
    HistEvent *ev;
    const char *str;
{
    history_t *h = (history_t *) p;
    size_t len;
    char *s;

    if (h->cursor == &h->list)
	return (history_def_enter(p, ev, str));
    len = strlen(h->cursor->ev.str) + strlen(str) + 1;
    s = (char *) h_malloc(len);
    if (!s) {
	he_seterrev(ev, _HE_MALLOC_FAILED);
	return -1;
    }
    (void)strcpy(s, h->cursor->ev.str);		/* XXX strcpy is safe */
    (void)strcat(s, str);			/* XXX strcat is safe */
    h_free((ptr_t) h->cursor->ev.str);
    h->cursor->ev.str = s;
    *ev = h->cursor->ev;
    return 0;
}


/* history_def_delete():
 *	Delete element hp of the h list
 */
private void
history_def_delete(h, ev, hp)
    history_t *h;
    HistEvent *ev;
    hentry_t *hp;
{
    if (hp == &h->list)
	abort();
    hp->prev->next = hp->next;
    hp->next->prev = hp->prev;
    h_free((ptr_t) hp->ev.str);
    h_free(hp);
    h->cur--;
}


/* history_def_insert():
 *	Insert element with string str in the h list
 */
private int
history_def_insert(h, ev, str)
    history_t *h;
    HistEvent *ev;
    const char *str;
{
    h->cursor = (hentry_t *) h_malloc(sizeof(hentry_t));
    if (h->cursor)
    	h->cursor->ev.str = strdup(str);
    if (!h->cursor || !h->cursor->ev.str) {
	he_seterrev(ev, _HE_MALLOC_FAILED);
	return -1;
    }
    h->cursor->ev.num = ++h->eventid;
    h->cursor->next = h->list.next;
    h->cursor->prev = &h->list;
    h->list.next->prev = h->cursor;
    h->list.next = h->cursor;
    h->cur++;

    *ev = h->cursor->ev;
    return 0;
}


/* history_def_enter():
 *	Default function to enter an item in the history
 */
private int
history_def_enter(p, ev, str)
    ptr_t p;
    HistEvent *ev;
    const char *str;
{
    history_t *h = (history_t *) p;

    if (history_def_insert(h, ev, str) == -1)
	return -1; /* error, keep error message */

    /*
     * Always keep at least one entry.
     * This way we don't have to check for the empty list.
     */
    while (h->cur - 1 > h->max) 
	history_def_delete(h, ev, h->list.prev);

    return 0;
}


/* history_def_init():
 *	Default history initialization function
 */
private void
history_def_init(p, ev, n)
    ptr_t *p;
    HistEvent *ev;
    int n;
{
    history_t *h = (history_t *) h_malloc(sizeof(history_t));
    if (n <= 0)
	n = 0;
    h->eventid = 0;
    h->cur = 0;
    h->max = n;
    h->list.next = h->list.prev = &h->list;
    h->list.ev.str = NULL;
    h->list.ev.num = 0;
    h->cursor = &h->list;
    *p = (ptr_t) h;
}


/* history_def_clear():
 *	Default history cleanup function
 */
private void
history_def_clear(p, ev)
    ptr_t p;
    HistEvent *ev;
{
    history_t *h = (history_t *) p;

    while (h->list.prev != &h->list)
	history_def_delete(h, ev, h->list.prev);
    h->eventid = 0;
    h->cur = 0;
}




/************************************************************************/

/* history_init():
 *	Initialization function.
 */
public History *
history_init()
{
    History *h = (History *) h_malloc(sizeof(History));
    HistEvent ev;

    history_def_init(&h->h_ref, &ev, 0);

    h->h_next  = history_def_next;
    h->h_first = history_def_first;
    h->h_last  = history_def_last;
    h->h_prev  = history_def_prev;
    h->h_curr  = history_def_curr;
    h->h_clear = history_def_clear;
    h->h_enter = history_def_enter;
    h->h_add   = history_def_add;

    return h;
}


/* history_end():
 *	clean up history;
 */
public void
history_end(h)
    History *h;
{
    HistEvent ev;
    if (h->h_next == history_def_next)
	history_def_clear(h->h_ref, &ev);
}



/* history_set_num():
 *	Set history number of events
 */
private int
history_set_num(h, ev, num)
    History *h;
    HistEvent *ev;
    int num;
{
    if (h->h_next != history_def_next) {
	he_seterrev(ev, _HE_NOT_ALLOWED);
	return -1;
    }

    if (num < 0) {
	he_seterrev(ev, _HE_BAD_PARAM);
	return -1;
    }

    history_def_set(h->h_ref, num);
    return 0;
}

/* history_get_size():
 *      Get number of events currently in history
 */
private int
history_get_size(h, ev)
    History *h;
    HistEvent *ev;
{
    int retval=0;
 
    if (h->h_next != history_def_next) {
	he_seterrev(ev, _HE_NOT_ALLOWED);
	return -1;
    }
    retval = history_def_getsize(h->h_ref);
    if (retval < -1) {
	he_seterrev(ev, _HE_SIZE_NEGATIVE);
	return -1;
    }

    ev->num = retval;
    return 0;
}

/* history_set_fun():
 *	Set history functions
 */
private int
history_set_fun(h, nh)
    History *h;
    History *nh;
{
    HistEvent ev;

    if (nh->h_first == NULL || nh->h_next == NULL ||
        nh->h_last == NULL  || nh->h_prev == NULL || nh->h_curr == NULL ||
	nh->h_enter == NULL || nh->h_add == NULL || nh->h_clear == NULL ||
	nh->h_ref == NULL) {
	if (h->h_next != history_def_next) {
	    history_def_init(&h->h_ref, &ev, 0);
	    h->h_first = history_def_first;
	    h->h_next  = history_def_next;
	    h->h_last  = history_def_last;
	    h->h_prev  = history_def_prev;
	    h->h_curr  = history_def_curr;
	    h->h_clear = history_def_clear;
	    h->h_enter = history_def_enter;
	    h->h_add   = history_def_add;
	}
	return -1;
    }

    if (h->h_next == history_def_next)
	history_def_clear(h->h_ref, &ev);

    h->h_first = nh->h_first;
    h->h_next  = nh->h_next;
    h->h_last  = nh->h_last;
    h->h_prev  = nh->h_prev;
    h->h_curr  = nh->h_curr;
    h->h_clear = nh->h_clear;
    h->h_enter = nh->h_enter;
    h->h_add   = nh->h_add;

    return 0;
}


/* history_load():
 *	History load function
 */
private int
history_load(h, fname)
    History *h;
    const char *fname;
{
    FILE *fp;
    char *line;
    size_t sz;
    int i = -1;
    HistEvent ev;

    if ((fp = fopen(fname, "r")) == NULL)
	return i;

    if ((line = fgetln(fp, &sz)) == NULL)
	goto done;

    if (strncmp(line, hist_cookie, sz) != 0)
	goto done;
	
    for (i = 0; (line = fgetln(fp, &sz)) != NULL; i++) {
	char c = line[sz];
	line[sz] = '\0';
	HENTER(h, &ev, line);
	line[sz] = c;
    }

done:
    (void) fclose(fp);
    return i;
}


/* history_save():
 *	History save function
 */
private int
history_save(h, fname)
    History *h;
    const char *fname;
{
    FILE *fp;
    HistEvent ev;
    int i = 0, retval;

    if ((fp = fopen(fname, "w")) == NULL)
	return -1;

    (void) fputs(hist_cookie, fp);
    for (retval = HLAST(h, &ev); retval != -1; retval = HPREV(h, &ev), i++)
	(void) fprintf(fp, "%s", ev.str);
    (void) fclose(fp);
    return i;
}


/* history_prev_event():
 *	Find the previous event, with number given
 */
private int
history_prev_event(h, ev, num)
    History *h;
    HistEvent *ev;
    int num;
{
    int retval;
    for (retval = HCURR(h, ev); retval != -1; retval = HPREV(h, ev))
	if (ev->num == num)
	    return 0;

    he_seterrev(ev, _HE_NOT_FOUND);
    return -1;
}


/* history_next_event():
 *	Find the next event, with number given
 */
private int
history_next_event(h, ev, num)
    History *h;
    HistEvent *ev;
    int num;
{
    int retval;
    for (retval = HCURR(h, ev); retval != -1; retval = HNEXT(h, ev))
	if (ev->num == num)
	    return 0;

    he_seterrev(ev, _HE_NOT_FOUND);
    return NULL;
}


/* history_prev_string():
 *	Find the previous event beginning with string
 */
private int
history_prev_string(h, ev, str)
    History *h;
    HistEvent *ev;
    const char* str;
{
    size_t len = strlen(str);
    int retval;

    for (retval = HCURR(h, ev); retval != -1; retval = HNEXT(h, ev))
	if (strncmp(str, ev->str, len) == 0)
	    return 0;

    he_seterrev(ev, _HE_NOT_FOUND);
    return -1;
}




/* history_next_string():
 *	Find the next event beginning with string
 */
private int
history_next_string(h, ev, str)
    History *h;
    HistEvent *ev;
    const char* str;
{
    size_t len = strlen(str);
    int retval;

    for (retval = HCURR(h, ev); retval != -1; retval = HPREV(h, ev))
	if (strncmp(str, ev->str, len) == 0)
	    return 0;

    he_seterrev(ev, _HE_NOT_FOUND);
    return -1;
}


/* history():
 *	User interface to history functions.
 */
int
#ifdef __STDC__
history(History *h, HistEvent *ev, int fun, ...)
#else
history(va_alist)
    va_dcl
#endif
{
    va_list va;
    const char *str;
    int retval;

#ifdef __STDC__
    va_start(va, fun);
#else
    History *h; 
    HistEvent *ev;
    int fun;
    va_start(va);
    h = va_arg(va, History *);
    ev = va_arg(va, HistEvent *);
    fun = va_arg(va, int);
#endif

    he_seterrev(ev, _HE_OK);

    switch (fun) {
    case H_ADD:
	str = va_arg(va, const char *);
	retval = HADD(h, ev, str);
	break;

    case H_ENTER:
	str = va_arg(va, const char *);
	retval = HENTER(h, ev, str);
	break;

    case H_FIRST:
	retval = HFIRST(h, ev);
	break;

    case H_NEXT:
	retval = HNEXT(h, ev);
	break;

    case H_LAST:
	retval = HLAST(h, ev);
	break;

    case H_PREV:
	retval = HPREV(h, ev);
	break;

    case H_CURR:
	retval = HCURR(h, ev);
	break;

    case H_CLEAR:
	HCLEAR(h, ev);
	retval = 0;
	break;

    case H_LOAD:
	retval = history_load(h, va_arg(va, const char *));
	if (retval == -1)
	    he_seterrev(ev, _HE_HIST_READ);
	break;

    case H_SAVE:
	retval = history_save(h, va_arg(va, const char *));
	if (retval == -1)
	    he_seterrev(ev, _HE_HIST_WRITE);
	break;

    case H_PREV_EVENT:
	retval = history_prev_event(h, ev, va_arg(va, int));
	break;

    case H_NEXT_EVENT:
	retval = history_next_event(h, ev, va_arg(va, int));
	break;

    case H_PREV_STR:
	retval = history_prev_string(h, ev, va_arg(va, const char*));
	break;

    case H_NEXT_STR:
	retval = history_next_string(h, ev, va_arg(va, const char*));
	break;

    case H_SETMAXSIZE:
	retval = history_set_num(h, ev, va_arg(va, int));
	break;

    case H_FUNC:
	{
	    History hf;
	    hf.h_ref   = va_arg(va, ptr_t);
	    hf.h_first = va_arg(va, history_gfun_t);
	    hf.h_next  = va_arg(va, history_gfun_t);
	    hf.h_last  = va_arg(va, history_gfun_t);
	    hf.h_prev  = va_arg(va, history_gfun_t);
	    hf.h_curr  = va_arg(va, history_gfun_t);
	    hf.h_clear = va_arg(va, history_vfun_t);
	    hf.h_enter = va_arg(va, history_efun_t);
	    hf.h_add   = va_arg(va, history_efun_t);

	    if ((retval = history_set_fun(h, &hf)) == -1)
		he_seterrev(ev, _HE_PARAM_MISSING);
	}
	break;

    case H_END:
	history_end(h);
	retval = 0;
	break;

    case H_GETSIZE:
	retval = history_get_size(h, ev);
	break;

    default:
	retval = -1;
	he_seterrev(ev, _HE_UNKNOWN);
	break;
    }
    va_end(va);
    return retval;
}
