
// MFCApplication2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
#include "msgdef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 对话框

CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	winpos.caption_hgt = 28;
	winpos.title = _T("转捩平台无线接收机地面控制软件");
	winpos.toppane_hgt = 48;
	winpos.statusbar_hgt = 24;

	m_pImage = new CImage();

	HRESULT res = m_pImage->Load("./res/system_upgrade.png");

	if (FAILED(res)) { delete m_pImage; m_pImage = NULL; }
	else{
		if (m_pImage->GetBPP() == 32) //确认该图像包含Alpha通道
		{
			int w;
			int h;
			for (w = 0; w < m_pImage->GetWidth(); w++)
			{
				for (h = 0; h < m_pImage->GetHeight(); h++)
				{
					byte *pByte = (byte *)m_pImage->GetPixelAddress(w, h);
					pByte[0] = pByte[0] * pByte[3] / 255;
					pByte[1] = pByte[1] * pByte[3] / 255;
					pByte[2] = pByte[2] * pByte[3] / 255;
				}
			}
		}
	}

}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_NCACTIVATE()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_GETMINMAXINFO()
	ON_WM_NCLBUTTONDBLCLK()
	ON_BN_CLICKED(IDOK, &CMFCApplication2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication2Dlg::OnBnClickedCancel)
	ON_WM_CLOSE()
	ON_WM_WINDOWPOSCHANGED()
	ON_MESSAGE(WM_COM_MSGDATA,OnComMsgCom)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CMFCApplication2Dlg 消息处理程序

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码	

	//m_wndLogo.Create(CDlgIcon::IDD, this);

	CRect rcWindow;
	
	GetWindowRect(&rcWindow);
	CPoint pt(0, 0);
	MapWindowPoints(NULL, &rcWindow);

	//m_wndLogo.SetWindowPos(this, rcWindow.left, rcWindow.top+2,0,0,SWP_NOSIZE|SWP_SHOWWINDOW);

	m_fontTitle.CreateFontA(12, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	
	CreatePanes();

	ReposePanes();

	ShowWindow(SW_MAXIMIZE);	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication2Dlg::CreatePanes()
{
	m_topPane.Create(CDialogPane::IDD, this);
	m_topPane.ShowWindow(SW_SHOW);

	m_statusBar.Create(CStatusPane::IDD, this);
	m_statusBar.ShowWindow(SW_SHOW);

	m_leftPane.Create(CDialogPaneLeft::IDD, this);
	m_leftPane.MoveWindow(0, 0, 250, 120);
	m_leftPane.ShowWindow(SW_SHOW);

	m_rightPane.Create(CDialogPaneRight::IDD, this);
	m_rightPane.MoveWindow(0, 0, 160, 120);
	m_rightPane.ShowWindow(SW_SHOW);

	m_workArea.Create(CDlgWorkArea::IDD, this);
	m_workArea.ShowWindow(SW_SHOW);

	m_bottomPane.Create(CDialogPaneBottom::IDD, this);
	m_bottomPane.MoveWindow(0, 0, 160, 200);
	m_bottomPane.ShowWindow(SW_SHOW);
}

CRect CMFCApplication2Dlg::CalcWorkArea()
{
	CRect rcPane;

	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rcWorkArea(rcClient);

	m_topPane.GetClientRect(&rcPane);
	rcWorkArea.top = rcClient.top + rcPane.Height();

	m_leftPane.GetClientRect(&rcPane);
	rcWorkArea.left = rcClient.left + rcPane.Width();

	m_bottomPane.GetClientRect(&rcPane);
	CRect rcPane2;
	m_statusBar.GetClientRect(&rcPane2);
	rcWorkArea.bottom = rcClient.bottom - rcPane.Height() - rcPane2.Height();

	m_rightPane.GetClientRect(&rcPane);
	rcWorkArea.right = rcClient.right - rcPane.Width();

	return rcWorkArea;
}

void CMFCApplication2Dlg::OnWorkAreaChanged(CWnd* pWnd)
{
	ReposePanes();
}

void CMFCApplication2Dlg::ReposePanes()
{
	if (!IsWindow(m_topPane.GetSafeHwnd())) return;

	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rcToppane(rcClient);
	rcToppane.bottom = rcToppane.top + winpos.toppane_hgt;
	m_topPane.MoveWindow(rcToppane);
	m_topPane.UpdateWindow();

	CRect rcStatusbar(rcClient);
	rcStatusbar.top = rcStatusbar.bottom - winpos.statusbar_hgt;
	rcStatusbar.bottom = rcClient.bottom - 1;
	m_statusBar.MoveWindow(rcStatusbar);
	m_statusBar.UpdateWindow();

	CRect rcLeftpane(rcClient);
	rcLeftpane.top = rcToppane.bottom+1;
	rcLeftpane.bottom = rcStatusbar.top-1;

	CRect rcPane;
	m_leftPane.GetClientRect(&rcPane);
	rcLeftpane.right = rcLeftpane.left+rcPane.Width();
	m_leftPane.MoveWindow(&rcLeftpane);
	m_leftPane.UpdateWindow();

	CRect rcBottompane(rcClient);
	rcBottompane.bottom = rcStatusbar.top-1;

	m_bottomPane.GetClientRect(&rcPane);
	rcBottompane.top = rcBottompane.bottom - rcPane.Height();

	rcBottompane.left = rcLeftpane.right;
	m_bottomPane.MoveWindow(&rcBottompane);
	//m_bottomPane.InvalidateRect(NULL);
	m_bottomPane.UpdateWindow();
	
	CRect rcRightpane(rcClient);
	rcRightpane.top = rcToppane.bottom;
	rcRightpane.bottom = rcBottompane.top;
	m_rightPane.GetClientRect(&rcPane);
	rcRightpane.left = rcRightpane.right - 200/*rcPane.Width()*/;
	m_rightPane.MoveWindow(&rcRightpane);
	m_rightPane.UpdateWindow();

	m_rcWorkArea = CalcWorkArea();
	m_workArea.MoveWindow(&m_rcWorkArea);

}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect    rcClip;

		dc.GetClipBox(rcClip);

		if (rcClip.IsRectEmpty()) return;

		CMemDC mdc(dc,rcClip);

		mdc.GetDC().FillSolidRect(rcClip, RGB(200, 200, 200));
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication2Dlg::OnSize(UINT nType, int cx, int cy)
{
	// TODO:  在此处添加消息处理程序代码
	CDialogEx::OnSize(nType, cx, cy);

	int cxFrame = GetSystemMetrics(SM_CXFRAME);
	int cyFrame = GetSystemMetrics(SM_CYFRAME);

	int cyCaption = GetSystemMetrics(SM_CYCAPTION);
	int cyBorder = GetSystemMetrics(SM_CYBORDER);
	int cyEdge = GetSystemMetrics(SM_CYEDGE);
	int cxEdge = GetSystemMetrics(SM_CXEDGE);
	//

	CRect rc = GetVisibleBound();

	//rc.DeflateRect(cxFrame + cxEdge + 1, cyFrame + cyEdge + 1);
	//rc.DeflateRect(cxFrame + cxEdge+1, cyFrame +cyEdge+1);
	//
	CRgn rgn;
	BOOL ok = rgn.CreateRectRgnIndirect(&rc);
	if (ok) SetWindowRgn(rgn, TRUE);

	rgn.Detach();

	ReposePanes();

	UpdateWindow();

}

void CMFCApplication2Dlg::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	RECT &rc = lpncsp->rgrc[0];

	int cyFrame   =  GetSystemMetrics(SM_CYFRAME);
	int cyCaption =  GetSystemMetrics(SM_CYCAPTION);
	int cyBorder  =  GetSystemMetrics(SM_CYBORDER);
	
	CRect rcVisual = GetVisibleBound();
	
	if (winpos.caption_hgt > cyCaption)
		rc.top += (winpos.caption_hgt - cyCaption - cyFrame);

	CDialogEx::OnNcCalcSize(bCalcValidRects, lpncsp);
}

