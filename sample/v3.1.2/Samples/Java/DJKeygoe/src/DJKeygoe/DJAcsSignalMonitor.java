package DJKeygoe;

public class DJAcsSignalMonitor {
}


///////////////////////////////////////////////////////////////////////////////
class ITP_SIGMonitor_EventType        // �������¼�����
{	
	public static final int SMON_EVT_Call_Generate  =  0x01; // ���з���
	public static final int SMON_EVT_Call_Connect   =  0x02; // ��������
	public static final int SMON_EVT_Call_Disconnect=  0x03; // ���жϿ�
	public static final int SMON_EVT_Call_Info      =  0x04; // ������Ϣ
	public static final int SMON_Evt_Gen_Signal_Info=  0x05; // ������Ϣ
	public static final int SMON_Evt_Raw_Signal_Info=  0x06; // ԭʼ��Ϣ
}


class ITP_SIGMonitor_Protocol         // ������Э�鶨��
{	
	public static final int SMON_Protocol_ISDN      = 0x01;  // ISDN����
	public static final int SMON_Protocol_SS7       = 0x02;  // �ߺ�����
	public static final int SMON_Protocol_N64K      = 0x03;  // N64K
}


class ITP_SIGMonitor_SI               // ҵ���ʾ�ﶨ��
{	
	public static final int SMON_SI_SCCP = 0x03;             // SCCP
	public static final int SMON_SI_TUP  = 0x04;             // TUP
	public static final int SMON_SI_ISUP = 0x05;             // ISUP
}


class ITP_SIGMonitor_ISUP_MsgType     // ��������Ϣ����
{	
	public static final int SMON_ISUP_ACM = 0x06;		     // ��ַȫ��Ϣ
	public static final int SMON_ISUP_ANM = 0x09;		     // Ӧ����Ϣ
	public static final int SMON_ISUP_CON = 0x07;		     // ������Ϣ
	
	public static final int SMON_ISUP_INF = 0x04;		     // ��Ϣ��Ϣ
	public static final int SMON_ISUP_IAM = 0x01;		     // ��ʼ��ַ��Ϣ
	
	public static final int SMON_ISUP_REL = 0x0C;		     // �ͷ���Ϣ
	public static final int SMON_ISUP_RLC = 0x10;		     // �ͷ������Ϣ
	
	public static final int SMON_ISUP_SAM = 0x02;		     // �����ַ��Ϣ
	
	//
	public static final int SMON_ISUP_CPG = 0x2C;		     // ���н�չ��Ϣ
	public static final int SMON_ISUP_CQR = 0x2B;		     // ��·Ⱥѯ����Ӧ��Ϣ
	public static final int SMON_ISUP_GRA = 0x29;		     // ��·Ⱥ��ԭ֤ʵ��Ϣ
	public static final int SMON_ISUP_CFN = 0x2F;		     // ������Ϣ
	
	public static final int SMON_ISUP_COT = 0x05;		     // ��ͨ��Ϣ
	public static final int SMON_ISUP_FRJ = 0x21;		     // ���ܾܾ���Ϣ
	
	public static final int SMON_ISUP_INR = 0x03;		     // ��Ϣ������Ϣ	
	
	public static final int SMON_ISUP_USR = 0x2D;		     // �û����û���Ϣ
	public static final int SMON_ISUP_FOT = 0x08;		     // ǰ�򴫵���Ϣ
	
	public static final int SMON_ISUP_RES = 0x0E;		     // �ָ���Ϣ
	public static final int SMON_ISUP_SUS = 0x0D;		     // ��ͣ��Ϣ
	
