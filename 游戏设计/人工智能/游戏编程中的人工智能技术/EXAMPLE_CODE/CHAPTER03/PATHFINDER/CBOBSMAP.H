#ifndef CBOBSMAP_H
#define CBOBSMAP_H

///////////////////////////////////////////////////////////////////////
//
//		File: CBobsMap.h
//
//		Author: Mat Buckland
//
//		Desc: Class for defining the map described in chapter 3
//
///////////////////////////////////////////////////////////////////////

#include "stdlib.h"
#include "windows.h"
#include <vector>

#include "defines.h"


using namespace std;




class CBobsMap
{
private:
	
	//storage for the map
	static const int	map[MAP_HEIGHT][MAP_WIDTH];

	static const int	m_iMapWidth;
	static const int	m_iMapHeight;

	//index into the array which is the start point
	static const int	m_iStartX;
	static const int	m_iStartY;

	//and the finish point
	static const int	m_iEndX;
	static const int	m_iEndY;


public:

	//we can use this array as Bobs memory if rqd
	int					memory[MAP_HEIGHT][MAP_WIDTH];

	CBobsMap()
	{
		ResetMemory();

	}

	//takes a string of directions and see's how far Bob
	//can get. Returns a fitness score proportional to the 
	//distance reached from the exit.
	double TestRoute(const vector<int> &vecPath, CBobsMap &memory);

	//given a surface to draw on this function uses the windows GDI
	//to display the map.
	void Render(const int cxClient, const int cyClient, HDC surface);

	//draws whatever path may be stored in the memory
	void MemoryRender(const int cxClient, const int cyClient, HDC surface);

	void ResetMemory();


};



#endif



			