unit DJAcsDevState;

interface

uses
  DJAcsDataDef;

Type DEVICE_CALL_STATE=
(
  DEVICE_COMMON_STATE_START   = 0,
  DCS_FREE                    = 1,   // ����״̬(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
  DCS_LOCAL_BLOCK             = 2,   // ��������(TUP,ISUP)
  DCS_REMOTE_BLOCK            = 3,   // Զ������(TUP,ISUP)
  DCS_BLOCK                   = 4,   // ���غ�Զ������(ISUP)
  DCS_UNAVAILABLE             = 5,   // ������(TUP,ISUP,PRI)

  DCS_CALLOUT                 = 6,   // ��ʼ����(TUP,ISUP,PRI,VOIP,ANA_TRK)
  DCS_CALLIN                  = 7,   // ���н���(TUP,ISUP,PRI,VOIP,ANA_TRK)
  DCS_ALERTING                = 8,   // ��ַ������û������(TUP,ISUP)

  DCS_CONNECT                 = 9,   // ��ͨ(���������з�ʽ)(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)

  DCS_DISCONNECT              = $A,  // �յ�����(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
  DCS_WAIT_FREE               = $B,  // �Բ��ߵ���Ӧ(TUP,ISUP,PRI,VOIP)

  	/////////////// ģ��/�ӿ���غ���״̬���� /////////////////////////////////////////////////////////
	DEVICE_ESPECIAL_STATE_START = $0100,
	// ISUPģ��/�ӿ�
	DES_ISUP_STATE_START        = (Integer(XMS_DEVSUB_E1_SS7_ISUP)  shl  8), // ISUP����״̬ //
	DES_ISUP_LOCAL_SUSPEND      = (DES_ISUP_STATE_START  or  $01), // ������ͣ
	DES_ISUP_REMOTE_SUSPEND     = (DES_ISUP_STATE_START  or  $02), // Զ����ͣ
	DES_ISUP_LOCAL_RESUME       = (DES_ISUP_STATE_START  or  $03), // ���ؼ���
	DES_ISUP_REMOTE_RESUME      = (DES_ISUP_STATE_START  or  $04), // Զ�˼���
	DES_ISUP_RECV_INR           = (DES_ISUP_STATE_START  or  $05), // �յ�INR������Ϣ
	DES_ISUP_RECV_INF           = (DES_ISUP_STATE_START or $06), // �յ�INF������Ϣ
	DES_ISUP_RECV_CQR           = (DES_ISUP_STATE_START or $07), // �յ�CQR������Ϣ
	DES_ISUP_RECV_USR           = (DES_ISUP_STATE_START or $08), // �յ�USR������Ϣ
	DES_ISUP_RECV_CPG           = (DES_ISUP_STATE_START or $09), // �յ�CPG������Ϣ
	
	// TUPģ��/�ӿ�
	DES_TUP_STATE_START         = (Integer(XMS_DEVSUB_E1_SS7_TUP)  shl  8),  // TUP ����״̬ //
	DES_TUP_RECV_CCL            = (DES_TUP_STATE_START or $01),  // �յ�CCL������Ϣ
	DES_TUP_RECV_RAN            = (DES_TUP_STATE_START or $02),  // �յ�RAN������Ϣ
	DES_TUP_RECV_GSM            = (DES_TUP_STATE_START or $03),  // �յ�GSM������Ϣ

	DES_SS7_LINK_STATE_START    = (Integer(XMS_DEVSUB_SS7_LINK)  shl  8),    //
	DES_SS7_LST_CONNECTING      = (DES_SS7_LINK_STATE_START or $01),
	DES_SS7_LST_ACTIVE          = (DES_SS7_LINK_STATE_START or $02),
	DES_SS7_LST_FAILED          = (DES_SS7_LINK_STATE_START or $03),
	DES_SS7_LST_WAITCON         = (DES_SS7_LINK_STATE_START or $04),
	DES_SS7_LST_SUSPEND         = (DES_SS7_LINK_STATE_START or $05),

	DES_DSS1_STATE_START        = (Integer(XMS_DEVSUB_E1_DSS1)  shl  8),      // DSS1 ����״̬ //
	DES_DSS1_RESTRAT            = (DES_DSS1_STATE_START or $01),  // Ӧ�ÿ�ʼ��������״̬
	DES_DSS1_WAIT_CONNECT_ACK   = (DES_DSS1_STATE_START or $02),  // �ȴ�����֤ʵ
	DES_DSS1_CALLER_RECV_ALERT  = (DES_DSS1_STATE_START or $03),  //ȥ�������ѽ��յ�������Ϣ
	DES_DSS1_CALLER_RECV_CALLPROCESS = (DES_DSS1_STATE_START or $04),  //ȥ�������ѽ��յ����н�����Ϣ
	DES_DSS1_CALLER_RECV_SETUP_ACK	 = (DES_DSS1_STATE_START or $05),  //ȥ�������ѽ��յ�����ȷ����Ϣ
	DES_DSS1_CALLER_WAIT_SETUP_ACK	 = (DES_DSS1_STATE_START or $06),  //ȥ�������ȴ�����ȷ��
	
	// VoIP H.323Э������״̬
	DES_H323_STATE_START        = $00010100,
	DES_H323_PROCEEDING         = (DES_H323_STATE_START + $01), // proceeding
	DES_H323_TRANSFERING        = (DES_H323_STATE_START + $02), // transfering
	DES_H323_ACF                = (DES_H323_STATE_START + $03), // admission confirm (reserved)
	DES_H323_ARJ                = (DES_H323_STATE_START + $04), // admission reject (reserved)
	DES_H323_INCOMPADDR         = (DES_H323_STATE_START + $05), // incomplete address (reserved)
	DES_H323_WAITACK            = (DES_H323_STATE_START + $06), // wait f or  address ack (reserved)
	
	// VoIP SIPЭ������״̬
	DES_SIP_STATE_START         = $00010200,
	DES_SIP_REDIRECTED          = (DES_SIP_STATE_START + $01),  // call redirected
	DES_SIP_UNAUTH              = (DES_SIP_STATE_START + $02),  // unauthenticated
	DES_SIP_ACCEPTED            = (DES_SIP_STATE_START + $03),  // accepted (200 ok sent, waiting ack)
	DES_SIP_REMOTEACCEPT        = (DES_SIP_STATE_START + $04),  // remote party accepted (reserved)
	DES_SIP_DISCONNECTING       = (DES_SIP_STATE_START + $05),  // BYE sent
	DES_SIP_TERMINATED          = (DES_SIP_STATE_START + $06),  // call finished
	DES_SIP_CANCELLED           = (DES_SIP_STATE_START + $07),  // call cancelled
	DES_SIP_CANCELLING          = (DES_SIP_STATE_START + $08),  // CANCEL sent
	DES_SIP_TIMEOUT             = (DES_SIP_STATE_START + $09),  // timeout after 1xx response received (reserved)
	DES_SIP_MSGSENDFAIL         = (DES_SIP_STATE_START + $0A),  // message send failed
	
	// ANALOG_TRUNKģ��/�ӿ�
	DES_ANALOG_TRUNK_STATE_START     = (Integer(XMS_DEVSUB_ANALOG_TRUNK)  shl  8),         // ANALOG_TRUNK ����״̬
	DES_ANALOG_TRUNK_OFFHOOK         = (DES_ANALOG_TRUNK_STATE_START or $01),  // ����ʱ,ժ��
	DES_ANALOG_TRUNK_CALLOUT_FAILURE = (DES_ANALOG_TRUNK_STATE_START or $02),  // ����ʧ��
	
	// ANALOG_USERģ��/�ӿ�
	DES_ANALOG_USER_STATE_START      = (Integer(XMS_DEVSUB_ANALOG_USER)  shl  8),         // ANALOG_USER ����״̬
	DES_ANALOG_USER_RING             = (DES_ANALOG_USER_STATE_START or $01),  // ����
	DES_ANALOG_USER_OFFHOOK          = (DES_ANALOG_USER_STATE_START or $02),  // ����ʱ,ժ��
	
	DES_DIGITAL_REC_STATE_START      = (Integer(XMS_DEVSUB_DIGITAL_REC)  shl  8),         //
	DES_DIGITAL_REC_VAD_VOC          = (DES_DIGITAL_REC_STATE_START or $01),  //
	DES_DIGITAL_REC_VAD_NON_VOC      = (DES_DIGITAL_REC_STATE_START or $02),  //
	
	DES_FAX_START                      = (Integer(XMS_DEVMAIN_FAX) shl 16),  // FAX ����״̬ //
	DES_FAX_OPEN                       = (DES_FAX_START ) ,      //0  ��
	DES_FAX_CLOSE                      = (DES_FAX_START or $01), //1  �ر�
	DES_FAX_RESET                      = (DES_FAX_START or $02), //2  ��λ
	DES_FAX_SETPARAM		               = (DES_FAX_START or $03), //3  �û����ô������
	
	DES_FAX_SENDFAX_RECVCMD            = (DES_FAX_START or $10), // ���ʹ���
	DES_FAX_SENDFAX_START              = (DES_FAX_START or $11), // ��ʼ���ʹ���
	DES_FAX_SENDFAX_REMOTESPEC         = (DES_FAX_START or $12), // ��ȡԶ�˴��������
	DES_FAX_SENDFAX_LOCAL_FINISH       = (DES_FAX_START or $13), // ���ñ��ش����ʽ
	DES_FAX_SENDFAX_SHAKEHAND_END      = (DES_FAX_START or $14), // �����źŽ���
	DES_FAX_SENDFAX_RESOLVE_START	     = (DES_FAX_START or $15), // �������ݷֽ⿪ʼ
	DES_FAX_SENDFAX_REQUESTPAGEDATA	   = (DES_FAX_START or $16), // ����ҳ����
	DES_FAX_SENDFAX_RESOLVE_RESULT	   = (DES_FAX_START or $17), // ҳ�ֽ���
	DES_FAX_SENDFAX_SENDDATA           = (DES_FAX_START or $18), // ���ô���ҳ����������
	DES_FAX_SENDFAX_SENDFINISH         = (DES_FAX_START or $19), // DSP������̽���
	DES_FAX_SENDFAX_USERSTOP           = (DES_FAX_START or $1A), // ֹͣ���ʹ���
	DES_FAX_SENDFAX_SENDEND            = (DES_FAX_START or $1B), // ���ͽ���
	
	DES_FAX_RECVFAX_RECVCMD            = (DES_FAX_START or $30), // ���մ���
	DES_FAX_RECVFAX_START              = (DES_FAX_START or $31), // ��ʼ���մ���
	DES_FAX_RECVFAX_HANDSHAKE	         = (DES_FAX_START or $32), // ���ֽ���
	DES_FAX_RECVFAX_RECVDATA_START     = (DES_FAX_START or $33), // ���մ�������
	DES_FAX_RECVFAX_BACKPAGESTATE	     = (DES_FAX_START or $34), // ҳ��״̬
	DES_FAX_RECVFAX_RECVDATA_END       = (DES_FAX_START or $35), // �������ݽ��ս���
	DES_FAX_RECVFAX_RE_HANDSHAKE       = (DES_FAX_START or $36), // ������
	DES_FAX_RECVFAX_COMPOSE_START      = (DES_FAX_START or $37), // �ϳɿ�ʼ
	DES_FAX_RECVFAX_COMPOSE_END        = (DES_FAX_START or $38), // �ϳɽ���
	DES_FAX_RECVFAX_RECVFINISH         = (DES_FAX_START or $39), // DSP������̽���
	DES_FAX_RECVFAX_USERSTOP           = (DES_FAX_START or $3A), // StopFax
	DES_FAX_RECVFAX_RECVEND            = (DES_FAX_START or $3B)  // ���ս���
);

