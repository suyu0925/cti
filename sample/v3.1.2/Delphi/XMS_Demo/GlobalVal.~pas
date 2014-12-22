unit GlobalVal;

interface
uses
  SysUtils,Analog_Common_Code,DJAcsDevState,XMS_Demo_Event,XMS_Demo_Sub,DJAcsDataDef;

Type
  Tglobal=record
  cfg_IniName:array [0..255] of char;
  cfg_CallingNum:Array[0..31] of char;
  cfg_SimCalledNum:Array[0..31] of char;
  cfg_IniShortName:string;
  cfg_ServerID:ServerID_t;
  cfg_iCalledLen:integer;
  cfg_iPartWork:integer;
  cfg_iPartWorkModuleID:integer;
  cfg_iCallOutRule:integer;
  cfg_s32DebugOn:integer;
  g_acsHandle:LongWord;
  g_u8UnitID:Byte;
  cfg_iVoiceRule:Integer;
  g_NumOfListBox:Integer;
  AllDeviceRes:Array[0..255] of TYPE_XMS_DSP_DEVICE_RES_DEMO;
  g_iTotalModule:Integer;
  MapTable_Module:Array[0..255] of Shortint;
  g_iTotalPcm:Integer;
  g_iTotalPcmOpened:Integer;
  MapTable_Pcm:Array[0..63] of TYPE_CHANNEL_MAP_TABLE;
  g_iTotalTrunk:Integer;
  g_iTotalTrunkOpened:Integer;
  MapTable_Trunk:Array[0..2047] of TYPE_CHANNEL_MAP_TABLE;
  g_iTotalUser:Integer;
  g_iTotalUserOpened:Integer;
  MapTable_User:Array[0..2047] of TYPE_CHANNEL_MAP_TABLE;
  g_iTotalVoice:Integer;
  g_iTotalVoiceOpened:Integer;
  g_iTotalVoiceFree:Integer;
  MapTable_Voice:Array[0..2047] of TYPE_CHANNEL_MAP_TABLE;
  g_Param_Analog:TYPE_ANALOG_GTD_PARAM;
  g_Param_CAS:CmdParamData_CAS_t;
  cfg_iDispChnl:integer;
  cfg_VocPath:Array[0..127] of char;
  g_callerDtmf:Array[0..19] of char;
  g_dtmfIndex:Byte;
end;

implementation
end.




