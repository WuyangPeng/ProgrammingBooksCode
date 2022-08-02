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
 * File: search.c                                 *
 * Purpose: contains functions related to the     *
 * recursive search.                              *
 **************************************************/

#include "faile.h"
#include "extvars.h"
#include "protos.h"


void order_moves (move_s moves[], long int move_ordering[], int num_moves,
		  move_s *h_move) {

  /* sort out move ordering scores in move_ordering, using implemented
     heuristics: */

  int cap_values[14] = {
    0,100,100,310,310,0,0,500,500,955,955,325,325,0};
  int i, from, target, promoted, captured;

  /* fill the move ordering array: */

  /* if searching the pv, give it the highest move ordering, and if not, rely
     on the other heuristics: */
  if (searching_pv) {
    searching_pv = FALSE;
    for (i = 0; i < num_moves; i++) {
      from = moves[i].from;
      target = moves[i].target;
      promoted = moves[i].promoted;
      captured = moves[i].captured;
      
      /* give captures precedence in move ordering, and order captures by
	 material gain */
      if (captured != npiece)
	move_ordering[i] = cap_values[captured]-cap_values[board[from]]+1000;
      else
	move_ordering[i] = 0;

      /* make sure the suggested hash move gets ordered high: */
      if (from == h_move->from && target == h_move->target
	  && promoted == h_move->promoted) {
	move_ordering[i] += INF-10000;
      }

      /* make the pv have highest move ordering: */
      if (from == pv[1][ply].from && target == pv[1][ply].target
	  && promoted == pv[1][ply].promoted) {
	searching_pv = TRUE;
	move_ordering[i] += INF;
      }

      /* heuristics other than pv (no need to use them on the pv move - it is
	 already ordered highest) */
      else {
	/* add the history heuristic bonus: */
	move_ordering[i] += (history_h[from][target]>>i_depth);

	/* add the killer move heuristic bonuses: */
	if (from == killer1[ply].from && target == killer1[ply].target
	    && promoted == killer1[ply].promoted)
	  move_ordering[i] += 1000;
	else if (from == killer2[ply].from && target == killer2[ply].target
	    && promoted == killer2[ply].promoted)
	  move_ordering[i] += 500;
	else if (from == killer3[ply].from && target == killer3[ply].target
	    && promoted == killer3[ply].promoted)
	  move_ordering[i] += 250;
      }
    }
  }

  /* if not searching the pv: */
  else {
    for (i = 0; i < num_moves; i++) {
      from = moves[i].from;
      target = moves[i].target;
      promoted = moves[i].promoted;
      captured = moves[i].captured;
      
      /* give captures precedence in move ordering, and order captures by
	 material gain */
      if (captured != npiece)
	move_ordering[i] = cap_values[captured]-cap_values[board[from]]+1000;
      else
	move_ordering[i] = 0;

      /* make sure the suggested hash move gets ordered first: */
      if (from == h_move->from && target == h_move->target
	  && promoted == h_move->promoted) {
	move_ordering[i] += INF+1000;
      }

      /* heuristics other than pv */
      
      /* add the history heuristic bonus: */
      move_ordering[i] += (history_h[from][target]>>i_depth);

      /* add the killer move heuristic bonuses: */
      if (from == killer1[ply].from && target == killer1[ply].target
	  && promoted == killer1[ply].promoted)
	move_ordering[i] += 1000;
      else if (from == killer2[ply].from && target == killer2[ply].target
	  && promoted == killer2[ply].promoted)
	move_ordering[i] += 500;
      else if (from == killer3[ply].from && target == killer3[ply].target
	  && promoted == killer3[ply].promoted)
	move_ordering[i] += 250;
    }
  }

}


void perft (int depth) {

  move_s moves[MOVE_BUFF];
  int num_moves, i, ep_temp;
  d_long temp_hash = cur_pos;

  ep_temp = ep_square;
  num_moves = 0;

  /* return if we are at the maximum depth: */
  if (!depth) {
    return;
  }

  /* generate the move list: */
  gen (&moves[0], &num_moves);

  /* loop through the moves at the current depth: */
  for (i = 0; i < num_moves; i++) {
    make (&moves[0], i);

    /* check to see if our move is legal: */
    if (check_legal (&moves[0], i)) {
      raw_nodes++;
      /* go deeper into the tree recursively, increasing the indent to
	 create the "tree" effect: */
      perft (depth-1);
    }

    /* unmake the move to go onto the next: */
    unmake (&moves[0], i);
    cur_pos = temp_hash;
    ep_square = ep_temp;
  }

}


