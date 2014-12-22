unit DJAcsCmdDef;

interface

uses
  SysUtils,Windows,DJAcsDataDef;

Type ACS_CMD_TYPE = 
(
	ACS_CMD_TYPE_GETDEVLIST  = $01,
	ACS_CMD_TYPE_OPENDEVICE,
	ACS_CMD_TYPE_CLOSEDEVICE,
	ACS_CMD_TYPE_RESETDEVICE,
	ACS_CMD_TYPE_GETDEVICESTATE,
	ACS_CMD_TYPE_SETDEVGROUP,	
	ACS_CMD_TYPE_SETDEVPARAM,	
	ACS_CMD_TYPE_GETDEVPARAM,	
	ACS_CMD_TYPE_MAKECALLOUT,
	ACS_CMD_TYPE_ALERTCALL,
	ACS_CMD_TYPE_ANSWERCALLIN,	
	ACS_CMD_TYPE_LINKDEV,
	ACS_CMD_TYPE_UNLINKDEV,	
	ACS_CMD_TYPE_CLEARCALL,
	ACS_CMD_TYPE_JOINTOCONF,
	ACS_CMD_TYPE_LEAVEFROMCONF,
	ACS_CMD_TYPE_CLEARCONF,
	ACS_CMD_TYPE_PLAYFILE,
	ACS_CMD_TYPE_INITPLAYINDEX,
	ACS_CMD_TYPE_BUILDPLAYINDEX,
	ACS_CMD_TYPE_CONTROLPLAY,
	ACS_CMD_TYPE_RECORDFILE,
	ACS_CMD_TYPE_CONTROLRECORD,
	ACS_CMD_TYPE_SENDFAX,
	ACS_CMD_TYPE_STOPSENDFAX,
	ACS_CMD_TYPE_RECVFAX,
	ACS_CMD_TYPE_STOPRECVFAX,
	ACS_CMD_TYPE_CHANGEMONITORFILTER,	
	ACS_CMD_TYPE_SENDIO,	
	ACS_CMD_TYPE_SENDSIGMSG,
	ACS_CMD_TYPE_RECORDCSP,	
	ACS_CMD_TYPE_DBGON,
	ACS_CMD_TYPE_DBGOFF,    
  ACS_CMD_TYPE_PLAY_3GPP,
  ACS_CMD_TYPE_CONTROL_3GPP_PLAY,
  ACS_CMD_TYPE_RECORD_3GPP,
  ACS_CMD_TYPE_CONTROL_3GPP_RECORD,
	ACS_CMD_TYPE_PLAYCSP,
	ACS_CMD_TYPE_SENDPLAYCSP,
	ACS_CMD_TYPE_SETMASTER,
	ACS_CMD_TYPE_QUERYLIC,
	ACS_CMD_TYPE_CTXREG,
	ACS_CMD_TYPE_CTXLINK,
	ACS_CMD_TYPE_CTXSENDAPPDATA,
	ACS_CMD_TYPE_INIT3GPPINDEX,
	ACS_CMD_TYPE_BUILD3GPPINDEX,
	ACS_CMD_TYPE_SENDRAWFRAME,
	ACS_CMD_TYPE_JOIN3GCONF,
	ACS_CMD_TYPE_LEAVE3GCONF,
	ACS_CMD_TYPE_CLEAR3GCONF,
	ACS_CMD_TYPE_GET3GCONFLAYOUT,
	ACS_CMD_TYPE_SET3GCONFLAYOUT,
	ACS_CMD_TYPE_GET3GCONFVISABLE,
	ACS_CMD_TYPE_SET3GCONFVISABLE,
	ACS_CMD_TYPE_RESTART3GCONF
);

Type CTX_APPDATA_RET =
(
	CTX_APPDATA_RET_SUCCESS		= $0,
	CTX_APPDATA_RET_NODEST		= $4,
	CTX_APPDATA_RET_NOSRC  		= $5,
	CTX_APPDATA_DEST_RECVOK   = $FF
);

