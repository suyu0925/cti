// XMSVoIPDemoRTPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSVoIPDemo.h"
#include "XMSVoIPDemoRTPDlg.h"

#include "XMSData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXMSVoIPDemoRTPDlg dialog


CXMSVoIPDemoRTPDlg::CXMSVoIPDemoRTPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXMSVoIPDemoRTPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXMSVoIPDemoRTPDlg)
	m_iAudioTxCodec = 0;
	m_iAudioRxCodec = 0;
	m_iVideoRxCodec = 0;
	m_iVideoTxCodec = 0;
	m_strAudioIP = _T("");
	m_uAudioPort = 0;
	m_strVideoIP = _T("");
	m_uVideoPort = 0;
	m_iAudioDisable = 0;
	m_iVideoDisable = 0;
	m_cAudioRxPt = 0;
	m_cAudioTxPt = 0;
	m_cVideoRxPt = 0;
	m_cVideoTxPt = 0;
	//}}AFX_DATA_INIT
}


void CXMSVoIPDemoRTPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXMSVoIPDemoRTPDlg)
	DDX_CBIndex(pDX, IDC_COMBO_AUDIO_CODECTX, m_iAudioTxCodec);
	DDX_CBIndex(pDX, IDC_COMBO_AUDIO_CODECRX, m_iAudioRxCodec);
	DDX_CBIndex(pDX, IDC_COMBO_VIDEO_CODECRX, m_iVideoRxCodec);
	DDX_CBIndex(pDX, IDC_COMBO_VIDEO_CODECTX, m_iVideoTxCodec);
	DDX_Text(pDX, IDC_EDIT_AUDIO_IP, m_strAudioIP);
	DDX_Text(pDX, IDC_EDIT_AUDIO_PORT, m_uAudioPort);
	DDX_Text(pDX, IDC_EDIT_VIDEO_IP, m_strVideoIP);
	DDX_Text(pDX, IDC_EDIT_VIDEO_PORT, m_uVideoPort);
	DDX_Radio(pDX, IDC_RADIO_AUDIO_ENABLE, m_iAudioDisable);
	DDX_Radio(pDX, IDC_RADIO_VIDEO_ENABLE, m_iVideoDisable);
	DDX_Text(pDX, IDC_EDIT_AUDIO_PTRX, m_cAudioRxPt);
	DDX_Text(pDX, IDC_EDIT_AUDIO_PTTX, m_cAudioTxPt);
	DDX_Text(pDX, IDC_EDIT_VIDEO_PTRX, m_cVideoRxPt);
	DDX_Text(pDX, IDC_EDIT_VIDEO_PTTX, m_cVideoTxPt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXMSVoIPDemoRTPDlg, CDialog)
	//{{AFX_MSG_MAP(CXMSVoIPDemoRTPDlg)
	ON_BN_CLICKED(IDC_RADIO_AUDIO_ENABLE, validCtrl)
	ON_BN_CLICKED(IDC_RADIO_AUDIO_DISABLE, validCtrl)
	ON_BN_CLICKED(IDC_RADIO_VIDEO_ENABLE, validCtrl)
	ON_BN_CLICKED(IDC_RADIO_VIDEO_DISABLE, validCtrl)
	//}}AFX_MSG_MAP
	ON_MESSAGE(UM_UPDATEDATA, OnUpdateData)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMSVoIPDemoRTPDlg message handlers

BOOL CXMSVoIPDemoRTPDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	GetDlgItem(IDC_EDIT_IP)->SetFocus();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CXMSVoIPDemoRTPDlg::OnOK() 
{
	UpdateData();

	if (!m_iAudioDisable)
	{
		if (m_strAudioIP.IsEmpty())
		{
			MessageBox(_T("Please fill IP address"));
			GetDlgItem(IDC_EDIT_AUDIO_IP)->SetFocus();
			return;
		}

		if (m_uAudioPort == 0)
		{
			MessageBox(_T("Please fill port"));
			GetDlgItem(IDC_EDIT_AUDIO_PORT)->SetFocus();
			return;
		}
	}

	// set rtp session enable/disable
	Acs_VoIP_RTPSESSION paramRtpSession = {0};
	paramRtpSession.m_u8Enable = !m_iAudioDisable || !m_iVideoDisable;
//	paramRtpSession.m_u8PayloadDtmf = 100;
//	paramRtpSession.m_u8PayloadTone = 101;
	XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[m_iDeviceIP].device, VOIP_PARAM_RTPSESSION, sizeof(paramRtpSession), &paramRtpSession);

	// set rtp address
	m_paramAddr.audio.m_u8Enable = !m_iAudioDisable;
	if (m_paramAddr.audio.m_u8Enable)
	{
		strcpy(m_paramAddr.audio.m_s8IP, m_strAudioIP);
		m_paramAddr.audio.m_u16Port = m_uAudioPort;
	}

	m_paramAddr.video.m_u8Enable = !m_iVideoDisable;
	if (m_paramAddr.video.m_u8Enable)
	{
		strcpy(m_paramAddr.video.m_s8IP, m_strVideoIP);
		m_paramAddr.video.m_u16Port = m_uVideoPort;
	}

	XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[m_iDeviceIP].device, VOIP_PARAM_RTPADDR, sizeof(m_paramAddr), &m_paramAddr);

	// set rtp codex
	const int idAudioCodec[] =
	{
		VOIP_MEDIA_AUDIO_PCMU,
		VOIP_MEDIA_AUDIO_PCMA,
		VOIP_MEDIA_AUDIO_G723,
		VOIP_MEDIA_AUDIO_G729
	};

	const int idVideoCodec[] =
	{
		VOIP_MEDIA_VIDEO_H261,
		VOIP_MEDIA_VIDEO_H263,
		VOIP_MEDIA_VIDEO_H263P,
		VOIP_MEDIA_VIDEO_MPEG4,
		VOIP_MEDIA_VIDEO_H264
	};

	m_paramCodec.audio.m_u8Enable = !m_iAudioDisable;
	if (m_paramCodec.audio.m_u8Enable)
	{
		m_paramCodec.audio.m_u8TxCodec = idAudioCodec[m_iAudioTxCodec];
		m_paramCodec.audio.m_u8TxPayloadType = m_cAudioTxPt;

		m_paramCodec.audio.m_u8RxCodec = idAudioCodec[m_iAudioRxCodec];
		m_paramCodec.audio.m_u8RxPayloadType = m_cAudioRxPt;
	}

	m_paramCodec.video.m_u8Enable = !m_iVideoDisable;
	if (m_paramCodec.video.m_u8Enable)
	{
		m_paramCodec.video.m_u8TxCodec = idVideoCodec[m_iVideoTxCodec];
		m_paramCodec.video.m_u8TxPayloadType = m_cVideoTxPt;

		m_paramCodec.video.m_u8RxCodec = idVideoCodec[m_iVideoRxCodec];
		m_paramCodec.video.m_u8RxPayloadType = m_cVideoRxPt;
	}

	XMS_ctsSetParam(g_acsHandle, &g_deviceVoIP[m_iDeviceIP].device, VOIP_PARAM_RTPCODEC, sizeof(m_paramCodec), &m_paramCodec);

	CDialog::OnOK();
}

