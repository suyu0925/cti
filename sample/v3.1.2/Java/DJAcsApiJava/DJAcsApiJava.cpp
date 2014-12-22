//#include <ITPDataStandard.h>
#include "windows.h"
#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"
#include "DJAcsDevState.h"

#include <jni.h>
#include <stdio.h>

#include "DJAcsApiJava.h"

#pragma comment(lib, "C:\\DJKeygoe\\Lib\\DJAcsAPI.lib")

#define  FetchVoipCallData(pAcsEvt)  ((DJ_S8 *)FetchEventData(pAcsEvt) + sizeof(Acs_CallControl_Data))

typedef struct CBData{
	EsrFunc m_pfnUserProcess;
	jobject m_objInterface;
	JNIEnv* m_pEnv;
	jobject m_objCallBack;
	JavaVM* mg_Jvm;
}CBData;

CBData g_cbData;

FILE* fp = fopen("Log File.txt", "w+");

void LogInfo(char* Str)
{
	fprintf(fp, "%s\n", Str);
}

DJ_Void EvtHandler(DJ_U32 esrParam);

//根据对象object，得到对象每个成员值
void GetData_DeviceID		  (JNIEnv*, jobject*, DeviceID_t*);
void GetData_ControlPlay	  (JNIEnv*, jobject*, ControlPlay_t*);
void GetData_PlayProperty	  (JNIEnv*, jobject*, PlayProperty_t*);
void GetData_RecordProperty	  (JNIEnv*, jobject*, RecordProperty_t*);
void GetData_CtrlRecord		  (JNIEnv*, jobject*, ControlRecord_t*);
void GetData_VocInputControl  (JNIEnv*, jobject*, VocInputControlParam_t*);
void GetData_VocOutputControl (JNIEnv*, jobject*, VocOutputControlParam_t*);
void GetData_MixerControlParam(JNIEnv*, jobject*, MixerControlParam_t*);
void GetData_GtdControl		  (JNIEnv*, jobject*, VocGtdControlParam_t*);
void GetData_CmdConf		  (JNIEnv*, jobject*, CmdParamData_Conf_t*);
void GetData_FaxPrivate		  (JNIEnv*, jobject*, FaxPrivate_t*);
void GetData_Private		  (JNIEnv*, jobject*, PrivateData_t*);
void GetData_ServerID		  (JNIEnv*, jobject*, ServerID_t*);
void GetData_CspPlay		  (JNIEnv*, jobject*, CSPPlayProperty_t*);
void GetData_CspPlayInfo	  (JNIEnv*, jobject*, CSPPlayDataInfo_t*);
void GetData_CtrlPlay		  (JNIEnv*, jobject*, ControlPlay_t*);
void GetData_RecordCsp		  (JNIEnv*, jobject*, RecordCSPProperty_t*);
void GetData_Play3GppIndex	  (JNIEnv*, jobject*, Play3gppProperty_t*);
void GetData_MediaPlay		  (JNIEnv*, jobject*, Acs_MediaEx_Play*);
void GetData_Ctrl3GpPlay	  (JNIEnv*, jobject*, Control3gppPlay_t*);
void GetData_Record3Gpp		  (JNIEnv*, jobject*, Record3gppProperty_t*);
void GetData_MediaRecord	  (JNIEnv*, jobject*, Acs_MediaEx_Record*);
void GetData_Ctrl3GppRecord	  (JNIEnv*, jobject*, Control3gppRecord_t*);
void GetData_LayOutList		  (JNIEnv*, jobject*, Acs_3GVConf_LayoutList*);
void GetData_VisibleList	  (JNIEnv*, jobject*, Acs_3GVConf_VisibleList*);
void GetData_ParamItem		  (JNIEnv*, jobject*, PutTextInPicture_Param*);
void GetData_UserLedCtrl	  (JNIEnv*, jobject*, UserLedCtrl*);
void GetData_OutPutV		  (JNIEnv*, jobject*, Acs_MediaEx_Output_V*);
void GetData_OutPutA		  (JNIEnv*, jobject*, Acs_MediaEx_Output_A*);
void GetData_InPutV			  (JNIEnv*, jobject*, Acs_MediaEx_Input_V*);
void GetData_ChMediaAudio	  (JNIEnv*, jobject*, Acs_VoIP_RTPOpen*);
void GetData_ChMediaVideo	  (JNIEnv*, jobject*, Acs_VoIP_RTPOpen*);
void GetData_ChAddrAudio	  (JNIEnv*, jobject*, Acs_VoIP_RTPADDR*);
void GetData_ChAddrVideo	  (JNIEnv*, jobject*, Acs_VoIP_RTPADDR*);
void GetData_ChCodecAudio	  (JNIEnv*, jobject*, Acs_VoIP_RTPCODEC*);
void GetData_ChCodecVideo	  (JNIEnv*, jobject*, Acs_VoIP_RTPCODEC*);

void GetObjectArrayData_CalledTable(JNIEnv*, CAS_CalledTableDesc_t*, jobjectArray*, int);


//调用XMS_ctsSetParam,根据不同类型获取数据
void GetData_SetEcm			 (JNIEnv*, Acs_SetECM*, jobject*);
void GetData_SetFaxBps		 (JNIEnv*, Acs_SetFaxBps*, jobject*);
void GetData_RtpAddr		 (JNIEnv*, Acs_VoIP_RTPADDR*, jobject*);
void GetData_RtpOpen		 (JNIEnv*, Acs_VoIP_RTPOpen*, jobject*);
void GetData_AnalogEmCMD     (JNIEnv*, Acs_AnalogEM_CMD*, jobject*);
void GetData_TransAddFile	 (JNIEnv*, Acs_TransAddFile*, jobject*);
void GetData_RtpCodec		 (JNIEnv*, Acs_VoIP_RTPCODEC*, jobject*);
void GetData_Cas			 (JNIEnv*, CmdParamData_CAS_t*, jobject*);
void GetData_TransAddHeader  (JNIEnv*, Acs_TransAddHeader*, jobject*);
void GetData_MediaInfo		 (JNIEnv*, Acs_VoIP_MediaInfo*, jobject*);
void GetData_RtpSession		 (JNIEnv*, Acs_VoIP_RTPSESSION*, jobject*);
void GetData_CmdVoice		 (JNIEnv*, CmdParamData_Voice_t*, jobject*);
void GetData_324CH_t		 (JNIEnv*, CmdParamData_324CH_t*, jobject*);
void GetData_GtdFreq		 (JNIEnv*, CmdParamData_GtdFreq_t*, jobject*);
void GetData_CtClkNet		 (JNIEnv*, CmdParamData_CTCLKNET_t*, jobject*);
void GetData_FskParam		 (JNIEnv*, CmdParamData_FskParam_t*, jobject*);
void GetData_FlashParam		 (JNIEnv*, CmdParamData_FlashParam_t*, jobject*);
void GetData_AnalogUser		 (JNIEnv*, CmdParamData_AnalogUser_t*, jobject*);
void GetData_AnalogTrunk	 (JNIEnv*, CmdParamData_AnalogTrunk_t*, jobject*);
void GetData_GtdProtoType	 (JNIEnv*, CmdParamData_GtdProtoType_t*, jobject*);
void GetData_BoardCommon	 (JNIEnv*, CmdParam_BoardCommonParam_t*, jobject*);
void GetData_VadMinDetect	 (JNIEnv*, CmdParam_VADMinDetectParam_t*, jobject*);
void GetData_SilenceDetect	 (JNIEnv*, CmdParam_SilenceDetectParam_t*, jobject*);
void GetData_TrkFlash		 (JNIEnv*, CmdParamData_TrunkFlashParam_t*, jobject*);
void GetData_AnalogTrkFlash  (JNIEnv*, CmdParamData_AnalogTrunkFlash_t*, jobject*);

//调用XMS_ctsGetParam,根据不同类型获取数据
void GetData_BoardInfo		 (JNIEnv*, Acs_ParamData_UserReadXmsBoardInfo*, jobject*);
void GetData_ReadVoltage	 (JNIEnv*, CmdParamData_ReadVoltage_t*, jobject*);
void GetData_3GppCfg		 (JNIEnv*, Get3gppCfg_t*, jobject*);

//收到事件后 JNI根据事件类型 返回不同的数据结构 Java回调函数中只需要进行强转即可
void SetData_Evt		(Acs_Evt_t*,			jobject*);
void SetData_3Gpp		(CmdParamData_3GPP_t*,  jobject*);
void SetData_3G324		(Acs_3G324_Data*,		jobject*);
void SetData_IOData		(Acs_IO_Data*,			jobject*);
void SetData_ReadSn		(CmdParamData_ReadSn_t*,jobject*);
void SetData_SigMon		(Acs_SigMon_Data*,		jobject*);
void SetData_CtxReg		(Acs_CtxReg_Data*,		jobject*);
void SetData_FaxProc	(Acs_FaxProc_Data*,		jobject*);
void SetData_CtxLink	(Acs_CtxLink_Data*,		jobject*);
void SetData_DeviceID	(DeviceID_t*,			jobject*);
void SetData_MediaProc	(Acs_MediaProc_Data*,	jobject*);
void SetData_Unifailure	(Acs_UniFailure_Data*,	jobject*);
void SetData_ParamProc  (Acs_ParamProc_Data *,	jobject*);
void SetData_VoipCodec	(Acs_VoIP_RTPCODEC*,	jobject*);
void SetData_ModRelate	(Acs_ModRelate_Data*,	jobject*);
void SetData_GetLayout	(Acs_GetLayout_Data*,	jobject*);
void SetData_SetLayout	(Acs_SetLayout_Data*,	jobject*);
void SetData_CspDataReq (Acs_CSPDataReq_Data*,	jobject*);
void SetData_SendSigMsg (Acs_SendSigMsg_Data*,  jobject*);
void SetData_MasterState(Acs_MasterState_Data*,	jobject*);
void SetData_SS7RawFrame(Acs_SS7RawFrame_Data*,	jobject*);
void SetData_LinkDevData(Acs_LinkDev_Data*,		jobject*);
void SetData_CallControl(Acs_CallControl_Data*, jobject*);
void SetData_DevListHead(Acs_Dev_List_Head_t*,	jobject*);
void SetData_ConfControl(Acs_ConfControl_Data*, jobject*);
void SetData_GeneralProc(Acs_GeneralProc_Data*, jobject*);
void SetData_ChCodecVideo(Acs_VoIP_RTPCODEC*,   jobject*);
void SetData_ChCodecAudio(Acs_VoIP_RTPCODEC*,   jobject*);
void SetData_ModRelateMod(Acs_ModRelate_Mod*,		  jobject*);
void SetData_Clear3GVConf(Acs_Clear3GVConf_Data*,     jobject*);
void SetData_LicenseQuery(Acs_LicenseQuery_Data*,	  jobject*);
void SetData_MediaCspProc(Acs_MediaCSPProc_Data*,	  jobject*);
void SetData_Media3GppProc(Acs_Media3GPPProc_Data*,   jobject*);
void SetData_JoinTo3GVConf(Acs_JoinTo3GVConf_Data*,	  jobject*);
void SetData_GetVisibleList(Acs_GetVisibleList_Data*, jobject*);
void SetData_SetVisibleList(Acs_SetVisibleList_Data*, jobject*);
void SetData_SlaveWorkState(Acs_SlaveWorkState_Data*, jobject*);
void SetData_CtxAppDataInfo(Acs_CtxAppData_Info*,	  jobject*);
void SetData_AnalogInterface(Acs_AnalogInterface_Data*, jobject*);
void SetData_VoipCallPrivate(VoIPCallPrivate_t*,		jobject*);
void SetData_ClockRefSrcState(ACS_Clock_RefSrc_State_Data*, jobject*);
void SetData_LeaveFrom3GVConf(Acs_LeaveFrom3GVConf_Data*,   jobject*);

