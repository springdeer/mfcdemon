// DlgPageRcvrMon.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgPageRcvrMon.h"
#include "afxdialogex.h"


// CDlgPageRcvrMon �Ի���

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


// CDlgPageRcvrMon ��Ϣ�������


void CDlgPageRcvrMon::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CDlgPageRcvrMon::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
}
