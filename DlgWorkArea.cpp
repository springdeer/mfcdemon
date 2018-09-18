// DlgWorkArea.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgWorkArea.h"
#include "afxdialogex.h"


// CDlgWorkArea 对话框

IMPLEMENT_DYNAMIC(CDlgWorkArea, CDialogEx)

CDlgWorkArea::CDlgWorkArea(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgWorkArea::IDD, pParent)
{

}

CDlgWorkArea::~CDlgWorkArea()
{
}

void CDlgWorkArea::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgWorkArea, CDialogEx)
	ON_WM_PAINT()	
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgWorkArea 消息处理程序


void CDlgWorkArea::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	//CRect rcClient;
	//GetClientRect(&rcClient);

	//dc.FillSolidRect(&rcClient, RGB(120, 255, 120));

	dc.TextOut(12, 12, _T("this is a work area!"));
}

BOOL CDlgWorkArea::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rectTab;
	GetClientRect(&rectTab);
	m_tab.Create(CMFCTabCtrl::STYLE_3D_ONENOTE, rectTab, this, 1202, CMFCTabCtrl::LOCATION_BOTTOM);

	m_pageCPCheck.Create(CDlgPageCPCheck::IDD, &m_tab);
	m_pageNaviState.Create(CDlgPageNavistate::IDD, &m_tab);
	m_pageRcvrMon.Create(CDlgPageRcvrMon::IDD, &m_tab);
	m_PCPrestate.Create(CDlgPCPrestate::IDD, &m_tab);

	m_tab.AddTab(&m_PCPrestate, "计算机预备状态", (UINT)-1, FALSE);
	m_tab.AddTab(&m_pageNaviState, "组合导航预备状态", (UINT)-1, FALSE);
	m_tab.AddTab(&m_pageCPCheck, "计算机自检数据", (UINT)-1, FALSE);
	m_tab.AddTab(&m_pageRcvrMon, "接收机监测数据", (UINT)-1, FALSE);

	m_tab.ShowWindow(SW_SHOW);
	m_tab.EnableTabSwap(FALSE);//不可拖拽

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDlgWorkArea::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	CRect rcClient;
	GetClientRect(&rcClient);

	if (::IsWindow(m_tab.GetSafeHwnd())){
		m_tab.MoveWindow(&rcClient);
		
		CRect rcWnd;
		m_tab.GetWndArea(rcWnd);

		m_pageCPCheck.MoveWindow(&rcWnd);
		m_pageNaviState.MoveWindow(&rcWnd);
		m_pageRcvrMon.MoveWindow(&rcWnd);
		m_PCPrestate.MoveWindow(&rcWnd);
		
		//m_tab.GetTabWnd(m_tab.GetActiveTab())->InvalidateRect(NULL);
		m_tab.GetTabWnd(m_tab.GetActiveTab())->UpdateWindow();
	}

}

void CDlgWorkArea::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	
	*pResult = 0;
}

CWnd * CDlgWorkArea::GetActiveWnd()
{
	return m_tab.GetActiveWnd();
}