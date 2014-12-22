unit DJITPISDN;

interface

//Q931模块与流程执行模块之间通讯包包头子功能定义
const ITP_SUB_FUNC_FLOW_TO_Q931_GET_CHNL_STATE       = $01;     //获取通道状态  查询指定单元指定通道的当前状态
const ITP_SUB_FUNC_FLOW_TO_Q931_CALL_OUT             = $02;     //发起一个呼叫
const ITP_SUB_FUNC_FLOW_TO_Q931_APPEND_CALLEEID      = $03;     //追加被叫号码  发起呼叫后，追加被叫号码
const ITP_SUB_FUNC_FLOW_TO_Q931_GET_CALL_INFO        = $04;     //获取呼叫信息  获取呼叫信息，包括主叫号码、被叫号码等
const ITP_SUB_FUNC_FLOW_TO_Q931_GET_CALL_RESULT      = $05;     //获取呼出结果
const ITP_SUB_FUNC_FLOW_TO_Q931_GET_DISCONN_REASON   = $06;     //获取挂机原因
const ITP_SUB_FUNC_FLOW_TO_Q931_SET_CHNL_STATE       = $07;     //设置通道状态
const ITP_SUB_FUNC_FLOW_TO_Q931_SET_PARAM            = $08;     //设置参数
const ITP_SUB_FUNC_FLOW_TO_Q931_GET_PARAM            = $09;     //获取参数
const ITP_SUB_FUNC_FLOW_TO_Q931_SET_SIGNAL           = $10;     //设置信号

const ITP_SUB_FUNC_Q931_TO_FLOW_CHNL_STATE           = $11;     //反馈通道状态  当通道状态发生了迁移或接收到流程执行模块的请求包，Q931模块向流程执行模块发送本包，以告之流程执行模块指定通道的当前状态
const ITP_SUB_FUNC_Q931_TO_FLOW_CALL_INFO            = $12;     //反馈呼叫信息  当接收到流程执行模块的请求包，Q931模块向流程执行模块发送本包，包含主叫号码、被叫号码、主叫子地址、被叫子地址及它们的长度
const ITP_SUB_FUNC_Q931_TO_FLOW_CALL_RESULT          = $13;     //反馈呼出结果  当接收到流程执行模块的请求包，Q931模块向流程执行模块发送本包，以告之流程执行模块指定通道的呼出结果
const ITP_SUB_FUNC_Q931_TO_FLOW_DISCONN_REASON       = $14;     //反馈挂机原因  当接收到流程执行模块的请求包，Q931模块向流程执行模块发送本包，以告之流程执行模块指定通道的挂机原因
const ITP_SUB_FUNC_Q931_TO_FLOW_SET_PARAM            = $15;     //反馈设置参数结果
const ITP_SUB_FUNC_Q931_TO_FLOW_GET_PARAM            = $16;     //反馈获取参数结果
const ITP_SUB_FUNC_Q931_TO_FLOW_SET_SIGNAL           = $17;     //反馈设置信号结果

//Q931模块与同级模块之间的包头子功能定义
const ITP_SUB_FUNC_Q931_STANDBY_CHNL_STATE           = $01;
const ITP_SUB_FUNC_Q931_STANDBY_REQ_CHNL_STATE       = $02;

const ITP_SUB_FUNC_Q931_STANDBY_LINK_STATE           = $03;
const ITP_SUB_FUNC_Q931_STANDBY_REQ_LINK_STATE       = $04;


//Q931模块通道状态定义
const ITP_Q931_CH_FREE					        = 1;   //空闲状态
//#define ITP_Q931_CH_WAIT_APP_FREE		  = 2;   //Q931等待应用层同步释放资源
const ITP_Q931_CH_RESTART               = 2;
const ITP_Q931_CH_UNAVIABLE			        = 3;   //通道不可用
const ITP_Q931_CH_WAIT_CONNECT_ACK		  = 4;   //等待连接证实
const ITP_Q931_CH_CONNECT				        = 5;   //通道连通状态
const ITP_Q931_CH_WAIT_RELEASE			    = 6;   //已发送拆线信号，等待对方发送释放信号
const ITP_Q931_CH_WAIT_RELEASE_COMPLETE = 7;   //已发送释放信号，等待对方发送释放完成信号
const ITP_Q931_CALLEE_WAIT_ANSWER		    = 11;  //来话方，呼叫到达
const ITP_Q931_CALLER_WAIT_ANSWER		    = 12;  //去话方，已呼出，等待对方回应
const ITP_Q931_CALLER_RECV_ALERT		    = 21;  //去话方，已接收到提醒消息
const ITP_Q931_CALLER_RECV_SETUP_ACK	  = 22;  //去话方，已接收到建立确认消息
const ITP_Q931_CALLER_RECV_CALLPROCESS  = 23;  //去话方，已接收到呼叫进程消息
const ITP_Q931_CALLER_WAIT_SETUP_ACK	  = 24;  //去话方，等待建立确认
const ITP_Q931_CALLEE_WAIT_INFO         = $90; //来话方，等待后续被叫号码信息
const ITP_Q931_CALLEE_SEND_ALERT			  = $91; //来话方，发送了提醒消息


