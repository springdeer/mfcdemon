#pragma once


// CDlgPageRcvrMon �Ի���

class CDlgPageRcvrMon : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPageRcvrMon)

public:
	CDlgPageRcvrMon(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPageRcvrMon();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
