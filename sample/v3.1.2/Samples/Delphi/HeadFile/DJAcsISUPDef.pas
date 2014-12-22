unit DJAcsISUPDef;

interface

uses
  Windows;

// ISUP������Ϣ����(������Ҫֱ�ӷ��Ͳ���) /////////////////////////////////////
Type XMS_ISUP_Signalling_Message =     // ISUP������Ϣ
(
	ISUP_SM_BLO = $13,              // ���
	
	ISUP_SM_CGB = $18,              // ��·Ⱥ���
	ISUP_SM_CGU = $19,              // ��·Ⱥ�������
	ISUP_SM_CPG = $2C,              // ���н�չ
	ISUP_SM_CQM = $2A,              // ��·Ⱥ��Ѷ
	
	ISUP_SM_GRS = $17,              // ��·Ⱥ��ԭ
	
	ISUP_SM_INF = $04,              // ��Ϣ
	ISUP_SM_INR = $03,              // ��Ϣ����
	
	ISUP_SM_RES = $0E,              // �ָ�
	ISUP_SM_RSC = $12,              // ��·��ԭ
	
	ISUP_SM_SAM = $02,              // ������ַ
	ISUP_SM_SGM = $38,              // �ֶ�
	ISUP_SM_SUS = $0D,              // ��ͣ
	
	ISUP_SM_UBL = $14,              // �������
	ISUP_SM_USR = $2D               // �û����û���Ϣ
);


// ISUP����������� ///////////////////////////////////////////////////////////
Type XMS_ISUP_Signalling_Parameter =                      // ISUP�������
(
	ISUP_SP_AccessDeliveryInformation          = $2E, // ���봫����Ϣ
	ISUP_SP_AccessTransport                    = $03, // ���봫��
	ISUP_SP_AutomaticCongestionLevel           = $27, // �Զ�ӵ����
	ISUP_SP_BackwardCallIndicator              = $11, // �������ָʾ��
	ISUP_SP_CallDiversionInformation           = $36, // ����ת����Ϣ
	ISUP_SP_CallHistoryInformation             = $2D, // ������ʷ��Ϣ
	ISUP_SP_CallReference                      = $01, // ���вο�
	ISUP_SP_CalledPartNumber                   = $04, // �����û�����
	ISUP_SP_CallingPartNumber                  = $0A, // �����û�����
	ISUP_SP_CallingPartCategory                = $09, // �����û����
	ISUP_SP_CauseIndicator                     = $12, // ԭ��ָʾ��
	ISUP_SP_CircuitGroupSupervisionIndicator   = $15, // ��·Ⱥ������Ϣ����ָʾ��
	ISUP_SP_CircuitStateIndicator              = $26, // ��·״ָ̬ʾ��
	ISUP_SP_CUGInterlockCode                   = $1A, // �պ��û�Ⱥ�����
	ISUP_SP_ConnectedNumber                    = $21, // �����ĺ���
	ISUP_SP_ConnectionRequest                  = $0D, // ��������
	ISUP_SP_ContitnuityIndicator               = $10, // ��ָͨʾ��
	ISUP_SP_EchoControlInformation             = $37, // ����������Ϣ
	ISUP_SP_EndOptionalParameter               = $00, // ��ѡ����βָʾ��
	ISUP_SP_EventInformation                   = $24, // �¼���Ϣ
	ISUP_SP_FacilityIndicator                  = $18, // ����ָʾ��
	ISUP_SP_ForwardCallIndicator               = $07, // ǰ�����ָʾ��
	ISUP_SP_GenericDigit                       = $47, // ��������
	ISUP_SP_GenericNotifyIndicator             = $2C, // ����ָ֪ͨʾ��
	ISUP_SP_GenericNumber                      = $46, // ��������
	ISUP_SP_GenericReference                   = $42, // �����ο�
	ISUP_SP_InformationIndicator               = $0F, // ��Ϣָʾ��
	ISUP_SP_InformationRequestIndicator        = $0E, // ��Ϣ����ָʾ��
	ISUP_SP_LocationNumber                     = $3F, // ��λ����
	ISUP_SP_MCIDRequestIndicator               = $3B, // MCID����ָʾ��
	ISUP_SP_MCIDResponseIndicator              = $3C, // MCID��Ӧָʾ��
	ISUP_SP_MsgCompatibilityInformation        = $38, // ��Ϣ��������Ϣ
	ISUP_SP_MlppPrecedence                     = $3A, // MLPP����
	ISUP_SP_NatureOfConnectionIndicator        = $06, // ��������ָʾ��
	ISUP_SP_NetworkSpecificFacility            = $2F, // �����ض�����
	ISUP_SP_OptBackwardCallIndicator           = $29, // ��ѡ�������ָʾ��
	ISUP_SP_OptForwardCallIndicator            = $08, // ��ѡǰ�����ָʾ��
	ISUP_SP_OriginalCalledNumber               = $28, // ԭ���ı��к���
	ISUP_SP_OriginationISCPointCode            = $2B, // ʼ�����ʽ�������(ISC)�ĵ���
	ISUP_SP_ParamCompatibilityInformation      = $39, // ������������Ϣ
	ISUP_SP_PropagationDelayCounter            = $31, // �����ӳټ�����
	ISUP_SP_RangeState                         = $16, // ��Χ��״̬
	ISUP_SP_RedirectingNumber                  = $0B, // �ķ�����
	ISUP_SP_RedirectionInformation             = $13, // �ķ���Ϣ
	ISUP_SP_RedirectionNumber                  = $0C, // �ķ�����
	ISUP_SP_RedirectionRestricition            = $40, // �ķ��������Ʋ���
	ISUP_SP_RemoteOperation                    = $32, // Զ�˲���
	ISUP_SP_ServiceActivation                  = $33, // ҵ�񼤻�
	ISUP_SP_SignalPointCode                    = $1E, // ��������
	ISUP_SP_SubsequentNumber                   = $05, // ��������
	ISUP_SP_SuspendResumeIndicator             = $22, // ��ͣ/�ָ�ָʾ��
	ISUP_SP_TransitNetworkSelection            = $23, // �������ѡ��
	ISUP_SP_TransmissionMediumRequirement      = $02, // ����ý��Ҫ��
	ISUP_SP_TransmissionMediumRequirementPrime = $3E, // ����ý��Ҫ��(������)
	ISUP_SP_TransmissionMediumUsed             = $35, // ʹ�õĴ���ý��
	ISUP_SP_UserServiceInformation             = $1D, // �û�ҵ����Ϣ
	ISUP_SP_UserServiceInformationPrime        = $30, // �û�ҵ����Ϣ(������)
	ISUP_SP_UserTeleserviceInformation         = $34, // �û��ն�ҵ����Ϣ
	ISUP_SP_UserToUserIndicator                = $2A, // �û����û�ָʾ��
	ISUP_SP_UserToUserInformation              = $20, // �û����û���Ϣ
	ISUP_SP_MessageParameterAllParse           = $FF, // ���������в���(�255)
	ISUP_SP_MessageParameterAllRaw             = $FE  // ԭʼ�����в���(�255)
);


