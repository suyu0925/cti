package DJKeygoe;

public class DJAcsCmdDef {

}

class ACS_CMD_TYPE
{	
	public static final int ACS_CMD_TYPE_GETDEVLIST  		= 0x01;
	public static final int ACS_CMD_TYPE_OPENDEVICE  		= 0x02;
	public static final int ACS_CMD_TYPE_CLOSEDEVICE  		= 0x03;
	public static final int ACS_CMD_TYPE_RESETDEVICE  		= 0x04;
	public static final int ACS_CMD_TYPE_GETDEVICESTATE  	= 0x05;
	public static final int ACS_CMD_TYPE_SETDEVGROUP  		= 0x06;	
	public static final int ACS_CMD_TYPE_SETDEVPARAM  		= 0x07;
	public static final int ACS_CMD_TYPE_GETDEVPARAM  		= 0x08;
	public static final int ACS_CMD_TYPE_MAKECALLOUT  		= 0x09;
	public static final int ACS_CMD_TYPE_ALERTCALL  		= 0x0A;
	public static final int ACS_CMD_TYPE_ANSWERCALLIN  		= 0x0B;
	public static final int ACS_CMD_TYPE_LINKDEV  			= 0x0C;
	public static final int ACS_CMD_TYPE_UNLINKDEV  		= 0x0D;
	public static final int ACS_CMD_TYPE_CLEARCALL  		= 0x0E;
	public static final int ACS_CMD_TYPE_JOINTOCONF  		= 0x0F;
	public static final int ACS_CMD_TYPE_LEAVEFROMCONF  	= 0x10;
	public static final int ACS_CMD_TYPE_CLEARCONF  		= 0x11;
	public static final int ACS_CMD_TYPE_PLAYFILE  			= 0x12;
	public static final int ACS_CMD_TYPE_INITPLAYINDEX  	= 0x13;
	public static final int ACS_CMD_TYPE_BUILDPLAYINDEX  	= 0x14;
	public static final int ACS_CMD_TYPE_CONTROLPLAY  		= 0x15;
	public static final int ACS_CMD_TYPE_RECORDFILE  		= 0x16;
	public static final int ACS_CMD_TYPE_CONTROLRECORD  	= 0x17;
	public static final int ACS_CMD_TYPE_SENDFAX  			= 0x18;
	public static final int ACS_CMD_TYPE_STOPSENDFAX  		= 0x19;
	public static final int ACS_CMD_TYPE_RECVFAX  			= 0x1A;
	public static final int ACS_CMD_TYPE_STOPRECVFAX  		= 0x1B;
	public static final int ACS_CMD_TYPE_CHANGEMONITORFILTER= 0x1C;
	public static final int ACS_CMD_TYPE_SENDIO  			= 0x1D;
	public static final int ACS_CMD_TYPE_SENDSIGMSG  		= 0x1E;
	public static final int ACS_CMD_TYPE_RECORDCSP  		= 0x1F;
	public static final int ACS_CMD_TYPE_DBGON  			= 0x20;
	public static final int ACS_CMD_TYPE_DBGOFF  			= 0x21;
	public static final int ACS_CMD_TYPE_PLAY_3GPP  		= 0x22;
    public static final int ACS_CMD_TYPE_CONTROL_3GPP_PLAY  = 0x23;
    public static final int ACS_CMD_TYPE_RECORD_3GPP  		= 0x24;
    public static final int ACS_CMD_TYPE_CONTROL_3GPP_RECORD= 0x25;	
    public static final int ACS_CMD_TYPE_PLAYCSP  			= 0x26;
	public static final int ACS_CMD_TYPE_SENDPLAYCSP  		= 0x27;
	public static final int ACS_CMD_TYPE_SETMASTER  		= 0x28;
	public static final int ACS_CMD_TYPE_QUERYLIC  			= 0x29;
	public static final int ACS_CMD_TYPE_CTXREG  			= 0x2A;
	public static final int ACS_CMD_TYPE_CTXLINK  			= 0x2B;
	public static final int ACS_CMD_TYPE_CTXSENDAPPDATA  	= 0x2C;
	public static final int ACS_CMD_TYPE_INIT3GPPINDEX  	= 0x2D;
	public static final int ACS_CMD_TYPE_BUILD3GPPINDEX  	= 0x2E;
	public static final int ACS_CMD_TYPE_SENDRAWFRAME  		= 0x2F;
	public static final int ACS_CMD_TYPE_JOIN3GCONF  		= 0x30;
	public static final int ACS_CMD_TYPE_LEAVE3GCONF  		= 0x31;
	public static final int ACS_CMD_TYPE_CLEAR3GCONF  		= 0x32;
	public static final int ACS_CMD_TYPE_GET3GCONFLAYOUT  	= 0x33;
	public static final int ACS_CMD_TYPE_SET3GCONFLAYOUT  	= 0x34;
	public static final int ACS_CMD_TYPE_GET3GCONFVISABLE  	= 0x35;
	public static final int ACS_CMD_TYPE_SET3GCONFVISABLE  	= 0x36;
	public static final int ACS_CMD_TYPE_RESTART3GCONF  	= 0x37;
}

