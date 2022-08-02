#include "CController.h"

//number of stars
const int NumStars = 20;

//this defines the vertices for the lander shape
const int	 NumPadVerts = 4;

const SPoint Pad[NumPadVerts] = {SPoint(-20, 0),
                                 SPoint(20, 0),
                                 SPoint(20, 5),
                                 SPoint(-20, 5)};
                                      
//------------------------------dtor -------------------------------------
//
//------------------------------------------------------------------------
CController::~CController()
{
  if (m_pUserLander)
  {
    delete m_pUserLander;
  }
}
//-----------------------------ctor---------------------------------------
//
//------------------------------------------------------------------------
CController::CController(int cxClient,
                         int cyClient):
                                       m_bSuccess(false),                                  
                                       m_vPadPos(SVector2D(RandFloat()*cxClient, 50)),
                                       m_cxClient(cxClient),
                                       m_cyClient(cyClient)
                                       
{


  //create a starting postion for the landers
  SVector2D vStartPos = SVector2D(WINDOW_WIDTH/2, cyClient-50);

  //create the user controlled lander
  m_pUserLander = new CLander(cxClient, cyClient, PI, vStartPos, m_vPadPos);

  //set up the VB for the landing pad
  for (int i=0; i<NumPadVerts; ++i)
  {
    m_vecPadVB.push_back(Pad[i]);
  }

  //setup the stars
  for (i=0; i<NumStars; ++i)
  {
    m_vecStarVB.push_back(SPoint(RandInt(0, cxClient), RandInt(100, cyClient)));
  }

}

                                    
//------------------------------- NewRun ---------------------------------
//
//  reinitializes all the variables for a new run
//------------------------------------------------------------------------
void CController::NewRun()
{

  //change position of landing pad
   m_vPadPos = SVector2D(50+ RandFloat()*(m_cxClient-100), 50);

   //reset the spaceship
   m_pUserLander->Reset(m_vPadPos);

}

//-----------------------Render--------------------------------------
//
//	given a GDI surface this function renders the ship and the
//	landing pad
//-------------------------------------------------------------------
void CController::Render(HDC &surface)
{
  //change the mapping mode so that the origin is at the bottom left
  //of our window and so that the y axis increases as it goes from
  //bottom to top     
  SetMapMode( surface, MM_ANISOTROPIC );
  SetViewportExtEx( surface, 1, -1, NULL );
  SetWindowExtEx( surface, 1, 1, NULL );
  SetViewportOrgEx( surface, 0, m_cyClient, NULL );

   //select in the pen we want to use
  HPEN OldPen = (HPEN)SelectObject(surface, GetStockObject(WHITE_PEN));

  //first render the stars
  for (int i=0; i<m_vecStarVB.size(); ++i)
  {
    //add some twinkle
    if (RandFloat() > 0.1)
    {
      SetPixel(surface, m_vecStarVB[i].x, m_vecStarVB[i].y, RGB(255, 255, 255));
    }
  }
  
  //render the user controlled ship
  m_pUserLander->Render(surface);

  //render the landing pad...
  RenderLandingPad(surface);

      
  //return the mapping mode to its default state so text is rendered
  //correctly
  SetMapMode( surface, MM_ANISOTROPIC );
  SetViewportExtEx( surface, 1, 1, NULL );
  SetWindowExtEx( surface, 1, 1, NULL );
  SetViewportOrgEx( surface, 0, 0, NULL );

  //Render additional information
  SetBkMode(surface, TRANSPARENT);
  SetTextColor(surface, RGB(0,0,255));
 
  string s= "Cursor Keys - Rotate   Spacebar - Thrust   R - Retry";
  TextOut(surface, 30, m_cyClient - 20, s.c_str(), s.size());

  //replace the pen
  SelectObject(surface, OldPen);
}
//----------------------------- RenderLandingPad ------------------------
//
//  Does exactly that
//-----------------------------------------------------------------------
void CController::RenderLandingPad(HDC &surface)
{
    //create a temp buffer
  vector<SPoint> PadVB = m_vecPadVB;

  //transform the vertices
  WorldTransform(PadVB);

  //draw the lines
  MoveToEx(surface, (int)PadVB[0].x, (int)PadVB[0].y, NULL);

  for (int vert=1; vert<4; ++vert)
	{
		LineTo(surface, (int)PadVB[vert].x, (int)PadVB[vert].y);
	}

  LineTo(surface, (int)PadVB[0].x, (int)PadVB[0].y);
}

//---------------------WorldTransform--------------------------------
//
//	sets up the translation matrices for the landing pad and applies
//  the world transform to the pads vertex buffer
//-------------------------------------------------------------------
void CController::WorldTransform(vector<SPoint> &pad)
{
	//create a transformation matrix
	C2DMatrix matTransform;
	
	//and translate
	matTransform.Translate(m_vPadPos.x, m_vPadPos.y);
	
  //now transform the pads vertices
  matTransform.TransformSPoints(pad);

}
//------------------------------- Update ---------------------------------
//
//------------------------------------------------------------------------
bool CController::Update(double TimeElapsed)
{
   //update user controlled ship
   m_pUserLander->UpdateShip(TimeElapsed);

   return true;
}


