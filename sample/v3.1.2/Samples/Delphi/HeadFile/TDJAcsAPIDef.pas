unit TDJAcsAPIDef;

interface
uses
  SysUtils,Windows,DJAcsDataDef,Dialogs;

Type
  EsrFunc=procedure(esrParam:Longword);cdecl;
  TXMS_acsOpenStream=function (acsHandle:pointer;serverID:pointer;u8AppID:Byte;u32SendQSize:Longword;u32RecvQSize:Longword;s32DebugOn:Integer;privateData:pointer):integer;stdcall;
  TXMS_acsSetEsr=function(acsHandle:Longword;esr:EsrFunc;esrParam:Longword;notifyAll:Integer):integer;stdcall;
  TXMS_acsGetDeviceList=function(acsHandle:Longword;privateData:pointer):integer;stdcall;
  TXMS_ctsOpenDevice=function(acsHandle:Longword;deviceID:pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsSetParam=function(acsHandle:Longword;deviceID:pointer;u16ParamCmdType:Word;u16ParamDataSize:Word;paramData:pointer):integer;stdcall;
  TXMS_ctsResetDevice=function(acsHandle:Longword;deviceID:pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsGetDevState=function(acsHandle:Longword;deviceID:pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsUnlinkDevice=function(acsHandle:Longword;srcDeviceID:pointer;destDeviceID:pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsLinkDevice=function(acsHandle:Longword;srcDeviceID:pointer;destDeviceID:pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsSendIOData=function(acsHandle:Longword;deviceID:pointer;u16IoType:Word;u16IoDataLen:Word;paramData:pointer):integer;stdcall;
  TXMS_ctsSetDevTimer=function(acsHandle:Longword;deviceID:pointer;u32Elapse:Integer):integer;stdcall;
  TXMS_ctsMakeCallOut=function(acsHandle:Longword;deviceID:pointer;callingID:pointer;calledID:pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsClearCall=function(acsHandle:Longword;deviceID:pointer;s32ClearCause:integer;privateData:pointer):integer;stdcall;
  TXMS_acsCloseStream=function(acsHandle:Longword;privateData:pointer):integer;stdcall;
  TXMS_ctsInitPlayIndex=function(acsHandle:Longword;mediaDeviceID:pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsBuildPlayIndex=function(acsHandle:Longword;mediaDeviceID:pointer;playProperty:pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsControlPlay=function(acsHandle:Longword;mediaDeviceID:pointer;controlPlay:pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsAlertCall=function(acsHandle:Longword;deviceID:pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsAnswerCallIn=function(acsHandle:Longword;deviceID:pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsPlay=function(acsHandle:Longword;mediaDeviceID:pointer;playProperty:pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsRecord=function(acsHandle:Longword;mediaDeviceID:pointer;recordProperty:pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsControlRecord=function(acsHandle:Longword;mediaDeviceID:pointer;controlRecord:pointer;privateData:pointer):integer;stdcall;
  TXMS_acsSetMaster=function(acsHandle:Longword;u8Master:Byte;privateData:pointer):integer;stdcall;
  TXMS_acsSetTimer=function(acsHandle:LongWord;u32Elapse:Cardinal):integer;stdcall;
  TXMS_ctsCloseDevice=function(acsHandle:Longword;deviceID:pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsSetDevGroup=function(acsHandle:Longword;deviceID:pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsGetParam=function(acsHandle:Longword;deviceID:pointer;u16ParamCmdType:Word;u16ParamDataSize:Word;paramData:pointer):integer;stdcall;
  TXMS_ctsJoinToConf=function(acsHandle:Longword;confDeviceID:pointer;mediaDeviceID:Pointer;confParam:Pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsLeaveFromConf=function(acsHandle:Longword;confDeviceID:pointer;mediaDeviceID:Pointer;confParam:Pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsClearConf=function(acsHandle:Longword;confDeviceID:Pointer;privateData:pointer):integer;stdcall;
  TXMS_ctsSendFax=function(acsHandle:Longword;faxDeviceID:pointer;mediaDeviceID:pointer;s8TiffFile:PChar;s8LocalID:Pchar;privateData:pointer):Integer;stdcall;
  TXMS_ctsStopSendFax=function(acsHandle:Longword;faxDeviceID:pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctsReceiveFax=function(acsHandle:Longword;faxDeviceID:pointer;mediaDeviceID:pointer;s8TiffFile:PChar;s8LocalID:Pchar;privateData:pointer):Integer;stdcall;
  TXMS_ctsStopReceiveFax=function(acsHandle:Longword;faxDeviceID:pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctsChangeMonitorFilter=function(acsHandle:Longword;deviceID:Pointer;monitorFilter:Longword;privateData:pointer):Integer;stdcall;
  TXMS_ctsSendSignalMsg=function(acsHandle:Longword;deviceID:pointer;u16SignalMsgType:Word):Integer;stdcall;
  TXMS_acsOpenStreamExt=function(acsHandle:Longword;serverID:pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctsPlayCSP=function(acsHandle:Longword;mediaDeviceID:Pointer;cspPlayProperty:Pointer;privateData :pointer):Integer;stdcall;
  TXMS_ctsSendCSPData=function(acsHandle:Longword;mediaDeviceID:Pointer;cspDataInfo :pointer;cspData:Pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctsControlPlayCSP=function(acsHandle:Longword;mediaDeviceID:Pointer;controlPlay:pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctsRecordCSP=function(acsHandle:Longword;mediaDeviceID:Pointer;recCSPProperty:pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctsControlRecordCSP=function(acsHandle:Longword;mediaDeviceID:Pointer;controlRecord:pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctsInitPlay3gppIndex=function(acsHandle:Longword;mediaDeviceID:pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctsBuildPlay3gppIndex=function(acsHandle:Longword;mediaDeviceID:pointer;playProperty:pointer;privateData:pointer):Integer;stdcall;
  TXMS_cts3gppPlay=function(acsHandle:Longword;mediaDeviceID:pointer;playProperty:pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctsControl3gppPlay=function(acsHandle:Longword;mediaDeviceID:pointer;controlPlay:pointer;privateData:pointer):Integer;stdcall;
  TXMS_cts3gppRecord=function(acsHandle:Longword;mediaDeviceID:pointer;recordProperty:pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctsControl3gppRecord=function(acsHandle:Longword;mediaDeviceID:pointer;controlRecord:pointer;privateData:pointer):Integer;stdcall;
  TXMS_acsQueryLicense=function(acsHandle:Longword;deviceID:Pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctxRegister=function(acsHandle:Longword;s8AppRegName:PChar;u8RegType:Byte;privateData:pointer):Integer;stdcall;
  TXMS_ctxLink=function(acsHandle:Longword;srcDev:Pointer;destDev:Pointer;u8Option:Byte;privateData:pointer):Integer;stdcall;
  TXMS_ctxSendAppData=function(acsHandle:Longword;s8SrcAppRegName:Pchar;s8DestAppRegName:Pchar;u8AppReqType:Byte;
                              pData:Pointer;u32DataSize:Longword;u8SrcAppUnitID:Byte;u8DestAppUnitID:Byte;
                              srcDevice:Pointer;privateData:pointer):Integer;stdcall;

  TXMS_ctsSendRawFrame=function(acsHandle:Longword;deviceID:Pointer;u16FrameSize:WOrd;pData:Pointer):Integer;stdcall;
  TXMS_ctsJoinTo3GVConf=function(acsHandle:Longword;device3GVConfID:Pointer;deviceID:Pointer;input:pointer;
                                output:pointer;u8Visible:Byte;privateData:pointer):Integer;stdcall;

  TXMS_ctsLeaveFrom3GVConf=function(acsHandle:Longword;device3GVConfID:Pointer;deviceID:Pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctsClear3GVConf=function(acsHandle:Longword;device3GVConfID:Pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctsGetLayout=function(acsHandle:Longword;device3GVConfID:Pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctsSetLayout=function(acsHandle:Longword;device3GVConfID:Pointer;layoutList:pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctsGetVisibleList=function(acsHandle:Longword;device3GVConfID:Pointer;privateData:pointer):Integer;stdcall;
  TXMS_ctsSetVisibleList=function(acsHandle:Longword;device3GVConfID:Pointer;visableList:pointer;privateData:pointer):Integer;stdcall;
	TXMS_ctsPutTextInPicture=function(acsHandle:Longword;s8DstFile:Pchar;paramItem:pointer;u32ParamSum:Longword;privateData:pointer):Integer;stdcall;
  TXMS_ctsRestart3GVConf=function(acsHandle:Longword;device3GVConfID:Pointer;privateData:pointer):Integer;stdcall;
	TXMS_acsGetRelateMod=function(acsHandle:Longword;u8ModType:Byte;u8UnitID:Byte):Integer;stdcall;
	TXMS_ctsPutUsrEvt=function(acsHandle:Longword;deviceID:Pointer;pUserEvt:pointer):Integer;stdcall;
	TXMS_acsLedCtrl=function(acsHandle:Longword;u8DspUnitID:Byte;pLedCtrl:pointer):Integer;stdcall;
  TXMS_acsCloseStreamExt=function(acsHandle:Longword;serverID:pointer;privateData:pointer):Integer;stdcall;

Var
  g_pDJApiLedCtrl:Pointer;
  g_pDJApiPutUsrEvt:Pointer;
  g_pDJApiGetRelateMod:Pointer;
  g_pDJApiRestart3GVConf:Pointer;
  g_pDJApiPutTextInPicture:Pointer;
  g_pDJApiSetVisibleList:Pointer;
  g_pDJApiGetVisibleList:Pointer;
  g_pDJApiSetLayout:Pointer;
  g_pDJApiGetLayout:Pointer;
  g_pDJApiClear3GVConf:pointer;
  g_pDJApiLeaveFrom3GVConf:Pointer;
  g_pDJApiJoinTo3GVConf:Pointer;
  g_pDJApiSendRawFrame:Pointer;
  g_pDJApiSendAppData:Pointer;
  g_pDJApiLink:Pointer;
  g_pDJApiRegister:Pointer;
  g_pDJApiQueryLicense:Pointer;
  g_pDJApiControl3gppRecord:Pointer;
  g_pDJApi3gppRecord:Pointer;
  g_pDJApiControl3gppPlay:Pointer;
  g_pDJApi3gppPlay:Pointer;
  g_pDJApiBuildPlay3gppIndex:Pointer;
  g_pDJApiInitPlay3gppIndex:Pointer;
  g_pDJApiControlRecordCSP:Pointer;
  g_pDJApiRecordCSP:Pointer;
  g_pDJApiControlPlayCSP:Pointer;
  g_pDJApiSendCSPData:Pointer;
  g_pDJApiPlayCSP:Pointer;
  g_pDJApiOpenStreamExt:Pointer;
  g_pDJApiSendSignalMsg:Pointer;
  g_pDJApiOpenStream:Pointer;
  g_pDJApiSetEsr:Pointer;
  g_pDJApiGetDevList:Pointer;
  g_pDJApiOpenDevice:Pointer;
  g_pDJApiSetParam:Pointer;
  g_pDJApiResetDevice:Pointer;
  g_pDJApiGetDevState:Pointer;
  g_pDJApiUnlinkDevice:Pointer;
  g_pDJApiLinkDevice:Pointer;
  g_pDJApiSendIOData:Pointer;
  g_pDJApiSetDevTimer:Pointer;
  g_pDJApiMakeCallOut:Pointer;
  g_pDJApiClearCall:Pointer;
  g_pDJApiCloseStream:Pointer;
  g_pDJApiInitPlayIndex:Pointer;
  g_pDJApiBuildPlayIndex:Pointer;
  g_pDJApiControlPlay:pointer;
  g_pDJApiAlertCall:Pointer;
  g_pDJApiAnswerCallIn:Pointer;
  g_pDJApiPlay:Pointer;
  g_pDJApiRecord:Pointer;
  g_pDJApiControlRecord:pointer;
  g_pDJApiSetMaster:pointer;
  g_pDJApiSetTimer:pointer;
  g_pDJApiCloseDevice:Pointer;
  g_pDJApiSetDevGroup:Pointer;
  g_pDJApiGetParam:Pointer;
  g_pDJApiClearConf:Pointer;
  g_pDJApiSendFax:Pointer;
  g_pDJApiStopSendFax:Pointer;
  g_pDJApiReceiveFax:Pointer;
  g_pDJApiStopReceiveFax:Pointer;
  g_pDJApiChangeMonitorFilter:Pointer;
  g_pDJApiCloseStreamExt:Pointer;
  g_pDJApiJoinToConf:Pointer;
  g_pDJApiLeaveFromConf:Pointer;
  DJApiHandle:THandle;

  Function LoadDJApi():Byte;

  function XMS_acsOpenStream(var acsHandle:Longword;Var serverID:ServerID_t;u8AppID:Byte;u32SendQSize:Longword;u32RecvQSize:Longword;s32DebugOn:Integer;var privateData:PrivateData_t):integer;

  function XMS_acsCloseStream(acsHandle:Longword;Var privateData:PrivateData_t):integer;

  function XMS_acsSetMaster(acsHandle:Longword;u8Master:Byte;Var privateData:PrivateData_t):integer;

  function XMS_acsSetEsr(acsHandle:Longword;esr:EsrFunc;esrParam:Longword;notifyAll:Integer):integer;

  function XMS_acsGetDeviceList(acsHandle:Longword;var privateData:PrivateData_t):integer;

  function XMS_acsSetTimer(acsHandle:LongWord;u32Elapse:Cardinal):integer;

  function XMS_ctsOpenDevice(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsCloseDevice(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsResetDevice(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsSetDevTimer(acsHandle:Longword;Var deviceID:DeviceID_t;u32Elapse:Integer):integer;

  function XMS_ctsGetDevState(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsSetDevGroup(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsMakeCallOut(acsHandle:Longword;Var deviceID:DeviceID_t;callingID:pointer;calledID:pointer;Var privateData:PrivateData_t):integer;

  function XMS_ctsSetParam(acsHandle:Longword;Var deviceID:DeviceID_t;u16ParamCmdType:Word;u16ParamDataSize:Word;paramData:pointer):integer;

  function XMS_ctsGetParam(acsHandle:Longword;Var deviceID:DeviceID_t;u16ParamCmdType:Word;u16ParamDataSize:Word;paramData:pointer):integer;

  function XMS_ctsAlertCall(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsAnswerCallIn(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsUnlinkDevice(acsHandle:Longword;Var srcDeviceID:DeviceID_t;Var destDeviceID:DeviceID_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsLinkDevice(acsHandle:Longword;Var srcDeviceID:DeviceID_t;Var destDeviceID:DeviceID_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsClearCall(acsHandle:Longword;Var deviceID:DeviceID_t;s32ClearCause:integer;Var privateData:PrivateData_t):integer;

  function XMS_ctsJoinToConf(acsHandle:Longword;Var confDeviceID:DeviceID_t;Var mediaDeviceID:DeviceID_t;Var confParam:CmdParamData_Conf_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsLeaveFromConf(acsHandle:Longword;Var confDeviceID:DeviceID_t;Var mediaDeviceID:DeviceID_t;Var confParam:CmdParamData_Conf_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsClearConf(acsHandle:Longword;Var confDeviceID:DeviceID_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsPlay(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var playProperty:PlayProperty_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsInitPlayIndex(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsBuildPlayIndex(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var playProperty:PlayProperty_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsControlPlay(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var controlPlay:ControlPlay_t;Var privateData:PrivateData_t):integer;

	function XMS_ctsRecord(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var recordProperty:RecordProperty_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsControlRecord(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var controlRecord:ControlRecord_t;Var privateData:PrivateData_t):integer;

  function XMS_ctsSendFax(acsHandle:Longword;Var faxDeviceID:DeviceID_t;Var mediaDeviceID:DeviceID_t;s8TiffFile:PChar;s8LocalID:Pchar;Var privateData:PrivateData_t):Integer;

	function XMS_ctsStopSendFax(acsHandle:Longword;Var faxDeviceID:DeviceID_t;Var privateData:PrivateData_t):Integer;

	function XMS_ctsReceiveFax(acsHandle:Longword;Var faxDeviceID:DeviceID_t;Var mediaDeviceID:DeviceID_t;s8TiffFile:PChar;s8LocalID:Pchar;Var privateData:PrivateData_t):Integer;

  function XMS_ctsStopReceiveFax(acsHandle:Longword;Var faxDeviceID:DeviceID_t;Var privateData:PrivateData_t):Integer;

	function XMS_ctsChangeMonitorFilter(acsHandle:Longword;Var deviceID:DeviceID_t;monitorFilter:Longword;Var privateData:PrivateData_t):Integer;

  function XMS_ctsSendIOData(acsHandle:Longword;Var deviceID:DeviceID_t;u16IoType:Word;u16IoDataLen:Word;paramData:pointer):integer;

	function XMS_ctsSendSignalMsg(acsHandle:Longword;Var deviceID:DeviceID_t;u16SignalMsgType:Word):Integer;

	function XMS_acsOpenStreamExt(acsHandle:Longword;Var serverID:ServerID_t;Var privateData:PrivateData_t):Integer;

  function XMS_acsCloseStreamExt(acsHandle:Longword;Var serverID:ServerID_t;Var privateData:PrivateData_t):Integer;

	function XMS_ctsPlayCSP(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var cspPlayProperty:CSPPlayProperty_t; Var privateData :PrivateData_t):Integer;

	function XMS_ctsSendCSPData(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var cspDataInfo :CSPPlayDataInfo_t;cspData:Pointer;var privateData:PrivateData_t):Integer;

	function XMS_ctsControlPlayCSP(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var controlPlay:ControlPlay_t;Var privateData:PrivateData_t):Integer;

	function XMS_ctsRecordCSP(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var recCSPProperty:RecordCSPProperty_t;Var privateData:PrivateData_t):Integer;

	function XMS_ctsControlRecordCSP(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var controlRecord:ControlRecord_t;Var privateData:PrivateData_t):Integer;

	function XMS_ctsInitPlay3gppIndex(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var privateData:PrivateData_t):Integer;

	function XMS_ctsBuildPlay3gppIndex(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var playProperty:Play3gppProperty_t;Var privateData:PrivateData_t):Integer;

  function XMS_cts3gppPlay(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var playProperty:Play3gppProperty_t;Var privateData:PrivateData_t):Integer;

  function XMS_ctsControl3gppPlay(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var controlPlay:Control3gppPlay_t;Var privateData:PrivateData_t):Integer;

  function XMS_cts3gppRecord(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var recordProperty:Record3gppProperty_t;Var privateData:PrivateData_t):Integer;

  function XMS_ctsControl3gppRecord(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var controlRecord:Control3gppRecord_t;Var privateData:PrivateData_t):Integer;

  function XMS_acsQueryLicense(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):Integer;

  function XMS_ctxRegister(acsHandle:Longword;s8AppRegName:PChar;u8RegType:Byte;Var privateData:PrivateData_t):Integer;

  function XMS_ctxLink(acsHandle:Longword;Var srcDev:DeviceID_t;Var destDev:DeviceID_t;u8Option:Byte;Var privateData:PrivateData_t):Integer;

  function XMS_ctxSendAppData(acsHandle:Longword;s8SrcAppRegName:Pchar;s8DestAppRegName:Pchar;u8AppReqType:Byte;
                              pData:Pointer;u32DataSize:Longword;u8SrcAppUnitID:Byte;u8DestAppUnitID:Byte;
                              Var srcDevice:DeviceID_t;Var privateData:PrivateData_t):Integer;

	function XMS_ctsSendRawFrame(acsHandle:Longword;Var deviceID:DeviceID_t;u16FrameSize:WOrd;pData:Pointer):Integer;

	function XMS_ctsJoinTo3GVConf(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var deviceID:DeviceID_t;Var input:Acs_MediaEx_Input_V;
                                Var output:Acs_MediaEx_Output_V;u8Visible:Byte;var privateData:PrivateData_t):Integer;

	function XMS_ctsLeaveFrom3GVConf(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):Integer;

	function XMS_ctsClear3GVConf(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var privateData:PrivateData_t):Integer;

  function XMS_ctsGetLayout(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var privateData:PrivateData_t):Integer;

  function XMS_ctsSetLayout(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var layoutList:Acs_3GVConf_LayoutList;Var privateData:PrivateData_t):Integer;

	function XMS_ctsGetVisibleList(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var privateData:PrivateData_t):Integer;

  function XMS_ctsSetVisibleList(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var visableList:Acs_3GVConf_VisibleList;Var privateData:PrivateData_t):Integer;

	function XMS_ctsPutTextInPicture(acsHandle:Longword;s8DstFile:Pchar;Var paramItem:PutTextInPicture_Param;u32ParamSum:Longword;Var privateData:PrivateData_t):Integer;

  function XMS_ctsRestart3GVConf(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var privateData:PrivateData_t):Integer;

	function XMS_acsGetRelateMod(acsHandle:Longword;u8ModType:Byte;u8UnitID:Byte):Integer;
	
	function XMS_ctsPutUsrEvt(acsHandle:Longword;Var deviceID:DeviceID_t;Var pUserEvt:UserEvt_Head_t):Integer;

	function XMS_acsLedCtrl(acsHandle:Longword;u8DspUnitID:Byte;Var pLedCtrl:UserLedCtrl):integer;

implementation

Function LoadDJApi():Byte;
Begin
  DJApiHandle := LoadLibrary('DJAcsAPI.dll');

  if DJApiHandle <> 0 then
  begin
       g_pDJApiSetMaster:=GetProcAddress(DJApiHandle, 'XMS_acsSetMaster');
       if g_pDJApiSetMaster=nil  then
       begin
          ShowMessage('XMS_acsSetMaster∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiOpenStream:=GetProcAddress(DJApiHandle, 'XMS_acsOpenStream');
       if g_pDJApiOpenStream=nil  then
       begin
          ShowMessage('XMS_acsOpenStream∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiSetEsr:=GetProcAddress(DJApiHandle,'XMS_acsSetESR');
       if g_pDJApiSetEsr=nil  then
       begin
          ShowMessage('XMS_acsSetESR∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiGetDevList:=GetProcAddress(DJApiHandle,'XMS_acsGetDeviceList');
       if g_pDJApiSetEsr=nil  then
       begin
          ShowMessage('XMS_acsGetDeviceList∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiOpenDevice:=GetProcAddress(DJApiHandle,'XMS_ctsOpenDevice');
       if g_pDJApiOpenDevice=nil then
       begin
          ShowMessage('XMS_ctsOpenDevice∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiSetParam:=GetProcAddress(DJApiHandle,'XMS_ctsSetParam');
       if g_pDJApiSetParam=nil then
       begin
          ShowMessage('XMS_ctsSetParam∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiResetDevice:=GetProcAddress(DJApiHandle,'XMS_ctsResetDevice');
       if g_pDJApiResetDevice=nil then
       begin
          ShowMessage('XMS_ctsResetDevice∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiGetDevState:=GetProcAddress(DJApiHandle,'XMS_ctsGetDevState');
       if g_pDJApiGetDevState=nil then
       begin
          ShowMessage('XMS_ctsGetDevState∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiUnlinkDevice:=GetProcAddress(DJApiHandle,'XMS_ctsUnlinkDevice');
       if g_pDJApiUnlinkDevice=nil then
       begin
          ShowMessage('XMS_ctsUnlinkDevice∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiLinkDevice:=GetProcAddress(DJApiHandle,'XMS_ctsLinkDevice');
       if g_pDJApiLinkDevice=nil then
       begin
          ShowMessage('XMS_ctsLinkDevice∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiSendIOData:=GetProcAddress(DJApiHandle,'XMS_ctsSendIOData');
       if g_pDJApiSendIOData=nil then
       begin
          ShowMessage('XMS_ctsSendIOData∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiSetDevTimer:=GetProcAddress(DJApiHandle,'XMS_ctsSetDevTimer');
       if g_pDJApiSetDevTimer=nil then
       begin
          ShowMessage('XMS_ctsSetDevTimer∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiMakeCallOut:=GetProcAddress(DJApiHandle,'XMS_ctsMakeCallOut');
       if g_pDJApiMakeCallOut=nil then
       begin
          ShowMessage('XMS_ctsMakeCallOut∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiClearCall:=GetProcAddress(DJApiHandle,'XMS_ctsClearCall');
       if g_pDJApiClearCall=nil then
       begin
          ShowMessage('XMS_ctsClearCall∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;
       
       g_pDJApiLeaveFromConf:=GetProcAddress(DJApiHandle,'XMS_ctsLeaveFromConf');
       if g_pDJApiLeaveFromConf=nil then
       begin
          ShowMessage('XMS_ctsLeaveFromConf∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;
       
       g_pDJApiJoinToConf := GetProcAddress(DJApiHandle, 'XMS_ctsJoinToConf');
       if g_pDJApiJoinToConf=nil then
       begin
          ShowMessage('XMS_ctsJoinToConf∫Ø ˝º”‘ÿ ß∞‹');
          result:=0;
          exit;
       end;

       g_pDJApiCloseStream:=GetProcAddress(DJApiHandle,'XMS_acsCloseStream');
       if g_pDJApiCloseStream=nil then
       begin
          ShowMessage('XMS_acsCloseStream∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiInitPlayIndex:=GetProcAddress(DJApiHandle,'XMS_ctsInitPlayIndex');
       if g_pDJApiInitPlayIndex=nil then
       begin
          ShowMessage('XMS_ctsInitPlayIndex∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiBuildPlayIndex:=GetProcAddress(DJApiHandle,'XMS_ctsBuildPlayIndex');
       if g_pDJApiBuildPlayIndex=nil then
       begin
          ShowMessage('XMS_ctsBuildPlayIndex∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiControlPlay:=GetProcAddress(DJApiHandle,'XMS_ctsControlPlay');
       if g_pDJApiControlPlay=nil then
       begin
          ShowMessage('XMS_ctsControlPlay∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

       g_pDJApiAlertCall:=GetProcAddress(DJApiHandle,'XMS_ctsAlertCall');
       if g_pDJApiAlertCall=nil then
       begin
          ShowMessage('XMS_ctsAlertCall∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiAnswerCallIn:=GetProcAddress(DJApiHandle,'XMS_ctsAnswerCallIn');
       if g_pDJApiAnswerCallIn=nil then
       begin
          ShowMessage('XMS_ctsAnswerCallIn∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiPlay:=GetProcAddress(DJApiHandle,'XMS_ctsPlay');
       if g_pDJApiPlay=nil then
       begin
          ShowMessage('XMS_ctsPlay∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiRecord:=GetProcAddress(DJApiHandle,'XMS_ctsRecord');
       if g_pDJApiRecord=nil then
       begin
          ShowMessage('XMS_ctsRecord∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiControlRecord:=GetProcAddress(DJApiHandle,'XMS_ctsControlRecord');
       if g_pDJApiControlRecord=nil then
       begin
          ShowMessage('XMS_ctsControlRecord∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiLedCtrl:=GetProcAddress(DJApiHandle,'XMS_acsLedCtrl');
       if g_pDJApiLedCtrl=nil then
       begin
          ShowMessage('XMS_acsLedCtrl∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiPutUsrEvt:=GetProcAddress(DJApiHandle,'XMS_ctsPutUsrEvt');
       if g_pDJApiPutUsrEvt=nil then
       begin
          ShowMessage('XMS_ctsPutUsrEvt∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiGetRelateMod:=GetProcAddress(DJApiHandle,'XMS_acsGetRelateMod');
       if g_pDJApiGetRelateMod=nil then
       begin
          ShowMessage('XMS_acsGetRelateMod∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiRestart3GVConf:=GetProcAddress(DJApiHandle,'XMS_ctsRestart3GVConf');
       if g_pDJApiRestart3GVConf=nil then
       begin
          ShowMessage('XMS_ctsRestart3GVConf∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiPutTextInPicture:=GetProcAddress(DJApiHandle,'XMS_ctsPutTextInPicture');
       if g_pDJApiPutTextInPicture=nil then
       begin
          ShowMessage('XMS_ctsPutTextInPicture∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiSetVisibleList:=GetProcAddress(DJApiHandle,'XMS_ctsSetVisibleList');
       if g_pDJApiSetVisibleList=nil then
       begin
          ShowMessage('XMS_ctsSetVisibleList∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiGetVisibleList:=GetProcAddress(DJApiHandle,'XMS_ctsGetVisibleList');
       if g_pDJApiGetVisibleList=nil then
       begin
          ShowMessage('XMS_ctsGetVisibleList∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiSetLayout:=GetProcAddress(DJApiHandle,'XMS_ctsSetLayout');
       if g_pDJApiSetLayout=nil then
       begin
          ShowMessage('XMS_ctsSetLayout∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiGetLayout:=GetProcAddress(DJApiHandle,'XMS_ctsGetLayout');
       if g_pDJApiGetLayout=nil then
       begin
          ShowMessage('XMS_ctsGetLayout∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiClear3GVConf:=GetProcAddress(DJApiHandle,'XMS_ctsClear3GVConf');
       if g_pDJApiClear3GVConf=nil then
       begin
          ShowMessage('XMS_ctsClear3GVConf∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiLeaveFrom3GVConf:=GetProcAddress(DJApiHandle,'XMS_ctsLeaveFrom3GVConf');
       if g_pDJApiLeaveFrom3GVConf=nil then
       begin
          ShowMessage('XMS_ctsLeaveFrom3GVConf∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiJoinTo3GVConf:=GetProcAddress(DJApiHandle,'XMS_ctsJoinTo3GVConf');
       if g_pDJApiJoinTo3GVConf=nil then
       begin
          ShowMessage('XMS_ctsJoinTo3GVConf∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiSendRawFrame:=GetProcAddress(DJApiHandle,'XMS_ctsSendRawFrame');
       if g_pDJApiSendRawFrame=nil then
       begin
          ShowMessage('XMS_ctsSendRawFrame∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiSendAppData:=GetProcAddress(DJApiHandle,'XMS_ctxSendAppData');
       if g_pDJApiSendAppData=nil then
       begin
          ShowMessage('XMS_ctxSendAppData∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiLink:=GetProcAddress(DJApiHandle,'XMS_ctxLink');
       if g_pDJApiLink=nil then
       begin
          ShowMessage('XMS_ctxLink∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiRegister:=GetProcAddress(DJApiHandle,'XMS_ctxRegister');
       if g_pDJApiRegister=nil then
       begin
          ShowMessage('XMS_ctxRegister∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiQueryLicense:=GetProcAddress(DJApiHandle,'XMS_acsQueryLicense');
       if g_pDJApiQueryLicense=nil then
       begin
          ShowMessage('XMS_acsQueryLicense∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiControl3gppRecord:=GetProcAddress(DJApiHandle,'XMS_ctsControl3gppRecord');
       if g_pDJApiControl3gppRecord=nil then
       begin
          ShowMessage('XMS_ctsControl3gppRecord∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApi3gppRecord:=GetProcAddress(DJApiHandle,'XMS_cts3gppRecord');
       if g_pDJApi3gppRecord=nil then
       begin
          ShowMessage('XMS_cts3gppRecord∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiControl3gppPlay:=GetProcAddress(DJApiHandle,'XMS_ctsControl3gppPlay');
       if g_pDJApiControl3gppPlay=nil then
       begin
          ShowMessage('XMS_ctsControl3gppPlay∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApi3gppPlay:=GetProcAddress(DJApiHandle,'XMS_cts3gppPlay');
       if g_pDJApi3gppPlay=nil then
       begin
          ShowMessage('XMS_cts3gppPlay∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiBuildPlay3gppIndex:=GetProcAddress(DJApiHandle,'XMS_ctsBuildPlay3gppIndex');
       if g_pDJApiBuildPlay3gppIndex=nil then
       begin
          ShowMessage('XMS_ctsBuildPlay3gppIndex∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;


      g_pDJApiInitPlay3gppIndex:=GetProcAddress(DJApiHandle,'XMS_ctsInitPlay3gppIndex');
       if g_pDJApiInitPlay3gppIndex=nil then
       begin
          ShowMessage('XMS_ctsInitPlay3gppIndex∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiControlRecordCSP:=GetProcAddress(DJApiHandle,'XMS_ctsControlRecordCSP');
       if g_pDJApiControlRecordCSP=nil then
       begin
          ShowMessage('XMS_ctsControlRecordCSP∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiRecordCSP:=GetProcAddress(DJApiHandle,'XMS_ctsRecordCSP');
       if g_pDJApiRecordCSP=nil then
       begin
          ShowMessage('XMS_ctsRecordCSP∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiControlPlayCSP:=GetProcAddress(DJApiHandle,'XMS_ctsControlPlayCSP');
       if g_pDJApiControlPlayCSP=nil then
       begin
          ShowMessage('XMS_ctsControlPlayCSP∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiSendCSPData:=GetProcAddress(DJApiHandle,'XMS_ctsSendCSPData');
       if g_pDJApiSendCSPData=nil then
       begin
          ShowMessage('XMS_ctsSendCSPData∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiPlayCSP:=GetProcAddress(DJApiHandle,'XMS_ctsPlayCSP');
       if g_pDJApiPlayCSP=nil then
       begin
          ShowMessage('XMS_ctsPlayCSP∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiOpenStreamExt:=GetProcAddress(DJApiHandle,'XMS_acsOpenStreamExt');
       if g_pDJApiOpenStreamExt=nil then
       begin
          ShowMessage('XMS_acsOpenStreamExt∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiSendSignalMsg:=GetProcAddress(DJApiHandle,'XMS_ctsSendSignalMsg');
       if g_pDJApiSendSignalMsg=nil then
       begin
          ShowMessage('XMS_ctsSendSignalMsg∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiCloseStreamExt:=GetProcAddress(DJApiHandle,'XMS_acsCloseStreamExt');
       if g_pDJApiPlayCSP=nil then
       begin
          ShowMessage('XMS_acsCloseStreamExt∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiSetTimer:=GetProcAddress(DJApiHandle,'XMS_acsSetTimer');
       if g_pDJApiSetTimer=nil then
       begin
          ShowMessage('XMS_acsSetTimer∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiCloseDevice:=GetProcAddress(DJApiHandle,'XMS_ctsCloseDevice');
       if g_pDJApiCloseDevice=nil then
       begin
          ShowMessage('XMS_ctsCloseDevice∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiSetDevGroup:=GetProcAddress(DJApiHandle,'XMS_ctsSetDevGroup');
       if g_pDJApiSetDevGroup=nil then
       begin
          ShowMessage('XMS_ctsSetDevGroup∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiGetParam:=GetProcAddress(DJApiHandle,'XMS_ctsGetParam');
       if g_pDJApiGetParam=nil then
       begin
          ShowMessage('XMS_ctsGetParam∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiClearConf:=GetProcAddress(DJApiHandle,'XMS_ctsClearConf');
       if g_pDJApiClearConf=nil then
       begin
          ShowMessage('XMS_ctsClearConf∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

      g_pDJApiSendFax:=GetProcAddress(DJApiHandle,'XMS_ctsSendFax');
       if g_pDJApiSendFax=nil then
       begin
          ShowMessage('XMS_ctsSendFax∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;
       
       g_pDJApiStopSendFax:=GetProcAddress(DJApiHandle,'XMS_ctsStopSendFax');
       if g_pDJApiStopSendFax=nil then
       begin
          ShowMessage('XMS_ctsStopSendFax∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;
       
       g_pDJApiReceiveFax:=GetProcAddress(DJApiHandle,'XMS_ctsReceiveFax');
       if g_pDJApiReceiveFax=nil then
       begin
          ShowMessage('XMS_ctsReceiveFax∫Ø ˝º”‘ÿ ß∞‹');
          result:=0;
          exit;
       end;
       
       g_pDJApiStopReceiveFax:=GetProcAddress(DJApiHandle,'XMS_ctsStopReceiveFax');
       if g_pDJApiStopReceiveFax=nil then
       begin
          ShowMessage('XMS_ctsStopReceiveFax∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;
       
       g_pDJApiChangeMonitorFilter:=GetProcAddress(DJApiHandle,'XMS_ctsChangeMonitorFilter');
       if g_pDJApiChangeMonitorFilter=nil then
       begin
          ShowMessage('XMS_ctsChangeMonitorFilter∫Ø ˝º”‘ÿ ß∞‹°£');
          result:=0;
          exit;
       end;

  end;
  result:=1;
end;

function XMS_acsOpenStream(var acsHandle:Longword;Var serverID:ServerID_t;u8AppID:Byte;u32SendQSize:Longword;
                                        u32RecvQSize:Longword;s32DebugOn:Integer;var privateData:PrivateData_t):integer;
begin
  if LoadDJApi() <= 0 then
  begin
    result := -1;
  end
  else
  begin
    result := TXMS_acsOpenStream(g_pDJApiOpenStream)(pointer(@acsHandle),pointer(@serverID),u8AppID,u32SendQSize,u32RecvQSize,s32DebugOn,pointer(@privateData));
  end;
end;

function XMS_acsCloseStream(acsHandle:Longword;Var privateData:PrivateData_t):integer;
Var
  ret:integer;
begin
  ret:=TXMS_acsCloseStream(g_pDJApiCloseStream)(acsHandle,pointer(@privateData));
  FreeLibrary(DJApiHandle);
  result:=ret;
end;

function XMS_acsSetMaster(acsHandle:Longword;u8Master:Byte;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_acsSetMaster(g_pDJApiSetMaster)(acsHandle,u8Master,pointer(@privateData));
end;

function XMS_acsSetEsr(acsHandle:Longword;esr:EsrFunc;esrParam:Longword;notifyAll:Integer):integer;
begin
  result:= TXMS_acsSetEsr(g_pDJApiSetEsr)(acsHandle,esr,esrParam,notifyAll);
end;

function XMS_acsGetDeviceList(acsHandle:Longword;var privateData:PrivateData_t):integer;
begin
  result:=TXMS_acsGetDeviceList(g_pDJApiGetDevList)(acsHandle,pointer(@privateData));
end;

function XMS_acsSetTimer(acsHandle:LongWord;u32Elapse:Cardinal):integer;
begin
  result:=TXMS_acsSetTimer(g_pDJApiSetTimer)(acsHandle,u32Elapse);
end;

function XMS_ctsOpenDevice(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsOpenDevice(g_pDJApiOpenDevice)(acsHandle,pointer(@deviceID),pointer(@privateData));
end;

function XMS_ctsCloseDevice(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsCloseDevice(g_pDJApiCloseDevice)(acsHandle,pointer(@deviceID),pointer(@privateData));
end;

function XMS_ctsResetDevice(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsResetDevice(g_pDJApiResetDevice)(acsHandle,pointer(@deviceID),pointer(@privateData));
end;

function XMS_ctsSetDevTimer(acsHandle:Longword;Var deviceID:DeviceID_t;u32Elapse:Integer):integer;
begin
  result:=TXMS_ctsSetDevTimer(g_pDJApiSetDevTimer)(acsHandle,pointer(@deviceID),u32Elapse);
end;

function XMS_ctsGetDevState(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsGetDevState(g_pDJApiGetDevState)(acsHandle,pointer(@deviceID),pointer(@privateData));
end;

function XMS_ctsSetDevGroup(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsSetDevGroup(g_pDJApiSetDevGroup)(acsHandle,pointer(@deviceID),pointer(@privateData));
end;

function XMS_ctsMakeCallOut(acsHandle:Longword;Var deviceID:DeviceID_t;callingID:pointer;calledID:pointer;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsMakeCallOut(g_pDJApiMakeCallOut)(acsHandle,pointer(@deviceID),callingID,calledID,pointer(@privateData));
end;

function XMS_ctsSetParam(acsHandle:Longword;Var deviceID:DeviceID_t;u16ParamCmdType:Word;u16ParamDataSize:Word;paramData:pointer):integer;
begin
  result:=TXMS_ctsSetParam(g_pDJApiSetParam)(acsHandle,pointer(@deviceID),u16ParamCmdType,u16ParamDataSize,paramData);
end;

function XMS_ctsGetParam(acsHandle:Longword;Var deviceID:DeviceID_t;u16ParamCmdType:Word;u16ParamDataSize:Word;paramData:pointer):integer;
begin
  result:=TXMS_ctsGetParam(g_pDJApiGetParam)(acsHandle,pointer(@deviceID),u16ParamCmdType,u16ParamDataSize,paramData);
end;

function XMS_ctsAlertCall(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsAlertCall(g_pDJApiAlertCall)(acsHandle,pointer(@deviceID),pointer(@privateData));
end;

function XMS_ctsAnswerCallIn(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsAnswerCallIn(g_pDJApiAnswerCallIn)(acsHandle,pointer(@deviceID),pointer(@privateData));
end;

function XMS_ctsUnlinkDevice(acsHandle:Longword;Var srcDeviceID:DeviceID_t;Var destDeviceID:DeviceID_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsUnlinkDevice(g_pDJApiUnLinkDevice)(acsHandle,pointer(@srcDeviceID),pointer(@destDeviceID),pointer(@privateData));
end;

function XMS_ctsLinkDevice(acsHandle:Longword;Var srcDeviceID:DeviceID_t;Var destDeviceID:DeviceID_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsLinkDevice(g_pDJApiLinkDevice)(acsHandle,pointer(@srcDeviceID),pointer(@destDeviceID),pointer(@privateData));
end;

function XMS_ctsClearCall(acsHandle:Longword;Var deviceID:DeviceID_t;s32ClearCause:integer;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsClearCall(g_pDJApiClearCall)(acsHandle,pointer(@deviceID),s32ClearCause,pointer(@privateData));
end;

function XMS_ctsJoinToConf(acsHandle:Longword;Var confDeviceID:DeviceID_t;Var mediaDeviceID:DeviceID_t;Var confParam:CmdParamData_Conf_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsJoinToConf(g_pDJApiJoinToConf)(acsHandle,pointer(@confDeviceID),pointer(@mediaDeviceID),pointer(@confParam),pointer(@privateData));
end;

function XMS_ctsLeaveFromConf(acsHandle:Longword;Var confDeviceID:DeviceID_t;Var mediaDeviceID:DeviceID_t;Var confParam:CmdParamData_Conf_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsLeaveFromConf(g_pDJApiLeaveFromConf)(acsHandle,pointer(@confDeviceID),pointer(@mediaDeviceID),pointer(@confParam),pointer(@privateData));
end;

function XMS_ctsClearConf(acsHandle:Longword;Var confDeviceID:DeviceID_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsClearConf(g_pDJApiClearConf)(acsHandle,pointer(@confDeviceID),pointer(@privateData));
end;

function XMS_ctsPlay(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var playProperty:PlayProperty_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsPlay(g_pDJApiPlay)(acsHandle,pointer(@mediaDeviceID),pointer(@playProperty),pointer(@privateData));
end;

function XMS_ctsInitPlayIndex(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsInitPlayIndex(g_pDJApiInitPlayIndex)(acsHandle,pointer(@mediaDeviceID),pointer(@privateData));
end;

function XMS_ctsBuildPlayIndex(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var playProperty:PlayProperty_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsBuildPlayIndex(g_pDJApiBuildPlayIndex)(acsHandle,pointer(@mediaDeviceID),pointer(@playProperty),pointer(@privateData));
end;

function XMS_ctsControlPlay(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var controlPlay:ControlPlay_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsControlPlay(g_pDJApiControlPlay)(acsHandle,pointer(@mediaDeviceID),pointer(@controlPlay),pointer(@privateData));
end;

function XMS_ctsRecord(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var recordProperty:RecordProperty_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsRecord(g_pDJApiRecord)(acsHandle,pointer(@mediaDeviceID),pointer(@recordProperty),pointer(@privateData));
end;

function XMS_ctsControlRecord(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var controlRecord:ControlRecord_t;Var privateData:PrivateData_t):integer;
begin
  result:=TXMS_ctsControlRecord(g_pDJApiControlRecord)(acsHandle,pointer(@mediaDeviceID),pointer(@controlRecord),pointer(@privateData));
end;

function XMS_ctsSendFax(acsHandle:Longword;Var faxDeviceID:DeviceID_t;Var mediaDeviceID:DeviceID_t;s8TiffFile:PChar;s8LocalID:Pchar;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsSendFax(g_pDJApiSendFax)(acsHandle,pointer(@faxDeviceID),pointer(@mediaDeviceID),s8TiffFile,s8LocalID,pointer(@privateData));
end;

function XMS_ctsStopSendFax(acsHandle:Longword;Var faxDeviceID:DeviceID_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsStopSendFax(g_pDJApiStopSendFax)(acsHandle,pointer(@faxDeviceID),pointer(@privateData));
end;

function XMS_ctsReceiveFax(acsHandle:Longword;Var faxDeviceID:DeviceID_t;Var mediaDeviceID:DeviceID_t;s8TiffFile:PChar;s8LocalID:Pchar;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsReceiveFax(g_pDJApiReceiveFax)(acsHandle,pointer(@faxDeviceID),pointer(@mediaDeviceID),s8TiffFile,s8LocalID,pointer(@privateData));
end;

function XMS_ctsStopReceiveFax(acsHandle:Longword;Var faxDeviceID:DeviceID_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsStopReceiveFax(g_pDJApiStopReceiveFax)(acsHandle,pointer(@faxDeviceID),pointer(@privateData));
end;

function XMS_ctsChangeMonitorFilter(acsHandle:Longword;Var deviceID:DeviceID_t;monitorFilter:Longword;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsChangeMonitorFilter(g_pDJApiChangeMonitorFilter)(acsHandle,pointer(@deviceID),monitorFilter,pointer(@privateData));
end;

function XMS_ctsSendIOData(acsHandle:Longword;Var deviceID:DeviceID_t;u16IoType:Word;u16IoDataLen:Word;paramData:pointer):integer;
begin
  result:=TXMS_ctsSendIOData(g_pDJApiSendIOData)(acsHandle,pointer(@deviceID),u16IoType,u16IoDataLen,paramData);
end;

function XMS_ctsSendSignalMsg(acsHandle:Longword;Var deviceID:DeviceID_t;u16SignalMsgType:Word):Integer;
begin
  result:=TXMS_ctsSendSignalMsg(g_pDJApiSendSignalMsg)(acsHandle,pointer(@deviceID),u16SignalMsgType);
end;

function XMS_acsOpenStreamExt(acsHandle:Longword;Var serverID:ServerID_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_acsOpenStreamExt(g_pDJApiOpenStreamExt)(acsHandle,pointer(@serverID),pointer(@privateData));
end;

function XMS_acsCloseStreamExt(acsHandle:Longword;Var serverID:ServerID_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_acsCloseStreamExt(g_pDJApiOpenStreamExt)(acsHandle,pointer(@serverID),pointer(@privateData));
end;

function XMS_ctsPlayCSP(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var cspPlayProperty:CSPPlayProperty_t; Var privateData :PrivateData_t):Integer;
begin
  result:=TXMS_ctsPlayCSP(g_pDJApiPlayCSP)(acsHandle,pointer(@mediaDeviceID),pointer(@cspPlayProperty),pointer(@privateData));
end;

function XMS_ctsSendCSPData(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var cspDataInfo :CSPPlayDataInfo_t;cspData:Pointer;var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsSendCSPData(g_pDJApiSendCSPData)(acsHandle,pointer(@mediaDeviceID),pointer(@cspDataInfo),cspData,pointer(@privateData));
end;

function XMS_ctsControlPlayCSP(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var controlPlay:ControlPlay_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsControlPlayCSP(g_pDJApiControlPlayCSP)(acsHandle,pointer(@mediaDeviceID),pointer(@controlPlay),pointer(@privateData));
end;

function XMS_ctsRecordCSP(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var recCSPProperty:RecordCSPProperty_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsRecordCSP(g_pDJApiSendCSPData)(acsHandle,pointer(@mediaDeviceID),pointer(@recCSPProperty),pointer(@privateData));
end;

function XMS_ctsControlRecordCSP(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var controlRecord:ControlRecord_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsControlRecordCSP(g_pDJApiControlRecordCSP)(acsHandle,pointer(@mediaDeviceID),pointer(@controlRecord),pointer(@privateData));
end;

function XMS_ctsInitPlay3gppIndex(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsInitPlay3gppIndex(g_pDJApiInitPlay3gppIndex)(acsHandle,pointer(@mediaDeviceID),pointer(@privateData));
end;

function XMS_ctsBuildPlay3gppIndex(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var playProperty:Play3gppProperty_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsBuildPlay3gppIndex(g_pDJApiBuildPlay3gppIndex)(acsHandle,POinter(@mediaDeviceID),pointer(@playProperty),pointer(@privateData));
end;

function XMS_cts3gppPlay(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var playProperty:Play3gppProperty_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_cts3gppPlay(g_pDJApi3gppPlay)(acsHandle,pointer(@mediaDeviceID),pointer(@playProperty),pointer(@privateData));
end;

function XMS_ctsControl3gppPlay(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var controlPlay:Control3gppPlay_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsControl3gppPlay(g_pDJApiControl3gppPlay)(acsHandle,pointer(@mediaDeviceID),pointer(@controlPlay),pointer(@privateData));
end;

function XMS_cts3gppRecord(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var recordProperty:Record3gppProperty_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_cts3gppRecord(g_pDJApi3gppRecord)(acsHandle,pointer(@mediaDeviceID),pointer(@recordProperty),pointer(@privateData));
end;

function XMS_ctsControl3gppRecord(acsHandle:Longword;Var mediaDeviceID:DeviceID_t;Var controlRecord:Control3gppRecord_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsControl3gppRecord(g_pDJApiControl3gppRecord)(acsHandle,pointer(@mediaDeviceID),pointer(@controlRecord),pointer(@privateData));
end;

function XMS_acsQueryLicense(acsHandle:Longword;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_acsQueryLicense(g_pDJApiQueryLicense)(acsHandle,pointer(@deviceID),pointer(@privateData));
end;

function XMS_ctxRegister(acsHandle:Longword;s8AppRegName:PChar;u8RegType:Byte;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctxRegister(g_pDJApiRegister)(acsHandle,s8AppRegName,u8RegType,pointer(@privateData));
end;

function XMS_ctxLink(acsHandle:Longword;Var srcDev:DeviceID_t;Var destDev:DeviceID_t;u8Option:Byte;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctxLink(g_pDJApiLink)(acsHandle,pointer(@srcDev),pointer(@destDev),u8Option,pointer(@privateData));
end;

function XMS_ctxSendAppData(acsHandle:Longword;s8SrcAppRegName:Pchar;s8DestAppRegName:Pchar;u8AppReqType:Byte;
                              pData:Pointer;u32DataSize:Longword;u8SrcAppUnitID:Byte;u8DestAppUnitID:Byte;
                              Var srcDevice:DeviceID_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctxSendAppData(g_pDJApiSendAppData)(acsHandle,s8SrcAppRegName,s8DestAppRegName,u8AppReqType,
                              pData,u32DataSize,u8SrcAppUnitID,u8DestAppUnitID,pointer(@srcDevice),pointer(@privateData));
end;

function XMS_ctsSendRawFrame(acsHandle:Longword;Var deviceID:DeviceID_t;u16FrameSize:Word;pData:Pointer):Integer;
begin
  result:=TXMS_ctsSendRawFrame(g_pDJApiSendRawFrame)(acsHandle,pointer(@deviceID),u16FrameSize,pData);
end;

function XMS_ctsJoinTo3GVConf(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var deviceID:DeviceID_t;Var input:Acs_MediaEx_Input_V;
                                Var output:Acs_MediaEx_Output_V;u8Visible:Byte;var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsJoinTo3GVConf(g_pDJApiJoinTo3GVConf)(acsHandle,pointer(@device3GVConfID),pointer(@deviceID),pointer(@input),pointer(@output),u8Visible,pointer(@privateData));
end;

function XMS_ctsLeaveFrom3GVConf(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var deviceID:DeviceID_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsLeaveFrom3GVConf(g_pDJApiLeaveFrom3GVConf)(acsHandle,pointer(@device3GVConfID),pointer(@deviceID),pointer(@privateData));
end;

function XMS_ctsClear3GVConf(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsClear3GVConf(g_pDJApiClear3GVConf)(acsHandle,pointer(@device3GVConfID),pointer(@privateData));
end;

function XMS_ctsGetLayout(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsGetLayout(g_pDJApiGetLayout)(acsHandle,pointer(@device3GVConfID),pointer(@privateData));
end;

function XMS_ctsSetLayout(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var layoutList:Acs_3GVConf_LayoutList;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsSetLayout(g_pDJApiSetLayout)(acsHandle,pointer(@device3GVConfID),pointer(@layoutList),pointer(@privateData));
end;

function XMS_ctsGetVisibleList(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsGetVisibleList(g_pDJApiGetVisibleList)(acsHandle,pointer(@device3GVConfID),pointer(@privateData));
end;

function XMS_ctsSetVisibleList(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var visableList:Acs_3GVConf_VisibleList;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsSetVisibleList(g_pDJApiSetVisibleList)(acsHandle,pointer(@device3GVConfID),pointer(@visableList),pointer(@privateData));
end;

function XMS_ctsPutTextInPicture(acsHandle:Longword;s8DstFile:Pchar;Var paramItem:PutTextInPicture_Param;u32ParamSum:Longword;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsPutTextInPicture(g_pDJApiPutTextInPicture)(acsHandle,s8DstFile,pointer(@paramItem),u32ParamSum,pointer(@privateData));
end;

function XMS_ctsRestart3GVConf(acsHandle:Longword;Var device3GVConfID:DeviceID_t;Var privateData:PrivateData_t):Integer;
begin
  result:=TXMS_ctsRestart3GVConf(g_pDJApiRestart3GVConf)(acsHandle,pointer(@device3GVConfID),pointer(@privateData));
end;

function XMS_acsGetRelateMod(acsHandle:Longword;u8ModType:Byte;u8UnitID:Byte):Integer;
begin
  result:=TXMS_acsGetRelateMod(g_pDJApiGetRelateMod)(acsHandle,u8ModType,u8UnitID);
end;

function XMS_ctsPutUsrEvt(acsHandle:Longword;Var deviceID:DeviceID_t;Var pUserEvt:UserEvt_Head_t):Integer;
begin
  result:=TXMS_ctsPutUsrEvt(g_pDJApiPutUsrEvt)(acsHandle,pointer(@deviceID),pointer(@pUserEvt));
end;

function XMS_acsLedCtrl(acsHandle:Longword;u8DspUnitID:Byte;Var pLedCtrl:UserLedCtrl):Integer;
begin
  result:=TXMS_acsLedCtrl(g_pDJApiLedCtrl)(acsHandle,u8DspUnitID,pointer(@pLedCtrl));
end;

end.

