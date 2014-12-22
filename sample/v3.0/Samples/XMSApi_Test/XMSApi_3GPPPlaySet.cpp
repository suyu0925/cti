// XMSApi_3GPPPlaySet.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "XMSApi_3GPPPlaySet.h"

#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"

#include "XMSApi_Test_Sub.h"
#include "XMSApi_Test_String.h"
#include "XMSApi_Test_Event.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern	int		iOpenedIndex1;

extern	TYPE_MY_DEVICE_STRUCT	DevOpened[];

extern PlayProperty_t		g_PlayProperty;
extern Play3gppProperty_t	g_Play3gppProperty;

/*标识是否启用录制码流命令*/
extern bool g_bIsPlayCodeStream;

/////////////////////////////////////////////////////////////////////////////
// CXMSApi_3GPPPlaySet dialog


CXMSApi_3GPPPlaySet::CXMSApi_3GPPPlaySet(CWnd* pParent /*=NULL*/)
	: CDialog(CXMSApi_3GPPPlaySet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXMSApi_3GPPPlaySet)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CXMSApi_3GPPPlaySet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXMSApi_3GPPPlaySet)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CXMSApi_3GPPPlaySet, CDialog)
	//{{AFX_MSG_MAP(CXMSApi_3GPPPlaySet)
	ON_BN_CLICKED(IDC_RADIO_Normal_Stop, OnRADIONormalStop)
	ON_BN_CLICKED(IDC_RADIO_Single_Code, OnRADIOSingleCode)
	ON_BN_CLICKED(IDC_RADIO_Any_Code, OnRADIOAnyCode)
	ON_BN_CLICKED(IDC_RADIO_PLAY_TYPE_FILE, OnRadioPlayTypeFile)
	ON_BN_CLICKED(IDC_RADIO_PLAY_TYPE_INDEX, OnRadioPlayTypeIndex)
	ON_BN_CLICKED(IDC_RADIO_PLAY_TYPE_FILE_QUEUE, OnRadioPlayTypeFileQueue)
	ON_BN_CLICKED(IDC_RADIO_PLAY_TYPE_INDEX_QUEUE, OnRadioPlayTypeIndexQueue)
	ON_BN_CLICKED(IDC_RADIO_PLY_CODE_STRM, OnRadioPlyCodeStrm)
	ON_BN_CLICKED(IDC_BUTTON_GET_AFILE_NAME, OnButtonGetAfileName)
	ON_BN_CLICKED(IDC_BUTTON_GET_VFILE_NAME, OnButtonGetVfileName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMSApi_3GPPPlaySet message handlers

BOOL CXMSApi_3GPPPlaySet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char	TmpStr[256];

	GetDlgItem ( IDC_EDIT_Play_DevcieID )->SetWindowText ( GetString_DeviceAll (&DevOpened[iOpenedIndex1].DevID) );

	//playpropetry . m_u32TaskID
	sprintf ( TmpStr, "%d", g_Play3gppProperty.m_u8TaskID );
	GetDlgItem ( IDC_EDIT_Play_u32TaskID )->SetWindowText ( TmpStr );
	
	//playpropetry . m_u32MaxSize
//	sprintf ( TmpStr, "%d", g_Play3gppProperty.m_u32MaxSize );
	//GetDlgItem ( IDC_EDIT_Play_u32MaxSize )->SetWindowText ( TmpStr );

	// playpropetry . m_u32MaxTime
	sprintf ( TmpStr, "%d", g_Play3gppProperty.m_u32MaxTime );
	GetDlgItem ( IDC_EDIT_Play_u32MaxTime )->SetWindowText ( TmpStr );

	sprintf ( TmpStr, "%d", g_Play3gppProperty.m_u32VideoMaxTime );
	GetDlgItem ( IDC_EDIT_Play_u32VideoMaxTime )->SetWindowText ( TmpStr );


	//sprintf ( TmpStr, "%d", g_Play3gppProperty.m_u8MediaType );
	//GetDlgItem ( IDC_EDIT_Play_u8MediaType )->SetWindowText ( TmpStr );
	
	//m_u8MediaType
	g_Play3gppProperty.m_u8MediaType = MEDIA_TYPE_ANV;
	if ( g_Play3gppProperty.m_u8MediaType == MEDIA_TYPE_ANV )
		((CButton *)GetDlgItem ( IDC_RADIO_ANV ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_ANV ))->SetCheck(0);

	if ( g_Play3gppProperty.m_u8MediaType == MEDIA_TYPE_AUDIO )
		((CButton *)GetDlgItem ( IDC_RADIO_AUDIO ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_AUDIO ))->SetCheck(0);

	if ( g_Play3gppProperty.m_u8MediaType == MEDIA_TYPE_VIDEO )
		((CButton *)GetDlgItem ( IDC_RADIO_VIDEO ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_VIDEO ))->SetCheck(0);

	
	//playpropetry . m_u8SrcMode
	if ( g_Play3gppProperty.m_u8SrcMode == XMS_SRC_8K )
		((CButton *)GetDlgItem ( IDC_RADIO_SRC_8K ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_SRC_8K ))->SetCheck(0);
	if ( g_Play3gppProperty.m_u8SrcMode == XMS_SRC_6K )
		((CButton *)GetDlgItem ( IDC_RADIO_SRC_6K ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_SRC_6K ))->SetCheck(0);
	if ( g_Play3gppProperty.m_u8SrcMode == XMS_SRC_GTG )
		((CButton *)GetDlgItem ( IDC_RADIO_SRC_GTG ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_SRC_GTG ))->SetCheck(0);
	if ( g_Play3gppProperty.m_u8SrcMode == XMS_SRC_FSK )
		((CButton *)GetDlgItem ( IDC_RADIO_SRC_FSK ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_SRC_FSK ))->SetCheck(0);
	if ( g_Play3gppProperty.m_u8SrcMode == XMS_SRC_FAX )
		((CButton *)GetDlgItem ( IDC_RADIO_SRC_FAX ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_SRC_FAX ))->SetCheck(0);

	//playpropetry . m_u8DecodeType
	if ( g_Play3gppProperty.m_u8DecodeType == XMS_Alaw_type )
		((CButton *)GetDlgItem ( IDC_RADIO_Alaw_type ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Alaw_type ))->SetCheck(0);
	if ( g_Play3gppProperty.m_u8DecodeType == XMS_Ulaw_type )
		((CButton *)GetDlgItem ( IDC_RADIO_Ulaw_type ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Ulaw_type ))->SetCheck(0);
	if ( g_Play3gppProperty.m_u8DecodeType == XMS_Vox_type )
		((CButton *)GetDlgItem ( IDC_RADIO_Vox_type ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Vox_type ))->SetCheck(0);
	if ( g_Play3gppProperty.m_u8DecodeType == XMS_Linear_8bit )
		((CButton *)GetDlgItem ( IDC_RADIO_Linear_8bit ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Linear_8bit ))->SetCheck(0);
	if ( g_Play3gppProperty.m_u8DecodeType == XMS_Linear_16bit )
		((CButton *)GetDlgItem ( IDC_RADIO_PLY_Linear_16bit ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_PLY_Linear_16bit ))->SetCheck(0);

	//playpropetry . m_u32StopMode
	if ( g_PlayProperty.m_u32StopMode == XMS_Normal_Stop )
		((CButton *)GetDlgItem ( IDC_RADIO_Normal_Stop ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Normal_Stop ))->SetCheck(0);
	if ( g_Play3gppProperty.m_u32StopMode == XMS_Single_Code )
		((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->SetCheck(0);
	if ( g_Play3gppProperty.m_u32StopMode == XMS_Any_Code )
		((CButton *)GetDlgItem ( IDC_RADIO_Any_Code ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Any_Code ))->SetCheck(0);

	//playpropetry . m_u32StopCode
	sprintf ( TmpStr, "%c", g_Play3gppProperty.m_u32StopCode );
	GetDlgItem ( IDC_EDIT_Play_u32StopCode )->SetWindowText ( TmpStr );

	//playpropetry . m_u16FileOffset
	sprintf ( TmpStr, "%d", g_Play3gppProperty.m_u16TimeOffset );
	GetDlgItem ( IDC_EDIT_Play_u16TimeOffset )->SetWindowText ( TmpStr );

	sprintf ( TmpStr, "%d", g_Play3gppProperty.m_u16VideoTimeOffset );
	GetDlgItem ( IDC_EDIT_Play_u16VideoTimeOffset )->SetWindowText ( TmpStr );

	//playpropetry . m_u16PlayType
	if ( g_Play3gppProperty.m_u16PlayType == XMS_PLAY_TYPE_FILE )
		((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_FILE ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_FILE ))->SetCheck(0);
	if ( g_Play3gppProperty.m_u16PlayType == XMS_PLAY_TYPE_INDEX )
		((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_INDEX ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_INDEX ))->SetCheck(0);
	if ( g_Play3gppProperty.m_u16PlayType == XMS_PLAY_TYPE_FILE_QUEUE )
		((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_FILE_QUEUE ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_FILE_QUEUE ))->SetCheck(0);
	if ( g_Play3gppProperty.m_u16PlayType == XMS_PLAY_TYPE_INDEX_QUEUE )
		((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_INDEX_QUEUE ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_INDEX_QUEUE ))->SetCheck(0);

	//playpropetry . m_u16PlayIndex
	sprintf ( TmpStr, "%d", g_Play3gppProperty.m_u16PlayIndex );
	GetDlgItem ( IDC_EDIT_Play_u16PlayIndex )->SetWindowText ( TmpStr );

	//playpropetry . m_u16PlayIndex
	sprintf ( TmpStr, "%d", g_Play3gppProperty.m_u16VideoPlayIndex );
	GetDlgItem ( IDC_EDIT_Play_u16PlayIndex_Video )->SetWindowText ( TmpStr );

	//playpropetry . m_s8PlayContext
	GetDlgItem ( IDC_EDIT_Play_s8PlayContent )->SetWindowText (g_Play3gppProperty.m_s8PlayContent);
	GetDlgItem ( IDC_EDIT_Play_s8PlayContent_3GPP )->SetWindowText (g_Play3gppProperty.m_s8VideoPlayContent);

	// -------------------------------------------------------------------------------
	// Handle Enable Disable
	HandleEnableDisable ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CXMSApi_3GPPPlaySet::OnOK() 
{
	// TODO: Add extra validation here
	char	TmpStr[256];
	int		iTmpVal;

	//playpropetry . m_u32MaxSize
//	GetDlgItem ( IDC_EDIT_Play_u32MaxSize )->GetWindowText ( TmpStr, 20 );
//	sscanf ( TmpStr, "%d", &g_Play3gppProperty.m_u32MaxSize );

	// playpropetry . m_u32MaxTime
	GetDlgItem ( IDC_EDIT_Play_u32MaxTime )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &g_Play3gppProperty.m_u32MaxTime );

	GetDlgItem ( IDC_EDIT_Play_u32VideoMaxTime )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &g_Play3gppProperty.m_u32VideoMaxTime );

	//GetDlgItem ( IDC_EDIT_Play_u8MediaType )->GetWindowText ( TmpStr, 20 );
	//sscanf ( TmpStr, "%d", &g_Play3gppProperty.m_u8MediaType );

	//m_u8MediaType
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_ANV ))->GetCheck() )
		g_Play3gppProperty.m_u8MediaType = MEDIA_TYPE_ANV;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_AUDIO ))->GetCheck() )
		g_Play3gppProperty.m_u8MediaType = MEDIA_TYPE_AUDIO;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_VIDEO ))->GetCheck() )
		g_Play3gppProperty.m_u8MediaType = MEDIA_TYPE_VIDEO;

	//playpropetry . m_u8SrcMode
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_SRC_8K ))->GetCheck() )
		g_Play3gppProperty.m_u8SrcMode = XMS_SRC_8K;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_SRC_6K ))->GetCheck() )
		g_Play3gppProperty.m_u8SrcMode = XMS_SRC_6K;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_SRC_GTG ))->GetCheck() )
		g_Play3gppProperty.m_u8SrcMode = XMS_SRC_GTG;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_SRC_FSK ))->GetCheck() )
		g_Play3gppProperty.m_u8SrcMode = XMS_SRC_FSK;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_SRC_FAX ))->GetCheck() )
		g_Play3gppProperty.m_u8SrcMode = XMS_SRC_FAX;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_SRC_3GP_VIDEO ))->GetCheck() )
		g_Play3gppProperty.m_u8SrcMode = XMS_SRC_3GVIDEO;

	//playpropetry . m_u8DecodeType
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Alaw_type ))->GetCheck() )
		g_Play3gppProperty.m_u8DecodeType = XMS_Alaw_type;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Ulaw_type ))->GetCheck() )
		g_Play3gppProperty.m_u8DecodeType = XMS_Ulaw_type;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Vox_type ))->GetCheck() )
		g_Play3gppProperty.m_u8DecodeType = XMS_Vox_type;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Linear_8bit ))->GetCheck() )
		g_Play3gppProperty.m_u8DecodeType = XMS_Linear_8bit;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_PLY_Linear_16bit ))->GetCheck() )
		g_Play3gppProperty.m_u8DecodeType = XMS_Linear_16bit;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_PLY_AMR_TYPE ))->GetCheck() )
		g_Play3gppProperty.m_u8DecodeType = XMS_Amr_type;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_PLY_G723_TYPE ))->GetCheck() )
		g_Play3gppProperty.m_u8DecodeType = XMS_G723_type;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_PLY_CODE_STRM ))->GetCheck() )
		g_Play3gppProperty.m_u8DecodeType = XMS_CODE_STREAM;

	//playpropetry . m_u32StopMode
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Normal_Stop ))->GetCheck() )
		g_Play3gppProperty.m_u32StopMode = XMS_Normal_Stop;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->GetCheck() )
		g_Play3gppProperty.m_u32StopMode = XMS_Single_Code;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Any_Code ))->GetCheck() )
		g_Play3gppProperty.m_u32StopMode = XMS_Any_Code;

	//playpropetry . m_u32StopCode
	GetDlgItem ( IDC_EDIT_Play_u32StopCode )->GetWindowText ( TmpStr, 20 );
    g_Play3gppProperty.m_u32StopCode = TmpStr[0];
	//sscanf ( TmpStr, "%d", &g_Play3gppProperty.m_u32StopCode );

	//playpropetry . m_u16FileOffset
	GetDlgItem ( IDC_EDIT_Play_u16TimeOffset )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
    g_Play3gppProperty.m_u16TimeOffset = iTmpVal;

	GetDlgItem ( IDC_EDIT_Play_u16VideoTimeOffset )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_Play3gppProperty.m_u16VideoTimeOffset = iTmpVal;

	//playpropetry . m_u16PlayType
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_FILE ))->GetCheck() )
		g_Play3gppProperty.m_u16PlayType = XMS_PLAY_TYPE_FILE;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_INDEX ))->GetCheck() )
		g_Play3gppProperty.m_u16PlayType = XMS_PLAY_TYPE_INDEX;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_FILE_QUEUE ))->GetCheck() )
		g_Play3gppProperty.m_u16PlayType = XMS_PLAY_TYPE_FILE_QUEUE;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_INDEX_QUEUE ))->GetCheck() )
		g_Play3gppProperty.m_u16PlayType = XMS_PLAY_TYPE_INDEX_QUEUE;

	g_Play3gppProperty.m_u16VideoPlayType = g_Play3gppProperty.m_u16PlayType;

	//playpropetry . m_u16PlayIndex
	GetDlgItem ( IDC_EDIT_Play_u16PlayIndex )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_Play3gppProperty.m_u16PlayIndex = iTmpVal;

		//playpropetry . m_u16PlayIndex
	GetDlgItem ( IDC_EDIT_Play_u16PlayIndex_Video )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_Play3gppProperty.m_u16VideoPlayIndex = iTmpVal;

	this->GetDlgItem ( IDC_EDIT_Play_s8PlayContent )->GetWindowText (g_Play3gppProperty.m_s8PlayContent, ACS_MAX_FILE_NAME_LEN-1 );
	this->GetDlgItem ( IDC_EDIT_Play_s8PlayContent_3GPP )->GetWindowText (g_Play3gppProperty.m_s8VideoPlayContent,ACS_MAX_FILE_NAME_LEN-1 );

	// -------------------------------------------------------------------------------
	
	CDialog::OnOK();
}

