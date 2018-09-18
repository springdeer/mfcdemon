#pragma once


// CDlgPCPrestate 对话框

class CDlgPCPrestate : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPCPrestate)

public:
	CDlgPCPrestate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPCPrestate();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
};
