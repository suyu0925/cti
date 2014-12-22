using System;
using System.Collections.Generic;
using System.Text;

namespace DJKeygoe
{
    using DJ_U8 = Byte;
    using DJ_S8 = SByte;
    using DJ_U16 = UInt16;
    using DJ_S16 = Int16;
    using DJ_U32 = UInt32;
    using DJ_S32 = Int32;
    using DJ_U64 = UInt64;
    using DJ_S64 = Int64;
    using DJ_UI32 = UInt32;
    using DJ_SI32 = Int32;
    using DJ_F64 = Double;
    using RetCode_t = Int32;
    using ACSHandle_t = UInt32;
    using InvokeID_t = Int32;
    using LoginID_t = SByte;
    using EventClass_t = Int32;
    using EventType_t = Int32;
    using ACSConfirmation_t = Int32;
    using CallNum_t = SByte;
    using AcsCmdTye_t = Int32;

    using FlowType_t = Int32;
    using FlowChannel_t = Int32;
    using DeviceMain_t = Int16;
    using DeviceSub_t = Int16;
    using DeviceGroup_t = Int16;
    using ModuleID_t = SByte;
    using ChannelID_t = Int16;
    using ParmName_t = SByte;
    using ParmSize_t = Int32;
    using Version_t = Int32;
    using ACSUniversalFailure_t = Int32;
    using PlayCont_t = SByte;
    using FilePath_t = SByte;

    using Acs_Evt_State_t = Int32;
    using Acs_Evt_ErrCode_t = Int32;
    using Acs_MediaProc_Dtmf_t = SByte;
    using DJ_SOCKET = UInt32;

        // ISUP信令消息定义(根据需要直接发送部分) /////////////////////////////////////
        public enum XMS_ISUP_Signalling_Message     // ISUP信令消息
        {	
	        ISUP_SM_BLO = 0x13,              // 阻断
        	
	        ISUP_SM_CGB = 0x18,              // 电路群阻断
	        ISUP_SM_CGU = 0x19,              // 电路群阻断消除	
	        ISUP_SM_CPG = 0x2C,              // 呼叫进展
	        ISUP_SM_CQM = 0x2A,              // 电路群问讯
        	
	        ISUP_SM_GRS = 0x17,              // 电路群复原
        	
	        ISUP_SM_INF = 0x04,              // 信息
	        ISUP_SM_INR = 0x03,              // 信息请求
        	
	        ISUP_SM_RES = 0x0E,              // 恢复	
	        ISUP_SM_RSC = 0x12,              // 电路复原
        	
	        ISUP_SM_SAM = 0x02,              // 后续地址
	        ISUP_SM_SGM = 0x38,              // 分段
	        ISUP_SM_SUS = 0x0D,              // 暂停
        	
	        ISUP_SM_UBL = 0x14,              // 阻断消除	
	        ISUP_SM_USR = 0x2D               // 用户至用户信息
        };

