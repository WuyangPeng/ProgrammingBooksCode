#ifndef EIGHT_QUEENS_PROBLEM
#define EIGHT_QUEENS_PROBLEM

#include <iostream>
#include <vector>

#include "d_matrix.h"

using namespace std;

// can a queen at (row,col) be attacked by any of the
// non-attacking queens in columns 0 to col-1 ?
bool safeLocation(int row, int col, const vector<int>& queenList);

// place a queen in columns col through 7
bool placeQueens(vector<int>& queenList, int col);

// try to find a solution to the 8-Queens problem starting
// with a queen at (row,0)
bool queens(vector<int>& queenList, int row);

bool safeLocation(int row, int col, const vector<int>& queenList)
{
	int qRow, qCol;
	
	for (qCol = 0; qCol < col; qCol++)	// check previous columns only
	{
		qRow = queenList[qCol];
		if (qRow == row)				// same row
			return false;
		else if (qCol == col)		// same col
			return false;
		// can they attack on a diagonal?
		else if(qCol-qRow == col-row || qCol+qRow == col+row)
			return false;
	}
	return true;
}

bool placeQueens(vector<int>& queenList, int col)
{
	int row;
	bool foundLocation;

	if (col == 8)	// stopping condition
		foundLocation = true;
	else
	{
		foundLocation = false; // start with row 0
		row = 0;
		while (row < 8 && !foundLocation)
		{
			// check whether cell (row, col) is safe; if so,
			// assign row to queenList and call placeQueens()
			// for next column; otherwise, go to the next row
			if (safeLocation(row,col,queenList) == true)
			{
				// found good location
				queenList[col] = row;

				// recursive step. try to place queens in columns col+1
				// through 7
				foundLocation = placeQueens(queenList,col+1);
				if (!foundLocation)
					// use next row since current one does not lead
					// to a solution
					row++;
			}
			else
				// current row fails. go to the next row
				row++;

		}	// end while
	}

	// pass success or failure back to previous col
	return foundLocation;
}

bool queens(vector<int>& queenList, int row)
{
	// place first queen at (row,0)
	queenList[0] = row;

	// locate remaining queens in columns 1 through 7
	if (placeQueens(queenList, 1))
		return true;
	else
		return false;
}

class chessBoard
{
	public:
		chessBoard();
			// default constructor		

		void setQueens(const vector<int>& queenList);
			// set queens on board at cells (queenList[col], col)
			// 0 <= col < 8

		void clearBoard();
			// clear the board

		void drawBoard() const;	
			// draw the board using symbols 'Q' or '-'
	private:
		// simulates chess board
		matrix<bool> board;
};

// constructor. initialize board to blanks
chessBoard::chessBoard(): board(8,8)
{
	clearBoard();
}

// assign queens at locations (queenList[col],col),
// 0 <= col < 8
void chessBoard::setQueens(const vector<int>& queenList)
{
	clearBoard();

	for (int col = 0; col < 8; col++)
			board[queenList[col]][col] = true;
}

void chessBoard::clearBoard()
{
	int i,j;		

	for(i=0;i < 8;i++)
		for(j=0;j < 8;j++)
			board[i][j] = false;
}

// draw the chess board
void chessBoard::drawBoard() const
{
	int i,j;

	cout <<"   0 1 2 3 4 5 6 7" << endl;
	for (i = 0; i < 8; i++)
	{
		cout << i << " ";
		// draw the squares in current row
		for (j = 0; j < 8; j++)
		{
			if (board[i][j] == true)
				cout << " Q";
			else
				cout << " -";
		}
		cout << endl;
	}
}

#endif	// EIGHT_QUEENS_PROBLEM
