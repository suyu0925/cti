unit DJITPGUID;

interface

const  MODULE_TYPE_PROXY      = $00;           //Proxyģ��
const  MODULE_TYPE_DSP    	  = $01;          //DSP����ģ��
const  MODULE_TYPE_MEDIA	    = $02;           //ý�崦��ģ��
const  MODULE_TYPE_SS7        = $03;           //�ߺŴ���ģ��
const  MODULE_TYPE_CFG 	      = $04;           //����ģ��
const  MODULE_TYPE_MONITOR 	  = $05;           //���ģ��
const  MODULE_TYPE_FLOW       = $06;	       //����ģ��
const  MODULE_TYPE_PRI        = $07;	       //ISDN����ģ��
const  MODULE_TYPE_USER       = $08;           //�û�ģ��
const  MODULE_TYPE_INTERFACE  = $09;           //����ģ��
const  MODULE_TYPE_VOIP       = $0A;           //VoIPģ��
const  MODULE_TYPE_3G324M     = $0B;           //3G-324Mģ��
const  MODULE_TYPE_MEDIAEX	  = $0C;	       //ý������ģ��
const  MODULE_TYPE_FAXTIFF    = $0E;           //FAXTIFFģ��
const  MODULE_TYPE_ACS        = $0F;           //APIģ��
const  MODULE_TYPE_SIGMON     = $10;           //������ģ��
const  MODULE_TYPE_CTXM       = $11;           //��������ģ��
//DSP����ģ�鹦��ID����***************************************
const  DSP_MAIN_FUNCTION_CONFIG      = $01;           //ȫ���豸����
const  DSP_MAIN_FUNCTION_SPEECH      = $02;           //��������
const  DSP_MAIN_FUNCTION_FAX         = $03;           //���湦��
const  DSP_MAIN_FUNCTION_DIGITAL     = $04;           //�����м̹���
const  DSP_MAIN_FUNCTION_INTERFACE   = $05;           //��ϯ����ģ��
const  DSP_MAIN_FUNCTION_PRILINK     = $06;           //���鹦��ģ��
const  DSP_MAIN_FUNCTION_SS7LINK     = $07;           //�����м̹���ģ��
const  DSP_MAIN_FUNCTION_CTCLK       = $08;           //CT_BUSʱ��
const  DSP_MAIN_FUNCTION_CTTS        = $09;           //CT_BUS��Դ
const  DSP_MAIN_FUNCTION_CONNECTTS   = $0A;           //ʱ϶����
const  DSP_MAIN_FUNCTION_FIRMWARE    = $0B;           //�̼�����
const  DSP_MAIN_FUNCTION_VOIP        = $0C;           //VoIP����
const  DSP_MAIN_FUNCTION_3G324M      = $0D;           //G-324M����
const  DSP_MAIN_FUNCTION_LICENSE     = $0E;           //license alarm
const  DSP_MAIN_FUNCTION_RTPX	= $0F;		//Data exchange ����

const  DSP_MAIN_FUNCTION_CONFERENCE  = $10;           //for conference event
const  DSP_MAIN_FUNCTION_DEBUG_INFOR  = $11;     //for DSP debug information, add by zcq at 20090813
const  DSP_SUB_FUNCTION_LICENSE_INQUIRE     = $01;           //license alarm


const  SUB_FUNCTION_ALL                = $FF;        //�����ӹ���

const  DSP_SUB_FUNCTION_SPEECH_INPUT   = $01;        //���빦��(EC,AGC��)
const  DSP_SUB_FUNCTION_SPEECH_OUTPUT  = $02;        //�������(����,AGC��)
const  DSP_SUB_FUNCTION_SPEECH_PLAY    = $03;        //��������
const  DSP_SUB_FUNCTION_SPEECH_RECORD  = $04;        //¼������
const  DSP_SUB_FUNCTION_SPEECH_GTD     = $05;        //������Ƶ������
const  DSP_SUB_FUNCTION_SPEECH_CONF    = $06;        //���鴦����


