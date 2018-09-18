#pragma once
#include <vector>
#include <string>
using namespace std;

// CDlgDataMon 对话框

class itemdata
{
public:
	itemdata(int id, string name){ m_id = id; m_name = name; }

	int m_id;
	string m_name;
};

class CDlgDataMon : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDataMon)
	CDlgDataMon(CWnd* pParent = NULL);   // 标准构造函数
public:
	static CDlgDataMon * Get();

	virtual ~CDlgDataMon();

// 对话框数据
	enum { IDD = IDD_DIALOG_DATAMON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	void InitUI();
	void SetupList1();
	void SetupList2();
	void CheckListAll(CCheckListBox& list, BOOL bCheck);

	DECLARE_MESSAGE_MAP()
private:
	static CDlgDataMon * m_pObj;

	CCheckListBox m_listBox1;
	CCheckListBox m_listBox2;

	vector<itemdata> m_items1;
	vector<itemdata> m_items2;
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSelectall1();
	afx_msg void OnBnClickedBtnClearall1();
	afx_msg void OnBnClickedBtnSelectall2();
	afx_msg void OnBnClickedBtnClearall2();
};
