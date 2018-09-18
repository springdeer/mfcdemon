#pragma once
#include "afxwin.h"


// CDialogPaneBottom 对话框

class CDialogPaneBottom : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogPaneBottom)

public:
	CDialogPaneBottom(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogPaneBottom();

// 对话框数据
	enum { IDD = IDD_DIALOG_BOTTOM_PANE };

	void EnableShow(BOOL bEnable){ m_bEnableShow = bEnable; }
	void ClearData();
protected:
	void ShowCursor(CPoint point);
	void InsertRaw(unsigned char buffer[],int bufferlen);

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
protected:
	HCURSOR m_cursor;
	bool    m_bSizingBorder;
	bool    m_bLeftButtonDown;
	int     m_sizingCX;
	BOOL    m_bEnableShow;
	CListCtrl m_listData;
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedButton1();	
};
