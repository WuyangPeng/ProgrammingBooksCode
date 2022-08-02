#include "main.h"
#include "time.h"
//---------------------------------------------------------------------------
/*
Book:           AI for Game Developers
Authors:        David M. Bourg & Glenn Seemann
Example:        Flocking, Chapter 4
*/
//---------------------------------------------------------------------------




#define		_TIMESTEP						0.0025
#define		_TOL							1e-10
#define		_FWDTIME						10
#define		_THRUSTFACTOR					1.0
#define     _CHASESETUP						true
#define		_SPAWN_AREA_R					100

#define		_MAX_NUM_UNITS					20

#define		_UNIT_LENGTH					4

#define		_OBSTACLE_RADIUS_FACTOR			8
#define		_OBSTACLE_RADIUS				_OBSTACLE_RADIUS_FACTOR * _UNIT_LENGTH
#define		_COLLISION_VISIBILITY_FACTOR	25

#define		_WIDEVIEW_RADIUS_FACTOR				200
#define		_NARROWVIEW_RADIUS_FACTOR			50
#define		_LIMITEDVIEW_RADIUS_FACTOR			30

#define		_SEPARATION_FACTOR				5
#define		_BACK_VIEW_ANGLE_FACTOR			1
#define		_FRONT_VIEW_ANGLE_FACTOR		1

#define		_NUM_OBSTACLES					8





// Global Variables:
int				FrameCounter = 0;
RigidBody2D		Units[_MAX_NUM_UNITS];
Vector			Target;
Vector			Obstacles[_NUM_OBSTACLES];

bool	Initialize(void)
{
	int i;

	GetRandomNumber(0, _WINWIDTH, true);
			
	for(i=0; i<_MAX_NUM_UNITS; i++)
	{	
		Units[i].fMass = 10;
		Units[i].fInertia = 10;
		Units[i].fInertiaInverse = 1/10;
		Units[i].vPosition.x = GetRandomNumber(_WINWIDTH/2-_SPAWN_AREA_R, _WINWIDTH/2+_SPAWN_AREA_R, false);
		Units[i].vPosition.y = GetRandomNumber(_WINHEIGHT/2-_SPAWN_AREA_R, _WINHEIGHT/2+_SPAWN_AREA_R, false);
		Units[i].fWidth = _UNIT_LENGTH/2;
		Units[i].fLength = _UNIT_LENGTH;
		Units[i].fHeight = _UNIT_LENGTH;
		Units[i].fOrientation = GetRandomNumber(0, 360, false);	
		Units[i].CD.y = -0.12*Units[i].fLength;		Units[i].CD.x = 0.0f;			// coordinates of the body center of drag
		Units[i].CT.y = -0.50*Units[i].fLength;		Units[i].CT.x = 0.0f;			// coordinates of the propeller thrust vector
		Units[i].CPT.y = 0.5*Units[i].fLength;		Units[i].CPT.x = -0.5*Units[i].fWidth;	// coordinates of the port bow thruster
		Units[i].CST.y = 0.5*Units[i].fLength;		Units[i].CST.x = 0.5*Units[i].fWidth;	// coordinates of the starboard bow thruster

		Units[i].ProjectedArea = (Units[i].fLength + Units[i].fWidth) * Units[i].fHeight;

		Units[i].Leader = false;
		
		if(i>_MAX_NUM_UNITS/2)
		{
			Units[i].Interceptor = true;
			Units[i].ThrustForce = _THRUSTFORCE*1.5f;
		} else {
			Units[i].Interceptor = false;
			Units[i].ThrustForce = _THRUSTFORCE;
		}		

	}

	for(i=0; i<_NUM_OBSTACLES; i++)
	{
		Obstacles[i].x = GetRandomNumber(_OBSTACLE_RADIUS*4, _WINWIDTH-_OBSTACLE_RADIUS*4, false);
		Obstacles[i].y = /*_WINHEIGHT/2;*/GetRandomNumber(_OBSTACLE_RADIUS*4, _WINHEIGHT-_OBSTACLE_RADIUS*4, false);
	}

	return true;
}


