// XMSApi_3GPPControlRecord.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "XMSApi_3GPPControlRecord.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"

#include "XMSApi_Test_Func.h"
#include "XMSApi_Test_String.h"
#include "XMSApi_Test_Event.h"

extern	int		iOpenedIndex1;

extern	TYPE_MY_DEVICE_STRUCT	DevOpened[MAX_DEVICE_ALLOW_OPEN];
extern Control3gppRecord_t		g_Control3GPPRecord;

/////////////////////////////////////////////////////////////////////////////
// CXMSApi_3GPPControlRecord dialog


CXMSApi_3GPPControlRecord::CXMSApi_3GPPControlRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CXMSApi_3GPPControlRecord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXMSApi_3GPPControlRecord)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CXMSApi_3GPPControlRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXMSApi_3GPPControlRecord)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXMSApi_3GPPControlRecord, CDialog)
	//{{AFX_MSG_MAP(CXMSApi_3GPPControlRecord)
	ON_BN_CLICKED(IDC_BUTTON_3GPP_Stop, OnBUTTON3GPPStop)
	ON_BN_CLICKED(IDC_BUTTON_3GPP_Pause, OnBUTTON3GPPPause)
	ON_BN_CLICKED(IDC_BUTTON_3GPP_Resume, OnBUTTON3GPPResume)
	ON_BN_CLICKED(IDC_BUTTON_3GPP_StepBack, OnBUTTON3GPPStepBack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMSApi_3GPPControlRecord message handlers

void CXMSApi_3GPPControlRecord::OnBUTTON3GPPStop() 
{
	// TODO: Add your control notification handler code here
	
	g_Control3GPPRecord.m_u32ControlType = XMS_STOP_RECORD;
	Get_u32StepSize ();

	DoFunc_Control3GPPRecord_Real( &g_Control3GPPRecord);	// TODO: Add your control notification handler code here
	
}

void CXMSApi_3GPPControlRecord::OnBUTTON3GPPPause() 
{
	// TODO: Add your control notification handler code here
	g_Control3GPPRecord.m_u32ControlType = XMS_PAUSE_RECORD;
	Get_u32StepSize ();

	DoFunc_Control3GPPRecord_Real( &g_Control3GPPRecord);	
}

void CXMSApi_3GPPControlRecord::OnBUTTON3GPPResume() 
{
	// TODO: Add your control notification handler code here
	g_Control3GPPRecord.m_u32ControlType = XMS_RESUME_RECORD;
	Get_u32StepSize ();

	DoFunc_Control3GPPRecord_Real( &g_Control3GPPRecord);	
}

void CXMSApi_3GPPControlRecord::OnBUTTON3GPPStepBack() 
{
	// TODO: Add your control notification handler code here
	g_Control3GPPRecord.m_u32ControlType = XMS_STEP_BACKWARD_RECORD;
	Get_u32StepSize ();

	DoFunc_Control3GPPRecord_Real( &g_Control3GPPRecord);	
}

void CXMSApi_3GPPControlRecord::OnOK() 
{
	// TODO: Add extra validation here
	
	Get_u32StepSize ();

	CDialog::OnOK();
}

BOOL CXMSApi_3GPPControlRecord::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char	TmpStr[32];

	GetDlgItem ( IDC_EDIT_ControlRecord_3GPP_DeviceID )->SetWindowText ( GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

	//g_ControlRecord . m_u32StepSize
	sprintf ( TmpStr, "%d", g_Control3GPPRecord.m_u32StepTime );
	GetDlgItem ( IDC_EDIT_3GPP_u32StepSize )->SetWindowText ( TmpStr );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CXMSApi_3GPPControlRecord::Get_u32StepSize()
{
	char	TmpStr[32];
	int		iTmpVal;

	//g_ControlRecord . m_u32StepSize
	GetDlgItem ( IDC_EDIT_3GPP_u32StepSize )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_Control3GPPRecord.m_u32StepTime = iTmpVal;
}