void SetData_Conf		(CmdParamConf_MemberState_t*, jobject*);
void SetData_Board		(Acs_ParamData_UserReadXmsBoardInfo*, jobject*);
void SetData_ReadVolteage(CmdParamData_ReadVoltage_t*, jobject*);

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsOpenStream
 * Signature: (ILDJKeygoe/ServerID_t;BIIILDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsOpenStream
  (JNIEnv * env, jobject, jint acsHandle, jobject objServer, jbyte u8AppID, 
	jint u32SendQSize, jint u32RecvQSize, jint s32DebugOn, jobject privateData)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1acsOpenStream");

	ServerID_t serverID;
	int nRet = 0;

	memset((void *)&serverID, 0, sizeof(ServerID_t));

	GetData_ServerID(env, &objServer, &serverID);

	nRet = XMS_acsOpenStream((ACSHandle_t*)&acsHandle, &serverID,u8AppID,u32SendQSize,u32RecvQSize,s32DebugOn,NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1acsOpenStream");

	if (nRet >= 0) //调用成功 返回建立连接的句柄 
	{
		return acsHandle;
	}
	else
	{
		return nRet; //调用失败返回失败原因
	}

	//return acsHandle;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsCloseStream
 * Signature: (ILDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsCloseStream
  (JNIEnv * env, jobject obj, jint acsHandle, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1acsCloseStream");

	int nRet = XMS_acsCloseStream(acsHandle, NULL);

	env->DeleteGlobalRef(g_cbData.m_objCallBack);
	env->DeleteGlobalRef(g_cbData.m_objInterface);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1acsCloseStream");

//	fclose(fp);

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsSetMaster
 * Signature: (IBLjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsSetMaster
  (JNIEnv * env, jobject, jint acsHandle, jbyte u8Master, jobject obj)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1acsSetMaster");

	int nRet = XMS_acsSetMaster(acsHandle, u8Master, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1acsSetMaster");

	return nRet;
}

JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsSetESR
  (JNIEnv * env, jobject obj, jint acsHandle, jobject esr, jint esrParam, jint notifyAll)
{
	//JNIEnv * env 这个结构体中定义了很多JNI的接口函数指针，使开发者可以使用JNI所定义的接口功能
	//jobject obj  表示的是调用这个JNI函数的Java对象，类似于C++中的this 指针
	//后面参数和Java函数原型中一致

	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1acsSetESR");
	//g_cbData.m_pEnv = env;

	//jobject指针不能在多个线程中共享
	g_cbData.m_objCallBack = env->NewGlobalRef(obj); //创建一个全局变量
	g_cbData.m_objInterface = env->NewGlobalRef(esr); //创建一个全局变量


	/***JNIEnv指针不能直接跨线程共享使用,如果强行跨线程,可能造成程序崩溃
	   *java虚拟机的JavaVM指针是整个jvm公用的,我们可以通过JavaVM来得到当
	   *前线程的JNIEnv指针,获取方法 如下:
			JavaVM* gs_jvm;
			env->GetJavaVM(&gs_jvm);
		在另一个线程调用:
			JNIEnv *env;
			gs_jvm->AttachCurrentThread((void **)&env, NULL);
	***/
	env->GetJavaVM(&g_cbData.mg_Jvm);

	int nRet = -1;

	nRet = XMS_acsSetESR ( acsHandle, (EsrFunc)EvtHandler, esrParam, notifyAll );

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1acsSetESR");
	return nRet; 
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsGetDeviceList
 * Signature: (ILDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsGetDeviceList
(JNIEnv * env, jobject, jint acsHandle, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1acsGetDeviceList");
	
	int nRet = XMS_acsGetDeviceList(acsHandle, NULL);
	
	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1acsGetDeviceList");
	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsSetTimer
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsSetTimer
  (JNIEnv *, jobject, jint acsHandle, jint u32Elapse)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1acsSetTimer");

	int nRet = XMS_acsSetTimer(acsHandle, u32Elapse);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1acsSetTimer");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsOpenDevice
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsOpenDevice
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject privateDataObj)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsOpenDevice");

	int nRet = 0;
	DeviceID_t deviceID;

	memset((void*)&deviceID, 0, sizeof(DeviceID_t));

	GetData_DeviceID(env, &deviceObj, &deviceID);
	nRet = XMS_ctsOpenDevice(acsHandle, &deviceID, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsOpenDevice");
	
	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsCloseDevice
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsCloseDevice
  (JNIEnv * env, jobject obj, jint acsHandle, jobject deviceObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsCloseDevice");
	
	int nRet = 0;
	DeviceID_t deviceID;

	memset((void*)&deviceID, 0, sizeof(DeviceID_t));
	
	GetData_DeviceID(env, &deviceObj, &deviceID);

	nRet = XMS_ctsCloseDevice(acsHandle, &deviceID, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsCloseDevice");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsResetDevice
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsResetDevice
  (JNIEnv * env, jobject, jint acsHandle, jobject DevObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsResetDevice");

	DeviceID_t device;
	int nRet = -1;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	GetData_DeviceID(env, &DevObj, &device);

	nRet = XMS_ctsResetDevice(acsHandle, &device, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsResetDevice");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSetDevTimer
 * Signature: (ILDJKeygoe/DeviceID_t;I)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetDevTimer
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jint elapse)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetDevTimer");

	DeviceID_t device;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	
	GetData_DeviceID(env, &deviceObj, &device);
	
	int nRet = XMS_ctsSetDevTimer(acsHandle, &device, elapse);
	
	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetDevTimer");
	
	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsGetDevState
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetDevState
  (JNIEnv * env, jobject, jint acsHandle, jobject DevObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetDevState");

	DeviceID_t device;
	int nRet = -1;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	GetData_DeviceID(env, &DevObj, &device);

	nRet = XMS_ctsGetDevState(acsHandle, &device, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetDevState");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSetDevGroup
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetDevGroup
  (JNIEnv * env, jobject obj, jint acsHandle, jobject deviceObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetDevGroup");

	DeviceID_t device;
	int nRet = -1;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	GetData_DeviceID(env, &deviceObj, &device);

	nRet = XMS_ctsSetDevGroup(acsHandle, &device, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetDevGroup");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsMakeCallOut
 * Signature: (ILDJKeygoe/DeviceID_t;[B[BLDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsMakeCallOut
  (JNIEnv * env, jobject, jint acsHandle, jobject DeviceObj, jbyteArray CallIng, jbyteArray Called, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsMakeCallOut");

	DeviceID_t device;

	memset((void*)&device, 0, sizeof(DeviceID_t));
	
	GetData_DeviceID(env, &DeviceObj, &device);	

	int nRet = XMS_ctsMakeCallOut(acsHandle, &device, (char*)env->GetByteArrayElements(CallIng, NULL), 
		(char*)env->GetByteArrayElements(Called, NULL), NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsMakeCallOut");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSetParam
 * Signature: (ILDJKeygoe/DeviceID_t;S)I
 */
//设置设备参数,obj的类型是不确定的,通过IsInstanceOf判断obj是属于什么类型,
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jshort u16ParamCmdType, jshort u16ParamDataSize, jobject obj)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");

	int nRet = -1;
	jclass cla = NULL;

	DeviceID_t device;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	GetData_DeviceID(env, &deviceObj, &device);

	if (NULL == obj)
	{
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, 0, NULL);

		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/CmdParamData_Voice_t");
	if (env->IsInstanceOf(obj, cla)) //判断对象属于哪个类
	{
		CmdParamData_Voice_t  cmdVocData;

		memset((void*)&cmdVocData, 0, sizeof(CmdParamData_Voice_t));

		GetData_CmdVoice(env, &cmdVocData, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParamData_Voice_t), (void*)&cmdVocData);
	
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/CmdParamData_GtdFreq_t");
	if (env->IsInstanceOf(obj, cla))
	{
		CmdParamData_GtdFreq_t GtdFreq;
		
		memset((void*)&GtdFreq, 0, sizeof(CmdParamData_GtdFreq_t));
		
		GetData_GtdFreq(env, &GtdFreq, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParamData_GtdFreq_t), (void*)&GtdFreq);
	
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/CmdParamData_GtdProtoType_t");
	if (env->IsInstanceOf(obj, cla))
	{
		CmdParamData_GtdProtoType_t GtdProtoType;
		
		memset((void*)&GtdProtoType, 0, sizeof(CmdParamData_GtdProtoType_t));
		
		GetData_GtdProtoType(env, &GtdProtoType, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParamData_GtdProtoType_t), (void*)&GtdProtoType);
	
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/CmdParamData_AnalogTrunk_t");
	if (env->IsInstanceOf(obj, cla))
	{
		CmdParamData_AnalogTrunk_t AnalogTrk;
		
		memset((void *)&AnalogTrk, 0, sizeof(CmdParamData_AnalogTrunk_t));

		GetData_AnalogTrunk(env, &AnalogTrk, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParamData_AnalogTrunk_t), (void*)&AnalogTrk);
	
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/CmdParamData_CAS_t");
	if (env->IsInstanceOf(obj, cla))
	{
		CmdParamData_CAS_t CasData;
		
		memset((void *)&CasData, 0, sizeof(CmdParamData_CAS_t));

		GetData_Cas(env, &CasData, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParamData_CAS_t), (void*)&CasData);
	
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/CmdParamData_AnalogUser_t");
	if (env->IsInstanceOf(obj, cla))
	{
		CmdParamData_AnalogUser_t AnalogUserData;
		
		memset((void*)&AnalogUserData, 0, sizeof(CmdParamData_AnalogUser_t));
		
		GetData_AnalogUser(env, &AnalogUserData, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParamData_AnalogUser_t), (void*)&AnalogUserData);
	
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/CmdParamData_FlashParam_t");
	if (env->IsInstanceOf(obj, cla))
	{
		CmdParamData_FlashParam_t FlashParamData;

		memset((void*)&FlashParamData, 0, sizeof(CmdParamData_FlashParam_t));

		GetData_FlashParam(env, &FlashParamData, &obj);

		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParamData_FlashParam_t), (void*)&FlashParamData);
	
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/CmdParamData_AnalogTrunkFlash_t");
	if (env->IsInstanceOf(obj, cla))
	{
		CmdParamData_AnalogTrunkFlash_t AnalogTrkFlash;

		memset((void*)&AnalogTrkFlash, 0, sizeof(CmdParamData_AnalogTrunkFlash_t));

		GetData_AnalogTrkFlash(env, &AnalogTrkFlash, &obj);

		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParamData_AnalogTrunkFlash_t), &AnalogTrkFlash);
	
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/CmdParamData_TrunkFlashParam_t");
	if (env->IsInstanceOf(obj, cla))
	{
		CmdParamData_TrunkFlashParam_t TrkFlash;

		memset((void*)&TrkFlash, 0, sizeof (CmdParamData_TrunkFlashParam_t));

		GetData_TrkFlash(env, &TrkFlash, &obj);

		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParamData_TrunkFlashParam_t), &TrkFlash);
	
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/CmdParamData_FskParam_t");
	if (env->IsInstanceOf(obj, cla))
	{
		CmdParamData_FskParam_t FskParam;

		memset((void*)&FskParam, 0, sizeof(CmdParamData_FskParam_t));
		
		GetData_FskParam(env, &FskParam, &obj);

		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParamData_FskParam_t), &FskParam);

		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/Acs_AnalogEM_CMD");
	if (env->IsInstanceOf(obj, cla))
	{
		Acs_AnalogEM_CMD AnalogEmCMd;

		memset((void*)&AnalogEmCMd, 0, sizeof(Acs_AnalogEM_CMD));

		GetData_AnalogEmCMD(env, &AnalogEmCMd, &obj);

		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(Acs_AnalogEM_CMD), &AnalogEmCMd);

		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/Acs_SetFaxBps");
	if (env->IsInstanceOf(obj, cla))
	{
		Acs_SetFaxBps SetFaxBps;

		memset((void*)&SetFaxBps, 0, sizeof(Acs_SetFaxBps));

		GetData_SetFaxBps(env, &SetFaxBps, &obj);

		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(Acs_SetFaxBps), &SetFaxBps);

		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/Acs_TransAddHeader");
	if (env->IsInstanceOf(obj, cla))
	{
		Acs_TransAddHeader TransAddHeader;
		
		memset((void*)&TransAddHeader, 0, sizeof(Acs_TransAddHeader));
		
		GetData_TransAddHeader(env, &TransAddHeader, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(Acs_TransAddHeader), &TransAddHeader);

		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/Acs_TransAddFile");
	if (env->IsInstanceOf(obj, cla))
	{
		Acs_TransAddFile TransAddFile;

		memset((void*)&TransAddFile, 0, sizeof(Acs_TransAddFile));

		GetData_TransAddFile(env, &TransAddFile, &obj);

		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(Acs_TransAddFile), &TransAddFile);

		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/Acs_SetECM");
	if (env->IsInstanceOf(obj, cla))
	{
		Acs_SetECM SetEcm;
		
		memset((void*)&SetEcm, 0, sizeof(Acs_SetECM));
		
		GetData_SetEcm(env, &SetEcm, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(Acs_SetECM), &SetEcm);

		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/CmdParamData_CTCLKNET_t");
	if (env->IsInstanceOf(obj, cla))
	{
		CmdParamData_CTCLKNET_t CtClknet;
		
		memset((void*)&CtClknet, 0, sizeof(CmdParamData_CTCLKNET_t));
		
		GetData_CtClkNet(env, &CtClknet, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParamData_CTCLKNET_t), &CtClknet);
		
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/CmdParam_SilenceDetectParam_t");
	if (env->IsInstanceOf(obj, cla))
	{
		CmdParam_SilenceDetectParam_t SilenceDetect;
		
		memset((void*)&SilenceDetect, 0, sizeof(CmdParam_SilenceDetectParam_t));
		
		GetData_SilenceDetect(env, &SilenceDetect, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParam_SilenceDetectParam_t), &SilenceDetect);
	
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/CmdParam_VADMinDetectParam_t");
	if (env->IsInstanceOf(obj, cla))
	{
		CmdParam_VADMinDetectParam_t VadMinDetect;
		
		memset((void*)&VadMinDetect, 0, sizeof(CmdParam_VADMinDetectParam_t));
		
		GetData_VadMinDetect(env, &VadMinDetect, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParam_VADMinDetectParam_t), &VadMinDetect);

		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/CmdParam_BoardCommonParam_t");
	if (env->IsInstanceOf(obj, cla))
	{
		CmdParam_BoardCommonParam_t BrdCommon;
		
		memset((void*)&BrdCommon, 0, sizeof(CmdParam_BoardCommonParam_t));
		
		GetData_BoardCommon(env, &BrdCommon, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParam_BoardCommonParam_t), &BrdCommon);

		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/CmdParamData_324CH_t");
	if (env->IsInstanceOf(obj, cla))
	{
		CmdParamData_324CH_t _324CH_t;
		
		memset((void*)&_324CH_t, 0, sizeof(CmdParamData_324CH_t));
		
		GetData_324CH_t(env, &_324CH_t, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParamData_324CH_t), &_324CH_t);
		
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/Acs_VoIP_RTPOpen");
	if (env->IsInstanceOf(obj, cla))
	{
		Acs_VoIP_RTPOpen RtpOpen;
		
		memset((void*)&RtpOpen, 0, sizeof(Acs_VoIP_RTPOpen));
		
		GetData_RtpOpen(env, &RtpOpen, &obj);
			
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(Acs_VoIP_RTPOpen), &RtpOpen);
		
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/Acs_VoIP_RTPSESSION");
	if (env->IsInstanceOf(obj, cla))
	{
		Acs_VoIP_RTPSESSION RtpSession;
		
		memset((void*)&RtpSession, 0, sizeof(Acs_VoIP_RTPSESSION));
		
		GetData_RtpSession(env, &RtpSession, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(Acs_VoIP_RTPSESSION), &RtpSession);
		
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}
	
	cla = env->FindClass("DJKeygoe/Acs_VoIP_RTPADDR");
	if (env->IsInstanceOf(obj, cla))
	{
		Acs_VoIP_RTPADDR RtpAddr;
		
		memset((void*)&RtpAddr, 0, sizeof(Acs_VoIP_RTPADDR));
		
		GetData_RtpAddr(env, &RtpAddr, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(Acs_VoIP_RTPADDR), &RtpAddr);
		
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/Acs_VoIP_RTPCODEC");
	if (env->IsInstanceOf(obj, cla))
	{
		Acs_VoIP_RTPCODEC RtpCodec;
		
		memset((void*)&RtpCodec, 0, sizeof(Acs_VoIP_RTPCODEC));
		
		GetData_RtpCodec(env, &RtpCodec, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(Acs_VoIP_RTPCODEC), &RtpCodec);
		
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/MixerControlParam_t");
	if (env->IsInstanceOf(obj, cla))
	{
		MixerControlParam_t MixCtrl;
		
		memset((void*)&MixCtrl, 0, sizeof(MixerControlParam_t));
		
		GetData_MixerControlParam(env, &obj, &MixCtrl);
			
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(MixerControlParam_t), &MixCtrl);
		
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	cla = env->FindClass("DJKeygoe/Acs_VoIP_MediaInfo");
	if (env->IsInstanceOf(obj, cla))
	{
		Acs_VoIP_MediaInfo MediaInfo;
		
		memset((void*)&MediaInfo, 0, sizeof(Acs_VoIP_MediaInfo));
		
		GetData_MediaInfo(env, &MediaInfo, &obj);
		
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, sizeof(Acs_VoIP_MediaInfo), &MediaInfo);
		
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	if (u16ParamCmdType == ISDN_PARAM_APPENDCALLEE 
		|| u16ParamCmdType == ISDN_PARAM_ORINUMBER
		|| u16ParamCmdType == ISDN_PARAM_CALLTYPE)
	{
		nRet = XMS_ctsSetParam(acsHandle, &device, u16ParamCmdType, u16ParamDataSize, env->GetByteArrayElements((jbyteArray)obj, NULL));
		
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
		
		return nRet;
	}

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetParam");
	
	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsGetParam
 * Signature: (ILDJKeygoe/DeviceID_t;SLjava/lang/Object;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetParam
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jshort u16ParamCmdType, jshort u16ParamDataSize, jobject obj)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetParam");
	
	DeviceID_t device;
	int nRet = -1;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	GetData_DeviceID(env, &deviceObj, &device);

	if (obj == NULL)
	{
		nRet = XMS_ctsGetParam(acsHandle, &device, u16ParamCmdType, u16ParamDataSize, NULL);

		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetParam");

		return nRet;
	}

	jclass targetClaBoardInfo = env->FindClass("DJKeygoe/Acs_ParamData_UserReadXmsBoardInfo");
	if (env->IsInstanceOf(obj, targetClaBoardInfo)) //如果传入的是Acs_ParamData_UserReadXmsBoardInfo对象
	{
		Acs_ParamData_UserReadXmsBoardInfo BoardInfo;

		memset((void*)&BoardInfo, 0, sizeof(Acs_ParamData_UserReadXmsBoardInfo));
		
		GetData_BoardInfo(env, &BoardInfo, &obj);

		nRet = XMS_ctsGetParam(acsHandle, &device, u16ParamCmdType, sizeof(Acs_ParamData_UserReadXmsBoardInfo), (DJ_Void*)&BoardInfo);

		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetParam");

		return nRet;
	}

	jclass targetClaReadVoltage = env->FindClass("DJKeygoe/CmdParamData_ReadVoltage_t");
	if (env->IsInstanceOf(obj, targetClaReadVoltage)) //如果传入的是CmdParamData_ReadVoltage_t对象
	{
		CmdParamData_ReadVoltage_t ReadVoltage;

		memset((void*)&ReadVoltage, 0, sizeof(CmdParamData_ReadVoltage_t));

		GetData_ReadVoltage(env, &ReadVoltage, &obj);

		nRet = XMS_ctsGetParam(acsHandle, &device, u16ParamCmdType, sizeof(CmdParamData_ReadVoltage_t), (DJ_Void*)&ReadVoltage);
	
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetParam");
		
		return nRet;
	}

	jclass targetCla3GppCfg = env->FindClass("DJKeygoe/Get3gppCfg_t");
	if (env->IsInstanceOf(obj, targetCla3GppCfg)) 
	{
		Get3gppCfg_t _3GppCfg;
		
		memset((void*)&_3GppCfg, 0, sizeof(Get3gppCfg_t));
		
		GetData_3GppCfg(env, &_3GppCfg, &obj);
		
		nRet = XMS_ctsGetParam(acsHandle, &device, u16ParamCmdType, sizeof(Get3gppCfg_t), (DJ_Void*)&_3GppCfg);
		
		LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetParam");
		
		return nRet;
	}

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsAlertCall
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsAlertCall
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsAlertCall");

	DeviceID_t device;
	int nRet = -1;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	GetData_DeviceID(env, &deviceObj, &device);
	
	nRet = XMS_ctsAlertCall(acsHandle, &device, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsAlertCall");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsAnswerCallIn
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsAnswerCallIn
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsAnswerCallIn");

	DeviceID_t device;
	int nRet = -1;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	GetData_DeviceID(env, &deviceObj, &device);
	
	nRet = XMS_ctsAnswerCallIn(acsHandle, &device, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsAnswerCallIn");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsUnlinkDevice
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsUnlinkDevice
  (JNIEnv * env, jobject obj, jint acsHandle, jobject dev1Obj, jobject dev2Obj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsUnlinkDevice");

	DeviceID_t Dev1, Dev2;

	int nRet = -1;

	memset((void*)&Dev1, 0, sizeof(DeviceID_t));
	memset((void*)&Dev2, 0, sizeof(DeviceID_t));

	GetData_DeviceID(env, &dev1Obj, &Dev1);
	GetData_DeviceID(env, &dev2Obj, &Dev2);

	nRet = XMS_ctsUnlinkDevice(acsHandle, &Dev1, &Dev2, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsUnlinkDevice");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsLinkDevice
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsLinkDevice
  (JNIEnv * env, jobject, jint acsHandle, jobject dev1Obj, jobject dev2Obj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsLinkDevice");

	DeviceID_t Dev1, Dev2;
	
	int nRet = -1;
	
	memset((void*)&Dev1, 0, sizeof(DeviceID_t));
	memset((void*)&Dev2, 0, sizeof(DeviceID_t));
	
	GetData_DeviceID(env, &dev1Obj, &Dev1);
	GetData_DeviceID(env, &dev2Obj, &Dev2);
	
	nRet = XMS_ctsLinkDevice(acsHandle, &Dev1, &Dev2, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsLinkDevice");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsClearCall
 * Signature: (ILDJKeygoe/DeviceID_t;ILDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsClearCall
  (JNIEnv * env, jobject, jint acsHandle, jobject DevObj, jint s32ClearCause, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsClearCall");
	
	DeviceID_t device;
	int nRet = -1;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	GetData_DeviceID(env, &DevObj, &device);
	
	nRet = XMS_ctsClearCall(acsHandle, &device, s32ClearCause, NULL);
	
	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsClearCall");
	
	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsJoinToConf
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;LDJKeygoe/CmdParamData_Conf_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsJoinToConf
  (JNIEnv * env, jobject obj, jint acsHandle, jobject confDeviceObj, jobject mediaDeviceObj, jobject CmdConfDataObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsJoinToConf");

	DeviceID_t ConfDevice, MediaDevice;
	CmdParamData_Conf_t ConfData;

	memset((void*)&ConfDevice, 0, sizeof(DeviceID_t));
	memset((void*)&MediaDevice, 0, sizeof(DeviceID_t));
	memset((void*)&ConfData, 0, sizeof(CmdParamData_Conf_t));

	GetData_DeviceID(env, &confDeviceObj, &ConfDevice);
	GetData_DeviceID(env, &mediaDeviceObj, &MediaDevice);

	GetData_CmdConf(env, &CmdConfDataObj, &ConfData);

	int nRet = XMS_ctsJoinToConf(acsHandle, &ConfDevice, &MediaDevice, &ConfData, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsJoinToConf");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsLeaveFromConf
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;LDJKeygoe/CmdParamData_Conf_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsLeaveFromConf
  (JNIEnv * env, jobject obj, jint acsHandle, jobject confDeviceObj, jobject mediaDeviceObj, jobject CmdConfDataObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsLeaveFromConf");

	DeviceID_t ConfDevice, MediaDevice;
	CmdParamData_Conf_t ConfData;

	memset((void*)&ConfDevice, 0, sizeof(DeviceID_t));
	memset((void*)&MediaDevice, 0, sizeof(DeviceID_t));
	memset((void*)&ConfData, 0, sizeof(CmdParamData_Conf_t));

	GetData_DeviceID(env, &confDeviceObj, &ConfDevice);
	GetData_DeviceID(env, &mediaDeviceObj, &MediaDevice);

	GetData_CmdConf(env, &CmdConfDataObj, &ConfData);

	int nRet = XMS_ctsLeaveFromConf(acsHandle, &ConfDevice, &MediaDevice, &ConfData, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsLeaveFromConf");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsClearConf
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsClearConf
  (JNIEnv * env, jobject, jint acsHandle, jobject confDeviceObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsClearConf");

	DeviceID_t ConfDevice;

	memset((void*)&ConfDevice, 0, sizeof(DeviceID_t));

	GetData_DeviceID(env, &confDeviceObj, &ConfDevice);

	int nRet = XMS_ctsClearConf(acsHandle, &ConfDevice, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsClearConf");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsPlay
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PlayProperty_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsPlay
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject playPropertyObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsPlay");

	DeviceID_t device;
	PlayProperty_t playProtery;
	int nRet = -1;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	memset((void*)&playProtery, 0, sizeof(PlayProperty_t));

	GetData_DeviceID(env, &deviceObj, &device);
	GetData_PlayProperty(env, &playPropertyObj, &playProtery);

	nRet = XMS_ctsPlay(acsHandle, &device, &playProtery, NULL);

	LogInfo(playProtery.m_s8PlayContent);
	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsPlay");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsInitPlayIndex
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsInitPlayIndex
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsInitPlayIndex");

	DeviceID_t device;
	int nRet = 0;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	GetData_DeviceID(env, &deviceObj, &device);

	nRet = XMS_ctsInitPlayIndex(acsHandle, &device, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsInitPlayIndex");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsBuildPlayIndex
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PlayProperty_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsBuildPlayIndex
  (JNIEnv * env, jobject, jint acsHandle, jobject MediaDevObj, jobject playPropertyObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsBuildPlayIndex");

	PlayProperty_t  playProperty;
	DeviceID_t	    MediaDevice;
	int nRet = 0;
	
	memset((void*)&MediaDevice, 0, sizeof(DeviceID_t));
	memset((void*)&playProperty, 0, sizeof(PlayProperty_t));

	GetData_DeviceID(env, &MediaDevObj, &MediaDevice);
	GetData_PlayProperty(env, &playPropertyObj, &playProperty);
	
	nRet = XMS_ctsBuildPlayIndex(acsHandle, &MediaDevice, &playProperty, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsBuildPlayIndex");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsControlPlay
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/ControlPlay_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlPlay
  (JNIEnv * env, jobject obj, jint acsHandle, jobject deviceIdObj, jobject ControlPlayObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlPlay");

	DeviceID_t deviceID;
	ControlPlay_t	controlPlay;

	int nRet = 0;

	memset((void*)&deviceID, 0, sizeof(DeviceID_t));
	memset((void*)&controlPlay, 0, sizeof(ControlPlay_t));

	GetData_DeviceID(env, &deviceIdObj, &deviceID); 
	GetData_ControlPlay(env, &ControlPlayObj, &controlPlay);

	nRet = XMS_ctsControlPlay ( acsHandle, &deviceID, &controlPlay, NULL );

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlPlay");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsRecord
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/RecordProperty_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsRecord
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject recordPropertyObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsRecord");
	
	DeviceID_t device;
	RecordProperty_t recordProtery;
	int nRet = 0;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	memset((void*)&recordProtery, 0, sizeof(RecordProperty_t));
	
	GetData_DeviceID(env, &deviceObj, &device);
	GetData_RecordProperty(env, &recordPropertyObj, &recordProtery);
	

	nRet = XMS_ctsRecord(acsHandle, &device, &recordProtery, NULL);
	
	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsRecord");
	
	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsControlRecord
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/ControlRecord_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlRecord
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject ctrlRecordObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlRecord");
	
	DeviceID_t device;
	ControlRecord_t ctrlRecord;
	int nRet = -1;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	memset((void*)&ctrlRecord, 0, sizeof(ControlRecord_t));
	
	GetData_DeviceID(env, &deviceObj, &device);
	GetData_CtrlRecord(env, &ctrlRecordObj, &ctrlRecord);
	
	nRet = XMS_ctsControlRecord(acsHandle, &device, &ctrlRecord, NULL);
	
	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlRecord");
	
	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSendFax
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;BBLDJKeygoe/PrivateData_t;)I
 */
//PrivateData_t字段可能有不同应用 发送T38时,发送的是FaxPrivate_t结构体的数据
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendFax
  (JNIEnv * env, jobject obj, jint acsHandle, jobject faxDeviceObj, jobject mediaDeviceObj, 
  jbyteArray s8TiffFile, jbyteArray s8LocalID, jobject objPrivate)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendFax");

	DeviceID_t faxDeviceID, mediaDeviceID;
	int nRet = -1;

	memset((void*)&faxDeviceID, 0, sizeof(DeviceID_t));
	memset((void*)&mediaDeviceID, 0, sizeof(DeviceID_t));

	GetData_DeviceID(env, &faxDeviceObj, &faxDeviceID);
	GetData_DeviceID(env, &mediaDeviceObj, &mediaDeviceID);

	if (objPrivate == NULL)
	{
		nRet = XMS_ctsSendFax(acsHandle, &faxDeviceID, &mediaDeviceID, 
			(char*)env->GetByteArrayElements(s8TiffFile, NULL), (char*)env->GetByteArrayElements(s8LocalID, NULL), NULL);
	}
	else
	{
		jclass targerCla = env->FindClass("DJKeygoe/FaxPrivate_t");
		if (env->IsInstanceOf(objPrivate, targerCla)) //如果Java穿过来的对象属于FaxPrivate_t实例(发送T38)
		{
			FaxPrivate_t faxPrivate;
			
			memset((void*)&faxPrivate, 0, sizeof(FaxPrivate_t));
			
			GetData_FaxPrivate(env, &objPrivate, &faxPrivate);
			
			nRet = XMS_ctsSendFax(acsHandle, &faxDeviceID, &mediaDeviceID, 
				(char*)env->GetByteArrayElements(s8TiffFile, NULL), (char*)env->GetByteArrayElements(s8LocalID, NULL), (PrivateData_t*)&faxPrivate);
		} 
	}

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendFax");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsStopSendFax
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsStopSendFax
  (JNIEnv * env, jobject obj, jint acsHandle, jobject faxDeviceObj, jobject objPrivate)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsStopSendFax");

	DeviceID_t faxDeviceID;
	int nRet = 0;

	memset((void*)&faxDeviceID, 0, sizeof(DeviceID_t));

	GetData_DeviceID(env, &faxDeviceObj, &faxDeviceID);

	if (objPrivate == NULL)
	{
		nRet = XMS_ctsStopSendFax(acsHandle, &faxDeviceID, NULL);
	}
	else
	{
		jclass targerCla = env->FindClass("DJKeygoe/FaxPrivate_t");
		if (env->IsInstanceOf(objPrivate, targerCla)) //如果Java穿过来的对象属于FaxPrivate_t实例(发送T38)
		{
			FaxPrivate_t faxPrivate;

			memset((void*)&faxPrivate, 0, sizeof(FaxPrivate_t));

			GetData_FaxPrivate(env, &objPrivate, &faxPrivate);

			nRet = XMS_ctsStopSendFax(acsHandle, &faxDeviceID, (PrivateData_t*)&faxPrivate);
		} 
	}

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsStopSendFax");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsReceiveFax
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;[B[BLDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsReceiveFax
  (JNIEnv * env, jobject, jint acsHandle, jobject faxDeviceObj, jobject mediaDeviceObj, 
	jbyteArray s8TiffFile, jbyteArray s8LocalID, jobject privateObj)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsReceiveFax");
	
	DeviceID_t faxDeviceID, mediaDeviceID;
	int nRet = 0;
	
	memset((void*)&faxDeviceID, 0, sizeof(DeviceID_t));
	memset((void*)&mediaDeviceID, 0, sizeof(DeviceID_t));
	
	GetData_DeviceID(env, &faxDeviceObj, &faxDeviceID);
	GetData_DeviceID(env, &mediaDeviceObj, &mediaDeviceID);
	
	if (NULL == privateObj)
	{
		nRet = XMS_ctsSendFax(acsHandle, &faxDeviceID, &mediaDeviceID, 
			(char*)env->GetByteArrayElements(s8TiffFile, NULL), (char*)env->GetByteArrayElements(s8LocalID, NULL), NULL);
	}
	else
	{
		jclass targerCla = env->FindClass("DJKeygoe/FaxPrivate_t");
		if (env->IsInstanceOf(privateObj, targerCla)) //如果Java穿过来的对象属于FaxPrivate_t实例(发送T38)
		{
			FaxPrivate_t faxPrivate;
			
			memset((void*)&faxPrivate, 0, sizeof(FaxPrivate_t));
			
			GetData_FaxPrivate(env, &privateObj, &faxPrivate);
			
			nRet = XMS_ctsSendFax(acsHandle, &faxDeviceID, &mediaDeviceID, 
				(char*)env->GetByteArrayElements(s8TiffFile, NULL), (char*)env->GetByteArrayElements(s8LocalID, NULL), (PrivateData_t*)&faxPrivate);
		} 
	}
	
	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsReceiveFax");
	
	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsStopReceiveFax
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsStopReceiveFax
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject privateObj)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsStopReceiveFax");
	
	DeviceID_t faxDeviceID;
	int nRet = 0;
	
	memset((void*)&faxDeviceID, 0, sizeof(DeviceID_t));
	
	GetData_DeviceID(env, &deviceObj, &faxDeviceID);
	
	if (privateObj == NULL)
	{
		nRet = XMS_ctsStopReceiveFax(acsHandle, &faxDeviceID, NULL);
	}
	else
	{
		jclass targerCla = env->FindClass("DJKeygoe/FaxPrivate_t");
		if (env->IsInstanceOf(privateObj, targerCla)) //如果Java穿过来的对象属于FaxPrivate_t实例(发送T38)
		{
			FaxPrivate_t faxPrivate;
			
			memset((void*)&faxPrivate, 0, sizeof(FaxPrivate_t));
			
			GetData_FaxPrivate(env, &privateObj, &faxPrivate);
			
			nRet = XMS_ctsStopReceiveFax(acsHandle, &faxDeviceID, (PrivateData_t*)&faxPrivate);
		}
	}
	
	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsStopReceiveFax");
	
	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsChangeMonitorFilter
 * Signature: (ILDJKeygoe/DeviceID_t;ILDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsChangeMonitorFilter
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jint monitorFilter, jobject obj)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsChangeMonitorFilter");

	int nRet = -1;

	DeviceID_t device;

	memset((void*)&device, 0, sizeof(DeviceID_t));

	GetData_DeviceID(env, &deviceObj, &device);

	nRet = XMS_ctsChangeMonitorFilter(acsHandle, &device, monitorFilter, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsChangeMonitorFilter");
	
	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSendIOData
 * Signature: (ILDJKeygoe/DeviceID_t;SS[B)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendIOData
  (JNIEnv * env, jobject obj, jint acsHandle, jobject deviceObj, jshort u16IoType, jshort u16IoDataLen, jbyteArray pSendIOData)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendIOData");

	DeviceID_t device;

	memset((void*)&device, 0, sizeof(DeviceID_t));

	GetData_DeviceID(env, &deviceObj, &device);

	int nRet = XMS_ctsSendIOData(acsHandle, &device, u16IoType, u16IoDataLen, env->GetByteArrayElements(pSendIOData, NULL));

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendIOData");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSendSignalMsg
 * Signature: (ILDJKeygoe/DeviceID_t;S)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendSignalMsg
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jshort u16SignalMsgType)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendSignalMsg");
	
	DeviceID_t device;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	
	GetData_DeviceID(env, &deviceObj, &device);
	
	int nRet = XMS_ctsSendSignalMsg(acsHandle, &device, u16SignalMsgType);
	
	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendSignalMsg");
	
	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsOpenStreamExt
 * Signature: (ILDJKeygoe/ServerID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsOpenStreamExt
  (JNIEnv * env, jobject, jint acsHandle, jobject serverIDObj, jobject privateObj)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1acsOpenStreamExt");
	
	ServerID_t serverID;
	
	memset((void*)&serverID, 0, sizeof(ServerID_t));

	GetData_ServerID(env, &serverIDObj, &serverID);
	
	int nRet = XMS_acsOpenStreamExt(acsHandle, &serverID, NULL);
	
	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1acsOpenStreamExt");
	
	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsCloseStreamExt
 * Signature: (ILDJKeygoe/ServerID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsCloseStreamExt
  (JNIEnv * env, jobject, jint acsHandle, jobject serverObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1acsCloseStreamExt");
	
	ServerID_t serverID;
	
	memset((void*)&serverID, 0, sizeof(ServerID_t));
	
	GetData_ServerID(env, &serverObj, &serverID);
	
	int nRet = XMS_acsCloseStreamExt(acsHandle, &serverID, NULL);
	
	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1acsCloseStreamExt");
	
	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsPlayCSP
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/CSPPlayProperty_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsPlayCSP
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject cspPlayObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsPlayCSP");

	DeviceID_t device;
	CSPPlayProperty_t cspPlay;

	memset((void*)&device, 0, sizeof(DeviceID_t));
	memset((void*)&cspPlay, 0, sizeof(CSPPlayProperty_t));

	GetData_DeviceID(env, &deviceObj, &device);
	GetData_CspPlay(env, &cspPlayObj, &cspPlay);

	int nRet = XMS_ctsPlayCSP(acsHandle, &device, &cspPlay, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsPlayCSP");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSendCSPData
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/CSPPlayDataInfo_t;[BLDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendCSPData
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject cspPlayDataObj, jbyteArray pSendCspData, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendCSPData");

	DeviceID_t device;
	CSPPlayDataInfo_t cspDataInfo;

	memset((void*)&device, 0, sizeof(DeviceID_t));
	memset((void*)&cspDataInfo, 0, sizeof(CSPPlayDataInfo_t));

	GetData_DeviceID(env, &deviceObj, &device);
	GetData_CspPlayInfo(env, &cspPlayDataObj, &cspDataInfo);

	int nRet = XMS_ctsSendCSPData(acsHandle, &device, &cspDataInfo, env->GetByteArrayElements(pSendCspData, NULL), NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendCSPData");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsControlPlayCSP
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/ControlPlay_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlPlayCSP
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject CtrlPlayObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlPlayCSP");

	DeviceID_t device;
	ControlPlay_t ctrlPlay;

	memset((void*)&device, 0, sizeof(DeviceID_t));
	memset((void*)&ctrlPlay, 0, sizeof(ControlPlay_t));

	GetData_DeviceID(env, &deviceObj, &device);
	GetData_CtrlPlay(env, &CtrlPlayObj, &ctrlPlay);

	int nRet = XMS_ctsControlPlayCSP(acsHandle, &device, &ctrlPlay, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlPlayCSP");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsRecordCSP
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/RecordCSPProperty_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsRecordCSP
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject recordCspObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsRecordCSP");

	DeviceID_t device;
	RecordCSPProperty_t recordCsp;

	memset((void*)&device, 0, sizeof(DeviceID_t));
	memset((void*)&recordCsp, 0, sizeof(RecordCSPProperty_t));

	GetData_DeviceID(env, &deviceObj, &device);
	GetData_RecordCsp(env, &recordCspObj, &recordCsp);

	int nRet = XMS_ctsRecordCSP(acsHandle, &device, &recordCsp, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsRecordCSP");
	
	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsControlRecordCSP
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/ControlRecord_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlRecordCSP
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject ctrlRecordObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlRecordCSP");

	DeviceID_t device;
	ControlRecord_t ctrlRecord;

	memset((void*)&device, 0, sizeof(DeviceID_t));
	memset((void*)&ctrlRecord, 0, sizeof(ControlRecord_t));

	GetData_DeviceID(env, &deviceObj, &device);
	GetData_CtrlRecord(env, &ctrlRecordObj, &ctrlRecord);

	int nRet = XMS_ctsControlRecordCSP(acsHandle, &device, &ctrlRecord, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControlRecordCSP");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsInitPlay3gppIndex
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsInitPlay3gppIndex
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsInitPlay3gppIndex");

	DeviceID_t device;

	memset((void*)&device, 0, sizeof(DeviceID_t));

	GetData_DeviceID(env, &deviceObj, &device);

	int nRet = XMS_ctsInitPlay3gppIndex(acsHandle, &device, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsInitPlay3gppIndex");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsBuildPlay3gppIndex
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/Play3gppProperty_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsBuildPlay3gppIndex
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject play3GppObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsBuildPlay3gppIndex");

	DeviceID_t device;
	Play3gppProperty_t play3Gpp;

	memset((void*)&device, 0, sizeof(DeviceID_t));
	memset((void*)&play3Gpp, 0, sizeof(Play3gppProperty_t));

	GetData_DeviceID(env, &deviceObj, &device);
	GetData_Play3GppIndex(env, &play3GppObj, &play3Gpp); 

	int nRet = XMS_ctsBuildPlay3gppIndex(acsHandle, &device, &play3Gpp, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsBuildPlay3gppIndex");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_cts3gppPlay
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/Play3gppProperty_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1cts3gppPlay
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject play3GppObj, jobject mediaObj)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1cts3gppPlay");

	DeviceID_t device;
	Play3gppProperty_t play3Gpp;
	int nRet = 0;

	memset((void*)&device, 0, sizeof(DeviceID_t));
	memset((void*)&play3Gpp, 0, sizeof(Play3gppProperty_t));

	GetData_DeviceID(env, &deviceObj, &device);
	GetData_Play3GppIndex(env, &play3GppObj, &play3Gpp);
	
	if (mediaObj == NULL)
	{
		nRet = XMS_cts3gppPlay(acsHandle, &device, &play3Gpp, NULL); 
	}
	else
	{
		jclass targerCla = env->FindClass("DJKeygoe/Acs_MediaEx_Play");
		if (env->IsInstanceOf(mediaObj, targerCla)) //如果Java穿过来的对象属于FaxPrivate_t实例(发送T38)
		{
			Acs_MediaEx_Play mediaPlay;
			
			memset((void*)&mediaPlay, 0, sizeof(Acs_MediaEx_Play));
			
			GetData_MediaPlay(env, &mediaObj, &mediaPlay);
			
			nRet = XMS_cts3gppPlay(acsHandle, &device, &play3Gpp, (PrivateData_t*)&mediaPlay);
		} 
	}
	
	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1cts3gppPlay");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsControl3gppPlay
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/Control3gppPlay_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControl3gppPlay
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject ctrl3GppPlayObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControl3gppPlay");

	DeviceID_t device;
	Control3gppPlay_t ctrl3GppPlay;

	memset((void*)&device, 0, sizeof(DeviceID_t));
	memset((void*)&ctrl3GppPlay, 0, sizeof(Control3gppPlay_t));

	GetData_DeviceID(env, &deviceObj, &device);
	GetData_Ctrl3GpPlay(env, &ctrl3GppPlayObj, &ctrl3GppPlay);

	int nRet = XMS_ctsControl3gppPlay(acsHandle, &device, &ctrl3GppPlay, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControl3gppPlay");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_cts3gppRecord
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/Record3gppProperty_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1cts3gppRecord
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject record3GppObj, jobject Obj)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1cts3gppRecord");

	DeviceID_t device;
	Record3gppProperty_t rcord3Gpp;
	int nRet = 0;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	memset((void*)&rcord3Gpp, 0, sizeof(Record3gppProperty_t));
	
	GetData_DeviceID(env, &deviceObj, &device);
	GetData_Record3Gpp(env, &record3GppObj, &rcord3Gpp);
	
	if (NULL == Obj)
	{
		nRet = XMS_cts3gppRecord(acsHandle, &device, &rcord3Gpp, NULL);
	}
	else
	{
		jclass targerCla = env->FindClass("DJKeygoe/Acs_MediaEx_Record");
		if (env->IsInstanceOf(Obj, targerCla)) //如果Java穿过来的对象属于Acs_MediaEx_Record实例
		{
			Acs_MediaEx_Record mediaRecord;
			
			memset((void*)&mediaRecord, 0, sizeof(Acs_MediaEx_Record));
			
			GetData_MediaRecord(env, &Obj, &mediaRecord);
				
			nRet = XMS_cts3gppRecord(acsHandle, &device, &rcord3Gpp, (PrivateData_t*)&mediaRecord);
		} 
	}

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1cts3gppRecord");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsControl3gppRecord
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/Control3gppRecord_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControl3gppRecord
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject ctrl3GppRecordObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControl3gppRecord");

	DeviceID_t device;
	Control3gppRecord_t ctrl3GppRecord;

	memset((void*)&device, 0, sizeof(DeviceID_t));
	memset((void*)&ctrl3GppRecord, 0, sizeof(Control3gppRecord_t));

	GetData_DeviceID(env, &deviceObj, &device);
	GetData_Ctrl3GppRecord(env, &ctrl3GppRecordObj, &ctrl3GppRecord);

	int nRet = XMS_ctsControl3gppRecord(acsHandle, &device, &ctrl3GppRecord, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsControl3gppRecord");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsQueryLicense
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsQueryLicense
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1acsQueryLicense");

	DeviceID_t device;

	memset((void*)&device, 0, sizeof(DeviceID_t));

	GetData_DeviceID(env, &deviceObj, &device);

	int nRet = XMS_acsQueryLicense(acsHandle, &device, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1acsQueryLicense");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctxRegister
 * Signature: (I[BBLDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctxRegister
  (JNIEnv * env, jobject, jint acsHandle, jbyteArray s8AppRegName, jbyte u8RegType, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctxRegister");

	int nRet = XMS_ctxRegister(acsHandle, (DJ_S8*)env->GetByteArrayElements(s8AppRegName, NULL), u8RegType, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctxRegister");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctxLink
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;BLDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctxLink
  (JNIEnv * env, jobject, jint acsHandle, jobject dev1Obj, jobject dev2Obj, jbyte u8Option, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctxLink");

	DeviceID_t dev1, dev2;
	
	memset((void*)&dev1, 0, sizeof(DeviceID_t));
	memset((void*)&dev2, 0, sizeof(DeviceID_t));

	GetData_DeviceID(env, &dev1Obj, &dev1);
	GetData_DeviceID(env, &dev2Obj, &dev2);

	int nRet = XMS_ctxLink(acsHandle, &dev1, &dev2, u8Option, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctxLink");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctxSendAppData
 * Signature: (I[B[BB[BIBBLDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctxSendAppData
  (JNIEnv * env, jobject, jint acsHandle, jbyteArray s8SrcAppRegName, jbyteArray s8DestAppRegName, 
  jbyte u8AppReqType, jbyteArray pData, jint u32DataSize, jbyte u8SrcAppUnitID, jbyte u8DestAppUnitID, 
  jobject deviceObj, jobject Obj)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctxSendAppData");

	DeviceID_t device;

	memset((void*)&device, 0, sizeof(DeviceID_t));

	GetData_DeviceID(env, &deviceObj, &device);

	int nRet = XMS_ctxSendAppData(acsHandle, 
		(DJ_S8*)env->GetByteArrayElements(s8SrcAppRegName, NULL),
		(DJ_S8*)env->GetByteArrayElements(s8DestAppRegName, NULL),
		u8AppReqType, 
		(DJ_S8*)env->GetByteArrayElements(pData, NULL),
		u32DataSize, u8SrcAppUnitID, u8DestAppUnitID, &device, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctxSendAppData");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSendRawFrame
 * Signature: (ILDJKeygoe/DeviceID_t;S[B)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendRawFrame
  (JNIEnv * env, jobject, jint acsHandle, jobject deviceObj, jshort u16FrameSize, jbyteArray pData)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendRawFrame");

	DeviceID_t device;
	
	memset((void*)&device, 0, sizeof(DeviceID_t));
	
	GetData_DeviceID(env, &deviceObj, &device);

	int nRet = XMS_ctsSendRawFrame(acsHandle, &device, u16FrameSize, 
		(DJ_Void*)env->GetByteArrayElements(pData, NULL));

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSendRawFrame");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsJoinTo3GVConf
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;LDJKeygoe/Acs_MediaEx_Input_V;LDJKeygoe/Acs_MediaEx_Output_V;BLDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsJoinTo3GVConf
  (JNIEnv * env, jobject, jint acsHandle, jobject device3GvConfObj, jobject deviceObj, 
   jobject mediaExInputObj, jobject mediaExOutputObj, jbyte u8Visiable, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsJoinTo3GVConf");

	DeviceID_t device, _3GvConfDevice;
	Acs_MediaEx_Input_V  InPutVideo;
	Acs_MediaEx_Output_V OutPutVideo;

	memset((void*)&device, 0, sizeof(DeviceID_t));
	memset((void*)&_3GvConfDevice, 0, sizeof(DeviceID_t));
	memset((void*)&InPutVideo, 0, sizeof(Acs_MediaEx_Input_V));
	memset((void*)&OutPutVideo, 0, sizeof(Acs_MediaEx_Output_V));

	GetData_DeviceID(env, &deviceObj, &device);
	GetData_DeviceID(env, &device3GvConfObj, &_3GvConfDevice);

	GetData_OutPutV(env, &mediaExOutputObj, &OutPutVideo);
	GetData_InPutV(env, &mediaExInputObj, &InPutVideo);

	int nRet = XMS_ctsJoinTo3GVConf(acsHandle, &_3GvConfDevice, &device, &InPutVideo, &OutPutVideo, u8Visiable, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsJoinTo3GVConf");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsLeaveFrom3GVConf
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsLeaveFrom3GVConf
  (JNIEnv * env, jobject, jint acsHandle, jobject device3GvConfObj, jobject deviceObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsLeaveFrom3GVConf");

	DeviceID_t device, _3GvConfDevice;

	memset((void*)&device, 0, sizeof(DeviceID_t));
	memset((void*)&_3GvConfDevice, 0, sizeof(DeviceID_t));

	GetData_DeviceID(env, &deviceObj, &device);
	GetData_DeviceID(env, &device3GvConfObj, &_3GvConfDevice);

	int nRet = XMS_ctsLeaveFrom3GVConf(acsHandle, &_3GvConfDevice, &device, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsLeaveFrom3GVConf");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsClear3GVConf
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsClear3GVConf
  (JNIEnv * env, jobject, jint acsHandle, jobject device3GvConfObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsClear3GVConf");

	DeviceID_t _3GvConfDevice;

	memset((void*)&_3GvConfDevice, 0, sizeof(DeviceID_t));

	GetData_DeviceID(env, &device3GvConfObj, &_3GvConfDevice);

	int nRet = XMS_ctsClear3GVConf(acsHandle, &_3GvConfDevice, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsClear3GVConf");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsGetLayout
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetLayout
  (JNIEnv * env, jobject, jint acsHandle, jobject device3GvConfObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetLayout");

	DeviceID_t _3GvConfDevice;
	
	memset((void*)&_3GvConfDevice, 0, sizeof(DeviceID_t));

	GetData_DeviceID(env, &device3GvConfObj, &_3GvConfDevice);

	int nRet = XMS_ctsGetLayout(acsHandle, &_3GvConfDevice, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetLayout");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSetLayout
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/Acs_3GVConf_LayoutList;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetLayout
  (JNIEnv * env, jobject, jint acsHandle, jobject device3GvConfObj, jobject layOutObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetLayout");

	DeviceID_t _3GvConfDevice;
	Acs_3GVConf_LayoutList layOutList;
	
	memset((void*)&_3GvConfDevice, 0, sizeof(DeviceID_t));
	memset((void*)&layOutList, 0, sizeof(Acs_3GVConf_LayoutList));
	
	GetData_DeviceID(env, &device3GvConfObj, &_3GvConfDevice);
	GetData_LayOutList(env, &layOutObj, &layOutList);

	int nRet = XMS_ctsSetLayout(acsHandle, &_3GvConfDevice, &layOutList, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetLayout");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsGetVisibleList
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetVisibleList
  (JNIEnv * env, jobject, jint acsHandle, jobject device3GvConfObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetVisibleList");

	DeviceID_t _3GvConfDevice;

	memset((void*)&_3GvConfDevice, 0, sizeof(DeviceID_t));

	GetData_DeviceID(env, &device3GvConfObj, &_3GvConfDevice);

	int nRet = XMS_ctsGetVisibleList(acsHandle, &_3GvConfDevice, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsGetVisibleList");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsSetVisibleList
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/Acs_3GVConf_VisibleList;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetVisibleList
  (JNIEnv * env, jobject, jint acsHandle, jobject device3GvConfObj, jobject visableListObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetVisibleList");

	DeviceID_t _3GvConfDevice;
	Acs_3GVConf_VisibleList VisibleList;
	
	memset((void*)&_3GvConfDevice, 0, sizeof(DeviceID_t));
	memset((void*)&VisibleList, 0, sizeof(Acs_3GVConf_VisibleList));
	
	GetData_DeviceID(env, &device3GvConfObj, &_3GvConfDevice);
	GetData_VisibleList(env, &visableListObj, &VisibleList);
	
	int nRet = XMS_ctsSetVisibleList(acsHandle, &_3GvConfDevice, &VisibleList, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsSetVisibleList");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsPutTextInPicture
 * Signature: (I[BLDJKeygoe/PutTextInPicture_Param;ILDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsPutTextInPicture
  (JNIEnv * env, jobject, jint acsHandle, jbyteArray u8DestFile, jobject paramItemObj, jint u32ParamSum, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsPutTextInPicture");

	PutTextInPicture_Param paramItem;

	memset((void*)&paramItem, 0, sizeof(PutTextInPicture_Param));

	GetData_ParamItem(env, &paramItemObj, &paramItem);

	int nRet = XMS_ctsPutTextInPicture(acsHandle, (char *)env->GetByteArrayElements(u8DestFile, NULL),
		&paramItem, u32ParamSum, NULL);
	
	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsPutTextInPicture");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_ctsRestart3GVConf
 * Signature: (ILDJKeygoe/DeviceID_t;LDJKeygoe/PrivateData_t;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsRestart3GVConf
  (JNIEnv * env, jobject, jint acsHandle, jobject device3GvConfObj, jobject)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsRestart3GVConf");
	
	DeviceID_t _3GvConfDevice;
	
	memset((void*)&_3GvConfDevice, 0, sizeof(DeviceID_t));
	
	GetData_DeviceID(env, &device3GvConfObj, &_3GvConfDevice);
		
	int nRet = XMS_ctsRestart3GVConf(acsHandle, &_3GvConfDevice, NULL);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1ctsRestart3GVConf");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsGetRelateMod
 * Signature: (IBB)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsGetRelateMod
  (JNIEnv * env, jobject, jint acsHandle, jbyte u8ModType, jbyte u8UnitID)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1acsGetRelateMod");

	int nRet = XMS_acsGetRelateMod(acsHandle, u8ModType, u8UnitID);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1acsGetRelateMod");

	return nRet;
}

/*
 * Class:     DJKeygoe_DJAcsAPIDef
 * Method:    XMS_acsLedCtrl
 * Signature: (IBLDJKeygoe/UserLedCtrl;)I
 */
JNIEXPORT jint JNICALL Java_DJKeygoe_DJAcsAPIDef_XMS_1acsLedCtrl
  (JNIEnv * env, jobject, jint acsHandle, jbyte u8DspUnitID, jobject LedCtrlObj)
{
	LogInfo("Entry Java_DJKeygoe_DJAcsAPIDef_XMS_1acsLedCtrl");

	UserLedCtrl userLedCtrl;

	memset((void*)&userLedCtrl, 0, sizeof(UserLedCtrl));

	GetData_UserLedCtrl(env, &LedCtrlObj, &userLedCtrl);

	LogInfo("Exit Java_DJKeygoe_DJAcsAPIDef_XMS_1acsLedCtrl");

	return 0;
}




void SetByteArrayData(jbyteArray* pByteArr, byte* SourData, int nLen) //写数组
{
	LogInfo("Entry SetByteArrayData");

	jbyte* u8Data = g_cbData.m_pEnv->GetByteArrayElements(*pByteArr, NULL);
	for (int i = 0; i < nLen; i++)
	{
		u8Data[i] = SourData[i];
	}
	g_cbData.m_pEnv->ReleaseByteArrayElements(*pByteArr, u8Data, 0); //把更改反射到Java数组中

	LogInfo("Exit SetByteArrayData");
}

void GetByteArrayData(JNIEnv* env, byte* pDestArr, jbyteArray* pByteArr, int nLen)
{
	LogInfo("Entry GetByteArrayData");

	jbyte* u8Data = env->GetByteArrayElements(*pByteArr, NULL);
	for (int i = 0; i < nLen; i++)
	{
		pDestArr[i] = u8Data[i];
	}

	LogInfo("Exit GetByteArrayData");
}

void GetData_MixerControlParam(JNIEnv* env, jobject* MixerControlObj, MixerControlParam_t* MixerControl)
{
	LogInfo("Entry GetData_MixerControlParam");
	
	jclass OutputControlCla = env->GetObjectClass(*MixerControlObj);
	LogInfo("OutputControlCla");
	
	jfieldID fieldSRC1_Ctrl = env->GetFieldID(OutputControlCla, "m_u8SRC1_Ctrl", "B");
	MixerControl->m_u8SRC1_Ctrl = env->GetByteField(*MixerControlObj, fieldSRC1_Ctrl);
	
	jfieldID fieldSRC2_Ctrl = env->GetFieldID(OutputControlCla, "m_u8SRC2_Ctrl", "B");
	MixerControl->m_u8SRC2_Ctrl = env->GetByteField(*MixerControlObj, fieldSRC2_Ctrl);
	
	jfieldID fieldSRC_ChID1 = env->GetFieldID(OutputControlCla, "m_u16SRC_ChID1", "S");
	MixerControl->m_u16SRC_ChID1 = env->GetShortField(*MixerControlObj, fieldSRC_ChID1);
	
	jfieldID fieldSRC_ChID2 = env->GetFieldID(OutputControlCla, "m_u16SRC_ChID2", "S");
	MixerControl->m_u16SRC_ChID2 = env->GetShortField(*MixerControlObj, fieldSRC_ChID2);
	
	jfieldID fieldVideo = env->GetFieldID(OutputControlCla, "m_u8Video", "B");
	MixerControl->m_u8Video = env->GetByteField(*MixerControlObj, fieldVideo);
	
	jfieldID fieldRfu = env->GetFieldID(OutputControlCla, "m_s8Rfu", "B");
	MixerControl->m_s8Rfu = env->GetByteField(*MixerControlObj, fieldRfu);
	
	LogInfo("Exit GetData_MixerControlParam");	
}

void GetObjectArrayData_CalledTable(JNIEnv* env, CAS_CalledTableDesc_t* m_CalledTable, jobjectArray* ObjArr_CalledTable, int nNumOfObjArr)
{
	LogInfo("Entry GetObjectArrayData_CalledTable");

	jobject objCalledTable = NULL;
	jclass  claCalledTable = NULL;
	jfieldID NumHeadLenFieldID = NULL, NumHeadFieldID = NULL, NumLenFieldID = NULL;
	jbyteArray NumHead = NULL;

	for (int i = 0; i < nNumOfObjArr; i++)
	{
		objCalledTable = env->GetObjectArrayElement(*ObjArr_CalledTable, i);
		claCalledTable = env->GetObjectClass(objCalledTable);

		NumHeadLenFieldID = env->GetFieldID(claCalledTable, "m_u8NumHeadLen", "B");
		m_CalledTable[i].m_u8NumHeadLen = env->GetByteField(objCalledTable, NumHeadLenFieldID);

		NumHeadFieldID = env->GetFieldID(claCalledTable, "m_u8NumHead", "[B");
		NumHead = (jbyteArray)(env->GetObjectField(objCalledTable, NumHeadFieldID));
		GetByteArrayData(env, &(m_CalledTable[i].m_u8NumHead[0]), &NumHead, 14);

		NumLenFieldID = env->GetFieldID(claCalledTable, "m_u8NumLen", "B");
		m_CalledTable[i].m_u8NumLen = env->GetByteField(objCalledTable, NumLenFieldID);
	}

	LogInfo("Exit GetObjectArrayData_CalledTable");
}

//把DSP返回的device返回给Java端
void SetData_DeviceID(DeviceID_t* pDev, jobject* DeviceObj) //设置DeviceID_t对象
{
	LogInfo("Entry SetData_DeviceID");

	jclass DeviceCla = g_cbData.m_pEnv->GetObjectClass(*DeviceObj);

	jfieldID DevMainFieldID = g_cbData.m_pEnv->GetFieldID(DeviceCla, "m_s16DeviceMain", "S");
	g_cbData.m_pEnv->SetShortField(*DeviceObj, DevMainFieldID, pDev->m_s16DeviceMain);

	jfieldID DevSubFieldID = g_cbData.m_pEnv->GetFieldID(DeviceCla, "m_s16DeviceSub", "S");
	g_cbData.m_pEnv->SetShortField(*DeviceObj, DevSubFieldID, pDev->m_s16DeviceSub);

	jfieldID DevMoudeIDFieldID  = g_cbData.m_pEnv->GetFieldID(DeviceCla, "m_s8ModuleID", "B");
	g_cbData.m_pEnv->SetByteField(*DeviceObj, DevMoudeIDFieldID, pDev->m_s8ModuleID);

	jfieldID DevMachineIDFieldID  = g_cbData.m_pEnv->GetFieldID(DeviceCla, "m_s8MachineID", "B");
	g_cbData.m_pEnv->SetByteField(*DeviceObj, DevMachineIDFieldID, pDev->m_s8MachineID);

	jfieldID DevChannIDFieldID = g_cbData.m_pEnv->GetFieldID(DeviceCla, "m_s16ChannelID", "S");
	g_cbData.m_pEnv->SetShortField(*DeviceObj, DevChannIDFieldID, pDev->m_s16ChannelID);
	
	jfieldID DevGroupFieldID = g_cbData.m_pEnv->GetFieldID(DeviceCla, "m_s16DeviceGroup", "S");
	g_cbData.m_pEnv->SetShortField(*DeviceObj, DevGroupFieldID, pDev->m_s16DeviceGroup);

	jfieldID DevRfuFieldID = g_cbData.m_pEnv->GetFieldID(DeviceCla, "m_Rfu2", "[B");
	jbyteArray m_Rfu2 = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*DeviceObj, DevRfuFieldID));
	SetByteArrayData(&m_Rfu2, (byte *)&(pDev->m_Rfu2), 2);

	jfieldID CallIDFieldID = g_cbData.m_pEnv->GetFieldID(DeviceCla, "m_CallID", "LDJKeygoe/CallID_t;");
	jobject CallIDObj = g_cbData.m_pEnv->GetObjectField(*DeviceObj, CallIDFieldID); //获取DeviceID_t对象，注意第一个参数该对象是所属对象的obj
	jclass CallIDCla = g_cbData.m_pEnv->GetObjectClass(CallIDObj);
	
	jfieldID FlowTypeID = g_cbData.m_pEnv->GetFieldID(CallIDCla, "m_s32FlowType", "I");
	g_cbData.m_pEnv->SetIntField(CallIDObj, FlowTypeID, pDev->m_CallID.m_s32FlowType);

	jfieldID FlowChannID = g_cbData.m_pEnv->GetFieldID(CallIDCla, "m_s32FlowChannel", "I");
	g_cbData.m_pEnv->SetIntField(CallIDObj, FlowChannID, pDev->m_CallID.m_s32FlowChannel);

	LogInfo("Exit SetData_DeviceID");
}

void GetData_RecordProperty(JNIEnv * env, jobject* recordPropertyObj, RecordProperty_t* recordProtery)
{
	LogInfo("Entry GetData_RecordProperty");

	jclass recordPropertyCla = env->GetObjectClass(*recordPropertyObj);
	
	jfieldID MaxSizeFieldID = env->GetFieldID(recordPropertyCla, "m_u32MaxSize", "I");
	recordProtery->m_u32MaxSize = env->GetIntField(*recordPropertyObj, MaxSizeFieldID);

	jfieldID MaxTimeFieldID = env->GetFieldID(recordPropertyCla, "m_u32MaxTime", "I");
	recordProtery->m_u32MaxTime = env->GetIntField(*recordPropertyObj, MaxTimeFieldID);

	jfieldID EncodeTypeFieldID = env->GetFieldID(recordPropertyCla, "m_u8EncodeType", "B");
	recordProtery->m_u8EncodeType = env->GetByteField(*recordPropertyObj, EncodeTypeFieldID);

	jfieldID SRCModeFieldID = env->GetFieldID(recordPropertyCla, "m_u8SRCMode", "B");
	recordProtery->m_u8SRCMode = env->GetByteField(*recordPropertyObj, SRCModeFieldID);

	jfieldID StopModeFieldID = env->GetFieldID(recordPropertyCla, "m_u8StopMode", "B");
	recordProtery->m_u8StopMode = env->GetByteField(*recordPropertyObj, StopModeFieldID);

	jfieldID StopCodeFieldID = env->GetFieldID(recordPropertyCla, "m_u8StopCode", "B");
	recordProtery->m_u8StopCode = env->GetByteField(*recordPropertyObj, StopCodeFieldID);

	jfieldID MixEnableFieldID = env->GetFieldID(recordPropertyCla, "m_s8IsMixEnable", "B");
	recordProtery->m_s8IsMixEnable = env->GetByteField(*recordPropertyObj, MixEnableFieldID);

	jfieldID TaskIDFieldID = env->GetFieldID(recordPropertyCla, "m_u8TaskID", "B");
	recordProtery->m_u8TaskID = env->GetByteField(*recordPropertyObj, TaskIDFieldID);

	jfieldID fieldMixerControl = env->GetFieldID(recordPropertyCla, "m_MixerControl", "LDJKeygoe/MixerControlParam_t;");
	jobject  MixerControlObj = env->GetObjectField(*recordPropertyObj, fieldMixerControl);
	GetData_MixerControlParam(env, &MixerControlObj, &recordProtery->m_MixerControl);

	jfieldID IsAppendFieldID = env->GetFieldID(recordPropertyCla, "m_s8IsAppend", "B");
	recordProtery->m_s8IsAppend = env->GetByteField(*recordPropertyObj, IsAppendFieldID);

	jfieldID FileNameFieldID = env->GetFieldID(recordPropertyCla, "m_s8FileName", "[B");
	jbyteArray playCont = (jbyteArray)(env->GetObjectField(*recordPropertyObj, FileNameFieldID));
	GetByteArrayData(env, (byte *)&recordProtery->m_s8FileName[0], &playCont, 260);

	jfieldID Rfu2FieldID = env->GetFieldID(recordPropertyCla, "m_s8Rfu2", "B");
	recordProtery->m_s8Rfu2[0] = env->GetByteField(*recordPropertyObj, Rfu2FieldID);

	LogInfo("Exit GetData_RecordProperty");
}

void GetData_CtrlRecord(JNIEnv * env, jobject* ctrlRecordObj, ControlRecord_t* ctrlRecord)
{
	LogInfo("Entry GetData_CtrlRecord");

	jclass ctrlRecordCla = env->GetObjectClass(*ctrlRecordObj);

	jfieldID ControlTypeFieldID = env->GetFieldID(ctrlRecordCla, "m_u32ControlType", "I");
	ctrlRecord->m_u32ControlType = env->GetIntField(*ctrlRecordObj, ControlTypeFieldID);

	jfieldID StepSizeFieldID = env->GetFieldID(ctrlRecordCla, "m_u32StepSize", "I");
	ctrlRecord->m_u32StepSize = env->GetIntField(*ctrlRecordObj, StepSizeFieldID);
	
	jfieldID DelayStopFieldID = env->GetFieldID(ctrlRecordCla, "m_u32DelayStop", "I");
	ctrlRecord->m_u32DelayStop = env->GetIntField(*ctrlRecordObj, DelayStopFieldID);

	LogInfo("Exit GetData_CtrlRecord");
}

void GetData_PlayProperty(JNIEnv * env, jobject* playPropertyObj, PlayProperty_t* playProperty)
{
	LogInfo("Entry GetData_PlayProperty");

	jclass playPropertyCla = env->GetObjectClass(*playPropertyObj);

	jfieldID TaskIDFieldID = env->GetFieldID(playPropertyCla, "m_u8TaskID", "B");
	playProperty->m_u8TaskID = env->GetByteField(*playPropertyObj, TaskIDFieldID);

	jfieldID SrcModeFieldID = env->GetFieldID(playPropertyCla, "m_u8SrcMode", "B");
	playProperty->m_u8SrcMode = env->GetByteField(*playPropertyObj, SrcModeFieldID);

	jfieldID DecodeTypeFieldID = env->GetFieldID(playPropertyCla, "m_u8DecodeType", "B");
	playProperty->m_u8DecodeType = env->GetByteField(*playPropertyObj, DecodeTypeFieldID);
	
	jfieldID RfuFieldID = env->GetFieldID(playPropertyCla, "m_s8Rfu1", "B");
	playProperty->m_s8Rfu1[0] = env->GetByteField(*playPropertyObj, RfuFieldID);

	jfieldID MaxSizeFieldID = env->GetFieldID(playPropertyCla, "m_u32MaxSize", "I");
	playProperty->m_u32MaxSize = env->GetIntField(*playPropertyObj, MaxSizeFieldID);

	jfieldID MaxTimeFieldID = env->GetFieldID(playPropertyCla, "m_u32MaxTime", "I");
	playProperty->m_u32MaxTime = env->GetIntField(*playPropertyObj, MaxTimeFieldID);

	jfieldID StopModeFieldID = env->GetFieldID(playPropertyCla, "m_u32StopMode", "I");
	playProperty->m_u32StopMode = env->GetIntField(*playPropertyObj, StopModeFieldID);

	jfieldID StopCodeFieldID = env->GetFieldID(playPropertyCla, "m_u32StopCode", "I");
	playProperty->m_u32StopCode = env->GetIntField(*playPropertyObj, StopCodeFieldID);

	jfieldID FileOffsetFieldID = env->GetFieldID(playPropertyCla, "m_u16FileOffset", "S");
	playProperty->m_u16FileOffset = env->GetShortField(*playPropertyObj, FileOffsetFieldID);

	jfieldID PlayTypeFieldID = env->GetFieldID(playPropertyCla, "m_u16PlayType", "S");
	playProperty->m_u16PlayType = env->GetShortField(*playPropertyObj, PlayTypeFieldID);

	jfieldID PlayIndexFieldID = env->GetFieldID(playPropertyCla, "m_u16PlayIndex", "S");
	playProperty->m_u16PlayIndex = env->GetShortField(*playPropertyObj, PlayIndexFieldID);

	jfieldID PlayContentFieldID = env->GetFieldID(playPropertyCla, "m_s8PlayContent", "[B");
	jbyteArray playCont = (jbyteArray)(env->GetObjectField(*playPropertyObj, PlayContentFieldID));
	GetByteArrayData(env, (byte *)&playProperty->m_s8PlayContent[0], &playCont, 128);

	jfieldID FileSubOffsetFieldID = env->GetFieldID(playPropertyCla, "m_u16FileSubOffset", "S");
	playProperty->m_u16FileSubOffset = env->GetShortField(*playPropertyObj, FileSubOffsetFieldID);

	LogInfo("Exit GetData_PlayProperty");
}

//把Java传过来的Device,取出成员赋给JNI端的DeviceID_t对象
void GetData_DeviceID(JNIEnv * env, jobject* DeviceObj, DeviceID_t* pDev)
{
	LogInfo("Entry GetDeviceIData");

	jclass DeviceCla = env->GetObjectClass(*DeviceObj);

	jfieldID DevMainFieldID = env->GetFieldID(DeviceCla, "m_s16DeviceMain", "S");
	pDev->m_s16DeviceMain = env->GetShortField(*DeviceObj, DevMainFieldID);

	jfieldID DevSubFieldID = env->GetFieldID(DeviceCla, "m_s16DeviceSub", "S");
	pDev->m_s16DeviceSub = env->GetShortField(*DeviceObj, DevSubFieldID);

	jfieldID DevMoudeIDFieldID  = env->GetFieldID(DeviceCla, "m_s8ModuleID", "B");
	pDev->m_s8ModuleID = env->GetByteField(*DeviceObj, DevMoudeIDFieldID);

	jfieldID DevMachineIDFieldID  = env->GetFieldID(DeviceCla, "m_s8MachineID", "B");
	pDev->m_s8MachineID = env->GetByteField(*DeviceObj, DevMachineIDFieldID);

	jfieldID DevChannIDFieldID = env->GetFieldID(DeviceCla, "m_s16ChannelID", "S");
	pDev->m_s16ChannelID = env->GetShortField(*DeviceObj, DevChannIDFieldID);

	jfieldID DevGroupFieldID = env->GetFieldID(DeviceCla, "m_s16DeviceGroup", "S");
	pDev->m_s16DeviceGroup = env->GetShortField(*DeviceObj, DevGroupFieldID);

	jfieldID DevRfuFieldID = env->GetFieldID(DeviceCla, "m_Rfu2", "[B");
	jbyteArray m_Rfu2 = (jbyteArray)(env->GetObjectField(*DeviceObj, DevRfuFieldID));
	jbyte* Refu = env->GetByteArrayElements(m_Rfu2, NULL);
	pDev->m_Rfu2[0] = Refu[0];
	pDev->m_Rfu2[1] = Refu[1];

	jfieldID CallIDFieldID = env->GetFieldID(DeviceCla, "m_CallID", "LDJKeygoe/CallID_t;");
	jobject CallIDObj = env->GetObjectField(*DeviceObj, CallIDFieldID); //获取DeviceID_t对象，注意第一个参数该对象是所属对象的obj
	jclass CallIDCla = env->GetObjectClass(CallIDObj);
	
	jfieldID FlowTypeID = env->GetFieldID(CallIDCla, "m_s32FlowType", "I");
	pDev->m_CallID.m_s32FlowType = env->GetIntField(CallIDObj, FlowTypeID);

	jfieldID FlowChannID = env->GetFieldID(CallIDCla, "m_s32FlowChannel", "I");
	pDev->m_CallID.m_s32FlowChannel = env->GetIntField(CallIDObj, FlowChannID);

	LogInfo("Exit GetDeviceIData");
}

void GetData_ControlPlay(JNIEnv * env, jobject* ControlObj, ControlPlay_t* ControlPlayData)
{
	LogInfo("Entry GetData_ControlPlay");

	jclass ControlCla = env->GetObjectClass(*ControlObj);

	jfieldID ControlTypeFieldID = env->GetFieldID(ControlCla, "m_u16ControlType", "S");
	ControlPlayData->m_u16ControlType = env->GetShortField(*ControlObj, ControlTypeFieldID);

	jfieldID StepSizeFieldID = env->GetFieldID(ControlCla, "m_u16StepSize", "S");
	ControlPlayData->m_u16StepSize = env->GetShortField(*ControlObj, StepSizeFieldID);

	jfieldID TuneTypeFieldID = env->GetFieldID(ControlCla, "m_u16TuneType", "S");
	ControlPlayData->m_u16TuneType = env->GetShortField(*ControlObj, TuneTypeFieldID);

	jfieldID SpeedSizeFieldID = env->GetFieldID(ControlCla, "m_u16SpeedSize", "S");
	ControlPlayData->m_u16SpeedSize = env->GetShortField(*ControlObj, SpeedSizeFieldID);

	LogInfo("Exit GetData_ControlPlay");
}

void GetData_GtdControl(JNIEnv* env, jobject* objfieldVocGtdCtrl, VocGtdControlParam_t* VocGtdControl)
{
	LogInfo("Entry GetData_GtdControl");

	jclass VocGtdControlCla = env->GetObjectClass(*objfieldVocGtdCtrl);

	jfieldID fieldAgcEnable = env->GetFieldID(VocGtdControlCla, "m_u8ChannelEnable", "B");
	VocGtdControl->m_u8ChannelEnable = env->GetByteField(*objfieldVocGtdCtrl, fieldAgcEnable);

	jfieldID fieldDTMFEnable = env->GetFieldID(VocGtdControlCla, "m_u8DTMFEnable", "B");
	VocGtdControl->m_u8DTMFEnable = env->GetByteField(*objfieldVocGtdCtrl, fieldDTMFEnable);

	jfieldID fieldMR2FEnable = env->GetFieldID(VocGtdControlCla, "m_u8MR2FEnable", "B");
	VocGtdControl->m_u8MR2FEnable = env->GetByteField(*objfieldVocGtdCtrl, fieldMR2FEnable);

	jfieldID fieldMR2BEnable = env->GetFieldID(VocGtdControlCla, "m_u8MR2BEnable", "B");
	VocGtdControl->m_u8MR2BEnable = env->GetByteField(*objfieldVocGtdCtrl, fieldMR2BEnable);
	
	jfieldID fieldGTDEnable = env->GetFieldID(VocGtdControlCla, "m_u8GTDEnable", "B");
	VocGtdControl->m_u8GTDEnable = env->GetByteField(*objfieldVocGtdCtrl, fieldGTDEnable);
	
	jfieldID fieldFSKEnable = env->GetFieldID(VocGtdControlCla, "m_u8FSKEnable", "B");
	VocGtdControl->m_u8FSKEnable = env->GetByteField(*objfieldVocGtdCtrl, fieldFSKEnable);

	jfieldID fieldEXTEnable = env->GetFieldID(VocGtdControlCla, "m_u8EXTEnable", "B");
	VocGtdControl->m_u8EXTEnable = env->GetByteField(*objfieldVocGtdCtrl, fieldEXTEnable);
	
	jfieldID fieldReserved = env->GetFieldID(VocGtdControlCla, "m_u8Reserved", "B");
	VocGtdControl->m_u8Reserved = env->GetByteField(*objfieldVocGtdCtrl, fieldReserved);

	jfieldID fieldGTDID = env->GetFieldID(VocGtdControlCla, "m_u8GTDID", "[B");
	jbyteArray GTDID = (jbyteArray)(env->GetObjectField(*objfieldVocGtdCtrl, fieldGTDID));
	GetByteArrayData(env, &VocGtdControl->m_u8GTDID[0], &GTDID, 8);

	LogInfo("Exit GetData_GtdControl");
}

void GetData_CmdConf(JNIEnv* env, jobject* obj, CmdParamData_Conf_t* ConfData)
{
	LogInfo("Entry GetData_CmdConf");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fieldInputOpt = env->GetFieldID(cla, "m_u8InputOpt", "B");
	ConfData->m_u8InputOpt = env->GetByteField(*obj, fieldInputOpt);

	jfieldID fieldOutputOpt = env->GetFieldID(cla, "m_u8OutputOpt", "B");
	ConfData->m_u8OutputOpt = env->GetByteField(*obj, fieldOutputOpt);

	jfieldID fieldRfu1 = env->GetFieldID(cla, "m_u8Rfu1", "B");
	ConfData->m_u8Rfu[0] = env->GetByteField(*obj, fieldRfu1);

	jfieldID fieldRfu2 = env->GetFieldID(cla, "m_u8Rfu2", "B");
	ConfData->m_u8Rfu[1] = env->GetByteField(*obj, fieldRfu2);

	LogInfo("Exit GetData_CmdConf");
}

void GetData_Private(JNIEnv* env, jobject* obj, PrivateData_t* PrivateData)
{
	LogInfo("Entry GetData_Private");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fieldDataSize = env->GetFieldID(cla, "m_u32DataSize", "I");
	PrivateData->m_u32DataSize = env->GetIntField(*obj, fieldDataSize);

	LogInfo("Exit GetData_Private");
}

void GetData_FaxPrivate(JNIEnv * env, jobject* obj, FaxPrivate_t* faxPrivate)
{
	LogInfo("Entry GetData_FaxPrivate");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fieldPrivate = env->GetFieldID(cla, "m_PrivateData", "LDJKeygoe/PrivateData_t;");
	jobject  objPrivate = env->GetObjectField(*obj, fieldPrivate);
	GetData_Private(env, &objPrivate, &faxPrivate->m_PrivateData);

	jfieldID fieldDevice = env->GetFieldID(cla, "m_VoIPDevice", "LDJKeygoe/DeviceID_t;");
	jobject  objDevice = env->GetObjectField(*obj, fieldDevice);
	GetData_DeviceID(env, &objDevice, &faxPrivate->m_VoIPDevice);

	jfieldID fieldWorkMode = env->GetFieldID(cla, "m_u8WorkMode", "B");
	faxPrivate->m_u8WorkMode = env->GetByteField(*obj, fieldWorkMode);

	jfieldID FieldRfu = env->GetFieldID(cla, "m_s8Rfu1", "[B");
	jbyteArray rfu = (jbyteArray)(env->GetObjectField(*obj, FieldRfu));
	GetByteArrayData(env, (byte *)&faxPrivate->m_s8Rfu1[0], &rfu, 3);

	LogInfo("Exit GetData_FaxPrivate");
}

void GetData_VocOutputControl(JNIEnv * env, jobject* objVocOutputControl, VocOutputControlParam_t* VocOutputControl)
{
	LogInfo("Entry GetData_VocOutputControl");

	jclass OutputControlCla = env->GetObjectClass(*objVocOutputControl);

	jfieldID fieldAgcEnable = env->GetFieldID(OutputControlCla, "m_u8AgcEnable", "B");
	VocOutputControl->m_u8AgcEnable = env->GetByteField(*objVocOutputControl, fieldAgcEnable);

	jfieldID fieldAgcMode = env->GetFieldID(OutputControlCla, "m_u8AgcMode", "B");
	VocOutputControl->m_u8AgcMode = env->GetByteField(*objVocOutputControl, fieldAgcMode);

	jfieldID fieldOutputType = env->GetFieldID(OutputControlCla, "m_u8OutputType", "B");
	VocOutputControl->m_u8OutputType = env->GetByteField(*objVocOutputControl, fieldOutputType);


	jfieldID fieldReserved = env->GetFieldID(OutputControlCla, "m_u8Reserved", "B");
	VocOutputControl->m_u8Reserved[0] = env->GetByteField(*objVocOutputControl, fieldReserved);

	jfieldID fieldFixGain = env->GetFieldID(OutputControlCla, "m_u16FixGain", "S");
	VocOutputControl->m_u16FixGain = env->GetShortField(*objVocOutputControl, fieldFixGain);

	jfieldID fieldRfu = env->GetFieldID(OutputControlCla, "m_s8Rfu", "[B");
	jbyteArray m_Rfu2 = (jbyteArray)(env->GetObjectField(*objVocOutputControl, fieldRfu));
	GetByteArrayData(env, (byte *)&VocOutputControl->m_s8Rfu[0], &m_Rfu2, 2);

	jfieldID fieldMixerControl = env->GetFieldID(OutputControlCla, "m_MixerControl", "LDJKeygoe/MixerControlParam_t;");
	jobject  MixerControlObj = env->GetObjectField(*objVocOutputControl, fieldMixerControl);
	GetData_MixerControlParam(env, &MixerControlObj, &VocOutputControl->m_MixerControl);

	LogInfo("Exit GetData_VocOutputControl");
}

void GetData_VocInputControl(JNIEnv * env, jobject* objVocInputControl, VocInputControlParam_t* VocInputControl)
{
	LogInfo("Entry GetData_VocInputControl");

	jclass InputControlCla = env->GetObjectClass(*objVocInputControl);

	jfieldID fieldAgcEnable = env->GetFieldID(InputControlCla, "m_u8AgcEnable", "B");
	VocInputControl->m_u8AgcEnable = env->GetByteField(*objVocInputControl, fieldAgcEnable);

	jfieldID fieldAgcMode = env->GetFieldID(InputControlCla, "m_u8AgcMode", "B");
	VocInputControl->m_u8AgcMode = env->GetByteField(*objVocInputControl, fieldAgcMode);

	jfieldID fieldEcEnable = env->GetFieldID(InputControlCla, "m_u8EcEnable", "B");
	VocInputControl->m_u8EcEnable = env->GetByteField(*objVocInputControl, fieldEcEnable);

	jfieldID fieldEcRefType = env->GetFieldID(InputControlCla, "m_u8EcRefType", "B");
	VocInputControl->m_u8EcRefType = env->GetByteField(*objVocInputControl, fieldEcRefType);

	jfieldID fieldVadEnable = env->GetFieldID(InputControlCla, "m_u8VadEnable", "B");
	VocInputControl->m_u8VadEnable = env->GetByteField(*objVocInputControl, fieldVadEnable);

	jfieldID fieldTadEnable = env->GetFieldID(InputControlCla, "m_u8TadEnable", "B");
	VocInputControl->m_u8TadEnable = env->GetByteField(*objVocInputControl, fieldTadEnable);

	jfieldID fieldNrEnable = env->GetFieldID(InputControlCla, "m_u8NrEnable", "B");
	VocInputControl->m_u8NrEnable = env->GetByteField(*objVocInputControl, fieldNrEnable);

	jfieldID fieldReserved = env->GetFieldID(InputControlCla, "m_u8Reserved", "B");
	VocInputControl->m_u8Reserved = env->GetByteField(*objVocInputControl, fieldReserved);

	jfieldID fieldFixGain = env->GetFieldID(InputControlCla, "m_u16FixGain", "S");
	VocInputControl->m_u16FixGain = env->GetShortField(*objVocInputControl, fieldFixGain);

	jfieldID fieldEcRefCh = env->GetFieldID(InputControlCla, "m_u16EcRefCh", "S");
	VocInputControl->m_u16EcRefCh = env->GetShortField(*objVocInputControl, fieldEcRefCh);

	jfieldID fieldReserved1 = env->GetFieldID(InputControlCla, "m_u32Reserved", "I");
	VocInputControl->m_u32Reserved = env->GetIntField(*objVocInputControl, fieldReserved1);

	LogInfo("Exit GetData_VocInputControl");

}


void SetData_Evt(Acs_Evt_t* pEvt, jobject* obj) //为Java中Acs_Evt_t对象赋值
{
	LogInfo("Entry SetData_Evt");

	jclass clsObj = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fieldIdAcsHand = g_cbData.m_pEnv->GetFieldID(clsObj, "m_s32AcsHandle", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldIdAcsHand, pEvt->m_s32AcsHandle); //更改一个整形变量

	jfieldID fieldIDevice = g_cbData.m_pEnv->GetFieldID(clsObj, "m_DeviceID", "LDJKeygoe/DeviceID_t;");
	jobject DeviceObj = g_cbData.m_pEnv->GetObjectField(*obj, fieldIDevice); //获取DeviceID_t对象，注意第一个参数该对象是所属对象的obj
	
	SetData_DeviceID(&pEvt->m_DeviceID, &DeviceObj);

	jfieldID fieldIdEvtSize = g_cbData.m_pEnv->GetFieldID(clsObj, "m_s32EvtSize", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldIdEvtSize, pEvt->m_s32EvtSize); 

	jfieldID fieldIdEvtType = g_cbData.m_pEnv->GetFieldID(clsObj, "m_s32EventType", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldIdEvtType, pEvt->m_s32EventType); 

	jfieldID fieldIdEsrParam = g_cbData.m_pEnv->GetFieldID(clsObj, "m_u32EsrParam", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldIdEsrParam, pEvt->m_u32EsrParam); 

	LogInfo("Exit SetData_Evt");
}

void SetData_Conf(CmdParamConf_MemberState_t* pConf, jobject* obj)
{
	LogInfo("Entry SetData_Conf");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fdNormalVad = g_cbData.m_pEnv->GetFieldID(cls, "m_s8NormalVad", "[B");
	jbyteArray szNormalVad = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdNormalVad));
	SetByteArrayData(&szNormalVad, (byte*)pConf->m_s8NormalVad, 16);

	jfieldID fdIPVad = g_cbData.m_pEnv->GetFieldID(cls, "m_s8IPVad", "[B");
	jbyteArray szIPVad = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdIPVad));
	SetByteArrayData(&szIPVad, (byte*)pConf->m_s8IPVad, 16);

	jfieldID fdTotalOfConfMem = g_cbData.m_pEnv->GetFieldID(cls, "m_u8TotalOfConfMem", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fdTotalOfConfMem, pConf->m_u8TotalOfConfMem); 

	jfieldID fdRef = g_cbData.m_pEnv->GetFieldID(cls, "m_u8Ref", "[B");
	jbyteArray szRef = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdRef));
	SetByteArrayData(&szRef, (byte*)pConf->m_u8Ref, 3);

	LogInfo("Exit SetData_Conf");
}

void SetData_GeneralProc(Acs_GeneralProc_Data* pGeneralData, jobject* obj)
{
	LogInfo("Entry SetData_GeneralProc");
	
	jclass clsObj = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(clsObj, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pGeneralData->m_s32AcsEvtState);

	jfieldID fieldEvtErrCode = g_cbData.m_pEnv->GetFieldID(clsObj, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtErrCode, pGeneralData->m_s32AcsEvtErrCode);

	jfieldID fieldDeviceState = g_cbData.m_pEnv->GetFieldID(clsObj, "m_s32DeviceState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldDeviceState, pGeneralData->m_s32DeviceState);

	jfieldID fieldResrv = g_cbData.m_pEnv->GetFieldID(clsObj, "m_s32Resrv", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldResrv, pGeneralData->m_s32Resrv);

	LogInfo("Exit SetData_GeneralProc");
}

void SetData_ParamProc  (Acs_ParamProc_Data * pParamData, jobject* obj)
{
	LogInfo("Entry SetData_ParamProc");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj); 

	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pParamData->m_s32AcsEvtState);
	
	jfieldID fieldEvtErrCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtErrCode, pParamData->m_s32AcsEvtErrCode);

	jfieldID fieldParamCmdType = g_cbData.m_pEnv->GetFieldID(cls, "m_u16ParamCmdType", "S");
	g_cbData.m_pEnv->SetShortField(*obj, fieldParamCmdType, pParamData->m_u16ParamCmdType);

	jfieldID fieldParamDataSize = g_cbData.m_pEnv->GetFieldID(cls, "m_u16ParamDataSize", "S");
	g_cbData.m_pEnv->SetShortField(*obj, fieldParamDataSize, pParamData->m_u16ParamDataSize);

	LogInfo("Exit SetData_ParamProc");
}

void SetData_ChCodecAudio(Acs_VoIP_RTPCODEC* pRtpCodex, jobject* obj)
{
	LogInfo("Entry SetData_ChCodecAudio");
	
	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fdEnable = g_cbData.m_pEnv->GetFieldID(cls, "m_u8Enable", "B");
	g_cbData.m_pEnv->SetIntField(*obj, fdEnable, pRtpCodex->audio.m_u8Enable);
	
	jfieldID fdTxCodec = g_cbData.m_pEnv->GetFieldID(cls, "m_u8TxCodec", "B");
	g_cbData.m_pEnv->SetIntField(*obj, fdTxCodec, pRtpCodex->audio.m_u8TxCodec);
	
	jfieldID fdTxPayloadType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8TxPayloadType", "B");
	g_cbData.m_pEnv->SetIntField(*obj, fdTxPayloadType, pRtpCodex->audio.m_u8TxPayloadType);
	
	jfieldID fdRxCodec = g_cbData.m_pEnv->GetFieldID(cls, "m_u8RxCodec", "B");
	g_cbData.m_pEnv->SetIntField(*obj, fdRxCodec, pRtpCodex->audio.m_u8RxCodec);
	
	jfieldID fdRxPayloadType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8RxPayloadType", "B");
	g_cbData.m_pEnv->SetIntField(*obj, fdRxPayloadType, pRtpCodex->audio.m_u8RxPayloadType);
	
	LogInfo("Exit SetData_ChCodecAudio");
}

void SetData_ChCodecVideo(Acs_VoIP_RTPCODEC* pRtpCodex, jobject* obj)
{
	LogInfo("Entry SetData_ChCodecVideo");
	
	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fdEnable = g_cbData.m_pEnv->GetFieldID(cls, "m_u8Enable", "B");
	g_cbData.m_pEnv->SetIntField(*obj, fdEnable, pRtpCodex->video.m_u8Enable);
	
	jfieldID fdTxCodec = g_cbData.m_pEnv->GetFieldID(cls, "m_u8TxCodec", "B");
	g_cbData.m_pEnv->SetIntField(*obj, fdTxCodec, pRtpCodex->video.m_u8TxCodec);
	
	jfieldID fdTxPayloadType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8TxPayloadType", "B");
	g_cbData.m_pEnv->SetIntField(*obj, fdTxPayloadType, pRtpCodex->video.m_u8TxPayloadType);
	
	jfieldID fdRxCodec = g_cbData.m_pEnv->GetFieldID(cls, "m_u8RxCodec", "B");
	g_cbData.m_pEnv->SetIntField(*obj, fdRxCodec, pRtpCodex->video.m_u8RxCodec);
	
	jfieldID fdRxPayloadType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8RxPayloadType", "B");
	g_cbData.m_pEnv->SetIntField(*obj, fdRxPayloadType, pRtpCodex->video.m_u8RxPayloadType);
	
	LogInfo("Exit SetData_ChCodecVideo");
}

void SetData_VoipCodec	(Acs_VoIP_RTPCODEC* pRtpCodex,	jobject* obj)
{
	LogInfo("Entry SetData_VoipCodec");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fieldAudio = g_cbData.m_pEnv->GetFieldID(cls, "audio", "LDJKeygoe/ChCodec;");
	jobject objAudio = g_cbData.m_pEnv->GetObjectField(*obj, fieldAudio); 
	SetData_ChCodecAudio(pRtpCodex, &objAudio);

	jfieldID fieldVideo = g_cbData.m_pEnv->GetFieldID(cls, "video", "LDJKeygoe/ChCodec;");
	jobject objVideo = g_cbData.m_pEnv->GetObjectField(*obj, fieldVideo);
	SetData_ChCodecVideo(pRtpCodex, &objVideo);

	LogInfo("Exit SetData_VoipCodec");
}

void SetData_LicenseQuery(Acs_LicenseQuery_Data* pLicenseQuery, jobject* obj)
{
	LogInfo("Entry SetData_LicenseQuery");
	
	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fieldModuleID = g_cbData.m_pEnv->GetFieldID(cls, "m_u8ModuleID", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldModuleID, pLicenseQuery->m_u8ModuleID);

	jfieldID fieldLicLeftDay = g_cbData.m_pEnv->GetFieldID(cls, "m_u16LicLeftDay", "S");
	g_cbData.m_pEnv->SetShortField(*obj, fieldLicLeftDay, pLicenseQuery->m_u16LicLeftDay);

	jfieldID fieldRfu = g_cbData.m_pEnv->GetFieldID(cls, "m_Rfu1", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldRfu, pLicenseQuery->m_Rfu1[0]);

	LogInfo("Exit SetData_LicenseQuery");
}

void SetData_ModRelate	(Acs_ModRelate_Data* pModRelateData, jobject* obj)
{
	LogInfo("Entry SetData_ModRelate");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fieldModCount = g_cbData.m_pEnv->GetFieldID(cls, "m_u8ModCount", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldModCount, pModRelateData->m_u8ModCount);

	jfieldID fieldSrcModType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8SrcModType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldSrcModType, pModRelateData->m_u8SrcModType);

	jfieldID fieldSrcModUnitID = g_cbData.m_pEnv->GetFieldID(cls, "m_u8SrcModUnitID", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldSrcModUnitID, pModRelateData->m_u8SrcModUnitID);

	jfieldID fieldm_rfu1 = g_cbData.m_pEnv->GetFieldID(cls, "m_rfu1", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldm_rfu1, pModRelateData->m_rfu1[0]);

	jfieldID fieldRelateMod = g_cbData.m_pEnv->GetFieldID(cls, "m_RelateMod", "[LDJKeygoe/Acs_ModRelate_Mod;");
	jobjectArray objArray = (jobjectArray)g_cbData.m_pEnv->GetObjectField(*obj, fieldRelateMod);

	for (int i=0; i<g_cbData.m_pEnv->GetArrayLength(objArray); i++)
	{
		jobject objModRelate_Mod = g_cbData.m_pEnv->GetObjectArrayElement(objArray, i);
		
		SetData_ModRelateMod((Acs_ModRelate_Mod*)(pModRelateData->m_RelateMod), &objModRelate_Mod);
	} 
    
	LogInfo("Exit SetData_ModRelate");
}

void SetData_ModRelateMod(Acs_ModRelate_Mod* pModRelateData, jobject* obj)
{
	LogInfo("Entry SetData_ModRelateMod");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fieldModuleType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8ModuleType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldModuleType, pModRelateData->m_u8ModuleType);

	jfieldID fieldUnitID = g_cbData.m_pEnv->GetFieldID(cls, "m_u8UnitID", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldUnitID, pModRelateData->m_u8UnitID);

	jfieldID fieldFlag = g_cbData.m_pEnv->GetFieldID(cls, "m_u8Flag", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldFlag, pModRelateData->m_u8Flag);

	jfieldID fieldRfu1 = g_cbData.m_pEnv->GetFieldID(cls, "m_s8Rfu1", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldRfu1, pModRelateData->m_s8Rfu1[0]);

	jfieldID fieldIp = g_cbData.m_pEnv->GetFieldID(cls, "m_s8IPAddress", "[B");
	jbyteArray szIp = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldIp));
	SetByteArrayData(&szIp, (byte*)pModRelateData->m_s8IPAddress, 32);
	
	jfieldID fieldPort = g_cbData.m_pEnv->GetFieldID(cls, "m_u32Port", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldPort, pModRelateData->m_u32Port);

	jfieldID fieldRfu2 = g_cbData.m_pEnv->GetFieldID(cls, "m_s8Rfu2", "[B");
	jbyteArray szRfu2 = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldRfu2));
	SetByteArrayData(&szRfu2, (byte*)pModRelateData->m_s8Rfu2, 4);

	LogInfo("Exit SetData_ModRelateMod");
}

void SetData_Unifailure(Acs_UniFailure_Data* pUnifailureData, jobject* obj)
{
	LogInfo("Entry SetData_Unifailure");

	jclass UnfailureCla = g_cbData.m_pEnv->GetObjectClass(*obj); 

	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(UnfailureCla, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pUnifailureData->m_s32AcsEvtState);

	jfieldID fieldEvtErrCode = g_cbData.m_pEnv->GetFieldID(UnfailureCla, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtErrCode, pUnifailureData->m_s32AcsEvtErrCode);

	LogInfo("Exit SetData_Unifailure");
}

void SetData_DevListHead(Acs_Dev_List_Head_t* pListHead, jobject* obj)
{
	LogInfo("Entry SetData_DevListHead");

	jclass ListHeadCla =  g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fieldDevMain = g_cbData.m_pEnv->GetFieldID(ListHeadCla, "m_s32DeviceMain", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldDevMain, pListHead->m_s32DeviceMain); 

	jfieldID fieldModuleId = g_cbData.m_pEnv->GetFieldID(ListHeadCla, "m_s32ModuleID", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldModuleId, pListHead->m_s32ModuleID); //更改一个整形变量

	jfieldID fieldDevNum = g_cbData.m_pEnv->GetFieldID(ListHeadCla, "m_s32DeviceNum", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldDevNum, pListHead->m_s32DeviceNum); //更改一个整形变量

	LogInfo("Exit SetData_DevListHead");
}

void GetData_MediaInfo(JNIEnv* env, Acs_VoIP_MediaInfo* pMediaInfo, jobject* obj)
{
	LogInfo("Entry GetData_MediaInfo");

	jclass cla =  env->GetObjectClass(*obj);
	
	jfieldID fdPayload_dtmf = env->GetFieldID(cla, "payload_dtmf", "B");
	pMediaInfo->payload_dtmf = env->GetByteField(*obj, fdPayload_dtmf); 

	jfieldID fdPayload_tone = env->GetFieldID(cla, "payload_tone", "B");
	pMediaInfo->payload_tone = env->GetByteField(*obj, fdPayload_tone);

	jfieldID fdAudioEnabled = env->GetFieldID(cla, "u8AudioEnabled", "B");
	pMediaInfo->u8AudioEnabled = env->GetByteField(*obj, fdAudioEnabled);

	jfieldID fdAudioAdd = env->GetFieldID(cla, "s8AudioAddress", "[B");
	jbyteArray AudioAddr = (jbyteArray)(env->GetObjectField(*obj, fdAudioAdd));
	GetByteArrayData(env, (byte *)pMediaInfo->s8AudioAddress, &AudioAddr, 20);

	jfieldID fdAudioPort = env->GetFieldID(cla, "u16AudioPort", "S");
	pMediaInfo->u16AudioPort = env->GetShortField(*obj, fdAudioPort);

	jfieldID fdVideoEnabled = env->GetFieldID(cla, "u8VideoEnabled", "B");
	pMediaInfo->u8VideoEnabled = env->GetByteField(*obj, fdVideoEnabled);

	jfieldID fdVideoAdd = env->GetFieldID(cla, "s8VideoAddress", "[B");
	jbyteArray VideoAddr = (jbyteArray)(env->GetObjectField(*obj, fdVideoAdd));
	GetByteArrayData(env, (byte *)pMediaInfo->s8VideoAddress, &VideoAddr, 20);

	jfieldID fdVideoPort = env->GetFieldID(cla, "u16VideoPort", "S");
	pMediaInfo->u16VideoPort = env->GetShortField(*obj, fdVideoPort);

	jfieldID fdMediaCapNum = env->GetFieldID(cla, "u8MediaCapNum", "B");
	pMediaInfo->u8MediaCapNum = env->GetByteField(*obj, fdMediaCapNum);

	jfieldID fdMediaCapList = env->GetFieldID(cla, "u8MediaCapList", "[B");
	jbyteArray MediaCapList = (jbyteArray)(env->GetObjectField(*obj, fdMediaCapList));
	GetByteArrayData(env, (byte *)pMediaInfo->u8MediaCapList, &MediaCapList, 10);

	LogInfo("Exit GetData_MediaInfo");
}

void GetData_RtpSession(JNIEnv* env, Acs_VoIP_RTPSESSION* pRtpSen, jobject* obj)
{
	LogInfo("Entry GetData_RtpSession");

	jclass cla =  env->GetObjectClass(*obj);

	jfieldID fdEnable = env->GetFieldID(cla, "m_u8Enable", "B");
	pRtpSen->m_u8Enable = env->GetByteField(*obj, fdEnable); 

	jfieldID fdPayloadDtmf = env->GetFieldID(cla, "m_u8PayloadDtmf", "B");
	pRtpSen->m_u8PayloadDtmf = env->GetByteField(*obj, fdPayloadDtmf); 

	jfieldID fdPayloadTone = env->GetFieldID(cla, "m_u8PayloadTone", "B");
	pRtpSen->m_u8PayloadTone = env->GetByteField(*obj, fdPayloadTone); 

	LogInfo("Exit GetData_RtpSession");
}

void GetData_CmdVoice(JNIEnv * env, CmdParamData_Voice_t* cmdVocData, jobject* obj)
{
	LogInfo("Entry GetData_CmdVoice");

	jclass CmdVocCla =  env->GetObjectClass(*obj);

	jfieldID fieldInputCtrlValid = env->GetFieldID(CmdVocCla, "m_u8InputCtrlValid", "B");
	cmdVocData->m_u8InputCtrlValid = env->GetByteField(*obj, fieldInputCtrlValid); 

	jfieldID fieldPlayGainMode = env->GetFieldID(CmdVocCla, "m_u8PlayGainMode", "B");
	cmdVocData->m_u8PlayGainMode = env->GetByteField(*obj, fieldPlayGainMode); 

	jfieldID fieldPlayFixGain = env->GetFieldID(CmdVocCla, "m_u16PlayFixGain", "S");
	cmdVocData->m_u16PlayFixGain = env->GetShortField(*obj, fieldPlayFixGain); 

	jfieldID fieldVocInputControl = env->GetFieldID(CmdVocCla, "m_VocInputControl", "LDJKeygoe/VocInputControlParam_t;");
	jobject  objVocInputControl = env->GetObjectField(*obj, fieldVocInputControl);
	GetData_VocInputControl(env, &objVocInputControl, &cmdVocData->m_VocInputControl);

	jfieldID fieldOutputCtrlValid = env->GetFieldID(CmdVocCla, "m_u8OutputCtrlValid", "B");
	cmdVocData->m_u8OutputCtrlValid = env->GetByteField(*obj, fieldOutputCtrlValid); 

	jfieldID fieldRfu2 = env->GetFieldID(CmdVocCla, "m_s8Rfu2", "[B");
	jbyteArray m_Rfu2 = (jbyteArray)(env->GetObjectField(*obj, fieldRfu2));
	GetByteArrayData(env, (byte *)&cmdVocData->m_s8Rfu2[0], &m_Rfu2, 3);

	jfieldID fieldVocOutputControl = env->GetFieldID(CmdVocCla, "m_VocOutputControl", "LDJKeygoe/VocOutputControlParam_t;");
	jobject  objVocOutputControl = env->GetObjectField(*obj, fieldVocOutputControl);
	GetData_VocOutputControl(env, &objVocOutputControl, &cmdVocData->m_VocOutputControl);

	jfieldID fieldGtdCtrlValid = env->GetFieldID(CmdVocCla, "m_u8GtdCtrlValid", "B");
	cmdVocData->m_u8GtdCtrlValid = env->GetByteField(*obj, fieldGtdCtrlValid); 

	jfieldID fieldRfu3 = env->GetFieldID(CmdVocCla, "m_s8Rfu3", "[B");
	jbyteArray m_Rfu3 = (jbyteArray)(env->GetObjectField(*obj, fieldRfu3));
	GetByteArrayData(env, (byte *)&cmdVocData->m_s8Rfu3[0], &m_Rfu3, 3);

	jfieldID fieldVocGtdCtrl = env->GetFieldID(CmdVocCla, "m_VocGtdControl", "LDJKeygoe/VocGtdControlParam_t;");
	jobject  objfieldVocGtdCtrl = env->GetObjectField(*obj, fieldVocGtdCtrl);
	GetData_GtdControl(env, &objfieldVocGtdCtrl, &cmdVocData->m_VocGtdControl);

	LogInfo("Exit GetData_CmdVoice");
}

void GetData_324CH_t(JNIEnv* env, CmdParamData_324CH_t* p324Ch_t, jobject* obj)
{
	LogInfo("Entry GetData_324CH_t");

	jclass cla =  env->GetObjectClass(*obj);
	
	jfieldID fdChannel_Enable = env->GetFieldID(cla, "m_u8Channel_Enable", "B");
	p324Ch_t->m_u8Channel_Enable = env->GetByteField(*obj,fdChannel_Enable);

	jfieldID fdAudioSRC1_Ctrl = env->GetFieldID(cla, "m_u8AudioSRC1_Ctrl", "B");
	p324Ch_t->m_u8AudioSRC1_Ctrl = env->GetByteField(*obj,fdAudioSRC1_Ctrl);

	jfieldID fdAudioSRC2_Ctrl = env->GetFieldID(cla, "m_u8AudioSRC2_Ctrl", "B");
	p324Ch_t->m_u8AudioSRC2_Ctrl = env->GetByteField(*obj,fdAudioSRC2_Ctrl);

	jfieldID fdVideoSRC1_Ctrl = env->GetFieldID(cla, "m_u8VideoSRC1_Ctrl", "B");
	p324Ch_t->m_u8VideoSRC1_Ctrl = env->GetByteField(*obj,fdVideoSRC1_Ctrl);

	jfieldID fdAudioSRC1_ID = env->GetFieldID(cla, "m_u16AudioSRC1_ID", "S");
	p324Ch_t->m_u16AudioSRC1_ID = env->GetShortField(*obj,fdAudioSRC1_ID);

	jfieldID fdAudioSRC2_ID = env->GetFieldID(cla, "m_u16AudioSRC2_ID", "S");
	p324Ch_t->m_u16AudioSRC2_ID = env->GetShortField(*obj,fdAudioSRC2_ID);

	jfieldID fdVideoSRC1_ID = env->GetFieldID(cla, "m_u16VideoSRC1_ID", "S");
	p324Ch_t->m_u16VideoSRC1_ID = env->GetShortField(*obj,fdVideoSRC1_ID);

	jfieldID fdAudioInDecodeFlag = env->GetFieldID(cla, "m_u8AudioInDecodeFlag", "B");
	p324Ch_t->m_u8AudioInDecodeFlag = env->GetByteField(*obj,fdAudioInDecodeFlag);

	jfieldID fdAudioOutEncodeFlag = env->GetFieldID(cla, "m_u8AudioOutEncodeFlag", "B");
	p324Ch_t->m_u8AudioOutEncodeFlag = env->GetByteField(*obj,fdAudioOutEncodeFlag);

	jfieldID fdAudioInCodec = env->GetFieldID(cla, "m_u8AudioInCodec", "B");
	p324Ch_t->m_u8AudioInCodec = env->GetByteField(*obj,fdAudioInCodec);

	jfieldID fdAudioOutCodec = env->GetFieldID(cla, "m_u8AudioOutCodec", "B");
	p324Ch_t->m_u8AudioOutCodec = env->GetByteField(*obj,fdAudioOutCodec);

	jfieldID fdVideoInCodec = env->GetFieldID(cla, "m_u8VideoInCodec", "B");
	p324Ch_t->m_u8VideoInCodec = env->GetByteField(*obj,fdVideoInCodec);
	
	jfieldID fdVideoOutCodec = env->GetFieldID(cla, "m_u8VideoOutCodec", "B");
	p324Ch_t->m_u8VideoOutCodec = env->GetByteField(*obj,fdVideoOutCodec);

	LogInfo("Exit GetData_324CH_t");
}

void GetData_GtdFreq(JNIEnv * env, CmdParamData_GtdFreq_t* GtdFreq, jobject* obj)
{
	LogInfo("Entry GetData_GtdFreq");

	jclass GtdFreqCla =  env->GetObjectClass(*obj);

	jfieldID fieldFreqIndex = env->GetFieldID(GtdFreqCla, "m_u16Freq_Index", "S");
	GtdFreq->m_u16Freq_Index = env->GetShortField(*obj,fieldFreqIndex);

	jfieldID fieldFreqCoef = env->GetFieldID(GtdFreqCla, "m_u16Freq_Coef", "S");
	GtdFreq->m_u16Freq_Coef = env->GetShortField(*obj,fieldFreqCoef);

	LogInfo("Exit GetData_GtdFreq");
}

void GetData_AnalogTrunk(JNIEnv* env, CmdParamData_AnalogTrunk_t* AnalogTrk, jobject* obj)
{
	LogInfo("Entry GetData_AnalogTrunk");

//	jclass cls = env->FindClass("DJKeygoe/DJAcsAPIDef");
//	jfieldID fieldAnalogTrk = env->GetFieldID(cls, "AnalogTrk", "LDJKeygoe/CmdParamData_AnalogTrunk_t;");
//	jobject obj = env->GetObjectField(g_cbData.m_objCallBack, fieldAnalogTrk);
	jclass GtdFreqCla =  env->GetObjectClass(*obj);

	jfieldID fieldRingCount = env->GetFieldID(GtdFreqCla, "m_u16CallInRingCount", "S");
	AnalogTrk->m_u16CallInRingCount = env->GetShortField(*obj,fieldRingCount);
	
	jfieldID fieldRingTimeOut = env->GetFieldID(GtdFreqCla, "m_u16CallInRingTimeOut", "S");
	AnalogTrk->m_u16CallInRingTimeOut = env->GetShortField(*obj,fieldRingTimeOut);

	LogInfo("Exit GetData_AnalogTrunkGetAnalogTrunkParamData");
}

void GetData_AnalogUser(JNIEnv* env, CmdParamData_AnalogUser_t* AnalogUserData, jobject* obj)
{
	LogInfo("Entry GetData_AnalogUser");

//	jclass cls = env->FindClass("DJKeygoe/DJAcsAPIDef");
//	jfieldID fieldUser = env->GetFieldID(cls, "g_AnalogUser", "LDJKeygoe/CmdParamData_AnalogUser_t;");
//	jobject obj = env->GetObjectField(g_cbData.m_objCallBack, fieldUser);
	jclass AnalogUserCla =  env->GetObjectClass(*obj);

	jfieldID FieldCallerIdOption = env->GetFieldID(AnalogUserCla, "m_u8CallerIdOption", "B");
	AnalogUserData->m_u8CallerIdOption = env->GetByteField(*obj, FieldCallerIdOption);

	jfieldID FieldRingCadenceType = env->GetFieldID(AnalogUserCla, "m_u8RingCadenceType", "B");
	AnalogUserData->m_u8RingCadenceType = env->GetByteField(*obj, FieldRingCadenceType);

	jfieldID FieldCallOutRingTimeOut = env->GetFieldID(AnalogUserCla, "m_u8CallOutRingTimeOut", "B");
	AnalogUserData->m_u8CallOutRingTimeOut = env->GetByteField(*obj, FieldCallOutRingTimeOut);

	jfieldID FieldRfu1 = env->GetFieldID(AnalogUserCla, "m_u8Rfu1", "B");
	AnalogUserData->m_u8Rfu1 = env->GetByteField(*obj, FieldRfu1);

	jfieldID FieldRfu2 = env->GetFieldID(AnalogUserCla, "m_u8Rfu2", "[B");
	jbyteArray rfu = (jbyteArray)(env->GetObjectField(*obj, FieldRfu2));
	GetByteArrayData(env, (byte *)&AnalogUserData->m_u8Rfu2[0], &rfu, 12);

	LogInfo("Exit GetData_AnalogUser");
}

void GetData_TransAddFile	 (JNIEnv* env, Acs_TransAddFile* pTransAddFile, jobject* obj)
{
	LogInfo("Entry GetData_TransAddFile");

	jclass Cla =  env->GetObjectClass(*obj);

	jfieldID fd32Op = env->GetFieldID(Cla, "m_u32Op", "I");
	pTransAddFile->m_u32Op = env->GetIntField(*obj, fd32Op);
	
	jfieldID fdFileName = env->GetFieldID(Cla, "m_strFileName", "[B");
	jbyteArray strFileName = (jbyteArray)(env->GetObjectField(*obj, fdFileName));
	GetByteArrayData(env, (byte*)pTransAddFile->m_strFileName, &strFileName, 256);

	LogInfo("Exit GetData_TransAddFile");
}

void GetData_RtpCodec(JNIEnv* env, Acs_VoIP_RTPCODEC* pRtpCodec, jobject* obj)
{
	LogInfo("Entry GetData_RtpCodec");

	jclass cla =  env->GetObjectClass(*obj);

	jfieldID fdAudio = env->GetFieldID(cla, "audio", "LDJKeygoe/ChCodec;");
	jobject  audioObj = env->GetObjectField(*obj, fdAudio);
	GetData_ChCodecAudio(env, &audioObj, pRtpCodec);

	jfieldID fdVideo = env->GetFieldID(cla, "video", "LDJKeygoe/ChCodec;");
	jobject  videoObj = env->GetObjectField(*obj, fdVideo);
	GetData_ChCodecVideo(env, &videoObj, pRtpCodec);

	LogInfo("Exit GetData_RtpCodec");
}

void GetData_Cas(JNIEnv * env, CmdParamData_CAS_t* CasData, jobject* obj)
{
	LogInfo("Entry GetData_Cas");

	jclass CasCla =  env->GetObjectClass(*obj);

	jfieldID fieldDevice = env->GetFieldID(CasCla, "m_VocDevID", "LDJKeygoe/DeviceID_t;");
	jobject  DeviceObj = env->GetObjectField(*obj, fieldDevice);
	GetData_DeviceID(env, &DeviceObj, &CasData->m_VocDevID);

	jfieldID FieldCalledTableCnt = env->GetFieldID(CasCla, "m_u8CalledTableCount", "B");
	CasData->m_u8CalledTableCount = env->GetByteField(*obj, FieldCalledTableCnt);

	jfieldID FieldRefu = env->GetFieldID(CasCla, "m_Rfu1", "[B");
	jbyteArray rfu = (jbyteArray)(env->GetObjectField(*obj, FieldRefu));
	GetByteArrayData(env, (byte *)&CasData->m_Rfu1[0], &rfu, 3);

	jfieldID FieldCalledTable = env->GetFieldID(CasCla, "m_CalledTable", "[LDJKeygoe/CAS_CalledTableDesc_t;");
	jobjectArray ObjArr_CalledTable = (jobjectArray)(env->GetObjectField(*obj, FieldCalledTable));
	GetObjectArrayData_CalledTable(env, &CasData->m_CalledTable[0], &ObjArr_CalledTable, 16);

	jfieldID FieldCalledLen = env->GetFieldID(CasCla, "m_u8CalledLen", "B");
	CasData->m_u8CalledLen = env->GetByteField(*obj, FieldCalledLen);

	jfieldID FieldCalledTimeOut = env->GetFieldID(CasCla, "m_u8CalledTimeOut", "B");
	CasData->m_u8CalledTimeOut = env->GetByteField(*obj, FieldCalledTimeOut);

	jfieldID FieldNeedCaller = env->GetFieldID(CasCla, "m_u8NeedCaller", "B");
	CasData->m_u8NeedCaller = env->GetByteField(*obj, FieldNeedCaller);

	jfieldID FieldCodeLen = env->GetFieldID(CasCla, "m_u8AreaCodeLen", "B");
	CasData->m_u8AreaCodeLen = env->GetByteField(*obj, FieldCodeLen);

	jfieldID FieldKA = env->GetFieldID(CasCla, "m_u8KA", "B");
	CasData->m_u8KA = env->GetByteField(*obj, FieldKA);

	jfieldID FieldKD = env->GetFieldID(CasCla, "m_u8KD", "B");
	CasData->m_u8KD = env->GetByteField(*obj, FieldKD);

	jfieldID FieldCtrlMode = env->GetFieldID(CasCla, "m_u8ControlMode", "B");
	CasData->m_u8ControlMode = env->GetByteField(*obj, FieldCtrlMode);

	jfieldID FieldCtyCode = env->GetFieldID(CasCla, "m_u8CountryCode", "B");
	CasData->m_u8CountryCode = env->GetByteField(*obj, FieldCtyCode);

	jfieldID FieldCallType = env->GetFieldID(CasCla, "m_u8CallType", "B");
	CasData->m_u8CallType = env->GetByteField(*obj, FieldCallType);

	jfieldID FieldAppendCallee = env->GetFieldID(CasCla, "m_u8AppendCallee", "B");
	CasData->m_u8AppendCallee = env->GetByteField(*obj, FieldAppendCallee);

	jfieldID FieldRefu2 = env->GetFieldID(CasCla, "m_u8Rfu", "[B");
	jbyteArray rfu2 = (jbyteArray)(env->GetObjectField(*obj, FieldRefu2));
	GetByteArrayData(env, (byte *)&CasData->m_u8Rfu[0], &rfu2, 6);

	LogInfo("Exit GetData_Cas");
}

void SetData_MediaProc(Acs_MediaProc_Data* pMediaData, jobject* obj)
{
	LogInfo("Entry SetData_MediaProc");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pMediaData->m_s32AcsEvtState);
	
	jfieldID fieldErrCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrCode, pMediaData->m_s32AcsEvtErrCode);

	jfieldID fieldTaskID = g_cbData.m_pEnv->GetFieldID(cls, "m_u8TaskID", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldTaskID, pMediaData->m_u8TaskID);

	jfieldID fieldGTD = g_cbData.m_pEnv->GetFieldID(cls, "m_u8GTD", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldGTD, pMediaData->m_u8GTD);

	jfieldID fieldCurFileIndex = g_cbData.m_pEnv->GetFieldID(cls, "m_u32CurFileIndex", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldCurFileIndex, pMediaData->m_u32CurFileIndex);
	
	jfieldID fieldCurFilePos = g_cbData.m_pEnv->GetFieldID(cls, "m_u32CurFilePos", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldCurFilePos, pMediaData->m_u32CurFilePos);

	LogInfo("Exit SetData_MediaProc");
}

void SetData_IOData(Acs_IO_Data* pIOData, jobject* obj)
{
	LogInfo("Entry SetData_IOData");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pIOData->m_s32AcsEvtState);
	
	jfieldID fieldErrCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrCode, pIOData->m_s32AcsEvtErrCode);

	jfieldID fieldIoType = g_cbData.m_pEnv->GetFieldID(cls, "m_u16IoType", "S");
	g_cbData.m_pEnv->SetShortField(*obj, fieldIoType, pIOData->m_u16IoType);

	jfieldID fieldIoDataLen = g_cbData.m_pEnv->GetFieldID(cls, "m_u16IoDataLen", "S");
	g_cbData.m_pEnv->SetShortField(*obj, fieldIoDataLen, pIOData->m_u16IoDataLen);

	LogInfo("Exit SetData_IOData");
}

void SetData_ReadSn(CmdParamData_ReadSn_t* pReadSn, jobject* obj)
{
	LogInfo("Entry SetData_ReadSn");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fdReadSn = g_cbData.m_pEnv->GetFieldID(cls, "m_u8ReadSn", "[B");
	jbyteArray szReadSn = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdReadSn));
	SetByteArrayData(&szReadSn, (byte *)(pReadSn->m_u8ReadSn), 13);

	jfieldID fdReserved = g_cbData.m_pEnv->GetFieldID(cls, "m_u8Reserved", "[B");
	jbyteArray szReserved = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdReserved));
	SetByteArrayData(&szReserved, (byte *)(pReadSn->m_u8Reserved), 3);

	LogInfo("Exit SetData_ReadSn");
}

void SetData_CallControl(Acs_CallControl_Data* pCallCtrlData, jobject* obj)
{
	LogInfo("Entry SetData_CallControl");

	jclass CallCtrlCla =  g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(CallCtrlCla, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pCallCtrlData->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(CallCtrlCla, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pCallCtrlData->m_s32AcsEvtErrCode);
	
	jfieldID fieldClearCause = g_cbData.m_pEnv->GetFieldID(CallCtrlCla, "m_s32CallClearCause", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldClearCause, pCallCtrlData->m_s32CallClearCause);
	
	jfieldID fieldCallingCategory = g_cbData.m_pEnv->GetFieldID(CallCtrlCla, "m_u8CallingCategory", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldCallingCategory, pCallCtrlData->m_u8CallingCategory);
	
	jfieldID fieldCallingAddrCategory = g_cbData.m_pEnv->GetFieldID(CallCtrlCla, "m_u8CallingAddressIndicator", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldCallingAddrCategory, pCallCtrlData->m_u8CallingAddressIndicator);
	
	jfieldID fieldCalledAddrCategory = g_cbData.m_pEnv->GetFieldID(CallCtrlCla, "m_u8CalledAddressIndicator", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldCalledAddrCategory, pCallCtrlData->m_u8CalledAddressIndicator );
	
	jfieldID fieldRfu = g_cbData.m_pEnv->GetFieldID(CallCtrlCla, "m_s8Rfu1", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldRfu, pCallCtrlData->m_s8Rfu1[0]);
	
	jfieldID fieldCallingNum = g_cbData.m_pEnv->GetFieldID(CallCtrlCla, "m_s8CallingNum", "[B");
	jbyteArray CallingNum = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldCallingNum));
	SetByteArrayData(&CallingNum, (byte *)(pCallCtrlData->m_s8CallingNum), 32);
	
	jfieldID fieldCalledNum = g_cbData.m_pEnv->GetFieldID(CallCtrlCla, "m_s8CalledNum", "[B");
	jbyteArray CalledNum = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldCalledNum));
	SetByteArrayData(&CalledNum, (byte *)(pCallCtrlData->m_s8CalledNum), 32);
	
	jfieldID fieldCallDirect = g_cbData.m_pEnv->GetFieldID(CallCtrlCla, "m_u8DRSCallDirectFlag", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldCallDirect, pCallCtrlData->m_u8DRSCallDirectFlag);
	
	jfieldID fieldRfu1 = g_cbData.m_pEnv->GetFieldID(CallCtrlCla, "m_s8Rfu2", "[B");
	jbyteArray s8Rfu = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldRfu1));
	SetByteArrayData(&s8Rfu, (byte *)(pCallCtrlData->m_s8Rfu2), 31);

	LogInfo("Exit SetData_CallControl");
}

void SetData_AnalogInterface(Acs_AnalogInterface_Data * pAnalogInterfaceData, jobject* obj)
{
	LogInfo("Entry SetData_AnalogInterface");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pAnalogInterfaceData->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pAnalogInterfaceData->m_s32AcsEvtErrCode);

	jfieldID fieldInterface = g_cbData.m_pEnv->GetFieldID(cls, "m_u8AnalogInterfaceState", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldInterface, pAnalogInterfaceData->m_u8AnalogInterfaceState);
	
	jfieldID fieldRfu = g_cbData.m_pEnv->GetFieldID(cls, "m_Rfu1", "[B");
	jbyteArray szRfu = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldRfu));
	SetByteArrayData(&szRfu, (byte *)(pAnalogInterfaceData->m_Rfu1), 3);

	LogInfo("Exit SetData_AnalogInterface");
}

void SetData_SendSigMsg(Acs_SendSigMsg_Data* pSendSigMsgData, jobject* obj)
{
	LogInfo("Entry SetData_SendSigMsg");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pSendSigMsgData->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pSendSigMsgData->m_s32AcsEvtErrCode);

	jfieldID fieldSignalMsgType = g_cbData.m_pEnv->GetFieldID(cls, "m_s16SignalMsgType", "S");
	g_cbData.m_pEnv->SetShortField(*obj, fieldSignalMsgType, pSendSigMsgData->m_s16SignalMsgType);

	jfieldID fieldRfu = g_cbData.m_pEnv->GetFieldID(cls, "m_s8Rfu", "[B");
	jbyteArray szRfu = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldRfu));
	SetByteArrayData(&szRfu, (byte *)(pSendSigMsgData->m_s8Rfu), 3);

	LogInfo("Exit SetData_SendSigMsg");
}

void SetData_SigMon(Acs_SigMon_Data* pSigMon, jobject* obj)
{
	LogInfo("Entry SetData_SigMon");
/*
	jclass cls =  g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldSigMon = g_cbData.m_pEnv->GetFieldID(cls, "m_SigMon", "LDJKeygoe/SMON_EVENT;");
	jobject  objSigMon = g_cbData.m_pEnv->GetObjectField(*obj, fieldSigMon);
	jclass	 cls1 = g_cbData.m_pEnv->GetObjectClass(objSigMon);

	jfieldID fieldEventType = g_cbData.m_pEnv->GetFieldID(cls, "EventType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldEventType, pSigMon->EventType);

	jfieldID fieldProtocol = g_cbData.m_pEnv->GetFieldID(cls, "Protocol", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldProtocol, pSigMon->Protocol);

	jfieldID fieldSI = g_cbData.m_pEnv->GetFieldID(cls, "SI", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldSI, pSigMon->SI);

	jfieldID fieldMsgType = g_cbData.m_pEnv->GetFieldID(cls, "MsgType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldMsgType, pSigMon->MsgType);

	jfieldID fieldCallerID = g_cbData.m_pEnv->GetFieldID(cls, "Caller_ID", "[B");
	jbyteArray szCallerID = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldCallerID));
	SetByteArrayData(&szCallerID, (byte *)(pSigMon->Caller_ID), 32);

	jfieldID fieldCalledID = g_cbData.m_pEnv->GetFieldID(cls, "Called_ID", "[B");
	jbyteArray szCalledID = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldCalledID));
	SetByteArrayData(&szCalledID, (byte *)(pSigMon->Caller_ID), 32);

	jfieldID fieldOriCalled = g_cbData.m_pEnv->GetFieldID(cls, "OriCalled", "[B");
	jbyteArray szOriCalled = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldOriCalled));
	SetByteArrayData(&szOriCalled, (byte *)(pSigMon->OriCalled), 32);

	jfieldID fieldDPC = g_cbData.m_pEnv->GetFieldID(cls, "DPC", "[B");
	jbyteArray szDPC = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldDPC));
	SetByteArrayData(&szDPC, (byte *)(pSigMon->szDPC), 3);

	jfieldID fieldOPC = g_cbData.m_pEnv->GetFieldID(cls, "OPC", "[B");
	jbyteArray szOPC = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldOPC));
	SetByteArrayData(&szOPC, (byte *)(pSigMon->szOPC), 3);

	jfieldID fieldPcm = g_cbData.m_pEnv->GetFieldID(cls, "Pcm", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldPcm, pSigMon->Pcm);

	jfieldID fieldChn = g_cbData.m_pEnv->GetFieldID(cls, "Chn", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldChn, pSigMon->Chn);

	jfieldID fieldReleaseReason = g_cbData.m_pEnv->GetFieldID(cls, "ReleaseReason", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldReleaseReason, pSigMon->ReleaseReason);

	jfieldID fieldReserved = g_cbData.m_pEnv->GetFieldID(cls, "Reserved", "[B");
	jbyteArray szReserved = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldReserved));
	SetByteArrayData(&szReserved, (byte *)(pSigMon->Reserved), 14);

	jfieldID fieldUnitID = g_cbData.m_pEnv->GetFieldID(cls, "Unit_ID", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldUnitID, pSigMon->Unit_ID);

	jfieldID fieldPortID = g_cbData.m_pEnv->GetFieldID(cls, "Port_ID", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldPortID, pSigMon->Port_ID);

	jfieldID fieldTs = g_cbData.m_pEnv->GetFieldID(cls, "TS", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldTs, pSigMon->TS);

	jfieldID fieldDatalen = g_cbData.m_pEnv->GetFieldID(cls, "DataLen", "S");
	g_cbData.m_pEnv->SetShortField(*obj, fieldDatalen, pSigMon->DataLen);

	jfieldID fieldRAWdata = g_cbData.m_pEnv->GetFieldID(cls, "RAWdata", "[B");
	jbyteArray szRAWdata = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldRAWdata));
	SetByteArrayData(&szRAWdata, (byte *)(pSigMon->Reserved), 2048);
*/
	LogInfo("Exit SetData_SigMon");
}

void SetData_CtxReg(Acs_CtxReg_Data* pCtxReg, jobject* obj)
{
	LogInfo("Entry SetData_CtxReg");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pCtxReg->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pCtxReg->m_s32AcsEvtErrCode);

	LogInfo("Exit SetData_CtxReg");
}

void SetData_CtxLink(Acs_CtxLink_Data* pCtxLink, jobject* obj)
{
	LogInfo("Entry SetData_CtxLink");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pCtxLink->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pCtxLink->m_s32AcsEvtErrCode);

	LogInfo("Exit SetData_CtxLink");
}

void SetData_CtxAppDataInfo(Acs_CtxAppData_Info* pCtxApp, jobject* obj)
{
	LogInfo("Entry SetData_CtxAppDataInfo");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pCtxApp->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pCtxApp->m_s32AcsEvtErrCode);

	jfieldID fdAppDataInfo = g_cbData.m_pEnv->GetFieldID(cls, "m_AppDataInfo", "LDJKeygoe/CTX_AppData_Info;");
	jobject objAppDataInfo = g_cbData.m_pEnv->GetObjectField(*obj, fdAppDataInfo);
	jclass  clsAppData = g_cbData.m_pEnv->GetObjectClass(objAppDataInfo);

	jfieldID fieldAppDataSize = g_cbData.m_pEnv->GetFieldID(clsAppData, "m_u32AppDataSize", "I");
	g_cbData.m_pEnv->SetIntField(objAppDataInfo, fieldAppDataSize, pCtxApp->m_AppDataInfo.m_u32AppDataSize);

	jfieldID fieldAppReqType = g_cbData.m_pEnv->GetFieldID(clsAppData, "m_u8AppReqType", "B");
	g_cbData.m_pEnv->SetByteField(objAppDataInfo, fieldAppReqType, pCtxApp->m_AppDataInfo.m_u8AppReqType);

	jfieldID fieldAcsUnitID = g_cbData.m_pEnv->GetFieldID(clsAppData, "m_u8AcsUnitID", "B");
	g_cbData.m_pEnv->SetByteField(objAppDataInfo, fieldAcsUnitID, pCtxApp->m_AppDataInfo.m_u8AcsUnitID);

	jfieldID fieldRfu1 = g_cbData.m_pEnv->GetFieldID(cls, "m_Rfu1", "[B");
	jbyteArray szRfu1 = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldRfu1));
	SetByteArrayData(&szRfu1, (byte *)(pCtxApp->m_AppDataInfo.m_Rfu1), 2);

	jfieldID fieldSrcRegName = g_cbData.m_pEnv->GetFieldID(cls, "m_s8SrcRegName", "[B");
	jbyteArray szSrcRegName = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldSrcRegName));
	SetByteArrayData(&szSrcRegName, (byte *)(pCtxApp->m_AppDataInfo.m_s8SrcRegName), 16);

	jfieldID fieldDestRegName = g_cbData.m_pEnv->GetFieldID(cls, "m_s8DestRegName", "[B");
	jbyteArray szDestRegName = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldDestRegName));
	SetByteArrayData(&szDestRegName, (byte *)(pCtxApp->m_AppDataInfo.m_s8DestRegName), 16);

	jfieldID fieldSrcAppUnitID = g_cbData.m_pEnv->GetFieldID(clsAppData, "m_u8SrcAppUnitID", "B");
	g_cbData.m_pEnv->SetByteField(objAppDataInfo, fieldSrcAppUnitID, pCtxApp->m_AppDataInfo.m_u8SrcAppUnitID);

	jfieldID fieldDstAppUnitID = g_cbData.m_pEnv->GetFieldID(clsAppData, "m_u8DstAppUnitID", "B");
	g_cbData.m_pEnv->SetByteField(objAppDataInfo, fieldDstAppUnitID, pCtxApp->m_AppDataInfo.m_u8DstAppUnitID);

	jfieldID fieldRfu2 = g_cbData.m_pEnv->GetFieldID(cls, "m_Rfu2", "[B");
	jbyteArray szRfu2 = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldRfu2));
	SetByteArrayData(&szRfu2, (byte *)(pCtxApp->m_AppDataInfo.m_Rfu2), 2);

	jfieldID fdDevice = g_cbData.m_pEnv->GetFieldID(cls, "m_srcDevice", "LDJKeygoe/DeviceID_t;");
	jobject objDevice = g_cbData.m_pEnv->GetObjectField(*obj, fdDevice);
	SetData_DeviceID(&pCtxApp->m_AppDataInfo.m_srcDevice, &objDevice);

	jfieldID fieldRfu3 = g_cbData.m_pEnv->GetFieldID(cls, "m_Rfu3", "[B");
	jbyteArray szRfu3 = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldRfu3));
	SetByteArrayData(&szRfu3, (byte *)(pCtxApp->m_AppDataInfo.m_Rfu3), 20);

	jfieldID fieldRst = g_cbData.m_pEnv->GetFieldID(clsAppData, "m_s32Rst", "I");
	g_cbData.m_pEnv->SetIntField(objAppDataInfo, fieldRst, pCtxApp->m_AppDataInfo.m_s32Rst);

	LogInfo("Exit SetData_CtxAppDataInfo");
}

void SetData_ConfControl(Acs_ConfControl_Data* pConfCtrl, jobject* obj)
{
	LogInfo("Entry SetData_ConfControl");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pConfCtrl->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pConfCtrl->m_s32AcsEvtErrCode);
	
	jfieldID fieldConfMembers = g_cbData.m_pEnv->GetFieldID(cls, "m_s32ConfMembers", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldConfMembers, pConfCtrl->m_s32ConfMembers);

	jfieldID fdDevice = g_cbData.m_pEnv->GetFieldID(cls, "m_MediaDevice", "LDJKeygoe/DeviceID_t;");
	jobject objDevice = g_cbData.m_pEnv->GetObjectField(*obj, fdDevice);
	SetData_DeviceID(&pConfCtrl->m_MediaDevice, &objDevice);

	LogInfo("Exit SetData_ConfControl");
}

void SetData_CspDataReq(Acs_CSPDataReq_Data* pCspDataReq, jobject* obj)
{
	LogInfo("Entry SetData_CspDataReq");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldReqCspDataLen = g_cbData.m_pEnv->GetFieldID(cls, "m_u16ReqCspDataLen", "S");
	g_cbData.m_pEnv->SetShortField(*obj, fieldReqCspDataLen, pCspDataReq->m_u16ReqCspDataLen);

	jfieldID fieldTaskID = g_cbData.m_pEnv->GetFieldID(cls, "m_u8TaskID", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldTaskID, pCspDataReq->m_u8TaskID);

	jfieldID fieldDataType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8DataType", "S");
	g_cbData.m_pEnv->SetShortField(*obj, fieldDataType, pCspDataReq->m_u8DataType);

	LogInfo("Exit SetData_CspDataReq");
}

void SetData_MediaCspProc(Acs_MediaCSPProc_Data* pMediaProcData, jobject* obj)
{
	LogInfo("Entry SetData_MediaCspProc");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldDataLen = g_cbData.m_pEnv->GetFieldID(cls, "m_u16DataLen", "S");
	g_cbData.m_pEnv->SetShortField(*obj, fieldDataLen, pMediaProcData->m_u16DataLen);

	jfieldID fieldDataType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8DataType", "B");
	g_cbData.m_pEnv->SetShortField(*obj, fieldDataType, pMediaProcData->m_u8DataType);

	jfieldID fieldTagNumber = g_cbData.m_pEnv->GetFieldID(cls, "m_u8TagNumber", "B");
	g_cbData.m_pEnv->SetShortField(*obj, fieldTagNumber, pMediaProcData->m_u8TagNumber);
	
	jfieldID fieldStreamData = g_cbData.m_pEnv->GetFieldID(cls, "m_u8StreamData", "[B");
	jbyteArray szStreamData = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldStreamData));
	SetByteArrayData(&szStreamData, (byte *)(pMediaProcData->m_u8StreamData), 4000);

	LogInfo("Exit SetData_MediaCspProc");
}

void SetData_Media3GppProc(Acs_Media3GPPProc_Data* pMediaProcData, jobject* obj)
{
	LogInfo("Entry SetData_Media3GppProc");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pMediaProcData->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pMediaProcData->m_s32AcsEvtErrCode);

	jfieldID fieldAudioTaskID = g_cbData.m_pEnv->GetFieldID(cls, "m_u8AudioTaskID", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldAudioTaskID, pMediaProcData->m_u8AudioTaskID);

	jfieldID fieldMediaType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8MediaType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldMediaType, pMediaProcData->m_u8MediaType);

	jfieldID fieldVideoTaskID = g_cbData.m_pEnv->GetFieldID(cls, "m_u8VideoTaskID", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldVideoTaskID, pMediaProcData->m_u8VideoTaskID);

	jfieldID fieldRfu = g_cbData.m_pEnv->GetFieldID(cls, "m_s8Rfu", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldRfu, pMediaProcData->m_s8Rfu);

	jfieldID fieldAudioCurFileIndex = g_cbData.m_pEnv->GetFieldID(cls, "m_u32AudioCurFileIndex", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldAudioCurFileIndex, pMediaProcData->m_u32AudioCurFileIndex);

	jfieldID fieldAudioCurFilePos = g_cbData.m_pEnv->GetFieldID(cls, "m_u32AudioCurFilePos", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldAudioCurFilePos, pMediaProcData->m_u32AudioCurFilePos);

	jfieldID fieldVideoCurFileIndex = g_cbData.m_pEnv->GetFieldID(cls, "m_u32VideoCurFileIndex", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldVideoCurFileIndex, pMediaProcData->m_u32VideoCurFileIndex);

	jfieldID fieldVideoCurFilePos = g_cbData.m_pEnv->GetFieldID(cls, "m_u32VideoCurFilePos", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldVideoCurFilePos, pMediaProcData->m_u32VideoCurFilePos);

	LogInfo("Exit SetData_Media3GppProc");
}

void SetData_FaxProc(Acs_FaxProc_Data* pFaxProcData, jobject* obj)
{
	LogInfo("Entry SetData_FaxProc");
	
	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldAcsEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldAcsEvtState, pFaxProcData->m_s32AcsEvtState);

	jfieldID fieldAcsEvtErrCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldAcsEvtErrCode, pFaxProcData->m_s32AcsEvtErrCode);

	jfieldID fieldErrorStep = g_cbData.m_pEnv->GetFieldID(cls, "m_u8ErrorStep", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldErrorStep, pFaxProcData->m_u8ErrorStep);

	jfieldID fieldT30SendState = g_cbData.m_pEnv->GetFieldID(cls, "m_u8T30SendState", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldT30SendState, pFaxProcData->m_u8T30SendState);

	jfieldID fieldRecvT30Cmd = g_cbData.m_pEnv->GetFieldID(cls, "m_u8RecvT30Cmd", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldRecvT30Cmd, pFaxProcData->m_u8RecvT30Cmd);

	jfieldID fieldRfu1 = g_cbData.m_pEnv->GetFieldID(cls, "m_u8Rfu1", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldRfu1, pFaxProcData->m_u8Rfu1);

	jfieldID fieldTotalPages = g_cbData.m_pEnv->GetFieldID(cls, "m_u16TotalPages", "S");
	g_cbData.m_pEnv->SetShortField(*obj, fieldTotalPages, pFaxProcData->m_u16TotalPages);

	jfieldID fieldRemoteID = g_cbData.m_pEnv->GetFieldID(cls, "m_s8RemoteID", "[B");
	jbyteArray szRemoteID = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldRemoteID));
	SetByteArrayData(&szRemoteID, (byte *)(pFaxProcData->m_u8Rfu2), 20);

	jfieldID fieldRfu2 = g_cbData.m_pEnv->GetFieldID(cls, "m_u8Rfu2", "[B");
	jbyteArray szRfu2 = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldRfu2));
	SetByteArrayData(&szRfu2, (byte *)(pFaxProcData->m_u8Rfu2), 2);

	LogInfo("Exit SetData_FaxProc");
}

void SetData_SS7RawFrame(Acs_SS7RawFrame_Data* pSs7RawFrame, jobject* obj)
{
	LogInfo("Entry SetData_SS7RawFrame");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldUserType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8UserType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldUserType, pSs7RawFrame->m_u8UserType);

	jfieldID fieldLinkType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8LinkType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldLinkType, pSs7RawFrame->m_u8LinkType);

	jfieldID fieldInfoType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8InfoType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldInfoType, pSs7RawFrame->m_u8InfoType);

	jfieldID fieldInfoLen = g_cbData.m_pEnv->GetFieldID(cls, "m_u8InfoLen", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldInfoLen, pSs7RawFrame->m_u8InfoLen);

	jfieldID fieldRfu1 = g_cbData.m_pEnv->GetFieldID(cls, "m_u8Rfu1", "[B");
	jbyteArray szRfu1 = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldRfu1));
	SetByteArrayData(&szRfu1, (byte *)(pSs7RawFrame->m_u8Rfu1), 4);

	jfieldID fieldInfo = g_cbData.m_pEnv->GetFieldID(cls, "m_u8Info", "[B");
	jbyteArray szInfo = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldInfo));
	SetByteArrayData(&szInfo, (byte *)(pSs7RawFrame->m_u8Info), 255);

	jfieldID fieldRfu2 = g_cbData.m_pEnv->GetFieldID(cls, "m_u8Rfu2", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldRfu2, pSs7RawFrame->m_u8Rfu2);

	LogInfo("Exit SetData_SS7RawFrame");
}

void SetData_ClockRefSrcState(ACS_Clock_RefSrc_State_Data* pData, jobject* obj)
{
	LogInfo("Entry SetData_ClockRefSrcState");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldModuleID = g_cbData.m_pEnv->GetFieldID(cls, "m_u8ModuleID", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldModuleID, pData->m_u8ModuleID);

	jfieldID fieldE1ID = g_cbData.m_pEnv->GetFieldID(cls, "m_u8E1ID", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldE1ID, pData->m_u8E1ID);

	jfieldID fieldState = g_cbData.m_pEnv->GetFieldID(cls, "m_u8State", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldState, pData->m_u8State);

	jfieldID fieldClockType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8ClockType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldClockType, pData->m_u8ClockType);

	jfieldID fieldRef = g_cbData.m_pEnv->GetFieldID(cls, "m_u8Ref", "[B");
	jbyteArray szRef = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fieldRef));
	SetByteArrayData(&szRef, (byte *)(pData->m_u8Ref), 4);

	LogInfo("Exit SetData_ClockRefSrcState");
}

void SetData_3Gpp(CmdParamData_3GPP_t* p3Gpp,  jobject* obj)
{
	LogInfo("Entry SetData_3Gpp");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fdAudioDecodeType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8AudioDecodeType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdAudioDecodeType, p3Gpp->m_u8AudioDecodeType);

	jfieldID fdAudioFrameType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8AudioFrameType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdAudioFrameType, p3Gpp->m_u8AudioFrameType);

	jfieldID fdAudioDecoderCfgLen = g_cbData.m_pEnv->GetFieldID(cls, "m_u16AudioDecoderCfgLen", "S");
	g_cbData.m_pEnv->SetShortField(*obj, fdAudioDecoderCfgLen, p3Gpp->m_u16AudioDecoderCfgLen);

	jfieldID fdAudioDecoderCfg = g_cbData.m_pEnv->GetFieldID(cls, "m_u8AudioDecoderCfg", "[B");
	jbyteArray szAudioDecoderCfg = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdAudioDecoderCfg));
	SetByteArrayData(&szAudioDecoderCfg, (byte *)(p3Gpp->m_u8AudioDecoderCfg), 200);

	jfieldID fdAudioProfiles = g_cbData.m_pEnv->GetFieldID(cls, "m_u8AudioProfiles", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdAudioProfiles, p3Gpp->m_u8AudioProfiles);

	jfieldID fdAudioLevel = g_cbData.m_pEnv->GetFieldID(cls, "m_u8AudioLevel", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdAudioLevel, p3Gpp->m_u8AudioLevel);

	jfieldID fdRfu1 = g_cbData.m_pEnv->GetFieldID(cls, "m_Rfu1", "[B");
	jbyteArray szRfu1 = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdRfu1));
	SetByteArrayData(&szRfu1, (byte *)(p3Gpp->m_Rfu1), 2);

	jfieldID fdVideoDecodeType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8VideoDecodeType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdVideoDecodeType, p3Gpp->m_u8VideoDecodeType);
	
	jfieldID fdVideoFrameType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8VideoFrameRate", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdVideoFrameType, p3Gpp->m_u8VideoFrameRate);
	
	jfieldID fdVideoDecoderCfgLen = g_cbData.m_pEnv->GetFieldID(cls, "m_u16VideoDecoderCfgLen", "S");
	g_cbData.m_pEnv->SetShortField(*obj, fdVideoDecoderCfgLen, p3Gpp->m_u16VideoDecoderCfgLen);
	
	jfieldID fdVideoDecoderCfg = g_cbData.m_pEnv->GetFieldID(cls, "m_u8VideoDecoderCfg", "[B");
	jbyteArray szVideoDecoderCfg = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdVideoDecoderCfg));
	SetByteArrayData(&szVideoDecoderCfg, (byte *)(p3Gpp->m_u8VideoDecoderCfg), 200);
	
	jfieldID fdVideoProfiles = g_cbData.m_pEnv->GetFieldID(cls, "m_u8VideoProfiles", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdVideoProfiles, p3Gpp->m_u8VideoProfiles);
	
	jfieldID fdVideoLevel = g_cbData.m_pEnv->GetFieldID(cls, "m_u8VideoLevel", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdVideoLevel, p3Gpp->m_u8VideoLevel);
	
	jfieldID fdRfu2 = g_cbData.m_pEnv->GetFieldID(cls, "m_Rfu2", "[B");
	jbyteArray szRfu2 = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdRfu2));
	SetByteArrayData(&szRfu2, (byte *)(p3Gpp->m_Rfu2), 2);

	LogInfo("Exit SetData_3Gpp");
}