class CTX_APPDATA_RET
{
	public static final int CTX_APPDATA_RET_SUCCESS		= 0x0;
	public static final int CTX_APPDATA_RET_NODEST		= 0x4;
	public static final int CTX_APPDATA_RET_NOSRC  		= 0x5;
	public static final int CTX_APPDATA_DEST_RECVOK     = 0xFF;
}

/*Acs_Cmd_t*/
class Acs_Cmd_t
{	
	public int      	   m_s32AcsHandle;    /*acs handle*/	
	public DeviceID_t      m_ITPDeviceID    = new DeviceID_t();      /*Device id*/
	public int      	   m_s32CmdType;      /*command type*/
	public byte       	   m_s8PackName[]   = new byte[64];  /*parmeter name*/
	public int       	   m_s32PackSize;     /*parmeter size*/
	public byte            m_u8AcsId;         /*acs server use*/
	public byte            m_Rfu1[]			= new byte[3];
}/*Acs_Cmd_t*/

/*ACS Cmd Head*/
class ACS_CMD_HEAD
{
	public PKG_HEAD_STRUCT  m_ITPPkgCmdHead = new PKG_HEAD_STRUCT();   /*ITP package head*/	
	public Acs_Cmd_t        m_ITPAcsCmd_t	= new Acs_Cmd_t();     /*acs command package head*/
}/**/

/*ACS set Master parm*/
class SetMasterParm_t
{
	public byte     		m_u8Master;
	public byte     	    m_u8AppUnitID;
	public byte     	    m_Rfu1[] = new byte[2];
}/**/

/*ACS open device parm*/
class OpenDevParm_t
{
	public int		        m_s32Resrv;/*Reserved*/
}/**/

/*ACS close device parm*/
class CloseDevParm_t
{
	public int		        m_s32Resrv;/*Reserved*/
}/**/

class ResetDevParm_t
{
	public int		        m_s32Resrv;/*Reserved*/
}/**/

class GetDevStateParm_t
{
	public int		        m_s32Resrv;/*Reserved*/
}/**/

/*ACS set device group parm*/
class SetDevGroupParm_t
{
	public int		        m_s32Resrv;/*Reserved*/
}/**/

/*ACS callout parm*/
class CalloutParm_t
{	
	public byte       	 m_s8CallingNum[] = new byte[32];/*calling id*/
	public byte          m_s8CalledNum[]  = new byte[32];/*called id*/
}/**/

class SetParm_t
{	
	public short         m_u16ParamCmdType;
	public short         m_u16ParamDataSize;
}/**/

class GetParm_t
{
	public short         m_u16ParamCmdType;
	public short         m_u16ParamDataSize;
}/**/

/*ACS callin parm*/
class AlertCallParm_t
{
	public int	         m_s32Resrv;/*Reserved*/
}/**/

/*ACS callin parm*/
class AnswerCallInParm_t
{
	public int	         m_s32Resrv;/*Reserved*/
}/**/

