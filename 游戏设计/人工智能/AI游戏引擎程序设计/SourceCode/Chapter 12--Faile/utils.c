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
 * File: utils.c                                  *
 * Purpose: misc. functions used throughout the   *
 * program.                                       *
 **************************************************/

#include "faile.h"
#include "extvars.h"
#include "protos.h"


long int allocate_time (void) {

  /* calculate the ammount of time the program can use in its search, measured
     in centi-seconds (calculate everything in float for more accuracy as
     we go, and return the result as a long int) */

  float allocated_time = 0.0, move_speed = 30.0;

  /* sudden death time allocation: */
  if (!moves_to_tc) {
    /* calculate move speed.  The idea is that if we are behind, we move
       faster, and if we have < 1 min left and a small increment, we REALLY
       need to start moving fast.  Also, if we aren't in a super fast
       game, don't worry about being behind on the clock at the beginning,
       because some players will make instant moves in the opening, and Faile
       will play poorly if it tries to do the same. */

    /* check to see if we're behind on time and need to speed up: */
    if ((min_per_game < 6 && !inc) || time_left < min_per_game*6000*4.0/5.0) {
      if ((opp_time-time_left) > (opp_time/5.0) && xb_mode)
	move_speed = 50.0;
      else if ((opp_time-time_left) > (opp_time/10.0) && xb_mode)
	move_speed = 40.0;
      else if ((opp_time-time_left) > (opp_time/20.0) && xb_mode)
	move_speed = 35.0;
    }

    /* see if we are ahead of time and can afford to slow down a bit: */
    if ((time_left-opp_time) > (time_left/5.0) && xb_mode)
      move_speed -= 15;
    else if ((time_left-opp_time) > (time_left/10.0) && xb_mode)
      move_speed -= 10;
    else if ((time_left-opp_time) > (time_left/20.0) && xb_mode)
      move_speed -= 5;

    /* check to see if we need to move REALLY fast: */
    if (time_left <= 6000 && inc < 300)
      move_speed += 30.0;

    /* allocate our base time: */
    allocated_time = time_left/move_speed;

    /* add our increment if applicable: */
    if (inc) {
      if (time_left-allocated_time-inc > 500) {
	allocated_time += inc;
      }
      else if (time_left-allocated_time-(inc*2.0/3.0) > 100) {
	allocated_time += inc*2.0/3.0;
      }
    }

  }
  
  /* conventional clock time allocation: */
  else {
    allocated_time = (float) min_per_game/moves_to_tc*6000 - 100;
    /* if we've got extra time, use some of it: */
    if (time_cushion) {
      allocated_time += time_cushion*2.0/3.0;
      time_cushion -= time_cushion*2.0/3.0;
    }
  }

  return ((long int) allocated_time);

}


/* The following code is used to check for input during search.  It is
   completely 100% platform based, and will not be used if ANSI has been
   defined.  The code is based on the bioskey function from OliThink by
   Oliver Brausch. */

#ifndef ANSI

#ifndef WIN32

int bioskey (void) {

  fd_set readfds;

  FD_ZERO (&readfds);
  FD_SET (fileno (stdin), &readfds);
  tv.tv_sec=0; tv.tv_usec=0;
  select (16, &readfds, 0, 0, &tv);

  return (FD_ISSET (fileno (stdin), &readfds));

}

#else

#undef frame
#include <windows.h>
#define frame 0

int bioskey (void) {

  static int init = 0, pipe;
  static HANDLE inh;
  DWORD dw;

  if (!init) {
    init = 1;
    inh = GetStdHandle (STD_INPUT_HANDLE);
    pipe = !GetConsoleMode (inh, &dw);
    if (!pipe) {
      SetConsoleMode(inh, dw & ~(ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT));
      FlushConsoleInputBuffer (inh);
    }
  }
  if (pipe) {
    if (!PeekNamedPipe (inh, NULL, 0, NULL, &dw, NULL)) {
      return 1;
    }
    return dw;
  } else {
    GetNumberOfConsoleInputEvents (inh, &dw);
    return dw <= 1 ? 0 : dw;
  }

  return (0);

}

#endif

#endif


