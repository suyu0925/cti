// CtxRegDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "CtxRegDlg.h"

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"
#include "XMSApi_Test_Event.h"
#include "XMSApi_Test_String.h"
#include "XMSApi_Test_Sub.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern ACSHandle_t		        g_acsHandle;
extern char                     g_s8OwnAppName[];
extern char                     g_s8OthersAppName[];
/////////////////////////////////////////////////////////////////////////////
// CCtxRegDlg dialog


CCtxRegDlg::CCtxRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCtxRegDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCtxRegDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCtxRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCtxRegDlg)
	DDX_Control(pDX, IDC_EDIT_REGNAME, m_RegName);
	DDX_Control(pDX, IDC_COMBO_REGTYPE, m_RegType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCtxRegDlg, CDialog)
	//{{AFX_MSG_MAP(CCtxRegDlg)
	ON_BN_CLICKED(IDC_Excute, OnExcute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCtxRegDlg message handlers

void CCtxRegDlg::OnOK() 
{
	CDialog::OnOK();
}

BOOL CCtxRegDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CComboBox * pCB;
	pCB = (CComboBox *)this->GetDlgItem(IDC_COMBO_REGTYPE);
    if (NULL == pCB)
	{
		ASSERT(0);
		return FALSE;
	}

    GetDlgItem ( IDC_EDIT_REGNAME )->SetWindowText ( g_s8OwnAppName );

	pCB->InsertString(0, "CTX Register");
	pCB->InsertString(1, "CTX UnRegister");

	pCB->SetItemData( 0, XMS_CTX_REG );
	pCB->SetItemData( 1, XMS_CTX_UNREG);

	pCB->SetTopIndex(0);
	pCB->SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CCtxRegDlg::OnExcute() 
{
    char szBuf[100] = {0};
	char MsgStr[100]={0};
	int nRegType;
	int r = 0;

	nRegType = m_RegType.GetCurSel();	
	nRegType = nRegType == 0 ? XMS_CTX_REG:XMS_CTX_UNREG;

	GetDlgItem ( IDC_EDIT_REGNAME )->GetWindowText ( szBuf, 100 );
		
	if ( 16 < strlen(szBuf) )
	{
		sprintf ( MsgStr, "Invalid User Name(%s) ( %d)", szBuf,nRegType  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr);
		return;
	}

	r = XMS_ctxRegister(g_acsHandle, szBuf,nRegType,NULL);
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctxRegister() FAIL! (%s %d)", 
			r, szBuf,nRegType  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr);
	}
	else
	{
		sprintf ( MsgStr, "X(%d) XMS_ctxRegister() success! (%s %d)", 
			r, szBuf,nRegType  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr);
	}	
}
