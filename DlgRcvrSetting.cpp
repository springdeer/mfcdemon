// DlgRcvrSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgRcvrSetting.h"
#include "afxdialogex.h"
#include "controls/public_res.h"

// CDlgRcvrSetting 对话框

CDlgRcvrSetting* CDlgRcvrSetting::m_pObj = NULL;

IMPLEMENT_DYNAMIC(CDlgRcvrSetting, CDialogEx)

CDlgRcvrSetting* CDlgRcvrSetting::Get()
{
	if (m_pObj == NULL){
		m_pObj = new CDlgRcvrSetting();
		m_pObj->Create(CDlgRcvrSetting::IDD);
	}

	m_pObj->CenterWindow();

	return m_pObj;
}

CDlgRcvrSetting::CDlgRcvrSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRcvrSetting::IDD, pParent)	
	, m_nB2PW(20)
	, m_nB2PW_close(20)
	, m_nB3PW(20)
	, m_nB3PW_close(20)
	, m_nB4PW(20)
	, m_nB4PW_close(20)
	, m_nD1PW(20)
	, m_nD1PW_close(20)
	, m_nT1PW(20)
	, m_nT2PW(20)
	, m_nT3PW(20)
	, m_nT4PW(20)
	, m_nT5PW(20)
	, m_nT6PW(20)
	, m_nT7PW(20)
	, m_nFirePW(20)
	, m_nTransPower(2)
	, m_nRcvrID(0)
	, m_iChannel(0)
	, m_bAutoSelectChannel(0)
{

}

CDlgRcvrSetting::~CDlgRcvrSetting()
{
}

void CDlgRcvrSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_B2PW, m_btnB2pw);
	DDX_Control(pDX, IDC_BUTTON_B2PW_CLOSE, m_btnB2pwClose);
	DDX_Control(pDX, IDC_BUTTON_B3PW, m_btnB3pw);
	DDX_Control(pDX, IDC_BUTTON_B3PW_CLOSE, m_btnB3pwClose);
	DDX_Control(pDX, IDC_BUTTON_B4PW, m_btnB4pw);
	DDX_Control(pDX, IDC_BUTTON_B4PW_CLOSE, m_btnB4pwClose);
	DDX_Control(pDX, IDC_BUTTON_D1PW, m_btnD1pw);
	DDX_Control(pDX, IDC_BUTTON_D1PW_CLOSE, m_btnD1pwClose);
	DDX_Control(pDX, IDC_BUTTON_RCVRID, m_btnRcvrId);
	DDX_Control(pDX, IDC_BUTTON_T1PW, m_btnT1pw);
	DDX_Control(pDX, IDC_BUTTON_T2PW, m_btnT2pw);
	DDX_Control(pDX, IDC_BUTTON_T3PW, m_btnT3pw);
	DDX_Control(pDX, IDC_BUTTON_T4PW, m_btnT4pw);
	DDX_Control(pDX, IDC_BUTTON_T5PW, m_btnT5pw);
	DDX_Control(pDX, IDC_BUTTON_T6PW, m_btnT6pw);
	DDX_Control(pDX, IDC_BUTTON_T7PW, m_btnT7pw);
	DDX_Control(pDX, IDC_BUTTON_FIREPW, m_btnFirepw);
	DDX_Control(pDX, IDC_BUTTON_FIREPW2, m_btnFirepw2);
	DDX_Text(pDX, IDC_EDIT_B2PW, m_nB2PW);
	DDX_Text(pDX, IDC_EDIT_B2PW_CLOSE, m_nB2PW_close);
	DDX_Text(pDX, IDC_EDIT_B3PW, m_nB3PW);
	DDX_Text(pDX, IDC_EDIT_B3PW_CLOSE, m_nB3PW_close);
	DDX_Text(pDX, IDC_EDIT_B4PW, m_nB4PW);
	DDX_Text(pDX, IDC_EDIT_B4PW_CLOSE, m_nB4PW_close);
	DDX_Text(pDX, IDC_EDIT_D1PW, m_nD1PW);
	DDX_Text(pDX, IDC_EDIT_D1PW_CLOSE, m_nD1PW_close);
	DDX_Text(pDX, IDC_EDIT_T1PW, m_nT1PW);
	DDX_Text(pDX, IDC_EDIT_T2PW, m_nT2PW);
	DDX_Text(pDX, IDC_EDIT_T3PW, m_nT3PW);
	DDX_Text(pDX, IDC_EDIT_T4PW, m_nT4PW);
	DDX_Text(pDX, IDC_EDIT_T5PW, m_nT5PW);
	DDX_Text(pDX, IDC_EDIT_T6PW, m_nT6PW);
	DDX_Text(pDX, IDC_EDIT_T7PW, m_nT7PW);
	DDX_Text(pDX, IDC_EDIT_FIREPW, m_nFirePW);
	DDX_Text(pDX, IDC_EDIT_POWER, m_nTransPower);
	DDX_Text(pDX, IDC_EDIT_RCVRID, m_nRcvrID);
	DDX_Radio(pDX, IDC_RADIO1, m_iChannel);
}


