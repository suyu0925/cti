unit DJAcsTUPDef;

interface

uses
  SysUtils,Windows;

// TUP信令消息定义(根据需要直接发送部分) //////////////////////////////////////
Type XMS_TUP_Signalling_Message =      // TUP信令消息
(
    TUP_SM_SAM = $31,              // 后续地址信号
    TUP_SM_SAO = $41,              // 带有一个地址的后续地址信号
    
    TUP_SM_GSM = $12,              // 一般前向建立信息信号
    TUP_SM_GRQ = $13,              // 一般请求信号
    
    TUP_SM_BLO = $27,              // 闭塞信号
    TUP_SM_UBL = $47,              // 解除闭塞信号
    TUP_SM_RSC = $77,              // 电路复原信号
    
    TUP_SM_MGB = $18,              // 面向维护的群闭塞信号
    TUP_SM_MGU = $38,              // 面向维护的群解除闭塞信号
    TUP_SM_HGB = $58,              // 面向硬件故障的群闭塞信号
    TUP_SM_HGU = $78,              // 面向硬件故障的群解除闭塞信号
    TUP_SM_GRS = $98,              // 电路群复原信号
    TUP_SM_SGB = $B8,              // 软件产生的群闭塞信号
    TUP_SM_SGU = $D8               // 软件产生的群解除闭塞消信号
);


// TUP信令参数定义 ////////////////////////////////////////////////////////////
Type XMS_TUP_Signalling_Parameter =                   // TUP信令参数
(
	TUP_SP_AccMessageIndicator        = $0C,       // ACC消息指示码
	TUP_SP_AcmMessageIndicator        = $09,       // ACM消息指示码
	TUP_SP_CalledPartAddress          = $0F,       // 被叫用户号码
	TUP_SP_CallingLineAddress         = $02,       // 主叫用户号码
	TUP_SP_CallingPartyCategory       = $01,       // 主叫用户类别
	TUP_SP_ConnectionNatureIndicator  = $0D,       // 接续性质指示码
	TUP_SP_EumOctetIndicator          = $0A,       // EUM消息八位组
	TUP_SP_EumSignallingPointCode     = $0B,       // EUM消息信令点
	TUP_SP_ForwardCallInformation     = $0E,       // 前向呼叫信息
	TUP_SP_GrqRequestTypeIndicator    = $08,       // GRQ请求指示码
	TUP_SP_GsmResponseTypeIndicator   = $06,       // GSM响应指示码
	TUP_SP_IaiFirstIndicator          = $05,       // IAI第一表示语
	TUP_SP_OriginalCalledAddress      = $03,       // 原被叫用户号码
	TUP_SP_RangeStatus                = $04,       // 范围与状态
	TUP_SP_SubsequentAddress          = $10        // 后续地址
);


// TUP信令参数数据结构定义 ////////////////////////////////////////////////////
// ACC消息指示码: TUP_SP_AccMessageIndicator //////////////////////////////////
// 信令: ACC
Type
  TUP_spAccMessageIndicator = record
	m_u8ACCInformation : Byte;                // ACC信息
	m_u8Reserved       : Array[0..2] of Byte; // 备用
end;


// ACM消息指示码: TUP_SP_AcmMessageIndicator //////////////////////////////////
// 信令: ACM
Type
  TUP_spAcmMessageIndicator = record
	m_u8TypeOfACMIndicator      : Byte; // 地址全信号类型表示语
	m_u8SubscriberFreeIndicator : Byte; // 用户闲表示语
	m_u8IncomingEchoSuppressorIndicator : Byte; // 来话回声抑制器表示语
	m_u8CallForwardingIndicator : Byte; // 呼叫转移表示语
	m_u8SignallingPathIndicator : Byte; // 信号通道表示语
	m_u8Reserved                : Array[0..2] of Byte; // 备用
end;


// 被叫用户号码: TUP_SP_CalledPartAddress /////////////////////////////////////
// 信令: IAM/IAI
Type
  TUP_spCalledPartAddress = record
	m_u8NatureOfAddressIndicator : Byte; // 地址性质表示语
	m_u8NumberOfAddressSignal    : Byte; // 地址信号的数量

	m_u8Reserved       : Array[0..1] of Byte; // 备用
	m_s8AddressSignal  : Array[0..39] of ShortInt; // 地址信号
end;


// 主叫用户号码: TUP_SP_CallingLineAddress ////////////////////////////////////
// 信令: IAI/GSM
Type
  TUP_spCallingLineAddress = record
	m_u8NatureOfAddressIndicator : Byte; // 地址性质表示语
	m_u8PresentationIndicator    : Byte; // 提供主叫用户线标识表示语
	m_u8IncompleteIndicator      : Byte; // 主叫用户线标识不全表示语
	m_u8NumberOfAddressSignal    : Byte; // 主叫地址信号的数量
	m_s8AddressSignal            : Array[0..39] of ShortInt; // 地址信号
end;


// 主叫用户类别: TUP_SP_CallingPartyCategory //////////////////////////////////
// 信令: IAM/IAI/GSM
Type
  TUP_spCallingPartyCategory = record
	m_u8CallingPartyCategory : Byte;                // 主叫用户类别
	m_u8Reserved             : Array[0..2] of Byte; // 备用
end;


