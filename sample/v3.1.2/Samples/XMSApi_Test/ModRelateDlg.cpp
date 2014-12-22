// ModRelateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "ModRelateDlg.h"
#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern DJ_U8 g_u8ModuleType;
extern DJ_U8 g_u8ModuleUnitID;


/////////////////////////////////////////////////////////////////////////////
// ModRelateDlg dialog


ModRelateDlg::ModRelateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ModRelateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ModRelateDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ModRelateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ModRelateDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ModRelateDlg, CDialog)
	//{{AFX_MSG_MAP(ModRelateDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ModRelateDlg message handlers

void ModRelateDlg::OnOK() 
{
	// TODO: Add extra validation here
	DJ_S8 s8Temp[256];

	((CButton*)GetDlgItem(IDC_EDIT_GET_RELATE_MT))->GetWindowText(s8Temp, 20);
	sscanf(s8Temp, "%d", &g_u8ModuleType );

	((CButton*)GetDlgItem(IDC_EDIT_GET_RELATE_UID))->GetWindowText(s8Temp, 20);
	sscanf(s8Temp, "%d", &g_u8ModuleUnitID );

	CDialog::OnOK();
}

BOOL ModRelateDlg::OnInitDialog() 
{
	DJ_S8 s8Temp[256];

	CDialog::OnInitDialog();
	
	sprintf(s8Temp, "%d", g_u8ModuleType );
	((CButton*)GetDlgItem(IDC_EDIT_GET_RELATE_MT))->SetWindowText(s8Temp);

	sprintf(s8Temp, "%d", g_u8ModuleUnitID );
	((CButton*)GetDlgItem(IDC_EDIT_GET_RELATE_UID))->SetWindowText(s8Temp);
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
