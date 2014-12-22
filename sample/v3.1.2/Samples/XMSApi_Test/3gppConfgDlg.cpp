// 3gppConfgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "3gppConfgDlg.h"

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"
#include "XMSApi_Test_Sub.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3gppConfgDlg dialog
extern Get3gppCfg_t          g_Get3gpCfg;


C3gppConfgDlg::C3gppConfgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(C3gppConfgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(C3gppConfgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void C3gppConfgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3gppConfgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(C3gppConfgDlg, CDialog)
	//{{AFX_MSG_MAP(C3gppConfgDlg)
	ON_BN_CLICKED(IDC_BUTTON_AUDIO_GET_PATH, OnButtonAudioGetPath)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_GET_PATH, OnButtonVideoGetPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3gppConfgDlg message handlers

BOOL C3gppConfgDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	memset(&g_Get3gpCfg, 0, sizeof(Get3gppCfg_t) );

	/*init the button state*/
	((CButton *)GetDlgItem ( IDC_RADIO_ANV ))->SetCheck(TRUE);
	((CButton *)GetDlgItem ( IDC_RADIO_AUDIO_NO_INDEX ))->SetCheck(TRUE);
	((CButton *)GetDlgItem ( IDC_RADIO_VIDEO_NO_INDEX ))->SetCheck(TRUE);

	GetDlgItem ( IDC_EDIT_AUDIO_Index )->EnableWindow(FALSE);
	GetDlgItem ( IDC_EDIT_VIDEO_Index )->EnableWindow(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void C3gppConfgDlg::OnButtonAudioGetPath() 
{
	char	TmpStr[256];
	// TODO: Add your control notification handler code here
	GetDlgItem ( IDC_EDIT_AUDIO_FILE_NAME )->GetWindowText ( TmpStr, MAX_FILE_NAME_LEN-1 );

	My_SelectFile ( TmpStr );

	GetDlgItem ( IDC_EDIT_AUDIO_FILE_NAME )->SetWindowText ( TmpStr );
	
}

void C3gppConfgDlg::OnButtonVideoGetPath() 
{
	char	TmpStr[256];
	// TODO: Add your control notification handler code here
	GetDlgItem ( IDC_EDIT_VIDEO_FILE_NAME )->GetWindowText ( TmpStr, MAX_FILE_NAME_LEN-1 );

	My_SelectFile ( TmpStr );

	GetDlgItem ( IDC_EDIT_VIDEO_FILE_NAME )->SetWindowText ( TmpStr );
	
}

void C3gppConfgDlg::OnOK() 
{
	// TODO: Add extra validation here
	int iRet = 0;
	char temp[256] = {0};

	memset(&g_Get3gpCfg, 0, sizeof(Get3gppCfg_t) );

	if (((CButton *)GetDlgItem ( IDC_RADIO_ANV ))->GetCheck() == 1)
		g_Get3gpCfg.m_u8MediaType = MEDIA_TYPE_ANV;
	if (((CButton *)GetDlgItem ( IDC_RADIO_AUDIO ))->GetCheck() == 1)
		g_Get3gpCfg.m_u8MediaType = MEDIA_TYPE_AUDIO;
	if (((CButton *)GetDlgItem ( IDC_RADIO_VIDEO ))->GetCheck() == 1)
		g_Get3gpCfg.m_u8MediaType = MEDIA_TYPE_VIDEO;

	if (MEDIA_TYPE_AUDIO == g_Get3gpCfg.m_u8MediaType 
	 || MEDIA_TYPE_ANV == g_Get3gpCfg.m_u8MediaType )
	{
		if (((CButton *)GetDlgItem ( IDC_RADIO_AUDIO_NO_INDEX ))->GetCheck() == 1)
		{
			g_Get3gpCfg.m_u8AudioFileType = XMS_CFG_TYPE_NON_INDEX;
			g_Get3gpCfg.m_u16AudioFileIndex = 0;

			GetDlgItem ( IDC_EDIT_AUDIO_FILE_NAME )->GetWindowText ( g_Get3gpCfg.m_s8AudioFileName, MAX_FILE_NAME_LEN-1 );
		}
		else
		{
			g_Get3gpCfg.m_u8AudioFileType = XMS_CFG_TYPE_INDEX;

			memset(g_Get3gpCfg.m_s8AudioFileName, 0, MAX_FILE_NAME_LEN);
			GetDlgItem ( IDC_EDIT_AUDIO_Index )->GetWindowText ( temp, 256 );
			g_Get3gpCfg.m_u16AudioFileIndex = atoi(temp);			
		}
		
	}


	if (MEDIA_TYPE_VIDEO == g_Get3gpCfg.m_u8MediaType 
	 || MEDIA_TYPE_ANV == g_Get3gpCfg.m_u8MediaType )
	{
		if (((CButton *)GetDlgItem ( IDC_RADIO_VIDEO_NO_INDEX ))->GetCheck() == 1)
		{
			g_Get3gpCfg.m_u8VideoFileType = XMS_CFG_TYPE_NON_INDEX;
			g_Get3gpCfg.m_u16VideoFileIndex = 0;

			GetDlgItem ( IDC_EDIT_VIDEO_FILE_NAME )->GetWindowText ( g_Get3gpCfg.m_s8VideoFileName, MAX_FILE_NAME_LEN-1 );
		}
		else
		{
			g_Get3gpCfg.m_u8VideoFileType = XMS_CFG_TYPE_INDEX;

			memset(g_Get3gpCfg.m_s8VideoFileName, 0, MAX_FILE_NAME_LEN);
			GetDlgItem ( IDC_EDIT_VIDEO_Index )->GetWindowText ( temp, 256 );
			g_Get3gpCfg.m_u16VideoFileIndex = atoi(temp);			
		}
		
	}
	
	CDialog::OnOK();
}