CRect   CMFCApplication2Dlg::GetVisibleBound()
{
	CRect rc;
	int cyCaption = GetSystemMetrics(SM_CYCAPTION);

	int cyEdge    = 0;
	int cxEdge    = 0;
	int cxFrame   = 0;
	int cyFrame   = 0;
	int cxBorder  = 0;
	int cyBorder  = 0;

	DWORD dwExCode = GetWindowLong(GetSafeHwnd(),GWL_EXSTYLE);
	DWORD dwCode = GetWindowLong(GetSafeHwnd(), GWL_STYLE);

	if (dwExCode & WS_EX_WINDOWEDGE){
		cyEdge = GetSystemMetrics(SM_CYEDGE);
		cxEdge = GetSystemMetrics(SM_CXEDGE);
	}

	if (dwCode & WS_THICKFRAME){
		cxFrame = GetSystemMetrics(SM_CXFRAME);
		cyFrame = GetSystemMetrics(SM_CYFRAME);
	}

	if (dwCode & WS_BORDER){
		cxBorder = GetSystemMetrics(SM_CXBORDER);
		cyBorder = GetSystemMetrics(SM_CYBORDER);
	}

	if (winpos.caption_hgt < cyCaption){
		GetWindowRect(&rc);

		rc.OffsetRect(-rc.left, -rc.top);
		rc.left  = rc.left  + cxEdge  + cxFrame +1;
		rc.right = rc.right - cxEdge  - cxFrame -1;
		rc.top   = rc.top   + cyFrame + cyEdge + cyCaption + 4 - winpos.caption_hgt;
		rc.bottom = rc.bottom - cyEdge - cyFrame -1;
	}
	else{
		GetWindowRect(&rc);

		rc.OffsetRect(-rc.left, -rc.top);
		rc.left  = rc.left + cxEdge + cxFrame+1 ;
		rc.right = rc.right - cxEdge - cxFrame-1;
		rc.top   = rc.top + cyFrame + cyEdge;
		rc.bottom = rc.bottom - cyEdge - cyFrame-1;
	}

	return rc;
}

