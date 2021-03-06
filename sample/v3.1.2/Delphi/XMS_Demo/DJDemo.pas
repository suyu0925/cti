unit DJDemo;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, GlobalVal, StdCtrls, ComCtrls,Analog_Common_Code,inifiles,
  DJAcsDevState,XMS_Demo_Event,XMS_Demo_Sub,DJAcsDataDef,CAS_Common_Cfg,TDJAcsAPIDef,
  XMS_Demo_String;

type
  TForm1 = class(TForm)
    Panel1: TPanel;
    ListView1: TListView;
    ListView2: TListView;
    ListView3: TListView;
    ListBox1:  TListBox;

    Button1: TButton;
    Button2: TButton;
    Button3: TButton;

    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;

    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;

    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Edit6: TEdit;

    GroupBox1: TGroupBox;
    GroupBox2: TGroupBox;
    Config:    TGroupBox;

    RadioButton1: TRadioButton;
    RadioButton2: TRadioButton;
    RadioButton3: TRadioButton;
    RadioButton4: TRadioButton;
    RadioButton5: TRadioButton;
    RadioButton6: TRadioButton;


    procedure FormCreate(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure OnExit(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure OnPrepareRemove(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
  private
    { Private declarations }
  public
    { Public declarations }
    nNeedCloseXms:Integer;

    Function InitSystem():Byte;

    Procedure ReadIniFile();
    Procedure InitListMain();
    Procedure InitListPcm();
    Procedure InitListMsg();
    Procedure InitListCount();
    Procedure InitTextBox();
    Procedure FetchFromText();
    Procedure WriteToConfig();
    Procedure ListView1AddItem(nNumOfItemToBeAdded:Integer);
    Procedure ListView2AddItem(nNumOfItemToBeAdded:Integer);
    Procedure ListView3AddItem(nNumOfItemToBeAdded:Integer);
    Procedure AddMsg(msgBuf:String);
  end;

var
  Form1: TForm1;
  msgBuf:string;
  g_gLobalVar:Tglobal;

  procedure esr(esrParam:Longword);cdecl;
  Procedure DrawCount_RemoveState(s8ModID:Shortint);
  Procedure DrawCount_User(s8ModID:ShortInt);
  Procedure DrawCount_Pcm(s8ModID:Shortint);
  Procedure DrawCount_Voc(s8ModID:Shortint);
  Procedure DrawCount_Trunk(s8ModID:Shortint);
  Procedure	DrawMain_State(pTrunk:pointer);
  Procedure	DrawMain_CallInfo(pTrunk:pointer);
  Procedure DrawMain_DTMF(pTrunk:pointer);
  Procedure DrawCount_ErrFlag(s8ModID:shortint);
  Procedure DrawMain_LineState (pTrunk:pointer);
  Procedure DrawPcm_TypeAndAlarm(pPcm:Pointer);
  Procedure DrawMain_VocInfo(pTrunk:pointer);
  Procedure	ReDrawAll ();
  Procedure RefreshMapTable();
  Procedure DispEventInfo(AcsEvt:pointer);
  Procedure AddDeviceRes(AcsDevList:pointer);
  Procedure CloseDeviceOK(Var pDevice:DeviceID_t);
  Procedure AddDeviceRes_Voice(s8DspModID:Shortint;pAcsDevList:pointer);
  Procedure AddDeviceRes_Pcm  (s8DspModID:Shortint;pAcsDevList:pointer);
  Procedure AddDeviceRes_Trunk(s8DspModID:Shortint;pAcsDevList:pointer);
  Procedure AddDeviceRes_Board(s8DspModID:Shortint;pAcsDevList:pointer);
  Procedure Change_State(pTrunk:pointer;NewState:TRUNK_STATE);
  Procedure Change_Voc_State(pVoice:pointer;NewState:VOICE_STATE);
  Procedure CheckRemoveReady(s8DspModID:Shortint);
  Procedure OpenTrunkDevice(OneTrunk:pointer);
  Procedure OpenVoiceDevice(OneVoc:pointer);
  Procedure OpenPcmDevice(OnePcm:pointer);
  Procedure OpenBoardDevice(s8DspModID:Shortint);
  Procedure OpenAllDevice_Dsp(s8DspModID:Shortint);
  Procedure PrepareForCallerID(pTrunk:pointer);
  Procedure OpenDeviceOK(Var m_DeviceID:DeviceID_t);
  Procedure SetGTD_ToneParam(Var pDevice:DeviceID_t);
  Procedure InitTrunkChannel(pTrunk:pointer);
  Procedure My_InitDtmfBuf (OneTrunk:pointer);
  Procedure My_BuildIndex(Var pVocDevID:DeviceID_t);
  Procedure ResetTrunk (pTrunk:Pointer);
  Procedure My_DualUnlink(Var pDev1:DeviceID_t;Var pDev2:DeviceID_t);
  Procedure My_DualLink(Var pDev1:DeviceID_t;Var pDev2:DeviceID_t);
  Procedure HandleDevState(pEvt:pointer);
  Procedure StopPlayFile(Var pVocDevID:DeviceID_t);
  Procedure FreeOneFreeVoice(Dev:pointer);
  Procedure HandleMultiple(IDStr:Pchar);
  Procedure TrunkWork (pTrunk:pointer;pEvt:pointer);
  Procedure SpecialForCas (pTrunk:Pointer;pEvt:Pointer);
  Procedure ConvertRawFskToCallerID(RawFSKStr:Pchar; nFskLen:Integer; IDStr:pchar;IDStrBufLen:integer; pOneTrunk:Pointer);
  Procedure StopRecordFile(Var pVocDevID:DeviceID_t);
  Procedure RecordFile(Var pVocDevID:DeviceID_t;s8FileName:PCHAR;u32RecSize:Integer;bIsAppend:Boolean);
  Procedure PlayIndex(Var pVocDevID:DeviceID_t;u16Index:Word;u8PlayTag:Byte;bIsQueue:Boolean);
  Procedure My_AddDtmfBuf(pTrunk:pointer;TmpDtmf:char);
  Procedure PlayFile(Var pVocDevID:DeviceID_t;s8FileName:Pchar;u8PlayTag:Byte;bIsQueue:boolean);
  Procedure FreeAllDeviceRes();
  Procedure Remove_OneDsp();
  Procedure SetGtD_AnalogTrunk(Var pDevId:DeviceID_t);
  procedure My_GetFskCode(pEvt:pointer;pTrunk:pointer);

  function CheckRecordEnd (pEvt:pointer):Boolean;
  function My_GetGtdCode(pEvt:pointer):char;
  Function My_GetDtmfCode(pEvt:pointer):char;
  Function CheckPlayEnd(pTrunk:pointer;pEvt:pointer):Boolean;
  function CalDispRow(iSeqID:integer):integer;
  function GetBit(nSourData:Integer;nBit:Byte):Byte;
  function SearchOneFreeVoice(pTrunk:pointer;Var pFreeVocDeviceID:DeviceID_t):integer;

implementation
{$R *.dfm}

procedure esr(esrParam:Longword);cdecl;
Var
  pAcsEvt:^Acs_Evt_t;
  pAcsEvtTemp:^Acs_Evt_t;
  pAcsDevList:^Acs_Dev_List_Head_t;
  pDevID:^DeviceID_t;
  pOneTrunk:^TRUNK_STRUCT;
  pOneVoc:^VOICE_STRUCT;
  pAcsUnifailure:^Acs_UniFailure_Data;
begin
  pAcsEvt:=nil;
  pAcsEvtTemp:=nil;
  pAcsDevList:=nil;
  pDevID:=nil;
  pOneTrunk:=nil;
  pOneVoc:=nil;
  pAcsUnifailure:=nil;

  pAcsEvt:=Pointer(esrParam);
  pAcsEvtTemp:=pointer(pAcsEvt);
  DispEventInfo(pAcsEvt); //结构体或者类函数传参时都以地址传送
  case pAcsEvt.m_s32EventType of

  integer(XMS_EVT_QUERY_ONE_DSP_START):
    begin
      Form1.ListView1AddItem(g_gLobalVar.AllDeviceRes[pAcsEvt.m_DeviceID.m_s8ModuleID].iSeqID + 1);
    end;

  integer(XMS_EVT_QUERY_DEVICE) :
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
      OpenDeviceOK ( pAcsEvt.m_DeviceID );
    end;

  integer(XMS_EVT_CLOSE_DEVICE):
    begin
      CloseDeviceOK ( pAcsEvt.m_DeviceID );
    end;

  integer(XMS_EVT_DEVICESTATE):
    begin
      HandleDevState(pAcsEvt);
    end;

  integer(XMS_EVT_OPEN_STREAM):
    begin
      Form1.nNeedCloseXms:=1;
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

  else
    begin
     if pAcsEvt.m_DeviceID.m_s16DeviceMain=Smallint(XMS_DEVMAIN_INTERFACE_CH) then
      begin
        pOneTrunk:=pointer(g_gLobalVar.AllDeviceRes[pAcsEvt.m_DeviceID.m_s8ModuleID].pTrunk);
        inc(pOneTrunk, pAcsEvt.m_DeviceID.m_s16ChannelID);
        TrunkWork(pOneTrunk, pAcsEvt );
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
                TrunkWork (pOneTrunk, pAcsEvt );
              end;
        end;
    end;

  end;
end;

Procedure TrunkWork (pTrunk:pointer;pEvt:pointer);
Var
  pOneTrunk:^TRUNK_STRUCT;
  pOneVoice:^VOICE_STRUCT;
  pAcsEvt:^Acs_Evt_t;
  pCallControl:^Acs_CallControl_Data;
  FreeVocDeviceID:DeviceID_t;
  FileName:string;
  TmpDtmf,TmpGtd:char;
  privateData:PrivateData_t;
begin
  pOneTrunk:=nil;
  pOneVoice:=nil;
  pAcsEvt:=nil;
  pCallControl:=nil;

  pOneTrunk:=pointer(pTrunk);
  pAcsEvt:=pointer(pEvt);

  if (pOneTrunk=nil) or (pAcsEvt=nil) then exit;
  privateData.m_u32DataSize:=0;

  if pAcsEvt.m_s32EventType=integer(XMS_EVT_CLEARCALL) then
    begin
      if (pOneTrunk.State<>TRK_FREE) and (pOneTrunk.State <> TRK_WAIT_REMOVE) then
        begin
          ResetTrunk(pOneTrunk);
          exit;
        end;
    end;

  if pOneTrunk.deviceID.m_s16DeviceSub=Smallint(XMS_DEVSUB_ANALOG_TRUNK) then
    begin
      TmpGtd := My_GetGtdCode ( pAcsEvt );

      if TmpGtd<>char(-1) then
        begin
          if (TmpGtd = 'I') or (TmpGtd = 'J') or (TmpGtd = 'K') then
            begin
              XMS_ctsResetDevice(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID,privateData);
              XMS_ctsClearCall(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID,0,privateData);
              ResetTrunk(pOneTrunk);
            end;
        end;
    end;

  case pOneTrunk.State of

    TRK_FREE:
      begin
        SpecialForCas(pOneTrunk,pAcsEvt);
        if pOneTrunk.deviceID.m_s16DeviceSub=Smallint(XMS_DEVSUB_ANALOG_TRUNK) then
          begin
            My_GetFskCode(pAcsEvt, pOneTrunk);
          end;

        if pAcsEvt.m_s32EventType=integer(XMS_EVT_CALLIN) then
        begin
          if pOneTrunk.deviceID.m_s16DeviceSub = Smallint(XMS_DEVSUB_ANALOG_TRUNK) then
            begin
              My_DualUnlink ( pOneTrunk.VocDevID, pOneTrunk.deviceID );
              FreeOneFreeVoice ( pointer(@pOneTrunk.VocDevID) );
              pOneVoice:=pointer(g_gLobalVar.AllDeviceRes[pOneTrunk.VocDevID.m_s8ModuleID].pVoice);
              inc(pOneVoice,pOneTrunk.VocDevID.m_s16ChannelID);
              FillChar(pOneVoice.UsedDevID,sizeof(DeviceID_t),0);
              FillChar(pOneTrunk.VocDevID,sizeof(DeviceID_t),0);
              DrawMain_VocInfo ( pOneTrunk );
            end;
          inc(pAcsEvt);
          pCallControl:=pointer(pAcsEvt);
          XMS_ctsAlertCall(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID,privateData);
          XMS_ctsAnswerCallIn(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID,privateData);

          if pOneTrunk.deviceID.m_s16DeviceSub <> Smallint(XMS_DEVSUB_ANALOG_TRUNK) then
            begin
              StrMove(pOneTrunk.CalleeCode,pCallControl.m_s8CalledNum,strlen(pCallControl.m_s8CalledNum));
              StrMove(pOneTrunk.CallerCode,pCallControl.m_s8CallingNum,strlen(pCallControl.m_s8CallingNum));
				      pOneTrunk.CalleeCode[strlen(pCallControl.m_s8CalledNum)]:=char(0);
              pOneTrunk.CallerCode[strlen(pCallControl.m_s8CallingNum)]:=char(0);
            end;
          DrawMain_CallInfo( pOneTrunk );
          Change_State (pOneTrunk, TRK_WAIT_ANSWERCALL);

        end;
     end;

    TRK_WAIT_ANSWERCALL:
      begin
        SpecialForCas(pOneTrunk,pAcsEvt);

        if pAcsEvt.m_s32EventType=integer(XMS_EVT_ANSWERCALL) then
          begin
            if SearchOneFreeVoice (pOneTrunk,FreeVocDeviceID) >= 0 then
              begin
                pOneTrunk.u8PlayTag := 16;
				        pOneTrunk.VocDevID := FreeVocDeviceID;
                pOneVoice:=pointer(g_gLobalVar.AllDeviceRes[FreeVocDeviceID.m_s8ModuleID].pVoice);
                inc(pOneVoice,FreeVocDeviceID.m_s16ChannelID);
                pOneVoice.UsedDevID:=pOneTrunk.deviceID;
                DrawMain_VocInfo ( pOneTrunk );
                My_DualLink ( pOneTrunk.VocDevID, pOneTrunk.deviceID );
                if pOneTrunk.deviceID.m_s16DeviceSub = Smallint(XMS_DEVSUB_ANALOG_TRUNK) then
                  begin
                    SetGtD_AnalogTrunk(pOneTrunk.VocDevID);
                  end;
                Change_State ( pOneTrunk, TRK_WAIT_LINKOK );
              end;
          end;
      end;

    TRK_WAIT_LINKOK:
      begin
        if pAcsEvt.m_s32EventType = integer(XMS_EVT_LINKDEVICE) then
          begin
            FileName:=Format('%s',[g_gLobalVar.cfg_VocPath]);
            FileName:=FileName+'\bank.001';
            inc(pOneTrunk.u8PlayTag);
            PlayFile(pOneTrunk.VocDevID,PCHAR(FileName),pOneTrunk.u8PlayTag,False);
            Change_State ( pOneTrunk, TRK_WELCOME );
          end;
      end;

    TRK_WELCOME:
      begin
        if CheckPlayEnd ( pOneTrunk, pAcsEvt)=True then
          begin
            FileName:=Format('%s',[g_gLobalVar.cfg_VocPath]);
            FileName:=FileName+'\bank.002';
            inc(pOneTrunk.u8PlayTag);
            PlayFile(pOneTrunk.VocDevID,pchar(FileName),pOneTrunk.u8PlayTag,False);
            Change_State ( pOneTrunk, TRK_ACCOUNT );
          end;

        TmpDtmf := My_GetDtmfCode ( pAcsEvt );
        if TmpDtmf <>char(-1) then
          begin
            My_AddDtmfBuf ( pOneTrunk, TmpDtmf );
		      	DrawMain_DTMF ( pOneTrunk );

			      StopPlayFile ( pOneTrunk.VocDevID );

			      Change_State ( pOneTrunk, TRK_ACCOUNT );
          end;
      end;

    TRK_ACCOUNT:
      begin
        TmpDtmf := My_GetDtmfCode ( pAcsEvt );

        if TmpDtmf<>char(-1) then
          begin
            My_AddDtmfBuf ( pOneTrunk, TmpDtmf );
			      DrawMain_DTMF ( pOneTrunk );

			      StopPlayFile ( pOneTrunk.vocDevID );

            if pOneTrunk.DtmfCount >= 8 then
              begin
                FileName:=Format('%s',[g_gLobalVar.cfg_VocPath]);
                FileName:=FileName+'\bank.003';
                inc(pOneTrunk.u8PlayTag);
                PlayFile ( pOneTrunk.VocDevID, Pchar(FileName), pOneTrunk.u8PlayTag, False );
                My_InitDtmfBuf ( pOneTrunk );
				        Change_State ( pOneTrunk, TRK_PASSWORD );
              end;
          end;
      end;

    TRK_PASSWORD:
      begin
        TmpDtmf := My_GetDtmfCode ( pAcsEvt );
		    if TmpDtmf <> char(-1) then
          begin
            My_AddDtmfBuf ( pOneTrunk, TmpDtmf );
			      DrawMain_DTMF ( pOneTrunk );

			      StopPlayFile ( pOneTrunk.VocDevID );

            if pOneTrunk.DtmfCount >= 6 then
              begin
                FileName:=Format('%s',[g_gLobalVar.cfg_VocPath]);
                FileName:=FileName+'\bank.004';
                inc(pOneTrunk.u8PlayTag);
                PlayFile ( pOneTrunk.VocDevID, pchar(FileName), pOneTrunk.u8PlayTag, False );
                My_InitDtmfBuf ( pOneTrunk );
				        Change_State ( pOneTrunk, TRK_SELECT );
              end;
          end;
      end;

    TRK_SELECT:
      begin
        TmpDtmf := My_GetDtmfCode ( pAcsEvt );
		    if TmpDtmf = char(-1) then
			    exit;

        My_AddDtmfBuf ( pOneTrunk, TmpDtmf );
        DrawMain_DTMF ( pOneTrunk );

        inc(pOneTrunk.u8PlayTag);
        FileName:=Format('%s',[g_gLobalVar.cfg_VocPath]);

        case TmpDtmf of
          '1':
            begin
              StopPlayFile ( pOneTrunk.VocDevID );

				      FileName:=Format('%s', [g_gLobalVar.cfg_VocPath] );
				      FileName:=FileName+'\bank.005';
				      PlayFile ( pOneTrunk.VocDevID, pchar(FileName), pOneTrunk.u8PlayTag, true );

				      PlayIndex ( pOneTrunk.VocDevID, 5, pOneTrunk.u8PlayTag, true );
				      PlayIndex ( pOneTrunk.VocDevID, 12, pOneTrunk.u8PlayTag, true );
				      PlayIndex ( pOneTrunk.VocDevID, 8, pOneTrunk.u8PlayTag, true );
				      PlayIndex ( pOneTrunk.VocDevID, 11, pOneTrunk.u8PlayTag, true );
				      PlayIndex ( pOneTrunk.VocDevID, 9, pOneTrunk.u8PlayTag, true );
				      PlayIndex ( pOneTrunk.VocDevID, 10, pOneTrunk.u8PlayTag, true );
				      PlayIndex ( pOneTrunk.VocDevID, 15, pOneTrunk.u8PlayTag, true );
				      PlayIndex ( pOneTrunk.VocDevID, 8, pOneTrunk.u8PlayTag, true );

				      PlayIndex ( pOneTrunk.VocDevID, 16, pOneTrunk.u8PlayTag, true );		// bank.008

				      Change_State ( pOneTrunk, TRK_PLAYRESULT );
            end;
          '2':
            begin
				      StopPlayFile ( pOneTrunk.VocDevID );

              FileName:=Format('%s', [g_gLobalVar.cfg_VocPath]);
              FileName:=FileName+'\bank.006';

				      PlayFile ( pOneTrunk.VocDevID, pchar(FileName), pOneTrunk.u8PlayTag, true );

				      PlayIndex ( pOneTrunk.VocDevID, 0, pOneTrunk.u8PlayTag, true );
				      PlayIndex ( pOneTrunk.VocDevID, 15, pOneTrunk.u8PlayTag, true );
				      PlayIndex ( pOneTrunk.VocDevID, 4, pOneTrunk.u8PlayTag, true );
				      PlayIndex ( pOneTrunk.VocDevID, 8, pOneTrunk.u8PlayTag, true );

				      FileName:=Format('%s', [g_gLobalVar.cfg_VocPath]);
              FileName:=FileName+'\bank.008';
				      PlayFile ( pOneTrunk.VocDevID, pchar(FileName), pOneTrunk.u8PlayTag, true );

				      Change_State ( pOneTrunk, TRK_PLAYRESULT );
            end;

          '3':
            begin
              StopPlayFile ( pOneTrunk.VocDevID );

              FileName:=Format('%s', [g_gLobalVar.cfg_VocPath]);
              FileName:=FileName+'\bank.007';

				      PlayFile ( pOneTrunk.VocDevID, pchar(FileName), pOneTrunk.u8PlayTag, true );

              FileName:=Format('%s', [g_gLobalVar.cfg_VocPath]);
              FileName:=FileName+'\D3';
				      PlayFile ( pOneTrunk.VocDevID, pchar(FileName), pOneTrunk.u8PlayTag, true );

              FileName:=Format('%s', [g_gLobalVar.cfg_VocPath]);
              FileName:=FileName+'\D13';
				      PlayFile ( pOneTrunk.VocDevID, pchar(FileName), pOneTrunk.u8PlayTag, true );

              FileName:=Format('%s', [g_gLobalVar.cfg_VocPath]);
              FileName:=FileName+'\D7';
				      PlayFile ( pOneTrunk.VocDevID, pchar(FileName), pOneTrunk.u8PlayTag, true );

              FileName:=Format('%s', [g_gLobalVar.cfg_VocPath]);
              FileName:=FileName+'\D12';
				      PlayFile ( pOneTrunk.VocDevID, pchar(FileName), pOneTrunk.u8PlayTag, true );

			        FileName:=Format('%s', [g_gLobalVar.cfg_VocPath]);
              FileName:=FileName+'\bank.008';
				      PlayFile ( pOneTrunk.VocDevID, pchar(FileName), pOneTrunk.u8PlayTag, true );

			        Change_State ( pOneTrunk, TRK_PLAYRESULT );
            end;
          '4':
            begin
              StopPlayFile ( pOneTrunk.VocDevID );

			        FileName:=Format('%s\DemoRec.%03d', [g_gLobalVar.cfg_VocPath, pOneTrunk.iSeqID] );
			        RecordFile ( pOneTrunk.VocDevID, pchar(FileName), 8000*10, false );

			        Change_State ( pOneTrunk, TRK_RECORDFILE );
            end;
        end;
      end;

    TRK_PLAYRESULT:
      begin
		    if CheckPlayEnd ( pOneTrunk, pAcsEvt)=True then
          begin
            XMS_ctsClearCall(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID,0,privateData);
            Change_State ( pOneTrunk, TRK_HANGON );
          end;
		  end;

	  TRK_PLAYRECORD:
      begin
		    if CheckPlayEnd ( pOneTrunk, pAcsEvt)=True then
          begin
            XMS_ctsClearCall(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID,0,privateData);
            Change_State ( pOneTrunk, TRK_HANGON );
          end;
		  end;

    TRK_RECORDFILE:
      begin
		    TmpDtmf := My_GetDtmfCode ( pAcsEvt );
		    if TmpDtmf <> char(-1) then
          begin
            My_AddDtmfBuf ( pOneTrunk, TmpDtmf );
			      DrawMain_DTMF ( pOneTrunk );
            StopRecordFile ( pOneTrunk.VocDevID );
          end;


		    if  CheckRecordEnd (pAcsEvt)=True then
		      begin
			      inc(pOneTrunk.u8PlayTag);

			      FileName:=Format('%s\DemoRec.%03d', [g_gLobalVar.cfg_VocPath, pOneTrunk.iSeqID] );
			      PlayFile ( pOneTrunk.VocDevID, pchar(FileName), pOneTrunk.u8PlayTag,False);

			      Change_State ( pOneTrunk, TRK_PLAYRECORD );
		     end;
     end;

  end;
end;

Procedure SetGtD_AnalogTrunk(Var pDevId:DeviceID_t);
Var
  cmdVoc:CmdParamData_Voice_t;
  u16ParamType:Word;
  u16ParamSize:Word;
  szbuffer:string;
  ret:integer;
begin
  FillChar(cmdVoc,sizeof(CmdParamData_Voice_t),0);
  cmdVoc.m_u8GtdCtrlValid := 1 ;						//Enable GTD
	cmdVoc.m_VocGtdControl.m_u8ChannelEnable := 1;		//Enable Gtd channel
	cmdVoc.m_VocGtdControl.m_u8DTMFEnable := 1;			// Detect DTMF
	cmdVoc.m_VocGtdControl.m_u8GTDEnable := 1;			// Detect GTD
	cmdVoc.m_VocGtdControl.m_u8FSKEnable := 1;			// Detect FSK for receive CallerID

	cmdVoc.m_VocGtdControl.m_u8EXTEnable := 2;		// Enable PVD Detect
  cmdVoc.m_VocGtdControl.m_u8GTDID[0]:=Byte('G');
  cmdVoc.m_VocGtdControl.m_u8GTDID[1]:=Byte('H');
  cmdVoc.m_VocGtdControl.m_u8GTDID[2]:=Byte('I');
  cmdVoc.m_VocGtdControl.m_u8GTDID[3]:=Byte('J');
  cmdVoc.m_VocGtdControl.m_u8GTDID[4]:=Byte('K');

  u16ParamType := Word(VOC_PARAM_UNIPARAM);
	u16ParamSize := sizeof(CmdParamData_Voice_t);
  ret:=XMS_ctsSetParam(g_gLobalVar.g_acsHandle,pDevId,u16ParamType,u16ParamSize,pointer(@cmdVoc));
  szbuffer:=Format('Set GTD ret = %d',[ret]);
  Form1.AddMsg ( szbuffer );
end;

function	CheckRecordEnd (pEvt:pointer):Boolean;
Var
  pAcsEvt:^Acs_Evt_t;
begin
  pAcsEvt:=pointer(pEvt);
  if pAcsEvt=nil then
  begin
    result:=False;
    exit;
  end;
  if pAcsEvt.m_s32EventType = integer(XMS_EVT_RECORD) then
    begin
      result:=True;
      exit;
    end;
	result:=False;
end;


Procedure StopRecordFile(Var pVocDevID:DeviceID_t);
Var
  controlRecord:ControlRecord_t;
  priData:PrivateData_t;
begin
  priData.m_u32DataSize:=0;
  FillChar(controlRecord,sizeof(ControlRecord_t),0);
  controlRecord.m_u32ControlType := integer(XMS_STOP_RECORD);
  XMS_ctsControlRecord(g_gLobalVar.g_acsHandle,pVocDevID,controlRecord,priData);
end;

Procedure RecordFile(Var pVocDevID:DeviceID_t;s8FileName:PCHAR;u32RecSize:Integer;bIsAppend:Boolean);
Var
  recordProperty:RecordProperty_t;
  priData:PrivateData_t;
begin
  FillChar(recordProperty,sizeof(RecordProperty_t),0);
  priData.m_u32DataSize:=0;

  recordProperty.m_u32MaxSize := u32RecSize;

  if bIsAppend=True then
    begin
      recordProperty.m_s8IsAppend := 1;
    end
  else
    begin
      recordProperty.m_s8IsAppend := 0;
    end;

  StrMove(recordProperty.m_s8FileName,s8FileName,strlen(s8FileName));

  XMS_ctsRecord(g_gLobalVar.g_acsHandle,pVocDevID,recordProperty,priData);

end;

Procedure PlayIndex(Var pVocDevID:DeviceID_t;u16Index:Word;u8PlayTag:Byte;bIsQueue:Boolean);
Var
  playProperty:PlayProperty_t;
  priData:PrivateData_t;
begin
  FillChar(playProperty,sizeof(PlayProperty_t),0);
  priData.m_u32DataSize:=0;
  if bIsQueue=True then
    begin
      playProperty.m_u16PlayType := Word(XMS_PLAY_TYPE_INDEX_QUEUE);
    end
  else
    begin
      playProperty.m_u16PlayType := Word(XMS_PLAY_TYPE_INDEX);
    end;
  playProperty.m_u8TaskID := u8PlayTag;
  playProperty.m_u16PlayIndex := u16Index;

  XMS_ctsPlay( g_gLobalVar.g_acsHandle, pVocDevID, playProperty, priData );
end;

Procedure My_AddDtmfBuf(pTrunk:pointer;TmpDtmf:char);
Var
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then exit;
  if pOneTrunk.DtmfCount < 31 then
    begin
      pOneTrunk.DtmfBuf[pOneTrunk.DtmfCount]:=TmpDtmf;
		  pOneTrunk.DtmfBuf[pOneTrunk.DtmfCount+1]:=char(0);
		  inc(pOneTrunk.DtmfCount);
    end;
end;

Function My_GetDtmfCode(pEvt:pointer):char;
Var
  pAcsEvt:^Acs_Evt_t;
  pIOData:^Acs_IO_Data;
  p:Pchar;
begin
  pAcsEvt:=nil;
  pIOData:=nil;

  pAcsEvt:=pointer(pEvt);
  if pAcsEvt=nil then
    begin
      result:=char(-1);
      exit;
    end;
  if pAcsEvt.m_s32EventType = integer(XMS_EVT_RECVIODATA) then
    begin
      inc(pAcsEvt);
      pIOData:=pointer(pAcsEvt);

      if (pIOData.m_u16IoType=Word(XMS_IO_TYPE_DTMF)) and (pIOData.m_u16IoDataLen>0) then
        begin
          inc(pIOData);
          p:=pointer(pIOData);
          result:=p[0];
          exit;
        end;
    end;
  result:=char(-1);
end;

Function CheckPlayEnd(pTrunk:pointer;pEvt:pointer):Boolean;
Var
  pOneTrunk:^TRUNK_STRUCT;
  pAcsEvt:^Acs_Evt_t;
  pMediaData:^Acs_MediaProc_Data;
begin
  pOneTrunk:=nil;
  pAcsEvt:=nil;
  pMediaData:=nil;

  pAcsEvt:=pointer(pEvt);
  pOneTrunk:=pointer(pTrunk);

  if (pAcsEvt=nil) or (pOneTrunk=nil) then
  begin
    result:=False;
    exit;
  end;
  if pAcsEvt.m_s32EventType=integer(XMS_EVT_PLAY) then
    begin
      inc(pAcsEvt);
      pMediaData:=pointer(pAcsEvt);

      if pMediaData.m_u8TaskID=pOneTrunk.u8PlayTag then
        begin
          result:=True;
          exit;
        end;
    end;
  result:=False;
end;


Procedure PlayFile(Var pVocDevID:DeviceID_t;s8FileName:Pchar;u8PlayTag:Byte;bIsQueue:boolean);
Var
  playProperty:PlayProperty_t;
  priData:PrivateData_t;
begin
  priData.m_u32DataSize:=0;
  FillChar(playProperty,sizeof(PlayProperty_t),0);
  if bIsQueue=True then
    begin
      playProperty.m_u16PlayType := Word(XMS_PLAY_TYPE_FILE_QUEUE);
    end
  else
    begin
      playProperty.m_u16PlayType := Word(XMS_PLAY_TYPE_FILE);
    end;

  playProperty.m_u8TaskID := u8PlayTag;

  StrMove(playProperty.m_s8PlayContent,s8FileName,strlen(s8FileName));

  XMS_ctsPlay( g_gLobalVar.g_acsHandle, pVocDevID, playProperty, priData );
end;

Procedure ConvertRawFskToCallerID(RawFSKStr:Pchar; nFskLen:Integer; IDStr:pchar;IDStrBufLen:integer; pOneTrunk:Pointer);
Var
  count,i,j,pos,len:integer;
  ChkSum:Byte;
  ch:Byte;
begin

  if 0 >= nFskLen then exit;

  count := nFskLen;

  for i:=0 to IDStrBufLen-1 do
     IDStr[i] := char(0);

    RawFSKStr[count] := char(0);

  for i:=0 to count-1 do
    begin
      ch:=Byte(RawFSKStr[i]);
      if ch=4 then break;
      if ch=128 then break;
    end;

      if (i=count) or (i=count-1) then exit;

      pos:=i;
      len:=integer(RawFSKStr[pos+1]);

      if len > IDStrBufLen then
        len := IDStrBufLen;

      i:=pos+2;
      j:=0;

      if (i<count-1) and (len>0) then
      begin
        for j:=0 to len-1 do
          begin
            if i<(count-1) then
              begin
                IDStr[j]:=char(integer(RawFSKStr[i]) and integer(127));
                if j=IDStrBufLen - 1 then break;
                inc(i);
              end;
          end;
      end;
      IDStr[j] := char(0);

      if (count-pos-3) < len  then exit;

      ChkSum := 0;
      for i:=pos to pos+len+3 do
        ChkSum := ChkSum+Byte(RawFSKStr[i]);

      if RawFSKStr[pos] = char(128) then
        HandleMultiple ( IDStr );
end;

Procedure HandleMultiple(IDStr:Pchar);
Var
  i:integer;
  p:Pchar;
  TmpIDStr:Array[0..79] of char;
  c:char;
begin
  p := IDStr;
  FillChar(TmpIDStr,sizeof(TmpIDStr),0);
  i:=0;
  while p^ <> char(0) do
    begin
      c:=p^;
      if (c=char(1)) or (c=char(2)) or (c=char(3)) or (c=char(4)) or(c=char(5)) then
        begin
          inc(p,2);
        end
      else
        begin
          TmpIDStr[i] := p^;
          inc(i);
          inc(p);
        end;
  end;

  TmpIDStr[i] := char(0);
  StrMove(IDStr,TmpIDStr,strlen(TmpIDStr));
  IDStr[strlen(TmpIDStr)]:=char(0);
end;

procedure My_GetFskCode(pEvt:pointer;pTrunk:pointer);
Var
  pIOData:^Acs_IO_Data;
  pAcsEvt:^Acs_Evt_t;
  pTempEvt:^Acs_Evt_t;
  pOneTrunk:^TRUNK_STRUCT;
  nFskDataLen:Integer;
  p:PChar;
  iDispRow:Integer;
  StateStr:String;
  
begin
  pIOData:=nil;
  pAcsEvt:=nil;

  pAcsEvt:=pointer(pEvt);
  pTempEvt:=pointer(pAcsEvt);
  pOneTrunk:=pointer(pTrunk);

  if pAcsEvt=nil then
  begin
    exit;
  end;

  if pAcsEvt.m_s32EventType=integer(XMS_EVT_RECVIODATA) then
    begin
      inc(pTempEvt);
      pIOData:=pointer(pTempEvt);
      nFskDataLen:=pIOData.m_u16IoDataLen;

      if (pIOData.m_u16IoType=Word(XMS_IO_TYPE_FSK)) and (pIOData.m_u16IoDataLen>0) then
        begin
          inc(pIOData);
          ConvertRawFskToCallerID(PChar(pIOData), nFskDataLen, pOneTrunk.CallerCode, 20, pOneTrunk);
          //StrMove(pOneTrunk.CallerCode, PChar(pIOData), nFskDataLen);
        end;

      if (pIOData.m_u16IoType=Word(XMS_IO_TYPE_DTMF)) and (pIOData.m_u16IoDataLen>0) then
        begin
          inc(pIOData);
          p:=PChar(pIOData);

          if (p[0] = 'D') or (p[0] = 'd') then
          begin
            g_gLobalVar.g_dtmfIndex := 0;
          end
          else if (p[0] = 'C') or (p[0] = 'c') then
          begin
            FillChar(pOneTrunk.CallerCode, 20, 0);
          end
          else if (p[0] >= '0') or (p[0] <= '9') then
          begin
            pOneTrunk.CallerCode[g_gLobalVar.g_dtmfIndex] := p[0];
            inc(g_gLobalVar.g_dtmfIndex);
            pOneTrunk:=pointer(pTrunk);

            iDispRow := CalDispRow(pOneTrunk.iSeqID);
	          if iDispRow<0	then exit;

	          StateStr:=pOneTrunk.CallerCode;

            Form1.ListView2.Items.Item[iDispRow].Subitems.Strings[5]:=StateStr;
          end;
        end;
    end;
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

  if (pOneTrunk=nil) or (pAcsEvt=nil) then exit;

  if pOneTrunk.deviceID.m_s16DeviceSub<>Smallint(XMS_DEVSUB_E1_CAS) then
    begin
      exit;
    end;

  if pAcsEvt.m_s32EventType=integer(XMS_EVT_CAS_MFC_START) then
    begin
      if SearchOneFreeVoice(pOneTrunk,FreeVocDeviceID) >= 0 then
        begin
          My_DualLink (FreeVocDeviceID,pOneTrunk.deviceID);
          pOneTrunk.VocDevID:=FreeVocDeviceID;
          pOneVoice:=pointer(g_gLobalVar.AllDeviceRes[FreeVocDeviceID.m_s8ModuleID].pVoice);
          inc(pOneVoice,FreeVocDeviceID.m_s16ChannelID);
          pOneVoice.UsedDevID:=pOneTrunk.deviceID;
          DrawMain_VocInfo ( pOneTrunk );
          g_gLobalVar.g_Param_CAS.m_VocDevID:=FreeVocDeviceID;
          XMS_ctsSetParam(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID,Word(CAS_PARAM_UNIPARAM),sizeof(CmdParamData_CAS_t),pointer(@g_gLobalVar.g_Param_CAS));
        end;
    end;

    if pAcsEvt.m_s32EventType=integer(XMS_EVT_CAS_MFC_END) then
      begin
        My_DualUnlink(pOneTrunk.VocDevID,pOneTrunk.deviceID );
        FreeOneFreeVoice (@pOneTrunk.VocDevID);
        pOneVoice:=pointer(g_gLobalVar.AllDeviceRes[pOneTrunk.VocDevID.m_s8ModuleID].pVoice);
        inc(pOneVoice,pOneTrunk.VocDevID.m_s16ChannelID);
        FillChar(pOneVoice.UsedDevID,sizeof(DeviceID_t),0);
        FillChar(pOneTrunk.VocDevID,sizeof(DeviceID_t),0);
        DrawMain_VocInfo ( pOneTrunk );
      end;
end;

function My_GetGtdCode(pEvt:pointer):char;
Var                                                                                       
  pIOData:^Acs_IO_Data;                                                                   
  p:PChar;
  pAcsEvt:^Acs_Evt_t;
  pTmpAcsEvt:^Acs_Evt_t;
begin
  pAcsEvt:=nil;                                                                           
  pIOData:=nil;                                                                           
                                                                                          
  pAcsEvt:=pointer(pEvt);
  pTmpAcsEvt:=pointer(pAcsEvt);

  if pAcsEvt=nil then
    begin                                                                                 
      result:=char(-1);                                                                   
      exit;                                                                               
    end;                                                                                  
  if pAcsEvt.m_s32EventType=integer(XMS_EVT_RECVIODATA) then
    begin                                                                                 
      inc(pTmpAcsEvt);
      pIOData:=pointer(pTmpAcsEvt);

      if (pIOData.m_u16IoType=Word(XMS_IO_TYPE_GTG)) and (pIOData.m_u16IoDataLen > 0) then
        begin
          inc(pIOData);
          p:=pointer(pIOData);
          result:=p[0];
          exit;                                                                           
        end;                                                                              
    end;                                                                                  
  result:=char(-1);
end;                                                                                      


Procedure ResetTrunk (pTrunk:Pointer);
Var
  pOneTrunk:^TRUNK_STRUCT;
  pOneVoc:^VOICE_STRUCT;
begin
  pOneTrunk:=nil;
  pOneVoc:=nil;

  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then exit;
  StopPlayFile(pOneTrunk.VocDevID);

  if pOneTrunk.VocDevID.m_s16DeviceMain <> 0 then
    begin
      My_DualUnlink(pOneTrunk.VocDevID, pOneTrunk.deviceID);
      FreeOneFreeVoice (@pOneTrunk.VocDevID);
      pOneVoc:=pointer(g_gLobalVar.AllDeviceRes[pOneTrunk.VocDevID.m_s8ModuleID].pVoice);
      inc(pOneVoc,pOneTrunk.VocDevID.m_s16ChannelID);

      FillChar(pOneVoc.UsedDevID,sizeof(DeviceID_t),0);
      FillChar(pOneTrunk.VocDevID,sizeof(DeviceID_t),0);

      DrawMain_VocInfo ( pOneTrunk );
    end;

  InitTrunkChannel(pOneTrunk);
  PrepareForCallerID(pOneTrunk);
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
  if pFreeVocDeviceID=nil then exit;
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

Procedure StopPlayFile(Var pVocDevID:DeviceID_t);
Var
  controlPlay:ControlPlay_t;
  priData:PrivateData_t;
begin
  priData.m_u32DataSize:=0;
  FillChar(controlPlay,sizeof(ControlPlay_t),0);
  controlPlay.m_u16ControlType:=Word(XMS_STOP_PLAY);
  XMS_ctsControlPlay(g_gLobalVar.g_acsHandle,pVocDevID,controlPlay,priData);
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
  if pAcsEvt=nil then exit;
  pTempEvt:=pointer(pEvt);
  inc(pTempEvt);
  pGeneralData:=pointer(pTempEvt);

  if pAcsEvt.m_DeviceID.m_s16DeviceMain=Smallint(XMS_DEVMAIN_INTERFACE_CH) then
    begin
      pOneTrunk:=pointer(g_gLobalVar.AllDeviceRes[pAcsEvt.m_DeviceID.m_s8ModuleID].pTrunk);
      inc(pOneTrunk,pAcsEvt.m_DeviceID.m_s16ChannelID);

      pOneTrunk.iLineState := pGeneralData.m_s32DeviceState;
		  DrawMain_LineState( pOneTrunk );
    end;

  if pAcsEvt.m_DeviceID.m_s16DeviceMain=Smallint(XMS_DEVMAIN_DIGITAL_PORT) then
    begin
      pOnePcm:=pointer(g_gLobalVar.AllDeviceRes[pAcsEvt.m_DeviceID.m_s8ModuleID].pPcm);
      inc(pOnePcm,pAcsEvt.m_DeviceID.m_s16ChannelID);
      pOnePcm.u8E1Type := (pGeneralData.m_s32DeviceState shr 16) and 255;
      pOnePcm.s32AlarmVal := (pGeneralData.m_s32DeviceState and 65535);
      DrawPcm_TypeAndAlarm ( pOnePcm );
    end;

end;

Procedure My_InitDtmfBuf (OneTrunk:pointer);
Var
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=nil;
  pOneTrunk:=pointer(OneTrunk);
  if pOneTrunk=nil then exit;
  pOneTrunk.DtmfCount:=0;
  //FillChar(pOneTrunk.DtmfBuf,32,0);

  pOneTrunk.DtmfBuf[0]:=char(0);
end;

Procedure InitTrunkChannel(pTrunk:pointer);
Var
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then exit;
  Change_State ( pOneTrunk, TRK_FREE );

  pOneTrunk.CallerCode[0]:=char(0);
	pOneTrunk.CalleeCode[0]:=char(0);

  My_InitDtmfBuf ( pOneTrunk );
  DrawMain_DTMF ( pOneTrunk );

  FillChar(pOneTrunk.VocDevID, 0, sizeof(DeviceID_t));
  DrawMain_VocInfo ( pOneTrunk );
end;

Procedure OpenDeviceOK(Var m_DeviceID:DeviceID_t);
Var
  pOneTrunk:^TRUNK_STRUCT;
  pOneVoice:^VOICE_STRUCT;
  pOnePcm:^PCM_STRUCT;
  privateData:PrivateData_t;
  pParamData:pointer;
  cmdAnalogTrunk:CmdParamData_AnalogTrunk_t;
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
      g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].bOpenFlag:=True;
      SetGTD_ToneParam(m_DeviceID);
    end;

  if m_DeviceID.m_s16DeviceMain=Smallint(XMS_DEVMAIN_INTERFACE_CH) then
    begin
      pOneTrunk:=pointer(g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].pTrunk);
      inc(pOneTrunk, m_DeviceID.m_s16ChannelID);
      pOneTrunk.deviceID.m_CallID:=m_DeviceID.m_CallID;

          InitTrunkChannel(pOneTrunk);
          XMS_ctsResetDevice(g_gLobalVar.g_acsHandle,m_DeviceID,privateData);
          XMS_ctsGetDevState(g_gLobalVar.g_acsHandle,m_DeviceID,privateData);

      inc(g_gLobalVar.g_iTotalTrunkOpened);
      inc(g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].lTrunkOpened);
      DrawCount_Trunk (m_DeviceID.m_s8ModuleID);

      if pOneTrunk.deviceID.m_s16DeviceSub=Smallint(XMS_DEVSUB_ANALOG_TRUNK) then
        begin
			    u16ParamType:=word(ANALOGTRUNK_PARAM_UNIPARAM);
			    u16ParamSize:=sizeof(CmdParamData_AnalogTrunk_t);

          FillChar(cmdAnalogTrunk,sizeof(cmdAnalogTrunk),0);

			    cmdAnalogTrunk.m_u16CallInRingCount := 3;
			    cmdAnalogTrunk.m_u16CallInRingTimeOut := 6000; //6 seconds

			    pParamData := pointer(@cmdAnalogTrunk);

          ret:=XMS_ctsSetParam(g_gLobalVar.g_acsHandle,pOneTrunk.deviceID,u16ParamType,u16ParamSize,pParamData);

			    szbuffer:=Format('Set AnalogTrunk  ret = %d\n',[ret]);
		    	Form1.AddMsg (szbuffer);

          PrepareForCallerID ( pOneTrunk );
        end

    end;

    if m_DeviceID.m_s16DeviceMain= Smallint(XMS_DEVMAIN_VOICE) then
      begin
        pOneVoice:=pointer(g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].pVoice);
        inc(pOneVoice,m_DeviceID.m_s16ChannelID);
        pOneVoice.deviceID.m_CallID := m_DeviceID.m_CallID;
        Change_Voc_State (pOneVoice, VOC_FREE);

        XMS_ctsResetDevice(g_gLobalVar.g_acsHandle,m_DeviceID,privateData);
        XMS_ctsGetDevState(g_gLobalVar.g_acsHandle,m_DeviceID,privateData);

        if g_gLobalVar.g_iTotalVoiceOpened=0 then
          begin
            My_BuildIndex(m_DeviceID);
          end;

        inc(g_gLobalVar.g_iTotalVoiceOpened);
        inc(g_gLobalVar.g_iTotalVoiceFree);
		    inc(g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].lVocOpened);
		    inc(g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].lVocFreeNum);
        DrawCount_Voc (m_DeviceID.m_s8ModuleID);
      end;

    if m_DeviceID.m_s16DeviceMain = Smallint(XMS_DEVMAIN_DIGITAL_PORT) then
      begin
        pOnePcm:=pointer(g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].pPcm);
        inc(pOnePcm,m_DeviceID.m_s16ChannelID);
        pOnePcm.bOpenFlag:=True;
        pOnePcm.deviceID.m_CallID := m_DeviceID.m_CallID;

        XMS_ctsResetDevice(g_gLobalVar.g_acsHandle,m_DeviceID,privateData);
        XMS_ctsGetDevState(g_gLobalVar.g_acsHandle,m_DeviceID,privateData);
        DrawPcm_TypeAndAlarm (pOnePcm);

        inc(g_gLobalVar.g_iTotalPcmOpened);
		    inc(g_gLobalVar.AllDeviceRes[m_DeviceID.m_s8ModuleID].lPcmOpened);

        DrawCount_Pcm (m_DeviceID.m_s8ModuleID);
      end;
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

