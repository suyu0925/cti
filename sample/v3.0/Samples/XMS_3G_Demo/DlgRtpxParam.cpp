// DlgRtpxParam.cpp : implementation file
//

#include "stdafx.h"
#include "SP.h"
#include "DlgRtpxParam.h"
#include <DJAcsDataDef.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRtpxParam dialog


CDlgRtpxParam::CDlgRtpxParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRtpxParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRtpxParam)
	m_bEnable = FALSE;
	m_pt = 0;
	m_bTranscode = FALSE;
	//}}AFX_DATA_INIT

	m_iDataType = 0;
	m_bEnable = TRUE;
}


void CDlgRtpxParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRtpxParam)
	DDX_Control(pDX, IDC_CMB_DATATYPE, m_cmbDataType);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_PAYLOAD, m_pt);
	DDX_Check(pDX, IDC_CHK_TRANSCODE, m_bTranscode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRtpxParam, CDialog)
	//{{AFX_MSG_MAP(CDlgRtpxParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRtpxParam message handlers

BOOL CDlgRtpxParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbDataType.InsertString(0, "H.263P");
	m_cmbDataType.InsertString(1, "H.263");
	m_cmbDataType.InsertString(2, "MPE4");
	m_cmbDataType.InsertString(3, "H.264");
	m_cmbDataType.InsertString(4, "A LAW");
	m_cmbDataType.InsertString(5, "U LAW");
	m_cmbDataType.InsertString(6, "G.723");
	m_cmbDataType.InsertString(7, "AMR");
	m_cmbDataType.SetCurSel(5);
	m_pt = 0;
	m_bTranscode = 1;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRtpxParam::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	m_iDataType = m_cmbDataType.GetCurSel();
	switch(m_iDataType)
	{
	case 0:
		m_iDataType = VOIP_MEDIA_VIDEO_H263P;
		break;
	case 1:
		m_iDataType = VOIP_MEDIA_VIDEO_H263;
		break;
	case 2:
		m_iDataType = VOIP_MEDIA_VIDEO_H264;
		break;
	case 3:
		m_iDataType = VOIP_MEDIA_VIDEO_MPEG4;
		break;
	case 4:
		m_iDataType = VOIP_MEDIA_AUDIO_PCMA;
		break;
	case 5:
		m_iDataType = VOIP_MEDIA_AUDIO_PCMU;
		break;
	case 6:
		m_iDataType = VOIP_MEDIA_AUDIO_G723;
		break;
	case 7:
		m_iDataType = VOIP_MEDIA_AUDIO_AMR;
		break;
	default:
		break;
	}
	
	CDialog::OnOK();
}
