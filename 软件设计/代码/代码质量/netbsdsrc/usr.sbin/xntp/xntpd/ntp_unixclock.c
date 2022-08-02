/*	$NetBSD: ntp_unixclock.c,v 1.3 1998/01/09 06:06:46 perry Exp $	*/

/*
 * ntp_unixclock.c - routines for reading and adjusting a 4BSD-style
 *		     system clock.  Emacs has hide-ifdef-mode ...
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>
#include <sys/types.h>
#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif /* HAVE_UNISTD_H */
# ifdef NLIST_STRUCT
#  include <nlist.h>
#  ifdef NLIST_NAME_UNION
#   define N_NAME n_un.n_name
#  else /* not NLIST_NAME_UNION */
#   define N_NAME n_name
#  endif /* not NLIST_NAME_UNION */
# endif /* NLIST_STRUCT */
# include <sys/stat.h>
# include <sys/time.h>

#ifdef HAVE_SYS_PARAM_H
# include <sys/param.h>
#endif
#ifdef HAVE_UTMP_H
# include <utmp.h>
#endif

#if defined(HAVE_GETBOOTFILE)
# include <paths.h>
#endif

#include "ntpd.h"
#include "ntp_io.h"
#include "ntp_unixtime.h"
#include "ntp_stdlib.h"

#if defined(HAVE_LIBKVM)
# ifdef HAVE_SYS_PROC_H
#  include <sys/proc.h>
# endif
# include <kvm.h>
# include <limits.h>

# ifndef _POSIX2_LINE_MAX
#  define _POSIX2_LINE_MAX 2048
# endif
#endif	/* HAVE_LIBKVM */

#ifdef HAVE_SYS_TIMEX_H		/* Linux - also HAVE___ADJTIMEX */
# include <sys/timex.h>
#endif

#ifdef hz /* Was: RS6000 */
# undef hz
#endif /* hz */

#ifdef HAVE_SYSCTL_CLOCKRATE
#include <sys/param.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#endif

extern int debug;
/*
 * These routines (init_systime, get_systime, step_systime, adj_systime)
 * implement an interface between the (more or less) system independent
 * bits of NTP and the peculiarities of dealing with the Unix system
 * clock.  These routines will run with good precision fairly independently
 * of your kernel's value of tickadj.  I couldn't tell the difference
 * between tickadj==40 and tickadj==5 on a microvax, though I prefer
 * to set tickadj == 500/hz when in doubt.  At your option you
 * may compile this so that your system's clock is always slewed to the
 * correct time even for large corrections.  Of course, all of this takes
 * a lot of code which wouldn't be needed with a reasonable tickadj and
 * a willingness to let the clock be stepped occasionally.  Oh well.
 */
extern	long adj_precision;	/* adj precision in usec (tickadj) */
extern	long tvu_maxslew;	/* maximum adjust doable in one sec (usec) */

#ifdef SYS_WINNT
extern  long units_per_tick;    /* imported from lib/systime.c module */
#endif /* SYS_WINNT */

extern	u_long tsf_maxslew;	/* same as above, as long format */

extern	l_fp sys_clock_offset;	/* correction for current system time */

#if defined(GDT_SURVEYING)
extern l_fp gdt_rsadj;		/* running sum of adjustments to time */
#endif

/*
 * Import sys_clock (it is updated in get_systime)
 */
extern long sys_clock;

/*
 * Export default_tick and default_tickadj (for ntp_config)
 */
u_long default_tick = 0;
u_long default_tickadj = 0;

static	void	clock_parms	P((u_long *, u_long *));

/*
 * init_systime - initialize the system clock support code, return
 *		  clock precision.
 *
 * Note that this code obtains to kernel variables related to the local
 * clock, tickadj and tick.  The code knows how the Berkeley adjtime
 * call works, and assumes these two variables are obtainable and are
 * used in the same manner.  Tick is supposed to be the number of
 * microseconds which are added to the system clock at clock interrupt
 * time when the time isn't being slewed.  Tickadj is supposed to be
 * the number of microseconds which are added or subtracted from tick when
 * the time is being slewed.
 *
 * If either of these two variables is missing, or is there but is used
 * for a purpose different than that described, you are SOL and may have
 * to do some custom kludging.
 *
 * This really shouldn't be in here.
 */
