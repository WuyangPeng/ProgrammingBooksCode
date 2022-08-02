#include "main.h"
#include "time.h"
//---------------------------------------------------------------------------
/*
Book:           AI for Game Developers
Authors:        David M. Bourg & Glenn Seemann
Example:        Pattern movement in continuous environments, Chapter 3
*/
//---------------------------------------------------------------------------

// Global Variables:
int				FrameCounter = 0;
RigidBody2D		Craft1, Craft2; // TODO: change Craft1 to Player and Craft2 to Computer
Vector			Target;

ControlData		PatrolPattern[_PATROL_ARRAY_SIZE];
StateChangeData	PatternTracking;
ControlData		ZigZagPattern[_ZIGZAG_ARRAY_SIZE];

ControlData		ComplexPattern[10];

#define		_TIMESTEP		0.0005
#define		_TOL			1e-10
#define		_FWDTIME		10
#define		_THRUSTFACTOR	1.0
#define     _CHASESETUP		true

bool	Initialize(void)
{
	
	Craft1.fMass = 10;
	Craft1.fInertia = 10;
	Craft1.fInertiaInverse = 1/10;
	Craft1.vPosition.x = _WINWIDTH-60;
	Craft1.vPosition.y = _WINHEIGHT*0.8;
	Craft1.fWidth = 10;
	Craft1.fLength = 20;
	Craft1.fHeight = 5;
	Craft1.fOrientation = 135;	
	Craft1.CD.y = -0.12*Craft1.fLength;		Craft1.CD.x = 0.0f;			// coordinates of the body center of drag
	Craft1.CT.y = -0.50*Craft1.fLength;		Craft1.CT.x = 0.0f;			// coordinates of the propeller thrust vector
	Craft1.CPT.y = 0.5*Craft1.fLength;		Craft1.CPT.x = -0.5*Craft1.fWidth;	// coordinates of the port bow thruster
	Craft1.CST.y = 0.5*Craft1.fLength;		Craft1.CST.x = 0.5*Craft1.fWidth;	// coordinates of the starboard bow thruster

	Craft1.ProjectedArea = (Craft1.fLength + Craft1.fWidth) * Craft1.fHeight;
	Craft1.ThrustForce = _THRUSTFORCE*1;


	Craft2.fMass = 10;
	Craft2.fInertia = 10;
	Craft2.fInertiaInverse = 1/10;
	if(_CHASESETUP)
	{
		Craft2.vPosition.x = 200;
		Craft2.vPosition.y = 250;//_WINHEIGHT*0.5;
	} else {
		Craft2.vPosition.x = Craft1.vPosition.x - Craft1.fLength*8;
		Craft2.vPosition.y = Craft1.vPosition.y - Craft1.fLength*4;
	}

	Craft2.fWidth = 10;
	Craft2.fLength = 20;
	Craft2.fHeight = 5;
	if(_CHASESETUP)
		Craft2.fOrientation = -90;
	else
		Craft2.fOrientation = 90;
	Craft2.CD.y = -0.12*Craft2.fLength;		Craft2.CD.x = 0.0f;			// coordinates of the body center of drag
	Craft2.CT.y = -0.50*Craft2.fLength;		Craft2.CT.x = 0.0f;			// coordinates of the propeller thrust vector
	Craft2.CPT.y = 0.5*Craft2.fLength;		Craft2.CPT.x = 0.5*Craft2.fWidth;	// coordinates of the port bow thruster
	Craft2.CST.y = 0.5*Craft2.fLength;		Craft2.CST.x = -0.5*Craft2.fWidth;	// coordinates of the starboard bow thruster

	Craft2.ProjectedArea = (Craft2.fLength + Craft2.fWidth) * Craft2.fHeight;
	Craft2.ThrustForce = _THRUSTFORCE*_THRUSTFACTOR;

	
	// initialize the patterns here:	
	PatrolPattern[0].LimitPositionChange = true;
	PatrolPattern[0].LimitHeadingChange = false;
	PatrolPattern[0].dHeadingLimit = 0;	
	PatrolPattern[0].dPositionLimit = 200;
	PatrolPattern[0].PThrusterActive = false;
	PatrolPattern[0].SThrusterActive = false;

	PatrolPattern[1].LimitPositionChange = false;
	PatrolPattern[1].LimitHeadingChange = true;
	PatrolPattern[1].dHeadingLimit = 90;	
	PatrolPattern[1].dPositionLimit = 0;
	PatrolPattern[1].PThrusterActive = true;
	PatrolPattern[1].SThrusterActive = false;

/*	PatrolPattern[2].LimitPositionChange = true;
	PatrolPattern[2].LimitHeadingChange = false;
	PatrolPattern[2].dHeadingLimit = 0;	
	PatrolPattern[2].dPositionLimit = 200;
	PatrolPattern[2].PThrusterActive = false;
	PatrolPattern[2].SThrusterActive = false;

	PatrolPattern[3].LimitPositionChange = false;
	PatrolPattern[3].LimitHeadingChange = true;
	PatrolPattern[3].dHeadingLimit = 90;	
	PatrolPattern[3].dPositionLimit = 0;
	PatrolPattern[3].PThrusterActive = true;
	PatrolPattern[3].SThrusterActive = false;

	PatrolPattern[4].LimitPositionChange = true;
	PatrolPattern[4].LimitHeadingChange = false;
	PatrolPattern[4].dHeadingLimit = 0;	
	PatrolPattern[4].dPositionLimit = 200;
	PatrolPattern[4].PThrusterActive = false;
	PatrolPattern[4].SThrusterActive = false;

	PatrolPattern[5].LimitPositionChange = false;
	PatrolPattern[5].LimitHeadingChange = true;
	PatrolPattern[5].dHeadingLimit = 90;	
	PatrolPattern[5].dPositionLimit = 0;
	PatrolPattern[5].PThrusterActive = true;
	PatrolPattern[5].SThrusterActive = false;

	PatrolPattern[6].LimitPositionChange = true;
	PatrolPattern[6].LimitHeadingChange = false;
	PatrolPattern[6].dHeadingLimit = 0;	
	PatrolPattern[6].dPositionLimit = 200;
	PatrolPattern[6].PThrusterActive = false;
	PatrolPattern[6].SThrusterActive = false;

	PatrolPattern[7].LimitPositionChange = false;
	PatrolPattern[7].LimitHeadingChange = true;
	PatrolPattern[7].dHeadingLimit = 90;	
	PatrolPattern[7].dPositionLimit = 0;
	PatrolPattern[7].PThrusterActive = true;
	PatrolPattern[7].SThrusterActive = false;
*/

	ZigZagPattern[0].LimitPositionChange = true;
	ZigZagPattern[0].LimitHeadingChange = false;
	ZigZagPattern[0].dHeadingLimit = 0;	
	ZigZagPattern[0].dPositionLimit = 100;
	ZigZagPattern[0].PThrusterActive = false;
	ZigZagPattern[0].SThrusterActive = false;

	ZigZagPattern[1].LimitPositionChange = false;
	ZigZagPattern[1].LimitHeadingChange = true;
	ZigZagPattern[1].dHeadingLimit = 60;	
	ZigZagPattern[1].dPositionLimit = 0;
	ZigZagPattern[1].PThrusterActive = true;
	ZigZagPattern[1].SThrusterActive = false;

	ZigZagPattern[2].LimitPositionChange = true;
	ZigZagPattern[2].LimitHeadingChange = false;
	ZigZagPattern[2].dHeadingLimit = 0;	
	ZigZagPattern[2].dPositionLimit = 100;
	ZigZagPattern[2].PThrusterActive = false;
	ZigZagPattern[2].SThrusterActive = false;

	ZigZagPattern[3].LimitPositionChange = false;
	ZigZagPattern[3].LimitHeadingChange = true;
	ZigZagPattern[3].dHeadingLimit = 60;	
	ZigZagPattern[3].dPositionLimit = 0;
	ZigZagPattern[3].PThrusterActive = false;
	ZigZagPattern[3].SThrusterActive = true;



	ComplexPattern[0].LimitPositionChange = true;
	ComplexPattern[0].LimitHeadingChange = false;
	ComplexPattern[0].dHeadingLimit = 0;	
	ComplexPattern[0].dPositionLimit = 200;
	ComplexPattern[0].PThrusterActive = false;
	ComplexPattern[0].SThrusterActive = false;

	ComplexPattern[1].LimitPositionChange = false;
	ComplexPattern[1].LimitHeadingChange = true;
	ComplexPattern[1].dHeadingLimit = 135;	
	ComplexPattern[1].dPositionLimit = 0;
	ComplexPattern[1].PThrusterActive = true;
	ComplexPattern[1].SThrusterActive = false;

	ComplexPattern[2].LimitPositionChange = false;
	ComplexPattern[2].LimitHeadingChange = true;
	ComplexPattern[2].dHeadingLimit = 135;	
	ComplexPattern[2].dPositionLimit = 0;
	ComplexPattern[2].PThrusterActive = false;
	ComplexPattern[2].SThrusterActive = true;

	ComplexPattern[3].LimitPositionChange = true;
	ComplexPattern[3].LimitHeadingChange = false;
	ComplexPattern[3].dHeadingLimit = 0;	
	ComplexPattern[3].dPositionLimit = 50;
	ComplexPattern[3].PThrusterActive = false;
	ComplexPattern[3].SThrusterActive = false;

	ComplexPattern[4].LimitPositionChange = false;
	ComplexPattern[4].LimitHeadingChange = true;
	ComplexPattern[4].dHeadingLimit = 80;	
	ComplexPattern[4].dPositionLimit = 0;
	ComplexPattern[4].PThrusterActive = false;
	ComplexPattern[4].SThrusterActive = true;

	ComplexPattern[5].LimitPositionChange = true;
	ComplexPattern[5].LimitHeadingChange = false;
	ComplexPattern[5].dHeadingLimit = 0;	
	ComplexPattern[5].dPositionLimit = 200;
	ComplexPattern[5].PThrusterActive = false;
	ComplexPattern[5].SThrusterActive = false;

	ComplexPattern[6].LimitPositionChange = false;
	ComplexPattern[6].LimitHeadingChange = true;
	ComplexPattern[6].dHeadingLimit = 90;	
	ComplexPattern[6].dPositionLimit = 0;
	ComplexPattern[6].PThrusterActive = false;
	ComplexPattern[6].SThrusterActive = true;

	ComplexPattern[7].LimitPositionChange = true;
	ComplexPattern[7].LimitHeadingChange = false;
	ComplexPattern[7].dHeadingLimit = 0;	
	ComplexPattern[7].dPositionLimit = 250;
	ComplexPattern[7].PThrusterActive = false;
	ComplexPattern[7].SThrusterActive = false;

	ComplexPattern[8].LimitPositionChange = false;
	ComplexPattern[8].LimitHeadingChange = true;
	ComplexPattern[8].dHeadingLimit = 90;	
	ComplexPattern[8].dPositionLimit = 0;
	ComplexPattern[8].PThrusterActive = false;
	ComplexPattern[8].SThrusterActive = true;

	ComplexPattern[9].LimitPositionChange = true;
	ComplexPattern[9].LimitHeadingChange = false;
	ComplexPattern[9].dHeadingLimit = 0;	
	ComplexPattern[9].dPositionLimit = 50;
	ComplexPattern[9].PThrusterActive = false;
	ComplexPattern[9].SThrusterActive = false;



	InitializePatternTracking();

	
	return true;
}


