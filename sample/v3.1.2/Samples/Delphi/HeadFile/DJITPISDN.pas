unit DJITPISDN;

interface

//Q931ģ��������ִ��ģ��֮��ͨѶ����ͷ�ӹ��ܶ���
const ITP_SUB_FUNC_FLOW_TO_Q931_GET_CHNL_STATE       = $01;     //��ȡͨ��״̬  ��ѯָ����Ԫָ��ͨ���ĵ�ǰ״̬
const ITP_SUB_FUNC_FLOW_TO_Q931_CALL_OUT             = $02;     //����һ������
const ITP_SUB_FUNC_FLOW_TO_Q931_APPEND_CALLEEID      = $03;     //׷�ӱ��к���  ������к�׷�ӱ��к���
const ITP_SUB_FUNC_FLOW_TO_Q931_GET_CALL_INFO        = $04;     //��ȡ������Ϣ  ��ȡ������Ϣ���������к��롢���к����
const ITP_SUB_FUNC_FLOW_TO_Q931_GET_CALL_RESULT      = $05;     //��ȡ�������
const ITP_SUB_FUNC_FLOW_TO_Q931_GET_DISCONN_REASON   = $06;     //��ȡ�һ�ԭ��
const ITP_SUB_FUNC_FLOW_TO_Q931_SET_CHNL_STATE       = $07;     //����ͨ��״̬
const ITP_SUB_FUNC_FLOW_TO_Q931_SET_PARAM            = $08;     //���ò���
const ITP_SUB_FUNC_FLOW_TO_Q931_GET_PARAM            = $09;     //��ȡ����
const ITP_SUB_FUNC_FLOW_TO_Q931_SET_SIGNAL           = $10;     //�����ź�

const ITP_SUB_FUNC_Q931_TO_FLOW_CHNL_STATE           = $11;     //����ͨ��״̬  ��ͨ��״̬������Ǩ�ƻ���յ�����ִ��ģ����������Q931ģ��������ִ��ģ�鷢�ͱ������Ը�֮����ִ��ģ��ָ��ͨ���ĵ�ǰ״̬
const ITP_SUB_FUNC_Q931_TO_FLOW_CALL_INFO            = $12;     //����������Ϣ  �����յ�����ִ��ģ����������Q931ģ��������ִ��ģ�鷢�ͱ������������к��롢���к��롢�����ӵ�ַ�������ӵ�ַ�����ǵĳ���
const ITP_SUB_FUNC_Q931_TO_FLOW_CALL_RESULT          = $13;     //�����������  �����յ�����ִ��ģ����������Q931ģ��������ִ��ģ�鷢�ͱ������Ը�֮����ִ��ģ��ָ��ͨ���ĺ������
const ITP_SUB_FUNC_Q931_TO_FLOW_DISCONN_REASON       = $14;     //�����һ�ԭ��  �����յ�����ִ��ģ����������Q931ģ��������ִ��ģ�鷢�ͱ������Ը�֮����ִ��ģ��ָ��ͨ���Ĺһ�ԭ��
const ITP_SUB_FUNC_Q931_TO_FLOW_SET_PARAM            = $15;     //�������ò������
const ITP_SUB_FUNC_Q931_TO_FLOW_GET_PARAM            = $16;     //������ȡ�������
const ITP_SUB_FUNC_Q931_TO_FLOW_SET_SIGNAL           = $17;     //���������źŽ��

//Q931ģ����ͬ��ģ��֮��İ�ͷ�ӹ��ܶ���
const ITP_SUB_FUNC_Q931_STANDBY_CHNL_STATE           = $01;
const ITP_SUB_FUNC_Q931_STANDBY_REQ_CHNL_STATE       = $02;

const ITP_SUB_FUNC_Q931_STANDBY_LINK_STATE           = $03;
const ITP_SUB_FUNC_Q931_STANDBY_REQ_LINK_STATE       = $04;


