unit DJITPMsgPublic;

interface

uses
  SysUtils,Windows, DJAcsDataDef;

//ͨѶ�������ֶεĶ���
const PKG_EXTEND_NORMAL     = $00;
const PKG_EXTEND_ERROR      = $01;
const PKG_EXTEND_CONFIG     = $02;
const PKG_EXTEND_INTERFACE  = $03;
// ����˫������ʱ���ְ��ķ��ͷ���
const PKG_EXTEND_UPPER	    = $04;		// �ϼ�ģ���
const PKG_EXTEND_LOWER	    = $05;		// �¼�ģ���

const ITP_FLOW_MAX_INTERNAME_LEN     = 120;    //�û��Զ���ṹ����󳤶�
//ͨѶ��Ϣ��ͷ

//�������Բ�ͨѶ�¼��ṹ
Type
  FLOW_INTERDATA_HEAD = record
	m_PkgHead          : PKG_HEAD_STRUCT;               //�¼���ͷ
	m_SrcCallID        : CallID_t;                      //Դ����
	m_destCallID       : CallID_t;                      //Ŀ������
	m_u32CmdType       : DWORD;                         //�Զ�����������
  m_u32InterNameLen  : DWORD;                         //�û��ṹ������
	m_s8InterName      : Array[0..ITP_FLOW_MAX_INTERNAME_LEN-1] of ShortInt; //�û��ṹ��
	m_u32InterDataSize : DWORD;                        //�û��Զ���ṹ��С
end;

Type PACKAGE_TYPE =
(
	PKG_CMD = $5A,         // �������ݰ�
	PKG_EVT = $A5          // �¼����ݰ�
);

//************���ù���ģ����Ϣ��*****************


//ģ��״̬����
{˵��:
ģ��״̬��һ��DJ_U16���Ͷ��壬����DJ_U16 u16ModuleStates
����bit0 = 1,��ʾģ���Ѿ���ʼ��, bit0 = 0 ��ʾģ��δ��ʼ�������ͷ�
����bit1 = 1,��ʾģ���Ѿ�����  , bit1 = 0 ��ʾģ���Ѿ�ֹͣ
����bit2 = 1,��ʾģ��ȫ������  , bit2 = 0 ��ʾģ�黹�в��ֻ�ȫ��δ����
����bit3 = 1,��ʾģ���ѱ�����  , bit3 = 0 ��ʾģ��δ������
����bit4 = 1,��ʾģ���Ѿ�����  , bit4 = 0 ��ʾģ��Ͽ�����
����bit5 = 1,��ʾģ������ֹͣ  ,
����bit6 = 1,��ʾģ����������  , bit6 = 0,��ʾģ��û������  ,
����9��bitλ��ʱû���õ�
}

const MODULE_INIT       = $01;    //ģ���ѳ�ʼ��
const MODULE_START      = $02;    //ģ��������
const MODULE_RELATE     = $04;    //ģ����ȫ�������ϼ�ģ�����
const MODULE_MONITOR    = $08;    //ģ���ѱ�����
const MODULE_CONNECT    = $10;    //ģ��������
const MODULE_STOPPING   = $20;    //ģ������ֹͣ
const MODULE_ISTUNING   = $40;    //��������ģ��
const MODULE_SETSTANDBY = $80;    //��Ҫ��������ģ��

Type MOD_STATE =
(
	ITP_REPORT_MODSTATE_NORMAL    = $0,
	ITP_REPORT_MODSTATE_COMMBAD   = $1
);

//����������
Type
  ITP_HEART_TIME = record
	m_u32time         : DWORD;
	m_u32date         : DWORD;
	m_u16ModuleStates : WORD;
	m_u8HotState      : Byte;
	m_u8HotWorkState  : Byte;
end;

//���͸�DSP��������Ϣ

const MAX_IP_NUM  = 5;

Type
  ITP_DSP_HOTSTANDBY_INFO = record
	m_u8IPNum      : Byte;                          //IP ��Ŀ
	m_u8Reverse    : Array[0..2] of Byte;
	m_u32IPAddress : Array[0..MAX_IP_NUM-1] of DWORD;      //��ģ���IP��
end;


//�ӱ���config server��������config server����ģ����Ϣ�ṹ
Type
  CONFIG_MODULE_STRUCT = record
  m_u8ModuleType : Byte;         //ģ������
	m_u8UnitID     : Byte;         //ģ��ĵ�ԪID
	m_u8Reverse    : Array[0..1] of Byte;

  m_u32IPAddress : DWORD;
	m_u32Port      : DWORD;
end;


//������config server��ģ�鷢���л���Ϣ
Type
  CONFIG_HOTSTANDBY_STRUCT = record
	m_u8HOTState     : Byte;    //���öԷ�������, 0 ��ģ�� ��1 ��ģ��
	m_u8RetVal       : Byte;    //�����Ƿ�ɹ�  1 ʧ��  1 �ɹ�
	m_u8HotWorkState : Byte;    //������������״̬
  m_u8Reverse      : Byte;
end;


Type
  ITP_MODULE_EXCEPTION = record
	m_u8ExceptionType : Byte;	//ģ���쳣����  0��ͨѶ�쳣��1���ڲ��߼��쳣
	m_u8ModuleType    : Byte;	//�Ͽ�ģ������
	m_u8UnitID        : Byte;	//�Ͽ�ģ��ID
	m_u32IPAddress    : DWORD;	//�Ͽ�ģ��IP
end;

Type
  ITP_MODSTATE_REPORT = record
	m_u16ModState  : Word;   //ģ���쳣����  0�����쳣��1��ͨѶ�쳣��2���ڲ��߼��쳣
	m_u8ModuleType : Byte;   //�Ͽ�ģ������
	m_u8UnitID     : Byte;   //�Ͽ�ģ��ID
	m_u32IPAddress : DWORD;  //�Ͽ�ģ��IP
end;

//����ģ������
//ϵͳ������Ϣ(����ģ����Ϣ)

Type
  ITP_MODULE_ADDR = record
	m_u8ModuleType : Byte;			//ģ������
  m_u8UnitID     : Byte;			//ģ�鵥ԪID
	m_u16Port      : WORD;			//ģ�����ӵĶ˿ں�
  m_u32IPAddress : DWORD;			//ģ��IP��ַ
end;


Type
  ITP_MODULE_RELATE_ADDR = record
	m_u8ModuleType : Byte;			//ģ������
  m_u8UnitID     : Byte;				//ģ�鵥ԪID
	m_u16Port      : Word;				//ģ�����ӵĶ˿ں�
  m_u32IPAddress : DWORD;			//ģ��IP��ַ
	m_u32RelateFlag: DWORD;        //���ӷ���
end;

Type
  ITP_MOD_VALIDITY_DATA = record
	m_s8Username : Array[0..31] of ShortInt; // ��Ȩ�û�
	m_s8Password : Array[0..31] of ShortInt; // ��Ȩ����
end;

//���ģ�����ݰ�
Type
  ITP_MONITOR_ADDR = record
	m_u8ModuleType : Byte;      //ģ������
  m_u8UnitID : Byte;          //ģ�鵥ԪID
	m_u16ChanID : Word;         //ģ��ͨ����
	m_u16DebugLevel : Word;     //ģ���ؼ���
  m_u16UdpPort : Word;        //ģ�����ӵ�UDP�˿ں�
  m_u32IPAddress : DWORD;     //ģ��IP��ַ
	m_u32Reserved : DWORD;      //�����ֶ�
end;

const MAX_MACADDR_STR_LEN     = $14;     //������ַ�ַ����������ֵ
const MAX_MODULENAME_STR_LEN	= $10;     //ģ�����ַ����������ֵ
const MAX_ERRMSG_LEN          = $60;     //������Ϣ�ַ����������ֵ

