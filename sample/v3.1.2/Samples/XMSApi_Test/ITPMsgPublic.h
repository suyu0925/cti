//*****************************************************************************
//Copyright(c)  :  DONJIN CORPORTAION  All Rights Reserved                       
//FileName      :  ITPMsgPublic.h                                                              
//Version       :  1.1                                                              
//Author        :  ����                                                             
//DateTime      :  2005-06-30 15:00                                           
//Description  :   ITPϵͳ������Ϣ����Ϣ�����ݽṹ���嵥Ԫ(��Ҫ���������̽���ͨѶ)                                                               
//*****************************************************************************
//*****************************************************************************
//Version       :  1.1.1
//mender        :  ����
//DateTime      :  2005-10-28 09:00  
//Description  :   ����ITPϵͳ���������ģ�����Ϣ��                                                             
//*****************************************************************************
//*****************************************************************************
//Version       :  1.1.2
//mender        :  ����
//DateTime      :  2005-11-04 11:00  
//Description  :   ����ITPͨѶ��Ϣ��ͷ�����ֶεĶ���                                                          
//*****************************************************************************



#ifndef _ITPMSGPUBLIC_H
#define _ITPMSGPUBLIC_H


#include "ITPDataDefine.h"

//ͨѶ�������ֶεĶ���
#define PKG_EXTEND_NORMAL     0x00
#define PKG_EXTEND_ERROR      0x01
#define PKG_EXTEND_CONFIG     0x02
#define PKG_EXTEND_INTERFACE  0x03
// ����˫������ʱ���ְ��ķ��ͷ���
#define PKG_EXTEND_UPPER	  0x04		// �ϼ�ģ���
#define PKG_EXTEND_LOWER	  0x05		// �¼�ģ���
//ͨѶ��Ϣ��ͷ

typedef struct
{
	DJ_U8	m_u8PkgFlag;	// ����־: 0xa5,0x5a
	DJ_U8	m_u8PkgExtend;	// ����չλ
	
	DJ_U16	m_u16DataLen;	//���������ݳ���

    //GUID����ɲ���
	struct ITP_GUID_tag
	{
	    DJ_U8   m_u8ModuleType;  //ģ������
	    DJ_U8   m_u8MainFuncId;  //������ID      
	    DJ_U8   m_u8SubFuncId;   //�ӹ���ID
	    DJ_U8   m_u8UnitId;      //��ԪID 
	    DJ_U16  m_u16ChanId;     //ͨ��ID
	}ITP_GUID;

	DJ_U16 m_u16Reserve;     //�����ֶ�

}PKG_HEAD_STRUCT, *PPKG_HEAD_STRUCT;

#define PKG_HEAD_LEN  sizeof(PKG_HEAD_STRUCT)

enum PACKAGE_TYPE
{
	PKG_CMD = 0x5A,         // �������ݰ�
	PKG_EVT = 0xA5          // �¼����ݰ�
};

//************���ù���ģ����Ϣ��*****************


//ģ��״̬����
/*˵��:
ģ��״̬��һ��DJ_U16���Ͷ��壬����DJ_U16 u16ModuleStates
����bit0 = 1,��ʾģ���Ѿ���ʼ��, bit0 = 0 ��ʾģ��δ��ʼ�������ͷ�
����bit1 = 1,��ʾģ���Ѿ�����  , bit1 = 0 ��ʾģ���Ѿ�ֹͣ
����bit2 = 1,��ʾģ��ȫ������  , bit2 = 0 ��ʾģ�黹�в��ֻ�ȫ��δ����
����bit3 = 1,��ʾģ���ѱ�����  , bit3 = 0 ��ʾģ��δ������
����bit4 = 1,��ʾģ���Ѿ�����  , bit4 = 0 ��ʾģ��Ͽ�����
����bit5 = 1,��ʾģ������ֹͣ  , 
����bit6 = 1,��ʾģ����������  , bit6 = 0,��ʾģ��û������  , 
����9��bitλ��ʱû���õ�

*/

