#include "stdafx.h"
#include "XMSApi_Test.h"
#include "XMSApi_TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"

#include "XMSApi_Test_Sub.h"
#include "XMSApi_Test_Event.h"
#include "XMSApi_Test_String.h"
#include "XMSApi_Test_Event.h"

// -------------------------------------------------------
extern	CXMSApi_TestDlg	*pdlg;

int		TotalDevRes = 0;
TYPE_MY_DEVICE_STRUCT	*pDevRes = NULL;

int		TotalDevOpened = 0;
TYPE_MY_DEVICE_STRUCT	DevOpened[MAX_DEVICE_ALLOW_OPEN];

FILE * g_cspPlayFp = NULL;
FILE * g_cspRecordFp = NULL;

extern DeviceID_t g_PlayCSPDevID;
extern DeviceID_t g_RecCSPDevID;

char   g_szCSPPlayFile[MAX_PATH]={0};
char   g_szCSPRecordFile[MAX_PATH]={0};

char   g_szDataBuf[4000] = {0};
int    g_cspPlay = 0;
unsigned char g_u8CSPPlayTaskID = 0;

int			iNowOpIndex = -1;
int			iOpenedIndex1 = -1;
int			iOpenedIndex2 = -1;
int         iOpenedIndex3 = -1;


extern bool				bStartWorkFlag;
extern ACSHandle_t		g_acsHandle;
extern CXMSApi_TestDlg	*pdlg;
extern int g_iSendRecv;

extern Record3gppProperty_t   g_Record3gppProperty;
extern Dev_Codec_Info         g_stCodec;
extern int g_iSetTimerFlag;
extern App_Data_Struct        g_stAppData;
extern char                   g_s8OwnAppName[];
extern char                   g_s8OthersAppName[];
extern DJ_U8                  g_u8IsSendAppDataFlag;

extern DJ_U8                  g_u8LedDspUnit;

extern ServerID_t		cfg_cDSPIpAddr[128];

extern void	DoFunc_ControlPlayCSP( DJ_S32 s32CSPPlayControlType );

int FindOpenDevice(DeviceID_t	*pDev);

void SetRtpMediaInfo(DeviceID_t *pRtpDev, Acs_VoIP_MediaInfo *pMediaInfo);
bool	CheckOpenDevice ( int iIndex, bool	bIsDev1 = true);

void EncodeFskCaller(char* ioDataBuf,char* ioFskBuf,int* iFskLen)
{
	time_t tm1;
	char szSysTime[30];
	struct tm* newtime;

	int iTotal = 0;
	int ioDataLen =strlen(ioDataBuf);

	time(&tm1);
	newtime = localtime(&tm1);
	sprintf(szSysTime,"%02d%02d%02d%02d",
		newtime->tm_mon+1,
		newtime->tm_mday,
		newtime->tm_hour,
		newtime->tm_min);
	
	

	memset(ioFskBuf,0,sizeof(ioFskBuf));

	{
  
		int callerLen = strlen(ioDataBuf);
    
		ioFskBuf[0] = 4 ;
		ioFskBuf[1] = callerLen + 8;
    
		memcpy(ioFskBuf+2,szSysTime,8);
		memcpy(ioFskBuf+10,ioDataBuf,callerLen);
    
		int iTotal = 0 ;
    
		for( int iLoop = 0 ; iLoop< (2+8+ callerLen); iLoop++)
		{
			iTotal += ioFskBuf[iLoop];  
		}
 
		//printf("---AnalogUser Cksum orginal=[%d]---\n",iTotal);
		iTotal %= 256;
		unsigned char cCompliment = iTotal;

		ioFskBuf[10+callerLen] = (~((unsigned char)cCompliment)) + 1;
		ioDataLen = callerLen + 11; 
		*iFskLen = ioDataLen;

	}
}

extern int g_iLen;
extern char g_TmpStr[1024];

AppendCode g_AppendCode[] = {
	{'0','1', 0, 0},
	{'0','5', 0, 0},
	{'0','6', 0, 0},
	{'0','5', 0, 0},
	{'0','7', 0, 0},
	{'1','9', 0, 0},
};

DJ_S8 g_u8AppendSendPos = 0;
DJ_S8 g_u8AppendCodeSize = sizeof(g_AppendCode)/sizeof(AppendCode);

