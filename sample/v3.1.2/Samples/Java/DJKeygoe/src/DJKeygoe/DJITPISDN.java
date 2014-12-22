package DJKeygoe;

public class DJITPISDN {
	//Q931ģ��������ִ��ģ��֮��ͨѶ����ͷ�ӹ��ܶ���
	public static final int ITP_SUB_FUNC_FLOW_TO_Q931_GET_CHNL_STATE       = 0x01;     //��ȡͨ��״̬  ��ѯָ����Ԫָ��ͨ���ĵ�ǰ״̬
	public static final int ITP_SUB_FUNC_FLOW_TO_Q931_CALL_OUT             = 0x02;    //����һ������  
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_APPEND_CALLEEID     = 0x03;     //׷�ӱ��к���  ������к�׷�ӱ��к���
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_GET_CALL_INFO       = 0x04;     //��ȡ������Ϣ  ��ȡ������Ϣ���������к��롢���к����
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_GET_CALL_RESULT     = 0x05;     //��ȡ������� 
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_GET_DISCONN_REASON  = 0x06;     //��ȡ�һ�ԭ�� 
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_SET_CHNL_STATE      = 0x07;     //����ͨ��״̬ 
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_SET_PARAM           = 0x08;     //���ò���
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_GET_PARAM           = 0x09;     //��ȡ����
	public static final int  ITP_SUB_FUNC_FLOW_TO_Q931_SET_SIGNAL          = 0x10;     //�����ź�

	public static final int  ITP_SUB_FUNC_Q931_TO_FLOW_CHNL_STATE          = 0x11;     //����ͨ��״̬  ��ͨ��״̬������Ǩ�ƻ���յ�����ִ��ģ����������Q931ģ��������ִ��ģ�鷢�ͱ������Ը�֮����ִ��ģ��ָ��ͨ���ĵ�ǰ״̬
	public static final int  ITP_SUB_FUNC_Q931_TO_FLOW_CALL_INFO           = 0x12;     //����������Ϣ  �����յ�����ִ��ģ����������Q931ģ��������ִ��ģ�鷢�ͱ������������к��롢���к��롢�����ӵ�ַ�������ӵ�ַ�����ǵĳ���
	public static final int  ITP_SUB_FUNC_Q931_TO_FLOW_CALL_RESULT         = 0x13;     //�����������  �����յ�����ִ��ģ����������Q931ģ��������ִ��ģ�鷢�ͱ������Ը�֮����ִ��ģ��ָ��ͨ���ĺ������
	public static final int  ITP_SUB_FUNC_Q931_TO_FLOW_DISCONN_REASON      = 0x14;     //�����һ�ԭ��  �����յ�����ִ��ģ����������Q931ģ��������ִ��ģ�鷢�ͱ������Ը�֮����ִ��ģ��ָ��ͨ���Ĺһ�ԭ��
	public static final int  ITP_SUB_FUNC_Q931_TO_FLOW_SET_PARAM           = 0x15;     //�������ò������  
	public static final int  ITP_SUB_FUNC_Q931_TO_FLOW_GET_PARAM           = 0x16;     //������ȡ������� 
	public static final int  ITP_SUB_FUNC_Q931_TO_FLOW_SET_SIGNAL          = 0x17;     //���������źŽ��

	//Q931ģ����ͬ��ģ��֮��İ�ͷ�ӹ��ܶ���
	public static final int  ITP_SUB_FUNC_Q931_STANDBY_CHNL_STATE          = 0x01;
	public static final int  ITP_SUB_FUNC_Q931_STANDBY_REQ_CHNL_STATE      = 0x02;

	public static final int  ITP_SUB_FUNC_Q931_STANDBY_LINK_STATE          = 0x03;
	public static final int  ITP_SUB_FUNC_Q931_STANDBY_REQ_LINK_STATE      = 0x04;


