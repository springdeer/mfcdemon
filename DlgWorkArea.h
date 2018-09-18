#pragma once
#include "afxwin.h"
#include "controls/public_res.h" 
#include "controls/PngStateButton.h"
#include "afxcmn.h"
#include "DlgPageCPCheck.h"
#include "DlgPageNavistate.h"
#include "DlgPageRcvrMon.h"
#include "DlgPCPrestate.h"
// CDlgWorkArea �Ի���

class CDlgWorkArea : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgWorkArea)

public:
	CDlgWorkArea(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgWorkArea();

// �Ի�������
	enum { IDD = IDD_DIALOG_WORKAREA };
	CWnd * GetActiveWnd();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
