// DialogPane.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DialogPane.h"
#include "afxdialogex.h"
#include "DlgRcvrSetting.h"
#include "DlgDataMon.h"
#include "DlgVoltageSetting.h"
#include "MFCApplication2Dlg.h"
#include "DlgSearchDevice.h"
#include "msgdef.h"
// CDialogPane �Ի���

IMPLEMENT_DYNAMIC(CDialogPane, CDialogEx)

CDialogPane::CDialogPane(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogPane::IDD, pParent)
{
	TCHAR filepath[MAX_PATH];
	GetModuleFileName(AfxGetInstanceHandle(), filepath, sizeof(filepath));

	char* slash = _tcsrchr(filepath, _T('\\'));
	*(++slash) = '\0';

	m_strSelectedFolder = filepath;
}

CDialogPane::~CDialogPane()
{
}

void CDialogPane::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_COM, m_btnCom);
	DDX_Control(pDX, IDC_BUTTON_COM2, m_btnSSCOMOper);
	DDX_Control(pDX, IDC_BUTTON_SEPERATOR, m_btnSepratorCom);
	DDX_Control(pDX, IDC_BUTTON_WIRELESS_CONNECT, m_btnWirelessConnect);
	DDX_Control(pDX, IDC_BUTTON_WIRELESS_STATE, m_btnWirelessState);
	DDX_Control(pDX, IDC_BUTTON_SEPERATOR2, m_btnWirelessSeperator);
	DDX_Control(pDX, IDC_BUTTON_RCVRSETTING, m_btnRcvrSetting);
	DDX_Control(pDX, IDC_BUTTON_DATA_WANT, m_btnDataWant);
	DDX_Control(pDX, IDC_BUTTON_DATA_BOUND, m_btnDataBound);
	DDX_Control(pDX, IDC_BUTTON_SEPERATOR3, m_btnSeperatorData);
	DDX_Control(pDX, IDC_BUTTON_DATA_STORE, m_btnDataStore);
	DDX_Control(pDX, IDC_COMBO_MODE, m_comboMode);
	DDX_Control(pDX, IDC_BUTTON_WIRELESS_STATE2, m_btnSetmode);
	DDX_Control(pDX, IDC_BUTTON_APPICON, m_btnAppIcon);
}


BEGIN_MESSAGE_MAP(CDialogPane, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogPane::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogPane::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_COM, &CDialogPane::OnBnClickedButtonCom)
	ON_BN_CLICKED(IDC_BUTTON_COM2, &CDialogPane::OnBnClickedButtonCom2)
	ON_BN_CLICKED(IDC_BUTTON_WIRELESS_CONNECT, &CDialogPane::OnBnClickedButtonWirelessConnect)
	ON_BN_CLICKED(IDC_BUTTON_WIRELESS_STATE, &CDialogPane::OnBnClickedButtonWirelessState)
	ON_BN_CLICKED(IDC_BUTTON_RCVRSETTING, &CDialogPane::OnBnClickedButtonRcvrsetting)
	ON_BN_CLICKED(IDC_BUTTON_DATA_STORE, &CDialogPane::OnBnClickedButtonDataStore)
	ON_BN_CLICKED(IDC_BUTTON_DATA_WANT, &CDialogPane::OnBnClickedButtonDataWant)
	ON_BN_CLICKED(IDC_BUTTON_WIRELESS_STATE2, &CDialogPane::OnBnClickedButtonWirelessState2)
	ON_BN_CLICKED(IDC_BUTTON_SEPERATOR, &CDialogPane::OnBnClickedButtonSeperator)
	ON_BN_CLICKED(IDC_BUTTON_APPICON, &CDialogPane::OnBnClickedButtonAppicon)
	ON_BN_CLICKED(IDC_BUTTON_DATA_BOUND, &CDialogPane::OnBnClickedButtonDataBound)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDialogPane ��Ϣ�������


void CDialogPane::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
}


void CDialogPane::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnCancel();
}


void CDialogPane::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rcClient;
	GetClientRect(&rcClient);

	CRect rcClipBox;

	dc.GetClipBox(rcClipBox);
	if (rcClipBox.IsRectEmpty()) return;

	CMemDC mdc(dc, rcClient);
	mdc.GetDC().FillSolidRect(&rcClipBox, RGB(160, 50, 34));
	TRACE("onpaint .. \n");
}


void CDialogPane::OnBnClickedButtonCom()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


