/*
 * Copyright (c) 1997 Erez Zadok
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
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
 *      This product includes software developed by the University of
 *      California, Berkeley and its contributors.
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
 *
 *      %W% (Berkeley) %G%
 *
 * $Id: hlfsd.c,v 1.1.1.1 1997/12/22 22:29:04 cgd Exp $
 *
 * HLFSD was written at Columbia University Computer Science Department, by
 * Erez Zadok <ezk@cs.columbia.edu> and Alexander Dupuy <dupuy@cs.columbia.edu>
 * It is being distributed under the same terms and conditions as amd does.
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */
#include <am_defs.h>
#include <hlfsd.h>

/*
 * STATIC VARIABLES:
 */
static RETSIGTYPE proceed(int);
static RETSIGTYPE reaper(int);
static RETSIGTYPE reload(int);
static char *hlfs_group = DEFAULT_HLFS_GROUP;
static char default_dir_name[] = DEFAULT_DIRNAME;
static char *dir_name = default_dir_name;
static int printpid = 0;
static int stoplight = 0;
static void hlfsd_init(void);
static void usage(void);

static struct itimerval reloadinterval = {
  {DEFAULT_INTERVAL, 0},
  {DEFAULT_INTERVAL, 0}
};

/*
 * default mount options.
 */
static char default_mntopts[] = "ro,noac";

/*
 * GLOBALS:
 */
SVCXPRT *nfsxprt;
char *alt_spooldir = ALT_SPOOLDIR;
char *home_subdir = HOME_SUBDIR;
char *logfile = DEFAULT_LOGFILE;
char *progname;
char *slinkname = 0;
char hostname[MAXHOSTNAMELEN] = "localhost";
int cache_interval = DEFAULT_CACHE_INTERVAL;
int foreground = 1;		/* This is the top-level server */
int hlfs_gid = INVALIDID;
int masterpid = 0;
int noverify = 0;
int orig_umask;
int serverpid = 0;
nfstime startup;
pid_t mypid;			/* Current process id */
serv_state amd_state;
u_short nfs_port;

/* symbol must be available always */
#ifdef MOUNT_TABLE_ON_FILE
char *mnttab_file_name = MNTTAB_FILE_NAME;
#else /* not MOUNT_TABLE_ON_FILE */
char *mnttab_file_name = NULL;
#endif /* not MOUNT_TABLE_ON_FILE */

#ifdef DEBUG
int debug_flags = 0;
#endif /* DEBUG */

/* forward declarations */
void hlfsd_going_down(int rc);


static void
usage(void)
{
  fprintf(stderr,
	  "Usage: %s [-Cfhnpv] [-a altdir] [-c cache-interval] [-g group]\n",
	  progname);
  fprintf(stderr, "\t[-i interval] [-l logfile] [-o mntopts]\n");
  show_opts('x', xlog_opt);
#ifdef DEBUG
  show_opts('D', dbg_opt);
#endif /* DEBUG */
  fprintf(stderr, "\t[dir_name [subdir]]\n");
  exit(2);
}


