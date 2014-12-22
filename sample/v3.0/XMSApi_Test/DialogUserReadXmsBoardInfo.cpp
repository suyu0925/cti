// DialogUserReadXmsBoardInfo.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DialogUserReadXmsBoardInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogUserReadXmsBoardInfo dialog


CDialogUserReadXmsBoardInfo::CDialogUserReadXmsBoardInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogUserReadXmsBoardInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogUserReadXmsBoardInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogUserReadXmsBoardInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogUserReadXmsBoardInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogUserReadXmsBoardInfo, CDialog)
	//{{AFX_MSG_MAP(CDialogUserReadXmsBoardInfo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogUserReadXmsBoardInfo message handlers
