package DJKeygoe;

public class DJAcsTUPDef {

}


// TUP������Ϣ����(�����Ҫֱ�ӷ��Ͳ���) //////////////////////////////////////
class XMS_TUP_Signalling_Message     // TUP������Ϣ
{	  
	public static final int TUP_SM_SAM = 0x31;              // �����ַ�ź�
	public static final int TUP_SM_SAO = 0x41;              // ����һ����ַ�ĺ����ַ�ź�
    
	public static final int TUP_SM_GSM = 0x12;              // һ��ǰ������Ϣ�ź�
	public static final int TUP_SM_GRQ = 0x13;              // һ�������ź�
    
	public static final int TUP_SM_BLO = 0x27;              // �����ź�
	public static final int TUP_SM_UBL = 0x47;              // �������ź�
	public static final int TUP_SM_RSC = 0x77;              // ��·��ԭ�ź�
    
	public static final int TUP_SM_MGB = 0x18;              // ����ά����Ⱥ�����ź�
	public static final int TUP_SM_MGU = 0x38;              // ����ά����Ⱥ�������ź�
	public static final int TUP_SM_HGB = 0x58;              // ����Ӳ�����ϵ�Ⱥ�����ź�
	public static final int TUP_SM_HGU = 0x78;              // ����Ӳ�����ϵ�Ⱥ�������ź�
	public static final int TUP_SM_GRS = 0x98;              // ��·Ⱥ��ԭ�ź�
	public static final int TUP_SM_SGB = 0xB8;              // ��������Ⱥ�����ź�
	public static final int TUP_SM_SGU = 0xD8;              // ��������Ⱥ���������ź�
}


// TUP��������� ////////////////////////////////////////////////////////////
class XMS_TUP_Signalling_Parameter                   // TUP�������
{	
	public static final int TUP_SP_AccMessageIndicator        = 0x0C;       // ACC��Ϣָʾ��
	public static final int TUP_SP_AcmMessageIndicator        = 0x09;       // ACM��Ϣָʾ��
	public static final int TUP_SP_CalledPartAddress          = 0x0F;       // �����û�����
	public static final int TUP_SP_CallingLineAddress         = 0x02;       // �����û�����
	public static final int TUP_SP_CallingPartyCategory       = 0x01;       // �����û����
	public static final int TUP_SP_ConnectionNatureIndicator  = 0x0D;       // ��������ָʾ��
	public static final int TUP_SP_EumOctetIndicator          = 0x0A;       // EUM��Ϣ��λ��
	public static final int TUP_SP_EumSignallingPointCode     = 0x0B;       // EUM��Ϣ�����
	public static final int TUP_SP_ForwardCallInformation     = 0x0E;       // ǰ�������Ϣ
	public static final int TUP_SP_GrqRequestTypeIndicator    = 0x08;       // GRQ����ָʾ��
	public static final int TUP_SP_GsmResponseTypeIndicator   = 0x06;       // GSM��Ӧָʾ��
	public static final int TUP_SP_IaiFirstIndicator          = 0x05;       // IAI��һ��ʾ��
	public static final int TUP_SP_OriginalCalledAddress      = 0x03;       // ԭ�����û�����
	public static final int TUP_SP_RangeStatus                = 0x04;       // ��Χ��״̬
	public static final int TUP_SP_SubsequentAddress          = 0x10;       // �����ַ
}


// TUP���������ݽṹ���� ////////////////////////////////////////////////////
// ACC��Ϣָʾ��: TUP_SP_AccMessageIndicator //////////////////////////////////
// ����: ACC
class TUP_spAccMessageIndicator
{
	public byte 	 m_u8ACCInformation; // ACC��Ϣ
	public byte 	 m_u8Reserved[] = new byte[3]; // ����
}


