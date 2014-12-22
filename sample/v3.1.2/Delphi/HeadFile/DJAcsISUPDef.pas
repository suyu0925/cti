unit DJAcsISUPDef;

interface

uses
  Windows;

// ISUP信令消息定义(根据需要直接发送部分) /////////////////////////////////////
Type XMS_ISUP_Signalling_Message =     // ISUP信令消息
(
	ISUP_SM_BLO = $13,              // 阻断
	
	ISUP_SM_CGB = $18,              // 电路群阻断
	ISUP_SM_CGU = $19,              // 电路群阻断消除
	ISUP_SM_CPG = $2C,              // 呼叫进展
	ISUP_SM_CQM = $2A,              // 电路群问讯
	
	ISUP_SM_GRS = $17,              // 电路群复原
	
	ISUP_SM_INF = $04,              // 信息
	ISUP_SM_INR = $03,              // 信息请求
	
	ISUP_SM_RES = $0E,              // 恢复
	ISUP_SM_RSC = $12,              // 电路复原
	
	ISUP_SM_SAM = $02,              // 后续地址
	ISUP_SM_SGM = $38,              // 分段
	ISUP_SM_SUS = $0D,              // 暂停
	
	ISUP_SM_UBL = $14,              // 阻断消除
	ISUP_SM_USR = $2D               // 用户至用户信息
);


// ISUP信令参数定义 ///////////////////////////////////////////////////////////
Type XMS_ISUP_Signalling_Parameter =                      // ISUP信令参数
(
	ISUP_SP_AccessDeliveryInformation          = $2E, // 接入传递信息
	ISUP_SP_AccessTransport                    = $03, // 接入传送
	ISUP_SP_AutomaticCongestionLevel           = $27, // 自动拥塞级
	ISUP_SP_BackwardCallIndicator              = $11, // 后向呼叫指示码
	ISUP_SP_CallDiversionInformation           = $36, // 呼叫转移信息
	ISUP_SP_CallHistoryInformation             = $2D, // 呼叫历史信息
	ISUP_SP_CallReference                      = $01, // 呼叫参考
	ISUP_SP_CalledPartNumber                   = $04, // 被叫用户号码
	ISUP_SP_CallingPartNumber                  = $0A, // 主叫用户号码
	ISUP_SP_CallingPartCategory                = $09, // 主叫用户类别
	ISUP_SP_CauseIndicator                     = $12, // 原因指示码
	ISUP_SP_CircuitGroupSupervisionIndicator   = $15, // 电路群监视消息类型指示码
	ISUP_SP_CircuitStateIndicator              = $26, // 电路状态指示码
	ISUP_SP_CUGInterlockCode                   = $1A, // 闭合用户群相关码
	ISUP_SP_ConnectedNumber                    = $21, // 接续的号码
	ISUP_SP_ConnectionRequest                  = $0D, // 接续请求
	ISUP_SP_ContitnuityIndicator               = $10, // 导通指示码
	ISUP_SP_EchoControlInformation             = $37, // 回声控制信息
	ISUP_SP_EndOptionalParameter               = $00, // 任选参数尾指示码
	ISUP_SP_EventInformation                   = $24, // 事件信息
	ISUP_SP_FacilityIndicator                  = $18, // 功能指示码
	ISUP_SP_ForwardCallIndicator               = $07, // 前向呼叫指示码
	ISUP_SP_GenericDigit                       = $47, // 类属数字
	ISUP_SP_GenericNotifyIndicator             = $2C, // 类属通知指示码
	ISUP_SP_GenericNumber                      = $46, // 类属号码
	ISUP_SP_GenericReference                   = $42, // 类属参考
	ISUP_SP_InformationIndicator               = $0F, // 信息指示码
	ISUP_SP_InformationRequestIndicator        = $0E, // 信息请求指示码
	ISUP_SP_LocationNumber                     = $3F, // 定位号码
	ISUP_SP_MCIDRequestIndicator               = $3B, // MCID请求指示码
	ISUP_SP_MCIDResponseIndicator              = $3C, // MCID响应指示码
	ISUP_SP_MsgCompatibilityInformation        = $38, // 消息兼容性信息
	ISUP_SP_MlppPrecedence                     = $3A, // MLPP优先
	ISUP_SP_NatureOfConnectionIndicator        = $06, // 接续性质指示码
	ISUP_SP_NetworkSpecificFacility            = $2F, // 网络特定功能
	ISUP_SP_OptBackwardCallIndicator           = $29, // 任选后向呼叫指示码
	ISUP_SP_OptForwardCallIndicator            = $08, // 任选前向呼叫指示码
	ISUP_SP_OriginalCalledNumber               = $28, // 原来的被叫号码
	ISUP_SP_OriginationISCPointCode            = $2B, // 始发国际交换中心(ISC)的点码
	ISUP_SP_ParamCompatibilityInformation      = $39, // 参数兼容性信息
	ISUP_SP_PropagationDelayCounter            = $31, // 传播延迟计数器
	ISUP_SP_RangeState                         = $16, // 范围和状态
	ISUP_SP_RedirectingNumber                  = $0B, // 改发号码
	ISUP_SP_RedirectionInformation             = $13, // 改发信息
	ISUP_SP_RedirectionNumber                  = $0C, // 改发号码
	ISUP_SP_RedirectionRestricition            = $40, // 改发号码限制参数
	ISUP_SP_RemoteOperation                    = $32, // 远端操作
	ISUP_SP_ServiceActivation                  = $33, // 业务激活
	ISUP_SP_SignalPointCode                    = $1E, // 信令点编码
	ISUP_SP_SubsequentNumber                   = $05, // 后续号码
	ISUP_SP_SuspendResumeIndicator             = $22, // 暂停/恢复指示码
	ISUP_SP_TransitNetworkSelection            = $23, // 汇接网络选择
	ISUP_SP_TransmissionMediumRequirement      = $02, // 传输媒介要求
	ISUP_SP_TransmissionMediumRequirementPrime = $3E, // 传输媒介要求(基本的)
	ISUP_SP_TransmissionMediumUsed             = $35, // 使用的传输媒介
	ISUP_SP_UserServiceInformation             = $1D, // 用户业务信息
	ISUP_SP_UserServiceInformationPrime        = $30, // 用户业务信息(基本的)
	ISUP_SP_UserTeleserviceInformation         = $34, // 用户终端业务信息
	ISUP_SP_UserToUserIndicator                = $2A, // 用户至用户指示码
	ISUP_SP_UserToUserInformation              = $20, // 用户至用户信息
	ISUP_SP_MessageParameterAllParse           = $FF, // 解析的所有参数(最长255)
	ISUP_SP_MessageParameterAllRaw             = $FE  // 原始的所有参数(最长255)
);


