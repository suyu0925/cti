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
#include "DJAcsDevState.h"

#include "XMSApi_Test_Sub.h"
#include "XMSApi_Test_Event.h"
#include "XMSApi_Test_String.h"

char * GetString_EventType ( EventType_t EvtType )
{
	static char	TmpStr[40];

	switch ( EvtType )
	{
	case XMS_EVT_OPEN_STREAM:		return "OPEN_STREAM";
	case XMS_EVT_QUERY_DEVICE:		return "QUERY_DEVICE";
	case XMS_EVT_QUERY_DEVICE_END:	return "QUERY_DEVICE_END";
	case XMS_EVT_OPEN_DEVICE:		return "OPEN_DEVICE";
	case XMS_EVT_CLOSE_DEVICE:		return "CLOSE_DEVICE";
	case XMS_EVT_RESET_DEVICE:		return "RESET_DEVICE";
	case XMS_EVT_DEVICESTATE:		return "DEVICESTATE";
	case XMS_EVT_E1STATE:           return "E1STATE";
	case XMS_EVT_CTBUS_CLK_REF_SRC_STATE:		return "E1_CLK_STATE";
	case XMS_EVT_SETDEV_GROUP:		return "SETDEV_GROUP";
	case XMS_EVT_SETPARAM:			return "SETPARAM";
	case XMS_EVT_GETPARAM:			return "GETPARAM";
	case XMS_EVT_QUERY_ONE_DSP_START:	return "QUERY_ONE_DSP_START";
	case XMS_EVT_QUERY_ONE_DSP_END:		return "QUERY_ONE_DSP_END";
	case XMS_EVT_QUERY_REMOVE_ONE_DSP_START:	return "QUERY_REMOVE_ONE_DSP_START";
	case XMS_EVT_QUERY_REMOVE_ONE_DSP_END:		return "QUERY_REMOVE_ONE_DSP_END";
	case XMS_EVT_OPEN_STREAM_EXT:	return "OPEN_STREAM_EXT";

	case XMS_EVT_CALLOUT:			return "CALLOUT";
	case XMS_EVT_CALLIN:			return "CALLIN";
	case XMS_EVT_ALERTCALL:			return "ALERTCALL";
	case XMS_EVT_ANSWERCALL:		return "ANSWERCALL";
	case XMS_EVT_LINKDEVICE:		return "LINKDEVICE";
	case XMS_EVT_UNLINKDEVICE:		return "UNLINKDEVICE";
	case XMS_EVT_CLEARCALL:			return "CLEARCALL";
	case XMS_EVT_ANALOG_INTERFACE:	return "ANALOG_INTERFACE";
	case XMS_EVT_CAS_MFC_START:		return "XMS_EVT_CAS_MFC_START";
	case XMS_EVT_CAS_MFC_END:		return "XMS_EVT_CAS_MFC_END";

	case XMS_EVT_JOINTOCONF:		return "JOINTOCONF";
	case XMS_EVT_LEAVEFROMCONF:		return "LEAVEFROMCONF";
	case XMS_EVT_CLEARCONF:			return "CLEARCONF";


	case XMS_EVT_PLAY:				return "PLAY";
	case XMS_EVT_INITINDEX:			return "INITINDEX";
	case XMS_EVT_BUILDINDEX:		return "BUILDINDEX";
	case XMS_EVT_CONTROLPLAY:		return "CONTROLPLAY";
	case XMS_EVT_RECORD:			return "RECORD";
	case XMS_EVT_CONTROLRECORD:		return "CONTROLRECORD";
	case XMS_EVT_RECORDCSP:			return "RECORDCSP";
	case XMS_EVT_CONTROLRECORDCSP:  return "CONTROLRECORDCSP";
	case XMS_EVT_3GPP_PLAY:			return "3GPPPlay";
	case XMS_EVT_3GPP_CONTROLPLAY:	return "3GPPControlPlay";
	case XMS_EVT_3GPP_RECORD:		return "3GPPRecord";
	case XMS_EVT_3GPP_CONTROLRECORD: return "3GPPControlRecord";
	case XMS_EVT_PLAYCSPREQ:		return "CSPPlayReq";

	case XMS_EVT_SENDFAX:			return "XMS_EVT_SENDFAX";
	case XMS_EVT_RECVFAX:			return "XMS_EVT_RECVFAX";
	
	case XMS_EVT_SENDIODATA:		return "SENDIODATA";
	case XMS_EVT_RECVIODATA:		return "RECVIODATA";

	case XMS_EVT_MODMONITOR:	    return "MODMONITOR";
	case XMS_EVT_DEV_TIMER:			return  "DEV_TIMER";
 	case XMS_EVT_3GPP_INIT_INDEX:	return  "3GPPInitIndex";
	case XMS_EVT_3GPP_BUILD_INDEX:	return  "3GPPBuildIndex";
    case XMS_EVT_ACS_TIMER:         return  "SYS_TIMER";

    case XMS_EVT_CTX_REG:           return  "CTX_REG";
    case XMS_EVT_CTX_LINK:          return  "CTX_LINK";
    case XMS_EVT_CTX_APPDATA:       return  "CTX_APPDATA";
	
	case XMS_EVT_SET_MEDIAINFO:		return	"MEDIAINFO";
	case XMS_EVT_MASTER_STATE:      return  "MASTER STATE";
	case XMS_EVT_SLAVE_WORK_STATE:  return  "SLAVE WORK STATE";
	case XMS_EVT_UNIFAILURE:		return  "UNIFAILURE";
	case XMS_EVT_MODRELATE:         return  "MODRELATE";
    case XMS_EVT_CLOSE_STREAM_EXT:  return  "Close Stream EXT";
	}

	sprintf ( TmpStr, "UNKNOWN(0x%X)", EvtType );
	return TmpStr;
}

