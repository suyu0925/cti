#ifndef __ITP_SIGNAL_MONITOR_H__
#define __ITP_SIGNAL_MONITOR_H__

///////////////////////////////////////////////////////////////////////////////
enum ITP_SIGMonitor_EventType        // �������¼�����
{	
	SMON_EVT_Call_Generate  =  0x01, // ���з���
    SMON_EVT_Call_Connect   =  0x02, // ��������
	SMON_EVT_Call_Disconnect=  0x03, // ���жϿ�
	SMON_EVT_Call_Info      =  0x04, // ������Ϣ
	SMON_Evt_Gen_Signal_Info=  0x05, // ������Ϣ
	SMON_Evt_Raw_Signal_Info=  0x06, // ԭʼ��Ϣ
};


enum ITP_SIGMonitor_Protocol         // ������Э�鶨��
{	
	SMON_Protocol_ISDN      = 0x01,  // ISDN����
	SMON_Protocol_SS7       = 0x02,  // �ߺ�����
	SMON_Protocol_N64K      = 0x03,  // N64K
};


enum ITP_SIGMonitor_SI               // ҵ���ʾ�ﶨ��
{	
	SMON_SI_SCCP = 0x03,             // SCCP
    SMON_SI_TUP  = 0x04,             // TUP
	SMON_SI_ISUP = 0x05,             // ISUP
};


enum ITP_SIGMonitor_ISUP_MsgType     // ��������Ϣ����
{	
	SMON_ISUP_ACM = 0x06,		     // ��ַȫ��Ϣ
	SMON_ISUP_ANM = 0x09,		     // Ӧ����Ϣ
	
	SMON_ISUP_CON = 0x07,		     // ������Ϣ
	
	SMON_ISUP_INF = 0x04,		     // ��Ϣ��Ϣ
	SMON_ISUP_IAM = 0x01,		     // ��ʼ��ַ��Ϣ
	
	SMON_ISUP_REL = 0x0C,		     // �ͷ���Ϣ
	SMON_ISUP_RLC = 0x10,		     // �ͷ������Ϣ
	
	SMON_ISUP_SAM = 0x02,		     // ������ַ��Ϣ
	
	//
	SMON_ISUP_CPG = 0x2C,		     // ���н�չ��Ϣ
	SMON_ISUP_CQR = 0x2B,		     // ��·Ⱥѯ����Ӧ��Ϣ
	SMON_ISUP_GRA = 0x29,		     // ��·Ⱥ��ԭ֤ʵ��Ϣ
	SMON_ISUP_CFN = 0x2F,		     // ������Ϣ
	
	SMON_ISUP_COT = 0x05,		     // ��ͨ��Ϣ
	SMON_ISUP_FRJ = 0x21,		     // ���ܾܾ���Ϣ
	
	SMON_ISUP_INR = 0x03,		     // ��Ϣ������Ϣ	
	
	SMON_ISUP_USR = 0x2D,		     // �û����û���Ϣ
	SMON_ISUP_FOT = 0x08,		     // ǰ�򴫵���Ϣ
	
	SMON_ISUP_RES = 0x0E,		     // �ָ���Ϣ
	SMON_ISUP_SUS = 0x0D,		     // ��ͣ��Ϣ
	
	SMON_ISUP_BLO = 0x13,		     // ������Ϣ
	SMON_ISUP_BLA = 0x15,		     // ����֤ʵ��Ϣ
	SMON_ISUP_CCR = 0x11,		     // ��ͨ����������Ϣ
	SMON_ISUP_LPA = 0x24,		     // ��·ȷ����Ϣ
	SMON_ISUP_OLM = 0x30,		     // ��������Ϣ
	SMON_ISUP_RSC = 0x12,		     // ��·��ԭ��Ϣ
	SMON_ISUP_UBL = 0x14,		     // ���������Ϣ
	SMON_ISUP_UBA = 0x16,		     // �������֤ʵ��Ϣ
	SMON_ISUP_UCIC= 0x2E,		     // δװ����·ʶ������Ϣ
	
	SMON_ISUP_CGB = 0x18,		     // ��·Ⱥ������Ϣ
	SMON_ISUP_CGBA= 0x1A,		     // ��·Ⱥ����֤ʵ��Ϣ
	SMON_ISUP_CGU = 0x19,		     // ��·Ⱥ���������Ϣ
	SMON_ISUP_CGUA= 0x1B,		     // ��·Ⱥ�������֤ʵ��Ϣ
	
	SMON_ISUP_GRS = 0x17,		     // ��·Ⱥ��ԭ��Ϣ
	SMON_ISUP_CQM = 0x2A,		     // ��·Ⱥѯ����Ϣ
	
	SMON_ISUP_FAA = 0x20,		     // ���ܽ�����Ϣ
	SMON_ISUP_FAR = 0x1F,		     // ����������Ϣ
	
	SMON_ISUP_PAM = 0x28,		     // ������Ϣ
	
