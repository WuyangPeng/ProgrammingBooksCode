// File: prg15_6.cpp
// the program solves the 8-Queens problem. it prompts the user for
// the starting row for the queen in column 0 and calls the recursive
// backtracking function queens() to determine if there is a solution.
// if there is a solution, the position of the queens is passed to
// the chessboard object, board, and a call to its drawBoard() function
// shows the placement of the queens

#include <iostream>

#include "d_queens.h"

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

/*
Run 1:

Enter row for queen in column 0: 2

   0 1 2 3 4 5 6 7
0  - Q - - - - - -
1  - - - - - Q - -
2  Q - - - - - - -
3  - - - - - - Q -
4  - - - Q - - - -
5  - - - - - - - Q
6  - - Q - - - - -
7  - - - - Q - - -

Run 2:

Enter row for queen in column 0: 5

   0 1 2 3 4 5 6 7
0  - Q - - - - - -
1  - - - Q - - - -
2  - - - - - Q - -
3  - - - - - - - Q
4  - - Q - - - - -
5  Q - - - - - - -
6  - - - - - - Q -
7  - - - - Q - - -
*/