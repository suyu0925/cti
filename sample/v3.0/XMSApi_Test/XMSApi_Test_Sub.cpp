#include "stdafx.h"
#include "XMSApi_Test.h"
#include "XMSApi_TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"

#include "XMSApi_Test_Sub.h"
#include "XMSApi_Test_Event.h"
#include "XMSApi_Test_String.h"
#include "XMSApi_Test_Func.h"

// -----------------------------------------------------------------------
extern char   g_szCSPPlayFile[MAX_PATH];
extern char   g_szCSPRecordFile[MAX_PATH];
extern        ServerID_t g_stCSPServerID;

extern FILE * g_cspPlayFp;
extern FILE * g_cspRecordFp;

int		iComboDeviceSelect = 0;
int		iComboMsgSelect = 0 ;
int		iComboParam = 0;
int		iComboGetParam = 0;

CSP_OPERATER  g_stVocCSPProperty[255][255];


char	ParamTypeStr[MAX_PARAMETER_TYPE][32] =
{
	"Voice",                       //0
	"CAS",                         //1
	"ANALOG_USER",                 //2
	"ANALOG_TRUNK",                //3
	"ATRUNK_FLASH",                //11
	"ANALOG_REC_VOLTAGE",
	"REC_MOD_MODE",
	"VoIP",                        //4
	"Board_FskSet",                //5
	"Board_FlashSet",              //6
	"Board_GTDSet",                //7
	"Board_VSDSet",                //8
	"Board_GTGSet",                //9
	"Board_ActiveMemSet",          //10
	"Board_CTCLKSet",              //22
	"Board_VADMinLevelSet",        //22
	"Board_CommonParamSet",
	"Board_ResetBoardParamSet",    

	"VOC_Breaken_Call",            //12
	"VOC_3GFaxTone",               //13
	"Fax_PageHeader",              //14
	"Fax_ECM",                     //15
	"Fax_BPS",                     //16
	"Fax_Multi-File",              //17
	"MT_EM",                       //18
	"RTPX",                        //19
	"MediaEx",                     //20
	"ConfParamSet",                //21
	"SS7RawFrameParamSet",         //  author: chenz
	"UserReadXmsBoardInfo",         //  author: chenz
	"CmdParamDataCAS",
	"DSS1_CallType",
	"DSS1_APPENDCALLEE",
	"DSS1_CALL_PARAM",
	"DSS1_ORI_NUMBER",
	"Other",                       
};

char GetParamTypeStr[MAX_GETPARAMETER_TYPE][32] =
{
	"Get_3GP_FILE_CFG",
	"VOIP",
	"Get Board Info",
	"Get SS7 TUP",
	"Get SS7 ISUP",
	"Get Conf",
	"Get User SN",
	"Get Voc2W SN",
	"Get Voc4W SN",
	"Get Mod Voltage",
	"Get DSS1 OriNum",
};

// -----------------------------------------------------------------------
// variable declaration
extern CXMSApi_TestApp theApp;
CXMSApi_TestDlg	*pdlg = NULL;


// variable in "XMSApi_Test.INI"
char			cfg_IniName[MAX_FILE_NAME_LEN] = "";
char			cfg_IniShortName[] = "\\XMSApi_Test.INI";

ServerID_t		cfg_ServerID;
int				cfg_iAutoScroll;
int				cfg_s32DebugOn;
int				cfg_s32AutoRtp;
int				cfg_iComboDevice;
int				cfg_iComboParam;
int				cfg_iComboGetParam;

char			cfg_CallingNum[ACS_MAX_CALL_NUM];
char			cfg_CalledNum[ACS_MAX_CALL_NUM];

char			cfg_PlayFileName[MAX_FILE_NAME_LEN];
char			cfg_RecordFileName[MAX_FILE_NAME_LEN];

char			cfg_CSPPlayFileName[MAX_FILE_NAME_LEN];
char			cfg_CSPRecordFileName[MAX_FILE_NAME_LEN];
char			cfg_CSPIP[MAX_FILE_NAME_LEN];
int             cfg_CSPPort;

char			cfg_SendFaxName[MAX_FILE_NAME_LEN];
char			cfg_ReceiveFaxName[MAX_FILE_NAME_LEN];
char			cfg_IPIP[MAX_FILE_NAME_LEN];
int				cfg_iIPPort; //new added by wangzk 2007.10.17

int				iComboTone;

//------fsk-------
char cfg_rxFilterWindow[20];
char cfg_rxPeriodTheshold[20];
char cfg_rx55Count[20];
char cfg_rxAllOneSamples[20];
char cfg_rxDataTimeOut[20];
char cfg_txBit1Freq[20];
char cfg_txBit0Freq[20];
char cfg_tx55Count[20];
char cfg_txAllOneSamples[20];

//------GTD set_freq-------
char cfg_freq_index1[20];
char cfg_freq_coef1[20];
char cfg_freq_index2[20];
char cfg_freq_coef2[20];
char cfg_freq_index3[20];
char cfg_freq_coef3[20];
char cfg_freq_index4[20];
char cfg_freq_coef4[20];

//------GTD Set Tone-------
char cfg_gtdid1[20];
char cfg_freqmask1[20];
char cfg_threshold1[20];
char cfg_envelop1[20];
char cfg_repeatcount1[20];
char cfg_minontime11[20];
char cfg_maxontime11[20];
char cfg_minofftime11[20];
char cfg_maxofftime11[20];
char cfg_minontime21[20];
char cfg_maxontime21[20];
char cfg_minofftime21[20];
char cfg_maxofftime21[20];

char cfg_gtdid2[20];
char cfg_freqmask2[20];
char cfg_threshold2[20];
char cfg_envelop2[20];
char cfg_repeatcount2[20];
char cfg_minontime12[20];
char cfg_maxontime12[20];
char cfg_minofftime12[20];
char cfg_maxofftime12[20];
char cfg_minontime22[20];
char cfg_maxontime22[20];
char cfg_minofftime22[20];
char cfg_maxofftime22[20];

char cfg_gtdid3[20];
char cfg_freqmask3[20];
char cfg_threshold3[20];
char cfg_envelop3[20];
char cfg_repeatcount3[20];
char cfg_minontime13[20];
char cfg_maxontime13[20];
char cfg_minofftime13[20];
char cfg_maxofftime13[20];
char cfg_minontime23[20];
char cfg_maxontime23[20];
char cfg_minofftime23[20];
char cfg_maxofftime23[20];

char cfg_gtdid4[20];
char cfg_freqmask4[20];
char cfg_threshold4[20];
char cfg_envelop4[20];
char cfg_repeatcount4[20];
char cfg_minontime14[20];
char cfg_maxontime14[20];
char cfg_minofftime14[20];
char cfg_maxofftime14[20];
char cfg_minontime24[20];
char cfg_maxontime24[20];
char cfg_minofftime24[20];
char cfg_maxofftime24[20];

char cfg_gtdid5[20];
char cfg_freqmask5[20];
char cfg_threshold5[20];
char cfg_envelop5[20];
char cfg_repeatcount5[20];
char cfg_minontime15[20];
char cfg_maxontime15[20];
char cfg_minofftime15[20];
char cfg_maxofftime15[20];
char cfg_minontime25[20];
char cfg_maxontime25[20];
char cfg_minofftime25[20];
char cfg_maxofftime25[20];

char cfg_gtdid6[20];
char cfg_freqmask6[20];
char cfg_threshold6[20];
char cfg_envelop6[20];
char cfg_repeatcount6[20];
char cfg_minontime16[20];
char cfg_maxontime16[20];
char cfg_minofftime16[20];
char cfg_maxofftime16[20];
char cfg_minontime26[20];
char cfg_maxontime26[20];
char cfg_minofftime26[20];
char cfg_maxofftime26[20];
// end of "variable in "config.txt""

//------GTG set_freq-------
char gtg_cfg_freq_index1[20];
char gtg_cfg_freq_coef1[20];
char gtg_cfg_freq_index2[20];
char gtg_cfg_freq_coef2[20];
char gtg_cfg_freq_index3[20];
char gtg_cfg_freq_coef3[20];
char gtg_cfg_freq_index4[20];
char gtg_cfg_freq_coef4[20];

//------GTG Set Tone-------
char cfg_gtgid1[20];
char cfg_gtgfreqindex11[20];
char cfg_gtgfreqindex21[20];
char cfg_gtgthreshold11[20];
char cfg_gtgthreshold21[20];
char cfg_gtgenvelop1[20];
char cfg_gtgrepeatcount1[20];
char cfg_gtgontime11[20];
char cfg_gtgofftime11[20];
char cfg_gtgontime21[20];
char cfg_gtgofftime21[20];


char cfg_gtgid2[20];
char cfg_gtgfreqindex12[20];
char cfg_gtgfreqindex22[20];
char cfg_gtgthreshold12[20];
char cfg_gtgthreshold22[20];
char cfg_gtgenvelop2[20];
char cfg_gtgrepeatcount2[20];
char cfg_gtgontime12[20];
char cfg_gtgofftime12[20];
char cfg_gtgontime22[20];
char cfg_gtgofftime22[20];

char cfg_gtgid3[20];
char cfg_gtgfreqindex13[20];
char cfg_gtgfreqindex23[20];
char cfg_gtgthreshold13[20];
char cfg_gtgthreshold23[20];
char cfg_gtgenvelop3[20];
char cfg_gtgrepeatcount3[20];
char cfg_gtgontime13[20];
char cfg_gtgofftime13[20];
char cfg_gtgontime23[20];
char cfg_gtgofftime23[20];

char cfg_gtgid4[20];
char cfg_gtgfreqindex14[20];
char cfg_gtgfreqindex24[20];
char cfg_gtgthreshold14[20];
char cfg_gtgthreshold24[20];
char cfg_gtgenvelop4[20];
char cfg_gtgrepeatcount4[20];
char cfg_gtgontime14[20];
char cfg_gtgofftime14[20];
char cfg_gtgontime24[20];
char cfg_gtgofftime24[20];

