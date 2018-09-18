
// MFCApplication2.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2App

BEGIN_MESSAGE_MAP(CMFCApplication2App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCApplication2App ����

CMFCApplication2App::CMFCApplication2App()	
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��	

	m_nRunMode = _RUN_UNWIRE;

	m_bComConnected = FALSE;
}


// Ψһ��һ�� CMFCApplication2App ����

CMFCApplication2App theApp;


// CMFCApplication2App ��ʼ��
void CMFCApplication2App::InitConfig()
{
	TCHAR path[MAX_PATH];

	GetModuleFileName(AfxGetInstanceHandle(), path, sizeof(path));

	TCHAR* pEnd = _tcsrchr(path, _T('\\'));
	*(++pEnd) = '\0';

	_tcscat_s(path, sizeof(path), "config.ini");

	m_ini.SetFile(path);

	m_ini.ReadInt(_T("runtime"), _T("apptotaltime"), m_uTotalRuntime, 0);
}

BOOL CMFCApplication2App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	InitConfig();

	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	//CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));	
	
	m_uTotalRuntime++;

	m_dataLog.Init();

	CMFCApplication2Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO:  �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	//if (pShellManager != NULL)
	//{
	//	delete pShellManager;
	//}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CMFCApplication2App::ExitInstance()
{
	// TODO:  �ڴ����ר�ô����/����û���

	m_ini.WriteInt(_T("runtime"), _T("apptotaltime"), m_uTotalRuntime);

	return CWinAppEx::ExitInstance();
}

void CMFCApplication2App::IncTotalRuntime(int secs)
{
	m_uTotalRuntime += secs;
}

CDataLog * CMFCApplication2App::GetLog()
{
	return &m_dataLog;
}

void CMFCApplication2App::SetRunMode(int runmode)
{
	m_nRunMode = runmode;
}

int CMFCApplication2App::GetRunMode()
{
	return m_nRunMode;
}

CTransmiter* CMFCApplication2App::GetTransmiter()
{
	return &m_transmitter;
}

void  CMFCApplication2App::SetCommConnected(BOOL bConnected)
{
	m_bComConnected = bConnected;
}

CCommandWnds* CMFCApplication2App::GetCommandWnds()
{
	return &m_wndCommands;
}