// DlgPCPrestate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgPCPrestate.h"
#include "afxdialogex.h"


// CDlgPCPrestate �Ի���

IMPLEMENT_DYNAMIC(CDlgPCPrestate, CDialogEx)

CDlgPCPrestate::CDlgPCPrestate(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPCPrestate::IDD, pParent)
{

}

CDlgPCPrestate::~CDlgPCPrestate()
{
}

void CDlgPCPrestate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPCPrestate, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgPCPrestate::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgPCPrestate::OnBnClickedCancel)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgPCPrestate ��Ϣ�������


void CDlgPCPrestate::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CDlgPCPrestate::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
}


void CDlgPCPrestate::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	dc.TextOutA(10, 10, _T("afsadfasdf"));
}
