unit DJDial;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls, ExtCtrls, GlobalVal,inifiles,CAS_Common_Cfg,Analog_Common_Code,
  XMS_Dial_Sub,XMS_Dial_Event,DJAcsDataDef,DJAcsDevState,TDJAcsAPIDef;

Type
  TForm1 = class(TForm)
    Panel1: TPanel;
    Config: TGroupBox;

    ListView1: TListView;
    ListView2: TListView;
    ListView3: TListView;
    ListView4: TListView;

    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;

    ListBox1: TListBox;

    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;

    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Edit4: TEdit;
    Edit5: TEdit;
    Edit6: TEdit;

    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;

    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    RadioButton3: TRadioButton;

    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormSimulate(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure ReOpen_AllDevice(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure ExitDial(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure OnBtnRemove(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
  private
    { Private declarations }
  public
    g_NumOfListBox:integer;
    nNeedCloseXms:Integer;

    Procedure ReadIniFile();
    Procedure InitListMain();
    Procedure InitListUser();
    Procedure InitListPcm();
    Procedure InitListMsg();
    Procedure InitListCount();
    Procedure InitTextBox();
    Procedure FetchFromText();
    Procedure WriteToConfig();
    Procedure ListView1AddItem(nNumOfItemToBeAdded:Integer);
    Procedure ListView2AddItem(nNumOfItemToBeAdded:Integer);
    Procedure ListView3AddItem(nNumOfItemToBeAdded:Integer);
    Procedure ListView4AddItem(nNumOfItemToBeAdded:Integer);
    Procedure AddMsg(msgBuf:String);

    Function InitSystem():Byte;
    Function LoadDJApi():Byte;
    { Public declarations }
  end;

var
  Form1: TForm1;
  g_gLobalVar:Tglobal;
  msgBuf:string;
  MyCs:TRTLCriticalSection;//临界区

  iLoopStartSearchFreeTrunk:Integer;

  Procedure DispEventInfo(AcsEvt:pointer);
  Procedure AddDeviceRes(AcsDevList:pointer);
  Procedure CheckRemoveReady(s8DspModID:Shortint);
  Procedure DrawCount_RemoveState(s8ModID:Shortint);
  Procedure DrawCount_ErrFlag(s8ModID:shortint);
  Procedure DrawCount_Voc(s8ModID:Shortint);
  Procedure Change_Voc_State(pVoice:Pointer;NewState:VOICE_STATE);
  Procedure AddDeviceRes_Voice(s8DspModID:Shortint;pAcsDevList:pointer);
  Procedure AddDeviceRes_Pcm  (s8DspModID:Shortint;pAcsDevList:pointer);
  Procedure AddDeviceRes_Trunk(s8DspModID:Shortint;pAcsDevList:pointer);
  Procedure AddDeviceRes_Board(s8DspModID:Shortint;pAcsDevList:pointer);
  Procedure OpenBoardDevice(s8DspModID:Shortint);
  Procedure RefreshMapTable();
  Procedure	ReDrawAll ();
  Procedure DrawMain_LineState(pTrunk:pointer);
	Procedure	DrawMain_State(pTrunk:pointer);
	Procedure	DrawMain_CallInfo(pTrunk:pointer);
  Procedure OpenAllDevice_Dsp(s8DspModID:Shortint);
  Procedure DrawPcm_TypeAndAlarm(pPcm:Pointer);
  Procedure DrawCount_Pcm(s8ModID:Shortint);
  Procedure DrawUser_State(pTrunk:pointer);
  Procedure DrawUser_LineState(pTrunk:pointer);
  Procedure DrawCount_Trunk(s8ModID:Shortint);
  Procedure OpenDeviceOK(Var m_DeviceID:DeviceID_t);
  Procedure SetGTD_ToneParam(Var pDevice:DeviceID_t);
  Procedure My_InitDtmfBuf (OneTrunk:pointer);
  Procedure Change_UserState(OneTrunk:pointer;NewState:USER_STATE);
  Procedure DrawUser_LinkDev(OneUser:pointer);
  Procedure DrawUser_VocInfo(OneUser:pointer);
  Procedure InitUserChannel(OneUser:pointer);
  Procedure DrawCount_User(s8ModID:ShortInt);
  Procedure Change_State(pTrunk:pointer;NewState:TRUNK_STATE);
  Procedure DrawMain_LinkDev(pTrunk:pointer);
  Procedure InitTrunkChannel(pTrunk:pointer);
  Procedure OpenPcmDevice(OnePcm:pointer);
  Procedure HandleDevState(pEvt:pointer);
  Procedure OpenTrunkDevice(OneTrunk:pointer);
  Procedure OpenVoiceDevice(OneVoc:pointer);
  Procedure CloseDeviceOK(Var pDevice:DeviceID_t);
  Procedure TrunkWork (pTrunk:Pointer;pEvt:Pointer);
  Procedure UserWork (pTrunk:Pointer;pEvt:Pointer);
  Procedure ChannelWork (pTrunk:Pointer;pEvt:Pointer);
  Procedure My_DualLink(Var pDev1:DeviceID_t;Var pDev2:DeviceID_t);
  Procedure My_DualUnlink(Var pDev1:DeviceID_t;Var pDev2:DeviceID_t);
  Procedure ResetTrunk (pTrunk:Pointer);
  Procedure FreeOneFreeVoice(Dev:pointer);
  Procedure PlayTone(Var pVocDevID:DeviceID_t;iPlayType:integer);
  Procedure PlayDTMF(Var pVocDevID:DeviceID_t; DtmfStr:string);
  Procedure SpecialForCas (pTrunk:Pointer;pEvt:Pointer);
  Procedure DrawMain_Analog_Reason(pTrunk:pointer;ErrStr:string);
  Procedure DrawMain_Reason(pTrunk:pointer;s32ErrCode:integer;s32ClearCause:integer);
  Procedure SetGtd_AnalogTrunk(Var pDevId:DeviceID_t);
  Procedure SimulateCallOut();
  Procedure FreeAllDeviceRes();
  Procedure DrawUser_DTMF(Var pOneUser:TRUNK_STRUCT);
  Procedure My_AddDtmfBuf(Var pOneTrunk:TRUNK_STRUCT;TmpDtmf:char);
  Procedure StopPlayTone(Var pVocDevID:DeviceID_t);
  Procedure ResetUser(pTrunk:Pointer;pEvt:Pointer);
  Procedure Remove_OneDsp();

  function  CalDispRow(iSeqID:integer):integer;
  function  My_GetGtdOrPVDCode(Evt:pointer):char;
  function  My_GetDtmfCode(Evt:pointer):char;
  Function  GetString_EventType(s32EventType:Integer):string;
  function  GetString_DeviceMain(nDevMain:Smallint):string;
  function  GetString_ErrorCode ( s32ErrorCode:integer):string;
  function  GetString_DeviceSub(nDeviceSub:Smallint):string;
  function  GetString_LineState (iLineState:integer):string;
  function  GetString_PcmType(iPcmType:Byte):string;
  Function GetString_UserState(iUserID:USER_STATE):string;
  function  GetBit(nSourData:Integer;nBit:Byte):Byte;
  function  SearchOneFreeVoice(pTrunk:pointer;Var pFreeVocDeviceID:DeviceID_t):integer;
  function SearchOneFreeTrunk(pDtmf:Pchar;Var pFreeTrkDeviceID:DeviceID_t):integer;
  function GetOutUserID(pDtmf:PCHAR;Var pUserDeviceID:DeviceID_t):integer;
  function IsTrunk(s16DevSub:Smallint):Boolean;
  function CheckPlayGTGEnd(AcsEvt:pointer):boolean;
implementation

procedure esr(esrParam:Longword);cdecl;
Var
  pAcsEvt:^Acs_Evt_t;
  pAcsEvtTemp:^Acs_Evt_t;
  pAcsDevList:^Acs_Dev_List_Head_t;
  pAcsUnifailure:^Acs_UniFailure_Data;
  EvtType:Integer;
  pDevID:^DeviceID_t;
  pOneTrunk:^TRUNK_STRUCT;
  pOneVoc:^VOICE_STRUCT;
begin
  pAcsEvt:=nil;
  pAcsEvtTemp:=nil;
  pAcsDevList:=nil;
  pDevID:=nil;
  pOneTrunk:=nil;
  pOneVoc:=nil;
  pAcsUnifailure:=nil;

  if esrParam=0 then
    begin
      exit;
    end;

  pAcsEvt:=Pointer(esrParam);

  pAcsEvtTemp:=Pointer(esrParam);
  DispEventInfo(pointer(pAcsEvt)); //结构体或者类函数传参时都以地址传送
  EvtType:=pAcsEvt.m_s32EventType;
  case EvtType of
  integer(XMS_EVT_QUERY_ONE_DSP_START):
    begin
      Form1.ListView1AddItem(g_gLobalVar.AllDeviceRes[pAcsEvt.m_DeviceID.m_s8ModuleID].iSeqID + 1);
    end;

  Integer(XMS_EVT_OPEN_STREAM):
    begin
      Form1.nNeedCloseXms:=1;
      InitializeCriticalSection(MyCs);
    end;

  integer(XMS_EVT_QUERY_DEVICE):
    begin
      if (g_gLobalVar.cfg_iPartWork = 0) or (pAcsEvt.m_DeviceID.m_s8ModuleID = g_gLobalVar.cfg_iPartWorkModuleID) then
       begin
        inc(pAcsEvtTemp);
        pAcsDevList:=Pointer(pAcsEvtTemp);
        AddDeviceRes(pointer(pAcsDevList));
       end;
    end;

  integer(XMS_EVT_QUERY_ONE_DSP_END):
    begin
      if (g_gLobalVar.cfg_iPartWork = 0) or (pAcsEvt.m_DeviceID.m_s8ModuleID = g_gLobalVar.cfg_iPartWorkModuleID) then
        begin
          g_gLobalVar.AllDeviceRes[pAcsEvt.m_DeviceID.m_s8ModuleID].lFlag:=1;
          OpenAllDevice_Dsp(pAcsEvt.m_DeviceID.m_s8ModuleID);
          RefreshMapTable();
          ReDrawAll();
        end;
    end;

  integer(XMS_EVT_QUERY_REMOVE_ONE_DSP_END):
    begin
      if (g_gLobalVar.cfg_iPartWork = 0) or (pAcsEvt.m_DeviceID.m_s8ModuleID = g_gLobalVar.cfg_iPartWorkModuleID) then
        begin
          g_gLobalVar.AllDeviceRes[pAcsEvt.m_DeviceID.m_s8ModuleID].lFlag:=0;
          RefreshMapTable();
          ReDrawAll();
        end;
    end;

  integer(XMS_EVT_QUERY_DEVICE_END):
    begin
    end;

  integer(XMS_EVT_OPEN_DEVICE):
    begin
      OpenDeviceOK(pAcsEvt.m_DeviceID);
    end;

  integer(XMS_EVT_CLOSE_DEVICE):
    begin
      CloseDeviceOK(pAcsEvt.m_DeviceID);
    end;

  integer(XMS_EVT_DEVICESTATE):
    begin
      HandleDevState ( pointer(pAcsEvt) );
    end;

  integer(XMS_EVT_UNIFAILURE):
    begin
      inc(pAcsEvt);
      pAcsUnifailure:=pointer(pAcsEvt);

      if Integer(ACSERR_LINKBROKEN)=pAcsUnifailure.m_s32AcsEvtErrCode then
      begin
        Form1.nNeedCloseXms:=0;
      end;
    end;

  integer(XMS_EVT_MODMONITOR):
    begin
    end;

  else
    begin
     if pAcsEvt.m_DeviceID.m_s16DeviceMain=Smallint(XMS_DEVMAIN_INTERFACE_CH) then
      begin
        pOneTrunk:=pointer(g_gLobalVar.AllDeviceRes[pAcsEvt.m_DeviceID.m_s8ModuleID].pTrunk);
        inc(pOneTrunk, pAcsEvt.m_DeviceID.m_s16ChannelID);
        ChannelWork(pOneTrunk, pointer(pAcsEvt) );
      end
      else if pAcsEvt.m_DeviceID.m_s16DeviceMain=Smallint(XMS_DEVMAIN_VOICE) then
        begin
          pOneVoc:=pointer(g_gLobalVar.AllDeviceRes[pAcsEvt.m_DeviceID.m_s8ModuleID].pVoice);
          inc(pOneVoc,pAcsEvt.m_DeviceID.m_s16ChannelID);
          pDevID:=pointer(@pOneVoc.UsedDevID);
            if pDevID.m_s16DeviceMain=Smallint(XMS_DEVMAIN_INTERFACE_CH) then
              begin
                pOneTrunk:=pointer(g_gLobalVar.AllDeviceRes[pDevID.m_s8ModuleID].pTrunk);
                inc(pOneTrunk,pDevID.m_s16ChannelID);
                ChannelWork (pOneTrunk, pointer(pAcsEvt) );
              end;
        end;
    end;
  end;
end;

Procedure HandleDevState(pEvt:pointer);
Var
  pAcsEvt,pTempEvt:^Acs_Evt_t;
  pOneTrunk:^TRUNK_STRUCT;
  pOnePcm:^PCM_STRUCT;
  pGeneralData:^Acs_GeneralProc_Data;
begin
  pAcsEvt:=nil;
  pTempEvt:=nil;
  pOneTrunk:=nil;
  pOnePcm:=nil;
  pGeneralData:=nil;

  pAcsEvt:=pointer(pEvt);
  if pAcsEvt=nil then
  begin
    exit;
  end;
  pTempEvt:=pointer(pEvt);
  inc(pTempEvt);
  pGeneralData:=pointer(pTempEvt);

  if pAcsEvt=nil then
    begin
      exit;
    end;

  if pAcsEvt.m_DeviceID.m_s16DeviceMain=Smallint(XMS_DEVMAIN_INTERFACE_CH) then
    begin
      pOneTrunk:=pointer(g_gLobalVar.AllDeviceRes[pAcsEvt.m_DeviceID.m_s8ModuleID].pTrunk);
      inc(pOneTrunk,pAcsEvt.m_DeviceID.m_s16ChannelID);

      pOneTrunk.iLineState := pGeneralData.m_s32DeviceState;
		  DrawMain_LineState( pOneTrunk );

      if pAcsEvt.m_DeviceID.m_s16DeviceSub=smallint(XMS_DEVSUB_ANALOG_USER) then
        begin
          DrawUser_LineState( pOneTrunk );
        end;
    end;

  if pAcsEvt.m_DeviceID.m_s16DeviceMain=smallint(XMS_DEVMAIN_DIGITAL_PORT) then
    begin
      pOnePcm:=pointer(g_gLobalVar.AllDeviceRes[pAcsEvt.m_DeviceID.m_s8ModuleID].pPcm);
      inc(pOnePcm,pAcsEvt.m_DeviceID.m_s16ChannelID);
      pOnePcm.u8E1Type := (pGeneralData.m_s32DeviceState shr 16) and 255;
      pOnePcm.s32AlarmVal := (pGeneralData.m_s32DeviceState and 65535);
      DrawPcm_TypeAndAlarm ( pOnePcm );
    end;
end;

Procedure ChannelWork (pTrunk:Pointer;pEvt:Pointer);
Var
  pOneTrunk:^TRUNK_STRUCT;
  pAcsEvt:^Acs_Evt_t;
begin

  pOneTrunk:=nil;
  pAcsEvt:=nil;

  pOneTrunk:=pointer(pTrunk);
  pAcsEvt:=pointer(pEvt);

  if (pTrunk=nil) or (pEvt=nil) then
    begin
      exit;
    end;
  if pOneTrunk.deviceID.m_s16DeviceSub = smallint(XMS_DEVSUB_ANALOG_USER) then
    begin
		  UserWork ( pOneTrunk, pEvt );
    end
	else
    begin
		  TrunkWork ( pOneTrunk, pEvt );
    end;

end;

Procedure UserWork (pTrunk:Pointer;pEvt:Pointer);
Var
  pOneUser:^TRUNK_STRUCT;
  pOneVoice:^VOICE_STRUCT;
  pAcsEvt:^Acs_Evt_t;
  FreeVocDeviceID,FreeTrkDeviceID,OutUserDeviceID:DeviceID_t;
  TmpDtmf:char;
  i,ret:integer;
  MsgStr:string;
  pLinkTrunk,pLinkUser:^TRUNK_STRUCT;
  PrivData:PrivateData_t;
begin

  pOneUser:=nil;
  pOneVoice:=nil;
  pAcsEvt:=nil;
  pLinkTrunk:=nil;
  pLinkUser:=nil;

  PrivData.m_u32DataSize:=0;
  pOneUser:=pointer(pTrunk);
  pAcsEvt:=pointer(pEvt);

  if pAcsEvt=nil then
    begin
      exit;
    end;

  if pAcsEvt.m_s32EventType=integer(XMS_EVT_CLEARCALL) then
    begin
      if (pOneUser.UserState<>USER_FREE) and (pOneUser.UserState<>USER_WAIT_REMOVE) then
        begin
          ResetUser(pOneUser,pAcsEvt);
          exit;
        end;
    end;

  case pOneUser.UserState of
    USER_FREE:
      begin
        if pAcsEvt.m_s32EventType=integer(XMS_EVT_CALLIN) then
          begin
            if SearchOneFreeVoice(pOneUser,FreeVocDeviceID) >= 0 then
              begin
                pOneUser.VocDevID := FreeVocDeviceID;
                pOneVoice:=pointer(g_gLobalVar.AllDeviceRes[FreeVocDeviceID.m_s8ModuleID].pVoice);
                inc(pOneVoice,FreeVocDeviceID.m_s16ChannelID);

                pOneVoice.UsedDevID:=pOneUser.deviceID;
                DrawUser_VocInfo(pOneUser);

                My_DualLink ( FreeVocDeviceID, pOneUser.deviceID );
				        PlayTone ( pOneUser.VocDevID, 0 );		// dial tone

				        Change_UserState ( pOneUser, USER_OFFHOOK );
              end;
          end;
      end;

    USER_CALLOUT:
      begin
      end;

	  USER_LINK:
		  begin
      end;

	  USER_WAITHANGUP:
		  begin
      end;

    USER_OFFHOOK:
      begin
		    TmpDtmf:=My_GetDtmfCode (pAcsEvt);
		    if shortint(TmpDtmf) <> -1 then
          begin
			      My_AddDtmfBuf ( pOneUser^, TmpDtmf );
			      DrawUser_DTMF ( pOneUser^ );

			      StopPlayTone ( pOneUser.VocDevID );

			      if pOneUser.DtmfCount >= g_gLobalVar.cfg_iCalledLen  then
			         begin
                 if g_gLobalVar.cfg_iCallOutRule = 2	then
                    begin
					            i := GetOutUserID(pOneUser.DtmfBuf,OutUserDeviceID);
					            if ( i > 0 ) then
                         begin
                            ret:=XMS_ctsMakeCallOut
                                (g_gLobalVar.g_acsHandle,OutUserDeviceID,pointer(@g_gLobalVar.cfg_CallingNum),
                                pointer(@pOneUser.DtmfBuf),PrivData);
                                  if ret>0 then
                                    begin
                                      PlayTone(pOneUser.VocDevID, 1);
                                      pLinkUser:=pointer(g_gLobalVar.AllDeviceRes[OutUserDeviceID.m_s8ModuleID].pTrunk);
                                      inc(pLinkUser,OutUserDeviceID.m_s16ChannelID);
                                      pOneUser.LinkDevID:=OutUserDeviceID;
                                      pLinkUser.LinkDevID:=pOneUser.deviceID;
                                      DrawUser_LinkDev ( pOneUser );
							                        DrawUser_LinkDev ( pLinkUser );
                                      Change_UserState ( pOneUser, USER_CALLOUT );
							                        Change_UserState ( pLinkUser, USER_RING );
                                      XMS_ctsSetDevTimer(g_gLobalVar.g_acsHandle,OutUserDeviceID,g_gLobalVar.g_Param_Analog.m_u16SendFSKCallerIDTime);
                                    end
                                  else
                                    begin
                                      MsgStr:=Format('XMS_ctsMakeCallOut() FAIL! ret = %d',[ret]);
                                      Form1.AddMsg(MsgStr);
                                    end;
                        end;
                  end;

        i := SearchOneFreeTrunk ( pOneUser.DtmfBuf, FreeTrkDeviceID );
				if  i > 0 then
          begin
            ret:=XMS_ctsMakeCallOut(g_gLobalVar.g_acsHandle,FreeTrkDeviceID,pointer(@g_gLobalVar.cfg_CallingNum),
                           pointer(@pOneUser.DtmfBuf),PrivData);
            if ret > 0 then
              begin
                pLinkTrunk:=pointer(g_gLobalVar.AllDeviceRes[FreeTrkDeviceID.m_s8ModuleID].pTrunk);
                inc(pLinkTrunk,FreeTrkDeviceID.m_s16ChannelID);

                pOneUser.LinkDevID := FreeTrkDeviceID;
						    pLinkTrunk.LinkDevID := pOneUser.deviceID;
						    DrawUser_LinkDev ( pOneUser );
						    DrawMain_LinkDev ( pLinkTrunk);

                StrMove(pLinkTrunk.CallerCode,g_gLobalVar.cfg_CallingNum,strlen(g_gLobalVar.cfg_CallingNum));
                StrMove(pLinkTrunk.CalleeCode,pOneUser.DtmfBuf,pOneUser.DtmfCount-1);
                DrawMain_CallInfo ( pLinkTrunk );

                Change_UserState ( pOneUser, USER_CALLOUT );
						    Change_State ( pLinkTrunk, TRK_CALLOUT );
              end
            else
              begin
                MsgStr:=Format('XMS_ctsMakeCallOut() FAIL! ret = %d', [ret]);
                Form1.AddMsg(MsgStr);
              end;
          end;

        PlayTone ( pOneUser.VocDevID,2);		// busy tone
				Change_UserState ( pOneUser, USER_WAITHANGUP );
      end;
    end;
   end;
  end;
end;

function GetOutUserID(pDtmf:PCHAR;Var pUserDeviceID:DeviceID_t):integer;
Var
  iTmp:integer;
  s8ModID:Shortint;
  s16ChID:Smallint;
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=nil;

  if g_gLobalVar.cfg_iCallOutRule=2 then		// Select a Fix Channel by DTMF's tail 3
	  begin
      iTmp:=StrToInt(pDtmf);
		  iTmp:=iTmp mod 1000;

		  s8ModID := g_gLobalVar.MapTable_Trunk[iTmp].m_s8ModuleID;
		  s16ChID := g_gLobalVar.MapTable_Trunk[iTmp].m_s16ChannelID;

		  if ( iTmp >= g_gLobalVar.g_iTotalTrunk ) then
        begin
          result:=-1;
          exit;
        end;

      pOneTrunk:=pointer(g_gLobalVar.AllDeviceRes[s8ModID].pTrunk);
      inc(pOneTrunk,s16ChID);

		  if (pOneTrunk.iLineState=integer(DCS_FREE))
			    and(pOneTrunk.deviceID.m_s16DeviceSub=Smallint(XMS_DEVSUB_ANALOG_USER)) then
        begin
          pUserDeviceID:=pOneTrunk.deviceID;
          result:=iTmp;
          exit;
        end;
      end;
	result:=-1;
end;

Procedure StopPlayTone(Var pVocDevID:DeviceID_t);
begin
  PlayTone ( pVocDevID, -1 );
end;

Procedure DrawUser_DTMF(Var pOneUser:TRUNK_STRUCT);
Var
  StateStr:Array[0..32] of char;
  iDispRow:integer;
begin
  ZeroMemory(pointer(@StateStr),sizeof(StateStr)*sizeof(char));
  iDispRow := pOneUser.iUserSeqID;
  StrMove(StateStr,pOneUser.DtmfBuf,pOneUser.DtmfCount);
  Form1.ListView3.Items.Item[iDispRow].SubItems.Strings[4]:=StateStr;
end;

Procedure My_AddDtmfBuf(Var pOneTrunk:TRUNK_STRUCT;TmpDtmf:char);
begin
  if pOneTrunk.DtmfCount < 31 then
    begin
      pOneTrunk.DtmfBuf[pOneTrunk.DtmfCount]:=TmpDtmf;
		  pOneTrunk.DtmfBuf[pOneTrunk.DtmfCount+1]:=char(0);
		  inc(pOneTrunk.DtmfCount);
    end;
end;

Procedure ResetUser(pTrunk:Pointer;pEvt:Pointer);
Var
  pOneUser:^TRUNK_STRUCT;
  pLinkTrunk,pLinkUser:^TRUNK_STRUCT;
  PriData:PrivateData_t;
begin
  pOneUser:=nil;
  pLinkTrunk:=nil;
  pLinkUser:=nil;

  pOneUser:=pointer(pTrunk);
  if pOneUser=nil then
    begin
      exit;
    end;

  PriData.m_u32DataSize:=0;
  if pOneUser.VocDevID.m_s16DeviceMain <> 0 then
    begin
		  My_DualUnlink (pOneUser.VocDevID,pOneUser.deviceID);
		  FreeOneFreeVoice (pointer(@pOneUser.VocDevID));
    end;

  if pOneUser.LinkDevID.m_s16DeviceMain <> 0 then
	  begin
		  My_DualUnlink ( pOneUser.LinkDevID, pOneUser.deviceID );
      pLinkTrunk:=pointer(g_gLobalVar.AllDeviceRes[pOneUser.LinkDevID.m_s8ModuleID].pTrunk);
      inc(pLinkTrunk,pOneUser.LinkDevID.m_s16ChannelID);

      FillChar(pLinkTrunk.LinkDevID,sizeof(DeviceID_t),0);
      XMS_ctsClearCall(g_gLobalVar.g_acsHandle,pLinkTrunk.deviceID,0, PriData );

		  if pOneUser.LinkDevID.m_s16DeviceSub=Smallint(XMS_DEVSUB_ANALOG_USER) then
        begin
          pLinkUser:=pLinkTrunk;
          if pLinkUser.UserState=USER_RING then
            begin
              InitUserChannel(pLinkUser);
            end;
        end;
    end;

  InitUserChannel(pOneUser);
end;

Procedure TrunkWork (pTrunk:Pointer;pEvt:Pointer);
Var
  pOneTrunk:^TRUNK_STRUCT;
  pOneVoice:^VOICE_STRUCT;
  pAcsEvt:^Acs_Evt_t;
  pTempAcsEvt:^Acs_Evt_t;
  pCallControl:^Acs_CallControl_Data;
  pLinkUser:^TRUNK_STRUCT;
  FreeVocDeviceID:DeviceID_t;
  TmpGtd:char;
  TmpStr:string;
  PriData:PrivateData_t;
  ret:integer;
begin
  pOneTrunk:=nil;
  pOneVoice:=nil;
  pAcsEvt:=nil;
  pTempAcsEvt:=nil;
  pCallControl:=nil;
  pLinkUser:=nil;

  pOneTrunk:=pointer(pTrunk);
  pAcsEvt:=pointer(pEvt);

  if (pOneTrunk=nil) or (pAcsEvt=nil) then
  begin
    exit;
  end;

  PriData.m_u32DataSize:=0;

  if pAcsEvt.m_s32EventType=integer(XMS_EVT_CLEARCALL) then
    begin
      if (pOneTrunk.State <> TRK_FREE) and (pOneTrunk.State <> TRK_WAIT_REMOVE) then
        begin
          ResetTrunk(pointer(pOneTrunk));
          exit;
        end;
    end;

//  if pAcsEvt.m_s32EventType=integer(XMS_EVT_CALLOUT) then
//    begin
//      Change_State ( pOneTrunk, TRK_SIM_CALLOUT );
//    end;

  case pOneTrunk.State of
  TRK_FREE:
    begin
      SpecialForCas(pOneTrunk,pAcsEvt);
    end;

  TRK_CALLOUT:
    begin
      SpecialForCas(pOneTrunk,pAcsEvt);

      if pAcsEvt.m_s32EventType=integer(XMS_EVT_CALLOUT) then
        begin
          inc(pAcsEvt);
          pCallControl:=pointer(pAcsEvt);

          if pCallControl.m_s32AcsEvtState=1 then
            begin
              pLinkUser:=pointer(g_gLobalVar.AllDeviceRes[pOneTrunk.LinkDevID.m_s8ModuleID].pTrunk);
              inc(pLinkUser,pOneTrunk.LinkDevID.m_s16ChannelID);

              if pOneTrunk.deviceID.m_s8MachineID=pLinkUser.deviceID.m_s8MachineID then
                begin
                  My_DualLink (pOneTrunk.deviceID, pOneTrunk.LinkDevID );
                end;
              Change_State ( pOneTrunk, TRK_LINK );
				      Change_UserState ( pLinkUser, USER_LINK );
            end
          else //Call Fail
            begin
              DrawMain_Reason ( pOneTrunk, pCallControl.m_s32AcsEvtErrCode, pCallControl.m_s32CallClearCause );
				      Change_State ( pOneTrunk, TRK_FREE );

              pLinkUser:=pointer(g_gLobalVar.AllDeviceRes[pOneTrunk.LinkDevID.m_s8ModuleID].pTrunk);
              inc(pLinkUser,pOneTrunk.LinkDevID.m_s16ChannelID);
				      PlayTone ( pLinkUser.VocDevID, 2 );		// busy tone
              FillChar(pLinkUser.LinkDevID,sizeof(DeviceID_t),0);
              Change_UserState ( pLinkUser, USER_WAITHANGUP );
            end;
        end;
    end;

  TRK_SIM_CALLOUT:
    begin
      SpecialForCas(pOneTrunk,pAcsEvt);
      if pAcsEvt.m_s32EventType=integer(XMS_EVT_CALLOUT) then
        begin
          pTempAcsEvt:=pointer(pAcsEvt);
          inc(pTempAcsEvt);
          pCallControl:=pointer(pTempAcsEvt);
          if pAcsEvt.m_DeviceID.m_s16DeviceSub=Smallint(XMS_DEVSUB_ANALOG_TRUNK) then
            begin
              DrawMain_Analog_Reason(pOneTrunk,'');
              XMS_ctsSetDevTimer(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID,g_gLobalVar.g_Param_Analog.m_u16NoDialToneAfterOffHook);
              Change_State(pOneTrunk,TRK_SIM_ANALOG_OFFHOOK);
              exit;
            end;

          if pCallControl.m_s32AcsEvtState=1 then
            begin
              if SearchOneFreeVoice ( pOneTrunk, FreeVocDeviceID )>=0 then
                begin
                  pOneTrunk.VocDevID := FreeVocDeviceID;
                  pOneVoice:=pointer(g_gLobalVar.AllDeviceRes[FreeVocDeviceID.m_s8ModuleID].pVoice);
                  inc(pOneVoice,FreeVocDeviceID.m_s16ChannelID);
                  pOneVoice.UsedDevID:=pOneTrunk.deviceID;
                  My_DualLink (FreeVocDeviceID,pOneTrunk.deviceID);
                end;
              Change_State (pOneTrunk,TRK_SIM_LINK );
            end
           else //call fail
             begin
               DrawMain_Reason ( pOneTrunk, pCallControl.m_s32AcsEvtErrCode, pCallControl.m_s32CallClearCause );
				       Change_State ( pOneTrunk, TRK_FREE );
             end;
        end;
    end;

  TRK_SIM_LINK:
    begin
      if pAcsEvt.m_s32EventType=integer(XMS_EVT_LINKDEVICE) then
        begin
          PlayDTMF(pOneTrunk.VocDevID,'12345');
          Change_State(pOneTrunk,TRK_PLAYDTMF );
        end;
    end;

  TRK_PLAYDTMF:
    begin
      //if CheckPlayGTGEnd (pEvt)=true	then
      if pAcsEvt.m_s32EventType=integer(XMS_EVT_SENDIODATA) then
        begin
			    XMS_ctsClearCall(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID, 0, PriData );
			    Change_State (pOneTrunk,TRK_HANGUP);
        end;
    end;

  TRK_SIM_ANALOG_OFFHOOK:
    begin
		  if pAcsEvt.m_s32EventType=integer(XMS_EVT_DEV_TIMER) then
        begin
			    DrawMain_Analog_Reason(pOneTrunk, 'Wait Dial Tone TimeOut');
          XMS_ctsClearCall(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID, 0, PriData );
			    Change_State (pOneTrunk, TRK_HANGUP );
        end;

		TmpGtd := My_GetGtdOrPVDCode ( pAcsEvt );
		if shortint(TmpGtd)<>-1 then
      begin
        if (TmpGtd='I') or (TmpGtd='J') or(TmpGtd='K') then
          begin
            TmpStr:=Format('Busy Tone : %s',[TmpGtd]);
            DrawMain_Analog_Reason(pOneTrunk, TmpStr);
            XMS_ctsClearCall(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID, 0, PriData );
            Change_State (pOneTrunk, TRK_HANGUP );
          end
        else if TmpGtd='G' then
          begin
            ret:=XMS_ctsSendIOData(g_gLobalVar.g_acsHandle,pAcsEvt.m_DeviceID,Word(XMS_IO_TYPE_DTMF),strlen(g_gLobalVar.cfg_SimCalledNum),pointer(@g_gLobalVar.cfg_SimCalledNum));
            if ret>0 then
              begin
                XMS_ctsSetDevTimer(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID,g_gLobalVar.g_Param_Analog.m_u16Ringback_NoAnswerTime);
                Change_State(pOneTrunk,TRK_SIM_ANALOG_DIALING);
              end
            else
              begin
                ResetTrunk(pOneTrunk);
              end;
          end;
      end;
    end;

  TRK_SIM_ANALOG_DIALING:
    begin
		if pAcsEvt.m_s32EventType=integer(XMS_EVT_DEV_TIMER) then
      begin
			  DrawMain_Analog_Reason (pOneTrunk,'Wait Callee Offhook TimeOut');
        XMS_ctsClearCall(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID, 0, PriData );
			  Change_State(pOneTrunk,TRK_HANGUP);
	    end;

		TmpGtd:=My_GetGtdOrPVDCode(pAcsEvt);
		if shortint(TmpGtd) <> -1 then
      begin
			  if (TmpGtd='I') or (TmpGtd='J') or (TmpGtd='K') then		// Busy Tone
		      begin
				    TmpStr:=Format('Callee Busy Tone : %s',[TmpGtd]);
				    DrawMain_Analog_Reason (pOneTrunk,TmpStr);
            XMS_ctsClearCall(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID, 0, PriData );
				    Change_State ( pOneTrunk, TRK_HANGUP );
          end
        else if (TmpGtd='h') or (TmpGtd='b') then
          begin
            TmpStr:=Format('Callee Answer : %s', [TmpGtd]);
            DrawMain_Analog_Reason ( pOneTrunk, TmpStr );
            PlayDTMF (pOneTrunk.VocDevID, '12345' );
            Change_State( pOneTrunk,TRK_PLAYDTMF);
          end;
      end;
    end;

  end;
end;

function My_GetDtmfCode(Evt:pointer):char;
Var
  pAcsEvt:^Acs_Evt_t;
  pIOData:^Acs_IO_Data;
  pData:PCHAR;
begin
  pAcsEvt:=nil;
  pIOData:=nil;

  pAcsEvt:=pointer(Evt);
  if pAcsEvt=nil then
  begin
    exit;
  end;

  if pAcsEvt.m_s32EventType=integer(XMS_EVT_RECVIODATA) then
    begin
      inc(pAcsEvt);
      pIOData:=pointer(pAcsEvt);
        if (pIOData.m_u16IoType=Word(XMS_IO_TYPE_DTMF))
            and (pIOData.m_u16IoDataLen > 0) then
          begin
            inc(pIOData);
            pData:=pointer(pIOData);
            result:=pData[0];
            exit;
          end;
    end;
  result:=char(-1);
end;

function My_GetGtdOrPVDCode(Evt:pointer):char;
Var
  pAcsEvt:^Acs_Evt_t;
  pIOData:^Acs_IO_Data;
  pData:PCHAR;
  Msg:string;
begin
  pAcsEvt:=nil;
  pIOData:=nil;

  pAcsEvt:=pointer(Evt);

  if pAcsEvt=nil then
    begin
    end;
  if pAcsEvt.m_s32EventType=integer(XMS_EVT_RECVIODATA) then
    begin
      inc(pAcsEvt);
      pIOData:=pointer(pAcsEvt);
        if ((pIOData.m_u16IoType=Word(XMS_IO_TYPE_GTG))
            or (pIOData.m_u16IoType=Word(XMS_IO_TYPE_PVD))
            and (pIOData.m_u16IoDataLen > 0)) then
          begin
            inc(pIOData);
            pData:=pointer(pIOData);
            Msg:=Format('%s',[pData]);
            Form1.AddMsg(Msg);
            result:=pData[0];
            exit;
          end;
    end;
  result:=char(-1);
end;

function CheckPlayGTGEnd(AcsEvt:pointer):boolean;
Var
  pAcsEvt:^Acs_Evt_t;
begin
  pAcsEvt:=nil;

  pAcsEvt:=pointer(AcsEvt);
  if pAcsEvt=nil then
    begin
      exit;
    end;

  if pAcsEvt.m_s32EventType=integer(XMS_EVT_SENDIODATA) then
    begin
      result:=true;
      exit;
    end
  else
    begin
      result:=false;
    end;
end;

Procedure PlayDTMF(Var pVocDevID:DeviceID_t; DtmfStr:string);
Var
  len:Cardinal;
  u16IoType,u16IoLen:Word;
  IoDataBuf:Array[0..15] of char;
begin
  u16IoType:=0;
  //FillChar(IoDataBuf,sizeof(IoDataBuf),0);
  ZeroMemory(pointer(@IoDataBuf),sizeof(IoDataBuf)*sizeof(char));
  if Length(DtmfStr) = 0 then
    begin
      len:=0;
    end
  else
    begin
      u16IoType := Word(XMS_IO_TYPE_DTMF);
      len:=Length(DtmfStr);

      if len > 16 then len:=16;
      StrMove(IoDataBuf,PCHAR(DtmfStr),len);
    end;
    u16IoLen := Word(len);
    XMS_ctsSendIOData(g_gLobalVar.g_acsHandle,pVocDevID,u16IoType,u16IoLen,pointer(@IoDataBuf));
end;

function CalDispRow(iSeqID:integer):integer;
Var
  iRet:integer;
begin
  result:=iSeqID;
end;

Procedure DrawMain_Analog_Reason(pTrunk:pointer;ErrStr:string);
Var
  iDispRow:integer;
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then
  begin
    exit;
  end;
  iDispRow := CalDispRow(pOneTrunk.iSeqID);
  if iDispRow < 0 then exit;
  Form1.ListView2.Items.Item[iDispRow].SubItems.Strings[7]:=ErrStr;
end;

Procedure DrawMain_Reason(pTrunk:pointer;s32ErrCode:integer;s32ClearCause:integer);
Var
  StateStr:string;
  iDispRow:integer;
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then
    begin
      exit;
    end;
  iDispRow := CalDispRow(pOneTrunk.iSeqID);
  if iDispRow<0 then exit;

  StateStr:=Format('Err=%d,Cause=%d',[s32ErrCode,s32ClearCause]);
  Form1.ListView2.Items.Item[iDispRow].SubItems.Strings[7]:=StateStr;
end;

Procedure SpecialForCas (pTrunk:Pointer;pEvt:Pointer);
Var
  pOneTrunk:^TRUNK_STRUCT;
  pOneVoice:^VOICE_STRUCT;
  pAcsEvt:^Acs_Evt_t;
  FreeVocDeviceID:DeviceID_t;
begin
  pOneTrunk:=nil;
  pOneVoice:=nil;
  pAcsEvt:=nil;

  pOneTrunk:=pointer(pTrunk);
  pAcsEvt:=pointer(pEvt);

  if (pAcsEvt=nil) or (pOneTrunk=nil) then
    begin
      exit;
    end;

  if pOneTrunk.deviceID.m_s16DeviceSub<>Smallint(XMS_DEVSUB_E1_CAS) then
    begin
      exit;
    end;

  if pAcsEvt.m_s32EventType=integer(XMS_EVT_CAS_MFC_START) then
    begin
      if SearchOneFreeVoice(pOneTrunk,FreeVocDeviceID) >= 0 then
        begin
          pOneTrunk.VocDevID:=FreeVocDeviceID;
          pOneVoice:=pointer(g_gLobalVar.AllDeviceRes[FreeVocDeviceID.m_s8ModuleID].pVoice);
          inc(pOneVoice,FreeVocDeviceID.m_s16ChannelID);
          pOneVoice.UsedDevID:=pOneTrunk.deviceID;
          My_DualLink (FreeVocDeviceID,pOneTrunk.deviceID);
          g_gLobalVar.g_Param_CAS.m_VocDevID:=FreeVocDeviceID;
          XMS_ctsSetParam(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID,Word(CAS_PARAM_UNIPARAM),sizeof(CmdParamData_CAS_t),pointer(@g_gLobalVar.g_Param_CAS));
        end;
    end;

  if pAcsEvt.m_s32EventType=integer(XMS_EVT_CALLOUT) then
//    begin
//      if pAcsEvt.m_s32EventType=integer(XMS_EVT_CAS_MFC_END) then
        begin
          My_DualUnlink(pOneTrunk.VocDevID,pOneTrunk.deviceID );
          FreeOneFreeVoice (@pOneTrunk.VocDevID);
          pOneVoice:=pointer(g_gLobalVar.AllDeviceRes[pOneTrunk.VocDevID.m_s8ModuleID].pVoice);
          inc(pOneVoice,pOneTrunk.VocDevID.m_s16ChannelID);
          FillChar(pOneVoice.UsedDevID,sizeof(DeviceID_t),0);
          FillChar(pOneTrunk.VocDevID,sizeof(DeviceID_t),0);
        end;
//    end;
end;

function SearchOneFreeVoice(pTrunk:pointer;Var pFreeVocDeviceID:DeviceID_t):integer;
Var
  pOneTrunk:^TRUNK_STRUCT;
  pOneVoice:^VOICE_STRUCT;
  s8SearchModID,s8ModID:Shortint;
  i,lNowMostFreeNum:Integer;
begin
  pOneTrunk:=nil;
  pOneVoice:=nil;

  pOneTrunk:=pointer(pTrunk);
  s8ModID:=pOneTrunk.deviceID.m_s8ModuleID;
  if g_gLobalVar.cfg_iVoiceRule=0 then
    begin
      i:=pOneTrunk.iModSeqID;

      if i < g_gLobalVar.AllDeviceRes[s8ModID].lVocNum then
        begin
          pOneVoice := pointer(g_gLobalVar.AllDeviceRes[s8ModID].pVoice);
          inc(pOneVoice,i);
          if pOneVoice.State <> VOC_WAITOPEN then
            begin
              pFreeVocDeviceID:=pOneVoice.deviceID;
              Change_Voc_State ( pOneVoice, VOC_USED);
              dec(g_gLobalVar.AllDeviceRes[s8ModID].lVocFreeNum);
				      dec(g_gLobalVar.g_iTotalVoiceFree);
				      DrawCount_Voc ( s8ModID );
				      result:=i;
              exit;
            end;
        end;
        result:=-1;
        exit;
    end;

  if g_gLobalVar.cfg_iVoiceRule=1 then
    begin
      s8SearchModID := s8ModID;
    end
	else		// Search in Most free resource module
	  begin
		  s8SearchModID := -1;
		  lNowMostFreeNum := -1;
      if g_gLobalVar.g_iTotalModule > 0 then
        begin
		      for i := 0 to g_gLobalVar.g_iTotalModule-1 do
            begin
              if g_gLobalVar.AllDeviceRes[g_gLobalVar.MapTable_Module[i]].lVocFreeNum > lNowMostFreeNum then
                begin
                  s8SearchModID := g_gLobalVar.MapTable_Module[i];
				          lNowMostFreeNum := g_gLobalVar.AllDeviceRes[g_gLobalVar.MapTable_Module[i]].lVocFreeNum;
                end;
            end;
		    end;
    end;

  if g_gLobalVar.AllDeviceRes[s8SearchModID].lVocNum > 0 then
    begin
      for i:=0 to g_gLobalVar.AllDeviceRes[s8SearchModID].lVocNum-1 do
        begin
          pOneVoice:=pointer(g_gLobalVar.AllDeviceRes[s8SearchModID].pVoice);
          inc(pOneVoice,i);
          pFreeVocDeviceID:=pOneVoice.deviceID;
          Change_Voc_State( pOneVoice, VOC_USED);
          dec(g_gLobalVar.AllDeviceRes[s8SearchModID].lVocFreeNum);
			    dec(g_gLobalVar.g_iTotalVoiceFree);
			    DrawCount_Voc ( s8SearchModID );
			    result:=i;
          exit;
        end;
    end;

  result:=-1;
end;

Procedure My_DualUnlink(Var pDev1:DeviceID_t;Var pDev2:DeviceID_t);
Var
  PriData:PrivateData_t;
begin
  PriData.m_u32DataSize:=0;
  XMS_ctsUnlinkDevice(g_gLobalVar.g_acsHandle,pDev1,pDev2,PriData);
  XMS_ctsUnlinkDevice(g_gLobalVar.g_acsHandle,pDev2,pDev1,PriData);
end;

Procedure My_DualLink(Var pDev1:DeviceID_t;Var pDev2:DeviceID_t);
Var
  PriData:PrivateData_t;
begin
  PriData.m_u32DataSize:=0;
  XMS_ctsLinkDevice(g_gLobalVar.g_acsHandle,pDev1,pDev2,PriData);
  XMS_ctsLinkDevice(g_gLobalVar.g_acsHandle,pDev2,pDev1,PriData);
end;

Procedure PlayTone(Var pVocDevID:DeviceID_t;iPlayType:integer);
Var
  u16IoLen:integer;
  u16IoType:Word;
  IoDataBuf:Array[0..15] of char;
begin
  if iPlayType=-1 then
    begin
      u16IoLen:=0;
      u16IoType:=Word(XMS_IO_TYPE_GTG);
    end
  else
    begin
      u16IoLen:=1;
      u16IoType:=Word(XMS_IO_TYPE_GTG);

      if iPlayType=0 then begin IoDataBuf[0] := 'G'; end;
      if iPlayType=1 then begin IoDataBuf[0] := 'H'; end;
      if iPlayType=2 then begin IoDataBuf[0] := 'I'; end;
    end;
	XMS_ctsSendIOData(g_gLobalVar.g_acsHandle, pVocDevID, u16IoType,u16IoLen,pointer(@IoDataBuf));
end;

Procedure ResetTrunk (pTrunk:Pointer);
Var
  pOneTrunk:^TRUNK_STRUCT;
  pOneVoc:^VOICE_STRUCT;
  pLinkUser:^TRUNK_STRUCT;
begin
  pOneTrunk:=nil;
  pOneVoc:=nil;
  pLinkUser:=nil;

  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then
  begin
    exit;
  end;

  if pOneTrunk.LinkDevID.m_s16DeviceMain <> 0 then
    begin
      My_DualUnlink(pOneTrunk.LinkDevID,pOneTrunk.deviceID);
      pLinkUser:=pointer(g_gLobalVar.AllDeviceRes[pOneTrunk.LinkDevID.m_s8ModuleID].pTrunk);
      inc(pLinkUser,pOneTrunk.LinkDevID.m_s16ChannelID);
      My_DualLink (pLinkUser.VocDevID, pLinkUser.deviceID);
      PlayTone(pLinkUser.VocDevID,2);
      FillChar(pLinkUser.LinkDevID, sizeof(DeviceID_t), 0);
    end;

  if pOneTrunk.VocDevID.m_s16DeviceMain <> 0 then
    begin
      My_DualUnlink(pOneTrunk.VocDevID, pOneTrunk.deviceID);
      FreeOneFreeVoice (@pOneTrunk.VocDevID);
      pOneVoc:=pointer(g_gLobalVar.AllDeviceRes[pOneTrunk.VocDevID.m_s8ModuleID].pVoice);
      inc(pOneVoc,pOneTrunk.VocDevID.m_s16ChannelID);

      FillChar(pOneVoc.UsedDevID,sizeof(DeviceID_t),0);
      FillChar(pOneTrunk.VocDevID,sizeof(DeviceID_t),0);
    end;
  InitTrunkChannel(pOneTrunk);
end;

Procedure FreeOneFreeVoice(Dev:pointer);
Var
  pFreeVocDeviceID:^DeviceID_t;
  s8ModID:Shortint;
  pOneVoc:^VOICE_STRUCT;
begin
  pFreeVocDeviceID:=nil;
  pOneVoc:=nil;

  pFreeVocDeviceID:=pointer(Dev);
  if pFreeVocDeviceID=nil then
    begin
      exit;
    end;

  s8ModID := pFreeVocDeviceID.m_s8ModuleID;

  if g_gLobalVar.AllDeviceRes[s8ModID].lFlag=1 then
    begin
      pOneVoc:=pointer(g_gLobalVar.AllDeviceRes[pFreeVocDeviceID.m_s8ModuleID].pVoice);
      inc(pOneVoc,pFreeVocDeviceID.m_s16ChannelID);
      Change_Voc_State(pOneVoc,VOC_FREE);
      inc(g_gLobalVar.AllDeviceRes[s8ModID].lVocFreeNum);
      inc(g_gLobalVar.g_iTotalVoiceFree);
      DrawCount_Voc ( s8ModID );
    end;
end;

Procedure CloseDeviceOK(Var pDevice:DeviceID_t);
Var
  pOneTrunk:^TRUNK_STRUCT;
  pOneVoice:^VOICE_STRUCT;
  pOnePcm:^PCM_STRUCT;
begin
  pOneTrunk:=nil;
  pOneVoice:=nil;
  pOnePcm:=nil;

  g_gLobalVar.AllDeviceRes[pDevice.m_s8ModuleID].bErrFlag := true;
  DrawCount_ErrFlag (pDevice.m_s8ModuleID);

  if pDevice.m_s16DeviceMain=Smallint(XMS_DEVMAIN_BOARD) then
    begin
      g_gLobalVar.AllDeviceRes[pDevice.m_s8ModuleID].bOpenFlag := false;
    end;

  if pDevice.m_s16DeviceMain=Smallint(XMS_DEVMAIN_INTERFACE_CH) then
    begin
      pOneTrunk:=pointer(g_gLobalVar.AllDeviceRes[pDevice.m_s8ModuleID].pTrunk);
      inc(pOneTrunk,pDevice.m_s16ChannelID);
      Change_State(pOneTrunk,TRK_WAITOPEN);

      if pOneTrunk.deviceID.m_s16DeviceSub=Smallint(XMS_DEVSUB_ANALOG_USER) then
        begin
          Change_UserState(pOneTrunk,USER_WAITOPEN);
          dec(g_gLobalVar.g_iTotalUserOpened);
          DrawCount_User(pDevice.m_s8ModuleID);
        end;
      dec(g_gLobalVar.g_iTotalTrunkOpened);
      dec(g_gLobalVar.AllDeviceRes[pDevice.m_s8ModuleID].lTrunkOpened);
      DrawCount_Trunk(pDevice.m_s8ModuleID);
    end;

  if pDevice.m_s16DeviceMain=Smallint(XMS_DEVMAIN_VOICE) then
    begin
      pOneVoice:=pointer(g_gLobalVar.AllDeviceRes[pDevice.m_s8ModuleID].pVoice);
      inc(pOneVoice,pDevice.m_s16ChannelID);
      Change_Voc_State ( pOneVoice, VOC_WAITOPEN);
      dec(g_gLobalVar.g_iTotalVoiceOpened);
      dec(g_gLobalVar.g_iTotalVoiceFree);
      dec(g_gLobalVar.AllDeviceRes[pDevice.m_s8ModuleID].lVocOpened);
      dec(g_gLobalVar.AllDeviceRes[pDevice.m_s8ModuleID].lVocFreeNum);
		  DrawCount_Voc(pDevice.m_s8ModuleID);
    end;

  if pDevice.m_s16DeviceMain=Smallint(XMS_DEVMAIN_DIGITAL_PORT) then
    begin
      pOnePcm:=pointer(g_gLobalVar.AllDeviceRes[pDevice.m_s8ModuleID].pPcm);
      inc(pOnePcm,pDevice.m_s16ChannelID);
      pOnePcm.bOpenFlag:=false;
      dec(g_gLobalVar.g_iTotalPcmOpened);
      dec(g_gLobalVar.AllDeviceRes[pDevice.m_s8ModuleID].lPcmOpened );
      DrawCount_Pcm ( pDevice.m_s8ModuleID );
    end;
end;

Procedure OpenDeviceOK(Var m_DeviceID:DeviceID_t);
Var
  pOneTrunk:^TRUNK_STRUCT;
  pOneVoice:^VOICE_STRUCT;
  pOnePcm:^PCM_STRUCT;
  privateData:PrivateData_t;
  pParamData:pointer;
  cmdAnalogTrunk:CmdParamData_AnalogTrunk_t;
  g_AnalogUser:CmdParamData_AnalogUser_t;
  u16ParamType:Word;
  u16ParamSize:Word;
  szbuffer:string;
  ret:integer;
begin
  pOneTrunk:=nil;
  pOneVoice:=nil;
  pOnePcm:=nil;

  privateData.m_u32DataSize:=0;
  if m_DeviceID.m_s16DeviceMain=Smallint(XMS_DEVMAIN_BOARD) then
    begin
      g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].deviceID.m_CallID:=m_DeviceID.m_CallID;
      SetGTD_ToneParam(m_DeviceID);
    end;

  if m_DeviceID.m_s16DeviceMain=Smallint(XMS_DEVMAIN_INTERFACE_CH) then
    begin
      pOneTrunk:=pointer(g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].pTrunk);
      inc(pOneTrunk, m_DeviceID.m_s16ChannelID);
      pOneTrunk.deviceID.m_CallID:=m_DeviceID.m_CallID;

      if pOneTrunk.deviceID.m_s16DeviceSub=Smallint(XMS_DEVSUB_ANALOG_USER) then
        begin
          InitUserChannel (pOneTrunk);
          XMS_ctsResetDevice(g_gLobalVar.g_acsHandle,m_DeviceID,privateData);
          XMS_ctsGetDevState(g_gLobalVar.g_acsHandle,m_DeviceID,privateData);
          Change_State ( pOneTrunk, TRK_NOTHANDLE );
          inc(g_gLobalVar.g_iTotalUserOpened);
          DrawCount_User(m_DeviceID.m_s8ModuleID );
        end
      else
        begin
          InitTrunkChannel(pOneTrunk);
          XMS_ctsResetDevice(g_gLobalVar.g_acsHandle,m_DeviceID,privateData);
          XMS_ctsGetDevState(g_gLobalVar.g_acsHandle,m_DeviceID,privateData);
        end;
      inc(g_gLobalVar.g_iTotalTrunkOpened);
      inc(g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].lTrunkOpened);
      DrawCount_Trunk (m_DeviceID.m_s8ModuleID);

      if pOneTrunk.deviceID.m_s16DeviceSub=Smallint(XMS_DEVSUB_ANALOG_TRUNK) then
        begin
			    u16ParamType:=word(ANALOGTRUNK_PARAM_UNIPARAM);
			    u16ParamSize:=sizeof(CmdParamData_AnalogTrunk_t);

          FillChar(cmdAnalogTrunk,sizeof(cmdAnalogTrunk),0);

			    cmdAnalogTrunk.m_u16CallInRingCount := 1;
			    cmdAnalogTrunk.m_u16CallInRingTimeOut := 6000; //6 seconds

			    pParamData := pointer(@cmdAnalogTrunk);

          ret:=XMS_ctsSetParam(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID,u16ParamType,u16ParamSize,pParamData);

			    szbuffer:=Format('Set AnalogTrunk  ret = %d\n',[ret]);
		    	Form1.AddMsg (szbuffer);
        end
      else if pOneTrunk.deviceID.m_s16DeviceSub=Smallint(XMS_DEVSUB_ANALOG_USER) then
        begin
          u16ParamType:=word(ANALOGUSER_PARAM_UNIPARAM);
          u16ParamSize:=sizeof(CmdParamData_AnalogUser_t);

          FillChar(g_AnalogUser,sizeof(g_AnalogUser),0);
          g_AnalogUser.m_u8CallerIdOption  := 1;
			    g_AnalogUser.m_u8RingCadenceType := 0;
			    g_AnalogUser.m_u8CallOutRingTimeOut := 30 ;

          pParamData:=pointer(@g_AnalogUser);

          ret:=XMS_ctsSetParam(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID,u16ParamType,u16ParamSize,pParamData);

			    szbuffer:=Format('Set AnalogTrunk  ret = %d\n',[ret]);
		    	Form1.AddMsg (szbuffer);
        end;
    end;

    if m_DeviceID.m_s16DeviceMain= smallint(XMS_DEVMAIN_VOICE) then
      begin
        pOneVoice:=pointer(g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].pVoice);
        inc(pOneVoice,m_DeviceID.m_s16ChannelID);
        pOneVoice.deviceID.m_CallID := m_DeviceID.m_CallID;
        Change_Voc_State (pOneVoice, VOC_FREE);
        inc(g_gLobalVar.g_iTotalVoiceOpened);
        inc(g_gLobalVar.g_iTotalVoiceFree);
		    inc(g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].lVocOpened);
		    inc(g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].lVocFreeNum);
        DrawCount_Voc (m_DeviceID.m_s8ModuleID);
      end;

    if m_DeviceID.m_s16DeviceMain= smallint(XMS_DEVMAIN_DIGITAL_PORT) then
      begin
        pOnePcm:=pointer(g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].pPcm);
        inc(pOnePcm,m_DeviceID.m_s16ChannelID);
        pOnePcm.deviceID.m_CallID := m_DeviceID.m_CallID;

        XMS_ctsResetDevice(g_gLobalVar.g_acsHandle,m_DeviceID,privateData);
        XMS_ctsGetDevState(g_gLobalVar.g_acsHandle,m_DeviceID,privateData);
        DrawPcm_TypeAndAlarm (pOnePcm);

        inc(g_gLobalVar.g_iTotalPcmOpened);
		    inc(g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].lPcmOpened);

        DrawCount_Pcm (m_DeviceID.m_s8ModuleID);
      end;
