// LeftView.cpp : implementation of the CLeftView class
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
extern int active_mode;
extern bsp_object *active_sel;
CLeftView *tv=0;

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, OnKeydown)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_EDIT_INSERT, OnEditInsert)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_INSERT, OnUpdateEditInsert)
	ON_COMMAND(ID_EDIT_RENAME, OnEditRename)
	ON_UPDATE_COMMAND_UI(ID_EDIT_RENAME, OnUpdateEditRename)
	ON_UPDATE_COMMAND_UI(ID_DOWN, OnUpdateDown)
	ON_COMMAND(ID_DOWN, OnDown)
	ON_UPDATE_COMMAND_UI(ID_UP, OnUpdateUp)
	ON_COMMAND(ID_UP, OnUp)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_DUPLICATE, OnEditDuplicate)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DUPLICATE, OnUpdateEditDuplicate)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	tv=this;
}

CLeftView::~CLeftView()
{
	tv=0;
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CFlyEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CFlyEditorDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFlyEditorDoc)));
	return (CFlyEditorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

void CLeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	if (pResult) *pResult = 0;

	int i,j;
	char buf[256];

	CFlyEditorDoc *doc=GetDocument();

	CListCtrl& list=lv->GetListCtrl();
	
	list.DeleteAllItems();
	list.ModifyStyle(0,LVS_SHOWSELALWAYS);

	for( i=0;i<lv->ncol;i++ )
	{
	lv->colsizes[i]=list.GetColumnWidth(0);
	list.DeleteColumn(0);
	}
	lv->ncol=0;

	CTreeCtrl& tree=GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD type=tree.GetItemData(item);

	GetDocument()->find_active();
	if (type>255)
		{
		bsp_object *o;
		if (active_mode)
			o=active_sel;
		else 
			o=(bsp_object *)type;
		lv->set_param_list(o);
		}
	else
	switch(type)
	{
	case TREE_TYPE_TEXTURES:
		list.InsertColumn( 0, "File", LVCFMT_LEFT, lv->colsizes[0],0 );
		list.InsertColumn( 1, "Size", LVCFMT_LEFT, lv->colsizes[1],0 );
		lv->ncol=2;
		for( i=0;i<doc->npiclib;i++ )
			{
			list.InsertItem(i,doc->piclib[i]->name);
			sprintf(buf,"%ix%ix%i",doc->piclib[i]->sx,doc->piclib[i]->sy,doc->piclib[i]->bytespixel*8);
			list.SetItem(i,1,LVIF_TEXT,buf,0,0,0,0);
			}
		break;
	case TREE_TYPE_LIGHTMAPS:
		list.InsertColumn( 0, "File", LVCFMT_LEFT, lv->colsizes[0],0 );
		list.InsertColumn( 1, "Size", LVCFMT_LEFT, lv->colsizes[1],0 );
		lv->ncol=2;
		for( i=0;i<doc->nlmpic;i++ )
			{
			sprintf(buf,"lightmap%i",i);
			list.InsertItem(i,buf);
			sprintf(buf,"%ix%ix%i",doc->lmpic[i]->sizex,doc->lmpic[i]->sizey,24);
			list.SetItem(i,1,LVIF_TEXT,buf,0,0,0,0);
			}
		break;
	case TREE_TYPE_OBJECTS:
		{
		list.InsertColumn( 0, "File", LVCFMT_LEFT, lv->colsizes[0],0 );
		list.InsertColumn( 1, "nvert", LVCFMT_LEFT, lv->colsizes[1],0 );
		list.InsertColumn( 2, "nface", LVCFMT_LEFT, lv->colsizes[2],0 );
		lv->ncol=3;
		mesh *o=doc->model_obj0;
		i=0;
		while(o)
			{
			list.InsertItem(i,o->name);
			sprintf(buf,"%i",o->nv);
			list.SetItem(i,1,LVIF_TEXT,buf,0,0,0,0);
			sprintf(buf,"%i",o->nf);
			list.SetItem(i,2,LVIF_TEXT,buf,0,0,0,0);
			i++;
			o=(mesh *)o->next_obj;
			}
		}
		break;
	case TREE_TYPE_SOUNDS:
		{
		list.InsertColumn( 0, "File", LVCFMT_LEFT, lv->colsizes[0],0 );
		list.InsertColumn( 1, "Length", LVCFMT_LEFT, lv->colsizes[1],0 );
		list.InsertColumn( 2, "Format", LVCFMT_LEFT, lv->colsizes[2],0 );
		lv->ncol=3;
		sound *s=doc->sound_obj0;
		i=0;
		while(s)
			{
			char *c=strrchr(s->name,'.');
			if (c && (c[1]=='w'||c[1]=='W') && (c[2]=='a'||c[2]=='A') && (c[3]=='v'||c[3]=='V'))
				{
				list.InsertItem(i,s->name);
				sprintf(buf,"%ims",s->total_time);
				list.SetItem(i,1,LVIF_TEXT,buf,0,0,0,0);
				if (s->buf[0])
					{
					WAVEFORMATEX format;
					DWORD d;
					s->buf[0]->GetFormat(&format,sizeof(format),&d);
					sprintf(buf,"%ix%ix%i",(int)format.nSamplesPerSec,(int)format.wBitsPerSample,(int)format.nChannels);
					list.SetItem(i,2,LVIF_TEXT,buf,0,0,0,0);
					}
				i++;
				}
			s=(sound *)s->next_obj;
			}
		}
		break;
	case TREE_TYPE_GLOBAL:
		lv->reset_param_list();	
		i=flyengine->get_global_param_desc(0,0);
		for( j=0;j<i;j++ )
			{
			flyengine->get_global_param_desc(j,&lv->pd[j]);
			lv->insert_param(lv->pd[j].name,lv->pd[j].type,lv->pd[j].data);
			}
		lv->fill_param_list();
		break;
	}

	if (active_mode)
		GetDocument()->find_active();

	rv->Invalidate(0);
}

