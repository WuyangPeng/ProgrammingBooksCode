; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGraphView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "graph.h"
LastPage=0

ClassCount=5
Class1=CGraphApp
Class2=CGraphDoc
Class3=CGraphView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CGraphApp]
Type=0
HeaderFile=graph.h
ImplementationFile=graph.cpp
Filter=N

[CLS:CGraphDoc]
Type=0
HeaderFile=graphDoc.h
ImplementationFile=graphDoc.cpp
Filter=N

[CLS:CGraphView]
Type=0
HeaderFile=graphView.h
ImplementationFile=graphView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CGraphView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=graph.cpp
ImplementationFile=graph.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=ID_APP_ABOUT
CommandCount=2

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

