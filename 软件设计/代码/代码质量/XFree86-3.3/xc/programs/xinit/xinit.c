/* $XConsortium: xinit.c /main/58 1996/02/22 10:37:38 kaleb $ */
/* $XFree86: xc/programs/xinit/xinit.c,v 3.17 1997/01/18 07:03:01 dawes Exp $ */

/*

Copyright (c) 1986  X Consortium

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the X Consortium.

*/

#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xmu/SysUtil.h>
#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#ifndef SYSV
#include <sys/wait.h>
#endif
#include <errno.h>
#include <setjmp.h>

#if !defined(SIGCHLD) && defined(SIGCLD)
#define SIGCHLD SIGCLD
#endif
#ifdef __EMX__
#define INCL_DOSMODULEMGR
#include <os2.h>
#define setpgid(a,b)
#define setuid(a)
#define setgid(a)
#define SHELL "cmd.exe"
#define XINITRC "xinitrc.cmd"
#define XSERVERRC "xservrc.cmd"
char **envsave;	/* to circumvent an EMX problem */
#define environ envsave
#endif

#ifndef X_NOT_STDC_ENV
#include <stdlib.h>
#else
extern char *getenv();
#endif
extern char **environ;
char **newenviron = NULL;

#ifndef SHELL
#define SHELL "sh"
#endif

#ifndef HAS_VFORK
#define vfork() fork()
#else
#if defined(sun) && !defined(SVR4)
#include <vfork.h>
#endif
#endif

/* A/UX setpgid incorrectly removes the controlling terminal.
   Per Posix, only setsid should do that. */
#if !defined(X_NOT_POSIX) && !defined(macII)
#define setpgrp setpgid
#endif

#ifdef __EMX__
#define HAS_EXECVPE
#endif

#ifdef HAS_EXECVPE
#define Execvpe(path, argv, envp) execvpe(path, argv, envp)
#else
#define Execvpe(path, argv, envp) execvp(path, argv)
#endif

char *bindir = BINDIR;
char *server_names[] = {
#if defined(ultrix) && defined(mips)
    "Xdec        Digital color display on DECstation",
#endif
#ifdef sun				/* Sun */
    "Xsun        Sun BW2, CG2, CG3, CG4, or CG6 on Sun 2, 3, 4, or 386i",
    "Xsunmono    Sun BW2 on Sun 2, 3, 4, or 386i ",
    "Xsun24      Sun BW2, CG2, CG3, CG4, CG6, or CG8 on Sun 4",
#endif
#ifdef hpux				/* HP */
    "Xhp         HP monochrome and colors displays on 9000/300 series",
#endif
#ifdef ibm				/* IBM */
    "Xibm        IBM AED, APA, 8514a, megapel, VGA displays on PC/RT",
#endif
#ifdef macII				/* MacII */
    "XmacII      Apple monochrome display on Macintosh II",
#endif
#ifdef XFREE86
    "XF86_SVGA   SVGA color display on i386 PC",
    "XF86_Mono   monochrome display on i386 PC",
    "XF86_VGA16  16 color VGA display on i386 PC",
    "XF86_S3     S3 color display on i386 PC",
    "XF86_S3V    S3 ViRGE color display on i386 PC",
    "XF86_8514   IBM 8514/A color display on i386 PC",
    "XF86_Mach8  ATI Mach8 color display on i386 PC",
    "XF86_Mach32 ATI Mach32 color display on i386 PC",
    "XF86_Mach64 ATI Mach64 color display on i386 PC",
    "XF86_P9000  Weitek P9000 color display on i386 PC",
    "XF86_AGX    IIT AGX color display on i386 PC",
    "XF86_W32    Tseng ET4000/W32 color display on i386 PC",
    "XF86_I128   #9 I128 color display on i386 PC",
#endif
    NULL};

#ifndef XINITRC
#define XINITRC ".xinitrc"
#endif
char xinitrcbuf[256];

#ifndef XSERVERRC
#define XSERVERRC ".xserverrc"
#endif
char xserverrcbuf[256];

