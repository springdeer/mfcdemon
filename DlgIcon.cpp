// DlgIcon.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgIcon.h"
#include "afxdialogex.h"
#include "MFCApplication2Dlg.h"

// CDlgIcon 对话框

IMPLEMENT_DYNAMIC(CDlgIcon, CDialogEx)

CDlgIcon::CDlgIcon(CWnd* pParent /*=NULL*/)
: CDialogEx(CDlgIcon::IDD, pParent)
{
	m_pImage = new CImage();

	HRESULT res = m_pImage->Load(IMAGE_logo);

	if (FAILED(res)) { delete m_pImage; m_pImage = NULL; }

}
CDlgIcon::~CDlgIcon()
{
}

void CDlgIcon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btnImage);
}


BEGIN_MESSAGE_MAP(CDlgIcon, CDialogEx)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgIcon::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgIcon 消息处理程序


BOOL CDlgIcon::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_btnImage.Init(IMAGE_logo, 4);
	

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgIcon::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (IsWindow(m_btnImage.GetSafeHwnd())) m_btnImage.MoveWindow(0, 0, cx, cy);
	// TODO:  在此处添加消息处理程序代码
	if (m_rgn.m_hObject != NULL){
		m_rgn.DeleteObject();
	}

	if (m_pImage){
		m_rgn.CreateEllipticRgn(0, 0, m_pImage->GetHeight(), m_pImage->GetHeight());
		SetWindowRgn((HRGN)m_rgn.m_hObject, FALSE);
	}
	
}


void CDlgIcon::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	//if (m_pImage)
	//	m_pImage->Draw(dc.GetSafeHdc(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight());
}


void CDlgIcon::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CMFCApplication2Dlg* pWnd = (CMFCApplication2Dlg*)AfxGetMainWnd();
	pWnd->ReposePanes();
}
