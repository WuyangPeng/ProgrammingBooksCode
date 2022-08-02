/* $XFree86: xc/programs/Xserver/hw/xfree86/os-support/os2/os2_init.c,v 3.11.2.1 1997/05/11 05:04:25 dawes Exp $ */
/*
 * (c) Copyright 1994 by Holger Veit
 *			<Holger.Veit@gmd.de>
 * Modified 1996 Sebastien Marineau <marineau@genie.uottawa.ca>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL 
 * HOLGER VEIT  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF 
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 * SOFTWARE.
 * 
 * Except as contained in this notice, the name of Holger Veit shall not be
 * used in advertising or otherwise to promote the sale, use or other dealings
 * in this Software without prior written authorization from Holger Veit.
 *
 */
/* $XConsortium: os2_init.c /main/9 1996/10/19 18:07:13 kaleb $ */

#include "X.h"
#include "Xmd.h"
#include "input.h"
#include "scrnintstr.h"

#include "compiler.h"

#define I_NEED_OS2_H
#define INCL_DOSFILEMGR
#define INCL_KBD
#define INCL_VIO
#define INCL_DOSMISC
#define INCL_DOSPROCESS
#define INCL_DOSSEMAPHORES
#define INCL_DOSMODULEMGR
#define INCL_DOSFILEMGR
#include "xf86.h"
#include "xf86Procs.h"
#include "xf86_OSlib.h"

VIOMODEINFO OriginalVideoMode;
void os2VideoNotify();
void os2HardErrorNotify();
void os2KbdMonitorThread();
void os2KbdBitBucketThread();
HEV hevPopupPending;
extern HEV hKbdSem;
extern BOOL os2HRTimerFlag;
extern void os2_checkinstallation(); /* os2_diag.c */

