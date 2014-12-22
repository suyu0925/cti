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
            public const int ACS_MAX_CALL_NUM = 32;
            public const int ACS_MAX_FILE_NAME_LEN = 128;
            public const int ACS_MAX_FILE_NUM = 8;
            public const int MAX_PATH = 260;
            public const int ACS_MAX_DECODER_CFG_LEN = 200;
            public const int MAX_DECODER_CFG_INFO = 128;
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
	        public DJ_U8                       m_u8InputCtrlValid;  /*is VocInputControl_t valid*/
	        public DJ_U8                       m_u8PlayGainMode;    /*Play gain mode,reference XMS_PLAY_GAIN_MODE*/  
	        public DJ_U16                      m_u16PlayFixGain;    /*Play fix gain*/ 
	        public VocInputControlParam_t	    m_VocInputControl;   /*valid to voc,not include RTP*/
	        public DJ_U8                       m_u8OutputCtrlValid; /*is VocOutputControl_t valid*/
	        public fixed DJ_S8                       m_s8Rfu2[3];         /*Rfu*/
	        public VocOutputControlParam_t	    m_VocOutputControl;  /*valid to voc and RTP*/
	        public DJ_U8                       m_u8GtdCtrlValid;    /*is VocGtdControl_t valid*/
	        public fixed DJ_S8                       m_s8Rfu3[3];         /*Rfu*/
            public VocGtdControlParam_t m_VocGtdControl;	 /*valid to voc and RTP*/
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

            public fixed DJ_U8 m_CalledTable[16 * sizeof(DJ_U8)*16];
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
	        XMS_EVT_CLASS_GENERAL            = 0x0001,
	        XMS_EVT_CLASS_CALLCONTROL        = 0x0002,
	        XMS_EVT_CLASS_CONFPROC           = 0x0003,
	        XMS_EVT_CLASS_VOIPPROC           = 0x0004,
	        XMS_EVT_CLASS_MEDIAPROC          = 0x0005,
	        XMS_EVT_CLASS_FAXPROC            = 0x0006,
	        XMS_EVT_CLASS_IOPROC             = 0x0007,
	        XMS_EVT_CLASS_SYSMONITOR         = 0x0008,
	        XMS_EVT_CLASS_UNIFAILURE         = 0x0009,	
        };

        /*Event type define */
        public enum XMS_EVT_TYPE
        {
            XMS_EVT_OPEN_STREAM = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL << 16) + 0x01),	
	        XMS_EVT_QUERY_DEVICE                    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x02),	
	        XMS_EVT_QUERY_DEVICE_END                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x03),
	        XMS_EVT_OPEN_DEVICE                     = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x04),
	        XMS_EVT_CLOSE_DEVICE                    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x05),
	        XMS_EVT_RESET_DEVICE                    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x06),
	        XMS_EVT_DEVICESTATE                     = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x07),
	        XMS_EVT_SETDEV_GROUP                    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x08),
	        XMS_EVT_SETPARAM                        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x09),
	        XMS_EVT_GETPARAM                        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0A),
	        XMS_EVT_QUERY_ONE_DSP_START             = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0B),
	        XMS_EVT_QUERY_ONE_DSP_END               = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0C),
	        XMS_EVT_QUERY_REMOVE_ONE_DSP_START      = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0D),
	        XMS_EVT_QUERY_REMOVE_ONE_DSP_END        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0E),
	        XMS_EVT_OPEN_STREAM_EXT                 = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0F),	
	        XMS_EVT_LICENSE_QUERY                   = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x10),	
	        XMS_EVT_ACS_TIMER                       = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0xFF),
    			
	        XMS_EVT_CALLOUT							= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x01),
	        XMS_EVT_CALLIN							= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x02),
	        XMS_EVT_ALERTCALL		                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x03),
	        XMS_EVT_ANSWERCALL		                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x04),
	        XMS_EVT_LINKDEVICE				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x05),
	        XMS_EVT_UNLINKDEVICE					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x06),
	        XMS_EVT_CLEARCALL						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x07),
	        XMS_EVT_ANALOG_INTERFACE                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x08),
	        XMS_EVT_CAS_MFC_START					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x09),
	        XMS_EVT_CAS_MFC_END						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0A),
	        XMS_EVT_SENDSIGMSG						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0B),		
	        XMS_EVT_SIGMON       					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0C),
	        XMS_EVT_3G324M       					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0D),
	        XMS_EVT_CTX_REG                         = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0E),
	        XMS_EVT_CTX_LINK                        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0F),
	        XMS_EVT_CTX_APPDATA                     = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x10),
	        XMS_EVT_DRS_CALL_NUMS                   = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x11),
    	
    	
	        XMS_EVT_SS7RawFrame						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x20),
	        XMS_EVT_SS7SendRawFrame					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x21),

    		
	        XMS_EVT_JOINTOCONF					    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CONFPROC<<16)+0x01),
	        XMS_EVT_LEAVEFROMCONF					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CONFPROC<<16)+0x02),
	        XMS_EVT_CLEARCONF					    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CONFPROC<<16)+0x03),
    		
	        XMS_EVT_PLAY			                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x01),
	        XMS_EVT_INITINDEX				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x02),
	        XMS_EVT_BUILDINDEX						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x03),
	        XMS_EVT_CONTROLPLAY				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x04),
	        XMS_EVT_RECORD							= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x05),
	        XMS_EVT_CONTROLRECORD				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x06),
	        XMS_EVT_RECORDCSP   				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x07),
	        XMS_EVT_CONTROLRECORDCSP    		    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x08),
            XMS_EVT_3GPP_PLAY			            = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x09),
	        XMS_EVT_3GPP_CONTROLPLAY		        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0A),
	        XMS_EVT_3GPP_RECORD	    				= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0B),
	        XMS_EVT_3GPP_CONTROLRECORD    		    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0C),
	        XMS_EVT_PLAYCSPREQ 				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0D),
	        XMS_EVT_3GPP_INIT_INDEX                           = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0E),
	        XMS_EVT_3GPP_BUILD_INDEX                          = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0F),
    	
	        XMS_EVT_SENDFAX			                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_FAXPROC<<16)+0x01),
	        XMS_EVT_RECVFAX					        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_FAXPROC<<16)+0x02),
    			
	        XMS_EVT_SENDIODATA						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_IOPROC<<16)+0x01),
	        XMS_EVT_RECVIODATA						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_IOPROC<<16)+0x02),
    		
	        XMS_EVT_MODMONITOR				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR<<16)+0x01),
	        XMS_EVT_DEV_TIMER						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR<<16)+0x02),
    	
	        XMS_EVT_UNIFAILURE						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_UNIFAILURE<<16)+0x01),	
        };

        public enum XMS_DEVMAIN_TYPE
        {
	        XMS_DEVMAIN_CONFIG               = 0x01, /*config adding for log manager*/
	        XMS_DEVMAIN_VOICE                = 0x02, /*Voice device*/
	        XMS_DEVMAIN_FAX                  = 0x03, /*Fax device*/
	        XMS_DEVMAIN_DIGITAL_PORT         = 0x04, /*Digital Port device*/
	        XMS_DEVMAIN_INTERFACE_CH         = 0x05, /*Interface Ch device*/
	        XMS_DEVMAIN_DSS1_LINK            = 0x06, /*DSS1 Link device*/
	        XMS_DEVMAIN_SS7_LINK             = 0x07, /*SS7 Link device*/
	        XMS_DEVMAIN_BOARD                = 0x08, /*DSP Board device*/
	        XMS_DEVMAIN_CTBUS_TS             = 0x09, /*CTBus ts device*/
	        XMS_DEVMAIN_RTP                  = 0x0A, /*VoIP device*/
	        XMS_DEVMAIN_MEDIAEX              = 0x0B, /*MediaEx device*/
	        XMS_DEVMAIN_CONFERENCE           = 0x0C, /*Conference Group Device*/
	        XMS_DEVMAIN_VIDEO                = 0x0D, /*Video device*/
	        XMS_DEVMAIN_CTX                  = 0x10, /*Ctx device*/
	        XMS_DEVMAIN_RTPX                 = 0x11, /*RTPX device*/
	        XMS_DEVMAIN_VOIP                 = 0x12, /*VoIP device*/
	        XMS_DEVMAIN_VIDEOCONF            = 0x1F, /*Video Conference Device*/
        };

        public enum XMS_INTERFACE_DEVSUB_TYPE
        {
	        XMS_DEVSUB_BASE                       = 0x0,  /*Base*/
	        XMS_DEVSUB_ANALOG_TRUNK               = 0x01, /*Analog Trunk*/
	        XMS_DEVSUB_ANALOG_USER                = 0x02, /*Analog User*/
	        XMS_DEVSUB_ANALOG_HIZ                 = 0x03, /*Analog Hiz*/
	        XMS_DEVSUB_ANALOG_EMPTY               = 0x04, /*Analog Empty*/
	        XMS_DEVSUB_E1_PCM                     = 0x05, /*E1 PCM*/
	        XMS_DEVSUB_E1_CAS                     = 0x06, /*E1 CAS*/
	        XMS_DEVSUB_E1_DSS1                    = 0x07, /*E1 DSS1*/
	        XMS_DEVSUB_E1_SS7_TUP                 = 0x08, /*E1 SS7 TUP*/
	        XMS_DEVSUB_E1_SS7_ISUP                = 0x09, /*E1 SS7 ISUP*/
	        XMS_DEVSUB_ANALOG_VOC2W			      = 0x0A, /*Voice only 2 wire*/
            XMS_DEVSUB_ANALOG_VOC4W			      = 0x0B, /*Voice only 4 wire*/
            XMS_DEVSUB_ANALOG_EM			      = 0x0C, /*EM control module*/
            XMS_DEVSUB_ANALOG_MAG			      = 0x0D, /*magnetic module*/
            XMS_DEVSUB_E1_DCH				      = 0x0E, /*E1 6D25B's Dchannel*/
            XMS_DEVSUB_E1_BCH				      = 0x0F, /*E1 6D25B's Bchannel*/
            XMS_DEVSUB_UNUSABLE				      = 0x10, /*unusable timeslot, such as ts0 of E1*/
	        XMS_DEVSUB_HIZ_CAS				      = 0x11, /*Hiz Cas*/
	        XMS_DEVSUB_HIZ_PRI				      = 0x12, /*Hiz Pri*/
        	XMS_DEVSUB_HIZ_SS7					  = 0x13, /*Hiz ss7*/
        	XMS_DEVSUB_HIZ_PRI_LINK			      = 0x14, /*Hiz pri link*/
        	XMS_DEVSUB_HIZ_SS7_64K_LINK  		  = 0x15, /*Hiz ss7 64k link*/
        	XMS_DEVSUB_HIZ_SS7_2M_LINK    		  = 0x16, /*Hiz ss7 2M link*/
	        XMS_DEVSUB_SS7_LINK		              = 0x17, /*ss7 link*/
	        XMS_DEVSUB_LINESIDE		              = 0x18, /*LineSide E1*/
        	XMS_DEVSUB_ANALOG_REC	              = 0x19, /*Analog phone Record*/
        	XMS_DEVSUB_HIZ_HDLC_N64K_LINK         = 0x1A, /*Hiz n*64K */
        	XMS_DEVSUB_SS7_2M_LINK                = 0x1B, /*SS7 2M LINK*/
        	XMS_DEVSUB_HIZ_HDLC                   = 0x1C, /*Hiz */
	        XMS_DEVSUB_DIGITAL_REC	              = 0x20, /*Digital phone Record*/
        };

        public enum XMS_E1_TYPE
		{
            XMS_E1_TYPE_NULL                 = 0,
			XMS_E1_TYPE_Analog30	         = 1, /* Analog Interface 30*/
			XMS_E1_TYPE_PCM31		         = 2, /* E1 Frame,ts31*/
			XMS_E1_TYPE_PCM30		         = 3, /* E1 Frame,ts 30*/
			XMS_E1_TYPE_CAS			         = 4, /* E1 Frame,CAS*/
			XMS_E1_TYPE_PRI			         = 5, /* E1 Frame,PRI*/
			XMS_E1_TYPE_SS7_TUP_0_Link	     = 6, /* E1 Frame,TUP: 0 link*/
			XMS_E1_TYPE_SS7_TUP_1_Link	     = 7, /* E1 Frame,TUP: 1 link*/
			XMS_E1_TYPE_SS7_TUP_2_Link	     = 8, /* E1 Frame,TUP: 2 link*/
			XMS_T1_TYPE_D4	                 = 9, /* T1 Frame*/
			XMS_T1_TYPE_ESF		             = 10, /* T1 Frame*/
			XMS_J1_TYPE_D4		             = 11, /* J1 Frame*/
			XMS_J1_TYPE_ESF		             = 12, /* J1 Frame*/
			XMS_SLC_TYPE_96    	             = 13, /* SLC_96 Frame*/
			XMS_E1_TYPE_SS7_ISUP_0_Link	     = 14, /* E1 Frame,ISUP: 0 link*/
			XMS_E1_TYPE_SS7_ISUP_1_Link	     = 15, /* E1 Frame,ISUP: 1 link*/
			XMS_E1_TYPE_SS7_ISUP_2_Link	     = 16, /*E1 Frame,ISUP: 2 link*/
			XMS_E1_TYPE_6D25B		     = 17, /* E1 Frame, 6 DChannel,25 BChannel*/
			XMS_E1_TYPE_1D30B                    = 18, /*E1 Frame, 1 DChannel, 30 BChannel*/
			XMS_E1_TYPE_11D20B                   = 19, /*E1 Frame, 11 DChannel, 20 BChannel*/
			XMS_E1_TYPE_HIZ_CAS                  = 20, /*E1 Frame, HIZ CAS*/
			XMS_E1_TYPE_HIZ_PRI                  = 21, /*E1 Frame, HIZ PRI*/	
			XMS_E1_TYPE_HIZ_SS7                  = 22, /*E1 Frame, HIZ SS7*/
			XMS_E1_TYPE_HIZ_64K_SS7   	         = 23, /*E1 Frame, HIZ pure 64k SS7*/
			XMS_E1_TYPE_HIZ_2M_SS7               = 24, /*E1 Frame, HIZ 2M SS7*/
			XMS_E1_TYPE_LINESIDE                 = 25, /*E1 Frame, lineside*/
			XMS_E1_TYPE_HIZ_N64K_HDLC            = 26, /*E1 Frame, HIZ N*64K HDLC*/	
			XMS_E1_TYPE_2M_SS7									 = 27, /*E1 Frame, 2M SS7*/
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
}