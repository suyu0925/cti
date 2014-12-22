unit DJAcsDataDef;

interface
uses
  SysUtils, Variants, Messages, Windows;

const  ACS_MAX_CALL_NUM             = 32;
const  ACS_SIGDATA_MAX_LEN          = 300;
const  ACS_MAX_IO_SIZE              = 2048;
const  ACS_LOCALID_MAX_LEN          = 20;
const  ACS_REMOTEID_MAX_LEN         = 20;
const  ACS_MAX_DECODER_CFG_LEN      = 200;
const  XMS_MAX_REGNAME_LEN          = 16;
const  ACS_MAX_H245_SIG_PDU_LEN     = 4000;
const  ITP_VOIP_MONDATA_MAX         = 1024;
const  MAX_PATH                     = 260;
const  ACS_MAX_FILE_NAME_LEN        = 128;
const  XMS_MAX_PLAY_QUEUE_NUM       = 255;
const  XMS_MAX_IDNEX_TABLE_NUM      = 1024;
const	 ITP_MAX_STREAM_DATA_LENGTH		= 4000;
const  ACS_IOEVT_MASK_ALL           = $FFFF;

const   COUNTRY_BEGIN  = $00;

const   CHINA      = $01;
const   KOREA      = $02;
const   INDIA      = $03;
const   VIETNAM    = $04;

const   COUNTRY_END   = $05;

const MAX_CAPS_NUM    = 4;
const MAX_DECODER_CFG_INFO = 128;


const  ACS_SNAPSHOT_ALL                  = $0;
const  ACS_SNAPSHOT_INTERFACE            = $1;
const  ACS_SNAPSHOT_VOC                  = $2;
const  ACS_SNAPSHOT_CTBUS                = $3;
const  ACS_SNAPSHOT_VOIP                 = $4;
const  ACS_SNAPSHOT_CONFERENCE           = $5;
const  ACS_SNAPSHOT_VIDEO                = $6;

const  T6_Encode                         = 2;


Type
  ITP_GUID_tag = record
  m_u8ModuleType : Byte;  //模块类型
	m_u8MainFuncId : Byte;  //主功能ID
	m_u8SubFuncId  : Byte;  //子功能ID
	m_u8UnitId     : Byte;  //单元ID
	m_u16ChanId    : Word;  //通道ID
end;

Type
  PKG_HEAD_STRUCT = record
	m_u8PkgFlag   : byte;	// 包标志: 0xa5,0x5a
	m_u8PkgExtend : byte;	// 包扩展位
	
	m_u16DataLen  : Word;	//不定长数据长度
  ITP_GUID      : ITP_GUID_tag;
	m_u16Reserve  : Word; //保留字段
end;

Type
  CallID_t = record
  m_s32FlowType:Integer;
  m_s32FlowChannel:Integer;
end;

Type
  DeviceID_t = record
  m_s16DeviceMain:Smallint;
  m_s16DeviceSub:Smallint;
  m_s8ModuleID:Shortint;
  m_s8MachineID:Shortint;
  m_s16ChannelID:Smallint;
  m_s16DeviceGroup:Smallint;
  m_Rfu2:Array[0..1] of char;
  m_CallID:CallID_t;
end;

Type
  ShortArr = array[0..31] of char;
  ServerID_t = record
  m_s8ServerIp : ShortArr;
  m_u32ServerPort: Cardinal;
  m_s8UserName : ShortArr;
  m_s8UserPwd : ShortArr;
end;

Type
   PrivateData_t = record
   m_u32DataSize : Cardinal;
end;

Type
  CAS_CalledTableDesc_t=record
  m_u8NumHeadLen:Byte;
  m_u8NumHead:Array[0..13] of Byte;
  m_u8NumLen:Byte;
end;

Type
  CmdParamData_CAS_t = record
  m_VocDevID:DeviceID_t;
  m_u8CalledTableCount:Byte;
  m_Rfu1:Array[0..2] of Byte;
  m_CalledTable:Array[0..15] of CAS_CalledTableDesc_t;
  m_u8CalledLen:Byte;
  m_u8CalledTimeOut:Byte;
  m_u8NeedCaller:Byte;
  m_u8AreaCodeLen:Byte;
  m_u8KA:Byte;
  m_u8KD:Byte;
  m_u8ControlMode:Byte;
  m_u8CountryCode:Byte;
  m_u8CallType:Byte;
  m_u8AppendCallee:Byte;
  m_u8Rfu:Array[0..5] of Byte;
end;

Type
    CmdParamData_AnalogTrunk_t=record
    m_u16CallInRingCount:Word;
    m_u16CallInRingTimeOut:Word;
end;

Type
    CmdParamData_AnalogUser_t=record
    m_u8CallerIdOption:Byte;
    m_u8RingCadenceType:Byte;
    m_u8CallOutRingTimeOut:Byte;
    m_u8Rfu1:Byte;
    m_u8Rfu2:Array[0..11] of Byte;
end;

Type
    Acs_MediaProc_Data=record
    m_s32AcsEvtState:integer;
    m_s32AcsEvtErrCode:integer;
    m_u8TaskID:Byte;
    m_u8GTD:Byte;
    m_s8Rfu:Array[0..1] of char;
    m_u32CurFileIndex:Cardinal;
    m_u32CurFilePos:Cardinal;
    m_PrivData:PrivateData_t;
end;

Type
  Acs_Evt_t=record
  m_s32AcsHandle:Integer;
  m_DeviceID:DeviceID_t;
  m_s32EvtSize:Integer;
  m_s32EventType:Integer;
  m_u32EsrParam:Integer;
end;

Type
  Acs_Dev_List_Head_t=record
  m_s32DeviceMain:Integer;
  m_s32ModuleID:Integer;
  m_s32DeviceNum:Integer;
end;

Type
  Acs_UniFailure_Data=record
  m_s32AcsEvtState:Integer;
  m_s32AcsEvtErrCode:Integer;
end;

Type
  CmdParamData_GtdFreq_t=record
  m_u16Freq_Index:Word;
  m_u16Freq_Coef: Word;
end;

Type
  ControlRecord_t=record
  m_u32ControlType:Cardinal;
  m_u32StepSize:Cardinal;
  m_u32DelayStop:Cardinal;
end;

Type
  CmdParamData_GtdProtoType_t=record
  m_u16GtdID:Word;
  m_u16Freq_Mask:Word;
  m_u16Amp_Threshold:Word;
  m_u16Envelope_Mode:Word;
  m_u16Repeat_Count:Word;
  m_u16Min_On_Time1:Word;
  m_u16Max_On_Time1:Word;
  m_u16Min_Off_Time1:Word;
  m_u16Max_Off_Time1:Word;
  m_u16Min_On_Time2:Word;
  m_u16Max_On_Time2:Word;
  m_u16Min_Off_Time2:Word;
  m_u16Max_Off_Time2:Word;
end;

Type
  Acs_CallControl_Data=record
  m_s32AcsEvtState:Integer;
  m_s32AcsEvtErrCode:Integer;
  m_s32CallClearCause:Integer;
  m_u8CallingCategory:Byte;
  m_u8CallingAddressIndicator:Byte;
  m_u8CalledAddressIndicator:Byte;
  m_s8Rfu1:ShortInt;
  m_s8CallingNum:Array[0..31] of char;
  m_s8CalledNum:Array[0..31] of char;
  m_u8DRSCallDirectFlag:Byte;
  m_s8Rfu2:Array[0..30] of Shortint;
  m_PrivData:PrivateData_t;
end;

Type
  Acs_GeneralProc_Data=record
  m_s32AcsEvtState:Integer;
  m_s32AcsEvtErrCode:Integer;
  m_s32DeviceState:Integer;
  m_s32Resrv:Integer;
  m_PrivData:PrivateData_t;
end;

Type
  Acs_IO_Data=record
  m_s32AcsEvtState:integer;
  m_s32AcsEvtErrCode:integer;
  m_u16IoType:Word;
  m_u16IoDataLen:Word;
end;

Type
  VocInputControlParam_t=record
  m_u8AgcEnable:Byte;
  m_u8AgcMode:Byte;
  m_u8EcEnable:Byte;
  m_u8EcRefType:Byte;
  m_u8VadEnable:Byte;
  m_u8TadEnable:Byte;
  m_u8NrEnable:Byte;
  m_u8Reserved:Byte;
  m_u16FixGain:Word;
  m_u16EcRefCh:Word;
  m_u32Reserved:Cardinal;
end;

Type
  MixerControlParam_t=record
  m_u8SRC1_Ctrl:Byte;
  m_u8SRC2_Ctrl:Byte;
  m_u16SRC_ChID1:Word;
  m_u16SRC_ChID2:Word;
  m_u8Video:Byte;
  m_s8Rfu:Shortint;
end;

Type
  VocOutputControlParam_t=record
  m_u8AgcEnable:Byte;
  m_u8AgcMode:Byte;
  m_u8OutputType:Byte;
  m_u8Reserved:Byte;
  m_u16FixGain:Word;
  m_s8Rfu:Array[0..1] of Shortint;
  m_MixerControl:MixerControlParam_t;
end;

Type
  VocGtdControlParam_t=record
  m_u8ChannelEnable:Byte;
  m_u8DTMFEnable:Byte;
  m_u8MR2FEnable:Byte;
  m_u8MR2BEnable:Byte;
  m_u8GTDEnable:Byte;
  m_u8FSKEnable:Byte;
  m_u8EXTEnable:Byte;
  m_u8Reserved:Byte;
  m_u8GTDID:Array[0..7] of Byte;
end;

Type
  CmdParamData_Voice_t=record
  m_u8InputCtrlValid:Byte;
  m_u8PlayGainMode:Byte;
  m_u16PlayFixGain:Word;
  m_VocInputControl: VocInputControlParam_t;
  m_u8OutputCtrlValid:Byte;
  m_s8Rfu2:Array[0..2] of char;
  m_VocOutputControl: VocOutputControlParam_t;
  m_u8GtdCtrlValid:Byte;
  m_s8Rfu3:Array[0..2] of char;
  m_VocGtdControl:VocGtdControlParam_t;
end;

Type
  PlayProperty_t=record
  m_u8TaskID:Byte;
  m_u8SrcMode:Byte;
  m_u8DecodeType:Byte;
  m_s8Rfu1:char;
  m_u32MaxSize:Cardinal;
  m_u32MaxTime:Cardinal;
  m_u32StopMode:Cardinal;
  m_u32StopCode:Cardinal;
  m_u16FileOffset:Word;
  m_u16PlayType:Word;
  m_u16PlayIndex:Word;
  m_s8PlayContent:Array[0..127] of char;
  m_u16FileSubOffset:Word;
end;

Type
  ControlPlay_t=record
  m_u16ControlType:Word;
  m_u16StepSize:Word;
  m_u16TuneType:Word;
  m_u16SpeedSize:Word;
end;

Type
  RecordProperty_t=record
  m_u32MaxSize:Cardinal;
  m_u32MaxTime:Cardinal;
  m_u8EncodeType:Byte;
  m_u8SRCMode:Byte;
  m_u8StopMode:Byte;
  m_u8StopCode:Byte;
  m_s8IsMixEnable:Byte;
  m_u8TaskID:Byte;
  m_MixerControl:MixerControlParam_t;
  m_s8IsAppend:Shortint;
  m_s8FileName:Array[0..259] of char;
  m_s8Rfu2:Shortint;
end;

Type
  CmdParamData_Conf_t=record
  m_u8InputOpt:Byte;
  m_u8OutputOpt:Byte;
  m_u8Rfu:Array[0..1] of Byte;
end;

Type
  CSPPlayDataInfo_t=record
  m_u16DataLen:Word;
  m_u8DataType:Byte;
  m_u8TaskID:Byte;
end;

Type
  RecordCSPProperty_t=record
  m_u8EncodeType:Byte;
  m_u8SRCMode:Byte;
  m_u16PacketLen:Word;
  m_u8CSPRecType:Byte;
  m_u8StopMode:Byte;
  m_u8StopCode:Byte;
  m_s8IsMixEnable:char;
  m_MixerControl:MixerControlParam_t;
  m_u8IsVADEnable:Byte;
  m_s8Rfu1:Array[0..2] of char;
end;

Type
  Play3gppProperty_t=record
  m_u8TaskID:Byte;
  m_u8SrcMode:Byte;
  m_u8DecodeType:Byte;
  m_u8Audio_tracks:Char;
  m_u8AmrFrameType:Char;
  m_u8AudioNoDecode:Byte;
  m_u8Rfu1:Array[0..1] of char;
  m_u32MaxTime:Cardinal;
  m_u32StopMode:Cardinal;
  m_u32StopCode:Cardinal;
  m_u16TimeOffset:Word;
  m_u16PlayType:Word;
  m_u16PlayIndex:Word;
  m_s16Rfu2:Smallint;
  m_s8PlayContent:Array[0..127] of char;
  m_u8VideoFrameRate:Byte;
  m_u8VideoDecode_Type:Byte;
  m_u8VideoHigh:Byte;
  m_u8VideoWidth:Byte;
  m_u32VideoMaxTime:Cardinal;
  m_u16VideoTimeOffset:Word;
  m_u16VideoPlayType:Word;
  m_u16VideoPlayIndex:Word;
  m_u8VideoTaskID:Byte;
  m_u8MediaType:Byte;
  m_s8VideoPlayContent:Array[0..127] of char;
end;

Type
  Control3gppPlay_t=record
  m_u16ControlType:Word;
  m_u16StepTime:Word;
  m_u16TuneType:Word;
  m_u16SpeedSize:Word;
  m_u8MediaType:Byte;
  m_u8Reserv1:Array[0..2] of char;
end;

Type
  Record3gppProperty_t=record
  m_u32MaxTime:Cardinal;
  m_u8StopMode:Byte;
  m_u8StopCode:Byte;

  m_s8IsAppend:Char;
  m_u8AudioEncodeType:Byte;
  m_u8AudioSRCMode:Byte;
  m_u8AudioTracks:char;
  m_u16AudioMaxBitRate:Word;
  m_u16AudioAverageBitRate:Word;
  m_u8MediaType:char;
  m_s8AudioIsMixEnable:char;
  m_AudioMixerControl:MixerControlParam_t;

  m_u8VideoEncodeType:Byte;
  m_u8VideoFrameRate:Byte;
  m_u16VideoWidth:Word;
  m_u16VideoHeight:Word;
  m_u16VideoMaxBitRate:Word;
  m_u16VideoAverageBitRate:Word;
  m_Rfu2:Byte;
  m_s8VideoIsMixEnable:char;
  m_VideoMixerControl:MixerControlParam_t;

  m_u8AudioProfiles:Byte;
  m_u8AudioLevel:Byte;
  m_u16AudioDecoderCfgLen:Word;
  m_u8AudioDecoderCfg:Array[0..199] of char;

  m_u8VideoProfiles:Byte;
  m_u8VideoLevel:Byte;
  m_u16VideoDecoderCfgLen:Word;
  m_u8VideoDecoderCfg:Array [0..199] of Byte;
  m_s8FileName:Array[0..259] of char;
end;

Type
  Control3gppRecord_t=record
  m_u32ControlType:Word;
  m_u8MediaType:Byte;
  m_u8Reserv1:Byte;
  m_u32StepTime:Cardinal;
  m_u32SpeedSize:Cardinal;
end;

Type
  Acs_MediaEx_Input_V=record
  m_u16Port:Word;
  m_u8Codec:Byte;
  m_u8PayloadType:Byte;
  m_u32ProfileLevelId:Word;
  decoderConfigLength:Word;
  decoderConfigInfo:Array[0..127] of char;
end;

Type
  Acs_MediaEx_Output_V=record
  m_s8IP:Array[0..19] of char;
  m_u16Port:Word;
  m_u8Codec:Byte;
  m_u8PayloadType:Byte;
  m_u16ResX:Word;
  m_u16ResY:Word;
  m_u8Fps:Byte;
  m_u16Kbps:Word;
end;

Type
  Acs_3GVConf_LayoutList=record
  m_device:Array[0..15] of DeviceID_t;
end;

Type
  Acs_3GVConf_VisibleList=record
  m_device:Array[0..15] of DeviceID_t;
end;

Type
  TColor=record
  m_u8R:Byte;
  m_u8G:Byte;
  m_u8B:Byte;
end;

Type
  TPoint=record
  x:Integer;
  y:Integer;
end;

Type
  UserLedCtrl=record
	m_u8LedTimeEnable:Byte;       {Led ontime & offtime ctrl paramter enable?}
	m_Rfu1:ShortInt;
	m_u16OnTime:Word;             //*LED ontime: 100~2000 ms*/
	m_u16OffTime:Word;            //*LED offtime: 100~2000 ms*/
	m_u8WatchDogOutEnbale:Byte;   //*LED watchdog out time ctrl paramter enable? */
	m_Rfu2:ShortInt;
	m_u16WatchDogOutTime:Word;    //*LED watchdog out time: 10~300 S*/
	m_u8WatchDogTimeEnable:Byte;  //*LED watchdog out state ctrl paramter enable? */
	m_Rfu3:ShortInt;
	m_u16WatchDogOnTime:Word;     //*LED watchdog ontime: 100~2000 ms*/
	m_u16WatchDogOffTime:Word;    //*LED watchdog offtime: 100~2000 ms*/
	m_u8FeedWatchDogEnable:Byte;  //*LED watchdog feed ? 0: feed not enable, 1: feed*/
	m_Rfu4 : Array[0..2] of ShortInt;
end;