void CLeftView::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	CTreeCtrl& tree=GetTreeCtrl();
	DWORD type=tree.GetItemData(pTVDispInfo->item.hItem);

	if (type>255)
		{
		CEdit *edit=tree.GetEditControl();
		edit->SetLimitText(30);
		*pResult = 0;
		}
	else
		*pResult = 1;
}

void CLeftView::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	if (pTVDispInfo->item.pszText && pTVDispInfo->item.pszText[0] && pTVDispInfo->item.pszText[0]!=' ')
	{
	CTreeCtrl& tree=GetTreeCtrl();
	bsp_object *o=(bsp_object *)tree.GetItemData(pTVDispInfo->item.hItem);

	strcpy(o->long_name,pTVDispInfo->item.pszText);
	char *c;
	while( c=strchr(o->long_name,' ') )
		*c='_';
	bsp_object *obj=flyengine->active_obj0;
	while(obj)
		{
		if (obj->source==o)
			strcpy(obj->long_name,o->long_name);
		obj=(bsp_object *)obj->next_obj;
		}

	tree.SetItemText(pTVDispInfo->item.hItem,o->long_name);
	GetDocument()->SetModifiedFlag();
	}

	*pResult = 0;
}

void CLeftView::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;
	if (pResult) 
		*pResult = 0;

	CTreeCtrl& tree=GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD type=tree.GetItemData(item);
	char str[256];
	
	switch(pTVKeyDown->wVKey)
	{
	case VK_DELETE:
		if (type>255)
			{
			bsp_object *o=(bsp_object *)type;
			sprintf(str,"Delete object class '%s' and all active instances and references ?",o->long_name);
			HTREEITEM item2=tree.GetParentItem(item);
			if (IDYES==AfxMessageBox(str,MB_YESNO|MB_ICONQUESTION))
				{
				GetDocument()->dll.delete_class(o);
				tree.DeleteItem(item);
				GetDocument()->SetModifiedFlag();
				if (tree.ItemHasChildren(item2)==0)
					tree.SetItemImage(item2,0,0);
				}
			}
		else if (type==TREE_TYPE_DLLS)
			{
			CString s=tree.GetItemText(item);
			sprintf(str,"Delete plugin '%s' and all it's stock and active classes ?",(char *)(LPCSTR)s);
			HTREEITEM item2=tree.GetParentItem(item);
			if (IDYES==AfxMessageBox(str,MB_YESNO|MB_ICONQUESTION))
				{
				GetDocument()->dll.delete_dll((char *)(LPCSTR)s);
				tree.DeleteItem(item);
				GetDocument()->SetModifiedFlag();
				if (tree.ItemHasChildren(item2)==0)
					tree.SetItemImage(item2,0,0);
				}
			}
		rv->Invalidate(0);
		break;
	case VK_INSERT:
		if (flyengine->flydatapath[0]==0)
			AfxMessageBox("You must save the fly file before including new objects.",MB_OK|MB_ICONINFORMATION);
		else
		if (type==TREE_TYPE_OBJECTS)
		{
		char file[256];
		strcpy(file,flyengine->flydatapath);
		strcat(file,"objects\\");
		strcat(file,"*.3ds;*.fao");
		char *c=lv->edit_files("","All object files (*.3ds;*.fao)|*.3ds;*.fao|3dstudio object files (*.3ds)|*.3ds|Fly animated object files (*.fao)|*.fao||",file);
		if (c)
			{
			flyengine->get_model_object(c);
			OnSelchanged(0,0);
			}
		}
		else
		if (type==TREE_TYPE_TEXTURES)
		{
		char file[256];
		strcpy(file,flyengine->flydatapath);
		strcat(file,"maps\\");
		strcat(file,"*.jpg;*.tga");
		char *c=lv->edit_files("","All image files (*.jpg;*.tga)|*.jpg;*.tga|TGA image files (*.tga)|*.tga|JPG image files (*.jpg)|*.jpg||",file);
		if (c)
			{
			flyengine->get_picture(c);
			flyengine->close_texture_cache();
			flyengine->init_texture_cache();
			OnSelchanged(0,0);
			}
		}
		else
		if (type==TREE_TYPE_PLUGINS)
		{
			char str[256];
			strcpy(str,flyengine->flysdkpath);
			strcat(str,"plugin\\*.dll");
			char *file=lv->edit_files("dll","Fly plugin dll files (*.dll)|*.dll||",str);
			if (file)
			{
				int c=flyengine->dll.ncd,i;
				int dll=flyengine->dll.add_dll(file);
				if (dll!=-1)
				{
					flyengine->dll.load_classes(dll,0);
					HTREEITEM item2,item3;
					item2=tree.GetChildItem(item);
					if (item2==0)
						item3=tree.InsertItem(file,item);
					else 
						{
						while( item3=tree.GetNextSiblingItem(item2) )
							item2=item3;
						item3=tree.InsertItem(file,item,item2);
						}
					tree.SetItemData(item3,TREE_TYPE_DLLS);
					tree.SetItemImage(item3,TREE_TYPE_DLLS*2,TREE_TYPE_DLLS*2+1);
					for( i=c;i<flyengine->dll.ncd;i++ )
						{
						item2=tree.InsertItem(flyengine->dll.cd[i]->get_name(),item3);
						tree.SetItemData(item2,TREE_TYPE_STOCK);
						tree.SetItemImage(item2,TREE_TYPE_STOCK*2,TREE_TYPE_STOCK*2+1);
						}
					tree.EnsureVisible(item3);
					tree.SelectItem(item3);
					tree.Expand(item3,TVE_EXPAND);
					GetDocument()->SetModifiedFlag();
				}
			}
		}
		else if (type==TREE_TYPE_STOCK)
		{
			CString s=tree.GetItemText(item);
			bsp_object *o=flyengine->dll.add_class((char *)(LPCSTR)s);
			if (o)
				{
				static int count=1;
				sprintf(str,"new %s %i",(char *)(LPCSTR)s,count++);
				HTREEITEM item2,item3;
				item2=tree.GetChildItem(item);
				if (item2==0)
					item3=tree.InsertItem(str,item);
				else 
					{
					while( item3=tree.GetNextSiblingItem(item2) )
						item2=item3;
					item3=tree.InsertItem(str,item,item2);
					}
				tree.SetItemData(item3,(DWORD)o);
				tree.SetItemImage(item3,TREE_TYPE_DYNOBJECT*2,TREE_TYPE_DYNOBJECT*2+1);
				tree.EnsureVisible(item3);
				tree.SelectItem(item3);
				tree.EditLabel(item3);
				strcpy(o->long_name,str);
				o->name[0]=0;
				GetDocument()->SetModifiedFlag();
				}
		}
		rv->Invalidate(0);
		break;
	}
}