void	DoUnitAI(int i)
{
		
		int		j;
		int		N;
		Vector	Pave;
		Vector	Vave;
		Vector	Fs;
		Vector	Pfs;
		Vector	d, u, v, w;
		double	m;
		int		Nf;
		bool	InView;
		bool	DoFlock = WideView || LimitedView || NarrowView;
		int		RadiusFactor;

		// begin Flock AI
		Fs.x = Fs.y = Fs.z = 0;
		Pave.x = Pave.y = Pave.z = 0;
		Vave.x = Vave.y = Vave.z = 0;
		N = 0;
		Pfs.x = 0;
		Pfs.y = Units[i].fLength / 2.0f;
		Nf = 0;
		
		for(j=1; j<_MAX_NUM_UNITS; j++)
		{
			if(i!=j)
			{
				InView = false;
				d = Units[j].vPosition - Units[i].vPosition;
				w = VRotate2D(-Units[i].fOrientation, d);
				
				if(((w.y > 0) && (fabs(w.x) < fabs(w.y)*_FRONT_VIEW_ANGLE_FACTOR))) 
					if(d.Magnitude() <= (Units[i].fLength * _NARROWVIEW_RADIUS_FACTOR))
						Nf++;

				if(WideView)
				{
					InView = ((w.y > 0) || ((w.y < 0) && (fabs(w.x) > fabs(w.y)*_BACK_VIEW_ANGLE_FACTOR)));
					RadiusFactor = _WIDEVIEW_RADIUS_FACTOR;
				}

				if(LimitedView)
				{
					InView = (w.y > 0);
					RadiusFactor = _LIMITEDVIEW_RADIUS_FACTOR;
				}

				if(NarrowView)
				{
					InView = (((w.y > 0) && (fabs(w.x) < fabs(w.y)*_FRONT_VIEW_ANGLE_FACTOR)));
					RadiusFactor = _NARROWVIEW_RADIUS_FACTOR;
				}
				
				if(InView && (Units[i].Interceptor == Units[j].Interceptor))			
				{
					if(d.Magnitude() <= (Units[i].fLength * RadiusFactor))
					{
						Pave += Units[j].vPosition;
						Vave += Units[j].vVelocity;
						N++;
					}
				}

				// Separation Rule:
				if(InView)//(w.y > 0) || ((w.y < 0) && (fabs(w.x) > fabs(w.y)*_BACK_VIEW_ANGLE_FACTOR)))
				{					
					if(d.Magnitude() <= (Units[i].fLength * _SEPARATION_FACTOR))
					{
						if(w.x < 0) m = 1;
						if(w.x > 0) m = -1;						
						
						Fs.x += m*_STEERINGFORCE * (Units[i].fLength * _SEPARATION_FACTOR) / d.Magnitude();
					}
				}
				
			}
		}
		

		// Cohesion Rule: 
		if(DoFlock && (N > 0))
		{
			Pave = Pave / N;
			v = Units[i].vVelocity;
			v.Normalize();
			u = Pave - Units[i].vPosition;
			u.Normalize();
			w = VRotate2D(-Units[i].fOrientation, u);
			if(w.x < 0) m = -1;
			if(w.x > 0) m = 1;
			if(fabs(v*u) < 1.0f)
				Fs.x += m * _STEERINGFORCE * acos(v * u) / pi;
		}

		// Alignment Rule:
		if(DoFlock && (N > 0))
		{
			Vave = Vave / N;
			u = Vave;
			u.Normalize();
			v = Units[i].vVelocity;
			v.Normalize();			
			w = VRotate2D(-Units[i].fOrientation, u);
			if(w.x < 0) m = -1;
			if(w.x > 0) m = 1;
			if(fabs(v*u) < 1)
				Fs.x += m * _STEERINGFORCE * acos(v * u) / pi;
		}

		// Chase the target if the unit is a leader
		if(Chase)
		{
			if(Nf == 0) 
				Units[i].Leader = true;
			else
				Units[i].Leader = false;

			if((Units[i].Leader || !DoFlock))
			{				
				if(!Units[i].Interceptor)
				{
					// Chase							
					u = Units[0].vPosition;
					d = u - Units[i].vPosition;
					w = VRotate2D(-Units[i].fOrientation, d);
					if(w.x < 0) m = -1;
					if(w.x > 0) m = 1;
					Fs.x += m*_STEERINGFORCE;
				} else {
					// Intercept		
					Vector	s1, s2, s12;
					double	tClose;	
					Vector	Vr12;

					Vr12 = Units[0].vVelocity-Units[i].vVelocity; // closing velocity
					s12 = Units[0].vPosition - Units[i].vPosition; // range to close
					tClose = s12.Magnitude() / Vr12.Magnitude(); // time to close

					s1 = Units[0].vPosition + (Units[0].vVelocity * tClose);
					Target = s1;
					s2 = s1 - Units[i].vPosition;	
					w = VRotate2D(-Units[i].fOrientation, s2);	
					if(w.x < 0) m = -1;
					if(w.x > 0) m = 1;
					Fs.x += m*_STEERINGFORCE;	
				}
			}
		}
		
		// Collision avoidance (with static obstacles)
		Vector	a, p, b;		
		
		for(j=0; j<_NUM_OBSTACLES; j++)
		{
			u = Units[i].vVelocity;
			u.Normalize();
			v = u * _COLLISION_VISIBILITY_FACTOR * Units[i].fLength;
			
			a = Obstacles[j] - Units[i].vPosition;
			p = (a * u) * u;
			b = p - a;

			if((b.Magnitude() < _OBSTACLE_RADIUS) && (p.Magnitude() < v.Magnitude()))
			{
				// impending collision...steer away
				w = VRotate2D(-Units[i].fOrientation, a);
				w.Normalize();
				if(w.x < 0) m = 1;
				if(w.x > 0) m = -1;
				Fs.x += m * _STEERINGFORCE * (_COLLISION_VISIBILITY_FACTOR * Units[i].fLength)/a.Magnitude();
			}
		}
		
		
		// apply accumulated steering force
		Units[i].Fa = Fs;
		Units[i].Pa = Pfs;
		// end Flock AI

}

