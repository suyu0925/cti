// RecModModeSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "RecModModeSetDlg.h"

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"
#include "XMSApi_Test_Sub.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecModModeSetDlg dialog
extern DigRecSwitchMode                  g_RecModCfg;


CRecModModeSetDlg::CRecModModeSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecModModeSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecModModeSetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRecModModeSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecModModeSetDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecModModeSetDlg, CDialog)
	//{{AFX_MSG_MAP(CRecModModeSetDlg)
	ON_BN_CLICKED(IDC_RADIO_RDMS_ENABLE, OnRadioRdmsEnable)
	ON_BN_CLICKED(IDC_RADIO_RDMS_Disable, OnRADIORDMSDisable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecModModeSetDlg message handlers

BOOL CRecModModeSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetConfig();

    if ( 1 == g_RecModCfg.m_u8Enable )
	{
		ShowDefWindow(true);
	}
	else
	{
		ShowDefWindow(false);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRecModModeSetDlg::OnOK() 
{
	// TODO: Add extra validation here
	GetConfig();

	CDialog::OnOK();
}

void CRecModModeSetDlg::OnRadioRdmsEnable() 
{
	// TODO: Add your control notification handler code here
		/*init the button state*/
	/*((CButton *)GetDlgItem ( IDC_RADIO_ANV ))->SetCheck(TRUE);
	((CButton *)GetDlgItem ( IDC_RADIO_AUDIO_NO_INDEX ))->SetCheck(TRUE);
	((CButton *)GetDlgItem ( IDC_RADIO_VIDEO_NO_INDEX ))->SetCheck(TRUE);*/

	ShowDefWindow(true);

}

void CRecModModeSetDlg::OnRADIORDMSDisable() 
{
	// TODO: Add your control notification handler code here
	ShowDefWindow(false);

}

void CRecModModeSetDlg::ShowDefWindow( bool bVal ) 
{
	// TODO: Add your control notification handler code here
	GetDlgItem ( IDC_RADIO_XMS_DRS_SWITCH_AVAYA )->EnableWindow(bVal);
	GetDlgItem ( IDC_RADIO_XMS_DRS_SWITCH_SIMENZ )->EnableWindow(bVal);

	GetDlgItem ( IDC_RADIO_XMS_DRS_SWITCH_TADIRANT )->EnableWindow(bVal);
	GetDlgItem ( IDC_RADIO_XMS_DRS_SWITCH_ERRICSION )->EnableWindow(bVal);

	GetDlgItem ( IDC_RADIO_XMS_DRS_SWITCH_TOSHIBA )->EnableWindow(bVal);

	GetDlgItem ( IDC_RADIO_XMS_Alaw_type )->EnableWindow(bVal);
	GetDlgItem ( IDC_RADIO_XMS_Ulaw_type )->EnableWindow(bVal);

	GetDlgItem ( IDC_RADIO_RDMS_ENABLE_SigData )->EnableWindow(bVal);
	GetDlgItem ( IDC_RADIO_RDMS_Disable_SigData )->EnableWindow(bVal);

}

void CRecModModeSetDlg::GetConfig( ) 
{
	// TODO: Add your control notification handler code here
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_RDMS_ENABLE ))->GetCheck() )
	{
		g_RecModCfg.m_u8Enable = 1;
	}
	else
	{
		g_RecModCfg.m_u8Enable = 0;
	}

	if ( ((CButton *)GetDlgItem ( IDC_RADIO_XMS_DRS_SWITCH_AVAYA ))->GetCheck() )
		g_RecModCfg.m_u8SwitchMode = XMS_DRS_SWITCH_AVAYA;
	else if ( ((CButton *)GetDlgItem ( IDC_RADIO_XMS_DRS_SWITCH_SIMENZ ))->GetCheck() )
		g_RecModCfg.m_u8SwitchMode = XMS_DRS_SWITCH_SIMENZ;
	else if ( ((CButton *)GetDlgItem ( IDC_RADIO_XMS_DRS_SWITCH_TADIRANT ))->GetCheck() )
		g_RecModCfg.m_u8SwitchMode = XMS_DRS_SWITCH_TADIRANT;
	else if ( ((CButton *)GetDlgItem ( IDC_RADIO_XMS_DRS_SWITCH_ERRICSION ))->GetCheck() )
		g_RecModCfg.m_u8SwitchMode = XMS_DRS_SWITCH_ERRICSION;
	else if ( ((CButton *)GetDlgItem ( IDC_RADIO_XMS_DRS_SWITCH_TOSHIBA ))->GetCheck() )
		g_RecModCfg.m_u8SwitchMode = XMS_DRS_SWITCH_TOSHIBA;

	if ( ((CButton *)GetDlgItem ( IDC_RADIO_XMS_Alaw_type ))->GetCheck() )
		g_RecModCfg.m_u8EncodeType = XMS_Alaw_type;
	else if ( ((CButton *)GetDlgItem ( IDC_RADIO_XMS_Ulaw_type ))->GetCheck() )
		g_RecModCfg.m_u8SwitchMode = XMS_Ulaw_type;

	if ( ((CButton *)GetDlgItem ( IDC_RADIO_RDMS_ENABLE_SigData ))->GetCheck() )
		g_RecModCfg.m_u8IsRecordSigData = 1;
	else 
		g_RecModCfg.m_u8IsRecordSigData = 0;
}