Type XMS_DEVICE_ATRUNK_CALLOUT_REASON =
(
	XMS_ATRUNK_CALLOUT_SUCC                = 1, //
	XMS_ATRUNK_CALLOUT_WAIDAILTONE_TIMEOUT = 2, //
	XMS_ATRUNK_CALLOUT_RING_TIMEOUT        = 3, //
	XMS_ATRUNK_CALLOUT_BUSY                = 4  //
);

Type XMS_DEVICE_CLEAR_CALL_CAUSE =                        //�һ�ԭ����
(
	XMS_CC_ReasonUnspecified                        = 0,   //ԭ��δָ��
	XMS_CC_UnallocatedNumber                        = 1,   //δ����ĺ���
	XMS_CC_NorouteToSpecifiedTransitNetwork         = 2,   //��·�ɵ�ָ����ת����
	XMS_CC_NorouteToDestination                     = 3,   //��·�ɵ�Ŀ�ĵ�
	XMS_CC_SendSpecialInformationTone               = 4,   //����ר����Ϣ��
	XMS_CC_MisdialledTrunkPrefix                    = 5,   //�󲦳�;�ֹ�
	XMS_CC_Preemption                               = 8,   //Ԥռ
	XMS_CC_PreemptionCircuitReservedForReuse        = 9,   //Ԥռһ��·��������
	XMS_CC_NormalCallClearing                       = 16,  //�����ĺ��в���
	XMS_CC_UserBusy                                 = 17,  //�û�æ
	XMS_CC_NoUserResponding                         = 18,  //�û�δ��Ӧ
	XMS_CC_UserAlertedNoAnswer                      = 19,  //�û�δӦ��
	XMS_CC_SubscriberAbsent                         = 20,  //�û�ȱϯ
	XMS_CC_CallRejected                             = 21,  //���о���
	XMS_CC_NumberChanged                            = 22,  //����ı�
	XMS_CC_DestinationOutOforder                    = 27,  //Ŀ�ĵز��ɵ���
	XMS_CC_InvalidNumberFormat                      = 28,  //��Ч�ĺ����ʽ
	XMS_CC_FacilityRejected                         = 29,  //���ܾܾ�
	XMS_CC_NormalUnspecified                        = 31,  //������δָ��
	XMS_CC_NoCircuitChannelAvailable                = 34,  //�޵�·/ͨ·����
	XMS_CC_NetworkOutOforder                        = 38,  //����δ��������
	XMS_CC_TemporaryFailure                         = 41,  //��ʱ����
	XMS_CC_SwitchingEquipmentCongestion             = 42,  //�����豸ӵ��
	XMS_CC_AccessInformationDiscarded               = 43,  //������Ϣ����
	XMS_CC_RequestedCircuitChannelNotAvailable      = 44,  //������ĵ�·/ͨ·������
	XMS_CC_PrecedenceCallBlocked                    = 46,  //���Ⱥ��б���
	XMS_CC_ResourceUnavailableUnspecified           = 47,  //��Դ�����ã�δָ��
	XMS_CC_RequestedFacilityNotSubscribed           = 50,  //�����������δԤ��
	XMS_CC_OutgoingCallsBarredWithinCUG             = 53,  //CUG������ȥ����
	XMS_CC_IncomingCallsBarredWithinCUG             = 55,  //CUG������������
	XMS_CC_BearerCapabilityNotAuthorized            = 57,  //����������Ȩ
	XMS_CC_BearerCapabilityNotPresentlyAvailable    = 58,  //��������Ŀǰ������
	XMS_CC_ServiceorOptionNotAvailableUnspecified   = 63,  //ҵ��/��ѡ�����ã�δָ��
	XMS_CC_BearerCapabilityNotImplemented           = 65,  //��������δʵ��
	XMS_CC_RequestedFacilityNotImplemented          = 69,  //�����������δʵ��
	XMS_CC_RestrictedDigitalInfoBearerIsAvailable   = 70,  //ֻ�����޵�������Ϣ������������
	XMS_CC_ServiceorOptionNotImplementedUnspecified = 79,  //ҵ�����ѡδʵ�֣�δָ��
	XMS_CC_UserNotMemberOfCUG                       = 87,  //�����û�����CUG�ĳ�Ա
	XMS_CC_IncompatibleDestination                  = 88,  //�����ݵ�Ŀ�ĵ�
	XMS_CC_NonExistentCUG                           = 90,  //�����ڵ�CUG
	XMS_CC_InvalidTransitNetworkSelection           = 91,  //��Ч��ת����ѡ��
	XMS_CC_InvalidMessageUnspecified                = 95,  //��Ч����Ϣ��δָ��
	XMS_CC_MessageTypeNonExistenorNotImplemented    = 97,  //��Ϣ���Ͳ����ڻ�δʵ��
	XMS_CC_InfElementNonExistentorNotImplemented    = 99,  //���������ڻ�δʵ��
	XMS_CC_RecoveryOnTimerExpiry                    = 102, //��ʱ������ʱ�ָ�
	XMS_CC_ParameterNonExistentorNotImplement       = 103, //���������ڻ�δʵ�֣�����
	XMS_CC_MessageWithUnrecognizedParameter         = 110, //��Ϣ����δ��ʶ��Ĳ���������
	XMS_CC_ProtocolErrorUnspecified                 = 111, //Э�����δָ��
	XMS_CC_InterworkingUnspecified                  = 127, //��ͨ��δָ��
	
	//
	XMS_CC_DualSeizure                              = 129, // ͬ��
	XMS_CC_RemoteBlock                              = 130, // Զ�����
	XMS_CC_RemoteUnblock                            = 131, // Զ���������
	XMS_CC_ResetCircuit                             = 132, // ��·��ԭ
	XMS_CC_LocalBusy                                = 133  // �û���æ(TUP)
);

