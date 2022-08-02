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
 * File: faile.c                                  *
 * Purpose: main program.                         *
 **************************************************/

#include "faile.h"
#include "protos.h"

char divider[50] = "-------------------------------------------------";
move_s dummy = {0,0,0,0,0,0,0};

int board[144], moved[144], ep_square, white_to_move, wking_loc,
  bking_loc, white_castled, black_castled, result, ply, pv_length[PV_BUFF],
  history_h[144][144], pieces[33], squares[144], num_pieces, i_depth, fifty,
  fifty_move[PV_BUFF], game_ply;

long int nodes, raw_nodes, qnodes, piece_count, killer_scores[PV_BUFF],
  killer_scores2[PV_BUFF], moves_to_tc, min_per_game, inc, time_left,
  opp_time, time_cushion, time_for_move, cur_score, start_piece_count,
  last_root_score;

bool xb_mode, captures, searching_pv, post, time_exit, time_failure,
  allow_more_time, bad_root_score;

move_s pv[PV_BUFF][PV_BUFF], killer1[PV_BUFF], killer2[PV_BUFF],
 killer3[PV_BUFF];

rtime_t start_time;

d_long h_values[14][144], ep_h_values[144], wck_h_values[2], wcq_h_values[2],
  bck_h_values[2], bcq_h_values[2], color_h_values[2], cur_pos, 
  rep_history[PV_BUFF];

hash_s *hash_table;

unsigned long int hash_mask, hash_max_mb = 0;