#define	TRUE		1
#define	FALSE		0
#define	OK_EXIT		0
#define	ERR_EXIT	1

char *default_server = "X";
char *default_display = ":0";		/* choose most efficient */
#ifndef __EMX__
char *default_client[] = {"xterm", "-geometry", "+1+1", "-n", "login", NULL};
#else
char *default_client[] = {"/XFree86/bin/xterm.exe", "-geometry", "+1+1", "-n", "login", NULL};
#endif
char *serverargv[100];
char *clientargv[100];
char **server = serverargv + 2;		/* make sure room for sh .xserverrc args */
char **client = clientargv + 2;		/* make sure room for sh .xinitrc args */
char *displayNum;
char *program;
Display *xd;			/* server connection */
#ifndef SYSV
#if defined(SVR4) || defined(_POSIX_SOURCE) || defined(CSRG_BASED) || defined(__EMX__) || defined(Lynx)
int status;
#else
union wait	status;
#endif
#endif /* SYSV */
int serverpid = -1;
int clientpid = -1;

#ifdef X_NOT_STDC_ENV
extern int errno;
#endif


static void shutdown();
static void set_environment();

#ifdef SIGNALRETURNSINT
#define SIGVAL int
#else
#define SIGVAL void
#endif

SIGVAL sigCatch(sig)
	int	sig;
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	Error("unexpected signal %d\r\n", sig);
	shutdown();
	exit(1);
}

SIGVAL sigAlarm(sig)
	int sig;
{
#if defined(SYSV) || defined(SVR4) || defined(linux) || defined(__EMX__)
	signal (sig, sigAlarm);
#endif
}

SIGVAL
sigUsr1(sig)
	int sig;
{
#if defined(SYSV) || defined(SVR4) || defined(linux) || defined(__EMX__)
	signal (sig, sigUsr1);
#endif
}

static void Execute (vec, envp)
    char **vec;				/* has room from up above */
    char **envp;
{
    Execvpe (vec[0], vec, envp);
#ifndef __EMX__
    if (access (vec[0], R_OK) == 0) {
	vec--;				/* back it up to stuff shell in */
	vec[0] = SHELL;
	Execvpe (vec[0], vec, envp);
    }
#endif
    return;
}

