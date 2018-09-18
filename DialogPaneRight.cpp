// DialogPaneLeft.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DialogPaneLeft.h"
#include "afxdialogex.h"
#include "MFCApplication2Dlg.h"
#include "DialogPaneRight.h"
#include "msgdef.h"
#include "Protobuffer.h"
// CDialogPaneRight 对话框

IMPLEMENT_DYNAMIC(CDialogPaneRight, CDialogEx)

CDialogPaneRight::CDialogPaneRight(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogPaneRight::IDD, pParent)
{
	m_sizingCX = 3;
}

CDialogPaneRight::~CDialogPaneRight()
{
}

void CDialogPaneRight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_B4STATE, m_btnVB4State);
	DDX_Control(pDX, IDC_BUTTON_D1STATE, m_btnVD1State);
	DDX_Control(pDX, IDC_BUTTON_B3STATE, m_btnB3State);
	DDX_Control(pDX, IDC_BUTTON_B2STATE, m_btnVB2State);
	DDX_Control(pDX, IDC_BUTTON_PLUSB4VOLT, m_btnB4Tip);
	DDX_Control(pDX, IDC_BUTTON_PLUSD1VOLT2, m_btnD1Tip);
	DDX_Control(pDX, IDC_BUTTON_PLUSB3VOLT3, m_btnB3Tip);
	DDX_Control(pDX, IDC_BUTTON_PLUSB2VOLT4, m_btnB2Tip);
	DDX_Control(pDX, IDC_BUTTON_KEYRESET1_IND, m_btnHGJB1Ind);
	DDX_Control(pDX, IDC_BUTTON_FIRE1_IND, m_btnYJFDJDHInd);
	DDX_Control(pDX, IDC_BUTTON_SAFEUNLOCK_IND, m_btnABJGJBInd);
	DDX_Control(pDX, IDC_BUTTON_SAFERESET_IND, m_btnABJGFWInd);
	DDX_Control(pDX, IDC_BUTTON_KEYRESET1_STATE, m_btnKeyReset1State);
	DDX_Control(pDX, IDC_BUTTON_FIRE1_STATE, m_btnFire1State);
	DDX_Control(pDX, IDC_BUTTON_SECUNLOCK_STATE, m_btnSecUnlockState);
	DDX_Control(pDX, IDC_BUTTON_SAFERESET_STATE, m_btnSafeResetState);
}


BEGIN_MESSAGE_MAP(CDialogPaneRight, CDialogEx)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_BUTTON_UNPLUS_D1, &CDialogPaneRight::OnBnClickedButtonUnplusD1)
	ON_BN_CLICKED(IDC_BUTTON_STOPSHOW, &CDialogPaneRight::OnBnClickedButtonStopshow)
	ON_BN_CLICKED(IDC_BUTTON_SAVEFILE, &CDialogPaneRight::OnBnClickedButtonSavefile)
	ON_BN_CLICKED(IDC_BUTTON_PLUSB4VOLT, &CDialogPaneRight::OnBnClickedButtonPlusb4volt)
	ON_BN_CLICKED(IDC_BUTTON_ALLOWSHOW, &CDialogPaneRight::OnBnClickedButtonAllowshow)
	ON_BN_CLICKED(IDC_BUTTON_CLEARSHOW, &CDialogPaneRight::OnBnClickedButtonClearshow)
	ON_BN_CLICKED(IDC_BUTTON_PLUSB2VOLT4, &CDialogPaneRight::OnBnClickedButtonPlusb2volt4)
	ON_BN_CLICKED(IDC_BUTTON_KEYRESET1_IND, &CDialogPaneRight::OnBnClickedButtonKeyreset1Ind)
	ON_BN_CLICKED(IDC_BUTTON_KETYRESET, &CDialogPaneRight::OnBnClickedButtonKetyreset)
	ON_BN_CLICKED(IDC_BUTTON_UNPLUS_B4, &CDialogPaneRight::OnBnClickedButtonUnplusB4)
	ON_BN_CLICKED(IDC_BUTTON_UNPLUS_B3, &CDialogPaneRight::OnBnClickedButtonUnplusB3)
	ON_BN_CLICKED(IDC_BUTTON_UNPLUS_B2, &CDialogPaneRight::OnBnClickedButtonUnplusB2)
END_MESSAGE_MAP()


// CDialogPaneRight 消息处理程序

