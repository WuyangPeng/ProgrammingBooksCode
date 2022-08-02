// MatCalc.cpp: implementation of the MatCalc class.
//
//////////////////////////////////////////////////////////////////////
#include <memory.h>
#include <math.h>
#include "MatCalc.h"

// Initialize our function pointers
Func MatCalc::pf_solve = { MatCalc::multiply, MatCalc::add, MatCalc::subtract, MatCalc::cross, MatCalc::dot };

//////////////////////////////////////////////////////////////////////////////////////
// Function:	Constructor
//
// Purpose:		Initialize our class members
//
// Input:		r:		the number of rows in our data (count from 1)
//				c:		the number of columns in our data (count from 1)
//				pItem:	what, if any, to set our data to
//
// Ouput:		none			
//////////////////////////////////////////////////////////////////////////////////////
MatCalc::MatCalc(int r, int c, float *pItem)
{
	row = r;
	col = c;

	pData = new float[row * col];

	if(pItem)
		memcpy(pData, pItem, sizeof(float) * row * col);
}

//////////////////////////////////////////////////////////////////////////////////////
// Function:	Destructor
//
// Purpose:		Release our memory
//
// Input:		none
//
// Ouput:		none			
//////////////////////////////////////////////////////////////////////////////////////
MatCalc::~MatCalc()
{
	delete [] pData;
}

//////////////////////////////////////////////////////////////////////////////////////
// Function:	Copy Constructor
//
// Purpose:		copy an existing MatCalc
//
// Input:		m:	the matrix that is being copied
//
// Ouput:		none			
//////////////////////////////////////////////////////////////////////////////////////
MatCalc::MatCalc(const MatCalc &m)
{
	row = m.row;
	col = m.col;

	pData = new float[row * col];

	memcpy(pData, m.pData, sizeof(float) * row * col);

}

