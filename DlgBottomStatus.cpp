// DlgPaneBottom.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgBottomStatus.h"
#include "afxdialogex.h"

// CDlgBottomStatus �Ի���

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
	DDX_Control(pDX, IDC_BUTTON_SEPERATOR, m_btnSeprator1);
	DDX_Control(pDX, IDC_BUTTON_SEPERATOR4, m_btnSeprator2);
	DDX_Control(pDX, IDC_BUTTON_SEPERATOR5, m_btnSeprator3);
}


BEGIN_MESSAGE_MAP(CDlgBottomStatus, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEPERATOR, &CDlgBottomStatus::OnBnClickedButtonSeperator)
END_MESSAGE_MAP()


// CDlgBottomStatus ��Ϣ�������

void CDlgBottomStatus::OnBnClickedButtonSeperator()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


BOOL CDlgBottomStatus::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_btnSeprator1.Init(IMAGE_SEPRATOR, 1);
	m_btnSeprator2.Init(IMAGE_SEPRATOR, 1);
	m_btnSeprator3.Init(IMAGE_SEPRATOR, 1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