#define MODULE_INIT     0x01    //ģ���ѳ�ʼ��
#define MODULE_START    0x02    //ģ��������
#define MODULE_RELATE   0x04    //ģ����ȫ�������ϼ�ģ�����
#define MODULE_MONITOR  0x08    //ģ���ѱ�����
#define MODULE_CONNECT  0x10    //ģ��������
#define MODULE_STOPPING 0x20    //ģ������ֹͣ
#define MODULE_ISTUNING 0x40    //��������ģ��

enum
{
	ITP_REPORT_MODSTATE_NORMAL    = 0x0,
	ITP_REPORT_MODSTATE_COMMBAD   = 0x1,
};

//����������
typedef struct 
{
	DJ_U32	m_u32time;
	DJ_U32	m_u32date;
	DJ_U16  m_u16ModuleStates;
	DJ_U16  m_u16Param;
}ITP_HEART_TIME,*PITP_HEART_TIME;

typedef struct
{
	DJ_U8        m_u8ModuleType;		//ģ������
	DJ_U8        m_u8UnitID;			//ģ��ĵ�ԪID
	DJ_U32       m_u32IPAddress;		//��ģ���IP
	DJ_U32       m_u32BuddyIPAddress;	//�Զ�ģ��IP
	DJ_U8        m_u8ActiveState;		//��ģ��״̬��1:��ģ��״̬��0:��ģ��״̬

}ITP_MODULE_HOTSTANDBY_INFO,*PITP_MODULE_HOTSTANDBY_INFO;

typedef struct 
{
	DJ_U8  m_u8ExceptionType;	//ģ���쳣����  0��ͨѶ�쳣��1���ڲ��߼��쳣
	DJ_U8  m_u8ModuleType;		//�Ͽ�ģ������
	DJ_U8  m_u8UnitID;			//�Ͽ�ģ��ID
	DJ_U32 m_u32IPAddress;		//�Ͽ�ģ��IP

}ITP_MODULE_EXCEPTION,*PITP_MODULE_EXCEPTION;

typedef struct
{
	DJ_U16       m_u16ModState;   //ģ���쳣����  0�����쳣��1��ͨѶ�쳣��2���ڲ��߼��쳣
	DJ_U8        m_u8ModuleType;   //�Ͽ�ģ������
	DJ_U8        m_u8UnitID;       //�Ͽ�ģ��ID
	DJ_U32       m_u32IPAddress;   //�Ͽ�ģ��IP
}ITP_MODSTATE_REPORT,*PITP_MODSTATE_REPORT;

//����ģ������
//ϵͳ������Ϣ(����ģ����Ϣ)

typedef struct
{
	DJ_U8	m_u8ModuleType;			//ģ������
    DJ_U8   m_u8UnitID;				//ģ�鵥ԪID
	DJ_U16  m_u16Port;				//ģ�����ӵĶ˿ں�
    DJ_U32  m_u32IPAddress;			//ģ��IP��ַ
}ITP_MODULE_ADDR,*PITP_MODULE_ADDR;


typedef struct
{
	DJ_U8	m_u8ModuleType;			//ģ������
    DJ_U8   m_u8UnitID;				//ģ�鵥ԪID
	DJ_U16  m_u16Port;				//ģ�����ӵĶ˿ں�
    DJ_U32  m_u32IPAddress;			//ģ��IP��ַ
	DJ_U32  m_u32RelateFlag;        //���ӷ���
}ITP_MODULE_RELATE_ADDR,*PITP_MODULE_RELATE_ADDR;

typedef struct
{
	DJ_S8         m_s8Username[32]; // ��Ȩ�û�
	DJ_S8         m_s8Password[32]; // ��Ȩ����	
}ITP_MOD_VALIDITY_DATA,*PITP_MOD_VALIDITY_DATA;

//���ģ�����ݰ�
typedef struct
{
	DJ_U8	m_u8ModuleType;      //ģ������
    DJ_U8   m_u8UnitID;          //ģ�鵥ԪID
	DJ_U16  m_u16ChanID;         //ģ��ͨ����
	DJ_U16	m_u16DebugLevel;     //ģ���ؼ���
    DJ_U16  m_u16UdpPort;        //ģ�����ӵ�UDP�˿ں�
    DJ_U32  m_u32IPAddress;      //ģ��IP��ַ
	DJ_U32	m_u32Reserved;       //�����ֶ�
}ITP_MONITOR_ADDR,*PITP_MONITOR_ADDR;