long int qsearch (int alpha, int beta, int depth) {

  /* perform a quiscense search on the current node using alpha-beta with
     negamax search */

  move_s moves[MOVE_BUFF];
  int num_moves, i, j, ep_temp;
  long int score = -INF, standpat, move_ordering[MOVE_BUFF];
  bool legal_move, no_moves;
  d_long temp_hash;

  /* return our score if we're at a leaf node: */
  if (!depth) {
    score = eval ();
    return score;
  }

  pv_length[ply] = ply;
  temp_hash = cur_pos;
  ep_temp = ep_square;

  /* see if our position's score is good enough that we can exit early: */
  standpat = eval ();
  if (standpat >= beta) {
    return standpat;
  }
  else if (standpat > alpha) {
    alpha = standpat;
  }

  num_moves = 0;
  no_moves = TRUE;

  /* generate and order moves: */
  gen (&moves[0], &num_moves);
  order_moves (&moves[0], &move_ordering[0], num_moves, &dummy);

  /* loop through the moves at the current node: */
  while (remove_one (&i, &move_ordering[0], num_moves)) {

    make (&moves[0], i);
    assert (cur_pos.x1 == compute_hash ().x1 &&
	    cur_pos.x2 == compute_hash ().x2);
    ply++;
    legal_move = FALSE;

    /* go deeper if it's a legal move: */
    if (check_legal (&moves[0], i)) {
      nodes++;
      qnodes++;
      score = -qsearch (-beta, -alpha, depth-1);
      no_moves = FALSE;
      legal_move = TRUE;
    }

    ply--;
    unmake (&moves[0], i);
    ep_square = ep_temp;
    cur_pos = temp_hash;

    /* check our current score vs. alpha: */
    if (score > alpha && legal_move) {

      /* don't update the history heuristic scores here, since depth is messed
	 up when qsearch is called */
      
      /* try for an early cutoff: */
      if (score >= beta) {
	u_killers (moves[i], score);
	return beta;
      }
      alpha = score;

      /* update the pv: */
      pv[ply][ply] = moves[i];
      for (j = ply+1; j < pv_length[ply+1]; j++)
	pv[ply][j] = pv[ply+1][j];
      pv_length[ply] = pv_length[ply+1];
    }

  }

  /* We don't check for mate / stalemate here, because without generating all
     of the moves leading up to it, we don't know if the position could have
     been avoided by one side or not.  So if we have found no moves,
     simply return our evaluation: */
  if (no_moves) {
    return (standpat);
  }

  return alpha;

}


bool remove_one (int *marker, long int move_ordering[], int num_moves) {

  /* a function to give pick the top move order, one at a time on each call.
     Will return TRUE while there are still moves left, FALSE after all moves
     have been used */

  int i, best = -1;

  *marker = -1;

  for (i = 0; i < num_moves; i++) {
    if (move_ordering[i] > best) {
      *marker = i;
      best = move_ordering[i];
    }
  }

  if (*marker > -1) {
    move_ordering[*marker] = -1;
    return TRUE;
  }
  else {
    return FALSE;
  }

}


