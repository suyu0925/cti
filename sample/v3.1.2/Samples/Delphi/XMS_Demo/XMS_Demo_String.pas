unit XMS_Demo_String;

interface
uses
  SysUtils,DJAcsDataDef,DJAcsDevState;

  Function GetString_EventType(s32EventType:Integer):string;
  function GetString_DeviceMain(nDevMain:Integer):string;
  function GetString_LineState (iLineState:integer):string;
  function GetString_DeviceSub(nDeviceSub:Smallint):string;
  function GetString_ErrorCode ( s32ErrorCode:integer):string;
  function GetString_PcmType(iPcmType:integer):string;

implementation

function GetString_PcmType(iPcmType:integer):string;
begin
  if iPcmType=0 then
    begin
      result:='Disable';
      exit;
    end;

  result:='UNKNOWN';

  case iPcmType of
    integer(XMS_E1_TYPE_Analog30): result:='T_Analog30';
    integer(XMS_E1_TYPE_PCM31): result:='T_PCM31';
    integer(XMS_E1_TYPE_PCM30): result:='T_PCM30';
    integer(XMS_E1_TYPE_CAS): result:='T_CAS';
    integer(XMS_E1_TYPE_PRI): result:='T_PRI';
    integer(XMS_E1_TYPE_SS7_TUP_0_Link): result:='T_TUP_0_LK';
    integer(XMS_E1_TYPE_SS7_TUP_1_Link): result:='T_TUP_1_LK';
    integer(XMS_E1_TYPE_SS7_TUP_2_Link): result:='T_TUP_2_L';
    integer(XMS_T1_TYPE_D4): result:='T_D4';
    integer(XMS_T1_TYPE_ESF): result:='T_ESF';
    integer(XMS_J1_TYPE_D4): result:='J_D4';
    integer(XMS_J1_TYPE_ESF): result:='J_ESF';
    integer(XMS_SLC_TYPE_96): result:='SLC_TYPE_96';
    integer(XMS_E1_TYPE_SS7_ISUP_0_Link): result:='T_ISUP_0_LK';
    integer(XMS_E1_TYPE_SS7_ISUP_1_Link): result:='T_ISUP_1_LK';
    integer(XMS_E1_TYPESS7_ISUP_2_Link):  result:='T_ISUP_2_LK';
    integer(XMS_E1_TYPE_6D25B): result:='T_6D25B';
  end;
end;

function GetString_ErrorCode ( s32ErrorCode:integer):string;
Begin
  result:='UNKNOWN';
  case s32ErrorCode of
    integer(ACSERR_LOADLIBERR): result:='LOADLIBERR';
    integer(ACSERR_BADPARAMETER): result:='BADPARAMETER';
    integer(ACSERR_NOSERVER): result:='NOSERVER';
    integer(ACSERR_MAXCONN_EXCEED): result:='MAXCONN_EXCEED';
    integer(ACSERR_BADHDL): result:='ABADHDL';

    integer(ACSERR_FAILSEND): result:='FAILSEND';
    integer(ACSERR_LINKBROKEN): result:='LINKBROKEN';
    integer(ACSERR_NOMESSAGE): result:='NOMESSAGE';
    integer(ACSERR_GETRESFAIL): result:='GETRESFAIL';
    integer(ACSERR_NOSUPPORTCMD): result:='NOSUPPORTCMD';
  end;
end;

