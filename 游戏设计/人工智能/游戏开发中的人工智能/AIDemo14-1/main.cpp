#include "main.h"
#include "time.h"
#include "MyNeuralNetwork.h"


#define		_TIMESTEP						0.0025
#define		_TOL							1e-10
#define		_FWDTIME						10
#define		_THRUSTFACTOR					1.0
#define     _CHASESETUP						true
#define		_SPAWN_AREA_R					300

#define		_MAX_NUM_UNITS					20

#define		_UNIT_LENGTH					4

#define		_WIDEVIEW_RADIUS_FACTOR				200
#define		_NARROWVIEW_RADIUS_FACTOR			50
#define		_LIMITEDVIEW_RADIUS_FACTOR			30
#define		_CRITICAL_RADIUS_FACTOR				6

#define		_SEPARATION_FACTOR				5
#define		_BACK_VIEW_ANGLE_FACTOR			1
#define		_FRONT_VIEW_ANGLE_FACTOR		1

#define		_MAXHITPOINTS					500

// Global Variables:
int				FrameCounter = 0;
RigidBody2D		Units[_MAX_NUM_UNITS];
Vector			Target;

NeuralNetwork	TheBrain;

double			TrainingSet[14][7] = {	
0,		1,		0,		0.2,	0.9,	0.1,	0.1,
0,		1,		1,		0.2,	0.9,	0.1,	0.1,
0,		1,		0,		0.8,	0.1,	0.1,	0.1,
0.1,	0.5,	0,		0.2,	0.9,	0.1,	0.1,
0,		0.25,	1,		0.5,	0.1,	0.9,	0.1,
0,		0.2,	1,		0.2,	0.1,	0.1,	0.9,
0.3,	0.2,	0,		0.2,	0.9,	0.1,	0.1,
0,		0.2,	0,		0.3,	0.1,	0.9,	0.1,
0,		1,		0,		0.2,	0.1,	0.9,	0.1,
0,		1,		1,		0.6,	0.1,	0.1,	0.1,
0,		1,		0,		0.8,	0.1,	0.9,	0.1,
0.1,	0.2,	0,		0.2,	0.1,	0.1,	0.9,
0,		0.25,	1,		0.5,	0.1,	0.1,	0.9,
0,		0.6,	0,		0.2,	0.1,	0.1,	0.9
};


/*
double			TrainingSet[14][8] = {	
0,		1,		0,		0.2,	0.9,	0.1,	0.1,	0,
0,		1,		1,		0.2,	0.9,	0.1,	0.1,	0,
0,		1,		0,		0.8,	0.1,	0.1,	0.1,	1,
0.1,	0.5,	0,		0.2,	0.9,	0.1,	0.1,	0,
0,		0.25,	1,		0.5,	0.1,	0.9,	0.1,	0,
0,		0.2,	1,		0.2,	0.1,	0.1,	0.9,	0,
0.3,	0.2,	0,		0.2,	0.9,	0.1,	0.1,	0,
0,		0.2,	0,		0.3,	0.1,	0.9,	0.1,	0,
0,		1,		0,		0.2,	0.1,	0.9,	0.1,	1,
0,		1,		1,		0.6,	0.1,	0.1,	0.1,	1,
0,		1,		0,		0.8,	0.1,	0.9,	0.1,	0,
0.1,	0.2,	0,		0.2,	0.1,	0.1,	0.9,	0,
0,		0.25,	1,		0.5,	0.1,	0.1,	0.9,	0,
0,		0.6,	0,		0.2,	0.1,	0.1,	0.9,	0
};
*/


double			DamageRate = 0.4;


