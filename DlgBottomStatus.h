#pragma once
#include "afxwin.h"
#include "controls/public_res.h"
#include "controls/PngStateButton.h"

// CDlgBottomStatus �Ի���

class CDlgBottomStatus : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgBottomStatus)

public:
	CDlgBottomStatus(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgBottomStatus();

// �Ի�������
	enum { IDD = IDD_DIALOG_BOTTOM_BAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CPngStateButton m_btnSeprator1;
	CPngStateButton m_btnSeprator2;
	CPngStateButton m_btnSeprator3;
	afx_msg void OnBnClickedButtonSeperator();
	virtual BOOL OnInitDialog();
};