end;

Procedure InitTrunkChannel(pTrunk:pointer);
Var
  pOneTrunk:^TRUNK_STRUCT;
Begin
  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then
    begin
      exit;
    end;
  Change_State (pOneTrunk,TRK_FREE);
  FillChar(pOneTrunk.VocDevID, sizeof(DeviceID_t), 0);
  FillChar(pOneTrunk.LinkDevID, sizeof(DeviceID_t), 0);
  DrawMain_LinkDev ( pOneTrunk );
end;

Procedure DrawMain_LinkDev(pTrunk:pointer);
Var
  StateStr:string;
  iDispRow:integer;
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then
  begin
      exit;
  end;

  iDispRow:=CalDispRow(pOneTrunk.iSeqID);

  if iDispRow < 0 then
    begin
      exit;
    end;

  if pOneTrunk.LinkDevID.m_s16DeviceMain <> 0 then
    begin
      StateStr:=Format('%d,%d',[pOneTrunk.LinkDevID.m_s8ModuleID, pOneTrunk.LinkDevID.m_s16ChannelID]);
    end
  else
    begin
      StateStr:='';
    end;

  Form1.ListView2.Items.Item[iDispRow].SubItems.Strings[6]:=StateStr;
end;

Procedure DrawCount_User(s8ModID:ShortInt);
Var
  TmpStr:string;