void SetData_3G324(Acs_3G324_Data* p3G324Data, jobject* obj)
{
	LogInfo("Entry SetData_3G324");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldDataType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8DataType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldDataType, p3G324Data->m_u8DataType);

	jfieldID fieldRfu = g_cbData.m_pEnv->GetFieldID(cls, "Rfu1", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldRfu, p3G324Data->Rfu1);

	jfieldID fieldDataLen = g_cbData.m_pEnv->GetFieldID(cls, "m_u16DataLen", "S");
	g_cbData.m_pEnv->SetShortField(*obj, fieldDataLen, p3G324Data->m_u16DataLen);

	LogInfo("Exit SetData_3G324");
}

void SetData_Board(Acs_ParamData_UserReadXmsBoardInfo* pBoardInfo, jobject* obj)
{
	LogInfo("Entry SetData_Board");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fdMacAddr = g_cbData.m_pEnv->GetFieldID(cls, "m_u8MacAddr", "[B");
	jbyteArray szMacAddr = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdMacAddr));
	SetByteArrayData(&szMacAddr, (byte *)(pBoardInfo->m_u8MacAddr), 6);
	
	jfieldID fdChassisType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8ChassisType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdChassisType, pBoardInfo->m_u8ChassisType);

	jfieldID fdChassisIndex = g_cbData.m_pEnv->GetFieldID(cls, "m_u8ChassisIndex", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdChassisIndex, pBoardInfo->m_u8ChassisIndex);

	jfieldID fdChassisSlot = g_cbData.m_pEnv->GetFieldID(cls, "m_u8ChassisSlot", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdChassisSlot, pBoardInfo->m_u8ChassisSlot);

	jfieldID fdSubBoardIndex = g_cbData.m_pEnv->GetFieldID(cls, "m_u8SubBoardIndex", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdSubBoardIndex, pBoardInfo->m_u8SubBoardIndex);

	jfieldID fdBoardType = g_cbData.m_pEnv->GetFieldID(cls, "m_u8BoardType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdBoardType, pBoardInfo->m_u8BoardType);

	jfieldID fdRfu1 = g_cbData.m_pEnv->GetFieldID(cls, "rfu1", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdRfu1, pBoardInfo->rfu1[0]);

	jfieldID fdSystemName = g_cbData.m_pEnv->GetFieldID(cls, "m_s8SystemName", "[B");
	jbyteArray szSystemName = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdSystemName));
	SetByteArrayData(&szSystemName, (byte *)(pBoardInfo->m_s8SystemName), 32);

	jfieldID fdPlatformType = g_cbData.m_pEnv->GetFieldID(cls, "m_s8PlatformType", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdPlatformType, pBoardInfo->m_s8PlatformType);

	jfieldID fdUserCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s8UserCode", "[B");
	jbyteArray szUserCode = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdUserCode));
	SetByteArrayData(&szUserCode, (byte *)(pBoardInfo->m_s8UserCode), 7);

	jfieldID fdSysId = g_cbData.m_pEnv->GetFieldID(cls, "m_s32SysId", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fdSysId, pBoardInfo->m_s32SysId);

	jfieldID fdRfu2 = g_cbData.m_pEnv->GetFieldID(cls, "rfu2", "[B");
	jbyteArray szRfu2 = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdRfu2));
	SetByteArrayData(&szRfu2, (byte *)(pBoardInfo->rfu2), 20);

	jfieldID fdFirmwareName = g_cbData.m_pEnv->GetFieldID(cls, "m_s8FirmwareName", "[B");
	jbyteArray szFirmwareName = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdFirmwareName));
	SetByteArrayData(&szFirmwareName, (byte *)(pBoardInfo->m_s8FirmwareName), 8);

	jfieldID fdFirmwareVersion = g_cbData.m_pEnv->GetFieldID(cls, "m_s8FirmwareVersion", "[B");
	jbyteArray szFirmwareVersion = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdFirmwareVersion));
	SetByteArrayData(&szFirmwareVersion, (byte *)(pBoardInfo->m_s8FirmwareVersion), 8);

	jfieldID fdRevisionDate = g_cbData.m_pEnv->GetFieldID(cls, "m_s8RevisionDate", "[B");
	jbyteArray szRevisionDate = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdRevisionDate));
	SetByteArrayData(&szRevisionDate, (byte *)(pBoardInfo->m_s8RevisionDate), 8);

	LogInfo("Exit SetData_Board");
}

