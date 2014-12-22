unit DJAcsTUPDef;

interface

uses
  SysUtils,Windows;

// TUP������Ϣ����(������Ҫֱ�ӷ��Ͳ���) //////////////////////////////////////
Type XMS_TUP_Signalling_Message =      // TUP������Ϣ
(
    TUP_SM_SAM = $31,              // ������ַ�ź�
    TUP_SM_SAO = $41,              // ����һ����ַ�ĺ�����ַ�ź�
    
    TUP_SM_GSM = $12,              // һ��ǰ������Ϣ�ź�
    TUP_SM_GRQ = $13,              // һ�������ź�
    
    TUP_SM_BLO = $27,              // �����ź�
    TUP_SM_UBL = $47,              // ��������ź�
    TUP_SM_RSC = $77,              // ��·��ԭ�ź�
    
    TUP_SM_MGB = $18,              // ����ά����Ⱥ�����ź�
    TUP_SM_MGU = $38,              // ����ά����Ⱥ��������ź�
    TUP_SM_HGB = $58,              // ����Ӳ�����ϵ�Ⱥ�����ź�
    TUP_SM_HGU = $78,              // ����Ӳ�����ϵ�Ⱥ��������ź�
    TUP_SM_GRS = $98,              // ��·Ⱥ��ԭ�ź�
    TUP_SM_SGB = $B8,              // ���������Ⱥ�����ź�
    TUP_SM_SGU = $D8               // ���������Ⱥ����������ź�
);


// TUP����������� ////////////////////////////////////////////////////////////
Type XMS_TUP_Signalling_Parameter =                   // TUP�������
(
	TUP_SP_AccMessageIndicator        = $0C,       // ACC��Ϣָʾ��
	TUP_SP_AcmMessageIndicator        = $09,       // ACM��Ϣָʾ��
	TUP_SP_CalledPartAddress          = $0F,       // �����û�����
	TUP_SP_CallingLineAddress         = $02,       // �����û�����
	TUP_SP_CallingPartyCategory       = $01,       // �����û����
	TUP_SP_ConnectionNatureIndicator  = $0D,       // ��������ָʾ��
	TUP_SP_EumOctetIndicator          = $0A,       // EUM��Ϣ��λ��
	TUP_SP_EumSignallingPointCode     = $0B,       // EUM��Ϣ�����
	TUP_SP_ForwardCallInformation     = $0E,       // ǰ�������Ϣ
	TUP_SP_GrqRequestTypeIndicator    = $08,       // GRQ����ָʾ��
	TUP_SP_GsmResponseTypeIndicator   = $06,       // GSM��Ӧָʾ��
	TUP_SP_IaiFirstIndicator          = $05,       // IAI��һ��ʾ��
	TUP_SP_OriginalCalledAddress      = $03,       // ԭ�����û�����
	TUP_SP_RangeStatus                = $04,       // ��Χ��״̬
	TUP_SP_SubsequentAddress          = $10        // ������ַ
);


// TUP����������ݽṹ���� ////////////////////////////////////////////////////
// ACC��Ϣָʾ��: TUP_SP_AccMessageIndicator //////////////////////////////////
// ����: ACC
Type
  TUP_spAccMessageIndicator = record
	m_u8ACCInformation : Byte;                // ACC��Ϣ
	m_u8Reserved       : Array[0..2] of Byte; // ����
end;


// ACM��Ϣָʾ��: TUP_SP_AcmMessageIndicator //////////////////////////////////
// ����: ACM
Type
  TUP_spAcmMessageIndicator = record
	m_u8TypeOfACMIndicator      : Byte; // ��ַȫ�ź����ͱ�ʾ��
	m_u8SubscriberFreeIndicator : Byte; // �û��б�ʾ��
	m_u8IncomingEchoSuppressorIndicator : Byte; // ����������������ʾ��
	m_u8CallForwardingIndicator : Byte; // ����ת�Ʊ�ʾ��
	m_u8SignallingPathIndicator : Byte; // �ź�ͨ����ʾ��
	m_u8Reserved                : Array[0..2] of Byte; // ����
end;


// �����û�����: TUP_SP_CalledPartAddress /////////////////////////////////////
// ����: IAM/IAI
Type
  TUP_spCalledPartAddress = record
	m_u8NatureOfAddressIndicator : Byte; // ��ַ���ʱ�ʾ��
	m_u8NumberOfAddressSignal    : Byte; // ��ַ�źŵ�����

	m_u8Reserved       : Array[0..1] of Byte; // ����
	m_s8AddressSignal  : Array[0..39] of ShortInt; // ��ַ�ź�
end;


// �����û�����: TUP_SP_CallingLineAddress ////////////////////////////////////
// ����: IAI/GSM
Type
  TUP_spCallingLineAddress = record
	m_u8NatureOfAddressIndicator : Byte; // ��ַ���ʱ�ʾ��
	m_u8PresentationIndicator    : Byte; // �ṩ�����û��߱�ʶ��ʾ��
	m_u8IncompleteIndicator      : Byte; // �����û��߱�ʶ��ȫ��ʾ��
	m_u8NumberOfAddressSignal    : Byte; // ���е�ַ�źŵ�����
	m_s8AddressSignal            : Array[0..39] of ShortInt; // ��ַ�ź�
end;


// �����û����: TUP_SP_CallingPartyCategory //////////////////////////////////
// ����: IAM/IAI/GSM
Type
  TUP_spCallingPartyCategory = record
	m_u8CallingPartyCategory : Byte;                // �����û����
	m_u8Reserved             : Array[0..2] of Byte; // ����
end;


