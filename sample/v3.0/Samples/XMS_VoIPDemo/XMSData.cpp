#include "StdAfx.h"

#include "XMSData.h"
#include "DJAcsDevState.h"

// XMS service handle
ACSHandle_t g_acsHandle = NULL;

// IP Device number
int g_iVoIPDevNum = 0;

// Voice Device number
int g_iVocDevNum = 0;

// Conference Device number
int g_iConfDevNum = 0;

// VoIP Device data struct
XMS_VOIP_DEVICE g_deviceVoIP[MAX_DEVICE_VOIP];

// Voice Device data struct
XMS_VOICE_DEVICE g_deviceVoc[MAX_DEVICE_VOICE];

// Conference Device data struct
XMS_CONF_DEVICE g_deviceConf[MAX_DEVICE_CONF];

//////////////////////////////////////////////////////////////////////////
// reset IP Device struct
void resetDeviceVoIP(int iDevice)
{
	g_deviceVoIP[iDevice].iProtocol = 0;
	g_deviceVoIP[iDevice].iState = DCS_FREE;
	memset(&g_deviceVoIP[iDevice].addrCaller, 0, sizeof(XMS_VOIP_ADDR));
	memset(&g_deviceVoIP[iDevice].addrCallee, 0, sizeof(XMS_VOIP_ADDR));
	memset(&g_deviceVoIP[iDevice].szDtmf, 0, sizeof(g_deviceVoIP[iDevice].szDtmf));
	g_deviceVoIP[iDevice].iVoiceDevice = -1;
}

//////////////////////////////////////////////////////////////////////////
// reset Voice Device struct
void resetDeviceVoc(int iDevice)
{
	memset(&g_deviceVoc[iDevice].tszPlayFile, 0, sizeof(g_deviceVoc[iDevice].tszPlayFile));
	memset(&g_deviceVoc[iDevice].tszRecordFile, 0, sizeof(g_deviceVoc[iDevice].tszRecordFile));
	g_deviceVoc[iDevice].iVoIPDevice = -1;
}

//////////////////////////////////////////////////////////////////////////
// reset Conference Device struct
void resetDeviceConf(int iDevice)
{
	g_deviceConf[iDevice].iMemberCnt = 0;
	memset(&g_deviceConf[iDevice].iMember , -1, sizeof(g_deviceConf[iDevice].iMember));
}
