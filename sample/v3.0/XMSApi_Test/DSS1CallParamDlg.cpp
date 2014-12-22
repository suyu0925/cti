// DSS1CallParamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DSS1CallParamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSS1CallParamDlg dialog


CDSS1CallParamDlg::CDSS1CallParamDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDSS1CallParamDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDSS1CallParamDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDSS1CallParamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDSS1CallParamDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDSS1CallParamDlg, CDialog)
	//{{AFX_MSG_MAP(CDSS1CallParamDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSS1CallParamDlg message handlers