char *GetString_DeviceMain ( DJ_S32	s32DeviceMain )
{
	static char	TmpStr[40];

	switch ( s32DeviceMain )
	{
	case XMS_DEVMAIN_VOICE:				return "VOC  ";
	case XMS_DEVMAIN_FAX:				return "FAX  ";
	case XMS_DEVMAIN_DIGITAL_PORT:		return "DIGIT";
	case XMS_DEVMAIN_INTERFACE_CH:		return "INTCH";
	case XMS_DEVMAIN_DSS1_LINK:			return "DSS1 ";
	case XMS_DEVMAIN_SS7_LINK:			return "SS7  ";
	case XMS_DEVMAIN_BOARD:				return "BRD  ";
	case XMS_DEVMAIN_CTBUS_TS:			return "CTBUS";
	case XMS_DEVMAIN_VOIP:				return "VOIP ";
	case XMS_DEVMAIN_CONFERENCE:		return "CONF ";
	case XMS_DEVMAIN_VIDEO:				return "VIDEO";
	case XMS_DEVMAIN_RTPX:				return "RTPX";
	case XMS_DEVMAIN_MEDIAEX:			return "MediaEx";
	case XMS_DEVMAIN_CTX:			    return "CTX";
	case XMS_DEVMAIN_RTP:				return "RTP";
	}

	sprintf ( TmpStr, "UNKNOWN(0x%X)", s32DeviceMain );
	return TmpStr;
}