void CRecModModeSetDlg::SetConfig( ) 
{
	// TODO: Add your control notification handler code here

	if ( 1 == g_RecModCfg.m_u8Enable )
		((CButton *)GetDlgItem ( IDC_RADIO_RDMS_ENABLE ))->SetCheck(true);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_RDMS_Disable ))->SetCheck(true);

    if ( XMS_DRS_SWITCH_AVAYA == g_RecModCfg.m_u8SwitchMode )
		((CButton *)GetDlgItem ( IDC_RADIO_XMS_DRS_SWITCH_AVAYA ))->SetCheck(true);
	else if ( XMS_DRS_SWITCH_SIMENZ == g_RecModCfg.m_u8SwitchMode )
		((CButton *)GetDlgItem ( IDC_RADIO_XMS_DRS_SWITCH_SIMENZ ))->SetCheck(true);
	else if ( XMS_DRS_SWITCH_TADIRANT == g_RecModCfg.m_u8SwitchMode )
		((CButton *)GetDlgItem ( IDC_RADIO_XMS_DRS_SWITCH_TADIRANT ))->SetCheck(true);
	else if ( XMS_DRS_SWITCH_ERRICSION == g_RecModCfg.m_u8SwitchMode )
		((CButton *)GetDlgItem ( IDC_RADIO_XMS_DRS_SWITCH_ERRICSION ))->SetCheck(true);
	else if ( XMS_DRS_SWITCH_TOSHIBA == g_RecModCfg.m_u8SwitchMode )
		((CButton *)GetDlgItem ( IDC_RADIO_XMS_DRS_SWITCH_TOSHIBA ))->SetCheck(true);


	
    if ( XMS_Alaw_type == g_RecModCfg.m_u8EncodeType )
		((CButton *)GetDlgItem ( IDC_RADIO_XMS_Alaw_type ))->SetCheck(true);
	else if ( XMS_Ulaw_type == g_RecModCfg.m_u8EncodeType )
		((CButton *)GetDlgItem ( IDC_RADIO_XMS_Ulaw_type ))->SetCheck(true);

    if ( 1 == g_RecModCfg.m_u8EncodeType )
		((CButton *)GetDlgItem ( IDC_RADIO_RDMS_ENABLE_SigData ))->SetCheck(true);
	else if ( 0 == g_RecModCfg.m_u8EncodeType )
		((CButton *)GetDlgItem ( IDC_RADIO_RDMS_Disable_SigData ))->SetCheck(true);

}