#define MAX_MACADDR_STR_LEN     0x14     //������ַ�ַ����������ֵ
#define MAX_MODULENAME_STR_LEN	0x10     //ģ�����ַ����������ֵ
#define MAX_ERRMSG_LEN          0x60     //������Ϣ�ַ����������ֵ

//��������ù���֮�����Ϣ��
typedef struct
{
    DJ_U8       m_u8ModuleType;       //ģ������
    DJ_U8       m_u8UnitID;           //��ԪID
    DJ_U8		m_u8IsEnable;         //�Ƿ�ʹ��ģ�� 0:��ʹ��; 1:ʹ��
    DJ_U8       m_u8DSPType;          //DSP����
    DJ_U16      m_u16ModuleStates;    //ģ��״̬
    DJ_S8       m_s8ModuleName[MAX_MODULENAME_STR_LEN]; //ģ����
    DJ_S8       m_s8pMACAddress[MAX_MACADDR_STR_LEN];  //������ַ����DSPΪȫ0
    DJ_U32      m_u32Version;         //ģ��汾��
    DJ_U32      m_u32IPAddress;       //IP��ַ
    DJ_U32      m_u32Port;            //����˿�
	DJ_U32      m_u32Param;           //��������
}ITP_MODULE_STRUCT,*PITP_MODULE_STRUCT;

//���������
typedef struct
{
    DJ_S32      m_s32ErrorCode;
    DJ_S8       m_s8pErrMsg[MAX_ERRMSG_LEN];
}ITP_ERROR_STRUCT,*PITP_ERROR_STRUCT;

//**************************************
//ITP���ý��������ģ�����Ϣ��


//���ڵ��ʶ
#define ITP_ROOT_NODE      0x01

//�ڵ����ͣ�����޴˽ڵ㣬�򷵻�NODE_NONE
#define NODE_NONE       0x00
#define NODE_PARENT     0x01     //��֧����
#define NODE_RDONLY     0x02     //ֻ������
#define NODE_RDWR       0x03     //�ɶ�д����
#define NODE_SHOWONLY   0x04     //ֻ���б�����
#define NODE_RDWR_TABLE 0x05     //�ɶ�д�б����� 

//�ڵ㶨����Ϣ
typedef struct
{
	DJ_U8       m_u8NodeType;
	DJ_S8       m_s8ConfigName[31];
	DJ_S8       m_s8ConfigFileName[32];
	DJ_S32      m_s32NodeMsgCode;
    DJ_S32      m_s32ConfigNum;  
}ITP_INTERFACE_NODE_DATA,*PITP_INTERFACE_NODE_DATA;


//�ӽڵ��ʶ�б�
typedef struct
{
	DJ_U8       m_u8NodeType;
	DJ_S8       m_s8ConfigName[31];
	DJ_S32      m_s32NodeMsgCode;
}ITP_INTERFACE_SUBNODE_DATA,*PITP_INTERFACE_SUBNODE_DATA;


//��д�ڵ�����
typedef struct
{
	DJ_S32      m_s32IsWriteini;
	DJ_S32      m_s32NodeMsgCode;
	DJ_U16      m_u16FisrtData;
	DJ_U16      m_u16DataNum;
}ITP_INTERFACE_DONE_DATA,*PITP_INTERFACE_DONE_DATA;


//д�ڵ����ݽ��
typedef struct
{
	DJ_S32      m_s32NodeMsgCode;
	DJ_S32      m_s32RetCode;
}ITP_INTERFACE_WRDATA_MSG,*PITP_INTERFACE_WRDATA_MSG;

//���ڵ�������
typedef struct
{
	DJ_U8       m_u8NodeType;
	DJ_S8       m_s8ConfigFileName[31];
	DJ_S32      m_s32NodeMsgCode;
	DJ_U16      m_u16FisrtData;
	DJ_U16      m_u16DataNum;
}ITP_INTERFACE_RDATA_MSG,*PITP_INTERFACE_RDATA_MSG;
//**************************************


