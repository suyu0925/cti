
#include "stdafx.h"
#include "XMS_FaxDemo.h"
#include "XMS_FaxDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"
#include "DJAcsDevState.h"

#include "XMS_FaxDemo_Sub.H"
#include "XMS_FaxDemo_Event.H"
#include "XMS_FaxDemo_String.H"


// Special code for CAS(SS1)
#include "..\CAS_Common_Code\CAS_Common_Cfg.h"		
CmdParamData_CAS_t g_Param_CAS;
// end of code for CAS(SS1)

// -----------------------------------------------------------------------
// variable declaration
extern CXMS_FaxDemoApp theApp;
CXMS_FaxDemoDlg	*pdlg;

// var about XMS_FaxDemo.INI
char			cfg_IniName[MAX_FILE_NAME_LEN] = "";
char			cfg_IniShortName[] = "\\XMS_FaxDemo.INI";

ServerID_t		cfg_ServerID;
char			cfg_VocPath[128];
int				cfg_iDispChnl = 32;		// always disp 32 channel

int				cfg_iPartWork;
int				cfg_iPartWorkModuleID;

char			cfg_SendFaxName[MAX_FILE_NAME_LEN];
char			cfg_RcvFaxPath[128];

int				cfg_s32DebugOn;

// var about work
ACSHandle_t		g_acsHandle = -1;
DJ_U8			g_u8UnitID = 3;

// var in XMS_FaxDemo_Event.CPP
extern TYPE_XMS_DSP_DEVICE_RES_FAXDEMO	AllDeviceRes[MAX_DSP_MODULE_NUMBER_OF_XMS];

extern int						g_iTotalPcm;
extern int						g_iTotalPcmOpened;
extern TYPE_CHANNEL_MAP_TABLE	MapTable_Pcm[MAX_PCM_NUM_IN_THIS_DEMO];

extern int						g_iTotalTrunk;
extern int						g_iTotalTrunkOpened;
extern TYPE_CHANNEL_MAP_TABLE	MapTable_Trunk[MAX_TRUNK_NUM_IN_THIS_DEMO];

extern int						g_iTotalVoice;
extern int						g_iTotalVoiceOpened;
extern int						g_iTotalVoiceFree;
extern TYPE_CHANNEL_MAP_TABLE	MapTable_Voice[MAX_TRUNK_NUM_IN_THIS_DEMO];

extern int						g_iTotalModule;
extern DJ_S8					MapTable_Module[MAX_DSP_MODULE_NUMBER_OF_XMS];

extern int						g_iTotalFax;
extern int						g_iTotalFaxOpened;
extern int						g_iTotalFaxFree;
extern TYPE_CHANNEL_MAP_TABLE	MapTable_Fax[MAX_TRUNK_NUM_IN_THIS_DEMO];

// -----------------------------------------------------------------------
// local function decalration
// -----------------------------------------------------------------------
// next functions are about Config
// -----------------------------------------------------------------------
void	WriteToConfig(void);
void	ReadFromConfig(void);
void	InitTextBox(void);
void	FetchFromText();

// -----------------------------------------------------------------------
void	InitListMain(void);
void	InitListPcm(void);
void	InitListMsg(void);
void	InitListFax(void);
void	InitListCount(void);

// -----------------------------------------------------------------------
// next functions are about Config
// -----------------------------------------------------------------------
void	ReadFromConfig(void)
{
	GetCurrentDirectory ( MAX_FILE_NAME_LEN-32, cfg_IniName );
	strcat ( cfg_IniName, cfg_IniShortName );

	GetPrivateProfileString ( "ConfigInfo", "IpAddr", "192.168.0.8", cfg_ServerID.m_s8ServerIp, sizeof(cfg_ServerID.m_s8ServerIp), cfg_IniName);

	cfg_ServerID.m_u32ServerPort = GetPrivateProfileInt ( "ConfigInfo", "Port", 9001, cfg_IniName);

	GetPrivateProfileString("ConfigInfo","UserName","",cfg_ServerID.m_s8UserName,sizeof(cfg_ServerID.m_s8UserName),cfg_IniName);
	GetPrivateProfileString("ConfigInfo","PassWord","",cfg_ServerID.m_s8UserPwd,sizeof(cfg_ServerID.m_s8UserPwd),cfg_IniName);

	GetPrivateProfileString ( "ConfigInfo", "VocPath", "c:\\DJKeygoe\\Samples\\VOC", cfg_VocPath, sizeof(cfg_VocPath), cfg_IniName);

	cfg_iPartWork = GetPrivateProfileInt ( "ConfigInfo", "PartWork", 0, cfg_IniName);

	cfg_iPartWorkModuleID = GetPrivateProfileInt ( "ConfigInfo", "PartWorkModuleID", 0, cfg_IniName);

	GetPrivateProfileString ( "ConfigInfo", "SendFaxName", "c:\\DJKeygoe\\Temp\\sendfax1.tif", cfg_SendFaxName, sizeof(cfg_SendFaxName), cfg_IniName);

	GetPrivateProfileString ( "ConfigInfo", "RcvFaxPath", "c:\\DJKeygoe\\Temp", cfg_RcvFaxPath, sizeof(cfg_RcvFaxPath), cfg_IniName);

	cfg_s32DebugOn = GetPrivateProfileInt ( "ConfigInfo", "DebugOn", 0, cfg_IniName);
}

void	WriteToConfig(void)
{
	char	TmpStr[256];

	WritePrivateProfileString ( "ConfigInfo", "IpAddr", cfg_ServerID.m_s8ServerIp, cfg_IniName);
	
	sprintf ( TmpStr, "%d", cfg_ServerID.m_u32ServerPort);
	WritePrivateProfileString ( "ConfigInfo", "Port", TmpStr, cfg_IniName);
	
	WritePrivateProfileString ( "ConfigInfo", "VocPath", cfg_VocPath, cfg_IniName);

	sprintf ( TmpStr, "%d", cfg_iPartWork);
	WritePrivateProfileString ( "ConfigInfo", "PartWork", TmpStr, cfg_IniName);

	sprintf ( TmpStr, "%d", cfg_iPartWorkModuleID);
	WritePrivateProfileString ( "ConfigInfo", "PartWorkModuleID", TmpStr, cfg_IniName);

	WritePrivateProfileString ( "ConfigInfo", "SendFaxName", cfg_SendFaxName, cfg_IniName);

	WritePrivateProfileString ( "ConfigInfo", "RcvFaxPath", cfg_RcvFaxPath, cfg_IniName);

	sprintf ( TmpStr, "%d", cfg_s32DebugOn);
	WritePrivateProfileString ( "ConfigInfo", "DebugOn", TmpStr, cfg_IniName);
}

void	InitTextBox(void)
{
	char	TmpStr[256];

	pdlg->GetDlgItem ( IDC_EDIT_IPADDR )->SetWindowText ( cfg_ServerID.m_s8ServerIp );

	sprintf ( TmpStr, "%d", cfg_ServerID.m_u32ServerPort );
	pdlg->GetDlgItem ( IDC_EDIT_IPPORT )->SetWindowText ( TmpStr );

	pdlg->GetDlgItem ( IDC_EDIT_VOCPATH )->SetWindowText ( cfg_VocPath );

	if ( cfg_iPartWork == 0 )
		((CButton *)pdlg->GetDlgItem (IDC_CHECK_PartWork))->SetCheck ( 0 ) ;
	else
		((CButton *)pdlg->GetDlgItem (IDC_CHECK_PartWork))->SetCheck ( 1 ) ;

	sprintf ( TmpStr, "%d", cfg_iPartWorkModuleID );
	pdlg->GetDlgItem ( IDC_EDIT_ModuleID )->SetWindowText ( TmpStr );

	pdlg->GetDlgItem ( IDC_EDIT_SendFaxName )->SetWindowText ( cfg_SendFaxName );

	pdlg->GetDlgItem ( IDC_EDIT_RCVFAXPATH )->SetWindowText ( cfg_RcvFaxPath );

	if ( cfg_s32DebugOn == 0 )
		((CButton *)pdlg->GetDlgItem (IDC_CHECK_DEBUG))->SetCheck ( 0 ) ;
	else
		((CButton *)pdlg->GetDlgItem (IDC_CHECK_DEBUG))->SetCheck ( 1 ) ;
}

void	FetchFromText(void)
{
	char	TmpStr[256];

	pdlg->GetDlgItem ( IDC_EDIT_IPADDR )->GetWindowText ( cfg_ServerID.m_s8ServerIp, 30 );

	pdlg->GetDlgItem ( IDC_EDIT_IPPORT )->GetWindowText ( TmpStr, 30 );
	sscanf ( TmpStr, "%d", &cfg_ServerID.m_u32ServerPort);

	pdlg->GetDlgItem ( IDC_EDIT_VOCPATH )->GetWindowText ( cfg_VocPath, 128 );

	if ( ((CButton *)pdlg->GetDlgItem (IDC_CHECK_PartWork))->GetCheck ( ) )
		cfg_iPartWork = 1;
	else
		cfg_iPartWork = 0;

	pdlg->GetDlgItem ( IDC_EDIT_ModuleID )->GetWindowText ( TmpStr, 30 );
	sscanf ( TmpStr, "%d", &cfg_iPartWorkModuleID);

	pdlg->GetDlgItem ( IDC_EDIT_SendFaxName )->GetWindowText ( cfg_SendFaxName, MAX_FILE_NAME_LEN-1 );

	pdlg->GetDlgItem ( IDC_EDIT_RCVFAXPATH )->GetWindowText ( cfg_RcvFaxPath, 128 );

	if ( ((CButton *)pdlg->GetDlgItem (IDC_CHECK_DEBUG))->GetCheck ( ) )
		cfg_s32DebugOn = 1;
	else
		cfg_s32DebugOn = 0;
}

// -----------------------------------------------------------------------
// next functions are about Display
// -----------------------------------------------------------------------
void	InitListMsg(void)
{
	int	i = pdlg->m_ListMsg.GetHorizontalExtent ( );

	pdlg->m_ListMsg.SetHorizontalExtent ( i + 1000 );

}

