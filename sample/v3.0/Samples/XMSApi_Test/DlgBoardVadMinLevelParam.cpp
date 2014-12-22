// DlgBoardVadMinLevelParam.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgBoardVadMinLevelParam.h"

#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBoardVadMinLevelParam dialog

extern CmdParam_VADMinDetectParam_t      g_VADMinLevelParam;

CDlgBoardVadMinLevelParam::CDlgBoardVadMinLevelParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBoardVadMinLevelParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBoardVadMinLevelParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgBoardVadMinLevelParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBoardVadMinLevelParam)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBoardVadMinLevelParam, CDialog)
	//{{AFX_MSG_MAP(CDlgBoardVadMinLevelParam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBoardVadMinLevelParam message handlers

void CDlgBoardVadMinLevelParam::OnOK() 
{
	char temp[100] = {0};
	
	// TODO: Add extra validation here
	GetDlgItem(IDC_EDIT_VAD_MIN_LEVEL)->GetWindowText(temp, 14);
	sscanf( temp, "%d", &g_VADMinLevelParam.m_s32VadLevel );

	GetDlgItem(IDC_EDIT_VAD_INTERVAL)->GetWindowText(temp, 14);
	sscanf( temp, "%d", &g_VADMinLevelParam.m_u16VadInterval );

	CDialog::OnOK();
}

BOOL CDlgBoardVadMinLevelParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char temp[100] = {0};

	if ( 0 == g_VADMinLevelParam.m_s32VadLevel )
		g_VADMinLevelParam.m_s32VadLevel = -54;

	sprintf(temp, "%d", g_VADMinLevelParam.m_s32VadLevel);
	GetDlgItem(IDC_EDIT_VAD_MIN_LEVEL)->SetWindowText(temp);

	if ( 0 == g_VADMinLevelParam.m_u16VadInterval )
		g_VADMinLevelParam.m_u16VadInterval = 200;

	sprintf(temp, "%d", g_VADMinLevelParam.m_u16VadInterval);
	GetDlgItem(IDC_EDIT_VAD_INTERVAL)->SetWindowText(temp);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