Begin
  TmpStr:=Format('%3d/%3d',[g_gLobalVar.g_iTotalUser, g_gLobalVar.g_iTotalUserOpened]);
  Form1.ListView1.Items.Item[0].SubItems.Strings[5]:=TmpStr;
end;

Procedure Change_State(pTrunk:pointer;NewState:TRUNK_STATE);
Var
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then
  begin
  exit;
  end;
  //EnterCriticalSection(MyCs);
  pOneTrunk.State:=NewState;
  //LeaveCriticalSection(MyCs);
  DrawMain_State(pOneTrunk);

  if (g_gLobalVar.AllDeviceRes[pOneTrunk.deviceID.m_s8ModuleID].RemoveState=DSP_REMOVE_STATE_START)
     and (NewState=TRK_FREE) then
  begin
     pOneTrunk.State := TRK_WAIT_REMOVE;
     DrawMain_State(pOneTrunk);
     CheckRemoveReady( pOneTrunk.deviceID.m_s8ModuleID );
  end;
end;

Procedure InitUserChannel(OneUser:pointer);
Var
  pOneUser:^TRUNK_STRUCT;
begin
  pOneUser:=nil;

  pOneUser:=pointer(OneUser);
  if pOneUser=nil then
  begin
    exit;
  end;
  Change_UserState(OneUser,USER_FREE);
  My_InitDtmfBuf(pOneUser);
  FillChar(pOneUser.VocDevID, sizeof(DeviceID_t), 0);
  FillChar(pOneUser.LinkDevID, sizeof(DeviceID_t), 0);
  DrawUser_VocInfo ( pOneUser );
	DrawUser_LinkDev ( pOneUser );