void
init_systime()
{
	u_long tickadj;
	u_long tick;
	u_long hz;

	/*
	 * Obtain the values
	 */
#if !defined(VMS)
	clock_parms(&tickadj, &tick);
#else
	{
		extern int get_tickfreq(int *FREQ, int *SYSTICK);
		int freq,systick,sts;

		sts = get_tickfreq(&freq,&systick);
		if(!(sts & 1)) lib$stop(sts);

		tick = 1000000/freq;	/* (usec) */
	}
	tickadj = tick/10;	/* VMS_{ADJTIME,TICTIME}.C will do up to 10% */
#endif /* VMS */
#ifdef	DEBUG
	if (debug)
		printf("kernel vars: tickadj = %ld, tick = %ld\n", tickadj, tick);
#endif

	/*
	 * If tickadj or hz wasn't found, we're doomed.  If hz is
	 * unreasonably small, forget it.
	 */
	if (tickadj == 0 || tick == 0) {
		msyslog(LOG_ERR, "tickadj or tick unknown, exiting");
		exit(3);
	}
	if (tick > 65535) {
		msyslog(LOG_ERR, "tick value of %lu is unreasonably large",
		    tick);
		exit(3);
	}

	/*
	 * Estimate hz from tick
	 */
	hz = 1000000L / tick;

#ifdef SYS_WINNT
	if ((1000000L % tick) >	tick/2)
		hz += 1;
#endif /* SYS_WINNT */

	/*
	 * Set adj_precision and the maximum slew based on this.  Note
	 * that maxslew is set slightly shorter than it needs to be as
	 * insurance that all slews requested will complete in one second.
	 */
#ifdef ADJTIME_IS_ACCURATE
	adj_precision = 1;
#else
# if defined(SCO3_TICKADJ) || defined(SCO5_TICKADJ)
	adj_precision = tickadj * hz;
# else
#  ifndef SYS_WINNT
	adj_precision = tickadj;
#  else
	/* minimum adjustment is one 100 nanosecond unit at each clock tick */
	adj_precision = (long)(hz * 0.1);
#  endif /* SYS_WINNT */
# endif /* not SCO[35]_TICKADJ */
#endif /* ADJTIME_IS_ACCURATE */
#ifdef NEED_HPUX_ADJTIME
	/*
	 * when using adjtimed daemon, need to allow more time
	 * because daemon may not run right away
	 */
	tvu_maxslew = tickadj * (hz - 3);
#else
# if defined(SLEWALWAYS) && !defined(ADJTIME_IS_ACCURATE)
	/*
	 * give us more time if we are always slewing... just in case
	 */
	tvu_maxslew = tickadj * (hz - 3);
# else
#  if !defined(SYS_WINNT) && !defined(SCO3_TICKADJ) && !defined(SCO5_TICKADJ)
	tvu_maxslew = tickadj * (hz - 1);
#  else
	tvu_maxslew = tickadj * hz;
#  endif /* SYS_WINTNT */
# endif /* SLEWALWAYS */
#endif /* NEED_HPUX_ADJTIME */
	if (tvu_maxslew > 999990) {
		/*
		 * Don't let the maximum slew exceed 1 second in 4.  This
		 * simplifies calculations a lot since we can then deal
		 * with less-than-one-second fractions.
		 */
		tvu_maxslew = (999990/adj_precision) * adj_precision;
	}
	TVUTOTSF(tvu_maxslew, tsf_maxslew);
	NLOG(NLOG_SYSINFO) /* conditional if clause for conditional syslog */
	  msyslog(LOG_NOTICE, "tickadj = %d, tick = %d, tvu_maxslew = %d, est. hz = %d",
	    tickadj, tick, tvu_maxslew, hz);
#ifdef DEBUG
	if (debug)
		printf(
	"adj_precision = %ld, tvu_maxslew = %ld, tsf_maxslew = 0.%08lx\n",
		    adj_precision, tvu_maxslew, tsf_maxslew);
#endif

	/*
	 * Set the current offset to 0
	 */
	L_CLR(&sys_clock_offset);
#if defined(GDT_SURVEYING)
	/*
	 * Set the current increment
	 */

	L_CLR(&gdt_rsadj);
#endif /* GDT_SURVEYING */
}