// ISUP信令参数数据结构定义 ///////////////////////////////////////////////////
// 接入传送信息: ISUP_SP_AccessDeliveryInformation ////////////////////////////
Type
  ISUP_spAccessDeliveryInformation = record
	m_u8AccessDeliveryID : Byte;  // 接入传递指示码
	m_u8Reserved         : Array[0..2] of Byte;       // 对齐
end;


// 接入传送: ISUP_SP_AccessTransport //////////////////////////////////////////
Type
  ISUP_spAccessTransport = record
	m_u8AtpInformation : Array[0..239] of Byte;  // 信息单元按4.5/Q.931所述编码
	m_u8AtpLen         : Byte;                   // 参数长度
	m_u8Reserved       : Array[0..2] of Byte;    // 对齐
end;


// 自动拥塞级: ISUP_SP_AutomaticCongestionLevel ///////////////////////////////
Type
  ISUP_spAutomaticCongestionLevel = record
	m_u8CongestionLevelExceeded : Byte;     // 拥塞级超过某个级别
	m_u8Reserved : Array[0..2] of Byte;     // 对齐
end;


// 后向呼叫指示码: ISUP_SP_BackwardCallIndicator //////////////////////////////
Type
  ISUP_spBackwardCallIndicator = record
	m_u8ChargeIndicator         : Byte;       // 计费指示码
	m_u8CalledStatusIndicator   : Byte;       // 被叫用户状态指示码
	m_u8CalledCategoryIndicator : Byte;       // 被叫用户类别指示码
 	m_u8EndToEndMethodIndicator : Byte;       // 端到端方法指示码

	m_u8InterworkingIndicator         : Byte; // 互通指示码
	m_u8EndToEndInformationIndicator  : Byte; // 端到端信息指示码
	m_u8ISDNUserPartIndicator         : Byte; // ISDN用户部分指示码
	m_u8HoldingIndicator              : Byte; // 保持指示码
	m_u8ISDNAccessIndicator           : Byte; // ISDN接入指示码
	m_u8EchoControlDeviceIndicator    : Byte; // 回音控制器件指示码
	m_u8SCCPMethodIndicator           : Byte; // SCCP方法指示码
	m_u8Reserved                      : Byte; // 对齐
end;


// 呼叫转移信息: ISUP_SP_CallDiversionInformation /////////////////////////////
Type
  ISUP_spCallDiversionInformation = record
	m_u8NotificationSubscriptionOptions : Byte; // 通知登记任选
	m_u8RedirectingReason : Byte;               // 改发原因
	m_u8Reserved          : Array[0..1] of Byte;// 对齐
end;