/*ACS Link Device parm*/
class LinkDevParm_t
{
	public DeviceID_t    m_ITPDestDeviceID = new DeviceID_t();/*Device id*/
}/**/

/*ACS UnLink parm*/
class UnlinkDevParm_t
{
	public DeviceID_t    m_ITPDestDeviceID = new DeviceID_t();/*Device id*/
}/**/

/*ACS XMS Reg parm*/
class XMSCtxRegParm_t
{
	public byte   		 m_s8RegName[] = new byte[16];/*Reg Name*/	
	public byte   	     m_u8RegType;  /*1:Reg; 2: unReg,reference XMS_CTX_REG_TYPE*/
	public byte   	     m_u8AcsUnitID;
	public byte   	     m_Rfu1[] = new byte[2];
	public int   	     m_s32Rst;
}

/*ACS XMS ctxlink parm*/
class XMSCtxLinkParm_t
{
	public byte   		 m_u8CtxLinkOpt;/*link option,reference CTX_LINK_OPTION*/
	public byte   	     m_u8AcsUnitID;
	public byte   	     m_Rfu1[] = new byte[2];
	public DeviceID_t    m_srcDev = new DeviceID_t();
	public DeviceID_t    m_destDev= new DeviceID_t();
	public int   	     m_s32Rst;
}

/*ACS App Data Info*/
class XMS_AppData_Info_t
{
	public int   	     m_u32AppDataSize; /*user APP data size,not include XMS_AppData_Info_t*/
	public byte   	     m_u8AppReqType;   /*user APP req cmd type,user self define*/
	public byte   	     m_u8AcsUnitID;
	public byte   	     m_Rfu1[] = new byte[2];      
	public byte   	     m_s8SrcRegName[] = new byte[16]; /*src reg name*/
	public byte   	     m_s8DestRegName[] = new byte[16];/*dest reg name*/
	public byte   	     m_u8SrcAppUnitID;
	public byte   	     m_u8DstAppUnitID;
	public byte   	     m_Rfu2[] = new byte[2];
	public DeviceID_t    m_srcDevice;
	public byte   	     m_Rfu3[] = new byte[20];
	public int           m_s32Rst;
}/**/

/*ACS clearcall parm*/
class ClearCallParm_t
{
	public int           m_s32ClearCause;/*Reserved*/
	public int           m_s32Resrv;/*Reserved*/
}/**/

/*ACS Jointo conf parm*/
class JoinToConfParm_t
{
	public DeviceID_t           m_ITPMediaDevice = new DeviceID_t();/*media device*/
    public CmdParamData_Conf_t  m_ITPConfParam	 = new CmdParamData_Conf_t();  /*Conf param*/ 
}/**/

/*ACS Leave conf parm*/
class LeaveFromConfParm_t
{
	public DeviceID_t           m_ITPMediaDevice = new DeviceID_t();/*media device*/    
	public CmdParamData_Conf_t  m_ITPConfParam   = new CmdParamData_Conf_t();  /*Conf param*/ 
}/**/

class ClearConfParm_t
{
	public int       m_s32Resrv;/*Reserved*/
}/*Clear conf param*/

/*ACS play parm*/
class PlayParm_t
{    	
	public PlayProperty_t       m_PlayProperty = new PlayProperty_t();   /*playProperty*/	
}/**/

class InitPlayIndexParm_t
{
	public int               	m_s32Reserved;     /**/
}/**/

class BuildPlayIndexParm_t
{	
	public PlayProperty_t   	m_ITPPlayProperty = new PlayProperty_t();/**/
}/**/

/*ACS control play parm*/
class ControlPlayParm_t
{
	public ControlPlay_t  		m_ITPControlPlay = new ControlPlay_t(); /*control play parmeter*/
}/**/

/*ACS record parm*/
class RecordParm_t
{	
	public RecordProperty_t     m_ITPRecordProperty = new RecordProperty_t();/*record property set*/
}/**/