end;

Procedure DrawUser_VocInfo(OneUser:pointer);
Var
  pOneUser:^TRUNK_STRUCT;
  StateStr:string;
  pDev:^DeviceID_t;
  iDispRow:integer;
begin
  pOneUser:=nil;
  pDev:=nil;

  pOneUser:=pointer(OneUser);
  if pOneUser=nil then
  begin
    exit;
  end;
  iDispRow:=pOneUser.iUserSeqID;

  if pOneUser.VocDevID.m_s16DeviceMain <> -1 then
    begin
      pDev:=pointer(@pOneUser.VocDevID);
      StateStr:=Format('%d,%d', [pDev.m_s8ModuleID, pDev.m_s16ChannelID]);
    end
  else
    begin
       StateStr:='';
       Form1.ListView3.Items.Item[iDispRow].SubItems.Strings[5]:=StateStr;
    end;
end;

Procedure DrawUser_LinkDev(OneUser:pointer);
Var
  pOneUser:^TRUNK_STRUCT;
  StateStr:string;
  iDispRow:integer;
begin
  pOneUser:=nil;

  pOneUser:=pointer(OneUser);
  if pOneUser=nil then
  begin
    exit;
  end;
  iDispRow:=pOneUser.iUserSeqID;

  if pOneUser.VocDevID.m_s16DeviceMain <> -1 then
    begin
		  StateStr:=Format('%d,%d', [pOneUser.LinkDevID.m_s8ModuleID, pOneUser.LinkDevID.m_s16ChannelID] );
    end
  else
    begin
		  StateStr:='';
    end;

  Form1.ListView3.Items.Item[iDispRow].SubItems.Strings[6]:=StateStr;
end;

Procedure Change_UserState(OneTrunk:pointer;NewState:USER_STATE);
Var
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=nil;

  pOneTrunk:=pointer(OneTrunk);
  if pOneTrunk=nil then
    begin
      exit;
    end;
  pOneTrunk.UserState:=NewState;
  DrawUser_State(pOneTrunk);

  if (REMOVE_STATE(g_gLobalVar.AllDeviceRes[pOneTrunk.deviceID.m_s8ModuleID].RemoveState)=DSP_REMOVE_STATE_START)
  and (USER_FREE=NewState) then
    begin
      pOneTrunk.UserState:=USER_WAIT_REMOVE;
      DrawUser_State( pOneTrunk );
      CheckRemoveReady( pOneTrunk.deviceID.m_s8ModuleID );
    end;
end;

Procedure My_InitDtmfBuf (OneTrunk:pointer);
Var
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=nil;

  pOneTrunk:=pointer(OneTrunk);
  if pOneTrunk=nil then
  begin
    exit;
  end;
  pOneTrunk.DtmfCount:=0;
  ZeroMemory(pointer(@pOneTrunk.DtmfBuf),32);
end;

Procedure SetGTD_ToneParam(Var pDevice:DeviceID_t);
Var
  u16ParamType:Word;
  u16ParamSize:Word;
  TmpGtdFreq:CmdParamData_GtdFreq_t;
  TmpGtdProto:CmdParamData_GtdProtoType_t;
begin
  u16ParamType:=integer(BOARD_PARAM_SETGTDFREQ);
  u16ParamSize:=sizeof(CmdParamData_GtdFreq_t);

  // freq0
  TmpGtdFreq.m_u16Freq_Index:=0;
	TmpGtdFreq.m_u16Freq_Coef:=g_gLobalVar.g_Param_Analog.m_u16Freq0;
  XMS_ctsSetParam(g_gLobalVar.g_acsHandle,pDevice,u16ParamType,u16ParamSize,pointer(@TmpGtdFreq));

  TmpGtdFreq.m_u16Freq_Index:=1;
	TmpGtdFreq.m_u16Freq_Coef:=g_gLobalVar.g_Param_Analog.m_u16Freq1;
	XMS_ctsSetParam(g_gLobalVar.g_acsHandle,pDevice,u16ParamType,u16ParamSize,pointer(@TmpGtdFreq));

  //set DialTone
  u16ParamType:=integer(BOARD_PARAM_SETGTDTONE);
	u16ParamSize:=sizeof(CmdParamData_GtdProtoType_t);
  FillChar(TmpGtdProto,sizeof(CmdParamData_GtdProtoType_t),0);
  TmpGtdProto.m_u16GtdID := 48;		// DialTone, we use GTD's ID 48
	TmpGtdProto.m_u16Freq_Mask := g_gLobalVar.g_Param_Analog.m_u16DialTone_FreqIndexMask;
	TmpGtdProto.m_u16Envelope_Mode := 0;
	TmpGtdProto.m_u16Repeat_Count := 1;
	TmpGtdProto.m_u16Min_On_Time1 := g_gLobalVar.g_Param_Analog.m_u16DialTone_On_Time div 15;		// the unit is 15 ms
  XMS_ctsSetParam(g_gLobalVar.g_acsHandle,pDevice,u16ParamType,u16ParamSize,pointer(@TmpGtdProto));

  //set RingBack Tone
  u16ParamType :=integer(BOARD_PARAM_SETGTDTONE);
	u16ParamSize := sizeof(CmdParamData_GtdProtoType_t);
  FillChar(TmpGtdProto,sizeof(CmdParamData_GtdProtoType_t),0);
  TmpGtdProto.m_u16GtdID := 49;		// DialTone, we use GTD's ID 48
	TmpGtdProto.m_u16Freq_Mask := g_gLobalVar.g_Param_Analog.m_u16RingBackTone_FreqIndexMask;
	TmpGtdProto.m_u16Envelope_Mode := 1;
	TmpGtdProto.m_u16Repeat_Count := 1;
	TmpGtdProto.m_u16Min_On_Time1 := (g_gLobalVar.g_Param_Analog.m_u16RingBackTone_On_Time *
    (100-g_gLobalVar.g_Param_Analog.m_u16RingBackTone_TimeDeviation) div 100) div 15;
  TmpGtdProto.m_u16Max_On_Time1 := (g_gLobalVar.g_Param_Analog.m_u16RingBackTone_On_Time *
		(100 + g_gLobalVar.g_Param_Analog.m_u16RingBackTone_TimeDeviation))div 100  div 15;
	TmpGtdProto.m_u16Min_Off_Time1 := (g_gLobalVar.g_Param_Analog.m_u16RingBackTone_Off_Time *
		(100 - g_gLobalVar.g_Param_Analog.m_u16RingBackTone_TimeDeviation))div 100  div 15;
	TmpGtdProto.m_u16Max_Off_Time1 := (g_gLobalVar.g_Param_Analog.m_u16RingBackTone_Off_Time *
		(100 + g_gLobalVar.g_Param_Analog.m_u16RingBackTone_TimeDeviation))div 100  div 15;
  XMS_ctsSetParam(g_gLobalVar.g_acsHandle,pDevice,u16ParamType,u16ParamSize,pointer(@TmpGtdProto));

	// set Busy Tone0
	u16ParamType := integer(BOARD_PARAM_SETGTDTONE) ;
	u16ParamSize := sizeof(CmdParamData_GtdProtoType_t);
	
	FillChar(TmpGtdProto,sizeof(CmdParamData_GtdProtoType_t),0);
	TmpGtdProto.m_u16GtdID := 50;		// BusyTone0, we use GTD's ID 50
	TmpGtdProto.m_u16Freq_Mask := g_gLobalVar.g_Param_Analog.m_u16BusyTone0_FreqIndexMask;
	TmpGtdProto.m_u16Envelope_Mode := 1;
	TmpGtdProto.m_u16Repeat_Count := 1;
	TmpGtdProto.m_u16Min_On_Time1 := (g_gLobalVar.g_Param_Analog.m_u16BusyTone0_On_Time *
		(100 - g_gLobalVar.g_Param_Analog.m_u16BusyTone0_TimeDeviation)div 100 ) div 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Max_On_Time1 := (g_gLobalVar.g_Param_Analog.m_u16BusyTone0_On_Time *
		(100 + g_gLobalVar.g_Param_Analog.m_u16BusyTone0_TimeDeviation))div 100  div 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Min_Off_Time1 := (g_gLobalVar.g_Param_Analog.m_u16BusyTone0_Off_Time *
		(100 - g_gLobalVar.g_Param_Analog.m_u16BusyTone0_TimeDeviation))div 100  div 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Max_Off_Time1 := (g_gLobalVar.g_Param_Analog.m_u16BusyTone0_Off_Time *
		(100 + g_gLobalVar.g_Param_Analog.m_u16BusyTone0_TimeDeviation))div 100  div 15;		// the unit is 15 ms

  XMS_ctsSetParam(g_gLobalVar.g_acsHandle,pDevice,u16ParamType,u16ParamSize,pointer(@TmpGtdProto));

	//set Busy Tone1
	u16ParamType := integer(BOARD_PARAM_SETGTDTONE);
	u16ParamSize := sizeof(CmdParamData_GtdProtoType_t);

	FillChar(TmpGtdProto,sizeof(CmdParamData_GtdProtoType_t),0);
	TmpGtdProto.m_u16GtdID := 51;		// BusyTone1, we use GTD's ID 51
	TmpGtdProto.m_u16Freq_Mask := g_gLobalVar.g_Param_Analog.m_u16BusyTone1_FreqIndexMask;
	TmpGtdProto.m_u16Envelope_Mode := 1;
	TmpGtdProto.m_u16Repeat_Count := 1;
	TmpGtdProto.m_u16Min_On_Time1 := (g_gLobalVar.g_Param_Analog.m_u16BusyTone1_On_Time *
		(100 - g_gLobalVar.g_Param_Analog.m_u16BusyTone1_TimeDeviation)div 100 ) div 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Max_On_Time1 := (g_gLobalVar.g_Param_Analog.m_u16BusyTone1_On_Time *
		(100 + g_gLobalVar.g_Param_Analog.m_u16BusyTone1_TimeDeviation))div 100  div 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Min_Off_Time1 := (g_gLobalVar.g_Param_Analog.m_u16BusyTone1_Off_Time *
		(100 - g_gLobalVar.g_Param_Analog.m_u16BusyTone1_TimeDeviation))div 100  div 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Max_Off_Time1 := (g_gLobalVar.g_Param_Analog.m_u16BusyTone1_Off_Time *
		(100 + g_gLobalVar.g_Param_Analog.m_u16BusyTone1_TimeDeviation))div 100  div 15;		// the unit is 15 ms

  XMS_ctsSetParam(g_gLobalVar.g_acsHandle,pDevice,u16ParamType,u16ParamSize,pointer(@TmpGtdProto));

	// set Busy Tone2
	u16ParamType := integer(BOARD_PARAM_SETGTDTONE);
	u16ParamSize := sizeof(CmdParamData_GtdProtoType_t);

  FillChar(TmpGtdProto,sizeof(CmdParamData_GtdProtoType_t),0);
	TmpGtdProto.m_u16GtdID := 52;		// BusyTone2, we use GTD's ID 52
	TmpGtdProto.m_u16Freq_Mask := g_gLobalVar.g_Param_Analog.m_u16BusyTone2_FreqIndexMask;
	TmpGtdProto.m_u16Envelope_Mode := 1;
	TmpGtdProto.m_u16Repeat_Count := 1;
	TmpGtdProto.m_u16Min_On_Time1 := (g_gLobalVar.g_Param_Analog.m_u16BusyTone2_On_Time *
		(100 - g_gLobalVar.g_Param_Analog.m_u16BusyTone2_TimeDeviation)div 100 ) div 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Max_On_Time1 := (g_gLobalVar.g_Param_Analog.m_u16BusyTone2_On_Time *
		(100 + g_gLobalVar.g_Param_Analog.m_u16BusyTone2_TimeDeviation))div 100  div 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Min_Off_Time1 := (g_gLobalVar.g_Param_Analog.m_u16BusyTone2_Off_Time *
		(100 - g_gLobalVar.g_Param_Analog.m_u16BusyTone2_TimeDeviation))div 100  div 15;		// the unit is 15 ms
	TmpGtdProto.m_u16Max_Off_Time1 := (g_gLobalVar.g_Param_Analog.m_u16BusyTone2_Off_Time *
		(100 + g_gLobalVar.g_Param_Analog.m_u16BusyTone2_TimeDeviation))div 100  div 15;		// the unit is 15 ms

  XMS_ctsSetParam(g_gLobalVar.g_acsHandle,pDevice,u16ParamType,u16ParamSize,pointer(@TmpGtdProto));
end;

Procedure	ReDrawAll ();
Var
  TmpStr:string;
  i,iDispRow:Integer;
  ModuleId:Shortint;
  ChannelId:Smallint;
  pOneTrunk:^TRUNK_STRUCT;
  pOnePcm:^PCM_STRUCT;
begin
  pOneTrunk:=nil;
  pOnePcm:=nil;

  if g_gLobalVar.g_iTotalTrunk > 0 then
  begin
    for i:=0 to g_gLobalVar.g_iTotalTrunk-1 do
    begin
      iDispRow:=CalDispRow ( i );
      ModuleId:=g_gLobalVar.MapTable_Trunk[i].m_s8ModuleID;
      ChannelId:=g_gLobalVar.MapTable_Trunk[i].m_s16ChannelID;

      if iDispRow < 0 then Continue;
      TmpStr:=Format('%3d', [iDispRow]);

      TmpStr:=Format('%d,%d', [ModuleId, ChannelId]);
      Form1.ListView2.Items.Item[iDispRow].SubItems.Strings[0]:=TmpStr;

      pOneTrunk:=pointer(g_gLobalVar.AllDeviceRes[ModuleId].pTrunk);
      inc(pOneTrunk,ChannelId);
      Form1.ListView2.Items.Item[iDispRow].SubItems.Strings[1]:=GetString_DeviceSub( pOneTrunk.deviceID.m_s16DeviceSub);

	    DrawMain_LineState (pOneTrunk);
		  DrawMain_State (pOneTrunk);
		  DrawMain_CallInfo (pOneTrunk);
    end;
  end;

  if g_gLobalVar.g_iTotalPcm > 0 then
  begin
    for i:=0 to g_gLobalVar.g_iTotalPcm-1 do
    begin
      ModuleId:=g_gLobalVar.MapTable_Pcm[i].m_s8ModuleID;
      ChannelId:=g_gLobalVar.MapTable_Pcm[i].m_s16ChannelID;
      pOnePcm:=pointer(g_gLobalVar.AllDeviceRes[ModuleId].pPcm);
      inc(pOnePcm,ChannelId);
      DrawPcm_TypeAndAlarm(pOnePcm);
    end;
  end;

  if g_gLobalVar.g_iTotalUser > 0 then
  begin
    for i:=0 to g_gLobalVar.g_iTotalUser-1 do
      begin
        iDispRow:=i;
        ModuleId:=g_gLobalVar.MapTable_User[i].m_s8ModuleID;
        ChannelId:=g_gLobalVar.MapTable_User[i].m_s16ChannelID;

        pOneTrunk:=pointer(g_gLobalVar.AllDeviceRes[ModuleId].pTrunk);
        inc(pOneTrunk,ChannelId);

        TmpStr:=Format('%d,%d',[g_gLobalVar.MapTable_User[i].m_s8ModuleID, g_gLobalVar.MapTable_User[i].m_s16ChannelID]);
        Form1.ListView3.Items.Item[iDispRow].SubItems.Strings[0]:=TmpStr;

        TmpStr:=GetString_DeviceSub(pOneTrunk.deviceID.m_s16DeviceSub);
        Form1.ListView3.Items.Item[iDispRow].SubItems.Strings[1]:=TmpStr;
        DrawUser_LineState(pOneTrunk);
		    DrawUser_State(pOneTrunk);
      end;
  end;

  if g_gLobalVar.g_iTotalModule > 0 then
    begin
      Form1.ListView1AddItem(g_gLobalVar.g_iTotalModule);
      for i:=0 to g_gLobalVar.g_iTotalModule-1 do
        begin
           TmpStr:=Format('%3d', [g_gLobalVar.MapTable_Module[i]]);
           Form1.ListView1.Items.Item[i+1].SubItems.Strings[0]:=TmpStr;
        end;
    end;

  if g_gLobalVar.g_iTotalModule > 0 then
    begin
      for i:=0 to g_gLobalVar.g_iTotalModule-1 do
        begin
          DrawCount_Pcm(g_gLobalVar.Maptable_Module[i]);
          DrawCount_Trunk(g_gLobalVar.MapTable_Module[i]);
		      DrawCount_Voc(g_gLobalVar.MapTable_Module[i]);
		      DrawCount_ErrFlag(g_gLobalVar.MapTable_Module[i]);
		      DrawCount_RemoveState(g_gLobalVar.MapTable_Module[i]);
        end;
    end;
end;


