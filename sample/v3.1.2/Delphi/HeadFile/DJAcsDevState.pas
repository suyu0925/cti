unit DJAcsDevState;

interface

uses
  DJAcsDataDef;

Type DEVICE_CALL_STATE=
(
  DEVICE_COMMON_STATE_START   = 0,
  DCS_FREE                    = 1,   // 空闲状态(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
  DCS_LOCAL_BLOCK             = 2,   // 本地阻塞(TUP,ISUP)
  DCS_REMOTE_BLOCK            = 3,   // 远端阻塞(TUP,ISUP)
  DCS_BLOCK                   = 4,   // 本地和远端阻塞(ISUP)
  DCS_UNAVAILABLE             = 5,   // 不可用(TUP,ISUP,PRI)

  DCS_CALLOUT                 = 6,   // 开始呼出(TUP,ISUP,PRI,VOIP,ANA_TRK)
  DCS_CALLIN                  = 7,   // 呼叫进入(TUP,ISUP,PRI,VOIP,ANA_TRK)
  DCS_ALERTING                = 8,   // 地址收齐对用户振铃等(TUP,ISUP)

  DCS_CONNECT                 = 9,   // 连通(不分主被叫方式)(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)

  DCS_DISCONNECT              = $A,  // 收到拆线(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
  DCS_WAIT_FREE               = $B,  // 对拆线的响应(TUP,ISUP,PRI,VOIP)

  	/////////////// 模块/接口相关呼叫状态定义 /////////////////////////////////////////////////////////
	DEVICE_ESPECIAL_STATE_START = $0100,
	// ISUP模块/接口
	DES_ISUP_STATE_START        = (Integer(XMS_DEVSUB_E1_SS7_ISUP)  shl  8), // ISUP特有状态 //
	DES_ISUP_LOCAL_SUSPEND      = (DES_ISUP_STATE_START  or  $01), // 本地暂停
	DES_ISUP_REMOTE_SUSPEND     = (DES_ISUP_STATE_START  or  $02), // 远端暂停
	DES_ISUP_LOCAL_RESUME       = (DES_ISUP_STATE_START  or  $03), // 本地继续
	DES_ISUP_REMOTE_RESUME      = (DES_ISUP_STATE_START  or  $04), // 远端继续
	DES_ISUP_RECV_INR           = (DES_ISUP_STATE_START  or  $05), // 收到INR信令消息
	DES_ISUP_RECV_INF           = (DES_ISUP_STATE_START or $06), // 收到INF信令消息
	DES_ISUP_RECV_CQR           = (DES_ISUP_STATE_START or $07), // 收到CQR信令消息
	DES_ISUP_RECV_USR           = (DES_ISUP_STATE_START or $08), // 收到USR信令消息
	DES_ISUP_RECV_CPG           = (DES_ISUP_STATE_START or $09), // 收到CPG信令消息
	
	// TUP模块/接口
	DES_TUP_STATE_START         = (Integer(XMS_DEVSUB_E1_SS7_TUP)  shl  8),  // TUP 特有状态 //
	DES_TUP_RECV_CCL            = (DES_TUP_STATE_START or $01),  // 收到CCL信令消息
	DES_TUP_RECV_RAN            = (DES_TUP_STATE_START or $02),  // 收到RAN信令消息
	DES_TUP_RECV_GSM            = (DES_TUP_STATE_START or $03),  // 收到GSM信令消息

	DES_SS7_LINK_STATE_START    = (Integer(XMS_DEVSUB_SS7_LINK)  shl  8),    //
	DES_SS7_LST_CONNECTING      = (DES_SS7_LINK_STATE_START or $01),
	DES_SS7_LST_ACTIVE          = (DES_SS7_LINK_STATE_START or $02),
	DES_SS7_LST_FAILED          = (DES_SS7_LINK_STATE_START or $03),
	DES_SS7_LST_WAITCON         = (DES_SS7_LINK_STATE_START or $04),
	DES_SS7_LST_SUSPEND         = (DES_SS7_LINK_STATE_START or $05),

	DES_DSS1_STATE_START        = (Integer(XMS_DEVSUB_E1_DSS1)  shl  8),      // DSS1 特有状态 //
	DES_DSS1_RESTRAT            = (DES_DSS1_STATE_START or $01),  // 应用开始的重启动状态
	DES_DSS1_WAIT_CONNECT_ACK   = (DES_DSS1_STATE_START or $02),  // 等待连接证实
	DES_DSS1_CALLER_RECV_ALERT  = (DES_DSS1_STATE_START or $03),  //去话方，已接收到提醒消息
	DES_DSS1_CALLER_RECV_CALLPROCESS = (DES_DSS1_STATE_START or $04),  //去话方，已接收到呼叫进程消息
	DES_DSS1_CALLER_RECV_SETUP_ACK	 = (DES_DSS1_STATE_START or $05),  //去话方，已接收到建立确认消息
	DES_DSS1_CALLER_WAIT_SETUP_ACK	 = (DES_DSS1_STATE_START or $06),  //去话方，等待建立确认
	
	// VoIP H.323协议特有状态
	DES_H323_STATE_START        = $00010100,
	DES_H323_PROCEEDING         = (DES_H323_STATE_START + $01), // proceeding
	DES_H323_TRANSFERING        = (DES_H323_STATE_START + $02), // transfering
	DES_H323_ACF                = (DES_H323_STATE_START + $03), // admission confirm (reserved)
	DES_H323_ARJ                = (DES_H323_STATE_START + $04), // admission reject (reserved)
	DES_H323_INCOMPADDR         = (DES_H323_STATE_START + $05), // incomplete address (reserved)
	DES_H323_WAITACK            = (DES_H323_STATE_START + $06), // wait f or  address ack (reserved)
	
	// VoIP SIP协议特有状态
	DES_SIP_STATE_START         = $00010200,
	DES_SIP_REDIRECTED          = (DES_SIP_STATE_START + $01),  // call redirected
	DES_SIP_UNAUTH              = (DES_SIP_STATE_START + $02),  // unauthenticated
	DES_SIP_ACCEPTED            = (DES_SIP_STATE_START + $03),  // accepted (200 ok sent, waiting ack)
	DES_SIP_REMOTEACCEPT        = (DES_SIP_STATE_START + $04),  // remote party accepted (reserved)
	DES_SIP_DISCONNECTING       = (DES_SIP_STATE_START + $05),  // BYE sent
	DES_SIP_TERMINATED          = (DES_SIP_STATE_START + $06),  // call finished
	DES_SIP_CANCELLED           = (DES_SIP_STATE_START + $07),  // call cancelled
	DES_SIP_CANCELLING          = (DES_SIP_STATE_START + $08),  // CANCEL sent
	DES_SIP_TIMEOUT             = (DES_SIP_STATE_START + $09),  // timeout after 1xx response received (reserved)
	DES_SIP_MSGSENDFAIL         = (DES_SIP_STATE_START + $0A),  // message send failed
	
	// ANALOG_TRUNK模块/接口
	DES_ANALOG_TRUNK_STATE_START     = (Integer(XMS_DEVSUB_ANALOG_TRUNK)  shl  8),         // ANALOG_TRUNK 特有状态
	DES_ANALOG_TRUNK_OFFHOOK         = (DES_ANALOG_TRUNK_STATE_START or $01),  // 呼出时,摘机
	DES_ANALOG_TRUNK_CALLOUT_FAILURE = (DES_ANALOG_TRUNK_STATE_START or $02),  // 呼出失败
	
	// ANALOG_USER模块/接口
	DES_ANALOG_USER_STATE_START      = (Integer(XMS_DEVSUB_ANALOG_USER)  shl  8),         // ANALOG_USER 特有状态
	DES_ANALOG_USER_RING             = (DES_ANALOG_USER_STATE_START or $01),  // 振铃
	DES_ANALOG_USER_OFFHOOK          = (DES_ANALOG_USER_STATE_START or $02),  // 呼出时,摘机
	
	DES_DIGITAL_REC_STATE_START      = (Integer(XMS_DEVSUB_DIGITAL_REC)  shl  8),         //
	DES_DIGITAL_REC_VAD_VOC          = (DES_DIGITAL_REC_STATE_START or $01),  //
	DES_DIGITAL_REC_VAD_NON_VOC      = (DES_DIGITAL_REC_STATE_START or $02),  //
	
	DES_FAX_START                      = (Integer(XMS_DEVMAIN_FAX) shl 16),  // FAX 特有状态 //
	DES_FAX_OPEN                       = (DES_FAX_START ) ,      //0  打开
	DES_FAX_CLOSE                      = (DES_FAX_START or $01), //1  关闭
	DES_FAX_RESET                      = (DES_FAX_START or $02), //2  复位
	DES_FAX_SETPARAM		               = (DES_FAX_START or $03), //3  用户设置传真参数
	
	DES_FAX_SENDFAX_RECVCMD            = (DES_FAX_START or $10), // 发送传真
	DES_FAX_SENDFAX_START              = (DES_FAX_START or $11), // 开始发送传真
	DES_FAX_SENDFAX_REMOTESPEC         = (DES_FAX_START or $12), // 获取远端传真机性能
	DES_FAX_SENDFAX_LOCAL_FINISH       = (DES_FAX_START or $13), // 设置本地传真格式
	DES_FAX_SENDFAX_SHAKEHAND_END      = (DES_FAX_START or $14), // 握手信号结束
	DES_FAX_SENDFAX_RESOLVE_START	     = (DES_FAX_START or $15), // 传真数据分解开始
	DES_FAX_SENDFAX_REQUESTPAGEDATA	   = (DES_FAX_START or $16), // 请求页数据
	DES_FAX_SENDFAX_RESOLVE_RESULT	   = (DES_FAX_START or $17), // 页分解结果
	DES_FAX_SENDFAX_SENDDATA           = (DES_FAX_START or $18), // 设置传真页，发送数据
	DES_FAX_SENDFAX_SENDFINISH         = (DES_FAX_START or $19), // DSP传真过程结束
	DES_FAX_SENDFAX_USERSTOP           = (DES_FAX_START or $1A), // 停止传送传真
	DES_FAX_SENDFAX_SENDEND            = (DES_FAX_START or $1B), // 发送结束
	
	DES_FAX_RECVFAX_RECVCMD            = (DES_FAX_START or $30), // 接收传真
	DES_FAX_RECVFAX_START              = (DES_FAX_START or $31), // 开始接收传真
	DES_FAX_RECVFAX_HANDSHAKE	         = (DES_FAX_START or $32), // 握手结束
	DES_FAX_RECVFAX_RECVDATA_START     = (DES_FAX_START or $33), // 接收传真数据
	DES_FAX_RECVFAX_BACKPAGESTATE	     = (DES_FAX_START or $34), // 页后状态
	DES_FAX_RECVFAX_RECVDATA_END       = (DES_FAX_START or $35), // 传真数据接收结束
	DES_FAX_RECVFAX_RE_HANDSHAKE       = (DES_FAX_START or $36), // 重握手
	DES_FAX_RECVFAX_COMPOSE_START      = (DES_FAX_START or $37), // 合成开始
	DES_FAX_RECVFAX_COMPOSE_END        = (DES_FAX_START or $38), // 合成结束
	DES_FAX_RECVFAX_RECVFINISH         = (DES_FAX_START or $39), // DSP传真过程结束
	DES_FAX_RECVFAX_USERSTOP           = (DES_FAX_START or $3A), // StopFax
	DES_FAX_RECVFAX_RECVEND            = (DES_FAX_START or $3B)  // 接收结束
);