Type
  Acs_Cmd_t = record
	m_s32AcsHandle : Integer;       //*acs handle*/
	m_ITPDeviceID  : DeviceID_t;    //*Device id*/
	m_s32CmdType   : Integer;       //*command type*/
	m_s8PackName   : Array[0..63] of ShortInt;  //*parmeter name*/
	m_s32PackSize  : Integer;       //*parmeter size*/
	m_u8AcsId      : Byte;          //*acs server use*/
	m_Rfu1         : Array[0..2] of ShortInt;
end;

Type
  ACS_CMD_HEAD = record
	m_ITPPkgCmdHead : PKG_HEAD_STRUCT;   //ITP package head*/
	m_ITPAcsCmd_t   : Acs_Cmd_t;         //acs command package head*/
end;

Type
  SetMasterParm_t = record
	m_u8Master    : Byte;
	m_u8AppUnitID : Byte;
	m_Rfu1        : Array[0..1] of ShortInt;
end;

Type
  OpenDevParm_t = record
	m_s32Resrv : Integer; //*Reserved*/
end;

Type
  CloseDevParm_t = record
	m_s32Resrv : Integer; //*Reserved*/
end;

Type
  ResetDevParm_t = record
	m_s32Resrv : Integer; //*Reserved*/
end;

Type
  GetDevStateParm_t = record
	m_s32Resrv : Integer; //*Reserved*/
end;

Type
  SetDevGroupParm_t = record
	m_s32Resrv : Integer; //*Reserved*/
end;

Type
  CalloutParm_t = record
	m_s8CallingNum : Array[0..ACS_MAX_CALL_NUM-1] of ShortInt; //*calling id*/
	m_s8CalledNum  : Array[0..ACS_MAX_CALL_NUM-1] of ShortInt; //*called id*/
end;

Type
  SetParm_t = record
	m_u16ParamCmdType  : Word;
	m_u16ParamDataSize : Word;
end;

Type
  GetParm_t = record
	m_u16ParamCmdType  : Word;
	m_u16ParamDataSize : Word;
end;

Type
  AlertCallParm_t = record
	m_s32Resrv : Integer; //*Reserved*/
end;

Type
  AnswerCallInParm_t = record
	m_s32Resrv : Integer; //*Reserved*/
end;

Type
  LinkDevParm_t = record
	m_ITPDestDeviceID : DeviceID_t; //*Device id*/
end;


Type
  UnlinkDevParm_t = record
	m_ITPDestDeviceID : DeviceID_t; //*Device id*/
end;

Type
  XMSCtxRegParm_t = record
	m_s8RegName   : Array[0..XMS_MAX_REGNAME_LEN-1] of ShortInt; //*Reg Name*/
	m_u8RegType   : Byte;                                        //*1:Reg; 2: unReg,reference XMS_CTX_REG_TYPE*/
	m_u8AcsUnitID : Byte;
	m_Rfu1        : Array[0..1] of ShortInt;
	m_s32Rst      : Integer;
end;


Type
  XMSCtxLinkParm_t = record
	m_u8CtxLinkOpt : Byte; //*link option,reference CTX_LINK_OPTION*/
	m_u8AcsUnitID  : Byte;
	m_Rfu1    : Array[0..1] of ShortInt;
	m_srcDev  : DeviceID_t;
	m_destDev : DeviceID_t;
	m_s32Rst  : Integer;
end;

Type
  XMS_AppData_Info_t = record
	m_u32AppDataSize : DWORD; //*user APP data size,not include XMS_AppData_Info_t*/
	m_u8AppReqType   : Byte;  //*user APP req cmd type,user self define*/
	m_u8AcsUnitID    : Byte;
	m_Rfu1           : Array[0..1] of Byte;
	m_s8SrcRegName   : Array[0..XMS_MAX_REGNAME_LEN-1] of ShortInt; //*src reg name*/
	m_s8DestRegName  : Array[0..XMS_MAX_REGNAME_LEN-1] of ShortInt; //*dest reg name*/
	m_u8SrcAppUnitID : Byte;
	m_u8DstAppUnitID : Byte;
	m_Rfu2           : Array[0..1] of ShortInt;
	m_srcDevice      : DeviceID_t;
	m_Rfu3           : Array[0..19] of ShortInt;
	m_s32Rst         : Integer;
