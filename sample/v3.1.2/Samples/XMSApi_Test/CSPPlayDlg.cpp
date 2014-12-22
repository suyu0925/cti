// CSPPlayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "CSPPlayDlg.h"
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

extern FILE * g_cspPlayFp;
extern FILE * g_cspRecordFp;

extern DeviceID_t g_PlayCSPDevID;
extern DeviceID_t g_RecCSPDevID;

extern char   g_szCSPPlayFile[MAX_PATH];
extern char   g_szCSPRecordFile[MAX_PATH];

extern int    g_cspPlay;
extern unsigned char g_u8CSPPlayTaskID;
extern ACSHandle_t		        g_acsHandle;
extern TYPE_MY_DEVICE_STRUCT	DevOpened[MAX_DEVICE_ALLOW_OPEN];
extern int			            iOpenedIndex1;

/////////////////////////////////////////////////////////////////////////////
// CCSPPlayDlg dialog

extern DeviceID_t DevPlayCsp;

CCSPPlayDlg::CCSPPlayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCSPPlayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCSPPlayDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCSPPlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCSPPlayDlg)
	DDX_Control(pDX, IDC_COMBO_SRC_MODE, m_PlaySrcMode);
	DDX_Control(pDX, IDC_COMBO_DECODE_TYPE, m_DecodeType);
//	DDX_Control(pDX, IDC_EDIT_DATALEN, m_DataLen);
//	DDX_Control(pDX, IDC_COMBO_DATATYPE, m_DataType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCSPPlayDlg, CDialog)
	//{{AFX_MSG_MAP(CCSPPlayDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)	
	ON_BN_CLICKED(IDC_RADIO_Normal_Stop, OnRADIONormalStop)
	ON_BN_CLICKED(IDC_RADIO_Single_Code, OnRADIOSingleCode)
	ON_BN_CLICKED(IDC_RADIO_Any_Code, OnRADIOAnyCode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCSPPlayDlg message handlers

void CCSPPlayDlg::OnButton1() 
{
	char MsgStr[100]={0};
	char TmpStr[20] = {0};
	int r = 0;
	CSPPlayProperty_t cspProperty={0};
	CSP_OPERATER*pCSP = GetCurrVocCSPProperty( );

	if ( NULL == pCSP )
		return;
	
	//sprintf(szBuf,"%d",g_u8CSPPlayTaskID );	
	GetDlgItem ( IDC_EDIT_TASKID )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &g_u8CSPPlayTaskID );

	cspProperty.m_u8DecodeType = m_DecodeType.GetCurSel();
	cspProperty.m_u8SrcMode    = m_PlaySrcMode.GetCurSel();
	cspProperty.m_u8TaskID     = g_u8CSPPlayTaskID;

	GetDlgItem ( IDC_EDIT_MAX_SIZE )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &cspProperty.m_u32MaxSize );

	GetDlgItem ( IDC_EDIT_MAX_TIME )->GetWindowText ( TmpStr, 20 );
	sscanf ( TmpStr, "%d", &cspProperty.m_u32MaxTime );

	cspProperty.m_u32StopMode = XMS_Normal_Stop;
	cspProperty.m_u32StopCode = 0;
	
		//playpropetry . m_u32StopMode
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Normal_Stop ))->GetCheck() )
		cspProperty.m_u32StopMode = XMS_Normal_Stop;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->GetCheck() )
		cspProperty.m_u32StopMode = XMS_Single_Code;
	if ( ((CButton *)GetDlgItem ( IDC_RADIO_Any_Code ))->GetCheck() )
		cspProperty.m_u32StopMode = XMS_Any_Code;

	//playpropetry . m_u32StopCode
	GetDlgItem ( IDC_EDIT_CSP_STOP_MODE )->GetWindowText ( TmpStr, 20 );
    cspProperty.m_u32StopCode = TmpStr[0];

	
	g_PlayCSPDevID = pCSP->m_PlayCSPDevID;
	pCSP->m_PlayCSPProperty = cspProperty;
	g_cspPlay = pCSP->m_cspPlay = 1;

	//XMS_ctsPlayCSP(g_acsHandle,&DevOpened[iOpenedIndex1].DevID, &cspProperty,NULL);
	XMS_ctsPlayCSP(g_acsHandle,&g_PlayCSPDevID, &cspProperty,NULL);
	if ( r < 0 )
	{
		sprintf ( MsgStr, "X(%d) XMS_ctsPlayCSP() FAIL! (%s)", 
			r, GetString_DeviceAll (&g_PlayCSPDevID)  );
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr);
	}
	else
	{
		sprintf ( MsgStr, "XMS_ctsPlayCSP() OK! (%s)", 
			GetString_DeviceAll (&g_PlayCSPDevID));
		AddMsg ( MSG_TYPE_FUNCTION, MsgStr );
	}

	CDialog::OnOK();	
}