#ifndef __EMX__
main(argc, argv)
int argc;
register char **argv;
#else
main(int argc, char **argv, char **envp)
#endif
{
	register char **sptr = server;
	register char **cptr = client;
	register char **ptr;
	int pid;
	int client_given = 0, server_given = 0;
	int client_args_given = 0, server_args_given = 0;
	int start_of_client_args, start_of_server_args;
#ifdef __EMX__
	envsave = envp;	/* circumvent an EMX problem */

	/* Check whether the system will run at all */
	if (_emx_rev < 50) {
		APIRET rc;
		HMODULE hmod;
		char name[CCHMAXPATH];
		char fail[9];
		fputs ("This program requires emx.dll revision 50 (0.9c) "
			"or later.\n", stderr);
		rc = DosLoadModule (fail, sizeof (fail), "emx", &hmod);
		if (rc == 0) {
			rc = DosQueryModuleName (hmod, sizeof (name), name);
			if (rc == 0)
				fprintf (stderr, "Please delete or update `%s'.\n", name);
			DosFreeModule (hmod);
		}
		exit (2);
	}
#endif
	program = *argv++;
	argc--;
	/*
	 * copy the client args.
	 */
	if (argc == 0 ||
#ifndef __EMX__
	    (**argv != '/' && **argv != '.')) {
#else
	    (**argv != '/' && **argv != '\\' && **argv != '.' &&
	     !(isalpha(**argv) && (*argv)[1]==':'))) {
#endif
		for (ptr = default_client; *ptr; )
			*cptr++ = *ptr++;
#ifdef sun
		/* 
		 * If running on a sun, and if WINDOW_PARENT isn't defined, 
		 * that means SunWindows isn't running, so we should pass 
		 * the -C flag to xterm so that it sets up a console.
		 */
		if ( getenv("WINDOW_PARENT") == NULL )
		    *cptr++ = "-C";
#endif /* sun */
	} else {
		client_given = 1;
	}
	start_of_client_args = (cptr - client);
	while (argc && strcmp(*argv, "--")) {
		client_args_given++;
		*cptr++ = *argv++;
		argc--;
	}
	*cptr = NULL;
	if (argc) {
		argv++;
		argc--;
	}

	/*
	 * Copy the server args.
	 */
	if (argc == 0 ||
#ifndef __EMX__
	    (**argv != '/' && **argv != '.')) {
		*sptr++ = default_server;
#else
	    (**argv != '/' && **argv != '\\' && **argv != '.' &&
	     !(isalpha(**argv) && (*argv)[1]==':'))) {
		*sptr = getenv("XSERVER");
		if (!*sptr) {
			Error("No XSERVER environment variable set");
			exit(1);
		}
		*sptr++;
#endif
	} else {
		server_given = 1;
		*sptr++ = *argv++;
		argc--;
	}
	if (argc > 0 && (argv[0][0] == ':' && isdigit(argv[0][1])))
		displayNum = *argv;
	else
		displayNum = *sptr++ = default_display;

	start_of_server_args = (sptr - server);
	while (--argc >= 0) {
		server_args_given++;
		*sptr++ = *argv++;
	}
	*sptr = NULL;

	/*
	 * if no client arguments given, check for a startup file and copy
	 * that into the argument list
	 */
	if (!client_given) {
	    char *cp;
	    Bool required = False;

	    xinitrcbuf[0] = '\0';
	    if ((cp = getenv ("XINITRC")) != NULL) {
		strcpy (xinitrcbuf, cp);
		required = True;
	    } else if ((cp = getenv ("HOME")) != NULL) {
		(void) sprintf (xinitrcbuf, "%s/%s", cp, XINITRC);
	    }
	    if (xinitrcbuf[0]) {
		if (access (xinitrcbuf, F_OK) == 0) {
		    client += start_of_client_args - 1;
		    client[0] = xinitrcbuf;
		} else if (required) {
		    fprintf (stderr,
			     "%s:  warning, no client init file \"%s\"\n",
			     program, xinitrcbuf);
		}
	    }
	}

	/*
	 * if no server arguments given, check for a startup file and copy
	 * that into the argument list
	 */
	if (!server_given) {
	    char *cp;
	    Bool required = False;

	    xserverrcbuf[0] = '\0';
	    if ((cp = getenv ("XSERVERRC")) != NULL) {
		strcpy (xserverrcbuf, cp);
		required = True;
	    } else if ((cp = getenv ("HOME")) != NULL) {
		(void) sprintf (xserverrcbuf, "%s/%s", cp, XSERVERRC);
	    }
	    if (xserverrcbuf[0]) {
		if (access (xserverrcbuf, F_OK) == 0) {
		    server += start_of_server_args - 1;
		    server[0] = xserverrcbuf;
		} else if (required) {
		    fprintf (stderr,
			     "%s:  warning, no server init file \"%s\"\n",
			     program, xserverrcbuf);
		}
	    }
	}


	/*
	 * put the display name into the environment
	 */
	set_environment ();

	/*
	 * Start the server and client.
	 */
#ifdef SIGCHLD
	signal(SIGCHLD, SIG_DFL);	/* Insurance */
#endif
	signal(SIGQUIT, sigCatch);
	signal(SIGINT, sigCatch);
	signal(SIGHUP, sigCatch);
	signal(SIGPIPE, sigCatch);
	signal(SIGALRM, sigAlarm);
	signal(SIGUSR1, sigUsr1);
	if (startServer(server) > 0
	 && startClient(client) > 0) {
		pid = -1;
		while (pid != clientpid && pid != serverpid)
			pid = wait(NULL);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);

	shutdown();

	if (serverpid < 0 )
		Fatal("Server error.\n");
	if (clientpid < 0)
		Fatal("Client error.\n");
	exit(OK_EXIT);
}


/*
 *	waitforserver - wait for X server to start up
 */

