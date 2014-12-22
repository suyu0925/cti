unit XMS_Dial_Sub;

interface
uses
  SysUtils,DJAcsDataDef;

Type
    VOICE_STATE=
    (
    VOC_WAITOPEN,
    VOC_FREE,
    VOC_USED,
    VOC_WAIT_REMOVE
    );

Type TRUNK_STATE=
    (
    TRK_WAITOPEN = 0,
    TRK_FREE = 1,
    TRK_NOTHANDLE = 2,
    TRK_CALLOUT = 3,
    TRK_SIM_CALLOUT = 4,
    TRK_SIM_LINK = 5,
    TRK_SIM_ANALOG_OFFHOOK = 6,
    TRK_SIM_ANALOG_DIALING = 7,
    TRK_LINK = 8,
    TRK_PLAYDTMF = 9,
    TRK_HANGUP = 10,
    TRK_FAIL = 11,
    TRK_WAIT_REMOVE = 12
    );

Type USER_STATE =
(
	USER_WAITOPEN=0,
	USER_FREE=1,
	USER_OFFHOOK=2,
	USER_CALLOUT=3,
	USER_LINK=4,
	USER_WAITHANGUP=5,
	USER_WAIT_REMOVE=6,
	USER_RING=7
);

Type
    VOICE_STRUCT=record
    deviceID:DeviceID_t;
    iSeqID:Integer;
    UsedDevID:DeviceID_t;
    State:VOICE_STATE;
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
    TRUNK_STRUCT=record
    deviceID:DeviceID_t;
    iSeqID:Integer;
    iModSeqID:Integer;
    iLineState:Integer;
    VocDevID:DeviceID_t;
    LinkDevID:DeviceID_t;
    State:TRUNK_STATE;
    UserState:USER_STATE;
    iUserSeqID:Integer;
    DtmfCount:Integer;
    DtmfBuf:Array[0..31] of char;
    CallerCode:Array[0..19] of char;
    CalleeCode:Array[0..19] of char;
end;

implementation

end.