Procedure PrepareForCallerID(pTrunk:pointer);
Var
  pOneTrunk:^TRUNK_STRUCT;
  pOneVoc:^VOICE_STRUCT;
  FreeVocDeviceID:DeviceID_t;
begin
  pOneTrunk:=nil;
  pOneVoc:=nil;

  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then exit;

  if pOneTrunk.deviceID.m_s16DeviceSub <> Smallint(XMS_DEVSUB_ANALOG_TRUNK) then exit;

  if SearchOneFreeVoice ( pOneTrunk, FreeVocDeviceID ) >= 0 then
    begin
		  pOneTrunk.VocDevID := FreeVocDeviceID;
      pOneVoc:=pointer(g_gLobalVar.AllDeviceRes[FreeVocDeviceID.m_s8ModuleID].pVoice);
      inc(pOneVoc,FreeVocDeviceID.m_s16ChannelID);
      pOneVoc.UsedDevID:=pOneTrunk.deviceID;

		  DrawMain_VocInfo ( pOneTrunk );

		  My_DualLink ( FreeVocDeviceID, pOneTrunk.deviceID );
		  SetGtD_AnalogTrunk(FreeVocDeviceID);
	  end;
end;

Procedure My_DualLink(Var pDev1:DeviceID_t;Var pDev2:DeviceID_t);
Var
  PriData:PrivateData_t;
