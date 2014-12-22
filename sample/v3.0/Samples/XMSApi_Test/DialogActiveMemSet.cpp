// DialogActiveMemSet.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DialogActiveMemSet.h"

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogActiveMemSet dialog
//extern CmdParam_ActiveMemDetectParam_t   g_ConfActiveMemParam;


CDialogActiveMemSet::CDialogActiveMemSet(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogActiveMemSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogActiveMemSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogActiveMemSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogActiveMemSet)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogActiveMemSet, CDialog)
	//{{AFX_MSG_MAP(CDialogActiveMemSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogActiveMemSet message handlers

void CDialogActiveMemSet::OnOK() 
{
	// TODO: Add extra validation here
	char str[100] = {0};
	int iTemp = 0;

	GetDlgItem(IDC_EDIT_ACTIVE_MEM_VAD_LEVEL)->GetWindowText(str, 100);
	sscanf( str, "%d", &iTemp); 
//	g_ConfActiveMemParam.m_s32VadLevel = iTemp;

	CDialog::OnOK();
}

BOOL CDialogActiveMemSet::OnInitDialog() 
{
	CDialog::OnInitDialog();

	char str[100] = {0};
	
//	if ( 0 == g_ConfActiveMemParam.m_s32VadLevel )
//		g_ConfActiveMemParam.m_s32VadLevel = -48;

	// TODO: Add extra initialization here
//	sprintf(str, "%d", g_ConfActiveMemParam.m_s32VadLevel);
	GetDlgItem(IDC_EDIT_ACTIVE_MEM_VAD_LEVEL)->SetWindowText(str);

	GetDlgItem(IDOK)->EnableWindow(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