Type XMS_DEVICE_ATRUNK_CALLOUT_REASON =
(
	XMS_ATRUNK_CALLOUT_SUCC                = 1, //
	XMS_ATRUNK_CALLOUT_WAIDAILTONE_TIMEOUT = 2, //
	XMS_ATRUNK_CALLOUT_RING_TIMEOUT        = 3, //
	XMS_ATRUNK_CALLOUT_BUSY                = 4  //
);

Type XMS_DEVICE_CLEAR_CALL_CAUSE =                        //挂机原因定义
(
	XMS_CC_ReasonUnspecified                        = 0,   //原因未指定
	XMS_CC_UnallocatedNumber                        = 1,   //未分配的号码
	XMS_CC_NorouteToSpecifiedTransitNetwork         = 2,   //无路由到指定的转接网
	XMS_CC_NorouteToDestination                     = 3,   //无路由到目的地
	XMS_CC_SendSpecialInformationTone               = 4,   //发送专用信息音
	XMS_CC_MisdialledTrunkPrefix                    = 5,   //误拨长途字管
	XMS_CC_Preemption                               = 8,   //预占
	XMS_CC_PreemptionCircuitReservedForReuse        = 9,   //预占一电路留作再用
	XMS_CC_NormalCallClearing                       = 16,  //正常的呼叫拆线
	XMS_CC_UserBusy                                 = 17,  //用户忙
	XMS_CC_NoUserResponding                         = 18,  //用户未响应
	XMS_CC_UserAlertedNoAnswer                      = 19,  //用户未应答
	XMS_CC_SubscriberAbsent                         = 20,  //用户缺席
	XMS_CC_CallRejected                             = 21,  //呼叫拒收
	XMS_CC_NumberChanged                            = 22,  //号码改变
	XMS_CC_DestinationOutOforder                    = 27,  //目的地不可到达
	XMS_CC_InvalidNumberFormat                      = 28,  //无效的号码格式
	XMS_CC_FacilityRejected                         = 29,  //性能拒绝
	XMS_CC_NormalUnspecified                        = 31,  //正常－未指定
	XMS_CC_NoCircuitChannelAvailable                = 34,  //无电路/通路工作
	XMS_CC_NetworkOutOforder                        = 38,  //网络未正常工作
	XMS_CC_TemporaryFailure                         = 41,  //临时故障
	XMS_CC_SwitchingEquipmentCongestion             = 42,  //交换设备拥塞
	XMS_CC_AccessInformationDiscarded               = 43,  //接入信息舍弃
	XMS_CC_RequestedCircuitChannelNotAvailable      = 44,  //所请求的电路/通路不可用
	XMS_CC_PrecedenceCallBlocked                    = 46,  //优先呼叫闭塞
	XMS_CC_ResourceUnavailableUnspecified           = 47,  //资源不可用－未指定
	XMS_CC_RequestedFacilityNotSubscribed           = 50,  //所请求的性能未预定
	XMS_CC_OutgoingCallsBarredWithinCUG             = 53,  //CUG中限制去呼叫
	XMS_CC_IncomingCallsBarredWithinCUG             = 55,  //CUG中限制来呼叫
	XMS_CC_BearerCapabilityNotAuthorized            = 57,  //承载能力无权
	XMS_CC_BearerCapabilityNotPresentlyAvailable    = 58,  //承载能力目前不可用
	XMS_CC_ServiceorOptionNotAvailableUnspecified   = 63,  //业务/任选不可用－未指定
	XMS_CC_BearerCapabilityNotImplemented           = 65,  //承载能力未实现
	XMS_CC_RequestedFacilityNotImplemented          = 69,  //所请求的性能未实现
	XMS_CC_RestrictedDigitalInfoBearerIsAvailable   = 70,  //只有受限的数字信息承载能力可用
	XMS_CC_ServiceorOptionNotImplementedUnspecified = 79,  //业务或任选未实现－未指定
	XMS_CC_UserNotMemberOfCUG                       = 87,  //被叫用户不是CUG的成员
	XMS_CC_IncompatibleDestination                  = 88,  //不兼容的目的地
	XMS_CC_NonExistentCUG                           = 90,  //不存在的CUG
	XMS_CC_InvalidTransitNetworkSelection           = 91,  //无效的转接网选择
	XMS_CC_InvalidMessageUnspecified                = 95,  //无效的消息，未指定
	XMS_CC_MessageTypeNonExistenorNotImplemented    = 97,  //消息类型不存在或未实现
	XMS_CC_InfElementNonExistentorNotImplemented    = 99,  //参数不存在或未实现
	XMS_CC_RecoveryOnTimerExpiry                    = 102, //定时器终了时恢复
	XMS_CC_ParameterNonExistentorNotImplement       = 103, //参数不存在或未实现－传递
	XMS_CC_MessageWithUnrecognizedParameter         = 110, //消息带有未被识别的参数－舍弃
	XMS_CC_ProtocolErrorUnspecified                 = 111, //协议错误，未指定
	XMS_CC_InterworkingUnspecified                  = 127, //互通，未指定
	
	//
	XMS_CC_DualSeizure                              = 129, // 同抢
	XMS_CC_RemoteBlock                              = 130, // 远端阻断
	XMS_CC_RemoteUnblock                            = 131, // 远端阻断消除
	XMS_CC_ResetCircuit                             = 132, // 电路复原
	XMS_CC_LocalBusy                                = 133  // 用户市忙(TUP)
);