begin
  PriData.m_u32DataSize:=0;
  XMS_ctsLinkDevice(g_gLobalVar.g_acsHandle,pDev1,pDev2,PriData);
  XMS_ctsLinkDevice(g_gLobalVar.g_acsHandle,pDev2,pDev1,PriData);
end;

Procedure My_DualUnlink(Var pDev1:DeviceID_t;Var pDev2:DeviceID_t);
Var

  PriData:PrivateData_t;
begin
  PriData.m_u32DataSize:=0;
  XMS_ctsUnlinkDevice(g_gLobalVar.g_acsHandle,pDev1,pDev2,PriData);
  XMS_ctsUnlinkDevice(g_gLobalVar.g_acsHandle,pDev2,pDev1,PriData);
end;

function SearchOneFreeVoice(pTrunk:pointer;Var pFreeVocDeviceID:DeviceID_t):integer;
Var
  pOneTrunk:^TRUNK_STRUCT;
  pOneVoice:^VOICE_STRUCT;
  s8SearchModID,s8ModID:Shortint;
  i,lNowMostFreeNum:Integer;
  s16ChID:Smallint;
begin
  pOneTrunk:=nil;
  pOneVoice:=nil;

  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then
  begin
    result:=-1;
    exit;
  end;
  s8ModID:=pOneTrunk.deviceID.m_s8ModuleID;
  if g_gLobalVar.cfg_iVoiceRule=0 then
    begin
      s16ChID:=pOneTrunk.deviceID.m_s16ChannelID;
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
          if pOneVoice.state=VOC_FREE then
            begin
              pFreeVocDeviceID:=pOneVoice.deviceID;
              Change_Voc_State( pOneVoice, VOC_USED);
              dec(g_gLobalVar.AllDeviceRes[s8SearchModID].lVocFreeNum);
			        dec(g_gLobalVar.g_iTotalVoiceFree);
			        DrawCount_Voc ( s8SearchModID );
			        result:=i;
              exit;
            end;
        end;
    end;

  result:=-1;
