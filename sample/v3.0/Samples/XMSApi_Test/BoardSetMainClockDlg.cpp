// BoardSetMainClockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "BoardSetMainClockDlg.h"

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

Acs_BoardPrivateExt_Data     g_stBoardPrivateExt_Data = {0};

/////////////////////////////////////////////////////////////////////////////
// CBoardSetMainClockDlg dialog


CBoardSetMainClockDlg::CBoardSetMainClockDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBoardSetMainClockDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBoardSetMainClockDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CBoardSetMainClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBoardSetMainClockDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBoardSetMainClockDlg, CDialog)
	//{{AFX_MSG_MAP(CBoardSetMainClockDlg)
	ON_BN_CLICKED(IDC_RADIO_XMS_BOARD_EXT_TYPE_NULL, OnRadioXmsBoardExtTypeNull)
	ON_BN_CLICKED(IDC_RADIO_XMS_BOARD_EXT_TYPE_CLOCK, OnRadioXmsBoardExtTypeClock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBoardSetMainClockDlg message handlers

void CBoardSetMainClockDlg::OnOK() 
{
	// TODO: Add extra validation here
	memset(&g_stBoardPrivateExt_Data,0,sizeof(g_stBoardPrivateExt_Data));
	if ( ((CButton*)GetDlgItem(IDC_RADIO_XMS_BOARD_EXT_TYPE_NULL))->GetCheck() )
	{
		g_stBoardPrivateExt_Data.m_u32ExtType = XMS_BOARD_EXT_TYPE_NULL;
	}
	else
	{
		g_stBoardPrivateExt_Data.m_u32ExtType = XMS_BOARD_EXT_TYPE_CLOCK;
	}

	if ( g_stBoardPrivateExt_Data.m_u32ExtType == XMS_BOARD_EXT_TYPE_CLOCK )
	{
		if ( ((CButton*)GetDlgItem(IDC_RADIO_XMS_BOARD_EXT_CLOCK_SET))->GetCheck() )
		{
			g_stBoardPrivateExt_Data.m_u8SysClockMode = XMS_BOARD_CLOCK_MODE_AUTO;
		}
		else
		{
			g_stBoardPrivateExt_Data.m_u8SysClockMode = XMS_BOARD_CLOCK_MODE_MANUAL;
		}
	}


	if ( ((CButton*)GetDlgItem(IDC_RADIO_XMS_BOARD_CLK_MASTER))->GetCheck() )
		g_stBoardPrivateExt_Data.m_u8SysClockType = XMS_BOARD_EXT_CLOCK_TYPE_MASTER;
	else
		g_stBoardPrivateExt_Data.m_u8SysClockType = XMS_BOARD_EXT_CLOCK_TYPE_SLAVE;


	CDialog::OnOK();
}

void CBoardSetMainClockDlg::OnRadioXmsBoardExtTypeNull() 
{
	// TODO: Add your control notification handler code here
	g_stBoardPrivateExt_Data.m_u32ExtType = XMS_BOARD_EXT_TYPE_NULL;
	EnableControlFlag();
}

void CBoardSetMainClockDlg::OnRadioXmsBoardExtTypeClock() 
{
	// TODO: Add your control notification handler code here
	g_stBoardPrivateExt_Data.m_u32ExtType = XMS_BOARD_EXT_TYPE_CLOCK;
	EnableControlFlag();	
}

BOOL CBoardSetMainClockDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	EnableControlFlag();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBoardSetMainClockDlg::EnableControlFlag()
{
	// TODO: Add extra initialization here
	if ( XMS_BOARD_EXT_TYPE_CLOCK == g_stBoardPrivateExt_Data.m_u32ExtType )
	{
		((CButton*)GetDlgItem(IDC_RADIO_XMS_BOARD_EXT_TYPE_CLOCK))->SetCheck(true );
		((CButton*)GetDlgItem(IDC_RADIO_XMS_BOARD_EXT_CLOCK_NO_SET))->EnableWindow(true);
		((CButton*)GetDlgItem(IDC_RADIO_XMS_BOARD_EXT_CLOCK_SET))->EnableWindow(true);

		if ( XMS_BOARD_CLOCK_MODE_MANUAL == g_stBoardPrivateExt_Data.m_u8SysClockMode )
		{
			((CButton*)GetDlgItem(IDC_RADIO_XMS_BOARD_EXT_CLOCK_NO_SET))->SetCheck( true);
		}
		else
		{
			((CButton*)GetDlgItem(IDC_RADIO_XMS_BOARD_EXT_CLOCK_SET))->SetCheck(true );
		}
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_XMS_BOARD_EXT_TYPE_NULL))->SetCheck(true );
		((CButton*)GetDlgItem(IDC_RADIO_XMS_BOARD_EXT_CLOCK_NO_SET))->EnableWindow(false);
		((CButton*)GetDlgItem(IDC_RADIO_XMS_BOARD_EXT_CLOCK_SET))->EnableWindow(false);

		if ( XMS_BOARD_CLOCK_MODE_MANUAL == g_stBoardPrivateExt_Data.m_u8SysClockMode )
		{
			((CButton*)GetDlgItem(IDC_RADIO_XMS_BOARD_EXT_CLOCK_NO_SET))->SetCheck(true );
		}
		else
		{
			((CButton*)GetDlgItem(IDC_RADIO_XMS_BOARD_EXT_CLOCK_SET))->SetCheck(true );
		}
	}

	if ( XMS_BOARD_EXT_CLOCK_TYPE_MASTER == g_stBoardPrivateExt_Data.m_u8SysClockType )
	{
		((CButton*)GetDlgItem(IDC_RADIO_XMS_BOARD_CLK_MASTER))->SetCheck( true);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_XMS_BOARD_CLK_SLAVE))->SetCheck(true );
	}

}
