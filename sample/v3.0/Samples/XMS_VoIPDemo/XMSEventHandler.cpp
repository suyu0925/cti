// XMSEventHandler.cpp : implementation file
//

#include "stdafx.h"

#include "XMSVoIPDemo.h"
#include "XMSVoIPDemoDlg.h"

#include "XMSEventHandler.h"
#include "XMSData.h"

CXMSVoIPDemoDlg *g_pDlg = NULL;

//////////////////////////////////////////////////////////////////////////
// event handlers
void OnOpenStream(Acs_Evt_t *pAcsEvt);
void OnQueryDevice(Acs_Evt_t *pAcsEvt);
void OnQueryDeviceEnd(Acs_Evt_t *pAcsEvt);
void OnOpenDevice(Acs_Evt_t *pAcsEvt);
void OnCloseDevice(Acs_Evt_t *pAcsEvt);
void OnDeviceState(Acs_Evt_t *pAcsEvt);
void OnCallOut(Acs_Evt_t *pAcsEvt);
void OnCallIn(Acs_Evt_t *pAcsEvt);
void OnAlertCall(Acs_Evt_t *pAcsEvt);
void OnAnswerCall(Acs_Evt_t *pAcsEvt);
void OnClearCall(Acs_Evt_t *pAcsEvt);
void OnLinkDevice(Acs_Evt_t *pAcsEvt);
void OnUnlinkDevice(Acs_Evt_t *pAcsEvt);
void OnPlay(Acs_Evt_t *pAcsEvt);
void OnSendIOData(Acs_Evt_t *pAcsEvt);
void OnRecvIOData(Acs_Evt_t *pAcsEvt);
void OnJoinConf(Acs_Evt_t *pAcsEvt);
void OnGetParam(Acs_Evt_t *pAcsEvt);

