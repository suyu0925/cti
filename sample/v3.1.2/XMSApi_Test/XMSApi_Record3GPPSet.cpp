// XMSApi_Record3GPPSet.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "XMSApi_Record3GPPSet.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"

#include "XMSApi_Test_String.h"
#include "XMSApi_Test_Event.h"

extern Record3gppProperty_t   g_Record3gppProperty;
extern	int		iOpenedIndex1;

extern	TYPE_MY_DEVICE_STRUCT	DevOpened[MAX_DEVICE_ALLOW_OPEN];
/////////////////////////////////////////////////////////////////////////////
// CXMSApi_Record3GPPSet dialog


CXMSApi_Record3GPPSet::CXMSApi_Record3GPPSet(CWnd* pParent /*=NULL*/)
	: CDialog(CXMSApi_Record3GPPSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXMSApi_Record3GPPSet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CXMSApi_Record3GPPSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXMSApi_Record3GPPSet)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXMSApi_Record3GPPSet, CDialog)
	//{{AFX_MSG_MAP(CXMSApi_Record3GPPSet)
	ON_BN_CLICKED(IDC_RADIO_Normal_Stop, OnRADIONormalStop)
	ON_BN_CLICKED(IDC_RADIO_Single_Code, OnRADIOSingleCode)
	ON_BN_CLICKED(IDC_RADIO_Any_Code, OnRADIOAnyCode)
	ON_BN_CLICKED(IDC_CHECK_s8MixEnable, OnCHECKs8MixEnable)
	ON_BN_CLICKED(IDC_CHECK_Viedeo_s8MixEnable, OnCHECKViedeos8MixEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMSApi_Record3GPPSet message handlers

void CXMSApi_Record3GPPSet::OnOK() 
{
	// TODO: Add extra validation here
	char	TmpStr[256];
	int		iTmpVal;

	//////////////////////////////////////////////////////////////////////////
	//common
	// g_Record3gppProperty . m_u8StopMode
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Normal_Stop ))->GetCheck() )
		g_Record3gppProperty.m_u8StopMode = XMS_Normal_Stop;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->GetCheck() )
		g_Record3gppProperty.m_u8StopMode = XMS_Single_Code;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Any_Code ))->GetCheck() )
		g_Record3gppProperty.m_u8StopMode = XMS_Any_Code;

	// g_Record3gppProperty . m_u8StopCode
	GetDlgItem ( IDC_EDIT_Record_u8StopCode )->GetWindowText ( TmpStr, 20 );
	//sscanf ( TmpStr, "%d", &iTmpVal );
	g_Record3gppProperty.m_u8StopCode = TmpStr[0];

	// g_Record3gppProperty . m_u32MaxTime
	GetDlgItem ( IDC_EDIT_Record_u32MaxTime )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &g_Record3gppProperty.m_u32MaxTime );
     
	// g_Record3gppProperty . m_s8IsAppend
	g_Record3gppProperty . m_s8IsAppend = ((CButton *)GetDlgItem ( IDC_CHECK_s8IsAppend ))->GetCheck();
	//////////////////////////////////////////////////////////////////////////
	//audio
	// g_Record3gppProperty . m_u8AudioEncodeType
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_amr_type ))->GetCheck() )
		g_Record3gppProperty.m_u8AudioEncodeType = XMS_Amr_type;

	// g_Record3gppProperty . m_u8AudioSRCMode
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_SRC_3GVIDEO ))->GetCheck() )
		g_Record3gppProperty.m_u8AudioSRCMode = XMS_SRC_3GVIDEO;

    //g_Record3gppProperty.m_u8AudioProfiles
	GetDlgItem ( IDC_EDIT_Record_Audio_Profile )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_Record3gppProperty.m_u8AudioProfiles = iTmpVal;

    //g_Record3gppProperty.m_u8AudioLevel
	GetDlgItem ( IDC_EDIT_Record_Audio_Level )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_Record3gppProperty.m_u8AudioLevel = iTmpVal;

	
	// g_Record3gppProperty . m_s8AudioIsMixEnable
	g_Record3gppProperty.m_s8AudioIsMixEnable = ((CButton *)GetDlgItem ( IDC_CHECK_s8MixEnable ))->GetCheck();

	// g_Record3gppProperty . m_AudioMixerControl . m_u8SRC1_Ctrl
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL ))->GetCheck() )
		g_Record3gppProperty.m_AudioMixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_NULL;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT ))->GetCheck() )
		g_Record3gppProperty.m_AudioMixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_INPUT;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY ))->GetCheck() )
		g_Record3gppProperty.m_AudioMixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_PLAY;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF ))->GetCheck() )
		g_Record3gppProperty.m_AudioMixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_CONF;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP ))->GetCheck() )
		g_Record3gppProperty.m_AudioMixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_IP;

	// g_Record3gppProperty . m_AudioMixerControl . m_u8SRC2_Ctrl
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL2 ))->GetCheck() )
		g_Record3gppProperty.m_AudioMixerControl.m_u8SRC2_Ctrl = XMS_MIXER_FROM_NULL;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT2 ))->GetCheck() )
		g_Record3gppProperty.m_AudioMixerControl.m_u8SRC2_Ctrl = XMS_MIXER_FROM_INPUT;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY2 ))->GetCheck() )
		g_Record3gppProperty.m_AudioMixerControl.m_u8SRC2_Ctrl = XMS_MIXER_FROM_PLAY;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF2 ))->GetCheck() )
		g_Record3gppProperty.m_AudioMixerControl.m_u8SRC2_Ctrl = XMS_MIXER_FROM_CONF;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP2 ))->GetCheck() )
		g_Record3gppProperty.m_AudioMixerControl.m_u8SRC2_Ctrl = XMS_MIXER_FROM_IP;

	// g_Record3gppProperty . m_AudioMixerControl . m_u16SRC_ChID1
	GetDlgItem ( IDC_EDIT_Record_u16SRC_ChID1 )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_Record3gppProperty.m_AudioMixerControl.m_u16SRC_ChID1 = iTmpVal;
	
	// g_Record3gppProperty . m_AudioMixerControl . m_u16SRC_ChID2
	GetDlgItem ( IDC_EDIT_Record_u16SRC_ChID2 )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_Record3gppProperty.m_AudioMixerControl.m_u16SRC_ChID2 = iTmpVal;

	//////////////////////////////////////////////////////////////////////////
	//video
		// g_Record3gppProperty . m_u8VideoEncodeType
	if ( ((CButton *)GetDlgItem ( IDC_Radio_Record_H263 ))->GetCheck() )
		g_Record3gppProperty.m_u8VideoEncodeType = XMS_VIDEO_CODE_TYPE_H263;
	else if ( ((CButton *)GetDlgItem ( IDC_Radio_Record_Mp4v ))->GetCheck() )
		g_Record3gppProperty.m_u8VideoEncodeType = XMS_VIDEO_CODE_TYPE_MP4V;
	else if ( ((CButton *)GetDlgItem ( IDC_Radio_Record_H264 ))->GetCheck() )
		g_Record3gppProperty.m_u8VideoEncodeType = XMS_VIDEO_CODE_TYPE_H264;

		// g_Record3gppProperty . m_u8VideoFrameRate
	GetDlgItem ( IDC_EDIT_Record_VIdeoFrameRate )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_Record3gppProperty.m_u8VideoFrameRate = iTmpVal;

			// g_Record3gppProperty . m_u8VideoProfiles
	GetDlgItem ( IDC_EDIT_Record_Vdieo_Profile )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_Record3gppProperty.m_u8VideoProfiles = iTmpVal;

			// g_Record3gppProperty . m_u8VideoLevel
	GetDlgItem ( IDC_EDIT_Record_Video_Level )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_Record3gppProperty.m_u8VideoLevel = iTmpVal;

			// g_Record3gppProperty . m_u16VideoWidth
	GetDlgItem ( IDC_EDIT_Record_Vdieo_Width )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_Record3gppProperty.m_u16VideoWidth = iTmpVal;

				// g_Record3gppProperty . m_u16VideoHeight
	GetDlgItem ( IDC_EDIT_Record_Video_Height )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_Record3gppProperty.m_u16VideoHeight = iTmpVal;
	
	// g_Record3gppProperty . m_s8AudioIsMixEnable
	g_Record3gppProperty.m_s8VideoIsMixEnable = ((CButton *)GetDlgItem ( IDC_CHECK_Viedeo_s8MixEnable ))->GetCheck();

	// g_Record3gppProperty . m_AudioMixerControl . m_u8SRC1_Ctrl
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_NULL ))->GetCheck() )
		g_Record3gppProperty.m_VideoMixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_NULL;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_INPUT ))->GetCheck() )
		g_Record3gppProperty.m_VideoMixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_INPUT;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_PLAY ))->GetCheck() )
		g_Record3gppProperty.m_VideoMixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_PLAY;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_CONF ))->GetCheck() )
		g_Record3gppProperty.m_VideoMixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_CONF;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_RTP ))->GetCheck() )
		g_Record3gppProperty.m_VideoMixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_IP;

	// g_Record3gppProperty . m_AudioMixerControl . m_u8SRC2_Ctrl
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_NULL2 ))->GetCheck() )
		g_Record3gppProperty.m_VideoMixerControl.m_u8SRC2_Ctrl = XMS_MIXER_FROM_NULL;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_INPUT2 ))->GetCheck() )
		g_Record3gppProperty.m_VideoMixerControl.m_u8SRC2_Ctrl = XMS_MIXER_FROM_INPUT;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_PLAY2 ))->GetCheck() )
		g_Record3gppProperty.m_VideoMixerControl.m_u8SRC2_Ctrl = XMS_MIXER_FROM_PLAY;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_CONF2 ))->GetCheck() )
		g_Record3gppProperty.m_VideoMixerControl.m_u8SRC2_Ctrl = XMS_MIXER_FROM_CONF;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_RTP2 ))->GetCheck() )
		g_Record3gppProperty.m_VideoMixerControl.m_u8SRC2_Ctrl = XMS_MIXER_FROM_IP;

	// g_Record3gppProperty . m_AudioMixerControl . m_u16SRC_ChID1
	GetDlgItem ( IDC_EDIT_Record_Video_u16SRC_ChID1 )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_Record3gppProperty.m_VideoMixerControl.m_u16SRC_ChID1 = iTmpVal;
	
	// g_Record3gppProperty . m_AudioMixerControl . m_u16SRC_ChID2
	GetDlgItem ( IDC_EDIT_Record_Video_u16SRC_ChID2 )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_Record3gppProperty.m_VideoMixerControl.m_u16SRC_ChID2 = iTmpVal;

	CDialog::OnOK();
}