// ACM��Ϣָʾ��: TUP_SP_AcmMessageIndicator //////////////////////////////////
// ����: ACM
class TUP_spAcmMessageIndicator
{
	public byte 	 m_u8TypeOfACMIndicator; // ��ַȫ�ź����ͱ�ʾ��
	public byte 	 m_u8SubscriberFreeIndicator; // �û��б�ʾ��
	public byte 	 m_u8IncomingEchoSuppressorIndicator; // ����������������ʾ��
	public byte 	 m_u8CallForwardingIndicator; // ����ת�Ʊ�ʾ��
	public byte 	 m_u8SignallingPathIndicator; // �ź�ͨ����ʾ��
	public byte 	 m_u8Reserved[] = new byte[3]; // ����
}


// �����û�����: TUP_SP_CalledPartAddress /////////////////////////////////////
// ����: IAM/IAI
class TUP_spCalledPartAddress
{
	public byte 	 m_u8NatureOfAddressIndicator; // ��ַ���ʱ�ʾ��
	public byte 	 m_u8NumberOfAddressSignal; // ��ַ�źŵ�����
	public byte 	 m_u8Reserved[] = new byte[2]; // ����	
	public byte 	 m_s8AddressSignal[] = new byte[40]; // ��ַ�ź�
}


// �����û�����: TUP_SP_CallingLineAddress ////////////////////////////////////
// ����: IAI/GSM
class TUP_spCallingLineAddress
{
	public byte 	 m_u8NatureOfAddressIndicator; // ��ַ���ʱ�ʾ��
	public byte 	 m_u8PresentationIndicator; // �ṩ�����û��߱�ʶ��ʾ��
	public byte 	 m_u8IncompleteIndicator; // �����û��߱�ʶ��ȫ��ʾ��
	public byte 	 m_u8NumberOfAddressSignal; // ���е�ַ�źŵ�����
	public byte 	 m_s8AddressSignal[] = new byte[40]; // ��ַ�ź�
}


// �����û����: TUP_SP_CallingPartyCategory //////////////////////////////////
// ����: IAM/IAI/GSM
class TUP_spCallingPartyCategory
{
	public byte 	 m_u8CallingPartyCategory;  // �����û����
	public byte 	 m_u8Reserved[] = new byte[3]; // ����
}


// ��������ָʾ��: TUP_SP_ConnectionNatureIndicator ///////////////////////////
// ����: IAM/IAI
class TUP_spConnectionNatureIndicator
{	
	public byte 	 m_u8NatureOfCircuitIndicator; // ��·���ʱ�ʾ��
	public byte 	 m_u8ContinuityCheckIndicator; // ��ͨ�����ʾ��
	public byte 	 m_u8EchoSuppressorIndicator;  // ȥ��������������ʾ��
	public byte 	 m_u8Reserved;
}


// EUM��Ϣ��λ��: TUP_SP_EumOctetIndicator ////////////////////////////////////
// ����: EUM
class TUP_spEumOctetIndicator
{
	public byte 	 m_u8UnsuccessfulIndicator; // ���ɹ���ʾ��
	public byte 	 m_u8Reserved[] = new byte[3]; // ����
}


// EUM��Ϣ�����: TUP_SP_EumSignallingPointCode ///////////////////////////////
// ����: EUM
class TUP_spEumSignallingPointCode
{
	public int	 	 m_u32SPC; // ��������
}


// ǰ�������Ϣ: TUP_SP_ForwardCallInformation ////////////////////////////////
// ����: IAM/IAI
class TUP_spForwardCallInformation
{
	public byte 	 m_u8InternationalCallIndicator; // ����������б�ʾ��
	
	public byte 	 m_u8RedirectedCallIndicator; // �ķ����б�ʾ��
	public byte 	 m_u8AllDigitalPathRequiredIndicator; // ��Ҫȫ��������ͨ·��ʾ��
	public byte 	 m_u8SignallingPathIndicator; // �ź�ͨ����ʾ��
}