void	TrainTheBrain(void)
{
	int		i;
	double	error = 1;
	int		c = 0;	
	
	TheBrain.DumpData("PreTraining.txt");

	while((error > 0.05) && (c<50000))
	{
		error = 0;
		c++;
		for(i=0; i<14; i++)
		{
			TheBrain.SetInput(0, TrainingSet[i][0]);	
			TheBrain.SetInput(1, TrainingSet[i][1]);	
			TheBrain.SetInput(2, TrainingSet[i][2]);
			TheBrain.SetInput(3, TrainingSet[i][3]);

							
			TheBrain.SetDesiredOutput(0, TrainingSet[i][4]);	
			TheBrain.SetDesiredOutput(1, TrainingSet[i][5]);	
			TheBrain.SetDesiredOutput(2, TrainingSet[i][6]);
			//TheBrain.SetDesiredOutput(3, TrainingSet[i][7]);
	
			TheBrain.FeedForward();
			error += TheBrain.CalculateError();
			TheBrain.BackPropagate();

		}
		error = error / 14.0f;		
	}

	//c = c * 1;

	TheBrain.DumpData("PostTraining.txt");


}

void	ReTrainTheBrain(int i, double d0, double d1, double d2, double d3)
{
	double	error = 1;
	int		c = 0;	
	
	while((error > 0.1) && (c<5000))
	{
		
		c++;
		TheBrain.SetInput(0, Units[i].Inputs[0]);	
		TheBrain.SetInput(1, Units[i].Inputs[1]);		
		TheBrain.SetInput(2, Units[i].Inputs[2]);
		TheBrain.SetInput(3, Units[i].Inputs[3]);											
		TheBrain.SetDesiredOutput(0, d0);	
		TheBrain.SetDesiredOutput(1, d1);	
		TheBrain.SetDesiredOutput(2, d2);
		//TheBrain.SetDesiredOutput(3, d3);
	
		TheBrain.FeedForward();
		error = TheBrain.CalculateError();
		TheBrain.BackPropagate();		
	}

	//c = c * 1;
}

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

		Units[i].ThrustForce = _THRUSTFORCE;
		Units[i].HitPoints = _MAXHITPOINTS;
		Units[i].Chase = false;
		Units[i].Flock = false;
		Units[i].Evade = false;
		Units[i].Wander = true;

	}

	Units[0].vPosition.x = 0;
	Units[0].vPosition.y = 0;
	Units[0].fOrientation = 45;
	Units[0].HitPoints = _MAXHITPOINTS;
	Units[0].ThrustForce = _THRUSTFORCE*2;

	TheBrain.Initialize(4, 3, 3/*4*/);
	TheBrain.SetLearningRate(0.2);
	TheBrain.SetMomentum(true, 0.9);
	TrainTheBrain();


	return true;
}

