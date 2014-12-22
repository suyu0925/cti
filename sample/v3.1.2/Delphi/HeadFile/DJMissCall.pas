unit DJMissCall;

interface

uses
  SysUtils, Variants, Messages, Windows;
  
const DJSSM_CALL_GENERATE			= $01;	// ���з���
const DJSSM_CALL_CONNECT			= $02;	// ͨ������
const DJSSM_CALL_DISCONNECT		= $03;	// ͨ���Ͽ�
const DJSSM_CALL_INFO				  = $04;	// ������Ϣ
const DJSSM_CALL_INFO_ACM			= $05;	// �յ�ACM��Ϣ

const FORCE_MODE					= $01;	// ǿ������

// TUP��æ�ź�
const CALLEE_SLB					= $1E;	// �����л�æ
const CALLEE_SSB					= $65;	// ����æ
const CALLEE_STB					= $2E;	// ���г���æ

const CALLEE_LOS					= $85;	// ��·�˳�����
const CALLEE_CGC					= $25;	// ��·Ⱥӵ��
const CALLEE_ADI					= $45;	// ��ַ��ȫ
const CALLEE_SEC					= $15;	// �����豸ӵ��
const CALLEE_UNN					= $75;	// δ��������ź�
const CALLEE_SST					= $95;	// �ر��ź���
const CALLEE_EUM					= $F5;	// ���������ɹ������䣩

// TUP�����ź�
const CALLINF_CLF					= $46;	// ǰ�����
const CALLINF_CBK					= $36;	// �������

// ISUP�����ͷ�ԭ��ֵ
Type CAUSE_VALUE =
(
	RSN_UNALLOCATED_NUMBER   = $01,		//�պ�
	RSN_NORMAL_CALL_CLEARING = $10,	  //�����ĺ������
	RSN_USER_BUSY            = $11,		//�û�æ
	RSN_NO_USER_RESPONDING   = $12,		//���û���Ӧ����ʱû���յ�ACM
	RSN_USER_ALERTING_NO_ANSWER = $13, //������Ӧ�𣬳�ʱδժ��
	RSN_CALL_REJECTED        = $15,		//���оܾ�
	RSN_INCOMPLETE_NUMBER    = $1c,		//�������ĺ���
	RSN_NORMAL_NO_SET        = $1f,		//������δ�涨
	RSN_NO_CIRCUIT_CHANNELAVAILABLE = $22,           //�޿��õĵ�·
	RSN_REQUESTEDCIRCUIT_CHANNEL_NOTAVAILABLE = $2c, //����ĵ�·������
	RSN_RECOVERY_ON_TIME_EXPIRY = $66,	//��ʱ����ʱ�ָ�

	RSN_LOCAL_RLC   = $20,			//�����ͷŵ�·
	RSN_RECEIVE_RSC = $21 			//��·��ԭ
);

const ERR_DMSU_SOCKFAIL			    = 1000;//-1		// ������DMSU����socketʧ��
const ERR_DMSU_CONNECTFAIL		  = 2000;//-2		// ����DMSUʧ��
const ERR_DMSU_INITRPARSERFAIL	= -3;		// ��ʼ����Ϣ��������ʧ��
const ERR_DMSU_INITFRAGMENTFAIL	= -4;		// ��ʼ�����ݽ�������ʧ��
const ERR_DMSU_INITRECVFAIL		  = -5;		// ��ʼ�����ն���ʧ��
const ERR_DMSU_STARTRECVTFAIL		= -6;		// ���������߳�ʧ��
const ERR_DMSU_STARTHEARTTFAIL	= -7;		// ���������߳�ʧ��
const ERR_DMSU_STARTPARSERTFAIL = -8;		// ���������߳�ʧ��
const ERR_DMSU_NOTEXISTS			  = -9;		// ���Ӳ���
const ERR_DMSU_CONNECTIONOK		  = -10;		// ��ǰ��������

const ERR_EVT_NODATA				    = -1;		// û�н��յ�����
const ERR_EVT_GETDATAFAIL			  = -2;		// ��ȡ����ʧ��
const ERR_EVT_DATANOTENOUGH		  = -3;		// ���ݳ��Ȳ���
const ERR_EVT_NOTEXISTS			    = -4;		// ���Ӳ�����
const ERR_EVT_DISCONNECT			  = -5;		// ��DMSU�����ӶϿ�

Type
  tSockInfo = record
	Addr    : Array[0..15] of ShortInt;
	Port    : Word;
	BufSize : DWORD;
	RecvBufSize : DWORD;
	UnitID  : Byte;
end;

Type
  tMonEvt = record
	caller_id : Array[0..31] of ShortInt;			// ���к���
	callee_id : Array[0..31] of ShortInt;			// ���к���
	original_callee_id : Array[0..31] of ShortInt;// ԭ���к���
	Even       : Byte;		  // �¼�ָʾ��
	LocalPcmID : Byte;	    // ���ػ����������PCM��
	pcm        : Byte;			// �������������м̺�
	chn        : Byte;			// ������������ʱ϶��
	Protocol   : Byte;		  // Э������
	SubProtocol: Byte;	    // Э��������
	ToneID     : Integer;		// ������
	ReleaseReason : Byte;   // ����ԭ��ֵ
	MsgType    : Byte;		  // ��Ϣ����
	DPC        : Integer;
	OPC        : Integer;
	DataLen    : Integer;					        // ԭʼ������
	OriginalData : Array[0..299] of Byte; // ԭʼ�� CR20061116_01
end;

// ��Ϣ����
const SYS_INFO_BUFFER			 =	00;		// ��Ϣ������Ϣ

/////////////////////////////////////////////////////////////////////////
// ������ʾ
const SYS_NOT_EXISTS			 =	-1;		// ָ����DMSU�豸������
const SYS_MAX_INFO_LEN		 =	128;		// ��Ϣ������󳤶�

// �ṹ����
Type
  tSysBufInfo = record
	BuffID  : byte;
	BufSize : Integer;
	InUse   : Integer;
end;

Type
  tSysState = record
	sysID : Byte;						// ������Ϣ������Դ
	infoLen : Byte;					// ��Ϣ����
	info : Array[0..SYS_MAX_INFO_LEN-1] of Byte;		// ��Ϣ����
end;

implementation

end.
