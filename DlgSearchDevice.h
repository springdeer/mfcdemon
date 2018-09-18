#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Protobuffer.h"
#include "msgdef.h"
#include "controls/PngStateButton.h"
// CDlgSearchDevice 对话框

class CDlgSearchDevice : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSearchDevice)

public:
	CDlgSearchDevice(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSearchDevice();
	void SetComStrings(vector<CString>& vecStrings);
// 对话框数据
	enum { IDD = IDD_DLG_SEARCH_DEVICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult);
	CListBox m_listData;
	afx_msg void OnBnClickedCancel();

	afx_msg LRESULT OnComMsgCom(WPARAM wParam,LPARAM lParam);
private:
	vector<CString> m_vecStrings;
	UINT  m_uTimer;
	int   m_waitSecs;
	int   m_iNdx;
	CProtoBuffer m_protoBuff;
	CTextStateButton m_btnCancel;
	int m_indxMemo;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
