unit XMS_Demo_Sub;

interface
uses
  SysUtils,DJAcsDataDef;

Type
TRUNK_STATE=
    (
    TRK_WAITOPEN = 0,
    TRK_FREE = 1,
    TRK_WELCOME = 2,
    TRK_ACCOUNT = 3,
    TRK_PASSWORD = 4,
    TRK_SELECT = 5,
    TRK_PLAYRESULT = 6,
    TRK_RECORDFILE = 7,
    TRK_PLAYRECORD = 8,
    TRK_HANGON = 9,
    TRK_WAIT_ANSWERCALL = 10,
    TRK_WAIT_LINKOK = 11,
    TRK_WAIT_REMOVE = 12
    );

Type
    VOICE_STATE=
    (
     VOC_WAITOPEN,
     VOC_FREE,
     VOC_USED,
     VOC_WAIT_REMOVE
     );

Type
    TRUNK_STRUCT=record
    deviceID:DeviceID_t;
    iSeqID:Integer;
    iModSeqID:Integer;
    iLineState:Integer;
    VocDevID:DeviceID_t;
    u8PlayTag:Byte;
    State:TRUNK_STATE;
    DtmfCount:Integer;
    DtmfBuf:Array[0..31] of char;
    CallerCode:Array[0..19] of char;
    CalleeCode:Array[0..19] of char;
end;

Type
    PCM_STRUCT=record
    deviceID:DeviceID_t;
    iSeqID:Integer;
    bOpenFlag:Bytebool;
    u8E1Type:Byte;
    s32AlarmVal:Integer;
end;

Type
    VOICE_STRUCT=record
    deviceID:DeviceID_t;
    iSeqID:Integer;
    UsedDevID:DeviceID_t;
    State:VOICE_STATE;
end;

implementation

end.
 