        // ISUP信令参数定义 ///////////////////////////////////////////////////////////
         public enum XMS_ISUP_Signalling_Parameter                     // ISUP信令参数
        {
	        ISUP_SP_AccessDeliveryInformation            = 0x2E, // 接入传递信息
	        ISUP_SP_AccessTransport                           = 0x03, // 接入传送
	        ISUP_SP_AutomaticCongestionLevel           = 0x27, // 自动拥塞级
	        ISUP_SP_BackwardCallIndicator                  = 0x11, // 后向呼叫指示码
	        ISUP_SP_CallDiversionInformation              = 0x36, // 呼叫转移信息
	        ISUP_SP_CallHistoryInformation                  = 0x2D, // 呼叫历史信息
	        ISUP_SP_CallReference                               = 0x01, // 呼叫参考
	        ISUP_SP_CalledPartNumber                        = 0x04, // 被叫用户号码
	        ISUP_SP_CallingPartNumber                       = 0x0A, // 主叫用户号码
	        ISUP_SP_CallingPartCategory                     = 0x09, // 主叫用户类别
	        ISUP_SP_CauseIndicator                             = 0x12, // 原因指示码
	        ISUP_SP_CircuitGroupSupervisionIndicator = 0x15, // 电路群监视消息类型指示码
	        ISUP_SP_CircuitStateIndicator                    = 0x26, // 电路状态指示码
	        ISUP_SP_CUGInterlockCode                        = 0x1A, // 闭合用户群相关码
	        ISUP_SP_ConnectedNumber                        = 0x21, // 接续的号码
	        ISUP_SP_ConnectionRequest                      = 0x0D, // 接续请求
	        ISUP_SP_ContitnuityIndicator                     = 0x10, // 导通指示码
	        ISUP_SP_EchoControlInformation               = 0x37, // 回声控制信息
	        ISUP_SP_EndOptionalParameter                 = 0x00, // 任选参数尾指示码
	        ISUP_SP_EventInformation                         = 0x24, // 事件信息
	        ISUP_SP_FacilityIndicator                            = 0x18, // 功能指示码
	        ISUP_SP_ForwardCallIndicator                    = 0x07, // 前向呼叫指示码
	        ISUP_SP_GenericDigit                                  = 0x47, // 类属数字
	        ISUP_SP_GenericNotifyIndicator                  = 0x2C, // 类属通知指示码
	        ISUP_SP_GenericNumber                             = 0x46, // 类属号码
	        ISUP_SP_GenericReference                         = 0x42, // 类属参考
	        ISUP_SP_InformationIndicator                    = 0x0F, // 信息指示码
	        ISUP_SP_InformationRequestIndicator       = 0x0E, // 信息请求指示码
	        ISUP_SP_LocationNumber                           = 0x3F, // 定位号码
	        ISUP_SP_MCIDRequestIndicator                 = 0x3B, // MCID请求指示码
	        ISUP_SP_MCIDResponseIndicator               = 0x3C, // MCID响应指示码
	        ISUP_SP_MsgCompatibilityInformation        = 0x38, // 消息兼容性信息
	        ISUP_SP_MlppPrecedence                           = 0x3A, // MLPP优先
	        ISUP_SP_NatureOfConnectionIndicator      = 0x06, // 接续性质指示码
	        ISUP_SP_NetworkSpecificFacility                 = 0x2F, // 网络特定功能
	        ISUP_SP_OptBackwardCallIndicator            = 0x29, // 任选后向呼叫指示码
	        ISUP_SP_OptForwardCallIndicator              = 0x08, // 任选前向呼叫指示码
	        ISUP_SP_OriginalCalledNumber                  = 0x28, // 原来的被叫号码
	        ISUP_SP_OriginationISCPointCode             = 0x2B, // 始发国际交换中心(ISC)的点码
	        ISUP_SP_ParamCompatibilityInformation    = 0x39, // 参数兼容性信息
	        ISUP_SP_PropagationDelayCounter            = 0x31, // 传播延迟计数器
	        ISUP_SP_RangeState                                  = 0x16, // 范围和状态
	        ISUP_SP_RedirectingNumber                       = 0x0B, // 改发号码
	        ISUP_SP_RedirectionInformation                 = 0x13, // 改发信息
	        ISUP_SP_RedirectionNumber                       = 0x0C, // 改发号码
	        ISUP_SP_RedirectionRestricition                  = 0x40, // 改发号码限制参数
	        ISUP_SP_RemoteOperation                         = 0x32, // 远端操作
	        ISUP_SP_ServiceActivation                          = 0x33, // 业务激活
	        ISUP_SP_SignalPointCode                           = 0x1E, // 信令点编码
	        ISUP_SP_SubsequentNumber                     = 0x05, // 后续号码
	        ISUP_SP_SuspendResumeIndicator            = 0x22, // 暂停/恢复指示码
	        ISUP_SP_TransitNetworkSelection              = 0x23, // 汇接网络选择
	        ISUP_SP_TransmissionMediumRequirement          = 0x02, // 传输媒介要求
	        ISUP_SP_TransmissionMediumRequirementPrime = 0x3E, // 传输媒介要求(基本的)
	        ISUP_SP_TransmissionMediumUsed                      = 0x35, // 使用的传输媒介
	        ISUP_SP_UserServiceInformation                         = 0x1D, // 用户业务信息
	        ISUP_SP_UserServiceInformationPrime                = 0x30, // 用户业务信息(基本的)
	        ISUP_SP_UserTeleserviceInformation                   = 0x34, // 用户终端业务信息
	        ISUP_SP_UserToUserIndicator                              = 0x2A, // 用户至用户指示码
	        ISUP_SP_UserToUserInformation                         = 0x20, // 用户至用户信息
	        ISUP_SP_MessageParameterAllParse                  = 0xFF, // 解析的所有参数(最长255)
	        ISUP_SP_MessageParameterAllRaw                    = 0xFE  // 原始的所有参数(最长255)
        };


        // ISUP信令参数数据结构定义 ///////////////////////////////////////////////////
        // 接入传送信息: ISUP_SP_AccessDeliveryInformation ////////////////////////////
        public unsafe struct ISUP_spAccessDeliveryInformation
        {
	        public DJ_U8          m_u8AccessDeliveryID;  // 接入传递指示码	
	        public fixed DJ_U8 m_u8Reserved[3];       // 对齐
        }


        // 接入传送: ISUP_SP_AccessTransport //////////////////////////////////////////
        public unsafe struct ISUP_spAccessTransport
        {
	        public fixed DJ_U8    m_u8AtpInformation[240];  // 信息单元按4.5/Q.931所述编码

	        public DJ_U8            m_u8AtpLen;               // 参数长度
	        public fixed DJ_U8   m_u8Reserved[3];          // 对齐
        }


        // 自动拥塞级: ISUP_SP_AutomaticCongestionLevel ///////////////////////////////
        public unsafe struct ISUP_spAutomaticCongestionLevel
        {	
	        public DJ_U8          m_u8CongestionLevelExceeded;     // 拥塞级超过某个级别
	        public fixed DJ_U8 m_u8Reserved[3];                 // 对齐
        };


        // 后向呼叫指示码: ISUP_SP_BackwardCallIndicator //////////////////////////////
        public struct ISUP_spBackwardCallIndicator
        {	
	        public DJ_U8 m_u8ChargeIndicator;             // 计费指示码
	        public DJ_U8 m_u8CalledStatusIndicator;       // 被叫用户状态指示码
	        public DJ_U8 m_u8CalledCategoryIndicator;     // 被叫用户类别指示码
 	        public DJ_U8 m_u8EndToEndMethodIndicator;     // 端到端方法指示码
        	