void CDialogPaneRight::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rcBox,rcClient;
	GetClientRect(&rcBox);

	dc.GetClipBox(rcBox);
	if (rcBox.IsRectEmpty()) return;

	CMemDC memdc(dc, rcBox);
	CDC& refdc = memdc.GetDC();

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
}


void CDialogPaneRight::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	UpdateWindow();

}

void CDialogPaneRight::ShowCursor(CPoint point)
{
	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rcSizingLine(&rcClient);
	rcSizingLine.right = rcSizingLine.left + 3;
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

void CDialogPaneRight::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//ShowCursor(point);

	//bool bSizing = m_bSizingBorder && m_bLeftButtonDown;
	//while (bSizing){
	//	SetCapture();

	//	CRect rcClient;
	//	GetClientRect(&rcClient);

	//	if (rcClient.right - point.x  > 200 || rcClient.right-point.x < 135) break;

	//	rcClient.left = rcClient.left + point.x;

	//	TRACE("point x %d\n", point.x);

	//	MapWindowPoints(GetParent(), &rcClient);

	//	MoveWindow(&rcClient);

	//	CDialogFrame * pFrame = (CDialogFrame *)(CMFCApplication2Dlg*)GetParent();
	//	pFrame->OnWorkAreaChanged(this);

	//	break;
	//}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CDialogPaneRight::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	ShowCursor(point);

	m_bLeftButtonDown = true;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDialogPaneRight::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_bLeftButtonDown = false;
	bool bSizing = m_bSizingBorder && m_bLeftButtonDown;

	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}


BOOL CDialogPaneRight::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	return TRUE;

	return CDialogEx::OnEraseBkgnd(pDC);
}


void CDialogPaneRight::OnBnClickedButtonUnplusD1()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!theApp.IsCommConnected()){
		::MessageBox(GetSafeHwnd(), _T("未连接远程控制台."), _T("操作提示"), MB_OK | MB_ICONSTOP);
		return;
	}

	DisconnectPlusD1 fCommand;
	fCommand.type = theApp.GetTransmiter()->GetChan();

	theApp.GetTransmiter()->MailCommand(_REQ_DISCONNECT_PLUSD1, &fCommand);
}


void CDialogPaneRight::OnBnClickedButtonStopshow()
{
	// TODO:  在此添加控件通知处理程序代码
	CMFCApplication2Dlg * pWnd = (CMFCApplication2Dlg *)AfxGetMainWnd();
	CDialogPaneBottom *pPane = pWnd->GetBottomPane();

	if (pPane) pPane->EnableShow(FALSE);
}


void CDialogPaneRight::OnBnClickedButtonSavefile()
{
	// TODO:  在此添加控件通知处理程序代码
}