BEGIN_MESSAGE_MAP(CDlgRcvrSetting, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_B2PW, &CDlgRcvrSetting::OnBnClickedButtonB2pw)
	ON_BN_CLICKED(IDC_BUTTON_RCVRID, &CDlgRcvrSetting::OnBnClickedButtonRcvrid)
	ON_BN_CLICKED(IDC_BUTTON_B2PW_CLOSE, &CDlgRcvrSetting::OnBnClickedButtonB2pwClose)
	ON_BN_CLICKED(IDC_BUTTON_B3PW, &CDlgRcvrSetting::OnBnClickedButtonB3pw)
	ON_BN_CLICKED(IDC_BUTTON_B3PW_CLOSE, &CDlgRcvrSetting::OnBnClickedButtonB3pwClose)
	ON_BN_CLICKED(IDC_BUTTON_B4PW, &CDlgRcvrSetting::OnBnClickedButtonB4pw)
	ON_BN_CLICKED(IDC_BUTTON_B4PW_CLOSE, &CDlgRcvrSetting::OnBnClickedButtonB4pwClose)
	ON_BN_CLICKED(IDC_BUTTON_D1PW, &CDlgRcvrSetting::OnBnClickedButtonD1pw)
	ON_BN_CLICKED(IDC_BUTTON_D1PW_CLOSE, &CDlgRcvrSetting::OnBnClickedButtonD1pwClose)
	ON_BN_CLICKED(IDC_BUTTON_T1PW, &CDlgRcvrSetting::OnBnClickedButtonT1pw)
	ON_BN_CLICKED(IDC_BUTTON_T2PW, &CDlgRcvrSetting::OnBnClickedButtonT2pw)
	ON_BN_CLICKED(IDC_BUTTON_T3PW, &CDlgRcvrSetting::OnBnClickedButtonT3pw)
	ON_BN_CLICKED(IDC_BUTTON_T4PW, &CDlgRcvrSetting::OnBnClickedButtonT4pw)
	ON_BN_CLICKED(IDC_BUTTON_T5PW, &CDlgRcvrSetting::OnBnClickedButtonT5pw)
	ON_BN_CLICKED(IDC_BUTTON_T6PW, &CDlgRcvrSetting::OnBnClickedButtonT6pw)
	ON_BN_CLICKED(IDC_BUTTON_T7PW, &CDlgRcvrSetting::OnBnClickedButtonT7pw)
	ON_BN_CLICKED(IDC_BUTTON_FIREPW, &CDlgRcvrSetting::OnBnClickedButtonFirepw)
	ON_BN_CLICKED(IDC_BUTTON_FIREPW2, &CDlgRcvrSetting::OnBnClickedButtonFirepw2)
	ON_BN_CLICKED(IDC_CHECK_AUTOADJUST, &CDlgRcvrSetting::OnBnClickedCheckAutoadjust)
END_MESSAGE_MAP()


// CDlgRcvrSetting 消息处理程序

void CDlgRcvrSetting::InitUi()
{
	m_btnB2pw.Init(IMAGE_GO,4);
	m_btnB2pwClose.Init(IMAGE_GO, 4);
	m_btnB3pw.Init(IMAGE_GO, 4);
	m_btnB3pwClose.Init(IMAGE_GO, 4);
	m_btnB4pw.Init(IMAGE_GO, 4);
	m_btnB4pwClose.Init(IMAGE_GO, 4);
	m_btnD1pw.Init(IMAGE_GO, 4);
	m_btnD1pwClose.Init(IMAGE_GO, 4);
	m_btnRcvrId.Init(IMAGE_GO, 4);
	m_btnT1pw.Init(IMAGE_GO, 4);
	m_btnT2pw.Init(IMAGE_GO, 4);
	m_btnT3pw.Init(IMAGE_GO, 4);
	m_btnT4pw.Init(IMAGE_GO, 4);
	m_btnT5pw.Init(IMAGE_GO, 4);
	m_btnT6pw.Init(IMAGE_GO, 4);
	m_btnT7pw.Init(IMAGE_GO, 4);
	m_btnFirepw.Init(IMAGE_GO, 4);
	m_btnFirepw2.Init(IMAGE_GO, 4);	

}

BOOL CDlgRcvrSetting::IsDigit(TCHAR ch)
{
	if (ch >= _T('0') && ch <= _T('9')) return TRUE;

	return FALSE;
}

BOOL CDlgRcvrSetting::CheckIntRange(CString strValue, int left, int right,int& rslt)
{
	int length = strValue.GetLength();

	int i = 0;
	for (; i < length; i++){
		if (!IsDigit(strValue.GetAt(i))) return FALSE;
	}
	
	TCHAR* pEnd = NULL;
	rslt = _tcstol(strValue.GetBuffer(0), &pEnd, 10);
	strValue.ReleaseBuffer();

	if (rslt >= left && rslt <= right) return TRUE;

	return FALSE;
}

