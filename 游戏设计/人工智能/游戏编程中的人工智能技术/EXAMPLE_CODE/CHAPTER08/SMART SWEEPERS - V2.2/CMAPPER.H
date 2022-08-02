#ifndef CMAPPER_H
#define CMAPPER_H

//------------------------------------------------------------------------
//
//	Name: CMapper.h
//
//  Author: Mat Buckland 2002
//
//  Desc: Class to create a memory for a minesweeper.
//
//------------------------------------------------------------------------

#include <vector>
#include <windows.h>

#include "utils.h"
#include "Cparams.h"

using namespace std;

//------------------------------------------------------------------------
//
//  structure to define a 'cell'. A cell is a RECT in space and keeps
//  a track of how many ticks the bot has spent at the cell.
//------------------------------------------------------------------------
struct SCell
{
  //how often frequented
  int iTicksSpentHere;

  //the coordinates which describe the cell's position
  RECT Cell;

  SCell(int xmin, int xmax, int ymin, int ymax):iTicksSpentHere(0)                                                                                         
  {
    Cell.left   = xmin;
    Cell.right  = xmax;
    Cell.top    = ymin;
    Cell.bottom = ymax;
  }
                    
  void Update()
  {
    ++iTicksSpentHere;
  }



  void Reset()
  {
    iTicksSpentHere = 0;
  }
};


//------------------------------------------------------------------------
//
//  This mapper class holds information about a 2d vector of cells
//------------------------------------------------------------------------
class CMapper
{
private:

  //the 2d vector of memory cells
  vector<vector<SCell> > m_2DvecCells;

  int     m_NumCellsX;
  int     m_NumCellsY;
  int     m_iTotalCells;

  //the dimensions of each cell
  double  m_dCellSize;
  
public:

  CMapper():m_NumCellsX(0),
            m_NumCellsY(0),
            m_iTotalCells(0)
  {}

  //this must be called after an instance of this class has been
  //created. This sets up all the cell coordinates.
  void    Init(int MaxRangeX, int MaxRangeY);

  //this method is called each frame and updates the time spent
  //at the cell at this position
  void    Update(double xPos, double yPos);

  //returns how many ticks have been spent at this cell position
  int     TicksLingered(double xPos, double yPos) const;

  //returns the total number of cells visited
  int     NumCellsVisited()const;
  
  //returns if the cell at the given position has been visited or
  //not
  bool    BeenVisited(double xPos, double yPos) const;

  //This method renders any visited cells in shades of red. The
  //darker the red, the more time has been spent at that cell
  void    Render(HDC surface);

  void    Reset();

  int     NumCells()const{return m_iTotalCells;}
};



#endif