BOOL CDialogPane::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_btnCom.Init(IMAGE_COMSTATE, 3);
	m_btnCom.SetTooltip(_T("��������״̬"));

	vector<string> states = { "�򿪴���", "ȡ������", "�Ͽ�����" };
	CFont font1;
	font1.CreateFontA(14, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnSSCOMOper.Init(states,(HFONT)font1.Detach());
	m_btnSepratorCom.Init(IMAGE_SEPRATOR, 1);

	states = { "��������", "ȡ������", "�Ͽ�����" };
	CFont font2;
	font2.CreateFontA(14, 0, 0, 0, FW_SEMIBOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
	m_btnWirelessConnect.Init(states, (HFONT)font2.Detach());
	m_btnWirelessConnect.SetTooltip(_T("�����߽��ջ���������"));

	m_btnWirelessState.Init(IMAGE_WIRELESS_CONNECT, 3);
	m_btnWirelessState.SetTooltip(_T("��������״̬"));
	m_btnWirelessSeperator.Init(IMAGE_SEPRATOR, 1);

	m_btnRcvrSetting.Init(IMAGE_RCVRSETTING, 4);
	m_btnRcvrSetting.SetTooltip(_T("�������߽��ջ�����״̬"));

	m_btnDataWant.Init(IMAGE_DATAWANT, 4);
	m_btnDataWant.SetTooltip(_T("�������ݼ������"));

	m_btnDataBound.Init(IMAGE_DATABOUND, 4);
	m_btnDataBound.SetTooltip(_T("�������ݼ����ֵ"));

	m_btnDataStore.Init(IMAGE_STORAGE, 4);
	m_btnDataStore.SetTooltip(_T("������ݴ浵"));

	m_btnSeperatorData.Init(IMAGE_SEPRATOR,1);

	m_comboMode.InsertString(0, _T("���߲���"));
	m_comboMode.SetItemData(0,_RUN_UNWIRE);

	m_comboMode.InsertString(1, _T("���߲���"));
	m_comboMode.SetItemData(1, _RUN_WIRELINE);

	m_comboMode.InsertString(2, _T("��������"));
	m_comboMode.SetItemData(2, _RUN_PIPELINE);
	m_comboMode.SetCurSel(0);

	m_btnSetmode.Init(IMAGE_SETPROP, 4);
	m_btnSetmode.SetTooltip(_T("����ѡ��Ĳ���ģʽ"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

BOOL CDialogPane::FindSSCom()
{
	long lReg;
	HKEY hKey;
	DWORD MaxValueLength;
	DWORD dwValueNumber;

	m_sscoms.clear();

	//��ע���
	lReg = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DEVICEMAP\\SERIALCOMM"), 0, KEY_QUERY_VALUE, &hKey);

	if (lReg != ERROR_SUCCESS) //�ɹ�ʱ����ERROR_SUCCESS
	{
		MessageBox(_T("��ע���ʧ�ܣ�"));
		return FALSE;
	}

	lReg = RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL, NULL, &dwValueNumber, &MaxValueLength, NULL, NULL, NULL);

	if (lReg != ERROR_SUCCESS) //û�гɹ�
	{
		MessageBox(_T("��ȡע�����Ϣʧ�ܣ�"));
		return FALSE;
	}

	TCHAR *pValueName, *pComNumber;
	DWORD cchValueName, dwValueSize = 10;

	for (int i = 0; i < dwValueNumber; i++)
	{
		cchValueName = MaxValueLength + 1;
		dwValueSize = 10;
		pValueName = (TCHAR *)VirtualAlloc(NULL, cchValueName, MEM_COMMIT, PAGE_READWRITE);

		//ö���Ӽ�
		lReg = RegEnumValue(hKey, i, pValueName, &cchValueName, NULL, NULL, NULL, NULL);

		if ((lReg != ERROR_SUCCESS) && (lReg != ERROR_NO_MORE_ITEMS))
		{
			MessageBox(_T("ö��ע�������û�и������Ŀ��"));//Enum Registry Error or no more Items!
			return FALSE;
		}

		pComNumber = (TCHAR*)VirtualAlloc(NULL, 6, MEM_COMMIT, PAGE_READWRITE);
		//��ȡ��ֵ
		lReg = RegQueryValueEx(hKey, pValueName, NULL, NULL, (LPBYTE)pComNumber, &dwValueSize);

		if (lReg != ERROR_SUCCESS)
		{
			MessageBox(_T("���ܻ�ȡ��������"));
			return FALSE;
		}

		CString str(pComNumber);
		//m_comPort.InsertString(i,str);//�ѻ�ȡ��ֵ���뵽COMBOX�ؼ���
		m_sscoms.push_back(str);

		VirtualFree(pValueName, 0, MEM_RELEASE);
		VirtualFree(pComNumber, 0, MEM_RELEASE);
	}

	RegCloseKey(hKey);

	return TRUE;
}

void CDialogPane::SearchCom()
{
	FindSSCom();

	CDlgSearchDevice dlgSearch;

	dlgSearch.SetComStrings(m_sscoms);

	int rslt = dlgSearch.DoModal();
	if (rslt == IDOK){
		theApp.SetCommConnected(TRUE);
		theApp.GetTransmiter()->SetMsgWnd(AfxGetMainWnd()->GetSafeHwnd(), WM_COM_MSGDATA);
		m_btnCom.Animate(TRUE, 200);
		m_btnSSCOMOper.ShowState(2);
		
		theApp.GetTransmiter()->Start();
	}
	else{
		//m_btnCom.ShowState(0);
		theApp.SetCommConnected(FALSE);
		m_btnCom.Animate(FALSE, 200);
		m_btnSSCOMOper.ShowState(0);
		
	}
}

void CDialogPane::OnBnClickedButtonCom2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (theApp.IsCommConnected()){
		theApp.GetTransmiter()->Stop();
		theApp.GetTransmiter()->GetDevice()->Close();
		theApp.SetCommConnected(FALSE);

		m_btnCom.Animate(FALSE, 200);
		m_btnSSCOMOper.ShowState(0);
		
	}
	else{
		SearchCom();
	}
	
}

void CDialogPane::ShowWirelessConnected(BOOL bConnected)
{
	m_btnWirelessState.Animate(bConnected, 150);
}

void CDialogPane::OnBnClickedButtonWirelessConnect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!theApp.IsCommConnected()){
		MessageBox(_T("δ����Զ�̿���̨"),_T("��ʾ"),MB_OK|MB_ICONSTOP);
		return;
	}

	CProtoBuffer proto; 
	RemoteConnect rRemoteConnect;	

	rRemoteConnect.type = theApp.GetTransmiter()->GetChan();

	theApp.GetTransmiter()->MailCommand(_REQ_REMOTE_CONNECT, &rRemoteConnect);
	
}