waitforserver()
{
	int	ncycles	 = 120;		/* # of cycles to wait */
	int	cycles;			/* Wait cycle count */

	for (cycles = 0; cycles < ncycles; cycles++) {
		if (xd = XOpenDisplay(displayNum)) {
			return(TRUE);
		}
		else {
#define MSG "X server to begin accepting connections"
		    if (!processTimeout (1, MSG)) 
		      break;
#undef MSG
		}
	}

	fprintf (stderr, "giving up.\r\n");
	return(FALSE);
}

/*
 * return TRUE if we timeout waiting for pid to exit, FALSE otherwise.
 */
processTimeout(timeout, string)
	int	timeout;
	char	*string;
{
	int	i = 0, pidfound = -1;
	static char	*laststring;

	for (;;) {
#if defined(SYSV) || defined(__EMX__)
		alarm(1);
		if ((pidfound = wait(NULL)) == serverpid)
			break;
		alarm(0);
#else /* SYSV */
#if defined(SVR4) || defined(_POSIX_SOURCE) || defined(Lynx)
		if ((pidfound = waitpid(serverpid, &status, WNOHANG)) == serverpid)
			break;
#else
		if ((pidfound = wait3(&status, WNOHANG, NULL)) == serverpid)
			break;
#endif
#endif /* SYSV */
		if (timeout) {
			if (i == 0 && string != laststring)
				fprintf(stderr, "\r\nwaiting for %s ", string);
			else
				fprintf(stderr, ".");
			fflush(stderr);
		}
		if (timeout)
			sleep (1);
		if (++i > timeout)
			break;
	}
	if ( i > 0 ) fputc( '\n', stderr );     /* tidy up after message */
	laststring = string;
	return( serverpid != pidfound );
}

startServer(server)
	char *server[];
{
	serverpid = vfork();
	switch(serverpid) {
	case 0:
		/*
		 * don't hang on read/write to control tty
		 */
#ifdef SIGTTIN
		(void) signal(SIGTTIN, SIG_IGN);
#endif
#ifdef SIGTTOU
		(void) signal(SIGTTOU, SIG_IGN);
#endif
		/*
		 * ignore SIGUSR1 in child.  The server
		 * will notice this and send SIGUSR1 back
		 * at xinit when ready to accept connections
		 */
		(void) signal(SIGUSR1, SIG_IGN);
		/*
		 * prevent server from getting sighup from vhangup()
		 * if client is xterm -L
		 */
#ifndef __EMX__
		setpgrp(0,getpid());
#endif
		Execute (server, environ);
		Error ("no server \"%s\" in PATH\n", server[0]);
		{
		    char **cpp;

		    fprintf (stderr,
"\nUse the -- option, or make sure that %s is in your path and\n",
			     bindir);
		    fprintf (stderr,
"that \"%s\" is a program or a link to the right type of server\n",
			     server[0]);
		    fprintf (stderr,
"for your display.  Possible server names include:\n\n");
		    for (cpp = server_names; *cpp; cpp++) {
			fprintf (stderr, "    %s\n", *cpp);
		    }
		    fprintf (stderr, "\n");
		}
		exit (ERR_EXIT);

		break;
	case -1:
		break;
	default:
		/*
		 * don't nice server
		 */
#ifdef PRIO_PROCESS
		setpriority( PRIO_PROCESS, serverpid, -1 );
#endif

		errno = 0;
		if (! processTimeout(0, "")) {
			serverpid = -1;
			break;
		}
		/*
		 * kludge to avoid race with TCP, giving server time to
		 * set his socket options before we try to open it,
		 * either use the 15 second timeout, or await SIGUSR1.
		 *
		 * If your machine is substantially slower than 15 seconds,
		 * you can easily adjust this value.
		 */
		alarm (15);
		pause ();
		alarm (0);

		if (waitforserver() == 0) {
			Error("unable to connect to X server\r\n");
			shutdown();
			serverpid = -1;
		}
		break;
	}

	return(serverpid);
}

