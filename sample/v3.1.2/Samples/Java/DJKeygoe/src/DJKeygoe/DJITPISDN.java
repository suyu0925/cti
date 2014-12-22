package DJKeygoe;

public class DJITPISDN {
	//Q931模块与流程执行模块之间通讯包包头子功能定义
	public static final int ITP_SUB_FUNC_FLOW_TO_Q931_GET_CHNL_STATE       = 0x01;     //获取通道状态  查询指定单元指定通道的当前状态
	public static final int ITP_SUB_FUNC_FLOW_TO_Q931_CALL_OUT             = 0x02;    //发起一个呼叫  
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_APPEND_CALLEEID     = 0x03;     //追加被叫号码  发起呼叫后，追加被叫号码
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_GET_CALL_INFO       = 0x04;     //获取呼叫信息  获取呼叫信息，包括主叫号码、被叫号码等
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_GET_CALL_RESULT     = 0x05;     //获取呼出结果 
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_GET_DISCONN_REASON  = 0x06;     //获取挂机原因 
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_SET_CHNL_STATE      = 0x07;     //设置通道状态 
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_SET_PARAM           = 0x08;     //设置参数
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_GET_PARAM           = 0x09;     //获取参数
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_SET_SIGNAL          = 0x10;     //设置信号

	public static final int  ITP_SUB_FUNC_Q931_TO_FLOW_CHNL_STATE          = 0x11;     //反馈通道状态  当通道状态发生了迁移或接收到流程执行模块的请求包，Q931模块向流程执行模块发送本包，以告之流程执行模块指定通道的当前状态
	public static final int  ITP_SUB_FUNC_Q931_TO_FLOW_CALL_INFO           = 0x12;     //反馈呼叫信息  当接收到流程执行模块的请求包，Q931模块向流程执行模块发送本包，包含主叫号码、被叫号码、主叫子地址、被叫子地址及它们的长度
	public static final int  ITP_SUB_FUNC_Q931_TO_FLOW_CALL_RESULT         = 0x13;     //反馈呼出结果  当接收到流程执行模块的请求包，Q931模块向流程执行模块发送本包，以告之流程执行模块指定通道的呼出结果
	public static final int  ITP_SUB_FUNC_Q931_TO_FLOW_DISCONN_REASON      = 0x14;     //反馈挂机原因  当接收到流程执行模块的请求包，Q931模块向流程执行模块发送本包，以告之流程执行模块指定通道的挂机原因
	public static final int  ITP_SUB_FUNC_Q931_TO_FLOW_SET_PARAM           = 0x15;     //反馈设置参数结果  
	public static final int  ITP_SUB_FUNC_Q931_TO_FLOW_GET_PARAM           = 0x16;     //反馈获取参数结果 
	public static final int  ITP_SUB_FUNC_Q931_TO_FLOW_SET_SIGNAL          = 0x17;     //反馈设置信号结果

	//Q931模块与同级模块之间的包头子功能定义
	public static final int  ITP_SUB_FUNC_Q931_STANDBY_CHNL_STATE          = 0x01;
	public static final int  ITP_SUB_FUNC_Q931_STANDBY_REQ_CHNL_STATE      = 0x02;

	public static final int  ITP_SUB_FUNC_Q931_STANDBY_LINK_STATE          = 0x03;
	public static final int  ITP_SUB_FUNC_Q931_STANDBY_REQ_LINK_STATE      = 0x04;


