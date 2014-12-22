// DlgRtpxAddr.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgRtpxAddr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRtpxAddr dialog


CDlgRtpxAddr::CDlgRtpxAddr(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRtpxAddr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRtpxAddr)
	m_uiPort = 0;
	//}}AFX_DATA_INIT
}


void CDlgRtpxAddr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRtpxAddr)
	DDX_Control(pDX, IDC_IPADDRESS_IP, m_IP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_uiPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRtpxAddr, CDialog)
	//{{AFX_MSG_MAP(CDlgRtpxAddr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRtpxAddr message handlers

BOOL CDlgRtpxAddr::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_IP.SetAddress(192, 168, 10, 1);
	m_uiPort = 20000;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRtpxAddr::OnOK() 
{
	// TODO: Add extra validation here
	BYTE f1, f2, f3, f4; 
	UpdateData(TRUE);
	m_IP.GetAddress(f1, f2, f3, f4);
	m_uiIP = f4;
	m_uiIP <<= 8;
	m_uiIP += f3;
	m_uiIP <<= 8;
	m_uiIP += f2;
	m_uiIP <<= 8;
	m_uiIP += f1;
	
	CDialog::OnOK();
}
