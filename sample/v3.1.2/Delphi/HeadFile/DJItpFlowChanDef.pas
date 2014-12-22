unit DJItpFlowChanDef;

interface

uses
  SysUtils,Windows,DJAcsDataDef;

const ITP_MAX_MOD_TYPE_NUM           = 128;    // ���ģ����
const ITP_MAX_RELATEMOD_NUM          = 64;     //������ģ����
const ITP_MAX_SYSFUNC_NUM            = 32;     //����ģ��ϵͳ�����ӿڸ���
const ITP_MAX_DLLFUNC_NUM            = 4;      //���̶�̬��ӿں�������
const ITP_FLOW_MAX_FLOWNAME_LEN      = 40;     //��������󳤶�
const ITP_FLOW_MAX_INTERNAME_LEN     = 120;    //�û��Զ���ṹ����󳤶�

const MAX_PATH                       = 260;

const ITP_MAX_BINDRES_NUM            = 256;    //����ͨ���󶨵������Դ����
const ITP_MAX_BINDTIMER_NUM          = 64;     //����ͨ���󶨵����ʱ������
const ITP_FLOW_SHOW_INFO_SIZE        = 40;     //�û���ʾ״̬���泤��
const ITP_FLOW_SHOW_INFO_NUM         = 3;      //�û���ʾ״̬�������

Type ITP_RESOPEN_TYPE =
(
    ITP_RESOPEN_FREE = 0,
    ITP_RESOPEN_LISTEN,
	  ITP_RESOPEN_EXCLUDE
);

//����ͨ���ṹ
Type
  ITP_FLOW_CHAN = record
  
  m_u16FlowCurState  : Word;           //������ͨ����ǰ״̬
  m_u16FlowInfoIndex : Word;           //������ͨ����Ӧ�������ͱ��
  m_u16ChanIndex     : Word;           //������ͨ����Ӧͨ�����
  m_u16StartState    : Word;           //������־,0:��ֹ;1:ʹ��
	m_u16BusyState     : Word;           //Busy��־,0:Free;1:Busy
  m_PITPFlowInfo     : Pointer; //������Ϣ
  m_u16CurResNum     : Word;           //�������ͨ���󶨵ĵ�ǰ��Դ����
  m_s16ChanRetCode   : Smallint;       //����ͨ������״ֵ̬
	m_PITPResList      : Array[0..ITP_MAX_BINDRES_NUM-1] of Pointer;//�������ͨ���󶨵���Դ�����
  m_u16CurTimerNum   : Word;           //��ʱ������
	m_u8Master         : Byte;
	m_s8Rfu            : ShortInt;
  m_PITPTimerChan    : Array[0..ITP_MAX_BINDTIMER_NUM -1] of Pointer;//��ʱ�����
  m_PITPSysFunc      : Array[0..ITP_MAX_SYSFUNC_NUM-1] of PDword;            //ϵͳ����ָ��
  m_s8InfoBuf        : Array[0..ITP_FLOW_SHOW_INFO_NUM-1,0..ITP_FLOW_SHOW_INFO_SIZE-1] of ShortInt;//�û���ʾ״̬
	m_u8RelateModInfo  : Array[0..ITP_MAX_MOD_TYPE_NUM-1] of Byte; //��ص�ģ��
  m_PITPEvtPack      : ^PKG_HEAD_STRUCT; //�¼���ָ��
	m_PITPInterEvt     : ^PKG_HEAD_STRUCT; //�����ڲ��¼���ָ��
  m_PITPFlowExtData  : Pbyte;            //������չ����
  m_PITPPublicBuf    : Pbyte;            //����ʹ�û�����
end;

type
  PITP_FLOW_CHAN = ^ITP_FLOW_CHAN;