long int search (int alpha, int beta, int depth, bool do_null) {

  /* search the current node using alpha-beta with negamax search */

  move_s moves[MOVE_BUFF], h_move;
  int num_moves, i, j, ep_temp, extensions = 0, h_type;
  long int score = -INF, move_ordering[MOVE_BUFF], null_score = -INF, i_alpha,
    h_score;
  bool no_moves, legal_move;
  d_long temp_hash;

  /* before we do anything, see if we're out of time or we have input: */
  if (i_depth > mindepth && !(nodes & 4095)) {
    if (rdifftime (rtime (), start_time) >= time_for_move) {
      /* see if our score has suddenly dropped, and if so, try to allocate
	 some extra time: */
      if (allow_more_time && bad_root_score) {
	allow_more_time = FALSE;
	if (time_left > (5*time_for_move)) {
	  time_for_move *= 2;
	}
	else {
	  time_exit = TRUE;
	  return 0;
	}
      }
      else {
	time_exit = TRUE;
	return 0;
      }
    }
    #ifndef ANSI
    if (xb_mode && bioskey ()) {
      time_exit = TRUE;
      return 0;
    }
    #endif
  }

  /* check for a draw by repetition before continuing: */
  if (is_draw ()) {
    return 0;
  }

  pv_length[ply] = ply;

  /* see what info we can get from our hash table: */
  h_score = chk_hash (alpha, beta, depth, &h_type, &h_move);
  if (h_type != no_info) {
    switch (h_type) {
      case exact:
	return (h_score);
      case u_bound:
	return (h_score);
      case l_bound:
	return (h_score);
      case avoid_null:
	do_null = FALSE;
	break;
      default:
	break;
    }
  }

  temp_hash = cur_pos;
  ep_temp = ep_square;
  i_alpha = alpha;

  /* perform check extensions if we haven't gone past maxdepth: */
  if (in_check ()) {
    if (ply < maxdepth+1) extensions++;
  }
  /* if not in check, look into null moves: */
  else {
    /* conditions for null move:
       - not in check
       - we didn't just make a null move
       - we don't have a risk of zugzwang by being in the endgame
       - depth is >= R + 1
       what we do after null move:
       - if score is close to -mated, we're in danger, increase depth
       - if score is >= beta, we can get an early cutoff and exit */
    if (do_null && null_red && piece_count >= 5 && depth >= null_red+1) {
      /* update the rep_history just so things don't get funky: */
      rep_history[game_ply++] = cur_pos;
      fifty++;

      xor (&cur_pos, color_h_values[0]);
      xor (&cur_pos, color_h_values[1]);
      xor (&cur_pos, ep_h_values[ep_square]);
      xor (&cur_pos, ep_h_values[0]);

      white_to_move ^= 1;
      ply++;
      ep_square = 0;
      null_score = -search (-beta, -beta+1, depth-null_red-1, FALSE);
      ep_square = ep_temp;
      ply--;
      white_to_move ^= 1;

      game_ply--;
      fifty--;

      xor (&cur_pos, color_h_values[0]);
      xor (&cur_pos, color_h_values[1]);
      xor (&cur_pos, ep_h_values[ep_square]);
      xor (&cur_pos, ep_h_values[0]);
      assert (cur_pos.x1 == compute_hash ().x1 &&
	      cur_pos.x2 == compute_hash ().x2);

      /* check to see if we ran out of time: */
      if (time_exit)
	return 0;

      /* check to see if we can get a quick cutoff from our null move: */
      if (null_score >= beta)
	return beta;
      
      if (null_score < -INF+10*maxdepth)
	extensions++;
    }
  }

  /* try to find a stable position before passing the position to eval (): */
  if (!(depth+extensions)) {
    captures = TRUE;
    score = qsearch (alpha, beta, maxdepth);
    captures = FALSE;
    return score;
  }

  num_moves = 0;
  no_moves = TRUE;

  /* generate and order moves: */
  gen (&moves[0], &num_moves);
  order_moves (&moves[0], &move_ordering[0], num_moves, &h_move);

  /* loop through the moves at the current node: */
  while (remove_one (&i, &move_ordering[0], num_moves)) {

    make (&moves[0], i);
    assert (cur_pos.x1 == compute_hash ().x1 &&
	    cur_pos.x2 == compute_hash ().x2);
    ply++;
    legal_move = FALSE;

    /* go deeper if it's a legal move: */
    if (check_legal (&moves[0], i)) {
      nodes++;
      score = -search (-beta, -alpha, depth-1+extensions, TRUE);
      no_moves = FALSE;
      legal_move = TRUE;
    }

    ply--;
    unmake (&moves[0], i);
    ep_square = ep_temp;
    cur_pos = temp_hash;

    /* return if we've run out of time: */
    if (time_exit) return 0;

    /* check our current score vs. alpha: */
    if (score > alpha && legal_move) {
      
      /* update the history heuristic since we have a cutoff: */
      history_h[moves[i].from][moves[i].target] += depth;

      /* try for an early cutoff: */
      if (score >= beta) {
	u_killers (moves[i], score);
	store_hash (i_alpha, depth, score, l_bound, moves[i]);
	return beta;
      }
      alpha = score;

      /* update the pv: */
      pv[ply][ply] = moves[i];
      for (j = ply+1; j < pv_length[ply+1]; j++)
	pv[ply][j] = pv[ply+1][j];
      pv_length[ply] = pv_length[ply+1];
    }

  }

  /* check for mate / stalemate: */
  if (no_moves) {
    if (in_check ()) {
      alpha = -INF+ply;
    }
    else {
      alpha = 0;
    }
  }
  else {
    /* check the 50 move rule if no mate situation is on the board: */
    if (fifty > 100) {
      return 0;
    }
  }

  /* store our hash info: */
  if (alpha > i_alpha)
    store_hash (i_alpha, depth, alpha, exact, pv[ply][ply]);
  else
    store_hash (i_alpha, depth, alpha, u_bound, dummy);

  return alpha;

}


