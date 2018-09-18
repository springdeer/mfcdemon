// DialogPaneBottom.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DialogPaneBottom.h"
#include "afxdialogex.h"
#include "MFCApplication2Dlg.h"

// CDialogPaneBottom 对话框

IMPLEMENT_DYNAMIC(CDialogPaneBottom, CDialogEx)

CDialogPaneBottom::CDialogPaneBottom(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogPaneBottom::IDD, pParent)
{
	m_sizingCX = 3;
	m_bEnableShow = TRUE;
}

CDialogPaneBottom::~CDialogPaneBottom()
{
}

void CDialogPaneBottom::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA, m_listData);
}


BEGIN_MESSAGE_MAP(CDialogPaneBottom, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogPaneBottom::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDialogPaneBottom 消息处理程序


void CDialogPaneBottom::ShowCursor(CPoint point)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rcSizingLine(&rcClient);
	rcSizingLine.bottom = rcSizingLine.top + 4;

	if (rcSizingLine.PtInRect(point)){
		HCURSOR cursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_SIZENS));
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


void CDialogPaneBottom::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rcClient,rcClipBox;
	GetClientRect(&rcClient);
	
	dc.GetClipBox(&rcClipBox);

	if (rcClipBox.IsRectEmpty()) return;

	CMemDC mdc(dc,rcClipBox);
	CDC& refdc = mdc.GetDC();

	refdc.FillSolidRect(&rcClipBox, RGB(200, 100, 34));

	CRect rcBorder(rcClient);
	rcBorder.bottom = rcBorder.top + m_sizingCX;
	refdc.FillSolidRect(&rcBorder, RGB(200, 200, 200));

	rcBorder = rcClient;
	rcBorder.right = rcBorder.left + 1;
	refdc.FillSolidRect(&rcBorder, RGB(200, 200, 200));

	rcBorder = rcClient;
	rcBorder.left = rcBorder.right - 1;
	refdc.FillSolidRect(&rcBorder, RGB(158, 160, 189));

	if (m_bLeftButtonDown && m_bSizingBorder){
		CRect rcSizingLine(&rcClient);
		rcSizingLine.bottom = rcSizingLine.top + 4;
		refdc.FillSolidRect(&rcSizingLine, RGB(122, 122, 122));
	}
	
}


void CDialogPaneBottom::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	CRect rcClient;
	GetClientRect(&rcClient);

	if (IsWindow(m_listData.GetSafeHwnd())){
		rcClient.DeflateRect(1, 1);
		rcClient.top = rcClient.top + 4;
		m_listData.MoveWindow(&rcClient);
		m_listData.UpdateWindow();
	}	

	UpdateWindow();
}


void CDialogPaneBottom::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	ShowCursor(point);

	bool bSizing = m_bSizingBorder && m_bLeftButtonDown;
	TRACE(_T("%d,%d\n"), m_bSizingBorder, m_bLeftButtonDown);

	while (bSizing){

		CRect rcClient;
		GetClientRect(&rcClient);		
		
		CRect rcSizingLine(&rcClient);
		rcSizingLine.bottom = rcSizingLine.top + 4;
		InvalidateRect(&rcSizingLine);

		CRect rcMap;
		if (rcClient.bottom - point.y  < 30 || rcClient.bottom - point.y  > 200) { return; }

		rcClient.top += (point.y - rcClient.top);

		MapWindowPoints(GetParent(), &rcClient);

		MoveWindow(&rcClient);

		CDialogFrame * pFrame = (CDialogFrame *)(CMFCApplication2Dlg*)GetParent();
		pFrame->OnWorkAreaChanged(this);

		break;
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CDialogPaneBottom::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_bLeftButtonDown = true;
	SetCapture();

	ShowCursor(point);	

	if (m_bSizingBorder && m_bLeftButtonDown){
		CRect rcSizingLine;
		GetClientRect(&rcSizingLine);
		rcSizingLine.bottom = rcSizingLine.top + 4;
		InvalidateRect(&rcSizingLine);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDialogPaneBottom::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	bool bSizing = m_bSizingBorder && m_bLeftButtonDown;
	if (bSizing){
		m_bLeftButtonDown = false;

		CRect rcSizingLine;
		GetClientRect(&rcSizingLine);
		rcSizingLine.bottom = rcSizingLine.top + 4;
		InvalidateRect(&rcSizingLine);

		ReleaseCapture();
	}
	
	CDialogEx::OnLButtonUp(nFlags, point);
}


BOOL CDialogPaneBottom::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	return CDialogEx::OnEraseBkgnd(pDC);
}


void CDialogPaneBottom::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
}

void CDialogPaneBottom::InsertRaw(unsigned char buffer[], int bufferlen)
{
// 	if (buffer == NULL || bufferlen < 1 || !m_bEnableShow) return;
// 
// 	CString strRaw;
// 	for (int i = 0; i < bufferlen; i++)
// 	{
// 		TCHAR chs[3];
// 		_stprintf_s(chs, sizeof(chs), _T("%02X"), buffer[i]);
// 		strRaw.Append(chs);
// 	}
// 
// 	m_listData.AddString((LPCTSTR)strRaw);
// 	
// 	CRect rcClient;
// 	m_listData.GetClientRect(&rcClient);
// 
// 	if (m_listData.GetCount() > 0){
// 		int nCountPerPage = rcClient.Height() / m_listData.GetItemHeight(0);
// 		if (m_listData.GetTopIndex() + nCountPerPage >= m_listData.GetCount()){
// 			m_listData.SetTopIndex(m_listData.GetCount() - nCountPerPage);
// 		}
// 	}	
}

void CDialogPaneBottom::ClearData()
{
	//m_listData.ResetContent();
}