BOOL CCSPPlayDlg::OnInitDialog() 
{
	CSP_OPERATER*pCSP = GetCurrVocCSPProperty( );
	
	CDialog::OnInitDialog();
	char szBuf[100] = {0};

	m_DecodeType.AddString("XMS_Alaw_type");
	m_DecodeType.AddString("XMS_Ulaw_type");
	m_DecodeType.AddString("XMS_Vox_type");
	m_DecodeType.AddString("XMS_Linear_8bit");
	m_DecodeType.AddString("XMS_Linear_16bit");

	m_DecodeType.SetCurSel(0);
	
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
	m_PlaySrcMode.AddString("XMS_SRC_8K");
	m_PlaySrcMode.AddString("XMS_SRC_6K");
	m_PlaySrcMode.AddString("XMS_SRC_GTG");
	m_PlaySrcMode.AddString("XMS_SRC_FSK Invalid");
	m_PlaySrcMode.AddString("XMS_SRC_RTP Invalid");
	m_PlaySrcMode.AddString("XMS_SRC_FAX Invalid");
	m_PlaySrcMode.AddString("XMS_SRC_3GVIDEO Invalid");
	m_PlaySrcMode.AddString("XMS_SRC_11K");
	m_PlaySrcMode.AddString("XMS_SRC_FAX_ECM Invalid");

	m_PlaySrcMode.SetCurSel(0);
		
	//g_cspPlay = 1;
//	m_DataLen.SetWindowText("4000");
//	m_DataType.AddString("Voc");	
//	m_DataType.AddString("Video");
//	m_DataType.SetCurSel(0);
    
	g_u8CSPPlayTaskID = (DJ_U8)GetTickCount();
	if ( NULL != pCSP )
		pCSP->m_u8CSPPlayTaskID = g_u8CSPPlayTaskID;

	
	sprintf(szBuf,"%d",g_u8CSPPlayTaskID );	
	GetDlgItem ( IDC_EDIT_TASKID )->SetWindowText(szBuf);

	sprintf(szBuf,"%d",0 );	
	GetDlgItem ( IDC_EDIT_MAX_SIZE )->SetWindowText(szBuf);

	sprintf(szBuf,"%d",0 );	
	GetDlgItem ( IDC_EDIT_MAX_TIME )->SetWindowText(szBuf);

	bool bNow = false;

	// TODO: Add your control notification handler code here
	((CButton *)GetDlgItem ( IDC_RADIO_Normal_Stop ))->SetCheck(true);

	// TODO: Add your control notification handler code here
	bNow = (((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->GetCheck()==1);
	GetDlgItem ( IDC_EDIT_CSP_STOP_MODE )->EnableWindow(bNow);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCSPPlayDlg::OnRADIONormalStop() 
{
	bool bNow = false;

	// TODO: Add your control notification handler code here
	bNow = (((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->GetCheck()==1);
	GetDlgItem ( IDC_EDIT_CSP_STOP_MODE )->EnableWindow(bNow);
}

void CCSPPlayDlg::OnRADIOSingleCode() 
{
	bool bNow = false;

	// TODO: Add your control notification handler code here
	bNow = (((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->GetCheck()==1);
	GetDlgItem ( IDC_EDIT_CSP_STOP_MODE )->EnableWindow(bNow);
	
}

void CCSPPlayDlg::OnRADIOAnyCode() 
{
	bool bNow = false;

	// TODO: Add your control notification handler code here
	bNow = (((CButton *)GetDlgItem ( IDC_RADIO_Single_Code ))->GetCheck()==1);
	GetDlgItem ( IDC_EDIT_CSP_STOP_MODE )->EnableWindow(bNow);
	
}