//������Ϣ�ṹ
Type
  ITP_FLOW_INFO = record

  m_u32FlowIndex : DWORD;                          //���̱��
  m_s8FlowName   : Array[0..ITP_FLOW_MAX_FLOWNAME_LEN-1] of ShortInt; //������
  m_s8DllName    : Array[0..MAX_PATH-1] of ShortInt;                  //��̬����
  m_u32StartState: DWORD;                         //����ʹ��״̬
  m_u32LoadState : DWORD;                         //���̼���״̬
  m_hdlDllHandle : PDword;                        //���̶�̬����
  m_hdlDllFunc   : Array[0..ITP_MAX_DLLFUNC_NUM-1] of PDword;         //���̶�̬��ӿں���ָ��
  m_u16FlowChanNum : Word;                        //�ö�̬���Ӧ�ĸ�������
	m_u16Resrv     : Word;
  m_PITPFlowChan : ^PITP_FLOW_CHAN;               //�ö�̬���Ӧ�ĸ�����
end;

//��Դͨ���ṹ
Type
  ITP_RES_CHAN = record
  
	m_u16ChanIndex : Word;         //��ͨ����ͨ��������
  m_u8UnitIndex  : Byte;         //��ͨ������ģ�鵥Ԫ������
	m_u8ModType    : Byte;         //��ͨ������ģ���Module_Type
  m_u8FuncType   : Byte;         //��ͨ������ģ���Func_Type
  m_u8ChanType   : Byte;         //��ͨ�������ͣ������ֻ��Interface_ch����
  m_s16ChanGroup : SmallInt;     //��ͨ�������
  m_u8BusyFlag   : Byte;         //ͨ��æ��־,0:����;1:��ռ��;2:������
  m_PITPFlowChan : Pointer; //����ͨ����Ϣ
	m_PITPListenFlowChan : PITP_FLOW_CHAN; //��������ͨ��
  m_s8InfoBuf          : Array[0..ITP_FLOW_SHOW_INFO_NUM-1,0..ITP_FLOW_SHOW_INFO_SIZE-1] of ShortInt;//�û���ʾ״̬
  m_u8RelateModInfo    : Array[0..ITP_MAX_RELATEMOD_NUM-1] of Byte;     //�����Դ��ص�ģ��
	m_s8MachineId        : ShortInt;                                //�����ID
	m_s8Resrv            : Array[0..ITP_MAX_RELATEMOD_NUM-2] of ShortInt;
end;

//��ʱ���ṹ
Type
  PTIMERFUNC=procedure(p:PInteger);cdecl;
  
  ITP_FLOW_TIMER = record
  
  m_u64Time      : Double;        //����ʱ��
  m_u32Ticks     : DWord;         //�������
  m_u8StartFlag  : Byte;          //������־
	m_u8Caller     : Byte;          //������:�û�DLL����ģ�鱾��
	m_Resrv        : Array[0..1] of Byte;
  m_PITPFlowChan : Pointer;//����ͨ��ָ��
  m_PITPTimerFunc: PTIMERFUNC;    //��ʱ������
	m_u16ChanIndex : Word;          //��������������Ϊ��������ת�����ֵ��¼�����Ϊ��Դ�����һ��
  m_u8UnitIndex  : Byte;
	m_u8ModType    : Byte;
end;

//�������Բ�ͨѶ�¼��ṹ
Type
  FLOW_INTERDATA_HEAD = record
	m_PkgHead     : PKG_HEAD_STRUCT;                    //�¼���ͷ
	m_SrcCallID   : CallID_t;                           //Դ����
	m_destCallID  : CallID_t;                           //Ŀ������
	m_u32CmdType  : DWORD;                              //�Զ�����������
	m_u32InterNameLen : DWORD;                          //�û��ṹ������
	m_s8InterName : Array[0..ITP_FLOW_MAX_INTERNAME_LEN-1] of ShortInt; //�û��ṹ��
	m_u32InterDataSize : DWORD;                         //�û��Զ���ṹ��С
end;

implementation

end.
