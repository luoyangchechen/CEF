#ifndef _CEFBROWSEREVENTHANDLER_H_
#define _CEFBROWSEREVENTHANDLER_H_
#include "include/cef_client.h"  
#include "include/base/cef_lock.h" //线程安全


class CMainFrameWnd;

class CCefBrowserEventHandler
	: public CefClient
	, public CefDragHandler			    // 拖拽事件
	, public CefDisplayHandler			// 显示变化事件
	, public CefLoadHandler			    // 加载错误事件
	, public CefLifeSpanHandler		    // 声明周期事件
{
public:
	CCefBrowserEventHandler(CMainFrameWnd* pMainFrame);

	virtual ~CCefBrowserEventHandler();

public:
	// CefClient 事件处理器,如果没有对应处理器则默认使用内部处理器
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE;
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE;
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE;
	virtual CefRefPtr<CefDragHandler> GetDragHandler() OVERRIDE {
		return this;
	}

public:	
	// display handler method
	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title) OVERRIDE;

public:
	// load handler method
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, 
		ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) OVERRIDE;

	// CefDragHandler methods
	virtual bool OnDragEnter(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefDragData> dragData,
		CefDragHandler::DragOperationsMask mask) OVERRIDE;

public:
	// display handler meethod
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	//CefLifeSpanHandler
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


	virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
		CefProcessId source_process,
		CefRefPtr<CefProcessMessage> message);


	bool IsClosing() const { return m_bIsClosing; }

	CefRefPtr<CefBrowser> GetBrowser(){return m_Browser;} 

protected:

	CefRefPtr<CefBrowser> m_Browser; 

	int m_BrowserId;

	bool m_bIsClosing;

	CMainFrameWnd* 	 m_pMainWnd;

	IMPLEMENT_REFCOUNTING(CCefBrowserEventHandler);
	//由于CEF采用多线程架构，有必要使用锁和闭包来保证在多不同线程安全的传递数据。IMPLEMENT_LOCKING定义提供了Lock()和Unlock()方法以及AutoLock对象来保证不同代码块同步访问
	IMPLEMENT_LOCKING(CCefBrowserEventHandler);//必须包含#include "include/base/cef_lock.h" 
};

#endif//_CEFBROWSEREVENTHANDLER_H_