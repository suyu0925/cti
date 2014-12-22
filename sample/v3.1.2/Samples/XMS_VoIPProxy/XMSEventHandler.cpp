// XMSEventHandler.cpp : implementation file
//

#include "stdafx.h"

#include "XMSVoIPProxy.h"
#include "XMSVoIPProxyDlg.h"

#include "XMSEventHandler.h"
#include "XMSData.h"

extern CXMSVoIPProxyApp theApp;
CXMSVoIPProxyDlg *g_pDlg = NULL;
std::list<tagRouteItem*> g_lsRoute;

RetCode_t linkDevice(XMS_VOIP_DEVICE *devIP, XMS_VOICE_DEVICE *devVoc);
RetCode_t linkDevice(XMS_INTERFACE_DEVICE *devTrk, XMS_VOICE_DEVICE *devVoc);
RetCode_t unlinkDevice(XMS_VOIP_DEVICE *devIP, XMS_VOICE_DEVICE *devVoc);
RetCode_t unlinkDevice(XMS_INTERFACE_DEVICE *devTrk, XMS_VOICE_DEVICE *devVoc);

int getMatchVoIP(const DJ_S8 *szRegTelNo);

//////////////////////////////////////////////////////////////////////////
// event handlers
void OnOpenStream(Acs_Evt_t *pAcsEvt);
void OnQueryDevice(Acs_Evt_t *pAcsEvt);
void OnQueryDeviceEnd(Acs_Evt_t *pAcsEvt);
void OnOpenDevice(Acs_Evt_t *pAcsEvt);
void OnCloseDevice(Acs_Evt_t *pAcsEvt);
void OnDeviceState(Acs_Evt_t *pAcsEvt);
void OnDeviceStateVoIP(int iDeviceIP, int iState);
void OnDeviceStateTrunk(int iDeviceTrk, int iState);
void OnCallOut(Acs_Evt_t *pAcsEvt);
void OnCallIn(Acs_Evt_t *pAcsEvt);
void OnAlertCall(Acs_Evt_t *pAcsEvt);
void OnAnswerCall(Acs_Evt_t *pAcsEvt);
void OnClearCall(Acs_Evt_t *pAcsEvt);
void OnLinkDevice(Acs_Evt_t *pAcsEvt);
void OnUnlinkDevice(Acs_Evt_t *pAcsEvt);
void OnPlay(Acs_Evt_t *pAcsEvt);
void OnRecvIOData(Acs_Evt_t *pAcsEvt);
void OnRecvIODataVoIP(int iDevice, Acs_Evt_t *pAcsEvt);
void OnRecvIODataVoice(int iDevice, Acs_Evt_t *pAcsEvt);
void OnJoinConf(Acs_Evt_t *pAcsEvt);
void OnUnattandCallTransfer(int iSrcDev, Acs_VoIP_Refer* pRefer);
void OnAttandCallTransfer(int iSrcDev, Acs_VoIP_Refer* pRefer);
void SendReferNotify(int iVoIPDev, int iStatusCode);
void OnGetParam(Acs_Evt_t* pAcsEvt);
void OnGetMediaInfo(Acs_Evt_t* pAcsEvt);
void SetRTPIP(DeviceID_t* dev, DJ_U8 u8AudioEnabled, const DJ_S8* s8AudioAddress, DJ_U16  u16AudioPort, DJ_U8   u8VideoEnabled, const DJ_S8* s8VideoAddress, DJ_U16  u16VideoPort);
void SetRTPSession(DeviceID_t* dev, DJ_U8 u8Enabled, DJ_U8 dtmf, DJ_U8 tone);
void SetRTPCodec(DeviceID_t* dev, DJ_U8 u8AudioEnabled, DJ_U8 u8AudioCodec, DJ_U8 u8AudioPayloadType, DJ_U8 u8VideoEnabled, DJ_U8 u8VideoCodec, DJ_U8 u8VideoPayloadType);

#define RTP_PORT_BASE(portbase, unit_id)	(DJ_U16)(portbase + (unit_id < 65 ? (unit_id-1)*100 : (unit_id-49)*100 ))

typedef struct ITP_RTP_CODEC_TAG
{
    DJ_U8	u8CodecType;		// codec type
    DJ_U8	u8PayloadType;		// rtp payload type
    DJ_S8	s8MimeSubtype[10];	// MIME subtype name (used as sdp encoding name)
    DJ_S8	s8H245Name[50];		// h.245 capability name
} ITP_RTP_CODEC;

ITP_RTP_CODEC g_rtp_codec[] =
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

RetCode_t linkDevice(XMS_VOIP_DEVICE *devIP, XMS_VOICE_DEVICE *devVoc)
{
	RetCode_t ret = XMS_ctsLinkDevice(g_acsHandle, &devIP->device, &devVoc->device, NULL);

	TRACE("link voip(%d/%d) to voice(%d/%d)\n",
		devIP->device.m_s8ModuleID, devIP->device.m_s16ChannelID,
		devVoc->device.m_s8ModuleID, devVoc->device.m_s16ChannelID);

	return ret;
}

RetCode_t linkDevice(XMS_INTERFACE_DEVICE *devTrk, XMS_VOICE_DEVICE *devVoc)
{
	RetCode_t ret;
	ret = XMS_ctsLinkDevice(g_acsHandle, &devTrk->device, &devVoc->device, NULL);
	ret = XMS_ctsLinkDevice(g_acsHandle, &devVoc->device, &devTrk->device, NULL);

	TRACE("link trunk(%d/%d) to voice(%d/%d)\n",
		devTrk->device.m_s8ModuleID, devTrk->device.m_s16ChannelID,
		devVoc->device.m_s8ModuleID, devVoc->device.m_s16ChannelID);

	return ret;
}

RetCode_t unlinkDevice(XMS_VOIP_DEVICE *devIP, XMS_VOICE_DEVICE *devVoc)
{
	RetCode_t ret = XMS_ctsUnlinkDevice(g_acsHandle, &devIP->device, &devVoc->device, NULL);
	devIP->iVocDevice = -1;
	devVoc->iVoIPDevice = -1;

	TRACE("unlink voip(%d/%d) to voice(%d/%d)\n",
		devIP->device.m_s8ModuleID, devIP->device.m_s16ChannelID,
		devVoc->device.m_s8ModuleID, devVoc->device.m_s16ChannelID);

	return ret;
}

RetCode_t unlinkDevice(XMS_INTERFACE_DEVICE *devTrk, XMS_VOICE_DEVICE *devVoc)
{
	RetCode_t ret;
	ret = XMS_ctsUnlinkDevice(g_acsHandle, &devTrk->device, &devVoc->device, NULL);
	devTrk->iVocDevice = -1;
	ret = XMS_ctsUnlinkDevice(g_acsHandle, &devVoc->device, &devTrk->device, NULL);
	devVoc->iTrunkDevice = -1;

	TRACE("unlink trunk(%d/%d) to voice(%d/%d)\n",
		devTrk->device.m_s8ModuleID, devTrk->device.m_s16ChannelID,
		devVoc->device.m_s8ModuleID, devVoc->device.m_s16ChannelID);

	return ret;
}

//////////////////////////////////////////////////////////////////////////
// find registered sip client matching telephone-number or user-id
int getVoIPRegClient(const DJ_S8 *szRegTelNo, const DJ_S8 *szRegUserID)
{
	// search matching callee number in registration table
	for (int iReg = 0; iReg < MAX_VOIP_REG; ++iReg)
	{
		if ((szRegTelNo != NULL && strlen(szRegTelNo) > 0 && strcmp(g_ipRegSlot[iReg].addrRegClient.tszTelNo, szRegTelNo) == 0) ||
			(szRegUserID != NULL && strlen(szRegUserID) > 0 && strcmp(g_ipRegSlot[iReg].addrRegClient.tszTelNo, szRegUserID) == 0))
			return iReg;
	}

	return -1;
}

