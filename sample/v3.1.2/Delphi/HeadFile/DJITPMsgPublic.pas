unit DJITPMsgPublic;

interface

uses
  SysUtils,Windows, DJAcsDataDef;

//通讯包特殊字段的定义
const PKG_EXTEND_NORMAL     = $00;
const PKG_EXTEND_ERROR      = $01;
const PKG_EXTEND_CONFIG     = $02;
const PKG_EXTEND_INTERFACE  = $03;
// 用于双机备份时区分包的发送方向
const PKG_EXTEND_UPPER	    = $04;		// 上级模块包
const PKG_EXTEND_LOWER	    = $05;		// 下级模块包

const ITP_FLOW_MAX_INTERNAME_LEN     = 120;    //用户自定义结构名最大长度
//通讯消息包头

//流程内自部通讯事件结构
Type
  FLOW_INTERDATA_HEAD = record
	m_PkgHead          : PKG_HEAD_STRUCT;               //事件包头
	m_SrcCallID        : CallID_t;                      //源流程
	m_destCallID       : CallID_t;                      //目的流程
	m_u32CmdType       : DWORD;                         //自定义命令类型
  m_u32InterNameLen  : DWORD;                         //用户结构名长度
	m_s8InterName      : Array[0..ITP_FLOW_MAX_INTERNAME_LEN-1] of ShortInt; //用户结构名
	m_u32InterDataSize : DWORD;                        //用户自定义结构大小
end;

Type PACKAGE_TYPE =
(
	PKG_CMD = $5A,         // 命令数据包
	PKG_EVT = $A5          // 事件数据包
);

//************配置管理模块消息包*****************


//模块状态定义
{说明:
模块状态由一个DJ_U16类型定义，例如DJ_U16 u16ModuleStates
其中bit0 = 1,表示模块已经初始化, bit0 = 0 表示模块未初始化或已释放
其中bit1 = 1,表示模块已经启动  , bit1 = 0 表示模块已经停止
其中bit2 = 1,表示模块全部关联  , bit2 = 0 表示模块还有部分或全部未关联
其中bit3 = 1,表示模块已被监视  , bit3 = 0 表示模块未被监视
其中bit4 = 1,表示模块已经连接  , bit4 = 0 表示模块断开连接
其中bit5 = 1,表示模块正在停止  ,
其中bit6 = 1,表示模块正在运行  , bit6 = 0,表示模块没有运行  ,
其他9个bit位暂时没有用到
}

const MODULE_INIT       = $01;    //模块已初始化
const MODULE_START      = $02;    //模块已启动
const MODULE_RELATE     = $04;    //模块已全部被其上级模块关联
const MODULE_MONITOR    = $08;    //模块已被监视
const MODULE_CONNECT    = $10;    //模块已连接
const MODULE_STOPPING   = $20;    //模块正在停止
const MODULE_ISTUNING   = $40;    //正在运行模块
const MODULE_SETSTANDBY = $80;    //需要设置主从模块

Type MOD_STATE =
(
	ITP_REPORT_MODSTATE_NORMAL    = $0,
	ITP_REPORT_MODSTATE_COMMBAD   = $1
);

//心跳包数据
Type
  ITP_HEART_TIME = record
	m_u32time         : DWORD;
	m_u32date         : DWORD;
	m_u16ModuleStates : WORD;
	m_u8HotState      : Byte;
	m_u8HotWorkState  : Byte;
end;

//传送给DSP的主从信息

const MAX_IP_NUM  = 5;

Type
  ITP_DSP_HOTSTANDBY_INFO = record
	m_u8IPNum      : Byte;                          //IP 数目
	m_u8Reverse    : Array[0..2] of Byte;
	m_u32IPAddress : Array[0..MAX_IP_NUM-1] of DWORD;      //主模块的IP组
end;


//从备份config server向主备份config server发送模块信息结构
Type
  CONFIG_MODULE_STRUCT = record
  m_u8ModuleType : Byte;         //模块类型
	m_u8UnitID     : Byte;         //模块的单元ID
	m_u8Reverse    : Array[0..1] of Byte;

  m_u32IPAddress : DWORD;
	m_u32Port      : DWORD;
end;


//主备份config server向模块发送切换消息
Type
  CONFIG_HOTSTANDBY_STRUCT = record
	m_u8HOTState     : Byte;    //设置对方的主从, 0 从模块 ，1 主模块
	m_u8RetVal       : Byte;    //设置是否成功  1 失败  1 成功
	m_u8HotWorkState : Byte;    //本机机器工作状态
  m_u8Reverse      : Byte;