void AddMsg ( char *str)
{
	static	int		iTotal_ListMsg = 0;
	char		TmpStr[256];

	sprintf ( TmpStr, "%3d: ", iTotal_ListMsg+1 );
	strcat ( TmpStr, str );
	pdlg->m_ListMsg.AddString ( TmpStr );

//	pdlg->m_ListMsg.SetCurSel ( iTotal_ListMsg);
		
	iTotal_ListMsg ++;
}

// -------------------------------------------------------------------------------------------------
void	InitListMain(void)
{
	LV_COLUMN	lvc;
	DWORD dwExStyle;
	
	dwExStyle = LVS_EX_FULLROWSELECT | /*LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES |*/
						LVS_EX_HEADERDRAGDROP;// | LVS_EX_TRACKSELECT;
	pdlg->m_ListMain.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(dwExStyle));	

	lvc.mask =  LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 0;
	lvc.pszText = "ID" ;
	lvc.cx = 30;
	pdlg->m_ListMain.InsertColumn ( 0, &lvc ); 

	lvc.iSubItem = 1;
	lvc.pszText = "Mod,Ch" ;
	lvc.cx = 50;
	pdlg->m_ListMain.InsertColumn ( 1, &lvc ); 

	lvc.iSubItem = 2;
	lvc.pszText = "Type" ;
	lvc.cx = 60;
	pdlg->m_ListMain.InsertColumn ( 2, &lvc ); 

	lvc.iSubItem = 3;
	lvc.pszText = "LineState" ;
	lvc.cx = 70;
	pdlg->m_ListMain.InsertColumn ( 3, &lvc ); 

	lvc.iSubItem = 4;
	lvc.pszText = "State" ;
	lvc.cx = 70;
	pdlg->m_ListMain.InsertColumn ( 4, &lvc ); 

	lvc.iSubItem = 5;
	lvc.pszText = "Called" ;
	lvc.cx = 60;
	pdlg->m_ListMain.InsertColumn ( 5, &lvc ); 

	lvc.iSubItem = 6;
	lvc.pszText = "Calling" ;
	lvc.cx = 60;
	pdlg->m_ListMain.InsertColumn ( 6, &lvc ); 

	lvc.iSubItem = 7;
	lvc.pszText = "DTMF" ;
	lvc.cx = 40;
	pdlg->m_ListMain.InsertColumn ( 7, &lvc ); 

	lvc.iSubItem = 8;
	lvc.pszText = "VocInfo" ;
	lvc.cx = 55;
	pdlg->m_ListMain.InsertColumn ( 8, &lvc ); 

	lvc.iSubItem = 9;
	lvc.pszText = "FaxInfo" ;
	lvc.cx = 55;
	pdlg->m_ListMain.InsertColumn ( 9, &lvc ); 
}

int		CalDispRow ( int iSeqID )
{
	int	iRet;

	if ( cfg_iDispChnl == 30 )
	{
		if ( (iSeqID % 16) == 0 )
			return -1;
	
		iRet = (iSeqID / 32) * 30 + (iSeqID % 32);
		iRet --;
		if ( (iSeqID % 32) > 16 )
			iRet --;
		return iRet;

	}

	if ( cfg_iDispChnl == 31 )
	{
		if ( (iSeqID % 32) == 0 )
			return -1;

		iRet = (iSeqID / 32) * 31 + (iSeqID % 32);
		iRet --;
		return iRet;
	}

	return iSeqID;
}

void DrawMain_LineState( TRUNK_STRUCT *pOneTrunk )
{
	char StateStr[100];
	int	 iDispRow;

	iDispRow = CalDispRow(pOneTrunk->iSeqID); 
	if ( iDispRow < 0 )	return;

	// 
	GetString_LineState ( StateStr, pOneTrunk->iLineState );
	pdlg->m_ListMain.SetItemText ( iDispRow, 3, StateStr ); 
}

void DrawMain_State( TRUNK_STRUCT *pOneTrunk )
{
	char StateStr[100];
	int	 iDispRow;

	iDispRow = CalDispRow(pOneTrunk->iSeqID); 
	if ( iDispRow < 0 )	return;

	//
	switch( pOneTrunk->State ) 
	{
	case TRK_WAITOPEN:
		strcpy(StateStr,"Wait Open"); 
		break;

	case TRK_FREE:		
		strcpy(StateStr,"Free"); 
		break ;

	case TRK_SELECT:
		strcpy(StateStr,"Select");
		break;

	case TRK_FAX_SEND:
		strcpy(StateStr,"Fax Send");
		break;
	
	case TRK_FAX_RECEIVE:
		strcpy(StateStr,"Fax Rcv");
		break;
	
	case TRK_FAX_ERROR:
		strcpy(StateStr,"Fax Err");
		break;

	case TRK_WAIT_ANSWERCALL:
		strcpy(StateStr,"WaitAnswer");
		break;

	case TRK_WAIT_LINKOK:
		strcpy(StateStr,"Wait LinkOK");
		break;

	case TRK_WAIT_REMOVE:
		strcpy(StateStr,"Remove DSP");
		break;

	default:
		strcpy(StateStr,"other");
		break;
	}

	pdlg->m_ListMain.SetItemText ( iDispRow, 4, StateStr ); 
}

void DrawMain_CallInfo( TRUNK_STRUCT *pOneTrunk )
{
	char StateStr[100];
	int	 iDispRow;

	iDispRow = CalDispRow(pOneTrunk->iSeqID); 
	if ( iDispRow < 0 )	return;

	strcpy ( StateStr, pOneTrunk->CalleeCode );
	pdlg->m_ListMain.SetItemText ( iDispRow, 5, StateStr ); 

	strcpy ( StateStr, pOneTrunk->CallerCode );
	pdlg->m_ListMain.SetItemText ( iDispRow, 6, StateStr ); 
}

void DrawMain_DTMF( TRUNK_STRUCT *pOneTrunk )
{
	char StateStr[100];
	int	 iDispRow;

	iDispRow = CalDispRow(pOneTrunk->iSeqID); 
	if ( iDispRow < 0 )	return;

	strcpy(StateStr,pOneTrunk->DtmfBuf);
	pdlg->m_ListMain.SetItemText ( iDispRow, 7, StateStr ); 

}

void DrawMain_VocInfo( TRUNK_STRUCT *pOneTrunk )
{
	char StateStr[100];
	int	 iDispRow;
	DeviceID_t	*pDev;

	iDispRow = CalDispRow(pOneTrunk->iSeqID); 
	if ( iDispRow < 0 )	return;

	if ( pOneTrunk->VocDevID.m_s16DeviceMain != 0 )
	{
		pDev = &pOneTrunk->VocDevID;
		sprintf ( StateStr, "%d,%d", pDev->m_s8ModuleID, pDev->m_s16ChannelID ); 
	}
	else
		strcpy(StateStr, "");

	pdlg->m_ListMain.SetItemText ( iDispRow, 8, StateStr ); 

}

void DrawMain_FaxInfo( TRUNK_STRUCT *pOneTrunk )
{
	char StateStr[100];
	int	 iDispRow;
	DeviceID_t	*pDev;

	iDispRow = CalDispRow(pOneTrunk->iSeqID); 
	if ( iDispRow < 0 )	return;

	if ( pOneTrunk->FaxDevID.m_s16DeviceMain != 0 )
	{
		pDev = &pOneTrunk->FaxDevID;
		sprintf ( StateStr, "%d,%d", pDev->m_s8ModuleID, pDev->m_s16ChannelID ); 
	}
	else
		strcpy(StateStr, "");

	pdlg->m_ListMain.SetItemText ( iDispRow, 9, StateStr ); 

}

// -------------------------------------------------------------------------------------------------
void	InitListPcm(void)
{
	LV_COLUMN	lvc;
	DWORD dwExStyle;

	dwExStyle = LVS_EX_FULLROWSELECT | /*LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES |*/
						LVS_EX_HEADERDRAGDROP;// | LVS_EX_TRACKSELECT;
	pdlg->m_ListPcm.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(dwExStyle));	

	lvc.mask =  LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 0;
	lvc.pszText = "PcmID" ;
	lvc.cx = 60;
	pdlg->m_ListPcm.InsertColumn ( 0, &lvc ); 

	lvc.iSubItem = 1;
	lvc.pszText = "Type" ;
	lvc.cx = 80;
	pdlg->m_ListPcm.InsertColumn ( 1, &lvc ); 

	lvc.iSubItem = 2;
	lvc.pszText = "Alarm Value" ;
	lvc.cx = 80;
	pdlg->m_ListPcm.InsertColumn ( 2, &lvc ); 

	lvc.iSubItem = 3;
	lvc.pszText = "Sig Detect" ;
	lvc.cx = 80;
	pdlg->m_ListPcm.InsertColumn ( 3, &lvc ); 

	lvc.iSubItem = 4;
	lvc.pszText = "Frame Sync" ;
	lvc.cx = 80;

	pdlg->m_ListPcm.InsertColumn ( 4, &lvc ); 
	lvc.iSubItem = 5;
	lvc.pszText = "Remote Alarm" ;
	lvc.cx = 85;
	pdlg->m_ListPcm.InsertColumn ( 5, &lvc ); 
}

void DrawPcm_TypeAndAlarm ( PCM_STRUCT *pOnePcm )
{
	char StateStr[100];
	int	 iDispRow;
	int	 AlarmVal;

	iDispRow = pOnePcm->iSeqID; 

	AlarmVal = pOnePcm->s32AlarmVal;

	// E1 Type
	sprintf ( StateStr, "%s", GetString_PcmType (pOnePcm->u8E1Type) );
	pdlg->m_ListPcm.SetItemText ( iDispRow, 1, StateStr ); 

	// Alarm
	sprintf ( StateStr, "0x%X", AlarmVal );
	pdlg->m_ListPcm.SetItemText ( iDispRow, 2, StateStr ); 

	if ( AlarmVal & XMS_E1PORT_MASK_LOST_SIGNAL )
		pdlg->m_ListPcm.SetItemText ( iDispRow, 3, " X" ); 
	else
		pdlg->m_ListPcm.SetItemText ( iDispRow, 3, "O" ); 

	if ( AlarmVal & XMS_E1PORT_MASK_FAS_ALARM )
		pdlg->m_ListPcm.SetItemText ( iDispRow, 4, " X" ); 
	else
		pdlg->m_ListPcm.SetItemText ( iDispRow, 4, "O" ); 

	if ( AlarmVal & XMS_E1PORT_MASK_REMOTE_ALARM )
		pdlg->m_ListPcm.SetItemText ( iDispRow, 5, " X" ); 
	else
		pdlg->m_ListPcm.SetItemText ( iDispRow, 5, "O" ); 
	
}

