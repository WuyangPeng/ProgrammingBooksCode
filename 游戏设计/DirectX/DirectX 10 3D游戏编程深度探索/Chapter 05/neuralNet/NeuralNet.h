/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _NEURALNET_H
#define _NEURALNET_H

#include <string>
#include <vector>
#include <map>

using namespace std;

#include "file.h"

class cNeuralNet  
{
protected:
	class cNode;
	class cEdge;

public:
	wstring GetOutput();

	void SendInput( const TCHAR* inputName, float amt );
	
	void Load( cFile& file );
	void Run();
	void Clear();
	cNeuralNet();
	virtual ~cNeuralNet();

	void ListInputs();
	void GetInputs();

protected:


	cNode* FindNode( const TCHAR* name );

	class cNode
	{
	public:
		void Init( const TCHAR* name, float weight );

		void Clear();
		virtual void Run();

		void AddOutEdge( cNode* target, float edgeWeight );
		void SendInput( float in );

		const TCHAR* GetName() const;
		float GetTotal() const;
	protected:

		// Computes the output function given the total.
		virtual float CalcOutput();
		
		wstring	m_name;
		float	m_weight; // initial bias in either direction
		float	m_total;  // total of the summed inputs up to this point

		vector< cEdge >	m_outEdges;

	};

	class cEdge
	{
		cNode*	m_pSrc;
		cNode*	m_pDest;
		float	m_weight;
	public:

		cEdge( cNode* pSrc, cNode* pDst, float weight );

		void Fire( float amount );
	};
	friend class cNode;

	vector< vector< cNode* > > m_nodes;

	// maps the names of output nodes to output strings.
	map< wstring, wstring > m_inputs;
	map< wstring, wstring > m_outputs;

	wstring m_defaultOutput;
};


inline const TCHAR* cNeuralNet::cNode::GetName() const
{
	return m_name.c_str();
}

inline float cNeuralNet::cNode::GetTotal() const
{
	return m_total;
}


#endif // _NEURALNET_H
