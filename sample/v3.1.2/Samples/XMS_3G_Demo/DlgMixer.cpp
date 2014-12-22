// DlgMixer.cpp : implementation file
//

#include "stdafx.h"
#include "SP.h"
#include "DlgMixer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMixer dialog


CDlgMixer::CDlgMixer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMixer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMixer)
	m_bAudio = FALSE;
	m_bVideo = FALSE;
	m_uiSrcId = 0;
	m_uiSrc2Id = 0;
	//}}AFX_DATA_INIT
	m_iSrcCtrl = 0;
}


void CDlgMixer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMixer)
	DDX_Control(pDX, IDC_CMB_SRC2CTRL, m_CobSrc2Ctrl);
	DDX_Control(pDX, IDC_CMB_SRCCTRL, m_CobSrcCtrl);
	DDX_Check(pDX, IDC_CHK_AUDIO, m_bAudio);
	DDX_Check(pDX, IDC_CHK_VIDEO, m_bVideo);
	DDX_Text(pDX, IDC_EDIT_SRCID, m_uiSrcId);
	DDV_MinMaxUInt(pDX, m_uiSrcId, 0, 128);
	DDX_Text(pDX, IDC_EDIT_SRC2ID, m_uiSrc2Id);
	DDV_MinMaxUInt(pDX, m_uiSrc2Id, 0, 128);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMixer, CDialog)
	//{{AFX_MSG_MAP(CDlgMixer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMixer message handlers

BOOL CDlgMixer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_CobSrcCtrl.InsertString(0, "From NULL");
	m_CobSrcCtrl.InsertString(1, "From Input");
	m_CobSrcCtrl.InsertString(2, "From Play");
	m_CobSrcCtrl.InsertString(3, "From Conf");
	m_CobSrcCtrl.InsertString(4, "From RTP");
	m_CobSrcCtrl.InsertString(5, "From 3G-324M");
	m_CobSrcCtrl.InsertString(6, "From RTPX");
	m_CobSrcCtrl.SetCurSel(4);

	m_CobSrc2Ctrl.InsertString(0, "From NULL");
	m_CobSrc2Ctrl.InsertString(1, "From Input");
	m_CobSrc2Ctrl.InsertString(2, "From Play");
	m_CobSrc2Ctrl.InsertString(3, "From Conf");
	m_CobSrc2Ctrl.InsertString(4, "From RTP");
	m_CobSrc2Ctrl.InsertString(5, "From 3G-324M");
	m_CobSrc2Ctrl.InsertString(6, "From RTPX");
	m_CobSrc2Ctrl.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMixer::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	m_iSrcCtrl = m_CobSrcCtrl.GetCurSel();
	m_iSrc2Ctrl = m_CobSrc2Ctrl.GetCurSel();
	CDialog::OnOK();
}