void CDialogPane::OnBnClickedButtonWirelessState()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDialogPane::OnBnClickedButtonRcvrsetting()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CDlgRcvrSetting::Get()->ShowWindow(SW_SHOW);
}


void CDialogPane::OnBnClickedButtonDataStore()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CMFCApplication2Dlg * pMain = (CMFCApplication2Dlg *)AfxGetMainWnd();

	CString strBmpFile;
	SYSTEMTIME t;
	GetLocalTime(&t);		
	CString strFileName;
	strFileName.Format(_T("\\%02d%02d%02d_%02d%02d%02d.bmp"),t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond);

	CFileDialog fileDlg(FALSE, _T("image file(*.bmp)|*.bmp"), strFileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("image file(*.bmp)|*.bmp||"),this);
	if (fileDlg.DoModal() == IDOK)
	//if (theApp.GetShellManager()->BrowseForFolder(m_strSelectedFolder, this, m_strSelectedFolder))
	{
		CString strFile = fileDlg.GetPathName();
		strBmpFile.Format(strFile, t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
		pMain->PrintWnd(pMain->GetWorkAreaWnd(), strBmpFile);
	}	
}


void CDialogPane::OnBnClickedButtonDataWant()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDlgDataMon::Get()->ShowWindow(SW_SHOW);
}


void CDialogPane::OnBnClickedButtonWirelessState2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int  nItem = m_comboMode.GetCurSel();
	UINT uData = m_comboMode.GetItemData(nItem);
	theApp.SetRunMode(uData);
}


void CDialogPane::OnBnClickedButtonSeperator()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CDialogPane::OnBnClickedButtonAppicon()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CDialogPane::OnBnClickedButtonDataBound()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDlgVoltageSetting::Get()->ShowWindow(SW_SHOW);
}


BOOL CDialogPane::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;

	return CDialogEx::OnEraseBkgnd(pDC);
}


void CDialogPane::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	UpdateWindow();
	// TODO:  �ڴ˴������Ϣ����������
}
