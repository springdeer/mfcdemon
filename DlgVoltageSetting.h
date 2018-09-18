#pragma once


// CDlgVoltageSetting 对话框

class CDlgVoltageSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVoltageSetting)
	CDlgVoltageSetting(CWnd* pParent = NULL);   // 标准构造函数
public:
	static CDlgVoltageSetting*Get();
	virtual ~CDlgVoltageSetting();

// 对话框数据
	enum { IDD = IDD_DIALOG_VOLTAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL  CheckIntRange(CString strValue, int left, int right, int& rslt);
	BOOL  IsDigit(TCHAR ch);
	BOOL  IsNumber(CString strValue, int& iValue);
	BOOL  IsNumber_float(CString strValue, double& iValue);
	DECLARE_MESSAGE_MAP()
private:
	static CDlgVoltageSetting* m_pObj;
public:
	int m_nB4High;
	int m_nB4Low;
	int m_nD1High;
	int m_nD1Low;
	int m_nB3High;
	int m_nB3Low;
	int m_nB2High;
	int m_nB2Low;

	afx_msg void OnBnClickedOk();
	double m_dfB4Fact;
	double m_dfD1Fact;
	double m_dfB3Fact;
	double m_dfB2Fact;
};