void CMFCApplication2Dlg::OnNcPaint()
{
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnNcPaint()
	//CDialogEx::OnNcPaint();
	CRect rcVisibleBound = GetVisibleBound();

	int cxFrame = GetSystemMetrics(SM_CXFRAME);
	int cyFrame = GetSystemMetrics(SM_CYFRAME);

	int cyCaption = GetSystemMetrics(SM_CYCAPTION);
	int cyBorder  =  GetSystemMetrics(SM_CYBORDER);
	int cxBorder  =  GetSystemMetrics(SM_CXBORDER);
	int cxEdge = GetSystemMetrics(SM_CXEDGE);
	int cyEdge = GetSystemMetrics(SM_CYEDGE);

	CRect rcWindow1, rcClient, rcNCTop, rcBorderTop, rcBorderLeft, rcBorderRight, rcBorderBottom;

	//GetWindowRect(&rcWindow1);
	GetClientRect(&rcClient);

	rcNCTop.SetRectEmpty();
	rcNCTop.top   = rcVisibleBound.top;
	rcNCTop.left  = rcVisibleBound.left;
	rcNCTop.right = rcVisibleBound.right;
	rcNCTop.bottom = rcNCTop.top + winpos.caption_hgt;

	CDC* pWindowDC = GetWindowDC();
	pWindowDC->FillSolidRect(&rcNCTop, RGB(123, 23, 34));

	m_pImage->Draw(pWindowDC->GetSafeHdc(), rcVisibleBound.left + 3, rcVisibleBound.top+3, 26, 26, 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight());

	rcBorderTop.SetRectEmpty();
	rcBorderTop.right = rcVisibleBound.right;
	rcBorderTop.bottom = rcVisibleBound.top+1;
	pWindowDC->FillSolidRect(&rcBorderTop, RGB(123, 123, 134));

	rcBorderLeft.SetRectEmpty();
	rcBorderLeft.left = rcVisibleBound.left;
	rcBorderLeft.top =  rcVisibleBound.top;
	rcBorderLeft.right = rcVisibleBound.left + 2;
	rcBorderLeft.bottom = rcVisibleBound.bottom;

	pWindowDC->FillSolidRect(&rcBorderLeft, RGB(123, 123, 34));

	rcBorderRight.SetRectEmpty();
	rcBorderRight.top = rcVisibleBound.top;
	rcBorderRight.left = (rcVisibleBound.right - 2);
	rcBorderRight.right = rcVisibleBound.right;
	rcBorderRight.bottom = rcVisibleBound.bottom;

	pWindowDC->FillSolidRect(&rcBorderRight, RGB(123, 123, 34));

	rcBorderBottom.SetRectEmpty();
	
	rcBorderBottom.right = rcVisibleBound.right;
	rcBorderBottom.bottom = rcVisibleBound.bottom;
	rcBorderBottom.top = rcBorderBottom.bottom -2;

	pWindowDC->FillSolidRect(&rcBorderBottom, RGB(123, 123, 34));

	//////////////////////////////////////////////////////////////////////////
	CBitmap* pBitmap = new CBitmap;
	CBitmap* pOldBitmap;
	CDC* pDisplayMemDC = new CDC();
	pDisplayMemDC->CreateCompatibleDC(pWindowDC);

	CRect rtButtons;
	rtButtons.left = rcVisibleBound.right - cxFrame - cxBorder - 24;
	rtButtons.top = rcVisibleBound.top + 3;
	rtButtons.right = rtButtons.left + 24;
	rtButtons.bottom = rtButtons.top + 24;
	m_rtButtExit = rtButtons;

	pBitmap->LoadBitmap(IDB_BITMAP_EXIT_NORMAL);
	pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);

	pWindowDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);

	pDisplayMemDC->SelectObject(pOldBitmap);
	pBitmap->DeleteObject();
	//////////////////////////////////////////////////////////////////////////
	rtButtons.left = m_rtButtExit.left - cxFrame - cxBorder - 24;
	rtButtons.top = rcVisibleBound.top + 3;
	rtButtons.right = rtButtons.left + 24;
	rtButtons.bottom = rtButtons.top + 24;
	m_rtButtMax = rtButtons;

	if (!IsZoomed())
		pBitmap->LoadBitmap(IDB_BITMAP_MAX_NORMAL);
	else
		pBitmap->LoadBitmap(IDB_BITMAP_RESTORE_NORMAL);

	pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);

	pWindowDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);

	pDisplayMemDC->SelectObject(pOldBitmap);
	pBitmap->DeleteObject();
	//////////////////////////////////////////////////////////////////////////
	rtButtons.left = m_rtButtMax.left - cxFrame - cxBorder - 24;
	rtButtons.top = rcVisibleBound.top + 3;
	rtButtons.right = rtButtons.left + 24;
	rtButtons.bottom = rtButtons.top + 24;
	m_rtButtMin = rtButtons;

	pBitmap->LoadBitmap(IDB_BITMAP_MIN_NORMAL);
	pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);

	pWindowDC->BitBlt(rtButtons.left, rtButtons.top, rtButtons.Width(), rtButtons.Height(), pDisplayMemDC, 0, 0, SRCCOPY);

	pDisplayMemDC->SelectObject(pOldBitmap);
	pBitmap->DeleteObject();
	//////////////////////////////////////////////////////////////////////////
	
	pWindowDC->SetTextColor(RGB(220, 200, 200));
	pWindowDC->SetBkMode(TRANSPARENT);
	CFont* oldFont = pWindowDC->SelectObject(&m_fontTitle);
	
	pWindowDC->TextOut(rcVisibleBound.left + 42, rcVisibleBound.top+6, _T("转捩平台无线接收机地面控制软件"));
	pWindowDC->SelectObject(oldFont);
	//////////////////////////////////////////////////////////////////////////
	ReleaseDC(pDisplayMemDC);
	delete pDisplayMemDC;
	delete pBitmap;

	//m_topPane.InvalidateRect(NULL);
	m_topPane.UpdateWindow();
}


