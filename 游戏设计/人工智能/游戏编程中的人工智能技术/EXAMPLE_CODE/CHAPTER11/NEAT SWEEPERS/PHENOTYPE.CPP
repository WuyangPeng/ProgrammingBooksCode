#include "phenotype.h"

//------------------------------------Sigmoid function------------------------
//
//----------------------------------------------------------------------------

float Sigmoid(float netinput, float response)
{
	return ( 1 / ( 1 + exp(-netinput / response)));
}


//--------------------------------- ctor ---------------------------------
//
//------------------------------------------------------------------------
CNeuralNet::CNeuralNet(vector<SNeuron*> neurons,
                       int              depth):m_vecpNeurons(neurons),
                                               m_iDepth(depth)
{}


//--------------------------------- dtor ---------------------------------
//
//------------------------------------------------------------------------
CNeuralNet::~CNeuralNet()
{
  //delete any live neurons
  for (int i=0; i<m_vecpNeurons.size(); ++i)
  {
    if (m_vecpNeurons[i])
    {
      delete m_vecpNeurons[i];

      m_vecpNeurons[i] = NULL;
    }
  }
}

//----------------------------------Update--------------------------------
//	takes a list of doubles as inputs into the network then steps through 
//  the neurons calculating each neurons next output.
//
//	finally returns a std::vector of doubles as the output from the net.
//------------------------------------------------------------------------
vector<double> CNeuralNet::Update(const vector<double> &inputs,
                                  const run_type        type)
{
  //create a vector to put the outputs into
  vector<double>	outputs;

  //if the mode is snapshot then we require all the neurons to be
  //iterated through as many times as the network is deep. If the 
  //mode is set to active the method can return an output after
  //just one iteration
  int FlushCount = 0;
  
  if (type == snapshot)
  {
    FlushCount = m_iDepth;
  }
  else
  {
    FlushCount = 1;
  }

  //iterate through the network FlushCount times
  for (int i=0; i<FlushCount; ++i)
  {
    //clear the output vector
    outputs.clear();
   
    //this is an index into the current neuron
    int cNeuron = 0;

    //first set the outputs of the 'input' neurons to be equal
    //to the values passed into the function in inputs
    while (m_vecpNeurons[cNeuron]->NeuronType == input)
    {
      m_vecpNeurons[cNeuron]->dOutput = inputs[cNeuron];

      ++cNeuron;
    }

    //set the output of the bias to 1
    m_vecpNeurons[cNeuron++]->dOutput = 1;

    //then we step through the network a neuron at a time
    while (cNeuron < m_vecpNeurons.size())
    {
      //this will hold the sum of all the inputs x weights 
      double sum = 0;

      //sum this neuron's inputs by iterating through all the links into
      //the neuron
      for (int lnk=0; lnk<m_vecpNeurons[cNeuron]->vecLinksIn.size(); ++lnk)
      {
        //get this link's weight
        double Weight = m_vecpNeurons[cNeuron]->vecLinksIn[lnk].dWeight;

        //get the output from the neuron this link is coming from
        double NeuronOutput =
        m_vecpNeurons[cNeuron]->vecLinksIn[lnk].pIn->dOutput;

        //add to sum
        sum += Weight * NeuronOutput;
      }

      //now put the sum through the activation function and assign the 
      //value to this neuron's output
      m_vecpNeurons[cNeuron]->dOutput = 
      Sigmoid(sum, m_vecpNeurons[cNeuron]->dActivationResponse);

      if (m_vecpNeurons[cNeuron]->NeuronType == output)
      {
        //add to our outputs
        outputs.push_back(m_vecpNeurons[cNeuron]->dOutput);
      }

      //next neuron
      ++cNeuron;
    }

  }//next iteration through the network

  //the network needs to be flushed if this type of update is performed
  //otherwise it is possible for dependencies to be built on the order
  //the training data is presented
  if (type == snapshot)
  {
    for (int n=0; n<m_vecpNeurons.size(); ++n)
    {
      m_vecpNeurons[n]->dOutput = 0;
    }
  }

  //return the outputs
  return outputs;
}

