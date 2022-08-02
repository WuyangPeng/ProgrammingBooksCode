// File: prg15_6g.cpp
// the program solves the 8-Queens problem. it prompts the user for
// the starting row for the queen in column 0 and calls the recursive
// backtracking function queens() to determine if there is a solution.
// if there is a solution, the position of the queens is passed to
// the chessboard object, board, and a call to its drawBoard() function
// shows the placement of the queens graphically using the drawing
// package discussed in Chapter 13

#include <iostream>
#include <vector>

// graphical display of 8-Queens solution
#include "d_gqueen.h"

using namespace std;

int main ()
{
	int row;
	vector<int> queenList(8);
	chessBoard board;

	// enter a starting row for queen in column 0
	cout << "Enter row for queen in column 0: ";
	cin >> row;
	cout << endl;

	// see if there is a solution
	if (queens(queenList, row))
	{
		board.setQueens(queenList);
		// display the solution
		board.drawBoard();
	}
	else
		cout << "No solution" << endl;

	return 0;
}