end;

Type
  ClearCallParm_t = record
	m_s32ClearCause : Integer;
	m_s32Resrv : Integer;
end;

Type
  JoinToConfParm_t = record
	m_ITPMediaDevice : DeviceID_t;           //*media device*/
  m_ITPConfParam   : CmdParamData_Conf_t;  //*Conf param*/
end;

Type
  LeaveFromConfParm_t = record
	m_ITPMediaDevice : DeviceID_t;          //*media device*/
	m_ITPConfParam   : CmdParamData_Conf_t; //*Conf param*/
end;

Type
  ClearConfParm_t = record
  m_s32Resrv : Integer;  //*Reserved*/
end;

Type
  PlayParm_t = record
	m_PlayProperty : PlayProperty_t;   //*playProperty*/
end;

Type
  InitPlayIndexParm_t  =record
	m_s32Reserved : Integer;
end;

Type
  BuildPlayIndexParm_t  =record
	m_ITPPlayProperty : PlayProperty_t;
end;

Type
  ControlPlayParm_t = record
	m_ITPControlPlay : ControlPlay_t; //*control play parmeter*/
end;

Type
  RecordParm_t = record
	m_ITPRecordProperty : RecordProperty_t; //*record property set*/
end;

Type
  ControlRecordParm_t = record
	m_ITPControlRecord : ControlRecord_t; //*control record set*/
end;

Type
  RecordCSPParm_t = record
	m_ITPRecordCSPProperty : RecordCSPProperty_t; //*record CSP property set*/
end;

const		ITP_MAX_STREAM_DATA_LENGTH		 = 4000;

Type
  CSPPlayParm_t = record
	m_ITPCSPPlayProperty : CSPPlayProperty_t;     //*ITP csp play property*/
end;

Type
  CSPPlaySendDataParm_t = record
	m_ITPPkgCmdHead   : PKG_HEAD_STRUCT;      //*ITP package head*/
	m_CspPlayDataInfo : CSPPlayDataInfo_t;          //*csp play data info*/
	m_u8StreamData    : Array[0..ITP_MAX_STREAM_DATA_LENGTH-1] of Byte;	//*stream data*/
end;

Type
  MonitorFilterParm_t = record
	m_u32MonitorFilter : DWORD; //*event monitor filter,reference ACS_IOEVT_MASK*/
end;

Type
  SendIOParm_t = record
  m_u16IoType    : Word;  //*io proc type*/
	m_u16IoDataLen : Word;  //*io data len*/
end;

Type
  SendSigMsgParm_t = record
  m_u16SigMsgType : Word;     //*Signal Msg Type*/
	m_s8Rfu         : Array[0..1] of ShortInt;          //*Rfu*/
end;

Type
  FaxHandShake_t = record
	m_u8Handshake_Result : Byte;  //*T30 handshake result*/
	m_u8Local_ID         : Array[0..19] of Byte;
	m_u8Remote_ID        : Array[0..19] of Byte;
	m_u8Modem_Type       : Byte;	//*F144_MODEM,F96_MODEM,F48_MODEM*/
	m_u8Fax_Speed        : Byte;  //*2400,4800,7200,9600,12000,14400*/
	m_u8Dencity          : Byte;	//*T4_LOW_DENSITY or T4_HIGH_DENSITY*/
	m_u8Encode_Type      : Byte;  //*T4_MH_ENCODE or T4_MR_ENCODE or T6_ENCODE*/
	m_u8Line_Width       : Byte;
	m_u8Min_Scanline_Time: Byte; 	//*minimum scanline time in ms, 0 for no limit*/
	m_u8Page_Length      : Byte;
	m_u8Ecm_Support      : Byte;	//*ECM_SUPPORT or ECM_UNSUPPORT*/
	m_u8Host_Control     : Byte;  //host command
	m_u8Reserve          : Array[0..5] of Byte;
	m_u32Total_Page_Num  : DWORD; //total sending page num, set by Ap when sending fax
