package DJKeygoe;

public class DJITPMsgPublic {
	//ͨѶ�������ֶεĶ���
	public static final int   PKG_EXTEND_NORMAL     = 0x00;
	public static final int   PKG_EXTEND_ERROR      = 0x01;
	public static final int   PKG_EXTEND_CONFIG     = 0x02;
	public static final int   PKG_EXTEND_INTERFACE  = 0x03;
	//����˫������ʱ���ְ��ķ��ͷ���
	public static final int   PKG_EXTEND_UPPER	  	= 0x04;		// �ϼ�ģ���
	public static final int   PKG_EXTEND_LOWER	  	= 0x05;		// �¼�ģ���
	
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
	public static final int   MODULE_INIT     		= 0x01;    //ģ���ѳ�ʼ��
	public static final int   MODULE_START    		= 0x02;    //ģ��������
	public static final int   MODULE_RELATE   		= 0x04;    //ģ����ȫ�������ϼ�ģ�����
	public static final int   MODULE_MONITOR  		= 0x08;    //ģ���ѱ�����
	public static final int   MODULE_CONNECT  		= 0x10;    //ģ��������
	public static final int   MODULE_STOPPING 		= 0x20;    //ģ������ֹͣ
	public static final int   MODULE_ISTUNING 		= 0x40;    //��������ģ��
	public static final int   MODULE_SETSTANDBY 	= 0x80;    //��Ҫ��������ģ��
	
	
	//******************ý�崦�����Ϣ������***********************************
	public static final int   MSG_MEDIA						= 0x3000;
	public static final int   MSG_MEDIA_DEV					= MSG_MEDIA + 0x100;
	public static final int   MSG_MEDIA_DEV_OPEN			= MSG_MEDIA_DEV + 0x001;
	public static final int   MSG_MEDIA_DEV_CLOSE			= MSG_MEDIA_DEV + 0x002;
	public static final int   MSG_MEDIA_DEV_STOP			= MSG_MEDIA_DEV + 0x003;
	public static final int   MSG_MEDIA_PLAYREC				= MSG_MEDIA_DEV + 0x100;
	public static final int   MSG_MEDIA_PLAYREC_PLAY		= 0x001;
	public static final int   MSG_MEDIA_PLAYREC_RECORD		= 0x002;
	public static final int   MSG_MEDIA_UT					= MSG_MEDIA_PLAYREC + 0x100;
	public static final int   MSG_MEDIA_FSK					= MSG_MEDIA_UT + 0x100;
	public static final int   MSG_MEDIA_EC					= MSG_MEDIA_FSK + 0x100;
	public static final int   MSG_MEDIA_DTMF				= MSG_MEDIA_EC + 0x100;
	public static final int   MSG_MEDIA_CA					= MSG_MEDIA_DTMF + 0x100;
	public static final int   MSG_MEDIA_DIAL				= MSG_MEDIA_CA + 0x100;
	public static final int   MSG_MEDIA_PARM				= MSG_MEDIA_DIAL + 0x100;
	public static final int   MSG_MEDIA_CONF				= MSG_MEDIA_PARM + 0x100;
	public static final int   MSG_MEDIA_MS					= MSG_MEDIA_CONF + 0x100;
	public static final int   MSG_MEDIA_MS_SEND				= MSG_MEDIA_MS + 0x001;
	public static final int   MSG_MEDIA_MS_RECV				= MSG_MEDIA_MS + 0x002;
	public static final int   MSG_MEDIA_MS_VLDRSC			= MSG_MEDIA_MS + 0x003;
	public static final int   MSG_MEDIA_END               	= 0x3FFF;
	
	
	//���ڵ��ʶ
	public static final int   ITP_ROOT_NODE      			= 0x01;

	//�ڵ����ͣ�����޴˽ڵ㣬�򷵻�NODE_NONE
	public static final int   NODE_NONE       				= 0x00;
	public static final int   NODE_PARENT     				= 0x01;     //��֧����
	public static final int   NODE_RDONLY     				= 0x02;     //ֻ������
	public static final int   NODE_RDWR       				= 0x03;     //�ɶ�д����
	public static final int   NODE_SHOWONLY   				= 0x04;     //ֻ���б�����
	public static final int   NODE_RDWR_TABLE 				= 0x05;     //�ɶ�д�б����� 
}

//ͨѶ��Ϣ��ͷ

//�������Բ�ͨѶ�¼��ṹ
class FLOW_INTERDATA_HEAD
{
	public PKG_HEAD_STRUCT  m_PkgHead	= new PKG_HEAD_STRUCT();                                 //�¼���ͷ
	public CallID_t         m_SrcCallID = new CallID_t();                               //Դ����
	public CallID_t         m_destCallID= new CallID_t();                              //Ŀ������
	public int           	m_u32CmdType;                              //�Զ�����������
	public int  	        m_u32InterNameLen;                         //�û��ṹ������
	public byte             m_s8InterName[] = new byte[120]; //�û��ṹ��
	public int      	    m_u32InterDataSize;                        //�û��Զ���ṹ��С
}

