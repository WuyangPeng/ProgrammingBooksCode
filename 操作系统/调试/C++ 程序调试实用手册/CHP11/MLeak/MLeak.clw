; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMLeakView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MLeak.h"
LastPage=0

ClassCount=5
Class1=CMLeakApp
Class2=CMLeakDoc
Class3=CMLeakView
Class4=CMainFrame

ResourceCount=2
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX

[CLS:CMLeakApp]
Type=0
HeaderFile=MLeak.h
ImplementationFile=MLeak.cpp
Filter=N

[CLS:CMLeakDoc]
Type=0
HeaderFile=MLeakDoc.h
ImplementationFile=MLeakDoc.cpp
Filter=N

[CLS:CMLeakView]
Type=0
HeaderFile=MLeakView.h
ImplementationFile=MLeakView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CMLeakView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=MLeak.cpp
ImplementationFile=MLeak.cpp
Filter=D

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