/*ACS control record parm*/
class ControlRecordParm_t
{
	public ControlRecord_t  	m_ITPControlRecord = new ControlRecord_t();/*control record set*/
}/**/

/*ACS record Ram parm*/
class RecordCSPParm_t
{	
	public RecordCSPProperty_t  m_ITPRecordCSPProperty = new RecordCSPProperty_t();/*record CSP property set*/
}/**/

/*ACS CSPPlayParm_t*/
class CSPPlayParm_t
{	
	public CSPPlayProperty_t    m_ITPCSPPlayProperty = new CSPPlayProperty_t();     /*ITP csp play property*/
}/**/

/*CSPPlayData*/
class CSPPlaySendDataParm_t
{
	public PKG_HEAD_STRUCT        m_ITPPkgCmdHead 	= new PKG_HEAD_STRUCT();      /*ITP package head*/
	public CSPPlayDataInfo_t      m_CspPlayDataInfo = new CSPPlayDataInfo_t();    /*csp play data info*/
	public byte                   m_u8StreamData[]	= new byte[4000];	/*stream data*/
}/**/

/*ACS monitor filter parm*/
class MonitorFilterParm_t
{
	public int                	  m_u32MonitorFilter;/*event monitor filter,reference ACS_IOEVT_MASK*/
}/**/

/*ACS send io parm*/
class SendIOParm_t
{	
    public short         m_u16IoType;     /*io proc type*/
    public short         m_u16IoDataLen;  /*io data len*/  
}/*IO data pack*/

/*ACS send Signal Msg Type*/
class SendSigMsgParm_t
{	
	public short         m_u16SigMsgType;     /*Signal Msg Type*/
	public byte          m_s8Rfu[] = new byte[2];          /*Rfu*/  
}/**/
/*fax_shakehand_param*/
class FaxHandShake_t
{
	public byte   		 m_u8Handshake_Result;   /*T30 handshake result*/
	public byte   		 m_u8Local_ID[]   = new byte[20];
	public byte   		 m_u8Remote_ID[]  = new byte[20];
	public byte   		 m_u8Modem_Type;		/*F144_MODEM,F96_MODEM,F48_MODEM*/
	public byte   		 m_u8Fax_Speed;          /*2400,4800,7200,9600,12000,14400*/
	public byte   		 m_u8Dencity;		/*T4_LOW_DENSITY or T4_HIGH_DENSITY*/
	public byte   		 m_u8Encode_Type;   /*T4_MH_ENCODE or T4_MR_ENCODE or T6_ENCODE*/
	public byte   		 m_u8Line_Width;		
	public byte   		 m_u8Min_Scanline_Time; 	/*minimum scanline time in ms, 0 for no limit*/
	public byte   		 m_u8Page_Length;		
	public byte   		 m_u8Ecm_Support;	/*ECM_SUPPORT or ECM_UNSUPPORT*/
	public byte   	     m_u8Host_Control;  //host command
	public byte   	     m_u8Reserve[]   = new byte[6];
	public int   	     m_u32Total_Page_Num;  //total sending page num, set by Ap when sending fax
}/*FaxHandShake_t*/

/*faxReceivePageParam*/
class FaxPageAttri_t 
{
	public int   		m_u32PageNo;       //��ǰҳ��ҳ�ţ���1��ʼ
	public int   		m_u32ByteCount;    //��ǰҳ�����ֽ���	
	public byte   		m_u8YResolution;	 //��ֱ�ֱ��ʣ��ͷֱ���0�� �߷ֱ���1
	public byte   		m_u8EncodeType;    //MH 0�� MR 1�� MMR 2
	public byte   		m_u8PageWidth;	 //ҳ��0���1728
	public byte   		m_u8MinScanlineTime;  //��С��ɨ��ʱ��
	public int   	    m_u32PageOffset;     //ҳ���ƫ����
	public int   	    m_u32FillOrder;      //�ֽڵ�bitλ˳��
	public int   	    m_u32XResolution;    //ˮƽ�ֱ���      
	public int   	    m_u32Reserve[] = new int[10];    //����
}/*FaxRecvPage_t*/