void CLeftView::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;
	CTreeCtrl& tree=GetTreeCtrl();
	if (pNMTreeView->action==2)
		tree.SetItemImage(pNMTreeView->itemNew.hItem,1,1);
	else 
	if (pNMTreeView->action==1)
		tree.SetItemImage(pNMTreeView->itemNew.hItem,0,0);
}

void CLeftView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMenu *menu;
	menu=AfxGetApp()->GetMainWnd()->GetMenu()->GetSubMenu(1);

	CTreeCtrl& tree=tv->GetTreeCtrl();

	TVHITTESTINFO hti;
	GetCursorPos(&hti.pt);
	ScreenToClient(&hti.pt);
	tree.HitTest(&hti);
	if (hti.flags&TVHT_ONITEMLABEL)
		tree.SelectItem(hti.hItem);
	
	GetCursorPos(&hti.pt);
	menu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,hti.pt.x,hti.pt.y,AfxGetApp()->GetMainWnd(),0);

	*pResult = 0;
}

void CLeftView::OnEditDelete() 
{
	TV_KEYDOWN key;
	key.wVKey=VK_DELETE;
	OnKeydown((NMHDR*)&key,0);
}

void CLeftView::OnEditInsert() 
{
	TV_KEYDOWN key;
	key.wVKey=VK_INSERT;
	OnKeydown((NMHDR*)&key,0);
}

