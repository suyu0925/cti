package DJKeygoe;

public class DJAcsISUPDef {

}


// ISUP������Ϣ����(�����Ҫֱ�ӷ��Ͳ���) /////////////////////////////////////
class XMS_ISUP_Signalling_Message     // ISUP������Ϣ
{	
	public static final int ISUP_SM_BLO = 0x13;              // ���
	
	public static final int ISUP_SM_CGB = 0x18;              // ��·Ⱥ���
	public static final int ISUP_SM_CGU = 0x19;              // ��·Ⱥ������	
	public static final int ISUP_SM_CPG = 0x2C;              // ���н�չ
	public static final int ISUP_SM_CQM = 0x2A;              // ��·Ⱥ��Ѷ
	
	public static final int ISUP_SM_GRS = 0x17;              // ��·Ⱥ��ԭ
	
	public static final int ISUP_SM_INF = 0x04;              // ��Ϣ
	public static final int ISUP_SM_INR = 0x03;              // ��Ϣ����
	
	public static final int ISUP_SM_RES = 0x0E;              // �ָ�	
	public static final int ISUP_SM_RSC = 0x12;              // ��·��ԭ
	
	public static final int ISUP_SM_SAM = 0x02;              // �����ַ
	public static final int ISUP_SM_SGM = 0x38;              // �ֶ�
	public static final int ISUP_SM_SUS = 0x0D;              // ��ͣ
	
	public static final int ISUP_SM_UBL = 0x14;              // ������	
	public static final int ISUP_SM_USR = 0x2D;               // �û����û���Ϣ
}


// ISUP��������� ///////////////////////////////////////////////////////////
class XMS_ISUP_Signalling_Parameter                     // ISUP�������
{
	public static final int ISUP_SP_AccessDeliveryInformation          = 0x2E; // ���봫����Ϣ
	public static final int ISUP_SP_AccessTransport                    = 0x03; // ���봫��
	public static final int ISUP_SP_AutomaticCongestionLevel           = 0x27; // �Զ�ӵ��
	public static final int ISUP_SP_BackwardCallIndicator              = 0x11; // �������ָʾ��
	public static final int ISUP_SP_CallDiversionInformation           = 0x36; // ����ת����Ϣ
	public static final int ISUP_SP_CallHistoryInformation             = 0x2D; // ������ʷ��Ϣ
	public static final int ISUP_SP_CallReference                      = 0x01; // ���вο�
	public static final int ISUP_SP_CalledPartNumber                   = 0x04; // �����û�����
	public static final int ISUP_SP_CallingPartNumber                  = 0x0A; // �����û�����
	public static final int ISUP_SP_CallingPartCategory                = 0x09; // �����û����
	public static final int ISUP_SP_CauseIndicator                     = 0x12; // ԭ��ָʾ��
	public static final int ISUP_SP_CircuitGroupSupervisionIndicator   = 0x15; // ��·Ⱥ������Ϣ����ָʾ��
	public static final int ISUP_SP_CircuitStateIndicator              = 0x26; // ��·״ָ̬ʾ��
	public static final int ISUP_SP_CUGInterlockCode                   = 0x1A; // �պ��û�Ⱥ�����
	public static final int ISUP_SP_ConnectedNumber                    = 0x21; // ����ĺ���
	public static final int ISUP_SP_ConnectionRequest                  = 0x0D; // ��������
	public static final int ISUP_SP_ContitnuityIndicator               = 0x10; // ��ָͨʾ��
	public static final int ISUP_SP_EchoControlInformation             = 0x37; // ���������Ϣ
	public static final int ISUP_SP_EndOptionalParameter               = 0x00; // ��ѡ����βָʾ��
	public static final int ISUP_SP_EventInformation                   = 0x24; // �¼���Ϣ
	public static final int ISUP_SP_FacilityIndicator                  = 0x18; // ����ָʾ��
	public static final int ISUP_SP_ForwardCallIndicator               = 0x07; // ǰ�����ָʾ��
	public static final int ISUP_SP_GenericDigit                       = 0x47; // ��������
	public static final int ISUP_SP_GenericNotifyIndicator             = 0x2C; // ����ָ֪ͨʾ��
	public static final int ISUP_SP_GenericNumber                      = 0x46; // ��������
	public static final int ISUP_SP_GenericReference                   = 0x42; // �����ο�
	public static final int ISUP_SP_InformationIndicator               = 0x0F; // ��Ϣָʾ��
	public static final int ISUP_SP_InformationRequestIndicator        = 0x0E; // ��Ϣ����ָʾ��
	public static final int ISUP_SP_LocationNumber                     = 0x3F; // ��λ����
	public static final int ISUP_SP_MCIDRequestIndicator               = 0x3B; // MCID����ָʾ��
	public static final int ISUP_SP_MCIDResponseIndicator              = 0x3C; // MCID��Ӧָʾ��
	public static final int ISUP_SP_MsgCompatibilityInformation        = 0x38; // ��Ϣ��������Ϣ
	public static final int ISUP_SP_MlppPrecedence                     = 0x3A; // MLPP����
	public static final int ISUP_SP_NatureOfConnectionIndicator        = 0x06; // ��������ָʾ��
	public static final int ISUP_SP_NetworkSpecificFacility            = 0x2F; // �����ض�����
	public static final int ISUP_SP_OptBackwardCallIndicator           = 0x29; // ��ѡ�������ָʾ��
	public static final int ISUP_SP_OptForwardCallIndicator            = 0x08; // ��ѡǰ�����ָʾ��
	public static final int ISUP_SP_OriginalCalledNumber               = 0x28; // ԭ���ı��к���
	public static final int ISUP_SP_OriginationISCPointCode            = 0x2B; // ʼ����ʽ�������(ISC)�ĵ���
	public static final int ISUP_SP_ParamCompatibilityInformation      = 0x39; // �����������Ϣ
	public static final int ISUP_SP_PropagationDelayCounter            = 0x31; // �����ӳټ�����
	public static final int ISUP_SP_RangeState                         = 0x16; // ��Χ��״̬
	public static final int ISUP_SP_RedirectingNumber                  = 0x0B; // �ķ�����
	public static final int ISUP_SP_RedirectionInformation             = 0x13; // �ķ���Ϣ
	public static final int ISUP_SP_RedirectionNumber                  = 0x0C; // �ķ�����
	public static final int ISUP_SP_RedirectionRestricition            = 0x40; // �ķ��������Ʋ���
	public static final int ISUP_SP_RemoteOperation                    = 0x32; // Զ�˲���
	public static final int ISUP_SP_ServiceActivation                  = 0x33; // ҵ�񼤻�
	public static final int ISUP_SP_SignalPointCode                    = 0x1E; // ��������
	public static final int ISUP_SP_SubsequentNumber                   = 0x05; // �������
	public static final int ISUP_SP_SuspendResumeIndicator             = 0x22; // ��ͣ/�ָ�ָʾ��
	public static final int ISUP_SP_TransitNetworkSelection            = 0x23; // �������ѡ��
	public static final int ISUP_SP_TransmissionMediumRequirement      = 0x02; // ����ý��Ҫ��
	public static final int ISUP_SP_TransmissionMediumRequirementPrime = 0x3E; // ����ý��Ҫ��(���)
	public static final int ISUP_SP_TransmissionMediumUsed             = 0x35; // ʹ�õĴ���ý��
	public static final int ISUP_SP_UserServiceInformation             = 0x1D; // �û�ҵ����Ϣ
	public static final int ISUP_SP_UserServiceInformationPrime        = 0x30; // �û�ҵ����Ϣ(���)
	public static final int ISUP_SP_UserTeleserviceInformation         = 0x34; // �û��ն�ҵ����Ϣ
	public static final int ISUP_SP_UserToUserIndicator                = 0x2A; // �û����û�ָʾ��
	public static final int ISUP_SP_UserToUserInformation              = 0x20; // �û����û���Ϣ
	public static final int ISUP_SP_MessageParameterAllParse           = 0xFF; // ���������в���(�255)
	public static final int ISUP_SP_MessageParameterAllRaw             = 0xFE;  // ԭʼ�����в���(�255)
}