end;

Procedure DrawMain_VocInfo(pTrunk:pointer);
Var
  iDispRow:integer;
  StateStr:string;
  pDev:^DeviceID_t;
  pOneTrunk:^TRUNK_STRUCT;
begin
  pDev:=nil;
  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then exit;
  iDispRow := CalDispRow(pOneTrunk.iSeqID);
  if iDispRow < 0	then exit;

  if pOneTrunk.VocDevID.m_s16DeviceMain <> 0 then
	  begin
		  pDev := pointer(@pOneTrunk.VocDevID);
		  StateStr:=Format('%d,%d', [pDev.m_s8ModuleID, pDev.m_s16ChannelID] );
	  end
  else
    begin
      StateStr:='';
    end;

  Form1.ListView2.Items.Item[iDispRow].SubItems.Strings[7]:=StateStr;
end;

Procedure My_BuildIndex(Var pVocDevID:DeviceID_t);
Var
  FileName,MsgStr:string;
  playProperty:PlayProperty_t;
  ret,i:integer;
  priData:PrivateData_t;
begin
  priData.m_u32DataSize:=0;
  FillChar(playProperty,sizeof(PlayProperty_t),0);
  ret:=XMS_ctsInitPlayIndex(g_gLobalVar.g_acsHandle,pVocDevID,priData);

  if ret<0 then
    begin
      MsgStr:=Format('XMS_ctsInitPlayIndex() FAIL. ret = %d', [ret]);
      Form1.AddMsg(MsgStr);
      exit;
    end;

  for i:=0 to 16 do
    begin
      if i=16 then
        begin
          playProperty.m_u16PlayType := WORD(XMS_BUILD_INDEX_FILE);
          FileName:=g_gLobalVar.cfg_VocPath+'\bank.008';
        end
      else
        begin
          playProperty.m_u16PlayType := WORD(XMS_BUILD_INDEX_RAM);
          FileName:=Format('%s\D%d',[g_gLobalVar.cfg_VocPath,i]);
        end;

      StrMove(playProperty.m_s8PlayContent,PCHAR(FileName),Length(FileName));

      ret := XMS_ctsBuildPlayIndex( g_gLobalVar.g_acsHandle, pVocDevID, playProperty, priData );
      if ret < 0 then
        begin
          MsgStr:=Format('XMS_ctsBuildPlayIndex(%s) FAIL. ret = %d', [FileName, ret]);
          Form1.AddMsg(MsgStr);
        end;
    end;
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

	    DrawMain_LineState ( pOneTrunk );
		  DrawMain_State ( pOneTrunk );
		  DrawMain_CallInfo (pOneTrunk );
      DrawMain_DTMF(pOneTrunk);
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