// -------------------------------------------------------
void	DispEventInfo ( Acs_Evt_t *pAcsEvt )
{
	char	TmpStr[512] = {0};
	char	TmpS[512] = {0};

	char		  SendTiffFileName[ACS_MAX_FILE_NAME_LEN];
	char		  RecvTiffFileName[ACS_MAX_FILE_NAME_LEN];
	
	char dtmf='?';

	Acs_Dev_List_Head_t * pAcsDevList = NULL;
	Acs_UniFailure_Data * pAcsUniFailure = NULL;
	Acs_GeneralProc_Data *pGeneralData = NULL;
	Acs_CallControl_Data *pCallControl = NULL;
	//Acs_IO_Data			 *pIOData = NULL;
	Acs_CAS_ExtraInfo_t  *pCAS_ExtraInfo = NULL;
	Acs_AnalogInterface_Data* pAnalogInterface=NULL;
	Acs_CSPDataReq_Data* pCspReqData=NULL;
	Acs_ParamProc_Data*  pSetParam=NULL;
	Acs_ParamProc_Data*  pGetParam=NULL;
	Acs_MediaProc_Data*  pMedia=NULL;
	Acs_ConfControl_Data *pConfEvt = NULL;
	Acs_ParamData_UserReadXmsBoardInfo* pBoardInfor=NULL;
    
	sprintf ( TmpStr, "" );
	strcat ( TmpStr, GetString_EventType ( pAcsEvt->m_s32EventType ) );

	Acs_MediaProc_Data * pMediaData = (Acs_MediaProc_Data *)FetchEventData(pAcsEvt);
	Acs_OpenStreamExt_Data *pEvt = (Acs_OpenStreamExt_Data*)FetchEventData(pAcsEvt);
	Acs_IO_Data			 *pIOData  = (Acs_IO_Data*)FetchEventData(pAcsEvt);
	Acs_ModRelate_Data  *pRelateData = (Acs_ModRelate_Data*)FetchEventData(pAcsEvt);

	switch ( pAcsEvt->m_s32EventType )
	{
	case XMS_EVT_MODRELATE:
		{
			sprintf(TmpS, "SMT: %d, SUID: %d, ", pRelateData->m_u8SrcModType, pRelateData->m_u8SrcModUnitID );
			strcat (TmpStr, TmpS );
			for ( DJ_S32 i = 0; i < pRelateData->m_u8ModCount; i++ )
			{
				sprintf(TmpS, "(MT%d: %d, UID%d: %d, IP: %s, Port: %d)  ", i,pRelateData->m_RelateMod[i].m_u8ModuleType, i, pRelateData->m_RelateMod[i].m_u8UnitID, pRelateData->m_RelateMod[i].m_s8IPAddress, pRelateData->m_RelateMod[i].m_u32Port );
				strcat (TmpStr, TmpS );

				if ( i > 4 && i%4 == 0 )
				{
					strcat(TmpStr, " ");
					AddMsg ( MSG_TYPE_EVENT, TmpStr );
					sprintf ( TmpStr, "" );
					strcat ( TmpStr, GetString_EventType ( pAcsEvt->m_s32EventType ) );
				}
			}
			strcat(TmpStr, " ");
		}
		break;
	case XMS_EVT_ACS_TIMER:
		{
				strcat(TmpStr, " ");
				//strcat ( TmpStr, GetString_DeviceAll (&pAcsEvt->m_DeviceID) );
				strcat (TmpStr, "EVT" );
		}
		break;

	case XMS_EVT_DEV_TIMER:
		{         
			if ( 1 == g_iSetTimerFlag )
			{
				strcat(TmpStr, " ");
				strcat ( TmpStr, GetString_DeviceAll (&pAcsEvt->m_DeviceID) );

				g_iSetTimerFlag = 0;
			}
			else
			{
				char ioFskBuf[512] = {0};
				int iFskLen, iIODataType;
				char MsgStr[512];

				memset(ioFskBuf,0,sizeof(ioFskBuf));
				pdlg->GetDlgItemText(IDC_EDIT_CALLINGNUM, MsgStr, sizeof(MsgStr) );

				if ( 1 == ((CButton *)pdlg->GetDlgItem ( IDC_RADIO_CALLER_DTMF ))->GetCheck() )
				{
					strcpy(ioFskBuf, MsgStr);
					iIODataType = XMS_IO_TYPE_DTMF;					
					iFskLen = strlen(ioFskBuf);
				}
				else
				{
					EncodeFskCaller(MsgStr,ioFskBuf,&iFskLen);
					iIODataType = XMS_IO_TYPE_FSK;					
				}

				int r = XMS_ctsSendIOData ( g_acsHandle, &pAcsEvt->m_DeviceID, 
				iIODataType, (DJ_U16)iFskLen, (DJ_Void *) ioFskBuf );
				if ( r < 0 )
				{
					sprintf ( MsgStr, "X(%d) XMS_ctsSendIOData( %s, %d, [%s] ) FAIL! (%s)", 
						r, "GTG ", g_iLen, TmpStr, 
						GetString_DeviceAll (&pAcsEvt->m_DeviceID)  );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
				}
				else
				{
					sprintf ( MsgStr, "XMS_ctsSendIOData( %s, %d, [%s] ) OK! (%s)", 
						"GTG ", g_iLen, TmpStr,  
						GetString_DeviceAll (&pAcsEvt->m_DeviceID)  );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
				}			
			}
		}
		break;
	case XMS_EVT_BUILDINDEX:
		pMedia=(Acs_MediaProc_Data*)FetchEventData(pAcsEvt);
		sprintf(TmpS," EvtState=%d taskID=%d fileIndex=%u,%x",pMedia->m_s32AcsEvtState,pMedia->m_u8TaskID,pMedia->m_u32CurFileIndex,pMedia->m_u32CurFileIndex);
		strcat(TmpStr,TmpS);
		break;
	case XMS_EVT_PLAY:
		pMedia=(Acs_MediaProc_Data*)FetchEventData(pAcsEvt);
		sprintf(TmpS," EvtState=%d Errcode=%s taskID=%d fileIndex=%d, len: %d",pMedia->m_s32AcsEvtState, GetStringMediaErrCode(pMedia->m_s32AcsEvtState,pMedia->m_s32AcsEvtErrCode),pMedia->m_u8TaskID,pMedia->m_u32CurFileIndex, pMedia->m_u32CurFilePos);
		strcat(TmpStr,TmpS);
		break;
	case XMS_EVT_RECORD:
		pMedia=(Acs_MediaProc_Data*)FetchEventData(pAcsEvt);
		sprintf(TmpS," EvtState=%d Errcode=%s taskID=%d fileIndex=%d, len: %d",pMedia->m_s32AcsEvtState,GetStringMediaErrCode(pMedia->m_s32AcsEvtState,pMedia->m_s32AcsEvtErrCode),pMedia->m_u8TaskID,pMedia->m_u32CurFileIndex, pMedia->m_u32CurFilePos);
		strcat(TmpStr,TmpS);
		break;
	case XMS_EVT_JOINTOCONF:
		 pConfEvt = (Acs_ConfControl_Data*)FetchEventData(pAcsEvt);
		//sprintf(TmpS," EvtState=%d Errcode=%s Members=%d VOC(dsp: %d, ch: %d)",pConfEvt->m_s32AcsEvtState, GetStringConfErrCode(pConfEvt->m_s32AcsEvtState,pConfEvt->m_s32AcsEvtErrCode),pConfEvt->m_s32ConfMembers,pConfEvt->m_MediaDevice.m_s8ModuleID,pConfEvt->m_MediaDevice.m_s16ChannelID);
		sprintf(TmpS," EvtState=%d Errcode=%d Members=%d VOC(dsp: %d, ch: %d)",pConfEvt->m_s32AcsEvtState, pConfEvt->m_s32AcsEvtErrCode,pConfEvt->m_s32ConfMembers,pConfEvt->m_MediaDevice.m_s8ModuleID,pConfEvt->m_MediaDevice.m_s16ChannelID);
		strcat(TmpStr,TmpS);
		 
		break;
	case XMS_EVT_LEAVEFROMCONF:	
		 pConfEvt = (Acs_ConfControl_Data*)FetchEventData(pAcsEvt);
		sprintf(TmpS," EvtState=%d Errcode=%d Members=%d VOC(dsp: %d, ch: %d)",pConfEvt->m_s32AcsEvtState, pConfEvt->m_s32AcsEvtErrCode,pConfEvt->m_s32ConfMembers,pConfEvt->m_MediaDevice.m_s8ModuleID,pConfEvt->m_MediaDevice.m_s16ChannelID);
		strcat(TmpStr,TmpS);
		 
		break;
	case XMS_EVT_CLEARCONF:	
		 pConfEvt = (Acs_ConfControl_Data*)FetchEventData(pAcsEvt);
		sprintf(TmpS," EvtState=%d Errcode=%d Members=%d VOC(dsp: %d, ch: %d)",pConfEvt->m_s32AcsEvtState, pConfEvt->m_s32AcsEvtErrCode,pConfEvt->m_s32ConfMembers,pConfEvt->m_MediaDevice.m_s8ModuleID,pConfEvt->m_MediaDevice.m_s16ChannelID);
		strcat(TmpStr,TmpS);
		 
		break;

	case XMS_EVT_SETPARAM:
		pSetParam = (Acs_ParamProc_Data*)FetchEventData(pAcsEvt);
		sprintf(TmpS," CmdType=[%d]",pSetParam->m_u16ParamCmdType);
		strcat(TmpStr,TmpS);
		break;

	case XMS_EVT_UNLINKDEVICE:
		pGeneralData = (Acs_GeneralProc_Data*) FetchEventData(pAcsEvt);
		break;
	case XMS_EVT_PLAYCSPREQ:
		//
		pCspReqData = (Acs_CSPDataReq_Data*)FetchEventData(pAcsEvt);
		sprintf(TmpS,"CSPPLAYREQ datalen =%d",pCspReqData->m_u16ReqCspDataLen);
		strcat(TmpStr,TmpS);
		break;

	case XMS_EVT_ANALOG_INTERFACE:
		pAnalogInterface = (Acs_AnalogInterface_Data*)FetchEventData(pAcsEvt);
		sprintf(TmpS,"(%d,%s)",pAnalogInterface->m_u8AnalogInterfaceState,GetString_AnalogInterfaceState(pAcsEvt->m_DeviceID.m_s16DeviceSub,pAnalogInterface->m_u8AnalogInterfaceState));
		strcat(TmpStr,TmpS);
		break;
	case XMS_EVT_SENDIODATA:

		sprintf ( TmpS, " (%s,%s,MachineID:%2d,ModuleID:%3d,Ch:%d), IOType: %s", 
			GetString_DeviceMain(pAcsEvt->m_DeviceID.m_s16DeviceMain),
			GetString_DeviceSub(pAcsEvt->m_DeviceID.m_s16DeviceMain,pAcsEvt->m_DeviceID.m_s16DeviceSub),
			pAcsEvt->m_DeviceID.m_s8MachineID,
			pAcsEvt->m_DeviceID.m_s8ModuleID,
			pAcsEvt->m_DeviceID.m_s16ChannelID,
			GetString_IOType(pIOData->m_u16IoType) );
		/*strcat ( TmpStr, TmpS );
		{
			CmdParamData_AnalogTrunk_t cmdAnalogTrunk;
			void*p =(void*)&cmdAnalogTrunk; ;
			XMS_ctsSetParam(g_acsHandle,&pAcsEvt->m_DeviceID,ANALOGTRUNK_PARAM_UNBINDVOC,sizeof(CmdParamData_AnalogTrunk_t),p);
			////
		}*/
		strcat(TmpStr,TmpS);
		break;
	case XMS_EVT_LINKDEVICE:
		{
			Acs_LinkDev_Data * pData = (Acs_LinkDev_Data *)FetchEventData(pAcsEvt);
			sprintf ( TmpS, " (%s,%s,MachineID:%d,ModID:%d,Ch:%d)->(%s,%s,MachineID:%d,ModID:%d,Ch:%d)", 
				GetString_DeviceMain(pData->m_SrcDevice.m_s16DeviceMain),
				GetString_DeviceSub(pData->m_SrcDevice.m_s16DeviceMain,pData->m_SrcDevice.m_s16DeviceSub),
				pData->m_SrcDevice.m_s8MachineID,
				pData->m_SrcDevice.m_s8ModuleID,
				pData->m_SrcDevice.m_s16ChannelID,
				GetString_DeviceMain(pData->m_DestDevice.m_s16DeviceMain),
				GetString_DeviceSub(pData->m_DestDevice.m_s16DeviceMain,pData->m_DestDevice.m_s16DeviceSub),
				pData->m_DestDevice.m_s8MachineID,
				pData->m_DestDevice.m_s8ModuleID,
				pData->m_DestDevice.m_s16ChannelID);
			strcat ( TmpStr, TmpS );
		}
		break;
	case XMS_EVT_CLEARCALL:
		{
			pCallControl = (Acs_CallControl_Data*)FetchEventData(pAcsEvt);

			sprintf ( TmpS, " (%s,%s,MachineID:%2d,ModuleID:%3d,Ch:%d, State: %d, ErrCode: %d)", 
				GetString_DeviceMain(pAcsEvt->m_DeviceID.m_s16DeviceMain),
				GetString_DeviceSub(pAcsEvt->m_DeviceID.m_s16DeviceMain,pAcsEvt->m_DeviceID.m_s16DeviceSub),
				pAcsEvt->m_DeviceID.m_s8MachineID,
				pAcsEvt->m_DeviceID.m_s8ModuleID,
				pAcsEvt->m_DeviceID.m_s16ChannelID,
				pCallControl->m_s32AcsEvtState,
				pCallControl->m_s32AcsEvtErrCode );
		strcat ( TmpStr, TmpS );
		}
		break;
	case XMS_EVT_OPEN_STREAM:
		break;

	case XMS_EVT_OPEN_STREAM_EXT:
		sprintf ( TmpS, " (IP: %s, Port: %d, User: %s, Pwd: %s)", 
			pEvt->m_ServerID.m_s8ServerIp,
			pEvt->m_ServerID.m_u32ServerPort,
			pEvt->m_ServerID.m_s8UserName,
			pEvt->m_ServerID.m_s8UserPwd);
		strcat ( TmpStr, TmpS );
		break;
	case XMS_EVT_QUERY_DEVICE:
		pAcsDevList = (Acs_Dev_List_Head_t *)FetchEventData(pAcsEvt);
		sprintf ( TmpS, " (%s,%2d,%3d), PacktSize: %d", 
			GetString_DeviceMain(pAcsDevList->m_s32DeviceMain),
			pAcsDevList->m_s32ModuleID,
			pAcsDevList->m_s32DeviceNum,
			pAcsEvt->m_s32EvtSize );
		strcat ( TmpStr, TmpS );
		break;

	case XMS_EVT_QUERY_ONE_DSP_START:
	case XMS_EVT_QUERY_ONE_DSP_END:
		sprintf ( TmpS, " (%d)", pAcsEvt->m_DeviceID.m_s8ModuleID );
		strcat ( TmpStr, TmpS );
		break;

	case XMS_EVT_OPEN_DEVICE:
		{
			pGeneralData = (Acs_GeneralProc_Data*)FetchEventData(pAcsEvt);
			int isize = sizeof(Acs_GeneralProc_Evt);
			 isize = sizeof(Acs_GeneralProc_Data);
			
			sprintf ( TmpS, "(%s) CallID(%d,%d)",  GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				pAcsEvt->m_DeviceID.m_CallID.m_s32FlowType, pAcsEvt->m_DeviceID.m_CallID.m_s32FlowChannel );
			strcat ( TmpStr, TmpS );
		}
		break;

	case XMS_EVT_DEVICESTATE:
		pGeneralData = (Acs_GeneralProc_Data *)FetchEventData(pAcsEvt);

		if ( pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_VOICE )
		{
			sprintf ( TmpS, "(%s) S=0x%X(%s)", GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				pGeneralData->m_s32DeviceState, GetString_VocDeviceState(pAcsEvt->m_DeviceID.m_s8ModuleID, pAcsEvt->m_DeviceID.m_s16ChannelID, pGeneralData->m_s32DeviceState) );		
		}
		else if ( XMS_DEVMAIN_FAX == pAcsEvt->m_DeviceID.m_s16DeviceMain )
		{
			sprintf ( TmpS, "(%s) S=0x%X(%s)", GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				pGeneralData->m_s32DeviceState, GetString_FaxState(pGeneralData->m_s32DeviceState) );		
		}
		else if ( XMS_DEVMAIN_INTERFACE_CH == pAcsEvt->m_DeviceID.m_s16DeviceMain )
		{
			sprintf ( TmpS, "(%s) S=0x%X(%s)", GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				pGeneralData->m_s32DeviceState, GetString_DeviceState(pGeneralData->m_s32DeviceState) );
			
			if ( XMS_DEVSUB_E1_DSS1 == pAcsEvt->m_DeviceID.m_s16DeviceSub && DES_DSS1_CALLER_RECV_SETUP_ACK == pGeneralData->m_s32DeviceState )
			{
				DJ_U16 u16ParamType = ISDN_PARAM_APPENDCALLEE;
				DJ_U16 u16ParamSize = 2;

				XMS_ctsSetParam( g_acsHandle, &DevOpened[iOpenedIndex1].DevID, u16ParamType, u16ParamSize, (DJ_Void *)&g_AppendCode[g_u8AppendSendPos]);
				if ( g_u8AppendCodeSize <= g_u8AppendSendPos+1 )
				{
					g_u8AppendSendPos = 0;
				}
				else
				{
					g_u8AppendSendPos++;
				}
			}
		}
		else if ( XMS_DEVMAIN_DIGITAL_PORT == pAcsEvt->m_DeviceID.m_s16DeviceMain )
		{
			sprintf ( TmpS, "(%s) S=0x%X(%s)", GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				pGeneralData->m_s32DeviceState, GetString_DigitalPortDeviceState(pGeneralData->m_s32DeviceState) );	
		}
		else
		{
			sprintf ( TmpS, "(%s) S=0x%X(%s)", GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				pGeneralData->m_s32DeviceState, GetString_DeviceState(pGeneralData->m_s32DeviceState) );								
		}

		strcat ( TmpStr, TmpS );
		break;
	case XMS_EVT_CTBUS_CLK_REF_SRC_STATE:
		{
			ACS_Clock_RefSrc_State_Data* pClockData = (ACS_Clock_RefSrc_State_Data *)FetchEventData(pAcsEvt);

			if ( pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_BOARD )
			{
				sprintf ( TmpS, " (DSP: %d, E1: %d, State: %s)", pClockData->m_u8ModuleID, pClockData->m_u8E1ID, GetString_ClockState( pClockData->m_u8State) );		
			}
			else
			{
				sprintf ( TmpS, "Invalid Device Type: %d", pAcsEvt->m_DeviceID.m_s16DeviceMain ); 
			}
			
			strcat ( TmpStr, TmpS );
		}
		break;
	case XMS_EVT_E1STATE: 
		{
			ACS_Digital_PortState_Data* pData = (ACS_Digital_PortState_Data *)FetchEventData(pAcsEvt);

			sprintf ( TmpS, "(%s) (%s)", GetString_DeviceAll(&pAcsEvt->m_DeviceID),  GetString_E1Info( pData ) );
			strcat ( TmpStr, TmpS );
		}
		break;

	case XMS_EVT_CALLIN:
		{
			pCallControl = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);

			sprintf ( TmpS, "(%s) (%s,%s)", GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				 pCallControl->m_s8CallingNum, pCallControl->m_s8CalledNum); 
			strcat ( TmpStr, TmpS );
		}
		break;

	case XMS_EVT_CALLOUT:
		pCallControl = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);

		sprintf ( TmpS, "(%s) EvtState=%d, ErrCode=%d,ClearCause=%d) calling=%s called=%s", GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
			pCallControl->m_s32AcsEvtState, pCallControl->m_s32AcsEvtErrCode, pCallControl->m_s32CallClearCause,pCallControl->m_s8CallingNum,pCallControl->m_s8CalledNum );  
		strcat ( TmpStr, TmpS );
		break;

	case XMS_EVT_RECVIODATA:
		{
		pIOData = (Acs_IO_Data *)FetchEventData(pAcsEvt);


		//strcat ( TmpStr, TmpS );
		//AddMsg ( MSG_TYPE_EVENT, TmpStr );
		

		pdlg->GetDlgItem ( IDC_EDIT_SENDFAX )->GetWindowText ( SendTiffFileName, ACS_MAX_FILE_NAME_LEN-1 );
		pdlg->GetDlgItem ( IDC_EDIT_RECEIVEFAX )->GetWindowText ( RecvTiffFileName, ACS_MAX_FILE_NAME_LEN-1 );
		//sprintf ( s8LocalID, "DJ:83636988" );

		if( pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_VOIP)
		{
			//Fax Process....begin
			switch (pIOData->m_u16IoType)
			{
				case XMS_IO_TYPE_VOIP_H245UII:
					if (pIOData->m_u16IoDataLen == sizeof(Acs_VoIP_H245UII))
					{
						Acs_VoIP_H245UII *h245Uii = (Acs_VoIP_H245UII *)FetchIOData(pAcsEvt);
						dtmf = h245Uii->m_s8Signal;
					}
					sprintf ( TmpS, "(%s) (%s,%d) [%c]", GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
					GetString_IOType(pIOData->m_u16IoType),  pIOData->m_u16IoDataLen, dtmf ); 
					break;
				case XMS_IO_TYPE_VOIP_SIPINFO:
					if (pIOData->m_u16IoDataLen == sizeof(Acs_VoIP_SIPINFO))
					{
						Acs_VoIP_SIPINFO *sipInfo = (Acs_VoIP_SIPINFO *)FetchIOData(pAcsEvt);
						if (strcmp(sipInfo->m_s8ContentType, "application/dtmf") == 0)
							sscanf(sipInfo->m_s8Body, "dtmf=%c", &dtmf);
					}
					sprintf ( TmpS, "(%s) (%s,%d) [%c]", GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
					GetString_IOType(pIOData->m_u16IoType),  pIOData->m_u16IoDataLen, dtmf ); 
					break;
				case XMS_IO_TYPE_VOIP_RTPDTMF:
					if (pIOData->m_u16IoDataLen == sizeof(Acs_VoIP_RTPDTMF))
					{
						Acs_VoIP_RTPDTMF *rtpDtmf = (Acs_VoIP_RTPDTMF *)FetchIOData(pAcsEvt);
						dtmf = rtpDtmf->m_s8EventChar;
					}
					sprintf ( TmpS, "(%s) (%s,%d) [%c]", GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
					GetString_IOType(pIOData->m_u16IoType),  pIOData->m_u16IoDataLen, dtmf ); 
					break;
				case XMS_IO_TYPE_VOIP_FAXSTART:
					if (pIOData->m_u16IoDataLen == sizeof(DJ_S32))
					{
						DJ_S32 *ret = (DJ_S32 *)FetchIOData(pAcsEvt);
						if (*ret == 0)
						{
							

							pdlg->UpdateData();

							if (g_iSendRecv == 0)//SendFax
							{
								//pdlg->m_lstIP.SetItemText(iDevice, 3, _T("Send Fax"));

								XMS_ctsSendFax(g_acsHandle,
									&DevOpened[iOpenedIndex1].DevID,
									&DevOpened[iOpenedIndex2].DevID,
									//&g_deviceVoIP[iDevice].device,
									(DJ_S8 *)(LPCTSTR)SendTiffFileName, "1234", NULL);

								sprintf ( TmpS, "(%s) (%s,%d) T38START SENDFAX", GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
								GetString_IOType(pIOData->m_u16IoType),  pIOData->m_u16IoDataLen  ); 
							}
							else
							{
								//pdlg->m_lstIP.SetItemText(iDevice, 3, _T("Recv Fax"));
								XMS_ctsReceiveFax(g_acsHandle,
									&DevOpened[iOpenedIndex1].DevID,
									&DevOpened[iOpenedIndex2].DevID,
									//&g_deviceVoIP[iDevice].device,
									(DJ_S8 *)(LPCTSTR)RecvTiffFileName, "1234", NULL);

								sprintf ( TmpS, "(%s) (%s,%d) T38START RECVFAX", GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
								GetString_IOType(pIOData->m_u16IoType),  pIOData->m_u16IoDataLen  ); 
							}
						}
					}
			
					
					break;
				//default:
				//	sprintf ( TmpS, "(%s) (%s,%d) INVALID IOTYPE FOR VOIP", GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				//				GetString_IOType(pIOData->m_u16IoType),  pIOData->m_u16IoDataLen  ); 
				//	break;

				
			}
		//Fax Process....end

		}
		else //NO IP Device
		{
			char *p;
			p = (char *)(pIOData) + sizeof(Acs_IO_Data);
			switch( pIOData->m_u16IoType)
			{
			case XMS_IO_TYPE_DTMF:
				sprintf ( TmpS, "(%s) (%s,%d) [%c]", 
				GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				GetString_IOType(pIOData->m_u16IoType),  
				pIOData->m_u16IoDataLen, 
				p[0] ); 
				break;
			case XMS_IO_TYPE_GTD:
				sprintf ( TmpS, "(%s) (%s,%d) [%c]", 
				GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				GetString_IOType(pIOData->m_u16IoType),  
				pIOData->m_u16IoDataLen, 
				*p ); 
				break;
			case XMS_IO_TYPE_FSK:
				sprintf ( TmpS, "(%s) (%s,Len:%d) %c%c%c%....%c", 
				GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				GetString_IOType(pIOData->m_u16IoType),  
				pIOData->m_u16IoDataLen, 
				p[0],p[1],p[2],p[pIOData->m_u16IoDataLen-1] ); 
				break;
			
			case XMS_IO_TYPE_PVD:
				sprintf ( TmpS, "(%s) (%s,%d) [%c]->[%c]", 
				GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				GetString_IOType(pIOData->m_u16IoType),  
				pIOData->m_u16IoDataLen, 
				p[0], p[pIOData->m_u16IoDataLen-1] ); 

			case XMS_IO_TYPE_MSK:
				sprintf ( TmpS, "(%s) (%s,%d) [%02x]->[%02x]", 
				GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				GetString_IOType(pIOData->m_u16IoType),  
				pIOData->m_u16IoDataLen, 
				p[0], p[pIOData->m_u16IoDataLen-1] ); 
				break;
			case XMS_IO_TYPE_VSD:
				sprintf ( TmpS, "(%s) (%s,%d) [%c]->[%C]", 
				GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				GetString_IOType(pIOData->m_u16IoType),  
				pIOData->m_u16IoDataLen, 
				p[0], p[pIOData->m_u16IoDataLen-1] ); 
				break;
			case XMS_IO_TYPE_MSKREND:
				sprintf ( TmpS, "(%s) (%s,%d) Recv MSK Data OK", 
				GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				GetString_IOType(pIOData->m_u16IoType),  
				pIOData->m_u16IoDataLen); 
				break;
			case XMS_IO_TYPE_DPD:
				sprintf ( TmpS, "(%s) (%s,%d) [%c]->[%c]", 
				GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
				GetString_IOType(pIOData->m_u16IoType),  
				pIOData->m_u16IoDataLen, 
				p[0], p[pIOData->m_u16IoDataLen-1] ); 
				break;

			default:
				break;
			}
			
		}

		}
		strcat ( TmpStr, TmpS );
		//AddMsg ( MSG_TYPE_EVENT, TmpStr );
		break;

	case XMS_EVT_CAS_MFC_START:
	case XMS_EVT_CAS_MFC_END:
		pCAS_ExtraInfo = (Acs_CAS_ExtraInfo_t *)FetchEventData(pAcsEvt);

		sprintf ( TmpS, "(%s) KA=%d, KD=%d)", GetString_DeviceAll(&pAcsEvt->m_DeviceID), 
			pCAS_ExtraInfo->m_u8KA, pCAS_ExtraInfo->m_u8KD );
		strcat ( TmpStr, TmpS );
		break;


	case XMS_EVT_UNIFAILURE:
		pAcsUniFailure = (Acs_UniFailure_Data *)FetchEventData(pAcsEvt);

		sprintf ( TmpS, ": %s(0x%X)", GetString_ErrorCode(pAcsUniFailure->m_s32AcsEvtErrCode), pAcsUniFailure->m_s32AcsEvtErrCode );
		strcat ( TmpStr, TmpS );

		if ( pAcsEvt->m_DeviceID.m_s16DeviceMain != 0 )
		{
			//Unifailure event that some device link each other
			sprintf ( TmpS, " (%s)", GetString_DeviceAll(&pAcsEvt->m_DeviceID) );
			strcat ( TmpStr, TmpS );
		}
		break;
