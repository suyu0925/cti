
package DJKeygoe;


public class DJAcsAPIDef {
	
	public native int XMS_acsOpenStream(int acsHandle, 
			  ServerID_t server,
			  byte u8AppID,
			  int u32SendQSize,
			  int u32RecvQSize,
			  int s32DebugOn,
			  Object privateData); 
	
	public native int XMS_acsCloseStream(int acsHandle,Object privateData);
	
	public native int XMS_acsSetMaster(int acsHandle,byte u8Master,Object privateData);
	
    public native int XMS_acsSetESR(int acsHandle, EsrFunc esr, int esrParam, int notifyAll); 
    
    public native int XMS_acsGetDeviceList(int acsHandle, Object privateData);
    
    public native int XMS_acsSetTimer(int acsHandle,int u32Elapse);
    
    public native int XMS_ctsOpenDevice(int acsHandle, DeviceID_t deviceID, Object privateData);
    
    public native int XMS_ctsCloseDevice(int acsHandle,DeviceID_t deviceID,Object privateData);
    
    public native int XMS_ctsResetDevice(int acsHandle,DeviceID_t deviceID,Object privateData);

    public native int XMS_ctsSetDevTimer(int acsHandle,DeviceID_t deviceID,int u32Elapse);
	
    public native int XMS_ctsGetDevState(int acsHandle,DeviceID_t deviceID,Object privateData);
			
    public native int XMS_ctsSetDevGroup(int acsHandle,DeviceID_t deviceID,Object privateData);	

    public native int XMS_ctsMakeCallOut(int acsHandle,DeviceID_t deviceID,byte callingID[],
										byte calledID[],Object privateData);
	
    ////obj作为byte数组,u16ParamDataSize为数组长度 ,obj作为对象,u16ParamDataSize忽略
    public native int XMS_ctsSetParam(int acsHandle,DeviceID_t deviceID,short u16ParamCmdType, short u16ParamDataSize, Object obj);

    public native int XMS_ctsGetParam(int acsHandle,DeviceID_t deviceID,short u16ParamCmdType, short u16ParamDataSize, Object obj);
	
    public native int XMS_ctsAlertCall(int acsHandle,DeviceID_t deviceID,Object privateData);

    public native int XMS_ctsAnswerCallIn(int acsHandle,DeviceID_t deviceID,Object privateData);
	
    public native int XMS_ctsLinkDevice(int acsHandle,DeviceID_t srcDeviceID,DeviceID_t destDeviceID,Object privateData);
	
    public native int XMS_ctsUnlinkDevice(int acsHandle,DeviceID_t srcDeviceID,DeviceID_t destDeviceID,Object privateData);
		
    public native int XMS_ctsClearCall(int acsHandle, DeviceID_t deviceID,int s32ClearCause,Object privateData);
	
    public native int XMS_ctsJoinToConf(int acsHandle,DeviceID_t confDeviceID,DeviceID_t mediaDeviceID, CmdParamData_Conf_t confParam, Object privateData);

    public native int XMS_ctsLeaveFromConf(int acsHandle,DeviceID_t confDeviceID,DeviceID_t mediaDeviceID,CmdParamData_Conf_t confParam,Object privateData);

    public native int XMS_ctsClearConf(int acsHandle,DeviceID_t confDeviceID,Object privateData);

    public native int XMS_ctsPlay(int acsHandle,DeviceID_t mediaDeviceID,
								PlayProperty_t playProperty,Object privateData);

    public native int XMS_ctsInitPlayIndex(int acsHandle,DeviceID_t mediaDeviceID,Object privateData);

    public native int XMS_ctsBuildPlayIndex(int acsHandle,DeviceID_t mediaDeviceID,PlayProperty_t playProperty,Object privateData);

    public native int XMS_ctsControlPlay(int acsHandle,DeviceID_t mediaDeviceID,
								ControlPlay_t controlPlay,Object privateData);
	
    public native int XMS_ctsRecord(int acsHandle,DeviceID_t mediaDeviceID,
								RecordProperty_t recordProperty,Object privateData);
	
    public native int XMS_ctsControlRecord(int acsHandle,DeviceID_t mediaDeviceID,
								ControlRecord_t controlRecord,Object privateData);
	
    //����T38
    public native int XMS_ctsSendFax(int acsHandle,DeviceID_t faxDeviceID,DeviceID_t mediaDeviceID,
							    byte s8TiffFile[],byte s8LocalID[],Object privateData);
	
    public native int XMS_ctsStopSendFax(int acsHandle,DeviceID_t faxDeviceID,Object privateData);
	
    public native int XMS_ctsReceiveFax(int acsHandle,DeviceID_t faxDeviceID,DeviceID_t mediaDeviceID,
							    byte s8TiffFile[],byte s8LocalID[],Object privateData);
	
    public native int XMS_ctsStopReceiveFax(int acsHandle,DeviceID_t faxDeviceID,Object privateData);
	
    public native int XMS_ctsChangeMonitorFilter(int acsHandle,DeviceID_t deviceID,int monitorFilter,Object privateData);	

