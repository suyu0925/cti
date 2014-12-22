// CSPPlayCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"

#include "CSPPlayCtrlDlg.h"
#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"

#include "XMSApi_Test_Sub.h"
#include "XMSApi_Test_Func.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCSPPlayCtrlDlg dialog
extern DJ_S32 g_s32CSPPlayControlType;


CCSPPlayCtrlDlg::CCSPPlayCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCSPPlayCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCSPPlayCtrlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCSPPlayCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCSPPlayCtrlDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCSPPlayCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CCSPPlayCtrlDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSPPlayCtrlDlg message handlers

void CCSPPlayCtrlDlg::OnOK() 
{
	// TODO: Add extra validation here
	if ( 1 == ((CButton*)GetDlgItem( IDC_RADIO_STOP_CSPPLAY ))->GetCheck() )
	{
		g_s32CSPPlayControlType = XMS_CSP_STOP_PLAY;		
	}

	if ( 1 == ((CButton*)GetDlgItem( IDC_RADIO_DELAY_STOP_CSPPLAY ))->GetCheck() )
	{
		g_s32CSPPlayControlType = XMS_CSP_DELAY_STOP_PLAY;		
	}

	CDialog::OnOK();
}

BOOL CCSPPlayCtrlDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
		// TODO: Add extra validation here
	if ( XMS_CSP_STOP_PLAY == g_s32CSPPlayControlType )
	{
		((CButton*)GetDlgItem( IDC_RADIO_STOP_CSPPLAY ))->SetCheck(1);
	}
	else if ( XMS_CSP_DELAY_STOP_PLAY == g_s32CSPPlayControlType )
	{
		((CButton*)GetDlgItem( IDC_RADIO_DELAY_STOP_CSPPLAY ))->SetCheck(1);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