char cfg_gtgid5[20];
char cfg_gtgfreqindex15[20];
char cfg_gtgfreqindex25[20];
char cfg_gtgthreshold15[20];
char cfg_gtgthreshold25[20];
char cfg_gtgenvelop5[20];
char cfg_gtgrepeatcount5[20];
char cfg_gtgontime15[20];
char cfg_gtgofftime15[20];
char cfg_gtgontime25[20];
char cfg_gtgofftime25[20];

char cfg_gtgid6[20];
char cfg_gtgfreqindex16[20];
char cfg_gtgfreqindex26[20];
char cfg_gtgthreshold16[20];
char cfg_gtgthreshold26[20];
char cfg_gtgenvelop6[20];
char cfg_gtgrepeatcount6[20];
char cfg_gtgontime16[20];
char cfg_gtgofftime16[20];
char cfg_gtgontime26[20];
char cfg_gtgofftime26[20];

char cfg_flash_mintime[20];
char cfg_flash_maxtime[20];

// ss7Raw author:chenz
char cfg_ss7_m_u8UserType[20];
char cfg_ss7_m_u8LinkType[20];
char cfg_ss7_m_u8MsgType[20];
char cfg_ss7_m_u8InfoLen[20];
char cfg_ss7_m_u8UnitId[20];
char cfg_ss7_m_u8E1Port[20];
char cfg_ss7_m_u8Ts[20];
char cfg_ss7_m_u8Reserved1[20];
char cfg_ss7_m_u8Info[255];
char cfg_ss7_Reserved2[20];

// UserReadXmsBoardInfo author:chenz
char cfg_Acs_m_u8MacAddr[20];
char cfg_Acs_m_u8ChassisType[20];
char cfg_Acs_m_u8ChassisIndex[20];
char cfg_Acs_m_u8ChassisSlot[20];
char cfg_Acs_m_u8SubBoardIndex[20];
char cfg_Acs_m_u8BoardType[20];
char cfg_Acs_rfu1[20];
char cfg_Acs_m_s8SystemName[32];
char cfg_Acs_m_s8PlatformType[20];
char cfg_Acs_m_s8UserCode[20];
char cfg_Acs_m_s32SysId[20];
char cfg_Acs_rfu2[20];
char cfg_Acs_m_s8FirmwareName[20];
char cfg_Acs_m_s8FirmwareVersion[20];
char cfg_Acs_m_s8RevisionDate[20];

// CmdParamData_CAS_t author:chenz
char cfg_Acs_m_u8CalledTableCount[20];
char cfg_Acs_m_u8CalledLen[20];
char cfg_Acs_m_u8CalledTimeOut[20];
char cfg_Acs_m_u8NeedCaller[20];
char cfg_Acs_m_u8AreaCodeLen[20];
char cfg_Acs_m_u8KA[20];
char cfg_Acs_m_u8KD[20];
char cfg_Acs_m_u8ControlMode[20];
char cfg_Acs_m_u8CountryCode[20];

ACSHandle_t		g_acsHandle = -1;
DJ_U8			g_u8UnitID = 12;

char            g_s8OwnAppName[100] = "App1";
char            g_s8OthersAppName[100] = "App2";

bool			bStartWorkFlag = false;

extern	int		iNowOpIndex;
extern	int		iOpenedIndex1;
extern	int		iOpenedIndex2;
extern	int		iOpenedIndex3;

extern	int		TotalDevRes;
extern	int		TotalDevOpened;
extern	TYPE_MY_DEVICE_STRUCT	*pDevRes;
extern	TYPE_MY_DEVICE_STRUCT	DevOpened[MAX_DEVICE_ALLOW_OPEN];


// -----------------------------------------------------------------------
// local function decalration
void	WriteToConfig(void);
void	ReadFromConfig(void);
void	InitTextBox(void);
void	FetchFromText();

void	InitComboBox(void);
void	InitListMsg(void);

