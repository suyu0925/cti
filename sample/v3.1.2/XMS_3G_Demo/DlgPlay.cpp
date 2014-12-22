// DlgPlay.cpp : implementation file
//

#include "stdafx.h"
#include "sp.h"
#include "DlgPlay.h"
#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPlay dialog


CDlgPlay::CDlgPlay(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPlay)
	m_uiTime = 0;
	m_uiFps = 0;
	m_uiBr = 0;
	m_uiX = 0;
	m_uiY = 0;
	m_sFile = _T("");
	m_sFileOverlay = _T("");
	m_bLoop = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgPlay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPlay)
	DDX_Control(pDX, IDC_CMB_TYPE, m_cmbType);
	DDX_Text(pDX, IDC_EDIT_TIME, m_uiTime);
	DDX_Text(pDX, IDC_EDIT_FPS, m_uiFps);
	DDX_Text(pDX, IDC_EDIT_BR, m_uiBr);
	DDX_Text(pDX, IDC_EDIT_X, m_uiX);
	DDX_Text(pDX, IDC_EDIT_Y, m_uiY);
	DDX_Text(pDX, IDC_EDIT_FILE, m_sFile);
	DDX_Text(pDX, IDC_EDIT_FILEOVERLAY, m_sFileOverlay);
	DDX_Check(pDX, IDC_CHK_LOOP, m_bLoop);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPlay, CDialog)
	//{{AFX_MSG_MAP(CDlgPlay)
	ON_BN_CLICKED(IDC_BUTTON_FILE, OnButtonFile)
	ON_BN_CLICKED(IDC_BUTTON_FILEOVERLAY, OnButtonFileoverlay)
	ON_CBN_SELCHANGE(IDC_CMB_TYPE, OnSelchangeCmbType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPlay message handlers

BOOL CDlgPlay::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cmbType.InsertString(0, "MEDIA AUDIO");
	m_cmbType.InsertString(1, "MEDIA VIDEO");
	m_cmbType.InsertString(2, "MEDIA ANV");
	m_cmbType.InsertString(3, "MEDIAEX AUDIO");
	m_cmbType.InsertString(4, "MEDIAEX VIDEO");
	m_cmbType.InsertString(5, "MEDIAEX ANV");
	m_cmbType.SetCurSel(5);
	
	m_nPlayType = 0;
	m_uiTime = 1000000;
	m_uiX = 176;
	m_uiY = 144;
	m_uiFps = 10;
	m_uiBr = 40;
	m_sFile.Format("C:\\DJKeygoe\\Samples\\Voc\\advertisement(QCIF-46K-H263-12K-AMR).3gp");
	UpdateData(FALSE);
	
	(CWnd*)GetDlgItem(IDC_EDIT_FILEOVERLAY)->EnableWindow(TRUE);
	(CWnd*)GetDlgItem(IDC_BUTTON_FILEOVERLAY)->EnableWindow(TRUE);
	(CWnd*)GetDlgItem(IDC_CHK_LOOP)->EnableWindow(TRUE);
	(CWnd*)GetDlgItem(IDC_EDIT_X)->EnableWindow(TRUE);
	(CWnd*)GetDlgItem(IDC_EDIT_Y)->EnableWindow(TRUE);
	(CWnd*)GetDlgItem(IDC_EDIT_FPS)->EnableWindow(TRUE);
	(CWnd*)GetDlgItem(IDC_EDIT_BR)->EnableWindow(TRUE);
	(CWnd*)GetDlgItem(IDC_EDIT_TIME)->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPlay::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	
	m_nPlayType = m_cmbType.GetCurSel();
	switch(m_nPlayType)
	{
	case 0:
		m_nPlayType = MEDIA_TYPE_AUDIO;
		break;
	case 1:
		m_nPlayType = MEDIA_TYPE_VIDEO;
		break;
	case 2:
		m_nPlayType = MEDIA_TYPE_ANV;
		break;
	case 3:
		m_nPlayType = MEDIA_TYPE_MEDIAEX_AUDIO;
		break;
	case 4:
		m_nPlayType = MEDIA_TYPE_MEDIAEX_VIDEO;
		break;
	case 5:
		m_nPlayType = MEDIA_TYPE_MEDIAEX_ANV;
		break;
	default:
		m_nPlayType = MEDIA_TYPE_MEDIAEX_ANV;
		break;
	}

	CDialog::OnOK();
}

void CDlgPlay::OnButtonFile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog filedlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,     
		"All files(*.*)|*.*||", NULL); 
	
	if(filedlg.DoModal() == IDOK)
	{
		UpdateData(TRUE);
		m_sFile.Format("%s", filedlg.GetPathName());
		UpdateData(FALSE);
	}
}

void CDlgPlay::OnButtonFileoverlay() 
{
	// TODO: Add your control notification handler code here
	CFileDialog filedlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,     
		"All files(*.*)|*.*||", NULL); 
	
	if(filedlg.DoModal() == IDOK)
	{
		UpdateData(TRUE);
		m_sFileOverlay.Format("%s", filedlg.GetPathName());
		UpdateData(FALSE);
	}
}

void CDlgPlay::OnSelchangeCmbType() 
{
	// TODO: Add your control notification handler code here
	if(m_cmbType.GetCurSel() < 3)
	{
		(CWnd*)GetDlgItem(IDC_EDIT_TIME)->EnableWindow(TRUE);
		(CWnd*)GetDlgItem(IDC_EDIT_FILEOVERLAY)->EnableWindow(FALSE);
		(CWnd*)GetDlgItem(IDC_BUTTON_FILEOVERLAY)->EnableWindow(FALSE);
		(CWnd*)GetDlgItem(IDC_CHK_LOOP)->EnableWindow(FALSE);
		(CWnd*)GetDlgItem(IDC_EDIT_X)->EnableWindow(FALSE);
		(CWnd*)GetDlgItem(IDC_EDIT_Y)->EnableWindow(FALSE);
		(CWnd*)GetDlgItem(IDC_EDIT_FPS)->EnableWindow(FALSE);
		(CWnd*)GetDlgItem(IDC_EDIT_BR)->EnableWindow(FALSE);
	}
	else
	{
		(CWnd*)GetDlgItem(IDC_EDIT_FILEOVERLAY)->EnableWindow(TRUE);
		(CWnd*)GetDlgItem(IDC_BUTTON_FILEOVERLAY)->EnableWindow(TRUE);
		(CWnd*)GetDlgItem(IDC_CHK_LOOP)->EnableWindow(TRUE);
		(CWnd*)GetDlgItem(IDC_EDIT_X)->EnableWindow(TRUE);
		(CWnd*)GetDlgItem(IDC_EDIT_Y)->EnableWindow(TRUE);
		(CWnd*)GetDlgItem(IDC_EDIT_FPS)->EnableWindow(TRUE);
		(CWnd*)GetDlgItem(IDC_EDIT_BR)->EnableWindow(TRUE);
		(CWnd*)GetDlgItem(IDC_EDIT_TIME)->EnableWindow(FALSE);
	}
}
