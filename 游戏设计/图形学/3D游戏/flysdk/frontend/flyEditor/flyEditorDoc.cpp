// flyEditorDoc.cpp : implementation of the CFlyEditorDoc class
//

#include "stdafx.h"
#include "flyEditor.h"
#include "flyEditorDoc.h"
#include "flyEditorView.h"
#include "flyRenderView.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFlyRenderView *rv;
extern CFlyEditorView *lv;
extern CLeftView *tv;

extern int drawflag;
int active_mode=0,active_num,active_tot;
bsp_object *active_sel=0;
extern CDialogBar *dlgBar;

/////////////////////////////////////////////////////////////////////////////
// CFlyEditorDoc

IMPLEMENT_DYNCREATE(CFlyEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CFlyEditorDoc, CDocument)
	//{{AFX_MSG_MAP(CFlyEditorDoc)
	ON_COMMAND(ID_SIMMULATE, OnSimmulate)
	ON_UPDATE_COMMAND_UI(ID_SIMMULATE, OnUpdateSimmulate)
	ON_COMMAND(ID_RENDER_OPENGL, OnRenderOpengl)
	ON_UPDATE_COMMAND_UI(ID_RENDER_OPENGL, OnUpdateRenderOpengl)
	ON_COMMAND(ID_RENDER_NORENDER, OnRenderNorender)
	ON_UPDATE_COMMAND_UI(ID_RENDER_NORENDER, OnUpdateRenderNorender)
	ON_COMMAND(ID_FILE_RESTART, OnFileRestart)
	ON_UPDATE_COMMAND_UI(ID_FILE_RESTART, OnUpdateFileRestart)
	ON_COMMAND(ID_VIEW_OBJSCENE, OnViewObjscene)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OBJSCENE, OnUpdateViewObjscene)
	ON_BN_CLICKED(IDC_ACTIVATE, OnActivate)
	ON_BN_CLICKED(IDC_ACTIVE, OnActive)
	ON_BN_CLICKED(IDC_DESTROY, OnDestroy)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN, OnDeltaposSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlyEditorDoc construction/destruction

CFlyEditorDoc::CFlyEditorDoc()
{
	flyengine=this;
	noinput=1;
	tree_il.Create(IDB_TREE_ICONS,16,0,RGB(192,192,192));
	appid=FLYAPPID_FLYEDITOR;
}

CFlyEditorDoc::~CFlyEditorDoc()
{
	close_fly_file();
	free_directx();
}

/////////////////////////////////////////////////////////////////////////////
// CFlyEditorDoc serialization

void CFlyEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFlyEditorDoc diagnostics

#ifdef _DEBUG
void CFlyEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFlyEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFlyEditorDoc commands

BOOL CFlyEditorDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	set_engine(this,rv->m_hWnd,AfxGetInstanceHandle(),FLYAPPID_FLYEDITOR);
	init_directx();

	char str[256],fly_file_name[256];
	strcpy(fly_file_name,lpszPathName);
	strcpy(str,flysdkpath);
	strcat(str,"data\\");
	int len=strlen(str);
	_strlwr(fly_file_name);
	if (strncmp(fly_file_name,str,len)==0)
		open_fly_file(&fly_file_name[len]);
	if (flyfilename[0]==0)
	{
		strcpy(str,"Could not load .fly file:\n");
		strcat(str,fly_file_name);
		AfxMessageBox(str,MB_OK|MB_ICONEXCLAMATION);
	}

	FillTreeView();
	SetModifiedFlag(0);

	return TRUE;
}

BOOL CFlyEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	set_engine(this,rv->m_hWnd,AfxGetInstanceHandle(),FLYAPPID_FLYEDITOR);
	init_directx();

	close_fly_file();

	CTreeCtrl& tree=tv->GetTreeCtrl();
	tree.SelectItem(0);
	tree.DeleteAllItems();
	
	CListCtrl& list=lv->GetListCtrl();
	list.DeleteAllItems();
	list.DeleteColumn(0);
	list.DeleteColumn(0);
	list.DeleteColumn(0);

	FillTreeView();

	SetModifiedFlag(0);

	UpdateAllViews(0);

	return TRUE;
}

