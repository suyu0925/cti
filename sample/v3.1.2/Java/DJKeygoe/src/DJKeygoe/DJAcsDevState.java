package DJKeygoe;

public class DJAcsDevState {

}


class DEVICE_CALL_STATE{
	/////////////// ͨ�ú���״̬���� //////////////////////////////////////////////////////////////////
	public static final int DEVICE_COMMON_STATE_START   = 0x0000; // ͨ��״̬��ʼʶ���: TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR
	public static final int DCS_FREE                    = 0x0001; // ����״̬(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
	public static final int DCS_LOCAL_BLOCK             = 0x0002; // ��������(TUP,ISUP)
	public static final int DCS_REMOTE_BLOCK            = 0x0003; // Զ������(TUP,ISUP)
	public static final int DCS_BLOCK                   = 0x0004; // ���غ�Զ������(ISUP)
	public static final int DCS_UNAVAILABLE             = 0x0005; // ������(TUP,ISUP,PRI)
	
	public static final int DCS_CALLOUT                 = 0x0006; // ��ʼ����(TUP,ISUP,PRI,VOIP,ANA_TRK)
	public static final int DCS_CALLIN                  = 0x0007; // ���н���(TUP,ISUP,PRI,VOIP,ANA_TRK)
	public static final int DCS_ALERTING                = 0x0008; // ��ַ������û������(TUP,ISUP)
	
	public static final int DCS_CONNECT                 = 0x0009; // ��ͨ(���������з�ʽ)(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
	
	public static final int DCS_DISCONNECT              = 0x000A; // �յ�����(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
	public static final int DCS_WAIT_FREE               = 0x000B; // �Բ��ߵ���Ӧ(TUP,ISUP,PRI,VOIP)
	