// -----------------------------------------------------------------------
void	ReadFromConfig(void)
{

	GetCurrentDirectory ( MAX_FILE_NAME_LEN-32, cfg_IniName );
	strcat ( cfg_IniName, cfg_IniShortName );

	GetPrivateProfileString ( "ConfigInfo", "IpAddr", "192.168.0.8", cfg_ServerID.m_s8ServerIp, sizeof(cfg_ServerID.m_s8ServerIp), cfg_IniName);

	cfg_ServerID.m_u32ServerPort = GetPrivateProfileInt ( "ConfigInfo", "Port", 9001, cfg_IniName);
		
	GetPrivateProfileString("ConfigInfo","UserName","",cfg_ServerID.m_s8UserName,sizeof(cfg_ServerID.m_s8UserName),cfg_IniName);
	GetPrivateProfileString("ConfigInfo","PassWord","",cfg_ServerID.m_s8UserPwd,sizeof(cfg_ServerID.m_s8UserPwd),cfg_IniName);

	g_u8UnitID = GetPrivateProfileInt ( "ConfigInfo", "AppUnitID", 12, cfg_IniName);

	cfg_iAutoScroll = GetPrivateProfileInt ( "ConfigInfo", "AutoScroll", 1, cfg_IniName);

	cfg_iComboDevice= GetPrivateProfileInt ( "ConfigInfo", "ComboDevice", 0, cfg_IniName);

	cfg_iComboParam = GetPrivateProfileInt ( "ConfigInfo", "ComboParam", 0, cfg_IniName);
	
	cfg_iComboGetParam = GetPrivateProfileInt ( "ConfigInfo", "ComboGetParam", 0, cfg_IniName);
   
	GetPrivateProfileString ( "ConfigInfo", "AppName", "App1", g_s8OwnAppName, sizeof(g_s8OwnAppName), cfg_IniName);

	GetPrivateProfileString ( "ConfigInfo", "CallingNum", "12345", cfg_CallingNum, sizeof(cfg_CallingNum), cfg_IniName);

	GetPrivateProfileString ( "ConfigInfo", "CalledNum", "99999", cfg_CalledNum, sizeof(cfg_CalledNum), cfg_IniName);

	GetPrivateProfileString ( "ConfigInfo", "PlayFile", "", cfg_PlayFileName, sizeof(cfg_PlayFileName), cfg_IniName);

	GetPrivateProfileString ( "ConfigInfo", "RecordFile", "", cfg_RecordFileName, sizeof(cfg_RecordFileName), cfg_IniName);

	/////////////////////////////////////////////////
	GetPrivateProfileString ( "ConfigInfo", "CSPPlayFile", "", cfg_CSPPlayFileName, sizeof(cfg_CSPPlayFileName), cfg_IniName);

	GetPrivateProfileString ( "ConfigInfo", "CSPRecordFile", "", cfg_CSPRecordFileName, sizeof(cfg_CSPRecordFileName), cfg_IniName);

	GetPrivateProfileString ( "ConfigInfo", "CSPDSPIP", "", cfg_CSPIP, sizeof(cfg_PlayFileName), cfg_IniName);

	cfg_CSPPort = GetPrivateProfileInt ( "ConfigInfo", "CSPDSPPort", 0, cfg_IniName);

    
	/////////////////////////////////////////////////
	GetPrivateProfileString ( "ConfigInfo", "SendFaxFile", "", cfg_SendFaxName, sizeof(cfg_SendFaxName), cfg_IniName);

	GetPrivateProfileString ( "ConfigInfo", "ReceiveFaxFile", "", cfg_ReceiveFaxName, sizeof(cfg_ReceiveFaxName), cfg_IniName);

	//new
	GetPrivateProfileString ( "ConfigInfo", "IPIP", "192.168.10.58", cfg_IPIP, sizeof(cfg_IPIP), cfg_IniName);
	cfg_iIPPort     = GetPrivateProfileInt ( "ConfigInfo", "IPPort", 1730, cfg_IniName);


	cfg_s32DebugOn = GetPrivateProfileInt ( "ConfigInfo", "DebugOn", 0, cfg_IniName);
	cfg_s32AutoRtp = GetPrivateProfileInt ( "ConfigInfo", "autortp", 0, cfg_IniName);

	//fsk
	GetPrivateProfileString("fsk","rxFilterWindow","4",cfg_rxFilterWindow,20,cfg_IniName);
	GetPrivateProfileString("fsk","rxPeriodTheshold","80",cfg_rxPeriodTheshold,20,cfg_IniName);
	GetPrivateProfileString("fsk","rx55Count","10",cfg_rx55Count,20,cfg_IniName);
	GetPrivateProfileString("fsk","rxAllOneSamples","60",cfg_rxAllOneSamples,20,cfg_IniName);
	GetPrivateProfileString("fsk","rxDataTimeOut","20",cfg_rxDataTimeOut,20,cfg_IniName);
	GetPrivateProfileString("fsk","txBit1Freq","1350",cfg_txBit1Freq,20,cfg_IniName);
	GetPrivateProfileString("fsk","txBit0Freq","2150",cfg_txBit0Freq,20,cfg_IniName);
	GetPrivateProfileString("fsk","tx55Count","20",cfg_tx55Count,20,cfg_IniName);
	GetPrivateProfileString("fsk","txAllOneSamples","600",cfg_txAllOneSamples,20,cfg_IniName);

	//GTD
	GetPrivateProfileString("GTD","freq_index1","0",cfg_freq_index1,20,cfg_IniName);
	GetPrivateProfileString("GTD","freq_coef1","450",cfg_freq_coef1,20,cfg_IniName);
	GetPrivateProfileString("GTD","freq_index2","1",cfg_freq_index2,20,cfg_IniName);
	GetPrivateProfileString("GTD","freq_coef2","500",cfg_freq_coef2,20,cfg_IniName);
	GetPrivateProfileString("GTD","freq_index3","2",cfg_freq_index3,20,cfg_IniName);
	GetPrivateProfileString("GTD","freq_coef3","1100",cfg_freq_coef3,20,cfg_IniName);
	GetPrivateProfileString("GTD","freq_index4","3",cfg_freq_index4,20,cfg_IniName);
	GetPrivateProfileString("GTD","freq_coef4","2100",cfg_freq_coef4,20,cfg_IniName);

	//dial
	GetPrivateProfileString("GTD","gtdid1","48",cfg_gtdid1,20,cfg_IniName);
	GetPrivateProfileString("GTD","freqmask1","3",cfg_freqmask1,20,cfg_IniName);
	GetPrivateProfileString("GTD","threshold1","0",cfg_threshold1,20,cfg_IniName);
	GetPrivateProfileString("GTD","envelop1","0",cfg_envelop1,20,cfg_IniName);
	GetPrivateProfileString("GTD","repeatcount1","1",cfg_repeatcount1,20,cfg_IniName);

	GetPrivateProfileString("GTD","minontime11","100",cfg_minontime11, 20,cfg_IniName);
	GetPrivateProfileString("GTD","maxontime11","0",  cfg_maxontime11, 20,cfg_IniName);
	GetPrivateProfileString("GTD","minofftime11","0", cfg_minofftime11,20,cfg_IniName);
	GetPrivateProfileString("GTD","maxofftime11","0", cfg_maxofftime11,20,cfg_IniName);
	GetPrivateProfileString("GTD","minontime21","0" , cfg_minontime21, 20,cfg_IniName);
	GetPrivateProfileString("GTD","maxontime21","0" , cfg_maxontime21, 20,cfg_IniName);
	GetPrivateProfileString("GTD","minofftime21","0", cfg_minofftime21,20,cfg_IniName);
	GetPrivateProfileString("GTD","maxofftime21","0", cfg_maxofftime21,20,cfg_IniName);

	//ring
	GetPrivateProfileString("GTD","gtdid2","49",cfg_gtdid2,20,cfg_IniName);
	GetPrivateProfileString("GTD","freqmask2","3",cfg_freqmask2,20,cfg_IniName);
	GetPrivateProfileString("GTD","threshold2","0",cfg_threshold2,20,cfg_IniName);
	GetPrivateProfileString("GTD","envelop2","1",cfg_envelop2,20,cfg_IniName);
	GetPrivateProfileString("GTD","repeatcount2","1",cfg_repeatcount2,20,cfg_IniName);

	GetPrivateProfileString("GTD","minontime12","55",  cfg_minontime12, 20,cfg_IniName);
	GetPrivateProfileString("GTD","maxontime12","75",  cfg_maxontime12, 20,cfg_IniName);
	GetPrivateProfileString("GTD","minofftime12","240",cfg_minofftime12,20,cfg_IniName);
	GetPrivateProfileString("GTD","maxofftime12","280",cfg_maxofftime12,20,cfg_IniName);
	GetPrivateProfileString("GTD","minontime22","0" ,  cfg_minontime22, 20,cfg_IniName);
	GetPrivateProfileString("GTD","maxontime22","0" ,  cfg_maxontime22, 20,cfg_IniName);
	GetPrivateProfileString("GTD","minofftime22","0",  cfg_minofftime22,20,cfg_IniName);
	GetPrivateProfileString("GTD","maxofftime22","0",  cfg_maxofftime22,20,cfg_IniName);

	//busy1
	GetPrivateProfileString("GTD","gtdid3","50",cfg_gtdid3,20,cfg_IniName);
	GetPrivateProfileString("GTD","freqmask3","3",cfg_freqmask3,20,cfg_IniName);
	GetPrivateProfileString("GTD","threshold3","0",cfg_threshold3,20,cfg_IniName);
	GetPrivateProfileString("GTD","envelop3","1",cfg_envelop3,20,cfg_IniName);
	GetPrivateProfileString("GTD","repeatcount3","2",cfg_repeatcount3,20,cfg_IniName);

	GetPrivateProfileString("GTD","minontime13","42",cfg_minontime13, 20,cfg_IniName);
	GetPrivateProfileString("GTD","maxontime13","52",  cfg_maxontime13, 20,cfg_IniName);
	GetPrivateProfileString("GTD","minofftime13","42", cfg_minofftime13,20,cfg_IniName);
	GetPrivateProfileString("GTD","maxofftime13","53", cfg_maxofftime13,20,cfg_IniName);
	GetPrivateProfileString("GTD","minontime23","0" , cfg_minontime23, 20,cfg_IniName);
	GetPrivateProfileString("GTD","maxontime23","0" , cfg_maxontime23, 20,cfg_IniName);
	GetPrivateProfileString("GTD","minofftime23","0", cfg_minofftime23,20,cfg_IniName);
	GetPrivateProfileString("GTD","maxofftime23","0", cfg_maxofftime23,20,cfg_IniName);

	//busy-2
	GetPrivateProfileString("GTD","gtdid4","51",cfg_gtdid4,20,cfg_IniName);
	GetPrivateProfileString("GTD","freqmask4","3",cfg_freqmask4,20,cfg_IniName);
	GetPrivateProfileString("GTD","threshold4","0",cfg_threshold4,20,cfg_IniName);
	GetPrivateProfileString("GTD","envelop4","1",cfg_envelop4,20,cfg_IniName);
	GetPrivateProfileString("GTD","repeatcount4","2",cfg_repeatcount4,20,cfg_IniName);

	GetPrivateProfileString("GTD","minontime14","20", cfg_minontime14, 20,cfg_IniName);
	GetPrivateProfileString("GTD","maxontime14","27", cfg_maxontime14, 20,cfg_IniName);
	GetPrivateProfileString("GTD","minofftime14","20",cfg_minofftime14,20,cfg_IniName);
	GetPrivateProfileString("GTD","maxofftime14","27",cfg_maxofftime14,20,cfg_IniName);
	GetPrivateProfileString("GTD","minontime24","0" , cfg_minontime24, 20,cfg_IniName);
	GetPrivateProfileString("GTD","maxontime24","0" , cfg_maxontime24, 20,cfg_IniName);
	GetPrivateProfileString("GTD","minofftime24","0", cfg_minofftime24,20,cfg_IniName);
	GetPrivateProfileString("GTD","maxofftime24","0", cfg_maxofftime24,20,cfg_IniName);

	memset(cfg_freqmask5,0,sizeof(cfg_freqmask5));
	//busy-3
	GetPrivateProfileString("GTD","gtdid5","52",cfg_gtdid5,20,cfg_IniName);
	GetPrivateProfileString("GTD","freqmask5","3",cfg_freqmask5,20,cfg_IniName);
	GetPrivateProfileString("GTD","threshold5","0",cfg_threshold5,20,cfg_IniName);
	GetPrivateProfileString("GTD","envelop5","1",cfg_envelop5,20,cfg_IniName);
	GetPrivateProfileString("GTD","repeatcount5","2",cfg_repeatcount5,20,cfg_IniName);

	GetPrivateProfileString("GTD","minontime15","30", cfg_minontime15, 20,cfg_IniName);
	GetPrivateProfileString("GTD","maxontime15","38", cfg_maxontime15, 20,cfg_IniName);
	GetPrivateProfileString("GTD","minofftime15","30",cfg_minofftime15,20,cfg_IniName);
	GetPrivateProfileString("GTD","maxofftime15","38",cfg_maxofftime15,20,cfg_IniName);
	GetPrivateProfileString("GTD","minontime25","0" , cfg_minontime25, 20,cfg_IniName);
	GetPrivateProfileString("GTD","maxontime25","0" , cfg_maxontime25, 20,cfg_IniName);
	GetPrivateProfileString("GTD","minofftime25","0", cfg_minofftime25,20,cfg_IniName);
	GetPrivateProfileString("GTD","maxofftime25","0", cfg_maxofftime25,20,cfg_IniName);

	//fax-tone
	GetPrivateProfileString("GTD","gtdid6",      "53",cfg_gtdid6,20,cfg_IniName);
	GetPrivateProfileString("GTD","freqmask6",   "4", cfg_freqmask6,20,cfg_IniName);
	GetPrivateProfileString("GTD","threshold6",  "0", cfg_threshold6,20,cfg_IniName);
	GetPrivateProfileString("GTD","envelop6",    "0", cfg_envelop6,20,cfg_IniName);
	GetPrivateProfileString("GTD","repeatcount6","1", cfg_repeatcount6,20,cfg_IniName);

	GetPrivateProfileString("GTD","minontime16","10", cfg_minontime16, 20,cfg_IniName);
	GetPrivateProfileString("GTD","maxontime16","0",  cfg_maxontime16, 20,cfg_IniName);
	GetPrivateProfileString("GTD","minofftime16","0", cfg_minofftime16,20,cfg_IniName);
	GetPrivateProfileString("GTD","maxofftime16","0", cfg_maxofftime16,20,cfg_IniName);
	GetPrivateProfileString("GTD","minontime26","0" , cfg_minontime26, 20,cfg_IniName);
	GetPrivateProfileString("GTD","maxontime26","0" , cfg_maxontime26, 20,cfg_IniName);
	GetPrivateProfileString("GTD","minofftime26","0", cfg_minofftime26,20,cfg_IniName);
	GetPrivateProfileString("GTD","maxofftime26","0", cfg_maxofftime26,20,cfg_IniName);
	
	GetPrivateProfileString("flash","mintime","5",  cfg_flash_mintime,20,cfg_IniName);
	GetPrivateProfileString("flash","maxtime","25", cfg_flash_maxtime,20,cfg_IniName);

	// SS7 param. author:chenz
	GetPrivateProfileString("SS7","m_u8UserType","3",cfg_ss7_m_u8UserType,20,cfg_IniName);
    GetPrivateProfileString("SS7","m_u8LinkType","2",cfg_ss7_m_u8LinkType,20,cfg_IniName);
	GetPrivateProfileString("SS7","m_u8MsgType","1",cfg_ss7_m_u8MsgType,20,cfg_IniName);
	GetPrivateProfileString("SS7","m_u8InfoLen","10",cfg_ss7_m_u8InfoLen,20,cfg_IniName);
	GetPrivateProfileString("SS7","m_u8UnitId","0001",cfg_ss7_m_u8UnitId,20,cfg_IniName);
	GetPrivateProfileString("SS7","m_u8E1Port","8000",cfg_ss7_m_u8E1Port,20,cfg_IniName);
	GetPrivateProfileString("SS7","m_u8Ts","50",cfg_ss7_m_u8Ts,20,cfg_IniName);
	GetPrivateProfileString("SS7","m_u8Reserved1","0",cfg_ss7_m_u8Reserved1,20,cfg_IniName);
    GetPrivateProfileString("SS7","m_u8Info","keygoe",cfg_ss7_m_u8Info,255,cfg_IniName);
	GetPrivateProfileString("SS7","Reserved2","0",cfg_ss7_Reserved2,20,cfg_IniName);

	// ACS param. author:chenz
	GetPrivateProfileString("ACS","m_u8MacAddr","111111",cfg_Acs_m_u8MacAddr,20,cfg_IniName);
    GetPrivateProfileString("ACS","m_u8ChassisType","0",cfg_Acs_m_u8ChassisType,20,cfg_IniName);
	GetPrivateProfileString("ACS","m_u8ChassisIndex","1",cfg_Acs_m_u8ChassisIndex,20,cfg_IniName);
	GetPrivateProfileString("ACS","m_u8ChassisSlot","1",cfg_Acs_m_u8ChassisSlot,20,cfg_IniName);
	GetPrivateProfileString("ACS","m_u8SubBoardIndex","1",cfg_Acs_m_u8SubBoardIndex,20,cfg_IniName);
	GetPrivateProfileString("ACS","m_u8BoardType","0",cfg_Acs_m_u8BoardType,20,cfg_IniName);
	GetPrivateProfileString("ACS","rfu1","1",cfg_Acs_rfu1,20,cfg_IniName);
	GetPrivateProfileString("ACS","m_s8SystemName","keygoe",cfg_Acs_m_s8SystemName,32,cfg_IniName);
    GetPrivateProfileString("ACS","m_s8PlatformType","0",cfg_Acs_m_s8PlatformType,20,cfg_IniName);
	GetPrivateProfileString("ACS","m_s8UserCode","keygoe",cfg_Acs_m_s8UserCode,20,cfg_IniName);
	GetPrivateProfileString("ACS","m_s32SysId","0001",cfg_Acs_m_s32SysId,20,cfg_IniName);
	GetPrivateProfileString("ACS","rfu2","50",cfg_Acs_rfu2,20,cfg_IniName);
	GetPrivateProfileString("ACS","m_s8FirmwareName","keygoe",cfg_Acs_m_s8FirmwareName,20,cfg_IniName);
    GetPrivateProfileString("ACS","m_s8FirmwareVersion","1.0.0",cfg_Acs_m_s8FirmwareVersion,20,cfg_IniName);
	GetPrivateProfileString("ACS","m_s8RevisionDate","2010-07-27",cfg_Acs_m_s8RevisionDate,20,cfg_IniName);
   
	// ACS param. author:chenz
	GetPrivateProfileString("CMD","m_u8CalledTableCount","0",cfg_Acs_m_u8CalledTableCount,20,cfg_IniName);
    GetPrivateProfileString("CMD","m_u8CalledLen","0",cfg_Acs_m_u8CalledLen,20,cfg_IniName);
	GetPrivateProfileString("CMD","m_u8CalledTimeOut","0",cfg_Acs_m_u8CalledTimeOut,20,cfg_IniName);
	GetPrivateProfileString("CMD","m_u8NeedCaller","1",cfg_Acs_m_u8NeedCaller,20,cfg_IniName);
	GetPrivateProfileString("CMD","m_u8AreaCodeLen","0",cfg_Acs_m_u8AreaCodeLen,20,cfg_IniName);
	GetPrivateProfileString("CMD","m_u8KA","1",cfg_Acs_m_u8KA,20,cfg_IniName);
	GetPrivateProfileString("CMD","m_u8KD","3",cfg_Acs_m_u8KD,20,cfg_IniName);
	GetPrivateProfileString("CMD","m_u8ControlMode","1",cfg_Acs_m_u8ControlMode,20,cfg_IniName);
	GetPrivateProfileString("CMD","m_u8CountryCode","1",cfg_Acs_m_u8CountryCode,20,cfg_IniName);
}