// ISUP���������ݽṹ���� ///////////////////////////////////////////////////
// ���봫����Ϣ: ISUP_SP_AccessDeliveryInformation ////////////////////////////
class ISUP_spAccessDeliveryInformation
{
	public byte	 	m_u8AccessDeliveryID;  // ���봫��ָʾ��	
	public byte		m_u8Reserved[] = new byte[3];       // ����
}


// ���봫��: ISUP_SP_AccessTransport //////////////////////////////////////////
class ISUP_spAccessTransport
{
	public byte		m_u8AtpInformation[] = new byte[240];  // ��Ϣ��Ԫ��4.5/Q.931��������
	public byte	 	m_u8AtpLen;               // �����
	public byte	 	m_u8Reserved[] = new byte[3];          // ����
}


// �Զ�ӵ��: ISUP_SP_AutomaticCongestionLevel ///////////////////////////////
class ISUP_spAutomaticCongestionLevel
{	
	public byte		m_u8CongestionLevelExceeded;     // ӵ����ĳ������
	public byte		m_u8Reserved[] = new byte[3];                 // ����
}


// �������ָʾ��: ISUP_SP_BackwardCallIndicator //////////////////////////////
class ISUP_spBackwardCallIndicator
{	
	public byte		 m_u8ChargeIndicator;             // �Ʒ�ָʾ��
	public byte		 m_u8CalledStatusIndicator;       // �����û�״ָ̬ʾ��
	public byte		 m_u8CalledCategoryIndicator;     // �����û����ָʾ��
	public byte		 m_u8EndToEndMethodIndicator;     // �˵��˷���ָʾ��
	