// -------------------------------------------------------------------------------------------------
void	InitListFax(void)
{
	LV_COLUMN	lvc;
	DWORD dwExStyle;
	
	dwExStyle = LVS_EX_FULLROWSELECT | /*LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES |*/
						LVS_EX_HEADERDRAGDROP;// | LVS_EX_TRACKSELECT;
	pdlg->m_ListFax.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(dwExStyle));	

	lvc.mask =  LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 0;
	lvc.pszText = "ID" ;
	lvc.cx = 30;
	pdlg->m_ListFax.InsertColumn ( 0, &lvc ); 

	lvc.iSubItem = 1;
	lvc.pszText = "Mod,Ch" ;
	lvc.cx = 50;
	pdlg->m_ListFax.InsertColumn ( 1, &lvc ); 

	lvc.iSubItem = 2;
	lvc.pszText = "LineState" ;
	lvc.cx = 70;
	pdlg->m_ListFax.InsertColumn ( 2, &lvc ); 

	lvc.iSubItem = 3;
	lvc.pszText = "State" ;
	lvc.cx = 70;
	pdlg->m_ListFax.InsertColumn ( 3, &lvc ); 

	lvc.iSubItem = 4;
	lvc.pszText = "Detail Infomation" ;
	lvc.cx = 250;
	pdlg->m_ListFax.InsertColumn ( 4, &lvc ); 
}

void DrawFax_LineState( FAX_STRUCT *pOneFax )
{
	char StateStr[100];
	int	 iDispRow;

	iDispRow = pOneFax->iSeqID; 

	sprintf ( StateStr, "0x%X", pOneFax->iLineState );
	pdlg->m_ListFax.SetItemText ( iDispRow, 2, StateStr ); 
}

void DrawFax_State( FAX_STRUCT *pOneFax )
{
	char StateStr[100];
	int	 iDispRow;

	iDispRow = pOneFax->iSeqID; 

	//
	switch( pOneFax->State ) 
	{
	case FAX_WAITOPEN:
		strcpy(StateStr,"Wait Open"); 
		break;

	case FAX_FREE:		
		strcpy(StateStr,"Free"); 
		break ;

	case FAX_USED:
		strcpy(StateStr,"*Use*");
		break;

	case FAX_WAIT_REMOVE:
		strcpy(StateStr,"Remove DSP");
		break;

	default:
		strcpy(StateStr,"other");
		break;
	}

	pdlg->m_ListFax.SetItemText ( iDispRow, 3, StateStr ); 
}

void DrawFax_DetailInfo ( FAX_STRUCT *pOneFax, Acs_FaxProc_Data *pFaxData )
{
	char StateStr[100];
	int	 iDispRow;

	iDispRow = pOneFax->iSeqID; 

	if ( pFaxData == NULL )
	{
		sprintf ( StateStr, "" );
	}
	else
	{
		if ( pFaxData->m_s32AcsEvtState == 1)
		{
			sprintf ( StateStr, "Fax OK. St = %d, Err = %d, ErrStep = %d", 
				pFaxData->m_s32AcsEvtState, pFaxData->m_s32AcsEvtErrCode, pFaxData->m_u8ErrorStep );
		}
		else
		{
			sprintf ( StateStr, "Fax Error. St = %d, Err = %d, ErrStep = %d", 
				pFaxData->m_s32AcsEvtState, pFaxData->m_s32AcsEvtErrCode, pFaxData->m_u8ErrorStep );
		}
	}

	pdlg->m_ListFax.SetItemText ( iDispRow, 4, StateStr ); 
}

// -------------------------------------------------------------------------------------------------
void	InitListCount(void)
{
	LV_COLUMN	lvc;
	DWORD dwExStyle;
	
	dwExStyle = LVS_EX_FULLROWSELECT | /*LVS_EX_GRIDLINES | LVS_EX_SUBITEMIMAGES |*/
						LVS_EX_HEADERDRAGDROP;// | LVS_EX_TRACKSELECT;
	pdlg->m_ListCount.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LPARAM(dwExStyle));	

	lvc.mask =  LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 0;
	lvc.pszText = "ID" ;
	lvc.cx = 40;
	pdlg->m_ListCount.InsertColumn ( 0, &lvc ); 

	lvc.iSubItem = 1;
	lvc.pszText = "ModID" ;
	lvc.cx = 45;
	pdlg->m_ListCount.InsertColumn ( 1, &lvc ); 

	lvc.iSubItem = 2;
	lvc.pszText = "Pcm/Open" ;
	lvc.cx = 70;
	pdlg->m_ListCount.InsertColumn ( 2, &lvc ); 

	lvc.iSubItem = 3;
	lvc.pszText = "Trk/Open" ;
	lvc.cx = 70;
	pdlg->m_ListCount.InsertColumn ( 3, &lvc ); 

	lvc.iSubItem = 4;
	lvc.pszText = "Voc/Open" ;
	lvc.cx = 70;
	pdlg->m_ListCount.InsertColumn ( 4, &lvc ); 

	lvc.iSubItem = 5;
	lvc.pszText = "VocFree" ;
	lvc.cx = 55;
	pdlg->m_ListCount.InsertColumn ( 5, &lvc ); 

	lvc.iSubItem = 6;
	lvc.pszText = "Fax/Open" ;
	lvc.cx = 70;
	pdlg->m_ListCount.InsertColumn ( 6, &lvc ); 

	lvc.iSubItem = 7;
	lvc.pszText = "FaxFree" ;
	lvc.cx = 55;
	pdlg->m_ListCount.InsertColumn ( 7, &lvc ); 

	lvc.iSubItem = 8;
	lvc.pszText = "ErrFlag" ;
	lvc.cx = 60;
	pdlg->m_ListCount.InsertColumn ( 8, &lvc ); 

	lvc.iSubItem = 9;
	lvc.pszText = "RemoveState" ;
	lvc.cx = 80;
	pdlg->m_ListCount.InsertColumn ( 9, &lvc ); 
}

void	DrawCount_Pcm ( DJ_S8	s8ModID )
{
	char	TmpStr[256];
	int		iDispRow;

	iDispRow = AllDeviceRes[s8ModID].iSeqID + 1;

	sprintf ( TmpStr, "%3d /%3d", AllDeviceRes[s8ModID].lPcmNum, AllDeviceRes[s8ModID].lPcmOpened );
	pdlg->m_ListCount.SetItemText ( iDispRow, 2, TmpStr );

	// total
	iDispRow = 0;
	sprintf ( TmpStr, "%3d /%3d", g_iTotalPcm, g_iTotalPcmOpened );
	pdlg->m_ListCount.SetItemText ( iDispRow, 2, TmpStr );

}

void	DrawCount_Trunk ( DJ_S8	s8ModID )
{
	char	TmpStr[256];
	int		iDispRow;

	iDispRow = AllDeviceRes[s8ModID].iSeqID + 1;

	sprintf ( TmpStr, "%3d/%3d", AllDeviceRes[s8ModID].lTrunkNum, AllDeviceRes[s8ModID].lTrunkOpened );
	pdlg->m_ListCount.SetItemText ( iDispRow, 3, TmpStr );

	// total
	iDispRow = 0;
	sprintf ( TmpStr, "%3d/%3d", g_iTotalTrunk, g_iTotalTrunkOpened );
	pdlg->m_ListCount.SetItemText ( iDispRow, 3, TmpStr );
}

void	DrawCount_Voc ( DJ_S8	s8ModID )
{
	char	TmpStr[256];
	int		iDispRow;

	iDispRow = AllDeviceRes[s8ModID].iSeqID + 1;

	sprintf ( TmpStr, "%3d/%3d", AllDeviceRes[s8ModID].lVocNum, AllDeviceRes[s8ModID].lVocOpened );
	pdlg->m_ListCount.SetItemText ( iDispRow, 4, TmpStr );

	sprintf ( TmpStr, "%3d", AllDeviceRes[s8ModID].lVocFreeNum );
	pdlg->m_ListCount.SetItemText ( iDispRow, 5, TmpStr );

	// total
	iDispRow = 0;
	sprintf ( TmpStr, "%3d/%3d", g_iTotalVoice, g_iTotalVoiceOpened );
	pdlg->m_ListCount.SetItemText ( iDispRow, 4, TmpStr );

	sprintf ( TmpStr, "%3d", g_iTotalVoiceFree );
	pdlg->m_ListCount.SetItemText ( iDispRow, 5, TmpStr );
}

void	DrawCount_Fax ( DJ_S8	s8ModID )
{
	char	TmpStr[256];
	int		iDispRow;

	iDispRow = AllDeviceRes[s8ModID].iSeqID + 1;

	sprintf ( TmpStr, "%3d/%3d", AllDeviceRes[s8ModID].lFaxNum, AllDeviceRes[s8ModID].lFaxOpened );
	pdlg->m_ListCount.SetItemText ( iDispRow, 6, TmpStr );

	sprintf ( TmpStr, "%3d", AllDeviceRes[s8ModID].lFaxFreeNum );
	pdlg->m_ListCount.SetItemText ( iDispRow, 7, TmpStr );

	// total
	iDispRow = 0;

	sprintf ( TmpStr, "%3d/%3d", g_iTotalFax, g_iTotalFaxOpened );
	pdlg->m_ListCount.SetItemText ( iDispRow, 6, TmpStr );

	sprintf ( TmpStr, "%3d", g_iTotalFaxFree );
	pdlg->m_ListCount.SetItemText ( iDispRow, 7, TmpStr );
}

void	DrawCount_ErrFlag ( DJ_S8	s8ModID )
{
	char	TmpStr[256];
	int		iDispRow;

	iDispRow = AllDeviceRes[s8ModID].iSeqID + 1;

	if ( AllDeviceRes[s8ModID].bErrFlag )
		sprintf ( TmpStr, "T" );
	else
		sprintf ( TmpStr, "" );

	pdlg->m_ListCount.SetItemText ( iDispRow, 8, TmpStr );
}