Procedure DrawCount_Voc(s8ModID:Shortint);
Var
  TmpStr:string;
  iDispRow:Integer;
begin

  iDispRow:=g_gLobalVar.AllDeviceRes[s8ModID].iSeqID + 1;

  TmpStr:=Format('%3d /%3d',[g_gLobalVar.AllDeviceRes[s8ModID].lVocNum, g_gLobalVar.AllDeviceRes[s8ModID].lVocOpened]);
  Form1.ListView1.Items.Item[iDispRow].Subitems.Strings[3]:=TmpStr;
  TmpStr:=Format('%3d',[g_gLobalVar.AllDeviceRes[s8ModID].lVocFreeNum]);
  Form1.ListView1.Items.Item[iDispRow].Subitems.Strings[4]:=TmpStr;

  TmpStr:=Format('%3d /%3d',[g_gLobalVar.g_iTotalVoice, g_gLobalVar.g_iTotalVoiceOpened]);
  Form1.ListView1.Items.Item[0].Subitems.Strings[3]:=TmpStr;
  TmpStr:=Format('%3d',[g_gLobalVar.g_iTotalVoiceFree]);
  Form1.ListView1.Items.Item[0].Subitems.Strings[4]:=TmpStr;

end;

Procedure DrawCount_Trunk(s8ModID:Shortint);
Var
  TmpStr:string;
  iDispRow:Integer;
begin

  iDispRow:=g_gLobalVar.AllDeviceRes[s8ModID].iSeqID + 1;
  TmpStr:=Format('%3d /%3d',[g_gLobalVar.AllDeviceRes[s8ModID].lTrunkNum, g_gLobalVar.AllDeviceRes[s8ModID].lTrunkOpened]);
  Form1.ListView1.Items.Item[iDispRow].Subitems.Strings[2]:=TmpStr;

  TmpStr:=Format('%3d /%3d',[g_gLobalVar.g_iTotalTrunk, g_gLobalVar.g_iTotalTrunkOpened]);
  Form1.ListView1.Items.Item[0].Subitems.Strings[2]:=TmpStr;

end;

Procedure DrawCount_Pcm(s8ModID:Shortint);
Var
  TmpStr:string;
  iDispRow:Integer;
begin

  iDispRow:=g_gLobalVar.AllDeviceRes[s8ModID].iSeqID + 1;
  TmpStr:=Format('%3d /%3d',[g_gLobalVar.AllDeviceRes[s8ModID].lPcmNum, g_gLobalVar.AllDeviceRes[s8ModID].lPcmOpened]);
  Form1.ListView1.Items.Item[iDispRow].Subitems.Strings[1]:=TmpStr;

  TmpStr:=Format('%3d /%3d',[g_gLobalVar.g_iTotalPcm, g_gLobalVar.g_iTotalPcmOpened]);
  Form1.ListView1.Items.Item[0].Subitems.Strings[1]:=TmpStr;

end;

Procedure DrawUser_LineState(pTrunk:pointer);
Var
  StateStr:string;
  iDispRow:Integer;
  pOneUser:^TRUNK_STRUCT;
begin

  pOneUser:=nil;
  pOneUser:=pointer(pTrunk);
  if pOneUser=nil then
    begin
      exit;
    end;
  iDispRow:=pOneUser.iUserSeqID;
  pOneUser:=pointer(pTrunk);
  StateStr:=GetString_LineState(pOneUser.iLineState);
  Form1.ListView3.Items.Item[iDispRow].SubItems.Strings[2]:=StateStr;
end;

Procedure DrawUser_State(pTrunk:pointer);
Var
  StateStr:string;
  iDispRow:Integer;
  pOneUser:^TRUNK_STRUCT;
begin
  pOneUser:=nil;
  pOneUser:=pointer(pTrunk);
  if pOneUser=nil then
    begin
      exit;
    end;
  iDispRow:=pOneUser.iUserSeqID;
  pOneUser:=pointer(pTrunk);
  StateStr:=GetString_UserState(pOneUser.UserState);
  Form1.ListView3.Items.Item[iDispRow].SubItems.Strings[3]:=StateStr;
end;

Function GetString_UserState(iUserID:USER_STATE):string;
begin
  result:='Other';
  case iUserID of
    USER_WAITOPEN: result:='Wait Open';
    USER_FREE: result:='Free';
    USER_OFFHOOK: result:='OffHook';
    USER_CALLOUT: result:='CallOut';
    USER_LINK: result:='WaitHangUp';
    USER_WAITHANGUP: result:='Link';
    USER_WAIT_REMOVE: result:='Remove DSP';
    USER_RING: result:='Ring';
  end;
end;

Procedure DrawPcm_TypeAndAlarm(pPcm:Pointer);
Var
  pOnePcm:^PCM_STRUCT;
  StateStr:string;
  iDispRow,AlarmVal:Integer;
Begin
  pOnePcm:=nil;
  pOnePcm:=pointer(pPcm);
  if pPcm=nil then
    begin
    exit;
    end;
  iDispRow:=pOnePcm.iSeqID;
  AlarmVal:=pOnePcm.s32AlarmVal;

  StateStr:=GetString_PcmType(pOnePcm.u8E1Type);
  Form1.ListView4.Items.Item[iDispRow].SubItems.Strings[0]:=StateStr;

  StateStr:=Format('0X%x',[AlarmVal]);
  Form1.ListView4.Items.Item[iDispRow].SubItems.Strings[1]:=StateStr;

  if GetBit(AlarmVal, 0)=1 then
    begin
      Form1.ListView4.Items.Item[iDispRow].SubItems.Strings[2]:='X';
    end
  else
    begin
      Form1.ListView4.Items.Item[iDispRow].SubItems.Strings[2]:='O';
    end;

  if GetBit(AlarmVal, 1)=1 then
    begin
      Form1.ListView4.Items.Item[iDispRow].SubItems.Strings[3]:='X';
    end
  else
    begin
      Form1.ListView4.Items.Item[iDispRow].SubItems.Strings[3]:='O';
    end;

  if GetBit(AlarmVal, 4)=1 then
    begin
      Form1.ListView4.Items.Item[iDispRow].SubItems.Strings[4]:='X';
    end
  else
    begin
      Form1.ListView4.Items.Item[iDispRow].SubItems.Strings[4]:='O';
    end;
end;

function GetBit(nSourData:Integer;nBit:Byte):Byte;
Var
  ret:Byte;
Begin
   ret:= nSourData shr nBit;
   ret := ret and 1;
   result:=ret;
end;

function GetString_PcmType(iPcmType:Byte):string;
begin

  if iPcmType=0 then
    begin
      result:='Disable';
      exit;
    end;

  result:='UNKNOWN';

  case iPcmType of
    Byte(XMS_E1_TYPE_Analog30): result:='T_Analog30';
    Byte(XMS_E1_TYPE_PCM31): result:='T_PCM31';
    Byte(XMS_E1_TYPE_PCM30): result:='T_PCM30';
    Byte(XMS_E1_TYPE_CAS): result:='T_CAS';
    Byte(XMS_E1_TYPE_PRI): result:='T_PRI';
    Byte(XMS_E1_TYPE_SS7_TUP_0_Link): result:='T_TUP_0_LK';
    Byte(XMS_E1_TYPE_SS7_TUP_1_Link): result:='T_TUP_1_LK';
    Byte(XMS_E1_TYPE_SS7_TUP_2_Link): result:='T_TUP_2_L';
    Byte(XMS_T1_TYPE_D4): result:='T_D4';
    Byte(XMS_T1_TYPE_ESF): result:='T_ESF';
    Byte(XMS_J1_TYPE_D4): result:='J_D4';
    Byte(XMS_J1_TYPE_ESF): result:='J_ESF';
    Byte(XMS_SLC_TYPE_96): result:='SLC_TYPE_96';
    Byte(XMS_E1_TYPE_SS7_ISUP_0_Link): result:='T_ISUP_0_LK';
    Byte(XMS_E1_TYPE_SS7_ISUP_1_Link): result:='T_ISUP_1_LK';
    Byte(XMS_E1_TYPESS7_ISUP_2_Link):  result:='T_ISUP_2_LK';
    Byte(XMS_E1_TYPE_6D25B): result:='T_6D25B';
  end;
end;

Procedure RefreshMapTable();
Var
  i,j:Integer;
  TrkCount, VocCount, PcmCount, ModuleCount, UserCount:Integer;
  iModSeqID:Integer;
  pVoc:^VOICE_STRUCT;
  pTrunk:^TRUNK_STRUCT;
  pPcm:^PCM_STRUCT;
Begin

  pVoc:=nil;
  pTrunk:=nil;
  pPcm:=nil;

  ModuleCount:=0;
  TrkCount:=0;
  VocCount:=0;
  PcmCount:=0;
  UserCount:=0;

  for i:=0 to 255 do
    begin
      if g_gLobalVar.AllDeviceRes[i].lFlag=1 then
        begin
          g_gLobalVar.AllDeviceRes[i].iSeqID:=ModuleCount;
          g_gLobalVar.MapTable_Module[ModuleCount]:=i;
          inc(ModuleCount);
          if g_gLobalVar.AllDeviceRes[i].lVocNum>0 then
          begin
            pVoc:=Pointer(g_gLobalVar.AllDeviceRes[i].pVoice);
            for j:=0 to g_gLobalVar.AllDeviceRes[i].lVocNum-1 do
              begin
                pVoc.iSeqID:=VocCount;
                g_gLobalVar.MapTable_Voice[VocCount].m_s8ModuleID:=pVoc.deviceID.m_s8ModuleID;
                g_gLobalVar.MapTable_Voice[VocCount].m_s16ChannelID:=pVoc.deviceID.m_s16ChannelID;
                if j<>g_gLobalVar.AllDeviceRes[i].lVocNum-1 then
                  inc(pVoc);
                inc(VocCount);
              end;
          end;
          if g_gLobalVar.AllDeviceRes[i].lPcmNum > 0 then
            begin
              pPcm:=pointer(g_gLobalVar.AllDeviceRes[i].pPcm);
              for j:= 0 to g_gLobalVar.AllDeviceRes[i].lPcmNum-1 do
                begin
                    pPcm.iSeqID:=PcmCount;
				            g_gLobalVar.MapTable_Pcm[PcmCount].m_s8ModuleID:=pPcm.deviceID.m_s8ModuleID;
				            g_gLobalVar.MapTable_Pcm[PcmCount].m_s16ChannelID:=pPcm.deviceID.m_s16ChannelID;
				            inc(PcmCount);
                    if j<>g_gLobalVar.AllDeviceRes[i].lPcmNum-1 then
                      inc(pPcm);
                end;
            end;

         iModSeqID:=0;
         if g_gLobalVar.AllDeviceRes[i].lTrunkNum > 0 then
         begin
            pTrunk:=Pointer(g_gLobalVar.AllDeviceRes[i].pTrunk);
            for j:=0 to g_gLobalVar.AllDeviceRes[i].lTrunkNum-1 do
              begin
                pTrunk.iSeqID := TrkCount;
                g_gLobalVar.MapTable_Trunk[TrkCount].m_s8ModuleID:=pTrunk.deviceID.m_s8ModuleID;
                g_gLobalVar.MapTable_Trunk[TrkCount].m_s16ChannelID:=pTrunk.deviceID.m_s16ChannelID;
                inc(TrkCount);
               // DevSubType:=XMS_INTERFACE_DEVSUB_TYPE(pTrunk.deviceID.m_s16DeviceSub);

                if pTrunk.deviceID.m_s16DeviceSub <> Smallint(XMS_DEVSUB_UNUSABLE) then
                  begin
                    pTrunk.iModSeqID:=iModSeqID;
                    inc(iModSeqID);
                  end;

                if pTrunk.deviceID.m_s16DeviceSub=Smallint(XMS_DEVSUB_ANALOG_USER) then
                  begin
                    pTrunk.iUserSeqID:=UserCount;
                    g_gLobalVar.MapTable_User[UserCount].m_s8ModuleID:=pTrunk.deviceID.m_s8ModuleID;
                    g_gLobalVar.MapTable_User[UserCount].m_s16ChannelID:=pTrunk.deviceID.m_s16ChannelID;
					          inc(UserCount);
                  end;

                if (j>=0 ) and (j<g_gLobalVar.AllDeviceRes[i].lTrunkNum-1) then
                  begin
                    inc(pTrunk);
                  end;

              end;
            end;
        end;
    end;
    g_gLobalVar.g_iTotalModule := ModuleCount;
	  g_gLobalVar.g_iTotalTrunk := TrkCount;
	  g_gLobalVar.g_iTotalUser := UserCount;
	  g_gLobalVar.g_iTotalVoice := VocCount;
	  g_gLobalVar.g_iTotalPcm := PcmCount;

    Form1.ListView3AddItem(g_gLobalVar.g_iTotalUser);
end;

Procedure OpenAllDevice_Dsp(s8DspModID:Shortint);
var
  i:Integer;
  pVoice:^VOICE_STRUCT;
  pPcm:^PCM_STRUCT;
  pTrunk:^TRUNK_STRUCT;
begin

  pVoice:=nil;
  pPcm:=nil;
  pTrunk:=nil;

  g_gLobalVar.AllDeviceRes[s8DspModID].bErrFlag:=false;
	DrawCount_ErrFlag (s8DspModID);
	g_gLobalVar.AllDeviceRes[s8DspModID].RemoveState:=DSP_REMOVE_STATE_NONE;
	DrawCount_RemoveState (s8DspModID);
  OpenBoardDevice ( s8DspModID );

  if g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum > 0 then
  begin
    pVoice:=pointer(g_gLobalVar.AllDeviceRes[s8DspModID].pVoice);
    for i := 0 to g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum-1 do
	  begin
		  OpenVoiceDevice ( pVoice );
      if i <> g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum-1 then
        begin
          inc(pVoice);
        end;
	  end;
  end;

	// pPcm
  if g_gLobalVar.AllDeviceRes[s8DspModID].lPcmNum > 0 then
  begin
    pPcm:=pointer(g_gLobalVar.AllDeviceRes[s8DspModID].pPcm);
	  for i := 0 to g_gLobalVar.AllDeviceRes[s8DspModID].lPcmNum-1 do
	  begin
		  OpenPcmDevice ( pPcm );
      if i <> g_gLobalVar.AllDeviceRes[s8DspModID].lPcmNum-1 then
        begin
          inc(pPcm);
        end;
	  end;
  end;

	// pTrunk
  if g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum > 0 then
  begin
    pTrunk:=pointer(g_gLobalVar.AllDeviceRes[s8DspModID].pTrunk);
	  for i := 0 to g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum-1 do
	  begin
		  OpenTrunkDevice (pTrunk);
      if i <> g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum-1 then
        begin
          inc(pTrunk);
        end;
	  end;
  end;

end;

Procedure OpenVoiceDevice(OneVoc:pointer);
Var
  ret:Integer;
  PricateData:PrivateData_t;
  pOneVoice:^VOICE_STRUCT;
begin

  pOneVoice:=nil;

  ret:=0;
  PricateData.m_u32DataSize:=0;
  pOneVoice:=pointer(OneVoc);
  if pOneVoice=nil then
  begin
      exit;
  end;

  if pOneVoice.State=VOC_WAITOPEN then
    begin
      ret:=XMS_ctsOpenDevice(g_gLobalVar.g_acsHandle,pOneVoice.deviceID,PricateData);
    end;
  if ret < 0 then
    begin
      msgBuf:=Format('XMS_ctsOpenDevice(%s, %d) FAIL. ret = %d',
                      [g_gLobalVar.cfg_ServerID.m_s8ServerIp, g_gLobalVar.cfg_ServerID.m_u32ServerPort, ret]);
      ShowMessage(msgBuf);
      Form1.AddMsg(msgBuf);
      exit;
    end;
end;

Procedure OpenPcmDevice(OnePcm:pointer);
Var
  ret:Integer;
  PricateData:PrivateData_t;
  pOnePcm:^PCM_STRUCT;
begin
  pOnePcm:=nil;

  ret:=0;
  PricateData.m_u32DataSize:=0;
  pOnePcm:=pointer(OnePcm);
  if pOnePcm=nil then
    begin
      exit;
    end;

  if pOnePcm.bOpenFlag=false then
    begin
      ret:=XMS_ctsOpenDevice(g_gLobalVar.g_acsHandle,pOnePcm.deviceID,PricateData);
    end;
  if ret < 0 then
    begin
      msgBuf:=Format('XMS_ctsOpenDevice(%s, %d) FAIL. ret = %d',
                      [g_gLobalVar.cfg_ServerID.m_s8ServerIp, g_gLobalVar.cfg_ServerID.m_u32ServerPort, ret]);
      ShowMessage(msgBuf);
      Form1.AddMsg(msgBuf);
      exit;
    end;
end;

Procedure OpenTrunkDevice(OneTrunk:pointer);
Var
  ret:Integer;
  PricateData:PrivateData_t;
  pOneTrunk:^TRUNK_STRUCT;
begin

  pOneTrunk:=nil;

  ret:=0;
  PricateData.m_u32DataSize:=0;
  pOneTrunk:=pointer(OneTrunk);

  if pOneTrunk=nil then
    begin
      exit;
    end;
  if pOneTrunk.State=TRK_WAITOPEN then
    begin
      ret:=XMS_ctsOpenDevice(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID,PricateData);
    end;
  if ret < 0 then
    begin
      msgBuf:=Format('XMS_ctsOpenDevice(%s, %d) FAIL. ret = %d',
                      [g_gLobalVar.cfg_ServerID.m_s8ServerIp, g_gLobalVar.cfg_ServerID.m_u32ServerPort, ret]);
      ShowMessage(msgBuf);
      Form1.AddMsg(msgBuf);
      exit;
    end;
end;

Procedure OpenBoardDevice(s8DspModID:Shortint);
var
  ret:Integer;
  PricateData:PrivateData_t;
Begin
  ret:=0;
  PricateData.m_u32DataSize:=0;
  if g_gLobalVar.AllDeviceRes[s8DspModID].bOpenFlag=False then
    begin
      ret:=XMS_ctsOpenDevice(g_gLobalVar.g_acsHandle,g_gLobalVar.AllDeviceRes[s8DspModID].deviceID,PricateData);
    end;

  if ret < 0 then
    begin
      msgBuf:=Format('XMS_ctsOpenDevice(%s, %d) FAIL. ret = %d',
                      [g_gLobalVar.cfg_ServerID.m_s8ServerIp, g_gLobalVar.cfg_ServerID.m_u32ServerPort, ret]);
      ShowMessage(msgBuf);
      Form1.AddMsg(msgBuf);
      exit;
    end;
end;

Procedure DrawCount_ErrFlag(s8ModID:shortint);
var
  TmpStr:string;
  iDispRow:Integer;
begin
  iDispRow:=g_gLobalVar.AllDeviceRes[s8ModID].iSeqID + 1;
  if g_gLobalVar.AllDeviceRes[s8ModID].bErrFlag = True then
  begin
     TmpStr:='T';
  end
  else
  begin
    TmpStr:='';
  end;
  Form1.ListView1.Items.Item[iDispRow].SubItems.Strings[6]:=TmpStr;
end;

Procedure Change_Voc_State(pVoice:pointer;NewState:VOICE_STATE);
Var
  pOneVoice:^VOICE_STRUCT;
begin

  pOneVoice:=nil;
  pOneVoice:=pointer(pVoice);
  if pOneVoice=nil then
    begin
      exit;
    end;
  pOneVoice.State:=NewState;
  if (g_gLobalVar.AllDeviceRes[pOneVoice.deviceID.m_s8ModuleID].RemoveState=DSP_REMOVE_STATE_START) And (NewState=VOC_FREE) then
  begin
    pOneVoice.State:=VOC_WAIT_REMOVE;
    CheckRemoveReady (pOneVoice.deviceID.m_s8ModuleID);
  end;
