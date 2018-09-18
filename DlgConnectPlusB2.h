#pragma once
#include "resource.h"
#include "CommandWnds.h"
// CDlgConnectPlusB2 对话框

class CDlgConnectPlusB2 : public CDialogEx, public ICommandWnd
{
	DECLARE_DYNAMIC(CDlgConnectPlusB2)
public:
	CDlgConnectPlusB2(CWnd* pParent = NULL);   // 标准构造函数

	virtual void   Show();
	virtual BOOL   IsCommandTimeout();
	virtual void   ExitCommand();
	virtual BOOL   CheckKBState(int key);
	virtual BOOL   CheckRemoteReplay(void* reply);
protected:	
	virtual ~CDlgConnectPlusB2();
	void    UpdateTip();
// 对话框数据
	enum { IDD = IDD_DLG_CONNET_PLUSB2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
private:
	UINT   m_uTimer;
	time_t m_timeCmd;
	BOOL   m_state;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
};