void SetData_ReadVolteage(CmdParamData_ReadVoltage_t* pReadVoltage, jobject* obj)
{
	LogInfo("Entry SetData_ReadVolteage");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fdReadFlag = g_cbData.m_pEnv->GetFieldID(cls, "m_u8ReadFlag", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdReadFlag, pReadVoltage->m_u8ReadFlag);

	jfieldID fdReserved1= g_cbData.m_pEnv->GetFieldID(cls, "m_s8Reserved1", "[B");
	jbyteArray szReserved1 = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdReserved1));
	SetByteArrayData(&szReserved1, (byte*)pReadVoltage->m_s8Reserved1, 3);

	jfieldID fdTimeSpan = g_cbData.m_pEnv->GetFieldID(cls, "m_u32TimeSpan", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fdTimeSpan, pReadVoltage->m_u32TimeSpan);

	jfieldID fdVoltage = g_cbData.m_pEnv->GetFieldID(cls, "m_s8Voltage", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdVoltage, pReadVoltage->m_s8Voltage);

	jfieldID fdReserved2= g_cbData.m_pEnv->GetFieldID(cls, "m_u8Reserved2", "[B");
	jbyteArray szReserved2 = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdReserved2));
	SetByteArrayData(&szReserved2, (byte*)pReadVoltage->m_u8Reserved2, 3);

	LogInfo("Exit SetData_ReadVolteage");
}