	SMON_ISUP_UPT = 0x34,		     // �û����ֲ���
	SMON_ISUP_UPA = 0x35,		     // �û����ֿ�����
	
	SMON_ISUP_FAC = 0x33,		     // ������Ϣ
	SMON_ISUP_NRM = 0x32,		     // ������Դ����
	SMON_ISUP_IDR = 0x36,		     // ʶ������
	SMON_ISUP_IRS = 0x37,		     // ʶ����Ӧ
	SMON_ISUP_SGM = 0x38,		     // �ֶ�
	
	SMON_ISUP_CRG = 0x31,		     // �Ʒ���Ϣ
	SMON_ISUP_OPR = 0xFE,		     // ����Ա��Ϣ
	SMON_ISUP_MPM = 0xFD,		     // �ƴ�����
	SMON_ISUP_CCL = 0xFC,		     // ���йһ�
};


enum ITP_SIGMonitor_TUP_MsgType      // ��������Ϣ����
{	
	SMON_TUP_IAM = 0x11,             // ��ʼ��ַ��Ϣ
	SMON_TUP_IAI = 0x21,             // ���и�����Ϣ�ĳ�ʼ��ַ��Ϣ
	SMON_TUP_SAM = 0x31,             // ������ַ��Ϣ
	SMON_TUP_SAO = 0x41,             // ����һ����ַ�źŵĺ�����ַ��Ϣ	
	
	SMON_TUP_ACM = 0x14,             // ��ַ��ȫ��Ϣ
	
	SMON_TUP_SEC = 0x15,             // �����豸ӵ���ź�
	SMON_TUP_CGC = 0x25,             // ��·Ⱥӵ���ź�
	SMON_TUP_NNC = 0x35,             // ������ӵ���ź�
	SMON_TUP_ADI = 0x45,             // ��ַ��ȫ�ź�
	SMON_TUP_CFL = 0x55,             // ���й����ź�
	SMON_TUP_SSB = 0x65,             // �û�æ�ź�
	SMON_TUP_UNN = 0x75,             // �պ�
	SMON_TUP_LOS = 0x85,             // ��·�������ź�
	SMON_TUP_SST = 0x95,             // ����ר����Ϣ���ź�
	SMON_TUP_ACB = 0xA5,             // ����ܾ��ź�
	SMON_TUP_DPN = 0xB5,             // ���ṩ����ͨ·�ź�
	SMON_TUP_MPR = 0xC5,             // ���м�ǰ׺
	
	SMON_TUP_SLB = 0x1E,             // �û���æ�ź�
	SMON_TUP_STB = 0x2E,             // �û���æ�ź�
	
	SMON_TUP_ANU = 0x06,             // Ӧ���źţ��Ʒ�δ˵��
	SMON_TUP_ANC = 0x16,             // Ӧ���źš��շ�
	SMON_TUP_ANN = 0x26,             // Ӧ���źš����
	SMON_TUP_CBK = 0x36,             // �һ��ź�
	SMON_TUP_CLF = 0x46,             // �����ź�	
	
	SMON_TUP_RLG = 0x17,             // �ͷż໤�ź�	
	
	SMON_TUP_GSM = 0x12,             // һ��ǰ������Ϣ��Ϣ
	
	//
	SMON_TUP_COT = 0x32,             // ��ͨ�ź�
	SMON_TUP_CCF = 0x42,             // ��ͨ�����ź�
		
	SMON_TUP_GRQ = 0x13,             // һ��������Ϣ			
	
	SMON_TUP_CHG = 0x24,             // �Ʒ���Ϣ
		
	SMON_TUP_EUM = 0xF5,             // ����ĺ��������ɹ���Ϣ
			
	SMON_TUP_RAN = 0x56,             // ��Ӧ���ź�
	SMON_TUP_FOT = 0x66,             // ǰ��ת���ź�
	SMON_TUP_CCL = 0x76,             // �����û��һ��ź�
	
	SMON_TUP_BLO = 0x27,             // �����ź�
	SMON_TUP_BLA = 0x37,             // ����֤ʵ�ź�
	SMON_TUP_UBL = 0x47,             // ��������ź�
	SMON_TUP_UBA = 0x57,             // �������֤ʵ�ź�
	SMON_TUP_CCR = 0x67,             // ����ͨ�����ź�
	SMON_TUP_RSC = 0x77,             // ��·��ԭ�ź�
		
