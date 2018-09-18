// StatusPane.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "StatusPane.h"
#include "afxdialogex.h"


// CStatusPane 对话框

IMPLEMENT_DYNAMIC(CStatusPane, CDialogEx)

CStatusPane::CStatusPane(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStatusPane::IDD, pParent)
{

}

CStatusPane::~CStatusPane()
{

}

void CStatusPane::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_RUNTIME, m_btnRunTime);
	DDX_Control(pDX, IDC_BUTTON_HISTTIME, m_btnHistTime);
	DDX_Control(pDX, IDC_BUTTON_REMOTETIME, m_btnRemoteTime);
	DDX_Control(pDX, IDC_BUTTON_REMOTETIME2, m_btnUTC);
}


BEGIN_MESSAGE_MAP(CStatusPane, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_SEPERATOR, &CStatusPane::OnBnClickedButtonSeperator)
	ON_BN_CLICKED(IDC_BUTTON_RUNTIME, &CStatusPane::OnBnClickedButtonRuntime)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CStatusPane 消息处理程序


void CStatusPane::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rcClient;
	GetClientRect(&rcClient);
	CRect rcClipBox;

	dc.GetClipBox(&rcClipBox);
	if (rcClipBox.IsRectEmpty()) return;

	CMemDC memdc(dc, rcClipBox);
	CDC& refdc = memdc.GetDC();

	refdc.FillSolidRect(&rcClipBox, RGB(160, 50, 34));
}

void CStatusPane::OnBnClickedButtonSeperator()
{
	// TODO:  在此添加控件通知处理程序代码
}

BOOL CStatusPane::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CFont font1;
	font1.CreateFontA(12, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnRunTime.Init(vector<string>(), (HFONT)font1.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnRunTime.ShowText(_T("运行时间:"));

	CFont font2;
	font2.CreateFontA(12, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnHistTime.Init(vector<string>(), (HFONT)font2.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnHistTime.ShowText(_T("累计运行时间:"));

	CFont font3;
	font3.CreateFontA(12, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnRemoteTime.Init(vector<string>(), (HFONT)font3.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnRemoteTime.ShowText(_T("弹上设备运行时间:"));

	CFont font4;
	font4.CreateFontA(12, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnUTC.Init(vector<string>(), (HFONT)font4.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnUTC.ShowText(_T("UTC时间:2018-03-05 9:27:45"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CStatusPane::OnBnClickedButtonRuntime()
{
	// TODO:  在此添加控件通知处理程序代码
}


BOOL CStatusPane::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	return CDialogEx::OnEraseBkgnd(pDC);
}
