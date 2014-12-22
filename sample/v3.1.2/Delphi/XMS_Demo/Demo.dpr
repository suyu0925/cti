program Demo;

uses
  ShareMem,
  Forms,
  DJDemo in 'DJDemo.pas' {Form1},
  GlobalVal in 'GlobalVal.pas',
  DJAcsDataDef in 'DJAcsDataDef.pas',
  XMS_Demo_Sub in 'XMS_Demo_Sub.pas',
  XMS_Demo_Event in 'XMS_Demo_Event.pas',
  DJAcsDevState in 'DJAcsDevState.pas',
  Analog_Common_Code in 'Analog_Common_Code.pas',
  TDJAcsAPIDef in 'TDJAcsAPIDef.pas',
  CAS_Common_Cfg in 'CAS_Common_Cfg.pas',
  XMS_Demo_String in 'XMS_Demo_String.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
