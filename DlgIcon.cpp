// DlgIcon.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgIcon.h"
#include "afxdialogex.h"
#include "MFCApplication2Dlg.h"

// CDlgIcon �Ի���

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


// CDlgIcon ��Ϣ�������


BOOL CDlgIcon::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_btnImage.Init(IMAGE_logo, 4);
	

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgIcon::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (IsWindow(m_btnImage.GetSafeHwnd())) m_btnImage.MoveWindow(0, 0, cx, cy);
	// TODO:  �ڴ˴������Ϣ����������
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
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	//if (m_pImage)
	//	m_pImage->Draw(dc.GetSafeHdc(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight());
}


void CDlgIcon::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMFCApplication2Dlg* pWnd = (CMFCApplication2Dlg*)AfxGetMainWnd();
	pWnd->ReposePanes();
}
