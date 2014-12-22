using System;
using System.Collections.Generic;
using System.Text;

namespace DJKeygoe
{
    using DJ_U8 = Byte;
    using DJ_S8 = SByte;
    using DJ_U16 = UInt16;
    using DJ_U32 = UInt32;
    using DJ_S32 = Int32;

    class DJITPMsgPublic
    {
        //通讯包特殊字段的定义
        public const DJ_U32 PKG_EXTEND_NORMAL       = 0x00;
        public const DJ_U32  PKG_EXTEND_ERROR         = 0x01;
        public const DJ_U32  PKG_EXTEND_CONFIG       = 0x02;
        public const DJ_U32  PKG_EXTEND_INTERFACE  = 0x03;
        // 用于双机备份时区分包的发送方向
        public const DJ_U32  PKG_EXTEND_UPPER	   = 0x04;		// 上级模块包
        public const DJ_U32  PKG_EXTEND_LOWER	   = 0x05;		// 下级模块包


        //************配置管理模块消息包*****************


        //模块状态定义
        /*说明:
        模块状态由一个DJ_U16类型定义，例如DJ_U16 u16ModuleStates
        其中bit0 = 1,表示模块已经初始化, bit0 = 0 表示模块未初始化或已释放
        其中bit1 = 1,表示模块已经启动  , bit1 = 0 表示模块已经停止
        其中bit2 = 1,表示模块全部关联  , bit2 = 0 表示模块还有部分或全部未关联
        其中bit3 = 1,表示模块已被监视  , bit3 = 0 表示模块未被监视
        其中bit4 = 1,表示模块已经连接  , bit4 = 0 表示模块断开连接
        其中bit5 = 1,表示模块正在停止  , 
        其中bit6 = 1,表示模块正在运行  , bit6 = 0,表示模块没有运行  , 
        其他9个bit位暂时没有用到

        */

        public const DJ_U32 MODULE_INIT          = 0x01;    //模块已初始化
        public const DJ_U32 MODULE_START       = 0x02;    //模块已启动
        public const DJ_U32 MODULE_RELATE     = 0x04;    //模块已全部被其上级模块关联
        public const DJ_U32 MODULE_MONITOR  = 0x08;    //模块已被监视
        public const DJ_U32 MODULE_CONNECT  = 0x10;    //模块已连接
        public const DJ_U32 MODULE_STOPPING = 0x20;    //模块正在停止
        public const DJ_U32 MODULE_ISTUNING  = 0x40;    //正在运行模块
        public const DJ_U32 MODULE_SETSTANDBY = 0x80;    //需要设置主从模块
        

        //根节点标识
        public const DJ_U32 ITP_ROOT_NODE     = 0x01;

        //节点类型，如果无此节点，则返回NODE_NONE
        public const DJ_U32 NODE_NONE             = 0x00;
        public const DJ_U32 NODE_PARENT          = 0x01;     //分支配置
        public const DJ_U32 NODE_RDONLY          = 0x02;     //只读配置
        public const DJ_U32 NODE_RDWR             = 0x03;     //可读写配置
        public const DJ_U32 NODE_SHOWONLY    = 0x04;     //只读列表配置
        public const DJ_U32 NODE_RDWR_TABLE = 0x05;     //可读写列表配置 


        public const DJ_U32 ERASE_PASSWORD = 0x87654321;    //DSP FLASH擦除密码

        //******************媒体处理层消息包定义***********************************
        public const DJ_U32   MSG_MEDIA						    = 0x3000;

        public const DJ_U32 MSG_MEDIA_DEV = MSG_MEDIA + 0x100;
        public const DJ_U32   MSG_MEDIA_DEV_OPEN		= 	MSG_MEDIA_DEV + 0x001;
        public const DJ_U32   MSG_MEDIA_DEV_CLOSE		= 	MSG_MEDIA_DEV + 0x002;
        public const DJ_U32   MSG_MEDIA_DEV_STOP			= MSG_MEDIA_DEV + 0x003;

        public const DJ_U32   MSG_MEDIA_PLAYREC			= 	MSG_MEDIA_DEV + 0x100;
        public const DJ_U32   MSG_MEDIA_PLAYREC_PLAY	= 	0x001;
        public const DJ_U32   MSG_MEDIA_PLAYREC_RECORD		= 0x002;

        public const DJ_U32   MSG_MEDIA_UT					= MSG_MEDIA_PLAYREC + 0x100;

        public const DJ_U32   MSG_MEDIA_FSK				= 	MSG_MEDIA_UT + 0x100;

