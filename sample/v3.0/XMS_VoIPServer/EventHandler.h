#ifndef _EVENT_HANDLER_H__
#define _EVENT_HANDLER_H__


#include "DJAcsAPIDef.h"
#include "DJAcsDevState.h"
#include <assert.h>

#define DJ_MAX_USER					480
#define DJ_MAX_CALL					240
#define DJ_MAX_DEVICE_BUF			(2 + 0 + 480 + 60 + 256)	// board + trunk + ip + rtp + voice

#define DJ_ASSERT(x)	assert(x)
// user state
enum DJ_USER_STATE
{
    US_IDLE,		// idle
	US_REG,			// register
	US_UNREG,		// unregister
	US_INITIATED,		// make call
	US_ALERTING,		// alerting
	US_HOLD,		// hold
	US_CONNECTED		// connected
};
// call state
enum DJ_CALL_STATE
{
    CS_NULL,				// NULL					caller      callee
	CS_ORIGINATED,				// originated			callin		N/A
	CS_DELIVERED,				// delivered			callin		make call
	CS_ALERTING,				// callee alert			callin		alerting
	CS_ESTABLISHED,				// established			callin		connected
	CS_ANSWER_CALL,				// AnswerCall			answer call	connected
	CS_CONNECTED,				// connected			connected	connected
	CS_TRANSLATE,				// refering
	CS_PLAYING,				// play file
	CS_PLAYEND
};

class CDJCmd;
class CDJDevice;
class CDJXms;
class CDJUser;
class CDJCall;
class CDJLogic;
class CDJRtp;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef void (CDJCmd::*DJ_PMSG) (void);
typedef void (CDJCmd::*DJ_PCMD) (void);
typedef DJ_U32 (CDJCmd::*DJ_PBV) ( void *pAcsEvt );

enum DJSig
{
    DJSig_end	= 0,		// end
	DJSig_cmd,
	DJSig_pbv
};
union DJ_MSG_FUNCTION
{
    DJ_PMSG		fnPMSG;
    DJ_PCMD		fnPCMD;
    DJ_PBV		fnPBV;
};

#define  DJ_ON_COMMAND( msgID, memberFxn )	\
{ (DJ_U32)msgID, (DJ_U32)0, DJSig_cmd, (DJ_PMSG)(DJ_PCMD) memberFxn },

#define  DJ_ON_MSG( msgID, memberFxn )	\
{ (DJ_U32)msgID, (DJ_U32)0, DJSig_pbv, (DJ_PMSG)(DJ_PBV) memberFxn },

struct DJ_MSGMAP_ENTRY
{
    DJ_U32		nMessage;		// message ID
    DJ_U32		nID;			// ID
    DJ_U32		nSig;			// function type
    DJ_PMSG		pfn;			// function pointer
};

struct DJ_MSGMAP
{
    DJ_MSGMAP			*pBaseMessageMap;
    DJ_MSGMAP_ENTRY		*lpEntries;
};

#define DJDEC_MESSAGE_MAP() \
    static DJ_MSGMAP_ENTRY	msgEntries[];	\
    static DJ_MSGMAP	msgMap;	\
virtual DJ_MSGMAP	*GetMessageMap() const;

#define DJBEG_MESSAGE_MAP( theClass, baseClass )	\
    DJ_MSGMAP	*theClass::GetMessageMap() const	\
{ return &theClass::msgMap;	}	\
    DJ_MSGMAP	theClass::msgMap	=	\
{ &(baseClass::msgMap),		\
    ( DJ_MSGMAP_ENTRY * ) &( theClass::msgEntries ) };	\
    DJ_MSGMAP_ENTRY theClass::msgEntries[]	=	\
{ 

#define DJEND_MESSAGE_MAP()	\
{ 0, 0, DJSig_end, (DJ_PMSG) 0 }	\
};