void	DrawCount_RemoveState ( DJ_S8	s8ModID )
{
	char	TmpStr[256];
	int		iDispRow;

	iDispRow = AllDeviceRes[s8ModID].iSeqID + 1;

	switch ( AllDeviceRes[s8ModID].RemoveState )
	{
	case DSP_REMOVE_STATE_NONE:
		sprintf ( TmpStr, "" );
		break;
	case DSP_REMOVE_STATE_START:
		sprintf ( TmpStr, "Start" );
		break;
	case DSP_REMOVE_STATE_READY:
		sprintf ( TmpStr, "Ready" );
		break;
	}

	pdlg->m_ListCount.SetItemText ( iDispRow, 9, TmpStr );
}

// -------------------------------------------------------------------------------------------------
void	ReDrawAll (void)
{
	char	TmpStr[256];
	int		i, iDispRow;
	TRUNK_STRUCT	*pOneTrunk;
	FAX_STRUCT		*pOneFax;

	// m_ListMain
	pdlg->m_ListMain.DeleteAllItems ();
	for ( i = 0; i < g_iTotalTrunk; i ++ )
	{
		iDispRow = CalDispRow ( i ); 
		if ( iDispRow < 0 )	continue;

		// Fix content
		sprintf ( TmpStr, "%3d", iDispRow );
		pdlg->m_ListMain.InsertItem ( iDispRow, TmpStr );

		sprintf ( TmpStr, "%d,%d", MapTable_Trunk[i].m_s8ModuleID, MapTable_Trunk[i].m_s16ChannelID );
		pdlg->m_ListMain.SetItemText ( iDispRow, 1, TmpStr );

		pOneTrunk = &M_OneTrunk(MapTable_Trunk[i]);
		pdlg->m_ListMain.SetItemText ( iDispRow, 2, GetString_DeviceSub( pOneTrunk->deviceID.m_s16DeviceSub) );

		// Changed content
		DrawMain_LineState ( pOneTrunk );
		DrawMain_State ( pOneTrunk );
		DrawMain_CallInfo ( pOneTrunk );
		DrawMain_DTMF ( pOneTrunk );
	}

	// m_ListPcm
	pdlg->m_ListPcm.DeleteAllItems ();
	for ( i = 0; i < g_iTotalPcm; i ++ )
	{
		sprintf ( TmpStr, "%3d", i );
		pdlg->m_ListPcm.InsertItem ( i, TmpStr );

		// Changed content
		DrawPcm_TypeAndAlarm ( &M_OnePcm(MapTable_Pcm[i]) );
	}

	// m_ListFax
	pdlg->m_ListFax.DeleteAllItems ();
	for ( i = 0; i < g_iTotalFax; i ++ )
	{
		// Fix content
		sprintf ( TmpStr, "%3d", i );
		pdlg->m_ListFax.InsertItem ( i, TmpStr );

		sprintf ( TmpStr, "%d,%d", MapTable_Fax[i].m_s8ModuleID, MapTable_Fax[i].m_s16ChannelID );
		pdlg->m_ListFax.SetItemText ( i, 1, TmpStr );

		pOneFax = &M_OneFax(MapTable_Fax[i]);
		// Changed content
		DrawFax_LineState ( pOneFax );
		DrawFax_State ( pOneFax );
	}

	// m_ListCount
	pdlg->m_ListCount.DeleteAllItems ();
	// Insert Row
	pdlg->m_ListCount.InsertItem ( 0, "Total" );
	for ( i = 0; i < g_iTotalModule; i ++ )
	{
		sprintf ( TmpStr, "%3d", i );
		pdlg->m_ListCount.InsertItem ( i+1, TmpStr );

		sprintf ( TmpStr, "%3d", MapTable_Module[i] );
		pdlg->m_ListCount.SetItemText ( i+1, 1, TmpStr );
	}

	// Display Content
	for ( i = 0; i < g_iTotalModule; i ++ )
	{
		DrawCount_Pcm ( MapTable_Module[i] );
		DrawCount_Trunk ( MapTable_Module[i] );
		DrawCount_Voc ( MapTable_Module[i] );
		DrawCount_Fax ( MapTable_Module[i] );
		DrawCount_ErrFlag ( MapTable_Module[i] );
		DrawCount_RemoveState ( MapTable_Module[i] );
	}
}

// -----------------------------------------------------------------------
// next functions are about Init & Exit
// -----------------------------------------------------------------------
bool	InitSystem()
{
	RetCode_t	r;
	char		MsgStr[160];

	pdlg = (CXMS_FaxDemoDlg	*)theApp.m_pMainWnd;

	// Read From "XMS_FaxDemo.INI"
	ReadFromConfig();

	// Special code for CAS(SS1)
	// Read From "C:\\DJKeygoe\\Samples\\CAS_Common_Code\\SaXMS_CAS_Cfg.INI"
	if ( CAS_Common_Cfg_ReadCfg ( &g_Param_CAS ) != 0 )
	{
		sprintf ( MsgStr, "CAS_Common_Cfg_ReadCfg \"C:\\DJKeygoe\\Samples\\CAS_Common_Code\\XMS_CAS_Cfg.INI\" Error!" );
		MessageBox(NULL, MsgStr, "Init System", MB_OK ) ;
	}
	// end of code for CAS(SS1)

	// Init m_ListMain
	InitListMain();

	// Init m_ListPcm
	InitListPcm();

	// Init m_ListMsg
	InitListMsg();

	// Init m_ListFax
	InitListFax();

	// Init m_ListCount
	InitListCount();

	// Init Conifg's text box
	InitTextBox();

	// now open ACS Server
	/* Call acsOpenStream() to connect with ACS Server */
	r = XMS_acsOpenStream ( &g_acsHandle, 
						&cfg_ServerID,
						g_u8UnitID,		// App Unit ID 
						32,				// sendQSize, in K Bytes
						32,				// recvQSize, in K Bytes
						cfg_s32DebugOn,	// Debug On/Off
						NULL);

	if ( r < 0 )
	{
		sprintf ( MsgStr, "XMS_acsOpenStream(IP Addr : %s, port : %d) FAIL. ret = %d", 
			cfg_ServerID.m_s8ServerIp, cfg_ServerID.m_u32ServerPort, r );

		MessageBox(NULL, MsgStr, "Init System", MB_OK ) ;
		AddMsg ( MsgStr );
		return false;
	}
	else
	{
		sprintf ( MsgStr, "XMS_acsOpenStream(%s,%d) OK!", cfg_ServerID.m_s8ServerIp, cfg_ServerID.m_u32ServerPort );
		AddMsg ( MsgStr );
	}

	r = XMS_acsSetESR ( g_acsHandle, (EsrFunc)EvtHandler, 0, 1 );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "XMS_acsSetESR() FAIL! ret = %d", r );
		AddMsg ( MsgStr );
		return false;
	}
	else
	{
		sprintf ( MsgStr, "XMS_acsSetESR() OK!" );
		AddMsg ( MsgStr );
	}

	InitAllDeviceRes ();

	XMS_acsGetDeviceList ( g_acsHandle, NULL );

	return true;
}

void	ExitSystem() 
{
	RetCode_t	r;
	int			i;

	// close all device
	for ( i = 0; i < g_iTotalModule; i ++ )
	{
		CloseAllDevice_Dsp ( MapTable_Module[i] );
	}

	r = XMS_acsCloseStream ( g_acsHandle, NULL );

	FreeAllDeviceRes ();

	// save to "XMS_FaxDemo.INI"
	FetchFromText();
	WriteToConfig();

}

// -----------------------------------------------------------------------
// next functions are about Open & Close
// -----------------------------------------------------------------------
void	OpenTrunkDevice ( TRUNK_STRUCT *pOneTrunk )
{
	RetCode_t	r;
	
	if ( pOneTrunk->State == TRK_WAITOPEN )		// not Open yet
	{
		r = XMS_ctsOpenDevice ( g_acsHandle, &pOneTrunk->deviceID, NULL );
		if ( r < 0 )
		{
			AddMsg ( "XMS_ctsOpenDevice Fail in OpenTrunkDevice()!" );
		}
	}
}

void	OpenVoiceDevice ( VOICE_STRUCT *pOneVoice )
{
	RetCode_t	r;
	
	if ( pOneVoice->State == VOC_WAITOPEN )		// not Open yet
	{
		r = XMS_ctsOpenDevice ( g_acsHandle, &pOneVoice->deviceID, NULL );
		if ( r < 0 )
		{
			AddMsg ( "XMS_ctsOpenDevice Fail in OpenVoiceDevice()!" );
		}
	}
}

void	OpenPcmDevice ( PCM_STRUCT *pOnePcm )
{
	RetCode_t	r;
	
	if ( pOnePcm->bOpenFlag == false )		// not Open yet
	{
		r = XMS_ctsOpenDevice ( g_acsHandle, &pOnePcm->deviceID, NULL );
		if ( r < 0 )
		{
			AddMsg ( "XMS_ctsOpenDevice Fail in OpenPcmDevice()!" );
		}
	}
}

void	OpenFaxDevice ( FAX_STRUCT *pOneFax )
{
	RetCode_t	r;
	
	if ( pOneFax->State == FAX_WAITOPEN )		// not Open yet
	{
		r = XMS_ctsOpenDevice ( g_acsHandle, &pOneFax->deviceID, NULL );
		if ( r < 0 )
		{
			AddMsg ( "XMS_ctsOpenDevice Fail in OpenFaxDevice()!" );
		}
	}
}

void	OpenBoardDevice ( DJ_S8 s8DspModID )
{
	RetCode_t	r;

	if ( AllDeviceRes[s8DspModID].bOpenFlag == false )	// not Open yet
	{
		r = XMS_ctsOpenDevice ( g_acsHandle, &AllDeviceRes[s8DspModID].deviceID, NULL );

		if ( r < 0 )
		{
			AddMsg ( "XMS_ctsOpenDevice Fail in OpenBoardDevice()!" );
		}
	}
}

