#include "CController.h"


//these hold the geometry of the sweepers and the mines
const int	 NumSweeperVerts = 16;
const SPoint sweeper[NumSweeperVerts] = {SPoint(-1, -1),
                                         SPoint(-1, 1),
                                         SPoint(-0.5, 1),
                                         SPoint(-0.5, -1),

                                         SPoint(0.5, -1),
                                         SPoint(1, -1),
                                         SPoint(1, 1),
                                         SPoint(0.5, 1),
                                         
                                         SPoint(-0.5, -0.5),
                                         SPoint(0.5, -0.5),

                                         SPoint(-0.5, 0.5),
                                         SPoint(-0.25, 0.5),
                                         SPoint(-0.25, 1.75),
                                         SPoint(0.25, 1.75),
                                         SPoint(0.25, 0.5),
                                         SPoint(0.5, 0.5)};



const int NumMineVerts = 4;
const SPoint mine[NumMineVerts] = {SPoint(-1, -1),
                                   SPoint(-1, 1),
                                   SPoint(1, 1),
                                   SPoint(1, -1)};

                                      
const int NumObjectVerts = 42;
const SPoint objects[NumObjectVerts] = {SPoint(80, 60),
                                        SPoint(200,60),
                                        SPoint(200,60),
                                        SPoint(200,100),
                                        SPoint(200,100),
                                        SPoint(160,100),
                                        SPoint(160,100),
                                        SPoint(160,200),
                                        SPoint(160,200),
                                        SPoint(80,200),
                                        SPoint(80,200),
                                        SPoint(80,60),

                                        SPoint(250,100),
                                        SPoint(300,40),
                                        SPoint(300,40),
                                        SPoint(350,100),
                                        SPoint(350,100),
                                        SPoint(250, 100),

                                        SPoint(220,180),
                                        SPoint(320,180),
                                        SPoint(320,180),
                                        SPoint(320,300),
                                        SPoint(320,300),
                                        SPoint(220,300),
                                        SPoint(220,300),
                                        SPoint(220,180),

                                        SPoint(12,15),
                                        SPoint(380, 15),
                                        SPoint(380,15),
                                        SPoint(380,360),
                                        SPoint(380,360),                                
                                        SPoint(12,360),
                                        SPoint(12,360),
                                        SPoint(12,340),
                                        SPoint(12,340),
                                        SPoint(100,290),
                                        SPoint(100,290),
                                        SPoint(12,240),
                                        SPoint(12,240),
                                        SPoint(12,15)};





//---------------------------------------constructor---------------------
//
//	initilaize the sweepers, their brains and the GA factory
//
//-----------------------------------------------------------------------
CController::CController(HWND hwndMain,
                         int  cxClient,
                         int  cyClient): m_NumSweepers(CParams::iNumSweepers), 
										                     m_bFastRender(false),
                                         m_bRenderBest(false),
										                     m_iTicks(0),
										                     m_hwndMain(hwndMain),
                                         m_hwndInfo(NULL),
										                     m_iGenerations(0),
                                         m_cxClient(cxClient),
                                         m_cyClient(cyClient),
                                         m_iViewThisSweeper(0)
{
  
	//let's create the mine sweepers
	for (int i=0; i<m_NumSweepers; ++i)
	{
		m_vecSweepers.push_back(CMinesweeper());
	}
  
  //and the vector of sweepers which will hold the best performing sweeprs
  for (i=0; i<CParams::iNumBestSweepers; ++i)
	{
		m_vecBestSweepers.push_back(CMinesweeper());
	}

  

  m_pPop = new Cga(CParams::iNumSweepers,
                   CParams::iNumInputs,
                   CParams::iNumOutputs,
                   hwndMain,
                   10,10);  

  //create the phenotypes
   vector<CNeuralNet*> pBrains = m_pPop->CreatePhenotypes();
   
	//assign the phenotypes
  for (i=0; i<m_NumSweepers; i++)
  {   
    m_vecSweepers[i].InsertNewBrain(pBrains[i]);
  }

	//create a pen for the graph drawing
	m_BluePen        = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_RedPen         = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_GreenPen       = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
  m_GreyPenDotted  = CreatePen(PS_DOT, 1, RGB(100, 100, 100));
  m_RedPenDotted   = CreatePen(PS_DOT, 1, RGB(200, 0, 0));

	m_OldPen	= NULL;

  //and the brushes
  m_BlueBrush = CreateSolidBrush(RGB(0,0,244));
  m_RedBrush = CreateSolidBrush(RGB(150,0,0));

	//fill the vertex buffers
	for (i=0; i<NumSweeperVerts; ++i)
	{
		m_SweeperVB.push_back(sweeper[i]);
	}

  for (i=0; i<NumObjectVerts; ++i)
  {
    m_ObjectsVB.push_back(objects[i]);
  }
}

