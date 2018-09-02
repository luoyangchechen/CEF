#include "stdafx.h"
#include "CefBrowserEventHandler.h"
#include <sstream>
#include <string>
#include "include/base/cef_bind.h"
#include "include/views/cef_browser_view.h"
#include "include/views/cef_window.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"

CefBrowserEventHandler::CefBrowserEventHandler(void)
	:m_bIsClosing(false)
	,m_hParent(NULL)
{

}


CefBrowserEventHandler::~CefBrowserEventHandler(void)
{

}

CefRefPtr<CefDisplayHandler> CefBrowserEventHandler::GetDisplayHandler() 
{
	return this;
}

CefRefPtr<CefLifeSpanHandler> CefBrowserEventHandler::GetLifeSpanHandler()
{
	return this;
}

CefRefPtr<CefLoadHandler> CefBrowserEventHandler::GetLoadHandler()
{
	return this;
}


void CefBrowserEventHandler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, 
	const CefString& errorText, const CefString& failedUrl)
{
	CEF_REQUIRE_UI_THREAD();
	if (ERR_ABORTED == errorCode)
		return ;

	std::stringstream ss;
	ss << "<html><body bgcolor=\"white\">"
		"<h2>Failed to load URL " << std::string(failedUrl) <<
		" with error " << std::string(errorText) << " (" << errorCode <<
		").</h2></body></html>";
	frame->LoadString(ss.str(), failedUrl);
}

void CefBrowserEventHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	m_browser_list.push_back(browser);

	if (!m_Browser.get())
	{
		m_Browser = browser;
		m_BrowserId = browser->GetIdentifier();

		m_hParent = browser->GetHost()->GetWindowHandle();
	}
}

bool CefBrowserEventHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	if(m_BrowserId == browser->GetIdentifier()) 
	{
		// Set a flag to indicate that the window close should be allowed.
		m_bIsClosing = true;
	}
	return false;
}

void CefBrowserEventHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();
	if(m_BrowserId == browser->GetIdentifier())  
	{
		m_Browser = NULL;
	}
}

void CefBrowserEventHandler::CloseAllBrowser(bool force_close) 
{
	if (!CefCurrentlyOn(TID_UI)) 
	{
		CefPostTask(TID_UI,base::Bind(&CefBrowserEventHandler::CloseAllBrowser, this, force_close));
		return;
	}

	if (m_browser_list.empty())
		return;

	BrowserList::const_iterator it = m_browser_list.begin();
	for (; it != m_browser_list.end(); ++it)
	{
		(*it)->GetHost()->CloseBrowser(force_close);
	}
}

bool CefBrowserEventHandler::OnBeforePopup(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	const CefString& target_url,
	const CefString& target_frame_name,
	WindowOpenDisposition target_disposition,
	bool user_gesture,
	const CefPopupFeatures& popupFeatures,
	CefWindowInfo& windowInfo,
	CefRefPtr<CefClient>& client,
	CefBrowserSettings& settings,
	bool* no_javascript_access)
{
	switch (target_disposition)
	{
	case WOD_NEW_FOREGROUND_TAB:
	case WOD_NEW_BACKGROUND_TAB:
	case WOD_NEW_POPUP:
	case WOD_NEW_WINDOW:
		browser->GetMainFrame()->LoadURL(target_url);
		return true; //cancel create
	}
	return false;
}

void CefBrowserEventHandler::OnFullscreenModeChange(CefRefPtr<CefBrowser> browser, bool fullscreen)
{
	static RECT preWinRect = {0};

	//The parent window of the inner browser
	if (m_hParent == NULL)
	{
		return;
	}

	if (fullscreen)
	{
		//Title bar height
		int nHeadHeight = 34; 
		//The number of px between parent window and inner browser
		int nOffset = 1; 
		int nW = GetSystemMetrics(SM_CXSCREEN);
		int nH = GetSystemMetrics(SM_CYSCREEN);
		//Store the rectangle of old window
		::GetWindowRect(m_hParent, &preWinRect); 
		::SetWindowPos(m_hParent, HWND_TOPMOST, 0, -nHeadHeight, nW, nH + nHeadHeight + nOffset, SWP_NOACTIVATE | SWP_NOSENDCHANGING);
	}
	else
	{
		int nW = preWinRect.right - preWinRect.left;
		int nH = preWinRect.bottom - preWinRect.top;
		int nX = preWinRect.left;
		int nY = preWinRect.top;

		if (nW <= 0 || nH <= 0)
		{
			return;
		}

		::SetWindowPos(m_hParent, HWND_NOTOPMOST, nX, nY, nW, nH, SWP_NOACTIVATE);
	}

	return;
}