	public static final int SMON_ISUP_BLO = 0x13;		     // ������Ϣ
	public static final int SMON_ISUP_BLA = 0x15;		     // ����֤ʵ��Ϣ
	public static final int SMON_ISUP_CCR = 0x11;		     // ��ͨ����������Ϣ
	public static final int SMON_ISUP_LPA = 0x24;		     // ��·ȷ����Ϣ
	public static final int SMON_ISUP_OLM = 0x30;		     // �����Ϣ
	public static final int SMON_ISUP_RSC = 0x12;		     // ��·��ԭ��Ϣ
	public static final int SMON_ISUP_UBL = 0x14;		     // ��������Ϣ
	public static final int SMON_ISUP_UBA = 0x16;		     // ������֤ʵ��Ϣ
	public static final int SMON_ISUP_UCIC= 0x2E;		     // δװ����·ʶ������Ϣ
	
	public static final int SMON_ISUP_CGB = 0x18;		     // ��·Ⱥ������Ϣ
	public static final int SMON_ISUP_CGBA= 0x1A;		     // ��·Ⱥ����֤ʵ��Ϣ
	public static final int SMON_ISUP_CGU = 0x19;		     // ��·Ⱥ��������Ϣ
	public static final int SMON_ISUP_CGUA= 0x1B;		     // ��·Ⱥ������֤ʵ��Ϣ
	
	public static final int SMON_ISUP_GRS = 0x17;		     // ��·Ⱥ��ԭ��Ϣ
	public static final int SMON_ISUP_CQM = 0x2A;		     // ��·Ⱥѯ����Ϣ
	
	public static final int SMON_ISUP_FAA = 0x20;		     // ���ܽ�����Ϣ
	public static final int SMON_ISUP_FAR = 0x1F;		     // ����������Ϣ
	
	public static final int SMON_ISUP_PAM = 0x28;		     // ������Ϣ
	
	public static final int SMON_ISUP_UPT = 0x34;		     // �û����ֲ���
	public static final int SMON_ISUP_UPA = 0x35;		     // �û����ֿ�����
	
	public static final int SMON_ISUP_FAC = 0x33;		     // ������Ϣ
	public static final int SMON_ISUP_NRM = 0x32;		     // ������Դ����
	public static final int SMON_ISUP_IDR = 0x36;		     // ʶ������
	public static final int SMON_ISUP_IRS = 0x37;		     // ʶ����Ӧ
	public static final int SMON_ISUP_SGM = 0x38;		     // �ֶ�
	
	public static final int SMON_ISUP_CRG = 0x31;		     // �Ʒ���Ϣ
	public static final int SMON_ISUP_OPR = 0xFE;		     // ����Ա��Ϣ
	public static final int SMON_ISUP_MPM = 0xFD;		     // �ƴ�����
	public static final int SMON_ISUP_CCL = 0xFC;		     // ���йһ�
}


class ITP_SIGMonitor_TUP_MsgType      // ��������Ϣ����
{	
	public static final int SMON_TUP_IAM = 0x11;             // ��ʼ��ַ��Ϣ
	public static final int SMON_TUP_IAI = 0x21;             // ���и�����Ϣ�ĳ�ʼ��ַ��Ϣ
	public static final int SMON_TUP_SAM = 0x31;             // �����ַ��Ϣ
	public static final int SMON_TUP_SAO = 0x41;             // ����һ����ַ�źŵĺ����ַ��Ϣ	
	
	public static final int SMON_TUP_ACM = 0x14;             // ��ַ��ȫ��Ϣ
	
	public static final int SMON_TUP_SEC = 0x15;             // �����豸ӵ���ź�
	public static final int SMON_TUP_CGC = 0x25;             // ��·Ⱥӵ���ź�
	public static final int SMON_TUP_NNC = 0x35;             // �����ӵ���ź�
	public static final int SMON_TUP_ADI = 0x45;             // ��ַ��ȫ�ź�
	public static final int SMON_TUP_CFL = 0x55;             // ���й����ź�
	public static final int SMON_TUP_SSB = 0x65;             // �û�æ�ź�
	public static final int SMON_TUP_UNN = 0x75;             // �պ�
	public static final int SMON_TUP_LOS = 0x85;             // ��·�������ź�
	public static final int SMON_TUP_SST = 0x95;             // ����ר����Ϣ���ź�
	public static final int SMON_TUP_ACB = 0xA5;             // ����ܾ��ź�
	public static final int SMON_TUP_DPN = 0xB5;             // ���ṩ����ͨ·�ź�
	public static final int SMON_TUP_MPR = 0xC5;             // ���м�ǰ׺