	//Q931模块通道状态定义
	public static final int  ITP_Q931_CH_FREE					    = 1;   //空闲状态
	//#define ITP_Q931_CH_WAIT_APP_FREE		        2   //Q931等待应用层同步释放资源
	public static final int  ITP_Q931_CH_RESTART                    = 2;
	public static final int  ITP_Q931_CH_UNAVIABLE			        = 3;   //通道不可用
	public static final int  ITP_Q931_CH_WAIT_CONNECT_ACK		    = 4;   //等待连接证实
	public static final int  ITP_Q931_CH_CONNECT				    = 5;   //通道连通状态
	public static final int  ITP_Q931_CH_WAIT_RELEASE			    = 6;   //已发送拆线信号，等待对方发送释放信号
	public static final int  ITP_Q931_CH_WAIT_RELEASE_COMPLETE      = 7;   //已发送释放信号，等待对方发送释放完成信号
	public static final int  ITP_Q931_CALLEE_WAIT_ANSWER		    = 11;  //来话方，呼叫到达
	public static final int  ITP_Q931_CALLER_WAIT_ANSWER		    = 12;  //去话方，已呼出，等待对方回应
	public static final int  ITP_Q931_CALLER_RECV_ALERT		        = 21;  //去话方，已接收到提醒消息
	public static final int  ITP_Q931_CALLER_RECV_SETUP_ACK	        = 22;  //去话方，已接收到建立确认消息
	public static final int  ITP_Q931_CALLER_RECV_CALLPROCESS       = 23;  //去话方，已接收到呼叫进程消息
	public static final int  ITP_Q931_CALLER_WAIT_SETUP_ACK	        = 24;  //去话方，等待建立确认
	public static final int  ITP_Q931_CALLEE_WAIT_INFO              = 0x90; //来话方，等待后续被叫号码信息
	public static final int  ITP_Q931_CALLEE_SEND_ALERT			    = 0x91; //来话方，发送了提醒消息


	//通道动作定义
	public static final int 	ITP_Q931_CH_SET_FREE			   = 1;    //APP 层检查通道状态为 OxO2 时，同步释放通道资源
	public static final int  ITP_Q931_CH_SET_CONNECT		       = 2;    //设置通道连接
	public static final int  ITP_Q931_CH_SET_DISCONNECT	           = 3;    //解除通道连接
	public static final int  ITP_Q931_CALLEE_SET_ALERTING	       = 4;    //被叫方发送提醒消息
	public static final int 	ITP_Q931_CH_SET_RESTART		       = 5;    //设置通道重新启动


	//Q931呼出结果定义
	public static final int  ITP_Q931_C_NO_RESULT		   = 0;    //尚未返回呼出结果
	public static final int  ITP_Q931_C_USER_IDLE		   = 1;    //被叫空闲
	public static final int  ITP_Q931_C_USER_OFFHOOK	   = 2;    //被叫摘机，连通
	public static final int  ITP_Q931_C_WAIT_CALL_PROC     = 3;    //重叠发送被叫号码，等待对端确认被叫号码收齐
	public static final int  ITP_Q931_C_OTHERS             = 10;   //其它结果，呼叫可能结束，请查询通道状态
	public static final int  ITP_Q931_C_STATE_UNAVIABLE    = 11;   //状态不对，未进行呼出


	//定义挂机原因
	public static final int  ITP_Q931_RSN_UNKNOW_REASON           = 0x00;   //原因未知
	public static final int  ITP_Q931_RSN_UNALLOC_NUMBER          = 0x01;   //空号
	public static final int  ITP_Q931_RSN_NORMAL_DISCONNECT       = 0x10;   //正常的呼叫清除
	public static final int  ITP_Q931_RSN_USER_BUSY               = 0x11;   //用户忙
	public static final int  ITP_Q931_RSN_NO_RESPOND              = 0x12;   //无响应
	public static final int  ITP_Q931_RSN_NO_ANSWER               = 0x13;   //无用户应答
	public static final int  ITP_Q931_RSN_REFUSR_CALL             = 0x15;   //呼叫拒绝
	public static final int  ITP_Q931_RSN_NUMBER_ERROR            = 0x1C;   //号码不全
	public static final int  ITP_Q931_RSN_TIMEOUT	              = 0x66;   //超时
	public static final int  ITP_Q931_RSN_DCHANNEL_DOWN           = 0xfd;   //链路中断
	public static final int  ITP_Q931_RSN_BCHANNEL_UNAVIABLE      = 0x22;   //通道不可用
	public static final int  ITP_Q931_RSN_UNAVIABLE_CIRCULT       = 0x2c;   //无可用通路

	public static final int  ITP_Q931_RSN_UNAVIABLE_CRN           = 0x51;   //无效的参考值
	public static final int  ITP_Q931_RSN_UNCOMPATIBLE            = 0x58;   //不兼容的终点
	public static final int  ITP_Q931_RSN_UNAVIABLE_MSG           = 0x5F;   //无效的消息

