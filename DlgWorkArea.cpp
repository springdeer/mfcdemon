// DlgWorkArea.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgWorkArea.h"
#include "afxdialogex.h"


// CDlgWorkArea �Ի���

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


// CDlgWorkArea ��Ϣ�������


void CDlgWorkArea::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	//CRect rcClient;
	//GetClientRect(&rcClient);

	//dc.FillSolidRect(&rcClient, RGB(120, 255, 120));

	dc.TextOut(12, 12, _T("this is a work area!"));
}

BOOL CDlgWorkArea::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rectTab;
	GetClientRect(&rectTab);
	m_tab.Create(CMFCTabCtrl::STYLE_3D_ONENOTE, rectTab, this, 1202, CMFCTabCtrl::LOCATION_BOTTOM);

	m_pageCPCheck.Create(CDlgPageCPCheck::IDD, &m_tab);
	m_pageNaviState.Create(CDlgPageNavistate::IDD, &m_tab);
	m_pageRcvrMon.Create(CDlgPageRcvrMon::IDD, &m_tab);
	m_PCPrestate.Create(CDlgPCPrestate::IDD, &m_tab);

	m_tab.AddTab(&m_PCPrestate, "�����Ԥ��״̬", (UINT)-1, FALSE);
	m_tab.AddTab(&m_pageNaviState, "��ϵ���Ԥ��״̬", (UINT)-1, FALSE);
	m_tab.AddTab(&m_pageCPCheck, "������Լ�����", (UINT)-1, FALSE);
	m_tab.AddTab(&m_pageRcvrMon, "���ջ��������", (UINT)-1, FALSE);

	m_tab.ShowWindow(SW_SHOW);
	m_tab.EnableTabSwap(FALSE);//������ק

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDlgWorkArea::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	*pResult = 0;
}

CWnd * CDlgWorkArea::GetActiveWnd()
{
	return m_tab.GetActiveWnd();
}