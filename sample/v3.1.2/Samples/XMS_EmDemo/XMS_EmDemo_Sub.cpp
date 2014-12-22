#include "stdafx.h"
#include "XMS_EmDemo.h"
#include "XMS_EmDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"
#include "DJAcsDevState.h"

#include "XMS_EmDemo_Sub.H"
#include "XMS_EmDemo_Event.H"
#include "XMS_EmDemo_String.H"

// Special code for CAS(SS1)
#include "..\CAS_Common_Code\CAS_Common_Cfg.h"		
CmdParamData_CAS_t g_Param_CAS;
// end of code for CAS(SS1)

// Special code for Analog
#include "..\Analog_Common_Code\Analog_Common_Code.h"		
TYPE_ANALOG_GTD_PARAM g_Param_Analog;

void	SetGTD_ToneParam ( DeviceID_t *pDevice );
// end of code for Analog


// -----------------------------------------------------------------------
// variable declaration
extern CXMS_EmDemoApp theApp;
CXMS_EmDemoDlg	*pdlg;

// var about XMS_EmDemo.INI
char			cfg_IniName[MAX_FILE_NAME_LEN] = "";
char			cfg_IniShortName[] = "\\XMS_EmDemo.INI";

ServerID_t		cfg_ServerID;
char			cfg_VocPath[128];
int				cfg_iDispChnl;
int				cfg_iVoiceRule;

int				cfg_iPartWork;
int				cfg_iPartWorkModuleID;

int				cfg_s32DebugOn;

// var about work
ACSHandle_t		g_acsHandle = -1;
DJ_U8			g_u8UnitID = 2;

// var in XMS_EmDemo_Event.CPP
extern TYPE_XMS_DSP_DEVICE_RES_DEMO	AllDeviceRes[MAX_DSP_MODULE_NUMBER_OF_XMS];

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

// -----------------------------------------------------------------------
// local function decalration
void	WriteToConfig(void);
void	ReadFromConfig(void);
void	InitTextBox(void);
void	FetchFromText();

void	InitListMain(void);
void	InitListPcm(void);
void	InitListMsg(void);

void	My_DualLink ( DeviceID_t *pDev1, DeviceID_t *pDev2 );
void	My_DualUnlink ( DeviceID_t *pDev1, DeviceID_t *pDev2 );
void	SetGtD_AnalogTrunk(DeviceID_t* pDevId);
// -----------------------------------------------------------------------
typedef  struct 
{
	DJ_U8                   m_u8EM_DSPID;        //the dsp of EM channel
	DJ_U8                   m_u8EMVOC_DSPID;     //the dsp of EM VOC channel
	DJ_U8                   m_U8Ref[2];
	DJ_U16                  m_u16EM_CH;          //EM channel ID
	DJ_U16                  m_u16EM_VOC_CH;      //EM VOC channel ID
}ChInfo;

typedef struct
{
	DJ_U8                   m_u8IsUsed;          //is used flag
	DJ_U8                   m_u8Ref;             //reserve
	DJ_U16                  m_u16SeqID;          //the sequnce ID of this struct for a EM&VOC channal	
	ChInfo                  m_stE1Info;           //the channel info of linking with E1
	ChInfo                  m_stEMInfo;			 //the channel info of linking with MInfo
}MT_EM_CH;

typedef struct
{
	DJ_U16                  m_u16EMCount;        //the count of the EM channel including EM channel and VOC channel
	DJ_U16                  m_u16Ref;

	MT_EM_CH              * m_pstMtEmCH;
}MT_EM_INFO;

MT_EM_INFO                  g_stEMInfo;
#define  MAX_APPNAME_LEN    30

////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool     ComChInfo( ChInfo *pstDstInfo, ChInfo *pstSrcInfo )
{
	if ( pstDstInfo->m_u16EM_CH == pstSrcInfo->m_u16EM_CH
	  && pstDstInfo->m_u16EM_VOC_CH == pstSrcInfo->m_u16EM_VOC_CH 
	  && pstDstInfo->m_u8EM_DSPID == pstSrcInfo->m_u8EM_DSPID
	  && pstDstInfo->m_u8EMVOC_DSPID == pstSrcInfo->m_u8EMVOC_DSPID )
		return true;
	else
		return false;
}	

int     GetMtEmCH( MT_EM_CH * m_pstMtEmCH, DJ_U8 u8DSPID, DJ_U16 u16CHID )
{
	if ( NULL == m_pstMtEmCH )
		return NULL;

	for (int i = 0; i < g_stEMInfo.m_u16EMCount; i++ )
	{
		if ( g_stEMInfo.m_pstMtEmCH[i].m_stE1Info.m_u8EMVOC_DSPID == u8DSPID
			&& g_stEMInfo.m_pstMtEmCH[i].m_stE1Info.m_u16EM_VOC_CH == u16CHID )
		{
			*m_pstMtEmCH = g_stEMInfo.m_pstMtEmCH[i];
			return 0;
		}
		else if ( g_stEMInfo.m_pstMtEmCH[i].m_stE1Info.m_u8EM_DSPID == u8DSPID
			&& g_stEMInfo.m_pstMtEmCH[i].m_stE1Info.m_u16EM_CH == u16CHID )
		{
			*m_pstMtEmCH = g_stEMInfo.m_pstMtEmCH[i];
			return 0;
		}
		
		if ( g_stEMInfo.m_pstMtEmCH[i].m_stEMInfo.m_u8EMVOC_DSPID == u8DSPID
			&& g_stEMInfo.m_pstMtEmCH[i].m_stEMInfo.m_u16EM_VOC_CH == u16CHID )
		{
			*m_pstMtEmCH = g_stEMInfo.m_pstMtEmCH[i];
			return 0;
		}
		else if ( g_stEMInfo.m_pstMtEmCH[i].m_stEMInfo.m_u8EM_DSPID == u8DSPID
			&& g_stEMInfo.m_pstMtEmCH[i].m_stEMInfo.m_u16EM_CH == u16CHID )
		{
			*m_pstMtEmCH = g_stEMInfo.m_pstMtEmCH[i];
			return 0;
		}
	}

	return -1;
}

int     GetDInfo( ChInfo *pstDstInfo, ChInfo *pstEMInfo )
{
	if ( NULL == pstDstInfo || NULL == pstEMInfo )
		return NULL;

	for (int i = 0; i < g_stEMInfo.m_u16EMCount; i++ )
	{
		if ( ComChInfo( &g_stEMInfo.m_pstMtEmCH[i].m_stEMInfo, pstEMInfo) )
		{
			*pstDstInfo = g_stEMInfo.m_pstMtEmCH[i].m_stE1Info;
			return 0;
		}
	}

	return -1;
}

