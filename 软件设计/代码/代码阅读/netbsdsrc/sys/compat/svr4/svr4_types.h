/*	$NetBSD: svr4_types.h,v 1.8.6.1 1997/11/17 02:28:22 thorpej Exp $	 */

/*
 * Copyright (c) 1994 Christos Zoulas
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
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef	_SVR4_TYPES_H_
#define	_SVR4_TYPES_H_

typedef u_quad_t	 svr4_ino64_t;
typedef quad_t		 svr4_off64_t;
typedef quad_t		 svr4_blkcnt64_t;
typedef u_quad_t	 svr4_fsblkcnt64_t;

typedef long  		 svr4_off_t;
typedef u_long		 svr4_dev_t;
typedef u_long		 svr4_ino_t;
typedef u_long		 svr4_mode_t;
typedef u_long		 svr4_nlink_t;
typedef long		 svr4_uid_t;
typedef long		 svr4_gid_t;
typedef long		 svr4_daddr_t;
typedef long		 svr4_pid_t;
typedef long		 svr4_time_t;
typedef long		 svr4_blkcnt_t;
typedef u_long		 svr4_fsblkcnt_t;
typedef char		*svr4_caddr_t;
typedef u_int		 svr4_size_t;

typedef short		 svr4_o_dev_t;
typedef short		 svr4_o_pid_t;
typedef u_short		 svr4_o_ino_t;
typedef u_short		 svr4_o_mode_t;
typedef short		 svr4_o_nlink_t;
typedef u_short		 svr4_o_uid_t;
typedef u_short		 svr4_o_gid_t;
typedef long		 svr4_clock_t;
typedef int		 svr4_key_t;

typedef struct timespec  svr4_timestruc_t;

#define svr4_to_bsd_odev_t(d) makedev((((d) & 0x7f00) >> 8), ((d) & 0xff))
/* XXX: we limit the minor number to 0xff, instead of 0x3ffff */
#define svr4_to_bsd_dev_t(d) makedev((((d) & 0xfffc0000) >> 18), ((d) & 0xff))

#define bsd_to_svr4_odev_t(d) (((major(d) & 0x7f) << 8)|(minor(d) & 0xff))
#define bsd_to_svr4_dev_t(d) (((major(d) & 0x3fff) << 18)|(minor(d) & 0x3ffff))


#endif /* !_SVR4_TYPES_H_ */
