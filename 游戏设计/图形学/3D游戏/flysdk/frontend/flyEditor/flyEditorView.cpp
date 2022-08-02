// flyEditorView.cpp : implementation of the CFlyEditorView class
//

#include "stdafx.h"
#include "flyEditor.h"
#include "flyEditorDoc.h"
#include "flyEditorView.h"
#include "flyRenderView.h"
#include "LeftView.h"
#include "DlgEditValue.h"
#include "DlgEditList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFlyRenderView *rv;
CFlyEditorView *lv=0;
extern CLeftView *tv;
extern int active_mode;
extern bsp_object *active_sel;

/////////////////////////////////////////////////////////////////////////////
// CFlyEditorView

IMPLEMENT_DYNCREATE(CFlyEditorView, CListView)

BEGIN_MESSAGE_MAP(CFlyEditorView, CListView)
	//{{AFX_MSG_MAP(CFlyEditorView)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(LVN_KEYDOWN, OnKeydown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlyEditorView construction/destruction

CFlyEditorView::CFlyEditorView()
{
	lv=this;
	colsizes[0]=80;
	colsizes[1]=80;
	colsizes[2]=80;
	ncol=0;
}

CFlyEditorView::~CFlyEditorView()
{
	lv=0;
}

BOOL CFlyEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFlyEditorView drawing

void CFlyEditorView::OnDraw(CDC* pDC)
{
}

void CFlyEditorView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CFlyEditorView diagnostics

#ifdef _DEBUG
void CFlyEditorView::AssertValid() const
{
	CListView::AssertValid();
}

void CFlyEditorView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CFlyEditorDoc* CFlyEditorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFlyEditorDoc)));
	return (CFlyEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFlyEditorView message handlers
void CFlyEditorView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
}

void CFlyEditorView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	*pResult = 0;

	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD type=tree.GetItemData(item);
	if (type==TREE_TYPE_TEXTURES ||
		type==TREE_TYPE_LIGHTMAPS ||
		type==TREE_TYPE_OBJECTS)
		rv->Invalidate(1);
}

void CFlyEditorView::reset_param_list()
{
	nparam=0;
	CListCtrl& list=GetListCtrl();
	list.InsertColumn( 0, "Param", LVCFMT_LEFT, colsizes[0],0 );
	list.InsertColumn( 1, "Value", LVCFMT_LEFT, colsizes[1],0 );
	ncol=2;
	list.DeleteAllItems();
}

void CFlyEditorView::insert_param(char *name, int type, void *data)
{
	CListCtrl& list=GetListCtrl();
	strcpy(pd[nparam].name,name);
	pd[nparam].type=type; 
	pd[nparam].data=data;
	nparam++;
}

char *CFlyEditorView::get_param_formated(int i)
{
	static char str[256];
	str[0]=0;
	if (pd[i].type>255 || pd[i].type<-255)
		{
		if (*((bsp_object **)pd[i].data)!=0)
			strcpy(str,(*((bsp_object **)pd[i].data))->long_name);
		}
	else
	switch(pd[i].type)
	{
	case ' ':
		break;
	case 'f':
		sprintf(str,"%.5f",*((float *)pd[i].data));
		break;
	case 'a':
		sprintf(str,"%.5f",acos(*((float *)pd[i].data))*PiUnder180);
		break;
	case 'i':
		sprintf(str,"%i",*((int *)pd[i].data));
		break;
	case 'c':
	case 'v':
		sprintf(str,"%.4f %.4f %.4f",((float *)pd[i].data)[0],((float *)pd[i].data)[1],((float *)pd[i].data)[2]);
		break;
	case 'p':
		if (*((int *)pd[i].data)!=-1)
			sprintf(str,"%s",flyengine->piclib[*((int *)pd[i].data)]->name);
		break;
	case 'b':
	case 's':
		strcpy(str,(char *)pd[i].data);
		break;
	case '3':
		if (*((mesh **)pd[i].data)!=0)
			strcpy(str,(*((mesh **)pd[i].data))->name);
		break;
	case 'm':
		if (*((mesh **)pd[i].data)!=0)
			strcpy(str,(*((mesh **)pd[i].data))->name);
		break;
	case 'z':
		if (*((bezier_curve **)pd[i].data)!=0)
			strcpy(str,(*((bezier_curve **)pd[i].data))->name);
		break;
	case 'h':
		if (*((bezier_patch **)pd[i].data)!=0)
			strcpy(str,(*((bezier_patch **)pd[i].data))->name);
		break;
	case 'w':
		if (*((sound **)pd[i].data)!=0)
			strcpy(str,(*((sound **)pd[i].data))->name);
		break;
	case 'o':
		if (*((bsp_object **)pd[i].data)!=0)
			strcpy(str,(*((bsp_object **)pd[i].data))->long_name);
		break;
	case 'd':
		if (*((bsp_object **)pd[i].data)!=0)
			strcpy(str,(*((bsp_object **)pd[i].data))->long_name);
		break;
	}
	return str;
}

