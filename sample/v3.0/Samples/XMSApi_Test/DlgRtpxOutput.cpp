// DlgRtpxOutput.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgRtpxOutput.h"
#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRtpxOutput dialog


CDlgRtpxOutput::CDlgRtpxOutput(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRtpxOutput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRtpxOutput)
	m_bEnable = FALSE;
	m_uiPayload = 0;
	m_uiPort = 0;
	m_uiSrcId = 0;
	//}}AFX_DATA_INIT
}


void CDlgRtpxOutput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRtpxOutput)
	DDX_Control(pDX, IDC_IPADDRESS_IP, m_IP);
	DDX_Control(pDX, IDC_CMB_SRCCTRL, m_cmbSrcCtrl);
	DDX_Control(pDX, IDC_CMB_MEDIATYPE, m_cmbMediaType);
	DDX_Check(pDX, IDC_CHECK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_PAYLOAD, m_uiPayload);
	DDX_Text(pDX, IDC_EDIT_PORT, m_uiPort);
	DDX_Text(pDX, IDC_EDIT_SRCID, m_uiSrcId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRtpxOutput, CDialog)
	//{{AFX_MSG_MAP(CDlgRtpxOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRtpxOutput message handlers

BOOL CDlgRtpxOutput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbMediaType.InsertString(0, "H.263P");
	m_cmbMediaType.InsertString(1, "H.263");
	m_cmbMediaType.InsertString(2, "MPE4");
	m_cmbMediaType.InsertString(3, "H.264");
	m_cmbMediaType.SetCurSel(1);

	m_cmbSrcCtrl.InsertString(0, "From NULL");
	m_cmbSrcCtrl.InsertString(1, "");
	m_cmbSrcCtrl.InsertString(2, "From Play");
	m_cmbSrcCtrl.InsertString(3, "");
	m_cmbSrcCtrl.InsertString(4, "From RTP");
	m_cmbSrcCtrl.InsertString(5, "From 3G-324M");
	m_cmbSrcCtrl.InsertString(6, "From RTPX");
	m_cmbSrcCtrl.SetCurSel(4);
	
	m_bEnable = TRUE;
	m_uiPayload = 100;
	m_uiPort = 20000;
	m_IP.SetAddress(192, 168, 10, 1);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRtpxOutput::OnOK() 
{
	// TODO: Add extra validation here
	BYTE f1, f2, f3, f4;
	UpdateData();
	m_IP.GetAddress(f1, f2, f3, f4);
	m_uiIP = f4;
	m_uiIP <<= 8;
	m_uiIP += f3;
	m_uiIP <<= 8;
	m_uiIP += f2;
	m_uiIP <<= 8;
	m_uiIP += f1;
	m_uiMediaType = m_cmbMediaType.GetCurSel()+1;
	m_uiSrcCtrl = m_cmbSrcCtrl.GetCurSel();

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