//////////////////////////////////////////////////////////////////////////
Type XMS_VOIP_ERRCODE =
(
	XMS_VOIP_ERR_OK							  = 0,	// command succeed with no err or 
	XMS_VOIP_ERR_INTERNAL					= -1,	// internal err or 
	XMS_VOIP_ERR_SERVICE_DISABLED	= -2,	// service disabled
	XMS_VOIP_ERR_INVALID_CALLID		= -3,	// call id invalid
	XMS_VOIP_ERR_UNKNOWN_PROTOCOL	= -4,	// call protocol unknown
	XMS_VOIP_ERR_CALL_ACTIVE			= -5,	// call is active
	XMS_VOIP_ERR_CALL_FREE				= -6,	// call is free
	XMS_VOIP_ERR_SLOT_NOACCESS		= -7	// call slot no access
);

Type XMS_VOIP_DISCONNECT_REASON =
(
	XMS_VOIP_DISCONNECT_UNKNOWN				= $00,	// unknown reason
	XMS_VOIP_DISCONNECT_LOCAL				  = $01,	// local disconnect
	XMS_VOIP_DISCONNECT_REMOTE				= $02,	// remote disconnect

	// H.323
	XMS_VOIP_DISCONNECT_H323_BUSY			    = $03,	// busy
	XMS_VOIP_DISCONNECT_H323_REJECT			  = $04,	// remote reject
	XMS_VOIP_DISCONNECT_H323_UNREACHABLE	= $05,	// not reachable

	// SIP
	XMS_VOIP_DISCONNECT_SIP_LOCAL_REJECT	  = $06,	// local reject
	XMS_VOIP_DISCONNECT_SIP_REQUEST_FAILURE	= $07,	// 4xx response rcvd (not 401  or  407)
	XMS_VOIP_DISCONNECT_SIP_SERVER_FAILURE	= $08,	// 5xx response rcvd
	XMS_VOIP_DISCONNECT_SIP_GLOBAL_FAILURE	= $09,	// 6xx response rcvd
	XMS_VOIP_DISCONNECT_SIP_LOCAL_FAILURE	  = $0A,	// local netw or k failure
	XMS_VOIP_DISCONNECT_SIP_TIMEOUT			    = $0B	// time out
);

Type XMS_VOC_DEV_STATE = 
(
	XMS_VOC_DEV_STATE_FREE		         = $00,   // device in free state
	XMS_VOC_DEV_STATE_PLAYING	         = $01,   // device in playing state
	XMS_VOC_DEV_STATE_CSPPLAYING	     = $02,   // device in CSPplaying state
	XMS_VOC_DEV_STATE_RECORDING	       = $04,   // device in rec or ding state
	XMS_VOC_DEV_STATE_CSPRECORDING	   = $08,   // device in CSPrec or ding state
	XMS_VOC_DEV_STATE_PLAYSTOPING	     = $10,   // device in playstoping state
	XMS_VOC_DEV_STATE_CSPPLAYSTOPING   = $20,   // device in CSPplaystoping state
	XMS_VOC_DEV_STATE_RECORDSTOPING	   = $40,   // device in rec or dstoping state
	XMS_VOC_DEV_STATE_CSPRECORDSTOPING = $80,   // device in CSPrec or dstoping state
  XMS_VOC_DEV_STATE_SENDINGIODATA    = $100   // device in SENDINGIODATA state
);

implementation

end.