	public byte		 m_u8InterworkingIndicator;       // ��ָͨʾ��
	public byte		 m_u8EndToEndInformationIndicator;// �˵�����Ϣָʾ��
	public byte		 m_u8ISDNUserPartIndicator;       // ISDN�û�����ָʾ��
	public byte		 m_u8HoldingIndicator;            // ����ָʾ��
	public byte		 m_u8ISDNAccessIndicator;         // ISDN����ָʾ��
	public byte		 m_u8EchoControlDeviceIndicator;  // ������������ָʾ��
	public byte		 m_u8SCCPMethodIndicator;         // SCCP����ָʾ��
	public byte		 m_u8Reserved;                    // ����
}


// ����ת����Ϣ: ISUP_SP_CallDiversionInformation /////////////////////////////
class ISUP_spCallDiversionInformation
{	
	public byte		 m_u8NotificationSubscriptionOptions; // ֪ͨ�Ǽ���ѡ
	public byte		 m_u8RedirectingReason;               // �ķ�ԭ��
	public byte		 m_u8Reserved[] = new byte[2];                     // ����
}


// ������ʷ��Ϣ: ISUP_SP_CallHistoryInformation ///////////////////////////////
class ISUP_spCallHistoryInformation
{	
	public short	 m_u16PropagationDelayValue; // ����ʱ��ֵ
	public byte		 m_u8Reserved[] = new byte[2];            // ����
}


// ���вο�: ISUP_SP_CallReference ////////////////////////////////////////////
class ISUP_spCallReference
{	
	public int		  m_u32CallIdentity; // ����ʶ��
	public int		  m_u32SPcode;       // ����
	public byte		  m_u8Reserved[] = new byte[4];   // ����
}

// �����û�����: ISUP_SP_CalledPartNumber /////////////////////////////////////
class ISUP_spCalledPartNumber
{
	public byte		 m_u8NatureOfAddressIndicator;  // ��ַ����ָʾ��
	public byte		 m_u8OddEvenIndicator;          // ��żָʾ��
	public byte		 m_u8NumberingPlanIndicator;    // ����ƻ�ָʾ
	public byte		 m_u8InternalNetworkNumberIndicator;// �ڲ��������ָʾ��
	public byte		 m_u8Reserved[] 	 = new byte[4];               // ����
	public byte		 m_s8AddressSignal[] = new byte[40];         // ��ַ�ź�	
}


// �����û�����: ISUP_SP_CallingPartNumber ////////////////////////////////////
class ISUP_spCallingPartNumber
{	
	public byte		 m_u8NatureOfAddressIndicator; // ��ַ����ָʾ��
	public byte		 m_u8OddEvenIndicator;         // ��żָʾ��
	public byte		 m_u8Screening;                // ����
	public byte		 m_u8AddressPresentationRestrictedIndicator;  // ��ַ��ʾָʾ
	public byte		 m_u8NumberingPlanIndicator;   // ����ƻ�ָʾ
	public byte		 m_u8NumberIncompleteIndicator;// ���к��벻ȫָʾ	
	public byte		 m_s8AddressSignal[] = new byte[40]; // ��ַ�ź�
	public byte		 m_u8Reserved	  [] = new byte[2];       // ����
}

// �����û����: ISUP_SP_CallingPartCategory //////////////////////////////////
class ISUP_spCallingPartCategory
{	
	public byte		 m_u8CallingPartyCategory; // �����û����
	public byte		 m_u8Reserved[] = new byte[3];          // ����
}

// ԭ��ָʾ��: ISUP_SP_CauseIndicator /////////////////////////////////////////
class ISUP_spCauseIndicator
{	
	public byte		 m_u8Location;             // ��λ
	public byte		 m_u8CodindStandard;       // �����׼
	public byte		 m_u8ExtensionIndicator1;  // ����
	public byte		 m_u8CauseValue;           // ԭ��ֵ
	public byte		 m_u8ExtensionIndicator2;  // ����
	public byte		 m_u8Reserved[] = new byte[2];          // ����
	public byte		 m_u8Diagnose[] = new byte[32];         // ���	
	public byte		 m_u8DiagnoseLen;          // ��ϳ���
}


// ��·Ⱥ������Ϣ����ָʾ��: ISUP_SP_CircuitGroupSupervisionIndicator /////////
class ISUP_spCircuitGroupSupervisionIndicator
{
	public byte		 m_u8CircuitGroupSupervisionIndicator; // ����ָʾ��
	public byte		 m_u8Reserved[] = new byte[3]; // ����
}

// ��·״ָ̬ʾ��: ISUP_SP_CircuitStateIndicator //////////////////////////////
class ISUP_spCircuitStateIndicator
{	
	public byte		 m_u8CircuitStateIndicator[] = new byte[32];
}

// �պ��û�Ⱥ�����: ISUP_SP_CUGInterlockCode /////////////////////////////////
class ISUP_spCUGInterlockCode
{	
	public byte		  m_u8NIDigit1;  // ��1��NI����
	public byte		  m_u8NIDigit2;  // ��2��NI����
	public byte		  m_u8NIDigit3;  // ��3��NI����
	public byte		  m_u8NIDigit4;  // ��4��NI����	
	public short	  m_u16BinaryCode; // ��������
	public byte		  m_u8Reserved[] = new byte[2]; // ����
}

