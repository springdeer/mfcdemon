// DlgPageCPCheck.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgPageCPCheck.h"
#include "afxdialogex.h"


// CDlgPageCPCheck �Ի���

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


// CDlgPageCPCheck ��Ϣ�������


void CDlgPageCPCheck::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CDlgPageCPCheck::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
}
