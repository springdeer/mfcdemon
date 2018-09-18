// DlgVoltageSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgVoltageSetting.h"
#include "afxdialogex.h"


// CDlgVoltageSetting 对话框
CDlgVoltageSetting* CDlgVoltageSetting::m_pObj = NULL;

IMPLEMENT_DYNAMIC(CDlgVoltageSetting, CDialogEx)

CDlgVoltageSetting* CDlgVoltageSetting::Get()
{
	if (m_pObj == NULL){
		m_pObj = new CDlgVoltageSetting();
		m_pObj->Create(CDlgVoltageSetting::IDD);
	}

	m_pObj->CenterWindow();

	return m_pObj;
}

CDlgVoltageSetting::CDlgVoltageSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgVoltageSetting::IDD, pParent)
	, m_nB4High(30)
	, m_nB4Low(20)
	, m_nD1High(30)
	, m_nD1Low(20)
	, m_nB3High(30)
	, m_nB3Low(20)
	, m_nB2High(30)
	, m_nB2Low(20)	
	, m_dfB4Fact(1.0)
	, m_dfD1Fact(1.0)
	, m_dfB3Fact(1.0)
	, m_dfB2Fact(1.0)
{

}

CDlgVoltageSetting::~CDlgVoltageSetting()
{
}

void CDlgVoltageSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_B4HIGH, m_nB4High);
	DDX_Text(pDX, IDC_EDIT_B4LOW, m_nB4Low);
	DDX_Text(pDX, IDC_EDIT_D1HIGH, m_nD1High);
	DDX_Text(pDX, IDC_EDIT_D1LOW, m_nD1Low);
	DDX_Text(pDX, IDC_EDIT_B3HIGH, m_nB3High);
	DDX_Text(pDX, IDC_EDIT_B3LOW, m_nB3Low);
	DDX_Text(pDX, IDC_EDIT_B2HIGH, m_nB2High);
	DDX_Text(pDX, IDC_EDIT_B2LOW, m_nB2Low);
	DDX_Text(pDX, IDC_EDIT_B4FACT, m_dfB4Fact);
	DDX_Text(pDX, IDC_EDIT_D1FACT, m_dfD1Fact);
	DDX_Text(pDX, IDC_EDIT_B3FACT, m_dfB3Fact);
	DDX_Text(pDX, IDC_EDIT_B2FACT, m_dfB2Fact);
}


BEGIN_MESSAGE_MAP(CDlgVoltageSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgVoltageSetting::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgVoltageSetting 消息处理程序
BOOL CDlgVoltageSetting::IsDigit(TCHAR ch)
{
	if (ch >= _T('0') && ch <= _T('9')) return TRUE;

	return FALSE;
}

BOOL  CDlgVoltageSetting::IsNumber(CString strValue, int& iValue)
{
	int length = strValue.GetLength();

	int i = 0;
	for (; i < length; i++){
		if (!IsDigit(strValue.GetAt(i))) return FALSE;
	}

	TCHAR* pEnd = NULL;
	iValue = _tcstol(strValue.GetBuffer(0), &pEnd, 10);
	strValue.ReleaseBuffer();

	return TRUE;
}

BOOL  CDlgVoltageSetting::IsNumber_float(CString strValue, double& rValue)
{
	int length = strValue.GetLength();

	int i = 0;
	for (; i < length; i++){
		TCHAR ch = strValue.GetAt(i);
		if (!IsDigit(ch) && ch!=_T('.')) return FALSE;
	}

	TCHAR* pEnd = NULL;
	rValue = _tcstod(strValue.GetBuffer(0), &pEnd);
	strValue.ReleaseBuffer();

	if (*pEnd == _T('\0'))
		return TRUE;
	else
		return FALSE;
}

BOOL CDlgVoltageSetting::CheckIntRange(CString strValue, int left, int right, int& rslt)
{
	int length = strValue.GetLength();

	int i = 0;
	for (; i < length; i++){
		if (!IsDigit(strValue.GetAt(i))) return FALSE;
	}

	TCHAR* pEnd = NULL;
	TCHAR* str = strValue.GetBuffer(0);
	strValue.ReleaseBuffer();

	rslt = _tcstol(str, &pEnd, 10);
	if (rslt >= left && rslt <= right)
		return TRUE;

	return FALSE;
}

void CDlgVoltageSetting::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strValue;

	GetDlgItemText(IDC_EDIT_B4HIGH, strValue);
	if (!IsNumber(strValue, m_nB4High)){
		MessageBox(_T("请输入整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_B4HIGH);
		pEdit->SetFocus();
		pEdit->SetSel(0,-1);
		return;
	}

	GetDlgItemText(IDC_EDIT_B4LOW, strValue);
	if (!IsNumber(strValue, m_nB4Low)){
		MessageBox(_T("请输入整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_B4LOW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}

	GetDlgItemText(IDC_EDIT_D1HIGH, strValue);
	if (!IsNumber(strValue, m_nD1High)){
		MessageBox(_T("请输入整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_D1HIGH);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}

	GetDlgItemText(IDC_EDIT_D1LOW, strValue);
	if (!IsNumber(strValue, m_nD1Low)){
		MessageBox(_T("请输入整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_D1LOW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}

	GetDlgItemText(IDC_EDIT_B3HIGH, strValue);
	if (!IsNumber(strValue, m_nB3High)){
		MessageBox(_T("请输入整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_B3HIGH);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}

	GetDlgItemText(IDC_EDIT_B3LOW, strValue);
	if (!IsNumber(strValue, m_nB3Low)){
		MessageBox(_T("请输入整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_B3LOW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}

	GetDlgItemText(IDC_EDIT_B2HIGH, strValue);
	if (!IsNumber(strValue, m_nB2High)){
		MessageBox(_T("请输入整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_B2HIGH);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}

	GetDlgItemText(IDC_EDIT_B2LOW, strValue);
	if (!IsNumber(strValue, m_nB2Low)){
		MessageBox(_T("请输入整数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_B2LOW);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}

	GetDlgItemText(IDC_EDIT_B4FACT, strValue);
	if (!IsNumber_float(strValue, m_dfB4Fact)){
		MessageBox(_T("请输入浮点数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_B4FACT);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}

	GetDlgItemText(IDC_EDIT_D1FACT, strValue);
	if (!IsNumber_float(strValue, m_dfD1Fact)){
		MessageBox(_T("请输入浮点数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_D1FACT);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}

	GetDlgItemText(IDC_EDIT_B3FACT, strValue);
	if (!IsNumber_float(strValue, m_dfB3Fact)){
		MessageBox(_T("请输入浮点数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_B3FACT);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}

	GetDlgItemText(IDC_EDIT_B4FACT, strValue);
	if (!IsNumber_float(strValue, m_dfB4Fact)){
		MessageBox(_T("请输入浮点数."), _T("提示"), MB_OK | MB_ICONHAND);
		CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_B4FACT);
		pEdit->SetFocus();
		pEdit->SetSel(0, -1);
		return;
	}

	CDialogEx::OnOK();
}
