using System;
using System.Text;
using System.Runtime.InteropServices;

namespace DJKeygoe
{
        using DJ_U8 = Byte;
        using DJ_S8 = SByte;
        using DJ_U16 = UInt16;
        using DJ_S16 = Int16;
        using DJ_U32 = UInt32;
        using DJ_S32 = Int32;
        using DJ_U64 = UInt64;
        using DJ_S64 = Int64;
        using DJ_UI32 = UInt32;
        using DJ_SI32 = Int32;
        using DJ_F64 = Double;
        using RetCode_t = Int32;
        using ACSHandle_t = UInt32;
        using InvokeID_t = Int32;
        using LoginID_t = SByte;
        using EventClass_t = Int32;
        using EventType_t = Int32;
        using ACSConfirmation_t = Int32;
        using CallNum_t = SByte;
        using AcsCmdTye_t = Int32;

        using FlowType_t = Int32;
        using FlowChannel_t = Int32;
        using DeviceMain_t = Int16;
        using DeviceSub_t = Int16;
        using DeviceGroup_t = Int16;
        using ModuleID_t = SByte;
        using ChannelID_t = Int16;
        using ParmName_t = SByte;
        using ParmSize_t = Int32;
        using Version_t = Int32;
        using ACSUniversalFailure_t = Int32;
        using PlayCont_t = SByte;
        using FilePath_t = SByte;

        using Acs_Evt_State_t = Int32;
        using Acs_Evt_ErrCode_t = Int32;
        using Acs_MediaProc_Dtmf_t = SByte;
        using DJ_SOCKET = UInt32;

        public class ConstantVar
        {
            /*Array len*/
            public const DJ_S32  ACS_MAX_CALL_NUM = 32;
            public const DJ_S32  ACS_SIGDATA_MAX_LEN = 300;
            public const DJ_S32  ACS_MAX_IO_SIZE = 2048;
            public const DJ_S32  ACS_LOCALID_MAX_LEN = 20;
            public const DJ_S32  ACS_REMOTEID_MAX_LEN = 20;
            public const DJ_S32  ACS_MAX_DECODER_CFG_LEN = 200;
            public const DJ_S32  XMS_MAX_REGNAME_LEN = 16;
            public const DJ_S32  ACS_MAX_H245_SIG_PDU_LEN = 4000;
            public const DJ_S32  ITP_VOIP_MONDATA_MAX = 1024;
            public const DJ_S32  ACS_MAX_FILE_NAME_LEN = 128;
            public const DJ_S32  ACS_MAX_FILE_NUM = 8;
            public const DJ_S32  MAX_PATH = 260;
            public const DJ_S32  MAX_CAPS_NUM = 4;
            public const DJ_S32  MAX_DECODER_CFG_INFO = 128;
            public const DJ_S32  ACS_SNAPSHOT_ALL = 0x0;
            public const DJ_S32  ACS_SNAPSHOT_INTERFACE = 0x1;
            public const DJ_S32  ACS_SNAPSHOT_VOC = 0x2;
            public const DJ_S32  ACS_SNAPSHOT_CTBUS = 0x3;
            public const DJ_S32  ACS_SNAPSHOT_VOIP = 0x4;
            public const DJ_S32  ACS_SNAPSHOT_CONFERENCE = 0x5;
            public const DJ_S32  ACS_SNAPSHOT_VIDEO = 0x6;
            public const DJ_S32  T6_Encode = 0x2;
            public const DJ_S32  XMS_MAX_PLAY_QUEUE_NUM = 255;
            public const DJ_S32  XMS_MAX_IDNEX_TABLE_NUM = 1024;
            public const DJ_S32  ITP_MAX_STREAM_DATA_LENGTH = 4000;
            public const DJ_S32  SYS_MAX_INFO_LEN = 128;

                /* VoIP Call Slot Access Flag */
            public const DJ_S32 XMS_VOIP_ACCESS_NONE = 0x00;	/* no access */
            public const DJ_S32 XMS_VOIP_ACCESS_H323 = 0x01;	/* h.323 call access */
            public const DJ_S32 XMS_VOIP_ACCESS_SIP = 0x02;	/* sip call access */
            public const DJ_S32 XMS_VOIP_ACCESS_INCOMING = 0x04;	/* incoming call access */
            public const DJ_S32 XMS_VOIP_ACCESS_OUTGOING = 0x08;	/* outgoing call access */
            public const DJ_S32 XMS_VOIP_ACCESS_REGISTRATION = 0x10;	/* registration access */

            public const DJ_S32 COUNTRY_BEGIN = 0x00;	/* no access */
            public const DJ_S32 CHINA = 0x01;	/* h.323 call access */
            public const DJ_S32 KOREA = 0x02;	/* sip call access */
            public const DJ_S32 INDIA = 0x03;	/* incoming call access */
            public const DJ_S32 VIETNAM = 0x04;	/* outgoing call access */
            public const DJ_S32 COUNTRY_END = 0x05;	/* registration access */

            public const DJ_S32 ACS_IOEVT_MASK_ALL = 0xFFFF;	/* registration access */
        };
        /*CallID*/
        public struct CallID_t
        {
            public FlowType_t m_s32FlowType;    /*CallType*/
            public FlowChannel_t m_s32FlowChannel; /*Call Channel*/
        };/*CallID_t*/

        public unsafe struct ServerID_t
        {
            public fixed sbyte m_s8ServerIp[32]; /*XMS server ip*/
            public UInt32 m_u32ServerPort;  /*XMS server port*/
            public fixed sbyte m_s8UserName[32]; /**/
            public fixed sbyte m_s8UserPwd[32];  /**/
        };

    /*Voice param*/
        public unsafe struct CmdParamData_Voice_t
        {
	        public DJ_U8                                    m_u8InputCtrlValid;  /*is VocInputControl_t valid*/
	        public DJ_U8                                    m_u8PlayGainMode;    /*Play gain mode,reference XMS_PLAY_GAIN_MODE*/  
	        public DJ_U16                                  m_u16PlayFixGain;    /*Play fix gain*/ 
	        public VocInputControlParam_t	    m_VocInputControl;   /*valid to voc,not include RTP*/
	        public DJ_U8                                    m_u8OutputCtrlValid; /*is VocOutputControl_t valid*/
	        public fixed DJ_S8                            m_s8Rfu2[3];         /*Rfu*/
	        public VocOutputControlParam_t	    m_VocOutputControl;  /*valid to voc and RTP*/
	        public DJ_U8                                    m_u8GtdCtrlValid;    /*is VocGtdControl_t valid*/
	        public fixed DJ_S8                            m_s8Rfu3[3];         /*Rfu*/
            public VocGtdControlParam_t          m_VocGtdControl;	 /*valid to voc and RTP*/
        };/*CmdParamData_Voice_t*/

        public unsafe struct DeviceID_t
        {
            public DeviceMain_t m_s16DeviceMain;  /*device main type*/
            public DeviceSub_t m_s16DeviceSub;   /*device sub type*/
            public ModuleID_t m_s8ModuleID;     /*device module ID*/
            public DJ_S8 m_s8MachineID;    /*device machine ID*/
            public ChannelID_t m_s16ChannelID;   /*device channel ID*/
            public DeviceGroup_t m_s16DeviceGroup; /*device group ID*/
            public fixed DJ_S8 m_Rfu2[2];        /*Reserved*/
            public CallID_t m_CallID;         /*Serveice ID*/
        };/*DeviceID_t*/

        /*Acs_Evt_t*/
        public struct Acs_Evt_t
        {
            public ACSHandle_t m_s32AcsHandle;       /*acs handle*/
            public DeviceID_t m_DeviceID;           /*Device ID*/
            public DJ_S32 m_s32EvtSize;         /*Evt size*/
            public EventType_t m_s32EventType;       /*event type code*/
            public DJ_U32 m_u32EsrParam;        /*App esr param*/
        };/**/

        /*privatedata*/
        public struct PrivateData_t
        {
            public DJ_U32 m_u32DataSize; /*private data size*/
        };/*PrivateData_t*/

        /* Called Number Table Description */
        public unsafe struct CAS_CalledTableDesc_t
        {
            public DJ_U8 m_u8NumHeadLen;			/* Compared Called Number Head Length */
            public fixed DJ_U8 m_u8NumHead[14];		/* Compared Called Number Head Content */
            public DJ_U8 m_u8NumLen;				/* Total Called Number Length */
        };/**/

        /* CAS Parameter Type Define*/
        public unsafe struct CmdParamData_CAS_t
        {
            public DeviceID_t m_VocDevID;				/* Voice Device ID which is used for MFC, alloced by Application */

            /* Call In Parameter */
            public DJ_U8 m_u8CalledTableCount;	/* Called Table Count ( 0-16:Table Count) */
            public fixed DJ_U8 m_Rfu1[3];              /* Reserved*/

            public fixed DJ_U8 m_CalledTable[16 * sizeof(DJ_U8) * 16];
            //public CAS_CalledTableDesc_t[] m_CalledTable = new CAS_CalledTableDesc_t[16];		/*CAS_CalledTableDesc_t m_CalledTable[16]  Max 16 items */
            public DJ_U8 m_u8CalledLen;			/* Called Number Length (0:Variable, Other:Length) */

            public DJ_U8 m_u8CalledTimeOut;		/* Time Out Seconds when Receive MFC */

            public DJ_U8 m_u8NeedCaller;			/* Is Need Caller Number ( 1:Yes, 0:No ) */
            public DJ_U8 m_u8AreaCodeLen;		/* Area Code Length when receive Called Number, Used for Receive Caller Number */

            /* Call Out Parameter */
            public DJ_U8 m_u8KA;					/* KA ( Default KA = 1 ) */
            public DJ_U8 m_u8KD;					/* KD ( Default KD = 3 ) */

            /* Other */
            public DJ_U8 m_u8ControlMode;		/* Release Control Mode ( 0:None, 1:Caller Control, 2:Called Control ) */
            public DJ_U8 m_u8CountryCode;
            public DJ_U8 m_u8CallType;
            public DJ_U8 m_u8AppendCallee;
            public fixed DJ_U8 m_u8Rfu[6];
            //public DJ_U8 []m_u8Rfu = new DJ_U8[6];				/* Reserved for Future Use */
        };/*CmdParamData_CAS_t*/

        /*AnalogTrunk Parameter Define*/
        public struct CmdParamData_AnalogTrunk_t
        {
            //CallIn Paramteter
            public DJ_U16 m_u16CallInRingCount; //ring count before CallIn event
            public DJ_U16 m_u16CallInRingTimeOut;//Unit:ms Ring TimeOut,when ring timed out ,state changed to DCS_Free
        };/*CmdParamData_AnalogTrunk_t*/

        /*AnalogUser Parameter Define*/
        public unsafe struct CmdParamData_AnalogUser_t
        {
            // Call Out Parameter 
            public DJ_U8 m_u8CallerIdOption;//0:disabled; 1:Fsk CallerId; 2:DTMF CallerId;,reference XMS_ANALOG_USER_CALLERID_OPT
            public DJ_U8 m_u8RingCadenceType;//0: single-pulse ring; 1:double-pulse ring; 2: triple-pulse ring
            public DJ_U8 m_u8CallOutRingTimeOut;// unit: second ; Ringing TimeOut ,it timetout ,then state return to DCS_FREE
            public DJ_U8 m_u8Rfu1;
            public fixed DJ_U8 m_u8Rfu2[12];
        };/*CmdParamData_AnalogUser_t*/

        /*Acs_MediaProc_Data*/
        public unsafe struct Acs_MediaProc_Data
        {
            public Acs_Evt_State_t m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
            public Acs_Evt_ErrCode_t m_s32AcsEvtErrCode;  /*acs event errcode ,reference XMS_MEDIA_ERR_CODE*/
            public DJ_U8 m_u8TaskID;          /*play Task ID*/
            public DJ_U8 m_u8GTD;             /*GTD ID*/
            public fixed DJ_S8 m_s8Rfu[2];
            public DJ_U32 m_u32CurFileIndex;   /*current play file index*/
            public DJ_U32 m_u32CurFilePos;     /*current play pos*/
            public PrivateData_t m_PrivData;          /*private data*/
        };/**/

        /*Acs_Dev_List_Head_t*/
        public struct Acs_Dev_List_Head_t
        {
            public DJ_S32 m_s32DeviceMain;   /*device Main*/
            public DJ_S32 m_s32ModuleID;     /*Device Module ID*/
            public DJ_S32 m_s32DeviceNum;    /*device num*/
        };/**/

        /*Acs unifail event*/
        public struct Acs_UniFailure_Data
        {
            public Acs_Evt_State_t m_s32AcsEvtState;   /*acs event state, -1*/
            public Acs_Evt_ErrCode_t m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
        };/**/

        public struct CmdParamData_GtdFreq_t
        {
            public DJ_U16 m_u16Freq_Index;  /* Frequence index: 0-15*/
            public DJ_U16 m_u16Freq_Coef;   /* Frequence*/
        };/*CmdParamData_GtdFreq_t*/

        public struct CmdParamData_GtdProtoType_t
        {
            public DJ_U16 m_u16GtdID;
            public DJ_U16 m_u16Freq_Mask;
            public DJ_U16 m_u16Amp_Threshold;
            public DJ_U16 m_u16Envelope_Mode;
            public DJ_U16 m_u16Repeat_Count;
            public DJ_U16 m_u16Min_On_Time1;
            public DJ_U16 m_u16Max_On_Time1;
            public DJ_U16 m_u16Min_Off_Time1;
            public DJ_U16 m_u16Max_Off_Time1;
            public DJ_U16 m_u16Min_On_Time2;
            public DJ_U16 m_u16Max_On_Time2;
            public DJ_U16 m_u16Min_Off_Time2;
            public DJ_U16 m_u16Max_Off_Time2;
        };/*CmdParamData_GtdProtoType_t*/

        /* Acs VoIP H.245 UserInputIndication struct */
        public struct CmdParamData_GtgFreq_t
        {
            public DJ_U16 m_u16Freq_Index;  /* Frequence index: 0-15*/
            public DJ_U16 m_u16Freq_Coef;   /* Frequence*/
        };/*CmdParamData_GtgFreq_t*/

        //---This Struct according to ITP_GTG_Template(DSP_PACKET_DEF.H)
        public struct CmdParamData_GtgProtoType_t
        {
            public DJ_U8 m_u8GTG_id;	        /*影射GTG ID，有效值0x30-0x3F*/
            public DJ_U8 m_u8Reserved1;		/*保留*/
            public DJ_U16 m_u16Reserved2;		/*保留*/

            //-------ITP_GTG_Prototype--------
            public DJ_U8 m_u8Freq1_Index;
            public DJ_U8 m_u8Freq2_Index;
            public DJ_U16 m_u16Freq1_Amp;
            public DJ_U16 m_u16Freq2_Amp;
            public DJ_U16 m_u16Envelope_Mode;
            public DJ_U16 m_u16Repeat_Count;
            public DJ_U16 m_u16On_Time1;
            public DJ_U16 m_u16Off_Time1;
            public DJ_U16 m_u16On_Time2;
            public DJ_U16 m_u16Off_Time2;
            public DJ_U16 m_u16Reserved;		/*保留*/
        };/*CmdParamData_GtgProtoType_t*/

        /*ACS control record */
        public struct ControlRecord_t
        {
            public DJ_U32 m_u32ControlType;  /*control record type,reference XMS_CTRL_RECORD_TYPE*/
            public DJ_U32 m_u32StepSize;     /*step size*/
            public DJ_U32 m_u32SpeedSize;    /*speed size,reserved*/
        };/*ControlRecord_t*/

        /*Acs_CallControl_Data*/
        public unsafe struct Acs_CallControl_Data
        {
            public Acs_Evt_State_t m_s32AcsEvtState;                 /*acs event state, 1: success; 0: failed*/
            public Acs_Evt_ErrCode_t m_s32AcsEvtErrCode;               /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
            public DJ_S32 m_s32CallClearCause;              /*Call clear cause code*/
            public DJ_U8 m_u8CallingCategory;              /*Calling Category*/
            public DJ_U8 m_u8CallingAddressIndicator;      /*Address Indicator*/
            public DJ_U8 m_u8CalledAddressIndicator;       /*Address Indicator*/
            public fixed DJ_S8 m_s8Rfu1[1];
            public fixed CallNum_t m_s8CallingNum[ConstantVar.ACS_MAX_CALL_NUM]; /*calling num*/
            public fixed CallNum_t m_s8CalledNum[ConstantVar.ACS_MAX_CALL_NUM];  /*called num*/
            public DJ_U8 m_u8DRSCallDirectFlag;            /*Call direction flag, 0: Call In; 1: Call Out, reference XMS_DRS_CALL_DIRECT_DEF*/
            public fixed DJ_S8 m_s8Rfu2[31];
            public PrivateData_t m_PrivData;                       /*private data*/
        };/**/

        /*general proc evt data*/
        public struct Acs_GeneralProc_Data
        {
            public Acs_Evt_State_t m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
            public Acs_Evt_ErrCode_t m_s32AcsEvtErrCode;  /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
            public DJ_S32 m_s32DeviceState;    /*Device State*/
            public DJ_S32 m_s32Resrv;          /*reserved*/
            public PrivateData_t m_PrivData;          /*private data*/
        };/**/

        /*Acs_IO_Data*/
        public struct Acs_IO_Data
        {
            public Acs_Evt_State_t m_s32AcsEvtState;   /*acs event state*/
            public Acs_Evt_ErrCode_t m_s32AcsEvtErrCode; /*acs event errcode*/
            public DJ_U16 m_u16IoType;     /*io proc type*/
            public DJ_U16 m_u16IoDataLen;  /*io data len*/
        };/**/

        /*VOC input control param*/
        public struct VocInputControlParam_t
        {
            public DJ_U8 m_u8AgcEnable;       /*0:disable;1:enable*/
            public DJ_U8 m_u8AgcMode;         /*0:ALS mode; 1:AGC mode,reference XMS_AGC_MODE*/
            public DJ_U8 m_u8EcEnable;        /*0:disable;1:enable*/
            public DJ_U8 m_u8EcRefType;       /*0:ref from input;1:ref from output*/
            public DJ_U8 m_u8VadEnable;       /*0:disable;1:enable*/
            public DJ_U8 m_u8TadEnable;       /*0:disable;1:enable*/
            public DJ_U8 m_u8NrEnable;        /*0:disable;1:enable*/
            public DJ_U8 m_u8Reserved;        /*Rfu*/
            public DJ_U16 m_u16FixGain;       /*0x400 = 0dB*/
            public DJ_U16 m_u16EcRefCh;       /*Rfu*/
            public DJ_U32 m_u32Reserved;      /*Rfu*/
        };/*VocInputControl_t*/

        /*混音通道属性*/
        public struct MixerControlParam_t
        {
            public DJ_U8 m_u8SRC1_Ctrl;  /*reference XMS_MIXER_TYPE*/
            public DJ_U8 m_u8SRC2_Ctrl;  /*reference XMS_MIXER_TYPE*/
            public DJ_U16 m_u16SRC_ChID1; /*Media ChID1*/
            public DJ_U16 m_u16SRC_ChID2; /*Media ChID2*/
            public DJ_U8 m_u8Video;
            public DJ_S8 m_s8Rfu;     /*Rfu*/
        };/*MixerControl_t*/

        /*VOC ouput control param*/
        public unsafe struct VocOutputControlParam_t
        {
            public DJ_U8 m_u8AgcEnable;	  /*0:disable;1:enable*/
            public DJ_U8 m_u8AgcMode;	  /*0:ALS mode; 1:AGC mode*/
            public DJ_U8 m_u8OutputType;  /*0:silence;1:from input;2:from play;3:from mixer,control by m_MixerControl,Reference XMS_VOC_OUTPUT_TYPE*/
            public fixed DJ_U8 m_u8Reserved[1]; /**/
            public DJ_U16 m_u16FixGain;	  /*0x400 = 0dB*/
            public fixed DJ_S8 m_s8Rfu[2];      /*Rfu*/
            public MixerControlParam_t m_MixerControl;  /**/
        };/*VocOutputControl_t*/

        /*VOC GTD control param*/
        public unsafe struct VocGtdControlParam_t
        {
            public DJ_U8 m_u8ChannelEnable; /*0: all disable; 1: control by next params*/
            public DJ_U8 m_u8DTMFEnable;	   /*0:disable;1:enable*/
            public DJ_U8 m_u8MR2FEnable;	   /*0:disable;1:enable*/
            public DJ_U8 m_u8MR2BEnable;	   /*0:disable;1:enable*/
            public DJ_U8 m_u8GTDEnable;	   /*0:disable;1:enable*/
            public DJ_U8 m_u8FSKEnable;	   /*0:disable;1:enable*/
            public DJ_U8 m_u8EXTEnable;     /*0 bit: DPD, 1 bit: PVD, 2 bit: MSK reference to EXT_ENABLE_TYPE public enum*/
            public DJ_U8 m_u8Reserved;      /*rfu*/
            public fixed DJ_U8 m_u8GTDID[8];      /**/
        };/*VocGtdControl_t*/

        /*ACS playpropetry*/
        public unsafe struct PlayProperty_t
        {
            public DJ_U8 m_u8TaskID;         /*play task ID*/
            public DJ_U8 m_u8SrcMode;        /*file src mode, reference XMS_VOC_SRC_MODE*/
            public DJ_U8 m_u8DecodeType;     /*decode type, reference XMS_VOC_CODE_TYPE*/
            public fixed DJ_S8 m_s8Rfu1[1];        /*Reserved*/
            public DJ_U32 m_u32MaxSize;       /*play max size(BYTES),  0: file real size; >0: max play size*/
            public DJ_U32 m_u32MaxTime;       /*play max time(Seconds) 0: file real seconds; >0: max play seconds*/
            public DJ_U32 m_u32StopMode;      /*stop play mode,referecne XMS_PLAYREC_STOP_MODE*/
            public DJ_U32 m_u32StopCode;      /*stop play when receive this dtmf code*/
            public DJ_U16 m_u16FileOffset;    /*start play at the file offset*/
            public DJ_U16 m_u16PlayType;      /*play type: 0-normal,1-index,referecnce XMS_PLAY_TYPE*/
            public DJ_U16 m_u16PlayIndex;     /**/
            public fixed DJ_S8 m_s8PlayContent[ConstantVar.ACS_MAX_FILE_NAME_LEN];/*play file name */
            public DJ_U16 m_u16FileSubOffset; /*start play at the offset from m_u16FileOffset, and the granularity is 1 bytes, fileOffSet = m_u16FileOffset*8K + m_u16FileSubOffset*/
        };/*PlayProperty_t*/

        /*control play */
        public struct ControlPlay_t
        {
            public DJ_U16 m_u16ControlType;  /*play control type,reference XMS_CTRL_PLAY_TYPE*/
            public DJ_U16 m_u16StepSize;     /*play step size*/
            public DJ_U16 m_u16TuneType;     /*tune type,reserved*/
            public DJ_U16 m_u16SpeedSize;    /*speed size,reserved*/
        };/*ControlPlay_t*/

        /*ACS record file propetry*/
        public unsafe struct RecordProperty_t
        {
            public DJ_U32 m_u32MaxSize;    /* record max size, 0: no limit file size; >0: record max size*/
            public DJ_U32 m_u32MaxTime;    /* record max time, 0: no limit record time; >0: record max time*/
            public DJ_U8 m_u8EncodeType;  /* encode type, reference XMS_VOC_CODE_TYPE*/
            public DJ_U8 m_u8SRCMode;     /*file src mode, reference XMS_VOC_SRC_MODE*/
            public DJ_U8 m_u8StopMode;    /*stop record mode,referecne XMS_PLAYREC_STOP_MODE*/
            public DJ_U8 m_u8StopCode;	   /*stop record when receive this dtmf code*/
            public DJ_S8 m_s8IsMixEnable; /*is Mix*/
            public DJ_U8 m_u8TaskID;      /*change from Reserved to m_u8TaskID on 090112*/
            public MixerControlParam_t m_MixerControl;  /*Mixer Contronl parameter*/
            public DJ_S8 m_s8IsAppend;    /*0: trunc record file; 1: append record file,reference XMS_REC_OPENFILE_TYPE*/
            public fixed FilePath_t m_s8FileName[ConstantVar.MAX_PATH];/*record file name*/
            public fixed DJ_S8 m_s8Rfu2[1];      /*Reserved*/
        };/*RecordProperty_t*/

