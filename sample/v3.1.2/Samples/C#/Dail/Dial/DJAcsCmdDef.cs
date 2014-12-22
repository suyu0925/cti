using System;
using System.Collections.Generic;
using System.Text;

using System.Runtime.InteropServices;

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
    
    public enum ACS_CMD_TYPE
    {	
	    ACS_CMD_TYPE_GETDEVLIST  = 0x01,
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
	    ACS_CMD_TYPE_RESTART3GCONF,
    };

    public enum CTX_APPDATA_RET
    {
	    CTX_APPDATA_RET_SUCCESS		= 0x0,
	    CTX_APPDATA_RET_NODEST		= 0x4,
	    CTX_APPDATA_RET_NOSRC  		= 0x5,
	    CTX_APPDATA_DEST_RECVOK     = 0xFF,
    };

    /*Acs_Cmd_t*/
    public unsafe struct Acs_Cmd_t
    {	
	    public ACSHandle_t               m_s32AcsHandle;    /*acs handle*/	
	    public DeviceID_t                   m_ITPDeviceID;      /*Device id*/
	    public AcsCmdTye_t               m_s32CmdType;      /*command type*/
	    public fixed ParmName_t       m_s8PackName[64];  /*parmeter name*/
	    public ParmSize_t                  m_s32PackSize;     /*parmeter size*/
	    public DJ_U8                          m_u8AcsId;         /*acs server use*/
	    public fixed DJ_S8                   m_Rfu1[3];
    };/*Acs_Cmd_t*/

    /*ACS Cmd Head*/
    public struct ACS_CMD_HEAD
    {
	    public PKG_HEAD_STRUCT  m_ITPPkgCmdHead;   /*ITP package head*/	
	    public Acs_Cmd_t        m_ITPAcsCmd_t;     /*acs command package head*/
    };/**/

    /*ACS set Master parm*/
    public unsafe struct SetMasterParm_t
    {
	    public DJ_U8    m_u8Master;
	    public DJ_U8    m_u8AppUnitID;
	    public fixed DJ_S8    m_Rfu1[2];
    };/**/

    /*ACS open device parm*/
    public struct OpenDevParm_t
    {
	    public DJ_S32   m_s32Resrv;/*Reserved*/
    };/**/

    /*ACS close device parm*/
    public struct CloseDevParm_t
    {
	    public DJ_S32      m_s32Resrv;/*Reserved*/
    };/**/

    public struct ResetDevParm_t
    {
	    public DJ_S32      m_s32Resrv;/*Reserved*/
    };/**/

    public struct GetDevStateParm_t
    {
	    public DJ_S32      m_s32Resrv;/*Reserved*/
    };/**/

    /*ACS set device group parm*/
    public struct SetDevGroupParm_t
    {
	    public DJ_S32      m_s32Resrv;/*Reserved*/
    };/**/

    /*ACS callout parm*/
    public unsafe struct CalloutParm_t
    {
        public fixed CallNum_t m_s8CallingNum[ConstantVar.ACS_MAX_CALL_NUM];/*calling id*/
        public fixed CallNum_t m_s8CalledNum[ConstantVar.ACS_MAX_CALL_NUM];/*called id*/
    };/**/

    public struct SetParm_t
    {	
	    public DJ_U16              m_u16ParamCmdType;
	    public DJ_U16              m_u16ParamDataSize;
    };/**/

    public struct GetParm_t
    {
	    public DJ_U16              m_u16ParamCmdType;
	    public DJ_U16              m_u16ParamDataSize;
    };/**/

    /*ACS callin parm*/
    public struct AlertCallParm_t
    {
	    public DJ_S32        m_s32Resrv;/*Reserved*/
    };/**/

    /*ACS callin parm*/
    public struct AnswerCallInParm_t
    {
	    public DJ_S32        m_s32Resrv;/*Reserved*/
    };/**/

    /*ACS Link Device parm*/
    public struct LinkDevParm_t
    {
	    public DeviceID_t   m_ITPDestDeviceID;/*Device id*/
    };/**/

    /*ACS UnLink parm*/
    public struct UnlinkDevParm_t
    {
	    public DeviceID_t   m_ITPDestDeviceID;/*Device id*/
    };/**/

    /*ACS XMS Reg parm*/
    public unsafe struct XMSCtxRegParm_t
    {
        public fixed DJ_S8   m_s8RegName[ConstantVar.XMS_MAX_REGNAME_LEN];/*Reg Name*/	
	    public DJ_U8           m_u8RegType;  /*1:Reg; 2: unReg,reference XMS_CTX_REG_TYPE*/
	    public DJ_U8           m_u8AcsUnitID;
	    public fixed DJ_S8   m_Rfu1[2];
	    public DJ_S32         m_s32Rst;
    };

    /*ACS XMS ctxlink parm*/
    public unsafe struct XMSCtxLinkParm_t
    {
	    public DJ_U8	                   m_u8CtxLinkOpt;/*link option,reference CTX_LINK_OPTION*/
	    public DJ_U8                   m_u8AcsUnitID;
	    public fixed DJ_S8           m_Rfu1[2];
	    public DeviceID_t            m_srcDev;
	    public DeviceID_t            m_destDev;
	    public DJ_S32                 m_s32Rst;
    };

    /*ACS App Data Info*/
    public unsafe struct XMS_AppData_Info_t
    {
	    public DJ_U32             m_u32AppDataSize; /*user APP data size,not include XMS_AppData_Info_t*/
	    public DJ_U8               m_u8AppReqType;   /*user APP req cmd type,user self define*/
	    public DJ_U8               m_u8AcsUnitID;
	    public fixed DJ_U8       m_Rfu1[2];
        public fixed DJ_S8       m_s8SrcRegName[ConstantVar.XMS_MAX_REGNAME_LEN]; /*src reg name*/
        public fixed DJ_S8       m_s8DestRegName[ConstantVar.XMS_MAX_REGNAME_LEN];/*dest reg name*/
	    public DJ_U8               m_u8SrcAppUnitID;
	    public DJ_U8               m_u8DstAppUnitID;
	    public fixed DJ_S8       m_Rfu2[2];
	    public DeviceID_t        m_srcDevice;
	    public fixed DJ_S8       m_Rfu3[20];
	    public DJ_S32             m_s32Rst;
    };/**/

    /*ACS clearcall parm*/
    public struct ClearCallParm_t
    {
	    public DJ_S32        m_s32ClearCause;/*Reserved*/
	    public DJ_S32        m_s32Resrv;/*Reserved*/
    };/**/

    /*ACS Jointo conf parm*/
    public struct JoinToConfParm_t
    {
	    public DeviceID_t           m_ITPMediaDevice;/*media device*/
        public CmdParamData_Conf_t  m_ITPConfParam;  /*Conf param*/ 
    };/**/

    /*ACS Leave conf parm*/
    public struct LeaveFromConfParm_t
    {
	    public DeviceID_t                      m_ITPMediaDevice;/*media device*/    
	    public CmdParamData_Conf_t  m_ITPConfParam;  /*Conf param*/ 
    };/**/

    public struct ClearConfParm_t
    {
        public DJ_S32       m_s32Resrv;/*Reserved*/
    };/*Clear conf param*/

    /*ACS play parm*/
    public struct PlayParm_t
    {    	
	    public PlayProperty_t       m_PlayProperty;   /*playProperty*/	
    };/**/

    public struct InitPlayIndexParm_t
    {
	    public DJ_S32               m_s32Reserved;     /**/
    };/**/

    public struct BuildPlayIndexParm_t
    {	
	    public PlayProperty_t   m_ITPPlayProperty;/**/
    };/**/

    /*ACS control play parm*/
    public struct ControlPlayParm_t
    {
	    public ControlPlay_t  m_ITPControlPlay; /*control play parmeter*/
    };/**/

    /*ACS record parm*/
    public struct RecordParm_t
    {	
	    public RecordProperty_t    m_ITPRecordProperty;/*record property set*/
    };/**/

    /*ACS control record parm*/
    public struct ControlRecordParm_t
    {
	    public ControlRecord_t  m_ITPControlRecord;/*control record set*/
    };/**/

    /*ACS record Ram parm*/
    public struct RecordCSPParm_t
    {	
	    public RecordCSPProperty_t    m_ITPRecordCSPProperty;/*record CSP property set*/
    };/**/

 //   #define		ITP_MAX_STREAM_DATA_LENGTH		4000
 //   using            ITP_MAX_STREAM_DATA_LENGTH   =   4000;
    /*ACS CSPPlayParm_t*/
    public struct CSPPlayParm_t
    {	
	    public CSPPlayProperty_t            m_ITPCSPPlayProperty;     /*ITP csp play property*/
    };/**/

    /*CSPPlayData*/
    public unsafe struct CSPPlaySendDataParm_t
    {
	    public PKG_HEAD_STRUCT      m_ITPPkgCmdHead;      /*ITP package head*/
	    public CSPPlayDataInfo_t       m_CspPlayDataInfo;    /*csp play data info*/
        public fixed DJ_U8                   m_u8StreamData[ConstantVar.ITP_MAX_STREAM_DATA_LENGTH];	/*stream data*/
    };/**/

    /*ACS monitor filter parm*/
    public struct MonitorFilterParm_t
    {
	    public DJ_U32                m_u32MonitorFilter;/*event monitor filter,reference ACS_IOEVT_MASK*/
    };/**/

    /*ACS send io parm*/
    public struct SendIOParm_t
    {	
        public DJ_U16         m_u16IoType;     /*io proc type*/
	    public DJ_U16         m_u16IoDataLen;  /*io data len*/  
    };/*IO data pack*/

    /*ACS send Signal Msg Type*/
    public unsafe struct SendSigMsgParm_t
    {	
        public DJ_U16                 m_u16SigMsgType;     /*Signal Msg Type*/
	    public fixed DJ_S8           m_s8Rfu[2];          /*Rfu*/  
    };/**/

    /*fax_shakehand_param*/
    public unsafe struct FaxHandShake_t
    {
	    public DJ_U8    m_u8Handshake_Result;   /*T30 handshake result*/
	    public fixed DJ_U8	    m_u8Local_ID[20];
	    public fixed DJ_U8	    m_u8Remote_ID[20];
	    public DJ_U8	    m_u8Modem_Type;		/*F144_MODEM,F96_MODEM,F48_MODEM*/
	    public DJ_U8	    m_u8Fax_Speed;          /*2400,4800,7200,9600,12000,14400*/
	    public DJ_U8	    m_u8Dencity;		/*T4_LOW_DENSITY or T4_HIGH_DENSITY*/
	    public DJ_U8	    m_u8Encode_Type;   /*T4_MH_ENCODE or T4_MR_ENCODE or T6_ENCODE*/
	    public DJ_U8	    m_u8Line_Width;		
	    public DJ_U8	    m_u8Min_Scanline_Time; 	/*minimum scanline time in ms, 0 for no limit*/
	    public DJ_U8	    m_u8Page_Length;		
	    public DJ_U8	    m_u8Ecm_Support;	/*ECM_SUPPORT or ECM_UNSUPPORT*/
	    public DJ_U8    m_u8Host_Control;  //host command
	    public fixed DJ_U8    m_u8Reserve[6];
	    public DJ_U32  m_u32Total_Page_Num;  //total sending page num, set by Ap when sending fax
    };/*FaxHandShake_t*/

    /*faxReceivePageParam*/
    public unsafe struct FaxPageAttri_t
    {
	    public DJ_U32	  m_u32PageNo;       //当前页的页号，从1开始
	    public DJ_U32	  m_u32ByteCount;    //当前页的总字节数	
	    public DJ_U8	      m_u8YResolution;	 //垂直分辨率，低分辨率0， 高分辨率1
	    public DJ_U8	      m_u8EncodeType;    //MH 0， MR 1， MMR 2
	    public DJ_U8	      m_u8PageWidth;	 //页宽0代表1728
	    public DJ_U8	      m_u8MinScanlineTime;  //最小行扫描时间
	    public DJ_U32    m_u32PageOffset;     //页数据偏移量
	    public DJ_U32    m_u32FillOrder;      //字节的bit位顺序
	    public DJ_U32    m_u32XResolution;    //水平分辨率      
	    public fixed DJ_U32    m_u32Reserve[10];    //保留
    };/*FaxRecvPage_t*/


    public unsafe struct FaxLocalSpec_t
    {
	    public DJ_U8	    m_u8Modem_Type;		
	    public DJ_U8	    m_u8Fax_Speed;          
	    public DJ_U8	    m_u8Dencity;		
	    public DJ_U8	    m_u8Encode_Type;  
	    public DJ_U8    m_u8Line_Width;		
	    public DJ_U8	    m_u8Min_Scanline_Time; 	
	    public DJ_U8	    m_u8Page_Length;		
	    public DJ_U8	    m_u8Ecm_Support;	
	    public fixed DJ_U8	m_u8Remote_ID[20]; 
    };/*FaxLocalSpec_t*/

    public unsafe struct FaxEndingParam_t
    {
	    public DJ_U16  m_u16Fax_Channel_ID;    //Fax Chan
	    public DJ_U16  m_u16Fax_End_Flag;      //Fax end flag
	    public DJ_U8	    m_u8Last_Error_Code;	//error code of last fax operation
	    public DJ_U8	    m_u8Last_Error_State;	//error state of last fax operation
	    public DJ_U8	    m_u8Last_Send_T30_Command_State;//store the state the T30 command just sent
	    public DJ_U8	    m_u8Last_Rcv_T30_Command;	//store the T30 command just received
	    public DJ_U16	m_u16Total_Page_Num;		//total pages,send: sending total pages successfully  ;rev: receiving total pages successfully
        public fixed DJ_U8	m_u8Remote_Id[20];
    };/*FaxEndingParam_t*/

    public struct FaxRemoteSepc_t
    {
	    public DJ_U8	    m_u8Modem_Type;		//F144_MODEM,F96_MODEM,F48_MODEM
	    public DJ_U8	    m_u8Fax_Speed;		//BPS_14400,BPS_12000,BPS_9600,BPS_7200,BPS_4800,BPS_2400
	    public DJ_U8	    m_u8Dencity;		//T4_LOW_DENSITY or T4_HIGH_DENSITY
	    public DJ_U8	    m_u8Encode_Type;	//T4_MH_ENCODE or T4_MR_ENCODE or T6_ENCODE
	    public DJ_U8	    m_u8Line_Width;		//see line width list
	    public DJ_U8	    m_u8Min_Scanline_Time; 	//minimum scanline time in ms, 0 for no limit
	    public DJ_U8	    m_u8Page_Length;		//
	    public DJ_U8	    m_u8Ecm_Support;	//ECM_SUPPORT or ECM_UNSUPPORT
    };/*FaxRemoteSepc_t*/

    /*Fax_Page_t*/
    public struct Fax_Page_t
    {
	    public DJ_U16	 m_u16Total_Page_Num;        //总共需要发送的页数
	    public DJ_U16	 m_u16Send_EOM_Flag;        //页后控制
	    public DJ_U32	 m_u32Current_Page_Offset;  //页偏移    
	    public DJ_U32	 m_u32Current_Page_Bytes;	     //当前页的字节数
    };/*Fax_Page_t*/

    /*SendFaxParm_t*/
    public unsafe struct SendFaxParm_t
    {
        public fixed DJ_S8    m_s8LocalID[ConstantVar.ACS_LOCALID_MAX_LEN]; /*Local ID*/
        public fixed DJ_S8    m_s8FaxTiffFile[ConstantVar.MAX_PATH];        /*fax tiff file*/
	    public DeviceID_t     m_ITPMediaDeviceID;               /*Media deviceID*/	
    };/**/

    /*StopSendFaxParm_t*/
    public unsafe struct StopSendFaxParm_t
    {	
	    public fixed DJ_S8          m_s8Rfu1[4]; /*Reserved*/	
    };/**/

    /*RecvFaxParm_t*/
    public unsafe struct RecvFaxParm_t
    {
        public fixed DJ_S8        m_s8LocalID[ConstantVar.ACS_LOCALID_MAX_LEN]; /*fax Local ID*/
        public fixed DJ_S8        m_s8FaxTiffFile[ConstantVar.MAX_PATH];        /*fax tiff file*/
	    public DeviceID_t         m_ITPMediaDeviceID;               /*media deviceID*/
    };/**/

    /*StopRecvFaxParm_t*/
    public unsafe struct StopRecvFaxParm_t
    {	
	    public fixed DJ_S8          m_s8Rfu1[4]; /*Reserved*/	
    };/**/

    /*ACS 3gpp play parm*/
    public struct InitPlay3gppIndexParm_t
    {
	    public DJ_S32               m_s32Reserved;     /**/
    };/**/

    public struct BuildPlay3gppIndexParm_t
    {	
	    public Play3gppProperty_t   m_ITPPlayProperty;/**/
    };/**/

    /*ACS 3gpp play parm*/
    public struct Play3gppParm_t
    {    	
	    public Play3gppProperty_t       m_PlayProperty;   /*Play3gppProperty_t*/	
    };/**/

    /*ACS control play parm*/
    public struct Control3gppPlayParm_t
    {
	    public Control3gppPlay_t  m_ITPControlPlay; /*control play parmeter*/
    };/**/

    /*ACS record parm*/
    public struct Record3gppParm_t
    {	
	    public Record3gppProperty_t    m_ITPRecordProperty;/*record property set*/
    };/**/

    /*ACS control record parm*/
    public struct Control3gppRecordParm_t
    {
	    public Control3gppRecord_t  m_ITPControlRecord;/*control record set*/
    };/**/

    /*ACS Query License parm*/
    public unsafe struct QueryLicenseParm_t
    {
	    public DJ_U8             m_u8ModuleID; /*Board module ID*/
	    public fixed DJ_S8     m_Rfu1[3];    /*Rfu*/
    };/**/

    /*SendRawFrameParm_t*/
    public struct SendRawFrameParm_t
    {		
	    public DJ_U16              m_u16FrameSize;
	    public DJ_U16              m_Rfu1;
    };/**/

    /*JoinTo3GVConfParm_t*/
    public struct JoinTo3GVConfParm_t
    {	
	    public DeviceID_t                       m_device;
	    public Acs_MediaEx_Input_V     m_input;
	    public Acs_MediaEx_Output_V  m_output;
	    public DJ_U8                              m_u8Visible;
    };/**/

    /*LeaveFrom3GVConfParm_t*/
    public struct LeaveFrom3GVConfParm_t
    {	
	    public DeviceID_t               m_device;
    };/**/

    /*Clear3GVConfParm_t*/
    public struct Clear3GVConfParm_t
    {
	    public DJ_S32               m_s32Reserved;     /**/
    };/**/

    /*GetLayoutParm_t*/
    public struct GetLayoutParm_t
    {	
	    public DJ_S32               m_s32Reserved;     /**/
    };/**/

    /*SetLayoutParm_t*/
    public struct SetLayoutParm_t
    {	
	    public Acs_3GVConf_LayoutList m_list;
    };/**/

    /*GetVisibleListParm_t*/
    public struct GetVisibleListParm_t
    {	
	    public DJ_S32               m_s32Reserved;     /**/
    };/**/

    /*SetVisibleListParm_t*/
    public struct SetVisibleListParm_t
    {	
	    public Acs_3GVConf_VisibleList m_list;
    };/**/

    /*Restart3GVConfParm_t*/
    public struct Restart3GVConfParm_t
    {	
	    public DJ_S32               m_s32Reserved;     /**/
    };/**/

    /*Syn_OpenDev*/
    public struct QueryDevLinkParm_t
    {
	    public DeviceID_t    m_ITPDevice;
    };

    /*Syn_OpenDev*/
    public struct Syn_OpenDev
    {
	    public Acs_Cmd_t     m_AcsCmd;
	    public DeviceID_t    m_TrunkDev;
	    public DeviceID_t    m_CtxDev;
    };/*Syn_OpenDev*/

    /*SS7_Syn_CallIn*/
    public unsafe struct SS7_Syn_CallIn
    {
	    public fixed DJ_S8     m_s8Caller[32];
	    public fixed DJ_S8     m_s8Called[32];
	    public DJ_S32           m_s32CallingPartCategory;
	    public DJ_S32           m_s32NatureOfCallerAddress;
	    public DJ_S32           m_s32NatureOfCalledAddress;
	    public DJ_S32           m_s32iAnswerType;
	    public DJ_S32           m_s32iCallOUTorIN;
    };/*SS7_Syn_CallIn*/

    /*SS7_Syn_CallOut*/
    public struct SS7_Syn_CallOut
    {
        public DJ_S32 m_s32iCallOutResult;
        public DJ_S32 m_s32iCallOUTorIN;
    };/*SS7_Syn_CallOut*/

    [StructLayout(LayoutKind.Explicit)]
    public struct Acs_Cmd_Param
    {
        [FieldOffset(0)]
        public OpenDevParm_t        m_ITPAcsOpenDevParm;
        [FieldOffset(0)]
        public CloseDevParm_t        m_ITPAcsCloseDevParm;
        [FieldOffset(0)]
        public ResetDevParm_t        m_ITPAcsResetDevParm;
        [FieldOffset(0)]
        public GetDevStateParm_t   m_ITPAcsGetDevStateParm;
        [FieldOffset(0)]
        public SetDevGroupParm_t  m_ITPAcsSetDevGrpParm;
        [FieldOffset(0)]
        public CalloutParm_t            m_ITPAcsCallOutParm;
        [FieldOffset(0)]
        public SetParm_t                  m_ITPAcsSetParm;
        [FieldOffset(0)]
        public GetParm_t                 m_ITPAcsGetParm;
        [FieldOffset(0)]
        public AnswerCallInParm_t  m_ITPAcsAnSwerCallInParm;
        [FieldOffset(0)]
        public LinkDevParm_t           m_ITPAcsLinkDevParm;
        [FieldOffset(0)]
        public UnlinkDevParm_t       m_ITPAcsUnlinkDevParm;
        [FieldOffset(0)]
        public ClearCallParm_t         m_ITPAcsClearCallParm;
        [FieldOffset(0)]
        public JoinToConfParm_t      m_ITPAcsJoinToConfParm;
        [FieldOffset(0)]
        public LeaveFromConfParm_t m_ITPAcsLeaveConfParm;
        [FieldOffset(0)]
        public PlayParm_t                m_ITPAcsPlayParm;
        [FieldOffset(0)]
        public InitPlayIndexParm_t m_ITPAcsInitPlayIndex;
        [FieldOffset(0)]
        public BuildPlayIndexParm_t m_ITPAcsBuildPlayIndex;
        [FieldOffset(0)]
        public ControlPlayParm_t    m_ITPAcsCtrlPlayParm;
        [FieldOffset(0)]
        public RecordParm_t            m_ITPAcsRecordParm;
        [FieldOffset(0)]
        public ControlRecordParm_t m_ITPAcsCtrlRecordParm;
        [FieldOffset(0)]
        public SendFaxParm_t          m_ITPAcsSendFaxParm;
        [FieldOffset(0)]
        public StopSendFaxParm_t   m_ITPAcsStopSendFaxParm;
        [FieldOffset(0)]
        public SendFaxParm_t         m_ITPAcsRecvFaxParm;
        [FieldOffset(0)]
        public StopRecvFaxParm_t   m_ITPAcsStopRecvFaxParm;
        [FieldOffset(0)]
        public MonitorFilterParm_t   m_ITPAcsMonFilterParm;
        [FieldOffset(0)]
        public SendIOParm_t           m_ITPAcsSendIoParm;
        [FieldOffset(0)]
        public Play3gppParm_t        m_ITPAcsPlay3gpParm;
        [FieldOffset(0)]
        public Control3gppPlayParm_t m_ITPAcsCtrl3gpPlayParm;
        [FieldOffset(0)]
        public Record3gppParm_t        m_ITPAcsRecord3gpParm;
        [FieldOffset(0)]
        public Control3gppRecordParm_t m_ITPAcsCtrl3gpRecordParm;
    }

    /*Acs_cmd*/
    public struct Acs_Cmd
    {
        public ACS_CMD_HEAD     m_ITPAcsCmdHead;/*acs cmd head*/	
        public Acs_Cmd_Param     m_CmdParam;
        public PrivateData_t         m_ITPPrivateData;/*private data*/
    };/**/

    public struct Acs_DevSub_Info
    {
	    public DJ_S16      m_s16DeviceSub;
	    public DJ_S16      m_s16StartTs;
	    public DJ_S16      m_s16DeviceNum;
	    public DJ_S16      m_Rfu1;
    }

    public class Acs_Dev_Info
    {
	    public DJ_S8                     m_s8MachID;
	    public DJ_S8                     m_s8ModuleID;	
	    public DJ_S16                   m_s16DeviceMain;
	    public DJ_S16                   m_s16DevSubNum;	
	    public DJ_S16                   m_Rfu1;
	    public Acs_DevSub_Info   []m_DevSub = new Acs_DevSub_Info[128];
    }
}
