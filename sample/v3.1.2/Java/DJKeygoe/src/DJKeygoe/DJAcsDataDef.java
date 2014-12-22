package DJKeygoe;

public class DJAcsDataDef {
}

class ServerID_t{
	public byte []m_s8ServerIp = new byte[32];
	public int  m_u32ServerPort;
	public byte []m_s8UserName = new byte[32];
	public byte []m_s8UserPwd = new byte[32];
}

class PrivateData_t{
	public int m_u32DataSize;
}

class CallID_t{
	public int m_s32FlowType; 		/*CallType*/
	public int m_s32FlowChannel;	/*Call Channel*/
}

class DeviceID_t{
	public short 		m_s16DeviceMain; 		/*device main type*/
	public short 		m_s16DeviceSub; 		/*device sub type*/
	public byte 		m_s8ModuleID;      	 	/*device module ID*/
	public byte 		m_s8MachineID;    		/*device machine ID*/
	public short		m_s16ChannelID;   		/*device channel ID*/
	public short		m_s16DeviceGroup; 		/*device group ID*/
	public byte 		m_Rfu2[] = new byte[2]; /*Reserved*/
	public CallID_t		m_CallID = new CallID_t();	/*Serveice ID*/
	
	public void CopyDeviceID_tObj(DeviceID_t SourDev){
		m_s16DeviceMain 	= SourDev.m_s16DeviceMain;
		m_s16DeviceSub	 	= SourDev.m_s16DeviceSub;
		m_s8ModuleID 		= SourDev.m_s8ModuleID;
		m_s8MachineID 		= SourDev.m_s8MachineID;
		m_s16ChannelID 		= SourDev.m_s16ChannelID;
		m_s16DeviceGroup 	= SourDev.m_s16DeviceGroup;
		m_Rfu2[0]			= SourDev.m_Rfu2[0];
		m_Rfu2[1]			= SourDev.m_Rfu2[1];
		
		m_CallID.m_s32FlowChannel = SourDev.m_CallID.m_s32FlowChannel;
		m_CallID.m_s32FlowType 	  = SourDev.m_CallID.m_s32FlowType;
	}
	
	public void InitDeviceID(){
		m_s16DeviceMain 	= 0;
		m_s16DeviceSub	 	= 0;
		m_s8ModuleID 		= 0;
		m_s8MachineID 		= 0;
		m_s16ChannelID 		= 0;
		m_s16DeviceGroup 	= 0;
		m_Rfu2[0]			= 0;
		m_Rfu2[1]			= 0;
		
		m_CallID.m_s32FlowChannel = 0;
		m_CallID.m_s32FlowType 	  = 0;
	}
}


class Acs_Evt_t{
	public int 		m_s32AcsHandle;			/*acs handle*/
	public DeviceID_t  m_DeviceID = new DeviceID_t();				/*Device ID*/
	public int 		m_s32EvtSize;			/*Evt size*/
	public int 		m_s32EventType;			/*event type code*/
	public int 		m_u32EsrParam;			/*App esr param*/
	
	public void InitEvt(){
		m_s32AcsHandle = 0;
		m_s32EvtSize   = 0;
		m_s32EventType = 0;
		m_u32EsrParam  = 0;
		
		m_DeviceID.InitDeviceID();
	}
}

/*Acs_IO_Data*/
class Acs_IO_Data
{
	public int      m_s32AcsEvtState;   /*acs event state*/
	public int      m_s32AcsEvtErrCode; /*acs event errcode*/	
	public short    m_u16IoType;        /*io proc type*/
	public short    m_u16IoDataLen;     /*io data len*/  
	
	public void InitData(){
		m_s32AcsEvtState   = 0;
		m_s32AcsEvtErrCode = 0;
		m_u16IoType 	   = 0;
		m_u16IoDataLen 	   = 0;
	}
}/**/


class Acs_GeneralProc_Data{
	public int 		m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/	
	public int      m_s32AcsEvtErrCode;  /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	public int 		m_s32DeviceState;	 /*Device State*/
	public int 		m_s32Resrv;			 /*reserved*/
	public PrivateData_t	m_PrivData = new PrivateData_t();		 /*private data*/
}

/*Acs_Dev_List_Head_t*/
class Acs_Dev_List_Head_t{
	public int        m_s32DeviceMain;   /*device Main*/
	public int        m_s32ModuleID;     /*Device Module ID*/
	public int        m_s32DeviceNum;    /*device num*/
}/**/

/* CAS Parameter Type Define*/
class CmdParamData_CAS_t {
	public DeviceID_t		m_VocDevID = new DeviceID_t() ;				/* Voice Device ID which is used for MFC, alloced by Application */

	/* Call In Parameter */
	public byte				m_u8CalledTableCount = 0;					/* Called Table Count ( 0-16:Table Count) */
	public byte             m_Rfu1[] 			 = new byte[3];     	/* Reserved*/
	
	public CAS_CalledTableDesc_t m_CalledTable[]	= new	CAS_CalledTableDesc_t[16];		/* Max 16 items */
	
	public byte				m_u8CalledLen 	 = 0;		/* Called Number Length (0:Variable, Other:Length) */
	public byte				m_u8CalledTimeOut= 0;		/* Time Out Seconds when Receive MFC */
	public byte 			m_u8NeedCaller   = 0;		/* Is Need Caller Number ( 1:Yes, 0:No ) */
	public byte				m_u8AreaCodeLen  = 0;		/* Area Code Length when receive Called Number, Used for Receive Caller Number */

	/* Call Out Parameter */
	public byte				m_u8KA 			 = 0;		/* KA ( Default KA = 1 ) */
	public byte				m_u8KD	 		 = 0;		/* KD ( Default KD = 3 ) */

	/* Other */
	public byte				m_u8ControlMode  = 0;		/* Release Control Mode ( 0:None, 1:Caller Control, 2:Called Control ) */
	public byte             m_u8CountryCode  = 0;    
    public byte             m_u8CallType 	 = 0;
    public byte             m_u8AppendCallee = 0;
	public byte				m_u8Rfu[] 		 = new byte[6];		/* Reserved for Future Use */

/*	CmdParamData_CAS_t(){
		for (int i = 0; i < 16; i++){
			m_CalledTable[i] = new CAS_CalledTableDesc_t();
		}
	}*/

}

/* Called Number Table Description */ 
class CAS_CalledTableDesc_t {
	public byte						m_u8NumHeadLen = 0;			/* Compared Called Number Head Length */
	public byte						m_u8NumHead[] = new byte[14];		/* Compared Called Number Head Content */
	public byte						m_u8NumLen	= 0;			/* Total Called Number Length */
}/**/

/*ACS_Conf_Param*/
class CmdParamData_Conf_t{
	public byte               m_u8InputOpt;	 /*conf input option, reference XMS_CONF_INPUT_OPT*/
	public byte               m_u8OutputOpt; /*conf output option, reference XMS_CONF_OUTPUT_OPT*/
	public byte               m_u8Rfu1;      /*Rfu*/
	public byte               m_u8Rfu2;      /*Rfu*/
}/*CmdParamData_Conf_t*/

/*ACS playpropetry*/
class PlayProperty_t{	
	public byte                m_u8TaskID;         /*play task ID*/	
	public byte                m_u8SrcMode;        /*file src mode, reference XMS_VOC_SRC_MODE*/
	public byte                m_u8DecodeType;     /*decode type, reference XMS_VOC_CODE_TYPE*/	
	public byte                m_s8Rfu1;           /*Reserved*/
	public int                 m_u32MaxSize;       /*play max size(BYTES),  0: file real size; >0: max play size*/
	public int                 m_u32MaxTime;       /*play max time(Seconds) 0: file real seconds; >0: max play seconds*/	
	public int                 m_u32StopMode;      /*stop play mode,referecne XMS_PLAYREC_STOP_MODE*/
	public int                 m_u32StopCode;      /*stop play when receive this dtmf code*/
	public short               m_u16FileOffset;    /*start play at the file offset*/
	public short               m_u16PlayType;      /*play type: 0-normal,1-index,referecnce XMS_PLAY_TYPE*/
	public short               m_u16PlayIndex;     /**/
	public byte 			   m_s8PlayContent[] = new byte[128];/*play file name */
	public short               m_u16FileSubOffset; /*start play at the offset from m_u16FileOffset, and the granularity is 1 bytes, fileOffSet = m_u16FileOffset*8K + m_u16FileSubOffset*/
}

/*control play */
class ControlPlay_t{
	public short             m_u16ControlType;  /*play control type,reference XMS_CTRL_PLAY_TYPE*/
	public short             m_u16StepSize;     /*play step size*/
	public short             m_u16TuneType;     /*tune type,reserved*/
	public short             m_u16SpeedSize;    /*speed size,reserved*/
}

/*����ͨ������*/
class MixerControlParam_t{
	public byte		m_u8SRC1_Ctrl;  /*reference XMS_MIXER_TYPE*/
	public byte		m_u8SRC2_Ctrl;  /*reference XMS_MIXER_TYPE*/
	public short	m_u16SRC_ChID1; /*Media ChID1*/
	public short	m_u16SRC_ChID2; /*Media ChID2*/
	public byte		m_u8Video;
	public byte   	m_s8Rfu;     /*Rfu*/
}/*MixerControl_t*/

/*ACS record file propetry*/
class RecordProperty_t{	
	public int                m_u32MaxSize;    /* record max size, 0: no limit file size; >0: record max size*/
	public int                m_u32MaxTime;    /* record max time, 0: no limit record time; >0: record max time*/	
	public byte	              m_u8EncodeType;  /* encode type, reference XMS_VOC_CODE_TYPE*/	
	public byte	              m_u8SRCMode;     /*file src mode, reference XMS_VOC_SRC_MODE*/
	public byte	              m_u8StopMode;    /*stop record mode,referecne XMS_PLAYREC_STOP_MODE*/
	public byte	              m_u8StopCode;	   /*stop record when receive this dtmf code*/
	public byte               m_s8IsMixEnable; /*is Mix*/
	public byte               m_u8TaskID;      /*change from Reserved to m_u8TaskID on 090112*/
	public MixerControlParam_t m_MixerControl = new MixerControlParam_t();  /*Mixer Contronl parameter*/
	public byte               m_s8IsAppend;    /*0: trunc record file; 1: append record file,reference XMS_REC_OPENFILE_TYPE*/
	public byte            	  m_s8FileName[] = new byte[260];/*record file name*/
	public byte               m_s8Rfu2;      /*Reserved*/
}/*RecordProperty_t*/

/*ACS record Ram propetry*/
class RecordCSPProperty_t{	
	public byte	              	m_u8EncodeType;  /* encode type, reference XMS_VOC_CODE_TYPE*/	
	public byte	              	m_u8SRCMode;     /*file src mode, reference XMS_VOC_SRC_MODE*/
	public short                m_u16PacketLen;  /*Record Packet Length*/
	public byte                 m_u8CSPRecType;  /*1: barge-in, 2: non barge-in, reference XMS_CSPREC_TYPE*/
	public byte	              	m_u8StopMode;    /*Obsolete, stop record mode,referecne XMS_PLAYREC_STOP_MODE*/
	public byte	              	m_u8StopCode;    /*Obsolete, stop record when receive this dtmf code*/
	public byte                 m_s8IsMixEnable; /*is Mix*/
	public MixerControlParam_t  m_MixerControl = new MixerControlParam_t();  /*Mixer Contronl parameter*/
	public byte                 m_u8IsVADEnable; /*Is start to VAD Function, 0: Disable, 1: Enable*/
	public byte                 m_s8Rfu1[] = new byte[3];
} /*RecordCSPProperty_t*/

/*ACS control record */
class ControlRecord_t{
	public int             m_u32ControlType;  /*control record type,reference XMS_CTRL_RECORD_TYPE*/
	public int             m_u32StepSize;     /*step size: 0~65534*/
	public int             m_u32DelayStop;    /*Delay to stop record,reference to XMS_REC_DELAY_STOP_SWITCH*/
}/*ControlRecord_t*/

/*ACS CSPPlayProperty_t*/
class CSPPlayProperty_t{	
	public byte                m_u8TaskID;         /*play task ID*/	
	public byte                m_u8SrcMode;        /*file src mode, reference XMS_VOC_SRC_MODE*/
	public byte                m_u8DecodeType;     /*decode type, reference XMS_VOC_CODE_TYPE*/	
	public byte                m_s8Rfu1;        /*Reserved*/
	public int                 m_u32MaxSize;       /*play max size(BYTES),  0: file real size; >0: max play size*/
	public int                 m_u32MaxTime;       /*play max time(Seconds) 0: file real seconds; >0: max play seconds*/	
	public int                 m_u32StopMode;      /*stop play mode,referecne XMS_PLAYREC_STOP_MODE*/
	public int                 m_u32StopCode;      /*stop play when receive this dtmf code*/
	public byte                m_Rfu1[] = new byte[4];			
}/*CSPPlayProperty_t*/

/*CSPPlayDataInfo_t*/
class CSPPlayDataInfo_t{
	public short	m_u16DataLen;   		/*data length*/
	public byte		m_u8DataType;		    /*data type,0: voc,1:video,reference XMS_CSPPLAY_DATA_TYPE*/
	public byte		m_u8TaskID;	  		    /*task id*/
}/*CSPPlayDataInfo_t*/

/*ACS play3gpppropetry*/
class Play3gppProperty_t{	
	public byte                m_u8TaskID;              /*audio: play task ID*/	
	public byte                m_u8SrcMode;             /*audio: file src mode, reference XMS_VOC_SRC_MODE*/
	public byte                m_u8DecodeType;          /*audio: decode type, reference XMS_VOC_CODE_TYPE*/	
	public byte                m_u8Audio_tracks;        /*audio: audio tracks*/
	public byte                m_u8AmrFrameType;        /*audio: amr frame type*/
	public byte                m_u8AudioNoDecode;       /*audio: FALSE: AMR to line-decodetype(default value); TRUE: No decode;*/
	public byte                m_u8Rfu1[] = new byte[2];/*reserved*/
	public int                 m_u32MaxTime;            /*audio: play max time(Seconds) 0: file real seconds; >0: max play seconds*/	
	public int                 m_u32StopMode;           /*audio: stop play mode,referecne XMS_PLAYREC_STOP_MODE*/
	public int                 m_u32StopCode;           /*audio: stop play when receive this dtmf code*/
	public short               m_u16TimeOffset;         /*audio: start play at the file offset with time*/
	public short               m_u16PlayType;           /*audio: play type: 0-normal,1-index,referecnce XMS_PLAY_TYPE*/
	public short               m_u16PlayIndex;          /*audio: play index*/
	public short               m_s16Rfu2;               /*Reserved*/
	public byte                m_s8PlayContent[] = new byte[128];/*audio: play file name */
	public byte                m_u8VideoFrameRate;      /*video frame rate*/
	public byte	               m_u8VideoDecode_Type;    /*video: video decode type*/
	public byte	               m_u8VideoHigh;           /*video: video high*/
	public byte	               m_u8VideoWidth;          /*video: video width*/	
	public int                 m_u32VideoMaxTime;       /*video: play max time(Seconds) 0: file real seconds; >0: max play seconds*/	
	public short               m_u16VideoTimeOffset;    /*video: start play at the file offset with time*/
	public short               m_u16VideoPlayType;      /*video: play type: 0-normal,1-index,referecnce XMS_PLAY_TYPE*/
	public short               m_u16VideoPlayIndex;     /*video: play index*/
	public byte                m_u8VideoTaskID;         /*video: play video task ID*/
	public byte                m_u8MediaType;           /*common: media type XMS_MEDIA_TYPE*/        
	public byte                m_s8VideoPlayContent[] = new byte[128];/*video: play file name */
}/*PlayProperty_3gp_t*/

/*control 3gpp play */
class Control3gppPlay_t{
	public short             m_u16ControlType;  /*play control type,reference XMS_CTRL_PLAY_TYPE*/
	public short             m_u16StepTime;     /*play step time*/
	public short             m_u16TuneType;     /*tune type,reserved*/
	public short             m_u16SpeedSize;    /*speed size,reserved*/
	public byte              m_u8MediaType;     /*media type: 0: audio; 1: video; 4: A & V*/
	public byte              m_u8Reserv1[] = new byte[3];    /*reserve*/
}/*Control3gppPlay_t*/

/*ACS 3gpp record propetry*/
class Record3gppProperty_t{
	public int                m_u32MaxTime;          /*record max time, 0: no limit record time; >0: record max time*/	
	public byte	              m_u8StopMode;          /*stop record mode,referecne XMS_PLAYREC_STOP_MODE*/	
	public byte	              m_u8StopCode;	         /*stop record when receive this dtmf code*/

	public byte               m_s8IsAppend;          /*0: trunc record file; 1: append record file,reference XMS_REC_OPENFILE_TYPE*/	
	public byte	              m_u8AudioEncodeType;   /*encode type, reference XMS_VOC_CODE_TYPE*/	
	public byte	              m_u8AudioSRCMode;      /*file src mode, reference XMS_VOC_SRC_MODE*/
	public byte               m_u8AudioTracks;       /*audio channel,reference XMS_AUDIO_TRACKS*/
	public short              m_u16AudioMaxBitRate;  /*audio max bitrate,0~65535*/
	public short              m_u16AudioAverageBitRate;/*audio average bitrate,0~65535*/
	public byte               m_u8MediaType;
	public byte               m_s8AudioIsMixEnable;  /*is Mix, 0 : no mix,1: mix*/
	public MixerControlParam_t   m_AudioMixerControl = new MixerControlParam_t();  /*Mixer Contronl parameter*/
	
	public byte	              m_u8VideoEncodeType;  /*encode type, reference XMS_VIDEO_CODE_TYPE*/	
	public byte	              m_u8VideoFrameRate;   /*video frame rate,10~30*/
	public short              m_u16VideoWidth;      /*video width,176*/
	public short              m_u16VideoHeight;     /*video heigth,144*/
	public short              m_u16VideoMaxBitRate; /*video max bit rate,0~65535*/
	public short              m_u16VideoAverageBitRate;/*video average bit rate,0~65535*/
	public byte               m_Rfu2;
	public byte               m_s8VideoIsMixEnable; /*is Mix, 0 : no mix,1: mix*/
	public MixerControlParam_t   m_VideoMixerControl = new MixerControlParam_t();  /*Mixer Contronl parameter*/

	public byte               m_u8AudioProfiles;    /*audio profiles?*/
	public byte               m_u8AudioLevel;       /*audio level ?*/
	public short              m_u16AudioDecoderCfgLen;/*audio decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
	public byte               m_u8AudioDecoderCfg[] = new byte[200];/*audio decoder cfg*/
	
	public byte               m_u8VideoProfiles;    /*video profiles?*/
	public byte               m_u8VideoLevel;       /*video level?*/	
	public short              m_u16VideoDecoderCfgLen;  /*video decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
	public byte               m_u8VideoDecoderCfg[] = new byte[200];/*video decoder cfg?*/
	public byte            	  m_s8FileName[] = new byte[260];/*record file name*/
}/*Record3gpProperty_t*/

/*ACS control 3gpp record */
class Control3gppRecord_t
{
	public short             m_u32ControlType;  /*control record type,reference XMS_CTRL_RECORD_TYPE*/
	public byte              m_u8MediaType;     /*media type: reference to XMS_MEDIA_TYPE*/
	public byte              m_u8Reserv1;    /*reserve*/
	public int               m_u32StepTime;     /*step time*/
	public int               m_u32SpeedSize;    /*speed size,reserved*/
}/*Control3gpRecord_t*/

/*Acs unifail event*/
class Acs_UniFailure_Data
{
	public int          	m_s32AcsEvtState;   /*acs event state, -1*/
	public int		        m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
}

/*UserLedCtrl*/
class UserLedCtrl 
{
	public byte		m_u8LedTimeEnable;       /*Led ontime & offtime ctrl paramter enable? */	
	public byte		m_Rfu1;
	public short	m_u16OnTime;             /*LED ontime: 100~2000 ms*/
	public short	m_u16OffTime;            /*LED offtime: 100~2000 ms*/
	public byte     m_u8WatchDogOutEnbale;   /*LED watchdog out time ctrl paramter enable? */
	public byte     m_Rfu2;
	public short	m_u16WatchDogOutTime;    /*LED watchdog out time: 10~300 S*/
	public byte     m_u8WatchDogTimeEnable;  /*LED watchdog out state ctrl paramter enable? */
	public byte     m_Rfu3;
	public short	m_u16WatchDogOnTime;     /*LED watchdog ontime: 100~2000 ms*/
	public short	m_u16WatchDogOffTime;    /*LED watchdog offtime: 100~2000 ms*/
	public byte     m_u8FeedWatchDogEnable;  /*LED watchdog feed ? 0: feed not enable, 1: feed*/
	public byte     m_Rfu4[] = new byte[3];
}/*UserLedCtrl*/

class CmdParamData_GtdFreq_t
{	
	public short	m_u16Freq_Index;  /* Frequence index: 0-15*/
	public short    m_u16Freq_Coef;   /* Frequence*/
}/*CmdParamData_GtdFreq_t*/

class CmdParamData_GtdProtoType_t
{
	public short  	m_u16GtdID;
	public short	m_u16Freq_Mask;
	public short	m_u16Amp_Threshold;
	public short	m_u16Envelope_Mode;
	public short	m_u16Repeat_Count;
	public short	m_u16Min_On_Time1;
	public short	m_u16Max_On_Time1;
	public short	m_u16Min_Off_Time1;
	public short	m_u16Max_Off_Time1;
	public short	m_u16Min_On_Time2;
	public short	m_u16Max_On_Time2;
	public short	m_u16Min_Off_Time2;
	public short	m_u16Max_Off_Time2;
	
	public void InitGtdProtoTypeWithZero(){
		m_u16GtdID 			= 0;
		m_u16Freq_Mask 		= 0;
		m_u16Amp_Threshold  = 0;
		m_u16Envelope_Mode  = 0;
		m_u16Repeat_Count   = 0;
		m_u16Min_On_Time1   = 0;
		m_u16Max_On_Time1   = 0;
		m_u16Min_Off_Time1  = 0;
		m_u16Max_Off_Time1  = 0;
		m_u16Min_On_Time2   = 0;
		m_u16Max_On_Time2   = 0;
		m_u16Min_Off_Time2  = 0;
		m_u16Max_Off_Time2  = 0;
	}
}/*CmdParamData_GtdProtoType_t*/

/*AnalogTrunk Parameter Define*/
class CmdParamData_AnalogTrunk_t
{
	//CallIn Paramteter
	public short  m_u16CallInRingCount; //ring count before CallIn event
	public short  m_u16CallInRingTimeOut;//Unit:ms Ring TimeOut,when ring timed out ,state changed to DCS_Free
}/*CmdParamData_AnalogTrunk_t*/

/*VOC input control param*/
class VocInputControlParam_t 
{
	public byte   m_u8AgcEnable;       /*0:disable;1:enable*/
	public byte   m_u8AgcMode;         /*0:ALS mode; 1:AGC mode,reference XMS_AGC_MODE*/
	public byte   m_u8EcEnable;        /*0:disable;1:enable*/
	public byte   m_u8EcRefType;       /*0:ref from input;1:ref from output*/
	public byte   m_u8VadEnable;       /*0:disable;1:enable*/
	public byte   m_u8TadEnable;       /*0:disable;1:enable*/
	public byte   m_u8NrEnable;        /*0:disable;1:enable*/
	public byte   m_u8Reserved;        /*Rfu*/
	public short  m_u16FixGain;       /*0x400 = 0dB*/
	public short  m_u16EcRefCh;       /*Rfu*/
	public int    m_u32Reserved;      /*Rfu*/
}/*VocInputControl_t*/