//��������ù���֮�����Ϣ��
Type
  ITP_MODULE_STRUCT = record
  m_u8ModuleType : Byte;        //ģ������
  m_u8UnitID     : Byte;        //��ԪID
  m_u8IsEnable   : Byte;        //�Ƿ�ʹ��ģ�� 0:��ʹ��; 1:ʹ��
  m_u8DSPType    : Byte;        //DSP����
  m_u16ModuleStates : Word;     //ģ��״̬
  m_s8ModuleName    : Array[0..MAX_MODULENAME_STR_LEN-1] of ShortInt; //ģ����
  m_s8pMACAddress   : Array[0..MAX_MACADDR_STR_LEN-1] of ShortInt;    //������ַ����DSPΪȫ0
  m_u32Version      : DWORD;    //ģ��汾��
  m_u32IPAddress    : DWORD;    //IP��ַ
  m_u32Port  : DWORD;           //����˿�
	m_u32Param : DWORD;           //��������
end;

//���������
Type
  ITP_ERROR_STRUCT = record
  m_s32ErrorCode : Integer;
  m_s8pErrMsg    : Array[0..MAX_ERRMSG_LEN-1] of ShortInt;
end;

//���ù����͸�VOIPģ�飬No2IP���óɹ�֪ͨ��Ϣ
Type
  ITP_ADDIP_OK_NOTIFY_STRUCT = record
  m_u8ExcuteResult : byte;
	m_u8Reserve      : Array[0..6] of Byte;
end;

//���ù����͸�FLOWģ�飬��֪�����Ѿ�����������֪ͨ��Ϣ
Type
  ITP_SLAVE_WORK_NOTIFY_STRUCT = Record
  m_u8WorkSate : Byte;              //0:�����쳣; 1: ��������
	m_u8Reserve  : Array[0..6] of Byte;
end;



//**************************************
//ITP���ù���ģ���ȡSNMP���ݵ���Ϣ��

//��ͨ��״̬�����cfgSrv�����̣�
Type
  ITP_CH_STATE_RESULT = record
	m_u8UnitID  : Word;				//��ԪID
	m_uReserved : Word;				//����
	m_u16State  : Array[0..127] of DWORD;			//DSP������ͨ��״̬
	m_u8DeviceSubType : Array[0..127] of Byte;//DSP���豸������
end;

//��Q931״̬�����cfgSrv��Q931��
Type
  ITP_Q931_STATE_RESULT = record
	m_u8UnitID : Word;				//��ԪID
	m_u8PcmNum : Word;				//PCM��
	m_u8LinkState   : Array[0..3] of Byte;		//����״̬,����DEF�ļ�
	m_u8RestartFlag : Array[0..3] of Byte;		//������־
end;

//����״̬�����cfgSrv��proxy��
Type
  ITP_PC_STATE_RESULT = record
	m_u32CpuIdle  : Array[0..7] of DWORD;			//����CPU
	m_u32MemFree  : DWORD;			//�����ڴ�
	m_u32SwapFree : DWORD;			//���н���
	m_u32HDFree   : DWORD;			//����Ӳ��
end;

//mainmod�¼����ӹ�ϵ�����cfgSrv��mainmod��
Type
  ITP_MAINMOD_DOWNRELATE_RESULT = record
	m_u8ModuleType : Byte;		//ģ������
  m_u8UnitID : Byte;				//ģ�鵥ԪID
	m_u8RelateIndex : Byte;		//ģ��Ĺ�����,0-255
	m_u8RelateState : Byte;		//����״̬,0:����,1:�Ͽ�
end;


//**************************************
//ITP���ý��������ģ�����Ϣ��


//���ڵ��ʶ
const ITP_ROOT_NODE   = $01;

//�ڵ����ͣ�����޴˽ڵ㣬�򷵻�NODE_NONE
const NODE_NONE       = $00;
const NODE_PARENT     = $01;     //��֧����
const NODE_RDONLY     = $02;     //ֻ������
const NODE_RDWR       = $03;     //�ɶ�д����
const NODE_SHOWONLY   = $04;     //ֻ���б�����
const NODE_RDWR_TABLE = $05;     //�ɶ�д�б�����

//�ڵ㶨����Ϣ
Type
  ITP_INTERFACE_NODE_DATA = record
	m_u8NodeType       : Byte;
	m_s8ConfigName     : Array[0..30] of ShortInt;
	m_s8ConfigFileName : Array[0..31] of ShortInt;
	m_s32NodeMsgCode   : Integer;
  m_s32ConfigNum     : Integer;