// ISUP����������ݽṹ���� ///////////////////////////////////////////////////
// ���봫����Ϣ: ISUP_SP_AccessDeliveryInformation ////////////////////////////
Type
  ISUP_spAccessDeliveryInformation = record
	m_u8AccessDeliveryID : Byte;  // ���봫��ָʾ��
	m_u8Reserved         : Array[0..2] of Byte;       // ����
end;


// ���봫��: ISUP_SP_AccessTransport //////////////////////////////////////////
Type
  ISUP_spAccessTransport = record
	m_u8AtpInformation : Array[0..239] of Byte;  // ��Ϣ��Ԫ��4.5/Q.931��������
	m_u8AtpLen         : Byte;                   // ��������
	m_u8Reserved       : Array[0..2] of Byte;    // ����
end;


// �Զ�ӵ����: ISUP_SP_AutomaticCongestionLevel ///////////////////////////////
Type
  ISUP_spAutomaticCongestionLevel = record
	m_u8CongestionLevelExceeded : Byte;     // ӵ��������ĳ������
	m_u8Reserved : Array[0..2] of Byte;     // ����
end;


// �������ָʾ��: ISUP_SP_BackwardCallIndicator //////////////////////////////
Type
  ISUP_spBackwardCallIndicator = record
	m_u8ChargeIndicator         : Byte;       // �Ʒ�ָʾ��
	m_u8CalledStatusIndicator   : Byte;       // �����û�״ָ̬ʾ��
	m_u8CalledCategoryIndicator : Byte;       // �����û����ָʾ��
 	m_u8EndToEndMethodIndicator : Byte;       // �˵��˷���ָʾ��

	m_u8InterworkingIndicator         : Byte; // ��ָͨʾ��
	m_u8EndToEndInformationIndicator  : Byte; // �˵�����Ϣָʾ��
	m_u8ISDNUserPartIndicator         : Byte; // ISDN�û�����ָʾ��
	m_u8HoldingIndicator              : Byte; // ����ָʾ��
	m_u8ISDNAccessIndicator           : Byte; // ISDN����ָʾ��
	m_u8EchoControlDeviceIndicator    : Byte; // ������������ָʾ��
	m_u8SCCPMethodIndicator           : Byte; // SCCP����ָʾ��
	m_u8Reserved                      : Byte; // ����
end;


// ����ת����Ϣ: ISUP_SP_CallDiversionInformation /////////////////////////////
Type
  ISUP_spCallDiversionInformation = record
	m_u8NotificationSubscriptionOptions : Byte; // ֪ͨ�Ǽ���ѡ
	m_u8RedirectingReason : Byte;               // �ķ�ԭ��
	m_u8Reserved          : Array[0..1] of Byte;// ����
end;


// ������ʷ��Ϣ: ISUP_SP_CallHistoryInformation ///////////////////////////////
Type
  ISUP_spCallHistoryInformation = record
	m_u16PropagationDelayValue : Word;    // ����ʱ��ֵ
	m_u8Reserved : Array[0..1] of Byte;  // ����
end;


// ���вο�: ISUP_SP_CallReference ////////////////////////////////////////////
Type
  ISUP_spCallReference = record
	m_u32CallIdentity : DWORD; // ����ʶ��

	m_u32SPcode : DWORD;       // ����
	m_u8Reserved : Array[0..3] of Byte;   // ����
end;


// �����û�����: ISUP_SP_CalledPartNumber /////////////////////////////////////
Type
  ISUP_spCalledPartNumber = record
	m_u8NatureOfAddressIndicator : Byte;      // ��ַ����ָʾ��
	m_u8OddEvenIndicator         : Byte;      // ��żָʾ��
	m_u8NumberingPlanIndicator   : Byte;      // ����ƻ�ָʾ
	m_u8InternalNetworkNumberIndicator : Byte;// �ڲ��������ָʾ��

	m_u8Reserved      : Array[0..3] of Byte;          // ����

 	m_s8AddressSignal : Array[0..39] of Byte;         // ��ַ�ź�
end;


// �����û�����: ISUP_SP_CallingPartNumber ////////////////////////////////////
Type
  ISUP_spCallingPartNumber = record
	m_u8NatureOfAddressIndicator : Byte; // ��ַ����ָʾ��
	m_u8OddEvenIndicator : Byte;         // ��żָʾ��
	
	m_u8Screening : Byte;                // ����
	m_u8AddressPresentationRestrictedIndicator : Byte;  // ��ַ��ʾָʾ
	m_u8NumberingPlanIndicator : Byte;   // ����ƻ�ָʾ
	m_u8NumberIncompleteIndicator : Byte;// ���к��벻ȫָʾ
	
	m_s8AddressSignal : Array[0..39] of ShortInt; // ��ַ�ź�
	
  m_u8Reserved : Array[0..1] of ShortInt;       // ����
end;


// �����û����: ISUP_SP_CallingPartCategory //////////////////////////////////
Type
  ISUP_spCallingPartCategory = record
	m_u8CallingPartyCategory : Byte;    // �����û����
	m_u8Reserved : Array[0..2] of Byte; // ����
end;


// ԭ��ָʾ��: ISUP_SP_CauseIndicator /////////////////////////////////////////
Type
  ISUP_spCauseIndicator = record
	m_u8Location : Byte;             // ��λ
	m_u8CodindStandard : Byte;       // �����׼
	m_u8ExtensionIndicator1 : Byte;  // ����
	
	m_u8CauseValue : Byte;           // ԭ��ֵ
	m_u8ExtensionIndicator2 : Byte;  // ����
	
	m_u8Reserved : Array[0..1] of Byte;          // ����

	m_u8Diagnose : Array[0..31] of Byte;         // ���
	m_u8DiagnoseLen : byte;          // ��ϳ���
end;


// ��·Ⱥ������Ϣ����ָʾ��: ISUP_SP_CircuitGroupSupervisionIndicator /////////
Type
  ISUP_spCircuitGroupSupervisionIndicator = record
	m_u8CircuitGroupSupervisionIndicator : byte; // ����ָʾ��
	m_u8Reserved : Array[0..2] of Byte; // ����
end;


// ��·״ָ̬ʾ��: ISUP_SP_CircuitStateIndicator //////////////////////////////
Type
  ISUP_spCircuitStateIndicator = record
	m_u8CircuitStateIndicator : Array[0..31] of Byte;
end;


// �պ��û�Ⱥ�����: ISUP_SP_CUGInterlockCode /////////////////////////////////
Type
  ISUP_spCUGInterlockCode  =record
	m_u8NIDigit1 : byte;  // ��1��NI����
	m_u8NIDigit2 : byte;  // ��2��NI����
	m_u8NIDigit3 : byte;  // ��3��NI����
	m_u8NIDigit4 : byte;  // ��4��NI����
	
	m_u16BinaryCode : Word; // ��������
	m_u8Reserved : Array[0..1] of Byte; // ����
end;


// �����ĺ���: ISUP_SP_ConnectedNumber ////////////////////////////////////////
Type
  ISUP_spConnectedNumber = record
	m_u8NatureOfAddressIndicator : Byte; // ��ַ����ָʾ��
	m_u8OddEvenIndicator : Byte;         // ��żָʾ��
    
	m_u8ScreeningIndicator : Byte;       // ����ָʾ��
	m_u8AddressPresentationRestrictedIndicator : Byte; // ��ַ��ʾ����
	m_u8NumberingPlanIndicator : Byte;   // ����ƻ�ָʾ

	m_u8Reserved : Array[0..2] of Byte;              // ����
	
	m_s8AddressSignal : Array[0..39] of Byte;        // ��ַ�ź�
end;


// ��������: ISUP_SP_ConnectionRequest ////////////////////////////////////////
Type
  ISUP_spConnectionRequest = record
	m_u32LocalReference : DWORD; // ����ʶ��
	
	m_u32SPcode : DWORD;         // ����
	
	m_u8ProtocolClass : Byte;    // Э�����
	m_u8Credit : Byte;           // �ź���

	m_u8Reserved : Array[0..1] of Byte;     // ����
end;


// ��ָͨʾ��: ISUP_SP_ContitnuityIndicator ///////////////////////////////////
Type
  ISUP_spContitnuityIndicator = record
	m_u8ContinuityIndicator : Byte; // ��ָͨʾ��
	m_u8Reserved : Array[0..2] of Byte; // ����
end;


// ����������Ϣ: ISUP_SP_EchoControlInformation ///////////////////////////////
Type
  ISUP_spEchoControlInformation = record
	m_u8OutEchoControlInformationIndicator : Byte; // ȥ�������������Ӧָʾ
	m_u8InEchoControlInformationIndicator : Byte;  // ���������������Ӧָʾ
	m_u8OutEchoControlRequestIndicator : Byte;     // ȥ���������������ָʾ
	m_u8InEchoControlRequestIndicator : Byte;      // �����������������ָʾ
end;


// �¼���Ϣ: ISUP_SP_EventInformation /////////////////////////////////////////
Type
  ISUP_spEventInformation = record
	m_u8EventIndicator : Byte; // �¼�ָʾ��
	m_u8EventPresentationRestrictedIndicator : Byte;// �¼���ʾ����ָʾ��
	m_u8Reserved : Array[0..1] of Byte; // ����
end;


// ����ָʾ��: ISUP_SP_FacilityIndicator //////////////////////////////////////
Type
  ISUP_spFacilityIndicator = record
	m_u8FacilityIndicator : Byte; // ����ָʾ��
	m_u8Reserved : Array[0..2] of Byte;
end;


// ǰ�����ָʾ��: ISUP_SP_ForwardCallIndicator ///////////////////////////////
Type
  ISUP_spForwardCallIndicator = record
	m_u8NationalInternatoinalIndicator : Byte; // ����/���ʺ���ָʾ��
	m_u8EndToEndMethodIndicator : Byte;        // �˵��˷���ָʾ��
	m_u8InterworkingIndicator : Byte;          // ��ָͨʾ��
	m_u8EndToEndInformationIndicator : Byte;   // �˵�����Ϣָʾ��
	m_u8ISDNUserPartIndicator : Byte;          // ISDN�û�����ָʾ��
	m_u8ISDNUserPartPreferenceIndicator : Byte;// ISDN�û���������ָʾ��
	
	m_u8ISDNAccessIndicator : Byte; // ISDN����ָʾ��
	m_u8SCCPMethodIndicator : Byte; // SCCP����ָʾ��
	
	m_u8Reserved : Array[0..3] of Byte;        // ����
end;


// ��������: ISUP_SP_GenericDigit /////////////////////////////////////////////
Type
  ISUP_spGenericDigit = record
	m_u8TypeOfDigit : Byte;   // ��������
	m_u8EncodingScheme : Byte;// ����ƻ�
	
	m_u8Digit : Array[0..31] of Byte;     // ����
	m_u8DigitLen : Byte;      // ���ֳ���
	
	m_u8Reserved : Byte;      // ����
end;


// ����ָ֪ͨʾ��: ISUP_SP_GenericNotifyIndicator /////////////////////////////
Type
  ISUP_spGenericNotifyIndicator = record
	m_u8NotificationIndicator : Byte;    // ָ֪ͨʾ��
	m_u8ExtensionIndicator    : Byte;    // ����ָʾ��
	m_u8Reserved : Array[0..1] of Byte;  // ����
end;


// ��������: ISUP_SP_GenericNumber ////////////////////////////////////////////
Type
  ISUP_spGenericNumber = record
	m_u8NumberQualifierIndicator : Byte; // �����޶�ָʾ��

	m_u8NatureOfAddressIndicator : Byte; // ��ַ����ָʾ��
	m_u8OddEvenIndicator         : Byte; // ��żָʾ��

	m_u8ScreeningIndicator       : Byte; // ����
	m_u8AddressPresentationRestrictedIndicator : Byte; // ��ʾָʾ
	m_u8NumberingPlanIndicator   : Byte; // ����ƻ�ָʾ
	m_u8NumberIncompleteIndicator: Byte; //	���벻ȫָʾ

	m_s8AddressSignal : Array[0..39] of ShortInt; // ��ַ�ź�
	
	m_u8Reserved : Byte;          // ����
end;


