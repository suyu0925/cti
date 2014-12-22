// FaxECMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "FaxECMDlg.h"

#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern Acs_SetECM       g_FaxECMCmd;

/////////////////////////////////////////////////////////////////////////////
// CFaxECMDlg dialog


CFaxECMDlg::CFaxECMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFaxECMDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFaxECMDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFaxECMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFaxECMDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFaxECMDlg, CDialog)
	//{{AFX_MSG_MAP(CFaxECMDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaxECMDlg message handlers

void CFaxECMDlg::OnOK() 
{
	// TODO: Add extra validation here
	// TODO: Add extra validation here
		// TODO: Add extra validation here
//	char TmpStr[20];
//	int iTmpVal;

	memset(&g_FaxECMCmd, 0, sizeof(g_FaxECMCmd) );
	if (((CButton *)GetDlgItem ( IDC_CHECK_FAX_NORMAL ))->GetCheck())
	{
		g_FaxECMCmd.m_u8FaxECMMode = XMS_FAX_ECM_MODE_TYPE_NORMAL;
	}

	if (((CButton *)GetDlgItem ( IDC_CHECK_FAX_ECM ))->GetCheck())
	{
		g_FaxECMCmd.m_u8FaxECMMode = XMS_FAX_ECM_MODE_TYPE_ECM;	
	}

	CDialog::OnOK();
}

BOOL CFaxECMDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if ( XMS_FAX_ECM_MODE_TYPE_NORMAL == g_FaxECMCmd.m_u8FaxECMMode)
		((CButton *)GetDlgItem ( IDC_CHECK_FAX_NORMAL ))->SetCheck(TRUE);
	else
		((CButton *)GetDlgItem ( IDC_CHECK_FAX_ECM ))->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
