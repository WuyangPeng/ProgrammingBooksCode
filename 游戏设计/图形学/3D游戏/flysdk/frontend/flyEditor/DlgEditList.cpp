// DlgEditList.cpp : implementation file
//

#include "stdafx.h"
#include "flyeditor.h"
#include "DlgEditList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEditList dialog


CDlgEditList::CDlgEditList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEditList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEditList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgEditList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEditList)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEditList, CDialog)
	//{{AFX_MSG_MAP(CDlgEditList)
	ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEditList message handlers

BOOL CDlgEditList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int i=m_list.AddString("<None>");
	m_list.SetItemData(i,0);
	m_list.SetCurSel(i);

	short int i1,i2;
	i1=pd->type&0xffff;
	i2=pd->type>>16;

	if (pd->type=='d' || i1<-255)
	{
		bsp_object *o=flyengine->active_obj0;
		while(o)
		{
			if ((i2 && o->type>=-i1 && o->type<=-i2) ||
				pd->type=='d' || pd->type==-o->type)
			{
				i=m_list.AddString(o->long_name);
				m_list.SetItemData(i,(DWORD)o);
			}
			o=(bsp_object *)o->next_obj;
		}
	}
	else
	if (pd->type=='o' || i1>255)
	{
		bsp_object *o=flyengine->stock_obj0;
		while(o)
		{
			if ((i2 && o->type>=i1 && o->type<=i2) ||
				pd->type=='o' || pd->type==o->type)
			{
				i=m_list.AddString(o->long_name);
				m_list.SetItemData(i,(DWORD)o);
			}
			o=(bsp_object *)o->next_obj;
		}
	}
	SetFocus();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEditList::OnOK() 
{
	int sel=m_list.GetCurSel();
	
	bsp_object *obj=(bsp_object *)m_list.GetItemData(sel);

	*((bsp_object **)pd->data)=obj;
	
	CDialog::OnOK();
}

void CDlgEditList::OnDblclkList1() 
{
	OnOK();
}