class FaxLocalSpec_t
{
	public byte   	    m_u8Modem_Type;		
	public byte   		m_u8Fax_Speed;          
	public byte   		m_u8Dencity;		
	public byte   		m_u8Encode_Type;  
	public byte   		m_u8Line_Width;		
	public byte   		m_u8Min_Scanline_Time; 	
	public byte   		m_u8Page_Length;		
	public byte   		m_u8Ecm_Support;	
	public byte   		m_u8Remote_ID[] = new byte[20]; 
}/*FaxLocalSpec_t*/

class FaxEndingParam_t
{
	public short    m_u16Fax_Channel_ID;    //Fax Chan
	public short  	m_u16Fax_End_Flag;      //Fax end flag
	public byte  	m_u8Last_Error_Code;	//error code of last fax operation
	public byte  	m_u8Last_Error_State;	//error state of last fax operation
	public byte  	m_u8Last_Send_T30_Command_State;//store the state the T30 command just sent
	public byte  	m_u8Last_Rcv_T30_Command;	//store the T30 command just received
	public short	m_u16Total_Page_Num;		//total pages,send: sending total pages successfully  ;rev: receiving total pages successfully
	public byte  	m_u8Remote_Id[] = new byte[20];
}/*FaxEndingParam_t*/

class FaxRemoteSepc_t
{
	public byte   	m_u8Modem_Type;		//F144_MODEM,F96_MODEM,F48_MODEM
	public byte  	m_u8Fax_Speed;		//BPS_14400,BPS_12000,BPS_9600,BPS_7200,BPS_4800,BPS_2400
	public byte  	m_u8Dencity;		//T4_LOW_DENSITY or T4_HIGH_DENSITY
	public byte  	m_u8Encode_Type;	//T4_MH_ENCODE or T4_MR_ENCODE or T6_ENCODE
	public byte  	m_u8Line_Width;		//see line width list
	public byte  	m_u8Min_Scanline_Time; 	//minimum scanline time in ms, 0 for no limit
	public byte  	m_u8Page_Length;		//
	public byte  	m_u8Ecm_Support;	//ECM_SUPPORT or ECM_UNSUPPORT
}/*FaxRemoteSepc_t*/

/*Fax_Page_t*/
class Fax_Page_t
{
	public short	 m_u16Total_Page_Num;        //�ܹ���Ҫ���͵�ҳ��
	public short	 m_u16Send_EOM_Flag;        //ҳ�����
	public int		 m_u32Current_Page_Offset;  //ҳƫ��    
	public int		 m_u32Current_Page_Bytes;	     //��ǰҳ���ֽ���
}/*Fax_Page_t*/

/*SendFaxParm_t*/
class SendFaxParm_t
{
	public byte   	   	 m_s8LocalID[] = new byte[20]; /*Local ID*/	
	public byte   	     m_s8FaxTiffFile[] = new byte[260];        /*fax tiff file*/
	public DeviceID_t    m_ITPMediaDeviceID = new DeviceID_t();               /*Media deviceID*/	
}/**/

/*StopSendFaxParm_t*/
class StopSendFaxParm_t
{	
	public byte          m_s8Rfu1[] = new byte[4]; /*Reserved*/	
}/**/

/*RecvFaxParm_t*/
class RecvFaxParm_t
{
	public byte   	     m_s8LocalID[] = new byte[20]; /*fax Local ID*/	
	public byte          m_s8FaxTiffFile[] = new byte[260];        /*fax tiff file*/
	public DeviceID_t    m_ITPMediaDeviceID = new DeviceID_t();               /*media deviceID*/
}/**/

/*StopRecvFaxParm_t*/
class StopRecvFaxParm_t
{	
	public byte m_s8Rfu1[] = new byte[4]; /*Reserved*/	
}/**/

/*ACS 3gpp play parm*/
class InitPlay3gppIndexParm_t
{
	public int m_s32Reserved;     /**/
}/**/

