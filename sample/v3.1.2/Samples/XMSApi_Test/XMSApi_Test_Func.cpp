#include "stdafx.h"
#include "XMSApi_Test.h"
#include "XMSApi_TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "XMSApi_PlaySet.h"
#include "XMSApi_RecordSet.h"
#include "XMSApi_ControlPlay.h"
#include "XMSApi_ControlRecord.h"
#include "XMSApi_ConfParam.h"
#include "XMSApi_Test_ParamVoice.h"
#include "XMSApi_BuildIndex.h"
#include "XMSApi_SendIOData.h"
#include "XMSApi_ParamCAS.h"
#include "DialogAnaTrunk.h"
#include "DialogAnalogUser.h"
#include "DlgParamType.h"
#include "DlgRtpxInput.h"
#include "DlgRtpxOutput.h"
#include "DlgRtpxMixer.h"
#include "DlgRtpxAddr.h"
#include "DlgMediaExParam.h"
#include "DlgMediaExInput.h"
#include "DlgMediaExOutput.h"
#include "DlgSetVoIPParams.h"

#include "DialogFskSet.h"
#include "DialogFlashSet.h"
#include "DialogGtdSet.h"
#include "DialogGtgSet.h"
#include "DialogATrunkFlash.h"
#include "Dialog3GFaxTone.h"
#include "DialogActiveMemSet.h"
#include "DlgFaxBpsParam.h"
#include "DlgFaxMultiFileParam.h"

#include "RecCSPDlg.h"
#include "CSPPlayDlg.h"
#include "DialogATrunkEM.h"
#include "DialogSVDSet.h"
#include "ConfParaSetDlg.h"
#include "ModRelateDlg.h"

#include "DialogFaxHeader.h"
#include "FaxECMDlg.h"

#include "CtxRegDlg.h"
#include "CtxLinkDlg.h"
#include "CtxAppData.h"
#include "txLinkCtxDlg.h"
#include "3gppConfgDlg.h"
#include "SendSignalData.h"
#include "CLKDialog.h"
#include "BoardSetMainClockDlg.h"
#include "DlgBoardVadMinLevelParam.h"
#include "DlgBoardCommonParam.h"
#include "DlgSS7SS7RawFrame.h"  // author:chenz 
#include "DlgUserReadXmsBoardInfo.h" // author:chenz 
#include "DlgCmdParamDataCAS.h"  // author:chenz 
#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"

#include "XMSApi_Test_Sub.h"
#include "XMSApi_Test_Event.h"
#include "XMSApi_Test_String.h"
#include "XMSApi_Test_Func.h"

#include "XMS_Test_ParamVoip.h"
#include "XMSApi_3GPP_BuildIndex.h"
#include "XMSApi_3GPPPlaySet.h"
#include "XMSApi_Control3GPPPlay.h"
#include "XMSApi_Record3GPPSet.h"
#include "XMSApi_3GPPControlRecord.h"
#include "ARecVoltageSetDlg.h"
#include "RecModModeSetDlg.h"
#include "ITPISDN.h"
#include "DSS1CallParamDlg.h"
#include "LedDlg.h"

#include "..\CAS_Common_Code\CAS_Common_Cfg.h"

#define RTP_PORT_BASE(portbase, unit_id)	(DJ_U16)(portbase + (unit_id-1)*100)
extern int FindOpenDevice(DeviceID_t	*pDev);

// ----------------------------------------------------------
extern ACSHandle_t		g_acsHandle;
extern bool				bStartWorkFlag;

extern	int		iNowOpIndex;
extern	int		iOpenedIndex1;
extern	int		iOpenedIndex2;
extern	int		iOpenedIndex3;

extern	int		TotalDevRes;
extern	int		TotalDevOpened;
extern	TYPE_MY_DEVICE_STRUCT	*pDevRes;
extern	TYPE_MY_DEVICE_STRUCT	DevOpened[MAX_DEVICE_ALLOW_OPEN];
extern	App_Data_Struct         g_stAppData;

extern	CXMSApi_TestDlg	*pdlg;

extern int		iComboParam;
extern int		iComboGetParam;

extern char		ParamTypeStr[MAX_PARAMETER_TYPE][32];
extern char		cfg_IniName[MAX_FILE_NAME_LEN];
extern FILE * g_cspPlayFp;
extern FILE * g_cspRecordFp;
extern char   g_szCSPPlayFile[MAX_PATH];
extern char   g_szCSPRecordFile[MAX_PATH];

extern int		g_iProtocol;
extern int		g_Select;
extern bool   g_bIsExPathTo260;

extern int g_iTimerType;    //0: Timer, 1: Dev Timer
extern int g_iElapseTime;   
extern int g_NetRef;

DJ_U8 g_u8ModuleType = 2;
DJ_U8 g_u8ModuleUnitID  = 1;

// ----------------------------------------------------------
PlayProperty_t		g_PlayProperty;
Play3gppProperty_t	   g_Play3gppProperty;

RecordProperty_t	   g_RecordProperty;
Record3gppProperty_t   g_Record3gppProperty;

ControlPlay_t		    g_ControlPlay;
Control3gppPlay_t		g_Control3GPPPlay;

ControlRecord_t		    g_ControlRecord;
Control3gppRecord_t		g_Control3GPPRecord;

CmdParamData_Conf_t		g_Conf_Param;

CmdParamData_Voice_t	g_Voice_Param;

PlayProperty_t		 g_BuildIndexProperty;
Play3gppProperty_t   g_Build3gppIndexProperty;

CmdParamData_CAS_t	g_CAS_Param;

CmdParamData_AnalogTrunk_t        g_AnalogTrunk;
RecordCSPProperty_t               g_RecCSP;
CSPPlayProperty_t                 g_PlayCSP;
CmdParamData_AnalogUser_t         g_AnalogUser;

MixerControlParam_t					g_VoIP_Param;
Acs_VoIP_MediaInfo					g_VoIP_MediaInfo;
Acs_VoIP_RTPSESSION					g_RTP_Session;
Acs_VoIP_RTPADDR					g_RTP_Addr;
Acs_VoIP_RTPCODEC					g_RTP_Codec;
Acs_VoIP_RTPOpen					g_RTP_Open;

CmdParamData_FskParam_t           g_FskSet;
CmdParamData_FlashParam_t         g_FlashSet;
CmdParamData_GtdFreq_t            g_GtdFreq;
CmdParamData_GtdProtoType_t       g_GtdProto;
CmdParamData_GtgFreq_t            g_GtgFreq[4];
CmdParamData_GtgProtoType_t       g_GtgProto;
//CmdParam_ActiveMemDetectParam_t   g_ConfActiveMemParam;
CmdParam_VADMinDetectParam_t      g_VADMinLevelParam = {0};
CmdParam_BoardCommonParam_t       g_BoardCommonParm = {0};

CmdParamData_SS7RawFrame_t        g_SS7RawFrameParam ;  // author:chenz
Acs_ParamData_UserReadXmsBoardInfo g_UserReadXmsBoardInfo;  // author:chenz
CmdParamData_CAS_t                g_CmdParamDataCAS;  // author:chenz 
CmdParamData_CTCLKNET_t           g_CTCLK;

CmdParamData_AnalogTrunkFlash_t   g_ATrunkFlash;
ITP_3G_FaxToneStruct_t            g_3GFaxTone;
Acs_TransAddHeader	              g_FaxHeader;
Acs_AnalogEM_CMD                  g_ATrunkEM;
Acs_SetECM		                  g_FaxECMCmd;
Acs_SetFaxBps                     g_FaxBpsParam;
Acs_TransAddFile                  g_FaxMultiFileParam;

CmdParam_SilenceDetectParam_t     g_SVDCmd;
CmdParamConf_VadInterval_t        g_stParamConf;

CmdParamData_AnalogRecVoltage_t   g_AnalogRecVoltage;
DigRecSwitchMode                  g_RecModCfg;

ITP_Q931_CALL_PARAM               g_DSS1CallParam;
ITP_Q931_ORINUM_PARAM             g_DSS1OriNumParam;

UserLedCtrl                       g_LedCtrl={0};
DJ_U8                             g_u8LedDspUnit=0;
CLedDlg                           g_LedDlg;
ModRelateDlg                      g_GetRelateDlg;

DeviceID_t g_RecCSPDevID;
DeviceID_t g_PlayCSPDevID;


Dev_Codec_Info g_stCodec = {0};

ServerID_t g_stCSPServerID = {0} ;

/*标识是否启用录制码流命令*/
bool g_bIsRecordCodeStream = false;
bool g_bIsPlayCodeStream   = false;

/*下发获取3gp参数配置命令结构*/
Get3gppCfg_t          g_Get3gpCfg;

ServerID_t		cfg_cDSPIpAddr[128];

// ----------------------------------------------------------
void	InitVar_Func(void)
{
	memset ( &g_PlayProperty, 0, sizeof(PlayProperty_t) );

	memset ( &g_RecordProperty, 0, sizeof(RecordProperty_t) );

	memset ( &g_ControlPlay, 0, sizeof(ControlPlay_t) );

	memset ( &g_ControlRecord, 0, sizeof(ControlRecord_t) );

	memset ( &g_Conf_Param, 0, sizeof (CmdParamData_Conf_t) );
	g_Conf_Param.m_u8InputOpt = g_Conf_Param.m_u8OutputOpt = 1;

	memset ( &g_Voice_Param, 0, sizeof (CmdParamData_Voice_t) );

	memset ( &g_BuildIndexProperty, 0, sizeof (PlayProperty_t) );

	memset(&g_AnalogTrunk,0,sizeof(g_AnalogTrunk));
	memset(&g_AnalogUser,0,sizeof(g_AnalogUser));

	// read g_CAS_Param from "c:\\DJKeygoe\\XMS_CAS_Cfg.INI"
	long	r;
	char	TmpStr[64];

	r = CAS_Common_Cfg_ReadCfg ( &g_CAS_Param );
	if ( r != 0 )
	{
		sprintf ( TmpStr, "Error in Read CAS Cfg! return = %d", r );
		AfxMessageBox ( TmpStr );
	}
}

void DoShowMessage ( char * MsgStr)
{
	AfxMessageBox ( MsgStr );
	AddMsg ( MSG_TYPE_OTHER, MsgStr );
}

bool	CheckOpenDevice ( int iIndex, bool	bIsDev1 )
{
	char		MsgStr[160];

	if ( iIndex == -1 )
	{
		if ( bIsDev1 )
			sprintf ( MsgStr, "Select an Opened Dev1 First!" );
		else
			sprintf ( MsgStr, "Select an Opened Dev2 First!" );

		AfxMessageBox ( MsgStr );
		AddMsg ( MSG_TYPE_OTHER, MsgStr );
		return false;
	}

	if ( (iIndex < 0) || (iIndex >= TotalDevOpened) )
	{
		sprintf ( MsgStr, "Selected Opened Device overflow. Index = %d.", iIndex );
		AfxMessageBox ( MsgStr );
		AddMsg ( MSG_TYPE_OTHER, MsgStr );
		return false;
	}

	return true;
}

bool	CheckOpenDeviceForVoIP (int iIndex )
{
	char		MsgStr[160];

	if ( iIndex == -1)
	//( DevOpened[iIndex].DevID.m_s16DeviceMain != XMS_DEVMAIN_VOICE )
	{
		
		sprintf ( MsgStr, "Select an Opened Dev3 First!" );
		
		AfxMessageBox ( MsgStr );
		AddMsg ( MSG_TYPE_OTHER, MsgStr );
		return false;
	}

	return true;
}



