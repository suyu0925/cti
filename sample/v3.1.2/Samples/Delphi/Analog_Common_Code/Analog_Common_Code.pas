unit Analog_Common_Code;

interface
uses
  SysUtils,inifiles;

Type
  TYPE_ANALOG_GTD_PARAM=record
  m_u16Freq0:                       Word;
  m_u16Freq1:                       Word;
  m_u16DialTone_FreqIndexMask:      Word;
  m_u16DialTone_On_Time:            Word;
  m_u16RingBackTone_FreqIndexMask:  Word;
  m_u16RingBackTone_On_Time:        Word;
  m_u16RingBackTone_Off_Time:       Word;
  m_u16RingBackTone_TimeDeviation:  Word;

  m_u16BusyTone0_FreqIndexMask:     Word;
  m_u16BusyTone0_On_Time:           Word;
  m_u16BusyTone0_Off_Time:          Word;
  m_u16BusyTone0_TimeDeviation:     Word;

  m_u16BusyTone1_FreqIndexMask:     Word;
  m_u16BusyTone1_On_Time:           Word;
  m_u16BusyTone1_Off_Time:          Word;
  m_u16BusyTone1_TimeDeviation:     Word;

  m_u16BusyTone2_FreqIndexMask:     Word;
  m_u16BusyTone2_On_Time:           Word;
  m_u16BusyTone2_Off_Time:          Word;
  m_u16BusyTone2_TimeDeviation:     Word;

  m_u16NoDialToneAfterOffHook:      Word;
  m_u16Ringback_NoAnswerTime:       Word;
  m_u16SendFSKCallerIDTime:         Word;
end;

Var
Analog_Cfg_IniName:string;
function Analog_Common_Cfg_ReadCfg(Var g_Param_Analog:TYPE_ANALOG_GTD_PARAM):integer;

implementation

function Analog_Common_Cfg_ReadCfg(Var g_Param_Analog:TYPE_ANALOG_GTD_PARAM):integer;
Var
  iTmp:integer;
  inifile:Tinifile;
