// DialogPaneLeft.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DialogPaneLeft.h"
#include "afxdialogex.h"
#include "MFCApplication2Dlg.h"
// CDialogPaneLeft 对话框

IMPLEMENT_DYNAMIC(CDialogPaneLeft, CDialogEx)

CDialogPaneLeft::CDialogPaneLeft(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogPaneLeft::IDD, pParent)
{
	m_sizingCX = 3;
	m_hideparam.m_bHide = false;
	m_hideparam.m_bInflated = false;
	m_hideparam.oldSize = CSize(0,0);

	m_headerparam.bkcolor = RGB(123, 23, 34);
	m_headerparam.forecolor = RGB(200,200,200);
	m_headerparam.title = _T("一起来吃个鸡吧!");
	m_headerparam.cy = 24;

	m_bInited = false;

}

CDialogPaneLeft::~CDialogPaneLeft()
{
}

void CDialogPaneLeft::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_HIDE, m_btnHidePane);
}


BEGIN_MESSAGE_MAP(CDialogPaneLeft, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BTN_HIDE, &CDialogPaneLeft::OnBnClickedBtnHide)
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


// CDialogPaneLeft 消息处理程序

void CDialogPaneLeft::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rcBox,rcClient;
	GetClientRect(&rcClient);

	dc.GetClipBox(rcBox);
	if (rcBox.IsRectEmpty()) return;

	CMemDC memdc(dc, rcBox);
	CDC& refdc = memdc.GetDC();
	//refdc.Draw3dRect(&rcClient, RGB(200, 100, 34),RGB(200, 100, 34));
	refdc.FillSolidRect(&rcBox, RGB(200, 100, 34));

// 	CRect rcBorder(rcClient);
// 	rcBorder.bottom = rcBorder.top + 1;
// 	refdc.FillSolidRect(&rcBorder, RGB(200, 200, 200));
// 
// 	rcBorder = rcClient;
// 	rcBorder.top = rcBorder.bottom - 1;
// 	refdc.FillSolidRect(&rcBorder, RGB(200, 200, 200));
// 
// 	rcBorder = rcClient;
// 	rcBorder.left = rcBorder.right - m_sizingCX;
// 	refdc.FillSolidRect(&rcBorder, RGB(158, 160, 189));

	DrawHeader(&refdc);
}

void CDialogPaneLeft::DrawFrame(CDC* pDC)
{
	const int height = 20;

}

void CDialogPaneLeft::DrawHeader(CDC* pDC)
{
	CRect rcClient;

	GetClientRect(&rcClient);

	CRect m_rcHeader(1, 1, rcClient.right - 1, m_headerparam.cy+1);
    
	pDC->FillSolidRect(&m_rcHeader, m_headerparam.bkcolor);

	pDC->SetTextColor(m_headerparam.forecolor);

	pDC->DrawText(m_headerparam.title, &m_rcHeader, DT_LEFT|DT_VCENTER);

}

CRect CDialogPaneLeft::CalcHeadArea()
{
	CRect rt;

	GetClientRect(&rt);

	rt.bottom = m_headerparam.cy;

	return rt;
}

CRect CDialogPaneLeft::CalcWorkArea()
{
	CRect rt;

	GetClientRect(&rt);

	rt.top = m_headerparam.cy;
	//rt.DeflateRect(1, 1);

	return rt;
}

void CDialogPaneLeft::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	CRect rcHead   = CalcHeadArea();
	CRect rcWkArea = CalcWorkArea();

	//ValidateRect(&rcWkArea);

	if (m_bInited && ::IsWindow(m_btnHidePane.GetSafeHwnd())){
		CRect rcBtnHide;
		m_btnHidePane.GetClientRect(&rcBtnHide);

		int cx = rcBtnHide.Width();
		int cy = rcBtnHide.Height();

		rcBtnHide.left = rcHead.right - cx-4;
		rcBtnHide.top = (rcHead.Height() - cy) / 2;
		rcBtnHide.right = rcBtnHide.left + cx;
		rcBtnHide.bottom = rcBtnHide.top + cy;

		m_btnHidePane.MoveWindow(&rcBtnHide);
	}

	if (::IsWindow(m_tabWnd.GetSafeHwnd())){
		m_tabWnd.MoveWindow(&rcWkArea);

		CRect rcWnd;
		m_tabWnd.GetWndArea(rcWnd);

		m_pageCPCheck.MoveWindow(&rcWnd);
		m_pageNaviState.MoveWindow(&rcWnd);
		m_pageRcvrMon.MoveWindow(&rcWnd);

		m_tabWnd.GetTabWnd(m_tabWnd.GetActiveTab())->InvalidateRect(NULL);
	}

	UpdateWindow();
}

void CDialogPaneLeft::ShowCursor(CPoint point)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rcSizingLine(&rcClient);
	rcSizingLine.left = rcSizingLine.right - 3;
	if (rcSizingLine.PtInRect(point)){
		HCURSOR cursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZEWE));
		m_bSizingBorder = true;
		m_cursor = SetCursor(cursor);
	}
	else{
		if (m_bSizingBorder && m_bLeftButtonDown) { return; }

		m_bSizingBorder = false;

		HCURSOR cursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
		SetCursor(cursor);
	}
}

