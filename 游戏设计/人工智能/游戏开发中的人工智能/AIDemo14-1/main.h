#ifndef _MAINHEADER
#define _MAINHEADER

#include "winmain.h"
#include "mymath.h"
#include "RigidBody2D.h"


#define	_RENDER_FRAME_COUNT		33


void	DoUnitAI(int i);
void	UpdateSimulation(void);
bool	Initialize(void);
void	DrawCraft(RigidBody2D	craft, COLORREF clr);
int		GetRandomNumber(int min, int max, bool seed);

void	TrainTheBrain(void);
void	ReTrainTheBrain(int i, double d0, double d1, double d2, double d3);

void	Finalize(void);




#endif