// DlgSetVoIPParams.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgSetVoIPParams.h"
#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern Acs_VoIP_MediaInfo	g_VoIP_MediaInfo;
extern Acs_VoIP_RTPSESSION	g_RTP_Session;
extern Acs_VoIP_RTPADDR		g_RTP_Addr;
extern Acs_VoIP_RTPCODEC	g_RTP_Codec;
extern Acs_VoIP_RTPOpen		g_RTP_Open;

/////////////////////////////////////////////////////////////////////////////
// CDlgSetVoIPParams dialog

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
		"PCMU", 				// MIME subtype name
		"g711Ulaw64k"			// h.245 capability name
	},
	{	// g.711 a-law
		VOIP_MEDIA_AUDIO_PCMA,	// media id
		8,						// rtp payload type
		"PCMA", 				// MIME subtype name
		"g711Alaw64k"			// h.245 capability name
	},
	{	// g.723
		VOIP_MEDIA_AUDIO_G723,	// media id
		4,						// rtp payload type
		"G723", 				// MIME subtype name
		"g7231" 				// h.245 capability name
	},
	{	// g.729
		VOIP_MEDIA_AUDIO_G729,	// media id
		18, 					// rtp payload type
		"G729", 				// MIME subtype name
		"g729"					// h.245 capability name (prefix for g729, g729AnnexA, g729wAnnexB, g729AnnexAwAnnexB)
	},
	{	// amr-nb
			VOIP_MEDIA_AUDIO_AMR,	// media id
			96, 					// rtp payload type (dynamic)
			"AMR",					// MIME subtype name
			"amr"					// h.245 capability name
		},
		/*	{	// t.38/rtp
		VOIP_MEDIA_AUDIO_T38,	// media id
		97, 					// rtp payload type (dynamic)
		"t38",					// MIME subtype name
		"t38fax"				// h.245 capability name
	},*/
	// video capabilities
	{	// h.261
		VOIP_MEDIA_VIDEO_H261,	// media id
		31, 					// rtp payload type
		"H261", 				// MIME subtype name
		"h261VideoCapability"	// h.245 capability name 
	},
	{	// h.263
		VOIP_MEDIA_VIDEO_H263,	// media id
		34, 					// rtp payload type
		"H263", 				// MIME subtype name
		"h263VideoCapability"	// h.245 capability name 
	},
	{	// h.263+
		VOIP_MEDIA_VIDEO_H263P, // media id
		100,					// rtp payload type (dynamic)
		"H263-1998",			// MIME subtype name
		"h263VideoCapability98" // h.245 capability name 
	},
	{	// mpeg-4/visual
		VOIP_MEDIA_VIDEO_MPEG4, // media id
		101,					// rtp payload type (dynamic)
		"MP4V-ES",				// MIME subtype name
		"genericVideoCapability"// h.245 capability name 
	},
	{	// h.264
		VOIP_MEDIA_VIDEO_H264,	// media id
		102,					// rtp payload type (dynamic)
		"H264", 				// MIME subtype name
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


CDlgSetVoIPParams::CDlgSetVoIPParams(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetVoIPParams::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetVoIPParams)
	m_bV = FALSE;
	m_bA = TRUE;
	m_nDtmf = 101;
	m_nTone = 0;
	m_szIPV = _T("");
	m_nPortV = 0;
	m_szIPA = _T("192.168.10.36");
	m_nPortA = 10000;
	m_szCapsA = _T("");
	m_szCapsV = _T("");
	m_bRTPAddr = TRUE;
	m_bRTPCodec = TRUE;
	m_bRTPSession = TRUE;
	m_bVoIPMedia = TRUE;
	m_bOpenRTP = TRUE;
	m_bUseDsp = TRUE;
	m_szDSPIP = _T("192.168.10.36");
	m_nDspPort = 0;
	//}}AFX_DATA_INIT
}

void CDlgSetVoIPParams::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetVoIPParams)
	DDX_Check(pDX, IDC_CHECK_VIDEO, m_bV);
	DDX_Check(pDX, IDC_CHECK_AUDIO, m_bA);
	DDX_Text(pDX, IDC_EDIT_DTMF, m_nDtmf);
	DDX_Text(pDX, IDC_EDIT_TONE, m_nTone);
	DDX_Text(pDX, IDC_EDIT_VIDEO_ADDR, m_szIPV);
	DDX_Text(pDX, IDC_EDIT_VIDEO_PORT, m_nPortV);
	DDX_Text(pDX, IDC_EDIT_AUDIO_ADDR, m_szIPA);
	DDX_Text(pDX, IDC_EDIT_AUDIO_PORT, m_nPortA);
	DDX_Text(pDX, IDC_EDIT_CAPSLIST_A, m_szCapsA);
	DDX_Text(pDX, IDC_EDIT_CAPSLIST_V, m_szCapsV);
	DDX_Check(pDX, IDC_CHECK_RTP_ADDR, m_bRTPAddr);
	DDX_Check(pDX, IDC_CHECK_RTP_CODEC, m_bRTPCodec);
	DDX_Check(pDX, IDC_CHECK_RTP_SESSION, m_bRTPSession);
	DDX_Check(pDX, IDC_CHECK_VOIP_MEDIA, m_bVoIPMedia);
	DDX_Check(pDX, IDC_CHECK_OPEN_RTP, m_bOpenRTP);
	DDX_Check(pDX, IDC_CHECK_USE_DSP, m_bUseDsp);
	DDX_Text(pDX, IDC_EDIT_DSP_ADDR, m_szDSPIP);
	DDX_Text(pDX, IDC_EDIT_DSP_PORT, m_nDspPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgSetVoIPParams, CDialog)
	//{{AFX_MSG_MAP(CDlgSetVoIPParams)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetVoIPParams message handlers