	//Q931ģ��ͨ��״̬����
	public static final int  ITP_Q931_CH_FREE					    = 1;   //����״̬
	//#define ITP_Q931_CH_WAIT_APP_FREE		        2   //Q931�ȴ�Ӧ�ò�ͬ���ͷ���Դ
	public static final int  ITP_Q931_CH_RESTART                    = 2;
	public static final int  ITP_Q931_CH_UNAVIABLE			        = 3;   //ͨ��������
	public static final int  ITP_Q931_CH_WAIT_CONNECT_ACK		    = 4;   //�ȴ�����֤ʵ
	public static final int  ITP_Q931_CH_CONNECT				    = 5;   //ͨ����ͨ״̬
	public static final int  ITP_Q931_CH_WAIT_RELEASE			    = 6;   //�ѷ��Ͳ����źţ��ȴ��Է������ͷ��ź�
	public static final int  ITP_Q931_CH_WAIT_RELEASE_COMPLETE      = 7;   //�ѷ����ͷ��źţ��ȴ��Է������ͷ�����ź�
	public static final int  ITP_Q931_CALLEE_WAIT_ANSWER		    = 11;  //�����������е���
	public static final int  ITP_Q931_CALLER_WAIT_ANSWER		    = 12;  //ȥ�������Ѻ������ȴ��Է���Ӧ
	public static final int  ITP_Q931_CALLER_RECV_ALERT		        = 21;  //ȥ�������ѽ��յ�������Ϣ
	public static final int  ITP_Q931_CALLER_RECV_SETUP_ACK	        = 22;  //ȥ�������ѽ��յ�����ȷ����Ϣ
	public static final int  ITP_Q931_CALLER_RECV_CALLPROCESS       = 23;  //ȥ�������ѽ��յ����н�����Ϣ
	public static final int  ITP_Q931_CALLER_WAIT_SETUP_ACK	        = 24;  //ȥ�������ȴ�����ȷ��
	public static final int  ITP_Q931_CALLEE_WAIT_INFO              = 0x90; //���������ȴ��������к�����Ϣ
	public static final int  ITP_Q931_CALLEE_SEND_ALERT			    = 0x91; //��������������������Ϣ


	//ͨ����������
	public static final int 	ITP_Q931_CH_SET_FREE			   = 1;    //APP ����ͨ��״̬Ϊ OxO2 ʱ��ͬ���ͷ�ͨ����Դ
	public static final int  ITP_Q931_CH_SET_CONNECT		       = 2;    //����ͨ������
	public static final int  ITP_Q931_CH_SET_DISCONNECT	           = 3;    //���ͨ������
	public static final int  ITP_Q931_CALLEE_SET_ALERTING	       = 4;    //���з�����������Ϣ
	public static final int 	ITP_Q931_CH_SET_RESTART		       = 5;    //����ͨ����������


	//Q931�����������
	public static final int  ITP_Q931_C_NO_RESULT		   = 0;    //��δ���غ������
	public static final int  ITP_Q931_C_USER_IDLE		   = 1;    //���п���
	public static final int  ITP_Q931_C_USER_OFFHOOK	   = 2;    //����ժ������ͨ
	public static final int  ITP_Q931_C_WAIT_CALL_PROC     = 3;    //�ص����ͱ��к��룬�ȴ��Զ�ȷ�ϱ��к�������
	public static final int  ITP_Q931_C_OTHERS             = 10;   //������������п��ܽ��������ѯͨ��״̬
	public static final int  ITP_Q931_C_STATE_UNAVIABLE    = 11;   //״̬���ԣ�δ���к���


	//����һ�ԭ��
	public static final int  ITP_Q931_RSN_UNKNOW_REASON           = 0x00;   //ԭ��δ֪
	public static final int  ITP_Q931_RSN_UNALLOC_NUMBER          = 0x01;   //�պ�
	public static final int  ITP_Q931_RSN_NORMAL_DISCONNECT       = 0x10;   //�����ĺ������
	public static final int  ITP_Q931_RSN_USER_BUSY               = 0x11;   //�û�æ
	public static final int  ITP_Q931_RSN_NO_RESPOND              = 0x12;   //����Ӧ
	public static final int  ITP_Q931_RSN_NO_ANSWER               = 0x13;   //���û�Ӧ��
	public static final int  ITP_Q931_RSN_REFUSR_CALL             = 0x15;   //���оܾ�
	public static final int  ITP_Q931_RSN_NUMBER_ERROR            = 0x1C;   //���벻ȫ
	public static final int  ITP_Q931_RSN_TIMEOUT	              = 0x66;   //��ʱ
	public static final int  ITP_Q931_RSN_DCHANNEL_DOWN           = 0xfd;   //��·�ж�
	public static final int  ITP_Q931_RSN_BCHANNEL_UNAVIABLE      = 0x22;   //ͨ��������
	public static final int  ITP_Q931_RSN_UNAVIABLE_CIRCULT       = 0x2c;   //�޿���ͨ·

