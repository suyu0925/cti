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

//流程信息结构
class ITP_FLOW_INFO
{
    public int     	 m_u32FlowIndex;                          //流程标号
    public byte      m_s8FlowName[] = new byte[40]; //流程名
    public byte      m_s8DllName [] = new byte[260];                   //动态库名	
    public int       m_u32StartState;                         //流程使能状态
    public int       m_u32LoadState;                          //流程加载状态
    public int       m_hdlDllHandle[];                          //流程动态库句柄
    public int       m_hdlDllFunc[][] = new int[4][];       //流程动态库接口函数指针
    public short     m_u16FlowChanNum;                        //该动态库对应的副本个数
    public short     m_u16Resrv;
    public ITP_FLOW_CHAN m_PITPFlowChan[];                     //该动态库对应的副本表
}

//流程通道结构
class ITP_FLOW_CHAN
{
	public short           m_u16FlowCurState;           //该流程通道当前状态
	public short           m_u16FlowInfoIndex;          //该流程通道对应流程类型标记
	public short           m_u16ChanIndex;              //该流程通道对应通道标记
	public short           m_u16StartState;             //启动标志,0:禁止;1:使能
	public short           m_u16BusyState;              //Busy标志,0:Free;1:Busy
    public ITP_FLOW_INFO   m_PITPFlowInfo;              //流程信息
    public short           m_u16CurResNum;              //与此流程通道绑定的当前资源数量
    public short           m_s16ChanRetCode;            //流程通道返回状态值
    public ITP_RES_CHAN    m_PITPResList[] = new ITP_RES_CHAN[256];//与此流程通道绑定的资源句柄表
	public short           m_u16CurTimerNum;            //定时器个数
	public byte            m_u8Master;
	public byte            m_s8Rfu;
	public ITP_FLOW_TIMER  m_PITPTimerChan[] = new ITP_FLOW_TIMER[64];//定时器句柄
    public Integer         m_PITPSysFunc[] = new Integer[32];    //系统函数指针
    public byte            m_s8InfoBuf[][] = new byte[3][40];//用户显示状态
    public byte            m_u8RelateModInfo[] = new byte[128]; //相关的模块
    public PKG_HEAD_STRUCT m_PITPEvtPack;                 //事件包指针
    public PKG_HEAD_STRUCT m_PITPInterEvt;                //流程内部事件包指针
	public Byte            m_PITPFlowExtData;            //流程扩展数据
	public Byte            m_PITPPublicBuf;              //公共使用缓存区
}

//资源通道结构
class ITP_RES_CHAN
{
	public short	 m_u16ChanIndex;        //该通道的通道索引号
    public byte 	 m_u8UnitIndex;         //该通道所在模块单元索引号
    public byte 	 m_u8ModType;           //该通道所在模块的Module_Type
    public byte 	 m_u8FuncType;          //该通道所在模块的Func_Type        
    public byte 	 m_u8ChanType;          //该通道的类型，此项仅只有Interface_ch有用
    public short 	 m_s16ChanGroup;        //该通道的组号
    public byte 	 m_u8BusyFlag;          //通道忙标志,0:空闲;1:独占打开;2:监听打开
    public ITP_FLOW_CHAN  m_PITPFlowChan; //流程通道信息
	public ITP_FLOW_CHAN  m_PITPListenFlowChan; //监听流程通道
	public byte     m_s8InfoBuf[][] = new byte[3][40];//用户显示状态
    public byte     m_u8RelateModInfo[] = new byte[64];     //与该资源相关的模块
    public byte     m_s8MachineId;                                //机箱号ID 
	public byte     m_s8Resrv[] = new byte[63];
}

//定时器结构
class ITP_FLOW_TIMER
{	
    public double     m_u64Time;              //触发时间
    public int	      m_u32Ticks;             //触发间隔
    public byte       m_u8StartFlag;          //启动标志
    public byte       m_u8Caller;             //调用者:用户DLL或者模块本身
    public byte       m_Resrv[] = new byte[2];
    public ITP_FLOW_CHAN  	 m_PITPFlowChan;   //流程通道指针
    public ItpFlowChanDef    m_PITPTimerFunc = new ItpFlowChanDef();       //定时处理函数
	public short	  m_u16ChanIndex;        //后续三个定义是为了与流程转换部分的事件参数为资源句柄相一致
	public byte	   	  m_u8UnitIndex;         //
	public byte	   	  m_u8ModType;           //
}