	        public DJ_U8 m_u8InterworkingIndicator;       // 互通指示码
	        public DJ_U8 m_u8EndToEndInformationIndicator;// 端到端信息指示码
	        public DJ_U8 m_u8ISDNUserPartIndicator;       // ISDN用户部分指示码
	        public DJ_U8 m_u8HoldingIndicator;            // 保持指示码
	        public DJ_U8 m_u8ISDNAccessIndicator;         // ISDN接入指示码
	        public DJ_U8 m_u8EchoControlDeviceIndicator;  // 回音控制器件指示码
	        public DJ_U8 m_u8SCCPMethodIndicator;         // SCCP方法指示码
	        public DJ_U8 m_u8Reserved;                    // 对齐
        }

        // 呼叫转移信息: ISUP_SP_CallDiversionInformation /////////////////////////////
        public unsafe struct ISUP_spCallDiversionInformation
        {	
	        public DJ_U8          m_u8NotificationSubscriptionOptions; // 通知登记任选
	        public DJ_U8          m_u8RedirectingReason;                    // 改发原因
	        public fixed DJ_U8 m_u8Reserved[2];                              // 对齐
        } 

        // 呼叫历史信息: ISUP_SP_CallHistoryInformation ///////////////////////////////
        public unsafe struct ISUP_spCallHistoryInformation
        {	
	        public DJ_U16         m_u16PropagationDelayValue; // 传播时延值
	        public fixed DJ_U8  m_u8Reserved[2];            // 对齐
        };


        // 呼叫参考: ISUP_SP_CallReference ////////////////////////////////////////////
        public unsafe struct ISUP_spCallReference
        {	
	        public DJ_U32          m_u32CallIdentity; // 呼叫识别

	        public DJ_U32          m_u32SPcode;       // 点码
	        public fixed DJ_U8    m_u8Reserved[4];   // 备用
        };


        // 被叫用户号码: ISUP_SP_CalledPartNumber /////////////////////////////////////
        public unsafe struct ISUP_spCalledPartNumber
        {
	        public DJ_U8 m_u8NatureOfAddressIndicator;  // 地址性质指示码
	        public DJ_U8 m_u8OddEvenIndicator;          // 奇偶指示码
	        public DJ_U8 m_u8NumberingPlanIndicator;    // 号码计划指示
	        public DJ_U8 m_u8InternalNetworkNumberIndicator;// 内部网络号码指示码
	        public fixed DJ_U8 m_u8Reserved[4];               // 备用
 	        public fixed DJ_S8 m_s8AddressSignal[40];         // 地址信号	
        };


        // 主叫用户号码: ISUP_SP_CallingPartNumber ////////////////////////////////////
        public unsafe struct ISUP_spCallingPartNumber
        {	
	        public DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	        public DJ_U8 m_u8OddEvenIndicator;         // 奇偶指示码
        	
	        public DJ_U8 m_u8Screening;                // 屏蔽
	        public DJ_U8 m_u8AddressPresentationRestrictedIndicator;  // 地址显示指示
	        public DJ_U8 m_u8NumberingPlanIndicator;   // 号码计划指示
	        public DJ_U8 m_u8NumberIncompleteIndicator;// 主叫号码不全指示	
        	
	        public fixed DJ_S8 m_s8AddressSignal[40]; // 地址信号
        	
	        public fixed DJ_U8 m_u8Reserved[2];       // 对齐
        };


        // 主叫用户类别: ISUP_SP_CallingPartCategory //////////////////////////////////
        public unsafe struct ISUP_spCallingPartCategory
        {	
	        public DJ_U8 m_u8CallingPartyCategory; // 主叫用户类别
	        public fixed DJ_U8 m_u8Reserved[3];          // 对齐
        };


        // 原因指示码: ISUP_SP_CauseIndicator /////////////////////////////////////////
        public unsafe struct ISUP_spCauseIndicator
        {	
	        public DJ_U8 m_u8Location;             // 定位
	        public DJ_U8 m_u8CodindStandard;       // 编码标准
	        public DJ_U8 m_u8ExtensionIndicator1;  // 扩充
        	
	        public DJ_U8 m_u8CauseValue;           // 原因值
	        public DJ_U8 m_u8ExtensionIndicator2;  // 扩充
        	
	        public fixed DJ_U8 m_u8Reserved[2];          // 对齐
        	
	        public fixed DJ_U8 m_u8Diagnose[32];         // 诊断	
	        public DJ_U8 m_u8DiagnoseLen;          // 诊断长度
        };


        // 电路群监视消息类型指示码: ISUP_SP_CircuitGroupSupervisionIndicator /////////
        public unsafe struct ISUP_spCircuitGroupSupervisionIndicator
        {
	        public DJ_U8 m_u8CircuitGroupSupervisionIndicator; // 类型指示码
	        public fixed DJ_U8 m_u8Reserved[3]; // 对齐
        };


        // 电路状态指示码: ISUP_SP_CircuitStateIndicator //////////////////////////////
        public unsafe struct ISUP_spCircuitStateIndicator
        {	
	        public fixed DJ_U8 m_u8CircuitStateIndicator[32];
        };


        // 闭合用户群相关码: ISUP_SP_CUGInterlockCode /////////////////////////////////
        public unsafe struct ISUP_spCUGInterlockCode
        {	
	        public DJ_U8  m_u8NIDigit1;  // 第1个NI数字
	        public DJ_U8  m_u8NIDigit2;  // 第2个NI数字
	        public DJ_U8  m_u8NIDigit3;  // 第3个NI数字
	        public DJ_U8  m_u8NIDigit4;  // 第4个NI数字	
        	
