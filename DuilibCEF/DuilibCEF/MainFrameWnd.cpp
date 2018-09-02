#include "CefBrowserEventHandler.h"
#include "MainFrameWnd.h"

CefRefPtr<CCefBrowserEventHandler> m_handler = NULL;

CMainFrameWnd::CMainFrameWnd()
{

}

CMainFrameWnd::~CMainFrameWnd()
{
	
}

LPCTSTR CMainFrameWnd::GetWindowClassName() const
{
	return _T("MainFrameWnd");
}

void CMainFrameWnd::OnFinalMessage(HWND hWnd)
{
	CWindowWnd::OnFinalMessage(hWnd);
}


UILIB_RESOURCETYPE CMainFrameWnd::GetResourceType() const
{
	return UILIB_FILE;
}

LRESULT CMainFrameWnd::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return FALSE;
}

CDuiString CMainFrameWnd::GetSkinFile()
{
	return _T("MainDlg.xml");
}

CDuiString CMainFrameWnd::GetSkinFolder()
{
	return _T("");
}

CControlUI* CMainFrameWnd::CreateControl(LPCTSTR pstrClass)
{
	
	return NULL;
}

void CMainFrameWnd::OnPrepare()
{

}

void CMainFrameWnd::InitWindow()
{
	m_handler = new CCefBrowserEventHandler(this);

	RECT rc;
	::GetClientRect(this->GetHWND(),&rc);

	rc.top    += 28;
	rc.left   += 1;
	rc.right  += -1;
	rc.bottom += -1;

	CefWindowInfo info;  
	info.SetAsChild(*this, rc);

	TCHAR tszModule[MAX_PATH + 1] = { 0 };
	::GetModuleFileName(NULL, tszModule, MAX_PATH); 
	::PathRemoveFileSpec(tszModule);

	wstring url =tszModule;
	url+=L"\\mp4.html";
	//url+=L"\\test.html";

	CefBrowserSettings settings1;  
	//CefBrowserHost::CreateBrowser(info, m_handler.get(), CefString ("http://www.baidu.com"), settings1, NULL);  
	CefBrowserHost::CreateBrowser(info, m_handler.get(), CefString (url), settings1, NULL);  
}


void CMainFrameWnd::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("windowinit") ) OnPrepare();

	if(msg.sType == _T("click"))
	{
		if (msg.pSender->GetName() == _T("backbtn"))
		{
			m_handler->GetBrowser()->GoBack();
		}
	}

	WindowImplBase::Notify(msg);
}

void CMainFrameWnd::OnClick(TNotifyUI& msg)
{
	__super::OnClick(msg);
}


LRESULT CMainFrameWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	if (m_handler && !m_handler->IsClosing()) {
		CefRefPtr<CefBrowser> browser = m_handler->GetBrowser();
		if (browser.get()) {
			// Notify the browser window that we would like to close it. This
			// will result in a call to ClientHandler::DoClose() if the
			// JavaScript 'onbeforeunload' event handler allows it.
			browser->GetHost()->CloseBrowser(false);

			// Cancel the close.
			return 0;
		}
	}
	//::PostQuitMessage(1L);
	//return __super::OnClose(uMsg, wParam, lParam, bHandled);
	DestroyWindow(m_hWnd);
	return 0;
}

LRESULT CMainFrameWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	WindowImplBase::OnSize(uMsg,wParam,lParam,bHandled);

	if (m_handler != NULL){  
		CefRefPtr<CefBrowser> browser = m_handler->GetBrowser();  
		if (browser){  
			CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle(); 

			RECT rt;
			::GetClientRect(m_hWnd, &rt);

			int cx = rt.right - rt.left -2;

			int cy = rt.bottom - rt.top -30;

			::MoveWindow(hwnd, 1, 28, cx, cy, TRUE);  
		}  
	} 


	return 0;
}

 LRESULT CMainFrameWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
 {
	 //bHandled = FALSE;
	 PostQuitMessage(0);
	 return 0;
 }

//禁用双击标题栏窗口最大化
LRESULT CMainFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch( uMsg)
	{
	case WM_NCLBUTTONDBLCLK:
		{
			return 0;
		}
		break;
	case WM_SIZE:
		lRes = OnSize(uMsg,wParam,lParam,bHandled);
		break;
	default:
		bHandled = FALSE;
	}
	return WindowImplBase::HandleMessage(uMsg,wParam,lParam);
}