void	WriteToConfig(void)
{
	char	TmpStr[256];

	WritePrivateProfileString ( "ConfigInfo", "IpAddr", cfg_ServerID.m_s8ServerIp, cfg_IniName);
	
	sprintf ( TmpStr, "%d", cfg_ServerID.m_u32ServerPort);
	WritePrivateProfileString ( "ConfigInfo", "Port", TmpStr, cfg_IniName);

	sprintf ( TmpStr, "%d", g_u8UnitID);
	WritePrivateProfileString ( "ConfigInfo", "AppUnitID", TmpStr, cfg_IniName);

	sprintf ( TmpStr, "%d", cfg_iAutoScroll);
	WritePrivateProfileString ( "ConfigInfo", "AutoScroll", TmpStr, cfg_IniName);

	sprintf ( TmpStr, "%d", cfg_iComboDevice);
	WritePrivateProfileString ( "ConfigInfo", "ComboDevice", TmpStr, cfg_IniName);

	sprintf ( TmpStr, "%d", cfg_iIPPort);
	WritePrivateProfileString ( "ConfigInfo", "IPPort", TmpStr, cfg_IniName);
	
	sprintf ( TmpStr, "%d", cfg_iComboParam);
	WritePrivateProfileString ( "ConfigInfo", "ComboParam", TmpStr, cfg_IniName);

	sprintf ( TmpStr, "%d", cfg_iComboGetParam);
	WritePrivateProfileString ( "ConfigInfo", "ComboGetParam", TmpStr, cfg_IniName);

	sprintf ( TmpStr, "%d", cfg_iIPPort);
	WritePrivateProfileString ( "ConfigInfo", "IPPort", TmpStr, cfg_IniName);

	WritePrivateProfileString ( "ConfigInfo", "CallingNum", cfg_CallingNum, cfg_IniName);

	WritePrivateProfileString ( "ConfigInfo", "CalledNum", cfg_CalledNum, cfg_IniName);

	WritePrivateProfileString ( "ConfigInfo", "PlayFile", cfg_PlayFileName, cfg_IniName);

	WritePrivateProfileString ( "ConfigInfo", "RecordFile", cfg_RecordFileName, cfg_IniName);

	/////////////////////////////////////////////////
	WritePrivateProfileString ( "ConfigInfo", "CSPPlayFile", cfg_CSPPlayFileName, cfg_IniName);

	WritePrivateProfileString ( "ConfigInfo", "CSPRecordFile", cfg_CSPRecordFileName, cfg_IniName);

	WritePrivateProfileString ( "ConfigInfo", "CSPDSPIP", cfg_CSPIP, cfg_IniName);

	sprintf ( TmpStr, "%d", cfg_CSPPort );
	WritePrivateProfileString ( "ConfigInfo", "CSPDSPPort", TmpStr, cfg_IniName);
	/////////////////////////////////////////////////

	WritePrivateProfileString ( "ConfigInfo", "SendFaxFile", cfg_SendFaxName, cfg_IniName);

	WritePrivateProfileString ( "ConfigInfo", "ReceiveFaxFile", cfg_ReceiveFaxName, cfg_IniName);

	WritePrivateProfileString ( "ConfigInfo", "IPIP", cfg_IPIP, cfg_IniName);

	sprintf ( TmpStr, "%d", cfg_s32DebugOn);
	WritePrivateProfileString ( "ConfigInfo", "DebugOn", TmpStr, cfg_IniName);
	WritePrivateProfileString ( "ConfigInfo", "autortp", cfg_s32AutoRtp?"1":"0", cfg_IniName);

	//fsk
	WritePrivateProfileString("fsk","rxFilterWindow",cfg_rxFilterWindow,cfg_IniName);
	WritePrivateProfileString("fsk","rxPeriodTheshold",cfg_rxPeriodTheshold,cfg_IniName);
	WritePrivateProfileString("fsk","rx55Count",cfg_rx55Count,cfg_IniName);
	WritePrivateProfileString("fsk","rxAllOneSamples",cfg_rxAllOneSamples,cfg_IniName);
	WritePrivateProfileString("fsk","rxDataTimeOut",cfg_rxDataTimeOut,cfg_IniName);
	WritePrivateProfileString("fsk","txBit1Freq",cfg_txBit1Freq,cfg_IniName);
	WritePrivateProfileString("fsk","txBit0Freq",cfg_txBit0Freq,cfg_IniName);
	WritePrivateProfileString("fsk","tx55Count",cfg_tx55Count,cfg_IniName);
	WritePrivateProfileString("fsk","txAllOneSamples",cfg_txAllOneSamples,cfg_IniName);

	//WritePrivateProfileString ( "GTD", "IPIP", cfg_IPIP, cfg_IniName);
	//GTD
	WritePrivateProfileString("GTD","freq_index1",cfg_freq_index1,cfg_IniName);
	WritePrivateProfileString("GTD","freq_coef1", cfg_freq_coef1, cfg_IniName);
	WritePrivateProfileString("GTD","freq_index2",cfg_freq_index2,cfg_IniName);
	WritePrivateProfileString("GTD","freq_coef2", cfg_freq_coef2, cfg_IniName);
	WritePrivateProfileString("GTD","freq_index3",cfg_freq_index3,cfg_IniName);
	WritePrivateProfileString("GTD","freq_coef3", cfg_freq_coef3, cfg_IniName);
	WritePrivateProfileString("GTD","freq_index4",cfg_freq_index4,cfg_IniName);
	WritePrivateProfileString("GTD","freq_coef4", cfg_freq_coef4, cfg_IniName);

	//dial
	WritePrivateProfileString("GTD","gtdid1",      cfg_gtdid1,      cfg_IniName);
	WritePrivateProfileString("GTD","freqmask1",   cfg_freqmask1,   cfg_IniName);
	WritePrivateProfileString("GTD","threshold1",  cfg_threshold1,  cfg_IniName);
	WritePrivateProfileString("GTD","envelop1",    cfg_envelop1,    cfg_IniName);
	WritePrivateProfileString("GTD","repeatcount1",cfg_repeatcount1,cfg_IniName);
	WritePrivateProfileString("GTD","minontime11", cfg_minontime11, cfg_IniName);
	WritePrivateProfileString("GTD","maxontime11", cfg_maxontime11, cfg_IniName);
	WritePrivateProfileString("GTD","minofftime11",cfg_minofftime11,cfg_IniName);
	WritePrivateProfileString("GTD","maxofftime11",cfg_maxofftime11,cfg_IniName);
	WritePrivateProfileString("GTD","minontime21", cfg_minontime21, cfg_IniName);
	WritePrivateProfileString("GTD","maxontime21", cfg_maxontime21, cfg_IniName);
	WritePrivateProfileString("GTD","minofftime21",cfg_minofftime21,cfg_IniName);
	WritePrivateProfileString("GTD","maxofftime21",cfg_maxofftime21,cfg_IniName);

	//ring
	WritePrivateProfileString("GTD","gtdid2",      cfg_gtdid2,      cfg_IniName);
	WritePrivateProfileString("GTD","freqmask2",   cfg_freqmask2,   cfg_IniName);
	WritePrivateProfileString("GTD","threshold2",  cfg_threshold2,  cfg_IniName);
	WritePrivateProfileString("GTD","envelop2",    cfg_envelop2,    cfg_IniName);
	WritePrivateProfileString("GTD","repeatcount2",cfg_repeatcount2,cfg_IniName);
	WritePrivateProfileString("GTD","minontime12", cfg_minontime12, cfg_IniName);
	WritePrivateProfileString("GTD","maxontime12", cfg_maxontime12, cfg_IniName);
	WritePrivateProfileString("GTD","minofftime12",cfg_minofftime12,cfg_IniName);
	WritePrivateProfileString("GTD","maxofftime12",cfg_maxofftime12,cfg_IniName);
	WritePrivateProfileString("GTD","minontime22", cfg_minontime22, cfg_IniName);
	WritePrivateProfileString("GTD","maxontime22", cfg_maxontime22, cfg_IniName);
	WritePrivateProfileString("GTD","minofftime22",cfg_minofftime22,cfg_IniName);
	WritePrivateProfileString("GTD","maxofftime22",cfg_maxofftime22,cfg_IniName);

	//busy-i
	WritePrivateProfileString("GTD","gtdid3",      cfg_gtdid3,      cfg_IniName);
	WritePrivateProfileString("GTD","freqmask3",   cfg_freqmask3,   cfg_IniName);
	WritePrivateProfileString("GTD","threshold3",  cfg_threshold3,  cfg_IniName);
	WritePrivateProfileString("GTD","envelop3",    cfg_envelop3,    cfg_IniName);
	WritePrivateProfileString("GTD","repeatcount3",cfg_repeatcount3,cfg_IniName);
	WritePrivateProfileString("GTD","minontime13", cfg_minontime13, cfg_IniName);
	WritePrivateProfileString("GTD","maxontime13", cfg_maxontime13, cfg_IniName);
	WritePrivateProfileString("GTD","minofftime13",cfg_minofftime13,cfg_IniName);
	WritePrivateProfileString("GTD","maxofftime13",cfg_maxofftime13,cfg_IniName);
	WritePrivateProfileString("GTD","minontime23", cfg_minontime23, cfg_IniName);
	WritePrivateProfileString("GTD","maxontime23", cfg_maxontime23, cfg_IniName);
	WritePrivateProfileString("GTD","minofftime23",cfg_minofftime23,cfg_IniName);
	WritePrivateProfileString("GTD","maxofftime23",cfg_maxofftime23,cfg_IniName);

	//busy-j
	WritePrivateProfileString("GTD","gtdid4",      cfg_gtdid4,      cfg_IniName);
	WritePrivateProfileString("GTD","freqmask4",   cfg_freqmask4,   cfg_IniName);
	WritePrivateProfileString("GTD","threshold4",  cfg_threshold4,  cfg_IniName);
	WritePrivateProfileString("GTD","envelop4",    cfg_envelop4,    cfg_IniName);
	WritePrivateProfileString("GTD","repeatcount4",cfg_repeatcount4,cfg_IniName);
	WritePrivateProfileString("GTD","minontime14", cfg_minontime14, cfg_IniName);
	WritePrivateProfileString("GTD","maxontime14", cfg_maxontime14, cfg_IniName);
	WritePrivateProfileString("GTD","minofftime14",cfg_minofftime14,cfg_IniName);
	WritePrivateProfileString("GTD","maxofftime14",cfg_maxofftime14,cfg_IniName);
	WritePrivateProfileString("GTD","minontime24", cfg_minontime24, cfg_IniName);
	WritePrivateProfileString("GTD","maxontime24", cfg_maxontime24, cfg_IniName);
	WritePrivateProfileString("GTD","minofftime24",cfg_minofftime24,cfg_IniName);
	WritePrivateProfileString("GTD","maxofftime24",cfg_maxofftime24,cfg_IniName);

	//busy-k
	WritePrivateProfileString("GTD","gtdid5",      cfg_gtdid5,      cfg_IniName);
	WritePrivateProfileString("GTD","freqmask5",   cfg_freqmask5,   cfg_IniName);
	WritePrivateProfileString("GTD","threshold5",  cfg_threshold5,  cfg_IniName);
	WritePrivateProfileString("GTD","envelop5",    cfg_envelop5,    cfg_IniName);
	WritePrivateProfileString("GTD","repeatcount5",cfg_repeatcount5,cfg_IniName);
	WritePrivateProfileString("GTD","minontime15", cfg_minontime15, cfg_IniName);
	WritePrivateProfileString("GTD","maxontime15", cfg_maxontime15, cfg_IniName);
	WritePrivateProfileString("GTD","minofftime15",cfg_minofftime15,cfg_IniName);
	WritePrivateProfileString("GTD","maxofftime15",cfg_maxofftime15,cfg_IniName);
	WritePrivateProfileString("GTD","minontime25", cfg_minontime25, cfg_IniName);
	WritePrivateProfileString("GTD","maxontime25", cfg_maxontime25, cfg_IniName);
	WritePrivateProfileString("GTD","minofftime25",cfg_minofftime25,cfg_IniName);
	WritePrivateProfileString("GTD","maxofftime25",cfg_maxofftime25,cfg_IniName);

	//fax-tone
	WritePrivateProfileString("GTD","gtdid6",      cfg_gtdid6,      cfg_IniName);
	WritePrivateProfileString("GTD","freqmask6",   cfg_freqmask6,   cfg_IniName);
	WritePrivateProfileString("GTD","threshold6",  cfg_threshold6,  cfg_IniName);
	WritePrivateProfileString("GTD","envelop6",    cfg_envelop6,    cfg_IniName);
	WritePrivateProfileString("GTD","repeatcount6",cfg_repeatcount6,cfg_IniName);
	WritePrivateProfileString("GTD","minontime16", cfg_minontime16, cfg_IniName);
	WritePrivateProfileString("GTD","maxontime16", cfg_maxontime16, cfg_IniName);
	WritePrivateProfileString("GTD","minofftime16",cfg_minofftime16,cfg_IniName);
	WritePrivateProfileString("GTD","maxofftime16",cfg_maxofftime16,cfg_IniName);
	WritePrivateProfileString("GTD","minontime26", cfg_minontime26, cfg_IniName);
	WritePrivateProfileString("GTD","maxontime26", cfg_maxontime26, cfg_IniName);
	WritePrivateProfileString("GTD","minofftime26",cfg_minofftime26,cfg_IniName);
	WritePrivateProfileString("GTD","maxofftime26",cfg_maxofftime26,cfg_IniName);

	WritePrivateProfileString("flash","mintime", cfg_flash_mintime,cfg_IniName);
	WritePrivateProfileString("flash","maxtime", cfg_flash_maxtime,cfg_IniName);

	// SS7 author:chenz
	WritePrivateProfileString("SS7","m_u8UserType", cfg_ss7_m_u8UserType,cfg_IniName);
	WritePrivateProfileString("SS7","m_u8LinkType", cfg_ss7_m_u8LinkType,cfg_IniName);
	WritePrivateProfileString("SS7","m_u8MsgType", cfg_ss7_m_u8MsgType,cfg_IniName);
	WritePrivateProfileString("SS7","m_u8InfoLen", cfg_ss7_m_u8InfoLen,cfg_IniName);
	WritePrivateProfileString("SS7","m_u8UnitId", cfg_ss7_m_u8UnitId,cfg_IniName);
	WritePrivateProfileString("SS7","m_u8E1Port", cfg_ss7_m_u8E1Port,cfg_IniName);
	WritePrivateProfileString("SS7","m_u8Ts", cfg_ss7_m_u8Ts,cfg_IniName);
	WritePrivateProfileString("SS7","m_u8Reserved1", cfg_ss7_m_u8Reserved1,cfg_IniName);
	WritePrivateProfileString("SS7","m_u8Info", cfg_ss7_m_u8Info,cfg_IniName);
	WritePrivateProfileString("SS7","Reserved2", cfg_ss7_Reserved2,cfg_IniName);

	// ACS author:chenz
	WritePrivateProfileString("ACS","m_u8MacAddr", cfg_Acs_m_u8MacAddr,cfg_IniName);
	WritePrivateProfileString("ACS","m_u8ChassisType", cfg_Acs_m_u8ChassisType,cfg_IniName);
	WritePrivateProfileString("ACS","m_u8ChassisIndex", cfg_Acs_m_u8ChassisIndex,cfg_IniName);
	WritePrivateProfileString("ACS","m_u8ChassisSlot", cfg_Acs_m_u8ChassisSlot,cfg_IniName);
	WritePrivateProfileString("ACS","m_u8SubBoardIndex", cfg_Acs_m_u8SubBoardIndex,cfg_IniName);
	WritePrivateProfileString("ACS","m_u8BoardType", cfg_Acs_m_u8BoardType,cfg_IniName);
	WritePrivateProfileString("ACS","rfu1", cfg_Acs_rfu1,cfg_IniName);
	WritePrivateProfileString("ACS","m_s8SystemName", cfg_Acs_m_s8SystemName,cfg_IniName);
	WritePrivateProfileString("ACS","m_s8PlatformType", cfg_Acs_m_s8PlatformType,cfg_IniName);
	WritePrivateProfileString("ACS","m_s8UserCode", cfg_Acs_m_s8UserCode,cfg_IniName);
	WritePrivateProfileString("ACS","m_s32SysId", cfg_Acs_m_s32SysId,cfg_IniName);
	WritePrivateProfileString("ACS","rfu2", cfg_Acs_rfu2,cfg_IniName);
	WritePrivateProfileString("ACS","m_s8FirmwareName", cfg_Acs_m_s8FirmwareName,cfg_IniName);
	WritePrivateProfileString("ACS","m_s8FirmwareVersion", cfg_Acs_m_s8FirmwareVersion,cfg_IniName);
	WritePrivateProfileString("ACS","m_s8RevisionDate", cfg_Acs_m_s8RevisionDate,cfg_IniName);

	// ACS author:chenz
	WritePrivateProfileString("CMD","m_u8CalledTableCount", cfg_Acs_m_u8CalledTableCount,cfg_IniName);
	WritePrivateProfileString("CMD","m_u8CalledLen", cfg_Acs_m_u8CalledLen,cfg_IniName);
	WritePrivateProfileString("CMD","m_u8CalledTimeOut", cfg_Acs_m_u8CalledTimeOut,cfg_IniName);
	WritePrivateProfileString("CMD","m_u8NeedCaller", cfg_Acs_m_u8NeedCaller,cfg_IniName);
	WritePrivateProfileString("CMD","m_u8AreaCodeLen", cfg_Acs_m_u8AreaCodeLen,cfg_IniName);
	WritePrivateProfileString("CMD","m_u8KA", cfg_Acs_m_u8KA,cfg_IniName);
	WritePrivateProfileString("CMD","m_u8KD", cfg_Acs_m_u8KD,cfg_IniName);
	WritePrivateProfileString("CMD","m_u8ControlMode", cfg_Acs_m_u8ControlMode,cfg_IniName);
	WritePrivateProfileString("CMD","m_u8CountryCode", cfg_Acs_m_u8CountryCode,cfg_IniName);
	

}