	        public DJ_U16 m_u16BinaryCode; // 二进制码
	        public fixed DJ_U8  m_u8Reserved[2]; // 对齐
        };


        // 接续的号码: ISUP_SP_ConnectedNumber ////////////////////////////////////////
        public unsafe struct ISUP_spConnectedNumber
        {	
	        public DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	        public DJ_U8 m_u8OddEvenIndicator;         // 奇偶指示码
            
	        public DJ_U8 m_u8ScreeningIndicator;       // 屏蔽指示码
	        public DJ_U8 m_u8AddressPresentationRestrictedIndicator; // 地址显示限制
	        public DJ_U8 m_u8NumberingPlanIndicator;   // 号码计划指示	

	        public fixed DJ_U8 m_u8Reserved[3];              // 备用
        	
	        public fixed DJ_S8 m_s8AddressSignal[40];        // 地址信号	
        };


        // 接续请求: ISUP_SP_ConnectionRequest ////////////////////////////////////////
        public unsafe struct ISUP_spConnectionRequest
        {	
	        public DJ_U32 m_u32LocalReference; // 呼叫识别
        	
	        public DJ_U32 m_u32SPcode;         // 点码
        	
	        public DJ_U8  m_u8ProtocolClass;   // 协议类别
	        public DJ_U8  m_u8Credit;          // 信号量

	        public fixed DJ_U8  m_u8Reserved[2];     // 对齐
        };


        // 导通指示码: ISUP_SP_ContitnuityIndicator ///////////////////////////////////
        public unsafe struct ISUP_spContitnuityIndicator
        {	
	        public DJ_U8 m_u8ContinuityIndicator; // 导通指示码
	        public fixed DJ_U8 m_u8Reserved[3]; // 对齐
        };


        // 回声控制信息: ISUP_SP_EchoControlInformation ///////////////////////////////
        public struct ISUP_spEchoControlInformation
        {	
	        public DJ_U8 m_u8OutEchoControlInformationIndicator; // 去话半回声控制响应指示
	        public DJ_U8 m_u8InEchoControlInformationIndicator;  // 来话半回声控制响应指示
	        public DJ_U8 m_u8OutEchoControlRequestIndicator;     // 去话半回声控制请求指示
	        public DJ_U8 m_u8InEchoControlRequestIndicator;      // 来话半回声控制请求指示
        };


        // 事件信息: ISUP_SP_EventInformation /////////////////////////////////////////
        public unsafe struct ISUP_spEventInformation
        {
	        public DJ_U8 m_u8EventIndicator; // 事件指示码
	        public DJ_U8 m_u8EventPresentationRestrictedIndicator;// 事件显示限制指示码	
	        public fixed DJ_U8 m_u8Reserved[2]; // 对齐
        };


        // 功能指示码: ISUP_SP_FacilityIndicator //////////////////////////////////////
        public unsafe struct ISUP_spFacilityIndicator
        {	
	        public DJ_U8 m_u8FacilityIndicator; // 功能指示码
	        public fixed DJ_U8 m_u8Reserved[3];
        } ;


        // 前向呼叫指示码: ISUP_SP_ForwardCallIndicator ///////////////////////////////
        public unsafe struct ISUP_spForwardCallIndicator
        {	
	        public DJ_U8 m_u8NationalInternatoinalIndicator; // 国内/国际呼叫指示码
	        public DJ_U8 m_u8EndToEndMethodIndicator;        // 端到端方法指示码
	        public DJ_U8 m_u8InterworkingIndicator;          // 互通指示码
	        public DJ_U8 m_u8EndToEndInformationIndicator;   // 端到端信息指示码
	        public DJ_U8 m_u8ISDNUserPartIndicator;          // ISDN用户部分指示码
	        public DJ_U8 m_u8ISDNUserPartPreferenceIndicator;// ISDN用户部分优先指示码
	        public DJ_U8 m_u8ISDNAccessIndicator; // ISDN接入指示码
	        public DJ_U8 m_u8SCCPMethodIndicator; // SCCP方法指示码  	
	        public fixed DJ_U8 m_u8Reserved[4];         // 备用
        };


        // 类属数字: ISUP_SP_GenericDigit /////////////////////////////////////////////
        public unsafe struct ISUP_spGenericDigit
        {	
	        public DJ_U8         m_u8TypeOfDigit;   // 数字类型
	        public DJ_U8         m_u8EncodingScheme;// 编码计划	
	        public fixed DJ_U8 m_u8Digit[32];     // 数字
	        public DJ_U8        m_u8DigitLen;      // 数字长度
	        public DJ_U8        m_u8Reserved;      // 对齐
        };


        // 类属通知指示码: ISUP_SP_GenericNotifyIndicator /////////////////////////////
        public unsafe struct ISUP_spGenericNotifyIndicator
        {
	        public DJ_U8 m_u8NotificationIndicator; // 通知指示码
	        public DJ_U8 m_u8ExtensionIndicator;    // 扩充指示码
	        public fixed DJ_U8 m_u8Reserved[2];           // 对齐
        };


        // 类属号码: ISUP_SP_GenericNumber ////////////////////////////////////////////
        public unsafe struct ISUP_spGenericNumber
        {	
	        public DJ_U8         m_u8NumberQualifierIndicator;    // 号码限定指示码
	        public DJ_U8         m_u8NatureOfAddressIndicator;// 地址性质指示码
	        public DJ_U8         m_u8OddEvenIndicator;  // 奇偶指示码	
	        public DJ_U8         m_u8ScreeningIndicator;// 屏蔽
	        public DJ_U8         m_u8AddressPresentationRestrictedIndicator; // 显示指示
	        public DJ_U8         m_u8NumberingPlanIndicator;    // 号码计划指示
	        public DJ_U8         m_u8NumberIncompleteIndicator; //	号码不全指示	
	        public fixed DJ_S8 m_s8AddressSignal[40]; // 地址信号
	        public DJ_U8         m_u8Reserved;          // 对齐
        };


        // 类属参考: ISUP_SP_GenericReference /////////////////////////////////////////
        public unsafe struct ISUP_spGenericReference
        {
	        public           DJ_U8 m_u8ReferenceRestrictedIndicator; // 参考限定指示码
	        public           DJ_U8 m_u8ReferenceLength;  // 参考长度	
	        public fixed  DJ_U8 m_u8ReferenceCode[4]; // 参考八位组信息
	        public fixed  DJ_U8 m_u8Reserved[2];      // 对齐
        };


        // 信息指示码: ISUP_SP_InformationIndicator ///////////////////////////////////
        public unsafe struct ISUP_spInformationIndicator
        {	
	        public DJ_U8 m_u8CallingPartyAddressResponseIndicator; // 主叫用户地址响应指示码
	        public DJ_U8 m_u8HoldProvidedIndicator; // 保持提供指示码
	        public DJ_U8 m_u8CallingPartyCategoryResponseIndicator; // 主叫用户类别响应指示码
	        public DJ_U8 m_u8ChargeInformationResponseIndicator;  // 计费信息响应指示码
	        public DJ_U8 m_u8SolicitedInformationIndicator;  // 请求信息指示码
	        public fixed  DJ_U8 m_u8Reserved[3]; // 对齐
        };


        // 信息请示指示码: ISUP_SP_InformationRequestIndicator ////////////////////////
        public unsafe struct ISUP_spInformationRequestIndicator
        {	
	        public DJ_U8 m_u8CallingPartyAddressRequestIndicator; // 主叫用户地址请求指示码
	        public DJ_U8 m_u8HoldingIndicator; // 保持指示码
	        public DJ_U8 m_u8CallingPartyCategoryRequestIndicator;// 主叫用户类别请求指示码
	        public DJ_U8 m_u8ChargeInformationRequestIndicator;   // 计费信息请求指示码	
	        public DJ_U8 m_u8MaliciousCallIdentificationRequestIndicator; // 恶意呼叫识别
	        public fixed DJ_U8 m_u8Reserved[3];  // 对齐
        };


        // 定位号码: ISUP_SP_LocationNumber ///////////////////////////////////////////
        public unsafe struct ISUP_spLocationNumber
        {	
	        public DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	        public DJ_U8 m_u8OddEvenIndicator;         // 奇偶指示码

	        public DJ_U8 m_u8ScreeningIndicator;       // 屏蔽指示码
	        public DJ_U8 m_u8AddressPresentationRestrictedIndicator; // 地址显示限制指示码
	        public DJ_U8 m_u8NumberingPlanIndicator;   // 号码计划指示码
	        public DJ_U8 m_u8InternalNetworkNumberIndicator; // 内部网络号码指示码	
        	
	        public fixed DJ_S8 m_s8AddressSignal[40]; // 地址信号

	        public fixed DJ_U8 m_u8Reserved[2]; // 对齐
        };


        // MCID请求指示码: ISUP_SP_MCIDRequestIndicator ///////////////////////////////
        public unsafe struct ISUP_spMCIDRequestIndicator
        {	
	        public DJ_U8 m_u8MCIDRequestIndicator; // MCID请求指示码
	        public DJ_U8 m_u8HoldingIndicator;     // 保持指示码
	        public fixed DJ_U8 m_u8Reserved[2]; // 备用
        };


        // MCID 响应指示码: ISUP_SP_MCIDResponseIndicator /////////////////////////////
        public unsafe struct ISUP_spMCIDResponseIndicator
        {	
	        public DJ_U8 m_u8MCIDResponseIndicator; // MCID响应指示码
	        public DJ_U8 m_u8HoldProvidedIndicator; // 保持提供指示码
	        public fixed DJ_U8 m_u8Reserved[2]; // 备用
        };


        // 消息兼容性信息: ISUP_SP_MsgCompatibilityInformation ////////////////////////
        public unsafe struct ISUP_spMsgCompatibilityInformation
        {	
	        public DJ_U8 m_u8TransitAtIntermediateExchangeIndicator1;// 在中间交换局汇接指示码
	        public DJ_U8 m_u8ReleaseCallIndicator1;      // 释放呼叫指示码
	        public DJ_U8 m_u8SendNotificationIndicator1; // 发送通知指示码
	        public DJ_U8 m_u8DiscardMessageIndicator1;   // 舍弃消息指示码
	        public DJ_U8 m_u8PassOnNotPossibleIndicator1;// 通过不可能指示码
	        public DJ_U8 m_u8ExtensionIndicator1;        // 扩充指示码
	        public fixed DJ_U8 m_u8Reserved1[2];               // 对齐
        	