/////////////////////////////////////////////////////////////////////////////////
	case XMS_EVT_3GPP_PLAY:
		{
			Acs_Media3GPPProc_Data * pEvt = (Acs_Media3GPPProc_Data *)FetchEventData(pAcsEvt);

			sprintf ( TmpS, " ST:%d err: %s MT:%d a_t:%d a_i:%d a_p:%d v_t:%d v_i:%d v_p:%d",
				pEvt->m_s32AcsEvtState,
				GetStringMediaErrCode(pEvt->m_s32AcsEvtState,pEvt->m_s32AcsEvtErrCode),
				pEvt->m_u8MediaType,
				pEvt->m_u8AudioTaskID,
				pEvt->m_u32AudioCurFileIndex,
				pEvt->m_u32AudioCurFilePos,
				pEvt->m_u8VideoTaskID,
				pEvt->m_u32VideoCurFileIndex,
				pEvt->m_u32VideoCurFilePos);
			strcat ( TmpStr, TmpS );	
		}
		break;
	case XMS_EVT_3GPP_BUILD_INDEX:
		pMedia=(Acs_MediaProc_Data*)FetchEventData(pAcsEvt);
		sprintf(TmpS," EvtState=%d taskID=%d fileIndex=%u,%x",pMedia->m_s32AcsEvtState,pMedia->m_u8TaskID,pMedia->m_u32CurFileIndex,pMedia->m_u32CurFileIndex);
		strcat(TmpStr,TmpS);
		break;
	case XMS_EVT_3GPP_INIT_INDEX:
	//	pMedia=(Acs_MediaProc_Data*)FetchEventData(pAcsEvt);
		sprintf(TmpS," Init3GPPIndex OK");
		strcat(TmpStr,TmpS);
		break;
	case XMS_EVT_GETPARAM:
	{
		if ( XMS_DEVMAIN_VOIP == pAcsEvt->m_DeviceID.m_s16DeviceMain )
		{
			Acs_ParamProc_Data *pParam = (Acs_ParamProc_Data*)(FetchEventData(pAcsEvt));
			if(pParam->m_u16ParamCmdType == VOIP_PARAM_RTPCODEC)
			{
				Acs_VoIP_RTPCODEC *pCodec = (Acs_VoIP_RTPCODEC*)(FetchParamData(pAcsEvt));
				if(pCodec->audio.m_u8Enable)
				{
					g_stCodec.audio.RxCodec = pCodec->audio.m_u8RxCodec;
					g_stCodec.audio.RxPayloadType = pCodec->audio.m_u8RxPayloadType;
					g_stCodec.audio.TxCodec= pCodec->audio.m_u8TxCodec;
					g_stCodec.audio.TxPayloadType = pCodec->audio.m_u8TxPayloadType;
				}
				if(pCodec->video.m_u8Enable)
				{
					g_stCodec.video.RxCodec = pCodec->video.m_u8RxCodec;
					g_stCodec.video.RxPayloadType = pCodec->video.m_u8RxPayloadType;
					g_stCodec.video.TxCodec= pCodec->video.m_u8TxCodec;
					g_stCodec.video.TxPayloadType = pCodec->video.m_u8TxPayloadType;
				}
				
				if(pCodec->video.m_u8TxCodec == VOIP_MEDIA_VIDEO_H263)
				{
					sprintf(TmpS," Video Codec=[%s]","h263");
					strcat(TmpStr,TmpS);
				}
				else if(pCodec->video.m_u8TxCodec == VOIP_MEDIA_VIDEO_MPEG4)
				{
					sprintf(TmpS," Video Codec=[%s]","mp4v");
					strcat(TmpStr,TmpS);
				}
				else if(pCodec->video.m_u8TxCodec == VOIP_MEDIA_VIDEO_H264)
				{
					sprintf(TmpS," Video Codec=[%s]","h264");
					strcat(TmpStr,TmpS);
				}
				else 
				{
					sprintf(TmpS,"Video Codec=[%s]","Invalid");
					strcat(TmpStr,TmpS);
				}
			}
		}
		else if ( XMS_DEVMAIN_VOICE == pAcsEvt->m_DeviceID.m_s16DeviceMain )
		{
			CmdParamData_3GPP_t * pData = NULL;
			Acs_ParamProc_Data * pEvt = (Acs_ParamProc_Data *)FetchEventData(pAcsEvt);
			if ( H324_PARAM_MEDIA == pEvt->m_u16ParamCmdType )
			{
				pData =  (CmdParamData_3GPP_t *)FetchParamData(pAcsEvt);
            
				/////////////////////////////////////////////////////////////////////////////////
				//begin of init the struct
				g_Record3gppProperty.m_s8AudioIsMixEnable = TRUE;
				g_Record3gppProperty.m_AudioMixerControl.m_u16SRC_ChID1 = DevOpened[iOpenedIndex1].DevID.m_s16ChannelID;
				g_Record3gppProperty.m_AudioMixerControl.m_u8SRC1_Ctrl  = XMS_MIXER_FROM_PLAY;

				g_Record3gppProperty.m_s8VideoIsMixEnable = TRUE;
				g_Record3gppProperty.m_VideoMixerControl.m_u16SRC_ChID1 = DevOpened[iOpenedIndex1].DevID.m_s16ChannelID;
				g_Record3gppProperty.m_VideoMixerControl.m_u8SRC1_Ctrl  = XMS_MIXER_FROM_PLAY;

				//init the record property on 070723 by fuyunshi
				g_Record3gppProperty.m_u32MaxTime = 0;          /*record max time, 0: no limit record time; >0: record max time*/	
				g_Record3gppProperty.m_u8StopMode = 0;          /*stop record mode,referecne XMS_PLAYREC_STOP_MODE*/	
				g_Record3gppProperty.m_u8StopCode = 0;	      /*stop record when receive this dtmf code*/
				g_Record3gppProperty.m_s8IsAppend = 0;          /*0: trunc record file; 1: append record file,reference XMS_REC_OPENFILE_TYPE*/	

				g_Record3gppProperty.m_u8AudioSRCMode    = XMS_SRC_3GVIDEO;  /*file src mode, reference XMS_VOC_SRC_MODE*/
				g_Record3gppProperty.m_u8AudioTracks     = XMS_AUDIO_TRACKS_STEREO;      /*audio channel,reference XMS_AUDIO_TRACKS*/
				g_Record3gppProperty.m_u16AudioMaxBitRate = 0;      /*audio max bitrate,0~65535*/
				g_Record3gppProperty.m_u16AudioAverageBitRate = 0;  /*audio average bitrate,0~65535*/
//				g_Record3gppProperty.m_Rfu1[0] = 0;
//				g_Record3gppProperty.m_Rfu1[1] = 0;

				g_Record3gppProperty.m_u8VideoEncodeType = XMS_VIDEO_CODE_TYPE_H263;
				g_Record3gppProperty.m_u8VideoFrameRate  = 15;
				g_Record3gppProperty.m_u16VideoHeight    = 144;
				g_Record3gppProperty.m_u16VideoWidth     = 176;
				g_Record3gppProperty.m_u8VideoProfiles   = 0;
				g_Record3gppProperty.m_u8VideoLevel      = 10;
				//end of init the struct
				/////////////////////////////////////////////////////////////////////////////////

				g_Record3gppProperty.m_u8AudioEncodeType = pData->m_u8AudioDecodeType;  /*encode type, reference XMS_VOC_CODE_TYPE*/	
				g_Record3gppProperty.m_u8AudioTracks = 2;      /*audio channel,reference XMS_AUDIO_TRACKS*/
				g_Record3gppProperty.m_u16AudioMaxBitRate = 0; /*audio max bitrate,0~65535*/
				g_Record3gppProperty.m_u16AudioAverageBitRate = 0;/*audio average bitrate,0~65535*/

				g_Record3gppProperty.m_u8VideoEncodeType = pData->m_u8VideoDecodeType;  /*encode type, reference XMS_VIDEO_CODE_TYPE*/	
				g_Record3gppProperty.m_u8VideoFrameRate = pData->m_u8VideoFrameRate;   /*video frame rate,10~30*/
				g_Record3gppProperty.m_u16VideoWidth = 0;      /*video width,176*/
				g_Record3gppProperty.m_u16VideoHeight= 0;     /*video heigth,144*/
				g_Record3gppProperty.m_u16VideoMaxBitRate = 0; /*video max bit rate,0~65535*/
				g_Record3gppProperty.m_u16VideoAverageBitRate = 0;/*video average bit rate,0~65535*/

				g_Record3gppProperty.m_u8AudioProfiles = pData->m_u8AudioProfiles;    /*audio profiles?*/
				g_Record3gppProperty.m_u8AudioLevel = pData->m_u8AudioLevel;       /*audio level ?*/
				g_Record3gppProperty.m_u16AudioDecoderCfgLen = 0;/*audio decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
				//g_Record3gppProperty.m_u8AudioDecoderCfg[ACS_MAX_DECODER_CFG_LEN];/*audio decoder cfg*/

				g_Record3gppProperty.m_u8VideoProfiles = pData->m_u8VideoProfiles;    /*video profiles?*/
				g_Record3gppProperty.m_u8VideoLevel = pData->m_u8VideoLevel;       /*video level?*/	
				g_Record3gppProperty.m_u16VideoDecoderCfgLen = pData->m_u16VideoDecoderCfgLen;  /*video decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
				
				memcpy(g_Record3gppProperty.m_u8VideoDecoderCfg, pData->m_u8VideoDecoderCfg, ACS_MAX_DECODER_CFG_LEN);

				TRACE("Recv Get Param Evt\n");
				TRACE("Audio: DT: %d, Profiles: %d, Level: %d\n", pData->m_u8AudioDecodeType, pData->m_u8AudioProfiles, pData->m_u8AudioLevel);
				TRACE("Video: DT: %d, Profiles: %d, Level: %d, CfgLen: %d\n", pData->m_u8VideoDecodeType, pData->m_u8VideoProfiles, pData->m_u8VideoLevel, pData->m_u16VideoDecoderCfgLen);
				if ( 0 != pData->m_u16VideoDecoderCfgLen)
				{
					TRACE("Config begin: \n<<");
					for (int i = 0; i < pData->m_u16VideoDecoderCfgLen; i ++)
						TRACE("%x ", pData->m_u8VideoDecoderCfg[i]);

					TRACE(">>\nConfig end: \n");

				}
			}
		}
		else if ( XMS_DEVMAIN_BOARD == pAcsEvt->m_DeviceID.m_s16DeviceMain )
		{
			pBoardInfor =  (Acs_ParamData_UserReadXmsBoardInfo *)FetchParamData(pAcsEvt);
			sprintf ( TmpS, ": (SysID: %d, BoardType: %d, Mac: %02x-%02x-%02x-%02x-%02x-%02x )", 
				pBoardInfor->m_s32SysId,
				/*pBoardInfor->m_s8FirmwareName,
				pBoardInfor->m_s8FirmwareVersion,
				pBoardInfor->m_s8PlatformType,
				pBoardInfor->m_s8RevisionDate,
				pBoardInfor->m_s8SystemName,
				pBoardInfor->m_s8UserCode,*/
				pBoardInfor->m_u8BoardType,
				//pBoardInfor->m_u8ChassisIndex,
				//pBoardInfor->m_u8ChassisSlot,
				//pBoardInfor->m_u8ChassisType,
				pBoardInfor->m_u8MacAddr[0],
				pBoardInfor->m_u8MacAddr[1],
				pBoardInfor->m_u8MacAddr[2],
				pBoardInfor->m_u8MacAddr[3],
				pBoardInfor->m_u8MacAddr[4],
				pBoardInfor->m_u8MacAddr[5]);
				//pBoardInfor->m_u8SubBoardIndex );
			strcat ( TmpStr, TmpS );
			
		}
		else if ( XMS_DEVMAIN_CONFERENCE == pAcsEvt->m_DeviceID.m_s16DeviceMain )
		{
			CmdParamConf_MemberState_t *pConfInfor =  (CmdParamConf_MemberState_t *)FetchParamData(pAcsEvt);
            
			sprintf ( TmpS, ":(TotalOfConfMem: %d, NormalState: %s", pConfInfor->m_u8TotalOfConfMem,
				 GetConfActiveMember( pConfInfor->m_s8NormalVad, NULL));
			strcat ( TmpStr, TmpS );
			sprintf ( TmpS, ", IPState: %s)", 
				 GetConfActiveMember( pConfInfor->m_s8IPVad, NULL));
			strcat ( TmpStr, TmpS );
		}
		else if ( XMS_DEVMAIN_INTERFACE_CH == pAcsEvt->m_DeviceID.m_s16DeviceMain )
		{
			Acs_ParamProc_Data *pParam = (Acs_ParamProc_Data*)(FetchEventData(pAcsEvt));

			///the same value for all analog module
			if ( ANALOGVOC2_PARAM_READSN == pParam->m_u16ParamCmdType )
			{
				if ( pAcsEvt->m_DeviceID.m_s16DeviceSub == XMS_DEVSUB_ANALOG_USER )
				{
					CmdParamData_ReadSn_t *pReadSN =  (CmdParamData_ReadSn_t *)FetchParamData(pAcsEvt);
            
					sprintf ( TmpS, ":(VersionNO: %s", pReadSN->m_u8ReadSn);
					strcat ( TmpStr, TmpS );
				}
				else if ( pAcsEvt->m_DeviceID.m_s16DeviceSub == XMS_DEVSUB_ANALOG_VOC2W )
				{
					CmdParamData_ReadSn_t *pReadSN =  (CmdParamData_ReadSn_t *)FetchParamData(pAcsEvt);
            
					sprintf ( TmpS, ":(VOC2W VersionNO: %s", pReadSN->m_u8ReadSn);
					strcat ( TmpStr, TmpS );
				}
				else if ( pAcsEvt->m_DeviceID.m_s16DeviceSub == XMS_DEVSUB_ANALOG_VOC4W )
				{
					CmdParamData_ReadSn_t *pReadSN =  (CmdParamData_ReadSn_t *)FetchParamData(pAcsEvt);
            
					sprintf ( TmpS, ":(VOC4W VersionNO: %s", pReadSN->m_u8ReadSn);
					strcat ( TmpStr, TmpS );
				}
				else 
				{
					CmdParamData_ReadSn_t *pReadSN =  (CmdParamData_ReadSn_t *)FetchParamData(pAcsEvt);
            
					sprintf ( TmpS, ":(Dev(0x%x,0x%x) VersionNO: %s", pAcsEvt->m_DeviceID.m_s16DeviceMain,pAcsEvt->m_DeviceID.m_s16DeviceSub, pReadSN->m_u8ReadSn);
					strcat ( TmpStr, TmpS );
				}
			}
			else if ( ISDN_PARAM_ORINUMBER == pParam->m_u16ParamCmdType )
			{
				
            	DJ_S8 *pData =  (DJ_S8 *)FetchParamData(pAcsEvt);
				
				if ( pParam->m_u16ParamDataSize > 0 )
				{
					sprintf ( TmpS, ":(OriNumber: %s", pData);
					strcat ( TmpStr, TmpS );
				}
			}
			///the same value for all analog module
			else if ( ANALOGHIZ_PARAM_GET_VOLTAGE == pParam->m_u16ParamCmdType )
			{
				CmdParamData_ReadVoltage_t *pData =  (CmdParamData_ReadVoltage_t *)FetchParamData(pAcsEvt);
				
				sprintf ( TmpS, ":(Voltage: %d)", pData->m_s8Voltage);
				strcat ( TmpStr, TmpS );
				
          //		sprintf ( TmpS, ":(Dev(0x%x,0x%x) Voltage: %d", pAcsEvt->m_DeviceID.m_s16DeviceMain, pAcsEvt->m_DeviceID.m_s16DeviceSub, pData->m_s8Voltage);
          // 		strcat ( TmpStr, TmpS );
			}
		}
	}
		break;
	case XMS_EVT_CTX_REG:
		{
			Acs_CtxReg_Data  * pCtxReg = (Acs_CtxReg_Data *)FetchEventData(pAcsEvt);
	

			//sprintf ( TmpS, "(%s) %s(0x%X)", GetString_DeviceAll(&pAcsEvt->m_DeviceID), GetString_ErrorCode(pCtxReg->m_s32AcsEvtErrCode), pCtxReg->m_s32AcsEvtErrCode );
			sprintf ( TmpS, ": %s (ErrCode: 0x%X)", GetString_ErrorCode(pCtxReg->m_s32AcsEvtErrCode), pCtxReg->m_s32AcsEvtErrCode );
			strcat ( TmpStr, TmpS );
		}
		break;
	case XMS_EVT_CTX_LINK:
		{
			Acs_CtxLink_Data * pCtxLink = (Acs_CtxLink_Data *)FetchEventData(pAcsEvt);
			sprintf ( TmpS, "(%s) %s(0x%X)", GetString_DeviceAll(&pAcsEvt->m_DeviceID), GetString_ErrorCode(pCtxLink->m_s32AcsEvtErrCode), pCtxLink->m_s32AcsEvtErrCode );
			//sprintf ( TmpS, ": %s (ErrCode: 0x%X)", GetString_ErrorCode(pCtxLink->m_s32AcsEvtErrCode), pCtxLink->m_s32AcsEvtErrCode );
			strcat ( TmpStr, TmpS );
		}
		break;
	case XMS_EVT_CTX_APPDATA:
		{
			Acs_CtxAppData_Info * pCtxAppData = (Acs_CtxAppData_Info *)FetchEventData(pAcsEvt);
			UserData4CTX        * pUserData   = (UserData4CTX*)(pCtxAppData+1);

			sprintf ( TmpS, ": %s %s(0x%X) AppDataSize:%d,AppReqType:%d,SrcRegName:%s,DestRegName:%s, TNums1: %d, TNums2: %d, TStr: %s",
				GetString_DeviceAll(&pAcsEvt->m_DeviceID), GetString_ErrorCode(pCtxAppData->m_s32AcsEvtErrCode), pCtxAppData->m_s32AcsEvtErrCode,
				pCtxAppData->m_AppDataInfo.m_u32AppDataSize,pCtxAppData->m_AppDataInfo.m_u8AppReqType,
				pCtxAppData->m_AppDataInfo.m_s8SrcRegName,pCtxAppData->m_AppDataInfo.m_s8DestRegName,
				pUserData->s32TestNum1,
				pUserData->s32TestNum2,
				pUserData->s8TestString);
			strcat ( TmpStr, TmpS );

			//Can't excute the ctx link to ctx using by API_TEST.exe that has excute the XMS_ctxSendAppData API.			
			if ( !g_u8IsSendAppDataFlag )
			{
				TRACE("****(%s)Get the App Data\n", GetString_DeviceAll(&pAcsEvt->m_DeviceID));
				g_stAppData.OthersCTXDevID = pCtxAppData->m_AppDataInfo.m_srcDevice;
				strcpy( g_s8OthersAppName, pCtxAppData->m_AppDataInfo.m_s8SrcRegName );								
			}

			g_u8IsSendAppDataFlag = 0;
		}
		break;
	case XMS_EVT_SENDFAX:
		{
			Acs_FaxProc_Data *pEvt = (Acs_FaxProc_Data*)FetchEventData(pAcsEvt);
			sprintf ( TmpS, " <FAX(DSP: %d, CH: %d), State: 0x%x, ErrCode: 0x%x>",  pAcsEvt->m_DeviceID.m_s8ModuleID, pAcsEvt->m_DeviceID.m_s16ChannelID, pEvt->m_s32AcsEvtState, pEvt->m_s32AcsEvtErrCode );
			strcat ( TmpStr, TmpS);
		}
		break;

	case XMS_EVT_RECVFAX:
		{
			Acs_FaxProc_Data *pEvt = (Acs_FaxProc_Data*)FetchEventData(pAcsEvt);
			sprintf ( TmpS, " <FAX(DSP: %d, CH: %d), State: 0x%x, ErrCode: 0x%x>",  pAcsEvt->m_DeviceID.m_s8ModuleID, pAcsEvt->m_DeviceID.m_s16ChannelID, pEvt->m_s32AcsEvtState, pEvt->m_s32AcsEvtErrCode  );
			strcat ( TmpStr, TmpS);
		}
		break;

	case XMS_EVT_MODMONITOR:
		{
			Acs_SysMon_Data *pEvt = (Acs_SysMon_Data*)FetchEventData(pAcsEvt);
			sprintf ( TmpS, " <MT: %d, IP: %s, Port: %d, UnitID: %d, State: %d>",  
				pEvt->m_u8ModuleType, pEvt->m_s8IPAddress, pEvt->m_u32Port, pEvt->m_u8UnitID, pEvt->m_u16ModuleState );
			strcat ( TmpStr, TmpS);
		}
		break;
	case XMS_EVT_MASTER_STATE:
 		{
 			Acs_MasterState_Data *pEvt = (Acs_MasterState_Data*)FetchEventData(pAcsEvt);
 			sprintf ( TmpS, " <IP: %s, Port: %d, WorkState: %d>", pEvt->m_s8ServerIp, pEvt->m_u32ServerPort,pEvt->m_u8MasterState );
 			strcat ( TmpStr, TmpS);
 		}
 		break; 

	case XMS_EVT_SLAVE_WORK_STATE:
		{
			Acs_SlaveWorkState_Data *pEvt = (Acs_SlaveWorkState_Data*)FetchEventData(pAcsEvt);
			sprintf ( TmpS, " <WorkState: %d>", pEvt->m_s8WorkState );
			strcat ( TmpStr, TmpS);
		}
		break;
	case XMS_EVT_SET_MEDIAINFO:
		{
			Acs_VoIP_MediaInfo *pMediaInfo = (Acs_VoIP_MediaInfo *)FetchEventData(pAcsEvt);
			sprintf(TmpS, _T("[%s] set media info"), GetString_DeviceAll(&pAcsEvt->m_DeviceID));
			strcat ( TmpStr, TmpS);
			sprintf(TmpS, _T(" dtmf:%d, tone:%d, addr:%s:%d, caps:"), pMediaInfo->payload_dtmf, pMediaInfo->payload_tone, pMediaInfo->s8AudioAddress, pMediaInfo->u16AudioPort);
			strcat ( TmpStr, TmpS);
			for( int i= 0;i< pMediaInfo->u8MediaCapNum;i++ )
			{
				if(i!=0)
					strcat ( TmpStr, ",");
				sprintf(TmpS, _T("%d"), pMediaInfo->u8MediaCapList[i]);
				strcat ( TmpStr, TmpS);
			}
		}
		break;