	public static final int  ITP_Q931_RSN_UNAVIABLE_CRN           = 0x51;   //��Ч�Ĳο�ֵ
	public static final int  ITP_Q931_RSN_UNCOMPATIBLE            = 0x58;   //�����ݵ��յ�
	public static final int  ITP_Q931_RSN_UNAVIABLE_MSG           = 0x5F;   //��Ч����Ϣ

	public static final int  ITP_Q931_RSN_NEEDMSG_LOST            = 0x60;   //�������Ϣ��Ԫ��ʧ

	public static final int  ITP_Q931_RSN_UNKNOW_MSG              = 0x61;    //��Ϣ���Ͳ�����
	public static final int  ITP_Q931_RSN_UNAVIABLE_STATUE        = 0x65;   //���к�״̬������

	//��������
	//������Ϣ��������

	public static final int  ITP_Q931_CAP_SPEECH          = 0x00;  /* Speech Bearer Capability */
	public static final int  ITP_Q931_CAP_UNREST_DIG      = 0x08;  /* Unrestricted Digital Capability */
	public static final int  ITP_Q931_CAP_REST_DIG        = 0x09;  /* Restricted Digital Capability */
	public static final int  ITP_Q931_CAP_3DOT1K_AUDIO    = 0x10;  /* 3.1KHz Audio Capability */
	public static final int  ITP_Q931_CAP_7K_AUDIO        = 0x11;  /* 7KHz Audio Capability */
	public static final int  ITP_Q931_CAP_VIDEO           = 0x18;  /* Video Capability */


	//������Ϣ��������

	public static final int  ITP_Q931_RATE_64KBPS         = 0x10;  /* B_CHANNEL_UNITS 1X64 */
	public static final int  ITP_Q931_RATE_128KBPS        = 0x11;  /* Non-standard 2X64       */
	public static final int  ITP_Q931_RATE_384KBPS        = 0x13;  /* H0_CHANNEL_UNITS 6X64   */
	public static final int  ITP_Q931_RATE_1536KBPS       = 0x15;  /* H11_CHANNEL_UNITS 24X64 */
	public static final int  ITP_Q931_RATE_1920KBPS       = 0x17;  /* H12_CHANNEL_UNITS 30X64 */
	public static final int  ITP_Q931_RATE__MULTI_RATE    = 0x18;  /* Multirate (64 kbit/s base rate) */

	//���崫�ݷ�ʽ
	public static final int  ITP_Q931_ITM_CIRCUIT         = 0x00;  /* ��·��ʽ */  //Ĭ��(only support)
	public static final int  ITP_Q931_ITM_PACKET          = 0x02;  /* ���鷽ʽ */

	//�����û�һ��Э��
	public static final int  ITP_Q931_UIL1_CCITTV110      = 0x01;  /* user info layer 1 - CCITT V.110/X.3*/
	public static final int  ITP_Q931_UIL1_G711ALAW       = 0x03;  /* user info layer 1 - G.711 A-law */
	public static final int  ITP_Q931_UIL1_G721ADCPM      = 0x04;  /* user info layer 1 - G.721 ADCPM */
	public static final int  ITP_Q931_UIL1_G722G725       = 0x05;  /* user info layer 1 - G.722 and G.725 */
	public static final int  ITP_Q931_UIL1_H223_H245      = 0x06;  /*Recommendations H.223 [92] and H.245 [93] */
	public static final int  ITP_Q931_UIL1_DEFINE_USER    = 0x07;  /*Non-ITU-T standardized rate adaption. This implies the presence of octet 5a and, */
	                                           /*optionally, octets 5b, 5c and 5d. The use of this codepoint indicates that the user rate */
	                                           /*specified in octet 5a is defined by the user. Additionally, octets 5b, 5c and 5d, if present, */
	                                           /*are defined in accordance with the user specified rate adaption. */
	public static final int  ITP_Q931_UIL1_CCITTV120      = 0x08;  /* user info layer 1 - CCITT V.120 */
	public static final int  ITP_Q931_UIL1_CCITTX31       = 0x09;  /* user info layer 1 - CCITT X.31 */

