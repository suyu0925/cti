// DlgMediaExParam.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgMediaExParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMediaExParam dialog


CDlgMediaExParam::CDlgMediaExParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMediaExParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMediaExParam)
	m_uiChNum = 0;
	//}}AFX_DATA_INIT
}


void CDlgMediaExParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMediaExParam)
	DDX_Control(pDX, IDC_CMB_PARAMTYPE, m_cmbParamType);
	DDX_Text(pDX, IDC_EDIT_CHNUM, m_uiChNum);
	DDV_MinMaxUInt(pDX, m_uiChNum, 0, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMediaExParam, CDialog)
	//{{AFX_MSG_MAP(CDlgMediaExParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMediaExParam message handlers

BOOL CDlgMediaExParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbParamType.InsertString(0, "INPUT");
	m_cmbParamType.InsertString(1, "OUTPUT");
	m_cmbParamType.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMediaExParam::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	m_iParamType = m_cmbParamType.GetCurSel();

	CDialog::OnOK();
}