void comp_to_coord (move_s move, char str[]) {

  /* convert a move_s internal format move to coordinate notation: */

  int prom, from, target, f_rank, t_rank, converter;
  char f_file, t_file;

  prom = move.promoted;
  from = move.from;
  target = move.target;

  /* check to see if we have valid coordinates before continuing: */
  if (rank (from) < 1 || rank (from) > 8 ||
      file (from) < 1 || file (from) > 8 ||
      rank (target) < 1 || rank (target) > 8 ||
      file (target) < 1 || file (target) > 8) {
    sprintf (str, "xxxx");
    return;
  }
  
  f_rank = rank (from);
  t_rank = rank (target);
  converter = (int) 'a';
  f_file = file (from)+converter-1;
  t_file = file (target)+converter-1;

  /* "normal" move: */
  if (!prom) {
    sprintf (str, "%c%d%c%d", f_file, f_rank, t_file, t_rank);
  }

  /* promotion move: */
  else {
    if (prom == wknight || prom == bknight) {
      sprintf (str, "%c%d%c%dn", f_file, f_rank, t_file, t_rank);
    }
    else if (prom == wrook || prom == brook) {
      sprintf (str, "%c%d%c%dr", f_file, f_rank, t_file, t_rank);
    }
    else if (prom == wbishop || prom == bbishop) {
      sprintf (str, "%c%d%c%db", f_file, f_rank, t_file, t_rank);
    }
    else {
      sprintf (str, "%c%d%c%dq", f_file, f_rank, t_file, t_rank);
    }
  }

}


void display_board (FILE *stream, int color) {

  /* prints a text-based representation of the board: */
  
  char *line_sep = "+----+----+----+----+----+----+----+----+";
  char *piece_rep[14] = {"!!", " P", "*P", " N", "*N", " K", "*K", " R",
			  "*R", " Q", "*Q", " B", "*B", "  "};
  int a,b,c;

  if (color % 2) {
    fprintf (stream, "  %s\n", line_sep);
    for (a = 1; a <= 8; a++) {
      fprintf (stream, "%d |", 9 - a);
      for (b = 0; b <= 11; b++) {
	c = 120 - a*12 + b;
	if (board[c] != 0)
	  fprintf (stream, " %s |", piece_rep[board[c]]);
      }
      fprintf (stream, "\n  %s\n", line_sep);
    }
    fprintf (stream, "\n     a    b    c    d    e    f    g    h\n\n");
  }

  else {
    fprintf (stream, "  %s\n", line_sep);
    for (a = 1; a <= 8; a++) {
      fprintf (stream, "%d |", a);
      for (b = 0; b <= 11; b++) {
	c = 24 + a*12 -b;
	if (board[c] != 0)
	  fprintf (stream, " %s |", piece_rep[board[c]]);
      }
      fprintf (stream, "\n  %s\n", line_sep);
    }
    fprintf (stream, "\n     h    g    f    e    d    c    b    a\n\n");
  }

}


void ics_game_end (void) {

  /* read in gameend commands from the file gameend.txt to output to the
     ICS at the end of a game. */

  FILE *stream;
  char line[STR_BUFF];

  if ((stream = fopen ("gameend.txt", "r")) == NULL) {
    fprintf (stderr, "Could not open file gameend.txt!\n");
    return;
  }

  rinput (line, STR_BUFF, stream);
  do {
    /* ignore empty lines, or lines starting with spaces: */
    if (strncmp (line, " ", 1) && strlen (line))
      printf ("tellics %s\n", line);
    rinput (line, STR_BUFF, stream);
  } while (!feof (stream));

  fclose (stream);

}


void init_game (void) {

  /* set up a new game: */

  int i;

  int init_board[144] = {
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,7,3,11,9,5,11,3,7,0,0,
  0,0,1,1,1,1,1,1,1,1,0,0,
  0,0,13,13,13,13,13,13,13,13,0,0,
  0,0,13,13,13,13,13,13,13,13,0,0,
  0,0,13,13,13,13,13,13,13,13,0,0,
  0,0,13,13,13,13,13,13,13,13,0,0,
  0,0,2,2,2,2,2,2,2,2,0,0,
  0,0,8,4,12,10,6,12,4,8,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0
  };


  memcpy (board, init_board, sizeof (init_board));
  for (i = 0; i <= 143; i++)
    moved[i] = 0;

  white_to_move = 1;
  ep_square = 0;
  wking_loc = 30;
  bking_loc = 114;
  white_castled = no_castle;
  black_castled = no_castle;
  fifty = 0;
  game_ply = 0;

  result = no_result;
  captures = FALSE;

  piece_count = 14;

  post = TRUE;

  moves_to_tc = 30;
  min_per_game = 10;
  time_cushion = 0;

  reset_piece_square ();

  /* compute the initial hash: */
  srand (173);
  cur_pos = compute_hash ();

  /* set the first 3 rep entry: */
  rep_history[0] = cur_pos;

}