// 接续性质指示码: TUP_SP_ConnectionNatureIndicator ///////////////////////////
// 信令: IAM/IAI
Type
  TUP_spConnectionNatureIndicator = record
	m_u8NatureOfCircuitIndicator : Byte; // 电路性质表示语
	m_u8ContinuityCheckIndicator : Byte; // 导通检验表示语
	m_u8EchoSuppressorIndicator  : Byte;  // 去话回声抑制器表示语
	m_u8Reserved                 : Byte;
end;


// EUM消息八位组: TUP_SP_EumOctetIndicator ////////////////////////////////////
// 信令: EUM
Type
  TUP_spEumOctetIndicator = record
	m_u8UnsuccessfulIndicator : Byte; // 不成功表示语
	m_u8Reserved              : Array[0..2] of Byte; // 备用
end;


// EUM消息信令点: TUP_SP_EumSignallingPointCode ///////////////////////////////
// 信令: EUM
Type
  TUP_spEumSignallingPointCode = record
	m_u32SPC : DWORD; // 信令点编码
end;


// 前向呼叫信息: TUP_SP_ForwardCallInformation ////////////////////////////////
// 信令: IAM/IAI
Type
  TUP_spForwardCallInformation = record
	m_u8InternationalCallIndicator      : Byte; // 国际来话呼叫表示语
	m_u8RedirectedCallIndicator         : Byte; // 改发呼叫表示语
	m_u8AllDigitalPathRequiredIndicator : Byte; // 需要全部是数字通路表示语
	m_u8SignallingPathIndicator         : Byte; // 信号通道表示语
end;


// GRQ请求指示码: TUP_SP_GrqRequestTypeIndicator //////////////////////////////
// 信令: GRQ
Type
  TUP_spGrqRequestTypeIndicator = record
	m_u8CallingPartyCategoryRequestIndicator  : Byte; // 主叫用户类别请求表示语
	m_u8CallingLineIdentityRequestIndicator   : Byte; // 主叫用户线标识请求表示语
	m_u8OriginalCalledAddressRequestIndicator : Byte; // 原被叫地址请求表示语
	m_u8MaliciousCallIdentificationIndicator  : Byte; // 恶意呼叫识别请求表示语
	m_u8HoldRequestIndicator                  : Byte; // 保持请求表示语
	m_u8EchoSuppressorRequestIndicator        : Byte; // 回声抑制器请求表示语
	m_u8Reserved : Array[0..1] of Byte; // 备用
end;


// GSM响应指示码: TUP_SP_GsmResponseTypeIndicator /////////////////////////////
// 信令: GSM
Type
  TUP_spGsmResponseTypeIndicator = record
	m_u8CallingPartyCategoryIndicator        : Byte; // 主叫用户类别表示语
	m_u8CallingLineIdentityIndicator         : Byte; // 主叫用户线标识表示语
	m_u8IdentityIndicator                    : Byte; // 来话中继和转接交换局标识
	m_u8OriginalCalledAddressIndicator       : Byte; // 原被叫地址表示语
	m_u8OutgoingEchoSuppressorIndicator      : Byte; // 去话回声抑制器表示语
	m_u8MaliciousCallIdentificationIndicator : Byte; // 恶意呼叫识别表示语
	m_u8HoldIndicator : Byte; // 保持表示语
	m_u8Reserved      : Byte; // 备用
end;


// IAI第一表示语: TUP_SP_IaiFirstIndicator ////////////////////////////////////
// 信令: IAI
Type
  TUP_spIaiFirstIndicator = record
	m_u8FacilityInformationIndicator    : Byte; // 网络能力或用户性能信息表示语
	m_u8CUGInformationIndicator         : Byte; // 闭合用户群信息表示语
	m_u8AdditionalCallingPartyIndicator : Byte; // 附加主叫用户信息表示语
	m_u8AdditionalRoutingIndicator      : Byte; // 附加路由信息表示语
	m_u8CallingLineIdentityIndicator    : Byte; // 主叫用户线标识表示语
	m_u8OriginalCalledAddressIndicator  : Byte; // 原被叫地址表示语
	m_u8ChargingInformationIndicator    : Byte; // 计费信息表示语
	m_u8Reserved : Byte; // 备用
end;


// 原被叫用户号码: TUP_SP_OriginalCalledAddress ///////////////////////////////
// 信令: IAI/GSM
Type
  TUP_spOriginalCalledAddress = record
	m_u8NatureOfAddressIndicator : Byte; // 地址性质表示语
	m_u8NumberOfAddressSignal    : Byte; // 地址信号的数量
	m_u8Reserved      : Array[0..1] of Byte;      // 备用
	m_s8AddressSignal : Array[0..39] of ShortInt; // 地址信号
end;


// 范围与状态: TUP_SP_RangeStatus /////////////////////////////////////////////
// 信令: GRM消息组
Type
  TUP_spRangeStatus = record
	m_u8Range : Byte;       // 范围
	m_u8Reserved : Array[0..2] of Byte; // 备用
	m_u32Status : DWORD;    // 状态
end;


// 后续地址: TUP_SP_SubsequentAddress /////////////////////////////////////////
// 信令: SAM/SAO
Type
  TUP_spSubsequentAddress = record
	m_s8AddressSignal : Array[0..39] of ShortInt; // 地址信号
end;

implementation

end.