// 呼叫历史信息: ISUP_SP_CallHistoryInformation ///////////////////////////////
Type
  ISUP_spCallHistoryInformation = record
	m_u16PropagationDelayValue : Word;    // 传播时延值
	m_u8Reserved : Array[0..1] of Byte;  // 对齐
end;


// 呼叫参考: ISUP_SP_CallReference ////////////////////////////////////////////
Type
  ISUP_spCallReference = record
	m_u32CallIdentity : DWORD; // 呼叫识别

	m_u32SPcode : DWORD;       // 点码
	m_u8Reserved : Array[0..3] of Byte;   // 备用
end;


// 被叫用户号码: ISUP_SP_CalledPartNumber /////////////////////////////////////
Type
  ISUP_spCalledPartNumber = record
	m_u8NatureOfAddressIndicator : Byte;      // 地址性质指示码
	m_u8OddEvenIndicator         : Byte;      // 奇偶指示码
	m_u8NumberingPlanIndicator   : Byte;      // 号码计划指示
	m_u8InternalNetworkNumberIndicator : Byte;// 内部网络号码指示码

	m_u8Reserved      : Array[0..3] of Byte;          // 备用

 	m_s8AddressSignal : Array[0..39] of Byte;         // 地址信号
end;


// 主叫用户号码: ISUP_SP_CallingPartNumber ////////////////////////////////////
Type
  ISUP_spCallingPartNumber = record
	m_u8NatureOfAddressIndicator : Byte; // 地址性质指示码
	m_u8OddEvenIndicator : Byte;         // 奇偶指示码
	
	m_u8Screening : Byte;                // 屏蔽
	m_u8AddressPresentationRestrictedIndicator : Byte;  // 地址显示指示
	m_u8NumberingPlanIndicator : Byte;   // 号码计划指示
	m_u8NumberIncompleteIndicator : Byte;// 主叫号码不全指示
	
	m_s8AddressSignal : Array[0..39] of ShortInt; // 地址信号
	
  m_u8Reserved : Array[0..1] of ShortInt;       // 对齐
end;


// 主叫用户类别: ISUP_SP_CallingPartCategory //////////////////////////////////
Type
  ISUP_spCallingPartCategory = record
	m_u8CallingPartyCategory : Byte;    // 主叫用户类别
	m_u8Reserved : Array[0..2] of Byte; // 对齐
end;


// 原因指示码: ISUP_SP_CauseIndicator /////////////////////////////////////////
Type
  ISUP_spCauseIndicator = record
	m_u8Location : Byte;             // 定位
	m_u8CodindStandard : Byte;       // 编码标准
	m_u8ExtensionIndicator1 : Byte;  // 扩充
	
	m_u8CauseValue : Byte;           // 原因值
	m_u8ExtensionIndicator2 : Byte;  // 扩充
	
	m_u8Reserved : Array[0..1] of Byte;          // 对齐

	m_u8Diagnose : Array[0..31] of Byte;         // 诊断
	m_u8DiagnoseLen : byte;          // 诊断长度
end;


// 电路群监视消息类型指示码: ISUP_SP_CircuitGroupSupervisionIndicator /////////
Type
  ISUP_spCircuitGroupSupervisionIndicator = record
	m_u8CircuitGroupSupervisionIndicator : byte; // 类型指示码
	m_u8Reserved : Array[0..2] of Byte; // 对齐
end;


// 电路状态指示码: ISUP_SP_CircuitStateIndicator //////////////////////////////
Type
  ISUP_spCircuitStateIndicator = record
	m_u8CircuitStateIndicator : Array[0..31] of Byte;
end;


// 闭合用户群相关码: ISUP_SP_CUGInterlockCode /////////////////////////////////
Type
  ISUP_spCUGInterlockCode  =record
	m_u8NIDigit1 : byte;  // 第1个NI数字
	m_u8NIDigit2 : byte;  // 第2个NI数字
	m_u8NIDigit3 : byte;  // 第3个NI数字
	m_u8NIDigit4 : byte;  // 第4个NI数字
	
	m_u16BinaryCode : Word; // 二进制码
	m_u8Reserved : Array[0..1] of Byte; // 对齐
end;


// 接续的号码: ISUP_SP_ConnectedNumber ////////////////////////////////////////
Type
  ISUP_spConnectedNumber = record
	m_u8NatureOfAddressIndicator : Byte; // 地址性质指示码
	m_u8OddEvenIndicator : Byte;         // 奇偶指示码
    
	m_u8ScreeningIndicator : Byte;       // 屏蔽指示码
	m_u8AddressPresentationRestrictedIndicator : Byte; // 地址显示限制
	m_u8NumberingPlanIndicator : Byte;   // 号码计划指示

	m_u8Reserved : Array[0..2] of Byte;              // 备用
	
	m_s8AddressSignal : Array[0..39] of Byte;        // 地址信号
