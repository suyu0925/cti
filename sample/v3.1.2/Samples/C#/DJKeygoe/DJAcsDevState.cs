using System;
using System.Text;
using System.Runtime.InteropServices;

namespace DJKeygoe
{
    public enum DEVICE_CALL_STATE
    {
        /////////////// ͨ�ú���״̬���� //////////////////////////////////////////////////////////////////
        DEVICE_COMMON_STATE_START     = 0x0000, // ͨ��״̬��ʼʶ���: TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR
        DCS_FREE                                        = 0x0001, // ����״̬(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
        DCS_LOCAL_BLOCK                         = 0x0002, // ��������(TUP,ISUP)
        DCS_REMOTE_BLOCK                       = 0x0003, // Զ������(TUP,ISUP)
        DCS_BLOCK                                      = 0x0004, // ���غ�Զ������(ISUP)
        DCS_UNAVAILABLE                           = 0x0005, // ������(TUP,ISUP,PRI)

        DCS_CALLOUT                                  = 0x0006, // ��ʼ����(TUP,ISUP,PRI,VOIP,ANA_TRK)
        DCS_CALLIN = 0x0007, // ���н���(TUP,ISUP,PRI,VOIP,ANA_TRK)
        DCS_ALERTING = 0x0008, // ��ַ������û������(TUP,ISUP)

        DCS_CONNECT = 0x0009, // ��ͨ(���������з�ʽ)(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)

        DCS_DISCONNECT = 0x000A, // �յ�����(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
        DCS_WAIT_FREE = 0x000B, // �Բ��ߵ���Ӧ(TUP,ISUP,PRI,VOIP)

        /////////////// ģ��/�ӿ���غ���״̬���� /////////////////////////////////////////////////////////
        DEVICE_ESPECIAL_STATE_START = 0x0100,
        // ISUPģ��/�ӿ�
        DES_ISUP_STATE_START = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_ISUP << 8), // ISUP����״̬ //
        DES_ISUP_LOCAL_SUSPEND = (DES_ISUP_STATE_START | 0x01), // ������ͣ
        DES_ISUP_REMOTE_SUSPEND = (DES_ISUP_STATE_START | 0x02), // Զ����ͣ
        DES_ISUP_LOCAL_RESUME = (DES_ISUP_STATE_START | 0x03), // ���ؼ���
        DES_ISUP_REMOTE_RESUME = (DES_ISUP_STATE_START | 0x04), // Զ�˼���
        DES_ISUP_RECV_INR = (DES_ISUP_STATE_START | 0x05), // �յ�INR������Ϣ
        DES_ISUP_RECV_INF = (DES_ISUP_STATE_START | 0x06), // �յ�INF������Ϣ
        DES_ISUP_RECV_CQR = (DES_ISUP_STATE_START | 0x07), // �յ�CQR������Ϣ
        DES_ISUP_RECV_USR = (DES_ISUP_STATE_START | 0x08), // �յ�USR������Ϣ
        DES_ISUP_RECV_CPG = (DES_ISUP_STATE_START | 0x09), // �յ�CPG������Ϣ