void	UpdateSimulation(void)
{
	double	dt = _TIMESTEP;
	RECT	r;
	
	Craft1.SetThrusters(false, false, 1);
	
	if (IsKeyDown(VK_UP))
		Craft1.ModulateThrust(true);
	
	if (IsKeyDown(VK_DOWN))
		Craft1.ModulateThrust(false);
		
	if (IsKeyDown(VK_RIGHT))
		Craft1.SetThrusters(true, false, 1);

	if (IsKeyDown(VK_LEFT))
		Craft1.SetThrusters(false, true, 1);

	// Do craft 2 AI

	Craft2.Fa.x = 0;
	Craft2.Fa.y = 0;
	Craft2.Pa.x = 0;
	Craft2.Pa.y = 0;

	if(BasicChase)
	{
		DoCraft2Chase();
		DoCraft2ModulateThrust();
	}
	if(BasicEvade)
		DoCraft2Evade();
	if(InterceptChase)
	{		
		DoCraft2InterceptAlt();	
	}
	if(PotentialChase)
		DoAttractCraft2();

	if(Patrol)
	{
		if(!DoPattern(PatrolPattern, _PATROL_ARRAY_SIZE))
			InitializePatternTracking();
	}
	
	if(ZigZag)
	{
		if(!DoPattern(ComplexPattern/*ZigZagPattern*/, 10/*_ZIGZAG_ARRAY_SIZE*/))
			InitializePatternTracking();
	}
	
	// update the simulation 
	//Craft1.UpdateBodyEuler(dt);
	Craft2.UpdateBodyEuler(dt);

	if(FrameCounter >= _RENDER_FRAME_COUNT)
	{	
		
		// update the display
		if(!ShowTrails)
			ClearBackBuffer();

		DrawCraft(Craft1, RGB(0,0,255));
		DrawCraft(Craft2, RGB(255,0,0));

		RECT	r;
		
		r.left = (int) (Target.x-3);
		r.top = (int) (Target.y-3);
		r.right = (int) (Target.x+3);
		r.bottom = (int) (Target.y+3);
		DrawEllipse(&r, 1, RGB(0,255,0));

		CopyBackBufferToWindow();
		FrameCounter = 0;

	} else
		FrameCounter++;

	if(Craft1.vPosition.x > _WINWIDTH) Craft1.vPosition.x = 0;
	if(Craft1.vPosition.x < 0) Craft1.vPosition.x = _WINWIDTH;
	if(Craft1.vPosition.y > _WINHEIGHT) Craft1.vPosition.y = 0;
	if(Craft1.vPosition.y < 0) Craft1.vPosition.y = _WINHEIGHT;

	if(Craft2.vPosition.x > _WINWIDTH) Craft2.vPosition.x = 0;
	if(Craft2.vPosition.x < 0) Craft2.vPosition.x = _WINWIDTH;
	if(Craft2.vPosition.y > _WINHEIGHT) Craft2.vPosition.y = 0;
	if(Craft2.vPosition.y < 0) Craft2.vPosition.y = _WINHEIGHT;


}

