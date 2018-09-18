
// MFCApplication2Dlg.h : 头文件
//

#pragma once
#include "DialogPane.h"
#include "DlgBottomStatus.h"
#include "StatusPane.h"
#include "DialogPaneLeft.h"
#include "DialogPaneRight.h"
#include "DialogPaneBottom.h"
#include "DlgWorkArea.h"
#include "DlgIcon.h"
#include <atlimage.h>
#include <gdiplusheaders.h>

// CMFCApplication2Dlg 对话框
class CDialogFrame{
public:
	virtual void OnWorkAreaChanged(CWnd* pWnd) = NULL;

};

struct windowposstruct{
	int caption_hgt;
	CString title;
	int toppane_hgt;
	int statusbar_hgt;
};

class CMFCApplication2Dlg : public CDialogEx, public CDialogFrame
{
// 构造
public:
	CMFCApplication2Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
	virtual void OnWorkAreaChanged(CWnd* pWnd);

	CDialogPaneBottom * GetBottomPane(){ return &m_bottomPane; }
	CWnd * GetWorkAreaWnd();

	void PrintWnd(CWnd* pWnd2Print, CString strFile);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持	
	
// 实现
protected:
	HICON m_hIcon;
	CImage * m_pImage;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnComMsgCom(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnNcPaint();
	afx_msg BOOL OnNcActivate(BOOL bActive);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	void  ReposePanes();
	CRect GetVisibleBound();
protected:
	void  CreatePanes();
	CRect CalcWorkArea();
private:
	CRect m_rtButtExit;
	CRect m_rtButtMax;
	CRect m_rtButtMin;
	windowposstruct winpos;

	CRect m_rcWorkArea;

	int   m_nCaptionHgt;
	int   m_hgtStatusbar;
	int   m_hgtToppane;
	CDialogPane m_topPane;
	//CDlgBottomStatus m_bottomBar;
	CStatusPane m_statusBar;
	CDialogPaneLeft  m_leftPane;
	CDialogPaneRight m_rightPane;
	CDialogPaneBottom m_bottomPane;
	CDlgWorkArea m_workArea;
	CFont m_fontTitle;
	CImage* m_logImage;
	//CDlgIcon m_wndLogo;
public:
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