/*VOC ouput control param*/
class VocOutputControlParam_t 
{
	public byte	             m_u8AgcEnable;	  /*0:disable;1:enable*/
	public byte	             m_u8AgcMode;	  /*0:ALS mode; 1:AGC mode*/
	public byte	             m_u8OutputType;  /*0:silence;1:from input;2:from play;3:from mixer,control by m_MixerControl,Reference XMS_VOC_OUTPUT_TYPE*/
	public byte	             m_u8Reserved; /**/
	public short	         m_u16FixGain;	  /*0x400 = 0dB*/
	public byte              m_s8Rfu[] = new byte[2];      /*Rfu*/
	public MixerControlParam_t	 m_MixerControl = new MixerControlParam_t();  /**/
}/*VocOutputControl_t*/

/*VOC GTD control param*/
class VocGtdControlParam_t
{
	public byte	m_u8ChannelEnable; /*0: all disable; 1: control by next params*/
	public byte	m_u8DTMFEnable;	   /*0:disable;1:enable*/
	public byte	m_u8MR2FEnable;	   /*0:disable;1:enable*/
	public byte	m_u8MR2BEnable;	   /*0:disable;1:enable*/
	public byte	m_u8GTDEnable;	   /*0:disable;1:enable*/
	public byte	m_u8FSKEnable;	   /*0:disable;1:enable*/
	public byte m_u8EXTEnable;     /*0 bit: DPD, 1 bit: PVD, 2 bit: MSK reference to EXT_ENABLE_TYPE enum*/
	public byte m_u8Reserved;      /*rfu*/
	public byte	m_u8GTDID[] = new byte[8];      /**/
}/*VocGtdControl_t*/

/*Voice param*/
class CmdParamData_Voice_t
{
	public byte                       m_u8InputCtrlValid;  /*is VocInputControl_t valid*/
	public byte                       m_u8PlayGainMode;    /*Play gain mode,reference XMS_PLAY_GAIN_MODE*/  
	public short                      m_u16PlayFixGain;    /*Play fix gain*/ 
	public VocInputControlParam_t	  m_VocInputControl = new VocInputControlParam_t();   /*valid to voc,not include RTP*/
	public byte                       m_u8OutputCtrlValid; /*is VocOutputControl_t valid*/
	public byte                       m_s8Rfu2[] = new byte[3];         /*Rfu*/
	public VocOutputControlParam_t	  m_VocOutputControl = new VocOutputControlParam_t();  /*valid to voc and RTP*/
	public byte                       m_u8GtdCtrlValid;    /*is VocGtdControl_t valid*/
	public byte                       m_s8Rfu3[] = new byte[3];         /*Rfu*/
	public VocGtdControlParam_t	      m_VocGtdControl = new VocGtdControlParam_t();	 /*valid to voc and RTP*/
}/*CmdParamData_Voice_t*/

/*Acs_CallControl_Data*/
class Acs_CallControl_Data
{
	public int         				 m_s32AcsEvtState;                 /*acs event state, 1: success; 0: failed*/
	public int       				 m_s32AcsEvtErrCode;               /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	public int                  	 m_s32CallClearCause;              /*Call clear cause code*/
	public byte                   	 m_u8CallingCategory;              /*Calling Category*/
	public byte                      m_u8CallingAddressIndicator;      /*Address Indicator*/
	public byte                      m_u8CalledAddressIndicator;       /*Address Indicator*/
	public byte                      m_s8Rfu1;
	public byte               		 m_s8CallingNum[] = new byte[32];  /*calling num*/
	public byte                      m_s8CalledNum [] = new byte[32];  /*called num*/
	public byte                      m_u8DRSCallDirectFlag;            /*Call direction flag, 0: Call In; 1: Call Out, reference XMS_DRS_CALL_DIRECT_DEF*/
	public byte                   	 m_s8Rfu2[] = new byte[31];
	public PrivateData_t             m_PrivData = new PrivateData_t(); /*private data*/
}/**/

/*Acs_MediaProc_Data*/
class Acs_MediaProc_Data
{
	public int 				         m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
	public int					     m_s32AcsEvtErrCode;  /*acs event errcode ,reference XMS_MEDIA_ERR_CODE*/	
	public byte                   	 m_u8TaskID;          /*play Task ID*/
	public byte                   	 m_u8GTD;             /*GTD ID*/	
	public byte                   	 m_s8Rfu[] = new byte[2];
	public int                  	 m_u32CurFileIndex;   /*current play file index*/
	public int                  	 m_u32CurFilePos;     /*current play pos*/
	public PrivateData_t           	 m_PrivData = new PrivateData_t();          /*private data*/
}/**/

/*AnalogUser Parameter Define*/
class CmdParamData_AnalogUser_t
{	
	// Call Out Parameter 
	public byte        				m_u8CallerIdOption;//0:disabled; 1:Fsk CallerId; 2:DTMF CallerId;,reference XMS_ANALOG_USER_CALLERID_OPT
	public byte        				m_u8RingCadenceType;//0: single-pulse ring; 1:double-pulse ring; 2: triple-pulse ring
	public byte        				m_u8CallOutRingTimeOut;// unit: second ; Ringing TimeOut ,it timetout ,then state return to DCS_FREE
	public byte        				m_u8Rfu1;
	public byte        				m_u8Rfu2[] = new byte[12];
}/*CmdParamData_AnalogUser_t*/

/*ACS Fax private param*/
class FaxPrivate_t
{
	public PrivateData_t   			m_PrivateData = new PrivateData_t();         /*privatedata head*/ 
	public DeviceID_t      			m_VoIPDevice = new DeviceID_t();          /*VoIP device ID*/
	public byte           			m_u8WorkMode;          /*Fax work mode,reference XMS_FAX_WORKMODE*/
	public byte           			m_s8Rfu1[] = new byte[3];           /*Rfu */
}/*FaxPrivate_t*/

/* Acs MediaEx Video Input Param*/
class Acs_MediaEx_Input_V
{
	public short	  m_u16Port;				/* local port */
	public byte		  m_u8Codec;				/* codec type */
	public byte		  m_u8PayloadType;			/* rtp payload type (if dynamic) */
	public short      m_u32ProfileLevelId;		/* codec extra attribute */
    public short      decoderConfigLength;
	public byte       decoderConfigInfo[] = new byte[128];
}/*Acs_MediaEx_Input_V*/

/* Acs MediaEx Output Param */
class Acs_MediaEx_Output_V
{
	public byte		  m_s8IP[] = new byte[20];				/* dest address */
	public short	  m_u16Port;				/* dest port */
	public byte		  m_u8Codec;				/* codec type */
	public byte		  m_u8PayloadType;		/* rtp payload type (if dynamic) */
	public short	  m_u16ResX;				/* resolution x */
	public short	  m_u16ResY;				/* resolution y */
	public byte		  m_u8Fps;				/* framerate in fps */
	public short	  m_u16Kbps;				/* bitrate in Kbps */
}/*Acs_MediaEx_Output_V*/

/* Acs MediaEx Audio Output Param*/
class Acs_MediaEx_Output_A
{
	public byte		  m_s8IP[] = new byte[20];				/* dest address */
	public short	  m_u16Port;				/* dest port */
	public byte		  m_u8Codec;				/* codec type */
	public byte		  m_u8PayloadType;		/* rtp payload type (if dynamic) */
}/*Acs_MediaEx_Output_A*/

/* Acs MediaEx Play Param */
class Acs_MediaEx_Play
{
	public PrivateData_t   	m_PrivateData = new PrivateData_t();			/*privatedata head*/
	public byte				m_s8SrcName[] = new byte[128];	/* file name */
	public int				m_u32Start;				/* start time */
	public byte				m_u8Loop;				/* loop */
	public Acs_MediaEx_Output_A	audio = new Acs_MediaEx_Output_A();			/* audio output param */
	public Acs_MediaEx_Output_V	video = new Acs_MediaEx_Output_V();			/* video output param */
	public byte					s8OverlayImage[] = new byte[200];
}/*Acs_MediaEx_PlayFile*/

/* Acs 3GVConf Play Param */
class Acs_3GVConf_Play
{
	public PrivateData_t   	m_PrivateData = new PrivateData_t();			/*privatedata head*/
	public DeviceID_t       m_device 	  = new DeviceID_t();			/*voc conf DeviceID*/
	public Acs_MediaEx_Play m_play 		  = new Acs_MediaEx_Play();			/*Acs_MediaEx_PlayFile*/
}/*Acs_MediaEx_PlayFile*/

/* Acs MediaEx Transcode Param */
class Acs_MediaEx_Transcode
{
	public PrivateData_t			m_PrivateData 	 = new PrivateData_t();	/*privatedata head*/ 
	public Acs_MediaEx_Input_V		input		  	 = new Acs_MediaEx_Input_V();			/* input param */
	public Acs_MediaEx_Output_V		output 		  	 = new Acs_MediaEx_Output_V();			/* output param */
	public byte						s8OverlayImage[] = new byte[200];
}/*Acs_MediaEx_Transcode*/

/* Acs MediaEx Conference Param */
class Acs_MediaEx_Conference
{
	public PrivateData_t			m_PrivateData 	 = new PrivateData_t();	/*privatedata head*/ 
	public Acs_MediaEx_Input_V		input[] 	  	 = new Acs_MediaEx_Input_V[16];		/* input param */
	public Acs_MediaEx_Output_V		output[] 	  	 = new Acs_MediaEx_Output_V[16];		/* output param */
	public byte						s8OverlayImage[] = new byte[200];
	
	public Acs_MediaEx_Conference(){
		for (int i = 0; i < 16; i++){
			input[i] = new Acs_MediaEx_Input_V();
			output[i] = new Acs_MediaEx_Output_V();
		}
	}
}/*Acs_MediaEx_Conference*/

/* Acs MediaEx Record Param */
class Acs_MediaEx_Record
{
	public PrivateData_t			m_PrivateData 	 = new PrivateData_t();			/*privatedata head*/
	public byte						m_s8DstName[] 	 = new byte[128];	/* file name */
	public Acs_MediaEx_Output_A		audio			 = new Acs_MediaEx_Output_A();			/* audio output param */
	public Acs_MediaEx_Output_V		video			 = new Acs_MediaEx_Output_V();/* video output param */
}/*Acs_MediaEx_Record*/

/* Acs 3GVConf Record Param */
class  Acs_3GVConf_Record
{
	public PrivateData_t   			m_PrivateData 	= new PrivateData_t();			/*privatedata head*/
	public DeviceID_t         		m_device 		= new DeviceID_t();			/*voc conf DeviceID*/
	public Acs_MediaEx_Record   	m_record 		= new Acs_MediaEx_Record();			/*Acs_MediaEx_RecordFile*/
}/*Acs_MediaEx_RecordFile*/

/* Acs 3GVConf Cmd Param */
class Acs_3GVConf_Cmd_V
{
	public DeviceID_t               m_device 	    = new DeviceID_t();
	public Acs_MediaEx_Input_V      m_input			= new Acs_MediaEx_Input_V();
	public Acs_MediaEx_Output_V     m_output		= new Acs_MediaEx_Output_V();
	public byte                    	m_u8Visible;
	public byte                    	m_u8CmdType;
}/*Acs_3GVConf_Cmd_V*/

/*Acs_3GVConf_LayoutList*/
class Acs_3GVConf_LayoutList 
{
	public DeviceID_t               m_device[] = new DeviceID_t [16];
	
	public Acs_3GVConf_LayoutList(){
		for (int i = 0; i < 16; i++){
			m_device[i] = new DeviceID_t();
		}
	}
}/*Acs_3GVConf_LayoutList*/

/*Acs_3GVConf_VisibleList*/
class Acs_3GVConf_VisibleList 
{
	public DeviceID_t               m_device[] = new DeviceID_t[16];
	
	public Acs_3GVConf_VisibleList(){
		for (int i = 0; i < 16; i++){
			m_device[i] = new DeviceID_t();
		}
	}
}/*Acs_3GVConf_VisibleList*/

/* Acs MediaEx Conference Layout */
class Acs_MediaEx_ConfLayout
{
	public PrivateData_t			m_PrivateData = new PrivateData_t();	/*privatedata head*/ 
	public int						layout[] = new int[16];
}/*Acs_MediaEx_ConfLayout*/

class Color{
	public byte 					m_u8R;
	public byte 					m_u8G;
	public byte 					m_u8B;
}

class Point{
	public int 						m_x;
	public int 						m_y;
}

class FontParam{
	public double 					m_f64DBSize;
	public double 					m_f64DBBlank;
	public double 					m_f64DBGap;
	public double 					m_f64DBAngle;
	public int						m_bUnderLine;
	public Color					m_strcutColor = new Color();
}

class PutTextInPicture_Param{
	public byte						m_u8PutByType;
	public byte						m_u8PutByLevel;
	public byte						m_s8PutText[] = new byte[260];
	public short					m_u16FontType;
	public FontParam				m_structFontParam = new FontParam();
	public float 					m_f32Diaphaneity;	
	public Point					m_structPoint = new Point();
}

/*Acs_AnalogMEG_CMD*/
class Acs_AnalogMEG_CMD 
{
	public byte						m_u8Channel_Enable;
	public byte						m_u8CallOut;
	public byte						m_u8RingTime;
	public byte						m_u8Reservered;
}/*Acs_AnalogMEG_CMD*/

/*ACS Event Head*/
class ACS_EVT_HEAD
{
	public PKG_HEAD_STRUCT  		m_PkgEvtHead = new PKG_HEAD_STRUCT();  /*ITP package head*/
	public Acs_Evt_t        		m_AcsEvt_t	 = new Acs_Evt_t();    /*acs event package head*/
}/**/

class ITP_GUID_tag{
	public byte   					m_u8ModuleType;  //
	public byte   					m_u8MainFuncId;  //
	public byte   					m_u8SubFuncId;   //
	public byte   					m_u8UnitId;      //
	public short 					m_u16ChanId;     //
}

class PKG_HEAD_STRUCT{
	public byte						m_u8PkgFlag;	//
	public byte						m_u8PkgExtend;	//
	public short					m_u16DataLen;	//

	//
	public ITP_GUID_tag 			ITP_GUID = new ITP_GUID_tag();
 
	public short 					m_u16Reserve;     //
}

/*ACS Get 3GPP file config add by fys*/
class Get3gppCfg_t{
	public byte              m_u8MediaType;                /*media type: XMS_MEDIA_TYPE*/
	public byte              m_u8AudioFileType;            /*audio file type: XMS_CFG_TYPE*/
	public short             m_u16AudioFileIndex;          /*audio file index: 0~1023*/
	public byte              m_s8AudioFileName[] = new byte[260];  /*audio file path and name*/
	public byte              m_u8VideoFileType;            /*video file type: XMS_CFG_TYPE*/
	public byte              m_u8Rfu1;                     /*reserve*/
	public short             m_u16VideoFileIndex;          /*video file index: 0~1023*/
	public byte              m_s8VideoFileName[] = new byte[260];  /*video file path and name*/
}/*Get3gppCfg_t*/

/*SigMon_t*/
class SigMon_t
{
	public byte        m_u8MonSigType;     /*singnal type,reference XMS_SIGMON_SIG_TYPE*/
	public byte        m_u8MonPackType;    /*Signal Pakcet type,reference XMS_SIGMON_PACK_TYPE*/	
	public byte        m_s8Rfu1[] = new byte[6];        /*Rfu*/	
}/*SigMon_t*/

/*CmdParamData_RTPXInput_t*/
class CmdParamData_RTPXInput_t
{
	public byte    	  m_u8ChanEnable;       /*Enable flag, 0: disable; 1: enable*/
	public byte    	  m_u8MediaType;        /*Data type,reference XMS_VOIP_MEDIA_CAPS*/
	public byte       m_u8PayloadType;      /*Payload type*/
	public byte    	  m_u8Rfu;              /*reserved*/ 
}/*CmdParamData_RTPXInput_t*/

/*CmdParamData_RTPXInput_A_t*/
class CmdParamData_RTPXInput_A_t
{
	public byte       m_u8ChanEnable;       /*Enable flag, 0: disable; 1: enable*/
	public byte       m_u8MediaType;        /*Data type,reference XMS_VOIP_MEDIA_CAPS*/
	public byte       m_u8PayloadType;      /*Payload type*/
	public byte       m_u8Decode;           /*Decode enable flag, 0: disable; 1: enable*/ 
}/*CmdParamData_RTPXInput_A_t*/
 
/*CmdParamData_RTPXOutput_t*/
class CmdParamData_RTPXOutput_t
{
	public byte       m_u8ChanEnable;       /*Enable flag, 0: disable; 1: enable*/
	public byte       m_u8MediaType;        /*Data type,reference XMS_VOIP_MEDIA_CAPS*/
	public byte       m_u8PayloadType;      /*Payload type*/
	public byte       m_u8SRC_Ctrl1;        /*Source type,reference XMS_MIXER_TYPE*/
	public short      m_u16SRC_Id1;         /*Source channel ID*/
	public short   	  m_u16RemotePort;	   /*Remote port*/
	public int		  m_u32RemoteIP;		   /*Remote IP*/
}/*CmdParamData_RTPXOutput_t*/

/*CmdParamData_RTPXOutput_A_t*/
class CmdParamData_RTPXOutput_A_t
{
	public byte       m_u8ChanEnable;       /*Enable flag, 0: disable; 1: enable*/
	public byte       m_u8MediaType;        /*Data type,reference XMS_VOIP_MEDIA_CAPS*/
	public byte       m_u8PayloadType;      /*Payload type*/
	public byte       m_u8Encode;           /*Encode enable flag, 0: disable; 1: enable*/ 
	public byte       m_u8SRC_Ctrl1;        /*Source 1 type,reference XMS_MIXER_TYPE*/
	public byte       m_u8SRC_Ctrl2;        /*Source 2 type,reference XMS_MIXER_TYPE*/
	public short      m_u16SRC_Id1;         /*Source channel 1 ID*/
	public short	  m_u16SRC_Id2;         /*Source channel 2 ID*/
	public short   	  m_u16RemotePort;	   /*Remote port*/
	public int		  m_u32RemoteIP;		   /*Remote IP*/
}/*CmdParamData_RTPXOutput_A_t*/

/*CmdParamData_RTPXAddr_t*/
class CmdParamData_RTPXAddr_t
{
	public int		  m_u32RemoteIP;		   /*Remote IP*/
	public short      m_u16RemotePort;	   /*Remote port*/
	public byte   	  m_u8Rfu[] = new byte[2];		   /*Reserved*/
}/*CmdParamData_RTPXOutput_t*/

/*ACS CSP record private parma*/
class CSPRecordPrivate_t
{
	public PrivateData_t  	 m_PrivateData = new PrivateData_t();         /*privatedata head*/ 
	public byte              m_u8CspRecPrivType;    /*directly send cmd to dsp,0:no,1:yes,reference XMS_CSPREC_PRIV_TYPE*/
	public byte              m_u8CmdDirect;         /*directly send cmd to dsp,0:no,1:yes,reference XMS_CSPREC_CMD_OPT*/
	public byte              m_s8Rfu1[] = new byte[2];
}/**/

/*ACS CSP control record private parma*/
class ControlCSPRecordPrivate_t
{
	public PrivateData_t   	 m_PrivateData = new PrivateData_t();                  /*privatedata head*/ 
	public byte           	 m_u8CtrlCspRecPrivType;         /*directly send cmd to dsp,0:no,1:yes,reference XMS_CONTROL_CSPREC_PRIV_TYPE*/
	public byte           	 m_u8CmdDirect;                  /*directly send cmd to dsp,0:no,1:yes,reference XMS_CONTROL_CSPREC_CMD_OPT*/
	public byte           	 m_s8Rfu1[] = new byte[2];
}/**/

/*ACS answer call private param*/
class AnswerCallPrivate_t
{
	public PrivateData_t     m_PrivateData = new PrivateData_t();         /*privatedata head*/ 
	public int		         m_s32AnswerType;       /*answer type*/
}/*AnswerCallPrivate_t*/

/*Acs_TransAddHeader*/
class Acs_TransAddHeader{
	public int		         m_u32Op;		               /*set param type, 0: clear old config, 
	                                         				1: set new config, reference to 
	                                         				XMS_FAX_PAGE_HEADER_TYPE*/
    public short  			 m_u16XPos;		               /*the x of picture position,*/
    public short  			 m_u16YPos;                     /*the y of picture position,*/
    public byte   			 m_u8Data[] = new byte[73];                  /*define by user for fax picture*/
    public byte   			 m_u8Rsrv;
    public int  			 m_u32FontSize;
    public int  			 m_u32Header;
}/*Acs_TransAddHeader*/

/*Acs_TransAddHeaderEx*/
class Acs_TransAddHeaderEx{
	public int			     m_u32Op;		               /*set param type, 0: clear old config, 
	                                         				1: set new config, reference to 
	                                         				XMS_FAX_PAGE_HEADER_TYPE */
	public short  		     m_u16XPos;		               /*the x of picture position,*/
	public short  		     m_u16YPos;                     /*the y of picture position,*/
	public int			     m_u32FontSize;                 /* 1-7 */
	public byte   		     m_u8Data[] = new byte[73];                  /*define by user for fax picture*/
}/*Acs_TransAddHeaderEx*/

/*Acs_TransAddFile*/
class Acs_TransAddFile{
	public int			     m_u32Op;			           /*Send Multi File param type, 
	                                         				0: clear file queue, 2: add 
	                                         				a new file to file queue, 
											 				reference to XMS_FAX_M_FILE_TYPE*/
	public byte			     m_strFileName[] = new byte[256];            /*the file name of need to be sent in a fax*/
}/*Acs_TransAddFile*/

/*Acs_SetECM*/
class Acs_SetECM{
	public byte   		     m_u8FaxECMMode;			       /*fac type, 0: normal; 1: Ecm, reference to XMS_FAX_ECM_MODE_TYPE*/
}/*Acs_SetECM*/

/*Acs_SetFaxBps*/
class Acs_SetFaxBps
{
	public byte   		     m_u8BPS;                       /*fax transfor speed, referece to XMS_FAX_BPS_TYPE*/			    
}/*Acs_SetFaxBps*/

/*ACS VoIP Call private param*/
class VoIPCallPrivate_t{
	public PrivateData_t     m_PrivateData = new PrivateData_t();         /*privatedata head*/ 
	public int          	 m_s32Protocol;         /*protocol type*/
	public byte          	 m_s8CallerAddress[] = new byte[20]; /*Caller Address*/
	public int          	 m_s32CallerPort;       /*Caller Port*/
	public byte           	 m_s8CallerUserID[] = new byte[40];  /*Caller UserID*/		
	public byte           	 m_s8CalleeAddress[] = new byte[20]; /*Callee Address*/
	public int          	 m_s32CalleePort;       /*Callee Port*/
	public byte           	 m_s8CalleeUserID[] = new byte[40];  /*Callee UserID*/		
	public byte           	 m_u8MediaCapNum;       /*media capability number*/
	public byte           	 m_u8MediaCapList[] = new byte[10];  /*media capability list*/
}/*VoIPCallPrivate_t*/