char *GetString_DeviceSub (DJ_S32	s32DeviceMain, DJ_S32	s32DeviceSub )
{
	static char	TmpStr[40];

	switch(s32DeviceMain)
	{
	case XMS_DEVMAIN_VOICE:
		{
			switch(s32DeviceSub)
			{
			case XMS_DEVSUB_MEDIA_VOC:			return "VOC";
			case XMS_DEVSUB_MEDIA_324:			return "324";
			}
		}
		break;

	case XMS_DEVMAIN_INTERFACE_CH:
		{
			switch ( s32DeviceSub )
			{
			case XMS_DEVSUB_BASE:						return "BASE   ";
			case XMS_DEVSUB_ANALOG_TRUNK:				return "A_TRUNK";
			case XMS_DEVSUB_ANALOG_USER:				return "A_USER ";
			case XMS_DEVSUB_ANALOG_HIZ:					return "A_HIZ  ";
			case XMS_DEVSUB_ANALOG_EMPTY:				return "A_EMPTY";
			case XMS_DEVSUB_E1_PCM:						return "E1_PCM ";
			case XMS_DEVSUB_E1_CAS:						return "E1_CAS ";
			case XMS_DEVSUB_E1_DSS1:					return "E1_DSS1";
			case XMS_DEVSUB_E1_SS7_TUP:					return "E1_TUP ";
			case XMS_DEVSUB_E1_SS7_ISUP:				return "E1_ISUP";
			case XMS_DEVSUB_ANALOG_VOC2W:				return "A_VOC2W";
			case XMS_DEVSUB_ANALOG_VOC4W:				return "A_VOC4W";
			case XMS_DEVSUB_ANALOG_EM:					return "A_EM   ";
			case XMS_DEVSUB_E1_DCH:						return "E1_DCH ";
			case XMS_DEVSUB_E1_BCH:						return "E1_BCH ";
			case XMS_DEVSUB_UNUSABLE:					return "UNUSE  ";			
			case XMS_DEVSUB_HIZ_CAS:					return "Hiz-Cas";
			case XMS_DEVSUB_HIZ_PRI:					return "Hiz-Pri";
			case XMS_DEVSUB_HIZ_SS7:					return "Hiz-SS7";
			case XMS_DEVSUB_HIZ_PRI_LINK:				return "Hiz-Pri-Link";
			case XMS_DEVSUB_HIZ_SS7_64K_LINK:			return "Hiz-SS7-64KLink";
			case XMS_DEVSUB_HIZ_SS7_2M_LINK:			return "Hiz-SS7-2MLink";
			case XMS_DEVSUB_SS7_LINK:					return "SS7-Link";
			case XMS_DEVSUB_ANALOG_REC:	                return "A_REC";
			case XMS_DEVSUB_DIGITAL_REC:	            return "D_REC";
			case XMS_DEVSUB_SS7_2M_LINK:				return "SS7-2M-Link";
			}
		}
	}

	if( s32DeviceMain == XMS_DEVMAIN_VOIP )
		sprintf ( TmpStr, "Non-SubDev");
	else
		sprintf ( TmpStr, "UNKNOWN(0x%X)", s32DeviceSub );

	return TmpStr;
}

char *GetString_DeviceAll ( DeviceID_t *pDevID )
{
	static char	TmpStr[80];
	char	TmpS[40]; 

	strcpy ( TmpStr, "" );

	// for VOICE
	if ( XMS_DEVMAIN_VOICE == pDevID->m_s16DeviceMain)
	{
		strcat ( TmpStr, GetString_DeviceSub(pDevID->m_s16DeviceMain, pDevID->m_s16DeviceSub) );
		strcat ( TmpStr, " " );
	}
	else  // main type
	{
		strcat ( TmpStr, GetString_DeviceMain(pDevID->m_s16DeviceMain) );
		strcat ( TmpStr, " " );
	}

	// dsp module ID, channel ID
	sprintf ( TmpS, "%3d, %3d, ", pDevID->m_s8ModuleID, pDevID->m_s16ChannelID );
	strcat ( TmpStr, TmpS );
	
	// sub type
	if ( pDevID->m_s16DeviceMain == XMS_DEVMAIN_INTERFACE_CH )
		strcat ( TmpStr, GetString_DeviceSub(pDevID->m_s16DeviceMain,pDevID->m_s16DeviceSub) );

	return TmpStr;
}

char *GetString_ErrorCode ( DJ_S32	s32ErrorCode )
{
	static char	TmpStr[40];

	switch ( s32ErrorCode )
	{
	case 0:                                 return "OK";
	case ACSERR_LOADLIBERR:					return "LOADLIBERR";
	case ACSERR_BADPARAMETER:				return "BADPARAMETER";
	case ACSERR_NOSERVER:					return "NOSERVER";
	case ACSERR_MAXCONN_EXCEED:				return "MAXCONN_EXCEED";
	case ACSERR_BADHDL:						return "ABADHDL";

	case ACSERR_FAILSEND:					return "FAILSEND";
	case ACSERR_LINKBROKEN:					return "LINKBROKEN";
	case ACSERR_NOMESSAGE:					return "NOMESSAGE";
	case ACSERR_GETRESFAIL:					return "GETRESFAIL";
	case ACSERR_NOSUPPORTCMD:				return "NOSUPPORTCMD";
	}

	sprintf ( TmpStr, "UNKNOWN(0x%X)", s32ErrorCode );
	return TmpStr;
}

