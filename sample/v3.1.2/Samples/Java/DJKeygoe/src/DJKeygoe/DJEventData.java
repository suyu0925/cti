package DJKeygoe;

public class DJEventData {

}

/*
 * API返回事件及该事件所带回的数据结构。
 * 举例：参考《Keygoe系统编程接口参考》XMS_EVT_OPENSTREAM事件返回数据Acs_Evt_t和Acs_GeneralProc_Data，
 * XMS_EVT_OPENSTREAM返回数据对应的结构是DJEvtOpenStreamData。
 * 对于有些事件不同的设备所返回的数据不同，例如XMS_EVT_CALLIN,如果是Voip呼叫返回的事件包括Acs_Evt_t
 * Acs_CallControl_Data和VoIPCallPrivate_t。如果是其它设备呼叫VoIPCallPrivate_t没有数据。
 * */
class DJEvtOpenStreamData{ //XMS_EVT_OPEN_STREAM data
	public Acs_GeneralProc_Data acsGenerProcData = new Acs_GeneralProc_Data();
}

class DJEvtQueryDeviceData{ //XMS_EVT_QUERY_DEVICE
	public Acs_Dev_List_Head_t acsDevListHead = new Acs_Dev_List_Head_t();
	public DeviceID_t device[] = new DeviceID_t[128];
	
	public DJEvtQueryDeviceData(){
		for (int i = 0; i < 128; i++){
			device[i] = new DeviceID_t();
		}
	}
}

class DJEvtOpenDeviceData{ //XMS_EVT_OPENDEVICE
	public Acs_GeneralProc_Data acsGenerProcData = new Acs_GeneralProc_Data();
}

class DJEvtCloseDeviceData{ //XMS_EVT_CLOSEDEVICE
	public Acs_GeneralProc_Data acsGenerProcData = new Acs_GeneralProc_Data();
}

class DJEvtDeviceStateData{//XMS_EVT_DEVICESTATE
	public Acs_GeneralProc_Data acsGenerProcData = new Acs_GeneralProc_Data();
}

class DJEvtResetDeviceData{// XMS_EVT_RESETDEVICE
	public Acs_GeneralProc_Data acsGenerProcData = new Acs_GeneralProc_Data();
}

class DJEvtSetDevGroupData{ //XMS_EVT_SET_DEVGROUP
	public Acs_GeneralProc_Data acsGenerProcData = new Acs_GeneralProc_Data();
}

class DJEvtSetParamData{ //XMS_EVT_SETPARAM
	public Acs_ParamProc_Data acsParamProcData = new Acs_ParamProc_Data();
}

class DJEvtGetParamData{ //XMS_EVT_GETPARAM
	public Acs_ParamProc_Data acsParamProcData = new Acs_ParamProc_Data();
	
	//调用XMS_ctsGetParam，返回XMS_EVT_GETPARAM事件，根据设备类型及cmdtype区分，具体返回的数据是什么类型
	public Acs_VoIP_RTPCODEC acsDataRtpCodec = new Acs_VoIP_RTPCODEC(); //devicemain = voip
	public CmdParamData_3GPP_t acsData3Gpp = new CmdParamData_3GPP_t(); //devicemain=voice
	public Acs_ParamData_UserReadXmsBoardInfo acsDataBoard = new Acs_ParamData_UserReadXmsBoardInfo(); // devicemain=board
	public CmdParamConf_MemberState_t acsDataConf = new CmdParamConf_MemberState_t(); //devmain=conference
	public CmdParamData_ReadSn_t acsDataReadSn = new CmdParamData_ReadSn_t(); //devmain=XMS_DEVMAIN_INTERFACE_CH
	public CmdParamData_ReadVoltage_t acsDataReadVolteage = new CmdParamData_ReadVoltage_t(); //devmain=XMS_DEVMAIN_INTERFACE_CH
	public byte OriginalNum[] = new byte[256]; //cmdtype=ISDN_PARAM_ORINUMBER
	
}

class DJEvtLicenseQueryData { //XMS_EVT_LICENSE_QUERY
	public Acs_LicenseQuery_Data acsLicenseQueryData = new Acs_LicenseQuery_Data();
}

class DJEvtModRelateData{ //XMS_EVT_MODRELATE
	public Acs_ModRelate_Data acsModRelateData = new Acs_ModRelate_Data();
}

class DJEvtCallInData{ //XMS_EVT_CALLIN
	public Acs_CallControl_Data acsCallInData = new Acs_CallControl_Data();
	public VoIPCallPrivate_t voipCallInData = new VoIPCallPrivate_t();//如果Voip设备的呼叫 voipCallData包括呼叫协议 主叫地址
}