end;

Type
  FaxPageAttri_t = record
	m_u32PageNo      : DWORD;   //当前页的页号，从1开始
	m_u32ByteCount   : DWORD;   //当前页的总字节数
	m_u8YResolution  : Byte;	  //垂直分辨率，低分辨率0， 高分辨率1
	m_u8EncodeType   : Byte;    //MH 0， MR 1， MMR 2
	m_u8PageWidth    : Byte;	  //页宽0代表1728
	m_u8MinScanlineTime : Byte; //最小行扫描时间
	m_u32PageOffset  : DWORD;   //页数据偏移量
	m_u32FillOrder   : DWORD;   //字节的bit位顺序
	m_u32XResolution : DWORD;   //水平分辨率
	m_u32Reserve     : Array[0..9] of DWORD;    //保留
end;


Type
  FaxLocalSpec_t = record
	m_u8Modem_Type        : Byte;
	m_u8Fax_Speed         : Byte;
	m_u8Dencity           : Byte;
	m_u8Encode_Type       : Byte;
	m_u8Line_Width        : Byte;
	m_u8Min_Scanline_Time : Byte;
	m_u8Page_Length       : Byte;
	m_u8Ecm_Support       : Byte;
	m_u8Remote_ID         : Array[0..19] of Byte;
end;

Type
  FaxEndingParam_t = record
	m_u16Fax_Channel_ID             : Word; //Fax Chan
	m_u16Fax_End_Flag               : Word; //Fax end flag
	m_u8Last_Error_Code             : Byte;	//error code of last fax operation
	m_u8Last_Error_State            : Byte;	//error state of last fax operation
	m_u8Last_Send_T30_Command_State : Byte; //store the state the T30 command just sent
	m_u8Last_Rcv_T30_Command        : Byte;	//store the T30 command just received
	m_u16Total_Page_Num             : Word;	//total pages,send: sending total pages successfully  ;rev: receiving total pages successfully
  m_u8Remote_Id                   : Array[0..19] of Byte;
end;

Type
  FaxRemoteSepc_t = record
	m_u8Modem_Type        : Byte;		//F144_MODEM,F96_MODEM,F48_MODEM
	m_u8Fax_Speed         : Byte;		//BPS_14400,BPS_12000,BPS_9600,BPS_7200,BPS_4800,BPS_2400
	m_u8Dencity           : Byte;		//T4_LOW_DENSITY or T4_HIGH_DENSITY
	m_u8Encode_Type       : Byte;	  //T4_MH_ENCODE or T4_MR_ENCODE or T6_ENCODE
	m_u8Line_Width        : Byte;		//see line width list
	m_u8Min_Scanline_Time : Byte; 	//minimum scanline time in ms, 0 for no limit
	m_u8Page_Length       : Byte;		//
	m_u8Ecm_Support       : Byte;	  //ECM_SUPPORT or ECM_UNSUPPORT
end;

Type
  Fax_Page_t = record
	m_u16Total_Page_Num      : Word;   //总共需要发送的页数
	m_u16Send_EOM_Flag       : Word;   //页后控制
	m_u32Current_Page_Offset : DWord;  //页偏移
	m_u32Current_Page_Bytes  : DWord;	 //当前页的字节数
end;

Type
  SendFaxParm_t = record
	m_s8LocalID        : Array[0..ACS_LOCALID_MAX_LEN-1] of ShortInt; //*Local ID*/
	m_s8FaxTiffFile    : Array[0..MAX_PATH-1] of ShortInt;            //*fax tiff file*/
	m_ITPMediaDeviceID : DeviceID_t;                                  //*Media deviceID*/