void CDlgSetVoIPParams::OnOK() 
{
	int i;
	int j;
	// TODO: Add extra validation here
	UpdateData();
	memset(&g_VoIP_MediaInfo, 0, sizeof(g_VoIP_MediaInfo));
	memset(&g_RTP_Addr, 0, sizeof(g_RTP_Addr));
	memset(&g_RTP_Session, 0, sizeof(g_RTP_Session));
	memset(&g_RTP_Codec, 0, sizeof(g_RTP_Codec));

	DJ_U8 capsV[10], capsA[10];
	int icountV=0;
	int icountA=0;

	if(m_bA)
	{
		char buf[128] = "\0";
		strcpy(buf, m_szCapsA);
		char* p = buf;
		while(true)
		{
			int ncap = atoi(p);
			for( i=0;i<icountA;++i)
			{
				if(capsA[i]==ncap)
					break;
			}
			if(i>=icountA)
				capsA[icountA++] = ncap;
			if(icountA>=10)
				break;
			p = strchr(p, ',');
			if(p==NULL)
				break;
			++p;
		}
	}
	if(m_bV)
	{
		char buf[128] = "\0";
		strcpy(buf, m_szCapsV);
		char* p = buf;
		while(true)
		{
			int ncap = atoi(p);
			for( i=0;i<icountV;++i)
			{
				if(capsV[i]==ncap)
					break;
			}
			if(i>=icountV)
				capsV[icountV++] = ncap;
			if(icountV>=10)
				break;
			p = strchr(p, ',');
			if(p==NULL)
				break;
			++p;
		}
	}

	if(m_bVoIPMedia)
	{
		g_VoIP_MediaInfo.payload_dtmf = m_nDtmf;
		g_VoIP_MediaInfo.payload_tone= m_nTone;

		g_VoIP_MediaInfo.u8AudioEnabled = m_bA?1:0;
		if(m_bA)
		{
			if(m_bUseDsp)
			{
				strcpy(g_VoIP_MediaInfo.s8AudioAddress, m_szDSPIP);
				g_VoIP_MediaInfo.u16AudioPort = m_nDspPort;
			}
			else
			{
				strcpy(g_VoIP_MediaInfo.s8AudioAddress, m_szIPA);
				g_VoIP_MediaInfo.u16AudioPort = m_nPortA;
			}
			memcpy(g_VoIP_MediaInfo.u8MediaCapList, capsA, sizeof(DJ_U8)*icountA);
			g_VoIP_MediaInfo.u8MediaCapNum = icountA;
		}

		g_VoIP_MediaInfo.u8VideoEnabled = m_bV?1:0;
		if(m_bV)
		{
			if(m_bUseDsp)
			{
				strcpy(g_VoIP_MediaInfo.s8AudioAddress, m_szDSPIP);
				g_VoIP_MediaInfo.u16AudioPort = m_nDspPort;
			}
			else
			{
				strcpy(g_VoIP_MediaInfo.s8VideoAddress, m_szIPV);
				g_VoIP_MediaInfo.u16VideoPort = m_nPortV;
			}
			if(m_bA)
			{
				for( i=0;i<icountV;++i)
				{
					for(int j=0;j<icountA && capsV[i]!=capsA[j];++j) ;
					if(j>=icountA)
						g_VoIP_MediaInfo.u8MediaCapList[g_VoIP_MediaInfo.u8MediaCapNum++] = capsV[i];
				}
			}
			else
			{
				memcpy(g_VoIP_MediaInfo.u8MediaCapList, capsV, sizeof(DJ_U8)*icountV);
				g_VoIP_MediaInfo.u8MediaCapNum = icountV;
			}
		}
	}
	
	if(m_bRTPSession)
	{
		g_RTP_Session.m_u8Enable = m_bA?1:0;
		g_RTP_Session.m_u8PayloadDtmf = m_nDtmf;
		g_RTP_Session.m_u8PayloadTone = m_nTone;
	}
	
	if(m_bRTPAddr)
	{
		g_RTP_Addr.audio.m_u8Enable = m_bA?1:0;
		if(m_bA)
		{
			strcpy(g_RTP_Addr.audio.m_s8IP, m_szIPA);
			g_RTP_Addr.audio.m_u16Port = m_nPortA;
		}
		g_RTP_Addr.video.m_u8Enable = m_bV?1:0;
		if(m_bV)
		{
			strcpy(g_RTP_Addr.video.m_s8IP, m_szIPV);
			g_RTP_Addr.video.m_u16Port = m_nPortV;
		}
	}
	
	if(m_bRTPCodec)
	{
		g_RTP_Codec.audio.m_u8Enable		= m_bA?1:0;
		if(m_bA)
		{
			g_RTP_Codec.audio.m_u8TxCodec		= capsA[0];
			g_RTP_Codec.audio.m_u8RxCodec		= g_RTP_Codec.audio.m_u8TxCodec;
			DJ_U8 u8CodePayload	= 0;
			for(int i= 0;i< 10;i++ )
			{
				if( g_rtp_codec[i].u8CodecType == capsA[0] )
				{
					u8CodePayload	= g_rtp_codec[i].u8PayloadType;
					break;
				}
			}
			g_RTP_Codec.audio.m_u8TxPayloadType	= u8CodePayload;
			g_RTP_Codec.audio.m_u8RxPayloadType	= g_RTP_Codec.audio.m_u8TxPayloadType;
		}
		
		g_RTP_Codec.video.m_u8Enable		= m_bV?1:0;
		if(m_bV)
		{
			g_RTP_Codec.video.m_u8TxCodec		= capsV[0];
			g_RTP_Codec.video.m_u8RxCodec		= g_RTP_Codec.video.m_u8TxCodec;
			DJ_U8 u8CodePayload	= 0;
			for( i= 0;i< 10;i++ )
			{
				if( g_rtp_codec[i].u8CodecType == capsA[0] )
				{
					u8CodePayload	= g_rtp_codec[i].u8PayloadType;
					break;
				}
			}
			g_RTP_Codec.video.m_u8TxPayloadType	= u8CodePayload;
			g_RTP_Codec.video.m_u8RxPayloadType	= g_RTP_Codec.video.m_u8TxPayloadType;
		}
	}

	if(m_bOpenRTP)
	{
		g_RTP_Open.m_u8Enable = 1;
		g_RTP_Open.m_u8PayloadDtmf = m_nDtmf;
		g_RTP_Open.m_u8PayloadTone = m_nTone;
		g_RTP_Open.audio.m_u8Enable = m_bA?1:0;
		if(m_bA)
		{
			g_RTP_Open.audio.m_u8RxCodec = capsA[0];
			g_RTP_Open.audio.m_u8TxCodec = g_RTP_Open.audio.m_u8RxCodec;
			DJ_U8 u8CodePayload	= 0;
			for( i= 0;i< 10;i++ )
			{
				if( g_rtp_codec[i].u8CodecType == g_RTP_Open.audio.m_u8RxCodec )
				{
					u8CodePayload	= g_rtp_codec[i].u8PayloadType;
					break;
				}
			}
			g_RTP_Open.audio.m_u8RxPayloadType = u8CodePayload;
			g_RTP_Open.audio.m_u8TxPayloadType = g_RTP_Open.audio.m_u8RxPayloadType;
		}
		g_RTP_Open.video.m_u8Enable = m_bV?1:0;
		if(m_bV)
		{
			g_RTP_Open.video.m_u8RxCodec = capsV[0];
			g_RTP_Open.video.m_u8TxCodec = g_RTP_Open.video.m_u8RxCodec;
			DJ_U8 u8CodePayload	= 0;
			for( i= 0;i< 10;i++ )
			{
				if( g_rtp_codec[i].u8CodecType == g_RTP_Open.video.m_u8RxCodec )
				{
					u8CodePayload	= g_rtp_codec[i].u8PayloadType;
					break;
				}
			}
			g_RTP_Open.video.m_u8RxPayloadType = u8CodePayload;
			g_RTP_Open.video.m_u8TxPayloadType = g_RTP_Open.video.m_u8RxPayloadType;
		}
	}

	CDialog::OnOK();
}

BOOL CDlgSetVoIPParams::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_bA = g_VoIP_MediaInfo.u8AudioEnabled;
	m_szIPA = g_VoIP_MediaInfo.s8AudioAddress;
	m_nPortA = g_VoIP_MediaInfo.u16AudioPort;
	for(int i=0; i<g_VoIP_MediaInfo.u8MediaCapNum; ++i)
	{
		CString str;
		str.Format("%d", g_VoIP_MediaInfo.u8MediaCapList[i]);
		if(i!=0)
			m_szCapsA += ",";
		m_szCapsA += str;
	}
	m_bV = g_VoIP_MediaInfo.u8VideoEnabled;
	m_szIPV = g_VoIP_MediaInfo.s8VideoAddress;
	m_nPortV = g_VoIP_MediaInfo.u16VideoPort;
	m_szCapsV = "";

	m_nDtmf = g_VoIP_MediaInfo.payload_dtmf;
	m_nTone = g_VoIP_MediaInfo.payload_tone;

	UpdateData(FALSE);
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
