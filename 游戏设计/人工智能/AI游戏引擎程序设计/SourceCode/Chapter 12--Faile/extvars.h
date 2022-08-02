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
 * File: extvars.h                                *
 * Purpose: holds global variables                *
 **************************************************/

extern char divider[50];

extern int board[144], moved[144], ep_square, white_to_move, wking_loc,
  bking_loc, white_castled, black_castled, result, ply, pv_length[PV_BUFF],
  history_h[144][144], pieces[33], squares[144], num_pieces, i_depth, fifty,
  fifty_move[PV_BUFF], game_ply;

extern long int nodes, raw_nodes, qnodes, piece_count, killer_scores[PV_BUFF],
  killer_scores2[PV_BUFF], moves_to_tc, min_per_game, inc, time_left,
  opp_time, time_cushion, time_for_move, cur_score, start_piece_count,
  last_root_score;

extern bool xb_mode, captures, searching_pv, post, time_exit, time_failure,
  allow_more_time, bad_root_score;

extern move_s pv[PV_BUFF][PV_BUFF], dummy, killer1[PV_BUFF], killer2[PV_BUFF],
  killer3[PV_BUFF];

extern rtime_t start_time;

extern d_long h_values[14][144], ep_h_values[144], wck_h_values[2],
  wcq_h_values[2], bck_h_values[2], bcq_h_values[2], color_h_values[2],
  cur_pos, rep_history[PV_BUFF];

extern hash_s *hash_table;

extern unsigned long int hash_mask, hash_max_mb;