void	InitializePatternTracking(void) 
{
	PatternTracking.CurrentControlID = 0;
	PatternTracking.dPosition = 0;
	PatternTracking.dHeading = 0;

	PatternTracking.InitialPosition = Craft2.vPosition;
	PatternTracking.InitialHeading = Craft2.vVelocity;	
	PatternTracking.InitialHeading.Normalize();
}

bool	DoPattern(ControlData *pPattern, int size)
{
	int		i = PatternTracking.CurrentControlID;
	Vector	u;
	
	if( (pPattern[i].LimitPositionChange && (PatternTracking.dPosition >= pPattern[i].dPositionLimit)) ||
		(pPattern[i].LimitHeadingChange && (PatternTracking.dHeading >= pPattern[i].dHeadingLimit)) )
	{
		InitializePatternTracking();
		i++;
		PatternTracking.CurrentControlID = i;
		if(PatternTracking.CurrentControlID >= size)
			return false;
	}
	
	if(pPattern[i].LimitHeadingChange)
	{
		u = Craft2.vVelocity;
		u.Normalize();
		double P;
		P = PatternTracking.InitialHeading * u;
		/*if(P < 1)
			PatternTracking.dHeading = fabs(acos(PatternTracking.InitialHeading * u) * 180 / pi);
		else
			PatternTracking.dHeading = 0;*/
		
		PatternTracking.dHeading = fabs(acos(PatternTracking.InitialHeading * u) * 180 / pi);

	
		
	}
		
	if(pPattern[i].LimitPositionChange)
	{
		u = Craft2.vPosition - PatternTracking.InitialPosition;
		PatternTracking.dPosition = u.Magnitude();
	}

	double f;
	if(pPattern[i].LimitHeadingChange)
		f = 1 - PatternTracking.dHeading / pPattern[i].dHeadingLimit;
	else
		f = 1;

	if(f < 0.05) f = 0.05;

	Craft2.SetThrusters(pPattern[i].PThrusterActive, pPattern[i].SThrusterActive, f);


	return true;	
		
}



