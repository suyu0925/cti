// XMSApi_Control3GPPPlay.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "XMSApi_Control3GPPPlay.h"

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

extern	TYPE_MY_DEVICE_STRUCT	DevOpened[];

extern ControlPlay_t		g_ControlPlay;
extern Control3gppPlay_t	g_Control3GPPPlay;
/////////////////////////////////////////////////////////////////////////////
// CXMSApi_Control3GPPPlay dialog


CXMSApi_Control3GPPPlay::CXMSApi_Control3GPPPlay(CWnd* pParent /*=NULL*/)
	: CDialog(CXMSApi_Control3GPPPlay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXMSApi_Control3GPPPlay)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CXMSApi_Control3GPPPlay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXMSApi_Control3GPPPlay)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXMSApi_Control3GPPPlay, CDialog)
	//{{AFX_MSG_MAP(CXMSApi_Control3GPPPlay)
	ON_BN_CLICKED(IDC_BUTTON_Stop, OnBUTTONStop)
	ON_BN_CLICKED(IDC_BUTTON_Pause, OnBUTTONPause)
	ON_BN_CLICKED(IDC_BUTTON_Resume, OnBUTTONResume)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMSApi_Control3GPPPlay message handlers

BOOL CXMSApi_Control3GPPPlay::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	char	TmpStr[32];

	GetDlgItem ( IDC_EDIT_ControlPlay_DeviceID )->SetWindowText ( GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

	//g_ControlPlay . m_u16StepSize
	//sprintf ( TmpStr, "%d", g_ControlPlay.m_u16StepSize );
	//GetDlgItem ( IDC_EDIT_u16StepSize )->SetWindowText ( TmpStr );
	///////////////////////////////////////////////////////
	CComboBox * pCB;
	pCB = (CComboBox *)this->GetDlgItem(IDC_COMBO_MEDIA_TYPE);
    if (NULL == pCB)
	{
		ASSERT(0);
		return FALSE;
	}

	pCB->InsertString(0, "Audio");
	pCB->InsertString(1, "Video");
	pCB->InsertString(2, "A&V");
	pCB->SetItemData( 0, 0);
	pCB->SetItemData( 1, 1);
	pCB->SetItemData( 2, 4);
	pCB->SetTopIndex(2);
	pCB->SetCurSel(2);
	///////////////////////////////////////////////////////

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CXMSApi_Control3GPPPlay::OnBUTTONStop() 
{
	// TODO: Add your control notification handler code here
		int index, temp;
	// TODO: Add your control notification handler code here
	CComboBox *pCB;
	pCB = (CComboBox *)this->GetDlgItem(IDC_COMBO_MEDIA_TYPE);
	if (NULL == pCB)
	{
		ASSERT(0);
		return;
	}

	index = pCB->GetCurSel();
	temp = pCB->GetItemData(index);

	// TODO: Add your control notification handler code here
	g_Control3GPPPlay.m_u16ControlType = XMS_STOP_PLAY;
	g_Control3GPPPlay.m_u8MediaType = temp;

	DoFunc_Control3GPPPlay_Real( &g_Control3GPPPlay);
}

void CXMSApi_Control3GPPPlay::OnBUTTONPause() 
{
	// TODO: Add your control notification handler code here
		int index, temp;
	// TODO: Add your control notification handler code here
	CComboBox *pCB;
	pCB = (CComboBox *)this->GetDlgItem(IDC_COMBO_MEDIA_TYPE);
	if (NULL == pCB)
	{
		ASSERT(0);
		return;
	}

	index = pCB->GetCurSel();
	temp = pCB->GetItemData(index);

	// TODO: Add your control notification handler code here
	g_Control3GPPPlay.m_u16ControlType = XMS_PAUSE_PLAY;
	g_Control3GPPPlay.m_u8MediaType = temp;

	DoFunc_Control3GPPPlay_Real( &g_Control3GPPPlay);	
}

void CXMSApi_Control3GPPPlay::OnBUTTONResume() 
{
	// TODO: Add your control notification handler code here
		int index, temp;
	// TODO: Add your control notification handler code here
	CComboBox *pCB;
	pCB = (CComboBox *)this->GetDlgItem(IDC_COMBO_MEDIA_TYPE);
	if (NULL == pCB)
	{
		ASSERT(0);
		return;
	}

	index = pCB->GetCurSel();
	temp = pCB->GetItemData(index);

	// TODO: Add your control notification handler code here
	g_Control3GPPPlay.m_u16ControlType = XMS_RESUME_PLAY;
	g_Control3GPPPlay.m_u8MediaType = temp;

	DoFunc_Control3GPPPlay_Real( &g_Control3GPPPlay);	
}