void CXMSApi_3GPPPlaySet::OnRADIONormalStop() 
{
	// TODO: Add your control notification handler code here
	
	// Handle Enable Disable
	HandleEnableDisable ();
}

void CXMSApi_3GPPPlaySet::OnRADIOSingleCode() 
{
	// TODO: Add your control notification handler code here
	
	// Handle Enable Disable
	HandleEnableDisable ();
}

void CXMSApi_3GPPPlaySet::OnRADIOAnyCode() 
{
	// TODO: Add your control notification handler code here
	
	// Handle Enable Disable
	HandleEnableDisable ();
}

void CXMSApi_3GPPPlaySet::OnRadioPlayTypeFile() 
{
	// TODO: Add your control notification handler code here

	// Handle Enable Disable
	HandleEnableDisable ();	
}

void CXMSApi_3GPPPlaySet::OnRadioPlayTypeIndex() 
{
	// TODO: Add your control notification handler code here
	
	// Handle Enable Disable
	HandleEnableDisable ();	
}

void CXMSApi_3GPPPlaySet::OnRadioPlayTypeFileQueue() 
{
	// TODO: Add your control notification handler code here
	
	// Handle Enable Disable
	HandleEnableDisable ();	
}

void CXMSApi_3GPPPlaySet::OnRadioPlayTypeIndexQueue() 
{
	// TODO: Add your control notification handler code here
	
	// Handle Enable Disable
	HandleEnableDisable ();	
}

