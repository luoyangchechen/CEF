// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef _CEFCLIENTAPP_H_
#define _CEFCLIENTAPP_H_

#include "include/cef_app.h"


class ClientApp : public CefApp,
                  public CefBrowserProcessHandler,
                  public CefRenderProcessHandler {
public:
 
  ClientApp();

  ~ClientApp();

  // CefApp methods:
  virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
	  OVERRIDE { return this; }

  // CefBrowserProcessHandler methods:
  virtual void OnContextInitialized() OVERRIDE;

  // CefApp methods.
  virtual void OnBeforeCommandLineProcessing(
	  const CefString& process_type,
	  CefRefPtr<CefCommandLine> command_line) OVERRIDE;

private:
	// Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(ClientApp);
};

#endif  // _CEFCLIENTAPP_H_