////ITP���ý����DSPģ����й̼����µ���Ϣ��

#define ERASE_PASSWORD 0x87654321    //DSP FLASH��������
#define MAX_DATA_BLOCK_LENGTH  4000  //д��FLASH���ݵ���󳤶�

//��FLASH����
typedef struct
{
    DJ_U32 m_u32AddrOffset;
	DJ_U32 m_u32ByteNum;
}ITP_FLASH_READ,*PITP_FLASH_READ;

//дFLASH����
typedef struct
{
    DJ_U32 m_u32AddrOffset;
	DJ_U32 m_u32ByteNum;
	DJ_U8  m_u8pData[MAX_DATA_BLOCK_LENGTH];
}ITP_FLASH_WRITE,*PITP_FLASH_WRITE;

//��FLASH�������
typedef struct
{
	DJ_U32 m_u32DataLen;
	DJ_U8  m_u8pData[MAX_DATA_BLOCK_LENGTH];
}ITP_FLASH_READ_MSG,*PITP_FLASH_READ_MSG;

//дFLASH�������
typedef struct
{
    DJ_U32 m_u32WriteStates;
	DJ_U32 m_u32CheckSum;
}ITP_FLASH_WRITE_MSG,*PITP_FLASH_WRITE_MSG;
//*******************************************************


//******************ý�崦�����Ϣ������***********************************
#define   MSG_MEDIA						0x3000

#define   MSG_MEDIA_DEV					MSG_MEDIA + 0x100
#define   MSG_MEDIA_DEV_OPEN			MSG_MEDIA_DEV + 0x001
#define   MSG_MEDIA_DEV_CLOSE			MSG_MEDIA_DEV + 0x002
#define   MSG_MEDIA_DEV_STOP			MSG_MEDIA_DEV + 0x003

#define   MSG_MEDIA_PLAYREC				MSG_MEDIA_DEV + 0x100
#define   MSG_MEDIA_PLAYREC_PLAY		0x001
#define   MSG_MEDIA_PLAYREC_RECORD		0x002

#define   MSG_MEDIA_UT					MSG_MEDIA_PLAYREC + 0x100

#define   MSG_MEDIA_FSK					MSG_MEDIA_UT + 0x100

#define   MSG_MEDIA_EC					MSG_MEDIA_FSK + 0x100

#define   MSG_MEDIA_DTMF				MSG_MEDIA_EC + 0x100

#define   MSG_MEDIA_CA					MSG_MEDIA_DTMF + 0x100

#define   MSG_MEDIA_DIAL				MSG_MEDIA_CA + 0x100

#define   MSG_MEDIA_PARM				MSG_MEDIA_DIAL + 0x100

#define   MSG_MEDIA_CONF				MSG_MEDIA_PARM + 0x100

#define   MSG_MEDIA_MS					MSG_MEDIA_CONF + 0x100
#define   MSG_MEDIA_MS_SEND				MSG_MEDIA_MS + 0x001
#define   MSG_MEDIA_MS_RECV				MSG_MEDIA_MS + 0x002
#define   MSG_MEDIA_MS_VLDRSC			MSG_MEDIA_MS + 0x003



#define   MSG_MEDIA_END               0x3FFF
//**************************************************************************

//**************************************




//**************************************



//��Ϣ������
DJ_S32 ITP_Msg_GetDataLen(PPKG_HEAD_STRUCT pPkgHead);
DJ_U8 *ITP_Msg_GetData(PPKG_HEAD_STRUCT pPkgHead);
DJ_S32 ITP_Msg_Init(PPKG_HEAD_STRUCT *ppPkgHead, DJ_S32 s32DataLen);
DJ_Void ITP_Msg_Release(PPKG_HEAD_STRUCT *ppPkgHead);
DJ_S32 ITP_Msg_AttachData(PPKG_HEAD_STRUCT *ppPkgHead,DJ_U8 *u8pData, DJ_S32 s32DataLen);
DJ_Void ITP_Msg_ClearData(PPKG_HEAD_STRUCT pPkgHead);



#endif