//--------------------------------------destructor-------------------------------------
//
//--------------------------------------------------------------------------------------
CController::~CController()
{
  if (m_pPop)
  {
    delete m_pPop;
  }
  
	DeleteObject(m_BluePen);
	DeleteObject(m_RedPen);
	DeleteObject(m_GreenPen);
	DeleteObject(m_OldPen);
  DeleteObject(m_GreyPenDotted);
  DeleteObject(m_RedPenDotted);
  DeleteObject(m_BlueBrush);
  DeleteObject(m_RedBrush);
}


//-------------------------------------Update---------------------------------------
//
//	This is the main workhorse. The entire simulation is controlled from here.
//
//--------------------------------------------------------------------------------------
bool CController::Update()
{
	//run the sweepers through NUM_TICKS amount of cycles. During this loop each
	//sweepers NN is constantly updated with the appropriate information from its 
	//surroundings. The output from the NN is obtained and the sweeper is moved. 
	if (m_iTicks++ < CParams::iNumTicks)
	{
		for (int i=0; i<m_NumSweepers; ++i)
		{
			//update the NN and position
			if (!m_vecSweepers[i].Update(m_ObjectsVB))
			{
				//error in processing the neural net
				MessageBox(m_hwndMain, "Wrong amount of NN inputs!", "Error", MB_OK);

				return false;
			}
		}

    //update the NNs of the last generations best performers
    if (m_iGenerations > 0)
    {
      for (int i=0; i<m_vecBestSweepers.size(); ++i)
      {
         //update the NN and position
			   if (!m_vecBestSweepers[i].Update(m_ObjectsVB))
			   {
				    //error in processing the neural net
				    MessageBox(m_hwndMain, "Wrong amount of NN inputs!", "Error", MB_OK);

				    return false;
			   }
      }
    }
	}

	//We have completed another generation so now we need to run the GA
	else
	{    
    //first add up each sweepers fitness scores. (remember for this task
    //there are many different sorts of penalties the sweepers may incur
    //and each one has a coefficient)
    for (int swp=0; swp<m_vecSweepers.size(); ++swp)
    {
        m_vecSweepers[swp].EndOfRunCalculations();
    }

		//increment the generation counter
		++m_iGenerations;

		//reset cycles
		m_iTicks = 0;

    //perform an epoch and grab the new brains
    vector<CNeuralNet*> pBrains = m_pPop->Epoch(GetFitnessScores());
			
		//insert the new  brains back into the sweepers and reset their
    //positions
    for (int i=0; i<m_NumSweepers; ++i)
		{
			m_vecSweepers[i].InsertNewBrain(pBrains[i]);
		
			m_vecSweepers[i].Reset();
		}

    //grab the NNs of the best performers from the last generation
    vector<CNeuralNet*> pBestBrains = m_pPop->GetBestPhenotypesFromLastGeneration();

    //put them into our record of the best sweepers
    for (i=0; i<m_vecBestSweepers.size(); ++i)
		{
			m_vecBestSweepers[i].InsertNewBrain(pBestBrains[i]);
		
			m_vecBestSweepers[i].Reset();
		}

        //this will call WM_PAINT which will render our scene
	  InvalidateRect(m_hwndInfo, NULL, TRUE);
		UpdateWindow(m_hwndInfo);

	}

	return true;
}

