//////////////////////////////////////////////////////////////////////
// FILE: dgl_dlllayer.h
// PURPOSE: include file of implementation of the CLayer class.
//////////////////////////////////////////////////////////////////////
// Part of DemoGL Demo System sourcecode. See version information
//////////////////////////////////////////////////////////////////////
// COPYRIGHTS:
// Copyright (c)1999-2001 Solutions Design. All rights reserved.
// Central DemoGL Website: www.demogl.com.
// 
// Released under the following license: (BSD)
// -------------------------------------------
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met: 
//
// 1) Redistributions of source code must retain the above copyright notice, this list of 
//    conditions and the following disclaimer. 
// 2) Redistributions in binary form must reproduce the above copyright notice, this list of 
//    conditions and the following disclaimer in the documentation and/or other materials 
//    provided with the distribution. 
// 
// THIS SOFTWARE IS PROVIDED BY SOLUTIONS DESIGN ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, 
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SOLUTIONS DESIGN OR CONTRIBUTORS BE LIABLE FOR 
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
// USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
//
// The views and conclusions contained in the software and documentation are those of the authors 
// and should not be interpreted as representing official policies, either expressed or implied, 
// of Solutions Design. 
//
// See also License.txt in the sourcepackage.
//
//////////////////////////////////////////////////////////////////////
// Contributers to the code:
//		- Frans Bouma [FB]
//////////////////////////////////////////////////////////////////////
// VERSION INFORMATION.
//
// v1.3: No changes.
// v1.2: No changes.
// v1.1: Added to the codebase.
//////////////////////////////////////////////////////////////////////

#ifndef _DGL_DLLLAYER_H
#define _DGL_DLLLAYER_H

////////////////////////////////////////////////////////////////////////
//                          
//						CLASS DEFINITIONS
//
////////////////////////////////////////////////////////////////////////
class CLayer
{
	// PUBLIC MEMBERS NOT ALLOWED

	// public method declarations
	public:
							CLayer(void);
		virtual				~CLayer(void);
		char				*GetEffectName(void);
		CEffect				*GetEffectObject(void);
		bool				GetLayerHidden(void);
		long				GetLayerNumber(void);
		CLayer				*GetNext(void);
		CLayer				*GetPrev(void);
		void				SetLayerHidden(bool bYN);
		void				SetNext(CLayer *pNext);
		void				SetPrev(CLayer *pPrev);
		void				StoreEffectObject(CEffect *pEffectObject, char *pszEffectName, long lLayerNumber);

	// Private member decalrations
	private:
		long				m_lLayerNumber;
		CEffect				*m_pEffectObject;
		CLayer				*m_pNext;
		CLayer				*m_pPrev;
		bool				m_bHidden;
		CStdString			m_sEffectName;
};


#endif	// _DGL_DLLLAYER_H