end;


Type
  ITP_MODULE_EXCEPTION = record
	m_u8ExceptionType : Byte;	//模块异常类型  0：通讯异常，1：内部逻辑异常
	m_u8ModuleType    : Byte;	//断开模块类型
	m_u8UnitID        : Byte;	//断开模块ID
	m_u32IPAddress    : DWORD;	//断开模块IP
end;

Type
  ITP_MODSTATE_REPORT = record
	m_u16ModState  : Word;   //模块异常类型  0：无异常，1：通讯异常，2：内部逻辑异常
	m_u8ModuleType : Byte;   //断开模块类型
	m_u8UnitID     : Byte;   //断开模块ID
	m_u32IPAddress : DWORD;  //断开模块IP
end;

//关联模块数据
//系统关联信息(关联模块信息)

Type
  ITP_MODULE_ADDR = record
	m_u8ModuleType : Byte;			//模块类型
  m_u8UnitID     : Byte;			//模块单元ID
	m_u16Port      : WORD;			//模块连接的端口号
  m_u32IPAddress : DWORD;			//模块IP地址
end;


Type
  ITP_MODULE_RELATE_ADDR = record
	m_u8ModuleType : Byte;			//模块类型
  m_u8UnitID     : Byte;				//模块单元ID
	m_u16Port      : Word;				//模块连接的端口号
  m_u32IPAddress : DWORD;			//模块IP地址
	m_u32RelateFlag: DWORD;        //连接方向
end;

Type
  ITP_MOD_VALIDITY_DATA = record
	m_s8Username : Array[0..31] of ShortInt; // 授权用户
	m_s8Password : Array[0..31] of ShortInt; // 授权密码
end;

//监控模块数据包
Type
  ITP_MONITOR_ADDR = record
	m_u8ModuleType : Byte;      //模块类型
  m_u8UnitID : Byte;          //模块单元ID
	m_u16ChanID : Word;         //模块通道号
	m_u16DebugLevel : Word;     //模块监控级别
  m_u16UdpPort : Word;        //模块连接的UDP端口号
  m_u32IPAddress : DWORD;     //模块IP地址
	m_u32Reserved : DWORD;      //保留字段
end;

const MAX_MACADDR_STR_LEN     = $14;     //网卡地址字符串长度最大值
const MAX_MODULENAME_STR_LEN	= $10;     //模块名字符串长度最大值
const MAX_ERRMSG_LEN          = $60;     //错误信息字符串长度最大值

//界面和配置管理之间的消息包
Type
  ITP_MODULE_STRUCT = record
  m_u8ModuleType : Byte;        //模块类型
  m_u8UnitID     : Byte;        //单元ID
  m_u8IsEnable   : Byte;        //是否使能模块 0:不使能; 1:使能
  m_u8DSPType    : Byte;        //DSP类型
  m_u16ModuleStates : Word;     //模块状态
  m_s8ModuleName    : Array[0..MAX_MODULENAME_STR_LEN-1] of ShortInt; //模块名
  m_s8pMACAddress   : Array[0..MAX_MACADDR_STR_LEN-1] of ShortInt;    //网卡地址，非DSP为全0
  m_u32Version      : DWORD;    //模块版本名
  m_u32IPAddress    : DWORD;    //IP地址
  m_u32Port  : DWORD;           //服务端口
	m_u32Param : DWORD;           //保留参数
end;

//错误包数据
Type
  ITP_ERROR_STRUCT = record
  m_s32ErrorCode : Integer;
  m_s8pErrMsg    : Array[0..MAX_ERRMSG_LEN-1] of ShortInt;
end;

//配置管理发送给VOIP模块，No2IP配置成功通知消息
Type
  ITP_ADDIP_OK_NOTIFY_STRUCT = record
  m_u8ExcuteResult : byte;
	m_u8Reserve      : Array[0..6] of Byte;
end;

//配置管理发送给FLOW模块，告知备机已经正常工作的通知消息
Type
  ITP_SLAVE_WORK_NOTIFY_STRUCT = Record
  m_u8WorkSate : Byte;              //0:工作异常; 1: 工作正常
	m_u8Reserve  : Array[0..6] of Byte;
end;



//**************************************
//ITP配置管理模块获取SNMP内容的消息包

//读通道状态结果（cfgSrv和流程）
Type
  ITP_CH_STATE_RESULT = record
	m_u8UnitID  : Word;				//单元ID
	m_uReserved : Word;				//保留
	m_u16State  : Array[0..127] of DWORD;			//DSP的所有通道状态
	m_u8DeviceSubType : Array[0..127] of Byte;//DSP的设备子类型