	//�����������
	public static final int  ITP_Q931_CALLNUM_UNKNOWN		        = 0x00;   //δ֪
	public static final int  ITP_Q931_CALLNUM_INTERNATIONAL	        = 0x01;   //���ʺ���
	public static final int  ITP_Q931_CALLNUM_DOMESTIC		        = 0x02;   //���ں���
	public static final int  ITP_Q931_CALLNUM_NETWORK_SPECIFIC      = 0x03;   //�����ض�����
	public static final int  ITP_Q931_CALLNUM_USER		 	        = 0x04;   //�û�����
	public static final int  ITP_Q931_CALLNUM_RESERVE		        = 0x07;   //��չ����


	//��������������
	public static final int  ITP_Q931_NUMPLAN_UNKNOWN                = 0x00;   //δ֪
	public static final int  ITP_Q931_NUMPLAN_ISDN                   = 0x01;   /* ISDN numb. plan E.164 */
	public static final int  ITP_Q931_NUMPLAN_TELEPHONY              = 0x02;   /* Telephony numb. plan E.163 */
	public static final int  ITP_Q931_NUMPLAN_PRIVATE                = 0x09;   /* Private numbering plan */
}

class ITP_Q931_CALL_PARAM
{
    public byte	 m_u8Cap;                //��Ϣ��������
    public byte	 m_u8ITM;                //���ݷ�ʽ
    public byte	 m_u8Rate;               //��Ϣ��������
    public byte	 m_u8UIL1;               //�û�һ��Э��
    public byte	 m_u8CallerType;         //���к�������
    public byte	 m_u8CallerPlan;         //���к����������
    public byte	 m_u8CallerSubType;      //�����ӵ�ַ��������
    public byte	 m_u8CallerSubPlan;      //�����ӵ�ַ�����������
    public byte	 m_u8CalleeType;         //���к�������
    public byte	 m_u8CalleePlan;         //���к����������
    public byte	 m_u8CalleeSubType;      //�����ӵ�ַ��������
    public byte	 m_u8CalleeSubPlan;      //�����ӵ�ַ�����������
    
    public byte	 m_u8LowLevelFlag;       //�Ͳ�����Ա�־: 0:��ʾû�д˵�Ԫ;1:��ʾ�д˵�Ԫ
    public byte	 m_u8LowLevelLen;        //�Ͳ��������Ϣ��Ԫ���ȣ�Ŀǰֻ֧��Ĭ��Ϊ5bytes�ĳ���
    public byte	 m_u8LowLevelData[] = new byte[5];    //�Ͳ��������Ϣ��Ԫ����
    public byte	 reserved[]		 = new byte[29];           //�����ֶ�
}

class ITP_Q931_ORINUM_PARAM
{
	public byte	 m_u8NumberType;         //��������
	public byte	 m_u8NumberPlan;         //�����������
	public byte	 reserved[] = new byte[2];            //�����ֶ�
	public byte	 m_szChangeNumber[] = new byte[32];   //ԭʼ����
}


/*��Ϣ����*/
class ITP_Q931_MSG_TYPE
{
	public static final int  ITP_Q931_Resume       = 0x26;	 //�ָ�
	public static final int  ITP_Q931_Suspend      = 0x25;	 //��ͣ
	public static final int  ITP_Q931_Information  = 0x7b;    //��Ϣ 
	public static final int  ITP_Q931_Notify       = 0x6e;	 //֪ͨ
	public static final int  ITP_Q931_StatusEnquiry= 0x75;    //״̬ѯ��
}

//������Ϣ�ṹ
class ITP_Q931_CALL_INFO_STRUCT
{
	public byte	 m_u8CallerLen;                      //���к��볤��
	public byte	 m_u8CalleeLen;                      //���к��볤��
	public byte	 m_u8CallerSubAddrLen;               //���к����ӵ�ַ����
	public byte	 m_u8CalleeSubAddrLen;               //���к����ӵ�ַ����
	public byte	 m_s8CallerId[]			= new byte[32];                   //���к��뻺����
	public byte	 m_s8CalleeId[]			= new byte[32];                   //���к��뻺����
	public byte	 m_s8CallerSubAddr[]	= new byte[32];              //���к����ӵ�ַ������ 
	public byte	 m_s8CalleeSubAddr[]	= new byte[32];              //���к����ӵ�ַ������
}

//ͨ����Ϣ�ṹ     
class ITP_Q931_CHNL_INFO_STRUCT
{
	public byte  m_u8UnitId;                        //DSP ��ԪID
	public byte  m_u8Reserved;                      //����
	public short m_u16Chnl;                         //DSP��Ԫ�ڵ�ͨ����
}