//DSP DSS1�ӹ��ܶ���
const  DSP_SUB_FUNCTION_DSS1_CFG_CMD_TO_DSP        = $01;      //DSS1�������        Q931->DSP
const  DSP_SUB_FUNCTION_DSS1_GET_CFG_TO_DSP        = $02;      //��ȡDSS1������Ϣ���Q931->DSP
const  DSP_SUB_FUNCTION_DSS1_CFG_INFO_TO_Q931      = $02;      //DSS1������Ϣ��        DSP->Q931
const  DSP_SUB_FUNCTION_DSS1_CONTROL_CMD_TO_DSP    = $03;      //DSS1��������          Q931->DSP
const  DSP_SUB_FUNCTION_DSS1_STATE_EVENT_TO_Q931   = $03;      //DSS1״̬�¼�          DSP->Q931
const  DSP_SUB_FUNCTION_DSS1_SIGNAL_DATA_TO_DSP    = $04;      //DSS1��������          Q931->DSP
const  DSP_SUB_FUNCTION_DSS1_SIGNAL_DATA_TO_Q931   = $04;      //DSS1��������          DSP->Q931
const  DSP_SUB_FUNCTION_DSS1_DATA_REQ_TO_Q931      = $05;      //DSS1���������        DSP->Q931
const  DSP_SUB_FUNCTION_DSS1_DEBUG_DATA_TO_Q931    = $06;      //DSS1������Ϣ��        DSP->Q931
//DSP DSS1�ӹ��ܶ��� end

//DSP �̼��ӹ��ܶ���
const  DSP_SUB_FUNCTION_FIRMWARE_READ_FLASH        = $01;      //��FLASH����
const  DSP_SUB_FUNCTION_FIRMWARE_WRITE_FLASH       = $02;      //дFLASH����
const  DSP_SUB_FUNCTION_FIRMWARE_ERASE_FLASH       = $03;      //����FLASH����
const  DSP_SUB_FUNCTION_FIRMWARE_FINISH_FLASH      = $04;      //����FLASH�������
const  DSP_SUB_FUNCTION_FIRMWARE_READ_SDRAM        = $06;      //��SDRAM����
const  DSP_SUB_FUNCTION_REBOOT                     = $07;      //DSP��������
//DSP �̼��ӹ��ܶ���

//******************************************************************************

const  MEDIA_MAIN_FUNCTION_STREAMPLAY    = $01;           //������
//ý�幦��ģ�鹦��ID����***************************************
const  MEDIA_MAIN_FUNCTION_STREAMRECORD  = $02;           //��¼��

//SS7�����ģ�鹦��ID����***************************************
const  SS7_MAIN_FUNCTION_ISUP      = $01;           //�ߺ�����
const  SS7_MAIN_FUNCTION_TUP       = $02;
const  SS7_MAIN_FUNCTION_SCCP      = $03;           //�ߺ�����SCCP
const  SS7_MAIN_FUNCTION_LINK      = $10;           //�ߺ�������·
const  SS7_MAIN_FUNCTION_FLOW      = $11;           //���̱�ʶ����

//PRI�����ģ�鹦��ID����***************************************
const  PRI_MAIN_FUNCTION_Q931      = $01;           //Q.931����


//����ģ�鹦��ID����***************************************

const  CONFIG_MAIN_FUNCTION_INIT        = $01;           //��ʼ��ģ��
const  CONFIG_MAIN_FUNCTION_START       = $02;           //����ģ��
const  CONFIG_MAIN_FUNCTION_STOP        = $03;           //ֹͣģ��
const  CONFIG_MAIN_FUNCTION_RELATE      = $04;           //����ģ��
const  CONFIG_MAIN_FUNCTION_UNRELATE    = $05;           //ֹͣ����ģ��
const  CONFIG_MAIN_FUNCTION_MONCONFIG   = $06;           //��������
const  CONFIG_MAIN_FUNCTION_MONSTART    = $07;           //��������
const  CONFIG_MAIN_FUNCTION_MONSTOP     = $08;           //����ֹͣ
const  CONFIG_MAIN_FUNCTION_HEART       = $09;           //������
const  CONFIG_MAIN_FUNCTION_VALIDITY    = $0A;           //ϵͳ������֤��
const  CONFIG_MAIN_FUNCTION_RELEAT      = $0B;
const  CONFIG_MAIN_FUNCTION_HOTSTANDBY  = $0C;           //��ģ�鷢�͵����ӹ�ϵ
const  CONFIG_MAIN_FUNCTION_HOTINFO     = $0D;           //��ģ�鷢�ʹ�ģ����Ϣ
const  CONFIG_MAIN_FUNCTION_IPINFO      = $0E;           //��ģ�鷢����IP��Ϣ
const  CONFIG_MAIN_FUNCTION_MODSTATE_REPORT    = $0F;
const  CONFIG_MAIN_FUNCTION_ADDNO2IP_NOTIFY    = $10;    //��VOIPģ�鷢����ӵڶ�IP��Ϣ

