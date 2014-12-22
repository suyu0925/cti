using System;
using System.Text;
using System.Runtime.InteropServices;

namespace DJKeygoe
{
    public enum DEVICE_CALL_STATE
    {
        /////////////// ͨ�ú���״̬���� //////////////////////////////////////////////////////////////////
        DEVICE_COMMON_STATE_START = 0x0000, // ͨ��״̬��ʼʶ���: TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR
        DCS_FREE = 0x0001, // ����״̬(TUP,ISUP,PRI,VOIP,ANA_TRK,ANA_USR)
        DCS_LOCAL_BLOCK = 0x0002, // ��������(TUP,ISUP)
        DCS_REMOTE_BLOCK = 0x0003, // Զ������(TUP,ISUP)
        DCS_BLOCK = 0x0004, // ���غ�Զ������(ISUP)
        DCS_UNAVAILABLE = 0x0005, // ������(TUP,ISUP,PRI)

        DCS_CALLOUT = 0x0006, // ��ʼ����(TUP,ISUP,PRI,VOIP,ANA_TRK)
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
}