//通道动作定义
const	ITP_Q931_CH_SET_FREE			       = 1;    //APP 层检查通道状态为 OxO2 时，同步释放通道资源
const ITP_Q931_CH_SET_CONNECT		       = 2;    //设置通道连接
const ITP_Q931_CH_SET_DISCONNECT	     = 3;    //解除通道连接
const ITP_Q931_CALLEE_SET_ALERTING	   = 4;    //被叫方发送提醒消息
const	ITP_Q931_CH_SET_RESTART		       = 5;    //设置通道重新启动


//Q931呼出结果定义
const ITP_Q931_C_NO_RESULT		       = 0;    //尚未返回呼出结果
const ITP_Q931_C_USER_IDLE		       = 1;    //被叫空闲
const ITP_Q931_C_USER_OFFHOOK	       = 2;    //被叫摘机，连通
const ITP_Q931_C_WAIT_CALL_PROC      = 3;    //重叠发送被叫号码，等待对端确认被叫号码收齐
const ITP_Q931_C_OTHERS              = 10;   //其它结果，呼叫可能结束，请查询通道状态
const ITP_Q931_C_STATE_UNAVIABLE     = 11;   //状态不对，未进行呼出


//定义挂机原因
const ITP_Q931_RSN_UNKNOW_REASON           = $00;   //原因未知
const ITP_Q931_RSN_UNALLOC_NUMBER          = $01;   //空号
const ITP_Q931_RSN_NORMAL_DISCONNECT       = $10;   //正常的呼叫清除
const ITP_Q931_RSN_USER_BUSY               = $11;   //用户忙
const ITP_Q931_RSN_NO_RESPOND              = $12;   //无响应
const ITP_Q931_RSN_NO_ANSWER               = $13;   //无用户应答
const ITP_Q931_RSN_REFUSR_CALL             = $15;   //呼叫拒绝
const ITP_Q931_RSN_NUMBER_ERROR            = $1C;   //号码不全
const ITP_Q931_RSN_TIMEOUT	               = $66;   //超时
const ITP_Q931_RSN_DCHANNEL_DOWN           = $fd;   //链路中断
const ITP_Q931_RSN_BCHANNEL_UNAVIABLE      = $22;   //通道不可用
const ITP_Q931_RSN_UNAVIABLE_CIRCULT       = $2c;   //无可用通路

const ITP_Q931_RSN_UNAVIABLE_CRN           = $51;   //无效的参考值
const ITP_Q931_RSN_UNCOMPATIBLE            = $58;   //不兼容的终点
const ITP_Q931_RSN_UNAVIABLE_MSG           = $5F;   //无效的消息


const ITP_Q931_RSN_NEEDMSG_LOST            = $60;   //必须的信息单元丢失

const ITP_Q931_RSN_UNKNOW_MSG              = $61;    //消息类型不存在
const ITP_Q931_RSN_UNAVIABLE_STATUE        = $65;   //呼叫和状态不符合

//承载能力
//定义信息传递能力

const ITP_Q931_CAP_SPEECH          = $00;  //* Speech Bearer Capability */
const ITP_Q931_CAP_UNREST_DIG      = $08;  //* Unrestricted Digital Capability */
const ITP_Q931_CAP_REST_DIG        = $09;  //* Restricted Digital Capability */
const ITP_Q931_CAP_3DOT1K_AUDIO    = $10;  //* 3.1KHz Audio Capability */
const ITP_Q931_CAP_7K_AUDIO        = $11;  //* 7KHz Audio Capability */
const ITP_Q931_CAP_VIDEO           = $18;  //* Video Capability */


//定义信息传递速率

const ITP_Q931_RATE_64KBPS         = $10;  //* B_CHANNEL_UNITS 1X64 */
const ITP_Q931_RATE_128KBPS        = $11;  //* Non-standard 2X64       */
const ITP_Q931_RATE_384KBPS        = $13;  //* H0_CHANNEL_UNITS 6X64   */
const ITP_Q931_RATE_1536KBPS       = $15;  //* H11_CHANNEL_UNITS 24X64 */
const ITP_Q931_RATE_1920KBPS       = $17;  //* H12_CHANNEL_UNITS 30X64 */
const ITP_Q931_RATE__MULTI_RATE    = $18;  //* Multirate (64 kbit/s base rate) */

