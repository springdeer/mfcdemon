#pragma once
#include "afxwin.h"

#include "controls/public_res.h" 
#include "controls/PngStateButton.h"
#include <vector>
using namespace std;

// CDialogPane 对话框

class CDialogPane : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogPane)

public:
	CDialogPane(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogPane();

// 对话框数据
	enum { IDD = IDD_DIALOG_TOP_PANE };
	void ShowWirelessConnected(BOOL bConnected);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
protected:
	BOOL FindSSCom();
	void SearchCom();
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonCom();
private:
	CPngStateButton m_btnCom;
	CTextStateButton m_btnSSCOMOper;
	CPngStateButton  m_btnSepratorCom;

	CTextStateButton m_btnWirelessConnect;
	CPngStateButton  m_btnWirelessState;
	CPngStateButton  m_btnWirelessSeperator;

	CPngButton m_btnRcvrSetting;
	CPngButton m_btnDataWant;
	CPngButton m_btnDataBound;

	CPngStateButton m_btnSeperatorData;
	CPngButton m_btnDataStore;
	CPngButton m_btnSetmode;//IMAGE_SETPROP
	CPngButton m_btnAppIcon;
	CString    m_strSelectedFolder;

	vector<CString>  m_sscoms;
public:
	virtual BOOL OnInitDialog();
	
	afx_msg void OnBnClickedButtonCom2();
	
	afx_msg void OnBnClickedButtonWirelessConnect();
	
	afx_msg void OnBnClickedButtonWirelessState();
	
	afx_msg void OnBnClickedButtonRcvrsetting();
		
	afx_msg void OnBnClickedButtonDataStore();
	CComboBox m_comboMode;
	afx_msg void OnBnClickedButtonDataWant();
	
	afx_msg void OnBnClickedButtonWirelessState2();
	afx_msg void OnBnClickedButtonSeperator();
	afx_msg void OnBnClickedButtonAppicon();
	afx_msg void OnBnClickedButtonDataBound();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
