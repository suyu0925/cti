// XMSEventHandler.cpp : implementation file
//

#include "stdafx.h"

#include "XMSVoIPGateway.h"
#include "XMSVoIPGatewayDlg.h"

#include "XMSEventHandler.h"
#include "XMSData.h"

CXMSVoIPGatewayDlg *g_pDlg = NULL;

RetCode_t linkDevice(XMS_VOIP_DEVICE *devIP, XMS_VOICE_DEVICE *devVoc);
RetCode_t linkDevice(XMS_INTERFACE_DEVICE *devTrk, XMS_VOICE_DEVICE *devVoc);
RetCode_t unlinkDevice(XMS_VOIP_DEVICE *devIP, XMS_VOICE_DEVICE *devVoc);
RetCode_t unlinkDevice(XMS_INTERFACE_DEVICE *devTrk, XMS_VOICE_DEVICE *devVoc);

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
// XMS main event handler
DJ_Void XMSEventHandler(DJ_U32 u32EsrParam)
{
	if (g_pDlg == NULL)
		g_pDlg = (CXMSVoIPGatewayDlg *)AfxGetMainWnd();

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

	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_OPEN_STREAM event handler
void OnOpenStream(Acs_Evt_t *pAcsEvt)
{
	TRACE(_T("XMS service opened (ret=%d)\n"), pAcsEvt->m_u32EsrParam);

	g_pDlg->GetDlgItem(IDC_BUTTON_INIT)->SetWindowText(_T("Close System"));

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

	if (pAcsDevList->m_s32ModuleID != g_pDlg->m_iDSP)
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
	case XMS_DEVMAIN_CONFERENCE:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_QUERY_DEVICE_END event handler
void OnQueryDeviceEnd(Acs_Evt_t *pAcsEvt)
{
	TRACE(_T("Device query end\n"));

	RetCode_t ret;

	// init device list
	g_pDlg->initIPList();
	g_pDlg->initTrunkList();

	// open all Board devices
	for (int iDevice = 0; iDevice < g_iBoardDevNum; ++iDevice)
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
		ret = XMS_ctsOpenDevice(g_acsHandle, &g_deviceVoIP[iDevice].device, NULL);
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
	for (iDevice = 0; iDevice < g_iTrunkDevNum; ++iDevice)
	{
		// opened already?
		if (g_deviceTrunk[iDevice].bOpened)
			continue;

		// send open device comannd
		ret = XMS_ctsOpenDevice(g_acsHandle, &g_deviceTrunk[iDevice].device, NULL);
	}
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
//			int iDeviceIP = mapDeviceItem(&pAcsEvt->m_DeviceID);
			int iDeviceIP = pAcsEvt->m_DeviceID.m_s16ChannelID;
			OnDeviceStateVoIP(iDeviceIP, pDeviceState->m_s32DeviceState);
		}
		break;
	case XMS_DEVMAIN_INTERFACE_CH:
		{
//			int iDeviceTrk = mapDeviceItem(&pAcsEvt->m_DeviceID);
			int iDeviceTrk = pAcsEvt->m_DeviceID.m_s16ChannelID;
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

			if (g_pDlg->m_bEC)
			{
				CmdParamData_Voice_t paramVoc = {0};
				paramVoc.m_u8InputCtrlValid = TRUE;
				paramVoc.m_VocInputControl.m_u16FixGain = 0x400;
				paramVoc.m_VocInputControl.m_u8EcEnable = TRUE;
				paramVoc.m_VocInputControl.m_u8EcRefType = XMS_EC_REF_FROM_OUTPUT;
				paramVoc.m_VocInputControl.m_u16EcRefCh = g_deviceVoc[iDeviceVoc].device.m_s16ChannelID;

				XMS_ctsSetParam(g_acsHandle, &g_deviceVoc[iDeviceVoc].device, VOC_PARAM_UNIPARAM,
					sizeof(paramVoc), &paramVoc);
			}

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

	// refresh Interface Device list
	g_pDlg->refreshListTrunk(iDeviceTrk);
}

//////////////////////////////////////////////////////////////////////////
// VoIP Device state change event handler
void OnDeviceStateVoIP(int iDeviceIP, int iState)
{
	RetCode_t ret;

	g_deviceVoIP[iDeviceIP].iState = iState;

	switch (iState)
	{
	case DCS_FREE:
//		g_deviceVoIP[iDeviceIP].iProtocol = 0;
		memset(&g_deviceVoIP[iDeviceIP].addrCaller, 0, sizeof(XMS_VOIP_ADDR));
		memset(&g_deviceVoIP[iDeviceIP].addrCallee, 0, sizeof(XMS_VOIP_ADDR));
		memset(&g_deviceVoIP[iDeviceIP].szDtmf, 0, sizeof(g_deviceVoIP[iDeviceIP].szDtmf));
		break;
	case DCS_CALLOUT:
		break;
	case DCS_CALLIN:
		break;
	case DCS_ALERTING:
		break;
	case DCS_CONNECT:
		{
			// find and link with a free Voice Device
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
			}
		}
		break;
	case DCS_DISCONNECT:
		{
			// unlink Voice Device
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
			}
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

	// make call fail?
	if (pCallEvt->m_s32AcsEvtErrCode != 0)
	{
		int iDeviceIP = pAcsEvt->m_DeviceID.m_s16ChannelID;
		int iDeviceTrk = g_deviceVoIP[iDeviceIP].iTrunkDevice;
		if (iDeviceTrk != -1 && g_deviceTrunk[iDeviceTrk].iState == DCS_CONNECT)
		{
			int iDeviceTrkVoc = initTrunkVoice(iDeviceTrk);
			if (iDeviceTrkVoc != -1)
			{
				// play busy tone on trunk device
				char tone = 'I';
				RetCode_t ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoc[iDeviceTrkVoc].device,
					XMS_IO_TYPE_GTG, sizeof(tone), &tone);
			}
		}

		CString strErr;
		strErr.Format(_T("Device[%d][%d] make call failed! (ret=%d)"),
			pAcsEvt->m_DeviceID.m_s8ModuleID,
			pAcsEvt->m_DeviceID.m_s16ChannelID,
			pCallEvt->m_s32AcsEvtErrCode);
		g_pDlg->MessageBox(strErr, _T("MakeCall"), MB_OK|MB_ICONERROR);

		if (pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_VOIP)
		{
//			int iDevice = mapDeviceItem(&pAcsEvt->m_DeviceID);

			g_deviceVoIP[iDeviceIP].iTrunkDevice = -1;
//			g_deviceTrunk[iDeviceTrk].iVoIPDevice = -1;

//			resetDeviceVoIP(iDeviceIP);
			g_pDlg->refreshListIP(iDeviceIP);
		}
	}
	else // make call ok
	{
		if (pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_INTERFACE_CH)
		{
//			int iDeviceTrk = mapDeviceItem(&pAcsEvt->m_DeviceID);
			int iDeviceTrk = pAcsEvt->m_DeviceID.m_s16ChannelID;

			// if a VoIP Device is to be linked, link it
			int iDeviceIP = g_deviceTrunk[iDeviceTrk].iVoIPDevice;
			if (iDeviceIP != -1)
			{
				XMS_ctsAnswerCallIn(g_acsHandle, &g_deviceVoIP[iDeviceIP].device, NULL);

				// Note: link with the Voice Device attached to the VoIP Device actually
				int iDeviceVoc = g_deviceVoIP[iDeviceIP].iVocDevice;
				if (iDeviceVoc != -1)
				{
					// send link device command
					RetCode_t ret = linkDevice(&g_deviceTrunk[iDeviceTrk], &g_deviceVoc[iDeviceVoc]);

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
	}
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

	switch (pAcsEvt->m_DeviceID.m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
		{
			// update incoming call info
			ASSERT(pCallEvt->m_PrivData.m_u32DataSize == sizeof(VoIPCallPrivate_t));

			VoIPCallPrivate_t *paramVoIPCall = (VoIPCallPrivate_t *)&(pCallEvt->m_PrivData);

//			int iDeviceIP = mapDeviceItem(&pAcsEvt->m_DeviceID);
			int iDeviceIP = pAcsEvt->m_DeviceID.m_s16ChannelID;

			g_deviceVoIP[iDeviceIP].iProtocol = paramVoIPCall->m_s32Protocol;

			strcpy(g_deviceVoIP[iDeviceIP].addrCaller.tszTelNo, pCallEvt->m_s8CallingNum);
			strcpy(g_deviceVoIP[iDeviceIP].addrCaller.tszAddr, paramVoIPCall->m_s8CallerAddress);
			g_deviceVoIP[iDeviceIP].addrCaller.port = (USHORT)paramVoIPCall->m_s32CallerPort;
			strcpy(g_deviceVoIP[iDeviceIP].addrCaller.tszUserID, paramVoIPCall->m_s8CallerUserID);

			strcpy(g_deviceVoIP[iDeviceIP].addrCallee.tszTelNo, pCallEvt->m_s8CalledNum);
			strcpy(g_deviceVoIP[iDeviceIP].addrCallee.tszAddr, paramVoIPCall->m_s8CalleeAddress);
			g_deviceVoIP[iDeviceIP].addrCallee.port = (USHORT)paramVoIPCall->m_s32CalleePort;
			strcpy(g_deviceVoIP[iDeviceIP].addrCallee.tszUserID, paramVoIPCall->m_s8CalleeUserID);

			g_pDlg->refreshListIP(iDeviceIP);

//			RetCode_t ret = XMS_ctsAnswerCallIn(g_acsHandle, &g_deviceVoIP[iDevice].device, NULL);

			for (int iDeviceTrk = 0; iDeviceTrk < g_iTrunkDevNum; ++iDeviceTrk)
			{
				if (strcmp(g_deviceVoIP[iDeviceIP].addrCallee.tszTelNo, g_deviceTrunk[iDeviceTrk].szTelNo) == 0)
					break;
			}

			if (iDeviceTrk >= g_iTrunkDevNum)
			{
				XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[iDeviceIP].device, 0, NULL);
				return;
			}

			// send make call command
			RetCode_t ret = XMS_ctsMakeCallOut(g_acsHandle, &g_deviceTrunk[iDeviceTrk].device, "", "", NULL);
			g_deviceVoIP[iDeviceIP].iTrunkDevice = iDeviceTrk;
			g_deviceTrunk[iDeviceTrk].iVoIPDevice = iDeviceIP;

			OnDeviceStateTrunk(iDeviceTrk, DCS_CALLOUT);
		}
		break;

	case XMS_DEVMAIN_INTERFACE_CH:
		switch (pAcsEvt->m_DeviceID.m_s16DeviceSub)
		{
		case XMS_DEVSUB_ANALOG_USER:
			{
				// find and link with a free Voice Device
//				int iDeviceTrk = mapDeviceItem(&pAcsEvt->m_DeviceID);
				int iDeviceTrk = pAcsEvt->m_DeviceID.m_s16ChannelID;

				if (g_deviceTrunk[iDeviceTrk].iState == DCS_CALLOUT)
				{
					// if a VoIP Device is to be linked, link it
					int iDeviceIP = g_deviceTrunk[iDeviceTrk].iVoIPDevice;
					if (iDeviceIP != -1)
					{
						XMS_ctsAnswerCallIn(g_acsHandle, &g_deviceVoIP[iDeviceIP].device, NULL);

						// Note: link with the Voice Device attached to the VoIP Device actually
						int iDeviceVoc = g_deviceVoIP[iDeviceIP].iVocDevice;
						if (iDeviceVoc != -1)
						{
							// send link device command
							RetCode_t ret = linkDevice(&g_deviceTrunk[iDeviceTrk], &g_deviceVoc[iDeviceVoc]);

//							g_deviceVoIP[iDeviceIP].iTrunkDevice = iDeviceTrk;
//							g_deviceVoIP[iDeviceIP].iVocDevice = iDeviceVoc;
						}
					}
					else
					{
						// find and link with a free Voice Device
						int iDeviceTrkVoc = initTrunkVoice(iDeviceTrk);
					}
				}
				else
				{
					int iDeviceVoc = initTrunkVoice(iDeviceTrk);

					if (iDeviceVoc != -1)
					{
						// play dial tone
						char tone = 'G';
						RetCode_t ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoc[iDeviceVoc].device,
							XMS_IO_TYPE_GTG, sizeof(tone), &tone);
					}
				}
			}
			break;
		}
		break;
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
			// if linked with Interface Device, unlink it
			// Note: unlink the Voice Device attached to the Interface Device actually
//			int iDeviceIP = mapDeviceItem(&pAcsEvt->m_DeviceID);
			int iDeviceIP = pAcsEvt->m_DeviceID.m_s16ChannelID;

			int iDeviceTrk = g_deviceVoIP[iDeviceIP].iTrunkDevice;
			if (iDeviceTrk != -1)
			{
				if (g_deviceTrunk[iDeviceTrk].iState == DCS_CALLOUT)
				{
					XMS_ctsClearCall(g_acsHandle, &g_deviceTrunk[iDeviceTrk].device, 0, NULL);
					OnDeviceStateTrunk(iDeviceTrk, DCS_FREE);
				}
				else
				{
					int iDeviceTrkVoc = initTrunkVoice(iDeviceTrk);
					if (iDeviceTrkVoc != -1)
					{
						// play busy tone on trunk device
						char tone = 'I';
						RetCode_t ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoc[iDeviceTrkVoc].device,
							XMS_IO_TYPE_GTG, sizeof(tone), &tone);
					}
				}

				g_deviceVoIP[iDeviceIP].iTrunkDevice = -1;
				g_deviceTrunk[iDeviceTrk].iVoIPDevice = -1;

				g_pDlg->refreshListTrunk(iDeviceTrk);
			}

			int iDeviceIPVoc = g_deviceVoIP[iDeviceIP].iVocDevice;
			if (iDeviceIPVoc != -1)
			{
				// send unlink device command
				ret = unlinkDevice(&g_deviceVoIP[iDeviceIP], &g_deviceVoc[iDeviceIPVoc]);
			}
		}
		break;
	case XMS_DEVMAIN_INTERFACE_CH:
		{
			// if linked with Voice Device, unlink it
//			int iDeviceTrk = mapDeviceItem(&pAcsEvt->m_DeviceID);
			int iDeviceTrk = pAcsEvt->m_DeviceID.m_s16ChannelID;

			memset(&g_deviceTrunk[iDeviceTrk].szCallerNum, 0, sizeof(g_deviceTrunk[iDeviceTrk].szCallerNum));
			memset(&g_deviceTrunk[iDeviceTrk].szCalleeNum, 0, sizeof(g_deviceTrunk[iDeviceTrk].szCalleeNum));
			memset(&g_deviceTrunk[iDeviceTrk].szDtmf, 0, sizeof(g_deviceTrunk[iDeviceTrk].szDtmf));

			int iDeviceVoc = g_deviceTrunk[iDeviceTrk].iVocDevice;
			if (iDeviceVoc != -1)
			{
				if (pAcsEvt->m_DeviceID.m_s16DeviceSub == XMS_DEVSUB_ANALOG_USER)
				{
					char tone;
					// stop playing tone
					ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoc[iDeviceVoc].device,
						XMS_IO_TYPE_GTG, 0, &tone);
				}

				// send unlink device command
				ret = unlinkDevice(&g_deviceTrunk[iDeviceTrk], &g_deviceVoc[iDeviceVoc]);
			}

			// unlink Voice Device
			int iDeviceIP = g_deviceTrunk[iDeviceTrk].iVoIPDevice;
			if (iDeviceIP != -1)
			{
				int iDeviceVoc = g_deviceVoIP[iDeviceIP].iVocDevice;
				if (iDeviceVoc != -1)
				{
					ret = unlinkDevice(&g_deviceTrunk[iDeviceTrk], &g_deviceVoc[iDeviceVoc]);
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

				// drop ip call attached
				ret = XMS_ctsClearCall(g_acsHandle, &g_deviceVoIP[iDeviceIP].device, 0, NULL);
				g_deviceTrunk[iDeviceTrk].iVoIPDevice = -1;
				g_deviceVoIP[iDeviceIP].iTrunkDevice = -1;
			}

			g_pDlg->refreshListTrunk(iDeviceTrk);
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

	switch (pAcsEvt->m_DeviceID.m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
		{
			// VoIP Device linked with Interface Device
//			int iDeviceIP = mapDeviceItem(&pAcsEvt->m_DeviceID);
			int iDeviceIP = pAcsEvt->m_DeviceID.m_s16ChannelID;
			int iDeviceTrk = g_deviceVoIP[iDeviceIP].iTrunkDevice;

			g_pDlg->refreshListIP(iDeviceIP);

			if (iDeviceTrk != -1)
				g_pDlg->refreshListTrunk(g_deviceVoIP[iDeviceIP].iTrunkDevice);
		}
		break;
	case XMS_DEVMAIN_INTERFACE_CH:
		{
			// Interface Device linked with Voice Device
			// nothing to do
		}
		break;
	}
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
//			int iDeviceIP = mapDeviceItem(&pAcsEvt->m_DeviceID);
			int iDeviceIP = pAcsEvt->m_DeviceID.m_s16ChannelID;
			int iDeviceTrk = g_deviceVoIP[iDeviceIP].iTrunkDevice;

			if (iDeviceTrk != -1)
			{
//				g_deviceTrunk[iDeviceTrk].iVoIPDevice = -1;
				g_pDlg->refreshListTrunk(iDeviceTrk);
			}

//			g_deviceVoIP[iDeviceIP].iTrunkDevice = -1;
			g_pDlg->refreshListIP(iDeviceIP);
		}
		break;
	case XMS_DEVMAIN_INTERFACE_CH:
		{
			// Interface Device unlinked with Voice Device
//			int iDeviceTrk = mapDeviceItem(&pAcsEvt->m_DeviceID);
			int iDeviceTrk = pAcsEvt->m_DeviceID.m_s16ChannelID;
			int iDeviceVoc = g_deviceTrunk[iDeviceTrk].iVocDevice;

			if (iDeviceVoc != -1)
			{
//				g_deviceTrunk[iDeviceTrk].iVocDevice = -1;
				g_pDlg->refreshListTrunk(iDeviceTrk);

//				g_deviceVoc[iDeviceVoc].iTrunkDevice = -1;
			}
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
//		int iDevice = mapDeviceItem(&pAcsEvt->m_DeviceID);
		int iDevice = pAcsEvt->m_DeviceID.m_s16ChannelID;
		memset(&g_deviceVoc[iDevice].tszPlayFile, 0, sizeof(g_deviceVoc[iDevice].tszPlayFile));
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS_EVT_RECVIODATA event handler (H.245 UserInputIndication/SIP INFO/RFC 2833 DTMF)
void OnRecvIOData(Acs_Evt_t *pAcsEvt)
{
//	Acs_IO_Data *pIOEvt = (Acs_IO_Data *)FetchEventData(pAcsEvt);

	TRACE(_T("Device[%02d][%02d][%02d] receive IO Data\n"),
		pAcsEvt->m_DeviceID.m_s8ModuleID,
		pAcsEvt->m_DeviceID.m_s16DeviceMain,
		pAcsEvt->m_DeviceID.m_s16ChannelID);

	switch (pAcsEvt->m_DeviceID.m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOIP:
		{
//			int iDeviceIP = mapDeviceItem(&pAcsEvt->m_DeviceID);
			int iDeviceIP = pAcsEvt->m_DeviceID.m_s16ChannelID;
			OnRecvIODataVoIP(iDeviceIP, pAcsEvt);
		}
		break;

	case XMS_DEVMAIN_VOICE:
		{
//			int iDeviceVoc = mapDeviceItem(&pAcsEvt->m_DeviceID);
			int iDeviceVoc = pAcsEvt->m_DeviceID.m_s16ChannelID;
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
	case XMS_IO_TYPE_VOIP_H245UII:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_H245UII))
		{
			Acs_VoIP_H245UII *h245Uii = (Acs_VoIP_H245UII *)FetchIOData(pAcsEvt);
			dtmf = h245Uii->m_s8Signal;
	
			g_deviceVoIP[iDeviceIP].szDtmf[iDtmfLen] = dtmf;
		}
		break;
	case XMS_IO_TYPE_VOIP_SIPINFO:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_SIPINFO))
		{
			Acs_VoIP_SIPINFO *sipInfo = (Acs_VoIP_SIPINFO *)FetchIOData(pAcsEvt);
			if (strcmp(sipInfo->m_s8ContentType, "application/dtmf") == 0)
				sscanf(sipInfo->m_s8Body, "dtmf=%c", &dtmf);

			g_deviceVoIP[iDeviceIP].szDtmf[iDtmfLen] = dtmf;
		}
		break;
	case XMS_IO_TYPE_VOIP_RTPDTMF:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_RTPDTMF))
		{
			Acs_VoIP_RTPDTMF *rtpDtmf = (Acs_VoIP_RTPDTMF *)FetchIOData(pAcsEvt);
			dtmf = rtpDtmf->m_s8EventChar;

			g_deviceVoIP[iDeviceIP].szDtmf[iDtmfLen] = dtmf;
		}
		break;
	case XMS_IO_TYPE_VOIP_REGREQUEST:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_REGSTATE))
		{
			// check client's info
			Acs_VoIP_REGSTATE *pRegRequest = (Acs_VoIP_REGSTATE *)FetchIOData(pAcsEvt);

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
			XMS_ctsSendIOData(g_acsHandle, &g_deviceVoIP[iDeviceIP].device, XMS_IO_TYPE_VOIP_REGRESPONSE,
				sizeof(regResponse), &regResponse);
		}
		break;
	case XMS_IO_TYPE_VOIP_REGSTATE:
		if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_REGSTATE))
		{
			Acs_VoIP_REGSTATE *pRegState = (Acs_VoIP_REGSTATE *)FetchIOData(pAcsEvt);
			iDeviceIP = pRegState->m_u16SlotID % g_iVoIPDevNum;
			if (pRegState->m_u8State)
			{
				strcpy(g_deviceVoIP[iDeviceIP].addrRegClient.tszTelNo, pRegState->m_s8TelNo);
				strcpy(g_deviceVoIP[iDeviceIP].addrRegClient.tszUserID, pRegState->m_s8UserID);
				strcpy(g_deviceVoIP[iDeviceIP].addrRegClient.tszAddr, pRegState->m_s8Address);
				g_deviceVoIP[iDeviceIP].addrRegClient.port = pRegState->m_u16Port;
				g_deviceVoIP[iDeviceIP].iProtocol = pRegState->m_u8Protocol;
			}
			else
			{
				memset(&g_deviceVoIP[iDeviceIP].addrRegClient, 0, sizeof(g_deviceVoIP[iDeviceIP].addrRegClient));
				g_deviceVoIP[iDeviceIP].iProtocol = 0;
			}
		}
		break;
	}

	// a dtmf string ends with '#' specifies the index of the Interface Device to call out with
/*	if (dtmf == '#' && g_deviceVoIP[iDeviceIP].iTrunkDevice == -1)
	{
		char *delim = strchr(g_deviceVoIP[iDeviceIP].szDtmf, '*');
		if (delim == NULL)
		{
			memset(g_deviceVoIP[iDeviceIP].szDtmf, 0, sizeof(g_deviceVoIP[iDeviceIP].szDtmf));
		}
		else
		{
			DeviceID_t deviceTrk;
			deviceTrk.m_s16DeviceMain = XMS_DEVMAIN_INTERFACE_CH;
			sscanf(g_deviceVoIP[iDeviceIP].szDtmf, "%d*%d#", &deviceTrk.m_s8ModuleID, &deviceTrk.m_s16ChannelID);

//			int iDeviceTrk = mapDeviceItem(&deviceTrk);
			int iDeviceTrk = deviceTrk.m_s16ChannelID;

			// send make call command
			RetCode_t ret = XMS_ctsMakeCallOut(g_acsHandle, &g_deviceTrunk[iDeviceTrk].device, "", "", NULL);
			g_deviceVoIP[iDeviceIP].iTrunkDevice = iDeviceTrk;
			g_deviceTrunk[iDeviceTrk].iVoIPDevice = iDeviceIP;
		}
	}
*/
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

		char dtmf = *(char *)FetchIOData(pAcsEvt);

		int iDtmfLen = strlen(g_deviceTrunk[iDeviceTrk].szDtmf);
		if (iDtmfLen >= sizeof(g_deviceTrunk[iDeviceTrk].szDtmf)-1)
		{
			memset(g_deviceTrunk[iDeviceTrk].szDtmf, 0, sizeof(g_deviceTrunk[iDeviceTrk].szDtmf));
			iDtmfLen = 0;
		}

		g_deviceTrunk[iDeviceTrk].szDtmf[iDtmfLen] = dtmf;

		g_pDlg->refreshListTrunk(iDeviceTrk);

		// a dtmf string ends with '#' specifies the callee ip address or telno to call out
		if (dtmf == '#' && g_deviceTrunk[iDeviceTrk].iVoIPDevice == -1)
		{
			// find a free VoIP Device to make call out
			for (int iDeviceIP = 0; iDeviceIP < g_iVoIPDevNum; ++iDeviceIP)
			{
				if (g_deviceVoIP[iDeviceIP].bOpened &&
					g_deviceVoIP[iDeviceIP].iTrunkDevice == -1)
				{
					break;
				}
			}

			// cannot find free VoIP Device
			if (iDeviceIP >= g_iVoIPDevNum)
				return;

			// fill IP call parameters
			VoIPCallPrivate_t paramVoIPCall = {0};
			paramVoIPCall.m_PrivateData.m_u32DataSize = sizeof(VoIPCallPrivate_t);

			int iProtocol = g_pDlg->GetDlgItem(IDC_RADIO_H323)->SendMessage(BM_GETCHECK);
			paramVoIPCall.m_s32Protocol = iProtocol != 0 ? XMS_VOIP_PROTOCOL_H323 : XMS_VOIP_PROTOCOL_SIP;

			CString strCalleeIP, strCalleeNum;

			if (strchr(g_deviceTrunk[iDeviceTrk].szDtmf, '*') != NULL)
			{
				// using ip address dial plan
				// to figure ip address string: remove '#' and replace '*' with '.'
				strCalleeIP = g_deviceTrunk[iDeviceTrk].szDtmf;
				strCalleeIP.Remove('#');
				strCalleeIP.Replace('*', '.');

				strcpy(paramVoIPCall.m_s8CalleeAddress, strCalleeIP);

				RetCode_t ret = XMS_ctsMakeCallOut(g_acsHandle, &g_deviceVoIP[iDeviceIP].device,
					"", "", (PrivateData_t *)&paramVoIPCall);
			}
			else
			{
				// using telno dial plan
				strCalleeNum = g_deviceTrunk[iDeviceTrk].szDtmf;
				strCalleeNum.Remove('#');

				// search registered ip client
				for (int iDeviceReg = 0; iDeviceReg < g_iVoIPDevNum; ++iDeviceReg)
				{
					if (strCalleeNum == g_deviceVoIP[iDeviceReg].addrRegClient.tszTelNo)
					{
						iDeviceIP = iDeviceReg;

						paramVoIPCall.m_s32Protocol = g_deviceVoIP[iDeviceReg].iProtocol;
						strcpy(paramVoIPCall.m_s8CalleeAddress, g_deviceVoIP[iDeviceReg].addrRegClient.tszAddr);
						paramVoIPCall.m_s32CalleePort = g_deviceVoIP[iDeviceReg].addrRegClient.port;
						strcpy(paramVoIPCall.m_s8CalleeUserID, g_deviceVoIP[iDeviceReg].addrRegClient.tszUserID);
						break;
					}
				}

				if (iDeviceReg >= g_iVoIPDevNum)
				{
					if (g_deviceTrunk[iDeviceTrk].iVocDevice != -1)
					{
						// play busy tone
						char tone = 'I';
						RetCode_t ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoc[iDeviceVoc].device,
							XMS_IO_TYPE_GTG, sizeof(tone), &tone);
					}
					return;
				}

				RetCode_t ret = XMS_ctsMakeCallOut(g_acsHandle, &g_deviceVoIP[iDeviceIP].device,
					"", (char *)(LPCTSTR)strCalleeNum, (PrivateData_t *)&paramVoIPCall);
			}

			if (g_deviceTrunk[iDeviceTrk].iVocDevice != -1)
			{
				// play ring-back tone
				char tone = 'H';
				RetCode_t ret = XMS_ctsSendIOData(g_acsHandle, &g_deviceVoc[iDeviceVoc].device,
					XMS_IO_TYPE_GTG, sizeof(tone), &tone);
			}

			// update call info
			g_deviceVoIP[iDeviceIP].iProtocol = paramVoIPCall.m_s32Protocol;
			strcpy(g_deviceVoIP[iDeviceIP].addrCallee.tszAddr, paramVoIPCall.m_s8CalleeAddress);
			g_deviceVoIP[iDeviceIP].addrCallee.port = (USHORT)paramVoIPCall.m_s32CalleePort;
			strcpy(g_deviceVoIP[iDeviceIP].addrCallee.tszUserID, paramVoIPCall.m_s8CalleeUserID);
			strcpy(g_deviceVoIP[iDeviceIP].addrCallee.tszTelNo, strCalleeNum);

			g_deviceVoIP[iDeviceIP].iTrunkDevice = iDeviceTrk;
			g_deviceTrunk[iDeviceTrk].iVoIPDevice = iDeviceIP;

			g_pDlg->refreshListIP(iDeviceIP);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// XMS Join Conference Event Handler
void OnJoinConf(Acs_Evt_t *pAcsEvt)
{
}