BOOL CXMSApi_Record3GPPSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char	TmpStr[256];

	///////////////////////////////////////////////////////////////////////////////////////////////////
	//common param
	// g_Record3gppProperty . m_s8IsAppend
    ((CButton *)GetDlgItem ( IDC_CHECK_s8IsAppend ))->EnableWindow(FALSE);
	((CButton *)GetDlgItem ( IDC_CHECK_s8IsAppend ))->SetCheck(g_Record3gppProperty.m_s8IsAppend);

	// g_Record3gppProperty . m_s8FileName
	GetDlgItem ( IDC_EDIT_Record_s8FileName )->SetWindowText (g_Record3gppProperty.m_s8FileName);

	// g_Record3gppProperty . m_u32MaxTime
	sprintf ( TmpStr, "%d", g_Record3gppProperty.m_u32MaxTime );
	GetDlgItem ( IDC_EDIT_Record_u32MaxTime )->SetWindowText ( TmpStr );

	//GetDlgItem ( IDC_EDIT_Record_DevcieID )->SetWindowText ( GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );
    	// g_Record3gppProperty . m_u8StopMode
	if ( g_Record3gppProperty.m_u8StopMode == XMS_Normal_Stop )
		((CButton *)GetDlgItem ( IDC_RADIO_Normal_Stop ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Normal_Stop ))->SetCheck(0);
	if ( g_Record3gppProperty.m_u8StopMode == XMS_Single_Code )
		((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->SetCheck(0);
	if ( g_Record3gppProperty.m_u8StopMode == XMS_Any_Code )
		((CButton *)GetDlgItem ( IDC_RADIO_Any_Code ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Any_Code ))->SetCheck(0);

	// g_Record3gppProperty . m_u8StopCode
	sprintf ( TmpStr, "%c", g_Record3gppProperty.m_u8StopCode );
	GetDlgItem ( IDC_EDIT_Record_u8StopCode )->SetWindowText ( TmpStr );

	///////////////////////////////////////////////////////////////////////////////////////////////////
	//audio param
	// g_Record3gppProperty . m_u8AudioEncodeType
	g_Record3gppProperty.m_u8AudioEncodeType = XMS_Amr_type;
	if ( g_Record3gppProperty.m_u8AudioEncodeType == XMS_Amr_type )
		((CButton *)GetDlgItem ( IDC_RADIO_amr_type ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_amr_type ))->SetCheck(0);

	// g_Record3gppProperty . m_u8AudioSRCMode
	g_Record3gppProperty.m_u8AudioSRCMode = XMS_SRC_3GVIDEO;
	if ( g_Record3gppProperty.m_u8AudioSRCMode == XMS_SRC_3GVIDEO )
		((CButton *)GetDlgItem ( IDC_RADIO_SRC_3GVIDEO ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_SRC_3GVIDEO ))->SetCheck(0);

	//g_Record3gppProperty.m_u8AudioProfiles
	sprintf ( TmpStr, "%d", g_Record3gppProperty.m_u8AudioProfiles );
	GetDlgItem ( IDC_EDIT_Record_Audio_Profile )->SetWindowText ( TmpStr );

	//g_Record3gppProperty.m_u8AudioLevel
	sprintf ( TmpStr, "%d", g_Record3gppProperty.m_u8AudioLevel );
	GetDlgItem ( IDC_EDIT_Record_Audio_Level )->SetWindowText ( TmpStr );

	// g_Record3gppProperty . m_s8AudioIsMixEnable
	((CButton *)GetDlgItem ( IDC_CHECK_s8MixEnable ))->SetCheck(g_Record3gppProperty.m_s8AudioIsMixEnable); 

	// g_Record3gppProperty . m_AudioMixerControl . m_u8SRC1_Ctrl
	if ( g_Record3gppProperty.m_AudioMixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_NULL )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL ))->SetCheck(0);
	if ( g_Record3gppProperty.m_AudioMixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_INPUT )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT ))->SetCheck(0);
	if ( g_Record3gppProperty.m_AudioMixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_PLAY )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY ))->SetCheck(0);
	if ( g_Record3gppProperty.m_AudioMixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_CONF )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF ))->SetCheck(0);
	if ( g_Record3gppProperty.m_AudioMixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_IP )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP ))->SetCheck(0);

	if ( g_Record3gppProperty.m_AudioMixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_324 )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_324 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_324 ))->SetCheck(0);

	if ( g_Record3gppProperty.m_AudioMixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_RTPX )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CTD ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CTD ))->SetCheck(0);

	// g_Record3gppProperty . m_AudioMixerControl . m_u8SRC2_Ctrl
	if ( g_Record3gppProperty.m_AudioMixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_NULL )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL2 ))->SetCheck(0);
	if ( g_Record3gppProperty.m_AudioMixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_INPUT )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT2 ))->SetCheck(0);
	if ( g_Record3gppProperty.m_AudioMixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_PLAY )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY2 ))->SetCheck(0);
	if ( g_Record3gppProperty.m_AudioMixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_CONF )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF2 ))->SetCheck(0);
	if ( g_Record3gppProperty.m_AudioMixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_IP )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP2 ))->SetCheck(0);

	if ( g_Record3gppProperty.m_AudioMixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_324 )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_324_2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_324_2 ))->SetCheck(0);

	if ( g_Record3gppProperty.m_AudioMixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_RTPX )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CTD2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CTD2 ))->SetCheck(0);


	// g_Record3gppProperty . m_AudioMixerControl . m_u16SRC_ChID1
	sprintf ( TmpStr, "%d", g_Record3gppProperty.m_AudioMixerControl.m_u16SRC_ChID1 );
	GetDlgItem ( IDC_EDIT_Record_u16SRC_ChID1 )->SetWindowText ( TmpStr );
	
	// g_Record3gppProperty . m_AudioMixerControl . m_u16SRC_ChID2
	sprintf ( TmpStr, "%d", g_Record3gppProperty.m_AudioMixerControl.m_u16SRC_ChID2 );
	GetDlgItem ( IDC_EDIT_Record_u16SRC_ChID2 )->SetWindowText ( TmpStr );

	///////////////////////////////////////////////////////////////////////////////////////////////////
	//video param
	if ( g_Record3gppProperty.m_u8VideoEncodeType == XMS_VIDEO_CODE_TYPE_H263 )
		((CButton *)GetDlgItem ( IDC_Radio_Record_H263 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_Radio_Record_H263 ))->SetCheck(0);

	if ( g_Record3gppProperty.m_u8VideoEncodeType == XMS_VIDEO_CODE_TYPE_MP4V )
		((CButton *)GetDlgItem ( IDC_Radio_Record_Mp4v ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_Radio_Record_Mp4v ))->SetCheck(0);

	if ( g_Record3gppProperty.m_u8VideoEncodeType == XMS_VIDEO_CODE_TYPE_H264 )
		((CButton *)GetDlgItem ( IDC_Radio_Record_H264 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_Radio_Record_H264 ))->SetCheck(0);

	//g_Record3gppProperty.m_u8VideoFrameRate
 	sprintf ( TmpStr, "%d", g_Record3gppProperty.m_u8VideoFrameRate );
	GetDlgItem ( IDC_EDIT_Record_VIdeoFrameRate )->SetWindowText ( TmpStr );
  
		//g_Record3gppProperty.m_u8VideoProfiles
 	sprintf ( TmpStr, "%d", g_Record3gppProperty.m_u8VideoProfiles );
	GetDlgItem ( IDC_EDIT_Record_Vdieo_Profile )->SetWindowText ( TmpStr );

		//g_Record3gppProperty.m_u8VideoLevel
 	sprintf ( TmpStr, "%d", g_Record3gppProperty.m_u8VideoLevel );
	GetDlgItem ( IDC_EDIT_Record_Video_Level )->SetWindowText ( TmpStr );

		//g_Record3gppProperty.m_u16VideoWidth
 	sprintf ( TmpStr, "%d", g_Record3gppProperty.m_u16VideoWidth );
	GetDlgItem ( IDC_EDIT_Record_Vdieo_Width )->SetWindowText ( TmpStr );

		//g_Record3gppProperty.m_u16VideoHeight
 	sprintf ( TmpStr, "%d", g_Record3gppProperty.m_u16VideoHeight );
	GetDlgItem ( IDC_EDIT_Record_Video_Height )->SetWindowText ( TmpStr );

	// g_Record3gppProperty . m_s8VideoIsMixEnable
	g_Record3gppProperty.m_s8VideoIsMixEnable = 0;
	((CButton *)GetDlgItem ( IDC_CHECK_Viedeo_s8MixEnable ))->SetCheck(g_Record3gppProperty.m_s8VideoIsMixEnable); 

	// g_Record3gppProperty . m_VideoMixerControl . m_u8SRC1_Ctrl
	if ( g_Record3gppProperty.m_VideoMixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_NULL )
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_NULL ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_NULL ))->SetCheck(0);
	if ( g_Record3gppProperty.m_VideoMixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_INPUT )
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_INPUT ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_INPUT ))->SetCheck(0);
	if ( g_Record3gppProperty.m_VideoMixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_PLAY )
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_PLAY ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_PLAY ))->SetCheck(0);
	if ( g_Record3gppProperty.m_VideoMixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_CONF )
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_CONF ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_CONF ))->SetCheck(0);
	if ( g_Record3gppProperty.m_VideoMixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_IP )
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_RTP ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_RTP ))->SetCheck(0);

	if ( g_Record3gppProperty.m_VideoMixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_324 )
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_324 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_324 ))->SetCheck(0);

	if ( g_Record3gppProperty.m_VideoMixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_RTPX )
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_CTD ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_CTD ))->SetCheck(0);

	// g_Record3gppProperty . m_VideoMixerControl . m_u8SRC2_Ctrl
	if ( g_Record3gppProperty.m_VideoMixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_NULL )
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_NULL2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_NULL2 ))->SetCheck(0);
	if ( g_Record3gppProperty.m_VideoMixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_INPUT )
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_INPUT2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_INPUT2 ))->SetCheck(0);
	if ( g_Record3gppProperty.m_VideoMixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_PLAY )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_PLAY2 ))->SetCheck(0);
	if ( g_Record3gppProperty.m_VideoMixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_CONF )
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_CONF2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_CONF2 ))->SetCheck(0);
	if ( g_Record3gppProperty.m_VideoMixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_IP )
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_RTP2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_RTP2 ))->SetCheck(0);

	if ( g_Record3gppProperty.m_VideoMixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_324 )
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_324_2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_324_2 ))->SetCheck(0);

	if ( g_Record3gppProperty.m_VideoMixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_RTPX )
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_CTD2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_CTD2 ))->SetCheck(0);

	// g_Record3gppProperty . m_VideoMixerControl . m_u16SRC_ChID1
	sprintf ( TmpStr, "%d", g_Record3gppProperty.m_VideoMixerControl.m_u16SRC_ChID1 );
	GetDlgItem ( IDC_EDIT_Record_Video_u16SRC_ChID1 )->SetWindowText ( TmpStr );
	
	// g_Record3gppProperty . m_VideoMixerControl . m_u16SRC_ChID2
	sprintf ( TmpStr, "%d", g_Record3gppProperty.m_VideoMixerControl.m_u16SRC_ChID2 );
	GetDlgItem ( IDC_EDIT_Record_Video_u16SRC_ChID2 )->SetWindowText ( TmpStr );

	// Handle Enable Disable
	HandleEnableDisable();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CXMSApi_Record3GPPSet::OnRADIONormalStop() 
{
	// TODO: Add your control notification handler code here

	// Handle Enable Disable
	HandleEnableDisable();	
}

