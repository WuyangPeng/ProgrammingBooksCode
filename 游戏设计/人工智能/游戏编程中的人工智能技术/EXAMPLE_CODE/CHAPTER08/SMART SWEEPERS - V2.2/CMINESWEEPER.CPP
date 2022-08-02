#include "CMinesweeper.h"

//-----------------------------------constructor-------------------------
//
//-----------------------------------------------------------------------
CMinesweeper::CMinesweeper():
                             m_dRotation(RandFloat() * CParams::dTwoPi),
                             m_lTrack(0),
                             m_rTrack(0),
                             m_dFitness(0),
							               m_dScale(CParams::iSweeperScale),
                             m_bCollided(false)
                             
			 
{
  //create a static start position
  m_vPosition = SVector2D(180, 200);

   //create the sensors
  CreateSensors(m_Sensors, CParams::iNumSensors, CParams::dSensorRange); 

  //initialize its memory
  m_MemoryMap.Init(CParams::WindowWidth,
                   CParams::WindowHeight);

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

  //reset its memory
  m_MemoryMap.Reset();

}

//------------------------- RenderMemory ---------------------------------
//
//------------------------------------------------------------------------
void CMinesweeper::Render(HDC surface)
{
  //render the memory
  m_MemoryMap.Render(surface);

  string s = itos(m_MemoryMap.NumCellsVisited());
  s = "Num Cells Visited: " + s;
  TextOut(surface, 230,0,s.c_str(), s.size());

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
//  The readings from the minesweeper's sensors
//  The readings from the minesweeper's feelers
//  bCollided
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

    inputs.push_back(m_vecFeelers[sr]);
  }
	
  inputs.push_back(m_bCollided);
  
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

  //update the memory map
  m_MemoryMap.Update(m_vPosition.x, m_vPosition.y);
  
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

  WorldTransform(m_tranSensors, 1);  //scale is 1

  //flush the sensors
  m_vecdSensors.clear();
  m_vecFeelers.clear();

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
    
    //check how many times the minesweeper has visited the cell
    //at the current position
    int HowOften = m_MemoryMap.TicksLingered(m_tranSensors[sr].x,
                                             m_tranSensors[sr].y);

    
    //Update the memory info according to HowOften. The maximum
    //value is 1 (because we want all the inputs into the
    //ANN to be scaled between -1 < n < 1)
    if (HowOften == 0)
    {
      m_vecFeelers.push_back(-1);

      continue;
    }
    
    if (HowOften < 10) 
    {
      m_vecFeelers.push_back(0);

      continue;
    }

    if (HowOften < 20)
    {
      m_vecFeelers.push_back(0.2);

      continue;
    }

    if (HowOften < 30)
    {
      m_vecFeelers.push_back(0.4);

      continue;
    }

    if (HowOften < 50)
    {
      m_vecFeelers.push_back(0.6);

      continue;
    }

    if (HowOften < 80) 
    {
      m_vecFeelers.push_back(0.8);

      continue;
    }

     m_vecFeelers.push_back(1);   

  }//next sensor
}

//------------------------- EndOfRunCalculations() -----------------------
//
//------------------------------------------------------------------------
void CMinesweeper::EndOfRunCalculations()
{
  m_dFitness += m_MemoryMap.NumCellsVisited();
}




		