//////////////////////////////////////////////////////////////////////////
// XMS main event handler
DJ_Void XMSEventHandler(DJ_Void *u32EsrParam)
{
	if (g_pDlg == NULL)
		g_pDlg = (CXMSVoIPProxyDlg *)theApp.m_pMainWnd;

	Acs_Evt_t *pAcsEvt = (Acs_Evt_t *)u32EsrParam;

//	TRACE(_T("EvtType=%x\n"), pAcsEvt->m_s32EventType);

	// dispatch event by type
	switch (pAcsEvt->m_s32EventType)
	{
	case XMS_EVT_OPEN_STREAM:
		OnOpenStream(pAcsEvt);
		break;

	case XMS_EVT_QUERY_DEVICE:
		OnQueryDevice(pAcsEvt);
		break;

	case XMS_EVT_QUERY_DEVICE_END:
		OnQueryDeviceEnd(pAcsEvt);
		break;

	case XMS_EVT_OPEN_DEVICE:
		OnOpenDevice(pAcsEvt);
		break;

	case XMS_EVT_CLOSE_DEVICE:
		OnCloseDevice(pAcsEvt);
		break;

	case XMS_EVT_DEVICESTATE:
		OnDeviceState(pAcsEvt);
		break;

	case XMS_EVT_CALLOUT:
		OnCallOut(pAcsEvt);
		break;

	case XMS_EVT_CALLIN:
		OnCallIn(pAcsEvt);
		break;

	case XMS_EVT_ALERTCALL:
		OnAlertCall(pAcsEvt);
		break;

	case XMS_EVT_ANSWERCALL:
		OnAnswerCall(pAcsEvt);
		break;

	case XMS_EVT_CLEARCALL:
		OnClearCall(pAcsEvt);
		break;

	case XMS_EVT_LINKDEVICE:
		OnLinkDevice(pAcsEvt);
		break;

	case XMS_EVT_UNLINKDEVICE:
		OnUnlinkDevice(pAcsEvt);
		break;

	case XMS_EVT_PLAY:
		OnPlay(pAcsEvt);
		break;

	case XMS_EVT_RECVIODATA:
		OnRecvIOData(pAcsEvt);
		break;

	case XMS_EVT_JOINTOCONF:
		OnJoinConf(pAcsEvt);
		break;

	case XMS_EVT_GETPARAM:
		OnGetParam(pAcsEvt);
		break;
	case XMS_EVT_SET_MEDIAINFO:
		OnGetMediaInfo(pAcsEvt);
		break;

	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_OPEN_STREAM event handler
void OnOpenStream(Acs_Evt_t *pAcsEvt)
{
	TRACE(_T("XMS service opened (ret=%d)\n"), pAcsEvt->m_u32EsrParam);

	g_pDlg->GetDlgItem(IDC_BUTTON_INIT)->SetWindowText(_T("Close XMS System"));

	g_pDlg->GetDlgItem(IDC_BUTTON_INIT)->EnableWindow();
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_QUERY_DEVICE event handler
void OnQueryDevice(Acs_Evt_t *pAcsEvt)
{
	Acs_Dev_List_Head_t *pAcsDevList = (Acs_Dev_List_Head_t *)FetchEventData(pAcsEvt);

	TRACE(_T("Device[%02d][%02d] query returned %d\n"),
		pAcsDevList->m_s32ModuleID,
		pAcsDevList->m_s32DeviceMain,
		pAcsDevList->m_s32DeviceNum);

	if (g_pDlg->m_bAutoRtp && pAcsDevList->m_s32ModuleID != g_pDlg->m_iDSP)
		return;
	if ((!g_pDlg->m_bAutoRtp) && pAcsDevList->m_s32ModuleID != g_pDlg->m_iDSP && XMS_DEVMAIN_VOIP!=pAcsDevList->m_s32DeviceMain)
		return;

	int iDevice;
	DeviceID_t *pDevice = (DeviceID_t *)(pAcsDevList+1);

	// save all the capable devices here
	switch (pAcsDevList->m_s32DeviceMain)
	{
	case XMS_DEVMAIN_BOARD:
		for (iDevice = 0; iDevice < pAcsDevList->m_s32DeviceNum && g_iBoardDevNum < MAX_DEVICE_BOARD; ++iDevice)
		{
			g_deviceBoard[g_iBoardDevNum++] = pDevice[iDevice];
		}
		break;
	case XMS_DEVMAIN_VOIP:
		for (iDevice = 0; iDevice < pAcsDevList->m_s32DeviceNum && g_iVoIPDevNum < MAX_DEVICE_VOIP; ++iDevice)
		{
			g_deviceVoIP[g_iVoIPDevNum++].device = pDevice[iDevice];
		}
		break;
	case XMS_DEVMAIN_RTP:
		for (iDevice = 0; iDevice < pAcsDevList->m_s32DeviceNum && g_iRTPDevNum < MAX_DEVICE_VOIP; ++iDevice)
		{
			g_deviceRTP[g_iRTPDevNum++].device = pDevice[iDevice];
		}
		break;
	case XMS_DEVMAIN_VOICE:
		for (iDevice = 0; iDevice < pAcsDevList->m_s32DeviceNum && g_iVocDevNum < MAX_DEVICE_VOICE; ++iDevice)
		{
			g_deviceVoc[g_iVocDevNum++].device = pDevice[iDevice];
		}
		break;
	case XMS_DEVMAIN_INTERFACE_CH:
		for (iDevice = 0; iDevice < pAcsDevList->m_s32DeviceNum && g_iTrunkDevNum < MAX_DEVICE_INTERFACE; ++iDevice)
		{
			g_deviceTrunk[g_iTrunkDevNum++].device = pDevice[iDevice];
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_QUERY_DEVICE_END event handler
void OnQueryDeviceEnd(Acs_Evt_t *pAcsEvt)
{
	int iDevice;

	TRACE(_T("Device query end\n"));

	RetCode_t ret;

	// init device list
	g_pDlg->initIPList();

	g_iVocDevNum = min(g_iVocDevNum, g_iVoIPDevNum);

	// open all Board devices
	for ( iDevice = 0; iDevice < g_iBoardDevNum; ++iDevice)
	{
		ret = XMS_ctsOpenDevice(g_acsHandle, &g_deviceBoard[iDevice], NULL);
	}

	// open all IP devices
	for (iDevice = 0; iDevice < g_iVoIPDevNum; ++iDevice)
	{
		// opened already?
		if (g_deviceVoIP[iDevice].bOpened)
			continue;

		// send open device command
		if(g_pDlg->m_bAutoRtp)
			ret = XMS_ctsOpenDevice(g_acsHandle, &g_deviceVoIP[iDevice].device, NULL);
		else
		{
			VoIPOpenPrivate_t   voipOpenPrivate = {0};
			voipOpenPrivate.m_PrivateData.m_u32DataSize = sizeof(VoIPOpenPrivate_t);
			voipOpenPrivate.m_u8RtpMode	= 1;//g_u8RtpMode;
			ret = XMS_ctsOpenDevice(g_acsHandle, &g_deviceVoIP[iDevice].device, (PrivateData_t *)&voipOpenPrivate);
		}
	}

	// open all IP devices
	for (iDevice = 0; iDevice < g_iRTPDevNum; ++iDevice)
	{
		// opened already?
		if (g_deviceRTP[iDevice].bOpened)
			continue;
		
		// send open device command
		ret = XMS_ctsOpenDevice(g_acsHandle, &g_deviceRTP[iDevice].device, NULL);
	}

	// open all Voice devices
	for (iDevice = 0; iDevice < g_iVocDevNum; ++iDevice)
	{
		// opened already?
		if (g_deviceVoc[iDevice].bOpened)
			continue;

		// send open device comannd
		ret = XMS_ctsOpenDevice(g_acsHandle, &g_deviceVoc[iDevice].device, NULL);
	}

	// open all Interface devices
/*	for (iDevice = 0; iDevice < g_iTrunkDevNum; ++iDevice)
	{
		// opened already?
		if (g_deviceTrunk[iDevice].bOpened)
			continue;

		// send open device comannd
		ret = XMS_ctsOpenDevice(g_acsHandle, &g_deviceTrunk[iDevice].device, NULL);
	}*/
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_OPEN_DEVICE event handler
void OnOpenDevice(Acs_Evt_t *pAcsEvt)
{
	TRACE(_T("Device[%02d][%02d][%02d] opened (ret=%d)\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID,
		pAcsEvt->m_u32EsrParam);

	switch (pAcsEvt->m_DeviceID.m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
	case XMS_DEVMAIN_RTP:
	case XMS_DEVMAIN_VOICE:
	case XMS_DEVMAIN_INTERFACE_CH:
	case XMS_DEVMAIN_CONFERENCE:
		g_pDlg->enableDevice(&pAcsEvt->m_DeviceID);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_CLOSE_DEVICE event handler
void OnCloseDevice(Acs_Evt_t *pAcsEvt)
{
	TRACE(_T("Device[%02d][%02d][%02d] closed (ret=%d)\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID,
		pAcsEvt->m_u32EsrParam);

	switch (pAcsEvt->m_DeviceID.m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
	case XMS_DEVMAIN_VOICE:
	case XMS_DEVMAIN_INTERFACE_CH:
	case XMS_DEVMAIN_CONFERENCE:
		g_pDlg->enableDevice(&pAcsEvt->m_DeviceID, FALSE);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_DEVICESTATE event handler
void OnDeviceState(Acs_Evt_t *pAcsEvt)
{
	Acs_GeneralProc_Data *pDeviceState = (Acs_GeneralProc_Data *)FetchEventData(pAcsEvt);

	TRACE(_T("Device[%02d][%02d][%02d] state changed to 0x%08X\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID,
		pDeviceState->m_s32DeviceState);

	switch (pAcsEvt->m_DeviceID.m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
		{
			int iDeviceIP = mapDeviceItem(&pAcsEvt->m_DeviceID);
			OnDeviceStateVoIP(iDeviceIP, pDeviceState->m_s32DeviceState);
		}
		break;
	case XMS_DEVMAIN_INTERFACE_CH:
		{
			int iDeviceTrk = mapDeviceItem(&pAcsEvt->m_DeviceID);
			OnDeviceStateTrunk(iDeviceTrk, pDeviceState->m_s32DeviceState);
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// find and link with a free Voice Device for an VoIP Device
int initIPVoice(int iDeviceIP)
{
	if (!g_deviceVoIP[iDeviceIP].bOpened)
		return -1;
	
	if (g_deviceVoIP[iDeviceIP].iVocDevice != -1)
		return g_deviceVoIP[iDeviceIP].iVocDevice;

	for (int iDeviceVoc = 0; iDeviceVoc < g_iVocDevNum; ++iDeviceVoc)
	{
		if (g_deviceVoc[iDeviceVoc].bOpened &&
			g_deviceVoc[iDeviceVoc].device.m_s8ModuleID == g_deviceVoIP[iDeviceIP].device.m_s8ModuleID &&
			g_deviceVoc[iDeviceVoc].iTrunkDevice == -1 && g_deviceVoc[iDeviceVoc].iVoIPDevice == -1)
		{
			// send link device command
			RetCode_t ret;
			ret = linkDevice(&g_deviceVoIP[iDeviceIP], &g_deviceVoc[iDeviceVoc]);

			g_deviceVoIP[iDeviceIP].iVocDevice = iDeviceVoc;
			g_deviceVoc[iDeviceVoc].iVoIPDevice = iDeviceIP;

			return iDeviceVoc;
		}
	}

	return -1;
}

//////////////////////////////////////////////////////////////////////////
// find and link with a free Voice Device for an Interface Device
int initTrunkVoice(int iDeviceTrk)
{
	if (!g_deviceTrunk[iDeviceTrk].bOpened)
		return -1;
	
	if (g_deviceTrunk[iDeviceTrk].iVocDevice != -1)
		return g_deviceTrunk[iDeviceTrk].iVocDevice;

	for (int iDeviceVoc = 0; iDeviceVoc < g_iVocDevNum; ++iDeviceVoc)
	{
		if (g_deviceVoc[iDeviceVoc].bOpened &&
			g_deviceVoc[iDeviceVoc].device.m_s8ModuleID == g_deviceTrunk[iDeviceTrk].device.m_s8ModuleID &&
			g_deviceVoc[iDeviceVoc].iTrunkDevice == -1 && g_deviceVoc[iDeviceVoc].iVoIPDevice == -1)
		{
			// send link device command
			RetCode_t ret;
			ret = linkDevice(&g_deviceTrunk[iDeviceTrk], &g_deviceVoc[iDeviceVoc]);

			g_deviceTrunk[iDeviceTrk].iVocDevice = iDeviceVoc;
			g_deviceVoc[iDeviceVoc].iTrunkDevice = iDeviceTrk;

			return iDeviceVoc;
		}
	}

	return -1;
}

//////////////////////////////////////////////////////////////////////////
// Interface Device state change event handler
void OnDeviceStateTrunk(int iDeviceTrk, int iState)
{
	RetCode_t ret;

	g_deviceTrunk[iDeviceTrk].iState = iState;

	switch (iState)
	{
	case DCS_FREE:
		memset(&g_deviceTrunk[iDeviceTrk].szCallerNum, 0, sizeof(g_deviceTrunk[iDeviceTrk].szCallerNum));
		memset(&g_deviceTrunk[iDeviceTrk].szCalleeNum, 0, sizeof(g_deviceTrunk[iDeviceTrk].szCalleeNum));
		memset(&g_deviceTrunk[iDeviceTrk].szDtmf, 0, sizeof(g_deviceTrunk[iDeviceTrk].szDtmf));
		break;
	case DCS_CALLOUT:
	case DCS_CALLIN:
	case DCS_ALERTING:
		break;
	case DCS_CONNECT:
		{
			// if a VoIP Device is to be linked, link it
			int iDeviceIP = g_deviceTrunk[iDeviceTrk].iVoIPDevice;
			if (iDeviceIP != -1)
			{
				// Note: link with the Voice Device attached to the VoIP Device actually
				int iDeviceVoc = g_deviceVoIP[iDeviceIP].iVocDevice;
				if (iDeviceVoc != -1)
				{
					// send link device command
					ret = linkDevice(&g_deviceTrunk[iDeviceTrk], &g_deviceVoc[iDeviceVoc]);

//					g_deviceVoIP[iDeviceIP].iTrunkDevice = iDeviceTrk;
//					g_deviceVoIP[iDeviceIP].iVocDevice = iDeviceVoc;
				}
			}
			else
			{
				// find and link with a free Voice Device
				int iDeviceTrkVoc = initTrunkVoice(iDeviceTrk);
			}
		}
		break;
	case DCS_DISCONNECT:
		{
			// unlink Voice Device
			int iDeviceIP = g_deviceTrunk[iDeviceTrk].iVoIPDevice;
			if (iDeviceIP != -1)
			{
				int iDeviceVoc = g_deviceVoIP[iDeviceIP].iVocDevice;
				if (iDeviceVoc != -1)
				{
					ret = unlinkDevice(&g_deviceTrunk[iDeviceTrk], &g_deviceVoc[iDeviceVoc]);
					ret = unlinkDevice(&g_deviceVoIP[iDeviceIP], &g_deviceVoc[iDeviceVoc]);
				}
				else
				{
					iDeviceVoc = g_deviceTrunk[iDeviceTrk].iVocDevice;
					if (iDeviceVoc != -1)
					{
						// send unlink device command
						ret = unlinkDevice(&g_deviceTrunk[iDeviceTrk], &g_deviceVoc[iDeviceVoc]);
					}
				}
			}
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// VoIP Device state change event handler
void OnDeviceStateVoIP(int iDeviceIP, int iState)
{
//	RetCode_t ret;

	g_deviceVoIP[iDeviceIP].iState = iState;

	switch (iState)
	{
	case DCS_FREE:
//		g_deviceVoIP[iDeviceIP].iProtocol = 0;
//		memset(&g_deviceVoIP[iDeviceIP].addrRegClient, 0, sizeof(XMS_VOIP_ADDR));
		memset(&g_deviceVoIP[iDeviceIP].tszPeerTelNo, 0, sizeof(g_deviceVoIP[iDeviceIP].tszPeerTelNo));
		memset(&g_deviceVoIP[iDeviceIP].szDtmf, 0, sizeof(g_deviceVoIP[iDeviceIP].szDtmf));
		break;
	case DCS_CALLOUT:
		break;
	case DCS_CALLIN:
		break;
	case DCS_ALERTING:
		if(g_deviceVoIP[iDeviceIP].iTranferSrcDev!=-1)
		{
			//SendReferNotify(g_deviceVoIP[iDeviceIP].iTranferSrcDev, 180);
		}
		break;
	case DCS_CONNECT:
		{
/*			// find and link with a free Voice Device
			int iDeviceIPVoc = initIPVoice(iDeviceIP);

			// if an Interface Device is to be linked, link it
			int iDeviceTrk = g_deviceVoIP[iDeviceIP].iTrunkDevice;
			if (iDeviceTrk != -1)
			{
				int iDeviceTrkVoc = g_deviceTrunk[iDeviceTrk].iVocDevice;
				if (iDeviceTrkVoc != -1)
				{
					// unlink Interface Device with previous Voice Device
					ret = unlinkDevice(&g_deviceTrunk[iDeviceTrk], &g_deviceVoc[iDeviceTrkVoc]);
				}

				// Note: link with the Voice Device attached to the VoIP Device actually
				// send link device command
				ret = linkDevice(&g_deviceTrunk[iDeviceTrk], &g_deviceVoc[iDeviceIPVoc]);

//				g_deviceVoIP[iDeviceIP].iVocDevice = iDeviceVoc;
			}*/
		}
		break;
	case DCS_DISCONNECT:
		{
/*			// unlink Voice Device
			int iDeviceVoc = g_deviceVoIP[iDeviceIP].iVocDevice;
			if (iDeviceVoc != -1)
			{
				ret = unlinkDevice(&g_deviceVoIP[iDeviceIP], &g_deviceVoc[iDeviceVoc]);
			}

			// unlink Interface Device
			int iDeviceTrk = g_deviceVoIP[iDeviceIP].iTrunkDevice;
			if (iDeviceTrk != -1 && iDeviceVoc != -1)
			{
				// Note: unlink with the Voice Device attached to the Interface Device actually
				// send unlink device command
				ret = unlinkDevice(&g_deviceTrunk[iDeviceTrk], &g_deviceVoc[iDeviceVoc]);
			}*/
		}
		break;
	default:
		break;
	}

	// refresh VoIP Device list
	g_pDlg->refreshListIP(iDeviceIP);
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_CALLOUT event handler (local make call out returns)
void OnCallOut(Acs_Evt_t *pAcsEvt)
{
	Acs_CallControl_Data *pCallEvt = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);

	TRACE(_T("Device[%02d][%02d][%02d] called out (ret=%d)\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID,
		pCallEvt->m_s32AcsEvtErrCode);

	int iDeviceCallee = mapDeviceItem(&pAcsEvt->m_DeviceID);
	VoIPCallPrivate_t *paramVoIPCall = (VoIPCallPrivate_t *)&(pCallEvt->m_PrivData);

	// find orginal caller device
	int iDeviceCaller = g_deviceVoIP[iDeviceCallee].iPeerDevice;
	if (iDeviceCaller < 0)
		return;
	int iReferOrg = g_deviceVoIP[iDeviceCallee].iTranferSrcDev;
	Acs_VoIP_MediaInfo ptem = g_deviceVoIP[iDeviceCaller].mediaInfo;
	if (pCallEvt->m_s32AcsEvtState != 0)
	{
		// make call ok
		if(iReferOrg==-1)
		{
			if(!g_pDlg->m_bAutoRtp)
			{
				if( g_pDlg->m_bUseDspRtp )
				{
					// find a free call slot to call out
					Acs_VoIP_MediaInfo* pMediaInfo = &g_deviceVoIP[iDeviceCallee].mediaInfo;
					int iDeviceRtp = iDeviceCaller;
					SetRTPSession(&g_deviceRTP[iDeviceCallee].device, 1, pMediaInfo->payload_dtmf, pMediaInfo->payload_tone);
					DJ_U8 u8CodePayload	= 0;
					for(int i= 0;i< 10;i++ )
					{
						if( g_rtp_codec[i].u8CodecType == pMediaInfo->u8MediaCapList[0] )
						{
							u8CodePayload	= g_rtp_codec[i].u8PayloadType;
							break;
						}
					}
					SetRTPCodec(&g_deviceRTP[iDeviceCallee].device, pMediaInfo->u8AudioEnabled, pMediaInfo->u8MediaCapList[0], u8CodePayload, 0, 0, 0);
					SetRTPIP(&g_deviceRTP[iDeviceCallee].device, pMediaInfo->u8AudioEnabled, pMediaInfo->s8AudioAddress, pMediaInfo->u16AudioPort,
						pMediaInfo->u8VideoEnabled, pMediaInfo->s8VideoAddress, pMediaInfo->u16VideoPort);
					
					strcpy( pMediaInfo->s8AudioAddress, g_pDlg->m_strDspIp);
					if(g_pDlg->m_bDspBehindNat)
						pMediaInfo->u16AudioPort = iDeviceRtp*2+RTP_PORT_BASE(10000, g_pDlg->m_iDSP);
					else
						pMediaInfo->u16AudioPort = 10000+iDeviceRtp*2;//RTP_PORT_BASE(10000, m_rtp->GetID());
					pMediaInfo->u8VideoEnabled	= 0;
					pMediaInfo->u8MediaCapNum	= 1;
				}
			
				XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, 
					VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo),
					&g_deviceVoIP[iDeviceCallee].mediaInfo);
				g_deviceVoIP[iDeviceCallee].mediaInfo;
			}

			XMS_ctsAnswerCallIn(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, NULL);

			if(g_pDlg->m_bAutoRtp)
			{
				// link voice devices
				XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device,
					&g_deviceVoc[iDeviceCaller].device, NULL);
				XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device,
					&g_deviceVoc[iDeviceCallee].device, NULL);
				XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCaller].device,
					&g_deviceVoc[iDeviceCallee].device, NULL);
				XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCallee].device,
					&g_deviceVoc[iDeviceCaller].device, NULL);
			}
			else if(g_pDlg->m_bUseDspRtp)
			{
				XMS_ctsLinkDevice(g_acsHandle, &g_deviceRTP[iDeviceCaller].device,
					&g_deviceVoc[iDeviceCaller].device, NULL);
				XMS_ctsLinkDevice(g_acsHandle, &g_deviceRTP[iDeviceCallee].device,
					&g_deviceVoc[iDeviceCallee].device, NULL);
				XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCaller].device,
					&g_deviceVoc[iDeviceCallee].device, NULL);
				XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCallee].device,
					&g_deviceVoc[iDeviceCaller].device, NULL);
			}
/*			if(g_deviceVoIP[iDeviceCallee].iState==DCS_CONNECT 
				&& !g_pDlg->m_bAutoRtp && !g_pDlg->m_bUseDspRtp)
			{


				VoIPCallModifyPrivateEx_t paramVoIPCall1 = {0};
				VoIPCallModifyPrivateEx_t *PparamVoIPCall1 = &paramVoIPCall1;
				paramVoIPCall1.m_s32Protocol =  XMS_VOIP_PROTOCOL_SIP;
				paramVoIPCall1.m_u8MediaCapNum = 0;
				paramVoIPCall1.m_u8MediaCapNum = g_deviceVoIP[iDeviceCallee].mediaInfo.u8MediaCapNum;
				memcpy(PparamVoIPCall1->m_u8MediaCapList, g_deviceVoIP[iDeviceCallee].mediaInfo.u8MediaCapList, sizeof(PparamVoIPCall1->m_u8MediaCapList));
				paramVoIPCall1.u8MediaMode = 0;

				XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, XMS_IO_TYPE_VOIP_CALLMODIFY,
					sizeof(paramVoIPCall1), &paramVoIPCall1);


				XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device, 
				VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo),
				&ptem);
				paramVoIPCall1.m_u8MediaCapNum = ptem.u8MediaCapNum;
				memcpy(PparamVoIPCall1->m_u8MediaCapList, ptem.u8MediaCapList, sizeof(PparamVoIPCall1->m_u8MediaCapList));
				XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device, XMS_IO_TYPE_VOIP_CALLMODIFY,
					sizeof(paramVoIPCall1), &paramVoIPCall1);
			}*/
			g_deviceVoIP[iDeviceCaller].mediaInfo;
		}
		else if( iReferOrg>=0 )
		{
			// link voice devices

			if(g_pDlg->m_bAutoRtp || g_pDlg->m_bUseDspRtp)
			{
				XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCallee].device,
					&g_deviceVoc[iReferOrg].device, NULL);
				XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceVoc[iReferOrg].device,
						&g_deviceVoc[iDeviceCallee].device, NULL);
			}

			g_deviceVoIP[iReferOrg].iPeerDevice = -1;
			memset(g_deviceVoIP[iReferOrg].tszPeerTelNo, '\0', sizeof(g_deviceVoIP[iReferOrg].tszPeerTelNo));

			g_deviceVoIP[iDeviceCaller].iPeerDevice = iDeviceCallee;
			//memset(g_deviceVoIP[iDeviceCaller].tszPeerTelNo, '\0', sizeof(g_deviceVoIP[iDeviceCaller].tszPeerTelNo));

			if(!g_pDlg->m_bAutoRtp)
			{
				if( g_pDlg->m_bUseDspRtp )
				{
					// find a free call slot to call out
					Acs_VoIP_MediaInfo* pMediaInfo = &g_deviceVoIP[iDeviceCallee].mediaInfo;
					int iDeviceRtp = iDeviceCaller;
					SetRTPSession(&g_deviceRTP[iDeviceCallee].device, 1, pMediaInfo->payload_dtmf, pMediaInfo->payload_tone);
					DJ_U8 u8CodePayload	= 0;
					for(int i= 0;i< 10;i++ )
					{
						if( g_rtp_codec[i].u8CodecType == pMediaInfo->u8MediaCapList[0] )
						{
							u8CodePayload	= g_rtp_codec[i].u8PayloadType;
							break;
						}
					}
					SetRTPCodec(&g_deviceRTP[iDeviceCallee].device, pMediaInfo->u8AudioEnabled, pMediaInfo->u8MediaCapList[0], u8CodePayload, 0, 0, 0);
					SetRTPIP(&g_deviceRTP[iDeviceCallee].device, pMediaInfo->u8AudioEnabled, pMediaInfo->s8AudioAddress, pMediaInfo->u16AudioPort,
						pMediaInfo->u8VideoEnabled, pMediaInfo->s8VideoAddress, pMediaInfo->u16VideoPort);

					strcpy( pMediaInfo->s8AudioAddress, g_pDlg->m_strDspIp);
					if(g_pDlg->m_bDspBehindNat)
						pMediaInfo->u16AudioPort = iDeviceRtp*2+RTP_PORT_BASE(10000, g_pDlg->m_iDSP);
					else
						pMediaInfo->u16AudioPort = 10000+iDeviceRtp*2;//RTP_PORT_BASE(10000, m_rtp->GetID());
					pMediaInfo->u8VideoEnabled	= 0;
					pMediaInfo->u8MediaCapNum	= 1;
				}

				XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, 
					VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo),
					&g_deviceVoIP[iDeviceCallee].mediaInfo);

			}


			SendReferNotify(iReferOrg, 200);



			VoIPCallModifyPrivate_t paramVoIPCall1 = {0};
			VoIPCallModifyPrivate_t *PparamVoIPCall1 = &paramVoIPCall1;
			paramVoIPCall1.m_PrivateData.m_u32DataSize = sizeof(VoIPCallModifyPrivate_t);
	

			paramVoIPCall1.m_u8MediaCapNum = 0;
			//paramVoIPCall1.m_u8MediaCapNum = paramVoIPCall->m_u8MediaCapNum;
			//memcpy(PparamVoIPCall1->m_u8MediaCapList, paramVoIPCall->m_u8MediaCapList, sizeof(PparamVoIPCall1->m_u8MediaCapList));
			paramVoIPCall1.u8MediaMode = 0;
			
			XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, XMS_IO_TYPE_VOIP_CALLMODIFY,
					sizeof(paramVoIPCall1), &paramVoIPCall1);



			if(g_pDlg->m_bAutoRtp)
			{
				XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device,
					&g_deviceVoc[iDeviceCallee].device, NULL);
			}
			else if(g_pDlg->m_bUseDspRtp)
			{
				XMS_ctsLinkDevice(g_acsHandle, &g_deviceRTP[iDeviceCallee].device,
					&g_deviceVoc[iDeviceCallee].device, NULL);
			}
			XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCaller].device,
				&g_deviceVoc[iDeviceCallee].device, NULL);
			XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCallee].device,
				&g_deviceVoc[iDeviceCaller].device, NULL);

			g_deviceVoIP[iDeviceCallee].iTranferSrcDev = -1;
		}
		else if( iReferOrg==-2 )
		{
				VoIPCallModifyPrivate_t paramVoIPCall1 = {0};
				VoIPCallModifyPrivate_t *PparamVoIPCall1 = &paramVoIPCall1;
				paramVoIPCall1.m_u8MediaCapNum = 0;
				paramVoIPCall1.m_u8MediaCapNum = g_deviceVoIP[iDeviceCallee].mediaInfo.u8MediaCapNum;
				memcpy(PparamVoIPCall1->m_u8MediaCapList, g_deviceVoIP[iDeviceCallee].mediaInfo.u8MediaCapList, sizeof(PparamVoIPCall1->m_u8MediaCapList));
				paramVoIPCall1.u8MediaMode = 0;
				if(!g_pDlg->m_bAutoRtp)
				{
					if( g_pDlg->m_bUseDspRtp )
					{
						// find a free call slot to call out
						Acs_VoIP_MediaInfo* pMediaInfo = &g_deviceVoIP[iDeviceCallee].mediaInfo;
						int iDeviceRtp = iDeviceCaller;
						SetRTPSession(&g_deviceRTP[iDeviceCallee].device, 1, pMediaInfo->payload_dtmf, pMediaInfo->payload_tone);
						DJ_U8 u8CodePayload	= 0;
						for(int i= 0;i< 10;i++ )
						{
							if( g_rtp_codec[i].u8CodecType == pMediaInfo->u8MediaCapList[0] )
							{
								u8CodePayload	= g_rtp_codec[i].u8PayloadType;
								break;
							}
						}
						SetRTPCodec(&g_deviceRTP[iDeviceCallee].device, pMediaInfo->u8AudioEnabled, pMediaInfo->u8MediaCapList[0], u8CodePayload, 0, 0, 0);
						SetRTPIP(&g_deviceRTP[iDeviceCallee].device, pMediaInfo->u8AudioEnabled, pMediaInfo->s8AudioAddress, pMediaInfo->u16AudioPort,
							pMediaInfo->u8VideoEnabled, pMediaInfo->s8VideoAddress, pMediaInfo->u16VideoPort);
						
						strcpy( pMediaInfo->s8AudioAddress, g_pDlg->m_strDspIp);
						if(g_pDlg->m_bDspBehindNat)
							pMediaInfo->u16AudioPort = iDeviceRtp*2+RTP_PORT_BASE(10000, g_pDlg->m_iDSP);
						else
							pMediaInfo->u16AudioPort = 10000+iDeviceRtp*2;//RTP_PORT_BASE(10000, m_rtp->GetID());
						pMediaInfo->u8VideoEnabled	= 0;
						pMediaInfo->u8MediaCapNum	= 1;
					}
				
					XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, 
						VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo),
						&g_deviceVoIP[iDeviceCallee].mediaInfo);
					g_deviceVoIP[iDeviceCallee].mediaInfo;
				}
