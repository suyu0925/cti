unit DJAcsSignalMonitor;

interface

Type ITP_SIGMonitor_EventType =       // 信令监控事件定义
(
	SMON_EVT_Call_Generate    =  $01, // 呼叫发起
  SMON_EVT_Call_Connect     =  $02, // 呼叫连接
	SMON_EVT_Call_Disconnect  =  $03, // 呼叫断开
	SMON_EVT_Call_Info        =  $04, // 呼叫信息
	SMON_Evt_Gen_Signal_Info  =  $05, // 信令信息
	SMON_Evt_Raw_Signal_Info  =  $06  // 原始信息
);


Type ITP_SIGMonitor_Protocol =          // 信令监控协议定义
(
	SMON_Protocol_ISDN      = $01,  // ISDN信令
	SMON_Protocol_SS7       = $02,  // 七号信令
	SMON_Protocol_N64K      = $03   // N64K
);


Type ITP_SIGMonitor_SI =                // 业务表示语定义
(
	SMON_SI_SCCP = $03,             // SCCP
  SMON_SI_TUP  = $04,             // TUP
	SMON_SI_ISUP = $05             // ISUP
);


Type ITP_SIGMonitor_ISUP_MsgType =      // 信令监控消息定义
(
	SMON_ISUP_ACM = $06,		     // 地址全消息
	SMON_ISUP_ANM = $09,		     // 应答消息
	
	SMON_ISUP_CON = $07,		     // 接续消息
	
	SMON_ISUP_INF = $04,		     // 信息消息
	SMON_ISUP_IAM = $01,		     // 初始地址消息
	
	SMON_ISUP_REL = $0C,		     // 释放消息
	SMON_ISUP_RLC = $10,		     // 释放完成消息
	
	SMON_ISUP_SAM = $02,		     // 后续地址消息
	
	//
	SMON_ISUP_CPG = $2C,		     // 呼叫进展消息
	SMON_ISUP_CQR = $2B,		     // 电路群询问响应消息
	SMON_ISUP_GRA = $29,		     // 电路群复原证实消息
	SMON_ISUP_CFN = $2F,		     // 混淆消息
	
	SMON_ISUP_COT = $05,		     // 导通消息
	SMON_ISUP_FRJ = $21,		     // 性能拒绝消息
	
	SMON_ISUP_INR = $03,		     // 信息请求消息
	
	SMON_ISUP_USR = $2D,		     // 用户至用户消息
	SMON_ISUP_FOT = $08,		     // 前向传递消息
	
	SMON_ISUP_RES = $0E,		     // 恢复消息
	SMON_ISUP_SUS = $0D,		     // 暂停消息
	
	SMON_ISUP_BLO = $13,		     // 闭塞消息
	SMON_ISUP_BLA = $15,		     // 闭塞证实消息
	SMON_ISUP_CCR = $11,		     // 导通检验请求消息
	SMON_ISUP_LPA = $24,		     // 环路确认消息
	SMON_ISUP_OLM = $30,		     // 过负荷消息
	SMON_ISUP_RSC = $12,		     // 电路复原消息
	SMON_ISUP_UBL = $14,		     // 解除闭塞消息
	SMON_ISUP_UBA = $16,		     // 解除闭塞证实消息
	SMON_ISUP_UCIC= $2E,		     // 未装备电路识别码消息
	
	SMON_ISUP_CGB = $18,		     // 电路群闭塞消息
	SMON_ISUP_CGBA= $1A,		     // 电路群闭塞证实消息
	SMON_ISUP_CGU = $19,		     // 电路群闭塞解除消息
	SMON_ISUP_CGUA= $1B,		     // 电路群闭塞解除证实消息
	
	SMON_ISUP_GRS = $17,		     // 电路群复原消息
	SMON_ISUP_CQM = $2A,		     // 电路群询问消息
	
	SMON_ISUP_FAA = $20,		     // 性能接受消息
	SMON_ISUP_FAR = $1F,		     // 性能请求消息
	
	SMON_ISUP_PAM = $28,		     // 传递消息
	
	SMON_ISUP_UPT = $34,		     // 用户部分测试
	SMON_ISUP_UPA = $35,		     // 用户部分可利用
	
	SMON_ISUP_FAC = $33,		     // 性能消息
	SMON_ISUP_NRM = $32,		     // 网络资源管理
	SMON_ISUP_IDR = $36,		     // 识别请求
	SMON_ISUP_IRS = $37,		     // 识别响应
	SMON_ISUP_SGM = $38,		     // 分段
	
	SMON_ISUP_CRG = $31,		     // 计费信息
	SMON_ISUP_OPR = $FE,		     // 话务员消息
	SMON_ISUP_MPM = $FD,		     // 计次脉冲
	SMON_ISUP_CCL = $FC 		     // 主叫挂机
);


