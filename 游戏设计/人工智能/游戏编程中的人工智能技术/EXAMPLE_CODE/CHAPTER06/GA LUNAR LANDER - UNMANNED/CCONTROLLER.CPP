#include "CController.h"

//number of stars
const int NumStars = 20;

//this defines the vertices for the lander shape
const int	 NumPadVerts = 4;

const SPoint Pad[NumPadVerts] = {SPoint(-20, 0),
                                 SPoint(20, 0),
                                 SPoint(20, 5),
                                 SPoint(-20, 5)};
                                      

//-----------------------------ctor---------------------------------------
//
//------------------------------------------------------------------------
CController::CController(int cxClient,
                         int cyClient):m_bFastRender(false),
                                       m_bShowFittest(false),
                                       m_bSuccess(false),
                                       m_iGeneration(0),
                                       m_cxClient(cxClient),
                                       m_cyClient(cyClient),
                                       m_iFittest(0)
                                       
{
   //setup the GA
  m_pGA = new CgaLander(CROSSOVER_RATE,
                         MUTATION_RATE,
                         POP_SIZE,
                         CHROMO_LENGTH,
                         cxClient,
                         cyClient);

  //grab the genomes
  m_vecPop = m_pGA->GrabPop();

  //create a starting postion for the landers
  SVector2D vStartPos = SVector2D(RandFloat()*cxClient, cyClient-50);

  //and the landing pad
  m_vPadPos = SVector2D(50 + RandFloat() * (m_cxClient-100), 50);

  //create the landers and insert their genomes
  for (int i=0; i<POP_SIZE; ++i)
  {
    m_vecLanders.push_back(CLander(cxClient, cyClient, PI, vStartPos, m_vPadPos));

    m_vecLanders[i].Decode(m_vecPop[i].vecActions);
  }

  //set up the VB for the landing pad
  for (i=0; i<NumPadVerts; ++i)
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
  //delete the old GA and create a new population of genomes
  if (m_pGA)
  {
    delete m_pGA;
  }

  m_pGA = new CgaLander(CROSSOVER_RATE,
                         MUTATION_RATE,
                         POP_SIZE,
                         CHROMO_LENGTH,
                         m_cxClient,
                         m_cyClient);

    //grab the genomes
  m_vecPop = m_pGA->GrabPop();
  
  //change position of landing pad
  m_vPadPos = SVector2D(50 + RandFloat() * (m_cxClient-100), 50);

  //insert the landers genomes
  for (int i=0; i<POP_SIZE; ++i)
  {
    m_vecLanders[i].Reset(m_vPadPos);

    m_vecLanders[i].Decode(m_vecPop[i].vecActions);
  }

  m_iGeneration = 0;
  m_iFittest    = 0;
  m_bSuccess    = false;
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
    //make them twinkle
    if (RandFloat() > 0.1)
    {
      SetPixel(surface, m_vecStarVB[i].x, m_vecStarVB[i].y, RGB(255, 255, 255));
    }
  }
  
  if(!m_bShowFittest)
  {
    //render all landers
    for (int i=0; i<m_vecLanders.size(); ++i)
    {
      m_vecLanders[i].Render(surface);
    }
  }

  else
  {
    //just render the best this generation
    m_vecLanders[m_iFittest].Render(surface);
  }
 
  //render the landing pad
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
  
	string s = "Generation: " + itos(m_iGeneration);
	TextOut(surface, 5, 2, s.c_str(), s.size());


  s = "F-Toggle Fast Render";
	TextOut(surface, 250, m_cyClient-15, s.c_str(), s.size());

  s = "B-Show Fittest";
	TextOut(surface, 5, m_cyClient-15, s.c_str(), s.size());

  s = "R-Reset";
	TextOut(surface, 150, m_cyClient-15, s.c_str(), s.size());


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

  //draw the lines which describe the landing pad
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
bool CController::Update()
{

  //if number of generations exceeds a predifined maximum before
  //finding a solution restart the GA
  if (m_iGeneration > MAX_GENERATIONS_ALLOWED)
  {
    NewRun();
  }

  //this is set if all the landers have finished performing all their
  //actions
  static bool bAllFinished = false;

  if (!bAllFinished)
  {
     bAllFinished = true;
     
     //for each lander
     for (int lndr=0; lndr<POP_SIZE; ++lndr)
     {
       //update the lander's position. 
       if (m_vecLanders[lndr].UpdateShip())
       {
         //the ship still has actions to perform so we set this to 
         //false in order for the loop to continue
         bAllFinished = false;
       }
     }

   }

   else
   {
     m_iFittest = 0;
     double BestScoreSoFar = 0;
       
     //grab the updated fitness scores and insert into the GA
     for (int lndr=0; lndr<POP_SIZE; ++lndr)
     {
       m_vecPop[lndr].dFitness = m_vecLanders[lndr].Fitness();

       //keep a track of the fittest lander each generation
       if (m_vecPop[lndr].dFitness > BestScoreSoFar)
       {
         BestScoreSoFar = m_vecPop[lndr].dFitness;

         m_iFittest = lndr;
       }

       //check for success
       if ( (m_vecPop[lndr].dFitness >= BIG_NUMBER) && !m_bSuccess)
       {
         m_bSuccess = true;

         Success();
       }

       //reset the landers
       m_vecLanders[lndr].Reset(m_vPadPos);
     }

     //reset finished flag
     bAllFinished = false;

     //only perform an Epoch of the GA if we haven't been successful
     //in producing a ship which can land
     if (!m_bSuccess)
     {
       //insert the genomes back into the GA and get a new population
        m_pGA->UpdatePop(m_vecPop);

        //put the new genomes back into the lander population
        for (lndr=0; lndr<POP_SIZE; ++lndr)
        {
          m_vecLanders[lndr].Decode(m_vecPop[lndr].vecActions);
        }

        //increment the generation counter
        m_iGeneration++; 
     }
   
   
  }//end else

  return true;
}
//-------------------------- Success --------------------------------
//
//  if a ship lands this sets the appropriate flags so we may view it
//  and plays a soundfile
//-------------------------------------------------------------------
void CController::Success()
{
  //make sure rendering toggles are set so we can see the successful
  //ship land in all its graceful glory
  if (!m_bShowFittest)
  {
    m_bShowFittest = true;
  }

  if (m_bFastRender)
  {
    m_bFastRender = false;
  }
  
  //play one of two victory wavs
  if (RandBool())
  {
    PlaySound("landed.wav", NULL, SND_ASYNC|SND_FILENAME);
  }
  else
  {
    PlaySound("leap.wav", NULL, SND_ASYNC|SND_FILENAME);
  }
           
   MessageBox(NULL, "Landed! Press OK to view", "Success", 0);
}

//----------------------- ToggleShowFittest ----------------------------
//
//  setting this means that we only render the fittest member of each
//  generation. Plays an appropriate sound file.
//----------------------------------------------------------------------
void CController::ToggleShowFittest()
{
  m_bShowFittest = !m_bShowFittest;
    
  if (m_bShowFittest)
  {
    PlaySound("view_best.wav", NULL, SND_ASYNC|SND_FILENAME);
  }
}