int
main(int argc, char *argv[])
{
  char *dot;
  char *mntopts = (char *) NULL;
  char hostpid_fs[MAXHOSTNAMELEN + 1 + 16];	/* room for ":(pid###)" */
  char progpid_fs[PROGNAMESZ + 1 + 11];		/* room for ":pid" */
  char preopts[128];
  int forcecache = 0;
  int forcefast = 0;
  int mntflags = 0;
  int opt, ret;
  int opterrs = 0;
  int retry;
  int soNFS;			/* NFS socket */
  int s = -99;

  mntent_t mnt;
  nfs_args_t mountargs;
  struct dirent *direntry;
  struct group *grp;
  struct stat stmodes;
  DIR *mountdir;
  MTYPE_TYPE type = MOUNT_TYPE_NFS;

#ifdef HAVE_SIGACTION
  struct sigaction sa;
#endif /* not HAVE_SIGACTION */

#ifndef HAVE_TRANSPORT_TYPE_TLI
  struct sockaddr_in localsocket;
#endif /* not HAVE_TRANSPORT_TYPE_TLI */


  /* ensure that only root can run hlfsd */
  if (geteuid()) {
    fprintf(stderr, "hlfsd can only be run as root\n");
    exit(1);
  }
  setbuf(stdout, (char *) NULL);
  umask(0);

  /* get program name and truncate so we don't overflow progpid_fs */

  if ((progname = strrchr(argv[0], '/')) != NULL)
    progname++;
  else
    progname = argv[0];
  if ((int) strlen(progname) > PROGNAMESZ) /* truncate to reasonable size */
    progname[PROGNAMESZ] = '\0';

  while ((opt = getopt(argc, argv, "a:c:CD:fg:hi:l:no:px:v")) != -1)
    switch (opt) {

    case 'a':
      if (!optarg || optarg[0] != '/') {
	printf("%s: invalid directory for -a: %s\n",
	       progname, optarg);
	exit(3);
      }
      alt_spooldir = optarg;
      break;

    case 'c':
      if (!atoi(optarg)) {
	printf("%s: invalid interval for -c: %s\n",
	       progname, optarg);
	exit(3);
      }
      cache_interval = atoi(optarg);
      break;

    case 'C':
      forcecache++;
      break;

    case 'f':
      forcefast++;
      break;

    case 'g':
      hlfs_group = optarg;
      break;

    case 'i':
      if (!atoi(optarg)) {
	printf("%s: invalid interval for -i: %s\n",
	       progname, optarg);
	exit(3);
      }
      reloadinterval.it_interval.tv_sec = atoi(optarg);
      reloadinterval.it_value.tv_sec = atoi(optarg);
      break;

    case 'l':
      logfile = optarg;
      break;

    case 'n':
      noverify++;
      break;

    case 'o':
      mntopts = optarg;
      break;

    case 'p':
      printpid++;
      break;

    case 'v':
      fprintf(stderr, "%s\n", HLFSD_VERSION);
      exit(0);

    case 'x':
      opterrs += switch_option(optarg);
      break;

    case 'D':
#ifdef DEBUG
      opterrs += debug_option(optarg);
#else /* not DEBUG */
      fprintf(stderr, "%s: not compiled with DEBUG -- sorry.\n", progname);
#endif /* not DEBUG */
      break;

    case 'h':
    case '?':
      opterrs++;
    }

  /* set some default debugging options */
  if (xlog_level_init == ~0)
    switch_option("");
  /* need my pid before any dlog/plog */
  mypid = getpid();
#ifdef DEBUG
  switch_option("debug");
#endif /* DEBUG */

/*
 * Terminate if did not ask to forcecache (-C) and hlfsd would not be able
 * to set the minimum cache intervals.
 */
#if !defined(MNT2_NFS_OPT_ACREGMIN) && !defined(MNT2_NFS_OPT_NOAC) && !defined(HAVE_FIELD_NFS_ARGS_T_ACREGMIN)
  if (!forcecache) {
    fprintf(stderr, "%s: will not be able to turn off attribute caches.\n", progname);
    exit(1);
  }
#endif /* !defined(MNT2_NFS_OPT_ACREGMIN) && !defined(MNT2_NFS_OPT_NOAC) && !defined(HAVE_FIELD_NFS_ARGS_T_ACREGMIN) */


  switch (argc - optind) {
  case 2:
    home_subdir = argv[optind + 1];
  case 1:
    dir_name = argv[optind];
  case 0:
    break;
  default:
    opterrs++;
  }

  if (opterrs)
    usage();

  /* find gid for hlfs_group */
  if ((grp = getgrnam(hlfs_group)) == (struct group *) NULL) {
    fprintf(stderr, "%s: cannot get gid for group \"%s\".\n",
	    progname, hlfs_group);
  } else {
    hlfs_gid = grp->gr_gid;
  }

  /* get hostname for logging and open log before we reset umask */
  gethostname(hostname, MAXHOSTNAMELEN);
  if ((dot = strchr(hostname, '.')) != NULL)
    *dot = '\0';
  if (logfile)
    switch_to_logfile(logfile);
  orig_umask = umask(0);

#if defined(DEBUG) && !defined(MOUNT_TABLE_ON_FILE)
  if (debug_flags & D_MTAB)
    dlog("-D mtab option ignored");
#endif /* defined(DEBUG) && !defined(MOUNT_TABLE_ON_FILE) */

  /* avoid hanging on other NFS servers if started elsewhere */
  if (chdir("/") < 0)
    fatal("cannot chdir to /: %m");

  if (geteuid() != 0)
    fatal("must be root to mount filesystems");

  /*
   * dir_name must match "^(/.*)/([^/]+)$", and is split at last '/' with
   * slinkname = `basename $dir_name` - requires dir_name be writable
   */

  if (dir_name[0] != '/'
      || ((slinkname = strrchr(dir_name, '/')), *slinkname++ = '\0',
	  (dir_name[0] == '\0' || slinkname[0] == '\0'))) {
    if (slinkname)
      *--slinkname = '/';
    printf("%s: invalid mount directory/link %s\n",
	   progname, dir_name);
    exit(3);
  }

  if (!forcefast) {
    /* make sure mount point exists and is at least mode 555 */
    if (stat(dir_name, &stmodes) < 0)
      if (errno != ENOENT || mkdirs(dir_name, 0555) < 0
	  || stat(dir_name, &stmodes) < 0)
	fatalerror(dir_name);

    if ((stmodes.st_mode & 0555) != 0555) {
      fprintf(stderr, "%s: directory %s not read/executable\n",
	      progname, dir_name);
      plog(XLOG_WARNING, "directory %s not read/executable",
	   dir_name);
    }

    /* warn if extraneous stuff will be hidden by mount */
    if ((mountdir = opendir(dir_name)) == NULL)
      fatalerror(dir_name);

    while ((direntry = readdir(mountdir)) != NULL) {
      if (strncmp(".", direntry->d_name,
		  NAMLEN(direntry)) &&
	  strncmp("..", direntry->d_name,
		  NAMLEN(direntry)) &&
	  strncmp(slinkname, direntry->d_name,
		  NAMLEN(direntry)))
	break;
    }

    if (direntry != NULL) {
      fprintf(stderr, "%s: %s/%s will be hidden by mount\n",
	      progname, dir_name, direntry->d_name);
      plog(XLOG_WARNING, "%s/%s will be hidden by mount\n",
	   dir_name, direntry->d_name);
    }
    closedir(mountdir);

    /* make sure alternate spool dir exists */
    if ((errno = mkdirs(alt_spooldir, OPEN_SPOOLMODE))) {
      fprintf(stderr, "%s: cannot create alternate dir ",
	      progname);
      perror(alt_spooldir);
      plog(XLOG_ERROR, "cannot create alternate dir %s: %m",
	   alt_spooldir);
    }
    chmod(alt_spooldir, OPEN_SPOOLMODE);

    /* create failsafe link to alternate spool directory */
    slinkname[-1] = '/';	/* unsplit dir_name to include link */
    if (lstat(dir_name, &stmodes) == 0 &&
	(stmodes.st_mode & S_IFMT) != S_IFLNK) {
      fprintf(stderr, "%s: failsafe %s not a symlink\n",
	      progname, dir_name);
      plog(XLOG_WARNING, "failsafe %s not a symlink\n",
	   dir_name);
    } else {
      unlink(dir_name);

      if (symlink(alt_spooldir, dir_name) < 0) {
	fprintf(stderr,
		"%s: cannot create failsafe symlink %s -> ",
		progname, dir_name);
	perror(alt_spooldir);
	plog(XLOG_WARNING,
	     "cannot create failsafe symlink %s -> %s: %m",
	     dir_name, alt_spooldir);
      }
    }

    slinkname[-1] = '\0';	/* resplit dir_name */
  } /* end of "if (!forcefast) {" */

  /*
   * Register hlfsd as an nfs service with the portmapper.
   */
#ifdef HAVE_TRANSPORT_TYPE_TLI
  ret = create_nfs_service(&soNFS, &nfs_port, &nfsxprt, nfs_program_2);
#else /* not HAVE_TRANSPORT_TYPE_TLI */
  ret = create_nfs_service(&soNFS, &nfs_port, &nfsxprt, nfs_program_2);
#endif /* not HAVE_TRANSPORT_TYPE_TLI */
  if (ret != 0)
    fatal("cannot create NFS service");

#ifdef HAVE_SIGACTION
  sa.sa_handler = proceed;
  sa.sa_flags = 0;
  sigemptyset(&(sa.sa_mask));
  sigaddset(&(sa.sa_mask), SIGUSR2);
  sigaction(SIGUSR2, &sa, NULL);
#else /* not HAVE_SIGACTION */
  signal(SIGUSR2, proceed);
#endif /* not HAVE_SIGACTION */

  plog(XLOG_INFO, "Initializing hlfsd...");
  hlfsd_init();			/* start up child (forking) to run svc_run */

#ifdef HAVE_SIGACTION
  sa.sa_handler = reaper;
  sa.sa_flags = 0;
  sigemptyset(&(sa.sa_mask));
  sigaddset(&(sa.sa_mask), SIGCHLD);
  sigaction(SIGCHLD, &sa, NULL);
#else /* not HAVE_SIGACTION */
  signal(SIGCHLD, reaper);
#endif /* not HAVE_SIGACTION */

#ifdef DEBUG
  /*
   * In the parent, if -D nodaemon (or -D daemon) , we don't need to
   * set this signal handler.
   */
  amuDebug(D_DAEMON) {
#endif /* DEBUG */
    /* XXX: port to use pure svr4 signals */
    s = -99;
    while (stoplight != SIGUSR2) {
      plog(XLOG_INFO, "parent waits for child to setup (stoplight=%d)", stoplight);
      s = sigpause(0);		/* wait for child to set up */
      sleep(1);
    }
#ifdef DEBUG
  }
#endif /* DEBUG */

  /*
   * setup options to mount table (/etc/{mtab,mnttab}) entry
   */
  sprintf(hostpid_fs, "%s:(pid%d)", hostname, masterpid);
  memset((char *) &mnt, 0, sizeof(mnt));
  mnt.mnt_dir = dir_name;	/* i.e., "/mail" */
  mnt.mnt_fsname = hostpid_fs;
  if (mntopts) {
    mnt.mnt_opts = mntopts;
  } else {
    strcpy(preopts, default_mntopts);
    /*
     * Turn off all kinds of attribute and symlink caches as
     * much as possible.  Also make sure that mount does not
     * show up to df.
     */
#ifdef MNTTAB_OPT_INTR
    strcat(preopts, ",");
    strcat(preopts, MNTTAB_OPT_INTR);
#endif /* MNTTAB_OPT_INTR */
#ifdef MNTTAB_OPT_IGNORE
    strcat(preopts, ",");
    strcat(preopts, MNTTAB_OPT_IGNORE);
#endif /* MNTTAB_OPT_IGNORE */
#ifdef MNT2_GEN_OPT_CACHE
    strcat(preopts, ",nocache");
#endif /* MNT2_GEN_OPT_CACHE */
#ifdef MNT2_NFS_OPT_SYMTTL
    strcat(preopts, ",symttl=0");
#endif /* MNT2_NFS_OPT_SYMTTL */
    mnt.mnt_opts = preopts;
  }

  memset((char *) &mountargs, 0, sizeof(mountargs)); /* paranoid */

  /*
   * Make sure that amd's top-level NFS mounts are hidden by default
   * from df.
   * If they don't appear to support the either the "ignore" mnttab
   * option entry, or the "auto" one, set the mount type to "nfs".
   */
  mnt.mnt_type = HIDE_MOUNT_TYPE;
  /* some systems don't have a mount type, but a mount flag */
#ifdef MNT2_NFS_OPT_AUTO
  mountargs.flags |= MNT2_NFS_OPT_AUTO;
#endif /* MNT2_NFS_OPT_AUTO */

#ifdef HAVE_TRANSPORT_TYPE_TLI
  mountargs.addr = &nfsxprt->xp_ltaddr;

  /*
   * set up knconf field.
   * the allocated mountargs.knconf is not freed via free_knetconfig().
   */
  if (get_knetconfig(&mountargs.knconf, nfsncp, NULL) < 0) {
    plog(XLOG_ERROR, "cannot fill knetconfig structure for mountargs");
  }

  /*
   * set up syncaddr field
   */
  mountargs.syncaddr = (struct netbuf *) NULL;
#else /* not HAVE_TRANSPORT_TYPE_TLI */
  amu_get_myaddress(&localsocket.sin_addr);
  localsocket.sin_family = AF_INET;
  localsocket.sin_port = htons(nfsxprt->xp_port);

  NFS_SA_DREF(mountargs, &localsocket);
#endif /* not HAVE_TRANSPORT_TYPE_TLI */

  /*
   * Update filehandle field
   */
  NFS_FH_DREF(mountargs.NFS_FH_FIELD, root_fhp);

#ifdef HAVE_FIELD_NFS_ARGS_T_FHSIZE
  mountargs.fhsize = FHSIZE;
#endif /* HAVE_FIELD_NFS_ARGS_T_FHSIZE */

  /*
   * Update hostname field.
   * Make some name prog:pid (i.e., hlfsd:174) for hostname
   */
  sprintf(progpid_fs, "%s:%d", progname, masterpid);

  /* Most kernels have a name length restriction. */
  if ((int) strlen(progpid_fs) >= (int) MAXHOSTNAMELEN)
    strcpy(progpid_fs + MAXHOSTNAMELEN - 3, "..");

  NFS_HN_DREF(mountargs.hostname, progpid_fs);

  /*
   * General mount options
   */
#ifdef HAVE_TRANSPORT_TYPE_TLI
  mountargs.flags |= MNT2_NFS_OPT_KNCONF;
#endif /* HAVE_TRANSPORT_TYPE_TLI */

#ifdef MNT2_NFS_OPT_FSNAME
  mountargs.fsname = hostpid_fs;
  mountargs.flags |= MNT2_NFS_OPT_FSNAME;
#endif /* MNT2_NFS_OPT_FSNAME */

#ifdef MNT2_NFS_OPT_HOSTNAME
  mountargs.flags |= MNT2_NFS_OPT_HOSTNAME;
#endif /* MNT2_NFS_OPT_HOSTNAME */

  mountargs.timeo = hasmntval(&mnt, MNTTAB_OPT_TIMEO);
#ifdef MNT2_NFS_OPT_TIMEO
  if (mountargs.timeo)
    mountargs.flags |= MNT2_NFS_OPT_TIMEO;
#endif /* MNT2_NFS_OPT_TIMEO */

  mountargs.retrans = hasmntval(&mnt, MNTTAB_OPT_RETRANS);
#ifdef MNT2_NFS_OPT_RETRANS
  if (mountargs.retrans)
    mountargs.flags |= MNT2_NFS_OPT_RETRANS;
#endif /* MNT2_NFS_OPT_RETRANS */

  if (hasmntopt(&mnt, MNTTAB_OPT_SOFT) != NULL)
    mountargs.flags |= MNT2_NFS_OPT_SOFT;

#ifdef MNTTAB_OPT_INT
  if (hasmntopt(&mnt, MNTTAB_OPT_INTR) != NULL)
    mountargs.flags |= MNT2_NFS_OPT_INT;
#endif /* MNTTAB_OPT_INT */

#ifdef MNT2_NFS_OPT_BIODS
  if (mountargs.biods = hasmntval(&mnt, MNTTAB_OPT_BIODS))
    mountargs.flags |= MNT2_NFS_OPT_BIODS;
#endif /* MNT2_NFS_OPT_BIODS */

#ifdef MNT2_NFS_OPT_DUMBTIMR
  mountargs.flags |= MNT2_NFS_OPT_DUMBTIMR;
#endif /* MNT2_NFS_OPT_DUMBTIMR */

#ifdef MNT2_NFS_OPT_NOAC
  plog(XLOG_INFO, "turning on NFS option noac");
  mountargs.flags |= MNT2_NFS_OPT_NOAC;
#endif /* MNT2_NFS_OPT_NOAC */

#ifdef MNT2_NFS_OPT_ACREGMIN
  plog(XLOG_INFO, "turning on NFS option acregmin");
  mountargs.flags |= MNT2_NFS_OPT_ACREGMIN;
#endif /* MNT2_NFS_OPT_ACREGMIN */
#ifdef MNT2_NFS_OPT_ACREGMAX
  plog(XLOG_INFO, "turning on NFS option acregmax");
  mountargs.flags |= MNT2_NFS_OPT_ACREGMAX;
#endif /* MNT2_NFS_OPT_ACREGMAX */
#ifdef HAVE_FIELD_NFS_ARGS_T_ACREGMIN
  plog(XLOG_INFO, "setting NFS acregmin/max to %d", SYMTTL_ATTR_CACHE_VALUE);
  mountargs.acregmin = SYMTTL_ATTR_CACHE_VALUE;
  mountargs.acregmax = SYMTTL_ATTR_CACHE_VALUE;
#endif /* HAVE_FIELD_NFS_ARGS_T_ACREGMIN */

#ifdef MNT2_NFS_OPT_ACDIRMIN
  plog(XLOG_INFO, "turning on NFS option acdirmin");
  mountargs.flags |= MNT2_NFS_OPT_ACDIRMIN;
#endif /* MNT2_NFS_OPT_ACDIRMIN */
#ifdef MNT2_NFS_OPT_ACDIRMAX
  plog(XLOG_INFO, "turning on NFS option acdirmax");
  mountargs.flags |= MNT2_NFS_OPT_ACDIRMAX;
#endif /* MNT2_NFS_OPT_ACDIRMAX */
#ifdef HAVE_FIELD_NFS_ARGS_T_ACDIRMIN
  plog(XLOG_INFO, "setting NFS acdirmin/max to %d", SYMTTL_ATTR_CACHE_VALUE);
  mountargs.acdirmin = SYMTTL_ATTR_CACHE_VALUE;
  mountargs.acdirmax = SYMTTL_ATTR_CACHE_VALUE;
#endif /* HAVE_FIELD_NFS_ARGS_T_ACDIRMIN */

#ifdef MNT2_NFS_OPT_SYMTTL
  plog(XLOG_INFO, "turning on NFS option symttl and setting value to %d", SYMTTL_ATTR_CACHE_VALUE);
  mountargs.flags |= MNT2_NFS_OPT_SYMTTL;
  mountargs.symttl = SYMTTL_ATTR_CACHE_VALUE;
#endif /* MNT2_NFS_OPT_SYMTTL */

#if defined(MNT2_NFS_OPT_POSIX) && defined(MNTTAB_OPT_POSIX)
  if (hasmntopt(&mnt, MNTTAB_OPT_POSIX) != NULL) {
    mountargs.flags |= MNT2_NFS_OPT_POSIX;
    mountargs.pathconf = NULL;
  }
#endif /* MNT2_NFS_OPT_POSIX && MNTTAB_OPT_POSIX */

  mntflags = compute_mount_flags(&mnt);

#if defined(MNT2_GEN_OPT_OVERLAY) && defined(MNTTAB_OPT_OVERLAY)
  /*
   * Overlay this amd mount (presumably on another amd which died
   * before and left the machine hung).  This will allow a new amd or
   * hlfsd to be remounted on top of another one.
   *      -Erez Zadok <ezk@cs.columbia.edu>
   */
  if (hasmntopt(&mnt, MNTTAB_OPT_OVERLAY) != NULL) {
    mntflags |= MNT2_GEN_OPT_OVERLAY;
    plog(XLOG_INFO, "using and overlay mount");
  }
#endif /* defined(MNT2_GEN_OPT_OVERLAY) && defined(MNTTAB_OPT_OVERLAY) */

  retry = hasmntval(&mnt, MNTTAB_OPT_RETRY);

/*
 * The following code could be cleverly ifdef-ed, but I duplicated the
 * mount_fs call three times for simplicity and readability.
 */
#ifdef DEBUG
/*
 * For some reason, this mount may have to be done in the background, if I am
 * using -D nodebug.  I suspect that the actual act of mounting requires
 * calling to hlfsd itself to invoke one or more of its nfs calls, to stat
 * /mail.  That means that even if you say -D nodaemon, at least the mount
 * of hlfsd itself on top of /mail will be done in the background.
 * The other alternative I have is to run svc_run, but set a special
 * signal handler to perform the mount in N seconds via some alarm.
 *      -Erez Zadok.
 */
  if (debug_flags & D_DAEMON) {	/* asked for -D daemon */
    if (mount_fs(&mnt, mntflags, (caddr_t) & mountargs, retry, type, 0, NULL, mnttab_file_name) < 0)
      fatal("nfsmount: %m");
  } else {			/* asked for -D nodaemon */
    if (fork() == 0) {		/* child runs mount */
      if (mount_fs(&mnt, mntflags, (caddr_t) & mountargs, retry, type, 0, NULL, mnttab_file_name) < 0) {
	fatal("nfsmount: %m");
      }
      exit(0);			/* all went well */
    }
  }
#else /* not DEBUG */
  if (mount_fs(&mnt, mntflags, (caddr_t) & mountargs, retry, type, 2, "udp", mnttab_file_name) < 0)
    fatal("nfsmount: %m");
#endif /* not DEBUG */

  if (printpid)
    printf("%d\n", masterpid);

  plog(XLOG_INFO, "hlfsd ready to serve");
#ifdef DEBUG
  /*
   * If asked not to fork a daemon (-D nodaemon), then hlfsd_init()
   * will not run svc_run.  We must start svc_run here.
   */
  dlog("starting no-daemon debugging svc_run");
  amuDebugNo(D_DAEMON)
    svc_run();
#endif /* DEBUG */

  cleanup(0);			/* should never happen here */
  return (0);			/* everything went fine? */
}


