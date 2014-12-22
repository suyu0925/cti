unit DJMissCall;

interface

uses
  SysUtils, Variants, Messages, Windows;
  
const DJSSM_CALL_GENERATE			= $01;	// 呼叫发起
const DJSSM_CALL_CONNECT			= $02;	// 通话建立
const DJSSM_CALL_DISCONNECT		= $03;	// 通话断开
const DJSSM_CALL_INFO				  = $04;	// 呼叫信息
const DJSSM_CALL_INFO_ACM			= $05;	// 收到ACM消息

const FORCE_MODE					= $01;	// 强制重连

// TUP遇忙信号
const CALLEE_SLB					= $1E;	// 被叫市话忙
const CALLEE_SSB					= $65;	// 被叫忙
const CALLEE_STB					= $2E;	// 被叫长话忙

const CALLEE_LOS					= $85;	// 线路退出服务
const CALLEE_CGC					= $25;	// 电路群拥塞
const CALLEE_ADI					= $45;	// 地址不全
const CALLEE_SEC					= $15;	// 交换设备拥塞
const CALLEE_UNN					= $75;	// 未分配号码信号
const CALLEE_SST					= $95;	// 特别信号音
const CALLEE_EUM					= $F5;	// 后向建立不成功（扩充）

// TUP拆线信号
const CALLINF_CLF					= $46;	// 前向拆线
const CALLINF_CBK					= $36;	// 后向拆线

// ISUP呼叫释放原因值
Type CAUSE_VALUE =
(
	RSN_UNALLOCATED_NUMBER   = $01,		//空号
	RSN_NORMAL_CALL_CLEARING = $10,	  //正常的呼叫清除
	RSN_USER_BUSY            = $11,		//用户忙
	RSN_NO_USER_RESPONDING   = $12,		//无用户响应，超时没有收到ACM
	RSN_USER_ALERTING_NO_ANSWER = $13, //被叫无应答，超时未摘机
	RSN_CALL_REJECTED        = $15,		//呼叫拒绝
	RSN_INCOMPLETE_NUMBER    = $1c,		//不完整的号码
	RSN_NORMAL_NO_SET        = $1f,		//正常，未规定
	RSN_NO_CIRCUIT_CHANNELAVAILABLE = $22,           //无可用的电路
	RSN_REQUESTEDCIRCUIT_CHANNEL_NOTAVAILABLE = $2c, //请求的电路不可用
	RSN_RECOVERY_ON_TIME_EXPIRY = $66,	//定时器超时恢复

	RSN_LOCAL_RLC   = $20,			//本地释放电路
	RSN_RECEIVE_RSC = $21 			//电路复原
);

const ERR_DMSU_SOCKFAIL			    = 1000;//-1		// 创建到DMSU连接socket失败
const ERR_DMSU_CONNECTFAIL		  = 2000;//-2		// 连接DMSU失败
const ERR_DMSU_INITRPARSERFAIL	= -3;		// 初始化消息解析队列失败
const ERR_DMSU_INITFRAGMENTFAIL	= -4;		// 初始化数据交换队列失败
const ERR_DMSU_INITRECVFAIL		  = -5;		// 初始化接收队列失败
const ERR_DMSU_STARTRECVTFAIL		= -6;		// 启动接收线程失败
const ERR_DMSU_STARTHEARTTFAIL	= -7;		// 启动心跳线程失败
const ERR_DMSU_STARTPARSERTFAIL = -8;		// 启动解析线程失败
const ERR_DMSU_NOTEXISTS			  = -9;		// 连接不存
const ERR_DMSU_CONNECTIONOK		  = -10;		// 当前连接正常

const ERR_EVT_NODATA				    = -1;		// 没有接收到数据
const ERR_EVT_GETDATAFAIL			  = -2;		// 获取数据失败
const ERR_EVT_DATANOTENOUGH		  = -3;		// 数据长度不足
const ERR_EVT_NOTEXISTS			    = -4;		// 连接不存在
const ERR_EVT_DISCONNECT			  = -5;		// 到DMSU的连接断开

Type
  tSockInfo = record
	Addr    : Array[0..15] of ShortInt;
	Port    : Word;
	BufSize : DWORD;
	RecvBufSize : DWORD;
	UnitID  : Byte;
end;

Type
  tMonEvt = record
	caller_id : Array[0..31] of ShortInt;			// 主叫号码
	callee_id : Array[0..31] of ShortInt;			// 被叫号码
	original_callee_id : Array[0..31] of ShortInt;// 原被叫号码
	Even       : Byte;		  // 事件指示码
	LocalPcmID : Byte;	    // 本地获得信令数据PCM号
	pcm        : Byte;			// 信令数据描述中继号
	chn        : Byte;			// 信令数据描述时隙号
	Protocol   : Byte;		  // 协议类型
	SubProtocol: Byte;	    // 协议子类型
	ToneID     : Integer;		// 保留字
	ReleaseReason : Byte;   // 拆线原因值
	MsgType    : Byte;		  // 消息类型
	DPC        : Integer;
	OPC        : Integer;
	DataLen    : Integer;					        // 原始包长度
	OriginalData : Array[0..299] of Byte; // 原始包 CR20061116_01
end;

// 信息掩码
const SYS_INFO_BUFFER			 =	00;		// 消息队列信息

/////////////////////////////////////////////////////////////////////////
// 出错提示
const SYS_NOT_EXISTS			 =	-1;		// 指定的DMSU设备不存在
const SYS_MAX_INFO_LEN		 =	128;		// 信息内容最大长度

// 结构定义
Type
  tSysBufInfo = record
	BuffID  : byte;
	BufSize : Integer;
	InUse   : Integer;
end;

Type
  tSysState = record
	sysID : Byte;						// 返回信息类属资源
	infoLen : Byte;					// 信息长度
	info : Array[0..SYS_MAX_INFO_LEN-1] of Byte;		// 信息内容
end;

implementation

end.
