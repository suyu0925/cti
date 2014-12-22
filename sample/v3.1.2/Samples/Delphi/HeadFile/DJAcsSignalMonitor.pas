unit DJAcsSignalMonitor;

interface

Type ITP_SIGMonitor_EventType =       // �������¼�����
(
	SMON_EVT_Call_Generate    =  $01, // ���з���
  SMON_EVT_Call_Connect     =  $02, // ��������
	SMON_EVT_Call_Disconnect  =  $03, // ���жϿ�
	SMON_EVT_Call_Info        =  $04, // ������Ϣ
	SMON_Evt_Gen_Signal_Info  =  $05, // ������Ϣ
	SMON_Evt_Raw_Signal_Info  =  $06  // ԭʼ��Ϣ
);


Type ITP_SIGMonitor_Protocol =          // ������Э�鶨��
(
	SMON_Protocol_ISDN      = $01,  // ISDN����
	SMON_Protocol_SS7       = $02,  // �ߺ�����
	SMON_Protocol_N64K      = $03   // N64K
);


Type ITP_SIGMonitor_SI =                // ҵ���ʾ�ﶨ��
(
	SMON_SI_SCCP = $03,             // SCCP
  SMON_SI_TUP  = $04,             // TUP
	SMON_SI_ISUP = $05             // ISUP
);


Type ITP_SIGMonitor_ISUP_MsgType =      // ��������Ϣ����
(
	SMON_ISUP_ACM = $06,		     // ��ַȫ��Ϣ
	SMON_ISUP_ANM = $09,		     // Ӧ����Ϣ
	
	SMON_ISUP_CON = $07,		     // ������Ϣ
	
	SMON_ISUP_INF = $04,		     // ��Ϣ��Ϣ
	SMON_ISUP_IAM = $01,		     // ��ʼ��ַ��Ϣ
	
	SMON_ISUP_REL = $0C,		     // �ͷ���Ϣ
	SMON_ISUP_RLC = $10,		     // �ͷ������Ϣ
	
	SMON_ISUP_SAM = $02,		     // ������ַ��Ϣ
	
	//
	SMON_ISUP_CPG = $2C,		     // ���н�չ��Ϣ
	SMON_ISUP_CQR = $2B,		     // ��·Ⱥѯ����Ӧ��Ϣ
	SMON_ISUP_GRA = $29,		     // ��·Ⱥ��ԭ֤ʵ��Ϣ
	SMON_ISUP_CFN = $2F,		     // ������Ϣ
	
	SMON_ISUP_COT = $05,		     // ��ͨ��Ϣ
	SMON_ISUP_FRJ = $21,		     // ���ܾܾ���Ϣ
	
	SMON_ISUP_INR = $03,		     // ��Ϣ������Ϣ
	
	SMON_ISUP_USR = $2D,		     // �û����û���Ϣ
	SMON_ISUP_FOT = $08,		     // ǰ�򴫵���Ϣ
	
	SMON_ISUP_RES = $0E,		     // �ָ���Ϣ
	SMON_ISUP_SUS = $0D,		     // ��ͣ��Ϣ
	
	SMON_ISUP_BLO = $13,		     // ������Ϣ
	SMON_ISUP_BLA = $15,		     // ����֤ʵ��Ϣ
	SMON_ISUP_CCR = $11,		     // ��ͨ����������Ϣ
	SMON_ISUP_LPA = $24,		     // ��·ȷ����Ϣ
	SMON_ISUP_OLM = $30,		     // ��������Ϣ
	SMON_ISUP_RSC = $12,		     // ��·��ԭ��Ϣ
	SMON_ISUP_UBL = $14,		     // ���������Ϣ
	SMON_ISUP_UBA = $16,		     // �������֤ʵ��Ϣ
	SMON_ISUP_UCIC= $2E,		     // δװ����·ʶ������Ϣ
	
	SMON_ISUP_CGB = $18,		     // ��·Ⱥ������Ϣ
	SMON_ISUP_CGBA= $1A,		     // ��·Ⱥ����֤ʵ��Ϣ
	SMON_ISUP_CGU = $19,		     // ��·Ⱥ���������Ϣ
	SMON_ISUP_CGUA= $1B,		     // ��·Ⱥ�������֤ʵ��Ϣ
	
	SMON_ISUP_GRS = $17,		     // ��·Ⱥ��ԭ��Ϣ
	SMON_ISUP_CQM = $2A,		     // ��·Ⱥѯ����Ϣ
	
	SMON_ISUP_FAA = $20,		     // ���ܽ�����Ϣ
	SMON_ISUP_FAR = $1F,		     // ����������Ϣ
	
	SMON_ISUP_PAM = $28,		     // ������Ϣ
	
	SMON_ISUP_UPT = $34,		     // �û����ֲ���
	SMON_ISUP_UPA = $35,		     // �û����ֿ�����
	
	SMON_ISUP_FAC = $33,		     // ������Ϣ
	SMON_ISUP_NRM = $32,		     // ������Դ����
	SMON_ISUP_IDR = $36,		     // ʶ������
	SMON_ISUP_IRS = $37,		     // ʶ����Ӧ
	SMON_ISUP_SGM = $38,		     // �ֶ�
	
	SMON_ISUP_CRG = $31,		     // �Ʒ���Ϣ
	SMON_ISUP_OPR = $FE,		     // ����Ա��Ϣ
	SMON_ISUP_MPM = $FD,		     // �ƴ�����
	SMON_ISUP_CCL = $FC 		     // ���йһ�
);


