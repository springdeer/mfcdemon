#pragma once
#include "afxwin.h"
#include "controls/PngStateButton.h"
#include "controls/PngStateButton.h"

// CDialogPaneRight 对话框

class CDialogPaneRight : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogPaneRight)

public:
	CDialogPaneRight(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogPaneRight();

// 对话框数据
	enum { IDD = IDD_DIALOG_RIGHT_PANE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	void ShowCursor(CPoint point);
	void InitUi();
private:
	HCURSOR m_cursor;
	bool    m_bSizingBorder;
	bool    m_bLeftButtonDown;
	int     m_sizingCX;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButtonUnplusD1();
	afx_msg void OnBnClickedButtonStopshow();
	CPngStateButton m_btnVB4State;
	CPngStateButton m_btnVD1State;
	CPngStateButton m_btnB3State;
	CPngStateButton m_btnVB2State;
	afx_msg void OnBnClickedButtonSavefile();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPlusb4volt();
	CTextStateButton m_btnB4Tip;
	CTextStateButton m_btnD1Tip;
	CTextStateButton m_btnB3Tip;
	CTextStateButton m_btnB2Tip;
	CTextStateButton m_btnHGJB1Ind;
	CTextStateButton m_btnYJFDJDHInd;
	CTextStateButton m_btnABJGJBInd;
	CTextStateButton m_btnABJGFWInd;
	afx_msg void OnBnClickedButtonAllowshow();
	afx_msg void OnBnClickedButtonClearshow();
	afx_msg void OnBnClickedButtonPlusb2volt4();
	CPngStateButton m_btnKeyReset1State;
	CPngStateButton m_btnFire1State;
	CPngStateButton m_btnSecUnlockState;
	CPngStateButton m_btnSafeResetState;
	afx_msg void OnBnClickedButtonKeyreset1Ind();
	afx_msg void OnBnClickedButtonKetyreset();
	afx_msg void OnBnClickedButtonUnplusB4();
	afx_msg void OnBnClickedButtonUnplusB3();
	afx_msg void OnBnClickedButtonUnplusB2();
};