void SetData_JoinTo3GVConf(Acs_JoinTo3GVConf_Data* pJoinTo3GVConf, jobject* obj)
{
	LogInfo("Entry SetData_JoinTo3GVConf");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pJoinTo3GVConf->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pJoinTo3GVConf->m_s32AcsEvtErrCode);
	
	jfieldID fdDevice = g_cbData.m_pEnv->GetFieldID(cls, "m_3GVConfDev", "LDJKeygoe/DeviceID_t;");
	jobject objDevice = g_cbData.m_pEnv->GetObjectField(*obj, fdDevice);
	SetData_DeviceID(&pJoinTo3GVConf->m_3GVConfDev, &objDevice);
	
	jfieldID fdSrcDevice = g_cbData.m_pEnv->GetFieldID(cls, "m_srcDev", "LDJKeygoe/DeviceID_t;");
	jobject objSrcDevice = g_cbData.m_pEnv->GetObjectField(*obj, fdDevice);
	SetData_DeviceID(&pJoinTo3GVConf->m_srcDev, &objSrcDevice);

	LogInfo("Exit SetData_JoinTo3GVConf");
}

void SetData_LeaveFrom3GVConf(Acs_LeaveFrom3GVConf_Data* pLeaveFreom3GVConfData, jobject* obj)
{
	LogInfo("Entry SetData_LeaveFrom3GVConf");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pLeaveFreom3GVConfData->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pLeaveFreom3GVConfData->m_s32AcsEvtErrCode);
	
	jfieldID fdDevice = g_cbData.m_pEnv->GetFieldID(cls, "m_3GVConfDev", "LDJKeygoe/DeviceID_t;");
	jobject objDevice = g_cbData.m_pEnv->GetObjectField(*obj, fdDevice);
	SetData_DeviceID(&pLeaveFreom3GVConfData->m_3GVConfDev, &objDevice);

	jfieldID fdSrcDevice = g_cbData.m_pEnv->GetFieldID(cls, "m_srcDev", "LDJKeygoe/DeviceID_t;");
	jobject objSrcDevice = g_cbData.m_pEnv->GetObjectField(*obj, fdDevice);
	SetData_DeviceID(&pLeaveFreom3GVConfData->m_srcDev, &objSrcDevice);

	LogInfo("Exit SetData_LeaveFrom3GVConf");
}

void SetData_Clear3GVConf(Acs_Clear3GVConf_Data* pClear3GvConfData, jobject* obj)
{
	LogInfo("Entry SetData_Clear3GVConf");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pClear3GvConfData->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pClear3GvConfData->m_s32AcsEvtErrCode);
	
	jfieldID fdDevice = g_cbData.m_pEnv->GetFieldID(cls, "m_3GVConfDev", "LDJKeygoe/DeviceID_t;");
	jobject objDevice = g_cbData.m_pEnv->GetObjectField(*obj, fdDevice);
	SetData_DeviceID(&pClear3GvConfData->m_3GVConfDev, &objDevice);

	LogInfo("Exit SetData_Clear3GVConf");
}

void SetData_GetLayout(Acs_GetLayout_Data* pGetLayoutData, jobject* obj)
{
	LogInfo("Entry SetData_GetLayout");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pGetLayoutData->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pGetLayoutData->m_s32AcsEvtErrCode);
	
	jfieldID fdDevice = g_cbData.m_pEnv->GetFieldID(cls, "m_3GVConfDev", "LDJKeygoe/DeviceID_t;");
	jobject objDevice = g_cbData.m_pEnv->GetObjectField(*obj, fdDevice);
	SetData_DeviceID(&pGetLayoutData->m_3GVConfDev, &objDevice);
	
	jfieldID fdVisibleList = g_cbData.m_pEnv->GetFieldID(cls, "m_list", "LDJKeygoe/Acs_3GVConf_VisibleList;");
	jobject objVisibleList = (jobject)g_cbData.m_pEnv->GetObjectField(*obj, fdVisibleList);
	
	jclass  clslList = g_cbData.m_pEnv->GetObjectClass(objVisibleList);
	
	jfieldID fieldDevice = g_cbData.m_pEnv->GetFieldID(clslList, "m_device", "LDJKeygoe/DeviceID_t;");
	jobjectArray objDeviceArr = (jobjectArray)g_cbData.m_pEnv->GetObjectField(objVisibleList, fieldDevice);
	
	for (int i=0; i<g_cbData.m_pEnv->GetArrayLength(objDeviceArr); i++)
	{
		jobject objDevice = g_cbData.m_pEnv->GetObjectArrayElement(objDeviceArr, i);
		SetData_DeviceID(&(pGetLayoutData->m_list.m_device[i]), &objDevice);
	}

	LogInfo("Exit SetData_GetLayout");
}

void SetData_SetLayout(Acs_SetLayout_Data* pSetLayoutData, jobject* obj)
{
	LogInfo("Entry SetData_GetLayout");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pSetLayoutData->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pSetLayoutData->m_s32AcsEvtErrCode);
	
	jfieldID fdDevice = g_cbData.m_pEnv->GetFieldID(cls, "m_3GVConfDev", "LDJKeygoe/DeviceID_t;");
	jobject objDevice = g_cbData.m_pEnv->GetObjectField(*obj, fdDevice);
	SetData_DeviceID(&pSetLayoutData->m_3GVConfDev, &objDevice);

	LogInfo("Exit SetData_GetLayout");
}

void SetData_GetVisibleList(Acs_GetVisibleList_Data* pGetVisibleList, jobject* obj)
{
	LogInfo("Entry SetData_GetVisibleList");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pGetVisibleList->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pGetVisibleList->m_s32AcsEvtErrCode);
	
	jfieldID fdDevice = g_cbData.m_pEnv->GetFieldID(cls, "m_3GVConfDev", "LDJKeygoe/DeviceID_t;");
	jobject objDevice = g_cbData.m_pEnv->GetObjectField(*obj, fdDevice);
	SetData_DeviceID(&pGetVisibleList->m_3GVConfDev, &objDevice);

	jfieldID fdVisibleList = g_cbData.m_pEnv->GetFieldID(cls, "m_list", "LDJKeygoe/Acs_3GVConf_VisibleList;");
	jobject objVisibleList = (jobject)g_cbData.m_pEnv->GetObjectField(*obj, fdVisibleList);
	
	jclass  clslList = g_cbData.m_pEnv->GetObjectClass(objVisibleList);
	
	jfieldID fieldDevice = g_cbData.m_pEnv->GetFieldID(clslList, "m_device", "LDJKeygoe/DeviceID_t;");
	jobjectArray objDeviceArr = (jobjectArray)g_cbData.m_pEnv->GetObjectField(objVisibleList, fieldDevice);

	for (int i=0; i<g_cbData.m_pEnv->GetArrayLength(objDeviceArr); i++)
	{
		jobject objDevice = g_cbData.m_pEnv->GetObjectArrayElement(objDeviceArr, i);
		SetData_DeviceID(&pGetVisibleList->m_list.m_device[i], &objDevice);
	}

	LogInfo("Exit SetData_GetVisibleList");
}

void SetData_SetVisibleList(Acs_SetVisibleList_Data* pGetVisibleList, jobject* obj)
{
	LogInfo("Entry SetData_SetVisibleList");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);

	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pGetVisibleList->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pGetVisibleList->m_s32AcsEvtErrCode);

	jfieldID fdDevice = g_cbData.m_pEnv->GetFieldID(cls, "m_3GVConfDev", "LDJKeygoe/DeviceID_t;");
	jobject objDevice = g_cbData.m_pEnv->GetObjectField(*obj, fdDevice);
	SetData_DeviceID( &pGetVisibleList->m_3GVConfDev, &objDevice);

	LogInfo("Exit SetData_SetVisibleList");
}

void SetData_MasterState(Acs_MasterState_Data* pMasterStateData, jobject* obj)
{
	LogInfo("Entry SetData_MasterState");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fdServerIp= g_cbData.m_pEnv->GetFieldID(cls, "m_s8ServerIp", "[B");
	jbyteArray szIp = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdServerIp));
	SetByteArrayData(&szIp, (byte*)pMasterStateData->m_s8ServerIp, 32);

	jfieldID fieldServerPort= g_cbData.m_pEnv->GetFieldID(cls, "m_u32ServerPort", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldServerPort, pMasterStateData->m_u32ServerPort);

	jfieldID fieldMasterState= g_cbData.m_pEnv->GetFieldID(cls, "m_u8MasterState", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldMasterState, pMasterStateData->m_u8MasterState);

	jfieldID fdRfu= g_cbData.m_pEnv->GetFieldID(cls, "m_Rfu1", "[B");
	jbyteArray szRfu = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdRfu));
	SetByteArrayData(&szRfu, (byte*)pMasterStateData->m_Rfu1, 3);

	LogInfo("Exit SetData_MasterState");
}

void SetData_SlaveWorkState(Acs_SlaveWorkState_Data* pSlaveWorkStateData, jobject* obj)
{
	LogInfo("Entry SetData_SlaveWorkState");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldWorkState= g_cbData.m_pEnv->GetFieldID(cls, "m_s8WorkState", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fieldWorkState, pSlaveWorkStateData->m_s8WorkState);

	jfieldID fdRfu= g_cbData.m_pEnv->GetFieldID(cls, "m_Rfu1", "[B");
	jbyteArray s8Rfu = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdRfu));
	SetByteArrayData(&s8Rfu, (byte*)pSlaveWorkStateData->m_Rfu1, 31);

	LogInfo("Exit SetData_SlaveWorkState");
}

void SetData_LinkDevData(Acs_LinkDev_Data* pLinkDevData, jobject* obj)
{
	LogInfo("Entry SetData_LinkDevData");

	jclass cls = g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fieldEvtState = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtState", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldEvtState, pLinkDevData->m_s32AcsEvtState);
	
	jfieldID fieldErrorCode = g_cbData.m_pEnv->GetFieldID(cls, "m_s32AcsEvtErrCode", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fieldErrorCode, pLinkDevData->m_s32AcsEvtErrCode);

	jfieldID fdSrcDevice = g_cbData.m_pEnv->GetFieldID(cls, "m_SrcDevice", "LDJKeygoe/DeviceID_t;");
	jobject objSrcDevice = g_cbData.m_pEnv->GetObjectField(*obj, fdSrcDevice);
	SetData_DeviceID(&pLinkDevData->m_SrcDevice, &objSrcDevice);

	jfieldID fdDestDevice = g_cbData.m_pEnv->GetFieldID(cls, "m_DestDevice", "LDJKeygoe/DeviceID_t;");
	jobject objDestDevice = g_cbData.m_pEnv->GetObjectField(*obj, fdDestDevice);
	SetData_DeviceID(&pLinkDevData->m_DestDevice, &objDestDevice);

	LogInfo("Exit SetData_LinkDevData");
}

void SetData_VoipCallPrivate(VoIPCallPrivate_t* pVoipCallData, jobject* obj)
{
	LogInfo("Entry SetData_VoipCallPrivate");

	jclass cls =  g_cbData.m_pEnv->GetObjectClass(*obj);
	
	jfieldID fdProtocol = g_cbData.m_pEnv->GetFieldID(cls, "m_s32Protocol", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fdProtocol, pVoipCallData->m_s32Protocol);

	jfieldID fdCallerAddress = g_cbData.m_pEnv->GetFieldID(cls, "m_s8CallerAddress", "[B");
	jbyteArray s8CallerAddress = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdCallerAddress));
	SetByteArrayData(&s8CallerAddress, (byte*)pVoipCallData->m_s8CallerAddress, 20);

	jfieldID fdCallerPort = g_cbData.m_pEnv->GetFieldID(cls, "m_s32CallerPort", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fdCallerPort, pVoipCallData->m_s32CallerPort);

	jfieldID fdCallerUserID = g_cbData.m_pEnv->GetFieldID(cls, "m_s8CallerUserID", "[B");
	jbyteArray s8CallerUserID = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdCallerUserID));
	SetByteArrayData(&s8CallerUserID, (byte*)pVoipCallData->m_s8CallerUserID, 40);

	jfieldID fdCalleeAddress = g_cbData.m_pEnv->GetFieldID(cls, "m_s8CalleeAddress", "[B");
	jbyteArray s8CalleeAddress = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdCalleeAddress));
	SetByteArrayData(&s8CalleeAddress, (byte*)pVoipCallData->m_s8CalleeAddress, 20);

	jfieldID fdCalleePort = g_cbData.m_pEnv->GetFieldID(cls, "m_s32CalleePort", "I");
	g_cbData.m_pEnv->SetIntField(*obj, fdCalleePort, pVoipCallData->m_s32CalleePort);

	jfieldID fdCalleeUserID = g_cbData.m_pEnv->GetFieldID(cls, "m_s8CalleeUserID", "[B");
	jbyteArray s8CalleeUserID = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdCalleeUserID));
	SetByteArrayData(&s8CalleeUserID, (byte*)pVoipCallData->m_s8CalleeUserID, 40);

	jfieldID fdCapNum = g_cbData.m_pEnv->GetFieldID(cls, "m_u8MediaCapNum", "B");
	g_cbData.m_pEnv->SetByteField(*obj, fdCapNum, pVoipCallData->m_u8MediaCapNum);

	jfieldID fdMediaCapList = g_cbData.m_pEnv->GetFieldID(cls, "m_u8MediaCapList", "[B");
	jbyteArray s8fdMediaCapList = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(*obj, fdMediaCapList));
	SetByteArrayData(&s8fdMediaCapList, (byte*)pVoipCallData->m_u8MediaCapList, 10);

	LogInfo("Exit SetData_VoipCallPrivate");
}

