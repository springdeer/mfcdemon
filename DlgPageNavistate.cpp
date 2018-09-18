// DlgPageNavistate.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgPageNavistate.h"
#include "afxdialogex.h"


// CDlgPageNavistate 对话框

IMPLEMENT_DYNAMIC(CDlgPageNavistate, CDialogEx)

CDlgPageNavistate::CDlgPageNavistate(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPageNavistate::IDD, pParent)
{

}

CDlgPageNavistate::~CDlgPageNavistate()
{
}

void CDlgPageNavistate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPageNavistate, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgPageNavistate::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgPageNavistate::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgPageNavistate 消息处理程序


void CDlgPageNavistate::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CDlgPageNavistate::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
}