static void
hlfsd_init(void)
{
  int child = 0;
#ifdef HAVE_SIGACTION
  struct sigaction sa;
#endif /* HAVE_SIGACTION */
#ifndef HAVE_SETPGRP
  int tty;
#endif /* not HAVE_SETPGRP */

  /*
   * Initialize file handles.
   */
  plog(XLOG_INFO, "initializing hlfsd file handles");
  hlfsd_init_filehandles();

#ifdef DEBUG
  /*
   * If -D daemon then we must fork.
   */
  amuDebug(D_DAEMON)
#endif /* DEBUG */
    child = fork();

  if (child < 0)
    fatal("fork: %m");

  if (child != 0) {		/* parent process - save child pid */
    masterpid = child;
    mypid = getpid();		/* for AMD routines */
    return;
  }

  /*
   * CHILD CODE:
   * initialize server
   */
  plog(XLOG_INFO, "initializing home directory database");
  init_homedir();
  plog(XLOG_INFO, "home directory database initialized");

  masterpid = serverpid = mypid = getpid();

  /*
   * SIGALRM/SIGHUP: reload password database if timer expired
   * or user sent HUP signal.
   */
#ifdef HAVE_SIGACTION
  sa.sa_handler = reload;
  sa.sa_flags = 0;
  sigemptyset(&(sa.sa_mask));
  sigaddset(&(sa.sa_mask), SIGALRM);
  sigaddset(&(sa.sa_mask), SIGHUP);
  sigaction(SIGALRM, &sa, NULL);
  sigaction(SIGHUP, &sa, NULL);
#else /* not HAVE_SIGACTION */
  signal(SIGALRM, reload);
  signal(SIGHUP, reload);
#endif /* not HAVE_SIGACTION */

  /*
   * SIGTERM: cleanup and exit.
   */
#ifdef HAVE_SIGACTION
  sa.sa_handler = cleanup;
  sa.sa_flags = 0;
  sigemptyset(&(sa.sa_mask));
  sigaddset(&(sa.sa_mask), SIGTERM);
  sigaction(SIGTERM, &sa, NULL);
#else /* not HAVE_SIGACTION */
  signal(SIGTERM, cleanup);
#endif /* not HAVE_SIGACTION */

  /*
   * SIGCHLD: interlock sycronization and testing
   */
#ifdef HAVE_SIGACTION
  sa.sa_handler = interlock;
  sa.sa_flags = 0;
  sigemptyset(&(sa.sa_mask));
  sigaddset(&(sa.sa_mask), SIGCHLD);
  sigaction(SIGCHLD, &sa, NULL);
#else /* not HAVE_SIGACTION */
  signal(SIGCHLD, interlock);
#endif /* not HAVE_SIGACTION */

  /*
   * SIGUSR1: dump internal hlfsd maps/cache to file
   */
#ifdef HAVE_SIGACTION
# if defined(DEBUG) || defined(DEBUG_PRINT)
  sa.sa_handler = plt_print;
# else /* not defined(DEBUG) || defined(DEBUG_PRINT) */
  sa.sa_handler = SIG_IGN;
# endif /* not defined(DEBUG) || defined(DEBUG_PRINT) */
  sa.sa_flags = 0;
  sigemptyset(&(sa.sa_mask));
  sigaddset(&(sa.sa_mask), SIGUSR1);
  sigaction(SIGUSR1, &sa, NULL);
#else /* not HAVE_SIGACTION */
# if defined(DEBUG) || defined(DEBUG_PRINT)
  signal(SIGUSR1, plt_print);
# else /* not defined(DEBUG) || defined(DEBUG_PRINT) */
  signal(SIGUSR1, SIG_IGN);
# endif /* not defined(DEBUG) || defined(DEBUG_PRINT) */
#endif /* not HAVE_SIGACTION */

  if (setitimer(ITIMER_REAL, &reloadinterval, (struct itimerval *) 0) < 0)
    fatal("setitimer: %m");

  gettimeofday((struct timeval *) &startup, (struct timezone *) 0);

#ifdef DEBUG
  /*
   * If -D daemon, then start serving here in the child,
   * and the parent will exit.  But if -D nodaemon, then
   * skip this code and make sure svc_run is entered elsewhere.
   */
  amuDebug(D_DAEMON) {
#endif /* DEBUG */

#ifdef HAVE_SETPGID
    setpgid(getpid(), getpid());
#else /* not HAVE_SETPGID */
# ifdef HAVE_SETPGRP
    setpgrp();
# else /* not HAVE_SETPGRP */
    if ((tty = open("/dev/tty", O_RDWR)) < 0) {
      /* not an error if already no ctty */
      if (errno != ENXIO)
	plog(XLOG_WARNING, "Could not open controlling tty: %m");
    } else {
      if (ioctl(tty, TIOCNOTTY, 0) < 0  &&  errno != ENOTTY)
	plog(XLOG_WARNING, "Could not disassociate tty (TIOCNOTTY): %m");
      close(tty);
    }
# endif /* not HAVE_SETPGRP */
#endif /* not HAVE_SETPGID */

    /*
     * signal parent we are ready. parent should
     * mount(2) and die.
     */
    if (kill(getppid(), SIGUSR2) < 0)
      fatal("kill: %m");
    plog(XLOG_INFO, "starting svc_run");
    svc_run();
    cleanup(0);		/* should never happen, just in case */
#ifdef DEBUG
  } /* end of code that runs iff hlfsd daemonizes */
#endif /* DEBUG */

}