/*void SetData_CallOut(Acs_CallControl_Data* pCallOutData)
{
	LogInfo("Entry SetData_CallOut");

	jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJAcsAPIDef");
	jfieldID fieldCallCtrl = g_cbData.m_pEnv->GetFieldID(cls, "CallOutData", "LDJKeygoe/Acs_CallControl_Data;");
	jobject obj = g_cbData.m_pEnv->GetObjectField(g_cbData.m_objCallBack, fieldCallCtrl);
	
	SetData_CallControl(&obj, pCallOutData);
	
	LogInfo("Exit SetData_CallOut");
}

void SetData_CallIn(Acs_CallControl_Data* pCallInData)
{
	LogInfo("Entry SetData_CallIn");

	jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJAcsAPIDef");
	jfieldID fieldCallCtrl = g_cbData.m_pEnv->GetFieldID(cls, "CallCtrlData", "LDJKeygoe/Acs_CallControl_Data;");
	jobject obj = g_cbData.m_pEnv->GetObjectField(g_cbData.m_objCallBack, fieldCallCtrl);

	SetData_CallControl(&obj, pCallInData);

	LogInfo("Exit SetData_CallIn");
}*/
					  
void GetData_GtdProtoType(JNIEnv* env, CmdParamData_GtdProtoType_t* GtdProtoType, jobject* obj)
{
	LogInfo("Entry GetData_GtdProtoType");

//	jclass cls = env->FindClass("DJKeygoe/DJAcsAPIDef");
//	jfieldID fieldGtdProtoType = env->GetFieldID(cls, "TmpGtdProto", "LDJKeygoe/CmdParamData_GtdProtoType_t;");
//	jobject obj = env->GetObjectField(g_cbData.m_objCallBack, fieldGtdProtoType);
	jclass GtdProtoTypeCla = env->GetObjectClass(*obj);

	jfieldID fieldGtdID = env->GetFieldID(GtdProtoTypeCla, "m_u16GtdID", "S");
	GtdProtoType->m_u16GtdID = env->GetShortField(*obj, fieldGtdID);
	
	jfieldID fieldFreqMask = env->GetFieldID(GtdProtoTypeCla, "m_u16Freq_Mask", "S");
	GtdProtoType->m_u16Freq_Mask = env->GetShortField(*obj, fieldFreqMask);

	jfieldID fieldThreshold = env->GetFieldID(GtdProtoTypeCla, "m_u16Amp_Threshold", "S");
	GtdProtoType->m_u16Amp_Threshold = env->GetShortField(*obj, fieldThreshold);
	
	jfieldID fieldEnvelopeMode = env->GetFieldID(GtdProtoTypeCla, "m_u16Envelope_Mode", "S");
	GtdProtoType->m_u16Envelope_Mode = env->GetShortField(*obj, fieldEnvelopeMode);

	jfieldID fieldRepeatCount = env->GetFieldID(GtdProtoTypeCla, "m_u16Repeat_Count", "S");
	GtdProtoType->m_u16Repeat_Count = env->GetShortField(*obj, fieldRepeatCount);

	jfieldID fieldMinOnTime1 = env->GetFieldID(GtdProtoTypeCla, "m_u16Min_On_Time1", "S");
	GtdProtoType->m_u16Min_On_Time1 = env->GetShortField(*obj, fieldMinOnTime1);

	jfieldID fieldMaxOnTime1 = env->GetFieldID(GtdProtoTypeCla, "m_u16Max_On_Time1", "S");
	GtdProtoType->m_u16Max_On_Time1 = env->GetShortField(*obj, fieldMaxOnTime1);

	jfieldID fieldMinOffTime1 = env->GetFieldID(GtdProtoTypeCla, "m_u16Min_Off_Time1", "S");
	GtdProtoType->m_u16Min_Off_Time1 = env->GetShortField(*obj, fieldMinOffTime1);

	jfieldID fieldMaxOffTime1 = env->GetFieldID(GtdProtoTypeCla, "m_u16Max_Off_Time1", "S");
	GtdProtoType->m_u16Max_Off_Time1 = env->GetShortField(*obj, fieldMaxOffTime1);

	jfieldID fieldMinOnTime2 = env->GetFieldID(GtdProtoTypeCla, "m_u16Min_On_Time2", "S");
	GtdProtoType->m_u16Min_On_Time2 = env->GetShortField(*obj, fieldMinOnTime2);

	jfieldID fieldMaxOnTime2 = env->GetFieldID(GtdProtoTypeCla, "m_u16Max_On_Time2", "S");
	GtdProtoType->m_u16Max_On_Time2 = env->GetShortField(*obj, fieldMaxOnTime2);

	jfieldID fieldMinOffTime2 = env->GetFieldID(GtdProtoTypeCla, "m_u16Min_Off_Time2", "S");
	GtdProtoType->m_u16Min_Off_Time2 = env->GetShortField(*obj, fieldMinOffTime2);

	jfieldID fieldMaxOffTime2 = env->GetFieldID(GtdProtoTypeCla, "m_u16Max_Off_Time2", "S");
	GtdProtoType->m_u16Max_Off_Time2 = env->GetShortField(*obj, fieldMaxOffTime2);

	LogInfo("Exit GetData_GtdProtoType");
}

void GetData_BoardCommon	 (JNIEnv* env, CmdParam_BoardCommonParam_t* pBrdCommon, jobject* obj)
{
	LogInfo("Entry GetData_BoardCommon");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdIsCNGEnable = (env)->GetFieldID(cla, "m_u8IsCNGEnable", "B");
	pBrdCommon->m_u8IsCNGEnable = (env)->GetByteField(*obj, fdIsCNGEnable);

	jfieldID fdCNGGainLevel = (env)->GetFieldID(cla, "m_u16CNGGainLevel", "S");
	pBrdCommon->m_u16CNGGainLevel = (env)->GetShortField(*obj, fdCNGGainLevel);

	jfieldID fdReserved = (env)->GetFieldID(cla, "m_u8Reserved1", "[B");
	jbyteArray ReserveArr = (jbyteArray)(env->GetObjectField(*obj, fdReserved));
	GetByteArrayData(env, (byte*)pBrdCommon->m_u8Reserved1, &ReserveArr, 29);

	LogInfo("Exit GetData_BoardCommon");
}

void GetData_VadMinDetect	 (JNIEnv* env, CmdParam_VADMinDetectParam_t* pVadMinDetect, jobject* obj)
{
	LogInfo("Entry GetData_VadMinDetect");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdVadLevel = (env)->GetFieldID(cla, "m_s32VadLevel", "I");
	pVadMinDetect->m_s32VadLevel = (env)->GetIntField(*obj, fdVadLevel);

	jfieldID fdVadInterval = (env)->GetFieldID(cla, "m_u16VadInterval", "S");
	pVadMinDetect->m_u16VadInterval = (env)->GetShortField(*obj, fdVadInterval);

	jfieldID fdReserved = (env)->GetFieldID(cla, "m_u8Reserved1", "[B");
	jbyteArray ReserveArr = (jbyteArray)(env->GetObjectField(*obj, fdReserved));
	GetByteArrayData(env, (byte*)pVadMinDetect->m_u8Reserved1, &ReserveArr, 2);

	LogInfo("Exit GetData_VadMinDetect");
}

void GetData_FlashParam		(JNIEnv* env, CmdParamData_FlashParam_t* pFlashParam, jobject* obj)
{
	LogInfo("Entry GetData_FlashParam");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdMinHookFlashTime = (env)->GetFieldID(cla, "m_u8MinHookFlashTime", "B");
	pFlashParam->m_u8MinHookFlashTime = (env)->GetByteField(*obj, fdMinHookFlashTime);

	jfieldID fdMaxHookFlashTime = (env)->GetFieldID(cla, "m_u8MaxHookFlashTime", "B");
	pFlashParam->m_u8MaxHookFlashTime = (env)->GetByteField(*obj, fdMaxHookFlashTime);

	LogInfo("Exit GetData_FlashParam");
}

void GetData_SilenceDetect	 (JNIEnv* env, CmdParam_SilenceDetectParam_t* pSilenceDetect, jobject* obj)
{
	LogInfo("Entry GetData_SilenceDetect");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdSilenceLevel = (env)->GetFieldID(cla, "m_s32SilenceLevel", "I");
	pSilenceDetect->m_s32SilenceLevel = (env)->GetIntField(*obj, fdSilenceLevel);

	jfieldID fdSilenceTimer = (env)->GetFieldID(cla, "m_s32SilenceTimer", "I");
	pSilenceDetect->m_s32SilenceTimer = (env)->GetIntField(*obj, fdSilenceTimer);

	jfieldID fdRfu = (env)->GetFieldID(cla, "m_s32Reserved2", "I");
	pSilenceDetect->m_s32Reserved2 = (env)->GetIntField(*obj, fdRfu);

	LogInfo("Exit GetData_SilenceDetect");
}

void GetData_TrkFlash(JNIEnv* env, CmdParamData_TrunkFlashParam_t* pTrkFlash, jobject* obj)
{
	LogInfo("Entry GetData_TrkFlash");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdHookFlashTime = (env)->GetFieldID(cla, "m_u8HookFlashTime", "B");
	pTrkFlash->m_u8HookFlashTime = (env)->GetByteField(*obj, fdHookFlashTime);

	jfieldID fdReserved = (env)->GetFieldID(cla, "m_u8reserved", "[B");
	jbyteArray ReserveArr = (jbyteArray)(env->GetObjectField(*obj, fdReserved));
	GetByteArrayData(env, pTrkFlash->m_u8reserved, &ReserveArr, 3);

	LogInfo("Exit GetData_TrkFlash");
}

void GetData_CtClkNet(JNIEnv* env, CmdParamData_CTCLKNET_t* pCkClknet, jobject* obj)
{
	LogInfo("Entry GetData_CtClkNet");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdNetRef1 = (env)->GetFieldID(cla, "m_u8NetRef1", "B");
	pCkClknet->m_u8NetRef1 = (env)->GetByteField(*obj, fdNetRef1);

	jfieldID fdSysClockType = (env)->GetFieldID(cla, "m_u8SysClockType", "B");
	pCkClknet->m_u8SysClockType = (env)->GetByteField(*obj, fdSysClockType);

	jfieldID fdReserved = (env)->GetFieldID(cla, "m_u8Rfu", "[B");
	jbyteArray ReserveArr = (jbyteArray)(env->GetObjectField(*obj, fdReserved));
	GetByteArrayData(env, pCkClknet->m_u8Rfu, &ReserveArr, 2);

	LogInfo("Exit GetData_CtClkNet");
}

void GetData_FskParam(JNIEnv* env, CmdParamData_FskParam_t* pFskParam, jobject* obj)
{
	LogInfo("Entry GetData_FskParam");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdFilterWindow = (env)->GetFieldID(cla, "rxFilterWindow", "S");
	pFskParam->rxFilterWindow = (env)->GetShortField(*obj, fdFilterWindow);

	jfieldID fdPeriodTheshold = (env)->GetFieldID(cla, "rxPeriodTheshold", "S");
	pFskParam->rxPeriodTheshold = (env)->GetShortField(*obj, fdPeriodTheshold);

	jfieldID fd55Count = (env)->GetFieldID(cla, "rx55Count", "S");
	pFskParam->rx55Count = (env)->GetShortField(*obj, fd55Count);

	jfieldID fdAllOneSamples = (env)->GetFieldID(cla, "rxAllOneSamples", "S");
	pFskParam->rxAllOneSamples = (env)->GetShortField(*obj, fdAllOneSamples);

	jfieldID fdDataTimeOut = (env)->GetFieldID(cla, "rxDataTimeOut", "S");
	pFskParam->rxDataTimeOut = (env)->GetShortField(*obj, fdDataTimeOut);

	jfieldID fdBit1Freq = (env)->GetFieldID(cla, "txBit1Freq", "S");
	pFskParam->txBit1Freq = (env)->GetShortField(*obj, fdBit1Freq);

	jfieldID fdBit0Freq = (env)->GetFieldID(cla, "txBit0Freq", "S");
	pFskParam->txBit0Freq = (env)->GetShortField(*obj, fdBit0Freq);

	jfieldID fdtx55Count = (env)->GetFieldID(cla, "tx55Count", "S");
	pFskParam->tx55Count = (env)->GetShortField(*obj, fdtx55Count);

	jfieldID fdtxAllOneSamples = (env)->GetFieldID(cla, "txAllOneSamples", "S");
	pFskParam->txAllOneSamples = (env)->GetShortField(*obj, fdtxAllOneSamples);

	//jfieldID fdReserved = (env)->GetFieldID(cla, "reserved", "[B");
	//jbyteArray ReserveArr = (jbyteArray)(env->GetObjectField(*obj, fdReserved));
	//GetByteArrayData(env, (byte*)pFskParam->reserved, &ReserveArr, 3);

	jfieldID fdReserved = (env)->GetFieldID(cla, "reserved", "[S");
	jshortArray ReserveArr = (jshortArray)(env->GetObjectField(*obj, fdReserved));
	strncpy((char*)pFskParam->reserved, (char*)(env->GetShortArrayElements(ReserveArr, NULL)), env->GetArrayLength(ReserveArr)*sizeof(DJ_U16));

	LogInfo("Exit GetData_FskParam");
}

void GetData_AnalogTrkFlash(JNIEnv* env, CmdParamData_AnalogTrunkFlash_t* pAnalogTrkFlash, jobject* obj)
{
	LogInfo("Entry GetData_AnalogTrkFlash");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdChannelEnable = (env)->GetFieldID(cla, "m_u8Channel_Enable", "B");
	pAnalogTrkFlash->m_u8Channel_Enable = (env)->GetByteField(*obj, fdChannelEnable);

	jfieldID fdType = (env)->GetFieldID(cla, "m_u8Type", "B");
	pAnalogTrkFlash->m_u8Type = (env)->GetByteField(*obj, fdType);

	jfieldID fdTxState = (env)->GetFieldID(cla, "m_u8Tx_State", "B");
	pAnalogTrkFlash->m_u8Tx_State = (env)->GetByteField(*obj, fdTxState);

	jfieldID fdRxState = (env)->GetFieldID(cla, "m_u8Rx_State", "B");
	pAnalogTrkFlash->m_u8Rx_State = (env)->GetByteField(*obj, fdRxState);

	LogInfo("Exit GetData_AnalogTrkFlash");
}

void GetData_AnalogEmCMD(JNIEnv* env, Acs_AnalogEM_CMD* pAnalogEm, jobject* obj)
{
	LogInfo("Entry GetData_AnalogEmCMD");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdChannelEnable = (env)->GetFieldID(cla, "m_u8Channel_Enable", "B");
	pAnalogEm->m_u8Channel_Enable = (env)->GetByteField(*obj, fdChannelEnable);

	jfieldID fdType = (env)->GetFieldID(cla, "m_u8Type", "B");
	pAnalogEm->m_u8Type = (env)->GetByteField(*obj, fdType);

	jfieldID fdTxState = (env)->GetFieldID(cla, "m_u8Tx_State", "B");
	pAnalogEm->m_u8Tx_State = (env)->GetByteField(*obj, fdTxState);

	jfieldID fdRxState = (env)->GetFieldID(cla, "m_u8Rx_State", "B");
	pAnalogEm->m_u8Rx_State = (env)->GetByteField(*obj, fdRxState);

	LogInfo("Exit GetData_AnalogEmCMD");
}

void GetData_SetEcm(JNIEnv* env, Acs_SetECM* pSetEcm, jobject* obj)
{
	LogInfo("Entry GetData_SetEcm");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdFaxECMMode = (env)->GetFieldID(cla, "m_u8FaxECMMode", "B");
	pSetEcm->m_u8FaxECMMode = (env)->GetByteField(*obj, fdFaxECMMode);

	LogInfo("Exit GetData_SetEcm");
}

void GetData_SetFaxBps(JNIEnv* env, Acs_SetFaxBps* pSetFaxBps, jobject* obj)
{
	LogInfo("Entry GetData_SetFaxBps");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdBps = (env)->GetFieldID(cla, "m_u8BPS", "B");
	pSetFaxBps->m_u8BPS = (env)->GetByteField(*obj, fdBps);

	LogInfo("Exit GetData_SetFaxBps");
}

void GetData_RtpAddr(JNIEnv* env, Acs_VoIP_RTPADDR* pRtpAddr, jobject* obj)
{
	LogInfo("Entry GetData_RtpAddr");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdAudio = env->GetFieldID(cla, "audio", "LDJKeygoe/ChAddr;");
	jobject  audioObj = env->GetObjectField(*obj, fdAudio);
	GetData_ChAddrAudio(env, &audioObj, pRtpAddr);

	jfieldID fdVideo = env->GetFieldID(cla, "video", "LDJKeygoe/ChAddr;");
	jobject  videoObj = env->GetObjectField(*obj, fdVideo);
	GetData_ChAddrVideo(env, &videoObj, pRtpAddr);

	LogInfo("Exit GetData_RtpAddr");
}

void GetData_RtpOpen(JNIEnv* env, Acs_VoIP_RTPOpen* pRtpOpen, jobject* obj)
{
	LogInfo("Entry GetData_RtpOpen");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdEnable = (env)->GetFieldID(cla, "m_u8Enable", "B");
	pRtpOpen->m_u8Enable = (env)->GetByteField(*obj, fdEnable);

	jfieldID fdPayloadDtmf = (env)->GetFieldID(cla, "m_u8PayloadDtmf", "B");
	pRtpOpen->m_u8PayloadDtmf = (env)->GetByteField(*obj, fdPayloadDtmf);

	jfieldID fdPayloadTone = (env)->GetFieldID(cla, "m_u8PayloadTone", "B");
	pRtpOpen->m_u8PayloadTone = (env)->GetByteField(*obj, fdPayloadTone);

	jfieldID fdAudio = env->GetFieldID(cla, "audio", "LDJKeygoe/ChMedia;");
	jobject  audioObj = env->GetObjectField(*obj, fdAudio);
	GetData_ChMediaAudio(env, &audioObj, pRtpOpen);

	jfieldID fdVideo = env->GetFieldID(cla, "video", "LDJKeygoe/ChMedia;");
	jobject  videoObj = env->GetObjectField(*obj, fdVideo);
	GetData_ChMediaVideo(env, &videoObj, pRtpOpen);

	LogInfo("Exit GetData_RtpOpen");
}

void GetData_TransAddHeader(JNIEnv* env, Acs_TransAddHeader* pTransAddHeader, jobject* obj)
{
	LogInfo("Entry GetData_TransAddHeader");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fd32Op = (env)->GetFieldID(cla, "m_u32Op", "I");
	pTransAddHeader->m_u32Op = env->GetIntField(*obj, fd32Op);

	jfieldID fdXPos = (env)->GetFieldID(cla, "m_u16XPos", "S");
	pTransAddHeader->m_u16XPos = env->GetShortField(*obj, fdXPos);

	jfieldID fdYPos = (env)->GetFieldID(cla, "m_u16YPos", "S");
	pTransAddHeader->m_u16YPos = env->GetShortField(*obj, fdYPos);

	jfieldID fdData = (env)->GetFieldID(cla, "m_u8Data", "[B");
	jbyteArray DataArr = (jbyteArray)(env->GetObjectField(*obj, fdData));
	GetByteArrayData(env, (byte*)pTransAddHeader->m_u8Data, &DataArr, 73);

	jfieldID fdRfu = (env)->GetFieldID(cla, "m_u8Rsrv", "B");
	pTransAddHeader->m_u8Rsrv = env->GetByteField(*obj, fdRfu);

	jfieldID fdFontSize = (env)->GetFieldID(cla, "m_u32FontSize", "I");
	pTransAddHeader->m_u32FontSize = env->GetIntField(*obj, fdFontSize);

	jfieldID fdHeader = (env)->GetFieldID(cla, "m_u32Header", "I");
	pTransAddHeader->m_u32Header = env->GetIntField(*obj, fdHeader);

	LogInfo("Exit GetData_TransAddHeader");
}

void GetData_BoardInfo(JNIEnv* env, Acs_ParamData_UserReadXmsBoardInfo* pBoardInfo, jobject* obj)
{
	LogInfo("Entry GetData_BoardInfo");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdMacAddr = (env)->GetFieldID(cla, "m_u8MacAddr", "[B");
	jbyteArray MacAddrArr = (jbyteArray)(env->GetObjectField(*obj, fdMacAddr));
	GetByteArrayData(env, pBoardInfo->m_u8MacAddr, &MacAddrArr, 6);

	jfieldID fdChassisType = (env)->GetFieldID(cla, "m_u8ChassisType", "B");
	pBoardInfo->m_u8ChassisType = (env)->GetByteField(*obj, fdChassisType);

	jfieldID fdChassisIndex = (env)->GetFieldID(cla, "m_u8ChassisIndex", "B");
	pBoardInfo->m_u8ChassisIndex = (env)->GetByteField(*obj, fdChassisIndex);

	jfieldID fdChassisSlot = (env)->GetFieldID(cla, "m_u8ChassisSlot", "B");
	pBoardInfo->m_u8ChassisSlot = (env)->GetByteField(*obj, fdChassisSlot);

	jfieldID fdSubBoardIndex = (env)->GetFieldID(cla, "m_u8SubBoardIndex", "B");
	pBoardInfo->m_u8SubBoardIndex = (env)->GetByteField(*obj, fdSubBoardIndex);

	jfieldID fdBoardType = (env)->GetFieldID(cla, "m_u8BoardType", "B");
	pBoardInfo->m_u8BoardType = (env)->GetByteField(*obj, fdBoardType);

	jfieldID fdrfu1 = (env)->GetFieldID(cla, "rfu1", "B");
	pBoardInfo->rfu1[0] = (env)->GetByteField(*obj, fdrfu1);

	jfieldID fdSystemName = (env)->GetFieldID(cla, "m_s8SystemName", "[B");
	jbyteArray SystemNameArr = (jbyteArray)(env->GetObjectField(*obj, fdSystemName));
	GetByteArrayData(env, (byte *)pBoardInfo->m_s8SystemName, &SystemNameArr, 32);

	jfieldID fdPlatformType = (env)->GetFieldID(cla, "m_s8PlatformType", "B");
	pBoardInfo->m_s8PlatformType = (env)->GetByteField(*obj, fdPlatformType);

	jfieldID fdUserCode = (env)->GetFieldID(cla, "m_s8UserCode", "[B");
	jbyteArray UserCodeArr = (jbyteArray)(env->GetObjectField(*obj, fdUserCode));
	GetByteArrayData(env, (byte *)pBoardInfo->m_s8UserCode, &UserCodeArr, 7);

	jfieldID fdSysId = (env)->GetFieldID(cla, "m_s32SysId", "I");
	pBoardInfo->m_s32SysId = (env)->GetIntField(*obj, fdSysId);

	jfieldID fdrfu2 = (env)->GetFieldID(cla, "rfu2", "[B");
	jbyteArray rfu2Arr = (jbyteArray)(env->GetObjectField(*obj, fdrfu2));
	GetByteArrayData(env, (byte *)pBoardInfo->rfu2, &rfu2Arr, 20);

	jfieldID fdFirmwareName = (env)->GetFieldID(cla, "m_s8FirmwareName", "[B");
	jbyteArray FirmwareNameArr = (jbyteArray)(env->GetObjectField(*obj, fdFirmwareName));
	GetByteArrayData(env, (byte *)pBoardInfo->m_s8FirmwareName, &FirmwareNameArr, 8);

	jfieldID fdFirmwareVersion = (env)->GetFieldID(cla, "m_s8FirmwareVersion", "[B");
	jbyteArray FirmwareVersionArr = (jbyteArray)(env->GetObjectField(*obj, fdFirmwareVersion));
	GetByteArrayData(env, (byte *)pBoardInfo->m_s8FirmwareVersion, &FirmwareVersionArr, 8);

	jfieldID fdRevisionDate = (env)->GetFieldID(cla, "m_s8RevisionDate", "[B");
	jbyteArray RevisionDateArr = (jbyteArray)(env->GetObjectField(*obj, fdRevisionDate));
	GetByteArrayData(env, (byte *)pBoardInfo->m_s8RevisionDate, &RevisionDateArr, 8);

	LogInfo("Exit GetData_BoardInfo");
}

void GetData_ReadVoltage(JNIEnv* env, CmdParamData_ReadVoltage_t* pReadVoltage, jobject* obj)
{
	LogInfo("Entry GetData_ReadVoltage");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdReadFlag = (env)->GetFieldID(cla, "fdReadFlag", "B");
	pReadVoltage->m_u8ReadFlag = (env)->GetByteField(*obj, fdReadFlag);

	jfieldID fdReserved1 = (env)->GetFieldID(cla, "m_s8Reserved1", "[B");
	jbyteArray ReservedArr = (jbyteArray)(env->GetObjectField(*obj, fdReserved1));
	GetByteArrayData(env, (byte*)pReadVoltage->m_s8Reserved1, &ReservedArr, 3);

	jfieldID fdTimeSpan = (env)->GetFieldID(cla, "m_u32TimeSpan", "I");
	pReadVoltage->m_u32TimeSpan = (env)->GetIntField(*obj, fdTimeSpan);

	jfieldID fdVoltage = (env)->GetFieldID(cla, "m_s8Voltage", "B");
	pReadVoltage->m_s8Voltage = (env)->GetByteField(*obj, fdVoltage);

	jfieldID fdReserved2 = (env)->GetFieldID(cla, "m_u8Reserved2", "[B");
	jbyteArray Reserved2Arr = (jbyteArray)(env->GetObjectField(*obj, fdReserved2));
	GetByteArrayData(env, (byte*)pReadVoltage->m_u8Reserved2, &Reserved2Arr, 3);

	LogInfo("Exit GetData_ReadVoltage");
}

void GetData_3GppCfg(JNIEnv * env, Get3gppCfg_t * _3GppCfg, jobject * obj)
{
	LogInfo("Entry GetData_3GppCfg");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdMediaType = (env)->GetFieldID(cla, "m_u8MediaType", "B");
	_3GppCfg->m_u8MediaType = (env)->GetByteField(*obj, fdMediaType);

	jfieldID fdAudioFileType = (env)->GetFieldID(cla, "m_u8AudioFileType", "B");
	_3GppCfg->m_u8AudioFileType = (env)->GetByteField(*obj, fdAudioFileType);

	jfieldID fdAudioFileIndex = (env)->GetFieldID(cla, "m_u16AudioFileIndex", "S");
	_3GppCfg->m_u16AudioFileIndex = (env)->GetShortField(*obj, fdAudioFileIndex);

	jfieldID fdAudioFileName = (env)->GetFieldID(cla, "m_s8AudioFileName", "[B");
	jbyteArray AudioFileNameArr = (jbyteArray)(env->GetObjectField(*obj, fdAudioFileName));
	GetByteArrayData(env, (byte*)_3GppCfg->m_s8AudioFileName, &AudioFileNameArr, 260);

	jfieldID fdVideoFileType = (env)->GetFieldID(cla, "m_u8VideoFileType", "B");
	_3GppCfg->m_u8VideoFileType = (env)->GetByteField(*obj, fdVideoFileType);

	jfieldID fdRfu1 = (env)->GetFieldID(cla, "m_u8Rfu1", "B");
	_3GppCfg->m_u8Rfu1 = (env)->GetByteField(*obj, fdRfu1);

	jfieldID fdVideoFileIndex = (env)->GetFieldID(cla, "m_u16VideoFileIndex", "S");
	_3GppCfg->m_u16VideoFileIndex = (env)->GetShortField(*obj, fdVideoFileIndex);

	jfieldID fdVideoFileName = (env)->GetFieldID(cla, "m_s8VideoFileName", "[B");
	jbyteArray VideoFileNameArr = (jbyteArray)(env->GetObjectField(*obj, fdVideoFileName));
	GetByteArrayData(env, (byte*)_3GppCfg->m_s8VideoFileName, &VideoFileNameArr, 260);

	LogInfo("Exit GetData_3GppCfg");
}

void GetData_RecordCsp(JNIEnv * env, jobject * obj, RecordCSPProperty_t* recordCsp)
{
	LogInfo("Entry GetData_RecordCsp");

	jclass cla = env->GetObjectClass(*obj);
	
	jfieldID fdEncodeType = (env)->GetFieldID(cla, "m_u8EncodeType", "B");
	recordCsp->m_u8EncodeType = (env)->GetByteField(*obj, fdEncodeType);

	jfieldID fdSRCMode = (env)->GetFieldID(cla, "m_u8SRCMode", "B");
	recordCsp->m_u8SRCMode = (env)->GetByteField(*obj, fdSRCMode);

	jfieldID fdPacketLen = (env)->GetFieldID(cla, "m_u16PacketLen", "S");
	recordCsp->m_u16PacketLen = (env)->GetShortField(*obj, fdPacketLen);

	jfieldID fdCSPRecType = (env)->GetFieldID(cla, "m_u8CSPRecType", "B");
	recordCsp->m_u8CSPRecType = (env)->GetByteField(*obj, fdCSPRecType);

	jfieldID fdStopMode = (env)->GetFieldID(cla, "m_u8StopMode", "B");
	recordCsp->m_u8StopMode = (env)->GetByteField(*obj, fdStopMode);

	jfieldID fdStopCode = (env)->GetFieldID(cla, "m_u8StopCode", "B");
	recordCsp->m_u8StopCode = (env)->GetByteField(*obj, fdStopCode);

	jfieldID fdIsMix = (env)->GetFieldID(cla, "m_s8IsMixEnable", "B");
	recordCsp->m_s8IsMixEnable = (env)->GetByteField(*obj, fdIsMix);

	jfieldID fdMixerControl = env->GetFieldID(cla, "m_MixerControl", "LDJKeygoe/MixerControlParam_t;");
	jobject  MixerControlObj = env->GetObjectField(*obj, fdMixerControl);
	GetData_MixerControlParam(env, &MixerControlObj, &recordCsp->m_MixerControl);

	jfieldID fdIsVAD = (env)->GetFieldID(cla, "m_u8IsVADEnable", "B");
	recordCsp->m_u8IsVADEnable = (env)->GetByteField(*obj, fdIsVAD);

	jfieldID fdRfu = (env)->GetFieldID(cla, "m_s8Rfu1", "[B");
	jbyteArray RfuArr = (jbyteArray)(env->GetObjectField(*obj, fdRfu));
	GetByteArrayData(env, (byte*)recordCsp->m_s8Rfu1, &RfuArr, 3);

	LogInfo("Exit GetData_RecordCsp");
}

void GetData_OutPutA(JNIEnv * env, jobject * obj, Acs_MediaEx_Output_A* audio)
{
	LogInfo("Entry GetData_OutPutA");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdIP = (env)->GetFieldID(cla, "m_s8IP", "[B");
	jbyteArray IPArr = (jbyteArray)(env->GetObjectField(*obj, fdIP));
	GetByteArrayData(env, (byte*)audio->m_s8IP, &IPArr, 20);

	jfieldID fdPort = (env)->GetFieldID(cla, "m_u16Port", "S");
	audio->m_u16Port = (env)->GetShortField(*obj, fdPort);

	jfieldID fdCodec = (env)->GetFieldID(cla, "m_u8Codec", "B");
	audio->m_u8Codec = (env)->GetByteField(*obj, fdCodec);

	jfieldID fdPayloadType = (env)->GetFieldID(cla, "m_u8PayloadType", "B");
	audio->m_u8PayloadType = (env)->GetByteField(*obj, fdPayloadType);

	LogInfo("Exit GetData_OutPutA");
}

void GetData_InPutV(JNIEnv * env, jobject * obj, Acs_MediaEx_Input_V* video)
{
	LogInfo("Entry GetData_InPutV");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdPort = (env)->GetFieldID(cla, "m_u16Port", "S");
	video->m_u16Port = (env)->GetShortField(*obj, fdPort);

	jfieldID fdCodec = (env)->GetFieldID(cla, "m_u8Codec", "B");
	video->m_u8Codec = (env)->GetByteField(*obj, fdCodec);

	jfieldID fdPayloadType = (env)->GetFieldID(cla, "m_u8PayloadType", "B");
	video->m_u8PayloadType = (env)->GetByteField(*obj, fdPayloadType);

	jfieldID fdProfileLevelId = (env)->GetFieldID(cla, "m_u32ProfileLevelId", "S");
	video->m_u32ProfileLevelId = (env)->GetShortField(*obj, fdProfileLevelId);

	jfieldID fddecoderConfigLength = (env)->GetFieldID(cla, "decoderConfigLength", "S");
	video->decoderConfigLength = (env)->GetShortField(*obj, fddecoderConfigLength);

	jfieldID fddecoderConfigInfo = (env)->GetFieldID(cla, "decoderConfigInfo", "[B");
	jbyteArray decoderConfigInfoArr = (jbyteArray)(env->GetObjectField(*obj, fddecoderConfigInfo));
	GetByteArrayData(env, video->decoderConfigInfo, &decoderConfigInfoArr, 128);

	LogInfo("Exit GetData_InPutV");
}

void GetData_ChAddrAudio	  (JNIEnv* env, jobject* obj, Acs_VoIP_RTPADDR* pRtpAddr)
{
	LogInfo("Entry GetData_ChAddrAudio");
	
	jclass cla = env->GetObjectClass(*obj);
	
	jfieldID fdEnable = (env)->GetFieldID(cla, "m_u8Enable", "B");
	pRtpAddr->audio.m_u8Enable = (env)->GetByteField(*obj, fdEnable);
	
	jfieldID fdIP = (env)->GetFieldID(cla, "m_s8IP", "[B");
	jbyteArray IPArr = (jbyteArray)(env->GetObjectField(*obj, fdIP));
	GetByteArrayData(env, (byte*)pRtpAddr->audio.m_s8IP, &IPArr, 20);
	
	jfieldID fdPort = (env)->GetFieldID(cla, "m_u16Port", "S");
	pRtpAddr->audio.m_u16Port = (env)->GetShortField(*obj, fdPort);
	
	LogInfo("Exit GetData_ChAddrAudio");
}