//*Acs_AnalogMEG_CMD*/
Type
   Acs_AnalogMEG_CMD = record
	 m_u8Channel_Enable:Byte;
	 m_u8CallOut:Byte;
	 m_u8RingTime:Byte;
	 m_u8Reservered:Byte;
end;

//ACS Event Head
Type
  ACS_EVT_HEAD = record
	m_PkgEvtHead : PKG_HEAD_STRUCT;  //*ITP package head*/
	m_AcsEvt_t : Acs_Evt_t;          //*acs event package head*/
end;

//*ACS CSPPlayProperty_t*/
Type
  CSPPlayProperty_t = record
	m_u8TaskID : Byte;         //*play task ID*/
	m_u8SrcMode : Byte;        //*file src mode, reference XMS_VOC_SRC_MODE*/
	m_u8DecodeType : Byte;     //*decode type, reference XMS_VOC_CODE_TYPE*/
	m_s8Rfu1 : Byte;           //*Reserved*/
	m_u32MaxSize : Dword;      //*play max size(BYTES),  0: file real size; >0: max play size*/
	m_u32MaxTime : DWORD;      //*play max time(Seconds) 0: file real seconds; >0: max play seconds*/
	m_u32StopMode : DWORD;     //*stop play mode,referecne XMS_PLAYREC_STOP_MODE*/
	m_u32StopCode : DWORD;     //*stop play when receive this dtmf code*/
	m_Rfu1 : Array[0..3] of ShortInt;
end;

//ACS Get 3GPP file config add by fys*/
Type
  Get3gppCfg_t = Record
	m_u8MediaType       : Byte;                //media type: XMS_MEDIA_TYPE*/
	m_u8AudioFileType   : Byte;                //audio file type: XMS_CFG_TYPE*/
	m_u16AudioFileIndex : Word;                //audio file index: 0~1023*/
	m_s8AudioFileName   : Array[0..MAX_PATH-1] of ShortInt;  //audio file path and name*/
	m_u8VideoFileType   : Byte;                //video file type: XMS_CFG_TYPE*/
	m_u8Rfu1            : Byte;                //reserve*/
	m_u16VideoFileIndex : Word;                //video file index: 0~1023*/
	m_s8VideoFileName   : Array[0..MAX_PATH-1] of ShortInt;  //video file path and name*/
end;

Type
  TFontParam=record
  m_f64DBSize:Double;
  m_f64DBBlank:Double;
  m_f64DBGap:Double;
  m_f64DBAngle:Double;
  m_bUnderLine:Integer;
  strcutColor:TColor;
end;

Type
  PutTextInPicture_Param=record
  m_u8PutByType:Byte;
  m_u8PutByLevel:Byte;
  m_s8PutText:Array[0..259] of char;
  m_u16FontType:Word;
  structFontParam:TFontParam;
  m_f32Diaphaneity:Single;
  structPoint:TPoint;
end;

Type
  UserEvt_Head_t=record
  m_u32UsrEvtType:Integer;
  m_u32UsrEvtLen:Integer;
  m_Rfu1:Array[0..3] of char;
  m_pUsrEvtData:pointer;
end;

Type
  SigMon_t = record
	m_u8MonSigType  : Byte;     //singnal type,reference XMS_SIGMON_SIG_TYPE*/
	m_u8MonPackType : Byte;     //Signal Pakcet type,reference XMS_SIGMON_PACK_TYPE*/
	m_s8Rfu1        : Array[0..5] of ShortInt;        //Rfu*/
  end;


//CmdParamData_RTPXInput_t*/
Type
  CmdParamData_RTPXInput_t = record
	m_u8ChanEnable  : Byte;         //Enable flag, 0: disable; 1: enable*/
	m_u8MediaType   : Byte;         //Data type,reference XMS_VOIP_MEDIA_CAPS*/
	m_u8PayloadType : Byte;         //Payload type*/
	m_u8Rfu         : Byte;         //reserved*/
  end;

//CmdParamData_RTPXInput_A_t
Type
  CmdParamData_RTPXInput_A_t = record
	m_u8ChanEnable  : Byte;        //Enable flag, 0: disable; 1: enable*/
	m_u8MediaType   : Byte;        //Data type,reference XMS_VOIP_MEDIA_CAPS*/
	m_u8PayloadType : Byte;        //Payload type*/
	m_u8Decode      : Byte;        //Decode enable flag, 0: disable; 1: enable*/
end;
 
//CmdParamData_RTPXOutput_t
Type
  CmdParamData_RTPXOutput_t = record
	m_u8ChanEnable  : Byte;       //Enable flag, 0: disable; 1: enable*/
	m_u8MediaType   : Byte;       //Data type,reference XMS_VOIP_MEDIA_CAPS*/
	m_u8PayloadType : Byte;       //Payload type*/
	m_u8SRC_Ctrl1   : Byte;       //Source type,reference XMS_MIXER_TYPE*/
	m_u16SRC_Id1    : Word;       //Source channel ID*/
	m_u16RemotePort : Word;	      //Remote port*/
	m_u32RemoteIP   : DWord;		  //Remote IP*/
end;

Type
  CmdParamData_RTPXOutput_A_t = Record
	m_u8ChanEnable  : Byte;        //Enable flag, 0: disable; 1: enable*/
	m_u8MediaType   : Byte;        //Data type,reference XMS_VOIP_MEDIA_CAPS*/
	m_u8PayloadType : Byte;        //Payload type*/
	m_u8Encode      : Byte;        //Encode enable flag, 0: disable; 1: enable*/
	m_u8SRC_Ctrl1   : Byte;        //Source 1 type,reference XMS_MIXER_TYPE*/
	m_u8SRC_Ctrl2   : Byte;        //Source 2 type,reference XMS_MIXER_TYPE*/
	m_u16SRC_Id1    : Word;        //Source channel 1 ID*/
	m_u16SRC_Id2    : Word;        //Source channel 2 ID*/
	m_u16RemotePort : Word;	       //Remote port*/
	m_u32RemoteIP   : DWord;		   //Remote IP*/
end;

Type
  CmdParamData_RTPXAddr_t = record
	m_u32RemoteIP   : DWord;		   //Remote IP*/
	m_u16RemotePort : Word;	     //Remote port*/
	m_u8Rfu      : Array[0..1] of ShortInt;		   //Reserved*/
end;

//ACS CSP record private parma*/
Type
  CSPRecordPrivate_t = Record
	m_PrivateData       : PrivateData_t;  //privatedata head*/
  m_u8CspRecPrivType  : Byte;           //directly send cmd to dsp,0:no,1:yes,reference XMS_CSPREC_PRIV_TYPE*/
	m_u8CmdDirect       : Byte;           //directly send cmd to dsp,0:no,1:yes,reference XMS_CSPREC_CMD_OPT*/
	m_s8Rfu1            : Array[0..1] of ShortInt;
end;

Type
  ControlCSPRecordPrivate_t = Record
	m_PrivateData          : PrivateData_t;                  //privatedata head*/
  m_u8CtrlCspRecPrivType : Byte;         //directly send cmd to dsp,0:no,1:yes,reference XMS_CONTROL_CSPREC_PRIV_TYPE*/
	m_u8CmdDirect          : Byte;         //directly send cmd to dsp,0:no,1:yes,reference XMS_CONTROL_CSPREC_CMD_OPT*/
	m_s8Rfu1               : Array[0..1] of ShortInt;
end;

//ACS answer call private param*/
Type
  AnswerCallPrivate_t = Record
	m_PrivateData : PrivateData_t;   //privatedata head*/
	m_s32AnswerType : Integer;       //answer type*/
End;

//ACS Fax private param
Type
  FaxPrivate_t = Record
	m_PrivateData : PrivateData_t; //privatedata head*/
	m_VoIPDevice  : DeviceID_t;    //VoIP device ID*/
	m_u8WorkMode  : Byte;          //Fax work mode,reference XMS_FAX_WORKMODE*/
	m_s8Rfu1      : Array[0..2] of ShortInt;
end;

//Acs_TransAddHeader
Type
  Acs_TransAddHeader = Record
    m_u32Op   : DWORD;		               //set param type, 0: clear old config,
	                                       //1: set new config, reference to
	                                       //XMS_FAX_PAGE_HEADER_TYPE*/
    m_u16XPos : Word;		                 //the x of picture position,*/
    m_u16YPos : Word;                    //the y of picture position,*/
    m_u8Data  : Array[0..72] of ShortInt;//define by user for fax picture*/
    m_u8Rsrv  : ShortInt;
    m_u32FontSize : DWord;
    m_u32Header   : DWord;
end;

//Acs_TransAddHeaderEx
Type
  Acs_TransAddHeaderEx = Record
  m_u32Op : DWord;		               //set param type, 0: clear old config,
	                                   //1: set new config, reference to
	                                   //XMS_FAX_PAGE_HEADER_TYPE
  m_u16XPos : Word;		               //the x of picture position,
  m_u16YPos : Word;                  //the y of picture position,
  m_u32FontSize : DWord;             // 1-7
  m_u8Data      : Array[0..72] of ShortInt;   //define by user for fax picture
end;

//Acs_TransAddFile*/
Type
  Acs_TransAddFile = Record

    m_u32Op : DWord;			           //Send Multi File param type,
	                                           //0: clear file queue, 2: add
                                             //a new file to file queue,
                                             //reference to XMS_FAX_M_FILE_TYPE*/
    Dm_strFileName : Array[0..255] of ShortInt;            //the file name of need to be sent in a fax
end;

Type
  Acs_SetECM = Record
  m_u8FaxECMMode : Byte;			       //fac type, 0: normal; 1: Ecm, reference to XMS_FAX_ECM_MODE_TYPE*/
end;

Type
  Acs_SetFaxBps = record
  m_u8BPS : Byte;                    //fax transfor speed, referece to XMS_FAX_BPS_TYPE*/
end;

Type
  VoIPCallPrivate_t = record
	m_PrivateData     : PrivateData_t;   //privatedata head
	m_s32Protocol     : Integer;         //protocol type
	m_s8CallerAddress : Array[0..19] of ShortInt; //Caller Address
	m_s32CallerPort   : Integer;         //Caller Port
	m_s8CallerUserID  : Array[0..39] of ShortInt; //Caller UserID
	m_s8CalleeAddress : Array[0..19] of ShortInt; //Callee Address
	m_s32CalleePort   : Integer;         //Callee Port
	m_s8CalleeUserID  : Array[0..39] of ShortInt; //Callee UserID
	m_u8MediaCapNum   : Byte;            //media capability number
	m_u8MediaCapList  : Array[0..9] of Byte;      //media capability list
end;

Type
  VoIPCallPrivateEx_t = Record
	m_PrivateData     : PrivateData_t;            //privatedata head
	m_s32Protocol     : Integer;                  //protocol type
	m_s8CallerAddress : Array[0..19] of ShortInt; //Caller Address
	m_s32CallerPort   : Integer;                  //Caller Port
	m_s8CallerUserID  :  Array[0..39] of ShortInt;//Caller UserID
	m_s8CalleeAddress :  Array[0..19] of ShortInt;//Callee Address
	m_s32CalleePort  : Integer;                   //Callee Port
	m_s8CalleeUserID :  Array[0..39] of ShortInt; //Callee UserID
	m_u8MediaCapNum  : Byte;                      //media capability number
	m_u8MediaCapList :  Array[0..9] of Byte;      //media capability list
	u8MediaMode      : Byte;			// media mode 0:noset(sendrecv) 1:sendonly 2:recvonly 3:sendrecv
end;

//ACS Voip Open private param
Type
  VoIPOpenPrivate_t = record
	m_PrivateData : PrivateData_t;	//privatedata head
	m_u8RtpMode   : Byte;		        //RTP Mode:0-default auto,1-user control
end;

Type
  VoIPForwardCallPrivate_t = Record
	m_PrivateData : PrivateData_t;                //privatedata head
	m_s32Protocol : Integer;                      //protocol type
	m_s8CallerAddress : Array[0..19] of ShortInt; //Caller Address
	m_s32CallerPort   : Integer;                  //Caller Port
	m_s8CallerUserID  : Array[0..39] of ShortInt; //Caller UserID
	m_s8TelNo         : Array[0..19] of ShortInt;	//telephone number
end;

Type
  VoIPAlertPrivate_t = record
	m_PrivateData    : PrivateData_t;         //privatedata head*/
	m_u8MediaCapNum  : Byte;                  //media capability number*/
	m_u8MediaCapList : Array[0..9] of Byte;   //media capability list*/
end;

Type
  VoIPAlertPrivateEx_t = record
	m_PrivateData     : PrivateData_t;        //privatedata head*/
	m_u8MediaCapNum   : Byte;                 //media capability number*/
	m_u8MediaCapList  : Array[0..9] of Byte;  //media capability list*/
	u16AlertCode      : Word;			            // alert code for sip, support 180,181,182,183, default is 183
end;

Type
  VoIPAnswerPrivate_t = record
	m_PrivateData    : PrivateData_t;            //privatedata head*/
	m_u8MediaCapNum  : Byte;                     //media capability number*/
	m_u8MediaCapList : Array[0..9] of Byte;      //media capability list*/
end;

Type
  VoIP_RTP_Format_t = record
  u8CodecType   : Byte;    // codec type
  u8PayloadType : Byte;    // payload type
end;

Type
  VoIP_RTP_Session_t = record
  u32IP   : DWord;               //remote rtp address
  u16Port : Word;                //remote rtp port
  tx      : VoIP_RTP_Format_t;   //transmit
  rx      : VoIP_RTP_Format_t;   //receive format
  end;

Type
  VoIPConnectPrivate_t = record
  m_PrivateData : PrivateData_t;
  audio         : VoIP_RTP_Session_t;
  video         : VoIP_RTP_Session_t;
end;

Type
  ChCodec = Record
	m_u8Enable        : Byte;		// enable flag
	m_u8TxCodec       : Byte;		// tx codec
	m_u8TxPayloadType : Byte;		// tx payload type (if dynamical)
	m_u8RxCodec       : Byte;		// rx codec
	m_u8RxPayloadType : Byte;		// rx payload type (if dynamical)
end;

Type
  Acs_VoIP_RTPCODEC = Record
  audio : ChCodec;
  video : ChCodec;
end;


Type
  ChMedia = Record
  m_u8Enable : Byte;			            // enable flag */
	m_s8IP : Array[0..19] of ShortInt;	// ip address */
	m_u16Port : Word;			              // port */
	m_u8TxCodec : Byte;			            // tx codec */
	m_u8TxPayloadType : Byte;		        // tx payload type (if dynamical) */
	m_u8RxCodec : Byte;			            // rx codec */
	m_u8RxPayloadType : Byte;		        // rx payload type (if dynamical) */
  end;

Type
  Acs_VoIP_RTPOpen = Record
  m_u8Enable      : Byte;		// enable/disable rtp session */
  m_u8PayloadDtmf : Byte;		// dynamic payload type for rtp dtmf */
  m_u8PayloadTone : Byte;		// dynamic payload type for rtp tone */
  audio : ChMedia;
  video : ChMedia;
end;

Type
  Acs_VoIP_MediaInfo = record
  payload_dtmf    : Byte;
  payload_tone    : Byte;
  u8AudioEnabled  : Byte;
  s8AudioAddress  : Array[0..19] of ShortInt;			// host address
  u16AudioPort    : Word;			// port number
  u8VideoEnabled  : Byte;
  s8VideoAddress  : Array[0..19] of ShortInt;			// host address
  u16VideoPort    : Word;			// port number
  u8MediaCapNum   : Byte;                         // media capability number
  u8MediaCapList  : Array[0..9] of byte;          // media capability list
end;

Type
  ChAddr = record
  m_u8Enable : Byte;			// enable flag
	m_s8IP     : Array[0..19] of ShortInt;			// ip address
	m_u16Port  : Word;			// port
  end;

Type
  Acs_VoIP_RTPADDR = record
  audio : ChAddr;
  video : ChAddr;
  end;

Type
  Acs_VoIP_RTPSESSION = record
	m_u8Enable : Byte;				// enable/disable rtp session
	m_u8PayloadDtmf : Byte;		// dynamic payload type for rtp dtmf
	m_u8PayloadTone : Byte;		// dynamic payload type for rtp tone
  end;

Type
  VoIPDummyPrivate_t = record
	m_PrivateData : PrivateData_t;	//privatedata head
  end;

// Acs VoIP Registration State struct
Type
  Acs_VoIP_REGSTATE = record
	m_u16SlotID   : Word;			//* Registration Slot ID */
	m_u8Protocol  : Byte;			//* VoIP Protocol */
	m_u8State     : Byte;			//* Registration State */
	m_s8TelNo     : Array[0..19] of ShortInt;		//* Client Telephone-subscriber */
	m_s8Address   : Array[0..19] of ShortInt;		//* Client Address */
	m_u16Port     : Word;				                //* Client Port */
	m_s8UserID    : Array[0..39] of ShortInt;		//* Client UserID */
end;

// Acs_VoIP_Regist Struct
Type
  Acs_VoIP_Regist = record
	m_u16SlotID   : Word;			                    // Registration Slot ID
	m_u8Protocol  : Byte;			                    // VoIP Protocol
	m_u8State     : Byte;			                    // Registration State
	m_s8TelNo     : Array[0..19] of ShortInt;			// Client Telephone-subscriber
	m_s8Address   : Array[0..19] of ShortInt;		  // Client Address
	m_u16Port     : Word;			                    // Client Port
	m_s8UserID    : Array[0..39] of ShortInt;			// Client UserID