        /*ACS_Conf_Param*/
        public unsafe struct CmdParamData_Conf_t
        {
            public DJ_U8 m_u8InputOpt;	 /*conf input option, reference XMS_CONF_INPUT_OPT*/
            public DJ_U8 m_u8OutputOpt;	 /*conf output option, reference XMS_CONF_OUTPUT_OPT*/
            public fixed DJ_U8 m_u8Rfu[2];      /*Rfu*/
        };/*CmdParamData_Conf_t*/

        /*CSPPlayDataInfo_t*/
        public struct CSPPlayDataInfo_t
        {
            public DJ_U16 m_u16DataLen;   		/*data length*/
            public DJ_U8 m_u8DataType;		    /*data type,0: voc,1:video,reference XMS_CSPPLAY_DATA_TYPE*/
            public DJ_U8 m_u8TaskID;	  		    /*task id*/
        };/*CSPPlayDataInfo_t*/

        /*ACS record Ram propetry*/
        public unsafe struct RecordCSPProperty_t
        {
            public DJ_U8 m_u8EncodeType;  /* encode type, reference XMS_VOC_CODE_TYPE*/
            public DJ_U8 m_u8SRCMode;     /*file src mode, reference XMS_VOC_SRC_MODE*/
            public DJ_U16 m_u16PacketLen;  /*Record Packet Length*/
            public DJ_U8 m_u8CSPRecType;  /*1: barge-in, 2: non barge-in, reference XMS_CSPREC_TYPE*/
            public fixed DJ_S8 m_s8Rfu1[3];
        };/*RecordCSPProperty_t*/

        /*ACS play3gpppropetry*/
        public unsafe struct Play3gppProperty_t
        {
            public DJ_U8 m_u8TaskID;              /*audio: play task ID*/
            public DJ_U8 m_u8SrcMode;             /*audio: file src mode, reference XMS_VOC_SRC_MODE*/
            public DJ_U8 m_u8DecodeType;          /*audio: decode type, reference XMS_VOC_CODE_TYPE*/
            public DJ_S8 m_u8Audio_tracks;        /*audio: audio tracks*/
            public DJ_S8 m_u8AmrFrameType;        /*audio: amr frame type*/
            public DJ_U8 m_u8AudioNoDecode;       /*audio: FALSE: AMR to line-decodetype(default value); TRUE: No decode;*/
            public fixed DJ_U8 m_u8Rfu1[2];             /*reserved*/
            public DJ_U32 m_u32MaxTime;            /*audio: play max time(Seconds) 0: file real seconds; >0: max play seconds*/
            public DJ_U32 m_u32StopMode;           /*audio: stop play mode,referecne XMS_PLAYREC_STOP_MODE*/
            public DJ_U32 m_u32StopCode;           /*audio: stop play when receive this dtmf code*/
            public DJ_U16 m_u16TimeOffset;         /*audio: start play at the file offset with time*/
            public DJ_U16 m_u16PlayType;           /*audio: play type: 0-normal,1-index,referecnce XMS_PLAY_TYPE*/
            public DJ_U16 m_u16PlayIndex;          /*audio: play index*/
            public DJ_S16 m_s16Rfu2;               /*Reserved*/
            public fixed DJ_S8 m_s8PlayContent[ConstantVar.ACS_MAX_FILE_NAME_LEN];/*audio: play file name */
            public DJ_U8 m_u8VideoFrameRate;      /*video frame rate*/
            public DJ_U8 m_u8VideoDecode_Type;    /*video: video decode type*/
            public DJ_U8 m_u8VideoHigh;           /*video: video high*/
            public DJ_U8 m_u8VideoWidth;          /*video: video width*/
            public DJ_U32 m_u32VideoMaxTime;       /*video: play max time(Seconds) 0: file real seconds; >0: max play seconds*/
            public DJ_U16 m_u16VideoTimeOffset;    /*video: start play at the file offset with time*/
            public DJ_U16 m_u16VideoPlayType;      /*video: play type: 0-normal,1-index,referecnce XMS_PLAY_TYPE*/
            public DJ_U16 m_u16VideoPlayIndex;     /*video: play index*/
            public DJ_U8 m_u8VideoTaskID;         /*video: play video task ID*/
            public DJ_U8 m_u8MediaType;           /*common: media type XMS_MEDIA_TYPE*/
            public fixed DJ_S8 m_s8VideoPlayContent[ConstantVar.ACS_MAX_FILE_NAME_LEN];/*video: play file name */

        };/*PlayProperty_3gp_t*/

        /*control 3gpp play */
        public unsafe struct Control3gppPlay_t
        {
            public DJ_U16 m_u16ControlType;  /*play control type,reference XMS_CTRL_PLAY_TYPE*/
            public DJ_U16 m_u16StepTime;     /*play step time*/
            public DJ_U16 m_u16TuneType;     /*tune type,reserved*/
            public DJ_U16 m_u16SpeedSize;    /*speed size,reserved*/
            public DJ_U8 m_u8MediaType;     /*media type: 0: audio; 1: video; 4: A & V*/
            public fixed DJ_U8 m_u8Reserv1[3];    /*reserve*/
        };/*Control3gppPlay_t*/

        /*ACS 3gpp record propetry*/
        public unsafe struct Record3gppProperty_t
        {
            public DJ_U32 m_u32MaxTime;          /*record max time, 0: no limit record time; >0: record max time*/
            public DJ_U8 m_u8StopMode;          /*stop record mode,referecne XMS_PLAYREC_STOP_MODE*/
            public DJ_U8 m_u8StopCode;	         /*stop record when receive this dtmf code*/

            public DJ_S8 m_s8IsAppend;          /*0: trunc record file; 1: append record file,reference XMS_REC_OPENFILE_TYPE*/
            public DJ_U8 m_u8AudioEncodeType;  /*encode type, reference XMS_VOC_CODE_TYPE*/
            public DJ_U8 m_u8AudioSRCMode;     /*file src mode, reference XMS_VOC_SRC_MODE*/
            public DJ_S8 m_u8AudioTracks;      /*audio channel,reference XMS_AUDIO_TRACKS*/
            public DJ_U16 m_u16AudioMaxBitRate; /*audio max bitrate,0~65535*/
            public DJ_U16 m_u16AudioAverageBitRate;/*audio average bitrate,0~65535*/
            public fixed DJ_S8 m_Rfu1[1];
            public DJ_S8 m_s8AudioIsMixEnable; /*is Mix, 0 : no mix,1: mix*/
            public MixerControlParam_t m_AudioMixerControl;  /*Mixer Contronl parameter*/

            public DJ_U8 m_u8VideoEncodeType;  /*encode type, reference XMS_VIDEO_CODE_TYPE*/
            public DJ_U8 m_u8VideoFrameRate;   /*video frame rate,10~30*/
            public DJ_U16 m_u16VideoWidth;      /*video width,176*/
            public DJ_U16 m_u16VideoHeight;     /*video heigth,144*/
            public DJ_U16 m_u16VideoMaxBitRate; /*video max bit rate,0~65535*/
            public DJ_U16 m_u16VideoAverageBitRate;/*video average bit rate,0~65535*/
            public DJ_U8 m_Rfu2;
            public DJ_S8 m_s8VideoIsMixEnable; /*is Mix, 0 : no mix,1: mix*/
            public MixerControlParam_t m_VideoMixerControl;  /*Mixer Contronl parameter*/

            public DJ_U8 m_u8AudioProfiles;    /*audio profiles?*/
            public DJ_U8 m_u8AudioLevel;       /*audio level ?*/
            public DJ_U16 m_u16AudioDecoderCfgLen;/*audio decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
            public fixed DJ_U8 m_u8AudioDecoderCfg[ConstantVar.ACS_MAX_DECODER_CFG_LEN];/*audio decoder cfg*/

            public DJ_U8 m_u8VideoProfiles;    /*video profiles?*/
            public DJ_U8 m_u8VideoLevel;       /*video level?*/
            public DJ_U16 m_u16VideoDecoderCfgLen;  /*video decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
            public fixed DJ_U8 m_u8VideoDecoderCfg[ConstantVar.ACS_MAX_DECODER_CFG_LEN];/*video decoder cfg?*/
            public fixed FilePath_t m_s8FileName[ConstantVar.MAX_PATH];/*record file name*/
        };/*Record3gpProperty_t*/

        /*ACS Get 3GPP file config add by fys*/
        public unsafe struct Get3gppCfg_t
        {
            public DJ_U8 m_u8MediaType;                /*media type: XMS_MEDIA_TYPE*/
            public DJ_U8 m_u8AudioFileType;            /*audio file type: XMS_CFG_TYPE*/
            public DJ_U16 m_u16AudioFileIndex;          /*audio file index: 0~1023*/
            public fixed DJ_S8 m_s8AudioFileName[ConstantVar.MAX_PATH];  /*audio file path and name*/
            public DJ_U8 m_u8VideoFileType;            /*video file type: XMS_CFG_TYPE*/
            public DJ_U8 m_u8Rfu1;                     /*reserve*/
            public DJ_U16 m_u16VideoFileIndex;          /*video file index: 0~1023*/
            public fixed DJ_S8 m_s8VideoFileName[ConstantVar.MAX_PATH];  /*video file path and name*/
        };/*Get3gppCfg_t*/

        /*ACS control 3gpp record */
        public struct Control3gppRecord_t
        {
            public DJ_U32 m_u32ControlType;  /*control record type,reference XMS_CTRL_RECORD_TYPE*/
            public DJ_U32 m_u32StepTime;     /*step time*/
            public DJ_U32 m_u32SpeedSize;    /*speed size,reserved*/
        };/*Control3gpRecord_t*/

        /* Acs MediaEx Video Input Param*/
        public unsafe struct Acs_MediaEx_Input_V
        {
	        public DJ_U16		m_u16Port;				/* local port */
	        public DJ_U8		m_u8Codec;				/* codec type */
	        public DJ_U8		m_u8PayloadType;		/* rtp payload type (if dynamic) */
	        public DJ_U16      m_u32ProfileLevelId;	/* codec extra attribute */
            public DJ_U16      decoderConfigLength;
	        public fixed DJ_U8       decoderConfigInfo[ConstantVar.MAX_DECODER_CFG_INFO];
        };/*Acs_MediaEx_Input_V*/

        /* Acs MediaEx Output Param */
        public unsafe struct Acs_MediaEx_Output_V
        {
	        public fixed DJ_S8		m_s8IP[20];				/* dest address */
	        public DJ_U16		m_u16Port;				/* dest port */
	        public DJ_U8		m_u8Codec;				/* codec type */
	        public DJ_U8		m_u8PayloadType;		/* rtp payload type (if dynamic) */
	        public DJ_U16		m_u16ResX;				/* resolution x */
	        public DJ_U16		m_u16ResY;				/* resolution y */
	        public DJ_U8		m_u8Fps;				/* framerate in fps */
	        public DJ_U16		m_u16Kbps;				/* bitrate in Kbps */
        };/*Acs_MediaEx_Output_V*/

        /*Acs_3GVConf_LayoutList*/
        public unsafe class Acs_3GVConf_LayoutList
        {
            public DeviceID_t[] m_device = new DeviceID_t[16];
        };/*Acs_3GVConf_LayoutList*/

        /*Acs_3GVConf_VisibleList*/
        public unsafe class Acs_3GVConf_VisibleList
        {
            public DeviceID_t[] m_device = new DeviceID_t[16];
        };/*Acs_3GVConf_VisibleList*/

        public unsafe struct CSPPlayProperty_t
        {	
	        public DJ_U8                m_u8TaskID;         /*play task ID*/	
	        public DJ_U8                m_u8SrcMode;        /*file src mode, reference XMS_VOC_SRC_MODE*/
	        public DJ_U8                m_u8DecodeType;     /*decode type, reference XMS_VOC_CODE_TYPE*/	
	        public fixed DJ_S8                m_s8Rfu1[1];        /*Reserved*/
	        public DJ_U32               m_u32MaxSize;       /*play max size(BYTES),  0: file real size; >0: max play size*/
	        public DJ_U32               m_u32MaxTime;       /*play max time(Seconds) 0: file real seconds; >0: max play seconds*/	
	        public DJ_U32               m_u32StopMode;      /*stop play mode,referecne XMS_PLAYREC_STOP_MODE*/
	        public DJ_U32               m_u32StopCode;      /*stop play when receive this dtmf code*/
	        public fixed DJ_S8                m_Rfu1[4];			
        };/*CSPPlayProperty_t*/

        public struct  tagDllCOLOR
        {
            public DJ_U8  m_u8R;
			public DJ_U8  m_u8G;
			public DJ_U8  m_u8B;
        };

        public struct tagDllFONTPARAM
	    {
		    public DJ_F64    m_f64DBSize;		/*Font Size, default set to 20.0*/
		    public DJ_F64    m_f64DBBlank;	/*Bank ratio, default set to 0.5*/
		    public DJ_F64    m_f64DBGap;		/*Gap ratio,default set to 0.1*/
		    public DJ_F64    m_f64DBAngle;	/*Rotate angle(not present)*/
		    public DJ_S32    m_bUnderLine;	/*Add under line(not present)*/
            public tagDllCOLOR strcutColor;
        }
		
        public struct tagDllPOINT
	    {
		    public DJ_S32 x;
		    public DJ_S32 y;
	    };

        public unsafe struct PutTextInPicture_Param
        {
	        public DJ_U8   m_u8PutByType;		/*1:Text; 2:Picture,refer PUT_TEXTINPIC_TYPE*/
	        public DJ_U8   m_u8PutByLevel;		/*Picture level*/
	        public fixed DJ_S8   m_s8PutText[260];	/*Put text string*/
	        public DJ_U16  m_u16FontType;		/*Font type,refer PUT_TEXTINPIC_FONTTYPE*/
            public tagDllFONTPARAM structFontParam;
            public float m_f32Diaphaneity;/*Diaphaneity,default set to 1.0(opacity)*/
            public tagDllPOINT structPoint;
        };

        /*UserEvt_Head_t*/
        public unsafe struct UserEvt_Head_t
        {
            public DJ_U32    m_u32UsrEvtType;     /*User self-define event type*/
	        public DJ_U32    m_u32UsrEvtLen;      /*User self-define event length*/
	        public fixed DJ_S8     m_Rfu1[4];
	        public DJ_U8 * m_pUsrEvtData;       /*User self-define event data*/  
        };/**/

        /*UserLedCtrl*/
        public unsafe struct UserLedCtrl
        {
	        public DJ_U8	m_u8LedTimeEnable;       /*Led ontime & offtime ctrl paramter enable? */	
	        public DJ_S8   m_Rfu1;
	        public DJ_U16	m_u16OnTime;             /*LED ontime: 100~2000 ms*/
	        public DJ_U16	m_u16OffTime;            /*LED offtime: 100~2000 ms*/
	        public DJ_U8   m_u8WatchDogOutEnbale;   /*LED watchdog out time ctrl paramter enable? */
	        public DJ_S8   m_Rfu2;
	        public DJ_U16	m_u16WatchDogOutTime;    /*LED watchdog out time: 10~300 S*/
	        public DJ_U8   m_u8WatchDogTimeEnable;  /*LED watchdog out state ctrl paramter enable? */
	        public DJ_S8   m_Rfu3;
	        public DJ_U16	m_u16WatchDogOnTime;     /*LED watchdog ontime: 100~2000 ms*/
	        public DJ_U16	m_u16WatchDogOffTime;    /*LED watchdog offtime: 100~2000 ms*/
	        public DJ_U8   m_u8FeedWatchDogEnable;  /*LED watchdog feed ? 0: feed not enable, 1: feed*/
	        public fixed DJ_S8   m_Rfu4[3];
        };/*UserLedCtrl*/

        public struct TYPE_ANALOG_GTD_PARAM
        {
            // Freq
            public DJ_U16 m_u16Freq0;
            public DJ_U16 m_u16Freq1;

            // DailTone
            public DJ_U16 m_u16DialTone_FreqIndexMask;
            public DJ_U16 m_u16DialTone_On_Time;

            // RingBackTone
            public DJ_U16 m_u16RingBackTone_FreqIndexMask;
            public DJ_U16 m_u16RingBackTone_On_Time;
            public DJ_U16 m_u16RingBackTone_Off_Time;
            public DJ_U16 m_u16RingBackTone_TimeDeviation;		// in percentage

            // BusyTone0
            public DJ_U16 m_u16BusyTone0_FreqIndexMask;
            public DJ_U16 m_u16BusyTone0_On_Time;
            public DJ_U16 m_u16BusyTone0_Off_Time;
            public DJ_U16 m_u16BusyTone0_TimeDeviation;				// in percentage

            // BusyTone1
            public DJ_U16 m_u16BusyTone1_FreqIndexMask;
            public DJ_U16 m_u16BusyTone1_On_Time;
            public DJ_U16 m_u16BusyTone1_Off_Time;
            public DJ_U16 m_u16BusyTone1_TimeDeviation;				// in percentage

            // BusyTone2
            public DJ_U16 m_u16BusyTone2_FreqIndexMask;
            public DJ_U16 m_u16BusyTone2_On_Time;
            public DJ_U16 m_u16BusyTone2_Off_Time;
            public DJ_U16 m_u16BusyTone2_TimeDeviation;				// in percentage

            // other 
            public DJ_U16 m_u16NoDialToneAfterOffHook;
            public DJ_U16 m_u16Ringback_NoAnswerTime;

            public DJ_U16 m_u16SendFSKCallerIDTime;					// for Analog_User Channel
        } ;

        /*Acs_AnalogMEG_CMD*/
        public struct Acs_AnalogMEG_CMD
        {
	        public DJ_U8	    m_u8Channel_Enable;
	        public DJ_U8 	m_u8CallOut;
	        public DJ_U8	    m_u8RingTime;
	        public DJ_U8	    m_u8Reservered;
        };/*Acs_AnalogMEG_CMD*/

        /*ACS Event Head*/
        public struct ACS_EVT_HEAD
        {
	        public PKG_HEAD_STRUCT  m_PkgEvtHead;  /*ITP package head*/
	        public Acs_Evt_t        m_AcsEvt_t;    /*acs event package head*/
        };/**/

            /*SigMon_t*/
        public unsafe struct SigMon_t
        {
	        public DJ_U8        m_u8MonSigType;     /*singnal type,reference XMS_SIGMON_SIG_TYPE*/
	        public DJ_U8        m_u8MonPackType;    /*Signal Pakcet type,reference XMS_SIGMON_PACK_TYPE*/	
	        public fixed DJ_S8        m_s8Rfu1[6];        /*Rfu*/	
        };/*SigMon_t*/

        /*CmdParamData_RTPXInput_t*/
        public struct CmdParamData_RTPXInput_t
        {
	        public DJ_U8    m_u8ChanEnable;       /*Enable flag, 0: disable; 1: enable*/
	        public DJ_U8    m_u8MediaType;        /*Data type,reference XMS_VOIP_MEDIA_CAPS*/
	        public DJ_U8    m_u8PayloadType;      /*Payload type*/
	        public DJ_U8    m_u8Rfu;              /*reserved*/ 
        };/*CmdParamData_RTPXInput_t*/

        /*CmdParamData_RTPXInput_A_t*/
        public struct CmdParamData_RTPXInput_A_t
        {
	        public DJ_U8    m_u8ChanEnable;       /*Enable flag, 0: disable; 1: enable*/
	        public DJ_U8    m_u8MediaType;        /*Data type,reference XMS_VOIP_MEDIA_CAPS*/
	        public DJ_U8    m_u8PayloadType;      /*Payload type*/
	        public DJ_U8    m_u8Decode;           /*Decode enable flag, 0: disable; 1: enable*/ 
        };/*CmdParamData_RTPXInput_A_t*/
         
        /*CmdParamData_RTPXOutput_t*/
        public struct CmdParamData_RTPXOutput_t
        {
	        public DJ_U8    m_u8ChanEnable;       /*Enable flag, 0: disable; 1: enable*/
	        public DJ_U8    m_u8MediaType;        /*Data type,reference XMS_VOIP_MEDIA_CAPS*/
	        public DJ_U8    m_u8PayloadType;      /*Payload type*/
	        public DJ_U8    m_u8SRC_Ctrl1;        /*Source type,reference XMS_MIXER_TYPE*/
	        public DJ_U16   m_u16SRC_Id1;         /*Source channel ID*/
	        public DJ_U16   m_u16RemotePort;	   /*Remote port*/
	        public  DJ_U32	 m_u32RemoteIP;		   /*Remote IP*/
        };/*CmdParamData_RTPXOutput_t*/

        /*CmdParamData_RTPXOutput_A_t*/
        public struct CmdParamData_RTPXOutput_A_t
        {
	        public DJ_U8    m_u8ChanEnable;       /*Enable flag, 0: disable; 1: enable*/
	        public DJ_U8    m_u8MediaType;        /*Data type,reference XMS_VOIP_MEDIA_CAPS*/
	        public DJ_U8    m_u8PayloadType;      /*Payload type*/
	        public DJ_U8    m_u8Encode;           /*Encode enable flag, 0: disable; 1: enable*/ 
	        public DJ_U8    m_u8SRC_Ctrl1;        /*Source 1 type,reference XMS_MIXER_TYPE*/
	        public DJ_U8    m_u8SRC_Ctrl2;        /*Source 2 type,reference XMS_MIXER_TYPE*/
	        public DJ_U16   m_u16SRC_Id1;         /*Source channel 1 ID*/
	        public DJ_U16   m_u16SRC_Id2;         /*Source channel 2 ID*/
	        public DJ_U16   m_u16RemotePort;	   /*Remote port*/
	        public DJ_U32	 m_u32RemoteIP;		   /*Remote IP*/
        };/*CmdParamData_RTPXOutput_A_t*/

        /*CmdParamData_RTPXAddr_t*/
        public unsafe struct CmdParamData_RTPXAddr_t
        {
	        public DJ_U32	 m_u32RemoteIP;		   /*Remote IP*/
	        public DJ_U16   m_u16RemotePort;	   /*Remote port*/
	        public fixed DJ_U8	 m_u8Rfu[2];		   /*Reserved*/
        };/*CmdParamData_RTPXOutput_t*/

        /*ACS CSP record private parma*/
        public unsafe struct CSPRecordPrivate_t
        {
	        public PrivateData_t   m_PrivateData;         /*privatedata head*/ 
            public DJ_U8               m_u8CspRecPrivType;    /*directly send cmd to dsp,0:no,1:yes,reference XMS_CSPREC_PRIV_TYPE*/
	        public DJ_U8               m_u8CmdDirect;         /*directly send cmd to dsp,0:no,1:yes,reference XMS_CSPREC_CMD_OPT*/
	        public fixed DJ_S8       m_s8Rfu1[2];
        };/**/

        /*ACS CSP control record private parma*/
        public unsafe struct ControlCSPRecordPrivate_t
        {
	        public PrivateData_t   m_PrivateData;                  /*privatedata head*/ 
            public DJ_U8               m_u8CtrlCspRecPrivType;         /*directly send cmd to dsp,0:no,1:yes,reference XMS_CONTROL_CSPREC_PRIV_TYPE*/
	        public DJ_U8               m_u8CmdDirect;                  /*directly send cmd to dsp,0:no,1:yes,reference XMS_CONTROL_CSPREC_CMD_OPT*/
	        public fixed DJ_S8       m_s8Rfu1[2];
        }/**/