end;

Procedure CheckRemoveReady(s8DspModID:Shortint);
Var
  i:Integer;
  pTrunkStr:^TRUNK_STRUCT;
  pVocStr:^VOICE_STRUCT;
  //DevSubType:XMS_INTERFACE_DEVSUB_TYPE;
begin

  pTrunkStr:=nil;
  pVocStr:=nil;

  pTrunkStr:=pointer(g_gLobalVar.AllDeviceRes[s8DspModID].pTrunk);
  pVocStr:=pointer(g_gLobalVar.AllDeviceRes[s8DspModID].pVoice);
  for i:=0 to g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum -1 do
  begin
    if(pTrunkStr.State <> TRK_WAITOPEN) and (pTrunkStr.State <> TRK_WAIT_REMOVE) and (pTrunkStr.State <> TRK_NOTHANDLE) then
      begin
        exit;
      end;
    //DevSubType:=XMS_INTERFACE_DEVSUB_TYPE(pTrunkStr.deviceID.m_s16DeviceSub);
    if pTrunkStr.deviceID.m_s16DeviceSub = smallint(XMS_DEVSUB_ANALOG_USER) then
      begin
      if(pTrunkStr.UserState <> USER_WAITOPEN) and (pTrunkStr.UserState <> USER_WAIT_REMOVE) then
        begin
          exit;
        end;
      end;
    if i <> g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum-1 then
      Inc(pTrunkStr);
  end;

  for i:=0 to g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum -1 do
  begin
  if(pVocStr.State <> VOC_WAITOPEN) and (pVocStr.State <> VOC_WAIT_REMOVE) then
    begin
      exit;
    end;
  if  i <> g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum -1 then
  begin
    Inc(pVocStr);
  end;
  end;

  g_gLobalVar.AllDeviceRes[s8DspModID].RemoveState:=DSP_REMOVE_STATE_READY;
  DrawCount_RemoveState ( s8DspModID );
end;

Procedure DrawCount_RemoveState(s8ModID:Shortint);
Var
  TmpStr:string;
  iDispRow:Integer;
begin
  iDispRow:=g_gLobalVar.AllDeviceRes[s8ModID].iSeqID + 1;
  case g_gLobalVar.AllDeviceRes[s8ModID].RemoveState of
  DSP_REMOVE_STATE_NONE: TmpStr:='';
  DSP_REMOVE_STATE_START:TmpStr:='Start';
  DSP_REMOVE_STATE_READY:TmpStr:='Ready';
  end;
  Form1.ListView1.Items.Item[iDispRow].SubItems.Strings[7]:=TmpStr;
end;

Procedure AddDeviceRes(AcsDevList:pointer);
Var
  pAcsDevList:^Acs_Dev_List_Head_t;
  s8DspModID:Shortint;
begin
  pAcsDevList:=nil;

  pAcsDevList:= pointer(AcsDevList);
  if pAcsDevList=nil then
    begin
      exit;
    end;
  s8DspModID:=Shortint(pAcsDevList.m_s32ModuleID);
  if (s8DspModID < 0) or (s8DspModID > 255) then //疑问s8DspModID范围是-128~127
  begin
    exit;
  end;
  case pAcsDevList.m_s32DeviceMain of
  Smallint(XMS_DEVMAIN_VOICE): AddDeviceRes_Voice(s8DspModID, pAcsDevList);
  Smallint(XMS_DEVMAIN_DIGITAL_PORT): AddDeviceRes_Pcm(s8DspModID, pAcsDevList);
  Smallint(XMS_DEVMAIN_INTERFACE_CH): AddDeviceRes_Trunk(s8DspModID, pAcsDevList);
  Smallint(XMS_DEVMAIN_BOARD): AddDeviceRes_Board(s8DspModID, pAcsDevList);
  end;
end;

Procedure AddDeviceRes_Pcm  (s8DspModID:Shortint;pAcsDevList:pointer);
Var
  i,s32Num:Integer;
  pDev:^DeviceID_t;
  PcmDevList:^Acs_Dev_List_Head_t;
  PcmArray:^PCM_STRUCT;
  TmpStr:string;
begin
  pDev:=nil;
  PcmDevList:=nil;
  PcmArray:=nil;

  PcmDevList:=pointer(pAcsDevList);

  if PcmDevList=nil then
    begin
      Exit;
    end;

	s32Num:=PcmDevList.m_s32DeviceNum;
 	if (g_gLobalVar.AllDeviceRes[s8DspModID].lPcmNum = 0) And (s32Num > 0) then		// 新增加的资源
  begin
    g_gLobalVar.AllDeviceRes[s8DspModID].pPcm:=allocmem(sizeof(PCM_STRUCT)*s32Num);
    PcmArray:=pointer(g_gLobalVar.AllDeviceRes[s8DspModID].pPcm);
    if g_gLobalVar.AllDeviceRes[s8DspModID].pPcm <> nil then
    begin
      g_gLobalVar.AllDeviceRes[s8DspModID].lPcmNum:=s32Num;
      g_gLobalVar.AllDeviceRes[s8DspModID].lPcmOpened:=0;
      inc(PcmDevList);
      pDev:=Pointer(PcmDevList);

      for i:=0 to s32Num-1 do
      begin
       CopyMemory(Pointer(@PcmArray.deviceID), pDev, sizeof(DeviceID_t));
       PcmArray.bOpenFlag:=False;
       if i <> s32Num-1 then
       begin
        inc(pDev);
        inc(PcmArray);
       end;
      end;
    end
    else if g_gLobalVar.AllDeviceRes[s8DspModID].pPcm = nil then
    begin
       g_gLobalVar.AllDeviceRes[s8DspModID].lPcmNum:=0;
       g_gLobalVar.AllDeviceRes[s8DspModID].lPcmOpened:=0;
       TmpStr:='AllocMemory PCM_STRUCT fail in AddDeviceRes_Pcm()';
       Form1.AddMsg ( TmpStr );
    end;
  end;

  if (g_gLobalVar.AllDeviceRes[s8DspModID].lPcmNum > 0) And (s32Num = 0) then
  begin
    PcmArray:=pointer(g_gLobalVar.AllDeviceRes[s8DspModID].pPcm);
    for i:=0 to g_gLobalVar.AllDeviceRes[s8DspModID].lPcmNum-1 do
    begin
      if  PcmArray.bOpenFlag <> False then
      begin
        CloseDeviceOK(PcmArray.deviceID);
        if i <> g_gLobalVar.AllDeviceRes[s8DspModID].lPcmNum-1 then
          begin
            inc(PcmArray);
          end;
      end;
    end;
    g_gLobalVar.AllDeviceRes[s8DspModID].lPcmNum:=0;
    g_gLobalVar.AllDeviceRes[s8DspModID].lPcmOpened:=0;
    freemem(g_gLobalVar.AllDeviceRes[s8DspModID].pPcm,sizeof(PCM_STRUCT)*g_gLobalVar.AllDeviceRes[s8DspModID].lPcmNum);
  end;
  Form1.ListView4AddItem(g_gLobalVar.AllDeviceRes[s8DspModID].lPcmNum);
end;

Procedure AddDeviceRes_Trunk(s8DspModID:Shortint;pAcsDevList:pointer);
Var
  i,s32Num:Integer;
  pDev:^DeviceID_t;
  TrunkDevList:^Acs_Dev_List_Head_t;
  TrunkArray:^TRUNK_STRUCT;
  TmpStr:string;
begin
  pDev:=nil;
  TrunkDevList:=nil;
  TrunkArray:=nil;

  TrunkDevList:=pointer(pAcsDevList);
  if TrunkDevList=nil then
    begin
      exit;
    end;

	s32Num:=TrunkDevList.m_s32DeviceNum;
 	if (g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum = 0) And (s32Num > 0) then		// 新增加的资源
  begin
    g_gLobalVar.AllDeviceRes[s8DspModID].pTrunk:=allocmem(sizeof(TRUNK_STRUCT)*s32Num);
    TrunkArray:=pointer(g_gLobalVar.AllDeviceRes[s8DspModID].pTrunk);
    if g_gLobalVar.AllDeviceRes[s8DspModID].pTrunk <> nil then
    begin
      g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum:=s32Num;
      g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkOpened:=0;
      inc(TrunkDevList);
      pDev:=Pointer(TrunkDevList);
      for i:=0 to s32Num-1 do
      begin
       CopyMemory(Pointer(@TrunkArray.deviceID), pDev, sizeof(DeviceID_t));
       TrunkArray.State:=TRK_WAITOPEN;
       if i <> s32Num-1 then
       begin
        inc(pDev);
        inc(TrunkArray);
       end;
      end;
    end
    else if g_gLobalVar.AllDeviceRes[s8DspModID].pVoice = nil then
    begin
       g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum:=0;
       g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkOpened:=0;
       TmpStr:='AllocMemory TRUNK_STRUCT fail in AddDeviceRes_Trunk()';
       Form1.AddMsg ( TmpStr );
    end;
  end;

  if (g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum > 0) And (s32Num = 0) then
  begin
    TrunkArray:=pointer(g_gLobalVar.AllDeviceRes[s8DspModID].pTrunk);
    for i:=0 to g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum-1 do
    begin
      if  TrunkArray.State <> TRK_WAITOPEN then
      begin
        CloseDeviceOK(TrunkArray.deviceID);
        if i <> g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum-1 then
        begin
          inc(TrunkArray);
        end;
      end;
    end;

    freemem(g_gLobalVar.AllDeviceRes[s8DspModID].pTrunk,sizeof(TRUNK_STRUCT)*g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum);
    g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum:=0;
    g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkOpened:=0;
  end;
  Form1.ListView2AddItem(g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum);
end;

Procedure AddDeviceRes_Board(s8DspModID:Shortint;pAcsDevList:pointer);
Var
  s32Num:Integer;
  pDev:^DeviceID_t;
  PboardDevList:^Acs_Dev_List_Head_t;
begin
  pDev:=nil;
  PboardDevList:=nil;

  PboardDevList:=pointer(pAcsDevList);
  if PboardDevList=nil then
    begin
      exit;
    end;

  s32Num:=PboardDevList.m_s32DeviceNum;
  if (g_gLobalVar.AllDeviceRes[s8DspModID].lFlag=0) And (s32Num >0) then
  begin
    //inc(PboardDevList,sizeof(Acs_Dev_List_Head_t));
    inc(PboardDevList);
    pDev:=pointer(PboardDevList);
    CopyMemory(Pointer(@g_gLobalVar.AllDeviceRes[s8DspModID].deviceID), pDev, sizeof(DeviceID_t));
    g_gLobalVar.AllDeviceRes[s8DspModID].bOpenFlag := false;
		g_gLobalVar.AllDeviceRes[s8DspModID].bErrFlag := false;
		g_gLobalVar.AllDeviceRes[s8DspModID].RemoveState := DSP_REMOVE_STATE_NONE;
  end
  else
  if (g_gLobalVar.AllDeviceRes[s8DspModID].lFlag=1) And (s32Num=0) then
  begin
    if g_gLobalVar.AllDeviceRes[s8DspModID].bOpenFlag <> False then
      begin
        CloseDeviceOK (g_gLobalVar.AllDeviceRes[s8DspModID].deviceID);
      end;
    fillchar(g_gLobalVar.AllDeviceRes[s8DspModID].deviceID,sizeof(DeviceID_t),0);
  end;
end;

Procedure AddDeviceRes_Voice(s8DspModID:Shortint;pAcsDevList:pointer);
Var
  i,s32Num:Integer;
  pDev:^DeviceID_t;
  VocDevList:^Acs_Dev_List_Head_t;
  VocArray:^VOICE_STRUCT;
  TmpStr:string;
begin
  pDev:=nil;
  VocDevList:=nil;
  VocArray:=nil;

  VocDevList:=pAcsDevList;

  if  VocDevList=nil then
    begin
      exit;
    end;
	s32Num:=VocDevList.m_s32DeviceNum;
 	if (g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum = 0) And (s32Num > 0) then		// 新增加的资源
  begin
    g_gLobalVar.AllDeviceRes[s8DspModID].pVoice:=allocmem(sizeof(VOICE_STRUCT)*s32Num);
    VocArray:=pointer(g_gLobalVar.AllDeviceRes[s8DspModID].pVoice);
    if g_gLobalVar.AllDeviceRes[s8DspModID].pVoice <> nil then
    begin
      g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum:=s32Num;
      g_gLobalVar.AllDeviceRes[s8DspModID].lVocOpened:=0;
      g_gLobalVar.AllDeviceRes[s8DspModID].lVocFreeNum:=0;

      inc(VocDevList);
      pDev:=Pointer(VocDevList);
      for i:=0 to s32Num-1 do
      begin
       CopyMemory(Pointer(@VocArray.deviceID), pDev, sizeof(DeviceID_t));
       VocArray.State := VOC_WAITOPEN;
       if i <> s32num-1 then
        begin
          inc(pDev);
          inc(VocArray);
        end;
      end;
    end
    else if g_gLobalVar.AllDeviceRes[s8DspModID].pVoice = nil then
    begin
       g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum:=s32Num;
       g_gLobalVar.AllDeviceRes[s8DspModID].lVocOpened:=0;
       g_gLobalVar.AllDeviceRes[s8DspModID].lVocFreeNum:=0;
       TmpStr:='AllocMemory VOICE_STRUCT fail in AddDeviceRes_Voice()';
       Form1.AddMsg ( TmpStr );
    end;
  end;

  if (g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum > 0) And (s32Num = 0) then
  begin
    VocArray:=pointer(g_gLobalVar.AllDeviceRes[s8DspModID].pVoice);
    for i:=0 to g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum-1 do
    begin
      if  VocArray.State <> VOC_WAITOPEN then
      begin
        CloseDeviceOK(VocArray.deviceID);
        if i <> g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum-1 then
          begin
            inc(VocArray);
          end;
      end;
    end;
    g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum:=0;
    g_gLobalVar.AllDeviceRes[s8DspModID].lVocOpened:=0;
    g_gLobalVar.AllDeviceRes[s8DspModID].lVocFreeNum:=0;
    freemem(g_gLobalVar.AllDeviceRes[s8DspModID].pVoice,sizeof(VOICE_STRUCT)*g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum);
  end;
end;

Function GetString_EventType(s32EventType:Integer):string;
begin
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
    else result:='UNKNOWN';
  end;
end;

function GetString_DeviceMain(nDevMain:Smallint):string;
begin
  result:='UNKNOWN';
  case nDevMain of
    Smallint(XMS_DEVMAIN_VOICE): result:='VOC';
    Smallint(XMS_DEVMAIN_FAX): result:='FAX';
    Smallint(XMS_DEVMAIN_DIGITAL_PORT): result:='DIGIT';
    Smallint(XMS_DEVMAIN_INTERFACE_CH): result:='INTCH';
    Smallint(XMS_DEVMAIN_DSS1_LINK): result:='DSS1';
    Smallint(XMS_DEVMAIN_SS7_LINK): result:='SS7';
    Smallint(XMS_DEVMAIN_BOARD): result:='BRD';
    Smallint(XMS_DEVMAIN_CTBUS_TS): result:='CTBUS';
    Smallint(XMS_DEVMAIN_CONFERENCE): result:='CONF';
    Smallint(XMS_DEVMAIN_VIDEO): result:='VIDEO';
    Smallint(XMS_DEVMAIN_VOIP):  result:='VOIP';
  end;
end;

function GetString_DeviceSub(nDeviceSub:Smallint):string;
begin
  result:='UNKNOWN';
  case nDeviceSub of
     smallint(XMS_DEVSUB_BASE):						result:='BASE';
     smallint(XMS_DEVSUB_ANALOG_TRUNK):						result:='A_TRUNK';
     smallint(XMS_DEVSUB_ANALOG_USER):						result:='A_USER';
     smallint(XMS_DEVSUB_ANALOG_HIZ):						result:='A_HIZ';
     smallint(XMS_DEVSUB_ANALOG_EMPTY):						result:='A_EMPTY';
     smallint(XMS_DEVSUB_E1_PCM):						result:='E1_PCM';
     smallint(XMS_DEVSUB_E1_CAS):						result:='E1_CAS';
     smallint(XMS_DEVSUB_E1_DSS1):						result:='E1_DSS1';
     smallint(XMS_DEVSUB_E1_SS7_TUP):						result:='E1_TUP';
     smallint(XMS_DEVSUB_E1_SS7_ISUP):						result:='E1_ISUP';
     smallint(XMS_DEVSUB_ANALOG_VOC2W):						result:='A_VOC2W';
     smallint(XMS_DEVSUB_ANALOG_VOC4W):						result:='A_VOC4W';
     smallint(XMS_DEVSUB_ANALOG_EM):						result:='A_EM';
     smallint(XMS_DEVSUB_E1_DCH):						result:='E1_DCH';
     smallint(XMS_DEVSUB_E1_BCH):						result:='E1_BCH';
     smallint(XMS_DEVSUB_UNUSABLE):						result:='UNUSE';

     smallint(XMS_DEVSUB_HIZ_CAS):						result:='HIZ_CAS';
     smallint(XMS_DEVSUB_HIZ_PRI):						result:='HIZ_PRI';
     smallint(XMS_DEVSUB_HIZ_SS7):						result:='HIZ_SS7';
     smallint(XMS_DEVSUB_HIZ_PRI_LINK):						result:='HIZ_PRI_LINK';
     smallint(XMS_DEVSUB_HIZ_SS7_64K_LINK):						result:='HIZ_SS7_64K_LINK';
     smallint(XMS_DEVSUB_HIZ_SS7_2M_LINK):						result:='HIZ_SS7_2M_LINK';
     smallint(XMS_DEVSUB_SS7_LINK):						result:='SS7_LINK';
     smallint(XMS_DEVSUB_LINESIDE):						result:='LINESIDE';
     smallint(XMS_DEVSUB_ANALOG_REC):						result:='A_REC';
     smallint(XMS_DEVSUB_DIGITAL_REC):						result:='D_REC';
     smallint(XMS_DEVSUB_HIZ_HDLC_N64K_LINK):						result:='HDLC_N64_LINK';
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

Procedure DrawMain_LineState (pTrunk:pointer);
Var
  StateStr:string;
  iDispRow:Integer;
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=nil;

  pOneTrunk:=pointer(pTrunk);

  if pOneTrunk=nil then
    begin
      exit;
    end;
  iDispRow := pOneTrunk.iSeqID;
	if iDispRow < 0 then
    begin
      exit;
    end;

	StateStr:=GetString_LineState(pOneTrunk.iLineState);

  Form1.ListView2.Items.Item[iDispRow].Subitems.Strings[2]:=StateStr;
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

Procedure	DrawMain_State(pTrunk:pointer);
Var
  //TrunkSta:TRUNK_STATE;
  pOneTrunk:^TRUNK_STRUCT;
  StateStr:string;
  iDispRow:integer;