static RETSIGTYPE
proceed(int signum)
{
  stoplight = signum;
}


static RETSIGTYPE
reload(int signum)
{
  int child;
  int status;

  if (getpid() != masterpid)
    return;

  /*
   * If received a SIGHUP, close and reopen the log file (so that it
   * can be rotated)
   */
  if (signum == SIGHUP && logfile)
    switch_to_logfile(logfile);

  if ((child = fork()) > 0) {
    serverpid = child;

    init_homedir();

    if (kill(child, SIGKILL) < 0) {
      plog(XLOG_ERROR, "kill child: %m");
    } else {			/* wait for child to die before continue */
      if (wait(&status) != child) {
	/*
	 * I took out this line because it generates
	 * annoying output.  It indicates a very
	 * small bug in hlfsd which is totally
	 * harmless.  It causes hlfsd to work a bit
	 * harder than it should.  Nevertheless, I
	 * intend on fixing it in a future release.
	 * Erez Zadok <ezk@cs.columbia.edu>
	 */
	/* plog(XLOG_ERROR, "unknown child"); */
      }
    }

    serverpid = masterpid;
  } else if (child < 0) {
    plog(XLOG_ERROR, "unable to fork: %m");
  } else			/* let child handle requests while we reload */
    serverpid = getpid();
}