class CDJCmd 
{
    DJDEC_MESSAGE_MAP()
public:
    CDJCmd();
    virtual ~CDJCmd();
public:
    // 发送命令消息
    virtual DJ_U32 SendMsg( DJ_U32 nMsgID, void *pAcsEvt );
    // 消息预处理
    virtual DJ_U32 TranslateMsg( void *pAcsEvt );
    // 默认命令消息处理函数
    virtual DJ_U32 DefMsgProc(DJ_U32 nMsgID, void *pAcsEvt);
protected:
    DJ_MSGMAP_ENTRY* SearchMsgEntry( DJ_U32 nID );
protected:
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// djlog
#define DJ_PORT_USER		1
#define DJ_PORT_DEVICE		2
#define DJ_PORT_CALL		3
#define DJ_PORT_EVENT		4

#define DJ_LEVEL_LOG		1
#define DJ_LEVEL_WARN		2
#define DJ_LEVEL_ERR		3

void djPrint(int nPort, const char *format,...);
void djPrint(int nPort, int nID, int nCnt, ...);

class CDJLog
{
public:
    CDJLog();
    virtual ~CDJLog();
public:
    int PrintTime( char *pTime, int iTimeFlag );
    BOOL Print(int nPort, const char *pData, int nCnt);
    BOOL Print(int nPort, int nID, int nItem, const char *pData);
    static CDJLog* GetLog();
public:
    CListCtrl*	m_tUser;
    CListCtrl*	m_tDevice;
    CListCtrl*	m_tCall;
    CListCtrl*	m_tEvent;
protected:
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// device
class CDJDevice : public CDJCmd
{
    DJDEC_MESSAGE_MAP()
public:
    CDJDevice();
    virtual ~CDJDevice();
public:
    enum DEV_TYPE{DT_NULL, DT_VOIP, DT_VOC, DT_TRUNK};
    // open
    virtual BOOL Open();
    // make call
    virtual void MakeCall(DJ_S8 *s8CallerNum, DJ_S8 *s8CalleeNum){;}
    // answer call
    virtual void AnswerCall(DJ_S32 s32State, BOOL bAllocRtp, BOOL bTransfer){;}
    // forward call
    virtual void ForwardCall(DJ_S8* s8TelNo, DJ_S8* s8UserID, DJ_S8* s8Address, DJ_U16 u16Port) {;}
    // transfer call
    virtual void TransferCall(CDJDevice* device) {;}
    // refer call
    virtual void ReferCall(Acs_VoIP_Refer_Response* referResp){;}
    // clear call
    virtual void ClearCall(){;}
    // get user id
    virtual DJ_S8* GetUserID(){return "";}
    // send io data
    DJ_U32 SendIOData(DJ_U16 u16Type, DJ_U16 u16Size, DJ_Void* data);
    // close
    void Close();
    //
    DJ_U32 GetID() { return m_id; }
    // 
    DeviceID_t* GetDevice() { return &m_device; }
    //
    CDJDevice* GetNext() { return m_next; }
    // get call
    CDJCall* GetCall() { return m_call; }
    // Set call
    void SetCall(CDJCall* call)	{ m_call = call; }
    // is used
    BOOL IsUsed() const { return m_bUsed; }
    // set Used
    void SetUsed(BOOL bUsed) { m_bUsed	= bUsed; }
    // get state
    DJ_U32 GetState() const { return m_nState; }
    // set user
    void SetUser(CDJUser* user) { m_user= user; }
    // get User
    CDJUser* GetUser() { return m_user; }
    //
    BOOL IsRefer() { return m_bRefer; }
    // 
    void SetRefer(BOOL bRefer) { m_bRefer = bRefer; }
protected:
    // open device event
    DJ_U32	OnOpenDevice(void* param);
    // close device event
    DJ_U32	OnCloseDevice(void* param);
    // device state event
    DJ_U32 OnDeviceState(void* param);
protected:
    DJ_U32		m_id;			// id
    CDJXms		*m_parent;		// xms
    BOOL		m_bRefer;
    // call
    CDJCall		*m_call;		// call
    CDJUser		*m_user;		// user
    // normal memeber
    DeviceID_t	m_device;		// system handler
    BOOL		m_bOpen;				
    BOOL		m_bUsed;		// used flag
    DJ_U32		m_nState;		// state
    // for link
    CDJDevice*	m_next;
    friend class CDJXms;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// voip
class CDJVoip : public CDJDevice
{
    DJDEC_MESSAGE_MAP()
public:
    CDJVoip();
    virtual ~CDJVoip();
public:
    Acs_VoIP_MediaInfo* GetMediaInfo(){ return &m_tMediaInfo; }
    // open device
    virtual BOOL Open();
    // make call 
    virtual void MakeCall(DJ_S8 *s8CallerNum, DJ_S8 *s8CalleeNum);
    // answer call
    virtual void AnswerCall(DJ_S32 s32State, BOOL bAllocRtp, BOOL bTransfer);
    // forward call
    virtual void ForwardCall(DJ_S8* s8TelNo, DJ_S8* s8UserID, DJ_S8* s8Address, DJ_U16 u16Port);
    // trnasfer call
    virtual void TransferCall(CDJDevice* device);
    // refer call
    virtual void ReferCall(Acs_VoIP_Refer_Response* referResp);
    // clear call
    virtual void ClearCall();
    // reset
    void Reset();
    // set rtp
    void SetRtp(CDJRtp* rtp) { m_rtp = rtp; }
    // get rtp
    CDJRtp* GetRtp() { return m_rtp; }
    // re-invite
    void OnReInvite();
    // set mediainfo
    void SetMediaInfo(Acs_VoIP_MediaInfo* mediaInfo);
protected:
    // recieve io data event
    DJ_U32 OnRecvIOData(void* param);
    // media info
    DJ_U32 OnSetMediaInfo(void *param);
    // call in event
    DJ_U32 OnCallIn(void* param);
    // alert call
    DJ_U32 OnAlertCall(void *param);
    // answer call
    DJ_U32 OnAnswerCall(void *param);
    // call out
    DJ_U32 OnCallOut(void *param);
    // clear call
    DJ_U32 OnClearCall(void *param);
    // refer result
    DJ_U32 OnReferRsult(void *param);
    // get user id
    virtual DJ_S8* GetUserID(){ return m_s8UserID;}
public:
    DJ_S8		m_s8UserID[20];		// binding user's name
protected:
    int			m_iProtocol;			// h.323/sip
    Acs_VoIP_MediaInfo	m_tMediaInfo;			// media info
    CDJRtp*		m_rtp;
private:
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// rtp
class CDJRtp : public CDJDevice
{
public:
    CDJRtp();
    virtual ~CDJRtp();
public:
    void SetSession(DJ_U8 u8Enabled, DJ_U8 dtmf, DJ_U8 tone);
    void SetIP(DJ_U8 u8AudioEnabled, const DJ_S8* s8AudioAddress, DJ_U16  u16AudioPort, DJ_U8   u8VideoEnabled, const DJ_S8* s8VideoAddress, DJ_U16  u16VideoPort);
    void SetCodec(DJ_U8 u8AudioEnabled, DJ_U8 u8AudioCodec, DJ_U8 u8AudioPayloadType, DJ_U8 u8VideoEnabled, DJ_U8 u8VideoCodec, DJ_U8 u8VideoPayloadType);
protected:
protected:
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// voice
class CDJVoice : public CDJDevice
{
    DJDEC_MESSAGE_MAP()
public:
    CDJVoice();
    virtual ~CDJVoice();
public:
    // clear call
    virtual void ClearCall();
    // set property
    void SetProperty(DJ_U8 u8DecodeType, DJ_U16 u16PlayType, DJ_U8 u8SrcMode);
    // play
    void Play(const char* filename);
    // play event
    DJ_U32 OnPlay(void *param);
    // play end event
    DJ_U32 OnPlayEnd(void *param);
    // get user name
    DJ_S8* GetUserID(){ return "IVR";}
protected:
protected:
    PlayProperty_t	m_property;
private:
    BOOL m_bPlaying;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// XMS system
class CDJXms
{
public:
    CDJXms();
    virtual ~CDJXms();
public:
    // Init
    BOOL InitSystem(unsigned int nId, const char* strServerIP, const int strServerPort, const char* strUserName, const char* strPassword);
    // close system
    void CloseSystem();
    // Open all device
    BOOL OpenAllDevices();
    // handler
    ACSHandle_t Handler()	{ return g_acsHandle; }
    // alloc device
    CDJDevice* AllocDevice(DJ_U32 u32Type, DJ_U32 nID	= 0);
    // release device
    void ReleaseDevice( DJ_U32 u32Type, DJ_U32 nID );
    // print
    void Print(DJ_U32 u32Type);
protected:
    // get device by device's handle
    CDJDevice* GetDeviceItem( const DeviceID_t *pDevice );
    
