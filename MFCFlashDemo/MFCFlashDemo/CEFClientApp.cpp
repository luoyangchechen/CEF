#include "CEFClientApp.h"  // NOLINT(build/include)


ClientApp::ClientApp()
{

}

ClientApp::~ClientApp()
{

}


void ClientApp::OnContextInitialized() {


}


void ClientApp::OnBeforeCommandLineProcessing(
	const CefString& process_type,
	CefRefPtr<CefCommandLine> command_line)
{
	command_line->AppendSwitch("no-proxy-server");
	command_line->AppendSwitch("--enable-npapi");
	command_line->AppendSwitch("--disable-web-security");//关闭同源策略
	command_line->AppendSwitch("allow-outdated-plugins");

	//manifest.json中的version
	command_line->AppendSwitchWithValue("ppapi-flash-version", "30_0_0_154");

	//加载flash插件
	command_line->AppendSwitchWithValue("ppapi-flash-path", "plugins\\pepflashplayer32_30_0_0_154.dll");
	//command_line->AppendSwitch("--enable-system-flash");//使用系统flash
}