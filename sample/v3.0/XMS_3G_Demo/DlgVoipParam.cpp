// DlgVoipParam.cpp : implementation file
//

#include "stdafx.h"
#include "SP.h"
#include "DlgVoipParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVoipParam dialog


CDlgVoipParam::CDlgVoipParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVoipParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVoipParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgVoipParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVoipParam)
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVoipParam, CDialog)
	//{{AFX_MSG_MAP(CDlgVoipParam)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVoipParam message handlers