RETSIGTYPE
cleanup(int signum)
{
  struct stat stbuf;
  int umount_result;

#ifdef DEBUG
  amuDebug(D_DAEMON)
#endif /* DEBUG */
    if (getpid() != masterpid)
    return;

#ifdef DEBUG
  amuDebug(D_DAEMON)
#endif /* DEBUG */
    if (fork() != 0) {
    masterpid = 0;
    return;
  }
  mypid = getpid();

  for (;;) {
    while ((umount_result = UMOUNT_FS(dir_name, mnttab_file_name)) == EBUSY) {
#ifdef DEBUG
      dlog("cleanup(): umount delaying for 10 seconds");
#endif /* DEBUG */
      sleep(10);
    }
    if (stat(dir_name, &stbuf) == 0 && stbuf.st_ino == ROOTID) {
      plog(XLOG_ERROR, "unable to unmount %s", dir_name);
      plog(XLOG_ERROR, "suspending, unmount before terminating");
      kill(mypid, SIGSTOP);
      continue;			/* retry unmount */
    }
    break;
  }

#ifdef DEBUG
  dlog("cleanup(): killing processes and terminating");
  amuDebug(D_DAEMON)
#endif /* DEBUG */
    kill(masterpid, SIGKILL);

#ifdef DEBUG
  amuDebug(D_DAEMON)
#endif /* DEBUG */
    kill(serverpid, SIGKILL);

  plog(XLOG_INFO, "hlfsd terminating with status 0\n");
  exit(0);
}


static RETSIGTYPE
reaper(int signum)
{
  int result;

  if (wait(&result) == masterpid) {
    exit(4);
  }
}


void
hlfsd_going_down(int rc)
{
  int mypid = getpid();

  if (mypid == masterpid)
    cleanup(0);
  else if (mypid == serverpid)
    kill(masterpid, SIGTERM);

  exit(rc);
}


void
fatal(char *mess)
{
  if (logfile && !STREQ(logfile, "stderr")) {
    char lessmess[128];
    int messlen;

    messlen = strlen(mess);

    if (!STREQ(&mess[messlen + 1 - sizeof(ERRM)], ERRM))
      fprintf(stderr, "%s: %s\n", progname, mess);
    else {
      strcpy(lessmess, mess);
      lessmess[messlen - 4] = '\0';

      if (errno < sys_nerr)
	fprintf(stderr, "%s: %s: %s\n", progname,
		lessmess, sys_errlist[errno]);
      else
	fprintf(stderr, "%s: %s: Error %d\n",
		progname, lessmess, errno);
    }
  }
  plog(XLOG_FATAL, mess);

  hlfsd_going_down(1);
}
