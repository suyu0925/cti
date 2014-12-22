package DJKeygoe;

public class DJMissCall {
	public static final int DJSSM_CALL_GENERATE			= 0x01;	// 呼叫发起
	public static final int DJSSM_CALL_CONNECT			= 0x02;	// 通话建立
	public static final int DJSSM_CALL_DISCONNECT		= 0x03;	// 通话断开
	public static final int DJSSM_CALL_INFO				= 0x04;	// 呼叫信息
	public static final int DJSSM_CALL_INFO_ACM			= 0x05;	// 收到ACM消息
		
	public static final int FORCE_MODE					= 0x01;	// 强制重连

	// TUP遇忙信号
	public static final int CALLEE_SLB					= 0x1E;	// 被叫市话忙	
	public static final int CALLEE_SSB					= 0x65;	// 被叫忙
	public static final int CALLEE_STB					= 0x2E;	// 被叫长话忙

	public static final int CALLEE_LOS					= 0x85;	// 线路退出服务
	public static final int CALLEE_CGC					= 0x25;	// 电路群拥塞
	public static final int CALLEE_ADI					= 0x45;	// 地址不全
	public static final int CALLEE_SEC					= 0x15;	// 交换设备拥塞
	public static final int CALLEE_UNN					= 0x75;	// 未分配号码信号
	public static final int CALLEE_SST					= 0x95;	// 特别信号音
	public static final int CALLEE_EUM					= 0xF5;	// 后向建立不成功（扩充）

	// TUP拆线信号
	public static final int CALLINF_CLF					= 0x46;	// 前向拆线
	public static final int CALLINF_CBK					= 0x36;	// 后向拆线
	
	
	public static final int  ERR_DMSU_SOCKFAIL			= 1000;//-1		// 创建到DMSU连接socket失败
	public static final int  ERR_DMSU_CONNECTFAIL		= 2000;//-2		// 连接DMSU失败
	public static final int  ERR_DMSU_INITRPARSERFAIL	= -3;		// 初始化消息解析队列失败
	public static final int  ERR_DMSU_INITFRAGMENTFAIL	= -4;		// 初始化数据交换队列失败
	public static final int  ERR_DMSU_INITRECVFAIL		= -5;		// 初始化接收队列失败
	public static final int  ERR_DMSU_STARTRECVTFAIL	= -6;		// 启动接收线程失败
	public static final int  ERR_DMSU_STARTHEARTTFAIL	= -7;		// 启动心跳线程失败
	public static final int  ERR_DMSU_STARTPARSERTFAIL  = -8;		// 启动解析线程失败
	public static final int  ERR_DMSU_NOTEXISTS			= -9;		// 连接不存
	public static final int  ERR_DMSU_CONNECTIONOK		= -10;		// 当前连接正常
		
	public static final int  ERR_EVT_NODATA				= -1;		// 没有接收到数据
	public static final int  ERR_EVT_GETDATAFAIL		= -2;		// 获取数据失败
	public static final int  ERR_EVT_DATANOTENOUGH		= -3;		// 数据长度不足
	public static final int  ERR_EVT_NOTEXISTS			= -4;		// 连接不存在
	public static final int  ERR_EVT_DISCONNECT			= -5;		// 到DMSU的连接断开

////////////////////////////////////////////////////////////////////////////
	// 设置原始信令包传送方式  CR20061116_01

	// 解析掩码
	public static final int  PRO_TRANS		 = 0x00;	// 透传
	public static final int  PRO_PARSER		 = 0x01;	// 解析
	public static final int  PRO_BOTH		 = 0x02;	// 解析并传送

	// 操作掩码
	public static final int  PRO_ADD		 = 0x00;	// 添加
	public static final int  PRO_REMOVE		 = 0x01;	// 移除
	public static final int  PRO_MODIFY		 = 0x02;	// 修改
	
/////////////////////////////////////////////////////////////////////////
	// 系统状态信息 CR20061116_02
	//

	/////////////////////////////////////////////////////////////////////////
	// 信息掩码
	public static final int SYS_INFO_BUFFER				= 00;		// 消息队列信息

	/////////////////////////////////////////////////////////////////////////
	// 出错提示
	public static final int SYS_NOT_EXISTS				= -1;		// 指定的DMSU设备不存在
	public static final int SYS_MAX_INFO_LEN			= 128;		// 信息内容最大长度
}

// ISUP呼叫释放原因值
class CAUSE_VALUE
{
	public static final int RSN_UNALLOCATED_NUMBER 		= 0x01;		//空号
	public static final int RSN_NORMAL_CALL_CLEARING 	= 0x10;	//正常的呼叫清除
	public static final int RSN_USER_BUSY 				= 0x11;				//用户忙
	public static final int RSN_NO_USER_RESPONDING 		= 0x12;		//无用户响应，超时没有收到ACM
	public static final int RSN_USER_ALERTING_NO_ANSWER = 0x13; //被叫无应答，超时未摘机
	public static final int RSN_CALL_REJECTED 			= 0x15;			//呼叫拒绝
	public static final int RSN_INCOMPLETE_NUMBER 		= 0x1c;		//不完整的号码
	public static final int RSN_NORMAL_NO_SET 			= 0x1f;			//正常，未规定
	public static final int RSN_NO_CIRCUIT_CHANNELAVAILABLE 			= 0x22;//无可用的电路
	public static final int RSN_REQUESTEDCIRCUIT_CHANNEL_NOTAVAILABLE 	= 0x2c; //请求的电路不可用
	public static final int RSN_RECOVERY_ON_TIME_EXPIRY = 0x66;	//定时器超时恢复

	public static final int RSN_LOCAL_RLC 				= 0x20;				//本地释放电路
	public static final int RSN_RECEIVE_RSC 			= 0x21;				//电路复原
}

class tSockInfo
{
	public byte  Addr[] = new byte[16];
	public short Port;
	public long  BufSize;
	public long  RecvBufSize;
	public char  UnitID;
}

class tMonEvt
{
	public byte caller_id[]		   = new byte[32];			// 主叫号码
	public byte callee_id[]		   = new byte[32];			// 被叫号码
	public byte original_callee_id[] = new byte[32];// 原被叫号码
	public byte Event;		// 事件指示码
	public byte LocalPcmID;	// 本地获得信令数据PCM号
	public byte pcm;			// 信令数据描述中继号
	public byte chn;			// 信令数据描述时隙号
	public byte Protocol;		// 协议类型
	public byte SubProtocol;	// 协议子类型 
	public int  ToneID;		// 保留字
	public byte ReleaseReason;// 拆线原因值
	public byte MsgType;		// 消息类型
	public int  DPC;
	public int  OPC; 	
	public int  DataLen;					 // 原始包长度
	public byte OriginalData[] = new byte[300]; // 原始包 CR20061116_01
}


/////////////////////////////////////////////////////////////////////////
// 结构定义
class tSysBufInfo{
	public byte BuffID;
	public int  BufSize;
	public int  InUse;	
}

class tSysState
{
	public byte sysID;						// 返回信息类属资源
	public byte infoLen;						// 信息长度
	public byte info[] = new byte[128];		// 信息内容
}

// end CR20061116_02


// 协议工作模式
class tProtocolMode
{
	public byte	Protocol;
	public byte WorkMode;
}

// END CR20061116_01

// CR20070830_001
class DMSU_LOG
{
	public int LogType;
	public long Param1;
}
