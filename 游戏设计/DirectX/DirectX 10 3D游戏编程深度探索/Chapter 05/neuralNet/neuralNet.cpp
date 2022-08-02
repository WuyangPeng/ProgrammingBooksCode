/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/


using namespace std;

#include "stdafx.h"
#include <math.h> // for atof, exp
#include <stdio.h>
#include <stdlib.h> // for atof
#include "NeuralNet.h"

int wmain(int argc, TCHAR* argv[])
{
	// Sorry, I don't do cout.
	wprintf_s( L"Advanced 3D Game Programming with DirectX 10.0\n" );
	wprintf_s( L"----------------------------------------------\n\n" );
	wprintf_s( L"Neural Net Simulator\n\n");

	if( argc != 2 )
	{
		wprintf_s(L"Usage: neuralnet filename.nn\n");
		return 0;
	}

	wprintf_s(L"Using nn description file [%s]\n\n", argv[1] );

	cNeuralNet nn;
	cFile nnFile;
	nnFile.Open( (TCHAR*)argv[1] );
	nn.Load( nnFile );
	nnFile.Close();

	int done = 0;
	while( !done )
	{
		// Clear the totals
		nn.Clear();

		// List the inputs for the net from the user
		nn.ListInputs();

		// Get the inputs for the net from the user
		nn.GetInputs();

		// Run the net
		nn.Run();

		// Get the net's output.
		wstring output = nn.GetOutput();

		wprintf_s(L"\nNeural Net output was [%s]\n", output.c_str() );
		wprintf_s(L"\nRun Again? (y/n)\n");
		TCHAR buff[80];
		_getws_s( buff, 80 );

		if( !(buff[0] == 'y' || buff[0] == 'Y') )
		{
			done = 1;
		}
	}
	return 0;
}


cNeuralNet::cNeuralNet()
{
	// no work needs to be done.
}

cNeuralNet::~cNeuralNet()
{
	// delete all of the nodes. (each node will get it's outgoing edges)
	int numLayers = m_nodes.size();
	for( int i=0; i<numLayers; i++ )
	{
		int layerSize = m_nodes[i].size();
		for( int j=0; j<layerSize; j++ )
		{
			delete m_nodes[i][j];
		}
	}
}


cNeuralNet::cNode* cNeuralNet::FindNode( const TCHAR *name)
{
	cNode* pCurr;

	// Search for the node.
	int numLayers = m_nodes.size();
	for( int i=0; i<numLayers; i++ )
	{
		int layerSize = m_nodes[i].size();
		for( int j=0; j<layerSize; j++ )
		{
			pCurr = m_nodes[i][j];
			if( 0 == wcscmp( pCurr->GetName(), name ) )
				return pCurr;
		}
	}

	// didn't contain the node (bad)
	wprintf_s( L"ERROR IN NEURAL NET FILE!\n");
	wprintf_s( L"Tried to look for node named [%s]\n", name );
	wprintf_s( L"but couldn't find it!\n");
	exit(0);
	return NULL;
}

void cNeuralNet::Clear()
{
	// Call clear on each of the networks.
	cNode* pCurr;

	int numLayers = m_nodes.size();
	for( int i=0; i<numLayers; i++ )
	{
		int layerSize = m_nodes[i].size();
		for( int j=0; j<layerSize; j++ )
		{
			pCurr = m_nodes[i][j];
			pCurr->Clear();
		}
	}
}

void cNeuralNet::Run()
{
	// Run each layer, running each node in each layer.
	int numLayers = m_nodes.size();
	for( int i=0; i<numLayers; i++ )
	{
		int layerSize = m_nodes[i].size();
		for( int j=0; j<layerSize; j++ )
		{
			m_nodes[i][j]->Run();
		}
	}
}

void cNeuralNet::SendInput( const TCHAR *inputTarget, float amt)
{
	// Find the node that we're sending the input to, and send it.
	FindNode( inputTarget )->SendInput( amt );
}

void cNeuralNet::cNode::Clear()
{
	// initial total is set to the bias
	m_total = m_weight; 
}

void cNeuralNet::cNode::Run()
{
	// Compute the transfer function
	float output = CalcOutput();

	// Send it to each of our children
	int size = m_outEdges.size();
	for( int i=0; i< size; i++ )
	{
		m_outEdges[i].Fire( output );
	}
}


void cNeuralNet::cNode::Init( const TCHAR *name, float weight) 
{
	m_name = wstring( name );
	m_weight = weight;
}

float cNeuralNet::cNode::CalcOutput()
{
	// This can use an exponential-type function
	// but for simplicity's sake we're just doing
	// flat yes/no.
	if( m_total >= 1.0f )
		return 1.0f;
	else
		return 0.f;
}

void cNeuralNet::cNode::SendInput(float in)
{
	// just add the input to the total for the network.
	m_total += in;
}

void cNeuralNet::cNode::AddOutEdge(cNode *target, float edgeWeight)
{
	// Create an edge structure
	m_outEdges.push_back( cEdge( this, target, edgeWeight) );
}