/*ACS VoIP Call private param*/
class VoIPCallPrivateEx_t{
	public PrivateData_t   	 m_PrivateData = new PrivateData_t();         /*privatedata head*/ 
	public int          	 m_s32Protocol;         /*protocol type*/
	public byte           	 m_s8CallerAddress[] = new byte[20]; /*Caller Address*/
	public int          	 m_s32CallerPort;       /*Caller Port*/
	public byte           	 m_s8CallerUserID[] = new byte[40];  /*Caller UserID*/		
	public byte           	 m_s8CalleeAddress[] = new byte[20]; /*Callee Address*/
	public int          	 m_s32CalleePort;       /*Callee Port*/
	public byte            	 m_s8CalleeUserID[] = new byte[40];  /*Callee UserID*/		
	public byte           	 m_u8MediaCapNum;       /*media capability number*/
	public byte           	 m_u8MediaCapList[] = new byte[10];  /*media capability list*/
	public byte				 u8MediaMode;			// media mode 0:noset(sendrecv) 1:sendonly 2:recvonly 3:sendrecv
}/*VoIPCallPrivate_t*/

/*ACS Voip Open private param*/
class VoIPOpenPrivate_t
{
	public PrivateData_t 	m_PrivateData = new PrivateData_t();		/*privatedata head*/
	public byte				m_u8RtpMode;		/*RTP Mode:0-default auto,1-user control*/
}/*VoIPOpenPrivate_t*/

/*ACS VoIP Forward Call param*/
class VoIPForwardCallPrivate_t
{
	public PrivateData_t    m_PrivateData = new PrivateData_t();         /*privatedata head*/ 
	public int          	m_s32Protocol;         /*protocol type*/
	public byte           	m_s8CallerAddress[] = new byte[20]; /*Caller Address*/
	public int          	m_s32CallerPort;       /*Caller Port*/
	public byte           	m_s8CallerUserID[] = new byte[40];  /*Caller UserID*/		
	public byte				m_s8TelNo[] = new byte[20];	       /*telephone number*/
}/*VoIPForwardCallPrivate_t*/

/*ACS VoIP Alert private param*/
class VoIPAlertPrivate_t
{
	public PrivateData_t    m_PrivateData = new PrivateData_t();         /*privatedata head*/ 
	public byte           	m_u8MediaCapNum;       /*media capability number*/
	public byte           	m_u8MediaCapList[] = new byte[10];  /*media capability list*/
}/*VoIPAlertPrivate_t*/

/*ACS VoIP Alert private param*/
class VoIPAlertPrivateEx_t
{
	public PrivateData_t   	m_PrivateData;         /*privatedata head*/ 
	public byte           	m_u8MediaCapNum;       /*media capability number*/
	public byte           	m_u8MediaCapList[] = new byte[10];  /*media capability list*/
	public short			u16AlertCode;			// alert code for sip, support 180,181,182,183, default is 183
}/*VoIPAlertPrivate_t*/

/*ACS VoIP Answer private param*/
class VoIPAnswerPrivate_t
{
	public PrivateData_t    m_PrivateData = new PrivateData_t();         /*privatedata head*/ 
	public byte             m_u8MediaCapNum;       /*media capability number*/
	public byte             m_u8MediaCapList[] = new byte[10];  /*media capability list*/
}/*VoIPAnswerPrivate_t*/

class VoIP_RTP_Format_t{
	public byte       		u8CodecType;		/* codec type */
	public byte       		u8PayloadType;		/* payload type */
}	

class VoIP_RTP_Session_t
{
	public int				 u32IP;				/* remote rtp address */
	public short			 u16Port;			/* remote rtp port */
	public VoIP_RTP_Format_t tx = new VoIP_RTP_Format_t(); /* transmit format */ 
	public VoIP_RTP_Format_t rx = new VoIP_RTP_Format_t(); /* receive format */
}	

class VoIPConnectPrivate_t
{
	public PrivateData_t      m_PrivateData = new PrivateData_t();			/*privatedata head*/ 
	public VoIP_RTP_Session_t audio = new VoIP_RTP_Session_t();
	public VoIP_RTP_Session_t video = new VoIP_RTP_Session_t();
}/*VoIPConnectPrivate_t*/

class ChCodec{
	public byte			    m_u8Enable;				/* enable flag */
	public byte			  	m_u8TxCodec;			/* tx codec */
	public byte			  	m_u8TxPayloadType;		/* tx payload type (if dynamical) */
	public byte			  	m_u8RxCodec;			/* rx codec */
	public byte			  	m_u8RxPayloadType;		/* rx payload type (if dynamical) */
}

/* Acs VoIP RTP Codec struct */
class Acs_VoIP_RTPCODEC{
	public ChCodec 			audio = new ChCodec();
	public ChCodec 			video = new ChCodec();
}/*Acs_VoIP_RTPCODEC*/

class ChMedia{
	public byte			 	m_u8Enable;			/* enable flag */
	public byte			 	m_s8IP[] = new byte[20];			/* ip address */
	public short			m_u16Port;			/* port */
	public byte			 	m_u8TxCodec;			/* tx codec */
	public byte			 	m_u8TxPayloadType;		/* tx payload type (if dynamical) */
	public byte			 	m_u8RxCodec;			/* rx codec */
	public byte			 	m_u8RxPayloadType;		/* rx payload type (if dynamical) */	
}

/* Acs Voip RTP Open struct */
class Acs_VoIP_RTPOpen
{
	public byte			 	m_u8Enable;				/* enable/disable rtp session */
	public byte			 	m_u8PayloadDtmf;		/* dynamic payload type for rtp dtmf */
	public byte			 	m_u8PayloadTone;		/* dynamic payload type for rtp tone */	
    public ChMedia 			audio = new ChMedia();
    public ChMedia 			video = new ChMedia();
}/*AcsVoIP_RTPOpen*/

/* Acs_VoIP_MediaInfo */
class Acs_VoIP_MediaInfo{
	public byte			    payload_dtmf;
	public byte			    payload_tone;
	public byte			    u8AudioEnabled;
	public byte			    s8AudioAddress[] = new byte[20];			// host address
	public short		  	u16AudioPort;			// port number
    public byte			    u8VideoEnabled;
    public byte			    s8VideoAddress[] = new byte[20];			// host address
    public short		  	u16VideoPort;			// port number
    public byte			    u8MediaCapNum;                      // media capability number
    public byte			    u8MediaCapList[] = new byte[10];                 // media capability list
}/*Acs_VoIP_MediaInfo*/

class ChAddr{
    public byte				m_u8Enable;			/* enable flag */
    public byte				m_s8IP[] = new byte[20];			/* ip address */
    public short			m_u16Port;			/* port */
}

/* Acs VoIP RTP Address struct */
class Acs_VoIP_RTPADDR {
	public ChAddr 			audio = new ChAddr();
	public ChAddr 			video = new ChAddr();
}/*Acs_VoIP_RTPADDR*/

/* Acs VoIP RTP Session struct */
class Acs_VoIP_RTPSESSION {
	public byte	m_u8Enable;				/* enable/disable rtp session */
	public byte	m_u8PayloadDtmf;		/* dynamic payload type for rtp dtmf */
	public byte	m_u8PayloadTone;		/* dynamic payload type for rtp tone */
}/*Acs_VoIP_RTPSESSION*/

class VoIPDummyPrivate_t{
	public PrivateData_t   m_PrivateData = new PrivateData_t();			/*privatedata head*/ 
}

/* Acs VoIP Registration State struct */
class Acs_VoIP_REGSTATE 
{
	public short			m_u16SlotID;			/* Registration Slot ID */
	public byte				m_u8Protocol;			/* VoIP Protocol */
	public byte				m_u8State;				/* Registration State */
	public byte				m_s8TelNo	[] = new byte[20];			/* Client Telephone-subscriber */
	public byte				m_s8Address [] = new byte[20];		/* Client Address */
	public short			m_u16Port;				/* Client Port */
	public byte				m_s8UserID  [] = new byte[40];			/* Client UserID */
}/*Acs_VoIP_REGISTRATION*/

/* Acs_VoIP_Regist Struct */
class Acs_VoIP_Regist
{
	public short			m_u16SlotID;			/* Registration Slot ID */
	public byte				m_u8Protocol;			/* VoIP Protocol */
	public byte				m_u8State;			/* Registration State */
	public byte				m_s8TelNo	[] = new byte[20];			/* Client Telephone-subscriber */
	public byte				m_s8Address [] = new byte[20];		/* Client Address */
	public short			m_u16Port;			/* Client Port */
	public byte				m_s8UserID  [] = new byte[40];			/* Client UserID */	
}/*Acs_VoIP_Regist*/

/* Acs_VoIP_Regist_Response struct */
class Acs_VoIP_Regist_Response
{
	public byte				m_u8State;		/* Registration State */    
    public byte				m_s8TelNo	[] = new byte[20];	    	/* subscriber number */
    public byte				m_s8Username[] = new byte[40];	/* username for authorization */
}/*Acs_VoIP_Regist_Response*/

/* Acs VoIP Refer struct */
class Acs_VoIP_Refer 
{
	public byte				m_u8Protocol;			/* VoIP Protocol */
	public byte				m_u8State;				/* Registration State */
	public byte				m_s8TelNo	[] = new byte[20];			/* Client Telephone-subscriber */
	public byte				m_s8Address [] = new byte[20];		/* Client Address */
	public short			m_u16Port;				/* Client Port */
	public byte				m_s8UserID  [] = new byte[40];			/* Client UserID */
	public byte			    m_u8ReferedToUnitId;	// Referd-to header with replaces tag when act or sact
	public short		    m_u16ReferedToChanId;	// Referd-to header with replaces tag when act or sact
}/*Acs_VoIP_Refer*/

/* Acs VoIP Refer Response struct */
class Acs_VoIP_Refer_Response 
{
	public byte				m_u8ReferFlag;			/* refer flag */
	public byte				m_u8SrcUnitID;				/* source Unit ID */
	public short			m_u16SrcChanID;				/* source Channel ID */
	public byte				m_u8DestUnitID;				/* destination Unit ID */
	public short			m_u16DestChanID;				/* destination Channel ID */
	public byte				m_s8TelNo[]	 	 = new byte[20];			/* Client Telephone-subscriber */
	public byte				m_s8Address[]	 = new byte[20];		/* Client Address */
	public short			m_u16Port;				/* Client Port */
	public byte				m_s8UserID[]	 = new byte[40];			/* Client UserID */
}/*Acs_VoIP_Refer_Response*/

/* Acs VoIP Refer Result struct */
class Acs_VoIP_ReferResult 
{
	public byte				m_u8Protocol;		/* protocol */
	public byte				m_u8State;			/* state */
	public byte				m_u8Reason;			/* reason */
}/*Acs_VoIP_ReferResult*/

/* Acs VoIP Refer Result struct */
class Acs_VoIP_Notify
{
	public int				m_u32StatusCode;		/* statusCode */
}/*Acs_VoIP_Notify*/

/* Acs VoIP Registraion Response struct */
class Acs_VoIP_REGRESP 
{
	public short			m_u16SlotID;			/* Registration Slot ID */
	public byte				m_u8Granted;			/* grant registration */
	public byte				m_s8Password[] = new byte[20];		/* password for sip authentication */
}/*Acs_VoIP_REGRESP*/

/*analog flash param*/
class CmdParamData_FlashParam_t
{
	public byte				m_u8MinHookFlashTime;		//default is 5, //in units of 20ms
	public byte				m_u8MaxHookFlashTime;		//default is 25,in units of 20ms	
}/*CmdParamData_FlashParam_t*/

class CmdParamData_TrunkFlashParam_t{
	public byte				m_u8HookFlashTime;		//default is 10, //in units of 20ms
	public byte				m_u8reserved[] = new byte[3];		
}

/*Analoge Rec Module Voltage param*/
class CmdParamData_AnalogRecVoltage_t
{
	public byte			    m_u8Valtage;                   //[0, 54], default is 54
	public byte			    m_u8Reserve[] = new byte[3];                //reserve
}

class CmdParamData_ReadSn_t
{
	public byte		       m_u8ReadSn[]   = new byte[13];
	public byte		       m_u8Reserved[] = new byte[3];
}

/*silence voice detect param*/
class CmdParam_SilenceDetectParam_t	{ 	
	public int 		       m_s32SilenceLevel;            //silence detect level(db),default: -42, [-60, -20]        
	public int 		       m_s32SilenceTimer;            //silence detect timer(ms)
	public int 		       m_s32Reserved2;               //reserve
}/*CmdParam_SilenceDetectParam_t*/

/*CmdParam_ActiveMemDetectParam_t is obsolete now*/
/*active member detect param*/
class CmdParam_ActiveMemDetectParam_t	{ 	
	public int 		       m_s32VadLevel;                //active conf member detect level(db), obsolete        
    public int 		       m_s32Reserved1;               //reserve                              obsolete
} /*CmdParam_ActiveMemDetectParam_t*/

/*VAD min level detect param*/
class CmdParam_VADMinDetectParam_t	
{ 	
	public int 			   m_s32VadLevel;                //VAD min detect level(db), default: -54, [-60, -20] 
	public short 		   m_u16VadInterval;             //VAD interval(5ms), default: 200, [10, 300]       
	public byte 		   m_u8Reserved1[] = new byte[2];             //reserve
} /*CmdParam_VADMinDetectParam_t*/

/*Board Common param set*/
class CmdParam_BoardCommonParam_t	
{ 	
	public byte 		   m_u8IsCNGEnable;              //the switch of CNG, 0: Disable, 1: Enable 
	public short 		   m_u16CNGGainLevel;            //the value of CNG gain,default: 9,[4, 15]       
	public byte 		   m_u8Reserved1[] = new byte[29];            //reserve
} /*CmdParam_BoardCommonParam_t*/

/*FSK Send/Recv param*/
class	CmdParamData_FskParam_t
{
	public short 		   rxFilterWindow;         /*default is 4, shouldn't change it */
	public short 		   rxPeriodTheshold;       /*default is 320,shouldn't change it */
	public short 		   rx55Count;              /*default is 6, can be changed as needed */
	public short 		   rxAllOneSamples;        /*default is 200, can be changed as needed */
	public short 		   rxDataTimeOut;          /*default is 20ms,can be changed as needed */
	public short 		   txBit1Freq;             /*default is 1200,can be changed as needed */
	public short 		   txBit0Freq;             /*default is 2200,can be changed as needed */
	public short 		   tx55Count;              /*default is 30, can be changed as needed  */
	public short 		   txAllOneSamples;        /*default is 600, can be changed as needed */
	public short 		   reserved[] = new short[3];
}/*CmdParamData_FskParam_t*/

/* Acs Conference Active Member List struct */
class CmdParamConf_MemberState_t
{
	public byte 		   m_s8NormalVad[] = new byte[16];       /*the buffer of normal active member in the conferece*/
	public byte 		   m_s8IPVad[] 	   = new byte[16];           /*the buffer of IP active member in the conferece*/
	public byte 		   m_u8TotalOfConfMem;      /*the total of members in the conferece*/
	public byte 		   m_u8Ref[] 	   = new byte[3];              /*reserver*/
} 

/* Acs Set Conference Vad Check Interval struct */
class CmdParamConf_VadInterval_t
{
	public short 	  	   m_u16VadCheckInterval;   /*The Interval Of Check Vad In A Conferece: [30, 65535], Unit: ms*/
	public byte 	   	   m_u8RptConfMemEnable;    /*If Auto Report Active Conference member, 1: Enable, 0: Disable*/
	public byte 	       m_u8Ref[] = new byte[5];              /*reserve*/
}

/* Acs VoIP H.245 UserInputIndication struct */
class CmdParamData_GtgFreq_t
{	
	public short 	  	   m_u16Freq_Index;  /* Frequence index: 0-15*/
	public short 	  	   m_u16Freq_Coef;   /* Frequence*/
}/*CmdParamData_GtgFreq_t*/

//---This Struct according to ITP_GTG_Template(DSP_PACKET_DEF.H)
class CmdParamData_GtgProtoType_t
{
	public byte 	   	   m_u8GTG_id;	        /*Ӱ��GTG ID����Чֵ0x30-0x3F*/
	public byte 	   	   m_u8Reserved1;		/*����*/
	public short 	  	   m_u16Reserved2;		/*����*/

	//-------ITP_GTG_Prototype--------
	public byte 		   m_u8Freq1_Index;
	public byte 		   m_u8Freq2_Index;
	public short 	  	   m_u16Freq1_Amp;
	public short 	  	   m_u16Freq2_Amp;
	public short 	  	   m_u16Envelope_Mode;
	public short 	  	   m_u16Repeat_Count;
	public short 	  	   m_u16On_Time1;
	public short 	  	   m_u16Off_Time1;
	public short 	  	   m_u16On_Time2;
	public short 	  	   m_u16Off_Time2;
	public short 	  	   m_u16Reserved;		/*����*/
}/*CmdParamData_GtgProtoType_t*/

/* Acs VoIP H.245 UserInputIndication struct */
class CmdParamData_CTCLKNET_t
{
	public byte 	   	   m_u8NetRef1;       /*L_NET0=0x08,L_NET1=0x09,L_NET2=0x0A,L_Net3=0x0B*/
	public byte 	   	   m_u8SysClockType;  /*reference to XMS_BOARD_CLOCK_TYPE*/
	public byte 	   	   m_u8Rfu[] = new byte[2];        /* Reserved*/
}

/* Acs VoIP H.245 UserInputIndication struct */
class Acs_VoIP_H245UII
{
	public byte 	   	   m_s8String[] = new byte[100];		/* UserInputIndication string (general string)*/
	public byte 	 	   m_s8Signal;				/* UserInputIndication signal type (dtmf char in "0123456789#*ABCD!")*/
	public byte 	       m_Rfu[] 		= new byte[3];               /* Reserved*/
	public int 	 		   m_u32Duration;			/* UserInputIndication signal duration (in milliseconds)*/
}/*Acs_VoIP_H245UII*/

/* Acs Video Link Param */
class Acs_Video_Link_Param
{
	public PrivateData_t   m_PrivateData       = new PrivateData_t();	/*privatedata head*/ 
	public byte 	   	   m_u8TranscodeModule;		/* transcode module id */
	public byte 	   	   m_u8SrcCodec;				/* source codec type */
	public short 	       decoderConfigLength;
    public byte 	       decoderConfigInfo[] = new byte[128];
    public byte 	       m_u8DstCodec;				/* destination codec type */
    public byte 	       m_u8Fps;						/* destination framerate in fps */
    public short 	       m_u16Kbps;					/* destination bitrate in Kbps */ 
	public short 	       m_u16ResX;					/* destination resolution x */
    public short 	       m_u16ResY;					/* destination resolution y */
	public byte 	       s8OverlayImage[]    = new byte[200];
}/*Acs_Video_Link_Param*/

class Acs_3G324M_H223CAP
{
	public byte 	  	   videoWithAL1;
	public byte 	  	   videoWithAL2;
	public byte 	  	   videoWithAL3;
	public byte 	  	   audioWithAL1;
	public byte 	  	   audioWithAL2;
	public byte 	  	   audioWithAL3;
	public short 	   	   maximumAl2SDUSize;
	public short 	   	   maximumAl3SDUSize;
	public short 	   	   maximumDelayJitter;
	public byte 	  	   maxMUXPDUSizeCapability;
	public byte 	  	   nsrpSupport;
	public byte 	  	   modeChangeCapability;
	public byte 	       h223AnnexA;
	public byte 	  	   h223AnnexADoubleFlag;
	public byte 	       h223AnnexB;
	public byte 	       h223AnnexBwithHeader;
	public byte 	  	   reserved;
}

class Acs_3G324M_CAP_AMR
{
	public byte 	 	   maxBitRate;
	public byte 	 	   maxFramesPerSdu;
	public byte 	 	   reserved[] = new byte[2];
} 

class Acs_3G324M_CAP_G723
{
	public byte 	  	   maxFramesPerSdu;
	public byte 	  	   silenceSuppression;
	public byte 	  	   reserved[] = new byte[2];
}

class Acs_3G324M_CAP_H263
{
	public byte 	  	   sqcifMPI;
	public byte 	  	   qcifMPI;
	public byte 	  	   cifMPI;
	public byte 	  	   cif4MPI;
	public byte 	  	   cif16MPI;
	public byte 	  	   reserved1;
	public short 	  	   maxBitRate;
	public byte 	  	   unrestrictedVector;
	public byte 	  	   arithmeticCoding;
	public byte 	  	   advancedPrediction;
	public byte 	  	   pbFrames;
	public byte 	  	   temporalSpatialTradeOffCapability;
	public byte 	  	   errorCompensation;
	public byte 	  	   reserved2[] = new byte[2];
}

class Acs_3G324M_CAP_MP4
{
	public short 	   	   maxBitRate;
	public byte 	   	   profileAndLevel;
	public byte 	   	   object;
	public byte 	       reserved[] 		   = new byte[3];
	public byte 	       decoderConfigLength;
	public byte 	       decoderConfigInfo[] = new byte[128];
}

class Acs_3G324M_CAP
{
	public Acs_3G324M_CAP_AMR  AmrAudioCapability	 = new Acs_3G324M_CAP_AMR();
	public Acs_3G324M_CAP_G723 G7231AudioCapability	 = new Acs_3G324M_CAP_G723();
	public Acs_3G324M_CAP_H263 H263VideoCapability	 = new Acs_3G324M_CAP_H263();
	public Acs_3G324M_CAP_MP4  Mpeg4VideoCapability  = new Acs_3G324M_CAP_MP4();
}

class Acs_3G324M_CAPENTRY
{
	public short 	 		   entryNumber;
	public byte 	 		   capType;							/* reference to XMS_VOIP_MEDIA_CAPS */
	public byte  			   direction;						/* reference to XMS_CAP_DIRECTION */
	public Acs_3G324M_CAP 	   capability	= new Acs_3G324M_CAP();
}

class Acs_3G324M_CAPTABLE
{
	public short 	 		   capabilityNum;
	public short 	 		   reserved;
	public Acs_3G324M_CAPENTRY CapabilityTableEntry[] = new Acs_3G324M_CAPENTRY[4];
	
	public Acs_3G324M_CAPTABLE(){
		for (int i = 0; i < 4; i++){
			CapabilityTableEntry[i] = new Acs_3G324M_CAPENTRY();
		}
	}
} 

class Acs_3G324M_TCS
{
	public Acs_3G324M_H223CAP  h223Capability = new Acs_3G324M_H223CAP(); 
	public Acs_3G324M_CAPTABLE capabilityTable = new Acs_3G324M_CAPTABLE();
}

/* Acs VoIP SIP INFO struct */
class Acs_VoIP_SIPINFO
{
	public byte 	 		   m_s8ContentType[] = new byte[50];	/* content type string (mime)*/
	public byte 	 		   m_s8Body[] = new byte[800];			/* info message body string*/
}/*Acs_VoIP_SIPINFO*/

/* Acs VoIP SIP Register/Unregister struct */
class Acs_VoIP_SIPREG
{
	public byte 	 		   m_s8TelNo[]    = new byte[20];	    /* subscriber number */
	public byte 	 		   m_s8Username[] = new byte[20];	/* username for authorization */
	public byte 	 		   m_s8Password[] = new byte[20];	/* paswword for authorization */
}/*Acs_VoIP_SIPREG*/


