// DlgConnectPlusB2.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgConnectPlusB2.h"
#include "afxdialogex.h"


// CDlgConnectPlusB2 对话框

IMPLEMENT_DYNAMIC(CDlgConnectPlusB2, CDialogEx)

CDlgConnectPlusB2::CDlgConnectPlusB2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgConnectPlusB2::IDD, pParent)
{
}

CDlgConnectPlusB2::~CDlgConnectPlusB2()
{
}

void CDlgConnectPlusB2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgConnectPlusB2, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgConnectPlusB2::OnBnClickedOk)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_EDIT1, &CDlgConnectPlusB2::OnEnChangeEdit1)
	ON_BN_CLICKED(IDCANCEL, &CDlgConnectPlusB2::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgConnectPlusB2 消息处理程序
void   CDlgConnectPlusB2::Show()
{
	this->DoModal();
}

BOOL   CDlgConnectPlusB2::IsCommandTimeout()
{
	return (time(NULL) - m_timeCmd)>_COMMAND_TIMEOUT;
}

void   CDlgConnectPlusB2::ExitCommand()
{
	m_state = eState_Init;

	if (m_uTimer){
		KillTimer(m_uTimer);
		m_uTimer = NULL;
	}

	OnCancel();
}

BOOL   CDlgConnectPlusB2::CheckKBState(int key)
{
	BOOL bCheck = TRUE;

	if (bCheck){
		ConnectPlusB2 fCommand;

		fCommand.type = theApp.GetTransmiter()->GetChan();

		theApp.GetTransmiter()->MailCommand(_REQ_CONNECT_PLUS_B2, &fCommand);

		m_state   = eState_WaitRemotereply;
		m_timeCmd = time(NULL);
	}

	return FALSE;
}

BOOL   CDlgConnectPlusB2::CheckRemoteReplay(void* reply)
{
	m_state = eState_CommandOk;

	UpdateTip();

	return FALSE;
}

void CDlgConnectPlusB2::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	ConnectPlusB2 fCommand;
	fCommand.type = theApp.GetTransmiter()->GetChan();
	
	//theApp.GetTransmiter()->MailCommand(_REQ_CONNECT_PLUS_B2, &fCommand);	
	//发送按键控制指令
	m_state = eState_Waitkey;

	UpdateTip();

}

BOOL CDlgConnectPlusB2::OnInitDialog()
{
	__super::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_state = eState_Init;	
	
	UpdateTip();

	m_uTimer = SetTimer(101,1000,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDlgConnectPlusB2::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == m_uTimer){
		if (eState_WaitRemotereply == m_state){
			time_t now = time(NULL);
			if (now - m_timeCmd >= _COMMAND_TIMEOUT)
				m_state = eState_WaitTimeout;			
		}

		if (eState_WaitRemotereply == m_state || eState_WaitTimeout == m_state)
			UpdateTip();
	}

	__super::OnTimer(nIDEvent);
}

void  CDlgConnectPlusB2::UpdateTip()
{
	switch (m_state)
	{
	case eState_Init :
		SetDlgItemText(IDC_EDIT_STATE, _T("点击【接通/取消】按钮进行操作."));
		break;
	case eState_Waitkey:
		SetDlgItemText(IDC_EDIT_STATE, _T("请按下相应的按键.."));
		break;
	case eState_WaitRemotereply:
	{
		time_t  now = time(NULL);
		CString strTip;
		strTip.Format(_T("指令已经发送 %d秒"), now - m_timeCmd);
		SetDlgItemText(IDC_EDIT_STATE, strTip);
	}
		break;
	case eState_WaitTimeout:
		SetDlgItemText(IDC_EDIT_STATE, _T("指令执行超时."));
		break;
	case eState_CommandOk:
		SetDlgItemText(IDC_EDIT_STATE, _T("指令执行成功."));
		break;
	case eState_CommandFailed:
		SetDlgItemText(IDC_EDIT_STATE, _T("指令执行失败."));
		break;
	default :
		break;
	}	
}

void CDlgConnectPlusB2::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 __super::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CDlgConnectPlusB2::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	theApp.GetCommandWnds()->ExitCommand();
}


void CDlgConnectPlusB2::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	theApp.GetCommandWnds()->ExitCommand();
}
