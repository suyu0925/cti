unit DJItpFlowChanDef;

interface

uses
  SysUtils,Windows,DJAcsDataDef;

const ITP_MAX_MOD_TYPE_NUM           = 128;    // 最大模块数
const ITP_MAX_RELATEMOD_NUM          = 64;     //最大关联模块数
const ITP_MAX_SYSFUNC_NUM            = 32;     //流程模块系统函数接口个数
const ITP_MAX_DLLFUNC_NUM            = 4;      //流程动态库接口函数个数
const ITP_FLOW_MAX_FLOWNAME_LEN      = 40;     //流程名最大长度
const ITP_FLOW_MAX_INTERNAME_LEN     = 120;    //用户自定义结构名最大长度

const MAX_PATH                       = 260;

const ITP_MAX_BINDRES_NUM            = 256;    //流程通道绑定的最大资源个数
const ITP_MAX_BINDTIMER_NUM          = 64;     //流程通道绑定的最大定时器个数
const ITP_FLOW_SHOW_INFO_SIZE        = 40;     //用户显示状态缓存长度
const ITP_FLOW_SHOW_INFO_NUM         = 3;      //用户显示状态缓存个数

Type ITP_RESOPEN_TYPE =
(
    ITP_RESOPEN_FREE = 0,
    ITP_RESOPEN_LISTEN,
	  ITP_RESOPEN_EXCLUDE
);

//流程通道结构
Type
  ITP_FLOW_CHAN = record
  
  m_u16FlowCurState  : Word;           //该流程通道当前状态
  m_u16FlowInfoIndex : Word;           //该流程通道对应流程类型标记
  m_u16ChanIndex     : Word;           //该流程通道对应通道标记
  m_u16StartState    : Word;           //启动标志,0:禁止;1:使能
	m_u16BusyState     : Word;           //Busy标志,0:Free;1:Busy
  m_PITPFlowInfo     : Pointer; //流程信息
  m_u16CurResNum     : Word;           //与此流程通道绑定的当前资源数量
  m_s16ChanRetCode   : Smallint;       //流程通道返回状态值
	m_PITPResList      : Array[0..ITP_MAX_BINDRES_NUM-1] of Pointer;//与此流程通道绑定的资源句柄表
  m_u16CurTimerNum   : Word;           //定时器个数
	m_u8Master         : Byte;
	m_s8Rfu            : ShortInt;
  m_PITPTimerChan    : Array[0..ITP_MAX_BINDTIMER_NUM -1] of Pointer;//定时器句柄
  m_PITPSysFunc      : Array[0..ITP_MAX_SYSFUNC_NUM-1] of PDword;            //系统函数指针
  m_s8InfoBuf        : Array[0..ITP_FLOW_SHOW_INFO_NUM-1,0..ITP_FLOW_SHOW_INFO_SIZE-1] of ShortInt;//用户显示状态
	m_u8RelateModInfo  : Array[0..ITP_MAX_MOD_TYPE_NUM-1] of Byte; //相关的模块
  m_PITPEvtPack      : ^PKG_HEAD_STRUCT; //事件包指针
	m_PITPInterEvt     : ^PKG_HEAD_STRUCT; //流程内部事件包指针
  m_PITPFlowExtData  : Pbyte;            //流程扩展数据
  m_PITPPublicBuf    : Pbyte;            //公共使用缓存区
end;

type
  PITP_FLOW_CHAN = ^ITP_FLOW_CHAN;

//流程信息结构
Type
  ITP_FLOW_INFO = record

  m_u32FlowIndex : DWORD;                          //流程标号
  m_s8FlowName   : Array[0..ITP_FLOW_MAX_FLOWNAME_LEN-1] of ShortInt; //流程名
  m_s8DllName    : Array[0..MAX_PATH-1] of ShortInt;                  //动态库名
  m_u32StartState: DWORD;                         //流程使能状态
  m_u32LoadState : DWORD;                         //流程加载状态
  m_hdlDllHandle : PDword;                        //流程动态库句柄
  m_hdlDllFunc   : Array[0..ITP_MAX_DLLFUNC_NUM-1] of PDword;         //流程动态库接口函数指针
  m_u16FlowChanNum : Word;                        //该动态库对应的副本个数
	m_u16Resrv     : Word;
  m_PITPFlowChan : ^PITP_FLOW_CHAN;               //该动态库对应的副本表
end;

//资源通道结构
Type
  ITP_RES_CHAN = record
  
	m_u16ChanIndex : Word;         //该通道的通道索引号
  m_u8UnitIndex  : Byte;         //该通道所在模块单元索引号
	m_u8ModType    : Byte;         //该通道所在模块的Module_Type
  m_u8FuncType   : Byte;         //该通道所在模块的Func_Type
  m_u8ChanType   : Byte;         //该通道的类型，此项仅只有Interface_ch有用
  m_s16ChanGroup : SmallInt;     //该通道的组号
  m_u8BusyFlag   : Byte;         //通道忙标志,0:空闲;1:独占打开;2:监听打开
  m_PITPFlowChan : Pointer; //流程通道信息
	m_PITPListenFlowChan : PITP_FLOW_CHAN; //监听流程通道
  m_s8InfoBuf          : Array[0..ITP_FLOW_SHOW_INFO_NUM-1,0..ITP_FLOW_SHOW_INFO_SIZE-1] of ShortInt;//用户显示状态
  m_u8RelateModInfo    : Array[0..ITP_MAX_RELATEMOD_NUM-1] of Byte;     //与该资源相关的模块
	m_s8MachineId        : ShortInt;                                //机箱号ID
	m_s8Resrv            : Array[0..ITP_MAX_RELATEMOD_NUM-2] of ShortInt;
end;

//定时器结构
Type
  PTIMERFUNC=procedure(p:PInteger);cdecl;
  
  ITP_FLOW_TIMER = record
  
  m_u64Time      : Double;        //触发时间
  m_u32Ticks     : DWord;         //触发间隔
  m_u8StartFlag  : Byte;          //启动标志
	m_u8Caller     : Byte;          //调用者:用户DLL或者模块本身
	m_Resrv        : Array[0..1] of Byte;
  m_PITPFlowChan : Pointer;//流程通道指针
  m_PITPTimerFunc: PTIMERFUNC;    //定时处理函数
	m_u16ChanIndex : Word;          //后续三个定义是为了与流程转换部分的事件参数为资源句柄相一致
  m_u8UnitIndex  : Byte;
	m_u8ModType    : Byte;
end;

//流程内自部通讯事件结构
Type
  FLOW_INTERDATA_HEAD = record
	m_PkgHead     : PKG_HEAD_STRUCT;                    //事件包头
	m_SrcCallID   : CallID_t;                           //源流程
	m_destCallID  : CallID_t;                           //目的流程
	m_u32CmdType  : DWORD;                              //自定义命令类型
	m_u32InterNameLen : DWORD;                          //用户结构名长度
	m_s8InterName : Array[0..ITP_FLOW_MAX_INTERNAME_LEN-1] of ShortInt; //用户结构名
	m_u32InterDataSize : DWORD;                         //用户自定义结构大小
end;

implementation

end.