/* Acs VoIP RTP DTMF struct */
class Acs_VoIP_RTPDTMF
{
	public byte 	 		   m_s8EventChar;			/* dtmf event char */
	public byte 	 		   m_s8Volume;				/* volume (in dbm0 from -63 to 0) */
	public short 	 		   m_u16Duration;			/* duration (in timestamp units) */
}/*Acs_VoIP_RTPDTMF*/

/* Acs VoIP RTP TONE struct */
class Acs_VoIP_RTPTONE
{
	public short 	 			m_u16Modulation;		/* modulation */
	public byte 	 			m_u8TriFlag;			/* tri-frequency flag */
	public byte 	 			m_s8Volume;				/* volume */
	public short 	 			m_u16Duration;			/* duration */
	public byte 	 			m_u8FrequencyNum;		/* number of frequencies */
	public short 	 			m_u16Frequency[] = new short[10];		/* frequencies to mix the tone */
}/*Acs_VoIP_RTPTONE*/

/* Acs VoIP Mixer struct*/
class Acs_VoIP_Mixer
{
	public byte 	 			m_u8SRC1_Ctrl;  /*reference XMS_MIXER_TYPE*/
	public byte 	 			m_u8SRC2_Ctrl;  /*reference XMS_MIXER_TYPE*/
	public short 	 			m_u16SRC_ChID1; /*Media ChID1*/
	public short 	 			m_u16SRC_ChID2; /*Media ChID2*/
	public byte 	 		    m_s8Video;      /*Video Channel*/
	public byte 	 		    m_s8Rfu;        /*Rfu*/
}/*Acs_VoIP_Mixer*/

class CmdParamData_AnalogTrunkFlash_t
{
	public byte 	 			m_u8Channel_Enable;
	public byte 	 			m_u8Type;
	public byte 	 			m_u8Tx_State;
	public byte 	 			m_u8Rx_State;
}/*CmdParamData_AnalogTrunkFlash_t*/

/*DTMF control param*/
class CmdDtmfParamData_Voice_t
{
	public int                  m_u32MaxValidIntervalTime;  /* max interval time: ms*/
	public byte                 m_u8MaxCodeNums;            /* max DTMF nums : 0 ~ 255*/
	public byte                 m_u8Rfu1[] = new byte[3];                /*Rfu*/
	public byte                 m_u8DTMF[] = new byte[32];               /*DTMF buffer*/
}/*CmdDtmfParamData_Voice_t*/

/* Struct of AddFaxFile */
class CmdParamData_AddFax_t 
{
	public byte       			m_s8FaxFileName[] = new byte[128]; /* FaxFileName ,Usual As Tiff Format */
}/*CmdParamData_AddFax_t*/

/* Struct of StartSendFax */
class CmdParamData_StartSendFax_t
{
	public DeviceID_t 			m_VocDev 	  = new DeviceID_t();
	public byte       	        m_s8LocalID[] = new byte[20];
}/*CmdParamData_StartSendFax_t*/

/*CmdParamData_3GPP_t*/
class CmdParamData_3GPP_t
{	
	public byte          		m_u8AudioDecodeType;  /*audio decode type*/
	public byte                 m_u8AudioFrameType;   /*audio frame type,reference XMS_AUDIO_AMR_FRAME_TYPE*/
	public short      			m_u16AudioDecoderCfgLen;/*audio decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
    public byte      			m_u8AudioDecoderCfg[] = new byte[200];/*audio decoder cfg*/
    public byte                 m_u8AudioProfiles;    /*audio profiles?*/
    public byte                 m_u8AudioLevel;		  /*audio level ?*/
    public byte                 m_Rfu1[] = new byte[2];

    public byte                 m_u8VideoDecodeType;      /*video decode type*/
    public byte                 m_u8VideoFrameRate;       /*video frame rate 10 ~ 30*/
    public short                m_u16VideoDecoderCfgLen;  /*video decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
	public byte                 m_u8VideoDecoderCfg[] = new byte[200];/*video decoder cfg?*/
	public byte                 m_u8VideoProfiles;        /*video profiles?*/
	public byte                 m_u8VideoLevel;           /*video level?*/
	public byte                 m_Rfu2[] = new byte[2];
}/*CmdParamData_3GPP_t*/

/*DigRecSwitchMode*/
class DigRecSwitchMode
{
	public byte                 m_u8Enable;               /*the switch of the function, 0: disable; 1: enable*/
	public byte                 m_u8SwitchMode;           /*the digital switch type,referece to XMS_DRS_SWITCH_TYPE*/
	public byte                 m_u8EncodeType;           /*audio's encode type, referece to the A-Law or Mu-law of XMS_VOC_CODE_TYPE, and any other type is not supported by keygoe*/
	public byte                 m_u8IsRecordSigData;      /*the switch to wheather record the signal data from DSP, 0: disable; 1: enable*/
	public byte                 m_Rfu1[] = new byte[4];                /*reserve*/
}/*DigRecSwitchMode*/

/*CmdParamdata Body*/
/*typedef struct
{
	union
	{
		CmdParamData_Voice_t		m_cmdParamDataVoice; 		
		CmdParamData_Conf_t		    m_CmdParamDataConf; 
	};
}CmdParamData_t;*/

class CmdParamData_t
{
	public CmdParamData_Voice_t		m_cmdParamDataVoice = new CmdParamData_Voice_t();     /**/		
	public CmdParamData_Conf_t		m_CmdParamDataConf  = new CmdParamData_Conf_t();      /**/
}

/*Acs_OpenDev_Evt*/
class Acs_GeneralProc_Evt
{
	public ACS_EVT_HEAD             m_AcsEvtHead 	  = new ACS_EVT_HEAD();     /*acs event head*/
	public Acs_GeneralProc_Data     m_AcsGenLProcData = new Acs_GeneralProc_Data(); /*acs general proc event data*/
}/**/


/*OpenStreamExt evt data*/
class Acs_OpenStreamExt_Data
{
	public ServerID_t        		m_ServerID	= new ServerID_t();
	public int   					m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
	public byte             		m_s8Rfu1[] = new byte[12];
}/**/

/*Acs_OpenStreamExt_Evt*/
class Acs_OpenStreamExt_Evt
{
	public ACS_EVT_HEAD             m_AcsEvtHead 			= new ACS_EVT_HEAD();           /*acs event head*/
	public Acs_OpenStreamExt_Data   m_AcsOpenStreamExtData	= new Acs_OpenStreamExt_Data(); /*acs general proc event data*/
}/**/

/*Acs_CloseStreamExt_Data*/
class Acs_CloseStreamExt_Data
{
	public ServerID_t      			m_ServerID	= new ServerID_t();
	public byte			            m_s8Rfu1[]  = new byte[16];
}/**/

/*Acs_CloseStreamExt_Evt*/
class Acs_CloseStreamExt_Evt
{
	public ACS_EVT_HEAD             m_AcsEvtHead = new ACS_EVT_HEAD();            /*acs event head*/
	public Acs_CloseStreamExt_Data  m_AcsCloseStreamExtData = new Acs_CloseStreamExt_Data(); /*acs general proc event data*/
}/**/

/*ACS master state*/
class Acs_MasterState_Data
{
	public byte      				m_s8ServerIp[] = new byte[32]; /*XMS server ip*/
	public int     					m_u32ServerPort;  /*XMS server port*/
	public byte      				m_u8MasterState; /*Acs server master state,reference ACS_MASTER_STATE*/
	public byte      				m_Rfu1[] = new byte[3];
}

/*Acs_MasterState_Evt*/
class Acs_MasterState_Evt
{
	public ACS_EVT_HEAD             m_AcsEvtHead 		= new ACS_EVT_HEAD();     /*acs event head*/
	public Acs_MasterState_Data     m_AcsMasterState	= new Acs_MasterState_Data(); /*acs master state*/
}/**/

/*ACS Slave Work state*/
class Acs_SlaveWorkState_Data
{
	public byte      	      		m_s8WorkState; /*Slave machine work state: 0: conk out, 1: working, reference to ACS_WORK_STATE*/
	public byte      	          	m_Rfu1[] = new byte[31];    /*reserve*/
}

/*Acs_SlaveWork_Evt*/
class Acs_SlaveWorkState_Evt
{
	public ACS_EVT_HEAD             m_AcsEvtHead = new ACS_EVT_HEAD();        /*acs event head*/
	public Acs_SlaveWorkState_Data  m_AcsSlaveWorkState = new Acs_SlaveWorkState_Data(); /*acs slave work state*/
}/**/


/*Acs_BakSysStartEvt*/
class Acs_BakSysStartEvt
{
	public ACS_EVT_HEAD   			m_AcsEvtHead = new ACS_EVT_HEAD();  /*acs event head*/
	public int         				m_Rfu1;
}/**/


class Acs_ParamProc_Data
{
	public int         				m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
	public int         		        m_s32AcsEvtErrCode;  /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	public short         		    m_u16ParamCmdType;  /*acs param Cmd Type*/
	public short         		    m_u16ParamDataSize; /*acs param Data Size*/
}/**/

class Acs_ParamData_Evt
{
	public ACS_EVT_HEAD             m_AcsEvtHead     = new ACS_EVT_HEAD();     /*acs event head*/
	public Acs_ParamProc_Data       m_ParamProcData  = new Acs_ParamProc_Data();
}/**/

class Acs_ParamData_UserReadXmsBoardInfo
{
	public byte						m_u8MacAddr[]		= new byte[6];	   /* Mac address */
	public byte						m_u8ChassisType;   /* chassis type��0: ITP1200; 1:3U chassis; 2:5U chassis; 3: 11U chassis */
	public byte						m_u8ChassisIndex;  /* chassis  No */
	public byte						m_u8ChassisSlot;   /* chassis slot number */
	public byte						m_u8SubBoardIndex; /* module index inside one board*/
	public byte						m_u8BoardType;	   /* Board type��0:itp1200;1:itp2400; 2: itp4800*/
	public byte						rfu1;
	public byte						m_s8SystemName[]	= new byte[32];/* System name */	
	public byte						m_s8PlatformType;  /* Platform: 1:callback; 2:keygoe 1000; 3:keygoe 3000; 4:keygoe 8000*/
	public byte						m_s8UserCode[]		= new byte[7];   /* User code */
	public int						m_s32SysId;        /* sys id*/
	public byte						rfu2[]				= new byte[20];
	public byte						m_s8FirmwareName[]	= new byte[8];	/* DSP firmwarename */
	public byte						m_s8FirmwareVersion[] = new byte[8];	/* DSP firmware version*/
	public byte						m_s8RevisionDate[]	= new byte[8];	/* DSP firmware date*/
}

/*Acs_BoardPrivateExt_Data*/
class Acs_BoardPrivateExt_Data
{
	public int					 	m_u32ExtType;        //reference to XMS_BOARD_PRIVATE_EXT_TYPE
	public byte						m_uClockTypeOrMode;
	public byte						m_u8SysClockType;
	public byte						m_u8Ref[] = new byte[2];
}/*Acs_BoardPrivateExt_Data*/

/*Acs_BoardRstState_Data*/
class Acs_BoardRstState_Data
{
	public byte						m_u8Ref[] = new byte[16];
}/*Acs_BoardRstState_Data*/

/* CAS Extra Infomation, used by XMS_EVT_CAS_MFC_END*/
class Acs_CAS_ExtraInfo_t
{
	/* Call In Infomation */
	public byte					    m_u8KA; /* Caller's KA */
	public byte					    m_u8KD; /* Caller's KD */
	/* Call Out Infomation */

	/* Other */
	public byte	                    m_u8Rfu[] = new byte[14];/* Reserved for Future Use */
}/*Acs_CAS_ExtraInfo_t*/

/*Acs_CallControl_Evt*/
class Acs_CAS_MFC_Evt
{
	public ACS_EVT_HEAD             m_AcsEvtHead	   = new ACS_EVT_HEAD();     /*acs event head*/
	public Acs_CAS_ExtraInfo_t      m_AcsCASExtraInfo  = new Acs_CAS_ExtraInfo_t(); /*acs CAS ExtraInfo event data*/
}/**/

/*Acs_CallControl_Evt*/
class Acs_CallControl_Evt
{
	public ACS_EVT_HEAD             m_AcsEvtHead = new ACS_EVT_HEAD();     /*acs event head*/
	public Acs_CallControl_Data     m_AcsCallControl = new Acs_CallControl_Data(); /*acs call control event data*/
}/**/

/*Acs_LinkDev_Data*/
class Acs_LinkDev_Data
{
	public int          			m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
	public int        				m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	public DeviceID_t               m_SrcDevice   = new DeviceID_t();
	public DeviceID_t               m_DestDevice  = new DeviceID_t();
}/*Acs_LinkDev_Data*/

/*Acs_LinkDev_Evt*/
class Acs_LinkDev_Evt
{
	public ACS_EVT_HEAD             m_AcsEvtHead = new ACS_EVT_HEAD();     /*acs event head*/
	public Acs_LinkDev_Data         m_AcsLinkDev = new Acs_LinkDev_Data();     /*acs Link Device event data*/
}/*Acs_LinkDev_Evt*/

/*Acs_CtxReg_Data*/
class Acs_CtxReg_Data
{
	public int         				m_s32AcsEvtState;   /*acs event state, 1: success; -1: failed*/
	public int       				m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
}/**/

/*Acs_CtxReg_Evt*/
class Acs_CtxReg_Evt
{
	public ACS_EVT_HEAD             m_AcsEvtHead = new ACS_EVT_HEAD();     /*acs event head*/
	public Acs_CtxReg_Data          m_AcsCtxReg	 = new Acs_CtxReg_Data();      /*acs ctxReg evt*/
}/**/

/*Acs_CtxLink_Data*/
class Acs_CtxLink_Data
{
	public int         				m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
	public int       				m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
}/**/

/*Acs_CtxLink_Evt*/
class Acs_CtxLink_Evt
{
	public ACS_EVT_HEAD             m_AcsEvtHead = new ACS_EVT_HEAD();     /*acs event head*/
	public Acs_CtxLink_Data         m_AcsCtxLink = new Acs_CtxLink_Data();
}/**/

/*CTX App Data Info*/
class CTX_AppData_Info
{
	public int         		        m_u32AppDataSize; /*user APP data size,not include XMS_AppData_Info_t*/
	public byte         		    m_u8AppReqType;   /*user APP req cmd type,user self define*/
	public byte         	       	m_u8AcsUnitID;
	public byte         	       	m_Rfu1[] 		  = new byte[2];      
	public byte         	        m_s8SrcRegName[]  = new byte[16]; /*src reg name*/
	public byte         	        m_s8DestRegName[] = new byte[16];/*dest reg name*/
	public byte         	        m_u8SrcAppUnitID;
	public byte         	        m_u8DstAppUnitID;
	public byte         	        m_Rfu2[] 		  = new byte[2];
	public DeviceID_t  				m_srcDevice 	  = new DeviceID_t();
	public byte         	        m_Rfu3[] 		  = new byte[20];
	public int         	      		m_s32Rst;
}/**/

/*Acs_CtxAppData_Info*/
class Acs_CtxAppData_Info
{
	public int         				m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
	public int       				m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	public CTX_AppData_Info         m_AppDataInfo = new CTX_AppData_Info();
}/**/

/*Acs_CtxAppData_Evt*/
class Acs_CtxAppData_Evt
{
	public ACS_EVT_HEAD             m_AcsEvtHead	 = new ACS_EVT_HEAD();     /*acs event head*/
	public Acs_CtxAppData_Info      m_AcsCtxAppData	 = new Acs_CtxAppData_Info();
}/**/

/*Acs_CtxState_Info*/
class Acs_CtxState_Info
{
	public int       		        m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
	public int       		        m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	public int       		        m_u32CtxState;
	public byte       		        m_s8SrcRegName[]  = new byte[16];
	public byte       		        m_s8DestRegName[] = new byte[16];
}/**/

/*Acs_Ctx_State_Evt*/
class Acs_Ctx_State_Evt
{
	public ACS_EVT_HEAD             m_AcsEvtHead  = new ACS_EVT_HEAD();     /*acs event head*/
	public Acs_CtxState_Info        m_AcsCtxState = new Acs_CtxState_Info();
}/**/

/*Acs_SigMon_Data*/
class Acs_SigMon_Data
{
	public SMON_EVENT           	m_SigMon    = new SMON_EVENT();            /*sig monitor data*/
	public PrivateData_t        	m_PrivData  = new PrivateData_t();          /*private data*/
}/*Acs_SigMon_Data*/

/*Acs_SigMon_Evt*/
class Acs_SigMon_Evt
{
	public ACS_EVT_HEAD             m_AcsEvtHead = new ACS_EVT_HEAD();     /*acs event head*/
	public Acs_SigMon_Data          m_AcsSigMon  = new Acs_SigMon_Data();      /*acs call control event data*/
}/**/

/*Acs_3G324_Data*/
class	Acs_3G324_Data
{
	public byte						m_u8DataType;		    /*3G324 event data type*/
	public byte						Rfu1;				    /*reserved*/
	public short					m_u16DataLen;	        /*3G324 event data size*/	
}/*Acs_3G324_Data*/

/*Acs_3G324_Evt*/
class Acs_3G324_Evt
{
	public ACS_EVT_HEAD				m_AcsEvtHead = new ACS_EVT_HEAD();  /*acs event head*/	
	public Acs_3G324_Data			m_Acs324Data = new Acs_3G324_Data();  /*acs 3G324 event*/
}/**/

/*Acs_3G324_Stop_Evt*/
class	Acs_3G324_Stop_Evt
{
	public byte	m_u8StopCode;			/*3G324 session stop code*/
	public byte	m_u8Rfu[] = new byte[3];				/*reserved*/	
}/**/

/*Acs_AnalogInterface_Data*/
class Acs_AnalogInterface_Data
{
	public int         				m_s32AcsEvtState;   /*acs event state, 1: success; 0: failed*/
	public int       				m_s32AcsEvtErrCode; /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	public byte                   	m_u8AnalogInterfaceState;/*Analog Interface State,reference XMS_ANALOG_INTERFACE_STATE*/
	public byte                   	m_Rfu1[] = new byte[3];
	public PrivateData_t           	m_PrivData;          /*private data*/
}/**/

/*Acs_AnalogInterface_Evt*/
class Acs_AnalogInterface_Evt
{
	public ACS_EVT_HEAD                  m_AcsEvtHead = new ACS_EVT_HEAD();     /*acs event head*/
	public Acs_AnalogInterface_Data      m_AcsAnalogInterfaceData = new Acs_AnalogInterface_Data(); /*acs Analog Interface event data*/
}/**/

/*Acs_SendSigMsg_Data*/
class Acs_SendSigMsg_Data
{
	public int         			  m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
	public int       			  m_s32AcsEvtErrCode;  /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	public short                  m_s16SignalMsgType;  /*acs signal msg type*/
	public byte                   m_s8Rfu[] = new byte[2];          /*Rfu*/
}/**/

/*Acs_SendSigMsg_Evt*/
class Acs_SendSigMsg_Evt
{
	public ACS_EVT_HEAD           m_AcsEvtHead	  = new ACS_EVT_HEAD();     /*acs event head*/
	public Acs_SendSigMsg_Data    m_AcsSendSigMsg = new Acs_SendSigMsg_Data();  /*acs send signal msg event data*/
}/**/

/*Acs_ConfControl_Data*/
class Acs_ConfControl_Data
{
	public int         	          m_s32AcsEvtState;    /*acs event state, 1: success; 0: failed*/
	public int         	          m_s32AcsEvtErrCode;  /*acs event errcode,reference XMS_ERROR_CODE_DEF*/
	public int         	          m_s32ConfMembers;    /*Obsolete, replaced by m_u8TotalOfConfMem of CmdParamConf_MemberState_t*/		
	public DeviceID_t             m_MediaDevice = new DeviceID_t();
	public PrivateData_t          m_PrivData    = new PrivateData_t();/*private data*/
}/**/

/*Acs_ConfControl_Evt*/
class Acs_ConfControl_Evt
{
	public ACS_EVT_HEAD           m_AcsEvtHead	   = new ACS_EVT_HEAD();      /*acs event head*/
	public Acs_ConfControl_Data   m_AcsConfControl = new Acs_ConfControl_Data();  /*acs call control event data*/
}/**/

/*Acs_MediaProc_Evt*/
class Acs_MediaProc_Evt
{
	public ACS_EVT_HEAD           m_AcsEvtHead	   = new ACS_EVT_HEAD();    /*acs event head*/
	public Acs_MediaProc_Data     m_AcsMediaProc   = new Acs_MediaProc_Data();  /*acs media proc event data*/
}/**/

/*Acs_CSPDataReq_Data*/
class Acs_CSPDataReq_Data
{
	public short				  m_u16ReqCspDataLen; /*DSP request data length*/
	public byte					  m_u8TaskID;	        /*Task ID*/
	public byte					  m_u8DataType;	    /*Data Type: reference XMS_CSPPLAY_DATA_TYPE*/
}/*Acs_CSPDataReq_Data*/

/*Acs_CSPDataReq_Evt*/
class Acs_CSPDataReq_Evt
{
	public ACS_EVT_HEAD           m_AcsEvtHead			= new ACS_EVT_HEAD();         /*acs event head*/
	public Acs_CSPDataReq_Data    m_AcsCSPDataReqProc	= new Acs_CSPDataReq_Data();  /*acs media CSP play request data*/
}/**/

/*Acs_MediaCSPProc_Data*/
class Acs_MediaCSPProc_Data
{
	public short				  m_u16DataLen;	        /*stream data size*/
	public byte					  m_u8DataType;		    /*stream data type*/
	public byte					  m_u8TagNumber;			/*Rfu*/
	public byte			  		  m_u8StreamData[] = new byte[4000];	/*stream data*/
}

/*Acs_MediaCSPProc_Evt*/
class Acs_MediaCSPProc_Evt
{
	public ACS_EVT_HEAD           m_AcsEvtHead		= new ACS_EVT_HEAD();       /*acs event head*/
	public Acs_MediaCSPProc_Data  m_AcsMediaCSPProc	= new Acs_MediaCSPProc_Data();  /*acs media CSP proc event data*/
}/**/

/*Acs_Media3GPPProc_Data*/
class Acs_Media3GPPProc_Data
{
	public int         			  m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	public int               	  m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	public byte                   m_u8AudioTaskID;          /*audio:  play Task ID*/
	public byte                   m_u8MediaType;            /*common: media type XMS_MEDIA_TYPE*/
	public byte                   m_u8VideoTaskID;          /*video:  play Task ID*/
	public byte                   m_s8Rfu;
	public int                    m_u32AudioCurFileIndex;   /*audio:current play index*/
	public int                    m_u32AudioCurFilePos;     /*audio:current play pos*/
	public int                    m_u32VideoCurFileIndex;   /*video:current play index*/
	public int                    m_u32VideoCurFilePos;     /*video:current play pos*/
	public PrivateData_t          m_PrivData = new PrivateData_t();/*private data*/
}/**/

/*Acs_Media3GPPProc_Evt*/
class Acs_Media3GPPProc_Evt
{
	public ACS_EVT_HEAD           m_AcsEvtHead = new ACS_EVT_HEAD();    /*acs event head*/
	public Acs_Media3GPPProc_Data m_AcsMedia3GPPProc = new Acs_Media3GPPProc_Data();  /*acs media proc event data*/
}/**/