end;

// Acs_VoIP_Regist_Response struct
Type
  Acs_VoIP_Regist_Response = record
  m_u8State : Byte;		                  // Registration State
  m_s8TelNo : Array[0..19] of shortint;	// subscriber number
end;

// Acs VoIP Refer struct
Type
  Acs_VoIP_Refer = record
	m_u8Protocol: Byte;			                  // VoIP Protocol
	m_u8State   : Byte;				                // Registration State
	m_s8TelNo   : Array[0..19] of ShortInt;		// Client Telephone-subscriber
	m_s8Address : Array[0..19] of ShortInt;		// Client Address
	m_u16Port   : Word;				                // Client Port
	m_s8UserID  : Array[0..39] of ShortInt;		// Client UserID
	m_u8ReferedToUnitId : Byte;	              // Referd-to header with replaces tag when act or sact
	m_u16ReferedToChanId : Word;            	// Referd-to header with replaces tag when act or sact
end;


// Acs VoIP Refer Response struct
Type
  Acs_VoIP_Refer_Response = record
	m_u8ReferFlag   : Byte;			                // refer flag
	m_u8SrcUnitID   : Byte;				              // source Unit ID
	m_u16SrcChanID  : Word;				              // source Channel ID
	m_u8DestUnitID  : Byte;				              // destination Unit ID
	m_u16DestChanID : Word;				              // destination Channel ID
	m_s8TelNo       : Array[0..19] of ShortInt;	// Client Telephone-subscriber
	m_s8Address     : Array[0..19] of ShortInt;	// Client Address
	m_u16Port       : Word;				              // Client Port
	m_s8UserID      : Array[0..39] of ShortInt;	// Client UserID
end;

// Acs VoIP Refer Result struct
Type
  Acs_VoIP_ReferResult = record
	m_u8Protocol : byte;			// protocol
	m_u8State    : byte;			// state
	m_u8Reason   : byte;			// reason
end;

// Acs VoIP Refer Result struct
Type
  Acs_VoIP_Notify = record
	m_u32StatusCode : DWORD;		// statusCode
end;

// Acs VoIP Registraion Response struct
Type
  Acs_VoIP_REGRESP = record
	m_u16SlotID  : Word;			               // Registration Slot ID
	m_u8Granted  : Byte;			               // grant registration
	m_s8Password : Array[0..19] of ShortInt; // password for sip authentication
end;

//analog flash param
Type
  CmdParamData_FlashParam_t = record
	m_u8MinHookFlashTime : Byte;		//default is 5, //in units of 20ms
	m_u8MaxHookFlashTime : Byte;		//default is 25,in units of 20ms
end;

Type
  CmdParamData_TrunkFlashParam_t = record
	m_u8HookFlashTime : Byte;		//default is 10, //in units of 20ms
	m_u8reserved      : Array[0..2] of Byte;
end;

//Analoge Rec Module Voltage param
Type
  CmdParamData_AnalogRecVoltage_t = record
	m_u8Valtage    : Byte;                   //[0, 54], default is 54
	m_u8Reserve    : Array[0..2] of Byte;    //reserve
end;

Type
  CmdParamData_ReadSn_t = record
  m_u8ReadSn   : Array[0..12] of Byte;
  m_u8Reserved : Array[0..2] of Byte;
end;

Type
  CmdParamData_ReadVoltage_t = record
	m_u8ReadFlag  : Byte;      //Read voltage control flag, 0: stop read; 1: start read
	m_s8Reserved1 : Array[0..2] of ShortInt;
	m_u32TimeSpan : DWord;     //Keygoe report voltage event time span, unit: ms
	m_s8Voltage   : ShortInt;  //Current voltage value
  m_u8Reserved2 : Array[0..2] of Byte;
end;

//silence voice detect param*/
Type
  CmdParam_SilenceDetectParam_t = record
  m_s32SilenceLevel : Integer;            //silence detect level(db),default: -42, [-60, -20]
  m_s32SilenceTimer : Integer;            //silence detect timer(ms)
  m_s32Reserved2    : Integer;            //reserve
end;

//CmdParam_ActiveMemDetectParam_t is obsolete now
//active member detect param
Type
  CmdParam_ActiveMemDetectParam_t = record
  m_s32VadLevel  : Integer;              //active conf member detect level(db), obsolete
  m_s32Reserved1 : Integer;               //reserve                              obsolete
end;

//VAD min level detect param
Type
  CmdParam_VADMinDetectParam_t = record
  m_s32VadLevel    : Dword;             //VAD min detect level(db), default: -54, [-60, -20]
  m_u16VadInterval : Word;              //VAD interval(5ms), default: 200, [10, 300]
  m_u8Reserved1    : Array[0..1] of Byte;
end;

//Board Common param set
Type
  CmdParam_BoardCommonParam_t = record
  m_u8IsCNGEnable   : Byte;              //the switch of CNG, 0: Disable, 1: Enable
  m_u16CNGGainLevel : Word;              //the value of CNG gain,default: 9,[4, 15]
  m_u8Reserved1     : Array[0..28] of byte;
end;

//FSK Send/Recv param
Type
  CmdParamData_FskParam_t = record
	rxFilterWindow   : Word;        //default is 4, shouldn't change it
	rxPeriodTheshold : Word;        //default is 320,shouldn't change it
	rx55Count        : Word;        //default is 6, can be changed as needed
	rxAllOneSamples  : Word;        //default is 200, can be changed as needed
	rxDataTimeOut    : Word;        //default is 20ms,can be changed as needed
	txBit1Freq       : Word;        //default is 1200,can be changed as needed
	txBit0Freq       : Word;        //default is 2200,can be changed as needed
	tx55Count        : Word;        //default is 30, can be changed as needed
	txAllOneSamples  : Word;        //default is 600, can be changed as needed
	reserved         : Array[0..2] of Word;
end;

// Acs Conference Active Member List struct
Type
  CmdParamConf_MemberState_t = record
  m_s8NormalVad      : Array[0..15] of Byte;  //the buffer of normal active member in the conferece
  m_s8IPVad          : Array[0..15] of Byte;  //the buffer of IP active member in the conferece
  m_u8TotalOfConfMem : byte;                  //the total of members in the conferece
  m_u8Ref            : Array[0..2] of Byte;   //reserver
end;

// Acs Set Conference Vad Check Interval struct
Type
  CmdParamConf_VadInterval_t = record
  m_u16VadCheckInterval : Word;   //The Interval Of Check Vad In A Conferece: [30, 65535], Unit: ms
  m_u8RptConfMemEnable : Byte;    //If Auto Report Active Conference member, 1: Enable, 0: Disable
  m_u8Ref : Array[0..4] of byte;
end;

// Acs VoIP H.245 UserInputIndication struct
Type
  CmdParamData_GtgFreq_t = record
	m_u16Freq_Index : Word;  // Frequence index: 0-15
	m_u16Freq_Coef  : Word;  // Frequence
end;

//---This Struct according to ITP_GTG_Template(DSP_PACKET_DEF.H)
Type
  CmdParamData_GtgProtoType_t = record
	m_u8GTG_id      : byte;	  //影射GTG ID，有效值0x30-0x3F
	m_u8Reserved1   : byte;		//保留
	m_u16Reserved2  : Word;		//保留

	//-------ITP_GTG_Prototype--------
	m_u8Freq1_Index : byte;
	m_u8Freq2_Index : byte;
	m_u16Freq1_Amp  : Word;
	m_u16Freq2_Amp  : Word;
	m_u16Envelope_Mode : Word;
	m_u16Repeat_Count  : Word;
	m_u16On_Time1  : Word;
	m_u16Off_Time1 : Word;
	m_u16On_Time2  : Word;
	m_u16Off_Time2 : Word;
	m_u16Reserved  : Word;		//保留
end;

// Acs VoIP H.245 UserInputIndication struct
Type
  CmdParamData_CTCLKNET_t = record
  m_u8NetRef1      : Byte;       //L_NET0=0x08,L_NET1=0x09,L_NET2=0x0A,L_Net3=0x0B
	m_u8SysClockType : Byte;       //reference to XMS_BOARD_CLOCK_TYPE
  m_u8Rfu          : Array[0..1] of Byte;
end;

// Acs VoIP H.245 UserInputIndication struct
Type
  Acs_VoIP_H245UII = record
	m_s8String    : Array[0..99] of ShortInt;		// UserInputIndication string (general string)
	m_s8Signal    : ShortInt;				            // UserInputIndication signal type (dtmf char in "0123456789#*ABCD!")
	m_Rfu         : Array[0..2] of ShortInt;    // Reserved
	m_u32Duration : DWORD;			                // UserInputIndication signal duration (in milliseconds)
end;

// Acs MediaEx Audio Output Param
Type
  Acs_MediaEx_Output_A = record
	m_s8IP    : Array[0..19] of ShortInt;	// dest address
	m_u16Port : Word;				              // dest port
	m_u8Codec : Byte;				              // codec type
	m_u8PayloadType : Byte;		            // rtp payload type (if dynamic)
end;

// Acs MediaEx Play Param
Type
  Acs_MediaEx_Play = record
	m_PrivateData : PrivateData_t;			//privatedata head
	m_s8SrcName   : Array[0..ACS_MAX_FILE_NAME_LEN-1] of ShortInt;	// file name
	m_u32Start    : Dword;				              // start time
	m_u8Loop      : byte;				                // loop
	audio         : Acs_MediaEx_Output_A;			  // audio output param
	video         : Acs_MediaEx_Output_V;			  // video output param
	s8OverlayImage: Array[0..199] of ShortInt;
end;

// Acs 3GVConf Play Param
Type
  Acs_3GVConf_Play = record
	m_PrivateData : PrivateData_t;			//privatedata head
	m_device      : DeviceID_t;			    //voc conf DeviceID
	m_play        : Acs_MediaEx_Play;		//Acs_MediaEx_PlayFile
end;

Type
  Acs_MediaEx_Transcode = record
	m_PrivateData : PrivateData_t;	          //privatedata head*/
	input         : Acs_MediaEx_Input_V;			// input param
	output        : Acs_MediaEx_Output_V;			// output param
	s8OverlayImage: Array[0..199] of ShortInt;
end;

Type
  Acs_MediaEx_Conference = record
	m_PrivateData : PrivateData_t;	// privatedata head
	input         : Array[0..15] of Acs_MediaEx_Input_V;		// input param
	output        : Array[0..15] of Acs_MediaEx_Output_V;		// output param
	s8OverlayImage: Array[0..199] of ShortInt;
end;

Type
  Acs_MediaEx_Record = record
	m_PrivateData : PrivateData_t;			      //privatedata head
	m_s8DstName   : Array[0..ACS_MAX_FILE_NAME_LEN-1] of ShortInt;	// file name
	audio         : Acs_MediaEx_Output_A;			// audio output param
	video         : Acs_MediaEx_Output_V;			// video output param
end;

Type
  Acs_3GVConf_Record = record
	m_PrivateData : PrivateData_t;			//privatedata head
	m_device : DeviceID_t;			        //voc conf DeviceID
	m_record : Acs_MediaEx_Record;			//Acs_MediaEx_RecordFile
end;

Type
  Acs_3GVConf_Cmd_V = record
	m_device    : DeviceID_t;
	m_input     : Acs_MediaEx_Input_V;
	m_output    : Acs_MediaEx_Output_V;
	m_u8Visible : Byte;
	m_u8CmdType : Byte;
end;

Type
  Acs_MediaEx_ConfLayout = record
	m_PrivateData : PrivateData_t;
	layout        : Array[0..15] of Integer;
end;

Type
  Acs_Video_Link_Param = record
	m_PrivateData       : PrivateData_t;// privatedata head
  m_u8TranscodeModule : Byte;		      // transcode module id
	m_u8SrcCodec        : Byte;				  // source codec type
  decoderConfigLength : Word;
	decoderConfigInfo   : Array[0..MAX_DECODER_CFG_INFO-1] of Byte;
	m_u8DstCodec        : Byte;				  // destination codec type
	m_u8Fps             : Byte;					// destination framerate in fps
	m_u16Kbps           : Word;					// destination bitrate in Kbps
  m_u16ResX           : Word;					// destination resolution x
	m_u16ResY           : Word;					// destination resolution y
	s8OverlayImage      : Array[0..199] of ShortInt;
end;

Type
  Acs_3G324M_H223CAP = record
	videoWithAL1            : Byte;
	videoWithAL2            : Byte;
	videoWithAL3            : Byte;
	audioWithAL1            : Byte;
	audioWithAL2            : Byte;
	audioWithAL3            : Byte;
	maximumAl2SDUSize       : Word;
	maximumAl3SDUSize       : Word;
	maximumDelayJitter      : Word;
	maxMUXPDUSizeCapability : Byte;
	nsrpSupport             : Byte;
	modeChangeCapability    : Byte;
	h223AnnexA              : Byte;
	h223AnnexADoubleFlag    : Byte;
	h223AnnexB              : Byte;
	h223AnnexBwithHeader    : Byte;
	reserved                : Byte;
end;

Type
  Acs_3G324M_CAP_AMR = record
	maxBitRate : Byte;
	maxFramesPerSdu : Byte;
	reserved : Array[0..1] of Byte;
end;

Type
  Acs_3G324M_CAP_G723 = record
	maxFramesPerSdu    : Byte;
	silenceSuppression : Byte;
	reserved           : Array[0..1] of Byte;
end;

Type
  Acs_3G324M_CAP_H263 = record
	sqcifMPI    : Byte;
	qcifMPI     : Byte;
	cifMPI      : Byte;
	cif4MPI     : Byte;
	cif16MPI    : Byte;
	reserved1   : Byte;
	maxBitRate  : Word;
	unrestrictedVector : Byte;
	arithmeticCoding   : Byte;
	advancedPrediction : Byte;
	pbFrames           : Byte;
	temporalSpatialTradeOffCapability : Byte;
	errorCompensation : Byte;
	reserved2         : Array[0..1] of Byte;
end;

Type
  Acs_3G324M_CAP_MP4 = record
	maxBitRate          : Word;
	profileAndLevel     : Byte;
	Obj                 : Byte;
	reserved            : Array[0..2] of Byte;
	decoderConfigLength : Byte;
	decoderConfigInfo   : Array[0..MAX_DECODER_CFG_INFO-1] of Byte;
end;

Type
  Acs_3G324M_CAP = record
  case integer of
  1:(AmrAudioCapability   : Acs_3G324M_CAP_AMR);
  2:(G7231AudioCapability : Acs_3G324M_CAP_G723);
  3:(H263VideoCapability  : Acs_3G324M_CAP_H263);
  4:(Mpeg4VideoCapability : Acs_3G324M_CAP_MP4);
end;

Type
  Acs_3G324M_CAPENTRY = record
  entryNumber : Word;
	capType     : Byte;							// reference to XMS_VOIP_MEDIA_CAPS
	direction   : Byte;						  // reference to XMS_CAP_DIRECTION
	capability  : Acs_3G324M_CAP;
end;

Type
  Acs_3G324M_CAPTABLE = record
	capabilityNum          : Word;
	reserved               : Word;
	CapabilityTableEntry   : Array[0..MAX_CAPS_NUM-1] of Acs_3G324M_CAPENTRY;
end;

Type
  Acs_3G324M_TCS = record
	h223Capability  : Acs_3G324M_H223CAP;
	capabilityTable : Acs_3G324M_CAPTABLE;
end;

Type
  Acs_VoIP_SIPINFO = record
	m_s8ContentType : Array[0..49] of ShortInt;	 // content type string (mime)
	m_s8Body        : Array[0..799] of ShortInt; // info message body string
end;

Type
  Acs_VoIP_SIPREG = record
	m_s8TelNo    : Array[0..19] of ShortInt;	// subscriber number
	m_s8Username : Array[0..19] of ShortInt;	// username for authorization
	m_s8Password : Array[0..19] of ShortInt;	// paswword for authorization
end;

Type
  Acs_VoIP_RTPDTMF = record
	m_s8EventChar : ShortInt;	// dtmf event char
	m_s8Volume    : ShortInt;	// volume (in dbm0 from -63 to 0)
	m_u16Duration : Word;			// duration (in timestamp units)
end;

Type
  Acs_VoIP_RTPTONE = record
	m_u16Modulation  : Word;		        // modulation
	m_u8TriFlag      : byte;			      // tri-frequency flag
	m_s8Volume       : ShortInt;				// volume
	m_u16Duration    : Word;			      // duration
	m_u8FrequencyNum : Byte;            // number of frequencies
	m_u16Frequency   : Array[0..9] of Word;		// frequencies to mix the tone
end;

Type
  Acs_VoIP_Mixer = record
	m_u8SRC1_Ctrl  : Byte;      //reference XMS_MIXER_TYPE
	m_u8SRC2_Ctrl  : Byte;      //reference XMS_MIXER_TYPE
	m_u16SRC_ChID1 : Word;      //Media ChID1
	m_u16SRC_ChID2 : Word;      //Media ChID2
	m_s8Video      : ShortInt;  //Video Channel
	m_s8Rfu        : ShortInt;  //Rfu*/
end;

Type
  CmdParamData_AnalogTrunkFlash_t = record
	m_u8Channel_Enable : byte;
	m_u8Type           : byte;
	m_u8Tx_State       : byte;
	m_u8Rx_State       : byte;
end;




