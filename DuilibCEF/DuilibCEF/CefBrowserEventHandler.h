#ifndef _CEFBROWSEREVENTHANDLER_H_
#define _CEFBROWSEREVENTHANDLER_H_
#include "include/cef_client.h"  
#include "include/base/cef_lock.h" //�̰߳�ȫ


class CMainFrameWnd;

class CCefBrowserEventHandler
	: public CefClient
	, public CefDragHandler			    // ��ק�¼�
	, public CefDisplayHandler			// ��ʾ�仯�¼�
	, public CefLoadHandler			    // ���ش����¼�
	, public CefLifeSpanHandler		    // ���������¼�
{
public:
	CCefBrowserEventHandler(CMainFrameWnd* pMainFrame);

	virtual ~CCefBrowserEventHandler();

public:
	// CefClient �¼�������,���û�ж�Ӧ��������Ĭ��ʹ���ڲ�������
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
	//����CEF���ö��̼ܹ߳����б�Ҫʹ�����ͱհ�����֤�ڶ಻ͬ�̰߳�ȫ�Ĵ������ݡ�IMPLEMENT_LOCKING�����ṩ��Lock()��Unlock()�����Լ�AutoLock��������֤��ͬ�����ͬ������
	IMPLEMENT_LOCKING(CCefBrowserEventHandler);//�������#include "include/base/cef_lock.h" 
};

#endif//_CEFBROWSEREVENTHANDLER_H_