end;

//读Q931状态结果（cfgSrv和Q931）
Type
  ITP_Q931_STATE_RESULT = record
	m_u8UnitID : Word;				//单元ID
	m_u8PcmNum : Word;				//PCM号
	m_u8LinkState   : Array[0..3] of Byte;		//连接状态,参照DEF文件
	m_u8RestartFlag : Array[0..3] of Byte;		//重连标志
end;

//主机状态结果（cfgSrv和proxy）
Type
  ITP_PC_STATE_RESULT = record
	m_u32CpuIdle  : Array[0..7] of DWORD;			//空闲CPU
	m_u32MemFree  : DWORD;			//空闲内存
	m_u32SwapFree : DWORD;			//空闲交换
	m_u32HDFree   : DWORD;			//空闲硬盘
end;

//mainmod下级连接关系结果（cfgSrv和mainmod）
Type
  ITP_MAINMOD_DOWNRELATE_RESULT = record
	m_u8ModuleType : Byte;		//模块类型
  m_u8UnitID : Byte;				//模块单元ID
	m_u8RelateIndex : Byte;		//模块的关联号,0-255
	m_u8RelateState : Byte;		//连接状态,0:正常,1:断开
end;


//**************************************
//ITP配置界面和其他模块的消息包


//根节点标识
const ITP_ROOT_NODE   = $01;

//节点类型，如果无此节点，则返回NODE_NONE
const NODE_NONE       = $00;
const NODE_PARENT     = $01;     //分支配置
const NODE_RDONLY     = $02;     //只读配置
const NODE_RDWR       = $03;     //可读写配置
const NODE_SHOWONLY   = $04;     //只读列表配置
const NODE_RDWR_TABLE = $05;     //可读写列表配置

//节点定义信息
Type
  ITP_INTERFACE_NODE_DATA = record
	m_u8NodeType       : Byte;
	m_s8ConfigName     : Array[0..30] of ShortInt;
	m_s8ConfigFileName : Array[0..31] of ShortInt;
	m_s32NodeMsgCode   : Integer;
  m_s32ConfigNum     : Integer;
end;


//子节点标识列表
Type
  ITP_INTERFACE_SUBNODE_DATA = record
	m_u8NodeType     : Byte;
	m_s8ConfigName   : Array[0..30] of ShortInt;
	m_s32NodeMsgCode : Integer;
end;


//读写节点数据
Type
  ITP_INTERFACE_DONE_DATA = record
	m_s32IsWriteini : Integer;
	m_s32NodeMsgCode : Integer;
	m_u16FisrtData : Word;
	m_u16DataNum : Word;
end;


//写节点数据结果
Type
  ITP_INTERFACE_WRDATA_MSG = record
	m_s32NodeMsgCode : Integer;
	m_s32RetCode     : Integer;
end;

//读节点操作结果
Type
  ITP_INTERFACE_RDATA_MSG = record
	m_u8NodeType : Byte;
	m_s8ConfigFileName : Array[0..30] of ShortInt;
	m_s32NodeMsgCode : Integer;
	m_u16FisrtData : Word;
	m_u16DataNum : Word;
end;
//**************************************


////ITP配置界面和DSP模块进行固件更新的消息包

const ERASE_PASSWORD = $87654321;      //DSP FLASH擦除密码
const MAX_DATA_BLOCK_LENGTH   = 4000;  //写入FLASH数据的最大长度

//读FLASH操作
Type
  ITP_FLASH_READ = record
  m_u32AddrOffset : DWORD;
	m_u32ByteNum    : DWORD;
end;

//写FLASH操作
Type
  ITP_FLASH_WRITE = record
  m_u32AddrOffset : DWORD;
	m_u32ByteNum    : DWORD;
	m_u8pData       : Array[0..MAX_DATA_BLOCK_LENGTH-1] of Byte;
end;

//读FLASH操作结果
Type
  ITP_FLASH_READ_MSG = record
	m_u32DataLen : DWORD;
	m_u8pData    : Array[0..MAX_DATA_BLOCK_LENGTH-1] of Byte;
end;

//写FLASH操作结果
Type
  ITP_FLASH_WRITE_MSG = record
  m_u32WriteStates : DWORD;
	m_u32CheckSum : DWORD;
end;
//*******************************************************


//******************媒体处理层消息包定义***********************************
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