void	DrawCraft(RigidBody2D	craft, COLORREF clr)
{
	Vector	vList[5];
	double	wd, lg;
	int		i;
	Vector	v1;

	wd = craft.fWidth;
	lg = craft.fLength;
	vList[0].y = lg/2;	vList[0].x = wd/2;
	vList[1].y = -lg/2;	vList[1].x = wd/2;
	vList[2].y = -lg/2;	vList[2].x = -wd/2;
	vList[3].y = lg/2;	vList[3].x = -wd/2;
	vList[4].y = lg/2*1.5; vList[4].x = 0;
	for(i=0; i<5; i++)
	{
		v1 = VRotate2D(craft.fOrientation, vList[i]);
		vList[i] = v1 + craft.vPosition;			
	}

	DrawLine(vList[0].x, vList[0].y, vList[1].x, vList[1].y, 2, clr);
	DrawLine(vList[1].x, vList[1].y, vList[2].x, vList[2].y, 2, clr);
	DrawLine(vList[2].x, vList[2].y, vList[3].x, vList[3].y, 2, clr);
	DrawLine(vList[3].x, vList[3].y, vList[4].x, vList[4].y, 2, clr);
	DrawLine(vList[4].x, vList[4].y, vList[0].x, vList[0].y, 2, clr);

	if(ShowVectors)
	{
		Vector	v, u;
		double	f = 5;

		// Show velocity vectors in green
		DrawLine(craft.vPosition.x, craft.vPosition.y, craft.vPosition.x+craft.vVelocity.x, craft.vPosition.y+craft.vVelocity.y, 3, RGB(0,255,0));
		
		// Show force vectors in black
		// thrust vector
		v.x = 0;
		v.y = craft.ThrustForce*f;
		v = VRotate2D(craft.fOrientation, v);
		u.x = craft.CT.x;
		u.y = craft.CT.y;
		u = VRotate2D(craft.fOrientation, u);
		DrawLine(craft.vPosition.x+u.x, craft.vPosition.y+u.y, craft.vPosition.x + u.x + v.x, craft.vPosition.y + u.y + v.y, 1, RGB(0,0,0));

		// port steering force
		v.x = craft.PThrust.x*f;
		v.y = craft.PThrust.y*f;
		v = VRotate2D(craft.fOrientation, v);
		u.x = craft.CPT.x;
		u.y = craft.CPT.y;
		u = VRotate2D(craft.fOrientation, u);
		DrawLine(craft.vPosition.x+u.x, craft.vPosition.y+u.y, craft.vPosition.x + u.x + v.x, craft.vPosition.y + u.y + v.y, 1, RGB(0,0,0));

		// stbd steering force
		v.x = craft.SThrust.x*f;
		v.y = craft.SThrust.y*f;
		v = VRotate2D(craft.fOrientation, v);
		u.x = craft.CST.x;
		u.y = craft.CST.y;
		u = VRotate2D(craft.fOrientation, u);
		DrawLine(craft.vPosition.x+u.x, craft.vPosition.y+u.y, craft.vPosition.x + u.x + v.x, craft.vPosition.y + u.y + v.y, 1, RGB(0,0,0));

		// applied force
		v.x = craft.Fa.x*f;
		v.y = craft.Fa.y*f;
		v = VRotate2D(craft.fOrientation, v);
		u.x = craft.Pa.x;
		u.y = craft.Pa.y;
		u = VRotate2D(craft.fOrientation, u);
		DrawLine(craft.vPosition.x+u.x, craft.vPosition.y+u.y, craft.vPosition.x + u.x + v.x, craft.vPosition.y + u.y + v.y, 1, RGB(0,0,0));

	}

}