void GetData_ChAddrVideo	  (JNIEnv* env, jobject* obj, Acs_VoIP_RTPADDR* pRtpAddr)
{
	LogInfo("Entry GetData_ChAddrVideo");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdEnable = (env)->GetFieldID(cla, "m_u8Enable", "B");
	pRtpAddr->video.m_u8Enable = (env)->GetByteField(*obj, fdEnable);
	
	jfieldID fdIP = (env)->GetFieldID(cla, "m_s8IP", "[B");
	jbyteArray IPArr = (jbyteArray)(env->GetObjectField(*obj, fdIP));
	GetByteArrayData(env, (byte*)pRtpAddr->video.m_s8IP, &IPArr, 20);
	
	jfieldID fdPort = (env)->GetFieldID(cla, "m_u16Port", "S");
	pRtpAddr->video.m_u16Port = (env)->GetShortField(*obj, fdPort);

	LogInfo("Exit GetData_ChAddrVideo");
}

void GetData_ChCodecAudio	  (JNIEnv* env, jobject* obj, Acs_VoIP_RTPCODEC* pRtpCodec)
{
	LogInfo("Entry GetData_ChCodecAudio");
	
	jclass cla = env->GetObjectClass(*obj);
	
	jfieldID fdEnable = (env)->GetFieldID(cla, "m_u8Enable", "B");
	pRtpCodec->audio.m_u8Enable = (env)->GetByteField(*obj, fdEnable);
	
	jfieldID fdTxCodec = (env)->GetFieldID(cla, "m_u8TxCodec", "B");
	pRtpCodec->audio.m_u8TxCodec = (env)->GetByteField(*obj, fdTxCodec);
	
	jfieldID fdTxPayloadType = (env)->GetFieldID(cla, "m_u8TxPayloadType", "B");
	pRtpCodec->audio.m_u8TxPayloadType = (env)->GetByteField(*obj, fdTxPayloadType);
	
	jfieldID fdRxCodec = (env)->GetFieldID(cla, "m_u8RxCodec", "B");
	pRtpCodec->audio.m_u8RxCodec = (env)->GetByteField(*obj, fdRxCodec);
	
	jfieldID fdRxPayloadType = (env)->GetFieldID(cla, "m_u8RxPayloadType", "B");
	pRtpCodec->audio.m_u8RxPayloadType = (env)->GetByteField(*obj, fdRxPayloadType);
	
	LogInfo("Exit GetData_ChCodecAudio");
}

void GetData_ChCodecVideo	  (JNIEnv* env, jobject* obj, Acs_VoIP_RTPCODEC* pRtpCodec)
{
	LogInfo("Entry GetData_ChCodecVideo");

	jclass cla = env->GetObjectClass(*obj);
	
	jfieldID fdEnable = (env)->GetFieldID(cla, "m_u8Enable", "B");
	pRtpCodec->video.m_u8Enable = (env)->GetByteField(*obj, fdEnable);

	jfieldID fdTxCodec = (env)->GetFieldID(cla, "m_u8TxCodec", "B");
	pRtpCodec->video.m_u8TxCodec = (env)->GetByteField(*obj, fdTxCodec);

	jfieldID fdTxPayloadType = (env)->GetFieldID(cla, "m_u8TxPayloadType", "B");
	pRtpCodec->video.m_u8TxPayloadType = (env)->GetByteField(*obj, fdTxPayloadType);

	jfieldID fdRxCodec = (env)->GetFieldID(cla, "m_u8RxCodec", "B");
	pRtpCodec->video.m_u8RxCodec = (env)->GetByteField(*obj, fdRxCodec);

	jfieldID fdRxPayloadType = (env)->GetFieldID(cla, "m_u8RxPayloadType", "B");
	pRtpCodec->video.m_u8RxPayloadType = (env)->GetByteField(*obj, fdRxPayloadType);

	LogInfo("Exit GetData_ChCodecVideo");
}

void GetData_ChMediaAudio(JNIEnv* env, jobject* obj, Acs_VoIP_RTPOpen* pMedia)
{
	LogInfo("Entry GetData_ChMediaAudio");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdEnable = (env)->GetFieldID(cla, "m_u8Enable", "B");
	pMedia->audio.m_u8Enable = (env)->GetByteField(*obj, fdEnable);

	jfieldID fdIP = (env)->GetFieldID(cla, "m_s8IP", "[B");
	jbyteArray IPArr = (jbyteArray)(env->GetObjectField(*obj, fdIP));
	GetByteArrayData(env, (byte*)pMedia->audio.m_s8IP, &IPArr, 20);

	jfieldID fdPort = (env)->GetFieldID(cla, "m_u16Port", "S");
	pMedia->audio.m_u16Port = (env)->GetShortField(*obj, fdPort);

	jfieldID fdTxCodec = (env)->GetFieldID(cla, "m_u8TxCodec", "B");
	pMedia->audio.m_u8TxCodec = (env)->GetByteField(*obj, fdTxCodec);

	jfieldID fdTxPayloadType = (env)->GetFieldID(cla, "m_u8TxPayloadType", "B");
	pMedia->audio.m_u8TxPayloadType = (env)->GetByteField(*obj, fdTxPayloadType);

	jfieldID fdRxCodec = (env)->GetFieldID(cla, "m_u8RxCodec", "B");
	pMedia->audio.m_u8RxCodec = (env)->GetByteField(*obj, fdRxCodec);

	jfieldID fdRxPayloadType = (env)->GetFieldID(cla, "m_u8RxPayloadType", "B");
	pMedia->audio.m_u8RxPayloadType = (env)->GetByteField(*obj, fdRxPayloadType);

	LogInfo("Exit GetData_ChMediaAudio");
}

void GetData_ChMediaVideo	  (JNIEnv* env, jobject* obj, Acs_VoIP_RTPOpen* pMedia)
{
	LogInfo("Entry GetData_ChMediaVideo");

	jclass cla = env->GetObjectClass(*obj);
	
	jfieldID fdEnable = (env)->GetFieldID(cla, "m_u8Enable", "B");
	pMedia->video.m_u8Enable = (env)->GetByteField(*obj, fdEnable);
	
	jfieldID fdIP = (env)->GetFieldID(cla, "m_s8IP", "[B");
	jbyteArray IPArr = (jbyteArray)(env->GetObjectField(*obj, fdIP));
	GetByteArrayData(env, (byte*)pMedia->video.m_s8IP, &IPArr, 20);
	
	jfieldID fdPort = (env)->GetFieldID(cla, "m_u16Port", "S");
	pMedia->video.m_u16Port = (env)->GetShortField(*obj, fdPort);
	
	jfieldID fdTxCodec = (env)->GetFieldID(cla, "m_u8TxCodec", "B");
	pMedia->video.m_u8TxCodec = (env)->GetByteField(*obj, fdTxCodec);
	
	jfieldID fdTxPayloadType = (env)->GetFieldID(cla, "m_u8TxPayloadType", "B");
	pMedia->video.m_u8TxPayloadType = (env)->GetByteField(*obj, fdTxPayloadType);
	
	jfieldID fdRxCodec = (env)->GetFieldID(cla, "m_u8RxCodec", "B");
	pMedia->video.m_u8RxCodec = (env)->GetByteField(*obj, fdRxCodec);
	
	jfieldID fdRxPayloadType = (env)->GetFieldID(cla, "m_u8RxPayloadType", "B");
	pMedia->video.m_u8RxPayloadType = (env)->GetByteField(*obj, fdRxPayloadType);

	LogInfo("Exit GetData_ChMediaVideo");
}

void GetData_OutPutV(JNIEnv * env, jobject * obj, Acs_MediaEx_Output_V* video)
{
	LogInfo("Entry GetData_OutPutV");

	jclass cla = env->GetObjectClass(*obj);
	
	jfieldID fdIP = (env)->GetFieldID(cla, "m_s8IP", "[B");
	jbyteArray IPArr = (jbyteArray)(env->GetObjectField(*obj, fdIP));
	GetByteArrayData(env, (byte*)video->m_s8IP, &IPArr, 20);
	
	jfieldID fdPort = (env)->GetFieldID(cla, "m_u16Port", "S");
	video->m_u16Port = (env)->GetShortField(*obj, fdPort);
	
	jfieldID fdCodec = (env)->GetFieldID(cla, "m_u8Codec", "B");
	video->m_u8Codec = (env)->GetByteField(*obj, fdCodec);
	
	jfieldID fdPayloadType = (env)->GetFieldID(cla, "m_u8PayloadType", "B");
	video->m_u8PayloadType = (env)->GetByteField(*obj, fdPayloadType);

	jfieldID fdResX = (env)->GetFieldID(cla, "m_u16ResX", "S");
	video->m_u16ResX = (env)->GetShortField(*obj, fdResX);

	jfieldID fdResY = (env)->GetFieldID(cla, "m_u16ResY", "S");
	video->m_u16ResY = (env)->GetShortField(*obj, fdResY);

	jfieldID fdFps = (env)->GetFieldID(cla, "m_u8Fps", "B");
	video->m_u8Fps = (env)->GetByteField(*obj, fdFps);

	jfieldID fdKbps = (env)->GetFieldID(cla, "m_u16Kbps", "S");
	video->m_u16Kbps = (env)->GetShortField(*obj, fdKbps);

	LogInfo("Exit GetData_OutPutV");
}

void GetData_LayOutList		  (JNIEnv * env, jobject * obj, Acs_3GVConf_LayoutList* layOutList)
{
	LogInfo("Entry GetData_LayOutList");

	jclass cla  = env->GetObjectClass(*obj);

	jfieldID fdDevice = env->GetFieldID(cla, "m_device", "[LDJKeygoe/DeviceID_t;");
	jobjectArray  DeviceArr = (jobjectArray)(env->GetObjectField(*obj, fdDevice));

	for (int i = 0; i < 16; i++)
	{
		jobject obj = env->GetObjectArrayElement(DeviceArr, i);
		GetData_DeviceID(env, &obj, layOutList->m_device+i);
	}

	LogInfo("Exit GetData_LayOutList");
}

void GetData_UserLedCtrl	  (JNIEnv * env, jobject * obj, UserLedCtrl* userLedCtrl)
{
	LogInfo("Entry GetData_UserLedCtrl");

	jclass cla  = env->GetObjectClass(*obj);

	jfieldID fdLedTimeEnable = (env)->GetFieldID(cla, "m_u8LedTimeEnable", "B");
	userLedCtrl->m_u8LedTimeEnable = (env)->GetByteField(*obj, fdLedTimeEnable);

	jfieldID fdRfu = (env)->GetFieldID(cla, "m_Rfu1", "B");
	userLedCtrl->m_Rfu1 = (env)->GetByteField(*obj, fdRfu);

	jfieldID fdOnTime = (env)->GetFieldID(cla, "m_u16OnTime", "S");
	userLedCtrl->m_u16OnTime = (env)->GetShortField(*obj, fdOnTime);

	jfieldID fdOffTime = (env)->GetFieldID(cla, "m_u16OffTime", "S");
	userLedCtrl->m_u16OffTime = (env)->GetShortField(*obj, fdOffTime);

	jfieldID fdWatchDogOutEnbale = (env)->GetFieldID(cla, "m_u8WatchDogOutEnbale", "B");
	userLedCtrl->m_u8WatchDogOutEnbale = (env)->GetByteField(*obj, fdWatchDogOutEnbale);

	jfieldID fdRfu2 = (env)->GetFieldID(cla, "m_Rfu2", "B");
	userLedCtrl->m_Rfu2 = (env)->GetByteField(*obj, fdRfu2);

	jfieldID fdWatchDogOutTime = (env)->GetFieldID(cla, "m_u16WatchDogOutTime", "S");
	userLedCtrl->m_u16WatchDogOutTime = (env)->GetShortField(*obj, fdWatchDogOutTime);

	jfieldID fdWatchDogTimeEnable = (env)->GetFieldID(cla, "m_u8WatchDogTimeEnable", "B");
	userLedCtrl->m_u8WatchDogTimeEnable = (env)->GetByteField(*obj, fdWatchDogTimeEnable);

	jfieldID fdRfu3 = (env)->GetFieldID(cla, "m_Rfu3", "B");
	userLedCtrl->m_Rfu3 = (env)->GetByteField(*obj, fdRfu3);

	jfieldID fdWatchDogOnTime = (env)->GetFieldID(cla, "m_u16WatchDogOnTime", "S");
	userLedCtrl->m_u16WatchDogOnTime = (env)->GetShortField(*obj, fdWatchDogOnTime);

	jfieldID fdWatchDogOffTime = (env)->GetFieldID(cla, "m_u16WatchDogOffTime", "S");
	userLedCtrl->m_u16WatchDogOffTime = (env)->GetShortField(*obj, fdWatchDogOffTime);

	jfieldID fdFeedWatchDogEnable = (env)->GetFieldID(cla, "m_u8FeedWatchDogEnable", "B");
	userLedCtrl->m_u8FeedWatchDogEnable = (env)->GetByteField(*obj, fdFeedWatchDogEnable);

	jfieldID fdRfu4 = (env)->GetFieldID(cla, "m_Rfu4", "[B");
	jbyteArray Rfu4Arr = (jbyteArray)(env->GetObjectField(*obj, fdRfu4));
	GetByteArrayData(env, (byte*)userLedCtrl->m_Rfu4, &Rfu4Arr, 3);

	LogInfo("Exit GetData_UserLedCtrl");
}

void GetData_ParamItem		  (JNIEnv * env, jobject * obj, PutTextInPicture_Param* paramItem)
{
	LogInfo("Entry GetData_ParamItem");

	jclass cla  = env->GetObjectClass(*obj);

	jfieldID fdPutByType = (env)->GetFieldID(cla, "m_u8PutByType", "B");
	paramItem->m_u8PutByType = (env)->GetByteField(*obj, fdPutByType);

	jfieldID fdPutByLevel = (env)->GetFieldID(cla, "m_u8PutByLevel", "B");
	paramItem->m_u8PutByLevel = (env)->GetByteField(*obj, fdPutByLevel);

	jfieldID fdPutText = (env)->GetFieldID(cla, "m_s8PutText", "[B");
	jbyteArray PutTextArr = (jbyteArray)(env->GetObjectField(*obj, fdPutText));
	GetByteArrayData(env, (byte*)paramItem->m_s8PutText, &PutTextArr, 260);

	jfieldID fdFontType = (env)->GetFieldID(cla, "m_u16FontType", "S");
	paramItem->m_u16FontType = (env)->GetShortField(*obj, fdFontType);

	jfieldID fdDiaphaneity = (env)->GetFieldID(cla, "m_f32Diaphaneity", "F");
	paramItem->m_f32Diaphaneity = (env)->GetFloatField(*obj, fdDiaphaneity);

	jfieldID fdFontParam = env->GetFieldID(cla, "m_structFontParam", "LDJKeygoe/FontParam;");
	jobject  FontParamObj = env->GetObjectField(*obj, fdFontParam);
	jclass fontCla  = env->GetObjectClass(FontParamObj);
	
	jfieldID fdDBSize = (env)->GetFieldID(fontCla, "m_f64DBSize", "D");
	paramItem->structFontParam.m_f64DBSize = (env)->GetDoubleField(FontParamObj, fdDBSize);
	
	jfieldID fdDBBlank = (env)->GetFieldID(fontCla, "m_f64DBBlank", "D");
	paramItem->structFontParam.m_f64DBBlank = (env)->GetDoubleField(FontParamObj, fdDBBlank);
	
	jfieldID fdDBGap = (env)->GetFieldID(fontCla, "m_f64DBGap", "D");
	paramItem->structFontParam.m_f64DBGap = (env)->GetDoubleField(FontParamObj, fdDBGap);
	
	jfieldID fdDBAngle = (env)->GetFieldID(fontCla, "m_f64DBAngle", "D");
	paramItem->structFontParam.m_f64DBAngle = (env)->GetDoubleField(FontParamObj, fdDBAngle);
	
	jfieldID fdUnderLine = (env)->GetFieldID(fontCla, "m_bUnderLine", "I");
	paramItem->structFontParam.m_bUnderLine = (env)->GetIntField(FontParamObj, fdUnderLine);
	
	jfieldID fdColor = env->GetFieldID(fontCla, "m_strcutColor", "LDJKeygoe/Color;");
	jobject  ColorObj = env->GetObjectField(FontParamObj, fdColor);
	jclass   ColorCla = env->GetObjectClass(ColorObj);

	jfieldID fdColorR = (env)->GetFieldID(ColorCla, "m_u8R", "B");
	paramItem->structFontParam.strcutColor.m_u8R = (env)->GetByteField(ColorObj, fdColorR);

	jfieldID fdColorG = (env)->GetFieldID(ColorCla, "m_u8G", "B");
	paramItem->structFontParam.strcutColor.m_u8G = (env)->GetByteField(ColorObj, fdColorG);

	jfieldID fdColorB = (env)->GetFieldID(ColorCla, "m_u8B", "B");
	paramItem->structFontParam.strcutColor.m_u8B = (env)->GetByteField(ColorObj, fdColorB);

	jfieldID fdPoint = env->GetFieldID(cla, "m_structPoint", "LDJKeygoe/Point;");
	jobject  PointObj = env->GetObjectField(*obj, fdPoint);
	jclass	 PointCla = env->GetObjectClass(PointObj);
	
	jfieldID fdPointX = (env)->GetFieldID(PointCla, "m_x", "I");
	paramItem->structPoint.x = (env)->GetIntField(PointObj, fdPointX);

	jfieldID fdPointY = (env)->GetFieldID(PointCla, "m_y", "I");
	paramItem->structPoint.y = (env)->GetIntField(PointObj, fdPointY);
	
	LogInfo("Exit GetData_ParamItem");
}

void GetData_VisibleList	  (JNIEnv * env , jobject * obj, Acs_3GVConf_VisibleList* visiableList)
{
	LogInfo("Entry GetData_VisibleList");

	jclass cla  = env->GetObjectClass(*obj);

	jfieldID fdDevice = env->GetFieldID(cla, "m_device", "[LDJKeygoe/DeviceID_t;");
	jobjectArray  DeviceArr = (jobjectArray)(env->GetObjectField(*obj, fdDevice));

	for (int i = 0; i < 16; i++)
	{
		jobject Obj = env->GetObjectArrayElement(DeviceArr, i);
		GetData_DeviceID(env, &Obj, visiableList->m_device+i);
	}

	LogInfo("Exit GetData_VisibleList");
}

void GetData_Ctrl3GppRecord (JNIEnv * env, jobject * obj, Control3gppRecord_t* ctrl3GppRecord)
{
	LogInfo("Entry GetData_Ctrl3GppRecord");

	jclass cla  = env->GetObjectClass(*obj);

	jfieldID fdCtrlType = (env)->GetFieldID(cla, "m_u32ControlType", "S");
	ctrl3GppRecord->m_u32ControlType = (env)->GetShortField(*obj, fdCtrlType);

	jfieldID fdMediaType = (env)->GetFieldID(cla, "m_u8MediaType", "B");
	ctrl3GppRecord->m_u8MediaType = (env)->GetByteField(*obj, fdMediaType);

	jfieldID fdReserv1 = (env)->GetFieldID(cla, "m_u8Reserv1", "B");
	ctrl3GppRecord->m_u8Reserv1 = (env)->GetByteField(*obj, fdReserv1);
	
	jfieldID fdStepTime = (env)->GetFieldID(cla, "m_u32StepTime", "I");
	ctrl3GppRecord->m_u32StepTime = (env)->GetIntField(*obj, fdStepTime);

	jfieldID fdSpeedSize = (env)->GetFieldID(cla, "m_u32SpeedSize", "I");
	ctrl3GppRecord->m_u32SpeedSize = (env)->GetIntField(*obj, fdSpeedSize);

	LogInfo("Exit GetData_Ctrl3GppRecord");
}

void GetData_MediaRecord (JNIEnv * env, jobject * obj, Acs_MediaEx_Record* mediaRecord)
{
	LogInfo("Entry GetData_MediaRecord");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fieldPrivate = env->GetFieldID(cla, "m_PrivateData", "LDJKeygoe/PrivateData_t;");
	jobject  objPrivate = env->GetObjectField(*obj, fieldPrivate);
	GetData_Private(env, &objPrivate, &mediaRecord->m_PrivateData);

	jfieldID fdDstName = (env)->GetFieldID(cla, "m_s8DstName", "[B");
	jbyteArray DstNameArr = (jbyteArray)(env->GetObjectField(*obj, fdDstName));
	GetByteArrayData(env, (byte *)mediaRecord->m_s8DstName, &DstNameArr, 128);

	jfieldID fdAudio = env->GetFieldID(cla, "audio", "LDJKeygoe/Acs_MediaEx_Output_A;");
	jobject  audioObj = env->GetObjectField(*obj, fdAudio);
	GetData_OutPutA(env, &audioObj, &mediaRecord->audio);

	jfieldID fdVideo = env->GetFieldID(cla, "video", "LDJKeygoe/Acs_MediaEx_Output_V;");
	jobject  VideoObj = env->GetObjectField(*obj, fdVideo);
	GetData_OutPutV(env, &VideoObj, &mediaRecord->video);

	LogInfo("Exit GetData_MediaRecord");
}

void GetData_Record3Gpp (JNIEnv * env, jobject * obj, Record3gppProperty_t* record3Gpp)
{
	LogInfo("Entry GetData_Record3Gpp");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdMaxTime = (env)->GetFieldID(cla, "m_u32MaxTime", "I");
	record3Gpp->m_u32MaxTime = (env)->GetIntField(*obj, fdMaxTime);

	jfieldID fdStopMode = (env)->GetFieldID(cla, "m_u8StopMode", "B");
	record3Gpp->m_u8StopMode = (env)->GetByteField(*obj, fdStopMode);

	jfieldID fdStopCode = (env)->GetFieldID(cla, "m_u8StopCode", "B");
	record3Gpp->m_u8StopCode = (env)->GetByteField(*obj, fdStopCode);

	jfieldID fdIsAppend = (env)->GetFieldID(cla, "m_s8IsAppend", "B");
	record3Gpp->m_s8IsAppend = (env)->GetByteField(*obj, fdIsAppend);

	jfieldID fdAudioEncodeType = (env)->GetFieldID(cla, "m_u8AudioEncodeType", "B");
	record3Gpp->m_u8AudioEncodeType = (env)->GetByteField(*obj, fdAudioEncodeType);

	jfieldID fdAudioSRCMode = (env)->GetFieldID(cla, "m_u8AudioSRCMode", "B");
	record3Gpp->m_u8AudioSRCMode = (env)->GetByteField(*obj, fdAudioSRCMode);

	jfieldID fdAudioTracks = (env)->GetFieldID(cla, "m_u8AudioTracks", "B");
	record3Gpp->m_u8AudioTracks = (env)->GetByteField(*obj, fdAudioTracks);

	jfieldID fdAudioMaxBitRate = (env)->GetFieldID(cla, "m_u16AudioMaxBitRate", "S");
	record3Gpp->m_u16AudioMaxBitRate = (env)->GetShortField(*obj, fdAudioMaxBitRate);

	jfieldID fdAudioAverageBitRate = (env)->GetFieldID(cla, "m_u16AudioAverageBitRate", "S");
	record3Gpp->m_u16AudioAverageBitRate = (env)->GetShortField(*obj, fdAudioAverageBitRate);

	jfieldID fdMediaType = (env)->GetFieldID(cla, "m_u8MediaType", "B");
	record3Gpp->m_u8MediaType = (env)->GetByteField(*obj, fdMediaType);

	jfieldID fdAudioIsMixEnable = (env)->GetFieldID(cla, "m_s8AudioIsMixEnable", "B");
	record3Gpp->m_s8AudioIsMixEnable = (env)->GetByteField(*obj, fdAudioIsMixEnable);

	jfieldID fdMixerControl = env->GetFieldID(cla, "m_AudioMixerControl", "LDJKeygoe/MixerControlParam_t;");
	jobject  MixerControlObj = env->GetObjectField(*obj, fdMixerControl);
	GetData_MixerControlParam(env, &MixerControlObj, &record3Gpp->m_AudioMixerControl);

	jfieldID fdVideoEncodeType = (env)->GetFieldID(cla, "m_u8VideoEncodeType", "B");
	record3Gpp->m_u8VideoEncodeType = (env)->GetByteField(*obj, fdVideoEncodeType);

	jfieldID fdVideoFrameRate = (env)->GetFieldID(cla, "m_u8VideoFrameRate", "B");
	record3Gpp->m_u8VideoFrameRate = (env)->GetByteField(*obj, fdVideoFrameRate);

	jfieldID fdVideoWidth = (env)->GetFieldID(cla, "m_u16VideoWidth", "S");
	record3Gpp->m_u16VideoWidth = (env)->GetShortField(*obj, fdVideoWidth);

	jfieldID fdVideoHeight = (env)->GetFieldID(cla, "m_u16VideoHeight", "S");
	record3Gpp->m_u16VideoHeight = (env)->GetShortField(*obj, fdVideoHeight);

	jfieldID fdVideoMaxBitRate = (env)->GetFieldID(cla, "m_u16VideoMaxBitRate", "S");
	record3Gpp->m_u16VideoMaxBitRate = (env)->GetShortField(*obj, fdVideoMaxBitRate);

	jfieldID fdVideoAverageBitRate = (env)->GetFieldID(cla, "m_u16VideoAverageBitRate", "S");
	record3Gpp->m_u16VideoAverageBitRate = (env)->GetShortField(*obj, fdVideoAverageBitRate);

	jfieldID fdRfu2 = (env)->GetFieldID(cla, "m_Rfu2", "B");
	record3Gpp->m_Rfu2 = (env)->GetByteField(*obj, fdRfu2);

	jfieldID fdVideoIsMixEnable = (env)->GetFieldID(cla, "m_s8VideoIsMixEnable", "B");
	record3Gpp->m_s8VideoIsMixEnable = (env)->GetByteField(*obj, fdVideoIsMixEnable);

	jfieldID fdVideoMixerControl = env->GetFieldID(cla, "m_VideoMixerControl", "LDJKeygoe/MixerControlParam_t;");
	jobject  videoMixerControlObj = env->GetObjectField(*obj, fdVideoMixerControl);
	GetData_MixerControlParam(env, &videoMixerControlObj, &record3Gpp->m_VideoMixerControl);

	jfieldID fdAudioProfiles = (env)->GetFieldID(cla, "m_u8AudioProfiles", "B");
	record3Gpp->m_u8AudioProfiles = (env)->GetByteField(*obj, fdAudioProfiles);

	jfieldID fdAudioLevel = (env)->GetFieldID(cla, "m_u8AudioLevel", "B");
	record3Gpp->m_u8AudioLevel = (env)->GetByteField(*obj, fdAudioLevel);

	jfieldID fdAudioDecoderCfgLen = (env)->GetFieldID(cla, "m_u16AudioDecoderCfgLen", "S");
	record3Gpp->m_u16AudioDecoderCfgLen = (env)->GetShortField(*obj, fdAudioDecoderCfgLen);

	jfieldID fdAudioDecoderCfg = (env)->GetFieldID(cla, "m_u8AudioDecoderCfg", "[B");
	jbyteArray AudioDecoderCfgArr = (jbyteArray)(env->GetObjectField(*obj, fdAudioDecoderCfg));
	GetByteArrayData(env, record3Gpp->m_u8AudioDecoderCfg, &AudioDecoderCfgArr, 200);

	jfieldID fdVideoProfiles = (env)->GetFieldID(cla, "m_u8VideoProfiles", "B");
	record3Gpp->m_u8VideoProfiles = (env)->GetByteField(*obj, fdVideoProfiles);

	jfieldID fdVideoLevel = (env)->GetFieldID(cla, "m_u8VideoLevel", "B");
	record3Gpp->m_u8VideoLevel = (env)->GetByteField(*obj, fdVideoLevel);

	jfieldID fdVideoDecoderCfgLen = (env)->GetFieldID(cla, "m_u16VideoDecoderCfgLen", "S");
	record3Gpp->m_u16VideoDecoderCfgLen = (env)->GetShortField(*obj, fdVideoDecoderCfgLen);

	jfieldID fdVideoDecoderCfg = (env)->GetFieldID(cla, "m_u8VideoDecoderCfg", "[B");
	jbyteArray VideoDecoderCfgArr = (jbyteArray)(env->GetObjectField(*obj, fdVideoDecoderCfg));
	GetByteArrayData(env, record3Gpp->m_u8VideoDecoderCfg, &VideoDecoderCfgArr, 200);

	jfieldID fdFileName = (env)->GetFieldID(cla, "m_s8FileName", "[B");
	jbyteArray FileNameArr = (jbyteArray)(env->GetObjectField(*obj, fdFileName));
	GetByteArrayData(env, (byte*)record3Gpp->m_s8FileName, &FileNameArr, 260);

	LogInfo("Exit GetData_Record3Gpp");
}

void GetData_Ctrl3GpPlay (JNIEnv * env, jobject * obj, Control3gppPlay_t* ctrl3GpPlay)
{
	LogInfo("Entry GetData_Ctrl3GpPlay");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdCtrlType = (env)->GetFieldID(cla, "m_u16ControlType", "S");
	ctrl3GpPlay->m_u16ControlType = (env)->GetShortField(*obj, fdCtrlType);

	jfieldID fdStepTime = (env)->GetFieldID(cla, "m_u16StepTime", "S");
	ctrl3GpPlay->m_u16StepTime = (env)->GetShortField(*obj, fdStepTime);

	jfieldID fdTuneType = (env)->GetFieldID(cla, "m_u16TuneType", "S");
	ctrl3GpPlay->m_u16TuneType = (env)->GetShortField(*obj, fdTuneType);

	jfieldID fdSpeedSize = (env)->GetFieldID(cla, "m_u16SpeedSize", "S");
	ctrl3GpPlay->m_u16SpeedSize = (env)->GetShortField(*obj, fdSpeedSize);

	jfieldID fdMediaType = (env)->GetFieldID(cla, "m_u8MediaType", "B");
	ctrl3GpPlay->m_u8MediaType = (env)->GetByteField(*obj, fdMediaType);

	jfieldID fdReserv = (env)->GetFieldID(cla, "m_u8Reserv1", "[B");
	jbyteArray ReservArr = (jbyteArray)(env->GetObjectField(*obj, fdReserv));
	GetByteArrayData(env, ctrl3GpPlay->m_u8Reserv1, &ReservArr, 3);

	LogInfo("Exit GetData_Ctrl3GpPlay");
}

void GetData_MediaPlay (JNIEnv * env, jobject * obj, Acs_MediaEx_Play* MediaPlay)
{
	LogInfo("Entry GetData_MediaPlay");

	jclass cla = env->GetObjectClass(*obj);
	
	jfieldID fieldPrivate = env->GetFieldID(cla, "m_PrivateData", "LDJKeygoe/PrivateData_t;");
	jobject  PrivateObj = env->GetObjectField(*obj, fieldPrivate);
	GetData_Private(env, &PrivateObj, &MediaPlay->m_PrivateData);

	jfieldID fdSrcName = (env)->GetFieldID(cla, "m_s8SrcName", "[B");
	jbyteArray SrcNameArr = (jbyteArray)(env->GetObjectField(*obj, fdSrcName));
	GetByteArrayData(env, (byte*)MediaPlay->m_s8SrcName, &SrcNameArr, 128);

	jfieldID fdStart = (env)->GetFieldID(cla, "m_u32Start", "I");
	MediaPlay->m_u32Start = (env)->GetIntField(*obj, fdStart);

	jfieldID fdLoop = (env)->GetFieldID(cla, "m_u8Loop", "B");
	MediaPlay->m_u8Loop = (env)->GetByteField(*obj, fdLoop);

	jfieldID fieldAudio = env->GetFieldID(cla, "audio", "LDJKeygoe/Acs_MediaEx_Output_A;");
	jobject  AudioObj = env->GetObjectField(*obj, fieldAudio);
	GetData_OutPutA(env, &AudioObj, &MediaPlay->audio);

	jfieldID fieldVideo = env->GetFieldID(cla, "video", "LDJKeygoe/Acs_MediaEx_Output_V;");
	jobject  VideoObj = env->GetObjectField(*obj, fieldVideo);
	GetData_OutPutV(env, &VideoObj, &MediaPlay->video);

	jfieldID fdOverlayImage = (env)->GetFieldID(cla, "s8OverlayImage", "[B");
	jbyteArray OverlayImageArr = (jbyteArray)(env->GetObjectField(*obj, fdOverlayImage));
	GetByteArrayData(env, (byte*)MediaPlay->s8OverlayImage, &OverlayImageArr, 200);

	LogInfo("Exit GetData_MediaPlay");
}

void GetData_Play3GppIndex (JNIEnv * env, jobject * obj, Play3gppProperty_t* play3Gpp)
{
	LogInfo("Entry GetData_Play3GppIndex");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdTaskID = (env)->GetFieldID(cla, "m_u8TaskID", "B");
	play3Gpp->m_u8TaskID = (env)->GetByteField(*obj, fdTaskID);

	jfieldID fdSrcMode = (env)->GetFieldID(cla, "m_u8SrcMode", "B");
	play3Gpp->m_u8SrcMode = (env)->GetByteField(*obj, fdSrcMode);

	jfieldID fdDecodeType = (env)->GetFieldID(cla, "m_u8DecodeType", "B");
	play3Gpp->m_u8DecodeType = (env)->GetByteField(*obj, fdDecodeType);

	jfieldID fdAudio_tracks = (env)->GetFieldID(cla, "m_u8Audio_tracks", "B");
	play3Gpp->m_u8Audio_tracks = (env)->GetByteField(*obj, fdAudio_tracks);

	jfieldID fdAmrFrameType = (env)->GetFieldID(cla, "m_u8AmrFrameType", "B");
	play3Gpp->m_u8AmrFrameType = (env)->GetByteField(*obj, fdAmrFrameType);

	jfieldID fdAudioNoDecode = (env)->GetFieldID(cla, "m_u8AudioNoDecode", "B");
	play3Gpp->m_u8AudioNoDecode = (env)->GetByteField(*obj, fdAudioNoDecode);

	jfieldID fdRfu = (env)->GetFieldID(cla, "m_u8Rfu1", "[B");
	jbyteArray RfuArr = (jbyteArray)(env->GetObjectField(*obj, fdRfu));
	GetByteArrayData(env, play3Gpp->m_u8Rfu1, &RfuArr, 2);

	jfieldID fdMaxTime = (env)->GetFieldID(cla, "m_u32MaxTime", "I");
	play3Gpp->m_u32MaxTime = (env)->GetIntField(*obj, fdMaxTime);

	jfieldID fdStopMode = (env)->GetFieldID(cla, "m_u32StopMode", "I");
	play3Gpp->m_u32StopMode = (env)->GetIntField(*obj, fdStopMode);

	jfieldID fdStopCode = (env)->GetFieldID(cla, "m_u32StopCode", "I");
	play3Gpp->m_u32StopCode = (env)->GetIntField(*obj, fdStopCode);

	jfieldID fdTimeOffset = (env)->GetFieldID(cla, "m_u16TimeOffset", "S");
	play3Gpp->m_u16TimeOffset = (env)->GetShortField(*obj, fdTimeOffset);

	jfieldID fdPlayType = (env)->GetFieldID(cla, "m_u16PlayType", "S");
	play3Gpp->m_u16PlayType = (env)->GetShortField(*obj, fdPlayType);

	jfieldID fdPlayIndex = (env)->GetFieldID(cla, "m_u16PlayIndex", "S");
	play3Gpp->m_u16PlayIndex = (env)->GetShortField(*obj, fdPlayIndex);

	jfieldID fdRfu2 = (env)->GetFieldID(cla, "m_s16Rfu2", "S");
	play3Gpp->m_s16Rfu2 = (env)->GetShortField(*obj, fdRfu2);

	jfieldID fdPlayContent = (env)->GetFieldID(cla, "m_s8PlayContent", "[B");
	jbyteArray fdPlayContentArr = (jbyteArray)(env->GetObjectField(*obj, fdPlayContent));
	GetByteArrayData(env, (byte*)play3Gpp->m_s8PlayContent, &fdPlayContentArr, 128);

	jfieldID fdVideoFrameRate = (env)->GetFieldID(cla, "m_u8VideoFrameRate", "B");
	play3Gpp->m_u8VideoFrameRate = (env)->GetByteField(*obj, fdVideoFrameRate);

	jfieldID fdVideoDecode_Type = (env)->GetFieldID(cla, "m_u8VideoDecode_Type", "B");
	play3Gpp->m_u8VideoDecode_Type = (env)->GetByteField(*obj, fdVideoDecode_Type);

	jfieldID fdVideoHigh = (env)->GetFieldID(cla, "m_u8VideoHigh", "B");
	play3Gpp->m_u8VideoHigh = (env)->GetByteField(*obj, fdVideoHigh);

	jfieldID fdVideoWidth = (env)->GetFieldID(cla, "m_u8VideoWidth", "B");
	play3Gpp->m_u8VideoWidth = (env)->GetByteField(*obj, fdVideoWidth);

	jfieldID fdVideoMaxTime = (env)->GetFieldID(cla, "m_u32VideoMaxTime", "I");
	play3Gpp->m_u32VideoMaxTime = (env)->GetIntField(*obj, fdVideoMaxTime);

	jfieldID fdVideoTimeOffset = (env)->GetFieldID(cla, "m_u16VideoTimeOffset", "S");
	play3Gpp->m_u16VideoTimeOffset = (env)->GetShortField(*obj, fdVideoTimeOffset);

	jfieldID fdVideoPlayType = (env)->GetFieldID(cla, "m_u16VideoPlayType", "S");
	play3Gpp->m_u16VideoPlayType = (env)->GetShortField(*obj, fdVideoPlayType);

	jfieldID fdVideoPlayIndex = (env)->GetFieldID(cla, "m_u16VideoPlayIndex", "S");
	play3Gpp->m_u16VideoPlayIndex = (env)->GetShortField(*obj, fdVideoPlayIndex);

	jfieldID fdVideoTaskID = (env)->GetFieldID(cla, "m_u8VideoTaskID", "B");
	play3Gpp->m_u8VideoTaskID = (env)->GetByteField(*obj, fdVideoTaskID);

	jfieldID fdMediaType = (env)->GetFieldID(cla, "m_u8MediaType", "B");
	play3Gpp->m_u8MediaType = (env)->GetByteField(*obj, fdMediaType);

	jfieldID fdVideoPlayContent = (env)->GetFieldID(cla, "m_s8VideoPlayContent", "[B");
	jbyteArray VideoPlayContentArr = (jbyteArray)(env->GetObjectField(*obj, fdVideoPlayContent));
	GetByteArrayData(env, (byte*)play3Gpp->m_s8VideoPlayContent, &VideoPlayContentArr, 128);

	LogInfo("Exit GetData_Play3GppIndex");
}