	        public DJ_U8 m_u8TransitAtIntermediateExchangeIndicator2;// 在中间交换局汇接指示码
	        public DJ_U8 m_u8ReleaseCallIndicator2;      // 释放呼叫指示码
	        public DJ_U8 m_u8SendNotificationIndicator2; // 发送通知指示码
	        public DJ_U8 m_u8DiscardMessageIndicator2;   // 舍弃消息指示码
	        public DJ_U8 m_u8PassOnNotPossibleIndicator2;// 通过不可能指示码
	        public DJ_U8 m_u8ExtensionIndicator2;        // 扩充指示码
	        public fixed DJ_U8 m_u8Reserved2[2];               // 对齐
        };


        // MLPP优先: ISUP_SP_MlppPrecedence ///////////////////////////////////////////
        public unsafe struct ISUP_spMlppPrecedence
        {	
	        public DJ_U8  m_u8PrecedenceLevel;  // 优先级	
	        public DJ_U8  m_u8LFB;        // LFB
	        public fixed DJ_U8  m_u8Reserved[2];// 对齐
        	
	        public DJ_U8  m_u8NIDigit1;  // 第1个NI数字
	        public DJ_U8  m_u8NIDigit2;  // 第2个NI数字
	        public DJ_U8  m_u8NIDigit3;  // 第3个NI数字
	        public DJ_U8  m_u8NIDigit4;  // 第4个NI数字	
        	
	        public DJ_U32 m_u32MLPPServiceDomain;
        };


        // 接续性质指示码: ISUP_SP_NatureOfConnectionIndicator ////////////////////////
        public struct ISUP_spNatureOfConnectionIndicator
        {	
	        public DJ_U8 m_u8SatelliteIndicator;        // 卫星指示码
	        public DJ_U8 m_u8ContinuityCheckIndicator;  // 导通检验指示码
	        public DJ_U8 m_u8EchoControlDeviceIndicator;// 回声控制器件指示码
	        public DJ_U8 m_u8Reserved;
        };


        // 网络特定功能: ISUP_SP_NetworkSpecificFacility //////////////////////////////
        public unsafe struct ISUP_spNetworkSpecificFacility
        {	
	        public fixed DJ_U8 m_u8NsfInformation[32];  // 参数信息
        	
	        public DJ_U8         m_u8NsfLen;              // 参数长度
	        public fixed DJ_U8 m_u8Reserved[3];         // 对齐	
        };


        // 任选后向呼叫指示码: ISUP_SP_OptBackwardCallIndicator ///////////////////////
        public unsafe struct ISUP_spOptBackwardCallIndicator
        {	
	        public DJ_U8 m_u8InBandInformationIndicator;    // 带内信息指示码
	        public DJ_U8 m_u8CallTransferPossibleIndicator; // 呼叫转移可能发送指示码
	        public DJ_U8 m_u8SimpleSegmentationIndicator;   // 简单分段指示码
	        public DJ_U8 m_u8MLPPUserIndicator;             // MLPP用户指示码

	        public fixed DJ_U8 m_u8Reserved[4];
        };


        // 任选前向呼叫指示码: ISUP_SP_OptForwardCallIndicator ////////////////////////
        public struct ISUP_spOptForwardCallIndicator
        {		
	        public DJ_U8 m_u8ClosedUserGroupCallIndicator; // CUG呼叫指示码
	        public DJ_U8 m_u8SimpleSegmentationIndicator;  // 简单分段指示码
	        public DJ_U8 m_u8UserIdentityRequestIndicator; // 接续的用户识别请求指示码
	        public DJ_U8 m_u8Reserved;                     // 对齐
        };


        // 原被叫号码: ISUP_SP_OriginalCalledNumber ///////////////////////////////////
        public unsafe struct ISUP_spOriginalCalledNumber
        {	
	        public DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	        public DJ_U8 m_u8OddEvenIndicator;         // 奇偶指示码
        	
	        public DJ_U8 m_u8AddressPresentationRestrictedIndicator; // 显示指示
	        public DJ_U8 m_u8NumberingPlanIndicator; // 号码计划指示
        	
	        public fixed DJ_S8 m_s8AddressSignal[40]; // 地址信号
        	
	        public fixed DJ_U8 m_u8Reserved[4];  // 备用
        };


        // 始发国际交换中心(ISC)的点码: ISUP_SP_OriginationISCPointCode ///////////////
        public unsafe struct ISUP_spOriginationISCPointCode
        {
	        public DJ_U32        m_u32SPcode;     // 点码
	        public fixed DJ_U8  m_u8Reserved[4]; // 备用
        };


        // 参数兼容性信息: ISUP_SP_ParamCompatibilityInformation //////////////////////
        public struct ISUP_spParamCompatibilityInformation
        {
	        public DJ_U8 m_u8UpgradedParameter1;         // 第一个升格参数	
	        public DJ_U8 m_u8TransitAtIntermediateExchangeIndicator1;// 在中间交换局汇接指示码
	        public DJ_U8 m_u8ReleaseCallIndicator1;      // 释放呼叫指示码
	        public DJ_U8 m_u8SendNotificationIndicator1; // 发送通知指示码
	        public DJ_U8 m_u8DiscardMessageIndicator1;   // 舍弃消息指示码
	        public DJ_U8 m_u8DiscardParameterIndicator1; // 舍弃参数指示码
	        public DJ_U8 m_u8ExtensionIndicator1;        // 扩充指示码
	        public DJ_U8 m_u8Reserved1;                  // 备用
        	