int main (int argc, char *argv[]) {

  char input[STR_BUFF], *p, output[STR_BUFF];
  move_s move, comp_move;
  int depth = 4, comp_color;
  bool force_mode, show_board;
  double nps, elapsed;
  clock_t cpu_start = 0, cpu_end = 0;

  parse_cmdline (argc, argv);
  start_up ();
  init_hash_values ();
  init_hash_tables ();
  init_game ();
  init_book ();
  xb_mode = FALSE;
  force_mode = FALSE;
  comp_color = 0;
  show_board = TRUE;
  
  setbuf (stdout, NULL);
  setbuf (stdin, NULL);

  /* keep looping for input, and responding to it: */
  while (TRUE) {

    /* case where it's the computer's turn to move: */
    if (comp_color == white_to_move && !force_mode) {
      nodes = 0;
      qnodes = 0;
      ply = 0;

      start_time = rtime ();
      cpu_start = clock ();
      comp_move = think ();
      cpu_end = clock ();

      /* check for a game end: */
      if (((comp_color == 1 && result != white_is_mated) ||
	  (comp_color == 0 && result != black_is_mated)) &&
	  result != stalemate && result != draw_by_fifty &&
	  result != draw_by_rep) {
	
	comp_to_coord (comp_move, output);

	make (&comp_move, 0);

	/* check to see if we draw by rep/fifty after our move: */
	if (is_draw ()) {
	  result = draw_by_rep;
	}
	else if (fifty > 100) {
	  result = draw_by_fifty;
	}

	reset_piece_square ();
	/* check to see if we mate our opponent with our current move: */
	if (!result) {
	  if (xb_mode) {
	    printf ("move %s\n", output);
	  }
	  else {
	    printf ("\n%s\n", output);
	  }
	}
	else {
	  if (xb_mode) {
	    printf ("move %s\n", output);
	  }
	  else {
	    printf ("\n%s\n", output);
	  }
	  if (result == white_is_mated) {
	    printf ("0-1 {Black Mates}\n");
	  }
	  else if (result == black_is_mated) {
	    printf ("1-0 {White Mates}\n");
	  }
	  else if (result == draw_by_fifty) {
	    printf ("1/2-1/2 {Fifty move rule}\n");
	  }
	  else if (result == draw_by_rep) {
	    printf ("1/2-1/2 {3 fold repetition}\n");
	  }
	  else {
	    printf ("1/2-1/2 {Draw}\n");
	  }
	}
      }
      /* we have been mated or there is a draw: */
      else {
	if (result == white_is_mated) {
	  printf ("0-1 {Black Mates}\n");
	}
	else if (result == black_is_mated) {
	  printf ("1-0 {White Mates}\n");
	}
	else if (result == stalemate) {
	  printf ("1/2-1/2 {Stalemate}\n");
	}
	else if (result == draw_by_fifty) {
	  printf ("1/2-1/2 {Fifty move rule}\n");
	}
	else if (result == draw_by_rep) {
	  printf ("1/2-1/2 {3 fold repetition}\n");
	}
	else {
	  printf ("1/2-1/2 {Draw}\n");
	}
      }

    }

    /* get our input: */
    if (!xb_mode) {
      if (show_board && strcmp (input, "help")) {
	printf ("\n");
	display_board (stdout, 1-comp_color);
      }
      printf ("Faile> ");
      rinput (input, STR_BUFF, stdin);
    }
    else {
      rinput (input, STR_BUFF, stdin);
    }

    /* check to see if we have a move.  If it's legal, play it. */
    if (is_valid_comp (pgn_to_comp (input))) {
      /* good SAN input style move */
      move = pgn_to_comp (input);
      make (&move, 0);
      reset_piece_square ();
      if (show_board) {
	printf ("\n");
	display_board (stdout, 1-comp_color);
      }
    }
    else if (is_move (&input[0])) {
      /* good coordinate style input move */
      if (verify_coord (input, &move)) {
	make (&move, 0);
	reset_piece_square ();
	if (show_board) {
	  printf ("\n");
	  display_board (stdout, 1-comp_color);
	}
      }
      else {
	printf ("Illegal move: %s\n", input);
      }
    }
    else {

      /* make everything lower case for convenience: */
      for (p = input; *p; p++) *p = tolower (*p);

      /* command parsing: */
      if (!strcmp (input, "quit") || !strcmp (input, "exit")) {
	shut_down (EXIT_SUCCESS);
      }
      else if (!strcmp (input, "diagram") || !strcmp (input, "d")) {
	toggle_bool (&show_board);
      }
      else if (!strncmp (input, "perft", 5)) {
	sscanf (input+6, "%d", &depth);
	raw_nodes = 0;
	perft (depth);
	printf ("Raw nodes for depth %d: %ld\n", depth, raw_nodes);
      }
      else if (!strcmp (input, "new")) {
	init_game ();
	/* refresh our hash tables: */
	refresh_hash ();
	force_mode = FALSE;
	comp_color = 0;
      }
      else if (!strcmp (input, "xboard")) {
	xb_mode = TRUE;
	toggle_bool (&show_board);
	signal (SIGINT, SIG_IGN);
	printf ("\n");
      }
      else if (!strcmp (input, "nodes")) {
	printf ("Number of nodes: %li (%0.2f%% qnodes)\n", nodes,
		(float) ((float) qnodes / (float) nodes * 100.0));
      }
      else if (!strcmp (input, "nps")) {
	elapsed = (cpu_end-cpu_start)/(double) CLOCKS_PER_SEC;
	nps = (float) nodes/(float) elapsed;
	if (!elapsed)
	  printf ("NPS: N/A\n");
	else
	  printf ("NPS: %ld\n", (long int) nps);
      }
      else if (!strcmp (input, "post")) {
	toggle_bool (&post);
	if (xb_mode)
	  post = TRUE;
      }
      else if (!strcmp (input, "nopost")) {
	post = FALSE;
      }
      else if (!strcmp (input, "random")) {
	continue;
      }
      else if (!strcmp (input, "hard")) {
	continue;
      }
      else if (!strcmp (input, "easy")) {
	continue;
      }
      else if (!strcmp (input, "?")) {
	continue;
      }
      else if (!strcmp (input, "white")) {
	white_to_move = 1;
	comp_color = 0;
      }
      else if (!strcmp (input, "black")) {
	white_to_move = 0;
	comp_color = 1;
      }
      else if (!strcmp (input, "force")) {
	force_mode = TRUE;
      }
      else if (!strcmp (input, "go")) {
	comp_color = white_to_move;
	force_mode = FALSE;
      }
      else if (!strncmp (input, "time", 4)) {
	sscanf (input+5, "%ld", &time_left);
      }
      else if (!strncmp (input, "otim", 4)) {
	sscanf (input+5, "%ld", &opp_time);
      }
      else if (!strncmp (input, "level", 5)) {
	/* extract the time controls: */
	sscanf (input+6, "%ld %ld %ld", &moves_to_tc, &min_per_game, &inc);
	time_left = min_per_game*6000;
	opp_time = time_left;
	inc *= 100;
      }
      else if (!strncmp (input, "result", 6)) {
	ics_game_end ();
	init_game ();
	force_mode = FALSE;
	comp_color = 0;
      }
      else if (!strcmp (input, "help")) {
	printf ("\n%s\n\n", divider);
	printf ("diagram/d: toggle diagram display\n");
	printf ("exit/quit: terminate Faile\n");
	printf ("go:        make Faile play the side to move\n");
	printf ("new:       start a new game\n");
	printf ("level <x>: the xboard style command to set time\n");
	printf ("  <x> should be in the form: <a> <b> <c> where:\n");
	printf ("  a -> moves to TC (0 if using an ICS style TC)\n");
	printf ("  b -> minutes per game\n");
	printf ("  c -> increment in seconds\n");
	printf ("nodes:     outputs the number of nodes searched\n");
	printf ("nps:       outputs Faile's NPS in search\n");
	printf ("perft <x>: compute raw nodes to depth x\n");
	printf ("post:      toggles thinking output\n");
	printf ("xboard:    put Faile into xboard mode\n");
	printf ("\n%s\n\n", divider);
      }
      else if (!xb_mode) {
	printf ("Illegal move: %s\n", input);
      }

    }

  }

  return 0;

}