begin
  pOneTrunk:=nil;
  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then
  begin
  exit;
  end;
  iDispRow := pOneTrunk.iSeqID;
  if iDispRow < 0 then exit;
  pOneTrunk:=pointer(pTrunk);

  case pOneTrunk.State of
    TRK_WAITOPEN: StateStr:='Wait Open';
    TRK_FREE:     StateStr:='Free';
    TRK_NOTHANDLE:StateStr:='NotHandle';
    TRK_CALLOUT:  StateStr:='CallOut';
    TRK_SIM_CALLOUT: StateStr:='SimCallOut';
    TRK_SIM_LINK:    StateStr:='SimLinkOk';
    TRK_SIM_ANALOG_OFFHOOK: StateStr:='OffHook';
    TRK_SIM_ANALOG_DIALING: StateStr:='Dialing';
    TRK_LINK:      StateStr:='Link';
    TRK_PLAYDTMF:  StateStr:='PlayDtmf';
    TRK_HANGUP:    StateStr:='HangUp';
    TRK_FAIL:      StateStr:='FAIL';
    TRK_WAIT_REMOVE:        StateStr:='Remove DSP';
  end;
  Form1.ListView2.Items.Item[iDispRow].Subitems.Strings[3]:=StateStr;
end;

Procedure	DrawMain_CallInfo(pTrunk:pointer);
Var
  StateStr:string;
  iDispRow:Integer;
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=nil;
  pOneTrunk:=pointer(pTrunk);
  if pTrunk=nil then
    begin
      exit;
    end;
  iDispRow := CalDispRow(pOneTrunk.iSeqID);
	if iDispRow<0	then exit;
  pOneTrunk:=pointer(pTrunk);

	StateStr:=pOneTrunk.CalleeCode;
  Form1.ListView2.Items.Item[iDispRow].Subitems.Strings[4]:=StateStr;

	StateStr:=pOneTrunk.CallerCode;
  Form1.ListView2.Items.Item[iDispRow].Subitems.Strings[5]:=StateStr;
end;

Procedure DispEventInfo(AcsEvt:pointer);
var
  TmpS:string;
  TmpStr:string;
  pAcsEvt:^Acs_Evt_t;
  pAcsTempEvt:^Acs_Evt_t;
  pAcsDevList:^Acs_Dev_List_Head_t;
  pAcsUniFailure:^Acs_UniFailure_Data;
begin
  TmpS:='';
  TmpStr:='';
  pAcsEvt:=nil;
  pAcsTempEvt:=nil;
  pAcsDevList:=nil;
  pAcsUniFailure:=nil;

  pAcsEvt:=pointer(AcsEvt);
  pAcsTempEvt:=pointer(pAcsEvt);
  if pAcsEvt=nil then exit;
  TmpS:=Format('EVT(%4d) : ',[pAcsEvt.m_s32EvtSize]);
  TmpStr:=Format('%s %s',[TmpS,GetString_EventType(pAcsEvt.m_s32EventType)]);

  case pAcsEvt.m_s32EventType of

    integer(XMS_EVT_QUERY_DEVICE):
    begin
      inc(pAcsTempEvt);
      pAcsDevList:=pointer(pAcsTempEvt);
      TmpS:=format('(%s,%2d,%3d)',[GetString_DeviceMain(pAcsDevList.m_s32DeviceMain),pAcsDevList.m_s32ModuleID,pAcsDevList.m_s32DeviceNum]);
      TmpStr:=conCat(TmpStr, TmpS);
    end;

    integer(XMS_EVT_UNIFAILURE):
    begin
      inc(pAcsTempEvt);
      pAcsUniFailure:=pointer(pAcsTempEvt);
      TmpS:=format(': %s(0x%X) Dev=(%s, %d, %d)',
                    [GetString_ErrorCode(pAcsUniFailure.m_s32AcsEvtErrCode),pAcsUniFailure.m_s32AcsEvtErrCode,GetString_DeviceMain(pAcsEvt.m_DeviceID.m_s16DeviceMain),
                     pAcsEvt.m_DeviceID.m_s8ModuleID,pAcsEvt.m_DeviceID.m_s16ChannelID]);

       TmpStr:=conCat(TmpStr, TmpS);
    end;

    else
      begin
        Tmps:=format('Dev=(%s, %d, %d)',[GetString_DeviceMain(pAcsEvt.m_DeviceID.m_s16DeviceMain),pAcsEvt.m_DeviceID.m_s8ModuleID,pAcsEvt.m_DeviceID.m_s16ChannelID]);
        TmpStr:=conCat(TmpStr, TmpS);
      end;

  end;
  Form1.AddMsg(TmpStr);
end;

{$R *.dfm}

Procedure TForm1.ReadIniFile();
Var
  inifile:Tinifile;
  tempStr:string;

begin
  g_gLobalVar.cfg_IniShortName:='.\XMS_Dial.INI';
  inifile:=Tinifile.Create(g_gLobalVar.cfg_IniShortName);
        tempStr:=inifile.ReadString('ConfigInfo','IpAddr','192.168.10.75');
        strpCopy(g_gLobalVar.cfg_ServerID.m_s8ServerIp, tempStr);
        Edit1.Text:=g_gLobalVar.cfg_ServerID.m_s8ServerIp;
        g_gLobalVar.cfg_ServerID.m_u32ServerPort:=inifile.ReadInteger('ConfigInfo','Port',9000);
        Edit2.Text:=IntToStr(g_gLobalVar.cfg_ServerID.m_u32ServerPort);
        tempStr:=inifile.ReadString('ConfigInfo','UserName','');
        strpCopy(g_gLobalVar.cfg_ServerID.m_s8UserName, tempStr);
        tempStr:=inifile.ReadString('ConfigInfo','PassWord','');
        strpCopy(g_gLobalVar.cfg_ServerID.m_s8UserPwd, tempStr);
        g_gLobalVar.cfg_iCalledLen:=inifile.ReadInteger('ConfigInfo','CalledLen',5);
        if g_gLobalVar.cfg_iCalledLen > 20 then
         begin
          g_gLobalVar.cfg_iCalledLen := 20;
         end;
        tempStr:=inifile.ReadString('ConfigInfo','CallingNum','83636988');
        strpCopy(g_gLobalVar.cfg_CallingNum, tempStr);
        g_gLobalVar.cfg_iCallOutRule:=inifile.ReadInteger('ConfigInfo','CallOutRule',0);
        tempStr:=inifile.ReadString('ConfigInfo','SimCalledRNum','12345');
        strpCopy(g_gLobalVar.cfg_SimCalledNum, tempStr);
        g_gLobalVar.cfg_iPartWork:=inifile.ReadInteger('ConfigInfo','PartWork',0);
        g_gLobalVar.cfg_iPartWorkModuleID:=inifile.ReadInteger('ConfigInfo','PartWorkModuleID',0);
        g_gLobalVar.cfg_s32DebugOn:=inifile.ReadInteger('ConfigInfo','DebugOn',0);
  inifile.Free;
end;

Procedure TForm1.InitListMain();
var
  Item:TListColumn;
begin
  Item:=ListView2.Columns.Add;
  Item.Caption:='ID';
  Item.Width:=30;

  Item:=ListView2.Columns.Add;
  Item.Caption:='Mod,Ch';
  Item.Width:=50;

  Item:=ListView2.Columns.Add;
  Item.Caption:='Type';
  Item.Width:=60;

	Item:=ListView2.Columns.Add;
  Item.Caption:='LineState';
  Item.Width:=70;

	Item:=ListView2.Columns.Add;
  Item.Caption:='State';
  Item.Width:=70;

	Item:=ListView2.Columns.Add;
  Item.Caption:='Called';
  Item.Width:=60;

	Item:=ListView2.Columns.Add;
  Item.Caption:='Calling';
  Item.Width:=60;

	Item:=ListView2.Columns.Add;
  Item.Caption:='LinkDev';
  Item.Width:=60;

	Item:=ListView2.Columns.Add;
  Item.Caption:='FailReason';
  Item.Width:=75;
end;

Procedure TForm1.InitListUser();
var
  Item:TListColumn;
begin
  Item:=ListView3.Columns.Add;
  Item.Caption:='ID';
  Item.Width:=30;

  Item:=ListView3.Columns.Add;
  Item.Caption:='Mod,Ch';
  Item.Width:=50;

  Item:=ListView3.Columns.Add;
  Item.Caption:='Type';
  Item.Width:=60;

	Item:=ListView3.Columns.Add;
  Item.Caption:='LineState';
  Item.Width:=70;

	Item:=ListView3.Columns.Add;
  Item.Caption:='State';
  Item.Width:=70;

	Item:=ListView3.Columns.Add;
  Item.Caption:='DTMF';
  Item.Width:=60;

	Item:=ListView3.Columns.Add;
  Item.Caption:='VocInfo';
  Item.Width:=70;

	Item:=ListView3.Columns.Add;
  Item.Caption:='LinkDev';
  Item.Width:=70;
end;

Procedure TForm1.InitListPcm();
var
  Item:TListColumn;
begin
  Item:=ListView4.Columns.Add;
  Item.Caption:='PcmID';
  Item.Width:=60;

  Item:=ListView4.Columns.Add;
  Item.Caption:='Type';
  Item.Width:=80;

  Item:=ListView4.Columns.Add;
  Item.Caption:='Alarm Value';
  Item.Width:=80;

	Item:=ListView4.Columns.Add;
  Item.Caption:='Sig Detect';
  Item.Width:=80;

	Item:=ListView4.Columns.Add;
  Item.Caption:='Frame Sync';
  Item.Width:=80;

	Item:=ListView4.Columns.Add;
  Item.Caption:='Remote Alarm';
  Item.Width:=85;
end;

Procedure TForm1.InitListMsg();
var
  i:integer;
begin
  i:=ListBox1.ScrollWidth;
  ListBox1.ScrollWidth:=(i +1000);
end;

Procedure TForm1.InitListCount();
Var
  Item:TListColumn;
Begin
  Item:=ListView1.Columns.Add;
  Item.Caption:='ID';
  Item.Width:=40;

  Item:=ListView1.Columns.Add;
  Item.Caption:='ModID';
  Item.Width:=45;

	Item:=ListView1.Columns.Add;
  Item.Caption:='Pcm/Open';
  Item.Width:=70;

	Item:=ListView1.Columns.Add;
  Item.Caption:='Trk/Open';
  Item.Width:=70;

	Item:=ListView1.Columns.Add;
  Item.Caption:='Voc/Open';
  Item.Width:=70;

	Item:=ListView1.Columns.Add;
  Item.Caption:='VocFree';
  Item.Width:=55;

	Item:=ListView1.Columns.Add;
  Item.Caption:='User/Open';
  Item.Width:=70;

  Item:=ListView1.Columns.Add;
  Item.Caption:='ErrFlag';
  Item.Width:=60;

	Item:=ListView1.Columns.Add;
  Item.Caption:='RemoveState';
  Item.Width:=80;
end;

Procedure Tform1.InitTextBox();
begin
  Edit1.Text:=g_gLobalVar.cfg_ServerID.m_s8ServerIp;
  Edit2.Text:=IntToStr(g_gLobalVar.cfg_ServerID.m_u32ServerPort);
  Edit3.Text:=IntToStr(g_gLobalVar.cfg_iCalledLen);
  Edit4.Text:=g_gLobalVar.cfg_CallingNum;
  if g_gLobalVar.cfg_iCallOutRule=0 then
    begin
      RadioButton1.Checked:=True;
    end
  else if g_gLobalVar.cfg_iCallOutRule=1 then
    begin
      RadioButton2.Checked:=True;
    end
  else
    begin
      RadioButton3.Checked:=True;
    end;
  Edit5.Text:=g_gLobalVar.cfg_SimCalledNum;
  if g_gLobalVar.cfg_iPartWork = 0 then
    begin
      CheckBox2.Checked:=False;
    end
  else
    begin
      CheckBox2.Checked:=True;
    end;
  Edit6.Text:=IntToStr(g_gLobalVar.cfg_iPartWorkModuleID);
  if g_gLobalVar.cfg_s32DebugOn=0 then
    begin
      CheckBox1.Checked:=False;
    end
  else
    begin
      CheckBox1.Checked:=True;
    end;
end;

Procedure TForm1.AddMsg(msgBuf:string); //给ListBox添加消息
var
  Msg:String;
Begin
  Msg:=Format('%3d: ',[g_NumOfListBox]);
  Msg:=Msg+msgBuf;
  if g_NumOfListBox=5000 then
    begin
      g_NumOfListBox:=1;
      ListBox1.Clear;
    end;
  ListBox1.Items.Add(Msg);
  inc(g_NumOfListBox);
end;

Function TForm1.LoadDJApi():Byte;
Begin
  DJApiHandle := LoadLibrary('DJAcsAPI.dll');
  if DJApiHandle <> 0 then
  begin
       g_pDJApiOpenStream:=GetProcAddress(DJApiHandle, 'XMS_acsOpenStream');
       if g_pDJApiOpenStream=nil  then
       begin
          ShowMessage('XMS_acsOpenStream函数加载失败。');
          result:=0;
          exit;
       end;

       g_pDJApiSetEsr:=GetProcAddress(DJApiHandle,'XMS_acsSetESR');
       if g_pDJApiSetEsr=nil  then
       begin
          ShowMessage('XMS_acsSetESR函数加载失败。');
          result:=0;
          exit;
       end;

       g_pDJApiGetDevList:=GetProcAddress(DJApiHandle,'XMS_acsGetDeviceList');
       if g_pDJApiSetEsr=nil  then
       begin
          ShowMessage('XMS_acsGetDeviceList函数加载失败。');
          result:=0;
          exit;
       end;

       g_pDJApiOpenDevice:=GetProcAddress(DJApiHandle,'XMS_ctsOpenDevice');
       if g_pDJApiOpenDevice=nil then
       begin
          ShowMessage('XMS_ctsOpenDevice函数加载失败。');
          result:=0;
          exit;
       end;

       g_pDJApiSetParam:=GetProcAddress(DJApiHandle,'XMS_ctsSetParam');
       if g_pDJApiSetParam=nil then
       begin
          ShowMessage('XMS_ctsSetParam函数加载失败。');
          result:=0;
          exit;
       end;

       g_pDJApiResetDevice:=GetProcAddress(DJApiHandle,'XMS_ctsResetDevice');
       if g_pDJApiResetDevice=nil then
       begin
          ShowMessage('XMS_ctsResetDevice函数加载失败。');
          result:=0;
          exit;
       end;

       g_pDJApiGetDevState:=GetProcAddress(DJApiHandle,'XMS_ctsGetDevState');
       if g_pDJApiGetDevState=nil then
       begin
          ShowMessage('XMS_ctsGetDevState函数加载失败。');
          result:=0;
          exit;
       end;

       g_pDJApiUnlinkDevice:=GetProcAddress(DJApiHandle,'XMS_ctsUnlinkDevice');
       if g_pDJApiUnlinkDevice=nil then
       begin
          ShowMessage('XMS_ctsUnlinkDevice函数加载失败。');
          result:=0;
          exit;
       end;

       g_pDJApiLinkDevice:=GetProcAddress(DJApiHandle,'XMS_ctsLinkDevice');
       if g_pDJApiLinkDevice=nil then
       begin
          ShowMessage('XMS_ctsLinkDevice函数加载失败。');
          result:=0;
          exit;
       end;

       g_pDJApiSendIOData:=GetProcAddress(DJApiHandle,'XMS_ctsSendIOData');
       if g_pDJApiSendIOData=nil then
       begin
          ShowMessage('XMS_ctsSendIOData函数加载失败。');
          result:=0;
          exit;
       end;

       g_pDJApiSetDevTimer:=GetProcAddress(DJApiHandle,'XMS_ctsSetDevTimer');
       if g_pDJApiSetDevTimer=nil then
       begin
          ShowMessage('XMS_ctsSetDevTimer函数加载失败。');
          result:=0;
          exit;
       end;

       g_pDJApiMakeCallOut:=GetProcAddress(DJApiHandle,'XMS_ctsMakeCallOut');
       if g_pDJApiMakeCallOut=nil then
       begin
          ShowMessage('XMS_ctsMakeCallOut函数加载失败。');
          result:=0;
          exit;
       end;

       g_pDJApiClearCall:=GetProcAddress(DJApiHandle,'XMS_ctsClearCall');
       if g_pDJApiClearCall=nil then
       begin
          ShowMessage('XMS_ctsClearCall函数加载失败。');
          result:=0;
          exit;
       end;

       g_pDJApiCloseStream:=GetProcAddress(DJApiHandle,'XMS_acsCloseStream');
       if g_pDJApiCloseStream=nil then
       begin
          ShowMessage('XMS_acsCloseStream函数加载失败。');
          result:=0;
          exit;
       end;
  end;
  result:=1;
end;

Function TForm1.InitSystem():Byte;
Var
  ret:Integer;
  PravateData:PrivateData_t;
  MsgStr:string;
begin
  Fillchar(g_gLobalVar,sizeof(Tglobal),0);
  g_gLobalVar.g_u8UnitID:=1;
  g_NumOfListBox:=1;
  PravateData.m_u32DataSize:=0;
  g_gLobalVar.g_acsHandle:=0;
  g_gLobalVar.cfg_iDispChnl:=32;
  iLoopStartSearchFreeTrunk:=0;
  FillChar(g_gLobalVar.cfg_CallingNum,sizeof(g_gLobalVar.cfg_CallingNum),0);
  FillChar(g_gLobalVar.cfg_SimCalledNum,sizeof(g_gLobalVar.cfg_SimCalledNum),0);
  ReadIniFile();
  if CAS_Common_Cfg_ReadCfg (g_gLobalVar.g_Param_CAS) <> 0 then
  begin
		MsgStr:='CAS_Common_Cfg_ReadCfg \"D:\DJKeygoe\Samples\Delphi\CAS_Common_Code\XMS_CAS_Cfg.INI\" Error!';
		ShowMessage(MsgStr);
	end;

  if Analog_Common_Cfg_ReadCfg(g_gLobalVar.g_Param_Analog) <> 0 then
    begin
      MsgStr:='Analog_Common_Cfg_ReadCfg \"C:\DJKeygoe\Samples\Delphi\Analog_Common_Code\XMS_Analog_Cfg.INI\" Error!';
		  ShowMessage(MsgStr);
    end;

  InitListMain();
  InitListUser();
  InitListPcm();
  InitListMsg();
  InitListCount();
  InitTextBox();
  ret:=LoadDJApi();
  if ret=0 then
  begin
    result:=0;
    exit;
  end;
  ret:=XMS_acsOpenStream(g_gLobalVar.g_acsHandle,
                         g_gLobalVar.cfg_ServerID,
                         g_gLobalVar.g_u8UnitID,
                         32,32,
                         g_gLobalVar.cfg_s32DebugOn,
                         PravateData);
  if ret < 0 then
  begin
    msgBuf:=Format('XMS_acsOpenStream(%s, %d) FAIL. ret = %d',
      [g_gLobalVar.cfg_ServerID.m_s8ServerIp, g_gLobalVar.cfg_ServerID.m_u32ServerPort, ret]);
    ShowMessage(msgBuf);
    AddMsg(msgBuf);
    result:=0;
    exit;
  end
  else
  Begin
    msgBuf:=Format('XMS_acsOpenStream(%s, %d) OK!',[g_gLobalVar.cfg_ServerID.m_s8ServerIp, g_gLobalVar.cfg_ServerID.m_u32ServerPort]);
    AddMsg(msgBuf)
  end;

  ret:=XMS_acsSetEsr(g_gLobalVar.g_acsHandle,@esr,0,1);
  if ret < 0 then
  Begin
  msgBuf:=Format('XMS_acsSetEsr(%s, %d) FAIL. ret = %d',
      [g_gLobalVar.cfg_ServerID.m_s8ServerIp, g_gLobalVar.cfg_ServerID.m_u32ServerPort, ret]);
    ShowMessage(msgBuf);
    AddMsg(msgBuf);
    result:=0;
    exit;
  end
  else
  Begin
    msgBuf:=Format('XMS_acsSetEsr(%s, %d) OK!',[g_gLobalVar.cfg_ServerID.m_s8ServerIp, g_gLobalVar.cfg_ServerID.m_u32ServerPort]);
    AddMsg(msgBuf)
  end;

  XMS_acsGetDeviceList(g_gLobalVar.g_acsHandle,PravateData);
  result:=1;