class BuildPlay3gppIndexParm_t
{	
	public Play3gppProperty_t   m_ITPPlayProperty = new Play3gppProperty_t();/**/
}/**/

/*ACS 3gpp play parm*/
class Play3gppParm_t
{    	
	public Play3gppProperty_t   m_PlayProperty = new Play3gppProperty_t();   /*Play3gppProperty_t*/	
}/**/

/*ACS control play parm*/
class Control3gppPlayParm_t
{
	public Control3gppPlay_t    m_ITPControlPlay = new Control3gppPlay_t(); /*control play parmeter*/
}/**/

/*ACS record parm*/
class Record3gppParm_t
{	
	public Record3gppProperty_t m_ITPRecordProperty = new Record3gppProperty_t();/*record property set*/
}/**/

/*ACS control record parm*/
class Control3gppRecordParm_t
{
	public Control3gppRecord_t  m_ITPControlRecord = new Control3gppRecord_t();/*control record set*/
}/**/

/*ACS Query License parm*/
class QueryLicenseParm_t
{
	public byte     	m_u8ModuleID; /*Board module ID*/
	public byte       	m_Rfu1[] = new byte[3];    /*Rfu*/
}/**/

/*SendRawFrameParm_t*/
class SendRawFrameParm_t
{		
	public short              		m_u16FrameSize;
	public short                    m_Rfu1;
}/**/

/*JoinTo3GVConfParm_t*/
class JoinTo3GVConfParm_t
{	
	public DeviceID_t        		m_device = new DeviceID_t();
	public Acs_MediaEx_Input_V      m_input = new Acs_MediaEx_Input_V();
	public Acs_MediaEx_Output_V     m_output = new Acs_MediaEx_Output_V();
	public byte                     m_u8Visible;
}/**/

/*LeaveFrom3GVConfParm_t*/
class LeaveFrom3GVConfParm_t
{	
	public DeviceID_t        m_device = new DeviceID_t();
}/**/

/*Clear3GVConfParm_t*/
class Clear3GVConfParm_t
{
	public int               m_s32Reserved;     /**/
}/**/

/*GetLayoutParm_t*/
class GetLayoutParm_t
{	
	public int               m_s32Reserved;     /**/
}/**/

/*SetLayoutParm_t*/
class SetLayoutParm_t
{	
	public Acs_3GVConf_LayoutList m_list = new Acs_3GVConf_LayoutList();
}/**/

/*GetVisibleListParm_t*/
class GetVisibleListParm_t
{	
	public int               m_s32Reserved;     /**/
}/**/

/*SetVisibleListParm_t*/
class SetVisibleListParm_t
{	
	public Acs_3GVConf_VisibleList m_list = new Acs_3GVConf_VisibleList();
}/**/

/*Restart3GVConfParm_t*/
class Restart3GVConfParm_t
{	
	public int           m_s32Reserved;     /**/
}/**/

/*Syn_OpenDev*/
class QueryDevLinkParm_t
{
	public DeviceID_t    m_ITPDevice = new DeviceID_t();
}

/*Syn_OpenDev*/
class Syn_OpenDev
{
	public Acs_Cmd_t     m_AcsCmd	= new Acs_Cmd_t();
	public DeviceID_t    m_TrunkDev = new DeviceID_t();
	public DeviceID_t    m_CtxDev	= new DeviceID_t();
}/*Syn_OpenDev*/

/*SS7_Syn_CallIn*/
class SS7_Syn_CallIn
{
	public byte     m_s8Caller[] = new byte[32];
	public byte     m_s8Called[] = new byte[32];
	public int      m_s32CallingPartCategory;
	public int      m_s32NatureOfCallerAddress;
	public int      m_s32NatureOfCalledAddress;
	public int      m_s32iAnswerType;
	public int      m_s32iCallOUTorIN;
}/*SS7_Syn_CallIn*/

/*SS7_Syn_CallOut*/
class SS7_Syn_CallOut
{		
	public int	    m_s32iCallOutResult;
	public int	    m_s32iCallOUTorIN;
}/*SS7_Syn_CallOut*/