	        public DJ_U8 m_u8UpgradedParameter2;         // 第二个升格参数	
	        public DJ_U8 m_u8TransitAtIntermediateExchangeIndicator2;// 在中间交换局汇接指示码
	        public DJ_U8 m_u8ReleaseCallIndicator2;      // 释放呼叫指示码
	        public DJ_U8 m_u8SendNotificationIndicator2; // 发送通知指示码
	        public DJ_U8 m_u8DiscardMessageIndicator2;   // 舍弃消息指示码
	        public DJ_U8 m_u8DiscardParameterIndicator2; // 舍弃参数指示码
	        public DJ_U8 m_u8ExtensionIndicator2;        // 扩充指示码
	        public DJ_U8 m_u8Reserved2;                  // 备用

	        public DJ_U8 m_u8UpgradedParameter3;         // 第三个升格参数	
	        public DJ_U8 m_u8TransitAtIntermediateExchangeIndicator3;// 在中间交换局汇接指示码
	        public DJ_U8 m_u8ReleaseCallIndicator3;      // 释放呼叫指示码
	        public DJ_U8 m_u8SendNotificationIndicator3; // 发送通知指示码
	        public DJ_U8 m_u8DiscardMessageIndicator3;   // 舍弃消息指示码
	        public DJ_U8 m_u8DiscardParameterIndicator3; // 舍弃参数指示码
	        public DJ_U8 m_u8ExtensionIndicator3;        // 扩充指示码
	        public DJ_U8 m_u8Reserved3;                  // 备用
        };


        // 传播延时计数器: ISUP_SP_PropagationDelayCounter ////////////////////////////
        public unsafe struct ISUP_spPropagationDelayCounter
        {	
	        public DJ_U16        m_u16PropagationDelayValue;  // 传播时延值
	        public fixed DJ_U8  m_u8Reserved[2]; // 对齐
        };


        // 范围和状态: ISUP_SP_RangeState /////////////////////////////////////////////
        public unsafe struct ISUP_spRangeState
        {
	        public           DJ_U8  m_u8Range;      // 范围
	        public fixed  DJ_U8  m_u8Reserved[3];// 对齐
        	
	        public           DJ_U32 m_u32Status;    // 状态
        };


        // 改发号码: ISUP_SP_RedirectingNumber ////////////////////////////////////////
        public unsafe struct ISUP_spRedirectingNumber
        {	
	        public DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	        public DJ_U8 m_u8OddEvenIndicator; // 奇偶指示码	
            
	        public DJ_U8 m_u8AddressPresentationRestrictedIndicator; // 显示限制指示码
	        public DJ_U8 m_u8NumberingPlanIndicator; // 号码计划指示码	
        	
	        public fixed DJ_S8 m_s8AddressSignal[40]; // 地址信号

	        public fixed DJ_U8 m_u8Reserved[4];  // 备用
        };


        // 改发信息: ISUP_SP_RedirectionInformation ///////////////////////////////////
        public unsafe struct ISUP_spRedirectionInformation
        {
	        public DJ_U8 m_u8RedirectingIndicator; // 改发指示码
	        public DJ_U8 m_u8OriginalRedirectionReason; // 原理的改发原因
	        public DJ_U8 m_u8RedirectionCounter;   // 改发计数器
	        public DJ_U8 m_u8RedirectingReason;    // 改发原因

	        public fixed DJ_U8 m_u8Reserved[4]; // 备用	
        };


        // 改发号码: ISUP_SP_RedirectionNumber ////////////////////////////////////////
        public unsafe struct ISUP_spRedirectionNumber
        {	
	        public DJ_U8 m_u8NatureOfAddressIndicator; // 地址性质指示码
	        public DJ_U8 m_u8OddEvenIndicator;         // 奇偶指示码
	        public DJ_U8 m_u8NumberingPlanIndicator;   // 号码计划指示码
	        public DJ_U8 m_u8InternalNetworkNumberIndicator; // 内部网络号码指示码
        	
	        public fixed DJ_S8 m_s8AddressSignal[40];            // 地址信号

	        public fixed DJ_U8 m_u8Reserved[4]; // 备用
        };


        // 改发号码限制参数: ISUP_SP_RedirectionRestricition //////////////////////////
        public unsafe struct ISUP_spRedirectionRestricition
        {	
	        public DJ_U8 m_u8PresentationRestrictedIndicator; // 显示限制指示码
	        public fixed DJ_U8 m_u8Reserved[3];
        };


        // 远端操作: ISUP_SP_RemoteOperation //////////////////////////////////////////
        public unsafe struct ISUP_spRemoteOperation
        {	
	        public DJ_U8 m_u8ProtocolProfile;    // 协议剖析    
	        public DJ_U8 m_u8ExtensionIndicator; // 扩充	
	        public fixed DJ_U8 m_u8Component[240];
	        public DJ_U8 m_u8ComponentLen;
	        public DJ_U8 m_u8Reserved;          // 对齐
        };


        // 业务激活: ISUP_SP_ServiceActivation ////////////////////////////////////////
        public unsafe struct ISUP_spServiceActivation
        {
	        public fixed DJ_U8 m_u32FeatureCode[32];  // 特征码
	        public DJ_U8          m_u8FCLen;             // 特征码长度
	        public fixed DJ_U8 m_u8Reserved[3];       // 对齐	
        };


        // 信令点编码: ISUP_SP_SignalPointCode ////////////////////////////////////////
        public unsafe struct ISUP_spSignalPointCode
        {	
	        public          DJ_U32 m_u32SPcode;     // 点码	
	        public fixed DJ_U8  m_u8Reserved[4]; // 备用	
        };