// --------------------------------------------------------------------
// normal 
// --------------------------------------------------------------------
void	DoFunc_GetDeviceList (void)
{
	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	return;

	r = XMS_acsGetDeviceList ( g_acsHandle, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_acsGetDeviceList() FAIL!", r );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_acsGetDeviceList() OK!" );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_OpenDevice(void)
{
	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	return;

	if ( iNowOpIndex == -1 )
	{
		sprintf ( MsgStr, "Select a Device First!" );
		AfxMessageBox ( MsgStr );
		AddMsg ( MSG_TYPE_OTHER, MsgStr );
		return;
	}

	if ( (iNowOpIndex < 0) || (iNowOpIndex >= TotalDevRes) )
	{
		sprintf ( MsgStr, "Selected Device overflow. iIndex = %d.", iNowOpIndex );
		AfxMessageBox ( MsgStr );
		AddMsg ( MSG_TYPE_OTHER, MsgStr );
		return;
	}

	if ( XMS_DEVMAIN_BOARD == pDevRes[iNowOpIndex].DevID.m_s16DeviceMain )
	{
		CBoardSetMainClockDlg dlg;
		
		if ( IDOK == dlg.DoModal() && XMS_BOARD_EXT_TYPE_CLOCK == g_stBoardPrivateExt_Data.m_u32ExtType )
		{
			DJ_U8       u8Buf[200] = {0};
			PrivateData_t  * pPDataHead       = (PrivateData_t *)u8Buf;
			Acs_BoardPrivateExt_Data * pPData = (Acs_BoardPrivateExt_Data*)(pPDataHead+1);
			
			pPDataHead->m_u32DataSize = sizeof(PrivateData_t) + sizeof( Acs_BoardPrivateExt_Data );

			memcpy(pPData, &g_stBoardPrivateExt_Data, sizeof(g_stBoardPrivateExt_Data) );
			r = XMS_ctsOpenDevice ( g_acsHandle, &pDevRes[iNowOpIndex].DevID, (PrivateData_t *)u8Buf );
		}
		else
		{
			r = XMS_ctsOpenDevice ( g_acsHandle, &pDevRes[iNowOpIndex].DevID, NULL );
		}
	}
	else if(XMS_DEVMAIN_VOIP==pDevRes[iNowOpIndex].DevID.m_s16DeviceMain)
	{
		BOOL bControlRtp = ((CButton*)pdlg->GetDlgItem(IDC_AUTORTP))->GetCheck();
		VoIPOpenPrivate_t pVoIPOpenHead;
		pVoIPOpenHead.m_u8RtpMode = bControlRtp?1:0;
		PrivateData_t* pPDataHead = (PrivateData_t *)&pVoIPOpenHead;
		
		pPDataHead->m_u32DataSize = sizeof(VoIPOpenPrivate_t);
		
		r = XMS_ctsOpenDevice ( g_acsHandle, &pDevRes[iNowOpIndex].DevID, pPDataHead );
	}
	else
	{
		r = XMS_ctsOpenDevice ( g_acsHandle, &pDevRes[iNowOpIndex].DevID, NULL );
	}

	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsOpenDevice() FAIL! (%s)", r, GetString_DeviceAll (&pDevRes[iNowOpIndex].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsOpenDevice() OK! (%s)", GetString_DeviceAll (&pDevRes[iNowOpIndex].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}

#ifdef	DEBUG_IN_HOME_NOTEBOOK
	// for-test
	OpenDeviceOK ( &pDevRes[iNowOpIndex].DevID );
	//
#endif
}

void	DoFunc_CloseDevice(void)
{
	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	return;

	if(g_Select == 0)
	{
		if ( !CheckOpenDevice (iOpenedIndex1) )
			return;

		r = XMS_ctsCloseDevice ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsCloseDevice() FAIL! (%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsCloseDevice() OK! (%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
	else
	{
		if ( !CheckOpenDeviceForVoIP (iOpenedIndex3) )
			return;

		r = XMS_ctsCloseDevice ( g_acsHandle, &DevOpened[iOpenedIndex3].DevID, NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsCloseDevice() FAIL! (%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsCloseDevice() OK! (%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}

	/*int iRow = pdlg->m_ListDevOpened.GetCurSel ();
		
	if(DevOpened[iRow].DevID.m_s16DeviceMain == XMS_DEVMAIN_CTBUS_TS
		|| DevOpened[iRow].DevID.m_s16DeviceMain == XMS_DEVMAIN_VOIP)
	{		
		pdlg->GetDlgItem ( IDC_EDIT_DEVICE3 )->SetWindowText ("");
	}*/

	
#ifdef	DEBUG_IN_HOME_NOTEBOOK
	// for-test
//	CloseDeviceOK ( &DevOpened[iRow].DevID );
	//
#endif
}

void	DoFunc_ResetDevice(void)
{
	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	return;

	if(g_Select == 0 )
	{
		if ( !CheckOpenDevice (iOpenedIndex1) )
			return;
		r = XMS_ctsResetDevice ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, NULL );
			if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsResetDevice() FAIL! (%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsResetDevice() OK! (%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
	else
	{
		if ( !CheckOpenDevice (iOpenedIndex3) )
			return;
		r = XMS_ctsResetDevice ( g_acsHandle, &DevOpened[iOpenedIndex3].DevID, NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsResetDevice() FAIL! (%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsResetDevice() OK! (%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}

	//if ( !CheckOpenDevice (iOpenedIndex1) )
	//	return;

	
	
}

void	DoFunc_GetDeviceState(void)
{
	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	r = XMS_ctsGetDevState ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsGetDevState() FAIL! (%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsGetDevState() OK! (%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_GetDeviceStateVoIP(void)
{
	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex3) )
		return;

	r = XMS_ctsGetDevState ( g_acsHandle, &DevOpened[iOpenedIndex3].DevID, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsGetDevState() FAIL! (%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsGetDevState() OK! (%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}
// --------------------------------------------------------------------
//  end of normal 
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// call control
// --------------------------------------------------------------------
void	DoFunc_AlertCall(void)
{
	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	return;

	if( g_Select == 0 )
	{
		if ( !CheckOpenDevice (iOpenedIndex1) )
			return;
		r = XMS_ctsAlertCall ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, NULL );
			if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsAlertCall() FAIL! (%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsAlertCall() OK! (%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
	else
	{
		if ( !CheckOpenDevice (iOpenedIndex3) )
			return;
		r = XMS_ctsAlertCall ( g_acsHandle, &DevOpened[iOpenedIndex3].DevID, NULL );
			if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsAlertCall() FAIL! (%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsAlertCall() OK! (%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
	

}

typedef struct ITP_RTP_CODEC_TAG
{
    DJ_U8	u8CodecType;		// codec type
    DJ_U8	u8PayloadType;		// rtp payload type
    DJ_S8	s8MimeSubtype[10];	// MIME subtype name (used as sdp encoding name)
    DJ_S8	s8H245Name[50];		// h.245 capability name
} ITP_RTP_CODEC;

ITP_RTP_CODEC rtp_codec[] =
{
    // audio capabilities
    {	// g.711 u-law
		VOIP_MEDIA_AUDIO_PCMU,	// media id
		0,						// rtp payload type
		"PCMU",					// MIME subtype name
		"g711Ulaw64k"			// h.245 capability name
    },
    {	// g.711 a-law
		VOIP_MEDIA_AUDIO_PCMA,	// media id
		8,						// rtp payload type
		"PCMA",					// MIME subtype name
		"g711Alaw64k"			// h.245 capability name
	},
	{	// g.723
		VOIP_MEDIA_AUDIO_G723,	// media id
		4,						// rtp payload type
		"G723",					// MIME subtype name
		"g7231"					// h.245 capability name
	},
	{	// g.729
		VOIP_MEDIA_AUDIO_G729,	// media id
		18,						// rtp payload type
		"G729",					// MIME subtype name
		"g729"					// h.245 capability name (prefix for g729, g729AnnexA, g729wAnnexB, g729AnnexAwAnnexB)
	},
	{	// amr-nb
		VOIP_MEDIA_AUDIO_AMR,	// media id
		96,						// rtp payload type (dynamic)
		"AMR",					// MIME subtype name
		"amr"					// h.245 capability name
	},
	/*	{	// t.38/rtp
	    VOIP_MEDIA_AUDIO_T38,	// media id
	    97,						// rtp payload type (dynamic)
	    "t38",					// MIME subtype name
	    "t38fax"				// h.245 capability name
    },*/
// video capabilities
	{	// h.261
		VOIP_MEDIA_VIDEO_H261,	// media id
		31,						// rtp payload type
		"H261",					// MIME subtype name
		"h261VideoCapability"	// h.245 capability name 
	},
	{	// h.263
		VOIP_MEDIA_VIDEO_H263,	// media id
		34,						// rtp payload type
		"H263",					// MIME subtype name
		"h263VideoCapability"	// h.245 capability name 
	},
	{	// h.263+
		VOIP_MEDIA_VIDEO_H263P,	// media id
		100,					// rtp payload type (dynamic)
		"H263-1998",			// MIME subtype name
		"h263VideoCapability98"	// h.245 capability name 
	},
	{	// mpeg-4/visual
		VOIP_MEDIA_VIDEO_MPEG4,	// media id
		101,					// rtp payload type (dynamic)
		"MP4V-ES",				// MIME subtype name
		"genericVideoCapability"// h.245 capability name 
	},
	{	// h.264
		VOIP_MEDIA_VIDEO_H264,	// media id
		102,					// rtp payload type (dynamic)
		"H264",					// MIME subtype name
		"h264VideoCapability"	// h.245 capability name 
	},
	// image capabilities
	{	// t.38/udptl
		VOIP_MEDIA_IMAGE_T38,	// media id
		0,						// no payload type for t.38/udptl
		"t38",					// MIME subtype name
		"t38fax"				// h.245 capability name
	}
};

void SetRtpMediaInfo(DeviceID_t *pRtpDev, Acs_VoIP_MediaInfo *pMediaInfo)
{
	Acs_VoIP_RTPSESSION session;
	Acs_VoIP_RTPADDR rtpAddr;
	Acs_VoIP_RTPCODEC rtpCodec;
	RetCode_t r;

	memset(&session, 0, sizeof(Acs_VoIP_RTPSESSION));
	session.m_u8Enable = 1;
	session.m_u8PayloadDtmf = pMediaInfo->payload_dtmf;
	session.m_u8PayloadTone = pMediaInfo->payload_tone;
	r = XMS_ctsSetParam(g_acsHandle, pRtpDev, VOIP_PARAM_RTPSESSION, sizeof(Acs_VoIP_RTPSESSION), &session);
	
	memset(&rtpAddr, 0, sizeof(Acs_VoIP_RTPADDR));
	rtpAddr.audio.m_u8Enable = 1;
	strcpy(rtpAddr.audio.m_s8IP, pMediaInfo->s8AudioAddress);
	rtpAddr.audio.m_u16Port = pMediaInfo->u16AudioPort;
	r = XMS_ctsSetParam(g_acsHandle, pRtpDev, VOIP_PARAM_RTPADDR, sizeof(Acs_VoIP_RTPADDR), &rtpAddr);

	memset(&rtpCodec, 0, sizeof(Acs_VoIP_RTPCODEC));
	for (int i=0; i<10; i++)
	{
		if (pMediaInfo->u8MediaCapList[0] == rtp_codec[i].u8CodecType)
		{
			rtpCodec.audio.m_u8TxPayloadType = rtp_codec[i].u8PayloadType;
			rtpCodec.audio.m_u8RxPayloadType = rtp_codec[i].u8PayloadType;
			break;
		}
	}	
	rtpCodec.audio.m_u8Enable = 1;
	rtpCodec.audio.m_u8TxCodec = pMediaInfo->u8MediaCapList[0];   // g.711 u-law	
	rtpCodec.audio.m_u8RxCodec = pMediaInfo->u8MediaCapList[0];
	r = XMS_ctsSetParam(g_acsHandle, pRtpDev, VOIP_PARAM_RTPCODEC, sizeof(Acs_VoIP_RTPCODEC), &rtpCodec);

}

void 	SetVOIPMediaInfo ( DeviceID_t *pVoipDev,  DeviceID_t *pRtpDev)
{
	Acs_VoIP_MediaInfo mediaInfo;
	RetCode_t r;

	if ( NULL == pVoipDev || NULL == pRtpDev)
		return ;

 	memset(&mediaInfo, 0, sizeof(Acs_VoIP_MediaInfo));
 	mediaInfo.payload_dtmf = 101;
 	mediaInfo.payload_tone = 0;
 	mediaInfo.u8AudioEnabled = 1;
 	strcpy(mediaInfo.s8AudioAddress, cfg_cDSPIpAddr[pRtpDev->m_s8ModuleID - 1].m_s8ServerIp);
 	mediaInfo.u16AudioPort = 10000+2*pRtpDev->m_s16ChannelID;
 	mediaInfo.u8MediaCapNum = 1;
 	mediaInfo.u8MediaCapList[0] = rtp_codec[0].u8CodecType;

 	r = XMS_ctsSetParam(g_acsHandle, pVoipDev, VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo), &mediaInfo);
}

void	DoFunc_AnswerCallIn(void)
{
	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	return;

	if(g_Select == 0 )
	{
		if ( !CheckOpenDevice (iOpenedIndex1) )
			return;

        BOOL bControlRtp = ((CButton*)pdlg->GetDlgItem(IDC_AUTORTP))->GetCheck();
        if(bControlRtp && DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain == XMS_DEVMAIN_VOIP)
        {
            if(!CheckOpenDevice (iOpenedIndex2) || DevOpened[iOpenedIndex2].DevID.m_s16DeviceMain != XMS_DEVMAIN_RTP)
            {
                AddMsg ( MSG_TYPE_FUNCTION, "Please select rtp device as device2" );
                return;
            }
            
            //set rtp;
            SetRtpMediaInfo(&DevOpened[iOpenedIndex2].DevID, (Acs_VoIP_MediaInfo*)DevOpened[iOpenedIndex1].pDevData);
            
            //set voip media info;
            SetVOIPMediaInfo(&DevOpened[iOpenedIndex1].DevID, &DevOpened[iOpenedIndex2].DevID);
        }

		r = XMS_ctsAnswerCallIn ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsAnswerCallIn() FAIL! (%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsAnswerCallIn() OK! (%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
	else
	{
		if ( !CheckOpenDevice (iOpenedIndex3) )
			return;

		r = XMS_ctsAnswerCallIn ( g_acsHandle, &DevOpened[iOpenedIndex3].DevID, NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsAnswerCallIn() FAIL! (%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsAnswerCallIn() OK! (%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
}

void	DoFunc_ClearCall(void)
{
	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	return;

	if(g_Select == 0)
	{
		if ( !CheckOpenDevice (iOpenedIndex1) )
			return;

		r = XMS_ctsClearCall ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, 0, NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsClearCall() FAIL! (%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsClearCall() OK! (%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
	else
	{
		if ( !CheckOpenDevice (iOpenedIndex3) )
			return;

		r = XMS_ctsClearCall ( g_acsHandle, &DevOpened[iOpenedIndex3].DevID, 0, NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsClearCall() FAIL! (%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsClearCall() OK! (%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
}

void	DoFunc_MakeCallOut(void)
{
	RetCode_t	r;
	char		MsgStr[160];
	char		Str_callingNum[ACS_MAX_CALL_NUM]; 
	char		Str_calledNum[ACS_MAX_CALL_NUM];
	char		m_strCalleeAddr[ACS_MAX_CALL_NUM];
	char		m_strCalleePort[ACS_MAX_CALL_NUM];
	if ( !bStartWorkFlag )	return;



	pdlg->GetDlgItem ( IDC_EDIT_CALLINGNUM )->GetWindowText ( Str_callingNum, ACS_MAX_CALL_NUM-1 );
	pdlg->GetDlgItem ( IDC_EDIT_CALLEDNUM )->GetWindowText ( Str_calledNum, ACS_MAX_CALL_NUM-1 );
	
	pdlg->GetDlgItem ( IDC_EDIT_CALLEE_ADDR )->GetWindowText ( m_strCalleeAddr, ACS_MAX_CALL_NUM-1 );
	pdlg->GetDlgItem ( IDC_EDIT_CALLEE_PORT )->GetWindowText ( m_strCalleePort, ACS_MAX_CALL_NUM-1 );

	if( g_Select == 0)
	//if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain == XMS_DEVMAIN_INTERFACE_CH )
	{
		if ( !CheckOpenDevice (iOpenedIndex1) )
			return;

		if (DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_VOIP )
		{
			r = XMS_ctsMakeCallOut ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, 
										Str_callingNum,	Str_calledNum,
										NULL );
			if ( r < 0 )
			{
				sprintf ( MsgStr, "X(%d) XMS_ctsMakeCallOut(%s,%s) FAIL! (%s)",
					r, Str_callingNum, Str_calledNum, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
				AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
			}
			else
			{
				sprintf ( MsgStr, "XMS_ctsMakeCallOut(%s,%s) OK! (%s)",
					Str_callingNum, Str_calledNum, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
				AddMsg ( MSG_TYPE_FUNCTION, MsgStr );

			if(DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain == XMS_DEVMAIN_INTERFACE_CH 
			&& DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub  == XMS_DEVSUB_ANALOG_USER)
			{
				char szDev2[128];
				pdlg->GetDlgItemText(IDC_EDIT_DEVICE2,szDev2,sizeof(szDev2));

				//if ( !CheckOpenDevice (iOpenedIndex2) )
				if( strlen(szDev2) == 0 )
				{
					sprintf ( MsgStr, "XMS_ctsMakeCallOut SendCallerSetTimer(%s) Failed! Voc is NULL",
					Str_callingNum );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
					return;
				}
				else
				{
					if ( 1 == ((CButton*)pdlg->GetDlgItem(IDC_RADIO_CALLER_FSK))->GetCheck() )
					{
						XMS_ctsSetDevTimer(g_acsHandle,&DevOpened[iOpenedIndex2].DevID,2000);						
					}
					else
					{
						XMS_ctsSetDevTimer(g_acsHandle,&DevOpened[iOpenedIndex2].DevID, 1000);
					}
				}
			}

			}
		}
		else
		{
            BOOL bControlRtp = ((CButton*)pdlg->GetDlgItem(IDC_AUTORTP))->GetCheck();
            if(bControlRtp)
            {
                if(!CheckOpenDevice (iOpenedIndex2) || DevOpened[iOpenedIndex2].DevID.m_s16DeviceMain != XMS_DEVMAIN_RTP)
                {
                    AddMsg ( MSG_TYPE_FUNCTION, "Please select rtp device as device2" );
                    return;
                }
            
                //set voip media info;
                SetVOIPMediaInfo(&DevOpened[iOpenedIndex1].DevID, &DevOpened[iOpenedIndex2].DevID);
            }

			// fill call parameters
			VoIPCallPrivate_t voipCallParam = {0};
			memset(&voipCallParam,0,sizeof(voipCallParam));
			voipCallParam.m_PrivateData.m_u32DataSize = sizeof(VoIPCallPrivate_t);
			voipCallParam.m_s32Protocol = g_iProtocol == 0 ? XMS_VOIP_PROTOCOL_H323 : XMS_VOIP_PROTOCOL_SIP;

			strcpy(voipCallParam.m_s8CalleeAddress, m_strCalleeAddr);
			if (strlen(m_strCalleeAddr) >0)
				voipCallParam.m_s32CalleePort = atol(m_strCalleePort);
			strcpy(voipCallParam.m_s8CalleeUserID, "");
			
			r = XMS_ctsMakeCallOut(g_acsHandle, &DevOpened[iOpenedIndex1].DevID, 
				Str_callingNum,	Str_calledNum, (PrivateData_t *)&voipCallParam);

			//--------------add end
			//r = XMS_ctsMakeCallOut ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, 
			//							Str_callingNum,	Str_calledNum,
			//							NULL );
			if ( r < 0 )
			{
				sprintf ( MsgStr, "X(%d) XMS_ctsMakeCallOut(%s,%s:%s) FAIL! (%s)",
					r, Str_callingNum, m_strCalleeAddr,m_strCalleePort, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
				AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
			}
			else
			{
				sprintf ( MsgStr, "XMS_ctsMakeCallOut(%s,%s:%s) OK! (%s)",
					Str_callingNum, m_strCalleeAddr,m_strCalleePort, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
				AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
			}
		}
	}
	else //if (DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain == XMS_DEVMAIN_VOIP )
	{
		if ( !CheckOpenDevice (iOpenedIndex3) )
			return;

		//--------------add begin

		// fill call parameters
		VoIPCallPrivate_t voipCallParam = {0};
		memset(&voipCallParam,0,sizeof(voipCallParam));
		voipCallParam.m_PrivateData.m_u32DataSize = sizeof(VoIPCallPrivate_t);
		voipCallParam.m_s32Protocol = g_iProtocol == 0 ? XMS_VOIP_PROTOCOL_H323 : XMS_VOIP_PROTOCOL_SIP;

		strcpy(voipCallParam.m_s8CalleeAddress, m_strCalleeAddr);
		if (strlen(m_strCalleeAddr) >0)
			voipCallParam.m_s32CalleePort = atol(m_strCalleePort);
		strcpy(voipCallParam.m_s8CalleeUserID, "");
		
		r = XMS_ctsMakeCallOut(g_acsHandle, &DevOpened[iOpenedIndex3].DevID, 
			"", "", (PrivateData_t *)&voipCallParam);

		//--------------add end
		//r = XMS_ctsMakeCallOut ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, 
		//							Str_callingNum,	Str_calledNum,
		//							NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsMakeCallOut(%s,%s) FAIL! (%s)",
				r, Str_callingNum, Str_calledNum, GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID) );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsMakeCallOut(%s,%s) OK! (%s)",
				Str_callingNum, Str_calledNum, GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID) );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
}

void	DoFunc_LinkDevice(void)
{
	RetCode_t	r;
	char		MsgStr[160];
	char		DevStr1[64], DevStr2[64],DevStr3[64];

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex2, false) )
		return;

	sprintf ( DevStr1, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID));
	sprintf ( DevStr2, GetString_DeviceAll (&DevOpened[iOpenedIndex2].DevID));
	sprintf ( DevStr3, GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID));

	if( g_Select == 0)
	{
		if ( !CheckOpenDevice (iOpenedIndex1) )
			return;

		r = XMS_ctsLinkDevice ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, &DevOpened[iOpenedIndex2].DevID, NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsLinkDevice() FAIL! src(%s) -> dst(%s)", 
				r, DevStr1, DevStr2  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsLinkDevice() OK! src(%s) -> dst(%s)", 
				DevStr1, DevStr2  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
	else
	{
		if ( !CheckOpenDevice (iOpenedIndex3) )
			return;

		r = XMS_ctsLinkDevice ( g_acsHandle, &DevOpened[iOpenedIndex3].DevID, &DevOpened[iOpenedIndex2].DevID, NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsLinkDevice() FAIL! src(%s) -> dst(%s)", 
				r, DevStr3, DevStr2  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsLinkDevice() OK! src(%s) -> dst(%s)", 
				DevStr3, DevStr2  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
}

// --------------------------------------------------------------------
// end of call control
// --------------------------------------------------------------------


// --------------------------------------------------------------------
// link/play/record
// --------------------------------------------------------------------
void	DoFunc_UnlinkDevice(void)
{
	RetCode_t	r;
	char		MsgStr[160];
	char		DevStr1[64], DevStr2[64],DevStr3[64];

	if ( !bStartWorkFlag )	return;



	if ( !CheckOpenDevice (iOpenedIndex2, false) )
		return;

	sprintf ( DevStr1, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID));
	sprintf ( DevStr2, GetString_DeviceAll (&DevOpened[iOpenedIndex2].DevID));
	sprintf ( DevStr3, GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID));

	if( g_Select == 0)
	{
		if ( !CheckOpenDevice (iOpenedIndex1) )
			return;

		r = XMS_ctsUnlinkDevice ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, &DevOpened[iOpenedIndex2].DevID, NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsUnlinkDevice() FAIL! src(%s) -> dst(%s)", 
				r, DevStr1, DevStr2  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsUnlinkDevice() OK! src(%s) -> dst(%s)", 
				DevStr1, DevStr2  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
	/*else
	{
		if ( !CheckOpenDevice (iOpenedIndex3) )
			return;

		r = XMS_ctsUnlinkDevice ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, &DevOpened[iOpenedIndex2].DevID, NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsUnlinkDevice() FAIL! src(%s) -> dst(%s)", 
				r, DevStr1, DevStr2  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsUnlinkDevice() OK! src(%s) -> dst(%s)", 
				DevStr1, DevStr2  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}*/
}

/*added by fuyunshi on 070619 for 3gpp on 070619*/
void	DoFunc_3GPPPlay(bool bIsDetailPlay, DJ_U8 u8MediaType)
{
	RetCode_t	r;
	char		MsgStr[160];
	char		TmpStr1[32], TmpStr2[ACS_MAX_FILE_NAME_LEN];
	Play3gppProperty_t		tmp_PlayProperty;

	CXMSApi_3GPPPlaySet	MyPlaySet;

	if ( !bStartWorkFlag )	return;

#ifndef	DEBUG_IN_HOME_NOTEBOOK
	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;
#endif

	if ( bIsDetailPlay )
	{
		g_Play3gppProperty.m_u8TaskID = (DJ_S8)GetTickCount();
        g_Play3gppProperty.m_u8VideoTaskID = g_Play3gppProperty.m_u8TaskID;

		pdlg->GetDlgItem ( IDC_EDIT_PLAY )->GetWindowText ( g_Play3gppProperty.m_s8PlayContent, ACS_MAX_FILE_NAME_LEN-1 );
		pdlg->GetDlgItem ( IDC_EDIT_PLAY )->GetWindowText ( g_Play3gppProperty.m_s8VideoPlayContent, ACS_MAX_FILE_NAME_LEN-1 );

		int	nRes = MyPlaySet.DoModal ();
		if ( nRes != IDOK )
		{
			return;
		}

		memcpy ( &tmp_PlayProperty, &g_Play3gppProperty, sizeof(Play3gppProperty_t) );
	}
	else
	{
		memset ( &tmp_PlayProperty, 0, sizeof(Play3gppProperty_t) );

 		tmp_PlayProperty.m_u8MediaType  = u8MediaType;//MEDIA_TYPE_ANV;
 		tmp_PlayProperty.m_u8TaskID     = (DJ_S8)GetTickCount();
        tmp_PlayProperty.m_u8DecodeType = XMS_Amr_type;
        tmp_PlayProperty.m_u8SrcMode    = XMS_SRC_3GVIDEO;
        tmp_PlayProperty.m_u16PlayType  = XMS_PLAY_TYPE_FILE;
        

        tmp_PlayProperty.m_u16VideoPlayType = XMS_PLAY_TYPE_FILE;
		tmp_PlayProperty.m_u8VideoTaskID    = tmp_PlayProperty.m_u8TaskID;
        tmp_PlayProperty.m_u8VideoDecode_Type = XMS_VIDEO_CODE_TYPE_H263;
        tmp_PlayProperty.m_u8VideoFrameRate    = 30;


		pdlg->GetDlgItem ( IDC_EDIT_PLAY )->GetWindowText ( tmp_PlayProperty.m_s8PlayContent, ACS_MAX_FILE_NAME_LEN-1 );
		pdlg->GetDlgItem ( IDC_EDIT_PLAY )->GetWindowText ( tmp_PlayProperty.m_s8VideoPlayContent, ACS_MAX_FILE_NAME_LEN-1 );
	}
 
	{
		strcpy ( TmpStr1, "PLAY_3GPP_FILE" );

		if ( tmp_PlayProperty.m_u16PlayType == XMS_PLAY_TYPE_INDEX )
			sprintf ( TmpStr2, "<index=%d>", tmp_PlayProperty.m_u16PlayIndex );
		else if ( tmp_PlayProperty.m_u16PlayType == XMS_PLAY_TYPE_INDEX_QUEUE )
			sprintf ( TmpStr2, "<index Q=%d>", tmp_PlayProperty.m_u16PlayIndex );
		else if ( tmp_PlayProperty.m_u16PlayType == XMS_PLAY_TYPE_FILE )
			sprintf ( TmpStr2, "<\"%s\">", tmp_PlayProperty.m_s8PlayContent );
		else
		{
              strcpy(tmp_PlayProperty.m_s8PlayContent, g_Play3gppProperty.m_s8PlayContent);				
		}

		sprintf ( TmpStr2, "<File Q\"%s\">", tmp_PlayProperty.m_s8PlayContent );

		memcpy(&g_Play3gppProperty, &tmp_PlayProperty, sizeof(g_Play3gppProperty) );	
	}

	r = XMS_cts3gppPlay ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, &tmp_PlayProperty, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_3GPPPlay(%s, %s) FAIL! (%s)", 
			r, TmpStr1, TmpStr2,
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_3GPPPlay(%s, %s) OK! (%s)", 
			TmpStr1, TmpStr2, 
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_Play(bool bIsDetailPlay)
{
	RetCode_t	r;
	DJ_U8       u8MediaType = 0;
	int         index;
	char		MsgStr[160];
	char		TmpStr1[32], TmpStr2[ACS_MAX_FILE_NAME_LEN];
	char        strFileNameEx[300];

	PlayProperty_t		tmp_PlayProperty;
    CComboBox *pCB;
	PrivateData_t  * pPDataHead = NULL;
    Acs_MediaPrivateExt_Data * pPData = NULL;

	pCB = (CComboBox *)pdlg->GetDlgItem(IDC_COMBO_STOP_MEDIA_TYPE);
	if (NULL == pCB)
	{
		ASSERT(0);
		return;
	}

	index = pCB->GetCurSel();
	u8MediaType = (DJ_U8)pCB->GetItemData(index);

	////////////////////////////////////////////////////////////////////////////
    if (((CButton *)pdlg->GetDlgItem ( IDC_CHECK_260_PATH ))->GetCheck())
		g_bIsExPathTo260 = 1;
	else
		g_bIsExPathTo260 = 0;
	////////////////////////////////////////////////////////////////////////////

	if ( XMS_DEVSUB_MEDIA_VOC == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		CXMSApi_PlaySet	MyPlaySet;

		if ( !bStartWorkFlag )	return;

	#ifndef	DEBUG_IN_HOME_NOTEBOOK
		if ( !CheckOpenDevice (iOpenedIndex1) )
			return;
	#endif

		if ( bIsDetailPlay )
		{
			g_PlayProperty.m_u8TaskID = (DJ_S8)GetTickCount();
			if ( !g_bIsExPathTo260 )
				pdlg->GetDlgItem ( IDC_EDIT_PLAY )->GetWindowText ( g_PlayProperty.m_s8PlayContent, ACS_MAX_FILE_NAME_LEN-1 );

			int	nRes = MyPlaySet.DoModal ();
			if ( nRes != IDOK )
			{
				return;
			}

			memcpy ( &tmp_PlayProperty, &g_PlayProperty, sizeof(PlayProperty_t) );
		}
		else
		{
			memset ( &tmp_PlayProperty, 0, sizeof(PlayProperty_t) );

			tmp_PlayProperty.m_u8TaskID = (DJ_S8)GetTickCount();

			if ( !g_bIsExPathTo260 )
				pdlg->GetDlgItem ( IDC_EDIT_PLAY )->GetWindowText ( tmp_PlayProperty.m_s8PlayContent, ACS_MAX_FILE_NAME_LEN-1 );
		}

		{
			strcpy ( TmpStr1, "PLAY_FILE" );

			if ( tmp_PlayProperty.m_u16PlayType == XMS_PLAY_TYPE_INDEX )
				sprintf ( TmpStr2, "<index=%d>", tmp_PlayProperty.m_u16PlayIndex );
			else if ( tmp_PlayProperty.m_u16PlayType == XMS_PLAY_TYPE_INDEX_QUEUE )
				sprintf ( TmpStr2, "<index Q=%d>", tmp_PlayProperty.m_u16PlayIndex );
			else if ( tmp_PlayProperty.m_u16PlayType == XMS_PLAY_TYPE_FILE )
				sprintf ( TmpStr2, "<\"%s\">", tmp_PlayProperty.m_s8PlayContent );
			else
				sprintf ( TmpStr2, "<File Q\"%s\">", tmp_PlayProperty.m_s8PlayContent );
		}

		////////////////////////////////////////////////////////////////////////////
		if ( g_bIsExPathTo260 )
		{
			memset(strFileNameEx, 0, 300);
			pPDataHead = (PrivateData_t*)strFileNameEx;
			pPData     = (Acs_MediaPrivateExt_Data*)(pPDataHead+1);
        
			pPDataHead->m_u32DataSize = sizeof(PrivateData_t) + sizeof(Acs_MediaPrivateExt_Data);

			pPData->m_u32ExtType = XMS_EXT_TYPE_PATH;
			pdlg->GetDlgItem ( IDC_EDIT_PLAY )->GetWindowText ( (char*)pPData->m_u8Buf, MAX_PATH-1 );
			memset(tmp_PlayProperty.m_s8PlayContent, 0, sizeof( tmp_PlayProperty.m_s8PlayContent) );

		}
		////////////////////////////////////////////////////////////////////////////
		r = XMS_ctsPlay ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, &tmp_PlayProperty, pPDataHead );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsPlay(%s, %s) FAIL! (%s)", 
				r, TmpStr1, TmpStr2,
				GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsPlay(%s, %s) OK! (%s)", 
				TmpStr1, TmpStr2, 
				GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		
	}
	else if ( XMS_DEVSUB_MEDIA_324 == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		// TODO: Add your control notification handler code here
		DoFunc_3GPPPlay( bIsDetailPlay, u8MediaType );
		//DoFunc_Play(true);
	}	
}

void	DoFunc_3GPPStopPlay( int iMediaType )
{
	RetCode_t	r;
	char		MsgStr[160];
	Control3gppPlay_t	controlPlay;

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	controlPlay.m_u16ControlType = XMS_STOP_PLAY;
	if ( iMediaType == MEDIA_TYPE_AUDIO 
	  || iMediaType == MEDIA_TYPE_VIDEO
	  || iMediaType == MEDIA_TYPE_ANV)
		controlPlay.m_u8MediaType    = iMediaType;
	else
		controlPlay.m_u8MediaType    = MEDIA_TYPE_ANV;

	r = XMS_ctsControl3gppPlay ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, &controlPlay, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_3GPPStopPlay() FAIL! (%s)", 
			r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_3GPPStopPlay() OK! (%s)", 
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_MyStopPlay(int iMediaType)
{
 	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	
		return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

   if ( XMS_DEVSUB_MEDIA_VOC == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		ControlPlay_t	controlPlay;

		controlPlay.m_u16ControlType = XMS_STOP_PLAY;

		r = XMS_ctsControlPlay ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, &controlPlay, NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) MyStopPlay() FAIL! (%s)", 
				r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "MyStopPlay() OK! (%s)", 
				GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}	
	}
	else if ( XMS_DEVSUB_MEDIA_324 == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		DoFunc_3GPPStopPlay( iMediaType );
	}
}

void	DoFunc_ControlPlay_Real(ControlPlay_t *pControlPlay)
{
	RetCode_t	r;
	char		MsgStr[160];

	r = XMS_ctsControlPlay ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, pControlPlay, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsControlPlay(%s, %d) FAIL! (%s)", 
			r, 
			GetString_PlayControlType(pControlPlay->m_u16ControlType),pControlPlay->m_u16StepSize,
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsControlPlay(%s, %d) OK! (%s)", 
			GetString_PlayControlType(pControlPlay->m_u16ControlType),pControlPlay->m_u16StepSize,
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_Control3GPPPlay_Real(Control3gppPlay_t *pControlPlay)
{
	RetCode_t	r;
	char		MsgStr[160];

	r = XMS_ctsControl3gppPlay ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, pControlPlay, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsControl3gppPlay(%s) FAIL! (%s)", 
			r, 
			GetString_PlayControlType(pControlPlay->m_u16ControlType),
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsControl3gppPlay(%s) OK! (%s)", 
			GetString_PlayControlType(pControlPlay->m_u16ControlType),
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_ControlPlay(void)
{
	if ( XMS_DEVSUB_MEDIA_VOC == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		CXMSApi_ControlPlay	MyControl;

		if ( !bStartWorkFlag )	return;

		if ( !CheckOpenDevice (iOpenedIndex1) )
			return;

		MyControl.DoModal ();	
	}
	else if ( XMS_DEVSUB_MEDIA_324 == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		CXMSApi_Control3GPPPlay	MyControl;

		if ( !bStartWorkFlag )	return;

		if ( !CheckOpenDevice (iOpenedIndex1) )
			return;

		MyControl.DoModal ();			
	}
}

void	DoFunc_3GPPRecord ( bool bIsDetailRecord )
{
	RetCode_t			r;
	char				MsgStr[160];
	Record3gppProperty_t	recordProperty;
	CXMSApi_Record3GPPSet	MyRecordSet;
	
	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;
	
	pdlg->GetDlgItem ( IDC_EDIT1_RECORD )->GetWindowText ( g_Record3gppProperty.m_s8FileName, ACS_MAX_FILE_NAME_LEN-1 );
	strcpy(g_RecordProperty.m_s8FileName, g_Record3gppProperty.m_s8FileName);

	if ( bIsDetailRecord )
	{
		g_Record3gppProperty.m_s8AudioIsMixEnable = TRUE;
		g_Record3gppProperty.m_AudioMixerControl.m_u16SRC_ChID1 = DevOpened[iOpenedIndex1].DevID.m_s16ChannelID;
		g_Record3gppProperty.m_AudioMixerControl.m_u8SRC1_Ctrl  = XMS_MIXER_FROM_PLAY;

		g_Record3gppProperty.m_s8VideoIsMixEnable = TRUE;
		g_Record3gppProperty.m_VideoMixerControl.m_u16SRC_ChID1 = DevOpened[iOpenedIndex1].DevID.m_s16ChannelID;
		g_Record3gppProperty.m_VideoMixerControl.m_u8SRC1_Ctrl  = XMS_MIXER_FROM_PLAY;
		/////////////////////////////////////////////////////////////////////////////////

		//init the record property on 070723 by fuyunshi
		g_Record3gppProperty.m_u32MaxTime = 0;          /*record max time, 0: no limit record time; >0: record max time*/	
		g_Record3gppProperty.m_u8StopMode = 0;          /*stop record mode,referecne XMS_PLAYREC_STOP_MODE*/	
		g_Record3gppProperty.m_u8StopCode = 0;	      /*stop record when receive this dtmf code*/
		g_Record3gppProperty.m_s8IsAppend = 0;          /*0: trunc record file; 1: append record file,reference XMS_REC_OPENFILE_TYPE*/	

		g_Record3gppProperty.m_u8AudioSRCMode    = XMS_SRC_3GVIDEO;  /*file src mode, reference XMS_VOC_SRC_MODE*/
		g_Record3gppProperty.m_u8AudioTracks     = XMS_AUDIO_TRACKS_STEREO;      /*audio channel,reference XMS_AUDIO_TRACKS*/
		g_Record3gppProperty.m_u16AudioMaxBitRate = 0;      /*audio max bitrate,0~65535*/
		g_Record3gppProperty.m_u16AudioAverageBitRate = 0;  /*audio average bitrate,0~65535*/
//		g_Record3gppProperty.m_Rfu1[0] = 0;
//		g_Record3gppProperty.m_Rfu1[1] = 0;

		g_Record3gppProperty.m_u8VideoEncodeType = XMS_VIDEO_CODE_TYPE_H263;
		g_Record3gppProperty.m_u8VideoFrameRate  = 15;
		g_Record3gppProperty.m_u16VideoHeight    = 144;
		g_Record3gppProperty.m_u16VideoWidth     = 176;
		g_Record3gppProperty.m_u8VideoProfiles   = 0;
		g_Record3gppProperty.m_u8VideoLevel      = 10;

		/////////////////////////////////////////////////////////////////////////////////

	    int	nRes = MyRecordSet.DoModal ();
		if ( nRes != IDOK )
		{
			return;
		}
	}
	else
	{
		g_Record3gppProperty.m_s8AudioIsMixEnable = TRUE;
		g_Record3gppProperty.m_AudioMixerControl.m_u16SRC_ChID1 = DevOpened[iOpenedIndex1].DevID.m_s16ChannelID;
		g_Record3gppProperty.m_AudioMixerControl.m_u8SRC1_Ctrl  = XMS_MIXER_FROM_PLAY;

		g_Record3gppProperty.m_s8VideoIsMixEnable = TRUE;
		g_Record3gppProperty.m_VideoMixerControl.m_u16SRC_ChID1 = DevOpened[iOpenedIndex1].DevID.m_s16ChannelID;
		g_Record3gppProperty.m_VideoMixerControl.m_u8SRC1_Ctrl  = XMS_MIXER_FROM_PLAY;

	}

    memset( &recordProperty, 0, sizeof(Record3gppProperty_t) );
    memcpy(&recordProperty, &g_Record3gppProperty, sizeof(Record3gppProperty_t) );

	r = XMS_cts3gppRecord ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, &recordProperty, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) DoFunc_3GPPRecord(%s) FAIL! (%s)", 
			r, recordProperty.m_s8FileName, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "DoFunc_3GPPRecord(%s) OK! (%s)", 
			recordProperty.m_s8FileName, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_3GPPStopRecord(void)
{
	RetCode_t	r;
	char		MsgStr[160];
	Control3gppRecord_t	controlRecord;

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	controlRecord.m_u32ControlType = XMS_STOP_RECORD;

	r = XMS_ctsControl3gppRecord ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, &controlRecord, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) DoFunc_3GPPStopRecord() FAIL! (%s)", 
			r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "DoFunc_3GPPStopRecord() OK! (%s)", 
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_Record ( bool bIsDetailRecord )
{
	RetCode_t			r;
	char				MsgStr[160], BUF[256];
	RecordProperty_t	recordProperty;
	SYSTEMTIME SystemTime;

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	if ( XMS_DEVSUB_MEDIA_VOC == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		CXMSApi_RecordSet	MyRecordSet;

		pdlg->GetDlgItem ( IDC_EDIT1_RECORD )->GetWindowText ( g_RecordProperty.m_s8FileName, ACS_MAX_FILE_NAME_LEN-1 );
		
		if ( bIsDetailRecord )
		{
			int	nRes = MyRecordSet.DoModal ();
			if ( nRes != IDOK )
			{
				return;
			}
		}
		else
		{
			g_RecordProperty.m_u8TaskID = (DJ_U8)(GetTickCount() % 128);
			g_RecordProperty.m_s8IsMixEnable = 1;
			g_RecordProperty.m_MixerControl.m_u8SRC1_Ctrl  = XMS_MIXER_FROM_PLAY;
			g_RecordProperty.m_MixerControl.m_u16SRC_ChID1 = DevOpened[iOpenedIndex1].DevID.m_s16ChannelID;
			g_RecordProperty.m_MixerControl.m_u8SRC2_Ctrl  = XMS_MIXER_FROM_NULL;
			g_RecordProperty.m_MixerControl.m_u16SRC_ChID2 = DevOpened[iOpenedIndex1].DevID.m_s16ChannelID;
		}

		memcpy ( &recordProperty, &g_RecordProperty, sizeof(RecordProperty_t) );
		GetLocalTime(&SystemTime);

		r = XMS_ctsRecord ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, &recordProperty, NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsRecord(%s) FAIL! (%s)", 
				r, recordProperty.m_s8FileName, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsRecord(%s) OK! (%s)", 
				recordProperty.m_s8FileName, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
	else if ( XMS_DEVSUB_MEDIA_324 == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		DoFunc_3GPPRecord( bIsDetailRecord );
	}

    sprintf(BUF, "DSP: %d, CH: %d, %u-%02u-%02u %02u:%02u:%02u:%03u ", DevOpened[iOpenedIndex1].DevID.m_s8ModuleID, DevOpened[iOpenedIndex1].DevID.m_s16ChannelID, SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay, SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond,SystemTime.wMilliseconds);

	TRACE("%s\n", BUF);
}

void	DoFunc_MyStopRecord(void)
{
	RetCode_t	r;
	char		MsgStr[160];
	ControlRecord_t	controlRecord;

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;


	if ( XMS_DEVSUB_MEDIA_VOC == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		controlRecord.m_u32ControlType = XMS_STOP_RECORD;

		r = XMS_ctsControlRecord ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, &controlRecord, NULL );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) MyStopRecord() FAIL! (%s)", 
				r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "MyStopRecord() OK! (%s)", 
				GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}	
	}
	else if ( XMS_DEVSUB_MEDIA_324 == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		DoFunc_3GPPStopRecord( );
	}
}

void	DoFunc_ControlRecord_Real(ControlRecord_t *pControlRecord)
{
	RetCode_t	r;
	char		MsgStr[160];

	r = XMS_ctsControlRecord ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, pControlRecord, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsControlRecord(%s, %d) FAIL! (%s)", 
			r, 
			GetString_RecordControlType(pControlRecord->m_u32ControlType),pControlRecord->m_u32StepSize,
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsControlRecord(%s, %d) OK! (%s)", 
			GetString_RecordControlType(pControlRecord->m_u32ControlType),pControlRecord->m_u32StepSize,
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_Control3GPPRecord_Real(Control3gppRecord_t *pControlRecord)
{
	RetCode_t	r;
	char		MsgStr[160];

	r = XMS_ctsControl3gppRecord ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, pControlRecord, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsControl3gppRecord(%s, %d) FAIL! (%s)", 
			r, 
			GetString_RecordControlType(pControlRecord->m_u32ControlType),pControlRecord->m_u32StepTime,
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsControl3gppRecord(%s, %d) OK! (%s)", 
			GetString_RecordControlType(pControlRecord->m_u32ControlType),pControlRecord->m_u32StepTime,
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_ControlRecord(void)
{

	if ( XMS_DEVSUB_MEDIA_VOC == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		CXMSApi_ControlRecord	MyControl;

		if ( !bStartWorkFlag )	return;

		if ( !CheckOpenDevice (iOpenedIndex1) )
			return;

		MyControl.DoModal ();
    }
	else if ( XMS_DEVSUB_MEDIA_324 == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		CXMSApi_3GPPControlRecord	MyControl;

		if ( !bStartWorkFlag )	return;

		if ( !CheckOpenDevice (iOpenedIndex1) )
			return;

		MyControl.DoModal ();
	}
}
// --------------------------------------------------------------------
// end of link/play/record
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// Fax
// --------------------------------------------------------------------
void	DoFunc_SendFax(void)
{
	RetCode_t	r;
	char		MsgStr[160];
	char		TiffFileName[ACS_MAX_FILE_NAME_LEN];
	char		s8LocalID[20];
	char		DevStr1[64], DevStr2[64];

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	if ( !CheckOpenDevice (iOpenedIndex2, false) )
		return;

	pdlg->GetDlgItem ( IDC_EDIT_SENDFAX )->GetWindowText ( TiffFileName, ACS_MAX_FILE_NAME_LEN-1 );
	sprintf ( s8LocalID, "DJ:83636988" );

	sprintf ( DevStr1, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID));
	sprintf ( DevStr2, GetString_DeviceAll (&DevOpened[iOpenedIndex2].DevID));

	r = XMS_ctsSendFax ( g_acsHandle, 
					&DevOpened[iOpenedIndex1].DevID,			// FaxDevice
					&DevOpened[iOpenedIndex2].DevID,			// mediaDevice
					TiffFileName,
					s8LocalID,
					NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsSendFax(%s, %s) FAIL! fax(%s) media(%s)", 
			r, TiffFileName, s8LocalID,
			DevStr1, DevStr2  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsSendFax(%s, %s) OK! fax(%s) media(%s)", 
			TiffFileName, s8LocalID,
			DevStr1, DevStr2  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}

}

void	DoFunc_StopSendFax(void)
{
	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	r = XMS_ctsStopSendFax ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsStopSendFax() FAIL! fax(%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsStopSendFax() OK! fax(%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_ReceiveFax(void)
{
	RetCode_t	r;
	char		MsgStr[160];
	char		TiffFileName[ACS_MAX_FILE_NAME_LEN];
	char		s8LocalID[20];
	char		DevStr1[64], DevStr2[64];

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	if ( !CheckOpenDevice (iOpenedIndex2, false) )
		return;

	pdlg->GetDlgItem ( IDC_EDIT_RECEIVEFAX )->GetWindowText ( TiffFileName, ACS_MAX_FILE_NAME_LEN-1 );
	sprintf ( s8LocalID, "DJ:83636988" );

	sprintf ( DevStr1, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID));
	sprintf ( DevStr2, GetString_DeviceAll (&DevOpened[iOpenedIndex2].DevID));

	r = XMS_ctsReceiveFax ( g_acsHandle, 
					&DevOpened[iOpenedIndex1].DevID,			// FaxDevice
					&DevOpened[iOpenedIndex2].DevID,			// mediaDevice
					TiffFileName,
					s8LocalID,
					NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsReceiveFax(%s, %s) FAIL! media(%s) fax(%s)", 
			r, TiffFileName, s8LocalID,
			DevStr1, DevStr2  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsReceiveFax(%s, %s) OK! fax(%s) media(%s)", 
			TiffFileName, s8LocalID,
			DevStr1, DevStr2  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_StopReceiveFax(void)
{
	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	r = XMS_ctsStopReceiveFax ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsStopReceiveFax() FAIL! fax(%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsStopReceiveFax() OK! fax(%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}
// --------------------------------------------------------------------
// end Fax
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// conference 
// --------------------------------------------------------------------
int		g_IsLeaveConf = false;

void 	DoFunc_JoinToConf(void)
{
	RetCode_t	r;
	char		MsgStr[160];
	char		DevStr1[64], DevStr2[64];
	CXMSApi_ConfParam	MyConfParam;
	CmdParamData_Conf_t	confParam;

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	if ( !CheckOpenDevice (iOpenedIndex2, false) )
		return;

	int	nRes;

	g_IsLeaveConf = false;
	nRes = MyConfParam.DoModal ();
	if ( nRes != IDOK )
		return;

	confParam = g_Conf_Param;

	sprintf ( DevStr1, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID));
	sprintf ( DevStr2, GetString_DeviceAll (&DevOpened[iOpenedIndex2].DevID));

	r = XMS_ctsJoinToConf ( g_acsHandle, 
					&DevOpened[iOpenedIndex1].DevID,			// confDevice
					&DevOpened[iOpenedIndex2].DevID,			// MediaDevice
					&confParam,
					NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsJoinToConf(InOpt=%d,OutOpt=%d) FAIL! conf(%s) media(%s)", 
			r, confParam.m_u8InputOpt, confParam.m_u8OutputOpt,
			DevStr1, DevStr2  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsJoinToConf(InOpt=%d,OutOpt=%d) OK! conf(%s) media(%s)", 
			confParam.m_u8InputOpt, confParam.m_u8OutputOpt,
			DevStr1, DevStr2  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}

}

void	DoFunc_LeaveFromConf(void)
{
	RetCode_t	r;
	char		MsgStr[160];
	char		DevStr1[64], DevStr2[64];
	CXMSApi_ConfParam	MyConfParam;
	CmdParamData_Conf_t	confParam;

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	if ( !CheckOpenDevice (iOpenedIndex2, false) )
		return;

	int	nRes;

	g_IsLeaveConf = true;
	nRes = MyConfParam.DoModal ();
	if ( nRes != IDOK )
		return;

	confParam = g_Conf_Param;

	sprintf ( DevStr1, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID));
	sprintf ( DevStr2, GetString_DeviceAll (&DevOpened[iOpenedIndex2].DevID));

	r = XMS_ctsLeaveFromConf ( g_acsHandle, 
					&DevOpened[iOpenedIndex1].DevID,			// confDevice
					&DevOpened[iOpenedIndex2].DevID,			// MediaDevice
					&confParam,
					NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsLeaveFromConf() FAIL! conf(%s) media(%s)", 
			r, DevStr1, DevStr2  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsLeaveFromConf() OK! conf(%s) media(%s)", 
			DevStr1, DevStr2  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void 	DoFunc_ClearConf(void)
{
	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	r = XMS_ctsClearConf ( g_acsHandle, 
					&DevOpened[iOpenedIndex1].DevID,			// confDevice
					NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsClearConf() FAIL! conf(%s)", 
			r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsClearConf() OK! conf(%s)", 
			 GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

// --------------------------------------------------------------------
// end of conference 
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// other
// --------------------------------------------------------------------
void	DoFunc_SetParam(void)
{
#define MAX_CODE_NUMBERS   7


	RetCode_t	r;
	char		MsgStr[160];
	void		* p;
	int			nRes;
	static DJ_S32 i = 0;
    DJ_S32 iParam = 1,iTemp = 0; 
	DJ_S8 str[] = "110";
	DJ_S8 strTemp[10] = {0};

	// parameter
	DJ_U16		u16ParamType, u16ParamSize;
	CXMSApi_Test_ParamVoice	My_P_Voice;
	CXMSApi_ParamCAS		My_P_CAS;
	CDialogAnaTrunk         My_P_Trunk;
	CDialogAnalogUser       My_P_User;
	CXMS_Test_ParamVoIP     My_P_VoIP;
	CDlgSetVoIPParams		My_P_SetVoIP;
	CDialogFskSet			My_P_Fsk;
	CDialogFlashSet			My_P_Flash;
	CDialogGTDSet			My_P_GtdSet;
    CDialogGTGSet           My_P_GtgSet;
	CCLKDialog              My_P_CLKSet;
	DialogAtrunkFlash		My_P_ATrunkFlash;
	CDialog3GFaxTone        My_P_3GFaxTone;
	CDialogFaxHeader		My_P_FaxHeader;
	DialogAtrunkEM          My_P_EM;
    CFaxECMDlg              My_p_FAXECM;
    CDlgFaxBpsParam         My_p_FaxBpsParam;
	CDialogSVDSet           My_p_SVD;
	CDialogActiveMemSet     My_ConfActiveMemDetect;
	CDlgParamType			My_p_ParamType;
	CDlgRtpxInput			My_p_RtpxInput;
	CDlgRtpxOutput			My_p_RtpxOutput;
	CDlgRtpxMixer			My_p_RtpxMixer;
	CDlgRtpxAddr			My_p_RtpxAddr;
	CDlgMediaExParam		My_p_MediaExParam;
	CDlgMediaExInput		My_p_MediaExInput;
	CDlgMediaExOutput		My_p_MediaExOutput;
    CDlgFaxMultiFileParam   My_p_FaxMultiFile;
    

	CDlgBoardVadMinLevelParam       My_VADMinLevelParam;
	CDlgBoardCommonParam            My_BoardCommonParam;

	CARecVoltageSetDlg              My_A_REC;
	CRecModModeSetDlg               My_REC_Mod;
    CDSS1CallParamDlg               My_DSS1CallParam;

	CDlgSS7SS7RawFrame       My_SS7RawFrameParam;  // author:chenz
	CDlgUserReadXmsBoardInfo My_UserReadXmsBoardInfo;  // author:chenz
	CDlgCmdParamDataCAS      My_CmdParamDataCAS;  // author:chenz

	CmdParamData_RTPXAddr_t paramAddr;
	MixerControlParam_t paramMixer;
	CmdParamData_RTPXOutput_t paramOut;
	CmdParamData_RTPXInput_t paramIn;
//	Acs_MediaEx_Input MediaExIn[16];
//	Acs_MediaEx_Output MediaExOut[16];

#ifndef	DEBUG_IN_HOME_NOTEBOOK
	if ( !bStartWorkFlag )	return;

if ( iComboParam != 5 )
{
	if ( !CheckOpenDevice (iOpenedIndex1) )  
		return;
}

#endif

	switch (iComboParam)
	{
	case 0:		// Voice
 		nRes = My_P_Voice.DoModal ();

		if ( nRes != IDOK )
		{
			return ;
		}

		u16ParamType = VOC_PARAM_UNIPARAM;
		u16ParamSize = sizeof(CmdParamData_Voice_t);
		p = (void *)&g_Voice_Param;
		break;

	case SET_PARAM_TYPE_E1_CAS_SET: //1:		// CAS
		// parameter CAS

		if ( !CheckOpenDevice (iOpenedIndex2) )
			return;
		
		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH || 
			 DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub  != XMS_DEVSUB_E1_CAS )
		{
			AfxMessageBox("Dev1 is NOT a CAS Device!");
			return;
		}

		nRes = My_P_CAS.DoModal ();
		if ( nRes != IDOK )
		{
			return ;
		}

		g_CAS_Param.m_VocDevID = DevOpened[iOpenedIndex2].DevID;

		u16ParamType = CAS_PARAM_UNIPARAM;
		u16ParamSize = sizeof(CmdParamData_CAS_t);
		p = (void *)&g_CAS_Param;
		//
		break;

	case SET_PARAM_TYPE_A_USER_SET: //2: //Analog User

		//if ( !CheckOpenDevice (iOpenedIndex2) )
		//	return;
		
		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH || 
			 DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub  != XMS_DEVSUB_ANALOG_USER )
		{
			AfxMessageBox("Dev1 is NOT an AnalogUser Device!");
			return;
		}
		
		nRes = My_P_User.DoModal ();
		if ( nRes != IDOK )
		{
			return ;
		}

		//g_AnalogUser.m_VocDevID = DevOpened[iOpenedIndex2].DevID;

		u16ParamType = ANALOGUSER_PARAM_UNIPARAM;
		u16ParamSize = sizeof(CmdParamData_AnalogUser_t);
		p = (void *)&g_AnalogUser;

		break;

	case SET_PARAM_TYPE_A_TRUNK_SET: //3: //Analog Trunk
		//if ( !CheckOpenDevice (iOpenedIndex2) )
		//	return;

		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH || 
			 DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub  != XMS_DEVSUB_ANALOG_TRUNK )
		{
			AfxMessageBox("Dev1 is NOT An AnalogTrunk Device!");
			return;
		}

		nRes = My_P_Trunk.DoModal ();
		if ( nRes != IDOK )
		{
			return ;
		}

		//g_AnalogTrunk.m_VocDevID = DevOpened[iOpenedIndex2].DevID;

		u16ParamType = ANALOGTRUNK_PARAM_UNIPARAM;
		u16ParamSize = sizeof(CmdParamData_AnalogTrunk_t);
		p = (void *)&g_AnalogTrunk;
		break;

	case SET_PARAM_TYPE_A_REC_VOLTAGE_SET:
		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH || 
			 DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub  != XMS_DEVSUB_ANALOG_REC )
		{
			AfxMessageBox("Dev1 is NOT An Analog Rec Module Device!");
			return;
		}

		nRes = My_A_REC.DoModal ();
		if ( nRes != IDOK )
		{
			return ;
		}

		u16ParamType = XMS_AREC_PARAM_SET_VOLTAGE;
		u16ParamSize = sizeof(CmdParamData_AnalogRecVoltage_t);
		p = (void *)&g_AnalogRecVoltage;
		break;

	case SET_PARAM_TYPE_REC_MOD_MODE_SET:
		if ( (DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH)
		|| ( (DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub != XMS_DEVSUB_ANALOG_REC)
		  && (DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub != XMS_DEVSUB_DIGITAL_REC)) )
		{
			AfxMessageBox("Dev1 is NOT An Analog Rec or Digital Rec Device!");
			return;
		}

		nRes = My_REC_Mod.DoModal ();
		if ( nRes != IDOK )
		{
			return ;
		}

		//g_AnalogTrunk.m_VocDevID = DevOpened[iOpenedIndex2].DevID;

		u16ParamType = XMS_DIGREC_PARAM_UNI;
		u16ParamSize = sizeof(DigRecSwitchMode);
		p = (void *)&g_RecModCfg;
		break;

	case SET_PARAM_TYPE_VOIP_MIXER_SET: //4://VoIP
		{
			//if( !CheckOpenDevice(iOpenedIndex3) )
			//	return;

			//if ( !CheckOpenDeviceForVoIP (&DevOpened[iOpenedIndex1].DevID) )
			//	return;

			if( !CheckOpenDeviceForVoIP(iOpenedIndex1 ) )
				return;

			if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_VOIP)
			{
				AfxMessageBox("Dev1 is NOT A Voip Device!");
				return;
			}

			if( !CheckOpenDevice(iOpenedIndex2,false) )
				return;
			
			if ( DevOpened[iOpenedIndex2].DevID.m_s16DeviceMain != XMS_DEVMAIN_RTP)
			{
				nRes = My_P_VoIP.DoModal();
				if( nRes != IDOK)
				{
					return;
				}
				
				//g_VoIP.m_u16SRC_ChID1 = g_deviceVoc[iDeviceVoc].device.m_s16ChannelID;
				
				g_VoIP_Param.m_u8SRC1_Ctrl = XMS_MIXER_FROM_PLAY;
				g_VoIP_Param.m_u16SRC_ChID1 = DevOpened[iOpenedIndex2].DevID.m_s16ChannelID;
				u16ParamType = VOIP_PARAM_RTPMIXER;
				u16ParamSize = sizeof(MixerControlParam_t);
				p = (void *)&g_VoIP_Param;
				
				break;
			}

			int iDspIndex = iOpenedIndex2;
			int iDevIndex = iOpenedIndex3;
			if( g_Select == 0)
				iOpenedIndex1;

			My_P_SetVoIP.m_nDspPort = RTP_PORT_BASE(10000, DevOpened[iOpenedIndex2].DevID.m_s8ModuleID) + DevOpened[iOpenedIndex2].DevID.m_s16ChannelID*2;
			if(NULL!=DevOpened[iOpenedIndex1].pDevData)
				memcpy(&g_VoIP_MediaInfo, DevOpened[iOpenedIndex1].pDevData, sizeof(Acs_VoIP_MediaInfo));
			nRes = My_P_SetVoIP.DoModal();
			if( nRes != IDOK)
			{
				return;
			}
			
			if(My_P_SetVoIP.m_bRTPSession)
			{
				u16ParamType = VOIP_PARAM_RTPSESSION;
				u16ParamSize = sizeof(Acs_VoIP_RTPSESSION);
				p = (void *)&g_RTP_Session;
				
				r = XMS_ctsSetParam( g_acsHandle, &DevOpened[iDspIndex].DevID, u16ParamType, u16ParamSize, (DJ_Void *)p );
				if ( r < 0 )
				{
					sprintf ( MsgStr, "X(%d) XMS_ctsSetParam( ParamType = %s ) FAIL! (%s)", 
						r, ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iDspIndex].DevID)  );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
				}
				else
				{
					sprintf ( MsgStr, "XMS_ctsSetParam( ParamType = %s ) OK! (%s)", 
						ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iDspIndex].DevID)  );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
				}
			}
			
			if(My_P_SetVoIP.m_bRTPAddr)
			{
				u16ParamType = VOIP_PARAM_RTPADDR;
				u16ParamSize = sizeof(Acs_VoIP_RTPADDR);
				p = (void *)&g_RTP_Addr;
				
				r = XMS_ctsSetParam( g_acsHandle, &DevOpened[iDspIndex].DevID, u16ParamType, u16ParamSize, (DJ_Void *)p );
				if ( r < 0 )
				{
					sprintf ( MsgStr, "X(%d) XMS_ctsSetParam( ParamType = %s ) FAIL! (%s)", 
						r, ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iDspIndex].DevID)  );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
				}
				else
				{
					sprintf ( MsgStr, "XMS_ctsSetParam( ParamType = %s ) OK! (%s)", 
						ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iDspIndex].DevID)  );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
				}
			}
			
			if(My_P_SetVoIP.m_bRTPCodec)
			{
				u16ParamType = VOIP_PARAM_RTPCODEC;
				u16ParamSize = sizeof(Acs_VoIP_RTPCODEC);
				p = (void *)&g_RTP_Codec;
				
				r = XMS_ctsSetParam( g_acsHandle, &DevOpened[iDspIndex].DevID, u16ParamType, u16ParamSize, (DJ_Void *)p );
				if ( r < 0 )
				{
					sprintf ( MsgStr, "X(%d) XMS_ctsSetParam( ParamType = %s ) FAIL! (%s)", 
						r, ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iDspIndex].DevID)  );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
				}
				else
				{
					sprintf ( MsgStr, "XMS_ctsSetParam( ParamType = %s ) OK! (%s)", 
						ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iDspIndex].DevID)  );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
				}
			}

			//if(My_P_SetVoIP.m_bOpenRTP)
			if(false)
			{
				//CDJDevice* pDev = CDJDevice::AllocDevice(u32Type, nID);
				u16ParamType = VOIP_PARAM_RTPOPEN;
				u16ParamSize = sizeof(Acs_VoIP_RTPOpen);
				p = (void *)&g_RTP_Open;

				r = XMS_ctsSetParam( g_acsHandle, &DevOpened[iDevIndex].DevID, u16ParamType, u16ParamSize, (DJ_Void *)p );
				if ( r < 0 )
				{
					sprintf ( MsgStr, "X(%d) XMS_ctsSetParam( ParamType = %s ) FAIL! (%s)", 
						r, ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iDevIndex].DevID)  );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
				}
				else
				{
					sprintf ( MsgStr, "XMS_ctsSetParam( ParamType = %s ) OK! (%s)", 
						ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iDevIndex].DevID)  );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
				}
			}
			
			if(My_P_SetVoIP.m_bVoIPMedia)
			{
				u16ParamType = VOIP_PARAM_MEDIAINFO;
				u16ParamSize = sizeof(Acs_VoIP_MediaInfo);
				p = (void *)&g_VoIP_MediaInfo;
				
				r = XMS_ctsSetParam( g_acsHandle, &DevOpened[iDevIndex].DevID, u16ParamType, u16ParamSize, (DJ_Void *)p );
				if ( r < 0 )
				{
					sprintf ( MsgStr, "X(%d) XMS_ctsSetParam( ParamType = %s ) FAIL! (%s)", 
						r, ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iDevIndex].DevID)  );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
				}
				else
				{
					sprintf ( MsgStr, "XMS_ctsSetParam( ParamType = %s ) OK! (%s)", 
						ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iDevIndex].DevID)  );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
				}
			}
		}
		break;

	case SET_PARAM_TYPE_BOARD_FSK_SET: //5: //fsk set
		//if ( !CheckOpenDevice (iOpenedIndex2) )
		//	return;

		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_BOARD )
		{
			AfxMessageBox("Dev1 is NOT A Board Device!");
			return;
		}

		nRes = My_P_Fsk.DoModal ();
		if ( nRes != IDOK )
		{
			return ;
		}

		u16ParamType = BOARD_PARAM_SETFSK;
		u16ParamSize = sizeof(CmdParamData_FskParam_t);
		p = (void *)&g_FskSet;
		break;
	case SET_PARAM_TYPE_BOARD_FLASH_TIME_SET: //6: //flash Time  set
			//if ( !CheckOpenDevice (iOpenedIndex2) )
		//	return;

		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_BOARD )
		{
			AfxMessageBox("Dev1 is NOT A Board Device!");
			return;
		}

		nRes = My_P_Flash.DoModal ();
		if ( nRes != IDOK )
		{
			return ;
		}

		u16ParamType = BOARD_PARAM_SETFLASH;
		u16ParamSize = sizeof(CmdParamData_FlashParam_t);
		p = (void *)&g_FlashSet;
		break;
	case SET_PARAM_TYPE_BOARD_GTD_SET: //7://setGTD
		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_BOARD )
		{
			AfxMessageBox("Dev1 Is NOT A Board Device!");
			return;
		}

		nRes = My_P_GtdSet.DoModal ();
		if ( nRes != IDOK )
		{
			return ;
		}

		//*** Set GTD_Freq
		u16ParamType = 	BOARD_PARAM_SETGTDFREQ ;
		u16ParamSize = sizeof(CmdParamData_GtdFreq_t);
		p = (void *)&g_GtdFreq;

		r = XMS_ctsSetParam( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, u16ParamType, u16ParamSize, (DJ_Void *)p );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsSetParam( ParamType = %s GTD_FREQ) FAIL! (%s)", 
				r, ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsSetParam( ParamType = %s GTD_FREQ) OK! (%s)", 
				ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		
		//Set GTD ProtoType(GTD_Template)
		u16ParamType = 	BOARD_PARAM_SETGTDTONE ;
		u16ParamSize = sizeof(CmdParamData_GtdProtoType_t);
		p = (void *)&g_GtdProto;

		r = XMS_ctsSetParam( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, u16ParamType, u16ParamSize, (DJ_Void *)p );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsSetParam( ParamType = %s GTD_PROTO) FAIL! (%s)", 
				r, ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsSetParam( ParamType = %s GTD_PROTO) OK! (%s)", 
				ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}

		return;

		//break;
	case SET_PARAM_TYPE_BOARD_VSD_SET: //8:
		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_BOARD )
		{
			AfxMessageBox("Dev1 Is NOT A Board Device!");
			return;
		}

		nRes = My_p_SVD.DoModal ();
		if ( nRes != IDOK )
		{
			return ;
		}

		//*** Set VSD
		u16ParamType = 	BOARD_PARAM_SETVSD ;
		u16ParamSize = sizeof(CmdParam_SilenceDetectParam_t);
		p = (void *)&g_SVDCmd;
		break;
	case SET_PARAM_TYPE_BOARD_GTG_SET: //9:
       	if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_BOARD )
		{
			AfxMessageBox("Dev1 Is NOT A Board Device!");
			return;
		}

		nRes = My_P_GtgSet.DoModal ();
		if ( nRes != IDOK )
		{
			return ;
		}

		//*** Set GTD_Freq
		u16ParamType = 	BOARD_PARAM_SETGTGFREQ ;
		u16ParamSize = sizeof(CmdParamData_GtgFreq_t);
		p = (void *)&g_GtgFreq;

		r = XMS_ctsSetParam( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, u16ParamType, u16ParamSize, (DJ_Void *)p );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsSetParam( ParamType = %s GTG_FREQ) FAIL! (%s)", 
				r, ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsSetParam( ParamType = %s GTG_FREQ) OK! (%s)", 
				ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		
		//Set GTD ProtoType(GTD_Template)
		u16ParamType = 	BOARD_PARAM_SETGTGTONE ;
		u16ParamSize = sizeof(CmdParamData_GtgProtoType_t);
		p = (void *)&g_GtgProto;

		r = XMS_ctsSetParam( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, u16ParamType, u16ParamSize, (DJ_Void *)p );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsSetParam( ParamType = %s GTG_PROTO) FAIL! (%s)", 
				r, ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsSetParam( ParamType = %s GTG_PROTO) OK! (%s)", 
				ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		break;
	case SET_PARAM_TYPE_BOARD_RESET_SET:
		{
			if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_BOARD )
			{
				AfxMessageBox("Dev1 Is NOT A Board Device!");
				return;
			}

			//*** Set RST BOARD
			Acs_BoardRstState_Data data = {0};
			u16ParamType = 	BOARD_PARAM_SET_RST_MASTER ;
			u16ParamSize = sizeof(Acs_BoardRstState_Data);
			p = (void *)&data;
/*
			r = XMS_ctsSetParam( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, u16ParamType, u16ParamSize, (DJ_Void *)p );
			if ( r < 0 )
			{
				sprintf ( MsgStr, "X(%d) XMS_ctsSetParam( ParamType = %s GTG_FREQ) FAIL! (%s)", 
					r, ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
				AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
			}
			else
			{
				sprintf ( MsgStr, "XMS_ctsSetParam( ParamType = %s GTG_FREQ) OK! (%s)", 
					ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
				AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
			}*/
		}
		
		break;
	case SET_PARAM_TYPE_BOARD_CONF_ACTIVE_DTT: //10:   //active member detect
		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_BOARD )
		{
			AfxMessageBox("Dev1 Is NOT A Board Device!");
			return;
		}

		nRes = My_ConfActiveMemDetect.DoModal();
		if ( nRes != IDOK )
		{
			return ;
		}
		
		u16ParamType = BOARD_PARAM_SET_ACTIVE_MEM_VAD;
//		u16ParamSize = sizeof(CmdParam_ActiveMemDetectParam_t);
//		p = (void *)&g_ConfActiveMemParam;

	    break;
	case SET_PARAM_TYPE_BOARD_CLK: //22:  //SET_PARAM_TYPE_CLK
		{
			if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_BOARD )
			{
			    AfxMessageBox("Dev1 Is NOT A Board Device!");
			    return;
			}
		    nRes = My_P_CLKSet.DoModal ();
		    if ( nRes != IDOK )
			{
			   return ;
			}

		    u16ParamType = BOARD_PARAM_SETCTCLK;
		    u16ParamSize = sizeof(CmdParamData_CTCLKNET_t);
		    p = (void *)&g_CTCLK;
			break;
		}
	case SET_PARAM_TYPE_BOARD_VAD_MIN_LEVEL: //22:  //SET_PARAM_TYPE_CLK
		{
			if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_BOARD )
			{
				AfxMessageBox("Dev1 Is NOT A Board Device!");
				return;
			}

			nRes = My_VADMinLevelParam.DoModal();
			if ( nRes != IDOK )
			{
				return ;
			}
			
			u16ParamType = BOARD_PARAM_SET_MIN_VAD;
			u16ParamSize = sizeof(CmdParam_VADMinDetectParam_t);
			p = (void *)&g_VADMinLevelParam;

			break;
		}

	case SET_PARAM_TYPE_BOARD_COMM_CFG: //22:  //SET_PARAM_TYPE_CLK
		{
			if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_BOARD )
			{
				AfxMessageBox("Dev1 Is NOT A Board Device!");
				return;
			}

			nRes = My_BoardCommonParam.DoModal();
			if ( nRes != IDOK )
			{
				return ;
			}
			
			u16ParamType = BOARD_PARAM_SET_COMMON_CFG;
			u16ParamSize = sizeof(CmdParam_BoardCommonParam_t);
			p = (void *)&g_BoardCommonParm;

			break;
		}
	
	case SET_PARAM_TYPE_A_TRUNK_FLASH_EVENT: //11: //8: //Analog Trunk Set FlashEvent
		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH || 
			 DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub  != XMS_DEVSUB_ANALOG_TRUNK )
		{
			AfxMessageBox("Dev1 is NOT An AnalogTrunk Device!");
			return;
		}

		nRes = My_P_ATrunkFlash.DoModal ();
		if ( nRes != IDOK )
		{
			return ;
		}

		u16ParamType = ANALOGTRUNK_PARAM_SETFLASH;
		u16ParamSize = sizeof(CmdParamData_AnalogTrunkFlash_t);
		p = (void *)&g_ATrunkFlash;

		break;

	case SET_PARAM_TYPE_VOC_GTG_KEY_INTRPT: //12: //9: //key interrupt
		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_VOICE )
		{
			AfxMessageBox("Dev1 Is NOT A Voice Device!");
			return;
		}
		return;
	
	case SET_PARAM_TYPE_FAX_TONE: //13: //10://3G FaxTone
		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_VOICE )
		{
			AfxMessageBox("Dev1 Is NOT A Voice Device!");
			return;
		}
		nRes = My_P_3GFaxTone.DoModal();
		if ( nRes != IDOK )
		{
			return ;
		}

		u16ParamType = VOC_PARAM_3GFAXTONE;
		u16ParamSize = sizeof(ITP_3G_FaxToneStruct_t);
		p = (void *)&g_3GFaxTone;

		break;

	case SET_PARAM_TYPE_FAX_SET_HEADER: //14: //11://fax setheader
		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_FAX )
		{
			AfxMessageBox("Dev1 Is NOT A Fax Device!");
			return;
		}
		nRes = My_P_FaxHeader.DoModal();
		if ( nRes != IDOK )
		{
			return ;
		}

		u16ParamType = FAX_PARAM_FAXHEADER;
		u16ParamSize = sizeof(Acs_TransAddHeader);
		p = (void *)&g_FaxHeader;
		break;

	case SET_PARAM_TYPE_FAX_ECM:  //15: //FAX ECM
		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_FAX )
		{
			AfxMessageBox("Dev1 is NOT An FAX Device!");
			return;
		}

		nRes = My_p_FAXECM.DoModal ();
		if ( nRes != IDOK )
		{
			return ;
		}

		//g_ATrunkFlash.m_VocDevID = DevOpened[iOpenedIndex2].DevID;

		u16ParamType = FAX_PARAM_ECM;
		u16ParamSize = sizeof(Acs_SetECM);
		p = (void *)&g_FaxECMCmd;
		break;
	////////////////////////////////////////////////////////////////////////////////////////////
	case SET_PARAM_TYPE_FAX_BPS: //16: //FAX ECM 		

		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_FAX )
		{
			AfxMessageBox("Dev1 is NOT An FAX Device!");
			return;
		}

		nRes = My_p_FaxBpsParam.DoModal ();
		if ( nRes != IDOK )
		{
			return ;
		}

		u16ParamType = FAX_PARAM_BPS;
		u16ParamSize = sizeof(Acs_SetFaxBps);
		p = (void *)&g_FaxBpsParam;
		break;
	//////////
	case SET_PARAM_TYPE_FAX_ADDFILE: //17: //FAX Multi-File Transfer 		

		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_FAX )
		{
			AfxMessageBox("Dev1 is NOT An FAX Device!");
			return;
		}

		nRes = My_p_FaxMultiFile.DoModal ();
		if ( nRes != IDOK )
		{
			return ;
		}

		u16ParamType = FAX_PARAM_ADDFAXFILE;
		u16ParamSize = sizeof(Acs_TransAddFile);
		p = (void *)&g_FaxMultiFileParam;
		break;
	//////////
	case SET_PARAM_TYPE_EM: //18: //14: //em
		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH || 
			 DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub  != XMS_DEVSUB_ANALOG_EM )
		{
			AfxMessageBox("Dev1 is NOT An AnalogEM Device!");
			return;
		}

		nRes = My_P_EM.DoModal ();
		if ( nRes != IDOK )
		{
			return ;
		}

		//g_ATrunkFlash.m_VocDevID = DevOpened[iOpenedIndex2].DevID;

		u16ParamType = XMS_AEM_PARAM_SND_M_SIGNAL;
		u16ParamSize = sizeof(Acs_AnalogEM_CMD);
		p = (void *)&g_ATrunkEM;
		break;   
	case SET_PARAM_TYPE_DSS1_CALL_TYPE: //18: //14: //em
		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH || 
			 DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub  != XMS_DEVSUB_E1_DSS1 )
		{
			AfxMessageBox("Dev1 is NOT An AnalogEM Device!");
			return;
		}

		iParam = 1;
		u16ParamType = ISDN_PARAM_CALLTYPE;
		u16ParamSize = 1;
		
		i = 0;
		p = (void *)&iParam;
		break;   

	case SET_PARAM_TYPE_DSS1_APPENDCALLEE: //18: //14: //em
		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH || 
			 DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub  != XMS_DEVSUB_E1_DSS1 )
		{
			AfxMessageBox("Dev1 is NOT An AnalogEM Device!");
			return;
		}


		u16ParamType = ISDN_PARAM_APPENDCALLEE;
		u16ParamSize = 2;
		
		iTemp = i;

		if ( (MAX_CODE_NUMBERS - 1) == i )
		{
			strTemp[0] = '0';
		}
		else
		{
			strTemp[0] = '0';
		}

		strTemp[1] = str[iTemp];

		{
			r = XMS_ctsSetParam( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, u16ParamType, u16ParamSize, (DJ_Void *)&strTemp[0]);
			if ( r < 0 )
			{
				sprintf ( MsgStr, "X(%d) XMS_ctsSetParam( ParamType = %s ) FAIL! (%s)", 
					r, ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
				AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
			}
			else
			{
				sprintf ( MsgStr, "XMS_ctsSetParam( ParamType = %s ) OK! (%s)", 
					ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
				AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
			}
		}

		iTemp++;
		if ( iTemp >= MAX_CODE_NUMBERS ) 
			iTemp = 0;

		i = iTemp;
		return;

	case SET_PARAM_TYPE_DSS1_CALL_PARAM:
		{
			if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH || 
			 DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub  != XMS_DEVSUB_E1_DSS1 )
			{
				AfxMessageBox("Dev1 is NOT An AnalogEM Device!");
				return;
			}

			memset( &g_DSS1CallParam, 0, sizeof(ITP_Q931_CALL_PARAM) );

			g_DSS1CallParam.m_u8Cap = ITP_Q931_CAP_UNREST_DIG;
			g_DSS1CallParam.m_u8Rate = ITP_Q931_RATE_64KBPS;
			g_DSS1CallParam.m_u8UIL1 = ITP_Q931_UIL1_H223_H245;
			g_DSS1CallParam.m_u8CallerType = ITP_Q931_CALLNUM_UNKNOWN;
			g_DSS1CallParam.m_u8CallerSubType = ITP_Q931_CALLNUM_UNKNOWN;
			g_DSS1CallParam.m_u8CalleeType = ITP_Q931_CALLNUM_UNKNOWN;
			g_DSS1CallParam.m_u8CalleeSubType = ITP_Q931_CALLNUM_UNKNOWN;

			g_DSS1CallParam.m_u8CallerPlan = ITP_Q931_NUMPLAN_ISDN;
			g_DSS1CallParam.m_u8CallerSubPlan = ITP_Q931_NUMPLAN_ISDN;
			g_DSS1CallParam.m_u8CalleePlan = ITP_Q931_NUMPLAN_ISDN;
			g_DSS1CallParam.m_u8CalleeSubPlan = ITP_Q931_NUMPLAN_ISDN;

			nRes = My_DSS1CallParam.DoModal ();
			if ( nRes != IDOK )
			{
				memset( &g_DSS1CallParam, 0, sizeof(ITP_Q931_CALL_PARAM) );
			}

			u16ParamType = ISDN_PARAM_CALLOUT;
			u16ParamSize = sizeof(PITP_Q931_CALL_PARAM);


			//p = (void *)&g_DSS1CallParam;
			p = (void *)&g_DSS1CallParam;
		}
		break;

	case SET_PARAM_TYPE_DSS1_ORICALLER:
		{
			if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH || 
			 DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub  != XMS_DEVSUB_E1_DSS1 )
			{
				AfxMessageBox("Dev1 is NOT An AnalogEM Device!");
				return;
			}

			memset( &g_DSS1OriNumParam, 0, sizeof(ITP_Q931_ORINUM_PARAM) );

			g_DSS1OriNumParam.m_u8NumberType = ITP_Q931_CALLNUM_UNKNOWN;
			g_DSS1OriNumParam.m_u8NumberPlan = ITP_Q931_NUMPLAN_ISDN;
			strcpy( g_DSS1OriNumParam.m_szChangeNumber, "156579" );

/*			nRes = My_DSS1CallParam.DoModal ();
			if ( nRes != IDOK )
			{
				memset( &g_DSS1CallParam, 0, sizeof(ITP_Q931_CALL_PARAM) );
			}
*/
			u16ParamType = ISDN_PARAM_ORINUMBER;
			u16ParamSize = sizeof(ITP_Q931_ORINUM_PARAM);

			p = (void *)&g_DSS1OriNumParam;
		}
		break;

	case SET_PARAM_TYPE_RTPX: //19: //17:
		if(DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_RTPX)
		{
			AfxMessageBox("Dev1 is not a RTPX device!");
			return;
		}

		if(My_p_ParamType.DoModal() != IDOK)
			return;
		
		switch(My_p_ParamType.m_iParamType)
		{
		case XMS_RTPX_PARAM_INPUT:	
			if(My_p_RtpxInput.DoModal() != IDOK)
				return;
					
			memset(&paramIn, 0, sizeof(paramIn));
			paramIn.m_u8ChanEnable = My_p_RtpxInput.m_bEnable;
			paramIn.m_u8MediaType = My_p_RtpxInput.m_uiMediaType;
			paramIn.m_u8PayloadType = My_p_RtpxInput.m_uiPayload;
			
			u16ParamType = XMS_RTPX_PARAM_INPUT;
			u16ParamSize = sizeof(paramIn);
			p = (void *)&paramIn;
			break;
		case XMS_RTPX_PARAM_OUTPUT:
			if(My_p_RtpxOutput.DoModal() != IDOK)
				return;

			memset(&paramOut, 0, sizeof(paramOut));
			paramOut.m_u8ChanEnable = My_p_RtpxOutput.m_bEnable;
			paramOut.m_u8MediaType = My_p_RtpxOutput.m_uiMediaType;
			paramOut.m_u8PayloadType = My_p_RtpxOutput.m_uiPayload;
			
			paramOut.m_u8SRC_Ctrl1 = My_p_RtpxOutput.m_uiSrcCtrl;
			paramOut.m_u16SRC_Id1 = My_p_RtpxOutput.m_uiSrcId;
		
			paramOut.m_u32RemoteIP = My_p_RtpxOutput.m_uiIP;
			paramOut.m_u16RemotePort = My_p_RtpxOutput.m_uiPort;
		
			u16ParamType = XMS_RTPX_PARAM_OUTPUT;
			u16ParamSize = sizeof(paramOut);
			p = (void *)&paramOut;
			break;
		case XMS_RTPX_PARAM_MIXER:
			if(My_p_RtpxMixer.DoModal() != IDOK)
				return;
			
			memset(&paramMixer, 0, sizeof(paramMixer));
			paramMixer.m_u8SRC1_Ctrl = My_p_RtpxMixer.m_uiSrcCtrl;
			paramMixer.m_u16SRC_ChID1 = My_p_RtpxMixer.m_uiSrcId;

			u16ParamType = XMS_RTPX_PARAM_MIXER;
			u16ParamSize = sizeof(paramMixer);
			p = (void *)&paramMixer;
			break;
		case XMS_RTPX_PARAM_ADDR:
			if(My_p_RtpxAddr.DoModal() != IDOK)
				return;
				
			memset(&paramAddr, 0, sizeof(paramAddr));
			paramAddr.m_u32RemoteIP = My_p_RtpxAddr.m_uiIP;
			paramAddr.m_u16RemotePort = My_p_RtpxAddr.m_uiPort;

			u16ParamType = XMS_RTPX_PARAM_ADDR;
			u16ParamSize = sizeof(paramAddr);
			p = (void *)&paramAddr;				
			break;
		}
		
		break;
	case SET_PARAM_TYPE_MEDIAEX_PARAM: // 20: //18:  mediaEx //SET_PARAM_TYPE_MEDIAEX_PARAM
		if(DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_MEDIAEX)
		{
			AfxMessageBox("Dev1 is not a MediaEx device!");
			return;
		}

		if(My_p_MediaExParam.DoModal() != IDOK)
			return;
		
		switch(My_p_MediaExParam.m_iParamType)
		{
		case MEDIAEX_PARAM_INPUT:	
//			memset(&MediaExIn, 0, sizeof(Acs_MediaEx_Input)*My_p_MediaExParam.m_uiChNum);
//			for(i = 0; i < (DJ_S32)My_p_MediaExParam.m_uiChNum; i++)
//			{
//				if(My_p_MediaExInput.DoModal() != IDOK)
//					break;
//
//				MediaExIn[i].m_u8Codec = My_p_MediaExInput.m_uiMedia;
//				MediaExIn[i].m_u8PayloadType = My_p_MediaExInput.m_uiPT;
//				MediaExIn[i].m_u16Port = My_p_MediaExInput.m_uiPort;
//				MediaExIn[i].m_u32ProfileLevelId = My_p_MediaExInput.m_uiLevel;
//			}
//		
//			
//			u16ParamType = MEDIAEX_PARAM_INPUT;
//			u16ParamSize = sizeof(Acs_MediaEx_Input)*My_p_MediaExParam.m_uiChNum;
//			p = (void *)&MediaExIn;
			break;
		case MEDIAEX_PARAM_OUTPUT:
//			memset(&MediaExOut, 0, sizeof(Acs_MediaEx_Output)*My_p_MediaExParam.m_uiChNum);
//			for(i = 0; i < (DJ_S32)My_p_MediaExParam.m_uiChNum; i++)
//			{
//				if(My_p_MediaExOutput.DoModal() != IDOK)
//					break;
//				
//				MediaExOut[i].m_u8Codec = My_p_MediaExOutput.m_uiMedia;
//				MediaExOut[i].m_u8PayloadType = My_p_MediaExOutput.m_uiPT;
//				strcpy(MediaExOut[i].m_s8IP, My_p_MediaExOutput.m_sIP);
//				MediaExOut[i].m_u16Port = My_p_MediaExOutput.m_uiPort;
//				MediaExOut[i].m_u16ResX = My_p_MediaExOutput.m_uiX;
//				MediaExOut[i].m_u16ResY = My_p_MediaExOutput.m_uiY;
//				MediaExOut[i].m_u8MaxFps = My_p_MediaExOutput.m_uiFPS;
//				MediaExOut[i].m_u16Kbps = My_p_MediaExOutput.m_uiKbps;
//			}
//			
//			
//			u16ParamType = MEDIAEX_PARAM_OUTPUT;
//			u16ParamSize = sizeof(Acs_MediaEx_Output)*My_p_MediaExParam.m_uiChNum;
//			p = (void *)&MediaExOut;
			break;
		default:
			break;
		}

		break;
	case SET_PARAM_TYPE_CONF_PARAM: //21: //SET_PARAM_TYPE_CONF_PARAM
		{		
			//memset(&g_stParamConf, 0, sizeof(CmdParamConf_VadInterval_t);	
			CConfParaSetDlg dlg;

			if ( IDOK == dlg.DoModal())
			{
				u16ParamType = CONF_PARAM_UNIPARAM;
				u16ParamSize = sizeof(CmdParamConf_VadInterval_t);
				p = (void *)&g_stParamConf;
			}
			else
				return;
		}
		break;

	case SET_PARAM_TYPE_ACS_PARAM:                  // author:chnez 
		{

			/*
			XMS_DEVMAIN_INTERFACE_CH        main
			 XMS_DEVSUB_ANALOG_TRUNK         sub
			*/
			if(DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH)
			{
				AfxMessageBox("Dev1 is not a INTERFACE device!");
				return;
			}

			nRes = My_UserReadXmsBoardInfo.DoModal();
			u16ParamType = ANALOGTRUNK_PARAM_READSN;
			u16ParamSize = sizeof(Acs_ParamData_UserReadXmsBoardInfo);
			p = (void * )&g_UserReadXmsBoardInfo;
		}
		break;

	case SET_PARAM_TYPE_SS7RAWFRAME_PARAM:          // author:chnez 
		{
		/*
		XMS_DEVMAIN_INTERFACE_CH        main
		
		  XMS_DEVSUB_E1_SS7_TUP  
		  XMS_DEVSUB_E1_SS7_ISUP          sub
			*/
			
			if( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH  )
			{
				AfxMessageBox("Dev1 is not a INTERFACE device!");
				return;
			}
			
			if (DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub != XMS_DEVSUB_E1_SS7_TUP && DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub != XMS_DEVSUB_E1_SS7_ISUP) 
			{
				AfxMessageBox("Dev1 is not a TUP or ISUP device!");
				return;
			}
			
			nRes = My_SS7RawFrameParam.DoModal ();
			if ( nRes != IDOK )
			{
				return ;
			}
			u16ParamType = XMS_SS7_USER_SCCP;
			u16ParamSize = sizeof(CmdParamData_SS7RawFrame_t);
			p = (void * )&g_SS7RawFrameParam;
		}
		break;
	case SET_PARAM_TYPE_CAS_CMDPARAM:               // author:chnez
		{
			/*
			XMS_DEVMAIN_INTERFACE_CH        main
			 XMS_DEVSUB_E1_CAS              sub
			*/

			if(DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH)
			{
				AfxMessageBox("Dev1 is not a INTERFACE device!");
				return;
			}

			if(DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub != XMS_DEVSUB_E1_CAS)
			{
				AfxMessageBox("Dev1 is not a CAS device!");
				return;
			}

			nRes = My_CmdParamDataCAS.DoModal();
			u16ParamType = CAS_PARAM_UNIPARAM;
			u16ParamSize = sizeof(CmdParamData_CAS_t);
			p = (void * )&g_CmdParamDataCAS;
		}
		break;
	default:
		{
			sprintf ( MsgStr, "Parameter Type[%s] Not Support!", ParamTypeStr[iComboParam] );
			AfxMessageBox ( MsgStr );
			AddMsg ( MSG_TYPE_OTHER, MsgStr );
			return;
		}
    }

	if( g_Select == 0)
	{
		r = XMS_ctsSetParam( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, u16ParamType, u16ParamSize, (DJ_Void *)p );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsSetParam( ParamType = %s ) FAIL! (%s)", 
				r, ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsSetParam( ParamType = %s ) OK! (%s)", 
				ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
	else
	{
		r = XMS_ctsSetParam( g_acsHandle, &DevOpened[iOpenedIndex3].DevID, u16ParamType, u16ParamSize, (DJ_Void *)p );
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsSetParam( ParamType = %s ) FAIL! (%s)", 
				r, ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsSetParam( ParamType = %s ) OK! (%s)", 
				ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}

}