        /*ACS answer call private param*/
        public struct AnswerCallPrivate_t
        {
	        public PrivateData_t   m_PrivateData;         /*privatedata head*/ 
	        public DJ_S32             m_s32AnswerType;       /*answer type*/
        };/*AnswerCallPrivate_t*/

        /*ACS Fax private param*/
        public unsafe struct FaxPrivate_t
        {
	        public PrivateData_t   m_PrivateData;         /*privatedata head*/ 
	        public DeviceID_t        m_VoIPDevice;          /*VoIP device ID*/
	        public DJ_U8               m_u8WorkMode;          /*Fax work mode,reference XMS_FAX_WORKMODE*/
	        public fixed DJ_S8       m_s8Rfu1[3];           /*Rfu */
        };/*FaxPrivate_t*/

        /*Acs_TransAddHeader*/
        public unsafe struct Acs_TransAddHeader
        {
            public DJ_U32  m_u32Op;		               /*set param type, 0: clear old config, 
	                                                 1: set new config, reference to 
	                                                 XMS_FAX_PAGE_HEADER_TYPE*/
            public DJ_U16  m_u16XPos;		               /*the x of picture position,*/
            public DJ_U16  m_u16YPos;                     /*the y of picture position,*/
            public fixed DJ_S8   m_u8Data[73];                  /*define by user for fax picture*/
            public DJ_S8   m_u8Rsrv;
            public DJ_U32  m_u32FontSize;
            public DJ_U32  m_u32Header;
        };/*Acs_TransAddHeader*/

        /*Acs_TransAddHeaderEx*/
        public unsafe struct Acs_TransAddHeaderEx
        {
            public DJ_U32  m_u32Op;		               /*set param type, 0: clear old config, 
	                                                 1: set new config, reference to 
	                                                 XMS_FAX_PAGE_HEADER_TYPE*/
            public DJ_U16  m_u16XPos;		               /*the x of picture position,*/
            public DJ_U16  m_u16YPos;                     /*the y of picture position,*/
            public DJ_U32  m_u32FontSize;                 /* 1-7 */
            public fixed DJ_S8   m_u8Data[73];                  /*define by user for fax picture*/
        };/*Acs_TransAddHeaderEx*/

        /*Acs_TransAddFile*/
        public unsafe struct Acs_TransAddFile
        {
            public DJ_U32  m_u32Op;			           /*Send Multi File param type, 
	                                                 0: clear file queue, 2: add 
	                                                 a new file to file queue, 
											         reference to XMS_FAX_M_FILE_TYPE*/
            public fixed DJ_S8   m_strFileName[256];            /*the file name of need to be sent in a fax*/
        };/*Acs_TransAddFile*/

        /*Acs_SetECM*/
        public struct Acs_SetECM
        {
            public DJ_U8 m_u8FaxECMMode;			       /*fac type, 0: normal; 1: Ecm, reference to XMS_FAX_ECM_MODE_TYPE*/
        };/*Acs_SetECM*/

        /*Acs_SetFaxBps*/
        public struct Acs_SetFaxBps
        {
            public DJ_U8   m_u8BPS;                       /*fax transfor speed, referece to XMS_FAX_BPS_TYPE*/			    
        };/*Acs_SetFaxBps*/

        /*ACS VoIP Call private param*/
        public unsafe struct VoIPCallPrivate_t
        {
	        public PrivateData_t        m_PrivateData;         /*privatedata head*/ 
	        public DJ_S32                  m_s32Protocol;         /*protocol type*/
	        public fixed DJ_S8           m_s8CallerAddress[20]; /*Caller Address*/
	        public DJ_S32                  m_s32CallerPort;       /*Caller Port*/
	        public fixed DJ_S8           m_s8CallerUserID[40];  /*Caller UserID*/		
	        public fixed DJ_S8           m_s8CalleeAddress[20]; /*Callee Address*/
	        public DJ_S32                 m_s32CalleePort;       /*Callee Port*/
	        public fixed DJ_S8           m_s8CalleeUserID[40];  /*Callee UserID*/		
	        public DJ_U8                   m_u8MediaCapNum;       /*media capability number*/
	        public fixed DJ_U8           m_u8MediaCapList[10];  /*media capability list*/
        };/*VoIPCallPrivate_t*/

        /*ACS VoIP Call private param*/
        public unsafe struct VoIPCallPrivateEx_t
        {
	        public PrivateData_t        m_PrivateData;         /*privatedata head*/ 
	        public DJ_S32                   m_s32Protocol;         /*protocol type*/
	        public fixed DJ_S8           m_s8CallerAddress[20]; /*Caller Address*/
	        public DJ_S32                   m_s32CallerPort;       /*Caller Port*/
	        public fixed DJ_S8           m_s8CallerUserID[40];  /*Caller UserID*/		
	        public fixed DJ_S8           m_s8CalleeAddress[20]; /*Callee Address*/
	        public DJ_S32                   m_s32CalleePort;       /*Callee Port*/
	        public fixed DJ_S8           m_s8CalleeUserID[40];  /*Callee UserID*/		
	        public DJ_U8                    m_u8MediaCapNum;       /*media capability number*/
	        public fixed DJ_U8           m_u8MediaCapList[10];  /*media capability list*/
	        public DJ_U8			            u8MediaMode;			// media mode 0:noset(sendrecv) 1:sendonly 2:recvonly 3:sendrecv
        };/*VoIPCallPrivate_t*/

        /*ACS Voip Open private param*/
        public struct VoIPOpenPrivate_t
        {
	        public PrivateData_t 	m_PrivateData;		/*privatedata head*/
	        public DJ_U8		m_u8RtpMode;		/*RTP Mode:0-default auto,1-user control*/
        };/*VoIPOpenPrivate_t*/

        /*ACS VoIP Forward Call param*/
        public unsafe struct VoIPForwardCallPrivate_t
        {
	        public PrivateData_t       m_PrivateData;         /*privatedata head*/ 
	        public DJ_S32                 m_s32Protocol;         /*protocol type*/
	        public fixed DJ_S8           m_s8CallerAddress[20]; /*Caller Address*/
	        public DJ_S32                 m_s32CallerPort;       /*Caller Port*/
	        public fixed DJ_S8           m_s8CallerUserID[40];  /*Caller UserID*/		
	        public fixed DJ_S8		   m_s8TelNo[20];	       /*telephone number*/
        };/*VoIPForwardCallPrivate_t*/

        /*ACS VoIP Alert private param*/
        public unsafe struct VoIPAlertPrivate_t
        {
	        public PrivateData_t        m_PrivateData;         /*privatedata head*/ 
	        public DJ_U8                    m_u8MediaCapNum;       /*media capability number*/
	        public fixed DJ_U8           m_u8MediaCapList[10];  /*media capability list*/
        };/*VoIPAlertPrivate_t*/

        /*ACS VoIP Alert private param*/
        public unsafe struct VoIPAlertPrivateEx_t
        {
	        public PrivateData_t   m_PrivateData;         /*privatedata head*/ 
	        public DJ_U8               m_u8MediaCapNum;       /*media capability number*/
	        public fixed DJ_U8      m_u8MediaCapList[10];  /*media capability list*/
	        public DJ_U16			  u16AlertCode;			// alert code for sip, support 180,181,182,183, default is 183
        };/*VoIPAlertPrivate_t*/

        /*ACS VoIP Answer private param*/
        public unsafe struct VoIPAnswerPrivate_t
        {
	        public PrivateData_t   m_PrivateData;         /*privatedata head*/ 
	        public DJ_U8               m_u8MediaCapNum;       /*media capability number*/
	        public fixed DJ_U8       m_u8MediaCapList[10];  /*media capability list*/
        };/*VoIPAnswerPrivate_t*/

    public struct VoIP_RTP_Format_t
		{
			public DJ_U8		u8CodecType;		/* codec type */
			public DJ_U8		u8PayloadType;		/* payload type */
		};/*VoIP_RTP_Format_t*/
				
        public struct VoIP_RTP_Session_t
		{
			public DJ_U32			u32IP;				/* remote rtp address */
			public DJ_U16			u16Port;			/* remote rtp port */
			public VoIP_RTP_Format_t tx;
			public VoIP_RTP_Format_t rx;
		};/*VoIP_RTP_Session_t*/
			
		public struct VoIPConnectPrivate_t
		{
			public PrivateData_t   m_PrivateData;			/*privatedata head*/ 
			public VoIP_RTP_Session_t audio;
			public VoIP_RTP_Session_t video;
		};/*VoIPConnectPrivate_t*/

        public struct ChCodec
		{
			public DJ_U8	m_u8Enable;				/* enable flag */
			public DJ_U8	m_u8TxCodec;			/* tx codec */
			public DJ_U8	m_u8TxPayloadType;		/* tx payload type (if dynamical) */
			public DJ_U8	m_u8RxCodec;			/* rx codec */
			public DJ_U8	m_u8RxPayloadType;		/* rx payload type (if dynamical) */
		};/*ChCodec*/
			
		/* Acs VoIP RTP Codec struct */
		public struct Acs_VoIP_RTPCODEC
		{
			public ChCodec audio;
			public ChCodec video;
		};/*Acs_VoIP_RTPCODEC*/

        public unsafe struct ChMedia
        {
			public DJ_U8	m_u8Enable;			/* enable flag */
			public fixed DJ_S8	m_s8IP[20];			/* ip address */
			public DJ_U16	m_u16Port;			/* port */
			public DJ_U8	m_u8TxCodec;			/* tx codec */
			public DJ_U8	m_u8TxPayloadType;		/* tx payload type (if dynamical) */
			public DJ_U8	m_u8RxCodec;			/* rx codec */
			public DJ_U8	m_u8RxPayloadType;		/* rx payload type (if dynamical) */	
        };/*ChMedia*/
    
		/* Acs Voip RTP Open struct */
		public struct Acs_VoIP_RTPOpen
		{
		    public DJ_U8	m_u8Enable;				/* enable/disable rtp session */
		    public DJ_U8	m_u8PayloadDtmf;		/* dynamic payload type for rtp dtmf */
		    public DJ_U8	m_u8PayloadTone;		/* dynamic payload type for rtp tone */	
		    public ChMedia audio;
		    public ChMedia video;	
		};/*AcsVoIP_RTPOpen*/

        public unsafe struct Acs_VoIP_MediaInfo
		{
		    public DJ_U8   payload_dtmf;
		    public DJ_U8   payload_tone;
		    public DJ_U8   u8AudioEnabled;
		    public fixed DJ_S8   s8AudioAddress[20];			// host address
		    public DJ_U16  u16AudioPort;			// port number
		    public DJ_U8   u8VideoEnabled;
		    public fixed DJ_S8   s8VideoAddress[20];			// host address
		    public DJ_U16  u16VideoPort;			// port number
		    public DJ_U8   u8MediaCapNum;                      // media capability number
		    public fixed DJ_U8   u8MediaCapList[10];                 // media capability list
		};/*Acs_VoIP_MediaInfo*/

        public unsafe struct ChAddr
        {
			    public DJ_U8	m_u8Enable;			/* enable flag */
			    public fixed DJ_S8	m_s8IP[20];			/* ip address */
			    public DJ_U16	m_u16Port;			/* port */
        };/*ChAddr*/
		    
		/* Acs VoIP RTP Address struct */
		public struct Acs_VoIP_RTPADDR
		{
		  public ChAddr audio;
		  public ChAddr video;
		};/*Acs_VoIP_RTPADDR*/

        /* Acs VoIP RTP Session struct */
        public struct Acs_VoIP_RTPSESSION
        {
	        public DJ_U8	    m_u8Enable;				/* enable/disable rtp session */
	        public DJ_U8	    m_u8PayloadDtmf;		/* dynamic payload type for rtp dtmf */
	        public DJ_U8	    m_u8PayloadTone;		/* dynamic payload type for rtp tone */
        };/*Acs_VoIP_RTPSESSION*/

        public struct VoIPDummyPrivate_t
        {
	        public PrivateData_t   m_PrivateData;			/*privatedata head*/ 
        };

        /* Acs VoIP Registration State struct */
        public unsafe struct Acs_VoIP_REGSTATE
        {
	        public DJ_U16	m_u16SlotID;			/* Registration Slot ID */
	        public DJ_U8	m_u8Protocol;			/* VoIP Protocol */
	        public DJ_U8	m_u8State;				/* Registration State */
	        public fixed DJ_S8	m_s8TelNo[20];			/* Client Telephone-subscriber */
	        public fixed DJ_S8	m_s8Address[20];		/* Client Address */
	        public DJ_U16	m_u16Port;				/* Client Port */
	        public fixed DJ_S8	m_s8UserID[40];			/* Client UserID */
        };/*Acs_VoIP_REGISTRATION*/

        /* Acs_VoIP_Regist Struct */
        public unsafe struct Acs_VoIP_Regist
        {
	        public DJ_U16	m_u16SlotID;			/* Registration Slot ID */
	        public DJ_U8	m_u8Protocol;			/* VoIP Protocol */
	        public DJ_U8	m_u8State;			/* Registration State */
	        public fixed DJ_S8	m_s8TelNo[20];			/* Client Telephone-subscriber */
	        public fixed DJ_S8	m_s8Address[20];		/* Client Address */
	        public DJ_U16	m_u16Port;			/* Client Port */
	        public fixed DJ_S8	m_s8UserID[40];			/* Client UserID */	
        };/*Acs_VoIP_Regist*/

        /* Acs_VoIP_Regist_Response struct */
        public unsafe struct Acs_VoIP_Regist_Response
        {
            public DJ_U8	m_u8State;		/* Registration State */    
            public fixed DJ_S8	m_s8TelNo[20];	    	/* subscriber number */
            public fixed DJ_S8	m_s8Username[40];	/* username for authorization */
        };/*Acs_VoIP_Regist_Response*/

        /* Acs VoIP Refer struct */
        public unsafe struct Acs_VoIP_Refer
        {
	        public DJ_U8	m_u8Protocol;			/* VoIP Protocol */
	        public DJ_U8	m_u8State;				/* Registration State */
	        public fixed DJ_S8	m_s8TelNo[20];			/* Client Telephone-subscriber */
	        public fixed DJ_S8	m_s8Address[20];		/* Client Address */
	        public DJ_U16	m_u16Port;				/* Client Port */
	        public fixed DJ_S8	m_s8UserID[40];			/* Client UserID */
	        public DJ_U8   m_u8ReferedToUnitId;	// Referd-to header with replaces tag when act or sact
	        public DJ_U16  m_u16ReferedToChanId;	// Referd-to header with replaces tag when act or sact
        };/*Acs_VoIP_Refer*/


        /* Acs VoIP Refer Response struct */
        public unsafe struct Acs_VoIP_Refer_Response
        {
	        public DJ_U8	m_u8ReferFlag;			/* refer flag */
	        public DJ_U8	m_u8SrcUnitID;				/* source Unit ID */
	        public DJ_U16	m_u16SrcChanID;				/* source Channel ID */
	        public DJ_U8	m_u8DestUnitID;				/* destination Unit ID */
	        public DJ_U16	m_u16DestChanID;				/* destination Channel ID */
	        public fixed DJ_S8	m_s8TelNo[20];			/* Client Telephone-subscriber */
	        public fixed DJ_S8	m_s8Address[20];		/* Client Address */
	        public DJ_U16	m_u16Port;				/* Client Port */
	        public fixed DJ_S8	m_s8UserID[40];			/* Client UserID */
        };/*Acs_VoIP_Refer_Response*/

        /* Acs VoIP Refer Result struct */
        public struct Acs_VoIP_ReferResult
        {
	        public DJ_U8	m_u8Protocol;			/* protocol */
	        public DJ_U8	m_u8State;			/* state */
	        public DJ_U8	m_u8Reason;			/* reason */
        };/*Acs_VoIP_ReferResult*/

        /* Acs VoIP Refer Result struct */
        public struct Acs_VoIP_Notify
        {
	        public DJ_U32	m_u32StatusCode;		/* statusCode */
        };/*Acs_VoIP_Notify*/

        /* Acs VoIP Registraion Response struct */
        public unsafe struct Acs_VoIP_REGRESP
        {
	        public DJ_U16	m_u16SlotID;			/* Registration Slot ID */
	        public DJ_U8	m_u8Granted;			/* grant registration */
	        public fixed DJ_S8	m_s8Password[20];		/* password for sip authentication */
        };/*Acs_VoIP_REGRESP*/

        /*analog flash param*/
        public struct CmdParamData_FlashParam_t
        {
	        public DJ_U8	m_u8MinHookFlashTime;		//default is 5, //in units of 20ms
	        public DJ_U8	m_u8MaxHookFlashTime;		//default is 25,in units of 20ms	
        };/*CmdParamData_FlashParam_t*/

        public unsafe struct CmdParamData_TrunkFlashParam_t
        {
	        public DJ_U8	m_u8HookFlashTime;		//default is 10, //in units of 20ms
	        public fixed DJ_U8	m_u8reserved[3];		
        };

        /*Analoge Rec Module Voltage param*/
        public unsafe struct CmdParamData_AnalogRecVoltage_t
        {
	        public DJ_U8   m_u8Valtage;                   //[0, 54], default is 54
	        public fixed DJ_U8   m_u8Reserve[3];                //reserve
        };

        public unsafe struct CmdParamData_ReadSn_t
        {
            public  fixed   DJ_U8  m_u8ReadSn[13];
            public  fixed   DJ_U8  m_u8Reserved[3];
        };

        /*silence voice detect param*/
        public struct	CmdParam_SilenceDetectParam_t
        { 	
            public DJ_S32    m_s32SilenceLevel;            //silence detect level(db),default: -42, [-60, -20]        
            public DJ_S32    m_s32SilenceTimer;            //silence detect timer(ms)
            public DJ_S32    m_s32Reserved2;               //reserve
        };/*CmdParam_SilenceDetectParam_t*/

        /*CmdParam_ActiveMemDetectParam_t is obsolete now*/
        /*active member detect param*/
        public struct	CmdParam_ActiveMemDetectParam_t
        { 	
            public DJ_S32    m_s32VadLevel;                //active conf member detect level(db), obsolete        
            public DJ_S32    m_s32Reserved1;               //reserve                              obsolete
        }; /*CmdParam_ActiveMemDetectParam_t*/

        /*VAD min level detect param*/
        public unsafe struct	CmdParam_VADMinDetectParam_t
        { 	
            public DJ_S32    m_s32VadLevel;                //VAD min detect level(db), default: -54, [-60, -20] 
            public DJ_U16    m_u16VadInterval;             //VAD interval(5ms), default: 200, [10, 300]       
            public fixed DJ_U8     m_u8Reserved1[2];             //reserve
        }; /*CmdParam_VADMinDetectParam_t*/

        /*Board Common param set*/
        public unsafe struct	CmdParam_BoardCommonParam_t
        { 	
            public DJ_U8     m_u8IsCNGEnable;              //the switch of CNG, 0: Disable, 1: Enable 
            public DJ_U16    m_u16CNGGainLevel;            //the value of CNG gain,default: 9,[4, 15]       
            public fixed DJ_U8     m_u8Reserved1[29];            //reserve
        }; /*CmdParam_BoardCommonParam_t*/

        /*FSK Send/Recv param*/
        public unsafe struct CmdParamData_FskParam_t
        {
	        public DJ_U16	rxFilterWindow;         /*default is 4, shouldn't change it */
	        public DJ_U16	rxPeriodTheshold;       /*default is 320,shouldn't change it */
	        public DJ_U16	rx55Count;              /*default is 6, can be changed as needed */
	        public DJ_U16	rxAllOneSamples;        /*default is 200, can be changed as needed */
	        public DJ_U16	rxDataTimeOut;          /*default is 20ms,can be changed as needed */
	        public DJ_U16	txBit1Freq;             /*default is 1200,can be changed as needed */
	        public DJ_U16	txBit0Freq;             /*default is 2200,can be changed as needed */
	        public DJ_U16	tx55Count;              /*default is 30, can be changed as needed  */
	        public DJ_U16	txAllOneSamples;        /*default is 600, can be changed as needed */
	        public fixed DJ_U16	reserved[3];
        };/*CmdParamData_FskParam_t*/

        /* Acs Conference Active Member List struct */
        public unsafe struct CmdParamConf_MemberState_t
        {
                public fixed DJ_U8   m_s8NormalVad[16];       /*the buffer of normal active member in the conferece*/
                public fixed DJ_U8   m_s8IPVad[16];           /*the buffer of IP active member in the conferece*/
                public DJ_U8            m_u8TotalOfConfMem;      /*the total of members in the conferece*/
                public fixed DJ_U8   m_u8Ref[3];              /*reserver*/
        }; 

        /* Acs Set Conference Vad Check Interval struct */
        public unsafe struct CmdParamConf_VadInterval_t
        {
                public DJ_U16  m_u16VadCheckInterval;   /*The Interval Of Check Vad In A Conferece: [30, 65535], Unit: ms*/
                public DJ_U8   m_u8RptConfMemEnable;    /*If Auto Report Active Conference member, 1: Enable, 0: Disable*/
                public fixed DJ_U8   m_u8Ref[5];              /*reserve*/
        };

        /* Acs VoIP H.245 UserInputIndication struct */
        public unsafe struct CmdParamData_CTCLKNET_t
        {
            public DJ_U8   m_u8NetRef1;       /*L_NET0=0x08,L_NET1=0x09,L_NET2=0x0A,L_Net3=0x0B*/
	        public DJ_U8   m_u8SysClockType;  /*reference to XMS_BOARD_CLOCK_TYPE*/
            public fixed DJ_U8   m_u8Rfu[2];        /* Reserved*/

        };

        /* Acs VoIP H.245 UserInputIndication struct */
        public unsafe struct Acs_VoIP_H245UII
        {
	        public fixed DJ_S8	m_s8String[100];		/* UserInputIndication string (general string)*/
	        public DJ_S8	m_s8Signal;				/* UserInputIndication signal type (dtmf char in "0123456789#*ABCD!")*/
	        public fixed DJ_S8   m_Rfu[3];               /* Reserved*/
	        public DJ_U32	m_u32Duration;			/* UserInputIndication signal duration (in milliseconds)*/
        };/*Acs_VoIP_H245UII*/

        /* Acs MediaEx Audio Output Param*/
        public unsafe struct Acs_MediaEx_Output_A
        {
	        public fixed DJ_S8		m_s8IP[20];				/* dest address */
	        public DJ_U16	m_u16Port;				/* dest port */
	        public DJ_U8		m_u8Codec;				/* codec type */
	        public DJ_U8		m_u8PayloadType;		/* rtp payload type (if dynamic) */
        };/*Acs_MediaEx_Output_A*/

        /* Acs MediaEx Play Param */
        public unsafe struct Acs_MediaEx_Play
        {
	        public PrivateData_t   m_PrivateData;			/*privatedata head*/
	        public fixed DJ_S8	  m_s8SrcName[ConstantVar.ACS_MAX_FILE_NAME_LEN];	/* file name */
	        public  DJ_U32			  m_u32Start;				/* start time */
	        public DJ_U8			     m_u8Loop;				/* loop */
	        public Acs_MediaEx_Output_A	audio;			/* audio output param */
	        public Acs_MediaEx_Output_V	video;			/* video output param */
	        public fixed DJ_S8					s8OverlayImage[200];
        };/*Acs_MediaEx_PlayFile*/

            /* Acs 3GVConf Play Param */
        public struct Acs_3GVConf_Play
        {
	        public PrivateData_t   m_PrivateData;			/*privatedata head*/
	        public DeviceID_t         m_device;			/*voc conf DeviceID*/
	        public Acs_MediaEx_Play   m_play;			/*Acs_MediaEx_PlayFile*/
        } ;/*Acs_MediaEx_PlayFile*/

        /* Acs MediaEx Transcode Param */
        public unsafe struct Acs_MediaEx_Transcode
        {
	        public PrivateData_t			        m_PrivateData;	/*privatedata head*/ 
	        public Acs_MediaEx_Input_V	input;			/* input param */
	        public Acs_MediaEx_Output_V	output;			/* output param */
	        public fixed DJ_S8					s8OverlayImage[200];
        } ;/*Acs_MediaEx_Transcode*/

