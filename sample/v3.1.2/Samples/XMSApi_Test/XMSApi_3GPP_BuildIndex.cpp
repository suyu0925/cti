// XMSApi_3GPP_BuildIndex.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "XMSApi_3GPP_BuildIndex.h"

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"

#include "XMSApi_Test_Sub.h"
#include "XMSApi_Test_String.h"
#include "XMSApi_Test_Event.h"
#include "XMSApi_Test_Func.h"

extern	int		iOpenedIndex1;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	TYPE_MY_DEVICE_STRUCT	DevOpened[];

extern Play3gppProperty_t   g_Build3gppIndexProperty;

/////////////////////////////////////////////////////////////////////////////
// CXMSApi_3GPP_BuildIndex dialog


CXMSApi_3GPP_BuildIndex::CXMSApi_3GPP_BuildIndex(CWnd* pParent /*=NULL*/)
	: CDialog(CXMSApi_3GPP_BuildIndex::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXMSApi_3GPP_BuildIndex)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CXMSApi_3GPP_BuildIndex::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXMSApi_3GPP_BuildIndex)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXMSApi_3GPP_BuildIndex, CDialog)
	//{{AFX_MSG_MAP(CXMSApi_3GPP_BuildIndex)
	ON_BN_CLICKED(IDC_BUTTON_SelectBuildIndex, OnBUTTONSelectBuildIndex)
	ON_BN_CLICKED(IDC_BUTTON_SelectBuildIndex_Video, OnBUTTONSelectBuildIndexVideo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMSApi_3GPP_BuildIndex message handlers

BOOL CXMSApi_3GPP_BuildIndex::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	GetDlgItem ( IDC_EDIT_BuildIndex_DeviceID )->SetWindowText ( GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
	
	/*audio*/
	if ( g_Build3gppIndexProperty.m_u16PlayType == XMS_BUILD_INDEX_FILE )
		((CButton *)GetDlgItem ( IDC_RADIO_INDEX_FILE ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_INDEX_RAM ))->SetCheck(1);

	GetDlgItem ( IDC_EDIT_BuildPlayIndex )->SetWindowText ( g_Build3gppIndexProperty.m_s8PlayContent );

	/*video*/	
	if ( g_Build3gppIndexProperty.m_u16VideoPlayType == XMS_BUILD_INDEX_FILE )
		((CButton *)GetDlgItem ( IDC_RADIO_INDEX_FILE_VIDEO ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_INDEX_RAM_VIDEO ))->SetCheck(1);

	GetDlgItem ( IDC_EDIT_BuildPlayIndex_Video )->SetWindowText ( g_Build3gppIndexProperty.m_s8VideoPlayContent );

	CComboBox * pCB;
	pCB = (CComboBox *)this->GetDlgItem(IDC_COMBO_BuildIndex_MediaType);
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

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CXMSApi_3GPP_BuildIndex::OnBUTTONSelectBuildIndex() 
{
	// TODO: Add your control notification handler code here
	char	TmpStr[256];

	GetDlgItem ( IDC_EDIT_BuildPlayIndex )->GetWindowText ( TmpStr, MAX_FILE_NAME_LEN-1 );

	My_SelectFile ( TmpStr );

	GetDlgItem ( IDC_EDIT_BuildPlayIndex )->SetWindowText ( TmpStr );
	
}

void CXMSApi_3GPP_BuildIndex::OnBUTTONSelectBuildIndexVideo() 
{
	// TODO: Add your control notification handler code here
	char	TmpStr[256];

	GetDlgItem ( IDC_EDIT_BuildPlayIndex_Video )->GetWindowText ( TmpStr, MAX_FILE_NAME_LEN-1 );

	My_SelectFile ( TmpStr );

	GetDlgItem ( IDC_EDIT_BuildPlayIndex_Video )->SetWindowText ( TmpStr );

}

void CXMSApi_3GPP_BuildIndex::OnOK() 
{
	// TODO: Add extra validation here
	GetNowSetVal ();

	DoFunc_Build3GPPPlayIndex_Real ();

//	CDialog::OnOK();
}

void CXMSApi_3GPP_BuildIndex::GetNowSetVal()
{
	//audio
	if( ((CButton *)GetDlgItem ( IDC_RADIO_INDEX_FILE ))->GetCheck() )
		g_Build3gppIndexProperty.m_u16PlayType = XMS_BUILD_INDEX_FILE; 
	else
		g_Build3gppIndexProperty.m_u16PlayType = XMS_BUILD_INDEX_RAM; 

	GetDlgItem ( IDC_EDIT_BuildPlayIndex )->GetWindowText ( g_Build3gppIndexProperty.m_s8PlayContent, ACS_MAX_FILE_NAME_LEN-1 );
    
	//video
	if( ((CButton *)GetDlgItem ( IDC_RADIO_INDEX_FILE_VIDEO ))->GetCheck() )
		g_Build3gppIndexProperty.m_u16VideoPlayType = XMS_BUILD_INDEX_FILE; 
	else
		g_Build3gppIndexProperty.m_u16VideoPlayType = XMS_BUILD_INDEX_RAM; 

	GetDlgItem ( IDC_EDIT_BuildPlayIndex_Video )->GetWindowText ( g_Build3gppIndexProperty.m_s8VideoPlayContent, ACS_MAX_FILE_NAME_LEN-1 );

	CComboBox * pCB;
	pCB = (CComboBox *)this->GetDlgItem(IDC_COMBO_BuildIndex_MediaType);
    if (NULL == pCB)
	{
		ASSERT(0);
		return;
	}

	g_Build3gppIndexProperty.m_u8MediaType = (DJ_U8)pCB->GetItemData( pCB->GetCurSel() );

}