Type ITP_SIGMonitor_TUP_MsgType =       // ��������Ϣ����
(
	SMON_TUP_IAM = $11,             // ��ʼ��ַ��Ϣ
	SMON_TUP_IAI = $21,             // ���и�����Ϣ�ĳ�ʼ��ַ��Ϣ
	SMON_TUP_SAM = $31,             // ������ַ��Ϣ
	SMON_TUP_SAO = $41,             // ����һ����ַ�źŵĺ�����ַ��Ϣ
	
	SMON_TUP_ACM = $14,             // ��ַ��ȫ��Ϣ
	
	SMON_TUP_SEC = $15,             // �����豸ӵ���ź�
	SMON_TUP_CGC = $25,             // ��·Ⱥӵ���ź�
	SMON_TUP_NNC = $35,             // ������ӵ���ź�
	SMON_TUP_ADI = $45,             // ��ַ��ȫ�ź�
	SMON_TUP_CFL = $55,             // ���й����ź�
	SMON_TUP_SSB = $65,             // �û�æ�ź�
	SMON_TUP_UNN = $75,             // �պ�
	SMON_TUP_LOS = $85,             // ��·�������ź�
	SMON_TUP_SST = $95,             // ����ר����Ϣ���ź�
	SMON_TUP_ACB = $A5,             // ����ܾ��ź�
	SMON_TUP_DPN = $B5,             // ���ṩ����ͨ·�ź�
	SMON_TUP_MPR = $C5,             // ���м�ǰ׺
	
	SMON_TUP_SLB = $1E,             // �û���æ�ź�
	SMON_TUP_STB = $2E,             // �û���æ�ź�
	
	SMON_TUP_ANU = $06,             // Ӧ���źţ��Ʒ�δ˵��
	SMON_TUP_ANC = $16,             // Ӧ���źš��շ�
	SMON_TUP_ANN = $26,             // Ӧ���źš����
	SMON_TUP_CBK = $36,             // �һ��ź�
	SMON_TUP_CLF = $46,             // �����ź�
	
	SMON_TUP_RLG = $17,             // �ͷż໤�ź�
	
	SMON_TUP_GSM = $12,             // һ��ǰ������Ϣ��Ϣ
	
	//
	SMON_TUP_COT = $32,             // ��ͨ�ź�
	SMON_TUP_CCF = $42,             // ��ͨ�����ź�
		
	SMON_TUP_GRQ = $13,             // һ��������Ϣ
	
	SMON_TUP_CHG = $24,             // �Ʒ���Ϣ
		
	SMON_TUP_EUM = $F5,             // ����ĺ��������ɹ���Ϣ
			
	SMON_TUP_RAN = $56,             // ��Ӧ���ź�
	SMON_TUP_FOT = $66,             // ǰ��ת���ź�
	SMON_TUP_CCL = $76,             // �����û��һ��ź�
	
	SMON_TUP_BLO = $27,             // �����ź�
	SMON_TUP_BLA = $37,             // ����֤ʵ�ź�
	SMON_TUP_UBL = $47,             // ��������ź�
	SMON_TUP_UBA = $57,             // �������֤ʵ�ź�
	SMON_TUP_CCR = $67,             // ����ͨ�����ź�
	SMON_TUP_RSC = $77,             // ��·��ԭ�ź�

	SMON_TUP_MGB = $18,             // ����ά����Ⱥ������Ϣ
	SMON_TUP_MBA = $28,             // ����ά����Ⱥ����֤ʵ��Ϣ
	SMON_TUP_MGU = $38,             // ����ά����Ⱥ���������Ϣ
	SMON_TUP_MUA = $48,             // ����ά����Ⱥ�������֤ʵ��Ϣ
	SMON_TUP_HGB = $58,             // ����Ӳ�����ϵ�Ⱥ������Ϣ
	SMON_TUP_HBA = $68,             // ����Ӳ�����ϵ�Ⱥ����֤ʵ��Ϣ
	SMON_TUP_HGU = $78,             // ����Ӳ�����ϵ�Ⱥ���������Ϣ
	SMON_TUP_HUA = $88,             // ����Ӳ�����ϵ�Ⱥ�������֤ʵ��Ϣ
	SMON_TUP_GRS = $98,             // ��·Ⱥ��ԭ��Ϣ
	SMON_TUP_GRA = $A8,             // Ⱥ��ԭ֤ʵ��Ϣ
	SMON_TUP_SGB = $B8,             // ���������Ⱥ������Ϣ
	SMON_TUP_SBA = $C8,             // ���������Ⱥ����֤ʵ��Ϣ
	SMON_TUP_SGU = $D8,             // ���������Ⱥ���������Ϣ
	SMON_TUP_SUA = $E8,             // ���������Ⱥ�������֤ʵ��Ϣ
		
	SMON_TUP_ACC = $1A,             // �Զ�ӵ��������Ϣ��Ϣ
		
	SMON_TUP_MPM = $2C,             // �ƴ�������Ϣ
		
	SMON_TUP_OPR = $1D,             // ����Ա�ź�
	
	SMON_TUP_MAL = $1F             // �������׷���ź�
);