void	InitTextBox(void)
{
	char	TmpStr[256];

	pdlg->GetDlgItem ( IDC_EDIT_SERVER_IPADDR )->SetWindowText ( cfg_ServerID.m_s8ServerIp );

	sprintf ( TmpStr, "%d", cfg_ServerID.m_u32ServerPort );
	pdlg->GetDlgItem ( IDC_EDIT_SERVER_IPPORT )->SetWindowText ( TmpStr );

	if ( cfg_iAutoScroll == 0 )
		((CButton *)pdlg->GetDlgItem ( IDC_CHECK_AutoScroll ))->SetCheck(0);
	else
		((CButton *)pdlg->GetDlgItem ( IDC_CHECK_AutoScroll ))->SetCheck(1);

	pdlg->GetDlgItem ( IDC_EDIT_CALLINGNUM )->SetWindowText ( cfg_CallingNum );
	pdlg->GetDlgItem ( IDC_EDIT_CALLEDNUM )->SetWindowText ( cfg_CalledNum );

	pdlg->GetDlgItem ( IDC_EDIT_PLAY )->SetWindowText ( cfg_PlayFileName );
	pdlg->GetDlgItem ( IDC_EDIT1_RECORD )->SetWindowText ( cfg_RecordFileName );

	pdlg->GetDlgItem ( IDC_EDIT_SENDFAX )->SetWindowText ( cfg_SendFaxName );
	pdlg->GetDlgItem ( IDC_EDIT_RECEIVEFAX )->SetWindowText ( cfg_ReceiveFaxName );
	
	sprintf ( TmpStr, "%d", cfg_iIPPort );
	pdlg->GetDlgItem ( IDC_EDIT_CALLEE_PORT )->SetWindowText (TmpStr  );

	pdlg->GetDlgItem ( IDC_EDIT_CALLEE_ADDR )->SetWindowText (cfg_IPIP  );

	if ( cfg_s32DebugOn == 0 )
		((CButton *)pdlg->GetDlgItem (IDC_CHECK_DEBUG))->SetCheck ( 0 ) ;
	else
		((CButton *)pdlg->GetDlgItem (IDC_CHECK_DEBUG))->SetCheck ( 1 ) ;

	/////////////////////////////////////////////////
	pdlg->GetDlgItem ( IDC_EDIT_PLAYCSP_FILE )->SetWindowText ( cfg_CSPPlayFileName );
	pdlg->GetDlgItem ( IDC_EDIT_RECCSP_FILE )->SetWindowText ( cfg_CSPRecordFileName );
	pdlg->GetDlgItem ( IDC_EDIT_DSPIP )->SetWindowText ( cfg_CSPIP );

	sprintf ( TmpStr, "%d", cfg_CSPPort );
	pdlg->GetDlgItem ( IDC_EDIT_DSPPORT )->SetWindowText ( TmpStr );

	((CButton *)pdlg->GetDlgItem ( IDC_AUTORTP ))->SetCheck ( cfg_s32AutoRtp );

	/////////////////////////////////////////////////
}

