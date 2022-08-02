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
 * File: hash.c                                   *
 * Purpose: contains functions needed for hashing *
 **************************************************/

#include "faile.h"
#include "extvars.h"
#include "protos.h"
#include "rand.h"


d_long compute_hash (void) {

  /* compute and return the initial hash value for the position */

  d_long this_pos = {0, 0};
  int i, square;

  /* loop through the board, adding up piece values: */
  for (i = 1; i <= num_pieces; i++) {
    square = pieces[i];
    if (square)
      xor (&this_pos, h_values[board[square]][square]);
  }

  /* add the ep hash value: */
  xor (&this_pos, ep_h_values[ep_square]);

  /* add the castling hash values: */
  xor (&this_pos, wck_h_values[!moved[30] && !moved[33]]);
  xor (&this_pos, wcq_h_values[!moved[30] && !moved[26]]);
  xor (&this_pos, bck_h_values[!moved[114] && !moved[117]]);
  xor (&this_pos, bcq_h_values[!moved[114] && !moved[110]]);

  /* add the hash value for side to move: */
  xor (&this_pos, color_h_values[white_to_move]);

  return (this_pos);

}


void hash_to_pv (int depth) {

  /* try to extract the PV from hash info */

  hash_s *hash_p;
  d_long temp_hash, hash;
  int ep_temp;
  move_s move, ign_me;
  char str_move[6];

  if (!depth)
    return;

  /* lookup our hash: */
  hash_p = hash_table + (hash_mask & cur_pos.x1);
  hash = hash_p->hash;
  if (hash.x1 == cur_pos.x1 && hash.x2 == cur_pos.x2) {
    move = hash_p->move;
    comp_to_coord (move, str_move);
    if (verify_coord (str_move, &ign_me)) {
      pv[1][i_depth-depth+1] = move;
      pv_length[1] = i_depth-depth+2;
      temp_hash = cur_pos;
      ep_temp = ep_square;
      make (&move, 0);
      ply++;
      if (check_legal (&move, 0)) {
	hash_to_pv (depth-1);
      }
      ply--;
      unmake (&move, 0);
      ep_square = ep_temp;
      cur_pos = temp_hash;
    }
  }

}


void init_hash_tables (void) {

  /* this function allocates space for the hash tables, as well as setting
     some necessary values for storing hashes */

  int i = 1;
  unsigned long int max_hash = 1, element_size = sizeof (hash_s);

  /* see if user specified a hash size, otherwise use default: */
  if (!hash_max_mb)
    hash_max_mb = HASH_MB;

  /* compute the maximum hash element, based upon size desired: */
  while (max_hash * element_size <= hash_max_mb<<19) {
    max_hash = 1 << i++;
  }

  /* compute the hash mask, for computing hash table indices: */
  hash_mask = max_hash-1;

  /* allocate our hash table's memory, and report on the allocation: */
  if ((hash_table = malloc (max_hash*element_size)) == NULL) {
    fprintf (stderr, "Couldn't allocate memory for hash tables!\n");
    shut_down (EXIT_FAILURE);
  }
  printf ("\nMemory Allocation:\n");
  printf ("%lu hash entries * %lu bytes/entry = %lu kb of RAM\n",
	  max_hash, element_size, (max_hash*element_size)>>10);

  /* clear our hash tables of possible errant values: */
  memset (hash_table, 0, max_hash*element_size);

}