void CXMSApi_3GPPPlaySet::OnRadioPlyCodeStrm() 
{
	// TODO: Add your control notification handler code here
	g_bIsPlayCodeStream = true;
	HandleEnableDisable();
	g_bIsPlayCodeStream = false;
}

void CXMSApi_3GPPPlaySet::HandleEnableDisable()
{
	Enable_File (true);
}

void CXMSApi_3GPPPlaySet::Enable_File(bool IsEnable )
{
	bool	bNow = false;

	if (g_bIsPlayCodeStream)
	{
		// handle all
		//playpropetry . m_u32TaskID
		GetDlgItem ( IDC_EDIT_Play_u32TaskID )->EnableWindow(bNow);
		
		//playpropetry . m_u32MaxSize
//		GetDlgItem ( IDC_EDIT_Play_u32MaxSize )->EnableWindow(bNow);

		// playpropetry . m_u32MaxTime
		GetDlgItem ( IDC_EDIT_Play_u32MaxTime )->EnableWindow(bNow);

		// playpropetry . m_u32VideoMaxTime
		GetDlgItem ( IDC_EDIT_Play_u32VideoMaxTime )->EnableWindow(bNow);

		//playpropetry . m_u8MediaType
		GetDlgItem ( IDC_RADIO_ANV )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_AUDIO )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_VIDEO )->EnableWindow(bNow);

		//playpropetry . m_u8SrcMode
		GetDlgItem ( IDC_RADIO_SRC_8K )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_SRC_6K )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_SRC_GTG )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_SRC_FSK )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_SRC_FAX )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_SRC_3GP_VIDEO )->EnableWindow(bNow);
		((CButton *)GetDlgItem ( IDC_RADIO_SRC_3GP_VIDEO ))->SetCheck(1);

		//playpropetry . m_u8DecodeType
		GetDlgItem ( IDC_RADIO_Alaw_type )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Ulaw_type )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Vox_type )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Linear_8bit )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_PLY_Linear_16bit )->EnableWindow(bNow);
        GetDlgItem ( IDC_RADIO_PLY_AMR_TYPE )->EnableWindow(bNow);
        GetDlgItem ( IDC_RADIO_PLY_G723_TYPE )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_PLY_CODE_STRM )->EnableWindow(bNow);
        ((CButton *)GetDlgItem ( IDC_RADIO_PLY_CODE_STRM ))->SetCheck(1);

		//playpropetry . m_u32StopMode
		GetDlgItem ( IDC_RADIO_Normal_Stop )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Single_Code )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_Any_Code )->EnableWindow(bNow);

		//playpropetry . m_u32StopCode
		GetDlgItem ( IDC_EDIT_Play_u32StopCode )->EnableWindow(bNow);

		//playpropetry . m_u16FileOffset
		GetDlgItem ( IDC_EDIT_Play_u16TimeOffset )->EnableWindow(bNow);
		GetDlgItem ( IDC_EDIT_Play_u16VideoTimeOffset )->EnableWindow(bNow);

		//playpropetry . m_u16PlayType
		GetDlgItem ( IDC_RADIO_PLAY_TYPE_FILE )->EnableWindow(bNow);
		((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_FILE ))->SetCheck(1);
		GetDlgItem ( IDC_RADIO_PLAY_TYPE_INDEX )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_PLAY_TYPE_FILE_QUEUE )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_PLAY_TYPE_INDEX_QUEUE )->EnableWindow(bNow);

		//playpropetry . m_u16PlayIndex
		GetDlgItem ( IDC_EDIT_Play_u16PlayIndex )->EnableWindow(bNow);
		GetDlgItem ( IDC_EDIT_Play_u16PlayIndex_Video )->EnableWindow(bNow);

		/* handle some special
		if ( IsEnable )
		{
			// Enable/Disable : m_u32StopMode
			bNow = (((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->GetCheck()==1);
			GetDlgItem ( IDC_EDIT_Play_u32StopCode )->EnableWindow(bNow);

			bNow = (((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_INDEX ))->GetCheck()==1) 
				|| (((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_INDEX_QUEUE ))->GetCheck()==1);
			GetDlgItem ( IDC_EDIT_Play_u16PlayIndex )->EnableWindow(bNow);
		}   */
	}
	else
	{
		// handle all
		//playpropetry . m_u32TaskID
		GetDlgItem ( IDC_EDIT_Play_u32TaskID )->EnableWindow(IsEnable);
		
		//playpropetry . m_u32MaxSize
		//GetDlgItem ( IDC_EDIT_Play_u32MaxSize )->EnableWindow(IsEnable);

		// playpropetry . m_u32MaxTime
		GetDlgItem ( IDC_EDIT_Play_u32MaxTime )->EnableWindow(IsEnable);

		// playpropetry . m_u32VideoMaxTime
		GetDlgItem ( IDC_EDIT_Play_u32VideoMaxTime )->EnableWindow(IsEnable);

    	//GetDlgItem ( IDC_EDIT_Play_u8MediaType )->EnableWindow(IsEnable);
		//playpropetry . m_u8MediaType
		GetDlgItem ( IDC_RADIO_ANV )->EnableWindow(IsEnable);
		GetDlgItem ( IDC_RADIO_AUDIO )->EnableWindow(IsEnable);
		GetDlgItem ( IDC_RADIO_VIDEO )->EnableWindow(IsEnable);

		//playpropetry . m_u8SrcMode
		GetDlgItem ( IDC_RADIO_SRC_8K )->EnableWindow(false);
		GetDlgItem ( IDC_RADIO_SRC_6K )->EnableWindow(false);
		GetDlgItem ( IDC_RADIO_SRC_GTG )->EnableWindow(false);
		GetDlgItem ( IDC_RADIO_SRC_FSK )->EnableWindow(false);
		GetDlgItem ( IDC_RADIO_SRC_FAX )->EnableWindow(false);
		GetDlgItem ( IDC_RADIO_SRC_3GP_VIDEO )->EnableWindow(false);

		//playpropetry . m_u8DecodeType
		GetDlgItem ( IDC_RADIO_Alaw_type )->EnableWindow(false);
		GetDlgItem ( IDC_RADIO_Ulaw_type )->EnableWindow(false);
		GetDlgItem ( IDC_RADIO_Vox_type )->EnableWindow(false);
		GetDlgItem ( IDC_RADIO_Linear_8bit )->EnableWindow(false);
		GetDlgItem ( IDC_RADIO_PLY_Linear_16bit )->EnableWindow(false);
		GetDlgItem ( IDC_RADIO_PLY_AMR_TYPE )->EnableWindow(false);
		GetDlgItem ( IDC_RADIO_PLY_G723_TYPE )->EnableWindow(false);
		GetDlgItem ( IDC_RADIO_PLY_CODE_STRM )->EnableWindow(false);

		//playpropetry . m_u32StopMode
		GetDlgItem ( IDC_RADIO_Normal_Stop )->EnableWindow(IsEnable);
		GetDlgItem ( IDC_RADIO_Single_Code )->EnableWindow(IsEnable);
		GetDlgItem ( IDC_RADIO_Any_Code )->EnableWindow(IsEnable);

		//playpropetry . m_u32StopCode
		GetDlgItem ( IDC_EDIT_Play_u32StopCode )->EnableWindow(IsEnable);

		//playpropetry . m_u16FileOffset
		GetDlgItem ( IDC_EDIT_Play_u16TimeOffset )->EnableWindow(IsEnable);
		GetDlgItem ( IDC_EDIT_Play_u16VideoTimeOffset )->EnableWindow(IsEnable);

		//playpropetry . m_u16PlayType
		GetDlgItem ( IDC_RADIO_PLAY_TYPE_FILE )->EnableWindow(IsEnable);
		GetDlgItem ( IDC_RADIO_PLAY_TYPE_INDEX )->EnableWindow(IsEnable);
		GetDlgItem ( IDC_RADIO_PLAY_TYPE_FILE_QUEUE )->EnableWindow(IsEnable);
		GetDlgItem ( IDC_RADIO_PLAY_TYPE_INDEX_QUEUE )->EnableWindow(IsEnable);

		//playpropetry . m_u16PlayIndex
		GetDlgItem ( IDC_EDIT_Play_u16PlayIndex )->EnableWindow(IsEnable);
		GetDlgItem ( IDC_EDIT_Play_u16PlayIndex_Video )->EnableWindow(IsEnable);

		// handle some special
		if ( IsEnable )
		{
			// Enable/Disable : m_u32StopMode
			bNow = (((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->GetCheck()==1);
			GetDlgItem ( IDC_EDIT_Play_u32StopCode )->EnableWindow(bNow);

			bNow = (((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_INDEX ))->GetCheck()==1) 
				|| (((CButton *)GetDlgItem ( IDC_RADIO_PLAY_TYPE_INDEX_QUEUE ))->GetCheck()==1);
			{
			GetDlgItem ( IDC_EDIT_Play_u16PlayIndex )->EnableWindow(bNow);
			GetDlgItem ( IDC_EDIT_Play_u16PlayIndex_Video )->EnableWindow(bNow);
			}
		}
	}
}

void CXMSApi_3GPPPlaySet::OnButtonGetAfileName() 
{
	// TODO: Add your control notification handler code here
	Select3GPPPlayFile(IDC_EDIT_Play_s8PlayContent);
}

void CXMSApi_3GPPPlaySet::OnButtonGetVfileName() 
{
	// TODO: Add your control notification handler code here
	Select3GPPPlayFile(IDC_EDIT_Play_s8PlayContent_3GPP);	
}

void CXMSApi_3GPPPlaySet::Select3GPPPlayFile(DWORD u32EditID)
{
	char	TmpStr[256];                                                              
                                                                                          
	GetDlgItem ( u32EditID )->GetWindowText ( TmpStr, MAX_FILE_NAME_LEN-1 );
                                                                                          
	My_SelectFile ( TmpStr );                                                         
                                                                                          
	GetDlgItem ( u32EditID )->SetWindowText ( TmpStr );  
}
