package DJKeygoe;

public class DJITPCom {

}

///////////////// 模块连接到服务端时，发送的授权请求信息 //////////////////////
class LICENCE_INFO_STRUCT
{	
	public int          	m_ItpFlag;       // 系统标识	
	public byte           	m_u8ModuleType;  // 模块类型
	public byte           	m_u8MainFuncId;  // 主功能号
	public byte           	m_u8SubFuncId;   // 子功能号
	public byte           	m_u8UnitId;      // 单元号			
	public int          	m_Version;       // 版本号	
	public int          	m_AckInfo;       // 确认值,初始0,成功1,错误-1，上层不用关心
	public PKG_HEAD_STRUCT  m_PkgHead = new PKG_HEAD_STRUCT();       // 授权包头
	public byte           	m_s8Username[] = new byte[32];// 授权用户
	public byte           	m_s8Password[] = new byte[32];// 授权密码
	public byte           	m_u8Reserved[] = new byte[36];// 备用	
}

///////////////// 上层模块查询服务端有无客户端连接用到的结构 //////////////////
class CONN_INFO_STRUCT
{
	public int     m_SkForListen;     // 接受连接时用到的套节字：用来监听
	public int     m_SkForClient;     // 接受连接时返回的套节字：用来通讯
	public byte    m_szIP[] = new byte[32];        // 客户端IP地址
	public int     m_Port;            // 客户端端口号
	public LICENCE_INFO_STRUCT Licence = new LICENCE_INFO_STRUCT();	
}