        public const DJ_U32   MSG_MEDIA_EC					= MSG_MEDIA_FSK + 0x100;

        public const DJ_U32   MSG_MEDIA_DTMF				= MSG_MEDIA_EC + 0x100;

        public const DJ_U32   MSG_MEDIA_CA					= MSG_MEDIA_DTMF + 0x100;

        public const DJ_U32   MSG_MEDIA_DIAL				= MSG_MEDIA_CA + 0x100;

        public const DJ_U32   MSG_MEDIA_PARM				= MSG_MEDIA_DIAL + 0x100;

        public const DJ_U32   MSG_MEDIA_CONF				= MSG_MEDIA_PARM + 0x100;

        public const DJ_U32   MSG_MEDIA_MS					= MSG_MEDIA_CONF + 0x100;
        public const DJ_U32   MSG_MEDIA_MS_SEND		= 	MSG_MEDIA_MS + 0x001;
        public const DJ_U32   MSG_MEDIA_MS_RECV		= 	MSG_MEDIA_MS + 0x002;
        public const DJ_U32   MSG_MEDIA_MS_VLDRSC	= 	MSG_MEDIA_MS + 0x003;

        public const DJ_U32   MSG_MEDIA_END               = 0x3FFF;
    }

    //GUID的组成部分
    public struct ITP_GUID_tag
    {
        public DJ_U8   m_u8ModuleType;  //模块类型
        public DJ_U8   m_u8MainFuncId;  //主功能ID      
        public DJ_U8   m_u8SubFuncId;   //子功能ID
        public DJ_U8   m_u8UnitId;      //单元ID 
        public DJ_U16 m_u16ChanId;     //通道ID
    };

    //通讯消息包头
    public struct PKG_HEAD_STRUCT
    {
        public DJ_U8 m_u8PkgFlag;	// 包标志: 0xa5,0x5a
        public DJ_U8 m_u8PkgExtend;	// 包扩展位

        public DJ_U16 m_u16DataLen;	//不定长数据长度

        public ITP_GUID_tag ITP_GUID;

        public DJ_U16 m_u16Reserve;     //保留字段
    };

    //流程内自部通讯事件结构
    public unsafe struct FLOW_INTERDATA_HEAD
    {
	    public PKG_HEAD_STRUCT  m_PkgHead;                                 //事件包头
	    public CallID_t                  m_SrcCallID;                               //源流程
	    public CallID_t                  m_destCallID;                              //目的流程
	    public DJ_U32                  m_u32CmdType;                              //自定义命令类型
	    public DJ_U32                  m_u32InterNameLen;                         //用户结构名长度
	    public fixed DJ_S8            m_s8InterName[120]; //用户结构名
	    public DJ_U32                  m_u32InterDataSize;                        //用户自定义结构大小
    };

    public enum PACKAGE_TYPE
    {
        PKG_CMD = 0x5A,         // 命令数据包
        PKG_EVT = 0xA5          // 事件数据包
    };

    public enum MOD_STATE
    {
	    ITP_REPORT_MODSTATE_NORMAL    = 0x0,
	    ITP_REPORT_MODSTATE_COMMBAD   = 0x1,
    };

    //心跳包数据
    public struct ITP_HEART_TIME
    {
	    public DJ_U32	m_u32time;
	    public DJ_U32	m_u32date;
	    public DJ_U16  m_u16ModuleStates;
	    public DJ_U8   m_u8HotState;
	    public DJ_U8   m_u8HotWorkState;
    };

    public unsafe struct ITP_DSP_HOTSTANDBY_INFO
    {
	    public DJ_U8            m_u8IPNum;                          //IP 数目
	    public fixed DJ_U8    m_u8Reverse[3];      
	    public fixed DJ_U32   m_u32IPAddress[5];      //主模块的IP组
    };

    //从备份config server向主备份config server发送模块信息结构
    public unsafe struct CONFIG_MODULE_STRUCT
    {
        public DJ_U8                m_u8ModuleType;     //模块类型
	    public DJ_U8                m_u8UnitID;         //模块的单元ID
	    public fixed DJ_U8        m_u8Reverse[2];
        public DJ_U32              m_u32IPAddress;
	    public DJ_U32              m_u32Port;
    };