void	DoFunc_GetParam(void)
{
	RetCode_t	r;
	char		MsgStr[160];

	// parameter
	DJ_U16		u16ParamType, u16ParamSize;
	DJ_Void *   pParam = NULL;  
	Get3gppCfg_t tempCfg;
	CmdParamData_ReadVoltage_t  tempreadvolt;

#ifndef	DEBUG_IN_HOME_NOTEBOOK
	if ( !bStartWorkFlag )	return;

if ( iComboGetParam != 6 )
{
	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;
}

#endif

	switch (iComboGetParam)
	{
	case 0:		// Voice
		{
			if ( (DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_VOICE)
			  || (DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub != XMS_DEVSUB_MEDIA_324))
			{
				AfxMessageBox("Dev1 is NOT A 324 Voc Device!");
				return;
			}

			C3gppConfgDlg dlg;
			r = dlg.DoModal();
			if (IDOK != r)
			{
				return;
			}

	        u16ParamType = H324_PARAM_MEDIA;
			
			u16ParamSize = sizeof(Get3gppCfg_t);

	        memcpy(&tempCfg, &g_Get3gpCfg, u16ParamSize );
            pParam = (DJ_Void*)&tempCfg;
		}
		break;

	case 1:		// VOIP
		if( !CheckOpenDeviceForVoIP(iOpenedIndex1 ) )
			return;

		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_VOIP)
		{
			AfxMessageBox("Dev1 is NOT A Voip Device!");
			return;
		}
        
        u16ParamType = VOIP_PARAM_RTPCODEC;
		u16ParamSize = 0;
		break;
	case 2:		// board
		if( !CheckOpenDeviceForVoIP(iOpenedIndex1 ) )
			return;

		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_BOARD)
		{
			AfxMessageBox("Dev1 is NOT A Board Device!");
			return;
		}
        
        u16ParamType = BOARD_PARAM_GETBOARDINFO;
		u16ParamSize = 0;
		break;
	case 5:		// Conf
		if( !CheckOpenDeviceForVoIP(iOpenedIndex1 ) )
			return;

		if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_CONFERENCE )
		{
			AfxMessageBox("Dev1 is NOT A Conf Device!");
			return;
		}
        
        u16ParamType = CONF_PARAM_VAD;
		u16ParamSize = 0;
		break;

	case 6:		// Anolog user
	//if( !CheckOpenDeviceForVoIP(iOpenedIndex1 ) )
	//	return;

	if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH
		&& DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub != XMS_DEVSUB_ANALOG_USER )
	{
		AfxMessageBox("Dev1 is NOT A User Device!");
		return;
	}
    
    u16ParamType = ANALOGUSER_PARAM_READSN;
	u16ParamSize = 0;
	break;
	case 7:		// Anolog voc2
	//if( !CheckOpenDeviceForVoIP(iOpenedIndex1 ) )
	//	return;

	if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH
		&& DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub != XMS_DEVSUB_ANALOG_VOC2W )
	{
		AfxMessageBox("Dev1 is NOT A User Device!");
		return;
	}
    
    u16ParamType = ANALOGVOC2_PARAM_READSN;
	u16ParamSize = 0;
	break;
	case 8:		// Anolog voc4
	//if( !CheckOpenDeviceForVoIP(iOpenedIndex1 ) )
	//	return;

	if ( DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain != XMS_DEVMAIN_INTERFACE_CH
		&& DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub != XMS_DEVSUB_ANALOG_VOC4W )
	{
		AfxMessageBox("Dev1 is NOT A User Device!");
		return;
	}
    
    u16ParamType = ANALOGVOC4_PARAM_READSN;
	u16ParamSize = 0;
	break;

	case 9:		// get mod voltage 
		u16ParamType = ANALOGHIZ_PARAM_GET_VOLTAGE ;  //then same value for all analog module
		u16ParamSize = sizeof(CmdParamData_ReadVoltage_t);	
		tempreadvolt.m_u8ReadFlag = 1;
		tempreadvolt.m_u32TimeSpan = 0;
		pParam = (DJ_Void*)&tempreadvolt;
		break;
	case 10:
		u16ParamType = ISDN_PARAM_ORINUMBER;  //then same value for all analog module
		u16ParamSize = 0;
		break;
  default:
	sprintf ( MsgStr, "Parameter Type[%s] Not Support!", ParamTypeStr[iComboParam] );
	AfxMessageBox ( MsgStr );
	AddMsg ( MSG_TYPE_OTHER, MsgStr );
	return;
	}

	if( g_Select == 0)
	{
		r = XMS_ctsGetParam( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, u16ParamType, u16ParamSize, pParam);
   		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsGetParam( ParamType = %s ) FAIL! (%s)", 
				r, ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsGetParam( ParamType = %s ) OK! (%s)", 
				ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
	else
	{
		r = XMS_ctsGetParam( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, u16ParamType, u16ParamSize, pParam);
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsGetParam( ParamType = %s ) FAIL! (%s)", 
				r, ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsGetParam( ParamType = %s ) OK! (%s)", 
				ParamTypeStr[iComboParam], GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
}

void	DoFunc_InitPlayIndex(void)
{
	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	if ( XMS_DEVSUB_MEDIA_VOC == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		r = XMS_ctsInitPlayIndex( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, NULL );

		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsInitPlayIndex( ) FAIL! (%s)", 
				r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsInitPlayIndex( ) OK! (%s)", 
				GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}
	else if ( XMS_DEVSUB_MEDIA_324 == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		r = XMS_ctsInitPlay3gppIndex( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, NULL );

		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsInitPlay3gppIndex( ) FAIL! (%s)", 
				r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsInitPlay3gppIndex( ) OK! (%s)", 
				GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
	}

	pdlg->m_ComboIndexList.ResetContent();
}

void	DoFunc_BuildPlayIndex_Real(void)
{
	RetCode_t	r;
	char		MsgStr[160], TmpS[32];

	if ( g_BuildIndexProperty.m_u16PlayType == XMS_BUILD_INDEX_FILE )
		strcpy ( TmpS, "(FILE)" );
	else
		strcpy ( TmpS, "(RAM )" );

	//g_BuildIndexProperty.m_u16PlayIndex = 0 ;
	r = XMS_ctsBuildPlayIndex ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, &g_BuildIndexProperty, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsBuildPlayIndex( %s %s ) FAIL! (%s)", 
			r, TmpS, g_BuildIndexProperty.m_s8PlayContent, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsInitPlayIndex( %s %s ) OK! (%s)", 
			TmpS, g_BuildIndexProperty.m_s8PlayContent, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}

	// add to the Combo
	sprintf ( MsgStr, "%2d - %s %s", pdlg->m_ComboIndexList.GetCount(), TmpS, g_BuildIndexProperty.m_s8PlayContent );
	pdlg->m_ComboIndexList.AddString (MsgStr);
	pdlg->m_ComboIndexList.SetCurSel (pdlg->m_ComboIndexList.GetCount()-1);
}