////////////////////////////////////////////////////////////////////////////////////////////////////
	default:
		break;

	}

	AddMsg ( MSG_TYPE_EVENT, TmpStr );
}

void	InitDeviceRes (void)
{
	TotalDevRes = 0;

	TotalDevOpened = 0;
}

void	FreeDeviceRes (void)
{
	if ( pDevRes != NULL )
	{
		free ( pDevRes );
		pDevRes = NULL;
	}

	TotalDevRes = 0;
	TotalDevOpened = 0;
}

void	AddDeviceRes ( Acs_Dev_List_Head_t *pAcsDevList )
{
	char	TmpStr[256];
	void	*p;
	int		i;
	DeviceID_t	*pDev;


	if ( pDevRes == NULL )
	{
		pDevRes = (TYPE_MY_DEVICE_STRUCT *) malloc ( pAcsDevList->m_s32DeviceNum * sizeof(TYPE_MY_DEVICE_STRUCT) );
		if ( pDevRes == NULL )
		{
			AddMsg ( MSG_TYPE_OTHER, "malloc() Fail in My Function AddDeviceRes()!" );
			return;
		}
	}
	else
	{
		p = realloc ( pDevRes, (TotalDevRes + pAcsDevList->m_s32DeviceNum) * sizeof(TYPE_MY_DEVICE_STRUCT) );
		if ( p == NULL )
		{
			sprintf ( TmpStr, "realloc() from %d to %d Fail in My Function AddDeviceRes()!", 
				TotalDevRes,  TotalDevRes + pAcsDevList->m_s32DeviceNum );
			AddMsg ( MSG_TYPE_OTHER, TmpStr );
			return;
		}

		pDevRes = (TYPE_MY_DEVICE_STRUCT *)p;
	}
	
	pDev = (DeviceID_t *) ((DJ_S8 *)pAcsDevList + sizeof(Acs_Dev_List_Head_t));
	for ( i = 0; i < pAcsDevList->m_s32DeviceNum; i ++ )
	{
		pDevRes[TotalDevRes + i].DevID = pDev[i];
		pDevRes[TotalDevRes + i].pDevData = NULL;
	}

	TotalDevRes += pAcsDevList->m_s32DeviceNum;

}