char *GetString_PlayControlType ( DJ_U16 u16ControlType )
{
	static char	TmpStr[40];

	switch ( u16ControlType )
	{
	case XMS_STOP_PLAY:						return "STOP_PLAY";
	case XMS_PAUSE_PLAY:					return "PAUSE_PLAY";
	case XMS_RESUME_PLAY:					return "RESUME_PLAY";
	case XMS_STEP_BACKWARD_PLAY:			return "STEP_BACKWARD_PLAY";
	case XMS_STEP_FORWARD_PLAY:				return "STEP_FORWARD_PLAY";
	}

	sprintf ( TmpStr, "UNKNOWN(0x%X)", u16ControlType );
	return TmpStr;
}

char *GetString_RecordControlType ( DJ_U32 u32ControlType )
{
	static char	TmpStr[40];

	switch ( u32ControlType )
	{
	case XMS_STOP_RECORD:					return "STOP_RECORD";
	case XMS_PAUSE_RECORD:					return "PAUSE_RECORD";
	case XMS_RESUME_RECORD:					return "RESUME_RECORD";
	case XMS_STEP_BACKWARD_RECORD:			return "STEP_BACKWARD_RECORD";
	}

	sprintf ( TmpStr, "UNKNOWN(0x%X)", u32ControlType );
	return TmpStr;
}

char *GetString_DeviceState ( DJ_U32	s32DeviceState )
{
	static char	TmpStr[40];

	switch ( s32DeviceState )
	{
	case DEVICE_COMMON_STATE_START:			return "S_BASE";
	case DCS_FREE:							return "S_FREE";
	case DCS_LOCAL_BLOCK:					return "S_LOCAL_BLOCK";
	case DCS_REMOTE_BLOCK:					return "S_REMOTE_BLOCK";
	case DCS_BLOCK:							return "S_BLOCK";
	case DCS_UNAVAILABLE:					return "S_UNAVAILABLE";

	case DCS_CALLOUT:						return "S_CALLOUT";
	case DCS_CALLIN:						return "S_CALLIN";
	case DCS_ALERTING:						return "S_ALERTING";

	case DCS_CONNECT:						return "S_CONNECT";
	case DCS_DISCONNECT:					return "S_DISCONNECT";
	case DCS_WAIT_FREE:						return "S_WAIT_FREE";
	//default:                                return "Unknow State";
	}

	////////////////////////////
	/*
	//15 is ISUP_1_LINK
int E1type = (pGeneralData->m_s32DeviceState >> 16) & 0xFF;
int alarmValue = pGeneralData->m_s32DeviceState & 0xFFFF;
if ( alarmValue & XMS_E1PORT_MASK_LOST_SIGNAL )
{
   // Link Broken
}

	*/
	//return GetString_FaxState(s32DeviceState);
	sprintf ( TmpStr, "UNKNOWN(0x%X)", s32DeviceState );
	return TmpStr;
}

