#pragma once


// CDlgPageNavistate 对话框

class CDlgPageNavistate : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPageNavistate)

public:
	CDlgPageNavistate(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPageNavistate();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
