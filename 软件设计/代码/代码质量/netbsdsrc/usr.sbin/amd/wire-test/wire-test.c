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
 * $Id: wire-test.c,v 1.1.1.1 1997/12/22 22:29:11 cgd Exp $
 *
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif /* HAVE_CONFIG_H */
#include <am_defs.h>

#define STRMAX	100

/* dummy variables */
char *progname, hostname[MAXHOSTNAMELEN];
int orig_umask, foreground, debug_flags;
pid_t mypid;
serv_state amd_state;

int
main(int argc, char **argv)
{
  char *networkName1, *networkNumber1;
  char *networkName2, *networkNumber2;
  struct in_addr myipaddr;	/* (An) IP address of this host */
  char *testhost, *proto;
  int nv, ret;
  struct sockaddr_in *ip;
  struct hostent *hp = 0;

  progname = argv[0];
  mypid = getpid();
  orig_umask = umask(0);

  if (gethostname(hostname, MAXHOSTNAMELEN) < 0) {
    perror(argv[0]);
    exit(1);
  }
  if ((networkName1 = (char *) calloc(STRMAX, sizeof(char)))
      == (char *) NULL) {
    perror(argv[0]);
    exit(1);
  }
  if ((networkNumber1 = (char *) calloc(STRMAX, sizeof(char)))
      == (char *) NULL) {
    perror(argv[0]);
    exit(1);
  }
  if ((networkName2 = (char *) calloc(STRMAX, sizeof(char)))
      == (char *) NULL) {
    perror(argv[0]);
    exit(1);
  }
  if ((networkNumber2 = (char *) calloc(STRMAX, sizeof(char)))
      == (char *) NULL) {
    perror(argv[0]);
    exit(1);
  }
  getwire(&networkName1, &networkNumber1, &networkName2, &networkNumber2);
  fprintf(stderr, "Network name is \"%s\"\n", networkName1);
  fprintf(stderr, "Network number is \"%s\"\n", networkNumber1);
  fprintf(stderr, "Network name is \"%s\"\n", networkName2);
  fprintf(stderr, "Network number is \"%s\"\n", networkNumber2);

  /* also print my IP address */
  amu_get_myaddress(&myipaddr);
  fprintf(stderr, "My IP address is 0x%x.\n", (unsigned int) htonl(myipaddr.s_addr));

  /*
   * NFS VERSION/PROTOCOL TESTS:
   * If argv[1] is specified  perform nfs tests to that host, else use
   * localhost.
   */
  if (argc > 1)
    testhost = argv[1];
  else
    testhost = "localhost";
  hp = gethostbyname(testhost);
  if (!hp) {
    fprintf(stderr, "NFS vers/proto failed: no such hostname \"%s\"\n", testhost);
    exit(1);
  }
  ip = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));
  memset((voidp) ip, 0, sizeof(*ip));
  ip->sin_family = AF_INET;
  memmove((voidp) &ip->sin_addr, (voidp) hp->h_addr, sizeof(ip->sin_addr));
  ip->sin_port = htons(NFS_PORT);

  xlog_level = 0;		/* turn off debugging */
  fprintf(stderr, "NFS Version and protocol tests to host \"%s\"...\n", testhost);
  proto = "udp";
  for (nv=2; nv<=3; ++nv) {
    fprintf(stderr, "\ttesting vers=%d, proto=\"%s\" -> ", nv, proto);
    ret = get_nfs_version(testhost, ip, nv, proto);
    if (ret == 0)
      fprintf(stderr, "failed!\n");
    else
      fprintf(stderr, "found version %d.\n", ret);
  }

  proto = "tcp";
  for (nv=2; nv<=3; ++nv) {
    fprintf(stderr, "\ttesting vers=%d, proto=\"%s\" -> ", nv, proto);
    ret = get_nfs_version(testhost, ip, nv, proto);
    if (ret == 0)
      fprintf(stderr, "failed!\n");
    else
      fprintf(stderr, "found version %d.\n", ret);
  }

  exit(0);
  return 0; /* should never reach here */
}