        // TUPģ��/�ӿ�
        DES_TUP_STATE_START = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_SS7_TUP << 8),  // TUP ����״̬ //
        DES_TUP_RECV_CCL = (DES_TUP_STATE_START | 0x01),  // �յ�CCL������Ϣ
        DES_TUP_RECV_RAN = (DES_TUP_STATE_START | 0x02),  // �յ�RAN������Ϣ
        DES_TUP_RECV_GSM = (DES_TUP_STATE_START | 0x03),  // �յ�GSM������Ϣ

        DES_SS7_LINK_STATE_START = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_SS7_LINK << 8),    // 
        DES_SS7_LST_CONNECTING = (DES_SS7_LINK_STATE_START | 0x01),
        DES_SS7_LST_ACTIVE = (DES_SS7_LINK_STATE_START | 0x02),
        DES_SS7_LST_FAILED = (DES_SS7_LINK_STATE_START | 0x03),
        DES_SS7_LST_WAITCON = (DES_SS7_LINK_STATE_START | 0x04),
        DES_SS7_LST_SUSPEND = (DES_SS7_LINK_STATE_START | 0x05),

        DES_DSS1_STATE_START = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_E1_DSS1 << 8),      // DSS1 ����״̬ //
        DES_DSS1_RESTRAT = (DES_DSS1_STATE_START | 0x01),  // Ӧ�ÿ�ʼ��������״̬
        DES_DSS1_WAIT_CONNECT_ACK = (DES_DSS1_STATE_START | 0x02),  // �ȴ�����֤ʵ
        DES_DSS1_CALLER_RECV_ALERT = (DES_DSS1_STATE_START | 0x03),  //ȥ�������ѽ��յ�������Ϣ
        DES_DSS1_CALLER_RECV_CALLPROCESS = (DES_DSS1_STATE_START | 0x04),  //ȥ�������ѽ��յ����н�����Ϣ
        DES_DSS1_CALLER_RECV_SETUP_ACK = (DES_DSS1_STATE_START | 0x05),  //ȥ�������ѽ��յ�����ȷ����Ϣ
        DES_DSS1_CALLER_WAIT_SETUP_ACK = (DES_DSS1_STATE_START | 0x06),  //ȥ�������ȴ�����ȷ��

        // VoIP H.323Э������״̬
        DES_H323_STATE_START = 0x00010100,
        DES_H323_PROCEEDING = (DES_H323_STATE_START + 0x01), // proceeding
        DES_H323_TRANSFERING = (DES_H323_STATE_START + 0x02), // transfering
        DES_H323_ACF = (DES_H323_STATE_START + 0x03), // admission confirm (reserved)
        DES_H323_ARJ = (DES_H323_STATE_START + 0x04), // admission reject (reserved)
        DES_H323_INCOMPADDR = (DES_H323_STATE_START + 0x05), // incomplete address (reserved)
        DES_H323_WAITACK = (DES_H323_STATE_START + 0x06), // wait for address ack (reserved)

        // VoIP SIPЭ������״̬
        DES_SIP_STATE_START = 0x00010200,
        DES_SIP_REDIRECTED = (DES_SIP_STATE_START + 0x01),  // call redirected
        DES_SIP_UNAUTH = (DES_SIP_STATE_START + 0x02),  // unauthenticated
        DES_SIP_ACCEPTED = (DES_SIP_STATE_START + 0x03),  // accepted (200 ok sent, waiting ack)
        DES_SIP_REMOTEACCEPT = (DES_SIP_STATE_START + 0x04),  // remote party accepted (reserved)
        DES_SIP_DISCONNECTING = (DES_SIP_STATE_START + 0x05),  // BYE sent
        DES_SIP_TERMINATED = (DES_SIP_STATE_START + 0x06),  // call finished
        DES_SIP_CANCELLED = (DES_SIP_STATE_START + 0x07),  // call cancelled
        DES_SIP_CANCELLING = (DES_SIP_STATE_START + 0x08),  // CANCEL sent
        DES_SIP_TIMEOUT = (DES_SIP_STATE_START + 0x09),  // timeout after 1xx response received (reserved)
        DES_SIP_MSGSENDFAIL = (DES_SIP_STATE_START + 0x0A),  // message send failed

        // ANALOG_TRUNKģ��/�ӿ�
        DES_ANALOG_TRUNK_STATE_START = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_TRUNK << 8),         // ANALOG_TRUNK ����״̬
        DES_ANALOG_TRUNK_OFFHOOK = (DES_ANALOG_TRUNK_STATE_START | 0x01),  // ����ʱ,ժ��
        DES_ANALOG_TRUNK_CALLOUT_FAILURE = (DES_ANALOG_TRUNK_STATE_START | 0x02),  // ����ʧ��

        // ANALOG_USERģ��/�ӿ�
        DES_ANALOG_USER_STATE_START = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_ANALOG_USER << 8),         // ANALOG_USER ����״̬
        DES_ANALOG_USER_RING = (DES_ANALOG_USER_STATE_START | 0x01),  // ����
        DES_ANALOG_USER_OFFHOOK = (DES_ANALOG_USER_STATE_START | 0x02),  // ����ʱ,ժ��

        DES_DIGITAL_REC_STATE_START = (XMS_INTERFACE_DEVSUB_TYPE.XMS_DEVSUB_DIGITAL_REC << 8),         // 
        DES_DIGITAL_REC_VAD_VOC = (DES_DIGITAL_REC_STATE_START | 0x01),  // 
        DES_DIGITAL_REC_VAD_NON_VOC = (DES_DIGITAL_REC_STATE_START | 0x02),  //

        DES_FAX_START = (XMS_DEVMAIN_TYPE.XMS_DEVMAIN_FAX << 16),  // FAX ����״̬ //
        DES_FAX_OPEN = (DES_FAX_START),      //0  ��
        DES_FAX_CLOSE = (DES_FAX_START | 0x01), //1  �ر�
        DES_FAX_RESET = (DES_FAX_START | 0x02), //2  ��λ
        DES_FAX_SETPARAM = (DES_FAX_START | 0x03), //3  �û����ô������

        DES_FAX_SENDFAX_RECVCMD = (DES_FAX_START | 0x10), // ���ʹ���
        DES_FAX_SENDFAX_START = (DES_FAX_START | 0x11), // ��ʼ���ʹ���
        DES_FAX_SENDFAX_REMOTESPEC = (DES_FAX_START | 0x12), // ��ȡԶ�˴��������
        DES_FAX_SENDFAX_LOCAL_FINISH = (DES_FAX_START | 0x13), // ���ñ��ش����ʽ
        DES_FAX_SENDFAX_SHAKEHAND_END = (DES_FAX_START | 0x14), // �����źŽ���
        DES_FAX_SENDFAX_RESOLVE_START = (DES_FAX_START | 0x15), // �������ݷֽ⿪ʼ
        DES_FAX_SENDFAX_REQUESTPAGEDATA = (DES_FAX_START | 0x16), // ����ҳ����
        DES_FAX_SENDFAX_RESOLVE_RESULT = (DES_FAX_START | 0x17), // ҳ�ֽ���
        DES_FAX_SENDFAX_SENDDATA = (DES_FAX_START | 0x18), // ���ô���ҳ����������
        DES_FAX_SENDFAX_SENDFINISH = (DES_FAX_START | 0x19), // DSP������̽���
        DES_FAX_SENDFAX_USERSTOP = (DES_FAX_START | 0x1A), // ֹͣ���ʹ���
        DES_FAX_SENDFAX_SENDEND = (DES_FAX_START | 0x1B), // ���ͽ���

        DES_FAX_RECVFAX_RECVCMD = (DES_FAX_START | 0x30), // ���մ���
        DES_FAX_RECVFAX_START = (DES_FAX_START | 0x31), // ��ʼ���մ���
        DES_FAX_RECVFAX_HANDSHAKE = (DES_FAX_START | 0x32), // ���ֽ���
        DES_FAX_RECVFAX_RECVDATA_START = (DES_FAX_START | 0x33), // ���մ�������
        DES_FAX_RECVFAX_BACKPAGESTATE = (DES_FAX_START | 0x34), // ҳ��״̬
        DES_FAX_RECVFAX_RECVDATA_END = (DES_FAX_START | 0x35), // �������ݽ��ս���
        DES_FAX_RECVFAX_RE_HANDSHAKE = (DES_FAX_START | 0x36), // ������
        DES_FAX_RECVFAX_COMPOSE_START = (DES_FAX_START | 0x37), // �ϳɿ�ʼ
        DES_FAX_RECVFAX_COMPOSE_END = (DES_FAX_START | 0x38), // �ϳɽ���
        DES_FAX_RECVFAX_RECVFINISH = (DES_FAX_START | 0x39), // DSP������̽���
        DES_FAX_RECVFAX_USERSTOP = (DES_FAX_START | 0x3A), // StopFax
        DES_FAX_RECVFAX_RECVEND = (DES_FAX_START | 0x3B), // ���ս���
    };

    public enum XMS_DEVICE_ATRUNK_CALLOUT_REASON
    {
        XMS_ATRUNK_CALLOUT_SUCC = 1, //
        XMS_ATRUNK_CALLOUT_WAIDAILTONE_TIMEOUT = 2, //
        XMS_ATRUNK_CALLOUT_RING_TIMEOUT = 3, //
        XMS_ATRUNK_CALLOUT_BUSY = 4, //
    };

    public enum XMS_DEVICE_CLEAR_CALL_CAUSE                         //�һ�ԭ����
    {
        XMS_CC_ReasonUnspecified = 0,   //ԭ��δָ��
        XMS_CC_UnallocatedNumber = 1,   //δ����ĺ���
        XMS_CC_NoRouteToSpecifiedTransitNetwork = 2,   //��·�ɵ�ָ����ת����
        XMS_CC_NoRouteToDestination = 3,   //��·�ɵ�Ŀ�ĵ�
        XMS_CC_SendSpecialInformationTone = 4,   //����ר����Ϣ��
        XMS_CC_MisdialledTrunkPrefix = 5,   //�󲦳�;�ֹ�
        XMS_CC_Preemption = 8,   //Ԥռ
        XMS_CC_PreemptionCircuitReservedForReuse = 9,   //Ԥռһ��·��������
        XMS_CC_NormalCallClearing = 16,  //�����ĺ��в���
        XMS_CC_UserBusy = 17,  //�û�æ
        XMS_CC_NoUserResponding = 18,  //�û�δ��Ӧ
        XMS_CC_UserAlertedNoAnswer = 19,  //�û�δӦ��
        XMS_CC_SubscriberAbsent = 20,  //�û�ȱϯ
        XMS_CC_CallRejected = 21,  //���о���
        XMS_CC_NumberChanged = 22,  //����ı�
        XMS_CC_DestinationOutOfOrder = 27,  //Ŀ�ĵز��ɵ���
        XMS_CC_InvalidNumberFormat = 28,  //��Ч�ĺ����ʽ
        XMS_CC_FacilityRejected = 29,  //���ܾܾ�
        XMS_CC_NormalUnspecified = 31,  //������δָ��
        XMS_CC_NoCircuitChannelAvailable = 34,  //�޵�·/ͨ·����
        XMS_CC_NetworkOutOfOrder = 38,  //����δ��������
        XMS_CC_TemporaryFailure = 41,  //��ʱ����
        XMS_CC_SwitchingEquipmentCongestion = 42,  //�����豸ӵ��
        XMS_CC_AccessInformationDiscarded = 43,  //������Ϣ����
        XMS_CC_RequestedCircuitChannelNotAvailable = 44,  //������ĵ�·/ͨ·������
        XMS_CC_PrecedenceCallBlocked = 46,  //���Ⱥ��б���
        XMS_CC_ResourceUnavailableUnspecified = 47,  //��Դ�����ã�δָ��
        XMS_CC_RequestedFacilityNotSubscribed = 50,  //�����������δԤ��
        XMS_CC_OutgoingCallsBarredWithinCUG = 53,  //CUG������ȥ����
        XMS_CC_IncomingCallsBarredWithinCUG = 55,  //CUG������������
        XMS_CC_BearerCapabilityNotAuthorized = 57,  //����������Ȩ
        XMS_CC_BearerCapabilityNotPresentlyAvailable = 58,  //��������Ŀǰ������
        XMS_CC_ServiceOrOptionNotAvailableUnspecified = 63,  //ҵ��/��ѡ�����ã�δָ��
        XMS_CC_BearerCapabilityNotImplemented = 65,  //��������δʵ��
        XMS_CC_RequestedFacilityNotImplemented = 69,  //�����������δʵ��
        XMS_CC_RestrictedDigitalInfoBearerIsAvailable = 70,  //ֻ�����޵�������Ϣ������������
        XMS_CC_ServiceOrOptionNotImplementedUnspecified = 79,  //ҵ�����ѡδʵ�֣�δָ��
        XMS_CC_UserNotMemberOfCUG = 87,  //�����û�����CUG�ĳ�Ա
        XMS_CC_IncompatibleDestination = 88,  //�����ݵ�Ŀ�ĵ�
        XMS_CC_NonExistentCUG = 90,  //�����ڵ�CUG
        XMS_CC_InvalidTransitNetworkSelection = 91,  //��Ч��ת����ѡ��
        XMS_CC_InvalidMessageUnspecified = 95,  //��Ч����Ϣ��δָ��
        XMS_CC_MessageTypeNonExistenOrNotImplemented = 97,  //��Ϣ���Ͳ����ڻ�δʵ��
        XMS_CC_InfElementNonExistentOrNotImplemented = 99,  //���������ڻ�δʵ��
        XMS_CC_RecoveryOnTimerExpiry = 102, //��ʱ������ʱ�ָ�
        XMS_CC_ParameterNonExistentOrNotImplement = 103, //���������ڻ�δʵ�֣�����
        XMS_CC_MessageWithUnrecognizedParameter = 110, //��Ϣ����δ��ʶ��Ĳ���������
        XMS_CC_ProtocolErrorUnspecified = 111, //Э�����δָ��
        XMS_CC_InterworkingUnspecified = 127, //��ͨ��δָ��

        //
        XMS_CC_DualSeizure = 129, // ͬ��
        XMS_CC_RemoteBlock = 130, // Զ�����
        XMS_CC_RemoteUnblock = 131, // Զ���������
        XMS_CC_ResetCircuit = 132, // ��·��ԭ
        XMS_CC_LocalBusy = 133, // �û���æ(TUP)
    };

    //////////////////////////////////////////////////////////////////////////
    public enum XMS_VOIP_ERRCODE
    {
        XMS_VOIP_ERR_OK = 0,	// command succeed with no error
        XMS_VOIP_ERR_INTERNAL = -1,	// internal error
        XMS_VOIP_ERR_SERVICE_DISABLED = -2,	// service disabled
        XMS_VOIP_ERR_INVALID_CALLID = -3,	// call id invalid
        XMS_VOIP_ERR_UNKNOWN_PROTOCOL = -4,	// call protocol unknown
        XMS_VOIP_ERR_CALL_ACTIVE = -5,	// call is active
        XMS_VOIP_ERR_CALL_FREE = -6,	// call is free
        XMS_VOIP_ERR_SLOT_NOACCESS = -7	// call slot no access
    };

    public enum XMS_VOIP_DISCONNECT_REASON
    {
        XMS_VOIP_DISCONNECT_UNKNOWN = 0x00,	// unknown reason
        XMS_VOIP_DISCONNECT_LOCAL = 0x01,	// local disconnect
        XMS_VOIP_DISCONNECT_REMOTE = 0x02,	// remote disconnect

        // H.323
        XMS_VOIP_DISCONNECT_H323_BUSY = 0x03,	// busy
        XMS_VOIP_DISCONNECT_H323_REJECT = 0x04,	// remote reject
        XMS_VOIP_DISCONNECT_H323_UNREACHABLE = 0x05,	// not reachable

        // SIP
        XMS_VOIP_DISCONNECT_SIP_LOCAL_REJECT = 0x06,	// local reject
        XMS_VOIP_DISCONNECT_SIP_REQUEST_FAILURE = 0x07,	// 4xx response rcvd (not 401 or 407)
        XMS_VOIP_DISCONNECT_SIP_SERVER_FAILURE = 0x08,	// 5xx response rcvd
        XMS_VOIP_DISCONNECT_SIP_GLOBAL_FAILURE = 0x09,	// 6xx response rcvd
        XMS_VOIP_DISCONNECT_SIP_LOCAL_FAILURE = 0x0A,	// local network failure
        XMS_VOIP_DISCONNECT_SIP_TIMEOUT = 0x0B	// time out
    };

    public enum XMS_VOC_DEV_STATE
    {
        XMS_VOC_DEV_STATE_FREE = 0x00,   // device in free state
        XMS_VOC_DEV_STATE_PLAYING = 0x01,   // device in playing state
        XMS_VOC_DEV_STATE_CSPPLAYING = 0x02,   // device in CSPplaying state
        XMS_VOC_DEV_STATE_RECORDING = 0x04,   // device in recording state
        XMS_VOC_DEV_STATE_CSPRECORDING = 0x08,   // device in CSPrecording state
        XMS_VOC_DEV_STATE_PLAYSTOPING = 0x10,   // device in playstoping state
        XMS_VOC_DEV_STATE_CSPPLAYSTOPING = 0x20,   // device in CSPplaystoping state
        XMS_VOC_DEV_STATE_RECORDSTOPING = 0x40,   // device in recordstoping state
        XMS_VOC_DEV_STATE_CSPRECORDSTOPING = 0x80,   // device in CSPrecordstoping state
        XMS_VOC_DEV_STATE_SENDINGIODATA = 0x100,  // device in SENDINGIODATA state
    };
}