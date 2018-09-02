
// MFCFlashDemoDlg.h : header file
//

#pragma once
#include "CefBrowserEventHandler.h"


// CMFCFlashDemoDlg dialog
class CMFCFlashDemoDlg : public CDialogEx
{
// Construction
public:
	CMFCFlashDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MFCFLASHDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CefRefPtr<CefBrowserEventHandler>  m_simpleClient;

	BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSearch();
	afx_msg void OnBnClickedBtnGoford();
	afx_msg void OnBnClickedBtnGoback();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