// ����ĺ���: ISUP_SP_ConnectedNumber ////////////////////////////////////////
class ISUP_spConnectedNumber
{	
	public byte		 m_u8NatureOfAddressIndicator; // ��ַ����ָʾ��
	public byte		 m_u8OddEvenIndicator;         // ��żָʾ��
	public byte		 m_u8ScreeningIndicator;       // ����ָʾ��
	public byte		 m_u8AddressPresentationRestrictedIndicator; // ��ַ��ʾ����
	public byte		 m_u8NumberingPlanIndicator;   // ����ƻ�ָʾ	
	public byte		 m_u8Reserved	  [] = new byte[3];              // ����
	public byte		 m_s8AddressSignal[] = new byte[40];        // ��ַ�ź�	
}


// ��������: ISUP_SP_ConnectionRequest ////////////////////////////////////////
class ISUP_spConnectionRequest
{	
	public int		 m_u32LocalReference; // ����ʶ��
	public int		 m_u32SPcode;         // ����
	public byte		 m_u8ProtocolClass;   // Э�����
	public byte		 m_u8Credit;          // �ź���
	public byte		 m_u8Reserved[] = new byte[2];     // ����
}

// ��ָͨʾ��: ISUP_SP_ContitnuityIndicator ///////////////////////////////////
class ISUP_spContitnuityIndicator
{	
	public byte		 m_u8ContinuityIndicator; // ��ָͨʾ��
	public byte		 m_u8Reserved[] = new byte[3]; // ����
}


// ���������Ϣ: ISUP_SP_EchoControlInformation ///////////////////////////////
class ISUP_spEchoControlInformation
{	
	public byte		 m_u8OutEchoControlInformationIndicator; // ȥ������������Ӧָʾ
	public byte		 m_u8InEchoControlInformationIndicator;  // ��������������Ӧָʾ
	public byte		 m_u8OutEchoControlRequestIndicator;     // ȥ��������������ָʾ
	public byte		 m_u8InEchoControlRequestIndicator;      // ����������������ָʾ
}

// �¼���Ϣ: ISUP_SP_EventInformation /////////////////////////////////////////
class ISUP_spEventInformation
{
	public byte		 m_u8EventIndicator; // �¼�ָʾ��
	public byte		 m_u8EventPresentationRestrictedIndicator;// �¼���ʾ����ָʾ��	
	public byte		 m_u8Reserved[] = new byte[2]; // ����
}

// ����ָʾ��: ISUP_SP_FacilityIndicator //////////////////////////////////////
class ISUP_spFacilityIndicator
{	
	public byte		 m_u8FacilityIndicator; // ����ָʾ��
	public byte		 m_u8Reserved[] = new byte[3];
}

// ǰ�����ָʾ��: ISUP_SP_ForwardCallIndicator ///////////////////////////////
class ISUP_spForwardCallIndicator
{	
	public byte		 m_u8NationalInternatoinalIndicator; // ����/��ʺ���ָʾ��
	public byte		 m_u8EndToEndMethodIndicator;        // �˵��˷���ָʾ��
	public byte		 m_u8InterworkingIndicator;          // ��ָͨʾ��
	public byte		 m_u8EndToEndInformationIndicator;   // �˵�����Ϣָʾ��
	public byte		 m_u8ISDNUserPartIndicator;          // ISDN�û�����ָʾ��
	public byte		 m_u8ISDNUserPartPreferenceIndicator;// ISDN�û���������ָʾ��
	public byte		 m_u8ISDNAccessIndicator; // ISDN����ָʾ��
	public byte		 m_u8SCCPMethodIndicator; // SCCP����ָʾ��
	public byte		 m_u8Reserved[] = new byte[4];         // ����
}


// ��������: ISUP_SP_GenericDigit /////////////////////////////////////////////
class ISUP_spGenericDigit
{	
	public byte		 m_u8TypeOfDigit;   // ��������
	public byte		 m_u8EncodingScheme;// ����ƻ�	
	public byte		 m_u8Digit[] = new byte[32];     // ����
	public byte		 m_u8DigitLen;      // ���ֳ���
	public byte		 m_u8Reserved;      // ����
}


// ����ָ֪ͨʾ��: ISUP_SP_GenericNotifyIndicator /////////////////////////////
class ISUP_spGenericNotifyIndicator
{
	public byte		 m_u8NotificationIndicator; // ָ֪ͨʾ��
	public byte		 m_u8ExtensionIndicator;    // ����ָʾ��
	public byte		 m_u8Reserved[] = new byte[2];           // ����
}

// ��������: ISUP_SP_GenericNumber ////////////////////////////////////////////
class ISUP_spGenericNumber
{	
	public byte		 m_u8NumberQualifierIndicator;    // �����޶�ָʾ��
	public byte		 m_u8NatureOfAddressIndicator;// ��ַ����ָʾ��
	public byte		 m_u8OddEvenIndicator;  // ��żָʾ��	
	public byte		 m_u8ScreeningIndicator;// ����
	public byte		 m_u8AddressPresentationRestrictedIndicator; // ��ʾָʾ
	public byte		 m_u8NumberingPlanIndicator;    // ����ƻ�ָʾ
	public byte		 m_u8NumberIncompleteIndicator; //	���벻ȫָʾ	
	public byte		 m_s8AddressSignal[] = new byte[40]; // ��ַ�ź�
	public byte		 m_u8Reserved;          // ����
}