    //主备份config server向模块发送切换消息
    public struct CONFIG_HOTSTANDBY_STRUCT
    {
	    public DJ_U8       m_u8HOTState;    //设置对方的主从, 0 从模块 ，1 主模块
	    public DJ_U8       m_u8RetVal;      //设置是否成功  1 失败  1 成功
	    public DJ_U8       m_u8HotWorkState; //本机机器工作状态
        public DJ_U8       m_u8Reverse;
    };


    public struct  ITP_MODULE_EXCEPTION
    {
	    public DJ_U8  m_u8ExceptionType;	//模块异常类型  0：通讯异常，1：内部逻辑异常
	    public DJ_U8  m_u8ModuleType;		//断开模块类型
	    public DJ_U8  m_u8UnitID;			//断开模块ID
	    public DJ_U32 m_u32IPAddress;		//断开模块IP
    };

    public struct ITP_MODSTATE_REPORT
    {
	    public DJ_U16       m_u16ModState;   //模块异常类型  0：无异常，1：通讯异常，2：内部逻辑异常
	    public DJ_U8        m_u8ModuleType;   //断开模块类型
	    public DJ_U8        m_u8UnitID;       //断开模块ID
	    public DJ_U32       m_u32IPAddress;   //断开模块IP
    };

    //关联模块数据
    //系统关联信息(关联模块信息)

    public struct ITP_MODULE_ADDR
    {
	    public DJ_U8	m_u8ModuleType;			//模块类型
        public DJ_U8   m_u8UnitID;				//模块单元ID
	    public DJ_U16  m_u16Port;				//模块连接的端口号
        public DJ_U32  m_u32IPAddress;			//模块IP地址
    };


    public struct ITP_MODULE_RELATE_ADDR
    {
	    public DJ_U8	m_u8ModuleType;			//模块类型
        public DJ_U8   m_u8UnitID;				//模块单元ID
	    public DJ_U16  m_u16Port;				//模块连接的端口号
        public DJ_U32  m_u32IPAddress;			//模块IP地址
	    public DJ_U32  m_u32RelateFlag;        //连接方向
    };

    public unsafe struct ITP_MOD_VALIDITY_DATA
    {
	    public fixed DJ_S8         m_s8Username[32]; // 授权用户
	    public fixed DJ_S8         m_s8Password[32]; // 授权密码	
    };

    //监控模块数据包
    public struct ITP_MONITOR_ADDR
    {
	    public DJ_U8	    m_u8ModuleType;      //模块类型
        public DJ_U8    m_u8UnitID;          //模块单元ID
	    public DJ_U16  m_u16ChanID;         //模块通道号
	    public DJ_U16	m_u16DebugLevel;     //模块监控级别
        public DJ_U16  m_u16UdpPort;        //模块连接的UDP端口号
        public DJ_U32  m_u32IPAddress;      //模块IP地址
	    public DJ_U32	m_u32Reserved;       //保留字段
    };

    //界面和配置管理之间的消息包
    public unsafe struct ITP_MODULE_STRUCT
    {
        public DJ_U8               m_u8ModuleType;       //模块类型
        public DJ_U8               m_u8UnitID;           //单元ID
        public DJ_U8		           m_u8IsEnable;         //是否使能模块 0:不使能; 1:使能
        public DJ_U8               m_u8DSPType;          //DSP类型
        public DJ_U16             m_u16ModuleStates;    //模块状态
        public fixed DJ_S8       m_s8ModuleName[16]; //模块名
        public fixed DJ_S8       m_s8pMACAddress[20];  //网卡地址，非DSP为全0
        public DJ_U32             m_u32Version;         //模块版本名
        public DJ_U32             m_u32IPAddress;       //IP地址
        public DJ_U32             m_u32Port;            //服务端口
	    public DJ_U32             m_u32Param;           //保留参数
    };

    //错误包数据
    public unsafe struct ITP_ERROR_STRUCT
    {
        public  DJ_S32              m_s32ErrorCode;
        public  fixed DJ_S8       m_s8pErrMsg[96];
    };

    //配置管理发送给VOIP模块，No2IP配置成功通知消息
    public unsafe struct ITP_ADDIP_OK_NOTIFY_STRUCT
    {
        public  DJ_U8               m_u8ExcuteResult;
	    public  fixed DJ_U8       m_u8Reserve[7];
    };

    //配置管理发送给FLOW模块，告知备机已经正常工作的通知消息
    public unsafe struct ITP_SLAVE_WORK_NOTIFY_STRUCT
    {
        public  DJ_U8       m_u8WorkSate;            //0:工作异常; 1: 工作正常
	    public  fixed DJ_U8       m_u8Reserve[7];          //保留
    };


