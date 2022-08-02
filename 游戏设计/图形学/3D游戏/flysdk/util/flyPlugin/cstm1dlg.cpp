// cstm1dlg.cpp : implementation file
//

#include "stdafx.h"
#include "flyplugin.h"
#include "chooser.h"
#include "cstm1dlg.h"
#include "cstm2dlg.h"
#include "flypluginaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char str_num_classes[256];
char str_get_class_desc[512];
char *buf_img1=0;
BITMAPINFO bmi;
char classes_names[MAX_CLASSES][64];
int num_classes;

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog


CCustom1Dlg::CCustom1Dlg()
	: CAppWizStepDlg(CCustom1Dlg::IDD)
{
	//{{AFX_DATA_INIT(CCustom1Dlg)
	//}}AFX_DATA_INIT
}


void CCustom1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustom1Dlg)
	DDX_Control(pDX, IDC_CLASSES, m_classes);
	DDX_Control(pDX, IDC_CLASSNAME, m_classname);
	//}}AFX_DATA_MAP
}

// This is called whenever the user presses Next, Back, or Finish with this step
//  present.  Do all validation & data exchange from the dialog in this function.
BOOL CCustom1Dlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;

	char str[512], str2[512], str3[512];
	static char buf1[2048], buf2[2048], buf3[2048], buf4[2048], buf5[4096], buf6[8192];
	buf1[0]=0; buf2[0]=0; buf3[0]=0, buf4[0]=0; buf5[0]=0; buf6[0]=0;

	int i,j=m_classes.GetCount();
	sprintf(str_num_classes,"\treturn %i;\n",j);
	num_classes=j;

	strcpy(buf3,"enum\n{\n");
	
	str_get_class_desc[0]=0;
	for( i=0;i<j;i++ )
	{
		m_classes.GetText(i,str);
		strcpy(classes_names[i],str);
		strcat(buf1,str);
		strcat(buf1,"\n");
		
		sprintf(str2,"%s_desc cd_%s;\n",str, str);
		strcat(buf2,str2);

		sprintf(str2, "\tcase %i:\n", i);
		strcat(str_get_class_desc, str2);
		sprintf(str2, "\t\treturn &cd_%s;\n", str);
		strcat(str_get_class_desc, str2);

		strcpy(str3,str);
		strupr(str3);
		sprintf(str2,"\tTYPE_%s%s\n",str3,(i==0 ? "=100000," : ","));
		strcat(buf3,str2);

		sprintf(str2,"class %s_desc : public class_desc\n{\npublic:\n\tvoid *create() { return new %s; };\n\tchar *get_name() { return \"%s\"; };\n\tint get_type() { return TYPE_%s; };\n};\n",str,str,str,str3);
		strcat(buf4,str2);

		sprintf(str2,"class %s : public bsp_object\n{\npublic:\n\t%s() { type=TYPE_%s; };\n\tint step(int dt);\n\tvoid draw();\n\tint get_custom_param_desc(int i,param_desc *pd);\n\tbsp_object *clone();\n};\n",str,str,str3);
		strcat(buf5,str2);

		sprintf(str2,"void %s::step(int dt)\n{\n\t// TODO: animate dt milliseconds\n}\n\n",str);
		strcat(buf6,str2);
		sprintf(str2,"void %s::draw()\n{\n\t// TODO: draw using opengl\n}\n\n",str);
		strcat(buf6,str2);
		sprintf(str2,"bsp_object *%s::clone()\n{\n\t%s *tmp=new %s;\n\t*tmp=*this;\n\ttmp->source=this;\n\treturn tmp;\n}\n\n",str,str,str);
		strcat(buf6,str2);
		sprintf(str2,"int %s::get_custom_param_desc(int i,param_desc *pd)\n{\n\tif (pd!=0)\n\tswitch(i)\n\t{\n\tcase 0:\n\t\t// TODO: pd->type=PARAM_TYPE;\n\t\t// TODO: pd->data=&PARAM_DATA;\n\t\t// TODO: strcpy(pd->name,\"param_name\");\n\t\tbreak;\n\t}\n\treturn 0; // return number of parameters\n}\n\n",str);
		strcat(buf6,str2);
	}

	strcat(buf3,"};\n");

	Flypluginaw.m_Dictionary["CLASSES"]=buf1;
	Flypluginaw.m_Dictionary["CLASS_DESC"]=buf2;
	Flypluginaw.m_Dictionary["ENUM"]=buf3;
	Flypluginaw.m_Dictionary["CLSSESDESC_H"]=buf4;
	Flypluginaw.m_Dictionary["CLASSES_H"]=buf5;
	Flypluginaw.m_Dictionary["CLASSES_CPP"]=buf6;
	
	int dllnum=1;
	buf1[0]=0;

	sprintf(str,"num_classes\t@%i\n",dllnum++);
	strcat(buf1,str); str[0]=0;
	strcat(str,"__declspec( dllexport )\n");
	strcat(str,"int num_classes()\n");
	strcat(str,"{\n");
	strcat(str,str_num_classes);
	strcat(str,"}\n");
	Flypluginaw.m_Dictionary["NUM_CLASSES"]=str;
	sprintf(str,"get_class_desc\t@%i\n",dllnum++);
	strcat(buf1,str); str[0]=0;
	strcat(str,"__declspec( dllexport )\n");
	strcat(str,"class_desc *get_class_desc(int i)\n");
	strcat(str,"{\n");
	strcat(str,"\tswitch(i)\n");
	strcat(str,"\t{\n");
	strcat(str,str_get_class_desc);
	strcat(str,"\tdefault: return 0;\n");
	strcat(str,"\t}\n");
	strcat(str,"}\n");
	Flypluginaw.m_Dictionary["GET_CLASS_DESC"]=str;
	sprintf(str,"fly_message\t@%i\n",dllnum++);
	strcat(buf1,str); str[0]=0;
	strcat(str,"__declspec( dllexport )\n");
	strcat(str,"int fly_message(int msg,int param,void *data)\n");
	strcat(str,"{\n");
	strcat(str,"\tswitch(msg)\n");
	strcat(str,"\t{\n");
	strcat(str,"\tcase FLYM_UPDATESCENE:\n");
	strcat(str,"\t\t// step plugin (dt in param)\n");
	strcat(str,"\t\tbreak;\n");
	strcat(str,"\tcase FLYM_DRAWSCENE:\n");
	strcat(str,"\t\t// draw 3d plugin\n");
	strcat(str,"\t\tbreak;\n");
	strcat(str,"\tcase FLYM_DRAWTEXT:\n");
	strcat(str,"\t\t// draw 2d plugin\n");
	strcat(str,"\t\tbreak;\n");
	strcat(str,"\tcase FLYM_INITSCENE:\n");
	strcat(str,"\t\t// scene load: init plugin\n");
	strcat(str,"\t\tbreak;\n");
	strcat(str,"\tcase FLYM_CLOSESCENE:\n");
	strcat(str,"\t\t// scene close: free plugin\n");
	strcat(str,"\t\tbreak;\n");
	strcat(str,"\t}\n");
	strcat(str,"\treturn 1;\n");
	strcat(str,"}\n");
	Flypluginaw.m_Dictionary["FLY_MESSAGE"]=str;

	Flypluginaw.m_Dictionary["FUNCTIONS"]=buf1;

	if (((CCustom2Dlg *)Flypluginaw.m_pChooser->m_pDlgs[2])->m_hWnd)
		((CCustom2Dlg *)Flypluginaw.m_pChooser->m_pDlgs[2])->InitDialog();

	return TRUE;	// return FALSE if the dialog shouldn't be dismissed
}


BEGIN_MESSAGE_MAP(CCustom1Dlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustom1Dlg)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_BN_CLICKED(IDC_UP, OnUp)
	ON_BN_CLICKED(IDC_DOWN, OnDown)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg message handlers

void CCustom1Dlg::OnAdd() 
{
	char str[255];
	m_classname.GetWindowText(str,255);
	if (str[0])
	{
		int i=m_classes.InsertString(-1,str);
		m_classes.SetCurSel(i);
		m_classname.SetWindowText("");
	}
	m_classname.SetFocus();
}

void CCustom1Dlg::OnRemove() 
{
	int i=m_classes.GetCurSel();
	if (i!=-1)
		m_classes.DeleteString(i);
}

void CCustom1Dlg::OnUp() 
{
	int i=m_classes.GetCurSel();
	if (i==0)
		return;
	char str[256];
	m_classes.GetText(i,str);
	m_classes.DeleteString(i);
	m_classes.InsertString(i-1,str);
	m_classes.SetCurSel(i-1);
}

void CCustom1Dlg::OnDown() 
{
	int i=m_classes.GetCurSel();
	if (i==m_classes.GetCount()-1)
		return;
	char str[256];
	m_classes.GetText(i,str);
	m_classes.DeleteString(i);
	m_classes.InsertString(i+1,str);
	m_classes.SetCurSel(i+1);
}

void CCustom1Dlg::OnPaint() 
{
	CPaintDC dc(this); 

	RECT rect;
	GetClientRect(&rect);

	CBrush brush(RGB(96,96,96));
	rect.right=180;
	dc.FillRect(&rect,&brush);

	dc.SelectObject(GetStockObject(BLACK_PEN));

	dc.MoveTo(rect.right,0);
	dc.LineTo(rect.right,rect.bottom);

	if (buf_img1==0)
	{
	HRSRC res=FindResource(hInst,"IMG1","TEMPLATE");
	if (res)
		{
		HGLOBAL hg=LoadResource(hInst,res);
		if (hg)
			{
			buf_img1=(char *)LockResource(hg);
			if (buf_img1)
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
	if (buf_img1)
		SetDIBitsToDevice(dc.m_hDC,
			rect.right/2-64,32,128,128,
			0,0,0,128,
			&buf_img1[18],&bmi,DIB_RGB_COLORS);
}

BOOL CCustom1Dlg::OnInitDialog() 
{
	CAppWizStepDlg::OnInitDialog();
	
	static int i=0;
	if (i==0)
	{
	Flypluginaw.m_Dictionary["CLASSES"]="";
	Flypluginaw.m_Dictionary["CLASS_DESC"]="";
	Flypluginaw.m_Dictionary["ENUM"]="";
	Flypluginaw.m_Dictionary["CLSSESDESC_H"]="";
	Flypluginaw.m_Dictionary["CLASSES_H"]="";
	Flypluginaw.m_Dictionary["CLASSES_CPP"]="";

	Flypluginaw.m_Dictionary["NUM_CLASSES"]="";
	Flypluginaw.m_Dictionary["GET_CLASS_DESC"]="";
	Flypluginaw.m_Dictionary["FLY_MESSAGE"]="";
	Flypluginaw.m_Dictionary["FUNCTIONS"]="";

	Flypluginaw.m_Dictionary["FLYSDKPATH"]="\\FlySDK\\";

	i=1;
	}
	return TRUE;
}
