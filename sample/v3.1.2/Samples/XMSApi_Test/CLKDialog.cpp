// CLKDialog.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "CLKDialog.h"
#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int g_NetRef;

/////////////////////////////////////////////////////////////////////////////
// CCLKDialog dialog
extern CmdParamData_CTCLKNET_t           g_CTCLK;


CCLKDialog::CCLKDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CCLKDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCLKDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCLKDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCLKDialog)
	DDX_Control(pDX, IDC_NETCOMBO, m_NetComBo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCLKDialog, CDialog)
	//{{AFX_MSG_MAP(CCLKDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCLKDialog message handlers

void CCLKDialog::OnOK() 
{
	// TODO: Add extra validation here
	g_NetRef = m_NetComBo.GetCurSel()+8;
	g_CTCLK.m_u8NetRef1 = g_NetRef;

	if ( ((CButton*)GetDlgItem(IDC_RADIO_CLK_TYPE_MASTER))->GetCheck() )
	{
		g_CTCLK.m_u8SysClockType = XMS_BOARD_EXT_CLOCK_TYPE_MASTER;
	}
	else
	{
		g_CTCLK.m_u8SysClockType = XMS_BOARD_EXT_CLOCK_TYPE_SLAVE;
	}


	CDialog::OnOK();
}

BOOL CCLKDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_NetComBo.AddString("L_NET0");
	m_NetComBo.AddString("L_NET1");
	m_NetComBo.AddString("L_NET2");
	m_NetComBo.AddString("L_NET3");

	m_NetComBo.SetCurSel(g_CTCLK.m_u8NetRef1-8);

	if ( XMS_BOARD_EXT_CLOCK_TYPE_MASTER == g_CTCLK.m_u8SysClockType )
	{
		((CButton*)GetDlgItem(IDC_RADIO_CLK_TYPE_MASTER))->SetCheck(true);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_CLK_TYPE_SLAVE))->SetCheck(true);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