    // event handler
    static DJ_Void EventHandler(DJ_U32 u32EsrParam);
    
    // open xms system
    void OnOpenStream(Acs_Evt_t *pAcsEvt);
    void OnQueryDevice(Acs_Evt_t *pAcsEvt);
    void OnQueryDeviceEnd(Acs_Evt_t *pAcsEvt);
private:
    DJ_U32 InsertDevice(CDJDevice* pDevice, DJ_S32 s32Type);
    DJ_U32 InsertLink(CDJDevice* pDevice, CDJDevice*& listHead);
    CDJDevice* GetDeviceItem( CDJDevice* pDevice, DJ_S8 s8ModuleID, DJ_S16 s16ChannelID );
protected:
    DJ_U8		m_nID;				// app id
    ACSHandle_t g_acsHandle;		
    
    CDJDevice*	m_voip;				// voip
    DJ_U32		m_cntVoip;			// voip channel count
    DJ_U32		m_cntVoipUsed;		
    CDJDevice*	m_rtp;				// rtp
    DJ_U32		m_cntRtp;			// rtp channel count
    DJ_U32		m_cntRtpUsed;
    CDJDevice*	m_voice;			// voice
    DJ_U32		m_cntVoice;			// voice channel count
    DJ_U32		m_cntVoiceUsed;
    
