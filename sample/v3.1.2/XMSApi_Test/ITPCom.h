#ifndef __ITP_COM_H__
#define __ITP_COM_H__

#include "ITPMsgPublic.h"
#include "ITPDataDefine.h"

#define ITP_SYSTEM_FLAG 0x49545031  // ITPϵͳ��ʶ

///////////////// ģ�����ӵ������ʱ�����͵���Ȩ������Ϣ //////////////////////
typedef struct
{	
	DJ_S32          m_ItpFlag;       // ϵͳ��ʶ	
	DJ_U8           m_u8ModuleType;  // ģ������
	DJ_U8           m_u8MainFuncId;  // �����ܺ�
	DJ_U8           m_u8SubFuncId;   // �ӹ��ܺ�
	DJ_U8           m_u8UnitId;      // ��Ԫ��			
	
	DJ_S32          m_Version;       // �汾��	
	DJ_S32          m_AckInfo;       // ȷ��ֵ,��ʼ0,�ɹ�1,����-1���ϲ㲻�ù���
	
	PKG_HEAD_STRUCT m_PkgHead;       // ��Ȩ��ͷ
	DJ_S8           m_s8Username[32];// ��Ȩ�û�
	DJ_S8           m_s8Password[32];// ��Ȩ����
	
	DJ_U8           m_u8Reserved[36];// ����	
}LICENCE_INFO_STRUCT, *PLICENCE_INFO_STRUCT;

///////////////// �ϲ�ģ���ѯ��������޿ͻ��������õ��Ľṹ //////////////////
typedef struct
{
	DJ_SOCKET     m_SkForListen;     // ��������ʱ�õ����׽��֣���������
	DJ_SOCKET     m_SkForClient;     // ��������ʱ���ص��׽��֣�����ͨѶ
	DJ_S8         m_szIP[32];        // �ͻ���IP��ַ
	DJ_S32        m_Port;            // �ͻ��˶˿ں�

	LICENCE_INFO_STRUCT Licence;	
}CONN_INFO_STRUCT, *PCONN_INFO_STRUCT;


#ifdef __cplusplus
extern "C" 
{
#endif

DJ_S32  TCP_SkOpen(DJ_SOCKET *ps);                                   // ��һ���׽���
DJ_S32  TCP_SkClose(DJ_SOCKET s);                                    // �ر�һ���׽���

DJ_S32  TCP_SkConnect(DJ_SOCKET s, DJ_S8* pszIP, DJ_S32 Port, PLICENCE_INFO_STRUCT pLicence);

DJ_S32  TCP_SkWaitSet(DJ_SOCKET s, DJ_S8* pszIP, DJ_S32 Port);       // ���а󶨺ͼ���
DJ_S32  TCP_SkWaitConnect(DJ_SOCKET s);                              // �����ȴ��߳�
DJ_S32  TCP_SkGetConnect(DJ_SOCKET s, PCONN_INFO_STRUCT pConnInfo);  // ��ѯ�ͻ�����						
DJ_S32  TCP_SkEasyAuthorize(DJ_SOCKET s, DJ_S8* pszUsername,DJ_S8* pszPassword, DJ_U8 f = 0);

DJ_S32  TCP_SkSend(DJ_SOCKET s, PPKG_HEAD_STRUCT pHead);             // ��������
DJ_S32  TCP_SkRecv(DJ_SOCKET s, PPKG_HEAD_STRUCT pHead);             // ��������

DJ_S32  TCP_SkGetLastError();                                        // ���Ĵ������

DJ_S32  TCP_SkBeginLOGFile(DJ_S8* pszFilename);                      // ��ʼд��־�ļ�
DJ_S32  TCP_SkEndLOGFile();                                          // ����д��־�ļ�

DJ_S32  TCP_SkStartup();                                             // ��ʼ��(Linuxר��)
DJ_S32  TCP_SkCleanup();                                             // ���(Linuxר��)

#ifdef __cplusplus
}
#endif

#endif