char *GetString_VocDeviceState ( DJ_U8 u8DSPID, DJ_U16 u16ChID, DJ_U32 s32DeviceState )
{
	static char	TmpStr[100];

	memset( TmpStr, 0, 100 );

	if ( XMS_VOC_DEV_STATE_FREE == s32DeviceState )
	{
		TRACE("(DSP: %d, CH: %d) Voc DevState: %s \n", u8DSPID, u16ChID, "XMS_VOC_DEV_STATE_FREE" );
		strcat(TmpStr, "FREE " );
	}

  	if ( XMS_VOC_DEV_STATE_PLAYING & s32DeviceState )
	{
		TRACE("(DSP: %d, CH: %d) Voc DevState: %s \n", u8DSPID, u16ChID, "XMS_VOC_DEV_STATE_PLAYING" );
		strcat(TmpStr, "PLAYING " );
	}
  
  	if ( XMS_VOC_DEV_STATE_CSPPLAYING & s32DeviceState )
	{
		TRACE("(DSP: %d, CH: %d) Voc DevState: %s \n", u8DSPID, u16ChID, "XMS_VOC_DEV_STATE_CSPPLAYING" );
		strcat(TmpStr, "CSPPLAYING " );
	}

  	if ( XMS_VOC_DEV_STATE_RECORDING & s32DeviceState )
	{
		TRACE("(DSP: %d, CH: %d) Voc DevState: %s \n", u8DSPID, u16ChID, "XMS_VOC_DEV_STATE_RECORDING" );
		strcat(TmpStr, "RECORDING " );
	}

  	if ( XMS_VOC_DEV_STATE_CSPRECORDING & s32DeviceState )
	{
		TRACE("(DSP: %d, CH: %d) Voc DevState: %s \n", u8DSPID, u16ChID, "XMS_VOC_DEV_STATE_CSPRECORDING" );
		strcat(TmpStr, "CSPRECORDING " );
	}

	if ( XMS_VOC_DEV_STATE_PLAYSTOPING & s32DeviceState )
	{
		TRACE("(DSP: %d, CH: %d) Voc DevState: %s \n", u8DSPID, u16ChID, "XMS_VOC_DEV_STATE_PLAYSTOPING" );
		strcat(TmpStr, "PLAYSTOPING " );
	}

	if ( XMS_VOC_DEV_STATE_CSPPLAYSTOPING & s32DeviceState )
	{
		TRACE("(DSP: %d, CH: %d) Voc DevState: %s \n", u8DSPID, u16ChID, "XMS_VOC_DEV_STATE_CSPPLAYSTOPING" );
		strcat(TmpStr, "CSPPLAYSTOPING " );
	}

	if ( XMS_VOC_DEV_STATE_RECORDSTOPING & s32DeviceState )
	{
		TRACE("(DSP: %d, CH: %d) Voc DevState: %s \n", u8DSPID, u16ChID, "XMS_VOC_DEV_STATE_RECORDSTOPING" );
		strcat(TmpStr, "RECORDSTOPING " );
	}

	if ( XMS_VOC_DEV_STATE_CSPRECORDSTOPING & s32DeviceState )
	{
		TRACE("(DSP: %d, CH: %d) Voc DevState: %s \n", u8DSPID, u16ChID, "XMS_VOC_DEV_STATE_CSPRECORDSTOPING" );
		strcat(TmpStr, "CSPRECORDSTOPING " );
	}

	if ( XMS_VOC_DEV_STATE_SENDINGIODATA & s32DeviceState )
	{
		TRACE("(DSP: %d, CH: %d) Voc DevState: %s \n", u8DSPID, u16ChID, "XMS_VOC_DEV_STATE_SENDINGIODATA" );
		strcat(TmpStr, "SENDINGIODATA " );
	}

	//sprintf(TmpStr, " %d ", s32DeviceState);

	return TmpStr;
}

char *GetString_IOType ( DJ_U16 u16IOType )
{
	static char	TmpStr[40];

	switch ( u16IOType )
	{
	case XMS_IO_TYPE_DTMF:							return "TYPE_DTMF";
	case XMS_IO_TYPE_MR2F:							return "TYPE_MR2F";
	case XMS_IO_TYPE_MR2B:							return "TYPE_MR2B";
	case XMS_IO_TYPE_GTD:							return "TYPE_GTD";
	case XMS_IO_TYPE_FSK:							return "TYPE_FSK";
	case XMS_IO_TYPE_DPD:							return "TYPE_DPD";
	case XMS_IO_TYPE_PVD:							return "TYPE_PVD";
	case XMS_IO_TYPE_MSK:							return "TYPE_MSK";
	case XMS_IO_TYPE_VSD:							return "TYPE_VSD";
	case XMS_IO_TYPE_MSKREND:					    return "TYPE_MSKREND";
	case XMS_IO_TYPE_DRS:					        return "TYPE_DRS";
		
	}

	sprintf ( TmpStr, "UNKNOWN(0x%X)", u16IOType );

	return TmpStr;
}