Procedure DrawPcm_TypeAndAlarm(pPcm:Pointer);
Var
  pOnePcm:^PCM_STRUCT;
  StateStr:string;
  iDispRow,AlarmVal:Integer;
Begin
  pOnePcm:=nil;

  pOnePcm:=pointer(pPcm);
  if pOnePcm=nil then exit;
  iDispRow:=pOnePcm.iSeqID;
  AlarmVal:=pOnePcm.s32AlarmVal;

  StateStr:=GetString_PcmType(pOnePcm.u8E1Type);
  Form1.ListView3.Items.Item[iDispRow].SubItems.Strings[0]:=StateStr;

  StateStr:=Format('0X%x',[AlarmVal]);
  Form1.ListView3.Items.Item[iDispRow].SubItems.Strings[1]:=StateStr;

  if GetBit(AlarmVal, 0)=1 then
    begin
      Form1.ListView3.Items.Item[iDispRow].SubItems.Strings[2]:='X';
    end
  else
    begin
      Form1.ListView3.Items.Item[iDispRow].SubItems.Strings[2]:='O';
    end;

  if GetBit(AlarmVal, 1)=1 then
    begin
      Form1.ListView3.Items.Item[iDispRow].SubItems.Strings[3]:='X';
    end
  else
    begin
      Form1.ListView3.Items.Item[iDispRow].SubItems.Strings[3]:='O';
    end;

  if GetBit(AlarmVal, 4)=1 then
    begin
      Form1.ListView3.Items.Item[iDispRow].SubItems.Strings[4]:='X';
    end
  else
    begin
      Form1.ListView3.Items.Item[iDispRow].SubItems.Strings[4]:='O';
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