void CFlyEditorView::fill_param_list()
{
	CListCtrl& list=GetListCtrl();
	int i;
	for( i=0;i<nparam;i++ )
		{
		list.InsertItem(i,pd[i].name);
		char *buf=get_param_formated(i);
		list.SetItem(i,1,LVIF_TEXT,buf,0,0,0,0);
		}
}

void CFlyEditorView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (pResult)
		*pResult = 0;

	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD type=tree.GetItemData(item);
	if (type==TREE_TYPE_TEXTURES ||
		type==TREE_TYPE_LIGHTMAPS ||
		type==TREE_TYPE_OBJECTS)
		return;
	
	CListCtrl& list=GetListCtrl();
	POSITION pos=list.GetFirstSelectedItemPosition();
	if (pos==0)	return;
	int i=list.GetNextSelectedItem(pos);

	if (type==TREE_TYPE_SOUNDS)
		{
		CString str=list.GetItemText(i,0);
		sound *s=flyengine->get_sound_object((char *)(LPCSTR)str);
		if (s && s->buf[0])
			s->buf[0]->Play(0,0,0);
		return;
		}

	if (GetAsyncKeyState(VK_SHIFT)&(1<<16))
	{
		if (pd[i].type=='o' || pd[i].type>255)
			tv->SelectObject(tree.GetRootItem(),*((bsp_object **)pd[i].data));
		else if (pd[i].type=='d' || pd[i].type<255)
			tv->SelectObject(tree.GetRootItem(),(*((bsp_object **)pd[i].data))->source);
	}
	else
		{
		edit_param(i);
		char *buf=get_param_formated(i);
		list.SetItem(i,1,LVIF_TEXT,buf,0,0,0,0);
		}
}

void CFlyEditorView::update_instances(int i)
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD type=tree.GetItemData(item);
	
	if (type==TREE_TYPE_GLOBAL)
	{
		bsp_object *obj;
		obj=flyengine->stock_obj0;
		while(obj)
		{
			obj->message(vector(0,0,0),0,FLYOBJM_CHANGEPARAM,0,0);
			obj=(bsp_object *)obj->next_obj;
		}
		obj=flyengine->active_obj0;
		while(obj)
		{
			obj->message(vector(0,0,0),0,FLYOBJM_CHANGEPARAM,0,0);
			obj=(bsp_object *)obj->next_obj;
		}
	}
	else
	if (type>255)
	{
		bsp_object *o=(bsp_object *)type;
		o->message(vector(0,0,0),0,FLYOBJM_CHANGEPARAM,0,0);
		bsp_object *obj=flyengine->active_obj0;
		while(obj)
		{
			if (obj->source==o)
				{
				char *c;
				int len=4;

				c=((char *)pd[i].data)-((char *)o)+((char *)obj);
				if (pd[i].type=='v' || pd[i].type=='c')
					len=12;
				else if (pd[i].type=='s')
					len=strlen((char *)pd[i].data)+1;

				memcpy(c,pd[i].data,len);
				obj->message(vector(0,0,0),0,FLYOBJM_CHANGEPARAM,0,0);
				}

			obj=(bsp_object *)obj->next_obj;
		}
	}
}