// GRQ����ָʾ��: TUP_SP_GrqRequestTypeIndicator //////////////////////////////
// ����: GRQ
class TUP_spGrqRequestTypeIndicator
{
	public byte 	 m_u8CallingPartyCategoryRequestIndicator; // �����û���������ʾ��
	public byte 	 m_u8CallingLineIdentityRequestIndicator; // �����û��߱�ʶ�����ʾ��
	public byte 	 m_u8OriginalCalledAddressRequestIndicator; // ԭ���е�ַ�����ʾ��
	public byte 	 m_u8MaliciousCallIdentificationIndicator; // �������ʶ�������ʾ��
	public byte 	 m_u8HoldRequestIndicator; // ���������ʾ��
	public byte 	 m_u8EchoSuppressorRequestIndicator; // ���������������ʾ��
	public byte 	 m_u8Reserved[] = new byte[2]; // ����
}


// GSM��Ӧָʾ��: TUP_SP_GsmResponseTypeIndicator /////////////////////////////
// ����: GSM
class TUP_spGsmResponseTypeIndicator
{
	public byte 	 m_u8CallingPartyCategoryIndicator; // �����û�����ʾ��
	public byte 	 m_u8CallingLineIdentityIndicator; // �����û��߱�ʶ��ʾ��
	public byte 	 m_u8IdentityIndicator; // �����м̺�ת�ӽ����ֱ�ʶ
	public byte 	 m_u8OriginalCalledAddressIndicator; // ԭ���е�ַ��ʾ��
	public byte 	 m_u8OutgoingEchoSuppressorIndicator; // ȥ��������������ʾ��
	public byte 	 m_u8MaliciousCallIdentificationIndicator; // �������ʶ���ʾ��
	public byte 	 m_u8HoldIndicator; // ���ֱ�ʾ��
	public byte 	 m_u8Reserved; // ����
}


// IAI��һ��ʾ��: TUP_SP_IaiFirstIndicator ////////////////////////////////////
// ����: IAI
class TUP_spIaiFirstIndicator
{
	public byte 	 m_u8FacilityInformationIndicator; // �����������û�������Ϣ��ʾ��
	public byte 	 m_u8CUGInformationIndicator; // �պ��û�Ⱥ��Ϣ��ʾ��
	public byte 	 m_u8AdditionalCallingPartyIndicator; // ���������û���Ϣ��ʾ��
	public byte 	 m_u8AdditionalRoutingIndicator; // ����·����Ϣ��ʾ��
	public byte 	 m_u8CallingLineIdentityIndicator; // �����û��߱�ʶ��ʾ��
	public byte 	 m_u8OriginalCalledAddressIndicator; // ԭ���е�ַ��ʾ��
	public byte 	 m_u8ChargingInformationIndicator; // �Ʒ���Ϣ��ʾ��
	public byte 	 m_u8Reserved; // ����
}


// ԭ�����û�����: TUP_SP_OriginalCalledAddress ///////////////////////////////
// ����: IAI/GSM
class TUP_spOriginalCalledAddress
{
	public byte 	 m_u8NatureOfAddressIndicator; // ��ַ���ʱ�ʾ��
	public byte 	 m_u8NumberOfAddressSignal; // ��ַ�źŵ�����
	public byte 	 m_u8Reserved[] = new byte[2]; // ����
	public byte 	 m_s8AddressSignal[] = new byte[40]; // ��ַ�ź�
}


// ��Χ��״̬: TUP_SP_RangeStatus /////////////////////////////////////////////
// ����: GRM��Ϣ��
class TUP_spRangeStatus
{
	public byte 	  m_u8Range; // ��Χ
	public byte 	  m_u8Reserved[] = new byte[3]; // ����
	public int     	  m_u32Status;    // ״̬
}


// �����ַ: TUP_SP_SubsequentAddress /////////////////////////////////////////
// ����: SAM/SAO
class TUP_spSubsequentAddress
{
	public byte 	 m_s8AddressSignal[] = new byte[40]; // ��ַ�ź�
}