void cNeuralNet::Load(cFile &file)
{
	TCHAR buff[1024];
	TCHAR* pCurr;
	TCHAR delim[] = L" \t\n\r";

	TCHAR* context;

	while( 1 )
	{
		file.ReadNonCommentedLine( buff, '#' );
		pCurr = wcstok_s( buff, delim, &context );
		if( 0 == wcscmp( pCurr, L"NN_BEGIN" ) )
		{
			// Read in the # of layers
			int nLayers = _wtoi( wcstok_s( NULL, delim, &context ) );
			for( int i=0; i<nLayers; i++ )
			{
				// populate the vector-of-vectors with vectors.
				vector< cNeuralNet::cNode* > garbage;
				m_nodes.push_back( garbage );
			}
			
		}
		else if( 0 == wcscmp( pCurr, L"NN_END" ) )
		{
			// We're done loading the network.  break from the loop
			break;
		}
		else if( 0 == wcscmp( pCurr, L"NEURON" ) )
		{
			int layerNum = _wtoi( wcstok_s( NULL, delim, &context ) );
			cNode* pNew = new cNode();
			TCHAR* name;
			name = wcstok_s( NULL, delim, &context );
			pCurr = wcstok_s( NULL, delim, &context );
			float val;
			swscanf_s(pCurr, L"%f", &val );
			pNew->Init( name, val );

			// done initializing.  add it to the list
			m_nodes[layerNum].push_back( pNew );
		}
		else if( 0 == wcscmp( pCurr, L"INPUT" ) )
		{
			wstring nodeName = wstring( wcstok_s( NULL, delim, &context ) );
			
			TCHAR* pRestOfString = wcstok_s( NULL, L"\n\r", &context );

			TCHAR* pStrStart = wcschr( pRestOfString, '\"' );
			TCHAR* pStrEnd = wcsrchr( pRestOfString, '\"' );

			assert( pStrStart && pStrEnd && (pStrStart!=pStrEnd) );

			m_inputs[ nodeName ] = wstring( pStrStart+1, pStrEnd );
		}
		else if( 0 == wcscmp( pCurr, L"OUTPUT" ) )
		{
			wstring nodeName = wstring( wcstok_s( NULL, delim, &context ) );
			
			TCHAR* pRestOfString = wcstok_s( NULL, L"\n\r", &context );

			TCHAR* pStrStart = wcschr( pRestOfString, '\"' );
			TCHAR* pStrEnd = wcsrchr( pRestOfString, '\"' );

			assert( pStrStart && pStrEnd && (pStrStart!=pStrEnd) );

			m_outputs[ nodeName ] = wstring( pStrStart+1, pStrEnd );
		}
		else if( 0 == wcscmp( pCurr, L"DEFAULTOUT" ) )
		{
			TCHAR* pRestOfString = wcstok_s( NULL, L"\n\r", &context );

			TCHAR* pStrStart = wcschr( pRestOfString, '\"' );
			TCHAR* pStrEnd = wcsrchr( pRestOfString, '\"' );

			assert( pStrStart && pStrEnd && (pStrStart!=pStrEnd) );

			m_defaultOutput = wstring( pStrStart+1, pStrEnd );
		}
		else if( 0 == wcscmp( pCurr, L"EDGE" ) )
		{
			TCHAR* src;
			TCHAR* dst;
			src = wcstok_s( NULL, L" \t\n\r", &context );
			dst = wcstok_s( NULL, L" \t\n\r", &context );

			pCurr = wcstok_s( NULL, L" \t\n\r", &context );
			float val;
			swscanf_s(pCurr, L"%f", &val );

			FindNode( src )->AddOutEdge( FindNode( dst ), val );
		}

	}

}

cNeuralNet::cEdge::cEdge( cNode *pSrc, cNode *pDest, float weight)
: m_pSrc( pSrc )
, m_pDest( pDest )
, m_weight( weight)
{
	// all done.
}

void cNeuralNet::cEdge::Fire( float amount )
{
	// Send the signal, multiplied by the weight, 
	// to the destination node.
	m_pDest->SendInput( amount * m_weight );
}

//==========--------------------------  

void cNeuralNet::ListInputs()
{
	wprintf_s(L"\n");
	wprintf_s(L"Neural Net Inputs:\n");
	wprintf_s(L"------------------\n");

	map<wstring, wstring>::iterator iter;
	for( iter = m_inputs.begin(); iter != m_inputs.end(); iter++ )
	{
		wprintf_s(L"%s\n", (*iter).second.c_str() );
	}
}


void cNeuralNet::GetInputs()
{
	wprintf_s(L"\n");
	wprintf_s(L"Enter Inputs:\n");
	wprintf_s(L"-------------\n");

	map<wstring, wstring>::iterator iter;
	for( iter = m_inputs.begin(); iter != m_inputs.end(); iter++ )
	{
		wprintf_s(L"Enter floating point input for [%s]\n", (*iter).second.c_str() );
		TCHAR buff[80];
		_getws_s( buff, 80 );
		float value = (float)_wtof( buff );

		cNode* pNode = FindNode( (*iter).first.c_str() );

		pNode->SendInput( value );
	}
}


wstring cNeuralNet::GetOutput()
{
	map<wstring, wstring>::iterator iter;

	float fBest = 1.f;
	map<wstring, wstring>::iterator best = m_outputs.end();

	for( iter = m_outputs.begin(); iter != m_outputs.end(); iter++ )
	{
		// check the output.  is it the best?
		cNode* pNode = FindNode( (*iter).first.c_str() );
		if( pNode->GetTotal() > fBest )
		{
			// new best.
			fBest = pNode->GetTotal();
			best = iter;
			wprintf_s(L"new total: %f\n", fBest );
		}
	}
	if( best == m_outputs.end() )
	{
		return m_defaultOutput;
	}
	else
	{
		return (*best).second.c_str();
	}
}