//----------------------------- TidyXSplits -----------------------------
//
//  This is a fix to prevent neurons overlapping when they are displayed
//-----------------------------------------------------------------------
void TidyXSplits(vector<SNeuron*> &neurons)
{
  //stores the index of any neurons with identical splitY values 
  vector<int>    SameLevelNeurons;

  //stores all the splitY values already checked
  vector<double> DepthsChecked;


  //for each neuron find all neurons of identical ySplit level
  for (int n=0; n<neurons.size(); ++n)
  {
    double ThisDepth = neurons[n]->dSplitY;

    //check to see if we have already adjusted the neurons at this depth
    bool bAlreadyChecked = false;

    for (int i=0; i<DepthsChecked.size(); ++i)
    {
      if (DepthsChecked[i] == ThisDepth)
      {
        bAlreadyChecked = true;

        break;
      }
    }

    //add this depth to the depths checked.
    DepthsChecked.push_back(ThisDepth);

    //if this depth has not already been adjusted
    if (!bAlreadyChecked)
    {
      //clear this storage and add the neuron's index we are checking
      SameLevelNeurons.clear();
      SameLevelNeurons.push_back(n);
      
      //find all the neurons with this splitY depth
      for (int i=n+1; i<neurons.size(); ++i)
      {
        if (neurons[i]->dSplitY == ThisDepth)
        {
          //add the index to this neuron
          SameLevelNeurons.push_back(i);
        }
      }

      //calculate the distance between each neuron
      double slice = 1.0/(SameLevelNeurons.size()+1);
  

      //separate all neurons at this level
      for (i=0; i<SameLevelNeurons.size(); ++i)
      {
        int idx = SameLevelNeurons[i];

        neurons[idx]->dSplitX = (i+1) * slice;
      }
    }

  }//next neuron to check

}
//----------------------------- DrawNet ----------------------------------
//
//  creates a representation of the ANN on a device context
//
//------------------------------------------------------------------------
void CNeuralNet::DrawNet(HDC &surface, int Left, int Right, int Top, int Bottom)
{
  //the border width
  const int border = 10;
    
  //max line thickness
  const int MaxThickness = 5;

  TidyXSplits(m_vecpNeurons);

  //go through the neurons and assign x/y coords
  int spanX = Right - Left;
  int spanY = Top - Bottom - (2*border);

  for (int cNeuron=0; cNeuron<m_vecpNeurons.size(); ++cNeuron)
  {
    m_vecpNeurons[cNeuron]->iPosX = Left + spanX*m_vecpNeurons[cNeuron]->dSplitX;
    m_vecpNeurons[cNeuron]->iPosY = (Top - border) - (spanY * m_vecpNeurons[cNeuron]->dSplitY);
  }

  //create some pens and brushes to draw with
  HPEN GreyPen  = CreatePen(PS_SOLID, 1, RGB(200, 200, 200));
  HPEN RedPen   = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
  HPEN GreenPen = CreatePen(PS_SOLID, 1, RGB(0, 200, 0));
  HPEN OldPen   = NULL;

  //create a solid brush
  HBRUSH RedBrush = CreateSolidBrush(RGB(255, 0, 0));
  HBRUSH OldBrush = NULL;

  OldPen =   (HPEN)  SelectObject(surface, RedPen);
  OldBrush = (HBRUSH)SelectObject(surface, GetStockObject(HOLLOW_BRUSH));


  //radius of neurons
  int radNeuron = spanX/60;
  int radLink = radNeuron * 1.5;
  
  //now we have an X,Y pos for every neuron we can get on with the
  //drawing. First step through each neuron in the network and draw
  //the links
  for (cNeuron=0; cNeuron<m_vecpNeurons.size(); ++cNeuron)
  {
    //grab this neurons position as the start position of each
    //connection
    int StartX = m_vecpNeurons[cNeuron]->iPosX;
    int StartY = m_vecpNeurons[cNeuron]->iPosY;

    //is this a bias neuron? If so, draw the link in green
    bool bBias = false;

    if (m_vecpNeurons[cNeuron]->NeuronType == bias)
    {
      bBias = true;
    }

    //now iterate through each outgoing link to grab the end points
    for (int cLnk=0; cLnk<m_vecpNeurons[cNeuron]->vecLinksOut.size(); ++ cLnk)
    {
      int EndX = m_vecpNeurons[cNeuron]->vecLinksOut[cLnk].pOut->iPosX;
      int EndY = m_vecpNeurons[cNeuron]->vecLinksOut[cLnk].pOut->iPosY;

      //if link is forward draw a straight line
      if( (!m_vecpNeurons[cNeuron]->vecLinksOut[cLnk].bRecurrent) && !bBias)
      {
        int thickness = (int)(fabs(m_vecpNeurons[cNeuron]->vecLinksOut[cLnk].dWeight));        
        
        Clamp(thickness, 0, MaxThickness);

        HPEN Pen;

        //create a yellow pen for inhibitory weights
        if (m_vecpNeurons[cNeuron]->vecLinksOut[cLnk].dWeight <= 0)
        {
          Pen  = CreatePen(PS_SOLID, thickness, RGB(240, 230, 170));
        }

        //grey for excitory
        else
        {
          Pen  = CreatePen(PS_SOLID, thickness, RGB(200, 200, 200));
        }
        
        HPEN tempPen = (HPEN)SelectObject(surface, Pen);
        
        //draw the link
        MoveToEx(surface, StartX, StartY, NULL);
        LineTo(surface, EndX, EndY);

        SelectObject(surface, tempPen);

        DeleteObject(Pen);
      }

      else if( (!m_vecpNeurons[cNeuron]->vecLinksOut[cLnk].bRecurrent) && bBias)
      {
        SelectObject(surface, GreenPen);
        
        //draw the link
        MoveToEx(surface, StartX, StartY, NULL);
        LineTo(surface, EndX, EndY);
      }

      //recurrent link draw in red
      else
      {
        if ((StartX == EndX) && (StartY == EndY))
        {

          int thickness = (int)(fabs(m_vecpNeurons[cNeuron]->vecLinksOut[cLnk].dWeight));

          Clamp(thickness, 0, MaxThickness);
          
          HPEN Pen;

          //blue for inhibitory
          if (m_vecpNeurons[cNeuron]->vecLinksOut[cLnk].dWeight <= 0)
          {
            Pen  = CreatePen(PS_SOLID, thickness, RGB(0,0,255));
          }

          //red for excitory
          else
          {
            Pen  = CreatePen(PS_SOLID, thickness, RGB(255, 0, 0));
          }

          HPEN tempPen = (HPEN)SelectObject(surface, Pen);
          
          //we have a recursive link to the same neuron draw an ellipse
          int x = m_vecpNeurons[cNeuron]->iPosX ; 
          int y = m_vecpNeurons[cNeuron]->iPosY - (1.5 * radNeuron);

          Ellipse(surface, x-radLink, y-radLink, x+radLink, y+radLink);
          
          SelectObject(surface, tempPen);
          
          DeleteObject(Pen);
        }

        else
        {
          int thickness = (int)(fabs(m_vecpNeurons[cNeuron]->vecLinksOut[cLnk].dWeight));

          Clamp(thickness, 0, MaxThickness);

          HPEN Pen;

          //blue for inhibitory
          if (m_vecpNeurons[cNeuron]->vecLinksOut[cLnk].dWeight <= 0)
          {
            Pen  = CreatePen(PS_SOLID, thickness, RGB(0,0,255));
          }

          //red for excitory
          else
          {
            Pen  = CreatePen(PS_SOLID, thickness, RGB(255, 0, 0));
          }
          
        
          HPEN tempPen = (HPEN)SelectObject(surface, Pen);

          //draw the link
          MoveToEx(surface, StartX, StartY, NULL);
          LineTo(surface, EndX, EndY);

          SelectObject(surface, tempPen);
          
          DeleteObject(Pen);
        }
      }

    }
  }

  //now draw the neurons and their IDs
  SelectObject(surface, RedBrush);
  SelectObject(surface, GetStockObject(BLACK_PEN));

  for (cNeuron=0; cNeuron<m_vecpNeurons.size(); ++cNeuron)
  {
    int x = m_vecpNeurons[cNeuron]->iPosX; 
    int y = m_vecpNeurons[cNeuron]->iPosY;

    //display the neuron
    Ellipse(surface, x-radNeuron, y-radNeuron, x+radNeuron, y+radNeuron); 
  }

  //cleanup
  SelectObject(surface, OldPen);
  SelectObject(surface, OldBrush);
  
  DeleteObject(RedPen);
  DeleteObject(GreyPen);
  DeleteObject(GreenPen);
  DeleteObject(OldPen);
  DeleteObject(RedBrush);
  DeleteObject(OldBrush);
}




