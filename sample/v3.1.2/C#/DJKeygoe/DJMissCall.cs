using System;
using System.Collections.Generic;
using System.Text;

namespace DJKeygoe
{
    using DJ_U8 = Byte;
    using DJ_S8 = SByte;
    using DJ_U16 = UInt16;
    using DJ_U32 = UInt32;
    using DJ_S32 = Int32;

    class DJMissCall
    {
        public const DJ_S32   DJSSM_CALL_GENERATE		=	0x01;	// 呼叫发起
        public const DJ_S32   DJSSM_CALL_CONNECT			=  0x02;	// 通话建立
        public const DJ_S32   DJSSM_CALL_DISCONNECT	=	0x03	;// 通话断开
        public const DJ_S32   DJSSM_CALL_INFO				    =  0x04;	// 呼叫信息
        public const DJ_S32   DJSSM_CALL_INFO_ACM		=	0x05;	// 收到ACM消息
        	
        public const DJ_S32   FORCE_MODE				=	0x01;	// 强制重连

        // TUP遇忙信号
        public const DJ_S32   CALLEE_SLB				=	0x1E;	// 被叫市话忙	
        public const DJ_S32   CALLEE_SSB				=	0x65;	// 被叫忙
        public const DJ_S32   CALLEE_STB				=	0x2E;	// 被叫长话忙

        public const DJ_S32   CALLEE_LOS				=	0x85;	// 线路退出服务
        public const DJ_S32   CALLEE_CGC				=	0x25;	// 电路群拥塞
        public const DJ_S32   CALLEE_ADI				=	0x45;	// 地址不全
        public const DJ_S32   CALLEE_SEC				=	0x15	;// 交换设备拥塞
        public const DJ_S32   CALLEE_UNN				=	0x75;	// 未分配号码信号
        public const DJ_S32   CALLEE_SST				=	0x95;	// 特别信号音
        public const DJ_S32   CALLEE_EUM				=	0xF5;	// 后向建立不成功（扩充）

        // TUP拆线信号
        public const DJ_S32   CALLINF_CLF				=	0x46	;// 前向拆线
        public const DJ_S32   CALLINF_CBK				=	0x36;// 后向拆线

        public const DJ_S32 ERR_DMSU_SOCKFAIL                  = 1000;//-1		// 创建到DMSU连接socket失败
        public const DJ_S32 ERR_DMSU_CONNECTFAIL		    = 2000;//-2		// 连接DMSU失败
        public const DJ_S32 ERR_DMSU_INITRPARSERFAIL	    = -3;		// 初始化消息解析队列失败
        public const DJ_S32 ERR_DMSU_INITFRAGMENTFAIL	= -4;		// 初始化数据交换队列失败
        public const DJ_S32 ERR_DMSU_INITRECVFAIL		    = -5;		// 初始化接收队列失败
        public const DJ_S32 ERR_DMSU_STARTRECVTFAIL		= -6;		// 启动接收线程失败
        public const DJ_S32 ERR_DMSU_STARTHEARTTFAIL	    = -7;		// 启动心跳线程失败
        public const DJ_S32 ERR_DMSU_STARTPARSERTFAIL   = -8;		// 启动解析线程失败
        public const DJ_S32 ERR_DMSU_NOTEXISTS			    = -9;		// 连接不存
        public const DJ_S32 ERR_DMSU_CONNECTIONOK		= -10;		// 当前连接正常
        	
        public const DJ_S32 ERR_EVT_NODATA				        = -1;		// 没有接收到数据
        public const DJ_S32 ERR_EVT_GETDATAFAIL			    = -2;		// 获取数据失败
        public const DJ_S32 ERR_EVT_DATANOTENOUGH		    = -3;		// 数据长度不足
        public const DJ_S32 ERR_EVT_NOTEXISTS			        = -4;		// 连接不存在
        public const DJ_S32 ERR_EVT_DISCONNECT			    = -5;		// 到DMSU的连接断开

        
        // 解析掩码
        public const DJ_U8  PRO_TRANS		 = 0x00;	// 透传
        public const DJ_U8  PRO_PARSER		 = 0x01;	// 解析
        public const DJ_U8  PRO_BOTH		 = 0x02;	// 解析并传送

