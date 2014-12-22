// DlgAddr.cpp : implementation file
//

#include "stdafx.h"
#include "SP.h"
#include "DlgAddr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAddr dialog


CDlgAddr::CDlgAddr(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAddr)
	m_Port = 0;
	//}}AFX_DATA_INIT
}


void CDlgAddr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAddr)
	DDX_Control(pDX, IDC_IPADDRESS1, m_IP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAddr, CDialog)
	//{{AFX_MSG_MAP(CDlgAddr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAddr message handlers

void CDlgAddr::OnOK() 
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

BOOL CDlgAddr::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_IP.SetAddress(192, 168, 10, 69);
	m_Port = 20000;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
