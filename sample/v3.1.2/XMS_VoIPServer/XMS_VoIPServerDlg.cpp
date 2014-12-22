// XMS_VoIPServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XMS_VoIPServer.h"
#include "XMS_VoIPServerDlg.h"
#include <winsock2.h>
#include "EventHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMS_VoIPServerDlg dialog

CXMS_VoIPServerDlg::CXMS_VoIPServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXMS_VoIPServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXMS_VoIPServerDlg)
	m_strAddress = _T("192.168.10.53");
	m_nAppID = 6;
	m_nPort = 9000;
	m_strUserName = _T("");
	m_strPassword = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	GetModuleFileName(NULL, m_strIniFile.GetBuffer(_MAX_PATH), _MAX_PATH);
	m_strIniFile.ReleaseBuffer();
	m_strIniFile.Replace(_T(".exe"), _T(".ini"));

	loadConfig();
}
void CXMS_VoIPServerDlg::loadConfig()
{
	GetPrivateProfileString(_T("Server"), _T("IP"), _T(""), m_strAddress.GetBuffer(100), 100, m_strIniFile);
	m_strAddress.ReleaseBuffer();

	if (m_strAddress.IsEmpty())
	{
		// get local host ip
		char hostname[256] = {0};
		if (gethostname(hostname, sizeof(hostname)) == 0)
		{
			HOSTENT *he	= gethostbyname(hostname);

			if (he != NULL)
			{
				m_strAddress = inet_ntoa(*((struct in_addr *)he->h_addr_list[0]));
			}
		}
	}

	m_nPort = GetPrivateProfileInt(_T("Server"), _T("Port"), 9000, m_strIniFile);
	GetPrivateProfileString(_T("Server"), _T("Username"), _T(""), m_strUserName.GetBuffer(100), 100, m_strIniFile);
	m_strUserName.ReleaseBuffer();
	GetPrivateProfileString(_T("Server"), _T("Password"), _T(""), m_strPassword.GetBuffer(100), 100, m_strIniFile);
	m_strPassword.ReleaseBuffer();
}

void CXMS_VoIPServerDlg::saveConfig()
{
	UpdateData();

	WritePrivateProfileString(_T("Server"), _T("IP"), m_strAddress, m_strIniFile);
	CString strbuf;
	strbuf.Format(_T("%d"), m_nPort);
	WritePrivateProfileString(_T("Server"), _T("Port"), strbuf, m_strIniFile);
	WritePrivateProfileString(_T("Server"), _T("Username"), m_strUserName, m_strIniFile);
	WritePrivateProfileString(_T("Server"), _T("Password"), m_strPassword, m_strIniFile);
}

void CXMS_VoIPServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXMS_VoIPServerDlg)
	DDX_Control(pDX, IDC_LIST_EVENT, m_tListEvent);
	DDX_Control(pDX, IDC_LIST_USER, m_tListUser);
	DDX_Control(pDX, IDC_LIST_DEVICE, m_tListDevice);
	DDX_Control(pDX, IDC_LIST_CALL, m_tListCall);
	DDX_Text(pDX, IDC_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_APP_ID, m_nAppID);
	DDX_Text(pDX, IDC_PORT, m_nPort);
	DDX_Text(pDX, IDC_USERNAME, m_strUserName);
	DDX_Text(pDX, IDC_PASSWORD, m_strPassword);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXMS_VoIPServerDlg, CDialog)
	//{{AFX_MSG_MAP(CXMS_VoIPServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_INIT, OnBtnInit)
	ON_BN_CLICKED(IDC_BTN_CLEAR_LOG, OnBtnClearLog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXMS_VoIPServerDlg message handlers

BOOL CXMS_VoIPServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	// Init Log
	CDJLog* pLog	= CDJLog::GetLog();
	pLog->m_tCall	= &m_tListCall;
	pLog->m_tDevice	= &m_tListDevice;
	pLog->m_tEvent	= &m_tListEvent;
	pLog->m_tUser	= &m_tListUser;
	// Init UI
	InitUI();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CXMS_VoIPServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXMS_VoIPServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXMS_VoIPServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXMS_VoIPServerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
//	CDJApp::GetApp()->m_xms.CloseSystem();	
}

void CXMS_VoIPServerDlg::InitUI()
{
	// call
	m_tListCall.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_tListCall.InsertColumn(0, _T("#"), LVCFMT_CENTER, 40);
	m_tListCall.InsertColumn(1, _T("Caller"), LVCFMT_LEFT, 120);
	m_tListCall.InsertColumn(2, _T("Callee"), LVCFMT_CENTER, 120);
	m_tListCall.InsertColumn(3, _T("State"), LVCFMT_CENTER, 120);
//	djPrint(DJ_PORT_CALL, 1, 3, "Caller", "Callee", "State");
	// Device
	m_tListDevice.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_tListDevice.InsertColumn(0, _T("#"), LVCFMT_CENTER, 40);
	m_tListDevice.InsertColumn(1, _T("Type"), LVCFMT_LEFT, 60);
	m_tListDevice.InsertColumn(2, _T("sum"), LVCFMT_CENTER, 30);
	m_tListDevice.InsertColumn(3, _T("opened"), LVCFMT_CENTER, 60);
	m_tListDevice.InsertColumn(4, _T("used"), LVCFMT_CENTER, 60);
//	djPrint(DJ_PORT_DEVICE, 1, 4, "Type", "sum", "opened", "used");
	// User
	m_tListUser.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_tListUser.InsertColumn(0, _T("#"), LVCFMT_CENTER, 40);
	m_tListUser.InsertColumn(1, _T("TelNo"), LVCFMT_CENTER, 80);
	m_tListUser.InsertColumn(2, _T("UserID"), LVCFMT_CENTER, 80);
	m_tListUser.InsertColumn(3, _T("Address"), LVCFMT_CENTER, 120);
	m_tListUser.InsertColumn(4, _T("State"), LVCFMT_CENTER, 80);
//	djPrint(DJ_PORT_USER, 1, 4, "Protocol", "TelNo", "Address", "UserID");

	// Event
	m_tListEvent.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_tListEvent.InsertColumn(0, _T("#"), LVCFMT_CENTER, 40);
	m_tListEvent.InsertColumn(1, _T("Type"), LVCFMT_LEFT, 100);
	m_tListEvent.InsertColumn(2, _T("Message"), LVCFMT_LEFT, 600);
//	djPrint(DJ_LEVEL_LOG, "%s %s %s %s", "AAAA", "BBBB", "CCCC", "DDDD");
}

void CXMS_VoIPServerDlg::OnBtnInit() 
{
    UpdateData();
    // init app
    CDJApp::GetApp()->Init(m_nAppID, m_strAddress, m_nPort, m_strUserName, m_strPassword);
}
 

void CXMS_VoIPServerDlg::OnBtnClearLog() 
{
    m_tListEvent.DeleteAllItems();
}