/*Acs_JoinTo3GVConf_Data*/
class Acs_JoinTo3GVConf_Data
{
	public int             		 m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	public int           		 m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	public DeviceID_t            m_3GVConfDev = new DeviceID_t();
	public DeviceID_t            m_srcDev	  = new DeviceID_t();
	public PrivateData_t         m_PrivData	  = new PrivateData_t();/*private data*/
}/**/

/*Acs_JoinTo3GVConf_Evt*/
class Acs_JoinTo3GVConf_Evt
{
	public ACS_EVT_HEAD              m_AcsEvtHead = new ACS_EVT_HEAD();    /*acs event head*/
	public Acs_JoinTo3GVConf_Data    m_AcsJoinTo3GVConf = new Acs_JoinTo3GVConf_Data();  /*acs Join to 3GVConf event data*/
}/**/

/*Acs_LeaveFrom3GVConf_Data*/
class Acs_LeaveFrom3GVConf_Data
{
	public int                     m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	public int                     m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	public DeviceID_t              m_3GVConfDev = new DeviceID_t();
	public DeviceID_t              m_srcDev 	= new DeviceID_t();
	public PrivateData_t           m_PrivData	= new PrivateData_t();/*private data*/
}/**/

/*Acs_LeaveFrom3GVConf_Evt*/
class Acs_LeaveFrom3GVConf_Evt
{
	public ACS_EVT_HEAD              m_AcsEvtHead = new ACS_EVT_HEAD();    /*acs event head*/
	public Acs_LeaveFrom3GVConf_Data m_AcsLeaveFrom3GVConf = new Acs_LeaveFrom3GVConf_Data();  /*acs leave from 3GVConf event data*/
}/**/

/*Acs_Clear3GVConf_Data*/
class Acs_Clear3GVConf_Data
{
	public int                     m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	public int                     m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	public DeviceID_t              m_3GVConfDev = new DeviceID_t();
	public PrivateData_t           m_PrivData	= new PrivateData_t();/*private data*/
}/**/

/*Acs_Clear3GVConf_Evt*/
class Acs_Clear3GVConf_Evt
{
	public ACS_EVT_HEAD            m_AcsEvtHead = new ACS_EVT_HEAD();    /*acs event head*/
	public Acs_Clear3GVConf_Data   m_AcsClear3GVConf = new Acs_Clear3GVConf_Data();  /*acs clear 3GVConf event data*/
}/**/

/*Acs_GetLayout_Data*/
class Acs_GetLayout_Data
{
	public int                     m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	public int                 	   m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	public DeviceID_t              m_3GVConfDev = new DeviceID_t();
	public Acs_3GVConf_LayoutList  m_list		= new Acs_3GVConf_LayoutList();
	public PrivateData_t           m_PrivData	= new PrivateData_t();/*private data*/
}/**/

/*Acs_GetLayout_Evt*/
class Acs_GetLayout_Evt
{
	public ACS_EVT_HEAD              m_AcsEvtHead = new ACS_EVT_HEAD();    /*acs event head*/
	public Acs_GetLayout_Data        m_AcsGetLayout = new Acs_GetLayout_Data();  /*acs Get Layout event data*/
}/**/

/*Acs_SetLayout_Data*/
class Acs_SetLayout_Data
{
	public int                     m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	public int                     m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	public DeviceID_t              m_3GVConfDev = new DeviceID_t();
	public PrivateData_t           m_PrivData = new PrivateData_t();/*private data*/
}/**/

/*Acs_SetLayout_Evt*/
class Acs_SetLayout_Evt
{
	public ACS_EVT_HEAD            m_AcsEvtHead = new ACS_EVT_HEAD();    /*acs event head*/
	public Acs_SetLayout_Data      m_AcsSetLayout = new Acs_SetLayout_Data();  /*acs Set Layout event data*/
}/**/

/*Acs_GetVisibleList_Data*/
class Acs_GetVisibleList_Data
{
	public int                     m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	public int                     m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	public DeviceID_t              m_3GVConfDev = new DeviceID_t();
	public Acs_3GVConf_VisibleList m_list 		= new Acs_3GVConf_VisibleList();
	public PrivateData_t           m_PrivData 	= new PrivateData_t();/*private data*/
}/**/

/*Acs_GetVisibleList_Evt*/
class Acs_GetVisibleList_Evt
{
	public ACS_EVT_HEAD              m_AcsEvtHead = new ACS_EVT_HEAD();    /*acs event head*/
	public Acs_GetVisibleList_Data   m_AcsGetVisibleList = new Acs_GetVisibleList_Data();  /*acs Get Visible List event data*/
}/**/

/*Acs_SetVisibleList_Data*/
class Acs_SetVisibleList_Data
{
	public int                     m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	public int                     m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	public DeviceID_t              m_3GVConfDev = new DeviceID_t();
	public PrivateData_t           m_PrivData = new PrivateData_t();/*private data*/
}/**/

/*Acs_SetVisibleList_Evt*/
class Acs_SetVisibleList_Evt
{
	public ACS_EVT_HEAD              m_AcsEvtHead = new ACS_EVT_HEAD();    /*acs event head*/
	public Acs_SetVisibleList_Data   m_AcsSetVisibleList = new Acs_SetVisibleList_Data();  /*acs Set Visible List event data*/
}/**/

/*Acs_3GVConfStop_Data*/
class Acs_3GVConfStop_Data
{
	public int                       m_s32AcsEvtState;         /*common: acs event state, 1: success; 0: failed*/
	public int                       m_s32AcsEvtErrCode;       /*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/	
	public DeviceID_t                m_3GVConfDev = new DeviceID_t();
	public PrivateData_t             m_PrivData = new PrivateData_t();/*private data*/
}/**/

/*Acs_3GVConfStop_Evt*/
class Acs_3GVConfStop_Evt
{
	public ACS_EVT_HEAD           m_AcsEvtHead = new ACS_EVT_HEAD();    /*acs event head*/
	public Acs_3GVConfStop_Data   m_Acs3GVConfStop = new Acs_3GVConfStop_Data();  /*acs 3G VConf Stop event data*/
}/**/

/*Acs_IO_Evt*/
class Acs_IO_Evt
{
	public ACS_EVT_HEAD          m_AcsEvtHead = new ACS_EVT_HEAD(); /*acs event head*/	
	public Acs_IO_Data           m_AcsIOData = new Acs_IO_Data();  /*acs io event*/
}/**/

/*Acs License Query event*/
class Acs_LicenseQuery_Data
{
	public byte     			 m_u8ModuleID;          /*license alarm Board module ID*/
	public short    			 m_u16LicLeftDay;        /*license alarm Board left license days,0: No license or license overdue;100:license forever; else: left license days*/
	public byte     			 m_Rfu1;
}/**/

/*Acs_LicenseAlarm_Evt*/
class Acs_LicenseQuery_Evt
{
	public ACS_EVT_HEAD              m_AcsEvtHead = new ACS_EVT_HEAD();       /*acs event head*/
	public Acs_LicenseQuery_Data     m_LicenseQueryData = new Acs_LicenseQuery_Data(); /*universal failure confirmation event*/	
}/**/

/*Acs_UniFailure_Evt*/
class Acs_UniFailure_Evt
{
	public ACS_EVT_HEAD              m_AcsEvtHead = new ACS_EVT_HEAD();     /*acs event head*/
	public Acs_UniFailure_Data       m_UniverFailData = new Acs_UniFailure_Data(); /*universal failure confirmation event*/	
}/**/

/*Acs_FaxEnd_Data*/
class Acs_FaxProc_Data
{
	public int      		   m_s32AcsEvtState;   /*acs event state*/
	public int      		   m_s32AcsEvtErrCode; /*acs event errcode*/	
	public byte     		   m_u8ErrorStep;      /*error state of last fax operation*/
	public byte                m_u8T30SendState;   /*the state the T30 command just sent*/
	public byte                m_u8RecvT30Cmd;     /*the T30 command just received*/
	public byte                m_u8Rfu1;            /*Reserved*/ 
	public short               m_u16TotalPages;    /*total pages,send: sending total pages successfully  ;rev: receiving total pages successfully*/
	public byte                m_s8RemoteID[] = new byte[20];/*Remote ID*/	
	public byte                m_u8Rfu2[] = new byte[2];           /*Reserved*/
	public PrivateData_t       m_PrivData = new PrivateData_t();/*private data*/
}/**/

/*Acs_FaxProc_Evt*/
class Acs_FaxProc_Evt
{
	public ACS_EVT_HEAD        m_AcsEvtHead = new ACS_EVT_HEAD();     /*acs event head*/	
	public Acs_FaxProc_Data    m_AcsFaxProcData = new Acs_FaxProc_Data(); /*acs fax proc data*/
}/**/

/*ITP_3GPP_PARAM_CFG*/
class ITP_3GPP_PARAM_CFG
{
	public byte      	      m_u8AudioDecodeType;      /*audio decode type*/
	public byte               m_u8AudioFrameType;       /*audio frame type,reference XMS_AUDIO_AMR_FRAME_TYPE*/
	public short    	      m_u16AudioDecoderCfgLen;  /*audio decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
    public byte               m_u8AudioDecoderCfg[] = new byte[200];/*audio decoder cfg*/
    public byte               m_u8AudioProfiles;        /*audio profiles?*/
    public byte               m_u8AudioLevel;		  /*audio level ?*/
    public byte               m_Rfu1[] = new byte[2];

    public byte               m_u8VideoDecodeType;      /*video decode type*/
    public byte               m_u8VideoFrameRate;       /*video frame rate 10 ~ 30*/
    public short          	  m_u16VideoDecoderCfgLen;  /*video decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
    public byte               m_u8VideoDecoderCfg[] = new byte[200];/*video decoder cfg?*/
    public byte               m_u8VideoProfiles;        /*video profiles?*/
    public byte               m_u8VideoLevel;           /*video level?*/
    public byte               m_Rfu2[] = new byte[2];  

    public int                m_u32TrackNums;           /*track numbers*/
    public short          	  m_u16AudioMaxBitRate;
    public short          	  m_u16AudioAverageBitRate;
    public int                m_u32AudioBitMask;
    public short          	  m_u16VideoMaxBitRate;
    public short          	  m_u16VideoAverageBitRate;
    public int          	  m_u32VideoBitMask;
    public short              m_u16VideoWidth;
    public short              m_u16VideoHeight;
}/*ITP_3GPP_PARAM_CFG*/

/*CmdParamData_324CH_t*/
class CmdParamData_324CH_t {
	public byte       		m_u8Channel_Enable;		/* channel enable flag, 1 - enable, 0 - disable*/
	public byte       		m_u8AudioSRC1_Ctrl;		/* audio channel source 1 type */
	public byte       		m_u8AudioSRC2_Ctrl;		/* audio channel source 2 type */
	public byte       		m_u8VideoSRC1_Ctrl;		/* video channel source type */
	public short			m_u16AudioSRC1_ID;		/* audio channel source 1 id */
	public short			m_u16AudioSRC2_ID;		/* audio channel source 2 id */
	public short			m_u16VideoSRC1_ID;		/* video channel source id */
	public byte       	 	m_u8AudioInDecodeFlag;	/* 1 - input decode, 0 - no decode */
	public byte       	 	m_u8AudioOutEncodeFlag; /* 1 - output encode, 0 - no encode */
	public byte       	 	m_u8AudioInCodec;		/* audio input codec */
	public byte       		m_u8AudioOutCodec;		/* audio output codec */
	public byte       		m_u8VideoInCodec;		/* video input codec */
	public byte       		m_u8VideoOutCodec;		/* video output codec */
}

/*EvtH245OLC*/
class Evt_H245_OLC {
	public byte       	u8ChannelNumber;// logical channel number
	public byte       	u8Direction;	// transmit or receive
	public byte       	u8Codec;		// codec type
	public byte       	u8DecoderConfigInfoLen;	//decoder Config Length
	public byte       	s8DecoderConfigInfo[] = new byte[200];
}

/*EvtH245CLC*/
class Evt_H245_CLC {
	public byte    	u8ChannelNumber;// logical channel number
	public byte    	u8Direction;	// transmit or receive
	public byte     u8Reserved[] = new byte[2];
}

/*EvtH245SIG_PDU*/
class Evt_H245_SIG_PDU {
	public byte  	m_u8H245SigPdu[] = new byte[128];		/* H.245 signal data */
}

/*EvtH245USER_INPUT*/
class H245_UII{
	public byte     m_u8Type;		/* type=1: send signal, type=2: send str, type=3: send signal and str */
	public byte     m_s8Signal;		
	public byte     str[] = new byte[126];     
}

class  ITP_3G_FaxToneStruct_t
{
	public short    m_u16ChanEnable;  // 1: enable; 0: disable
}/*ITP_3G_FaxToneStruct_t;*/

class ITP_3G_FaxToneEventStruct_t
{
	public short    m_u16ChanState;  //1��ofax_tone; 0: voice tone
}/*ITP_3G_FaxToneEventStruct_t;*/

/*Acs_SS7RawFrame_Data*/
class Acs_SS7RawFrame_Data
{
	public byte    m_u8UserType; /*SS7 frame user type,reference XMS_SS7_FRAME_USER_TYPE*/
	public byte    m_u8LinkType; /*SS7 frame link type,reference XMS_SS7_FRAME_LINK_TYPE*/
	public byte    m_u8InfoType; /*SS7 frame info type,reference XMS_SS7_FRAME_INFO_TYPE*/
	public byte    m_u8InfoLen;  /*SS7 frame info len*/
	public byte    m_u8Rfu1[] = new byte[4];
	public byte    m_u8Info[] = new byte[255];/*SS7 frame info*/
	public byte    m_u8Rfu2;
}/**/

/*Acs_SS7RawFrame_Evt*/
class Acs_SS7RawFrame_Evt
{
	public ACS_EVT_HEAD              m_AcsEvtHead = new ACS_EVT_HEAD();         /*acs event head*/	
	public Acs_SS7RawFrame_Data		 m_AcsSS7RawFrameData = new Acs_SS7RawFrame_Data(); /*acs ss7 ras frame data*/
}/**/


/*Acs_MediaPrivateExt_Data*/
class Acs_MediaPrivateExt_Data
{
	public int    m_u32ExtType;        //reference to XMS_PRIVATE_EXT_TYPE
	public byte   m_u8Buf[] = new byte[260];
}/*Acs_MediaPrivateExt_Data*/ 

/*Acs_MediaECM_OffSet*/
class Acs_MediaECM_OffSet 
{
	public int    m_u32Play_FileOffset; //
	public int    m_u32Play_Max_Length; //
}/*Acs_MediaECM_OffSet*/

/*Acs_MediaECM_CMD*/
class Acs_MediaECM_CMD 
{
	public short  m_u16FrameNums;
	public short  m_u16Reserved[] = new short[3];
	public Acs_MediaECM_OffSet m_stOffSet[] = new Acs_MediaECM_OffSet[256];
	
	public Acs_MediaECM_CMD(){
		for (int i = 0; i < 256; i++){
			m_stOffSet[i] = new Acs_MediaECM_OffSet();
		}
	}
}/*Acs_MediaECM_CMD*/

/*Acs_AnalogEM_CMD*/
class Acs_AnalogEM_CMD 
{
	public byte		m_u8Channel_Enable;
	public byte		m_u8Type;
	public byte		m_u8Tx_State;
	public byte		m_u8Rx_State;
}/*Acs_AnalogEM_CMD*/

/*Acs_SysMon_Data*/
class Acs_SysMon_Data
{    
	public byte	    m_u8ModuleType;       /*Module type*/
	public byte     m_u8UnitID;           /*Module unitid*/        
	public short    m_u16ModuleState;     /*Module state,reference XMS_SYSMON_MODSTATE*/        
    public byte     m_s8IPAddress[] = new byte[32];    /*Module IP address*/
    public int      m_u32Port;            /*Module port*/
    public byte     m_s8Rfu[] = new byte[16];          /*rfu*/
}/**/

/*Acs_SysMon_Evt*/
class Acs_SysMon_Evt
{
	public ACS_EVT_HEAD          m_AcsEvtHead = new ACS_EVT_HEAD();     /*acs event head*/	
	public Acs_SysMon_Data       m_AcsSysMonData = new Acs_SysMon_Data(); /*acs fax proc data*/
}/**/

/*Acs_VoIP_Regist_Evt*/
class Acs_VoIP_Regist_Evt
{
	public ACS_EVT_HEAD	    m_AcsEvtHead = new ACS_EVT_HEAD();
	public Acs_VoIP_Regist  m_AcsRegist = new Acs_VoIP_Regist();
}/*Acs_VoIP_Regist_Evt*/

/*Acs_VoIP_Regist_State_Evt*/
class Acs_VoIP_Regist_State_Evt
{
	public ACS_EVT_HEAD	    	m_AcsEvtHead = new ACS_EVT_HEAD();
	public Acs_VoIP_REGSTATE	m_AcsRegistState = new Acs_VoIP_REGSTATE();
}/*Acs_VoIP_Regist_State_Evt*/

/*Acs_VoIP_Regist_Response_Evt*/
class Acs_VoIP_Regist_Response_Evt
{
	public ACS_EVT_HEAD	    		   m_AcsEvtHead = new ACS_EVT_HEAD();
	public Acs_VoIP_Regist_Response    m_AcsRegistResp = new Acs_VoIP_Regist_Response();
}/*Acs_VoIP_Regist_Response_Evt*/

/*Acs_VoIP_ReferResult_Evt*/
class Acs_VoIP_ReferResult_Evt
{
    public ACS_EVT_HEAD	    	   m_AcsEvtHead = new ACS_EVT_HEAD();
    public Acs_VoIP_ReferResult    m_AcsReferResult = new Acs_VoIP_ReferResult();
}/*Acs_VoIP_ReferResult_Evt*/

/*Acs_VoIP_MediaInfo_Evt*/
class Acs_VoIP_MediaInfo_Evt
{
	public ACS_EVT_HEAD	   		    m_AcsEvtHead = new ACS_EVT_HEAD();
	public Acs_VoIP_MediaInfo	    m_AcsMediaInfo = new Acs_VoIP_MediaInfo();
}/*Acs_VoIP_MediaInfo_Evt*/

/*Acs_VoIP_RTPSESSION_Evt*/
class Acs_VoIP_RTPSESSION_Evt
{
	public ACS_EVT_HEAD	    		m_AcsEvtHead = new ACS_EVT_HEAD();
	public Acs_VoIP_RTPSESSION	    m_AcsRtpSession = new Acs_VoIP_RTPSESSION();
}/*Acs_VoIP_RTPSESSION_Evt*/

/*Acs_VoIP_RTPADDR_Evt*/
class Acs_VoIP_RTPADDR_Evt
{
	public ACS_EVT_HEAD	    	m_AcsEvtHead = new ACS_EVT_HEAD();
	public Acs_VoIP_RTPADDR	    m_AcsRtpAddr = new Acs_VoIP_RTPADDR();
}/*Acs_VoIP_RTPADDR_Evt*/

/*Acs_VoIP_RTCPADDR_Evt*/
class Acs_VoIP_RTCPADDR_Evt
{
    public ACS_EVT_HEAD	    m_AcsEvtHead = new ACS_EVT_HEAD();
    public Acs_VoIP_RTPADDR	m_AcsRtcpAddr = new Acs_VoIP_RTPADDR();
}/*Acs_VoIP_RTCPADDR_Evt*/

/*Acs_VoIP_RTPCODEC_Evt*/
class Acs_VoIP_RTPCODEC_Evt
{
    public ACS_EVT_HEAD	    		m_AcsEvtHead = new ACS_EVT_HEAD();
    public Acs_VoIP_RTPCODEC	    m_AcsRtpCodec = new Acs_VoIP_RTPCODEC();
}/*Acs_VoIP_RTPCODEC_Evt*/
/*UserEvt_Head_t*/
class UserEvt_Head_t
{
    public int    			m_u32UsrEvtType;     /*User self-define event type*/
    public int    			m_u32UsrEvtLen;      /*User self-define event length*/
    public byte     		m_Rfu1[] = new byte[4];
    public byte				m_pUsrEvtData[];
}/**/

/*Acs_UserDef_Evt*/
class Acs_UserDef_Evt
{
	public ACS_EVT_HEAD     m_AcsEvtHead = new ACS_EVT_HEAD();     /*acs event head*/	
	public UserEvt_Head_t   m_UsrEvtHead = new UserEvt_Head_t();     /*User self-define event head*/
}/**/

/*Acs_ModRelate_Mod*/
class Acs_ModRelate_Mod
{    	
	public byte             m_u8ModuleType;       /*Module type*/
	public byte             m_u8UnitID;           /*Module unitid*/        	
	public byte             m_u8Flag;             /*Relate flag, 0:upper module; 1:lower module*/ 
	public byte             m_s8Rfu1;          /*rfu1*/        
	public byte             m_s8IPAddress[] = new byte[32];    /*Module IP address*/
	public int              m_u32Port;            /*Module port*/
    public byte             m_s8Rfu2[] = new byte[4];           /*rfu2*/
}/**/

/*Acs_ModRelate_Data*/
class Acs_ModRelate_Data
{    
	public byte                m_u8ModCount;         /*Relate module count*/
	public byte                m_u8SrcModType;
	public byte                m_u8SrcModUnitID;
	public byte                m_rfu1;
    public Acs_ModRelate_Mod   m_RelateMod[] = new Acs_ModRelate_Mod[64]; /*Relate module info*/    
    
    public Acs_ModRelate_Data(){
    	for (int i = 0; i < 64; i++){
    		m_RelateMod[i] = new Acs_ModRelate_Mod();
    	}
    }
}/**/

/*Acs_ModRelate_Evt*/
class Acs_ModRelate_Evt
{
	public ACS_EVT_HEAD          m_AcsEvtHead = new ACS_EVT_HEAD();     /*acs event head*/	
	public Acs_ModRelate_Data    m_AcsModRelateData = new Acs_ModRelate_Data(); /*acs fax proc data*/
}/**/

/*Acs_VoIPMon_Data*/
class Acs_VoIPMon_Data
{    
	public int               m_u32DataLen;
	public byte              m_u8MonData[] = new byte[1024];     /*VoIP Mon data*/	
}/**/

/*Acs_ModRelate_Evt*/
class Acs_VoIPMon_Evt
{
	public ACS_EVT_HEAD          m_AcsEvtHead = new ACS_EVT_HEAD();     /*acs event head*/	
	public Acs_VoIPMon_Data      m_AcsVoIPMonData = new Acs_VoIPMon_Data(); /*acs VoIP mon data*/
}/**/