void	FetchFromText(void)
{
	char	TmpStr[256];

	pdlg->GetDlgItem ( IDC_EDIT_SERVER_IPADDR )->GetWindowText ( cfg_ServerID.m_s8ServerIp, 30 );

	pdlg->GetDlgItem ( IDC_EDIT_SERVER_IPPORT )->GetWindowText ( TmpStr, 30 );
	sscanf ( TmpStr, "%d", &cfg_ServerID.m_u32ServerPort);


	pdlg->GetDlgItem ( IDC_EDIT_CALLEE_PORT )->GetWindowText ( TmpStr, 30 );
	sscanf ( TmpStr, "%d", &cfg_iIPPort);

	((CEdit*) pdlg->GetDlgItem ( IDC_EDIT_CALLEE_ADDR ))->GetWindowText ( cfg_IPIP, ACS_MAX_CALL_NUM-1 );

	if ( ((CButton *)pdlg->GetDlgItem ( IDC_CHECK_AutoScroll ))->GetCheck() == 1 )
		cfg_iAutoScroll = 1;
	else
		cfg_iAutoScroll = 0;

	cfg_iComboDevice = iComboDeviceSelect;
	cfg_iComboParam = iComboParam;
	cfg_iComboGetParam = iComboGetParam;

	((CEdit*) pdlg->GetDlgItem ( IDC_EDIT_CALLINGNUM ))->GetWindowText ( cfg_CallingNum, ACS_MAX_CALL_NUM-1 );
	((CEdit*) pdlg->GetDlgItem ( IDC_EDIT_CALLEDNUM ))->GetWindowText ( cfg_CalledNum, ACS_MAX_CALL_NUM-1 );

	((CEdit*) pdlg->GetDlgItem ( IDC_EDIT_PLAY ))->GetWindowText ( cfg_PlayFileName, MAX_FILE_NAME_LEN-1 );
	((CEdit*) pdlg->GetDlgItem ( IDC_EDIT1_RECORD ))->GetWindowText ( cfg_RecordFileName, MAX_FILE_NAME_LEN-1 );

	((CEdit*) pdlg->GetDlgItem ( IDC_EDIT_PLAYCSP_FILE ))->GetWindowText ( cfg_CSPPlayFileName, MAX_FILE_NAME_LEN-1 );
	((CEdit*) pdlg->GetDlgItem ( IDC_EDIT_RECCSP_FILE ))->GetWindowText ( cfg_CSPRecordFileName, MAX_FILE_NAME_LEN-1 );
	((CEdit*) pdlg->GetDlgItem ( IDC_EDIT_DSPIP ))->GetWindowText ( cfg_CSPIP, MAX_FILE_NAME_LEN-1 );
	((CEdit*) pdlg->GetDlgItem ( IDC_EDIT_DSPPORT ))->GetWindowText ( TmpStr, MAX_FILE_NAME_LEN-1 );
	sscanf(TmpStr, "%d", &cfg_CSPPort);

	((CEdit*) pdlg->GetDlgItem ( IDC_EDIT_SENDFAX ))->GetWindowText ( cfg_SendFaxName, MAX_FILE_NAME_LEN-1 ); cfg_SendFaxName[100] = 0;
	((CEdit*) pdlg->GetDlgItem ( IDC_EDIT_RECEIVEFAX ))->GetWindowText ( cfg_ReceiveFaxName, MAX_FILE_NAME_LEN-1 ); cfg_ReceiveFaxName[100] = 0;

	if ( ((CButton *)pdlg->GetDlgItem (IDC_CHECK_DEBUG))->GetCheck ( ) )
		cfg_s32DebugOn = 1;
	else
		cfg_s32DebugOn = 0;

	cfg_s32AutoRtp = ((CButton *)pdlg->GetDlgItem (IDC_AUTORTP))->GetCheck ( );
}

// ----------
void	InitListMsg(void)
{
	int	i = pdlg->m_ListMsg.GetHorizontalExtent ( );

	pdlg->m_ListMsg.SetHorizontalExtent ( i + 1000 );
}