void	OpenAllDevice_Dsp ( DJ_S8 s8DspModID )
{
	int			 i;

	AllDeviceRes[s8DspModID].bErrFlag = false;
	DrawCount_ErrFlag (s8DspModID);
	AllDeviceRes[s8DspModID].RemoveState = DSP_REMOVE_STATE_NONE;
	DrawCount_RemoveState (s8DspModID);

	// Open Board
	OpenBoardDevice ( s8DspModID );

	// pTrunk
	for ( i = 0; i < AllDeviceRes[s8DspModID].lTrunkNum; i++ )
	{
		OpenTrunkDevice ( &AllDeviceRes[s8DspModID].pTrunk[i] );
	}

	// pVoice
	for ( i = 0; i < AllDeviceRes[s8DspModID].lVocNum; i++ )
	{
		OpenVoiceDevice ( &AllDeviceRes[s8DspModID].pVoice[i] );
	}

	// pPcm
	for ( i = 0; i < AllDeviceRes[s8DspModID].lPcmNum; i++ )
	{
		OpenPcmDevice ( &AllDeviceRes[s8DspModID].pPcm[i] );
	}

	// pFax
	for ( i = 0; i < AllDeviceRes[s8DspModID].lFaxNum; i++ )
	{
		OpenFaxDevice ( &AllDeviceRes[s8DspModID].pFax[i] );
	}
}

void	ReOpen_AllDevice (void)
{
	int		i;

	for ( i = 0; i < g_iTotalModule; i ++ )
	{
		OpenAllDevice_Dsp ( MapTable_Module[i] );
	}
}

// --------------------------------------------------------------------------------
void	OpenDeviceOK ( DeviceID_t *pDevice )
{
	TRUNK_STRUCT	*pOneTrunk;

	if ( pDevice->m_s16DeviceMain == XMS_DEVMAIN_BOARD )
	{
		AllDeviceRes[pDevice->m_s8ModuleID].deviceID.m_CallID = pDevice->m_CallID;		// this line is very important, must before all operation
		AllDeviceRes[pDevice->m_s8ModuleID].bOpenFlag = true;
	}

	if ( pDevice->m_s16DeviceMain == XMS_DEVMAIN_INTERFACE_CH )
	{
		pOneTrunk = &M_OneTrunk(*pDevice);

		pOneTrunk->deviceID.m_CallID = pDevice->m_CallID;		// this line is very important, must before all operation

		// init this Device: Trunk
		InitTrunkChannel ( pOneTrunk );

		XMS_ctsResetDevice ( g_acsHandle, pDevice, NULL );
		XMS_ctsGetDevState ( g_acsHandle, pDevice, NULL );

		// modify the count
		g_iTotalTrunkOpened ++;
		AllDeviceRes[pDevice->m_s8ModuleID].lTrunkOpened ++;

		DrawCount_Trunk ( pDevice->m_s8ModuleID  );
	}

	if ( pDevice->m_s16DeviceMain == XMS_DEVMAIN_VOICE )
	{
		M_OneVoice(*pDevice).deviceID.m_CallID = pDevice->m_CallID;		// this is very important

		// init this Device: Voice
		Change_Voc_State ( &M_OneVoice(*pDevice), VOC_FREE);

		XMS_ctsResetDevice ( g_acsHandle, pDevice, NULL );
		XMS_ctsGetDevState ( g_acsHandle, pDevice, NULL );

		// modify the count
		g_iTotalVoiceOpened ++;
		g_iTotalVoiceFree ++;
		AllDeviceRes[pDevice->m_s8ModuleID].lVocOpened ++;
		AllDeviceRes[pDevice->m_s8ModuleID].lVocFreeNum ++;

		DrawCount_Voc ( pDevice->m_s8ModuleID );
	}

	if ( pDevice->m_s16DeviceMain == XMS_DEVMAIN_DIGITAL_PORT )
	{
		M_OnePcm(*pDevice).deviceID.m_CallID = pDevice->m_CallID;		// this is very important
		M_OnePcm(*pDevice).bOpenFlag = true;

		// init the Device: Pcm
		XMS_ctsResetDevice ( g_acsHandle, pDevice, NULL );
		XMS_ctsGetDevState ( g_acsHandle, pDevice, NULL );
		DrawPcm_TypeAndAlarm ( &M_OnePcm(*pDevice) );

		// moidfy the count
		g_iTotalPcmOpened ++;
		AllDeviceRes[pDevice->m_s8ModuleID].lPcmOpened ++;

		DrawCount_Pcm  ( pDevice->m_s8ModuleID );
	}

	if ( pDevice->m_s16DeviceMain == XMS_DEVMAIN_FAX )
	{
		M_OneFax(*pDevice).deviceID.m_CallID = pDevice->m_CallID;		// this is very important

		// init the Device: Fax
		XMS_ctsResetDevice ( g_acsHandle, pDevice, NULL );
		XMS_ctsGetDevState ( g_acsHandle, pDevice, NULL );
		
		Change_Fax_State ( &M_OneFax(*pDevice), FAX_FREE);

		// modify the Count

		g_iTotalFaxOpened ++;
		g_iTotalFaxFree ++;
		AllDeviceRes[pDevice->m_s8ModuleID].lFaxOpened ++;
		AllDeviceRes[pDevice->m_s8ModuleID].lFaxFreeNum ++;

		DrawCount_Fax ( pDevice->m_s8ModuleID );
	}

}

// --------------------------------------------------------------------------------
void	CloseDeviceOK ( DeviceID_t *pDevice )
{
	TRUNK_STRUCT	*pOneTrunk;

	AllDeviceRes[pDevice->m_s8ModuleID].bErrFlag = true;
	DrawCount_ErrFlag (pDevice->m_s8ModuleID);

	if ( pDevice->m_s16DeviceMain == XMS_DEVMAIN_BOARD )
	{
		AllDeviceRes[pDevice->m_s8ModuleID].bOpenFlag = false;
	}

	if ( pDevice->m_s16DeviceMain == XMS_DEVMAIN_INTERFACE_CH )
	{
		pOneTrunk = &M_OneTrunk(*pDevice);

		Change_State ( pOneTrunk, TRK_WAITOPEN );

		// modify the count
		g_iTotalTrunkOpened --;
		AllDeviceRes[pDevice->m_s8ModuleID].lTrunkOpened --;

		DrawCount_Trunk ( pDevice->m_s8ModuleID  );
	}

	if ( pDevice->m_s16DeviceMain == XMS_DEVMAIN_VOICE )
	{
		// init this Device: Voice
		Change_Voc_State ( &M_OneVoice(*pDevice), VOC_WAITOPEN);

		// modify the count
		g_iTotalVoiceOpened --;
		g_iTotalVoiceFree --;
		AllDeviceRes[pDevice->m_s8ModuleID].lVocOpened --;
		AllDeviceRes[pDevice->m_s8ModuleID].lVocFreeNum --;

		DrawCount_Voc ( pDevice->m_s8ModuleID );
	}

	if ( pDevice->m_s16DeviceMain == XMS_DEVMAIN_DIGITAL_PORT )
	{
		M_OnePcm(*pDevice).bOpenFlag = false;

		// moidfy the count
		g_iTotalPcmOpened --;
		AllDeviceRes[pDevice->m_s8ModuleID].lPcmOpened --;

		DrawCount_Pcm  ( pDevice->m_s8ModuleID );
	}

	if ( pDevice->m_s16DeviceMain == XMS_DEVMAIN_FAX )
	{
		Change_Fax_State ( &M_OneFax(*pDevice), FAX_WAITOPEN );

		// modify the Count
		g_iTotalFaxOpened --;
		g_iTotalFaxFree --;
		AllDeviceRes[pDevice->m_s8ModuleID].lFaxOpened --;
		AllDeviceRes[pDevice->m_s8ModuleID].lFaxFreeNum --;

		DrawCount_Fax ( pDevice->m_s8ModuleID );
	}

}

// --------------------------------------------------------------------------------
void	CloseTrunkDevice ( TRUNK_STRUCT *pOneTrunk )
{
	RetCode_t	r;
	
	pOneTrunk->State= TRK_WAITOPEN;

	r = XMS_ctsCloseDevice ( g_acsHandle, &pOneTrunk->deviceID, NULL );
	if ( r < 0 )
	{
		AddMsg ( "XMS_ctsCloseDevice Fail in CloseTrunkDevice()!" );
	}
}

void	CloseVoiceDevice ( VOICE_STRUCT *pOneVoice )
{
	RetCode_t	r;
	
	r = XMS_ctsCloseDevice ( g_acsHandle, &pOneVoice->deviceID, NULL );
	if ( r < 0 )
	{
		AddMsg ( "XMS_ctsCloseDevice Fail in CloseVoiceDevice()!" );
	}
}

void	ClosePcmDevice ( PCM_STRUCT *pOnePcm )
{
	RetCode_t	r;
	
	r = XMS_ctsCloseDevice ( g_acsHandle, &pOnePcm->deviceID, NULL );
	if ( r < 0 )
	{
		AddMsg ( "XMS_ctsCloseDevice Fail in ClosePcmDevice()!" );
	}
}

void	CloseFaxDevice ( FAX_STRUCT *pOneFax )
{
	RetCode_t	r;
	
	r = XMS_ctsCloseDevice ( g_acsHandle, &pOneFax->deviceID, NULL );
	if ( r < 0 )
	{
		AddMsg ( "XMS_ctsCloseDevice Fail in CloseFaxDevice()!" );
	}
}

void	CloseBoardDevice ( DeviceID_t *pBoardDevID )
{
	RetCode_t	r;

	r = XMS_ctsCloseDevice ( g_acsHandle, pBoardDevID, NULL );

	if ( r < 0 )
	{
		AddMsg ( "XMS_ctsCloseDevice Fail in CloseBoardDevice()!" );
	}
}

void	CloseAllDevice_Dsp ( DJ_S8 s8DspModID )
{
	int			 i;

	// close Board
	CloseBoardDevice ( &AllDeviceRes[s8DspModID].deviceID );

	// pTrunk
	for ( i = 0; i < AllDeviceRes[s8DspModID].lTrunkNum; i++ )
	{
		CloseTrunkDevice ( &AllDeviceRes[s8DspModID].pTrunk[i] );
	}

	// pVoice
	for ( i = 0; i < AllDeviceRes[s8DspModID].lVocNum; i++ )
	{
		CloseVoiceDevice ( &AllDeviceRes[s8DspModID].pVoice[i] );
	}

	// pPcm
	for ( i = 0; i < AllDeviceRes[s8DspModID].lPcmNum; i++ )
	{
		ClosePcmDevice ( &AllDeviceRes[s8DspModID].pPcm[i] );
	}

	// pFax
	for ( i = 0; i < AllDeviceRes[s8DspModID].lFaxNum; i++ )
	{
		CloseFaxDevice ( &AllDeviceRes[s8DspModID].pFax[i] );
	}
}