end;


// 接续请求: ISUP_SP_ConnectionRequest ////////////////////////////////////////
Type
  ISUP_spConnectionRequest = record
	m_u32LocalReference : DWORD; // 呼叫识别
	
	m_u32SPcode : DWORD;         // 点码
	
	m_u8ProtocolClass : Byte;    // 协议类别
	m_u8Credit : Byte;           // 信号量

	m_u8Reserved : Array[0..1] of Byte;     // 对齐
end;


// 导通指示码: ISUP_SP_ContitnuityIndicator ///////////////////////////////////
Type
  ISUP_spContitnuityIndicator = record
	m_u8ContinuityIndicator : Byte; // 导通指示码
	m_u8Reserved : Array[0..2] of Byte; // 对齐
end;


// 回声控制信息: ISUP_SP_EchoControlInformation ///////////////////////////////
Type
  ISUP_spEchoControlInformation = record
	m_u8OutEchoControlInformationIndicator : Byte; // 去话半回声控制响应指示
	m_u8InEchoControlInformationIndicator : Byte;  // 来话半回声控制响应指示
	m_u8OutEchoControlRequestIndicator : Byte;     // 去话半回声控制请求指示
	m_u8InEchoControlRequestIndicator : Byte;      // 来话半回声控制请求指示
end;


// 事件信息: ISUP_SP_EventInformation /////////////////////////////////////////
Type
  ISUP_spEventInformation = record
	m_u8EventIndicator : Byte; // 事件指示码
	m_u8EventPresentationRestrictedIndicator : Byte;// 事件显示限制指示码
	m_u8Reserved : Array[0..1] of Byte; // 对齐
end;


// 功能指示码: ISUP_SP_FacilityIndicator //////////////////////////////////////
Type
  ISUP_spFacilityIndicator = record
	m_u8FacilityIndicator : Byte; // 功能指示码
	m_u8Reserved : Array[0..2] of Byte;
end;


// 前向呼叫指示码: ISUP_SP_ForwardCallIndicator ///////////////////////////////
Type
  ISUP_spForwardCallIndicator = record
	m_u8NationalInternatoinalIndicator : Byte; // 国内/国际呼叫指示码
	m_u8EndToEndMethodIndicator : Byte;        // 端到端方法指示码
	m_u8InterworkingIndicator : Byte;          // 互通指示码
	m_u8EndToEndInformationIndicator : Byte;   // 端到端信息指示码
	m_u8ISDNUserPartIndicator : Byte;          // ISDN用户部分指示码
	m_u8ISDNUserPartPreferenceIndicator : Byte;// ISDN用户部分优先指示码
	
	m_u8ISDNAccessIndicator : Byte; // ISDN接入指示码
	m_u8SCCPMethodIndicator : Byte; // SCCP方法指示码
	
	m_u8Reserved : Array[0..3] of Byte;        // 备用
end;


// 类属数字: ISUP_SP_GenericDigit /////////////////////////////////////////////
Type
  ISUP_spGenericDigit = record
	m_u8TypeOfDigit : Byte;   // 数字类型
	m_u8EncodingScheme : Byte;// 编码计划
	
	m_u8Digit : Array[0..31] of Byte;     // 数字
	m_u8DigitLen : Byte;      // 数字长度
	
	m_u8Reserved : Byte;      // 对齐
end;


// 类属通知指示码: ISUP_SP_GenericNotifyIndicator /////////////////////////////
Type
  ISUP_spGenericNotifyIndicator = record
	m_u8NotificationIndicator : Byte;    // 通知指示码
	m_u8ExtensionIndicator    : Byte;    // 扩充指示码
	m_u8Reserved : Array[0..1] of Byte;  // 对齐
end;


// 类属号码: ISUP_SP_GenericNumber ////////////////////////////////////////////
Type
  ISUP_spGenericNumber = record
	m_u8NumberQualifierIndicator : Byte; // 号码限定指示码

	m_u8NatureOfAddressIndicator : Byte; // 地址性质指示码
	m_u8OddEvenIndicator         : Byte; // 奇偶指示码

	m_u8ScreeningIndicator       : Byte; // 屏蔽
	m_u8AddressPresentationRestrictedIndicator : Byte; // 显示指示
	m_u8NumberingPlanIndicator   : Byte; // 号码计划指示
	m_u8NumberIncompleteIndicator: Byte; //	号码不全指示

	m_s8AddressSignal : Array[0..39] of ShortInt; // 地址信号
	
	m_u8Reserved : Byte;          // 对齐
end;