   /* u16IoType    O �����������
    * u16IoDataLen O ������ݳ���
    * g_SendIOData O Ҫ���͵���ݻ�����
    * */
    public native int XMS_ctsSendIOData(int acsHandle,DeviceID_t deviceID,short u16IoType,short u16IoDataLen, byte g_SendIOData[]);

    public native int XMS_ctsSendSignalMsg(int acsHandle,DeviceID_t deviceID,short u16SignalMsgType);

    public native int XMS_acsOpenStreamExt(int acsHandle,ServerID_t serverID,Object privateData);

    public native int XMS_acsCloseStreamExt(int acsHandle,ServerID_t serverID,Object privateData);

    public native int XMS_ctsPlayCSP(int acsHandle,DeviceID_t mediaDeviceID,CSPPlayProperty_t  cspPlayProperty,Object privateData);

    public native int XMS_ctsSendCSPData(int acsHandle,DeviceID_t mediaDeviceID,CSPPlayDataInfo_t cspDataInfo, byte cspData[], Object privateData);

    public native int XMS_ctsControlPlayCSP(int acsHandle,DeviceID_t mediaDeviceID,ControlPlay_t controlPlay,Object privateData);

    public native int XMS_ctsRecordCSP(int acsHandle,DeviceID_t mediaDeviceID,
								RecordCSPProperty_t recCSPProperty,Object privateData);
	
    public native int XMS_ctsControlRecordCSP(int acsHandle,DeviceID_t mediaDeviceID,
								ControlRecord_t controlRecord,Object privateData);

    public native int XMS_ctsInitPlay3gppIndex(int acsHandle,DeviceID_t mediaDeviceID,Object privateData);

    public native int XMS_ctsBuildPlay3gppIndex(int acsHandle,DeviceID_t mediaDeviceID,
										   Play3gppProperty_t playProperty,Object privateData);

    public native int XMS_cts3gppPlay(int acsHandle,DeviceID_t mediaDeviceID,
								Play3gppProperty_t playProperty,Object privateData);

    public native int XMS_ctsControl3gppPlay(int acsHandle,DeviceID_t mediaDeviceID,
								Control3gppPlay_t controlPlay,Object privateData);
	
    public native int XMS_cts3gppRecord(int acsHandle,DeviceID_t mediaDeviceID,
								Record3gppProperty_t recordProperty,Object privateData);
	
    public native int XMS_ctsControl3gppRecord(int acsHandle,DeviceID_t mediaDeviceID,
								Control3gppRecord_t controlRecord,Object privateData);
    public native int XMS_acsQueryLicense(int acsHandle,DeviceID_t deviceID,Object privateData);
    public native int XMS_ctxRegister(int acsHandle,byte s8AppRegName[],byte u8RegType,Object privateData);

    public native int XMS_ctxLink(int acsHandle,DeviceID_t srcDev,DeviceID_t destDev,byte u8Option,Object privateData);

    public native int XMS_ctxSendAppData(int acsHandle,byte s8SrcAppRegName[],byte s8DestAppRegName[],
									byte u8AppReqType,byte pData[],int u32DataSize,
									byte u8SrcAppUnitID,byte u8DestAppUnitID,
									DeviceID_t srcDevice,Object privateData);

    public native int XMS_ctsSendRawFrame(int acsHandle,DeviceID_t deviceID, short u16FrameSize,byte pData[]);
	
    public native int XMS_ctsJoinTo3GVConf(int acsHandle, DeviceID_t device3GVConfID, 
						DeviceID_t deviceID, Acs_MediaEx_Input_V input, Acs_MediaEx_Output_V output, 
						byte u8Visible, Object privateData);
						
    public native int XMS_ctsLeaveFrom3GVConf(int acsHandle, DeviceID_t device3GVConfID, DeviceID_t deviceID, Object privateData);
	
    public native int XMS_ctsClear3GVConf(int acsHandle, DeviceID_t device3GVConfID, Object privateData);
	
    public native int XMS_ctsGetLayout(int acsHandle, DeviceID_t device3GVConfID, Object privateData);
	
    public native int XMS_ctsSetLayout(int acsHandle, DeviceID_t device3GVConfID, Acs_3GVConf_LayoutList layoutList, Object privateData);
	
    public native int XMS_ctsGetVisibleList(int acsHandle, DeviceID_t device3GVConfID, Object privateData);
	
    public native int XMS_ctsSetVisibleList(int acsHandle, DeviceID_t device3GVConfID, Acs_3GVConf_VisibleList visableList, Object privateData);

    public native int XMS_ctsPutTextInPicture(int acsHandle, byte s8DstFile[], PutTextInPicture_Param paramItem, int u32ParamSum, Object privateData);

    public native int XMS_ctsRestart3GVConf(int acsHandle, DeviceID_t device3GVConfID, Object privateData);

    public native int XMS_acsGetRelateMod(int acsHandle,byte u8ModType,byte u8UnitID);
	
    public native int XMS_ctsPutUsrEvt(int acsHandle,DeviceID_t deviceID, UserEvt_Head_t pUserEvt);

    public native int XMS_acsLedCtrl(int acsHandle, byte u8DspUnitID, UserLedCtrl pLedCtrl);
    
    static {
        System.loadLibrary("DJAcsApiJava");
    }
}