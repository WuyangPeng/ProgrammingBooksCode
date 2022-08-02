/*	$NetBSD: parse_conf.h,v 1.2 1998/01/09 06:06:18 perry Exp $	*/

/*
 * /src/NTP/REPOSITORY/v4/include/parse_conf.h,v 3.8 1996/12/01 16:02:47 kardel Exp
 *
 * parse_conf.h,v 3.8 1996/12/01 16:02:47 kardel Exp
 *
 * Copyright (c) 1993,1994,1995,1996 by Frank Kardel
 * Friedrich-Alexander Universit�t Erlangen-N�rnberg, Germany
 *                                    
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

#ifndef __PARSE_CONF_H__
#define __PARSE_CONF_H__
#if	!(defined(lint) || defined(__GNUC__))
  static char dcfhrcsid[]="parse_conf.h,v 3.8 1996/12/01 16:02:47 kardel Exp";
#endif

/*
 * field location structure (Meinberg clocks/simple format)
 */
#define O_DAY	0
#define O_MONTH 1
#define O_YEAR	2
#define O_HOUR	3
#define O_MIN	4
#define	O_SEC	5
#define O_WDAY	6
#define O_FLAGS 7
#define O_ZONE  8
#define O_UTCHOFFSET 9
#define O_UTCMOFFSET 10
#define O_UTCSOFFSET 11
#define O_COUNT (O_UTCSOFFSET+1)

#define MBG_EXTENDED	0x00000001

/*
 * see below for field offsets
 */

struct format
{
  struct foff
    {
      char offset;		/* offset into buffer */
      char length;		/* length of field */
    } field_offsets[O_COUNT];
  char *fixed_string;		/* string with must be chars (blanks = wildcards) */
  u_long flags;
};
#endif
