using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;

namespace DJKeygoe
{
    using DJ_U8 = Byte;
    using DJ_S8 = SByte;
    using DJ_U16 = UInt16;
    using DJ_S16 = Int16;
    using DJ_U32 = UInt32;
    using DJ_S32 = Int32;
    using DJ_U64 = UInt64;
    using DJ_S64 = Int64;
    using DJ_UI32 = UInt32;
    using DJ_SI32 = Int32;
    using DJ_F64 = Double;
    using RetCode_t = Int32;
    using ACSHandle_t = UInt32;
    using InvokeID_t = Int32;
    using LoginID_t = SByte;
    using EventClass_t = Int32;
    using EventType_t = Int32;
    using ACSConfirmation_t = Int32;
    using CallNum_t = SByte;
    using AcsCmdTye_t = Int32;

    using FlowType_t = Int32;
    using FlowChannel_t = Int32;
    using DeviceMain_t = Int16;
    using DeviceSub_t = Int16;
    using DeviceGroup_t = Int16;
    using ModuleID_t = SByte;
    using ChannelID_t = Int16;
    using ParmName_t = SByte;
    using ParmSize_t = Int32;
    using Version_t = Int32;
    using ACSUniversalFailure_t = Int32;
    using PlayCont_t = SByte;
    using FilePath_t = SByte;

    using Acs_Evt_State_t = Int32;
    using Acs_Evt_ErrCode_t = Int32;
    using Acs_MediaProc_Dtmf_t = SByte;
    using DJ_SOCKET = UInt32;

    public class DJAcsApiDef
    {
        [UnmanagedFunctionPointer(System.Runtime.InteropServices.CallingConvention.Cdecl)] //指定该托管参数调用Cdecl
        public delegate void EsrFunc(UInt32 esrParam); //声明一个函数指针，XMS_acsSetESR调用的回调函数EsrFunc类型

