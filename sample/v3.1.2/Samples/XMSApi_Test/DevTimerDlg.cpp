// DevTimerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DevTimerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDevTimerDlg dialog
int g_iTimerType  = 1;    //0: Timer, 1: Dev Timer
int g_iElapseTime = 0;   
int g_iSetTimerFlag = 0;

CDevTimerDlg::CDevTimerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDevTimerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDevTimerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDevTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDevTimerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDevTimerDlg, CDialog)
	//{{AFX_MSG_MAP(CDevTimerDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDevTimerDlg message handlers

void CDevTimerDlg::OnOK() 
{
    char TmpStr[20] = {0};
	int  iTmpVal = 0;

	// TODO: Add extra validation here
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_TIMER ))->GetCheck() )
		g_iTimerType = 0;
	else
		g_iTimerType = 1;

	GetDlgItem ( IDC_EDIT_ELAPSE_TIME )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );

	g_iElapseTime = iTmpVal;
    g_iSetTimerFlag = 1;

	CDialog::OnOK();
}

BOOL CDevTimerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    char TmpStr[20] = {0};
	int  iTmpVal = 0;
	
	// TODO: Add extra initialization here
	((CButton *)GetDlgItem ( IDC_RADIO_DEV_TIMER ))->SetCheck(true);

	sprintf ( TmpStr, "%d", iTmpVal );
	GetDlgItem ( IDC_EDIT_ELAPSE_TIME )->SetWindowText ( TmpStr );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