class ACS_Digital_PortState_Data 
{
	public byte			m_u8Lost_signal;	//
	public byte			m_u8Fas_align;	//
	public byte			m_u8Mf_align; 	//
	public byte			m_u8Crc4_align; 	//
	public byte			m_u8Remote_alarm; 	//
	public byte			m_u8Remote_MF_alarm;	//
	public byte			m_u8Rx_level;	//0-15: *(-2.5db)
	public byte			m_u8Tx_open;	//1:open circuit,
	public byte			m_u8Tx_overlimit;	//1:current over limit
	public byte			m_u8Port_Current_State;	//0: error state; 1: normal working state
	public byte			m_u8Port_Normal_Count;	//seconds of digital port normal working
	public byte			m_u8Port_Error_Count;	// seconds of digital port error
	public int			m_u32total_seconds;	//
	public int			m_u32RLOS_seconds;	//
	public int		 	m_u32LRCL_seconds;	//
	public int		 	m_u32RUA1_seconds;	//
	public int		 	m_u32RRA_seconds;	//
	public int		 	m_u32RDMA_seconds;	//
	public int		 	m_u32ILUT_seconds;	//
	public int		 	m_u32JALT_seconds;	//
	public int		 	m_u32TOCD_seconds;	//
	public int		 	m_u32TCLE_seconds;	//
	public int		 	m_u32RSLIP_seconds;	//
	public int		 	m_u32TSLIP_seconds;	//
	public int		 	m_u32LCVCR_count;	//
	public int		 	m_u32PCVCR_count;	//
	public int		 	m_u32FOSCR_count;	//
	public int		 	m_u32EBCR_count;		//
	public int			m_u32HDLC1_Tx_packets;	//
	public int			m_u32HDLC1_Rx_goodpk;	//
	public int			m_u32HDLC1_Rx_badpk;		//
	public int			m_u32HDLC2_Tx_packets;	//
	public int			m_u32HDLC2_Rx_goodpk;	//
	public int			m_u32HDLC2_Rx_badpk;		//
	public byte			m_u8E1Type;		/*E1 type*/
	public byte			m_u8Rfu[] = new byte[3];	/**/
}

class ACS_Digital_PortState_Evt
{
	public ACS_EVT_HEAD                 m_AcsEvtHead = new ACS_EVT_HEAD();
	public ACS_Digital_PortState_Data   m_AcsDigitalPortStateData = new ACS_Digital_PortState_Data();
}

class ACS_Clock_RefSrc_State_Data 
{
	public byte	     m_u8ModuleID;            /*The Module ID Of DSP*/
	public byte	     m_u8E1ID;                /*The E1 ID Of A DSP*/
	public byte	     m_u8State;               /*The E1's Master Clock Ref Source Of A DSP, Reference to XMS_CLK_STATE_TYPE*/
	public byte	     m_u8ClockType;           /*Keygoe current clock type is slave or master,Reference XMS_BOARD_CLOCK_TYPE*/
	public byte	     m_u8Ref[] = new byte[4];              /*Reserve*/
}

class ACS_Clock_RefSrc_State_Evt
{
    public ACS_EVT_HEAD                  m_AcsEvtHead = new ACS_EVT_HEAD();
    public ACS_Clock_RefSrc_State_Data   m_AcsClockRefSrcStateData = new ACS_Clock_RefSrc_State_Data();  
}

/* Acs VoIP SIP User Agent struct */
class Acs_VoIP_SIP_User_Agent
{
	public byte		m_s8UserAgent[] = new byte[40];	/* Sip User Agent Name with version No */
}/*Acs_VoIP_SIP_User_Agent*/

/* Acs VoIP SIP Diversion Information struct */
class Acs_VoIP_Call_Diversion_Info
{
	public byte		m_s8Diversion[] = new byte[64];	/* Sip Call Diversion URL */
	public byte		m_s8Reason[] = new byte[16];		/* Sip Call Diversion Reason */
}/*Acs_VoIP_Call_Diversion_Info*/

















/*constant definitions*/

/* Event class define*/
class XMS_EVT_CLASS{
	public static final int XMS_EVT_CLASS_GENERAL            = 0x0001;
	public static final int XMS_EVT_CLASS_CALLCONTROL        = 0x0002;
	public static final int XMS_EVT_CLASS_CONFPROC           = 0x0003;
	public static final int XMS_EVT_CLASS_VOIPPROC           = 0x0004;
	public static final int XMS_EVT_CLASS_MEDIAPROC          = 0x0005;
	public static final int XMS_EVT_CLASS_FAXPROC            = 0x0006;
	public static final int XMS_EVT_CLASS_IOPROC             = 0x0007;
	public static final int XMS_EVT_CLASS_SYSMONITOR         = 0x0008;
	public static final int XMS_EVT_CLASS_UNIFAILURE         = 0x0009;	
};

/*Event type define */
class XMS_EVT_TYPE{
	public static final int XMS_EVT_OPEN_STREAM                     = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x01);
	public static final int XMS_EVT_QUERY_DEVICE                    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x02);	
	public static final int XMS_EVT_QUERY_DEVICE_END                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x03);
	public static final int XMS_EVT_OPEN_DEVICE                     = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x04);
	public static final int XMS_EVT_CLOSE_DEVICE                    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x05);
	public static final int XMS_EVT_RESET_DEVICE                    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x06);
	public static final int XMS_EVT_DEVICESTATE                     = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x07);
	public static final int XMS_EVT_SETDEV_GROUP                    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x08);
	public static final int XMS_EVT_SETPARAM                        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x09);
	public static final int XMS_EVT_GETPARAM                        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0A);
	public static final int XMS_EVT_QUERY_ONE_DSP_START             = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0B);
	public static final int XMS_EVT_QUERY_ONE_DSP_END               = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0C);
	public static final int XMS_EVT_QUERY_REMOVE_ONE_DSP_START      = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0D);
	public static final int XMS_EVT_QUERY_REMOVE_ONE_DSP_END        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0E);
	public static final int XMS_EVT_OPEN_STREAM_EXT                 = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x0F);	
	public static final int XMS_EVT_LICENSE_QUERY                   = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x10);	
	public static final int XMS_EVT_CLOSE_STREAM_EXT                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x11);	
	public static final int XMS_EVT_MASTER_STATE                    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x13);
	public static final int XMS_EVT_SLAVE_WORK_STATE			    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x14);
	public static final int XMS_EVT_E1STATE                         = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x20);
	public static final int XMS_EVT_CTBUS_CLK_REF_SRC_STATE         = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0x30);
	public static final int XMS_EVT_USER_DEF                        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0xE0);	
	public static final int XMS_EVT_BAKSYS_STOP                     = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0xF0);
	public static final int XMS_EVT_ACS_TIMER                       = ((XMS_EVT_CLASS.XMS_EVT_CLASS_GENERAL<<16)+0xFF);
			
	public static final int XMS_EVT_CALLOUT							= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x01);
	public static final int XMS_EVT_CALLIN							= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x02);
	public static final int XMS_EVT_ALERTCALL		                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x03);
	public static final int XMS_EVT_ANSWERCALL		                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x04);
	public static final int XMS_EVT_LINKDEVICE				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x05);
	public static final int XMS_EVT_UNLINKDEVICE					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x06);
	public static final int XMS_EVT_CLEARCALL						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x07);
	public static final int XMS_EVT_ANALOG_INTERFACE                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x08);
	public static final int XMS_EVT_CAS_MFC_START					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x09);
	public static final int XMS_EVT_CAS_MFC_END						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0A);
	public static final int XMS_EVT_SENDSIGMSG						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0B);		
	public static final int XMS_EVT_SIGMON       					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0C);
	public static final int XMS_EVT_3G324M       					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0D);
	public static final int XMS_EVT_CTX_REG                         = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0E);
	public static final int XMS_EVT_CTX_LINK                        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x0F);
	public static final int XMS_EVT_CTX_APPDATA                     = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x10);
	public static final int XMS_EVT_DRS_CALL_NUMS                   = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x11);
	
	public static final int XMS_EVT_SS7RawFrame						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x20);
	public static final int XMS_EVT_SS7SendRawFrame					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CALLCONTROL<<16)+0x21);

	public static final int XMS_EVT_JOINTOCONF					    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CONFPROC<<16)+0x01);
	public static final int XMS_EVT_LEAVEFROMCONF					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_CONFPROC<<16)+0x02);
	public static final int XMS_EVT_CLEARCONF					    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_CONFPROC<<16)+0x03);
		
	public static final int XMS_EVT_SET_PAYLOAD				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x01);
	public static final int XMS_EVT_SET_RTPADDR				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x02);
	public static final int XMS_EVT_SET_RTCPADDR				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x03);
	public static final int XMS_EVT_SET_RTPCODEC				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x04);
	public static final int XMS_EVT_SET_MEDIAINFO				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x05);
	public static final int XMS_EVT_REFER_RESULT				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x06);
	public static final int XMS_EVT_REGIST				    	    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x07);
	public static final int XMS_EVT_REGIST_RESP				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_VOIPPROC<<16)+0x08);

	public static final int XMS_EVT_PLAY			                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x01);
	public static final int XMS_EVT_INITINDEX				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x02);
	public static final int XMS_EVT_BUILDINDEX						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x03);
	public static final int XMS_EVT_CONTROLPLAY				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x04);
	public static final int XMS_EVT_RECORD							= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x05);
	public static final int XMS_EVT_CONTROLRECORD				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x06);
	public static final int XMS_EVT_RECORDCSP   				    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x07);
	public static final int XMS_EVT_CONTROLRECORDCSP    		    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x08);
	public static final int XMS_EVT_3GPP_PLAY			            = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x09);
	public static final int XMS_EVT_3GPP_CONTROLPLAY		        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0A);
	public static final int XMS_EVT_3GPP_RECORD	    				= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0B);
	public static final int XMS_EVT_3GPP_CONTROLRECORD    		    = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0C);
	public static final int XMS_EVT_PLAYCSPREQ 				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0D);
	public static final int XMS_EVT_3GPP_INIT_INDEX                 = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0E);
	public static final int XMS_EVT_3GPP_BUILD_INDEX                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x0F);
	
	public static final int XMS_EVT_3GVCONF_JOIN					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x10);
	public static final int XMS_EVT_3GVCONF_LEAVE					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x11);
	public static final int XMS_EVT_3GVCONF_CLEAR					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x12);
	public static final int XMS_EVT_3GVCONF_GETLAYOUT				= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x13);
	public static final int XMS_EVT_3GVCONF_SETLAYOUT				= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x14);
	public static final int XMS_EVT_3GVCONF_GETVISIBLELIST			= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x15);
	public static final int XMS_EVT_3GVCONF_SETVISIBLELIST			= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x16);
	public static final int XMS_EVT_3GVCONF_STOP					= ((XMS_EVT_CLASS.XMS_EVT_CLASS_MEDIAPROC<<16)+0x17);
	
	public static final int XMS_EVT_SENDFAX			                = ((XMS_EVT_CLASS.XMS_EVT_CLASS_FAXPROC<<16)+0x01);
	public static final int XMS_EVT_RECVFAX					        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_FAXPROC<<16)+0x02);
			
	public static final int XMS_EVT_SENDIODATA						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_IOPROC<<16)+0x01);
	public static final int XMS_EVT_RECVIODATA						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_IOPROC<<16)+0x02);
		
	public static final int XMS_EVT_MODMONITOR				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR<<16)+0x01);
	public static final int XMS_EVT_DEV_TIMER						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR<<16)+0x02);
	public static final int XMS_EVT_MODRELATE				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR<<16)+0x03);
	public static final int XMS_EVT_VOIPMON  				        = ((XMS_EVT_CLASS.XMS_EVT_CLASS_SYSMONITOR<<16)+0x04);
	
	public static final int XMS_EVT_UNIFAILURE						= ((XMS_EVT_CLASS.XMS_EVT_CLASS_UNIFAILURE<<16)+0x01);
}

class XMS_DEVMAIN_TYPE{
	public static final int XMS_DEVMAIN_CONFIG               = 0x01; /*config adding for log manager*/
	public static final int XMS_DEVMAIN_VOICE                = 0x02; /*Voice device*/
	public static final int XMS_DEVMAIN_FAX                  = 0x03; /*Fax device*/
	public static final int XMS_DEVMAIN_DIGITAL_PORT         = 0x04; /*Digital Port device*/
	public static final int XMS_DEVMAIN_INTERFACE_CH         = 0x05; /*Interface Ch device*/
	public static final int XMS_DEVMAIN_DSS1_LINK            = 0x06; /*DSS1 Link device*/
	public static final int XMS_DEVMAIN_SS7_LINK             = 0x07; /*SS7 Link device*/
	public static final int XMS_DEVMAIN_BOARD                = 0x08; /*DSP Board device*/
	public static final int XMS_DEVMAIN_CTBUS_TS             = 0x09; /*CTBus ts device*/
	public static final int XMS_DEVMAIN_RTP                  = 0x0A; /*VoIP device*/
	public static final int XMS_DEVMAIN_MEDIAEX              = 0x0B; /*MediaEx device*/
	public static final int XMS_DEVMAIN_CONFERENCE           = 0x0C; /*Conference Group Device*/
	public static final int XMS_DEVMAIN_VIDEO                = 0x0D; /*Video device*/
	public static final int XMS_DEVMAIN_CTX                  = 0x10; /*Ctx device*/
	public static final int XMS_DEVMAIN_RTPX                 = 0x11; /*RTPX device*/
	public static final int XMS_DEVMAIN_VOIP                 = 0x12; /*VoIP device*/
	public static final int XMS_DEVMAIN_VIDEOCONF            = 0x1F; /*Video Conference Device*/
}

class XMS_INTERFACE_DEVSUB_TYPE
{
	public static final int XMS_DEVSUB_BASE                       = 0x0;  /*Base*/
	public static final int XMS_DEVSUB_ANALOG_TRUNK               = 0x01; /*Analog Trunk*/
	public static final int XMS_DEVSUB_ANALOG_USER                = 0x02; /*Analog User*/
	public static final int XMS_DEVSUB_ANALOG_HIZ                 = 0x03; /*Analog Hiz*/
	public static final int XMS_DEVSUB_ANALOG_EMPTY               = 0x04; /*Analog Empty*/
	public static final int XMS_DEVSUB_E1_PCM                     = 0x05; /*E1 PCM*/
	public static final int XMS_DEVSUB_E1_CAS                     = 0x06; /*E1 CAS*/
	public static final int XMS_DEVSUB_E1_DSS1                    = 0x07; /*E1 DSS1*/
	public static final int XMS_DEVSUB_E1_SS7_TUP                 = 0x08; /*E1 SS7 TUP*/
	public static final int XMS_DEVSUB_E1_SS7_ISUP                = 0x09; /*E1 SS7 ISUP*/
	public static final int XMS_DEVSUB_ANALOG_VOC2W			      = 0x0A; /*Voice only 2 wire*/
	public static final int XMS_DEVSUB_ANALOG_VOC4W			      = 0x0B; /*Voice only 4 wire*/
	public static final int XMS_DEVSUB_ANALOG_EM			      = 0x0C; /*EM control module*/
	public static final int XMS_DEVSUB_ANALOG_MAG			      = 0x0D; /*magnetic module*/
	public static final int XMS_DEVSUB_E1_DCH				      = 0x0E; /*E1 6D25B's Dchannel*/
	public static final int XMS_DEVSUB_E1_BCH				      = 0x0F; /*E1 6D25B's Bchannel*/
	public static final int XMS_DEVSUB_UNUSABLE				      = 0x10; /*unusable timeslot, such as ts0 of E1*/
	public static final int XMS_DEVSUB_HIZ_CAS				      = 0x11; /*Hiz Cas*/
	public static final int XMS_DEVSUB_HIZ_PRI				      = 0x12; /*Hiz Pri*/
	public static final int XMS_DEVSUB_HIZ_SS7					  = 0x13; /*Hiz ss7*/
	public static final int XMS_DEVSUB_HIZ_PRI_LINK			      = 0x14; /*Hiz pri link*/
	public static final int XMS_DEVSUB_HIZ_SS7_64K_LINK  		  = 0x15; /*Hiz ss7 64k link*/
	public static final int XMS_DEVSUB_HIZ_SS7_2M_LINK    		  = 0x16; /*Hiz ss7 2M link*/
	public static final int XMS_DEVSUB_SS7_LINK		              = 0x17; /*ss7 link*/
	public static final int XMS_DEVSUB_LINESIDE		              = 0x18; /*LineSide E1*/
	public static final int XMS_DEVSUB_ANALOG_REC	              = 0x19; /*Analog phone Record*/
	public static final int XMS_DEVSUB_HIZ_HDLC_N64K_LINK         = 0x1A; /*Hiz n*64K */
	public static final int XMS_DEVSUB_SS7_2M_LINK                = 0x1B; /*SS7 2M LINK*/
	public static final int XMS_DEVSUB_HIZ_HDLC                   = 0x1C; /*Hiz */
	public static final int XMS_DEVSUB_DIGITAL_REC	              = 0x20; /*Digital phone Record*/
};

class XMS_MEDIA_DEVSUB_TYPE
{
	public static final int XMS_DEVSUB_MEDIA_VOC                 = 0x0;  /*voc device*/
	public static final int XMS_DEVSUB_MEDIA_324                 = 0x1;  /*324 device*/
	public static final int XMS_DEVSUB_MEDIA_RAW				 = 0x2;	 /*Raw device*/
}

class XMS_CTBUS_DEVSUB_TYPE
{
	public static final int XMS_DEVSUB_CTBUS_LINK                 = 0x0; /*CTBus link ts*/	
	public static final int XMS_DEVSUB_CTBUS_CTX                  = 0x1; /*CTBus CTX ts*/	
};

class XMS_E1_TYPE
{
	public static final int XMS_E1_TYPE_Analog30	         = 1; /* Analog Interface 30*/
	public static final int XMS_E1_TYPE_PCM31		         = 2; /* E1 Frame,ts31*/
	public static final int XMS_E1_TYPE_PCM30		         = 3; /* E1 Frame,ts 30*/
	public static final int XMS_E1_TYPE_CAS			         = 4; /* E1 Frame,CAS*/
	public static final int XMS_E1_TYPE_PRI			         = 5; /* E1 Frame,PRI*/
	public static final int XMS_E1_TYPE_SS7_TUP_0_Link	     = 6; /* E1 Frame,TUP: 0 link*/
	public static final int XMS_E1_TYPE_SS7_TUP_1_Link	     = 7; /* E1 Frame,TUP: 1 link*/
	public static final int XMS_E1_TYPE_SS7_TUP_2_Link	     = 8; /* E1 Frame,TUP: 2 link*/
	public static final int XMS_T1_TYPE_D4	                 = 9; /* T1 Frame*/
	public static final int XMS_T1_TYPE_ESF		             = 10; /* T1 Frame*/
	public static final int XMS_J1_TYPE_D4		             = 11; /* J1 Frame*/
	public static final int XMS_J1_TYPE_ESF		             = 12; /* J1 Frame*/
	public static final int XMS_SLC_TYPE_96    	             = 13; /* SLC_96 Frame*/
	public static final int XMS_E1_TYPE_SS7_ISUP_0_Link	     = 14; /* E1 Frame,ISUP: 0 link*/
	public static final int XMS_E1_TYPE_SS7_ISUP_1_Link	     = 15; /* E1 Frame,ISUP: 1 link*/
	public static final int XMS_E1_TYPE_SS7_ISUP_2_Link	     = 16; /*E1 Frame,ISUP: 2 link*/
	public static final int XMS_E1_TYPE_6D25B		     	 = 17; /* E1 Frame, 6 DChannel,25 BChannel*/
	public static final int XMS_E1_TYPE_1D30B                = 18; /*E1 Frame, 1 DChannel, 30 BChannel*/
	public static final int XMS_E1_TYPE_11D20B               = 19; /*E1 Frame, 11 DChannel, 20 BChannel*/
	public static final int XMS_E1_TYPE_HIZ_CAS              = 20; /*E1 Frame, HIZ CAS*/
	public static final int XMS_E1_TYPE_HIZ_PRI              = 21; /*E1 Frame, HIZ PRI*/	
	public static final int XMS_E1_TYPE_HIZ_SS7              = 22; /*E1 Frame, HIZ SS7*/
	public static final int XMS_E1_TYPE_HIZ_64K_SS7   	     = 23; /*E1 Frame, HIZ pure 64k SS7*/
	public static final int XMS_E1_TYPE_HIZ_2M_SS7           = 24; /*E1 Frame, HIZ 2M SS7*/
	public static final int XMS_E1_TYPE_LINESIDE             = 25; /*E1 Frame, lineside*/
	public static final int XMS_E1_TYPE_HIZ_N64K_HDLC        = 26; /*E1 Frame, HIZ N*64K HDLC*/	
	public static final int XMS_E1_TYPE_2M_SS7				 = 27; /*E1 Frame, 2M SS7*/
}

/*E1 STATE BITS DEFINE*/
class XMS_E1PORT_MASK_STATE
{
	public static final int XMS_E1PORT_MASK_LOST_SIGNAL	     = 0x00000001;
	public static final int XMS_E1PORT_MASK_FAS_ALARM	     = 0x00000002;
	public static final int XMS_E1PORT_MASK_MFAS_ALARM	     = 0x00000004;
	public static final int XMS_E1PORT_MASK_CRC4_ALARM	     = 0x00000008;
	public static final int XMS_E1PORT_MASK_REMOTE_ALARM	 = 0x00000010;
	public static final int XMS_E1PORT_MASK_REMOTE_MF_ALARM	 = 0x00000020;
	public static final int XMS_E1PORT_MASK_TX_OPEN_ALARM	 = 0x00000040;
	public static final int XMS_E1PORT_MASK_TX_SHORT_ALARM	 = 0x00000080;
	public static final int XMS_E1PORT_MASK_RX_LEVEL	     = 0x00000F00;
	public static final int XMS_E1PORT_MASK_TYPE		     = 0x00FF0000;
}

class XMS_VOC_SRC_MODE
{
	public static final int XMS_SRC_8K                       = 0x0;
	public static final int XMS_SRC_6K                       = 0x1;
	public static final int XMS_SRC_GTG                      = 0x2;
	public static final int XMS_SRC_FSK                      = 0x3;
	public static final int XMS_SRC_RTP                      = 0x4;
	public static final int XMS_SRC_FAX                      = 0x5;
	public static final int XMS_SRC_3GVIDEO                  = 0x6;
	public static final int XMS_SRC_11K                      = 0x7;
	public static final int XMS_SRC_FAX_ECM                  = 0x8;
}

class XMS_VOC_CODE_TYPE
{
	public static final int XMS_Alaw_type                    = 0x0;
	public static final int XMS_Ulaw_type                    = 0x1;
	public static final int XMS_Vox_type                     = 0x2;
	public static final int XMS_Linear_8bit                  = 0x3;
	public static final int XMS_Linear_16bit                 = 0x4;
	public static final int XMS_Amr_type                     = 0x5;
	public static final int XMS_G723_type                    = 0x6;
	public static final int XMS_CODE_STREAM                  = 0x7;
}

class XMS_PLAYREC_STOP_MODE
{
	public static final int XMS_Normal_Stop                  = 0x0;
	public static final int XMS_Single_Code                  = 0x1;
	public static final int XMS_Any_Code                     = 0x2;
}

class XMS_CSPREC_TYPE
{
	public static final int XMS_CSPREC_NONE                  = 0x0;
	public static final int XMS_CSPREC_BARGEIN               = 0x1;
	public static final int XMS_CSPREC_NON_BARGEIN           = 0x2;
}

class XMS_CSPREC_PRIV_TYPE
{
	public static final int XMS_CSPREC_PRIV_CMD              = 0x0;
}

class XMS_CSPREC_CMD_OPT
{
	public static final int XMS_CSPREC_CMD_NORMAL            = 0x0;
	public static final int XMS_CSPREC_CMD_DIRECT            = 0x1;
}