end;

Type
  StopSendFaxParm_t = record
	m_s8Rfu1 : Array[0..3] of ShortInt; //*Reserved*/
end;

Type
  RecvFaxParm_t = record
	m_s8LocalID        : Array[0..ACS_LOCALID_MAX_LEN-1] of ShortInt; //*fax Local ID*/
	m_s8FaxTiffFile    : Array[0..MAX_PATH-1] of ShortInt;            //*fax tiff file*/
	m_ITPMediaDeviceID : DeviceID_t;                                  //*media deviceID*/
end;

Type
  StopRecvFaxParm_t = record
	m_s8Rfu1 : Array[0..3] of ShortInt; //*Reserved*/
end;

Type
  InitPlay3gppIndexParm_t = record
	m_s32Reserved : Integer;
end;

Type
  BuildPlay3gppIndexParm_t = record
	m_ITPPlayProperty : Play3gppProperty_t;
end;

Type
  Play3gppParm_t = record
	m_PlayProperty : Play3gppProperty_t;   //*Play3gppProperty_t*/
end;

Type
  Control3gppPlayParm_t = record
	m_ITPControlPlay : Control3gppPlay_t; //*control play parmeter*/
end;

Type
  Record3gppParm_t = record
	m_ITPRecordProperty : Record3gppProperty_t; //*record property set*/
end;

Type
  Control3gppRecordParm_t = record
	m_ITPControlRecord : Control3gppRecord_t; //*control record set*/
end;

Type
  QueryLicenseParm_t = record
	m_u8ModuleID : Byte; //*Board module ID*/
	m_Rfu1       : Array[0..2] of ShortInt;
end;

Type
  SendRawFrameParm_t = record
	m_u16FrameSize : Word;
	m_Rfu1         : Word;
end;

Type
  JoinTo3GVConfParm_t = record
	m_device    : DeviceID_t;
	m_input     : Acs_MediaEx_Input_V;
	m_output    : Acs_MediaEx_Output_V;
	m_u8Visible : Byte;
end;

Type
  LeaveFrom3GVConfParm_t = record
	m_device : DeviceID_t;
end;

Type
  Clear3GVConfParm_t = record
	m_s32Reserved : Integer;
end;

Type
  GetLayoutParm_t = record
	m_s32Reserved : Integer;
end;

Type
  SetLayoutParm_t = record
	m_list : Acs_3GVConf_LayoutList;
end;

Type
  GetVisibleListParm_t = record
	m_s32Reserved : Integer;
end;

Type
  SetVisibleListParm_t = record
	m_list : Acs_3GVConf_VisibleList;
end;

Type
  Restart3GVConfParm_t = record
	m_s32Reserved : Integer;
end;

Type
  QueryDevLinkParm_t = record
	m_ITPDevice : DeviceID_t;
end;

Type
  Syn_OpenDev = record
	m_AcsCmd   : Acs_Cmd_t;
	m_TrunkDev : DeviceID_t;
	m_CtxDev   : DeviceID_t;
end;

Type
  SS7_Syn_CallIn = record
	m_s8Caller                 : Array[0..31] of ShortInt;
	m_s8Called                 : Array[0..31] of ShortInt;
	m_s32CallingPartCategory   : Integer;
	m_s32NatureOfCallerAddress : Integer;
	m_s32NatureOfCalledAddress : Integer;
	m_s32iAnswerType           : Integer;
	m_s32iCallOUTorIN          : Integer;
end;

Type
  SS7_Syn_CallOut = record
	m_s32iCallOutResult : Integer;
	m_s32iCallOUTorIN : Integer;
end;

Type
  Acs_DevSub_Info  =record
	m_s16DeviceSub : SmallInt;
	m_s16StartTs   : SmallInt;
	m_s16DeviceNum : SmallInt;
	m_Rfu1         : SmallInt;
end;