void	OpenDeviceOK ( DeviceID_t	*pDev )
{
	char		TmpStr[256];

	if ( TotalDevOpened >= MAX_DEVICE_ALLOW_OPEN )
	{
		AddMsg ( MSG_TYPE_OTHER, "Add OpenDevice Fail. overflow." );
	}
	else
	{
		DevOpened[TotalDevOpened].DevID = *pDev;
		DevOpened[TotalDevOpened].bOpenFlag = true;
		DevOpened[TotalDevOpened].pDevData = NULL;

		sprintf ( TmpStr, "%d-(%s) (%d,%d)", TotalDevOpened, GetString_DeviceAll(pDev),
			pDev->m_CallID.m_s32FlowType, pDev->m_CallID.m_s32FlowChannel );
		pdlg->m_ListDevOpened.AddString ( TmpStr );

		if ( TotalDevOpened == 0 )
		{
			//it is fill into IDC_EDIT_DEVICE1 block automatic if opened the first deviceID
			//if ( pDev->m_s16DeviceMain != XMS_DEVMAIN_VOIP)
				 iOpenedIndex1 = 0;
			//else
			//	 iOpenedIndex3 = 0;

			//pdlg->GetDlgItem ( IDC_EDIT_DEVICE1 )->SetWindowText ( GetString_DeviceAll(&DevOpened[iOpenedIndex1].DevID) );
		}
/*		if ( iOpenedIndex1 == -1)
		{
			pdlg->m_ListDevOpened.SetCurSel (TotalDevOpened);
		}
*/
		TotalDevOpened ++;
	}
}