class XMS_CONTROL_CSPREC_PRIV_TYPE
{
	public static final int XMS_CONTROL_CSPREC_PRIV_CMD      = 0x0;
}

class XMS_CONTROL_CSPREC_CMD_OPT
{
	public static final int XMS_CONTROL_CSPREC_CMD_NORMAL    = 0x0;
	public static final int XMS_CONTROL_CSPREC_CMD_DIRECT    = 0x1;
}

class XMS_PLAY_TYPE
{
	public static final int XMS_PLAY_TYPE_FILE               = 0x0;
	public static final int XMS_PLAY_TYPE_INDEX              = 0x1;
	public static final int XMS_PLAY_TYPE_FILE_QUEUE         = 0x2;
	public static final int XMS_PLAY_TYPE_INDEX_QUEUE        = 0x3;
}

class XMS_BUILD_INDEX_TYPE
{
	public static final int XMS_BUILD_INDEX_RAM              = 0x4;
	public static final int XMS_BUILD_INDEX_FILE             = 0x5;
}

class XMS_CFG_TYPE
{
	public static final int XMS_CFG_TYPE_NON_INDEX           = 0x0;
	public static final int XMS_CFG_TYPE_INDEX               = 0x1;
}

class XMS_CTRL_PLAY_TYPE
{
	public static final int XMS_STOP_PLAY                    = 0x0;
	public static final int XMS_PAUSE_PLAY                   = 0x1;
	public static final int XMS_RESUME_PLAY                  = 0x2;
	public static final int XMS_STEP_BACKWARD_PLAY           = 0x3;
	public static final int XMS_STEP_FORWARD_PLAY            = 0x4;

	public static final int XMS_CSP_STOP_PLAY                = 0x5;
	public static final int XMS_CSP_PAUSE_PLAY               = 0x6;
	public static final int XMS_CSP_RESUME_PLAY              = 0x7;
	public static final int XMS_CSP_STEP_BACKWARD_PLAY       = 0x8;
	public static final int XMS_CSP_STEP_FORWARD_PLAY        = 0x9;
	public static final int XMS_CSP_DELAY_STOP_PLAY          = 0xA;
}

class XMS_PLAY_GAIN_MODE
{
	public static final int XMS_PLAY_GAIN_MODE_NOCHANGE     = 0x0;
	public static final int XMS_PLAY_GAIN_MODE_FIX          = 0x1;
	public static final int XMS_PLAY_GAIN_MODE_ALS          = 0x2;
	public static final int XMS_PLAY_GAIN_MODE_AGC          = 0x3;
}

class XMS_VOC_OUTPUT_TYPE
{
	public static final int XMS_VOC_OUTPUT_SILENCE           = 0x0;
	public static final int XMS_VOC_OUTPUT_FROM_INPUT        = 0x1;
	public static final int XMS_VOC_OUTPUT_FROM_PLAY         = 0x2;
	public static final int XMS_VOC_OUTPUT_FROM_MIXER        = 0x3; 	
}

class XMS_MIXER_TYPE
{
	public static final int XMS_MIXER_FROM_NULL              = 0x00;
	public static final int XMS_MIXER_FROM_INPUT             = 0x01;
	public static final int 	XMS_MIXER_FROM_PLAY          = 0x02;
	public static final int XMS_MIXER_FROM_CONF              = 0x03;
	public static final int XMS_MIXER_FROM_IP                = 0x04;
	public static final int XMS_MIXER_FROM_324               = 0x05;
	public static final int XMS_MIXER_FROM_RTPX              = 0x06;
}

class XMS_AGC_MODE
{
	public static final int XMS_AGC_MODE_ALS		          = 0x00;
	public static final int 	XMS_AGC_MODE_AGC		      = 0x01;
}

class XMS_EC_REF
{
	public static final int XMS_EC_REF_FROM_INPUT		      = 0x00;
	public static final int XMS_EC_REF_FROM_OUTPUT		      = 0x01;
}

class XMS_CONF_INPUT_OPT
{
	public static final int XMS_CONF_INPUT_OPT_SILENCE        = 0x0;
	public static final int XMS_CONF_INPUT_OPT_NORMAL         = 0x1;
	public static final int XMS_CONF_INPUT_OPT_PLAY           = 0x2;	
}

class XMS_CONF_OUTPUT_OPT
{
	public static final int XMS_CONF_OUTPUT_OPT_SILENCE		  = 0x0;
	public static final int XMS_CONF_OUTPUT_OPT_NORMAL	      = 0x1;
	public static final int XMS_CONF_OUTPUT_OPT_SUM	          = 0x2;
}

class XMS_CTRL_RECORD_TYPE
{
	public static final int XMS_STOP_RECORD                   = 0x0;
	public static final int XMS_PAUSE_RECORD                  = 0x1;
	public static final int XMS_RESUME_RECORD                 = 0x2;
	public static final int XMS_STEP_BACKWARD_RECORD          = 0x3;

	public static final int XMS_CSP_STOP_RECORD               = 0x4;
	public static final int XMS_CSP_PAUSE_RECORD              = 0x5;
	public static final int XMS_CSP_RESUME_RECORD             = 0x6;
	public static final int XMS_CSP_STEP_BACKWARD_RECORD      = 0x7;
	public static final int XMS_CSP_DELAY_STOP_RECORD         = 0x8;
}

class XMS_REC_DELAY_STOP_SWITCH
{
	public static final int XMS_REC_DELAY_STOP_DISABLE        = 0x0;
	public static final int XMS_REC_DELAY_STOP_ENABLE         = 0x1;
}

class XMS_REC_OPENFILE_TYPE
{
	public static final int XMS_REC_FILE_TRUNC                = 0x0;
	public static final int XMS_REC_FILE_APPEND               = 0x1;
}

class XMS_AUDIO_TRACKS
{
	public static final int XMS_AUDIO_TRACKS_MONO             = 0x1;
	public static final int XMS_AUDIO_TRACKS_STEREO           = 0x2;
}

class XMS_VIDEO_CODE_TYPE
{
	public static final int XMS_VIDEO_CODE_TYPE_H263P     	  = 0x1;
	public static final int XMS_VIDEO_CODE_TYPE_H263       	  = 0x2;
	public static final int XMS_VIDEO_CODE_TYPE_MP4V       	  = 0x3;  
	public static final int XMS_VIDEO_CODE_TYPE_H264       	  = 0x4;
}

class XMS_AUDIO_AMR_FRAME_TYPE
{
	public static final int XMS_AMR_FRAME_TYPE_4_75              = 0x0;
	public static final int XMS_AMR_FRAME_TYPE_5_15              = 0x1;
	public static final int XMS_AMR_FRAME_TYPE_5_90              = 0x2;
	public static final int XMS_AMR_FRAME_TYPE_6_70              = 0x3;
	public static final int XMS_AMR_FRAME_TYPE_7_40              = 0x4;
	public static final int XMS_AMR_FRAME_TYPE_7_95              = 0x5;
	public static final int XMS_AMR_FRAME_TYPE_10_2              = 0x6;
	public static final int XMS_AMR_FRAME_TYPE_12_2          = 0x7;
	public static final int XMS_AMR_FRAME_TYPE_AMR_SID           = 0x8;
	public static final int XMS_AMR_FRAME_TYPE_GSM_EFR_SID       = 0x9;
	public static final int XMS_AMR_FRAME_TYPE_TDMA_EFR_SID      = 0xA;
	public static final int XMS_AMR_FRAME_TYPE_PDC_EFR_SID       = 0xB;
	public static final int XMS_AMR_FRAME_TYPE_RESERVED1     = 0xC;
	public static final int XMS_AMR_FRAME_TYPE_RESERVED2         = 0xD;
	public static final int XMS_AMR_FRAME_TYPE_RESERVED3         = 0xE;
	public static final int XMS_AMR_FRAME_TYPE_NO_DATA           = 0xF;
}

class XMS_CSPPLAY_DATA_TYPE
{
	public static final int XMS_CSPPLAY_DATA_VOC                 = 0x0;
	public static final int XMS_CSPPLAY_DATA_VIDEO               = 0x1;
}

class XMS_PRIVATE_EXT_TYPE
{
	public static final int XMS_EXT_TYPE_PATH                    = 0x01;             //extend to path's size from 128 to 260
}

class XMS_BOARD_PRIVATE_EXT_TYPE
{
	public static final int XMS_BOARD_EXT_TYPE_NULL              = 0x00;             //nothing will excute
	public static final int XMS_BOARD_EXT_TYPE_CLOCK             = 0x01;             //extend to main clock in keygoe system
}

/*It will be replaced by XMS_BOARD_CLOCK_MODE later from V3.0.0*/
class XMS_BOARD_EXT_CLOCK_TYPE
{
	public static final int XMS_BOARD_EXT_CLOCK_NO_SET           = 0x00;             //extend to main clock in keygoe system
	public static final int XMS_BOARD_EXT_CLOCK_SET              = 0x01;             //extend to main clock in keygoe system
}


class XMS_BOARD_CLOCK_TYPE
{
	public static final int XMS_BOARD_EXT_CLOCK_TYPE_SLAVE       = 0x01;             //current board set slave clock to the peer CO
	public static final int XMS_BOARD_EXT_CLOCK_TYPE_MASTER      = 0x02;             //current board set master clock to the peer CO         
}

class XMS_BOARD_CLOCK_MODE
{
	public static final int XMS_BOARD_CLOCK_MODE_AUTO      		 = 0x00;     //clock set by Keygoe
	public static final int XMS_BOARD_CLOCK_MODE_MANUAL    		 = 0x01;        //clock set by user-app
}

class XMS_ANALOG_TRUNK_CALLERID_OPT
{
	public static final int XMS_ANALOG_TRUNK_CALLERID_DISABLE      = 0x0;
	public static final int XMS_ANALOG_TRUNK_CALLERID_FSK          = 0x1;
	public static final int XMS_ANALOG_TRUNK_CALLERID_DTMF         = 0x2;
	public static final int XMS_ANALOG_TRUNK_CALLERID_FSKORDTMF    = 0x3;
}

class XMS_ANALOG_TRUNK_DIALTONE_DETECT_OPT
{
	public static final int XMS_ANALOG_TRUNK_DIALTONE_DONTDETECT   = 0x0;
	public static final int XMS_ANALOG_TRUNK_DIALTONE_DETECT       = 0x1;
}

class XMS_ANALOG_TRUNK_CALLOUT_METHOD_OPT
{
	public static final int XMS_ANALOG_TRUNK_CALLOUT_APP_FULLCONTROL     = 0x0;
	public static final int XMS_ANALOG_TRUNK_CALLOUT_NORMAL_PROGRESS     = 0x1;
	public static final int XMS_ANALOG_TRUNK_CALLOUT_POLARITY_REVERSE    = 0x2;
}

class XMS_ANALOG_USER_CALLERID_OPT
{
	public static final int XMS_ANALOG_USER_CALLERID_DSIABLE            = 0x0;
	public static final int XMS_ANALOG_USER_CALLERID_FSK                = 0x1;
	public static final int XMS_ANALOG_USER_CALLERID_DTMF               = 0x2;
}

class XMS_ANALOG_USER_RINGCADENCE_TYPE
{
	public static final int XMS_ANALOG_USER_RINGCADENCE_SINGLEPULSE    = 0x0;
	public static final int XMS_ANALOG_USER_RINGCADENCE_DOUBLEPULSE    = 0x1;
	public static final int XMS_ANALOG_USER_RINGCADENCE_TRIPLEPULSE    = 0x2;
}

class XMS_ANALOG_USER_CALLIN_METHOD_TYPE
{
	public static final int XMS_ANALOG_USER_CALLIN_METHOD_APP_FULLCONTROL    = 0x0;
	public static final int XMS_ANALOG_USER_CALLIN_METHOD_AUTO_RECVCALLEE    = 0x1;
}

class XMS_FAX_MODEM_TYPE
{
	public static final int XMS_F48_Modem                        = 0x0;
	public static final int XMS_F96_Modem                        = 0x1;
	public static final int XMS_F144_Modem                       = 0x2;
}

class XMS_FAX_BPS_TYPE
{
	public static final int XMS_BPS_2400                         = 0x0;
	public static final int XMS_BPS_4800                         = 0x1;
	public static final int XMS_BPS_7200                         = 0x2;
	public static final int XMS_BPS_9600                         = 0x3;
	public static final int XMS_BPS_12000                        = 0x4;
	public static final int XMS_BPS_14400                        = 0x5;
}

class XMS_FAX_T4_TYPE
{
	public static final int XMS_T4_Low_Dencity                   = 0x0;
	public static final int XMS_T4_High_Dencity                  = 0x1;
	public static final int XMS_T4_MH_Encode                     = 0x0;
	public static final int XMS_T4_MR_Encode                     = 0x1;
}

class XMS_FAX_LINE_PIXEL_TYPE
{
	public static final int XMS_Line_Pixel_1728                  = 0x0;
	public static final int XMS_Line_Pixel_2048                  = 0x1;
	public static final int XMS_Line_Pixel_2432                  = 0x2;
	public static final int XMS_Line_Pixel_3456                  = 0x3;
	public static final int XMS_Line_Pixel_4096                  = 0x4;
	public static final int XMS_Line_Pixel_4864                  = 0x5;
}

class XMS_FAX_PAGE_LENGTH
{
	public static final int XMS_Page_Length_A4                   = 0x0;	
	public static final int XMS_Page_Length_B4                   = 0x1;
	public static final int XMS_Page_Length_Unlinit              = 0x2;
}

class XMS_FAX_SCANLINE_TIME
{
	public static final int XMS_Scanline_Time_0                  = 0x0;
	public static final int XMS_Scanline_Time_5                  = 0x1;
	public static final int XMS_Scanline_Time_10                 = 0x2;	
	public static final int XMS_Scanline_Time_20                 = 0x3;
	public static final int XMS_Scanline_Time_40                 = 0x4;
}

class XMS_FAX_HOSTCTRL_TYPE
{
	public static final int XMS_Fax_Null                         = 0x0;
	public static final int XMS_Fax_Recv                         = 0x1;
	public static final int XMS_Fax_Send                         = 0x2;
	public static final int XMS_Fax_Stop                         = 0x3;
}

class XMS_FAX_WORKMODE
{	
	public static final int XMS_FAX_WORKMODE_NORMAL              = 0x00;
	public static final int XMS_FAX_WORKMODE_SERVER              = 0x01;
	public static final int XMS_FAX_WORKMODE_GATEWAY             = 0x02;
}

class XMS_FAX_ECM_MODE_TYPE
{
	public static final int XMS_FAX_ECM_MODE_TYPE_NORMAL         = 0x00;
	public static final int XMS_FAX_ECM_MODE_TYPE_ECM            = 0x01;
}

class XMS_FAX_PAGE_HEADER_TYPE  
{
	public static final int XMS_FAX_PAGE_HEADER_TYPE_CLEAR       = 0x00;
	public static final int XMS_FAX_PAGE_HEADER_TYPE_SET         = 0x01;
}

class XMS_FAX_M_FILE_TYPE
{
	public static final int XMS_FAX_M_FILE_TYPE_CLEAR            = 0x00;
	public static final int XMS_FAX_M_FILE_TYPE_ADD              = 0x02;
}

class XMS_ANSWERCALL_TYPE
{
	public static final int XMS_ANSWERCALL_ANC                   = 0x0;
	public static final int XMS_ANSWERCALL_ANN                   = 0x1;
	public static final int XMS_ANSWERCALL_CON                   = 0x2;
}

class XMS_CTX_REG_TYPE
{
	public static final int XMS_CTX_REG                     = 0x1;/*ctx reg*/
	public static final int XMS_CTX_UNREG                   = 0x2;/*ctx unreg*/
}

class XMS_CTX_LINK_OPTION
{
	public static final int CTX_LINK_OPTION_RESET			= 0x1;/*reset all link*/
	public static final int CTX_LINK_OPTION_LINK			= 0x2;/*single link*/
	public static final int CTX_LINK_OPTION_UNLINK			= 0x3;/*single unlink*/
	public static final int CTX_LINK_OPTION_DUALLINK		= 0x4;/*dual link*/
	public static final int CTX_LINK_OPTION_DUALUNLINK		= 0x5;/*dual unlink*/
}

class XMS_MEDIA_TYPE
{
	public static final int MEDIA_TYPE_AUDIO                     = 0;   /*play audio only*/
	public static final int MEDIA_TYPE_VIDEO                     = 1;   /*play video only*/
    public static final int MEDIA_TYPE_ANV                       = 4;   /*play audio and video*/
    public static final int MEDIA_TYPE_MEDIAEX_AUDIO			 = 5;	/*use mediaex play audio*/
	public static final int MEDIA_TYPE_MEDIAEX_VIDEO			 = 6;	/*use mediaex play video*/
	public static final int MEDIA_TYPE_MEDIAEX_ANV				 = 7;	/*use mediaex play audio and video*/
}

class XMS_SS7_FRAME_USER_TYPE
{
	public static final int XMS_SS7_USER_SCCP = 0x03;
	public static final int XMS_SS7_USER_TUP  = 0x04;
	public static final int XMS_SS7_USER_ISUP = 0x05;
}
 
class XMS_SS7_FRAME_LINK_TYPE
{
	public static final int XMS_SS7_LINK_ITU  = 0x02;
	public static final int XMS_SS7_LINK_CHINA= 0x04;
}
 
class XMS_SS7_FRAME_INFO_TYPE
{
	public static final int XMS_SS7_INFO_DATA   = 0x01;
	public static final int XMS_SS7_INFO_CMD    = 0x02;
}

class XMS_SYSMON_MODSTATE
{   
	public static final int SYSMON_MODSTATE_DISCONNECT      = 0x0;/*Module disconnect*/
	public static final int SYSMON_MODSTATE_CONNECT         = 0x1;/*Module connect*/    
}

class XMS_CTBUS_CLKNET_TYPE
{
	public static final int L_NET0   = 0x08; 
	public static final int L_NET1   = 0x09; 
	public static final int L_NET2   = 0x0A;
	public static final int L_NET3   = 0x0B;   
}

class XMS_VOIP_PROTOCOL_TYPE
{
	public static final int XMS_VOIP_PROTOCOL_H323           = 0x1; /*VoIP H323 protocol*/
	public static final int XMS_VOIP_PROTOCOL_SIP            = 0x2; /*VoIP SIP protocol*/
}

class XMS_ERROR_CODE_DEF{
	public static final int ACSPOSITIVE_ACK                	 = 0x01; //Success

	public static final int ACSERR_LOADLIBERR              	 = 0x01; //
	public static final int ACSERR_BADPARAMETER              = 0x02;
	public static final int ACSERR_NOSERVER                  = 0x03;
	public static final int ACSERR_MAXCONN_EXCEED            = 0x04;
	public static final int ACSERR_BADHDL                    = 0x05;
	public static final int ACSERR_FAILSEND                  = 0x06;
	public static final int ACSERR_LINKBROKEN                = 0x07;
	public static final int ACSERR_NOMESSAGE                 = 0x08;
	public static final int ACSERR_GETRESFAIL                = 0x09;
	public static final int ACSERR_NOSUPPORTCMD              = 0x0A;
	public static final int ACSERR_DEVICEERR                 = 0x0B;
	public static final int ACSERR_CTX_REGOVERRUN     		 = 0x0C;
	public static final int ACSERR_CTX_REG_NAMEEXIS          = 0x0D;
	public static final int ACSERR_CTX_UNREG_NOREG		     = 0x0E;
	public static final int ACSERR_CTX_TRAN_NODEST		     = 0x0F;
	public static final int ACSERR_CTX_TRAN_NOSRC		     = 0x10;
	public static final int ACSERR_CTX_LINK_FAIL             = 0x11;
	public static final int ACSERR_CTX_APPDATA_NODEST        = 0x12;
	public static final int ACSERR_CTX_APPDATA_NOSRC       	 = 0x13;
	public static final int ACSERR_NOTMASTER                 = 0x14;
	public static final int ACSERR_PUTTEXTINPIC_PARAMERROR   = 0x14;
	public static final int ACSERR_PUTTEXTINPIC_OPENPICFAIL  = 0x15;
	public static final int ACSERR_PUTTEXTINPIC_SAVEPICFAIL  = 0x16;
}

/* Board Device Params */
class XMS_BOARD_PARAM_TYPE
{
	public static final int BOARD_PARAM_GETBOARDINFO          = 0;
	public static final int BOARD_PARAM_SETFSK                = 1;
	public static final int BOARD_PARAM_SETFLASH              = 2;
	public static final int BOARD_PARAM_SETGTDFREQ            = 3;
	public static final int BOARD_PARAM_SETGTDTONE            = 4;
	public static final int BOARD_PARAM_SETTRUNKFLASH         = 5;
	public static final int BOARD_PARAM_SETGTGFREQ            = 6; //GTG Freq
	public static final int BOARD_PARAM_SETGTGTONE            = 7; //GTG Tone
	public static final int BOARD_PARAM_SETVSD                = 8; //VSD
	public static final int BOARD_PARAM_SET_ACTIVE_MEM_VAD    = 9; //ACTIVE MEM VAD
	public static final int BOARD_PARAM_SETCTCLK              = 10;     
	public static final int BOARD_PARAM_SET_MIN_VAD           = 11; //ACTIVE MEM VAD           
	public static final int BOARD_PARAM_SET_COMMON_CFG        = 12; //COMMON CFG 
	public static final int BOARD_PARAM_SET_RST_MASTER        = 13; //
}

/* Analog Trunk Device Params */
class XMS_ANALOGTRUNK_PARAM_TYPE
{
	public static final int ANALOGTRUNK_PARAM_UNIPARAM 		= 0;
	public static final int ANALOGTRUNK_PARAM_SETFLASH 		= 1;
	public static final int ANALOGTRUNK_PARAM_UNSETUNIPARAM = 2 ;//added by jerry for UnSet UniParam(id = 0 )....
	public static final int ANALOGTRUNK_PARAM_UNBINDVOC     = 3 ;//Added by jerry For UnBind Voc From AnalogTrunk
	public static final int ANALOGTRUNK_PARAM_READSN        = 4 ;//get TRUNK's SN
	public static final int ANALOGTRUNK_PARAM_GET_VOLTAGE   = 5 ;//get TRUNK's voltage
}

/* Media Device Params */
class XMS_VOC_PARAM_TYPE
{
	public static final int VOC_PARAM_UNIPARAM     = 0;// set universal vocice parameters.
	public static final int VOC_PARAM_BREAKEN_CALL = 1;// added by jerry for keyInterrupet .08.02.19
	public static final int VOC_PARAM_3GFAXTONE    = 2;// added by jerry for 3G FaxTone Eanble or Disable 08.02.20
}

class XMS_MEDIA_IO_TYPE
{		
	public static final int XMS_IO_TYPE_DTMF                = 1;
	public static final int XMS_IO_TYPE_MR2F                = 2;
	public static final int XMS_IO_TYPE_MR2B                = 3;
	public static final int XMS_IO_TYPE_GTG                 = 4;
	public static final int XMS_IO_TYPE_GTD                 = 4;
	public static final int XMS_IO_TYPE_FSK                 = 5;
	public static final int XMS_IO_TYPE_DPD                 = 6;
	public static final int XMS_IO_TYPE_PVD                 = 7;
	public static final int XMS_IO_TYPE_MSK                 = 8;
	public static final int XMS_IO_TYPE_VSD                 = 9;
	public static final int XMS_IO_TYPE_MSKREND             = 10;
	public static final int XMS_IO_TYPE_DRS                 = 11;
}

