// DlgPageRcvrMon.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgPageRcvrMon.h"
#include "afxdialogex.h"


// CDlgPageRcvrMon 对话框

IMPLEMENT_DYNAMIC(CDlgPageRcvrMon, CDialogEx)

CDlgPageRcvrMon::CDlgPageRcvrMon(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPageRcvrMon::IDD, pParent)
{

}

CDlgPageRcvrMon::~CDlgPageRcvrMon()
{
}

void CDlgPageRcvrMon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPageRcvrMon, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgPageRcvrMon::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgPageRcvrMon::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgPageRcvrMon 消息处理程序


void CDlgPageRcvrMon::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CDlgPageRcvrMon::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
}