/*				if( !g_pDlg->m_bAutoRtp && !g_pDlg->m_bUseDspRtp)
				{
					XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, 
						VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo),
						&g_deviceVoIP[iDeviceCallee].mediaInfo);
				}*/
				XMS_ctsAnswerCallIn(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, NULL);

				XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, XMS_IO_TYPE_VOIP_CALLMODIFY,
					sizeof(paramVoIPCall1), &paramVoIPCall1);

				if( !g_pDlg->m_bAutoRtp && !g_pDlg->m_bUseDspRtp)
				{
					XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device, 
					VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo),
					&ptem);
					paramVoIPCall1.m_u8MediaCapNum = ptem.u8MediaCapNum;
					memcpy(PparamVoIPCall1->m_u8MediaCapList, ptem.u8MediaCapList, sizeof(PparamVoIPCall1->m_u8MediaCapList));
					XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device, XMS_IO_TYPE_VOIP_CALLMODIFY,
						sizeof(paramVoIPCall1), &paramVoIPCall1);
				}

				if(g_pDlg->m_bAutoRtp)
				{
					XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device,
						&g_deviceVoc[iDeviceCallee].device, NULL);
				}
				else if(g_pDlg->m_bUseDspRtp)
				{
					XMS_ctsLinkDevice(g_acsHandle, &g_deviceRTP[iDeviceCallee].device,
						&g_deviceVoc[iDeviceCallee].device, NULL);
				}
				XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCaller].device,
					&g_deviceVoc[iDeviceCallee].device, NULL);
				XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCallee].device,
					&g_deviceVoc[iDeviceCaller].device, NULL);

				g_deviceVoIP[iDeviceCallee].iTranferSrcDev = -1;
		}
	}
	else
	{
		// make call fail
		if(iReferOrg==-1)
		{
			XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, 0, NULL);

			resetDeviceVoIP(iDeviceCaller);
			resetDeviceVoIP(iDeviceCallee);
			g_pDlg->refreshListIP(iDeviceCaller);
			g_pDlg->refreshListIP(iDeviceCallee);
			if((!g_pDlg->m_bAutoRtp) && g_pDlg->m_bUseDspRtp)
			{
				resetDeviceRTP(iDeviceCaller);
				resetDeviceRTP(iDeviceCallee);
			}
		}
		else
		{
			SendReferNotify(iReferOrg, 403);
			resetDeviceVoIP(iDeviceCallee);
			g_pDlg->refreshListIP(iDeviceCallee);
			if((!g_pDlg->m_bAutoRtp) && g_pDlg->m_bUseDspRtp)
			{
				resetDeviceRTP(iDeviceCallee);
			}

// 			g_deviceVoIP[iDeviceCallee].iTranferSrcDev = -1;
// 			XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, 0, NULL);
// 			
// 			resetDeviceVoIP(iDeviceCaller);
// 			resetDeviceVoIP(iDeviceCallee);
// 			g_pDlg->refreshListIP(iDeviceCaller);
// 			g_pDlg->refreshListIP(iDeviceCallee);
		}
	}
}