void CFlyEditorDoc::FillTreeView()
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	tree.SelectItem(0);
	tree.DeleteAllItems();
	tree.ModifyStyle(0,TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT|TVS_SHOWSELALWAYS|TVS_EDITLABELS);
	tree.SetImageList(&tree_il,TVSIL_NORMAL);

	CListCtrl& list=lv->GetListCtrl();
	list.ModifyStyle(0,LVS_SINGLESEL);

	int i,j,k=0;
	char *name;
	HTREEITEM item1,item2,item3,item4,item5;

	item1=tree.InsertItem("Global");
	tree.SetItemData(item1,TREE_TYPE_GLOBAL);
	tree.SetItemImage(item1,TREE_TYPE_GLOBAL*2,TREE_TYPE_GLOBAL*2+1);
	item2=tree.InsertItem("Plugins");
	tree.SetItemData(item2,TREE_TYPE_PLUGINS);
	tree.SetItemImage(item2,TREE_TYPE_PLUGINS*2,TREE_TYPE_PLUGINS*2+1);
	for( i=0;i<dll.ndll;i++ )
		{
		item3=tree.InsertItem(dll.dll[i]->dll_filename,item2);
		tree.SetItemData(item3,TREE_TYPE_DLLS);
		tree.SetItemImage(item3,TREE_TYPE_DLLS*2,TREE_TYPE_DLLS*2+1);
		for( j=0;j<dll.dll[i]->nclasses;j++ )
			{
			name=dll.cd[k++]->get_name();
			item4=tree.InsertItem(name,item3);
			tree.SetItemData(item4,TREE_TYPE_STOCK);
			tree.SetItemImage(item4,TREE_TYPE_STOCK*2,TREE_TYPE_STOCK*2+1);
			char buf[256];
			int n=0;
			while(1)
				{
				sprintf(buf,"%s%i",name,n++);
				bsp_object *o=get_stock_object(buf);
				if (o==0) break;
				item5=tree.InsertItem(o->long_name,item4);
				tree.SetItemData(item5,(DWORD)o);
				tree.SetItemImage(item5,TREE_TYPE_DYNOBJECT*2,TREE_TYPE_DYNOBJECT*2+1);
				}
			}
		}

	item2=tree.InsertItem("Objects");
	tree.SetItemData(item2,TREE_TYPE_OBJECTS);
	tree.SetItemImage(item2,TREE_TYPE_OBJECTS*2,TREE_TYPE_OBJECTS*2+1);
	
	item2=tree.InsertItem("Sounds");
	tree.SetItemData(item2,TREE_TYPE_SOUNDS);
	tree.SetItemImage(item2,TREE_TYPE_SOUNDS*2,TREE_TYPE_SOUNDS*2+1);
	
	item2=tree.InsertItem("Textures");
	tree.SetItemData(item2,TREE_TYPE_TEXTURES);
	tree.SetItemImage(item2,TREE_TYPE_TEXTURES*2,TREE_TYPE_TEXTURES*2+1);

	item2=tree.InsertItem("Lightmaps");
	tree.SetItemData(item2,TREE_TYPE_LIGHTMAPS);
	tree.SetItemImage(item2,TREE_TYPE_LIGHTMAPS*2,TREE_TYPE_LIGHTMAPS*2+1);

	tree.SelectItem(item1);
}

void CFlyEditorDoc::OnSimmulate() 
{
	if (rv->timer==0)
		rv->timer=rv->SetTimer(1,1,0);
	else 
		{
		rv->KillTimer(rv->timer);
		rv->timer=0;
		}
}

void CFlyEditorDoc::OnUpdateSimmulate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(rv->timer);
}

void CFlyEditorDoc::OnRenderNorender() 
{
	if (rv->render_type!=0)
		{
		rv->render_type=0;
		close_texture_cache();
		free_render();
		}
	rv->Invalidate(1);
}

void CFlyEditorDoc::OnUpdateRenderNorender(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(rv->render_type==0);
}

void CFlyEditorDoc::OnRenderOpengl() 
{
	if (rv->render_type!=1)
		{
		rv->render_type=1;
		close_texture_cache();
		init_render(FLY_RENDER_OPENGL);
		init_texture_cache();
		}
	else OnRenderNorender();
	rv->Invalidate(1);
}

void CFlyEditorDoc::OnUpdateRenderOpengl(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(rv->render_type==1);	
}

BOOL CFlyEditorDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	char str[256],fly_file_name[256];

	strcpy(fly_file_name,lpszPathName);
	strcpy(str,flysdkpath);
	strcat(str,"data\\");
	int len=strlen(str);

	_strlwr(fly_file_name);
	if (strncmp(fly_file_name,str,len)==0)
	{
		if (save_fly_file(&fly_file_name[len]))
		{
			SetModifiedFlag(0);
			return 1;
		}
	}

	strcpy(str,"Could not save .fly file:\n");
	strcat(str,fly_file_name);
	AfxMessageBox(str,MB_OK|MB_ICONEXCLAMATION);
	return 0;
}