void CFlyEditorView::edit_param(int i)
{
	int flag=0;
	if (pd[i].type>255 || pd[i].type<-255)
		{
		edit_list(i);
		flag=1;
		}
	else
	switch(pd[i].type)
	{
	case ' ': 
		break;
	case 'p':
		{
		char file[256];
		strcpy(file,flyengine->flydatapath);
		strcat(file,"maps\\");
		if (*((int *)pd[i].data)==-1)
			strcat(file,"*.jpg;*.tga");
		else
			strcat(file,flyengine->piclib[*((int *)pd[i].data)]->name);
		char *c=edit_files("","All image files (*.jpg;*.tga)|*.jpg;*.tga|TGA image files (*.tga)|*.tga|JPG image files (*.jpg)|*.jpg||",file);
		if (c)
			{
			int np=flyengine->npiclib,p;
			p=flyengine->get_picture(c);
			*((int *)pd[i].data)=p;
			if (p==np)
				{
				flyengine->close_texture_cache();
				flyengine->init_texture_cache();
				}
			flag=1;
			}
		}
		break;
	case 'w':
		{
		char file[256];
		strcpy(file,flyengine->flydatapath);
		strcat(file,"sounds\\");
		if (*((sound **)pd[i].data)==0)
			strcat(file,"*.wav");
		else strcat(file,(*((sound **)pd[i].data))->name);
		char *c=edit_files("wav","Wave sound files (*.wav)|*.wav||",file);
		if (c)
			{
			*((sound **)pd[i].data)=flyengine->get_sound_object(c);
			flag=1;
			}
		}
		break;
	case '3':
		{
		char file[256];
		strcpy(file,flyengine->flydatapath);
		strcat(file,"objects\\");
		if (*((mesh **)pd[i].data)==0)
			strcat(file,"*.3ds");
		else strcat(file,(*((mesh **)pd[i].data))->name);
		char *c=edit_files("3ds","3DStudio model files (*.3ds)|*.3ds||",file);
		if (c)
			{
			*((mesh **)pd[i].data)=flyengine->get_model_object(c);
			flyengine->close_texture_cache();
			flyengine->init_texture_cache();
			flag=1;
			}
		}
		break;
	case 'm':
		{
		char file[256];
		strcpy(file,flyengine->flydatapath);
		strcat(file,"objects\\");
		if (*((mesh **)pd[i].data)==0)
			strcat(file,"*.fao");
		else strcat(file,(*((mesh **)pd[i].data))->name);
		char *c=edit_files("fao","Fly3D Animated Object (*.fao)|*.fao||",file);
		if (c)
			{
			*((mesh **)pd[i].data)=flyengine->get_model_object(c);
			flyengine->close_texture_cache();
			flyengine->init_texture_cache();
			flag=1;
			}
		}
		break;
	case 'z':
		{
		char file[256];
		strcpy(file,flyengine->flydatapath);
		strcat(file,"objects\\");
		if (*((bezier_curve **)pd[i].data)==0)
			strcat(file,"*.bez");
		else strcat(file,(*((bezier_curve**)pd[i].data))->name);
		char *c=edit_files("bez","Fly3D Bezier Curve (*.bez)|*.bez||",file);
		if (c)
			{
			*((bezier_curve **)pd[i].data)=flyengine->get_bezier_curve(c);
			flag=1;
			}
		}
		break;
	case 'h':
		{
		char file[256];
		strcpy(file,flyengine->flydatapath);
		strcat(file,"objects\\");
		if (*((bezier_patch **)pd[i].data)==0)
			strcat(file,"*.pch");
		else strcat(file,(*((bezier_patch**)pd[i].data))->name);
		char *c=edit_files("pch","Fly3D Bezier Patch (*.pch)|*.pch||",file);
		if (c)
			{
			*((bezier_patch **)pd[i].data)=flyengine->get_bezier_patch(c);
			flag=1;
			}
		}
		break;
	case 'c':
		{
		vector *v=(vector *)pd[i].data;
		COLORREF c=RGB(v->x*255,v->y*255,v->z*255);
		CColorDialog cd(c,CC_FULLOPEN,this);
		if (cd.DoModal()==IDOK)
			{
			c=cd.GetColor();
			v->x=GetRValue(c)/255.0f;
			v->y=GetGValue(c)/255.0f;
			v->z=GetBValue(c)/255.0f;
			flag=1;
			}
		}
		break;
	case 'f':
	case 'v':
	case 's':
	case 'i':
	case 'a':
		edit_value(i);
		flag=1;
		break;
	case 'o':
	case 'd':
		edit_list(i);
		flag=1;
		break;
	case 'b':
		char file[256];
		CFlyEditorDoc *doc=GetDocument();
		if (doc->GetPathName().IsEmpty())
			{
			AfxMessageBox("Changing this parameter requires saving the current document.",MB_OK|MB_ICONINFORMATION);
			break;
			}

		if (IDNO==AfxMessageBox("Changing the bsp file requires saving the current document and restarting.\nDo you want to proceed ?",MB_YESNO|MB_ICONQUESTION))
			break;

		strcpy(file,flyengine->flydatapath);
		strcat(file,"*.bsp");
		char *c=edit_files("bsp","Fly bsp files (*.bsp)|*.bsp||",file);
		if (c)
			{
			*strrchr(c,'.')=0;
			strcpy((char *)pd[i].data,c);
			doc->OnSaveDocument((char *)(LPCSTR)doc->GetPathName());
			doc->OnOpenDocument((char *)(LPCSTR)doc->GetPathName());
			}
		break;
	}
	update_instances(i);
	GetDocument()->SetModifiedFlag(flag);
	rv->Invalidate(0);
}