	public static final int  ITP_Q931_RSN_NEEDMSG_LOST            = 0x60;   //必须的信息单元丢失

	public static final int  ITP_Q931_RSN_UNKNOW_MSG              = 0x61;    //消息类型不存在
	public static final int  ITP_Q931_RSN_UNAVIABLE_STATUE        = 0x65;   //呼叫和状态不符合

	//承载能力
	//定义信息传递能力

	public static final int  ITP_Q931_CAP_SPEECH          = 0x00;  /* Speech Bearer Capability */
	public static final int  ITP_Q931_CAP_UNREST_DIG      = 0x08;  /* Unrestricted Digital Capability */
	public static final int  ITP_Q931_CAP_REST_DIG        = 0x09;  /* Restricted Digital Capability */
	public static final int  ITP_Q931_CAP_3DOT1K_AUDIO    = 0x10;  /* 3.1KHz Audio Capability */
	public static final int  ITP_Q931_CAP_7K_AUDIO        = 0x11;  /* 7KHz Audio Capability */
	public static final int  ITP_Q931_CAP_VIDEO           = 0x18;  /* Video Capability */


	//定义信息传递速率

	public static final int  ITP_Q931_RATE_64KBPS         = 0x10;  /* B_CHANNEL_UNITS 1X64 */
	public static final int  ITP_Q931_RATE_128KBPS        = 0x11;  /* Non-standard 2X64       */
	public static final int  ITP_Q931_RATE_384KBPS        = 0x13;  /* H0_CHANNEL_UNITS 6X64   */
	public static final int  ITP_Q931_RATE_1536KBPS       = 0x15;  /* H11_CHANNEL_UNITS 24X64 */
	public static final int  ITP_Q931_RATE_1920KBPS       = 0x17;  /* H12_CHANNEL_UNITS 30X64 */
	public static final int  ITP_Q931_RATE__MULTI_RATE    = 0x18;  /* Multirate (64 kbit/s base rate) */

	//定义传递方式
	public static final int  ITP_Q931_ITM_CIRCUIT         = 0x00;  /* 电路方式 */  //默认(only support)
	public static final int  ITP_Q931_ITM_PACKET          = 0x02;  /* 分组方式 */

	//定义用户一层协议
	public static final int  ITP_Q931_UIL1_CCITTV110      = 0x01;  /* user info layer 1 - CCITT V.110/X.3*/
	public static final int  ITP_Q931_UIL1_G711ALAW       = 0x03;  /* user info layer 1 - G.711 A-law */
	public static final int  ITP_Q931_UIL1_G721ADCPM      = 0x04;  /* user info layer 1 - G.721 ADCPM */
	public static final int  ITP_Q931_UIL1_G722G725       = 0x05;  /* user info layer 1 - G.722 and G.725 */
	public static final int  ITP_Q931_UIL1_H223_H245      = 0x06;  /*Recommendations H.223 [92] and H.245 [93] */
	public static final int  ITP_Q931_UIL1_DEFINE_USER    = 0x07;  /*Non-ITU-T standardized rate adaption. This implies the presence of octet 5a and, */
	                                           /*optionally, octets 5b, 5c and 5d. The use of this codepoint indicates that the user rate */
	                                           /*specified in octet 5a is defined by the user. Additionally, octets 5b, 5c and 5d, if present, */
	                                           /*are defined in accordance with the user specified rate adaption. */
	public static final int  ITP_Q931_UIL1_CCITTV120      = 0x08;  /* user info layer 1 - CCITT V.120 */
	public static final int  ITP_Q931_UIL1_CCITTX31       = 0x09;  /* user info layer 1 - CCITT X.31 */

	//定义号码类型
	public static final int  ITP_Q931_CALLNUM_UNKNOWN		        = 0x00;   //未知
	public static final int  ITP_Q931_CALLNUM_INTERNATIONAL	        = 0x01;   //国际号码
	public static final int  ITP_Q931_CALLNUM_DOMESTIC		        = 0x02;   //国内号码
	public static final int  ITP_Q931_CALLNUM_NETWORK_SPECIFIC      = 0x03;   //网络特定号码
	public static final int  ITP_Q931_CALLNUM_USER		 	        = 0x04;   //用户号码
	public static final int  ITP_Q931_CALLNUM_RESERVE		        = 0x07;   //扩展保留