Procedure DrawMain_LineState (pTrunk:pointer);
Var
  StateStr:string;
  iDispRow:Integer;
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=nil;

  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then exit;
	iDispRow := CalDispRow(pOneTrunk.iSeqID);
	if iDispRow < 0 then exit;

	StateStr:=GetString_LineState(pOneTrunk.iLineState);
  Form1.ListView2.Items.Item[iDispRow].Subitems.Strings[2]:=StateStr;
end;

Procedure DrawMain_DTMF(pTrunk:pointer);
Var
  pOneTrunk:^TRUNK_STRUCT;
  StateStr:string;
  iDispRow:integer;
begin
  pOneTrunk:=nil;

  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then exit;
  iDispRow := CalDispRow(pOneTrunk.iSeqID);
	if iDispRow < 0 then exit;
  StateStr:=pOneTrunk.DtmfBuf;
  Form1.ListView2.Items.Item[iDispRow].SubItems.Strings[6]:=StateStr;
end;

Procedure	DrawMain_CallInfo(pTrunk:pointer);
Var
  StateStr:string;
  iDispRow:Integer;
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=nil;

  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then exit;
  iDispRow := CalDispRow(pOneTrunk.iSeqID);
	if iDispRow<0	then exit;
  pOneTrunk:=pointer(pTrunk);

	StateStr:=pOneTrunk.CalleeCode;
  Form1.ListView2.Items.Item[iDispRow].Subitems.Strings[4]:=StateStr;

	StateStr:=pOneTrunk.CallerCode;
  Form1.ListView2.Items.Item[iDispRow].Subitems.Strings[5]:=StateStr;