begin
  Analog_Cfg_IniName:='..\Analog_Common_Code\XMS_Analog_Cfg.INI';
  inifile:=TiniFile.Create(Analog_Cfg_IniName);
          iTmp:=inifile.ReadInteger('Freq','Freq0',450);
          if (iTmp<300) or (iTmp>3400) then
            begin
              result:=-1;
              exit;
            end;
          g_Param_Analog.m_u16Freq0:=Word(iTmp);

          iTmp:=inifile.ReadInteger('Freq','Freq1',500);
          if (iTmp<300) or (iTmp>3400) then
            begin
              result:=-2;
              exit;
            end;
          g_Param_Analog.m_u16Freq1:=Word(iTmp);

          iTmp:=inifile.ReadInteger('DialTone','FreqIndexMask',3);
          if (iTmp<0) or (iTmp>255) then
            begin
              result:=-3;
              exit;
            end;
          g_Param_Analog.m_u16DialTone_FreqIndexMask:=Word(iTmp);

          iTmp:=inifile.ReadInteger('DialTone','On_Time',1000);
          if (iTmp<100) or (iTmp>5000) then
            begin
              result:=-4;
              exit;
            end;
          g_Param_Analog.m_u16DialTone_On_Time:=Word(iTmp);

          iTmp:=inifile.ReadInteger('RingBackTone','FreqIndexMask',3);
          if (iTmp<0) or (iTmp>255) then
            begin
              result:=-5;
              exit;
            end;
          g_Param_Analog.m_u16RingBackTone_FreqIndexMask:=Word(iTmp);

          iTmp:=inifile.ReadInteger('RingBackTone','On_Time',1000);
          if (iTmp<100) or (iTmp>5000) then
            begin
              result:=-5;
              exit;
            end;
          g_Param_Analog.m_u16RingBackTone_On_Time:=Word(iTmp);

          iTmp:=inifile.ReadInteger('RingBackTone','Off_Time',4000);
          if (iTmp<100) or (iTmp>5000) then
            begin
              result:=-6;
              exit;
            end;
          g_Param_Analog.m_u16RingBackTone_Off_Time:=Word(iTmp);

          iTmp:=inifile.ReadInteger('RingBackTone','TimeDeviation',10);
          if (iTmp<0) or (iTmp>50) then
            begin
              result:=-7;
              exit;
            end;
          g_Param_Analog.m_u16RingBackTone_TimeDeviation:=Word(iTmp);

          iTmp:=inifile.ReadInteger('BusyTone0','FreqIndexMask',3);
          if (iTmp<0) or (iTmp>255) then
            begin
              result:=-8;
              exit;
            end;
          g_Param_Analog.m_u16BusyTone0_FreqIndexMask:=Word(iTmp);

          iTmp:=inifile.ReadInteger('BusyTone0','On_Time',1000);
          if (iTmp<100) or (iTmp>5000) then
            begin
              result:=-8;
              exit;
            end;
          g_Param_Analog.m_u16BusyTone0_On_Time:=Word(iTmp);

          iTmp:=inifile.ReadInteger('BusyTone0','Off_Time',4000);
          if (iTmp<100) or (iTmp>5000) then
            begin
              result:=-10;
              exit;
            end;
          g_Param_Analog.m_u16BusyTone0_Off_Time:=Word(iTmp);

          iTmp:=inifile.ReadInteger('BusyTone0','TimeDeviation',10);
          if (iTmp<0) or (iTmp>50) then
            begin
              result:=-11;
              exit;
            end;
          g_Param_Analog.m_u16BusyTone0_TimeDeviation:=Word(iTmp);

          iTmp:=inifile.ReadInteger('BusyTone1','FreqIndexMask',3);
          if (iTmp<0) or (iTmp>255) then
            begin
              result:=-8;
              exit;
            end;
          g_Param_Analog.m_u16BusyTone1_FreqIndexMask:=Word(iTmp);

          iTmp:=inifile.ReadInteger('BusyTone1','On_Time',1000);
          if (iTmp<100) or (iTmp>5000) then
            begin
              result:=-8;
              exit;
            end;
          g_Param_Analog.m_u16BusyTone1_On_Time:=Word(iTmp);

          iTmp:=inifile.ReadInteger('BusyTone1','Off_Time',4000);
          if (iTmp<100) or (iTmp>5000) then
            begin
              result:=-10;
              exit;
            end;
          g_Param_Analog.m_u16BusyTone1_Off_Time:=Word(iTmp);

          iTmp:=inifile.ReadInteger('BusyTone1','TimeDeviation',10);
          if (iTmp<0) or (iTmp>50) then
            begin
              result:=-11;
              exit;
            end;
          g_Param_Analog.m_u16BusyTone1_TimeDeviation:=Word(iTmp);

          iTmp:=inifile.ReadInteger('BusyTone2','FreqIndexMask',3);
          if (iTmp<0) or (iTmp>255) then
            begin
              result:=-8;
              exit;
            end;
          g_Param_Analog.m_u16BusyTone2_FreqIndexMask:=Word(iTmp);

          iTmp:=inifile.ReadInteger('BusyTone2','On_Time',1000);
          if (iTmp<100) or (iTmp>5000) then
            begin
              result:=-8;
              exit;
            end;
          g_Param_Analog.m_u16BusyTone2_On_Time:=Word(iTmp);

          iTmp:=inifile.ReadInteger('BusyTone2','Off_Time',4000);
          if (iTmp<100) or (iTmp>5000) then
            begin
              result:=-10;
              exit;
            end;
          g_Param_Analog.m_u16BusyTone2_Off_Time:=Word(iTmp);

          iTmp:=inifile.ReadInteger('BusyTone2','TimeDeviation',10);
          if (iTmp<0) or (iTmp>50) then
            begin
              result:=-11;
              exit;
            end;
          g_Param_Analog.m_u16BusyTone2_TimeDeviation:=Word(iTmp);

          iTmp:=inifile.ReadInteger('Other','NoDialToneAfterOffHook',5000);
          if (iTmp<1000) or (iTmp>10000) then
            begin
              result:=-11;
              exit;
            end;
          g_Param_Analog.m_u16NoDialToneAfterOffHook:=Word(iTmp);

          iTmp:=inifile.ReadInteger('Other','Ringback_NoAnswerTime',40000);
          if (iTmp<10000) or (iTmp>60000) then
            begin
              result:=-11;
              exit;
            end;
          g_Param_Analog.m_u16Ringback_NoAnswerTime:=Word(iTmp);

          iTmp:=inifile.ReadInteger('Other','SendFSKCallerIDTime',1500);
          if (iTmp<1000) or (iTmp>5000) then
            begin
              result:=-11;
              exit;
            end;
          g_Param_Analog.m_u16SendFSKCallerIDTime:=Word(iTmp);
          inifile.Free;
  result:=0;
end;

end.
 