	//定义号码编码类型
	public static final int  ITP_Q931_NUMPLAN_UNKNOWN                = 0x00;   //未知
	public static final int  ITP_Q931_NUMPLAN_ISDN                   = 0x01;   /* ISDN numb. plan E.164 */
	public static final int  ITP_Q931_NUMPLAN_TELEPHONY              = 0x02;   /* Telephony numb. plan E.163 */
	public static final int  ITP_Q931_NUMPLAN_PRIVATE                = 0x09;   /* Private numbering plan */
}

class ITP_Q931_CALL_PARAM
{
    public byte	 m_u8Cap;                //信息传递能力
    public byte	 m_u8ITM;                //传递方式
    public byte	 m_u8Rate;               //信息传递速率
    public byte	 m_u8UIL1;               //用户一层协议
    public byte	 m_u8CallerType;         //主叫号码类型
    public byte	 m_u8CallerPlan;         //主叫号码编码类型
    public byte	 m_u8CallerSubType;      //主叫子地址号码类型
    public byte	 m_u8CallerSubPlan;      //主叫子地址号码编码类型
    public byte	 m_u8CalleeType;         //被叫号码类型
    public byte	 m_u8CalleePlan;         //被叫号码编码类型
    public byte	 m_u8CalleeSubType;      //被叫子地址号码类型
    public byte	 m_u8CalleeSubPlan;      //被叫子地址号码编码类型
    
    public byte	 m_u8LowLevelFlag;       //低层兼容性标志: 0:表示没有此单元;1:表示有此单元
    public byte	 m_u8LowLevelLen;        //低层兼容性信息单元长度，目前只支持默认为5bytes的场景
    public byte	 m_u8LowLevelData[] = new byte[5];    //低层兼容性信息单元内容
    public byte	 reserved[]		 = new byte[29];           //保留字段
}

class ITP_Q931_ORINUM_PARAM
{
	public byte	 m_u8NumberType;         //号码类型
	public byte	 m_u8NumberPlan;         //号码编码类型
	public byte	 reserved[] = new byte[2];            //保留字段
	public byte	 m_szChangeNumber[] = new byte[32];   //原始主叫
}


/*消息类型*/
class ITP_Q931_MSG_TYPE
{
	public static final int  ITP_Q931_Resume       = 0x26;	 //恢复
	public static final int  ITP_Q931_Suspend      = 0x25;	 //暂停
	public static final int  ITP_Q931_Information  = 0x7b;    //信息 
	public static final int  ITP_Q931_Notify       = 0x6e;	 //通知
	public static final int  ITP_Q931_StatusEnquiry= 0x75;    //状态询问
}

//呼叫信息结构
class ITP_Q931_CALL_INFO_STRUCT
{
	public byte	 m_u8CallerLen;                      //主叫号码长度
	public byte	 m_u8CalleeLen;                      //被叫号码长度
	public byte	 m_u8CallerSubAddrLen;               //主叫号码子地址长度
	public byte	 m_u8CalleeSubAddrLen;               //被叫号码子地址长度
	public byte	 m_s8CallerId[]			= new byte[32];                   //主叫号码缓冲区
	public byte	 m_s8CalleeId[]			= new byte[32];                   //被叫号码缓冲区
	public byte	 m_s8CallerSubAddr[]	= new byte[32];              //主叫号码子地址缓冲区 
	public byte	 m_s8CalleeSubAddr[]	= new byte[32];              //被叫号码子地址缓冲区
}

//通道信息结构     
class ITP_Q931_CHNL_INFO_STRUCT
{
	public byte  m_u8UnitId;                        //DSP 单元ID
	public byte  m_u8Reserved;                      //保留
	public short m_u16Chnl;                         //DSP单元内的通道号
}

