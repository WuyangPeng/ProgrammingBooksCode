/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _MOUSE_H
#define _MOUSE_H

#include <dinput.h>

/**
 * Any object that implements this interface can receive input
 * from the mouse.
 */
struct iMouseReceiver
{
	virtual void MouseMoved( int dx, int dy ){};
	virtual void MouseButtonUp( int button ){};
	virtual void MouseButtonDown( int button ){};
};


class cMouse  
{
	LPDIRECTINPUTDEVICE8	m_pDevice; 

	DIMOUSESTATE			m_lastState;

	iMouseReceiver*			m_pTarget;

public:

	cMouse( HWND hWnd, bool bExclusive );
	~cMouse();

	/**
	 * Use this to establish a MouseReceiver as the current 
	 * input focus
	 */
	void SetReceiver( iMouseReceiver* pTarget );

	eResult Update();

	eResult Acquire();
	void UnAcquire();
};

#endif // _MOUSE_H