//DTMF control param*/
Type
  CmdDtmfParamData_Voice_t = record
  m_u32MaxValidIntervalTime : Integer;              // max interval time: ms
  m_u8MaxCodeNums           : Byte;                 // max DTMF nums : 0 ~ 255
  m_u8Rfu1                  : Array[0..2] of Byte;
  m_u8DTMF                  : Array[0..31] of Byte; //DTMF buffer
end;

Type
  CmdParamData_AddFax_t = record
	m_s8FaxFileName : Array[0..127] of ShortInt; // FaxFileName ,Usual As Tiff Format
end;

Type
  CmdParamData_StartSendFax_t = record
	m_VocDev    : DeviceID_t;
	m_s8LocalID : Array[0..ACS_LOCALID_MAX_LEN-1] of ShortInt;
end;

Type
  CmdParamData_3GPP_t = record
  m_u8AudioDecodeType     : Byte;   //audio decode type
	m_u8AudioFrameType      : Byte;   //audio frame type,reference XMS_AUDIO_AMR_FRAME_TYPE
  m_u16AudioDecoderCfgLen : Word;   //audio decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN
	m_u8AudioDecoderCfg     : Array[0..ACS_MAX_DECODER_CFG_LEN-1] of Byte;//audio decoder cfg
	m_u8AudioProfiles       : Byte;   //audio profiles?
  m_u8AudioLevel          : Byte;		//audio level ?*
  m_Rfu1                  : Array[0..1] of Byte;

	m_u8VideoDecodeType     : Byte;   //video decode type
	m_u8VideoFrameRate      : Byte;   //video frame rate 10 ~ 30
	m_u16VideoDecoderCfgLen : Word;   //video decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN
	m_u8VideoDecoderCfg     : Array[0..ACS_MAX_DECODER_CFG_LEN-1] of Byte; //video decoder cfg?
	m_u8VideoProfiles       : Byte;   //video profiles?
	m_u8VideoLevel          : Byte;   //video level?
	m_Rfu2                  : Array[0..1] of Byte;
end;

Type
  DigRecSwitchMode = record
	m_u8Enable          : Byte;      //the switch of the function, 0: disable; 1: enable
	m_u8SwitchMode      : Byte;      //the digital switch type,referece to XMS_DRS_SWITCH_TYPE*/
	m_u8EncodeType      : Byte;      //audio's encode type, referece to the A-Law or Mu-law of XMS_VOC_CODE_TYPE, and any other type is not supported by keygoe
	m_u8IsRecordSigData : Byte;      //the switch to wheather record the signal data from DSP, 0: disable; 1: enable
	m_Rfu1              : Array[0..3] of ShortInt;
end;

Type
  CmdParamData_SS7RawFrame_t = record
	m_u8UserType : Byte;
	m_u8LinkType : Byte;
	m_u8MsgType  : Byte;
	m_u8InfoLen  : Byte;
	
	m_u8UnitId  : Byte;
	m_u8E1Port  : Byte;
	m_u8Ts      : Byte;
	m_u8Reserved1 : Byte;
	
	m_u8Info    : Array[0..254] of Byte;
	Reserved2   : Byte;
end;

Type
  CmdParamData_t = record
  case integer of
  1: (m_cmdParamDataVoice : CmdParamData_Voice_t);
  2: (m_CmdParamDataConf: CmdParamData_Conf_t);
end;

Type
  Acs_GeneralProc_Evt = record
	m_AcsEvtHead      : ACS_EVT_HEAD;         //acs event head
	m_AcsGenLProcData : Acs_GeneralProc_Data; //acs general proc event data
end;

Type
  Acs_OpenStreamExt_Data = record
	m_ServerID       : ServerID_t;
	m_s32AcsEvtState : Integer;    //acs event state, 1: success; 0: failed
	m_s8Rfu1         : Array[0..11] of ShortInt;
end;

Type
  Acs_OpenStreamExt_Evt = record
	m_AcsEvtHead           : ACS_EVT_HEAD;           //acs event head
	m_AcsOpenStreamExtData : Acs_OpenStreamExt_Data; //acs general proc event data
end;

Type
  Acs_CloseStreamExt_Data = record
	m_ServerID : ServerID_t;
	m_s8Rfu1   : Array[0..15] of ShortInt;
end;

Type
  Acs_CloseStreamExt_Evt = record
	m_AcsEvtHead            : ACS_EVT_HEAD;            //acs event head
	m_AcsCloseStreamExtData : Acs_CloseStreamExt_Data; //acs general proc event data
end;

Type
  Acs_MasterState_Data = record
	m_s8ServerIp    : Array[0..31] of ShortInt; //XMS server ip
	m_u32ServerPort : DWORD;                    //XMS server port
	m_u8MasterState : Byte;                     //Acs server master state,reference ACS_MASTER_STATE
	m_Rfu1          : Array[0..2] of ShortInt;
end;

Type
  Acs_MasterState_Evt = record
	m_AcsEvtHead     : ACS_EVT_HEAD;         //acs event head
	m_AcsMasterState : Acs_MasterState_Data; //acs master state
end;

Type
  Acs_SlaveWorkState_Data = record
	m_s8WorkState : ShortInt; //Slave machine work state: 0: conk out, 1: working, reference to ACS_WORK_STATE
	m_Rfu1        : Array[0..30] of ShortInt;
end;

Type
  Acs_SlaveWorkState_Evt = record
	m_AcsEvtHead        : ACS_EVT_HEAD;            //acs event head
	m_AcsSlaveWorkState : Acs_SlaveWorkState_Data; //acs slave work state
end;

Type
  Acs_BakSysStartEvt = record
  m_AcsEvtHead : ACS_EVT_HEAD;  //acs event head
  m_Rfu1       : Integer;
end;

Type
  Acs_ParamProc_Data = record
	m_s32AcsEvtState   : Integer;    //acs event state, 1: success; 0: failed
	m_s32AcsEvtErrCode : Integer;    //acs event errcode,reference XMS_ERROR_CODE_DEF
	m_u16ParamCmdType  : Word;       //acs param Cmd Type
	m_u16ParamDataSize : Word;       //acs param Data Size
end;

Type
  Acs_ParamData_Evt = record
	m_AcsEvtHead    : ACS_EVT_HEAD;     //acs event head
	m_ParamProcData : Acs_ParamProc_Data;
end;

Type
  Acs_ParamData_UserReadXmsBoardInfo = record
	m_u8MacAddr       : Array[0..5] of Byte;	   // Mac address
	m_u8ChassisType   : Byte;                    // chassis type，0: ITP1200; 1:3U chassis; 2:5U chassis; 3: 11U chassis
	m_u8ChassisIndex  : Byte;                    // chassis  No
	m_u8ChassisSlot   : Byte;                    // chassis slot number
	m_u8SubBoardIndex : Byte;                    // module index inside one board
	m_u8BoardType     : Byte;	                   // Board type，0:itp1200;1:itp2400; 2: itp4800
	rfu1              : Byte;
	m_s8SystemName    : Array[0..31] of ShortInt;// System name
	m_s8PlatformType  : ShortInt;                // Platform: 1:callback; 2:keygoe 1000; 3:keygoe 3000; 4:keygoe 8000
	m_s8UserCode      : Array[0..6] of ShortInt; // User code
	m_s32SysId        : Integer;                 // sys id
	rfu2              : Array[0..19] of ShortInt;

	m_s8FirmwareName    : Array[0..7] of ShortInt;	// DSP firmwarename
	m_s8FirmwareVersion : Array[0..7] of ShortInt;	// DSP firmware version
	m_s8RevisionDate    : Array[0..7] of ShortInt;	// DSP firmware date
end;

Type
  Acs_BoardPrivateExt_Data = record
	m_u32ExtType             : DWORD;   //reference to XMS_BOARD_PRIVATE_EXT_TYPE
  m_u8BoardClockTypeOrMode : Byte;    //reference to XMS_BOARD_EXT_CLOCK_TYPE   reference to XMS_BOARD_CLOCK_MODE
	m_u8SysClockType         : Byte;    //reference to XMS_BOARD_CLOCK_TYPE
	m_u8Ref : Array[0..1] of Byte;
end;

Type
  Acs_BoardRstState_Data = record
	m_u8Ref : Array[0..15] of Byte;  //reserve
end;


// CAS Extra Infomation, used by XMS_EVT_CAS_MFC_END
Type
  Acs_CAS_ExtraInfo_t = record
	// Call In Infomation
	m_u8KA  : byte; // Caller's KA *
	m_u8KD  : byte; // Caller's KD
	// Call Out Infomation
	m_u8Rfu : Array[0..13] of Byte;// Reserved for Future Use
end;

Type
  Acs_CAS_MFC_Evt = record
	m_AcsEvtHead      : ACS_EVT_HEAD;        //acs event head
	m_AcsCASExtraInfo : Acs_CAS_ExtraInfo_t; //acs CAS ExtraInfo event data
end;

Type
  Acs_MediaCSPProc_Data = record
	m_u16DataLen     : Word;	    //stream data size
	m_u8DataType     : Byte;		  //stream data type
	m_u8TagNumber    : Byte;			//Rfu
	m_u8StreamData   : Array[0..ITP_MAX_STREAM_DATA_LENGTH-1] of Byte;	//stream data
end;

Type
  Acs_MediaCSPProc_Evt = record
	m_AcsEvtHead      : ACS_EVT_HEAD;           //acs event head
	m_AcsMediaCSPProc : Acs_MediaCSPProc_Data;  //acs media CSP proc event data
end;

Type
  Acs_Media3GPPProc_Data = record
	m_s32AcsEvtState   : Integer;       //common: acs event state, 1: success; 0: failed
	m_s32AcsEvtErrCode : Integer;       //common: acs event errcode ,reference XMS_ERROR_CODE_DEF
	m_u8AudioTaskID    : Byte;          //audio:  play Task ID*/
	m_u8MediaType      : Byte;          //common: media type XMS_MEDIA_TYPE*/
	m_u8VideoTaskID    : Byte;          //video:  play Task ID*/
	m_s8Rfu            : ShortInt;
	m_u32AudioCurFileIndex : DWORD;     //audio:current play index*/
	m_u32AudioCurFilePos   : DWORD;     //audio:current play pos*/
	m_u32VideoCurFileIndex : DWORD;     //video:current play index*/
	m_u32VideoCurFilePos   : DWORD;     //video:current play pos*/
	m_PrivData             : PrivateData_t;
end;

Type
  Acs_Media3GPPProc_Evt = record
	m_AcsEvtHead : ACS_EVT_HEAD;                //acs event head
	m_AcsMedia3GPPProc : Acs_Media3GPPProc_Data;//acs media proc event data
end;

Type
  Acs_JoinTo3GVConf_Data = record
	m_s32AcsEvtState   : Integer;         //common: acs event state, 1: success; 0: failed
	m_s32AcsEvtErrCode : Integer;         //common: acs event errcode ,reference XMS_ERROR_CODE_DEF
	m_3GVConfDev       : DeviceID_t;
	m_srcDev           : DeviceID_t;
	m_PrivData         : PrivateData_t;   //private data*/
end;

Type
  Acs_JoinTo3GVConf_Evt = record
	m_AcsEvtHead       : ACS_EVT_HEAD;            //acs event head
	m_AcsJoinTo3GVConf : Acs_JoinTo3GVConf_Data;  //acs Join to 3GVConf event data
end;

Type
  Acs_LeaveFrom3GVConf_Data = record
	m_s32AcsEvtState   : Integer;       //common: acs event state, 1: success; 0: failed*/
	m_s32AcsEvtErrCode : Integer;       //common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/
	m_3GVConfDev       : DeviceID_t;
	m_srcDev           : DeviceID_t;
	m_PrivData         : PrivateData_t;
end;

Type
  Acs_LeaveFrom3GVConf_Evt = record
	m_AcsEvtHead          : ACS_EVT_HEAD;    //acs event head*/
	m_AcsLeaveFrom3GVConf : Acs_LeaveFrom3GVConf_Data;  //acs leave from 3GVConf event data*/
end;

Type
  Acs_Clear3GVConf_Data = record
	m_s32AcsEvtState   : Integer;         //*common: acs event state, 1: success; 0: failed*/
	m_s32AcsEvtErrCode : Integer;         //*common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/
	m_3GVConfDev       : DeviceID_t;
	m_PrivData         : PrivateData_t;
end;

Type
  Acs_Clear3GVConf_Evt = record
	m_AcsEvtHead : ACS_EVT_HEAD;                //*acs event head*/
	m_AcsClear3GVConf : Acs_Clear3GVConf_Data;  //*acs clear 3GVConf event data*/
end;

Type
  Acs_GetLayout_Data = record
	m_s32AcsEvtState   : Integer;       //common: acs event state, 1: success; 0: failed*/
	m_s32AcsEvtErrCode : Integer;       //common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/
	m_3GVConfDev       : DeviceID_t;
	m_list             : Acs_3GVConf_LayoutList;
	m_PrivData         : PrivateData_t; //private data*/
end;

Type
  Acs_GetLayout_Evt = record
	m_AcsEvtHead   : ACS_EVT_HEAD;    //acs event head*/
	m_AcsGetLayout : Acs_GetLayout_Data;  //acs Get Layout event data*/
end;

Type
  Acs_SetLayout_Data = record
	m_s32AcsEvtState   : Integer;       //common: acs event state, 1: success; 0: failed*/
	m_s32AcsEvtErrCode : Integer;       //common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/
	m_3GVConfDev       : DeviceID_t;
	m_PrivData         : PrivateData_t;
end;

Type
  Acs_SetLayout_Evt = record
	m_AcsEvtHead   : ACS_EVT_HEAD;       //acs event head*/
	m_AcsSetLayout : Acs_SetLayout_Data; //acs Set Layout event data*/
end;

Type
  Acs_GetVisibleList_Data = record
	m_s32AcsEvtState   : Integer;       //common: acs event state, 1: success; 0: failed*/
	m_s32AcsEvtErrCode : Integer;       //common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/
	m_3GVConfDev       : DeviceID_t;
	m_list             : Acs_3GVConf_VisibleList;
	m_PrivData         : PrivateData_t; //private data*/
end;

Type
  Acs_GetVisibleList_Evt = record
	m_AcsEvtHead        : ACS_EVT_HEAD;             //acs event head*/
	m_AcsGetVisibleList : Acs_GetVisibleList_Data;  //acs Get Visible List event data*/
end;

Type
  Acs_SetVisibleList_Data = record
	m_s32AcsEvtState   : Integer;       //common: acs event state, 1: success; 0: failed*/
	m_s32AcsEvtErrCode : Integer;       //common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/
	m_3GVConfDev       : DeviceID_t;
	m_PrivData         : PrivateData_t; //private data*/
end;

Type
  Acs_SetVisibleList_Evt = record
	m_AcsEvtHead        : ACS_EVT_HEAD;             //acs event head*/
	m_AcsSetVisibleList : Acs_SetVisibleList_Data;  //acs Set Visible List event data*/
end;

Type
  Acs_3GVConfStop_Data = record
	m_s32AcsEvtState    : Integer;         //common: acs event state, 1: success; 0: failed*/
	m_s32AcsEvtErrCode  : Integer;       //common: acs event errcode ,reference XMS_ERROR_CODE_DEF*/
	m_3GVConfDev        : DeviceID_t;
	m_PrivData          : PrivateData_t;
end;

Type
  Acs_3GVConfStop_Evt = record
	m_AcsEvtHead : ACS_EVT_HEAD;              //acs event head*/
	m_Acs3GVConfStop : Acs_3GVConfStop_Data;  //acs 3G VConf Stop event data*/
end;

Type
  Acs_IO_Evt = record
	m_AcsEvtHead : ACS_EVT_HEAD; //acs event head*/
	m_AcsIOData  : Acs_IO_Data;  //acs io event*/
end;

Type
  Acs_LicenseQuery_Data = record
	m_u8ModuleID    : Byte;        //license alarm Board module ID*/
	m_u16LicLeftDay : Word;        //license alarm Board left license days,0: No license or license overdue;100:license forever; else: left license days*/
	m_Rfu1          : ShortInt;
end;

Type
  Acs_LicenseQuery_Evt = record
	m_AcsEvtHead       : ACS_EVT_HEAD;          //acs event head*/
	m_LicenseQueryData : Acs_LicenseQuery_Data; //universal failure confirmation event*/
end;

Type
  Acs_UniFailure_Evt = record
	m_AcsEvtHead     : ACS_EVT_HEAD;        //acs event head*/
	m_UniverFailData : Acs_UniFailure_Data; //universal failure confirmation event*/
end;

Type
  Acs_FaxProc_Data = record
	m_s32AcsEvtState   : Integer;   //acs event state*/
	m_s32AcsEvtErrCode : Integer;   //acs event errcode*/
	m_u8ErrorStep      : Byte;      //error state of last fax operation*/
	m_u8T30SendState   : Byte;      //the state the T30 command just sent*/
	m_u8RecvT30Cmd     : Byte;      //the T30 command just received*/
	m_u8Rfu1           : Byte;      //Reserved*/
	m_u16TotalPages    : Word;      //total pages,send: sending total pages successfully  ;rev: receiving total pages successfully*/
  m_s8RemoteID       : Array[0..ACS_REMOTEID_MAX_LEN-1] of ShortInt; //Remote ID*/
	m_u8Rfu2           : Array[0..1] of Byte;
	m_PrivData         : PrivateData_t;
end;

Type
  Acs_FaxProc_Evt = record
	m_AcsEvtHead     : ACS_EVT_HEAD;     //acs event head*/
	m_AcsFaxProcData : Acs_FaxProc_Data; //acs fax proc data*/
