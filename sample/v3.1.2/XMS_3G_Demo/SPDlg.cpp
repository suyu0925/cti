// SPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SP.h"
#include "SPDlg.h"

#include <DJAcsApiDef.h>
#include "SPKeygoe.h"

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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSPDlg dialog

CSPDlg::CSPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSPDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSPDlg)
	DDX_Control(pDX, IDC_LIST_MEMBER, m_ListMember);
	DDX_Control(pDX, IDC_LIST_HOTCONF, m_ListHotConf);
	DDX_Control(pDX, IDC_LIST_DEV_INFO, m_ListDevInfo);
	DDX_Control(pDX, IDC_LIST_DEV_TYPE, m_ListDevType);
	DDX_Control(pDX, IDC_LIST_MSG, m_ListMsg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSPDlg, CDialog)
	//{{AFX_MSG_MAP(CSPDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_LIST_DEV_TYPE, OnClickListDevType)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_DEV_INFO, OnDblclkListDevInfo)
	ON_BN_CLICKED(IDC_BUTTON_OPENALL, OnButtonOpenall)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEALL, OnButtonCloseall)
	ON_BN_CLICKED(IDC_BUTTON_SETPARAM, OnButtonSetparam)
	ON_BN_CLICKED(IDC_BUTTON_CLEARCALL, OnButtonClearcall)
	ON_BN_CLICKED(IDC_BUTTON_IODATA, OnButtonIOData)
	ON_BN_CLICKED(IDC_BUTTON_CALL, OnButtonCall)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_RECORD, OnButtonRecord)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_LINK, OnButtonLink)
	ON_BN_CLICKED(IDC_BUTTON_UNLINK, OnButtonUnlink)
	ON_BN_CLICKED(IDC_BUTTON_RESET, OnButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonInit)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_LIST_HOTCONF, OnClickListHotconf)
	ON_BN_CLICKED(IDC_BUTTON_STOPREC, OnButtonStoprec)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_DEV_INFO, OnRclickListDevInfo)
	ON_COMMAND(IDR_MENU_MAIN_JOIN, OnMenuMainJoin)
	ON_COMMAND(IDR_MENU_MAIN_LEAVE, OnMenuMainLeave)
	ON_COMMAND(IDR_MENU_MAIN_PLAY, OnMenuMainPlay)
	ON_COMMAND(IDR_MENU_MAIN_RECORD, OnMenuMainRecord)
	ON_COMMAND(IDR_MENU_MAIN_RESTART, OnMenuMainRestart)
	ON_COMMAND(IDR_MENU_MAIN_SETLAYOUT, OnMenuMainSetlayout)
	ON_COMMAND(IDR_MENU_MAIN_SETVISIBLELIST, OnMenuMainSetvisiblelist)
	ON_COMMAND(IDR_MENU_MAIN_CLEAR, OnMenuMainClear)
	ON_COMMAND(IDR_MENU_MAIN_GETLAYOUT, OnMenuMainGetlayout)
	ON_COMMAND(IDR_MENU_MAIN_GETVISIBLELIST, OnMenuMainGetvisiblelist)
	ON_WM_TIMER()
	ON_COMMAND(IDR_MENU_MAIN_STARTTIMER, OnMenuMainStarttimer)
	ON_COMMAND(IDR_MENU_MAIN_STOPTIMER, OnMenuMainStoptimer)
	ON_BN_CLICKED(IDC_BUTTON_GETFILEINFO, OnButtonGetfileinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSPDlg message handlers

BOOL CSPDlg::OnInitDialog()
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
	InitSystem();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSPDlg::OnPaint() 
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
HCURSOR CSPDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSPDlg::OnClickListDevType(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString itemText;
	POSITION pos = m_ListDevType.GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
		int nItem = m_ListDevType.GetNextSelectedItem(pos);
		itemText = m_ListDevType.GetItemText(nItem, 0);
		DisplayDevInfo(atoi(itemText));
	}
	*pResult = 0;
}

void CSPDlg::OnDblclkListDevInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnOpenDevice();
	
	*pResult = 0;
}

void CSPDlg::OnButtonOpenall() 
{
	// TODO: Add your control notification handler code here
	OnOpenAllDevice();
}

void CSPDlg::OnButtonCloseall() 
{
	// TODO: Add your control notification handler code here
	OnCloseAllDevice();
}

void CSPDlg::OnButtonSetparam() 
{
	// TODO: Add your control notification handler code here
	OnSetParam(GetSelectDev());
}

void CSPDlg::OnButtonClearcall() 
{
	// TODO: Add your control notification handler code here
	OnClearCall(GetSelectDev());
}

void CSPDlg::OnButtonIOData() 
{
	// TODO: Add your control notification handler code here
	OnSendIOData(GetSelectDev());
}

void CSPDlg::OnButtonCall() 
{
	// TODO: Add your control notification handler code here
	OnCall(GetSelectDev());
}