int     GetEMInfo(ChInfo *pstDstInfo, ChInfo *pstDInfo)
{
	if ( NULL == pstDstInfo || NULL == pstDInfo )
		return NULL;

	for (int i = 0; i < g_stEMInfo.m_u16EMCount; i++ )
	{
		if ( ComChInfo( &g_stEMInfo.m_pstMtEmCH[i].m_stE1Info, pstDInfo) )
		{
			*pstDstInfo = g_stEMInfo.m_pstMtEmCH[i].m_stEMInfo;
			return 0;
		}
	}

	return -1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

DJ_S32 ReadEMNode(MT_EM_CH * info)
{
	static char strAppName[ ] = "EM_Config";
	static char strKey[MAX_APPNAME_LEN];

	TRACE("******** ReadEMInfo\n");
	
	memset(strKey, 0, MAX_APPNAME_LEN);
	sprintf(strKey, "E1_EMDsp[%d]", info->m_u16SeqID + 1);
	info->m_stE1Info.m_u8EM_DSPID = GetPrivateProfileInt(strAppName, strKey, 255, cfg_IniName);

	memset(strKey, 0, MAX_APPNAME_LEN);
	sprintf(strKey, "E1_EM_Ch[%d]", info->m_u16SeqID + 1);
	info->m_stE1Info.m_u16EM_CH = GetPrivateProfileInt(strAppName, strKey, 65535, cfg_IniName);

	memset(strKey, 0, MAX_APPNAME_LEN);
	sprintf(strKey, "E1_EMVOCDsp[%d]", info->m_u16SeqID + 1);
	info->m_stE1Info.m_u8EMVOC_DSPID = GetPrivateProfileInt(strAppName, strKey, 255, cfg_IniName);

	memset(strKey, 0, MAX_APPNAME_LEN);
	sprintf(strKey, "E1_EMVOC_Ch[%d]", info->m_u16SeqID + 1);
	info->m_stE1Info.m_u16EM_VOC_CH = GetPrivateProfileInt(strAppName, strKey, 65535, cfg_IniName);
		
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//E
	memset(strKey, 0, MAX_APPNAME_LEN);
	sprintf(strKey, "EM_EMDsp[%d]", info->m_u16SeqID + 1);
	info->m_stEMInfo.m_u8EM_DSPID = GetPrivateProfileInt(strAppName, strKey, 255, cfg_IniName);

	memset(strKey, 0, MAX_APPNAME_LEN);
	sprintf(strKey, "EM_EM_Ch[%d]", info->m_u16SeqID + 1);
	info->m_stEMInfo.m_u16EM_CH = GetPrivateProfileInt(strAppName, strKey, 65535, cfg_IniName);

	memset(strKey, 0, MAX_APPNAME_LEN);
	sprintf(strKey, "EM_EMVOCDsp[%d]", info->m_u16SeqID + 1);
	info->m_stEMInfo.m_u8EMVOC_DSPID = GetPrivateProfileInt(strAppName, strKey, 255, cfg_IniName);

	memset(strKey, 0, MAX_APPNAME_LEN);
	sprintf(strKey, "EM_EMVOC_Ch[%d]", info->m_u16SeqID + 1);
	info->m_stEMInfo.m_u16EM_VOC_CH = GetPrivateProfileInt(strAppName, strKey, 65535, cfg_IniName);

	return 0;
}

void ReadEMInfo(void)
{
	static char strAppName[ ] = "EM_Config";
	static char strKey[MAX_APPNAME_LEN];	
	
	TRACE("******** ReadEMInfo\n");

	memset(&g_stEMInfo, 0, sizeof(MT_EM_INFO) );

	///////////////////////////////////////////////////////////////////////////////////////
	//get the EM init config
	memset(strKey, 0, MAX_APPNAME_LEN);
	strcpy(strKey, "EM_MAX_GROUP_NUMS");
	g_stEMInfo.m_u16EMCount = GetPrivateProfileInt(strAppName,strKey,0, cfg_IniName);
	///////////////////////////////////////////////////////////////////////////////////////
	
	g_stEMInfo.m_pstMtEmCH = (MT_EM_CH*)malloc(sizeof(MT_EM_CH)*(g_stEMInfo.m_u16EMCount+1));
	if ( NULL == g_stEMInfo.m_pstMtEmCH )
	{
		return;
	}

	memset( (DJ_U8*)g_stEMInfo.m_pstMtEmCH, 0, sizeof(MT_EM_CH)*(g_stEMInfo.m_u16EMCount+1) );

	for (int i = 0; i < g_stEMInfo.m_u16EMCount; i++)
	{
		g_stEMInfo.m_pstMtEmCH[i].m_u16SeqID = i;
		g_stEMInfo.m_pstMtEmCH[i].m_u8IsUsed = FALSE;

		ReadEMNode( &g_stEMInfo.m_pstMtEmCH[i] );
	}
}

void	ReadFromConfig(void)
{
	GetCurrentDirectory ( MAX_FILE_NAME_LEN-32, cfg_IniName );
	strcat ( cfg_IniName, cfg_IniShortName );

	GetPrivateProfileString ( "ConfigInfo", "IpAddr", "192.168.0.8", cfg_ServerID.m_s8ServerIp, sizeof(cfg_ServerID.m_s8ServerIp), cfg_IniName);

	cfg_ServerID.m_u32ServerPort = GetPrivateProfileInt ( "ConfigInfo", "Port", 9001, cfg_IniName);

	GetPrivateProfileString("ConfigInfo","UserName","",cfg_ServerID.m_s8UserName,sizeof(cfg_ServerID.m_s8UserName),cfg_IniName);
	GetPrivateProfileString("ConfigInfo","PassWord","",cfg_ServerID.m_s8UserPwd,sizeof(cfg_ServerID.m_s8UserPwd),cfg_IniName);

	GetPrivateProfileString ( "ConfigInfo", "VocPath", "..\\VOC\\", cfg_VocPath, sizeof(cfg_VocPath), cfg_IniName);

	cfg_iDispChnl = GetPrivateProfileInt ( "ConfigInfo", "DispChnl", 30, cfg_IniName);

	cfg_iVoiceRule = GetPrivateProfileInt ( "ConfigInfo", "VoiceRule", 0, cfg_IniName);

	cfg_iPartWork = GetPrivateProfileInt ( "ConfigInfo", "PartWork", 0, cfg_IniName);

	cfg_iPartWorkModuleID = GetPrivateProfileInt ( "ConfigInfo", "PartWorkModuleID", 0, cfg_IniName);

	cfg_s32DebugOn = GetPrivateProfileInt ( "ConfigInfo", "DebugOn", 0, cfg_IniName);

	/////////////////////////////////////////////////////////////////////////////////////
	//read EM config
	ReadEMInfo( );

}

void	WriteToConfig(void)
{
	char	TmpStr[256];

	WritePrivateProfileString ( "ConfigInfo", "IpAddr", cfg_ServerID.m_s8ServerIp, cfg_IniName);
	
	sprintf ( TmpStr, "%d", cfg_ServerID.m_u32ServerPort);
	WritePrivateProfileString ( "ConfigInfo", "Port", TmpStr, cfg_IniName);
	
	WritePrivateProfileString ( "ConfigInfo", "VocPath", cfg_VocPath, cfg_IniName);

	sprintf ( TmpStr, "%d", cfg_iDispChnl);
	WritePrivateProfileString ( "ConfigInfo", "DispChnl", TmpStr, cfg_IniName);

	sprintf ( TmpStr, "%d", cfg_iVoiceRule);
	WritePrivateProfileString ( "ConfigInfo", "VoiceRule", TmpStr, cfg_IniName);

	sprintf ( TmpStr, "%d", cfg_iPartWork);
	WritePrivateProfileString ( "ConfigInfo", "PartWork", TmpStr, cfg_IniName);

	sprintf ( TmpStr, "%d", cfg_iPartWorkModuleID);
	WritePrivateProfileString ( "ConfigInfo", "PartWorkModuleID", TmpStr, cfg_IniName);

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

	if ( cfg_iDispChnl == 30 )
		((CButton *)pdlg->GetDlgItem (IDC_RADIO30))->SetCheck ( 1 ) ;
	else if ( cfg_iDispChnl == 31 )
		((CButton *)pdlg->GetDlgItem (IDC_RADIO31))->SetCheck ( 1 ) ;
	else if ( cfg_iDispChnl == 32 )
		((CButton *)pdlg->GetDlgItem (IDC_RADIO32))->SetCheck ( 1 ) ;

	if ( cfg_iVoiceRule == 0 )
		((CButton *)pdlg->GetDlgItem (IDC_RADIO_Fix))->SetCheck ( 1 ) ;
	else if ( cfg_iVoiceRule == 1 )
		((CButton *)pdlg->GetDlgItem (IDC_RADIO_SameModule))->SetCheck ( 1 ) ;
	else 
		((CButton *)pdlg->GetDlgItem (IDC_RADIO_MostFreeFist))->SetCheck ( 1 ) ;

	if ( cfg_iPartWork == 0 )
		((CButton *)pdlg->GetDlgItem (IDC_CHECK_PartWork))->SetCheck ( 0 ) ;
	else
		((CButton *)pdlg->GetDlgItem (IDC_CHECK_PartWork))->SetCheck ( 1 ) ;

	sprintf ( TmpStr, "%d", cfg_iPartWorkModuleID );
	pdlg->GetDlgItem ( IDC_EDIT_ModuleID )->SetWindowText ( TmpStr );

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

	if ( ((CButton *)pdlg->GetDlgItem (IDC_RADIO30))->GetCheck ( ) == 1 )
	{
		cfg_iDispChnl = 30;
	}
	else if ( ((CButton *)pdlg->GetDlgItem (IDC_RADIO31))->GetCheck ( ) == 1 )
	{
		cfg_iDispChnl = 31;
	}
	else if ( ((CButton *)pdlg->GetDlgItem (IDC_RADIO32))->GetCheck ( ) == 1 )
	{
		cfg_iDispChnl = 32;
	}

	if ( ((CButton *)pdlg->GetDlgItem (IDC_RADIO_Fix))->GetCheck ( ) )
		cfg_iVoiceRule = 0;
	else if ( ((CButton *)pdlg->GetDlgItem (IDC_RADIO_SameModule))->GetCheck ( ) )
		cfg_iVoiceRule = 1;
	else
		cfg_iVoiceRule = 2;

	if ( ((CButton *)pdlg->GetDlgItem (IDC_CHECK_PartWork))->GetCheck ( ) )
		cfg_iPartWork = 1;
	else
		cfg_iPartWork = 0;

	pdlg->GetDlgItem ( IDC_EDIT_ModuleID )->GetWindowText ( TmpStr, 30 );
	sscanf ( TmpStr, "%d", &cfg_iPartWorkModuleID);

	if ( ((CButton *)pdlg->GetDlgItem (IDC_CHECK_DEBUG))->GetCheck ( ) )
		cfg_s32DebugOn = 1;
	else
		cfg_s32DebugOn = 0;
}

// --------------------------------------------------------------------------------
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

// --------------------------------------------------------------------------------
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
	lvc.cx = 60;
	pdlg->m_ListMain.InsertColumn ( 7, &lvc ); 

	lvc.iSubItem = 8;
	lvc.pszText = "VocInfo" ;
	lvc.cx = 70;
	pdlg->m_ListMain.InsertColumn ( 8, &lvc ); 
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
		
	case TRK_WELCOME:
		strcpy(StateStr,"Welcome to DonJin Keygo Bank Demo");
		break ;
				
	case TRK_ACCOUNT:
		strcpy(StateStr,"Please input your acount") ;
		break ;

	case TRK_PASSWORD:
		strcpy(StateStr,"Please input your password");
		break;

	case TRK_SELECT:
		strcpy(StateStr,"Please select function");
		break;

	case TRK_RECORDFILE:
		strcpy(StateStr,"Record");
		break;

	case TRK_PLAYRESULT:
		strcpy(StateStr,"Play result");
		break;

	case TRK_PLAYRECORD:
		strcpy(StateStr,"Play Back");
		break;

	case TRK_WAIT_ANSWERCALL:
		strcpy(StateStr,"Wait offhook ok");
		break;

	case TRK_WAIT_LINKOK:
		strcpy(StateStr,"Wait Link ok");
		break;

	case TRK_WAIT_REMOVE:
		strcpy(StateStr,"DSP remove");
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
	lvc.pszText = "ErrFlag" ;
	lvc.cx = 60;
	pdlg->m_ListCount.InsertColumn ( 6, &lvc ); 

	lvc.iSubItem = 7;
	lvc.pszText = "RemoveState" ;
	lvc.cx = 80;
	pdlg->m_ListCount.InsertColumn ( 7, &lvc ); 
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

void	DrawCount_ErrFlag ( DJ_S8	s8ModID )
{
	char	TmpStr[256];
	int		iDispRow;

	iDispRow = AllDeviceRes[s8ModID].iSeqID + 1;

	if ( AllDeviceRes[s8ModID].bErrFlag )
		sprintf ( TmpStr, "T" );
	else
		sprintf ( TmpStr, "" );

	pdlg->m_ListCount.SetItemText ( iDispRow, 6, TmpStr );
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

	pdlg->m_ListCount.SetItemText ( iDispRow, 7, TmpStr );
}

// -------------------------------------------------------------------------------------------------
void	ReDrawAll (void)
{
	char	TmpStr[256];
	int		i, iDispRow;
	TRUNK_STRUCT	*pOneTrunk;

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
		DrawCount_ErrFlag ( MapTable_Module[i] );
		DrawCount_RemoveState ( MapTable_Module[i] );
	}
}

