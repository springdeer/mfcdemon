#pragma once


// CDlgPageRcvrMon 对话框

class CDlgPageRcvrMon : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPageRcvrMon)

public:
	CDlgPageRcvrMon(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPageRcvrMon();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
