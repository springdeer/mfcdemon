#pragma once
#include "afxwin.h"
#include "controls/public_res.h"
#include "controls/PngStateButton.h"

// CDlgBottomStatus 对话框

class CDlgBottomStatus : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBottomStatus)

public:
	CDlgBottomStatus(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgBottomStatus();

// 对话框数据
	enum { IDD = IDD_DIALOG_BOTTOM_BAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CPngStateButton m_btnSeprator1;
	CPngStateButton m_btnSeprator2;
	CPngStateButton m_btnSeprator3;
	afx_msg void OnBnClickedButtonSeperator();
	virtual BOOL OnInitDialog();
};
