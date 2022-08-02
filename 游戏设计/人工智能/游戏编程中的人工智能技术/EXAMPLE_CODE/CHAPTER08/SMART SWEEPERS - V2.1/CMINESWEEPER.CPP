#include "CMinesweeper.h"

//-----------------------------------constructor-------------------------
//
//-----------------------------------------------------------------------
CMinesweeper::CMinesweeper():
                             m_dRotation(RandFloat() * CParams::dTwoPi),
                             m_lTrack(0.16),
                             m_rTrack(0.16),
							               m_dScale(CParams::iSweeperScale),
                             m_bCollided(false),
                             m_dSpinBonus(0),
                             m_dCollisionBonus(0)
                             
			 
{
  //create a static start position
  m_vPosition = SVector2D(180, 200);

   //create the sensors
  CreateSensors(m_Sensors, CParams::iNumSensors, CParams::dSensorRange); 
}


//-------------------------------- CreateSensors ------------------------
//
//	This function returns a vector of points which make up the segments of
//  the sweepers sensors.
//------------------------------------------------------------------------
void CMinesweeper::CreateSensors(vector<SPoint> &sensors,
                                 int            NumSensors,
                                 double         range)
{
  //make sure vector of sensors is empty before proceeding
  sensors.clear();

  double SegmentAngle = CParams::dPi / (NumSensors-1);

	//going clockwise from 90deg left of position calculate the fan of
	//points radiating out (not including the origin)
	for (int i=0; i<CParams::iNumSensors; i++)
	{
		//calculate vertex position
		SPoint point;

    point.x = -sin(i * SegmentAngle - CParams::dHalfPi) * range;

	  point.y = cos(i * SegmentAngle - CParams::dHalfPi) * range;
		
		sensors.push_back(point);
		
	}//next segment

}
//-----------------------------Reset()------------------------------------
//
//	Resets the sweepers position, energy level and rotation
//
//------------------------------------------------------------------------
void CMinesweeper::Reset()
{
	//reset the sweepers positions
	m_vPosition = SVector2D(180, 200);
	
	//and the energy level
	m_dFitness = 0;

  //and the rotation
  m_dRotation = RandFloat() * CParams::dTwoPi;

  //and the bonuses
  m_dSpinBonus        = 0;
  m_dCollisionBonus   = 0;

}

//------------------------- RenderMemory ---------------------------------
//
//------------------------------------------------------------------------
void CMinesweeper::RenderPenalties(HDC surface)
{
  string s = ftos(m_dSpinBonus);
  s = "Spin: " + s;
  TextOut(surface, 200,0,s.c_str(), s.size());

  s = ftos(m_dCollisionBonus);
  s = "Collision: " + s;
  TextOut(surface, 300, 0,s.c_str(), s.size());

}
//---------------------WorldTransform--------------------------------
//
//	sets up a translation matrix for the sweeper according to its
//  scale, rotation and position. Returns the transformed vertices.
//-------------------------------------------------------------------
void CMinesweeper::WorldTransform(vector<SPoint> &sweeper, double scale)
{
	//create the world transformation matrix
	C2DMatrix matTransform;
	
	//scale
	matTransform.Scale(scale, scale);
	
	//rotate
	matTransform.Rotate(m_dRotation);
	
	//and translate
	matTransform.Translate(m_vPosition.x, m_vPosition.y);
	
	//now transform the ships vertices
	matTransform.TransformSPoints(sweeper);
}

//-------------------------------Update()--------------------------------
//
//	First we take sensor readings and feed these into the sweepers brain.
//
//	The inputs are:
//	
//  The readings from the minesweepers sensors
//
//	We receive two outputs from the brain.. lTrack & rTrack.
//	So given a force for each track we calculate the resultant rotation 
//	and acceleration and apply to current velocity vector.
//
//-----------------------------------------------------------------------
bool CMinesweeper::Update(vector<SPoint> &objects)
{
	
	//this will store all the inputs for the NN
	vector<double> inputs;	

  //grab sensor readings
  TestSensors(objects);


  //input sensors into net
  for (int sr=0; sr<m_vecdSensors.size(); ++sr)
  {
    inputs.push_back(m_vecdSensors[sr]);
  }
	
  
	//update the brain and get feedback
	vector<double> output = m_ItsBrain.Update(inputs);

	//make sure there were no errors in calculating the 
	//output
	if (output.size() < CParams::iNumOutputs) 
  {
    return false;
  }

  
	//assign the outputs to the sweepers left & right tracks
	m_lTrack = output[0];
	m_rTrack = output[1];

	//calculate steering forces
	double RotForce = m_lTrack - m_rTrack;

  //clamp rotation
	Clamp(RotForce, -CParams::dMaxTurnRate, CParams::dMaxTurnRate);
	
	m_dRotation += RotForce;

	//update Look At 
	m_vLookAt.x = -sin(m_dRotation);
	m_vLookAt.y = cos(m_dRotation);

  //if the sweepers haven't collided with an obstacle
  //update their position
  if (!m_bCollided)
  {
    m_dSpeed = (m_lTrack + m_rTrack);

   //update position
   m_vPosition += (m_vLookAt * m_dSpeed);
  }

    

  //-----------------------adjust the fitness bonuses

  //reward for not turning too quickly
  const float RotationTolerance = 0.03f;

  if (fabs(RotForce) < RotationTolerance)
  {
    m_dSpinBonus += 1;
  }

  //reward for not colliding with an object
  if (!m_bCollided)
  {
    m_dCollisionBonus += 1;
  }

  
	return true;
}
//----------------------- TestSensors ------------------------------------
//
//  This function checks for any intersections between the sweeper's 
//  sensors and the objects in its environment
//------------------------------------------------------------------------
void CMinesweeper::TestSensors(vector<SPoint> &objects)
{
  m_bCollided = false;  
  
  //first we transform the sensors into world coordinates
  m_tranSensors = m_Sensors;

  WorldTransform(m_tranSensors, 1);

  //flush the sensors
  m_vecdSensors.clear();

  //now to check each sensor against the objects in the world
  for (int sr=0; sr<m_tranSensors.size(); ++sr)
  {
    bool bHit = false;

    double dist = 0;
      
    for (int seg=0; seg<objects.size(); seg+=2)
    {
      if (LineIntersection2D(SPoint(m_vPosition.x, m_vPosition.y),
                             m_tranSensors[sr],
                             objects[seg],
                             objects[seg+1],
                             dist))
      {
        bHit = true;

        break;
      }
    }
      
    if (bHit)
    {
      m_vecdSensors.push_back(dist);

      //implement very simple collision detection
      if (dist < CParams::dCollisionDist)
      {
        m_bCollided = true;
      }
    }
    
    else
    {
      m_vecdSensors.push_back(-1);
    }    
  }//next sensor
}

//------------------------- EndOfRunCalculations() -----------------------
//
//------------------------------------------------------------------------
void CMinesweeper::EndOfRunCalculations()
{
  m_dFitness += m_dSpinBonus;
  m_dFitness += m_dCollisionBonus;
}




		
