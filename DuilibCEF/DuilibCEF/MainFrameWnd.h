#ifndef _MAINFRAMEWND_H_
#define _MAINFRAMEWND_H_
//#include "CefBrowserEventHandler.h"
#include "stdafx.h"

class CMainFrameWnd :public WindowImplBase
{
public:
	CMainFrameWnd();

    virtual ~CMainFrameWnd();   // ˽�л����������������˶���ֻ��ͨ��new�����ɣ�������ֱ�Ӷ���������ͱ�֤��delete this�������
public:
	LPCTSTR GetWindowClassName() const;	

	virtual void OnFinalMessage(HWND hWnd);

	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

	virtual UILIB_RESOURCETYPE GetResourceType() const;

	virtual CDuiString GetSkinFile();

	virtual CDuiString GetSkinFolder();

	virtual CControlUI* CreateControl(LPCTSTR pstrClass);

	 virtual void InitWindow();

     virtual void Notify(TNotifyUI& msg);

     virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

     virtual void OnClick(TNotifyUI& msg);

	 void OnPrepare();

public:

	 LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


	 LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	 LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
};
#endif//_MAINFRAMEWND_H_