end;

Type
  ITP_3GPP_PARAM_CFG = record
  m_u8AudioDecodeType     : Byte;       //audio decode type*/
  m_u8AudioFrameType      : Byte;       //audio frame type,reference XMS_AUDIO_AMR_FRAME_TYPE*/
  m_u16AudioDecoderCfgLen : Word;       //audio decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
  m_u8AudioDecoderCfg     : Array[0..ACS_MAX_DECODER_CFG_LEN-1] of Byte;  //audio decoder cfg*/
  m_u8AudioProfiles       : Byte;       //audio profiles?*/
  m_u8AudioLevel          : Byte;		    //audio level ?*/
  m_Rfu1                  : Array[0..1] of Byte;

  m_u8VideoDecodeType     : Byte;       //video decode type*/
  m_u8VideoFrameRate      : Byte;       //video frame rate 10 ~ 30*/
  m_u16VideoDecoderCfgLen : Word;       //video decoder cfg length,1~ACS_MAX_DECODER_CFG_LEN*/
  m_u8VideoDecoderCfg     : Array[0..ACS_MAX_DECODER_CFG_LEN-1] of Byte;  //video decoder cfg?*/
  m_u8VideoProfiles       : Byte;       //video profiles?*/
  m_u8VideoLevel          : Byte;       //video level?*/
  m_Rfu2                  : Array[0..1] of Byte;

  m_u32TrackNums          : DWORD;      //track numbers*/
  m_u16AudioMaxBitRate    : Word;
  m_u16AudioAverageBitRate: Word;
  m_u32AudioBitMask       : DWORD;
  m_u16VideoMaxBitRate    : Word;
  m_u16VideoAverageBitRate: Word;
  m_u32VideoBitMask       : DWORD;
  m_u16VideoWidth         : Word;
  m_u16VideoHeight        : Word;
end;

Type
  CmdParamData_324CH_t = record
	m_u8Channel_Enable : Byte;		// channel enable flag, 1 - enable, 0 - disable*/
	
	m_u8AudioSRC1_Ctrl : Byte;		// audio channel source 1 type */
	m_u8AudioSRC2_Ctrl : Byte;		// audio channel source 2 type */
	m_u8VideoSRC1_Ctrl : Byte;		// video channel source type */
	m_u16AudioSRC1_ID  : Word;		// audio channel source 1 id */
	m_u16AudioSRC2_ID  : Word;		// audio channel source 2 id */
	m_u16VideoSRC1_ID  : Word;		// video channel source id */

	m_u8AudioInDecodeFlag  : Byte;	// 1 - input decode, 0 - no decode */
	m_u8AudioOutEncodeFlag : Byte;  // 1 - output encode, 0 - no encode */
	m_u8AudioInCodec  : Byte;		// audio input codec */
	m_u8AudioOutCodec : Byte;		// audio output codec */
	m_u8VideoInCodec  : Byte;		// video input codec */
	m_u8VideoOutCodec : Byte;		// video output codec */
end;

Type
  Evt_H245_OLC = record
	u8ChannelNumber : Byte; // logical channel number
	u8Direction     : Byte;	// transmit or receive
	u8Codec         : Byte;	// codec type
	u8DecoderConfigInfoLen : Byte;	//decoder Config Length
	s8DecoderConfigInfo    : Array[0..MAX_DECODER_CFG_INFO-1] of Byte;
end;

Type
  Evt_H245_CLC = record
	u8ChannelNumber : Byte;     // logical channel number
	u8Direction     : Byte;	    // transmit or receive
	u8Reserved      : Array[0..1] of Byte;
end;

Type
  Evt_H245_SIG_PDU = record
	m_u8H245SigPdu : Array[0..ACS_MAX_H245_SIG_PDU_LEN-1] of Byte;		//* H.245 signal data */
end;

Type
  H245_UII = record
	m_u8Type   : Byte;		// type=1: send signal, type=2: send str, type=3: send signal and str */
	m_s8Signal : ShortInt;
	str        : Array[0..125] of ShortInt;
end;

Type
  ITP_3G_FaxToneStruct_t = record
	m_u16ChanEnable : Word;  // 1: enable; 0: disable
end;

Type
  ITP_3G_FaxToneEventStruct_t = record
	m_u16ChanState : Word;  //1￡ofax_tone; 0: voice tone
end;

Type
  Acs_SS7RawFrame_Data = record
	m_u8UserType : Byte; //SS7 frame user type,reference XMS_SS7_FRAME_USER_TYPE*/
	m_u8LinkType : Byte; //SS7 frame link type,reference XMS_SS7_FRAME_LINK_TYPE*/
	m_u8InfoType : Byte; //SS7 frame info type,reference XMS_SS7_FRAME_INFO_TYPE*/
	m_u8InfoLen  : Byte; //SS7 frame info len*/
	m_u8Rfu1     : Array[0..3] of Byte;
	m_u8Info     : Array[0..254] of Byte; //SS7 frame info*/
	m_u8Rfu2     : Byte;
end;

Type
  Acs_SS7RawFrame_Evt = record
	m_AcsEvtHead         : ACS_EVT_HEAD;         //acs event head*/
	m_AcsSS7RawFrameData : Acs_SS7RawFrame_Data; //acs ss7 ras frame data*/
end;

Type
  Acs_MediaPrivateExt_Data = record
	m_u32ExtType : DWORD;        //reference to XMS_PRIVATE_EXT_TYPE
	m_u8Buf      : Array[0..MAX_PATH-1] of Byte;
end;

Type
  Acs_MediaECM_OffSet = record
	m_u32Play_FileOffset : DWORD; //文件偏移,单位为1bytes
	m_u32Play_Max_Length : DWORD; //期望放音长度(单位：字节)
end;

Type
  Acs_MediaECM_CMD = record
	m_u16FrameNums : Word;
	m_u16Reserved  : Array[0..2] of Word;
	m_stOffSet     : Array[0..255] of Acs_MediaECM_OffSet;
end;

Type
  Acs_AnalogEM_CMD = record
	m_u8Channel_Enable : Byte;
	m_u8Type           : Byte;
	m_u8Tx_State       : Byte;
	m_u8Rx_State       : Byte;
end;

Type
  Acs_SysMon_Data = record
  m_u8ModuleType    : Byte;                       //Module type*/
  m_u8UnitID        : Byte;                       //Module unitid*/
  m_u16ModuleState  : Word;                       //Module state,reference XMS_SYSMON_MODSTATE*/
  m_s8IPAddress     : Array[0..31] of ShortInt;   //Module IP address*/
  m_u32Port         : DWord;                      //Module port*/
  m_s8Rfu           : Array[0..15] of ShortInt;   //rfu*/
end;

Type
  Acs_SysMon_Evt = record
	m_AcsEvtHead    : ACS_EVT_HEAD;     //acs event head*/
	m_AcsSysMonData : Acs_SysMon_Data;  //acs fax proc data*/
end;

Type
  Acs_VoIP_Regist_Evt = record
  m_AcsEvtHead : ACS_EVT_HEAD;
  m_AcsRegist  : Acs_VoIP_Regist;
end;

Type
  Acs_VoIP_Regist_State_Evt = record
  m_AcsEvtHead : ACS_EVT_HEAD;
  m_AcsRegistState : Acs_VoIP_REGSTATE;
end;

Type
  Acs_VoIP_Regist_Response_Evt = record
  m_AcsEvtHead    : ACS_EVT_HEAD;
  m_AcsRegistResp : Acs_VoIP_Regist_Response;
end;

Type
  Acs_VoIP_ReferResult_Evt = record
  m_AcsEvtHead : ACS_EVT_HEAD;
  m_AcsReferResult : Acs_VoIP_ReferResult;
end;

Type
  Acs_VoIP_MediaInfo_Evt = record
  m_AcsEvtHead : ACS_EVT_HEAD;
  m_AcsMediaInfo : Acs_VoIP_MediaInfo;
end;

Type
  Acs_VoIP_RTPSESSION_Evt = record
  m_AcsEvtHead    : ACS_EVT_HEAD;
  m_AcsRtpSession : Acs_VoIP_RTPSESSION;
end;

Type
  Acs_VoIP_RTPADDR_Evt = record
  m_AcsEvtHead : ACS_EVT_HEAD;
  m_AcsRtpAddr : Acs_VoIP_RTPADDR;
end;

Type
  Acs_VoIP_RTCPADDR_Evt = record
  m_AcsEvtHead : ACS_EVT_HEAD;
  m_AcsRtcpAddr : Acs_VoIP_RTPADDR;
end;

Type
  Acs_VoIP_RTPCODEC_Evt = record
  m_AcsEvtHead : ACS_EVT_HEAD;
  m_AcsRtpCodec : Acs_VoIP_RTPCODEC;
end;

Type
  Acs_UserDef_Evt = record
	m_AcsEvtHead : ACS_EVT_HEAD;     //acs event head*/
  m_UsrEvtHead : UserEvt_Head_t;   //User self-define event head*/
end;

Type
  Acs_ModRelate_Mod = record
  m_u8ModuleType : Byte;           //Module type*/
  m_u8UnitID     : Byte;           //Module unitid*/
	m_u8Flag       : Byte;           //Relate flag, 0:upper module; 1:lower module
  m_s8Rfu1       : ShortInt;       //rfu1
  m_s8IPAddress  : Array[0..31] of ShortInt;    //Module IP address
  m_u32Port      : DWORD;          //Module port*/
  m_s8Rfu2       : Array[0..3] of ShortInt;     //rfu2
end;

Type
  Acs_ModRelate_Data = record
	m_u8ModCount     : Byte;         //Relate module count
	m_u8SrcModType   : Byte;
	m_u8SrcModUnitID : Byte;
	m_rfu1           : ShortInt;
  m_RelateMod      : Array[0..63] of Acs_ModRelate_Mod; //Relate module info
end;

Type
  Acs_ModRelate_Evt = record
	m_AcsEvtHead       : ACS_EVT_HEAD;       //acs event head
	m_AcsModRelateData : Acs_ModRelate_Data; //acs fax proc data
end;

Type
  Acs_VoIPMon_Data = record
	m_u32DataLen : Integer;
	m_u8MonData  : Array[0..ITP_VOIP_MONDATA_MAX-1] of Byte;     //VoIP Mon data
end;

Type
  Acs_VoIPMon_Evt = record
	m_AcsEvtHead     : ACS_EVT_HEAD;     //acs event head
	m_AcsVoIPMonData : Acs_VoIPMon_Data; //acs VoIP mon data
end;

Type
  ACS_Digital_PortState_Data = record
	m_u8Lost_signal       : Byte;	    //1:无信号，0：有信号
	m_u8Fas_align         : Byte;	    //0：同步，1：失步
	m_u8Mf_align          : Byte; 	  //0：同步，1：失步
	m_u8Crc4_align        : Byte; 	  //0：同步，1：失步
	m_u8Remote_alarm      : Byte; 	  //0：无告警，1：远端告警
	m_u8Remote_MF_alarm   : Byte;	    //0：无告警，1：远端告警
	m_u8Rx_level          : Byte;	    //0-15: *(-2.5db)
	m_u8Tx_open           : Byte;	    //1:open circuit,
	m_u8Tx_overlimit      : Byte;	    //1:current over limit
	m_u8Port_Current_State: Byte;	    //0: error state; 1: normal working state
	m_u8Port_Normal_Count : Byte;	    //seconds of digital port normal working
	m_u8Port_Error_Count  : Byte;	    // seconds of digital port error
	m_u32total_seconds    : DWORD;	  //统计总时间
	m_u32RLOS_seconds     : DWORD;	  //接收失步总秒数
	m_u32LRCL_seconds     : DWORD;	  //接收无信号总秒数
	m_u32RUA1_seconds     : DWORD;	  //接收全1信号总秒数
	m_u32RRA_seconds      : DWORD;	  //远端告警总秒数
	m_u32RDMA_seconds     : DWORD;	  //远端CAS复帧告警总秒数
	m_u32ILUT_seconds     : DWORD;	  //接收电平过低总秒数
	m_u32JALT_seconds     : DWORD;	  //抖动超限总秒数
	m_u32TOCD_seconds     : DWORD;	  //发送开路错误总秒数
	m_u32TCLE_seconds     : DWORD;	  //发送短路错误总秒数
	m_u32RSLIP_seconds    : DWORD;	  //接收滑码错误总秒数
	m_u32TSLIP_seconds    : DWORD;	  //发送滑码错误总秒数
	m_u32LCVCR_count      : DWORD;	  //接收线路码型错误总计数
	m_u32PCVCR_count      : DWORD;	  //接收CRC4错误总计数
	m_u32FOSCR_count      : DWORD;	  //接收FAS错误总计数
	m_u32EBCR_count       : DWORD;		//远端CRC4 E-BIT总计数
	m_u32HDLC1_Tx_packets : DWORD;	  //HDLC1发送包计数
	m_u32HDLC1_Rx_goodpk  : DWORD;	  //HDLC1接收正确包计数
	m_u32HDLC1_Rx_badpk   : DWORD;		//HDLC1接收错误包计数
	m_u32HDLC2_Tx_packets : DWORD;	  //HDLC2发送包计数
	m_u32HDLC2_Rx_goodpk  : DWORD;	  //HDLC2接收正确包计数
	m_u32HDLC2_Rx_badpk   : DWORD;		//HDLC2接收错误包计数
	m_u8E1Type            : Byte;		  //E1 type*/
	m_u8Rfu               : Array[0..2] of Byte;
end;

Type
  ACS_Digital_PortState_Evt = record
  m_AcsEvtHead              : ACS_EVT_HEAD;
  m_AcsDigitalPortStateData : ACS_Digital_PortState_Data;
end;

Type
  ACS_Clock_RefSrc_State_Data = record
  m_u8ModuleID  : Byte;            //The Module ID Of DSP
  m_u8E1ID      : Byte;            //The E1 ID Of A DSP
  m_u8State     : Byte;            //The E1's Master Clock Ref Source Of A DSP, Reference to XMS_CLK_STATE_TYPE
	m_u8ClockType : Byte;            //Keygoe current clock type is slave or master,Reference XMS_BOARD_CLOCK_TYPE
  m_u8Ref       : Array[0..3] of Byte;
end;

Type
  ACS_Clock_RefSrc_State_Evt = record
    m_AcsEvtHead              : ACS_EVT_HEAD;
    m_AcsClockRefSrcStateData : ACS_Clock_RefSrc_State_Data;
end;

Type
  Acs_VoIP_SIP_User_Agent = record
	m_s8UserAgent : Array[0..39] of ShortInt;	  // Sip User Agent Name with version No
end;

Type
  Acs_VoIP_Call_Diversion_Info = record
	m_s8Diversion : Array[0..63] of ShortInt;	  // Sip Call Diversion URL
	m_s8Reason    : Array[0..15] of ShortInt;		// Sip Call Diversion Reason
end;

Type XMS_DRS_CALL_DIRECT_DEF =
(
	XMS_DRS_CALL_DIRECT_CALL_IN           = 0,
	XMS_DRS_CALL_DIRECT_CALL_OUT          = 1
);

//Event filter mask
Type XMS_IOEVT_MASK_TYPE =
(
	XMS_IOEVT_MASK_GTD              = $0001,
	XMS_IOEVT_MASK_FSK              = $0002,
	XMS_IOEVT_MASK_MR2F             = $0004,
	XMS_IOEVT_MASK_MR2B             = $0008
);

Type XMS_MEDIA_IO_TYPE =
(
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
	XMS_IO_TYPE_DRS                 = 11
);

Type XMS_MEDIA_ERR_CODE =
(
	XMS_ERR_CODE_OK                   = $00,
	XMS_ERR_CODE_APPSTOP              = $01,
	XMS_ERR_CODE_GTD                  = $02,
	XMS_ERR_CODE_OPENFILE_FAILED      = $03,
	XMS_ERR_CODE_WREADFILE_FAILED     = $04,
	XMS_ERR_CODE_CH_MISSING           = $05,
	XMS_ERR_CODE_EXE_FAILED           = $06,
	XMS_ERR_CODE_BUILD_INDEX_OK       = $07,
	XMS_ERR_CODE_PLAY_QUEUE_FULL      = $08,
	XMS_ERR_CODE_3G_AUDIO_OK          = $09,
	XMS_ERR_CODE_3G_VIDEO_OK          = $0A,
	XMS_ERR_CODE_BUILD_INDEX_FAILED   = $0B,
	XMS_ERR_SYSTEM_OVERLOAD           = $0C
);

//It will be replaced by XMS_CLK_STATE_TYPE later from V3.0.0
Type XMS_CLK_RS_STATE_TYPE =
(
	XMS_CLK_RS_STATE_MASTER_CLOCK_RS_SET       = 01,    //Set Master Clock Ref Source
	XMS_CLK_RS_STATE_MASTER_CLOCK_RS_RELEASE   = 02     //Release Master Clock Ref Source
);


Type XMS_CLK_STATE_TYPE =
(
	XMS_CLK_STATE_SET               = 01,    // Set master/slave clock
	XMS_CLK_STATE_RELEASE           = 02     // Release master/slave clock*
);