        // 后续号码: ISUP_SP_SubsequentNumber /////////////////////////////////////////
        public unsafe struct ISUP_spSubsequentNumber
        {		
	        public DJ_U8         m_u8OddEvenIndicator; // 奇偶指示码
	        public fixed DJ_U8 m_u8Reserved[3];      // 对齐
	        public fixed DJ_S8 m_s8AddressSignal[40];    // 地址信号
        };


        // 暂停恢复指示: ISUP_SP_SuspendResumeIndicator ///////////////////////////////
        public unsafe struct ISUP_spSuspendResumeIndicator
        {	
	        public DJ_U8         m_u8SuspendResumeIndicator; // 暂停/恢复指示码
	        public fixed DJ_U8 m_u8Reserved[3]; // 对齐	
        };


        // 汇接网络选择: ISUP_SP_TransitNetworkSelection //////////////////////////////
        public unsafe struct ISUP_spTransitNetworkSelection
        {	
	        public DJ_U8         m_u8NetworkIdentificationPlan;   // 网络识别计划
	        public DJ_U8          m_u8TypeOfNetworkIdentification; // 网络识别类型
	        public DJ_U8          m_u8OddEvenIndicator;            // 奇偶指示码
	        public DJ_U8          m_u8Reserved;                    // 对齐
        	
	        public fixed DJ_U8 m_u8NetworkIdentification[32];   // 网络识别
        	
	        public DJ_U8          m_u8NetIdLen;                    // 网络识别长度
	        public fixed DJ_U8 m_u8Rev[3];                      // 对齐	
        };


        // 传输媒价要求: ISUP_SP_TransmissionMediumRequirement ////////////////////////
        public unsafe struct ISUP_spTransmissionMediumRequirement
        {	
	        public DJ_U8 m_u8TransmissionMediumRequirement; // 传送媒介要求
	        public fixed DJ_U8 m_u8Reserved[3]; // 对齐	
        };


        // 传输媒介要求(基本): ISUP_SP_TransmissionMediumRequirementPrime /////////////
        public unsafe struct ISUP_spTransmissionMediumRequirementPrime
        {	
	        public DJ_U8 m_u8TransmissionMediumRequirement; // 传送媒介要求
	        public fixed DJ_U8 m_u8Reserved[3]; // 对齐
        };


        // 使用中的传输媒介: ISUP_SP_TransmissionMediumUsed ///////////////////////////
        public unsafe struct ISUP_spTransmissionMediumUsed
        {	
	        public DJ_U8          m_u8TransmissionMediumRequirement; // 传送媒介要求
	        public fixed DJ_U8 m_u8Reserved[3]; // 对齐
        };


        // 用户业务信息: ISUP_SP_UserServiceInformation ///////////////////////////////
        public unsafe struct ISUP_spUserServiceInformation
        {
	        public fixed DJ_U8 m_u8USInformation[32]; // 用户业务信息
	        public          DJ_U8 m_u8USILen;            // 信息长度
	        public fixed DJ_U8 m_u8Reserved[3];       // 对齐	
        };


        // 基本用户业务信息: ISUP_SP_UserServiceInformationPrime //////////////////////
        public unsafe struct ISUP_spUserServiceInformationPrime
        {
	        public fixed DJ_U8 m_u8USInformation[32]; // 用户业务信息
        	
	        public DJ_U8          m_u8USILen;            // 信息长度
	        public fixed DJ_U8 m_u8Reserved[3];       // 对齐	
        };


        // 用户电信业务信息: ISUP_SP_UserTeleserviceInformation ///////////////////////
        public struct ISUP_spUserTeleserviceInformation
        {	
	        public DJ_U8 m_u8Presentation;   // 显示
	        public DJ_U8 m_u8Interpretation; // 解释
	        public DJ_U8 m_u8CodingStandard; // 编码标准
	        public DJ_U8 m_u8ExtensionIndicator1; // 扩充
        	
	        public DJ_U8 m_u8HighLayerCharacteristicsIdentification; // 高层特性识别
	        public DJ_U8 m_u8ExtensionIndicator2; // 扩充

	        public DJ_U8 m_u8ExtendedHighLayerCharacteristicsIdentification; // 扩充的高层特性识别
	        public DJ_U8 m_u8ExtensionIndicator3;	// 扩充
        };


        // 用户至用户指示码: ISUP_SP_UserToUserIndicator //////////////////////////////
        public unsafe struct ISUP_spUserToUserIndicator
        {	
	        public DJ_U8          m_u8Type;     // 类型
	        public DJ_U8          m_u8Service1; // 业务
	        public DJ_U8          m_u8Service2; // 业务
	        public DJ_U8          m_u8Service3; // 业务
	        public DJ_U8          m_u8NetworkDiscardIndicator; // 网络舍弃指示码
	        public fixed DJ_U8 m_u8Reserved[3]; // 对齐
        };


        // 用户至用户信息: ISUP_SP_UserToUserInformation //////////////////////////////
        public unsafe struct ISUP_spUserToUserInformation
        {	
	        public fixed DJ_U8  m_u8UserToUserInformation[240];
        	
	        public DJ_U8          m_u8UifLen;      // 信息长度
	        public fixed DJ_U8  m_u8Reserved[3]; // 对齐
        };
}