/*Acs_cmd
typedef struct
{
	ACS_CMD_HEAD     m_ITPAcsCmdHead;//*acs cmd head
	union
	{
		OpenDevParm_t          m_ITPAcsOpenDevParm;       //*open devcie parm
		CloseDevParm_t         m_ITPAcsCloseDevParm;      //*Close device parm
		ResetDevParm_t         m_ITPAcsResetDevParm;      //*Reset device parm
		GetDevStateParm_t      m_ITPAcsGetDevStateParm;   //*Get device state parm
		SetDevGroupParm_t      m_ITPAcsSetDevGrpParm;     //*set device group parm
		CalloutParm_t          m_ITPAcsCallOutParm;       //*callout parm	
		SetParm_t              m_ITPAcsSetParm;           //*set parm
		GetParm_t              m_ITPAcsGetParm;           //*get parm
		AnswerCallInParm_t     m_ITPAcsAnSwerCallInParm;  //*answer callin parm
		LinkDevParm_t          m_ITPAcsLinkDevParm;       //*Link device parm
		UnlinkDevParm_t        m_ITPAcsUnlinkDevParm;     //*Unlink device parm		
		ClearCallParm_t        m_ITPAcsClearCallParm;     //*clear call parm		
		JoinToConfParm_t       m_ITPAcsJoinToConfParm;    //*join to conf parm
		LeaveFromConfParm_t    m_ITPAcsLeaveConfParm;     //*Leave from conf parm
		PlayParm_t             m_ITPAcsPlayParm;          //*play file parm
		InitPlayIndexParm_t    m_ITPAcsInitPlayIndex;     //*Init play index
		BuildPlayIndexParm_t   m_ITPAcsBuildPlayIndex;    //*Build play idnex
		ControlPlayParm_t      m_ITPAcsCtrlPlayParm;      //*control play parm
		RecordParm_t           m_ITPAcsRecordParm;        //*record file parm
		ControlRecordParm_t    m_ITPAcsCtrlRecordParm;    //*control record parm			
		SendFaxParm_t          m_ITPAcsSendFaxParm;       //*send  fax parm
		StopSendFaxParm_t      m_ITPAcsStopSendFaxParm;   //*stop send fax parm
		SendFaxParm_t          m_ITPAcsRecvFaxParm;       //* recv fax parm
		StopRecvFaxParm_t      m_ITPAcsStopRecvFaxParm;   //*stop recv fax parm
		MonitorFilterParm_t    m_ITPAcsMonFilterParm;     //*monitor filter parm
		SendIOParm_t           m_ITPAcsSendIoParm;        //*send io parm    
		Play3gppParm_t             m_ITPAcsPlay3gpParm;          //*play 3gp file parm
		Control3gppPlayParm_t      m_ITPAcsCtrl3gpPlayParm;      //*control 3gp play parm
		Record3gppParm_t           m_ITPAcsRecord3gpParm;        //*record 3gp file parm
		Control3gppRecordParm_t    m_ITPAcsCtrl3gpRecordParm;    //*control 3gp record parm			
	};//*acs cmd parm
	PrivateData_t    m_ITPPrivateData;//*private data
}Acs_Cmd;*/