void	DoCraft2Chase(void)
{
	Vector	u, v;
	bool	p = false;
	bool	s = false;
	
	u = VRotate2D(-Craft2.fOrientation, (Craft1.vPosition - Craft2.vPosition));
	u.Normalize();

	Target = Craft1.vPosition;

	if(u.x < -_TOL)
		p = true;
	else if(u.x > _TOL)
		s = true;
		
	Craft2.SetThrusters(p,s, 1);
}

void	DoCraft2Evade(void)
{
	Vector	u, v;
	bool	p = false;
	bool	s = false;
	
	u = VRotate2D(-Craft2.fOrientation, (Craft1.vPosition - Craft2.vPosition));
	u.Normalize();

	if(u.x > 0)
		p = true;
	else if(u.x < 0)
		s = true;

	Craft2.SetThrusters(p,s, 1);

	Target = Craft2.vPosition;
}

void	DoCraft2Intercept(void)
{
	Vector	u1, u2, u;
	Vector	s1, s2;
	Vector  Vr;
	double	t1, t2;
	Vector	s1unit, s2unit;
	bool	p = false;
	bool	s = false;

	Vr = Craft1.vVelocity - Craft2.vVelocity;

	s2 = GetVelocityIntersection() - Craft2.vPosition;
	s2unit = s2;
	s2unit.Normalize();
	u2 = VRotate2D(-Craft2.fOrientation, s2);
	t2 = s2.Magnitude()/(Vr * s2unit);
	
	s1 = Craft1.vPosition - Craft2.vPosition;
	s1unit = s1;
	s1unit.Normalize();
	u1 = VRotate2D(-Craft2.fOrientation, s1);
	t1 = s1.Magnitude()/(Vr * s1unit);

	if(t1 < 0.0)
	{
		u = u2;
		Target = s2 + Craft2.vPosition;
	} else if(t2 < 0.0) {
		u = u1;
		Target = s1 + Craft2.vPosition;
	} else if(t2 < t1)
	{
		u = u2;
		Target = s2 + Craft2.vPosition;
	} else {
		u = u1;
		Target = s1 + Craft2.vPosition;
	}
	u.Normalize();

	if(u.x < -_TOL)
		p = true;
	else if(u.x > _TOL)
		s = true;

	Craft2.SetThrusters(p,s, 1);
}

