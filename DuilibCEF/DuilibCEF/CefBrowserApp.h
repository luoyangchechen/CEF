#ifndef _CEFBROWSERAPP_H_
#define _CEFBROWSERAPP_H_
#include "include/cef_app.h"

class CCefBrowserApp
	: public CefApp
	, public CefBrowserProcessHandler
{
public:
	CCefBrowserApp();

public:
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()OVERRIDE { return this; };

public:
	// CefBrowserProcessHandler methods:
	virtual void OnContextInitialized();

	// CefApp methods.
	virtual void OnBeforeCommandLineProcessing(
		const CefString& process_type,
		CefRefPtr<CefCommandLine> command_line) OVERRIDE;

protected:

	IMPLEMENT_REFCOUNTING(CCefBrowserApp);
};
#endif //_CEFBROWSERAPP_H_