void CXMSApi_Record3GPPSet::OnRADIOSingleCode() 
{
	// TODO: Add your control notification handler code here

	// Handle Enable Disable
	HandleEnableDisable();	
}

void CXMSApi_Record3GPPSet::OnRADIOAnyCode() 
{
	// TODO: Add your control notification handler code here

	// Handle Enable Disable
	HandleEnableDisable();	
}

void CXMSApi_Record3GPPSet::HandleEnableDisable()
{
	bool	bNow;

	// Enable/Disable : m_u32StopMode
	bNow = (((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->GetCheck()==1);
	GetDlgItem ( IDC_EDIT_Record_u8StopCode )->EnableWindow(bNow);

	// Enable/Disable : m_s8MixEnable
	bNow = (((CButton *)GetDlgItem ( IDC_CHECK_s8MixEnable ))->GetCheck()==1);
	{
		// g_Record3gppProperty . m_AudioMixerControl . m_u8SRC1_Ctrl
		GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_324 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_CTD )->EnableWindow(bNow);

		// g_Record3gppProperty . m_AudioMixerControl . m_u8SRC2_Ctrl
		GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_324_2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_CTD2 )->EnableWindow(bNow);

		// g_Record3gppProperty . m_AudioMixerControl . m_u16SRC_ChID1
		GetDlgItem ( IDC_EDIT_Record_u16SRC_ChID1 )->EnableWindow(bNow);
	
		// g_Record3gppProperty . m_AudioMixerControl . m_u16SRC_ChID2
		GetDlgItem ( IDC_EDIT_Record_u16SRC_ChID2 )->EnableWindow(bNow);
	}

		// Enable/Disable : m_s8VideoIsMixEnable
	bNow = (((CButton *)GetDlgItem ( IDC_CHECK_Viedeo_s8MixEnable ))->GetCheck()==1);
	{
		// g_Record3gppProperty . m_AudioMixerControl . m_u8SRC1_Ctrl
		GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_NULL )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_INPUT )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_PLAY )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_CONF )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_RTP )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_324 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_CTD )->EnableWindow(bNow);

		// g_Record3gppProperty . m_AudioMixerControl . m_u8SRC2_Ctrl
		GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_NULL2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_INPUT2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_PLAY2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_CONF2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_RTP2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_324_2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Video_MIXER_FROM_CTD2 )->EnableWindow(bNow);

		// g_Record3gppProperty . m_AudioMixerControl . m_u16SRC_ChID1
		GetDlgItem ( IDC_EDIT_Record_Video_u16SRC_ChID1 )->EnableWindow(bNow);
	
		// g_Record3gppProperty . m_AudioMixerControl . m_u16SRC_ChID2
		GetDlgItem ( IDC_EDIT_Record_Video_u16SRC_ChID2 )->EnableWindow(bNow);
	}

}

void CXMSApi_Record3GPPSet::OnCHECKs8MixEnable() 
{
	// TODO: Add your control notification handler code here
	
	// Handle Enable Disable
	HandleEnableDisable();	
}

void CXMSApi_Record3GPPSet::OnCHECKViedeos8MixEnable() 
{
	// TODO: Add your control notification handler code here
	
	// Handle Enable Disable
	HandleEnableDisable();		
}