void CDlgRcvrSetting::OnBnClickedButtonB2pw()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_B2PW, strValue);
	
	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_B2PW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
	}
	
}


void CDlgRcvrSetting::OnBnClickedButtonRcvrid()
{
	// TODO:  在此添加控件通知处理程序代码
}


BOOL CDlgRcvrSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUi();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDlgRcvrSetting::OnBnClickedButtonB2pwClose()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_B2PW_CLOSE, strValue);

	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_B2PW_CLOSE);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
}


void CDlgRcvrSetting::OnBnClickedButtonB3pw()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_B3PW, strValue);

	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_B3PW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
}


void CDlgRcvrSetting::OnBnClickedButtonB3pwClose()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_B3PW_CLOSE, strValue);

	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_B3PW_CLOSE);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
}


void CDlgRcvrSetting::OnBnClickedButtonB4pw()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_B4PW, strValue);

	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_B4PW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
}


void CDlgRcvrSetting::OnBnClickedButtonB4pwClose()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_B4PW_CLOSE, strValue);

	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_B4PW_CLOSE);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
}


void CDlgRcvrSetting::OnBnClickedButtonD1pw()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_D1PW, strValue);

	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_D1PW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
}


void CDlgRcvrSetting::OnBnClickedButtonD1pwClose()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_D1PW_CLOSE, strValue);

	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_D1PW_CLOSE);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
}


void CDlgRcvrSetting::OnBnClickedButtonT1pw()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_T1PW, strValue);

	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_T1PW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
}


void CDlgRcvrSetting::OnBnClickedButtonT2pw()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_T2PW, strValue);

	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_T2PW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
}


void CDlgRcvrSetting::OnBnClickedButtonT3pw()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_T3PW, strValue);

	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_T3PW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
}


void CDlgRcvrSetting::OnBnClickedButtonT4pw()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_T4PW, strValue);

	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_T4PW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
}


void CDlgRcvrSetting::OnBnClickedButtonT5pw()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_T5PW, strValue);

	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_T5PW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
}


void CDlgRcvrSetting::OnBnClickedButtonT6pw()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_T6PW, strValue);

	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_T6PW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
}


void CDlgRcvrSetting::OnBnClickedButtonT7pw()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_T7PW, strValue);

	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_T7PW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
}


void CDlgRcvrSetting::OnBnClickedButtonFirepw()
{
	// TODO:  在此添加控件通知处理程序代码
	int iValue = 0;
	CString strValue;
	GetDlgItemText(IDC_EDIT_FIREPW, strValue);

	if (!CheckIntRange(strValue, 10, 6000, iValue)){
		MessageBox(_T("请输入10～6000的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_FIREPW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
}


void CDlgRcvrSetting::OnBnClickedButtonFirepw2()
{
	// TODO:  在此添加控件通知处理程序代码
	int iChannel = -1;

	CButton* pButtonA = (CButton*)GetDlgItem(IDC_RADIO_A);
	CButton* pButtonB = (CButton*)GetDlgItem(IDC_RADIO_B);
	CButton* pButtonC = (CButton*)GetDlgItem(IDC_RADIO_C);

	if (pButtonA->GetCheck() == BST_CHECKED)
		iChannel = 0;
	else if (pButtonB->GetCheck() == BST_CHECKED)
		iChannel = 1;
	else if (pButtonC->GetCheck() == BST_CHECKED)
		iChannel = 2;

	if (iChannel == -1){
		MessageBox(_T("请选择通道."), _T("提示"), MB_OK | MB_ICONHAND);
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	if (!m_bAutoSelectChannel){
		int iValue = -1;
		CString strValue;
		GetDlgItemText(IDC_EDIT_CHANNEL, strValue);
		if (!CheckIntRange(strValue, 1, 8, iValue)){
			MessageBox(_T("请输入1～8的整数."), _T("提示"), MB_OK | MB_ICONHAND);
			CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_CHANNEL);
			pEdit->SetFocus();
			pEdit->SetSel(0, -1);
			return;
		}
	}
	//////////////////////////////////////////////////////////////////////////	
	int iValue = -1;
	CString strValue;
	GetDlgItemText(IDC_EDIT_POWER, strValue);
	if (!CheckIntRange(strValue, 1, 3, iValue)){
		MessageBox(_T("请输入1～3的整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_POWER);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}
	
}


void CDlgRcvrSetting::OnBnClickedCheckAutoadjust()
{
	// TODO:  在此添加控件通知处理程序代码
	CButton * pBtn = (CButton *)GetDlgItem(IDC_CHECK_AUTOADJUST);

	if (pBtn->GetCheck() == BST_CHECKED){
		m_bAutoSelectChannel = TRUE;
		GetDlgItem(IDC_EDIT_CHANNEL)->EnableWindow(FALSE);	
	}
	else{
		GetDlgItem(IDC_EDIT_CHANNEL)->EnableWindow(TRUE);
		m_bAutoSelectChannel = FALSE;
	}	

}
