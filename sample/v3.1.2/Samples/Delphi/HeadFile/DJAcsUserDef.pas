unit DJAcsUserDef;

interface

uses
  SysUtils, Variants, Messages, Windows, DJAcsDataDef, DJItpFlowChanDef, DJAcsCmdDef;

Type
  Acs_Fax_InterCmd = record
	m_ITPFaxRes      : ^ITP_RES_CHAN; //*fax res*/
  m_ITPFaxVocRes   : ^ITP_RES_CHAN; //*fax voice res*/
  m_ITPSendFaxParm : SendFaxParm_t; //*send fax parm*/
end;

Type
  Acs_FaxEnd_InterCmd = record
  m_ITPFaxVocRes  : ^ITP_RES_CHAN; //*fax voice res*/
  m_s32EvtState   : Integer;
  m_s32ErrCode    : Integer;
  m_u8ErrStep     : Byte;
  m_u8T30CmdState : Byte;
  m_u8T30RcvState : Byte;
  m_u16TotalPages : Word;
  m_s8RemoteID    : Array[0..19] of ShortInt;
end;

Type
  LostCallInfo = record
	szCalling    : Array[0..19] of ShortInt;
	szCalled     : Array[0..19] of ShortInt;
	szOrigCalled : Array[0..19] of ShortInt;
	szLostTime   : Array[0..39] of ShortInt;
end;

Type
  Fax_VoIP_InterCmd = record
	m_FaxDevice  : DeviceID_t;
	m_s8T38Shake : ShortInt;
	m_s8Rfu1     : Array[0..2] of ShortInt;
end;

Type
  CallUserInfor = record
	m_DeviceID : DeviceID_t;
	m_szCaller : Array[0..31] of ShortInt;
end;

Type
  InterCmdStru = record
	m_s8Buff : Array[0..1023] of ShortInt;
end;


Type
  LinkStru = record
	DstDev : DeviceID_t; //dst dev*/
  SRtpx : ^ITP_RES_CHAN;
  DRtpx : ^ITP_RES_CHAN;
  MEx   : ^ITP_RES_CHAN;
end;

const MAX_LINKS			 = 128;

Type
  MediaType = record
	m_u8MediaType : Byte;
	rfu           : Byte;
	m_u16Kbps     : Word;
end;

Type
  CmdParamData_ReadVoltage_t = record
	m_u8ReadFlag : Byte;       //Read voltage control flag, 0: stop read; 1: start read*/
	m_s8Reserved1 : Array[0..2] of ShortInt;
	m_u32TimeSpan : DWORD;     //Keygoe report voltage event time span, unit: ms*/
	m_s8Voltage : ShortInt;    //Current voltage value*/
  m_u8Reserved2 : Array[0..2] of Byte;
end;

implementation

end.