Type ITP_SIGMonitor_TUP_MsgType =       // 信令监控消息定义
(
	SMON_TUP_IAM = $11,             // 初始地址消息
	SMON_TUP_IAI = $21,             // 带有附加信息的初始地址消息
	SMON_TUP_SAM = $31,             // 后续地址消息
	SMON_TUP_SAO = $41,             // 带有一个地址信号的后续地址消息
	
	SMON_TUP_ACM = $14,             // 地址收全消息
	
	SMON_TUP_SEC = $15,             // 交换设备拥塞信号
	SMON_TUP_CGC = $25,             // 电路群拥塞信号
	SMON_TUP_NNC = $35,             // 国家网拥塞信号
	SMON_TUP_ADI = $45,             // 地址不全信号
	SMON_TUP_CFL = $55,             // 呼叫故障信号
	SMON_TUP_SSB = $65,             // 用户忙信号
	SMON_TUP_UNN = $75,             // 空号
	SMON_TUP_LOS = $85,             // 线路不工作信号
	SMON_TUP_SST = $95,             // 发送专用信息音信号
	SMON_TUP_ACB = $A5,             // 接入拒绝信号
	SMON_TUP_DPN = $B5,             // 不提供数字通路信号
	SMON_TUP_MPR = $C5,             // 误播中继前缀
	
	SMON_TUP_SLB = $1E,             // 用户市忙信号
	SMON_TUP_STB = $2E,             // 用户长忙信号
	
	SMON_TUP_ANU = $06,             // 应答信号，计费未说明
	SMON_TUP_ANC = $16,             // 应答信号、收费
	SMON_TUP_ANN = $26,             // 应答信号、免费
	SMON_TUP_CBK = $36,             // 挂机信号
	SMON_TUP_CLF = $46,             // 拆线信号
	
	SMON_TUP_RLG = $17,             // 释放监护信号
	
	SMON_TUP_GSM = $12,             // 一般前向建立信息消息
	
	//
	SMON_TUP_COT = $32,             // 导通信号
	SMON_TUP_CCF = $42,             // 导通故障信号
		
	SMON_TUP_GRQ = $13,             // 一般请求消息
	
	SMON_TUP_CHG = $24,             // 计费消息
		
	SMON_TUP_EUM = $F5,             // 扩充的后向建立不成功消息
			
	SMON_TUP_RAN = $56,             // 再应答信号
	SMON_TUP_FOT = $66,             // 前向转移信号
	SMON_TUP_CCL = $76,             // 主叫用户挂机信号
	
	SMON_TUP_BLO = $27,             // 闭塞信号
	SMON_TUP_BLA = $37,             // 闭塞证实信号
	SMON_TUP_UBL = $47,             // 解除闭塞信号
	SMON_TUP_UBA = $57,             // 解除闭塞证实信号
	SMON_TUP_CCR = $67,             // 请求导通检验信号
	SMON_TUP_RSC = $77,             // 电路复原信号

	SMON_TUP_MGB = $18,             // 面向维护的群闭塞消息
	SMON_TUP_MBA = $28,             // 面向维护的群闭塞证实消息
	SMON_TUP_MGU = $38,             // 面向维护的群解除闭塞消息
	SMON_TUP_MUA = $48,             // 面向维护的群解除闭塞证实消息
	SMON_TUP_HGB = $58,             // 面向硬件故障的群闭塞消息
	SMON_TUP_HBA = $68,             // 面向硬件故障的群闭塞证实消息
	SMON_TUP_HGU = $78,             // 面向硬件故障的群解除闭塞消息
	SMON_TUP_HUA = $88,             // 面向硬件故障的群解除闭塞证实消息
	SMON_TUP_GRS = $98,             // 电路群复原消息
	SMON_TUP_GRA = $A8,             // 群复原证实消息
	SMON_TUP_SGB = $B8,             // 软件产生的群闭塞消息
	SMON_TUP_SBA = $C8,             // 软件产生的群闭塞证实消息
	SMON_TUP_SGU = $D8,             // 软件产生的群解除闭塞消息
	SMON_TUP_SUA = $E8,             // 软件产生的群解除闭塞证实消息
		
	SMON_TUP_ACC = $1A,             // 自动拥塞控制信息消息
		
	SMON_TUP_MPM = $2C,             // 计次脉冲消息
		
	SMON_TUP_OPR = $1D,             // 话务员信号
	
	SMON_TUP_MAL = $1F             // 恶意呼叫追查信号
);


