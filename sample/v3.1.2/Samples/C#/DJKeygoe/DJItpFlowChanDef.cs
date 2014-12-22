using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Text;

namespace DJKeygoe
{
    using DJ_U8 = Byte;
    using DJ_S8 = SByte;
    using DJ_U16 = UInt16;
    using DJ_S16 = Int16;
    using DJ_U32 = UInt32;
    using DJ_S32 = Int32;
    using DJ_F64 = Double;

    class DJItpFlowChanDef
    {
    }

    public enum ITP_RESOPEN_TYPE
    {
        ITP_RESOPEN_FREE = 0,
        ITP_RESOPEN_LISTEN,
        ITP_RESOPEN_EXCLUDE,
    };

    //流程信息结构
    public unsafe class ITP_FLOW_INFO
    {
        public DJ_U32            m_u32FlowIndex;                          //流程标号
        public DJ_S8              []m_s8FlowName = new DJ_S8[40]; //流程名
        public DJ_S8              []m_s8DllName = new DJ_S8[260];                   //动态库名	
        public DJ_U32            m_u32StartState;                         //流程使能状态
        public DJ_U32            m_u32LoadState;                          //流程加载状态
        public DJ_U32*          m_hdlDllHandle;                          //流程动态库句柄
        public DJ_U32*         []m_hdlDllFunc = new DJ_U32*[4];       //流程动态库接口函数指针
        public DJ_U16            m_u16FlowChanNum;                        //该动态库对应的副本个数
	    public DJ_U16            m_u16Resrv;
        public ITP_FLOW_CHAN m_PITPFlowChan;                     //该动态库对应的副本表
    };

    //流程通道结构
    public unsafe class ITP_FLOW_CHAN
    {
        public DJ_U16           m_u16FlowCurState;           //该流程通道当前状态
        public DJ_U16           m_u16FlowInfoIndex;          //该流程通道对应流程类型标记
        public DJ_U16           m_u16ChanIndex;              //该流程通道对应通道标记
        public DJ_U16           m_u16StartState;             //启动标志,0:禁止;1:使能
	    public DJ_U16           m_u16BusyState;              //Busy标志,0:Free;1:Busy
        public ITP_FLOW_INFO   m_PITPFlowInfo;              //流程信息
        public DJ_U16           m_u16CurResNum;              //与此流程通道绑定的当前资源数量
        public DJ_S16           m_s16ChanRetCode;            //流程通道返回状态值
	    public ITP_RES_CHAN    []m_PITPResList = new ITP_RES_CHAN[256];//与此流程通道绑定的资源句柄表
        public DJ_U16           m_u16CurTimerNum;            //定时器个数
	    public DJ_U8            m_u8Master;
	    public DJ_S8            m_s8Rfu;
        public ITP_FLOW_TIMER  []m_PITPTimerChan = new ITP_FLOW_TIMER[64];//定时器句柄
        public DJ_U32*        []m_PITPSysFunc = new DJ_U32*[32];    //系统函数指针
        public DJ_S8            [,]m_s8InfoBuf = new DJ_S8[3, 40];//用户显示状态
	    public DJ_U8            []m_u8RelateModInfo = new DJ_U8[128]; //相关的模块
        public PKG_HEAD_STRUCT* m_PITPEvtPack;                 //事件包指针
	    public PKG_HEAD_STRUCT* m_PITPInterEvt;                //流程内部事件包指针
        public DJ_U8            *m_PITPFlowExtData;            //流程扩展数据
        public DJ_U8            *m_PITPPublicBuf;              //公共使用缓存区
    };

    //资源通道结构
    public unsafe class ITP_RES_CHAN
    {
	    public DJ_U16	 m_u16ChanIndex;        //该通道的通道索引号
        public DJ_U8	     m_u8UnitIndex;         //该通道所在模块单元索引号
	    public DJ_U8	     m_u8ModType;           //该通道所在模块的Module_Type
        public DJ_U8	     m_u8FuncType;          //该通道所在模块的Func_Type        
        public DJ_U8	     m_u8ChanType;          //该通道的类型，此项仅只有Interface_ch有用
        public DJ_S16	 m_s16ChanGroup;        //该通道的组号
        public DJ_U8	     m_u8BusyFlag;          //通道忙标志,0:空闲;1:独占打开;2:监听打开
        public ITP_FLOW_CHAN  m_PITPFlowChan; //流程通道信息
	    public ITP_FLOW_CHAN  m_PITPListenFlowChan; //监听流程通道
        public DJ_S8    [,]m_s8InfoBuf = new DJ_S8[3, 40];//用户显示状态
        public DJ_U8    []m_u8RelateModInfo = new DJ_U8[64];     //与该资源相关的模块
	    public DJ_S8    m_s8MachineId;                                //机箱号ID 
	    public DJ_S8    []m_s8Resrv = new DJ_S8[63];
    };

    //定时器结构
    public unsafe class ITP_FLOW_TIMER
    {	
        [UnmanagedFunctionPointer(System.Runtime.InteropServices.CallingConvention.Cdecl)] //指定该托管参数调用Cdecl
        public delegate DJ_S32 PTIMERFUNC(DJ_S32* p); //声明一个函数指针，XMS_acsSetESR调用的回调函数EsrFunc类型

        public DJ_F64              m_u64Time;              //触发时间
        public DJ_U32             m_u32Ticks;             //触发间隔
        public DJ_U8               m_u8StartFlag;          //启动标志
	    public DJ_U8               m_u8Caller;             //调用者:用户DLL或者模块本身
	    public DJ_U8               []m_Resrv = new DJ_U8[2];
        public ITP_FLOW_CHAN  m_PITPFlowChan;   //流程通道指针
        public PTIMERFUNC           m_PITPTimerFunc;       //定时处理函数
	    public DJ_U16	           m_u16ChanIndex;        //后续三个定义是为了与流程转换部分的事件参数为资源句柄相一致
        public DJ_U8	               m_u8UnitIndex;         //
	    public DJ_U8	               m_u8ModType;           //
    };
}