//Q931ģ��ͨ��״̬����
const ITP_Q931_CH_FREE					        = 1;   //����״̬
//#define ITP_Q931_CH_WAIT_APP_FREE		  = 2;   //Q931�ȴ�Ӧ�ò�ͬ���ͷ���Դ
const ITP_Q931_CH_RESTART               = 2;
const ITP_Q931_CH_UNAVIABLE			        = 3;   //ͨ��������
const ITP_Q931_CH_WAIT_CONNECT_ACK		  = 4;   //�ȴ�����֤ʵ
const ITP_Q931_CH_CONNECT				        = 5;   //ͨ����ͨ״̬
const ITP_Q931_CH_WAIT_RELEASE			    = 6;   //�ѷ��Ͳ����źţ��ȴ��Է������ͷ��ź�
const ITP_Q931_CH_WAIT_RELEASE_COMPLETE = 7;   //�ѷ����ͷ��źţ��ȴ��Է������ͷ�����ź�
const ITP_Q931_CALLEE_WAIT_ANSWER		    = 11;  //�����������е���
const ITP_Q931_CALLER_WAIT_ANSWER		    = 12;  //ȥ�������Ѻ������ȴ��Է���Ӧ
const ITP_Q931_CALLER_RECV_ALERT		    = 21;  //ȥ�������ѽ��յ�������Ϣ
const ITP_Q931_CALLER_RECV_SETUP_ACK	  = 22;  //ȥ�������ѽ��յ�����ȷ����Ϣ
const ITP_Q931_CALLER_RECV_CALLPROCESS  = 23;  //ȥ�������ѽ��յ����н�����Ϣ
const ITP_Q931_CALLER_WAIT_SETUP_ACK	  = 24;  //ȥ�������ȴ�����ȷ��
const ITP_Q931_CALLEE_WAIT_INFO         = $90; //���������ȴ��������к�����Ϣ
const ITP_Q931_CALLEE_SEND_ALERT			  = $91; //��������������������Ϣ


//ͨ����������
const	ITP_Q931_CH_SET_FREE			       = 1;    //APP ����ͨ��״̬Ϊ OxO2 ʱ��ͬ���ͷ�ͨ����Դ
const ITP_Q931_CH_SET_CONNECT		       = 2;    //����ͨ������
const ITP_Q931_CH_SET_DISCONNECT	     = 3;    //���ͨ������
const ITP_Q931_CALLEE_SET_ALERTING	   = 4;    //���з�����������Ϣ
const	ITP_Q931_CH_SET_RESTART		       = 5;    //����ͨ����������


//Q931�����������
const ITP_Q931_C_NO_RESULT		       = 0;    //��δ���غ������
const ITP_Q931_C_USER_IDLE		       = 1;    //���п���
const ITP_Q931_C_USER_OFFHOOK	       = 2;    //����ժ������ͨ
const ITP_Q931_C_WAIT_CALL_PROC      = 3;    //�ص����ͱ��к��룬�ȴ��Զ�ȷ�ϱ��к�������
const ITP_Q931_C_OTHERS              = 10;   //������������п��ܽ��������ѯͨ��״̬
const ITP_Q931_C_STATE_UNAVIABLE     = 11;   //״̬���ԣ�δ���к���


//����һ�ԭ��
const ITP_Q931_RSN_UNKNOW_REASON           = $00;   //ԭ��δ֪
const ITP_Q931_RSN_UNALLOC_NUMBER          = $01;   //�պ�
const ITP_Q931_RSN_NORMAL_DISCONNECT       = $10;   //�����ĺ������
const ITP_Q931_RSN_USER_BUSY               = $11;   //�û�æ
const ITP_Q931_RSN_NO_RESPOND              = $12;   //����Ӧ
const ITP_Q931_RSN_NO_ANSWER               = $13;   //���û�Ӧ��
const ITP_Q931_RSN_REFUSR_CALL             = $15;   //���оܾ�
const ITP_Q931_RSN_NUMBER_ERROR            = $1C;   //���벻ȫ
const ITP_Q931_RSN_TIMEOUT	               = $66;   //��ʱ
const ITP_Q931_RSN_DCHANNEL_DOWN           = $fd;   //��·�ж�
const ITP_Q931_RSN_BCHANNEL_UNAVIABLE      = $22;   //ͨ��������
const ITP_Q931_RSN_UNAVIABLE_CIRCULT       = $2c;   //�޿���ͨ·

