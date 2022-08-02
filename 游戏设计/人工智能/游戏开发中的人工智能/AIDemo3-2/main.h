#ifndef _MAINHEADER
#define _MAINHEADER

#include "winmain.h"
#include "mymath.h"
#include "RigidBody2D.h"


#define	_RENDER_FRAME_COUNT		6600

#define _PATROL_ARRAY_SIZE		2
#define _ZIGZAG_ARRAY_SIZE		4


struct	ControlData {
	bool	PThrusterActive;
	bool	SThrusterActive;
	double	dHeadingLimit;
	double	dPositionLimit;
	bool	LimitHeadingChange;
	bool	LimitPositionChange;
};

struct	StateChangeData {
	Vector	InitialHeading;
	Vector	InitialPosition;
	double	dHeading;
	double	dPosition;
	int		CurrentControlID;
};

void	UpdateSimulation(void);
bool	Initialize(void);
void	DrawCraft(RigidBody2D	craft, COLORREF clr);
void	DoCraft2Chase(void);
void	DoCraft2Evade(void);
void	DoCraft2Intercept(void);
void	DoAttractCraft2(void);
int		GetRandomNumber(int min, int max, bool seed);
Vector	GetVelocityIntersection(void);
void	DoCraft2ModulateThrust(void);

void	DoCraft2InterceptAlt(void);

void	InitializePatternTracking(void);
bool	DoPattern(ControlData *pPattern, int size);



#endif