const  CONFIG_MAIN_FUNCTION_INTERFACE   = $10;           //����ģ�鷢�͹���������

const  CONFIG_MAIN_FUNCTION_USER        = $11;          //�û�ģ�鷢�͹���������
const  CONFIG_MAIN_FUNCTION_CFG         = $12;           //��һ�����ù����͹���������
const  CONFIG_MAIN_FUNCTION_SLAVE_WORK_NOTIFY  = $13;    //��FLOWģ�鷢�ͱ�����������֪ͨ��Ϣ


const CONFIG_SUB_FUNCTION_INTERFACE_REQALL      = $01;    //��������ģ������
const CONFIG_SUB_FUNCTION_INTERFACE_REQSINGAL   = $02;    //����ĳ��ģ������
const CONFIG_SUB_FUNCTION_INTERFACE_REQINIT     = $03;    //����ĳ��ģ���ʼ��������
const CONFIG_SUB_FUNCTION_INTERFACE_SETPARM     = $04;    //����ĳ��ģ�����(����IP,�Ƿ�ʹ�ܵ�)
const CONFIG_SUB_FUNCTION_INTERFACE_SETINIT     = $05;    //����ģ���ʼ����
const CONFIG_SUB_FUNCTION_INTERFACE_START       = $06;    //ģ���ʼ��������
const CONFIG_SUB_FUNCTION_INTERFACE_STOP        = $07;    //ģ��ֹͣ
const CONFIG_SUB_FUNCTION_INTERFACE_REQRELATE   = $08;    //����ģ�������Ϣ
const CONFIG_SUB_FUNCTION_INTERFACE_TRANRELATE  = $09;    //ģ�������Ϣ
const CONFIG_SUB_FUNCTION_INTERFACE_ADD         = $0a;    //����һ��ģ��
const CONFIG_SUB_FUNCTION_INTERFACE_SUB         = $0b;    //ɾ��һ��ģ��
const CONFIG_SUB_FUNCTION_INTERFACE_PASSWORD    = $0c;       //����ϵͳ���ֺ�ϵͳ��½����

const CONFIG_SUB_FUNCTION_INTERFACE_REQRELATE_NEW   = $0d;    //����ģ�������Ϣ(new)
const CONFIG_SUB_FUNCTION_INTERFACE_REQRELATE_ALL   = $0e;    //�������е�ģ�������Ϣ
const CONFIG_SUB_FUNCTION_INTERFACE_HEART       = $10;   //������

//����ģ����ӹ��ܶ���
const CONFIG_SUB_FUNCTION_CFG_MODULE_INFO                 = $01;      //ģ����Ϣ
const CONFIG_SUB_FUNCTION_CFG_SET_HOTSTANDBY              = $02;      //�ı����ӹ�ϵ
const CONFIG_SUB_FUNCTION_CFG_REPLY_HOTSTANDBY            = $03;    //�ı����ӹ�ϵӦ��
const CONFIG_SUB_FUNCTION_CFG_HEART                       = $04;    //���ù�����������
//�û�ģ���ӹ��ܶ���
const CONFIG_SUB_FUNCTION_USER_REQALL      = $01;        //��������ģ������
const CONFIG_SUB_FUNCTION_USER_REQSINGAL   = $02;        //����ĳ��ģ������
const CONFIG_SUB_FUNCTION_USER_REQRELATE   = $03;        //����ĳ��ģ�������Ϣ

const CONFIG_SUB_FUNCTION_USER_SET_HOTSTANDBY   = $04;        //�û���������ģ��Ϊ��

const CONFIG_SUB_FUNCTION_READNODE				 = $01;	// ������ڵ���Ϣ �÷�ͬ����������FACE_MAIN_FUNCTION_READNODE
const CONFIG_SUB_FUNCTION_GETCHANNELSTATE	 = $02;	// �����ȡͨ��״̬
const CONFIG_SUB_FUNCTION_MODDOWNRELATE		 = $03;	// ����mainmod������й���
const CONFIG_SUB_FUNCTION_GETCHASSISINFO	 = $04;	// ����DSP�����λ��Ϣ

//����ģ�鹦��ID����***************************************
const FACE_MAIN_FUNCTION_REQNODE                = $01;    //����ڵ㶨��
const FACE_MAIN_FUNCTION_READNODE               = $02;    //���ڵ�����
const FACE_MAIN_FUNCTION_WRITENODE              = $03;    //д�ڵ�����
const FACE_MAIN_FUNCTION_SAVECONFIG             = $04;    //����ڵ�����
const FACE_MAIN_FUNCTION_LOADCONFIG             = $05;    //ת�ؽڵ�����
const FACE_MAIN_FUNCTION_LICENCE				        = $06;    //װ����֤�ļ�

const FACE_MAIN_FUNCTION_PROXY                  = $08;    //���ý������

const FACE_MAIN_FUNCTION_QUERY_CTBUS            = $0A;    //��ѯDSPͨ��CT-BUS��
const FACE_MAIN_FUNCTION_QUERY_SLOT             = $0B;    //��ѯDSPʱ϶���ӹ�ϵ


const FACE_SUB_FUNCTION_PROXY_ADDMODULE         = $01;   //ͨ����������һ��ģ��
const FACE_SUB_FUNCTION_PROXY_SUBMODULE         = $02;   //ͨ������ɾ��һ��ģ��
const FACE_SUB_FUNCTION_PROXY_GETMODULECONFIG		= $03;	 //ͨ�������ȡһ��ģ�������ļ�����
const FACE_SUB_FUNCTION_PROXY_SETMODULECONFIG		= $04;   //ͨ����������һ��ģ�������ļ�����
const FACE_SUB_FUNCTION_PROXY_RESUMEMODULECONFIG= $05;   //ͨ������ָ�һ��ģ�������ļ�����
const FACE_SUB_FUNCTION_PROXY_STOPALL					  = $06;	 //ͨ������ֹͣ����Ϊ�˸��ǵ�ǰ�������ã�
const FACE_SUB_FUNCTION_PROXY_SAVECFGFILE				= $07;	 //ͨ�������������ļ�
const FACE_SUB_FUNCTION_PROXY_STARTALL				  = $08;	 //ͨ��������������= $06�ķ�������
const FACE_SUB_FUNCTION_PROXY_GET_LOGMODCONFIG  = $09;	 //ͨ�������ȡ��־server����
const FACE_SUB_FUNCTION_PROXY_SET_LOGMODCONFIG  = $0a;	 //ͨ������������־server����
const FACE_SUB_FUNCTION_PROXY_GET_LOGMODINFO    = $0b;	 //ͨ�������ȡ��־server��Ϣ
const FACE_SUB_FUNCTION_PROXY_RESETMODULE       = $0c;   //ͨ����������ģ��
const FACE_MAIN_FUNCTION_HEART                  = $09;   //�����������

//hn add for get link status at 20081212
const FACE_MAIN_FUNCTION_QUERY_LINK_STATUS    = $0a;    //��ѯʱ϶����״̬
const FACE_SUB_FUNCTION_QUERY_UPLINK          = $01;    //��ѯ������ʱ϶���ӹ�ϵ
const FACE_SUB_FUNCTION_QUERY_DOWNLINK        = $02;    //��ѯ������ʱ϶���ӹ�ϵ

//end add
//����ִ��ģ�鹦��ID����*************************************
const  CTX_MAIN_FUNCTION_CTXCMD                = $FA;	   //������������
//����ִ��ģ���ӹ���ID����*************************************
const  CTX_SUB_FUNCTION_CTXREG                 = $01;     //ACS���ͽ�������ע������
const  CTX_SUB_FUNCTION_CTXLINK                = $02;     //ACS���ͽ�������Link����
const  CTX_SUB_FUNCTION_CTXAPPDATA             = $03;     //ACS����ע�ύ����AppData������
const  CTX_SUB_FUNCTION_REPORTSLOT             = $07;     //����ģ���򽻻����ķ���DSP��Ϣ

//����ִ��ģ�鹦��ID����*************************************
const  FLOW_MAIN_FUNCTION_SYNCMD                = $FB;	   //����ͬ������
//����ִ��ģ�鹦��ID����:�����¼�*************************************
const  FLOW_MAIN_FUNCTION_ACSEVT                = $FC;	   //�����¼�
const  FLOW_SUB_FUNCTION_MASTER_STATE           = $01;     //ACS�ϱ�Master״̬�¼�
const  FLOW_SUB_FUNCTION_SLAVE_WORK_STATE       = $02;     //ACS�ϱ�Slave Work״̬�¼�


//����ִ��ģ�鹦��ID����:��������*************************************
const  FLOW_MAIN_FUNCTION_ACSCMD                = $FD;	   //��������
const  FLOW_MAIN_FUNCTION_TIMEREVT              = $FE;	   //��ʱ���¼�
const  MOD_MAIN_FUNCTION_MODHEART               = $FF;	   //��ģ��֮���������

//����ִ��ģ���ӹ���ID����*************************************
const  FLOW_SUB_FUNCTION_INTERCMD               = $01;     //�����ڲ�����
const  FLOW_SUB_FUNCTION_REQDEVICE              = $02;     //ACS������Դ�б�
const  FLOW_SUB_FUNCTION_OPENDEVICE             = $03;     //ACS���豸
const  FLOW_SUB_FUNCTION_CLOSEDEVICE            = $04;     //ACS�ر��豸
const  FLOW_SUB_FUNCTION_RESETDEVICE            = $05;     //ACS��λ�豸
const  FLOW_SUB_FUNCTION_GETDEVSTATE            = $06;     //ACS��ȡ�豸״̬
const  FLOW_SUB_FUNCTION_SETDEVGROUP            = $07;     //ACS������Դ���
const  FLOW_SUB_FUNCTION_SETPARAM               = $08;     //ACS���ò���
const  FLOW_SUB_FUNCTION_GETPARAM               = $09;     //ACS���ò��� ...
const  FLOW_SUB_FUNCTION_MAKECALLOUT            = $0A;     //ACS�������
const  FLOW_SUB_FUNCTION_ALERTCALL              = $0B;     //ACS Alert����
const  FLOW_SUB_FUNCTION_ANSWERCALLIN           = $0C;     //ACSӦ�����
const  FLOW_SUB_FUNCTION_LINKDEV                = $0D;     //ACS�����豸
const  FLOW_SUB_FUNCTION_UNLINKDEV              = $0E;     //ACS����豸����
const  FLOW_SUB_FUNCTION_CLEARCALL              = $0F;     //ACS�������
const  FLOW_SUB_FUNCTION_JOINTOCONF             = $10;     //ACS�������
const  FLOW_SUB_FUNCTION_LEAVEFROMCONF          = $11;     //ACS�뿪����
const  FLOW_SUB_FUNCTION_CLEARCONF              = $12;     //ACSɾ������
const  FLOW_SUB_FUNCTION_PLAYFILE               = $13;     //ACS����
const  FLOW_SUB_FUNCTION_INITPLAYINDEX          = $14;     //ACS��ʼ������
const  FLOW_SUB_FUNCTION_BUILDINDEX             = $15;     //ACS������������
const  FLOW_SUB_FUNCTION_CONTROLPLAY            = $16;     //ACS���Ʒ���
const  FLOW_SUB_FUNCTION_RECORDFILE             = $17;    //ACS¼��
const  FLOW_SUB_FUNCTION_CONTROLRECORD          = $18;     //ACS����¼��
const  FLOW_SUB_FUNCTION_SENDFAX                = $19;     //ACS���ʹ���
const  FLOW_SUB_FUNCTION_STOPSENDFAX            = $1A;     //ACSֹͣ���ʹ���
const  FLOW_SUB_FUNCTION_RECVFAX                = $1B;     //ACS���մ���
const  FLOW_SUB_FUNCTION_STOPRECVFAX            = $1C;     //ACSֹͣ���մ���
const  FLOW_SUB_FUNCTION_CHANGEMONITORFILTER    = $1D;     //ACS�ı��¼�filter
const  FLOW_SUB_FUNCTION_SENDIODATA             = $1E;     //ACS����IO����
const  FLOW_SUB_FUNCTION_SENDSIGMSG             = $1F;     //ACS����������Ϣ
const  FLOW_SUB_FUNCTION_RECORDCSP              = $20;     //ACS�ڴ�¼��
const  FLOW_SUB_FUNCTION_CONTROLRECORDCSP       = $21;     //ACS�����ڴ�¼��
const  ACS_SUB_FUNCTION_DBGON                   = $22;     //����ʹ��
const  ACS_SUB_FUNCTION_DBGOFF                  = $23;     //���Խ�ֹ
const  FLOW_SUB_FUNCTION_PLAY3GPP               = $24;     //����3gpp
const  FLOW_SUB_FUNCTION_CONTROLPLAY3GPP        = $25;     //���Ʋ���3gpp
const  FLOW_SUB_FUNCTION_RECORD3GPP             = $26;     //����3gpp
const  FLOW_SUB_FUNCTION_CONTROLRECORD3GPP      = $27;     //���Ʋ���3gpp
const  FLOW_SUB_FUNCTION_PLAYCSP                = $28;     //ACS����CSP����
const  FLOW_SUB_FUNCTION_SENDPLAYCSP            = $29;     //ACS����CSP��������
const  FLOW_SUB_FUNCTION_CTXREG                 = $2A;     //ACS����Ctx Reg�¼�
const  FLOW_SUB_FUNCTION_CTXLINK                = $2B;     //ACS����CTX Link�¼�
const  FLOW_SUB_FUNCTION_CTXAPPDATA             = $2C;     //ACS����CTX AppData�¼�
const  FLOW_SUB_FUNCTION_LICQUERY               = $2E;     //ACS����License query
const  FLOW_SUB_FUNCTION_LINKQUERY              = $2F;     //ACS����Link query
const  FLOW_SUB_FUNCTION_INIT3GPPINDEX          = $30;     //ACS��ʼ��3gpp����
const  FLOW_SUB_FUNCTION_BUILD3GPPINDEX         = $31;     //ACS����3gpp����
const  FLOW_SUB_FUNCTION_SENDRAWFRAME           = $32;     //ACS����ԭʼFrame����
const  FLOW_SUB_FUNCTION_JOIN3GCONF             = $33;     //ACS���ͼ���3G����
const  FLOW_SUB_FUNCTION_LEAVE3GCONF            = $34;     //ACS�����뿪3G����
const  FLOW_SUB_FUNCTION_CLEAR3GCONF            = $35;     //ACS�������3G����
const  FLOW_SUB_FUNCTION_GET3GCONFLAYOUT        = $36;     //ACS���ͻ�ȡ3G����Layout
const  FLOW_SUB_FUNCTION_SET3GCONFLAYOUT        = $37;     //ACS��������3G����Layout
const  FLOW_SUB_FUNCTION_GET3GCONFVISABLE       = $38;     //ACS���ͻ�ȡ3G����visable
const  FLOW_SUB_FUNCTION_SET3GCONFVISABLE       = $39;     //ACS��������3G����visable
const  FLOW_SUB_FUNCTION_RESTART3GCONF          = $3A;     //ACS��������3G����
const  FLOW_SUB_FUNCTION_SETMASTER              = $3B;     //ACS����Master����
const  ACS_SUB_FUNCTION_TRAPEN                  = $40;     //���
const  FLOW_SUB_FUNCTION_BAKSYSSTART            = $50;     //ACS����BakSysStart�¼�
const  FLOW_SUB_FUNCTION_VOIPMONDATA            = $51;     //ACS����VoIP����
const  FLOW_SUB_FUNCTION_SYNDATA                = $FC;     //��������ģ��֮�������
const  FLOW_SUB_FUNCTION_MASTERCHG              = $FE;     //��������״̬�¼�
const  FLOW_SUB_FUNCTION_RESETCHAN              = $FF;     //���͸�λͨ���¼�


//IP����ģ�鹦��ID����*******************************************

//faxTiffģ��������
const FAXTIFF_MAIN_FUNCTION_CHANGE  = $01;

//faxTiffģ���ӹ���
//���������
const FAXTIFF_SUB_FUNCTION_CHANGE_DECOMPOSE	= $01;  //�ֽ�
const FAXTIFF_SUB_FUNCTION_CHANGE_COMPOSE	  = $02;  //�ϳ�
const FAXTIFF_SUB_FUNCTION_PAGE_REQ		      = $03;  //�ֽ�ҳ����
const FAXTIFF_SUB_FUNCTION_TRANS_CONTROL    = $04;  //ת������
const FAXTIFF_SUB_FUNCTION_TRANS_ADDFILE	  = $05;  //�����ļ�
const FAXTIFF_SUB_FUNCTION_TRANS_ADDHEADER  = $06;  //���Ӵ���ͷ
const FAXTIFF_SUB_FUNCTION_TRANS_INIT		    = $07;  //��ʼ��

//�¼�������
const FAXTIFF_SUB_FUNCTION_DECOMPOSE_RESULT	= $01;  //�ֽ���
const FAXTIFF_SUB_FUNCTION_COMPOSE_RESULT	  = $02;  //�ϳɽ��
const FAXTIFF_SUB_FUNCTION_TRANS_STATE	    = $03;  //ת��״̬
const FAXTIFF_SUB_FUNCTION_LOCALFORMAT	    = $04;  //���ظ�ʽ
//****************************************************************

const MEDIAEX_MAIN_FUNCTION_REPORT_RTPPORT   = $01;
const MEDIAEX_SUB_FUNCTION_REPORT_RTPPORT    = $02;

implementation

end.
