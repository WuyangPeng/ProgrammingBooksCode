#include "CMinesweeper.h"

//-----------------------------------constructor-------------------------
//
//-----------------------------------------------------------------------
CMinesweeper::CMinesweeper():
                             m_dRotation(RandFloat()*CParams::dTwoPi),
                             m_lTrack(0.16),
                             m_rTrack(0.16),
                             m_dFitness(CParams::dStartEnergy),
							               m_dScale(CParams::iSweeperScale),
                             m_iClosestMine(0)
			 
{
	//create a random start position
	m_vPosition = SVector2D((RandFloat() * CParams::WindowWidth), 
					                (RandFloat() * CParams::WindowHeight));
  
}

//-------------------------------------------Reset()--------------------
//
//	Resets the sweepers position, energy level and rotation
//
//----------------------------------------------------------------------
void CMinesweeper::Reset()
{
	//reset the sweepers positions
	m_vPosition = SVector2D((RandFloat() * CParams::WindowWidth), 
					                (RandFloat() * CParams::WindowHeight));
	
	//and the energy level
	m_dFitness = CParams::dStartEnergy;

  //and the rotation
  m_dRotation = RandFloat()*CParams::dTwoPi;

	return;
}
//---------------------WorldTransform--------------------------------
//
//	sets up a translation matrix for the sweeper according to its
//  scale, rotation and position. Returns the transformed vertices.
//-------------------------------------------------------------------
void CMinesweeper::WorldTransform(vector<SPoint> &sweeper)
{
	//create the world transformation matrix
	C2DMatrix matTransform;
	
	//scale
	matTransform.Scale(m_dScale, m_dScale);
	
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
//  a signed angle to the closest mine
//
//	We receive two outputs from the brain.. lTrack & rTrack.
//	So given a force for each track we calculate the resultant rotation 
//	and acceleration and apply to current velocity vector.
//
//-----------------------------------------------------------------------
bool CMinesweeper::Update(vector<SVector2D> &mines)
{
	
	//this will store all the inputs for the NN
	vector<double> inputs;	

	//get vector to closest mine
	SVector2D vClosestMine = GetClosestMine(mines);
  
	//normalise it
  Vec2DNormalize(vClosestMine);
  
  //calculate dot product of the look at vector and Closest mine
  //vector. This will give us the angle we need turn to face
  //the closest mine
  double dot = Vec2DDot(m_vLookAt, vClosestMine);

  //calculate sign
  int sign   = Vec2DSign(m_vLookAt, vClosestMine);

  inputs.push_back(dot*sign);

  
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

  m_dSpeed = (m_lTrack + m_rTrack);

	//update Look At 
	m_vLookAt.x = -sin(m_dRotation);
	m_vLookAt.y = cos(m_dRotation);

	//update position
  m_vPosition += (m_vLookAt * m_dSpeed);

	//wrap around window limits
	if (m_vPosition.x > CParams::WindowWidth) m_vPosition.x = 0;
	if (m_vPosition.x < 0) m_vPosition.x = CParams::WindowWidth;
	if (m_vPosition.y > CParams::WindowHeight) m_vPosition.y = 0;
	if (m_vPosition.y < 0) m_vPosition.y = CParams::WindowHeight;

	return true;
}


//----------------------GetClosestObject()---------------------------------
//
//	returns the vector from the sweeper to the closest mine
//
//-----------------------------------------------------------------------
SVector2D CMinesweeper::GetClosestMine(vector<SVector2D> &mines)
{
	double			closest_so_far = 99999;

	SVector2D		vClosestObject(0, 0);

	//cycle through mines to find closest
	for (int i=0; i<mines.size(); i++)
	{
		double len_to_object = Vec2DLength(mines[i] - m_vPosition);

		if (len_to_object < closest_so_far)
		{
			closest_so_far	= len_to_object;
			
			vClosestObject	= m_vPosition - mines[i];

      m_iClosestMine = i;
		}
	}

	return vClosestObject;
}
//----------------------------- CheckForMine -----------------------------
//
//  this function checks for collision with its closest mine (calculated
//  earlier and stored in m_iClosestMine)
//-----------------------------------------------------------------------
int CMinesweeper::CheckForMine(vector<SVector2D> &mines, double size)
{
  SVector2D DistToObject = m_vPosition - mines[m_iClosestMine];
		
	if (Vec2DLength(DistToObject) < (size + 5))
	{
			return m_iClosestMine;
  }

  return -1;
}

		
