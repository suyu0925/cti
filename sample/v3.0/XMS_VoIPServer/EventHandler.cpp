
#include "stdafx.h"
#include "EventHandler.h"

// user state
LPCTSTR s_UserState[]=
{
    _T("N/A"),
	_T("REGISTED"),
	_T("UNREGISTED"),
	_T("INITIATED"),
	_T("ALERTING"),
	_T("HOLD"),
	_T("CONNECTED")
};
// call state
LPCTSTR s_CallState[]=
{
    _T("N/A"),
	_T("ORIGINATED"),
	_T("DELIVERED"),
	_T("ALERTING"),
	_T("ESTABLISHED"),
	_T("ANSWER_CALL"),
	_T("CONNECTED"),
	_T("TRANSLATE"),
	_T("PLAYING"),
	_T("PLAY END")
};

#define RTP_PORT_BASE(portbase, unit_id)	(DJ_U16)(portbase + (unit_id-1)*100)
#define RTP_IP(unit_id)				(g_config_rtp.u32GatewayWANIP ? g_config_rtp.u32GatewayWANIP : g_dsp_info[unit_id-1].ip)
//////////////////////////////////////////////////////////////////////////
// rtp capability set
// rtp codec capability struct
typedef struct ITP_RTP_CODEC_TAG
{
    DJ_U8	u8CodecType;		// codec type
    DJ_U8	u8PayloadType;		// rtp payload type
    DJ_S8	s8MimeSubtype[10];	// MIME subtype name (used as sdp encoding name)
    DJ_S8	s8H245Name[50];		// h.245 capability name
} ITP_RTP_CODEC;
ITP_RTP_CODEC g_rtp_codec[] =
{
    // audio capabilities
    {	// g.711 u-law
	VOIP_MEDIA_AUDIO_PCMU,	// media id
	    0,						// rtp payload type
	    "PCMU",					// MIME subtype name
	    "g711Ulaw64k"			// h.245 capability name
    },
    {	// g.711 a-law
	    VOIP_MEDIA_AUDIO_PCMA,	// media id
		8,						// rtp payload type
		"PCMA",					// MIME subtype name
		"g711Alaw64k"			// h.245 capability name
	},
	{	// g.723
		VOIP_MEDIA_AUDIO_G723,	// media id
		    4,						// rtp payload type
		    "G723",					// MIME subtype name
		    "g7231"					// h.245 capability name
	    },
	    {	// g.729
		    VOIP_MEDIA_AUDIO_G729,	// media id
			18,						// rtp payload type
			"G729",					// MIME subtype name
			"g729"					// h.245 capability name (prefix for g729, g729AnnexA, g729wAnnexB, g729AnnexAwAnnexB)
		},
		{	// amr-nb
			VOIP_MEDIA_AUDIO_AMR,	// media id
			    96,						// rtp payload type (dynamic)
			    "AMR",					// MIME subtype name
			    "amr"					// h.245 capability name
		    },
		    /*	{	// t.38/rtp
		    VOIP_MEDIA_AUDIO_T38,	// media id
		    97,						// rtp payload type (dynamic)
		    "t38",					// MIME subtype name
		    "t38fax"				// h.245 capability name
},*/
// video capabilities
		    {	// h.261
			    VOIP_MEDIA_VIDEO_H261,	// media id
				31,						// rtp payload type
				"H261",					// MIME subtype name
				"h261VideoCapability"	// h.245 capability name 
			},
			{	// h.263
				VOIP_MEDIA_VIDEO_H263,	// media id
				    34,						// rtp payload type
				    "H263",					// MIME subtype name
				    "h263VideoCapability"	// h.245 capability name 
			    },
			    {	// h.263+
				    VOIP_MEDIA_VIDEO_H263P,	// media id
					100,					// rtp payload type (dynamic)
					"H263-1998",			// MIME subtype name
					"h263VideoCapability98"	// h.245 capability name 
				},
				{	// mpeg-4/visual
					VOIP_MEDIA_VIDEO_MPEG4,	// media id
					    101,					// rtp payload type (dynamic)
					    "MP4V-ES",				// MIME subtype name
					    "genericVideoCapability"// h.245 capability name 
				    },
				    {	// h.264
					    VOIP_MEDIA_VIDEO_H264,	// media id
						102,					// rtp payload type (dynamic)
						"H264",					// MIME subtype name
						"h264VideoCapability"	// h.245 capability name 
					},
					// image capabilities
					{	// t.38/udptl
						VOIP_MEDIA_IMAGE_T38,	// media id
						    0,						// no payload type for t.38/udptl
						    "t38",					// MIME subtype name
						    "t38fax"				// h.245 capability name
					    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void djPrint(int nPort, const char *format,...)
{
    char buf[1024];
    int	nCnt	= 0;
    memset(buf, 0, sizeof(buf) );
    
    // 打印时间头
    nCnt	= CDJLog::GetLog()->PrintTime( buf, 3 );
    // 打印内容
    va_list ap;
    va_start( ap,format );
    nCnt	+= vsprintf( &buf[nCnt], format , ap );
    va_end( ap );
    // 打印'\0'
    DJ_ASSERT( nCnt< 1024 );
    buf[nCnt]	= '\0';
    nCnt++;
    
    CDJLog::GetLog()->Print(nPort, buf ,nCnt);
}

void djPrint(int nPort, int nID, int nCnt, ...)
{
    char* ptr	= NULL;
    
    // 打印内容
    va_list ap;
    va_start( ap,nCnt );
    for( int i= 0;i< nCnt;i++ )
    {
	ptr	= va_arg( ap, char* );
	CDJLog::GetLog()->Print(nPort, nID, i+1, ptr);
    }
    va_end( ap );
}
// CDJLog::CDJLog-------------------------------------------------------------------------------------------
CDJLog::CDJLog()
{
}
// CDJLog::~CDJLog-------------------------------------------------------------------------------------------
CDJLog::~CDJLog()
{
}
// CDJLog::GetLog-------------------------------------------------------------------------------------------
CDJLog* CDJLog::GetLog()
{
    static CDJLog  s_log;
    return &s_log;
}
// CDJLog::Print-------------------------------------------------------------------------------------------
BOOL CDJLog::Print(int nPort, const char *pData, int nCnt)
{
    if( NULL == pData || nCnt<= 0 )	
	return FALSE;
    
    int	nIndex	= 0;
    char buf[10]	= {0};
    const char* ptr	= pData;
    nIndex	= m_tEvent->GetItemCount();
    sprintf(buf, "%04d", nIndex+1);
    m_tEvent->InsertItem(nIndex, buf);
    switch(nPort)
    {
    case DJ_LEVEL_LOG:
	m_tEvent->SetItemText(nIndex, 1, _T("LOG"));
	break;
    case DJ_LEVEL_WARN:
	m_tEvent->SetItemText(nIndex, 1, _T("WARN"));
	break;
    case DJ_LEVEL_ERR:
	m_tEvent->SetItemText(nIndex, 1, _T("ERROR"));
	break;
    default:
	break;
    }
    
    m_tEvent->SetItemText(nIndex, 2, pData);
    
    return TRUE;
}

BOOL CDJLog::Print(int nPort, int nID, int nItem, const char *pData)
{
    int	nIndex	= 0;
    char buf[10]	= {0};
    const char* ptr	= pData;
    CListCtrl*	pList	= NULL;
    switch(nPort)
    {
    case DJ_PORT_USER:
	{
	    pList	= m_tUser;			
	}
	break;
    case DJ_PORT_DEVICE:
	{
	    pList	= m_tDevice;
	}
	break;
    case DJ_PORT_CALL:
	{
	    pList	= m_tCall;
	}
	break;
    case DJ_PORT_EVENT:
	{
	    pList	= m_tEvent;
	}
	break;
    default:
	return FALSE;
    }
    
    nIndex	= pList->GetItemCount();
    if( nID>nIndex )
    {
	DJ_ASSERT( nItem == 1 );
	while( nIndex<nID )
	{
	    sprintf(buf, "%04d", nIndex+1);
	    pList->InsertItem(nID, buf);
	    pList->SetItemText(nID-1, nItem, pData);
	    nIndex++;
	}
    }
    else
    {
	pList->SetItemText(nID-1, nItem, pData);
    }
    
    return TRUE;
}
// CDJLog::PrintTime-------------------------------------------------------------------------------------------
int CDJLog::PrintTime( char *pTime, int iTimeFlag )
{
    time_t curr_time = time(NULL);
    struct tm *pt = NULL;
    pt = localtime(&curr_time);
    if( !pt )	return 0;
    
    int n	= 0;
    switch( iTimeFlag )
    {
    case 1:
	n	= sprintf( pTime ,"%04d/%02d/%02d %02d:%02d:%02d ", pt->tm_year+1900, pt->tm_mon+1 ,pt->tm_mday ,pt->tm_hour ,pt->tm_min ,pt->tm_sec );
	break;
    case 2:
	n	= sprintf( pTime ,"/%02d/%02d %02d:%02d:%02d ", pt->tm_mon+1 ,pt->tm_mday ,pt->tm_hour ,pt->tm_min ,pt->tm_sec );
	break;
    case 3:
	n	= sprintf( pTime ,"%02d:%02d:%02d ", pt->tm_hour ,pt->tm_min ,pt->tm_sec );
	break;
    default:
	break;
    }
    
    return n;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// CDJXms
CDJXms::CDJXms()
: g_acsHandle(NULL)
, m_nID(0)
, m_bCanOpen(FALSE)
, m_voip(NULL)
, m_rtp(NULL)
, m_voice(NULL)
, m_cntVoip(0)
, m_cntVoipUsed(0)
, m_cntRtp(0)
, m_cntRtpUsed(0)
, m_cntVoice(0)
, m_cntVoiceUsed(0)
, m_pDevBuf(NULL)
{
    
}
// CDJXms::~CDJXms-------------------------------------------------------------------------------------------
CDJXms::~CDJXms()
{
    CloseSystem();
}
// CDJXms::Print-------------------------------------------------------------------------------------------
void CDJXms::Print(DJ_U32 u32Type)
{
    char strSum[64]	= {0};
    char strUsed[64]	= {0};
    switch( u32Type )
    {
    case XMS_DEVMAIN_VOIP:
	{
	    itoa(m_cntVoip, strSum, 10);
	    itoa(m_cntVoipUsed, strUsed, 10);
	    djPrint(DJ_PORT_DEVICE, 1, 4, "VOIP", strSum, strSum, strUsed);
	}
	break;
    case XMS_DEVMAIN_RTP:
	{
	    // print
	    itoa(m_cntRtp, strSum, 10);
	    itoa(m_cntRtpUsed, strUsed, 10);
	    djPrint(DJ_PORT_DEVICE, 2, 4, "RTP", strSum, strSum, strUsed);
	}
	break;
    case XMS_DEVMAIN_VOICE:
	{
	    // voice
	    itoa(m_cntVoice, strSum, 10);
	    itoa(m_cntVoiceUsed, strUsed, 10);
	    djPrint(DJ_PORT_DEVICE, 3, 4, "VOICE", strSum, strSum, strUsed);
	}
	break;
    default:
	break;
    }
}
// CDJXms::CloseSystem-------------------------------------------------------------------------------------------
void CDJXms::CloseSystem()
{
    RetCode_t ret	= 0;
    // close device
    if( NULL != m_pDevBuf )
    {
	for( DJ_U32 iDevice = 0;iDevice< DJ_MAX_DEVICE_BUF;iDevice++ )
	{
	    delete m_pDevBuf[iDevice];
	}
	delete [] m_pDevBuf;
    }
    m_pDevBuf	= NULL;
    
    m_voip		= NULL;
    m_rtp		= NULL;
    m_voice		= NULL;
    
    m_cntVoip		= 0;
    m_cntRtp		= 0;
    m_cntVoice		= 0;
    Sleep(50);
    // close XMS service	
    ret = XMS_acsCloseStream(g_acsHandle, NULL);
    g_acsHandle = NULL;
    m_bCanOpen	= FALSE;
}
// CDJXms::InitSystem-------------------------------------------------------------------------------------------
BOOL CDJXms::InitSystem(unsigned int nId, const char* strServerIP, const int strServerPort, const char* strUserName, const char* strPassword)
{
    // clear system
    if( NULL != g_acsHandle )
    {
	CloseSystem();
    }
    DJ_ASSERT(g_acsHandle == NULL);
    // init device buf
    m_pDevBuf	= new CDJDevice*[DJ_MAX_DEVICE_BUF];
    DJ_ASSERT(NULL != m_pDevBuf);
    memset( m_pDevBuf, 0, sizeof(CDJDevice*)*DJ_MAX_DEVICE_BUF);
    /*for( DJ_U32 iDevice= 0;iDevice< DJ_MAX_DEVICE_BUF;iDevice++ )
    {
    m_pDevBuf[iDevice]	= NULL;
}*/
    // init id
    m_nID	= nId;
    // init XMS service
    ServerID_t serverID;
    strcpy(serverID.m_s8ServerIp, strServerIP);
    serverID.m_u32ServerPort = strServerPort;
    strcpy(serverID.m_s8UserName, strUserName);
    strcpy(serverID.m_s8UserPwd, strPassword);
    
    // connect to XMS service
    RetCode_t ret = XMS_acsOpenStream(&g_acsHandle, &serverID, m_nID, 128, 32, FALSE, NULL);
    if (ret < 0 || g_acsHandle == NULL)
    {
	return FALSE;
    }
    // set XMS event handler
    ret = XMS_acsSetESR(g_acsHandle, EventHandler, NULL, TRUE);
    
    // get device list
    ret = XMS_acsGetDeviceList(g_acsHandle, NULL);
    
    return TRUE;
}
// CDJXms::GetDeviceItem-------------------------------------------------------------------------------------------
CDJDevice* CDJXms::GetDeviceItem( const DeviceID_t *pDevice )
{
    CDJDevice*	pTmp	= NULL;
    switch(pDevice->m_s16DeviceMain)
    {
    case XMS_DEVMAIN_VOIP:
	pTmp	= GetDeviceItem(m_voip, pDevice->m_s8ModuleID, pDevice->m_s16ChannelID);
	break;
    case XMS_DEVMAIN_RTP:
	pTmp	= GetDeviceItem(m_rtp, pDevice->m_s8ModuleID, pDevice->m_s16ChannelID);
	break;
    case XMS_DEVMAIN_VOICE:
	pTmp	= GetDeviceItem(m_voice, pDevice->m_s8ModuleID, pDevice->m_s16ChannelID);
	break;
    default:
	break;
    }
    
    return pTmp;
}
// CDJXms::GetDeviceItem-------------------------------------------------------------------------------------------
CDJDevice* CDJXms::GetDeviceItem( CDJDevice* pDevice, DJ_S8 s8ModuleID, DJ_S16 s16ChannelID )
{
    if( NULL == pDevice ) return NULL;
    
    CDJDevice* pTmp	= pDevice;
    while(NULL != pTmp)
    {
	if( pTmp->m_device.m_s8ModuleID == s8ModuleID 
	    && pTmp->m_device.m_s16ChannelID == s16ChannelID 
	    )
	{
	    return pTmp;
	}
	
	pTmp	= pTmp->m_next;
    }
    
    return NULL;
}
// CDJXms::EventHandler-------------------------------------------------------------------------------------------
DJ_Void CDJXms::EventHandler(DJ_U32 u32EsrParam)
{
    Acs_Evt_t *pAcsEvt = (Acs_Evt_t *)u32EsrParam;
    CDJXms* xms	= &CDJApp::GetApp()->m_xms;
    // dispatch event by type
    switch (pAcsEvt->m_s32EventType)
    {
    case XMS_EVT_OPEN_STREAM:
	xms->OnOpenStream(pAcsEvt);
	break;
	
    case XMS_EVT_QUERY_DEVICE:
	xms->OnQueryDevice(pAcsEvt);
	break;
	
    case XMS_EVT_QUERY_DEVICE_END:
	xms->OnQueryDeviceEnd(pAcsEvt);
	break;
    default:
	{
	    CDJDevice* pDevice	= xms->GetDeviceItem(&pAcsEvt->m_DeviceID);
	    if( NULL != pDevice )
	    {
		if( pAcsEvt->m_s32EventType == XMS_EVT_OPEN_DEVICE )
		{
		    if( pAcsEvt->m_DeviceID.m_s16DeviceMain == XMS_DEVMAIN_VOICE )
		    {
			pDevice->m_device	= pAcsEvt->m_DeviceID;
		    }
		    else
		    {
			pDevice->m_device	= pAcsEvt->m_DeviceID;
		    }
		}
		pDevice->SendMsg(pAcsEvt->m_s32EventType, FetchEventData(pAcsEvt));
	    }
	}
	break;
    }
}
// CDJXms::AllocDevice-------------------------------------------------------------------------------------------
CDJDevice* CDJXms::AllocDevice(DJ_U32 u32Type, DJ_U32 nID)
{
    DJ_U32 iDevice		= 0;
    CDJDevice*	pDevice	= NULL;
    switch( u32Type )
    {
    case XMS_DEVMAIN_VOIP:
	{
	    pDevice	= m_voip;
	    for (iDevice = 0; iDevice < m_cntVoip; ++iDevice)
	    {
		if( nID == 0 )
		{
		    if( !pDevice->IsUsed() )
		    {
			pDevice->SetUsed(TRUE);
			m_cntVoipUsed++;
			break;
		    }
		}
		else
		{
		    if( pDevice->GetID() == nID )
		    {
			pDevice->SetUsed(TRUE);
			m_cntVoipUsed++;
			break;
		    }
		}
		pDevice	= pDevice->m_next;
	    }
	}
	break;
    case XMS_DEVMAIN_RTP:
	{
	    pDevice	= m_rtp;
	    for (iDevice = 0; iDevice < m_cntRtp; ++iDevice)
	    {
		if( nID == 0 )
		{
		    if( !pDevice->IsUsed() )
		    {
			pDevice->SetUsed(TRUE);
			m_cntRtpUsed++;
			break;
		    }
		}
		else
		{
		    if( pDevice->GetID() == nID )
		    {
			pDevice->SetUsed(TRUE);
			m_cntRtpUsed++;
			break;
		    }
		}
		pDevice	= pDevice->m_next;
	    }
	}
	break;
    case XMS_DEVMAIN_VOICE:
	{
	    pDevice	= m_voice;
	    for (iDevice = 0; iDevice < m_cntVoice; ++iDevice)
	    {
		if( nID == 0 )
		{
		    if( !pDevice->IsUsed() )
		    {
			pDevice->SetUsed(TRUE);
			m_cntVoiceUsed++;
			break;
		    }
		}
		else
		{
		    if( pDevice->GetID() == nID )
		    {
			pDevice->SetUsed(TRUE);
			m_cntVoiceUsed++;
			break;
		    }
		}
		pDevice	= pDevice->m_next;
	    }
	}
	break;
    default:
	DJ_ASSERT(FALSE);
	break;
    }
    // print
    Print(u32Type);
    
    return pDevice;
}
// CDJXms::ReleaseDevice-------------------------------------------------------------------------------------------
void CDJXms::ReleaseDevice( DJ_U32 u32Type, DJ_U32 nID )
{
    CDJDevice* 	pDevice	= NULL;
    DJ_U32 iDevice		= 0;
    switch( u32Type )
    {
    case XMS_DEVMAIN_VOIP:
	{
	    pDevice	= m_voip;
	    for (iDevice = 0; iDevice < m_cntVoip; ++iDevice)
	    {
		if( pDevice->GetID() == nID )
		{
		    if( pDevice->IsUsed() )
		    {
			pDevice->SetUsed(FALSE);
			m_cntVoipUsed--;
		    }
		    break;
		}
		pDevice	= pDevice->m_next;
	    }
	}
	break;
    case XMS_DEVMAIN_RTP:
	{
	    pDevice	= m_rtp;
	    for (iDevice = 0; iDevice < m_cntRtp; ++iDevice)
	    {
		if( pDevice->GetID() == nID )
		{
		    if( pDevice->IsUsed() )
		    {
			pDevice->SetUsed(FALSE);
			m_cntRtpUsed--;
		    }
		    break;
		}
	    }
	}
	break;
    case XMS_DEVMAIN_VOICE:
	{
	    pDevice	= m_voice;
	    for (iDevice = 0; iDevice < m_cntVoice; ++iDevice)
	    {
		if( pDevice->GetID() == nID )
		{
		    if( pDevice->IsUsed() )
		    {
			pDevice->SetUsed(FALSE);
			m_cntVoiceUsed--;
		    }
		    break;
		}
		pDevice	= pDevice->m_next;
	    }
	}
	break;
    default:
	DJ_ASSERT(FALSE);
	break;
    }
    // print
    Print(u32Type);
}
// CDJXms::OnOpenStream-------------------------------------------------------------------------------------------
void CDJXms::OnOpenStream(Acs_Evt_t *pAcsEvt)
{
}
// CDJXms::InsertDevice-------------------------------------------------------------------------------------------
DJ_U32 CDJXms::InsertDevice(CDJDevice* pDevice, DJ_S32 s32Type)
{
    if( NULL == m_pDevBuf || NULL == pDevice )
    {
	return -1;
    }
    // get free device slot
    DJ_U16 i	= 0;
    for( ;i< DJ_MAX_DEVICE_BUF; i++ )
    {
	if( NULL == m_pDevBuf[i] )
	{
	    break;
	}
    }
    if( i>= DJ_MAX_DEVICE_BUF )
    {
	return -1;
    }
    m_pDevBuf[i]	= pDevice;
    switch (s32Type)
    {
    case XMS_DEVMAIN_VOIP:
	{
	    // link
	    InsertLink(pDevice, m_voip);
	    // update count
	    m_cntVoip++;
	    // set id
	    pDevice->m_id	= m_cntVoip;
	}
	break;
    case XMS_DEVMAIN_RTP:
	{
	    // link
	    InsertLink(pDevice, m_rtp);
	    // update count
	    m_cntRtp++;
	    // set id
	    pDevice->m_id	= m_cntRtp;
	}
	break;
    case XMS_DEVMAIN_VOICE:
	{
	    // link
	    InsertLink(pDevice, m_voice);
	    // update count
	    m_cntVoice++;
	    // set id
	    pDevice->m_id	= m_cntVoice;
	}
	break;
    default:
	break;
    }
    return 0;
}
// CDJXms::InsertLink-------------------------------------------------------------------------------------------
DJ_U32 CDJXms::InsertLink(CDJDevice* pDevice, CDJDevice*& listHead)
{
    if( listHead == NULL )
    {
	listHead	= pDevice;
	return 0;
    }
    CDJDevice* pTmp	= listHead;
    // link
    while(NULL != pTmp->m_next) 
    {
	pTmp	= pTmp->m_next;
    }
    pTmp->m_next	= pDevice;
    
    return 0;
}
// CDJXms::OnQueryDevice-------------------------------------------------------------------------------------------
void CDJXms::OnQueryDevice(Acs_Evt_t *pAcsEvt)
{
    Acs_Dev_List_Head_t *pAcsDevList = (Acs_Dev_List_Head_t *)FetchEventData(pAcsEvt);
    DeviceID_t *pDevice = (DeviceID_t *)(pAcsDevList+1);
    
    int			iDevice	= 0;
    CDJDevice*	pTmp	= NULL;
    CDJDevice*  pNew	= NULL;
    // save all the capable devices here
    switch (pAcsDevList->m_s32DeviceMain)
    {
    case XMS_DEVMAIN_VOIP:
	{
	    // init device
	    for( iDevice = 0; iDevice < pAcsDevList->m_s32DeviceNum; iDevice++)
	    {
		pNew	= new CDJVoip();
		// link
		if( InsertDevice(pNew, pAcsDevList->m_s32DeviceMain) != 0 )
		{
		    delete pNew;
		}
		else
		{
		    pNew->m_parent		= this;
		    pNew->m_device		= pDevice[iDevice];
		}
	    }
	}
	break;
    case XMS_DEVMAIN_RTP:
	{
	    // init device
	    for( iDevice = 0; iDevice < pAcsDevList->m_s32DeviceNum; iDevice++)
	    {
		pNew	= new CDJRtp();
		// link
		if( InsertDevice(pNew, pAcsDevList->m_s32DeviceMain) != 0 )
		{
		    delete pNew;
		}
		else
		{
		    pNew->m_parent		= this;
		    pNew->m_device		= pDevice[iDevice];
		}
	    }
	}
	break;
    case XMS_DEVMAIN_VOICE:
	{
	    // init device
	    for( iDevice = 0; iDevice < pAcsDevList->m_s32DeviceNum; iDevice++)
	    {
		pNew	= new CDJVoice();
		// link
		if( InsertDevice(pNew, pAcsDevList->m_s32DeviceMain) != 0 )
		{
		    delete pNew;
		}
		else
		{
		    pNew->m_parent		= this;
		    pNew->m_device		= pDevice[iDevice];
		}
	    }
	}
	break;
    default:
	break;
    }
    // print
    Print(pAcsDevList->m_s32DeviceMain);
    
}
// CDJXms::OnQueryDeviceEnd-------------------------------------------------------------------------------------------
void CDJXms::OnQueryDeviceEnd(Acs_Evt_t *pAcsEvt)
{
    m_bCanOpen	= TRUE;
    OpenAllDevices();
    // notify app
    CDJApp::GetApp()->OnQueryDeviceEnd();
}
// CDJXms::OpenAllDevices-------------------------------------------------------------------------------------------
BOOL CDJXms::OpenAllDevices()
{
    if( !m_bCanOpen )
	return FALSE;
    
    CDJDevice* pDevice	= m_voip;
    // open all IP devices
    for (DJ_U32 iDevice = 0; iDevice < m_cntVoip; ++iDevice)
    {
	pDevice->Open();
	pDevice	= pDevice->m_next;
    }
    pDevice	= m_rtp;
    // rtp device
    for(iDevice = 0; iDevice< m_cntRtp; ++iDevice)
    {
	pDevice->Open();
	pDevice	= pDevice->m_next;
    }
    pDevice	= m_voice;
    // open all Voice devices
    for (iDevice = 0; iDevice < m_cntVoice; ++iDevice)
    {
	pDevice->Open();
	pDevice	= pDevice->m_next;
    }
    
    return TRUE;
}
///////////////////////////////////////////////////////////////////////////////////////////
// CDJCmd
DJ_MSGMAP* CDJCmd::GetMessageMap() const
{
    return &CDJCmd::msgMap;	
}
DJ_MSGMAP CDJCmd::msgMap	=	{ NULL, ( DJ_MSGMAP_ENTRY * ) &( CDJCmd::msgEntries ) };
DJ_MSGMAP_ENTRY CDJCmd::msgEntries[]	=	
{ 
    { 0, 0, DJSig_end, (DJ_PMSG) 0 }
};
// CDJCmd::CDJCmd ------------------------------------------------------------
CDJCmd::CDJCmd()
{
}
// CDJCmd::~CDJCmd ------------------------------------------------------------
CDJCmd::~CDJCmd()
{
}
// CDJCmd::SearchMsgEntry ------------------------------------------------------------
DJ_MSGMAP_ENTRY	*CDJCmd::SearchMsgEntry( DJ_U32 nID )
{
    DJ_MSGMAP		*pMessageMap;
    DJ_MSGMAP_ENTRY	*lpEntry;
    
    for( pMessageMap = GetMessageMap(); pMessageMap	!= NULL;pMessageMap	= pMessageMap->pBaseMessageMap )
    {
	lpEntry	= pMessageMap->lpEntries;
	for( int i= 0;lpEntry[i].nMessage != 0;i++)
	{
	    if( lpEntry[i].nMessage == nID ) return &lpEntry[i];
	}
    }
    
    return NULL;
}
// CDJCmd::SendMsg ------------------------------------------------------------
DJ_U32 CDJCmd::SendMsg(DJ_U32 nMsgID, void *pAcsEvt)
{
    DJ_U32 bRet	= 0;
    DJ_MSGMAP_ENTRY	*lpEntry;
    lpEntry	= SearchMsgEntry(nMsgID);
    if( NULL != lpEntry )
    {
	DJ_MSG_FUNCTION	pFn;
	pFn.fnPMSG = lpEntry->pfn;
	switch( lpEntry->nSig )
	{
	case DJSig_cmd:
	    (this->*pFn.fnPCMD)();
	    break;
	case DJSig_pbv:
	    bRet    = (this->*pFn.fnPBV)(pAcsEvt);
	    break;
	default:
	    /* printf error */
	    break;
	}
    }
    else
    {
	bRet	= DefMsgProc( nMsgID, pAcsEvt );
    }
    
    return bRet;    
}
// CDJCmd::TranslateMsg ------------------------------------------------------------
DJ_U32 CDJCmd::TranslateMsg( void *pAcsEvt )
{
    return 0;
}
// CDJCmd::DefMsgProc ------------------------------------------------------------
DJ_U32 CDJCmd::DefMsgProc(DJ_U32 nMsgID, void *pAcsEvt)
{
    return 0;
}
DJBEG_MESSAGE_MAP(CDJDevice, CDJCmd)
DJ_ON_MSG(XMS_EVT_OPEN_DEVICE, OnOpenDevice)
DJ_ON_MSG(XMS_EVT_CLOSE_DEVICE, OnCloseDevice)
DJ_ON_MSG(XMS_EVT_DEVICESTATE, OnDeviceState)
DJEND_MESSAGE_MAP()
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// CDJDevice
CDJDevice::CDJDevice()
: m_id(0)
, m_bOpen(FALSE)
, m_next(NULL)
, m_call(NULL)
, m_bUsed(FALSE)
, m_nState(DCS_FREE)
, m_user(NULL)
//, m_bRefer(FALSE)
{
    memset(&m_device, -1, sizeof(DeviceID_t));
}

CDJDevice::~CDJDevice()
{
    Close();
}
// CDJDevice::Open-------------------------------------------------------------------------------------------
BOOL CDJDevice::Open()
{
    m_bOpen	= XMS_ctsOpenDevice(m_parent->Handler(), &m_device, NULL)<0?FALSE:TRUE;
    
    return m_bOpen;
}
// CDJDevice::Close-------------------------------------------------------------------------------------------
void CDJDevice::Close()
{
    // send close device command
    if( m_bOpen )
    {
	XMS_ctsCloseDevice(m_parent->Handler(), &m_device, NULL);
	m_bOpen	= FALSE;
	memset(&m_device, -1, sizeof(DeviceID_t));
    }
}
// CDJDevice::OnOpenDevice-------------------------------------------------------------------------------------------
DJ_U32 CDJDevice::OnOpenDevice(void* param)
{
    djPrint(DJ_LEVEL_LOG, _T("Device[%02d][%02d][%02d] device opened.\n"),m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID);
    return 0;
}
// CDJDevice::OnCloseDevice-------------------------------------------------------------------------------------------
DJ_U32 CDJDevice::OnCloseDevice(void* param)
{
    m_nState	= DCS_FREE;
    
    return 0;
}
// CDJDevice::OnDeviceState-------------------------------------------------------------------------------------------
DJ_U32 CDJDevice::OnDeviceState(void* param)
{
    Acs_GeneralProc_Data *pDeviceState	= (Acs_GeneralProc_Data *)param;
    
    djPrint(DJ_LEVEL_LOG, _T("Device[%02d][%02d][%02d] device state:0x%x, error code:%d.\n"),m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID, pDeviceState->m_s32DeviceState, pDeviceState->m_s32AcsEvtErrCode);
    
    m_nState	= pDeviceState->m_s32DeviceState;
    switch (pDeviceState->m_s32DeviceState)
    {
    case DCS_FREE:
	break;
    case DCS_CALLOUT:
	break;
    case DCS_CALLIN:
	break;
    case DCS_ALERTING:
	break;
    case DCS_CONNECT:
	break;
    case DCS_DISCONNECT:
	break;
    default:
	break;
    }
    // printf
    if( NULL != m_call )
	m_call->OnCallStateChaged();
    
    return 0;
}
// CDJDevice::SendIOData-------------------------------------------------------------------------------------------
DJ_U32 CDJDevice::SendIOData(DJ_U16 u16Type, DJ_U16 u16Size, DJ_Void* data)
{
    XMS_ctsSendIOData(m_parent->Handler(), &m_device, u16Type, u16Size, data);
    
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
DJBEG_MESSAGE_MAP(CDJVoip, CDJDevice)
DJ_ON_MSG(XMS_EVT_RECVIODATA, OnRecvIOData)
DJ_ON_MSG(XMS_EVT_SET_MEDIAINFO, OnSetMediaInfo)
DJ_ON_MSG(XMS_EVT_CALLIN, OnCallIn)
DJ_ON_MSG(XMS_EVT_ALERTCALL, OnAlertCall)
DJ_ON_MSG(XMS_EVT_ANSWERCALL, OnAnswerCall)
DJ_ON_MSG(XMS_EVT_CALLOUT, OnCallOut)
DJ_ON_MSG(XMS_EVT_CLEARCALL, OnClearCall)
DJ_ON_MSG(XMS_EVT_REFER_RESULT, OnReferRsult)
DJEND_MESSAGE_MAP()
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// CDJVoip
// CDJVoip::CDJVoip-------------------------------------------------------------------------------------------
CDJVoip::CDJVoip()
: m_rtp(NULL)
{
    memset(&m_tMediaInfo, 0, sizeof(Acs_VoIP_MediaInfo));
    memset(m_s8UserID, 0, sizeof(m_s8UserID));
}
// CDJVoip::~CDJVoip-------------------------------------------------------------------------------------------
CDJVoip::~CDJVoip()
{
}
// CDJVoip::Reset-------------------------------------------------------------------------------------------
void CDJVoip::Reset()
{
    memset(&m_tMediaInfo, 0, sizeof(Acs_VoIP_MediaInfo));
    memset(m_s8UserID, 0, sizeof(m_s8UserID));
}
// CDJVoip::Open-------------------------------------------------------------------------------------------
BOOL CDJVoip::Open()
{
    VoIPOpenPrivate_t   voipOpenPrivate = {0};
    voipOpenPrivate.m_PrivateData.m_u32DataSize = sizeof(VoIPOpenPrivate_t);
    voipOpenPrivate.m_u8RtpMode	= 1;//g_u8RtpMode;
    // send open device command
    m_bOpen	= XMS_ctsOpenDevice(m_parent->Handler(), &m_device, (PrivateData_t *)&voipOpenPrivate)<0?FALSE:TRUE;
    
    return m_bOpen;
}
// CDJVoip::MakeCall-------------------------------------------------------------------------------------------
void CDJVoip::MakeCall(DJ_S8 *s8CallerNum, DJ_S8 *s8CalleeNum)
{
    VoIPCallPrivate_t paramVoIPCall;
    memset( &paramVoIPCall, 0, sizeof( VoIPCallPrivate_t ) );
    paramVoIPCall.m_s32Protocol	= 2;// VOIP_PROTOCOL_SIP
    paramVoIPCall.m_PrivateData.m_u32DataSize = sizeof(VoIPCallPrivate_t);
    strcpy(paramVoIPCall.m_s8CallerUserID, s8CallerNum);
    strcpy(paramVoIPCall.m_s8CalleeUserID, s8CalleeNum);
    // set local	
    /*	if( bAllocRtp )
    {
    m_rtp	= (CDJRtp*)m_parent->AllocDevice( XMS_DEVMAIN_RTP );
    m_rtp->SetSession(1, m_tMediaInfo.payload_dtmf, m_tMediaInfo.payload_tone);
    m_rtp->SetIP(m_tMediaInfo.u8AudioEnabled, m_tMediaInfo.s8AudioAddress, m_tMediaInfo.u16AudioPort,
    m_tMediaInfo.u8VideoEnabled, m_tMediaInfo.s8VideoAddress, m_tMediaInfo.u16VideoPort);
    DJ_U8 u8CodePayload	= 0;
    for(int i= 0;i< 10;i++ )
    {
    if( g_rtp_codec[i].u8CodecType == m_tMediaInfo.u8MediaCapList[0] )
    {
				u8CodePayload	= g_rtp_codec[i].u8PayloadType;
				break;
				}
				}
				m_rtp->SetCodec(m_tMediaInfo.u8AudioEnabled, m_tMediaInfo.u8MediaCapList[0], u8CodePayload, 0, 0, 0);
				
				  strcpy( m_tMediaInfo.s8AudioAddress, "192.168.10.56");
				  m_tMediaInfo.u16AudioPort	= RTP_PORT_BASE(10000, m_rtp->GetID());
				  m_tMediaInfo.u8VideoEnabled	= 0;
				  m_tMediaInfo.u8MediaCapNum	= 1;
				  }
    */
    // set media info
    XMS_ctsSetParam(m_parent->Handler(), &m_device, VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo), &m_tMediaInfo);
    djPrint(DJ_LEVEL_LOG, _T("Device[%02d][%02d][%02d] Set media info.\n"),m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID);
    djPrint(DJ_LEVEL_LOG, _T("%d, %d, %s, %d, %d."), m_tMediaInfo.payload_dtmf, m_tMediaInfo.payload_tone, m_tMediaInfo.s8VideoAddress, m_tMediaInfo.u16VideoPort, m_tMediaInfo.u8MediaCapNum);
    for( int i= 0;i< m_tMediaInfo.u8MediaCapNum;i++ )
    {
	djPrint(DJ_LEVEL_LOG, _T("%d"), m_tMediaInfo.u8MediaCapList[i]);
    }
    // Make Call Out
    XMS_ctsMakeCallOut(m_parent->Handler(), &m_device, s8CallerNum, s8CalleeNum, (PrivateData_t *)&paramVoIPCall);
    
    djPrint(DJ_LEVEL_LOG, _T("Device[%02d][%02d][%02d] make call out.\n"),m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID);
}
// CDJVoip::AnswerCall-------------------------------------------------------------------------------------------
void CDJVoip::AnswerCall(DJ_S32 s32State, BOOL bAllocRtp, BOOL bTransfer)
{
    djPrint(DJ_LEVEL_LOG, _T("Device[%02d][%02d][%02d] answer call, state:%d, bAllocRtp:%d, bTransfer:%d.\n"),m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID, s32State, bAllocRtp, bTransfer);
    if (s32State != 0)
    {
	// set media info
	if( m_tMediaInfo.u8MediaCapNum>0 )
	{
	    // set local	
	    if( bAllocRtp )
	    {
		m_rtp	= (CDJRtp*)m_parent->AllocDevice( XMS_DEVMAIN_RTP );
		m_rtp->SetSession(1, m_tMediaInfo.payload_dtmf, m_tMediaInfo.payload_tone);
		m_rtp->SetIP(m_tMediaInfo.u8AudioEnabled, m_tMediaInfo.s8AudioAddress, m_tMediaInfo.u16AudioPort,
		    m_tMediaInfo.u8VideoEnabled, m_tMediaInfo.s8VideoAddress, m_tMediaInfo.u16VideoPort);
		DJ_U8 u8CodePayload	= 0;
		for(int i= 0;i< 10;i++ )
		{
		    if( g_rtp_codec[i].u8CodecType == m_tMediaInfo.u8MediaCapList[0] )
		    {
			u8CodePayload	= g_rtp_codec[i].u8PayloadType;
			break;
		    }
		}
		m_rtp->SetCodec(m_tMediaInfo.u8AudioEnabled, m_tMediaInfo.u8MediaCapList[0], u8CodePayload, 0, 0, 0);
		
		strcpy( m_tMediaInfo.s8AudioAddress, "192.168.10.56");
		m_tMediaInfo.u16AudioPort	= RTP_PORT_BASE(10000, m_rtp->GetID());
		m_tMediaInfo.u8VideoEnabled	= 0;
		m_tMediaInfo.u8MediaCapNum	= 1;
	    }
	    // set remote
	    XMS_ctsSetParam(m_parent->Handler(), &m_device, VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo), &m_tMediaInfo);
	    djPrint(DJ_LEVEL_LOG, _T("Device[%02d][%02d][%02d] Set media info.\n"),m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID);
	    djPrint(DJ_LEVEL_LOG, _T("%d, %d, %s, %d, %d."), m_tMediaInfo.payload_dtmf, m_tMediaInfo.payload_tone, m_tMediaInfo.s8VideoAddress, m_tMediaInfo.u16VideoPort, m_tMediaInfo.u8MediaCapNum);
	    for( int i= 0;i< m_tMediaInfo.u8MediaCapNum;i++ )
	    {
		djPrint(DJ_LEVEL_LOG, _T("%d"), m_tMediaInfo.u8MediaCapList[i]);
	    }
	}
	// accept call
	if(!bTransfer)
	{
	    // answer call in
	    XMS_ctsAnswerCallIn(m_parent->Handler(), &m_device, NULL);
	}
	else
	{
	    // transfer call
	    XMS_ctsSendIOData(m_parent->Handler(), &m_device, XMS_IO_TYPE_VOIP_TRANSFER,sizeof(DeviceID_t), &m_device);
	}
	
    }
    else
    {
	// make call fail
	XMS_ctsClearCall(m_parent->Handler(), &m_device, 0, NULL);
    }
}
// CDJVoip::ForwardCall-------------------------------------------------------------------------------------------
void CDJVoip::ForwardCall(DJ_S8* s8TelNo, DJ_S8* s8UserID, DJ_S8* s8Address, DJ_U16 u16Port)
{	
    VoIPForwardCallPrivate_t forwardCall	= {0};
    forwardCall.m_s32Protocol	= 2;// VOIP_PROTOCOL_SIP
    forwardCall.m_PrivateData.m_u32DataSize = sizeof(VoIPForwardCallPrivate_t);
    strcpy( forwardCall.m_s8TelNo, s8TelNo );
    strcpy( forwardCall.m_s8CallerUserID, s8UserID );
    strcpy( forwardCall.m_s8CallerAddress, s8Address );
    forwardCall.m_s32CallerPort	= u16Port;
    
    XMS_ctsSendIOData(m_parent->Handler(), &m_device, XMS_IO_TYPE_VOIP_FORWARD,sizeof(VoIPForwardCallPrivate_t), &forwardCall);
}
// CDJVoip::TransferCall-------------------------------------------------------------------------------------------
void CDJVoip::TransferCall(CDJDevice* device)
{	
    XMS_ctsSendIOData(m_parent->Handler(), &m_device, XMS_IO_TYPE_VOIP_TRANSFER,sizeof(DeviceID_t), (device==NULL)?&m_device:device->GetDevice());
}
// CDJVoip::ReferCall-------------------------------------------------------------------------------------------
void CDJVoip::ReferCall(Acs_VoIP_Refer_Response* referResp)
{
    XMS_ctsSendIOData(m_parent->Handler(), &m_device, XMS_IO_TYPE_VOIP_REFERRESPONSE,sizeof(Acs_VoIP_Refer_Response), referResp);
}
// CDJVoip::ClearCall-------------------------------------------------------------------------------------------
void CDJVoip::ClearCall()
{
    XMS_ctsClearCall(m_parent->Handler(), &m_device, 0, NULL);
}
// CDJVoip::OnRecvIOData-------------------------------------------------------------------------------------------
DJ_U32 CDJVoip::OnRecvIOData(void *param)
{
    Acs_IO_Data *pIOEvt = (Acs_IO_Data *)param;
    char dtmf = '?';
    
    djPrint(DJ_LEVEL_LOG, _T("Device[%02d][%02d][%02d] recieve io data.\n"),m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID);
    switch (pIOEvt->m_u16IoType)
    {
    case XMS_IO_TYPE_VOIP_REGREQUEST:
	if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_REGSTATE))
	{
	    // check client's info
	    Acs_VoIP_REGSTATE *pRegRequest = (Acs_VoIP_REGSTATE *)((DJ_S8*)pIOEvt + sizeof(Acs_IO_Data));
	    djPrint(DJ_LEVEL_LOG,_T("Client registrates from: \"%s\" %s@%s:%d\n"),
		pRegRequest->m_s8UserID, pRegRequest->m_s8TelNo, pRegRequest->m_s8Address, pRegRequest->m_u16Port);
	    
	    // response to registration
	    // if authentication is disabled,
	    //   set Acs_VoIP_REGRESP::m_u8Granted to 0/1 to grant/disgrant registration
	    // if authentication is enabled,
	    //   set Acs_VoIP_REGRESP::m_u8Granted to 0, and fill Acs_VoIP_REGRESP::m_s8Password to authenticate,
	    //   or
	    //   set Acs_VoIP_REGRESP::m_u8Granted to 0, and leave Acs_VoIP_REGRESP::m_s8Password empty to disgrant registration,
	    //   or
	    //   set Acs_VoIP_REGRESP::m_u8Granted to 1 to grant registration without authenticating.
	    Acs_VoIP_REGRESP regResponse = {0};
	    regResponse.m_u16SlotID = pRegRequest->m_u16SlotID;
	    regResponse.m_u8Granted = 1;
	    //			strcpy(regResponse.m_s8Password, "passwd");
	    XMS_ctsSendIOData(m_parent->Handler(), &m_device, XMS_IO_TYPE_VOIP_REGRESPONSE,
		sizeof(regResponse), &regResponse);
	}
	break;
    case XMS_IO_TYPE_VOIP_REFER:
	{
	    // check client's info
	    Acs_VoIP_Refer *pRefer = (Acs_VoIP_Refer *)((DJ_S8*)pIOEvt + sizeof(Acs_IO_Data));
	    djPrint(DJ_LEVEL_LOG,_T("Device[%02d][%02d][%02d] Client refer to: \"%s\" %s@%s:%d\n"),
		m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID,
		pRefer->m_s8UserID, pRefer->m_s8TelNo, pRefer->m_s8Address, pRefer->m_u16Port);
	    
	    // allow refer
	    //DJ_U8 bCanRefer = m_call->OnRefer(pRefer->m_s8TelNo, pRefer->m_s8UserID, pRefer->m_s8Address, pRefer->m_u16Port);
	    Acs_VoIP_Refer_Response referResp	= {0};
	    //			referResp.m_u8ReferFlag		=  2;
	    referResp.m_u8SrcUnitID		= m_device.m_s8ModuleID;
	    referResp.m_u16SrcChanID	= m_device.m_s16ChannelID;
	    strcpy(referResp.m_s8UserID, pRefer->m_s8TelNo);//pRefer->m_s8UserID);
	    strcpy(referResp.m_s8TelNo, pRefer->m_s8TelNo);
	    
	    //XMS_ctsSendIOData(m_parent->Handler(), &m_device, XMS_IO_TYPE_VOIP_REFERRESPONSE,sizeof(referResp), &referResp);
	    m_call->OnRefer(this, &referResp);
	    // forward call
	    /*if( NULL != m_call )
	    {
	    m_call->OnForward(this, pRefer->m_s8TelNo, pRefer->m_s8TelNo, pRefer->m_s8Address, pRefer->m_u16Port);
	}*/
	}
	break;
    case XMS_IO_TYPE_VOIP_REGSTATE:
	if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_REGSTATE))
	{
	    Acs_VoIP_REGSTATE *pRegState = (Acs_VoIP_REGSTATE *)((DJ_S8*)pIOEvt + sizeof(Acs_IO_Data));
	    if (pRegState->m_u16SlotID < DJ_MAX_USER)
	    {
		DJ_U16 u16SlotID = pRegState->m_u16SlotID;
		if (pRegState->m_u8State)
		{
		    CDJApp::GetApp()->OnUserRegister(u16SlotID, pRegState->m_s8TelNo, pRegState->m_s8UserID, pRegState->m_s8Address, pRegState->m_u16Port);
		}
		else
		{
		    // unregister
		    CDJApp::GetApp()->OnUserUnregister(u16SlotID);
		}
	    }
	}
	break;
	
    case XMS_IO_TYPE_VOIP_H245UII:
	if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_H245UII))
	{
	    Acs_VoIP_H245UII *h245Uii = (Acs_VoIP_H245UII *)((DJ_S8*)pIOEvt + sizeof(Acs_IO_Data));
	    //dtmf = h245Uii->m_s8Signal;
	    if( NULL != m_call )
	    {
		m_call->OnSendIOData(this, XMS_IO_TYPE_VOIP_H245UII, sizeof(*h245Uii), (void*)h245Uii);
	    }
	}
	break;
    case XMS_IO_TYPE_VOIP_SIPINFO:
	if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_SIPINFO))
	{
	    Acs_VoIP_SIPINFO *sipInfo = (Acs_VoIP_SIPINFO *)((DJ_S8*)pIOEvt + sizeof(Acs_IO_Data));
	    if ( NULL != m_call )
	    {
		m_call->OnSendIOData(this, XMS_IO_TYPE_VOIP_SIPINFO, sizeof(*sipInfo), sipInfo);
	    }
	}
	break;
    case XMS_IO_TYPE_VOIP_RTPDTMF:
	if (pIOEvt->m_u16IoDataLen == sizeof(Acs_VoIP_RTPDTMF))
	{
	    Acs_VoIP_RTPDTMF *rtpDtmf = (Acs_VoIP_RTPDTMF *)((DJ_S8*)pIOEvt + sizeof(Acs_IO_Data));
	    //dtmf = rtpDtmf->m_s8EventChar;
	    if ( NULL != m_call )
	    {
		m_call->OnSendIOData(this, XMS_IO_TYPE_VOIP_RTPDTMF, sizeof(*rtpDtmf), rtpDtmf);
	    }
	}
	break;
	}
	
	return 0;
}
// CDJVoip::SetMediaInfo-------------------------------------------------------------------------------------------
void CDJVoip::SetMediaInfo(Acs_VoIP_MediaInfo* mediaInfo)
{
    XMS_ctsSetParam(m_parent->Handler(), &m_device, VOIP_PARAM_MEDIAINFO, sizeof(Acs_VoIP_MediaInfo), mediaInfo);
}
// CDJVoip::OnSetMediaInfo-------------------------------------------------------------------------------------------
DJ_U32 CDJVoip::OnSetMediaInfo(void *param)
{
    Acs_VoIP_MediaInfo *pMediaInfo = (Acs_VoIP_MediaInfo *)param;
    djPrint(DJ_LEVEL_LOG, _T("Device[%02d][%02d][%02d] media info.\n"),m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID);
    djPrint(DJ_LEVEL_LOG, _T("%d, %d, %s, %d, %d."), pMediaInfo->payload_dtmf, pMediaInfo->payload_tone, pMediaInfo->s8VideoAddress, pMediaInfo->u16VideoPort, pMediaInfo->u8MediaCapNum);
    for( int i= 0;i< pMediaInfo->u8MediaCapNum;i++ )
    {
	djPrint(DJ_LEVEL_LOG, _T("%d"), pMediaInfo->u8MediaCapList[i]);
    }
    
    memcpy( &m_tMediaInfo, pMediaInfo, sizeof(Acs_VoIP_MediaInfo));
    //	strcpy( m_tMediaInfo.s8AudioAddress, m_tMediaInfo.s8VideoAddress );
    //	m_tMediaInfo.u16AudioPort = m_tMediaInfo.u16VideoPort;
    return 0;
}
// CDJVoip::OnCallIn-------------------------------------------------------------------------------------------
DJ_U32 CDJVoip::OnCallIn(void *param)
{
    Acs_CallControl_Data* pCallEvt = (Acs_CallControl_Data *)param;
    VoIPCallPrivate_t *paramVoIPCall = (VoIPCallPrivate_t *)&(pCallEvt->m_PrivData);
    djPrint(DJ_LEVEL_LOG, _T("Device[%02d][%02d][%02d] call in.\n"),m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID);
    /*
    CDJUser* caller	= CDJApp::GetApp()->GetUser( pCallEvt->m_s8CallingNum, paramVoIPCall->m_s8CallerUserID);
    if( NULL == caller )
    {
    XMS_ctsClearCall(m_parent->Handler(), &m_device, 0, NULL);
    return 1;
    }
    */
    if( NULL != m_call /*&& m_call->GetState() == CS_CONNECTED*/ )
    {
	// re-invite
	OnReInvite();
    }
    else
    {
	// alloc device
	if( !m_bUsed )
	    m_parent->AllocDevice(XMS_DEVMAIN_VOIP, m_id);
	// printf
	m_parent->Print(XMS_DEVMAIN_VOIP);
	
	CDJApp::GetApp()->OnCallIn( this, pCallEvt->m_s8CallingNum, paramVoIPCall->m_s8CallerUserID, pCallEvt->m_s8CalledNum, paramVoIPCall->m_s8CalleeUserID );
    }
    return 0;
}
// CDJVoip::OnReInvite-------------------------------------------------------------------------------------------
void CDJVoip::OnReInvite()
{
    djPrint(DJ_LEVEL_LOG,_T("Re-Invite."));
}
// CDJVoip::OnReferRsult-------------------------------------------------------------------------------------------
DJ_U32 CDJVoip::OnReferRsult(void *param)
{
    Acs_VoIP_ReferResult *pReferResult	= (Acs_VoIP_ReferResult*)param;
    djPrint(DJ_LEVEL_LOG, _T("Device[%02d][%02d][%02d] refer resutl, protocol:%d; state:%d; reason:%d.\n"),m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID, pReferResult->m_u8Protocol, pReferResult->m_u8State, pReferResult->m_u8Reason);
    
    CDJApp::GetApp()->OnReferResult(this, pReferResult->m_u8State, pReferResult->m_u8Reason);
    //	if( NULL != m_call )
    //		m_call->SetRefer(FALSE);
    
    return 0;
}
// CDJVoip::OnAlertCall-------------------------------------------------------------------------------------------
DJ_U32 CDJVoip::OnAlertCall(void *param)
{
    Acs_CallControl_Data *pCallEvt = (Acs_CallControl_Data *)param;
    
    djPrint(DJ_LEVEL_LOG, _T("Device[%02d][%02d][%02d] call alerted.\n"),m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID);
    
    return 0;
}
// CDJVoip::OnAnswerCall-------------------------------------------------------------------------------------------
DJ_U32 CDJVoip::OnAnswerCall(void *param)
{
    Acs_CallControl_Data *pCallEvt = (Acs_CallControl_Data *)param;
    djPrint(DJ_LEVEL_LOG, _T("Device[%02d][%02d][%02d] call answer.\n"),m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID);
    
    return 0;
}
// CDJVoip::OnCallOut-------------------------------------------------------------------------------------------
DJ_U32 CDJVoip::OnCallOut(void *param)
{
    Acs_CallControl_Data *pCallEvt = (Acs_CallControl_Data *)param;
    djPrint(DJ_LEVEL_LOG, _T("Device[%02d][%02d][%02d] call out.\n"),m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID);
    
    m_call->OnCallConnected(this, pCallEvt->m_s32AcsEvtState);
    
    
    return 0;
}
// CDJVoip::OnClearCall-------------------------------------------------------------------------------------------
DJ_U32 CDJVoip::OnClearCall(void *param)
{
    Acs_CallControl_Data *pCallEvt = (Acs_CallControl_Data *)param;
    
    djPrint(DJ_LEVEL_LOG, _T("Device[%02d][%02d][%02d] call clear.\n"),m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID);
    // find peer device
    if (m_call != NULL)
    {
	m_call->OnClearCall(this);
	// clear rtp
	if( m_rtp != NULL )
	{
	    m_rtp->SetSession(0,0,0);
	    m_parent->ReleaseDevice(XMS_DEVMAIN_RTP, m_rtp->GetID());
	    m_rtp	= NULL;
	}
	// clear ip
	m_parent->ReleaseDevice(XMS_DEVMAIN_VOIP, m_id);
    }
    
    //	SetRefer(FALSE);
    
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// CDJRtp
// CDJRtp::CDJRtp-------------------------------------------------------------------------------------------
CDJRtp::CDJRtp()
{
}
// CDJRtp::~CDJRtp-------------------------------------------------------------------------------------------
CDJRtp::~CDJRtp()
{
}
// CDJRtp::SetIP-------------------------------------------------------------------------------------------
void CDJRtp::SetIP(DJ_U8 u8AudioEnabled, const DJ_S8* s8AudioAddress, DJ_U16  u16AudioPort, DJ_U8   u8VideoEnabled, const DJ_S8* s8VideoAddress, DJ_U16  u16VideoPort)
{
    Acs_VoIP_RTPADDR	addr	= {0};
    strcpy(addr.audio.m_s8IP, s8AudioAddress);
    addr.audio.m_u16Port	= u16AudioPort;
    addr.audio.m_u8Enable	= u8AudioEnabled;
    strcpy(addr.video.m_s8IP,s8VideoAddress);
    addr.video.m_u16Port	= u16VideoPort;
    addr.video.m_u8Enable	= u8VideoEnabled;
    XMS_ctsSetParam(m_parent->Handler(), &m_device, VOIP_PARAM_RTPADDR, sizeof(Acs_VoIP_RTPADDR), &addr);
}
// CDJRtp::SetSession-------------------------------------------------------------------------------------------
void CDJRtp::SetSession(DJ_U8 u8Enabled, DJ_U8 dtmf, DJ_U8 tone)
{
    Acs_VoIP_RTPSESSION	session	= {0};
    session.m_u8Enable			= u8Enabled;
    session.m_u8PayloadDtmf		= dtmf;
    session.m_u8PayloadTone		= tone;
    XMS_ctsSetParam(m_parent->Handler(), &m_device, VOIP_PARAM_RTPSESSION, sizeof(Acs_VoIP_RTPSESSION), &session);
}
// CDJRtp::SetCodec-------------------------------------------------------------------------------------------
void CDJRtp::SetCodec(DJ_U8 u8AudioEnabled, DJ_U8 u8AudioCodec, DJ_U8 u8AudioPayloadType, DJ_U8 u8VideoEnabled, DJ_U8 u8VideoCodec, DJ_U8 u8VideoPayloadType)
{
    Acs_VoIP_RTPCODEC	codec	= {0};
    codec.audio.m_u8Enable			= u8AudioEnabled;
    codec.audio.m_u8TxCodec			= u8AudioCodec;
    codec.audio.m_u8RxCodec			= u8AudioCodec;
    codec.audio.m_u8TxPayloadType	= u8AudioPayloadType;
    codec.audio.m_u8RxPayloadType	= u8AudioPayloadType;
    codec.video.m_u8Enable			= u8VideoEnabled;
    codec.video.m_u8TxCodec			= u8VideoCodec;
    codec.video.m_u8RxCodec			= u8VideoCodec;
    codec.video.m_u8TxPayloadType	= u8VideoPayloadType;
    codec.video.m_u8RxPayloadType	= u8VideoPayloadType;
    XMS_ctsSetParam(m_parent->Handler(), &m_device, VOIP_PARAM_RTPCODEC, sizeof(Acs_VoIP_RTPCODEC), &codec);
}

DJBEG_MESSAGE_MAP(CDJVoice, CDJDevice)
DJ_ON_MSG(XMS_EVT_CONTROLPLAY, OnPlay)
DJ_ON_MSG(XMS_EVT_PLAY, OnPlayEnd)
DJEND_MESSAGE_MAP()
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// CDJVoice
CDJVoice::CDJVoice()
: m_bPlaying(FALSE)
{
    memset(&m_property, 0, sizeof(m_property));
}
// CDJVoice::~CDJVoice-------------------------------------------------------------------------------------------
CDJVoice::~CDJVoice()
{
}
// CDJVoice::ClearCall-------------------------------------------------------------------------------------------
void CDJVoice::ClearCall()
{
    // stop play
    if( m_bPlaying )
    {
	ControlPlay_t cp = {0};
	cp.m_u16ControlType = XMS_STOP_PLAY;
	// send control play command
	XMS_ctsControlPlay(m_parent->Handler(), &m_device, &cp, NULL);
    }
    // release resource
    m_parent->ReleaseDevice(XMS_DEVMAIN_VOICE, m_id);
    // 
    if( NULL != m_call )
	m_call->OnClearCall(this);
}
// CDJVoice::SetProperty-------------------------------------------------------------------------------------------
void CDJVoice::SetProperty(DJ_U8 u8DecodeType, DJ_U16 u16PlayType, DJ_U8 u8SrcMode)
{
    m_property.m_u8DecodeType	= u8DecodeType;
    m_property.m_u16PlayType	= u16PlayType;
    m_property.m_u8SrcMode		= u8SrcMode;
}
// CDJVoice::Play-------------------------------------------------------------------------------------------
void CDJVoice::Play(const char* filename)
{
    strcpy(m_property.m_s8PlayContent, filename);
    
    djPrint(DJ_LEVEL_LOG, _T("Device[%02d][%02d][%02d] device play.\n"),m_device.m_s8ModuleID,m_device.m_s16DeviceMain,m_device.m_s16ChannelID);
    djPrint(DJ_LEVEL_LOG, _T("filename:%s.\n"), m_property.m_s8PlayContent);
    XMS_ctsPlay(m_parent->Handler(), &m_device, &m_property, NULL);
    
    m_bPlaying	= TRUE;
}
// CDJVoice::OnPlay-------------------------------------------------------------------------------------------
DJ_U32 CDJVoice::OnPlay(void* param)
{
    if( NULL != m_call )
	m_call->OnPlay();
    
    return 0;
}
// CDJVoice::OnPlayEnd-------------------------------------------------------------------------------------------
DJ_U32 CDJVoice::OnPlayEnd(void *param)
{
    if( NULL != m_call )
	m_call->OnPlayEnd();
    
    m_bPlaying	= FALSE;
    
    ClearCall();
    
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// CDJUser
CDJUser::CDJUser()
: m_nID(0)
, m_u16SlotID(-1)
{
    memset(m_s8TelNo, 0, sizeof(m_s8TelNo));
    memset(m_s8UserID, 0, sizeof(m_s8UserID));
    
    memset(m_s8Address, 0, sizeof(m_s8Address));
    m_u16Port	= 0;
    
    m_u32State	= US_IDLE;
}
// CDJUser::~CDJUser-------------------------------------------------------------------------------------------
CDJUser::~CDJUser()
{
}
// CDJUser::Print-------------------------------------------------------------------------------------------
void CDJUser::Print()
{
    djPrint(DJ_PORT_USER, m_nID, 4, m_s8TelNo, m_s8UserID, m_s8Address, s_UserState[m_u32State]);
}
// CDJUser::Reset-------------------------------------------------------------------------------------------
void CDJUser::Reset()
{
    memset(m_szDtmf, 0, sizeof(m_szDtmf));
    m_u32State	= US_INITIATED;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// CDJCall
CDJCall::CDJCall()
: m_caller(NULL)
, m_callee(NULL)
, m_nID(0)
{
    m_nState	= CS_NULL;
}
// CDJCall::~CDJCall-------------------------------------------------------------------------------------------
CDJCall::~CDJCall()
{
}
// CDJCall::Print-------------------------------------------------------------------------------------------
void CDJCall::Print()
{
    char strCaller[64]	= {0};
    char strCallee[64]	= {0};
    DeviceID_t*	device	= NULL;
    if( m_caller != NULL && NULL != m_caller->GetDevice())
    {
	device	= m_caller->GetDevice();
	sprintf(strCaller, _T("%s:(%02d,%02d,%02d)--%02d"), m_caller->GetUserID(), device->m_s8ModuleID,device->m_s16DeviceMain,device->m_s16ChannelID, m_caller->GetState());
    }
    else
    {
	sprintf(strCaller, _T("N/A"));
    }
    // callee
    if( m_callee != NULL && NULL != m_callee->GetDevice() )
    {
	device	= m_callee->GetDevice();
	sprintf(strCallee, _T("%s:(%02d,%02d,%02d)--%02d"), m_callee->GetUserID(), device->m_s8ModuleID,device->m_s16DeviceMain,device->m_s16ChannelID, m_callee->GetState());
    }
    else
    {
	sprintf(strCallee, _T("N/A"));
    }
    // state
    djPrint(DJ_PORT_CALL, m_nID, 3, strCaller, strCallee, s_CallState[m_nState]);
}
// CDJCall::OnCallConnected-------------------------------------------------------------------------------------------
DJ_U32 CDJCall::OnCallConnected(CDJDevice* device, DJ_S32 s32State)
{
    if( m_callee == device && m_nState != CS_CONNECTED )
    {
	// set caller media info
	m_caller->SendMsg( XMS_EVT_SET_MEDIAINFO, ((CDJVoip*)device)->GetMediaInfo() );
	// anser call
	m_caller->AnswerCall(s32State, FALSE, FALSE);
    }
    
    return 0;
}
// CDJCall::OnSendIOData-------------------------------------------------------------------------------------------
DJ_U32 CDJCall::OnSendIOData(CDJDevice* device, DJ_U16 u16Type, DJ_U16 u16Size, DJ_Void* data)
{
    //	if (strcmp(sipInfo->m_s8ContentType, "application/dtmf") == 0)
    //	{
    //		sscanf(sipInfo->m_s8Body, "dtmf=%c", &dtmf);
    //	}
    
    if( m_callee == device )
    {
	m_caller->SendIOData( u16Type, u16Size, data );
    }
    else if( m_caller == device )
    {
	m_callee->SendIOData( u16Type, u16Size, data );
    }
    
    return 0;
}
// CDJCall::OnClearCall-------------------------------------------------------------------------------------------
DJ_U32 CDJCall::OnClearCall(CDJDevice* device)
{
    device->SetCall(NULL);
    if( NULL != m_caller && device == m_caller )
    {
	m_caller	= NULL;
	if(NULL != m_callee)
	    m_callee->ClearCall();
    }
    if( NULL != m_callee && device == m_callee )
    {
	m_callee	= NULL;
	if( NULL != m_caller )
	    m_caller->ClearCall();
    }
    // free call
    if( m_caller == NULL && m_callee == NULL )
    {
	// 
	m_nState	= CS_NULL;
	// free call
	CDJApp::GetApp()->ReleaseCall(this);
    }
    // print
    Print();
    
    return 0;
}
// CDJCall::OnRefer-------------------------------------------------------------------------------------------
DJ_U8 CDJCall::OnRefer(CDJDevice* device, Acs_VoIP_Refer_Response* referResp)
{
    CDJUser* user	= CDJApp::GetApp()->GetUser( referResp->m_s8TelNo, referResp->m_s8UserID);
    // get destination device
    CDJCall* callB	= CDJApp::GetApp()->GetCallByUser(user, this);
    BOOL bNewCall	= (callB == NULL)?TRUE:FALSE;
    // IVR
    if( strcmp(referResp->m_s8UserID, "8888") == 0 )
    {
	referResp->m_u8ReferFlag	= 1;
	strcpy(referResp->m_s8Address, "192.168.10.53");
	referResp->m_u16Port		= 5060;
	// refer call
	if( m_caller == device )
	{
	    m_callee->ReferCall(referResp);
	}
	else
	{
	    m_caller->ReferCall(referResp);
	}
	// free call
	//			CDJApp::GetApp()->ReleaseCall(this);
	return 0;
    }
    // reject
    if( user == NULL )
    {
	referResp->m_u8ReferFlag	= 0;
	device->ReferCall(referResp);
	return 0;
    }
    
    // IP trunk
    referResp->m_u8ReferFlag	= 2;
    djPrint(DJ_LEVEL_LOG, "user address:%s, port:%d.", user->m_s8Address, user->m_u16Port);
    //	djPrint(DJ_LEVEL_LOG, "caller:0x%x, callee:0x%x, device:0x%x.", m_caller, m_callee,device);
    // alloc call
    CDJCall* call	= CDJApp::GetApp()->AllocCall();
    // init call info
    call->m_nState	= CS_TRANSLATE;
    CDJDevice* callee	= CDJApp::GetApp()->m_xms.AllocDevice(XMS_DEVMAIN_VOIP);
    callee->SetCall(call);
    // set ip address
    if( strcmp(referResp->m_s8UserID, "8888") == 0 )
    {
	strcpy(referResp->m_s8Address, "192.168.10.53");
	referResp->m_u16Port		= 5060;
    }
    else
    {
	if( user == NULL )
	{
	    // reject
	    referResp->m_u8ReferFlag	= 0;
	    device->ReferCall(referResp);
	    return 0;
	}
	strcpy(referResp->m_s8Address, user->m_s8Address);
	referResp->m_u16Port		= user->m_u16Port;
    }
    // set callee
    call->SetCallee(callee);
    // set caller
    if( m_caller == device )
    {
	call->SetCaller(m_callee);
    }
    else
    {
	call->SetCaller(m_caller);
    }
    // refer call
    if( !bNewCall )
    {
	// clear remote
	if(callB->GetCaller()->GetUser() == user)
	{
	    referResp->m_u8DestUnitID		= callB->GetCaller()->GetDevice()->m_s8ModuleID;
	    referResp->m_u16DestChanID		= callB->GetCaller()->GetDevice()->m_s16ChannelID;;
	}
	else
	{
	    referResp->m_u8DestUnitID		= callB->GetCallee()->GetDevice()->m_s8ModuleID;
	    referResp->m_u16DestChanID		= callB->GetCallee()->GetDevice()->m_s16ChannelID;;
	}
    }
    else
    {
    }
    if( m_caller == device )
    {
	((CDJVoip*)callee)->SetMediaInfo(((CDJVoip*)m_callee)->GetMediaInfo());
    }
    else
    {
	((CDJVoip*)callee)->SetMediaInfo(((CDJVoip*)m_caller)->GetMediaInfo());
    }	
    
    callee->ReferCall(referResp);
    // print call info
    call->Print();
    
    return 0;
}
// CDJCall::OnForward-------------------------------------------------------------------------------------------
DJ_U8 CDJCall::OnForward(CDJDevice* device, DJ_S8* s8TelNo, DJ_S8* s8UserID, DJ_S8* s8Address, DJ_U16 u16Port)
{
    if( m_caller == device )
    {
	m_callee->ForwardCall(s8TelNo, s8UserID, s8Address, u16Port);
    }
    else if( m_callee == device)
    {
	m_caller->ForwardCall(s8TelNo, s8UserID, s8Address, u16Port);
    }
    else
    {
    }
    
    return 0;
}
// CDJCall::OnCallStateChaged-------------------------------------------------------------------------------------------
void CDJCall::OnCallStateChaged()
{
    //
    if( m_callee == NULL && m_caller == NULL )
    {
	m_nState	= 	CS_NULL;
	djPrint(DJ_LEVEL_LOG, "%s", "CS_NULL"); 
    }
    else if( m_caller != NULL )
    {
	switch( m_caller->GetState() )
	{
	case DCS_CALLIN:
	    {
		if(m_callee == NULL)
		{
		    m_nState	= CS_ORIGINATED;
		    djPrint(DJ_LEVEL_LOG, "%s", "CS_ORIGINATED"); 
		}
		else
		{
		    switch( m_callee->GetState() )
		    {
		    case DCS_CALLOUT:
			m_nState	= CS_DELIVERED;
			djPrint(DJ_LEVEL_LOG, "%s", "CS_DELIVERED"); 
			break;
		    case DCS_ALERTING:
			m_nState	= CS_ALERTING;
			djPrint(DJ_LEVEL_LOG, "%s", "CS_ALERTING"); 
			break;
		    case DCS_CONNECT:
			m_nState	= CS_ESTABLISHED;
			djPrint(DJ_LEVEL_LOG, "%s", "CS_ESTABLISHED"); 
			break;
		    default:
			break;
		    }
		}
	    }
	    break;
	case DES_SIP_ACCEPTED:
	    if( m_callee->GetState() == DCS_CONNECT )
	    {
		m_nState	= CS_ANSWER_CALL;
		djPrint(DJ_LEVEL_LOG, "%s", "CS_ANSWER_CALL"); 
	    }
	    break;
	case DCS_CONNECT:
	    if( m_callee!=NULL && m_callee->GetState() == DCS_CONNECT )
	    {
		m_nState	= CS_CONNECTED;
		djPrint(DJ_LEVEL_LOG, "%s", "CS_CONNECTED"); 
		djPrint(DJ_LEVEL_LOG, "call:%d, caller:0x%x, callee:0x%x.", m_nID, m_caller->GetDevice(), m_callee->GetDevice()); 
	    }
	    break;
	case DES_SIP_DISCONNECTING:
	    // clear call
	    if( m_callee == NULL )
	    {
		m_nState	= CS_NULL;
	    }
	    //		m_callee	= NULL;
	    //		m_caller->GetDevice()->SendMsg(XMS_EVT_CLEARCALL, NULL);
	    //		CDJApp::GetApp()->ReleaseCall(this);
	    break;
	default:
	    break;
	}
    }
    else
    {
	if(m_callee != NULL)
	{
	    djPrint(DJ_LEVEL_LOG, "callee state:<%02d>.", m_callee->GetState());
	    if( m_callee->GetState() == DES_SIP_DISCONNECTING )
	    {
		m_nState	= CS_NULL;
	    }
	}
	else
	{
	    DJ_ASSERT(FALSE);
	}
    }
    
    Print();
}
// CDJCall::OnPlay-------------------------------------------------------------------------------------------
void CDJCall::OnPlay()
{
    m_nState	= CS_PLAYING;
    Print();
}
// CDJCall::OnPlayEnd-------------------------------------------------------------------------------------------
void CDJCall::OnPlayEnd()
{
    m_nState	= CS_PLAYEND;
    Print();
}

DJBEG_MESSAGE_MAP(CDJApp, CDJCmd)
DJEND_MESSAGE_MAP()
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// CDJApp
CDJApp::CDJApp()
: m_user(NULL)
, m_call(NULL)
{
}
// CDJApp::CDJApp-------------------------------------------------------------------------------------------
CDJApp::~CDJApp()
{
    Destroy();
}
// CDJApp::Destroy------------------------------------------------------------------------------------------- 
void CDJApp::Destroy()
{
    m_xms.CloseSystem();
    // clear call
    if( NULL != m_call )
    {
	delete [] m_call;
	m_call	= NULL;
    }
    // clear user
    if( NULL != m_user )
    {
	delete [] m_user;
	m_user	= NULL;
    }
}
// CDJApp::Init-------------------------------------------------------------------------------------------
CDJApp* CDJApp::GetApp()
{
    static CDJApp s_app;
    return &s_app;
}
// CDJApp::Init-------------------------------------------------------------------------------------------
BOOL CDJApp::Init(unsigned int nId, const char* strServerIP, const int strServerPort, const char* strUserName, const char* strPassword)
{
    Destroy();
    int i	= 0;
    // alloc user
    m_user	= new CDJUser[DJ_MAX_USER];
    for(i= 0;i< DJ_MAX_USER;i++)
    {
	m_user[i].m_nID	= i+1;
	m_user[i].Print();
    }
    // alloc call
    m_call	= new CDJCall[DJ_MAX_CALL];
    for(i= 0;i< DJ_MAX_CALL;i++)
    {
	m_call[i].m_nID	= i+1;
	m_call[i].Print();
    }
    // init xms
    m_xms.InitSystem( nId, strServerIP, strServerPort, strUserName, strPassword );
    
    return TRUE;
}
// CDJApp::AllocCall-------------------------------------------------------------------------------------------
CDJCall* CDJApp::AllocCall()
{
    for(int i= 0;i< DJ_MAX_CALL;i++)
    {
	if( m_call[i].m_nState == CS_NULL )
	{
	    return &m_call[i];
	}
    }
    
    return NULL;
}
// CDJApp::GetCallByUser-------------------------------------------------------------------------------------------
CDJCall* CDJApp::GetCallByUser(CDJUser* user, CDJCall* call)
{
    if( user == NULL )
	return NULL;
    
    for( int i= 0;i< DJ_MAX_CALL;i++ )
    {
	if( m_call[i].m_nState == CS_NULL )
	    continue;
	
	if( &m_call[i] == call )
	    continue;
	
	if( (m_call[i].GetCaller() != NULL && m_call[i].GetCaller()->GetUser() == user) 
	    || (m_call[i].GetCallee() != NULL && m_call[i].GetCallee()->GetUser() == user)
	    )
	{
	    return &m_call[i];
	}
    }
    
    return NULL;
}
// CDJApp::ReleaseCall-------------------------------------------------------------------------------------------
void CDJApp::ReleaseCall(CDJCall* call)
{
    int nIndex	= m_call - call;
    m_call[nIndex].m_nState	= CS_NULL;
    m_call[nIndex].m_callee	= NULL;
    m_call[nIndex].m_caller	= NULL;
}
// CDJApp::GetUser-------------------------------------------------------------------------------------------
CDJUser* CDJApp::GetUser(DJ_S8* s8TelNo, DJ_S8* s8UserID)
{
    for(int i=0;i< DJ_MAX_USER;i++)
    {
	if( (strcmp(m_user[i].m_s8TelNo, s8TelNo)==0) || (strcmp(m_user[i].m_s8UserID, s8UserID) == 0) )
	{
	    return &m_user[i];
	}
    }
    
    return NULL;
}
// CDJApp::OnUserUnregister-------------------------------------------------------------------------------------------
void CDJApp::OnUserRegister(DJ_U16 u16SlotID, DJ_S8* s8TelNo, DJ_S8* s8UserID, DJ_S8* s8Address, DJ_U16 u16Port)
{
    for(int i= 0;i< DJ_MAX_USER;i++)
    {
	if( m_user[i].GetState() == US_IDLE )
	{
	    m_user[i].m_u16SlotID	= u16SlotID;
	    strcpy( m_user[i].m_s8TelNo, s8TelNo );
	    strcpy( m_user[i].m_s8UserID, s8UserID );
	    strcpy( m_user[i].m_s8Address, s8Address );
	    m_user[i].m_u16Port		= u16Port;
	    
	    m_user[i].m_u32State	= US_INITIATED;
	    m_user[i].Print();
	    break;
	}
	else
	{
	    // register again
	    if( m_user[i].m_u16SlotID == u16SlotID )
	    {
		strcpy( m_user[i].m_s8TelNo, s8TelNo );
		strcpy( m_user[i].m_s8UserID, s8UserID );
		strcpy( m_user[i].m_s8Address, s8Address );
		m_user[i].m_u16Port		= u16Port;
		
		m_user[i].m_u32State	= US_INITIATED;
		m_user[i].Print();
		break;
	    }
	}
    }
}
// CDJApp::OnUserUnregister-------------------------------------------------------------------------------------------
void CDJApp::OnUserUnregister(DJ_U16 u16SlotID)
{
    for(int i= 0;i< DJ_MAX_USER;i++)
    {
	if( m_user[i].m_u16SlotID == u16SlotID )
	{
	    m_user[i].m_u32State	= US_IDLE;
	    m_user[i].m_s8Address[0]	= '\0';
	    m_user[i].m_s8TelNo[0]	= '\0';
	    m_user[i].m_s8UserID[0]	= '\0';
	    m_user[i].m_u16Port		= 0;
	    m_user[i].m_u16SlotID	= 0;
	    m_user[i].Print();
	    break;
	}
    }
}
// CDJApp::OnDialAnalyze-------------------------------------------------------------------------------------------
CDJDevice*  CDJApp::OnDialAnalyze( DJ_S8* s8TelNo, DJ_S8* s8UserID, BOOL *bVoc )
{
    if( strcmp(s8TelNo, _T("8888")) == 0 || strcmp(s8UserID, _T("8888"))== 0 )
    {
	*bVoc	= TRUE;
	// get free IVR slot
	return m_xms.AllocDevice( XMS_DEVMAIN_VOICE );
    }
    else
    {
	*bVoc	= FALSE;
	// get free voip slot
	return m_xms.AllocDevice(XMS_DEVMAIN_VOIP);
    }
}
// CDJApp::OnCallIn-------------------------------------------------------------------------------------------
void CDJApp::OnCallIn( CDJVoip* caller, DJ_S8* s8CallerTelNo, DJ_S8* s8CallerUserID, DJ_S8* s8CalleeTelNo, DJ_S8* s8CalleeUserID )
{
    BOOL bTransfer	= (caller->GetState() != DCS_CALLIN);
    // get caller user
    CDJUser* callerUser	= GetUser( s8CallerTelNo, s8CallerUserID);
    if( NULL == callerUser )
    {
	caller->ClearCall();
	return;
    }
    // set user name
    strcpy(caller->m_s8UserID, callerUser->m_s8TelNo);
    // dial analyze
    CDJUser* calleeUser	= GetUser( s8CalleeTelNo, s8CalleeUserID);
    if( NULL == calleeUser )
    {
	caller->ClearCall();
	return;
    }
    BOOL bIVR	= FALSE;
    CDJDevice* callee	= OnDialAnalyze(s8CalleeTelNo, s8CalleeUserID, &bIVR);
    // 
    if( NULL != callee )
    {
	// alloc call
	CDJCall* call	= AllocCall();
	// init call info
	call->m_nState	= CS_ORIGINATED;
	call->m_caller	= caller;
	call->m_callee	= callee;
	caller->SetCall(call);
	callee->SetCall(call);
	caller->SetUser(callerUser);
	callee->SetUser(calleeUser);
	if( !bIVR )
	{
	    // set caller media info
	    callee->SendMsg( XMS_EVT_SET_MEDIAINFO, caller->GetMediaInfo() );
	    // make call
	    callee->MakeCall(s8CallerTelNo, s8CalleeTelNo);
	}
	else
	{
	    // answer call
	    caller->AnswerCall(1, TRUE, bTransfer);
	    CDJRtp* rtp	= caller->GetRtp();
	    // play voice
	    MixerControlParam_t paramMixer = {0};
	    paramMixer.m_u8SRC1_Ctrl = XMS_MIXER_FROM_PLAY;
	    paramMixer.m_u16SRC_ChID1 = callee->GetDevice()->m_s16ChannelID;
	    // send SetParam command
	    XMS_ctsSetParam(m_xms.Handler(), rtp->GetDevice(),VOIP_PARAM_RTPMIXER, sizeof(paramMixer), &paramMixer);
	    
	    ((CDJVoice*)callee)->SetProperty(XMS_Alaw_type, XMS_PLAY_TYPE_FILE,XMS_SRC_8K);
	    ((CDJVoice*)callee)->Play("C:\\DJKeygoe\\Samples\\Voc\\ConfMusi.Pcm");//BANK001-L16.WAV"); 
	    call->OnPlay();
	}
    }
}
// CDJApp::OnQueryDeviceEnd-------------------------------------------------------------------------------------------
void CDJApp::OnQueryDeviceEnd()
{
    
}
// CDJApp::OnReferResult-------------------------------------------------------------------------------------------
void CDJApp::OnReferResult(CDJDevice* caller, DJ_U8 u8State, DJ_U8 u8Reason)
{
    CDJCall* call	= NULL;
    // get refer call
    for( int i= 0;i< DJ_MAX_CALL;i++ )
    {
	if( m_call[i].m_nState == CS_NULL )
	    continue;
	
	if( (m_call[i].GetState() == CS_TRANSLATE) 
	    && (m_call[i].GetCallee() == caller || m_call[i].GetCaller() == caller)
	    )
	{
	    call	= &m_call[i];
	    break;
	}
    }
    
    if( NULL == call )
    {
	return;
    }
    // clear old call for caller and callee
    if( call->GetCaller()->GetCall() != call )
    {
	if(call->GetCaller()->GetCall()->GetCaller() == call->GetCaller())
	{
	    call->GetCaller()->GetCall()->SetCaller(NULL);
	}
	else
	{
	    call->GetCaller()->GetCall()->SetCallee(NULL);
	}
	djPrint(DJ_LEVEL_LOG, "OnReferResult, clear caller."); 
    }
    ((CDJVoip*)call->GetCaller())->SetMediaInfo(((CDJVoip*)call->GetCallee())->GetMediaInfo());
    call->GetCaller()->TransferCall(NULL);
    
    call->GetCaller()->SetCall(call);
    //	call->GetCallee()->SetCall(call);
    call->m_nState	= CS_CONNECTED;
    //	call->GetCallee()->SetRefer(TRUE);
    
    call->Print();
}