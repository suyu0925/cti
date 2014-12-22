# Microsoft Developer Studio Project File - Name="XMSApi_Test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=XMSApi_Test - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "XMSApi_Test.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XMSApi_Test.mak" CFG="XMSApi_Test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XMSApi_Test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "XMSApi_Test - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XMSApi_Test - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "C:\DJKeygoe\inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy                       release\*.exe                       .                      	copy                       release\*.exe                       .\b\ 
# End Special Build Tool

!ELSEIF  "$(CFG)" == "XMSApi_Test - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "C:\DJKeygoe\inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy                               .\debug\XMSApi_Test.EXE                               .
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "XMSApi_Test - Win32 Release"
# Name "XMSApi_Test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\3gppConfgDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ARecVoltageSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\BoardSetMainClockDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\CAS_Common_Code\CAS_Common_Cfg.CPP
# End Source File
# Begin Source File

SOURCE=.\CLKDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfParaSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CSPPlayCtrlDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CSPPlayDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CSPRecCtrlDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CtxAppData.cpp
# End Source File
# Begin Source File

SOURCE=.\CtxLinkDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CtxRegDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DevTimerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Dialog3GFaxTone.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogActiveMemSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogAnalogUser.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogAnaTrunk.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogAtrunkEM.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogAtrunkFlash.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogFaxHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogFlashSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogFskSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogGTD.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogGTDSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogGTGSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogSVDSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBoardCommonParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBoardVadMinLevelParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCmdParamDataCAS.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFaxBpsParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFaxMultiFileParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMediaExInput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMediaExOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMediaExParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgParamType.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRtpxAddr.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRtpxInput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRtpxMixer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRtpxOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSetVoIPParams.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSS7SS7RawFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUserReadXmsBoardInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DSS1CallParamDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\FaxECMDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LedDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ModRelateDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RecCSPDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RecModModeSetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SendSignalData.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\txLinkCtxDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\XMS_Test_ParamVoIP.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_3GPP_BuildIndex.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_3GPPControlRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_3GPPPlaySet.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_BuildIndex.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_ConfParam.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Control3GPPPlay.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_ControlPlay.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_ControlRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_ParamCAS.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_PlaySet.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Record3GPPSet.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_RecordSet.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_SendIOData.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Test.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Test.rc
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Test_Event.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Test_Func.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Test_ParamVoice.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Test_String.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Test_Sub.cpp
# End Source File
# Begin Source File

SOURCE=.\XMSApi_TestDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\Lib\DJAcsAPI.lib
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\3gppConfgDlg.h
# End Source File
# Begin Source File

SOURCE=.\ARecVoltageSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\BoardSetMainClockDlg.h
# End Source File
# Begin Source File

SOURCE=..\CAS_Common_Code\CAS_Common_Cfg.H
# End Source File
# Begin Source File

SOURCE=.\CLKDialog.h
# End Source File
# Begin Source File

SOURCE=.\ConfParaSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\CSPPlayCtrlDlg.h
# End Source File
# Begin Source File

SOURCE=.\CSPPlayDlg.h
# End Source File
# Begin Source File

SOURCE=.\CSPRecCtrlDlg.h
# End Source File
# Begin Source File

SOURCE=.\CtxAppData.h
# End Source File
# Begin Source File

SOURCE=.\CtxLinkDlg.h
# End Source File
# Begin Source File

SOURCE=.\CtxRegDlg.h
# End Source File
# Begin Source File

SOURCE=.\DevTimerDlg.h
# End Source File
# Begin Source File

SOURCE=.\Dialog3GFaxTone.h
# End Source File
# Begin Source File

SOURCE=.\DialogActiveMemSet.h
# End Source File
# Begin Source File

SOURCE=.\DialogAnalogUser.h
# End Source File
# Begin Source File

SOURCE=.\DialogAnaTrunk.h
# End Source File
# Begin Source File

SOURCE=.\DialogAtrunkEM.h
# End Source File
# Begin Source File

SOURCE=.\DialogAtrunkFlash.h
# End Source File
# Begin Source File

SOURCE=.\DialogFaxHeader.h
# End Source File
# Begin Source File

SOURCE=.\DialogFlashSet.h
# End Source File
# Begin Source File

SOURCE=.\DialogFskSet.h
# End Source File
# Begin Source File

SOURCE=.\DialogGTD.h
# End Source File
# Begin Source File

SOURCE=.\DialogGTDSet.h
# End Source File
# Begin Source File

SOURCE=.\DialogGTGSet.h
# End Source File
# Begin Source File

SOURCE=.\DialogSVDSet.h
# End Source File
# Begin Source File

SOURCE=.\DlgBoardCommonParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgBoardVadMinLevelParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgCmdParamDataCAS.h
# End Source File
# Begin Source File

SOURCE=.\DlgFaxBpsParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgFaxMultiFileParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgMediaExInput.h
# End Source File
# Begin Source File

SOURCE=.\DlgMediaExOutput.h
# End Source File
# Begin Source File

SOURCE=.\DlgMediaExParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgParamType.h
# End Source File
# Begin Source File

SOURCE=.\DlgRtpxAddr.h
# End Source File
# Begin Source File

SOURCE=.\DlgRtpxAddr.h
# End Source File
# Begin Source File

SOURCE=.\DlgRtpxInput.h
# End Source File
# Begin Source File

SOURCE=.\DlgRtpxMixer.h
# End Source File
# Begin Source File

SOURCE=.\DlgRtpxOutput.h
# End Source File
# Begin Source File

SOURCE=.\DlgSetVoIPParams.h
# End Source File
# Begin Source File

SOURCE=.\DlgSS7SS7RawFrame.h
# End Source File
# Begin Source File

SOURCE=.\DlgUserReadXmsBoardInfo.h
# End Source File
# Begin Source File

SOURCE=.\DSS1CallParamDlg.h
# End Source File
# Begin Source File

SOURCE=.\FaxECMDlg.h
# End Source File
# Begin Source File

SOURCE=.\LedDlg.h
# End Source File
# Begin Source File

SOURCE=.\ModRelateDlg.h
# End Source File
# Begin Source File

SOURCE=.\RecCSPDlg.h
# End Source File
# Begin Source File

SOURCE=.\RecModModeSetDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SendSignalData.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\txLinkCtxDlg.h
# End Source File
# Begin Source File

SOURCE=.\XMS_Test_ParamVoIP.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_3GPP_BuildIndex.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_3GPPControlRecord.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_3GPPPlaySet.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_BuildIndex.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_ConfParam.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Control3GPPPlay.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_ControlPlay.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_ControlRecord.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_ParamCAS.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_PlaySet.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Record3GPPSet.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_RecordSet.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_SendIOData.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Test.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Test_Event.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Test_Func.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Test_ParamVoice.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Test_String.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_Test_Sub.h
# End Source File
# Begin Source File

SOURCE=.\XMSApi_TestDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\XMSApi_Test.ico
# End Source File
# Begin Source File

SOURCE=.\res\XMSApi_Test.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