int FindOpenDevice(DeviceID_t	*pDev)
{
	for (int i = 0; i < TotalDevOpened; i ++ )
	{
		if ( ( DevOpened[i].DevID.m_s16DeviceMain == pDev->m_s16DeviceMain )
			&& ( DevOpened[i].DevID.m_s16DeviceSub == pDev->m_s16DeviceSub )
			&& ( DevOpened[i].DevID.m_s8ModuleID == pDev->m_s8ModuleID )
			&& ( DevOpened[i].DevID.m_s16ChannelID == pDev->m_s16ChannelID ) )
		{
			return i;
		}
	}
	return -1;
}

void	CloseDeviceOK ( DeviceID_t	*pDev )
{
	char		TmpStr[256];
	int			i, j, iRemoveIndex;
	bool		bFindFlag = false;

	for ( i = 0; i < TotalDevOpened; i ++ )
	{
		if ( ( DevOpened[i].DevID.m_s16DeviceMain == pDev->m_s16DeviceMain )
			&& ( DevOpened[i].DevID.m_s16DeviceSub == pDev->m_s16DeviceSub )
			&& ( DevOpened[i].DevID.m_s8ModuleID == pDev->m_s8ModuleID )
			&& ( DevOpened[i].DevID.m_s16ChannelID == pDev->m_s16ChannelID ) )
		{
			bFindFlag = true;
			iRemoveIndex = i;
			if(DevOpened[i].pDevData!=NULL)
			{
				free(DevOpened[i].pDevData);
				DevOpened[i].pDevData = NULL;
			}

			if ( i < TotalDevOpened -1 )
			{
				for ( j = i; j < TotalDevOpened-1 ; j ++ )
				{
					DevOpened[j] = DevOpened[j+1];
				}
				DevOpened[TotalDevOpened-1].pDevData = NULL;
			}
			break;
		}
	}

	if ( !bFindFlag )
	{
		sprintf ( TmpStr, "Fail to Remove from list in CloseDevice()! (%s)", GetString_DeviceAll(pDev) );
		AddMsg ( MSG_TYPE_OTHER, TmpStr );
	}
	else
	{
		TotalDevOpened --;

		if ( iOpenedIndex1 == iRemoveIndex)
		{
			iOpenedIndex1 = -1;
			pdlg->GetDlgItem ( IDC_EDIT_DEVICE1 )->SetWindowText ( "" );
		}
		
		/*if ( iOpenedIndex3 == iRemoveIndex)
		{
			iOpenedIndex3 = -1;
			pdlg->GetDlgItem ( IDC_EDIT_DEVICE3 )->SetWindowText ( "" );
		}*/
	}

	// redraw list
	pdlg->m_ListDevOpened.ResetContent ();
	for ( i = 0; i < TotalDevOpened; i ++ )
	{
		sprintf ( TmpStr, "%d-(%s) (%d,%d)", i, GetString_DeviceAll(&DevOpened[i].DevID),
			DevOpened[i].DevID.m_CallID.m_s32FlowType, DevOpened[i].DevID.m_CallID.m_s32FlowChannel );
		pdlg->m_ListDevOpened.AddString ( TmpStr );
	}

}

