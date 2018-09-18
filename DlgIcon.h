#pragma once

#include "controls/public_res.h" 
#include "controls/PngStateButton.h"
#include "afxwin.h"
// CDlgIcon 对话框

class CDlgIcon : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgIcon)

public:
	CDlgIcon(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgIcon();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