// �����ο�: ISUP_SP_GenericReference /////////////////////////////////////////
class ISUP_spGenericReference  
{
	public byte		 m_u8ReferenceRestrictedIndicator; // �ο��޶�ָʾ��
	public byte		 m_u8ReferenceLength;  // �ο�����		
	public byte		 m_u8ReferenceCode[] = new byte[4]; // �ο���λ����Ϣ
	public byte		 m_u8Reserved[] = new byte[2];      // ����
}

// ��Ϣָʾ��: ISUP_SP_InformationIndicator ///////////////////////////////////
class ISUP_spInformationIndicator
{	
	public byte		 m_u8CallingPartyAddressResponseIndicator; // �����û���ַ��Ӧָʾ��
	public byte		 m_u8HoldProvidedIndicator; // �����ṩָʾ��
	
	public byte		 m_u8CallingPartyCategoryResponseIndicator; // �����û������Ӧָʾ��
	public byte		 m_u8ChargeInformationResponseIndicator;  // �Ʒ���Ϣ��Ӧָʾ��
	public byte		 m_u8SolicitedInformationIndicator;  // ������Ϣָʾ��
	
	public byte		 m_u8Reserved[] = new byte[3]; // ����
}

// ��Ϣ��ʾָʾ��: ISUP_SP_InformationRequestIndicator ////////////////////////
class ISUP_spInformationRequestIndicator
{	
	public byte		 m_u8CallingPartyAddressRequestIndicator; // �����û���ַ����ָʾ��
	public byte		 m_u8HoldingIndicator; // ����ָʾ��
	
	public byte		 m_u8CallingPartyCategoryRequestIndicator;// �����û��������ָʾ��
	public byte		 m_u8ChargeInformationRequestIndicator;   // �Ʒ���Ϣ����ָʾ��
	
	public byte		 m_u8MaliciousCallIdentificationRequestIndicator; // �������ʶ��
	public byte		 m_u8Reserved[] = new byte[3];  // ����
}

// ��λ����: ISUP_SP_LocationNumber ///////////////////////////////////////////
class ISUP_spLocationNumber
{	
	public byte		 m_u8NatureOfAddressIndicator; // ��ַ����ָʾ��
	public byte		 m_u8OddEvenIndicator;         // ��żָʾ��

	public byte		 m_u8ScreeningIndicator;       // ����ָʾ��
	public byte		 m_u8AddressPresentationRestrictedIndicator; // ��ַ��ʾ����ָʾ��
	public byte		 m_u8NumberingPlanIndicator;   // ����ƻ�ָʾ��
	public byte		 m_u8InternalNetworkNumberIndicator; // �ڲ��������ָʾ��	
	
	public byte		 m_s8AddressSignal[] = new byte[40]; // ��ַ�ź�

	public byte		 m_u8Reserved[] = new byte[2]; // ����
}

// MCID����ָʾ��: ISUP_SP_MCIDRequestIndicator ///////////////////////////////
class ISUP_spMCIDRequestIndicator
{	
	public byte		 m_u8MCIDRequestIndicator; // MCID����ָʾ��
	public byte		 m_u8HoldingIndicator;     // ����ָʾ��
	public byte		 m_u8Reserved[] = new byte[2]; // ����
}


// MCID ��Ӧָʾ��: ISUP_SP_MCIDResponseIndicator /////////////////////////////
class ISUP_spMCIDResponseIndicator
{	
	public byte		 m_u8MCIDResponseIndicator; // MCID��Ӧָʾ��
	public byte		 m_u8HoldProvidedIndicator; // �����ṩָʾ��
	public byte		 m_u8Reserved[] = new byte[2]; // ����
}

// ��Ϣ��������Ϣ: ISUP_SP_MsgCompatibilityInformation ////////////////////////
class ISUP_spMsgCompatibilityInformation
{	
	public byte		 m_u8TransitAtIntermediateExchangeIndicator1;// ���м佻���ֻ��ָʾ��
	public byte		 m_u8ReleaseCallIndicator1;      // �ͷź���ָʾ��
	public byte		 m_u8SendNotificationIndicator1; // ����ָ֪ͨʾ��
	public byte		 m_u8DiscardMessageIndicator1;   // ������Ϣָʾ��
	public byte		 m_u8PassOnNotPossibleIndicator1;// ͨ�����ָʾ��
	public byte		 m_u8ExtensionIndicator1;        // ����ָʾ��
	public byte		 m_u8Reserved1[] = new byte[2];               // ����
	