char* GetString_AnalogInterfaceState(DJ_S16 u16DevSub,DJ_U8 u8Interface)
{
	static char	TmpStr[40];

	if(u16DevSub == XMS_DEVSUB_ANALOG_USER)
	{
		switch ( u8Interface )
		{
		case XMS_ANALOG_USER_CH_OFFHOOK:				return "AUSER_OFFHOOK";
		case XMS_ANALOG_USER_CH_ONHOOK:					return "AUSER_ONHOOK";
		case XMS_ANALOG_USER_CH_FLASH:					return "AUSER_FLASH";
		}
	}
	else if(u16DevSub == XMS_DEVSUB_ANALOG_TRUNK)
	{
		switch ( u8Interface )
		{
		case XMS_ANALOG_TRUNK_CH_RING:					return "ATRUNK_RING";
		case XMS_ANALOG_TRUNK_CH_POSITEX_POLARITY:		return "ATRUNK_POSITIVE";
		case XMS_ANALOG_TRUNK_CH_NEGATIVE_POLARITY:		return "ATRUNK_NEGATIVE";
		case XMS_ANALOG_TRUNK_CH_NOLOOP:				return "ATRUNK_NOLOOP";
		}
	}

	sprintf ( TmpStr, "UNKNOWN(0x%X)", u8Interface );
	return TmpStr;

}

char* GetString_FaxState(DJ_U32 u32State)
{
	static char	TmpStr[40];

	switch ( u32State )
	{

	case DES_FAX_OPEN:  return "FAX_OPEN";
	case DES_FAX_CLOSE: return "FAX_CLOSE";
	case DES_FAX_RESET: return "FAX_RESET";
	case DES_FAX_SENDFAX_RECVCMD:			return "SENDFAX_RECVCMD";
	case DES_FAX_SENDFAX_START:			return "SENDFAX_START";
	case DES_FAX_SENDFAX_REMOTESPEC:		return "SENDFAX_REMOTESPEC";
	case DES_FAX_SENDFAX_LOCAL_FINISH:		return "SENDFAX_LOCAL_FINISH";
	case DES_FAX_SENDFAX_SHAKEHAND_END:		return "SENDFAX_SHAKEHAND_END";
	case DES_FAX_SENDFAX_RESOLVE_START:		return "SENDFAX_RESOLVE_START";
	case DES_FAX_SENDFAX_REQUESTPAGEDATA:		return "SENDFAX_REQUESTPAGEDATA";
	case DES_FAX_SENDFAX_RESOLVE_RESULT:		return "SENDFAX_RESOLVE_RESULT";    
	case DES_FAX_SENDFAX_SENDDATA:			return "SENDFAX_SENDDATA";
	case DES_FAX_SENDFAX_SENDFINISH:		return "SENDFAX_SENDFINISH";
	case DES_FAX_SENDFAX_USERSTOP:			return "SENDFAX_USERSTOP";
	case DES_FAX_SENDFAX_SENDEND:			return "SENDFAX_SENDEND";

	case DES_FAX_RECVFAX_RECVCMD:			return "RECVFAX_RECVCMD";
	case DES_FAX_RECVFAX_START:			return "RECVFAX_START";
	case DES_FAX_RECVFAX_HANDSHAKE:			return "RECVFAX_HANDSHAKE";
	case DES_FAX_RECVFAX_RECVDATA_START:		return "RECVFAX_RECVDATA_START";
	case DES_FAX_RECVFAX_BACKPAGESTATE:		return "RECVFAX_BACKPAGESTATE";
	case DES_FAX_RECVFAX_RE_HANDSHAKE:		return "RECVFAX_RE_HANDSHAKE";
	case DES_FAX_RECVFAX_RECVDATA_END:		return "RECVFAX_RECVDATA_END";
	case DES_FAX_RECVFAX_USERSTOP:			return "RECVFAX_USERSTOP";
	case DES_FAX_RECVFAX_COMPOSE_START:		return "RECVFAX_COMPOSE_START";
	case DES_FAX_RECVFAX_COMPOSE_END:		return "RECVFAX_COMPOSE_END";
	case DES_FAX_RECVFAX_RECVFINISH:		return "RECVFAX_RECVFINISH";
	case DES_FAX_RECVFAX_RECVEND:			return "RECVFAX_RECVEND";
	}

	sprintf ( TmpStr, "FaxState UNKNOWN(0x%X)", u32State );
	return TmpStr;
}

char * GetStringConfErrCode( DJ_S32 s32RetState, DJ_S32 s32ErrCode )
{
	static char	TmpStr[40];

	if ( 0 == s32RetState )
		sprintf ( TmpStr, "OK(0x%X, 0x%X)", s32RetState, s32ErrCode );	
	else
		sprintf ( TmpStr, "Failed(0x%X, 0x%X)", s32RetState, s32ErrCode );	

	return TmpStr;
}