startClient(client)
	char *client[];
{
	if ((clientpid = vfork()) == 0) {
		setuid(getuid());
		setpgrp(0, getpid());
		environ = newenviron;
#ifdef __EMX__
#undef environ
		environ = newenviron;
		client[0] = (char*)__XOS2RedirRoot(client[0]);
#endif
		Execute (client,newenviron);
		Error ("no program named \"%s\" in PATH\r\n", client[0]);
		fprintf (stderr,
"\nSpecify a program on the command line or make sure that %s\r\n", bindir);
		fprintf (stderr,
"is in your path.\r\n");
		fprintf (stderr, "\n");
		exit (ERR_EXIT);
	}
	return (clientpid);
}

#if !defined(X_NOT_POSIX) || defined(SYSV) || defined(__EMX__)
#define killpg(pgrp, sig) kill(-(pgrp), sig)
#endif

static jmp_buf close_env;

static int ignorexio (dpy)
    Display *dpy;
{
    fprintf (stderr, "%s:  connection to X server lost.\r\n", program);
    longjmp (close_env, 1);
    /*NOTREACHED*/
}

static
void shutdown()
{
	/* have kept display opened, so close it now */
	if (clientpid > 0) {
		XSetIOErrorHandler (ignorexio);
		if (! setjmp(close_env)) {
		    XCloseDisplay(xd);
		}

		/* HUP all local clients to allow them to clean up */
		errno = 0;
		if ((killpg(clientpid, SIGHUP) != 0) &&
		    (errno != ESRCH))
			Error("can't send HUP to process group %d\r\n",
				clientpid);
	}

	if (serverpid < 0)
		return;
	errno = 0;
	if (killpg(serverpid, SIGTERM) < 0) {
		if (errno == EPERM)
			Fatal("Can't kill X server\r\n");
		if (errno == ESRCH)
			return;
	}
	if (! processTimeout(10, "X server to shut down")) {
	    fprintf (stderr, "\r\n");
	    return;
	}

	fprintf(stderr, 
	"\r\n%s:  X server slow to shut down, sending KILL signal.\r\n",
		program);
	fflush(stderr);
	errno = 0;
	if (killpg(serverpid, SIGKILL) < 0) {
		if (errno == ESRCH)
			return;
	}
	if (processTimeout(3, "server to die")) {
		fprintf (stderr, "\r\n");
		Fatal("Can't kill server\r\n");
	}
	fprintf (stderr, "\r\n");
	return;
}


/*
 * make a new copy of environment that has room for DISPLAY
 */

static void set_environment ()
{
    int nenvvars;
    char **newPtr, **oldPtr;
    static char displaybuf[256];

    /* count number of environment variables */
    for (oldPtr = environ; *oldPtr; oldPtr++) ;

    nenvvars = (oldPtr - environ);
    newenviron = (char **) malloc ((nenvvars + 2) * sizeof(char **));
    if (!newenviron) {
	fprintf (stderr,
		 "%s:  unable to allocate %d pointers for environment\n",
		 program, nenvvars + 2);
	exit (1);
    }

    /* put DISPLAY=displayname as first element */
    strcpy (displaybuf, "DISPLAY=");
    strcpy (displaybuf + 8, displayNum);
    newPtr = newenviron;
    *newPtr++ = displaybuf;

    /* copy pointers to other variables */
    for (oldPtr = environ; *oldPtr; oldPtr++) {
	if (strncmp (*oldPtr, "DISPLAY=", 8) != 0) {
	    *newPtr++ = *oldPtr;
	}
    }
    *newPtr = NULL;
    return;
}

Fatal(fmt, x0,x1,x2,x3,x4,x5,x6,x7,x8,x9)
	char	*fmt;
{
	Error(fmt, x0,x1,x2,x3,x4,x5,x6,x7,x8,x9);
	exit(ERR_EXIT);
}

Error(fmt, x0,x1,x2,x3,x4,x5,x6,x7,x8,x9)
	char	*fmt;
{
	fprintf(stderr, "%s:  ", program);
	if (errno > 0)
	  fprintf (stderr, "%s (errno %d):  ", strerror(errno), errno);
	fprintf(stderr, fmt, x0,x1,x2,x3,x4,x5,x6,x7,x8,x9);
}