	/////////////// ģ��/�ӿ���غ���״̬���� /////////////////////////////////////////////////////////
	public static final int DEVICE_ESPECIAL_STATE_START = 0x0100;
	// ISUPģ��/�ӿ�
	public static final int DES_ISUP_STATE_START        = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_ISUP << 8); // ISUP����״̬ //
	public static final int DES_ISUP_LOCAL_SUSPEND      = (DES_ISUP_STATE_START | 0x01); // ������ͣ
	public static final int DES_ISUP_REMOTE_SUSPEND     = (DES_ISUP_STATE_START | 0x02); // Զ����ͣ
	public static final int DES_ISUP_LOCAL_RESUME       = (DES_ISUP_STATE_START | 0x03); // ���ؼ���
	public static final int DES_ISUP_REMOTE_RESUME      = (DES_ISUP_STATE_START | 0x04); // Զ�˼���
	public static final int DES_ISUP_RECV_INR           = (DES_ISUP_STATE_START | 0x05); // �յ�INR������Ϣ
	public static final int DES_ISUP_RECV_INF           = (DES_ISUP_STATE_START | 0x06); // �յ�INF������Ϣ
	public static final int DES_ISUP_RECV_CQR           = (DES_ISUP_STATE_START | 0x07); // �յ�CQR������Ϣ
	public static final int DES_ISUP_RECV_USR           = (DES_ISUP_STATE_START | 0x08); // �յ�USR������Ϣ
	public static final int DES_ISUP_RECV_CPG           = (DES_ISUP_STATE_START | 0x09); // �յ�CPG������Ϣ
	
	// TUPģ��/�ӿ�
	public static final int DES_TUP_STATE_START         = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_TUP << 8);  // TUP ����״̬ //
	public static final int DES_TUP_RECV_CCL            = (DES_TUP_STATE_START | 0x01);  // �յ�CCL������Ϣ
	public static final int DES_TUP_RECV_RAN            = (DES_TUP_STATE_START | 0x02);  // �յ�RAN������Ϣ
	public static final int DES_TUP_RECV_GSM            = (DES_TUP_STATE_START | 0x03);  // �յ�GSM������Ϣ
	
	public static final int DES_SS7_LINK_STATE_START    = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_SS7_LINK << 8);    // 
	public static final int DES_SS7_LST_CONNECTING      = (DES_SS7_LINK_STATE_START | 0x01);
	public static final int DES_SS7_LST_ACTIVE          = (DES_SS7_LINK_STATE_START | 0x02);
	public static final int DES_SS7_LST_FAILED          = (DES_SS7_LINK_STATE_START | 0x03);
	public static final int DES_SS7_LST_WAITCON         = (DES_SS7_LINK_STATE_START | 0x04);
	public static final int DES_SS7_LST_SUSPEND         = (DES_SS7_LINK_STATE_START | 0x05);
	
	public static final int DES_DSS1_STATE_START        = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_DSS1 << 8);      // DSS1 ����״̬ //
	public static final int DES_DSS1_RESTRAT            = (DES_DSS1_STATE_START | 0x01);  // Ӧ�ÿ�ʼ��������״̬
	public static final int DES_DSS1_WAIT_CONNECT_ACK   = (DES_DSS1_STATE_START | 0x02);  // �ȴ�����֤ʵ
	public static final int DES_DSS1_CALLER_RECV_ALERT  = (DES_DSS1_STATE_START | 0x03);  //ȥ�������ѽ��յ�������Ϣ
	public static final int DES_DSS1_CALLER_RECV_CALLPROCESS = (DES_DSS1_STATE_START | 0x04);  //ȥ�������ѽ��յ����н����Ϣ
	public static final int DES_DSS1_CALLER_RECV_SETUP_ACK	 = (DES_DSS1_STATE_START | 0x05);  //ȥ�������ѽ��յ�����ȷ����Ϣ
	public static final int DES_DSS1_CALLER_WAIT_SETUP_ACK	 = (DES_DSS1_STATE_START | 0x06);  //ȥ�������ȴ���ȷ��
	
	// VoIP H.323Э������״̬
	public static final int DES_H323_STATE_START        = 0x00010100;
	public static final int DES_H323_PROCEEDING         = (DES_H323_STATE_START + 0x01); // proceeding
	public static final int DES_H323_TRANSFERING        = (DES_H323_STATE_START + 0x02); // transfering
	public static final int DES_H323_ACF                = (DES_H323_STATE_START + 0x03); // admission confirm (reserved)
	public static final int DES_H323_ARJ                = (DES_H323_STATE_START + 0x04); // admission reject (reserved)
	public static final int DES_H323_INCOMPADDR         = (DES_H323_STATE_START + 0x05); // incomplete address (reserved)
	public static final int DES_H323_WAITACK            = (DES_H323_STATE_START + 0x06); // wait for address ack (reserved)
	
	// VoIP SIPЭ������״̬
	public static final int DES_SIP_STATE_START         = 0x00010200;
	public static final int DES_SIP_REDIRECTED          = (DES_SIP_STATE_START + 0x01);  // call redirected
	public static final int DES_SIP_UNAUTH              = (DES_SIP_STATE_START + 0x02);  // unauthenticated
	public static final int DES_SIP_ACCEPTED            = (DES_SIP_STATE_START + 0x03);  // accepted (200 ok sent, waiting ack)
	public static final int DES_SIP_REMOTEACCEPT        = (DES_SIP_STATE_START + 0x04);  // remote party accepted (reserved)
	public static final int DES_SIP_DISCONNECTING       = (DES_SIP_STATE_START + 0x05);  // BYE sent
	public static final int DES_SIP_TERMINATED          = (DES_SIP_STATE_START + 0x06);  // call finished
	public static final int DES_SIP_CANCELLED           = (DES_SIP_STATE_START + 0x07);  // call cancelled
	public static final int DES_SIP_CANCELLING          = (DES_SIP_STATE_START + 0x08);  // CANCEL sent
	public static final int DES_SIP_TIMEOUT             = (DES_SIP_STATE_START + 0x09);  // timeout after 1xx response received (reserved)
	public static final int DES_SIP_MSGSENDFAIL         = (DES_SIP_STATE_START + 0x0A);  // message send failed
	
	// ANALOG_TRUNKģ��/�ӿ�
	public static final int DES_ANALOG_TRUNK_STATE_START     = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK << 8);         // ANALOG_TRUNK ����״̬
	public static final int DES_ANALOG_TRUNK_OFFHOOK         = (DES_ANALOG_TRUNK_STATE_START | 0x01);  // ����ʱ,ժ��
	public static final int DES_ANALOG_TRUNK_CALLOUT_FAILURE = (DES_ANALOG_TRUNK_STATE_START | 0x02);  // ����ʧ��
	
	// ANALOG_USERģ��/�ӿ�
	public static final int DES_ANALOG_USER_STATE_START      = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER << 8);         // ANALOG_USER ����״̬
	public static final int DES_ANALOG_USER_RING             = (DES_ANALOG_USER_STATE_START | 0x01);  // ����
	public static final int DES_ANALOG_USER_OFFHOOK          = (DES_ANALOG_USER_STATE_START | 0x02);  // ����ʱ,ժ��
	
	public static final int DES_DIGITAL_REC_STATE_START      = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_DIGITAL_REC << 8);         // 
	public static final int DES_DIGITAL_REC_VAD_VOC          = (DES_DIGITAL_REC_STATE_START | 0x01);  // 
	public static final int DES_DIGITAL_REC_VAD_NON_VOC      = (DES_DIGITAL_REC_STATE_START | 0x02);  //
	
	public static final int DES_FAX_START                      = (XMS_DEVMAIN_TYPE.XMS_DEVMAIN_FAX<<16);  // FAX ����״̬ //
	public static final int DES_FAX_OPEN                       = (DES_FAX_START ) ;      //0  ��
	public static final int DES_FAX_CLOSE                      = (DES_FAX_START | 0x01); //1  �ر�
	public static final int DES_FAX_RESET                      = (DES_FAX_START | 0x02); //2  ��λ
	public static final int DES_FAX_SETPARAM		   		   = (DES_FAX_START | 0x03); //3  �û����ô������
	
	public static final int DES_FAX_SENDFAX_RECVCMD            = (DES_FAX_START | 0x10); // ���ʹ���
	public static final int DES_FAX_SENDFAX_START              = (DES_FAX_START | 0x11); // ��ʼ���ʹ���
	public static final int DES_FAX_SENDFAX_REMOTESPEC         = (DES_FAX_START | 0x12); // ��ȡԶ�˴��������
	public static final int DES_FAX_SENDFAX_LOCAL_FINISH       = (DES_FAX_START | 0x13); // ���ñ��ش����ʽ
	public static final int DES_FAX_SENDFAX_SHAKEHAND_END      = (DES_FAX_START | 0x14); // �����źŽ���
	public static final int DES_FAX_SENDFAX_RESOLVE_START	   = (DES_FAX_START | 0x15); // ������ݷֽ⿪ʼ
	public static final int DES_FAX_SENDFAX_REQUESTPAGEDATA	   = (DES_FAX_START | 0x16); // ����ҳ���
	public static final int DES_FAX_SENDFAX_RESOLVE_RESULT	   = (DES_FAX_START | 0x17); // ҳ�ֽ���
	public static final int DES_FAX_SENDFAX_SENDDATA           = (DES_FAX_START | 0x18); // ���ô���ҳ���������
	public static final int DES_FAX_SENDFAX_SENDFINISH         = (DES_FAX_START | 0x19); // DSP�����̽���
	public static final int DES_FAX_SENDFAX_USERSTOP           = (DES_FAX_START | 0x1A); // ֹͣ���ʹ���
	public static final int DES_FAX_SENDFAX_SENDEND            = (DES_FAX_START | 0x1B); // ���ͽ���
	
	public static final int DES_FAX_RECVFAX_RECVCMD            = (DES_FAX_START | 0x30); // ���մ���
	public static final int DES_FAX_RECVFAX_START              = (DES_FAX_START | 0x31); // ��ʼ���մ���
	public static final int DES_FAX_RECVFAX_HANDSHAKE	  	   = (DES_FAX_START | 0x32); // ���ֽ���
	public static final int DES_FAX_RECVFAX_RECVDATA_START     = (DES_FAX_START | 0x33); // ���մ������
	public static final int DES_FAX_RECVFAX_BACKPAGESTATE	   = (DES_FAX_START | 0x34); // ҳ��״̬
	public static final int DES_FAX_RECVFAX_RECVDATA_END       = (DES_FAX_START | 0x35); // ������ݽ��ս���
	public static final int DES_FAX_RECVFAX_RE_HANDSHAKE       = (DES_FAX_START | 0x36); // ������
	public static final int DES_FAX_RECVFAX_COMPOSE_START      = (DES_FAX_START | 0x37); // �ϳɿ�ʼ
	public static final int DES_FAX_RECVFAX_COMPOSE_END        = (DES_FAX_START | 0x38); // �ϳɽ���
	public static final int DES_FAX_RECVFAX_RECVFINISH         = (DES_FAX_START | 0x39); // DSP�����̽���
	public static final int DES_FAX_RECVFAX_USERSTOP           = (DES_FAX_START | 0x3A); // StopFax
	public static final int DES_FAX_RECVFAX_RECVEND            = (DES_FAX_START | 0x3B); // ���ս���
}

