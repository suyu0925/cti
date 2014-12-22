// CSPRecCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "CSPRecCtrlDlg.h"
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
// CCSPRecCtrlDlg dialog

extern DJ_S32 g_s32CSPRecControlType;

CCSPRecCtrlDlg::CCSPRecCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCSPRecCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCSPRecCtrlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCSPRecCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCSPRecCtrlDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCSPRecCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CCSPRecCtrlDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSPRecCtrlDlg message handlers

void CCSPRecCtrlDlg::OnOK() 
{
	CSP_OPERATER*pCSP = GetCurrVocCSPProperty( );

	if ( NULL == pCSP )
		return;
	
	// TODO: Add extra validation here
	if ( 1 == ((CButton*)GetDlgItem( IDC_RADIO_STOP_CSPREC ))->GetCheck() )
	{
		g_s32CSPRecControlType = XMS_CSP_STOP_RECORD;		
	}

	if ( 1 == ((CButton*)GetDlgItem( IDC_RADIO_DELAY_STOP_CSPREC ))->GetCheck() )
	{
		g_s32CSPRecControlType = XMS_CSP_DELAY_STOP_RECORD;		
	}

	pCSP->m_s32CSPRecControlType = g_s32CSPRecControlType;
	
	CDialog::OnOK();
}

BOOL CCSPRecCtrlDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CSP_OPERATER*pCSP = GetCurrVocCSPProperty( );

	if ( NULL == pCSP )
		return 0;
	
	// TODO: Add extra initialization here
		// TODO: Add extra validation here

	g_s32CSPRecControlType = pCSP->m_s32CSPRecControlType;
	if ( XMS_CSP_STOP_RECORD == g_s32CSPRecControlType )
	{
		((CButton*)GetDlgItem( IDC_RADIO_STOP_CSPREC ))->SetCheck(1);
	}
	else if ( XMS_CSP_DELAY_STOP_RECORD == g_s32CSPRecControlType )
	{
		((CButton*)GetDlgItem( IDC_RADIO_DELAY_STOP_CSPREC ))->SetCheck(1);
	}else
	{
		((CButton*)GetDlgItem( IDC_RADIO_STOP_CSPREC ))->SetCheck(1);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