void GetData_CtrlPlay (JNIEnv * env, jobject * obj, ControlPlay_t* ctrlPlay)
{
	LogInfo("Entry GetData_CtrlPlay");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdControlType = (env)->GetFieldID(cla, "m_u16ControlType", "S");
	ctrlPlay->m_u16ControlType = (env)->GetShortField(*obj, fdControlType);

	jfieldID fdStepSize = (env)->GetFieldID(cla, "m_u16StepSize", "S");
	ctrlPlay->m_u16StepSize = (env)->GetShortField(*obj, fdStepSize);

	jfieldID fdTuneType = (env)->GetFieldID(cla, "m_u16TuneType", "S");
	ctrlPlay->m_u16TuneType = (env)->GetShortField(*obj, fdTuneType);

	jfieldID fdSpeedSize = (env)->GetFieldID(cla, "m_u16SpeedSize", "S");
	ctrlPlay->m_u16SpeedSize = (env)->GetShortField(*obj, fdSpeedSize);

	LogInfo("Exit GetData_CtrlPlay");
}

void GetData_CspPlayInfo (JNIEnv * env, jobject * obj, CSPPlayDataInfo_t* cspPlayInfo)
{
	LogInfo("Entry GetData_CspPlayInfo");

	jclass cla = env->GetObjectClass(*obj);

	jfieldID fdDataLen = (env)->GetFieldID(cla, "m_u16DataLen", "S");
	cspPlayInfo->m_u16DataLen = (env)->GetShortField(*obj, fdDataLen);

	jfieldID fdDataType = (env)->GetFieldID(cla, "m_u8DataType", "B");
	cspPlayInfo->m_u8DataType = (env)->GetByteField(*obj, fdDataType);

	jfieldID fdTaskID = (env)->GetFieldID(cla, "m_u8TaskID", "B");
	cspPlayInfo->m_u8TaskID = (env)->GetByteField(*obj, fdTaskID);

	LogInfo("Exit GetData_CspPlayInfo");
}

void GetData_CspPlay(JNIEnv * env, jobject * obj, CSPPlayProperty_t* cspPlay)
{
	LogInfo("Entry GetData_CspPlay");
	
	jclass cla = (env)->GetObjectClass(*obj);

	jfieldID fdTaskID = (env)->GetFieldID(cla, "m_u8TaskID", "B");
	cspPlay->m_u8TaskID = (env)->GetByteField(*obj, fdTaskID);

	jfieldID fdSrcMode = (env)->GetFieldID(cla, "m_u8SrcMode", "B");
	cspPlay->m_u8SrcMode = (env)->GetByteField(*obj, fdSrcMode);

	jfieldID fdDecodeType = (env)->GetFieldID(cla, "m_u8DecodeType", "B");
	cspPlay->m_u8DecodeType = (env)->GetByteField(*obj, fdDecodeType);

	jfieldID fdRfu1 = (env)->GetFieldID(cla, "m_s8Rfu1", "B");
	cspPlay->m_s8Rfu1[0] = (env)->GetByteField(*obj, fdRfu1);

	jfieldID fdMaxSize = (env)->GetFieldID(cla, "m_u32MaxSize", "I");
	cspPlay->m_u32MaxSize = (env)->GetIntField(*obj, fdMaxSize);

	jfieldID fdMaxTime = (env)->GetFieldID(cla, "m_u32MaxTime", "I");
	cspPlay->m_u32MaxTime = (env)->GetIntField(*obj, fdMaxTime);

	jfieldID fdStopMode = (env)->GetFieldID(cla, "m_u32StopMode", "I");
	cspPlay->m_u32StopMode = (env)->GetIntField(*obj, fdStopMode);

	jfieldID fdStopCode = (env)->GetFieldID(cla, "m_u32StopCode", "I");
	cspPlay->m_u32StopCode = (env)->GetIntField(*obj, fdStopCode);

	jfieldID fdRfu = (env)->GetFieldID(cla, "m_Rfu1", "[B");
	jbyteArray RfuArr = (jbyteArray)(env->GetObjectField(*obj, fdRfu));
	GetByteArrayData(env, (byte*)cspPlay->m_Rfu1, &RfuArr, 4);

	LogInfo("Exit GetData_CspPlay");
}

void GetData_ServerID (JNIEnv * env, jobject* obj, ServerID_t* serverID)
{
	LogInfo("Entry GetData_ServerID");

	jclass objectClass = (env)->GetObjectClass(*obj);

	jfieldID fdPort = (env)->GetFieldID(objectClass, "m_u32ServerPort", "I");
	serverID->m_u32ServerPort = (env)->GetIntField(*obj, fdPort);
	
	jfieldID fdIP = (env)->GetFieldID(objectClass, "m_s8ServerIp", "[B");
	jbyteArray IpArr = (jbyteArray)(env->GetObjectField(*obj, fdIP));
	GetByteArrayData(env, (byte*)serverID->m_s8ServerIp, &IpArr, 32);

	jfieldID fdUserName = (env)->GetFieldID(objectClass, "m_s8UserName", "[B");
	jbyteArray UserNameArr = (jbyteArray)(env->GetObjectField(*obj, fdUserName));
	GetByteArrayData(env, (byte*)serverID->m_s8UserName, &UserNameArr, 32);

	jfieldID fdUserPwd = (env)->GetFieldID(objectClass, "m_s8UserPwd", "[B");
	jbyteArray UserPwdArr = (jbyteArray)(env->GetObjectField(*obj, fdUserPwd));
	GetByteArrayData(env, (byte*)serverID->m_s8UserPwd, &UserPwdArr, 32);

	LogInfo("Exit GetData_ServerID");
}

/*
 * 在C++中调用Java的方法一般分为五个步骤：初始化虚拟机、获取类、创建类对象、调用方法和退出虚拟机
 */
DJ_Void EvtHandler(DJ_U32 esrParam) 
{
	LogInfo("Entry EvtHandler");

	Acs_Evt_t* pEvt = (Acs_Evt_t*)esrParam;

	g_cbData.mg_Jvm->AttachCurrentThread((void**)&g_cbData.m_pEnv, NULL);

	jclass clsAcsEvt = g_cbData.m_pEnv->FindClass("DJKeygoe/Acs_Evt_t");
	
	jmethodID  midAcsEvt = g_cbData.m_pEnv->GetMethodID(clsAcsEvt, "<init>", "()V");

	jobject objAcsEvt = g_cbData.m_pEnv->NewObject(clsAcsEvt, midAcsEvt);

	SetData_Evt(pEvt, &objAcsEvt);

	jobject obj = NULL;

	switch(pEvt->m_s32EventType)
	{
	case XMS_EVT_OPEN_STREAM:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtOpenStreamData");

			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);

			jfieldID fdProcData = g_cbData.m_pEnv->GetFieldID(cls, "acsGenerProcData", "LDJKeygoe/Acs_GeneralProc_Data;");
			jobject objProcData = g_cbData.m_pEnv->GetObjectField(obj, fdProcData);

			SetData_GeneralProc((Acs_GeneralProc_Data *)(FetchEventData(pEvt)), &objProcData);
			break;
		}

	case XMS_EVT_QUERY_DEVICE:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtQueryDeviceData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);

			jfieldID fdDevListData = g_cbData.m_pEnv->GetFieldID(cls, "acsDevListHead", "LDJKeygoe/Acs_Dev_List_Head_t;");
			jobject objDevList = g_cbData.m_pEnv->GetObjectField(obj, fdDevListData);
			
			SetData_DevListHead((Acs_Dev_List_Head_t *)(FetchEventData(pEvt)), &objDevList); 

			jfieldID fdDevice = g_cbData.m_pEnv->GetFieldID(cls, "device", "[LDJKeygoe/DeviceID_t;");
			
			jobjectArray objArray = (jobjectArray)g_cbData.m_pEnv->GetObjectField(obj, fdDevice);
			
			if (objArray)
			{
				jsize nObjArrLen = g_cbData.m_pEnv->GetArrayLength(objArray);
				
				Acs_Dev_List_Head_t* pListHeadData = (Acs_Dev_List_Head_t*)FetchEventData(pEvt);
				DJ_U8 * pData = (DJ_U8*)FetchDeviceList(pEvt);

				if (pListHeadData->m_s32DeviceNum > nObjArrLen)
				{
					printf ("\n pListHeadData->m_s32DeviceNum = %d, nObjArrLen = %d\n", pListHeadData->m_s32DeviceNum, nObjArrLen);
					MessageBox(0, "The device number more than array of Settings!", "Warning", MB_OK);
					return ;
				}
				
				for (int i = 0; i < pListHeadData->m_s32DeviceNum; i++)
				{
					jobject DeviceObj = g_cbData.m_pEnv->GetObjectArrayElement(objArray, i);
					
					SetData_DeviceID((DeviceID_t*)pData, &DeviceObj);
					
					DeviceID_t* pDevData = (DeviceID_t*)pData;
					
					pData = pData + sizeof(DeviceID_t);
				}
			}
			break;
		}

	case XMS_EVT_OPEN_DEVICE:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtOpenDeviceData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdProcData = g_cbData.m_pEnv->GetFieldID(cls, "acsGenerProcData", "LDJKeygoe/Acs_GeneralProc_Data;");
			jobject objProcData = g_cbData.m_pEnv->GetObjectField(obj, fdProcData);
			
			SetData_GeneralProc((Acs_GeneralProc_Data *)(FetchEventData(pEvt)), &objProcData);

			break;
		}

	case XMS_EVT_CLOSE_DEVICE:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtCloseDeviceData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdProcData = g_cbData.m_pEnv->GetFieldID(cls, "acsGenerProcData", "LDJKeygoe/Acs_GeneralProc_Data;");
			jobject objProcData = g_cbData.m_pEnv->GetObjectField(obj, fdProcData);
			
			SetData_GeneralProc((Acs_GeneralProc_Data *)(FetchEventData(pEvt)), &objProcData);
			break;
		}

	case XMS_EVT_DEVICESTATE:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtDeviceStateData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdProcData = g_cbData.m_pEnv->GetFieldID(cls, "acsGenerProcData", "LDJKeygoe/Acs_GeneralProc_Data;");
			jobject objProcData = g_cbData.m_pEnv->GetObjectField(obj, fdProcData);
			
			SetData_GeneralProc((Acs_GeneralProc_Data *)(FetchEventData(pEvt)), &objProcData);
			break;
		}

	case XMS_EVT_RESET_DEVICE:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtResetDeviceData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdProcData = g_cbData.m_pEnv->GetFieldID(cls, "acsGenerProcData", "LDJKeygoe/Acs_GeneralProc_Data;");
			jobject objProcData = g_cbData.m_pEnv->GetObjectField(obj, fdProcData);
			
			SetData_GeneralProc((Acs_GeneralProc_Data *)(FetchEventData(pEvt)), &objProcData);
			break;
		}

	case XMS_EVT_SETDEV_GROUP:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtSetDevGroupData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdProcData = g_cbData.m_pEnv->GetFieldID(cls, "acsGenerProcData", "LDJKeygoe/Acs_GeneralProc_Data;");
			jobject objProcData = g_cbData.m_pEnv->GetObjectField(obj, fdProcData);
			
			SetData_GeneralProc((Acs_GeneralProc_Data *)(FetchEventData(pEvt)), &objProcData);

			break;
		}

	case XMS_EVT_SETPARAM:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtSetParamData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdParamProcData = g_cbData.m_pEnv->GetFieldID(cls, "acsParamProcData", "LDJKeygoe/Acs_ParamProc_Data;");
			jobject objParamProcData = g_cbData.m_pEnv->GetObjectField(obj, fdParamProcData);
			
			SetData_ParamProc((Acs_ParamProc_Data *)(FetchEventData(pEvt)), &objParamProcData);

			break;
		}

	case XMS_EVT_GETPARAM:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtGetParamData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdParamProcData = g_cbData.m_pEnv->GetFieldID(cls, "acsParamProcData", "LDJKeygoe/Acs_ParamProc_Data;");
			jobject objParamProcData = g_cbData.m_pEnv->GetObjectField(obj, fdParamProcData);
			
			SetData_ParamProc((Acs_ParamProc_Data *)(FetchEventData(pEvt)), &objParamProcData);

			if (XMS_DEVMAIN_VOIP == pEvt->m_DeviceID.m_s16DeviceMain)
			{
				Acs_VoIP_RTPCODEC *pCodec = (Acs_VoIP_RTPCODEC*)(FetchParamData(pEvt));

				jfieldID fdRtpCodec = g_cbData.m_pEnv->GetFieldID(cls, "acsDataRtpCodec", "LDJKeygoe/Acs_VoIP_RTPCODEC;");
				jobject objRtpCodec = g_cbData.m_pEnv->GetObjectField(obj, fdRtpCodec);


				SetData_VoipCodec(pCodec, &objRtpCodec);

				break;
			}

			if (XMS_DEVMAIN_VOICE == pEvt->m_DeviceID.m_s16DeviceMain)
			{
				CmdParamData_3GPP_t *pData =  (CmdParamData_3GPP_t *)FetchParamData(pEvt);

				jfieldID fd3Gpp = g_cbData.m_pEnv->GetFieldID(cls, "acsData3Gpp", "LDJKeygoe/CmdParamData_3GPP_t;");
				jobject obj3Gpp = g_cbData.m_pEnv->GetObjectField(obj, fd3Gpp);

				SetData_3Gpp(pData, &obj3Gpp);

				break;
			}

			if (XMS_DEVMAIN_BOARD == pEvt->m_DeviceID.m_s16DeviceMain)
			{
				Acs_ParamData_UserReadXmsBoardInfo* pBoardInfor =  (Acs_ParamData_UserReadXmsBoardInfo *)FetchParamData(pEvt);

				jfieldID fdBoard = g_cbData.m_pEnv->GetFieldID(cls, "acsDataBoard", "LDJKeygoe/Acs_ParamData_UserReadXmsBoardInfo;");
				jobject objBoard = g_cbData.m_pEnv->GetObjectField(obj, fdBoard);

				SetData_Board(pBoardInfor, &objBoard);

				break;
			}

			if (XMS_DEVMAIN_CONFERENCE == pEvt->m_DeviceID.m_s16DeviceMain)
			{
				CmdParamConf_MemberState_t* pData = (CmdParamConf_MemberState_t*)FetchParamData(pEvt);

				jfieldID fdConf = g_cbData.m_pEnv->GetFieldID(cls, "acsDataConf", "LDJKeygoe/CmdParamConf_MemberState_t;");
				jobject objConf = g_cbData.m_pEnv->GetObjectField(obj, fdConf);

				SetData_Conf(pData, &objConf);

				break;
			}

			if (XMS_DEVMAIN_INTERFACE_CH == pEvt->m_DeviceID.m_s16DeviceMain)
			{
				Acs_ParamProc_Data* pParam = (Acs_ParamProc_Data *)(FetchEventData(pEvt));

				if (ANALOGVOC2_PARAM_READSN == pParam->m_u16ParamCmdType)
				{
					CmdParamData_ReadSn_t *pReadSN =  (CmdParamData_ReadSn_t *)FetchParamData(pEvt);

					jfieldID fdReadSn = g_cbData.m_pEnv->GetFieldID(cls, "acsDataReadSn", "LDJKeygoe/CmdParamData_ReadSn_t;");
					jobject objReadSn = g_cbData.m_pEnv->GetObjectField(obj, fdReadSn);
					
					SetData_ReadSn(pReadSN, &objReadSn);
				}
				else if (ANALOGHIZ_PARAM_GET_VOLTAGE == pParam->m_u16ParamCmdType)
				{
					byte *pData =  (byte *)FetchParamData(pEvt);

					jfieldID fdNum = g_cbData.m_pEnv->GetFieldID(cls, "OriginalNum", "[B");
					jbyteArray szNum = (jbyteArray)(g_cbData.m_pEnv->GetObjectField(obj, fdNum));
					SetByteArrayData(&szNum, pData, pParam->m_u16ParamDataSize);

				}
				else if (ISDN_PARAM_ORINUMBER == pParam->m_u16ParamCmdType)
				{
					CmdParamData_ReadVoltage_t *pData =  (CmdParamData_ReadVoltage_t *)FetchParamData(pEvt);

					jfieldID fdReadVol = g_cbData.m_pEnv->GetFieldID(cls, "acsDataReadVolteage", "LDJKeygoe/CmdParamData_ReadVoltage_t;");
					jobject objReadVol = g_cbData.m_pEnv->GetObjectField(obj, fdReadVol);
					
					SetData_ReadVolteage(pData, &objReadVol);
				}

				break;
			}

			break;
		}

	case XMS_EVT_LICENSE_QUERY:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtLicenseQueryData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdLicenseQueryData = g_cbData.m_pEnv->GetFieldID(cls, "acsLicenseQueryData", "LDJKeygoe/Acs_LicenseQuery_Data;");
			jobject objLicenseQueryData = g_cbData.m_pEnv->GetObjectField(obj, fdLicenseQueryData);
			
			SetData_LicenseQuery((Acs_LicenseQuery_Data *)(FetchEventData(pEvt)), &objLicenseQueryData);

			break;
		}

	case XMS_EVT_MODRELATE:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtModRelateData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdModRelateData = g_cbData.m_pEnv->GetFieldID(cls, "acsModRelateData", "LDJKeygoe/Acs_ModRelate_Data;");
			jobject objModRelateData = g_cbData.m_pEnv->GetObjectField(obj, fdModRelateData);
			
			SetData_ModRelate((Acs_ModRelate_Data*)(FetchEventData(pEvt)), &objModRelateData);

			break;
		}

	case XMS_EVT_CALLOUT:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtCallOutData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdCallOut = g_cbData.m_pEnv->GetFieldID(cls, "acsCallOutData", "LDJKeygoe/Acs_CallControl_Data;");
			jobject objCallOut = g_cbData.m_pEnv->GetObjectField(obj, fdCallOut);
			
			SetData_CallControl((Acs_CallControl_Data *)(FetchEventData(pEvt)), &objCallOut);

			if (((Acs_Evt_t*)pEvt)->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_VOIP) //如果是Voip呼叫 Acs_CallControl_Data后面跟有VoipCallPrivate_t
			{
				jfieldID fdVoipCallOut = g_cbData.m_pEnv->GetFieldID(cls, "voipCallOutData", "LDJKeygoe/VoIPCallPrivate_t;");
				jobject objVoipCallOut = g_cbData.m_pEnv->GetObjectField(obj, fdVoipCallOut);

				SetData_VoipCallPrivate((VoIPCallPrivate_t*)FetchVoipCallData(pEvt), &objVoipCallOut);
			}

			break;
		}

	case XMS_EVT_CALLIN:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtCallInData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdCallIn = g_cbData.m_pEnv->GetFieldID(cls, "acsCallInData", "LDJKeygoe/Acs_CallControl_Data;");
			jobject objCallIn = g_cbData.m_pEnv->GetObjectField(obj, fdCallIn);
			
			SetData_CallControl((Acs_CallControl_Data *)(FetchEventData(pEvt)), &objCallIn);
			
			if (((Acs_Evt_t*)pEvt)->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_VOIP) //如果是Voip呼叫 Acs_CallControl_Data后面跟有VoipCallPrivate_t
			{
				jfieldID fdVoipCallIn = g_cbData.m_pEnv->GetFieldID(cls, "voipCallInData", "LDJKeygoe/VoIPCallPrivate_t;");
				jobject objVoipCallIn = g_cbData.m_pEnv->GetObjectField(obj, fdVoipCallIn);
				
				SetData_VoipCallPrivate((VoIPCallPrivate_t*)FetchVoipCallData(pEvt), &objVoipCallIn);
			}

			break;
		}

	case XMS_EVT_ALERTCALL:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtAlertCallData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdAlertCall = g_cbData.m_pEnv->GetFieldID(cls, "acsAlertCallData", "LDJKeygoe/Acs_CallControl_Data;");
			jobject objAlertCall = g_cbData.m_pEnv->GetObjectField(obj, fdAlertCall);
			
			SetData_CallControl((Acs_CallControl_Data *)(FetchEventData(pEvt)), &objAlertCall);

			break;
		}

	case XMS_EVT_ANSWERCALL:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtAnswerCallData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdAnswerCall = g_cbData.m_pEnv->GetFieldID(cls, "acsAnswerCallData", "LDJKeygoe/Acs_CallControl_Data;");
			jobject objAnswerCall = g_cbData.m_pEnv->GetObjectField(obj, fdAnswerCall);
			
			SetData_CallControl((Acs_CallControl_Data *)(FetchEventData(pEvt)), &objAnswerCall);

			break;
		}

	case XMS_EVT_LINKDEVICE:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtLinkDeviceData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdLinkDev = g_cbData.m_pEnv->GetFieldID(cls, "acsLinkDevData", "LDJKeygoe/Acs_LinkDev_Data;");
			jobject objLinkDev = g_cbData.m_pEnv->GetObjectField(obj, fdLinkDev);
			
			SetData_LinkDevData((Acs_LinkDev_Data *)(FetchEventData(pEvt)), &objLinkDev);

			break;
		}

	case XMS_EVT_UNLINKDEVICE:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtUnLinkDeviceData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdUnLinkDev = g_cbData.m_pEnv->GetFieldID(cls, "acsUnLinkDevData", "LDJKeygoe/Acs_LinkDev_Data;");
			jobject objUnLinkDev = g_cbData.m_pEnv->GetObjectField(obj, fdUnLinkDev);
			
			SetData_LinkDevData((Acs_LinkDev_Data *)(FetchEventData(pEvt)), &objUnLinkDev);

			break;
		}


	case XMS_EVT_CLEARCALL:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtClearCallData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdclearCall = g_cbData.m_pEnv->GetFieldID(cls, "acsClearCallData", "LDJKeygoe/Acs_CallControl_Data;");
			jobject objClearCall = g_cbData.m_pEnv->GetObjectField(obj, fdclearCall);
			
			SetData_CallControl((Acs_CallControl_Data *)(FetchEventData(pEvt)), &objClearCall);

			break;
		}

	case XMS_EVT_ANALOG_INTERFACE:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtAnalogInterfaceData");

			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsAngInfaceData", "LDJKeygoe/Acs_AnalogInterface_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_AnalogInterface((Acs_AnalogInterface_Data *)(FetchEventData(pEvt)), &obj1);
			
			break;
		}

	case XMS_EVT_SENDSIGMSG:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtSendSigMsgData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsSendSigMsgData", "LDJKeygoe/Acs_SendSigMsg_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_SendSigMsg((Acs_SendSigMsg_Data *)(FetchEventData(pEvt)), &obj1);
			
			break;
		}

	case XMS_EVT_SIGMON:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtSigMonData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsSigMonData", "LDJKeygoe/Acs_SigMon_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_SigMon((Acs_SigMon_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_CTX_REG:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtCtxRegData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsCtxRegData", "LDJKeygoe/Acs_CtxReg_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_CtxReg((Acs_CtxReg_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_CTX_LINK:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtCtxLinkData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsCtxLinkData", "LDJKeygoe/Acs_CtxLink_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_CtxLink((Acs_CtxLink_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_CTX_APPDATA:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtCtxAppData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "ctxAppDataInfo", "LDJKeygoe/Acs_CtxAppData_Info;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_CtxAppDataInfo((Acs_CtxAppData_Info *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_JOINTOCONF:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtJoinToConfData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsConfCtrlData", "LDJKeygoe/Acs_ConfControl_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_ConfControl((Acs_ConfControl_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_LEAVEFROMCONF:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtLeaveFromConfData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsConfCtrlData", "LDJKeygoe/Acs_ConfControl_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_ConfControl((Acs_ConfControl_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_CLEARCONF:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtClearConfData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsConfCtrlData", "LDJKeygoe/Acs_ConfControl_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_ConfControl((Acs_ConfControl_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_PLAY:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtPlayData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsMediaProcData", "LDJKeygoe/Acs_MediaProc_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_MediaProc((Acs_MediaProc_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_INITINDEX:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtInitIndexData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsMediaProcData", "LDJKeygoe/Acs_MediaProc_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_MediaProc((Acs_MediaProc_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_BUILDINDEX:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtBuildIndexData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsMediaProcData", "LDJKeygoe/Acs_MediaProc_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_MediaProc((Acs_MediaProc_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_CONTROLPLAY:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtControlPlayData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsMediaProcData", "LDJKeygoe/Acs_MediaProc_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_MediaProc((Acs_MediaProc_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_RECORD:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtRecordData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsMediaProcData", "LDJKeygoe/Acs_MediaProc_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_MediaProc((Acs_MediaProc_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_CONTROLRECORD:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtControlRecordData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsMediaProcData", "LDJKeygoe/Acs_MediaProc_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_MediaProc((Acs_MediaProc_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_PLAYCSPREQ:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtPlayCspReq");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsCspDataReq", "LDJKeygoe/Acs_CSPDataReq_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_CspDataReq((Acs_CSPDataReq_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_RECORDCSP:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtRecordCsp");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsMediaCspProcData", "LDJKeygoe/Acs_MediaCSPProc_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_MediaCspProc((Acs_MediaCSPProc_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_3GPP_PLAY:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvt3gppPlayData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsMedia3gppProcData", "LDJKeygoe/Acs_Media3GPPProc_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_Media3GppProc((Acs_Media3GPPProc_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_3GPP_CONTROLPLAY:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvt3gppControlPlayData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsMedia3gppProcData", "LDJKeygoe/Acs_Media3GPPProc_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_Media3GppProc((Acs_Media3GPPProc_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_3GPP_RECORD:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvt3gppRecordData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsMedia3gppProcData", "LDJKeygoe/Acs_Media3GPPProc_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_Media3GppProc((Acs_Media3GPPProc_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_3GPP_CONTROLRECORD:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvt3gppControlRecordData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsMedia3gppProcData", "LDJKeygoe/Acs_Media3GPPProc_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_Media3GppProc((Acs_Media3GPPProc_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_3GPP_INIT_INDEX:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvt3gppInitIndex");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsMediaProcData", "LDJKeygoe/Acs_MediaProc_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_MediaProc((Acs_MediaProc_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_3GPP_BUILD_INDEX:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvt3gppBuildIndexData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsMedia3gppProcData", "LDJKeygoe/Acs_Media3GPPProc_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_Media3GppProc((Acs_Media3GPPProc_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_SENDFAX:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtSendFaxData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsFaxProcData", "LDJKeygoe/Acs_FaxProc_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_FaxProc((Acs_FaxProc_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_RECVFAX:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtRecvFaxData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsFaxProcData", "LDJKeygoe/Acs_FaxProc_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_FaxProc((Acs_FaxProc_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_SENDIODATA:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtSendIOData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdSendData = g_cbData.m_pEnv->GetFieldID(cls, "acsIOData", "LDJKeygoe/Acs_IO_Data;");
			jobject objSendData = g_cbData.m_pEnv->GetObjectField(obj, fdSendData);
			
			LogInfo ("	case XMS_EVT_SENDIODATA!\n");

			SetData_IOData((Acs_IO_Data *)(FetchEventData(pEvt)), &objSendData);

			LogInfo ("	case XMS_EVT_SENDIODATA!\n");

			break;
		}

	case XMS_EVT_RECVIODATA:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtRecvIOData");

			int nRecvDataLen = ((Acs_IO_Data *)(FetchEventData(pEvt)))->m_u16IoDataLen;
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "(I)V");

			obj = g_cbData.m_pEnv->NewObject(cls, mid, nRecvDataLen);

			jfieldID fdRecvData = g_cbData.m_pEnv->GetFieldID(cls, "acsIOData", "LDJKeygoe/Acs_IO_Data;");
			jobject objRecvData = g_cbData.m_pEnv->GetObjectField(obj, fdRecvData);

			SetData_IOData((Acs_IO_Data *)(FetchEventData(pEvt)), &objRecvData);

			//int nRecvDataLen = ((Acs_IO_Data *)(FetchEventData(pEvt)))->m_u16IoDataLen;
			
			//jmethodID methodID = g_cbData.m_pEnv->GetMethodID(cls, "SetRecvBufLen", "(I)V");
			
			//g_cbData.m_pEnv->CallVoidMethod(obj, methodID, nRecvDataLen); //设置recvbuf长度

			jfieldID fdRcvDataBuf = g_cbData.m_pEnv->GetFieldID(cls, "recvIOData", "[B");
			jbyteArray objRecvDataBuf = (jbyteArray)g_cbData.m_pEnv->GetObjectField(obj, fdRcvDataBuf);
			
			SetByteArrayData(&objRecvDataBuf, (byte*)FetchIOData(pEvt), nRecvDataLen);
			//根据返回长度 new一个数组

			break;
		}

	case XMS_EVT_UNIFAILURE:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtUnifailureData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fdUnifailureData = g_cbData.m_pEnv->GetFieldID(cls, "unifailureData", "LDJKeygoe/Acs_UniFailure_Data;");
			jobject objUnifailureData = g_cbData.m_pEnv->GetObjectField(obj, fdUnifailureData);
			
			SetData_Unifailure((Acs_UniFailure_Data *)(FetchEventData(pEvt)), &objUnifailureData);

			break;
		}

	case XMS_EVT_SS7RawFrame:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtSS7RawFrameData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsSS7RawFrameData", "LDJKeygoe/Acs_SS7RawFrame_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_SS7RawFrame((Acs_SS7RawFrame_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_CTBUS_CLK_REF_SRC_STATE:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtCtBusClkRefSrcStateData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsClockStateData", "LDJKeygoe/ACS_Clock_RefSrc_State_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_ClockRefSrcState((ACS_Clock_RefSrc_State_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_3G324M:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvt3G324MData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acs3G324Data", "LDJKeygoe/Acs_3G324_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_3G324((Acs_3G324_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_3GVCONF_JOIN:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtJoinTo3GVConfData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsJoinTo3GVConfData", "LDJKeygoe/Acs_JoinTo3GVConf_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_JoinTo3GVConf((Acs_JoinTo3GVConf_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_3GVCONF_LEAVE:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtLeaveFrom3GVConfData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsLeaveFrom3GVConfData", "LDJKeygoe/Acs_LeaveFrom3GVConf_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_LeaveFrom3GVConf((Acs_LeaveFrom3GVConf_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_3GVCONF_CLEAR:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtClear3GVConfData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsClear3GVConfData", "LDJKeygoe/Acs_Clear3GVConf_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_Clear3GVConf((Acs_Clear3GVConf_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_3GVCONF_GETLAYOUT:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtGetLayout3GVConfData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsGetLayoutData", "LDJKeygoe/Acs_GetLayout_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_GetLayout((Acs_GetLayout_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_3GVCONF_SETLAYOUT:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtSetLayout3GVConfData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsSetLayoutData", "LDJKeygoe/Acs_SetLayout_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_SetLayout((Acs_SetLayout_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_3GVCONF_GETVISIBLELIST:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtGetVisibleList3GVConfData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsGetVisibleListData", "LDJKeygoe/Acs_GetVisibleList_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_GetVisibleList((Acs_GetVisibleList_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_3GVCONF_SETVISIBLELIST:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtSetVisibleList3GVConfData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsSetVisibleListData", "LDJKeygoe/Acs_SetVisibleList_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_SetVisibleList((Acs_SetVisibleList_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_MASTER_STATE:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtMasterStateData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsMasterStateData", "LDJKeygoe/Acs_MasterState_Data;");

			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);

			SetData_MasterState((Acs_MasterState_Data*)(FetchEventData(pEvt)), &obj1);

			break;
		}

	case XMS_EVT_SLAVE_WORK_STATE:
		{
			jclass cls = g_cbData.m_pEnv->FindClass("DJKeygoe/DJEvtSlaveWorkStateData");
			
			jmethodID  mid = g_cbData.m_pEnv->GetMethodID(cls, "<init>", "()V");
			obj = g_cbData.m_pEnv->NewObject(cls, mid);
			
			jfieldID fd = g_cbData.m_pEnv->GetFieldID(cls, "acsSlaveWorkState", "LDJKeygoe/Acs_SlaveWorkState_Data;");
			jobject obj1 = g_cbData.m_pEnv->GetObjectField(obj, fd);
			
			SetData_SlaveWorkState((Acs_SlaveWorkState_Data *)(FetchEventData(pEvt)), &obj1);

			break;
		}

	default:
		{
			break;
		}
	}

	jclass jclsProcess = g_cbData.m_pEnv->GetObjectClass(g_cbData.m_objInterface);

	jmethodID jmidProcess = g_cbData.m_pEnv->GetMethodID(jclsProcess, "UserProcess", "(LDJKeygoe/Acs_Evt_t;Ljava/lang/Object;)V");

	g_cbData.m_pEnv->CallVoidMethod(g_cbData.m_objInterface, jmidProcess, objAcsEvt, obj); //回调Java函数

	g_cbData.mg_Jvm->DetachCurrentThread();

	LogInfo("Exit EvtHandler");
}