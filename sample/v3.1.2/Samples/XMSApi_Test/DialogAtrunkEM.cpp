// DialogAtrunkEM.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DialogAtrunkEM.h"

#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern Acs_AnalogEM_CMD          g_ATrunkEM;

/////////////////////////////////////////////////////////////////////////////
// DialogAtrunkEM dialog


DialogAtrunkEM::DialogAtrunkEM(CWnd* pParent /*=NULL*/)
	: CDialog(DialogAtrunkEM::IDD, pParent)
{
	//{{AFX_DATA_INIT(DialogAtrunkEM)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DialogAtrunkEM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DialogAtrunkEM)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DialogAtrunkEM, CDialog)
	//{{AFX_MSG_MAP(DialogAtrunkEM)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DialogAtrunkEM message handlers

BOOL DialogAtrunkEM::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//((CButton *)GetDlgItem ( IDC_CHECK_AT_CHANNEL_ENABLED ))->SetCheck(g_ATrunkFlash.m_u8Channel_Enable); 
	((CButton *)GetDlgItem ( IDC_RADIO_ATEM_ENABLE ))->SetCheck(1); 

	GetDlgItem ( IDC_EDIT_ATEM_TYPE )->SetWindowText ( "0" );
	GetDlgItem ( IDC_EDIT_ATEM_TXSTATE )->SetWindowText ( "1" );
	GetDlgItem ( IDC_EDIT_ATEM_RXSTATE )->SetWindowText ( "0" );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DialogAtrunkEM::OnOK() 
{
	// TODO: Add extra validation here
		// TODO: Add extra validation here
	char TmpStr[20];
	int iTmpVal;

	if (((CButton *)GetDlgItem ( IDC_RADIO_ATEM_ENABLE ))->GetCheck())
	{
		g_ATrunkEM.m_u8Channel_Enable = 1;
	}
	else
		g_ATrunkEM.m_u8Channel_Enable = 0;

	GetDlgItem ( IDC_EDIT_ATEM_TYPE )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_ATrunkEM.m_u8Type = iTmpVal;

	GetDlgItem ( IDC_EDIT_ATEM_TXSTATE )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_ATrunkEM.m_u8Tx_State = iTmpVal;
	
	GetDlgItem ( IDC_EDIT_ATEM_RXSTATE )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_ATrunkEM.m_u8Rx_State = iTmpVal;

	CDialog::OnOK();
}
