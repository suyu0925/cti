// DlgParamType.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgParamType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgParamType dialog


CDlgParamType::CDlgParamType(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgParamType::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgParamType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgParamType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgParamType)
	DDX_Control(pDX, IDC_CMB_PARAMTYPE, m_cmbParamType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgParamType, CDialog)
	//{{AFX_MSG_MAP(CDlgParamType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgParamType message handlers

BOOL CDlgParamType::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbParamType.InsertString(0, "INPUT");
	m_cmbParamType.InsertString(1, "OUTPUT");
	m_cmbParamType.InsertString(2, "MIXER");
	m_cmbParamType.InsertString(3, "ADDR");
	m_cmbParamType.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgParamType::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	m_iParamType = m_cmbParamType.GetCurSel();
	
	CDialog::OnOK();
}
