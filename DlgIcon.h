#pragma once

#include "controls/public_res.h" 
#include "controls/PngStateButton.h"
#include "afxwin.h"
// CDlgIcon �Ի���

class CDlgIcon : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgIcon)

public:
	CDlgIcon(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgIcon();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CRgn m_rgn;
	CImage * m_pImage;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	CPngButton m_btnImage;
	afx_msg void OnBnClickedButton1();
};