// --------------------------------------------------------------------------------
bool	InitSystem()
{
	RetCode_t	r;
	char		MsgStr[160];

	pdlg = (CXMS_EmDemoDlg	*)theApp.m_pMainWnd;

	// Read From "XMS_EmDemo.INI"
	ReadFromConfig();

	// Special code for CAS(SS1)
	// Read From "C:\\DJKeygoe\\Samples\\CAS_Common_Code\\XMS_CAS_Cfg.INI"
	if ( CAS_Common_Cfg_ReadCfg ( &g_Param_CAS ) != 0 )
	{
		sprintf ( MsgStr, "CAS_Common_Cfg_ReadCfg \"C:\\DJKeygoe\\Samples\\CAS_Common_Code\\XMS_CAS_Cfg.INI\" Error!" );
		MessageBox(NULL, MsgStr, "Init System", MB_OK ) ;
	}
	// end of code for CAS(SS1)

	// Special code for Analog
	// Read From "C:\\DJKeygoe\\Samples\\Analog_Common_Code\\XMS_Analog_Cfg.INI"
	if ( Analog_Common_Cfg_ReadCfg ( &g_Param_Analog ) != 0 )
	{
		sprintf ( MsgStr, "Analog_Common_Cfg_ReadCfg \"C:\\DJKeygoe\\Samples\\Analog_Common_Code\\XMS_Analog_Cfg.INI\" Error!" );
		MessageBox(NULL, MsgStr, "Init System", MB_OK ) ;
	}
	// end of code for CAS(SS1)

	// Init m_ListMain
	InitListMain();

	// Init m_ListPcm
	InitListPcm();

	// Init m_ListMsg
	InitListMsg();

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

	// save to "XMS_EmDemo.INI"
	FetchFromText();
	WriteToConfig();

}

// --------------------------------------------------------------------------------
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