Function GetString_EventType(s32EventType:Integer):string;
begin
  result:='UNKNOWN';
  case s32EventType of
  integer(XMS_EVT_OPEN_STREAM):		result:= 'OPEN_STREAM';
  integer(XMS_EVT_QUERY_DEVICE):		result:= 'QUERY_DEVICE';
  integer(XMS_EVT_QUERY_DEVICE_END):	result:= 'QUERY_DEVICE_END';
  integer(XMS_EVT_OPEN_DEVICE):		result:= 'OPEN_DEVICE';
  integer(XMS_EVT_CLOSE_DEVICE):		result:= 'CLOSE_DEVICE';
  integer(XMS_EVT_RESET_DEVICE):		result:= 'RESET_DEVICE';
  integer(XMS_EVT_DEVICESTATE):		result:= 'DEVICESTATE';
  integer(XMS_EVT_SETDEV_GROUP):		result:= 'SETDEV_GROUP';
  integer(XMS_EVT_SETPARAM):			result:= 'SETPARAM';
  integer(XMS_EVT_GETPARAM):			result:= 'GETPARAM';
  integer(XMS_EVT_QUERY_ONE_DSP_START):				result:= 'QUERY_ONE_DSP_START';
  integer(XMS_EVT_QUERY_ONE_DSP_END):					result:= 'QUERY_ONE_DSP_END';
  integer(XMS_EVT_QUERY_REMOVE_ONE_DSP_START):		result:= 'QUERY_REMOVE_ONE_DSP_START';
  integer(XMS_EVT_QUERY_REMOVE_ONE_DSP_END):			result:= 'QUERY_REMOVE_ONE_DSP_END';
  integer(XMS_EVT_MASTER_STATE): result:= 'MASTER_STATE';
  integer(XMS_EVT_CALLOUT):			result:= 'CALLOUT';
  integer(XMS_EVT_CALLIN):			result:= 'CALLIN';
  integer(XMS_EVT_ALERTCALL):			result:= 'ALERTCALL';
  integer(XMS_EVT_ANSWERCALL):		result:= 'ANSWERCALL';
  integer(XMS_EVT_LINKDEVICE):		result:= 'LINKDEVICE';
  integer(XMS_EVT_UNLINKDEVICE):		result:= 'UNLINKDEVICE';
  integer(XMS_EVT_CLEARCALL):			result:= 'CLEARCALL';
  integer(XMS_EVT_ANALOG_INTERFACE):	result:= 'ANALOG_INTERFACE';
  integer(XMS_EVT_CAS_MFC_START):		result:= 'CAS_MFC_START';
  integer(XMS_EVT_CAS_MFC_END):		result:= 'CAS_MFC_END';
                                                                                                    		
  integer(XMS_EVT_JOINTOCONF):		result:= 'JOINTOCONF';
  integer(XMS_EVT_LEAVEFROMCONF):		result:= 'LEAVEFROMCONF';
  integer(XMS_EVT_CLEARCONF):			result:= 'CLEARCONF';
                                                                                                    		
                                                                                                    		
  integer(XMS_EVT_PLAY):				result:= 'PLAY';
  integer(XMS_EVT_INITINDEX):			result:= 'INITINDEX';
  integer(XMS_EVT_BUILDINDEX):		result:= 'BUILDINDEX';
  integer(XMS_EVT_CONTROLPLAY):		result:= 'CONTROLPLAY';
  integer(XMS_EVT_RECORD):			result:= 'RECORD';
  integer(XMS_EVT_CONTROLRECORD):		result:= 'CONTROLRECORD';

  integer(XMS_EVT_SENDFAX):			result:= 'SENDFAX';
  integer(XMS_EVT_RECVFAX):			result:= 'RECVFAX';

  integer(XMS_EVT_SENDIODATA):		result:= 'SENDIODATA';
  integer(XMS_EVT_RECVIODATA):		result:= 'RECVIODATA';

  integer(XMS_EVT_MODMONITOR):	    result:= 'MODMONITORFILTER';
  integer(XMS_EVT_UNIFAILURE):		result:= 'UNIFAILURE';

  end;
end;

function GetString_DeviceMain(nDevMain:Integer):string;
begin
  result:='UNKNOWN';
  case nDevMain of
    integer(XMS_DEVMAIN_VOICE): result:='VOC';
    integer(XMS_DEVMAIN_FAX): result:='FAX';
    integer(XMS_DEVMAIN_DIGITAL_PORT): result:='DIGIT';
    integer(XMS_DEVMAIN_INTERFACE_CH): result:='INTCH';
    integer(XMS_DEVMAIN_DSS1_LINK): result:='DSS1';
    integer(XMS_DEVMAIN_SS7_LINK): result:='SS7';
    integer(XMS_DEVMAIN_BOARD): result:='BRD';
    integer(XMS_DEVMAIN_CTBUS_TS): result:='CTBUS';
    integer(XMS_DEVMAIN_CONFERENCE): result:='CONF';
    integer(XMS_DEVMAIN_VIDEO): result:='VIDEO';
    integer(XMS_DEVMAIN_VOIP):  result:='VOIP';
  end;
