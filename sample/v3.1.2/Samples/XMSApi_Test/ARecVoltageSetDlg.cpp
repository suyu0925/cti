// ARecVoltageSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "ARecVoltageSetDlg.h"

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"
#include "XMSApi_Test_Sub.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CARecVoltageSetDlg dialog

extern CmdParamData_AnalogRecVoltage_t  g_AnalogRecVoltage;

CARecVoltageSetDlg::CARecVoltageSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CARecVoltageSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CARecVoltageSetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CARecVoltageSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CARecVoltageSetDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CARecVoltageSetDlg, CDialog)
	//{{AFX_MSG_MAP(CARecVoltageSetDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CARecVoltageSetDlg message handlers

void CARecVoltageSetDlg::OnOK() 
{
	char TmpStr[256] = {0};

	// TODO: Add extra validation here
	GetDlgItem ( IDC_EDIT_m_u8Valtage )->GetWindowText ( TmpStr, 256 );
	g_AnalogRecVoltage.m_u8Valtage = atoi(TmpStr);			


	CDialog::OnOK();
}

BOOL CARecVoltageSetDlg::OnInitDialog() 
{
	
	// TODO: Add extra initialization here
	char TmpStr[20] = {0};

	if ( 0 == g_AnalogRecVoltage.m_u8Valtage )
	{
		g_AnalogRecVoltage.m_u8Valtage = 54;
	}

	sprintf(TmpStr, "%d", g_AnalogRecVoltage.m_u8Valtage);

	GetDlgItem ( IDC_EDIT_m_u8Valtage )->SetWindowText ( TmpStr );

	CDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