        /* Acs MediaEx Conference Param */
        public unsafe class Acs_MediaEx_Conference
        {
	        public PrivateData_t			m_PrivateData;	/*privatedata head*/
            public Acs_MediaEx_Input_V[] input = new Acs_MediaEx_Input_V[16];
            public Acs_MediaEx_Output_V[] output = new Acs_MediaEx_Output_V[16];
	        //public fixed Acs_MediaEx_Input_V		input[16];		/* input param */
	        //public fixed Acs_MediaEx_Output_V	    output[16];		/* output param */
	        public DJ_S8					[]s8OverlayImage= new DJ_S8[200];
        } ;/*Acs_MediaEx_Conference*/

        /* Acs MediaEx Record Param */
        public unsafe struct Acs_MediaEx_Record
        {
	        public PrivateData_t   m_PrivateData;			/*privatedata head*/
	        public fixed DJ_S8			m_s8DstName[ConstantVar.ACS_MAX_FILE_NAME_LEN];	/* file name */
	        public Acs_MediaEx_Output_A	audio;			/* audio output param */
	        public Acs_MediaEx_Output_V	video;			/* video output param */
        } ;/*Acs_MediaEx_Record*/

        /* Acs 3GVConf Record Param */
        public struct Acs_3GVConf_Record
        {
	        public PrivateData_t   m_PrivateData;			/*privatedata head*/
	        public DeviceID_t         m_device;			/*voc conf DeviceID*/
	        public Acs_MediaEx_Record   m_record;			/*Acs_MediaEx_RecordFile*/
        } ;/*Acs_MediaEx_RecordFile*/

        /* Acs 3GVConf Cmd Param */
        public struct Acs_3GVConf_Cmd_V
        {
	        public DeviceID_t               m_device;
	        public Acs_MediaEx_Input_V      m_input;
	        public Acs_MediaEx_Output_V     m_output;
	        public DJ_U8                    m_u8Visible;
	        public DJ_U8                    m_u8CmdType;
        } ;/*Acs_3GVConf_Cmd_V*/

        /* Acs MediaEx Conference Layout */
        public unsafe struct Acs_MediaEx_ConfLayout
        {
	        public PrivateData_t			m_PrivateData;	/*privatedata head*/ 
	        public fixed int						layout[16];
        };/*Acs_MediaEx_ConfLayout*/

        /* Acs Video Link Param */
        public unsafe struct Acs_Video_Link_Param
        {
	        public PrivateData_t m_PrivateData;	/*privatedata head*/ 
            public DJ_U8 m_u8TranscodeModule;		/* transcode module id */
	        public DJ_U8 m_u8SrcCodec;				/* source codec type */
            public DJ_U16 decoderConfigLength;
	        public fixed DJ_U8 decoderConfigInfo[ConstantVar.MAX_DECODER_CFG_INFO];
	        public DJ_U8 m_u8DstCodec;				/* destination codec type */
	        public DJ_U8 m_u8Fps;						/* destination framerate in fps */
	        public DJ_U16 m_u16Kbps;					/* destination bitrate in Kbps */ 
            public DJ_U16 m_u16ResX;					/* destination resolution x */
	        public DJ_U16 m_u16ResY;					/* destination resolution y */
	        public fixed DJ_S8 s8OverlayImage[200];
        };/*Acs_Video_Link_Param*/

        public struct Acs_3G324M_H223CAP
        {
	        public DJ_U8 videoWithAL1;
	        public DJ_U8 videoWithAL2;
	        public DJ_U8 videoWithAL3;
	        public DJ_U8 audioWithAL1;
	        public DJ_U8 audioWithAL2;
	        public DJ_U8 audioWithAL3;
	        public DJ_U16 maximumAl2SDUSize;
	        public DJ_U16 maximumAl3SDUSize;
	        public DJ_U16 maximumDelayJitter;
	        public DJ_U8 maxMUXPDUSizeCapability;
	        public DJ_U8 nsrpSupport;
	        public DJ_U8 modeChangeCapability;
	        public DJ_U8 h223AnnexA;
	        public DJ_U8 h223AnnexADoubleFlag;
	        public DJ_U8 h223AnnexB;
	        public DJ_U8 h223AnnexBwithHeader;
	        public DJ_U8 reserved;
        } ;

        public unsafe struct Acs_3G324M_CAP_AMR
        {
	        public DJ_U8 maxBitRate;
	        public DJ_U8 maxFramesPerSdu;
	        public fixed DJ_U8 reserved[2];
        }  ;

        public unsafe struct Acs_3G324M_CAP_G723
        { 
	        public DJ_U8 maxFramesPerSdu;
	        public DJ_U8 silenceSuppression;
	        public fixed DJ_U8 reserved[2];
        }  ;

        public unsafe struct Acs_3G324M_CAP_H263
        {
	        public DJ_U8 sqcifMPI;
	        public DJ_U8 qcifMPI;
	        public DJ_U8 cifMPI;
	        public DJ_U8 cif4MPI;
	        public DJ_U8 cif16MPI;
	        public DJ_U8 reserved1;
	        public DJ_U16 maxBitRate;
	        public DJ_U8 unrestrictedVector;
	        public DJ_U8 arithmeticCoding;
	        public DJ_U8 advancedPrediction;
	        public DJ_U8 pbFrames;
	        public DJ_U8 temporalSpatialTradeOffCapability;
	        public DJ_U8 errorCompensation;
	        public fixed DJ_U8 reserved2[2];
        }  ;

        public unsafe struct Acs_3G324M_CAP_MP4
        {
	        public DJ_U16 maxBitRate;
	        public DJ_U8 profileAndLevel;
	        public DJ_U8 obj;
	        public fixed DJ_U8 reserved[3];
	        public DJ_U8 decoderConfigLength;
	        public fixed DJ_U8 decoderConfigInfo[ConstantVar.MAX_DECODER_CFG_INFO];
        }  ;

        [StructLayout(LayoutKind.Explicit)]
        public struct Acs_3G324M_CAP
        {
            [FieldOffset(0)]
            public Acs_3G324M_CAP_AMR AmrAudioCapability;
            [FieldOffset(0)]
            public Acs_3G324M_CAP_G723 G7231AudioCapability;
            [FieldOffset(0)]
            public Acs_3G324M_CAP_H263 H263VideoCapability;
            [FieldOffset(0)]
            public Acs_3G324M_CAP_MP4 Mpeg4VideoCapability;
        }


        public struct Acs_3G324M_CAPENTRY
        {
	        public DJ_U16 entryNumber;
	        public DJ_U8 capType;							/* reference to XMS_VOIP_MEDIA_CAPS */
	        public DJ_U8 direction;						/* reference to XMS_CAP_DIRECTION */
	        public Acs_3G324M_CAP capability;
        } ;

        public class Acs_3G324M_CAPTABLE
        {
	        public DJ_U16 capabilityNum;
	        public DJ_U16 reserved;
	        public Acs_3G324M_CAPENTRY []CapabilityTableEntry = new Acs_3G324M_CAPENTRY[ConstantVar.MAX_CAPS_NUM];
        } ;

        public struct Acs_3G324M_TCS
        {
	        public Acs_3G324M_H223CAP h223Capability;
	        public Acs_3G324M_CAPTABLE capabilityTable;
        } ;

        /* Acs VoIP SIP INFO struct */
        public unsafe struct Acs_VoIP_SIPINFO
        {
	        public fixed DJ_S8	m_s8ContentType[50];	/* content type string (mime)*/
	        public fixed DJ_S8	m_s8Body[800];			/* info message body string*/
        };/*Acs_VoIP_SIPINFO*/

        /* Acs VoIP SIP Register/Unregister struct */
        public unsafe struct Acs_VoIP_SIPREG
        {
	        public fixed DJ_S8	m_s8TelNo[20];	    /* subscriber number */
	        public fixed DJ_S8	m_s8Username[20];	/* username for authorization */
	        public fixed DJ_S8	m_s8Password[20];	/* paswword for authorization */
        };/*Acs_VoIP_SIPREG*/

        /* Acs VoIP RTP DTMF struct */
        public struct Acs_VoIP_RTPDTMF
        {
	        public DJ_S8	m_s8EventChar;			/* dtmf event char */
	        public DJ_S8	m_s8Volume;				/* volume (in dbm0 from -63 to 0) */
	        public DJ_U16	m_u16Duration;			/* duration (in timestamp units) */
        };/*Acs_VoIP_RTPDTMF*/

        /* Acs VoIP RTP TONE struct */
        public unsafe struct Acs_VoIP_RTPTONE
        {
	        public DJ_U16	m_u16Modulation;		/* modulation */
	        public DJ_U8 	m_u8TriFlag;			/* tri-frequency flag */
	        public DJ_S8	    m_s8Volume;				/* volume */
	        public DJ_U16	m_u16Duration;			/* duration */
	        public DJ_U8	    m_u8FrequencyNum;		/* number of frequencies */
	        public fixed DJ_U16	m_u16Frequency[10];		/* frequencies to mix the tone */
        };/*Acs_VoIP_RTPTONE*/

        /* Acs VoIP Mixer struct*/
        public struct Acs_VoIP_Mixer
        {
            public DJ_U8 m_u8SRC1_Ctrl;  /*reference XMS_MIXER_TYPE*/
            public DJ_U8 m_u8SRC2_Ctrl;  /*reference XMS_MIXER_TYPE*/
            public DJ_U16 m_u16SRC_ChID1; /*Media ChID1*/
            public DJ_U16 m_u16SRC_ChID2; /*Media ChID2*/
            public DJ_S8 m_s8Video;      /*Video Channel*/
            public DJ_S8 m_s8Rfu;        /*Rfu*/
        };/*Acs_VoIP_Mixer*/

        public struct CmdParamData_AnalogTrunkFlash_t
        {
            public DJ_U8 m_u8Channel_Enable;
            public DJ_U8 m_u8Type;
            public DJ_U8 m_u8Tx_State;
            public DJ_U8 m_u8Rx_State;
        };/*CmdParamData_AnalogTrunkFlash_t*/

            /*DTMF control param*/
        public unsafe struct CmdDtmfParamData_Voice_t
        {
             public DJ_U32                      m_u32MaxValidIntervalTime;  /* max interval time: ms*/
             public DJ_U8                       m_u8MaxCodeNums;            /* max DTMF nums : 0 ~ 255*/
             public fixed DJ_U8                       m_u8Rfu1[3];                /*Rfu*/
             public fixed DJ_U8                       m_u8DTMF[32];               /*DTMF buffer*/
        };/*CmdDtmfParamData_Voice_t*/


        /* Struct of AddFaxFile */
        public unsafe struct CmdParamData_AddFax_t
        {
	        public fixed DJ_S8       m_s8FaxFileName[128]; /* FaxFileName ,Usual As Tiff Format */
        };/*CmdParamData_AddFax_t*/

        /* Struct of StartSendFax */
        public unsafe struct CmdParamData_StartSendFax_t
        {
	        public DeviceID_t m_VocDev;
	        public fixed DJ_S8      m_s8LocalID[ConstantVar.ACS_LOCALID_MAX_LEN];
        };/*CmdParamData_StartSendFax_t*/

        /*CmdParamData_3GPP_t*/
        public unsafe struct CmdParamData_3GPP_t
        {	
            public DJ_U8			   m_u8AudioDecodeType;  /*audio decode type*/
	        public DJ_U8           m_u8AudioFrameType;   /*audio frame type,reference XMS_AUDIO_AMR_FRAME_TYPE*/
            public DJ_U16			m_u16AudioDecoderCfgLen;/*audio decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
	        public fixed DJ_U8	m_u8AudioDecoderCfg[ConstantVar.ACS_MAX_DECODER_CFG_LEN];/*audio decoder cfg*/
	        public DJ_U8           m_u8AudioProfiles;    /*audio profiles?*/
            public DJ_U8           m_u8AudioLevel;		  /*audio level ?*/
            public fixed DJ_U8   m_Rfu1[2];

	        public DJ_U8           m_u8VideoDecodeType;      /*video decode type*/
	        public DJ_U8           m_u8VideoFrameRate;       /*video frame rate 10 ~ 30*/
	        public DJ_U16          m_u16VideoDecoderCfgLen;  /*video decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
	        public fixed DJ_U8   m_u8VideoDecoderCfg[ConstantVar.ACS_MAX_DECODER_CFG_LEN];/*video decoder cfg?*/
	        public DJ_U8           m_u8VideoProfiles;        /*video profiles?*/
	        public DJ_U8           m_u8VideoLevel;           /*video level?*/
	        public fixed DJ_U8           m_Rfu2[2];
        };/*CmdParamData_3GPP_t*/

        /*DigRecSwitchMode*/
        public unsafe struct DigRecSwitchMode
        {
	        public DJ_U8           m_u8Enable;               /*the switch of the function, 0: disable; 1: enable*/
	        public DJ_U8           m_u8SwitchMode;           /*the digital switch type,referece to XMS_DRS_SWITCH_TYPE*/
	        public DJ_U8           m_u8EncodeType;           /*audio's encode type, referece to the A-Law or Mu-law of XMS_VOC_CODE_TYPE, and any other type is not supported by keygoe*/
	        public DJ_U8           m_u8IsRecordSigData;      /*the switch to wheather record the signal data from DSP, 0: disable; 1: enable*/
	        public fixed DJ_S8           m_Rfu1[4];                /*reserve*/
        };/*DigRecSwitchMode*/
       
        /*CmdParamData_SS7RawFrame_t*/
        public unsafe struct CmdParamData_SS7RawFrame_t
        {
	        public DJ_U8 m_u8UserType;
	        public DJ_U8 m_u8LinkType;
	        public DJ_U8 m_u8MsgType;
	        public DJ_U8 m_u8InfoLen;
        	
	        public DJ_U8 m_u8UnitId;
	        public DJ_U8 m_u8E1Port;
	        public DJ_U8 m_u8Ts;
	        public DJ_U8 m_u8Reserved1;
        	
	        public fixed DJ_U8 m_u8Info[255];
	        public DJ_U8 Reserved2;
        };/*CmdParamData_SS7RawFrame_t*/

        [StructLayout(LayoutKind.Explicit)]
        public struct CmdParamData_t
        {
            [FieldOffset(0)]
            public CmdParamData_Voice_t m_cmdParamDataVoice;
            [FieldOffset(0)]
            public CmdParamData_Conf_t m_CmdParamDataConf;
        };

        /*Acs_OpenDev_Evt*/
        public struct Acs_GeneralProc_Evt
        {
	        public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
	        public Acs_GeneralProc_Data      m_AcsGenLProcData; /*acs general proc event data*/
        };/**/

        /*OpenStreamExt evt data*/
        public unsafe struct Acs_OpenStreamExt_Data
        {
	        public ServerID_t        m_ServerID;
	        public Acs_Evt_State_t   m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
	        public fixed DJ_S8             m_s8Rfu1[12];
        };/**/

        /*Acs_OpenStreamExt_Evt*/
        public struct Acs_OpenStreamExt_Evt
        {
	        public ACS_EVT_HEAD                m_AcsEvtHead;           /*acs event head*/
	        public Acs_OpenStreamExt_Data      m_AcsOpenStreamExtData; /*acs general proc event data*/
        };/**/

        /*Acs_CloseStreamExt_Data*/
        public unsafe struct Acs_CloseStreamExt_Data
        {
	        public ServerID_t      m_ServerID;
	        public fixed DJ_S8           m_s8Rfu1[16];
        };/**/

        /*Acs_CloseStreamExt_Evt*/
        public struct Acs_CloseStreamExt_Evt
        {
	        public ACS_EVT_HEAD                m_AcsEvtHead;            /*acs event head*/
	        public Acs_CloseStreamExt_Data     m_AcsCloseStreamExtData; /*acs general proc event data*/
        };/**/

        /*ACS master state*/
        public unsafe struct Acs_MasterState_Data
        {
	        public fixed DJ_S8      m_s8ServerIp[32]; /*XMS server ip*/
	        public DJ_U32     m_u32ServerPort;  /*XMS server port*/
	        public DJ_U8      m_u8MasterState; /*Acs server master state,reference ACS_MASTER_STATE*/
	        public fixed DJ_S8      m_Rfu1[3];
        };

        /*Acs_MasterState_Evt*/
        public struct Acs_MasterState_Evt
        {
	        public ACS_EVT_HEAD                m_AcsEvtHead;     /*acs event head*/
	        public Acs_MasterState_Data        m_AcsMasterState; /*acs master state*/
        };/**/

        /*ACS Slave Work state*/
        public unsafe struct Acs_SlaveWorkState_Data
        {
	        public DJ_S8      m_s8WorkState; /*Slave machine work state: 0: conk out, 1: working, reference to ACS_WORK_STATE*/
	        public fixed DJ_S8      m_Rfu1[31];    /*reserve*/
        };

        /*Acs_SlaveWork_Evt*/
        public struct Acs_SlaveWorkState_Evt
        {
	        public ACS_EVT_HEAD                m_AcsEvtHead;        /*acs event head*/
	        public Acs_SlaveWorkState_Data     m_AcsSlaveWorkState; /*acs slave work state*/
        };/**/


        /*Acs_BakSysStartEvt*/
        public struct Acs_BakSysStartEvt
        {
            public ACS_EVT_HEAD   m_AcsEvtHead;  /*acs event head*/
            public DJ_S32         m_Rfu1;
        };/**/

        public struct Acs_ParamProc_Data
        {
	        public Acs_Evt_State_t         m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
	        public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;  /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	        public DJ_U16                  m_u16ParamCmdType;  /*acs param Cmd Type*/
	        public DJ_U16                  m_u16ParamDataSize; /*acs param Data Size*/
        };/**/

        public struct Acs_ParamData_Evt
        {
	        public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
	        public Acs_ParamProc_Data        m_ParamProcData;
        };/**/

        public unsafe struct Acs_ParamData_UserReadXmsBoardInfo
        {
	        public fixed DJ_U8	 m_u8MacAddr[6];	   /* Mac address */
	        public DJ_U8	 m_u8ChassisType;   /* chassis type，0: ITP1200; 1:3U chassis; 2:5U chassis; 3: 11U chassis */
	        public DJ_U8	 m_u8ChassisIndex;  /* chassis  No */
	        public DJ_U8	 m_u8ChassisSlot;   /* chassis slot number */
	        public DJ_U8 m_u8SubBoardIndex; /* module index inside one board*/
	        public DJ_U8	 m_u8BoardType;	   /* Board type，0:itp1200;1:itp2400; 2: itp4800*/
	        public DJ_U8	 rfu1;
	        public fixed DJ_S8	 m_s8SystemName[32];/* System name */	
	        public DJ_S8	 m_s8PlatformType;  /* Platform: 1:callback; 2:keygoe 1000; 3:keygoe 3000; 4:keygoe 8000*/
	        public fixed DJ_S8	 m_s8UserCode[7];   /* User code */
	        public DJ_S32	m_s32SysId;        /* sys id*/
	        public fixed DJ_S8	 rfu2[20];

	        public fixed DJ_S8	 m_s8FirmwareName[8];	/* DSP firmwarename */
	        public fixed DJ_S8	 m_s8FirmwareVersion[8];	/* DSP firmware version*/
	        public fixed DJ_S8	 m_s8RevisionDate[8];	/* DSP firmware date*/
        };

        /*Acs_BoardPrivateExt_Data*/
        public unsafe struct Acs_BoardPrivateExt_Data
        {
	        public DJ_U32 m_u32ExtType;        //reference to XMS_BOARD_PRIVATE_EXT_TYPE
            public DJ_U8 m_u8BoardClockTypeOrSysClockMode;// BoardClockType reference to XMS_BOARD_EXT_CLOCK_TYPE
                                                                                              // SysClockMode reference to XMS_BOARD_CLOCK_MODE
	        public DJ_U8  m_u8SysClockType;    /*reference to XMS_BOARD_CLOCK_TYPE	*/
	        public fixed DJ_U8  m_u8Ref[2];
        };/*Acs_BoardPrivateExt_Data*/

        /*Acs_BoardRstState_Data*/
        public unsafe struct Acs_BoardRstState_Data
        {
	        public fixed DJ_U8  m_u8Ref[16];  //reserve	
        };/*Acs_BoardRstState_Data*/

        /* CAS Extra Infomation, used by XMS_EVT_CAS_MFC_END*/
        public unsafe struct Acs_CAS_ExtraInfo_t
        {
	        /* Call In Infomation */
	        public DJ_U8                     m_u8KA; /* Caller's KA */
	        public DJ_U8                     m_u8KD; /* Caller's KD */
	        /* Call Out Infomation */

	        /* Other */
	        public fixed DJ_U8                     m_u8Rfu[14];/* Reserved for Future Use */
        };/*Acs_CAS_ExtraInfo_t*/

        /*Acs_CallControl_Evt*/
        public struct Acs_CAS_MFC_Evt
        {
	        public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
	        public Acs_CAS_ExtraInfo_t       m_AcsCASExtraInfo; /*acs CAS ExtraInfo event data*/
        };/**/

          /*Acs_CallControl_Evt*/
        public struct Acs_CallControl_Evt
        {
            public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
            public Acs_CallControl_Data      m_AcsCallControl; /*acs call control event data*/
        };/**/

        /*Acs_LinkDev_Data*/
        public struct Acs_LinkDev_Data
        {
            public Acs_Evt_State_t         m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
            public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
            public DeviceID_t              m_SrcDevice;
            public DeviceID_t              m_DestDevice;
        };/*Acs_LinkDev_Data*/

        /*Acs_LinkDev_Evt*/
        public struct Acs_LinkDev_Evt
        {
            public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
            public Acs_LinkDev_Data          m_AcsLinkDev;     /*acs Link Device event data*/
        };/*Acs_LinkDev_Evt*/

        /*Acs_CtxReg_Data*/
        public struct Acs_CtxReg_Data
        {
            public Acs_Evt_State_t         m_s32AcsEvtState;   /*acs event state, 1: success; -1: failed*/
            public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
        };/**/

        /*Acs_CtxReg_Evt*/
        public struct Acs_CtxReg_Evt
        {
            public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
            public Acs_CtxReg_Data           m_AcsCtxReg;      /*acs ctxReg evt*/
        };/**/

        /*Acs_CtxLink_Data*/
        public struct Acs_CtxLink_Data
        {
            public Acs_Evt_State_t         m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
            public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
        };/**/

        /*Acs_CtxLink_Evt*/
        public struct Acs_CtxLink_Evt
        {
            public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
            public Acs_CtxLink_Data          m_AcsCtxLink;
        };/**/

        /*CTX App Data Info*/
        public unsafe struct CTX_AppData_Info
        {
            public DJ_U32      m_u32AppDataSize; /*user APP data size,not include XMS_AppData_Info_t*/
            public DJ_U8       m_u8AppReqType;   /*user APP req cmd type,user self define*/
            public DJ_U8       m_u8AcsUnitID;
            public fixed DJ_U8       m_Rfu1[2];      
            public fixed DJ_S8       m_s8SrcRegName[ConstantVar.XMS_MAX_REGNAME_LEN]; /*src reg name*/
            public fixed DJ_S8       m_s8DestRegName[ConstantVar.XMS_MAX_REGNAME_LEN];/*dest reg name*/
            public DJ_U8       m_u8SrcAppUnitID;
            public DJ_U8       m_u8DstAppUnitID;
            public fixed DJ_S8       m_Rfu2[2];
            public DeviceID_t  m_srcDevice;
            public fixed DJ_S8       m_Rfu3[20];
            public DJ_S32      m_s32Rst;
        };/**/

        /*Acs_CtxAppData_Info*/
        public struct Acs_CtxAppData_Info
        {
            public Acs_Evt_State_t         m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
            public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
            public CTX_AppData_Info        m_AppDataInfo;
        };/**/