// 类属参考: ISUP_SP_GenericReference /////////////////////////////////////////
Type
  ISUP_spGenericReference = record
	m_u8ReferenceRestrictedIndicator : Byte; // 参考限定指示码
	m_u8ReferenceLength  : Byte;  // 参考长度
	
	m_u8ReferenceCode : Array[0..3] of Byte; // 参考八位组信息
	m_u8Reserved      : Array[0..1] of Byte; // 对齐
end;


// 信息指示码: ISUP_SP_InformationIndicator ///////////////////////////////////
Type
  ISUP_spInformationIndicator = record
	m_u8CallingPartyAddressResponseIndicator : Byte; // 主叫用户地址响应指示码
	m_u8HoldProvidedIndicator : Byte; // 保持提供指示码
	
	m_u8CallingPartyCategoryResponseIndicator : Byte; // 主叫用户类别响应指示码
	m_u8ChargeInformationResponseIndicator : Byte;  // 计费信息响应指示码
	m_u8SolicitedInformationIndicator : Byte;  // 请求信息指示码
	
	m_u8Reserved : Array[0..2] of Byte; // 对齐
end;


// 信息请示指示码: ISUP_SP_InformationRequestIndicator ////////////////////////
Type
  ISUP_spInformationRequestIndicator = record
	m_u8CallingPartyAddressRequestIndicator : byte; // 主叫用户地址请求指示码
	m_u8HoldingIndicator : byte; // 保持指示码
	m_u8CallingPartyCategoryRequestIndicator : byte;// 主叫用户类别请求指示码
	m_u8ChargeInformationRequestIndicator : byte;   // 计费信息请求指示码
	m_u8MaliciousCallIdentificationRequestIndicator : byte; // 恶意呼叫识别
	m_u8Reserved : Array[0..2] of Byte;  // 对齐
end;


// 定位号码: ISUP_SP_LocationNumber ///////////////////////////////////////////
Type
  ISUP_spLocationNumber = record
	m_u8NatureOfAddressIndicator : Byte; // 地址性质指示码
	m_u8OddEvenIndicator : Byte;         // 奇偶指示码

	m_u8ScreeningIndicator : Byte;       // 屏蔽指示码
	m_u8AddressPresentationRestrictedIndicator : Byte; // 地址显示限制指示码
	m_u8NumberingPlanIndicator : Byte;   // 号码计划指示码
	m_u8InternalNetworkNumberIndicator : Byte; // 内部网络号码指示码
	
	m_s8AddressSignal : Array[0..39] of ShortInt; // 地址信号

	m_u8Reserved : Array[0..1] of Byte;  // 对齐
end;


// MCID请求指示码: ISUP_SP_MCIDRequestIndicator ///////////////////////////////
Type
  ISUP_spMCIDRequestIndicator = record
	m_u8MCIDRequestIndicator : byte;    // MCID请求指示码
	m_u8HoldingIndicator     : byte;    // 保持指示码
	m_u8Reserved : Array[0..1] of Byte; // 备用
end;


// MCID 响应指示码: ISUP_SP_MCIDResponseIndicator /////////////////////////////
Type
  ISUP_spMCIDResponseIndicator = record
	m_u8MCIDResponseIndicator : Byte; // MCID响应指示码
	m_u8HoldProvidedIndicator : Byte; // 保持提供指示码
	m_u8Reserved : Array[0..1] of Byte; // 备用
end;


// 消息兼容性信息: ISUP_SP_MsgCompatibilityInformation ////////////////////////
Type
  ISUP_spMsgCompatibilityInformation = record
	m_u8TransitAtIntermediateExchangeIndicator1 : byte;// 在中间交换局汇接指示码
	m_u8ReleaseCallIndicator1 : byte;      // 释放呼叫指示码
	m_u8SendNotificationIndicator1 : byte; // 发送通知指示码
	m_u8DiscardMessageIndicator1 : byte;   // 舍弃消息指示码
	m_u8PassOnNotPossibleIndicator1 : byte;// 通过不可能指示码
	m_u8ExtensionIndicator1 : byte;        // 扩充指示码
	m_u8Reserved1 : Array[0..1] of Byte;               // 对齐
	
	m_u8TransitAtIntermediateExchangeIndicator2 : byte;// 在中间交换局汇接指示码
	m_u8ReleaseCallIndicator2 : byte;      // 释放呼叫指示码
	m_u8SendNotificationIndicator2 : byte; // 发送通知指示码
	m_u8DiscardMessageIndicator2 : byte;   // 舍弃消息指示码
	m_u8PassOnNotPossibleIndicator2 : byte;// 通过不可能指示码
	m_u8ExtensionIndicator2 : byte;        // 扩充指示码
	m_u8Reserved2 : Array[0..1] of Byte;               // 对齐
end;


