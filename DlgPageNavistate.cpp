// DlgPageNavistate.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgPageNavistate.h"
#include "afxdialogex.h"


// CDlgPageNavistate �Ի���

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


// CDlgPageNavistate ��Ϣ�������


void CDlgPageNavistate::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CDlgPageNavistate::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
}
