/* $XConsortium: Events.h,v 1.2 93/09/23 18:57:02 rws Exp $ */
/*

Copyright 1993 by Davor Matic

Permission to use, copy, modify, distribute, and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation.  Davor Matic makes no representations about
the suitability of this software for any purpose.  It is provided "as
is" without express or implied warranty.

*/

#ifndef XNESTEVENTS_H
#define XNESTEVENTS_H

#include <X11/Xmd.h>

#define ProcessedExpose (LASTEvent + 1)

extern CARD32 lastEventTime;

void xnestCollectExposures();
void xnestCollectEvents();

#endif /* XNESTEVENTS_H */
