package DJKeygoe;

public class ItpFlowChanDef {
	public void PTIMERFUNC(){
		
	}
}

class ITP_RESOPEN_TYPE
{
	public static final int ITP_RESOPEN_FREE 	 = 0;
	public static final int ITP_RESOPEN_LISTEN   = 1;
	public static final int ITP_RESOPEN_EXCLUDE	 = 2;
}

//������Ϣ�ṹ
class ITP_FLOW_INFO
{
    public int     	 m_u32FlowIndex;                          //���̱��
    public byte      m_s8FlowName[] = new byte[40]; //������
    public byte      m_s8DllName [] = new byte[260];                   //��̬����	
    public int       m_u32StartState;                         //����ʹ��״̬
    public int       m_u32LoadState;                          //���̼���״̬
    public int       m_hdlDllHandle[];                          //���̶�̬����
    public int       m_hdlDllFunc[][] = new int[4][];       //���̶�̬��ӿں���ָ��
    public short     m_u16FlowChanNum;                        //�ö�̬���Ӧ�ĸ�������
    public short     m_u16Resrv;
    public ITP_FLOW_CHAN m_PITPFlowChan[];                     //�ö�̬���Ӧ�ĸ�����
}

//����ͨ���ṹ
class ITP_FLOW_CHAN
{
	public short           m_u16FlowCurState;           //������ͨ����ǰ״̬
	public short           m_u16FlowInfoIndex;          //������ͨ����Ӧ�������ͱ��
	public short           m_u16ChanIndex;              //������ͨ����Ӧͨ�����
	public short           m_u16StartState;             //������־,0:��ֹ;1:ʹ��
	public short           m_u16BusyState;              //Busy��־,0:Free;1:Busy
    public ITP_FLOW_INFO   m_PITPFlowInfo;              //������Ϣ
    public short           m_u16CurResNum;              //�������ͨ���󶨵ĵ�ǰ��Դ����
    public short           m_s16ChanRetCode;            //����ͨ������״ֵ̬
    public ITP_RES_CHAN    m_PITPResList[] = new ITP_RES_CHAN[256];//�������ͨ���󶨵���Դ�����
	public short           m_u16CurTimerNum;            //��ʱ������
	public byte            m_u8Master;
	public byte            m_s8Rfu;
	public ITP_FLOW_TIMER  m_PITPTimerChan[] = new ITP_FLOW_TIMER[64];//��ʱ�����
    public Integer         m_PITPSysFunc[] = new Integer[32];    //ϵͳ����ָ��
    public byte            m_s8InfoBuf[][] = new byte[3][40];//�û���ʾ״̬
    public byte            m_u8RelateModInfo[] = new byte[128]; //��ص�ģ��
    public PKG_HEAD_STRUCT m_PITPEvtPack;                 //�¼���ָ��
    public PKG_HEAD_STRUCT m_PITPInterEvt;                //�����ڲ��¼���ָ��
	public Byte            m_PITPFlowExtData;            //������չ����
	public Byte            m_PITPPublicBuf;              //����ʹ�û�����
}

//��Դͨ���ṹ
class ITP_RES_CHAN
{
	public short	 m_u16ChanIndex;        //��ͨ����ͨ��������
    public byte 	 m_u8UnitIndex;         //��ͨ������ģ�鵥Ԫ������
    public byte 	 m_u8ModType;           //��ͨ������ģ���Module_Type
    public byte 	 m_u8FuncType;          //��ͨ������ģ���Func_Type        
    public byte 	 m_u8ChanType;          //��ͨ�������ͣ������ֻ��Interface_ch����
    public short 	 m_s16ChanGroup;        //��ͨ�������
    public byte 	 m_u8BusyFlag;          //ͨ��æ��־,0:����;1:��ռ��;2:������
    public ITP_FLOW_CHAN  m_PITPFlowChan; //����ͨ����Ϣ
	public ITP_FLOW_CHAN  m_PITPListenFlowChan; //��������ͨ��
	public byte     m_s8InfoBuf[][] = new byte[3][40];//�û���ʾ״̬
    public byte     m_u8RelateModInfo[] = new byte[64];     //�����Դ��ص�ģ��
    public byte     m_s8MachineId;                                //�����ID 
	public byte     m_s8Resrv[] = new byte[63];
}

//��ʱ���ṹ
class ITP_FLOW_TIMER
{	
    public double     m_u64Time;              //����ʱ��
    public int	      m_u32Ticks;             //�������
    public byte       m_u8StartFlag;          //������־
    public byte       m_u8Caller;             //������:�û�DLL����ģ�鱾��
    public byte       m_Resrv[] = new byte[2];
    public ITP_FLOW_CHAN  	 m_PITPFlowChan;   //����ͨ��ָ��
    public ItpFlowChanDef    m_PITPTimerFunc = new ItpFlowChanDef();       //��ʱ������
	public short	  m_u16ChanIndex;        //��������������Ϊ��������ת�����ֵ��¼�����Ϊ��Դ�����һ��
	public byte	   	  m_u8UnitIndex;         //
	public byte	   	  m_u8ModType;           //
}