void	InitComboBox(void)
{
	char	TmpStr[256];

	// init m_ComboDevice
	pdlg->m_ComboDevice.AddString ( "All Type" );
	pdlg->m_ComboDevice.AddString ( "" );				
	pdlg->m_ComboDevice.AddString ( "0x02 - VOICE" );		
	pdlg->m_ComboDevice.AddString ( "0x03 - FAX" );			
	pdlg->m_ComboDevice.AddString ( "0x04 - DIGITAL_PORT" );	
	pdlg->m_ComboDevice.AddString ( "0x05 - INTERFACE_CH" );
	pdlg->m_ComboDevice.AddString ( "0x06 - DSS1_LINK" );	
	pdlg->m_ComboDevice.AddString ( "0x07 - SS7_LINK" );	
	pdlg->m_ComboDevice.AddString ( "0x08 - BOARD" );		
	pdlg->m_ComboDevice.AddString ( "0x09 - CTBUS_TS" );	
	pdlg->m_ComboDevice.AddString ( "0x0A - RTP" );			
	pdlg->m_ComboDevice.AddString ( "" );				
	pdlg->m_ComboDevice.AddString ( "0x0C - CONFERENCE" );	
	pdlg->m_ComboDevice.AddString ( "0x0D - VIDEO" );	
	pdlg->m_ComboDevice.AddString ( "0x10 - CTX" );
	pdlg->m_ComboDevice.AddString ( "0x11 - RTPX" );
	pdlg->m_ComboDevice.AddString ( "0x12 - VoIP" );
	pdlg->m_ComboDevice.AddString ( "0x1F - MediaEx" );

	iComboDeviceSelect = cfg_iComboDevice;
	pdlg->m_ComboDevice.SetCurSel ( iComboDeviceSelect );

	// init m_ComboMsg
	pdlg->m_ComboMsg.AddString ( "All Info" );
	pdlg->m_ComboMsg.AddString ( "1 - Function" );
	pdlg->m_ComboMsg.AddString ( "2 - Event" );
	pdlg->m_ComboMsg.AddString ( "3 - Other" );

	iComboMsgSelect = 0;
	pdlg->m_ComboMsg.SetCurSel ( iComboMsgSelect );

	// init m_ComboParam
	int i = 0;
	for ( i = 0; i < MAX_PARAMETER_TYPE ; i ++ )
	{
		sprintf ( TmpStr, "%2d - %s", i, ParamTypeStr[i] );
		pdlg->m_ComboParam.AddString ( TmpStr );
	}

	// init m_ComboGetParam
	for ( i = 0; i < MAX_GETPARAMETER_TYPE ; i ++ )
	{
		sprintf ( TmpStr, "%2d - %s", i, GetParamTypeStr[i] );
		pdlg->m_ComboGetParam.AddString ( TmpStr );
	}

	iComboParam = cfg_iComboParam;
	pdlg->m_ComboParam.SetCurSel ( iComboParam );
	iComboGetParam = cfg_iComboGetParam;
	pdlg->m_ComboGetParam.SetCurSel ( iComboGetParam );

		///////////////////////////////////////////////////////
	CComboBox * pCB;
	pCB = (CComboBox *)pdlg->GetDlgItem(IDC_COMBO_STOP_MEDIA_TYPE);
    if (NULL == pCB)
	{
		ASSERT(0);
		return;
	}

	pCB->InsertString(0, "Play Audio");
	pCB->InsertString(1, "Play Video");
	pCB->InsertString(2, "Play A&V");
	pCB->SetItemData( 0, 0);
	pCB->SetItemData( 1, 1);
	pCB->SetItemData( 2, 4);
	pCB->SetTopIndex(2);
	pCB->SetCurSel(2);

	///////////////////////////////////////////////////////////////////
	pCB = (CComboBox *)pdlg->GetDlgItem(IDC_COMBO_STOP_VMEDIA_TYPE);
    if (NULL == pCB)
	{
		ASSERT(0);
		return;
	}

	pCB->InsertString(0, "Record Audio");
	pCB->InsertString(1, "Record Video");
	pCB->InsertString(2, "Record A&V");
	pCB->SetItemData( 0, 0);
	pCB->SetItemData( 1, 1);
	pCB->SetItemData( 2, 4);
	pCB->SetTopIndex(2);
	pCB->SetCurSel(2);
	///////////////////////////////////////////////////////

}

void AddMsg ( int	iMsgType, char *str)
{
	char	TmpStr[512];
	static	int		iTotal_ListMsg = 0;
	static	int		iTotal_ListMsgHidden = 0;

	if(pdlg->m_ListMsg.GetCount() >= 1000)
	{
		pdlg->m_ListMsg.ResetContent();
	}

	sprintf ( TmpStr, "%d - %s", iMsgType, str );

	//pdlg->m_ListMsgHidden.AddString ( TmpStr );
	//iTotal_ListMsgHidden ++;

	//if ( ( iComboMsgSelect == 0 ) || (iComboMsgSelect == iMsgType ) )
	{
		pdlg->m_ListMsg.AddString ( TmpStr );
		iTotal_ListMsg ++;
		
		if ( cfg_iAutoScroll == 1 )
		{
			pdlg->m_ListMsg.SetCurSel (iTotal_ListMsg-1);
			pdlg->GetDlgItem ( IDC_EDIT_MsgDetail )->SetWindowText ( TmpStr );
		}
	
	}
}

void		InitDeviceInfo (void)
{
	char	TmpStr[256];
	int		i, iRow;

	pdlg->m_ListDevInfo.ResetContent ();

	iRow = pdlg->m_ComboDevice.GetCurSel ( ); 
	iComboDeviceSelect = iRow;
	if(iRow>=14 && iRow<=16)
		iRow = XMS_DEVMAIN_CTX+iRow-14;
	else if(iRow == 17)
		iRow = 0x1F;

	for ( i = 0; i < TotalDevRes; i ++ )
	{
		if ( ( iRow == 0 ) || (iRow == pDevRes[i].DevID.m_s16DeviceMain) )
		{
			sprintf ( TmpStr, "%3d - (%s)", i, GetString_DeviceAll(&pDevRes[i].DevID) );
			pdlg->m_ListDevInfo.AddString ( TmpStr ); 
		}
	}
}
// ----------


bool	InitSystem(void)
{
	RetCode_t	r;
	char		MsgStr[160];

	pdlg = (CXMSApi_TestDlg	*)theApp.m_pMainWnd;

	// Read From "Config.TXT"
	ReadFromConfig();

	// Init Combo Box
	InitComboBox();

	// Init m_ListMsg
	InitListMsg();

	// Init Conifg's text box
	InitTextBox();

	// init variable used by XMSApi_Test_Func.cpp
	InitVar_Func();

#ifdef	DEBUG_IN_HOME_NOTEBOOK
// ----- for-test-----
	typedef struct {
		Acs_Dev_List_Head_t		head;
		DeviceID_t		dev[32];
	} My_Struct;

	My_Struct	mmm;
	
	mmm.head.m_s32DeviceNum = 4;
	mmm.dev[0].m_s16DeviceMain = XMS_DEVMAIN_VOICE;
	mmm.dev[0].m_s8ModuleID = 1;
	mmm.dev[0].m_s16ChannelID = 1;
	mmm.dev[1].m_s16DeviceMain = XMS_DEVMAIN_VOICE;
	mmm.dev[1].m_s8ModuleID = 1;
	mmm.dev[1].m_s16ChannelID = 2;

	mmm.dev[2].m_s16DeviceMain = XMS_DEVMAIN_INTERFACE_CH;
	mmm.dev[2].m_s16DeviceSub = XMS_DEVSUB_E1_SS7_ISUP;
	mmm.dev[2].m_s8ModuleID = 1;
	mmm.dev[2].m_s16ChannelID = 8;
	mmm.dev[3].m_s16DeviceMain = XMS_DEVMAIN_INTERFACE_CH;
	mmm.dev[3].m_s16DeviceSub = XMS_DEVSUB_E1_SS7_ISUP;
	mmm.dev[3].m_s8ModuleID = 1;
	mmm.dev[3].m_s16ChannelID = 9;
void	AddDeviceRes ( Acs_Dev_List_Head_t *pAcsDevList );

	AddDeviceRes ( &mmm.head );
	InitDeviceInfo();

	bStartWorkFlag = true;

	return true;
// ----- end of for-test -----
#endif
	
	// now open ACS Server
	/*Invoke the acsOpenStream routine to create a connect to server*/
	r = XMS_acsOpenStream ( &g_acsHandle, 
						&cfg_ServerID,
						g_u8UnitID,		// App Unit ID 
						32,				// sendQSize, in K Bytes
						32,				// recvQSize, in K Bytes
						//cfg_s32DebugOn,	// Debug On/Off
						1,
						NULL);

	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_acsOpenStream(IP Addr : %s, port : %d) FAIL.", 
			r, cfg_ServerID.m_s8ServerIp, cfg_ServerID.m_u32ServerPort );

		MessageBox(NULL, MsgStr, "Init System", MB_OK ) ;
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
	else
	{
		sprintf ( MsgStr, "XMS_acsOpenStream(%s,%d) OK!", cfg_ServerID.m_s8ServerIp, cfg_ServerID.m_u32ServerPort );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}

	r = XMS_acsSetESR ( g_acsHandle, (EsrFunc)EvtHandler, 0, 1 );
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_acsSetESR() FAIL!", r );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
		return false;
	}
	else
	{
		sprintf ( MsgStr, "XMS_acsSetESR() OK!" );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}


    ServerID_t serverID;
	memset (&serverID, 0, sizeof(ServerID_t));
	strcpy ( serverID.m_s8ServerIp, cfg_ServerID.m_s8ServerIp );
	serverID.m_u32ServerPort = 9900;
	XMS_acsOpenStreamExt (g_acsHandle, &serverID, NULL);

	XMS_acsGetDeviceList ( g_acsHandle, NULL );

	bStartWorkFlag = false;

	return true;
}

