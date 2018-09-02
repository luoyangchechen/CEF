
// MFCFlashDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCFlashDemo.h"
#include "MFCFlashDemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCFlashDemoDlg dialog




CMFCFlashDemoDlg::CMFCFlashDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCFlashDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCFlashDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCFlashDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CMFCFlashDemoDlg::OnBnClickedBtnSearch)
	ON_BN_CLICKED(IDC_BTN_GOFORD, &CMFCFlashDemoDlg::OnBnClickedBtnGoford)
	ON_BN_CLICKED(IDC_BTN_GOBACK, &CMFCFlashDemoDlg::OnBnClickedBtnGoback)
	ON_WM_CLOSE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMFCFlashDemoDlg message handlers

BOOL CMFCFlashDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//开始创建浏览器
	CRect rtBody;

	GetWindowRect(&rtBody);

	RECT rect;
	GetClientRect(&rect);
	RECT rectnew = rect;
	rectnew.top = rect.top + 50;
	rectnew.bottom = rect.bottom;
	rectnew.left = rect.left;
	rectnew.right = rect.right;

	TCHAR tszModule[MAX_PATH + 1] = { 0 };
	::GetModuleFileName(NULL, tszModule, MAX_PATH); 
	::PathRemoveFileSpec(tszModule);

	CString url =tszModule;
	url+=_T("\\mp4.html");


	CefWindowInfo cefWindowInfo;

	cefWindowInfo.SetAsChild(GetSafeHwnd(), rectnew);

	CefBrowserSettings browserSetting;

	CefRefPtr<CefBrowserEventHandler> client(new CefBrowserEventHandler());

	m_simpleClient = client;

	//CefBrowserHost::CreateBrowser(cefWindowInfo, client.get(), CefString (url), browserSetting, NULL); 
	CefBrowserHost::CreateBrowser(cefWindowInfo, client.get(), _T("http://www.baidu.com"), browserSetting, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCFlashDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCFlashDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCFlashDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*
	Search按钮
*/
void CMFCFlashDemoDlg::OnBnClickedBtnSearch()
{
	// TODO: Add your control notification handler code here
	CString strUrl;
	GetDlgItem(IDC_EDIT_URL)->GetWindowText(strUrl);
	if (strUrl.Trim().IsEmpty())
	{
		AfxMessageBox(_T("请输入网址"));
		return;
	}
	const CefString cefStrUrl(strUrl);
	m_simpleClient->GetBrowser()->GetMainFrame()->LoadURL(cefStrUrl);
}

/*
	前进按钮
*/
void CMFCFlashDemoDlg::OnBnClickedBtnGoford()
{
	// TODO: Add your control notification handler code here
	m_simpleClient->GetBrowser()->GoBack();
}

/*
	后退按钮
*/
void CMFCFlashDemoDlg::OnBnClickedBtnGoback()
{
	// TODO: Add your control notification handler code here
	m_simpleClient->GetBrowser()->GoBack();
}


void CMFCFlashDemoDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	CefShutdown();

	CDialogEx::OnClose();
}


void CMFCFlashDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	RECT rect;
	GetClientRect(&rect);

	if (m_simpleClient.get())
	{
		CefRefPtr<CefBrowser> browser = m_simpleClient->GetBrowser();
		if (browser)
		{
			CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
			::MoveWindow(hwnd, 0, 50, rect.right - rect.left, rect.bottom - 50, true);
		}
	}
}

/*
	响应回车键
*/
BOOL CMFCFlashDemoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:    // 屏蔽回车
			OnBnClickedBtnSearch();
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}