bool is_draw (void) {

  /* is_draw () is used to see if a position is a draw.  Some notes:
     - the 2 repetition trick is attempted first: if we have already seen a
     position in the search history (not game history), we haven't found
     anything better to do than repeat, and searching the position again would
     be a waste of time
     - if there is no match on the 2 repetition check, we look for an actual
     3 fold repetition
     - we can't check for the 50 move rule here, since the 50 move rule must be
     checked at the end of a search node due to mates  on the 50th move, yet
     we want to check for a draw by repetition before we waste any time
     searching the position or generating moves
     - is_draw () can be used in both search () and search_root () as the
     for loop for the 2 repetition trick will exit immediately at the root */

  int i, repeats = 0, end, start;

  /* Check on the 2 repetition trick.  Some notes:
     - a position can't possibly have occurred once before if fifty isn't
     at least 4
     - the end point is picked to look at the least number of positions, ie
     if going to the last capture is shorter than looking at the whole search
     history, we will do only that much */
  if (fifty >= 4) {
    if ((game_ply-ply+1) < (game_ply-fifty)) {
      end = game_ply-fifty;
    }
    else {
      end = game_ply-ply+1;
    }
    for (i = (game_ply-2); i >= 0 && i >= end; i -= 2) {
      if (cur_pos.x1 == rep_history[i].x1 && cur_pos.x2 == rep_history[i].x2) {
	return TRUE;
      }
    }
  }

  /* Check for actual 3 repetition match.  Some notes:
     - a position can't possibly have occurred twice before if fifty isn't
     at least 6
     - there is no need for us to consider positions encountered during search,
     as if there was a match on any of them, it would have been found above
     - we need to adjust the starting point here based on who's turn it is:
     if it's the same as at the root, we need to subtract one extra */
  if (fifty >= 6) {
    start = game_ply-ply-(ply%2);
    end = game_ply-fifty;
    for (i = start; i >= 0 && i >= end; i -= 2) {
      if (cur_pos.x1 == rep_history[i].x1 && cur_pos.x2 == rep_history[i].x2) {
	repeats++;
      }
      if (repeats >= 2) {
	return TRUE;
      }
    }
  }

  return FALSE;

}


bool is_move (char str[]) {

  /* check to see if the input string is a move or not.  Returns true if it
     is in a move format supported by Faile. */

  if (isalpha ((int) str[0]) && isdigit ((int) str[1]) 
      && isalpha ((int) str[2]) && isdigit ((int) str[3])) {
    return TRUE;
  }
  else {
    return FALSE;
  }

}


bool is_valid_comp (move_s in_move) {

  /* see if the Faile internal format move is a valid one */

  if (in_move.from == 0) {
    return FALSE;
  }
  else {
    return TRUE;
  }

}