/*Old version
void	DoCraft2Intercept(void)
{
	Vector	u1, u2, u3, u;
	Vector	s1, s2, s3;
	Vector  Vr1, Vr2, Vr3;
	double	t1, t2, t3;
	bool	p = false;
	bool	s = false;

	// todo: change variable subscripts to  be consistent with craft #...

	s3 = Craft1.vPosition - Craft2.vPosition;
	u3 = VRotate2D(-Craft2.fOrientation, s3);
	if(u3.y < -_TOL)
	{
		if(GetRandomNumber(0, 10, true) < 5)
			p = true;
		else
			s = true;
		Craft2.SetThrusters(p,s);
		Target = Craft2.vPosition;
		return;
	}



	Vr1 = Craft1.vVelocity - Craft2.vVelocity;
	Vr2 = Craft1.vVelocity - Craft2.vVelocity;

	s1 = GetVelocityIntersection() - Craft2.vPosition;
	u1 = VRotate2D(-Craft2.fOrientation, s1);
	t1 = s1.Magnitude()/(Vr1 * s1);
	
	s2 = Craft1.vPosition - Craft2.vPosition;
	u2 = VRotate2D(-Craft2.fOrientation, s2);
	t2 = s2.Magnitude()/(Vr2 * s2);

	if(t1 < t2)
	{
		u = u1;
		Target = s1 + Craft2.vPosition;
	} else {
		u = u2;
		Target = s2 + Craft2.vPosition;
	}
	u.Normalize();

	if(u.x < -_TOL)
		p = true;
	else if(u.x > _TOL)
		s = true;
	else if(u.x == _TOL) {
		if(GetRandomNumber(0, 10, true) < 5)
			p = true;
		else
			s = true;
	}

	Craft2.SetThrusters(p,s);
}*/