	public byte		 m_u8TransitAtIntermediateExchangeIndicator2;// ���м佻���ֻ��ָʾ��
	public byte		 m_u8ReleaseCallIndicator2;      // �ͷź���ָʾ��
	public byte		 m_u8SendNotificationIndicator2; // ����ָ֪ͨʾ��
	public byte		 m_u8DiscardMessageIndicator2;   // ������Ϣָʾ��
	public byte		 m_u8PassOnNotPossibleIndicator2;// ͨ�����ָʾ��
	public byte		 m_u8ExtensionIndicator2;        // ����ָʾ��
	public byte		 m_u8Reserved2[] = new byte[2];               // ����
}

// MLPP����: ISUP_SP_MlppPrecedence ///////////////////////////////////////////
class ISUP_spMlppPrecedence
{	
	public byte		  m_u8PrecedenceLevel;  // ���ȼ�	
	public byte		  m_u8LFB;        // LFB
	public byte		  m_u8Reserved[] = new byte[2];// ����
	public byte		  m_u8NIDigit1;  // ��1��NI����
	public byte		  m_u8NIDigit2;  // ��2��NI����
	public byte		  m_u8NIDigit3;  // ��3��NI����
	public byte		  m_u8NIDigit4;  // ��4��NI����	
	public int		 m_u32MLPPServiceDomain;
}

// ��������ָʾ��: ISUP_SP_NatureOfConnectionIndicator ////////////////////////
class ISUP_spNatureOfConnectionIndicator
{	
	public byte		 m_u8SatelliteIndicator;        // ����ָʾ��
	public byte		 m_u8ContinuityCheckIndicator;  // ��ͨ����ָʾ��
	public byte		 m_u8EchoControlDeviceIndicator;// �����������ָʾ��
	public byte		 m_u8Reserved;
}

// �����ض�����: ISUP_SP_NetworkSpecificFacility //////////////////////////////
class ISUP_spNetworkSpecificFacility
{	
	public byte		 m_u8NsfInformation[] = new byte[32];  // ������Ϣ
	public byte		 m_u8NsfLen;              // �����
	public byte		 m_u8Reserved[] = new byte[3];         // ����	
}


// ��ѡ�������ָʾ��: ISUP_SP_OptBackwardCallIndicator ///////////////////////
class ISUP_spOptBackwardCallIndicator
{	
	public byte		 m_u8InBandInformationIndicator;    // ������Ϣָʾ��
	public byte		 m_u8CallTransferPossibleIndicator; // ����ת�ƿ��ܷ���ָʾ��
	public byte		 m_u8SimpleSegmentationIndicator;   // �򵥷ֶ�ָʾ��
	public byte		 m_u8MLPPUserIndicator;             // MLPP�û�ָʾ��
	public byte		 m_u8Reserved[] = new byte[4];
}


// ��ѡǰ�����ָʾ��: ISUP_SP_OptForwardCallIndicator ////////////////////////
class ISUP_spOptForwardCallIndicator
{		
	public byte		 m_u8ClosedUserGroupCallIndicator; // CUG����ָʾ��
	public byte		 m_u8SimpleSegmentationIndicator;  // �򵥷ֶ�ָʾ��
	public byte		 m_u8UserIdentityRequestIndicator; // ������û�ʶ������ָʾ��
	public byte		 m_u8Reserved;                     // ����
}

// ԭ���к���: ISUP_SP_OriginalCalledNumber ///////////////////////////////////
class ISUP_spOriginalCalledNumber
{	
	public byte		 m_u8NatureOfAddressIndicator; // ��ַ����ָʾ��
	public byte		 m_u8OddEvenIndicator;         // ��żָʾ��
	public byte		 m_u8AddressPresentationRestrictedIndicator; // ��ʾָʾ
	public byte		 m_u8NumberingPlanIndicator; // ����ƻ�ָʾ
	public byte		 m_s8AddressSignal[] = new byte[40]; // ��ַ�ź�
	public byte		 m_u8Reserved[] = new byte[4];  // ����
}


// ʼ����ʽ�������(ISC)�ĵ���: ISUP_SP_OriginationISCPointCode ///////////////
class ISUP_spOriginationISCPointCode
{
	public int		 m_u32SPcode;     // ����
	public byte		 m_u8Reserved[] = new byte[4]; // ����
}

// �����������Ϣ: ISUP_SP_ParamCompatibilityInformation //////////////////////
class ISUP_spParamCompatibilityInformation
{
	public byte		 m_u8UpgradedParameter1;         // ��һ��������	
	public byte		 m_u8TransitAtIntermediateExchangeIndicator1;// ���м佻���ֻ��ָʾ��
	public byte		 m_u8ReleaseCallIndicator1;      // �ͷź���ָʾ��
	public byte		 m_u8SendNotificationIndicator1; // ����ָ֪ͨʾ��
	public byte		 m_u8DiscardMessageIndicator1;   // ������Ϣָʾ��
	public byte		 m_u8DiscardParameterIndicator1; // �������ָʾ��
	public byte		 m_u8ExtensionIndicator1;        // ����ָʾ��
	public byte		 m_u8Reserved1;                  // ����
	
