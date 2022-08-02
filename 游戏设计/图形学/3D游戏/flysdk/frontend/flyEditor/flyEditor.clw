; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CLeftView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "flyeditor.h"
LastPage=0

ClassCount=9
Class1=CDlgEditList
Class2=CDlgEditValue
Class3=CFlyEditorApp
Class4=CAboutDlg
Class5=CFlyEditorDoc
Class6=CFlyEditorView
Class7=CFlyRenderView
Class8=CLeftView
Class9=CMainFrame

ResourceCount=5
Resource1=IDB_TREE_ICONS (English (U.S.))
Resource2=IDR_MAINFRAME (English (U.S.))
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDD_EDITVALUE (English (U.S.))
Resource5=IDD_EDITLIST (English (U.S.))

[CLS:CDlgEditList]
Type=0
BaseClass=CDialog
HeaderFile=DlgEditList.h
ImplementationFile=DlgEditList.cpp

[CLS:CDlgEditValue]
Type=0
BaseClass=CDialog
HeaderFile=DlgEditValue.h
ImplementationFile=DlgEditValue.cpp

[CLS:CFlyEditorApp]
Type=0
BaseClass=CWinApp
HeaderFile=flyEditor.h
ImplementationFile=flyEditor.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=flyEditor.cpp
ImplementationFile=flyEditor.cpp
LastObject=CAboutDlg

[CLS:CFlyEditorDoc]
Type=0
BaseClass=CDocument
HeaderFile=flyEditorDoc.h
ImplementationFile=flyEditorDoc.cpp
Filter=N
VirtualFilter=DC
LastObject=CFlyEditorDoc

[CLS:CFlyEditorView]
Type=0
BaseClass=CListView
HeaderFile=flyEditorView.h
ImplementationFile=flyEditorView.cpp

[CLS:CFlyRenderView]
Type=0
BaseClass=CView
HeaderFile=flyRenderView.h
ImplementationFile=flyRenderView.cpp

[CLS:CLeftView]
Type=0
BaseClass=CTreeView
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
Filter=C
VirtualFilter=VWC
LastObject=ID_EDIT_PASTE

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[DLG:IDD_EDITLIST]
Type=1
Class=CDlgEditList

[DLG:IDD_EDITVALUE]
Type=1
Class=CDlgEditValue

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_RESTART
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_DUPLICATE
Command9=ID_UP
Command10=ID_DOWN
Command11=ID_SIMMULATE
Command12=ID_RENDER_OPENGL
Command13=ID_VIEW_OBJSCENE
Command14=ID_APP_ABOUT
CommandCount=14

[TB:IDB_TREE_ICONS (English (U.S.))]
Type=1
Class=?
Command1=ID_STATIC
Command2=ID_STATIC
Command3=ID_STATIC
Command4=ID_STATIC
Command5=ID_STATIC
Command6=ID_STATIC
Command7=ID_STATIC
Command8=ID_STATIC
Command9=ID_STATIC
Command10=ID_STATIC
Command11=ID_STATIC
Command12=ID_STATIC
Command13=ID_STATIC
Command14=ID_STATIC
Command15=ID_STATIC
Command16=ID_STATIC
Command17=ID_STATIC
Command18=ID_STATIC
Command19=ID_STATIC
Command20=ID_STATIC
CommandCount=20

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_RESTART
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_EDIT_DUPLICATE
Command12=ID_EDIT_INSERT
Command13=ID_EDIT_DELETE
Command14=ID_EDIT_RENAME
Command15=ID_RENDER_NORENDER
Command16=ID_RENDER_OPENGL
Command17=ID_RENDER_DIRECT3D
Command18=ID_SIMMULATE
Command19=ID_VIEW_TOOLBAR
Command20=ID_VIEW_STATUS_BAR
Command21=ID_TOOLS_LIGHT
Command22=ID_TOOLS_VIEWPVS
Command23=ID_TOOLS_PAKFPK
Command24=ID_TOOLS_UNPAKFPK
Command25=ID_APP_ABOUT
CommandCount=25

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_DUPLICATE
Command3=ID_EDIT_PASTE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_RENAME
Command6=ID_SIMMULATE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_CUT
CommandCount=11

[DLG:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_ACTIVE,button,1342242819
Control2=IDC_NUM,static,1342181377
Control3=IDC_SPIN,msctls_updown32,1342177376
Control4=IDC_ACTIVATE,button,1342177280
Control5=IDC_DESTROY,button,1342177280

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_EDITVALUE (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_STATIC,static,1342177280
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

[DLG:IDD_EDITLIST (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_LIST1,listbox,1352728835
Control2=IDC_STATIC,static,1342177280
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816

