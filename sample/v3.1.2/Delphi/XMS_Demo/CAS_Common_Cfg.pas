unit CAS_Common_Cfg;

interface
uses
  Windows,SysUtils,inifiles,DJAcsDataDef;

Var
  CAS_Cfg_IniName:string;
  function CAS_Common_Cfg_ReadCfg(Var g_Param_CAS:CmdParamData_CAS_t):integer;
implementation

function CAS_Common_Cfg_ReadCfg(Var g_Param_CAS:CmdParamData_CAS_t):integer;
Var
  TmpStr:string;
  TmpName:string;
  pStr:Pchar;
  iTmp,i,j:integer;
  inifile:Tinifile;
begin

    CAS_Cfg_IniName:='.\XMS_CAS_Cfg.INI';

      inifile:=TiniFile.Create(CAS_Cfg_IniName);
          iTmp:=inifile.ReadInteger('Rule','CalledTableCount',1);
           if (iTmp<0) or (iTmp>16) then
            begin
              result:=-1;
              exit;
            end
           else
            begin
              g_Param_CAS.m_u8CalledTableCount:=iTmp;
            end;

          iTmp:=inifile.ReadInteger('Rule','CalledLen',5);
           if (iTmp<=0) or (iTmp>32) then
            begin
              result:=-2;
              exit;
            end
          else
            begin
              g_Param_CAS.m_u8CalledLen:=BYTE(iTmp);
            end;

          iTmp:=inifile.ReadInteger('Rule','CalledTimeOut',0);
           if (iTmp<0) or (iTmp>10) then
            begin
              result:=-3;
              exit;
            end
           else
            begin
              g_Param_CAS.m_u8CalledTimeOut:=BYTE(iTmp);
            end;

          iTmp:=inifile.ReadInteger('Rule','NeedCaller',1);
           if iTmp<>0 then
            begin
              iTmp:=1;
            end;
          g_Param_CAS.m_u8NeedCaller:=BYTE(iTmp);

          iTmp:=inifile.ReadInteger('Rule','AreaCodeLen',0);
          if g_Param_CAS.m_u8NeedCaller <> 0 then		// need caller
	         begin
		          if (iTmp <0) or (iTmp > 10) then
                begin
                  result:=-4;
                  exit;
                end;
           end;
          g_Param_CAS.m_u8AreaCodeLen := BYTE(iTmp);

          iTmp:=inifile.ReadInteger('Rule','ControlMode',0);
	        if (iTmp <> 0) and (iTmp <> 1) and (iTmp <> 2) then
		        iTmp := 0;
	        g_Param_CAS.m_u8ControlMode := Byte(iTmp);

          //FillChar(g_gLobalVar.g_Param_CAS.m_CalledTable,sizeof(CAS_CalledTableDesc_t)*16,0);
          ZeroMemory(pointer(@g_Param_CAS.m_CalledTable),sizeof(CAS_CalledTableDesc_t)*16);
          if  g_Param_CAS.m_u8CalledTableCount>0 then
            begin
              for i:=0 to g_Param_CAS.m_u8CalledTableCount-1 do
                begin
                  TmpName:=Format('NumHead[%d]',[i]);
                  TmpStr:=inifile.ReadString('CalledTable',TmpName,'168');
                  pStr:=Pchar(TmpStr);
                  if strlen(pStr)>14 then
                   pStr[14]:=char(0);
                  g_Param_CAS.m_CalledTable[i].m_u8NumHeadLen:=strlen(pStr);

                  if g_Param_CAS.m_CalledTable[i].m_u8NumHeadLen>0 then
                  begin
                    for j:=0 to g_Param_CAS.m_CalledTable[i].m_u8NumHeadLen-1 do
                      g_Param_CAS.m_CalledTable[i].m_u8NumHead[j]:=Byte(pStr[j]);
                  end;

                  TmpName:=Format('NumLen[%d]',[i]);
                  iTmp:=inifile.ReadInteger('CalledTable',TmpName,5);
                  if (iTmp<0) or (iTmp>16) then
                    begin
                      result:=-5;
                      exit;
                    end;
                  g_Param_CAS.m_CalledTable[i].m_u8NumLen := Byte(iTmp);
                end;
            end;
      g_Param_CAS.m_u8KA := 1;
      g_Param_CAS.m_u8KD := 3;
      inifile.Free;
      result:=0;
end;

end.