// �����ο�: ISUP_SP_GenericReference /////////////////////////////////////////
Type
  ISUP_spGenericReference = record
	m_u8ReferenceRestrictedIndicator : Byte; // �ο��޶�ָʾ��
	m_u8ReferenceLength  : Byte;  // �ο�����
	
	m_u8ReferenceCode : Array[0..3] of Byte; // �ο���λ����Ϣ
	m_u8Reserved      : Array[0..1] of Byte; // ����
end;


// ��Ϣָʾ��: ISUP_SP_InformationIndicator ///////////////////////////////////
Type
  ISUP_spInformationIndicator = record
	m_u8CallingPartyAddressResponseIndicator : Byte; // �����û���ַ��Ӧָʾ��
	m_u8HoldProvidedIndicator : Byte; // �����ṩָʾ��
	
	m_u8CallingPartyCategoryResponseIndicator : Byte; // �����û������Ӧָʾ��
	m_u8ChargeInformationResponseIndicator : Byte;  // �Ʒ���Ϣ��Ӧָʾ��
	m_u8SolicitedInformationIndicator : Byte;  // ������Ϣָʾ��
	
	m_u8Reserved : Array[0..2] of Byte; // ����
end;


// ��Ϣ��ʾָʾ��: ISUP_SP_InformationRequestIndicator ////////////////////////
Type
  ISUP_spInformationRequestIndicator = record
	m_u8CallingPartyAddressRequestIndicator : byte; // �����û���ַ����ָʾ��
	m_u8HoldingIndicator : byte; // ����ָʾ��
	m_u8CallingPartyCategoryRequestIndicator : byte;// �����û��������ָʾ��
	m_u8ChargeInformationRequestIndicator : byte;   // �Ʒ���Ϣ����ָʾ��
	m_u8MaliciousCallIdentificationRequestIndicator : byte; // �������ʶ��
	m_u8Reserved : Array[0..2] of Byte;  // ����
end;


// ��λ����: ISUP_SP_LocationNumber ///////////////////////////////////////////
Type
  ISUP_spLocationNumber = record
	m_u8NatureOfAddressIndicator : Byte; // ��ַ����ָʾ��
	m_u8OddEvenIndicator : Byte;         // ��żָʾ��

	m_u8ScreeningIndicator : Byte;       // ����ָʾ��
	m_u8AddressPresentationRestrictedIndicator : Byte; // ��ַ��ʾ����ָʾ��
	m_u8NumberingPlanIndicator : Byte;   // ����ƻ�ָʾ��
	m_u8InternalNetworkNumberIndicator : Byte; // �ڲ��������ָʾ��
	
	m_s8AddressSignal : Array[0..39] of ShortInt; // ��ַ�ź�

	m_u8Reserved : Array[0..1] of Byte;  // ����
end;


// MCID����ָʾ��: ISUP_SP_MCIDRequestIndicator ///////////////////////////////
Type
  ISUP_spMCIDRequestIndicator = record
	m_u8MCIDRequestIndicator : byte;    // MCID����ָʾ��
	m_u8HoldingIndicator     : byte;    // ����ָʾ��
	m_u8Reserved : Array[0..1] of Byte; // ����
end;


// MCID ��Ӧָʾ��: ISUP_SP_MCIDResponseIndicator /////////////////////////////
Type
  ISUP_spMCIDResponseIndicator = record
	m_u8MCIDResponseIndicator : Byte; // MCID��Ӧָʾ��
	m_u8HoldProvidedIndicator : Byte; // �����ṩָʾ��
	m_u8Reserved : Array[0..1] of Byte; // ����
end;


// ��Ϣ��������Ϣ: ISUP_SP_MsgCompatibilityInformation ////////////////////////
Type
  ISUP_spMsgCompatibilityInformation = record
	m_u8TransitAtIntermediateExchangeIndicator1 : byte;// ���м佻���ֻ��ָʾ��
	m_u8ReleaseCallIndicator1 : byte;      // �ͷź���ָʾ��
	m_u8SendNotificationIndicator1 : byte; // ����ָ֪ͨʾ��
	m_u8DiscardMessageIndicator1 : byte;   // ������Ϣָʾ��
	m_u8PassOnNotPossibleIndicator1 : byte;// ͨ��������ָʾ��
	m_u8ExtensionIndicator1 : byte;        // ����ָʾ��
	m_u8Reserved1 : Array[0..1] of Byte;               // ����
	
	m_u8TransitAtIntermediateExchangeIndicator2 : byte;// ���м佻���ֻ��ָʾ��
	m_u8ReleaseCallIndicator2 : byte;      // �ͷź���ָʾ��
	m_u8SendNotificationIndicator2 : byte; // ����ָ֪ͨʾ��
	m_u8DiscardMessageIndicator2 : byte;   // ������Ϣָʾ��
	m_u8PassOnNotPossibleIndicator2 : byte;// ͨ��������ָʾ��
	m_u8ExtensionIndicator2 : byte;        // ����ָʾ��
	m_u8Reserved2 : Array[0..1] of Byte;               // ����
end;


// MLPP����: ISUP_SP_MlppPrecedence ///////////////////////////////////////////
Type
  ISUP_spMlppPrecedence = record
	m_u8PrecedenceLevel : Byte;  // ���ȼ�
	m_u8LFB : Byte;        // LFB
	m_u8Reserved : Array[0..1] of Byte;// ����

	m_u8NIDigit1 : Byte;  // ��1��NI����
	m_u8NIDigit2 : Byte;  // ��2��NI����
	m_u8NIDigit3 : Byte;  // ��3��NI����
	m_u8NIDigit4 : Byte;  // ��4��NI����
	
	m_u32MLPPServiceDomain : DWORD;
end;


// ��������ָʾ��: ISUP_SP_NatureOfConnectionIndicator ////////////////////////
Type
  ISUP_spNatureOfConnectionIndicator = record
	m_u8SatelliteIndicator : Byte;        // ����ָʾ��
	m_u8ContinuityCheckIndicator : Byte;  // ��ͨ����ָʾ��
	m_u8EchoControlDeviceIndicator : Byte;// ������������ָʾ��
	m_u8Reserved : Byte;
end;


// �����ض�����: ISUP_SP_NetworkSpecificFacility //////////////////////////////
Type
  ISUP_spNetworkSpecificFacility = record
	m_u8NsfInformation : Array[0..31] of Byte;  // ������Ϣ
	
	m_u8NsfLen         : Byte;                  // ��������
	m_u8Reserved       : Array[0..2] of Byte;   // ����
end;


// ��ѡ�������ָʾ��: ISUP_SP_OptBackwardCallIndicator ///////////////////////
Type
  ISUP_spOptBackwardCallIndicator = record
	m_u8InBandInformationIndicator    : Byte; // ������Ϣָʾ��
	m_u8CallTransferPossibleIndicator : Byte; // ����ת�ƿ��ܷ���ָʾ��
	m_u8SimpleSegmentationIndicator   : Byte; // �򵥷ֶ�ָʾ��
	m_u8MLPPUserIndicator : Byte;             // MLPP�û�ָʾ��

	m_u8Reserved : Array[0..3] of Byte;
end;


// ��ѡǰ�����ָʾ��: ISUP_SP_OptForwardCallIndicator ////////////////////////
Type
  ISUP_spOptForwardCallIndicator = record
	m_u8ClosedUserGroupCallIndicator : byte; // CUG����ָʾ��
	m_u8SimpleSegmentationIndicator  : byte; // �򵥷ֶ�ָʾ��
	m_u8UserIdentityRequestIndicator : byte; // �������û�ʶ������ָʾ��
	m_u8Reserved : byte;                     // ����
end;


// ԭ���к���: ISUP_SP_OriginalCalledNumber ///////////////////////////////////
Type
  ISUP_spOriginalCalledNumber = record
	m_u8NatureOfAddressIndicator : byte; // ��ַ����ָʾ��
	m_u8OddEvenIndicator         : byte; // ��żָʾ��

	m_u8AddressPresentationRestrictedIndicator : byte; // ��ʾָʾ
	m_u8NumberingPlanIndicator   : byte; // ����ƻ�ָʾ

	m_s8AddressSignal : Array[0..39] of ShortInt; // ��ַ�ź�
	
	m_u8Reserved      : Array[0..3] of Byte;      // ����
end;


// ʼ�����ʽ�������(ISC)�ĵ���: ISUP_SP_OriginationISCPointCode ///////////////
Type
  ISUP_spOriginationISCPointCode = record
	m_u32SPcode  : DWORD;     // ����
	m_u8Reserved : Array[0..3] of Byte; // ����
end;


// ������������Ϣ: ISUP_SP_ParamCompatibilityInformation //////////////////////
Type
  ISUP_spParamCompatibilityInformation = record
	m_u8UpgradedParameter1 : Byte;         // ��һ���������
	m_u8TransitAtIntermediateExchangeIndicator1 : Byte;// ���м佻���ֻ��ָʾ��
	m_u8ReleaseCallIndicator1 : Byte;      // �ͷź���ָʾ��
	m_u8SendNotificationIndicator1 : Byte; // ����ָ֪ͨʾ��
	m_u8DiscardMessageIndicator1 : Byte;   // ������Ϣָʾ��
	m_u8DiscardParameterIndicator1 : Byte; // ��������ָʾ��
	m_u8ExtensionIndicator1 : Byte;        // ����ָʾ��
	m_u8Reserved1 : Byte;                  // ����
	
	m_u8UpgradedParameter2 : Byte;         // �ڶ����������
	m_u8TransitAtIntermediateExchangeIndicator2 : Byte;// ���м佻���ֻ��ָʾ��
	m_u8ReleaseCallIndicator2 : Byte;      // �ͷź���ָʾ��
	m_u8SendNotificationIndicator2 : Byte; // ����ָ֪ͨʾ��
	m_u8DiscardMessageIndicator2 : Byte;   // ������Ϣָʾ��
	m_u8DiscardParameterIndicator2 : Byte; // ��������ָʾ��
	m_u8ExtensionIndicator2 : Byte;        // ����ָʾ��
	m_u8Reserved2 : Byte;                  // ����

	m_u8UpgradedParameter3 : Byte;         // �������������
	m_u8TransitAtIntermediateExchangeIndicator3 : Byte;// ���м佻���ֻ��ָʾ��
	m_u8ReleaseCallIndicator3 : Byte;      // �ͷź���ָʾ��
	m_u8SendNotificationIndicator3 : Byte; // ����ָ֪ͨʾ��
	m_u8DiscardMessageIndicator3 : Byte;   // ������Ϣָʾ��
	m_u8DiscardParameterIndicator3 : Byte; // ��������ָʾ��
	m_u8ExtensionIndicator3 : Byte;        // ����ָʾ��
	m_u8Reserved3 : Byte;                  // ����
end;


// ������ʱ������: ISUP_SP_PropagationDelayCounter ////////////////////////////
Type
  ISUP_spPropagationDelayCounter = record
	m_u16PropagationDelayValue : Word;     // ����ʱ��ֵ
	m_u8Reserved : Array[0..1] of Byte; // ����
end;


// ��Χ��״̬: ISUP_SP_RangeState /////////////////////////////////////////////
Type
  ISUP_spRangeState = record
	m_u8Range : Byte;      // ��Χ
	m_u8Reserved : Array[0..2] of Byte;// ����
	
	m_u32Status : DWORD;    // ״̬
end;


// �ķ�����: ISUP_SP_RedirectingNumber ////////////////////////////////////////
Type
  ISUP_spRedirectingNumber = record
	m_u8NatureOfAddressIndicator : Byte; // ��ַ����ָʾ��
	m_u8OddEvenIndicator         : Byte; // ��żָʾ��
    
	m_u8AddressPresentationRestrictedIndicator : Byte; // ��ʾ����ָʾ��
	m_u8NumberingPlanIndicator : Byte; // ����ƻ�ָʾ��
	
	m_s8AddressSignal      : Array[0..39] of ShortInt; // ��ַ�ź�

	m_u8Reserved           : Array[0..3] of Byte;      // ����
end;


// �ķ���Ϣ: ISUP_SP_RedirectionInformation ///////////////////////////////////
Type
  ISUP_spRedirectionInformation = record
	m_u8RedirectingIndicator : Byte;      // �ķ�ָʾ��
	m_u8OriginalRedirectionReason : Byte; // ԭ��ĸķ�ԭ��
	m_u8RedirectionCounter   : Byte;      // �ķ�������
	m_u8RedirectingReason    : Byte;      // �ķ�ԭ��
	m_u8Reserved : Array[0..3] of Byte;   // ����
end;


// �ķ�����: ISUP_SP_RedirectionNumber ////////////////////////////////////////
Type
  ISUP_spRedirectionNumber = record
	m_u8NatureOfAddressIndicator : Byte;    // ��ַ����ָʾ��
	m_u8OddEvenIndicator         : Byte;    // ��żָʾ��
	m_u8NumberingPlanIndicator   : Byte;    // ����ƻ�ָʾ��
	m_u8InternalNetworkNumberIndicator : Byte; // �ڲ��������ָʾ��

	m_s8AddressSignal : Array[0..39] of Byte;  // ��ַ�ź�

	m_u8Reserved      : Array[0..3] of Byte;   // ����
end;


// �ķ��������Ʋ���: ISUP_SP_RedirectionRestricition //////////////////////////
Type
  ISUP_spRedirectionRestricition = record
	m_u8PresentationRestrictedIndicator : Byte; // ��ʾ����ָʾ��
	m_u8Reserved : Array[0..2] of Byte;
end;


// Զ�˲���: ISUP_SP_RemoteOperation //////////////////////////////////////////
Type
  ISUP_spRemoteOperation  =record
	m_u8ProtocolProfile    : Byte; // Э������
	m_u8ExtensionIndicator : Byte; // ����
	m_u8Component : Array[0..239] of Byte;
	m_u8ComponentLen : Byte;
	m_u8Reserved     : Byte;       // ����
end;


// ҵ�񼤻�: ISUP_SP_ServiceActivation ////////////////////////////////////////
Type
  ISUP_spServiceActivation = record
	m_u32FeatureCode : Array[0..31] of Byte;  // ������
	m_u8FCLen        : Byte;                  // �����볤��
	m_u8Reserved     : Array[0..2] of Byte;   // ����
end;


// ��������: ISUP_SP_SignalPointCode ////////////////////////////////////////
Type
  ISUP_spSignalPointCode = record
	m_u32SPcode  : DWORD;     // ����
	m_u8Reserved : Array[0..3] of Byte; // ����
end;


// ��������: ISUP_SP_SubsequentNumber /////////////////////////////////////////
Type
  ISUP_spSubsequentNumber = record
	m_u8OddEvenIndicator : byte; // ��żָʾ��
	m_u8Reserved      : Array[0..2] of Byte;     // ����
	m_s8AddressSignal : Array[0..39] of Byte;    // ��ַ�ź�
end;


// ��ͣ�ָ�ָʾ: ISUP_SP_SuspendResumeIndicator ///////////////////////////////
Type
  ISUP_spSuspendResumeIndicator = record
	m_u8SuspendResumeIndicator : Byte;     // ��ͣ/�ָ�ָʾ��
	m_u8Reserved : Array[0..2] of Byte; // ����
end;


// �������ѡ��: ISUP_SP_TransitNetworkSelection //////////////////////////////
Type
  ISUP_spTransitNetworkSelection = record
	m_u8NetworkIdentificationPlan   : Byte;   // ����ʶ��ƻ�
	m_u8TypeOfNetworkIdentification : Byte;   // ����ʶ������
	m_u8OddEvenIndicator            : Byte;   // ��żָʾ��
	m_u8Reserved                    : Byte;                    // ����

	m_u8NetworkIdentification       : Array[0..31] of Byte;    // ����ʶ��

	m_u8NetIdLen                    : Byte;                    // ����ʶ�𳤶�
  m_u8Rev                         : Array[0..2] of Byte;     // ����
end;


// ����ý��Ҫ��: ISUP_SP_TransmissionMediumRequirement ////////////////////////
Type
  ISUP_spTransmissionMediumRequirement = record
	m_u8TransmissionMediumRequirement : Byte; // ����ý��Ҫ��
	m_u8Reserved : Array[0..2] of Byte;       // ����
end;


// ����ý��Ҫ��(����): ISUP_SP_TransmissionMediumRequirementPrime /////////////
Type
  ISUP_spTransmissionMediumRequirementPrime = record
	m_u8TransmissionMediumRequirement : Byte; // ����ý��Ҫ��
	m_u8Reserved : Array[0..2] of Byte;       // ����
end;


// ʹ���еĴ���ý��: ISUP_SP_TransmissionMediumUsed ///////////////////////////
Type
  ISUP_spTransmissionMediumUsed = record

	m_u8TransmissionMediumRequirement : Byte; // ����ý��Ҫ��
	m_u8Reserved : Array[0..2] of Byte;       // ����
end;


// �û�ҵ����Ϣ: ISUP_SP_UserServiceInformation ///////////////////////////////
Type
  ISUP_spUserServiceInformation = record
	m_u8USInformation : Array[0..31] of Byte; // �û�ҵ����Ϣ
	m_u8USILen        : Byte;                 // ��Ϣ����
	m_u8Reserved      : Array[0..2] of Byte;  // ����
end;


// �����û�ҵ����Ϣ: ISUP_SP_UserServiceInformationPrime //////////////////////
Type
  ISUP_spUserServiceInformationPrime = record
	m_u8USInformation : Array[0..31] of Byte; // �û�ҵ����Ϣ
	m_u8USILen        : Byte;                 // ��Ϣ����
	m_u8Reserved      : Array[0..2] of Byte;  // ����
end;


// �û�����ҵ����Ϣ: ISUP_SP_UserTeleserviceInformation ///////////////////////
Type
  ISUP_spUserTeleserviceInformation = record
	m_u8Presentation : Byte;   // ��ʾ
	m_u8Interpretation : Byte; // ����
	m_u8CodingStandard : Byte; // �����׼
	m_u8ExtensionIndicator1 : Byte; // ����
	
	m_u8HighLayerCharacteristicsIdentification : Byte; // �߲�����ʶ��
	m_u8ExtensionIndicator2 : Byte; // ����

	m_u8ExtendedHighLayerCharacteristicsIdentification : Byte; // ����ĸ߲�����ʶ��
	m_u8ExtensionIndicator3 : Byte;	// ����
end;


// �û����û�ָʾ��: ISUP_SP_UserToUserIndicator //////////////////////////////
Type
  ISUP_spUserToUserIndicator = record
	m_u8Type : Byte;     // ����
	m_u8Service1 : Byte; // ҵ��
	m_u8Service2 : Byte; // ҵ��
	m_u8Service3 : Byte; // ҵ��
	m_u8NetworkDiscardIndicator : Byte; // ��������ָʾ��

	m_u8Reserved : Array[0..2] of Byte; // ����
end;


// �û����û���Ϣ: ISUP_SP_UserToUserInformation //////////////////////////////
Type
  ISUP_spUserToUserInformation = record
	m_u8UserToUserInformation : Array[0..239] of Byte;
	
	m_u8UifLen   : Byte;                // ��Ϣ����
	m_u8Reserved : Array[0..2] of Byte; // ����
end;


implementation

end.
