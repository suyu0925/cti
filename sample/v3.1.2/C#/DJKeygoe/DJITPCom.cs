using System;
using System.Collections.Generic;
using System.Text;

namespace DJKeygoe
{
    using DJ_U8 = Byte;
    using DJ_S8 = SByte;
    using DJ_S32 = Int32;
    using DJ_U32 = UInt32;

    class DJITPCom
    {
        public const DJ_U32  ITP_SYSTEM_FLAG = 0x49545031;  // ITP系统标识
    }


    ///////////////// 模块连接到服务端时，发送的授权请求信息 //////////////////////
    public unsafe struct LICENCE_INFO_STRUCT
    {	
	    public DJ_S32         m_ItpFlag;       // 系统标识	
	    public DJ_U8           m_u8ModuleType;  // 模块类型
	    public DJ_U8           m_u8MainFuncId;  // 主功能号
	    public DJ_U8           m_u8SubFuncId;   // 子功能号
	    public DJ_U8           m_u8UnitId;      // 单元号			
    	
	    public DJ_S32          m_Version;       // 版本号	
	    public DJ_S32          m_AckInfo;       // 确认值,初始0,成功1,错误-1，上层不用关心
    	
	    public PKG_HEAD_STRUCT m_PkgHead;       // 授权包头
	    public fixed DJ_S8              m_s8Username[32];// 授权用户
	    public fixed DJ_S8              m_s8Password[32];// 授权密码
    	
	    public fixed DJ_U8              m_u8Reserved[36];// 备用	
    };

    ///////////////// 上层模块查询服务端有无客户端连接用到的结构 //////////////////
    public unsafe struct CONN_INFO_STRUCT
    {
	    public DJ_U32       m_SkForListen;     // 接受连接时用到的套节字：用来监听
	    public DJ_U32       m_SkForClient;     // 接受连接时返回的套节字：用来通讯
	    public fixed DJ_S8 m_szIP[32];        // 客户端IP地址
	    public DJ_S32        m_Port;            // 客户端端口号

	    public LICENCE_INFO_STRUCT Licence;	
    };
}