        /*Acs_CtxAppData_Evt*/
        public struct Acs_CtxAppData_Evt
        {
            public ACS_EVT_HEAD             m_AcsEvtHead;     /*acs event head*/
            public Acs_CtxAppData_Info      m_AcsCtxAppData;
        };/**/

        /*Acs_CtxState_Info*/
        public unsafe struct Acs_CtxState_Info
        {
            public Acs_Evt_State_t         m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
            public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
            public DJ_U32                  m_u32CtxState;
            public fixed DJ_S8                   m_s8SrcRegName[ConstantVar.XMS_MAX_REGNAME_LEN];
            public fixed DJ_S8                   m_s8DestRegName[ConstantVar.XMS_MAX_REGNAME_LEN];
        };/**/

        /*Acs_Ctx_State_Evt*/
        public struct Acs_Ctx_State_Evt
        {
            public ACS_EVT_HEAD             m_AcsEvtHead;     /*acs event head*/
            public Acs_CtxState_Info        m_AcsCtxState;
        };/**/

        /*Acs_SigMon_Data*/
        public struct Acs_SigMon_Data
        {
            public SMON_EVENT           m_SigMon;            /*sig monitor data*/
            public PrivateData_t        m_PrivData;          /*private data*/
        };/*Acs_SigMon_Data*/

        /*Acs_SigMon_Evt*/
        public struct Acs_SigMon_Evt
        {
            public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
            public Acs_SigMon_Data           m_AcsSigMon;      /*acs call control event data*/
        };/**/

        /*Acs_3G324_Data*/
        public	struct Acs_3G324_Data
        {
            public DJ_U8	m_u8DataType;		    /*3G324 event data type*/
            public DJ_S8	Rfu1;				    /*reserved*/
            public DJ_U16	m_u16DataLen;	        /*3G324 event data size*/	
        };/*Acs_3G324_Data*/

        /*Acs_3G324_Evt*/
        public struct Acs_3G324_Evt
        {
            public ACS_EVT_HEAD		m_AcsEvtHead;  /*acs event head*/	
            public Acs_3G324_Data		m_Acs324Data;  /*acs 3G324 event*/
        };/**/

        /*Acs_3G324_Stop_Evt*/
        public unsafe struct Acs_3G324_Stop_Evt
        {
            public DJ_U8	m_u8StopCode;			/*3G324 session stop code*/
            public fixed DJ_U8 m_u8Rfu[3];				/*reserved*/	
        };/**/

        /*Acs_AnalogInterface_Data*/
        public unsafe struct Acs_AnalogInterface_Data
        {
            public Acs_Evt_State_t         m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
            public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
            public DJ_U8                   m_u8AnalogInterfaceState;/*Analog Interface State,reference XMS_ANALOG_INTERFACE_STATE*/
            public fixed DJ_U8                   m_Rfu1[3];
            public PrivateData_t           m_PrivData;          /*private data*/
        };/**/

        /*Acs_AnalogInterface_Evt*/
        public struct Acs_AnalogInterface_Evt
        {
            public ACS_EVT_HEAD                  m_AcsEvtHead;     /*acs event head*/
            public Acs_AnalogInterface_Data      m_AcsAnalogInterfaceData; /*acs Analog Interface event data*/
        };/**/

        /*Acs_SendSigMsg_Data*/
        public unsafe struct Acs_SendSigMsg_Data
        {
            public Acs_Evt_State_t         m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
            public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;  /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
            public DJ_S16                  m_s16SignalMsgType;  /*acs signal msg type*/
            public fixed DJ_S8                   m_s8Rfu[2];          /*Rfu*/
        };/**/

        /*Acs_SendSigMsg_Evt*/
        public struct Acs_SendSigMsg_Evt
        {
            public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
            public Acs_SendSigMsg_Data       m_AcsSendSigMsg;  /*acs send signal msg event data*/
        };/**/

        /*Acs_ConfControl_Data*/
        public struct Acs_ConfControl_Data
        {
            public Acs_Evt_State_t         m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
            public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;  /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
            public DJ_S32                  m_s32ConfMembers;    /*Obsolete, replaced by m_u8TotalOfConfMem of CmdParamConf_MemberState_t*/		
            public DeviceID_t              m_MediaDevice;
            public PrivateData_t           m_PrivData;/*private data*/
        };/**/

        /*Acs_ConfControl_Evt*/
        public struct Acs_ConfControl_Evt
        {
            public ACS_EVT_HEAD              m_AcsEvtHead;      /*acs event head*/
            public Acs_ConfControl_Data      m_AcsConfControl;  /*acs call control event data*/
        };/**/

        /*Acs_MediaProc_Evt*/
        public struct Acs_MediaProc_Evt
        {
            public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
            public Acs_MediaProc_Data        m_AcsMediaProc;  /*acs media proc event data*/
        };/**/

        /*Acs_CSPDataReq_Data*/
        public	struct Acs_CSPDataReq_Data
        {
            public DJ_U16			m_u16ReqCspDataLen; /*DSP request data length*/
            public DJ_U8			m_u8TaskID;	        /*Task ID*/
            public DJ_U8			m_u8DataType;	    /*Data Type: reference XMS_CSPPLAY_DATA_TYPE*/
        };/*Acs_CSPDataReq_Data*/

        /*Acs_CSPDataReq_Evt*/
        public struct Acs_CSPDataReq_Evt
        {
            public ACS_EVT_HEAD              m_AcsEvtHead;         /*acs event head*/
            public Acs_CSPDataReq_Data       m_AcsCSPDataReqProc;  /*acs media CSP play request data*/
        };/**/

        /*Acs_MediaCSPProc_Data*/
        public unsafe struct Acs_MediaCSPProc_Data
        {
	        public DJ_U16	m_u16DataLen;	        /*stream data size*/
	        public DJ_U8	    m_u8DataType;		    /*stream data type*/
	        public DJ_U8	    m_u8TagNumber;			/*Rfu*/
	        public  fixed DJ_U8	m_u8StreamData[ConstantVar.ITP_MAX_STREAM_DATA_LENGTH ];	/*stream data*/
        };

        /*Acs_MediaCSPProc_Evt*/
        public struct Acs_MediaCSPProc_Evt
        {
	        public ACS_EVT_HEAD                  m_AcsEvtHead;       /*acs event head*/
	        public Acs_MediaCSPProc_Data    m_AcsMediaCSPProc;  /*acs media CSP proc event data*/
        };/**/

        /*Acs_Media3GPPProc_Data*/
        public struct Acs_Media3GPPProc_Data
        {
	        public Acs_Evt_State_t            m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	        public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	        public DJ_U8                   m_u8AudioTaskID;          /*audio:  play Task ID*/
	        public DJ_U8                   m_u8MediaType;            /*common: media type XMS_MEDIA_TYPE*/
	        public DJ_U8                   m_u8VideoTaskID;          /*video:  play Task ID*/
	        public DJ_S8                   m_s8Rfu;
	        public DJ_U32                 m_u32AudioCurFileIndex;   /*audio:current play index*/
	        public DJ_U32                 m_u32AudioCurFilePos;     /*audio:current play pos*/
	        public DJ_U32                 m_u32VideoCurFileIndex;   /*video:current play index*/
	        public DJ_U32                 m_u32VideoCurFilePos;     /*video:current play pos*/
	        public PrivateData_t       m_PrivData;/*private data*/
        };/**/

        /*Acs_Media3GPPProc_Evt*/
        public struct Acs_Media3GPPProc_Evt
        {
	        public ACS_EVT_HEAD                      m_AcsEvtHead;    /*acs event head*/
	        public Acs_Media3GPPProc_Data    m_AcsMedia3GPPProc;  /*acs media proc event data*/
        };/**/

        /*Acs_JoinTo3GVConf_Data*/
        public struct Acs_JoinTo3GVConf_Data
        {
	        public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	        public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	        public DeviceID_t              m_3GVConfDev;
	        public DeviceID_t              m_srcDev;
	        public PrivateData_t           m_PrivData;/*private data*/
        };/**/

        /*Acs_JoinTo3GVConf_Evt*/
        public struct Acs_JoinTo3GVConf_Evt
        {
	        public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	        public Acs_JoinTo3GVConf_Data    m_AcsJoinTo3GVConf;  /*acs Join to 3GVConf event data*/
        };/**/

        /*Acs_LeaveFrom3GVConf_Data*/
        public struct Acs_LeaveFrom3GVConf_Data
        {
	        public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	        public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	        public DeviceID_t              m_3GVConfDev;
	        public DeviceID_t              m_srcDev;
	        public PrivateData_t           m_PrivData;/*private data*/
        };/**/

        /*Acs_LeaveFrom3GVConf_Evt*/
        public struct Acs_LeaveFrom3GVConf_Evt
        {
	        public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	        public Acs_LeaveFrom3GVConf_Data    m_AcsLeaveFrom3GVConf;  /*acs leave from 3GVConf event data*/
        };/**/

        /*Acs_Clear3GVConf_Data*/
        public struct Acs_Clear3GVConf_Data
        {
	        public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	        public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	        public DeviceID_t              m_3GVConfDev;
	        public PrivateData_t           m_PrivData;/*private data*/
        };/**/

        /*Acs_Clear3GVConf_Evt*/
        public struct Acs_Clear3GVConf_Evt
        {
	        public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	        public Acs_Clear3GVConf_Data     m_AcsClear3GVConf;  /*acs clear 3GVConf event data*/
        };/**/

        /*Acs_GetLayout_Data*/
        public struct Acs_GetLayout_Data
        {
	        public Acs_Evt_State_t            m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	        public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	        public DeviceID_t                    m_3GVConfDev;
	        public Acs_3GVConf_LayoutList  m_list;
	        public PrivateData_t               m_PrivData;/*private data*/
        };/**/

        /*Acs_GetLayout_Evt*/
        public struct Acs_GetLayout_Evt
        {
	        public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	        public Acs_GetLayout_Data        m_AcsGetLayout;  /*acs Get Layout event data*/
        };/**/

        /*Acs_SetLayout_Data*/
        public struct Acs_SetLayout_Data
        {
	        public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	        public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	        public DeviceID_t              m_3GVConfDev;
	        public PrivateData_t           m_PrivData;/*private data*/
        };/**/

        /*Acs_SetLayout_Evt*/
        public struct Acs_SetLayout_Evt
        {
	        public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	        public Acs_SetLayout_Data        m_AcsSetLayout;  /*acs Set Layout event data*/
        };/**/

        /*Acs_GetVisibleList_Data*/
        public struct Acs_GetVisibleList_Data
        {
	        public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	        public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	        public DeviceID_t              m_3GVConfDev;
	        public Acs_3GVConf_VisibleList m_list;
	        public PrivateData_t           m_PrivData;/*private data*/
        };/**/

        /*Acs_GetVisibleList_Evt*/
        public struct Acs_GetVisibleList_Evt
        {
	        public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	        public Acs_GetVisibleList_Data   m_AcsGetVisibleList;  /*acs Get Visible List event data*/
        };/**/

        /*Acs_SetVisibleList_Data*/
        public struct Acs_SetVisibleList_Data
        {
	        public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	        public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	        public DeviceID_t              m_3GVConfDev;
	        public PrivateData_t           m_PrivData;/*private data*/
        };/**/

        /*Acs_SetVisibleList_Evt*/
        public struct Acs_SetVisibleList_Evt
        {
	        public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	        public Acs_SetVisibleList_Data   m_AcsSetVisibleList;  /*acs Set Visible List event data*/
        };/**/

        /*Acs_3GVConfStop_Data*/
        public struct Acs_3GVConfStop_Data
        {
	        public Acs_Evt_State_t         m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	        public Acs_Evt_ErrCode_t       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	        public DeviceID_t              m_3GVConfDev;
	        public PrivateData_t           m_PrivData;/*private data*/
        };/**/

        /*Acs_3GVConfStop_Evt*/
        public struct Acs_3GVConfStop_Evt
        {
	        public ACS_EVT_HEAD              m_AcsEvtHead;    /*acs event head*/
	        public Acs_3GVConfStop_Data   m_Acs3GVConfStop;  /*acs 3G VConf Stop event data*/
        };/**/

        /*Acs_IO_Evt*/
        public struct Acs_IO_Evt
        {
	        public ACS_EVT_HEAD          m_AcsEvtHead; /*acs event head*/	
	        public Acs_IO_Data           m_AcsIOData;  /*acs io event*/
        };/**/

        /*Acs License Query event*/
        public struct Acs_LicenseQuery_Data
        {
	        public DJ_U8     m_u8ModuleID;          /*license alarm Board module ID*/
	        public DJ_U16    m_u16LicLeftDay;        /*license alarm Board left license days,0: No license or license overdue;100:license forever; else: left license days*/
	        public DJ_S8     m_Rfu1;
        };/**/

        /*Acs_LicenseAlarm_Evt*/
        public struct Acs_LicenseQuery_Evt
        {
	        public ACS_EVT_HEAD              m_AcsEvtHead;       /*acs event head*/
	        public Acs_LicenseQuery_Data     m_LicenseQueryData; /*universal failure confirmation event*/	
        };/**/

        /*Acs_UniFailure_Evt*/
        public struct Acs_UniFailure_Evt
        {
	        public ACS_EVT_HEAD              m_AcsEvtHead;     /*acs event head*/
	        public Acs_UniFailure_Data       m_UniverFailData; /*universal failure confirmation event*/	
        };/**/

        /*Acs_FaxEnd_Data*/
        public unsafe struct Acs_FaxProc_Data
        {
	        public Acs_Evt_State_t        m_s32AcsEvtState;   /*acs event state*/
	        public Acs_Evt_ErrCode_t    m_s32AcsEvtErrCode; /*acs event errcode*/	
	        public DJ_U8                        m_u8ErrorStep;      /*error state of last fax operation*/
	        public DJ_U8                        m_u8T30SendState;   /*the state the T30 command just sent*/
	        public DJ_U8                        m_u8RecvT30Cmd;     /*the T30 command just received*/
	        public DJ_U8                        m_u8Rfu1;            /*Reserved*/ 
	        public DJ_U16                      m_u16TotalPages;    /*total pages,send: sending total pages successfully  ;rev: receiving total pages successfully*/
            public  fixed DJ_S8              m_s8RemoteID[ConstantVar.ACS_REMOTEID_MAX_LEN];/*Remote ID*/	
	        public  fixed DJ_U8              m_u8Rfu2[2];           /*Reserved*/
	        public PrivateData_t            m_PrivData;/*private data*/
        };/**/

        /*Acs_FaxProc_Evt*/
        public struct Acs_FaxProc_Evt
        {
	        public ACS_EVT_HEAD          m_AcsEvtHead;     /*acs event head*/	
	        public Acs_FaxProc_Data      m_AcsFaxProcData; /*acs fax proc data*/
        };/**/

        /*ITP_3GPP_PARAM_CFG*/
        public unsafe struct ITP_3GPP_PARAM_CFG
        {
            public DJ_U8	             m_u8AudioDecodeType;      /*audio decode type*/
            public DJ_U8             m_u8AudioFrameType;       /*audio frame type,reference XMS_AUDIO_AMR_FRAME_TYPE*/
            public DJ_U16	         m_u16AudioDecoderCfgLen;  /*audio decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
            public  fixed DJ_U8    m_u8AudioDecoderCfg[ConstantVar.ACS_MAX_DECODER_CFG_LEN];/*audio decoder cfg*/
            public DJ_U8             m_u8AudioProfiles;        /*audio profiles?*/
            public DJ_U8             m_u8AudioLevel;		  /*audio level ?*/
            public  fixed DJ_U8   m_Rfu1[2];

            public DJ_U8             m_u8VideoDecodeType;      /*video decode type*/
            public DJ_U8             m_u8VideoFrameRate;       /*video frame rate 10 ~ 30*/
            public DJ_U16           m_u16VideoDecoderCfgLen;  /*video decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
            public  fixed DJ_U8   m_u8VideoDecoderCfg[ConstantVar.ACS_MAX_DECODER_CFG_LEN];/*video decoder cfg?*/
            public DJ_U8             m_u8VideoProfiles;        /*video profiles?*/
            public DJ_U8             m_u8VideoLevel;           /*video level?*/
            public  fixed DJ_U8   m_Rfu2[2];  

            public DJ_U32          m_u32TrackNums;           /*track numbers*/
            public DJ_U16          m_u16AudioMaxBitRate;
            public DJ_U16          m_u16AudioAverageBitRate;
            public DJ_U32          m_u32AudioBitMask;
            public DJ_U16          m_u16VideoMaxBitRate;
            public DJ_U16          m_u16VideoAverageBitRate;
            public DJ_U32          m_u32VideoBitMask;
            public DJ_U16          m_u16VideoWidth;
            public DJ_U16          m_u16VideoHeight;
        	
        };/*ITP_3GPP_PARAM_CFG*/

        /*CmdParamData_324CH_t*/
        public struct CmdParamData_324CH_t
        {
	        public DJ_U8	    m_u8Channel_Enable;		/* channel enable flag, 1 - enable, 0 - disable*/
	        public DJ_U8	    m_u8AudioSRC1_Ctrl;		/* audio channel source 1 type */
	        public DJ_U8 	m_u8AudioSRC2_Ctrl;		/* audio channel source 2 type */
	        public DJ_U8	    m_u8VideoSRC1_Ctrl;		/* video channel source type */
	        public DJ_U16	m_u16AudioSRC1_ID;		/* audio channel source 1 id */
	        public DJ_U16	m_u16AudioSRC2_ID;		/* audio channel source 2 id */
	        public DJ_U16	m_u16VideoSRC1_ID;		/* video channel source id */
	        public DJ_U8 	m_u8AudioInDecodeFlag;	/* 1 - input decode, 0 - no decode */
	        public DJ_U8 	m_u8AudioOutEncodeFlag; /* 1 - output encode, 0 - no encode */
	        public DJ_U8 	m_u8AudioInCodec;		/* audio input codec */
	        public DJ_U8	    m_u8AudioOutCodec;		/* audio output codec */
	        public DJ_U8 	m_u8VideoInCodec;		/* video input codec */
	        public DJ_U8 	m_u8VideoOutCodec;		/* video output codec */
        };

        /*EvtH245OLC*/
        public unsafe struct Evt_H245_OLC
        {
	        public DJ_U8	            u8ChannelNumber;// logical channel number
	        public DJ_U8	            u8Direction;	// transmit or receive
	        public DJ_U8	            u8Codec;		// codec type
	        public DJ_U8	            u8DecoderConfigInfoLen;	//decoder Config Length
	        public  fixed DJ_U8	s8DecoderConfigInfo[ConstantVar.MAX_DECODER_CFG_INFO];
        }

        /*EvtH245CLC*/
        public unsafe struct Evt_H245_CLC
        {
	        public DJ_U8	            u8ChannelNumber;// logical channel number
	        public DJ_U8	            u8Direction;	// transmit or receive
	        public  fixed DJ_U8   u8Reserved[2];
        };

        /*EvtH245SIG_PDU*/
        public unsafe struct Evt_H245_SIG_PDU 
        {
	        public  fixed DJ_U8	m_u8H245SigPdu[ConstantVar.ACS_MAX_H245_SIG_PDU_LEN];		/* H.245 signal data */
        };

        /*EvtH245USER_INPUT*/
        public unsafe struct H245_UII
        {
	        public DJ_U8 m_u8Type;		/* type=1: send signal, type=2: send str, type=3: send signal and str */
	        public DJ_S8 m_s8Signal;		
	        public  fixed DJ_S8 str[126];     
        };

        public  struct ITP_3G_FaxToneStruct_t
        {
	        public DJ_U16  m_u16ChanEnable;  // 1: enable; 0: disable
        };/*ITP_3G_FaxToneStruct_t;*/

        public  struct ITP_3G_FaxToneEventStruct_t
        {
	        public DJ_U16   m_u16ChanState;  //1￡ofax_tone; 0: voice tone
        };/*ITP_3G_FaxToneEventStruct_t;*/

        /*Acs_SS7RawFrame_Data*/
        public unsafe struct Acs_SS7RawFrame_Data
        {
	        public DJ_U8           m_u8UserType; /*SS7 frame user type,reference XMS_SS7_FRAME_USER_TYPE*/
	        public DJ_U8           m_u8LinkType; /*SS7 frame link type,reference XMS_SS7_FRAME_LINK_TYPE*/
	        public DJ_U8           m_u8InfoType; /*SS7 frame info type,reference XMS_SS7_FRAME_INFO_TYPE*/
	        public DJ_U8           m_u8InfoLen;  /*SS7 frame info len*/
	        public  fixed DJ_U8  m_u8Rfu1[4];
	        public  fixed DJ_U8  m_u8Info[255];/*SS7 frame info*/
	        public DJ_U8           m_u8Rfu2;
        };/**/

        /*Acs_SS7RawFrame_Evt*/
        public struct Acs_SS7RawFrame_Evt
        {
	        public ACS_EVT_HEAD                       m_AcsEvtHead;         /*acs event head*/	
	        public Acs_SS7RawFrame_Data		  m_AcsSS7RawFrameData; /*acs ss7 ras frame data*/
        } ;/**/


        /*Acs_MediaPrivateExt_Data*/
        public unsafe struct Acs_MediaPrivateExt_Data
        {
	        public DJ_U32          m_u32ExtType;        //reference to XMS_PRIVATE_EXT_TYPE
	        public  fixed DJ_U8  m_u8Buf[ConstantVar.MAX_PATH];
        };/*Acs_MediaPrivateExt_Data*/ 

        /*Acs_MediaECM_OffSet*/
        public struct Acs_MediaECM_OffSet
        {
	        public DJ_U32  m_u32Play_FileOffset; //文件偏移,单位为1bytes
	        public DJ_U32  m_u32Play_Max_Length; //期望放音长度(单位：字节)
        };/*Acs_MediaECM_OffSet*/

        /*Acs_MediaECM_CMD*/
        public class Acs_MediaECM_CMD
        {
	        public DJ_U16  m_u16FrameNums;
	        public DJ_U16  []m_u16Reserved = new DJ_U16[3];
	        public Acs_MediaECM_OffSet []m_stOffSet = new Acs_MediaECM_OffSet[256];
        };/*Acs_MediaECM_CMD*/

        /*Acs_AnalogEM_CMD*/
        public struct Acs_AnalogEM_CMD
        {
	        public DJ_U8	m_u8Channel_Enable;
	        public DJ_U8	m_u8Type;
	        public DJ_U8	m_u8Tx_State;
	        public DJ_U8	m_u8Rx_State;
        };/*Acs_AnalogEM_CMD*/

        /*Acs_SysMon_Data*/
        public unsafe struct Acs_SysMon_Data
        {    
            public DJ_U8                m_u8ModuleType;       /*Module type*/
            public DJ_U8                m_u8UnitID;           /*Module unitid*/        
            public DJ_U16              m_u16ModuleState;     /*Module state,reference XMS_SYSMON_MODSTATE*/        
            public fixed  DJ_S8       m_s8IPAddress[32];    /*Module IP address*/
            public DJ_U32              m_u32Port;            /*Module port*/
            public  fixed DJ_S8       m_s8Rfu[16];          /*rfu*/
        };/**/

        /*Acs_SysMon_Evt*/
        public struct Acs_SysMon_Evt
        {
	        public ACS_EVT_HEAD          m_AcsEvtHead;     /*acs event head*/	
	        public Acs_SysMon_Data       m_AcsSysMonData; /*acs fax proc data*/
        };/**/

        /*Acs_VoIP_Regist_Evt*/
        public struct Acs_VoIP_Regist_Evt
        {
            public ACS_EVT_HEAD	    m_AcsEvtHead;
            public Acs_VoIP_Regist    	    m_AcsRegist;
        };/*Acs_VoIP_Regist_Evt*/

        /*Acs_VoIP_Regist_State_Evt*/
        public struct Acs_VoIP_Regist_State_Evt
        {
            public ACS_EVT_HEAD	    m_AcsEvtHead;
            public Acs_VoIP_REGSTATE	    m_AcsRegistState;
        };/*Acs_VoIP_Regist_State_Evt*/

