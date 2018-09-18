// DlgSearchDevice.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgSearchDevice.h"
#include <CommCtrl.h>

#include "afxdialogex.h"

// CDlgSearchDevice 对话框

IMPLEMENT_DYNAMIC(CDlgSearchDevice, CDialogEx)

CDlgSearchDevice::CDlgSearchDevice(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSearchDevice::IDD, pParent)
{
	m_uTimer = NULL;
	m_iNdx = 0;
}

CDlgSearchDevice::~CDlgSearchDevice()
{
}

void CDlgSearchDevice::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listData);
	DDX_Control(pDX, IDC_CANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CDlgSearchDevice, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgSearchDevice::OnBnClickedButton1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CDlgSearchDevice::OnNMCustomdrawProgress1)
	ON_BN_CLICKED(IDC_CANCEL, &CDlgSearchDevice::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_MESSAGE(WM_COM_MSGDATA,OnComMsgCom)
END_MESSAGE_MAP()


// CDlgSearchDevice 消息处理程序

void CDlgSearchDevice::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
}


BOOL CDlgSearchDevice::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	vector<string> states = { "取消操作"};
	CFont font1;
	font1.CreateFontA(14, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnCancel.Init(states, (HFONT)font1.Detach());
    	
	m_waitSecs = 1500;
	if (m_vecStrings.size()) SetTimer(101, m_waitSecs, NULL);

	// TODO:  在此添加额外的初始化		
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CDlgSearchDevice::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}

void CDlgSearchDevice::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	m_listData.ResetContent();

	if (m_uTimer != NULL){
		KillTimer(m_uTimer);
		m_uTimer = NULL;
	}

	return OnCancel();
}

void CDlgSearchDevice::SetComStrings(vector<CString>& vecStrings)
{
	m_vecStrings = vecStrings;
}

void CDlgSearchDevice::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (101 == nIDEvent){
		m_iNdx = (m_iNdx%m_vecStrings.size());
		CString strCom = m_vecStrings.at(m_iNdx);
		strCom.Trim("COM");
		TCHAR * pEnd = NULL;

		if (m_iNdx == 0) m_listData.ResetContent();

		CString strTime;
		SYSTEMTIME t;
		GetLocalTime(&t);
		strTime.Format(_T("%02d:%02d:%02d"),t.wHour,t.wMinute,t.wSecond);
		m_listData.AddString(strTime+_T(" 测试COM") + strCom + "..");

		int comno = strtol(strCom.GetBuffer(0), &pEnd, 10);
		m_indxMemo = comno;
		CDevice* pDevice = theApp.GetTransmiter()->GetDevice();
		int openStatus = pDevice->Open(comno, 115200, 8, ONESTOPBIT, FALSE, NOPARITY, "dev", NULL, "", (void*)m_indxMemo);
		if (openStatus == 1){
			DevConnect fDevConn;
			char buffer[512];
			memset(buffer, 0, sizeof(buffer));

			theApp.GetTransmiter()->SetMsgWnd(GetSafeHwnd(), WM_COM_MSGDATA);			
			
			theApp.GetTransmiter()->MailCommand(_REQ_DEV_CONNECT, &fDevConn);
			
		}

		m_iNdx++;
	}

	CDialogEx::OnTimer(nIDEvent);
}

LRESULT CDlgSearchDevice::OnComMsgCom(WPARAM wParam, LPARAM lParam)
{
	if (_RES_DEV_CONNECTED == wParam){
		
		int nData = (int)lParam;

		if (nData == m_indxMemo){
			KillTimer(101);
			m_uTimer = NULL;
			OnOK();
		}
		else{
			if (m_waitSecs < 3){
				KillTimer(101);
				m_waitSecs *= 1.5;
				SetTimer(101, m_waitSecs, NULL);
			}			
		}

		return 0;
	}

	return 0;
}