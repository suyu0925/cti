#ifndef _SPKEYGOE_H_
#define _SPKEYGOE_H_

#include "DJAcsDataDef.h"

#define MAX_UNIT			16
#define MAX_DEV_TYPE	32
#define MAX_DEV			256

#define CONF_MODE_NONE			0
#define CONF_MODE_ADD			1
#define CONF_MODE_LISTEN		2
#define CONF_MODE_SPEAKONLY	3
#define CONF_MODE_PLAY			4

enum DevState
{
	DEV_STATE_NULL			= 0,
	DEV_STATE_WAITOPEN		= 1,
	DEV_STATE_FREE			= 2,
	DEV_STATE_USED			= 3,

	DEV_STATE_WAITCONNECT	= 4,
	DEV_STATE_CONNECT		= 5,
	DEV_STATE_WAITFREE		= 6,
	DEV_STATE_PLAYING			= 7,
	DEV_STATE_INCONF			= 8,
	DEV_STATE_JOIN			= 9,
	DEV_STATE_RECORDING		= 10,
	DEV_STATE_CREATEFAILED	= 11,
};

enum UserType
{
	USER_NULL	= 0,
	USER_2G	= 1,
	USER_3G	= 2,
};

typedef struct 
{
	ServerID_t	ServerId;
	int			DebugOn;
	int			DspId[MAX_UNIT];
	int			UnitId;
	
	char VocPath[256];

	char callee[32];
}GLobal_Cfg;

typedef struct  
{
	ACSHandle_t		ACSHandle;
	GLobal_Cfg		cfg;
}Global_Keygoe_Var;

typedef struct
{
	DJ_U32	Dev_Total;
	DJ_U32	Dev_Opened;
	DJ_U32	Dev_Free;
	DJ_S32	sn;
}Dev_Type_Info;

typedef struct
{
	char name[32];
	DeviceID_t *pDev;
}User_Info;

typedef struct usernode
{
	User_Info user;
	struct usernode *next;
}User_Node;

typedef User_Node *UserList;

typedef struct
{
	int id;
	char name[32];
	UserList MemberList;
	DeviceID_t *pVocConf;
	DeviceID_t *pVideoConf;
}Conf_Instance;

typedef struct confnode
{
	Conf_Instance conf;
	struct confnode *next;
}Conf_Node;

typedef struct 
{
	DeviceID_t	Dev;
	DevState		Dev_State;
	DJ_S32		sn;
	
	DeviceID_t *pLinkDev;			//link device
	DeviceID_t *pPlayRecDev;		//play & record device	(voice, sub type 0 or 1)
	DeviceID_t *pVoiceLinkDev1;		//voice exchange device (voice, sub type 0)
	DeviceID_t *pVoiceLinkDev2;		//voice exchange device (voice, sub type 0)
	Conf_Instance *pConf;				//current joined conference
	UserType		User_Type;
	
	struct CODEC_TAG
	{
		DJ_U8 RxCodec;
		DJ_U8 RxPayloadType;
		DJ_U8 TxCodec;
		DJ_U8 TxPayloadType;
	}audio, video;
		
	char szDTMF[32];
	char szText[32];
	char *szFileName[5];
	ITP_3GPP_PARAM_CFG RxMediaPara;
    DJ_U16 decoderConfigLength;
    DJ_U8	decoderConfigInfo[MAX_DECODER_CFG_INFO];
}Dev_Info;

typedef Conf_Node *ConfList;

extern ConfList g_ConfList;

#define M_DEVINFO(pDev)	(&g_DevInfo[pDev->m_s8ModuleID][pDev->m_s16DeviceMain][pDev->m_s16ChannelID])

extern Dev_Type_Info g_DevType[MAX_DEV_TYPE];
extern Dev_Info g_DevInfo[MAX_UNIT][MAX_DEV_TYPE][MAX_DEV];
extern int g_CurDisplayDevType;

bool InitSystem();
void ExitSystem();
void GetDevList();
void DisplayDevInfo(int DevType);
void DisplayConfInfo(int ConfId);
void OnOpenDevice();
void OnOpenAllDevice();
void OnCloseAllDevice();
void OnOpenCurTypeDevice();
void OnCloseCurTypeDevice();
DeviceID_t* GetSelectDev();
int OnSetParam(DeviceID_t *pDev);
int OnSendIOData(DeviceID_t *pDev);
int OnCall(DeviceID_t *pDev);
int OnClearCall(DeviceID_t *pDev);
int OnPlay(DeviceID_t *pDev);
int OnRecord(DeviceID_t *pDev);
int OnStopPlay(DeviceID_t *pDev);
int OnStopRecord(DeviceID_t *pDev);
int OnGetFileInfo(DeviceID_t *pDev);
int OnLinkDev(DeviceID_t *pDev);
int OnUnlinkDev(DeviceID_t *pDev);
int OnResetDev(DeviceID_t *pDev);
Conf_Instance* CreateConf(int id, DeviceID_t *pVocConf, DeviceID_t *pVideoConf);
Conf_Instance* FindConf(DeviceID_t *pDev);
int JoinConf(Conf_Instance *pConf, DeviceID_t *pDev, DJ_U8 visible = 1);
int LeaveConf(Conf_Instance *pConf, DeviceID_t *pDev, int destroyFlag, int restartFlag);
int DestroyConf(int ConfID, DeviceID_t *pDev);

/************************************************************************/
/* Video Conf Operators                                                 */
/* start                                                                */
/************************************************************************/
int OnJoinConf(DeviceID_t *pDev);
int OnLeaveConf(DeviceID_t *pDev);

int OnClearConf(DeviceID_t *pDev);
int OnRestartConf(DeviceID_t *pDev);

int OnPlayConf(DeviceID_t *pDev);
int OnRecordConf(DeviceID_t *pDev);

int OnGetLayout(DeviceID_t *pDev);
int OnSetLayout(DeviceID_t *pDev);

int OnGetVisibleList(DeviceID_t *pDev);
int OnSetVisibleList(DeviceID_t *pDev);

int OnTimerFor3GVConf();
/************************************************************************/
/* end                                                                  */
/************************************************************************/

DeviceID_t* GetOneDev(int unit, int dev_main, int dev_sub, DevState dev_state);

#endif
