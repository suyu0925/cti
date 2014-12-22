// DlgFaxBpsParam.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgFaxBpsParam.h"

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"

#include "XMSApi_Test_Func.h"
#include "XMSApi_Test_String.h"
#include "XMSApi_Test_Event.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFaxBpsParam dialog
extern Acs_SetFaxBps                     g_FaxBpsParam;


CDlgFaxBpsParam::CDlgFaxBpsParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFaxBpsParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFaxBpsParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgFaxBpsParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFaxBpsParam)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFaxBpsParam, CDialog)
	//{{AFX_MSG_MAP(CDlgFaxBpsParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFaxBpsParam message handlers

void CDlgFaxBpsParam::OnOK() 
{
	// TODO: Add extra validation here
	// TODO: Add extra initialization here
	if ( 1 == ((CButton*)(GetDlgItem(IDC_RADIO_XMS_BPS_2400)))->GetCheck() )
		g_FaxBpsParam.m_u8BPS = XMS_BPS_2400;
	else if ( 1 == ((CButton*)(GetDlgItem(IDC_RADIO_XMS_BPS_4800)))->GetCheck() )
		g_FaxBpsParam.m_u8BPS = XMS_BPS_4800;
	else if ( 1 == ((CButton*)(GetDlgItem(IDC_RADIO_XMS_BPS_7200)))->GetCheck() )
		g_FaxBpsParam.m_u8BPS = XMS_BPS_7200;
	else if ( 1 == ((CButton*)(GetDlgItem(IDC_RADIO_XMS_BPS_9600)))->GetCheck() )
		g_FaxBpsParam.m_u8BPS = XMS_BPS_9600;
	else if ( 1 == ((CButton*)(GetDlgItem(IDC_RADIO_XMS_BPS_12000)))->GetCheck() )
		g_FaxBpsParam.m_u8BPS = XMS_BPS_12000;
	else if ( 1 == ((CButton*)(GetDlgItem(IDC_RADIO_XMS_BPS_14400)))->GetCheck() )
		g_FaxBpsParam.m_u8BPS = XMS_BPS_14400;

	CDialog::OnOK();
}

BOOL CDlgFaxBpsParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if ( XMS_BPS_2400 == g_FaxBpsParam.m_u8BPS )
	{
		((CButton*)(GetDlgItem(IDC_RADIO_XMS_BPS_2400)))->SetCheck(true);
	}
	else if ( XMS_BPS_4800 == g_FaxBpsParam.m_u8BPS  )
	{
		((CButton*)(GetDlgItem(IDC_RADIO_XMS_BPS_4800)))->SetCheck(true);
	}
	else if ( XMS_BPS_7200 == g_FaxBpsParam.m_u8BPS  )
	{
		((CButton*)(GetDlgItem(IDC_RADIO_XMS_BPS_7200)))->SetCheck(true);
	}
	else if ( XMS_BPS_9600 == g_FaxBpsParam.m_u8BPS  )
	{
		((CButton*)(GetDlgItem(IDC_RADIO_XMS_BPS_9600)))->SetCheck(true);
	}
	else if ( XMS_BPS_12000 == g_FaxBpsParam.m_u8BPS  )
	{
		((CButton*)(GetDlgItem(IDC_RADIO_XMS_BPS_12000)))->SetCheck(true);
	}
	else if ( XMS_BPS_14400 == g_FaxBpsParam.m_u8BPS  )
	{
		((CButton*)(GetDlgItem(IDC_RADIO_XMS_BPS_14400)))->SetCheck(true);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
