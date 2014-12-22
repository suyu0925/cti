// DlgMediaExInput.cpp : implementation file
//

#include "stdafx.h"
#include "XMSApi_Test.h"
#include "DlgMediaExInput.h"
#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMediaExInput dialog


CDlgMediaExInput::CDlgMediaExInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMediaExInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMediaExInput)
	m_uiLevel = 0;
	m_uiPort = 0;
	m_uiPT = 0;
	//}}AFX_DATA_INIT
}


void CDlgMediaExInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMediaExInput)
	DDX_Control(pDX, IDC_CMB_MT, m_cbMT);
	DDX_Text(pDX, IDC_EDIT_LEVEL, m_uiLevel);
	DDV_MinMaxUInt(pDX, m_uiLevel, 0, 5);
	DDX_Text(pDX, IDC_EDIT_PORT, m_uiPort);
	DDV_MinMaxUInt(pDX, m_uiPort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_PT, m_uiPT);
	DDV_MinMaxUInt(pDX, m_uiPT, 0, 127);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMediaExInput, CDialog)
	//{{AFX_MSG_MAP(CDlgMediaExInput)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMediaExInput message handlers

BOOL CDlgMediaExInput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cbMT.InsertString(0, "H.263P");
	m_cbMT.InsertString(1, "H.263");
	m_cbMT.InsertString(2, "MPE4");
	m_cbMT.InsertString(3, "H.264");
	m_cbMT.SetCurSel(1);
	
	m_uiPT = 34;
	m_uiPort = 20000;
	m_uiLevel = 0;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMediaExInput::OnOK() 
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