//////////////////////////////////////////////////////////////////////////////////////
// Function:	Assignment operator
//
// Purpose:		copy an existing MatCalc
//
// Input:		m:	the matrix that is being copied
//
// Ouput:		ourselves			
//////////////////////////////////////////////////////////////////////////////////////
MatCalc &MatCalc::operator=(const MatCalc &m)
{
	if(this == &m)
		return *this;

	row = m.row;
	col = m.col;

	pData = new float[row * col];

	memcpy(pData, m.pData, sizeof(float) * row * col);

	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////
// Function:	multiply
//
// Purpose:		multiply 2 MatCalc's, encompassing a scalar times anything or a matrix times a vetor
//
// Input:		pOne:	a pointer to the left hand operand
//				pTwo:	a pointer to the right hand operand
//
// Ouput:		pTemp:	our answer			
//////////////////////////////////////////////////////////////////////////////////////
MatCalc *MatCalc::multiply(MatCalc *pOne, MatCalc *pTwo)
{
	//////////////////////////////////////////////////////////////////////////////////////
	// There is no need to error check compatibilty between our invoking object and our
	// passed in MatCalc, since that is handled within our main loop.  If error checking
	// needed to be done, we would have to compare the value in this->col and pTwo->row
	// to make sure they are identical, barring the case of a scalar being multiplied
	//////////////////////////////////////////////////////////////////////////////////////
	
	// Handles the event of a scalar as the left hand operand
	if(pOne->row == 1)
	{
		// Make a new Matrix or Vector
		MatCalc *pTemp = new MatCalc(pTwo->row, pTwo->col);

		// Multiply the scalar by every component
		for(int i = 0; i < pTwo->row * pTwo->col; ++i)
		{
			pTemp->pData[i] = pTwo->pData[i] * pOne->pData[0];
		}
		// Return our answer
		return pTemp;
	}
	// Handles the event of a scalar as the right hand operand
	else if(pTwo->row == 1)
	{
		// Make a new Matrix or Vector
		MatCalc *pTemp = new MatCalc(pOne->row, pOne->col);

		// Multiply the scalar by every component
		for(int i = 0; i < pOne->row * pOne->col; ++i)
		{
			pTemp->pData[i] = pOne->pData[i] * pTwo->pData[0];
		}
		// Return our answer
		return pTemp;
	}

	else
	{
		// A MatCalc pointer which will hold our answer
		MatCalc *pTemp = new MatCalc(pOne->row, pTwo->col);

		// Holds which value in pTemp->pData we are currently setting
		int index = 0;

		// Fills in our pTemp's data
		for(int i = 0; i < pOne->row; ++i)
		{
			for(int j = 0; j < pTwo->col; ++j)
			{
				// Dot the appropriate row witht he appropriate column
				pTemp->pData[index++] = pOne->dotRowCol(pOne->getRow(i), pTwo->getCol(j));
			}
		}
		// Return our answer
		return pTemp;
	}

}

//////////////////////////////////////////////////////////////////////////////////////
// Function:	add
//
// Purpose:		add 2 MatCalc's, encompassing a vector plus a vector or a matrix plus a matrix
//
// Input:		pOne:	a pointer to the left hand operand
//				pTwo:	a pointer to the right hand operand
//
// Ouput:		pTemp:	our answer			
//////////////////////////////////////////////////////////////////////////////////////
MatCalc *MatCalc::add(MatCalc *pOne, MatCalc *pTwo)
{
	// Create a temp of sufficiant size to hold our answer
	MatCalc *pTemp = new MatCalc(pOne->row, pTwo->col);

	// Add each component to its corresponding component
	for(int i = 0; i < pOne->row * pTwo->col; ++i)
	{
		pTemp->pData[i] = pOne->pData[i] + pTwo->pData[i];
	}
	// Return our answer
	return pTemp; 
}

//////////////////////////////////////////////////////////////////////////////////////
// Function:	subtract
//
// Purpose:		subtract 2 MatCalc's, encompassing a vector plus a vector or a matrix plus a matrix
//
// Input:		pOne:	a pointer to the left hand operand
//				pTwo:	a pointer to the right hand operand
//
// Ouput:		pTemp:	our answer			
//////////////////////////////////////////////////////////////////////////////////////
MatCalc *MatCalc::subtract(MatCalc *pOne, MatCalc *pTwo)
{
	// Create a temp of sufficiant size to hold our answer
	MatCalc *pTemp = new MatCalc(pOne->row, pTwo->col);

	// Subtract each component from its corresponding component
	for(int i = 0; i < pOne->row * pTwo->col; ++i)
	{
		pTemp->pData[i] = pOne->pData[i] - pTwo->pData[i];
	}
	
	// Return our answer
	return pTemp; 
}

//////////////////////////////////////////////////////////////////////////////////////
// Function:	dot
//
// Purpose:		dot 2 MatCalc's, encompassing a vector dotted to a vector
//
// Input:		pOne:	a pointer to the left hand operand
//				pTwo:	a pointer to the right hand operand
//
// Ouput:		pTemp:	our answer			
//////////////////////////////////////////////////////////////////////////////////////
MatCalc *MatCalc::dot(MatCalc *pOne, MatCalc *pTwo)
{
	// Create a temp of sufficiant size to hold our answer
	MatCalc *pTemp = new MatCalc(1, 1);

	// Call our internal function which dots for us
	pTemp->pData[0] = pOne->dotRowCol(pOne->getCol(0), pTwo->getCol(0));

	// Return our answer
	return pTemp;
}

//////////////////////////////////////////////////////////////////////////////////////
// Function:	cross
//
// Purpose:		cross 2 MatCalc's, encompassing a vector crossed to a vector
//
// Input:		pOne:	a pointer to the left hand operand
//				pTwo:	a pointer to the right hand operand
//
// Ouput:		pTemp:	our answer			
//////////////////////////////////////////////////////////////////////////////////////
MatCalc *MatCalc::cross(MatCalc *pOne, MatCalc *pTwo)
{
	// Create a temp of sufficiant size to hold our answer
	MatCalc *pTemp = new MatCalc(3, 1);

	// Calculate the first component
	pTemp->pData[0] = pOne->pData[1] * pTwo->pData[2] - pOne->pData[2] * pTwo->pData[1];
	// Calculate the second component
	pTemp->pData[1] = pOne->pData[2] * pTwo->pData[0] - pOne->pData[0] * pTwo->pData[2];
	// Calculate the third component
	pTemp->pData[2] = pOne->pData[0] * pTwo->pData[1] - pOne->pData[1] * pTwo->pData[0];

	// Return our answer
	return pTemp;
}

//////////////////////////////////////////////////////////////////////////////////////
// Function:	normalize
//
// Purpose:		make a vector unit length
//
// Input:		pOne:	a pointer to the vector being normalized
//
// Ouput:		pTemp:	our answer			
//////////////////////////////////////////////////////////////////////////////////////
MatCalc *MatCalc::normalize(MatCalc *pOne)
{
	// Create a temp of sufficiant size to hold our answer
	MatCalc *pTemp = new MatCalc(pOne->row, pOne->col);

	// This will hold our magnitude when we are done
	float fMag = 0;

	// Initialise our temp to the vector passed in and sum up the components squared (ignoring
	// the fourth component in the event that there is one)
	for(int i = 0; i < pOne->row; ++i)
	{
		if(i < 3)
		{
			fMag +=	powf(pOne->pData[i], 2);
			pTemp->pData[i] = pOne->pData[i];
		}
		else
			pTemp->pData[i] = 1;
	}

	// Square root our summed up values
	fMag = sqrtf(fMag);

	// For every component (except the fourth), divide by the magnitude to normalize 
	for(i = 0; i < pOne->row; ++i)
	{
		if(i < 3)
			pTemp->pData[i] /= fMag;
	}
	// Return our ansswer
	return pTemp;
}


//////////////////////////////////////////////////////////////////////////////////////
// Function:	dotRowcol
//
// Purpose:		dot 2 vectors, this function is internal to the class and used in the
//				multiply function
//
// Input:		r:			an array of floats holding the row being dotted
//				c:			an array of floats holding the column being dotted
//
// Ouput:		fAnswer:	the result			
//////////////////////////////////////////////////////////////////////////////////////
float MatCalc::dotRowCol(float *r, float *c) const
{
	// A variable to hold our final answer
	float fAnswer = 0;

	// For every component in our rows and columns, multiply and add to the summed up total
	for(int i = 0; i < this->row; ++i)
	{
		fAnswer += r[i] * c[i];	
	}

	// Clean up our memory
	delete [] r;
	delete [] c;

	// Return our answer
	return fAnswer;
}


//////////////////////////////////////////////////////////////////////////////////////
// Function:	getRow
//
// Purpose:		Return a particular row from our invoking object's pData
//
// Input:		r:		the particular row we are trying to capture (count from 0)
//
// Ouput:		pRow:	Our captured row			
//////////////////////////////////////////////////////////////////////////////////////
float *MatCalc::getRow(int r) const
{
	// Allocate an array large enough to hold the respective row
	float *pRow = new float[this->col];

	// Fill in our array
	for(int i = 0; i < col; ++i)
	{
		pRow[i] = pData[i + r * this->col];
	}
	// return the row
	return pRow;
}

//////////////////////////////////////////////////////////////////////////////////////
// Function:	getCol
//
// Purpose:		Return a particular column from our invoking object's pData
//
// Input:		c:		the particular col we are trying to capture (count from 0)
//
// Ouput:		pCol:	Our captured column			
//////////////////////////////////////////////////////////////////////////////////////
float *MatCalc::getCol(int c) const
{
	// Allocate an array large enough to hold the respective column
	float *pCol = new float[this->row];

	// Fill in our array
	for(int i = 0; i < row; ++i)
	{
		pCol[i] = pData[c + i * this->col];
	}

	// return the row
	return pCol;
}
