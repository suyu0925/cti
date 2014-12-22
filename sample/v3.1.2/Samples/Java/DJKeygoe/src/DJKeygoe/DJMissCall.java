package DJKeygoe;

public class DJMissCall {
	public static final int DJSSM_CALL_GENERATE			= 0x01;	// ���з���
	public static final int DJSSM_CALL_CONNECT			= 0x02;	// ͨ������
	public static final int DJSSM_CALL_DISCONNECT		= 0x03;	// ͨ���Ͽ�
	public static final int DJSSM_CALL_INFO				= 0x04;	// ������Ϣ
	public static final int DJSSM_CALL_INFO_ACM			= 0x05;	// �յ�ACM��Ϣ
		
	public static final int FORCE_MODE					= 0x01;	// ǿ������

	// TUP��æ�ź�
	public static final int CALLEE_SLB					= 0x1E;	// �����л�æ	
	public static final int CALLEE_SSB					= 0x65;	// ����æ
	public static final int CALLEE_STB					= 0x2E;	// ���г���æ

	public static final int CALLEE_LOS					= 0x85;	// ��·�˳�����
	public static final int CALLEE_CGC					= 0x25;	// ��·Ⱥӵ��
	public static final int CALLEE_ADI					= 0x45;	// ��ַ��ȫ
	public static final int CALLEE_SEC					= 0x15;	// �����豸ӵ��
	public static final int CALLEE_UNN					= 0x75;	// δ��������ź�
	public static final int CALLEE_SST					= 0x95;	// �ر��ź���
	public static final int CALLEE_EUM					= 0xF5;	// ���������ɹ������䣩

	// TUP�����ź�
	public static final int CALLINF_CLF					= 0x46;	// ǰ�����
	public static final int CALLINF_CBK					= 0x36;	// �������
	
	
	public static final int  ERR_DMSU_SOCKFAIL			= 1000;//-1		// ������DMSU����socketʧ��
	public static final int  ERR_DMSU_CONNECTFAIL		= 2000;//-2		// ����DMSUʧ��
	public static final int  ERR_DMSU_INITRPARSERFAIL	= -3;		// ��ʼ����Ϣ��������ʧ��
	public static final int  ERR_DMSU_INITFRAGMENTFAIL	= -4;		// ��ʼ�����ݽ�������ʧ��
	public static final int  ERR_DMSU_INITRECVFAIL		= -5;		// ��ʼ�����ն���ʧ��
	public static final int  ERR_DMSU_STARTRECVTFAIL	= -6;		// ���������߳�ʧ��
	public static final int  ERR_DMSU_STARTHEARTTFAIL	= -7;		// ���������߳�ʧ��
	public static final int  ERR_DMSU_STARTPARSERTFAIL  = -8;		// ���������߳�ʧ��
	public static final int  ERR_DMSU_NOTEXISTS			= -9;		// ���Ӳ���
	public static final int  ERR_DMSU_CONNECTIONOK		= -10;		// ��ǰ��������
		
	public static final int  ERR_EVT_NODATA				= -1;		// û�н��յ�����
	public static final int  ERR_EVT_GETDATAFAIL		= -2;		// ��ȡ����ʧ��
	public static final int  ERR_EVT_DATANOTENOUGH		= -3;		// ���ݳ��Ȳ���
	public static final int  ERR_EVT_NOTEXISTS			= -4;		// ���Ӳ�����
	public static final int  ERR_EVT_DISCONNECT			= -5;		// ��DMSU�����ӶϿ�

////////////////////////////////////////////////////////////////////////////
	// ����ԭʼ��������ͷ�ʽ  CR20061116_01

	// ��������
	public static final int  PRO_TRANS		 = 0x00;	// ͸��
	public static final int  PRO_PARSER		 = 0x01;	// ����
	public static final int  PRO_BOTH		 = 0x02;	// ����������

	// ��������
	public static final int  PRO_ADD		 = 0x00;	// ���
	public static final int  PRO_REMOVE		 = 0x01;	// �Ƴ�
	public static final int  PRO_MODIFY		 = 0x02;	// �޸�
	
/////////////////////////////////////////////////////////////////////////
	// ϵͳ״̬��Ϣ CR20061116_02
	//

	/////////////////////////////////////////////////////////////////////////
	// ��Ϣ����
	public static final int SYS_INFO_BUFFER				= 00;		// ��Ϣ������Ϣ

	/////////////////////////////////////////////////////////////////////////
	// ������ʾ
	public static final int SYS_NOT_EXISTS				= -1;		// ָ����DMSU�豸������
	public static final int SYS_MAX_INFO_LEN			= 128;		// ��Ϣ������󳤶�
}

// ISUP�����ͷ�ԭ��ֵ
class CAUSE_VALUE
{
	public static final int RSN_UNALLOCATED_NUMBER 		= 0x01;		//�պ�
	public static final int RSN_NORMAL_CALL_CLEARING 	= 0x10;	//�����ĺ������
	public static final int RSN_USER_BUSY 				= 0x11;				//�û�æ
	public static final int RSN_NO_USER_RESPONDING 		= 0x12;		//���û���Ӧ����ʱû���յ�ACM
	public static final int RSN_USER_ALERTING_NO_ANSWER = 0x13; //������Ӧ�𣬳�ʱδժ��
	public static final int RSN_CALL_REJECTED 			= 0x15;			//���оܾ�
	public static final int RSN_INCOMPLETE_NUMBER 		= 0x1c;		//�������ĺ���
	public static final int RSN_NORMAL_NO_SET 			= 0x1f;			//������δ�涨
	public static final int RSN_NO_CIRCUIT_CHANNELAVAILABLE 			= 0x22;//�޿��õĵ�·
	public static final int RSN_REQUESTEDCIRCUIT_CHANNEL_NOTAVAILABLE 	= 0x2c; //����ĵ�·������
	public static final int RSN_RECOVERY_ON_TIME_EXPIRY = 0x66;	//��ʱ����ʱ�ָ�

	public static final int RSN_LOCAL_RLC 				= 0x20;				//�����ͷŵ�·
	public static final int RSN_RECEIVE_RSC 			= 0x21;				//��·��ԭ
}

class tSockInfo
{
	public byte  Addr[] = new byte[16];
	public short Port;
	public long  BufSize;
	public long  RecvBufSize;
	public char  UnitID;
}

class tMonEvt
{
	public byte caller_id[]		   = new byte[32];			// ���к���
	public byte callee_id[]		   = new byte[32];			// ���к���
	public byte original_callee_id[] = new byte[32];// ԭ���к���
	public byte Event;		// �¼�ָʾ��
	public byte LocalPcmID;	// ���ػ����������PCM��
	public byte pcm;			// �������������м̺�
	public byte chn;			// ������������ʱ϶��
	public byte Protocol;		// Э������
	public byte SubProtocol;	// Э�������� 
	public int  ToneID;		// ������
	public byte ReleaseReason;// ����ԭ��ֵ
	public byte MsgType;		// ��Ϣ����
	public int  DPC;
	public int  OPC; 	
	public int  DataLen;					 // ԭʼ������
	public byte OriginalData[] = new byte[300]; // ԭʼ�� CR20061116_01
}


/////////////////////////////////////////////////////////////////////////
// �ṹ����
class tSysBufInfo{
	public byte BuffID;
	public int  BufSize;
	public int  InUse;	
}

class tSysState
{
	public byte sysID;						// ������Ϣ������Դ
	public byte infoLen;						// ��Ϣ����
	public byte info[] = new byte[128];		// ��Ϣ����
}

// end CR20061116_02


// Э�鹤��ģʽ
class tProtocolMode
{
	public byte	Protocol;
	public byte WorkMode;
}

// END CR20061116_01

// CR20070830_001
class DMSU_LOG
{
	public int LogType;
	public long Param1;
}