move_s search_root (int alpha, int beta, int depth) {

  /* search the root node using alpha-beta with negamax search */

  move_s moves[MOVE_BUFF], best_move = dummy, h_move;
  int num_moves, i, j, ep_temp, extensions = 0, h_type;
  long int root_score = -INF, move_ordering[MOVE_BUFF], i_alpha = -INF;
  bool no_moves, legal_move;
  d_long temp_hash;

  ply = 1;

  /* check for a draw by 3 fold repetition: */
  if (is_draw ()) {
    result = draw_by_rep;
    cur_score = 0;
    pv_length[ply] = 0;
    return (dummy);
  }

  num_moves = 0;
  no_moves = TRUE;
  searching_pv = TRUE;
  time_exit = FALSE;
  time_failure = FALSE;
  start_piece_count = piece_count;
  bad_root_score = FALSE;
  
  pv_length[ply] = ply;
  ep_temp = ep_square;
  temp_hash = cur_pos;
  
  /* don't use hashing for returning moves from the root, but at least
     use it for some move ordering: */
  chk_hash (alpha, beta, depth, &h_type, &h_move);

  /* check extensions: */
  if (in_check ()) extensions++;

  /* generate and order moves: */
  gen (&moves[0], &num_moves);
  order_moves (&moves[0], &move_ordering[0], num_moves, &h_move);

  /* loop through the moves at the root: */
  while (remove_one (&i, &move_ordering[0], num_moves)) {
    make (&moves[0], i);
    assert (cur_pos.x1 == compute_hash ().x1 &&
	    cur_pos.x2 == compute_hash ().x2);
    ply++;
    legal_move = FALSE;

    /* go deeper if it's a legal move: */
    if (check_legal (&moves[0], i)) {
      nodes++;
      root_score = -search (-beta, -alpha, depth-1+extensions, TRUE);

      /* check to see if we've aborted this search before we found a move: */
      if (time_exit && no_moves)
	time_failure = TRUE;

      no_moves = FALSE;
      legal_move = TRUE;
    }

    ply--;
    unmake (&moves[0], i);
    ep_square = ep_temp;
    cur_pos = temp_hash;

    /* if we've run out of time, return the best we have so far: */
    if (time_exit)
      return best_move;

    /* check our current score vs. alpha: */
    if (root_score > alpha && legal_move) {

      u_killers (moves[i], root_score);

      /* update the history heuristic since we have a cutoff: */
      history_h[moves[i].from][moves[i].target] += depth;

      alpha = root_score;
      best_move = moves[i];
      cur_score = alpha;

      /* see if our root score has dropped a lot: */
      if ((cur_score+40) < last_root_score) {
	bad_root_score = TRUE;
      }

      /* update the hash tables: */
      store_hash (i_alpha, depth, alpha, exact, best_move);
      
      /* update the pv: */
      pv[ply][ply] = moves[i];
      for (j = ply+1; j < pv_length[ply+1]; j++)
	pv[ply][j] = pv[ply+1][j];
      pv_length[ply] = pv_length[ply+1];

      /* print out thinking information: */
      if (post && i_depth >= mindepth) {
	post_thinking (alpha);
      }
    }

  }

  /* check to see if we are mated / stalemated: */
  if (no_moves) {
    if (in_check ()) {
      if (white_to_move == 1) {
	result = white_is_mated;
      }
      else {
	result = black_is_mated;
      }
    }
    else {
      result = stalemate;
    }
  }
  else {
    /* check for draw by the 50 move rule: */
    if (fifty > 100) {
      result = draw_by_fifty;
      cur_score = 0;
      pv_length[ply] = 0;
      return (dummy);
    }
  }

  /* check to see if we have mated our opponent: */
  if (root_score == INF-2) {
    if (white_to_move == 1) {
      result = black_is_mated;
    }
    else {
      result = white_is_mated;
    }
  }

  return best_move;

}


