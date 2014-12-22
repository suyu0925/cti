#ifndef _XMSAPI_TEST_FUNC_H_
#define _XMSAPI_TEST_FUNC_H_

bool	CheckOpenDevice ( int iIndex, bool	bIsDev1 = true);
bool	CheckOpenDeviceForVoIP (int iIndex ); //new add by jerry,Sep,9,2007
void	InitVar_Func(void);


void	DoFunc_GetDeviceList (void);
void	DoFunc_OpenDevice(void);
void	DoFunc_CloseDevice(void);
void	DoFunc_ResetDevice(void);
void	DoFunc_GetDeviceState(void);
void	DoFunc_GetDeviceStateVoIP(void);


void	DoFunc_AlertCall(void);
void	DoFunc_AnswerCallIn(void);
void	DoFunc_ClearCall(void);
void	DoFunc_MakeCallOut(void);

void	DoFunc_LinkDevice(void);
void	DoFunc_UnlinkDevice(void);

void	DoFunc_Play(bool bIsDetailPlay = false);
void    DoFunc_PlayCSP();		
void	DoFunc_ControlPlayCSP( DJ_S32 s32CSPPlayControlType );
void	DoFunc_MyStopPlay(int iMediaType);
void	DoFunc_3GPPStopPlay( int iMediaType );

void	DoFunc_ControlPlay(void);
void	DoFunc_ControlPlay_Real(ControlPlay_t *pControlPlay);
void	DoFunc_Record(bool bIsDetailRecord = false);
void	DoFunc_MyStopRecord(void);
void	DoFunc_3GPPStopRecord(void);

void	DoFunc_ControlRecord(void);
void	DoFunc_ControlRecord_Real(ControlRecord_t *pControlRecord);
void	DoFunc_Control3GPPRecord_Real(Control3gppRecord_t *pControlRecord);

void	DoFunc_SendFax(void);
void	DoFunc_StopSendFax(void);

void	DoFunc_ReceiveFax(void);
void	DoFunc_StopReceiveFax(void);


void	DoFunc_StartFaxT38(void);

void	DoFunc_SendFaxT38(void);
void	DoFunc_StopSendFaxT38(void);

void	DoFunc_ReceiveFaxT38(void);
void	DoFunc_StopReceiveFaxT38(void);

void 	DoFunc_JoinToConf(void);
void	DoFunc_LeaveFromConf(void);
void 	DoFunc_ClearConf(void);


void	DoFunc_SetParam(void);
void	DoFunc_GetParam(void);
void	DoFunc_InitPlayIndex(void);
void	DoFunc_BuildPlayIndex(void);
void	DoFunc_BuildPlayIndex_Real(void);

void	DoFunc_SendIOData(void);

void DoFunc_ConnDsp(void);
void DoFunc_DisConnDsp();
void DoFunc_RecCSP();
void DoFunc_CtrlRecCSP(DJ_S32 i32ControlType);

void DoFunc_CTXLink();
void DoFunc_CTXUnLink();

void DoFunc_GetBoardInfo();

void DoFunc_Build3GPPPlayIndex_Real(void);
void DoFunc_SendSignalMsg(DJ_U16 u16SignalMsgType);
void DoFunc_3GPPPlay(bool bIsDetailPlay, DJ_U8  u8MediaType);
void DoFunc_3GPPStopPlay( int iMediaType );
void DoFunc_Control3GPPPlay_Real(Control3gppPlay_t *pControlPlay);
void DoFunc_3GPPGetConfig( void );

void DoFunc_Timer(void);
void DoFunc_CtxReg();
void DoFunc_CTXLink();
void DoFunc_CTXAppData();
void DoFunc_SendSignalData();

void DoFunc_LedCtrl();
void DoFunc_SetMaster();
void DoFunc_GetRelateMod();

void DoShowMessage ( char * MsgStr );
#endif