BOOL CMFCApplication2Dlg::OnNcActivate(BOOL bActive)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	
	return CDialogEx::OnNcActivate(bActive);
}


LRESULT CMFCApplication2Dlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO:  在此添加专用代码和/或调用基类

	LRESULT lrst = CDialogEx::DefWindowProc(message, wParam, lParam);
	if (!::IsWindow(m_hWnd))
		return lrst;

 	if (//message == WM_MOVE
 		// message == WM_PAINT||
		//message == WM_NCPAINT||
		 message == WM_NCACTIVATE
		/*|| message == WM_NOTIFY*/)
	{
		OnNcPaint();
	}
	return lrst;
}


void CMFCApplication2Dlg::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CDC* pDC = GetWindowDC();
	CDC* pDisplayMemDC = new CDC;
	pDisplayMemDC->CreateCompatibleDC(pDC);
	CBitmap* pBitmap = new CBitmap;
	CBitmap* pOldBitmap;
	CRect rtWnd, rtButton;

	if (pDC)
	{
		GetWindowRect(&rtWnd);
		point.Offset(-rtWnd.left, -rtWnd.top);
		//关闭button
		if (m_rtButtExit.PtInRect(point))
			pBitmap->LoadBitmap(IDB_BITMAP_EXIT_HIGHT);
		else
			pBitmap->LoadBitmap(IDB_BITMAP_EXIT_NORMAL);
		rtButton = m_rtButtExit;
		//rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

		//最大化/恢复button
		if (m_rtButtMax.PtInRect(point))
		{
			if (IsZoomed())
				pBitmap->LoadBitmap(IDB_BITMAP_RESTORE_HIGHT);
			else
				pBitmap->LoadBitmap(IDB_BITMAP_MAX_HIGHT);
		}
		else
		{
			if (IsZoomed())
				pBitmap->LoadBitmap(IDB_BITMAP_RESTORE_NORMAL);
			else
				pBitmap->LoadBitmap(IDB_BITMAP_MAX_NORMAL);
		}
		rtButton = m_rtButtMax;
		//rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();

		//最小化button
		if (m_rtButtMin.PtInRect(point))
			pBitmap->LoadBitmap(IDB_BITMAP_MIN_HIGHT);
		else
			pBitmap->LoadBitmap(IDB_BITMAP_MIN_NORMAL);
		rtButton = m_rtButtMin;
		//rtButton.OffsetRect(-rtWnd.left, -rtWnd.top);
		pOldBitmap = (CBitmap*)pDisplayMemDC->SelectObject(pBitmap);
		pDC->BitBlt(rtButton.left, rtButton.top, rtButton.Width(), rtButton.Height(), pDisplayMemDC, 0, 0, SRCCOPY);
		pDisplayMemDC->SelectObject(pOldBitmap);
		pBitmap->DeleteObject();
	}

	ReleaseDC(pDisplayMemDC);
	ReleaseDC(pDC);
	delete pDisplayMemDC;
	delete pBitmap;

	CDialogEx::OnNcMouseMove(nHitTest, point);
}