//////////////////////////////////////////////////////////////////////////
Type XMS_VOIP_ERRCODE =
(
	XMS_VOIP_ERR_OK							  = 0,	// command succeed with no err or 
	XMS_VOIP_ERR_INTERNAL					= -1,	// internal err or 
	XMS_VOIP_ERR_SERVICE_DISABLED	= -2,	// service disabled
	XMS_VOIP_ERR_INVALID_CALLID		= -3,	// call id invalid
	XMS_VOIP_ERR_UNKNOWN_PROTOCOL	= -4,	// call protocol unknown
	XMS_VOIP_ERR_CALL_ACTIVE			= -5,	// call is active
	XMS_VOIP_ERR_CALL_FREE				= -6,	// call is free
	XMS_VOIP_ERR_SLOT_NOACCESS		= -7	// call slot no access
);

Type XMS_VOIP_DISCONNECT_REASON =
(
	XMS_VOIP_DISCONNECT_UNKNOWN				= $00,	// unknown reason
	XMS_VOIP_DISCONNECT_LOCAL				  = $01,	// local disconnect
	XMS_VOIP_DISCONNECT_REMOTE				= $02,	// remote disconnect

	// H.323
	XMS_VOIP_DISCONNECT_H323_BUSY			    = $03,	// busy
	XMS_VOIP_DISCONNECT_H323_REJECT			  = $04,	// remote reject
	XMS_VOIP_DISCONNECT_H323_UNREACHABLE	= $05,	// not reachable

	// SIP
	XMS_VOIP_DISCONNECT_SIP_LOCAL_REJECT	  = $06,	// local reject
	XMS_VOIP_DISCONNECT_SIP_REQUEST_FAILURE	= $07,	// 4xx response rcvd (not 401  or  407)
	XMS_VOIP_DISCONNECT_SIP_SERVER_FAILURE	= $08,	// 5xx response rcvd
	XMS_VOIP_DISCONNECT_SIP_GLOBAL_FAILURE	= $09,	// 6xx response rcvd
	XMS_VOIP_DISCONNECT_SIP_LOCAL_FAILURE	  = $0A,	// local netw or k failure
	XMS_VOIP_DISCONNECT_SIP_TIMEOUT			    = $0B	// time out
);

Type XMS_VOC_DEV_STATE = 
(
	XMS_VOC_DEV_STATE_FREE		         = $00,   // device in free state
	XMS_VOC_DEV_STATE_PLAYING	         = $01,   // device in playing state
	XMS_VOC_DEV_STATE_CSPPLAYING	     = $02,   // device in CSPplaying state
	XMS_VOC_DEV_STATE_RECORDING	       = $04,   // device in rec or ding state
	XMS_VOC_DEV_STATE_CSPRECORDING	   = $08,   // device in CSPrec or ding state
	XMS_VOC_DEV_STATE_PLAYSTOPING	     = $10,   // device in playstoping state
	XMS_VOC_DEV_STATE_CSPPLAYSTOPING   = $20,   // device in CSPplaystoping state
	XMS_VOC_DEV_STATE_RECORDSTOPING	   = $40,   // device in rec or dstoping state
	XMS_VOC_DEV_STATE_CSPRECORDSTOPING = $80,   // device in CSPrec or dstoping state
  XMS_VOC_DEV_STATE_SENDINGIODATA    = $100   // device in SENDINGIODATA state
);

implementation

end.
