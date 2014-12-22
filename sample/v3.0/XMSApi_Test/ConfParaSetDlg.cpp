// ConfParaSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "ConfParaSetDlg.h"

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"

#include "XMSApi_Test_Sub.h"
#include "XMSApi_Test_Event.h"
#include "XMSApi_Test_String.h"
#include "XMSApi_Test_Func.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CmdParamConf_VadInterval_t g_stParamConf;

/////////////////////////////////////////////////////////////////////////////
// CConfParaSetDlg dialog


CConfParaSetDlg::CConfParaSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfParaSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfParaSetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfParaSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfParaSetDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfParaSetDlg, CDialog)
	//{{AFX_MSG_MAP(CConfParaSetDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfParaSetDlg message handlers

void CConfParaSetDlg::OnOK() 
{
	char str[100] = {0};

	// TODO: Add extra validation here
	((CEdit*)GetDlgItem(IDC_EDIT_VAD_CHECK_INTERVAL))->GetWindowText(str, 100);
	sscanf( str, "%d", &g_stParamConf.m_u16VadCheckInterval);
	
	if ( ((CButton*)GetDlgItem(IDC_RADIO_RPT_CONF_MEM_ENABLE))->GetCheck() )
	{
		g_stParamConf.m_u8RptConfMemEnable = 1;
	}
	else if ( ((CButton*)GetDlgItem(IDC_RADIO_RPT_CONF_MEM_DISABLE))->GetCheck() )
	{
		g_stParamConf.m_u8RptConfMemEnable = 0;
	}

	CDialog::OnOK();
}

BOOL CConfParaSetDlg::OnInitDialog() 
{
	char str[100] = {0};

	CDialog::OnInitDialog();
	
	if ( 30 > g_stParamConf.m_u16VadCheckInterval 
	  || 65535 < g_stParamConf.m_u16VadCheckInterval )
		g_stParamConf.m_u16VadCheckInterval = 500;

	// TODO: Add extra initialization here
	sprintf(str, "%d", g_stParamConf.m_u16VadCheckInterval);
	((CEdit*)GetDlgItem(IDC_EDIT_VAD_CHECK_INTERVAL))->SetWindowText(str);

	if ( 1 == g_stParamConf.m_u8RptConfMemEnable )
	{
		((CButton*)GetDlgItem(IDC_RADIO_RPT_CONF_MEM_ENABLE))->SetCheck(true);
		((CButton*)GetDlgItem(IDC_RADIO_RPT_CONF_MEM_DISABLE))->SetCheck(false);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_RPT_CONF_MEM_ENABLE))->SetCheck(false);
		((CButton*)GetDlgItem(IDC_RADIO_RPT_CONF_MEM_DISABLE))->SetCheck(true);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
