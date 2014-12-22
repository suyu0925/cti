unit XMS_Dial_Event;

interface
uses
  SysUtils,DJAcsDataDef,XMS_Dial_Sub;

Type
  REMOVE_STATE=
  (
  DSP_REMOVE_STATE_NONE,
  DSP_REMOVE_STATE_START,
  DSP_REMOVE_STATE_READY
  );

Type
  TYPE_XMS_DSP_DEVICE_RES_DEMO=record
  lFlag:Integer;
  deviceID:DeviceID_t;
  iSeqID:Integer;
  bOpenFlag:Bytebool;
  bErrFlag:Bytebool;
  RemoveState:REMOVE_STATE;
  lVocNum:Integer;
  lVocOpened:Integer;
  lVocFreeNum:Integer;
  pVoice:^VOICE_STRUCT;
  lPcmNum:Integer;
  lPcmOpened:Integer;
  pPcm:^PCM_STRUCT;
  lTrunkNum:Integer;
  lTrunkOpened:Integer;
  pTrunk:^TRUNK_STRUCT;
end;

implementation

end.
