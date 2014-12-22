// DlgFaxMultiFileParam.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgFaxMultiFileParam.h"

#include "DJAcsDataDef.h"
#include "XMSApi_Test_Sub.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern Acs_TransAddFile g_FaxMultiFileParam;
/////////////////////////////////////////////////////////////////////////////
// CDlgFaxMultiFileParam dialog


CDlgFaxMultiFileParam::CDlgFaxMultiFileParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFaxMultiFileParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFaxMultiFileParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgFaxMultiFileParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFaxMultiFileParam)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFaxMultiFileParam, CDialog)
	//{{AFX_MSG_MAP(CDlgFaxMultiFileParam)
	ON_BN_CLICKED(IDC_BUTTON_FIND_FILE_PATH, OnButtonFindFilePath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFaxMultiFileParam message handlers

void CDlgFaxMultiFileParam::OnOK() 
{
	// TODO: Add extra validation here
		// TODO: Add extra initialization here
	if ( 1 == ((CButton*)(GetDlgItem(IDC_RADIO_TYPE_CLEAR)))->GetCheck() )
		g_FaxMultiFileParam.m_u32Op = XMS_FAX_M_FILE_TYPE_CLEAR;
	else
		g_FaxMultiFileParam.m_u32Op = XMS_FAX_M_FILE_TYPE_ADD;

	((CEdit*)GetDlgItem(IDC_EDIT_FAX_FILE_NAME))->GetWindowText(g_FaxMultiFileParam.m_strFileName, 256);

	CDialog::OnOK();
}

void CDlgFaxMultiFileParam::OnButtonFindFilePath() 
{
	char TmpStr[MAX_FILE_NAME_LEN];

	// TODO: Add your control notification handler code here
	GetDlgItem ( IDC_EDIT_FAX_FILE_NAME )->GetWindowText ( TmpStr, MAX_FILE_NAME_LEN-1 );

	My_SelectFile ( TmpStr );

	GetDlgItem ( IDC_EDIT_FAX_FILE_NAME )->SetWindowText ( TmpStr );
}

BOOL CDlgFaxMultiFileParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if ( g_FaxMultiFileParam.m_u32Op == XMS_FAX_M_FILE_TYPE_CLEAR )
		((CButton*)(GetDlgItem(IDC_RADIO_TYPE_CLEAR)))->SetCheck(true);
	else
		((CButton*)(GetDlgItem(IDC_RADIO_TYPE_ADD)))->SetCheck(true);
	
	((CEdit*)GetDlgItem(IDC_EDIT_FAX_FILE_NAME))->SetWindowText(g_FaxMultiFileParam.m_strFileName);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
