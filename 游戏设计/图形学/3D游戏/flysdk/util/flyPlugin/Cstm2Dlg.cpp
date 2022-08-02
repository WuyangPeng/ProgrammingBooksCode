// cstm2dlg.cpp : implementation file
//

#include "stdafx.h"
#include "flyplugin.h"
#include "chooser.h"
#include "cstm2dlg.h"
#include "flypluginaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *buf_img2=0;
extern BITMAPINFO bmi;
extern char classes_names[MAX_CLASSES][64];
extern int num_classes;

struct param_desc
{
	char name[64];
	int type;
} param[MAX_CLASSES][MAX_PARAM];
int nparam[MAX_CLASSES];

/////////////////////////////////////////////////////////////////////////////
// CCustom2Dlg dialog


CCustom2Dlg::CCustom2Dlg()
	: CAppWizStepDlg(CCustom2Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom2Dlg)
	//}}AFX_DATA_INIT
}


void CCustom2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom2Dlg)
	DDX_Control(pDX, IDC_PARAMETERS, m_param);
	DDX_Control(pDX, IDC_PARAM_NAME, m_paramname);
	DDX_Control(pDX, IDC_PARAM_TYPE, m_paramtype);
	DDX_Control(pDX, IDC_CLASSES, m_classes);
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom2Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;

	char buf[8192],buf2[4096],str[512],str2[512];
	buf[0]=0; buf2[0]=0;
	int i,j;
	for( i=0;i<num_classes;i++ )
	{
	sprintf(str,"int %s::step(int dt)\n{\n\t// TODO: animate dt milliseconds\n\treturn 0;\n}\n\n",classes_names[i]);
	strcat(buf,str);
	sprintf(str,"void %s::draw()\n{\n\t// TODO: draw using opengl\n}\n\n",classes_names[i]);
	strcat(buf,str);
	sprintf(str,"bsp_object *%s::clone()\n{\n\t%s *tmp=new %s;\n\t*tmp=*this;\n\ttmp->source=this;\n\treturn tmp;\n}\n\n",classes_names[i],classes_names[i],classes_names[i]);
	strcat(buf,str);
	sprintf(str,"int %s::get_custom_param_desc(int i,param_desc *pd)\n{\n\tif (pd!=0)\n\tswitch(i)\n\t{\n",classes_names[i]);
	strcat(buf,str);
	for( j=0;j<nparam[i];j++ )
		{
		sprintf(str,"\tcase %i:\n\t\tpd->type='%c';\n\t\tpd->data=&%s;\n\t\tstrcpy(pd->name,\"%s\");\n\t\tbreak;\n",j,param[i][j].type,param[i][j].name,param[i][j].name);
		strcat(buf,str);
		}
	sprintf(str,"\t}\n\treturn %i;\n}\n\n",nparam[i]);
	strcat(buf,str);

	strcpy(str2,classes_names[i]);
	strupr(str2);
	sprintf(str,"class %s : public bsp_object\n{\npublic:\n\t%s() { type=TYPE_%s; };\n\n",classes_names[i],classes_names[i],str2);
	strcat(buf2,str);
	for( j=0;j<nparam[i];j++ )
		{
		sprintf(str,"\t%s %s;\n",GetParamClass(param[i][j].type),param[i][j].name);
		strcat(buf2,str);
		}
	sprintf(str,"\n\tint step(int dt);\n\tvoid draw();\n\tint get_custom_param_desc(int i,param_desc *pd);\n\tbsp_object *clone();\n};\n");
	strcat(buf2,str);
	}
	
	Flypluginaw.m_Dictionary["CLASSES_CPP"]=buf;
	Flypluginaw.m_Dictionary["CLASSES_H"]=buf2;

	return TRUE;
}

BEGIN_MESSAGE_MAP(CCustom2Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom2Dlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_PARAM_DELETE, OnParamDelete)
	ON_BN_CLICKED(IDC_PARAM_NEW, OnParamNew)
	ON_BN_CLICKED(IDC_PARAM_DOWN, OnParamDown)
	ON_BN_CLICKED(IDC_PARAM_UP, OnParamUp)
	ON_CBN_SELCHANGE(IDC_CLASSES, OnSelchangeClasses)
	ON_LBN_SELCHANGE(IDC_PARAMETERS, OnSelchangeParameters)
	ON_EN_CHANGE(IDC_PARAM_NAME, OnChangeParamName)
	ON_CBN_SELCHANGE(IDC_PARAM_TYPE, OnSelchangeParamType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom2Dlg message handlers

void CCustom2Dlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	RECT rect;
	GetClientRect(&rect);

	CBrush brush(RGB(96,96,96));
	rect.right=180;
	dc.FillRect(&rect,&brush);

	dc.SelectObject(GetStockObject(BLACK_PEN));

	dc.MoveTo(rect.right,0);
	dc.LineTo(rect.right,rect.bottom);

	if (buf_img2==0)
	{
	HRSRC res=FindResource(hInst,"IMG2","TEMPLATE");
	if (res)
		{
		HGLOBAL hg=LoadResource(hInst,res);
		if (hg)
			{
			buf_img2=(char *)LockResource(hg);
			if (buf_img2)
				{
				bmi.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
				bmi.bmiHeader.biWidth=128;
				bmi.bmiHeader.biHeight=128;
				bmi.bmiHeader.biPlanes=1;
				bmi.bmiHeader.biBitCount=24;
				bmi.bmiHeader.biCompression=BI_RGB;
				bmi.bmiHeader.biSizeImage=0;
				bmi.bmiHeader.biXPelsPerMeter=3600;
				bmi.bmiHeader.biYPelsPerMeter=3600; 
				bmi.bmiHeader.biClrUsed=0;     
				bmi.bmiHeader.biClrImportant=0; 
				}
			}
		}
	}
	if (buf_img2)
		SetDIBitsToDevice(dc.m_hDC,
			rect.right/2-64,32,128,128,
			0,0,0,128,
			&buf_img2[18],&bmi,DIB_RGB_COLORS);
}

char *CCustom2Dlg::GetParamType(int type) 
{
	if (type>255 || type<-255)
		return "plugin";
	switch( type )
	{
	case 'a': return "angle";
	case 'i': return "int";
	case 'f': return "float";
	case 'v': return "vector";
	case 'c': return "color";
	case '3': return "3ds file";
	case 'm': return "fao file";
	case 'b': return "bezier curve";
	case 'h': return "bezier patch";
	case 'w': return "wav file";
	case 'p': return "picture file";
	case 'o': return "stock object";
	case 'd': return "active object";
	}
	return "nothing";
}

char *CCustom2Dlg::GetParamClass(int type) 
{
	if (type>255 || type<-255)
		return "bsp_object *";
	switch( type )
	{
	case 'a': return "float";
	case 'i': return "int";
	case 'f': return "float";
	case 'v': return "vector";
	case 'c': return "vector";
	case '3': return "mesh*";
	case 'm': return "anim_mesh*";
	case 'b': return "bezier_curve*";
	case 'h': return "bezier_patch*";
	case 'w': return "sound*";
	case 'p': return "int";
	case 'o': return "bsp_object*";
	case 'd': return "bsp_object*";
	}
	return "nothing";
}

void CCustom2Dlg::OnParamDelete() 
{
	int i=m_classes.GetCurSel();
	int j=m_param.GetCurSel();
	if (i==-1 || j==-1) return;
	memcpy(&param[i][j],&param[i][j+1],sizeof(param[0][0])*(nparam[i]-j-1));
	m_param.DeleteString(j);
	nparam[i]--;
	if (nparam[i])
		if (j<nparam[i])
			m_param.SetCurSel(j);
		else m_param.SetCurSel(j-1);
	OnSelchangeParameters();
}

void CCustom2Dlg::OnParamNew() 
{
	int i=m_classes.GetCurSel();
	if (i==-1) return;
	int j=nparam[i];
	char str[256];
	nparam[i]++;
	sprintf(str,"parameter%i",j);
	strcpy(param[i][j].name,str);
	param[i][j].type='i';
	sprintf(str,"%s\t%s",param[i][j].name,GetParamType(param[i][j].type));
	i=m_param.AddString(str);
	m_param.SetCurSel(i);
	OnSelchangeParameters();
}

void CCustom2Dlg::OnParamDown() 
{
	int i=m_classes.GetCurSel();
	int j=m_param.GetCurSel();
	if (i==-1 || j==-1) return;
	if (j<m_param.GetCount()-1)
	{
		char str[256];
		m_param.GetText(j,str);
		m_param.DeleteString(j);
		m_param.InsertString(j+1,str);
		struct param_desc pd;
		pd=param[i][j];
		param[i][j]=param[i][j+1];
		param[i][j+1]=pd;
		m_param.SetCurSel(j+1);
		OnSelchangeParameters();
	}
}

void CCustom2Dlg::OnParamUp() 
{
	int i=m_classes.GetCurSel();
	int j=m_param.GetCurSel();
	if (i==-1 || j==-1) return;
	if (j>0)
	{
		char str[256];
		m_param.GetText(j,str);
		m_param.DeleteString(j);
		m_param.InsertString(j-1,str);
		struct param_desc pd;
		pd=param[i][j];
		param[i][j]=param[i][j-1];
		param[i][j-1]=pd;
		m_param.SetCurSel(j-1);
		OnSelchangeParameters();
	}
}

void CCustom2Dlg::OnSelchangeClasses() 
{
	m_param.ResetContent();
	int i=m_classes.GetCurSel();
	if (i==-1) return;
	char str[16];
	int j;
	for( j=0;j<nparam[i];j++ )
	{
		sprintf(str,"%s\t%s",param[i][j].name,GetParamType(param[i][j].type));
		m_param.AddString(str);
	}
	if (m_param.GetCount()>0)
		m_param.SetCurSel(0);
	OnSelchangeParameters();
}

void CCustom2Dlg::OnSelchangeParameters() 
{
	int i=m_classes.GetCurSel();
	int j=m_param.GetCurSel();
	if (i==-1 || j==-1)
	{
		GetDlgItem(IDC_STATIC_NAME)->EnableWindow(0);
		GetDlgItem(IDC_STATIC_TYPE)->EnableWindow(0);
		GetDlgItem(IDC_PARAM_NAME)->EnableWindow(0);
		GetDlgItem(IDC_PARAM_TYPE)->EnableWindow(0);
		m_paramtype.SetCurSel(-1);
		m_paramname.SetWindowText("");
	}
	else
	{
		GetDlgItem(IDC_STATIC_NAME)->EnableWindow(1);
		GetDlgItem(IDC_STATIC_TYPE)->EnableWindow(1);
		GetDlgItem(IDC_PARAM_NAME)->EnableWindow(1);
		GetDlgItem(IDC_PARAM_TYPE)->EnableWindow(1);
		m_paramtype.SelectString(-1,GetParamType(param[i][j].type));
		m_paramname.SetWindowText(param[i][j].name);
	}
}

void CCustom2Dlg::OnChangeParamName() 
{
	int i=m_classes.GetCurSel();
	int j=m_param.GetCurSel();
	if (i==-1 || j==-1) return;
	m_paramname.GetWindowText(param[i][j].name,64);
	char str[256];
	sprintf(str,"%s\t%s",param[i][j].name,GetParamType(param[i][j].type));
	m_param.DeleteString(j);
	m_param.InsertString(j,str);
	m_param.SetCurSel(j);
}

void CCustom2Dlg::OnSelchangeParamType() 
{
	int i=m_classes.GetCurSel();
	int j=m_param.GetCurSel();
	if (i==-1 || j==-1) return;
	param[i][j].type=m_paramtype.GetItemData(m_paramtype.GetCurSel());
	char str[256];
	sprintf(str,"%s\t%s",param[i][j].name,GetParamType(param[i][j].type));
	m_param.DeleteString(j);
	m_param.InsertString(j,str);
	m_param.SetCurSel(j);
}

void CCustom2Dlg::InitDialog()
{
	m_classes.ResetContent();
	m_paramtype.ResetContent();
	m_param.SetTabStops(64);

	memset(nparam,0,sizeof(int)*MAX_CLASSES);
	
	int i;
	for( i=0;i<num_classes;i++ )
		m_classes.AddString(classes_names[i]);

	i=m_paramtype.AddString(GetParamType('i'));
	m_paramtype.SetItemData(i,'i');
	i=m_paramtype.AddString(GetParamType('f'));
	m_paramtype.SetItemData(i,'f');
	i=m_paramtype.AddString(GetParamType('c'));
	m_paramtype.SetItemData(i,'c');
	i=m_paramtype.AddString(GetParamType('v'));
	m_paramtype.SetItemData(i,'v');
	i=m_paramtype.AddString(GetParamType('3'));
	m_paramtype.SetItemData(i,'3');
	i=m_paramtype.AddString(GetParamType('m'));
	m_paramtype.SetItemData(i,'m');
	i=m_paramtype.AddString(GetParamType('b'));
	m_paramtype.SetItemData(i,'b');
	i=m_paramtype.AddString(GetParamType('w'));
	m_paramtype.SetItemData(i,'w');
	i=m_paramtype.AddString(GetParamType('p'));
	m_paramtype.SetItemData(i,'p');
	i=m_paramtype.AddString(GetParamType('o'));
	m_paramtype.SetItemData(i,'o');
	i=m_paramtype.AddString(GetParamType('d'));
	m_paramtype.SetItemData(i,'d');

	m_param.ResetContent();

	if (m_classes.GetCount()>0)
	{
		m_classes.SetCurSel(0);
		OnSelchangeClasses();
	}
	else OnSelchangeParameters();
}

BOOL CCustom2Dlg::OnInitDialog() 
{
	CAppWizStepDlg::OnInitDialog();
	
	InitDialog();

	return TRUE;
}
