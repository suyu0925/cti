// RecCSPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "RecCSPDlg.h"
#include "DJAcsDataDef.h"
#include "DJAcsAPIDef.h"
#include "XMSApi_Test_Event.h"
#include "XMSApi_Test_String.h"
#include "XMSApi_Test_Sub.h"

#include "DJAcsDataDef.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern ACSHandle_t		        g_acsHandle;
extern TYPE_MY_DEVICE_STRUCT	DevOpened[MAX_DEVICE_ALLOW_OPEN];
extern int			            iOpenedIndex1;
extern RecordCSPProperty_t      g_RecCSP;

extern FILE * g_cspPlayFp;
extern FILE * g_cspRecordFp;

extern char   g_szCSPPlayFile[MAX_PATH];
extern char   g_szCSPRecordFile[MAX_PATH];
/////////////////////////////////////////////////////////////////////////////
// CRecCSPDlg dialog




extern DeviceID_t g_RecCSPDevID;

CRecCSPDlg::CRecCSPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRecCSPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecCSPDlg)
	//}}AFX_DATA_INIT
}


void CRecCSPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecCSPDlg)
	DDX_Control(pDX, IDC_EDIT_PACKLEN, m_PackLen);
	DDX_Control(pDX, IDC_COMBO_SRCMODE, m_SrcMode);
	DDX_Control(pDX, IDC_COMBO_ENCODETYPE, m_EncodeType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecCSPDlg, CDialog)
	//{{AFX_MSG_MAP(CRecCSPDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_CHECK_s8MixEnable, OnCHECKs8MixEnable)
	ON_BN_CLICKED(IDC_RADIO_Normal_Stop, OnRADIONormalStop)
	ON_BN_CLICKED(IDC_RADIO_Single_Code, OnRADIOSingleCode)
	ON_BN_CLICKED(IDC_RADIO_Any_Code, OnRADIOAnyCode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecCSPDlg message handlers

BOOL CRecCSPDlg::OnInitDialog() 
{
	char szBuf[100] = {0};
	char TmpStr[512] = {0};
	CSP_OPERATER*pCSP = GetCurrVocCSPProperty( );

	CDialog::OnInitDialog();
	/*
	XMS_Alaw_type                    = 0x0,
	XMS_Ulaw_type                    = 0x1,
	XMS_Vox_type                     = 0x2,
	XMS_Linear_8bit                  = 0x3,
	XMS_Linear_16bit                 = 0x4,
	XMS_Amr_type                     = 0x5,
	XMS_G723_type                    = 0x6,
	XMS_CODE_STREAM                  = 0x7,
  */
	m_EncodeType.AddString("XMS_Alaw_type");
	m_EncodeType.AddString("XMS_Ulaw_type");
	m_EncodeType.AddString("XMS_Vox_type");
	m_EncodeType.AddString("XMS_Linear_8bit");
	m_EncodeType.AddString("XMS_Linear_16bit");

	m_EncodeType.SetCurSel(0);
	
	/*
	XMS_SRC_8K                       = 0x0,
	XMS_SRC_6K                       = 0x1,
	XMS_SRC_GTG                      = 0x2,
	XMS_SRC_FSK                      = 0x3,
	XMS_SRC_RTP                      = 0x4,
	XMS_SRC_FAX                      = 0x5,
	XMS_SRC_3GVIDEO                  = 0x6,
	XMS_SRC_11K                      = 0x7,
	XMS_SRC_FAX_ECM                  = 0x8,
	*/
	m_SrcMode.AddString("XMS_SRC_8K");
	m_SrcMode.AddString("XMS_SRC_6K");
	m_SrcMode.AddString("XMS_SRC_GTG");
	m_SrcMode.AddString("XMS_SRC_FSK Invalid");
	m_SrcMode.AddString("XMS_SRC_RTP Invalid");
	m_SrcMode.AddString("XMS_SRC_FAX Invalid");
	m_SrcMode.AddString("XMS_SRC_3GVIDEO Invalid");
	m_SrcMode.AddString("XMS_SRC_11K");
	m_SrcMode.AddString("XMS_SRC_FAX_ECM Invalid");

	m_SrcMode.SetCurSel(0);

	if ( NULL != pCSP )
		g_RecCSP = pCSP->m_RecCSPProperty;
	
	g_RecCSP.m_u16PacketLen = 2000; //init the PktLen to 2000 bytes/second
	sprintf(szBuf, "%d", g_RecCSP.m_u16PacketLen );
	GetDlgItem ( IDC_EDIT_PACKLEN )->SetWindowText ( szBuf );

	if ( XMS_CSPREC_BARGEIN == g_RecCSP.m_u8CSPRecType )
	{
		((CButton *)GetDlgItem ( IDC_RADIO_BARGE_IN ))->SetCheck(true);
	}
	else
	{
		((CButton *)GetDlgItem ( IDC_RADIO_NO_BARGE_IN ))->SetCheck(true);	
	}

	////////////////////////////////////////////////////////////////////////////////
	// g_RecordProperty . m_u8StopMode
	if ( g_RecCSP.m_u8StopMode == XMS_Normal_Stop )
		((CButton *)GetDlgItem ( IDC_RADIO_Normal_Stop ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Normal_Stop ))->SetCheck(0);
	if ( g_RecCSP.m_u8StopMode == XMS_Single_Code )
		((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->SetCheck(0);
	if ( g_RecCSP.m_u8StopMode == XMS_Any_Code )
		((CButton *)GetDlgItem ( IDC_RADIO_Any_Code ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_Any_Code ))->SetCheck(0);

	// g_RecordProperty . m_u8StopCode
	sprintf ( TmpStr, "%c", g_RecCSP.m_u8StopCode );
	GetDlgItem ( IDC_EDIT_Record_u8StopCode )->SetWindowText ( TmpStr );

	
	// g_RecordProperty . m_u8IsVadEnable
	((CButton *)GetDlgItem ( IDC_CHECK_u8VADEnable ))->SetCheck(g_RecCSP.m_u8IsVADEnable); 

	// g_RecordProperty . m_s8IsMixEnable
	((CButton *)GetDlgItem ( IDC_CHECK_s8MixEnable ))->SetCheck(g_RecCSP.m_s8IsMixEnable); 

	// g_RecordProperty . m_MixerControl . m_u8SRC1_Ctrl
	if ( g_RecCSP.m_MixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_NULL )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL ))->SetCheck(0);
	if ( g_RecCSP.m_MixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_INPUT )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT ))->SetCheck(0);
	if ( g_RecCSP.m_MixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_PLAY )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY ))->SetCheck(0);
	if ( g_RecCSP.m_MixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_CONF )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF ))->SetCheck(0);
	if ( g_RecCSP.m_MixerControl.m_u8SRC1_Ctrl == XMS_MIXER_FROM_IP )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP ))->SetCheck(0);

	// g_RecordProperty . m_MixerControl . m_u8SRC2_Ctrl
	if ( g_RecCSP.m_MixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_NULL )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL2 ))->SetCheck(0);
	if ( g_RecCSP.m_MixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_INPUT )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT2 ))->SetCheck(0);
	if ( g_RecCSP.m_MixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_PLAY )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY2 ))->SetCheck(0);
	if ( g_RecCSP.m_MixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_CONF )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF2 ))->SetCheck(0);
	if ( g_RecCSP.m_MixerControl.m_u8SRC2_Ctrl == XMS_MIXER_FROM_IP )
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP2 ))->SetCheck(1);
	else
		((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP2 ))->SetCheck(0);

	// g_RecordProperty . m_MixerControl . m_u16SRC_ChID1
	sprintf ( TmpStr, "%d", g_RecCSP.m_MixerControl.m_u16SRC_ChID1 );
	GetDlgItem ( IDC_EDIT_Record_u16SRC_ChID1 )->SetWindowText ( TmpStr );
	
	// g_RecordProperty . m_MixerControl . m_u16SRC_ChID2
	sprintf ( TmpStr, "%d", g_RecCSP.m_MixerControl.m_u16SRC_ChID2 );
	GetDlgItem ( IDC_EDIT_Record_u16SRC_ChID2 )->SetWindowText ( TmpStr );
	
	
	// Handle Enable Disable
	HandleEnableDisable();
	
	////////////////////////////////////////////////////////////////////////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRecCSPDlg::OnButton1() 
{
	char szBuf[100] = {0};
	char MsgStr[100]={0}, TmpStr[512] = {0};
	int nPackLen;
	int r = 0, iTmpVal = 0;
	
	CSP_OPERATER*pCSP = GetCurrVocCSPProperty( );

	if ( NULL == pCSP )
		return;

	g_cspRecordFp = pCSP->m_cspRecordFp;

	if ( NULL != g_cspRecordFp )
		return;
	
	g_cspRecordFp = fopen(g_szCSPRecordFile,"w+b");
	if ( NULL ==  g_cspRecordFp ) 
		return;

	pCSP->m_cspRecordFp = g_cspRecordFp;
	
	g_RecCSP.m_u8EncodeType = m_EncodeType.GetCurSel();
	g_RecCSP.m_u8SRCMode = m_SrcMode.GetCurSel();

	GetDlgItem ( IDC_EDIT_PACKLEN )->GetWindowText ( szBuf, 20 );
	sscanf ( szBuf, "%d", &nPackLen);
	g_RecCSP.m_u16PacketLen = nPackLen;

	if ( ((CButton *)GetDlgItem ( IDC_RADIO_BARGE_IN ))->GetCheck() )
		g_RecCSP.m_u8CSPRecType = XMS_CSPREC_BARGEIN; 

	if ( ((CButton *)GetDlgItem ( IDC_RADIO_NO_BARGE_IN ))->GetCheck() )
		g_RecCSP.m_u8CSPRecType = XMS_CSPREC_NON_BARGEIN; 

		// g_RecordProperty . m_u8StopMode
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Normal_Stop ))->GetCheck() )
		g_RecCSP.m_u8StopMode = XMS_Normal_Stop;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->GetCheck() )
		g_RecCSP.m_u8StopMode = XMS_Single_Code;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Any_Code ))->GetCheck() )
		g_RecCSP.m_u8StopMode = XMS_Any_Code;

	// g_RecordProperty . m_u8StopCode
	GetDlgItem ( IDC_EDIT_Record_u8StopCode )->GetWindowText ( TmpStr, 20 );
	//sscanf ( TmpStr, "%d", &iTmpVal );
	g_RecCSP.m_u8StopCode = TmpStr[0];

	// g_RecordProperty . m_u8IsVadEnable
	g_RecCSP.m_u8IsVADEnable = ((CButton *)GetDlgItem ( IDC_CHECK_u8VADEnable ))->GetCheck();

	// g_RecordProperty . m_s8IsMixEnable
	g_RecCSP.m_s8IsMixEnable = ((CButton *)GetDlgItem ( IDC_CHECK_s8MixEnable ))->GetCheck();

	// g_RecordProperty . m_MixerControl . m_u8SRC1_Ctrl
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL ))->GetCheck() )
		g_RecCSP.m_MixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_NULL;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT ))->GetCheck() )
		g_RecCSP.m_MixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_INPUT;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY ))->GetCheck() )
		g_RecCSP.m_MixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_PLAY;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF ))->GetCheck() )
		g_RecCSP.m_MixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_CONF;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP ))->GetCheck() )
		g_RecCSP.m_MixerControl.m_u8SRC1_Ctrl = XMS_MIXER_FROM_IP;

	// g_RecordProperty . m_MixerControl . m_u8SRC2_Ctrl
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL2 ))->GetCheck() )
		g_RecCSP.m_MixerControl.m_u8SRC2_Ctrl = XMS_MIXER_FROM_NULL;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT2 ))->GetCheck() )
		g_RecCSP.m_MixerControl.m_u8SRC2_Ctrl = XMS_MIXER_FROM_INPUT;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY2 ))->GetCheck() )
		g_RecCSP.m_MixerControl.m_u8SRC2_Ctrl = XMS_MIXER_FROM_PLAY;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF2 ))->GetCheck() )
		g_RecCSP.m_MixerControl.m_u8SRC2_Ctrl = XMS_MIXER_FROM_CONF;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP2 ))->GetCheck() )
		g_RecCSP.m_MixerControl.m_u8SRC2_Ctrl = XMS_MIXER_FROM_IP;

	// g_RecordProperty . m_MixerControl . m_u16SRC_ChID1
	GetDlgItem ( IDC_EDIT_Record_u16SRC_ChID1 )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_RecCSP.m_MixerControl.m_u16SRC_ChID1 = iTmpVal;
	
	// g_RecordProperty . m_MixerControl . m_u16SRC_ChID2
	GetDlgItem ( IDC_EDIT_Record_u16SRC_ChID2 )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &iTmpVal );
	g_RecCSP.m_MixerControl.m_u16SRC_ChID2 = iTmpVal;

	g_RecCSPDevID = pCSP->m_RecCSPDevID;
	pCSP->m_RecCSPProperty = g_RecCSP;
	
	r = XMS_ctsRecordCSP(g_acsHandle, &g_RecCSPDevID, 
		&g_RecCSP,NULL);
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsSRecordCSP() FAIL! (%s)", 
			r, GetString_DeviceAll (&g_RecCSPDevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr);
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsSRecordCSP() OK! (%s)", 
			GetString_DeviceAll (&g_RecCSPDevID));
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}
    
	TRACE("Encode: %d, SRC: %d, RecT: %d, PktLen: %d, StopMode: %d, StopCode: %x, MixEnable: %d, SrcCtrl1: %d, SrcCtrl2: %d, CHID1: %d, CHID2: %d\n", 
		g_RecCSP.m_u8EncodeType, g_RecCSP.m_u8SRCMode, g_RecCSP.m_u8CSPRecType, g_RecCSP.m_u16PacketLen, g_RecCSP.m_u8StopMode, g_RecCSP.m_u8StopCode, g_RecCSP.m_s8IsMixEnable, g_RecCSP.m_MixerControl.m_u8SRC1_Ctrl, g_RecCSP.m_MixerControl.m_u8SRC2_Ctrl, g_RecCSP.m_MixerControl.m_u16SRC_ChID1, g_RecCSP.m_MixerControl.m_u16SRC_ChID2 );
	
	CDialog::OnOK();
}