void	OpenBoardDevice (  DJ_S8 s8DspModID )
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

	// pTrunk
	for ( i = 0; i < AllDeviceRes[s8DspModID].lTrunkNum; i++ )
	{
		OpenTrunkDevice ( &AllDeviceRes[s8DspModID].pTrunk[i] );
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

void	OpenDeviceOK ( DeviceID_t *pDevice )
{
	TRUNK_STRUCT	*pOneTrunk;

	if ( pDevice->m_s16DeviceMain == XMS_DEVMAIN_BOARD )
	{
		AllDeviceRes[pDevice->m_s8ModuleID].deviceID.m_CallID = pDevice->m_CallID;		// this line is very important, must before all operation
		AllDeviceRes[pDevice->m_s8ModuleID].bOpenFlag = true;

		SetGTD_ToneParam ( pDevice);
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

		if ( pOneTrunk->deviceID.m_s16DeviceSub == XMS_DEVSUB_ANALOG_TRUNK )
		{
			// Set AnalogTrunk
			void* p = NULL;
			CmdParamData_AnalogTrunk_t cmdAnalogTrunk;
			DJ_U16 u16ParamType = ANALOGTRUNK_PARAM_UNIPARAM ;
			DJ_U16 u16ParamSize = sizeof(CmdParamData_AnalogTrunk_t);

			memset(&cmdAnalogTrunk,0,sizeof(cmdAnalogTrunk));
			cmdAnalogTrunk.m_u16CallInRingCount = 3;			// 3 times RingBack
			cmdAnalogTrunk.m_u16CallInRingTimeOut = 6000;		// 60 seconds

			p = (void*)&cmdAnalogTrunk;

			RetCode_t r ;
			r = XMS_ctsSetParam( g_acsHandle, & pOneTrunk->deviceID, u16ParamType, u16ParamSize, (DJ_Void *)p );
			char szbuffer[1024];
			memset(szbuffer,0,sizeof(szbuffer));
			sprintf(szbuffer,"Set AnalogTrunk  ret = %d\n",r);
			AddMsg ( szbuffer );

			// Search Free Voice for get CallerID(FSK)
			// if you needn't CallerID, ignore next line
			PrepareForCallerID ( pOneTrunk );
		}
	}

	if ( pDevice->m_s16DeviceMain == XMS_DEVMAIN_VOICE )
	{
		M_OneVoice(*pDevice).deviceID.m_CallID = pDevice->m_CallID;		// this is very important

		// init this Device: Voice
		Change_Voc_State ( &M_OneVoice(*pDevice), VOC_FREE);

		XMS_ctsResetDevice ( g_acsHandle, pDevice, NULL );
		XMS_ctsGetDevState ( g_acsHandle, pDevice, NULL );

		// Build Index
		if ( g_iTotalVoiceOpened == 0 )
		{
//			My_BuildIndex ( pDevice );
		}

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
}

// -------------------------------------------------------------------------------------------------
void	HandleDevState ( Acs_Evt_t *pAcsEvt )
{
	TRUNK_STRUCT	*pOneTrunk;
	PCM_STRUCT		*pOnePcm;
	Acs_GeneralProc_Data *pGeneralData = NULL;

	pGeneralData = (Acs_GeneralProc_Data *)FetchEventData(pAcsEvt);
	if ( pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_INTERFACE_CH )
	{
		pOneTrunk = &M_OneTrunk(pAcsEvt->m_DeviceID);

		pOneTrunk->iLineState = pGeneralData->m_s32DeviceState;
		DrawMain_LineState( pOneTrunk );
	}

	if ( pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_DIGITAL_PORT )
	{
		pOnePcm = &M_OnePcm(pAcsEvt->m_DeviceID);

		pOnePcm->u8E1Type = (pGeneralData->m_s32DeviceState >> 16) & 0xFF;
		pOnePcm->s32AlarmVal = (pGeneralData->m_s32DeviceState & 0xFFFF);

		DrawPcm_TypeAndAlarm ( pOnePcm );
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

	// check if all device is WAIT_OPEN or WAIT_REMOVE
	CheckRemoveReady ( s8DspModID );
}

// -----------------------------------------------------------------------------
// --------------------------------------------------------------------------------
void	My_BuildIndex ( DeviceID_t	*pVocDevID )
{
	RetCode_t	r;
	char		FileName[256], MsgStr[256];
	int			i;
	PlayProperty_t  playProperty;
	
	r = XMS_ctsInitPlayIndex ( g_acsHandle, pVocDevID, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "XMS_ctsInitPlayIndex() FAIL. ret = r", r );
		AddMsg ( MsgStr );
		return ;
	}

	memset ( &playProperty, 0, sizeof(playProperty) );
	for ( i = 0; i < 17; i ++ )
	{
		if ( i == 16 )
		{
			playProperty.m_u16PlayType = XMS_BUILD_INDEX_FILE;
			sprintf ( FileName, "%s\\bank.008", cfg_VocPath );
		}
		else
		{
			playProperty.m_u16PlayType = XMS_BUILD_INDEX_RAM;
			sprintf ( FileName, "%s\\D%d", cfg_VocPath, i );
		}

		strcpy ( playProperty.m_s8PlayContent, FileName );
	
		r = XMS_ctsBuildPlayIndex ( g_acsHandle, pVocDevID, &playProperty, NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "XMS_ctsBuildPlayIndex(%s) FAIL. ret = r", FileName, r );
			AddMsg ( MsgStr );
		}
	}

}

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
	DJ_U32           i = 0;	
	PlayProperty_t  playProperty;
	RetCode_t		 r;

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

DJ_S32	 PlayIndex ( DeviceID_t	*pVocDevID, DJ_U16 u16Index, DJ_U8 u8PlayTag, bool bIsQueue )
{	
	DJ_U32           i = 0;	
	PlayProperty_t  playProperty;
	RetCode_t		 r;

	memset(&playProperty,0,sizeof(playProperty));		
	
	if ( bIsQueue )
		playProperty.m_u16PlayType = XMS_PLAY_TYPE_INDEX_QUEUE;	
	else
		playProperty.m_u16PlayType = XMS_PLAY_TYPE_INDEX;	

	playProperty.m_u8TaskID = u8PlayTag;

	playProperty.m_u16PlayIndex = u16Index;
	
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

/* Stop Record */
DJ_S32 StopRecordFile ( DeviceID_t	*pVocDevID )
{
	RetCode_t		r;
	ControlRecord_t	controlRecord;

	controlRecord.m_u32ControlType = XMS_STOP_RECORD;

	r = XMS_ctsControlRecord ( g_acsHandle, pVocDevID, &controlRecord, NULL );

	return r;
}

/* Handle Record */
DJ_S32	 RecordFile ( DeviceID_t	*pVocDevID, DJ_S8 *s8FileName, DJ_U32 u32RecSize, bool bIsAppend )
{	
	DJ_U32				i = 0;	
	RecordProperty_t	recordProperty;
	RetCode_t			r;

	memset(&recordProperty,0,sizeof(RecordProperty_t));		
	
	recordProperty.m_u32MaxSize = u32RecSize;

	if ( bIsAppend )
		recordProperty.m_s8IsAppend = 1;
	else
		recordProperty.m_s8IsAppend = 0;

	strcpy ( recordProperty.m_s8FileName, s8FileName );

	r = XMS_ctsRecord ( g_acsHandle, pVocDevID, &recordProperty, NULL );

	return r;
}

bool	CheckRecordEnd ( TRUNK_STRUCT *pOneTrunk, Acs_Evt_t *pAcsEvt )
{
	Acs_MediaProc_Data	*pMediaData = NULL;

	if ( pAcsEvt->m_s32EventType == XMS_EVT_RECORD )	
	{
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
	char   sbuffer[200];
	char		*p;

	memset(sbuffer,0,sizeof(sbuffer));
	if ( pAcsEvt->m_s32EventType == XMS_EVT_RECVIODATA )	/*IO Data Event*/
	{
		pIOData = (Acs_IO_Data *)FetchEventData(pAcsEvt);

		if ( ( pIOData->m_u16IoType== XMS_IO_TYPE_DTMF ) 
			&& ( pIOData->m_u16IoDataLen > 0 ) )
		{
			p = (char *)FetchIOData(pAcsEvt);
			sprintf(sbuffer,"[%s]",p);
			AddMsg(sbuffer);

			return *p;
		}
	}

	return -1;	// not a good DTMF
}

unsigned char *My_GetFskCode ( Acs_Evt_t *pAcsEvt )
{
	Acs_IO_Data				*pIOData = NULL;
	unsigned char		*p;

	if ( pAcsEvt->m_s32EventType == XMS_EVT_RECVIODATA )	/*IO Data Evemt*/
	{
		pIOData = (Acs_IO_Data *)FetchEventData(pAcsEvt);

		if ( ( pIOData->m_u16IoType== XMS_IO_TYPE_FSK ) 
			&& ( pIOData->m_u16IoDataLen > 0 ) )
		{
			p = (unsigned char *)FetchIOData(pAcsEvt);

			return p;
		}
	}

	return NULL;	// not a good FSK
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

int		SearchOneFreeMTVOC (  TRUNK_STRUCT *pOneTrunk, DeviceID_t *pFreeVocDeviceID )
{
	DJ_S8			s8ModID;
	DJ_S16			s16ChID;
	int				i;
	static	int		iLoopStart = 0;
	TRUNK_STRUCT	*pVocTrunk;

	s8ModID = pOneTrunk->deviceID.m_s8ModuleID;

	TRACE("***** Before cfg_iVoiceRule: %d, iLoopStart: %d, EMCount: %d \n", cfg_iVoiceRule, iLoopStart, g_stEMInfo.m_u16EMCount );
	if ( 2 == cfg_iVoiceRule )
	{
		iLoopStart = iLoopStart % g_stEMInfo.m_u16EMCount;
		i = iLoopStart;		
	}
	else
		i = 0;

	TRACE("***** After cfg_iVoiceRule: %d, iLoopStart: %d, EMCount: %d \n", cfg_iVoiceRule, iLoopStart, g_stEMInfo.m_u16EMCount );
	
	for ( ; i < g_stEMInfo.m_u16EMCount; i ++ )
	{		
		iLoopStart = i;

		if ( g_stEMInfo.m_pstMtEmCH[i].m_u8IsUsed )
		{
			continue;
		}

		if ( s8ModID != g_stEMInfo.m_pstMtEmCH[i].m_stE1Info.m_u8EMVOC_DSPID ) 
			continue;

		s16ChID = g_stEMInfo.m_pstMtEmCH[i].m_stE1Info.m_u16EM_VOC_CH;

		pVocTrunk = &AllDeviceRes[s8ModID].pTrunk[s16ChID];

		if ( pVocTrunk->deviceID.m_s16DeviceSub != XMS_DEVSUB_ANALOG_VOC2W 
		  && pVocTrunk->deviceID.m_s16DeviceSub != XMS_DEVSUB_ANALOG_VOC4W )
			continue;

		if ( pVocTrunk->State == TRK_FREE )
		{
			*pFreeVocDeviceID = pVocTrunk->deviceID;
			g_stEMInfo.m_pstMtEmCH[i].m_u8IsUsed = TRUE;
			pVocTrunk->State = TRK_MT_USED;
			DrawCount_Trunk(s8ModID);

			iLoopStart = i + 1;
			return 0;
		}
	}

	if ( 2 == cfg_iVoiceRule )
	{
		iLoopStart = 0;
		for ( i = 0; i < g_stEMInfo.m_u16EMCount; i ++ )
		{
			iLoopStart = i;

			if ( g_stEMInfo.m_pstMtEmCH[i].m_u8IsUsed )
			{
				continue;
			}

			if ( s8ModID != g_stEMInfo.m_pstMtEmCH[i].m_stE1Info.m_u8EMVOC_DSPID ) 
				continue;

			s16ChID = g_stEMInfo.m_pstMtEmCH[i].m_stE1Info.m_u16EM_VOC_CH;

			pVocTrunk = &AllDeviceRes[s8ModID].pTrunk[s16ChID];

			if ( pVocTrunk->deviceID.m_s16DeviceSub != XMS_DEVSUB_ANALOG_VOC2W 
			  && pVocTrunk->deviceID.m_s16DeviceSub != XMS_DEVSUB_ANALOG_VOC4W )
				continue;

			if ( pVocTrunk->State == TRK_FREE )
			{
				*pFreeVocDeviceID = pVocTrunk->deviceID;
				g_stEMInfo.m_pstMtEmCH[i].m_u8IsUsed = TRUE;
				pVocTrunk->State = TRK_MT_USED;
				DrawCount_Trunk(s8ModID);
		
				iLoopStart = i + 1;
				return 0;
			}
		}
	}
	
	return -1;
}

int		FreeOneFreeMTVOC (  TRUNK_STRUCT *pTrunkMTVoc )
{
	DJ_S8	s8ModID;
	DeviceID_t *pFreeVocDeviceID = &pTrunkMTVoc->deviceID;

	s8ModID = pFreeVocDeviceID->m_s8ModuleID;
	for ( int i = 0; i < g_stEMInfo.m_u16EMCount; i++ )
	{
		if ( g_stEMInfo.m_pstMtEmCH[i].m_u8IsUsed )
		{
			if ( ( g_stEMInfo.m_pstMtEmCH[i].m_stE1Info.m_u8EMVOC_DSPID == s8ModID ) 
			  && ( g_stEMInfo.m_pstMtEmCH[i].m_stE1Info.m_u16EM_VOC_CH == pFreeVocDeviceID->m_s16ChannelID ) )
			{
				if ( AllDeviceRes[s8ModID].lFlag == 1 )
				{
					pTrunkMTVoc->State = TRK_FREE;
					g_stEMInfo.m_pstMtEmCH[i].m_u8IsUsed = FALSE;

					DrawCount_Trunk(s8ModID);
					return	0;		// OK
				}						
			}
		}
	}

	return -1;			// invalid VocDeviceID
}

int		SearchOneFreeVoice (  TRUNK_STRUCT *pOneTrunk, DeviceID_t *pFreeVocDeviceID )
{
	DJ_S8			s8ModID;
	DJ_S16			s16ChID;
	int				i;
	static	int		iLoopStart = 0;
	VOICE_STRUCT	*pOneVoice;
	DJ_S8			s8SearchModID;
	long			lNowMostFreeNum;

	s8ModID = pOneTrunk->deviceID.m_s8ModuleID;

	if ( cfg_iVoiceRule == 0 )			// Fix relationship between Trunk & Voice
	{
		s16ChID = pOneTrunk->deviceID.m_s16ChannelID;
		
		i = pOneTrunk->iModSeqID;

		if ( i < AllDeviceRes[s8ModID].lVocNum )
		{
			pOneVoice = &AllDeviceRes[s8ModID].pVoice[i];
			if ( pOneVoice->State != VOC_WAITOPEN )
			{
				*pFreeVocDeviceID = pOneVoice->deviceID;

				// use this voice device 
				Change_Voc_State ( pOneVoice, VOC_USED);
				AllDeviceRes[s8ModID].lVocFreeNum--;
				g_iTotalVoiceFree --;
				DrawCount_Voc ( s8ModID );
				return i;
			}
		}

		return -1;
	}

	if ( cfg_iVoiceRule == 1 )			// Search in Same Module
	{
		s8SearchModID = s8ModID;
	}
	else		// Search in Most free resource module
	{
		s8SearchModID = -1;
		lNowMostFreeNum = -1;
		for ( i = 0; i < g_iTotalModule; i ++ )
		{
			if ( AllDeviceRes[MapTable_Module[i]].lVocFreeNum > lNowMostFreeNum )
			{
				s8SearchModID = MapTable_Module[i];
				lNowMostFreeNum = AllDeviceRes[MapTable_Module[i]].lVocFreeNum;
			}
		}
	}

	for ( i = 0; i < AllDeviceRes[s8SearchModID].lVocNum; i ++ )
	{
		pOneVoice = &AllDeviceRes[s8SearchModID].pVoice[i];
		if ( pOneVoice->State == VOC_FREE )
		{
			*pFreeVocDeviceID = pOneVoice->deviceID;

			// user this voice device 
			Change_Voc_State ( pOneVoice, VOC_USED);
			AllDeviceRes[s8SearchModID].lVocFreeNum--;
			g_iTotalVoiceFree --;
			DrawCount_Voc ( s8SearchModID );
			return i;
		}
	}

	return -1;
}

int		FreeOneFreeVoice (  DeviceID_t *pFreeVocDeviceID )
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

void	Change_EM_State ( TRUNK_STRUCT *pOneTrunk, TRUNK_EMVOC_STATE NewState )
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

// Search Free Voice for get CallerID(FSK)
void	PrepareForCallerID ( TRUNK_STRUCT *pOneTrunk )
{
	DeviceID_t FreeVocDeviceID;

	if ( pOneTrunk->deviceID.m_s16DeviceSub != XMS_DEVSUB_ANALOG_TRUNK )
		return;

	if ( SearchOneFreeVoice ( pOneTrunk,  &FreeVocDeviceID ) >= 0 )
	{
		pOneTrunk->VocDevID = FreeVocDeviceID;

		M_OneVoice(FreeVocDeviceID).UsedDevID = pOneTrunk->deviceID; 

		DrawMain_VocInfo ( pOneTrunk );

		My_DualLink ( &FreeVocDeviceID, &pOneTrunk->deviceID );
		SetGtD_AnalogTrunk(&FreeVocDeviceID);
	}
}

void	InitTrunkChannel ( TRUNK_STRUCT *pOneTrunk )
{
	Change_State ( pOneTrunk, TRK_FREE );

	pOneTrunk->CallerCode[0]=0;
	pOneTrunk->CalleeCode[0]=0;

	My_InitDtmfBuf ( pOneTrunk );
	DrawMain_DTMF ( pOneTrunk );

	memset ( &pOneTrunk->VocDevID, 0, sizeof(DeviceID_t) );		// 0: didn't alloc Voc Device
	DrawMain_VocInfo ( pOneTrunk );
}

void ResetTrunk ( TRUNK_STRUCT *pOneTrunk, Acs_Evt_t *pAcsEvt )
{
	StopPlayFile ( &pOneTrunk->VocDevID );

	// free the used Voice Resource
	if ( pOneTrunk->VocDevID.m_s16DeviceMain != 0 )
	{
		if ( (pOneTrunk->VocDevID.m_s16DeviceSub == XMS_DEVSUB_ANALOG_VOC2W)
		  || (pOneTrunk->VocDevID.m_s16DeviceSub == XMS_DEVSUB_ANALOG_VOC4W) )
		{
			Change_EM_State ( pOneTrunk, TRK_EMVOC_FREE );
			NotifyEMDev( &pOneTrunk->VocDevID,MTVOC_EM_TYPE_D, FALSE );		
			NotifyEMDev( &pOneTrunk->VocDevID,MTVOC_EM_TYPE_E, FALSE );		
			FreeOneFreeMTVOC( &M_OneTrunk(pOneTrunk->VocDevID) );
		}

		My_DualUnlink ( &pOneTrunk->VocDevID, &pOneTrunk->deviceID );

		FreeOneFreeVoice (  &pOneTrunk->VocDevID );

		memset ( &M_OneVoice(pOneTrunk->VocDevID).UsedDevID,	0, sizeof(DeviceID_t) );		// 0: didn't alloc Device
		memset ( &pOneTrunk->VocDevID, 0, sizeof(DeviceID_t) );		// 0: didn't alloc Device
		DrawMain_VocInfo ( pOneTrunk );
	}


	InitTrunkChannel ( pOneTrunk );

	// Search Free Voice for get CallerID(FSK)
	// if you needn't CallerID, ignore next line
	PrepareForCallerID ( pOneTrunk );
}

// Special code for CAS(SS1)
void	SpecialForCas ( TRUNK_STRUCT *pOneTrunk, Acs_Evt_t *pAcsEvt )
{
	DeviceID_t				FreeVocDeviceID;

	if ( pOneTrunk->deviceID.m_s16DeviceSub != XMS_DEVSUB_E1_CAS )
		return;

	if ( pAcsEvt->m_s32EventType == XMS_EVT_CAS_MFC_START )	/* start receive MFC, need a Voice Device */
	{
		if ( SearchOneFreeVoice ( pOneTrunk,  &FreeVocDeviceID ) >= 0 )
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

		FreeOneFreeVoice (  &pOneTrunk->VocDevID );

		memset ( &M_OneVoice(pOneTrunk->VocDevID).UsedDevID,	0, sizeof(DeviceID_t) );		// 0: didn't alloc Voc Device 
		memset ( &pOneTrunk->VocDevID, 0, sizeof(DeviceID_t) );		// 0: didn't alloc Voc Device
		DrawMain_VocInfo ( pOneTrunk );
	}
}
// end of code for CAS(SS1)

// Special code for Analog
void	SetGTD_ToneParam ( DeviceID_t *pDevice )
{
	RetCode_t					r;
	DJ_U16						u16ParamType, u16ParamSize;
	CmdParamData_GtdFreq_t		TmpGtdFreq;
	CmdParamData_GtdProtoType_t	TmpGtdProto;

	// ---------- set Freq ----------
	u16ParamType = 	BOARD_PARAM_SETGTDFREQ ;
	u16ParamSize = sizeof(CmdParamData_GtdFreq_t);

	// freq0
	TmpGtdFreq.m_u16Freq_Index = 0;
	TmpGtdFreq.m_u16Freq_Coef = g_Param_Analog.m_u16Freq0;
	r = XMS_ctsSetParam( g_acsHandle, pDevice, u16ParamType, u16ParamSize, (DJ_Void *)&TmpGtdFreq );
		
	// freq1
	TmpGtdFreq.m_u16Freq_Index = 1;
	TmpGtdFreq.m_u16Freq_Coef = g_Param_Analog.m_u16Freq1;
	r = XMS_ctsSetParam( g_acsHandle, pDevice, u16ParamType, u16ParamSize, (DJ_Void *)&TmpGtdFreq );

	// ---------- set DialTone ----------
	u16ParamType = 	BOARD_PARAM_SETGTDTONE ;
	u16ParamSize = sizeof(CmdParamData_GtdProtoType_t);
	
	memset ( &TmpGtdProto, 0, sizeof(CmdParamData_GtdProtoType_t) );
	TmpGtdProto.m_u16GtdID = 48;		// DialTone, we use GTD's ID 48
	TmpGtdProto.m_u16Freq_Mask = g_Param_Analog.m_u16DialTone_FreqIndexMask;
	TmpGtdProto.m_u16Envelope_Mode = 0;
	TmpGtdProto.m_u16Repeat_Count = 1;
	TmpGtdProto.m_u16Min_On_Time1 = g_Param_Analog.m_u16DialTone_On_Time/15;		// the unit is 15 ms

	r = XMS_ctsSetParam( g_acsHandle, pDevice, u16ParamType, u16ParamSize, (DJ_Void *)&TmpGtdProto );

	// ---------- set RingBack Tone ----------
	u16ParamType = 	BOARD_PARAM_SETGTDTONE ;
	u16ParamSize = sizeof(CmdParamData_GtdProtoType_t);
	
	memset ( &TmpGtdProto, 0, sizeof(CmdParamData_GtdProtoType_t) );
	TmpGtdProto.m_u16GtdID = 49;		// DialTone, we use GTD's ID 49
	TmpGtdProto.m_u16Freq_Mask = g_Param_Analog.m_u16RingBackTone_FreqIndexMask;
	TmpGtdProto.m_u16Envelope_Mode = 1;
	TmpGtdProto.m_u16Repeat_Count = 1;
	TmpGtdProto.m_u16Min_On_Time1 = (g_Param_Analog.m_u16RingBackTone_On_Time * 
		(100 - g_Param_Analog.m_u16RingBackTone_TimeDeviation)/100 ) / 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Max_On_Time1 = (g_Param_Analog.m_u16RingBackTone_On_Time * 
		(100 + g_Param_Analog.m_u16RingBackTone_TimeDeviation))/100  / 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Min_Off_Time1 = (g_Param_Analog.m_u16RingBackTone_Off_Time * 
		(100 - g_Param_Analog.m_u16RingBackTone_TimeDeviation))/100  / 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Max_Off_Time1 = (g_Param_Analog.m_u16RingBackTone_Off_Time * 
		(100 + g_Param_Analog.m_u16RingBackTone_TimeDeviation))/100  / 15;		// the unit is 15 ms

	r = XMS_ctsSetParam( g_acsHandle, pDevice, u16ParamType, u16ParamSize, (DJ_Void *)&TmpGtdProto );

	// ---------- set Busy Tone0 ----------
	u16ParamType = 	BOARD_PARAM_SETGTDTONE ;
	u16ParamSize = sizeof(CmdParamData_GtdProtoType_t);
	
	memset ( &TmpGtdProto, 0, sizeof(CmdParamData_GtdProtoType_t) );
	TmpGtdProto.m_u16GtdID = 50;		// BusyTone0, we use GTD's ID 50
	TmpGtdProto.m_u16Freq_Mask = g_Param_Analog.m_u16BusyTone0_FreqIndexMask;
	TmpGtdProto.m_u16Envelope_Mode = 1;
	TmpGtdProto.m_u16Repeat_Count = 1;
	TmpGtdProto.m_u16Min_On_Time1 = (g_Param_Analog.m_u16BusyTone0_On_Time * 
		(100 - g_Param_Analog.m_u16BusyTone0_TimeDeviation)/100 ) / 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Max_On_Time1 = (g_Param_Analog.m_u16BusyTone0_On_Time * 
		(100 + g_Param_Analog.m_u16BusyTone0_TimeDeviation))/100  / 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Min_Off_Time1 = (g_Param_Analog.m_u16BusyTone0_Off_Time * 
		(100 - g_Param_Analog.m_u16BusyTone0_TimeDeviation))/100  / 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Max_Off_Time1 = (g_Param_Analog.m_u16BusyTone0_Off_Time * 
		(100 + g_Param_Analog.m_u16BusyTone0_TimeDeviation))/100  / 15;		// the unit is 15 ms

	r = XMS_ctsSetParam( g_acsHandle, pDevice, u16ParamType, u16ParamSize, (DJ_Void *)&TmpGtdProto );

	// ---------- set Busy Tone1 ----------
	u16ParamType = 	BOARD_PARAM_SETGTDTONE ;
	u16ParamSize = sizeof(CmdParamData_GtdProtoType_t);
	
	memset ( &TmpGtdProto, 0, sizeof(CmdParamData_GtdProtoType_t) );
	TmpGtdProto.m_u16GtdID = 51;		// BusyTone1, we use GTD's ID 51
	TmpGtdProto.m_u16Freq_Mask = g_Param_Analog.m_u16BusyTone1_FreqIndexMask;
	TmpGtdProto.m_u16Envelope_Mode = 1;
	TmpGtdProto.m_u16Repeat_Count = 1;
	TmpGtdProto.m_u16Min_On_Time1 = (g_Param_Analog.m_u16BusyTone1_On_Time * 
		(100 - g_Param_Analog.m_u16BusyTone1_TimeDeviation)/100 ) / 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Max_On_Time1 = (g_Param_Analog.m_u16BusyTone1_On_Time * 
		(100 + g_Param_Analog.m_u16BusyTone1_TimeDeviation))/100  / 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Min_Off_Time1 = (g_Param_Analog.m_u16BusyTone1_Off_Time * 
		(100 - g_Param_Analog.m_u16BusyTone1_TimeDeviation))/100  / 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Max_Off_Time1 = (g_Param_Analog.m_u16BusyTone1_Off_Time * 
		(100 + g_Param_Analog.m_u16BusyTone1_TimeDeviation))/100  / 15;		// the unit is 15 ms

	r = XMS_ctsSetParam( g_acsHandle, pDevice, u16ParamType, u16ParamSize, (DJ_Void *)&TmpGtdProto );

	// ---------- set Busy Tone2 ----------
	u16ParamType = 	BOARD_PARAM_SETGTDTONE ;
	u16ParamSize = sizeof(CmdParamData_GtdProtoType_t);
	
	memset ( &TmpGtdProto, 0, sizeof(CmdParamData_GtdProtoType_t) );
	TmpGtdProto.m_u16GtdID = 52;		// BusyTone2, we use GTD's ID 52
	TmpGtdProto.m_u16Freq_Mask = g_Param_Analog.m_u16BusyTone2_FreqIndexMask;
	TmpGtdProto.m_u16Envelope_Mode = 1;
	TmpGtdProto.m_u16Repeat_Count = 1;
	TmpGtdProto.m_u16Min_On_Time1 = (g_Param_Analog.m_u16BusyTone2_On_Time * 
		(100 - g_Param_Analog.m_u16BusyTone2_TimeDeviation)/100 ) / 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Max_On_Time1 = (g_Param_Analog.m_u16BusyTone2_On_Time * 
		(100 + g_Param_Analog.m_u16BusyTone2_TimeDeviation))/100  / 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Min_Off_Time1 = (g_Param_Analog.m_u16BusyTone2_Off_Time * 
		(100 - g_Param_Analog.m_u16BusyTone2_TimeDeviation))/100  / 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Max_Off_Time1 = (g_Param_Analog.m_u16BusyTone2_Off_Time * 
		(100 + g_Param_Analog.m_u16BusyTone2_TimeDeviation))/100  / 15;		// the unit is 15 ms

	r = XMS_ctsSetParam( g_acsHandle, pDevice, u16ParamType, u16ParamSize, (DJ_Void *)&TmpGtdProto );
}
// end of code for Analog

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

	cmdVoc.m_VocGtdControl.m_u8EXTEnable = 0x2;		// Enable PVD Detect

	strcpy((char*)&cmdVoc.m_VocGtdControl.m_u8GTDID[0],"GHIJK");	// Detect Busy Tone

	DJ_U16 u16ParamType = VOC_PARAM_UNIPARAM;
	DJ_U16 u16ParamSize = sizeof(cmdVoc);
	void* p = (void*) &cmdVoc;

	int r = XMS_ctsSetParam( g_acsHandle,pDevId,u16ParamType,u16ParamSize,(void*)p);
	char szbuffer[1024];
	memset(szbuffer,0,sizeof(szbuffer));
	sprintf(szbuffer,"Set GTD ret = %d\n",r);
	AddMsg ( szbuffer );

	//========Set GTG End  ========
}

void NotifyEMDev( DeviceID_t *pTrunkMTVoc, MTVOC_EM_TYPE Type, DJ_U8 txState )
{
	RetCode_t	r;
	void		* p;
	// parameter
	DJ_U16		u16ParamType, u16ParamSize;
	
	Acs_AnalogEM_CMD  ATrunkEM = {0};

	MT_EM_CH stMtEmCH;	
	TRUNK_STRUCT *pTrunkVoc = NULL;

	u16ParamType = XMS_AEM_PARAM_SND_M_SIGNAL;
	u16ParamSize = sizeof(Acs_AnalogEM_CMD);
	p = (void *)&ATrunkEM;

	//ON: if txState equal to 1, OFF:  if txState equal to 0
	ATrunkEM.m_u8Channel_Enable = 1;
	ATrunkEM.m_u8Type           = 1;
	ATrunkEM.m_u8Tx_State       = txState;
	ATrunkEM.m_u8Rx_State       = 0;

	if ( 0!= GetMtEmCH( &stMtEmCH, pTrunkMTVoc->m_s8ModuleID, pTrunkMTVoc->m_s16ChannelID ) )
	{
		return;
	}

	if ( Type == MTVOC_EM_TYPE_D )
		pTrunkVoc = &AllDeviceRes[stMtEmCH.m_stE1Info.m_u8EM_DSPID].pTrunk[stMtEmCH.m_stE1Info.m_u16EM_CH];
	else
		pTrunkVoc = &AllDeviceRes[stMtEmCH.m_stEMInfo.m_u8EM_DSPID].pTrunk[stMtEmCH.m_stEMInfo.m_u16EM_CH];

	if ( NULL != pTrunkVoc && pTrunkVoc->deviceID.m_s16DeviceSub == XMS_DEVSUB_ANALOG_EM )
	{	
		r = XMS_ctsSetParam( g_acsHandle, &pTrunkVoc->deviceID, u16ParamType, u16ParamSize, (DJ_Void *)p );
		if ( r < 0 )
		{
			TRACE("*****(DSP: %d, CH: %d) MTEM Send M MSG fail. \n", pTrunkVoc->deviceID.m_s8ModuleID, pTrunkVoc->deviceID.m_s16ChannelID);
		}
		else
		{
			TRACE("*****(DSP: %d, CH: %d) MTEM Send M(txState: %d) MSG success. \n", pTrunkVoc->deviceID.m_s8ModuleID, pTrunkVoc->deviceID.m_s16ChannelID, txState);
		}
	}

}

void EmChFreeProc(TRUNK_STRUCT *pOneTrunk, Acs_Evt_t *pAcsEvt)
{
	MT_EM_CH stMtEmCH;	
	TRUNK_STRUCT *pTrunkVoc = NULL;
	
	if ( 0 != GetMtEmCH( &stMtEmCH, pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID ))
	{
		return;
	}

	pTrunkVoc = &AllDeviceRes[stMtEmCH.m_stEMInfo.m_u8EMVOC_DSPID].pTrunk[stMtEmCH.m_stEMInfo.m_u16EM_VOC_CH];

	if ( NULL != pTrunkVoc )
	{
		pTrunkVoc->u8PlayTag = 0;
		
		My_DualUnlink ( &pTrunkVoc->VocDevID, &pTrunkVoc->deviceID ); 

		memset(&M_OneVoice(pTrunkVoc->VocDevID).UsedDevID, 0, sizeof(DeviceID_t) );
		memset(&M_OneTrunk(pTrunkVoc->VocDevID).VocDevID, 0, sizeof(DeviceID_t) );
		memset(&pTrunkVoc->VocDevID, 0, sizeof(DeviceID_t) );
		
		DrawMain_VocInfo ( pTrunkVoc );
		
		TRACE("*****(DSP: %d, CH: %d) MTEM Unlink (DSP: %d, CH: %d)\n", pTrunkVoc->deviceID.m_s8ModuleID, pTrunkVoc->deviceID.m_s16ChannelID, pTrunkVoc->VocDevID.m_s8ModuleID, pTrunkVoc->VocDevID.m_s16ChannelID );
	}
}


void EmChConnectProc(TRUNK_STRUCT *pOneTrunk, Acs_Evt_t *pAcsEvt)
{
	MT_EM_CH stMtEmCH;	
	DeviceID_t FreeVocDeviceID;
	TRUNK_STRUCT *pTrunkVoc = NULL;
	
	if ( 0!= GetMtEmCH( &stMtEmCH, pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID ))
	{
		return;
	}

	pTrunkVoc = &AllDeviceRes[stMtEmCH.m_stEMInfo.m_u8EMVOC_DSPID].pTrunk[stMtEmCH.m_stEMInfo.m_u16EM_VOC_CH];

	if ( NULL != pTrunkVoc )
	{
		if ( SearchOneFreeVoice( pTrunkVoc,  &FreeVocDeviceID ) >= 0 )
		{
			pTrunkVoc->u8PlayTag = 16;

			pTrunkVoc->VocDevID = FreeVocDeviceID;

			M_OneVoice(FreeVocDeviceID).UsedDevID = pTrunkVoc->deviceID; 

			DrawMain_VocInfo ( pTrunkVoc );

			My_DualLink ( &FreeVocDeviceID, &pTrunkVoc->deviceID ); 

			if ( pTrunkVoc->deviceID.m_s16DeviceSub == XMS_DEVSUB_ANALOG_TRUNK )
			{
				SetGtD_AnalogTrunk(&FreeVocDeviceID);		// prepare for get Busy Tone
			}
			
			TRACE("*****(DSP: %d, CH: %d) MTVOC Link to Voice(DSP: %d, CH: %d)\n", pTrunkVoc->deviceID.m_s8ModuleID, pTrunkVoc->deviceID.m_s16ChannelID, FreeVocDeviceID.m_s8ModuleID, FreeVocDeviceID.m_s16ChannelID );
			Change_EM_State ( pTrunkVoc, TRK_EMVOC_NOTIRY );
		}		
	}
}

//analog EM trunk proc routine
void EMWork ( TRUNK_STRUCT *pOneTrunk, Acs_Evt_t *pAcsEvt )
{
	if ( XMS_EVT_RESET_DEVICE == pAcsEvt->m_s32EventType )
	{
		Change_EM_State ( pOneTrunk, TRK_EMVOC_FREE );
	}

	//EM channel send M MSG or E MSG forwardly
	if ( XMS_EVT_SETPARAM == pAcsEvt->m_s32EventType )
	{
		switch(pOneTrunk->State)
		{
			case TRK_EMVOC_FREE:
					//TRACE("*****(DSP: %d, CH: %d)XMS_EVT_SETPARAM DCS_CONNECT. \n", pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID );
					//EmChConnectProc( pOneTrunk, pAcsEvt );					
					//Change_EM_State ( pOneTrunk, TRK_EMVOC_FINISH );
				break;

			case TRK_EMVOC_FINISH:
					//TRACE("*****(DSP: %d, CH: %d)XMS_EVT_SETPARAM DCS_FREE. \n", pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID );
					//EmChFreeProc( pOneTrunk, pAcsEvt );
					//Change_EM_State ( pOneTrunk, TRK_EMVOC_FREE );
				break;
		}
	}
	else if ( XMS_EVT_DEVICESTATE == pAcsEvt->m_s32EventType )  //the EM channel state is changed by receiving M MSG or E MSG
	{
		char str[100] = {0};
		Acs_GeneralProc_Data * pGeneralData = NULL;
		pGeneralData = (Acs_GeneralProc_Data *)FetchEventData(pAcsEvt);
		
		MT_EM_CH stMtEmCH;	
		TRUNK_STRUCT *pTrunkVoc = NULL;
		TRUNK_STRUCT *pTrunkE1 = NULL;
		VOICE_STRUCT *pMTVocVoice = NULL;
		DeviceID_t FreeVocDeviceID;
		
		if ( 0 != GetMtEmCH( &stMtEmCH, pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID ))
		{
			return;
		}

		switch ( pGeneralData->m_s32DeviceState )
		{
			//the EM channel state is changed from DCS_CONNECT to DCS_FREE by receiving E MSG or Sending M MSG forwardly
			case DCS_FREE:							
			{
				TRACE("*****(DSP: %d, CH: %d) MTEM Recv DCS_FREE. \n", pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID );

				//the EM channel that it's MTVOC link to the E1 interface, it's channel state changed from DCS_CONNECT to DCS_FREE 
				if ( pOneTrunk->deviceID.m_s8ModuleID == stMtEmCH.m_stE1Info.m_u8EM_DSPID
					&& pOneTrunk->deviceID.m_s16ChannelID == stMtEmCH.m_stE1Info.m_u16EM_CH)
				{
				    //the endpoint of E1
					pTrunkVoc = &AllDeviceRes[stMtEmCH.m_stE1Info.m_u8EMVOC_DSPID].pTrunk[stMtEmCH.m_stE1Info.m_u16EM_VOC_CH];
					if ( NULL != pTrunkVoc)
					{
						pTrunkE1 = &M_OneTrunk( pTrunkVoc->VocDevID );
						if ( NULL != pTrunkE1 )
						{
							//E1 interface Clear call and unlink to the E1_MTVOC
							XMS_ctsClearCall(g_acsHandle, &pTrunkE1->deviceID, 0, NULL );
							TRACE("*****(DSP: %d, CH: %d) MTEM Clear Call. \n", pTrunkE1->deviceID.m_s8ModuleID, pTrunkE1->deviceID.m_s16ChannelID );
							My_DualUnlink ( &pTrunkE1->deviceID, &pTrunkVoc->deviceID );
							TRACE("*****(DSP: %d, CH: %d) MTEM Unlink MTVOC dev(DSP: %d, CH: %d). \n", pTrunkE1->deviceID.m_s8ModuleID, pTrunkE1->deviceID.m_s16ChannelID, pTrunkVoc->deviceID.m_s8ModuleID, pTrunkVoc->deviceID.m_s16ChannelID );
							
							//memset(&pTrunkE1->VocDevID, 0, sizeof(DeviceID_t) );
							memset(&pTrunkVoc->VocDevID, 0, sizeof(DeviceID_t) );
							
							ResetTrunk( pTrunkE1, NULL );						
							//ResetTrunk( pTrunkVoc, NULL );						
						}
					}
				}
				//the EM channel that it's MTVOC connect to the EM's MTVOC with RJ11, it's channel state changed from DCS_CONNECT to DCS_FREE 
				else if ( pOneTrunk->deviceID.m_s8ModuleID == stMtEmCH.m_stEMInfo.m_u8EM_DSPID
					&& pOneTrunk->deviceID.m_s16ChannelID == stMtEmCH.m_stEMInfo.m_u16EM_CH)
				{
					//the endpoint of EM Device
					pTrunkVoc = &AllDeviceRes[stMtEmCH.m_stEMInfo.m_u8EMVOC_DSPID].pTrunk[stMtEmCH.m_stEMInfo.m_u16EM_VOC_CH];
					if ( NULL != pTrunkVoc)
					{
						//EM MTVOC stop play and unlink to the voice device
						ControlPlay_t controlPlay;

						memset(&controlPlay, 0, sizeof(ControlPlay_t) );
						controlPlay.m_u16ControlType = XMS_STOP_PLAY;

						pMTVocVoice = &M_OneVoice( pTrunkVoc->VocDevID );
						if ( NULL != pMTVocVoice)
						{
							XMS_ctsControlPlay(g_acsHandle, &pTrunkVoc->VocDevID, &controlPlay,NULL );				
							TRACE("*****(DSP: %d, CH: %d) MTEM Stop play. \n", pMTVocVoice->deviceID.m_s8ModuleID, pMTVocVoice->deviceID.m_s16ChannelID );
							
							My_DualUnlink ( &pMTVocVoice->deviceID, &pTrunkVoc->deviceID );
							TRACE("*****(DSP: %d, CH: %d) MTEM Unlink MTVOCVoice dev(DSP: %d, CH: %d). \n", pTrunkVoc->deviceID.m_s8ModuleID, pTrunkVoc->deviceID.m_s16ChannelID, pMTVocVoice->deviceID.m_s8ModuleID, pMTVocVoice->deviceID.m_s16ChannelID );
							
							memset(&pTrunkVoc->VocDevID, 0, sizeof(DeviceID_t) );
							memset(&pMTVocVoice->UsedDevID, 0, sizeof(DeviceID_t) );
							
							pTrunkVoc->u8PlayTag = 0;							
						}
					}
				}
				break;
			}
			//the EM channel state is changed from DCS_CONNECT to DCS_FREE by receiving E MSG or Sending M MSG forwardly
			case DCS_CONNECT: 
			{
				TRACE("*****(DSP: %d, CH: %d) MTEM Recv DCS_CONNECT. \n", pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID );

				//the EM channel that it's MTVOC link to the E1 interface, it's channel state changed from DCS_FREE to  DCS_CONNECT
				if ( pOneTrunk->deviceID.m_s8ModuleID == stMtEmCH.m_stE1Info.m_u8EM_DSPID
					&& pOneTrunk->deviceID.m_s16ChannelID == stMtEmCH.m_stE1Info.m_u16EM_CH)
				{
				    //the endpoint of E1
					pTrunkVoc = &AllDeviceRes[stMtEmCH.m_stE1Info.m_u8EMVOC_DSPID].pTrunk[stMtEmCH.m_stE1Info.m_u16EM_VOC_CH];
					if ( NULL != pTrunkVoc)
					{
						//TRACE("*****(DSP: %d, CH: %d)Recv DCS_CONNECT. \n", pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID );						
					}
				}
				//the EM channel that it's MTVOC connect to the EM's MTVOC with RJ11, it's channel state changed from DCS_FREE to DCS_CONNECT 
				else if ( pOneTrunk->deviceID.m_s8ModuleID == stMtEmCH.m_stEMInfo.m_u8EM_DSPID
					&& pOneTrunk->deviceID.m_s16ChannelID == stMtEmCH.m_stEMInfo.m_u16EM_CH)
				{
					//the endpoint of EM Device
					pTrunkVoc = &AllDeviceRes[stMtEmCH.m_stEMInfo.m_u8EMVOC_DSPID].pTrunk[stMtEmCH.m_stEMInfo.m_u16EM_VOC_CH];
					if ( NULL != pTrunkVoc)
					{
						//EM MTVOC finding a free voice to link to
						if ( SearchOneFreeVoice( pTrunkVoc,  &FreeVocDeviceID ) >= 0 )
						{
							pTrunkVoc->u8PlayTag = 16;
						
							pTrunkVoc->VocDevID = FreeVocDeviceID;
						
							M_OneVoice(FreeVocDeviceID).UsedDevID = pTrunkVoc->deviceID; 
						
							DrawMain_VocInfo ( pTrunkVoc );
						
							My_DualLink ( &FreeVocDeviceID, &pTrunkVoc->deviceID ); 
						
							if ( pTrunkVoc->deviceID.m_s16DeviceSub == XMS_DEVSUB_ANALOG_TRUNK )
							{
								SetGtD_AnalogTrunk(&FreeVocDeviceID);		// prepare for get Busy Tone
							}
							
							TRACE("*****(DSP: %d, CH: %d) MTVOC Link to Voice(DSP: %d, CH: %d)\n", pTrunkVoc->deviceID.m_s8ModuleID, pTrunkVoc->deviceID.m_s16ChannelID, FreeVocDeviceID.m_s8ModuleID, FreeVocDeviceID.m_s16ChannelID );
							Change_EM_State ( pTrunkVoc, TRK_EMVOC_NOTIRY );
						}
						//EmChConnectProc( pOneTrunk, pAcsEvt );
					}
				}
				break;
			}
		}
	}
}

//analog MTVOC trunk proc routine
void EMVocWork ( TRUNK_STRUCT *pOneTrunk, Acs_Evt_t *pAcsEvt )
{
	char FileName[260] = {0};
	
	if (pOneTrunk->State > TRK_EMVOC_FINISH)
		Change_EM_State ( pOneTrunk, TRK_EMVOC_FREE );

	switch(pOneTrunk->State)
	{
		case TRK_EMVOC_FREE:
			break;
			
		case TRK_EMVOC_NOTIRY:				
			if ( pAcsEvt->m_s32EventType == XMS_EVT_LINKDEVICE )	/*LinkDevice End*/
			{
				strcpy ( FileName, cfg_VocPath );
				strcat ( FileName, "\\ConfMusi.Pcm");
				pOneTrunk->u8PlayTag ++;
				PlayFile ( &pOneTrunk->VocDevID, FileName, pOneTrunk->u8PlayTag );
				TRACE("*****(DSP: %d, CH: %d) MTVOC play <%s>. \n", pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID, FileName);

				Change_EM_State ( pOneTrunk, TRK_EMVOC_PLAY );
			}
			break;
		case TRK_EMVOC_PLAY:
		{
			if ( CheckPlayEnd ( pOneTrunk, pAcsEvt) )	/*play end Event*/
			{		
				MT_EM_CH stMtEmCH;	
				TRUNK_STRUCT *pTrunkVoc = NULL;
				
				if ( 0 != GetMtEmCH( &stMtEmCH, pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID ))
				{
					return;
				}

				pTrunkVoc = &AllDeviceRes[stMtEmCH.m_stE1Info.m_u8EM_DSPID].pTrunk[stMtEmCH.m_stE1Info.m_u16EM_CH];
				if ( NULL != pTrunkVoc)
				{
					//EM MTVOC play complete and tell E1_MTVOC to unlink with E1 interface
					NotifyEMDev( &pTrunkVoc->deviceID, MTVOC_EM_TYPE_E, FALSE );
				}
				TRACE("*****(DSP: %d, CH: %d) MTVOC play file end and notify. \n", pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID);

				///////////////////////////////////////////////
				pOneTrunk->u8PlayTag = 0;
				
				My_DualUnlink ( &pOneTrunk->VocDevID, &pOneTrunk->deviceID );

				memset(&pOneTrunk->VocDevID, 0, sizeof(DeviceID_t) );
				
				TRACE("*****(DSP: %d, CH: %d) MTVOC Unlink MTVOC and voice(DSP: %d, CH: %d). \n", pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID,pOneTrunk->VocDevID.m_s8ModuleID, pOneTrunk->VocDevID.m_s16ChannelID );
				///////////////////////////////////////////////
				
				Change_EM_State ( pOneTrunk, TRK_EMVOC_FINISH );
			}

		}
			break;
		case TRK_EMVOC_FINISH:
		{
			TRACE("*****(DSP: %d, CH: %d) MTVOC Reset the trunk. \n", pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID);
			ResetTrunk(pOneTrunk,pAcsEvt);
			Change_EM_State ( pOneTrunk, TRK_EMVOC_FREE );				
		}
			break;
	}		
}

//signal trunk proc routine
void TrunkWork ( TRUNK_STRUCT *pOneTrunk, Acs_Evt_t *pAcsEvt )
{
	Acs_CallControl_Data *	pCallControl = NULL;
	DeviceID_t				FreeVocDeviceID;
	char					TmpGtd;
	Acs_IO_Data				*pIOData = NULL;


	if ( pAcsEvt->m_s32EventType == XMS_EVT_CLEARCALL )	/*clear Event*/
	{
		if ( (pOneTrunk->State != TRK_FREE) && (pOneTrunk->State != TRK_WAIT_REMOVE) )
		{
			//notify the EM that the MTVOC has to stop to transmit data, because of CLEARCALL
			NotifyEMDev( &pOneTrunk->VocDevID,MTVOC_EM_TYPE_D, FALSE );
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

		if ( pOneTrunk->deviceID.m_s16DeviceSub == XMS_DEVSUB_ANALOG_TRUNK )
		{
			unsigned char	 *p;
			pIOData = (Acs_IO_Data *)FetchEventData(pAcsEvt);

			p = My_GetFskCode ( pAcsEvt );
			if ( p != NULL )
			{
				ConvertRawFskToCallerID ( p,pIOData->m_u16IoDataLen, pOneTrunk->CallerCode, 20 );
			}	
		}

		if ( pAcsEvt->m_s32EventType == XMS_EVT_CALLIN )	/* Call In Event */
		{
			// release the Voice for get FSK
			if ( pOneTrunk->deviceID.m_s16DeviceSub == XMS_DEVSUB_ANALOG_TRUNK )	 
			{
				My_DualUnlink ( &pOneTrunk->VocDevID, &pOneTrunk->deviceID );

				FreeOneFreeVoice (  &pOneTrunk->VocDevID );

				memset ( &M_OneVoice(pOneTrunk->VocDevID).UsedDevID,	0, sizeof(DeviceID_t) );		// 0: didn't alloc Device
				memset ( &pOneTrunk->VocDevID, 0, sizeof(DeviceID_t) );		// 0: didn't alloc Device
				DrawMain_VocInfo ( pOneTrunk );
			}

			pCallControl = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);

			XMS_ctsAlertCall ( g_acsHandle, &pOneTrunk->deviceID, NULL );

			XMS_ctsAnswerCallIn ( g_acsHandle, &pOneTrunk->deviceID, NULL );

			if ( pOneTrunk->deviceID.m_s16DeviceSub != XMS_DEVSUB_ANALOG_TRUNK )
			{
				sprintf ( pOneTrunk->CalleeCode, pCallControl->m_s8CalledNum );
				sprintf ( pOneTrunk->CallerCode, pCallControl->m_s8CallingNum );
			}

			DrawMain_CallInfo( pOneTrunk );
			
			TRACE("*****************************************************************\n\n");
			TRACE("*****(DSP: %d, CH: %d) E1 Call In. \n", pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID);
			Change_State ( pOneTrunk, TRK_WAIT_ANSWERCALL );
		}
		break;

	case TRK_WAIT_ANSWERCALL:
		// Special code for CAS(SS1)
		SpecialForCas(pOneTrunk,pAcsEvt);

		if ( pAcsEvt->m_s32EventType == XMS_EVT_ANSWERCALL )	/*Answer Call In End Event*/
		{
			pCallControl = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);

			//Finding a free EM Group to bind with this digital interface after Answering the call in
			if ( SearchOneFreeMTVOC ( pOneTrunk,  &FreeVocDeviceID ) >= 0 )
			{
				TRACE("*****(DSP: %d, CH: %d) E1 Find a MTVOC(DSP: %d, CH: %d)\n", pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID, FreeVocDeviceID.m_s8ModuleID, FreeVocDeviceID.m_s16ChannelID);
				pOneTrunk->u8PlayTag = 16;

				pOneTrunk->VocDevID = FreeVocDeviceID;

				M_OneTrunk(FreeVocDeviceID).VocDevID = pOneTrunk->deviceID; 

				//DrawMain_VocInfo ( pOneTrunk );

				//link to the E1_MTVOC, so can transmit voice via it
				My_DualLink ( &FreeVocDeviceID, &pOneTrunk->deviceID ); 

				if ( pOneTrunk->deviceID.m_s16DeviceSub == XMS_DEVSUB_ANALOG_TRUNK )
				{
					SetGtD_AnalogTrunk(&FreeVocDeviceID);		// prepare for get Busy Tone
				}
				
				TRACE("*****(DSP: %d, CH: %d) E1 ANSWERCALL\n", pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID);
				Change_State ( pOneTrunk, TRK_WAIT_LINKOK );
			}
		}
		break;

	case TRK_WAIT_LINKOK:
		if ( pAcsEvt->m_s32EventType == XMS_EVT_LINKDEVICE )	/*LinkDevice End*/
		{
			TRACE("*****(DSP: %d, CH: %d) E1 TRUNK LINK MTVOC(DSP: %d, CH: %d) OK\n", pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID, pOneTrunk->VocDevID.m_s8ModuleID, pOneTrunk->VocDevID.m_s16ChannelID );

			//tell the EM_EM & EM_MTVOC to start to listen to voice when linking to E1_MTVOC with digital interface
			NotifyEMDev( &pOneTrunk->VocDevID, MTVOC_EM_TYPE_D );
			
		    //XMS_ctsSetDevTimer( g_acsHandle, &pOneTrunk->deviceID, 60000 );  //time out after 60 seconds and clear call
			Change_State ( pOneTrunk, TRK_MT_COM );
		}
		break;

	case TRK_MT_COM:
		if ( pAcsEvt->m_s32EventType == XMS_EVT_DEV_TIMER )	/*play end Event*/
		{
			TRACE("*****(DSP: %d, CH: %d) TRK_MT_COM \n", pOneTrunk->deviceID.m_s8ModuleID, pOneTrunk->deviceID.m_s16ChannelID);
			XMS_ctsClearCall ( g_acsHandle, &pOneTrunk->deviceID, 0, NULL );

			Change_State ( pOneTrunk, TRK_HANGON );
		}

		break;
	}
}