        /*Acs_VoIP_Regist_Response_Evt*/
        public struct Acs_VoIP_Regist_Response_Evt
        {
            public ACS_EVT_HEAD	    	m_AcsEvtHead;
            public Acs_VoIP_Regist_Response    m_AcsRegistResp;
        };/*Acs_VoIP_Regist_Response_Evt*/

        /*Acs_VoIP_ReferResult_Evt*/
        public struct Acs_VoIP_ReferResult_Evt
        {
            public ACS_EVT_HEAD	    m_AcsEvtHead;
            public Acs_VoIP_ReferResult    m_AcsReferResult;
        };/*Acs_VoIP_ReferResult_Evt*/

        /*Acs_VoIP_MediaInfo_Evt*/
        public struct Acs_VoIP_MediaInfo_Evt
        {
            public ACS_EVT_HEAD	    m_AcsEvtHead;
            public Acs_VoIP_MediaInfo	    m_AcsMediaInfo;
        };/*Acs_VoIP_MediaInfo_Evt*/

        /*Acs_VoIP_RTPSESSION_Evt*/
        public struct Acs_VoIP_RTPSESSION_Evt
        {
            public ACS_EVT_HEAD	    m_AcsEvtHead;
            public Acs_VoIP_RTPSESSION	    m_AcsRtpSession;
        };/*Acs_VoIP_RTPSESSION_Evt*/

        /*Acs_VoIP_RTPADDR_Evt*/
        public struct Acs_VoIP_RTPADDR_Evt
        {
            public ACS_EVT_HEAD	    m_AcsEvtHead;
            public Acs_VoIP_RTPADDR	    m_AcsRtpAddr;
        };/*Acs_VoIP_RTPADDR_Evt*/

        /*Acs_VoIP_RTCPADDR_Evt*/
        public struct Acs_VoIP_RTCPADDR_Evt
        {
            public ACS_EVT_HEAD	    m_AcsEvtHead;
            public Acs_VoIP_RTPADDR	    m_AcsRtcpAddr;
        };/*Acs_VoIP_RTCPADDR_Evt*/

        /*Acs_VoIP_RTPCODEC_Evt*/
        public struct Acs_VoIP_RTPCODEC_Evt
        {
            public ACS_EVT_HEAD	    m_AcsEvtHead;
            public Acs_VoIP_RTPCODEC	    m_AcsRtpCodec;
        };/*Acs_VoIP_RTPCODEC_Evt*/

        /*Acs_UserDef_Evt*/
        public struct Acs_UserDef_Evt
        {
	        public ACS_EVT_HEAD      m_AcsEvtHead;     /*acs event head*/	
            public UserEvt_Head_t     m_UsrEvtHead;     /*User self-define event head*/
        };/**/

        /*Acs_ModRelate_Mod*/
        public unsafe struct Acs_ModRelate_Mod
        {    	
            public DJ_U8                m_u8ModuleType;       /*Module type*/
            public DJ_U8                m_u8UnitID;           /*Module unitid*/        	
	        public DJ_U8                m_u8Flag;             /*Relate flag, 0:upper module; 1:lower module*/ 
            public DJ_S8                m_s8Rfu1;          /*rfu1*/        
            public fixed  DJ_S8      m_s8IPAddress[32];    /*Module IP address*/
            public DJ_U32             m_u32Port;            /*Module port*/
            public  fixed DJ_S8      m_s8Rfu2[4];           /*rfu2*/
        };/**/

        /*Acs_ModRelate_Data*/
        public class Acs_ModRelate_Data
        {    
	        public DJ_U8                m_u8ModCount;         /*Relate module count*/
	        public DJ_U8                m_u8SrcModType;
	        public DJ_U8                m_u8SrcModUnitID;
	        public DJ_S8                m_rfu1;
            public Acs_ModRelate_Mod    []m_RelateMod = new Acs_ModRelate_Mod[64]; /*Relate module info*/    
        };/**/

        /*Acs_ModRelate_Evt*/
        public struct Acs_ModRelate_Evt
        {
	        public ACS_EVT_HEAD          m_AcsEvtHead;     /*acs event head*/	
	        public Acs_ModRelate_Data m_AcsModRelateData; /*acs fax proc data*/
        };/**/

        /*Acs_VoIPMon_Data*/
        public unsafe struct Acs_VoIPMon_Data
        {    
	        public DJ_U32               m_u32DataLen;
	        public  fixed DJ_U8        m_u8MonData[ConstantVar.ITP_VOIP_MONDATA_MAX];     /*VoIP Mon data*/	
        };/**/

        /*Acs_ModRelate_Evt*/
        public struct Acs_VoIPMon_Evt
        {
	        public ACS_EVT_HEAD          m_AcsEvtHead;     /*acs event head*/	
	        public Acs_VoIPMon_Data    m_AcsVoIPMonData; /*acs VoIP mon data*/
        };/**/
        
        public unsafe struct ACS_Digital_PortState_Data
        {
	        public DJ_U8	m_u8Lost_signal;	//1:无信号，0：有信号
	        public DJ_U8	m_u8Fas_align;	//0：同步，1：失步
	        public DJ_U8	m_u8Mf_align; 	//0：同步，1：失步
	        public DJ_U8	m_u8Crc4_align; 	//0：同步，1：失步
	        public DJ_U8	m_u8Remote_alarm; 	//0：无告警，1：远端告警
	        public DJ_U8	m_u8Remote_MF_alarm;	//0：无告警，1：远端告警
	        public DJ_U8	m_u8Rx_level;	//0-15: *(-2.5db)
	        public DJ_U8	m_u8Tx_open;	//1:open circuit,
	        public DJ_U8	m_u8Tx_overlimit;	//1:current over limit
	        public DJ_U8	m_u8Port_Current_State;	//0: error state; 1: normal working state
	        public DJ_U8	m_u8Port_Normal_Count;	//seconds of digital port normal working
	        public DJ_U8	m_u8Port_Error_Count;	// seconds of digital port error
	        public DJ_U32	m_u32total_seconds;	//统计总时间
	        public DJ_U32	m_u32RLOS_seconds;	//接收失步总秒数
	        public DJ_U32 	m_u32LRCL_seconds;	//接收无信号总秒数
	        public DJ_U32 	m_u32RUA1_seconds;	//接收全1信号总秒数
	        public DJ_U32 	m_u32RRA_seconds;	//远端告警总秒数
	        public DJ_U32 	m_u32RDMA_seconds;	//远端CAS复帧告警总秒数
	        public DJ_U32 	m_u32ILUT_seconds;	//接收电平过低总秒数
	        public DJ_U32 	m_u32JALT_seconds;	//抖动超限总秒数
	        public DJ_U32 	m_u32TOCD_seconds;	//发送开路错误总秒数
	        public DJ_U32 	m_u32TCLE_seconds;	//发送短路错误总秒数
	        public DJ_U32 	m_u32RSLIP_seconds;	//接收滑码错误总秒数
	        public DJ_U32 	m_u32TSLIP_seconds;	//发送滑码错误总秒数
	        public DJ_U32 	m_u32LCVCR_count;	//接收线路码型错误总计数
	        public DJ_U32 	m_u32PCVCR_count;	//接收CRC4错误总计数
	        public DJ_U32 	m_u32FOSCR_count;	//接收FAS错误总计数
	        public DJ_U32 	m_u32EBCR_count;		//远端CRC4 E-BIT总计数
	        public DJ_U32	m_u32HDLC1_Tx_packets;	//HDLC1发送包计数
	        public DJ_U32	m_u32HDLC1_Rx_goodpk;	//HDLC1接收正确包计数
	        public DJ_U32	m_u32HDLC1_Rx_badpk;		//HDLC1接收错误包计数
	        public DJ_U32	m_u32HDLC2_Tx_packets;	//HDLC2发送包计数
	        public DJ_U32	m_u32HDLC2_Rx_goodpk;	//HDLC2接收正确包计数
	        public DJ_U32	m_u32HDLC2_Rx_badpk;		//HDLC2接收错误包计数
	        public DJ_U8	m_u8E1Type;		/*E1 type*/
	        public  fixed DJ_U8	m_u8Rfu[3];	/**/
        };

        public struct ACS_Digital_PortState_Evt
        {
            public ACS_EVT_HEAD                       m_AcsEvtHead;
            public ACS_Digital_PortState_Data   m_AcsDigitalPortStateData;
        };

        public unsafe struct ACS_Clock_RefSrc_State_Data
        {
            public DJ_U8     m_u8ModuleID;            /*The Module ID Of DSP*/
            public DJ_U8     m_u8E1ID;                /*The E1 ID Of A DSP*/
            public DJ_U8     m_u8State;               /*The E1's Master Clock Ref Source Of A DSP, Reference to XMS_CLK_STATE_TYPE*/
	        public DJ_U8     m_u8ClockType;           /*Keygoe current clock type is slave or master,Reference XMS_BOARD_CLOCK_TYPE*/
            public fixed DJ_U8     m_u8Ref[4];              /*Reserve*/
        };

        public struct ACS_Clock_RefSrc_State_Evt
        {
            public ACS_EVT_HEAD                           m_AcsEvtHead;
            public ACS_Clock_RefSrc_State_Data   m_AcsClockRefSrcStateData;  
        };

        /* Acs VoIP SIP User Agent struct */
        public unsafe struct Acs_VoIP_SIP_User_Agent
        {
	        public fixed  DJ_S8	m_s8UserAgent[40];	/* Sip User Agent Name with version No */
        };/*Acs_VoIP_SIP_User_Agent*/

        /* Acs VoIP SIP Diversion Information struct */
        public unsafe struct Acs_VoIP_Call_Diversion_Info
        {
	        public fixed DJ_S8	m_s8Diversion[64];	/* Sip Call Diversion URL */
	        public  fixed DJ_S8	m_s8Reason[16];		/* Sip Call Diversion Reason */
        };/*Acs_VoIP_Call_Diversion_Info*/

        public enum XMS_DEVMAIN_TYPE
        {
            XMS_DEVMAIN_CONFIG = 0x01, /*config adding for log manager*/
            XMS_DEVMAIN_VOICE = 0x02, /*Voice device*/
            XMS_DEVMAIN_FAX = 0x03, /*Fax device*/
            XMS_DEVMAIN_DIGITAL_PORT = 0x04, /*Digital Port device*/
            XMS_DEVMAIN_INTERFACE_CH = 0x05, /*Interface Ch device*/
            XMS_DEVMAIN_DSS1_LINK = 0x06, /*DSS1 Link device*/
            XMS_DEVMAIN_SS7_LINK = 0x07, /*SS7 Link device*/
            XMS_DEVMAIN_BOARD = 0x08, /*DSP Board device*/
            XMS_DEVMAIN_CTBUS_TS = 0x09, /*CTBus ts device*/
            XMS_DEVMAIN_RTP = 0x0A, /*VoIP device*/
            XMS_DEVMAIN_MEDIAEX = 0x0B, /*MediaEx device*/
            XMS_DEVMAIN_CONFERENCE = 0x0C, /*Conference Group Device*/
            XMS_DEVMAIN_VIDEO = 0x0D, /*Video device*/
            XMS_DEVMAIN_CTX = 0x10, /*Ctx device*/
            XMS_DEVMAIN_RTPX = 0x11, /*RTPX device*/
            XMS_DEVMAIN_VOIP = 0x12, /*VoIP device*/
            XMS_DEVMAIN_VIDEOCONF = 0x1F, /*Video Conference Device*/
        };

        public enum XMS_CAP_DIRECTION
        {
	        XMS_CAP_DIR_RX    = 1,
	        XMS_CAP_DIR_TX    = 2,
	        XMS_CAP_DIR_RXTX   = 3,
        };

        public enum XMS_DRS_CALL_DIRECT_DEF
        {
            XMS_DRS_CALL_DIRECT_CALL_IN = 0,
            XMS_DRS_CALL_DIRECT_CALL_OUT = 1,
        };

        public enum XMS_INTERFACE_DEVSUB_TYPE
        {
            XMS_DEVSUB_BASE = 0x0,  /*Base*/
            XMS_DEVSUB_ANALOG_TRUNK = 0x01, /*Analog Trunk*/
            XMS_DEVSUB_ANALOG_USER = 0x02, /*Analog User*/
            XMS_DEVSUB_ANALOG_HIZ = 0x03, /*Analog Hiz*/
            XMS_DEVSUB_ANALOG_EMPTY = 0x04, /*Analog Empty*/
            XMS_DEVSUB_E1_PCM = 0x05, /*E1 PCM*/
            XMS_DEVSUB_E1_CAS = 0x06, /*E1 CAS*/
            XMS_DEVSUB_E1_DSS1 = 0x07, /*E1 DSS1*/
            XMS_DEVSUB_E1_SS7_TUP = 0x08, /*E1 SS7 TUP*/
            XMS_DEVSUB_E1_SS7_ISUP = 0x09, /*E1 SS7 ISUP*/
            XMS_DEVSUB_ANALOG_VOC2W = 0x0A, /*Voice only 2 wire*/
            XMS_DEVSUB_ANALOG_VOC4W = 0x0B, /*Voice only 4 wire*/
            XMS_DEVSUB_ANALOG_EM = 0x0C, /*EM control module*/
            XMS_DEVSUB_ANALOG_MAG = 0x0D, /*magnetic module*/
            XMS_DEVSUB_E1_DCH = 0x0E, /*E1 6D25B's Dchannel*/
            XMS_DEVSUB_E1_BCH = 0x0F, /*E1 6D25B's Bchannel*/
            XMS_DEVSUB_UNUSABLE = 0x10, /*unusable timeslot, such as ts0 of E1*/
            XMS_DEVSUB_HIZ_CAS = 0x11, /*Hiz Cas*/
            XMS_DEVSUB_HIZ_PRI = 0x12, /*Hiz Pri*/
            XMS_DEVSUB_HIZ_SS7 = 0x13, /*Hiz ss7*/
            XMS_DEVSUB_HIZ_PRI_LINK = 0x14, /*Hiz pri link*/
            XMS_DEVSUB_HIZ_SS7_64K_LINK = 0x15, /*Hiz ss7 64k link*/
            XMS_DEVSUB_HIZ_SS7_2M_LINK = 0x16, /*Hiz ss7 2M link*/
            XMS_DEVSUB_SS7_LINK = 0x17, /*ss7 link*/
            XMS_DEVSUB_LINESIDE = 0x18, /*LineSide E1*/
            XMS_DEVSUB_ANALOG_REC = 0x19, /*Analog phone Record*/
            XMS_DEVSUB_HIZ_HDLC_N64K_LINK = 0x1A, /*Hiz n*64K */
            XMS_DEVSUB_SS7_2M_LINK = 0x1B, /*SS7 2M LINK*/
            XMS_DEVSUB_HIZ_HDLC = 0x1C, /*Hiz */
            XMS_DEVSUB_DIGITAL_REC = 0x20, /*Digital phone Record*/
        };

        public enum XMS_E1_TYPE
        {
            XMS_E1_TYPE_NULL = 0,
            XMS_E1_TYPE_Analog30 = 1, /* Analog Interface 30*/
            XMS_E1_TYPE_PCM31 = 2, /* E1 Frame,ts31*/
            XMS_E1_TYPE_PCM30 = 3, /* E1 Frame,ts 30*/
            XMS_E1_TYPE_CAS = 4, /* E1 Frame,CAS*/
            XMS_E1_TYPE_PRI = 5, /* E1 Frame,PRI*/
            XMS_E1_TYPE_SS7_TUP_0_Link = 6, /* E1 Frame,TUP: 0 link*/
            XMS_E1_TYPE_SS7_TUP_1_Link = 7, /* E1 Frame,TUP: 1 link*/
            XMS_E1_TYPE_SS7_TUP_2_Link = 8, /* E1 Frame,TUP: 2 link*/
            XMS_T1_TYPE_D4 = 9, /* T1 Frame*/
            XMS_T1_TYPE_ESF = 10, /* T1 Frame*/
            XMS_J1_TYPE_D4 = 11, /* J1 Frame*/
            XMS_J1_TYPE_ESF = 12, /* J1 Frame*/
            XMS_SLC_TYPE_96 = 13, /* SLC_96 Frame*/
            XMS_E1_TYPE_SS7_ISUP_0_Link = 14, /* E1 Frame,ISUP: 0 link*/
            XMS_E1_TYPE_SS7_ISUP_1_Link = 15, /* E1 Frame,ISUP: 1 link*/
            XMS_E1_TYPE_SS7_ISUP_2_Link = 16, /*E1 Frame,ISUP: 2 link*/
            XMS_E1_TYPE_6D25B = 17, /* E1 Frame, 6 DChannel,25 BChannel*/
            XMS_E1_TYPE_1D30B = 18, /*E1 Frame, 1 DChannel, 30 BChannel*/
            XMS_E1_TYPE_11D20B = 19, /*E1 Frame, 11 DChannel, 20 BChannel*/
            XMS_E1_TYPE_HIZ_CAS = 20, /*E1 Frame, HIZ CAS*/
            XMS_E1_TYPE_HIZ_PRI = 21, /*E1 Frame, HIZ PRI*/
            XMS_E1_TYPE_HIZ_SS7 = 22, /*E1 Frame, HIZ SS7*/
            XMS_E1_TYPE_HIZ_64K_SS7 = 23, /*E1 Frame, HIZ pure 64k SS7*/
            XMS_E1_TYPE_HIZ_2M_SS7 = 24, /*E1 Frame, HIZ 2M SS7*/
            XMS_E1_TYPE_LINESIDE = 25, /*E1 Frame, lineside*/
            XMS_E1_TYPE_HIZ_N64K_HDLC = 26, /*E1 Frame, HIZ N*64K HDLC*/
            XMS_E1_TYPE_2M_SS7 = 27, /*E1 Frame, 2M SS7*/
        };

        public enum XMS_MEDIA_DEVSUB_TYPE
        {
            XMS_DEVSUB_MEDIA_VOC = 0x0,  /*voc device*/
            XMS_DEVSUB_MEDIA_324 = 0x1,  /*324 device*/
            XMS_DEVSUB_MEDIA_RAW = 0x2,	 /*Raw device*/
        };

        public enum XMS_CTBUS_DEVSUB_TYPE
        {
            XMS_DEVSUB_CTBUS_LINK = 0x0, /*CTBus link ts*/
            XMS_DEVSUB_CTBUS_CTX = 0x1, /*CTBus CTX ts*/
        };

        /* Analog Trunk Device Params */
        public enum XMS_ANALOGTRUNK_PARAM_TYPE
        {
	        ANALOGTRUNK_PARAM_UNIPARAM = 0,
	        ANALOGTRUNK_PARAM_SETFLASH = 1,
	        ANALOGTRUNK_PARAM_UNSETUNIPARAM = 2 ,//added by jerry for UnSet UniParam(id = 0 )....
	        ANALOGTRUNK_PARAM_UNBINDVOC     = 3 ,//Added by jerry For UnBind Voc From AnalogTrunk
            ANALOGTRUNK_PARAM_READSN        = 4 ,//get TRUNK's SN
	        ANALOGTRUNK_PARAM_GET_VOLTAGE   = 5 ,//get TRUNK's voltage
        };

        /* Analog User Device Params */
        public enum XMS_ANALOGUSER_PARAM_TYPE
        {
	        ANALOGUSER_PARAM_UNIPARAM      = 0,	
	        ANALOGUSER_PARAM_UNBINDVOC     = 3 ,//Added by jerry For UnBind Voc From AnalogUser
            ANALOGUSER_PARAM_READSN        = 4, //get AnalogUser's SN
	        ANALOGUSER_PARAM_GET_VOLTAGE   = 5, //Get AnalogUser's voltage
        };

        public enum XMS_PLAY_TYPE
        {
	        XMS_PLAY_TYPE_FILE               = 0x0,
	        XMS_PLAY_TYPE_INDEX              = 0x1,
	        XMS_PLAY_TYPE_FILE_QUEUE         = 0x2,
	        XMS_PLAY_TYPE_INDEX_QUEUE        = 0x3,
        };

        /* Event class define*/
        public enum XMS_EVT_CLASS
        {
            XMS_EVT_CLASS_GENERAL = 0x0001,
            XMS_EVT_CLASS_CALLCONTROL = 0x0002,
            XMS_EVT_CLASS_CONFPROC = 0x0003,
            XMS_EVT_CLASS_VOIPPROC = 0x0004,
            XMS_EVT_CLASS_MEDIAPROC = 0x0005,
            XMS_EVT_CLASS_FAXPROC = 0x0006,
            XMS_EVT_CLASS_IOPROC = 0x0007,
            XMS_EVT_CLASS_SYSMONITOR = 0x0008,
            XMS_EVT_CLASS_UNIFAILURE = 0x0009,
        };

