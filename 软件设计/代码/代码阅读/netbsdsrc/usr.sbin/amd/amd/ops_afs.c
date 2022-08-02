/*
 * Copyright (c) 1997 Erez Zadok
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
 * Copyright (c) 1990 The Regents of the University of California.
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
 * $Id: ops_afs.c,v 1.1.1.1 1997/12/22 22:28:30 cgd Exp $
 *
 */

/*
 * Automount file system
 * Direct file system
 * Root file system
 * Top-level file system
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */
#include <am_defs.h>
#include <amd.h>

/****************************************************************************
 *** MACROS                                                               ***
 ****************************************************************************/

/*
 * Interval between forced retries of a mount.
 */
#define RETRY_INTERVAL	2

#define	IN_PROGRESS(cp) ((cp)->mp->am_mnt->mf_flags & MFF_MOUNTING)
#define ereturn(x) { *error_return = x; return 0; }


/****************************************************************************
 *** STRUCTURES                                                           ***
 ****************************************************************************/

/*
 * Mounting a file system may take a significant period of time.  The
 * problem is that if this is done in the main process thread then
 * the entire automounter could be blocked, possibly hanging lots of
 * processes on the system.  Instead we use a continuation scheme to
 * allow mounts to be attempted in a sub-process.  When the sub-process
 * exits we pick up the exit status (by convention a UN*X error number)
 * and continue in a notifier.  The notifier gets handed a data structure
 * and can then determine whether the mount was successful or not.  If
 * not, it updates the data structure and tries again until there are no
 * more ways to try the mount, or some other permanent error occurs.
 * In the mean time no RPC reply is sent, even after the mount is succesful.
 * We rely on the RPC retry mechanism to resend the lookup request which
 * can then be handled.
 */
struct continuation {
  char **ivec;			/* Current mount info */
  am_node *mp;			/* Node we are trying to mount */
  char *key;			/* Map key */
  char *info;			/* Info string */
  char **xivec;			/* Saved strsplit vector */
  char *auto_opts;		/* Automount options */
  am_opts fs_opts;		/* Filesystem options */
  char *def_opts;		/* Default automount options */
  int retry;			/* Try again? */
  int tried;			/* Have we tried any yet? */
  time_t start;			/* Time we started this mount */
  int callout;			/* Callout identifier */
};


/****************************************************************************
 *** FORWARD DEFINITIONS                                                  ***
 ****************************************************************************/
static am_node * dfs_readlink(am_node *mp, int *error_return);
static am_node *afs_lookuppn(am_node *mp, char *fname, int *error_return, int op);
static char * afs_match(am_opts *fo);
static int afs_bgmount(struct continuation * cp, int mpe);
static int afs_mount(am_node *mp);
static int afs_readdir(am_node *mp, nfscookie cookie, nfsdirlist *dp, nfsentry *ep, int count);
static int afs_readdir_browsable(am_node *mp, nfscookie cookie, nfsdirlist *dp, nfsentry *ep, int count);
static int afs_umount(am_node *mp);
static int root_mount(am_node *mp);
static int toplvl_mount(am_node *mp);
static int toplvl_umount(am_node *mp);
static void afs_umounted(am_node *mp);
static void toplvl_mounted(mntfs *mf);
#ifdef HAVE_AM_FS_UNION
static void union_mounted(mntfs *mf);
#endif /* HAVE_AM_FS_UNION */



/****************************************************************************
 *** OPS STRUCTURES                                                       ***
 ****************************************************************************/

am_ops root_ops =
{
  "root",
  0,				/* root_match */
  0,				/* root_init */
  root_mount,
  0,
  afs_umount,
  0,
  afs_lookuppn,
  afs_readdir,
  0,				/* root_readlink */
  0,				/* root_mounted */
  0,				/* root_umounted */
  find_afs_srvr,
  FS_NOTIMEOUT | FS_AMQINFO | FS_DIRECTORY
};


am_ops afs_ops =
{
  "auto",
  afs_match,
  0,				/* afs_init */
  afs_mount,
  0,
  afs_umount,
  0,
  afs_lookuppn,
  afs_readdir,
  0,				/* afs_readlink */
  0,				/* afs_mounted */
  afs_umounted,
  find_afs_srvr,
  FS_AMQINFO | FS_DIRECTORY
};


am_ops toplvl_ops =
{
  "toplvl",
  afs_match,
  0,				/* afs_init */
  toplvl_mount,
  0,
  toplvl_umount,
  0,
  afs_lookuppn,
  afs_readdir,			/* the browsable version of afs_readdir */
  0,				/* toplvl_readlink */
  toplvl_mounted,
  0,				/* toplvl_umounted */
  find_afs_srvr,
  FS_MKMNT | FS_NOTIMEOUT | FS_BACKGROUND | FS_AMQINFO | FS_DIRECTORY
};


am_ops dfs_ops =
{
  "direct",
  afs_match,
  0,				/* dfs_init */
  toplvl_mount,
  0,
  toplvl_umount,
  0,
  efs_lookuppn,
  efs_readdir,
  dfs_readlink,
  toplvl_mounted,
  0,				/* afs_umounted */
  find_afs_srvr,
  FS_MKMNT | FS_NOTIMEOUT | FS_BACKGROUND | FS_AMQINFO
};


#ifdef HAVE_AM_FS_UNION
am_ops union_ops =
{
  "union",
  afs_match,
  0,				/* afs_init */
  toplvl_mount,
  0,
  toplvl_umount,
  0,
  afs_lookuppn,
  afs_readdir,
  0,				/* toplvl_readlink */
  union_mounted,
  0,				/* toplvl_umounted */
  find_afs_srvr,
  FS_MKMNT | FS_NOTIMEOUT | FS_BACKGROUND | FS_AMQINFO | FS_DIRECTORY
};
#endif /* HAVE_AM_FS_UNION */


#ifdef HAVE_AM_FS_AUTOFS
/* Sun's kernel-based automounter-supporting file system */
am_ops autofs_ops =
{
  "autofs",
  afs_match,
  0,				/* afs_init */
  autofs_mount,
  0,
  autofs_umount,
  0,
  afs_lookuppn,
  afs_readdir,			/* the browsable version of afs_readdir */
  0,				/* autofs_readlink */
  autofs_mounted,
  0,				/* autofs_umounted */
  find_afs_srvr,
  FS_MKMNT | FS_NOTIMEOUT | FS_BACKGROUND | FS_AMQINFO | FS_DIRECTORY
};
#endif /* HAVE_AM_FS_AUTOFS */


/****************************************************************************
 *** FUNCTIONS                                                             ***
 ****************************************************************************/
/*
 * AFS needs nothing in particular.
 */
static char *
afs_match(am_opts *fo)
{
  char *p = fo->opt_rfs;

  if (!fo->opt_rfs) {
    plog(XLOG_USER, "auto: no mount point named (rfs:=)");
    return 0;
  }
  if (!fo->opt_fs) {
    plog(XLOG_USER, "auto: no map named (fs:=)");
    return 0;
  }

  /*
   * Swap round fs:= and rfs:= options
   * ... historical (jsp)
   */
  fo->opt_rfs = fo->opt_fs;
  fo->opt_fs = p;

  /*
   * mtab entry turns out to be the name of the mount map
   */
  return strdup(fo->opt_rfs ? fo->opt_rfs : ".");
}


/*
 * Mount an automounter directory.
 * The automounter is connected into the system
 * as a user-level NFS server.  mount_toplvl constructs
 * the necessary NFS parameters to be given to the
 * kernel so that it will talk back to us.
 */