class PACKAGE_TYPE
{
	public static final int   PKG_CMD = 0x5A;          // �������ݰ�
	public static final int   PKG_EVT = 0xA5;          // �¼����ݰ�
}

class REPORT_MODSTATE
{
	public static final int   ITP_REPORT_MODSTATE_NORMAL    = 0x0;
	public static final int   ITP_REPORT_MODSTATE_COMMBAD   = 0x1;
}

//����������
class ITP_HEART_TIME 
{
	public int		m_u32time;
	public int		m_u32date;
	public short	m_u16ModuleStates;
	public byte     m_u8HotState;
	public byte     m_u8HotWorkState;
}

//���͸�DSP��������Ϣ

class ITP_DSP_HOTSTANDBY_INFO
{
	public byte     m_u8IPNum;                          //IP ��Ŀ
	public byte     m_u8Reverse[] = new byte[3];      
	public int	    m_u32IPAddress[] = new int[5];      //��ģ���IP��
}


//�ӱ���config server��������config server����ģ����Ϣ�ṹ
class CONFIG_MODULE_STRUCT
{
	public byte        m_u8ModuleType;     //ģ������
	public byte        m_u8UnitID;         //ģ��ĵ�ԪID
	public byte        m_u8Reverse[] = new byte[2];
	
	public int         m_u32IPAddress;
	public int         m_u32Port;
}


//������config server��ģ�鷢���л���Ϣ
class CONFIG_HOTSTANDBY_STRUCT
{
	public byte        m_u8HOTState;    //���öԷ�������, 0 ��ģ�� ��1 ��ģ��
	public byte        m_u8RetVal;      //�����Ƿ�ɹ�  1 ʧ��  1 �ɹ�
	public byte        m_u8HotWorkState; //������������״̬
	public byte        m_u8Reverse;
}


class ITP_MODULE_EXCEPTION 
{
	public byte    	   m_u8ExceptionType;	//ģ���쳣����  0��ͨѶ�쳣��1���ڲ��߼��쳣
	public byte    	   m_u8ModuleType;		//�Ͽ�ģ������
	public byte    	   m_u8UnitID;			//�Ͽ�ģ��ID
	public int   	   m_u32IPAddress;		//�Ͽ�ģ��IP

}

class ITP_MODSTATE_REPORT
{
	public short       m_u16ModState;   //ģ���쳣����  0�����쳣��1��ͨѶ�쳣��2���ڲ��߼��쳣
	public byte        m_u8ModuleType;   //�Ͽ�ģ������
	public byte        m_u8UnitID;       //�Ͽ�ģ��ID
	public int         m_u32IPAddress;   //�Ͽ�ģ��IP
}

//����ģ������
//ϵͳ������Ϣ(����ģ����Ϣ)

class ITP_MODULE_ADDR
{
	public byte		   m_u8ModuleType;			//ģ������
	public byte		   m_u8UnitID;				//ģ�鵥ԪID
	public short	   m_u16Port;				//ģ�����ӵĶ˿ں�
	public int		   m_u32IPAddress;			//ģ��IP��ַ
}

class ITP_MODULE_RELATE_ADDR
{
	public byte		   m_u8ModuleType;			//ģ������
	public byte		   m_u8UnitID;				//ģ�鵥ԪID
	public short	   m_u16Port;				//ģ�����ӵĶ˿ں�
	public int		   m_u32IPAddress;			//ģ��IP��ַ
	public int		   m_u32RelateFlag;         //���ӷ���
}

class ITP_MOD_VALIDITY_DATA
{
	public byte        m_s8Username[] = new byte[32]; // ��Ȩ�û�
	public byte        m_s8Password[] = new byte[32]; // ��Ȩ����	
}

//���ģ�����ݰ�
class ITP_MONITOR_ADDR
{
	public byte    	   m_u8ModuleType;      //ģ������
	public byte        m_u8UnitID;          //ģ�鵥ԪID
	public short  	   m_u16ChanID;         //ģ��ͨ����
	public short	   m_u16DebugLevel;     //ģ���ؼ���
	public short  	   m_u16UdpPort;        //ģ�����ӵ�UDP�˿ں�
	public int  	   m_u32IPAddress;      //ģ��IP��ַ
	public int		   m_u32Reserved;       //�����ֶ�
}

//��������ù���֮�����Ϣ��
class ITP_MODULE_STRUCT
{
	public byte        m_u8ModuleType;       //ģ������
	public byte        m_u8UnitID;           //��ԪID
	public byte		   m_u8IsEnable;         //�Ƿ�ʹ��ģ�� 0:��ʹ��; 1:ʹ��
	public byte        m_u8DSPType;          //DSP����
	public short       m_u16ModuleStates;    //ģ��״̬
	public byte        m_s8ModuleName[] = new byte[16]; //ģ����
	public byte        m_s8pMACAddress[] = new byte[20];  //������ַ����DSPΪȫ0
	public int	       m_u32Version;         //ģ��汾��
	public int         m_u32IPAddress;       //IP��ַ
	public int         m_u32Port;            //����˿�
	public int         m_u32Param;           //��������
}