move_s think (void) {

  /* Perform iterative deepening to go further in the search */
  
  move_s comp_move, temp_move;
  int ep_temp, i, j;
  long int elapsed;

  /* see if we can get a book move: */
  comp_move = book_move ();
  if (is_valid_comp (comp_move)) {
    /* print out a pv line indicating a book move: */
    printf ("0 0 0 0 (Book move)\n");
    return (comp_move);
  }

  nodes = 0;
  qnodes = 0;
  allow_more_time = TRUE;

  /* allocate our time for this move: */
  time_for_move = allocate_time ();

  /* clear the pv before a new search: */
  for (i = 0; i < PV_BUFF; i++)
    for (j = 0; j < PV_BUFF; j++)
      pv[i][j] = dummy;

  /* clear the history heuristic: */
  memset (history_h, 0, sizeof (history_h));

  /* clear the killer moves: */
  for (i = 0; i < PV_BUFF; i++) {
    killer_scores[i] = -INF;
    killer_scores2[i] = -INF;
    killer1[i] = dummy;
    killer2[i] = dummy;
    killer3[i] = dummy;
  }

  for (i_depth = 1; i_depth <= maxdepth; i_depth++) {
    /* don't bother going deeper if we've already used 2/3 of our time, and we
       have finished our mindepth search, since we likely won't finish */
    elapsed = rdifftime (rtime (), start_time);
    if (elapsed > time_for_move*2.0/3.0 && i_depth > mindepth)
      break;

    ep_temp = ep_square;
    temp_move = search_root (-INF, INF, i_depth);
    ep_square = ep_temp;

    /* if we haven't aborted our search on time, set the computer's move
       and post our thinking: */
    if (!time_failure) {
      /* if our search score suddenly drops, and we ran out of time on the
	 search, just use previous results */
      comp_move = temp_move;
      last_root_score = cur_score;
      /* if our PV is really short, try to get some of it from hash info
	 (don't modify this if it is a mate / draw though): */
      if (pv_length[1] <= 2 && i_depth > 1 && abs (cur_score) < (INF-100) &&
	  result != stalemate && result != draw_by_fifty &&
	  result != draw_by_rep)
	hash_to_pv (i_depth);
      if (post && i_depth >= mindepth)
	post_thinking (cur_score);
    }

    /* reset the killer scores (we can keep the moves for move ordering for
       now, but the scores may not be accurate at higher depths, so we need
       to reset them): */
    for (j = 0; j < PV_BUFF; j++) {
      killer_scores[j] = -INF;
      killer_scores2[j] = -INF;
    }

  }

  /* update our elapsed time_cushion: */
  if (moves_to_tc) {
    elapsed = rdifftime (rtime (), start_time);
    time_cushion += time_for_move-elapsed+inc;
  }

  return comp_move;

}


void tree (int depth, int indent, FILE *output, char *disp_b) {

  move_s moves[MOVE_BUFF];
  int num_moves, i, j, ep_temp;
  d_long temp_hash = cur_pos;

  ep_temp = ep_square;
  num_moves = 0;

  /* return if we are at the maximum depth: */
  if (!depth) {
    return;
  }

  /* generate the move list: */
  gen (&moves[0], &num_moves);

  /* loop through the moves at the current depth: */
  for (i = 0; i < num_moves; i++) {
    make (&moves[0], i);

    /* check to see if our move is legal: */
    if (check_legal (&moves[0], i)) {
      /* indent and print out our line: */
      for (j = 0; j < indent; j++) {
	fputc (' ', output);
      }
      print_move (&moves[0], i, output);
      fprintf (output, "\n");

      /* display board if desired: */
      if (disp_b[0] == 'y')
	display_board (output, 1);

      /* go deeper into the tree recursively, increasing the indent to
	 create the "tree" effect: */
      tree (depth-1, indent+2, output, disp_b);
    }

    /* unmake the move to go onto the next: */
    unmake(&moves[0], i);
    cur_pos = temp_hash;
    ep_square = ep_temp;
  }

}


void u_killers (move_s move, long int score) {

  /* we have a cutoff, so update our killers: */

  if (score > killer_scores[ply]) {
    killer_scores2[ply] = killer_scores[ply];
    killer_scores[ply] = score;
    killer3[ply] = killer2[ply];
    killer2[ply] = killer1[ply];
    killer1[ply] = move;
  }
  else if (score > killer_scores2[ply]) {
    killer_scores2[ply] = score;
    killer3[ply] = killer2[ply];
    killer2[ply] = move;
  }

}
