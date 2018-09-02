// Duilib_Login.cpp : ����Ӧ�ó������ڵ㡣
//
#include "CefBrowserApp.h"
#include "MainFrameWnd.h"


//#define CEF_USE_SANDBOX 560

int APIENTRY _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR    lpCmdLine, int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("CefDemo"));


	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr)) return 0;

	/***************************************begin��ʼ��cef*******************************************/

	void* sandbox_info = NULL;
#if defined(CEF_USE_SANDBOX)
	CefScopedSandboxInfo scoped_sandbox;
	sandbox_info = scoped_sandbox.sandbox_info();
#endif

	CefMainArgs main_args(hInstance);
	CefRefPtr<CCefBrowserApp> spApp(new CCefBrowserApp);

	// Execute the secondary process, if any.
	int exit_code = CefExecuteProcess(main_args, spApp.get(),sandbox_info);
	if (exit_code >= 0)
		return exit_code;
	CefRefPtr<CefCommandLine> command_line;
	command_line = CefCommandLine::CreateCommandLine();
	command_line->AppendSwitch("no-proxy-server");//���������رմ�������

	//command_line->AppendSwitch("--disable-web-security");//�ر�ͬԴ����
	//command_line->AppendSwitchWithValue("ppapi-flash-version", "28.0.0.137");//PepperFlash\manifest.json�е�version
	//command_line->AppendSwitchWithValue("ppapi-flash-path", "PepperFlash\\pepflashplayer.dll");

	CefSettings cSettings;
	const char* loc = "zh-CN";

	cSettings.no_sandbox = true;  
	cSettings.multi_threaded_message_loop = true; 
	cSettings.single_process = false;
	cSettings.log_severity = LOGSEVERITY_DISABLE;//������־���𣬽����װ������׿�������������һ��debug.log�ļ�(���Խ׶ο���ȥ��)
	CefString(&cSettings.locale).FromASCII(loc);
	cef_string_from_ascii(loc, strlen(loc), &cSettings.locale);

	// Execute the secondary process, if any.
	CefInitialize(main_args, cSettings, spApp.get(),sandbox_info);
	/***************************************������ʼ��cef*******************************************/


	CMainFrameWnd*  pMain = new CMainFrameWnd;
	pMain->Create(NULL, _T("MainFrameWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES);
	pMain->CenterWindow();
	pMain->ShowWindow(TRUE);

	if (!cSettings.multi_threaded_message_loop) {
		// Run the CEF message loop. This function will block until the application
		// recieves a WM_QUIT message.
		CefRunMessageLoop();
	}
	else {
		DuiLib::CPaintManagerUI::MessageLoop();
	}

	CefShutdown();

	delete pMain;
	::CoUninitialize();
	return 0;
}