char *CFlyEditorView::edit_files(char *ext,char *filter,char *cur)
{
	static char file[256];
	CFileDialog fd(TRUE,ext,cur,OFN_NOCHANGEDIR|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST,filter,this);
	if (fd.DoModal()==IDOK)
	{
		strcpy(file,fd.GetPathName());
		strlwr(file);

		if (strrchr(cur,'\\'))
			*(strrchr(cur,'\\')+1)=0;
		else if (strrchr(cur,'/'))
			*(strrchr(cur,'/')+1)=0;
		int len=strlen(cur);
		if (!strncmp(file,cur,len))
			return &file[len];
	}
	return 0;
}

void CFlyEditorView::edit_list(int i)
{
	CDlgEditList dlg;
	dlg.pd=&pd[i];
	dlg.DoModal();
}

void CFlyEditorView::edit_value(int i)
{
	CDlgEditValue dlg;
	dlg.pd=&pd[i];
	strcpy(dlg.value,get_param_formated(i));
	dlg.DoModal();
}

void CFlyEditorView::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDown = (LV_KEYDOWN*)pNMHDR;

	if (pLVKeyDown->wVKey==VK_RETURN)
		OnDblclk(0,0);
	else if (pLVKeyDown->wVKey==VK_DELETE)
	{
	CListCtrl& list=GetListCtrl();
	POSITION pos=list.GetFirstSelectedItemPosition();
	if (pos==0)	return;
	int i=list.GetNextSelectedItem(pos);
	char str[256];
	sprintf(str,"Clear parameter '%s' ?",pd[i].name);
	if (IDYES==AfxMessageBox(str,MB_YESNO|MB_ICONQUESTION))
		{
		int len=4;
		if (pd[i].type=='v' || pd[i].type=='c')
			len=12;
		else if (pd[i].type=='s' || pd[i].type=='b')
			len=1;
		if (pd[i].type=='p')
			*((int *)pd[i].data)=-1;
		else memset(pd[i].data,0,len);
		
		char *buf=get_param_formated(i);
		list.SetItem(i,1,LVIF_TEXT,buf,0,0,0,0);
		GetDocument()->SetModifiedFlag();
		}
	}
	
	*pResult = 0;
}

void CFlyEditorView::set_param_list(bsp_object *o)
{
	char buf[256];
	int i,j,k;
	reset_param_list();	
	if (o!=0)
		{
		k=0;
		for( j=0;j<NUM_DEFAULT_PARAM;j++ )
			{
			o->get_param_desc(j,&pd[k]);
			sprintf(buf,"(%s)",pd[k].name);
			insert_param(buf,pd[k].type,pd[k].data);
			k++;
			}
		i=o->get_param_desc(0,0);
		for( j=NUM_DEFAULT_PARAM;j<i;j++ )
			o->get_param_desc(j,&pd[k++]);
		nparam=k;
		fill_param_list();
		}
}

void CFlyEditorView::update_param_list()
{
	GetDocument()->find_active();
	if (active_sel)
		{
		int i,j,k=0;
		for( j=0;j<NUM_DEFAULT_PARAM;j++ )
			{
			active_sel->get_param_desc(j,&pd[k]);
			k++;
			}
		i=active_sel->get_param_desc(0,0);
		for( j=NUM_DEFAULT_PARAM;j<i;j++ )
			active_sel->get_param_desc(j,&pd[k++]);
		if (k==nparam)
			{
			CListCtrl& list=GetListCtrl();
			for( i=0;i<nparam;i++ )
				list.SetItem(i,1,LVIF_TEXT,pd[i].get_string(),0,0,0,0);
			}
		}
}