void CDialogPaneLeft::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	if (m_hideparam.m_bHide)
	{ //打开鼠标进入与离开的消息监听

		TRACKMOUSEEVENT tme;

		tme.cbSize = sizeof(tme);

		tme.hwndTrack = m_hWnd;

		tme.dwFlags = TME_LEAVE | TME_HOVER;

		tme.dwHoverTime = 1;

		_TrackMouseEvent(&tme);
		TRACE(_T("track mouser hover.. \n"));
	}

	//ShowCursor(point);

	
	//bool bSizing = m_bSizingBorder && m_bLeftButtonDown;
	//while (bSizing){
	//	SetCapture();
	//	if (point.x < 135 || point.x > 300) break;

	//	CRect rcClient;
	//	GetClientRect(&rcClient);

	//	rcClient.right = rcClient.left + point.x;
	//	
	//	MapWindowPoints(GetParent(), &rcClient);

	//	MoveWindow(&rcClient);

	//	CDialogFrame * pFrame = (CDialogFrame *)(CMFCApplication2Dlg*)GetParent();
	//	pFrame->OnWorkAreaChanged(this);

	//	break;
	//}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CDialogPaneLeft::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	ShowCursor(point);

	m_bLeftButtonDown = true;

	if (m_hideparam.m_bHide){
		m_hideparam.m_bHide = false;
		m_hideparam.m_bInflated = false;
		DockHide(m_hideparam.m_bHide);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDialogPaneLeft::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_bLeftButtonDown = false;
	bool bSizing = m_bSizingBorder && m_bLeftButtonDown;

	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}


BOOL CDialogPaneLeft::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	return TRUE;

	return CDialogEx::OnEraseBkgnd(pDC);
}


BOOL CALLBACK EnumChildProc(HWND hWnd, LPARAM lParam)
{

	::ShowWindow(hWnd, lParam == 0 ? SW_HIDE : SW_SHOW);
	
	return true;

}

void CDialogPaneLeft::DockHide(bool bHide)
{
	if (bHide){
		::EnumChildWindows(GetSafeHwnd(), EnumChildProc, 0);

		CRect rcClient;
		GetClientRect(&rcClient);
		m_hideparam.oldSize = CSize(rcClient.Width(), rcClient.Height());

		rcClient.right = rcClient.left + 20;
		MapWindowPoints(GetParent(), &rcClient);
		MoveWindow(&rcClient);

		InvalidateRect(NULL);
		UpdateWindow();
	}
	else{
		::EnumChildWindows(GetSafeHwnd(), EnumChildProc, 1);

		CRect rcClient;
		GetClientRect(&rcClient);

		rcClient.right  = rcClient.left + m_hideparam.oldSize.cx;
		rcClient.bottom = rcClient.top + m_hideparam.oldSize.cy;

		MapWindowPoints(GetParent(), &rcClient);
		MoveWindow(&rcClient);
	}

	CDialogFrame * pFrame = (CDialogFrame *)(CMFCApplication2Dlg*)GetParent();
	pFrame->OnWorkAreaChanged(this);
}

void CDialogPaneLeft::OnBnClickedBtnHide()
{
	// TODO:  在此添加控件通知处理程序代码

	m_hideparam.m_bHide = !m_hideparam.m_bHide;

	DockHide(m_hideparam.m_bHide);
	
}


BOOL CDialogPaneLeft::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_btnHidePane.Init("./res/setprop.png", 4, BTN_TYPE_NORMAL);

	CRect rectTab;
	rectTab.SetRectEmpty();

	m_tabWnd.Create(CMFCTabCtrl::STYLE_3D, rectTab, this, 1209, CMFCTabCtrl::LOCATION_BOTTOM);

	m_pageCPCheck.Create(CDlgPageCPCheck::IDD, &m_tabWnd);
	m_pageNaviState.Create(CDlgPageNavistate::IDD, &m_tabWnd);
	m_pageRcvrMon.Create(CDlgPageRcvrMon::IDD, &m_tabWnd);
	
	m_tabWnd.AddTab(&m_pageNaviState, "设备管理", (UINT)-1, FALSE);
	m_tabWnd.AddTab(&m_pageCPCheck, "人员管理", (UINT)-1, FALSE);
	m_tabWnd.AddTab(&m_pageRcvrMon, "任务管理", (UINT)-1, FALSE);

	m_tabWnd.ShowWindow(SW_SHOW);
	m_tabWnd.EnableTabSwap(FALSE);//不可拖拽

	m_bInited = true;

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDialogPaneLeft::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	TRACE(_T("onmouse hover.. \n"));
	if (m_hideparam.m_bHide){
		CRect rcClient;
		GetClientRect(&rcClient);

		if (!m_hideparam.m_bInflated){
			rcClient.right = rcClient.left + rcClient.Width()*1.5;
			MapWindowPoints(GetParent(), &rcClient);
			MoveWindow(&rcClient);
			InvalidateRect(NULL);
			UpdateWindow();

			m_hideparam.m_bInflated = true;

			CDialogFrame * pFrame = (CDialogFrame *)(CMFCApplication2Dlg*)GetParent();
			pFrame->OnWorkAreaChanged(this);
		}
	}

	CDialogEx::OnMouseHover(nFlags, point);
}


void CDialogPaneLeft::OnMouseLeave()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_hideparam.m_bHide){
		CRect rcClient;
		GetClientRect(&rcClient);

		if (m_hideparam.m_bInflated){
			rcClient.right = rcClient.left + 20;
			MapWindowPoints(GetParent(), &rcClient);
			MoveWindow(&rcClient);
			m_hideparam.m_bInflated = false;

			CDialogFrame * pFrame = (CDialogFrame *)(CMFCApplication2Dlg*)GetParent();
			pFrame->OnWorkAreaChanged(this);
		}
	}

	CDialogEx::OnMouseLeave();
}