class XMS_DEVICE_ATRUNK_CALLOUT_REASON
{
	public static final int XMS_ATRUNK_CALLOUT_SUCC                = 1; //
	public static final int XMS_ATRUNK_CALLOUT_WAIDAILTONE_TIMEOUT = 2; //
	public static final int XMS_ATRUNK_CALLOUT_RING_TIMEOUT        = 3; //
	public static final int XMS_ATRUNK_CALLOUT_BUSY                = 4; //
}

class XMS_DEVICE_CLEAR_CALL_CAUSE                         //�һ�ԭ����
{
	public static final int XMS_CC_ReasonUnspecified                        = 0;   //ԭ��δָ��
	public static final int XMS_CC_UnallocatedNumber                        = 1;   //δ����ĺ���
	public static final int XMS_CC_NoRouteToSpecifiedTransitNetwork         = 2;   //��·�ɵ�ָ����ת����
	public static final int XMS_CC_NoRouteToDestination                     = 3;   //��·�ɵ�Ŀ�ĵ�
	public static final int XMS_CC_SendSpecialInformationTone               = 4;   //����ר����Ϣ��
	public static final int XMS_CC_MisdialledTrunkPrefix                    = 5;   //�󲦳�;�ֹ�
	public static final int XMS_CC_Preemption                               = 8;   //Ԥռ
	public static final int XMS_CC_PreemptionCircuitReservedForReuse        = 9;   //Ԥռһ��·��������
	public static final int XMS_CC_NormalCallClearing                       = 16;  //��ĺ��в���
	public static final int XMS_CC_UserBusy                                 = 17;  //�û�æ
	public static final int XMS_CC_NoUserResponding                         = 18;  //�û�δ��Ӧ
	public static final int XMS_CC_UserAlertedNoAnswer                      = 19;  //�û�δӦ��
	public static final int XMS_CC_SubscriberAbsent                         = 20;  //�û�ȱϯ
	public static final int XMS_CC_CallRejected                             = 21;  //���о���
	public static final int XMS_CC_NumberChanged                            = 22;  //����ı�
	public static final int XMS_CC_DestinationOutOfOrder                    = 27;  //Ŀ�ĵز��ɵ���
	public static final int XMS_CC_InvalidNumberFormat                      = 28;  //��Ч�ĺ����ʽ
	public static final int XMS_CC_FacilityRejected                         = 29;  //���ܾܾ�
	public static final int XMS_CC_NormalUnspecified                        = 31;  //��δָ��
	public static final int XMS_CC_NoCircuitChannelAvailable                = 34;  //�޵�·/ͨ·����
	public static final int XMS_CC_NetworkOutOfOrder                        = 38;  //����δ����
	public static final int XMS_CC_TemporaryFailure                         = 41;  //��ʱ����
	public static final int XMS_CC_SwitchingEquipmentCongestion             = 42;  //�����豸ӵ��
	public static final int XMS_CC_AccessInformationDiscarded               = 43;  //������Ϣ����
	public static final int XMS_CC_RequestedCircuitChannelNotAvailable      = 44;  //������ĵ�·/ͨ·������
	public static final int XMS_CC_PrecedenceCallBlocked                    = 46;  //���Ⱥ��б���
	public static final int XMS_CC_ResourceUnavailableUnspecified           = 47;  //��Դ�����ã�δָ��
	public static final int XMS_CC_RequestedFacilityNotSubscribed           = 50;  //�����������δԤ��
	public static final int XMS_CC_OutgoingCallsBarredWithinCUG             = 53;  //CUG������ȥ����
	public static final int XMS_CC_IncomingCallsBarredWithinCUG             = 55;  //CUG������������
	public static final int XMS_CC_BearerCapabilityNotAuthorized            = 57;  //����������Ȩ
	public static final int XMS_CC_BearerCapabilityNotPresentlyAvailable    = 58;  //��������Ŀǰ������
	public static final int XMS_CC_ServiceOrOptionNotAvailableUnspecified   = 63;  //ҵ��/��ѡ�����ã�δָ��
	public static final int XMS_CC_BearerCapabilityNotImplemented           = 65;  //��������δʵ��
	public static final int XMS_CC_RequestedFacilityNotImplemented          = 69;  //�����������δʵ��
	public static final int XMS_CC_RestrictedDigitalInfoBearerIsAvailable   = 70;  //ֻ�����޵�������Ϣ������������
	public static final int XMS_CC_ServiceOrOptionNotImplementedUnspecified = 79;  //ҵ�����ѡδʵ�֣�δָ��
	public static final int XMS_CC_UserNotMemberOfCUG                       = 87;  //�����û�����CUG�ĳ�Ա
	public static final int XMS_CC_IncompatibleDestination                  = 88;  //�����ݵ�Ŀ�ĵ�
	public static final int XMS_CC_NonExistentCUG                           = 90;  //�����ڵ�CUG
	public static final int XMS_CC_InvalidTransitNetworkSelection           = 91;  //��Ч��ת����ѡ��
	public static final int XMS_CC_InvalidMessageUnspecified                = 95;  //��Ч����Ϣ��δָ��
	public static final int XMS_CC_MessageTypeNonExistenOrNotImplemented    = 97;  //��Ϣ���Ͳ����ڻ�δʵ��
	public static final int XMS_CC_InfElementNonExistentOrNotImplemented    = 99;  //������ڻ�δʵ��
	public static final int XMS_CC_RecoveryOnTimerExpiry                    = 102; //��ʱ������ʱ�ָ�
	public static final int XMS_CC_ParameterNonExistentOrNotImplement       = 103; //������ڻ�δʵ�֣�����
	public static final int XMS_CC_MessageWithUnrecognizedParameter         = 110; //��Ϣ����δ��ʶ��Ĳ�������
	public static final int XMS_CC_ProtocolErrorUnspecified                 = 111; //Э�����δָ��
	public static final int XMS_CC_InterworkingUnspecified                  = 127; //��ͨ��δָ��
	