	public static final int SMON_TUP_SLB = 0x1E;             // �û���æ�ź�
	public static final int SMON_TUP_STB = 0x2E;             // �û���æ�ź�
	
	public static final int SMON_TUP_ANU = 0x06;             // Ӧ���źţ��Ʒ�δ˵��
	public static final int SMON_TUP_ANC = 0x16;             // Ӧ���źš��շ�
	public static final int SMON_TUP_ANN = 0x26;             // Ӧ���źš����
	public static final int SMON_TUP_CBK = 0x36;             // �һ��ź�
	public static final int SMON_TUP_CLF = 0x46;             // �����ź�	
	
	public static final int SMON_TUP_RLG = 0x17;             // �ͷż໤�ź�	
	
	public static final int SMON_TUP_GSM = 0x12;             // һ��ǰ������Ϣ��Ϣ
	
	//
	public static final int SMON_TUP_COT = 0x32;             // ��ͨ�ź�
	public static final int SMON_TUP_CCF = 0x42;             // ��ͨ�����ź�
		
	public static final int SMON_TUP_GRQ = 0x13;             // һ��������Ϣ			
	
	public static final int SMON_TUP_CHG = 0x24;             // �Ʒ���Ϣ
		
	public static final int SMON_TUP_EUM = 0xF5;             // ����ĺ��������ɹ���Ϣ
			
	public static final int SMON_TUP_RAN = 0x56;             // ��Ӧ���ź�
	public static final int SMON_TUP_FOT = 0x66;             // ǰ��ת���ź�
	public static final int SMON_TUP_CCL = 0x76;             // �����û��һ��ź�
	
	public static final int SMON_TUP_BLO = 0x27;             // �����ź�
	public static final int SMON_TUP_BLA = 0x37;             // ����֤ʵ�ź�
	public static final int SMON_TUP_UBL = 0x47;             // �������ź�
	public static final int SMON_TUP_UBA = 0x57;             // ������֤ʵ�ź�
	public static final int SMON_TUP_CCR = 0x67;             // ����ͨ�����ź�
	public static final int SMON_TUP_RSC = 0x77;             // ��·��ԭ�ź�
		
	public static final int SMON_TUP_MGB = 0x18;             // ����ά����Ⱥ������Ϣ
	public static final int SMON_TUP_MBA = 0x28;             // ����ά����Ⱥ����֤ʵ��Ϣ
	public static final int SMON_TUP_MGU = 0x38;             // ����ά����Ⱥ��������Ϣ
	public static final int SMON_TUP_MUA = 0x48;             // ����ά����Ⱥ������֤ʵ��Ϣ
	public static final int SMON_TUP_HGB = 0x58;             // ����Ӳ�����ϵ�Ⱥ������Ϣ
	public static final int SMON_TUP_HBA = 0x68;             // ����Ӳ�����ϵ�Ⱥ����֤ʵ��Ϣ
	public static final int SMON_TUP_HGU = 0x78;             // ����Ӳ�����ϵ�Ⱥ��������Ϣ
	public static final int SMON_TUP_HUA = 0x88;             // ����Ӳ�����ϵ�Ⱥ������֤ʵ��Ϣ
	public static final int SMON_TUP_GRS = 0x98;             // ��·Ⱥ��ԭ��Ϣ
	public static final int SMON_TUP_GRA = 0xA8;             // Ⱥ��ԭ֤ʵ��Ϣ
	public static final int SMON_TUP_SGB = 0xB8;             // ��������Ⱥ������Ϣ
	public static final int SMON_TUP_SBA = 0xC8;             // ��������Ⱥ����֤ʵ��Ϣ
	public static final int SMON_TUP_SGU = 0xD8;             // ��������Ⱥ��������Ϣ
	public static final int SMON_TUP_SUA = 0xE8;             // ��������Ⱥ������֤ʵ��Ϣ
		