//发起一个呼叫
class ITP_Q931_CMD_TO_Q931_CALLOUT
{
	public ITP_Q931_CHNL_INFO_STRUCT m_ITP_q931ChnlInfo = new ITP_Q931_CHNL_INFO_STRUCT();     //通道信息
	public ITP_Q931_CALL_INFO_STRUCT m_ITP_q931CallInfo = new ITP_Q931_CALL_INFO_STRUCT();     //呼叫信息
	
	public byte                 m_u8CallerNumType;  //主叫号码类型 
	public byte                 m_u8CalleeNumType;  //被叫号码类型
	public short                m_u16OverlapFlag;   //重叠发送被叫号码标志
}

//追加被叫号码   
class ITP_Q931_CMD_TO_Q931_APPEND_CALLEEID
{
	public ITP_Q931_CHNL_INFO_STRUCT m_ITP_q931ChnlInfo = new ITP_Q931_CHNL_INFO_STRUCT();     //通道信息

	public byte                 m_u8Length;         //追加被叫号码长度
	public byte                 m_u8SendEnd;        //发送完全标志
	public byte                 m_s8Reserved[] = new byte[2];    //保留
	public byte                 m_s8CalleeBuf[]= new byte[32];  //被叫号码缓冲区
}

//设置通道状态
class ITP_Q931_CMD_TO_Q931_CHNL_STATE
{   
	public ITP_Q931_CHNL_INFO_STRUCT m_ITP_q931ChnlInfo = new ITP_Q931_CHNL_INFO_STRUCT();     //通道信息
	
	public byte                 m_u8State;                  //通道状态
    public byte                 m_s8Reserved[] = new byte[3];            //保留
}

//Q931模块向流程执行模块反馈通道状态
class ITP_Q931_EVENT_TO_FLOW_CHNL_STATE
{
	public byte                 m_u8State;          //通道状态
	public byte                 m_s8Reserved[] = new byte[3];    //保留
}

//Q931模块向流程执行模块反馈呼出结果
class ITP_Q931_EVENT_TO_FLOW_CALL_RESULT
{
	public byte                 m_u8CallResult;     //呼出结果
	public byte                 m_s8Reserved[] = new byte[3];    //保留
}

//Q931模块向流程执行模块反馈挂机原因
class ITP_Q931_EVENT_TO_FLOW_DISCONN_REASON
{
	public byte                 m_u8DisconnReason;  //挂机原因
	public byte                 m_s8Reserved[] = new byte[3];    //保留
}

class ITP_Q931_PARAM
{
    public ITP_Q931_CHNL_INFO_STRUCT m_ITP_q931ChnlInfo = new ITP_Q931_CHNL_INFO_STRUCT(); //通道信息
	
    public byte                 m_u8ErrorCode;       //错误代码

    public byte                 m_u8ParamType;       //参数类型
    public byte                 m_u8ParamLen;        //参数长度
    public byte                 m_s8ParamData[] = new byte[100];  //参数数据
}

class ITP_Q931_SIGNAL
{
    public ITP_Q931_CHNL_INFO_STRUCT m_ITP_q931ChnlInfo = new ITP_Q931_CHNL_INFO_STRUCT(); //通道信息

    public byte                 m_u8ErrorCode;       //错误代码
    public byte                 m_u8SignalType;      //信令类型
}

class ITP_Q931_STANDBY_LINK_STATE
{
	public byte                 m_u8LinkID;         //链路ID
	public byte                 m_u8State;          //链路状态
	public byte                 m_s8Reserved[] = new byte[2];    //保留
}


class ITP_Q931_STANDBY_CHNL_STATE
{
	public byte                 m_u8State;          //通道状态
	public short                m_sCRN;		 //call reference  呼叫参考
	public byte                 m_bIncall;
	public byte                 m_s8Reserved[] = new byte[4];    //保留
}

//UUI
class ITP_Q931_UUI_PARAM
{
	public byte	   m_u8UUIFlag;                       //UUI Set Flag
	public byte	   m_u8MsgType;                       //MSG Type
	public byte	   m_u8Len;                           //UUI's Length
	public byte	   m_u8UUIData[] = new byte[131];                  //UUI data buffer
}