	//
	public static final int XMS_CC_DualSeizure                              = 129; // ͬ��
	public static final int XMS_CC_RemoteBlock                              = 130; // Զ�����
	public static final int XMS_CC_RemoteUnblock                            = 131; // Զ��������
	public static final int XMS_CC_ResetCircuit                             = 132; // ��·��ԭ
	public static final int XMS_CC_LocalBusy                                = 133; // �û���æ(TUP)
}

//////////////////////////////////////////////////////////////////////////
class XMS_VOIP_ERRCODE
{
	public static final int XMS_VOIP_ERR_OK							= 0;	// command succeed with no error
	public static final int XMS_VOIP_ERR_INTERNAL					= -1;	// internal error
	public static final int XMS_VOIP_ERR_SERVICE_DISABLED			= -2;	// service disabled
	public static final int XMS_VOIP_ERR_INVALID_CALLID				= -3;	// call id invalid
	public static final int XMS_VOIP_ERR_UNKNOWN_PROTOCOL			= -4;	// call protocol unknown
	public static final int XMS_VOIP_ERR_CALL_ACTIVE				= -5;	// call is active
	public static final int XMS_VOIP_ERR_CALL_FREE					= -6;	// call is free
	public static final int XMS_VOIP_ERR_SLOT_NOACCESS				= -7;	// call slot no access
}