#if !defined(VMS)

# ifndef HZ
#  define HZ	DEFAULT_HZ
# endif

# ifdef NLIST_STRUCT
#  ifdef NLIST_NAME_UNION
#   define NL_B {{
#   define NL_E }}
#  else
#   define NL_B {
#   define NL_E }
#  endif
# endif

#define K_FILLER_NAME "DavidLetterman"

/*
 * clock_parms - return the local clock tickadj and tick parameters
 *
 */

#ifdef HAVE_SYSCTL_CLOCKRATE
static void
clock_parms(ptickadj, ptick)
    u_long *ptickadj;
    u_long *ptick;
{
    int mib[2];
    size_t len;
    struct clockinfo c;
    int e;

    mib[0] = CTL_KERN;
    mib[1] = KERN_CLOCKRATE;
    len = sizeof(c);
    e = sysctl(mib,2,&c,&len,NULL,0);
    if (e != 0) {
	NLOG(NLOG_SYSINFO) /* conditional if clause for conditional syslog */
	syslog(LOG_NOTICE, "Could not find clockrate with sysctl\n");
	exit(1);
    }
    *ptickadj = c.tickadj;
    *ptick = c.tick;
}
#else

static void
clock_parms(ptickadj, ptick)
     u_long *ptickadj;
     u_long *ptick;
{
  u_long tick;
  int got_tick = 0;
  int got_tickadj = 0;
#ifdef SYS_WINNT
  DWORD add, every;
  BOOL noslew;
#else
  int hz;
#ifndef NOKMEM
  static struct nlist nl[] =
  {
    NL_B
# ifdef K_TICKADJ_NAME
#  define N_TICKADJ 0
    K_TICKADJ_NAME
# else
    K_FILLER_NAME
# endif /* K_TICKADJ_NAME */
    NL_E,
    NL_B
# ifdef K_TICK_NAME
#  define N_TICK 1
    K_TICK_NAME
# else
    K_FILLER_NAME
# endif /* K_TICK_NAME */
    NL_E,
    NL_B "" NL_E,
  };
# ifdef HAVE_K_OPEN
# else /* not HAVE_K_OPEN */
#  ifdef HAVE_KVM_OPEN
  register kvm_t *kd;
#  else /* not HAVE_KVM_OPEN */
  register int i;
  int kmem;
  struct stat stbuf;
  off_t where;
#   ifdef HAVE_BOOTFILE
  const char *kernelname;
#   else /* not HAVE_BOOTFILE */
  static char *kernelnames[] =
  {
    "/kernel/unix",
    "/kernel",
    "/vmunix",
    "/unix",
    "/mach",
    "/hp-ux",
    "/386bsd",
    "/netbsd",
    "/stand/vmunix",
    "/bsd",
#    ifdef KERNELFILE
    KERNELFILE,
#    endif
    NULL
  };
#   endif /* not HAVE_BOOTFILE */
#  endif /* not HAVE_KVM_OPEN */
# endif /* not HAVE_K_OPEN */
#endif /* not NOKMEM */
#endif /* not SYS_WINNT */

#ifdef SYS_WINNT
  if (!GetSystemTimeAdjustment(&add, &every, &noslew))
    {
      *ptick = 0;
      *ptickadj = 0;
      return;
    }
  units_per_tick = add;
#else /* not SYS_WINNT */
  hz = HZ;
#if defined(HAVE_SYSCONF) && defined(_SC_CLK_TCK)
  hz = (int) sysconf (_SC_CLK_TCK);
#endif /* SYS_WINNT */
#ifdef OVERRIDE_HZ
  hz = DEFAULT_HZ;
#endif

  {
#ifndef NOKMEM
# ifdef HAVE_K_OPEN /* { */
    if (K_open((char *)0, O_RDONLY, "/vmunix")!=0)
      {
	msyslog(LOG_ERR, "K_open failed");
	exit(3);
      }
    kusenlist(1);
    if (knlist(nl) != 0)
      {
	msyslog(LOG_ERR, "knlist failed");
	exit(3);
      }
# else  /* } not HAVE_K_OPEN { */
#  ifdef HAVE_KVM_OPEN /* { */
    if ((kd = kvm_open(NULL, NULL, NULL, O_RDONLY, NULL)) == NULL)
      {
	msyslog(LOG_ERR, "kvm_open failed");
	exit(3);
      }
    if (kvm_nlist(kd, nl) == -1)
      {
	msyslog(LOG_ERR, "kvm_nlist failed");
	exit(3);
      }
#  else /* } not HAVE_KVM_OPEN { */
#   ifdef HAVE_GETBOOTFILE
    kernelname = getbootfile();
    if (!kernelname)
      {
	msyslog(LOG_ERR, "getbootfile() didn't find kernel name!");
	exit(3);
      }
    else if (stat(kernelname, &stbuf) == -1)
      {
	msyslog(LOG_ERR, "stat(%s) failed: %m", kernelname);
	exit(3);
      }
    else if (nlist(kernelname, nl) < 0)
      {
	msyslog(LOG_ERR, "nlist(%s) failed: %m", kernelname);
	exit(3);
      }  
#   else /* not HAVE_GETBOOTFILE */
    for (i = 0; kernelnames[i] != NULL; i++)
      {
	if (stat(kernelnames[i], &stbuf) == -1)
	  continue;
	if (nlist(kernelnames[i], nl) >= 0)
	  break;
      }
    if (kernelnames[i] == NULL)
      {
	msyslog(LOG_ERR, "Clock init couldn't find kernel object file");
      }
#   endif /* not HAVE_GETBOOTFILE */
    kmem = open("/dev/kmem", O_RDONLY);
    if (kmem < 0)
      {
	msyslog(LOG_ERR, "Can't open /dev/kmem for reading: %m");
#ifdef	DEBUG
	if (debug)
	  perror("/dev/kmem");
#endif
      }
#  endif /* } not HAVE_KVM_OPEN */
# endif /* } not HAVE_K_OPEN */
#endif /* not NOKMEM */
  }
#endif /* not SYS_WINNT */

  /* Skippy says we need to know TICK before handling TICKADJ */
  {
#if defined(HAVE_SYS_TIMEX_H) && defined(HAVE___ADJTIMEX)
    struct timex txc;
#endif /* HAVE_SYS_TIMEX_H && HAVE___ADJTIMEX */

#if !defined(NOKMEM) && defined(N_TICK)
# ifdef HAVE_K_OPEN
    if (K_read(ptick, sizeof(*ptick), nl[N_TICK].n_value) != sizeof(*ptick))
      {
	msyslog(LOG_ERR, "K_read tick failed");
      }
    else
      {
	if (*ptick) ++got_tick;
      }
# else /* not HAVE_K_OPEN */
#  ifdef HAVE_KVM_OPEN
    if (kvm_read(kd, nl[N_TICK].n_value, (char *)ptick, sizeof(*ptick)) !=
	sizeof(*ptick))
      {
	msyslog(LOG_ERR, "kvm_read tick failed");
      }
    else
      {
	if (*ptick) ++got_tick;
      }
#  else /* not HAVE_KVM_OPEN */
    if ((where = nl[N_TICK].n_value) == 0)
      {
	msyslog(LOG_ERR, "Unknown kernel var <%s>",
	       nl[N_TICK].N_NAME);
      }
    else
      {
	if (lseek(kmem, where, SEEK_SET) == -1)
	  {
	    msyslog(LOG_ERR, "lseek for %s fails: %m",
		   nl[N_TICK].N_NAME);
	  }
	else
	  {
	    if (read(kmem, ptick, sizeof(*ptick)) != sizeof(*ptick))
	      {
		msyslog(LOG_ERR, "read for %s fails: %m",
		       nl[N_TICK].N_NAME);
	      }
	    else
	      {
#   ifdef NLIST_EXTRA_INDIRECTION
		/*
		 * Aix requires one more round of indirection
		 * if storage class a pointer.
		 */
		if ( nl[N_TICK].n_sclass == 0x6b)
		  {
		    if (lseek(kmem, *ptick, SEEK_SET) == -1)
		      {
			msyslog(LOG_ERR, "lseek2 for %s fails: %m",
			       nl[N_TICK].N_NAME);
		      }
		    else
		      {
			if (read(kmem, ptick, sizeof(*ptick)) !=
			    sizeof(*ptick))
			  {
			    msyslog(LOG_ERR, "read2 for %s fails: %m",
				   nl[N_TICK].N_NAME);
			  }
			else
			  {
			    if (*ptick) ++got_tick;
			  }
		      }
		  }
#   else /* not NLIST_EXTRA_INDIRECTION */
		if (*ptick) ++got_tick;
#   endif /* not NLIST_EXTRA_INDIRECTION */
	      }
	  }
      }
#  endif /* not HAVE_KVM_OPEN */
# endif /* not HAVE_K_OPEN */
# ifdef TICK_NANO
    if (got_tick)
      {
	*ptick /= 1000;
      }
# endif /* TICK_NANO */
#endif /* not NOKMEM && N_TICK */

    if (!got_tick && default_tick)
      {
	*ptick = default_tick;
	if (*ptick) ++got_tick;
      }

#ifdef PRESET_TICK
    if (!got_tick)
      {
# if defined(HAVE_SYS_TIMEX_H) && defined(HAVE___ADJTIMEX)
#  ifdef MOD_OFFSET
	txc.modes = 0;
#  else
	txc.mode = 0;
#  endif
	__adjtimex(&txc);
# endif /* HAVE_SYS_TIMEX_H && HAVE___ADJTIMEX */
	*ptick = (u_long) PRESET_TICK;
	if (*ptick) ++got_tick;
      }
#endif  /* PRESET_TICK */

    if (got_tick != 1)
      {
	msyslog(LOG_ERR, "Problem getting tick: %d != 1", got_tick);
	exit(3);
      }

    tick = *ptick;		/* This might be used by PRESET_TICKADJ */
  }

  /* Skippy says we need to know TICK before handling TICKADJ */
  {
#if !defined(NOKMEM) && defined(N_TICKADJ)
    if (nl[N_TICKADJ].n_value == 0)
      {
	msyslog(LOG_ERR, "Unknown kernel variable <%s>",
	       nl[N_TICKADJ].N_NAME);
      }
    else
      {
# ifdef HAVE_K_OPEN
	if (K_read(ptickadj, sizeof(*ptickadj), nl[N_TICKADJ].n_value) !=
	    sizeof(*ptickadj))
	  {
	    msyslog(LOG_ERR, "K_read tickadj failed");
	  }
	else
	  {
	    if (*ptickadj) ++got_tickadj;
	  }
# else /* not HAVE_K_OPEN */
#  ifdef HAVE_KVM_OPEN
	if (kvm_read(kd, nl[N_TICKADJ].n_value, (char *)ptickadj, sizeof(*ptickadj)) !=
	    sizeof(*ptickadj))
	  {
	    msyslog(LOG_ERR, "kvm_read tickadj failed");
	  }
	else
	  {
	    if (*ptickadj) ++got_tickadj;
	  }
#  else /* not HAVE_KVM_OPEN */
	if ((where = nl[N_TICKADJ].n_value) == 0)
	  {
	    msyslog(LOG_ERR, "Unknown kernel var <%s>",
		   nl[N_TICKADJ].N_NAME);
	  }
	else
	  {
	    if (lseek(kmem, where, SEEK_SET) == -1)
	      {
		msyslog(LOG_ERR, "lseek for %s fails: %m",
		       nl[N_TICKADJ].N_NAME);
	      }
	    else
	      {
		if (read(kmem, ptickadj, sizeof(*ptickadj)) !=
		    sizeof(*ptickadj))
		  {
		    msyslog(LOG_ERR, "read for %s fails: %m",
			   nl[N_TICKADJ].N_NAME);
		  }
		else
		  {
#   ifdef NLIST_EXTRA_INDIRECTION
		    /*
		     * Aix requires one more round of indirection
		     * if storage class a pointer.
		     */
		    if ( nl[N_TICKADJ].n_sclass == 0x6b)
		      {
			if (lseek(kmem, *ptickadj, SEEK_SET) == -1)
			  {
			    msyslog(LOG_ERR, "lseek2 for %s fails: %m",
				   nl[N_TICKADJ].N_NAME);
			  }
			else
			  {
			    if (read(kmem, ptickadj, sizeof(*ptickadj)) !=
				sizeof(*ptickadj))
			      {
				msyslog(LOG_ERR, "read2 for %s fails: %m",
				       nl[N_TICKADJ].N_NAME);
			      }
			    else
			      {
				if (*ptickadj) ++got_tickadj;
			      }
			  }
		      }
#   else /* not NLIST_EXTRA_INDIRECTION */
		    if (*ptickadj) ++got_tickadj;
#   endif /* not NLIST_EXTRA_INDIRECTION */
		  }
	      }
	  }
#  endif /* not HAVE_KVM_OPEN */
# endif /* not HAVE_K_OPEN */
      }

# ifdef TICKADJ_NANO
    if (got_tickadj)
      {
	*ptickadj /= 1000;
	if  (*ptickadj == 0)
	  {
	    *ptickadj = 1;
	  }
      }
# endif /* TICKADJ_NANO */
# ifdef SCO5_TICKADJ
    if (got_tickadj)
      {
	*ptickadj /= (1000 * hz);
      }
# else /* not SCO5_TICKADJ */
#  ifdef SCO3_TICKADJ
    if (got_tickadj)
      {
	*ptickadj *= (10000 / hz);
      }
#  endif /* SCO3_TICKADJ */
# endif/* not SCO5_TICKADJ */
#endif /* not NOKMEM && N_TICKADJ */

    if (!got_tickadj && default_tickadj)
      {
	*ptickadj = default_tickadj;
	if (*ptickadj) ++got_tickadj;
      }

# ifdef PRESET_TICKADJ
    if (!got_tickadj)
      {
	*ptickadj = (u_long) ((PRESET_TICKADJ) ? PRESET_TICKADJ : 1);
	if (*ptickadj) ++got_tickadj;
      }
# endif /* PRESET_TICKADJ */

    if (got_tickadj != 1)
      {
	msyslog(LOG_ERR, "Problem getting tickadj: %d != 1", got_tickadj);
	exit(3);
      }
  }

#ifndef NOKMEM
# ifdef HAVE_K_OPEN
  (void) K_close();
# else /* not HAVE_K_OPEN */
#  ifdef HAVE_KVM_OPEN
  if (kvm_close(kd) < 0)
    {
      msyslog(LOG_ERR, "kvm_close failed");
      exit(3);
    }
#  else /* not HAVE_KVM_OPEN */
  close(kmem);
#  endif /* not HAVE_KVM_OPEN */
# endif /* not HAVE_K_OPEN */
#endif /* not NOKMEM */

#ifdef	DEBUG
  if (debug)
    printf("tick = %ld, tickadj = %ld, hz = %d\n", *ptick, *ptickadj, hz);
#endif
}
#endif
#endif /* not VMS */