	public static final int SMON_TUP_ACC = 0x1A;             // �Զ�ӵ�������Ϣ��Ϣ
		
	public static final int SMON_TUP_MPM = 0x2C;            // �ƴ�������Ϣ
		
	public static final int SMON_TUP_OPR = 0x1D;             // ����Ա�ź�			
	
	public static final int SMON_TUP_MAL = 0x1F;            // �������׷���ź�
}


class ITP_SIGMonitor_ISDN_MsgType     // ��������Ϣ����
{
	public static final int SMON_ISDN_Alerting        = 0x01;// ����
	public static final int SMON_ISDN_Call_Proceeding = 0x02;// ���н��
	public static final int SMON_ISDN_Connect         = 0x07;// ����
	public static final int SMON_ISDN_Connect_Ack     = 0x0F;// ����֤ʵ
	public static final int SMON_ISDN_Progress        = 0x03;// ��չ
	public static final int SMON_ISDN_Setup           = 0x05;// ����
	public static final int SMON_ISDN_Setup_Ack       = 0x0D;// ����֤ʵ
	
	public static final int SMON_ISDN_Resume          = 0x26;// �ָ�
	public static final int SMON_ISDN_Resume_Ack      = 0x2E;// �ָ�֤ʵ
	public static final int SMON_ISDN_Resume_Reject   = 0x22;// �ָ��ܾ�
	public static final int SMON_ISDN_Suspend         = 0x25;// ��ͣ
	public static final int SMON_ISDN_Suspend_Ack     = 0x2D;// ��֤ͣʵ
	public static final int SMON_ISDN_Suspend_Reject  = 0x21;// ��ͣ�ܾ�
	public static final int SMON_ISDN_User_Information= 0x20;// �û���Ϣ
	
	public static final int SMON_ISDN_Disconnect      = 0x45;// ����
	public static final int SMON_ISDN_Release         = 0x4D;// �ͷ�
	public static final int SMON_ISDN_Release_Complete= 0x5A;// �ͷ����
	public static final int SMON_ISDN_Restart         = 0x46;// ��������
	public static final int SMON_ISDN_Restart_Ack     = 0x4E;// ����֤ʵ
	
	public static final int SMON_ISDN_Segment         = 0x60;// �ֶ�
	public static final int SMON_ISDN_Congestion_Ctrl = 0x79;// ӵ�����
	public static final int SMON_ISDN_Information     = 0x7B;// ��Ϣ
	public static final int SMON_ISDN_Notify          = 0x6E;// ֪ͨ
	public static final int SMON_ISDN_Status          = 0x7D;// ״̬
	public static final int SMON_ISDN_Status_Enquiry  = 0x75;// ״̬ѯ��
}

class SMON_EVENT                       // ���ص��¼���ݽṹ
{	
	public byte	   EventType;               // �¼�����
	public byte	   Protocol;                // Э������
	public byte	   SI;                      // ҵ���ʾ
	public byte	   MsgType;                 // ������Ϣ
	
	public byte	   Caller_ID[] = new byte[32];           // ���к���
	public byte	   Called_ID[] = new byte[32];           // ���к���
	public byte	   OriCalled[] = new byte[32];           // ԭʼ����
	
	public byte	   DPC[] = new byte[3];                  // Ŀ�ĵ���
	public byte	   OPC[] = new byte[3];                  // ԭ�˵���
	public byte	   Pcm;                     // CIC_Hig7
	public byte	   Chn;                     // CIC_Low5
	
	public byte	   ReleaseReason;           // ����ԭ��
	public byte	   Reserved[] = new byte[14];            // ��������
	public byte	   Unit_ID;                 // ��Դ��Ԫ
	public byte	   Port_ID;                 // ��Դ�˿�
	public byte	   TS;                      // ��Դʱ϶
	public short   DataLen;                 // ��ݳ���
	
	public byte	   RAWdata[] = new byte[2048];           // ԭʼ���
}


