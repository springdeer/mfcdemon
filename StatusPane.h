#pragma once
#include "afxwin.h"

#include "controls/public_res.h"
#include "controls/PngStateButton.h"

// CStatusPane 对话框

class CStatusPane : public CDialogEx
{
	DECLARE_DYNAMIC(CStatusPane)

public:
	CStatusPane(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStatusPane();

// 对话框数据
	enum { IDD = IDD_DIALOG_STATE_PANE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonSeperator();
protected:
	CTextStateButton m_btnRunTime;
	CTextStateButton m_btnHistTime;
	CTextStateButton m_btnRemoteTime;
	CTextStateButton m_btnUTC;
public:
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedButtonRuntime();
	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
