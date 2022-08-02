#ifdef __BORLANDC__
// suppress the warning message about comparing signed and unsigned values
#pragma warn -8012
#endif	// __BORLANDC__

#ifndef EIGHT_QUEENS_GRAPHICAL
#define EIGHT_QUEENS_GRAPHICAL

#include <vector>

#include "d_matrix.h"
#include "d_draw.h"
#include "d_rectsh.h"
#include "d_circsh.h"

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
		// constructor
		chessBoard();

		// close drawing window when object destroyed
		~chessBoard();

		// assign ch to board[row][col]
		void setQueens(const vector<int>& queenList);

		// clear the board
		void clearBoard();

		// draw the lightblue and white chess board. a queen
		// is represented by a small black circle in the cell
		void drawBoard();
	private:
		// simulates chess board
		matrix<bool> board;
};

// constructor. initialize board to blanks
chessBoard::chessBoard(): board(8,8)
{
	clearBoard();
}

// destructor
chessBoard::~chessBoard()
{
	// object being destroyed. close drawing surface
	closeWindow();
}

// assign ch to board[row][col]
void chessBoard::setQueens(const vector<int>& queenList)
{
	clearBoard();

	for (int col = 0; col < queenList.size(); col++)
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
void chessBoard::drawBoard()
{
	int i,j;
	// (h,v) is position of current square being drawn
	double h = 1.0, v = 1.0;
	// use to draw the board squares
	rectShape square(h,v,0.5,0.5),
		       frame(0.9,0.9,4.20,4.20,black);
	circleShape queen(0,0,0.15,black);

	// colors for squares without a queen alternate lightblue/white
	shapeColor c = lightblue;
	// only open the window once
	static bool windowOpen = false;

	if (windowOpen)
		// window already open. erase it
		eraseWindow();
	else
	{
		// open window and note that it is open
		openWindow();
		windowOpen = true;
	}

	frame.draw();
	// first square at (1,1)
	v = 1;
	for (i = 0; i < 8; i++)
	{
		// each row starts with h = 1.0
		h = 1.0;
		// draw the squares in current row
		for (j = 0; j < 8; j++)
		{
			// set the color of the square
			square.setColor(c);

			// locate the square. note for each row
			// that v is constant
			square.move(h,v);

			// draw the square at (h,v), length/width = 1.
			// use color c if not a queen;
			// otherwise, use white
			square.draw();

			if (board[i][j] == true)
			{
				queen.move(h+0.25, v+0.25);
				queen.draw();
			}

			// alternate red and black
			c = (c == white) ? lightblue : white;

			// set h for next square in this row
			h += 0.5;
		}
		// get ready for the next row
		v += 0.5;

		// color of last square starts new row
		c = (c == white) ? lightblue : white;
		square.setColor(c);
	}

	// view the board
	viewWindow();
}


#endif	// EIGHT_QUEENS_GRAPHICAL