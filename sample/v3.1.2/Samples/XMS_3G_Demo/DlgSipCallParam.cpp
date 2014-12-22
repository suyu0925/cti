// DlgSipCallParam.cpp : implementation file
//

#include "stdafx.h"
#include "sp.h"
#include "DlgSipCallParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSipCallParam dialog


CDlgSipCallParam::CDlgSipCallParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSipCallParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSipCallParam)
	m_sCalleeAddr = _T("");
	m_sCalleeID = _T("");
	m_sCalleeName = _T("");
	m_uiCalleePort = 0;
	m_sCallerAddr = _T("");
	m_sCallerID = _T("");
	m_sCallerName = _T("");
	m_uiCallerPort = 0;
	//}}AFX_DATA_INIT
}


void CDlgSipCallParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSipCallParam)
	DDX_Text(pDX, IDC_EDIT_CALLEE_ADDR, m_sCalleeAddr);
	DDV_MaxChars(pDX, m_sCalleeAddr, 15);
	DDX_Text(pDX, IDC_EDIT_CALLEE_ID, m_sCalleeID);
	DDX_Text(pDX, IDC_EDIT_CALLEE_NAME, m_sCalleeName);
	DDX_Text(pDX, IDC_EDIT_CALLEE_PORT, m_uiCalleePort);
	DDX_Text(pDX, IDC_EDIT_CALLER_ADDR, m_sCallerAddr);
	DDV_MaxChars(pDX, m_sCallerAddr, 15);
	DDX_Text(pDX, IDC_EDIT_CALLER_ID, m_sCallerID);
	DDX_Text(pDX, IDC_EDIT_CALLER_NAME, m_sCallerName);
	DDX_Text(pDX, IDC_EDIT_CALLER_PORT, m_uiCallerPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSipCallParam, CDialog)
	//{{AFX_MSG_MAP(CDlgSipCallParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSipCallParam message handlers

BOOL CDlgSipCallParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_sCallerAddr.Format("");
	m_uiCallerPort = 0;
	m_sCallerName.Format("Caller");
	m_sCallerID.Format("11111");
	m_sCalleeAddr.Format("192.168.10.69");
	m_uiCalleePort = 5060;
	m_sCalleeName.Format("Callee");
	m_sCalleeID.Format("55555");
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSipCallParam::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	CDialog::OnOK();
}
