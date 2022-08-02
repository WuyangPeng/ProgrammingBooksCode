#include "CController.h"
#include "resource.h"



string CController::m_sPatternName = "";


//--------------------------------- ctor -------------------------------
//
//----------------------------------------------------------------------
CController::CController(HWND hwnd):m_bDrawing(false),
                          m_iNumSmoothPoints(NUM_VECTORS+1),
                          m_hwnd(hwnd),
                          m_dHighestOutput(0),
                          m_iBestMatch(-1),
                          m_iMatch(-1),
                          m_iNumValidPatterns(NUM_PATTERNS),
                          m_Mode(UNREADY)
                         
{
  //create the database
  m_pData = new CData(m_iNumValidPatterns, NUM_VECTORS);

  //setup the network
  m_pNet = new CNeuralNet(NUM_VECTORS*2,        //inputs
                          m_iNumValidPatterns,  //outputs
                          NUM_HIDDEN_NEURONS,   //hidden
                          LEARNING_RATE);
                          
}

//--------------------------------- dtor --------------------------------
//
//-----------------------------------------------------------------------
CController::~CController()
{
  delete m_pData;
  delete m_pNet;
}
//-----------------------------------------------------------------
//
//  message handler for the dialog box
//-----------------------------------------------------------------
BOOL CALLBACK CController::DialogProc(HWND   hwnd,
                                 UINT   msg,
                                 WPARAM wParam,
                                 LPARAM lParam)
{
  switch(msg)
  {
  case WM_INITDIALOG:
    {
      return true;
    }

    break;

  case WM_COMMAND:
    {
      switch(LOWORD(wParam))
      {
      case IDOK:
        {
          //get a handle to the edit control
          HWND hwndEdit = GetDlgItem(hwnd, IDC_GRAB_NAME); 

          //set the focus
          SetFocus(hwndEdit);

          //get the text
          char buffer[30]; 

          GetWindowText(hwndEdit, buffer, 30);

          m_sPatternName = buffer;

          //if the user hasn't entered a name set name
          if (m_sPatternName.size == 0)
          {
            m_sPatternName = "User defined pattern";
          }
          
          EndDialog(hwnd, 0);

          return true;
        }

        break;
      }
    }

    break;

  }//end switch

  return false;
}

//--------------------------- Clear --------------------------------------
//
//  clears the current data
//------------------------------------------------------------------------
void CController::Clear()
{
  m_vecPath.clear();
  m_vecSmoothPath.clear();
  m_vecVectors.clear();
}

//------------------------------ Drawing ---------------------------------
//
//  this is called whenever the user depresses or releases the right
//  mouse button.
//  If val is true then the right mouse button has been depressed so all
//  mouse data is cleared ready for the next gesture. If val is false a
//  gesture has just been completed. The gesture is then either added to
//  the current data set or it is tested to see if it matches an existing
//  pattern.
//  The hInstance is required so a dialog box can be created as a child
//  window of the main app instance. The dialog box is used to grab the
//  name of any user defined gesture
//------------------------------------------------------------------------
bool CController::Drawing(bool val, HINSTANCE hInstance)
{
  if (val == true)
  {
    Clear();
  }

  else
  {
    //smooth and vectorize the data if we have enough points
    if (Smooth())
    {
      //create the vectors
      CreateVectors();

      if (m_Mode == ACTIVE)
      {

        if (!TestForMatch())
        {
          return false;
        }
      }

      else
      {
        //add the data set if user is happy with it
        if(MessageBox(m_hwnd, "Happy with this gesture?", "OK?", MB_YESNO) == IDYES)
        {
           //grab a name for this pattern
          DialogBox(hInstance,
                    MAKEINTRESOURCE(IDD_DIALOG1),
                    m_hwnd,
                    DialogProc);

          
           //add the data
           m_pData->AddData(m_vecVectors, m_sPatternName);

           //delete the old network
           delete m_pNet;

           ++m_iNumValidPatterns;

           //create a new network
           m_pNet = new CNeuralNet(NUM_VECTORS*2,
                                   m_iNumValidPatterns,
                                   NUM_VECTORS*2,
                                   LEARNING_RATE);

           //train the network
           TrainNetwork();

           m_Mode = ACTIVE;
         }

         else
         {
           //clear dismissed gesture
           m_vecPath.clear();
         }
      }
    }
  }
    
  m_bDrawing = val;

  return true;
}

