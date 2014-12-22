#ifndef _XMSAPI_TEST_STRING_H_
#define _XMSAPI_TEST_STRING_H_

//define micro to be used by user to get the active member of one conf at one time
#define GetActiveMem(MemList, CHID)  (((MemList)[(CHID)/8]>>((CHID)%8))&0x01)

char *GetString_EventType ( EventType_t EvtType );
char *GetString_DeviceMain ( DJ_S32	s32DeviceType );
char *GetString_DeviceSub (DJ_S32	s32DeviceMain, DJ_S32	s32DeviceSub );
char *GetString_DeviceAll ( DeviceID_t *pDevID );
char *GetString_ErrorCode ( DJ_S32	s32ErrorCode );
char *GetString_PlayControlType ( DJ_U16 u16ControlType );
char *GetString_RecordControlType ( DJ_U32 u32ControlType );
char *GetString_GtgType ( DJ_U16	u16GtgType );
char *GetString_DeviceState ( DJ_U32	s32DeviceState );
char *GetString_VocDeviceState ( DJ_U8 u8DSPID, DJ_U16 u16ChID, DJ_U32 s32DeviceState );

char *GetString_IOType ( DJ_U16 u16IOType );
char* GetString_AnalogInterfaceState(DJ_S16 u16DevSub,DJ_U8 u8Interface);
char* GetString_FaxState(DJ_U32 u32State);
char * GetStringMediaErrCode( DJ_S32 s32RetState, DJ_S32 s32ErrCode );
char * GetStringConfErrCode( DJ_S32 s32RetState, DJ_S32 s32ErrCode );
char *GetString_DigitalPortDeviceState ( DJ_U32	s32DeviceState );
char * GetConfActiveMember( DJ_U8 *pMemberList, DJ_U32 *pMemNums );
char *GetString_ClockState ( DJ_U8	u8ClockState );
char *GetString_E1Info( ACS_Digital_PortState_Data*  pData );

#endif