Type ITP_SIGMonitor_ISDN_MsgType =      // ��������Ϣ����
(
	SMON_ISDN_Alerting        = $01,// ����
	SMON_ISDN_Call_Proceeding = $02,// ���н���
	SMON_ISDN_Connect         = $07,// ����
	SMON_ISDN_Connect_Ack     = $0F,// ����֤ʵ
	SMON_ISDN_Progress        = $03,// ��չ
	SMON_ISDN_Setup           = $05,// ����
	SMON_ISDN_Setup_Ack       = $0D,// ����֤ʵ
	
	SMON_ISDN_Resume          = $26,// �ָ�
	SMON_ISDN_Resume_Ack      = $2E,// �ָ�֤ʵ
	SMON_ISDN_Resume_Reject   = $22,// �ָ��ܾ�
	SMON_ISDN_Suspend         = $25,// ��ͣ
	SMON_ISDN_Suspend_Ack     = $2D,// ��֤ͣʵ
	SMON_ISDN_Suspend_Reject  = $21,// ��ͣ�ܾ�
	SMON_ISDN_User_Information= $20,// �û���Ϣ
	
	SMON_ISDN_Disconnect      = $45,// ����
	SMON_ISDN_Release         = $4D,// �ͷ�
	SMON_ISDN_Release_Complete= $5A,// �ͷ����
	SMON_ISDN_Restart         = $46,// ��������
	SMON_ISDN_Restart_Ack     = $4E,// ����֤ʵ
	
	SMON_ISDN_Segment         = $60,// �ֶ�
	SMON_ISDN_Congestion_Ctrl = $79,// ӵ������
	SMON_ISDN_Information     = $7B,// ��Ϣ
	SMON_ISDN_Notify          = $6E,// ֪ͨ
	SMON_ISDN_Status          = $7D,// ״̬
	SMON_ISDN_Status_Enquiry  = $75 // ״̬ѯ��
);


///////////////////////////////////////////////////////////////////////////////
const SMON_Evt_Len_But_Raw_Data  = 128;// �¼�����ԭʼ���ݲ��ֵĳ���

Type                       // ���ص��¼����ݽṹ
  SMON_EVENT = record
	EventType : Byte;               // �¼�����
	Protocol  : Byte;               // Э������
	SI        : Byte;               // ҵ���ʾ
	MsgType   : Byte;               // ������Ϣ

	Caller_ID : Array[0..31] of ShortInt;           // ���к���
	Called_ID : Array[0..31] of ShortInt;           // ���к���
	OriCalled : Array[0..31] of ShortInt;           // ԭʼ����
	
	DPC : Array[0..2] of Byte;                  // Ŀ�ĵ���
	OPC : Array[0..2] of Byte;                  // ԭ�˵���

	Pcm : Byte;                     // CIC_Hig7
	Chn : Byte;                     // CIC_Low5
	
	ReleaseReason : Byte;           // ����ԭ��
	Reserved      : Array[0..13] of Byte;            // ��������

	Unit_ID : Byte;                 // ��Դ��Ԫ
	Port_ID : Byte;                 // ��Դ�˿�
	TS      : Byte;                      // ��Դʱ϶
	DataLen : Word;                 // ���ݳ���
	RAWdata : Array[0..2047] of Byte;           // ԭʼ����
end;

implementation

end.