class DJEvtCallOutData{ //XMS_EVT_CALLOUT
	public Acs_CallControl_Data acsCallOutData = new Acs_CallControl_Data();
	public VoIPCallPrivate_t voipCallOutData = new VoIPCallPrivate_t();//如果Voip设备的呼叫 voipCallData包括呼叫协议 主叫地址
}

class DJEvtAlertCallData{ //XMS_EVT_ALERTCALL
	public Acs_CallControl_Data acsAlertCallData = new Acs_CallControl_Data();
}

class DJEvtAnswerCallData{ //XMS_EVT_ANSWERCALL
	public Acs_CallControl_Data acsAnswerCallData = new Acs_CallControl_Data(); 
}

class DJEvtLinkDeviceData{ //XMS_EVT_LINKDEVICE
	public Acs_LinkDev_Data acsLinkDevData = new Acs_LinkDev_Data();
}

class DJEvtUnLinkDeviceData{ //XMS_EVT_UNLINKDEVICE
	public Acs_LinkDev_Data acsUnLinkDevData = new Acs_LinkDev_Data();
}

class DJEvtClearCallData{ //XMS_EVT_CLEARCALL
	public Acs_CallControl_Data acsClearCallData = new Acs_CallControl_Data();
}

class DJEvtAnalogInterfaceData{ //XMS_EVT_ANALOG_INTERFACE 
	public Acs_AnalogInterface_Data acsAngInfaceData = new Acs_AnalogInterface_Data();
}

class DJEvtSendSigMsgData{ //XMS_EVT_SENDSIGMSG
	public Acs_SendSigMsg_Data acsSendSigMsgData = new Acs_SendSigMsg_Data();
}

class DJEvtSigMonData{ //XMS_EVT_SIGMON
	public Acs_SigMon_Data acsSigMonData = new Acs_SigMon_Data();
}

class DJEvtCtxRegData{ //XMS_EVT_CTX_REG
	public Acs_CtxReg_Data acsCtxRegData = new Acs_CtxReg_Data();
}

class DJEvtCtxLinkData{ //XMS_EVT_CTX_LINK
	public Acs_CtxLink_Data acsCtxLinkData = new Acs_CtxLink_Data();
}

class DJEvtCtxAppData{ //XMS_EVT_CTX_APPDATA
	public Acs_CtxAppData_Info ctxAppDataInfo = new Acs_CtxAppData_Info();
}

class DJEvtJoinToConfData{ //XMS_EVT_JOINTOCONF
	public Acs_ConfControl_Data acsConfCtrlData = new Acs_ConfControl_Data();
}

class DJEvtLeaveFromConfData{ //XMS_EVT_LEAVEFROMCONF
	public Acs_ConfControl_Data acsConfCtrlData = new Acs_ConfControl_Data();
}

class DJEvtClearConfData{ //XMS_EVT_CLEARCONF
	public Acs_ConfControl_Data acsConfCtrlData = new Acs_ConfControl_Data();
}

class DJEvtPlayData{ //XMS_EVT_PLAY
	public Acs_MediaProc_Data acsMediaProcData = new Acs_MediaProc_Data();
}

class DJEvtInitIndexData{ //XMS_EVT_INITINDEX
	public Acs_MediaProc_Data acsMediaProcData = new Acs_MediaProc_Data();
}

class DJEvtBuildIndexData{ //XMS_EVT_BUILDINDEX
	public Acs_MediaProc_Data acsMediaProcData = new Acs_MediaProc_Data();
}

class DJEvtControlPlayData{ //XMS_EVT_CONTROLPLAY
	public Acs_MediaProc_Data acsMediaProcData = new Acs_MediaProc_Data();
}

class DJEvtRecordData{ //XMS_EVT_RECORD
	public Acs_MediaProc_Data acsMediaProcData = new Acs_MediaProc_Data(); 
}

class DJEvtControlRecordData{ //XMS_EVT_CONTROLRECORD
	public Acs_MediaProc_Data acsMediaProcData = new Acs_MediaProc_Data(); 
}

class DJEvtPlayCspReq{ //XMS_EVT_PLAYCSPREQ
	public Acs_CSPDataReq_Data acsCspDataReq = new Acs_CSPDataReq_Data();
}

class DJEvtRecordCsp{ //XMS_EVT_RECORDCSP
	public Acs_MediaCSPProc_Data acsMediaCspProcData = new Acs_MediaCSPProc_Data();
}

class DJEvt3gppPlayData{ // XMS_EVT_3GPP_PLAY
	public Acs_Media3GPPProc_Data acsMedia3gppProcData = new Acs_Media3GPPProc_Data();
}