LRESULT CXMSVoIPDemoRTPDlg::OnUpdateData(WPARAM paramType, LPARAM paramData)
{
	switch (paramType)
	{
	case VOIP_PARAM_RTPADDR:
		{
			m_paramAddr = *(Acs_VoIP_RTPADDR *)paramData;

			m_iAudioDisable = !m_paramAddr.audio.m_u8Enable;
			m_strAudioIP = m_paramAddr.audio.m_s8IP;
			m_uAudioPort = m_paramAddr.audio.m_u16Port;

			m_iVideoDisable = !m_paramAddr.video.m_u8Enable;
			m_strVideoIP = m_paramAddr.video.m_s8IP;
			m_uVideoPort = m_paramAddr.video.m_u16Port;
		}
		break;

	case VOIP_PARAM_RTPCODEC:
		{
			m_paramCodec = *(Acs_VoIP_RTPCODEC *)paramData;

			m_iAudioDisable = !m_paramCodec.audio.m_u8Enable;
			m_iAudioRxCodec = m_iAudioDisable ? 0 : m_paramCodec.audio.m_u8RxCodec;
			m_cAudioRxPt = m_paramCodec.audio.m_u8RxPayloadType;
			m_iAudioTxCodec = m_iAudioDisable ? 0 : m_paramCodec.audio.m_u8TxCodec;
			m_cAudioTxPt = m_paramCodec.audio.m_u8TxPayloadType;

			m_iVideoDisable = !m_paramCodec.video.m_u8Enable;
			m_iVideoRxCodec = m_iVideoDisable ? 0 : m_paramCodec.video.m_u8RxCodec-0x80;
			m_cVideoRxPt = m_paramCodec.video.m_u8RxPayloadType;
			m_iVideoTxCodec = m_iVideoDisable ? 0 : m_paramCodec.video.m_u8TxCodec-0x80;
			m_cVideoTxPt = m_paramCodec.video.m_u8TxPayloadType;
		}
		break;
	}

	UpdateData(FALSE);

	validCtrl();

	return TRUE;
}

void CXMSVoIPDemoRTPDlg::validCtrl()
{
	UpdateData();

	GetDlgItem(IDC_EDIT_AUDIO_IP)->EnableWindow(!m_iAudioDisable);
	GetDlgItem(IDC_EDIT_AUDIO_PORT)->EnableWindow(!m_iAudioDisable);
	GetDlgItem(IDC_COMBO_AUDIO_CODECTX)->EnableWindow(!m_iAudioDisable);
	GetDlgItem(IDC_EDIT_AUDIO_PTTX)->EnableWindow(!m_iAudioDisable);
	GetDlgItem(IDC_COMBO_AUDIO_CODECRX)->EnableWindow(!m_iAudioDisable);
	GetDlgItem(IDC_EDIT_AUDIO_PTRX)->EnableWindow(!m_iAudioDisable);

	GetDlgItem(IDC_EDIT_VIDEO_IP)->EnableWindow(!m_iVideoDisable);
	GetDlgItem(IDC_EDIT_VIDEO_PORT)->EnableWindow(!m_iVideoDisable);
	GetDlgItem(IDC_COMBO_VIDEO_CODECTX)->EnableWindow(!m_iVideoDisable);
	GetDlgItem(IDC_EDIT_VIDEO_PTTX)->EnableWindow(!m_iVideoDisable);
	GetDlgItem(IDC_COMBO_VIDEO_CODECRX)->EnableWindow(!m_iVideoDisable);
	GetDlgItem(IDC_EDIT_VIDEO_PTRX)->EnableWindow(!m_iVideoDisable);
}