//  CloseFile(f);
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
   InitSystem();
end;

procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
Var
  PriData:PrivateData_t;
begin
  FreeAllDeviceRes();
  FetchFromText();
	WriteToConfig();
  if nNeedCloseXms=1 then
  begin
    PriData.m_u32DataSize:=0;
    XMS_acsCloseStream(g_gLobalVar.g_acsHandle,PriData);
    FreeLibrary(DJApiHandle);
  end;
end;

Procedure TForm1.FetchFromText();
begin
  StrMove(g_gLobalVar.cfg_ServerID.m_s8ServerIp,PCHAR(Edit1.Text),Length(Edit1.Text)+1);
  g_gLobalVar.cfg_ServerID.m_u32ServerPort:=StrToInt(Edit2.Text);
  g_gLobalVar.cfg_iCalledLen:=StrToInt(Edit3.Text);
  StrMove(g_gLobalVar.cfg_CallingNum,PCHAR(Edit4.Text),Length(Edit4.Text)+1);
  if RadioButton1.Checked=True then
    begin
      g_gLobalVar.cfg_iCallOutRule:=0;
    end;
  if RadioButton2.Checked=True then
    begin
      g_gLobalVar.cfg_iCallOutRule:=1;
    end;
  if RadioButton3.Checked=True then
    begin
      g_gLobalVar.cfg_iCallOutRule:=2;
    end;
  StrMove(g_gLobalVar.cfg_SimCalledNum,PCHAR(Edit5.Text),Length(Edit5.Text)+1);

  if CheckBox2.Checked=true then
    begin
      g_gLobalVar.cfg_iPartWork:=1;
    end
  else
    begin
      g_gLobalVar.cfg_iPartWork:=0;
    end;
  g_gLobalVar.cfg_iPartWorkModuleID:=StrToInt(Edit6.Text);

  if CheckBox1.Checked=true then
    begin
      g_gLobalVar.cfg_s32DebugOn:=1;
    end
  else
    begin
      g_gLobalVar.cfg_s32DebugOn:=0;
    end;
end;

Procedure TForm1.WriteToConfig();
Var
  inifile:Tinifile;
begin
  g_gLobalVar.cfg_IniShortName:='.\XMS_Dial.INI';


    inifile:=Tinifile.Create(g_gLobalVar.cfg_IniShortName);

      begin
        inifile.WriteString('ConfigInfo','IpAddr',g_gLobalVar.cfg_ServerID.m_s8ServerIp);
        inifile.WriteInteger('ConfigInfo','Port',g_gLobalVar.cfg_ServerID.m_u32ServerPort);
        inifile.WriteInteger('ConfigInfo','CalledLen',g_gLobalVar.cfg_iCalledLen);
        inifile.WriteString('ConfigInfo','CallingNum',g_gLobalVar.cfg_CallingNum);

        inifile.WriteInteger('ConfigInfo','CallOutRule',g_gLobalVar.cfg_iCallOutRule);
        inifile.WriteString('ConfigInfo','SimCalledRNum',g_gLobalVar.cfg_SimCalledNum);

        inifile.WriteInteger('ConfigInfo','PartWork',g_gLobalVar.cfg_iPartWork);
        inifile.WriteInteger('ConfigInfo','PartWorkModuleID',g_gLobalVar.cfg_iPartWorkModuleID);
        inifile.WriteInteger('ConfigInfo','DebugOn',g_gLobalVar.cfg_s32DebugOn);
      end;
      inifile.Free;
end;


Procedure FreeAllDeviceRes();
Var
  i:integer;
begin
  for i:=0 to 255 do
    begin
      if g_gLobalVar.AllDeviceRes[i].pPcm <> nil then
        begin
          freemem(g_gLobalVar.AllDeviceRes[i].pPcm,sizeof(PCM_STRUCT)*g_gLobalVar.AllDeviceRes[i].lPcmNum);
        end;
      if g_gLobalVar.AllDeviceRes[i].pVoice <> nil then
        begin
          freemem(g_gLobalVar.AllDeviceRes[i].pVoice,sizeof(VOICE_STRUCT)*g_gLobalVar.AllDeviceRes[i].lVocNum);
        end;
      if g_gLobalVar.AllDeviceRes[i].pTrunk <> nil then
        begin
          freemem(g_gLobalVar.AllDeviceRes[i].pTrunk,sizeof(TRUNK_STRUCT)*g_gLobalVar.AllDeviceRes[i].lTrunkNum);
        end;

	    FillChar(g_gLobalVar.AllDeviceRes[i],sizeof(TYPE_XMS_DSP_DEVICE_RES_DEMO),0);

    end;

	g_gLobalVar.g_iTotalModule := 0;

	g_gLobalVar.g_iTotalPcm := 0;
	g_gLobalVar.g_iTotalPcmOpened := 0;

	g_gLobalVar.g_iTotalTrunk := 0;
	g_gLobalVar.g_iTotalTrunkOpened := 0;

	g_gLobalVar.g_iTotalUser := 0;
	g_gLobalVar.g_iTotalUserOpened := 0;

	g_gLobalVar.g_iTotalVoice := 0;
	g_gLobalVar.g_iTotalVoiceOpened := 0;
	g_gLobalVar.g_iTotalVoiceFree := 0;
end;

Procedure TForm1.ListView1AddItem(nNumOfItemToBeAdded:Integer);
Var
  i,j:Integer;
  ListItem:TListItem;
begin
  if ListView1.Items.Count = 0 then
  begin
      ListItem:=ListView1.Items.Add;
      ListItem.Caption:='Total';
      for j:=0 to 7 do
        begin
          ListItem.SubItems.Add('');
        end;
  end;

    for i:=ListView1.Items.Count to nNumOfItemToBeAdded do
    begin
      ListItem:=ListView1.Items.Add;
      ListItem.Caption:=IntToStr(i);
      for j:=0 to 7 do
        begin
          ListItem.SubItems.Add('');
        end;
    end;
end;

Procedure TForm1.ListView2AddItem(nNumOfItemToBeAdded:Integer);
Var
  i,j:Integer;
  ListItem:TListItem;
  nCount:integer;
begin
  nCount:=ListView2.Items.Count;
  for i:=0 to nNumOfItemToBeAdded-1 do
    begin
      ListItem:=ListView2.Items.Add;
      ListItem.Caption:=IntToStr(i+nCount);
      for j:=0 to 7 do
        begin
          ListItem.SubItems.Add('');
        end;
    end;
end;

Procedure TForm1.ListView3AddItem(nNumOfItemToBeAdded:Integer);
Var
  i,j:Integer;
  ListItem:TListItem;
  nCount:integer;
begin
  nCount:=ListView3.Items.Count;
  for i:=0 to nNumOfItemToBeAdded-1 do
    begin
      ListItem:=ListView3.Items.Add;
      ListItem.Caption:=IntToStr(i+nCount);
      for j:=0 to 6 do
        begin
          ListItem.SubItems.Add('');
        end;
    end;
end;

Procedure TForm1.ListView4AddItem(nNumOfItemToBeAdded:Integer);
Var
  i,j:Integer;
  ListItem:TListItem;
  nCount:integer;
begin
  nCount:=ListView4.Items.Count;
  for i:=0 to nNumOfItemToBeAdded-1 do
    begin
      ListItem:=ListView4.Items.Add;
      ListItem.Caption:=IntToStr(i+nCount);
      for j:=0 to 4 do
        begin
          ListItem.SubItems.Add('');
        end;
    end;
end;

procedure timerfun(handle:Thandle;msg:word;identer:word;dwtime:longword);stdcall;
begin
  SimulateCallOut();
end;

procedure TForm1.FormSimulate(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  //settimer(0,0,100,@timerfun);
  SimulateCallOut();
end;

Procedure SimulateCallOut();
Var
  FreeTrkDeviceID,FreeVocDeviceID:DeviceID_t;
  pLinkTrunk:^TRUNK_STRUCT;
  pLinkVoc:^VOICE_STRUCT;
  MsgStr,sCalled,sCalling:String;
  i,ret:Integer;
  PrivData:PrivateData_t;
begin
  pLinkTrunk:=nil;
  pLinkVoc:=nil;

  PrivData.m_u32DataSize:=0;
  i:=SearchOneFreeTrunk ( g_gLobalVar.cfg_SimCalledNum,FreeTrkDeviceID );
  if i>=0 then
      begin
        sCalled:=Form1.Edit5.Text;
        sCalling:=Form1.Edit4.Text;
        FillChar(g_gLobalVar.cfg_SimCalledNum,sizeof(g_gLobalVar.cfg_SimCalledNum),0);
        FillChar(g_gLobalVar.cfg_CallingNum,sizeof(g_gLobalVar.cfg_CallingNum),0);
        StrMove(g_gLobalVar.cfg_SimCalledNum,PCHAR(sCalled),Length(sCalled));
        StrMove(g_gLobalVar.cfg_CallingNum,PCHAR(sCalling),Length(sCalling));

        pLinkTrunk:=pointer(g_gLobalVar.AllDeviceRes[FreeTrkDeviceID.m_s8ModuleID].pTrunk);
        inc(pLinkTrunk,FreeTrkDeviceID.m_s16ChannelID);
        if (FreeTrkDeviceID.m_s16DeviceMain=smallint(XMS_DEVMAIN_INTERFACE_CH)) and
            (FreeTrkDeviceID.m_s16DeviceSub=smallint(XMS_DEVSUB_ANALOG_TRUNK)) then
          begin
            if  SearchOneFreeVoice(pLinkTrunk,FreeVocDeviceID) >= 0 then
              begin
                pLinkTrunk.VocDevID:=FreeVocDeviceID;
                pLinkVoc:=pointer(g_gLobalVar.AllDeviceRes[FreeVocDeviceID.m_s8ModuleID].pVoice);
                inc(pLinkVoc,FreeVocDeviceID.m_s16ChannelID);
                pLinkVoc.UsedDevID:=pLinkTrunk.deviceID;
                My_DualLink(FreeTrkDeviceID,FreeVocDeviceID);
                SetGtd_AnalogTrunk(FreeVocDeviceID);
              end
            else
              begin
                Showmessage('No VoiceDevice is Free!SearchOneFreeVoice Failed!');
                exit;
              end;
          end;
       ret:=XMS_ctsMakeCallOut(g_gLobalVar.g_acsHandle,FreeTrkDeviceID,pointer(@g_gLobalVar.cfg_CallingNum),pointer(@g_gLobalVar.cfg_SimCalledNum),PrivData);
       if ret>0 then
        begin
          DrawMain_LinkDev(pLinkTrunk);
          ZeroMemory(pointer(@pLinkTrunk.CallerCode),sizeof(pLinkTrunk.CallerCode));
          ZeroMemory(pointer(@pLinkTrunk.CallerCode),sizeof(pLinkTrunk.CalleeCode));
          StrMove(pLinkTrunk.CallerCode,g_gLobalVar.cfg_CallingNum,strlen(g_gLobalVar.cfg_CallingNum));
          StrMove(pLinkTrunk.CalleeCode,g_gLobalVar.cfg_SimCalledNum,strlen(g_gLobalVar.cfg_SimCalledNum));
          DrawMain_CallInfo ( pLinkTrunk );
          pLinkTrunk.State := TRK_SIM_CALLOUT;
          Change_State ( pLinkTrunk, TRK_SIM_CALLOUT );
        end
       else
        begin
          MsgStr:=Format('XMS_ctsMakeCallOut() FAIL! ret = %d', [ret]);
			    Form1.AddMsg ( MsgStr );
        end;

      end;
end;

Procedure SetGtd_AnalogTrunk(Var pDevId:DeviceID_t);
Var
  cmdVoc:CmdParamData_Voice_t;
  u16ParamType:Word;
  u16ParamSize:Word;
  ret:integer;
  Msg:string;
begin
  FillChar(cmdVoc,sizeof(CmdParamData_Voice_t),0);

  cmdVoc.m_u8GtdCtrlValid := 1 ; //Enable GTD
	cmdVoc.m_VocGtdControl.m_u8ChannelEnable := 1;//Enable Gtd channel
	cmdVoc.m_VocGtdControl.m_u8DTMFEnable := 1;
	cmdVoc.m_VocGtdControl.m_u8MR2FEnable := 1;
	cmdVoc.m_VocGtdControl.m_u8MR2BEnable := 1;
	cmdVoc.m_VocGtdControl.m_u8GTDEnable := 1;
	cmdVoc.m_VocGtdControl.m_u8FSKEnable := 1;

	cmdVoc.m_VocGtdControl.m_u8EXTEnable := 2;		// Enable PVD Detect
  cmdVoc.m_VocGtdControl.m_u8GTDID[0]:=Byte('G');
  cmdVoc.m_VocGtdControl.m_u8GTDID[1]:=Byte('H');
  cmdVoc.m_VocGtdControl.m_u8GTDID[2]:=Byte('I');
  cmdVoc.m_VocGtdControl.m_u8GTDID[3]:=Byte('J');
  cmdVoc.m_VocGtdControl.m_u8GTDID[4]:=Byte('K');

  u16ParamType := Word(VOC_PARAM_UNIPARAM);
	u16ParamSize := sizeof(cmdVoc);

  ret:=XMS_ctsSetParam(g_gLobalVar.g_acsHandle,pDevId,u16ParamType,u16ParamSize,pointer(@cmdVoc));

  Msg:=Format('Set GTD ret = %d', [ret]);
  Form1.AddMsg(Msg);
end;

function IsTrunk(s16DevSub:Smallint):Boolean;
begin
  if (s16DevSub = smallint(XMS_DEVSUB_E1_PCM)) or
     (s16DevSub = smallint(XMS_DEVSUB_E1_CAS)) or
     (s16DevSub = smallint(XMS_DEVSUB_E1_DSS1)) or
     (s16DevSub = smallint(XMS_DEVSUB_E1_SS7_TUP)) or
     (s16DevSub = smallint(XMS_DEVSUB_E1_SS7_ISUP)) or
     (s16DevSub = smallint(XMS_DEVSUB_ANALOG_TRUNK)) then
     begin
      result:=true;
      exit;
     end
  else
    begin
      result:=false;
      exit;
    end;
end;

function SearchOneFreeTrunk(pDtmf:Pchar;Var pFreeTrkDeviceID:DeviceID_t):integer;
Var
  i,iTmp:Integer;
  s8ModID:Shortint;
  s16ChID:Smallint;
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=nil;

  if g_gLobalVar.cfg_iCallOutRule=2 then
    begin
      iTmp:=StrToInt(pDtmf);
      iTmp:=iTmp mod 1000;

      s8ModID := g_gLobalVar.MapTable_Trunk[iTmp].m_s8ModuleID;
		  s16ChID := g_gLobalVar.MapTable_Trunk[iTmp].m_s16ChannelID;

      if iTmp >= g_gLobalVar.g_iTotalTrunk then
        begin
          result:=-1;
          exit;
        end;
      pOneTrunk:=pointer(g_gLobalVar.AllDeviceRes[s8ModID].pTrunk);
      inc(pOneTrunk,s16ChID);
      if (pOneTrunk.iLineState=integer(DCS_FREE)) and (IsTrunk(pOneTrunk.deviceID.m_s16DeviceSub)) then
        begin
          pFreeTrkDeviceID:=pOneTrunk.deviceID;
          result:=iTmp;
          exit;
        end;
      result:=-1;
      exit;
    end;

  if g_gLobalVar.cfg_iCallOutRule=0 then
    begin
      iLoopStartSearchFreeTrunk:=0;
    end;

  if g_gLobalVar.g_iTotalTrunk>0 then
    begin
      for i:=0 to g_gLobalVar.g_iTotalTrunk-1 do
        begin
          s8ModID := g_gLobalVar.MapTable_Trunk[iLoopStartSearchFreeTrunk].m_s8ModuleID;
		      s16ChID := g_gLobalVar.MapTable_Trunk[iLoopStartSearchFreeTrunk].m_s16ChannelID;
          pOneTrunk:=pointer(g_gLobalVar.AllDeviceRes[s8ModID].pTrunk);
          inc(pOneTrunk,s16ChID);
          if (pOneTrunk.iLineState=integer(DCS_FREE)) and (IsTrunk(pOneTrunk.deviceID.m_s16DeviceSub)) then
            begin
              pFreeTrkDeviceID:=pOneTrunk.deviceID;
              iTmp:=iLoopStartSearchFreeTrunk;
              iLoopStartSearchFreeTrunk:=(iLoopStartSearchFreeTrunk+1) mod g_gLobalVar.g_iTotalTrunk;
              result:=iTmp;
              exit;
            end;
          iLoopStartSearchFreeTrunk:=(iLoopStartSearchFreeTrunk+1) mod g_gLobalVar.g_iTotalTrunk;
        end;
    end;
    result:=-1;
end;

procedure TForm1.ReOpen_AllDevice(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
Var
  i:integer;
begin
  if g_gLobalVar.g_iTotalModule>0 then
    begin
	    for i := 0 to g_gLobalVar.g_iTotalModule-1 do
        begin
          OpenAllDevice_Dsp ( g_gLobalVar.MapTable_Module[i] );
        end;
    end;
end;

procedure TForm1.ExitDial(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  Self.Close;
end;

procedure TForm1.OnBtnRemove(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  Remove_OneDsp();
end;

Procedure Remove_OneDsp();
Var
  i:integer;
  nSelected:integer;
  s8DspModID:integer;
  pOneTrunk:^TRUNK_STRUCT;
  pOneVoice:^VOICE_STRUCT;
begin
  pOneTrunk:=nil;
  pOneVoice:=nil;

  if Form1.ListView1.SelCount<=0 then
    begin
      ShowMessage('Please select a valid DSP module in the upper list!');
      exit;
    end;

      nSelected:=Form1.ListView1.Selected.Index;
      if (nSelected<=0) or (nSelected>g_gLobalVar.g_iTotalModule) then
        begin
          ShowMessage('Please select a valid DSP module in the upper list!');
          exit;
        end;
      s8DspModID := g_gLobalVar.MapTable_Module[nSelected-1];		// because the first Row is Total, so minus 1
	    g_gLobalVar.AllDeviceRes[s8DspModID].RemoveState := DSP_REMOVE_STATE_START;
	    DrawCount_RemoveState ( s8DspModID );
      if g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum>0 then
        begin
          pOneTrunk:=pointer(g_gLobalVar.AllDeviceRes[s8DspModID].pTrunk);
          for i:=0 to g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum-1 do
            begin
              if pOneTrunk.State=TRK_FREE then
                Change_State ( pOneTrunk, TRK_WAIT_REMOVE );

              if pOneTrunk.deviceID.m_s16DeviceSub=smallint(XMS_DEVSUB_ANALOG_USER) then
                begin
                  if pOneTrunk.UserState=USER_FREE then
                    Change_UserState ( pOneTrunk, USER_WAIT_REMOVE );
                end;
              if i<>g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum-1 then
                inc(pOneTrunk);
            end;
        end;

      if g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum > 0 then
        begin
          pOneVoice:=pointer(g_gLobalVar.AllDeviceRes[s8DspModID].pVoice);
            for i:=0 to g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum-1 do
              begin
                Change_Voc_State ( pOneVoice, VOC_WAIT_REMOVE);

                if i<>g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum-1 then
                  inc(pOneVoice);
              end;
        end;
end;

end.