void CMFCApplication2Dlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect rtWnd;
	GetWindowRect(&rtWnd);
	point.Offset(-rtWnd.left, -rtWnd.top);

	if (m_rtButtExit.PtInRect(point))
	{
		SendMessage(WM_CLOSE);
	}
	else if (m_rtButtMin.PtInRect(point))
	{
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, MAKELPARAM(point.x, point.y));
	}
	else if (m_rtButtMax.PtInRect(point))
	{
		if (IsZoomed())
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, MAKELPARAM(point.x, point.y));
		else
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, MAKELPARAM(point.x, point.y));
			//Invalidate();
		}
	}
	
	CDialogEx::OnNcLButtonDown(nHitTest, point);

}


void CMFCApplication2Dlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//lpMMI->ptMinTrackSize.x = 120 + (24+10) * 3;
	int cxFrame = GetSystemMetrics(SM_CXFRAME);
	int cyFrame = GetSystemMetrics(SM_CYFRAME);
	int cyEdge = GetSystemMetrics(SM_CYEDGE);
	int cxEdge = GetSystemMetrics(SM_CXEDGE);
	RECT rcWorkArea;
	int ret = ::SystemParametersInfo(SPI_GETWORKAREA, sizeof(rcWorkArea), &rcWorkArea, 0);
	
	CRect rc = GetVisibleBound();

	lpMMI->ptMinTrackSize.x = 700;	//x宽度
	lpMMI->ptMinTrackSize.y = 400;	//y高度

	lpMMI->ptMaxPosition.x = -rc.left;
	lpMMI->ptMaxPosition.y = -rc.top;
	lpMMI->ptMaxTrackSize.x = rcWorkArea.right - rcWorkArea.left + (cxFrame + cxEdge + 1) * 2;
	lpMMI->ptMaxTrackSize.y = rcWorkArea.bottom - rcWorkArea.top + rc.top + cyFrame + 1 + cyEdge;

	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CMFCApplication2Dlg::OnNcLButtonDblClk(UINT nHitTest, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	
	CRect rtWnd;
	GetWindowRect(&rtWnd);
	point.Offset(-rtWnd.left, -rtWnd.top);

	if (IsZoomed())
		SendMessage(WM_SYSCOMMAND, SC_RESTORE, MAKELPARAM(point.x, point.y));
	else
	{
		//ShowWindow(SW_SHOWMAXIMIZED);
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, MAKELPARAM(point.x, point.y));
		//Invalidate();
	}

	
}


