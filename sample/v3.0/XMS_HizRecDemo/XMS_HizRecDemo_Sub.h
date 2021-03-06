#ifndef _XMS_HIZRECDEMO_SUB_H_
#define _XMS_HIZRECDEMO_SUB_H_

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"

#define	MAX_FILE_NAME_LEN		256

enum TRUNK_STATE {
	TRK_WAITOPEN,
	TRK_FREE,			
	TRK_OFFHOOK,
//	TRK_ACCOUNT,
//	TRK_PASSWORD,
//	TRK_SELECT,		
//	TRK_PLAYRESULT,
//	TRK_RECORDFILE,
//	TRK_PLAYRECORD,	
//	TRK_HANGON,

	// new add for XMS
//	TRK_WAIT_ANSWERCALL,
//	TRK_WAIT_LINKOK,

	TRK_WAIT_REMOVE,
};

typedef struct
{
	// ----------------
	DeviceID_t	deviceID;
	int			iSeqID;
	int			iModSeqID;
	int			iLineState;

	DeviceID_t	VocDevID;
	DJ_U8		u8PlayTag;

	// -----------------
	TRUNK_STATE	State;

	int		DtmfCount;
	char	DtmfBuf[32];

	char CallerCode[20];
	char CalleeCode[20];

} TRUNK_STRUCT;

enum VOICE_STATE {
	VOC_WAITOPEN,
	VOC_FREE,
	VOC_USED,

	VOC_WAIT_REMOVE
} ;

enum BOARD_TYPE
{
	BOARD_TYPE_A = 0,
	BOARD_TYPE_D = 1,
};

typedef struct
{
	// ----------------
	DeviceID_t	deviceID;
	int			iSeqID;

	DeviceID_t	UsedDevID;

	// ----------------
	VOICE_STATE	State;


} VOICE_STRUCT;

typedef struct
{
	// ----------------
	DeviceID_t	deviceID;
	int			iSeqID;
	bool		bOpenFlag;		// flag of OpenDevice OK

	//
	DJ_U8		u8E1Type;
	DJ_S32		s32AlarmVal;
} PCM_STRUCT;

// ----- decalure function -----
bool	InitSystem(void);
void	ExitSystem(void); 

void	AddMsg ( char *str);

void	OpenAllDevice_Dsp ( DJ_S8 s8DspModID );
void	CloseAllDevice_Dsp ( DJ_S8 s8DspModID );
void	ReOpen_AllDevice (void);

void	HandleDevState ( Acs_Evt_t *pAcsEvt );

void	InitTrunkChannel ( TRUNK_STRUCT *pOneTrunk );
void	ReDrawAll (void);
void	OpenDeviceOK ( DeviceID_t *pDevice );
void	CloseDeviceOK ( DeviceID_t *pDevice );

void	Remove_OneDsp(void);

void	My_BuildIndex ( DeviceID_t	*pVocDevID );

DJ_S32	 PlayFile ( DeviceID_t	*pVocDevID, DJ_S8 *s8FileName, DJ_U8 u8PlayTag, bool bIsQueue = false );
DJ_S32	 PlayIndex ( DeviceID_t	*pVocDevID, DJ_U16 u16Index, DJ_U8 u8PlayTag, bool bIsQueue );

void	TrunkWork ( TRUNK_STRUCT *pOneTrunk, Acs_Evt_t *pAcsEvt );

void	Change_State ( TRUNK_STRUCT *pOneTrunk, TRUNK_STATE NewState );
void	Change_Voc_State ( VOICE_STRUCT *pOneVoice, VOICE_STATE NewState );

char My_GetDtmfCode ( Acs_Evt_t *pAcsEvt );
char *My_GetFskCode ( Acs_Evt_t *pAcsEvt );
int	 SearchOneRecordVoice (  TRUNK_STRUCT *pOneTrunk, DeviceID_t *pFreeVocDeviceID );
int  SearchOneFreeVoice (  TRUNK_STRUCT *pOneTrunk, DeviceID_t *pFreeVocDeviceID );
void	PrepareForCallerID ( TRUNK_STRUCT *pOneTrunk );

#endif