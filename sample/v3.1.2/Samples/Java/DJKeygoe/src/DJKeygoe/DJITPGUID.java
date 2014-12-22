package DJKeygoe;

public class DJITPGUID {
	public static final int     MODULE_TYPE_PROXY       = 0x00;           //Proxyģ��
	public static final int     MODULE_TYPE_DSP    		= 0x01;           //DSP����ģ��
	public static final int     MODULE_TYPE_MEDIA	    = 0x02;           //ý�崦��ģ��
	public static final int     MODULE_TYPE_SS7        	= 0x03;           //�ߺŴ���ģ��	
	public static final int     MODULE_TYPE_CFG 	    = 0x04;           //����ģ��
	public static final int     MODULE_TYPE_MONITOR 	= 0x05;           //���ģ��
	public static final int     MODULE_TYPE_FLOW       	= 0x06;	       //����ģ��
	public static final int     MODULE_TYPE_PRI        	= 0x07;	       //ISDN����ģ��
	public static final int     MODULE_TYPE_USER       	= 0x08;           //�û�ģ��
	public static final int     MODULE_TYPE_INTERFACE  	= 0x09;           //����ģ��
	public static final int     MODULE_TYPE_VOIP       	= 0x0A;           //VoIPģ��
	public static final int     MODULE_TYPE_3G324M     	= 0x0B;           //3G-324Mģ��
	public static final int     MODULE_TYPE_MEDIAEX		= 0x0C;	       //ý������ģ��
	public static final int     MODULE_TYPE_FAXTIFF    	= 0x0E;           //FAXTIFFģ��
	public static final int     MODULE_TYPE_ACS        	= 0x0F;           //APIģ��
	public static final int     MODULE_TYPE_SIGMON     	= 0x10;           //������ģ��
	public static final int     MODULE_TYPE_CTXM       	= 0x11;           //��������ģ��
	//DSP����ģ�鹦��ID����***************************************
	public static final int     DSP_MAIN_FUNCTION_CONFIG      = 0x01;           //ȫ���豸����
	public static final int     DSP_MAIN_FUNCTION_SPEECH      = 0x02;           //��������
	public static final int     DSP_MAIN_FUNCTION_FAX         = 0x03;          //���湦��
	public static final int     DSP_MAIN_FUNCTION_DIGITAL     = 0x04;           //�����м̹���
	public static final int     DSP_MAIN_FUNCTION_INTERFACE   = 0x05;          //��ϯ����ģ��
	public static final int     DSP_MAIN_FUNCTION_PRILINK     = 0x06;           //���鹦��ģ��
	public static final int     DSP_MAIN_FUNCTION_SS7LINK     = 0x07;           //�����м̹���ģ��
	public static final int     DSP_MAIN_FUNCTION_CTCLK       = 0x08;           //CT_BUSʱ��
	public static final int     DSP_MAIN_FUNCTION_CTTS        = 0x09;           //CT_BUS��Դ
	public static final int     DSP_MAIN_FUNCTION_CONNECTTS   = 0x0A;           //ʱ϶����
	public static final int     DSP_MAIN_FUNCTION_FIRMWARE    = 0x0B;           //�̼�����
	public static final int     DSP_MAIN_FUNCTION_VOIP        = 0x0C;           //VoIP����
	public static final int     DSP_MAIN_FUNCTION_3G324M      = 0x0D;           //G-324M����
	public static final int     DSP_MAIN_FUNCTION_LICENSE     = 0x0E;           //license alarm
	public static final int     DSP_MAIN_FUNCTION_RTPX		  = 0x0F;		//Data exchange ����

	public static final int     DSP_MAIN_FUNCTION_CONFERENCE   = 0x10;           //for conference event
	public static final int     DSP_MAIN_FUNCTION_DEBUG_INFOR  = 0x11;     //for DSP debug information, add by zcq at 20090813
	public static final int     DSP_SUB_FUNCTION_LICENSE_INQUIRE     = 0x01;           //license alarm


	public static final int     SUB_FUNCTION_ALL                = 0xFF;        //�����ӹ���

	public static final int     DSP_SUB_FUNCTION_SPEECH_INPUT   = 0x01;        //���빦��(EC,AGC��)
	public static final int     DSP_SUB_FUNCTION_SPEECH_OUTPUT  = 0x02;        //�������(����,AGC��)
	public static final int     DSP_SUB_FUNCTION_SPEECH_PLAY    = 0x03;        //��������
	public static final int     DSP_SUB_FUNCTION_SPEECH_RECORD  = 0x04;        //¼������
	public static final int     DSP_SUB_FUNCTION_SPEECH_GTD     = 0x05;        //������Ƶ������
	public static final int     DSP_SUB_FUNCTION_SPEECH_CONF    = 0x06;        //���鴦����


	//DSP DSS1�ӹ��ܶ���
	public static final int     DSP_SUB_FUNCTION_DSS1_CFG_CMD_TO_DSP        = 0x01;      //DSS1�������        Q931->DSP
	public static final int     DSP_SUB_FUNCTION_DSS1_GET_CFG_TO_DSP        = 0x02;      //��ȡDSS1������Ϣ���Q931->DSP
	public static final int     DSP_SUB_FUNCTION_DSS1_CFG_INFO_TO_Q931      = 0x02;      //DSS1������Ϣ��        DSP->Q931   
	public static final int     DSP_SUB_FUNCTION_DSS1_CONTROL_CMD_TO_DSP    = 0x03;      //DSS1��������          Q931->DSP
	public static final int     DSP_SUB_FUNCTION_DSS1_STATE_EVENT_TO_Q931   = 0x03;      //DSS1״̬�¼�          DSP->Q931 
	public static final int     DSP_SUB_FUNCTION_DSS1_SIGNAL_DATA_TO_DSP    = 0x04;      //DSS1��������          Q931->DSP
	public static final int     DSP_SUB_FUNCTION_DSS1_SIGNAL_DATA_TO_Q931   = 0x04;      //DSS1��������          DSP->Q931
	public static final int     DSP_SUB_FUNCTION_DSS1_DATA_REQ_TO_Q931      = 0x05;      //DSS1���������        DSP->Q931
	public static final int     DSP_SUB_FUNCTION_DSS1_DEBUG_DATA_TO_Q931    = 0x06;      //DSS1������Ϣ��        DSP->Q931
	//DSP DSS1�ӹ��ܶ��� end

	//DSP �̼��ӹ��ܶ���
	public static final int     DSP_SUB_FUNCTION_FIRMWARE_READ_FLASH        = 0x01;      //��FLASH����
	public static final int     DSP_SUB_FUNCTION_FIRMWARE_WRITE_FLASH       = 0x02;      //дFLASH����
	public static final int     DSP_SUB_FUNCTION_FIRMWARE_ERASE_FLASH       = 0x03;      //����FLASH����
	public static final int     DSP_SUB_FUNCTION_FIRMWARE_FINISH_FLASH      = 0x04;      //����FLASH�������
	public static final int     DSP_SUB_FUNCTION_FIRMWARE_READ_SDRAM        = 0x06;      //��SDRAM����
	public static final int     DSP_SUB_FUNCTION_REBOOT                     = 0x07;      //DSP��������
	//DSP �̼��ӹ��ܶ���

	//******************************************************************************

	public static final int     MEDIA_MAIN_FUNCTION_STREAMPLAY    = 0x01;           //������
	//ý�幦��ģ�鹦��ID����***************************************
	public static final int     MEDIA_MAIN_FUNCTION_STREAMRECORD  = 0x02;           //��¼��

	//SS7�����ģ�鹦��ID����***************************************
	public static final int     SS7_MAIN_FUNCTION_ISUP      = 0x01;           //�ߺ�����
	public static final int     SS7_MAIN_FUNCTION_TUP       = 0x02;
	public static final int     SS7_MAIN_FUNCTION_SCCP      = 0x03;           //�ߺ�����SCCP
	public static final int     SS7_MAIN_FUNCTION_LINK      = 0x10;           //�ߺ�������·
	public static final int     SS7_MAIN_FUNCTION_FLOW      = 0x11;           //���̱�ʶ����

	//PRI�����ģ�鹦��ID����***************************************
	public static final int     PRI_MAIN_FUNCTION_Q931      = 0x01;           //Q.931����


	//����ģ�鹦��ID����***************************************