static tagRouteItem* findRoute(const char* strCallee)
{
	int i;
	int len = strlen(strCallee);
	for(std::list<tagRouteItem*>::iterator iter=g_lsRoute.begin(); iter!=g_lsRoute.end(); ++iter)
	{
		struct tagRouteItem* temproute = *iter;
		if(len!=temproute->strCalleeHead.GetLength())
			continue;
		
		for( i=0; i<len; ++i)
		{
			if(temproute->strCalleeHead[i]=='*' || temproute->strCalleeHead[i]=='X' || temproute->strCalleeHead[i]=='x')
				continue;
			if(strCallee[i]!=temproute->strCalleeHead[i])
				break;
		}
		if(i>=len)
			return temproute;
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_CALLIN event handler (remote call incoming)
void OnCallIn(Acs_Evt_t *pAcsEvt)
{
	int iDeviceCallee;

	Acs_CallControl_Data * pCallEvt = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);

	TRACE(_T("Device[%02d][%02d][%02d] incoming call\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID);

	switch (pAcsEvt->m_DeviceID.m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
		{
			VoIPCallPrivate_t *paramVoIPCall = (VoIPCallPrivate_t *)&(pCallEvt->m_PrivData);
			Acs_VoIP_Call_Diversion_Info divInfo;
			memset(&divInfo, 0, sizeof(Acs_VoIP_Call_Diversion_Info));

			TRACE("paramVoIPCall->m_s32Protocol=%d\n", paramVoIPCall->m_s32Protocol);
			TRACE("               m_s8CallerUserID=%s\n", paramVoIPCall->m_s8CallerUserID);
			TRACE("               m_s8CallerAddress=%s\n", paramVoIPCall->m_s8CallerAddress);
			TRACE("               m_s32CallerPort=%d\n", paramVoIPCall->m_s32CallerPort);
			TRACE("               m_s8CalleeUserID=%s\n", paramVoIPCall->m_s8CalleeUserID);
			TRACE("               m_s8CalleeAddress=%s\n", paramVoIPCall->m_s8CalleeAddress);
			TRACE("               m_s32CalleePort=%d\n", paramVoIPCall->m_s32CalleePort);
			TRACE("pCallEvt->m_s8CalledNum=%s\n", pCallEvt->m_s8CalledNum);
			TRACE("          m_s8CallingNum=%s\n", pCallEvt->m_s8CallingNum);

			int iDeviceCaller = mapDeviceItem(&pAcsEvt->m_DeviceID);
			XMS_ctsGetParam(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, VOIP_PARAM_CALL_DIVERSION_INFO, sizeof(Acs_VoIP_Call_Diversion_Info), &divInfo);

			int iReg = -1;
			if (g_pDlg->m_bInteractive)
			{
				int iReg = getVoIPRegClient(pCallEvt->m_s8CalledNum, paramVoIPCall->m_s8CalleeUserID);
				if (iReg < 0)
				{
					XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, 0, NULL);
					return;
				}
			}

			// find a free call slot to call out
			for ( iDeviceCallee = 0; iDeviceCallee < g_iVoIPDevNum; ++iDeviceCallee)
			{
				if (g_deviceVoIP[iDeviceCallee].iState == DCS_FREE)
					break;
			}
			if (iDeviceCallee >= g_iVoIPDevNum)
				return;

			// update caller info
			g_deviceVoIP[iDeviceCaller].iProtocol = paramVoIPCall->m_s32Protocol;
			strcpy(g_deviceVoIP[iDeviceCaller].tszPeerTelNo, pCallEvt->m_s8CalledNum);
			g_deviceVoIP[iDeviceCaller].iPeerDevice = iDeviceCallee;
			g_pDlg->refreshListIP(iDeviceCaller);

			paramVoIPCall->m_PrivateData.m_u32DataSize = sizeof(VoIPCallPrivate_t);
			if (g_pDlg->m_bInteractive)
				paramVoIPCall->m_s32Protocol = g_ipRegSlot[iReg].iProtocol;

			memset(paramVoIPCall->m_s8CallerAddress, 0, sizeof(paramVoIPCall->m_s8CallerAddress));
			paramVoIPCall->m_s32CallerPort = 0;

			if (g_pDlg->m_bInteractive)
			{
				strcpy(paramVoIPCall->m_s8CalleeAddress, g_ipRegSlot[iReg].addrRegClient.tszAddr);
				paramVoIPCall->m_s32CalleePort = g_ipRegSlot[iReg].addrRegClient.port;
				strcpy(paramVoIPCall->m_s8CalleeUserID, g_ipRegSlot[iReg].addrRegClient.tszUserID);
			}

			tagRouteItem* route = NULL;
			if (!g_pDlg->m_bInteractive)
			{
				route = findRoute(pCallEvt->m_s8CalledNum);
				if(route==NULL)
				{
					// clear callee address, cause keygoe to find the REAL callee address
					memset(paramVoIPCall->m_s8CalleeAddress, 0, sizeof(paramVoIPCall->m_s8CalleeAddress));
					paramVoIPCall->m_s32CalleePort = 0;
				}
				else
				{
					TRACE("Find route=(addr=%s port=%d user=%s password=%s callee=%s)\n", route->strAddr, route->uPort, route->strUserName, route->strPassword, route->strCalleeHead);
					strcpy(paramVoIPCall->m_s8CalleeAddress, route->strAddr);
					paramVoIPCall->m_s32CalleePort = route->uPort;
				}
			}

			// update callee info
			g_deviceVoIP[iDeviceCallee].iProtocol = paramVoIPCall->m_s32Protocol;
			strcpy(g_deviceVoIP[iDeviceCallee].tszPeerTelNo, pCallEvt->m_s8CallingNum);
			g_deviceVoIP[iDeviceCallee].iPeerDevice = iDeviceCaller;
			g_pDlg->refreshListIP(iDeviceCallee);

			if(!g_pDlg->m_bAutoRtp)
			{
				if( g_pDlg->m_bUseDspRtp )
				{
					// find a free call slot to call out
					Acs_VoIP_MediaInfo* pMediaInfo = &g_deviceVoIP[iDeviceCaller].mediaInfo;
					int iDeviceRtp = iDeviceCallee;
					SetRTPSession(&g_deviceRTP[iDeviceCaller].device, 1, pMediaInfo->payload_dtmf, pMediaInfo->payload_tone);
					DJ_U8 u8CodePayload	= 0;
					for(int i= 0;i< 10;i++ )
					{
						if( g_rtp_codec[i].u8CodecType == pMediaInfo->u8MediaCapList[0] )
						{
							u8CodePayload	= g_rtp_codec[i].u8PayloadType;
							break;
						}
					}
					SetRTPCodec(&g_deviceRTP[iDeviceCaller].device, pMediaInfo->u8AudioEnabled, pMediaInfo->u8MediaCapList[0], u8CodePayload, 0, 0, 0);
					SetRTPIP(&g_deviceRTP[iDeviceCaller].device, pMediaInfo->u8AudioEnabled, pMediaInfo->s8AudioAddress, pMediaInfo->u16AudioPort,
						pMediaInfo->u8VideoEnabled, pMediaInfo->s8VideoAddress, pMediaInfo->u16VideoPort);
					
					strcpy( pMediaInfo->s8AudioAddress, g_pDlg->m_strDspIp);
					if(g_pDlg->m_bDspBehindNat)
						pMediaInfo->u16AudioPort = iDeviceRtp*2+RTP_PORT_BASE(10000, g_pDlg->m_iDSP);
					else
						pMediaInfo->u16AudioPort = 10000+iDeviceRtp*2;//RTP_PORT_BASE(10000, m_rtp->GetID());
					pMediaInfo->u8VideoEnabled	= 0;
					pMediaInfo->u8MediaCapNum	= 1;
				}
				XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device, 
					VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo), 
					&g_deviceVoIP[iDeviceCaller].mediaInfo);
				g_deviceVoIP[iDeviceCaller].mediaInfo;
			}

			XMS_ctsMakeCallOut(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device,
				pCallEvt->m_s8CallingNum, pCallEvt->m_s8CalledNum,
				(PrivateData_t *)paramVoIPCall);
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_ALERTCALL event handler (received remote alert signaling (H.323: Q931 alerting; SIP: 1xx msg))
void OnAlertCall(Acs_Evt_t *pAcsEvt)
{
	Acs_CallControl_Data *pCallEvt = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);
	int iDevice = mapDeviceItem(&pAcsEvt->m_DeviceID);
	int iPeerDevice = g_deviceVoIP[iDevice].iPeerDevice;

	TRACE(_T("Device[%02d][%02d][%02d] call alerted (ret=%d)"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID,
		pCallEvt->m_s32AcsEvtErrCode);
	TRACE("iDevice=%d state=%d iPeerDevice=%d state=%d iTranferSrcDev=%d\n", 
		iDevice, g_deviceVoIP[iDevice].iState,
		iPeerDevice, g_deviceVoIP[iPeerDevice].iState,
		g_deviceVoIP[iDevice].iTranferSrcDev);
	if(pCallEvt->m_s32AcsEvtErrCode>=180 && pCallEvt->m_s32AcsEvtErrCode<=183)
	{
		if(g_deviceVoIP[iPeerDevice].iState == DCS_CALLIN || g_deviceVoIP[iPeerDevice].iState == DCS_ALERTING)
		{
			VoIPAlertPrivateEx_t priData;
			memset(&priData, 0, sizeof(priData));
			priData.m_PrivateData.m_u32DataSize = sizeof(priData);
			priData.u16AlertCode=pCallEvt->m_s32AcsEvtErrCode;
			XMS_ctsAlertCall(g_acsHandle, &g_deviceVoIP[iPeerDevice].device, (PrivateData_t*)&priData);
			
			//support old version alert call sample
// 			VoIPAlertPrivate_t priData;
// 			memset(&priData, 0, sizeof(priData));
// 			priData.m_PrivateData.m_u32DataSize = sizeof(priData);
// 			XMS_ctsAlertCall(g_acsHandle, &g_deviceVoIP[iPeerDevice].device, (PrivateData_t*)&priData);
		}
		if(g_deviceVoIP[iDevice].iTranferSrcDev>=0)
		{
			SendReferNotify(g_deviceVoIP[iDevice].iTranferSrcDev, pCallEvt->m_s32AcsEvtErrCode);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_ANSWERCALL event handler (local answer call returns)
void OnAnswerCall(Acs_Evt_t *pAcsEvt)
{
	Acs_CallControl_Data *pCallEvt = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);

	TRACE(_T("Device[%02d][%02d][%02d] call answered (ret=%d)\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID,
		pCallEvt->m_s32AcsEvtErrCode);
/*	if (pCallEvt->m_s32AcsEvtState != 0)
	{
		int iDeviceCaller = mapDeviceItem(&pAcsEvt->m_DeviceID);
		int iDeviceCallee = g_deviceVoIP[iDeviceCaller].iPeerDevice;

		XMS_ctsAnswerCallIn(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device, NULL);
		::AfxMessageBox("answercall");
	}
*/

}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_CLEARCALL event handler (call dropped by local or remote)
void OnClearCall(Acs_Evt_t *pAcsEvt)
{
	Acs_CallControl_Data *pCallEvt = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);

	TRACE(_T("Device[%02d][%02d][%02d] call cleared (ret=%d)\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID,
		pCallEvt->m_s32AcsEvtErrCode);

	RetCode_t ret;

	switch (pAcsEvt->m_DeviceID.m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
		{
			int iDevice = mapDeviceItem(&pAcsEvt->m_DeviceID);

			// find peer device
			int iDevicePeer = g_deviceVoIP[iDevice].iPeerDevice;
			if (iDevicePeer >= 0)
			{
				if(g_pDlg->m_bAutoRtp || g_pDlg->m_bUseDspRtp)
				{
					XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceVoc[iDevice].device,
						&g_deviceVoc[iDevicePeer].device, NULL);
					XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceVoc[iDevicePeer].device,
						&g_deviceVoc[iDevice].device, NULL);
				}

				ret = XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[iDevicePeer].device, 0, NULL);

				memset(g_deviceVoIP[iDevicePeer].tszPeerTelNo, 0, sizeof(g_deviceVoIP[iDevicePeer].tszPeerTelNo));
				g_deviceVoIP[iDevicePeer].iPeerDevice = -1;
			}

			if(g_pDlg->m_bAutoRtp)
			{
				// unlink voice devices
				XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceVoIP[iDevice].device,
					&g_deviceVoc[iDevice].device, NULL);
			}
			else if(g_pDlg->m_bUseDspRtp)
			{
				XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceRTP[iDevice].device,
					&g_deviceVoc[iDevice].device, NULL);
				//SetRTPCodec(&g_deviceRTP[iDevice].device, FALSE, 0, 0, FALSE, 0, 0);
				//SetRTPIP(&g_deviceRTP[iDevice].device, FALSE, "", 0, FALSE, "", 0);
				SetRTPSession(&g_deviceRTP[iDevice].device, FALSE, 0, 0);
			}

			resetDeviceVoIP(iDevice);
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_LINKDEVICE event handler
void OnLinkDevice(Acs_Evt_t *pAcsEvt)
{
	TRACE(_T("Device[%02d][%02d][%02d] linked\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID);

/*	switch (pAcsEvt->m_DeviceID.m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
		{
			// VoIP Device linked with Interface Device
			int iDeviceIP = mapDeviceItem(&pAcsEvt->m_DeviceID);

			g_pDlg->refreshListIP(iDeviceIP);
		}
		break;
	}*/
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_UNLINKDEVICE event handler
void OnUnlinkDevice(Acs_Evt_t *pAcsEvt)
{
	TRACE(_T("Device[%02d][%02d][%02d] unlinked\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID);

	switch (pAcsEvt->m_DeviceID.m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
		{
			// VoIP Device unlinked with Interface Device
			int iDeviceIP = mapDeviceItem(&pAcsEvt->m_DeviceID);
			g_pDlg->refreshListIP(iDeviceIP);
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_PLAY event handler (play stops)
void OnPlay(Acs_Evt_t *pAcsEvt)
{
	TRACE(_T("Device[%02d][%02d][%02d] play voice stopped\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID);

	if (pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_VOICE)
	{
		int iDevice = mapDeviceItem(&pAcsEvt->m_DeviceID);
		memset(&g_deviceVoc[iDevice].tszPlayFile, 0, sizeof(g_deviceVoc[iDevice].tszPlayFile));
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_RECVIODATA event handler (H.245 UserInputIndication/SIP INFO/RFC 2833 DTMF)
void OnRecvIOData(Acs_Evt_t *pAcsEvt)
{
	TRACE(_T("Device[%02d][%02d][%02d] receive IO Data\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID);

	switch (pAcsEvt->m_DeviceID.m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
		{
			int iDeviceIP = mapDeviceItem(&pAcsEvt->m_DeviceID);
			OnRecvIODataVoIP(iDeviceIP, pAcsEvt);
		}
		break;

	case XMS_DEVMAIN_VOICE:
		{
			int iDeviceVoc = mapDeviceItem(&pAcsEvt->m_DeviceID);
			OnRecvIODataVoice(iDeviceVoc, pAcsEvt);
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// VoIP Device IO Data event handler
// (H.245 UserInputIndication/SIP INFO/RFC 2833 DTMF)
void OnRecvIODataVoIP(int iDeviceIP, Acs_Evt_t *pAcsEvt)
{
	int iDtmfLen = strlen(g_deviceVoIP[iDeviceIP].szDtmf);
	if (iDtmfLen >= sizeof(g_deviceVoIP[iDeviceIP].szDtmf)-1)
	{
		memset(g_deviceVoIP[iDeviceIP].szDtmf, 0, sizeof(g_deviceVoIP[iDeviceIP].szDtmf));
		iDtmfLen = 0;
	}

	char dtmf = '?';

	Acs_IO_Data *pIOEvt = (Acs_IO_Data *)FetchEventData(pAcsEvt);

	switch (pIOEvt->m_u16IoType)
	{
	case XMS_IO_TYPE_VOIP_OPTIONNOTIFY:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_OPTIONNOTIFY))
		{
			Acs_VoIP_OPTIONNOTIFY *pOption=(Acs_VoIP_OPTIONNOTIFY *)FetchIOData(pAcsEvt);
			if( pOption->m_s8Reason == 8 )
//				::AfxMessageBox(pOption->m_s8CalleeAddress);
			{
			}
//			::AfxMessageBox(pOption->m_s8CalleeAddress);

		}
	case XMS_IO_TYPE_VOIP_SIPREG:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_SIPREG))
		{
			Acs_VoIP_SIPREG *pSipReg=(Acs_VoIP_SIPREG *)FetchIOData(pAcsEvt);
			
//			::AfxMessageBox(pSipReg->m_s8TelNo);
//			::AfxMessageBox(pSipReg->m_s8Username);
		}
		break;
	case XMS_IO_TYPE_VOIP_SIPUNREG:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_SIPREG))
		{
			Acs_VoIP_SIPREG *pSipReg=(Acs_VoIP_SIPREG *)FetchIOData(pAcsEvt);
			
//			::AfxMessageBox(pSipReg->m_s8TelNo);
//			::AfxMessageBox(pSipReg->m_s8Username);
		}
		break;
	case XMS_IO_TYPE_VOIP_REGREQUEST:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_REGSTATE))
		{
			// check client's info
			Acs_VoIP_REGSTATE *pRegRequest = (Acs_VoIP_REGSTATE *)FetchIOData(pAcsEvt);
			TRACE(_T("Client registrates from: \"%s\" %s@%s:%d\n"),
				pRegRequest->m_s8UserID, pRegRequest->m_s8TelNo, pRegRequest->m_s8Address, pRegRequest->m_u16Port);

			// response to registration
			// if authentication is disabled,
			//   set Acs_VoIP_REGRESP::m_u8Granted to 0/1 to grant/disgrant registration
			// if authentication is enabled,
			//   set Acs_VoIP_REGRESP::m_u8Granted to 0, and fill Acs_VoIP_REGRESP::m_s8Password to authenticate,
			//   or
			//   set Acs_VoIP_REGRESP::m_u8Granted to 0, and leave Acs_VoIP_REGRESP::m_s8Password empty to disgrant registration,
			//   or
			//   set Acs_VoIP_REGRESP::m_u8Granted to 1 to grant registration without authenticating.
			Acs_VoIP_REGRESP regResponse = {0};
			regResponse.m_u16SlotID = pRegRequest->m_u16SlotID;
			regResponse.m_u8Granted = 1;
//			strcpy(regResponse.m_s8Password, "passwd");
			XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDeviceIP].device, XMS_IO_TYPE_VOIP_REGRESPONSE,
				sizeof(regResponse), &regResponse);
		}
		break;
	case XMS_IO_TYPE_VOIP_REGSTATE:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_REGSTATE))
		{
			Acs_VoIP_REGSTATE *pRegState = (Acs_VoIP_REGSTATE *)FetchIOData(pAcsEvt);
			if (pRegState->m_u16SlotID < MAX_VOIP_REG)
			{
				DJ_U16 u16SlotID = pRegState->m_u16SlotID;
				if (pRegState->m_u8State)
				{
/*					strcpy(g_deviceVoIP[iDeviceIP].addrRegClient.tszTelNo, pRegState->m_s8TelNo);
					strcpy(g_deviceVoIP[iDeviceIP].addrRegClient.tszUserID, pRegState->m_s8UserID);
					strcpy(g_deviceVoIP[iDeviceIP].addrRegClient.tszAddr, pRegState->m_s8Address);
					g_deviceVoIP[iDeviceIP].addrRegClient.port = pRegState->m_u16Port;
					g_deviceVoIP[iDeviceIP].iProtocol = pRegState->m_u8Protocol;*/
					strcpy(g_ipRegSlot[u16SlotID].addrRegClient.tszTelNo, pRegState->m_s8TelNo);
					strcpy(g_ipRegSlot[u16SlotID].addrRegClient.tszUserID, pRegState->m_s8UserID);
					strcpy(g_ipRegSlot[u16SlotID].addrRegClient.tszAddr, pRegState->m_s8Address);
					g_ipRegSlot[u16SlotID].addrRegClient.port = pRegState->m_u16Port;
					g_ipRegSlot[u16SlotID].iProtocol = pRegState->m_u8Protocol;
				}
				else
				{
//					memset(&g_deviceVoIP[iDeviceIP].addrRegClient, 0, sizeof(g_deviceVoIP[iDeviceIP].addrRegClient));
//					g_deviceVoIP[iDeviceIP].iProtocol = 0;
					memset(&g_ipRegSlot[u16SlotID].addrRegClient, 0, sizeof(g_ipRegSlot[u16SlotID].addrRegClient));
					g_ipRegSlot[u16SlotID].iProtocol = 0;
				}

				g_pDlg->refreshListReg(u16SlotID);
			}
		}
		break;

	case XMS_IO_TYPE_VOIP_H245UII:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_H245UII))
		{
			Acs_VoIP_H245UII *h245Uii = (Acs_VoIP_H245UII *)FetchIOData(pAcsEvt);
			//dtmf = h245Uii->m_s8Signal;
			if (g_deviceVoIP[iDeviceIP].iPeerDevice != -1)
			{
				XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[g_deviceVoIP[iDeviceIP].iPeerDevice].device,
					XMS_IO_TYPE_VOIP_H245UII, sizeof(*h245Uii), h245Uii);
			}
		}
		break;
	case XMS_IO_TYPE_VOIP_SIPINFO:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_SIPINFO))
		{
			Acs_VoIP_SIPINFO *sipInfo = (Acs_VoIP_SIPINFO *)FetchIOData(pAcsEvt);
			//if (strcmp(sipInfo->m_s8ContentType, "application/dtmf") == 0)
			//	sscanf(sipInfo->m_s8Body, "dtmf=%c", &dtmf);
			if (g_deviceVoIP[iDeviceIP].iPeerDevice != -1)
			{
				XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[g_deviceVoIP[iDeviceIP].iPeerDevice].device,
					XMS_IO_TYPE_VOIP_SIPINFO, sizeof(*sipInfo), sipInfo);
			}
		}
		break;
	case XMS_IO_TYPE_VOIP_RTPDTMF:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_RTPDTMF))
		{
			Acs_VoIP_RTPDTMF *rtpDtmf = (Acs_VoIP_RTPDTMF *)FetchIOData(pAcsEvt);
			//dtmf = rtpDtmf->m_s8EventChar;
			if (g_deviceVoIP[iDeviceIP].iPeerDevice != -1)
			{
				XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[g_deviceVoIP[iDeviceIP].iPeerDevice].device,
					XMS_IO_TYPE_VOIP_RTPDTMF, sizeof(*rtpDtmf), rtpDtmf);
			}
		}
		break;
	case XMS_IO_TYPE_VOIP_REFER:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_Refer))
		{
			Acs_VoIP_Refer *pRefer = (Acs_VoIP_Refer *)FetchIOData(pAcsEvt);
			if(pRefer->m_u8ReferedToUnitId==0)	//UCT
			{
				OnUnattandCallTransfer(iDeviceIP, pRefer);
			}
			else
			{
				OnAttandCallTransfer(iDeviceIP, pRefer);
			}
		}
		break;
	case XMS_IO_TYPE_VOIP_CALLMODIFY:
		if (pIOEvt->m_u16IoDataLen >= sizeof(VoIPCallModifyPrivate_t))
		{
			VoIPCallModifyPrivate_t *pCallInfo = (VoIPCallModifyPrivate_t *)FetchIOData(pAcsEvt);
			TRACE("Call[%d] modified, and Media connection mode=%d\n",iDeviceIP,pCallInfo->u8MediaMode);
			 int iDevice=g_deviceVoIP[iDeviceIP].iPeerDevice;
//			if( 1 == pCallInfo->s32ReInvite )

			if(!g_pDlg->m_bAutoRtp)
			{
				if( g_pDlg->m_bUseDspRtp )
				{
					// find a free call slot to call out
					Acs_VoIP_MediaInfo* pMediaInfo = &g_deviceVoIP[iDeviceIP].mediaInfo;
					int iDeviceRtp = iDevice;
					SetRTPSession(&g_deviceRTP[iDeviceIP].device, 1, pMediaInfo->payload_dtmf, pMediaInfo->payload_tone);
					DJ_U8 u8CodePayload	= 0;
					for(int i= 0;i< 10;i++ )
					{
						if( g_rtp_codec[i].u8CodecType == pMediaInfo->u8MediaCapList[0] )
						{
							u8CodePayload	= g_rtp_codec[i].u8PayloadType;
							break;
						}
					}
					SetRTPCodec(&g_deviceRTP[iDeviceIP].device, pMediaInfo->u8AudioEnabled, pMediaInfo->u8MediaCapList[0], u8CodePayload, 0, 0, 0);
					SetRTPIP(&g_deviceRTP[iDeviceIP].device, pMediaInfo->u8AudioEnabled, pMediaInfo->s8AudioAddress, pMediaInfo->u16AudioPort,
						pMediaInfo->u8VideoEnabled, pMediaInfo->s8VideoAddress, pMediaInfo->u16VideoPort);
					
					strcpy( pMediaInfo->s8AudioAddress, g_pDlg->m_strDspIp);
					if(g_pDlg->m_bDspBehindNat)
						pMediaInfo->u16AudioPort = iDeviceRtp*2+RTP_PORT_BASE(10000, g_pDlg->m_iDSP);
					else
						pMediaInfo->u16AudioPort = 10000+iDeviceRtp*2;//RTP_PORT_BASE(10000, m_rtp->GetID());
					pMediaInfo->u8VideoEnabled	= 0;
					pMediaInfo->u8MediaCapNum	= 1;
				}
				XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDevice].device, 
					VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo), 
					&g_deviceVoIP[iDeviceIP].mediaInfo);
			}
								
			XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDevice].device, XMS_IO_TYPE_VOIP_CALLMODIFY,
						sizeof(VoIPCallModifyPrivate_t), pCallInfo);
	
		}
		break;
	case XMS_IO_TYPE_VOIP_CALLMODIFYANSWER:
		if (pIOEvt->m_u16IoDataLen >= sizeof(VoIPCallModifyPrivate_t))
		{
			VoIPCallModifyPrivate_t *pCallInfo = (VoIPCallModifyPrivate_t *)FetchIOData(pAcsEvt);
			TRACE("Call[%d] modified, and Media connection mode=%d\n",iDeviceIP,pCallInfo->u8MediaMode);
			int iDevice=g_deviceVoIP[iDeviceIP].iPeerDevice;
			if(pCallInfo->u8MediaMode ==2)
			{
				if(g_pDlg->m_bAutoRtp || g_pDlg->m_bUseDspRtp)
				{
					MixerControlParam_t paramMixer = {0};
					paramMixer.m_u8SRC1_Ctrl = XMS_MIXER_FROM_PLAY;
					paramMixer.m_u16SRC_ChID1 = g_deviceVoc[iDeviceIP].device.m_s16ChannelID;

					// send SetParam command
					RetCode_t ret = XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceIP].device,
						VOIP_PARAM_RTPMIXER, sizeof(paramMixer), &paramMixer);



					g_deviceVoIP[iDeviceIP].iVocDevice = iDeviceIP;
					g_deviceVoc[iDeviceIP].iVoIPDevice = iDeviceIP;



					PlayProperty_t pp = {0};
					pp.m_u8DecodeType =  XMS_Alaw_type ;
					pp.m_u16PlayType = XMS_PLAY_TYPE_FILE;
					pp.m_u8SrcMode =  XMS_SRC_8K ;
					strcpy(pp.m_s8PlayContent,"C:\\DJKeygoe\\Samples\\Voc\\ConfMusi.Pcm");
					 
					ret = XMS_ctsPlay(g_acsHandle, &g_deviceVoc[iDeviceIP].device, &pp, NULL);

				}
			}
			else
			{
	//			XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoIP[g_deviceVoIP[iDeviceIP].iPeerDevice].device,
	//						&g_deviceVoc[g_deviceVoIP[iDeviceIP].iPeerDevice].device, NULL);

					if(g_pDlg->m_bAutoRtp)
					{
						XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoIP[iDeviceIP].device,
						&g_deviceVoc[iDeviceIP].device, NULL);
					}
					else if(g_pDlg->m_bUseDspRtp)
					{
						XMS_ctsLinkDevice(g_acsHandle, &g_deviceRTP[iDeviceIP].device,
							&g_deviceVoc[iDeviceIP].device, NULL);
					}