end;

function  GetString_LineState (iLineState:integer):string;
begin
  case iLineState of
    integer(DEVICE_COMMON_STATE_START): result:='S_START';
    integer(DCS_FREE): result:='S_FREE';
    integer(DCS_LOCAL_BLOCK): result:='S_LOCAL_BLOCK';
    integer(DCS_REMOTE_BLOCK): result:='S_REMOTE_BLOCK';
    integer(DCS_BLOCK): result:='S_BLOCK';
    integer(DCS_UNAVAILABLE): result:='S_UNAVAILABLE';
    integer(DCS_CALLOUT): result:='S_CALLOUT';
    integer(DCS_CALLIN): result:='S_CALLIN';
    integer(DCS_ALERTING): result:='S_ALERTING';
    integer(DCS_CONNECT): result:='S_CONNECT';
    integer(DCS_DISCONNECT): result:='S_DISCONNECT';
    integer(DCS_WAIT_FREE): result:='S_WAIT_FREE';
    else  result:=Format('0x%x',[iLineState]);
  end;
end;

function GetString_DeviceSub(nDeviceSub:Smallint):string;
begin
  result:='UNKNOWN';
  case nDeviceSub of
     Smallint(XMS_DEVSUB_BASE):						result:='BASE';
     Smallint(XMS_DEVSUB_ANALOG_TRUNK):						result:='A_TRUNK';
     Smallint(XMS_DEVSUB_ANALOG_USER):						result:='A_USER';
     Smallint(XMS_DEVSUB_ANALOG_HIZ):						result:='A_HIZ';
     Smallint(XMS_DEVSUB_ANALOG_EMPTY):						result:='A_EMPTY';
     Smallint(XMS_DEVSUB_E1_PCM):						result:='E1_PCM';
     Smallint(XMS_DEVSUB_E1_CAS):						result:='E1_CAS';
     Smallint(XMS_DEVSUB_E1_DSS1):						result:='E1_DSS1';
     Smallint(XMS_DEVSUB_E1_SS7_TUP):						result:='E1_TUP';
     Smallint(XMS_DEVSUB_E1_SS7_ISUP):						result:='E1_ISUP';
     Smallint(XMS_DEVSUB_ANALOG_VOC2W):						result:='A_VOC2W';
     Smallint(XMS_DEVSUB_ANALOG_VOC4W):						result:='A_VOC4W';
     Smallint(XMS_DEVSUB_ANALOG_EM):						result:='A_EM';
     Smallint(XMS_DEVSUB_E1_DCH):						result:='E1_DCH';
     Smallint(XMS_DEVSUB_E1_BCH):						result:='E1_BCH';
     Smallint(XMS_DEVSUB_UNUSABLE):						result:='UNUSE';

     Smallint(XMS_DEVSUB_HIZ_CAS):						result:='HIZ_CAS';
     Smallint(XMS_DEVSUB_HIZ_PRI):						result:='HIZ_PRI';
     Smallint(XMS_DEVSUB_HIZ_SS7):						result:='HIZ_SS7';
     Smallint(XMS_DEVSUB_HIZ_PRI_LINK):						result:='HIZ_PRI_LINK';
     Smallint(XMS_DEVSUB_HIZ_SS7_64K_LINK):						result:='HIZ_SS7_64K_LINK';
     Smallint(XMS_DEVSUB_HIZ_SS7_2M_LINK):						result:='HIZ_SS7_2M_LINK';
     Smallint(XMS_DEVSUB_SS7_LINK):						result:='SS7_LINK';
     Smallint(XMS_DEVSUB_LINESIDE):						result:='LINESIDE';
     Smallint(XMS_DEVSUB_ANALOG_REC):						result:='A_REC';
     Smallint(XMS_DEVSUB_DIGITAL_REC):						result:='D_REC';
     Smallint(XMS_DEVSUB_HIZ_HDLC_N64K_LINK):						result:='HDLC_N64_LINK';
  end;
end;

end.