Type XMS_VOIP_IO_TYPE =
(
	XMS_IO_TYPE_VOIP_H245UII        = 1,  // VoIP H.245 UserInputIndication Event */
	XMS_IO_TYPE_VOIP_SIPINFO        = 2,  // VoIP SIP INFO Event */
	XMS_IO_TYPE_VOIP_RTPDTMF        = 3,  // VoIP RTP DTMF Event */
	XMS_IO_TYPE_VOIP_RTPTONE        = 4,  // VoIP RTP TONE */
	XMS_IO_TYPE_VOIP_FAXSTART       = 5,  // VoIP start fax mode (t.38 or t.30 pass-thru) */
	XMS_IO_TYPE_VOIP_FAXSTOP        = 6,  // VoIP stop fax mode(t.38 or t.30 pass-thru) */
	XMS_IO_TYPE_VOIP_REGSTATE       = 7,  // VoIP Registration State */
	XMS_IO_TYPE_VOIP_REGREQUEST     = 8,  // VoIP Registration Request */
	XMS_IO_TYPE_VOIP_REGRESPONSE    = 9,  // VoIP Registration Response */
	XMS_IO_TYPE_VOIP_TRANSFER       = 10, // VoIP Device Transfer */
	XMS_IO_TYPE_VOIP_SIPREG         = 11, // VoIP SIP Register */
	XMS_IO_TYPE_VOIP_SIPUNREG       = 12, // VoIP SIP Unregister */
	XMS_IO_TYPE_VOIP_REFER			    = 13, // Voip SIP Refer */
	XMS_IO_TYPE_VOIP_REFERRESPONSE	= 14, // Voip SIP Refer Response */
	XMS_IO_TYPE_VOIP_FORWARD		    = 15, // Voip SIP Forward call */
	XMS_IO_TYPE_VOIP_REFER_NOTIFY	  = 16, // VoIP SIP Send Refer Notify to Subscribe
	XMS_IO_TYPE_VOIP_CALLMODIFY		  = 17  // VoIP SIP Call Modified */
);

Type XMS_DCH_IO_TYPE =
(
	XMS_IO_TYPE_DCH_I_FRAME         = 1,
	XMS_IO_TYPE_DCH_UI_FRAME        = 2,
	XMS_IO_TYPE_DCH_DEBUG           = 3
);

Type XMS_LINESIDEE1_IO_TYPE =
(
	XMS_IO_TYPE_LINESIDEE1          = 12
);

Type XMS_ANALOG_INTERFACE_STATE =
(
	XMS_ANALOG_USER_CH_OFFHOOK             = 0,
	XMS_ANALOG_USER_CH_ONHOOK              = 1,	
	XMS_ANALOG_USER_CH_FLASH               = 2
);

Type XMS_ANALOG_INTERFACE_STATE2 =
(
	XMS_ANALOG_TRUNK_CH_RING               = 0, 
	XMS_ANALOG_TRUNK_CH_POSITEX_POLARITY   = 1, 
	XMS_ANALOG_TRUNK_CH_NEGATIVE_POLARITY  = 2, 
	XMS_ANALOG_TRUNK_CH_LOOPDROP           = 3,
	XMS_ANALOG_TRUNK_CH_NOLOOP             = 4, 
	XMS_ANALOG_TRUNK_CH_FLASH              = 8
);

Type XMS_SIG_RAWDATA_EVT_TYPE =
(
	XMS_SIG_RAWDATA_EVT_BASE         = $FF00
);

Type ACS_MASTER_STATE =
(
	ACS_STATE_SLAVE                  = 0,
	ACS_STATE_MASTER                 = 1
);

Type ACS_WORK_STATE =
(
	ACS_STATE_WORK_FAILURE           = 0,
	ACS_STATE_WORKING                = 1
);

Type XMS_SS7_SN_STATUS =
(
	XMS_SN_PAUSE      = 01, // Pause
	XMS_SN_RESUME     = 02, // Resume
	XMS_SN_CONG       = 03, // Network Congested
	XMS_SN_RMTUSRUNAV = 04, // Remote User Unavailable
	XMS_SN_RSTBEG     = 05, // Restart Begins
	XMS_SN_RSTEND     = 06, // Restart Ends
	XMS_SN_STPCONG    = 07, // Stop Network Congestion
	XMS_SN_RESTRICT   = 08, // Restrict
	XMS_SN_LNK_CHANGE = 09  // Link status changed
);

Type XMS_SS7_MSG_TYPE =
(
	XMS_SS7_MSG_DATA   = 01,
	XMS_SS7_MSG_CMD    = 02,
	XMS_SS7_MSG_STATUS = 03
);


Type XMS_SS7_USER_TYPE =
(
	XMS_SS7_USER_TYPE_SCCP = 03,
	XMS_SS7_USER_TYPE_TUP  = 04,
	XMS_SS7_USER_TYPE_ISUP = 05
);


Type XMS_SS7_LINK_TYPE =
(
	XMS_SS7_LINK_TYPE_ITU  = 02,
	XMS_SS7_LINK_TYPE_CHINA= 04
);

Type XMS_ANALOGTRUNK_PARAM_TYPE =
(
	ANALOGTRUNK_PARAM_UNIPARAM = 0,
	ANALOGTRUNK_PARAM_SETFLASH = 1,
	ANALOGTRUNK_PARAM_UNSETUNIPARAM = 2 ,//added by jerry for UnSet UniParam(id = 0 )....
	ANALOGTRUNK_PARAM_UNBINDVOC     = 3 ,//Added by jerry For UnBind Voc From AnalogTrunk
  ANALOGTRUNK_PARAM_READSN        = 4 ,//get TRUNK's SN
	ANALOGTRUNK_PARAM_GET_VOLTAGE   = 5 //get TRUNK's voltage
);

Type XMS_ANALOGUSER_PARAM_TYPE =
(
	ANALOGUSER_PARAM_UNIPARAM      = 0,	
	ANALOGUSER_PARAM_UNBINDVOC     = 3 ,//Added by jerry For UnBind Voc From AnalogUser
  ANALOGUSER_PARAM_READSN        = 4, //get AnalogUser's SN
	ANALOGUSER_PARAM_GET_VOLTAGE   = 5 //Get AnalogUser's voltage
);

Type XMS_PLAY_TYPE =
(
	XMS_PLAY_TYPE_FILE               = 0,
	XMS_PLAY_TYPE_INDEX              = 1,
	XMS_PLAY_TYPE_FILE_QUEUE         = 2,
	XMS_PLAY_TYPE_INDEX_QUEUE        = 3
);

Type XMS_EVT_TYPE =
(
  XMS_EVT_OPEN_STREAM                     = ((1 SHL 16)+ 01),
	XMS_EVT_QUERY_DEVICE                    = ((1 SHL 16)+ 02),
	XMS_EVT_QUERY_DEVICE_END                = ((1 SHL 16)+ 03),
	XMS_EVT_OPEN_DEVICE                     = ((1 SHL 16)+ 04),
	XMS_EVT_CLOSE_DEVICE                    = ((1 SHL 16)+ 05),
	XMS_EVT_RESET_DEVICE                    = ((1 SHL 16)+ 06),
	XMS_EVT_DEVICESTATE                     = ((1 SHL 16)+ 07),
	XMS_EVT_SETDEV_GROUP                    = ((1 SHL 16)+ 08),
	XMS_EVT_SETPARAM                        = ((1 SHL 16)+ 09),
	XMS_EVT_GETPARAM                        = ((1 SHL 16)+ 10),
	XMS_EVT_QUERY_ONE_DSP_START             = ((1 SHL 16)+ 11),
	XMS_EVT_QUERY_ONE_DSP_END               = ((1 SHL 16)+ 12),
	XMS_EVT_QUERY_REMOVE_ONE_DSP_START      = ((1 SHL 16)+ 13),
	XMS_EVT_QUERY_REMOVE_ONE_DSP_END        = ((1 SHL 16)+ 14),
	XMS_EVT_OPEN_STREAM_EXT                 = ((1 SHL 16)+ 15),
	XMS_EVT_LICENSE_QUERY                   = ((1 SHL 16)+ 16),
	XMS_EVT_CLOSE_STREAM_EXT                = ((1 SHL 16)+ 17),
	XMS_EVT_MASTER_STATE                    = ((1 SHL 16)+ 19),
	XMS_EVT_SLAVE_WORK_STATE			          = ((1 SHL 16)+ 20),
  XMS_EVT_E1STATE                         = ((1 SHL 16)+ 32),
  XMS_EVT_CTBUS_CLK_REF_SRC_STATE         = ((1 SHL 16)+ 48),
	XMS_EVT_USER_DEF                        = ((1 SHL 16)+ 224),
	XMS_EVT_BAKSYS_STOP                     = ((1 SHL 16)+ 240),
	XMS_EVT_ACS_TIMER                       = ((1 SHL 16)+ 255),
			
	XMS_EVT_CALLOUT							            = ((2 SHL 16)+ 01),
	XMS_EVT_CALLIN							            = ((2 SHL 16)+ 02),
	XMS_EVT_ALERTCALL		                    = ((2 SHL 16)+ 03),
	XMS_EVT_ANSWERCALL		                  = ((2 SHL 16)+ 04),
	XMS_EVT_LINKDEVICE				              = ((2 SHL 16)+ 05),
	XMS_EVT_UNLINKDEVICE					          = ((2 SHL 16)+ 06),
	XMS_EVT_CLEARCALL						            = ((2 SHL 16)+ 07),
	XMS_EVT_ANALOG_INTERFACE                = ((2 SHL 16)+ 08),
	XMS_EVT_CAS_MFC_START					          = ((2 SHL 16)+ 09),
	XMS_EVT_CAS_MFC_END						          = ((2 SHL 16)+ 10),
	XMS_EVT_SENDSIGMSG						          = ((2 SHL 16)+ 11),
	XMS_EVT_SIGMON       					          = ((2 SHL 16)+ 12),
	XMS_EVT_3G324M       				          	= ((2 SHL 16)+ 13),
	XMS_EVT_CTX_REG                         = ((2 SHL 16)+ 14),
	XMS_EVT_CTX_LINK                        = ((2 SHL 16)+ 15),
	XMS_EVT_CTX_APPDATA                     = ((2 SHL 16)+ 16),
	XMS_EVT_DRS_CALL_NUMS                   = ((2 SHL 16)+ 17),
	XMS_EVT_SS7RawFrame						          = ((2 SHL 16)+ 32),
	XMS_EVT_SS7SendRawFrame					        = ((2 SHL 16)+ 33),

	XMS_EVT_JOINTOCONF					            = ((3 SHL 16)+ 01),
	XMS_EVT_LEAVEFROMCONF					          = ((3 SHL 16)+ 02),
	XMS_EVT_CLEARCONF					              = ((3 SHL 16)+ 03),
		
	XMS_EVT_SET_PAYLOAD				              = ((4 SHL 16)+ 01),
	XMS_EVT_SET_RTPADDR				              = ((4 SHL 16)+ 02),
	XMS_EVT_SET_RTCPADDR				            = ((4 SHL 16)+ 03),
	XMS_EVT_SET_RTPCODEC				            = ((4 SHL 16)+ 04),
	XMS_EVT_SET_MEDIAINFO				            = ((4 SHL 16)+ 05),
	XMS_EVT_REFER_RESULT				            = ((4 SHL 16)+ 06),
	XMS_EVT_REGIST				    	            = ((4 SHL 16)+ 07),
	XMS_EVT_REGIST_RESP				              = ((4 SHL 16)+ 08),

	XMS_EVT_PLAY			                      = ((5 SHL 16)+ 01),
	XMS_EVT_INITINDEX				                = ((5 SHL 16)+ 02),
	XMS_EVT_BUILDINDEX						          = ((5 SHL 16)+ 03),
	XMS_EVT_CONTROLPLAY				              = ((5 SHL 16)+ 04),
	XMS_EVT_RECORD							            = ((5 SHL 16)+ 05),
	XMS_EVT_CONTROLRECORD				            = ((5 SHL 16)+ 06),
	XMS_EVT_RECORDCSP   				            = ((5 SHL 16)+ 07),
	XMS_EVT_CONTROLRECORDCSP    		        = ((5 SHL 16)+ 08),
  XMS_EVT_3GPP_PLAY			                  = ((5 SHL 16)+ 09),
	XMS_EVT_3GPP_CONTROLPLAY		            = ((5 SHL 16)+ 10),
	XMS_EVT_3GPP_RECORD	    				        = ((5 SHL 16)+ 11),
	XMS_EVT_3GPP_CONTROLRECORD    		      = ((5 SHL 16)+ 12),
	XMS_EVT_PLAYCSPREQ 				              = ((5 SHL 16)+ 13),
	XMS_EVT_3GPP_INIT_INDEX                 = ((5 SHL 16)+ 14),
	XMS_EVT_3GPP_BUILD_INDEX                = ((5 SHL 16)+ 15),
	XMS_EVT_3GVCONF_JOIN				            = ((5 SHL 16)+ 16),
	XMS_EVT_3GVCONF_LEAVE				            = ((5 SHL 16)+ 17),
	XMS_EVT_3GVCONF_CLEAR				            = ((5 SHL 16)+ 18),
	XMS_EVT_3GVCONF_GETLAYOUT			          = ((5 SHL 16)+ 19),
	XMS_EVT_3GVCONF_SETLAYOUT			          = ((5 SHL 16)+ 20),
	XMS_EVT_3GVCONF_GETVISIBLELIST			    = ((5 SHL 16)+ 21),
	XMS_EVT_3GVCONF_SETVISIBLELIST			    = ((5 SHL 16)+ 22),
	XMS_EVT_3GVCONF_STOP				            = ((5 SHL 16)+ 23),

	XMS_EVT_SENDFAX			                    = ((6 SHL 16)+ 01),
	XMS_EVT_RECVFAX					                = ((6 SHL 16)+ 02),
			
	XMS_EVT_SENDIODATA					            = ((7 SHL 16)+ 01),
	XMS_EVT_RECVIODATA						          = ((7 SHL 16)+ 02),
		
	XMS_EVT_MODMONITOR				              = ((8 SHL 16)+ 01),
	XMS_EVT_DEV_TIMER						            = ((8 SHL 16)+ 02),
	XMS_EVT_MODRELATE				                = ((8 SHL 16)+ 03),
	XMS_EVT_VOIPMON  				                = ((8 SHL 16)+ 04),
	
	XMS_EVT_UNIFAILURE						          = ((9 SHL 16)+ 01)
);

Type XMS_DEVMAIN_TYPE =
(
  XMS_DEVMAIN_CONFIG               = 01,
	XMS_DEVMAIN_VOICE                = 02,
	XMS_DEVMAIN_FAX                  = 03,
	XMS_DEVMAIN_DIGITAL_PORT         = 04,
	XMS_DEVMAIN_INTERFACE_CH         = 05,
	XMS_DEVMAIN_DSS1_LINK            = 06,
	XMS_DEVMAIN_SS7_LINK             = 07,
	XMS_DEVMAIN_BOARD                = 08,
	XMS_DEVMAIN_CTBUS_TS             = 09,
	XMS_DEVMAIN_RTP                  = 10,
	XMS_DEVMAIN_MEDIAEX              = 11,
	XMS_DEVMAIN_CONFERENCE           = 12,
	XMS_DEVMAIN_VIDEO                = 13,
	XMS_DEVMAIN_CTX                  = 16,
	XMS_DEVMAIN_RTPX                 = 17,
	XMS_DEVMAIN_VOIP                 = 18,
	XMS_DEVMAIN_VIDEOCONF            = 31
);

Type XMS_INTERFACE_DEVSUB_TYPE =
(
	XMS_DEVSUB_BASE                       =  $0,
	XMS_DEVSUB_ANALOG_TRUNK               =  01,
	XMS_DEVSUB_ANALOG_USER                =  02,
	XMS_DEVSUB_ANALOG_HIZ                 =  03, 
	XMS_DEVSUB_ANALOG_EMPTY               =  04, 
	XMS_DEVSUB_E1_PCM                     =  05, 
	XMS_DEVSUB_E1_CAS                     =  06, 
	XMS_DEVSUB_E1_DSS1                    =  07, 
	XMS_DEVSUB_E1_SS7_TUP                 =  08,
	XMS_DEVSUB_E1_SS7_ISUP                =  09,
	XMS_DEVSUB_ANALOG_VOC2W			          =  10,
  XMS_DEVSUB_ANALOG_VOC4W			          =  11,
  XMS_DEVSUB_ANALOG_EM			            =  12,
  XMS_DEVSUB_ANALOG_MAG			            =  13,
  XMS_DEVSUB_E1_DCH				              =  14,
  XMS_DEVSUB_E1_BCH				              =  15,
  XMS_DEVSUB_UNUSABLE				            =  16,
	XMS_DEVSUB_HIZ_CAS				            =  17,
	XMS_DEVSUB_HIZ_PRI				            =  18,
	XMS_DEVSUB_HIZ_SS7					          =  19,
	XMS_DEVSUB_HIZ_PRI_LINK			          =  20,
	XMS_DEVSUB_HIZ_SS7_64K_LINK  		      =  21,
	XMS_DEVSUB_HIZ_SS7_2M_LINK    		    =  22,
	XMS_DEVSUB_SS7_LINK		                =  23,
	XMS_DEVSUB_LINESIDE		                =  24,
	XMS_DEVSUB_ANALOG_REC	                =  25,
	XMS_DEVSUB_HIZ_HDLC_N64K_LINK         =  26, 
	XMS_DEVSUB_SS7_2M_LINK                =  27, 
	XMS_DEVSUB_HIZ_HDLC                   =  28, 
	XMS_DEVSUB_DIGITAL_REC	              =  32
);