	public static final int     CONFIG_MAIN_FUNCTION_INIT        = 0x01;           //��ʼ��ģ��
	public static final int     CONFIG_MAIN_FUNCTION_START       = 0x02;           //����ģ��
	public static final int     CONFIG_MAIN_FUNCTION_STOP        = 0x03;           //ֹͣģ��
	public static final int     CONFIG_MAIN_FUNCTION_RELATE      = 0x04;           //����ģ��
	public static final int     CONFIG_MAIN_FUNCTION_UNRELATE    = 0x05;           //ֹͣ����ģ��
	public static final int     CONFIG_MAIN_FUNCTION_MONCONFIG   = 0x06;           //��������
	public static final int     CONFIG_MAIN_FUNCTION_MONSTART    = 0x07;           //��������
	public static final int     CONFIG_MAIN_FUNCTION_MONSTOP     = 0x08;           //����ֹͣ
	public static final int     CONFIG_MAIN_FUNCTION_HEART       = 0x09;           //������
	public static final int     CONFIG_MAIN_FUNCTION_VALIDITY    = 0x0A;           //ϵͳ������֤��
	public static final int     CONFIG_MAIN_FUNCTION_RELEAT      = 0x0B;
	public static final int     CONFIG_MAIN_FUNCTION_HOTSTANDBY  = 0x0C;           //��ģ�鷢�͵����ӹ�ϵ
	public static final int     CONFIG_MAIN_FUNCTION_HOTINFO     = 0x0D;           //��ģ�鷢�ʹ�ģ����Ϣ
	public static final int     CONFIG_MAIN_FUNCTION_IPINFO      = 0x0E;           //��ģ�鷢����IP��Ϣ
	public static final int     CONFIG_MAIN_FUNCTION_MODSTATE_REPORT    = 0x0F;
	public static final int     CONFIG_MAIN_FUNCTION_ADDNO2IP_NOTIFY    = 0x10;    //��VOIPģ�鷢����ӵڶ�IP��Ϣ

	public static final int     CONFIG_MAIN_FUNCTION_INTERFACE   		 = 0x10;           //����ģ�鷢�͹���������

	public static final int     CONFIG_MAIN_FUNCTION_USER        		 = 0x11;          //�û�ģ�鷢�͹���������
	public static final int     CONFIG_MAIN_FUNCTION_CFG         		 = 0x12;           //��һ�����ù����͹���������
	public static final int     CONFIG_MAIN_FUNCTION_SLAVE_WORK_NOTIFY   = 0x13;    //��FLOWģ�鷢�ͱ�����������֪ͨ��Ϣ


	public static final int    CONFIG_SUB_FUNCTION_INTERFACE_REQALL      = 0x01;    //��������ģ������
	public static final int    CONFIG_SUB_FUNCTION_INTERFACE_REQSINGAL   = 0x02;    //����ĳ��ģ������
	public static final int    CONFIG_SUB_FUNCTION_INTERFACE_REQINIT     = 0x03;    //����ĳ��ģ���ʼ��������
	public static final int    CONFIG_SUB_FUNCTION_INTERFACE_SETPARM     = 0x04;    //����ĳ��ģ�����(����IP,�Ƿ�ʹ�ܵ�)
	public static final int    CONFIG_SUB_FUNCTION_INTERFACE_SETINIT     = 0x05;    //����ģ���ʼ����
	public static final int    CONFIG_SUB_FUNCTION_INTERFACE_START       = 0x06;    //ģ���ʼ��������
	public static final int    CONFIG_SUB_FUNCTION_INTERFACE_STOP        = 0x07;   //ģ��ֹͣ
	public static final int    CONFIG_SUB_FUNCTION_INTERFACE_REQRELATE   = 0x08;    //����ģ�������Ϣ
	public static final int    CONFIG_SUB_FUNCTION_INTERFACE_TRANRELATE  = 0x09;    //ģ�������Ϣ
	public static final int    CONFIG_SUB_FUNCTION_INTERFACE_ADD         = 0x0a;    //����һ��ģ��
	public static final int    CONFIG_SUB_FUNCTION_INTERFACE_SUB         = 0x0b;    //ɾ��һ��ģ��
	public static final int    CONFIG_SUB_FUNCTION_INTERFACE_PASSWORD    = 0x0c;       //����ϵͳ���ֺ�ϵͳ��½����

	public static final int    CONFIG_SUB_FUNCTION_INTERFACE_REQRELATE_NEW   = 0x0d;    //����ģ�������Ϣ(new)
	public static final int    CONFIG_SUB_FUNCTION_INTERFACE_REQRELATE_ALL   = 0x0e;    //�������е�ģ�������Ϣ
	public static final int    CONFIG_SUB_FUNCTION_INTERFACE_HEART       	 = 0x10;   //������

	//����ģ����ӹ��ܶ���
	public static final int    CONFIG_SUB_FUNCTION_CFG_MODULE_INFO                 = 0x01;      //ģ����Ϣ
	public static final int    CONFIG_SUB_FUNCTION_CFG_SET_HOTSTANDBY              = 0x02;      //�ı����ӹ�ϵ
	public static final int    CONFIG_SUB_FUNCTION_CFG_REPLY_HOTSTANDBY            = 0x03;    //�ı����ӹ�ϵӦ��
	public static final int    CONFIG_SUB_FUNCTION_CFG_HEART                       = 0x04;    //���ù�����������
	//�û�ģ���ӹ��ܶ���
	public static final int    CONFIG_SUB_FUNCTION_USER_REQALL      = 0x01;        //��������ģ������
	public static final int    CONFIG_SUB_FUNCTION_USER_REQSINGAL   = 0x02;        //����ĳ��ģ������
	public static final int    CONFIG_SUB_FUNCTION_USER_REQRELATE   = 0x03;        //����ĳ��ģ�������Ϣ

	public static final int    CONFIG_SUB_FUNCTION_USER_SET_HOTSTANDBY   	= 0x04;        //�û���������ģ��Ϊ��

	public static final int    CONFIG_SUB_FUNCTION_READNODE					= 0x01;	// ������ڵ���Ϣ �÷�ͬ����������FACE_MAIN_FUNCTION_READNODE
	public static final int    CONFIG_SUB_FUNCTION_GETCHANNELSTATE			= 0x02;	// �����ȡͨ��״̬
	public static final int    CONFIG_SUB_FUNCTION_MODDOWNRELATE			= 0x03;	// ����mainmod������й���
	public static final int    CONFIG_SUB_FUNCTION_GETCHASSISINFO			= 0x04;	// ����DSP�����λ��Ϣ

	//����ģ�鹦��ID����***************************************
	public static final int    FACE_MAIN_FUNCTION_REQNODE                = 0x01;    //����ڵ㶨��
	public static final int    FACE_MAIN_FUNCTION_READNODE               = 0x02;    //���ڵ�����
	public static final int    FACE_MAIN_FUNCTION_WRITENODE              = 0x03;    //д�ڵ�����
	public static final int    FACE_MAIN_FUNCTION_SAVECONFIG             = 0x04;    //����ڵ�����
	public static final int    FACE_MAIN_FUNCTION_LOADCONFIG             = 0x05;    //ת�ؽڵ�����
	public static final int    FACE_MAIN_FUNCTION_LICENCE				 = 0x06;    //װ����֤�ļ�

	public static final int    FACE_MAIN_FUNCTION_PROXY                  = 0x08;    //���ý������

	public static final int    FACE_MAIN_FUNCTION_QUERY_CTBUS            = 0x0A;    //��ѯDSPͨ��CT-BUS��
	public static final int    FACE_MAIN_FUNCTION_QUERY_SLOT             = 0x0B;    //��ѯDSPʱ϶���ӹ�ϵ


	public static final int    FACE_SUB_FUNCTION_PROXY_ADDMODULE         = 0x01;   //ͨ����������һ��ģ��
	public static final int    FACE_SUB_FUNCTION_PROXY_SUBMODULE         = 0x02;   //ͨ������ɾ��һ��ģ��
	public static final int    FACE_SUB_FUNCTION_PROXY_GETMODULECONFIG			= 0x03;	 //ͨ�������ȡһ��ģ�������ļ�����
	public static final int    FACE_SUB_FUNCTION_PROXY_SETMODULECONFIG			= 0x04;	 //ͨ����������һ��ģ�������ļ�����
	public static final int    FACE_SUB_FUNCTION_PROXY_RESUMEMODULECONFIG		= 0x05;	 //ͨ������ָ�һ��ģ�������ļ�����
	public static final int    FACE_SUB_FUNCTION_PROXY_STOPALL					= 0x06;	 //ͨ������ֹͣ����Ϊ�˸��ǵ�ǰ�������ã�
	public static final int    FACE_SUB_FUNCTION_PROXY_SAVECFGFILE				= 0x07;	 //ͨ�������������ļ�
	public static final int    FACE_SUB_FUNCTION_PROXY_STARTALL				 = 0x08;	 //ͨ��������������0x06�ķ�������
	public static final int    FACE_SUB_FUNCTION_PROXY_GET_LOGMODCONFIG      = 0x09;	 //ͨ�������ȡ��־server����
	public static final int    FACE_SUB_FUNCTION_PROXY_SET_LOGMODCONFIG      = 0x0a;	 //ͨ������������־server����
	public static final int    FACE_SUB_FUNCTION_PROXY_GET_LOGMODINFO        = 0x0b;	 //ͨ�������ȡ��־server��Ϣ
	public static final int    FACE_SUB_FUNCTION_PROXY_RESETMODULE           = 0x0c;       //ͨ����������ģ��
	public static final int    FACE_MAIN_FUNCTION_HEART                      = 0x09;    //�����������

	//hn add for get link status at 20081212
	public static final int    FACE_MAIN_FUNCTION_QUERY_LINK_STATUS     = 0x0a;  	//��ѯʱ϶����״̬
	public static final int    FACE_SUB_FUNCTION_QUERY_UPLINK     		= 0x01;    //��ѯ������ʱ϶���ӹ�ϵ
	public static final int    FACE_SUB_FUNCTION_QUERY_DOWNLINK   		= 0x02;    //��ѯ������ʱ϶���ӹ�ϵ

	//end add
	//����ִ��ģ�鹦��ID����*************************************
	public static final int     CTX_MAIN_FUNCTION_CTXCMD                = 0xFA;	   //������������
	//����ִ��ģ���ӹ���ID����*************************************
	public static final int     CTX_SUB_FUNCTION_CTXREG                 = 0x01;     //ACS���ͽ�������ע������
	public static final int     CTX_SUB_FUNCTION_CTXLINK                = 0x02;     //ACS���ͽ�������Link����
	public static final int     CTX_SUB_FUNCTION_CTXAPPDATA             = 0x03;     //ACS����ע�ύ����AppData������
	public static final int     CTX_SUB_FUNCTION_REPORTSLOT             = 0x07;     //����ģ���򽻻����ķ���DSP��Ϣ

	//����ִ��ģ�鹦��ID����*************************************
	public static final int     FLOW_MAIN_FUNCTION_SYNCMD                = 0xFB;	   //����ͬ������
	//����ִ��ģ�鹦��ID����:�����¼�*************************************
	public static final int     FLOW_MAIN_FUNCTION_ACSEVT                = 0xFC;	   //�����¼�
	public static final int     FLOW_SUB_FUNCTION_MASTER_STATE           = 0x01;     //ACS�ϱ�Master״̬�¼�
	public static final int     FLOW_SUB_FUNCTION_SLAVE_WORK_STATE       = 0x02;     //ACS�ϱ�Slave Work״̬�¼�


	//����ִ��ģ�鹦��ID����:��������*************************************
	public static final int     FLOW_MAIN_FUNCTION_ACSCMD                = 0xFD;	   //��������
	public static final int     FLOW_MAIN_FUNCTION_TIMEREVT              = 0xFE;	   //��ʱ���¼�
	public static final int     MOD_MAIN_FUNCTION_MODHEART               = 0xFF;	   //��ģ��֮���������

	//����ִ��ģ���ӹ���ID����*************************************
	public static final int     FLOW_SUB_FUNCTION_INTERCMD               = 0x01;     //�����ڲ�����
	public static final int     FLOW_SUB_FUNCTION_REQDEVICE              = 0x02;     //ACS������Դ�б�
	public static final int     FLOW_SUB_FUNCTION_OPENDEVICE             = 0x03;     //ACS���豸
	public static final int     FLOW_SUB_FUNCTION_CLOSEDEVICE            = 0x04;     //ACS�ر��豸
	public static final int     FLOW_SUB_FUNCTION_RESETDEVICE            = 0x05;     //ACS��λ�豸
	public static final int     FLOW_SUB_FUNCTION_GETDEVSTATE            = 0x06;     //ACS��ȡ�豸״̬
	public static final int     FLOW_SUB_FUNCTION_SETDEVGROUP            = 0x07;     //ACS������Դ���
	public static final int     FLOW_SUB_FUNCTION_SETPARAM               = 0x08;     //ACS���ò���
	public static final int     FLOW_SUB_FUNCTION_GETPARAM               = 0x09;     //ACS���ò��� ...
	public static final int     FLOW_SUB_FUNCTION_MAKECALLOUT            = 0x0A;     //ACS�������
	public static final int     FLOW_SUB_FUNCTION_ALERTCALL              = 0x0B;     //ACS Alert����
	public static final int     FLOW_SUB_FUNCTION_ANSWERCALLIN           = 0x0C;     //ACSӦ�����
	public static final int     FLOW_SUB_FUNCTION_LINKDEV                = 0x0D;     //ACS�����豸
	public static final int     FLOW_SUB_FUNCTION_UNLINKDEV              = 0x0E;     //ACS����豸����
	public static final int     FLOW_SUB_FUNCTION_CLEARCALL              = 0x0F;     //ACS�������
	public static final int     FLOW_SUB_FUNCTION_JOINTOCONF             = 0x10;     //ACS�������
	public static final int     FLOW_SUB_FUNCTION_LEAVEFROMCONF          = 0x11;     //ACS�뿪����
	public static final int     FLOW_SUB_FUNCTION_CLEARCONF              = 0x12;     //ACSɾ������
	public static final int     FLOW_SUB_FUNCTION_PLAYFILE               = 0x13;     //ACS����
	public static final int     FLOW_SUB_FUNCTION_INITPLAYINDEX          = 0x14;     //ACS��ʼ������
	public static final int     FLOW_SUB_FUNCTION_BUILDINDEX             = 0x15;     //ACS������������
	public static final int     FLOW_SUB_FUNCTION_CONTROLPLAY            = 0x16;     //ACS���Ʒ���
	public static final int     FLOW_SUB_FUNCTION_RECORDFILE             = 0x17 ;    //ACS¼��
	public static final int     FLOW_SUB_FUNCTION_CONTROLRECORD          = 0x18 ;    //ACS����¼��
	public static final int     FLOW_SUB_FUNCTION_SENDFAX                = 0x19 ;    //ACS���ʹ���
	public static final int     FLOW_SUB_FUNCTION_STOPSENDFAX            = 0x1A ;    //ACSֹͣ���ʹ���
	public static final int     FLOW_SUB_FUNCTION_RECVFAX                = 0x1B ;    //ACS���մ���
	public static final int     FLOW_SUB_FUNCTION_STOPRECVFAX            = 0x1C ;    //ACSֹͣ���մ���
	public static final int     FLOW_SUB_FUNCTION_CHANGEMONITORFILTER    = 0x1D ;    //ACS�ı��¼�filter
	public static final int     FLOW_SUB_FUNCTION_SENDIODATA             = 0x1E ;    //ACS����IO����
	public static final int     FLOW_SUB_FUNCTION_SENDSIGMSG             = 0x1F ;    //ACS����������Ϣ
	public static final int     FLOW_SUB_FUNCTION_RECORDCSP              = 0x20;     //ACS�ڴ�¼��
	public static final int     FLOW_SUB_FUNCTION_CONTROLRECORDCSP       = 0x21;     //ACS�����ڴ�¼��
	public static final int     ACS_SUB_FUNCTION_DBGON                   = 0x22;     //����ʹ��
	public static final int     ACS_SUB_FUNCTION_DBGOFF                  = 0x23;     //���Խ�ֹ
	public static final int     FLOW_SUB_FUNCTION_PLAY3GPP               = 0x24;    //����3gpp
	public static final int     FLOW_SUB_FUNCTION_CONTROLPLAY3GPP        = 0x25;     //���Ʋ���3gpp
	public static final int     FLOW_SUB_FUNCTION_RECORD3GPP             = 0x26;     //����3gpp
	public static final int     FLOW_SUB_FUNCTION_CONTROLRECORD3GPP      = 0x27;     //���Ʋ���3gpp
	public static final int     FLOW_SUB_FUNCTION_PLAYCSP                = 0x28;     //ACS����CSP����
	public static final int     FLOW_SUB_FUNCTION_SENDPLAYCSP            = 0x29;     //ACS����CSP��������
	public static final int     FLOW_SUB_FUNCTION_CTXREG                 = 0x2A;     //ACS����Ctx Reg�¼�
	public static final int     FLOW_SUB_FUNCTION_CTXLINK                = 0x2B;     //ACS����CTX Link�¼�
	public static final int     FLOW_SUB_FUNCTION_CTXAPPDATA             = 0x2C;     //ACS����CTX AppData�¼�
	public static final int     FLOW_SUB_FUNCTION_LICQUERY               = 0x2E;     //ACS����License query
	public static final int     FLOW_SUB_FUNCTION_LINKQUERY              = 0x2F;     //ACS����Link query
	public static final int     FLOW_SUB_FUNCTION_INIT3GPPINDEX          = 0x30;     //ACS��ʼ��3gpp����
	public static final int     FLOW_SUB_FUNCTION_BUILD3GPPINDEX         = 0x31;     //ACS����3gpp����
	public static final int     FLOW_SUB_FUNCTION_SENDRAWFRAME           = 0x32;     //ACS����ԭʼFrame����
	public static final int     FLOW_SUB_FUNCTION_JOIN3GCONF             = 0x33;     //ACS���ͼ���3G����
	public static final int     FLOW_SUB_FUNCTION_LEAVE3GCONF            = 0x34;     //ACS�����뿪3G����
	public static final int     FLOW_SUB_FUNCTION_CLEAR3GCONF            = 0x35;     //ACS�������3G����
	public static final int     FLOW_SUB_FUNCTION_GET3GCONFLAYOUT        = 0x36;     //ACS���ͻ�ȡ3G����Layout
	public static final int     FLOW_SUB_FUNCTION_SET3GCONFLAYOUT        = 0x37;     //ACS��������3G����Layout
	public static final int     FLOW_SUB_FUNCTION_GET3GCONFVISABLE       = 0x38;     //ACS���ͻ�ȡ3G����visable
	public static final int     FLOW_SUB_FUNCTION_SET3GCONFVISABLE       = 0x39;     //ACS��������3G����visable
	public static final int     FLOW_SUB_FUNCTION_RESTART3GCONF          = 0x3A;     //ACS��������3G����
	public static final int     FLOW_SUB_FUNCTION_SETMASTER              = 0x3B;     //ACS����Master����
	public static final int     ACS_SUB_FUNCTION_TRAPEN                  = 0x40;     //���
	public static final int     FLOW_SUB_FUNCTION_BAKSYSSTART            = 0x50;     //ACS����BakSysStart�¼�
	public static final int     FLOW_SUB_FUNCTION_VOIPMONDATA            = 0x51;     //ACS����VoIP����
	public static final int     FLOW_SUB_FUNCTION_SYNDATA                = 0xFC;     //��������ģ��֮�������
	public static final int     FLOW_SUB_FUNCTION_MASTERCHG              = 0xFE;     //��������״̬�¼�
	public static final int     FLOW_SUB_FUNCTION_RESETCHAN              = 0xFF;     //���͸�λͨ���¼�

	//IP����ģ�鹦��ID����*******************************************

	//faxTiffģ��������
	public static final int    FAXTIFF_MAIN_FUNCTION_CHANGE  			 = 0x01;

	//faxTiffģ���ӹ���
	//���������
	public static final int    FAXTIFF_SUB_FUNCTION_CHANGE_DECOMPOSE	 = 0x01;  //�ֽ�
	public static final int    FAXTIFF_SUB_FUNCTION_CHANGE_COMPOSE		 = 0x02;  //�ϳ�
	public static final int    FAXTIFF_SUB_FUNCTION_PAGE_REQ			 = 0x03;  //�ֽ�ҳ����
	public static final int    FAXTIFF_SUB_FUNCTION_TRANS_CONTROL        = 0x04;  //ת������
	public static final int    FAXTIFF_SUB_FUNCTION_TRANS_ADDFILE		 = 0x05;  //�����ļ�
	public static final int    FAXTIFF_SUB_FUNCTION_TRANS_ADDHEADER    	 = 0x06;  //���Ӵ���ͷ
	public static final int    FAXTIFF_SUB_FUNCTION_TRANS_INIT			 = 0x07;  //��ʼ��

	//�¼�������
	public static final int    FAXTIFF_SUB_FUNCTION_DECOMPOSE_RESULT	 = 0x01;  //�ֽ���
	public static final int    FAXTIFF_SUB_FUNCTION_COMPOSE_RESULT		 = 0x02;  //�ϳɽ��
	public static final int    FAXTIFF_SUB_FUNCTION_TRANS_STATE			 = 0x03;  //ת��״̬
	public static final int    FAXTIFF_SUB_FUNCTION_LOCALFORMAT			 = 0x04;  //���ظ�ʽ
	//****************************************************************

	public static final int    MEDIAEX_MAIN_FUNCTION_REPORT_RTPPORT   	 = 0x01;
	public static final int    MEDIAEX_SUB_FUNCTION_REPORT_RTPPORT    	 = 0x02;

	//#endif
}