void	DoFunc_BuildPlayIndex(void)
{
	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	if ( XMS_DEVSUB_MEDIA_VOC == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		CXMSApi_BuildIndex	MyBuildIndex;

		MyBuildIndex.DoModal ();	
	}
	else if ( XMS_DEVSUB_MEDIA_324 == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub )
	{
		CXMSApi_3GPP_BuildIndex	MyBuildIndex;

		MyBuildIndex.DoModal ();		
	}
}

void	DoFunc_SendIOData(void)
{
	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	CXMSApi_SendIOData	MySendIOData;

	MySendIOData.DoModal ();
}

void	DoFunc_ConnDsp(void)
{
	ServerID_t serverID={0};
	char szBuf[40]={0};
	char MsgStr[100]={0};

	if ( !bStartWorkFlag )	return;
	
	pdlg->GetDlgItem ( IDC_EDIT_DSPPORT )->GetWindowText (szBuf , 40);
	serverID.m_u32ServerPort = atoi(szBuf);
	pdlg->GetDlgItem ( IDC_EDIT_DSPIP )->GetWindowText (serverID.m_s8ServerIp,sizeof(serverID.m_s8ServerIp));
	GetPrivateProfileString("ConfigInfo","UserName","",serverID.m_s8UserName,sizeof(serverID.m_s8UserName),cfg_IniName);
	GetPrivateProfileString("ConfigInfo","PassWord","",serverID.m_s8UserPwd,sizeof(serverID.m_s8UserPwd),cfg_IniName);

	memcpy( &g_stCSPServerID, &serverID, sizeof(g_stCSPServerID) );

	int r = XMS_acsOpenStreamExt(g_acsHandle,&serverID,NULL);

	if ( ACSPOSITIVE_ACK != r )
	{
		sprintf ( MsgStr, "X(%d) XMS_acsOpenStreamExt() FAIL! ", r );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_acsOpenStreamExt() OK!" );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}		
}

void DoFunc_DisConnDsp()
{
	ServerID_t serverID={0};
	char szBuf[40]={0};
	char MsgStr[100]={0};

	if ( !bStartWorkFlag )	return;
	
	pdlg->GetDlgItem ( IDC_EDIT_DSPPORT )->GetWindowText (szBuf , 40);
	serverID.m_u32ServerPort = atoi(szBuf);
	pdlg->GetDlgItem ( IDC_EDIT_DSPIP )->GetWindowText (serverID.m_s8ServerIp,sizeof(serverID.m_s8ServerIp));
	GetPrivateProfileString("ConfigInfo","UserName","",serverID.m_s8UserName,sizeof(serverID.m_s8UserName),cfg_IniName);
	GetPrivateProfileString("ConfigInfo","PassWord","",serverID.m_s8UserPwd,sizeof(serverID.m_s8UserPwd),cfg_IniName);

	int r = XMS_acsCloseStreamExt(g_acsHandle,&serverID,NULL);	
	if ( ACSPOSITIVE_ACK != r )
	{
		sprintf ( MsgStr, "X(%d) XMS_acsCloseStreamExt() FAIL! ", r );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_acsCloseStreamExt() OK! " );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void DoFunc_RecCSP()
{
	CSP_OPERATER*pCSP = GetCurrVocCSPProperty( );

	if ( NULL == pCSP )
		return;
	
	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	g_RecCSPDevID = pCSP->m_RecCSPDevID;
	if ( 0 != g_RecCSPDevID.m_s16DeviceMain )
	{
		DoShowMessage("This channel has running CSP Recording. ");
		return;
	}

	g_RecCSPDevID  = DevOpened[iOpenedIndex1].DevID;
	pCSP->m_RecCSPDevID = g_RecCSPDevID;
	
	CRecCSPDlg RecCSPDlg;

	RecCSPDlg.DoModal();
}

void DoFunc_CtrlRecCSP( DJ_S32 i32ControlType )
{
	int  r = 0;
	char MsgStr[100]={0};
	ControlRecord_t ctrlRecCSP;
	CSP_OPERATER*pCSP = GetCurrVocCSPProperty( );

	if ( NULL == pCSP )
		return;

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	g_RecCSPDevID = pCSP->m_RecCSPDevID;
	if ( DevOpened[iOpenedIndex1].DevID.m_s8MachineID != g_RecCSPDevID.m_s8MachineID
	  || DevOpened[iOpenedIndex1].DevID.m_s8ModuleID != g_RecCSPDevID.m_s8ModuleID
	  || DevOpened[iOpenedIndex1].DevID.m_s16ChannelID != g_RecCSPDevID.m_s16ChannelID )
	{
		return;
	}

	memset(&ctrlRecCSP,0,sizeof(ctrlRecCSP));
	ctrlRecCSP.m_u32ControlType = i32ControlType;

	r = XMS_ctsControlRecordCSP(g_acsHandle, &g_RecCSPDevID,&ctrlRecCSP,NULL);
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsControlRecordCSP() FAIL! (%s)", 
			r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsControlRecordCSP() OK! (%s)", 
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}

	g_cspRecordFp = pCSP->m_cspRecordFp;
	if ( NULL != g_cspRecordFp )
		fclose(g_cspRecordFp);

	memset( &g_RecCSPDevID, 0, sizeof(g_RecCSPDevID) );

	pCSP->m_cspRecordFp = g_cspRecordFp = NULL;

	memset( &pCSP->m_RecCSPDevID, 0, sizeof(DeviceID_t) );
}

void	DoFunc_StartFaxT38(void)
{
	char		  DevStr1[64], DevStr2[64],DevStr3[64];

	char		  MsgStr[160];

	sprintf ( DevStr1, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID));
	sprintf ( DevStr2, GetString_DeviceAll (&DevOpened[iOpenedIndex2].DevID));
	//sprintf ( DevStr3, GetString_DeviceAll (&DevOpened[iOpenedIndex3].DevID));

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1, false) )
		return;

	RetCode_t r = XMS_ctsSendIOData(g_acsHandle, &DevOpened[iOpenedIndex1].DevID,
			XMS_IO_TYPE_VOIP_FAXSTART, 0, NULL);

	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsSendIOData(%s) FAIL! ", 
						r,DevStr1  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsSendIOData(%s) OK! ", 
						r,DevStr3  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_SendFaxT38(void)
{
	RetCode_t	  r;
	char		  MsgStr[160];
	char		  TiffFileName[ACS_MAX_FILE_NAME_LEN];
	char		  s8LocalID[20];
	char		  DevStr1[64], DevStr2[64];
	FaxPrivate_t  faxPriv={0};

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	if ( !CheckOpenDevice (iOpenedIndex2, false) )
		return;
		
	//if ( !CheckOpenDevice (iOpenedIndex3, false) )
	//	return;


	pdlg->GetDlgItem ( IDC_EDIT_SENDFAX )->GetWindowText ( TiffFileName, ACS_MAX_FILE_NAME_LEN-1 );
	sprintf ( s8LocalID, "DJ:83636988" );

	sprintf ( DevStr1, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID));
	sprintf ( DevStr2, GetString_DeviceAll (&DevOpened[iOpenedIndex2].DevID));

	faxPriv.m_PrivateData.m_u32DataSize = sizeof(faxPriv);
	faxPriv.m_VoIPDevice = DevOpened[iOpenedIndex3].DevID;	
	faxPriv.m_u8WorkMode = pdlg->m_FaxType.GetCurSel();
			
	r = XMS_ctsSendFax( g_acsHandle, 
					&DevOpened[iOpenedIndex1].DevID,			// FaxDevice
					&DevOpened[iOpenedIndex2].DevID,			// mediaDevice					
					TiffFileName,
					s8LocalID,
					(PrivateData_t *)(&faxPriv) );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsSendFaxT38(%s, %s) FAIL! fax(%s) media(%s)", 
			r, TiffFileName, s8LocalID,
			DevStr1, DevStr2  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsSendFaxT38(%s, %s) OK! fax(%s) media(%s)", 
			TiffFileName, s8LocalID,
			DevStr1, DevStr2  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_StopSendFaxT38(void)
{
	RetCode_t	 r;
	char		 MsgStr[160];
	FaxPrivate_t faxPriv={0};

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	faxPriv.m_PrivateData.m_u32DataSize = sizeof(faxPriv);
	faxPriv.m_VoIPDevice = DevOpened[iOpenedIndex3].DevID;
	faxPriv.m_u8WorkMode = pdlg->m_FaxType.GetCurSel();

	r = XMS_ctsStopSendFax( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsStopSendFaxT38() FAIL! fax(%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsStopSendFaxT38() OK! fax(%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_ReceiveFaxT38(void)
{
	RetCode_t	 r;
	char		 MsgStr[160];
	char		 TiffFileName[ACS_MAX_FILE_NAME_LEN];
	char		 s8LocalID[20];
	char		 DevStr1[64], DevStr2[64];
	FaxPrivate_t faxPriv={0};

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	if ( !CheckOpenDevice (iOpenedIndex2, false) )
		return;

	if ( !CheckOpenDevice (iOpenedIndex3, false) )
		return;

	pdlg->GetDlgItem ( IDC_EDIT_RECEIVEFAX )->GetWindowText ( TiffFileName, ACS_MAX_FILE_NAME_LEN-1 );
	sprintf ( s8LocalID, "DJ:83636988" );

	sprintf ( DevStr1, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID));
	sprintf ( DevStr2, GetString_DeviceAll (&DevOpened[iOpenedIndex2].DevID));

	faxPriv.m_PrivateData.m_u32DataSize = sizeof(faxPriv);
	faxPriv.m_VoIPDevice = DevOpened[iOpenedIndex3].DevID;
	faxPriv.m_u8WorkMode = XMS_FAX_WORKMODE_SERVER;

	r = XMS_ctsReceiveFax( g_acsHandle, 
					&DevOpened[iOpenedIndex1].DevID,			// FaxDevice
					&DevOpened[iOpenedIndex2].DevID,			// mediaDevice					
					TiffFileName,
					s8LocalID,
					NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsReceiveFaxT38(%s, %s) FAIL! media(%s) fax(%s)", 
			r, TiffFileName, s8LocalID,
			DevStr1, DevStr2  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsReceiveFaxT38(%s, %s) OK! fax(%s) media(%s)", 
			TiffFileName, s8LocalID,
			DevStr1, DevStr2  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_StopReceiveFaxT38(void)
{
	RetCode_t	  r;
	char		  MsgStr[160];
	FaxPrivate_t  faxPriv={0};

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	faxPriv.m_PrivateData.m_u32DataSize = sizeof(faxPriv);
	faxPriv.m_VoIPDevice = DevOpened[iOpenedIndex3].DevID;
	faxPriv.m_u8WorkMode = XMS_FAX_WORKMODE_SERVER;

	r = XMS_ctsStopReceiveFax( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsStopReceiveFaxT38() FAIL! fax(%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsStopReceiveFaxT38() OK! fax(%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void DoFunc_PlayCSP()
{
	CSP_OPERATER*pCSP = GetCurrVocCSPProperty( );

	if ( NULL == pCSP )
		return;

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	if ( 0 == strlen(g_szCSPPlayFile) ) 
		return;

/*	g_PlayCSPDevID = pCSP->m_PlayCSPDevID;
	if ( 0 != g_PlayCSPDevID.m_s16DeviceMain )
	{
		DoShowMessage("This channel has running CSP Playing. ");
		return;
	}*/

	g_cspPlayFp = pCSP->m_cspPlayFp;

	if ( NULL != g_cspPlayFp )
	{
		DoShowMessage("This channel has running CSP Playing. ");
		return;
	}
	
	g_cspPlayFp = fopen(g_szCSPPlayFile,"rb");	
	if(!g_cspPlayFp)
	{
		char		  MsgStr[160];
		sprintf ( MsgStr, "PlayCsp file not found(%s)", g_szCSPPlayFile );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		return;
	}
		
	g_PlayCSPDevID  = DevOpened[iOpenedIndex1].DevID;
	pCSP->m_PlayCSPDevID = g_PlayCSPDevID;
	pCSP->m_cspPlayFp = g_cspPlayFp;

	CCSPPlayDlg playCSPDlg;

	playCSPDlg.DoModal();
}

void	DoFunc_ControlPlayCSP( DJ_S32 s32CSPPlayControlType )
{
	RetCode_t	r;
	char		MsgStr[160];
	ControlPlay_t	controlPlay;

	CSP_OPERATER*pCSP = GetCurrVocCSPProperty( );
	if ( NULL == pCSP )
		return;
	
	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	g_PlayCSPDevID = pCSP->m_PlayCSPDevID;
	
	if ( DevOpened[iOpenedIndex1].DevID.m_s8MachineID != g_PlayCSPDevID.m_s8MachineID
	  || DevOpened[iOpenedIndex1].DevID.m_s8ModuleID != g_PlayCSPDevID.m_s8ModuleID
	  || DevOpened[iOpenedIndex1].DevID.m_s16ChannelID != g_PlayCSPDevID.m_s16ChannelID )
	{
		return;
	}


	//controlPlay.m_u16ControlType = XMS_CSP_DELAY_STOP_PLAY;
	controlPlay.m_u16ControlType = (DJ_U16)s32CSPPlayControlType;

	r = XMS_ctsControlPlay ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, &controlPlay, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) ControlPlayCSP() FAIL! (%s)", 
			r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "ControlPlayCSP() OK! (%s)", 
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}

	g_cspPlayFp = pCSP->m_cspPlayFp;
	if ( NULL != g_cspPlayFp )
	{
		memset( &g_PlayCSPDevID, 0, sizeof(g_PlayCSPDevID) );

		fclose(g_cspPlayFp);
		g_cspPlayFp = NULL;
	}
	
	memset( &pCSP->m_PlayCSPDevID, 0, sizeof(DeviceID_t) );
	pCSP->m_cspPlayFp = 0;
	
}

void DoFunc_GetBoardInfo()
{
	
	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	int size = sizeof(Acs_ParamData_UserReadXmsBoardInfo);
	r = XMS_ctsGetParam ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, BOARD_PARAM_GETBOARDINFO, size,NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsGetParam () FAIL! GetBoardInfo(%s)", r, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsGetParam() OK! GetBoardInfo(%s)", GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	
}

void	DoFunc_Build3GPPPlayIndex_Real(void)
{
	RetCode_t	r;
	char		MsgStr[500], TmpS[64];

	if ( g_Build3gppIndexProperty.m_u16PlayType == XMS_BUILD_INDEX_FILE && g_Build3gppIndexProperty.m_u16VideoPlayType == XMS_BUILD_INDEX_FILE )
		strcpy ( TmpS, "(A-FILE, V-FILE)" );
	else if ( g_Build3gppIndexProperty.m_u16PlayType == XMS_BUILD_INDEX_FILE && g_Build3gppIndexProperty.m_u16VideoPlayType != XMS_BUILD_INDEX_FILE )
		strcpy ( TmpS, "(A-FILE, V-RAM)" );
	else if ( g_Build3gppIndexProperty.m_u16PlayType != XMS_BUILD_INDEX_FILE && g_Build3gppIndexProperty.m_u16VideoPlayType != XMS_BUILD_INDEX_FILE )
		strcpy ( TmpS, "(A-RAM, V-RAM)" );
	else if ( g_Build3gppIndexProperty.m_u16PlayType != XMS_BUILD_INDEX_FILE && g_Build3gppIndexProperty.m_u16VideoPlayType == XMS_BUILD_INDEX_FILE )
		strcpy ( TmpS, "(A-RAM, V-FILE)" );

	//r = XMS_ctsBuildPlayIndex ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, &g_BuildIndexProperty, NULL );
	r = XMS_ctsBuildPlay3gppIndex ( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, &g_Build3gppIndexProperty, NULL );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "A-X(%d) XMS_ctsBuildPlay3gppIndex( %s %s ) FAIL! (%s)", 
			r, TmpS, g_Build3gppIndexProperty.m_s8PlayContent, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		/*sprintf ( MsgStr, "V-X(%d) XMS_ctsBuildPlay3gppIndex( %s %s ) FAIL! (%s)", 
			r, TmpS, g_Build3gppIndexProperty.m_s8VideoPlayContent, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );*/
	}
	else
	{
		sprintf ( MsgStr, "A-XMS_ctsBuildPlay3gppIndex( %s %s ) OK! (%s)", 
			TmpS, g_Build3gppIndexProperty.m_s8PlayContent, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		/*sprintf ( MsgStr, "V-XMS_ctsBuildPlay3gppIndex( %s %s ) OK! (%s)", 
			TmpS, g_Build3gppIndexProperty.m_s8VideoPlayContent, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );*/
	}

	// add to the Combo
	sprintf ( MsgStr, "%2d - %s %s", pdlg->m_ComboIndexList.GetCount(), TmpS, g_Build3gppIndexProperty.m_s8PlayContent );
	pdlg->m_ComboIndexList.AddString (MsgStr);
	pdlg->m_ComboIndexList.SetCurSel (pdlg->m_ComboIndexList.GetCount()-1);
}

/*模拟发送建立会话机制*/
void	DoFunc_SendSignalMsg(DJ_U16      u16SignalMsgType)
{
	RetCode_t	r;
	char		MsgStr[160];

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	r = XMS_ctsSendSignalMsg( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, u16SignalMsgType );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsSendSignalMsg(%u) FAIL! (%s)",
			r, u16SignalMsgType, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsSendSignalMsg(%u) OK! (%s)",
			u16SignalMsgType, GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void	DoFunc_3GPPGetConfig( void )
{
	RetCode_t	r;
	char MsgStr[100]={0};
	Get3gppCfg_t tempCfg;
	DJ_U16 u16ParamCmdType = H324_PARAM_MEDIA;

	memcpy(&tempCfg, &g_Get3gpCfg, sizeof(Get3gppCfg_t) );

	if ( !CheckOpenDevice (iOpenedIndex1) )
		return;

	r = XMS_ctsGetParam( g_acsHandle, &DevOpened[iOpenedIndex1].DevID,  u16ParamCmdType, sizeof(Get3gppCfg_t),(DJ_Void * )&tempCfg);
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsGetParam() FAIL! (%s)", 
			r,
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsGetParam() OK! (%s)", 
			GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
}

void DoFunc_Timer( void )
{
	RetCode_t	r;
	char MsgStr[512] = {0};

	if ( !CheckOpenDevice (iOpenedIndex1) )
	return;

	if ( 0 == g_iTimerType )
	{
		r = XMS_acsSetTimer( g_acsHandle, g_iElapseTime);
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_acsSetTimer() FAIL! (%s)", 
				r,
				GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_acsSetTimer() OK! (%s)", 
				GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}	
	}
	else
	{
		r = XMS_ctsSetDevTimer( g_acsHandle, &DevOpened[iOpenedIndex1].DevID,  g_iElapseTime);
		if ( r < 0 )
		{
			sprintf ( MsgStr, "X(%d) XMS_ctsSetDevTimer() FAIL! (%s)", 
				r,
				GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}
		else
		{
			sprintf ( MsgStr, "XMS_ctsSetDevTimer() OK! (%s)", 
				GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

			AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		}	
	}

	return;
}

void DoFunc_CtxReg()
{
	if ( !bStartWorkFlag )	return;

	//if ( !CheckOpenDevice (iOpenedIndex1, false) )
	//	return;	

	CCtxRegDlg dlg;

	dlg.DoModal();
}

void DoFunc_CTXLink()
{
	char MsgStr[200] = {0};

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex2, false) )
		return;
    
	if ( XMS_DEVMAIN_CTX == DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain )
	{
		if ( XMS_DEVMAIN_CTX != g_stAppData.OthersCTXDevID.m_s16DeviceMain )
		{
			sprintf ( MsgStr, 
				"Invalid DestDevice(%s), it must be sent by XMS_ctxSendAppData function from the other Api_Test.exe first!",
				GetString_DeviceAll(&g_stAppData.OthersCTXDevID) );
			AfxMessageBox ( MsgStr );
			return;
		}

		if ( (DevOpened[iOpenedIndex1].DevID.m_s8ModuleID == g_stAppData.OthersCTXDevID.m_s8ModuleID )
			&& (DevOpened[iOpenedIndex1].DevID.m_s16ChannelID == g_stAppData.OthersCTXDevID.m_s16ChannelID ) )
		{
			sprintf ( MsgStr, 
				"Invalid DestDevice(%s), the srcDev is same to the DestDev!",
				GetString_DeviceAll(&g_stAppData.OthersCTXDevID) );
			AfxMessageBox ( MsgStr );
			return;
		}

		CtxLinkCtxDlg dlg;
		dlg.DoModal();	
	}
	else
	{
		CCtxLinkDlg dlg;
		dlg.DoModal();	
	}
}

void DoFunc_CTXUnLink()
{
	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex2, false) )
		return;

	return;
}

void DoFunc_CTXAppData()
{
	char MsgStr[200] = {0};

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1, false) )
		return;

	if ( XMS_DEVMAIN_CTX != DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain )
	{
		sprintf ( MsgStr, 
			"Invalid DestDevice(%s), The iOpenedIndex1 device is not CTX Device, try again please!",
			GetString_DeviceAll(&DevOpened[iOpenedIndex1].DevID) );
		AfxMessageBox ( MsgStr );
		return;
	}

	CCtxAppData dlg;

	dlg.DoModal();	
}

void  DoFunc_SendSignalData()
{
	char MsgStr[200] = {0};
	RetCode_t r = 0;

	if ( !bStartWorkFlag )	return;

	if ( !CheckOpenDevice (iOpenedIndex1, false) )
		return;

	CSendSignalData dlg;
	dlg.DoModal();

	//do something
}

void DoFunc_LedCtrl()
{
	int nRes = g_LedDlg.DoModal();					
	if(g_LedCtrl.m_u8FeedWatchDogEnable == 1)
	{
		XMS_acsSetTimer(g_acsHandle,5000);
	}
	XMS_acsLedCtrl(g_acsHandle,g_u8LedDspUnit,&g_LedCtrl);
}

void DoFunc_SetMaster()
{
	XMS_acsSetMaster(g_acsHandle,1,NULL);
}


void DoFunc_GetRelateMod()
{
	int nRes = g_GetRelateDlg.DoModal();					
	XMS_acsGetRelateMod( g_acsHandle, g_u8ModuleType, g_u8ModuleUnitID );
}
// --------------------------------------------------------------------
// end of other 
// --------------------------------------------------------------------
