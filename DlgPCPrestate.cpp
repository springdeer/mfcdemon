// DlgPCPrestate.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgPCPrestate.h"
#include "afxdialogex.h"


// CDlgPCPrestate 对话框

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


// CDlgPCPrestate 消息处理程序


void CDlgPCPrestate::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CDlgPCPrestate::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
}


void CDlgPCPrestate::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	dc.TextOutA(10, 10, _T("afsadfasdf"));
}