char * GetStringMediaErrCode( DJ_S32 s32RetState, DJ_S32 s32ErrCode )
{
	static char	TmpStr[40];

	if ( 1 == s32RetState ) //success
	{
		switch ( s32ErrCode )
		{
		case XMS_ERR_CODE_OK:                   return "OK";
		case XMS_ERR_CODE_GTD:                  return "GTD_STOP";
		case XMS_ERR_CODE_APPSTOP:              return "APP_STOP";

		case XMS_ERR_CODE_OPENFILE_FAILED:      return "Open_File Failed";
		case XMS_ERR_CODE_WREADFILE_FAILED:     return "WR File Failed";
		case XMS_ERR_CODE_CH_MISSING:           return "Channel missing";
		case XMS_ERR_CODE_EXE_FAILED:           return "Execute failed";
		case XMS_ERR_CODE_PLAY_QUEUE_FULL:      return "Play Q Full";
		case XMS_ERR_CODE_BUILD_INDEX_FAILED:   return "Build index failed";
		case XMS_ERR_SYSTEM_OVERLOAD:           return "System overload";
		case XMS_ERR_CODE_BUILD_INDEX_OK:		return "BUILD INDEX OK";
		case XMS_ERR_CODE_3G_AUDIO_OK:			return "AUDIO OK";
		case XMS_ERR_CODE_3G_VIDEO_OK:		    return "VIDEO OK";
		}

		sprintf ( TmpStr, "Success Event, MediaErrCode UNKNOWN(0x%X, 0x%X)", s32RetState, s32ErrCode );		
	}

	if ( 0 == s32RetState ) //failed
	{
		switch ( s32ErrCode )
		{
		case XMS_ERR_CODE_APPSTOP:              return "APP_STOP";
		case XMS_ERR_CODE_GTD:                  return "GTD_STOP";
		case XMS_ERR_CODE_OPENFILE_FAILED:	    return "OPEN FAIL";
		case XMS_ERR_CODE_WREADFILE_FAILED:	    return "WR FAIL";
		case XMS_ERR_CODE_CH_MISSING:			return "CH MISSING";
		case XMS_ERR_CODE_EXE_FAILED:	        return "EXE FAIL";
		case XMS_ERR_CODE_PLAY_QUEUE_FULL:		return "QUEUE FULL";
		case XMS_ERR_CODE_BUILD_INDEX_FAILED:	return "BUILD INDEX NOK";
		case XMS_ERR_SYSTEM_OVERLOAD:			return "SYS OVERLOAD";
		}

		sprintf ( TmpStr, "Fail Event, MediaErrCode UNKNOWN(0x%X, 0x%X)", s32RetState, s32ErrCode );		
	}



	return TmpStr;
}

char *GetString_DigitalPortDeviceState ( DJ_U32	s32DeviceState )
{
	static char	TmpStr[100];

	memset(TmpStr, 0, 100);

	//15 is ISUP_1_LINK
	int E1type = (s32DeviceState >> 16) & 0xFF;
	int alarmValue = s32DeviceState & 0xFFFF;

	if ( XMS_E1PORT_MASK_LOST_SIGNAL & s32DeviceState  )
	{
		strcat(TmpStr,"LOST_SIGNAL");;
	}	
	else if ( s32DeviceState & XMS_E1PORT_MASK_FAS_ALARM )
	{
		strcat(TmpStr,"FAS_ALARM");;
	}	
	else if ( s32DeviceState & XMS_E1PORT_MASK_MFAS_ALARM )
	{
		strcat(TmpStr,"MFAS_ALARM");;
	}
	else if ( s32DeviceState & XMS_E1PORT_MASK_CRC4_ALARM )
	{
		strcat(TmpStr,"CRC4_ALARM");;
	}
	else if ( s32DeviceState & XMS_E1PORT_MASK_REMOTE_ALARM )
	{
		strcat(TmpStr,"REMOTE_ALARM");;
	}
	/*
	else if ( s32DeviceState & XMS_E1PORT_MASK_REMOTE_MF_ALARM )
	{
		strcat(TmpStr,"REMOTE_MF_ALARM");;
	}
	*/
	else if ( s32DeviceState & XMS_E1PORT_MASK_TX_OPEN_ALARM )
	{
		strcat(TmpStr,"TX_OPEN_ALARM");;
	}
	else if ( s32DeviceState & XMS_E1PORT_MASK_TX_SHORT_ALARM )
	{
		strcat(TmpStr,"TX_SHORT_ALARM");;
	}
	else
	{
		sprintf ( TmpStr, "E1 Link OK(0x%X)", s32DeviceState );		
	}

	/*
	if ( (s32DeviceState & XMS_E1PORT_MASK_RX_LEVEL )
	{
		strcat(TmpStr,"RX_LEVEL & ");;
	}
	if ( (s32DeviceState & XMS_E1PORT_MASK_TYPE )
	{
		strcat(TmpStr,"E1 Link OK ");;
	}
	*/

	if ( 0 == strlen(TmpStr) )
		sprintf ( TmpStr, "E1 Link OK(0x%X)", s32DeviceState );

	return TmpStr;
}