void CRecCSPDlg::HandleEnableDisable()
{
	bool	bNow;

	// Enable/Disable : m_u32StopMode
	bNow = (((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->GetCheck()==1);
	GetDlgItem ( IDC_EDIT_Record_u8StopCode )->EnableWindow(bNow);

	// Enable/Disable : m_s8MixEnable
	bNow = (((CButton *)GetDlgItem ( IDC_CHECK_s8MixEnable ))->GetCheck()==1);
	{
		// g_RecordProperty . m_MixerControl . m_u8SRC1_Ctrl
		GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP )->EnableWindow(bNow);

		// g_RecordProperty . m_MixerControl . m_u8SRC2_Ctrl
		GetDlgItem ( IDC_RADIO_MIXER_FROM_NULL2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_INPUT2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_PLAY2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_CONF2 )->EnableWindow(bNow);
		GetDlgItem ( IDC_RADIO_MIXER_FROM_RTP2 )->EnableWindow(bNow);

		// g_RecordProperty . m_MixerControl . m_u16SRC_ChID1
		GetDlgItem ( IDC_EDIT_Record_u16SRC_ChID1 )->EnableWindow(bNow);
	
		// g_RecordProperty . m_MixerControl . m_u16SRC_ChID2
		GetDlgItem ( IDC_EDIT_Record_u16SRC_ChID2 )->EnableWindow(bNow);
	}

}

void CRecCSPDlg::OnCHECKs8MixEnable() 
{
	// TODO: Add your control notification handler code here
	HandleEnableDisable();
}

void CRecCSPDlg::OnRADIONormalStop() 
{
	// Handle Enable Disable
	HandleEnableDisable();
}

void CRecCSPDlg::OnRADIOSingleCode() 
{
	// Handle Enable Disable
	HandleEnableDisable();	
}

void CRecCSPDlg::OnRADIOAnyCode() 
{
	// Handle Enable Disable
	HandleEnableDisable();	
}
