#ifndef _XMSAPI_TEST_EVENT_H_
#define _XMSAPI_TEST_EVENT_H_

#include "DJAcsDevState.h"

typedef struct 
{
	DeviceID_t	DevID;
	bool		bOpenFlag;
	void*		pDevData;
} TYPE_MY_DEVICE_STRUCT;

typedef struct 
{
	DeviceID_t	Dev;

	struct CODEC_TAG
	{
		DJ_U8 RxCodec;
		DJ_U8 RxPayloadType;
		DJ_U8 TxCodec;
		DJ_U8 TxPayloadType;
	}audio, video;

}Dev_Codec_Info;

typedef struct 
{
	DJ_U8 u8SrcUnitID;
	DJ_U8 u8DestUnitID;
	DJ_U8 u8AppRegType;
	DJ_U8 u8Ref;
	DJ_S32 s32TestNum1;
	DJ_S32 s32TestNum2;

	DeviceID_t OthersCTXDevID;

	DJ_S8 s8SrcAppRegName[20];
	DJ_S8 s8DestAppRegName[20];
	DJ_S8 s8TestString[100];

}App_Data_Struct;

typedef struct
{
	DJ_S32 s32TestNum1;
	DJ_S32 s32TestNum2;

	DeviceID_t CTXDevID;

	DJ_S8 s8TestString[100];
}UserData4CTX;

typedef struct
{
	DJ_S8 u8Flag;
	DJ_S8 s8Number;
	DJ_S8 ref[2];

}AppendCode;


#define	MAX_DEVICE_ALLOW_OPEN		32

DJ_Void EvtHandler(DJ_U32 esrParam);

void	OpenDeviceOK ( DeviceID_t	*pDev );
void	CloseDeviceOK ( DeviceID_t	*pDev );

#endif