Type ERROR_CODE =
(
  ACSERR_LOADLIBERR              =01,
  ACSERR_BADPARAMETER            =02,
  ACSERR_NOSERVER                =03,
  ACSERR_MAXCONN_EXCEED          =04,
  ACSERR_BADHDL                  =05,
  ACSERR_FAILSEND                =06,
  ACSERR_LINKBROKEN              =07,
  ACSERR_NOMESSAGE               =08,
  ACSERR_GETRESFAIL              =09,
  ACSERR_NOSUPPORTCMD            =10,
  ACSERR_DEVICEERR               =11,
  ACSERR_CTX_REGOVERRUN     		 =12,
  ACSERR_CTX_REG_NAMEEXIS        =13,
  ACSERR_CTX_UNREG_NOREG		     =14,
  ACSERR_CTX_TRAN_NODEST		     =15,
  ACSERR_CTX_TRAN_NOSRC		       =16,
  ACSERR_CTX_LINK_FAIL           =17,
  ACSERR_CTX_APPDATA_NODEST      =18,
  ACSERR_CTX_APPDATA_NOSRC       =19,
  ACSERR_NOTMASTER               =20,
  ACSERR_PUTTEXTINPIC_PARAMERROR =20,
  ACSERR_PUTTEXTINPIC_OPENPICFAIL =21,
  ACSERR_PUTTEXTINPIC_SAVEPICFAIL =22
);

Type XMS_MEDIA_DEVSUB_TYPE =
(
	XMS_DEVSUB_MEDIA_VOC                 = $0,  //*voc device*/
	XMS_DEVSUB_MEDIA_324                 = $1,  //*324 device*/
	XMS_DEVSUB_MEDIA_RAW				         = $2	  //*Raw device*/
);

Type XMS_CTBUS_DEVSUB_TYPE =
(
	XMS_DEVSUB_CTBUS_LINK                 = $0, //*CTBus link ts*/
	XMS_DEVSUB_CTBUS_CTX                  = $1  //*CTBus CTX ts*/
);

Type XMS_E1_TYPE =
  (
	XMS_E1_TYPE_Analog30	            = 1,
	XMS_E1_TYPE_PCM31		              = 2,
	XMS_E1_TYPE_PCM30		              = 3,
	XMS_E1_TYPE_CAS			              = 4,
	XMS_E1_TYPE_PRI			              = 5,
	XMS_E1_TYPE_SS7_TUP_0_Link	      = 6,
	XMS_E1_TYPE_SS7_TUP_1_Link	      = 7,
	XMS_E1_TYPE_SS7_TUP_2_Link	      = 8,
	XMS_T1_TYPE_D4	                  = 9,
	XMS_T1_TYPE_ESF		                = 10,
	XMS_J1_TYPE_D4		                = 11,
	XMS_J1_TYPE_ESF		                = 12,
	XMS_SLC_TYPE_96    	              = 13,
	XMS_E1_TYPE_SS7_ISUP_0_Link	      = 14,
	XMS_E1_TYPE_SS7_ISUP_1_Link	      = 15,
	XMS_E1_TYPESS7_ISUP_2_Link	      = 16,
	XMS_E1_TYPE_6D25B		              = 17,
	XMS_E1_TYPE_1D30B                    = 18,
	XMS_E1_TYPE_11D20B                   = 19,
	XMS_E1_TYPE_HIZ_CAS                  = 20,
	XMS_E1_TYPE_HIZ_PRI                  = 21,
	XMS_E1_TYPE_HIZ_SS7                  = 22,
	XMS_E1_TYPE_HIZ_64K_SS7   	         = 23,
	XMS_E1_TYPE_HIZ_2M_SS7               = 24,
	XMS_E1_TYPE_LINESIDE                 = 25,
	XMS_E1_TYPE_HIZ_N64K_HDLC            = 26,
	XMS_E1_TYPE_2M_SS7									 = 27
);

Type XMS_BOARD_PARAM_TYPE =
(
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
	BOARD_PARAM_SET_RST_MASTER        = 13 //
  );

  //*E1 STATE BITS DEFINE*/
Type XMS_E1PORT_MASK_STATE =
(
	XMS_E1PORT_MASK_LOST_SIGNAL	     = $00000001,
	XMS_E1PORT_MASK_FAS_ALARM	       = $00000002,
	XMS_E1PORT_MASK_MFAS_ALARM	     = $00000004,
	XMS_E1PORT_MASK_CRC4_ALARM	     = $00000008,
	XMS_E1PORT_MASK_REMOTE_ALARM	   = $00000010,
	XMS_E1PORT_MASK_REMOTE_MF_ALARM	 = $00000020,
	XMS_E1PORT_MASK_TX_OPEN_ALARM	   = $00000040,
	XMS_E1PORT_MASK_TX_SHORT_ALARM	 = $00000080,
	XMS_E1PORT_MASK_RX_LEVEL	       = $00000F00,
	XMS_E1PORT_MASK_TYPE		         = $00FF0000
);

Type XMS_VOIP_PROTOCOL_TYPE =
(
	XMS_VOIP_PROTOCOL_H323           = $1, //*VoIP H323 protocol*/
	XMS_VOIP_PROTOCOL_SIP            = $2  //*VoIP SIP protocol*/
);

Type XMS_VOC_SRC_MODE =
(
	XMS_SRC_8K                       = $0,
	XMS_SRC_6K                       = $1,
	XMS_SRC_GTG                      = $2,
	XMS_SRC_FSK                      = $3,
	XMS_SRC_RTP                      = $4,
	XMS_SRC_FAX                      = $5,
	XMS_SRC_3GVIDEO                  = $6,
	XMS_SRC_11K                      = $7,
	XMS_SRC_FAX_ECM                  = $8
);

Type XMS_VOC_CODE_TYPE =
(
	XMS_Alaw_type                    = $0,
	XMS_Ulaw_type                    = $1,
	XMS_Vox_type                     = $2,
	XMS_Linear_8bit                  = $3,
	XMS_Linear_16bit                 = $4,
	XMS_Amr_type                     = $5,
	XMS_G723_type                    = $6,
	XMS_CODE_STREAM                  = $7
);

Type XMS_PLAYREC_STOP_MODE =
(
	XMS_Normal_Stop                  = $0,
	XMS_Single_Code                  = $1,
	XMS_Any_Code                     = $2
);

Type XMS_CSPREC_TYPE =
(
	XMS_CSPREC_NONE                  = $0,
	XMS_CSPREC_BARGEIN               = $1,
	XMS_CSPREC_NON_BARGEIN           = $2
);

Type XMS_CSPREC_PRIV_TYPE =
(
	XMS_CSPREC_PRIV_CMD              = $0
);

Type XMS_CSPREC_CMD_OPT =
(
	XMS_CSPREC_CMD_NORMAL            = $0,
	XMS_CSPREC_CMD_DIRECT            = $1
);

Type XMS_CONTROL_CSPREC_PRIV_TYPE =
(
	XMS_CONTROL_CSPREC_PRIV_CMD      = $0
);

Type XMS_CONTROL_CSPREC_CMD_OPT =
(
	XMS_CONTROL_CSPREC_CMD_NORMAL    = $0,
	XMS_CONTROL_CSPREC_CMD_DIRECT    = $1
);

Type XMS_BUILD_INDEX_TYPE =
(
	XMS_BUILD_INDEX_RAM              = $4,
	XMS_BUILD_INDEX_FILE             = $5
);

Type XMS_CFG_TYPE =
(
	XMS_CFG_TYPE_NON_INDEX           = $0,
	XMS_CFG_TYPE_INDEX               = $1
);

Type XMS_CTRL_PLAY_TYPE =
(
	XMS_STOP_PLAY                    = $0,
	XMS_PAUSE_PLAY                   = $1,
	XMS_RESUME_PLAY                  = $2,
	XMS_STEP_BACKWARD_PLAY           = $3,
	XMS_STEP_FORWARD_PLAY            = $4,

	XMS_CSP_STOP_PLAY                = $5,
	XMS_CSP_PAUSE_PLAY               = $6,
	XMS_CSP_RESUME_PLAY              = $7,
	XMS_CSP_STEP_BACKWARD_PLAY       = $8,
	XMS_CSP_STEP_FORWARD_PLAY        = $9,
	XMS_CSP_DELAY_STOP_PLAY          = $A
);

Type XMS_PLAY_GAIN_MODE =
(
	XMS_PLAY_GAIN_MODE_NOCHANGE     = $0,
	XMS_PLAY_GAIN_MODE_FIX          = $1,
	XMS_PLAY_GAIN_MODE_ALS          = $2,
	XMS_PLAY_GAIN_MODE_AGC          = $3
);

Type XMS_VOC_OUTPUT_TYPE =
(
	XMS_VOC_OUTPUT_SILENCE           = $0,
	XMS_VOC_OUTPUT_FROM_INPUT        = $1,
	XMS_VOC_OUTPUT_FROM_PLAY         = $2,
	XMS_VOC_OUTPUT_FROM_MIXER        = $3
);

Type XMS_MIXER_TYPE =
(
	XMS_MIXER_FROM_NULL              = $00,
	XMS_MIXER_FROM_INPUT             = $01,
	XMS_MIXER_FROM_PLAY              = $02,
	XMS_MIXER_FROM_CONF              = $03,
	XMS_MIXER_FROM_IP                = $04,
	XMS_MIXER_FROM_324               = $05,
	XMS_MIXER_FROM_RTPX              = $06
);

Type XMS_AGC_MODE =
(
	XMS_AGC_MODE_ALS		          = $00,
	XMS_AGC_MODE_AGC		          = $01
);

Type XMS_EC_REF =
(
	XMS_EC_REF_FROM_INPUT		        = $00,
	XMS_EC_REF_FROM_OUTPUT		      = $01
);

Type XMS_CONF_INPUT_OPT =
(
	XMS_CONF_INPUT_OPT_SILENCE        = $0,
	XMS_CONF_INPUT_OPT_NORMAL         = $1,
	XMS_CONF_INPUT_OPT_PLAY           = $2
);

Type XMS_CONF_OUTPUT_OPT =
(
	XMS_CONF_OUTPUT_OPT_SILENCE		    = $0,
	XMS_CONF_OUTPUT_OPT_NORMAL	      = $1,
	XMS_CONF_OUTPUT_OPT_SUM	          = $2
);

Type XMS_CTRL_RECORD_TYPE =
(
	XMS_STOP_RECORD                   = $0,
	XMS_PAUSE_RECORD                  = $1,
	XMS_RESUME_RECORD                 = $2,
	XMS_STEP_BACKWARD_RECORD          = $3,

	XMS_CSP_STOP_RECORD               = $4,
	XMS_CSP_PAUSE_RECORD              = $5,
	XMS_CSP_RESUME_RECORD             = $6,
	XMS_CSP_STEP_BACKWARD_RECORD      = $7,
	XMS_CSP_DELAY_STOP_RECORD         = $8
);

Type XMS_REC_DELAY_STOP_SWITCH  =
(
	XMS_REC_DELAY_STOP_DISABLE        = $0,
	XMS_REC_DELAY_STOP_ENABLE         = $1
);

Type XMS_REC_OPENFILE_TYPE =
(
	XMS_REC_FILE_TRUNC                = $0,
	XMS_REC_FILE_APPEND               = $1
);

Type XMS_AUDIO_TRACKS =
(
	XMS_AUDIO_TRACKS_MONO             = $1,
	XMS_AUDIO_TRACKS_STEREO           = $2
);

Type XMS_VIDEO_CODE_TYPE =
(
	XMS_VIDEO_CODE_TYPE_H263P        = $1,
    XMS_VIDEO_CODE_TYPE_H263       = $2,
    XMS_VIDEO_CODE_TYPE_MP4V       = $3,
	XMS_VIDEO_CODE_TYPE_H264         = $4
);

Type XMS_AUDIO_AMR_FRAME_TYPE =
(
	XMS_AMR_FRAME_TYPE_4_75              = $0,
	XMS_AMR_FRAME_TYPE_5_15              = $1,
	XMS_AMR_FRAME_TYPE_5_90              = $2,
	XMS_AMR_FRAME_TYPE_6_70              = $3,
	XMS_AMR_FRAME_TYPE_7_40              = $4,
	XMS_AMR_FRAME_TYPE_7_95              = $5,
	XMS_AMR_FRAME_TYPE_10_2              = $6,
	XMS_AMR_FRAME_TYPE_12_2              = $7,
	XMS_AMR_FRAME_TYPE_AMR_SID           = $8,
	XMS_AMR_FRAME_TYPE_GSM_EFR_SID       = $9,
	XMS_AMR_FRAME_TYPE_TDMA_EFR_SID      = $A,
	XMS_AMR_FRAME_TYPE_PDC_EFR_SID       = $B,
	XMS_AMR_FRAME_TYPE_RESERVED1         = $C,
	XMS_AMR_FRAME_TYPE_RESERVED2         = $D,
	XMS_AMR_FRAME_TYPE_RESERVED3         = $E,
	XMS_AMR_FRAME_TYPE_NO_DATA           = $F
);

Type XMS_CSPPLAY_DATA_TYPE =
(
	XMS_CSPPLAY_DATA_VOC                 = $0,
	XMS_CSPPLAY_DATA_VIDEO               = $1
);

Type XMS_PRIVATE_EXT_TYPE  =
(
        XMS_EXT_TYPE_PATH              = $01              //extend to path's size from 128 to 260
);

Type XMS_BOARD_PRIVATE_EXT_TYPE =
(
	XMS_BOARD_EXT_TYPE_NULL                = $00,             //nothing will excute
    XMS_BOARD_EXT_TYPE_CLOCK             = $01              //extend to main clock in keygoe system
);

//It will be replaced by XMS_BOARD_CLOCK_MODE later from V3.0.0*/
Type XMS_BOARD_EXT_CLOCK_TYPE =
(
	XMS_BOARD_EXT_CLOCK_NO_SET           = $00,             //extend to main clock in keygoe system
  XMS_BOARD_EXT_CLOCK_SET              = $01              //extend to main clock in keygoe system
);


Type XMS_BOARD_CLOCK_TYPE  =
(
  XMS_BOARD_EXT_CLOCK_TYPE_SLAVE         = $01,             //current board set slave clock to the peer CO
	XMS_BOARD_EXT_CLOCK_TYPE_MASTER        = $02              //current board set master clock to the peer CO
);

Type XMS_BOARD_CLOCK_MODE =
(
	XMS_BOARD_CLOCK_MODE_AUTO      = Integer(XMS_BOARD_EXT_CLOCK_NO_SET),     //clock set by Keygoe
	XMS_BOARD_CLOCK_MODE_MANUAL    = Integer(XMS_BOARD_EXT_CLOCK_SET)        //clock set by user-app
);

Type XMS_ANALOG_TRUNK_CALLERID_OPT =
(
	XMS_ANALOG_TRUNK_CALLERID_DISABLE      = $0,
	XMS_ANALOG_TRUNK_CALLERID_FSK          = $1,
	XMS_ANALOG_TRUNK_CALLERID_DTMF         = $2,
	XMS_ANALOG_TRUNK_CALLERID_FSKORDTMF    = $3
);

Type XMS_ANALOG_TRUNK_DIALTONE_DETECT_OPT =
(
	XMS_ANALOG_TRUNK_DIALTONE_DONTDETECT   = $0,
	XMS_ANALOG_TRUNK_DIALTONE_DETECT       = $1
);

Type XMS_ANALOG_TRUNK_CALLOUT_METHOD_OPT =
(
	XMS_ANALOG_TRUNK_CALLOUT_APP_FULLCONTROL     = $0,
	XMS_ANALOG_TRUNK_CALLOUT_NORMAL_PROGRESS     = $1,
	XMS_ANALOG_TRUNK_CALLOUT_POLARITY_REVERSE    = $2
);

Type XMS_ANALOG_USER_CALLERID_OPT =
(
	XMS_ANALOG_USER_CALLERID_DSIABLE            = $0,
	XMS_ANALOG_USER_CALLERID_FSK                = $1,
	XMS_ANALOG_USER_CALLERID_DTMF               = $2
);

Type XMS_ANALOG_USER_RINGCADENCE_TYPE =
(
	XMS_ANALOG_USER_RINGCADENCE_SINGLEPULSE    = $0,
	XMS_ANALOG_USER_RINGCADENCE_DOUBLEPULSE    = $1,
	XMS_ANALOG_USER_RINGCADENCE_TRIPLEPULSE    = $2
);

Type XMS_ANALOG_USER_CALLIN_METHOD_TYPE =
(
	XMS_ANALOG_USER_CALLIN_METHOD_APP_FULLCONTROL    = $0,
	XMS_ANALOG_USER_CALLIN_METHOD_AUTO_RECVCALLEE    = $1
);

Type XMS_FAX_MODEM_TYPE =
(
	XMS_F48_Modem                        = $0,
	XMS_F96_Modem                        = $1,
	XMS_F144_Modem                       = $2
);

Type XMS_FAX_BPS_TYPE =
(
	XMS_BPS_2400                         = $0,
	XMS_BPS_4800                         = $1,
	XMS_BPS_7200                         = $2,
	XMS_BPS_9600                         = $3,
	XMS_BPS_12000                        = $4,
	XMS_BPS_14400                        = $5
);

Type XMS_FAX_T4_TYPE =
(
	XMS_T4_Low_Dencity                   = $0,
	XMS_T4_High_Dencity                  = $1,
	XMS_T4_MH_Encode                     = $0,
	XMS_T4_MR_Encode                     = $1
);