	SMON_TUP_MGB = 0x18,             // ����ά����Ⱥ������Ϣ
	SMON_TUP_MBA = 0x28,             // ����ά����Ⱥ����֤ʵ��Ϣ
	SMON_TUP_MGU = 0x38,             // ����ά����Ⱥ���������Ϣ
	SMON_TUP_MUA = 0x48,             // ����ά����Ⱥ�������֤ʵ��Ϣ
	SMON_TUP_HGB = 0x58,             // ����Ӳ�����ϵ�Ⱥ������Ϣ
	SMON_TUP_HBA = 0x68,             // ����Ӳ�����ϵ�Ⱥ����֤ʵ��Ϣ
	SMON_TUP_HGU = 0x78,             // ����Ӳ�����ϵ�Ⱥ���������Ϣ
	SMON_TUP_HUA = 0x88,             // ����Ӳ�����ϵ�Ⱥ�������֤ʵ��Ϣ
	SMON_TUP_GRS = 0x98,             // ��·Ⱥ��ԭ��Ϣ
	SMON_TUP_GRA = 0xA8,             // Ⱥ��ԭ֤ʵ��Ϣ
	SMON_TUP_SGB = 0xB8,             // ���������Ⱥ������Ϣ
	SMON_TUP_SBA = 0xC8,             // ���������Ⱥ����֤ʵ��Ϣ
	SMON_TUP_SGU = 0xD8,             // ���������Ⱥ���������Ϣ
	SMON_TUP_SUA = 0xE8,             // ���������Ⱥ�������֤ʵ��Ϣ
		
	SMON_TUP_ACC = 0x1A,             // �Զ�ӵ��������Ϣ��Ϣ
		
	SMON_TUP_MPM = 0x2C,             // �ƴ�������Ϣ
		
	SMON_TUP_OPR = 0x1D,             // ����Ա�ź�			
	
	SMON_TUP_MAL = 0x1F,             // �������׷���ź�
};


enum ITP_SIGMonitor_ISDN_MsgType     // ��������Ϣ����
{
	SMON_ISDN_Alerting        = 0x01,// ����
	SMON_ISDN_Call_Proceeding = 0x02,// ���н���
	SMON_ISDN_Connect         = 0x07,// ����
	SMON_ISDN_Connect_Ack     = 0x0F,// ����֤ʵ
	SMON_ISDN_Progress        = 0x03,// ��չ
	SMON_ISDN_Setup           = 0x05,// ����
	SMON_ISDN_Setup_Ack       = 0x0D,// ����֤ʵ
	
	SMON_ISDN_Resume          = 0x26,// �ָ�
	SMON_ISDN_Resume_Ack      = 0x2E,// �ָ�֤ʵ
	SMON_ISDN_Resume_Reject   = 0x22,// �ָ��ܾ�
	SMON_ISDN_Suspend         = 0x25,// ��ͣ
	SMON_ISDN_Suspend_Ack     = 0x2D,// ��֤ͣʵ
	SMON_ISDN_Suspend_Reject  = 0x21,// ��ͣ�ܾ�
	SMON_ISDN_User_Information= 0x20,// �û���Ϣ
	
	SMON_ISDN_Disconnect      = 0x45,// ����
	SMON_ISDN_Release         = 0x4D,// �ͷ�
	SMON_ISDN_Release_Complete= 0x5A,// �ͷ����
	SMON_ISDN_Restart         = 0x46,// ��������
	SMON_ISDN_Restart_Ack     = 0x4E,// ����֤ʵ
	
	SMON_ISDN_Segment         = 0x60,// �ֶ�
	SMON_ISDN_Congestion_Ctrl = 0x79,// ӵ������
	SMON_ISDN_Information     = 0x7B,// ��Ϣ
	SMON_ISDN_Notify          = 0x6E,// ֪ͨ
	SMON_ISDN_Status          = 0x7D,// ״̬
	SMON_ISDN_Status_Enquiry  = 0x75,// ״̬ѯ��
};


///////////////////////////////////////////////////////////////////////////////
#define SMON_Evt_Len_But_Raw_Data 128// �¼�����ԭʼ���ݲ��ֵĳ���

typedef struct                       // ���ص��¼����ݽṹ
{	
	DJ_U8   EventType;               // �¼�����
	DJ_U8   Protocol;                // Э������
	DJ_U8   SI;                      // ҵ���ʾ
	DJ_U8   MsgType;                 // ������Ϣ
	
	DJ_S8   Caller_ID[32];           // ���к���
	DJ_S8   Called_ID[32];           // ���к���
	DJ_S8   OriCalled[32];           // ԭʼ����
	
	DJ_U8   DPC[3];                  // Ŀ�ĵ���
	DJ_U8   OPC[3];                  // ԭ�˵���
	DJ_U8   Pcm;                     // CIC_Hig7
	DJ_U8   Chn;                     // CIC_Low5
	
	DJ_U8   ReleaseReason;           // ����ԭ��
	DJ_U8   Reserved[14];            // ��������
	DJ_U8   Unit_ID;                 // ��Դ��Ԫ
	DJ_U8   Port_ID;                 // ��Դ�˿�
	DJ_U8   TS;                      // ��Դʱ϶
	DJ_U16  DataLen;                 // ���ݳ���
	
	DJ_U8   RAWdata[2048];           // ԭʼ����
}SMON_EVENT, *PSMON_EVENT;

#endif