//						XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoIP[iDeviceIP].device,
//							&g_deviceVoc[iDeviceIP].device, NULL);
					XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoc[g_deviceVoIP[iDeviceIP].iPeerDevice].device,
						&g_deviceVoc[iDeviceIP].device, NULL);
					XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoc[iDeviceIP].device,
						&g_deviceVoc[g_deviceVoIP[iDeviceIP].iPeerDevice].device, NULL);

					ControlPlay_t cp = {0};
					cp.m_u16ControlType = XMS_STOP_PLAY;

					// send control play command
					RetCode_t ret = XMS_ctsControlPlay(g_acsHandle, &g_deviceVoc[iDeviceIP].device, &cp, NULL);

					memset(g_deviceVoc[iDeviceIP].tszPlayFile, 0, sizeof(g_deviceVoc[iDeviceIP].tszPlayFile));
			}
			VoIPCallModifyPrivate_t paramVoIPCallModify = {0};
			VoIPCallModifyPrivate_t *PparamVoIPCallModify = &paramVoIPCallModify;
			paramVoIPCallModify.m_PrivateData.m_u32DataSize= sizeof(VoIPCallModifyPrivate_t);
			paramVoIPCallModify.u8MediaMode=pCallInfo->u8MediaMode;
			paramVoIPCallModify.m_u8MediaCapNum=pCallInfo->m_u8MediaCapNum;
			//paramVoIPCallModify.m_u8MediaCapList=pCallInfo->m_u8MediaCapList;
			memcpy(PparamVoIPCallModify->m_u8MediaCapList, pCallInfo->m_u8MediaCapList, sizeof(PparamVoIPCallModify->m_u8MediaCapList));
			