void CLeftView::OnEditRename() 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	tree.EditLabel( item );
}

void CLeftView::OnUpdateEditRename(CCmdUI* pCmdUI) 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD o=tree.GetItemData(item);
	pCmdUI->Enable(item!=0 && o>255);
}

void CLeftView::OnUpdateEditInsert(CCmdUI* pCmdUI) 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD o=tree.GetItemData(item);

	pCmdUI->Enable(item!=0 && (o==TREE_TYPE_OBJECTS || o==TREE_TYPE_TEXTURES || o==TREE_TYPE_PLUGINS || o==TREE_TYPE_STOCK));
}

void CLeftView::OnUpdateEditDelete(CCmdUI* pCmdUI) 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD o=tree.GetItemData(item);

	pCmdUI->Enable(item!=0 && (o==TREE_TYPE_DLLS || o>255));
}

HTREEITEM CLeftView::SelectObject(HTREEITEM item,bsp_object *o)
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	DWORD type=tree.GetItemData(item);
	if (type>255)
		if (o==(bsp_object *)type)
			{
			tree.SelectItem(item);
			return item;
			}
	HTREEITEM item2,item3;
	if (tree.ItemHasChildren(item))
	{
		item2=SelectObject(tree.GetChildItem(item),o);
		if (item2)
			return item2;
	}
	item3=item;
	while(item3=tree.GetNextSiblingItem(item3))
	{
		item2=SelectObject(item3,o);
		if (item2)
			return item2;
	}

	return 0;
}
void CLeftView::OnUpdateDown(CCmdUI* pCmdUI) 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD o=tree.GetItemData(item);
	pCmdUI->Enable(o==TREE_TYPE_DLLS && tree.GetNextSiblingItem(item));
}

int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, 
		LPARAM lParamSort)
{
	return (int)lParam1-(int)lParam2;
}

void CLeftView::OnDown() 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;

	flyengine->dll.move_dll((char *)(LPCSTR)tree.GetItemText(item),1);

	HTREEITEM p=tree.GetParentItem(item);
	HTREEITEM i=tree.GetChildItem(p);
	int n=0;
	while(i)
		{
		tree.SetItemData(i,n++);
		i=tree.GetNextSiblingItem(i);
		}

	HTREEITEM a=tree.GetNextSiblingItem(item);
	int d=tree.GetItemData(a);
	tree.SetItemData(item,d);
	tree.SetItemData(a,d-1);

	TVSORTCB data;
	data.lParam=0;
	data.lpfnCompare=CompareFunc;
	data.hParent=p;
	tree.SortChildrenCB(&data);

	i=tree.GetChildItem(p);
	while(i)
		{
		tree.SetItemData(i,TREE_TYPE_DLLS);
		i=tree.GetNextSiblingItem(i);
		}

	GetDocument()->SetModifiedFlag();
}

void CLeftView::OnUpdateUp(CCmdUI* pCmdUI) 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;
	DWORD o=tree.GetItemData(item);
	pCmdUI->Enable(o==TREE_TYPE_DLLS && tree.GetPrevSiblingItem(item));
}

void CLeftView::OnUp() 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item==0) return;

	flyengine->dll.move_dll((char *)(LPCSTR)tree.GetItemText(item),-1);

	HTREEITEM p=tree.GetParentItem(item);
	HTREEITEM i=tree.GetChildItem(p);
	int n=0;
	while(i)
		{
		tree.SetItemData(i,n++);
		i=tree.GetNextSiblingItem(i);
		}

	HTREEITEM a=tree.GetPrevSiblingItem(item);
	int d=tree.GetItemData(a);
	tree.SetItemData(item,d);
	tree.SetItemData(a,d+1);

	TVSORTCB data;
	data.lParam=0;
	data.lpfnCompare=CompareFunc;
	data.hParent=p;
	tree.SortChildrenCB(&data);

	i=tree.GetChildItem(p);
	while(i)
		{
		tree.SetItemData(i,TREE_TYPE_DLLS);
		i=tree.GetNextSiblingItem(i);
		}

	GetDocument()->SetModifiedFlag();
}

void CLeftView::OnEditCut() 
{
	OnEditCopy();

	CFlyEditorDoc* pDoc = GetDocument();
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	HTREEITEM item2=tree.GetParentItem(item);
	DWORD type=tree.GetItemData(item);
	bsp_object *o=(bsp_object *)type;
	pDoc->dll.delete_class(o);
	tree.DeleteItem(item);
	if (tree.ItemHasChildren(item2)==0)
		tree.SetItemImage(item2,0,0);
	pDoc->SetModifiedFlag();
}

void CLeftView::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	DWORD type=0;
	if (item!=0) 
		type=tree.GetItemData(item);
	pCmdUI->Enable(type>255);
}

void CLeftView::OnEditCopy() 
{
	CFlyEditorDoc* pDoc = GetDocument();
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	DWORD type=tree.GetItemData(item);
	bsp_object *o=(bsp_object *)type;

	if ( ::OpenClipboard(0) )
	{
		EmptyClipboard();

		HGLOBAL hData=GlobalAlloc(GMEM_MOVEABLE,16384);
		char *buf=(char *)GlobalLock(hData);
		char str[256];
		int i,j;
		param_desc pd;
		for( i=0;i<pDoc->dll.ncd;i++ )
			if (pDoc->dll.cd[i]->get_type()==o->type)
				break;

		buf[0]=0;

		sprintf(str,"fly3dclass %s %s\r\n",pDoc->dll.cd[i]->get_name(),o->long_name);
		strcat(buf,str);

		j=o->get_param_desc(0,0);
		for( i=0;i<j;i++ )
		{
			o->get_param_desc(i,&pd);
			sprintf(str,"%s=%s\r\n",pd.name,pd.get_string());
			strcat(buf,str);
		}

		GlobalUnlock(hData);
		SetClipboardData( CF_TEXT, hData );

		CloseClipboard();	
	}
}

