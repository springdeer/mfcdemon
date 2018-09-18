#pragma once
#include "afxwin.h"
#include "controls/public_res.h" 
#include "controls/PngStateButton.h"
#include "afxcmn.h"
#include "DlgPageCPCheck.h"
#include "DlgPageNavistate.h"
#include "DlgPageRcvrMon.h"
#include "DlgPCPrestate.h"
// CDlgWorkArea 对话框

class CDlgWorkArea : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWorkArea)

public:
	CDlgWorkArea(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgWorkArea();

// 对话框数据
	enum { IDD = IDD_DIALOG_WORKAREA };
	CWnd * GetActiveWnd();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CMFCTabCtrl m_tab;
	CDlgPageCPCheck   m_pageCPCheck;
	CDlgPageNavistate m_pageNaviState;
	CDlgPageRcvrMon   m_pageRcvrMon;
	CDlgPCPrestate    m_PCPrestate;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
