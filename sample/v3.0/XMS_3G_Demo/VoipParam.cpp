// VoipParam.cpp : implementation file
//

#include "stdafx.h"
#include "SP.h"
#include "VoipParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VoipParam dialog


VoipParam::VoipParam(CWnd* pParent /*=NULL*/)
	: CDialog(VoipParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(VoipParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void VoipParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VoipParam)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VoipParam, CDialog)
	//{{AFX_MSG_MAP(VoipParam)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VoipParam message handlers
