#include "stdafx.h"

#include "XMSData.h"

// XMS service handle
ACSHandle_t g_acsHandle = NULL;

// Board Device number
int g_iBoardDevNum = 0;

// VoIP Device number
int g_iVoIPDevNum = 0;

// RTP Device number
int g_iRTPDevNum = 0;

// Voice Device number
int g_iVocDevNum = 0;

// Interface Device number
int g_iTrunkDevNum = 0;

// Conference Device number
int g_iConfDevNum = 0;

DJ_U32 MAX_DEVICE_VOIP=30*MAX_DEVICE_BOARD;
// Board Device
DeviceID_t g_deviceBoard[MAX_DEVICE_BOARD];

// VoIP Device data struct
//XMS_VOIP_DEVICE g_deviceVoIP[MAX_DEVICE_VOIP];

// VoIP Device data struct
XMS_VOIP_DEVICE *g_deviceVoIP=NULL;
// RTP Device data struct
//XMS_RTP_DEVICE g_deviceRTP[MAX_DEVICE_VOIP];
// RTP Device data struct
XMS_RTP_DEVICE *g_deviceRTP=NULL;

// VoIP Registration slot table
XMS_VOIP_REG g_ipRegSlot[MAX_VOIP_REG];

// Voice Device data struct
XMS_VOICE_DEVICE g_deviceVoc[MAX_DEVICE_VOICE];

// Interface Device data struct
XMS_INTERFACE_DEVICE g_deviceTrunk[MAX_DEVICE_INTERFACE];

// Conference Device data struct
XMS_CONF_DEVICE g_deviceConf[MAX_DEVICE_CONF];

// device subtype string
LPCTSTR g_pszDevSubName[] =
{
	_T("BASE"),
	_T("ANALOG_TRUNK"),
	_T("ANALOG_USER"),
	_T("ANALOG_HIZ"),
	_T("ANALOG_EMPTY"),
	_T("E1_PCM"),
	_T("E1_CAS"),
	_T("E1_DSS1"),
	_T("E1_SS7_TUP"),
	_T("E1_SS7_ISUP"),
	_T("ANALOG_VOC2W"),
	_T("ANALOG_VOC4W"),
	_T("ANALOG_EM"),
	_T("ANALOG_MAG"),
	_T("E1_DCH"),
	_T("E1_BCH"),
	_T("UNUSABLE")
};

// device common state string
LPCTSTR g_pszDevStateName[] =
{
	_T("STATE_START"),
	_T("FREE"),
	_T("LOCAL_BLOCK"),
	_T("REMOTE_BLOCK"),
	_T("BLOCK"),
	_T("UNAVAILABLE"),
	_T("CALLOUT"),
	_T("CALLIN"),
	_T("ALERTING"),
	_T("CONNECT"),
	_T("DISCONNECT"),
	_T("WAIT_FREE")
};

//////////////////////////////////////////////////////////////////////////
// reset IP Device struct
void resetDeviceVoIP(int iDevice)
{
	g_deviceVoIP[iDevice].iProtocol = 0;
	g_deviceVoIP[iDevice].iState = DCS_FREE;
	memset(&g_deviceVoIP[iDevice].tszPeerTelNo, 0, sizeof(g_deviceVoIP[iDevice].tszPeerTelNo));
	memset(&g_deviceVoIP[iDevice].szDtmf, 0, sizeof(g_deviceVoIP[iDevice].szDtmf));
	g_deviceVoIP[iDevice].iPeerDevice = -1;
	g_deviceVoIP[iDevice].iVocDevice = -1;
	g_deviceVoIP[iDevice].iTranferSrcDev = -1;
	g_deviceVoIP[iDevice].iRTPDevice = -1;
}

//////////////////////////////////////////////////////////////////////////
// reset RTP Device struct
void resetDeviceRTP(int iDevice)
{
	XMS_RTP_DEVICE* pRTP = &g_deviceRTP[iDevice];
	//memset(pRTP, 0, sizeof(XMS_RTP_DEVICE));
	pRTP->iState = DCS_FREE;
}

//////////////////////////////////////////////////////////////////////////
// reset Voice Device struct
void resetDeviceVoc(int iDevice)
{
	memset(&g_deviceVoc[iDevice].tszPlayFile, 0, sizeof(g_deviceVoc[iDevice].tszPlayFile));
	memset(&g_deviceVoc[iDevice].tszRecordFile, 0, sizeof(g_deviceVoc[iDevice].tszRecordFile));
	g_deviceVoc[iDevice].iTrunkDevice = -1;
	g_deviceVoc[iDevice].iVoIPDevice = -1;
}

//////////////////////////////////////////////////////////////////////////
// reset Trunk Device struct
void resetDeviceTrunk(int iDevice)
{
	g_deviceTrunk[iDevice].iState = DCS_FREE;
	memset(g_deviceTrunk[iDevice].szCallerNum, 0, sizeof(g_deviceTrunk[iDevice].szCallerNum));
	memset(g_deviceTrunk[iDevice].szCalleeNum, 0, sizeof(g_deviceTrunk[iDevice].szCalleeNum));
	memset(g_deviceTrunk[iDevice].szDtmf, 0, sizeof(g_deviceTrunk[iDevice].szDtmf));
	g_deviceTrunk[iDevice].iVocDevice = -1;
	g_deviceTrunk[iDevice].iVoIPDevice = -1;
}

//////////////////////////////////////////////////////////////////////////
// reset Conference Device struct
void resetDeviceConf(int iDevice)
{
	g_deviceConf[iDevice].iMemberCnt = 0;
	memset(&g_deviceConf[iDevice].iMember , -1, sizeof(g_deviceConf[iDevice].iMember));
}

//////////////////////////////////////////////////////////////////////////
// map XMS Device to list index
int mapDeviceItem(const DeviceID_t *pDevice)
{
/*	int iDevice;

	switch (pDevice->m_s16DeviceMain)
	{
	case XMS_DEVMAIN_VOICE:
		for (iDevice = 0; iDevice < g_iVocDevNum; ++iDevice)
		{
			if (g_deviceVoc[iDevice].device.m_s8ModuleID == pDevice->m_s8ModuleID &&
				g_deviceVoc[iDevice].device.m_s16ChannelID == pDevice->m_s16ChannelID)
				return iDevice;
		}
		break;

	case XMS_DEVMAIN_INTERFACE_CH:
		for (iDevice = 0; iDevice < g_iTrunkDevNum; ++iDevice)
		{
			if (g_deviceTrunk[iDevice].device.m_s8ModuleID == pDevice->m_s8ModuleID &&
				g_deviceTrunk[iDevice].device.m_s16ChannelID == pDevice->m_s16ChannelID)
				return iDevice;
		}
		break;

	case XMS_DEVMAIN_VOIP:
		for (iDevice = 0; iDevice < g_iVoIPDevNum; ++iDevice)
		{
			if (g_deviceVoIP[iDevice].device.m_s8ModuleID == pDevice->m_s8ModuleID &&
				g_deviceVoIP[iDevice].device.m_s16ChannelID == pDevice->m_s16ChannelID)
				return iDevice;
		}
		break;
	}

	return -1;*/
	return pDevice->m_s16ChannelID;
}