void parse_cmdline (int argc, char *argv[]) {

  /* parse command line switches */

  int i = 1, tmp = 0;
  char *p;

  while (i < argc) {
    for (p = argv[i]; *p; p++) *p = tolower (*p);
    if (!strcmp ("-hash", argv[i]) || !strcmp ("/hash", argv[i])) {
      if (++i >= argc) {
	fprintf (stderr, "You must specify a hash size: faile -hash <size>\n");
	shut_down (EXIT_FAILURE);
      }
      else {
	hash_max_mb = (unsigned long int) atol (argv[i++]);
	if (atol (argv[i-1]) < 0) {
	  fprintf (stderr, "Hash table size must be positive!\n");
	  shut_down (EXIT_FAILURE);
	}
      }
    }
    else if (!strcmp ("-mbook", argv[i]) || !strcmp ("/mbook", argv[i])) {
      if (++i >= argc) {
	fprintf (stderr, "You must specify an input file: faile -mbook "
		 "<PGN input> [<max ply>]\n");
	shut_down (EXIT_FAILURE);
      }
      if (++i >= argc) {
	/* no max ply specified, use default of 20: */
	fprintf (stderr, "No max ply set, max ply defaulted to 20.\n");
	make_book (argv[i-1], 20);
      }
      else {
	/* max ply is specified */
	tmp = atoi (argv[i]);
	if (tmp < 0) {
	  fprintf (stderr, "Max ply must be positive!\n");
	  shut_down (EXIT_FAILURE);
	}
	if (tmp > MAX_B_PLY) {
	  fprintf (stderr, "Max ply set to %d (max ply needs to be <= %d).\n",
		   MAX_B_PLY, MAX_B_PLY);
	  tmp = MAX_B_PLY;
	}
	make_book (argv[i-1], tmp);
      }
    }
    else {
      fprintf (stderr, "\nUnrecognized command line argument: %s\n\n",
	       argv[i++]);
    }
  }

}


void perft_debug (void) {

  /* A function to debug the move gen by doing perft's, showing the board, and
     accepting move input */

  char input[STR_BUFF], *p;
  move_s move;
  int depth;

  init_game ();

  /* go into a loop of doing a perft(), then making the moves the user inputs
     until the user enters "exit" or "quit" */
  while (TRUE) {
    /* get the desired depth to generate to: */
    printf ("\n\nPlease enter the desired depth for perft():\n");
    rinput (input, STR_BUFF, stdin);
    depth = atoi (input);

    /* print out the number of raw nodes for this depth: */
    raw_nodes = 0;
    perft (depth);
    printf ("\n\nRaw nodes for depth %d: %ld\n\n", depth, raw_nodes);

    /* print out the board: */
    display_board (stdout, 1);

    printf ("\nPlease input a move/command:\n");
    rinput (input, STR_BUFF, stdin);

    /* check to see if we have an exit/quit: */
    for (p = input; *p; p++) *p = tolower (*p);
    if (!strcmp (input, "exit") || !strcmp (input, "quit")) {
      exit (EXIT_SUCCESS);
    }

    if (!verify_coord (input, &move)) {
      /* loop until we get a legal move or an exit/quit: */
      do {
	printf ("\nIllegal move/command!  Please input a new move/command:\n");
	rinput (input, STR_BUFF, stdin);

	/* check to see if we have an exit/quit: */
	for (p = input; *p; p++) *p = tolower (*p);
	if (!strcmp (input, "exit") || !strcmp (input, "quit")) {
	  exit (EXIT_SUCCESS);
	}
      } while (!verify_coord (input, &move));
    }

    make (&move, 0);
  }
}


void post_thinking (long int score) {

  /* post our thinking output: */

  int i;
  long int elapsed;
  char output[STR_BUFF];

  /* in xboard mode, follow xboard conventions for thinking output, otherwise
     output the iterative depth, human readable score, and the pv */
  if (xb_mode) {
    elapsed = rdifftime (rtime (), start_time);
    printf ("%d %ld %ld %ld ", i_depth, score, elapsed, nodes);
    for (i = 1; i < pv_length[1]; i++) {
      comp_to_coord (pv[1][i], output);
      printf ("%s ", output);
    }
    printf ("\n");
  }
  else {
    if (score >= 0)
      printf ("%d  %1.2f  ", i_depth, (float) score/100);
    else
      printf ("%d %1.2f  ", i_depth, (float) score/100);
    for (i = 1; i < pv_length[1]; i++) {
      comp_to_coord (pv[1][i], output);
      printf ("%s ", output);
    }
    printf ("\n");
  }

}


void print_move (move_s moves[], int m, FILE *stream) {

  /* print out a move */

  char move[6];

  comp_to_coord (moves[m], move);

  fprintf (stream, "%s", move);

}


void rdelay (int time_in_s) {

  /* My delay function to cause a delay of time_in_s seconds */

  rtime_t time1, time2;
  long int timer = 0;

  time1 = rtime ();
  while (timer/100 < time_in_s) {
    time2 = rtime ();
    timer = rdifftime (time2, time1);
  }

}