void DJ_Test( DJ_U8 * pMemList, DJ_U32 u32ChID )
{
	int nVal    = (u32ChID)/8;
	int nOffSet = (u32ChID)%8;
	
    TRACE("((pMemList[ %d ])>>( %d )) & 0x01 == %d \n", nVal, nOffSet, ((pMemList[ nVal ])>>nOffSet)&0x01 );
	
}

char * GetConfActiveMember( DJ_U8 *pMemberList, DJ_U32 *pMemNums )
{
	int i = 0;
	char str[10] = {0};
	static char m_strTemp[512];

	memset( m_strTemp, 0, 512 );

	TRACE("****************************\n");
	for ( i = 0; i < 16; i++ )
	{
		TRACE("%x ", pMemberList[i]);
	}
	TRACE("\n****************************\n");

	if ( NULL != pMemNums )
		*pMemNums = 0;

	for ( i = 0; i < 128; i++ )
	{
		DJ_Test(pMemberList, i);

		if ( GetActiveMem(pMemberList, i) )
		{
			sprintf( str, "%d ", i);
			strcat(m_strTemp, str);		

			if ( NULL != pMemNums )
				*pMemNums++;
		}
	}

	return m_strTemp;
}

char *GetString_ClockState ( DJ_U8	u8ClockState )
{
	static char	TmpStr[40];

	switch ( u8ClockState )
	{
	case XMS_CLK_STATE_SET:			return "Clock Set";
	case XMS_CLK_STATE_RELEASE:     return "Clock Release";
    default:                        return "Unknow State";
	}

	sprintf ( TmpStr, "UNKNOWN(0x%X)", u8ClockState );
	return TmpStr;
}

char *GetString_E1Info( ACS_Digital_PortState_Data*  pData )
{
	static char	TmpStr[500];

	memset( TmpStr, 0, 500 );

	//1:表示正常，0：表示异常
	if ( 0 == pData->m_u8Lost_signal )
	{
		sprintf( TmpStr, "Sig:%s ", "1");
	}
	else
	{
		sprintf( TmpStr, "Sig:%s ", "0");
	}

	if ( 0 == pData->m_u8Fas_align )
	{
		strcat( TmpStr, "FA:1 ");
	}
	else
	{
		strcat( TmpStr, "FA:0 ");
	}

	if ( 0 == pData->m_u8Mf_align )
	{
		strcat( TmpStr, "MA:1 ");
	}
	else
	{
		strcat( TmpStr, "MA:0 ");
	}

	if ( 0 == pData->m_u8Crc4_align )
	{
		strcat( TmpStr, "CRC4:1 ");
	}
	else
	{
		strcat( TmpStr, "CRC4:0 ");
	}

	if ( 0 == pData->m_u8Remote_alarm )
	{
		strcat( TmpStr, "RA:1 ");
	}
	else
	{
		strcat( TmpStr, "RA:0 ");
	}

	if ( 0 == pData->m_u8Remote_MF_alarm )
	{
		strcat( TmpStr, "RMA:1 ");
	}
	else
	{
		strcat( TmpStr, "RMA:0 ");
	}

	return TmpStr;
}
