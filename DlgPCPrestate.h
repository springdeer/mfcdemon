#pragma once


// CDlgPCPrestate �Ի���

class CDlgPCPrestate : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPCPrestate)

public:
	CDlgPCPrestate(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPCPrestate();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
};
