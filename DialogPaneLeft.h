#pragma once

#include "./controls/PngButton.h"
#include "afxwin.h"
#include "afxcmn.h"

#include "DlgPageCPCheck.h"
#include "DlgPageNavistate.h"
#include "DlgPageRcvrMon.h"
#include "DlgPCPrestate.h"

// CDialogPaneLeft 对话框

struct Hideparam{
	CSize oldSize;
	bool m_bHide;
	bool m_bInflated;
};

struct Headerpaream{
	int cy;
	COLORREF bkcolor;
	COLORREF forecolor;
	CString  title;
};

class CDialogPaneLeft : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogPaneLeft)

public:
	CDialogPaneLeft(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDialogPaneLeft();

// 对话框数据
	enum { IDD = IDD_DIALOG_LEFT_PANE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CRect CalcWorkArea();
	CRect CalcHeadArea();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	void ShowCursor(CPoint point);
	void DrawHeader(CDC* pDC);
	void DrawFrame(CDC* pDC);
	void DockHide(bool bHide);
	Hideparam m_hideparam;
	Headerpaream m_headerparam;
private:
	CString m_header;
	HCURSOR m_cursor;
	CPngButton  m_btnHidePane;
	CMFCTabCtrl m_tabWnd;

	CDlgPageCPCheck   m_pageCPCheck;
	CDlgPageNavistate m_pageNaviState;
	CDlgPageRcvrMon   m_pageRcvrMon;

	bool    m_bSizingBorder;
	bool    m_bLeftButtonDown;
	int     m_sizingCX;
	bool    m_bInited;
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	
	afx_msg void OnBnClickedBtnHide();
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	
};
