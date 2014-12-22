#ifndef __XMSDATA_H__
#define __XMSDATA_H__

#include "DJAcsDataDef.h"

//////////////////////////////////////////////////////////////////////////
// XMS data definition

// Application ID of this demo
#define XMS_APP_ID				5

// max VoIP Device number in this demo
#define MAX_DEVICE_VOIP			30

// max VoIP Device number in this demo
#define MAX_DEVICE_VOICE		120

// max Conference Device number in this demo
#define MAX_DEVICE_CONF			64

// max conference member in this demo
#define MAX_CONF_MEMBER			10

// IP call party address struct
typedef struct XMS_VOIP_ADDR_TAG
{
	TCHAR	tszAddr[20];
	USHORT	port;
	TCHAR	tszUserID[40];
	TCHAR	tszTelNo[20];
} XMS_VOIP_ADDR;

// IP Device struct
typedef struct XMS_VOIP_DEVICE_TAG
{
	BOOL			bOpened;		// if opened
	DeviceID_t		device;			// XMS device id
	int				iProtocol;		// ip protocol (h.323/sip)
	int				iState;			// call state
	XMS_VOIP_ADDR	addrCaller;		// caller address
	XMS_VOIP_ADDR	addrCallee;		// callee address
	char			szDtmf[6];		// dtmf string
	int				iVoiceDevice;	// binded Voice Device index
} XMS_VOIP_DEVICE;

// Voice Device struct
typedef struct XMS_VOICE_DEVICE_TAG
{
	BOOL			bOpened;					// if opened
	DeviceID_t		device;						// XMS device id
	TCHAR			tszPlayFile[_MAX_PATH];		// play file name
	int				iSampleRate;				// play file sample rate (8k/6k)
	int				iCodec;						// play file codec (a law/u law)
	TCHAR			tszRecordFile[_MAX_PATH];	// record file name
	int				iVoIPDevice;				// binded IP Device index
} XMS_VOICE_DEVICE;

// Conference Device struct
typedef struct XMS_CONF_DEVICE_TAG
{
	BOOL			bOpened;		// if opened
	DeviceID_t		device;			// XMS device id
	int				iMemberCnt;		// members count
	int				iMember[MAX_CONF_MEMBER]; // conference member
} XMS_CONF_DEVICE;

// XMS service handle
extern ACSHandle_t g_acsHandle;

// IP Device number
extern int g_iVoIPDevNum;

// Voice Device number
extern int g_iVocDevNum;

// Conference Device number
extern int g_iConfDevNum;

// VoIP Device data struct
extern XMS_VOIP_DEVICE g_deviceVoIP[MAX_DEVICE_VOIP];

// Voice Device data struct
extern XMS_VOICE_DEVICE g_deviceVoc[MAX_DEVICE_VOICE];

// Conference Device data struct
extern XMS_CONF_DEVICE g_deviceConf[MAX_DEVICE_CONF];

//////////////////////////////////////////////////////////////////////////
// XMS data struct helper function
void resetDeviceVoIP(int iDevice);
void resetDeviceVoc(int iDevice);
void resetDeviceConf(int iDevice);

#endif