//���������
class ITP_ERROR_STRUCT
{
	public int      m_s32ErrorCode;
	public byte     m_s8pErrMsg[] = new byte[0x60];
}

//���ù����͸�VOIPģ�飬No2IP���óɹ�֪ͨ��Ϣ
class ITP_ADDIP_OK_NOTIFY_STRUCT
{
	public byte       m_u8ExcuteResult;
	public byte       m_u8Reserve[] = new byte[7];
}

//���ù����͸�FLOWģ�飬��֪�����Ѿ�����������֪ͨ��Ϣ
class ITP_SLAVE_WORK_NOTIFY_STRUCT
{
	public byte       m_u8WorkSate;            //0:�����쳣; 1: ��������
	public byte       m_u8Reserve[] = new byte[7];          //����
}


/* new snmp content - add by liangyu 20110706 - begin */
//**************************************
//ITP���ù���ģ���ȡSNMP���ݵ���Ϣ��

//��ͨ��״̬�����cfgSrv�����̣�
class ITP_CH_STATE_RESULT
{
	public short	 m_u8UnitID;				//��ԪID
	public short	 m_uReserved;				//����
	public int		 m_u16State[] = new int[128];			//DSP������ͨ��״̬
	public byte		 m_u8DeviceSubType[] = new byte[128];	//DSP���豸������
}

//��Q931״̬�����cfgSrv��Q931��
class ITP_Q931_STATE_RESULT
{
	public short	 m_u8UnitID;				//��ԪID
	public short	 m_u8PcmNum;				//PCM��
	public byte		 m_u8LinkState[]   = new byte[4];			//����״̬,����DEF�ļ�
	public byte		 m_u8RestartFlag[] = new byte[4];			//������־
}

//����״̬�����cfgSrv��proxy��
class ITP_PC_STATE_RESULT
{
	public int		 m_u32CpuIdle[] = new int[8];			//����CPU
	public int		 m_u32MemFree;						  	//�����ڴ�
	public int		 m_u32SwapFree;							//���н���
	public int		 m_u32HDFree;							//����Ӳ��
}

//mainmod�¼����ӹ�ϵ�����cfgSrv��mainmod��
class ITP_MAINMOD_DOWNRELATE_RESULT
{
	public byte	     m_u8ModuleType;			//ģ������
	public byte   	 m_u8UnitID;				//ģ�鵥ԪID
	public byte		 m_u8RelateIndex;		//ģ��Ĺ�����,0-255
	public byte		 m_u8RelateState;		//����״̬,0:����,1:�Ͽ�
}
/* new snmp content - add by liangyu 20110706 - end */

//**************************************
//ITP���ý��������ģ�����Ϣ��


//�ڵ㶨����Ϣ
class ITP_INTERFACE_NODE_DATA
{
	public byte       m_u8NodeType;
	public byte       m_s8ConfigName[] = new byte[31];
	public byte       m_s8ConfigFileName[] = new byte[32];
	public int        m_s32NodeMsgCode;
	public int        m_s32ConfigNum;  
}

//�ӽڵ��ʶ�б�
class ITP_INTERFACE_SUBNODE_DATA
{
	public byte       m_u8NodeType;
	public byte       m_s8ConfigName[] = new byte[31];
	public int	      m_s32NodeMsgCode;
}

//��д�ڵ�����
class ITP_INTERFACE_DONE_DATA
{
	public int	      m_s32IsWriteini;
	public int	      m_s32NodeMsgCode;
	public short	  m_u16FisrtData;
	public short      m_u16DataNum;
}


//д�ڵ����ݽ��
class ITP_INTERFACE_WRDATA_MSG
{
	public int	      m_s32NodeMsgCode;
	public int	      m_s32RetCode;
}

//���ڵ�������
class ITP_INTERFACE_RDATA_MSG
{
	public byte       m_u8NodeType;
	public byte       m_s8ConfigFileName[] = new byte[31];
	public int	      m_s32NodeMsgCode;
	public short      m_u16FisrtData;
	public short      m_u16DataNum;
}
//**************************************


////ITP���ý����DSPģ����й̼����µ���Ϣ��

//��FLASH����
class ITP_FLASH_READ
{
	public int	 m_u32AddrOffset;
	public int	 m_u32ByteNum;
}

//дFLASH����
class ITP_FLASH_WRITE
{
	public int	 m_u32AddrOffset;
	public int	 m_u32ByteNum;
	public byte	 m_u8pData[] = new byte[4000];
}

//��FLASH�������
class ITP_FLASH_READ_MSG
{
	public int	 m_u32DataLen;
	public byte	 m_u8pData[] = new byte[4000];
}

//дFLASH�������
class ITP_FLASH_WRITE_MSG
{
	public int	 m_u32WriteStates;
	public int	 m_u32CheckSum;
}
//*******************************************************