        // 操作掩码
        public const DJ_U8  PRO_ADD		     = 0x00;	// 添加
        public const DJ_U8  PRO_REMOVE	 = 0x01;	// 移除
        public const DJ_U8  PRO_MODIFY      = 0x02;	// 修改
    }

    // ISUP呼叫释放原因值
    public enum CAUSE_VALUE
    {
        RSN_UNALLOCATED_NUMBER = 0x01,		//空号
        RSN_NORMAL_CALL_CLEARING = 0x10,	//正常的呼叫清除
        RSN_USER_BUSY = 0x11,				//用户忙
        RSN_NO_USER_RESPONDING = 0x12,		//无用户响应，超时没有收到ACM
        RSN_USER_ALERTING_NO_ANSWER = 0x13, //被叫无应答，超时未摘机
        RSN_CALL_REJECTED = 0x15,			//呼叫拒绝
        RSN_INCOMPLETE_NUMBER = 0x1c,		//不完整的号码
        RSN_NORMAL_NO_SET = 0x1f,			//正常，未规定
        RSN_NO_CIRCUIT_CHANNELAVAILABLE = 0x22, //无可用的电路
        RSN_REQUESTEDCIRCUIT_CHANNEL_NOTAVAILABLE = 0x2c, //请求的电路不可用
        RSN_RECOVERY_ON_TIME_EXPIRY = 0x66,	//定时器超时恢复

        RSN_LOCAL_RLC = 0x20,				//本地释放电路
        RSN_RECEIVE_RSC = 0x21,				//电路复原
    };

    public unsafe struct tagSockInfo
    {
	    public fixed DJ_S8 Addr[16];
	    public DJ_U16       Port;
	    public DJ_U32       BufSize;
	    public DJ_U32       RecvBufSize;
	    public DJ_U8         UnitID;
    };

    public unsafe struct tagMonEvt
    {
	    public fixed DJ_S8 caller_id[32];			// 主叫号码
	    public fixed DJ_S8 callee_id[32];			// 被叫号码
	    public fixed DJ_S8 original_callee_id[32];// 原被叫号码
	    public DJ_U8         Event;		// 事件指示码
	    public DJ_U8          LocalPcmID;	// 本地获得信令数据PCM号
	    public DJ_U8          pcm;			// 信令数据描述中继号
	    public DJ_U8          chn;			// 信令数据描述时隙号
	    public DJ_U8          Protocol;		// 协议类型
	    public DJ_U8          SubProtocol;	// 协议子类型 
	    public DJ_U32        ToneID;		// 保留字
	    public DJ_U8          ReleaseReason;// 拆线原因值
	    public DJ_U8          MsgType;		// 消息类型
	    public DJ_S32        DPC;
	    public DJ_S32        OPC; 	
	    public DJ_S32        DataLen;					 // 原始包长度
	    public fixed DJ_U8 OriginalData[300]; // 原始包 CR20061116_01
    };

    // 结构定义
    public struct tSysBufInfo
    {
        public DJ_U8 BuffID;
        public DJ_S32 BufSize;
        public DJ_S32 InUse;	
    };

    public unsafe struct tSysState
    {
        public DJ_U8 sysID;						// 返回信息类属资源
        public DJ_U8 infoLen;						// 信息长度
        public fixed DJ_U8 info[ConstantVar.SYS_MAX_INFO_LEN];		// 信息内容
    };

    // 协议工作模式
    public struct tProtocolMode
    {
	    public DJ_U8 Protocol;
	    public DJ_U8 WorkMode;
    };

    // END CR20061116_01

    // CR20070830_001
    public struct DMSU_LOG
    {
        public DJ_S32 LogType;
        public DJ_S32 Param1;
    };
}