Type ITP_SIGMonitor_ISDN_MsgType =      // 信令监控消息定义
(
	SMON_ISDN_Alerting        = $01,// 提醒
	SMON_ISDN_Call_Proceeding = $02,// 呼叫进程
	SMON_ISDN_Connect         = $07,// 连接
	SMON_ISDN_Connect_Ack     = $0F,// 连接证实
	SMON_ISDN_Progress        = $03,// 进展
	SMON_ISDN_Setup           = $05,// 建立
	SMON_ISDN_Setup_Ack       = $0D,// 建立证实
	
	SMON_ISDN_Resume          = $26,// 恢复
	SMON_ISDN_Resume_Ack      = $2E,// 恢复证实
	SMON_ISDN_Resume_Reject   = $22,// 恢复拒绝
	SMON_ISDN_Suspend         = $25,// 暂停
	SMON_ISDN_Suspend_Ack     = $2D,// 暂停证实
	SMON_ISDN_Suspend_Reject  = $21,// 暂停拒绝
	SMON_ISDN_User_Information= $20,// 用户信息
	
	SMON_ISDN_Disconnect      = $45,// 拆线
	SMON_ISDN_Release         = $4D,// 释放
	SMON_ISDN_Release_Complete= $5A,// 释放完成
	SMON_ISDN_Restart         = $46,// 重新启动
	SMON_ISDN_Restart_Ack     = $4E,// 重启证实
	
	SMON_ISDN_Segment         = $60,// 分段
	SMON_ISDN_Congestion_Ctrl = $79,// 拥塞控制
	SMON_ISDN_Information     = $7B,// 信息
	SMON_ISDN_Notify          = $6E,// 通知
	SMON_ISDN_Status          = $7D,// 状态
	SMON_ISDN_Status_Enquiry  = $75 // 状态询问
);


///////////////////////////////////////////////////////////////////////////////
const SMON_Evt_Len_But_Raw_Data  = 128;// 事件包除原始数据部分的长度

Type                       // 返回的事件数据结构
  SMON_EVENT = record
	EventType : Byte;               // 事件类型
	Protocol  : Byte;               // 协议类型
	SI        : Byte;               // 业务表示
	MsgType   : Byte;               // 信令消息

	Caller_ID : Array[0..31] of ShortInt;           // 主叫号码
	Called_ID : Array[0..31] of ShortInt;           // 被叫号码
	OriCalled : Array[0..31] of ShortInt;           // 原始被叫
	
	DPC : Array[0..2] of Byte;                  // 目的点码
	OPC : Array[0..2] of Byte;                  // 原端点码

	Pcm : Byte;                     // CIC_Hig7
	Chn : Byte;                     // CIC_Low5
	
	ReleaseReason : Byte;           // 拆线原因
	Reserved      : Array[0..13] of Byte;            // 保留备用

	Unit_ID : Byte;                 // 来源单元
	Port_ID : Byte;                 // 来源端口
	TS      : Byte;                      // 来源时隙
	DataLen : Word;                 // 数据长度
	RAWdata : Array[0..2047] of Byte;           // 原始数据
end;

implementation

end.
