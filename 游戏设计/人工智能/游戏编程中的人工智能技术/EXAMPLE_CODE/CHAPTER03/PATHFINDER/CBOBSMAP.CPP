#include "CBobsMap.h"


//this defines our little maze which Bob wanders
//around in
const int CBobsMap::map[MAP_HEIGHT][MAP_WIDTH] = 
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
 8, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1,
 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1,
 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5,
 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};


const int CBobsMap::m_iMapHeight = MAP_HEIGHT;
const int CBobsMap::m_iMapWidth  = MAP_WIDTH;

const int CBobsMap::m_iStartX = 14;
const int CBobsMap::m_iStartY = 7;

const int CBobsMap::m_iEndX = 0;
const int CBobsMap::m_iEndY = 2;


//-------------------------------Render -----------------------------

void CBobsMap::Render(const int cxClient,
					  const int cyClient,
					  HDC surface)
{
	const int border = 20;
	
	int BlockSizeX = (cxClient - 2*border)/m_iMapWidth;
	int BlockSizeY = (cyClient - 2*border)/m_iMapHeight;

	HBRUSH	BlackBrush, RedBrush, OldBrush;
	HPEN	NullPen, OldPen;

	//grab a null pen so we can see the outlines of the cells
	NullPen = (HPEN)GetStockObject(NULL_PEN);

	//grab a brush to fill our cells with
	BlackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);

	//create a brush for the exit/entrance points
	RedBrush = CreateSolidBrush(RGB(255,0,0));

	//select them into the device conext
	OldBrush = (HBRUSH)SelectObject(surface, BlackBrush);
	OldPen	 =	 (HPEN)SelectObject(surface, NullPen);
	
	for (int y=0; y<m_iMapHeight; ++y)
	{
		for (int x=0; x<m_iMapWidth; ++x)
		{
			//calculate the corners of each cell
			int left  = border + (BlockSizeX * x);
			int right = left + BlockSizeX;
			
			int top    = border + (BlockSizeY * y);
			int bottom = top + BlockSizeY;
			
			//draw black rectangle if this is a wall
			if (map[y][x] == 1)
			{
				SelectObject(surface, BlackBrush);

				//draw the cell
				Rectangle(surface, left, top, right, bottom);
			}
			
			//draw red for exit and entrance
			if ( (map[y][x] == 5) || (map[y][x] == 8))
			{
				SelectObject(surface, RedBrush);

				//draw the cell
				Rectangle(surface, left, top, right, bottom);
			}
			
			
		}
	}

	//restore the original brush
	SelectObject(surface, OldBrush);

	//and pen
	SelectObject(surface, OldPen);
}

//-------------------------------MemoryRender ------------------------
//
//	//draws whatever path may be stored in the memory
//--------------------------------------------------------------------
void CBobsMap::MemoryRender(const int cxClient,
							const int cyClient,
							HDC surface)
{
	const int border = 20;
	
	int BlockSizeX = (cxClient - 2*border)/m_iMapWidth;
	int BlockSizeY = (cyClient - 2*border)/m_iMapHeight;
	
	HBRUSH	GreyBrush, OldBrush;
	HPEN	NullPen, OldPen;
	
	//grab a brush to fill our cells with
	GreyBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH);

	//grab a pen
	NullPen = (HPEN)GetStockObject(NULL_PEN);
	
	//select them into the device conext
	OldBrush = (HBRUSH)SelectObject(surface, GreyBrush);
	OldPen	 =	(HPEN)SelectObject(surface, NullPen);
	
	for (int y=0; y<m_iMapHeight; ++y)
	{
		for (int x=0; x<m_iMapWidth; ++x)
		{
			//calculate the corners of each cell
			int left  = border + (BlockSizeX * x);
			int right = left + BlockSizeX;
			
			int top    = border + (BlockSizeY * y);
			int bottom = top + BlockSizeY;
			
			//draw green rectangle if this is a wall
			if (memory[y][x] == 1)
			{
				Rectangle(surface, left, top, right, bottom);
			}
		}
	}
	
	//restore the original brush
	SelectObject(surface, OldBrush);
	
	//and pen
	SelectObject(surface, OldPen);

}

//---------------------------- TestRoute ---------------------------
//
//	given a decoded vector of directions and a map object representing
//	Bob's memory, this function moves Bob through the maze as far as 
//	he can go updating his memory as he moves.
//-------------------------------------------------------------------
double CBobsMap::TestRoute(const vector<int> &vecPath, CBobsMap &Bobs)
{
	int posX = m_iStartX;
	int posY = m_iStartY;

	for (int dir=0; dir<vecPath.size(); ++dir)
	{
		int NextDir = vecPath[dir];

		switch(vecPath[dir])
		{
		case 0: //North

			//check within bounds and that we can move
			if ( ((posY-1) < 0 ) || (map[posY-1][posX] == 1) )
			{
				break;
			}

			else
			{
				posY -= 1;
			}

			break;

		case 1: //South

			//check within bounds and that we can move
			if ( ((posY+1) >= m_iMapHeight) || (map[posY+1][posX] == 1) )
			{
				break;
			}
			
			else
			{
				posY += 1;
			}

			break;

		case 2: //East

			//check within bounds and that we can move
			if ( ((posX+1) >= m_iMapWidth ) || (map[posY][posX+1] == 1) )
			{
				break;
			}
			
			else
			{
				posX += 1;
			}

			break;

		case 3: //West

			//check within bounds and that we can move
			if ( ((posX-1) < 0 ) || (map[posY][posX-1] == 1) )
			{
				break;
			}
			
			else
			{
				posX -= 1;
			}

			break;

		}//end switch

		//mark the route in the memory array
		Bobs.memory[posY][posX] = 1;

	}//next direction

	//now we know the finish point of Bobs journey, let's assign
	//a fitness score which is proportional to his distance from
	//the exit

	int	DiffX = abs(posX - m_iEndX);
	int DiffY = abs(posY - m_iEndY);

	//we add the one to ensure we never divide by zero. Therefore
	//a solution has been found when this return value = 1
	return 1/(double)(DiffX+DiffY+1);
}

//--------------------- ResetMemory --------------------------
//
//	resets the memory map to zeros
//------------------------------------------------------------
void CBobsMap::ResetMemory()
{
	for (int y=0; y<m_iMapHeight; ++y)
	{
		for (int x=0; x<m_iMapWidth; ++x)
		{
			memory[y][x] = 0;
		}
	}
}