Type XMS_FAX_LINE_PIXEL_TYPE =
(
	XMS_Line_Pixel_1728                  = $0,
	XMS_Line_Pixel_2048                  = $1,
	XMS_Line_Pixel_2432                  = $2,
	XMS_Line_Pixel_3456                  = $3,
	XMS_Line_Pixel_4096                  = $4,
	XMS_Line_Pixel_4864                  = $5
);

Type XMS_FAX_PAGE_LENGTH =
(
	XMS_Page_Length_A4                   = $0,
	XMS_Page_Length_B4                   = $1,
	XMS_Page_Length_Unlinit              = $2
);

Type XMS_FAX_SCANLINE_TIME  =
(
	XMS_Scanline_Time_0                  = $0,
	XMS_Scanline_Time_5                  = $1,
	XMS_Scanline_Time_10                 = $2,
	XMS_Scanline_Time_20                 = $3,
	XMS_Scanline_Time_40                 = $4
);

Type XMS_FAX_HOSTCTRL_TYPE =
(
	XMS_Fax_Null                         = $0,
	XMS_Fax_Recv                         = $1,
	XMS_Fax_Send                         = $2,
	XMS_Fax_Stop                         = $3
);

Type XMS_FAX_WORKMODE =
(
	XMS_FAX_WORKMODE_NORMAL              = $00,
	XMS_FAX_WORKMODE_SERVER              = $01,
	XMS_FAX_WORKMODE_GATEWAY             = $02
);

Type XMS_FAX_ECM_MODE_TYPE =
(
	XMS_FAX_ECM_MODE_TYPE_NORMAL         = $00,
	XMS_FAX_ECM_MODE_TYPE_ECM            = $01
);

Type XMS_FAX_PAGE_HEADER_TYPE =
(
  XMS_FAX_PAGE_HEADER_TYPE_CLEAR         = $00,
	XMS_FAX_PAGE_HEADER_TYPE_SET           = $01
);

Type XMS_FAX_M_FILE_TYPE =
(
  XMS_FAX_M_FILE_TYPE_CLEAR              = $00,
	XMS_FAX_M_FILE_TYPE_ADD                = $02
);

Type XMS_ANSWERCALL_TYPE =
(
	XMS_ANSWERCALL_ANC                   = $0,
	XMS_ANSWERCALL_ANN                   = $1,
	XMS_ANSWERCALL_CON                   = $2
);

Type XMS_CTX_REG_TYPE =
(
	XMS_CTX_REG                     = $1,//ctx reg*/
	XMS_CTX_UNREG                   = $2 //ctx unreg*/
);

Type XMS_CTX_LINK_OPTION =
(
	CTX_LINK_OPTION_RESET			    = $1,//*reset all link*/
	CTX_LINK_OPTION_LINK			    = $2,//*single link*/
	CTX_LINK_OPTION_UNLINK			  = $3,//*single unlink*/
	CTX_LINK_OPTION_DUALLINK		  = $4,//*dual link*/
	CTX_LINK_OPTION_DUALUNLINK		= $5 //*dual unlink*/
);

Type XMS_MEDIA_TYPE =
(
    MEDIA_TYPE_AUDIO               = 0, //*play audio only*/
    MEDIA_TYPE_VIDEO               = 1, //*play video only*/
    MEDIA_TYPE_ANV                 = 4, //*play audio and video*/
		MEDIA_TYPE_MEDIAEX_AUDIO			 = 5,	//*use mediaex play audio*/
		MEDIA_TYPE_MEDIAEX_VIDEO			 = 6,	//*use mediaex play video*/
		MEDIA_TYPE_MEDIAEX_ANV				 = 7 	//*use mediaex play audio and video*/
);

Type XMS_SS7_FRAME_USER_TYPE =
(
	XMS_SS7_USER_SCCP = $03,
	XMS_SS7_USER_TUP  = $04,
	XMS_SS7_USER_ISUP = $05
);
 
Type XMS_SS7_FRAME_LINK_TYPE =
(
	XMS_SS7_LINK_ITU  = $02,
	XMS_SS7_LINK_CHINA= $04
);
 
Type XMS_SS7_FRAME_INFO_TYPE =
(
	XMS_SS7_INFO_DATA   = $01,
	XMS_SS7_INFO_CMD    = $02
);

Type XMS_SYSMON_MODSTATE =
(
	SYSMON_MODSTATE_DISCONNECT      = $0,//*Module disconnect*/
  SYSMON_MODSTATE_CONNECT         = $1 //*Module connect*/
);

Type XMS_CTBUS_CLKNET_TYPE =
(
   L_NET0   = $08,
   L_NET1   = $09,
   L_NET2   = $0A,
   L_NET3   = $0B

);

Type XMS_CAS_PARAM_TYPE=
(
	  CAS_PARAM_UNIPARAM      = 0,
    CAS_PARAM_MFCTYPE       = 1,
    CAS_PARAM_CALLTYPE      = 2,    //0 all (default)  1 逐位拨号 CmdParamData_CAS->m_u8CallType;
    CAS_PARAM_APPENDCALLEE  = 3    //CmdParamData_CAS->m_u8AppendCallee 一次一位
);

Type XMS_VOC_PARAM_TYPE=
(
	  VOC_PARAM_UNIPARAM      = 0,
    VOC_PARAM_BREAKEN_CALL  = 1,
    VOC_PARAM_3GFAXTONE     = 2
);

Type PUT_TEXTINPIC_FONTTYPE =	     // .\\PutTextInPicture.ini */
(
    FONTTYPE_SIMSUN      = 0,    //宋体&新宋体*/
    FONTTYPE_MICROSS     = 1     //Microsoft Sans Serif*/
);

Type PUT_TEXTINPIC_TYPE =
(
    PUT_TYPE_TEXT            = 1,
    PUT_TYPE_PICTURE         = 2
);

// VoIP Media Capabilities
Type XMS_VOIP_MEDIA_CAPS =
(
// audio media
	VOIP_MEDIA_AUDIO_PCMU		= $00,	// pcm u-law
	VOIP_MEDIA_AUDIO_PCMA		= $01,	// pcm a-law
	VOIP_MEDIA_AUDIO_G723		= $02,	// g.723
	VOIP_MEDIA_AUDIO_G729		= $03,	// g.729
	VOIP_MEDIA_AUDIO_T38		= $04,	// t.38/rtp
	VOIP_MEDIA_AUDIO_AMR		= $05,	// amr-nb
// video media
	VOIP_MEDIA_VIDEO_H261		= $80,	// h.261
	VOIP_MEDIA_VIDEO_H263		= $81,	// h.263
	VOIP_MEDIA_VIDEO_H263P	= $82,	// h.263+
	VOIP_MEDIA_VIDEO_MPEG4	= $83,	// mpeg-4 visual
	VOIP_MEDIA_VIDEO_H264		= $84,	// h.264

	VOIP_MEDIA_IMAGE_T38		= $F0 	// t.38/udptl
);

Type XMS_FAX_PARAM_TYPE =
(
	FAX_PARAM_FAXHEADER    = 0 ,
	FAX_PARAM_ADDFAXFILE   = 1 ,
	FAX_PARAM_ECM	         = 2,
	FAX_PARAM_MODE_TYPE    = 3,
	FAX_PARAM_BPS	         = 4,
	FAX_PARAM_FAXHEADEREX  = 5
);

// ISDN Device Param type
Type XMS_ISDN_PARAM_TYPE =
(
     ISDN_PARAM_ORINUMBER         = 0,
     ISDN_PARAM_CALLTYPE          = 1,
     ISDN_PARAM_APPENDCALLEE      = 2,
     ISDN_PARAM_CALLOUT           = 3,
     ISDN_PARAM_DISCONNECTREASON  = 4,
     ISDN_PARAM_LOW_LEVEL         = 5,
     ISDN_PARAM_UUI               = 6
);

// Conference Device Params
Type XMS_CONF_PARAM_TYPE =
(
	CONF_PARAM_UNIPARAM = 0,
  CONF_PARAM_VAD      = 1
);

// Analog EM Device Params
Type XMS_AEM_PARAM_TYPE =
(
	XMS_AEM_PARAM_SND_M_SIGNAL = 1 //send M msg to endpoint
);

// MediaEx Device Params
Type XMS_MEDIAEX_PARAM_TYPE =
(
	MEDIAEX_PARAM_INPUT = 0,
	MEDIAEX_PARAM_OUTPUT
);

// VoIP Call Slot Access Flag
const XMS_VOIP_ACCESS_NONE			= $00;	// no access
const XMS_VOIP_ACCESS_H323			= $01;	// h.323 call access
const XMS_VOIP_ACCESS_SIP				= $02;	// sip call access
const XMS_VOIP_ACCESS_INCOMING		 =  $04;	// incoming call access
const XMS_VOIP_ACCESS_OUTGOING		 =  $08;	// outgoing call access
const XMS_VOIP_ACCESS_REGISTRATION = 	$10;	// registration access

// VoIP Device Params
Type XMS_VOIP_PARAM_TYPE =
(
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
	VOIP_PARAM_CALL_DIVERSION_INFO
);

// Analog HIZ Device Params
Type XMS_ANALOGHIZ_PARAM_TYPE =
(
    ANALOGHIZ_PARAM_SET_SW_MODE   = 0 ,//set Switch Mode,replace by XMS_DIGREC_PARAM_UNI On Digital Module,reference to XMS_DIGREC_PARAM_TYPE
    ANALOGHIZ_PARAM_VOLTAGE       = 1 ,//Set voltage
    ANALOGHIZ_PARAM_READSN        = 4 ,//get HIZ's SN
    ANALOGHIZ_PARAM_GET_VOLTAGE   = 5  //get HIZ's voltage
);

// Analog VOC2 Device Params
Type XMS_ANALOGVOC2_PARAM_TYPE =
(
  ANALOGVOC2_PARAM_NULL          = 1 ,//RESERVE
  ANALOGVOC2_PARAM_READSN        = 4 ,//get VOC2 SN
	ANALOGVOC2_PARAM_GET_VOLTAGE   = 5  //get HIZ's voltage
);

// Analog VOC4 Device Params
Type XMS_ANALOGVOC4_PARAM_TYPE =
(
  ANALOGVOC4_PARAM_NULL          = 1 ,//RESERVE
  ANALOGVOC4_PARAM_READSN        = 4 ,//get VOC4 SN
	ANALOGVOC4_PARAM_GET_VOLTAGE   = 5  //get HIZ's voltage
);

// Analog MEG Device Params
Type XMS_AMEG_PARAM_TYPE =
(
	XMS_AMEG_PARAM_SEND_RING_SIGNAL = 1, // send ring msg to meg
	XMS_AMEG_PARAM_GET_SN           = 4, // get param for sn
	XMS_AMEG_PARAM_GET_VOLTAGE      = 5  // get param for voltage
);

// Analog EM Device Params
Type XMS_ANALOGEM_PARAM_TYPE =
(
	ANALOGEM_PARAM_NULL             = 1, //RESERVE
    ANALOGEM_PARAM_READSN         = 4, //get EM's SN
	ANALOGEM_PARAM_GET_VOLTAGE      = 5  //get EM's voltage
);

// 324 Config Params
Type XMS_324_PARAM_TYPE  =
(
	H324_PARAM_UNIPARAM  = $0,
	H324_PARAM_MEDIA     = $1,
	H324_PARAM_CH	     = $2,
	H324_PARAM_MIXER	 = $3,
	H324_PARAM_TCS		 = $4
);

//Digtial machine Record param type
Type XMS_DIGREC_PARAM_TYPE =
(
	XMS_DIGREC_PARAM_UNI         = $0,       //set switch mode param type
	XMS_AREC_PARAM_SET_VOLTAGE   = $01       //set analog rec module valtage param type
);

Type MD_CFG_TYPE =
(
	MD_CFG_TYPE_NON_INDEX      = $00,   //非索引操作
	MD_CFG_TYPE_INDEX          = $01    //索引操作
);


//XMS_324_CMD_SESSION_TYPE
Type XMS_324_CMD_SESSION_TYPE =
(
	XMS_324_CMD_TYPE_NORMAL_START			= $0,	// start session in normal mode */
	XMS_324_CMD_TYPE_MONITOR_START    = $1,	//* start session in monitor mode */
	XMS_324_CMD_TYPE_STOP             = $2,	//* stop session */
	XMS_324_CMD_TYPE_RESET					  = $3	//* reset session */
);

//XMS_324_CMD_CTRL_TYPE
Type XMS_324_CMD_CTRL_TYPE =
(
	XMS_324_CMD_TYPE_SETMET				= 1,	// set multiplex entry table */
	XMS_324_CMD_TYPE_OLC					= 2,	// open rx/tx logical channel */
	XMS_324_CMD_TYPE_CLC					= 3,	// close logical channel */
	XMS_324_CMD_TYPE_UII					= 4,	// Send user input */
	XMS_324_CMD_TYPE_VFU					= 5 	// send video fast update */
);

//XMS_324_EVT_TYPE
Type XMS_324_EVT_TYPE =
(
	XMS_324_EVT_TYPE_START				= 1,	// start session event
	XMS_324_EVT_TYPE_STOP				  = 2,	// stop session event
	XMS_324_EVT_TYPE_RESET				= 3,	// reset session event
	XMS_324_EVT_TYPE_UII					= 4,	// receive user input event
	XMS_324_EVT_TYPE_SIG_PDU      = 5,	// receive h.245 signal message event
	XMS_324_EVT_TYPE_OLC					= 6,	// open logical channel event
	XMS_324_EVT_TYPE_CLC					= 7 	// close logical channel event
);

// XMS_324_STOP_CODE
Type XMS_324_STOP_CODE =
(
	XMS_324_STOP_CODE_UNKOWN				  = 0,
	XMS_324_STOP_CODE_UPERSTOP				= 1,
	XMS_324_STOP_CODE_LOWERSTOP				= 2,
	XMS_324_STOP_CODE_HOSTSTOP				= 3,
	XMS_324_STOP_CODE_REMOTESTOP			= 4
);

// XMS_324_AL_TYPE
Type XMS_324_AL_TYPE =
(
	XMS_324_AL1_FRAMED					= 1,	// AL1 framed
	XMS_324_AL1_NOTFRAMED				= 2,	// AL1 not framed
	XMS_324_AL2_WITHOUTSN				= 3,	// AL2
	XMS_324_AL2_SN							= 4,	// AL2 with sn
	XMS_324_AL3								  = 5	  // AL3
);

// encode type define for 3G324M module
//  encode type */
Type XMS_ENCODE_TYPE =
(
	XMS_324_LC_CTRL							= $0,
	XMS_324_LC_AUDIO_G723				= $08,
	XMS_324_LC_AUDIO_AMR				= $14,
	XMS_324_LC_VIDEO_H263				= $83,
	XMS_324_LC_VIDEO_MPEG4			= $85
);

//////////////////////////////////////////////////////////////////
//XMS_SCCP_CMD_TYPE
Type XMS_SCCP_CMD_TYPE =
(
	XMS_SCCP_CMD_SETRAWDATA             = 1
);

//EXT_ENABLE_TYPE
Type EXT_ENABLE_TYPE =
(
    EXT_ENABLE_DPD                          = 01,
    EXT_ENABLE_PVD                          = 02,
    EXT_ENABLE_MSK                          = 04,
    EXT_ENABLE_VSD                          = 08
);

//DRS_EVT_MASK
Type DRS_EVT_MASK =
(
    DRS_EVT_HOOK_MASK                       = 01,
    DRS_EVT_CONNECT_MASK                    = 02,
    DRS_EVT_VAD_MASK                        = 04
);

//XMS_RTPX_PARAM_TYPE
Type XMS_RTPX_PARAM_TYPE =
(
	XMS_RTPX_PARAM_INPUT               = 0,
	XMS_RTPX_PARAM_OUTPUT              = 1,
	XMS_RTPX_PARAM_MIXER		           = 2,
	XMS_RTPX_PARAM_ADDR				         = 3,
	XMS_RTPX_PARAM_INPUT_A             = 4,
	XMS_RTPX_PARAM_OUTPUT_A            = 5,
	XMS_RTPX_PARAM_MIXER_A		         = 6,
	XMS_RTPX_PARAM_ADDR_A				       = 7
);

//XMS_DRS_SWITCH_TYPE*/
Type XMS_DRS_SWITCH_TYPE =
(
    XMS_DRS_SWITCH_AVAYA                = 01,
    XMS_DRS_SWITCH_SIMENZ               = 02,
    XMS_DRS_SWITCH_TADIRANT             = 03,
    XMS_DRS_SWITCH_ERRICSION            = 04,
    XMS_DRS_SWITCH_TOSHIBA              = 05
);

Type XMS_3GVCONF_ERROR_CODE_DEF =
(
	XMS_ERROR_DEVTYPEERROR  = 0,		// 不是可加入会议的设备
	XMS_ERROR_REJOIN3GVCONF = 1,		// 已存在会议中
	XMS_ERROR_GETRESFAIL    = 2,		// 分配资源失败
	XMS_ERROR_OVERFLOW      = 3,		// 会议成员已满
	XMS_ERROR_NONEVISIBLE   = 4,		// 会议无可视视频会员
	XMS_ERROR_OVERFLOWPR    = 5,		// 会议16方已满 因为有会议播放或者录制造成

	XMS_ERROR_3GVCONFSTOP   = 255 	// 会议停止 可能是新加入会议的可视成员参数错误或播放录音参数错误 也可能是会议进程出现错误
						                      // 遇到此事件应该重让最后一个加入会议的操作取消 或者重启会议
);

implementation

end.