//����һ������
class ITP_Q931_CMD_TO_Q931_CALLOUT
{
	public ITP_Q931_CHNL_INFO_STRUCT m_ITP_q931ChnlInfo = new ITP_Q931_CHNL_INFO_STRUCT();     //ͨ����Ϣ
	public ITP_Q931_CALL_INFO_STRUCT m_ITP_q931CallInfo = new ITP_Q931_CALL_INFO_STRUCT();     //������Ϣ
	
	public byte                 m_u8CallerNumType;  //���к������� 
	public byte                 m_u8CalleeNumType;  //���к�������
	public short                m_u16OverlapFlag;   //�ص����ͱ��к����־
}

//׷�ӱ��к���   
class ITP_Q931_CMD_TO_Q931_APPEND_CALLEEID
{
	public ITP_Q931_CHNL_INFO_STRUCT m_ITP_q931ChnlInfo = new ITP_Q931_CHNL_INFO_STRUCT();     //ͨ����Ϣ

	public byte                 m_u8Length;         //׷�ӱ��к��볤��
	public byte                 m_u8SendEnd;        //������ȫ��־
	public byte                 m_s8Reserved[] = new byte[2];    //����
	public byte                 m_s8CalleeBuf[]= new byte[32];  //���к��뻺����
}

//����ͨ��״̬
class ITP_Q931_CMD_TO_Q931_CHNL_STATE
{   
	public ITP_Q931_CHNL_INFO_STRUCT m_ITP_q931ChnlInfo = new ITP_Q931_CHNL_INFO_STRUCT();     //ͨ����Ϣ
	
	public byte                 m_u8State;                  //ͨ��״̬
    public byte                 m_s8Reserved[] = new byte[3];            //����
}

//Q931ģ��������ִ��ģ�鷴��ͨ��״̬
class ITP_Q931_EVENT_TO_FLOW_CHNL_STATE
{
	public byte                 m_u8State;          //ͨ��״̬
	public byte                 m_s8Reserved[] = new byte[3];    //����
}

//Q931ģ��������ִ��ģ�鷴���������
class ITP_Q931_EVENT_TO_FLOW_CALL_RESULT
{
	public byte                 m_u8CallResult;     //�������
	public byte                 m_s8Reserved[] = new byte[3];    //����
}

//Q931ģ��������ִ��ģ�鷴���һ�ԭ��
class ITP_Q931_EVENT_TO_FLOW_DISCONN_REASON
{
	public byte                 m_u8DisconnReason;  //�һ�ԭ��
	public byte                 m_s8Reserved[] = new byte[3];    //����
}

class ITP_Q931_PARAM
{
    public ITP_Q931_CHNL_INFO_STRUCT m_ITP_q931ChnlInfo = new ITP_Q931_CHNL_INFO_STRUCT(); //ͨ����Ϣ
	
    public byte                 m_u8ErrorCode;       //�������

    public byte                 m_u8ParamType;       //��������
    public byte                 m_u8ParamLen;        //��������
    public byte                 m_s8ParamData[] = new byte[100];  //��������
}

class ITP_Q931_SIGNAL
{
    public ITP_Q931_CHNL_INFO_STRUCT m_ITP_q931ChnlInfo = new ITP_Q931_CHNL_INFO_STRUCT(); //ͨ����Ϣ

    public byte                 m_u8ErrorCode;       //�������
    public byte                 m_u8SignalType;      //��������
}

class ITP_Q931_STANDBY_LINK_STATE
{
	public byte                 m_u8LinkID;         //��·ID
	public byte                 m_u8State;          //��·״̬
	public byte                 m_s8Reserved[] = new byte[2];    //����
}


class ITP_Q931_STANDBY_CHNL_STATE
{
	public byte                 m_u8State;          //ͨ��״̬
	public short                m_sCRN;		 //call reference  ���вο�
	public byte                 m_bIncall;
	public byte                 m_s8Reserved[] = new byte[4];    //����
}

//UUI
class ITP_Q931_UUI_PARAM
{
	public byte	   m_u8UUIFlag;                       //UUI Set Flag
	public byte	   m_u8MsgType;                       //MSG Type
	public byte	   m_u8Len;                           //UUI's Length
	public byte	   m_u8UUIData[] = new byte[131];                  //UUI data buffer
}
