// DlgIODataUII.cpp : implementation file
//

#include "stdafx.h"
#include "SP.h"
#include "DlgIODataUII.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIODataUII dialog


CDlgIODataUII::CDlgIODataUII(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIODataUII::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIODataUII)
	m_sAlphanumeric = _T("");
	m_sSignal = _T("");
	m_nUIIType = -1;
	//}}AFX_DATA_INIT
}


void CDlgIODataUII::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIODataUII)
	DDX_Text(pDX, IDC_EDIT_ALPHANUMERIC, m_sAlphanumeric);
	DDV_MaxChars(pDX, m_sAlphanumeric, 125);
	DDX_Text(pDX, IDC_EDIT_SIGNAL, m_sSignal);
	DDV_MaxChars(pDX, m_sSignal, 1);
	DDX_Radio(pDX, IDC_RADIO_SIGNAL, m_nUIIType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIODataUII, CDialog)
	//{{AFX_MSG_MAP(CDlgIODataUII)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIODataUII message handlers

BOOL CDlgIODataUII::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_sSignal = "0";
	m_sAlphanumeric = "1234567890ABCDEFGH";
	m_nUIIType = 0;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgIODataUII::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);

	CDialog::OnOK();
}
