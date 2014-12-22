// DlgRecord.cpp : implementation file
//

#include "stdafx.h"
#include "sp.h"
#include "DlgRecord.h"
#include "DJAcsDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRecord dialog


CDlgRecord::CDlgRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRecord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRecord)
	m_uiBR = 0;
	m_sFile = _T("");
	m_uiFps = 0;
	m_uiX = 0;
	m_uiY = 0;
	//}}AFX_DATA_INIT
}


void CDlgRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRecord)
	DDX_Control(pDX, IDC_CMB_TYPE, m_cmbType);
	DDX_Text(pDX, IDC_EDIT_BR, m_uiBR);
	DDX_Text(pDX, IDC_EDIT_FILE, m_sFile);
	DDX_Text(pDX, IDC_EDIT_FPS, m_uiFps);
	DDX_Text(pDX, IDC_EDIT_X, m_uiX);
	DDX_Text(pDX, IDC_EDIT_Y, m_uiY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRecord, CDialog)
	//{{AFX_MSG_MAP(CDlgRecord)
	ON_BN_CLICKED(IDC_BUTTON_FILE, OnButtonFile)
	ON_CBN_SELCHANGE(IDC_CMB_TYPE, OnSelchangeCmbType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRecord message handlers

BOOL CDlgRecord::OnInitDialog() 
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
	
	m_nRecType = 0;
	m_uiX = 176;
	m_uiY = 144;
	m_uiFps = 15;
	m_uiBR = 128;
	m_sFile.Format("C:\\DJKeygoe\\Samples\\Voc\\1.avi");
	UpdateData(FALSE);
	
	(CWnd*)GetDlgItem(IDC_EDIT_X)->EnableWindow(TRUE);
	(CWnd*)GetDlgItem(IDC_EDIT_Y)->EnableWindow(TRUE);
	(CWnd*)GetDlgItem(IDC_EDIT_FPS)->EnableWindow(TRUE);
	(CWnd*)GetDlgItem(IDC_EDIT_BR)->EnableWindow(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRecord::OnButtonFile() 
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

void CDlgRecord::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	
	m_nRecType = m_cmbType.GetCurSel();
	switch(m_nRecType)
	{
	case 0:
		m_nRecType = MEDIA_TYPE_AUDIO;
		break;
	case 1:
		m_nRecType = MEDIA_TYPE_VIDEO;
		break;
	case 2:
		m_nRecType = MEDIA_TYPE_ANV;
		break;
	case 3:
		m_nRecType = MEDIA_TYPE_MEDIAEX_AUDIO;
		break;
	case 4:
		m_nRecType = MEDIA_TYPE_MEDIAEX_VIDEO;
		break;
	case 5:
		m_nRecType = MEDIA_TYPE_MEDIAEX_ANV;
		break;
	default:
		m_nRecType = MEDIA_TYPE_MEDIAEX_ANV;
		break;
	}
	
	CDialog::OnOK();
}

void CDlgRecord::OnSelchangeCmbType() 
{
	// TODO: Add your control notification handler code here
	if(m_cmbType.GetCurSel() < 3)
	{
		(CWnd*)GetDlgItem(IDC_EDIT_X)->EnableWindow(FALSE);
		(CWnd*)GetDlgItem(IDC_EDIT_Y)->EnableWindow(FALSE);
		(CWnd*)GetDlgItem(IDC_EDIT_FPS)->EnableWindow(FALSE);
		(CWnd*)GetDlgItem(IDC_EDIT_BR)->EnableWindow(FALSE);
	}
	else
	{
		(CWnd*)GetDlgItem(IDC_EDIT_X)->EnableWindow(TRUE);
		(CWnd*)GetDlgItem(IDC_EDIT_Y)->EnableWindow(TRUE);
		(CWnd*)GetDlgItem(IDC_EDIT_FPS)->EnableWindow(TRUE);
		(CWnd*)GetDlgItem(IDC_EDIT_BR)->EnableWindow(TRUE);
	}
}