void CSPDlg::OnButtonPlay() 
{
	// TODO: Add your control notification handler code here
	OnPlay(GetSelectDev());
}

void CSPDlg::OnButtonRecord() 
{
	// TODO: Add your control notification handler code here
	OnRecord(GetSelectDev());
}

void CSPDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	OnStopPlay(GetSelectDev());
}

void CSPDlg::OnButtonLink() 
{
	// TODO: Add your control notification handler code here
	OnLinkDev(GetSelectDev());
}

void CSPDlg::OnButtonUnlink() 
{
	// TODO: Add your control notification handler code here
	OnUnlinkDev(GetSelectDev());
}

void CSPDlg::OnButtonReset() 
{
	// TODO: Add your control notification handler code here
	OnResetDev(GetSelectDev());
}

void CSPDlg::OnButtonInit() 
{
	// TODO: Add your control notification handler code here
	ExitSystem();
	Sleep(2000);
	InitSystem();
}

void CSPDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	ExitSystem();
	
	CDialog::OnClose();
}

void CSPDlg::OnOK() 
{
	// TODO: Add extra validation here
	ExitSystem();

	CDialog::OnOK();
}

void CSPDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	ExitSystem();

	CDialog::OnCancel();
}

void CSPDlg::OnClickListHotconf(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString itemText;
	POSITION pos = m_ListHotConf.GetFirstSelectedItemPosition();
	if(pos != NULL)
	{
		int nItem = m_ListHotConf.GetNextSelectedItem(pos);
		itemText = m_ListHotConf.GetItemText(nItem, 0);
		DisplayConfInfo(atoi(itemText));
	}

	*pResult = 0;
}

void CSPDlg::OnButtonStoprec() 
{
	// TODO: Add your control notification handler code here
	OnStopRecord(GetSelectDev());
}

void CSPDlg::OnRclickListDevInfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	DeviceID_t* pDev = GetSelectDev();
	if(pDev != NULL && pDev->m_s16DeviceMain == XMS_DEVMAIN_VIDEOCONF)
	{
		CMenu menu;
		if(menu.LoadMenu(IDR_MENU_MAIN))
		{
			CMenu *pPopupMenu = menu.GetSubMenu(0);

			CPoint curPoint;
			GetCursorPos(&curPoint);
			pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, 
				curPoint.x, curPoint.y, this);
		}
	}
	
	*pResult = 0;
}

void CSPDlg::OnMenuMainJoin() 
{
	// TODO: Add your command handler code here
	OnJoinConf(GetSelectDev());
}

void CSPDlg::OnMenuMainLeave() 
{
	// TODO: Add your command handler code here
	OnLeaveConf(GetSelectDev());
}

void CSPDlg::OnMenuMainPlay() 
{
	// TODO: Add your command handler code here
	OnPlayConf(GetSelectDev());
}

void CSPDlg::OnMenuMainRecord() 
{
	// TODO: Add your command handler code here
	OnRecordConf(GetSelectDev());
}

void CSPDlg::OnMenuMainRestart() 
{
	// TODO: Add your command handler code here
	OnRestartConf(GetSelectDev());
}

void CSPDlg::OnMenuMainSetlayout() 
{
	// TODO: Add your command handler code here
	OnSetLayout(GetSelectDev());
}

void CSPDlg::OnMenuMainSetvisiblelist() 
{
	// TODO: Add your command handler code here
	OnSetVisibleList(GetSelectDev());
}

void CSPDlg::OnMenuMainClear() 
{
	// TODO: Add your command handler code here
	OnClearConf(GetSelectDev());
}

void CSPDlg::OnMenuMainGetlayout() 
{
	// TODO: Add your command handler code here
	OnGetLayout(GetSelectDev());
}

void CSPDlg::OnMenuMainGetvisiblelist() 
{
	// TODO: Add your command handler code here
	OnGetVisibleList(GetSelectDev());
}

#define TIMER_FOR_TEST3GVCONF 12345

void CSPDlg::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == TIMER_FOR_TEST3GVCONF)
	{
		KillTimer(TIMER_FOR_TEST3GVCONF);
		OnTimerFor3GVConf();
		SetTimer(TIMER_FOR_TEST3GVCONF, 10000, NULL);
	}

	CDialog::OnTimer(nIDEvent);
}

void CSPDlg::OnMenuMainStarttimer() 
{
	// TODO: Add your command handler code here
	srand(100);
	SetTimer(TIMER_FOR_TEST3GVCONF, 10000, NULL);

	SetWindowText("DonJin Keygoe 3G Demo - test 3GVConf timer running");
}

void CSPDlg::OnMenuMainStoptimer() 
{
	// TODO: Add your command handler code here
	KillTimer(TIMER_FOR_TEST3GVCONF);
	SetWindowText("DonJin Keygoe 3G Demo");
}

void CSPDlg::OnButtonGetfileinfo() 
{
	// TODO: Add your control notification handler code here
    OnGetFileInfo(GetSelectDev());
}