// MLPP优先: ISUP_SP_MlppPrecedence ///////////////////////////////////////////
Type
  ISUP_spMlppPrecedence = record
	m_u8PrecedenceLevel : Byte;  // 优先级
	m_u8LFB : Byte;        // LFB
	m_u8Reserved : Array[0..1] of Byte;// 对齐

	m_u8NIDigit1 : Byte;  // 第1个NI数字
	m_u8NIDigit2 : Byte;  // 第2个NI数字
	m_u8NIDigit3 : Byte;  // 第3个NI数字
	m_u8NIDigit4 : Byte;  // 第4个NI数字
	
	m_u32MLPPServiceDomain : DWORD;
end;


// 接续性质指示码: ISUP_SP_NatureOfConnectionIndicator ////////////////////////
Type
  ISUP_spNatureOfConnectionIndicator = record
	m_u8SatelliteIndicator : Byte;        // 卫星指示码
	m_u8ContinuityCheckIndicator : Byte;  // 导通检验指示码
	m_u8EchoControlDeviceIndicator : Byte;// 回声控制器件指示码
	m_u8Reserved : Byte;
end;


// 网络特定功能: ISUP_SP_NetworkSpecificFacility //////////////////////////////
Type
  ISUP_spNetworkSpecificFacility = record
	m_u8NsfInformation : Array[0..31] of Byte;  // 参数信息
	
	m_u8NsfLen         : Byte;                  // 参数长度
	m_u8Reserved       : Array[0..2] of Byte;   // 对齐
end;


// 任选后向呼叫指示码: ISUP_SP_OptBackwardCallIndicator ///////////////////////
Type
  ISUP_spOptBackwardCallIndicator = record
	m_u8InBandInformationIndicator    : Byte; // 带内信息指示码
	m_u8CallTransferPossibleIndicator : Byte; // 呼叫转移可能发送指示码
	m_u8SimpleSegmentationIndicator   : Byte; // 简单分段指示码
	m_u8MLPPUserIndicator : Byte;             // MLPP用户指示码

	m_u8Reserved : Array[0..3] of Byte;
end;


// 任选前向呼叫指示码: ISUP_SP_OptForwardCallIndicator ////////////////////////
Type
  ISUP_spOptForwardCallIndicator = record
	m_u8ClosedUserGroupCallIndicator : byte; // CUG呼叫指示码
	m_u8SimpleSegmentationIndicator  : byte; // 简单分段指示码
	m_u8UserIdentityRequestIndicator : byte; // 接续的用户识别请求指示码
	m_u8Reserved : byte;                     // 对齐
end;


// 原被叫号码: ISUP_SP_OriginalCalledNumber ///////////////////////////////////
Type
  ISUP_spOriginalCalledNumber = record
	m_u8NatureOfAddressIndicator : byte; // 地址性质指示码
	m_u8OddEvenIndicator         : byte; // 奇偶指示码

	m_u8AddressPresentationRestrictedIndicator : byte; // 显示指示
	m_u8NumberingPlanIndicator   : byte; // 号码计划指示

	m_s8AddressSignal : Array[0..39] of ShortInt; // 地址信号
	
	m_u8Reserved      : Array[0..3] of Byte;      // 备用
end;


// 始发国际交换中心(ISC)的点码: ISUP_SP_OriginationISCPointCode ///////////////
Type
  ISUP_spOriginationISCPointCode = record
	m_u32SPcode  : DWORD;     // 点码
	m_u8Reserved : Array[0..3] of Byte; // 备用
end;


// 参数兼容性信息: ISUP_SP_ParamCompatibilityInformation //////////////////////
Type
  ISUP_spParamCompatibilityInformation = record
	m_u8UpgradedParameter1 : Byte;         // 第一个升格参数
	m_u8TransitAtIntermediateExchangeIndicator1 : Byte;// 在中间交换局汇接指示码
	m_u8ReleaseCallIndicator1 : Byte;      // 释放呼叫指示码
	m_u8SendNotificationIndicator1 : Byte; // 发送通知指示码
	m_u8DiscardMessageIndicator1 : Byte;   // 舍弃消息指示码
	m_u8DiscardParameterIndicator1 : Byte; // 舍弃参数指示码
	m_u8ExtensionIndicator1 : Byte;        // 扩充指示码
	m_u8Reserved1 : Byte;                  // 备用
	
	m_u8UpgradedParameter2 : Byte;         // 第二个升格参数
	m_u8TransitAtIntermediateExchangeIndicator2 : Byte;// 在中间交换局汇接指示码
	m_u8ReleaseCallIndicator2 : Byte;      // 释放呼叫指示码
	m_u8SendNotificationIndicator2 : Byte; // 发送通知指示码
	m_u8DiscardMessageIndicator2 : Byte;   // 舍弃消息指示码
	m_u8DiscardParameterIndicator2 : Byte; // 舍弃参数指示码
	m_u8ExtensionIndicator2 : Byte;        // 扩充指示码
	m_u8Reserved2 : Byte;                  // 备用

	m_u8UpgradedParameter3 : Byte;         // 第三个升格参数
	m_u8TransitAtIntermediateExchangeIndicator3 : Byte;// 在中间交换局汇接指示码
	m_u8ReleaseCallIndicator3 : Byte;      // 释放呼叫指示码
	m_u8SendNotificationIndicator3 : Byte; // 发送通知指示码
	m_u8DiscardMessageIndicator3 : Byte;   // 舍弃消息指示码
	m_u8DiscardParameterIndicator3 : Byte; // 舍弃参数指示码
	m_u8ExtensionIndicator3 : Byte;        // 扩充指示码
	m_u8Reserved3 : Byte;                  // 备用