Type
  Acs_Dev_Info = record
	m_s8MachID      : ShortInt;
	m_s8ModuleID    : ShortInt;
	m_s16DeviceMain : SmallInt;
	m_s16DevSubNum  : SmallInt;
	m_Rfu1          : SmallInt;
	m_DevSub        : Array[0..127] of Acs_DevSub_Info;
end;

Type
  Acs_Cmd_Parm = record
  case Integer of
	1:(m_ITPAcsCloseDevParm       : CloseDevParm_t);          //*Close device parm*/
	2:(m_ITPAcsResetDevParm       : ResetDevParm_t);          //*Reset device parm*/
	3:(m_ITPAcsGetDevStateParm    : GetDevStateParm_t);       //*Get device state parm*/
	4:(m_ITPAcsSetDevGrpParm      : SetDevGroupParm_t);       //*set device group parm*/
	5:(m_ITPAcsCallOutParm        : CalloutParm_t);           //*callout parm*/
	6:(m_ITPAcsSetParm            : SetParm_t);               //*set parm*/
	7:(m_ITPAcsGetParm            : GetParm_t);               //*get parm*/
	8:(m_ITPAcsAnSwerCallInParm   : AnswerCallInParm_t);      //*answer callin parm*/
	9:(m_ITPAcsLinkDevParm        : LinkDevParm_t);           //*Link device parm*/
	10:(m_ITPAcsUnlinkDevParm     : UnlinkDevParm_t);         //*Unlink device parm*/
	11:(m_ITPAcsClearCallParm     : ClearCallParm_t);         //*clear call parm*/
	12:(m_ITPAcsJoinToConfParm    : JoinToConfParm_t);        //*join to conf parm*/
	13:(m_ITPAcsLeaveConfParm     : LeaveFromConfParm_t);     //*Leave from conf parm*/
	14:(m_ITPAcsPlayParm          : PlayParm_t);              //*play file parm*/
	15:(m_ITPAcsInitPlayIndex     : InitPlayIndexParm_t);     //*Init play index*/
	16:(m_ITPAcsBuildPlayIndex    : BuildPlayIndexParm_t);    //*Build play idnex*/
	17:(m_ITPAcsCtrlPlayParm      : ControlPlayParm_t);       //*control play parm*/
	18:(m_ITPAcsRecordParm        : RecordParm_t);            //*record file parm*/
	19:(m_ITPAcsCtrlRecordParm    : ControlRecordParm_t);     //*control record parm*/
	20:(m_ITPAcsSendFaxParm       : SendFaxParm_t);           //*send  fax parm*/
	21:(m_ITPAcsStopSendFaxParm   : StopSendFaxParm_t);       //*stop send fax parm*/
	22:(m_ITPAcsRecvFaxParm       : SendFaxParm_t);           //* recv fax parm*/
	23:(m_ITPAcsStopRecvFaxParm   : StopRecvFaxParm_t);       //*stop recv fax parm*/
	24:(m_ITPAcsMonFilterParm     : MonitorFilterParm_t);     //*monitor filter parm*/
	25:(m_ITPAcsSendIoParm        : SendIOParm_t);            //*send io parm*/
	26:(m_ITPAcsPlay3gpParm       : Play3gppParm_t);          //*play 3gp file parm*/
	27:(m_ITPAcsCtrl3gpPlayParm   : Control3gppPlayParm_t);   //*control 3gp play parm*/
	28:(m_ITPAcsRecord3gpParm     : Record3gppParm_t);        //*record 3gp file parm*/
	29:(m_ITPAcsCtrl3gpRecordParm : Control3gppRecordParm_t); //*control 3gp record parm*/
  30:(m_ITPAcsOpenDevParm       : OpenDevParm_t);           //*open devcie parm*/
end;

Type
  Acs_Cmd = record
  m_ITPAcsCmdHead : ACS_CMD_HEAD;
  m_CmdParm       : Acs_Cmd_Parm;
  m_ITPPrivateData: PrivateData_t;
  end;

implementation

end.