class Acs_Cmd{	
	public ACS_CMD_HEAD     	  m_ITPAcsCmdHead 			= new ACS_CMD_HEAD();
	public OpenDevParm_t          m_ITPAcsOpenDevParm		= new OpenDevParm_t();       //*open devcie parm
	public CloseDevParm_t         m_ITPAcsCloseDevParm		= new CloseDevParm_t();      //*Close device parm
	public ResetDevParm_t         m_ITPAcsResetDevParm		= new ResetDevParm_t();      //*Reset device parm
	public GetDevStateParm_t      m_ITPAcsGetDevStateParm	= new GetDevStateParm_t();   //*Get device state parm
	public SetDevGroupParm_t      m_ITPAcsSetDevGrpParm		= new SetDevGroupParm_t();     //*set device group parm
	public CalloutParm_t          m_ITPAcsCallOutParm		= new CalloutParm_t();       //*callout parm	
	public SetParm_t              m_ITPAcsSetParm			= new SetParm_t();           //*set parm
	public GetParm_t              m_ITPAcsGetParm			= new GetParm_t();           //*get parm
	public AnswerCallInParm_t     m_ITPAcsAnSwerCallInParm	= new AnswerCallInParm_t();  //*answer callin parm
	public LinkDevParm_t          m_ITPAcsLinkDevParm		= new LinkDevParm_t();       //*Link device parm
	public UnlinkDevParm_t        m_ITPAcsUnlinkDevParm		= new UnlinkDevParm_t();     //*Unlink device parm		
	public ClearCallParm_t        m_ITPAcsClearCallParm		= new ClearCallParm_t();     //*clear call parm		
	public JoinToConfParm_t       m_ITPAcsJoinToConfParm	= new JoinToConfParm_t();    //*join to conf parm
	public LeaveFromConfParm_t    m_ITPAcsLeaveConfParm		= new LeaveFromConfParm_t();     //*Leave from conf parm
	public PlayParm_t             m_ITPAcsPlayParm			= new PlayParm_t();          //*play file parm
	public InitPlayIndexParm_t    m_ITPAcsInitPlayIndex		= new InitPlayIndexParm_t();     //*Init play index
	public BuildPlayIndexParm_t   m_ITPAcsBuildPlayIndex	= new BuildPlayIndexParm_t();    //*Build play idnex
	public ControlPlayParm_t      m_ITPAcsCtrlPlayParm		= new ControlPlayParm_t();      //*control play parm
	public RecordParm_t           m_ITPAcsRecordParm		= new RecordParm_t();        //*record file parm
	public ControlRecordParm_t    m_ITPAcsCtrlRecordParm	= new ControlRecordParm_t();    //*control record parm			
	public SendFaxParm_t          m_ITPAcsSendFaxParm		= new SendFaxParm_t();       //*send  fax parm
	public StopSendFaxParm_t      m_ITPAcsStopSendFaxParm	= new StopSendFaxParm_t();   //*stop send fax parm
	public SendFaxParm_t          m_ITPAcsRecvFaxParm		= new SendFaxParm_t();       //* recv fax parm
	public StopRecvFaxParm_t      m_ITPAcsStopRecvFaxParm	= new StopRecvFaxParm_t();   //*stop recv fax parm
	public MonitorFilterParm_t    m_ITPAcsMonFilterParm		= new MonitorFilterParm_t();     //*monitor filter parm
	public SendIOParm_t           m_ITPAcsSendIoParm		= new SendIOParm_t();        //*send io parm    
	public Play3gppParm_t             m_ITPAcsPlay3gpParm	= new Play3gppParm_t();          //*play 3gp file parm
	public Control3gppPlayParm_t      m_ITPAcsCtrl3gpPlayParm	= new Control3gppPlayParm_t();      //*control 3gp play parm
	public Record3gppParm_t           m_ITPAcsRecord3gpParm		= new Record3gppParm_t();        //*record 3gp file parm
	public Control3gppRecordParm_t    m_ITPAcsCtrl3gpRecordParm	= new Control3gppRecordParm_t();    //*control 3gp record parm	
	public PrivateData_t    	  	  m_ITPPrivateData			= new PrivateData_t();
}

class Acs_DevSub_Info
{
	public short            m_s16DeviceSub;
	public short            m_s16StartTs;
	public short            m_s16DeviceNum;
	public short            m_Rfu1;
}

class Acs_Dev_Info
{
	public byte             m_s8MachID;
	public byte             m_s8ModuleID;	
	public short            m_s16DeviceMain;
	public short            m_s16DevSubNum;	
	public short            m_Rfu1;
	public Acs_DevSub_Info  m_DevSub[] = new Acs_DevSub_Info[128];
	
	public Acs_Dev_Info(){
		for (int i = 0; i < 128; i++){
			m_DevSub[i] = new Acs_DevSub_Info();
		}
	}
}