	public byte		 m_u8UpgradedParameter2;         // �ڶ���������	
	public byte		 m_u8TransitAtIntermediateExchangeIndicator2;// ���м佻���ֻ��ָʾ��
	public byte		 m_u8ReleaseCallIndicator2;      // �ͷź���ָʾ��
	public byte		 m_u8SendNotificationIndicator2; // ����ָ֪ͨʾ��
	public byte		 m_u8DiscardMessageIndicator2;   // ������Ϣָʾ��
	public byte		 m_u8DiscardParameterIndicator2; // �������ָʾ��
	public byte		 m_u8ExtensionIndicator2;        // ����ָʾ��
	public byte		 m_u8Reserved2;                  // ����

	public byte		 m_u8UpgradedParameter3;         // �����������	
	public byte		 m_u8TransitAtIntermediateExchangeIndicator3;// ���м佻���ֻ��ָʾ��
	public byte		 m_u8ReleaseCallIndicator3;      // �ͷź���ָʾ��
	public byte		 m_u8SendNotificationIndicator3; // ����ָ֪ͨʾ��
	public byte		 m_u8DiscardMessageIndicator3;   // ������Ϣָʾ��
	public byte		 m_u8DiscardParameterIndicator3; // �������ָʾ��
	public byte		 m_u8ExtensionIndicator3;        // ����ָʾ��
	public byte		 m_u8Reserved3;                  // ����
}

// ������ʱ������: ISUP_SP_PropagationDelayCounter ////////////////////////////
class ISUP_spPropagationDelayCounter
{	
	public short	 m_u16PropagationDelayValue;  // ����ʱ��ֵ
	public byte		 m_u8Reserved[] = new byte[2]; // ����
}

// ��Χ��״̬: ISUP_SP_RangeState /////////////////////////////////////////////
class ISUP_spRangeState
{
	public byte		 m_u8Range;      // ��Χ
	public byte		 m_u8Reserved[] = new byte[3];// ����
	public int		 m_u32Status;    // ״̬
}

// �ķ�����: ISUP_SP_RedirectingNumber ////////////////////////////////////////
class ISUP_spRedirectingNumber
{	
	public byte		 m_u8NatureOfAddressIndicator; // ��ַ����ָʾ��
	public byte		 m_u8OddEvenIndicator; // ��żָʾ��	 
	public byte		 m_u8AddressPresentationRestrictedIndicator; // ��ʾ����ָʾ��
	public byte		 m_u8NumberingPlanIndicator; // ����ƻ�ָʾ��	
	public byte		 m_s8AddressSignal[] = new byte[40]; // ��ַ�ź�
	public byte		 m_u8Reserved[] = new byte[4];  // ����
}

// �ķ���Ϣ: ISUP_SP_RedirectionInformation ///////////////////////////////////
class ISUP_spRedirectionInformation
{
	public byte		 m_u8RedirectingIndicator; // �ķ�ָʾ��
	public byte		 m_u8OriginalRedirectionReason; // ԭ��ĸķ�ԭ��
	public byte		 m_u8RedirectionCounter;   // �ķ�������
	public byte		 m_u8RedirectingReason;    // �ķ�ԭ��
	public byte		 m_u8Reserved[] = new byte[4]; // ����	
}

// �ķ�����: ISUP_SP_RedirectionNumber ////////////////////////////////////////
class ISUP_spRedirectionNumber
{	
	public byte		 m_u8NatureOfAddressIndicator; // ��ַ����ָʾ��
	public byte		 m_u8OddEvenIndicator;         // ��żָʾ��
	public byte		 m_u8NumberingPlanIndicator;   // ����ƻ�ָʾ��
	public byte		 m_u8InternalNetworkNumberIndicator; // �ڲ��������ָʾ��
	public byte		 m_s8AddressSignal[] = new byte[40];            // ��ַ�ź�
	public byte		 m_u8Reserved[] = new byte[4]; // ����
}


// �ķ��������Ʋ���: ISUP_SP_RedirectionRestricition //////////////////////////
class ISUP_spRedirectionRestricition
{	
	public byte		 m_u8PresentationRestrictedIndicator; // ��ʾ����ָʾ��
	public byte		 m_u8Reserved[] = new byte[3];
}


// Զ�˲���: ISUP_SP_RemoteOperation //////////////////////////////////////////
class ISUP_spRemoteOperation
{	
	public byte		 m_u8ProtocolProfile;    // Э������    
	public byte		 m_u8ExtensionIndicator; // ����	
	public byte		 m_u8Component[] = new byte[240];
	public byte		 m_u8ComponentLen;
	public byte		 m_u8Reserved;          // ����
}


// ҵ�񼤻�: ISUP_SP_ServiceActivation ////////////////////////////////////////
class ISUP_spServiceActivation
{
	public byte		 m_u32FeatureCode[] = new byte[32];  // ������
	public byte		 m_u8FCLen;             // �����볤��
	public byte		 m_u8Reserved[] = new byte[3];       // ����	
}