class XMS_VOIP_DISCONNECT_REASON
{
	public static final int XMS_VOIP_DISCONNECT_UNKNOWN				= 0x00;	// unknown reason
	public static final int XMS_VOIP_DISCONNECT_LOCAL				= 0x01;	// local disconnect
	public static final int XMS_VOIP_DISCONNECT_REMOTE				= 0x02;	// remote disconnect

	// H.323
	public static final int XMS_VOIP_DISCONNECT_H323_BUSY			= 0x03;	// busy
	public static final int XMS_VOIP_DISCONNECT_H323_REJECT			= 0x04;	// remote reject
	public static final int XMS_VOIP_DISCONNECT_H323_UNREACHABLE	= 0x05;	// not reachable

	// SIP
	public static final int XMS_VOIP_DISCONNECT_SIP_LOCAL_REJECT	= 0x06;	// local reject
	public static final int XMS_VOIP_DISCONNECT_SIP_REQUEST_FAILURE	= 0x07;	// 4xx response rcvd (not 401 or 407)
	public static final int XMS_VOIP_DISCONNECT_SIP_SERVER_FAILURE	= 0x08;	// 5xx response rcvd
	public static final int XMS_VOIP_DISCONNECT_SIP_GLOBAL_FAILURE	= 0x09;	// 6xx response rcvd
	public static final int XMS_VOIP_DISCONNECT_SIP_LOCAL_FAILURE	= 0x0A;	// local network failure
	public static final int XMS_VOIP_DISCONNECT_SIP_TIMEOUT			= 0x0B;	// time out
};

class XMS_VOC_DEV_STATE
{
	public static final int XMS_VOC_DEV_STATE_FREE		       = 0x00;   // device in free state
	public static final int XMS_VOC_DEV_STATE_PLAYING	       = 0x01;   // device in playing state
	public static final int XMS_VOC_DEV_STATE_CSPPLAYING	   = 0x02;   // device in CSPplaying state
	public static final int XMS_VOC_DEV_STATE_RECORDING	       = 0x04;   // device in recording state
	public static final int XMS_VOC_DEV_STATE_CSPRECORDING	   = 0x08;   // device in CSPrecording state
	public static final int XMS_VOC_DEV_STATE_PLAYSTOPING	   = 0x10;   // device in playstoping state
	public static final int XMS_VOC_DEV_STATE_CSPPLAYSTOPING   = 0x20;   // device in CSPplaystoping state
	public static final int XMS_VOC_DEV_STATE_RECORDSTOPING	   = 0x40;   // device in recordstoping state
	public static final int XMS_VOC_DEV_STATE_CSPRECORDSTOPING = 0x80;   // device in CSPrecordstoping state
	public static final int XMS_VOC_DEV_STATE_SENDINGIODATA    = 0x100;  // device in SENDINGIODATA state
}