        /*Event type define */
        public enum XMS_EVT_TYPE
        {
            XMS_EVT_OPEN_STREAM = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x01),
            XMS_EVT_QUERY_DEVICE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x02),
            XMS_EVT_QUERY_DEVICE_END = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x03),
            XMS_EVT_OPEN_DEVICE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x04),
            XMS_EVT_CLOSE_DEVICE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x05),
            XMS_EVT_RESET_DEVICE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x06),
            XMS_EVT_DEVICESTATE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x07),
            XMS_EVT_SETDEV_GROUP = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x08),
            XMS_EVT_SETPARAM = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x09),
            XMS_EVT_GETPARAM = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x0A),
            XMS_EVT_QUERY_ONE_DSP_START = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x0B),
            XMS_EVT_QUERY_ONE_DSP_END = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x0C),
            XMS_EVT_QUERY_REMOVE_ONE_DSP_START = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x0D),
            XMS_EVT_QUERY_REMOVE_ONE_DSP_END = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x0E),
            XMS_EVT_OPEN_STREAM_EXT = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x0F),
            XMS_EVT_LICENSE_QUERY = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x10),
            XMS_EVT_CLOSE_STREAM_EXT = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x11),
            XMS_EVT_MASTER_STATE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x13),
            XMS_EVT_SLAVE_WORK_STATE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x14),
            XMS_EVT_E1STATE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x20),
            XMS_EVT_CTBUS_CLK_REF_SRC_STATE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x30),
            XMS_EVT_USER_DEF = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0xE0),
            XMS_EVT_BAKSYS_STOP = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0xF0),
            XMS_EVT_ACS_TIMER = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0xFF),

            XMS_EVT_CALLOUT = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x01),
            XMS_EVT_CALLIN = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x02),
            XMS_EVT_ALERTCALL = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x03),
            XMS_EVT_ANSWERCALL = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x04),
            XMS_EVT_LINKDEVICE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x05),
            XMS_EVT_UNLINKDEVICE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x06),
            XMS_EVT_CLEARCALL = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x07),
            XMS_EVT_ANALOG_INTERFACE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x08),
            XMS_EVT_CAS_MFC_START = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x09),
            XMS_EVT_CAS_MFC_END = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x0A),
            XMS_EVT_SENDSIGMSG = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x0B),
            XMS_EVT_SIGMON = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x0C),
            XMS_EVT_3G324M = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x0D),
            XMS_EVT_CTX_REG = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x0E),
            XMS_EVT_CTX_LINK = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x0F),
            XMS_EVT_CTX_APPDATA = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x10),
            XMS_EVT_DRS_CALL_NUMS = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x11),


            XMS_EVT_SS7RawFrame = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x20),
            XMS_EVT_SS7SendRawFrame = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL << 16) + 0x21),


            XMS_EVT_JOINTOCONF = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CONFPROC << 16) + 0x01),
            XMS_EVT_LEAVEFROMCONF = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CONFPROC << 16) + 0x02),
            XMS_EVT_CLEARCONF = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CONFPROC << 16) + 0x03),

            XMS_EVT_SET_PAYLOAD = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC << 16) + 0x01),
            XMS_EVT_SET_RTPADDR = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC << 16) + 0x02),
            XMS_EVT_SET_RTCPADDR = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC << 16) + 0x03),
            XMS_EVT_SET_RTPCODEC = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC << 16) + 0x04),
            XMS_EVT_SET_MEDIAINFO = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC << 16) + 0x05),
            XMS_EVT_REFER_RESULT = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC << 16) + 0x06),
            XMS_EVT_REGIST = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC << 16) + 0x07),
            XMS_EVT_REGIST_RESP = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC << 16) + 0x08),

            XMS_EVT_PLAY = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x01),
            XMS_EVT_INITINDEX = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x02),
            XMS_EVT_BUILDINDEX = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x03),
            XMS_EVT_CONTROLPLAY = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x04),
            XMS_EVT_RECORD = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x05),
            XMS_EVT_CONTROLRECORD = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x06),
            XMS_EVT_RECORDCSP = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x07),
            XMS_EVT_CONTROLRECORDCSP = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x08),
            XMS_EVT_3GPP_PLAY = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x09),
            XMS_EVT_3GPP_CONTROLPLAY = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x0A),
            XMS_EVT_3GPP_RECORD = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x0B),
            XMS_EVT_3GPP_CONTROLRECORD = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x0C),
            XMS_EVT_PLAYCSPREQ = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x0D),
            XMS_EVT_3GPP_INIT_INDEX = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x0E),
            XMS_EVT_3GPP_BUILD_INDEX = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x0F),

            XMS_EVT_3GVCONF_JOIN = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x10),
            XMS_EVT_3GVCONF_LEAVE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x11),
            XMS_EVT_3GVCONF_CLEAR = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x12),
            XMS_EVT_3GVCONF_GETLAYOUT = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x13),
            XMS_EVT_3GVCONF_SETLAYOUT = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x14),
            XMS_EVT_3GVCONF_GETVISIBLELIST = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x15),
            XMS_EVT_3GVCONF_SETVISIBLELIST = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x16),
            XMS_EVT_3GVCONF_STOP = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC << 16) + 0x17),

            XMS_EVT_SENDFAX = ((XMS_EVT_CLASS.XMS_EVT_CLASS_FAXPROC << 16) + 0x01),
            XMS_EVT_RECVFAX = ((XMS_EVT_CLASS.XMS_EVT_CLASS_FAXPROC << 16) + 0x02),

            XMS_EVT_SENDIODATA = ((XMS_EVT_CLASS.XMS_EVT_CLASS_IOPROC << 16) + 0x01),
            XMS_EVT_RECVIODATA = ((XMS_EVT_CLASS.XMS_EVT_CLASS_IOPROC << 16) + 0x02),

            XMS_EVT_MODMONITOR = ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR << 16) + 0x01),
            XMS_EVT_DEV_TIMER = ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR << 16) + 0x02),
            XMS_EVT_MODRELATE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR << 16) + 0x03),
            XMS_EVT_VOIPMON = ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR << 16) + 0x04),

            XMS_EVT_UNIFAILURE = ((XMS_EVT_CLASS.XMS_EVT_CLASS_UNIFAILURE << 16) + 0x01),
        };

        /* Board Device Params */
        public enum XMS_BOARD_PARAM_TYPE
		{
			BOARD_PARAM_GETBOARDINFO          = 0,
			BOARD_PARAM_SETFSK                = 1,
			BOARD_PARAM_SETFLASH              = 2,
			BOARD_PARAM_SETGTDFREQ            = 3,
			BOARD_PARAM_SETGTDTONE            = 4,
			BOARD_PARAM_SETTRUNKFLASH         = 5,
			BOARD_PARAM_SETGTGFREQ            = 6, //GTG Freq
			BOARD_PARAM_SETGTGTONE            = 7, //GTG Tone
			BOARD_PARAM_SETVSD                = 8, //VSD
			BOARD_PARAM_SET_ACTIVE_MEM_VAD    = 9, //ACTIVE MEM VAD
   		    BOARD_PARAM_SETCTCLK              = 10,     
  			BOARD_PARAM_SET_MIN_VAD           = 11, //ACTIVE MEM VAD           
			BOARD_PARAM_SET_COMMON_CFG        = 12, //COMMON CFG 
			BOARD_PARAM_SET_RST_MASTER        = 13, //
		};

        public enum XMS_CTRL_RECORD_TYPE
		{
			XMS_STOP_RECORD                   = 0x0,
			XMS_PAUSE_RECORD                  = 0x1,
			XMS_RESUME_RECORD                 = 0x2,
			XMS_STEP_BACKWARD_RECORD          = 0x3,

			XMS_CSP_STOP_RECORD               = 0x4,
			XMS_CSP_PAUSE_RECORD              = 0x5,
			XMS_CSP_RESUME_RECORD             = 0x6,
			XMS_CSP_STEP_BACKWARD_RECORD      = 0x7,
			XMS_CSP_DELAY_STOP_RECORD         = 0x8,
		};

        public enum XMS_MEDIA_IO_TYPE
		{		
			XMS_IO_TYPE_DTMF                = 1,
			XMS_IO_TYPE_MR2F                = 2,
			XMS_IO_TYPE_MR2B                = 3,
			XMS_IO_TYPE_GTG                 = 4,
			XMS_IO_TYPE_GTD                 = 4,
			XMS_IO_TYPE_FSK                 = 5,
			XMS_IO_TYPE_DPD                 = 6,
			XMS_IO_TYPE_PVD                 = 7,
			XMS_IO_TYPE_MSK                 = 8,
			XMS_IO_TYPE_VSD                 = 9,
			XMS_IO_TYPE_MSKREND             = 10,
			XMS_IO_TYPE_DRS                 = 11,
		};

        /* CAS Device Params */
        public enum XMS_CAS_PARAM_TYPE
        {
	        CAS_PARAM_UNIPARAM = 0,
            CAS_PARAM_MFCTYPE  = 1,
            CAS_PARAM_CALLTYPE      = 2,    //0 all (default)  1 逐位拨号 CmdParamData_CAS->m_u8CallType;
            CAS_PARAM_APPENDCALLEE  = 3,    //CmdParamData_CAS->m_u8AppendCallee 一次一位
        };

        /* Media Device Params */
        public enum XMS_VOC_PARAM_TYPE
        {
	        VOC_PARAM_UNIPARAM     = 0,// set universal vocice parameters.
	        VOC_PARAM_BREAKEN_CALL = 1,// added by jerry for keyInterrupet .08.02.19
	        VOC_PARAM_3GFAXTONE    = 2,// added by jerry for 3G FaxTone Eanble or Disable 08.02.20
        };

        public enum XMS_BUILD_INDEX_TYPE
        {
	        XMS_BUILD_INDEX_RAM              = 0x4,
	        XMS_BUILD_INDEX_FILE             = 0x5,
        };

        public enum XMS_CTRL_PLAY_TYPE
        {
	        XMS_STOP_PLAY                    = 0x0,
	        XMS_PAUSE_PLAY                   = 0x1,
	        XMS_RESUME_PLAY                  = 0x2,
	        XMS_STEP_BACKWARD_PLAY           = 0x3,
	        XMS_STEP_FORWARD_PLAY            = 0x4,

	        XMS_CSP_STOP_PLAY                = 0x5,
	        XMS_CSP_PAUSE_PLAY               = 0x6,
	        XMS_CSP_RESUME_PLAY              = 0x7,
	        XMS_CSP_STEP_BACKWARD_PLAY       = 0x8,
	        XMS_CSP_STEP_FORWARD_PLAY        = 0x9,
	        XMS_CSP_DELAY_STOP_PLAY          = 0xA,
         };

        /*E1 STATE BITS DEFINE*/
        public enum XMS_E1PORT_MASK_STATE
        {
            XMS_E1PORT_MASK_LOST_SIGNAL = 0x00000001,
            XMS_E1PORT_MASK_FAS_ALARM = 0x00000002,
            XMS_E1PORT_MASK_MFAS_ALARM = 0x00000004,
            XMS_E1PORT_MASK_CRC4_ALARM = 0x00000008,
            XMS_E1PORT_MASK_REMOTE_ALARM = 0x00000010,
            XMS_E1PORT_MASK_REMOTE_MF_ALARM = 0x00000020,
            XMS_E1PORT_MASK_TX_OPEN_ALARM = 0x00000040,
            XMS_E1PORT_MASK_TX_SHORT_ALARM = 0x00000080,
            XMS_E1PORT_MASK_RX_LEVEL = 0x00000F00,
            XMS_E1PORT_MASK_TYPE = 0x00FF0000,
        };

    /*Error code define*/
        public enum ERROR_CODE
        {
            ACSPOSITIVE_ACK = 0x01,
            ACSERR_LOADLIBERR = 0x01,
            ACSERR_BADPARAMETER = 0x02,
            ACSERR_NOSERVER = 0x03,
            ACSERR_MAXCONN_EXCEED = 0x04,
            ACSERR_BADHDL = 0x05,
            ACSERR_FAILSEND = 0x06,
            ACSERR_LINKBROKEN = 0x07,
            ACSERR_NOMESSAGE = 0x08,
            ACSERR_GETRESFAIL = 0x09,
            ACSERR_NOSUPPORTCMD = 0x0A,
            ACSERR_DEVICEERR = 0x0B,
            ACSERR_CTX_REGOVERRUN = 0x0C,
            ACSERR_CTX_REG_NAMEEXIS = 0x0D,
            ACSERR_CTX_UNREG_NOREG = 0x0E,
            ACSERR_CTX_TRAN_NODEST = 0x0F,
            ACSERR_CTX_TRAN_NOSRC = 0x10,
            ACSERR_CTX_LINK_FAIL = 0x11,
            ACSERR_CTX_APPDATA_NODEST = 0x12,
            ACSERR_CTX_APPDATA_NOSRC = 0x13,
        };

        public enum XMS_VOIP_PROTOCOL_TYPE
        {
            XMS_VOIP_PROTOCOL_H323 = 0x1, /*VoIP H323 protocol*/
            XMS_VOIP_PROTOCOL_SIP = 0x2, /*VoIP SIP protocol*/
        };

        public enum XMS_VOC_SRC_MODE
        {
            XMS_SRC_8K = 0x0,
            XMS_SRC_6K = 0x1,
            XMS_SRC_GTG = 0x2,
            XMS_SRC_FSK = 0x3,
            XMS_SRC_RTP = 0x4,
            XMS_SRC_FAX = 0x5,
            XMS_SRC_3GVIDEO = 0x6,
            XMS_SRC_11K = 0x7,
            XMS_SRC_FAX_ECM = 0x8,
        };

         public   enum XMS_VOC_CODE_TYPE
        {
	        XMS_Alaw_type                    = 0x0,
	        XMS_Ulaw_type                    = 0x1,
	        XMS_Vox_type                     = 0x2,
	        XMS_Linear_8bit                  = 0x3,
	        XMS_Linear_16bit                 = 0x4,
	        XMS_Amr_type                     = 0x5,
	        XMS_G723_type                    = 0x6,
	        XMS_CODE_STREAM                  = 0x7,
        };

        public enum XMS_PLAYREC_STOP_MODE
        {
	        XMS_Normal_Stop                  = 0x0,
	        XMS_Single_Code                  = 0x1,
	        XMS_Any_Code                     = 0x2,
        };

        public enum XMS_CSPREC_TYPE
        {
	        XMS_CSPREC_NONE                  = 0x0,
	        XMS_CSPREC_BARGEIN               = 0x1,
	        XMS_CSPREC_NON_BARGEIN           = 0x2,
        };

        enum XMS_CSPREC_PRIV_TYPE
        {
	        XMS_CSPREC_PRIV_CMD              = 0x0,
        };

        public enum XMS_CSPREC_CMD_OPT
        {
	        XMS_CSPREC_CMD_NORMAL            = 0x0,
	        XMS_CSPREC_CMD_DIRECT            = 0x1,
        };

        public enum XMS_CONTROL_CSPREC_PRIV_TYPE
        {
	        XMS_CONTROL_CSPREC_PRIV_CMD      = 0x0,
        };

        public enum XMS_CONTROL_CSPREC_CMD_OPT
        {
	        XMS_CONTROL_CSPREC_CMD_NORMAL    = 0x0,
	        XMS_CONTROL_CSPREC_CMD_DIRECT    = 0x1,
        };

        public enum XMS_CFG_TYPE
        {
	        XMS_CFG_TYPE_NON_INDEX           = 0x0,
	        XMS_CFG_TYPE_INDEX               = 0x1,
        };

        public enum XMS_PLAY_GAIN_MODE
        {
	        XMS_PLAY_GAIN_MODE_NOCHANGE     = 0x0,
	        XMS_PLAY_GAIN_MODE_FIX          = 0x1,
	        XMS_PLAY_GAIN_MODE_ALS          = 0x2,
	        XMS_PLAY_GAIN_MODE_AGC          = 0x3,
        };

        public enum XMS_VOC_OUTPUT_TYPE
        {
	        XMS_VOC_OUTPUT_SILENCE           = 0x0,
	        XMS_VOC_OUTPUT_FROM_INPUT        = 0x1,
	        XMS_VOC_OUTPUT_FROM_PLAY         = 0x2,
	        XMS_VOC_OUTPUT_FROM_MIXER        = 0x3, 	
        };

        public enum XMS_MIXER_TYPE
        {
	        XMS_MIXER_FROM_NULL              = 0x00,
	        XMS_MIXER_FROM_INPUT             = 0x01,
	        XMS_MIXER_FROM_PLAY              = 0x02,
	        XMS_MIXER_FROM_CONF              = 0x03,
	        XMS_MIXER_FROM_IP                = 0x04,
	        XMS_MIXER_FROM_324               = 0x05,
	        XMS_MIXER_FROM_RTPX              = 0x06,
        };

        public enum XMS_AGC_MODE
        {
	        XMS_AGC_MODE_ALS		          = 0x00,
	        XMS_AGC_MODE_AGC		          = 0x01,
        };

        public enum XMS_EC_REF
        {
	        XMS_EC_REF_FROM_INPUT		      = 0x00,
	        XMS_EC_REF_FROM_OUTPUT		      = 0x01,
        };

        public enum XMS_CONF_INPUT_OPT
        {
	        XMS_CONF_INPUT_OPT_SILENCE        = 0x0,
	        XMS_CONF_INPUT_OPT_NORMAL         = 0x1,
	        XMS_CONF_INPUT_OPT_PLAY           = 0x2,	
        };

        public enum XMS_CONF_OUTPUT_OPT
        {
	        XMS_CONF_OUTPUT_OPT_SILENCE		  = 0x0,
	        XMS_CONF_OUTPUT_OPT_NORMAL	      = 0x1,
	        XMS_CONF_OUTPUT_OPT_SUM	          = 0x2,
        };

        public enum XMS_REC_DELAY_STOP_SWITCH
        {
	        XMS_REC_DELAY_STOP_DISABLE        = 0x0,
	        XMS_REC_DELAY_STOP_ENABLE         = 0x1,
        };

        public enum XMS_REC_OPENFILE_TYPE
        {
	        XMS_REC_FILE_TRUNC                = 0x0,
	        XMS_REC_FILE_APPEND               = 0x1,
        };

        public enum XMS_AUDIO_TRACKS
        {
	        XMS_AUDIO_TRACKS_MONO             = 0x1,
	        XMS_AUDIO_TRACKS_STEREO           = 0x2,
        };

        public enum XMS_VIDEO_CODE_TYPE
        {
	        XMS_VIDEO_CODE_TYPE_H263P      = 0x1,
            XMS_VIDEO_CODE_TYPE_H263       = 0x2,
            XMS_VIDEO_CODE_TYPE_MP4V       = 0x3,   
	        XMS_VIDEO_CODE_TYPE_H264       = 0x4,
        };

        public enum XMS_AUDIO_AMR_FRAME_TYPE
        {
	        XMS_AMR_FRAME_TYPE_4_75              = 0x0,
	        XMS_AMR_FRAME_TYPE_5_15              = 0x1,
	        XMS_AMR_FRAME_TYPE_5_90              = 0x2,
	        XMS_AMR_FRAME_TYPE_6_70              = 0x3,
	        XMS_AMR_FRAME_TYPE_7_40              = 0x4,
	        XMS_AMR_FRAME_TYPE_7_95              = 0x5,
	        XMS_AMR_FRAME_TYPE_10_2              = 0x6,
	        XMS_AMR_FRAME_TYPE_12_2              = 0x7,
	        XMS_AMR_FRAME_TYPE_AMR_SID           = 0x8,
	        XMS_AMR_FRAME_TYPE_GSM_EFR_SID       = 0x9,
	        XMS_AMR_FRAME_TYPE_TDMA_EFR_SID      = 0xA,
	        XMS_AMR_FRAME_TYPE_PDC_EFR_SID       = 0xB,
	        XMS_AMR_FRAME_TYPE_RESERVED1         = 0xC,
	        XMS_AMR_FRAME_TYPE_RESERVED2         = 0xD,
	        XMS_AMR_FRAME_TYPE_RESERVED3         = 0xE,
	        XMS_AMR_FRAME_TYPE_NO_DATA           = 0xF,
        };

        public enum XMS_CSPPLAY_DATA_TYPE
        {
	        XMS_CSPPLAY_DATA_VOC                 = 0x0,
	        XMS_CSPPLAY_DATA_VIDEO               = 0x1,
        };

        public enum XMS_PRIVATE_EXT_TYPE
        {
                XMS_EXT_TYPE_PATH                    = 0x01,             //extend to path's size from 128 to 260
        };

        public enum XMS_BOARD_PRIVATE_EXT_TYPE
        {
	        XMS_BOARD_EXT_TYPE_NULL              = 0x00,             //nothing will excute
            XMS_BOARD_EXT_TYPE_CLOCK             = 0x01,             //extend to main clock in keygoe system
        };

        /*It will be replaced by XMS_BOARD_CLOCK_MODE later from V3.0.0*/
        public enum XMS_BOARD_EXT_CLOCK_TYPE
        {
	        XMS_BOARD_EXT_CLOCK_NO_SET           = 0x00,             //extend to main clock in keygoe system
                XMS_BOARD_EXT_CLOCK_SET              = 0x01,             //extend to main clock in keygoe system
        };

        public enum XMS_BOARD_CLOCK_TYPE
        {
            XMS_BOARD_EXT_CLOCK_TYPE_SLAVE       = 0x01,             //current board set slave clock to the peer CO
	        XMS_BOARD_EXT_CLOCK_TYPE_MASTER      = 0x02,             //current board set master clock to the peer CO         
        };

        public enum XMS_BOARD_CLOCK_MODE
        {
            XMS_BOARD_CLOCK_MODE_AUTO = XMS_BOARD_EXT_CLOCK_TYPE.XMS_BOARD_EXT_CLOCK_NO_SET,     //clock set by Keygoe
            XMS_BOARD_CLOCK_MODE_MANUAL = XMS_BOARD_EXT_CLOCK_TYPE.XMS_BOARD_EXT_CLOCK_SET,        //clock set by user-app
        };

        public  enum XMS_ANALOG_TRUNK_CALLERID_OPT
        {
	        XMS_ANALOG_TRUNK_CALLERID_DISABLE      = 0x0,
	        XMS_ANALOG_TRUNK_CALLERID_FSK          = 0x1,
	        XMS_ANALOG_TRUNK_CALLERID_DTMF         = 0x2,
	        XMS_ANALOG_TRUNK_CALLERID_FSKORDTMF    = 0x3,
        };

        public enum XMS_ANALOG_TRUNK_DIALTONE_DETECT_OPT
        {
	        XMS_ANALOG_TRUNK_DIALTONE_DONTDETECT   = 0x0,
	        XMS_ANALOG_TRUNK_DIALTONE_DETECT       = 0x1,
        };

        public enum XMS_ANALOG_TRUNK_CALLOUT_METHOD_OPT
        {
	        XMS_ANALOG_TRUNK_CALLOUT_APP_FULLCONTROL     = 0x0,
	        XMS_ANALOG_TRUNK_CALLOUT_NORMAL_PROGRESS     = 0x1,
	        XMS_ANALOG_TRUNK_CALLOUT_POLARITY_REVERSE    = 0x2,
        };

        public enum XMS_ANALOG_USER_CALLERID_OPT
        {
	        XMS_ANALOG_USER_CALLERID_DSIABLE            = 0x0,
	        XMS_ANALOG_USER_CALLERID_FSK                = 0x1,
	        XMS_ANALOG_USER_CALLERID_DTMF               = 0x2,
        };

        public enum XMS_ANALOG_USER_RINGCADENCE_TYPE
        {
	        XMS_ANALOG_USER_RINGCADENCE_SINGLEPULSE    = 0x0,
	        XMS_ANALOG_USER_RINGCADENCE_DOUBLEPULSE    = 0x1,
	        XMS_ANALOG_USER_RINGCADENCE_TRIPLEPULSE    = 0x2,
        };

        public enum XMS_ANALOG_USER_CALLIN_METHOD_TYPE
        {
	        XMS_ANALOG_USER_CALLIN_METHOD_APP_FULLCONTROL    = 0x0,
	        XMS_ANALOG_USER_CALLIN_METHOD_AUTO_RECVCALLEE    = 0x1,
        };

        public enum XMS_FAX_MODEM_TYPE
        {
	        XMS_F48_Modem                        = 0x0,
	        XMS_F96_Modem                        = 0x1,
	        XMS_F144_Modem                       = 0x2,
        };

        public enum XMS_FAX_BPS_TYPE
        {
	        XMS_BPS_2400                         = 0x0,
	        XMS_BPS_4800                         = 0x1,
	        XMS_BPS_7200                         = 0x2,
	        XMS_BPS_9600                         = 0x3,
	        XMS_BPS_12000                        = 0x4,
	        XMS_BPS_14400                        = 0x5,
        };

        public enum XMS_FAX_T4_TYPE
        {
	        XMS_T4_Low_Dencity                   = 0x0,
	        XMS_T4_High_Dencity                  = 0x1,
	        XMS_T4_MH_Encode                     = 0x0,
	        XMS_T4_MR_Encode                     = 0x1,
        };

        public enum XMS_FAX_LINE_PIXEL_TYPE
        {
	        XMS_Line_Pixel_1728                  = 0x0,
	        XMS_Line_Pixel_2048                  = 0x1,
	        XMS_Line_Pixel_2432                  = 0x2,
	        XMS_Line_Pixel_3456                  = 0x3,
	        XMS_Line_Pixel_4096                  = 0x4,
	        XMS_Line_Pixel_4864                  = 0x5,
        };

        public enum XMS_FAX_PAGE_LENGTH
        {
	        XMS_Page_Length_A4                   = 0x0,	
	        XMS_Page_Length_B4                   = 0x1,
	        XMS_Page_Length_Unlinit              = 0x2,
        };

        public enum XMS_FAX_SCANLINE_TIME
        {
	        XMS_Scanline_Time_0                  = 0x0,
	        XMS_Scanline_Time_5                  = 0x1,
	        XMS_Scanline_Time_10                 = 0x2,	
	        XMS_Scanline_Time_20                 = 0x3,
	        XMS_Scanline_Time_40                 = 0x4,
        };

        public enum XMS_FAX_HOSTCTRL_TYPE
        {
	        XMS_Fax_Null                         = 0x0,
	        XMS_Fax_Recv                         = 0x1,
	        XMS_Fax_Send                         = 0x2,
	        XMS_Fax_Stop                         = 0x3,
        };

        public enum XMS_FAX_WORKMODE
        {	
	        XMS_FAX_WORKMODE_NORMAL              = 0x00,
	        XMS_FAX_WORKMODE_SERVER              = 0x01,
	        XMS_FAX_WORKMODE_GATEWAY             = 0x02,
        };

        public enum XMS_FAX_ECM_MODE_TYPE
        {
	        XMS_FAX_ECM_MODE_TYPE_NORMAL         = 0x00,
	        XMS_FAX_ECM_MODE_TYPE_ECM            = 0x01,	
        };

        public enum XMS_FAX_PAGE_HEADER_TYPE  
        {
            XMS_FAX_PAGE_HEADER_TYPE_CLEAR       = 0x00,
	        XMS_FAX_PAGE_HEADER_TYPE_SET         = 0x01,
        };

        public enum XMS_FAX_M_FILE_TYPE
        {
            XMS_FAX_M_FILE_TYPE_CLEAR            = 0x00,
	        XMS_FAX_M_FILE_TYPE_ADD              = 0x02,
        };

        public enum XMS_ANSWERCALL_TYPE
        {
	        XMS_ANSWERCALL_ANC                   = 0x0,
	        XMS_ANSWERCALL_ANN                   = 0x1,
	        XMS_ANSWERCALL_CON                   = 0x2,
        };

        public enum XMS_CTX_REG_TYPE
        {
	        XMS_CTX_REG                     = 0x1,/*ctx reg*/
	        XMS_CTX_UNREG                   = 0x2,/*ctx unreg*/
        };

        public enum XMS_CTX_LINK_OPTION
        {
	        CTX_LINK_OPTION_RESET			= 0x1,/*reset all link*/
	        CTX_LINK_OPTION_LINK			= 0x2,/*single link*/
	        CTX_LINK_OPTION_UNLINK			= 0x3,/*single unlink*/
	        CTX_LINK_OPTION_DUALLINK		= 0x4,/*dual link*/
	        CTX_LINK_OPTION_DUALUNLINK		= 0x5,/*dual unlink*/
        };

        public enum XMS_MEDIA_TYPE
        {
                MEDIA_TYPE_AUDIO                     = 0,   /*play audio only*/
                MEDIA_TYPE_VIDEO                     = 1,   /*play video only*/
                MEDIA_TYPE_ANV                       = 4,   /*play audio and video*/
		        MEDIA_TYPE_MEDIAEX_AUDIO			 = 5,	/*use mediaex play audio*/
		        MEDIA_TYPE_MEDIAEX_VIDEO			 = 6,	/*use mediaex play video*/
		        MEDIA_TYPE_MEDIAEX_ANV				 = 7,	/*use mediaex play audio and video*/
        };

        public enum XMS_SS7_FRAME_USER_TYPE
        {
	        XMS_SS7_USER_SCCP = 0x03,
	        XMS_SS7_USER_TUP  = 0x04,
	        XMS_SS7_USER_ISUP = 0x05,
        };
         
        public enum XMS_SS7_FRAME_LINK_TYPE
        {
	        XMS_SS7_LINK_ITU  = 0x02,
	        XMS_SS7_LINK_CHINA= 0x04,
        };
         
        public enum XMS_SS7_FRAME_INFO_TYPE
        {
	        XMS_SS7_INFO_DATA   = 0x01,
	        XMS_SS7_INFO_CMD    = 0x02, 
        };

        public enum XMS_SYSMON_MODSTATE
        {   
	        SYSMON_MODSTATE_DISCONNECT      = 0x0,/*Module disconnect*/
            SYSMON_MODSTATE_CONNECT         = 0x1,/*Module connect*/    
        };

        public enum XMS_CTBUS_CLKNET_TYPE
        {
           L_NET0   = 0x08, 
           L_NET1   = 0x09, 
           L_NET2   = 0x0A,
           L_NET3   = 0x0B,
        };

        public enum PUT_TEXTINPIC_FONTTYPE	     /* .\\PutTextInPicture.ini */
        {
            FONTTYPE_SIMSUN = 0,    /*宋体&新宋体*/
            FONTTYPE_MICROSS,            /*Microsoft Sans Serif*/
        };

        public enum PUT_TEXTINPIC_TYPE
        {
            PUT_TYPE_TEXT = 1,
            PUT_TYPE_PICTURE = 2,
        };

        /* VoIP Media Capabilities */
        public enum XMS_VOIP_MEDIA_CAPS
        {
        // audio media
	        VOIP_MEDIA_AUDIO_PCMU		= 0x00,	// pcm u-law
	        VOIP_MEDIA_AUDIO_PCMA		= 0x01,	// pcm a-law
	        VOIP_MEDIA_AUDIO_G723		= 0x02,	// g.723
	        VOIP_MEDIA_AUDIO_G729		= 0x03,	// g.729
	        VOIP_MEDIA_AUDIO_T38		= 0x04,	// t.38/rtp
	        VOIP_MEDIA_AUDIO_AMR		= 0x05,	// amr-nb
        // video media
	        VOIP_MEDIA_VIDEO_H261		= 0x80,	// h.261
	        VOIP_MEDIA_VIDEO_H263		= 0x81,	// h.263
	        VOIP_MEDIA_VIDEO_H263P		= 0x82,	// h.263+
	        VOIP_MEDIA_VIDEO_MPEG4		= 0x83,	// mpeg-4 visual
	        VOIP_MEDIA_VIDEO_H264		= 0x84,	// h.264

	        VOIP_MEDIA_IMAGE_T38		= 0xF0,	// t.38/udptl
        };

        public enum XMS_FAX_PARAM_TYPE
        {
	        FAX_PARAM_FAXHEADER    = 0 ,
	        FAX_PARAM_ADDFAXFILE   = 1 ,
	        FAX_PARAM_ECM	       = 2,
	        FAX_PARAM_MODE_TYPE    = 3,
	        FAX_PARAM_BPS	       = 4,
	        FAX_PARAM_FAXHEADEREX  = 5
        };

        /* ISDN Device Param type*/
        public enum XMS_ISDN_PARAM_TYPE
        {
             ISDN_PARAM_ORINUMBER         = 0,
             ISDN_PARAM_CALLTYPE          = 1,
             ISDN_PARAM_APPENDCALLEE      = 2,
             ISDN_PARAM_CALLOUT           = 3,
             ISDN_PARAM_DISCONNECTREASON  = 4,
             ISDN_PARAM_LOW_LEVEL         = 5,
             ISDN_PARAM_UUI                = 6,
        };

        /* Conference Device Params */
        public enum XMS_CONF_PARAM_TYPE
        {
	        CONF_PARAM_UNIPARAM = 0,
            CONF_PARAM_VAD      = 1,
        };

        /* Analog EM Device Params */
        public enum XMS_AEM_PARAM_TYPE
        {
	        XMS_AEM_PARAM_SND_M_SIGNAL = 1, //send M msg to endpoint
        };

        /* MediaEx Device Params */
        public enum XMS_MEDIAEX_PARAM_TYPE
        {
	        MEDIAEX_PARAM_INPUT = 0,
	        MEDIAEX_PARAM_OUTPUT,
        };

        /* VoIP Device Params */
        public enum XMS_VOIP_PARAM_TYPE
        {
	        VOIP_PARAM_ACCESS = 0,
	        VOIP_PARAM_VOICE,
	        VOIP_PARAM_RTPSESSION,
	        VOIP_PARAM_RTPADDR,
	        VOIP_PARAM_RTCPADDR,
	        VOIP_PARAM_RTPCODEC,
	        VOIP_PARAM_RTPMIXER,
	        VOIP_PARAM_RTPWANIP,
	        VOIP_PARAM_PAYLOAD,
	        VOIP_PARAM_MEDIAINFO,
	        VOIP_PARAM_RTPOPEN,
	        VOIP_PARAM_SIP_USER_AGENT,
	        VOIP_PARAM_CALL_DIVERSION_INFO,
        };

        /* Analog HIZ Device Params */
        public enum XMS_ANALOGHIZ_PARAM_TYPE
        {
            ANALOGHIZ_PARAM_SET_SW_MODE   = 0 ,//set Switch Mode,replace by XMS_DIGREC_PARAM_UNI On Digital Module,reference to XMS_DIGREC_PARAM_TYPE
            ANALOGHIZ_PARAM_VOLTAGE       = 1 ,//Set voltage
            ANALOGHIZ_PARAM_READSN        = 4 ,//get HIZ's SN
            ANALOGHIZ_PARAM_GET_VOLTAGE   = 5 ,//get HIZ's voltage
        };

        /* Analog VOC2 Device Params */
        public enum XMS_ANALOGVOC2_PARAM_TYPE
        {
            ANALOGVOC2_PARAM_NULL          = 1 ,//RESERVE
            ANALOGVOC2_PARAM_READSN        = 4 ,//get VOC2 SN
	        ANALOGVOC2_PARAM_GET_VOLTAGE   = 5 ,//get HIZ's voltage
        };

        /* Analog VOC4 Device Params */
        public enum XMS_ANALOGVOC4_PARAM_TYPE
        {
            ANALOGVOC4_PARAM_NULL          = 1 ,//RESERVE
            ANALOGVOC4_PARAM_READSN        = 4 ,//get VOC4 SN
	        ANALOGVOC4_PARAM_GET_VOLTAGE   = 5 ,//get HIZ's voltage
        };

        /* Analog MEG Device Params */
        public enum XMS_AMEG_PARAM_TYPE
        {
	        XMS_AMEG_PARAM_SEND_RING_SIGNAL = 1, // send ring msg to meg
	        XMS_AMEG_PARAM_GET_SN           = 4, // get param for sn
	        XMS_AMEG_PARAM_GET_VOLTAGE      = 5, // get param for voltage
        };

        /* Analog EM Device Params */
        public enum XMS_ANALOGEM_PARAM_TYPE
        {
	        ANALOGEM_PARAM_NULL             = 1, //RESERVE
            ANALOGEM_PARAM_READSN           = 4, //get EM's SN
	        ANALOGEM_PARAM_GET_VOLTAGE      = 5, //get EM's voltage
        };

        /* 324 Config Params*/
        public enum XMS_324_PARAM_TYPE
        {
	        H324_PARAM_UNIPARAM  = 0x0,
	        H324_PARAM_MEDIA     = 0x1,
	        H324_PARAM_CH	     = 0x2,
	        H324_PARAM_MIXER	 = 0x3,
	        H324_PARAM_TCS		 = 0x4,
        };

        /*Digtial machine Record param type*/
        public enum XMS_DIGREC_PARAM_TYPE
        {
	        XMS_DIGREC_PARAM_UNI         = 0x0,       //set switch mode param type
	        XMS_AREC_PARAM_SET_VOLTAGE   = 0x01,      //set analog rec module valtage param type
        };

        public enum MD_CFG_TYPE
        {
	        MD_CFG_TYPE_NON_INDEX      = 0x00,   /*非索引操作*/
	        MD_CFG_TYPE_INDEX          = 0X01,   /*索引操作*/
        };


        /*XMS_324_CMD_SESSION_TYPE*/
        public enum XMS_324_CMD_SESSION_TYPE
        {	
	        XMS_324_CMD_TYPE_NORMAL_START			= 0x0,	/* start session in normal mode */
	        XMS_324_CMD_TYPE_MONITOR_START          = 0x1,	/* start session in monitor mode */
	        XMS_324_CMD_TYPE_STOP                   = 0x2,	/* stop session */
	        XMS_324_CMD_TYPE_RESET					= 0x3,	/* reset session */
        };

        /*XMS_324_CMD_CTRL_TYPE*/
        public enum XMS_324_CMD_CTRL_TYPE
        {
	        XMS_324_CMD_TYPE_SETMET					= 0x1,	/* set multiplex entry table */
	        XMS_324_CMD_TYPE_OLC					= 0x2,	/* open rx/tx logical channel */
	        XMS_324_CMD_TYPE_CLC					= 0x3,	/* close logical channel */
	        XMS_324_CMD_TYPE_UII					= 0x4,	/* Send user input */	
	        XMS_324_CMD_TYPE_VFU					= 0x5,	/* send video fast update */
        };

        /*XMS_324_EVT_TYPE*/
        public enum XMS_324_EVT_TYPE
        {
	        XMS_324_EVT_TYPE_START				    = 0x1,	/* start session event */
	        XMS_324_EVT_TYPE_STOP				    = 0x2,	/* stop session event */
	        XMS_324_EVT_TYPE_RESET					= 0x3,	/* reset session event */
	        XMS_324_EVT_TYPE_UII					= 0x4,	/* receive user input event */
	        XMS_324_EVT_TYPE_SIG_PDU                = 0x5,	/* receive h.245 signal message event */
	        XMS_324_EVT_TYPE_OLC						= 0x6,	/*open logical channel event*/
	        XMS_324_EVT_TYPE_CLC						= 0x7,	/*close logical channel event*/
        };

        /* XMS_324_STOP_CODE */
        public enum XMS_324_STOP_CODE
        {
	        XMS_324_STOP_CODE_UNKOWN				= 0x0,
	        XMS_324_STOP_CODE_UPERSTOP				= 0x1,
	        XMS_324_STOP_CODE_LOWERSTOP				= 0x2,
	        XMS_324_STOP_CODE_HOSTSTOP				= 0x3,	
	        XMS_324_STOP_CODE_REMOTESTOP			= 0x4,
        };

        /* XMS_324_AL_TYPE */
        public enum XMS_324_AL_TYPE
        {
	        XMS_324_AL1_FRAMED						= 0x1,	/* AL1 framed */
	        XMS_324_AL1_NOTFRAMED					= 0x2,	/* AL1 not framed */
	        XMS_324_AL2_WITHOUTSN					= 0x3,	/* AL2 */
	        XMS_324_AL2_SN							= 0x4,	/* AL2 with sn */
	        XMS_324_AL3								= 0x5,	/* AL3 */
        };

        /* encode type define for 3G324M module */
        /*  encode type */
        public enum XMS_ENCODE_TYPE
        {
	        XMS_324_LC_CTRL							= 0x0,
	        XMS_324_LC_AUDIO_G723					= 0x08,
	        XMS_324_LC_AUDIO_AMR					= 0x14,
	        XMS_324_LC_VIDEO_H263					= 0x83,
	        XMS_324_LC_VIDEO_MPEG4					= 0x85,
        };

        //////////////////////////////////////////////////////////////////
        /*XMS_SCCP_CMD_TYPE*/
        public enum XMS_SCCP_CMD_TYPE
        {
	        XMS_SCCP_CMD_SETRAWDATA             = 0x1,	
        };

        /*EXT_ENABLE_TYPE*/
        public enum EXT_ENABLE_TYPE
        {
            EXT_ENABLE_DPD                          = 0x01,
            EXT_ENABLE_PVD                          = 0x02,	
            EXT_ENABLE_MSK                          = 0x04,
            EXT_ENABLE_VSD                          = 0x08,
        };

        /*DRS_EVT_MASK*/
        public enum DRS_EVT_MASK
        {
            DRS_EVT_HOOK_MASK                       = 0x01,
            DRS_EVT_CONNECT_MASK                    = 0x02,	
            DRS_EVT_VAD_MASK                        = 0x04,
        };

        /*XMS_RTPX_PARAM_TYPE*/
        public enum XMS_RTPX_PARAM_TYPE
        {
	        XMS_RTPX_PARAM_INPUT               = 0x0,
	        XMS_RTPX_PARAM_OUTPUT              = 0x1,
	        XMS_RTPX_PARAM_MIXER		       = 0x2,
	        XMS_RTPX_PARAM_ADDR				   = 0x3,
	        XMS_RTPX_PARAM_INPUT_A               = 0x4,
	        XMS_RTPX_PARAM_OUTPUT_A              = 0x5,
	        XMS_RTPX_PARAM_MIXER_A		       = 0x6,
	        XMS_RTPX_PARAM_ADDR_A				   = 0x7
        };

        /*XMS_DRS_SWITCH_TYPE*/
        public enum XMS_DRS_SWITCH_TYPE
        { 
            XMS_DRS_SWITCH_AVAYA                = 0x01,
            XMS_DRS_SWITCH_SIMENZ               = 0x02,
            XMS_DRS_SWITCH_TADIRANT             = 0x03,
            XMS_DRS_SWITCH_ERRICSION            = 0x04,
            XMS_DRS_SWITCH_TOSHIBA              = 0x05,
        };

        /*Event filter mask*/
        public enum XMS_IOEVT_MASK_TYPE
        {
            XMS_IOEVT_MASK_GTD = 0x0001,
            XMS_IOEVT_MASK_FSK = 0x0002,
            XMS_IOEVT_MASK_MR2F = 0x0004,
            XMS_IOEVT_MASK_MR2B = 0x0008,
        };

        public enum XMS_MEDIA_ERR_CODE
        {
            XMS_ERR_CODE_OK = 0x00,
            XMS_ERR_CODE_APPSTOP = 0x01,
            XMS_ERR_CODE_GTD = 0x02,
            XMS_ERR_CODE_OPENFILE_FAILED = 0x03,
            XMS_ERR_CODE_WREADFILE_FAILED = 0x04,
            XMS_ERR_CODE_CH_MISSING = 0x05,
            XMS_ERR_CODE_EXE_FAILED = 0x06,
            XMS_ERR_CODE_BUILD_INDEX_OK = 0x07,
            XMS_ERR_CODE_PLAY_QUEUE_FULL = 0x08,
            XMS_ERR_CODE_3G_AUDIO_OK = 0x09,
            XMS_ERR_CODE_3G_VIDEO_OK = 0x0A,
            XMS_ERR_CODE_BUILD_INDEX_FAILED = 0x0B,
            XMS_ERR_SYSTEM_OVERLOAD = 0x0C,
        };

        /*It will be replaced by XMS_CLK_STATE_TYPE later from V3.0.0*/
        public enum XMS_CLK_RS_STATE_TYPE
        {
            XMS_CLK_RS_STATE_MASTER_CLOCK_RS_SET = 0x01,    /*Set Master Clock Ref Source*/
            XMS_CLK_RS_STATE_MASTER_CLOCK_RS_RELEASE = 0x02,    /*Release Master Clock Ref Source*/
        };


        public enum XMS_CLK_STATE_TYPE
        {
            XMS_CLK_STATE_SET = 0x01,    /*Set master/slave clock */
            XMS_CLK_STATE_RELEASE = 0x02,    /*Release master/slave clock*/
        };

        public enum XMS_VOIP_IO_TYPE
        {
            XMS_IO_TYPE_VOIP_H245UII = 1,  /* VoIP H.245 UserInputIndication Event */
            XMS_IO_TYPE_VOIP_SIPINFO = 2,  /* VoIP SIP INFO Event */
            XMS_IO_TYPE_VOIP_RTPDTMF = 3,  /* VoIP RTP DTMF Event */
            XMS_IO_TYPE_VOIP_RTPTONE = 4,  /* VoIP RTP TONE */
            XMS_IO_TYPE_VOIP_FAXSTART = 5,  /* VoIP start fax mode (t.38 or t.30 pass-thru) */
            XMS_IO_TYPE_VOIP_FAXSTOP = 6,  /* VoIP stop fax mode(t.38 or t.30 pass-thru) */
            XMS_IO_TYPE_VOIP_REGSTATE = 7,  /* VoIP Registration State */
            XMS_IO_TYPE_VOIP_REGREQUEST = 8,  /* VoIP Registration Request */
            XMS_IO_TYPE_VOIP_REGRESPONSE = 9,  /* VoIP Registration Response */
            XMS_IO_TYPE_VOIP_TRANSFER = 10, /* VoIP Device Transfer */
            XMS_IO_TYPE_VOIP_SIPREG = 11, /* VoIP SIP Register */
            XMS_IO_TYPE_VOIP_SIPUNREG = 12, /* VoIP SIP Unregister */
            XMS_IO_TYPE_VOIP_REFER = 13, /* Voip SIP Refer */
            XMS_IO_TYPE_VOIP_REFERRESPONSE = 14, /* Voip SIP Refer Response */
            XMS_IO_TYPE_VOIP_FORWARD = 15, /* Voip SIP Forward call */
            XMS_IO_TYPE_VOIP_REFER_NOTIFY = 16, // VoIP SIP Send Refer Notify to Subscribe
            XMS_IO_TYPE_VOIP_CALLMODIFY = 17, /* VoIP SIP Call Modified */
        };

        public enum XMS_DCH_IO_TYPE
        {
            XMS_IO_TYPE_DCH_I_FRAME = 1,
            XMS_IO_TYPE_DCH_UI_FRAME = 2,
            XMS_IO_TYPE_DCH_DEBUG = 3,
        };

        public enum XMS_LINESIDEE1_IO_TYPE
        {
            XMS_IO_TYPE_LINESIDEE1 = 12,
        };

        public enum XMS_ANALOG_INTERFACE_STATE
        {
            XMS_ANALOG_USER_CH_OFFHOOK = 0,
            XMS_ANALOG_USER_CH_ONHOOK = 1,
            XMS_ANALOG_USER_CH_FLASH = 2,
        };

        public enum XMS_ANALOG_INTERFACE_STATE2
        {
            XMS_ANALOG_TRUNK_CH_RING = 0,
            XMS_ANALOG_TRUNK_CH_POSITEX_POLARITY = 1,
            XMS_ANALOG_TRUNK_CH_NEGATIVE_POLARITY = 2,
            XMS_ANALOG_TRUNK_CH_LOOPDROP = 3,
            XMS_ANALOG_TRUNK_CH_NOLOOP = 4,
            XMS_ANALOG_TRUNK_CH_FLASH = 8,
        };


        public enum XMS_SIG_RAWDATA_EVT_TYPE
        {
            XMS_SIG_RAWDATA_EVT_BASE = 0xFF00,
        };

        public enum ACS_MASTER_STATE
        {
            ACS_STATE_SLAVE = 0x0,
            ACS_STATE_MASTER = 0x1,
        };

        public enum ACS_WORK_STATE
        {
            ACS_STATE_WORK_FAILURE = 0x0,
            ACS_STATE_WORKING = 0x1,
        };

        public enum XMS_SS7_SN_STATUS
        {
            XMS_SN_PAUSE = 0x01, // Pause
            XMS_SN_RESUME = 0x02, // Resume
            XMS_SN_CONG = 0x03, // Network Congested
            XMS_SN_RMTUSRUNAV = 0x04, // Remote User Unavailable
            XMS_SN_RSTBEG = 0x05, // Restart Begins
            XMS_SN_RSTEND = 0x06, // Restart Ends
            XMS_SN_STPCONG = 0x07, // Stop Network Congestion
            XMS_SN_RESTRICT = 0x08, // Restrict
            XMS_SN_LNK_CHANGE = 0x09, // Link status changed
        };


        public enum XMS_SS7_MSG_TYPE
        {
            XMS_SS7_MSG_DATA = 0x01,
            XMS_SS7_MSG_CMD = 0x02,
            XMS_SS7_MSG_STATUS = 0x03,
        };


        public enum XMS_SS7_USER_TYPE
        {
            XMS_SS7_USER_TYPE_SCCP = 0x03,
            XMS_SS7_USER_TYPE_TUP = 0x04,
            XMS_SS7_USER_TYPE_ISUP = 0x05,
        };


        public enum XMS_SS7_LINK_TYPE
        {
            XMS_SS7_LINK_TYPE_ITU = 0x02,
            XMS_SS7_LINK_TYPE_CHINA = 0x04,
        };

        public enum XMS_3GVCONF_ERROR_CODE_DEF
        {
            XMS_ERROR_DEVTYPEERROR = 0,		// 不是可加入会议的设备
            XMS_ERROR_REJOIN3GVCONF = 1,		// 已存在会议中
            XMS_ERROR_GETRESFAIL = 2,		// 分配资源失败
            XMS_ERROR_OVERFLOW = 3,			// 会议成员已满
            XMS_ERROR_NONEVISIBLE = 4,		// 会议无可视视频会员
            XMS_ERROR_OVERFLOWPR = 5,		// 会议16方已满 因为有会议播放或者录制造成

            XMS_ERROR_3GVCONFSTOP = 255,		// 会议停止 可能是新加入会议的可视成员参数错误或播放录音参数错误 也可能是会议进程出现错误
            // 遇到此事件应该重让最后一个加入会议的操作取消 或者重启会议
        };

        public enum tagPutTextInPictureResult
        {
            PutTextInPictureResult_Success = 0,					// 成功
            PutTextInPictureResult_ParamError = 1,			// 参数错误
            PutTextInPictureResult_OpenPicError = 2,		// 打开文件失败
            PutTextInPictureResult_SavePicError = 3			// 保存文件失败
        };
}