        [DllImport("DJAcsAPI.dll")]
        public static extern RetCode_t XMS_acsSetESR(ACSHandle_t acsHandle, EsrFunc FuncPtr, DJ_U32 esrParam, DJ_S32 notifyAll);

        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_acsOpenStream(ACSHandle_t* acsHandle, ServerID_t* serverID, DJ_U8 u8AppID,
                                        DJ_U32 u32SendQSize, DJ_U32 u32RecvQSize, DJ_S32 s32DebugOn, PrivateData_t* privateData);

        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_acsCloseStream(ACSHandle_t acsHandle,PrivateData_t * privateData);

        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_acsSetMaster(ACSHandle_t acsHandle,DJ_U8 u8Master,PrivateData_t * privateData);

        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_acsGetDeviceList(ACSHandle_t acsHandle,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
	    public static extern RetCode_t XMS_acsSetTimer(ACSHandle_t acsHandle,DJ_U32 u32Elapse);

        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsOpenDevice(ACSHandle_t acsHandle,DeviceID_t * deviceID,PrivateData_t * privateData);

        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsCloseDevice(ACSHandle_t acsHandle,DeviceID_t * deviceID,PrivateData_t * privateData);

        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsResetDevice(ACSHandle_t acsHandle,DeviceID_t * deviceID,PrivateData_t * privateData);

        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsSetDevTimer(ACSHandle_t acsHandle,DeviceID_t * deviceID,DJ_U32 u32Elapse);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsGetDevState(ACSHandle_t acsHandle,DeviceID_t * deviceID,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsSetDevGroup(ACSHandle_t acsHandle,DeviceID_t * deviceID,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsMakeCallOut(ACSHandle_t acsHandle,DeviceID_t * deviceID,CallNum_t * callingID,
										CallNum_t * calledID,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsSetParam(ACSHandle_t acsHandle, DeviceID_t* deviceID, DJ_U16 u16ParamCmdType, DJ_U16 u16ParamDataSize, void* paramData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsGetParam(ACSHandle_t acsHandle, DeviceID_t* deviceID, DJ_U16 u16ParamCmdType, DJ_U16 u16ParamDataSize, void* paramData);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsAlertCall(ACSHandle_t acsHandle,DeviceID_t * deviceID,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsAnswerCallIn(ACSHandle_t acsHandle,DeviceID_t * deviceID,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsLinkDevice(ACSHandle_t acsHandle,DeviceID_t * srcDeviceID,DeviceID_t * destDeviceID,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsUnlinkDevice(ACSHandle_t acsHandle,DeviceID_t * srcDeviceID,DeviceID_t * destDeviceID,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsClearCall(ACSHandle_t acsHandle, DeviceID_t * deviceID,DJ_S32 s32ClearCause,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsJoinToConf(ACSHandle_t acsHandle,DeviceID_t * confDeviceID,DeviceID_t * mediaDeviceID, CmdParamData_Conf_t * confParam, PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsLeaveFromConf(ACSHandle_t acsHandle,DeviceID_t * confDeviceID,DeviceID_t * mediaDeviceID,CmdParamData_Conf_t * confParam,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsClearConf(ACSHandle_t acsHandle,DeviceID_t * confDeviceID,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsPlay(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,
								PlayProperty_t * playProperty,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsInitPlayIndex(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsBuildPlayIndex(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,PlayProperty_t * playProperty,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsControlPlay(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,
								ControlPlay_t * controlPlay,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
	    public unsafe static extern RetCode_t XMS_ctsRecord(ACSHandle_t acsHandle,DeviceID_t * mediaDeviceID,
								RecordProperty_t * recordProperty,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsControlRecord(ACSHandle_t acsHandle, DeviceID_t* mediaDeviceID,
								ControlRecord_t * controlRecord,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsSendFax(ACSHandle_t acsHandle, DeviceID_t* faxDeviceID, DeviceID_t* mediaDeviceID,
							    DJ_S8 * s8TiffFile,DJ_S8 * s8LocalID,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsStopSendFax(ACSHandle_t acsHandle, DeviceID_t* faxDeviceID, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsReceiveFax(ACSHandle_t acsHandle, DeviceID_t* faxDeviceID, DeviceID_t* mediaDeviceID,
							    DJ_S8 * s8TiffFile,DJ_S8 * s8LocalID,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsStopReceiveFax(ACSHandle_t acsHandle, DeviceID_t* faxDeviceID, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsChangeMonitorFilter(ACSHandle_t acsHandle, DeviceID_t* deviceID, DJ_U32 monitorFilter, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsSendIOData(ACSHandle_t acsHandle, DeviceID_t* deviceID, DJ_U16 u16IoType, DJ_U16 u16IoDataLen, DJ_U8* ioData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsSendSignalMsg(ACSHandle_t acsHandle, DeviceID_t* deviceID, DJ_U16 u16SignalMsgType);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_acsOpenStreamExt(ACSHandle_t acsHandle, ServerID_t* serverID, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_acsCloseStreamExt(ACSHandle_t acsHandle, ServerID_t* serverID, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsPlayCSP(ACSHandle_t acsHandle, DeviceID_t* mediaDeviceID, CSPPlayProperty_t* cspPlayProperty, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsSendCSPData(ACSHandle_t acsHandle, DeviceID_t* mediaDeviceID, CSPPlayDataInfo_t* cspDataInfo, DJ_U8* cspData, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsControlPlayCSP(ACSHandle_t acsHandle, DeviceID_t* mediaDeviceID, ControlPlay_t* controlPlay, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsRecordCSP(ACSHandle_t acsHandle, DeviceID_t* mediaDeviceID,
								RecordCSPProperty_t * recCSPProperty,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsControlRecordCSP(ACSHandle_t acsHandle, DeviceID_t* mediaDeviceID,
								ControlRecord_t * controlRecord,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsInitPlay3gppIndex(ACSHandle_t acsHandle, DeviceID_t* mediaDeviceID, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsBuildPlay3gppIndex(ACSHandle_t acsHandle, DeviceID_t* mediaDeviceID,
										   Play3gppProperty_t * playProperty,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_cts3gppPlay(ACSHandle_t acsHandle, DeviceID_t* mediaDeviceID,
								Play3gppProperty_t * playProperty,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsControl3gppPlay(ACSHandle_t acsHandle, DeviceID_t* mediaDeviceID,
								Control3gppPlay_t * controlPlay,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_cts3gppRecord(ACSHandle_t acsHandle, DeviceID_t* mediaDeviceID,
								Record3gppProperty_t * recordProperty,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsControl3gppRecord(ACSHandle_t acsHandle, DeviceID_t* mediaDeviceID,
								Control3gppRecord_t * controlRecord,PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_acsQueryLicense(ACSHandle_t acsHandle, DeviceID_t* deviceID, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctxRegister(ACSHandle_t acsHandle, DJ_S8* s8AppRegName, DJ_U8 u8RegType, PrivateData_t* privateData);

        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctxLink(ACSHandle_t acsHandle, DeviceID_t* srcDev, DeviceID_t* destDev, DJ_U8 u8Option, PrivateData_t* privateData);

        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctxSendAppData(ACSHandle_t acsHandle, DJ_S8* s8SrcAppRegName, DJ_S8* s8DestAppRegName,
									DJ_U8 u8AppReqType,DJ_U8 * pData,DJ_U32 u32DataSize,
									DJ_U8 u8SrcAppUnitID,DJ_U8 u8DestAppUnitID,
									DeviceID_t * srcDevice,PrivateData_t * privateData);

        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsSendRawFrame(ACSHandle_t acsHandle, DeviceID_t* deviceID, DJ_U16 u16FrameSize, DJ_U8* pData);

        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsJoinTo3GVConf(ACSHandle_t acsHandle, DeviceID_t* device3GVConfID, 
						DeviceID_t * deviceID, Acs_MediaEx_Input_V* input, Acs_MediaEx_Output_V* output, 
						DJ_U8 u8Visible, PrivateData_t * privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsLeaveFrom3GVConf(ACSHandle_t acsHandle, DeviceID_t* device3GVConfID, DeviceID_t* deviceID, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsClear3GVConf(ACSHandle_t acsHandle, DeviceID_t* device3GVConfID, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsGetLayout(ACSHandle_t acsHandle, DeviceID_t* device3GVConfID, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsSetLayout(ACSHandle_t acsHandle, DeviceID_t* device3GVConfID, Acs_3GVConf_LayoutList layoutList, PrivateData_t* privateData);
        //C++原型:RetCode_t WINAPI XMS_ctsSetLayout(ACSHandle_t acsHandle, DeviceID_t * device3GVConfID, Acs_3GVConf_LayoutList * layoutList, PrivateData_t * privateData);

        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsGetVisibleList(ACSHandle_t acsHandle, DeviceID_t* device3GVConfID, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsSetVisibleList(ACSHandle_t acsHandle, DeviceID_t* device3GVConfID, Acs_3GVConf_VisibleList visableList, PrivateData_t* privateData);
        //C++原型:RetCode_t WINAPI XMS_ctsSetVisibleList(ACSHandle_t acsHandle, DeviceID_t * device3GVConfID, Acs_3GVConf_VisibleList * visableList, PrivateData_t * privateData);

        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsPutTextInPicture(ACSHandle_t acsHandle, DJ_S8* s8DstFile, PutTextInPicture_Param* paramItem, DJ_U32 u32ParamSum, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsRestart3GVConf(ACSHandle_t acsHandle, DeviceID_t* device3GVConfID, PrivateData_t* privateData);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_acsGetRelateMod(ACSHandle_t acsHandle, DJ_U8 u8ModType, DJ_U8 u8UnitID);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_ctsPutUsrEvt(ACSHandle_t acsHandle, DeviceID_t* deviceID, UserEvt_Head_t* pUserEvt);
        
        [DllImport("DJAcsAPI.dll")]
        public unsafe static extern RetCode_t XMS_acsLedCtrl(ACSHandle_t acsHandle, DJ_U8 u8DspUnitID, UserLedCtrl* pLedCtrl);

    }
}