const ITP_Q931_RSN_UNAVIABLE_CRN           = $51;   //��Ч�Ĳο�ֵ
const ITP_Q931_RSN_UNCOMPATIBLE            = $58;   //�����ݵ��յ�
const ITP_Q931_RSN_UNAVIABLE_MSG           = $5F;   //��Ч����Ϣ


const ITP_Q931_RSN_NEEDMSG_LOST            = $60;   //�������Ϣ��Ԫ��ʧ

const ITP_Q931_RSN_UNKNOW_MSG              = $61;    //��Ϣ���Ͳ�����
const ITP_Q931_RSN_UNAVIABLE_STATUE        = $65;   //���к�״̬������

//��������
//������Ϣ��������

const ITP_Q931_CAP_SPEECH          = $00;  //* Speech Bearer Capability */
const ITP_Q931_CAP_UNREST_DIG      = $08;  //* Unrestricted Digital Capability */
const ITP_Q931_CAP_REST_DIG        = $09;  //* Restricted Digital Capability */
const ITP_Q931_CAP_3DOT1K_AUDIO    = $10;  //* 3.1KHz Audio Capability */
const ITP_Q931_CAP_7K_AUDIO        = $11;  //* 7KHz Audio Capability */
const ITP_Q931_CAP_VIDEO           = $18;  //* Video Capability */


//������Ϣ��������

const ITP_Q931_RATE_64KBPS         = $10;  //* B_CHANNEL_UNITS 1X64 */
const ITP_Q931_RATE_128KBPS        = $11;  //* Non-standard 2X64       */
const ITP_Q931_RATE_384KBPS        = $13;  //* H0_CHANNEL_UNITS 6X64   */
const ITP_Q931_RATE_1536KBPS       = $15;  //* H11_CHANNEL_UNITS 24X64 */
const ITP_Q931_RATE_1920KBPS       = $17;  //* H12_CHANNEL_UNITS 30X64 */
const ITP_Q931_RATE__MULTI_RATE    = $18;  //* Multirate (64 kbit/s base rate) */

//���崫�ݷ�ʽ
const ITP_Q931_ITM_CIRCUIT         = $00;  //* ��·��ʽ */  //Ĭ��(only support)
const ITP_Q931_ITM_PACKET          = $02;  //* ���鷽ʽ */

//�����û�һ��Э��
const ITP_Q931_UIL1_CCITTV110      = $01;  //* user info layer 1 - CCITT V.110/X.3*/
const ITP_Q931_UIL1_G711ALAW       = $03;  //* user info layer 1 - G.711 A-law */
const ITP_Q931_UIL1_G721ADCPM      = $04;  //* user info layer 1 - G.721 ADCPM */
const ITP_Q931_UIL1_G722G725       = $05;  //* user info layer 1 - G.722 and G.725 */
const ITP_Q931_UIL1_H223_H245      = $06;  //*Recommendations H.223 [92] and H.245 [93] */
const ITP_Q931_UIL1_DEFINE_USER    = $07;  //*Non-ITU-T standardized rate adaption. This implies the presence of octet 5a and, */
                                           //*optionally, octets 5b, 5c and 5d. The use of this codepoint indicates that the user rate */
                                           //*specified in octet 5a is defined by the user. Additionally, octets 5b, 5c and 5d, if present, */
                                           //*are defined in accordance with the user specified rate adaption. */
const ITP_Q931_UIL1_CCITTV120      = $08;  //* user info layer 1 - CCITT V.120 */
const ITP_Q931_UIL1_CCITTX31       = $09;  //* user info layer 1 - CCITT X.31 */


//�����������
const ITP_Q931_CALLNUM_UNKNOWN		        = $00;   //δ֪
const ITP_Q931_CALLNUM_INTERNATIONAL	    = $01;   //���ʺ���
const ITP_Q931_CALLNUM_DOMESTIC		        = $02;   //���ں���
const ITP_Q931_CALLNUM_NETWORK_SPECIFIC   = $03;   //�����ض�����
const ITP_Q931_CALLNUM_USER		 	          = $04;   //�û�����
const ITP_Q931_CALLNUM_RESERVE		        = $07;   //��չ����


//��������������
const ITP_Q931_NUMPLAN_UNKNOWN                = $00;   //δ֪
const ITP_Q931_NUMPLAN_ISDN                   = $01;   //* ISDN numb. plan E.164 */
const ITP_Q931_NUMPLAN_TELEPHONY              = $02;   //* Telephony numb. plan E.163 */
const ITP_Q931_NUMPLAN_PRIVATE                = $09;   //* Private numbering plan */

//���ݽṹ����

Type
  ITP_Q931_CALL_PARAM = record
  m_u8Cap           : Byte;        //��Ϣ��������
  m_u8ITM           : Byte;        //���ݷ�ʽ
  m_u8Rate          : Byte;        //��Ϣ��������
  m_u8UIL1          : Byte;        //�û�һ��Э��
  m_u8CallerType    : Byte;        //���к�������
  m_u8CallerPlan    : Byte;        //���к����������
  m_u8CallerSubType : Byte;        //�����ӵ�ַ��������
  m_u8CallerSubPlan : Byte;        //�����ӵ�ַ�����������
  m_u8CalleeType    : Byte;        //���к�������
  m_u8CalleePlan    : Byte;        //���к����������
  m_u8CalleeSubType : Byte;        //�����ӵ�ַ��������
  m_u8CalleeSubPlan : Byte;        //�����ӵ�ַ�����������
  m_u8LowLevelFlag  : Byte;        //�Ͳ�����Ա�־: 0:��ʾû�д˵�Ԫ;1:��ʾ�д˵�Ԫ
	m_u8LowLevelLen   : Byte;        //�Ͳ��������Ϣ��Ԫ���ȣ�Ŀǰֻ֧��Ĭ��Ϊ5bytes�ĳ���
	m_u8LowLevelData  : Array[0..4] of Byte;    //�Ͳ��������Ϣ��Ԫ����
  reserved          : Array[0..28] of Byte;   //�����ֶ�
end;

Type
  ITP_Q931_ORINUM_PARAM = record
  m_u8NumberType : Byte;         //��������
  m_u8NumberPlan : Byte;         //�����������
  reserved         : Array[0..1] of Byte;        //�����ֶ�
	m_szChangeNumber : Array[0..31] of ShortInt;   //ԭʼ����
end;


//*��Ϣ����*/
Type ITP_Q931_MSG_TYPE = 
(
	ITP_Q931_Resume          = $26,	 //�ָ�
	ITP_Q931_Suspend         = $25,	 //��ͣ

	ITP_Q931_Information     = $7b,   //��Ϣ
	ITP_Q931_Notify          = $6e,	 //֪ͨ
	ITP_Q931_StatusEnquiry   = $75    //״̬ѯ��
);

//������Ϣ�ṹ
Type
  ITP_Q931_CALL_INFO_STRUCT = record
	m_u8CallerLen : Byte;                      //���к��볤��
  m_u8CalleeLen : Byte;                      //���к��볤��
  m_u8CallerSubAddrLen : Byte;               //���к����ӵ�ַ����
  m_u8CalleeSubAddrLen : Byte;               //���к����ӵ�ַ����
  m_s8CallerId : Array[0..31] of ShortInt;                   //���к��뻺����
  m_s8CalleeId : Array[0..31] of ShortInt;                   //���к��뻺����
  m_s8CallerSubAddr : Array[0..31] of ShortInt;              //���к����ӵ�ַ������
  m_s8CalleeSubAddr : Array[0..31] of ShortInt;              //���к����ӵ�ַ������
end;

//ͨ����Ϣ�ṹ     
Type
  ITP_Q931_CHNL_INFO_STRUCT = record
	m_u8UnitId   : Byte;                      //DSP ��ԪID
  m_u8Reserved : Byte;                      //����
  m_u16Chnl    : Word;                      //DSP��Ԫ�ڵ�ͨ����
end;

//����һ������
Type
  ITP_Q931_CMD_TO_Q931_CALLOUT = record
	m_ITP_q931ChnlInfo : ITP_Q931_CHNL_INFO_STRUCT;     //ͨ����Ϣ
  m_ITP_q931CallInfo : ITP_Q931_CALL_INFO_STRUCT;     //������Ϣ
	
	m_u8CallerNumType : Byte;  //���к�������
  m_u8CalleeNumType : Byte;  //���к�������
  m_u16OverlapFlag : Word;   //�ص����ͱ��к����־
end;

//׷�ӱ��к���   
Type
  ITP_Q931_CMD_TO_Q931_APPEND_CALLEEID = record
	m_ITP_q931ChnlInfo : ITP_Q931_CHNL_INFO_STRUCT;     //ͨ����Ϣ

	m_u8Length  : Byte;         //׷�ӱ��к��볤��
  m_u8SendEnd : Byte;         //������ȫ��־

  m_s8Reserved  : Array[0..1] of ShortInt;    //����
  m_s8CalleeBuf : Array[0..31] of ShortInt;   //���к��뻺����
end;

//����ͨ��״̬
Type
  ITP_Q931_CMD_TO_Q931_CHNL_STATE  =record
	m_ITP_q931ChnlInfo : ITP_Q931_CHNL_INFO_STRUCT;     //ͨ����Ϣ

  m_u8State    : Byte;                                //ͨ��״̬
  m_s8Reserved : Array[0..2] of ShortInt;             //����
end;

//Q931ģ��������ִ��ģ�鷴��ͨ��״̬
Type
  ITP_Q931_EVENT_TO_FLOW_CHNL_STATE = record
	m_u8State    : Byte;          //ͨ��״̬
  m_s8Reserved : Array[0..2] of ShortInt;    //����
end;

//Q931ģ��������ִ��ģ�鷴���������
Type
  ITP_Q931_EVENT_TO_FLOW_CALL_RESULT = record
	m_u8CallResult : Byte;     //�������
  m_s8Reserved   : Array[0..2] of ShortInt;    //����
end;

//Q931ģ��������ִ��ģ�鷴���һ�ԭ��
Type
  ITP_Q931_EVENT_TO_FLOW_DISCONN_REASON = record
	m_u8DisconnReason : byte;  //�һ�ԭ��
  m_s8Reserved : Array[0..2] of ShortInt;    //����
end;

Type
  ITP_Q931_PARAM = record
  m_ITP_q931ChnlInfo : ITP_Q931_CHNL_INFO_STRUCT; //ͨ����Ϣ
	
	m_u8ErrorCode : Byte;       //�������
	m_u8ParamType : Byte;       //��������
  m_u8ParamLen  : Byte;       //��������

 m_s8ParamData  : Array[0..99] of ShortInt;  //��������
end;

Type
  ITP_Q931_SIGNAL = record
  m_ITP_q931ChnlInfo : ITP_Q931_CHNL_INFO_STRUCT; //ͨ����Ϣ

  m_u8ErrorCode : Byte;       //�������
  m_u8SignalType : Byte;      //��������
end;

Type
  ITP_Q931_STANDBY_LINK_STATE = record
	m_u8LinkID   : Byte;          //��·ID
	m_u8State    : Byte;          //��·״̬
  m_s8Reserved : Array[0..1] of ShortInt;    //����
end;


Type
  ITP_Q931_STANDBY_CHNL_STATE = record
	m_u8State    : Byte;          //ͨ��״̬
	m_sCRN       : SmallInt;		  //call reference  ���вο�
	m_bIncall    : Byte;
  m_s8Reserved : Array[0..3] of ShortInt;    //����
end;

//UUI
Type
  ITP_Q931_UUI_PARAM = record
	m_u8UUIFlag : Byte;                       //UUI Set Flag
	m_u8MsgType : Byte;                       //MSG Type
	m_u8Len     : Byte;                       //UUI's Length
  m_u8UUIData : Array[0..130] of Byte;      //UUI data buffer
end;

implementation

end.
