unit DJITPCom;

interface

uses
  SysUtils, Variants, Messages, Windows, DJAcsDataDef;

const ITP_SYSTEM_FLAG = $49545031;  // ITPϵͳ��ʶ

///////////////// ģ�����ӵ������ʱ�����͵���Ȩ������Ϣ //////////////////////
Type
  LICENCE_INFO_STRUCT = record
	m_ItpFlag      : Integer;   // ϵͳ��ʶ
	m_u8ModuleType : Byte;      // ģ������
	m_u8MainFuncId : Byte;      // �����ܺ�
	m_u8SubFuncId  : Byte;      // �ӹ��ܺ�
	m_u8UnitId     : Byte;      // ��Ԫ��
	
	m_Version      : Integer;       // �汾��
	m_AckInfo      : Integer;       // ȷ��ֵ,��ʼ0,�ɹ�1,����-1���ϲ㲻�ù���

  m_PkgHead    : PKG_HEAD_STRUCT;         // ��Ȩ��ͷ
	m_s8Username : Array[0..31] of ShortInt;// ��Ȩ�û�
	m_s8Password : Array[0..31] of ShortInt;// ��Ȩ����
	
	m_u8Reserved : Array[0..35] of Byte;    // ����
end;

///////////////// �ϲ�ģ���ѯ��������޿ͻ��������õ��Ľṹ //////////////////
Type
  CONN_INFO_STRUCT = record
	m_SkForListen : DWORD;                      // ��������ʱ�õ����׽��֣���������
	m_SkForClient : DWORD;                      // ��������ʱ���ص��׽��֣�����ͨѶ
	m_szIP        : Array[0..31] of ShortInt;   // �ͻ���IP��ַ
	m_Port        : Integer;                    // �ͻ��˶˿ں�

	Licence : LICENCE_INFO_STRUCT;
end;

implementation

end.