// ��������ָʾ��: TUP_SP_ConnectionNatureIndicator ///////////////////////////
// ����: IAM/IAI
Type
  TUP_spConnectionNatureIndicator = record
	m_u8NatureOfCircuitIndicator : Byte; // ��·���ʱ�ʾ��
	m_u8ContinuityCheckIndicator : Byte; // ��ͨ�����ʾ��
	m_u8EchoSuppressorIndicator  : Byte;  // ȥ��������������ʾ��
	m_u8Reserved                 : Byte;
end;


// EUM��Ϣ��λ��: TUP_SP_EumOctetIndicator ////////////////////////////////////
// ����: EUM
Type
  TUP_spEumOctetIndicator = record
	m_u8UnsuccessfulIndicator : Byte; // ���ɹ���ʾ��
	m_u8Reserved              : Array[0..2] of Byte; // ����
end;


// EUM��Ϣ�����: TUP_SP_EumSignallingPointCode ///////////////////////////////
// ����: EUM
Type
  TUP_spEumSignallingPointCode = record
	m_u32SPC : DWORD; // ��������
end;


// ǰ�������Ϣ: TUP_SP_ForwardCallInformation ////////////////////////////////
// ����: IAM/IAI
Type
  TUP_spForwardCallInformation = record
	m_u8InternationalCallIndicator      : Byte; // �����������б�ʾ��
	m_u8RedirectedCallIndicator         : Byte; // �ķ����б�ʾ��
	m_u8AllDigitalPathRequiredIndicator : Byte; // ��Ҫȫ��������ͨ·��ʾ��
	m_u8SignallingPathIndicator         : Byte; // �ź�ͨ����ʾ��
end;


// GRQ����ָʾ��: TUP_SP_GrqRequestTypeIndicator //////////////////////////////
// ����: GRQ
Type
  TUP_spGrqRequestTypeIndicator = record
	m_u8CallingPartyCategoryRequestIndicator  : Byte; // �����û���������ʾ��
	m_u8CallingLineIdentityRequestIndicator   : Byte; // �����û��߱�ʶ�����ʾ��
	m_u8OriginalCalledAddressRequestIndicator : Byte; // ԭ���е�ַ�����ʾ��
	m_u8MaliciousCallIdentificationIndicator  : Byte; // �������ʶ�������ʾ��
	m_u8HoldRequestIndicator                  : Byte; // ���������ʾ��
	m_u8EchoSuppressorRequestIndicator        : Byte; // ���������������ʾ��
	m_u8Reserved : Array[0..1] of Byte; // ����
end;


// GSM��Ӧָʾ��: TUP_SP_GsmResponseTypeIndicator /////////////////////////////
// ����: GSM
Type
  TUP_spGsmResponseTypeIndicator = record
	m_u8CallingPartyCategoryIndicator        : Byte; // �����û�����ʾ��
	m_u8CallingLineIdentityIndicator         : Byte; // �����û��߱�ʶ��ʾ��
	m_u8IdentityIndicator                    : Byte; // �����м̺�ת�ӽ����ֱ�ʶ
	m_u8OriginalCalledAddressIndicator       : Byte; // ԭ���е�ַ��ʾ��
	m_u8OutgoingEchoSuppressorIndicator      : Byte; // ȥ��������������ʾ��
	m_u8MaliciousCallIdentificationIndicator : Byte; // �������ʶ���ʾ��
	m_u8HoldIndicator : Byte; // ���ֱ�ʾ��
	m_u8Reserved      : Byte; // ����
end;


// IAI��һ��ʾ��: TUP_SP_IaiFirstIndicator ////////////////////////////////////
// ����: IAI
Type
  TUP_spIaiFirstIndicator = record
	m_u8FacilityInformationIndicator    : Byte; // �����������û�������Ϣ��ʾ��
	m_u8CUGInformationIndicator         : Byte; // �պ��û�Ⱥ��Ϣ��ʾ��
	m_u8AdditionalCallingPartyIndicator : Byte; // ���������û���Ϣ��ʾ��
	m_u8AdditionalRoutingIndicator      : Byte; // ����·����Ϣ��ʾ��
	m_u8CallingLineIdentityIndicator    : Byte; // �����û��߱�ʶ��ʾ��
	m_u8OriginalCalledAddressIndicator  : Byte; // ԭ���е�ַ��ʾ��
	m_u8ChargingInformationIndicator    : Byte; // �Ʒ���Ϣ��ʾ��
	m_u8Reserved : Byte; // ����
end;


// ԭ�����û�����: TUP_SP_OriginalCalledAddress ///////////////////////////////
// ����: IAI/GSM
Type
  TUP_spOriginalCalledAddress = record
	m_u8NatureOfAddressIndicator : Byte; // ��ַ���ʱ�ʾ��
	m_u8NumberOfAddressSignal    : Byte; // ��ַ�źŵ�����
	m_u8Reserved      : Array[0..1] of Byte;      // ����
	m_s8AddressSignal : Array[0..39] of ShortInt; // ��ַ�ź�
end;


// ��Χ��״̬: TUP_SP_RangeStatus /////////////////////////////////////////////
// ����: GRM��Ϣ��
Type
  TUP_spRangeStatus = record
	m_u8Range : Byte;       // ��Χ
	m_u8Reserved : Array[0..2] of Byte; // ����
	m_u32Status : DWORD;    // ״̬
end;


// ������ַ: TUP_SP_SubsequentAddress /////////////////////////////////////////
// ����: SAM/SAO
Type
  TUP_spSubsequentAddress = record
	m_s8AddressSignal : Array[0..39] of ShortInt; // ��ַ�ź�
end;

implementation

end.