void xf86OpenConsole()
{
    /* try to catch problems before they become obvious */
    os2_checkinstallation();

    if (serverGeneration == 1) {
	HKBD fd;
	ULONG drive;
	ULONG dummy;
	KBDHWID hwid;
	APIRET rc;
	int VioTid;
        ULONG actual_handles;
        LONG new_handles;

	/* hv 250197 workaround for xkb-Problem: switch to X11ROOT drive */
	char *x11r = getenv("X11ROOT");
        /* Make sure X11ROOT is set before we go further sm280297 */
        if (x11r == NULL){ 
           ErrorF("The environment variable X11ROOT is not set! The xserver is aborting.\n");	
           exit(1);  
           }
        if (_chdir2(x11r) < 0) {
		ErrorF("xf86-OS/2: Cannot change to X11ROOT directory!\n");
	}

	ErrorF("xf86-OS/2: Console opened\n");
	OriginalVideoMode.cb=sizeof(VIOMODEINFO);
	rc=VioGetMode(&OriginalVideoMode,(HVIO)0);
	if(rc!=0) ErrorF("xf86-OS/2: Could not get original video mode. RC=%d\n",rc);
	xf86Info.consoleFd = -1;
        
        /* Set the number of handles to higher than the default 20. Set to 80 which should be plenty */
        new_handles = 0;
        rc = DosSetRelMaxFH(&new_handles,&actual_handles);
        if (actual_handles < 80) {
		new_handles = 80 - actual_handles;
		rc = DosSetRelMaxFH(&new_handles,&actual_handles);
		ErrorF("xf86-OS/2: Increased number of available handles to %d\n",actual_handles);
	}

	/* grab the keyboard */
	rc = KbdGetFocus(0,0);
	if (rc != 0)
		FatalError("xf86OpenConsole: cannot grab kbd focus, rc=%d\n",rc);

	/* open the keyboard */
	rc = KbdOpen(&fd);
	if (rc != 0)
		FatalError("xf86OpenConsole: cannot open keyboard, rc=%d\n",rc);
	xf86Info.consoleFd = fd;

	ErrorF("xf86-OS/2: Keyboard opened\n");

	/* assign logical keyboard */
	KbdFreeFocus(0);
	rc = KbdGetFocus(0,fd);
	if (rc != 0)
		FatalError("xf86OpenConsole: cannot set local kbd focus, rc=%d\n",rc);

/* Create kbd queue semaphore */
 
         rc = DosCreateEventSem(NULL,&hKbdSem,DC_SEM_SHARED,TRUE);
         if (rc != 0)
                  FatalError("xf86OpenConsole: cannot create keyboard queue semaphore, rc=%d\n",rc);
 
/* Create popup semaphore */

	rc=DosCreateEventSem("\\SEM32\\XF86PUP",&hevPopupPending,DC_SEM_SHARED,1);
	if(rc) ErrorF("xf86-OS/2: Could not create popup semaphore! RC=%d\n",rc);
	/* rc=VioRegister("xf86vio","XF86POPUP_SUBCLASS",0x20002004L,0L);
	if(rc) {
		FatalError("xf86-OS2: Could not register XF86VIO.DLL module. Please install in LIBPATH! RC=%d\n",rc);
	}  */

/* Start up the VIO monitor thread */
	VioTid=_beginthread(os2VideoNotify,NULL,0x4000,(void *)NULL);
	ErrorF("xf86-OS/2: Started Vio thread, Tid=%d\n",VioTid);
	rc=DosSetPriority(2,3,0,VioTid);

/* Start up the hard-error VIO monitor thread */
	VioTid=_beginthread(os2HardErrorNotify,NULL,0x4000,(void *)NULL);
	ErrorF("xf86-OS/2: Started hard error Vio mode monitor thread, Tid=%d\n",VioTid);
	rc=DosSetPriority(2,3,0,VioTid);

/* Start up the kbd monitor thread */
	VioTid=_beginthread(os2KbdMonitorThread,NULL,0x4000,(void *)NULL);
	ErrorF("xf86-OS/2: Started Kbd monitor thread, Tid=%d\n",VioTid);
	rc=DosSetPriority(2,3,0,VioTid);

/* Disable hard-errors through DosError */
	rc = DosQuerySysInfo(5,5,&drive,sizeof(drive));
	rc = DosSuppressPopUps(0x0001L,drive+96);     /* Disable popups */
	
	rc = KbdSetCp(0,0,fd);
	if(rc != 0)
		FatalError("xf86-OS/2: xf86OpenConsole: cannot set keyboard codepage, rc=%d\n",rc);

	hwid.cb = sizeof(hwid);	/* fix crash on P9000 */
	rc = KbdGetHWID(&hwid, fd);
	if (rc == 0) {
		switch (hwid.idKbd) {
		default:
		case 0xab54: /* 88/89 key */
		case 0:	/*unknown*/
		case 1: /*real AT 84 key*/
			xf86Info.kbdType = KB_84; break;
		case 0xab85: /* 122 key */
			FatalError("xf86-OS/2: OS/2 has detected an extended 122key keyboard: unsupported!\n");
		case 0xab41: /* 101/102 key */
			xf86Info.kbdType = KB_101; break;
		}				
	} else
		xf86Info.kbdType = KB_84; /*defensive*/

/* Start up the Kbd bit-bucket thread. We don't want to leave the kbd events in the driver queue */
	VioTid=_beginthread(os2KbdBitBucketThread,NULL,0x2000,(void *)NULL);
	ErrorF("xf86-OS/2: Started Kbd bit-bucket thread, Tid=%d\n",VioTid);

	xf86Config(FALSE); /* Read XF86Config */
    }
    return;
}

void xf86CloseConsole()
{
	APIRET rc;
	ULONG drive;

	if (xf86Info.consoleFd != -1) {
		KbdClose(xf86Info.consoleFd);
	}
	VioSetMode(&OriginalVideoMode,(HVIO)0);
	rc = DosQuerySysInfo(5,5,&drive,sizeof(drive));
	rc = DosSuppressPopUps(0x0000L,drive+96);    /* Reenable popups */
	rc = DosCloseEventSem(hevPopupPending);
	rc = VioDeRegister();
	return;
}

/* ARGSUSED */
int xf86ProcessArgument (argc, argv, i)
int argc;
char *argv[];
int i;
{
	if (!strcmp(argv[i], "-os2HRTimer")) {
		os2HRTimerFlag = TRUE;
		return 1;
	}
	return 0;
}

void xf86UseMsg()
{
        ErrorF("-os2HRTimer    -use the OS/2 high-resolution timer driver (TIMER0.SYS)\n");
	return;
}
