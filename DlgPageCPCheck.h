#pragma once

#include "resource.h"
// CDlgPageCPCheck �Ի���

class CDlgPageCPCheck : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPageCPCheck)

public:
	CDlgPageCPCheck(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPageCPCheck();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
