package DJKeygoe;

public class DJITPCom {

}

///////////////// ģ�����ӵ������ʱ�����͵���Ȩ������Ϣ //////////////////////
class LICENCE_INFO_STRUCT
{	
	public int          	m_ItpFlag;       // ϵͳ��ʶ	
	public byte           	m_u8ModuleType;  // ģ������
	public byte           	m_u8MainFuncId;  // �����ܺ�
	public byte           	m_u8SubFuncId;   // �ӹ��ܺ�
	public byte           	m_u8UnitId;      // ��Ԫ��			
	public int          	m_Version;       // �汾��	
	public int          	m_AckInfo;       // ȷ��ֵ,��ʼ0,�ɹ�1,����-1���ϲ㲻�ù���
	public PKG_HEAD_STRUCT  m_PkgHead = new PKG_HEAD_STRUCT();       // ��Ȩ��ͷ
	public byte           	m_s8Username[] = new byte[32];// ��Ȩ�û�
	public byte           	m_s8Password[] = new byte[32];// ��Ȩ����
	public byte           	m_u8Reserved[] = new byte[36];// ����	
}

///////////////// �ϲ�ģ���ѯ��������޿ͻ��������õ��Ľṹ //////////////////
class CONN_INFO_STRUCT
{
	public int     m_SkForListen;     // ��������ʱ�õ����׽��֣���������
	public int     m_SkForClient;     // ��������ʱ���ص��׽��֣�����ͨѶ
	public byte    m_szIP[] = new byte[32];        // �ͻ���IP��ַ
	public int     m_Port;            // �ͻ��˶˿ں�
	public LICENCE_INFO_STRUCT Licence = new LICENCE_INFO_STRUCT();	
}