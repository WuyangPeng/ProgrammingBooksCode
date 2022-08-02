#include "CAlien.h"



//the vertices making up its shape
const int NumAlienVerts = 19;
const SPoint Alien[NumAlienVerts] = { SPoint(1,3),
                                      SPoint(4,1),
                                      SPoint(4,-1),
                                      SPoint(2,-4),
                                      SPoint(1,-1),
                                      SPoint(0,-2),
                                      SPoint(-1,-1),
                                      SPoint(-2,-4),
                                      SPoint(-4,-1),
                                      SPoint(-4,1),
                                      SPoint(-1,3),

                                      SPoint(-2,1),
                                      SPoint(-1.5,0.5),
                                      SPoint(-2,0),
                                      SPoint(-2.5,1),

                                      SPoint(2,1),
                                      SPoint(1.5,0.5),
                                      SPoint(2,0),
                                      SPoint(2.5,1)};




//--------------------------------- ctor ---------------------------------
//
//------------------------------------------------------------------------
CAlien::CAlien(): m_dScale(CParams::dAlienScale),
                  m_vVelocity(SVector2D(0, 0)),
                  m_dMass(CParams::dAlienMass),
                  m_iAge(0),
                  m_bWarning(false)
{ 
  //set its position
  m_vPos = SVector2D(RandInt(0, CParams::WindowWidth), CParams::WindowHeight);
  
  //create the vertex buffer
  for (int i=0; i<NumAlienVerts; ++i)
  {
    m_vecAlienVB.push_back(Alien[i]);
  }

  //setup its bounding box
  m_AlienBBox.left  = m_vPos.x - (4*CParams::dAlienScale);
  m_AlienBBox.right = m_vPos.x + (4*CParams::dAlienScale);
  m_AlienBBox.top   = m_vPos.y + (3*CParams::dAlienScale);
  m_AlienBBox.bottom= m_vPos.y - (4*CParams::dAlienScale);

}


//------------------------------ Render ----------------------------------
void CAlien::Render(HDC &surface, HPEN &GreenPen, HPEN &RedPen)
{
  //transform the vertices
  WorldTransform();

  //select in green pen
  HPEN OldPen = (HPEN)SelectObject(surface, GreenPen);
 
  //draw body
  MoveToEx(surface, m_vecAlienVBTrans[0].x, m_vecAlienVBTrans[0].y, NULL);

  for (int vtx=0; vtx<11; ++vtx)
  {
    LineTo(surface, m_vecAlienVBTrans[vtx].x, m_vecAlienVBTrans[vtx].y);
  }

  LineTo(surface, m_vecAlienVBTrans[0].x, m_vecAlienVBTrans[0].y);

  //select in red pen
  SelectObject(surface, RedPen);
  
  //left eye
  MoveToEx(surface, m_vecAlienVBTrans[11].x, m_vecAlienVBTrans[11].y, NULL);

  for (vtx=12; vtx<15; ++vtx)
  {
    LineTo(surface, m_vecAlienVBTrans[vtx].x, m_vecAlienVBTrans[vtx].y);
  }

  //right eye
  MoveToEx(surface, m_vecAlienVBTrans[15].x, m_vecAlienVBTrans[15].y, NULL);

  for (vtx=16; vtx<19; ++vtx)
  {
    LineTo(surface, m_vecAlienVBTrans[vtx].x, m_vecAlienVBTrans[vtx].y);
  }


  //replace the old pen
  SelectObject(surface, OldPen);

  //display warning if a problem with the network
  if (m_bWarning)
  {
    string s = "Wrong amount of inputs!";
	  TextOut(surface, 110, 200, s.c_str(), s.size());
  }

}


//---------------------WorldTransform--------------------------------
//
//	sets up the translation matrices for the ship and applies the
//	world transform to the ships vertex buffer
//-------------------------------------------------------------------
void CAlien::WorldTransform()
{
	//copy the original vertices into the buffer about to be transformed
  m_vecAlienVBTrans = m_vecAlienVB;
  
  //create a transformation matrix
	C2DMatrix matTransform;
	
	//scale
	matTransform.Scale(m_dScale, m_dScale);

	//and translate
	matTransform.Translate(m_vPos.x, m_vPos.y);
	
  //now transform the ships vertices
  matTransform.TransformSPoints(m_vecAlienVBTrans);
}