end;


// 传播延时计数器: ISUP_SP_PropagationDelayCounter ////////////////////////////
Type
  ISUP_spPropagationDelayCounter = record
	m_u16PropagationDelayValue : Word;     // 传播时延值
	m_u8Reserved : Array[0..1] of Byte; // 对齐
end;


// 范围和状态: ISUP_SP_RangeState /////////////////////////////////////////////
Type
  ISUP_spRangeState = record
	m_u8Range : Byte;      // 范围
	m_u8Reserved : Array[0..2] of Byte;// 对齐
	
	m_u32Status : DWORD;    // 状态
end;


// 改发号码: ISUP_SP_RedirectingNumber ////////////////////////////////////////
Type
  ISUP_spRedirectingNumber = record
	m_u8NatureOfAddressIndicator : Byte; // 地址性质指示码
	m_u8OddEvenIndicator         : Byte; // 奇偶指示码
    
	m_u8AddressPresentationRestrictedIndicator : Byte; // 显示限制指示码
	m_u8NumberingPlanIndicator : Byte; // 号码计划指示码
	
	m_s8AddressSignal      : Array[0..39] of ShortInt; // 地址信号

	m_u8Reserved           : Array[0..3] of Byte;      // 备用
end;


// 改发信息: ISUP_SP_RedirectionInformation ///////////////////////////////////
Type
  ISUP_spRedirectionInformation = record
	m_u8RedirectingIndicator : Byte;      // 改发指示码
	m_u8OriginalRedirectionReason : Byte; // 原理的改发原因
	m_u8RedirectionCounter   : Byte;      // 改发计数器
	m_u8RedirectingReason    : Byte;      // 改发原因
	m_u8Reserved : Array[0..3] of Byte;   // 备用
end;


// 改发号码: ISUP_SP_RedirectionNumber ////////////////////////////////////////
Type
  ISUP_spRedirectionNumber = record
	m_u8NatureOfAddressIndicator : Byte;    // 地址性质指示码
	m_u8OddEvenIndicator         : Byte;    // 奇偶指示码
	m_u8NumberingPlanIndicator   : Byte;    // 号码计划指示码
	m_u8InternalNetworkNumberIndicator : Byte; // 内部网络号码指示码

	m_s8AddressSignal : Array[0..39] of Byte;  // 地址信号

	m_u8Reserved      : Array[0..3] of Byte;   // 备用
end;


// 改发号码限制参数: ISUP_SP_RedirectionRestricition //////////////////////////
Type
  ISUP_spRedirectionRestricition = record
	m_u8PresentationRestrictedIndicator : Byte; // 显示限制指示码
	m_u8Reserved : Array[0..2] of Byte;
end;


// 远端操作: ISUP_SP_RemoteOperation //////////////////////////////////////////
Type
  ISUP_spRemoteOperation  =record
	m_u8ProtocolProfile    : Byte; // 协议剖析
	m_u8ExtensionIndicator : Byte; // 扩充
	m_u8Component : Array[0..239] of Byte;
	m_u8ComponentLen : Byte;
	m_u8Reserved     : Byte;       // 对齐
end;


// 业务激活: ISUP_SP_ServiceActivation ////////////////////////////////////////
Type
  ISUP_spServiceActivation = record
	m_u32FeatureCode : Array[0..31] of Byte;  // 特征码
	m_u8FCLen        : Byte;                  // 特征码长度
	m_u8Reserved     : Array[0..2] of Byte;   // 对齐
end;


// 信令点编码: ISUP_SP_SignalPointCode ////////////////////////////////////////
Type
  ISUP_spSignalPointCode = record
	m_u32SPcode  : DWORD;     // 点码
	m_u8Reserved : Array[0..3] of Byte; // 备用
