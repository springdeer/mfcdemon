#pragma once


// CDlgPageNavistate �Ի���

class CDlgPageNavistate : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPageNavistate)

public:
	CDlgPageNavistate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPageNavistate();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
