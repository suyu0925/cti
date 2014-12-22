#ifndef _XMSAPI_TEST_SUB_H_
#define _XMSAPI_TEST_SUB_H_

//#define	DEBUG_IN_HOME_NOTEBOOK

#define	MSG_TYPE_ALL			0
#define	MSG_TYPE_FUNCTION		1
#define	MSG_TYPE_EVENT			2
#define	MSG_TYPE_OTHER			3

#define	MAX_FILE_NAME_LEN		256

#define	MAX_PARAMETER_TYPE		36  // author:chenz old value:35

#define	MAX_GETPARAMETER_TYPE	16


//operate CSP record or play property
typedef struct CSP_OPERATER_T
{
    DJ_U8      m_u8CSPPlayTaskID;
	DJ_U8      m_u8Ref[3];
	DJ_S32     m_cspPlay;
	DJ_S32     m_s32CSPRecControlType;
	FILE *     m_cspPlayFp;
	DeviceID_t m_PlayCSPDevID;
	CSPPlayProperty_t   m_PlayCSPProperty;
	DJ_S8      m_szCSPPlayFile[MAX_PATH];

	FILE *     m_cspRecordFp;
	DeviceID_t m_RecCSPDevID;
	RecordCSPProperty_t  m_RecCSPProperty;
    DJ_S8      m_szCSPRecordFile[MAX_PATH];
	
}CSP_OPERATER;

//this length must be referece to MAX_PARAMETER_TYPE 
enum
{
	SET_PARAM_TYPE_VOC_PARAM_SET   = 0,
	
	//1
	SET_PARAM_TYPE_E1_CAS_SET,
	SET_PARAM_TYPE_A_USER_SET,
	SET_PARAM_TYPE_A_TRUNK_SET, 
	SET_PARAM_TYPE_A_TRUNK_FLASH_EVENT,
	SET_PARAM_TYPE_A_REC_VOLTAGE_SET,
	SET_PARAM_TYPE_REC_MOD_MODE_SET,
	SET_PARAM_TYPE_VOIP_MIXER_SET,

	//7
	SET_PARAM_TYPE_BOARD_FSK_SET,
	SET_PARAM_TYPE_BOARD_FLASH_TIME_SET,
	SET_PARAM_TYPE_BOARD_GTD_SET,
	SET_PARAM_TYPE_BOARD_VSD_SET,
	SET_PARAM_TYPE_BOARD_GTG_SET,

	//12
	SET_PARAM_TYPE_BOARD_CONF_ACTIVE_DTT,  
	SET_PARAM_TYPE_BOARD_CLK,
	SET_PARAM_TYPE_BOARD_VAD_MIN_LEVEL,
	SET_PARAM_TYPE_BOARD_COMM_CFG,
	SET_PARAM_TYPE_BOARD_RESET_SET,


	SET_PARAM_TYPE_VOC_GTG_KEY_INTRPT,
	SET_PARAM_TYPE_FAX_TONE ,

	
	//19
	SET_PARAM_TYPE_FAX_SET_HEADER ,
	SET_PARAM_TYPE_FAX_ECM ,
	SET_PARAM_TYPE_FAX_BPS,
	SET_PARAM_TYPE_FAX_ADDFILE,
	SET_PARAM_TYPE_EM,
    
	//24
	SET_PARAM_TYPE_RTPX,
	SET_PARAM_TYPE_MEDIAEX_PARAM ,
	SET_PARAM_TYPE_CONF_PARAM,
	SET_PARAM_TYPE_SS7RAWFRAME_PARAM,  // author:chnez 
	SET_PARAM_TYPE_ACS_PARAM,          // author:chnez 
	SET_PARAM_TYPE_CAS_CMDPARAM,       // author:chnez 

	//30
	SET_PARAM_TYPE_DSS1_CALL_TYPE,
	SET_PARAM_TYPE_DSS1_APPENDCALLEE, 
	SET_PARAM_TYPE_DSS1_CALL_PARAM,
	SET_PARAM_TYPE_DSS1_ORICALLER,
	
	SET_PARAM_TYPE_OTHER  ,
};


// ----------------------------------------------------------
void	AddMsg ( int	iMsgType, char *str);
bool	InitSystem(void);
void	ExitSystem(void);

void	InitDeviceInfo (void);
void	SelectOpenDevice(void);
void	SelectOpenedDevice(void);

void	ExchangeDeviceIndex(void);
void	SelectComboDevice(void);
void	SelectComboMsg(void);

void	SelectSendFaxFile (void);
void	SelectReceiveFaxFile (void);

void	SelectPlayFile (void);
void	SelectRecordFile (int nEdit);
void	SelectBuildIndexFile (void);

void	My_SelectFile ( char *FullFileName );

DeviceID_t *   GetCurrVocDev( DJ_S32 iIndex );
CSP_OPERATER*  GetCurrVocCSPProperty(  );
CSP_OPERATER*  GetVocCSPProperty( DJ_U8 u8DSPID, DJ_U16 u16ChID );

#endif