/*				if(!g_pDlg->m_bAutoRtp && !g_pDlg->m_bUseDspRtp)
			{
				XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[g_deviceVoIP[iDeviceIP].iPeerDevice].device, 
				VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo), 
				&g_deviceVoIP[iDeviceIP].mediaInfo);
			}*/

			if(!g_pDlg->m_bAutoRtp)
			{
				if( g_pDlg->m_bUseDspRtp )
				{
					// find a free call slot to call out
					Acs_VoIP_MediaInfo* pMediaInfo = &g_deviceVoIP[iDeviceIP].mediaInfo;
					int iDeviceRtp = g_deviceVoIP[iDeviceIP].iPeerDevice;
					SetRTPSession(&g_deviceRTP[iDeviceIP].device, 1, pMediaInfo->payload_dtmf, pMediaInfo->payload_tone);
					DJ_U8 u8CodePayload	= 0;
					for(int i= 0;i< 10;i++ )
					{
						if( g_rtp_codec[i].u8CodecType == pMediaInfo->u8MediaCapList[0] )
						{
							u8CodePayload	= g_rtp_codec[i].u8PayloadType;
							break;
						}
					}
					SetRTPCodec(&g_deviceRTP[iDeviceIP].device, pMediaInfo->u8AudioEnabled, pMediaInfo->u8MediaCapList[0], u8CodePayload, 0, 0, 0);
					SetRTPIP(&g_deviceRTP[iDeviceIP].device, pMediaInfo->u8AudioEnabled, pMediaInfo->s8AudioAddress, pMediaInfo->u16AudioPort,
						pMediaInfo->u8VideoEnabled, pMediaInfo->s8VideoAddress, pMediaInfo->u16VideoPort);
					
					strcpy( pMediaInfo->s8AudioAddress, g_pDlg->m_strDspIp);
					if(g_pDlg->m_bDspBehindNat)
						pMediaInfo->u16AudioPort = iDeviceRtp*2+RTP_PORT_BASE(10000, g_pDlg->m_iDSP);
					else
						pMediaInfo->u16AudioPort = 10000+iDeviceRtp*2;//RTP_PORT_BASE(10000, m_rtp->GetID());
					pMediaInfo->u8VideoEnabled	= 0;
					pMediaInfo->u8MediaCapNum	= 1;
				}
				XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[g_deviceVoIP[iDeviceIP].iPeerDevice].device, 
					VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo), 
					&g_deviceVoIP[iDeviceIP].mediaInfo);
			}

			XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[g_deviceVoIP[iDeviceIP].iPeerDevice].device, XMS_IO_TYPE_VOIP_CALLMODIFYANSWER,
									sizeof(VoIPCallModifyPrivate_t), &paramVoIPCallModify);
		}

		break;
	}

	g_pDlg->refreshListIP(iDeviceIP);
}

//////////////////////////////////////////////////////////////////////////
// Voice Device IO Data event handler
void OnRecvIODataVoice(int iDeviceVoc, Acs_Evt_t *pAcsEvt)
{
	Acs_IO_Data *pIOEvt = (Acs_IO_Data *)FetchEventData(pAcsEvt);

	if (pIOEvt->m_u16IoType == XMS_IO_TYPE_DTMF)
	{
		// stop playing tone
		char tone;
		RetCode_t ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoc[iDeviceVoc].device,
			XMS_IO_TYPE_GTG, 0, &tone);

		int iDeviceTrk = g_deviceVoc[iDeviceVoc].iTrunkDevice;
		if (iDeviceTrk == -1)
			return; // should not be

		char dtmf = *(char *)(pIOEvt+1);

		int iDtmfLen = strlen(g_deviceTrunk[iDeviceTrk].szDtmf);
		if (iDtmfLen >= sizeof(g_deviceTrunk[iDeviceTrk].szDtmf)-1)
		{
			memset(g_deviceTrunk[iDeviceTrk].szDtmf, 0, sizeof(g_deviceTrunk[iDeviceTrk].szDtmf));
			iDtmfLen = 0;
		}

		g_deviceTrunk[iDeviceTrk].szDtmf[iDtmfLen] = dtmf;
	}
}