class DJEvt3gppControlPlayData{ // XMS_EVT_3GPP_CONTROLPLAY
	public Acs_Media3GPPProc_Data acsMedia3gppProcData = new Acs_Media3GPPProc_Data();
}

class DJEvt3gppRecordData{ // XMS_EVT_3GPP_RECORD
	public Acs_Media3GPPProc_Data acsMedia3gppProcData = new Acs_Media3GPPProc_Data();
}

class DJEvt3gppControlRecordData{ // XMS_EVT_3GPP_CONTROLRECORD
	public Acs_Media3GPPProc_Data acsMedia3gppProcData = new Acs_Media3GPPProc_Data();
}

class DJEvt3gppInitIndex{ //XMS_EVT_3GPP_INIT_INDEX
	public Acs_MediaProc_Data acsMediaProcData = new Acs_MediaProc_Data();
}

class DJEvt3gppBuildIndexData{ // XMS_EVT_3GPP_BUILD_INDEX
	public Acs_Media3GPPProc_Data acsMedia3gppProcData = new Acs_Media3GPPProc_Data();
}

class DJEvtSendFaxData{ //XMS_EVT_SENDFAX
	public Acs_FaxProc_Data acsFaxProcData = new Acs_FaxProc_Data();
}

class DJEvtRecvFaxData{ //XMS_EVT_RECVFAX
	public Acs_FaxProc_Data acsFaxProcData = new Acs_FaxProc_Data();
}

class DJEvtSendIOData{ //XMS_EVT_SENDIODATA
	public Acs_IO_Data acsIOData = new Acs_IO_Data();
}

class DJEvtRecvIOData{ //XMS_EVT_RECVIODATA
	public Acs_IO_Data acsIOData = new Acs_IO_Data();
	public byte	recvIOData[]; //recv data buffer
	
	public DJEvtRecvIOData(int nDataLen){
		recvIOData = new byte[nDataLen+1];
	}
}

class DJEvtUnifailureData{ //XMS_EVT_UNIFAILURE
	public Acs_UniFailure_Data unifailureData = new Acs_UniFailure_Data();
}

class DJEvtSS7RawFrameData { //XMS_EVT_SS7RawFrame
	public Acs_SS7RawFrame_Data acsSS7RawFrameData = new Acs_SS7RawFrame_Data();
}

class DJEvtCtBusClkRefSrcStateData{ //XMS_EVT_CTBUS_CLK_REF_SRC_STATE
	public ACS_Clock_RefSrc_State_Data acsClockStateData = new ACS_Clock_RefSrc_State_Data();
}

class DJEvt3G324MData{ //XMS_EVT_3G324M
	public Acs_3G324_Data acs3G324Data = new Acs_3G324_Data();
}

class DJEvtJoinTo3GVConfData{ //XMS_EVT_3GVCONF_JOIN
	public Acs_JoinTo3GVConf_Data acsJoinTo3GVConfData = new Acs_JoinTo3GVConf_Data();
}

class DJEvtLeaveFrom3GVConfData{ //XMS_EVT_3GVCONF_LEAVE
	public Acs_LeaveFrom3GVConf_Data acsLeaveFrom3GVConfData = new Acs_LeaveFrom3GVConf_Data();
}

class DJEvtClear3GVConfData{ //XMS_EVT_3GVCONF_CLEAR
	public Acs_Clear3GVConf_Data acsClear3GVConfData = new Acs_Clear3GVConf_Data();
}

class DJEvtGetLayout3GVConfData{ //XMS_EVT_3GVCONF_GETLAYOUT
	public Acs_GetLayout_Data acsGetLayoutData = new Acs_GetLayout_Data();
}

class DJEvtSetLayout3GVConfData{ //XMS_EVT_3GVCONF_SETLAYOUT
	public Acs_SetLayout_Data acsSetLayoutData = new Acs_SetLayout_Data();
}

class DJEvtGetVisibleList3GVConfData{ //XMS_EVT_3GVCONF_GETVISIBLELIST
	public Acs_GetVisibleList_Data acsGetVisibleListData = new Acs_GetVisibleList_Data();
}

class DJEvtSetVisibleList3GVConfData{ //XMS_EVT_3GVCONF_SETVISIBLELIST
	public Acs_SetVisibleList_Data acsSetVisibleListData = new Acs_SetVisibleList_Data();
}

class DJEvtMasterStateData{ //XMS_EVT_MASTER_STATE
	public Acs_MasterState_Data acsMasterStateData = new Acs_MasterState_Data();
}

class DJEvtSlaveWorkStateData{ //XMS_EVT_SLAVE_WORK_STATE
	public Acs_SlaveWorkState_Data acsSlaveWorkState = new Acs_SlaveWorkState_Data();
}