end;

Procedure RefreshMapTable();
Var
  i,j:Integer;
  TrkCount, VocCount, PcmCount, ModuleCount:Integer;
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

                if pTrunk.deviceID.m_s16DeviceSub <> Smallint(XMS_DEVSUB_UNUSABLE) then
                  begin
                    pTrunk.iModSeqID:=iModSeqID;
                    inc(iModSeqID);
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
  if pOneVoice=nil then exit;
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
  if pOnePcm=nil then exit;
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
  if pOneTrunk=nil then exit;
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

Procedure Change_State(pTrunk:pointer;NewState:TRUNK_STATE);
Var
  pOneTrunk:^TRUNK_STRUCT;
begin
  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then exit;
  pOneTrunk.State:=NewState;
  DrawMain_State(pOneTrunk);

  if (REMOVE_STATE(g_gLobalVar.AllDeviceRes[pOneTrunk.deviceID.m_s8ModuleID].RemoveState)=DSP_REMOVE_STATE_START)
     and (NewState=TRK_FREE) then
  begin
     pOneTrunk.State := TRK_WAIT_REMOVE;
     DrawMain_State(pOneTrunk);
     CheckRemoveReady( pOneTrunk.deviceID.m_s8ModuleID );
  end;
end;

Procedure	DrawMain_State(pTrunk:pointer);
Var
  pOneTrunk:^TRUNK_STRUCT;
  StateStr:string;
  iDispRow:integer;
begin
  pOneTrunk:=nil;

  pOneTrunk:=pointer(pTrunk);
  if pOneTrunk=nil then exit;

  iDispRow := CalDispRow(pOneTrunk.iSeqID);
  if iDispRow < 0 then exit;
  pOneTrunk:=pointer(pTrunk);

  case pOneTrunk.State of
    TRK_WAITOPEN: StateStr:='Wait Open';
    TRK_FREE:     StateStr:='Free';
    TRK_WELCOME:  StateStr:='Welcome to DonJin Keygo Bank Demo';
    TRK_ACCOUNT:  StateStr:='Please input your acount';
    TRK_PASSWORD: StateStr:='Please input your password';
    TRK_SELECT:   StateStr:='Please select function';
    TRK_RECORDFILE:    StateStr:='Record';
    TRK_PLAYRESULT: StateStr:='Play result';
    TRK_PLAYRECORD: StateStr:='Play Back';
    TRK_WAIT_ANSWERCALL:      StateStr:='Wait offhook ok';
    TRK_WAIT_LINKOK:  StateStr:='Wait Link ok';
    TRK_WAIT_REMOVE:        StateStr:='Remove DSP';
  end;
  Form1.ListView2.Items.Item[iDispRow].Subitems.Strings[3]:=StateStr;
end;

function CalDispRow(iSeqID:integer):integer;
Var
  iRet:integer;
begin
  if g_gLobalVar.cfg_iDispChnl=30 then
    begin
      if iSeqID mod 16=0 then
        begin
          result:=-1;
          exit;
        end;
      iRet := (iSeqID div 32) * 30 + (iSeqID mod 32);
      dec(iRet);
      if ( (iSeqID mod 32) > 16 ) then
			  dec(iRet);
		  result:= iRet;
      exit;
    end;

  if g_gLobalVar.cfg_iDispChnl=31 then
    begin
      if iSeqID mod 32=0 then
        begin
          result:=-1;
          exit;
        end;
      iRet := (iSeqID div 32) * 31 + (iSeqID mod 32);
		  dec(iRet);
		  result:=iRet;
      exit;
    end;
    
  result:=iSeqID;
end;

Procedure CheckRemoveReady(s8DspModID:Shortint);
Var
  i:Integer;
  pTrunkStr:^TRUNK_STRUCT;
  pVocStr:^VOICE_STRUCT;
begin
  pTrunkStr:=nil;
  pVocStr:=nil;

  pTrunkStr:=pointer(g_gLobalVar.AllDeviceRes[s8DspModID].pTrunk);
  pVocStr:=pointer(g_gLobalVar.AllDeviceRes[s8DspModID].pVoice);
  if g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum>0 then
    begin
      for i:=0 to g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum -1 do
      begin
        if(pTrunkStr.State <> TRK_WAITOPEN) and (pTrunkStr.State <> TRK_WAIT_REMOVE) then
          begin
            exit;
          end;
        if i <> g_gLobalVar.AllDeviceRes[s8DspModID].lTrunkNum -1 then
          begin
            inc(pTrunkStr);
          end;
      end;
    end;


  if g_gLobalVar.AllDeviceRes[s8DspModID].lVocNum>0 then
    begin
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
//  Form1.ListView1AddItem(iDispRow);
  Form1.ListView1.Items.Item[iDispRow].SubItems.Strings[6]:=TmpStr;
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

Procedure Change_Voc_State(pVoice:pointer;NewState:VOICE_STATE);
Var
  pOneVoice:^VOICE_STRUCT;
begin
  pOneVoice:=nil;

  pOneVoice:=pointer(pVoice);
  if pOneVoice=nil then exit;
  pOneVoice.State:=NewState;
  if (g_gLobalVar.AllDeviceRes[pOneVoice.deviceID.m_s8ModuleID].RemoveState=DSP_REMOVE_STATE_START) And (NewState=VOC_FREE) then
  begin
    pOneVoice.State:=VOC_WAIT_REMOVE;
    CheckRemoveReady (pOneVoice.deviceID.m_s8ModuleID);
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

Procedure DrawCount_User(s8ModID:ShortInt);
Var
  TmpStr:string;
Begin
  TmpStr:=Format('%3d/%3d',[g_gLobalVar.g_iTotalUser, g_gLobalVar.g_iTotalUserOpened]);
  Form1.ListView1.Items.Item[0].SubItems.Strings[5]:=TmpStr;
end;

Procedure AddDeviceRes(AcsDevList:pointer);
Var
  pAcsDevList:^Acs_Dev_List_Head_t;
  s8DspModID:Shortint;
begin
  pAcsDevList:=nil;
  pAcsDevList:= pointer(AcsDevList);
  if pAcsDevList=nil then exit;
  s8DspModID:=Shortint(pAcsDevList.m_s32ModuleID);
  if (s8DspModID < 0) or (s8DspModID > 255) then
  begin
    exit;
  end;
  case pAcsDevList.m_s32DeviceMain of
  integer(XMS_DEVMAIN_VOICE): AddDeviceRes_Voice(s8DspModID, pAcsDevList);
  integer(XMS_DEVMAIN_DIGITAL_PORT): AddDeviceRes_Pcm(s8DspModID, pAcsDevList);
  integer(XMS_DEVMAIN_INTERFACE_CH): AddDeviceRes_Trunk(s8DspModID, pAcsDevList);
  integer(XMS_DEVMAIN_BOARD): AddDeviceRes_Board(s8DspModID, pAcsDevList);
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
  PcmDevList:=pAcsDevList;
  if PcmDevList=nil then exit;
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
  Form1.ListView3AddItem(g_gLobalVar.AllDeviceRes[s8DspModID].lPcmNum);
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

  TrunkDevList:=pAcsDevList;
  if TrunkDevList=nil then exit;
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

  PboardDevList:=pAcsDevList;
  if PboardDevList=nil then exit;
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
  if VocDevList=nil then exit;
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

Procedure DispEventInfo(AcsEvt:pointer);
var
  TmpS:string;
  TmpStr:string;
  pAcsEvt:^Acs_Evt_t;
  pAcsTempEvt:^Acs_Evt_t;
  pAcsDevList:^Acs_Dev_List_Head_t;
  pAcsUniFailure:^Acs_UniFailure_Data;
  pIoData:^ACS_IO_Data;