void CMFCApplication2Dlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2Dlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2Dlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	theApp.PostThreadMessage(WM_QUIT, 0, 0);
	//__super::OnClose();
}


void CMFCApplication2Dlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	__super::OnWindowPosChanged(lpwndpos);
	
	// TODO:  在此处添加消息处理程序代码
	//if (!::IsWindow(m_wndLogo.GetSafeHwnd())) return;

	//CRect rcWindow;
	//GetWindowRect(&rcWindow);
	//m_wndLogo.SetWindowPos(&wndTop, rcWindow.left+4+1+4, rcWindow.top+4+1+8, 44, 44, SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOACTIVATE);
	//m_wndLogo.SetWindowPos(&wndTop, rcWindow.left + 4 + 1 + 4, rcWindow.top +2, 16, 6, SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOACTIVATE);
}

void CMFCApplication2Dlg::PrintWnd(CWnd* pWnd2Print,CString strFile)
{
	// TODO:  在此添加控件通知处理程序代码
	if (pWnd2Print == NULL || !::IsWindow(pWnd2Print->m_hWnd)) return;

	CString strPath;
	SYSTEMTIME t;	

	CRect rcClient;
	pWnd2Print->GetClientRect(&rcClient);

	CDC* pDC = pWnd2Print->GetDC();
	HDC memDC = ::CreateCompatibleDC(pDC->GetSafeHdc());

	int cx = rcClient.Width();
	int cy = rcClient.Height();

	HBITMAP bmp = ::CreateCompatibleBitmap(pDC->GetSafeHdc(), cx, cy);

	HBITMAP oldbmp = NULL;
	oldbmp = (HBITMAP)::SelectObject(memDC, bmp);

	::BitBlt(memDC, 0, 0, cx, cy, pDC->GetSafeHdc(), 0, 0, SRCCOPY);

	CImage tempImage;
	tempImage.Attach(bmp);
	tempImage.Save(strFile);

	::SelectObject(memDC, oldbmp);

}

CWnd * CMFCApplication2Dlg::GetWorkAreaWnd()
{	
	return &m_workArea;
}

LRESULT CMFCApplication2Dlg::OnComMsgCom(WPARAM wParam, LPARAM lParam)
{
	msgdata * msg = (msgdata *)wParam;
	//////////////////////////////////////////////////////////////////////////
	int msgid = msg->id();

	delete msg;

	return 0;
}

BOOL CMFCApplication2Dlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	return TRUE;

	return __super::OnEraseBkgnd(pDC);
}