//定义传递方式
const ITP_Q931_ITM_CIRCUIT         = $00;  //* 电路方式 */  //默认(only support)
const ITP_Q931_ITM_PACKET          = $02;  //* 分组方式 */

//定义用户一层协议
const ITP_Q931_UIL1_CCITTV110      = $01;  //* user info layer 1 - CCITT V.110/X.3*/
const ITP_Q931_UIL1_G711ALAW       = $03;  //* user info layer 1 - G.711 A-law */
const ITP_Q931_UIL1_G721ADCPM      = $04;  //* user info layer 1 - G.721 ADCPM */
const ITP_Q931_UIL1_G722G725       = $05;  //* user info layer 1 - G.722 and G.725 */
const ITP_Q931_UIL1_H223_H245      = $06;  //*Recommendations H.223 [92] and H.245 [93] */
const ITP_Q931_UIL1_DEFINE_USER    = $07;  //*Non-ITU-T standardized rate adaption. This implies the presence of octet 5a and, */
                                           //*optionally, octets 5b, 5c and 5d. The use of this codepoint indicates that the user rate */
                                           //*specified in octet 5a is defined by the user. Additionally, octets 5b, 5c and 5d, if present, */
                                           //*are defined in accordance with the user specified rate adaption. */
const ITP_Q931_UIL1_CCITTV120      = $08;  //* user info layer 1 - CCITT V.120 */
const ITP_Q931_UIL1_CCITTX31       = $09;  //* user info layer 1 - CCITT X.31 */


//定义号码类型
const ITP_Q931_CALLNUM_UNKNOWN		        = $00;   //未知
const ITP_Q931_CALLNUM_INTERNATIONAL	    = $01;   //国际号码
const ITP_Q931_CALLNUM_DOMESTIC		        = $02;   //国内号码
const ITP_Q931_CALLNUM_NETWORK_SPECIFIC   = $03;   //网络特定号码
const ITP_Q931_CALLNUM_USER		 	          = $04;   //用户号码
const ITP_Q931_CALLNUM_RESERVE		        = $07;   //扩展保留


//定义号码编码类型
const ITP_Q931_NUMPLAN_UNKNOWN                = $00;   //未知
const ITP_Q931_NUMPLAN_ISDN                   = $01;   //* ISDN numb. plan E.164 */
const ITP_Q931_NUMPLAN_TELEPHONY              = $02;   //* Telephony numb. plan E.163 */
const ITP_Q931_NUMPLAN_PRIVATE                = $09;   //* Private numbering plan */

//数据结构定义

Type
  ITP_Q931_CALL_PARAM = record
  m_u8Cap           : Byte;        //信息传递能力
  m_u8ITM           : Byte;        //传递方式
  m_u8Rate          : Byte;        //信息传递速率
  m_u8UIL1          : Byte;        //用户一层协议
  m_u8CallerType    : Byte;        //主叫号码类型
  m_u8CallerPlan    : Byte;        //主叫号码编码类型
  m_u8CallerSubType : Byte;        //主叫子地址号码类型
  m_u8CallerSubPlan : Byte;        //主叫子地址号码编码类型
  m_u8CalleeType    : Byte;        //被叫号码类型
  m_u8CalleePlan    : Byte;        //被叫号码编码类型
  m_u8CalleeSubType : Byte;        //被叫子地址号码类型
  m_u8CalleeSubPlan : Byte;        //被叫子地址号码编码类型
  m_u8LowLevelFlag  : Byte;        //低层兼容性标志: 0:表示没有此单元;1:表示有此单元
	m_u8LowLevelLen   : Byte;        //低层兼容性信息单元长度，目前只支持默认为5bytes的场景
	m_u8LowLevelData  : Array[0..4] of Byte;    //低层兼容性信息单元内容
  reserved          : Array[0..28] of Byte;   //保留字段
end;

Type
  ITP_Q931_ORINUM_PARAM = record
  m_u8NumberType : Byte;         //号码类型
  m_u8NumberPlan : Byte;         //号码编码类型
  reserved         : Array[0..1] of Byte;        //保留字段
	m_szChangeNumber : Array[0..31] of ShortInt;   //原始主叫
end;


//*消息类型*/
Type ITP_Q931_MSG_TYPE = 
(
	ITP_Q931_Resume          = $26,	 //恢复
	ITP_Q931_Suspend         = $25,	 //暂停

	ITP_Q931_Information     = $7b,   //信息
	ITP_Q931_Notify          = $6e,	 //通知
	ITP_Q931_StatusEnquiry   = $75    //状态询问
);

