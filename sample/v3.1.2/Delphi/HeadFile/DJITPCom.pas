unit DJITPCom;

interface

uses
  SysUtils, Variants, Messages, Windows, DJAcsDataDef;

const ITP_SYSTEM_FLAG = $49545031;  // ITP系统标识

///////////////// 模块连接到服务端时，发送的授权请求信息 //////////////////////
Type
  LICENCE_INFO_STRUCT = record
	m_ItpFlag      : Integer;   // 系统标识
	m_u8ModuleType : Byte;      // 模块类型
	m_u8MainFuncId : Byte;      // 主功能号
	m_u8SubFuncId  : Byte;      // 子功能号
	m_u8UnitId     : Byte;      // 单元号
	
	m_Version      : Integer;       // 版本号
	m_AckInfo      : Integer;       // 确认值,初始0,成功1,错误-1，上层不用关心

  m_PkgHead    : PKG_HEAD_STRUCT;         // 授权包头
	m_s8Username : Array[0..31] of ShortInt;// 授权用户
	m_s8Password : Array[0..31] of ShortInt;// 授权密码
	
	m_u8Reserved : Array[0..35] of Byte;    // 备用
end;

///////////////// 上层模块查询服务端有无客户端连接用到的结构 //////////////////
Type
  CONN_INFO_STRUCT = record
	m_SkForListen : DWORD;                      // 接受连接时用到的套节字：用来监听
	m_SkForClient : DWORD;                      // 接受连接时返回的套节字：用来通讯
	m_szIP        : Array[0..31] of ShortInt;   // 客户端IP地址
	m_Port        : Integer;                    // 客户端端口号

	Licence : LICENCE_INFO_STRUCT;
end;

implementation

end.
