; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSPDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "sp.h"
LastPage=0

ClassCount=19
Class1=CDlgAddr
Class2=CDlgIODataUII
Class3=CDlgLinkDev
Class4=CDlgMediaExInput
Class5=CDlgMediaExOutput
Class6=CDlgMixer
Class7=CDlgNum
Class8=CDlgParamType
Class9=CDlgRtpxParam
Class10=CDlgVoipParam
Class11=CSPApp
Class12=CAboutDlg
Class13=CSPDlg
Class14=VoipParam

ResourceCount=12
Resource1=IDD_SP_DIALOG (English (U.S.))
Resource2=IDD_DLG_RECORD
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDD_DIALOG_RTPX
Resource5=IDD_DLG_PLAY
Resource6=IDD_DLG_LINKDEV
Resource7=IDD_DLG_PARAMTYPE
Resource8=IDD_DLG_MIXER
Resource9=IDD_DLG_ADDR
Class15=CDlgSipCallParam
Class16=CDlgMediaExType
Class17=CDlgMediaExPlay
Class18=CDlgPlay
Resource10=IDD_DLG_SIP_CALLOUT
Class19=CDlgRecord
Resource11=IDD_DLG_IODATA_UII
Resource12=IDR_MENU_MAIN

[CLS:CDlgAddr]
Type=0
BaseClass=CDialog
HeaderFile=DlgAddr.h
ImplementationFile=DlgAddr.cpp

[CLS:CDlgIODataUII]
Type=0
BaseClass=CDialog
HeaderFile=DlgIODataUII.h
ImplementationFile=DlgIODataUII.cpp

[CLS:CDlgLinkDev]
Type=0
BaseClass=CDialog
HeaderFile=DlgLinkDev.h
ImplementationFile=DlgLinkDev.cpp
Filter=D
VirtualFilter=dWC
LastObject=CDlgLinkDev

[CLS:CDlgMediaExInput]
Type=0
BaseClass=CDialog
HeaderFile=DlgMediaExInput.h
ImplementationFile=DlgMediaExInput.cpp

[CLS:CDlgMediaExOutput]
Type=0
BaseClass=CDialog
HeaderFile=DlgMediaExOutput.h
ImplementationFile=DlgMediaExOutput.cpp

[CLS:CDlgMixer]
Type=0
BaseClass=CDialog
HeaderFile=DlgMixer.h
ImplementationFile=DlgMixer.cpp

[CLS:CDlgNum]
Type=0
BaseClass=CDialog
HeaderFile=DlgNum.h
ImplementationFile=DlgNum.cpp

[CLS:CDlgParamType]
Type=0
BaseClass=CDialog
HeaderFile=DlgParamType.h
ImplementationFile=DlgParamType.cpp

[CLS:CDlgRtpxParam]
Type=0
BaseClass=CDialog
HeaderFile=DlgRtpxParam.h
ImplementationFile=DlgRtpxParam.cpp
Filter=D
VirtualFilter=dWC
LastObject=CDlgRtpxParam

[CLS:CDlgVoipParam]
Type=0
BaseClass=CDialog
HeaderFile=DlgVoipParam.h
ImplementationFile=DlgVoipParam.cpp

[CLS:CSPApp]
Type=0
BaseClass=CWinApp
HeaderFile=SP.h
ImplementationFile=SP.cpp
LastObject=CSPApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=SPDlg.cpp
ImplementationFile=SPDlg.cpp
LastObject=CAboutDlg

[CLS:CSPDlg]
Type=0
BaseClass=CDialog
HeaderFile=SPDlg.h
ImplementationFile=SPDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST_MSG

[CLS:VoipParam]
Type=0
BaseClass=CDialog
HeaderFile=VoipParam.h
ImplementationFile=VoipParam.cpp

[DLG:IDD_DLG_ADDR]
Type=1
Class=CDlgAddr
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_IPADDRESS1,SysIPAddress32,1342242816
Control4=IDC_EDIT_PORT,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDD_DLG_IODATA_UII]
Type=1
Class=CDlgIODataUII
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDC_RADIO_SIGNAL,button,1342308361
Control3=IDC_RADIO_ALPHANUMERIC,button,1342242825
Control4=IDC_EDIT_SIGNAL,edit,1350631552
Control5=IDC_EDIT_ALPHANUMERIC,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDCANCEL,button,1342242816

[DLG:IDD_DLG_LINKDEV]
Type=1
Class=CDlgLinkDev
ControlCount=12
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_CMB_DESTTYPE,combobox,1344340227
Control4=IDC_EDIT_DESTID,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_UNIT,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_OVERLAYFILE,edit,1350631552
Control12=IDC_BUTTON_OPENFILE,button,1342242816

[DLG:IDD_DLG_MIXER]
Type=1
Class=CDlgMixer
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_CHK_AUDIO,button,1342242819
Control3=IDC_CHK_VIDEO,button,1342242819
Control4=IDC_CMB_SRCCTRL,combobox,1344340227
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_SRCID,edit,1350631552
Control7=IDOK,button,1342242816
Control8=IDCANCEL,button,1342242816
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_SRC2ID,edit,1350631552
Control12=IDC_CMB_SRC2CTRL,combobox,1344340227

[DLG:IDD_DLG_PARAMTYPE]
Type=1
Class=CDlgParamType
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COB_PARAMTYPE,combobox,1344340227

