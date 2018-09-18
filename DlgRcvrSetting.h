#pragma once
#include "afxwin.h"
#include "controls/PngButton.h"

// CDlgRcvrSetting 对话框

class CDlgRcvrSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRcvrSetting)
protected:
	CDlgRcvrSetting(CWnd* pParent = NULL);   // 标准构造函数
public:
	static CDlgRcvrSetting* Get();
	virtual ~CDlgRcvrSetting();

// 对话框数据
	enum { IDD = IDD_DIALOG_RCVR_SETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonB2pw();
protected:
	void InitUi();
	BOOL IsDigit(TCHAR ch);
	BOOL CheckIntRange(CString strValue, int left, int right,int& rslt);
private:
	static CDlgRcvrSetting* m_pObj;
public:
	CPngButton m_btnB2pw;
	CPngButton m_btnB2pwClose;
	CPngButton m_btnB3pw;
	CPngButton m_btnB3pwClose;
	CPngButton m_btnB4pw;
	CPngButton m_btnB4pwClose;
	CPngButton m_btnD1pw;
	CPngButton m_btnD1pwClose;
	CPngButton m_btnRcvrId;
	CPngButton m_btnT1pw;
	CPngButton m_btnT2pw;
	CPngButton m_btnT3pw;
	CPngButton m_btnT4pw;
	CPngButton m_btnT5pw;
	CPngButton m_btnT6pw;
	CPngButton m_btnT7pw;
	CPngButton m_btnFirepw;
	CPngButton m_btnFirepw2;
	afx_msg void OnBnClickedButtonRcvrid();
	virtual BOOL OnInitDialog();
protected:
	
public:
	
	UINT m_nB2PW;
	UINT m_nB2PW_close;
	UINT m_nB3PW;
	UINT m_nB3PW_close;
	UINT m_nB4PW;
	UINT m_nB4PW_close;
	UINT m_nD1PW;
	UINT m_nD1PW_close;
	UINT m_nT1PW;
	UINT m_nT2PW;
	UINT m_nT3PW;
	UINT m_nT4PW;
	UINT m_nT5PW;
	UINT m_nT6PW;
	UINT m_nT7PW;
	UINT m_nFirePW;
	UINT m_nTransPower;
	UINT m_nRcvrID;
	BOOL m_bAutoSelectChannel;
	afx_msg void OnBnClickedButtonB2pwClose();
	afx_msg void OnBnClickedButtonB3pw();
	afx_msg void OnBnClickedButtonB3pwClose();
	afx_msg void OnBnClickedButtonB4pw();
	afx_msg void OnBnClickedButtonB4pwClose();
	afx_msg void OnBnClickedButtonD1pw();
	afx_msg void OnBnClickedButtonD1pwClose();
	afx_msg void OnBnClickedButtonT1pw();
	afx_msg void OnBnClickedButtonT2pw();
	afx_msg void OnBnClickedButtonT3pw();
	afx_msg void OnBnClickedButtonT4pw();
	afx_msg void OnBnClickedButtonT5pw();
	afx_msg void OnBnClickedButtonT6pw();
	afx_msg void OnBnClickedButtonT7pw();
	afx_msg void OnBnClickedButtonFirepw();
	int m_iChannel;
	afx_msg void OnBnClickedButtonFirepw2();
	afx_msg void OnBnClickedCheckAutoadjust();
};