// ��������: ISUP_SP_SignalPointCode ////////////////////////////////////////
class ISUP_spSignalPointCode
{	
	public int		 m_u32SPcode;     // ����	
	public byte		 m_u8Reserved[] = new byte[4]; // ����	
}


// �������: ISUP_SP_SubsequentNumber /////////////////////////////////////////
class ISUP_spSubsequentNumber
{		
	public byte		 m_u8OddEvenIndicator; // ��żָʾ��
	public byte		 m_u8Reserved[] = new byte[3];      // ����
	public byte		 m_s8AddressSignal[] = new byte[40];    // ��ַ�ź�
}

// ��ͣ�ָ�ָʾ: ISUP_SP_SuspendResumeIndicator ///////////////////////////////
class ISUP_spSuspendResumeIndicator
{	
	public byte		 m_u8SuspendResumeIndicator; // ��ͣ/�ָ�ָʾ��
	public byte		 m_u8Reserved[] = new byte[3]; // ����	
}

// �������ѡ��: ISUP_SP_TransitNetworkSelection //////////////////////////////
class ISUP_spTransitNetworkSelection
{	
	public byte		 m_u8NetworkIdentificationPlan;   // ����ʶ��ƻ�
	public byte		 m_u8TypeOfNetworkIdentification; // ����ʶ������
	public byte		 m_u8OddEvenIndicator;            // ��żָʾ��
	public byte		 m_u8Reserved;                    // ����
	
	public byte		 m_u8NetworkIdentification[] = new byte[32];   // ����ʶ��
	
	public byte		 m_u8NetIdLen;                    // ����ʶ�𳤶�
	public byte		 m_u8Rev[] = new byte[3];                      // ����	
}

// ����ý��Ҫ��: ISUP_SP_TransmissionMediumRequirement ////////////////////////
class ISUP_spTransmissionMediumRequirement
{	
	public byte		 m_u8TransmissionMediumRequirement; // ����ý��Ҫ��
	public byte		 m_u8Reserved[] = new byte[3]; // ����	
}

// ����ý��Ҫ��(��): ISUP_SP_TransmissionMediumRequirementPrime /////////////
class ISUP_spTransmissionMediumRequirementPrime
{	
	public byte		 m_u8TransmissionMediumRequirement; // ����ý��Ҫ��
	public byte		 m_u8Reserved[] = new byte[3]; // ����
}


// ʹ���еĴ���ý��: ISUP_SP_TransmissionMediumUsed ///////////////////////////
class ISUP_spTransmissionMediumUsed
{	
	public byte		 m_u8TransmissionMediumRequirement; // ����ý��Ҫ��
	public byte		 m_u8Reserved[] = new byte[3]; // ����
}


// �û�ҵ����Ϣ: ISUP_SP_UserServiceInformation ///////////////////////////////
class ISUP_spUserServiceInformation
{
	public byte		 m_u8USInformation[] = new byte[32]; // �û�ҵ����Ϣ
	
	public byte		 m_u8USILen;            // ��Ϣ����
	public byte		 m_u8Reserved[] = new byte[3];       // ����	
}


// ���û�ҵ����Ϣ: ISUP_SP_UserServiceInformationPrime //////////////////////
class ISUP_spUserServiceInformationPrime
{
	public byte		 m_u8USInformation[] = new byte[32]; // �û�ҵ����Ϣ
	public byte		 m_u8USILen;            // ��Ϣ����
	public byte		 m_u8Reserved[] = new byte[3];       // ����	
}


// �û�����ҵ����Ϣ: ISUP_SP_UserTeleserviceInformation ///////////////////////
class ISUP_spUserTeleserviceInformation
{	
	public byte		 m_u8Presentation;   // ��ʾ
	public byte		 m_u8Interpretation; // ����
	public byte		 m_u8CodingStandard; // �����׼
	public byte		 m_u8ExtensionIndicator1; // ����
	
	public byte		 m_u8HighLayerCharacteristicsIdentification; // �߲�����ʶ��
	public byte		 m_u8ExtensionIndicator2; // ����

	public byte		 m_u8ExtendedHighLayerCharacteristicsIdentification; // ����ĸ߲�����ʶ��
	public byte		 m_u8ExtensionIndicator3;	// ����
}


// �û����û�ָʾ��: ISUP_SP_UserToUserIndicator //////////////////////////////
class ISUP_spUserToUserIndicator
{	
	public byte		 m_u8Type;     // ����
	public byte		 m_u8Service1; // ҵ��
	public byte		 m_u8Service2; // ҵ��
	public byte		 m_u8Service3; // ҵ��
	public byte		 m_u8NetworkDiscardIndicator; // ��������ָʾ��
	public byte		 m_u8Reserved[] = new byte[3]; // ����
}


// �û����û���Ϣ: ISUP_SP_UserToUserInformation //////////////////////////////
class ISUP_spUserToUserInformation
{	
	public byte		 m_u8UserToUserInformation[] = new byte[240];
	public byte		 m_u8UifLen;      // ��Ϣ����
	public byte		 m_u8Reserved[] = new byte[3]; // ����
}
