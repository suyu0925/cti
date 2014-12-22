// DlgBoardCommonParam.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgBoardCommonParam.h"

#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBoardCommonParam dialog

extern CmdParam_BoardCommonParam_t       g_BoardCommonParm;

CDlgBoardCommonParam::CDlgBoardCommonParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBoardCommonParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBoardCommonParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgBoardCommonParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBoardCommonParam)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBoardCommonParam, CDialog)
	//{{AFX_MSG_MAP(CDlgBoardCommonParam)
	ON_BN_CLICKED(IDC_RADIO_CNG_ENABLE, OnRadioCngEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBoardCommonParam message handlers

void CDlgBoardCommonParam::OnOK() 
{
	// TODO: Add extra validation here
	char str[50];

	if ( ((CButton*)GetDlgItem(IDC_RADIO_CNG_ENABLE))->GetCheck() )
	{
		g_BoardCommonParm.m_u8IsCNGEnable = 1;
		GetDlgItem(IDC_EDIT_CNG_GAIN_LEVEL)->GetWindowText(str, 50);

		sscanf(str, "%d", &g_BoardCommonParm.m_u16CNGGainLevel);
	}
	else
		g_BoardCommonParm.m_u8IsCNGEnable = 0;

	
	CDialog::OnOK();
}

BOOL CDlgBoardCommonParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char str[50];

	if ( 0 == g_BoardCommonParm.m_u16CNGGainLevel )
		g_BoardCommonParm.m_u16CNGGainLevel = 9;

	sprintf(str, "%d", g_BoardCommonParm.m_u16CNGGainLevel );
	GetDlgItem(IDC_EDIT_CNG_GAIN_LEVEL)->SetWindowText(str);

	// TODO: Add extra initialization here
	if ( 1 == g_BoardCommonParm.m_u8IsCNGEnable )
	{
		((CButton*)GetDlgItem(IDC_RADIO_CNG_ENABLE))->SetCheck(true);
		GetDlgItem(IDC_EDIT_CNG_GAIN_LEVEL)->EnableWindow( true );
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_CNG_ENABLE))->SetCheck(false);
		GetDlgItem(IDC_EDIT_CNG_GAIN_LEVEL)->EnableWindow( false );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgBoardCommonParam::DisplayControlX()
{
	if ( ((CButton*)GetDlgItem(IDC_RADIO_CNG_ENABLE))->GetCheck() )
	{
		g_BoardCommonParm.m_u8IsCNGEnable = 1;
		GetDlgItem(IDC_EDIT_CNG_GAIN_LEVEL)->EnableWindow( true );
		GetDlgItem(IDC_EDIT_CNG_GAIN_LEVEL)->SetFocus();
	}
	else
	{
		g_BoardCommonParm.m_u8IsCNGEnable = 0;
		GetDlgItem(IDC_EDIT_CNG_GAIN_LEVEL)->EnableWindow( false );
	}
	
}

void CDlgBoardCommonParam::OnRadioCngEnable() 
{
	// TODO: Add your control notification handler code here
	DisplayControlX();
	
}