long int rdifftime (rtime_t end, rtime_t start) {

  /* determine the time taken between start and the current time in
     centi-seconds */

  /* using ftime(): */
  #ifndef ANSI
  return ((end.time-start.time)*100 + (end.millitm-start.millitm)/10);

  /* -------------------------------------------------- */

  /* using time(): */
  #else
  return (100*(long int) difftime (end, start));
  #endif

}


void reset_piece_square (void) {

  /* reset the pieces[] / squares[] arrays */

  int i;

  /* we use piece number 0 to show a piece taken off the board, so don't
     use that piece number for other things: */
  pieces[0] = 0;
  num_pieces = 0;

  for (i = 26; i < 118; i++) {
    if (board[i] != frame && board[i] != npiece) {
      pieces[++num_pieces] = i;
      squares[i] = num_pieces;
    }
    else {
      squares[i] = 0;
    }
  }

}


void rinput (char str[], int n, FILE *stream) {

  /* My input function - reads in up to n-1 characters from stream, or until
     we encounter a \n or an EOF.  Appends a null character at the end of the
     string, and stores the string in str[] */

  int ch, i = 0;

  while ((ch = getc (stream)) != (int) '\n' && ch != EOF) {
    if (i < n-1) {
      str[i++] = ch;
    }
  }

  str [i] = '\0';

}


rtime_t rtime (void) {

  /* If ANSI is not defined, use ftime() as our timing function, otherwise
     use time() */

  /* using ftime(): */
  #ifndef ANSI
  rtime_t temp;
  ftime(&temp);
  return (temp);

  /* -------------------------------------------------- */

  /* using time(): */
  #else
  return (time (0));
  #endif

}


void shut_down (int status) {

  /* shut down Faile: */

  free (hash_table);
  exit (status);

}


void start_up (void) {

  /* things to do on start up of the program */

  printf ("Faile version 1.4\nby Adrien Regimbald\n\n\n");
  rdelay (2);

}


void toggle_bool (bool *var) {

  /* toggle FALSE -> TRUE, TRUE -> FALSE */

  if (*var) {
    *var = FALSE;
  }
  else {
    *var = TRUE;
  }

}


void tree_debug (void) {

  /* A function to make a tree of output at a certain depth and print out
     the number of nodes: */

  char input[STR_BUFF];
  FILE *stream;
  int depth;

  init_game ();

  /* get the desired depth to generate to: */
  printf ("\nPlease enter the desired depth:\n");
  rinput (input, STR_BUFF, stdin);
  depth = atoi (input);

  /* does the user want to output tree () ? */
  printf ("\nDo you want tree () output?  (y/n)\n");
  rinput (input, STR_BUFF, stdin);
  if (input[0] == 'y') {
    /* get our output file: */
    printf ("\nPlease enter the name of the output file for tree ():\n");
    rinput (input, STR_BUFF, stdin);
    if ((stream = fopen (input, "w")) == NULL) {
      fprintf (stderr, "Couldn't open file %s\n", input);
    }

    /* does the user want to output diagrams? */
    printf ("\nDo you want to output diagrams? (y/n)\n");
    rinput (input, STR_BUFF, stdin);

    tree (depth, 0, stream, input);
  }

  /* print out the number of raw nodes for this depth: */
  raw_nodes = 0;
  perft (depth);
  printf ("\n\n%s\nRaw nodes for depth %d: %ld\n%s\n\n", divider,
	  depth, raw_nodes, divider);

}


bool verify_coord (char input[], move_s *move) {

  /* checks to see if the move the user entered was legal or not, returns
     true if the move was legal, and stores the legal move inside move */

  move_s moves[MOVE_BUFF];
  int num_moves, i, ep_temp;
  char comp_move[6];
  bool legal = FALSE;
  d_long temp_hash;

  ep_temp = ep_square;
  temp_hash = cur_pos;
  num_moves = 0;
  gen (&moves[0], &num_moves);

  /* compare user input to the generated moves: */
  for (i = 0; i < num_moves; i++) {
    comp_to_coord (moves[i], comp_move);
    if (!strcmp (input, comp_move)) {
      make (&moves[0], i);
      if (check_legal (&moves[0], i)) {
	legal = TRUE;
	*move = moves[i];
      }
      unmake (&moves[0], i);
      ep_square = ep_temp;
      cur_pos = temp_hash;
    }
  }

  return (legal);

}
