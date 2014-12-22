#ifndef __XMSDATA_H__
#define __XMSDATA_H__

#include "DJAcsAPIDef.h"
#include "DJAcsDevState.h"

//////////////////////////////////////////////////////////////////////////
// XMS data definition

// Application ID of this demo
#define XMS_APP_ID				6

// max Board Device number in this demo
#define MAX_DEVICE_BOARD		4

// max VoIP Device number in this demo
#define MAX_DEVICE_VOIP			(30*MAX_DEVICE_BOARD)

// max VoIP Device number in this demo
#define MAX_DEVICE_VOICE		(120*MAX_DEVICE_BOARD)

// max Interface Device number in this demo
#define MAX_DEVICE_INTERFACE	(120*MAX_DEVICE_BOARD)

// max Conference Device number in this demo
#define MAX_DEVICE_CONF			(64*MAX_DEVICE_BOARD)

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
	XMS_VOIP_ADDR	addrRegClient;	// registered client address
	XMS_VOIP_ADDR	addrCaller;		// caller address
	XMS_VOIP_ADDR	addrCallee;		// callee address
	char			szDtmf[10];		// dtmf string
	int				iTrunkDevice;	// linked Interface Device index
	int				iVocDevice;		// linked Voice Device index (which attached to Interface Device)
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
	int				iTrunkDevice;				// linked Interface Device index
	int				iVoIPDevice;				// linked VoIP Device index
} XMS_VOICE_DEVICE;

// Interface Device struct
typedef struct XMS_INTERFACE_DEVICE_TAG
{
	BOOL			bOpened;			// if opened
	DeviceID_t		device;				// XMS device id
	int				iState;				// device state
	char			szCallerNum[10];	// caller number
	char			szCalleeNum[10];	// callee number
	char			szDtmf[20];			// dtmf string
	int				iVocDevice;			// linked Voice Device index
	int				iVoIPDevice;		// linked VoIP Device index
	char			szTelNo[20];		// binded telephone number
} XMS_INTERFACE_DEVICE;

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

// Board Device number
extern int g_iBoardDevNum;

// IP Device number
extern int g_iVoIPDevNum;

// Voice Device number
extern int g_iVocDevNum;

// Interface Device number
extern int g_iTrunkDevNum;

// Conference Device number
extern int g_iConfDevNum;

// Board Device
extern DeviceID_t g_deviceBoard[MAX_DEVICE_BOARD];

// VoIP Device data struct
extern XMS_VOIP_DEVICE g_deviceVoIP[MAX_DEVICE_VOIP];

// Voice Device data struct
extern XMS_VOICE_DEVICE g_deviceVoc[MAX_DEVICE_VOICE];

// Interface Device data struct
extern XMS_INTERFACE_DEVICE g_deviceTrunk[MAX_DEVICE_INTERFACE];

// Conference Device data struct
extern XMS_CONF_DEVICE g_deviceConf[MAX_DEVICE_CONF];

// device subtype string
extern LPCTSTR g_pszDevSubName[];

// device common state string
extern LPCTSTR g_pszDevStateName[];

//////////////////////////////////////////////////////////////////////////
// XMS data struct helper function
//int mapDeviceItem(const DeviceID_t *pDevice);
void resetDeviceVoIP(int iDevice);
void resetDeviceVoc(int iDevice);
void resetDeviceTrunk(int iDevice);
void resetDeviceConf(int iDevice);

#endif
