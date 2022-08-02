// DlgEditValue.cpp : implementation file
//

#include "stdafx.h"
#include "flyeditor.h"
#include "DlgEditValue.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEditValue dialog


CDlgEditValue::CDlgEditValue(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditValue::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEditValue)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgEditValue::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEditValue)
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEditValue, CDialog)
	//{{AFX_MSG_MAP(CDlgEditValue)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEditValue message handlers

void CDlgEditValue::OnKillfocusEdit1() 
{
	m_edit.GetWindowText(value,255);	
}

BOOL CDlgEditValue::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_edit.SetWindowText(value);
	
	char str[256]="Edit Value";
	switch(pd->type)
	{
	case 'v':
		strcat(str," (vector)");
		break;
	case 'f':
		strcat(str," (float)");
		break;
	case 'a':
		strcat(str," (angle)");
		break;
	case 'i':
		strcat(str," (int)");
		break;
	case 's':
		strcat(str," (string)");
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEditValue::OnOK() 
{
	char buf[256];
	m_edit.GetWindowText(buf,255);
	switch(pd->type)
	{
	case 'v':
		sscanf(buf,"%f %f %f",&((float *)pd->data)[0],&((float *)pd->data)[1],&((float *)pd->data)[2]);
		break;
	case 'f':
		sscanf(buf,"%f",(float *)pd->data);
		break;
	case 'a':
		sscanf(buf,"%f",(float *)pd->data);
		*((float *)pd->data)=(float)cos(*((float *)pd->data)*PiOver180);
		break;
	case 'i':
		sscanf(buf,"%i",(int *)pd->data);
		break;
	case 's':
		strcpy((char *)pd->data,buf);
		break;
	}
	CDialog::OnOK();
}
