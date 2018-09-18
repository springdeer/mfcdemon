// DlgConnectPlusB2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgConnectPlusB2.h"
#include "afxdialogex.h"


// CDlgConnectPlusB2 �Ի���

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


// CDlgConnectPlusB2 ��Ϣ�������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ConnectPlusB2 fCommand;
	fCommand.type = theApp.GetTransmiter()->GetChan();
	
	//theApp.GetTransmiter()->MailCommand(_REQ_CONNECT_PLUS_B2, &fCommand);	
	//���Ͱ�������ָ��
	m_state = eState_Waitkey;

	UpdateTip();

}

BOOL CDlgConnectPlusB2::OnInitDialog()
{
	__super::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_state = eState_Init;	
	
	UpdateTip();

	m_uTimer = SetTimer(101,1000,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDlgConnectPlusB2::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
		SetDlgItemText(IDC_EDIT_STATE, _T("�������ͨ/ȡ������ť���в���."));
		break;
	case eState_Waitkey:
		SetDlgItemText(IDC_EDIT_STATE, _T("�밴����Ӧ�İ���.."));
		break;
	case eState_WaitRemotereply:
	{
		time_t  now = time(NULL);
		CString strTip;
		strTip.Format(_T("ָ���Ѿ����� %d��"), now - m_timeCmd);
		SetDlgItemText(IDC_EDIT_STATE, strTip);
	}
		break;
	case eState_WaitTimeout:
		SetDlgItemText(IDC_EDIT_STATE, _T("ָ��ִ�г�ʱ."));
		break;
	case eState_CommandOk:
		SetDlgItemText(IDC_EDIT_STATE, _T("ָ��ִ�гɹ�."));
		break;
	case eState_CommandFailed:
		SetDlgItemText(IDC_EDIT_STATE, _T("ָ��ִ��ʧ��."));
		break;
	default :
		break;
	}	
}

void CDlgConnectPlusB2::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д __super::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDlgConnectPlusB2::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	theApp.GetCommandWnds()->ExitCommand();
}


void CDlgConnectPlusB2::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	theApp.GetCommandWnds()->ExitCommand();
}