// -----------------------------------------------------------------------
// next functions are about Real Work
// -----------------------------------------------------------------------
void	HandleDevState ( Acs_Evt_t *pAcsEvt )
{
	Acs_GeneralProc_Data *pGeneralData = NULL;

	pGeneralData = (Acs_GeneralProc_Data *)FetchEventData(pAcsEvt);
	if ( pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_INTERFACE_CH )
	{
		M_OneTrunk(pAcsEvt->m_DeviceID).iLineState = pGeneralData->m_s32DeviceState;
		DrawMain_LineState( &M_OneTrunk(pAcsEvt->m_DeviceID) );
	}

	if ( pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_DIGITAL_PORT )
	{
		M_OnePcm(pAcsEvt->m_DeviceID).u8E1Type = (pGeneralData->m_s32DeviceState >> 16) & 0xFF;
		M_OnePcm(pAcsEvt->m_DeviceID).s32AlarmVal = (pGeneralData->m_s32DeviceState & 0xFFFF);

		DrawPcm_TypeAndAlarm ( &M_OnePcm(pAcsEvt->m_DeviceID) );
	}

	if ( pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_FAX )
	{
		M_OneFax(pAcsEvt->m_DeviceID).iLineState = pGeneralData->m_s32DeviceState;
		DrawFax_LineState( &M_OneFax(pAcsEvt->m_DeviceID) );
	}

}

// -------------------------------------------------------------------------------------------------
void	CheckRemoveReady ( DJ_S8 s8DspModID )
{
	int			i;

	// check device : INTERFACE_CH
	for ( i = 0; i < AllDeviceRes[s8DspModID].lTrunkNum; i ++ )
	{
		if ( (AllDeviceRes[s8DspModID].pTrunk[i].State != TRK_WAITOPEN)
			&& (AllDeviceRes[s8DspModID].pTrunk[i].State != TRK_WAIT_REMOVE) )
		{
			return;
		}
	}

	// check device : VOICE
	for ( i = 0; i < AllDeviceRes[s8DspModID].lVocNum; i ++ )
	{
		if ( (AllDeviceRes[s8DspModID].pVoice[i].State != VOC_WAITOPEN)
			&& (AllDeviceRes[s8DspModID].pVoice[i].State != VOC_WAIT_REMOVE) )
		{
			return;
		}
	}

	// check device : FAX
	for ( i = 0; i < AllDeviceRes[s8DspModID].lFaxNum; i ++ )
	{
		if ( (AllDeviceRes[s8DspModID].pFax[i].State != FAX_WAITOPEN)
			&& (AllDeviceRes[s8DspModID].pFax[i].State != FAX_WAIT_REMOVE) )
		{
			return;
		}
	}

	// all device in this DSP is ready for remove 
	AllDeviceRes[s8DspModID].RemoveState = DSP_REMOVE_STATE_READY;
	DrawCount_RemoveState ( s8DspModID );
}

void	Remove_OneDsp(void)
{
	POSITION	pos;
	int			index, i;
	DJ_S8		s8DspModID;

	pos = pdlg->m_ListCount.GetFirstSelectedItemPosition();
	
	index = pdlg->m_ListCount.GetNextSelectedItem ( pos);
	if ( ( index <= 0 ) || ( index > g_iTotalModule ) )
	{
		AfxMessageBox ( "Please select a valid DSP module in the upper list!" );
		return;
	}

	s8DspModID = MapTable_Module[index-1];		// because the first Row is Total, so minus 1
	AllDeviceRes[s8DspModID].RemoveState = DSP_REMOVE_STATE_START;
	DrawCount_RemoveState ( s8DspModID );

	// handle device : INTERFACE_CH
	for ( i = 0; i < AllDeviceRes[s8DspModID].lTrunkNum; i ++ )
	{
		if ( AllDeviceRes[s8DspModID].pTrunk[i].State == TRK_FREE )
			Change_State ( &AllDeviceRes[s8DspModID].pTrunk[i], TRK_WAIT_REMOVE );
	}

	// handle device : VOICE
	for ( i = 0; i < AllDeviceRes[s8DspModID].lVocNum; i ++ )
	{
		if ( AllDeviceRes[s8DspModID].pVoice[i].State == VOC_FREE )
		{
			Change_Voc_State ( &AllDeviceRes[s8DspModID].pVoice[i], VOC_WAIT_REMOVE);
		}
	}

	// handle device : FAX
	for ( i = 0; i < AllDeviceRes[s8DspModID].lFaxNum; i ++ )
	{
		if ( AllDeviceRes[s8DspModID].pFax[i].State == FAX_FREE )
		{
			Change_Fax_State ( &AllDeviceRes[s8DspModID].pFax[i], FAX_WAIT_REMOVE);
		}
	}

	// check if all device is WAIT_OPEN or WAIT_REMOVE
	CheckRemoveReady ( s8DspModID );
}

// --------------------------------------------------------------------------------
/* Stop Play */
DJ_S32 StopPlayFile ( DeviceID_t	*pVocDevID )
{
	RetCode_t		r;
	ControlPlay_t	controlPlay;

	controlPlay.m_u16ControlType = XMS_STOP_PLAY;

	r = XMS_ctsControlPlay ( g_acsHandle, pVocDevID, &controlPlay, NULL );

	return r;
}

/* Handle Play */
DJ_S32	 PlayFile ( DeviceID_t	*pVocDevID, DJ_S8 *s8FileName, DJ_U8 u8PlayTag, bool bIsQueue )
{	
	DJ_U32          i = 0;	
	PlayProperty_t	playProperty;
	RetCode_t		r;

	memset(&playProperty,0,sizeof(playProperty));		
	
	if ( bIsQueue )
		playProperty.m_u16PlayType = XMS_PLAY_TYPE_FILE_QUEUE;	
	else
		playProperty.m_u16PlayType = XMS_PLAY_TYPE_FILE;	

	playProperty.m_u8TaskID = u8PlayTag;

	strcpy ( playProperty.m_s8PlayContent, s8FileName );
	
	r = XMS_ctsPlay ( g_acsHandle, pVocDevID, &playProperty, NULL );

	return r;
}

bool	CheckPlayEnd ( TRUNK_STRUCT *pOneTrunk, Acs_Evt_t *pAcsEvt )
{
	Acs_MediaProc_Data	*pMediaData = NULL;

	if ( pAcsEvt->m_s32EventType == XMS_EVT_PLAY )	
	{
		pMediaData = (Acs_MediaProc_Data *) FetchEventData(pAcsEvt);
		if ( pMediaData->m_u8TaskID == pOneTrunk->u8PlayTag )
			return true;
	}

	return false;
}

void My_InitDtmfBuf ( TRUNK_STRUCT *pOneTrunk )
{
	pOneTrunk->DtmfCount = 0;
	pOneTrunk->DtmfBuf[0] = 0; 
}

void My_AddDtmfBuf ( TRUNK_STRUCT *pOneTrunk, char TmpDtmf )
{
	if ( pOneTrunk->DtmfCount < (32-1) )
	{
		pOneTrunk->DtmfBuf[pOneTrunk->DtmfCount] = TmpDtmf; 
		pOneTrunk->DtmfBuf[pOneTrunk->DtmfCount+1] = 0; 
		pOneTrunk->DtmfCount ++;
	}
}

char My_GetDtmfCode ( Acs_Evt_t *pAcsEvt )
{
	Acs_IO_Data				*pIOData = NULL;
	char		*p;

	if ( pAcsEvt->m_s32EventType == XMS_EVT_RECVIODATA )	/*IO Data*/
	{
		pIOData = (Acs_IO_Data *)FetchEventData(pAcsEvt);

		if ( ( pIOData->m_u16IoType == XMS_IO_TYPE_DTMF ) 
			&& ( pIOData->m_u16IoDataLen > 0 ) )
		{
			p = (char *)FetchIOData(pAcsEvt);

			return *p;
		}
	}

	return -1;	// not a good DTMF
}

char My_GetGtdCode ( Acs_Evt_t *pAcsEvt )
{
	Acs_IO_Data				*pIOData = NULL;
	char   sbuffer[200];
	char		*p;

	memset(sbuffer,0,sizeof(sbuffer));
	if ( pAcsEvt->m_s32EventType == XMS_EVT_RECVIODATA )	/*IO Data Event*/
	{
		pIOData = (Acs_IO_Data *)FetchEventData(pAcsEvt);

		if ( ( pIOData->m_u16IoType== XMS_IO_TYPE_GTG ) 
			&& ( pIOData->m_u16IoDataLen > 0 ) )
		{
			p = (char *)FetchIOData(pAcsEvt);
			sprintf(sbuffer,"[%s]",p);
			AddMsg(sbuffer);

			return *p;
		}
	}

	return -1;	// not a good GTD
}

void SetGtD_AnalogTrunk(DeviceID_t* pDevId)
{
	//========Set GTG Begin========
	CmdParamData_Voice_t cmdVoc;
	memset(&cmdVoc,0,sizeof(cmdVoc));
	cmdVoc.m_u8GtdCtrlValid = 1 ;						//Enable GTD
	cmdVoc.m_VocGtdControl.m_u8ChannelEnable = 1;		//Enable Gtd channel
	cmdVoc.m_VocGtdControl.m_u8DTMFEnable = 1;			// Detect DTMF
	cmdVoc.m_VocGtdControl.m_u8GTDEnable = 1;			// Detect GTD 
	cmdVoc.m_VocGtdControl.m_u8FSKEnable = 1;			// Detect FSK for receive CallerID

	//cmdVoc.m_VocGtdControl.m_u8EXTEnable = 0x2;		// Enable PVD Detect

	strcpy((char*)&cmdVoc.m_VocGtdControl.m_u8GTDID[0],"GHIJK");	// Detect Busy Tone

	DJ_U16 u16ParamType = VOC_PARAM_UNIPARAM;
	DJ_U16 u16ParamSize = sizeof(cmdVoc);
	void* p = (void*) &cmdVoc;

	int r = XMS_ctsSetParam( g_acsHandle,pDevId,u16ParamType,u16ParamSize,(void*)p);

	//========Set GTG End  ========
}