static int
mount_toplvl(char *dir, char *opts)
{
  char fs_hostname[MAXHOSTNAMELEN + MAXPATHLEN + 1];
  int retry, error, flags;
  mntent_t mnt;
  nfs_args_t nfs_args;
  am_nfs_fh *fhp;
  struct sockaddr_in sin;
  u_short port;
  MTYPE_TYPE type = MOUNT_TYPE_NFS;


  memset((voidp) &nfs_args, 0, sizeof(nfs_args)); /* Paranoid */

  memset((voidp) &mnt, 0, sizeof(mnt));
  mnt.mnt_dir = dir;
  mnt.mnt_fsname = pid_fsname;
  mnt.mnt_opts = opts;

  /*
   * Make sure that amd's top-level NFS mounts are hidden by default
   * from df.
   * If they don't appear to support the either the "ignore" mnttab
   * option entry, or the "auto" one, set the mount type to "nfs".
   */
  mnt.mnt_type = HIDE_MOUNT_TYPE;
  /* some systems don't have a mount type, but a mount flag */
#ifdef MNT2_NFS_OPT_AUTO
  nfs_args.flags |= MNT2_NFS_OPT_AUTO;
#endif /* MNT2_NFS_OPT_AUTO */

  retry = hasmntval(&mnt, "retry");
  if (retry <= 0)
    retry = 2;			/* XXX */

  /*
   * SET MOUNT ARGS
   */
  /*
   * get fhandle of remote path for automount point
   */
  fhp = root_fh(dir);
  if (!fhp) {
    plog(XLOG_FATAL, "Can't find root file handle for %s", dir);
    return EINVAL;
  }
  NFS_FH_DREF(nfs_args.NFS_FH_FIELD, fhp);

#ifdef HAVE_FIELD_NFS_ARGS_T_FHSIZE
  nfs_args.fhsize = FHSIZE;
#endif /* HAVE_FIELD_NFS_ARGS_T_FHSIZE */

  /*
   * Create sockaddr to point to the local machine.  127.0.0.1
   * is not used since that will not work in HP-UX clusters and
   * this is no more expensive.
   */
  memset((voidp) &sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr = myipaddr;
  if ((port = hasmntval(&mnt, MNTTAB_OPT_PORT))) {
    sin.sin_port = htons(port);
  } else {
    plog(XLOG_ERROR, "no port number specified for %s", dir);
    return EINVAL;
  }

#ifndef HAVE_TRANSPORT_TYPE_TLI
  NFS_SA_DREF(nfs_args, &sin);
#else /* HAVE_TRANSPORT_TYPE_TLI */
  nfs_args.addr = &nfsxprt->xp_ltaddr;

  /* set up syncaddr field (secure NFS time sync address) */
  nfs_args.syncaddr = (struct netbuf *) NULL;

  /* set up knconf field */
  if (get_knetconfig(&nfs_args.knconf, nfsncp, NULL) < 0) {
    plog(XLOG_ERROR, "cannot fill knetconfig structure for nfs_args");
  }
  /* update the flags field for knconf */
  nfs_args.flags |= MNT2_NFS_OPT_KNCONF;
#endif /* HAVE_TRANSPORT_TYPE_TLI */

  /*
   * Make a ``hostname'' string for the kernel
   */
  sprintf(fs_hostname, "pid%ld@%s:%s",
	  (long) (foreground ? mypid : getppid()),
	  hostname,
	  dir);

  /*
   * Most kernels have a name length restriction (64 bytes)...
   */
  if (strlen(fs_hostname) >= MAXHOSTNAMELEN)
    strcpy(fs_hostname + MAXHOSTNAMELEN - 3, "..");
#ifdef HOSTNAMESZ
  /*
   * ... and some of these restrictions are 32 bytes (HOSTNAMESZ)
   * If you need to get the definition for HOSTNAMESZ found, you may
   * add the proper header file to the conf/nfs_prot/nfs_prot_*.h file.
   */
  if (strlen(fs_hostname) >= HOSTNAMESZ)
    strcpy(fs_hostname + HOSTNAMESZ - 3, "..");
#endif /* HOSTNAMESZ */

  /* copy over the host name */
  NFS_HN_DREF(nfs_args.hostname, fs_hostname);
#ifdef MNT2_NFS_OPT_HOSTNAME
  nfs_args.flags |= MNT2_NFS_OPT_HOSTNAME;
#endif /* MNT2_NFS_OPT_HOSTNAME */

#ifdef MNT2_NFS_OPT_FSNAME
  nfs_args.fsname = pid_fsname;
  nfs_args.flags |= MNT2_NFS_OPT_FSNAME;
#endif /* MNT2_NFS_OPT_FSNAME */

#ifdef MNT2_NFS_OPT_DUMBTIMR
  /*
   * Don't let the kernel start computing throughput of Amd
   * The numbers will be meaningless because of the way Amd
   * does mount retries.
   */
  nfs_args.flags |= MNT2_NFS_OPT_DUMBTIMR;
  plog(XLOG_INFO, "%s: disabling nfs congestion window", dir);
#endif /* MNT2_NFS_OPT_DUMBTIMR */

  /*
   * Parse a subset of the standard nfs options.  The
   * others are probably irrelevant for this application
   */
#ifdef MNT2_NFS_OPT_TIMEO
  if ((nfs_args.timeo = hasmntval(&mnt, MNTTAB_OPT_TIMEO)))
    nfs_args.flags |= MNT2_NFS_OPT_TIMEO;
#endif /* MNT2_NFS_OPT_TIMEO */

#ifdef MNT2_NFS_OPT_RETRANS
  if ((nfs_args.retrans = hasmntval(&mnt, MNTTAB_OPT_RETRANS)))
    nfs_args.flags |= MNT2_NFS_OPT_RETRANS;
#endif /* MNT2_NFS_OPT_RETRANS */

#ifdef MNT2_NFS_OPT_BIODS
  if (nfs_args.biods = hasmntval(&mnt, MNTTAB_OPT_BIODS))
    nfs_args.flags |= MNT2_NFS_OPT_BIODS;
#endif /* MNT2_NFS_OPT_BIODS */

#ifdef MNT2_NFS_OPT_NOAC
  /*
   * Don't cache attributes - they are changing under
   * the kernel's feet.  For example, IRIX5.2 will dispense
   * with nfs lookup calls and hand stale filehandles to
   * getattr unless we disable attribute caching on the
   * automount points.
   */
  nfs_args.flags |= MNT2_NFS_OPT_NOAC;

#else /* not MNT2_NFS_OPT_NOAC */
  /*
   * Setting these to 0 results in an error on some systems, which is why
   * it's better to use "noac" if possible.
   */
# if defined(MNT2_NFS_OPT_ACREGMIN) && defined(MNT2_NFS_OPT_ACREGMAX)
  nfs_args.acregmin = nfs_args.acregmax = 1;
  nfs_args.flags |= MNT2_NFS_OPT_ACREGMIN | MNT2_NFS_OPT_ACREGMAX;
# endif /* defined(MNT2_NFS_OPT_ACREGMIN) && defined(MNT2_NFS_OPT_ACREGMAX) */
# if defined(MNT2_NFS_OPT_ACDIRMIN) && defined(MNT2_NFS_OPT_ACDIRMAX)
  nfs_args.acdirmin = nfs_args.acdirmax = 1;
  nfs_args.flags |= MNT2_NFS_OPT_ACDIRMIN | MNT2_NFS_OPT_ACDIRMAX;
# endif /* defined(MNT2_NFS_OPT_ACDIRMIN) && defined(MNT2_NFS_OPT_ACDIRMAX) */
#endif /* not MNT2_NFS_OPT_NOAC */

#ifdef MNT2_NFS_OPT_SYMTTL
  /*
   * Don't let the kernel cache symbolic links we generate,
   * or else lookups will bypass amd and fail to remount
   * stuff as needed.
   */
  nfs_args.flags |= MNT2_NFS_OPT_SYMTTL;
  nfs_args.symttl = 0;
#endif /* MNT2_NFS_OPT_SYMTTL */

  /*
   * These two are constructed internally by the calling routine
   */
  if (hasmntopt(&mnt, MNTTAB_OPT_SOFT) != NULL)
    nfs_args.flags |= MNT2_NFS_OPT_SOFT;

#ifdef MNT2_NFS_OPT_INT
  if (hasmntopt(&mnt, MNTTAB_OPT_INTR) != NULL)
    nfs_args.flags |= MNT2_NFS_OPT_INT;
#endif /* MNT2_NFS_OPT_INT */

#if defined(MNT2_GEN_OPT_OVERLAY) && defined(MNTTAB_OPT_OVERLAY)
  /*
   * Overlay this amd mount (presumably on another amd which died
   * before and left the machine hung).  This will allow a new amd or
   * hlfsd to be remounted on top of another one.
   */
  if (hasmntopt(&mnt, MNTTAB_OPT_OVERLAY) != NULL) {
    flags |= MNT2_GEN_OPT_OVERLAY;
    plog(XLOG_INFO, "using an overlay mount");
  }
#endif /* defined(MNT2_GEN_OVERLAY) && defined(MNTOPT_OVERLAY) */

#ifdef HAVE_STRUCT_NFS_GFS_MOUNT
  /* this code is mostly Ultrix-specific */
  nfs_args.gfs_flags = flags;
  flags &= MNT2_GEN_OPT_RDONLY;
  if (flags & MNT2_GEN_OPT_RDONLY)
    nfs_args.flags |= MNT2_NFS_OPT_RONLY;
#endif /* HAVE_STRUCT_NFS_GFS_MOUNT */

#ifdef HAVE_FIELD_NFS_ARGS_T_VERSION
# ifdef NFS_ARGSVERSION
  nfs_args.version = NFS_ARGSVERSION; /* bsdi 3.0 */
# endif /* NFS_ARGSVERSION */
# ifdef DG_MOUNT_NFS_VERSION
  nfs_args.version = DG_MOUNT_NFS_VERSION; /* dg-ux */
# endif /* DG_MOUNT_NFS_VERSION */
#endif /* HAVE_FIELD_NFS_ARGS_VERSION */

  /*
   * Finally we can compute the mount flags set above.
   */
  flags = compute_mount_flags(&mnt);

  /*
   * This is it!  Here we try to mount amd on its mount points.
   */
  error = mount_fs(&mnt, flags, (caddr_t) & nfs_args, retry, type, 0, NULL, mnttab_file_name);

#ifdef HAVE_TRANSPORT_TYPE_TLI
  free_knetconfig(nfs_args.knconf);
#endif /* HAVE_TRANSPORT_TYPE_TLI */

  return error;
}


/*
 * Build a new map cache for this node, or re-use
 * an existing cache for the same map.
 */
void
afs_mkcacheref(mntfs *mf)
{
  char *cache;

  if (mf->mf_fo && mf->mf_fo->opt_cache)
    cache = mf->mf_fo->opt_cache;
  else
    cache = "none";
  mf->mf_private = (voidp) mapc_find(mf->mf_info, cache,
				     mf->mf_fo->opt_maptype);
  mf->mf_prfree = mapc_free;
}


/*
 * Mount the root...
 */
static int
root_mount(am_node *mp)
{
  mntfs *mf = mp->am_mnt;

  mf->mf_mount = strealloc(mf->mf_mount, pid_fsname);
  mf->mf_private = (voidp) mapc_find(mf->mf_info, "", NULL);
  mf->mf_prfree = mapc_free;

  return 0;
}


/*
 * Mount a sub-mount
 */
static int
afs_mount(am_node *mp)
{
  mntfs *mf = mp->am_mnt;

  /*
   * Pseudo-directories are used to provide some structure
   * to the automounted directories instead
   * of putting them all in the top-level automount directory.
   *
   * Here, just increment the parent's link count.
   */
  mp->am_parent->am_fattr.na_nlink++;

  /*
   * Info field of . means use parent's info field.
   * Historical - not documented.
   */
  if (mf->mf_info[0] == '.' && mf->mf_info[1] == '\0')
    mf->mf_info = strealloc(mf->mf_info, mp->am_parent->am_mnt->mf_info);

  /*
   * Compute prefix:
   *
   * If there is an option prefix then use that else
   * If the parent had a prefix then use that with name
   *      of this node appended else
   * Use the name of this node.
   *
   * That means if you want no prefix you must say so
   * in the map.
   */
  if (mf->mf_fo->opt_pref) {
    /* allow pref:=null to set a real null prefix */
    if (STREQ(mf->mf_fo->opt_pref, "null")) {
      mp->am_pref = "";
    } else {
      /*
       * the prefix specified as an option
       */
      mp->am_pref = strdup(mf->mf_fo->opt_pref);
    }
  } else {
    /*
     * else the parent's prefix
     * followed by the name
     * followed by /
     */
    char *ppref = mp->am_parent->am_pref;
    if (ppref == 0)
      ppref = "";
    mp->am_pref = str3cat((char *) 0, ppref, mp->am_name, "/");
  }

  /*
   * Attach a map cache
   */
  afs_mkcacheref(mf);

  return 0;
}


/*
 * Mount the top-level
 */
static int
toplvl_mount(am_node *mp)
{
  mntfs *mf = mp->am_mnt;
  struct stat stb;
  char opts[256], preopts[256];
  int error;
  char *mnttype;

  /*
   * Mounting the automounter.
   * Make sure the mount directory exists, construct
   * the mount options and call the mount_toplvl routine.
   */

  if (stat(mp->am_path, &stb) < 0) {
    return errno;
  } else if ((stb.st_mode & S_IFMT) != S_IFDIR) {
    plog(XLOG_WARNING, "%s is not a directory", mp->am_path);
    return ENOTDIR;
  }
  if (mf->mf_ops == &toplvl_ops)
    mnttype = "indirect";
  else if (mf->mf_ops == &dfs_ops)
    mnttype = "direct";
#ifdef HAVE_AM_FS_UNION
  else if (mf->mf_ops == &union_ops)
    mnttype = "union";
#endif /* HAVE_AM_FS_UNION */
  else
    mnttype = "auto";

  /*
   * Construct some mount options:
   *
   * Tack on magic map=<mapname> option in mtab to emulate
   * SunOS automounter behavior.
   */
  preopts[0] = '\0';
#ifdef MNTTAB_OPT_INTR
  strcat(preopts, MNTTAB_OPT_INTR);
  strcat(preopts, ",");
#endif /* MNTTAB_OPT_INTR */
#ifdef MNTTAB_OPT_IGNORE
  strcat(preopts, MNTTAB_OPT_IGNORE);
  strcat(preopts, ",");
#endif /* MNTTAB_OPT_IGNORE */
  sprintf(opts, "%s%s,%s=%d,%s=%d,%s=%d,%s,map=%s",
	  preopts,
	  MNTTAB_OPT_RW,
	  MNTTAB_OPT_PORT, nfs_port,
	  MNTTAB_OPT_TIMEO, gopt.afs_timeo,
	  MNTTAB_OPT_RETRANS, gopt.afs_retrans,
	  mnttype, mf->mf_info);

  /* now do the mount */
  error = mount_toplvl(mf->mf_mount, opts);
  if (error) {
    errno = error;
    plog(XLOG_FATAL, "mount_toplvl: %m");
    return error;
  }
  return 0;
}


static void
toplvl_mounted(mntfs *mf)
{
  afs_mkcacheref(mf);
}


/*
 * Unmount an automount sub-node
 */
static int
afs_umount(am_node *mp)
{
  return 0;
}


/*
 * Unmount a top-level automount node
 */
static int
toplvl_umount(am_node *mp)
{
  int error;
  struct stat stb;

again:
  /*
   * The lstat is needed if this mount is type=direct.
   * When that happens, the kernel cache gets confused
   * between the underlying type (dir) and the mounted
   * type (link) and so needs to be re-synced before
   * the unmount.  This is all because the unmount system
   * call follows links and so can't actually unmount
   * a link (stupid!).  It was noted that doing an ls -ld
   * of the mount point to see why things were not working
   * actually fixed the problem - so simulate an ls -ld here.
   */
  if (lstat(mp->am_path, &stb) < 0) {
#ifdef DEBUG
    dlog("lstat(%s): %m", mp->am_path);
#endif /* DEBUG */
  }
  error = UMOUNT_FS(mp->am_path, mnttab_file_name);
  if (error == EBUSY) {
    plog(XLOG_WARNING, "afs_unmount retrying %s in 1s", mp->am_path);
    sleep(1);			/* XXX */
    goto again;
  }
  return error;
}


/*
 * Unmount an automount node
 */
static void
afs_umounted(am_node *mp)
{
  /*
   * If this is a pseudo-directory then just adjust the link count
   * in the parent, otherwise call the generic unmount routine
   */
  if (mp->am_parent && mp->am_parent->am_parent)
    --mp->am_parent->am_fattr.na_nlink;
}


/*
 * Discard an old continuation
 */
static void
free_continuation(struct continuation *cp)
{
  if (cp->callout)
    untimeout(cp->callout);
  free((voidp) cp->key);
  free((voidp) cp->xivec);
  free((voidp) cp->info);
  free((voidp) cp->auto_opts);
  free((voidp) cp->def_opts);
  free_opts(&cp->fs_opts);
  free((voidp) cp);
}


/*
 * Discard the underlying mount point and replace
 * with a reference to an error filesystem.
 */
static void
assign_error_mntfs(am_node *mp)
{
  if (mp->am_error > 0) {
    /*
     * Save the old error code
     */
    int error = mp->am_error;
    if (error <= 0)
      error = mp->am_mnt->mf_error;
    /*
     * Discard the old filesystem
     */
    free_mntfs(mp->am_mnt);
    /*
     * Allocate a new error reference
     */
    mp->am_mnt = new_mntfs();
    /*
     * Put back the error code
     */
    mp->am_mnt->mf_error = error;
    mp->am_mnt->mf_flags |= MFF_ERROR;
    /*
     * Zero the error in the mount point
     */
    mp->am_error = 0;
  }
}


/*
 * The continuation function.  This is called by
 * the task notifier when a background mount attempt
 * completes.
 */
static void
afs_cont(int rc, int term, voidp closure)
{
  struct continuation *cp = (struct continuation *) closure;
  mntfs *mf = cp->mp->am_mnt;

  /*
   * Definitely not trying to mount at the moment
   */
  mf->mf_flags &= ~MFF_MOUNTING;

  /*
   * While we are mounting - try to avoid race conditions
   */
  new_ttl(cp->mp);

  /*
   * Wakeup anything waiting for this mount
   */
  wakeup((voidp) mf);

  /*
   * Check for termination signal or exit status...
   */
  if (rc || term) {
    am_node *xmp;

    if (term) {
      /*
       * Not sure what to do for an error code.
       */
      mf->mf_error = EIO;	/* XXX ? */
      mf->mf_flags |= MFF_ERROR;
      plog(XLOG_ERROR, "mount for %s got signal %d", cp->mp->am_path, term);
    } else {
      /*
       * Check for exit status...
       */
      mf->mf_error = rc;
      mf->mf_flags |= MFF_ERROR;
      errno = rc;		/* XXX */
      if (!STREQ(cp->mp->am_mnt->mf_ops->fs_type, "linkx"))
	plog(XLOG_ERROR, "%s: mount (afs_cont): %m", cp->mp->am_path);
    }

    /*
     * If we get here then that attempt didn't work, so
     * move the info vector pointer along by one and
     * call the background mount routine again
     */
    amd_stats.d_merr++;
    cp->ivec++;
    xmp = cp->mp;
    (void) afs_bgmount(cp, 0);
    assign_error_mntfs(xmp);
  } else {
    /*
     * The mount worked.
     */
    am_mounted(cp->mp);
    free_continuation(cp);
  }

  reschedule_timeout_mp();
}


/*
 * Retry a mount
 */
static void
afs_retry(int rc, int term, voidp closure)
{
  struct continuation *cp = (struct continuation *) closure;
  int error = 0;

#ifdef DEBUG
  dlog("Commencing retry for mount of %s", cp->mp->am_path);
#endif /* DEBUG */

  new_ttl(cp->mp);

  if ((cp->start + ALLOWED_MOUNT_TIME) < clocktime()) {
    /*
     * The entire mount has timed out.  Set the error code and skip past all
     * the info vectors so that afs_bgmount will not have any more ways to
     * try the mount, so causing an error.
     */
    plog(XLOG_INFO, "mount of \"%s\" has timed out", cp->mp->am_path);
    error = ETIMEDOUT;
    while (*cp->ivec)
      cp->ivec++;
    /* explicitly forbid further retries after timeout */
    cp->retry = FALSE;
  }
  if (error || !IN_PROGRESS(cp)) {
    (void) afs_bgmount(cp, error);
  }
  reschedule_timeout_mp();
}


/*
 * Try to mount a file system.  Can be called
 * directly or in a sub-process by run_task.
 */
static int
try_mount(voidp mvp)
{
  int error = 0;
  am_node *mp = (am_node *) mvp;
  mntfs *mf = mp->am_mnt;

  /*
   * If the directory is not yet made and it needs to be made, then make it!
   * This may be run in a background process in which case the flag setting
   * won't be noticed later - but it is set anyway just after run_task is
   * called.  It should probably go away totally...
   */
  if (!(mf->mf_flags & MFF_MKMNT) && mf->mf_ops->fs_flags & FS_MKMNT) {
    error = mkdirs(mf->mf_mount, 0555);
    if (!error)
      mf->mf_flags |= MFF_MKMNT;
  }

  /*
   * Mount it!
   */
  error = mount_node(mp);

#ifdef DEBUG
  if (error > 0) {
    errno = error;
    dlog("afs call to mount_node failed: %m");
  }
#endif /* DEBUG */

  return error;
}


/*
 * Pick a file system to try mounting and
 * do that in the background if necessary
 *
 For each location:
 if it is new -defaults then
 extract and process
 continue;
 fi
 if it is a cut then
 if a location has been tried then
 break;
 fi
 continue;
 fi
 parse mount location
 discard previous mount location if required
 find matching mounted filesystem
 if not applicable then
 this_error = No such file or directory
 continue
 fi
 if the filesystem failed to be mounted then
 this_error = error from filesystem
 elif the filesystem is mounting or unmounting then
 this_error = -1
 elif the fileserver is down then
 this_error = -1
 elif the filesystem is already mounted
 this_error = 0
 break
 fi
 if no error on this mount then
 this_error = initialise mount point
 fi
 if no error on this mount and mount is delayed then
 this_error = -1
 fi
 if this_error < 0 then
 retry = true
 fi
 if no error on this mount then
 make mount point if required
 fi
 if no error on this mount then
 if mount in background then
 run mount in background
 return -1
 else
 this_error = mount in foreground
 fi
 fi
 if an error occured on this mount then
 update stats
 save error in mount point
 fi
 endfor
 */
static int
afs_bgmount(struct continuation * cp, int mpe)
{
  mntfs *mf = cp->mp->am_mnt;	/* Current mntfs */
  mntfs *mf_retry = 0;		/* First mntfs which needed retrying */
  int this_error = -1;		/* Per-mount error */
  int hard_error = -1;
  int mp_error = mpe;

  /*
   * Try to mount each location.
   * At the end:
   * hard_error == 0 indicates something was mounted.
   * hard_error > 0 indicates everything failed with a hard error
   * hard_error < 0 indicates nothing could be mounted now
   */
  for (; this_error && *cp->ivec; cp->ivec++) {
    am_ops *p;
    am_node *mp = cp->mp;
    char *link_dir;
    int dont_retry;

    if (hard_error < 0)
      hard_error = this_error;

    this_error = -1;

    if (**cp->ivec == '-') {
      /*
       * Pick up new defaults
       */
      if (cp->auto_opts && *cp->auto_opts)
	cp->def_opts = str3cat(cp->def_opts, cp->auto_opts, ";", *cp->ivec + 1);
      else
	cp->def_opts = strealloc(cp->def_opts, *cp->ivec + 1);
#ifdef DEBUG
      dlog("Setting def_opts to \"%s\"", cp->def_opts);
#endif /* DEBUG */
      continue;
    }
    /*
     * If a mount has been attempted, and we find
     * a cut then don't try any more locations.
     */
    if (STREQ(*cp->ivec, "/") || STREQ(*cp->ivec, "||")) {
      if (cp->tried) {
#ifdef DEBUG
	dlog("Cut: not trying any more locations for %s",
	     mp->am_path);
#endif /* DEBUG */
	break;
      }
      continue;
    }

    /* match the operators */
    p = ops_match(&cp->fs_opts, *cp->ivec, cp->def_opts, mp->am_path, cp->key, mp->am_parent->am_mnt->mf_info);

    /*
     * Find a mounted filesystem for this node.
     */
    mp->am_mnt = mf = realloc_mntfs(mf, p, &cp->fs_opts,
				    cp->fs_opts.opt_fs,
				    cp->fs_opts.fs_mtab,
				    cp->auto_opts,
				    cp->fs_opts.opt_opts,
				    cp->fs_opts.opt_remopts);

    p = mf->mf_ops;
#ifdef DEBUG
    dlog("Got a hit with %s", p->fs_type);
#endif /* DEBUG */

    /*
     * Note whether this is a real mount attempt
     */
    if (p == &efs_ops) {
      plog(XLOG_MAP, "Map entry %s for %s failed to match", *cp->ivec, mp->am_path);
      if (this_error <= 0)
	this_error = ENOENT;
      continue;
    } else {
      if (cp->fs_opts.fs_mtab) {
	plog(XLOG_MAP, "Trying mount of %s on %s fstype %s",
	     cp->fs_opts.fs_mtab, mp->am_path, p->fs_type);
      }
      cp->tried = TRUE;
    }

    this_error = 0;
    dont_retry = FALSE;

    if (mp->am_link) {
      free(mp->am_link);
      mp->am_link = 0;
    }
    link_dir = mf->mf_fo->opt_sublink;

    if (link_dir && *link_dir) {
      if (*link_dir == '/') {
	mp->am_link = strdup(link_dir);
      } else {
	/*
	 * try getting fs option from continuation, not mountpoint!
	 * Don't try logging the string from mf, since it may be bad!
	 */
	if (cp->fs_opts.opt_fs != mf->mf_fo->opt_fs)
	  plog(XLOG_ERROR, "use %s instead of 0x%x",
	       cp->fs_opts.opt_fs, mf->mf_fo->opt_fs);

	mp->am_link = str3cat((char *) 0,
			      cp->fs_opts.opt_fs, "/", link_dir);

	normalize_slash(mp->am_link);
      }
    }

    if (mf->mf_error > 0) {
      this_error = mf->mf_error;
    } else if (mf->mf_flags & (MFF_MOUNTING | MFF_UNMOUNTING)) {
      /*
       * Still mounting - retry later
       */
#ifdef DEBUG
      dlog("Duplicate pending mount fstype %s", p->fs_type);
#endif /* DEBUG */
      this_error = -1;
    } else if (FSRV_ISDOWN(mf->mf_server)) {
      /*
       * Would just mount from the same place
       * as a hung mount - so give up
       */
#ifdef DEBUG
      dlog("%s is already hung - giving up", mf->mf_mount);
#endif /* DEBUG */
      mp_error = EWOULDBLOCK;
      dont_retry = TRUE;
      this_error = -1;
    } else if (mf->mf_flags & MFF_MOUNTED) {
#ifdef DEBUG
      dlog("duplicate mount of \"%s\" ...", mf->mf_info);
#endif /* DEBUG */

      /*
       * Just call mounted()
       */
      am_mounted(mp);

      this_error = 0;
      break;
    }

    /*
     * Will usually need to play around with the mount nodes
     * file attribute structure.  This must be done here.
     * Try and get things initialised, even if the fileserver
     * is not known to be up.  In the common case this will
     * progress things faster.
     */
    if (!this_error) {
      /*
       * Fill in attribute fields.
       */
      if (mf->mf_ops->fs_flags & FS_DIRECTORY)
	mk_fattr(mp, NFDIR);
      else
	mk_fattr(mp, NFLNK);

      mp->am_fattr.na_fileid = mp->am_gen;

      if (p->fs_init)
	this_error = (*p->fs_init) (mf);
    }

    /*
     * Make sure the fileserver is UP before doing any more work
     */
    if (!FSRV_ISUP(mf->mf_server)) {
#ifdef DEBUG
      dlog("waiting for server %s to become available", mf->mf_server->fs_host);
#endif /* DEBUG */
      this_error = -1;
    }

    if (!this_error && mf->mf_fo->opt_delay) {
      /*
       * If there is a delay timer on the mount
       * then don't try to mount if the timer
       * has not expired.
       */
      int i = atoi(mf->mf_fo->opt_delay);
      if (i > 0 && clocktime() < (cp->start + i)) {
#ifdef DEBUG
	dlog("Mount of %s delayed by %ds", mf->mf_mount, i - clocktime() + cp->start);
#endif /* DEBUG */
	this_error = -1;
      }
    }

    if (this_error < 0 && !dont_retry) {
      if (!mf_retry)
	mf_retry = dup_mntfs(mf);
      cp->retry = TRUE;
    }

    if (!this_error)
      if (p->fs_flags & FS_MBACKGROUND) {
	mf->mf_flags |= MFF_MOUNTING;	/* XXX */
#ifdef DEBUG
	dlog("backgrounding mount of \"%s\"", mf->mf_mount);
#endif /* DEBUG */
	if (cp->callout) {
	  untimeout(cp->callout);
	  cp->callout = 0;
	}
	run_task(try_mount, (voidp) mp, afs_cont, (voidp) cp);
	mf->mf_flags |= MFF_MKMNT;	/* XXX */
	if (mf_retry)
	  free_mntfs(mf_retry);
	return -1;
      } else {
#ifdef DEBUG
	dlog("foreground mount of \"%s\" ...", mf->mf_info);
#endif /* DEBUG */
	this_error = try_mount((voidp) mp);
	if (this_error < 0) {
	  if (!mf_retry)
	    mf_retry = dup_mntfs(mf);
	  cp->retry = TRUE;
	}
      }

    if (this_error >= 0) {
      if (this_error > 0) {
	amd_stats.d_merr++;
	if (mf != mf_retry) {
	  mf->mf_error = this_error;
	  mf->mf_flags |= MFF_ERROR;
	}
      }

      /*
       * Wakeup anything waiting for this mount
       */
      wakeup((voidp) mf);
    }
  }

  if (this_error && cp->retry) {
    free_mntfs(mf);
    mf = cp->mp->am_mnt = mf_retry;
    /*
     * Not retrying again (so far)
     */
    cp->retry = FALSE;
    cp->tried = FALSE;
    /*
     * Start at the beginning.
     * Rewind the location vector and
     * reset the default options.
     */
    cp->ivec = cp->xivec;
    cp->def_opts = strealloc(cp->def_opts, cp->auto_opts);
    /*
     * Arrange that afs_bgmount is called
     * after anything else happens.
     */
#ifdef DEBUG
    dlog("Arranging to retry mount of %s", cp->mp->am_path);
#endif /* DEBUG */
    sched_task(afs_retry, (voidp) cp, (voidp) mf);
    if (cp->callout)
      untimeout(cp->callout);
    cp->callout = timeout(RETRY_INTERVAL, wakeup, (voidp) mf);

    cp->mp->am_ttl = clocktime() + RETRY_INTERVAL;

    /*
     * Not done yet - so don't return anything
     */
    return -1;
  }

  if (hard_error < 0 || this_error == 0)
    hard_error = this_error;

  /*
   * Discard handle on duff filesystem.
   * This should never happen since it
   * should be caught by the case above.
   */
  if (mf_retry) {
    if (hard_error)
      plog(XLOG_ERROR, "discarding a retry mntfs for %s", mf_retry->mf_mount);
    free_mntfs(mf_retry);
  }

  /*
   * If we get here, then either the mount succeeded or
   * there is no more mount information available.
   */
  if (hard_error < 0 && mp_error)
    hard_error = cp->mp->am_error = mp_error;
  if (hard_error > 0) {
    /*
     * Set a small(ish) timeout on an error node if
     * the error was not a time out.
     */
    switch (hard_error) {
    case ETIMEDOUT:
    case EWOULDBLOCK:
      cp->mp->am_timeo = 17;
      break;
    default:
      cp->mp->am_timeo = 5;
      break;
    }
    new_ttl(cp->mp);
  }

  /*
   * Make sure that the error value in the mntfs has a
   * reasonable value.
   */
  if (mf->mf_error < 0) {
    mf->mf_error = hard_error;
    if (hard_error)
      mf->mf_flags |= MFF_ERROR;
  }

  /*
   * In any case we don't need the continuation any more
   */
  free_continuation(cp);

  return hard_error;
}


/*
 * Automount interface to RPC lookup routine
 * Find the corresponding entry and return
 * the file handle for it.
 */
static am_node *
afs_lookuppn(am_node *mp, char *fname, int *error_return, int op)
{
  am_node *ap, *new_mp, *ap_hung;
  char *info;			/* Mount info - where to get the file system */
  char **ivec, **xivec;		/* Split version of info */
  char *auto_opts;		/* Automount options */
  int error = 0;		/* Error so far */
  char path_name[MAXPATHLEN];	/* General path name buffer */
  char *pfname;			/* Path for database lookup */
  struct continuation *cp;	/* Continuation structure if need to mount */
  int in_progress = 0;		/* # of (un)mount in progress */
  char *dflts;
  mntfs *mf;

#ifdef DEBUG
  dlog("in afs_lookuppn");
#endif /* DEBUG */

  /*
   * If the server is shutting down
   * then don't return information
   * about the mount point.
   */
  if (amd_state == Finishing) {
#ifdef DEBUG
    if ((mf = mp->am_mnt) == 0 || mf->mf_ops == &dfs_ops)
      dlog("%s mount ignored - going down", fname);
    else
      dlog("%s/%s mount ignored - going down", mp->am_path, fname);
#endif /* DEBUG */
    ereturn(ENOENT);
  }

  /*
   * Handle special case of "." and ".."
   */
  if (fname[0] == '.') {
    if (fname[1] == '\0')
      return mp;		/* "." is the current node */
    if (fname[1] == '.' && fname[2] == '\0') {
      if (mp->am_parent) {
#ifdef DEBUG
	dlog(".. in %s gives %s", mp->am_path, mp->am_parent->am_path);
#endif /* DEBUG */
	return mp->am_parent;	/* ".." is the parent node */
      }
      ereturn(ESTALE);
    }
  }

  /*
   * Check for valid key name.
   * If it is invalid then pretend it doesn't exist.
   */
  if (!valid_key(fname)) {
    plog(XLOG_WARNING, "Key \"%s\" contains a disallowed character", fname);
    ereturn(ENOENT);
  }

  /*
   * Expand key name.
   * fname is now a private copy.
   */
  fname = expand_key(fname);

  for (ap_hung = 0, ap = mp->am_child; ap; ap = ap->am_osib) {
    /*
     * Otherwise search children of this node
     */
    if (FSTREQ(ap->am_name, fname)) {
      mf = ap->am_mnt;
      if (ap->am_error) {
	error = ap->am_error;
	continue;
      }
      /*
       * If the error code is undefined then it must be
       * in progress.
       */
      if (mf->mf_error < 0)
	goto in_progrss;

      /*
       * Check for a hung node
       */
      if (FSRV_ISDOWN(mf->mf_server)) {
#ifdef DEBUG
	dlog("server hung");
#endif /* DEBUG */
	error = ap->am_error;
	ap_hung = ap;
	continue;
      }
      /*
       * If there was a previous error with this node
       * then return that error code.
       */
      if (mf->mf_flags & MFF_ERROR) {
	error = mf->mf_error;
	continue;
      }
      if (!(mf->mf_flags & MFF_MOUNTED) || (mf->mf_flags & MFF_UNMOUNTING)) {
      in_progrss:
	/*
	 * If the fs is not mounted or it is unmounting then there
	 * is a background (un)mount in progress.  In this case
	 * we just drop the RPC request (return nil) and
	 * wait for a retry, by which time the (un)mount may
	 * have completed.
	 */
#ifdef DEBUG
	dlog("ignoring mount of %s in %s -- flags (%x) in progress",
	     fname, mf->mf_mount, mf->mf_flags);
#endif /* DEBUG */
	in_progress++;
	continue;
      }

      /*
       * Otherwise we have a hit: return the current mount point.
       */
#ifdef DEBUG
      dlog("matched %s in %s", fname, ap->am_path);
#endif /* DEBUG */
      free(fname);
      return ap;
    }
  }

  if (in_progress) {
#ifdef DEBUG
    dlog("Waiting while %d mount(s) in progress", in_progress);
#endif /* DEBUG */
    free(fname);
    ereturn(-1);
  }

  /*
   * If an error occured then return it.
   */
  if (error) {
#ifdef DEBUG
    errno = error;		/* XXX */
    dlog("Returning error: %m", error);
#endif /* DEBUG */
    free(fname);
    ereturn(error);
  }

  /*
   * If doing a delete then don't create again!
   */
  switch (op) {
  case VLOOK_DELETE:
    ereturn(ENOENT);

  case VLOOK_CREATE:
    break;

  default:
    plog(XLOG_FATAL, "Unknown op to afs_lookuppn: 0x%x", op);
    ereturn(EINVAL);
  }

  /*
   * If the server is going down then just return,
   * don't try to mount any more file systems
   */
  if ((int) amd_state >= (int) Finishing) {
#ifdef DEBUG
    dlog("not found - server going down anyway");
#endif /* DEBUG */
    free(fname);
    ereturn(ENOENT);
  }

  /*
   * If we get there then this is a reference to an,
   * as yet, unknown name so we need to search the mount
   * map for it.
   */
  if (mp->am_pref) {
    sprintf(path_name, "%s%s", mp->am_pref, fname);
    pfname = path_name;
  } else {
    pfname = fname;
  }

  mf = mp->am_mnt;

#ifdef DEBUG
  dlog("will search map info in %s to find %s", mf->mf_info, pfname);
#endif /* DEBUG */
  /*
   * Consult the oracle for some mount information.
   * info is malloc'ed and belongs to this routine.
   * It ends up being free'd in free_continuation().
   *
   * Note that this may return -1 indicating that information
   * is not yet available.
   */
  error = mapc_search((mnt_map *) mf->mf_private, pfname, &info);
  if (error) {
    if (error > 0)
      plog(XLOG_MAP, "No map entry for %s", pfname);
    else
      plog(XLOG_MAP, "Waiting on map entry for %s", pfname);
    free(fname);
    ereturn(error);
  }
#ifdef DEBUG
  dlog("mount info is %s", info);
#endif /* DEBUG */

  /*
   * Split info into an argument vector.
   * The vector is malloc'ed and belongs to
   * this routine.  It is free'd in free_continuation()
   */
  xivec = ivec = strsplit(info, ' ', '\"');

  /*
   * Default error code...
   */
  if (ap_hung)
    error = EWOULDBLOCK;
  else
    error = ENOENT;

  /*
   * Allocate a new map
   */
  new_mp = exported_ap_alloc();
  if (new_mp == 0) {
    free((voidp) xivec);
    free((voidp) info);
    free((voidp) fname);
    ereturn(ENOSPC);
  }
  if (mf->mf_auto)
    auto_opts = mf->mf_auto;
  else
    auto_opts = "";

  auto_opts = strdup(auto_opts);

#ifdef DEBUG
  dlog("searching for /defaults entry");
#endif /* DEBUG */
  if (mapc_search((mnt_map *) mf->mf_private, "/defaults", &dflts) == 0) {
    char *dfl;
    char **rvec;
#ifdef DEBUG
    dlog("/defaults gave %s", dflts);
#endif /* DEBUG */
    if (*dflts == '-')
      dfl = dflts + 1;
    else
      dfl = dflts;

    /*
     * Chop the defaults up
     */
    rvec = strsplit(dfl, ' ', '\"');

    if (gopt.flags & CFM_ENABLE_DEFAULT_SELECTORS) {
      /*
       * Pick whichever first entry matched the list of selectors.
       * Strip the selectors from the string, and assign to dfl the
       * rest of the string.
       */
      if (rvec) {
	am_opts ap;
	am_ops *pt;
	char **sp = rvec;
	while (*sp) {		/* loop until you find something, if any */
	  memset((char *) &ap, 0, sizeof(am_opts));
	  pt = ops_match(&ap, *sp, "", mp->am_path, "/defaults",
			 mp->am_parent->am_mnt->mf_info);
	  if (pt == &efs_ops) {
	    plog(XLOG_MAP, "failed to match defaults for \"%s\"", *sp);
	  } else {
	    dfl = strip_selectors(*sp, "/defaults");
	    plog(XLOG_MAP, "matched default selectors \"%s\"", dfl);
	    break;
	  }
	  ++sp;
	}
      }
    } else {			/* not enable_default_selectors */
      /*
       * Extract first value
       */
      dfl = rvec[0];
    }

    /*
     * If there were any values at all...
     */
    if (dfl) {
      /*
       * Log error if there were other values
       */
      if (!(gopt.flags & CFM_ENABLE_DEFAULT_SELECTORS) && rvec[1]) {
# ifdef DEBUG
	dlog("/defaults chopped into %s", dfl);
# endif /* DEBUG */
	plog(XLOG_USER, "More than a single value for /defaults in %s", mf->mf_info);
      }

      /*
       * Prepend to existing defaults if they exist,
       * otherwise just use these defaults.
       */
      if (*auto_opts && *dfl) {
	char *nopts = (char *) xmalloc(strlen(auto_opts) + strlen(dfl) + 2);
	sprintf(nopts, "%s;%s", dfl, auto_opts);
	free(auto_opts);
	auto_opts = nopts;
      } else if (*dfl) {
	auto_opts = strealloc(auto_opts, dfl);
      }
    }
    free(dflts);
    /*
     * Don't need info vector any more
     */
    free((voidp) rvec);
  }

  /*
   * Fill it in
   */
  init_map(new_mp, fname);

  /*
   * Put it in the table
   */
  insert_am(new_mp, mp);

  /*
   * Fill in some other fields,
   * path and mount point.
   *
   * bugfix: do not prepend old am_path if direct map
   *         <wls@astro.umd.edu> William Sebok
   */
  new_mp->am_path = str3cat(new_mp->am_path,
			    mf->mf_ops == &dfs_ops ? "" : mp->am_path,
			    *fname == '/' ? "" : "/", fname);

#ifdef DEBUG
  dlog("setting path to %s", new_mp->am_path);
#endif /* DEBUG */

  /*
   * Take private copy of pfname
   */
  pfname = strdup(pfname);

  /*
   * Construct a continuation
   */
  cp = ALLOC(struct continuation);
  cp->callout = 0;
  cp->mp = new_mp;
  cp->xivec = xivec;
  cp->ivec = ivec;
  cp->info = info;
  cp->key = pfname;
  cp->auto_opts = auto_opts;
  cp->retry = FALSE;
  cp->tried = FALSE;
  cp->start = clocktime();
  cp->def_opts = strdup(auto_opts);
  memset((voidp) &cp->fs_opts, 0, sizeof(cp->fs_opts));

  /*
   * Try and mount the file system.  If this succeeds immediately (possible
   * for a ufs file system) then return the attributes, otherwise just
   * return an error.
   */
  error = afs_bgmount(cp, error);
  reschedule_timeout_mp();
  if (!error) {
    free(fname);
    return new_mp;
  }

  /*
   * Code for quick reply.  If nfs_program_2_transp is set, then
   * its the transp that's been passed down from nfs_program_2().
   * If new_mp->am_transp is not already set, set it by copying in
   * nfs_program_2_transp.  Once am_transp is set, quick_reply() can
   * use it to send a reply to the client that requested this mount.
   */
  if (nfs_program_2_transp && !new_mp->am_transp) {
    new_mp->am_transp = (SVCXPRT *) xmalloc(sizeof(SVCXPRT));
    *(new_mp->am_transp) = *nfs_program_2_transp;
  }
  if (error && (new_mp->am_mnt->mf_ops == &efs_ops))
    new_mp->am_error = error;

  assign_error_mntfs(new_mp);

  free(fname);

  ereturn(error);
}


/*
 * Locate next node in sibling list which is mounted
 * and is not an error node.
 */
static am_node *
next_nonerror_node(am_node *xp)
{
  mntfs *mf;

  /*
   * Bug report (7/12/89) from Rein Tollevik <rein@ifi.uio.no>
   * Fixes a race condition when mounting direct automounts.
   * Also fixes a problem when doing a readdir on a directory
   * containing hung automounts.
   */
  while (xp &&
	 (!(mf = xp->am_mnt) ||	/* No mounted filesystem */
	  mf->mf_error != 0 ||	/* There was a mntfs error */
	  xp->am_error != 0 ||	/* There was a mount error */
	  !(mf->mf_flags & MFF_MOUNTED) ||	/* The fs is not mounted */
	  (mf->mf_server->fs_flags & FSF_DOWN))	/* The fs may be down */
	 )
    xp = xp->am_osib;

  return xp;
}


/*
 * This readdir function which call a special version of it that allows
 * browsing if browsable_dirs=yes was set on the map.
 */
static int
afs_readdir(am_node *mp, nfscookie cookie, nfsdirlist *dp, nfsentry *ep, int count)
{
  u_int gen = *(u_int *) cookie;
  am_node *xp;
  mntent_t mnt;

  dp->dl_eof = FALSE;		/* assume readdir not done */

  /* check if map is browsable */
  if (mp->am_mnt && mp->am_mnt->mf_mopts) {
    mnt.mnt_opts = mp->am_mnt->mf_mopts;
    if (hasmntopt(&mnt, "browsable"))
      return afs_readdir_browsable(mp, cookie, dp, ep, count);
  }

  if (gen == 0) {
    /*
     * In the default instance (which is used to start a search) we return
     * "." and "..".
     *
     * This assumes that the count is big enough to allow both "." and ".."
     * to be returned in a single packet.  If it isn't (which would be
     * fairly unbelievable) then tough.
     */
#ifdef DEBUG
    dlog("default search");
#endif /* DEBUG */
    /*
     * Check for enough room.  This is extremely approximate but is more
     * than enough space.  Really need 2 times:
     *      4byte fileid
     *      4byte cookie
     *      4byte name length
     *      4byte name
     * plus the dirlist structure */
    if (count < (2 * (2 * (sizeof(*ep) + sizeof("..") + 4) + sizeof(*dp))))
      return EINVAL;

    xp = next_nonerror_node(mp->am_child);
    dp->dl_entries = ep;

    /* construct "." */
    ep[0].ne_fileid = mp->am_gen;
    ep[0].ne_name = ".";
    ep[0].ne_nextentry = &ep[1];
    *(u_int *) ep[0].ne_cookie = 0;

    /* construct ".." */
    if (mp->am_parent)
      ep[1].ne_fileid = mp->am_parent->am_gen;
    else
      ep[1].ne_fileid = mp->am_gen;
    ep[1].ne_name = "..";
    ep[1].ne_nextentry = 0;
    *(u_int *) ep[1].ne_cookie =
      xp ? xp->am_gen : ~(u_int) 0;

    if (!xp)
      dp->dl_eof = TRUE;	/* by default assume readdir done */

    return 0;
  }
#ifdef DEBUG
  dlog("real child");
#endif /* DEBUG */

  if (gen == ~(u_int) 0) {
#ifdef DEBUG
    dlog("End of readdir in %s", mp->am_path);
#endif /* DEBUG */
    dp->dl_eof = TRUE;
    dp->dl_entries = 0;
    return 0;
  }

  /* non-browsable directories code */
  xp = mp->am_child;
  while (xp && xp->am_gen != gen)
    xp = xp->am_osib;

  if (xp) {
    int nbytes = count / 2;	/* conservative */
    int todo = MAX_READDIR_ENTRIES;
    dp->dl_entries = ep;
    do {
      am_node *xp_next = next_nonerror_node(xp->am_osib);

      if (xp_next) {
	*(u_int *) ep->ne_cookie = xp_next->am_gen;
      } else {
	*(u_int *) ep->ne_cookie = ~(u_int) 0;
	dp->dl_eof = TRUE;
      }

      ep->ne_fileid = xp->am_gen;
      ep->ne_name = xp->am_name;
      nbytes -= sizeof(*ep) + 1;
      if (xp->am_name)
	nbytes -= strlen(xp->am_name);

      xp = xp_next;

      if (nbytes > 0 && !dp->dl_eof && todo > 1) {
	ep->ne_nextentry = ep + 1;
	ep++;
	--todo;
      } else {
	todo = 0;
      }
    } while (todo > 0);

    ep->ne_nextentry = 0;

    return 0;
  }
  return ESTALE;
}


/* This one is called only if map is browsable */
static int
afs_readdir_browsable(am_node *mp, nfscookie cookie, nfsdirlist *dp, nfsentry *ep, int count)
{
  u_int gen = *(u_int *) cookie;
  int chain_length, i;
  static nfsentry *te, *te_next;
#ifdef DEBUG_READDIR
  nfsentry *ne;
#endif /* DEBUG_READDIR */

  dp->dl_eof = FALSE;		/* assume readdir not done */

#ifdef DEBUG_READDIR
  plog(XLOG_INFO, "afs_readdir_browsable gen=%u", gen);
#endif /* DEBUG_READDIR */

  if (gen == 0) {
    /*
     * In the default instance (which is used to start a search) we return
     * "." and "..".
     *
     * This assumes that the count is big enough to allow both "." and ".."
     * to be returned in a single packet.  If it isn't (which would be
     * fairly unbelievable) then tough.
     */
#ifdef DEBUG
    dlog("default search");
#endif /* DEBUG */
    /*
     * Check for enough room.  This is extremely approximate but is more
     * than enough space.  Really need 2 times:
     *      4byte fileid
     *      4byte cookie
     *      4byte name length
     *      4byte name
     * plus the dirlist structure */
    if (count < (2 * (2 * (sizeof(*ep) + sizeof("..") + 4) + sizeof(*dp))))
      return EINVAL;

    /*
     * compute # of entries to send in this chain.
     * heuristics: 30 bytes per entry.
     */
    chain_length = count / 30;
    /* reset static state counters */
    te = te_next = NULL;

    dp->dl_entries = ep;

    /* construct "." */
    ep[0].ne_fileid = mp->am_gen;
    ep[0].ne_name = ".";
    ep[0].ne_nextentry = &ep[1];
    *(u_int *) ep[0].ne_cookie = 0;

    /* construct ".." */
    if (mp->am_parent)
      ep[1].ne_fileid = mp->am_parent->am_gen;
    else
      ep[1].ne_fileid = mp->am_gen;
    ep[1].ne_name = "..";
    ep[1].ne_nextentry = 0;
    *(u_int *) ep[1].ne_cookie = ~(u_int) 0;

    /*
     * If map is browsable, call a function make_entry_chain() to construct
     * a linked list of unmounted keys, and return it.  Then link the chain
     * to the regular list.  Get the chain only once, but return
     * chunks of it each time.
     */
    te = make_entry_chain(mp, dp->dl_entries);
    if (!te)
      return 0;
#ifdef DEBUG_READDIR
    for (ne=te; ne; ne=ne->ne_nextentry)
      plog(XLOG_INFO, "gen1 key \"%s\"", ne->ne_name);
#endif /* DEBUG_READDIR */

    /* return only "chain_length" entries */
    te_next = te;
    for (i=1; i<chain_length; ++i) {
      te_next = te_next->ne_nextentry;
      if (!te_next)
	break;
    }
    if (te_next) {
      nfsentry *te_saved = te_next->ne_nextentry;
      te_next->ne_nextentry = NULL; /* terminate "te" chain */
      te_next = te_saved;	/* save rest of "te" for next interation */
      dp->dl_eof = FALSE;	/* tell readdir there's more */
    } else {
      dp->dl_eof = TRUE;	/* tell readdir that's it */
    }
    ep[1].ne_nextentry = te;	/* append this chunk of "te" chain */
#ifdef DEBUG_READDIR
    for (ne=te; ne; ne=ne->ne_nextentry)
      plog(XLOG_INFO, "gen2 key \"%s\"", ne->ne_name);
#endif /* DEBUG_READDIR */
    return 0;
  } /* end of "if (gen == 0)" statement */

#ifdef DEBUG
  dlog("real child");
#endif /* DEBUG */

  if (gen == ~(u_int) 0) {
#ifdef DEBUG
    dlog("End of readdir in %s", mp->am_path);
#endif /* DEBUG */
    dp->dl_eof = TRUE;
    dp->dl_entries = 0;
    return 0;
  }

  /*
   * If browsable directories, then continue serving readdir() with another
   * chunk of entries, starting from where we left off (when gen was equal
   * to 0).  Once again, assume last chunk served to readdir.
   */
  dp->dl_eof = TRUE;
  dp->dl_entries = ep;

  te = te_next;			/* reset 'te' from last saved te_next */
  if (!te) {			/* another indicator of end of readdir */
    dp->dl_entries = 0;
    return 0;
  }
  /*
   * compute # of entries to send in this chain.
   * heuristics: 30 bytes per entry.
   */
  chain_length = count / 30;
  /* return only "chain_length" entries */
  for (i=1; i<chain_length; ++i) {
    te_next = te_next->ne_nextentry;
    if (!te_next)
      break;
  }
  if (te_next) {
    nfsentry *te_saved = te_next->ne_nextentry;
    te_next->ne_nextentry = NULL; /* terminate "te" chain */
    te_next = te_saved;		/* save rest of "te" for next interation */
    dp->dl_eof = FALSE;		/* tell readdir there's more */
  }
  ep = te;			/* send next chunk of "te" chain */
  dp->dl_entries = ep;
#ifdef DEBUG_READDIR
  plog(XLOG_INFO, "dl_entries=0x%x, te_next=0x%x, dl_eof=%d",
       dp->dl_entries, te_next, dp->dl_eof);
  for (ne=te; ne; ne=ne->ne_nextentry)
    plog(XLOG_INFO, "gen2 key \"%s\"", ne->ne_name);
#endif /* DEBUG_READDIR */
  return 0;
}


static am_node *
dfs_readlink(am_node *mp, int *error_return)
{
  am_node *xp;
  int rc = 0;

  xp = next_nonerror_node(mp->am_child);
  if (!xp) {
    if (!mp->am_mnt->mf_private)
      afs_mkcacheref(mp->am_mnt);	/* XXX */
    xp = afs_lookuppn(mp, mp->am_path + 1, &rc, VLOOK_CREATE);
  }
  if (xp) {
    new_ttl(xp);		/* (7/12/89) from Rein Tollevik */
    return xp;
  }
  if (amd_state == Finishing)
    rc = ENOENT;
  *error_return = rc;
  return 0;
}


#ifdef HAVE_AM_FS_UNION
/*
 * Create a reference to a union'ed entry
 */
static int
create_union_node(char *dir, voidp arg)
{
  if (!STREQ(dir, "/defaults")) {
    int error = 0;
    (void) toplvl_ops.lookuppn(arg, dir, &error, VLOOK_CREATE);
    if (error > 0) {
      errno = error;		/* XXX */
      plog(XLOG_ERROR, "Could not mount %s: %m", dir);
    }
    return error;
  }
  return 0;
}


static void
union_mounted(mntfs *mf)
{
  int i;

  afs_mkcacheref(mf);

  /*
   * Having made the union mount point,
   * populate all the entries...
   */
  for (i = 0; i <= last_used_map; i++) {
    am_node *mp = exported_ap[i];
    if (mp && mp->am_mnt == mf) {
      /* return value from create_union_node is ignored by mapc_keyiter */
      (void) mapc_keyiter((mnt_map *) mp->am_mnt->mf_private,
			  (void (*)(char *, voidp)) create_union_node,
			  mp);
      break;
    }
  }
}
#endif /* HAVE_AM_FS_UNION */


#ifdef HAVE_FS_AUTOFS
/*
 * Pick a file system to try mounting and
 * do that in the background if necessary
 *
 For each location:
 if it is new -defaults then
 extract and process
 continue;
 fi
 if it is a cut then
 if a location has been tried then
 break;
 fi
 continue;
 fi
 parse mount location
 discard previous mount location if required
 find matching mounted filesystem
 if not applicable then
 this_error = No such file or directory
 continue
 fi
 if the filesystem failed to be mounted then
 this_error = error from filesystem
 elif the filesystem is mounting or unmounting then
 this_error = -1
 elif the fileserver is down then
 this_error = -1
 elif the filesystem is already mounted
 this_error = 0
 break
 fi
 if no error on this mount then
 this_error = initialise mount point
 fi
 if no error on this mount and mount is delayed then
 this_error = -1
 fi
 if this_error < 0 then
 retry = true
 fi
 if no error on this mount then
 make mount point if required
 fi
 if no error on this mount then
 if mount in background then
 run mount in background
 return -1
 else
 this_error = mount in foreground
 fi
 fi
 if an error occured on this mount then
 update stats
 save error in mount point
 fi
 endfor
 */
static int
autofs_bgmount(struct continuation * cp, int mpe)
{
  mntfs *mf = cp->mp->am_mnt;	/* Current mntfs */
  mntfs *mf_retry = 0;		/* First mntfs which needed retrying */
  int this_error = -1;		/* Per-mount error */
  int hard_error = -1;
  int mp_error = mpe;

  /*
   * Try to mount each location.
   * At the end:
   * hard_error == 0 indicates something was mounted.
   * hard_error > 0 indicates everything failed with a hard error
   * hard_error < 0 indicates nothing could be mounted now
   */
  for (; this_error && *cp->ivec; cp->ivec++) {
    am_ops *p;
    am_node *mp = cp->mp;
    char *link_dir;
    int dont_retry;

    if (hard_error < 0)
      hard_error = this_error;

    this_error = -1;

    if (**cp->ivec == '-') {
      /*
       * Pick up new defaults
       */
      if (cp->auto_opts && *cp->auto_opts)
	cp->def_opts = str3cat(cp->def_opts, cp->auto_opts, ";", *cp->ivec + 1);
      else
	cp->def_opts = strealloc(cp->def_opts, *cp->ivec + 1);
#ifdef DEBUG
      dlog("Setting def_opts to \"%s\"", cp->def_opts);
#endif /* DEBUG */
      continue;
    }
    /*
     * If a mount has been attempted, and we find
     * a cut then don't try any more locations.
     */
    if (STREQ(*cp->ivec, "/") || STREQ(*cp->ivec, "||")) {
      if (cp->tried) {
#ifdef DEBUG
	dlog("Cut: not trying any more locations for %s",
	     mp->am_path);
#endif /* DEBUG */
	break;
      }
      continue;
    }

    /* match the operators */
    p = ops_match(&cp->fs_opts, *cp->ivec, cp->def_opts, mp->am_path, cp->key, mp->am_parent->am_mnt->mf_info);

    /*
     * Find a mounted filesystem for this node.
     */
    mp->am_mnt = mf = realloc_mntfs(mf, p, &cp->fs_opts,
				    cp->fs_opts.opt_fs,
				    cp->fs_opts.fs_mtab,
				    cp->auto_opts,
				    cp->fs_opts.opt_opts,
				    cp->fs_opts.opt_remopts);

    p = mf->mf_ops;
#ifdef DEBUG
    dlog("Got a hit with %s", p->fs_type);
#endif /* DEBUG */

    /*
     * Note whether this is a real mount attempt
     */
    if (p == &efs_ops) {
      plog(XLOG_MAP, "Map entry %s for %s failed to match", *cp->ivec, mp->am_path);
      if (this_error <= 0)
	this_error = ENOENT;
      continue;
    } else {
      if (cp->fs_opts.fs_mtab) {
	plog(XLOG_MAP, "Trying mount of %s on \"%s\" fstype %s",
	     cp->fs_opts.fs_mtab, mp->am_path, p->fs_type);
      }
      cp->tried = TRUE;
    }

    this_error = 0;
    dont_retry = FALSE;

    if (mp->am_link) {
      free(mp->am_link);
      mp->am_link = 0;
    }
    link_dir = mf->mf_fo->opt_sublink;

    if (link_dir && *link_dir) {
      if (*link_dir == '/') {
	mp->am_link = strdup(link_dir);
      } else {
	/*
	 * try getting fs option from continuation, not mountpoint!
	 * Don't try logging the string from mf, since it may be bad!
	 */
	if (cp->fs_opts.opt_fs != mf->mf_fo->opt_fs)
	  plog(XLOG_ERROR, "use %s instead of 0x%x",
	       cp->fs_opts.opt_fs, mf->mf_fo->opt_fs);

	mp->am_link = str3cat((char *) 0,
			      cp->fs_opts.opt_fs, "/", link_dir);

	normalize_slash(mp->am_link);
      }
    }

    if (mf->mf_error > 0) {
      this_error = mf->mf_error;
    } else if (mf->mf_flags & (MFF_MOUNTING | MFF_UNMOUNTING)) {
      /*
       * Still mounting - retry later
       */
#ifdef DEBUG
      dlog("Duplicate pending mount fstype %s", p->fs_type);
#endif /* DEBUG */
      this_error = -1;
    } else if (FSRV_ISDOWN(mf->mf_server)) {
      /*
       * Would just mount from the same place
       * as a hung mount - so give up
       */
#ifdef DEBUG
      dlog("%s is already hung - giving up", mf->mf_mount);
#endif /* DEBUG */
      mp_error = EWOULDBLOCK;
      dont_retry = TRUE;
      this_error = -1;
    } else if (mf->mf_flags & MFF_MOUNTED) {
#ifdef DEBUG
      dlog("duplicate mount of \"%s\" ...", mf->mf_info);
#endif /* DEBUG */

      /*
       * Just call mounted()
       */
      am_mounted(mp);

      this_error = 0;
      break;
    }

    /*
     * Will usually need to play around with the mount nodes
     * file attribute structure.  This must be done here.
     * Try and get things initialised, even if the fileserver
     * is not known to be up.  In the common case this will
     * progress things faster.
     */
    if (!this_error) {
      /*
       * Fill in attribute fields.
       */
      if (mf->mf_ops->fs_flags & FS_DIRECTORY)
	mk_fattr(mp, NFDIR);
      else
	mk_fattr(mp, NFLNK);

      mp->am_fattr.na_fileid = mp->am_gen;

      if (p->fs_init)
	this_error = (*p->fs_init) (mf);
    }

    /*
     * Make sure the fileserver is UP before doing any more work
     */
    if (!FSRV_ISUP(mf->mf_server)) {
#ifdef DEBUG
      dlog("waiting for server %s to become available", mf->mf_server->fs_host);
#endif /* DEBUG */
      this_error = -1;
    }

    if (!this_error && mf->mf_fo->opt_delay) {
      /*
       * If there is a delay timer on the mount
       * then don't try to mount if the timer
       * has not expired.
       */
      int i = atoi(mf->mf_fo->opt_delay);
      if (i > 0 && clocktime() < (cp->start + i)) {
#ifdef DEBUG
	dlog("Mount of %s delayed by %ds", mf->mf_mount, i - clocktime() + cp->start);
#endif /* DEBUG */
	this_error = -1;
      }
    }

    if (this_error < 0 && !dont_retry) {
      if (!mf_retry)
	mf_retry = dup_mntfs(mf);
      cp->retry = TRUE;
    }

    if (!this_error)
      if (p->fs_flags & FS_MBACKGROUND) {
	mf->mf_flags |= MFF_MOUNTING;	/* XXX */
#ifdef DEBUG
	dlog("backgrounding mount of \"%s\"", mf->mf_mount);
#endif /* DEBUG */
	if (cp->callout) {
	  untimeout(cp->callout);
	  cp->callout = 0;
	}
	run_task(try_mount, (voidp) mp, afs_cont, (voidp) cp);
	mf->mf_flags |= MFF_MKMNT;	/* XXX */
	if (mf_retry)
	  free_mntfs(mf_retry);
	return -1;
      } else {
#ifdef DEBUG
	dlog("foreground mount of \"%s\" ...", mf->mf_info);
#endif /* DEBUG */
	this_error = try_mount((voidp) mp);
	if (this_error < 0) {
	  if (!mf_retry)
	    mf_retry = dup_mntfs(mf);
	  cp->retry = TRUE;
	}
      }

    if (this_error >= 0) {
      if (this_error > 0) {
	amd_stats.d_merr++;
	if (mf != mf_retry) {
	  mf->mf_error = this_error;
	  mf->mf_flags |= MFF_ERROR;
	}
      }

      /*
       * Wakeup anything waiting for this mount
       */
      wakeup((voidp) mf);
    }
  }

  if (this_error && cp->retry) {
    free_mntfs(mf);
    mf = cp->mp->am_mnt = mf_retry;
    /*
     * Not retrying again (so far)
     */
    cp->retry = FALSE;
    cp->tried = FALSE;
    /*
     * Start at the beginning.
     * Rewind the location vector and
     * reset the default options.
     */
    cp->ivec = cp->xivec;
    cp->def_opts = strealloc(cp->def_opts, cp->auto_opts);
    /*
     * Arrange that autofs_bgmount is called
     * after anything else happens.
     */
#ifdef DEBUG
    dlog("Arranging to retry mount of %s", cp->mp->am_path);
#endif /* DEBUG */
    sched_task(afs_retry, (voidp) cp, (voidp) mf);
    if (cp->callout)
      untimeout(cp->callout);
    cp->callout = timeout(RETRY_INTERVAL, wakeup, (voidp) mf);

    cp->mp->am_ttl = clocktime() + RETRY_INTERVAL;

    /*
     * Not done yet - so don't return anything
     */
    return -1;
  }

  if (hard_error < 0 || this_error == 0)
    hard_error = this_error;

  /*
   * Discard handle on duff filesystem.
   * This should never happen since it
   * should be caught by the case above.
   */
  if (mf_retry) {
    if (hard_error)
      plog(XLOG_ERROR, "discarding a retry mntfs for %s", mf_retry->mf_mount);
    free_mntfs(mf_retry);
  }

  /*
   * If we get here, then either the mount succeeded or
   * there is no more mount information available.
   */
  if (hard_error < 0 && mp_error)
    hard_error = cp->mp->am_error = mp_error;
  if (hard_error > 0) {
    /*
     * Set a small(ish) timeout on an error node if
     * the error was not a time out.
     */
    switch (hard_error) {
    case ETIMEDOUT:
    case EWOULDBLOCK:
      cp->mp->am_timeo = 17;
      break;
    default:
      cp->mp->am_timeo = 5;
      break;
    }
    new_ttl(cp->mp);
  }

  /*
   * Make sure that the error value in the mntfs has a
   * reasonable value.
   */
  if (mf->mf_error < 0) {
    mf->mf_error = hard_error;
    if (hard_error)
      mf->mf_flags |= MFF_ERROR;
  }

  /*
   * In any case we don't need the continuation any more
   */
  free_continuation(cp);

  return hard_error;
}


/*
 * Automount interface to RPC lookup routine
 * Find the corresponding entry and return
 * the file handle for it.
 */
am_node *
autofs_lookuppn(am_node *mp, char *fname, int *error_return, int op)
{
  am_node *ap, *new_mp, *ap_hung;
  char *info;			/* Mount info - where to get the file system */
  char **ivec, **xivec;		/* Split version of info */
  char *auto_opts;		/* Automount options */
  int error = 0;		/* Error so far */
  char path_name[MAXPATHLEN];	/* General path name buffer */
  char apath[MAXPATHLEN];	/* authofs path (added space) */
  char *pfname;			/* Path for database lookup */
  struct continuation *cp;	/* Continuation structure if need to mount */
  int in_progress = 0;		/* # of (un)mount in progress */
  char *dflts;
  mntfs *mf;

#ifdef DEBUG
  dlog("in autofs_lookuppn");
#endif /* DEBUG */

  /*
   * If the server is shutting down
   * then don't return information
   * about the mount point.
   */
  if (amd_state == Finishing) {
#ifdef DEBUG
    if ((mf = mp->am_mnt) == 0 || mf->mf_ops == &dfs_ops)
      dlog("%s mount ignored - going down", fname);
    else
      dlog("%s/%s mount ignored - going down", mp->am_path, fname);
#endif /* DEBUG */
    ereturn(ENOENT);
  }

  /*
   * Handle special case of "." and ".."
   */
  if (fname[0] == '.') {
    if (fname[1] == '\0')
      return mp;		/* "." is the current node */
    if (fname[1] == '.' && fname[2] == '\0') {
      if (mp->am_parent) {
#ifdef DEBUG
	dlog(".. in %s gives %s", mp->am_path, mp->am_parent->am_path);
#endif /* DEBUG */
	return mp->am_parent;	/* ".." is the parent node */
      }
      ereturn(ESTALE);
    }
  }

  /*
   * Check for valid key name.
   * If it is invalid then pretend it doesn't exist.
   */
  if (!valid_key(fname)) {
    plog(XLOG_WARNING, "Key \"%s\" contains a disallowed character", fname);
    ereturn(ENOENT);
  }

  /*
   * Expand key name.
   * fname is now a private copy.
   */
  fname = expand_key(fname);

  for (ap_hung = 0, ap = mp->am_child; ap; ap = ap->am_osib) {
    /*
     * Otherwise search children of this node
     */
    if (FSTREQ(ap->am_name, fname)) {
      mf = ap->am_mnt;
      if (ap->am_error) {
	error = ap->am_error;
	continue;
      }
      /*
       * If the error code is undefined then it must be
       * in progress.
       */
      if (mf->mf_error < 0)
	goto in_progrss;

      /*
       * Check for a hung node
       */
      if (FSRV_ISDOWN(mf->mf_server)) {
#ifdef DEBUG
	dlog("server hung");
#endif /* DEBUG */
	error = ap->am_error;
	ap_hung = ap;
	continue;
      }
      /*
       * If there was a previous error with this node
       * then return that error code.
       */
      if (mf->mf_flags & MFF_ERROR) {
	error = mf->mf_error;
	continue;
      }
      if (!(mf->mf_flags & MFF_MOUNTED) || (mf->mf_flags & MFF_UNMOUNTING)) {
      in_progrss:
	/*
	 * If the fs is not mounted or it is unmounting then there
	 * is a background (un)mount in progress.  In this case
	 * we just drop the RPC request (return nil) and
	 * wait for a retry, by which time the (un)mount may
	 * have completed.
	 */
#ifdef DEBUG
	dlog("ignoring mount of %s in %s -- flags (%x) in progress",
	     fname, mf->mf_mount, mf->mf_flags);
#endif /* DEBUG */
	in_progress++;
	continue;
      }

      /*
       * Otherwise we have a hit: return the current mount point.
       */
#ifdef DEBUG
      dlog("matched %s in %s", fname, ap->am_path);
#endif /* DEBUG */
      free(fname);
      return ap;
    }
  }

  if (in_progress) {
#ifdef DEBUG
    dlog("Waiting while %d mount(s) in progress", in_progress);
#endif /* DEBUG */
    free(fname);
    ereturn(-1);
  }

  /*
   * If an error occured then return it.
   */
  if (error) {
#ifdef DEBUG
    errno = error;		/* XXX */
    dlog("Returning error: %m", error);
#endif /* DEBUG */
    free(fname);
    ereturn(error);
  }

  /*
   * If doing a delete then don't create again!
   */
  switch (op) {
  case VLOOK_DELETE:
    ereturn(ENOENT);

  case VLOOK_CREATE:
    break;

  default:
    plog(XLOG_FATAL, "Unknown op to autofs_lookuppn: 0x%x", op);
    ereturn(EINVAL);
  }

  /*
   * If the server is going down then just return,
   * don't try to mount any more file systems
   */
  if ((int) amd_state >= (int) Finishing) {
#ifdef DEBUG
    dlog("not found - server going down anyway");
#endif /* DEBUG */
    free(fname);
    ereturn(ENOENT);
  }

  /*
   * If we get there then this is a reference to an,
   * as yet, unknown name so we need to search the mount
   * map for it.
   */
  if (mp->am_pref) {
    sprintf(path_name, "%s%s", mp->am_pref, fname);
    pfname = path_name;
  } else {
    pfname = fname;
  }

  mf = mp->am_mnt;

#ifdef DEBUG
  dlog("will search map info in %s to find %s", mf->mf_info, pfname);
#endif /* DEBUG */
  /*
   * Consult the oracle for some mount information.
   * info is malloc'ed and belongs to this routine.
   * It ends up being free'd in free_continuation().
   *
   * Note that this may return -1 indicating that information
   * is not yet available.
   */
  error = mapc_search((mnt_map *) mf->mf_private, pfname, &info);
  if (error) {
    if (error > 0)
      plog(XLOG_MAP, "No map entry for %s", pfname);
    else
      plog(XLOG_MAP, "Waiting on map entry for %s", pfname);
    free(fname);
    ereturn(error);
  }
#ifdef DEBUG
  dlog("mount info is %s", info);
#endif /* DEBUG */

  /*
   * Split info into an argument vector.
   * The vector is malloc'ed and belongs to
   * this routine.  It is free'd in free_continuation()
   */
  xivec = ivec = strsplit(info, ' ', '\"');

  /*
   * Default error code...
   */
  if (ap_hung)
    error = EWOULDBLOCK;
  else
    error = ENOENT;

  /*
   * Allocate a new map
   */
  new_mp = exported_ap_alloc();
  if (new_mp == 0) {
    free((voidp) xivec);
    free((voidp) info);
    free((voidp) fname);
    ereturn(ENOSPC);
  }
  if (mf->mf_auto)
    auto_opts = mf->mf_auto;
  else
    auto_opts = "";

  auto_opts = strdup(auto_opts);

#ifdef DEBUG
  dlog("searching for /defaults entry");
#endif /* DEBUG */
  if (mapc_search((mnt_map *) mf->mf_private, "/defaults", &dflts) == 0) {
    char *dfl;
    char **rvec;
#ifdef DEBUG
    dlog("/defaults gave %s", dflts);
#endif /* DEBUG */
    if (*dflts == '-')
      dfl = dflts + 1;
    else
      dfl = dflts;

    /*
     * Chop the defaults up
     */
    rvec = strsplit(dfl, ' ', '\"');

    if (gopt.flags & CFM_ENABLE_DEFAULT_SELECTORS) {
      /*
       * Pick whichever first entry matched the list of selectors.
       * Strip the selectors from the string, and assign to dfl the
       * rest of the string.
       */
      if (rvec) {
	am_opts ap;
	am_ops *pt;
	char **sp = rvec;
	while (*sp) {		/* loop until you find something, if any */
	  memset((char *) &ap, 0, sizeof(am_opts));
	  pt = ops_match(&ap, *sp, "", mp->am_path, "/defaults",
			 mp->am_parent->am_mnt->mf_info);
	  if (pt == &efs_ops) {
	    plog(XLOG_MAP, "failed to match defaults for \"%s\"", *sp);
	  } else {
	    dfl = strip_selectors(*sp, "/defaults");
	    plog(XLOG_MAP, "matched default selectors \"%s\"", dfl);
	    break;
	  }
	  ++sp;
	}
      }
    } else {			/* not enable_default_selectors */
      /*
       * Extract first value
       */
      dfl = rvec[0];
    }

    /*
     * If there were any values at all...
     */
    if (dfl) {
      /*
       * Log error if there were other values
       */
      if (!(gopt.flags & CFM_ENABLE_DEFAULT_SELECTORS) && rvec[1]) {
# ifdef DEBUG
	dlog("/defaults chopped into %s", dfl);
# endif /* DEBUG */
	plog(XLOG_USER, "More than a single value for /defaults in %s", mf->mf_info);
      }

      /*
       * Prepend to existing defaults if they exist,
       * otherwise just use these defaults.
       */
      if (*auto_opts && *dfl) {
	char *nopts = (char *) xmalloc(strlen(auto_opts) + strlen(dfl) + 2);
	sprintf(nopts, "%s;%s", dfl, auto_opts);
	free(auto_opts);
	auto_opts = nopts;
      } else if (*dfl) {
	auto_opts = strealloc(auto_opts, dfl);
      }
    }
    free(dflts);
    /*
     * Don't need info vector any more
     */
    free((voidp) rvec);
  }

  /*
   * Fill it in
   */
  init_map(new_mp, fname);

  /*
   * Turn on autofs flag if needed.
   */
  if (mp->am_flags & AMF_AUTOFS) {
    new_mp->am_flags |= AMF_AUTOFS;
  }

  /*
   * Put it in the table
   */
  insert_am(new_mp, mp);

  /*
   * Fill in some other fields,
   * path and mount point.
   *
   * bugfix: do not prepend old am_path if direct map
   *         <wls@astro.umd.edu> William Sebok
   */

  strcpy(apath, fname);
  strcat(apath, " ");
  new_mp->am_path = str3cat(new_mp->am_path,
			    mf->mf_ops == &dfs_ops ? "" : mp->am_path,
			    *fname == '/' ? "" : "/",
			    apath);

#ifdef DEBUG
  dlog("setting path to \"%s\"", new_mp->am_path);
#endif /* DEBUG */

  /*
   * Take private copy of pfname
   */
  pfname = strdup(pfname);

  /*
   * Construct a continuation
   */
  cp = ALLOC(struct continuation);
  cp->callout = 0;
  cp->mp = new_mp;
  cp->xivec = xivec;
  cp->ivec = ivec;
  cp->info = info;
  cp->key = pfname;
  cp->auto_opts = auto_opts;
  cp->retry = FALSE;
  cp->tried = FALSE;
  cp->start = clocktime();
  cp->def_opts = strdup(auto_opts);
  memset((voidp) &cp->fs_opts, 0, sizeof(cp->fs_opts));

  /*
   * Try and mount the file system.  If this succeeds immediately (possible
   * for a ufs file system) then return the attributes, otherwise just
   * return an error.
   */
  error = autofs_bgmount(cp, error);
  reschedule_timeout_mp();
  if (!error) {
    free(fname);
    return new_mp;
  }

  /*
   * Code for quick reply.  If nfs_program_2_transp is set, then
   * its the transp that's been passed down from nfs_program_2().
   * If new_mp->am_transp is not already set, set it by copying in
   * nfs_program_2_transp.  Once am_transp is set, quick_reply() can
   * use it to send a reply to the client that requested this mount.
   */
  if (nfs_program_2_transp && !new_mp->am_transp) {
    new_mp->am_transp = (SVCXPRT *) xmalloc(sizeof(SVCXPRT));
    *(new_mp->am_transp) = *nfs_program_2_transp;
  }
  if (error && (new_mp->am_mnt->mf_ops == &efs_ops))
    new_mp->am_error = error;

  assign_error_mntfs(new_mp);

  free(fname);

  ereturn(error);
}
#endif /* HAVE_FS_AUTOFS */
