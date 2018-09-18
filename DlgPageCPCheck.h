#pragma once

#include "resource.h"
// CDlgPageCPCheck 对话框

class CDlgPageCPCheck : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPageCPCheck)

public:
	CDlgPageCPCheck(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPageCPCheck();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