void	Finalize(void)
{
	TheBrain.DumpData("Final.txt");
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
		int		Nf, Na;
		bool	InView;		
		int		RadiusFactor;

		// begin Flock AI
		Fs.x = Fs.y = Fs.z = 0;
		Pave.x = Pave.y = Pave.z = 0;
		Vave.x = Vave.y = Vave.z = 0;
		N = 0;
		Pfs.x = 0;
		Pfs.y = Units[i].fLength / 2.0f;
		Nf = 0;
		Na = 0;
		
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

				if(d.Magnitude() <= (Units[i].fLength * _LIMITEDVIEW_RADIUS_FACTOR))
						Na++;

				if(Units[i].Flock)
				{
					InView = (w.y > 0);
					RadiusFactor = _LIMITEDVIEW_RADIUS_FACTOR;
				}
				
				if(InView)			
				{
					if(d.Magnitude() <= (Units[i].fLength * RadiusFactor))
					{
						Pave += Units[j].vPosition;
						Vave += Units[j].vVelocity;
						N++;
					}
				}

				if(!Units[i].Flock) // even if we're not flocking keep the units apart
				{
					InView = ((w.y > 0) || ((w.y < 0) && (fabs(w.x) > fabs(w.y)*_BACK_VIEW_ANGLE_FACTOR)));
					RadiusFactor = _WIDEVIEW_RADIUS_FACTOR;
				}						

				// Separation Rule:
				if(InView)
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

		Units[i].NumFriends = Na;
		

		// Cohesion Rule: 
		if(Units[i].Flock && (N > 0))
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
		if(Units[i].Flock && (N > 0))
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

		// Chase
		if(Units[i].Chase)
		{
			u = Units[0].vPosition;
			d = u - Units[i].vPosition;
			w = VRotate2D(-Units[i].fOrientation, d);
			if(w.x < 0) m = -1;
			if(w.x > 0) m = 1;
			Fs.x += m*_STEERINGFORCE;			
		}

		// Evade
		if(Units[i].Evade)
		{
			u = Units[0].vPosition;
			d = u - Units[i].vPosition;
			w = VRotate2D(-Units[i].fOrientation, d);
			if(w.x < 0) m = 1;
			if(w.x > 0) m = -1;
			Fs.x += m*_STEERINGFORCE;
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
	Vector	u;
	bool	kill = false;
	
	// initialize the back buffer
	if(FrameCounter >= _RENDER_FRAME_COUNT)
		ClearBackBuffer();
	
	// Update player controlled unit:	
	Units[0].SetThrusters(false, false, 1);
	Units[0].SetThrusters(false, false, 1);

	if (IsKeyDown(VK_RIGHT))
		Units[0].SetThrusters(true, false, 0.5);

	if (IsKeyDown(VK_LEFT))
		Units[0].SetThrusters(false, true, 0.5);

	if (IsKeyDown('0'))
		DamageRate = 0.0;
	if (IsKeyDown('1'))
		DamageRate = 0.2;
	if (IsKeyDown('2'))
		DamageRate = 0.4;
	if (IsKeyDown('3'))
		DamageRate = 0.6;
	if (IsKeyDown('4'))
		DamageRate = 0.8;
	if (IsKeyDown('5'))
		DamageRate = 1.0;
	if (IsKeyDown('6'))
		DamageRate = 1.2;
	if (IsKeyDown('7'))
		DamageRate = 1.4;
	if (IsKeyDown('8'))
		DamageRate = 1.6;
	if (IsKeyDown('9'))
		DamageRate = 1000.0;

	Units[0].UpdateBodyEuler(dt);
	if(FrameCounter >= _RENDER_FRAME_COUNT)
		DrawCraft(Units[0], RGB(0, 255, 0));

	if(Units[0].vPosition.x > _WINWIDTH) Units[0].vPosition.x = 0;
	if(Units[0].vPosition.x < 0) Units[0].vPosition.x = _WINWIDTH;
	if(Units[0].vPosition.y > _WINHEIGHT) Units[0].vPosition.y = 0;
	if(Units[0].vPosition.y < 0) Units[0].vPosition.y = _WINHEIGHT;

	// calc number of enemy units currently engaging the target
	Vector d;
	Units[0].NumFriends = 0;
	for(i=1; i<_MAX_NUM_UNITS; i++)
	{	
		d = Units[i].vPosition - Units[0].vPosition;
		if(d.Magnitude() <= (Units[0].fLength * _CRITICAL_RADIUS_FACTOR))
			Units[0].NumFriends++;
	}

	// deduct hit points from target
	if(Units[0].NumFriends > 0)
	{
		Units[0].HitPoints -= 0.2 * Units[0].NumFriends;
		if(Units[0].HitPoints < 0)
		{
			Units[0].vPosition.x = _WINWIDTH/2;
			Units[0].vPosition.y = _WINHEIGHT/2;
			Units[0].HitPoints = _MAXHITPOINTS;
			kill = true;
		}
	} else {
		//Units[0].HitPoints += 1;
		//if(Units[0].HitPoints > _MAXHITPOINTS) Units[0].HitPoints = _MAXHITPOINTS;
	}

	
	// update computer controlled units:	
	for(i=1; i<_MAX_NUM_UNITS; i++)
	{		
		u = Units[0].vPosition - Units[i].vPosition;
		if(kill)
		{				
			if((u.Magnitude() <= (Units[0].fLength * _CRITICAL_RADIUS_FACTOR)) /*&& (Units[i].Command != 2)*/)		
			{
				ReTrainTheBrain(i, 0.9, 0.1, 0.1, 0.1);
				Units[i].HitPoints += _MAXHITPOINTS/4.0f;
				if(Units[i].HitPoints > _MAXHITPOINTS) Units[i].HitPoints = _MAXHITPOINTS;
			}
		}				

		// handle enemy hitpoints, and learning if required
		if(u.Magnitude() <= (Units[0].fLength * _CRITICAL_RADIUS_FACTOR))		
		{
			Units[i].HitPoints -= DamageRate;
			if((Units[i].HitPoints < 0))
			{
				Units[i].vPosition.x = GetRandomNumber(_WINWIDTH/2-_SPAWN_AREA_R, _WINWIDTH/2+_SPAWN_AREA_R, false);
				Units[i].vPosition.y = GetRandomNumber(_WINHEIGHT/2-_SPAWN_AREA_R, _WINHEIGHT/2+_SPAWN_AREA_R, false);
				Units[i].HitPoints = _MAXHITPOINTS/2.0;
//				if(Units[i].Command == 0)
					ReTrainTheBrain(i, 0.1, 0.1, 0.9, 0.1);					
			}
		} else {
			Units[i].HitPoints+=0.01;
			if(Units[i].HitPoints > _MAXHITPOINTS) Units[i].HitPoints = _MAXHITPOINTS;
/*			if((Units[i].HitPoints < 0))
			{
				Units[i].vPosition.x = GetRandomNumber(_WINWIDTH/2-_SPAWN_AREA_R, _WINWIDTH/2+_SPAWN_AREA_R, false);
				Units[i].vPosition.y = GetRandomNumber(_WINHEIGHT/2-_SPAWN_AREA_R, _WINHEIGHT/2+_SPAWN_AREA_R, false);
				Units[i].HitPoints = _MAXHITPOINTS/2;
				if (Units[i].Command != 0)
					ReTrainTheBrain(i, 0.9, 0.1, 0.1, 0.1);					
			}*/
		}

		// get a new command
		Units[i].Inputs[0] = Units[i].NumFriends/_MAX_NUM_UNITS;
		Units[i].Inputs[1] = (double) (Units[i].HitPoints/_MAXHITPOINTS);
		Units[i].Inputs[2] = (Units[0].NumFriends>0 ? 1:0);
		Units[i].Inputs[3] = (u.Magnitude()/800.0f);
		
			
		TheBrain.SetInput(0, Units[i].Inputs[0]);	
		TheBrain.SetInput(1, Units[i].Inputs[1]);		
		TheBrain.SetInput(2, Units[i].Inputs[2]);
		TheBrain.SetInput(3, Units[i].Inputs[3]);			
		TheBrain.FeedForward();

		Units[i].Command = TheBrain.GetMaxOutputID();
		switch(Units[i].Command)
		{
			case 0: 
				Units[i].Chase = true;
				Units[i].Flock = false;
				Units[i].Evade = false;				
				Units[i].Wander = false;
				break;

			case 1:
				Units[i].Chase = false;
				Units[i].Flock = true;
				Units[i].Evade = false;
				Units[i].Wander = false;
				break;

			case 2:
				Units[i].Chase = false;
				Units[i].Flock = false;
				Units[i].Evade = true;
				Units[i].Wander = false;
				break;
			/*case 3:
				Units[i].Chase = false;
				Units[i].Flock = false;
				Units[i].Evade = true;
				Units[i].Wander = true;
				break;*/

		}

		DoUnitAI(i);
		
		Units[i].UpdateBodyEuler(dt);

		if(FrameCounter >= _RENDER_FRAME_COUNT)
		{
			if(Units[i].Command == 0)
				DrawCraft(Units[i], RGB(255,0,0));
			else if(Units[i].Command == 1)
				DrawCraft(Units[i], RGB(0,0,255));
			else if(Units[i].Command == 2)
				DrawCraft(Units[i], RGB(128,128,0));
			else
				DrawCraft(Units[i], RGB(0,128,128));


		}

		if(Units[i].vPosition.x > _WINWIDTH) Units[i].vPosition.x = 0;
		if(Units[i].vPosition.x < 0) Units[i].vPosition.x = _WINWIDTH;
		if(Units[i].vPosition.y > _WINHEIGHT) Units[i].vPosition.y = 0;
		if(Units[i].vPosition.y < 0) Units[i].vPosition.y = _WINHEIGHT;	
		
	} // end i-loop	

	kill = false;

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


