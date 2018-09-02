#ifndef _CEFBROWSEREVENTHANDLER_H_
#define _CEFBROWSEREVENTHANDLER_H_
#include "include/cef_client.h"

#include <list>

class CefBrowserEventHandler : public CefClient,
	public CefDisplayHandler,
	public CefLifeSpanHandler,
	public CefLoadHandler {
public:
	CefBrowserEventHandler(void);
	~CefBrowserEventHandler(void);

public:
	// CefClient 事件处理器,如果没有对应处理器则默认使用内部处理器
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE;
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE;
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE;

public:
	// load handler method
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) OVERRIDE;

public:
	// display handler meethod
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& target_url,
		const CefString& target_frame_name,
		WindowOpenDisposition target_disposition,
		bool user_gesture,
		const CefPopupFeatures& popupFeatures,
		CefWindowInfo& windowInfo,
		CefRefPtr<CefClient>& client,
		CefBrowserSettings& settings,
		bool* no_javascript_access) OVERRIDE;

	virtual void OnFullscreenModeChange(CefRefPtr<CefBrowser> browser, bool fullscreen) OVERRIDE;
public:
	// own method of cef browser event handler
	void CloseAllBrowser(bool bForceClose = true);

	CefRefPtr<CefBrowser> GetBrowser(){return m_Browser;} 
protected:
	typedef std::list<CefRefPtr<CefBrowser> > BrowserList;
	BrowserList  m_browser_list;
	CefRefPtr<CefBrowser> m_Browser;
	int m_BrowserId;

	bool m_bIsClosing;


	HWND m_hParent;
	IMPLEMENT_REFCOUNTING(CefBrowserEventHandler);

};

#endif//_CEFBROWSEREVENTHANDLER_H_