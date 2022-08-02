/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/


// cNetError.h: interface for the cNetError class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNETERROR_H__B0419ACA_D198_11D3_AE4F_00E029031C67__INCLUDED_)
#define AFX_CNETERROR_H__B0419ACA_D198_11D3_AE4F_00E029031C67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class cNetError  
{
protected:
	TCHAR d_text[1000];

public:
	cNetError( const TCHAR* pText );
	cNetError();
	virtual ~cNetError();


  const TCHAR *Text()
  {
    return (const TCHAR*)d_text;
  }
};

#endif // !defined(AFX_CERROR_H__B0419ACA_D198_11D3_AE4F_00E029031C67__INCLUDED_)