//------------------------------ TrainNetwork -----------------------------
//
//  Trains the neural net work with the predefined training set
//-------------------------------------------------------------------------
bool CController::TrainNetwork()
{  
  m_Mode = TRAINING;

  if(!m_pNet->Train(m_pData, m_hwnd))
  {
    return false;
  }

  m_Mode = ACTIVE;

  return true;
}
  

//------------------------- TestForMatch ----------------------------------
//
//  checks the mouse pattern to see if it matches one of the learned
//  patterns
//-------------------------------------------------------------------------
bool CController::TestForMatch()
{
  //input the smoothed mouse vectors into the net and see if we get a match
  vector<double> outputs = m_pNet->Update(m_vecVectors);

  if (outputs.size() == 0)
  {
    MessageBox(NULL, "Error in with ANN output", "Error!", MB_OK);

    return false;
  }

  //run through the outputs and see which is highest
  m_dHighestOutput = 0;
  m_iBestMatch = 0;
  m_iMatch = -1;
  
  for (int i=0; i<outputs.size(); ++i)
  {
    if (outputs[i] > m_dHighestOutput)
    {
      //make a note of the most likely candidate
      m_dHighestOutput = outputs[i];

      m_iBestMatch = i;
 

      //if the candidates output exceeds the threshold we 
      //have a match! ...so make a note of it.
      if (m_dHighestOutput > MATCH_TOLERANCE)
      {
        m_iMatch = m_iBestMatch;
                  
      }
    }
  }

  return true;
}

//----------------------------------- CreateVectors ----------------------
//
//  this function creates normalized vectors out of the series of POINTS
//  in m_vecSmoothPoints
//------------------------------------------------------------------------
void CController::CreateVectors()
{ 
  for (int p=1; p<m_vecSmoothPath.size(); ++p)
  {    

    double x = m_vecSmoothPath[p].x - m_vecSmoothPath[p-1].x;
    double y = m_vecSmoothPath[p].y - m_vecSmoothPath[p-1].y;

    SVector2D v1(1, 0);
    SVector2D v2(x, y);

    Vec2DNormalize(v2);

    m_vecVectors.push_back(v2.x);
    m_vecVectors.push_back(v2.y);
  }

}

//------------------------------------- Smooth ---------------------------
//
//------------------------------------------------------------------------
bool CController::Smooth()
{
  //make sure it contains enough points for us to work with
  if (m_vecPath.size() < m_iNumSmoothPoints)
  {
    //return
    return false;
  }

  //copy the raw mouse data
  m_vecSmoothPath = m_vecPath;

  //while there are excess points iterate through the points
  //finding the shortest spans, creating a new point in its place
  //and deleting the adjacent points.
  while (m_vecSmoothPath.size() > m_iNumSmoothPoints)
  {
    double ShortestSoFar = 99999999;

    int PointMarker = 0;

    //calculate the shortest span
    for (int SpanFront=2; SpanFront<m_vecSmoothPath.size()-1; ++SpanFront)
    {
      //calculate the distance between these points
      double length = 
      sqrt( (m_vecSmoothPath[SpanFront-1].x - m_vecSmoothPath[SpanFront].x) *
            (m_vecSmoothPath[SpanFront-1].x - m_vecSmoothPath[SpanFront].x) +

            (m_vecSmoothPath[SpanFront-1].y - m_vecSmoothPath[SpanFront].y)*
            (m_vecSmoothPath[SpanFront-1].y - m_vecSmoothPath[SpanFront].y));

      if (length < ShortestSoFar)
      {
        ShortestSoFar = length;

        PointMarker = SpanFront;
      }      
    }

    //now the shortest span has been found calculate a new point in the 
    //middle of the span and delete the two end points of the span
    POINTS newPoint;

    newPoint.x = (m_vecSmoothPath[PointMarker-1].x + 
                  m_vecSmoothPath[PointMarker].x)/2;

    newPoint.y = (m_vecSmoothPath[PointMarker-1].y +
                  m_vecSmoothPath[PointMarker].y)/2;

    m_vecSmoothPath[PointMarker-1] = newPoint;

    m_vecSmoothPath.erase(m_vecSmoothPath.begin() + PointMarker);
  }

  return true;
}