void	DoCraft2InterceptAlt(void)
{
	Vector	u;
	Vector	s1, s2, s12;
	bool	p = false;
	bool	s = false;
	double	tClose;	
	Vector	Vr12;
	double	vr;
	
	// turn around if we get ahead of the prey...
	s12 = Craft1.vPosition - Craft2.vPosition;
	u = VRotate2D(-Craft2.fOrientation, s12);
	if(u.y < -_TOL)
	{
		//if(GetRandomNumber(0, 10, true) < 5)
			p = true;
		//else
		//	s = true;
		Craft2.SetThrusters(p,s, 1);
		Target = Craft2.vPosition;
		return;
	}

	Vr12 = Craft1.vVelocity-Craft2.vVelocity; // closing velocity
	s12 = Craft1.vPosition - Craft2.vPosition; // range to close
	tClose = s12.Magnitude() / Vr12.Magnitude(); // time to close

	s1 = Craft1.vPosition + (Craft1.vVelocity * tClose);
	Target = s1;
	s2 = s1 - Craft2.vPosition;	
	u = VRotate2D(-Craft2.fOrientation, s2);	

	u.Normalize();
	if(u.x < -_TOL)
		p = true;
	else if(u.x > _TOL)
		s = true;

	Craft2.SetThrusters(p,s, 1);
	
}



void	DoAttractCraft2(void)
{
	// Apply Leonard-Jones potential force to Craft2
	// todo: make sure rigidbody calcloads function handles it
	Vector	r = Craft2.vPosition - Craft1.vPosition;
	Vector  u = r;

	u.Normalize();

	double	k1 = 0.5e2; // repel
	double	k2 = 1.0e2; // attract

	Craft2.Fa = VRotate2D( -Craft2.fOrientation, ((k1*pow(Craft2.fLength*5/r.Magnitude(), 4) - k2*pow(Craft2.fLength*3/r.Magnitude(), 2)) ) * u);
	Craft2.Pa.x = 0;
	Craft2.Pa.y = Craft2.fLength / 2;

	Target = Craft1.vPosition;
	
}

Vector	GetVelocityIntersection(void)
{
	double s, t, num, denom;
	Vector	a,b,c,d;

	a = Craft1.vPosition;
	b = a+Craft1.vVelocity;
	c = Craft2.vPosition;
	d = c+Craft2.vVelocity;

	denom = a.x * (d.y-c.y) +
			b.x * (c.y-d.y) +
			d.x * (b.y-a.y) +
			c.x * (a.y-b.y);

	if(denom == 0)
		return Vector(a.x, a.y, 0);

	num =	a.x * (d.y-c.y) +
			c.x * (a.y-d.y) +
			d.x * (c.y-a.y);
	s = num/denom;

	num =	-( a.x * (c.y-b.y) +
			   b.x * (a.y-c.y) +
			   c.x * (b.y-a.y) );
	t = num/denom;

	if( (s >= 0) && (t >= 0) )
		return Vector(a.x+s*(b.x-a.x), a.y+s*(b.y-a.y),0);
	else
		return Vector(a.x, a.y, 0);

}



int GetRandomNumber(int min, int max, bool seed)
{
	int	number;	

	if(seed)
		srand( (unsigned)time( NULL ) );
		
    number = (((abs(rand())%(max-min+1))+min));    
    
    if(number>max)
		number = max;

    if(number<min)
    	number = min;
		
	return number;
}

void	DoCraft2ModulateThrust(void)
{
	Vector	r = Craft1.vPosition - Craft2.vPosition;
	double	dmax = Craft2.fLength * 10;

	if((Craft2.PThrust.Magnitude() > 0) || (Craft2.SThrust.Magnitude() > 0)) // turning
	{
		if(r.Magnitude() > dmax)
			Craft2.ThrustForce = _MAXTHRUST;
		else
			Craft2.ThrustForce = r.Magnitude() / dmax * _MAXTHRUST;
	} else {		
		// todo: check how close we are to target and adjust speed to stay with it
		Craft2.ThrustForce = _MAXTHRUST;
	}

}