[DLG:IDD_DIALOG_RTPX]
Type=1
Class=CDlgRtpxParam
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CHK_ENABLE,button,1342242819
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_CMB_DATATYPE,combobox,1344340227
Control7=IDC_EDIT_PAYLOAD,edit,1350631552
Control8=IDC_CHK_TRANSCODE,button,1342242819

[DLG:IDD_DLG_VOIPPARAM]
Type=1
Class=CDlgVoipParam

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_SP_DIALOG]
Type=1
Class=CSPDlg

[DLG:IDD_DLG_VOIP_PARAM]
Type=1
Class=VoipParam

[DLG:IDD_DLG_SIP_CALLOUT]
Type=1
Class=CDlgSipCallParam
ControlCount=16
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_CALLER_NAME,edit,1350631552
Control4=IDC_EDIT_CALLER_ID,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_CALLEE_NAME,edit,1350631552
Control8=IDC_EDIT_CALLEE_ID,edit,1350631552
Control9=IDC_EDIT_CALLER_PORT,edit,1350631552
Control10=IDC_EDIT_CALLER_ADDR,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT_CALLEE_ADDR,edit,1350631552
Control14=IDC_EDIT_CALLEE_PORT,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SP_DIALOG (English (U.S.))]
Type=1
Class=?
ControlCount=26
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_MSG,listbox,1353781507
Control4=IDC_LIST_DEV_INFO,SysListView32,1350631425
Control5=IDC_STATIC,static,1342308352
Control6=IDC_LIST_DEV_TYPE,SysListView32,1350631425
Control7=IDC_STATIC_DEVINFO,static,1342308352
Control8=IDC_BUTTON_OPENALL,button,1342242816
Control9=IDC_BUTTON_CLOSEALL,button,1342242816
Control10=IDC_BUTTON_SETPARAM,button,1342242816
Control11=IDC_BUTTON_CLEARCALL,button,1342242816
Control12=IDC_BUTTON_IODATA,button,1342242816
Control13=IDC_BUTTON_CALL,button,1342242816
Control14=IDC_BUTTON_PLAY,button,1342242816
Control15=IDC_BUTTON_RECORD,button,1342242816
Control16=IDC_BUTTON_STOP,button,1342242816
Control17=IDC_BUTTON_LINK,button,1342242816
Control18=IDC_BUTTON_UNLINK,button,1342242816
Control19=IDC_BUTTON_RESET,button,1342242816
Control20=IDC_LIST_HOTCONF,SysListView32,1350631425
Control21=IDC_LIST_MEMBER,SysListView32,1350631425
Control22=IDC_STATIC_MEMBER,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_BUTTON_INIT,button,1342242816
Control25=IDC_BUTTON_STOPREC,button,1342242816
Control26=IDC_BUTTON_GETFILEINFO,button,1342242816

[CLS:CDlgSipCallParam]
Type=0
HeaderFile=DlgSipCallParam.h
ImplementationFile=DlgSipCallParam.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CDlgSipCallParam

[CLS:CDlgMediaExType]
Type=0
HeaderFile=DlgMediaExType.h
ImplementationFile=DlgMediaExType.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgMediaExType
VirtualFilter=dWC

[CLS:CDlgMediaExPlay]
Type=0
HeaderFile=DlgMediaExPlay.h
ImplementationFile=DlgMediaExPlay.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgMediaExPlay
VirtualFilter=dWC

[DLG:IDD_DLG_PLAY]
Type=1
Class=CDlgPlay
ControlCount=21
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CMB_TYPE,combobox,1344340227
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_X,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_Y,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_FPS,edit,1350631552
Control12=IDC_EDIT_BR,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_TIME,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_FILE,edit,1350631552
Control17=IDC_BUTTON_FILE,button,1342242816
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EDIT_FILEOVERLAY,edit,1350631552
Control20=IDC_BUTTON_FILEOVERLAY,button,1342242816
Control21=IDC_CHK_LOOP,button,1342242819

[CLS:CDlgPlay]
Type=0
HeaderFile=DlgPlay.h
ImplementationFile=DlgPlay.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHK_LOOP
VirtualFilter=dWC

[DLG:IDD_DLG_RECORD]
Type=1
Class=CDlgRecord
ControlCount=15
Control1=IDOK,button,1342242816
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_X,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_Y,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_FPS,edit,1350631552
Control10=IDC_EDIT_BR,edit,1350631552
Control11=IDC_CMB_TYPE,combobox,1344340227
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_FILE,edit,1350631552
Control15=IDC_BUTTON_FILE,button,1342242816

[CLS:CDlgRecord]
Type=0
HeaderFile=DlgRecord.h
ImplementationFile=DlgRecord.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgRecord
VirtualFilter=dWC

[MNU:IDR_MENU_MAIN]
Type=1
Class=?
Command1=IDR_MENU_MAIN_JOIN
Command2=IDR_MENU_MAIN_LEAVE
Command3=IDR_MENU_MAIN_PLAY
Command4=IDR_MENU_MAIN_RECORD
Command5=IDR_MENU_MAIN_CLEAR
Command6=IDR_MENU_MAIN_RESTART
Command7=IDR_MENU_MAIN_GETLAYOUT
Command8=IDR_MENU_MAIN_SETLAYOUT
Command9=IDR_MENU_MAIN_GETVISIBLELIST
Command10=IDR_MENU_MAIN_SETVISIBLELIST
Command11=IDR_MENU_MAIN_STARTTIMER
Command12=IDR_MENU_MAIN_STOPTIMER
CommandCount=12

