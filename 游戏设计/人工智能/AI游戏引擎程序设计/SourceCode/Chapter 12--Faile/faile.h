/*
MIT License

Copyright (c) 2000 Adrien M. Regimbald

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
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/**************************************************
 * Faile version 1.4                              *
 * Author: Adrien Regimbald                       *
 * E-mail: adrien@ee.ualberta.ca                  *
 * Web Page: http://www.ee.ualberta.ca/~adrien/   *
 *                                                *
 * File: faile.h                                  *
 * Purpose: holds defines & typedefs for various  *
 * parts of the program.                          *
 **************************************************/

#ifndef FAILE_H
#define FAILE_H

/* #define ANSI */

#include <ctype.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#ifndef ANSI

#include <sys/types.h>
#include <sys/timeb.h>

#ifndef WIN32
#include <sys/time.h>
struct timeval tv;
#endif

#endif

#define NDEBUG
#include <assert.h>

#define maxdepth 30
#define mindepth 3
#define null_red 2
#define FALSE 0
#define TRUE 1

/* define names for piece constants: */
#define frame   0
#define wpawn   1
#define bpawn   2
#define wknight 3
#define bknight 4
#define wking   5
#define bking   6
#define wrook   7
#define brook   8
#define wqueen  9
#define bqueen  10
#define wbishop 11
#define bbishop 12
#define npiece  13

/* castle flags: */
#define no_castle  0
#define wck        1
#define wcq        2
#define bck        3
#define bcq        4

/* result flags: */
#define no_result      0
#define stalemate      1
#define white_is_mated 2
#define black_is_mated 3
#define draw_by_fifty  4
#define draw_by_rep    5

/* hash flags: */
#define no_info    0
#define avoid_null 1
#define exact      2
#define u_bound    3
#define l_bound    4

#define rank(square) ((((square)-26)/12)+1)
#define file(square) ((((square)-26)%12)+1)

typedef unsigned char s_int;
typedef s_int bool;

typedef struct {
  bool ep;
  s_int from;
  s_int target;
  s_int captured;
  s_int promoted;
  s_int castled;
  s_int cap_num;
} move_s;

typedef struct {
  unsigned long int x1;
  unsigned long int x2;
} d_long;

typedef struct {
  d_long hash;
  s_int depth;
  long int score;
  move_s move;
  s_int flag;
} hash_s;

typedef enum {p_none, p_pawn, p_K, p_Q, p_R, p_N, p_B} piece_t;

#ifndef ANSI
typedef struct timeb rtime_t;
#else
typedef time_t rtime_t;
#endif

#define STR_BUFF 256
#define MOVE_BUFF 200
#define INF 1000000
#define PV_BUFF 1000
#define HASH_MB 8
#define MAX_B_PLY 40

#endif