// void OnUnattandCallTransfer(int iSrcDev, Acs_VoIP_Refer* pRefer)
// {
// 	int iDeviceCaller = g_deviceVoIP[iSrcDev].iPeerDevice;
// 	CString strCallerNo = g_deviceVoIP[iSrcDev].tszPeerTelNo;
// 	XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCaller].device,
// 		&g_deviceVoc[iSrcDev].device, NULL);
// 	XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceVoc[iSrcDev].device,
// 		&g_deviceVoc[iDeviceCaller].device, NULL);
// 
// 	g_deviceVoIP[iSrcDev].iPeerDevice = -1;
// 	memset(g_deviceVoIP[iSrcDev].tszPeerTelNo, '\0', sizeof(g_deviceVoIP[iSrcDev].tszPeerTelNo));
// 	
// 	XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[iSrcDev].device, 0, NULL);
// 
// 	// find a free call slot to call out
// 	for (int iDeviceCallee = 0; iDeviceCallee < g_iVoIPDevNum; ++iDeviceCallee)
// 	{
// 		if (g_deviceVoIP[iDeviceCallee].iState == DCS_FREE)
// 			break;
// 	}
// 	if (iDeviceCallee >= g_iVoIPDevNum)
// 	{
// 		g_deviceVoIP[iDeviceCaller].iPeerDevice = -1;
// 		memset(g_deviceVoIP[iDeviceCaller].tszPeerTelNo, '\0', sizeof(g_deviceVoIP[iDeviceCaller].tszPeerTelNo));
// 		
// 		XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, 0, NULL);
// 		return;
// 	}
// 	
// 	// update caller info
// 	// fill call parameters
// 	VoIPCallPrivate_t paramVoIPCall = {0};
// 	paramVoIPCall.m_PrivateData.m_u32DataSize = sizeof(VoIPCallPrivate_t);
// 	paramVoIPCall.m_s32Protocol = XMS_VOIP_PROTOCOL_SIP;
// 	
// 	// use code below to set media caps (supported in v2.1.2)
// 	paramVoIPCall.m_u8MediaCapNum = 0;
// 	paramVoIPCall.m_u8MediaCapList[0] = VOIP_MEDIA_AUDIO_G723;
// 	paramVoIPCall.m_u8MediaCapList[1] = VOIP_MEDIA_AUDIO_PCMA;
// 	paramVoIPCall.m_u8MediaCapList[2] = VOIP_MEDIA_AUDIO_G729;
// 	
// 	int iReg = -1;
// 	if (g_pDlg->m_bInteractive)
// 	{
// 		int iReg = getVoIPRegClient(pRefer->m_s8TelNo, pRefer->m_s8UserID);
// 		if (iReg < 0)
// 		{
// 			// Send Notify Server Bussy
// 			//SendReferNotify(iSrcDev, 403);
// 			g_deviceVoIP[iDeviceCaller].iPeerDevice = -1;
// 			memset(g_deviceVoIP[iDeviceCaller].tszPeerTelNo, '\0', sizeof(g_deviceVoIP[iDeviceCaller].tszPeerTelNo));
// 			
// 			XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, 0, NULL);
// 			return;
// 		}
// 	}
// 	if (g_pDlg->m_bInteractive)
// 		paramVoIPCall.m_s32Protocol = g_ipRegSlot[iReg].iProtocol;
// 	
// 	memset(paramVoIPCall.m_s8CallerAddress, 0, sizeof(paramVoIPCall.m_s8CallerAddress));
// 	paramVoIPCall.m_s32CallerPort = 0;
// 	
// 	if (g_pDlg->m_bInteractive)
// 	{
// 		strcpy(paramVoIPCall.m_s8CalleeAddress, g_ipRegSlot[iReg].addrRegClient.tszAddr);
// 		paramVoIPCall.m_s32CalleePort = g_ipRegSlot[iReg].addrRegClient.port;
// 		strcpy(paramVoIPCall.m_s8CalleeUserID, g_ipRegSlot[iReg].addrRegClient.tszUserID);
// 	}
// 	
// 	tagRouteItem* route = NULL;
// 	if (!g_pDlg->m_bInteractive)
// 	{
// 		route = findRoute(pRefer->m_s8TelNo);
// 		if(route==NULL)
// 		{
// 			// clear callee address, cause keygoe to find the REAL callee address
// 			memset(paramVoIPCall.m_s8CalleeAddress, 0, sizeof(paramVoIPCall.m_s8CalleeAddress));
// 			paramVoIPCall.m_s32CalleePort = 0;
// 		}
// 		else
// 		{
// 			TRACE("Find route=(addr=%s port=%d user=%s password=%s callee=%s)\n", route->strAddr, route->uPort, route->strUserName, route->strPassword, route->strCalleeHead);
// 			strcpy(paramVoIPCall.m_s8CalleeAddress, route->strAddr);
// 			paramVoIPCall.m_s32CalleePort = route->uPort;
// 		}
// 	}
// 	
// 	strcpy(g_deviceVoIP[iDeviceCallee].tszPeerTelNo, strCallerNo);
// 	XMS_ctsMakeCallOut(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device,
// 		g_deviceVoIP[iDeviceCallee].tszPeerTelNo, pRefer->m_s8TelNo, (PrivateData_t *)&paramVoIPCall);
// 	
// 	// update callee info
// 	g_deviceVoIP[iDeviceCallee].iProtocol = paramVoIPCall.m_s32Protocol;
// 	strcpy(g_deviceVoIP[iDeviceCallee].tszPeerTelNo, strCallerNo);
// 	g_deviceVoIP[iDeviceCallee].iPeerDevice = iDeviceCaller;
// 	g_deviceVoIP[iDeviceCallee].iTranferSrcDev = iDeviceCaller;
// 	g_pDlg->refreshListIP(iDeviceCallee);
// 
// 	strcpy(g_deviceVoIP[iDeviceCaller].tszPeerTelNo, pRefer->m_s8TelNo);
// 	g_deviceVoIP[iDeviceCaller].iPeerDevice = iDeviceCallee;
// 	g_pDlg->refreshListIP(iDeviceCaller);
// }

void OnUnattandCallTransfer(int iSrcDev, Acs_VoIP_Refer* pRefer)
{
	int iDeviceCallee;

	// find a free call slot to call out
	for ( iDeviceCallee = 0; iDeviceCallee < g_iVoIPDevNum; ++iDeviceCallee)
	{
		if (g_deviceVoIP[iDeviceCallee].iState == DCS_FREE)
			break;
	}
	if (iDeviceCallee >= g_iVoIPDevNum)
	{
		//Send Notify Server Bussy
		SendReferNotify(iSrcDev, 403);
		return;
	}
	
	// update caller info
	// fill call parameters
	VoIPCallPrivate_t paramVoIPCall = {0};
	paramVoIPCall.m_PrivateData.m_u32DataSize = sizeof(VoIPCallPrivate_t);
	paramVoIPCall.m_s32Protocol = XMS_VOIP_PROTOCOL_SIP;
	
	// use code below to set media caps (supported in v2.1.2)
	paramVoIPCall.m_u8MediaCapNum = 0;
	paramVoIPCall.m_u8MediaCapList[0] = VOIP_MEDIA_AUDIO_G723;
	paramVoIPCall.m_u8MediaCapList[1] = VOIP_MEDIA_AUDIO_PCMA;
	paramVoIPCall.m_u8MediaCapList[2] = VOIP_MEDIA_AUDIO_G729;
	
	int iReg = -1;
	if (g_pDlg->m_bInteractive)
	{
		int iReg = getVoIPRegClient(pRefer->m_s8TelNo, pRefer->m_s8UserID);
		if (iReg < 0)
		{
			// Send Notify Server Bussy
			SendReferNotify(iSrcDev, 403);
			return;
		}
	}
	if (g_pDlg->m_bInteractive)
		paramVoIPCall.m_s32Protocol = g_ipRegSlot[iReg].iProtocol;
	
	memset(paramVoIPCall.m_s8CallerAddress, 0, sizeof(paramVoIPCall.m_s8CallerAddress));
	paramVoIPCall.m_s32CallerPort = 0;
	
	if (g_pDlg->m_bInteractive)
	{
		strcpy(paramVoIPCall.m_s8CalleeAddress, g_ipRegSlot[iReg].addrRegClient.tszAddr);
		paramVoIPCall.m_s32CalleePort = g_ipRegSlot[iReg].addrRegClient.port;
		strcpy(paramVoIPCall.m_s8CalleeUserID, g_ipRegSlot[iReg].addrRegClient.tszUserID);
	}
	
	tagRouteItem* route = NULL;
	if (!g_pDlg->m_bInteractive)
	{
		route = findRoute(pRefer->m_s8TelNo);
		if(route==NULL)
		{
			// clear callee address, cause keygoe to find the REAL callee address
			memset(paramVoIPCall.m_s8CalleeAddress, 0, sizeof(paramVoIPCall.m_s8CalleeAddress));
			paramVoIPCall.m_s32CalleePort = 0;
		}
		else
		{
			TRACE("Find route=(addr=%s port=%d user=%s password=%s callee=%s)\n", route->strAddr, route->uPort, route->strUserName, route->strPassword, route->strCalleeHead);
			strcpy(paramVoIPCall.m_s8CalleeAddress, route->strAddr);
			paramVoIPCall.m_s32CalleePort = route->uPort;
		}
	}
	
	if(0)	//Only for Diversion test
	{
		Acs_VoIP_Call_Diversion_Info divInfo;
		memset(&divInfo, 0, sizeof(Acs_VoIP_Call_Diversion_Info));
		sprintf(divInfo.m_s8Diversion, "<tel:%s>", g_deviceVoIP[g_deviceVoIP[iSrcDev].iPeerDevice].tszPeerTelNo);
		sprintf(divInfo.m_s8Reason, "unknown");
		XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device, VOIP_PARAM_CALL_DIVERSION_INFO, sizeof(Acs_VoIP_Call_Diversion_Info), &divInfo);
	}

	if(!g_pDlg->m_bAutoRtp)
	{
		if( g_pDlg->m_bUseDspRtp )
		{
			// find a free call slot to call out
			Acs_VoIP_MediaInfo* pMediaInfo = &g_deviceVoIP[iSrcDev].mediaInfo;
			strcpy( pMediaInfo->s8AudioAddress, g_pDlg->m_strDspIp);
			if(g_pDlg->m_bDspBehindNat)
				pMediaInfo->u16AudioPort = iDeviceCallee*2+RTP_PORT_BASE(10000, g_pDlg->m_iDSP);
			else
				pMediaInfo->u16AudioPort = 10000+iDeviceCallee*2;//RTP_PORT_BASE(10000, m_rtp->GetID());
			pMediaInfo->u8VideoEnabled	= 0;
			pMediaInfo->u8MediaCapNum	= 1;
			XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device, 
			VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo), 
			&g_deviceVoIP[iSrcDev].mediaInfo);
		}
		else
		{
			XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device, 
				VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo), 
				&g_deviceVoIP[g_deviceVoIP[iSrcDev].iPeerDevice].mediaInfo);
		}
	}


	XMS_ctsMakeCallOut(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device,
		g_deviceVoIP[iSrcDev].tszPeerTelNo, pRefer->m_s8TelNo,
		(PrivateData_t *)&paramVoIPCall);


//		::AfxMessageBox("zhuanyi");

	// update callee info
	g_deviceVoIP[iDeviceCallee].iProtocol = paramVoIPCall.m_s32Protocol;
	strcpy(g_deviceVoIP[iDeviceCallee].tszPeerTelNo, g_deviceVoIP[iSrcDev].tszPeerTelNo);
	g_deviceVoIP[iDeviceCallee].iPeerDevice = g_deviceVoIP[iSrcDev].iPeerDevice;
	g_deviceVoIP[iDeviceCallee].iTranferSrcDev = iSrcDev;
	g_pDlg->refreshListIP(iDeviceCallee);

}

// void OnAttandCallTransfer(int iSrcDev, Acs_VoIP_Refer* pRefer)
// {
// 	
// 	int iDeviceCaller = g_deviceVoIP[iSrcDev].iPeerDevice;
// 	CString strCallerNo = g_deviceVoIP[iSrcDev].tszPeerTelNo;
// 	BOOL bACT = g_deviceVoIP[pRefer->m_u16ReferedToChanId].iState==DCS_CONNECT;
// 
// 	XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCaller].device,
// 		&g_deviceVoc[iSrcDev].device, NULL);
// 	XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceVoc[iSrcDev].device,
// 		&g_deviceVoc[iDeviceCaller].device, NULL);
// 	
// 	g_deviceVoIP[iSrcDev].iPeerDevice = -1;
// 	memset(g_deviceVoIP[iSrcDev].tszPeerTelNo, '\0', sizeof(g_deviceVoIP[iSrcDev].tszPeerTelNo));
// 	
// 	XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[iSrcDev].device, 0, NULL);
// 	
// 	int iDeviceCallee = pRefer->m_u16ReferedToChanId;
// 	CString strCalleeNo = g_deviceVoIP[iDeviceCallee].tszPeerTelNo;
// 	iDeviceCallee = g_deviceVoIP[iDeviceCallee].iPeerDevice;
// 
// 	if(bACT)
// 	{
// 		XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceVoc[pRefer->m_u16ReferedToChanId].device,
// 			&g_deviceVoc[iDeviceCallee].device, NULL);
// 		XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCallee].device,
// 			&g_deviceVoc[pRefer->m_u16ReferedToChanId].device, NULL);
// 	}
// 
// 	g_deviceVoIP[pRefer->m_u16ReferedToChanId].iPeerDevice = -1;
// 	memset(g_deviceVoIP[pRefer->m_u16ReferedToChanId].tszPeerTelNo, '\0', sizeof(g_deviceVoIP[pRefer->m_u16ReferedToChanId].tszPeerTelNo));
// 
// 	XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[pRefer->m_u16ReferedToChanId].device, 0, NULL);
// 
// 	if(bACT)
// 	{
// 		XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCaller].device,
// 			&g_deviceVoc[iDeviceCallee].device, NULL);
// 		
// 		XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCallee].device,
// 			&g_deviceVoc[iDeviceCaller].device, NULL);
// 	}
// 
// 	g_deviceVoIP[iDeviceCallee].iPeerDevice = iDeviceCaller;
// 	strcpy(g_deviceVoIP[iDeviceCallee].tszPeerTelNo, strCallerNo);
// 	g_pDlg->refreshListIP(iDeviceCallee);
// 	
// 	g_deviceVoIP[iDeviceCaller].iPeerDevice = iDeviceCallee;
// 	strcpy(g_deviceVoIP[iDeviceCaller].tszPeerTelNo, strCalleeNo);
// 	g_pDlg->refreshListIP(iDeviceCaller);
// 
// 	if(bACT)
// 	{
// 		g_deviceVoIP[iDeviceCallee].iTranferSrcDev = -1;
// 		g_deviceVoIP[iDeviceCaller].iTranferSrcDev = -1;
// 	}
// }