void	ExitSystem(void) 
{
	// 
//	RetCode_t	r;

	bStartWorkFlag = false;

	for (int iDevice = 0; iDevice < MAX_DEVICE_ALLOW_OPEN; ++iDevice)
	{
		// opened already?
		if (!DevOpened[iDevice].bOpenFlag)
			continue;
		
		// send close device command
		XMS_ctsCloseDevice(g_acsHandle, &DevOpened[iDevice].DevID, NULL);
	}

	//r = XMS_acsCloseStream ( g_acsHandle, NULL );
	//Sleep(5000);

	// save to "config.txt"
	FetchFromText();
	WriteToConfig();
}

void	SelectOpenDevice(void)
{
	int		iRow = 0;
	char	TmpStr[256];
	
	iRow = pdlg->m_ListDevInfo.GetCurSel ();

	pdlg->m_ListDevInfo.GetText ( iRow, TmpStr );
	
	sscanf ( TmpStr, "%d", &iRow);

	iNowOpIndex = iRow;
	pdlg->GetDlgItem ( IDC_EDIT_NOW_OPEN_DEVICE )->SetWindowText ( GetString_DeviceAll(&pDevRes[iRow].DevID) );

}

void	SelectOpenedDevice(void)
{
	int		iRow;
	
	iRow = pdlg->m_ListDevOpened.GetCurSel ();
		
	if ( (iRow < 0) || (iRow >= TotalDevOpened) )
	{
		pdlg->GetDlgItem ( IDC_EDIT_DEVICE1 )->SetWindowText ( "" );
		pdlg->GetDlgItem ( IDC_EDIT_DEVICE3 )->SetWindowText ( "" );
	}
	else
	{
		/*if(DevOpened[iRow].DevID.m_s16DeviceMain == XMS_DEVMAIN_CTBUS_TS
			|| DevOpened[iRow].DevID.m_s16DeviceMain == XMS_DEVMAIN_VOIP)
		{
			//added by jerry Sep,25,2007
			//iOpenedIndex1 = iRow;

			iOpenedIndex3 = iRow;
			pdlg->GetDlgItem ( IDC_EDIT_DEVICE3 )->SetWindowText ( GetString_DeviceAll(&DevOpened[iOpenedIndex3].DevID) );
		}
		else*/
		{
			iOpenedIndex1 = iRow;
			pdlg->GetDlgItem ( IDC_EDIT_DEVICE1 )->SetWindowText ( GetString_DeviceAll(&DevOpened[iOpenedIndex1].DevID) );
			
			if ( (XMS_DEVMAIN_INTERFACE_CH == DevOpened[iOpenedIndex1].DevID.m_s16DeviceMain) 
			  && (XMS_DEVSUB_ANALOG_USER == DevOpened[iOpenedIndex1].DevID.m_s16DeviceSub) )
			{
				pdlg->GetDlgItem ( IDC_RADIO_CALLER_DTMF )->EnableWindow( 1 );
				pdlg->GetDlgItem ( IDC_RADIO_CALLER_FSK )->EnableWindow( 1 );
				((CButton *)pdlg->GetDlgItem ( IDC_RADIO_CALLER_DTMF ))->SetCheck ( 0 );
				((CButton *)pdlg->GetDlgItem ( IDC_RADIO_CALLER_FSK ))->SetCheck ( 1 );
			}
			else
			{
				pdlg->GetDlgItem ( IDC_RADIO_CALLER_DTMF )->EnableWindow( 0 );
				pdlg->GetDlgItem ( IDC_RADIO_CALLER_FSK )->EnableWindow( 0 );
			}
		}
	}
}

void	ExchangeDeviceIndex(void)
{
	int		i;

	// exchange iOpenedIndex1 & iOpenedIndex2
	i = iOpenedIndex1;
	iOpenedIndex1 = iOpenedIndex2;
	iOpenedIndex2 = i;

	if ( (iOpenedIndex1 < 0) || (iOpenedIndex1 >= TotalDevOpened) )
		pdlg->GetDlgItem ( IDC_EDIT_DEVICE1 )->SetWindowText ( "" );
	else
		pdlg->GetDlgItem ( IDC_EDIT_DEVICE1 )->SetWindowText ( GetString_DeviceAll(&DevOpened[iOpenedIndex1].DevID) );

	if ( (iOpenedIndex2 < 0) || (iOpenedIndex2 >= TotalDevOpened) )
		pdlg->GetDlgItem ( IDC_EDIT_DEVICE2 )->SetWindowText ( "" );
	else
		pdlg->GetDlgItem ( IDC_EDIT_DEVICE2 )->SetWindowText ( GetString_DeviceAll(&DevOpened[iOpenedIndex2].DevID) );
}

void	SelectComboDevice(void)
{
	InitDeviceInfo ();
}

void	RefreshListMsg (void)
{

}

void	SelectComboMsg(void)
{
	int		iRow;

	iRow = pdlg->m_ComboMsg.GetCurSel ( ); 

	RefreshListMsg();
}

// -----------------------------------------------------------------
char	FilePackDefaultPath[MAX_FILE_NAME_LEN+1] = ".";

void FetchPath ( char *FullName )
{
	strcpy ( FilePackDefaultPath, FullName );

	for ( int i = strlen(FilePackDefaultPath)-1; i >= 0; i -- ) {
		if ( FilePackDefaultPath[i] == '\\' ) {
			FilePackDefaultPath[i] = 0;
			break;
		}
	}
}

void	My_SelectFile ( char *FullFileName )
{

	char	TmpStr[100];
	char	TmpStr1[10] = "*.*";
	CFileDialog	m_FileSel(true);

	strcpy ( TmpStr, "*.*" );
	TmpStr1[strlen(TmpStr1)+1] = 0;		// need 2 NULL
	memcpy ( TmpStr+strlen(TmpStr)+1, TmpStr1, sizeof(TmpStr1) );

	FetchPath ( FullFileName );

	m_FileSel.m_ofn.lpstrFilter = TmpStr;
	m_FileSel.m_ofn.lpstrInitialDir = FilePackDefaultPath;

	int	rtn = m_FileSel.DoModal();

	if ( rtn == IDOK )
	{
		strcpy ( FullFileName, m_FileSel.GetPathName () );
	}
}

void	SelectSendFaxFile (void)
{
	char	TmpStr[256];

	pdlg->GetDlgItem ( IDC_EDIT_SENDFAX )->GetWindowText ( TmpStr, MAX_FILE_NAME_LEN-1 );

	My_SelectFile ( TmpStr );

	pdlg->GetDlgItem ( IDC_EDIT_SENDFAX )->SetWindowText ( TmpStr );

}

void	SelectReceiveFaxFile (void)
{
	char	TmpStr[256];

	pdlg->GetDlgItem ( IDC_EDIT_RECEIVEFAX )->GetWindowText ( TmpStr, MAX_FILE_NAME_LEN-1 );
	My_SelectFile ( TmpStr );
	pdlg->GetDlgItem ( IDC_EDIT_RECEIVEFAX )->SetWindowText ( TmpStr );

}

void	SelectPlayFile (void)
{
	char	TmpStr[256];

	pdlg->GetDlgItem ( IDC_EDIT_PLAY )->GetWindowText ( TmpStr, MAX_FILE_NAME_LEN-1 );

	My_SelectFile ( TmpStr );

	pdlg->GetDlgItem ( IDC_EDIT_PLAY )->SetWindowText ( TmpStr );

}

void	SelectRecordFile (int nEdit)
{
	char	TmpStr[256];

	pdlg->GetDlgItem ( nEdit )->GetWindowText ( TmpStr, MAX_FILE_NAME_LEN-1 );

	My_SelectFile ( TmpStr );

	pdlg->GetDlgItem ( nEdit )->SetWindowText ( TmpStr );
	
	if(nEdit == IDC_EDIT_RECCSP_FILE)
	{
		strcpy(g_szCSPRecordFile,TmpStr);
	}
}

DeviceID_t * GetCurrVocDev( DJ_S32 iIndex )
{
	DJ_U8 u8DSPID = 0;
	DJ_U16 u16ChID  = 0;

	if ( 0 != DevOpened[iIndex].DevID.m_s16DeviceMain && XMS_DEVMAIN_VOICE == DevOpened[iIndex].DevID.m_s16DeviceMain )
	{
		u8DSPID = DevOpened[iIndex].DevID.m_s8ModuleID;
		u16ChID  = DevOpened[iIndex].DevID.m_s16ChannelID;

		if ( 128 <= u8DSPID || 128 <= u16ChID )
		{
			return NULL;
		}

		return &DevOpened[iIndex].DevID;
	}
	else
		return NULL;
}

CSP_OPERATER* GetCurrVocCSPProperty(  )
{
	DJ_U8 u8DSPID = 0;
	DJ_U16 u16ChID  = 0;
	DJ_S32 iIndex = iOpenedIndex1;

	if ( 0 != DevOpened[iIndex].DevID.m_s16DeviceMain && XMS_DEVMAIN_VOICE == DevOpened[iIndex].DevID.m_s16DeviceMain )
	{
		u8DSPID = DevOpened[iIndex].DevID.m_s8ModuleID;
		u16ChID  = DevOpened[iIndex].DevID.m_s16ChannelID;

		if ( 128 <= u8DSPID || 128 <= u16ChID )
		{
			return NULL;
		}

		return &g_stVocCSPProperty[u8DSPID][u16ChID];
	}
	else
		return NULL;
}

CSP_OPERATER* GetVocCSPProperty( DJ_U8 u8DSPID, DJ_U16 u16ChID )
{
	if ( 128 <= u8DSPID || 128 <= u16ChID )
	{
		return NULL;
	}

	return &g_stVocCSPProperty[u8DSPID][u16ChID];
}