    BOOL		m_bCanOpen;			// open flag
private:
    CDJDevice**	m_pDevBuf;			// device handler buffer
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// user
class CDJUser
{
    friend class CDJApp;
public:
    CDJUser();
    virtual ~CDJUser();
public:
    // reset
    void Reset();
    // print
    void Print();
    // get state
    DJ_U32 GetState() { return m_u32State; }
protected:
public:
    DJ_U16		m_u16SlotID;			// register slot 
    DJ_S8		m_s8TelNo[20];			/* Client Telephone-subscriber */
    DJ_S8		m_s8UserID[40];			/* Client UserID */
    
    DJ_S8		m_s8Address[20];		/* Client Address */
    DJ_U16		m_u16Port;			/* Client Port */
    
    char		m_szDtmf[10];			// dtmf string
protected:
    DJ_U32		m_nID;				// id
    DJ_U32		m_u32State;			// state
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// call
class CDJCall
{
    friend class CDJApp;
public:
    CDJCall();
    virtual ~CDJCall();
public:
    // printf
    void Print();
    
    // call connected
    DJ_U32 OnCallConnected(CDJDevice* device, DJ_S32 s32State);
    // send io data
    DJ_U32 OnSendIOData(CDJDevice* device, DJ_U16 u16Type, DJ_U16 u16Size, DJ_Void* data);
    // clear call
    DJ_U32 OnClearCall(CDJDevice* device);
    // Refer
    DJ_U8 OnRefer(CDJDevice* device, Acs_VoIP_Refer_Response* referResp);
    // forward
    DJ_U8 OnForward(CDJDevice* device, DJ_S8* s8TelNo, DJ_S8* s8UserID, DJ_S8* s8Address, DJ_U16 u16Port);
    // call state changed
    void OnCallStateChaged();
    // play file
    void OnPlay();
    // play file end
    void OnPlayEnd();
    
    // get state
    DJ_U32 GetState() { return m_nState; }
    // get caller
    CDJDevice* GetCaller() { return m_caller; }
    // get callee
    CDJDevice* GetCallee() { return m_callee; }
    //
    void SetCaller(CDJDevice* caller) { m_caller	= caller; }
    //
    void SetCallee(CDJDevice* callee) { m_callee	= callee; }
protected:
protected:
    CDJDevice* m_caller;		// caller
    CDJDevice* m_callee;		// callee
    
    DJ_U32	m_nID;			// id
    DJ_U32	m_nState;		// state
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// app
class CDJApp : public CDJCmd
{
    DJDEC_MESSAGE_MAP()
public:
    CDJApp();
    virtual ~CDJApp();
public:
    // get global app handler
    static CDJApp* GetApp();
    // init
    BOOL Init(unsigned int nId, const char* strServerIP, const int strServerPort, const char* strUserName, const char* strPassword);
    // alloc call
    CDJCall* AllocCall();
    // get call by user
    CDJCall* GetCallByUser(CDJUser* user, CDJCall* call);
    // release call
    void ReleaseCall(CDJCall* call);
    // get user
    CDJUser* GetUser(DJ_S8* s8TelNo, DJ_S8* s8UserID);
    // user register event
    void OnUserRegister(DJ_U16 u16SlotID, DJ_S8* s8TelNo, DJ_S8* s8UserID, DJ_S8* s8Address, DJ_U16 u16Port);
    // user unregister event
    void OnUserUnregister(DJ_U16 u16SlotID);
    // user call in
    void OnCallIn( CDJVoip* caller, DJ_S8* s8CallerTelNo, DJ_S8* s8CallerUserID, DJ_S8* s8CalleeTelNo, DJ_S8* s8CalleeUserID );
    // init xms end
    void OnQueryDeviceEnd();
    // analyze tel no
    CDJDevice*  OnDialAnalyze( DJ_S8* s8TelNo, DJ_S8* s8UserID, BOOL *bVoc );
    // refer call result
    void OnReferResult(CDJDevice* caller, DJ_U8 u8State, DJ_U8 u8Reason);
protected:
    // destroy
    void Destroy();
public:
    CDJXms		m_xms;
protected:
    CDJUser*	m_user;
    CDJCall*	m_call;
};

#endif	// _EVENT_HANDLER_H__