begin
  pAcsEvt:=nil;
  pAcsTempEvt:=nil;
  pAcsDevList:=nil;
  pAcsUniFailure:=nil;

  pAcsEvt:=pointer(AcsEvt);
  if pAcsEvt=nil then
    begin
      exit;
    end;
  pAcsTempEvt:=pointer(pAcsEvt);

  TmpStr:=Format('EVT(%4d) : ',[pAcsEvt.m_s32EvtSize]);
  TmpStr:=ConCat(TmpStr, GetString_EventType(pAcsEvt.m_s32EventType));

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
      TmpS:=format(': %s(0x%X) dev=(%s, %d, %d)',
                    [GetString_ErrorCode(pAcsUniFailure.m_s32AcsEvtErrCode),pAcsUniFailure.m_s32AcsEvtErrCode,GetString_DeviceMain(pAcsEvt.m_DeviceID.m_s16DeviceMain),
                     pAcsEvt.m_DeviceID.m_s8ModuleID,pAcsEvt.m_DeviceID.m_s16ChannelID]);

       TmpStr:=conCat(TmpStr, TmpS);
    end;

    else
      begin
        Tmps:=Format(' Dev=(%s,%d,%d)',[GetString_DeviceMain(pAcsEvt.m_DeviceID.m_s16DeviceMain),
                     pAcsEvt.m_DeviceID.m_s8ModuleID,pAcsEvt.m_DeviceID.m_s16ChannelID]);
        TmpStr:=conCat(TmpStr,Tmps);
      end;
  end;
  Form1.AddMsg(TmpStr);
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  InitSystem();
end;

Procedure TForm1.AddMsg(msgBuf:string); //给ListBox添加消息
var
  Msg:String;
Begin
  Msg:=Format('%4d: ',[g_gLobalVar.g_NumOfListBox]);
  Msg:=Msg+msgBuf;

  if g_gLobalVar.g_NumOfListBox=5000 then
    begin
      ListBox1.Clear;
      g_gLobalVar.g_NumOfListBox:=1;
    end;

  ListBox1.Items.Add(Msg);
  inc(g_gLobalVar.g_NumOfListBox);
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
  Item.Caption:='DTMF';
  Item.Width:=60;

	Item:=ListView2.Columns.Add;
  Item.Caption:='VocInfo';
  Item.Width:=70;
end;

Procedure TForm1.InitListPcm();
var
  Item:TListColumn;
begin
  Item:=ListView3.Columns.Add;
  Item.Caption:='PcmID';
  Item.Width:=60;

  Item:=ListView3.Columns.Add;
  Item.Caption:='Type';
  Item.Width:=80;

  Item:=ListView3.Columns.Add;
  Item.Caption:='Alarm Value';
  Item.Width:=80;

	Item:=ListView3.Columns.Add;
  Item.Caption:='Sig Detect';
  Item.Width:=80;

	Item:=ListView3.Columns.Add;
  Item.Caption:='Frame Sync';
  Item.Width:=80;

	Item:=ListView3.Columns.Add;
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
  Item.Caption:='ErrFlag';
  Item.Width:=60;

	Item:=ListView1.Columns.Add;
  Item.Caption:='RemoveState';
  Item.Width:=80;
end;

Procedure Tform1.InitTextBox();
begin
  if g_gLobalVar.cfg_iDispChnl=30 then
    begin
      RadioButton1.Checked:=True;
    end
  else if g_gLobalVar.cfg_iDispChnl=31 then
    begin
      RadioButton2.Checked:=True;
    end
  else if g_gLobalVar.cfg_iDispChnl=32 then
    begin
      RadioButton3.Checked:=True;
    end;

  if g_gLobalVar.cfg_iVoiceRule=0 then
    begin
      RadioButton4.Checked:=True;
    end
  else if g_gLobalVar.cfg_iVoiceRule=1 then
    begin
      RadioButton5.Checked:=True;
    end
  else
    begin
      RadioButton6.Checked:=True;
    end;

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

Function TForm1.InitSystem():Byte;
Var
  ret:Integer;
  PravateData:PrivateData_t;
  MsgStr:string;
begin
  Fillchar(g_gLobalVar,sizeof(Tglobal),0);
  g_gLobalVar.g_u8UnitID:=2;
  g_gLobalVar.g_NumOfListBox:=1;
  PravateData.m_u32DataSize:=0;
  g_gLobalVar.g_acsHandle:=0;
  g_gLobalVar.cfg_iDispChnl:=32;
  ZeroMemory(pointer(@g_gLobalVar.cfg_CallingNum),sizeof(g_gLobalVar.cfg_CallingNum));
  ZeroMemory(pointer(@g_gLobalVar.cfg_SimCalledNum),sizeof(g_gLobalVar.cfg_SimCalledNum));

  ReadIniFile();

  if CAS_Common_Cfg_ReadCfg (g_gLobalVar.g_Param_CAS) <> 0 then
    begin
		  MsgStr:='CAS_Common_Cfg_ReadCfg \"C:\\DJKeygoe\\Samples\\Delphi\\CAS_Common_Code\\XMS_CAS_Cfg.INI\" Error!';
		  ShowMessage(MsgStr);
  	end;

  if Analog_Common_Cfg_ReadCfg(g_gLobalVar.g_Param_Analog) <> 0 then
    begin
      MsgStr:='Analog_Common_Cfg_ReadCfg \"C:\\DJKeygoe\\Samples\\Delphi\\Analog_Common_Code\\XMS_Analog_Cfg.INI\" Error!';
		  ShowMessage(MsgStr);
    end;

  InitListMain();
  InitListPcm();
  InitListMsg();
  InitListCount();
  InitTextBox();

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
end;

Procedure TForm1.ReadIniFile();
Var
  inifile:Tinifile;
  tempStr:string;

begin
  g_gLobalVar.cfg_IniShortName:='.\XMS_Demo.INI';
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

  tempStr:=inifile.ReadString('ConfigInfo','VocPath','..\VOC\');
  strpCopy(g_gLobalVar.cfg_VocPath, tempStr);
  Edit3.Text:=g_gLobalVar.cfg_VocPath;

  g_gLobalVar.cfg_iDispChnl:=inifile.ReadInteger('ConfigInfo','DispChnl',32);
  g_gLobalVar.cfg_iVoiceRule:=inifile.ReadInteger('ConfigInfo','VoiceRule',0);

  g_gLobalVar.cfg_iPartWork:=inifile.ReadInteger('ConfigInfo','PartWork',0);
  g_gLobalVar.cfg_iPartWorkModuleID:=inifile.ReadInteger('ConfigInfo','PartWorkModuleID',0);
  g_gLobalVar.cfg_s32DebugOn:=inifile.ReadInteger('ConfigInfo','DebugOn',0);
  inifile.Free;
end;

Procedure TForm1.ListView1AddItem(nNumOfItemToBeAdded:Integer);
Var
  i,j:Integer;
  ListItem:TListItem;
begin
  ListView1.items.clear;
  ListItem:=ListView1.Items.Add;
  ListItem.Caption:='Total';
  for j:=0 to 7 do
    begin
      ListItem.SubItems.Add('');
    end;

  for i:=0 to nNumOfItemToBeAdded-1 do
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
//  ListView3.items.clear;
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

Procedure TForm1.FetchFromText();
begin
  StrMove(g_gLobalVar.cfg_ServerID.m_s8ServerIp,PCHAR(Edit1.Text),Length(Edit1.Text)+1);
  g_gLobalVar.cfg_ServerID.m_u32ServerPort:=StrToInt(Edit2.Text);
  StrMove(g_gLobalVar.cfg_VocPath,PCHAR(Edit3.Text),Length(Edit3.Text)+1);
  if RadioButton1.Checked=True then
    begin
      g_gLobalVar.cfg_iDispChnl:=30;
    end;
  if RadioButton2.Checked=True then
    begin
      g_gLobalVar.cfg_iDispChnl:=31;
    end;
  if RadioButton3.Checked=True then
    begin
      g_gLobalVar.cfg_iDispChnl:=32;
    end;

  if RadioButton4.Checked=True then
    begin
     g_gLobalVar.cfg_iVoiceRule:=0;
    end
  else if RadioButton5.Checked=True then
    begin
      g_gLobalVar.cfg_iVoiceRule:=1;
    end
  else
    begin
      g_gLobalVar.cfg_iVoiceRule:=2;
    end;

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
  g_gLobalVar.cfg_IniShortName:='.\XMS_Demo.INI';


    inifile:=Tinifile.Create(g_gLobalVar.cfg_IniShortName);

      begin
        inifile.WriteString('ConfigInfo','IpAddr',g_gLobalVar.cfg_ServerID.m_s8ServerIp);
        inifile.WriteInteger('ConfigInfo','Port',g_gLobalVar.cfg_ServerID.m_u32ServerPort);
        inifile.WriteString('ConfigInfo','VocPath',g_gLobalVar.cfg_VocPath);

        inifile.WriteInteger('ConfigInfo','DispChnl',g_gLobalVar.cfg_iDispChnl);
        inifile.WriteInteger('ConfigInfo','VoiceRule',g_gLobalVar.cfg_iVoiceRule);

        inifile.WriteInteger('ConfigInfo','PartWork',g_gLobalVar.cfg_iPartWork);
        inifile.WriteInteger('ConfigInfo','PartWorkModuleID',g_gLobalVar.cfg_iPartWorkModuleID);
        inifile.WriteInteger('ConfigInfo','DebugOn',g_gLobalVar.cfg_s32DebugOn);
      end;
      inifile.Free;

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

	g_gLobalVar.g_iTotalVoice := 0;
	g_gLobalVar.g_iTotalVoiceOpened := 0;
	g_gLobalVar.g_iTotalVoiceFree := 0;
end;

procedure TForm1.OnExit(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  Self.Close;
end;

procedure TForm1.OnPrepareRemove(Sender: TObject; Button: TMouseButton;
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