//--------------------------------- LearningMode -------------------------
//
//  clears the screen and puts the app into learning mode, ready to accept
//  a user defined gesture
//------------------------------------------------------------------------
void CController::LearningMode()
{
  m_Mode = LEARNING;

  Clear();

  //update window
  InvalidateRect(m_hwnd, NULL, TRUE);
  UpdateWindow(m_hwnd);
}
			
//-------------------------------- Render --------------------------------
//
//------------------------------------------------------------------------
void CController::Render(HDC &surface, int cxClient, int cyClient)
{
    
  //render error from any training taking place
  if(m_Mode == TRAINING)
  {   
    string s = "Error: " + ftos(m_pNet->Error());
    TextOut(surface, cxClient/2, 5, s.c_str(), s.size());

     s = "Epochs: " + ftos(m_pNet->Epoch());
    TextOut(surface, 5, 5, s.c_str(), s.size());
  }

  if (m_pNet->Trained())
  {
    if ((m_Mode == ACTIVE))
    {
       string s = "Recognition circuits active";
       TextOut(surface, 5, cyClient-20, s.c_str(), s.size());
    }

    if (m_Mode == LEARNING)
    {
      string s = "Recognition circuits offline - Enter a new gesture";
      TextOut(surface, 5, cyClient-20, s.c_str(), s.size());
    }
  }

  else
  {
     string s = "Training in progress...";
     TextOut(surface, 5, cyClient-20, s.c_str(), s.size());
  }


  if (!m_bDrawing)
  {  
    //render best match
    if (m_dHighestOutput > 0)
    {
   
      if ( (m_vecSmoothPath.size() > 1) && (m_Mode != LEARNING) )
      {
        if (m_dHighestOutput < MATCH_TOLERANCE)
        {
          string s = "I'm guessing this is the pattern " + 
                     m_pData->PatternName(m_iBestMatch); 

          TextOut(surface, 5, 10, s.c_str(), s.size());
        }

        else
        {
          SetTextColor(surface, RGB(0, 0, 255));

          string s = m_pData->PatternName(m_iMatch);
          TextOut(surface, 5, 10, s.c_str(), s.size());

          SetTextColor(surface, RGB(0, 0, 0));

        }
      }

      else if (m_Mode != LEARNING)
      {
        SetTextColor(surface, RGB(255, 0, 0));

        string s = "Not enough points drawn - plz try again";
        TextOut(surface, 5, 10, s.c_str(), s.size());

        SetTextColor(surface, RGB(0, 0, 0));
      }
    }
  }
  
  if (m_vecPath.size() < 1)
  {
    return;
  }
  
  MoveToEx(surface, m_vecPath[0].x, m_vecPath[0].y, NULL);

  for (int vtx=1; vtx<m_vecPath.size(); ++vtx)
  {
    LineTo(surface, m_vecPath[vtx].x, m_vecPath[vtx].y);
  }
  
  //draw the points which make up the smoothed path
  if ((!m_bDrawing) && (m_vecSmoothPath.size() > 0))
  {
    for (int vtx=0; vtx<m_vecPath.size(); ++vtx)
    {
      POINTS pt = m_vecSmoothPath[vtx];

      Ellipse(surface, pt.x-2, pt.y-2, pt.x+2, pt.y+2);
    }
  }	 
}