end;


// 后续号码: ISUP_SP_SubsequentNumber /////////////////////////////////////////
Type
  ISUP_spSubsequentNumber = record
	m_u8OddEvenIndicator : byte; // 奇偶指示码
	m_u8Reserved      : Array[0..2] of Byte;     // 对齐
	m_s8AddressSignal : Array[0..39] of Byte;    // 地址信号
end;


// 暂停恢复指示: ISUP_SP_SuspendResumeIndicator ///////////////////////////////
Type
  ISUP_spSuspendResumeIndicator = record
	m_u8SuspendResumeIndicator : Byte;     // 暂停/恢复指示码
	m_u8Reserved : Array[0..2] of Byte; // 对齐
end;


// 汇接网络选择: ISUP_SP_TransitNetworkSelection //////////////////////////////
Type
  ISUP_spTransitNetworkSelection = record
	m_u8NetworkIdentificationPlan   : Byte;   // 网络识别计划
	m_u8TypeOfNetworkIdentification : Byte;   // 网络识别类型
	m_u8OddEvenIndicator            : Byte;   // 奇偶指示码
	m_u8Reserved                    : Byte;                    // 对齐

	m_u8NetworkIdentification       : Array[0..31] of Byte;    // 网络识别

	m_u8NetIdLen                    : Byte;                    // 网络识别长度
  m_u8Rev                         : Array[0..2] of Byte;     // 对齐
end;


// 传输媒价要求: ISUP_SP_TransmissionMediumRequirement ////////////////////////
Type
  ISUP_spTransmissionMediumRequirement = record
	m_u8TransmissionMediumRequirement : Byte; // 传送媒介要求
	m_u8Reserved : Array[0..2] of Byte;       // 对齐
end;


// 传输媒介要求(基本): ISUP_SP_TransmissionMediumRequirementPrime /////////////
Type
  ISUP_spTransmissionMediumRequirementPrime = record
	m_u8TransmissionMediumRequirement : Byte; // 传送媒介要求
	m_u8Reserved : Array[0..2] of Byte;       // 对齐
end;


// 使用中的传输媒介: ISUP_SP_TransmissionMediumUsed ///////////////////////////
Type
  ISUP_spTransmissionMediumUsed = record

	m_u8TransmissionMediumRequirement : Byte; // 传送媒介要求
	m_u8Reserved : Array[0..2] of Byte;       // 对齐
end;


// 用户业务信息: ISUP_SP_UserServiceInformation ///////////////////////////////
Type
  ISUP_spUserServiceInformation = record
	m_u8USInformation : Array[0..31] of Byte; // 用户业务信息
	m_u8USILen        : Byte;                 // 信息长度
	m_u8Reserved      : Array[0..2] of Byte;  // 对齐
end;


// 基本用户业务信息: ISUP_SP_UserServiceInformationPrime //////////////////////
Type
  ISUP_spUserServiceInformationPrime = record
	m_u8USInformation : Array[0..31] of Byte; // 用户业务信息
	m_u8USILen        : Byte;                 // 信息长度
	m_u8Reserved      : Array[0..2] of Byte;  // 对齐
end;


// 用户电信业务信息: ISUP_SP_UserTeleserviceInformation ///////////////////////
Type
  ISUP_spUserTeleserviceInformation = record
	m_u8Presentation : Byte;   // 显示
	m_u8Interpretation : Byte; // 解释
	m_u8CodingStandard : Byte; // 编码标准
	m_u8ExtensionIndicator1 : Byte; // 扩充
	
	m_u8HighLayerCharacteristicsIdentification : Byte; // 高层特性识别
	m_u8ExtensionIndicator2 : Byte; // 扩充

	m_u8ExtendedHighLayerCharacteristicsIdentification : Byte; // 扩充的高层特性识别
	m_u8ExtensionIndicator3 : Byte;	// 扩充
end;


// 用户至用户指示码: ISUP_SP_UserToUserIndicator //////////////////////////////
Type
  ISUP_spUserToUserIndicator = record
	m_u8Type : Byte;     // 类型
	m_u8Service1 : Byte; // 业务
	m_u8Service2 : Byte; // 业务
	m_u8Service3 : Byte; // 业务
	m_u8NetworkDiscardIndicator : Byte; // 网络舍弃指示码

	m_u8Reserved : Array[0..2] of Byte; // 对齐
end;


// 用户至用户信息: ISUP_SP_UserToUserInformation //////////////////////////////
Type
  ISUP_spUserToUserInformation = record
	m_u8UserToUserInformation : Array[0..239] of Byte;
	
	m_u8UifLen   : Byte;                // 信息长度
	m_u8Reserved : Array[0..2] of Byte; // 对齐
end;


implementation

end.
