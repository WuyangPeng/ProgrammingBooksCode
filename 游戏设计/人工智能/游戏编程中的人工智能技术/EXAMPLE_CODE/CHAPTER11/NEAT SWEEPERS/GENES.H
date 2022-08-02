#ifndef GENES_H
#define GENES_H
//-----------------------------------------------------------------------
//
//  Name: GeneGenes.h
//
//  Author: Mat Buckland 2002
//
//	Desc: neuron and link gene definitions used in the 
//        implementation of Kenneth Owen Stanley's and Risto 
//        Miikkulainen's NEAT idea.These structures are used to define
//        a genome.
//
//-----------------------------------------------------------------------

class CNeuron;

//------------------------------------------------------------------------
//
//  enumeration for all the available neuron types
//------------------------------------------------------------------------
enum neuron_type
{
  input,
  hidden,
  output,
  bias,
  none
};

//------------------------------------------------------------------------
//
//  this structure defines a neuron gene
//------------------------------------------------------------------------
struct SNeuronGene
{  
  //its identification
  int         iID;

  //its type
  neuron_type NeuronType;

  //is it recurrent
  bool        bRecurrent;

  //sets the curvature of the sigmoid function
  double    dActivationResponse;

  //position in network grid
  double    dSplitY, dSplitX;

  SNeuronGene(neuron_type type,
              int         id,
              double      y,
              double      x,
              bool        r = false):iID(id),
                                     NeuronType(type),
                                     bRecurrent(r),
                                     dSplitY(y),
                                     dSplitX(x),
                                     dActivationResponse(1)
  {}
};

//------------------------------------------------------------------------
//
//  this structure defines a link gene
//------------------------------------------------------------------------
struct SLinkGene
{
	//the IDs of the two neurons this link connects		
	int     FromNeuron,
	        ToNeuron;
	
	double	dWeight;

  //flag to indicate if this link is currently enabled or not
  bool    bEnabled;

  //flag to indicate if this link is recurrent or not
  bool    bRecurrent;
	
	int     InnovationID;

  SLinkGene(){}
  
  SLinkGene(int    in,
            int    out,
            bool   enable,
            int    tag,
            double w,
            bool   rec = false):bEnabled(enable),
								                InnovationID(tag),
                                FromNeuron(in),
                                ToNeuron(out),
                                dWeight(w),
                                bRecurrent(rec)
	{}

  //overload '<' used for sorting(we use the innovation ID as the criteria)
	friend bool operator<(const SLinkGene& lhs, const SLinkGene& rhs)
	{
		return (lhs.InnovationID < rhs.InnovationID);
	}
};


                                         
#endif 