void OnAttandCallTransfer(int iSrcDev, Acs_VoIP_Refer* pRefer)
{
	
	int iDeviceCaller = g_deviceVoIP[iSrcDev].iPeerDevice;
	CString strCallerNo = g_deviceVoIP[iSrcDev].tszPeerTelNo;
	BOOL bACT = g_deviceVoIP[pRefer->m_u16ReferedToChanId].iState==DCS_CONNECT;
	
	XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCaller].device,
		&g_deviceVoc[iSrcDev].device, NULL);
	XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceVoc[iSrcDev].device,
		&g_deviceVoc[iDeviceCaller].device, NULL);
	
	g_deviceVoIP[iSrcDev].iPeerDevice = -1;
	memset(g_deviceVoIP[iSrcDev].tszPeerTelNo, '\0', sizeof(g_deviceVoIP[iSrcDev].tszPeerTelNo));
// 	
// 	XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[iSrcDev].device, 0, NULL);

	
	int iDeviceCallee = pRefer->m_u16ReferedToChanId;
	CString strCalleeNo = g_deviceVoIP[iDeviceCallee].tszPeerTelNo;
	iDeviceCallee = g_deviceVoIP[iDeviceCallee].iPeerDevice;
	
	if(bACT)
	{
		XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceVoc[pRefer->m_u16ReferedToChanId].device,
			&g_deviceVoc[iDeviceCallee].device, NULL);
		XMS_ctsUnlinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCallee].device,
			&g_deviceVoc[pRefer->m_u16ReferedToChanId].device, NULL);
	}
	
	g_deviceVoIP[pRefer->m_u16ReferedToChanId].iPeerDevice = -1;
	memset(g_deviceVoIP[pRefer->m_u16ReferedToChanId].tszPeerTelNo, '\0', sizeof(g_deviceVoIP[pRefer->m_u16ReferedToChanId].tszPeerTelNo));
	
	XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[pRefer->m_u16ReferedToChanId].device, 0, NULL);
	
	if(bACT)
	{
		XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCaller].device, &g_deviceVoc[iDeviceCallee].device, NULL);
		XMS_ctsLinkDevice(g_acsHandle, &g_deviceVoc[iDeviceCallee].device, &g_deviceVoc[iDeviceCaller].device, NULL);

		SendReferNotify(iSrcDev, 200);
	}
	else	//SACT
	{	
		XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[iSrcDev].device, 0, NULL);
		g_deviceVoIP[iDeviceCallee].iTranferSrcDev = -2;
	}
	
	g_deviceVoIP[iDeviceCallee].iPeerDevice = iDeviceCaller;
	strcpy(g_deviceVoIP[iDeviceCallee].tszPeerTelNo, strCallerNo);
	g_pDlg->refreshListIP(iDeviceCallee);
	
	g_deviceVoIP[iDeviceCaller].iPeerDevice = iDeviceCallee;
	strcpy(g_deviceVoIP[iDeviceCaller].tszPeerTelNo, strCalleeNo);
	g_pDlg->refreshListIP(iDeviceCaller);
	
	if(bACT)
	{
		g_deviceVoIP[iDeviceCallee].iTranferSrcDev = -1;
		g_deviceVoIP[iDeviceCaller].iTranferSrcDev = -1;
	}

	if(bACT)
	{
		Acs_VoIP_MediaInfo ptem = g_deviceVoIP[iDeviceCaller].mediaInfo;
		
/*		if(!g_pDlg->m_bAutoRtp && !g_pDlg->m_bUseDspRtp)
		{
			XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, 
				VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo),
				&g_deviceVoIP[iDeviceCallee].mediaInfo);
		}*/

		if(!g_pDlg->m_bAutoRtp)
		{
			if( g_pDlg->m_bUseDspRtp )
			{
				// find a free call slot to call out
				Acs_VoIP_MediaInfo* pMediaInfo = &g_deviceVoIP[iDeviceCallee].mediaInfo;
				int iDeviceRtp = iDeviceCaller;
/*				SetRTPSession(&g_deviceRTP[iDeviceCallee].device, 1, pMediaInfo->payload_dtmf, pMediaInfo->payload_tone);
				DJ_U8 u8CodePayload	= 0;
				for(int i= 0;i< 10;i++ )
				{
					if( g_rtp_codec[i].u8CodecType == pMediaInfo->u8MediaCapList[0] )
					{
						u8CodePayload	= g_rtp_codec[i].u8PayloadType;
						break;
					}
				}
				SetRTPCodec(&g_deviceRTP[iDeviceCallee].device, pMediaInfo->u8AudioEnabled, pMediaInfo->u8MediaCapList[0], u8CodePayload, 0, 0, 0);
				SetRTPIP(&g_deviceRTP[iDeviceCallee].device, pMediaInfo->u8AudioEnabled, pMediaInfo->s8AudioAddress, pMediaInfo->u16AudioPort,
					pMediaInfo->u8VideoEnabled, pMediaInfo->s8VideoAddress, pMediaInfo->u16VideoPort);*/
				
				strcpy( pMediaInfo->s8AudioAddress, g_pDlg->m_strDspIp);
				if(g_pDlg->m_bDspBehindNat)
					pMediaInfo->u16AudioPort = iDeviceRtp*2+RTP_PORT_BASE(10000, g_pDlg->m_iDSP);
				else
					pMediaInfo->u16AudioPort = 10000+iDeviceRtp*2;//RTP_PORT_BASE(10000, m_rtp->GetID());
				pMediaInfo->u8VideoEnabled	= 0;
				pMediaInfo->u8MediaCapNum	= 1;
			}
		
			XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, 
				VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo),
				&g_deviceVoIP[iDeviceCallee].mediaInfo);
			g_deviceVoIP[iDeviceCallee].mediaInfo;
		}

		g_deviceVoIP[iDeviceCaller].mediaInfo;
					VoIPCallModifyPrivate_t paramVoIPCall1 = {0};
			paramVoIPCall1.m_PrivateData.m_u32DataSize = sizeof(VoIPCallPrivateEx_t);
			VoIPCallModifyPrivate_t *PparamVoIPCall1=&paramVoIPCall1;


			paramVoIPCall1.m_u8MediaCapNum = g_deviceVoIP[iDeviceCallee].mediaInfo.u8MediaCapNum;
			memcpy(PparamVoIPCall1->m_u8MediaCapList, g_deviceVoIP[iDeviceCallee].mediaInfo.u8MediaCapList, sizeof(PparamVoIPCall1->m_u8MediaCapList));
			paramVoIPCall1.u8MediaMode = 0;
			
			XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDeviceCaller].device, XMS_IO_TYPE_VOIP_CALLMODIFY,
				sizeof(paramVoIPCall1), &paramVoIPCall1);

		if( !g_pDlg->m_bAutoRtp && !g_pDlg->m_bUseDspRtp)
		{
			XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device, 
				VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo),
				&ptem);
			paramVoIPCall1.m_u8MediaCapNum = ptem.u8MediaCapNum;
			memcpy(PparamVoIPCall1->m_u8MediaCapList, ptem.u8MediaCapList, sizeof(PparamVoIPCall1->m_u8MediaCapList));
			XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDeviceCallee].device, XMS_IO_TYPE_VOIP_CALLMODIFY,
				sizeof(paramVoIPCall1), &paramVoIPCall1);
		}
	}


}

void SendReferNotify(int iVoIPDev, int iStatusCode)
{
	Acs_VoIP_Notify notify = {iStatusCode};
	XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iVoIPDev].device, XMS_IO_TYPE_VOIP_REFER_NOTIFY,
				sizeof(notify), &notify);
}

//////////////////////////////////////////////////////////////////////////
// XMS Join Conference Event Handler
void OnJoinConf(Acs_Evt_t *pAcsEvt)
{
}

void OnGetParam(Acs_Evt_t* pAcsEvt)
{
	if ( XMS_DEVMAIN_VOIP == pAcsEvt->m_DeviceID.m_s16DeviceMain )
	{
		Acs_ParamProc_Data *pParam = (Acs_ParamProc_Data*)(FetchEventData(pAcsEvt));

		if(pParam->m_u16ParamCmdType == VOIP_PARAM_VOIPADDR)
		{
			Acs_VoIP_WANADDR *pWanAddr = (Acs_VoIP_WANADDR *)(FetchParamData(pAcsEvt));
			
//			::AfxMessageBox(pWanAddr->m_s8WanAddress);
		}
		if(pParam->m_u16ParamCmdType == VOIP_PARAM_CALL_DIVERSION_INFO)
		{
			Acs_VoIP_Call_Diversion_Info *pDivInfo = (Acs_VoIP_Call_Diversion_Info*)(FetchParamData(pAcsEvt));
			if(strcmp(pDivInfo->m_s8Diversion, "")==0)
				TRACE("Get Call Diversion response, but there are no any call diversion information\n");
			else
				TRACE("Get Call Diversion response: diversion=%s reason=%s\n", pDivInfo->m_s8Diversion, pDivInfo->m_s8Reason);
		}
				if(pParam->m_u16ParamCmdType == VOIP_PARAM_VOIPADDR)
		{

		}

	}
}

void OnGetMediaInfo(Acs_Evt_t* pAcsEvt)
{
	Acs_VoIP_MediaInfo *pMediaInfo = (Acs_VoIP_MediaInfo *)FetchEventData(pAcsEvt);
	int iDeviceCaller = mapDeviceItem(&pAcsEvt->m_DeviceID);
	Acs_VoIP_MediaInfo *pCallMediaInfo = &g_deviceVoIP[iDeviceCaller].mediaInfo;
	memcpy(pCallMediaInfo, pMediaInfo, sizeof(Acs_VoIP_MediaInfo));
}

void SetRTPIP(DeviceID_t* dev, DJ_U8 u8AudioEnabled, const DJ_S8* s8AudioAddress, DJ_U16  u16AudioPort, DJ_U8   u8VideoEnabled, const DJ_S8* s8VideoAddress, DJ_U16  u16VideoPort)
{
    Acs_VoIP_RTPADDR	addr	= {0};
    strcpy(addr.audio.m_s8IP, s8AudioAddress);
    addr.audio.m_u16Port	= u16AudioPort;
    addr.audio.m_u8Enable	= u8AudioEnabled;
    strcpy(addr.video.m_s8IP,s8VideoAddress);
    addr.video.m_u16Port	= u16VideoPort;
    addr.video.m_u8Enable	= u8VideoEnabled;
    XMS_ctsSetParam(g_acsHandle, dev, VOIP_PARAM_RTPADDR, sizeof(Acs_VoIP_RTPADDR), &addr);
}

// CDJRtp::SetSession-------------------------------------------------------------------------------------------
void SetRTPSession(DeviceID_t* dev, DJ_U8 u8Enabled, DJ_U8 dtmf, DJ_U8 tone)
{
    Acs_VoIP_RTPSESSION	session	= {0};
    session.m_u8Enable			= u8Enabled;
    session.m_u8PayloadDtmf		= dtmf;
    session.m_u8PayloadTone		= tone;
    XMS_ctsSetParam(g_acsHandle, dev, VOIP_PARAM_RTPSESSION, sizeof(Acs_VoIP_RTPSESSION), &session);
}

// CDJRtp::SetCodec-------------------------------------------------------------------------------------------
void SetRTPCodec(DeviceID_t* dev, DJ_U8 u8AudioEnabled, DJ_U8 u8AudioCodec, DJ_U8 u8AudioPayloadType, DJ_U8 u8VideoEnabled, DJ_U8 u8VideoCodec, DJ_U8 u8VideoPayloadType)
{
    Acs_VoIP_RTPCODEC	codec	= {0};
    codec.audio.m_u8Enable			= u8AudioEnabled;
    codec.audio.m_u8TxCodec			= u8AudioCodec;
    codec.audio.m_u8RxCodec			= u8AudioCodec;
    codec.audio.m_u8TxPayloadType	= u8AudioPayloadType;
    codec.audio.m_u8RxPayloadType	= u8AudioPayloadType;
    codec.video.m_u8Enable			= u8VideoEnabled;
    codec.video.m_u8TxCodec			= u8VideoCodec;
    codec.video.m_u8RxCodec			= u8VideoCodec;
    codec.video.m_u8TxPayloadType	= u8VideoPayloadType;
    codec.video.m_u8RxPayloadType	= u8VideoPayloadType;
    XMS_ctsSetParam(g_acsHandle, dev, VOIP_PARAM_RTPCODEC, sizeof(Acs_VoIP_RTPCODEC), &codec);
}