void	My_DualLink ( DeviceID_t *pDev1, DeviceID_t *pDev2 )
{
	XMS_ctsLinkDevice ( g_acsHandle, pDev1, pDev2, NULL ); 
	XMS_ctsLinkDevice ( g_acsHandle, pDev2, pDev1, NULL ); 
}

void	My_DualUnlink ( DeviceID_t *pDev1, DeviceID_t *pDev2 )
{
	XMS_ctsUnlinkDevice ( g_acsHandle, pDev1, pDev2, NULL ); 
	XMS_ctsUnlinkDevice ( g_acsHandle, pDev2, pDev1, NULL ); 
}

int		SearchOneFreeVoice (  DeviceID_t *pFreeVocDeviceID, SEARCH_RULE SearchRule, DJ_S8 s8RefModID )
{
	int				i;
	static	int		iLoopStart = 0;
	VOICE_STRUCT	*pOneVoice;
	DJ_S8			s8SearchModID;
	long			lNowMaxFreeNum;

	if ( SearchRule == SEARCH_RULE_SAME_MODULE )			// Search in Same Module
	{
		s8SearchModID = s8RefModID;
	}
	else		// Search in Max free resource module
	{
		s8SearchModID = -1;
		lNowMaxFreeNum = -1;
		for ( i = 0; i < g_iTotalModule; i ++ )
		{
			if ( AllDeviceRes[MapTable_Module[i]].lVocFreeNum > lNowMaxFreeNum )
			{
				s8SearchModID = MapTable_Module[i];
				lNowMaxFreeNum = AllDeviceRes[MapTable_Module[i]].lVocFreeNum;
			}
		}
	}

	for ( i = 0; i < AllDeviceRes[s8SearchModID].lVocNum; i ++ )
	{
		pOneVoice = &AllDeviceRes[s8SearchModID].pVoice[i];
		if ( pOneVoice->State == VOC_FREE )
		{
			*pFreeVocDeviceID = pOneVoice->deviceID;

			// Õ¼ÓÃ¸Ãvoice device 
			Change_Voc_State ( &AllDeviceRes[s8SearchModID].pVoice[i], VOC_USED);
			AllDeviceRes[s8SearchModID].lVocFreeNum--;
			g_iTotalVoiceFree --;
			DrawCount_Voc ( s8SearchModID );
			return i;
		}
	}

	return -1;
}

int		FreeOneVoice (  DeviceID_t *pFreeVocDeviceID )
{
	DJ_S8	s8ModID;

	s8ModID = pFreeVocDeviceID->m_s8ModuleID;
	if ( AllDeviceRes[s8ModID].lFlag == 1 )
	{
		Change_Voc_State ( &M_OneVoice(*pFreeVocDeviceID), VOC_FREE);

		AllDeviceRes[s8ModID].lVocFreeNum++;
		g_iTotalVoiceFree ++;
		DrawCount_Voc ( s8ModID );
		return	0;		// OK
	}

	return -1;			// invalid VocDeviceID
}

int		SearchOneFreeFax ( DeviceID_t *pFreeFaxDeviceID )
{
	int				i;
	static	int		iLoopStart = 0;
	FAX_STRUCT		*pOneFax;
	DJ_S8			s8SearchModID;
	long			lNowMaxFreeNum;

	// Search in Max free resource module
	{
		s8SearchModID = -1;
		lNowMaxFreeNum = -1;
		for ( i = 0; i < g_iTotalModule; i ++ )
		{
			if ( AllDeviceRes[MapTable_Module[i]].lFaxFreeNum > lNowMaxFreeNum )
			{
				s8SearchModID = MapTable_Module[i];
				lNowMaxFreeNum = AllDeviceRes[MapTable_Module[i]].lFaxFreeNum;
			}
		}
	}

	for ( i = 0; i < AllDeviceRes[s8SearchModID].lFaxNum; i ++ )
	{
		pOneFax = &AllDeviceRes[s8SearchModID].pFax[i];
		if ( pOneFax->State == FAX_FREE )
		{
			*pFreeFaxDeviceID = pOneFax->deviceID;

			// use this fax device 
			Change_Fax_State ( pOneFax, FAX_USED);

			AllDeviceRes[s8SearchModID].lFaxFreeNum--;
			g_iTotalFaxFree --;

			DrawCount_Fax ( s8SearchModID );
			return i;
		}
	}

	return -1;
}

int		FreeOneFax (  DeviceID_t *pFreeFaxDeviceID )
{
	DJ_S8	s8ModID;

	s8ModID = pFreeFaxDeviceID->m_s8ModuleID;
	if ( AllDeviceRes[s8ModID].lFlag == 1 )
	{
		Change_Fax_State ( &M_OneFax(*pFreeFaxDeviceID), FAX_FREE);

		AllDeviceRes[s8ModID].lFaxFreeNum++;
		g_iTotalFaxFree ++;

		DrawCount_Fax ( s8ModID );
		return	0;		// OK
	}

	return -1;			// invalid VocDeviceID
}

void	Change_Voc_State ( VOICE_STRUCT *pOneVoice, VOICE_STATE NewState )
{
	pOneVoice->State = NewState;

	// Check if ready to remove DSP hardware
	if ( (AllDeviceRes[pOneVoice->deviceID.m_s8ModuleID].RemoveState == DSP_REMOVE_STATE_START)
		&& (NewState == VOC_FREE) )
	{
		pOneVoice->State = VOC_WAIT_REMOVE;

		CheckRemoveReady ( pOneVoice->deviceID.m_s8ModuleID );
	}
}

void	Change_Fax_State ( FAX_STRUCT *pOneFax, FAX_STATE NewState )
{
	pOneFax->State = NewState;
	DrawFax_State( pOneFax );

	// Check if ready to remove DSP hardware
	if ( (AllDeviceRes[pOneFax->deviceID.m_s8ModuleID].RemoveState == DSP_REMOVE_STATE_START)
		&& (NewState == FAX_FREE) )
	{
		pOneFax->State = FAX_WAIT_REMOVE;
		DrawFax_State( pOneFax );

		CheckRemoveReady ( pOneFax->deviceID.m_s8ModuleID );
	}
}

void	Change_State ( TRUNK_STRUCT *pOneTrunk, TRUNK_STATE NewState )
{
	pOneTrunk->State = NewState;

	DrawMain_State ( pOneTrunk );

	// Check if ready to remove DSP hardware
	if ( (AllDeviceRes[pOneTrunk->deviceID.m_s8ModuleID].RemoveState == DSP_REMOVE_STATE_START)
		&& (NewState == TRK_FREE) )
	{
		pOneTrunk->State = TRK_WAIT_REMOVE;

		DrawMain_State ( pOneTrunk );

		CheckRemoveReady ( pOneTrunk->deviceID.m_s8ModuleID );
	}
}

void	InitTrunkChannel ( TRUNK_STRUCT *pOneTrunk )
{
	Change_State ( pOneTrunk, TRK_FREE );

	pOneTrunk->CallerCode[0]=0;
	pOneTrunk->CalleeCode[0]=0;

	My_InitDtmfBuf ( pOneTrunk );
	DrawMain_DTMF ( pOneTrunk );

	memset ( &pOneTrunk->VocDevID, 0, sizeof(DeviceID_t) );		// 0: didn't alloc Device
	DrawMain_VocInfo ( pOneTrunk );

	memset ( &pOneTrunk->FaxDevID, 0, sizeof(DeviceID_t) );		// 0: didn't alloc Device
	DrawMain_FaxInfo ( pOneTrunk );
}

void ResetTrunk ( TRUNK_STRUCT *pOneTrunk, Acs_Evt_t *pAcsEvt )
{
	StopPlayFile ( &pOneTrunk->VocDevID );

	// free the used Voice Resource
	if ( pOneTrunk->VocDevID.m_s16DeviceMain != 0 )
	{
		My_DualUnlink ( &pOneTrunk->deviceID, &pOneTrunk->VocDevID );
		FreeOneVoice ( &pOneTrunk->VocDevID );

		memset ( &M_OneVoice(pOneTrunk->VocDevID).UsedDevID,	0, sizeof(DeviceID_t) );		// 0: didn't alloc Voc Device 
		memset ( &pOneTrunk->VocDevID, 0, sizeof(DeviceID_t) );		// 0: didn't alloc Device
		DrawMain_VocInfo ( pOneTrunk );
	}

	// free the used Fax Resource
	if ( pOneTrunk->FaxDevID.m_s16DeviceMain != 0 )
	{
		// stop send or receive fax
		if ( pOneTrunk->State == TRK_FAX_SEND )
		{
			XMS_ctsStopSendFax ( g_acsHandle, &pOneTrunk->FaxDevID, NULL );
		}
		else if ( pOneTrunk->State == TRK_FAX_RECEIVE )
		{
			XMS_ctsStopReceiveFax ( g_acsHandle, &pOneTrunk->FaxDevID, NULL );
		}

		// free the fax device
		FreeOneFax ( &pOneTrunk->FaxDevID );

		memset ( &M_OneFax(pOneTrunk->FaxDevID).UsedDevID, 0, sizeof(DeviceID_t) );		// 0: didn't alloc Device
		memset ( &pOneTrunk->FaxDevID, 0, sizeof(DeviceID_t) );		// 0: didn't alloc Device
		DrawMain_FaxInfo ( pOneTrunk );
	}

	InitTrunkChannel ( pOneTrunk );
}