void CDialogPaneRight::InitUi()
{
	m_btnB3State.Init(IMAGE_VOLSTATE, 3);
	m_btnVD1State.Init(IMAGE_VOLSTATE, 3);
	m_btnVB4State.Init(IMAGE_VOLSTATE, 3);
	m_btnVB2State.Init(IMAGE_VOLSTATE, 3);

	m_btnKeyReset1State.Init(IMAGE_VOLSTATE, 3);
	m_btnFire1State.Init(IMAGE_VOLSTATE, 3);
	m_btnSecUnlockState.Init(IMAGE_VOLSTATE, 3);
	m_btnSafeResetState.Init(IMAGE_VOLSTATE, 3);

	CFont font1;
	font1.CreateFontA(15, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnB4Tip.Init(vector<string>(), (HFONT)font1.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnB4Tip.SetTextColor(RGB(64, 62, 23));
	m_btnB4Tip.ShowText(_T("+B4电压状态:"));

	CFont font2;
	font2.CreateFontA(15, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnD1Tip.Init(vector<string>(), (HFONT)font2.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnD1Tip.SetTextColor(RGB(64, 62, 23));
	m_btnD1Tip.ShowText(_T("+D1电压状态:"));

	CFont font3;
	font3.CreateFontA(15, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnB3Tip.Init(vector<string>(), (HFONT)font3.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnB3Tip.SetTextColor(RGB(64, 62, 23));
	m_btnB3Tip.ShowText(_T("+B3电压状态:"));

	CFont font4;
	font4.CreateFontA(15, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnB2Tip.Init(vector<string>(), (HFONT)font4.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnB2Tip.SetTextColor(RGB(64, 62, 23));
	m_btnB2Tip.ShowText(_T("+B2电压状态:"));

	CFont font5;
	font5.CreateFontA(15, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnHGJB1Ind.Init(vector<string>(), (HFONT)font5.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnHGJB1Ind.SetTextColor(RGB(64, 62, 23));
	m_btnHGJB1Ind.ShowText(_T("火工解保1指示:"));

	CFont font6;
	font6.CreateFontA(15, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnYJFDJDHInd.Init(vector<string>(), (HFONT)font6.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnYJFDJDHInd.SetTextColor(RGB(64, 62, 23));
	m_btnYJFDJDHInd.ShowText(_T("一级发动机点火指示:"));
	
	CFont font7;
	font7.CreateFontA(15, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnABJGJBInd.Init(vector<string>(), (HFONT)font7.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnABJGJBInd.SetTextColor(RGB(64, 62, 23));
	m_btnABJGJBInd.ShowText(_T("安保机构解保指示:"));

	CFont font8;
	font8.CreateFontA(15, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnABJGFWInd.Init(vector<string>(), (HFONT)font8.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnABJGFWInd.SetTextColor(RGB(64, 62, 23));
	m_btnABJGFWInd.ShowText(_T("安保机构复位指示:"));
	
}

BOOL CDialogPaneRight::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUi();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDialogPaneRight::OnBnClickedButtonPlusb4volt()
{
	// TODO:  在此添加控件通知处理程序代码
	static int i = 0;
	m_btnVB4State.ShowState(i++ % 3);
}


void CDialogPaneRight::OnBnClickedButtonAllowshow()
{
	// TODO:  在此添加控件通知处理程序代码
	CMFCApplication2Dlg * pWnd = (CMFCApplication2Dlg *)AfxGetMainWnd();
	CDialogPaneBottom *pPane = pWnd->GetBottomPane();

	if (pPane) pPane->EnableShow(TRUE);
}


void CDialogPaneRight::OnBnClickedButtonClearshow()
{
	// TODO:  在此添加控件通知处理程序代码
	CMFCApplication2Dlg * pWnd = (CMFCApplication2Dlg *)AfxGetMainWnd();
	CDialogPaneBottom *pPane = pWnd->GetBottomPane();

	if (pPane) pPane->ClearData();
}


void CDialogPaneRight::OnBnClickedButtonPlusb2volt4()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CDialogPaneRight::OnBnClickedButtonKeyreset1Ind()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CDialogPaneRight::OnBnClickedButtonKetyreset()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!theApp.IsCommConnected()){
		::MessageBox(GetSafeHwnd(), _T("未连接远程控制台."), _T("操作提示"), MB_OK | MB_ICONSTOP);
		return;
	}

	SecureReset fCommand;
	fCommand.type = theApp.GetTransmiter()->GetChan();

	theApp.GetTransmiter()->MailCommand(_REQ_SECURE_RESET, &fCommand);
}


void CDialogPaneRight::OnBnClickedButtonUnplusB4()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!theApp.IsCommConnected()){
		::MessageBox(GetSafeHwnd(), _T("未连接远程控制台."), _T("操作提示"), MB_OK | MB_ICONSTOP);
		return;
	}

	DisconnectPlusB4 fCommand;
	fCommand.type = theApp.GetTransmiter()->GetChan();

	theApp.GetTransmiter()->MailCommand(_REQ_DISCONNECT_PLUSB4, &fCommand);
}


void CDialogPaneRight::OnBnClickedButtonUnplusB3()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!theApp.IsCommConnected()){
		::MessageBox(GetSafeHwnd(), _T("未连接远程控制台."), _T("操作提示"), MB_OK | MB_ICONSTOP);
		return;
	}

	DisconnectPlusB3 fCommand;
	fCommand.type = theApp.GetTransmiter()->GetChan();

	theApp.GetTransmiter()->MailCommand(_REQ_DISCONNECT_PLUSB3, &fCommand);
}


void CDialogPaneRight::OnBnClickedButtonUnplusB2()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!theApp.IsCommConnected()){
		::MessageBox(GetSafeHwnd(), _T("未连接远程控制台."), _T("操作提示"), MB_OK | MB_ICONSTOP);
		return;
	}

	DisconnectPlusB2 fCommand;
	fCommand.type = theApp.GetTransmiter()->GetChan();

	theApp.GetTransmiter()->MailCommand(_REQ_DISCONNECT_PLUSB2, &fCommand);
}
