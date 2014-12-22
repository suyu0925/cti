// LedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "LedDlg.h"
#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern UserLedCtrl  g_LedCtrl;
extern DJ_U8        g_u8LedDspUnit;
/////////////////////////////////////////////////////////////////////////////
// CLedDlg dialog


CLedDlg::CLedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLedDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLedDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLedDlg, CDialog)
	//{{AFX_MSG_MAP(CLedDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLedDlg message handlers

void CLedDlg::OnButton1() 
{
	char szBuf[20]={0};

	memset(&g_LedCtrl,0,sizeof(g_LedCtrl));

	if(((CButton *)GetDlgItem ( IDC_RADIO_LEDTIME_ENABLE ))->GetCheck())
	{
		g_LedCtrl.m_u8LedTimeEnable = 1;

		GetDlgItem ( IDC_EDIT_LED_ONTIME )->GetWindowText ( szBuf, 20 );
		g_LedCtrl.m_u16OnTime = atoi(szBuf);
		GetDlgItem ( IDC_EDIT_LED_OFFTIME )->GetWindowText ( szBuf, 20 );
		g_LedCtrl.m_u16OffTime = atoi(szBuf);
	}
	if(((CButton *)GetDlgItem ( IDC_RADIO_WD_OUT_ENABLE ))->GetCheck())
	{
		g_LedCtrl.m_u8WatchDogOutEnbale = 1;

		GetDlgItem ( IDC_EDIT_WD_OUT_TIME )->GetWindowText ( szBuf, 20 );
		g_LedCtrl.m_u16WatchDogOutTime = atoi(szBuf);		
	}
	if(((CButton *)GetDlgItem ( IDC_RADIO_WD_TIME_ENABLE ))->GetCheck())
	{
		g_LedCtrl.m_u8WatchDogTimeEnable = 1;

		GetDlgItem ( IDC_EDIT_WD_ONTIME )->GetWindowText ( szBuf, 20 );
		g_LedCtrl.m_u16WatchDogOnTime = atoi(szBuf);
		GetDlgItem ( IDC_EDIT_WD_OFFTIME )->GetWindowText ( szBuf, 20 );
		g_LedCtrl.m_u16WatchDogOffTime = atoi(szBuf);
	}
	
	if(((CButton *)GetDlgItem ( IDC_CHECK_FEED_WD ))->GetCheck())
	{
		g_LedCtrl.m_u8FeedWatchDogEnable = 1;
	}


	GetDlgItem ( IDC_EDIT_UNITID )->GetWindowText ( szBuf, 20 );
	g_u8LedDspUnit =  atoi(szBuf);
	CDialog::OnOK();
}