// Special code for CAS(SS1)
void	SpecialForCas ( TRUNK_STRUCT *pOneTrunk, Acs_Evt_t *pAcsEvt )
{
	DeviceID_t				FreeVocDeviceID;

	if ( pOneTrunk->deviceID.m_s16DeviceSub != XMS_DEVSUB_E1_CAS )
		return;

	if ( pAcsEvt->m_s32EventType == XMS_EVT_CAS_MFC_START )	/* start receive MFC, need a Voice Device */
	{
		if ( SearchOneFreeVoice ( &FreeVocDeviceID, SEARCH_RULE_MAX_FREE_FIST, 0 ) >= 0 )
		{
			// add next line from V2.2.0, link by Application Program
			My_DualLink ( &FreeVocDeviceID, &pOneTrunk->deviceID );

			pOneTrunk->VocDevID = FreeVocDeviceID;
			M_OneVoice(FreeVocDeviceID).UsedDevID = pOneTrunk->deviceID; 
			DrawMain_VocInfo ( pOneTrunk );

			g_Param_CAS.m_VocDevID = FreeVocDeviceID;
			XMS_ctsSetParam ( g_acsHandle, &pOneTrunk->deviceID, 
				CAS_PARAM_UNIPARAM, sizeof(CmdParamData_CAS_t), (DJ_Void *)&g_Param_CAS );
		}
	}

	if ( pAcsEvt->m_s32EventType == XMS_EVT_CAS_MFC_END )	/* receive MFC end, release Voice Device */
	{
		// add next line from V2.2.0, unlink by Application Program
		My_DualUnlink(&pOneTrunk->VocDevID,&pOneTrunk->deviceID );		

		FreeOneVoice (  &pOneTrunk->VocDevID );

		memset ( &M_OneVoice(pOneTrunk->VocDevID).UsedDevID,	0, sizeof(DeviceID_t) );		// 0: didn't alloc Device 
		memset ( &pOneTrunk->VocDevID, 0, sizeof(DeviceID_t) );		// 0: didn't alloc Voc Device
		DrawMain_VocInfo ( pOneTrunk );
	}
}
// end of code for CAS(SS1)

void TrunkWork ( TRUNK_STRUCT *pOneTrunk, Acs_Evt_t *pAcsEvt )
{
	Acs_CallControl_Data *	pCallControl = NULL;
	Acs_FaxProc_Data	 *  pFaxData = NULL;
	DeviceID_t				FreeVocDeviceID, FreeVocDeviceID_ForFax;
	DeviceID_t				FreeFaxDeviceID;
	char					FileName[256], MsgStr[256];
	char					TmpDtmf, TmpGtd;
	RetCode_t				r;

	if ( pAcsEvt->m_s32EventType == XMS_EVT_CLEARCALL )	/*Clear Call*/
	{
		if ( (pOneTrunk->State != TRK_FREE) && (pOneTrunk->State != TRK_WAIT_REMOVE) )
		{
			ResetTrunk ( pOneTrunk, pAcsEvt );
			return ; 
		}
	}

	if ( pOneTrunk->deviceID.m_s16DeviceSub == XMS_DEVSUB_ANALOG_TRUNK )
	{
		TmpGtd = My_GetGtdCode ( pAcsEvt );
		if ( TmpGtd  != -1 ) 
		{
			if ( TmpGtd == 'I' || TmpGtd == 'J' || TmpGtd == 'K' )	// Busy Tone
			{
				XMS_ctsResetDevice(g_acsHandle,&pOneTrunk->deviceID,NULL);
				XMS_ctsClearCall(g_acsHandle,&pOneTrunk->deviceID,0,NULL);
				ResetTrunk(pOneTrunk,pAcsEvt);
			}
		}
	}

	switch(pOneTrunk->State)
	{
	case TRK_FREE:
		// Special code for CAS(SS1)
		SpecialForCas(pOneTrunk,pAcsEvt);

		if ( pAcsEvt->m_s32EventType == XMS_EVT_CALLIN )	/*Call In*/
		{
			pCallControl = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);

			XMS_ctsAlertCall ( g_acsHandle, &pOneTrunk->deviceID, NULL );

			XMS_ctsAnswerCallIn ( g_acsHandle, &pOneTrunk->deviceID, NULL );

			sprintf ( pOneTrunk->CalleeCode, pCallControl->m_s8CalledNum );
			sprintf ( pOneTrunk->CallerCode, pCallControl->m_s8CallingNum );
			DrawMain_CallInfo( pOneTrunk );
			
			Change_State ( pOneTrunk, TRK_WAIT_ANSWERCALL );
		}
		break;

	case TRK_WAIT_ANSWERCALL:
		// Special code for CAS(SS1)
		SpecialForCas(pOneTrunk,pAcsEvt);

		if ( pAcsEvt->m_s32EventType == XMS_EVT_ANSWERCALL )	/*Answer Call In End Event*/
		{
			pCallControl = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);

			if ( SearchOneFreeVoice ( &FreeVocDeviceID, SEARCH_RULE_MAX_FREE_FIST, 0 ) >= 0 )
			{
				pOneTrunk->u8PlayTag = 16;

				pOneTrunk->VocDevID = FreeVocDeviceID;
				M_OneVoice(FreeVocDeviceID).UsedDevID = pOneTrunk->deviceID; 

				DrawMain_VocInfo ( pOneTrunk );

				My_DualLink ( &pOneTrunk->deviceID, &FreeVocDeviceID );
				
				if ( pOneTrunk->deviceID.m_s16DeviceSub == XMS_DEVSUB_ANALOG_TRUNK )
				{
					SetGtD_AnalogTrunk(&FreeVocDeviceID);		// prepare for get Busy Tone
				}

				Change_State ( pOneTrunk, TRK_WAIT_LINKOK );
			}
		}
		break;

	case TRK_WAIT_LINKOK:
		if ( pAcsEvt->m_s32EventType == XMS_EVT_LINKDEVICE )	/*LinkDevice OK*/
		{
			strcpy ( FileName, cfg_VocPath );
			strcat ( FileName, "\\FaxMsg.001");
			pOneTrunk->u8PlayTag ++;
			PlayFile ( &pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag );

			Change_State ( pOneTrunk, TRK_SELECT );
		}
		break;

	case TRK_SELECT:
		// if play end
			// do nothing

		TmpDtmf = My_GetDtmfCode ( pAcsEvt );
		if ( TmpDtmf == -1 )								/*DTMF*/
			break;

		My_AddDtmfBuf ( pOneTrunk, TmpDtmf );
		DrawMain_DTMF ( pOneTrunk );

		StopPlayFile ( &pOneTrunk->VocDevID );

		if ( (TmpDtmf == '1')  || (TmpDtmf == '2') )
		{
			if ( SearchOneFreeFax ( &FreeFaxDeviceID ) >= 0 )
			{
				DrawFax_DetailInfo ( &M_OneFax(FreeFaxDeviceID), NULL );

				if ( ( SearchOneFreeVoice ( &FreeVocDeviceID_ForFax, SEARCH_RULE_SAME_MODULE, FreeFaxDeviceID.m_s8ModuleID ) ) >= 0 )
				{
					// draw the fax
					DrawFax_State ( &M_OneFax(FreeFaxDeviceID) );

					// free the original Voc Device
					My_DualUnlink ( &pOneTrunk->deviceID, &pOneTrunk->VocDevID );
					FreeOneVoice ( &pOneTrunk->VocDevID );

					memset ( &M_OneVoice(pOneTrunk->VocDevID).UsedDevID,	0, sizeof(DeviceID_t) );		// 0: didn't alloc Device
					memset ( &pOneTrunk->VocDevID, 0, sizeof(DeviceID_t) );		// 0: didn't alloc Device
					DrawMain_VocInfo ( pOneTrunk );

					// remember now Voc & Fax Device
					pOneTrunk->VocDevID = FreeVocDeviceID_ForFax;
					M_OneVoice(FreeVocDeviceID_ForFax).UsedDevID = pOneTrunk->deviceID; 
					pOneTrunk->FaxDevID = FreeFaxDeviceID;
					M_OneFax(FreeFaxDeviceID).UsedDevID = pOneTrunk->deviceID; 

					My_DualLink ( &pOneTrunk->deviceID, &pOneTrunk->VocDevID );
					DrawMain_VocInfo ( pOneTrunk );
					DrawMain_FaxInfo ( pOneTrunk );

					if ( TmpDtmf == '1' )	 // "1" for keygoe is SendFax
					{
						r = XMS_ctsSendFax ( g_acsHandle, 
										&FreeFaxDeviceID,
										&FreeVocDeviceID_ForFax,
									cfg_SendFaxName, "DJ83636988", NULL );
						if ( r < 0 )
						{
							sprintf ( MsgStr, "XMS_ctsSendFax ( %s ) Fail!", cfg_SendFaxName );
							AddMsg ( MsgStr );
						}

						Change_State ( pOneTrunk, TRK_FAX_SEND );
						break;
					}
					else					// "1" for keygoe is RcvFax
					{
						sprintf ( FileName, "%s\\XMS_FaxDemo_%03d.tif", cfg_RcvFaxPath, pOneTrunk->iSeqID );
						r = XMS_ctsReceiveFax ( g_acsHandle, 
										&FreeFaxDeviceID,
										&FreeVocDeviceID_ForFax,
									FileName, "DJ83636988", NULL );
						if ( r < 0 )
						{
							sprintf ( MsgStr, "XMS_ctsReceiveFax ( %s ) Fail!", FileName );
							AddMsg ( MsgStr );
						}

						Change_State ( pOneTrunk, TRK_FAX_RECEIVE );
						break;
					}
				}
				else
				{
					FreeOneFax ( &FreeFaxDeviceID );
				}

				Change_State ( pOneTrunk, TRK_FAX_ERROR );
			}
			break;
		}
		break;


	case TRK_FAX_SEND:
		if ( pAcsEvt->m_s32EventType == XMS_EVT_SENDFAX )	/* Send Fax OK*/
		{
			pFaxData = (Acs_FaxProc_Data *)FetchEventData(pAcsEvt);

			DrawFax_DetailInfo ( &M_OneFax(pOneTrunk->FaxDevID), pFaxData );
			XMS_ctsClearCall ( g_acsHandle, &pOneTrunk->deviceID, 0, NULL );
		}
		break;

	case TRK_FAX_RECEIVE:
		if ( pAcsEvt->m_s32EventType == XMS_EVT_RECVFAX )	/* Receive Fax OK*/
		{
			pFaxData = (Acs_FaxProc_Data *)FetchEventData(pAcsEvt);

			DrawFax_DetailInfo ( &M_OneFax(pOneTrunk->FaxDevID), pFaxData );
			XMS_ctsClearCall ( g_acsHandle, &pOneTrunk->deviceID, 0, NULL );
		}
		break;

	case TRK_FAX_ERROR:
		break;

	}
}