//////////////////////////////////////////////////////////////////////////
// XMS main event handler
DJ_Void XMSEventHandler(DJ_U32 u32EsrParam)
{
	if (g_pDlg == NULL)
		g_pDlg = (CXMSVoIPDemoDlg *)AfxGetMainWnd();

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

	case XMS_EVT_SENDIODATA:
		OnSendIOData(pAcsEvt);
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

	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_OPEN_STREAM event handler
void OnOpenStream(Acs_Evt_t *pAcsEvt)
{
	TRACE(_T("XMS service opened (ret=%d)\n"), pAcsEvt->m_u32EsrParam);

//	g_pDlg->GetDlgItem(IDC_BUTTON_INIT)->EnableWindow(TRUE);
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

	if (pAcsDevList->m_s32ModuleID != g_pDlg->m_iDSP)
		return;

	int iDevice;
	DeviceID_t *pDevice = (DeviceID_t *)(pAcsDevList+1);

	// save all the capable devices here
	// Note: Device Module ID is ignored in this demo,
	//       which needs to be paid attention to in user's applications!
	switch (pAcsDevList->m_s32DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
		for (iDevice = 0; iDevice < pAcsDevList->m_s32DeviceNum && g_iVoIPDevNum < MAX_DEVICE_VOIP; ++iDevice)
		{
			g_deviceVoIP[g_iVoIPDevNum++].device = pDevice[iDevice];
		}
		break;
	case XMS_DEVMAIN_VOICE:
		for (iDevice = 0; iDevice < pAcsDevList->m_s32DeviceNum && g_iVocDevNum < MAX_DEVICE_VOICE; ++iDevice)
		{
			g_deviceVoc[g_iVocDevNum++].device = pDevice[iDevice];
		}
		break;
	case XMS_DEVMAIN_CONFERENCE:
		for (iDevice = 0; iDevice < pAcsDevList->m_s32DeviceNum && g_iConfDevNum < MAX_DEVICE_CONF; ++iDevice)
		{
			g_deviceConf[g_iConfDevNum++].device = pDevice[iDevice];
		}
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_QUERY_DEVICE_END event handler
void OnQueryDeviceEnd(Acs_Evt_t *pAcsEvt)
{
	TRACE(_T("Device query end\n"));

	// init device list
	g_pDlg->initIPList();
	g_pDlg->initVocList();
	g_pDlg->initConfTree();
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
	case XMS_DEVMAIN_VOICE:
	case XMS_DEVMAIN_CONFERENCE:
		g_pDlg->enableDevice(&pAcsEvt->m_DeviceID);
		break;
	}

#ifdef TEST_ACCESS
	// test for set slot access
	if (pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_VOIP &&
		pAcsEvt->m_DeviceID.m_s16ChannelID == 29)
	{
		DJ_U8 u8AccessFlag = 0x22;
		XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[29].device,
			VOIP_PARAM_ACCESS, 1, &u8AccessFlag);
	}
#endif
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
	case XMS_DEVMAIN_CONFERENCE:
		g_pDlg->enableDevice(&pAcsEvt->m_DeviceID, FALSE);
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_DEVICESTATE event handler (VoIP call state changes)
void OnDeviceState(Acs_Evt_t *pAcsEvt)
{
	Acs_GeneralProc_Data *pDeviceState = (Acs_GeneralProc_Data *)FetchEventData(pAcsEvt);

	TRACE(_T("Device[%02d][%02d][%02d] state changed to 0x%08X\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID,
		pDeviceState->m_s32DeviceState);

	if (pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_VOIP)
	{
		int iDevice = pAcsEvt->m_DeviceID.m_s16ChannelID;

		g_deviceVoIP[iDevice].iState = pDeviceState->m_s32DeviceState;

		switch (pDeviceState->m_s32DeviceState)
		{
		case DCS_FREE:
			g_deviceVoIP[iDevice].iProtocol = 0;
			g_deviceVoIP[iDevice].iState = DCS_FREE;
			memset(&g_deviceVoIP[iDevice].addrCaller, 0, sizeof(XMS_VOIP_ADDR));
			memset(&g_deviceVoIP[iDevice].addrCallee, 0, sizeof(XMS_VOIP_ADDR));
			memset(&g_deviceVoIP[iDevice].szDtmf, 0, sizeof(g_deviceVoIP[iDevice].szDtmf));
//			resetDeviceVoIP(iDevice);
			break;
		case DCS_CALLOUT:
			break;
		case DCS_CALLIN:
			break;
		case DCS_ALERTING:
			break;
		case DCS_CONNECT:
			break;
		case DCS_DISCONNECT:
			break;
		default:
			break;
		}

		g_pDlg->refreshListIP(iDevice);
		g_pDlg->refreshCtrlIP();
		g_pDlg->refreshCtrlConf();
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_CALLOUT event handler (local make call out returns)
void OnCallOut(Acs_Evt_t *pAcsEvt)
{
	Acs_CallControl_Data *pCallEvt = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);

	DJ_U32 *u32ErrCodeExt = (DJ_U32 *)&pCallEvt->m_PrivData;

	TRACE(_T("Device[%02d][%02d][%02d] called out (ret=%d/%d)\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID,
		pCallEvt->m_s32AcsEvtErrCode,
		*u32ErrCodeExt);

	if (pCallEvt->m_s32AcsEvtErrCode != 0)
	{
		CString strErr;
		strErr.Format(_T("Device[%d][%d] make call failed! (ret=%d/%d)"),
			pAcsEvt->m_DeviceID.m_s8ModuleID,
			pAcsEvt->m_DeviceID.m_s16ChannelID,
			pCallEvt->m_s32AcsEvtErrCode,
			*u32ErrCodeExt);
		g_pDlg->MessageBox(strErr, _T("MakeCall"), MB_OK|MB_ICONERROR);

		int iDevice = pAcsEvt->m_DeviceID.m_s16ChannelID;

		resetDeviceVoIP(iDevice);
		g_pDlg->refreshListIP(iDevice);
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_ALERTCALL event handler (received remote alert signaling (H.323: Q931 alerting; SIP: 1xx msg))
void OnAlertCall(Acs_Evt_t *pAcsEvt)
{
	Acs_CallControl_Data *pCallEvt = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);

	TRACE(_T("Device[%02d][%02d][%02d] call alerted (ret=%d)\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID,
		pCallEvt->m_s32AcsEvtErrCode);
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
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_CALLIN event handler (remote call incoming)
void OnCallIn(Acs_Evt_t *pAcsEvt)
{
	Acs_CallControl_Data * pCallEvt = (Acs_CallControl_Data *)FetchEventData(pAcsEvt);

	TRACE(_T("Device[%02d][%02d][%02d] incoming call\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID);

	if (pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_VOIP)
	{
		// update incoming call info
		ASSERT(pCallEvt->m_PrivData.m_u32DataSize == sizeof(VoIPCallPrivate_t));

		VoIPCallPrivate_t *paramVoIPCall = (VoIPCallPrivate_t *)&(pCallEvt->m_PrivData);

		int iDevice = pAcsEvt->m_DeviceID.m_s16ChannelID;

		g_deviceVoIP[iDevice].iProtocol = paramVoIPCall->m_s32Protocol;

		strcpy(g_deviceVoIP[iDevice].addrCaller.tszTelNo, pCallEvt->m_s8CallingNum);
		strcpy(g_deviceVoIP[iDevice].addrCaller.tszAddr, paramVoIPCall->m_s8CallerAddress);
		g_deviceVoIP[iDevice].addrCaller.port = (USHORT)paramVoIPCall->m_s32CallerPort;
		strcpy(g_deviceVoIP[iDevice].addrCaller.tszUserID, paramVoIPCall->m_s8CallerUserID);

		strcpy(g_deviceVoIP[iDevice].addrCallee.tszTelNo, pCallEvt->m_s8CalledNum);
		strcpy(g_deviceVoIP[iDevice].addrCallee.tszAddr, paramVoIPCall->m_s8CalleeAddress);
		g_deviceVoIP[iDevice].addrCallee.port = (USHORT)paramVoIPCall->m_s32CalleePort;
		strcpy(g_deviceVoIP[iDevice].addrCallee.tszUserID, paramVoIPCall->m_s8CalleeUserID);

		// media caps (supported in v2.1.2)
		char szMediaCaps[100] = {0};
		for (int iCap = 0; iCap < paramVoIPCall->m_u8MediaCapNum; ++iCap)
			sprintf(szMediaCaps+strlen(szMediaCaps), " %d", paramVoIPCall->m_u8MediaCapList[iCap]);
		TRACE(_T("Media Caps(%d):%s\n"), paramVoIPCall->m_u8MediaCapNum, szMediaCaps);

		g_pDlg->refreshListIP(iDevice);
	}
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

	// if has Voice Device binded, unbind it
	int iDeviceIP = pAcsEvt->m_DeviceID.m_s16ChannelID;
	int iDeviceVoc = g_deviceVoIP[iDeviceIP].iVoiceDevice;
	if (iDeviceVoc != -1)
	{
		MixerControlParam_t paramMixer = {0};

		// send SetParam command
		RetCode_t ret = XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[iDeviceIP].device,
			VOIP_PARAM_RTPMIXER, sizeof(paramMixer), &paramMixer);

		g_deviceVoIP[iDeviceIP].iVoiceDevice = -1;
		g_deviceVoc[iDeviceVoc].iVoIPDevice = -1;

		g_pDlg->refreshListIP(iDeviceIP);
		g_pDlg->refreshListVoc(iDeviceVoc);
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
/*	if (pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_VOIP)
	{
		int iDevice = pAcsEvt->m_DeviceID.m_s16ChannelID;
		g_pDlg->refreshListIP(iDevice);
		g_pDlg->refreshListVoc(g_deviceVoIP[iDevice].iVoiceDevice);
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
/*	if (pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_VOIP)
	{
		int iDeviceIP = pAcsEvt->m_DeviceID.m_s16ChannelID;
		int iDeviceVoc = g_deviceVoIP[iDeviceIP].iVoiceDevice;
		if (iDeviceVoc != -1)
		{
			g_deviceVoc[iDeviceVoc].iVoIPDevice = -1;
			g_pDlg->refreshListVoc(iDeviceVoc);
			g_deviceVoIP[iDeviceIP].iVoiceDevice = -1;
		}
		g_pDlg->refreshListIP(iDeviceIP);
		g_pDlg->refreshCtrlIP();
	}*/
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
		int iDevice = pAcsEvt->m_DeviceID.m_s16ChannelID;
		memset(&g_deviceVoc[iDevice].tszPlayFile, 0, sizeof(g_deviceVoc[iDevice].tszPlayFile));
		g_pDlg->GetDlgItem(IDC_BUTTON_PLAY)->SetWindowText(_T("Play"));
		g_pDlg->refreshListVoc(iDevice);
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_SENDIODATA event handler (H.245 UserInputIndication/SIP INFO/RFC 2833 DTMF)
void OnSendIOData(Acs_Evt_t *pAcsEvt)
{
	Acs_IO_Data *pIOEvt = (Acs_IO_Data *)FetchEventData(pAcsEvt);

	TRACE(_T("Device[%02d][%02d][%02d] send IO Data (type=%d) %s\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID,
		pIOEvt->m_u16IoType,
		pIOEvt->m_s32AcsEvtState?"succeeded":"failed");
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_RECVIODATA event handler (H.245 UserInputIndication/SIP INFO/RFC 2833 DTMF)
void OnRecvIOData(Acs_Evt_t *pAcsEvt)
{
	Acs_IO_Data *pIOEvt = (Acs_IO_Data *)FetchEventData(pAcsEvt);

	TRACE(_T("Device[%02d][%02d][%02d] receive IO Data\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID);

	int iDevice = pAcsEvt->m_DeviceID.m_s16ChannelID;

	int iDtmfLen = strlen(g_deviceVoIP[iDevice].szDtmf);
	if (iDtmfLen >= sizeof(g_deviceVoIP[iDevice].szDtmf)-1)
	{
		memset(g_deviceVoIP[iDevice].szDtmf, 0, sizeof(g_deviceVoIP[iDevice].szDtmf));
		iDtmfLen = 0;
	}

	char dtmf = '?';

	switch (pIOEvt->m_u16IoType)
	{
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
			XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDevice].device, XMS_IO_TYPE_VOIP_REGRESPONSE,
				sizeof(regResponse), &regResponse);
		}
		break;
	case XMS_IO_TYPE_VOIP_REGSTATE:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_REGSTATE))
		{
			Acs_VoIP_REGSTATE *pRegState = (Acs_VoIP_REGSTATE *)FetchIOData(pAcsEvt);
			TRACE(_T("Client %s on slot(%d): %s@%s:%d\n"),
				pRegState->m_u8State?_T("registered"):_T("unregistered"),
				pRegState->m_u16SlotID,
				pRegState->m_s8TelNo, pRegState->m_s8Address, pRegState->m_u16Port);
		}
		break;
	case XMS_IO_TYPE_VOIP_H245UII:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_H245UII))
		{
			Acs_VoIP_H245UII *h245Uii = (Acs_VoIP_H245UII *)FetchIOData(pAcsEvt);
			dtmf = h245Uii->m_s8Signal;
			g_deviceVoIP[iDevice].szDtmf[iDtmfLen] = dtmf;
		}
		break;
	case XMS_IO_TYPE_VOIP_SIPINFO:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_SIPINFO))
		{
			Acs_VoIP_SIPINFO *sipInfo = (Acs_VoIP_SIPINFO *)FetchIOData(pAcsEvt);
			if (strcmp(sipInfo->m_s8ContentType, "application/dtmf") == 0)
				sscanf(sipInfo->m_s8Body, "dtmf=%c", &dtmf);
			g_deviceVoIP[iDevice].szDtmf[iDtmfLen] = dtmf;
		}
		break;
	case XMS_IO_TYPE_VOIP_RTPDTMF:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_RTPDTMF))
		{
			Acs_VoIP_RTPDTMF *rtpDtmf = (Acs_VoIP_RTPDTMF *)FetchIOData(pAcsEvt);
			dtmf = rtpDtmf->m_s8EventChar;
			g_deviceVoIP[iDevice].szDtmf[iDtmfLen] = dtmf;
		}
		break;
	case XMS_IO_TYPE_VOIP_RTPTONE:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_RTPTONE))
		{
			Acs_VoIP_RTPTONE *rtpTone = (Acs_VoIP_RTPTONE *)FetchIOData(pAcsEvt);
		}
		break;
	case XMS_IO_TYPE_VOIP_REFER_NOTIFY:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_ReferResult))
		{
			Acs_VoIP_ReferResult *pTransferResult = (Acs_VoIP_ReferResult *)FetchIOData(pAcsEvt);
			TRACE("XMS_IO_TYPE_VOIP_REFER_NOTIFY state:%d reason:%d\n", pTransferResult->m_u8State, pTransferResult->m_u8Reason);
			if(pTransferResult->m_u8State==17)
			{
				if(pTransferResult->m_u8Reason==23 || pTransferResult->m_u8Reason==24)
				{
					RetCode_t ret = XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[iDevice].device, 0, NULL);
				}
				else
				{
					VoIPCallModifyPrivate_t callModify = {0};
					callModify.m_PrivateData.m_u32DataSize = sizeof(VoIPCallModifyPrivate_t);
					callModify.m_u8MediaCapNum = 0;
					// set media mode to send/recv
					callModify.u8MediaMode = 0;
					
					RetCode_t ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDevice].device, XMS_IO_TYPE_VOIP_CALLMODIFY, sizeof(VoIPCallModifyPrivate_t), (void*)&callModify);
				}
			}
		}
		break;
	}

	if (pIOEvt->m_u16IoType != XMS_IO_TYPE_VOIP_REGREQUEST &&
		pIOEvt->m_u16IoType != XMS_IO_TYPE_VOIP_REGSTATE)
		g_pDlg->refreshListIP(iDevice);
}

//////////////////////////////////////////////////////////////////////////
// XMS Join Conference Event Handler
void OnJoinConf(Acs_Evt_t *pAcsEvt)
{
}

//////////////////////////////////////////////////////////////////////////
// Get Param Event Handler
void OnGetParam(Acs_Evt_t *pAcsEvt)
{
	TRACE(_T("Device[%02d][%02d][%02d] receive GetParam\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID);

	if (g_pDlg->m_pdlgRtp->GetSafeHwnd() == NULL)
		return;

	Acs_ParamProc_Data *pParamEvt = (Acs_ParamProc_Data *)FetchEventData(pAcsEvt);
	g_pDlg->m_pdlgRtp->SendMessage(UM_UPDATEDATA, pParamEvt->m_u16ParamCmdType, (LPARAM)FetchParamData(pAcsEvt));
}