//---------------------------------- RenderNetworks ----------------------
//
//  Renders the best four phenotypes from the previous generation
//------------------------------------------------------------------------
void CController::RenderNetworks(HDC &surface)
{
  if (m_iGenerations < 1)
  {
    return;
  }

  //draw the network of the best 4 genomes. First get the dimensions of the 
   //info window
   RECT rect;
	GetClientRect(m_hwndInfo, &rect);

	int	cxInfo = rect.right;
	int	cyInfo = rect.bottom;

   //now draw the 4 best networks
   m_vecBestSweepers[0].DrawNet(surface, 0, cxInfo/2, cyInfo/2, 0);
   m_vecBestSweepers[1].DrawNet(surface, cxInfo/2, cxInfo, cyInfo/2, 0);
   m_vecBestSweepers[2].DrawNet(surface, 0, cxInfo/2, cyInfo, cyInfo/2);
   m_vecBestSweepers[3].DrawNet(surface, cxInfo/2, cxInfo, cyInfo, cyInfo/2);
}

//------------------------------------Render()--------------------------------------
//
//----------------------------------------------------------------------------------
void CController::Render(HDC &surface)
{
	//do not render if running at accelerated speed
	if (!m_bFastRender)
	{   
    string s = "Generation: " + itos(m_iGenerations);
	  TextOut(surface, 5, 0, s.c_str(), s.size());
    
    //select in the blue pen
    m_OldPen = (HPEN)SelectObject(surface, m_BluePen);
    
    if (m_bRenderBest)
    {  		
      //render the best sweepers memory cells
      m_vecBestSweepers[m_iViewThisSweeper].Render(surface);

      //render the best sweepers from the last generation
      RenderSweepers(surface, m_vecBestSweepers);

      //render the best sweepers sensors
      RenderSensors(surface, m_vecBestSweepers);
    }
      
    else
    {
		  //render the sweepers
      RenderSweepers(surface, m_vecSweepers);
    }

    SelectObject(surface, m_OldPen);

    //render the objects
    for (int i=0; i<NumObjectVerts; i+=2)
    {
      MoveToEx(surface, m_ObjectsVB[i].x, m_ObjectsVB[i].y, NULL);

      LineTo(surface, m_ObjectsVB[i+1].x, m_ObjectsVB[i+1].y);
    }

	}//end if
 
  else
  {    
    PlotStats(surface);

    RECT sr;
    sr.top    = m_cyClient-50;
    sr.bottom = m_cyClient;
    sr.left   = 0;
    sr.right  = m_cxClient;

    //render the species chart
    m_pPop->RenderSpeciesInfo(surface, sr);

  }

}
//------------------------- RenderSweepers -------------------------------
//
//  given a vector of sweepers this function renders them to the screen
//------------------------------------------------------------------------
void CController::RenderSweepers(HDC &surface, vector<CMinesweeper> &sweepers)
{
  for (int i=0; i<sweepers.size(); ++i)
	{
    
    //if they have crashed into an obstacle draw
    if ( sweepers[i].Collided())
    {
      SelectObject(surface, m_RedPen);
    }

    else
    {
      SelectObject(surface, m_BluePen);
    }
      
    //grab the sweeper vertices
	  vector<SPoint> sweeperVB = m_SweeperVB;

	  //transform the vertex buffer
	  sweepers[i].WorldTransform(sweeperVB, sweepers[i].Scale());

	  //draw the sweeper left track
		MoveToEx(surface, (int)sweeperVB[0].x, (int)sweeperVB[0].y, NULL);

		for (int vert=1; vert<4; ++vert)
		{
		  LineTo(surface, (int)sweeperVB[vert].x, (int)sweeperVB[vert].y);
		}

    LineTo(surface, (int)sweeperVB[0].x, (int)sweeperVB[0].y);

    //draw the sweeper right track
	  MoveToEx(surface, (int)sweeperVB[4].x, (int)sweeperVB[4].y, NULL);

		for (vert=5; vert<8; ++vert)
		{
	    LineTo(surface, (int)sweeperVB[vert].x, (int)sweeperVB[vert].y);
		}

    LineTo(surface, (int)sweeperVB[4].x, (int)sweeperVB[4].y);

    MoveToEx(surface, (int)sweeperVB[8].x, (int)sweeperVB[8].y, NULL);
    LineTo(surface, (int)sweeperVB[9].x, (int)sweeperVB[9].y);

    MoveToEx(surface, (int)sweeperVB[10].x, (int)sweeperVB[10].y, NULL);

    for (vert=11; vert<16; ++vert)
    {
		   LineTo(surface, (int)sweeperVB[vert].x, (int)sweeperVB[vert].y);
		}
	}//next sweeper
}