end;


//�ӽڵ��ʶ�б�
Type
  ITP_INTERFACE_SUBNODE_DATA = record
	m_u8NodeType     : Byte;
	m_s8ConfigName   : Array[0..30] of ShortInt;
	m_s32NodeMsgCode : Integer;
end;


//��д�ڵ�����
Type
  ITP_INTERFACE_DONE_DATA = record
	m_s32IsWriteini : Integer;
	m_s32NodeMsgCode : Integer;
	m_u16FisrtData : Word;
	m_u16DataNum : Word;
end;


//д�ڵ����ݽ��
Type
  ITP_INTERFACE_WRDATA_MSG = record
	m_s32NodeMsgCode : Integer;
	m_s32RetCode     : Integer;
end;

//���ڵ�������
Type
  ITP_INTERFACE_RDATA_MSG = record
	m_u8NodeType : Byte;
	m_s8ConfigFileName : Array[0..30] of ShortInt;
	m_s32NodeMsgCode : Integer;
	m_u16FisrtData : Word;
	m_u16DataNum : Word;
end;
//**************************************


////ITP���ý����DSPģ����й̼����µ���Ϣ��

const ERASE_PASSWORD = $87654321;      //DSP FLASH��������
const MAX_DATA_BLOCK_LENGTH   = 4000;  //д��FLASH���ݵ���󳤶�

//��FLASH����
Type
  ITP_FLASH_READ = record
  m_u32AddrOffset : DWORD;
	m_u32ByteNum    : DWORD;
end;

//дFLASH����
Type
  ITP_FLASH_WRITE = record
  m_u32AddrOffset : DWORD;
	m_u32ByteNum    : DWORD;
	m_u8pData       : Array[0..MAX_DATA_BLOCK_LENGTH-1] of Byte;
end;

//��FLASH�������
Type
  ITP_FLASH_READ_MSG = record
	m_u32DataLen : DWORD;
	m_u8pData    : Array[0..MAX_DATA_BLOCK_LENGTH-1] of Byte;
end;

//дFLASH�������
Type
  ITP_FLASH_WRITE_MSG = record
  m_u32WriteStates : DWORD;
	m_u32CheckSum : DWORD;
end;
//*******************************************************


//******************ý�崦�����Ϣ������***********************************
const   MSG_MEDIA						  = $3000;

const   MSG_MEDIA_DEV					= MSG_MEDIA + $100;
const   MSG_MEDIA_DEV_OPEN		= MSG_MEDIA_DEV + $001;
const   MSG_MEDIA_DEV_CLOSE		= MSG_MEDIA_DEV + $002;
const   MSG_MEDIA_DEV_STOP		= MSG_MEDIA_DEV + $003;

const   MSG_MEDIA_PLAYREC			= MSG_MEDIA_DEV + $100;
const   MSG_MEDIA_PLAYREC_PLAY		  = $001;
const   MSG_MEDIA_PLAYREC_RECORD		= $002;

const   MSG_MEDIA_UT					= MSG_MEDIA_PLAYREC + $100;

const   MSG_MEDIA_FSK					= MSG_MEDIA_UT + $100;

const   MSG_MEDIA_EC					= MSG_MEDIA_FSK + $100;

const   MSG_MEDIA_DTMF				= MSG_MEDIA_EC + $100;

const   MSG_MEDIA_CA					= MSG_MEDIA_DTMF + $100;

const   MSG_MEDIA_DIAL				= MSG_MEDIA_CA + $100;

const   MSG_MEDIA_PARM				= MSG_MEDIA_DIAL + $100;

const   MSG_MEDIA_CONF				= MSG_MEDIA_PARM + $100;

const   MSG_MEDIA_MS					= MSG_MEDIA_CONF + $100;
const   MSG_MEDIA_MS_SEND			= MSG_MEDIA_MS + $001;
const   MSG_MEDIA_MS_RECV			= MSG_MEDIA_MS + $002;
const   MSG_MEDIA_MS_VLDRSC		= MSG_MEDIA_MS + $003;



const   MSG_MEDIA_END         = $3FFF;

implementation

end.
