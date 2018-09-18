// StatusPane.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "StatusPane.h"
#include "afxdialogex.h"


// CStatusPane �Ի���

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


// CStatusPane ��Ϣ�������


void CStatusPane::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

BOOL CStatusPane::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	CFont font1;
	font1.CreateFontA(12, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnRunTime.Init(vector<string>(), (HFONT)font1.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnRunTime.ShowText(_T("����ʱ��:"));

	CFont font2;
	font2.CreateFontA(12, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnHistTime.Init(vector<string>(), (HFONT)font2.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnHistTime.ShowText(_T("�ۼ�����ʱ��:"));

	CFont font3;
	font3.CreateFontA(12, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnRemoteTime.Init(vector<string>(), (HFONT)font3.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnRemoteTime.ShowText(_T("�����豸����ʱ��:"));

	CFont font4;
	font4.CreateFontA(12, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnUTC.Init(vector<string>(), (HFONT)font4.Detach(), CTextStateButton::eTSBS_STATIC);
	m_btnUTC.ShowText(_T("UTCʱ��:2018-03-05 9:27:45"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CStatusPane::OnBnClickedButtonRuntime()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


BOOL CStatusPane::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	return CDialogEx::OnEraseBkgnd(pDC);
}