//呼叫信息结构
Type
  ITP_Q931_CALL_INFO_STRUCT = record
	m_u8CallerLen : Byte;                      //主叫号码长度
  m_u8CalleeLen : Byte;                      //被叫号码长度
  m_u8CallerSubAddrLen : Byte;               //主叫号码子地址长度
  m_u8CalleeSubAddrLen : Byte;               //被叫号码子地址长度
  m_s8CallerId : Array[0..31] of ShortInt;                   //主叫号码缓冲区
  m_s8CalleeId : Array[0..31] of ShortInt;                   //被叫号码缓冲区
  m_s8CallerSubAddr : Array[0..31] of ShortInt;              //主叫号码子地址缓冲区
  m_s8CalleeSubAddr : Array[0..31] of ShortInt;              //被叫号码子地址缓冲区
end;

//通道信息结构     
Type
  ITP_Q931_CHNL_INFO_STRUCT = record
	m_u8UnitId   : Byte;                      //DSP 单元ID
  m_u8Reserved : Byte;                      //保留
  m_u16Chnl    : Word;                      //DSP单元内的通道号
end;

//发起一个呼叫
Type
  ITP_Q931_CMD_TO_Q931_CALLOUT = record
	m_ITP_q931ChnlInfo : ITP_Q931_CHNL_INFO_STRUCT;     //通道信息
  m_ITP_q931CallInfo : ITP_Q931_CALL_INFO_STRUCT;     //呼叫信息
	
	m_u8CallerNumType : Byte;  //主叫号码类型
  m_u8CalleeNumType : Byte;  //被叫号码类型
  m_u16OverlapFlag : Word;   //重叠发送被叫号码标志
end;

//追加被叫号码   
Type
  ITP_Q931_CMD_TO_Q931_APPEND_CALLEEID = record
	m_ITP_q931ChnlInfo : ITP_Q931_CHNL_INFO_STRUCT;     //通道信息

	m_u8Length  : Byte;         //追加被叫号码长度
  m_u8SendEnd : Byte;         //发送完全标志

  m_s8Reserved  : Array[0..1] of ShortInt;    //保留
  m_s8CalleeBuf : Array[0..31] of ShortInt;   //被叫号码缓冲区
end;

//设置通道状态
Type
  ITP_Q931_CMD_TO_Q931_CHNL_STATE  =record
	m_ITP_q931ChnlInfo : ITP_Q931_CHNL_INFO_STRUCT;     //通道信息

  m_u8State    : Byte;                                //通道状态
  m_s8Reserved : Array[0..2] of ShortInt;             //保留
end;

//Q931模块向流程执行模块反馈通道状态
Type
  ITP_Q931_EVENT_TO_FLOW_CHNL_STATE = record
	m_u8State    : Byte;          //通道状态
  m_s8Reserved : Array[0..2] of ShortInt;    //保留
end;

//Q931模块向流程执行模块反馈呼出结果
Type
  ITP_Q931_EVENT_TO_FLOW_CALL_RESULT = record
	m_u8CallResult : Byte;     //呼出结果
  m_s8Reserved   : Array[0..2] of ShortInt;    //保留
end;

//Q931模块向流程执行模块反馈挂机原因
Type
  ITP_Q931_EVENT_TO_FLOW_DISCONN_REASON = record
	m_u8DisconnReason : byte;  //挂机原因
  m_s8Reserved : Array[0..2] of ShortInt;    //保留
end;

Type
  ITP_Q931_PARAM = record
  m_ITP_q931ChnlInfo : ITP_Q931_CHNL_INFO_STRUCT; //通道信息
	
	m_u8ErrorCode : Byte;       //错误代码
	m_u8ParamType : Byte;       //参数类型
  m_u8ParamLen  : Byte;       //参数长度

 m_s8ParamData  : Array[0..99] of ShortInt;  //参数数据
end;

Type
  ITP_Q931_SIGNAL = record
  m_ITP_q931ChnlInfo : ITP_Q931_CHNL_INFO_STRUCT; //通道信息

  m_u8ErrorCode : Byte;       //错误代码
  m_u8SignalType : Byte;      //信令类型
end;

Type
  ITP_Q931_STANDBY_LINK_STATE = record
	m_u8LinkID   : Byte;          //链路ID
	m_u8State    : Byte;          //链路状态
  m_s8Reserved : Array[0..1] of ShortInt;    //保留
end;


Type
  ITP_Q931_STANDBY_CHNL_STATE = record
	m_u8State    : Byte;          //通道状态
	m_sCRN       : SmallInt;		  //call reference  呼叫参考
	m_bIncall    : Byte;
  m_s8Reserved : Array[0..3] of ShortInt;    //保留
end;

//UUI
Type
  ITP_Q931_UUI_PARAM = record
	m_u8UUIFlag : Byte;                       //UUI Set Flag
	m_u8MsgType : Byte;                       //MSG Type
	m_u8Len     : Byte;                       //UUI's Length
  m_u8UUIData : Array[0..130] of Byte;      //UUI data buffer
end;

implementation

end.