void CFlyEditorDoc::OnFileRestart() 
{
	if (IsModified())
		OnSaveDocument((char *)(LPCSTR)GetPathName());
	OnOpenDocument((char *)(LPCSTR)GetPathName());
	UpdateAllViews(0);
}

void CFlyEditorDoc::OnUpdateFileRestart(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!GetPathName().IsEmpty());
}

void CFlyEditorDoc::OnViewObjscene() 
{
	drawflag=!drawflag;
	rv->Invalidate(0);
}

void CFlyEditorDoc::OnUpdateViewObjscene(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(drawflag);
}

void CFlyEditorDoc::OnActivate() 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD type=tree.GetItemData(item);
	if (type>255)
		flyengine->activate(((bsp_object *)type)->clone());
	rv->Invalidate(0);
}

void CFlyEditorDoc::find_active()
{
	static char str[32];

	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD type=tree.GetItemData(item);

	active_num=-1;
	active_tot=0;

	if (type<256)
	{
		active_sel=0;
		dlgBar->GetDlgItem(IDC_NUM)->SetWindowText("");
		return;
	}

	bsp_object *o=active_obj0,*first=0;
	while(o)
		{
		if (o->source==(bsp_object *)type)
			{
			if (o==active_sel)
				active_num=active_tot;
			if (first==0)
				first=o;
			active_tot++;
			}
		o=(bsp_object *)o->next_obj;
		}

	if (active_num==-1 || active_sel==0)
		{
		active_sel=first;
		if (active_tot>0)
			active_num=0;
		else active_num=-1;
		}

	if (active_sel==0)
		active_sel=(bsp_object *)type;
	
	if (active_tot==0)
		strcpy(str,"None");
	else if (active_mode==0)
			sprintf(str,"%i",active_tot);
		else sprintf(str,"%i/%i",active_num+1,active_tot);
	dlgBar->GetDlgItem(IDC_NUM)->SetWindowText(str);

	if (active_mode==0 && type>255)
		active_sel=(bsp_object *)type;
}

void CFlyEditorDoc::OnActive() 
{
	active_mode=dlgBar->IsDlgButtonChecked(IDC_ACTIVE);
	dlgBar->GetDlgItem(IDC_NUM)->EnableWindow(active_mode);
	dlgBar->GetDlgItem(IDC_SPIN)->EnableWindow(active_mode);
	dlgBar->GetDlgItem(IDC_ACTIVATE)->EnableWindow(active_mode);
	dlgBar->GetDlgItem(IDC_DESTROY)->EnableWindow(active_mode);
	lv->update_param_list();
	rv->Invalidate(0);
}

void CFlyEditorDoc::OnDestroy() 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD type=tree.GetItemData(item);
	
	if (active_mode==1 && active_sel)
	{
		bsp_object *o=active_obj0,*op=0;
		while(o)
			{
			if (o->source==(bsp_object *)type)
				if (o==active_sel)
					break;
			op=o;
			o=(bsp_object *)o->next_obj;
			}
		if (o==0) return;
		
		if (last_active_obj==o)
			last_active_obj=op;
		
		bsp_object *n=(bsp_object *)o->next_obj;
		delete o;
		if (op==0)
			{
			active_obj0=n;
			active_sel=n;
			}
		else 
			{
			op->next_obj=n;
			active_sel=op;
			}

		lv->update_param_list();
		rv->Invalidate(0);
	}
}

void CFlyEditorDoc::OnDeltaposSpin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD type=tree.GetItemData(item);
	if (active_mode && type>255)
	{
	if (pNMUpDown->iDelta==-1)
		{
		if (active_num<active_tot-1)
			active_num++;
		}
	else
	if (pNMUpDown->iDelta==1)
		{
		if (active_num>0)
			active_num--;
		}

	active_sel=0;
	int i=active_num;
	bsp_object *o=active_obj0;
	while(o)
		{
		if (o->source==(bsp_object *)type)
			if (i==0)
				{
				active_sel=o;
				break;
				}
			else i--;
		o=(bsp_object *)o->next_obj;
		}
	}
	lv->update_param_list();
	rv->Invalidate(0);
	
	*pResult = 0;
}