void CLeftView::OnUpdateEditCopy(CCmdUI* pCmdUI) 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	DWORD type=0;
	if (item!=0) 
		type=tree.GetItemData(item);
	pCmdUI->Enable(type>255);
}

void CLeftView::OnEditPaste() 
{
	if (IsClipboardFormatAvailable(CF_TEXT))
	{
		if (::OpenClipboard(0))
		{
			HGLOBAL hData=GetClipboardData(CF_TEXT);
			if (hData)
				{
				char *buf=(char *)GlobalLock(hData);

				char *c1=strchr(buf,'\r');
				*c1=0;
				c1+=2;
				char *c2=strchr(buf,' ');
				*(c2++)=0;
				char *c3=strchr(c2,' ');
				*(c3++)=0;

				bsp_object *o=flyengine->dll.add_class(c2);
				if (o)
					{
					strcpy(o->long_name,c3);
					strcat(o->long_name,"_copy");
					o->name[0]=0;

					param_desc pd;
					int i,j,k;
					j=o->get_param_desc(0,0);
					for( i=0;i<j;i++ )
					{
						o->get_param_desc(i,&pd);
						k=strlen(pd.name);
						if (memcmp(pd.name,c1,k)==0)
						{
						c2=&c1[k+1];
						c3=strchr(c1,'\r');
						*c3=0;
						c1=c3+2;
						pd.set_string(c2);
						}
					}

					CTreeCtrl& tree=tv->GetTreeCtrl();
					HTREEITEM item=tree.GetSelectedItem();
					HTREEITEM item2,item3;
					item2=tree.GetChildItem(item);
					if (item2==0)
						item3=tree.InsertItem(o->long_name,item);
					else 
						{
						while( item3=tree.GetNextSiblingItem(item2) )
							item2=item3;
						item3=tree.InsertItem(o->long_name,item,item2);
						}

					tree.SetItemData(item3,(DWORD)o);
					tree.SetItemImage(item3,TREE_TYPE_DYNOBJECT*2,TREE_TYPE_DYNOBJECT*2+1);
					tree.EnsureVisible(item3);
					tree.SelectItem(item3);
					tree.EditLabel(item3);
					}
				else AfxMessageBox("Could not paste !\nClass name not present in scene.",MB_OK|MB_ICONINFORMATION);

				GlobalUnlock(hData);
				GetDocument()->SetModifiedFlag();
				}
			CloseClipboard();
		}
	}
}

void CLeftView::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	int pasteok=0;
	
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	if (item && tree.GetItemData(item)==TREE_TYPE_STOCK)
	if (IsClipboardFormatAvailable(CF_TEXT))
	{
		if (::OpenClipboard(0))
		{
			HGLOBAL hData=GetClipboardData(CF_TEXT);
			if (hData)
				{
				char *buf=(char *)GlobalLock(hData);
				CString s=tree.GetItemText(item);
				if (memcmp(buf,"fly3dclass ",11)==0)
					if (memcmp(&buf[11],s,s.GetLength())==0)
						pasteok=1;
				GlobalUnlock(hData);
				}
			CloseClipboard();
		}
	}
	pCmdUI->Enable( pasteok );
}

void CLeftView::OnEditDuplicate() 
{
	OnEditCopy();
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	tree.SelectItem(tree.GetParentItem(item));
	OnEditPaste();
}

void CLeftView::OnUpdateEditDuplicate(CCmdUI* pCmdUI) 
{
	CTreeCtrl& tree=tv->GetTreeCtrl();
	HTREEITEM item=tree.GetSelectedItem();
	DWORD type=0;
	if (item!=0) 
		type=tree.GetItemData(item);
	pCmdUI->Enable(type>255);
}