void	UpdateSimulation(void)
{
	double	dt = _TIMESTEP;
	int		i;
	
	// initialize the back buffer
	if(FrameCounter >= _RENDER_FRAME_COUNT)
	{
		ClearBackBuffer();
		DrawObstacles();
	}
	
	// Update player controlled unit:	
	Units[0].SetThrusters(false, false, 1);
	Units[0].SetThrusters(false, false, 1);

	if (IsKeyDown(VK_RIGHT))
		Units[0].SetThrusters(true, false, 0.5);

	if (IsKeyDown(VK_LEFT))
		Units[0].SetThrusters(false, true, 0.5);

	Units[0].UpdateBodyEuler(dt);
	if(FrameCounter >= _RENDER_FRAME_COUNT)
		DrawCraft(Units[0], RGB(0, 255, 0));

	if(Units[0].vPosition.x > _WINWIDTH) Units[0].vPosition.x = 0;
	if(Units[0].vPosition.x < 0) Units[0].vPosition.x = _WINWIDTH;
	if(Units[0].vPosition.y > _WINHEIGHT) Units[0].vPosition.y = 0;
	if(Units[0].vPosition.y < 0) Units[0].vPosition.y = _WINHEIGHT;
	
	// update computer controlled units:	
	for(i=1; i<_MAX_NUM_UNITS; i++)
	{		
		DoUnitAI(i);
		
		Units[i].UpdateBodyEuler(dt);

		if(FrameCounter >= _RENDER_FRAME_COUNT)
		{
			if(Units[i].Leader)
				DrawCraft(Units[i], RGB(255,0,0));
			else {
				if(Units[i].Interceptor)
					DrawCraft(Units[i], RGB(255,0,255));		
				else
					DrawCraft(Units[i], RGB(0,0,255));
			}
		}

		if(Units[i].vPosition.x > _WINWIDTH) Units[i].vPosition.x = 0;
		if(Units[i].vPosition.x < 0) Units[i].vPosition.x = _WINWIDTH;
		if(Units[i].vPosition.y > _WINHEIGHT) Units[i].vPosition.y = 0;
		if(Units[i].vPosition.y < 0) Units[i].vPosition.y = _WINHEIGHT;		
	} // end i-loop	

	if(FrameCounter >= _RENDER_FRAME_COUNT) {
		CopyBackBufferToWindow();
		FrameCounter = 0;
	}  else
		FrameCounter++;
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
		double	f = 0.025;

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

void DrawObstacles(void)
{
	int		i;
	RECT	r;
	int		radius = _OBSTACLE_RADIUS/2;

	for(i=0; i<_NUM_OBSTACLES; i++)
	{
		SetRect(&r, Obstacles[i].x - radius, Obstacles[i].y - radius, Obstacles[i].x + radius, Obstacles[i].y + radius);
		DrawEllipse(&r, 2, RGB(255,0,0));

	}

}



/*
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
*/


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


