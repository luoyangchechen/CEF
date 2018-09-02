#include "CefBrowserEventHandler.h"
//#include "stdafx.h"
#include <sstream>
#include <string>
#include "include/cef_app.h"
#include "include/wrapper/cef_closure_task.h"
#include "include/wrapper/cef_helpers.h"
#include "MainFrameWnd.h"


CCefBrowserEventHandler::CCefBrowserEventHandler(CMainFrameWnd* pMainFrame)
	:m_bIsClosing(false)
	,m_pMainWnd(pMainFrame)
{

}

CCefBrowserEventHandler::~CCefBrowserEventHandler()
{

}

CefRefPtr<CefDisplayHandler> CCefBrowserEventHandler::GetDisplayHandler()
{
	return this;
}

CefRefPtr<CefLifeSpanHandler> CCefBrowserEventHandler::GetLifeSpanHandler()
{
	return this;
}

CefRefPtr<CefLoadHandler> CCefBrowserEventHandler::GetLoadHandler() 
{
	return this;
}

void CCefBrowserEventHandler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) 
{
	
}

void CCefBrowserEventHandler::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, 
										  const CefString& errorText, const CefString& failedUrl) 
{
	CEF_REQUIRE_UI_THREAD();
	if (ERR_ABORTED == errorCode)
		return ;

	std::stringstream ss;
	ss <<	"<html><body bgcolor=\"white\">"
			"<h2>Failed to load URL " << std::string(failedUrl) <<
			" with error " << std::string(errorText) << " (" << errorCode <<
			").</h2></body></html>";
	frame->LoadString(ss.str(), failedUrl);
}

void CCefBrowserEventHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) 
{
	CEF_REQUIRE_UI_THREAD();

	//base::AutoLock lock_scope(lock_);

	AutoLock lock_scope(this);
	if (!m_Browser.get())
	{
		m_Browser = browser;
		m_BrowserId = browser->GetIdentifier();
	}
	 

}

bool CCefBrowserEventHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

	//base::AutoLock lock_scope(lock_);
	AutoLock lock_scope(this);


	if(m_BrowserId == browser->GetIdentifier()) 
	{
		// Set a flag to indicate that the window close should be allowed.
		m_bIsClosing = true;
	}

	return false;
}

void CCefBrowserEventHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) 
{
	CEF_REQUIRE_UI_THREAD();

	//base::AutoLock lock_scope(lock_);
	AutoLock lock_scope(this);

	if(m_BrowserId == browser->GetIdentifier())  
	{
		m_Browser = NULL;
	}
}

bool CCefBrowserEventHandler::OnDragEnter(CefRefPtr<CefBrowser> browser,
										  CefRefPtr<CefDragData> dragData,
										  CefDragHandler::DragOperationsMask mask) 
{
	CEF_REQUIRE_UI_THREAD();

	// Forbid dragging of link URLs.
	if (mask & DRAG_OPERATION_LINK)
		return true;

	return false;
}

bool CCefBrowserEventHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
									  CefProcessId source_process,
									  CefRefPtr<CefProcessMessage> message) 
{

	return false;
}

bool CCefBrowserEventHandler::OnBeforePopup(CefRefPtr<CefBrowser> browser,
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