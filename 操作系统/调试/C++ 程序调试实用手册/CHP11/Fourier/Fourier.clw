; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFourierView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Fourier.h"
LastPage=0

ClassCount=7
Class1=CFourierApp
Class2=CFourierDoc
Class3=CFourierView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=FourierDlg
Class7=FourierDlg2
Resource3=IDD_DIALOG1

[CLS:CFourierApp]
Type=0
HeaderFile=Fourier.h
ImplementationFile=Fourier.cpp
Filter=N

[CLS:CFourierDoc]
Type=0
HeaderFile=FourierDoc.h
ImplementationFile=FourierDoc.cpp
Filter=N

[CLS:CFourierView]
Type=0
HeaderFile=FourierView.h
ImplementationFile=FourierView.cpp
Filter=C
LastObject=IDM_FOURIER
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T




[CLS:CAboutDlg]
Type=0
HeaderFile=Fourier.cpp
ImplementationFile=Fourier.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308481
Control3=IDC_STATIC,static,1342308353
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308353
Control6=IDC_STATIC,static,1342308353

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=IDM_FOURIER
Command3=IDM_COLOR
Command4=ID_APP_ABOUT
CommandCount=4

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

[DLG:IDD_DIALOG1]
Type=1
Class=FourierDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308354
Control4=IDC_EDIT2,edit,1350631552

[CLS:FourierDlg]
Type=0
HeaderFile=FourierDlg.h
ImplementationFile=FourierDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=FourierDlg

[CLS:FourierDlg2]
Type=0
HeaderFile=FourierDlg2.h
ImplementationFile=FourierDlg2.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=FourierDlg2

