// DlgRtpxInput.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgRtpxInput.h"
#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRtpxInput dialog


CDlgRtpxInput::CDlgRtpxInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRtpxInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRtpxInput)
	m_bEnable = FALSE;
	m_uiPayload = 0;
	//}}AFX_DATA_INIT
}


void CDlgRtpxInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRtpxInput)
	DDX_Control(pDX, IDC_CMB_MEDIATYPE, m_cmbMediaType);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_PAYLOAD, m_uiPayload);
	DDV_MinMaxUInt(pDX, m_uiPayload, 0, 127);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRtpxInput, CDialog)
	//{{AFX_MSG_MAP(CDlgRtpxInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRtpxInput message handlers

BOOL CDlgRtpxInput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbMediaType.InsertString(0, "H.263P");
	m_cmbMediaType.InsertString(1, "H.263");
	m_cmbMediaType.InsertString(2, "MPE4");
	m_cmbMediaType.InsertString(3, "H.264");
	m_cmbMediaType.SetCurSel(1);
	
	m_bEnable = TRUE;
	m_uiPayload = 100;
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRtpxInput::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	m_uiMediaType = m_cmbMediaType.GetCurSel()+1;
	switch(m_uiMediaType)
	{
	case XMS_VIDEO_CODE_TYPE_H263P:
		m_uiMediaType = VOIP_MEDIA_VIDEO_H263P;
		break;
	case XMS_VIDEO_CODE_TYPE_H263:
		m_uiMediaType = VOIP_MEDIA_VIDEO_H263;
		break;
	case XMS_VIDEO_CODE_TYPE_H264:
		m_uiMediaType = VOIP_MEDIA_VIDEO_H264;
		break;
	case XMS_VIDEO_CODE_TYPE_MP4V:
		m_uiMediaType = VOIP_MEDIA_VIDEO_MPEG4;
		break;
	default:
		m_uiMediaType = 255;
		break;
	}

	CDialog::OnOK();
}
