// DlgPageCPCheck.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgPageCPCheck.h"
#include "afxdialogex.h"


// CDlgPageCPCheck 对话框

IMPLEMENT_DYNAMIC(CDlgPageCPCheck, CDialogEx)

CDlgPageCPCheck::CDlgPageCPCheck(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPageCPCheck::IDD, pParent)
{

}

CDlgPageCPCheck::~CDlgPageCPCheck()
{
}

void CDlgPageCPCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPageCPCheck, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgPageCPCheck::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgPageCPCheck::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgPageCPCheck 消息处理程序


void CDlgPageCPCheck::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CDlgPageCPCheck::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
}
