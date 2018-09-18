// DlgPaneBottom.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgBottomStatus.h"
#include "afxdialogex.h"


// CDlgBottomStatus 对话框

IMPLEMENT_DYNAMIC(CDlgBottomStatus, CDialogEx)

CDlgBottomStatus::CDlgBottomStatus(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgBottomStatus::IDD, pParent)
{

}

CDlgBottomStatus::~CDlgBottomStatus()
{
}

void CDlgBottomStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgBottomStatus, CDialogEx)
END_MESSAGE_MAP()


// CDlgBottomStatus 消息处理程序