// -------------------------------------------------------
DJ_Void EvtHandler(DJ_U32 esrParam)
{
	Acs_Evt_t *			    pAcsEvt = NULL;

	Acs_Dev_List_Head_t * pAcsDevList = NULL;
	Acs_GeneralProc_Data* pGeneral=NULL;

	char		TmpStr[256];
	char *      pStr = NULL;

	pAcsEvt = (Acs_Evt_t *) esrParam;

	DispEventInfo ( pAcsEvt );

	switch ( pAcsEvt->m_s32EventType )
	{
		case XMS_EVT_OPEN_STREAM:
			printf("");
			break;

		case XMS_EVT_QUERY_DEVICE:
			if ( !bStartWorkFlag )
			{
				pAcsDevList = ( Acs_Dev_List_Head_t *) ( (DJ_S8 *)pAcsEvt + sizeof(Acs_Evt_t) );

				//Add or modify device resource to pool when receive the device's event of the state changing
				AddDeviceRes ( pAcsDevList );
			}
			break; 

		case XMS_EVT_QUERY_DEVICE_END:	//get device list completely
			if ( !bStartWorkFlag )
			{
				pGeneral = (Acs_GeneralProc_Data*)FetchEventData(pAcsEvt);
				sprintf ( TmpStr, "Start work. DeviceNum = %d\n", TotalDevRes );
				AddMsg ( MSG_TYPE_OTHER, TmpStr );

				InitDeviceInfo();

				bStartWorkFlag = true;
			}
			break;

		case XMS_EVT_OPEN_DEVICE:
			OpenDeviceOK ( &pAcsEvt->m_DeviceID );						
			break;

		case XMS_EVT_CLOSE_DEVICE:
			CloseDeviceOK ( &pAcsEvt->m_DeviceID );

			pStr = GetString_DeviceAll(&pAcsEvt->m_DeviceID);
			sprintf(TmpStr,"Close devcie evt: %s",pStr);
			AfxMessageBox(TmpStr,NULL,MB_OK);
			break;
		case XMS_EVT_ACS_TIMER:
			{
				UserLedCtrl ledCtrl={0};
				ledCtrl.m_u8FeedWatchDogEnable = 1;
				XMS_acsLedCtrl(g_acsHandle,g_u8LedDspUnit,&ledCtrl);
			}
			break;
		case XMS_EVT_PLAYCSPREQ:
			{
				DJ_S32  r = 0;
				char MsgStr[100]={0};
				CSPPlayDataInfo_t     playCSP={0};
				Acs_CSPDataReq_Data * pCspReq = NULL;
				CSP_OPERATER*pCSP = GetVocCSPProperty( pAcsEvt->m_DeviceID.m_s8ModuleID, (DJ_U16)pAcsEvt->m_DeviceID.m_s16ChannelID );

				if ( NULL == pCSP )
					break;

				g_cspPlay = pCSP->m_cspPlay;
				if(g_cspPlay == 0)
				{
					break;
				}

				pCspReq = (Acs_CSPDataReq_Data *)FetchEventData(pAcsEvt);

				g_cspPlayFp = pCSP->m_cspPlayFp;
				if(g_cspPlayFp == NULL)
				{
					strcpy( g_szCSPPlayFile, pCSP->m_szCSPPlayFile );
					g_cspPlayFp = fopen(g_szCSPPlayFile,"rb");
					pCSP->m_cspPlayFp = g_cspPlayFp;
				}

				if(feof(g_cspPlayFp))
				{
					fseek(g_cspPlayFp,SEEK_SET,0);
					TRACE("Play File Finish\n");
					sprintf ( MsgStr, "CSPPlay File<%s> End", g_szCSPPlayFile );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr);
					DoFunc_ControlPlayCSP( XMS_CSP_DELAY_STOP_PLAY );
					break;
				}
				
				playCSP.m_u16DataLen = pCspReq->m_u16ReqCspDataLen;
				playCSP.m_u8DataType = XMS_CSPPLAY_DATA_VOC;
				playCSP.m_u8TaskID = (DJ_U8)(GetTickCount() % 128);	
				
				long rr = fread(g_szDataBuf,sizeof(char),playCSP.m_u16DataLen,g_cspPlayFp);

				playCSP.m_u16DataLen = (DJ_U16)rr;

				TRACE("CSPPlay ReqDataLen = %d,sentData=%d\n",pCspReq->m_u16ReqCspDataLen,rr);

				g_PlayCSPDevID = pCSP->m_PlayCSPDevID;
				r = XMS_ctsSendCSPData(g_acsHandle, &g_PlayCSPDevID, &playCSP,g_szDataBuf,NULL);
				if ( r < 0 )
				{
					sprintf ( MsgStr, "X(%d) XMS_ctsSendCSPData() FAIL! (%s)", 
						r, GetString_DeviceAll (&g_PlayCSPDevID)  );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr);
				}
				else
				{
					/*
					sprintf ( MsgStr, "XMS_ctsSendCSPData(), ReqLen: %d, SendLen: %d OK! (%s)", 
						, GetString_DeviceAll (&g_PlayCSPDevID) );
					AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
					*/
				}	
				
				sprintf(MsgStr," ReqLen: %d, SndLen: %d ", pCspReq->m_u16ReqCspDataLen, playCSP.m_u16DataLen );
				AddMsg ( MSG_TYPE_FUNCTION, MsgStr );

			}
			break;
		case XMS_EVT_CONTROLPLAY:
			{
				CSP_OPERATER*pCSP = GetVocCSPProperty( pAcsEvt->m_DeviceID.m_s8ModuleID, (DJ_U16)pAcsEvt->m_DeviceID.m_s16ChannelID );

				if ( NULL != pCSP )
					pCSP->m_cspPlay = 0;

				g_cspPlay = 0;
			
			}
			break;
		case XMS_EVT_RECORDCSP:
			{
				Acs_MediaCSPProc_Data * pCSPData = NULL;
				CSP_OPERATER*pCSP = GetVocCSPProperty( pAcsEvt->m_DeviceID.m_s8ModuleID, (DJ_U16)pAcsEvt->m_DeviceID.m_s16ChannelID );

				if ( NULL == pCSP )
					break;

				g_cspRecordFp = pCSP->m_cspRecordFp;
				
				if ( NULL == g_cspRecordFp )
					break;
								
				pCSPData = (Acs_MediaCSPProc_Data *)FetchEventData(pAcsEvt);				
				fwrite(pCSPData->m_u8StreamData,sizeof(char),pCSPData->m_u16DataLen,g_cspRecordFp);				
				TRACE("***** CspRec RecvData=%d\n", pCSPData->m_u16DataLen);
			}
			break;
		case XMS_EVT_SET_MEDIAINFO:
			{
				Acs_VoIP_MediaInfo *pMediaInfo = (Acs_VoIP_MediaInfo *)FetchEventData(pAcsEvt);
				int index = FindOpenDevice(&pAcsEvt->m_DeviceID);
				if(index==-1)
					break;
				DevOpened[index].pDevData = (Acs_VoIP_MediaInfo*)malloc(sizeof(Acs_VoIP_MediaInfo));
				memcpy(DevOpened[index].pDevData, pMediaInfo, sizeof(Acs_VoIP_MediaInfo));
			}
			break;
        case XMS_EVT_OPEN_STREAM_EXT:
            {
                Acs_OpenStreamExt_Data *pStreamExt = NULL;
		        pStreamExt = (Acs_OpenStreamExt_Data *)FetchEventData(pAcsEvt);
		        
		        if ( (pStreamExt->m_ServerID.m_u32ServerPort == 9900) && (pStreamExt->m_s32AcsEvtState == 1) )
		        {
			        XMS_acsGetRelateMod (g_acsHandle, 6, 1);
		        }
            }
		    break;

	    case XMS_EVT_MODRELATE:
            {
                int 	i, j;
	            Acs_ModRelate_Data *pRelate = NULL;

	            pRelate = (Acs_ModRelate_Data *)FetchEventData(pAcsEvt);
	            if ( NULL == pRelate )
		            return;

	            for (i=0; i<pRelate->m_u8ModCount; i++)
	            {
		            if ( pRelate->m_RelateMod[i].m_u8ModuleType == 1 )
		            {
			            j = pRelate->m_RelateMod[i].m_u8UnitID - 1;
			            
			            sprintf (cfg_cDSPIpAddr[j].m_s8ServerIp, "%s", pRelate->m_RelateMod[i].m_s8IPAddress);
			            cfg_cDSPIpAddr[j].m_u32ServerPort = 6000;
		            }
	            }
            }
		    break;
        case XMS_EVT_CALLOUT:
            {
                BOOL bControlRtp = ((CButton*)pdlg->GetDlgItem(IDC_AUTORTP))->GetCheck();
                if(bControlRtp && pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_VOIP &&
                   CheckOpenDevice (iOpenedIndex2) && DevOpened[iOpenedIndex2].DevID.m_s16DeviceMain == XMS_DEVMAIN_RTP)
                {
                    //set rtp;
                    SetRtpMediaInfo(&DevOpened[iOpenedIndex2].DevID, (Acs_VoIP_MediaInfo*)DevOpened[iOpenedIndex1].pDevData);
                }
            }
            break;
        case XMS_EVT_CLEARCALL:
            {
                BOOL bControlRtp = ((CButton*)pdlg->GetDlgItem(IDC_AUTORTP))->GetCheck();
                if(bControlRtp && pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_VOIP)
                {
                     if(CheckOpenDevice (iOpenedIndex2) && DevOpened[iOpenedIndex2].DevID.m_s16DeviceMain == XMS_DEVMAIN_RTP)
                     {
                        //set rtp;
                        Acs_VoIP_RTPSESSION session;

	                    memset(&session, 0, sizeof(Acs_VoIP_RTPSESSION));
	                    XMS_ctsSetParam(g_acsHandle, &DevOpened[iOpenedIndex2].DevID, VOIP_PARAM_RTPSESSION, sizeof(Acs_VoIP_RTPSESSION), &session);
                     }
                }
            }
            break;
		default:
			break;
	}

}