//----------------------------- RenderSensors ----------------------------
//
//  renders the sensors of a given vector of sweepers
//------------------------------------------------------------------------
void CController::RenderSensors(HDC &surface, vector<CMinesweeper> &sweepers)
{
   //render the sensors
    for (int i=0; i<sweepers.size(); ++i)
    {
      //grab each sweepers sensor data
      vector<SPoint> tranSensors    = sweepers[i].Sensors();
      vector<double> SensorReadings = sweepers[i].SensorReadings();
      vector<double> MemoryReadings = sweepers[i].MemoryReadings();

      for (int sr=0; sr<tranSensors.size(); ++sr)
      {
        if (SensorReadings[sr] > 0)
        {
          SelectObject(surface, m_RedPen);
        }

        else
        {
          SelectObject(surface, m_GreyPenDotted);
        }
        
        //make sure we clip the drawing of the sensors or we will get
        //unwanted artifacts appearing
        if (!((fabs(sweepers[i].Position().x - tranSensors[sr].x) >
              (CParams::dSensorRange+1))||
              (fabs(sweepers[i].Position().y - tranSensors[sr].y) >
              (CParams::dSensorRange+1))))
        {
        
          MoveToEx(surface,
                   (int)sweepers[i].Position().x,
                   (int)sweepers[i].Position().y,
                   NULL);

          LineTo(surface, (int)tranSensors[sr].x, (int)tranSensors[sr].y);

          //render the cell sensors
          RECT rect;
          rect.left  = (int)tranSensors[sr].x - 2;
          rect.right = (int)tranSensors[sr].x + 2;
          rect.top   = (int)tranSensors[sr].y - 2;
          rect.bottom= (int)tranSensors[sr].y + 2;
          
          if (MemoryReadings[sr] < 0)
          {

            FillRect(surface, &rect, m_BlueBrush);
          }

          else
          {
            FillRect(surface, &rect, m_RedBrush);
          }
          
        }
      }
    }   
}


//--------------------------PlotStats-------------------------------------
//
//  Given a surface to draw on this function displays some simple stats 
//------------------------------------------------------------------------
void CController::PlotStats(HDC surface)const
{
    string s = "Generation:              " + itos(m_iGenerations);
	  TextOut(surface, 5, 25, s.c_str(), s.size());
    
    s = "Num Species:          " + itos(m_pPop->NumSpecies());
	  TextOut(surface, 5, 45, s.c_str(), s.size());

    s = "Best Fitness so far: " + ftos(m_pPop->BestEverFitness());
    TextOut(surface, 5, 5, s.c_str(), s.size());
}


//------------------------------- GetFitnessScores -----------------------
//
//  returns a std::vector containing the genomes fitness scores
//------------------------------------------------------------------------
vector<double> CController::GetFitnessScores()const
{
  vector<double> scores;

  for (int i=0; i<m_vecSweepers.size(); ++i)
  {
     scores.push_back(m_vecSweepers[i].Fitness());
  }
  return scores;
}