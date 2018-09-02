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
	command_line->AppendSwitch("--disable-web-security");//�ر�ͬԴ����
	command_line->AppendSwitch("allow-outdated-plugins");

	//manifest.json�е�version
	command_line->AppendSwitchWithValue("ppapi-flash-version", "30_0_0_154");

	//����flash���
	command_line->AppendSwitchWithValue("ppapi-flash-path", "plugins\\pepflashplayer32_30_0_0_154.dll");
	//command_line->AppendSwitch("--enable-system-flash");//ʹ��ϵͳflash
}