void init_hash_values (void) {

  /* this function sets the hash value tables for the various pieces, as well
     as values for castling rights, en passant, and side to move */

  int i, j;

  /* set frame and npiece values to 0: */
  for (j = 0; j < 144; j++) {
    h_values[0][j].x1 = 0;
    h_values[0][j].x2 = 0;
    h_values[13][j].x1 = 0;
    h_values[13][j].x2 = 0;
  }

  /* set the hash values for the pieces: */
  for (i = 1; i <= 12; i++) {
    for (j = 0; j < 144; j++) {
      h_values[i][j].x1 = rand_32 ();
      h_values[i][j].x2 = rand_32 ();
    }
  }

  /* set the ep hash values: */
  ep_h_values[0].x1 = 0;
  ep_h_values[0].x2 = 0;
  for (j = 1; j < 144; j++) {
    ep_h_values[j].x1 = rand_32 ();
    ep_h_values[j].x2 = rand_32 ();
  }

  /* set the castling hash values: */
  for (j = 0; j <= 1; j++) {
    wck_h_values[j].x1 = rand_32 ();
    wck_h_values[j].x2 = rand_32 ();
    wcq_h_values[j].x1 = rand_32 ();
    wcq_h_values[j].x2 = rand_32 ();
    bck_h_values[j].x1 = rand_32 ();
    bck_h_values[j].x2 = rand_32 ();
    bcq_h_values[j].x1 = rand_32 ();
    bcq_h_values[j].x2 = rand_32 ();
  }

  /* set the hash values for side to move: */
  color_h_values[0].x1 = rand_32 ();
  color_h_values[0].x2 = rand_32 ();
  color_h_values[1].x1 = rand_32 ();
  color_h_values[1].x2 = rand_32 ();

}


long int chk_hash (int alpha, int beta, int depth, int *type, move_s *move) {

  /* see what info we can get from our hash tables for the current
     position.  This could be a value we can return, a suggested move, or
     even just a warning not to use null search in this position */

  hash_s *hash_p;
  long int score;
  s_int h_depth, flag;
  d_long hash;

  *type = no_info;
  *move = dummy;

  /* lookup our hash: */
  hash_p = hash_table + (hash_mask & cur_pos.x1);
  hash = hash_p->hash;
  if (hash.x1 == cur_pos.x1 && hash.x2 == cur_pos.x2) {
    /* get info from the hash: */
    *move = hash_p->move;
    score = hash_p->score;
    h_depth = hash_p->depth;
    flag = hash_p->flag;

    /* adjust our score if it is a mate score: */
    if (abs (score) > INF-100) {
      if (score > 0)
	score -= (ply);
      else
	score += (ply);
    }

    /* see if we should avoid null moves: */
    if (h_depth >= depth-null_red && score < beta && flag == u_bound)
      *type = avoid_null;

    /* check what info we can get from our hash: */
    if (h_depth >= depth) {
      switch (flag) {
        case u_bound:
	  if (score <= alpha) {
	    *type = u_bound;
	    return (alpha);
	  }
	  break;
        case l_bound:
	  if (score >= beta) {
	    *type = l_bound;
	    return (beta);
	  }
	  break;
        case exact:
	  *type = exact;
	  return (score);
	  break;
      }
    }
  }

  return (0);

}


void refresh_hash (void) {

  /* reset the depths on the hash table to 0 for every game, so that old hash
     entries don't keep new ones from being added in the next game: */

  unsigned long int i;

  for (i = 0; i <= hash_mask; i++) {
    hash_table[i].depth = 0;
  }

}


void store_hash (int alpha, int depth, int score, int flag, move_s move) {

  /* store a position into the hash table: */

  hash_s *hash_p;

  /* look for the correct place to put the hash: */
  hash_p = hash_table + (hash_mask & cur_pos.x1);

  /* don't replace if the info in the hash table is more accurate than
     what we have now: */
  if (depth < hash_p->depth) {
    return;
  }

  /* adjust for mate scores: */
  if (abs (score) > INF-100) {
    if (score > 0)
      score += (ply);
    else
      score -= (ply);
  }

  /* store our hash info: */
  hash_p->hash = cur_pos;
  hash_p->depth = depth;
  hash_p->score = score;
  hash_p->move = move;
  hash_p->flag = flag;

}


void xor (d_long *a, d_long b) {

  /* xor two d_long values: */

  a->x1 ^= b.x1;
  a->x2 ^= b.x2;

}