//----------------------------- GetActionFromNetwork ---------------------
//
//  this function updates the neural net and returns the action the 
//  network selects as its output
//------------------------------------------------------------------------
action_type CAlien::GetActionFromNetwork(const vector<CBullet> &bullets,
                                         const SVector2D       &GunPos)
{
  //the inputs into the net 
  vector<double> NetInputs;

  //This will hold the outputs from the neural net
  static vector<double> outputs(0,3);

  //add in the vector to the gun turret
  int XComponentToTurret = GunPos.x - m_vPos.x;
  int YComponentToTurret = GunPos.y - m_vPos.y;

  NetInputs.push_back(XComponentToTurret);
  NetInputs.push_back(YComponentToTurret);

  //now any bullets
  for (int blt=0; blt<bullets.size(); ++blt)
  {
    if (bullets[blt].Active())
    {
      
      double xComponent = bullets[blt].Pos().x - m_vPos.x;
      double yComponent = bullets[blt].Pos().y - m_vPos.y;

      NetInputs.push_back(xComponent);
      NetInputs.push_back(yComponent);
    }

    else
    {
      //if a bullet is innactive just input the vector to
      //the gun turret
      NetInputs.push_back(XComponentToTurret);
      NetInputs.push_back(YComponentToTurret);
    }
  }

  //feed the inputs into the net and get the outputs
  outputs = m_ItsBrain.Update(NetInputs);

  //this is set if there is a problem with the update
  if (outputs.size() == 0)
  {
     m_bWarning = true;
  }

  //determine which action is valid this frame. The highest valued
  //output over 0.9. If none are over 0.9 then just drift with
  //gravity
  double BiggestSoFar = 0;

  action_type action = drift;

  for (int i=0; i<outputs.size(); ++i)
  {
    if( (outputs[i] > BiggestSoFar) && (outputs[i] > 0.9))
    {
      action = (action_type)i;
      
      BiggestSoFar = outputs[i];
    }
  }

  return action;
}


//----------------------------- Update -----------------------------------
//
//  Checks for user keypresses and updates the aliens parameters accordingly
//------------------------------------------------------------------------
bool CAlien::Update(vector<CBullet> &bullets,const SVector2D &GunPos)
{
  //update age
  ++m_iAge;

  //get the next action from the neural network
  int action = GetActionFromNetwork(bullets, GunPos);

  //switch on the action
  switch(action)
  {
  case thrust_left:
    {
      m_vVelocity.x -= CParams::dMaxThrustLateral/m_dMass;
    }

    break;

  case thrust_right:
    {
      m_vVelocity.x += CParams::dMaxThrustLateral/m_dMass;
    }

    break;

  case thrust_up:
    {
      m_vVelocity.y += CParams::dMaxThrustVertical/m_dMass;
    }

    break;

    default:break;
  }

  //add in gravity
  SVector2D gravity(0, CParams::dGravityPerTick); 
                                                         
  m_vVelocity += gravity;

  //clamp the velocity of the alien
  Clamp(m_vVelocity.x, -CParams::dMaxVelocity, CParams::dMaxVelocity);
  Clamp(m_vVelocity.y, -CParams::dMaxVelocity, CParams::dMaxVelocity);
  
  //update the alien's position
	m_vPos += m_vVelocity;

  //wrap around window width 
  if (m_vPos.x < 0)
  {
    m_vPos.x = CParams::WindowWidth;
  }

  if (m_vPos.x > CParams::WindowWidth)
  {
    m_vPos.x = 0;
  }

  //update the bounding box 
  m_AlienBBox.left  = m_vPos.x - (4*CParams::dAlienScale);
  m_AlienBBox.right = m_vPos.x + (4*CParams::dAlienScale);
  m_AlienBBox.top   = m_vPos.y + (3*CParams::dAlienScale);
  m_AlienBBox.bottom= m_vPos.y - (4*CParams::dAlienScale);

  //an alien dies if it drops below the gun, flys too high
  //or is hit by a bullet
  if ( (m_vPos.y > (CParams::WindowHeight + 5)) ||
       (m_vPos.y < 15)                          || 
       CheckForCollision(bullets))
  {   
    return false;
  }
      
  return true;
}


//------------------------- CheckForCollision ---------------------------
//
//  tests the aliens bounding box against each bullet's bounding box.
//  returns true if a collision is detected
//-----------------------------------------------------------------------
bool CAlien::CheckForCollision(vector<CBullet> &bullets)const
{
  //for each bullet  
  for (int blt=0; blt<bullets.size(); ++blt)
  {
    //if bullet is not active goto next bullet
    if (!bullets[blt].Active())
    {
      continue;
    }
    
    RECT blts = bullets[blt].BBox();

    //test for intersection between bounding boxes
    if (!((blts.bottom > m_AlienBBox.top) ||
          (blts.top < m_AlienBBox.bottom) ||
          (blts.left > m_AlienBBox.right) ||
          (blts.right < m_AlienBBox.left)))
    {
      bullets[blt].SwitchOff();
      
      return true;
    }
  }

  return false;
}


//--------------------------------- Reset --------------------------------
//
//------------------------------------------------------------------------
void CAlien::Reset()
{
  m_iAge      = 0;
  m_vVelocity = SVector2D(0, 0);
  m_vPos      = SVector2D(RandInt(0, CParams::WindowWidth), CParams::WindowHeight);
}


//------------------------------ mutate ----------------------------------
//
//  mutates the connection weights in the alien's neural network.
//------------------------------------------------------------------------
void CAlien::Mutate()
{

  //grab the weights for the neural net
  vector<double> weights = m_ItsBrain.GetWeights();

  //mutate them
  for (int w=0; w<weights.size(); ++w)
  {
    //do we perturb this weight?
    if (RandFloat() < CParams::dMutationRate)
		{
			//add a small value to the weight
			weights[w] += (RandomClamped() * CParams::dMaxPerturbation);
		}
	}

  //put 'em back!
  m_ItsBrain.PutWeights(weights);
}

