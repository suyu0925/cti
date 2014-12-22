// DlgRtpxMixer.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgRtpxMixer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRtpxMixer dialog


CDlgRtpxMixer::CDlgRtpxMixer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRtpxMixer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRtpxMixer)
	m_uiSrcId = 0;
	//}}AFX_DATA_INIT
}


void CDlgRtpxMixer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRtpxMixer)
	DDX_Control(pDX, IDC_CMB_SRCCTRL, m_cmbRtpxMixer);
	DDX_Text(pDX, IDC_EDIT_SRCID, m_uiSrcId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRtpxMixer, CDialog)
	//{{AFX_MSG_MAP(CDlgRtpxMixer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRtpxMixer message handlers

BOOL CDlgRtpxMixer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbRtpxMixer.InsertString(0, "From NULL");
	m_cmbRtpxMixer.InsertString(1, "");
	m_cmbRtpxMixer.InsertString(2, "From Play");
	m_cmbRtpxMixer.InsertString(3, "");
	m_cmbRtpxMixer.InsertString(4, "From RTP");
	m_cmbRtpxMixer.InsertString(5, "From 3G-324M");
	m_cmbRtpxMixer.InsertString(6, "From RTPX");
	m_cmbRtpxMixer.SetCurSel(4);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRtpxMixer::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	m_uiSrcCtrl = m_cmbRtpxMixer.GetCurSel();
	
	CDialog::OnOK();
}
