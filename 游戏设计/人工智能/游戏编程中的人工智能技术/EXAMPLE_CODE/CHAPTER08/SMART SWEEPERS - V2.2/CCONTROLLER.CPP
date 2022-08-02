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
CController::CController(HWND hwndMain): m_NumSweepers(CParams::iNumSweepers), 
										                     m_pGA(NULL),
										                     m_bFastRender(false),
										                     m_iTicks(0),
										                     m_hwndMain(hwndMain),
										                     m_iGenerations(0),
                                         cxClient(CParams::WindowWidth),
                                         cyClient(CParams::WindowHeight)
                                        
{
	//let's create the mine sweepers
	for (int i=0; i<m_NumSweepers; ++i)
	{
		m_vecSweepers.push_back(CMinesweeper());
	}

	//get the total number of weights used in the sweepers
	//NN so we can initialise the GA
	m_NumWeightsInNN = m_vecSweepers[0].GetNumberOfWeights();

  //calculate the neuron placement in the weight vector
  vector<int> SplitPoints = m_vecSweepers[0].CalculateSplitPoints();

	//initialize the Genetic Algorithm class
	m_pGA = new CGenAlg(m_NumSweepers,
                      CParams::dMutationRate,
	                    CParams::dCrossoverRate,
	                    m_NumWeightsInNN,
                      SplitPoints);

	//Get the weights from the GA and insert into the sweepers brains
	m_vecThePopulation = m_pGA->GetChromos();

	for (i=0; i<m_NumSweepers; i++)
  {
		m_vecSweepers[i].PutWeights(m_vecThePopulation[i].vecWeights);
  }


	//create the pens for the graph drawing
	m_BluePen        = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_RedPen         = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_GreenPen       = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
  m_GreyPenDotted  = CreatePen(PS_DOT, 1, RGB(200, 200, 200));
  m_RedPenDotted   = CreatePen(PS_DOT, 1, RGB(250, 200, 200));

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
	if(m_pGA)
  {
    delete m_pGA;
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


//---------------------WorldTransform--------------------------------
//
//	sets up the translation matrices for the mines and applies the
//	world transform to each vertex in the vertex buffer passed to this
//	method.
//-------------------------------------------------------------------
void CController::WorldTransform(vector<SPoint> &VBuffer,
                                 SVector2D      vPos,
                                 double         rotation,
                                 double         scale)
{
	//create the world transformation matrix
	C2DMatrix matTransform;
	
	//scale
	matTransform.Scale(scale, scale);

   	//rotate
	matTransform.Rotate(rotation);
	
	//translate
	matTransform.Translate(vPos.x, vPos.y);


	//transform the ships vertices
	matTransform.TransformSPoints(VBuffer);
}


//-------------------------------------Update---------------------------------------
//
//	This is the main workhorse. The entire simulation is controlled from here.
//
//	The comments should explain what is going on adequately.
//--------------------------------------------------------------------------------------
bool CController::Update()
{
	
	//run the sweepers through CParams::iNumTicks amount of cycles. During this loop each
	//sweepers NN is constantly updated with the appropriate information from its 
	//surroundings. The output from the NN is obtained and the sweeper is moved. If
	//it encounters a mine its fitness is updated appropriately,
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
	}

	//**We have completed another generation.

	//Time to run the GA and update the sweepers with their new NNs
	else
	{
    int BestCellCoverage = 0;

    for (int swp=0; swp<m_vecSweepers.size(); ++swp)
    {
       //add up all the penalties and calculate a fitness score
       m_vecSweepers[swp].EndOfRunCalculations();

       //update the fitness score stored in the GA with this score
			 m_vecThePopulation[swp].dFitness = m_vecSweepers[swp].Fitness();

       if (m_vecSweepers[swp].NumCellsVisited() > BestCellCoverage)
       {
         BestCellCoverage = m_vecSweepers[swp].NumCellsVisited();
       }
    }

		//update the stats to be used in our stat window
		m_vecAvFitness.push_back(fabs(m_pGA->AverageRawFitness()));
		m_vecBestFitness.push_back(fabs(m_pGA->BestRawFitness()));

		//increment the generation counter
		++m_iGenerations;

		//reset cycles
		m_iTicks = 0;

		//insert the sweepers chromosones into the GA factory and
		//run the factory to create a new population
		m_vecThePopulation = m_pGA->Epoch(m_vecThePopulation);
			
		//insert the new (hopefully)improved brains back into the sweepers
    //and reset their positions etc
    for (int i=0; i<m_NumSweepers; ++i)
		{
			m_vecSweepers[i].PutWeights(m_vecThePopulation[i].vecWeights);
		
			m_vecSweepers[i].Reset();
		}
	}

	return true;
}
//------------------------------------Render()--------------------------------------
//
//----------------------------------------------------------------------------------
void CController::Render(HDC surface)
{
	//render the stats
	string s = "Generation: " + itos(m_iGenerations);
	TextOut(surface, 5, 0, s.c_str(), s.size());

	//do not render if running at accelerated speed
	if (!m_bFastRender)
	{
		//display the penalties
    m_vecSweepers[0].Render(surface);
    
    //render the objects
    for (int i=0; i<NumObjectVerts; i+=2)
    {
      MoveToEx(surface, m_ObjectsVB[i].x, m_ObjectsVB[i].y, NULL);

      LineTo(surface, m_ObjectsVB[i+1].x, m_ObjectsVB[i+1].y);
    }

   		
    //we want the fittest displayed in green
    m_OldPen = (HPEN)SelectObject(surface, m_GreenPen);

		//render the sweepers
		for (i=0; i<m_vecSweepers.size(); i++)
		{
			if (i < CParams::iNumElite)
      {
        SelectObject(surface,m_OldPen);        
      }

      else
      {
        SelectObject(surface, m_GreyPenDotted);
      }

      //render red if collided and elite
      if ( m_vecSweepers[i].Collided() && (i < CParams::iNumElite) )
      {
        SelectObject(surface, m_RedPen);
      }
      
      //render dotted red if collided and not elite
      if ( m_vecSweepers[i].Collided() && (i > CParams::iNumElite) )
      {
        SelectObject(surface, m_RedPenDotted);
      }
      
      //grab the sweeper vertices
			vector<SPoint> sweeperVB = m_SweeperVB;

			//transform the vertex buffer
			m_vecSweepers[i].WorldTransform(sweeperVB, m_vecSweepers[i].Scale());

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

		}

    //render the sensors
    for (i=0; i<CParams::iNumElite; ++i)
    {
      //grab each sweepers sensor data
      vector<SPoint> tranSensors    = m_vecSweepers[i].Sensors();
      vector<double>   SensorReadings = m_vecSweepers[i].SensorReadings();
      vector<double> MemoryReadings = m_vecSweepers[i].MemoryReadings();

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
        if (!((fabs(m_vecSweepers[i].Position().x - tranSensors[sr].x) >
              (CParams::dSensorRange+1))||
              (fabs(m_vecSweepers[i].Position().y - tranSensors[sr].y) >
              (CParams::dSensorRange+1))))
        {
        
          MoveToEx(surface,
                   (int)m_vecSweepers[i].Position().x,
                   (int)m_vecSweepers[i].Position().y,
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

    SelectObject(surface, m_OldPen);

	}//end if

  else
  {
    PlotStats(surface);
  }

}
//--------------------------PlotStats-------------------------------------
//
//  Given a surface to draw on this function displays stats and a crude
//  graph showing best and average fitness
//------------------------------------------------------------------------
void CController::PlotStats(HDC surface)
{
   
    string s = "Best Fitness:       " + ftos(m_pGA->BestRawFitness());
	  TextOut(surface, 5, 20, s.c_str(), s.size());

     s = "Average Fitness: " + ftos(m_pGA->AverageRawFitness());
	  TextOut(surface, 5, 40, s.c_str(), s.size());
    
    //render the graph
    float HSlice = (float)cxClient/(m_iGenerations+1);
    float VSlice = (float)cyClient/((m_pGA->BestRawFitness()+1) * 1.5);

    //plot the graph for the best fitness
    float x = 0;
    
    m_OldPen = (HPEN)SelectObject(surface, m_RedPen);

    MoveToEx(surface, 0, cyClient, NULL);
    
    for (int i=0; i<m_vecBestFitness.size(); ++i)
    {
       LineTo(surface, x, (cyClient - VSlice*m_vecBestFitness[i]));

       x += HSlice;
    }

    //plot the graph for the average fitness
    x = 0;

    SelectObject(surface, m_BluePen);

    MoveToEx(surface, 0, cyClient, NULL);
    
    for (i=0; i<m_vecAvFitness.size(); ++i)
    {
       LineTo(surface, x, (cyClient - VSlice*m_vecAvFitness[i]));

       x += HSlice;
    }

    //replace the old pen
    SelectObject(surface, m_OldPen);
}

