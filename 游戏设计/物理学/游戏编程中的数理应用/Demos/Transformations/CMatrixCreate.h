// CMatrix3Dlg.h - Header file for the CMatrix3Dlg Class
// This Dialog Box is used to take 3x3 Transformation Matrix input from the user
// Note that this Matrix is coverted into a 4x4 TM
//
// ©New Riders, 2003. All rights reserved.
// Created By: Mike Fawcett & Mike Wigand

// PRAGMAS //
#pragma once

// INCLUDES //
#include "stdafx.h"
#include "GraphicsUtil.h"
#include "resource.h"

class CMatrixCreate : public CDialog					// a resource-based modal dialog box
{
public:
	CMatrixCreate();														// default constructor
	enum { IDD = IDD_MATRIX_CREATE };					// set its ID
	
protected:
	void ErrorCheck(int item);										// 
	virtual void DoDataExchange(CDataExchange *pDX);
	virtual void OnOK();
	virtual void OnCancel();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditM00();
	afx_msg void OnEnChangeEditM01();
	afx_msg void OnEnChangeEditM02();
	afx_msg void OnEnChangeEditM10();
	afx_msg void OnEnChangeEditM11();
	afx_msg void OnEnChangeEditM12();
	afx_msg void OnEnChangeEditM20();
	afx_msg void OnEnChangeEditM21();
	afx_msg void OnEnChangeEditM22();
};