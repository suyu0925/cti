// DialogSVDSet.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DialogSVDSet.h"

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CmdParam_SilenceDetectParam_t  g_SVDCmd;

/////////////////////////////////////////////////////////////////////////////
// CDialogSVDSet dialog


CDialogSVDSet::CDialogSVDSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSVDSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogSVDSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogSVDSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSVDSet)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogSVDSet, CDialog)
	//{{AFX_MSG_MAP(CDialogSVDSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogSVDSet message handlers

BOOL CDialogSVDSet::OnInitDialog() 
{
	char temp[256] = {0};

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if ( 0 == g_SVDCmd.m_s32SilenceLevel )
	{
		memset(&g_SVDCmd, 0, sizeof(g_SVDCmd) );

		g_SVDCmd.m_s32SilenceLevel = -42;
		g_SVDCmd.m_s32SilenceTimer = 3000;
	}

	sprintf(temp, "%d", g_SVDCmd.m_s32SilenceLevel );
	GetDlgItem ( IDC_EDIT_LEVEL )->SetWindowText(temp);

	sprintf(temp, "%d", g_SVDCmd.m_s32SilenceTimer );
	GetDlgItem ( IDC_EDIT_TIME_OUT )->SetWindowText(temp);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogSVDSet::OnOK() 
{
	char temp[256];

	// TODO: Add extra validation here
	GetDlgItem ( IDC_EDIT_LEVEL )->GetWindowText ( temp, 256 );
	g_SVDCmd.m_s32SilenceLevel = atoi(temp);			

	GetDlgItem ( IDC_EDIT_TIME_OUT )->GetWindowText ( temp, 256 );
	g_SVDCmd.m_s32SilenceTimer = atoi(temp);			

	CDialog::OnOK();
}