/* CAS Device Params */
class XMS_CAS_PARAM_TYPE
{
	public static final int CAS_PARAM_UNIPARAM 				= 0;
	public static final int CAS_PARAM_MFCTYPE  				= 1;
	public static final int CAS_PARAM_CALLTYPE      		= 2;    //0 all (default)  1 ��λ���� CmdParamData_CAS->m_u8CallType;
	public static final int CAS_PARAM_APPENDCALLEE  		= 3;    //CmdParamData_CAS->m_u8AppendCallee һ��һλ
}

/* Analog User Device Params */
class XMS_ANALOGUSER_PARAM_TYPE
{
	public static final int ANALOGUSER_PARAM_UNIPARAM      	 = 0;	
	public static final int ANALOGUSER_PARAM_UNBINDVOC     	 = 3; //Added by jerry For UnBind Voc From AnalogUser
	public static final int ANALOGUSER_PARAM_READSN          = 4; //get AnalogUser's SN
	public static final int ANALOGUSER_PARAM_GET_VOLTAGE     = 5; //Get AnalogUser's voltage
}

class PUT_TEXTINPIC_FONTTYPE	     /* .\\PutTextInPicture.ini */
{
	public static final int FONTTYPE_SIMSUN      			 = 0;    /*����&������*/
	public static final int FONTTYPE_MICROSS				 = 1;            /*Microsoft Sans Serif*/
}

class PUT_TEXTINPIC_TYPE
{
	public static final int PUT_TYPE_TEXT            		 = 1;
	public static final int PUT_TYPE_PICTURE         		 = 2;
}

/* VoIP Media Capabilities */
class XMS_VOIP_MEDIA_CAPS
{
	// audio media
	public static final int VOIP_MEDIA_AUDIO_PCMU		= 0x00;	// pcm u-law
	public static final int VOIP_MEDIA_AUDIO_PCMA		= 0x01;	// pcm a-law
	public static final int VOIP_MEDIA_AUDIO_G723		= 0x02;	// g.723
	public static final int VOIP_MEDIA_AUDIO_G729		= 0x03;	// g.729
	public static final int VOIP_MEDIA_AUDIO_T38		= 0x04;	// t.38/rtp
	public static final int VOIP_MEDIA_AUDIO_AMR		= 0x05;	// amr-nb
	// video media
	public static final int VOIP_MEDIA_VIDEO_H261		= 0x80;	// h.261
	public static final int VOIP_MEDIA_VIDEO_H263		= 0x81;	// h.263
	public static final int VOIP_MEDIA_VIDEO_H263P		= 0x82;	// h.263+
	public static final int VOIP_MEDIA_VIDEO_MPEG4		= 0x83;	// mpeg-4 visual
	public static final int VOIP_MEDIA_VIDEO_H264		= 0x84;	// h.264

	public static final int VOIP_MEDIA_IMAGE_T38		= 0xF0;	// t.38/udptl
}

class XMS_FAX_PARAM_TYPE
{
	public static final int FAX_PARAM_FAXHEADER    = 0;
	public static final int FAX_PARAM_ADDFAXFILE   = 1;
	public static final int FAX_PARAM_ECM	       = 2;
	public static final int FAX_PARAM_MODE_TYPE    = 3;
	public static final int FAX_PARAM_BPS	       = 4;
	public static final int FAX_PARAM_FAXHEADEREX  = 5;
}

/* ISDN Device Param type*/
class XMS_ISDN_PARAM_TYPE
{
	public static final int ISDN_PARAM_ORINUMBER         = 0;
	public static final int ISDN_PARAM_CALLTYPE          = 1;
	public static final int ISDN_PARAM_APPENDCALLEE      = 2;
	public static final int ISDN_PARAM_CALLOUT           = 3;
	public static final int ISDN_PARAM_DISCONNECTREASON  = 4;
	public static final int ISDN_PARAM_LOW_LEVEL         = 5;
	public static final int ISDN_PARAM_UUI               = 6;
}

/* Conference Device Params */
class XMS_CONF_PARAM_TYPE
{
	public static final int CONF_PARAM_UNIPARAM = 0;
	public static final int CONF_PARAM_VAD      = 1;
}

/* Analog EM Device Params */
class XMS_AEM_PARAM_TYPE
{
	public static final int XMS_AEM_PARAM_SND_M_SIGNAL = 1; //send M msg to endpoint
}

/* MediaEx Device Params */
class XMS_MEDIAEX_PARAM_TYPE
{
	public static final int MEDIAEX_PARAM_INPUT 	= 0;
	public static final int MEDIAEX_PARAM_OUTPUT	= 1;
}

/* VoIP Device Params */
class XMS_VOIP_PARAM_TYPE
{
	public static final int VOIP_PARAM_ACCESS 				= 0;
	public static final int VOIP_PARAM_VOICE 				= 1;
	public static final int VOIP_PARAM_RTPSESSION 			= 2;
	public static final int VOIP_PARAM_RTPADDR 				= 3;
	public static final int VOIP_PARAM_RTCPADDR 			= 4;
	public static final int VOIP_PARAM_RTPCODEC 			= 5;
	public static final int VOIP_PARAM_RTPMIXER 			= 6;
	public static final int VOIP_PARAM_RTPWANIP 			= 7;
	public static final int VOIP_PARAM_PAYLOAD 				= 8;
	public static final int VOIP_PARAM_MEDIAINFO 			= 9;
	public static final int VOIP_PARAM_RTPOPEN 				= 10;
	public static final int VOIP_PARAM_SIP_USER_AGENT 		= 11;
	public static final int VOIP_PARAM_CALL_DIVERSION_INFO 	= 12;
}

/* Analog HIZ Device Params */
class XMS_ANALOGHIZ_PARAM_TYPE
{
	public static final int ANALOGHIZ_PARAM_SET_SW_MODE   = 0 ;//set Switch Mode,replace by XMS_DIGREC_PARAM_UNI On Digital Module,reference to XMS_DIGREC_PARAM_TYPE
	public static final int ANALOGHIZ_PARAM_VOLTAGE       = 1 ;//Set voltage
	public static final int ANALOGHIZ_PARAM_READSN        = 4 ;//get HIZ's SN
	public static final int ANALOGHIZ_PARAM_GET_VOLTAGE   = 5 ;//get HIZ's voltage
}

/* Analog VOC2 Device Params */
class XMS_ANALOGVOC2_PARAM_TYPE
{
	public static final int ANALOGVOC2_PARAM_NULL          = 1 ;//RESERVE
	public static final int ANALOGVOC2_PARAM_READSN        = 4 ;//get VOC2 SN
	public static final int ANALOGVOC2_PARAM_GET_VOLTAGE   = 5 ;//get HIZ's voltage
}

/* Analog VOC4 Device Params */
class XMS_ANALOGVOC4_PARAM_TYPE
{
	public static final int ANALOGVOC4_PARAM_NULL          = 1 ;//RESERVE
	public static final int ANALOGVOC4_PARAM_READSN        = 4 ;//get VOC4 SN
	public static final int ANALOGVOC4_PARAM_GET_VOLTAGE   = 5 ;//get HIZ's voltage
}

/* Analog MEG Device Params */
class XMS_AMEG_PARAM_TYPE
{
	public static final int XMS_AMEG_PARAM_SEND_RING_SIGNAL = 1; // send ring msg to meg
	public static final int XMS_AMEG_PARAM_GET_SN           = 4; // get param for sn
	public static final int XMS_AMEG_PARAM_GET_VOLTAGE      = 5; // get param for voltage
}

/* Analog EM Device Params */
class XMS_ANALOGEM_PARAM_TYPE
{
	public static final int ANALOGEM_PARAM_NULL             = 1; //RESERVE
	public static final int ANALOGEM_PARAM_READSN           = 4; //get EM's SN
	public static final int ANALOGEM_PARAM_GET_VOLTAGE      = 5; //get EM's voltage
}

/* 324 Config Params*/
class XMS_324_PARAM_TYPE
{
	public static final int H324_PARAM_UNIPARAM  = 0x0;
	public static final int H324_PARAM_MEDIA     = 0x1;
	public static final int H324_PARAM_CH	     = 0x2;
	public static final int H324_PARAM_MIXER	 = 0x3;
	public static final int H324_PARAM_TCS		 = 0x4;
}

/*Digtial machine Record param type*/
class XMS_DIGREC_PARAM_TYPE
{
	public static final int XMS_DIGREC_PARAM_UNI         = 0x0;      //set switch mode param type
	public static final int XMS_AREC_PARAM_SET_VOLTAGE   = 0x01;      //set analog rec module valtage param type
}


class MD_CFG_TYPE
{
	public static final int MD_CFG_TYPE_NON_INDEX      = 0x00;
	public static final int MD_CFG_TYPE_INDEX          = 0x01;
}


/*XMS_324_CMD_SESSION_TYPE*/
class XMS_324_CMD_SESSION_TYPE
{	
	public static final int XMS_324_CMD_TYPE_NORMAL_START			= 0x0;	/* start session in normal mode */
	public static final int XMS_324_CMD_TYPE_MONITOR_START          = 0x1;	/* start session in monitor mode */
	public static final int XMS_324_CMD_TYPE_STOP                   = 0x2;	/* stop session */
	public static final int XMS_324_CMD_TYPE_RESET					= 0x3;	/* reset session */
}

/*XMS_324_CMD_CTRL_TYPE*/
class XMS_324_CMD_CTRL_TYPE
{
	public static final int XMS_324_CMD_TYPE_SETMET					= 0x1;	/* set multiplex entry table */
	public static final int XMS_324_CMD_TYPE_OLC					= 0x2;	/* open rx/tx logical channel */
	public static final int XMS_324_CMD_TYPE_CLC					= 0x3;	/* close logical channel */
	public static final int XMS_324_CMD_TYPE_UII					= 0x4;	/* Send user input */	
	public static final int XMS_324_CMD_TYPE_VFU					= 0x5;	/* send video fast update */
}

/*XMS_324_EVT_TYPE*/
class XMS_324_EVT_TYPE
{
	public static final int XMS_324_EVT_TYPE_START				    = 0x1;	/* start session event */
	public static final int XMS_324_EVT_TYPE_STOP				    = 0x2;	/* stop session event */
	public static final int XMS_324_EVT_TYPE_RESET					= 0x3;	/* reset session event */
	public static final int XMS_324_EVT_TYPE_UII					= 0x4;	/* receive user input event */
	public static final int XMS_324_EVT_TYPE_SIG_PDU                = 0x5;	/* receive h.245 signal message event */
	public static final int XMS_324_EVT_TYPE_OLC					= 0x6;	/*open logical channel event*/
	public static final int XMS_324_EVT_TYPE_CLC					= 0x7;	/*close logical channel event*/
}

/* XMS_324_STOP_CODE */
class XMS_324_STOP_CODE
{
	public static final int XMS_324_STOP_CODE_UNKOWN				= 0x0;
	public static final int XMS_324_STOP_CODE_UPERSTOP				= 0x1;
	public static final int XMS_324_STOP_CODE_LOWERSTOP				= 0x2;
	public static final int XMS_324_STOP_CODE_HOSTSTOP				= 0x3;	
	public static final int XMS_324_STOP_CODE_REMOTESTOP			= 0x4;
}

/* XMS_324_AL_TYPE */
class XMS_324_AL_TYPE
{
	public static final int XMS_324_AL1_FRAMED						= 0x1;	/* AL1 framed */
	public static final int XMS_324_AL1_NOTFRAMED					= 0x2;	/* AL1 not framed */
	public static final int XMS_324_AL2_WITHOUTSN					= 0x3;	/* AL2 */
	public static final int XMS_324_AL2_SN							= 0x4;	/* AL2 with sn */
	public static final int XMS_324_AL3								= 0x5;	/* AL3 */
}

/* encode type define for 3G324M module */
/*  encode type */
class XMS_ENCODE_TYPE
{
	public static final int XMS_324_LC_CTRL							= 0x0;
	public static final int XMS_324_LC_AUDIO_G723					= 0x08;
	public static final int XMS_324_LC_AUDIO_AMR					= 0x14;
	public static final int XMS_324_LC_VIDEO_H263					= 0x83;
	public static final int XMS_324_LC_VIDEO_MPEG4					= 0x85;
}

//////////////////////////////////////////////////////////////////
/*XMS_SCCP_CMD_TYPE*/
class XMS_SCCP_CMD_TYPE
{
	public static final int XMS_SCCP_CMD_SETRAWDATA            = 0x1;	
}

/*EXT_ENABLE_TYPE*/
class EXT_ENABLE_TYPE
{
	public static final int EXT_ENABLE_DPD                     = 0x01;
	public static final int EXT_ENABLE_PVD                     = 0x02;	
	public static final int EXT_ENABLE_MSK                     = 0x04;
	public static final int EXT_ENABLE_VSD                     = 0x08;
}

/*DRS_EVT_MASK*/
class DRS_EVT_MASK
{
	public static final int DRS_EVT_HOOK_MASK                  = 0x01;
	public static final int DRS_EVT_CONNECT_MASK               = 0x02;	
	public static final int DRS_EVT_VAD_MASK                   = 0x04;
}

/*XMS_RTPX_PARAM_TYPE*/
class XMS_RTPX_PARAM_TYPE
{
	public static final int XMS_RTPX_PARAM_INPUT               = 0x0;
	public static final int XMS_RTPX_PARAM_OUTPUT              = 0x1;
	public static final int XMS_RTPX_PARAM_MIXER		       = 0x2;
	public static final int XMS_RTPX_PARAM_ADDR				   = 0x3;
	public static final int XMS_RTPX_PARAM_INPUT_A             = 0x4;
	public static final int XMS_RTPX_PARAM_OUTPUT_A            = 0x5;
	public static final int XMS_RTPX_PARAM_MIXER_A		       = 0x6;
	public static final int XMS_RTPX_PARAM_ADDR_A			   = 0x7;
}

/*XMS_DRS_SWITCH_TYPE*/
class XMS_DRS_SWITCH_TYPE
{ 
	public static final int XMS_DRS_SWITCH_AVAYA                = 0x01;
	public static final int XMS_DRS_SWITCH_SIMENZ               = 0x02;
	public static final int XMS_DRS_SWITCH_TADIRANT             = 0x03;
	public static final int XMS_DRS_SWITCH_ERRICSION            = 0x04;
	public static final int XMS_DRS_SWITCH_TOSHIBA              = 0x05;
}

class XMS_CAP_DIRECTION
{
	public static final int XMS_CAP_DIR_RX    					= 1;
	public static final int XMS_CAP_DIR_TX    					= 2;
	public static final int XMS_CAP_DIR_RXTX   					= 3;
}

/*Event filter mask*/
class XMS_IOEVT_MASK_TYPE
{
	public static final int XMS_IOEVT_MASK_GTD              = 0x0001;
	public static final int XMS_IOEVT_MASK_FSK              = 0x0002;
	public static final int XMS_IOEVT_MASK_MR2F             = 0x0004;
	public static final int XMS_IOEVT_MASK_MR2B             = 0x0008;
}

class XMS_MEDIA_ERR_CODE
{
	public static final int XMS_ERR_CODE_OK                   = 0x00;
	public static final int XMS_ERR_CODE_APPSTOP              = 0x01;
	public static final int XMS_ERR_CODE_GTD                  = 0x02;
	public static final int XMS_ERR_CODE_OPENFILE_FAILED      = 0x03;
	public static final int XMS_ERR_CODE_WREADFILE_FAILED     = 0x04;
	public static final int XMS_ERR_CODE_CH_MISSING           = 0x05;
	public static final int XMS_ERR_CODE_EXE_FAILED           = 0x06;	
	public static final int XMS_ERR_CODE_BUILD_INDEX_OK       = 0x07;
	public static final int XMS_ERR_CODE_PLAY_QUEUE_FULL      = 0x08;
	public static final int XMS_ERR_CODE_3G_AUDIO_OK          = 0x09;
	public static final int XMS_ERR_CODE_3G_VIDEO_OK          = 0x0A;
	public static final int XMS_ERR_CODE_BUILD_INDEX_FAILED   = 0x0B;
	public static final int XMS_ERR_SYSTEM_OVERLOAD           = 0x0C;
}

/*It will be replaced by XMS_CLK_STATE_TYPE later from V3.0.0*/
class XMS_CLK_RS_STATE_TYPE
{
	public static final int XMS_CLK_RS_STATE_MASTER_CLOCK_RS_SET       = 0x01;    /*Set Master Clock Ref Source*/
	public static final int XMS_CLK_RS_STATE_MASTER_CLOCK_RS_RELEASE   = 0x02;    /*Release Master Clock Ref Source*/
}


class XMS_CLK_STATE_TYPE
{
	public static final int XMS_CLK_STATE_SET               = 0x01;    /*Set master/slave clock */
	public static final int XMS_CLK_STATE_RELEASE           = 0x02;    /*Release master/slave clock*/
}

class XMS_VOIP_IO_TYPE
{
	public static final int XMS_IO_TYPE_VOIP_H245UII        = 1;  /* VoIP H.245 UserInputIndication Event */
	public static final int XMS_IO_TYPE_VOIP_SIPINFO        = 2;  /* VoIP SIP INFO Event */
	public static final int XMS_IO_TYPE_VOIP_RTPDTMF        = 3;  /* VoIP RTP DTMF Event */
	public static final int XMS_IO_TYPE_VOIP_RTPTONE        = 4;  /* VoIP RTP TONE */
	public static final int XMS_IO_TYPE_VOIP_FAXSTART       = 5;  /* VoIP start fax mode (t.38 or t.30 pass-thru) */
	public static final int XMS_IO_TYPE_VOIP_FAXSTOP        = 6;  /* VoIP stop fax mode(t.38 or t.30 pass-thru) */
	public static final int XMS_IO_TYPE_VOIP_REGSTATE       = 7;  /* VoIP Registration State */
	public static final int XMS_IO_TYPE_VOIP_REGREQUEST     = 8;  /* VoIP Registration Request */
	public static final int XMS_IO_TYPE_VOIP_REGRESPONSE    = 9;  /* VoIP Registration Response */
	public static final int XMS_IO_TYPE_VOIP_TRANSFER       = 10; /* VoIP Device Transfer */ 
	public static final int XMS_IO_TYPE_VOIP_SIPREG         = 11; /* VoIP SIP Register */
	public static final int XMS_IO_TYPE_VOIP_SIPUNREG       = 12; /* VoIP SIP Unregister */
	public static final int XMS_IO_TYPE_VOIP_REFER			= 13; /* Voip SIP Refer */
	public static final int XMS_IO_TYPE_VOIP_REFERRESPONSE	= 14; /* Voip SIP Refer Response */
	public static final int XMS_IO_TYPE_VOIP_FORWARD		= 15; /* Voip SIP Forward call */
	public static final int XMS_IO_TYPE_VOIP_REFER_NOTIFY	= 16; // VoIP SIP Send Refer Notify to Subscribe
	public static final int XMS_IO_TYPE_VOIP_CALLMODIFY		= 17; /* VoIP SIP Call Modified */
}

class XMS_DCH_IO_TYPE
{
	public static final int XMS_IO_TYPE_DCH_I_FRAME         = 1;
	public static final int XMS_IO_TYPE_DCH_UI_FRAME        = 2;
	public static final int XMS_IO_TYPE_DCH_DEBUG           = 3;
}

class XMS_LINESIDEE1_IO_TYPE
{
	public static final int XMS_IO_TYPE_LINESIDEE1          = 12;
}

class XMS_ANALOG_INTERFACE_STATE
{
	public static final int XMS_ANALOG_USER_CH_OFFHOOK             = 0;
	public static final int XMS_ANALOG_USER_CH_ONHOOK              = 1;	
	public static final int XMS_ANALOG_USER_CH_FLASH               = 2;


}

class XMS_ANALOG_INTERFACE_STATE2
{
	public static final int XMS_ANALOG_TRUNK_CH_RING               = 0; 
	public static final int XMS_ANALOG_TRUNK_CH_POSITEX_POLARITY   = 1; 
	public static final int XMS_ANALOG_TRUNK_CH_NEGATIVE_POLARITY  = 2; 
	public static final int XMS_ANALOG_TRUNK_CH_LOOPDROP           = 3;
	public static final int XMS_ANALOG_TRUNK_CH_NOLOOP             = 4; 
	public static final int XMS_ANALOG_TRUNK_CH_FLASH              = 8;
}

class XMS_SIG_RAWDATA_EVT_TYPE
{
	public static final int XMS_SIG_RAWDATA_EVT_BASE         = 0xFF00;
}

class ACS_MASTER_STATE
{
	public static final int ACS_STATE_SLAVE                  = 0x0;
	public static final int ACS_STATE_MASTER                 = 0x1;
}

class ACS_WORK_STATE
{
	public static final int ACS_STATE_WORK_FAILURE           = 0x0; 
	public static final int ACS_STATE_WORKING                = 0x1;
}

class XMS_SS7_SN_STATUS
{
	public static final int XMS_SN_PAUSE      = 0x01; // Pause
	public static final int XMS_SN_RESUME     = 0x02; // Resume
	public static final int XMS_SN_CONG       = 0x03; // Network Congested
	public static final int XMS_SN_RMTUSRUNAV = 0x04; // Remote User Unavailable
	public static final int XMS_SN_RSTBEG     = 0x05; // Restart Begins
	public static final int XMS_SN_RSTEND     = 0x06; // Restart Ends
	public static final int XMS_SN_STPCONG    = 0x07; // Stop Network Congestion
	public static final int XMS_SN_RESTRICT   = 0x08; // Restrict
	public static final int XMS_SN_LNK_CHANGE = 0x09; // Link status changed
}

class XMS_SS7_MSG_TYPE
{
	public static final int XMS_SS7_MSG_DATA   = 0x01;
	public static final int XMS_SS7_MSG_CMD    = 0x02;
	public static final int XMS_SS7_MSG_STATUS = 0x03;
}

class XMS_SS7_USER_TYPE
{
	public static final int XMS_SS7_USER_TYPE_SCCP = 0x03;
	public static final int XMS_SS7_USER_TYPE_TUP  = 0x04;
	public static final int XMS_SS7_USER_TYPE_ISUP = 0x05;
}

class XMS_SS7_LINK_TYPE
{
	public static final int XMS_SS7_LINK_TYPE_ITU  = 0x02;
	public static final int XMS_SS7_LINK_TYPE_CHINA= 0x04;
}

class XMS_3GVCONF_ERROR_CODE_DEF
{
	public static final int XMS_ERROR_DEVTYPEERROR 	= 0;		//
	public static final int XMS_ERROR_REJOIN3GVCONF = 1;		//
	public static final int XMS_ERROR_GETRESFAIL 	= 2;		//
	public static final int XMS_ERROR_OVERFLOW 		= 3;		//
	public static final int XMS_ERROR_NONEVISIBLE 	= 4;		//
	public static final int XMS_ERROR_OVERFLOWPR 	= 5;		//
	public static final int XMS_ERROR_3GVCONFSTOP 	= 255;		//
}

class XMS_DRS_CALL_DIRECT_DEF
{
	public static final int XMS_DRS_CALL_DIRECT_CALL_IN           = 0;
	public static final int XMS_DRS_CALL_DIRECT_CALL_OUT          = 1;
}



