/*-
 * Copyright (c) 1997 Michael Graff.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the author nor the names of other contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <err.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/rnd.h>

typedef struct {
	char *name;
	u_int32_t   type;
} arg_t;

arg_t source_types[] = {
	{ "unknown", RND_TYPE_UNKNOWN },
	{ "disk",    RND_TYPE_DISK },
	{ "network", RND_TYPE_NET },
	{ "net",     RND_TYPE_NET },
	{ "tape",    RND_TYPE_TAPE },
	{ "tty",     RND_TYPE_TTY },
	{ NULL,      0 }
};

static void usage(void);
u_int32_t find_type(char *name);
char *find_name(u_int32_t);
void do_ioctl(rndctl_t *);
char * strflags(u_int32_t);
void do_list(int, u_int32_t, char *);

static void
usage(void)
{
	errx(1, "Usage:  rndctl [-CEce | -l] [-d name | -t type]");
}

u_int32_t
find_type(char *name)
{
	arg_t *a;

	a = source_types;
	
	while (a->name != NULL) {
		if (strcmp(a->name, name) == 0)
			return a->type;
		a++;
	}

	errx(1, "Error:  Device type %s unknown", name);
	return 0;
}

char *
find_name(u_int32_t type)
{
	arg_t *a;

	a = source_types;
	
	while (a->name != NULL) {
		if (type == a->type)
			return a->name;
		a++;
	}

	errx(1, "Error:  Device type %u unknown", type);
	return 0;
}

void
do_ioctl(rndctl_t *rctl)
{
	int fd;
	int res;

	fd = open("/dev/urandom", O_RDONLY, 0644);
	if (fd < 0)
		err(1, "open");

	res = ioctl(fd, RNDCTL, rctl);
	if (res < 0)
		err(1, "ioctl(RNDCTL)");

	close(fd);
}

char *
strflags(u_int32_t fl)
{
	static char str[512];

	str[0] = 0;
	strcat(str, "<");

	if (fl & RND_FLAG_NO_ESTIMATE)
		strcat(str, "no");
	strcat(str, "estimate, ");
	if (fl & RND_FLAG_NO_COLLECT)
		strcat(str, "no");
	strcat(str, "collect>");

	return str;
}

#define HEADER "Device Name      Type           Bits Flags\n" \
               "---------------- -------- ---------- -----\n"

void
do_list(int all, u_int32_t type, char *name)
{
	rndstat_t       rstat;
	rndstat_name_t  rstat_name;
	int             fd;
	int             res;
	u_int32_t	start;

	fd = open("/dev/urandom", O_RDONLY, 0644);
	if (fd < 0)
		err(1, "open");

	if (all == 0 && type == 0xff) {
		strncpy(rstat_name.name, name, 16);
		res = ioctl(fd, RNDGETSRCNAME, &rstat_name);
		if (res < 0)
			err(1, "ioctl(RNDGETSRCNAME)");
		printf(HEADER);
		printf("%-16s %-8s %10u %s\n",
		       rstat_name.source.name,
		       find_name(rstat_name.source.tyfl & 0xff),
		       rstat_name.source.total,
		       strflags(rstat_name.source.tyfl));
		close(fd);
		return;
	}

	/*
	 * run through all the devices present in the system, and either
	 * print out ones that match, or print out all of them.
	 */
	printf(HEADER);
	start = 0;
	for (;;) {
		rstat.count = RND_MAXSTATCOUNT;
		rstat.start = start;
		res = ioctl(fd, RNDGETSRCNUM, &rstat);
		if (res < 0)
			err(1, "ioctl(RNDGETSRCNUM)");
                        
		if (rstat.count == 0)
			break;
                        
		for (res = 0 ; res < rstat.count ; res++) {
			if ((all != 0)
			    || (type == (rstat.source[res].tyfl & 0xff)))
				printf("%-16s %-8s %10u %s\n",
				       rstat.source[res].name,
				       find_name(rstat.source[res].tyfl & 0xff),
				       rstat.source[res].total,
				       strflags(rstat.source[res].tyfl));
		}
		start += rstat.count;
	}

	close(fd);
}

int
main(int argc, char **argv)
{
	rndctl_t  rctl;
	int       ch;
	int       cmd;
	int       lflag;
	int       mflag;
	u_int32_t type;
	char      name[16];

	rctl.mask = 0;
	rctl.flags = 0;

	cmd = 0;
	lflag = 0;
	mflag = 0;
	type = 0xff;

	while ((ch = getopt(argc, argv, "CEcelt:d:")) != -1)
		switch(ch) {
		case 'C':
			rctl.flags |= RND_FLAG_NO_COLLECT;
			rctl.mask |= RND_FLAG_NO_COLLECT;
			mflag++;
			break;
		case 'E':
			rctl.flags |= RND_FLAG_NO_ESTIMATE;
			rctl.mask |= RND_FLAG_NO_ESTIMATE;
			mflag++;
			break;
		case 'c':
			rctl.flags &= ~RND_FLAG_NO_COLLECT;
			rctl.mask |= RND_FLAG_NO_COLLECT;
			mflag++;
			break;
		case 'e':
			rctl.flags &= ~RND_FLAG_NO_ESTIMATE;
			rctl.mask |= RND_FLAG_NO_ESTIMATE;
			mflag++;
			break;
		case 'l':
			lflag++;
			break;
		case 't':
			if (cmd != 0)
				usage();
			cmd = 't';

			type = find_type(optarg);
			break;
		case 'd':
			if (cmd != 0)
				usage();
			cmd = 'd';

			type = 0xff;
			strncpy(name, optarg, 16);
			break;
		case '?':
		default:
			usage();
		}

	/*
	 * cannot list and modify at the same time
	 */
	if (lflag != 0 && mflag != 0)
		usage();

	/*
	 * bomb out on no-ops
	 */
	if (lflag == 0 && mflag == 0)
		usage();

	/*
	 * if not listing, we need a device name or a type
	 */
	if (lflag == 0 && cmd == 0)
		usage();

	/*
	 * modify request
	 */
	if (mflag != 0) {
		rctl.type = type;
		strncpy(rctl.name, name, 16);
		do_ioctl(&rctl);

		exit(0);
	}

	/*
	 * list sources
	 */
	if (lflag != 0)
		do_list(cmd == 0, type, name);

	return 0;
}
