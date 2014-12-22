// DlgMediaExOutput.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgMediaExOutput.h"
#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMediaExOutput dialog


CDlgMediaExOutput::CDlgMediaExOutput(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMediaExOutput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMediaExOutput)
	m_uiFPS = 0;
	m_sIP = _T("");
	m_uiKbps = 0;
	m_uiPort = 0;
	m_uiPT = 0;
	m_uiX = 0;
	m_uiY = 0;
	//}}AFX_DATA_INIT
}


void CDlgMediaExOutput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMediaExOutput)
	DDX_Control(pDX, IDC_CMB_MT, m_cbMT);
	DDX_Text(pDX, IDC_EDIT_FPS, m_uiFPS);
	DDV_MinMaxUInt(pDX, m_uiFPS, 0, 30);
	DDX_Text(pDX, IDC_EDIT_IP, m_sIP);
	DDX_Text(pDX, IDC_EDIT_KBPS, m_uiKbps);
	DDX_Text(pDX, IDC_EDIT_PORT, m_uiPort);
	DDV_MinMaxUInt(pDX, m_uiPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_PT, m_uiPT);
	DDV_MinMaxUInt(pDX, m_uiPT, 0, 127);
	DDX_Text(pDX, IDC_EDIT_X, m_uiX);
	DDX_Text(pDX, IDC_EDIT_Y, m_uiY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMediaExOutput, CDialog)
	//{{AFX_MSG_MAP(CDlgMediaExOutput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMediaExOutput message handlers

BOOL CDlgMediaExOutput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cbMT.InsertString(0, "H.263P");
	m_cbMT.InsertString(1, "H.263");
	m_cbMT.InsertString(2, "MPE4");
	m_cbMT.InsertString(3, "H.264");
	m_cbMT.SetCurSel(1);
	
	m_uiPT = 34;
	m_sIP = "192.168.10.202";
	m_uiPort = 20000;
	m_uiX = 176;
	m_uiY = 144;
	m_uiFPS = 0;
	m_uiKbps = 0;
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMediaExOutput::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	m_uiMedia = m_cbMT.GetCurSel();
	switch(m_uiMedia)
	{
	case 0:
		m_uiMedia = VOIP_MEDIA_VIDEO_H263P;
		break;
	case 1:
		m_uiMedia = VOIP_MEDIA_VIDEO_H263;
		break;
	case 2:
		m_uiMedia = VOIP_MEDIA_VIDEO_MPEG4;
		break;
	case 3:
		m_uiMedia = VOIP_MEDIA_VIDEO_H264;
		break;
	default:
		break;
	}
	CDialog::OnOK();
}