    /* new snmp content - add by liangyu 20110706 - begin */
    //**************************************
    //ITP配置管理模块获取SNMP内容的消息包

    //读通道状态结果（cfgSrv和流程）
    public unsafe struct ITP_CH_STATE_RESULT
    {
	    public DJ_U16          m_u8UnitID;				//单元ID
	    public DJ_U16          m_uReserved;				//保留
	    public fixed DJ_U32 m_u16State[128];			//DSP的所有通道状态
	    public fixed DJ_U8   m_u8DeviceSubType[128];	//DSP的设备子类型
    };

    //读Q931状态结果（cfgSrv和Q931）
    public unsafe struct ITP_Q931_STATE_RESULT
    {
	    public DJ_U16 m_u8UnitID;				//单元ID
	    public DJ_U16 m_u8PcmNum;				//PCM号
	    public fixed DJ_U8 m_u8LinkState[4];			//连接状态,参照DEF文件
	    public fixed DJ_U8 m_u8RestartFlag[4];		//重连标志
    };

    //主机状态结果（cfgSrv和proxy）
    public unsafe struct ITP_PC_STATE_RESULT
    {
	    public fixed DJ_U32 m_u32CpuIdle[8];			//空闲CPU
	    public DJ_U32         m_u32MemFree;			//空闲内存
	    public DJ_U32         m_u32SwapFree;			//空闲交换
	    public DJ_U32         m_u32HDFree;				//空闲硬盘
    };

    //mainmod下级连接关系结果（cfgSrv和mainmod）
    public struct ITP_MAINMOD_DOWNRELATE_RESULT
    {
	    public DJ_U8	m_u8ModuleType;			//模块类型
        public DJ_U8   m_u8UnitID;				//模块单元ID
	    public DJ_U8	m_u8RelateIndex;		//模块的关联号,0-255
	    public DJ_U8	m_u8RelateState;		//连接状态,0:正常,1:断开
    };
    /* new snmp content - add by liangyu 20110706 - end */

    //节点定义信息
    public unsafe struct ITP_INTERFACE_NODE_DATA
    {
	    public DJ_U8                m_u8NodeType;
	    public fixed DJ_S8       m_s8ConfigName[31];
	    public fixed DJ_S8       m_s8ConfigFileName[32];
	    public DJ_S32              m_s32NodeMsgCode;
        public DJ_S32              m_s32ConfigNum;  
    };


    //子节点标识列表
    public unsafe struct ITP_INTERFACE_SUBNODE_DATA
    {
	    public DJ_U8                m_u8NodeType;
	    public fixed DJ_S8       m_s8ConfigName[31];
	    public DJ_S32               m_s32NodeMsgCode;
    };


    //读写节点数据
    public struct ITP_INTERFACE_DONE_DATA
    {
	    public DJ_S32      m_s32IsWriteini;
	    public DJ_S32      m_s32NodeMsgCode;
	    public DJ_U16      m_u16FisrtData;
	    public DJ_U16      m_u16DataNum;
    };


    //写节点数据结果
    public struct ITP_INTERFACE_WRDATA_MSG
    {
	    public DJ_S32      m_s32NodeMsgCode;
	    public DJ_S32      m_s32RetCode;
    };

    //读节点操作结果
    public unsafe struct ITP_INTERFACE_RDATA_MSG
    {
	    public DJ_U8               m_u8NodeType;
	    public fixed DJ_S8      m_s8ConfigFileName[31];
	    public DJ_S32             m_s32NodeMsgCode;
	    public DJ_U16             m_u16FisrtData;
	    public DJ_U16             m_u16DataNum;
    };

    //读FLASH操作
    public struct ITP_FLASH_READ
    {
        public DJ_U32 m_u32AddrOffset;
	    public DJ_U32 m_u32ByteNum;
    };

    //写FLASH操作
    public unsafe struct ITP_FLASH_WRITE
    {
        public DJ_U32 m_u32AddrOffset;
	    public DJ_U32 m_u32ByteNum;
	    public fixed DJ_U8  m_u8pData[4000];
    };

    //读FLASH操作结果
    public unsafe struct ITP_FLASH_READ_MSG
    {
	    public DJ_U32 m_u32DataLen;
	    public fixed DJ_U8  m_u8pData[4000];
    };

    //写FLASH操作结果
    public struct ITP_FLASH_WRITE_MSG
    {
        public DJ_U32 m_u32WriteStates;
	    public DJ_U32 m_u32CheckSum;
    };
    //*******************************************************
}
