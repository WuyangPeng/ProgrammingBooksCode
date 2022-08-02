// CMatrixCreate.cpp - Source file for the CMatrixCreate Class
//
// ©New Riders, 2003. All rights reserved.
// Created By: Mike Fawcett & Mike Wigand
// INCLUDES //
#include "stdafx.h"
#include <algorithm>
#include "CMatrixCreate.h"
#include "EntityManager.h"

// PRAGMAS //
//#pragma warning (disable : 4244)

// CMatrixCreate - Default Constructor
CMatrixCreate::CMatrixCreate() : CDialog(CMatrixCreate::IDD)
{

}


void CMatrixCreate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

void CMatrixCreate::OnOK()
{
	char buffer[20];																		// temporary storage for data entered
	char *stopstring;

	Matrix4* mat = new Matrix4;

	GetDlgItemText(IDC_EDIT_M00, buffer, 20);
	mat->mat[0] = strtod(buffer, &stopstring);
	GetDlgItemText(IDC_EDIT_M01, buffer, 20);
	mat->mat[4] = strtod(buffer, &stopstring);
	mat->mat[8] = 0.0;
	GetDlgItemText(IDC_EDIT_M02, buffer, 20);
	mat->mat[12] = strtod(buffer, &stopstring);

	GetDlgItemText(IDC_EDIT_M10, buffer, 20);
	mat->mat[1] = strtod(buffer, &stopstring);
	GetDlgItemText(IDC_EDIT_M11, buffer, 20);
	mat->mat[5] = strtod(buffer, &stopstring);
	mat->mat[9] = 0.0;
	GetDlgItemText(IDC_EDIT_M12, buffer, 20);
	mat->mat[13] = strtod(buffer, &stopstring);

	mat->mat[2] = 0.0;
	mat->mat[6] = 0.0;
	mat->mat[10] = 1.0;
	mat->mat[14] = 0.0;

	GetDlgItemText(IDC_EDIT_M20, buffer, 20);
	mat->mat[3] = strtod(buffer, &stopstring);
	GetDlgItemText(IDC_EDIT_M21, buffer, 20);
	mat->mat[7] = strtod(buffer, &stopstring);
	mat->mat[11] = 0.0;	
	GetDlgItemText(IDC_EDIT_M22, buffer, 20);
	mat->mat[15] = strtod(buffer, &stopstring);

	EntityManager* EMan = EntityManager::getInstance();
	EMan->selected->transMats.push_back(mat);
	
	// Close the dialog.
	CDialog::OnOK();
}

void CMatrixCreate::OnCancel()
{

	CDialog::OnCancel();
}

BEGIN_MESSAGE_MAP(CMatrixCreate, CDialog)
	ON_EN_CHANGE(IDC_EDIT_M00, OnEnChangeEditM00)
	ON_EN_CHANGE(IDC_EDIT_M01, OnEnChangeEditM01)
	ON_EN_CHANGE(IDC_EDIT_M02, OnEnChangeEditM02)
	ON_EN_CHANGE(IDC_EDIT_M10, OnEnChangeEditM10)
	ON_EN_CHANGE(IDC_EDIT_M11, OnEnChangeEditM11)
	ON_EN_CHANGE(IDC_EDIT_M12, OnEnChangeEditM12)
	ON_EN_CHANGE(IDC_EDIT_M20, OnEnChangeEditM20)
	ON_EN_CHANGE(IDC_EDIT_M21, OnEnChangeEditM21)
	ON_EN_CHANGE(IDC_EDIT_M22, OnEnChangeEditM22)
END_MESSAGE_MAP()

void CMatrixCreate::OnEnChangeEditM00()
{
	ErrorCheck(IDC_EDIT_M00);
}
void CMatrixCreate::OnEnChangeEditM01()
{
	ErrorCheck(IDC_EDIT_M01);
}
void CMatrixCreate::OnEnChangeEditM02()
{
	ErrorCheck(IDC_EDIT_M02);
}
void CMatrixCreate::OnEnChangeEditM10()
{
	ErrorCheck(IDC_EDIT_M10);
}
void CMatrixCreate::OnEnChangeEditM11()
{
	ErrorCheck(IDC_EDIT_M11);
}
void CMatrixCreate::OnEnChangeEditM12()
{
	ErrorCheck(IDC_EDIT_M12);
}
void CMatrixCreate::OnEnChangeEditM20()
{
	ErrorCheck(IDC_EDIT_M20);
}
void CMatrixCreate::OnEnChangeEditM21()
{
	ErrorCheck(IDC_EDIT_M21);
}
void CMatrixCreate::OnEnChangeEditM22()
{
	ErrorCheck(IDC_EDIT_M22);
}

void CMatrixCreate::ErrorCheck(int item)
{
	// Encapuslate all this into an error checking routine.
	char buffer[20];
	std::string buf;

	GetDlgItemText(item, buffer, 20);
	buf.assign(buffer);

	if (buf.size() == 0)
		return;

	// Make sure the character they just entered is valid.
	//
	// If there are more than one decimal points, remove the last one.
	int numDecs = (int)std::count(buf.begin(), buf.end(), '.');
	if (numDecs > 1)
	{
		std::string::iterator iter = &buf[buf.find_last_of(".")];
		buf.erase(iter, iter + 1);

		// Figure out how to set cursor pos to end of string.
		SetDlgItemText(item, buf.c_str());		
		return;
	}

	// Remove all non numeric characters.
	std::string::iterator newEnd = std::remove_if(buf.begin(), buf.end(), isalpha);
	if (newEnd != buf.end())
	{
		buf.erase(newEnd, buf.end());
		// Figure out how to set cursor pos to end of string.
		SetDlgItemText(item, buf.c_str());
	}
};