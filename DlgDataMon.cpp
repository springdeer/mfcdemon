// DlgDataMon.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgDataMon.h"
#include "afxdialogex.h"
#include <string>

using namespace std;

// CDlgDataMon �Ի���

IMPLEMENT_DYNAMIC(CDlgDataMon, CDialogEx)

CDlgDataMon * CDlgDataMon::m_pObj = NULL;

CDlgDataMon * CDlgDataMon::Get()
{
	if (m_pObj == NULL){
		m_pObj = new CDlgDataMon();
		m_pObj->Create(CDlgDataMon::IDD);
	}

	m_pObj->CenterWindow();

	return m_pObj;
}


CDlgDataMon::CDlgDataMon(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDataMon::IDD, pParent)
{
	
}

CDlgDataMon::~CDlgDataMon()
{
}

void CDlgDataMon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgDataMon, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgDataMon::OnBnClickedOk)
	ON_BN_CLICKED(ID_BTN_SELECTALL_1, &CDlgDataMon::OnBnClickedBtnSelectall1)
	ON_BN_CLICKED(ID_BTN_CLEARALL_1, &CDlgDataMon::OnBnClickedBtnClearall1)
	ON_BN_CLICKED(ID_BTN_SELECTALL_2, &CDlgDataMon::OnBnClickedBtnSelectall2)
	ON_BN_CLICKED(ID_BTN_CLEARALL2, &CDlgDataMon::OnBnClickedBtnClearall2)
END_MESSAGE_MAP()


// CDlgDataMon ��Ϣ�������

void CDlgDataMon::SetupList1()
{
	m_items1.push_back(itemdata(1, "1. ���м�ʱʱ��"));

	m_items1.push_back(itemdata(2, "2. x1��ӱ����ٶ�����"));
	m_items1.push_back(itemdata(3, "3. y1��ӱ����ٶ�����"));
	m_items1.push_back(itemdata(4, "4. z1��ӱ����ٶ�����"));

	m_items1.push_back(itemdata(5, "5. x1�����ݽǶ�����"));
	m_items1.push_back(itemdata(6, "6. y1�����ݽǶ�����"));
	m_items1.push_back(itemdata(7, "7. z1�����ݽǶ�����"));

	m_items1.push_back(itemdata(8, "8. ��ϵ���װ���Լ�״̬"));
	m_items1.push_back(itemdata(9, "9. UTC�������ʱ"));

	m_items1.push_back(itemdata(10, "10. ���µ㾭��"));
	m_items1.push_back(itemdata(11, "11. ���µ�γ��"));
	m_items1.push_back(itemdata(12, "12. ���µ�߶�"));

	m_items1.push_back(itemdata(13, "13. GPS84ϵλ��x����"));
	m_items1.push_back(itemdata(14, "14. GPS84ϵλ��y����"));
	m_items1.push_back(itemdata(15, "15. GPS84ϵλ��z����"));
	m_items1.push_back(itemdata(16, "16. GPS84ϵ�ٶ�x����"));
	m_items1.push_back(itemdata(17, "17. GPS84ϵ�ٶ�y����"));
	m_items1.push_back(itemdata(18, "18. GPS84ϵ�ٶ�z����"));

	m_items1.push_back(itemdata(19, "19. PDOPֵ"));
	m_items1.push_back(itemdata(20, "20. ���ջ�״̬��"));
	m_items1.push_back(itemdata(21, "21. ��λ������"));

	m_items1.push_back(itemdata(22, "22. ����ϵ������"));
	m_items1.push_back(itemdata(23, "23. ����ϵƫ����"));
	m_items1.push_back(itemdata(24, "24. ����ϵ������"));

	m_items1.push_back(itemdata(25, "25. �������ٶȹ���ֵ"));
	m_items1.push_back(itemdata(26, "26. ������ٶȹ���ֵ"));

	m_items1.push_back(itemdata(27, "27. ������Ч�Ա�ʶ��"));
	m_items1.push_back(itemdata(28, "28. ��ˮƽ����״̬��ʶ��"));

	m_items1.push_back(itemdata(29, "29. +B2��ѹ"));
	m_items1.push_back(itemdata(30, "30. +B3��ѹ"));
	m_items1.push_back(itemdata(31, "31. +B4��ѹ"));
	m_items1.push_back(itemdata(32, "32. +D1��ѹ"));

	m_items1.push_back(itemdata(33, "33. ���߽��ջ��Լ�״̬"));
	m_items1.push_back(itemdata(34, "34. 1#����ң���ź�"));
	m_items1.push_back(itemdata(35, "35. 2#����ң���ź�"));
	m_items1.push_back(itemdata(36, "36. 3#����ң���ź�"));
	m_items1.push_back(itemdata(37, "37. 4#����ң���ź�"));

	m_items1.push_back(itemdata(38, "38. ��+15V��Դң��"));
	m_items1.push_back(itemdata(39, "39. ��-15V��Դң��"));
	m_items1.push_back(itemdata(40, "40. ��P15V��Դң��"));

	m_items1.push_back(itemdata(41, "41. ��ŷ�������"));
	m_items1.push_back(itemdata(42, "42. ��ŷ������ֻز�"));

	m_items1.push_back(itemdata(43, "43. ʱ����1"));
	m_items1.push_back(itemdata(44, "44. ʱ����ز�1"));
	m_items1.push_back(itemdata(45, "45. ����+5V"));
	m_items1.push_back(itemdata(46, "46. ����-5V"));
	m_items1.push_back(itemdata(47, "47. GPS+5V"));
	m_items1.push_back(itemdata(48, "48. �����+5V"));

	m_items1.push_back(itemdata(49, "49. ����/ģ��״̬��"));
	m_items1.push_back(itemdata(50, "50. ���н׶�״̬��"));

	for (int i = 0; i < m_items1.size(); i++)
	{
		m_listBox1.AddString(m_items1[i].m_name.c_str());
		m_listBox1.SetItemData(i, m_items1[i].m_id);
	}

}

void CDlgDataMon::SetupList2()
{
	m_items2.push_back(itemdata(1, "1. ��ϵ�����ʱʱ��"));

	m_items2.push_back(itemdata(2, "2. x1��ӱ����ٶ�����"));
	m_items2.push_back(itemdata(3, "3. y1��ӱ����ٶ�����"));
	m_items2.push_back(itemdata(4, "4. z1��ӱ����ٶ�����"));

	m_items2.push_back(itemdata(5, "5. x1�����ݽǶ�����"));
	m_items2.push_back(itemdata(6, "6. y1�����ݽǶ�����"));
	m_items2.push_back(itemdata(7, "7. z1�����ݽǶ�����"));

	m_items2.push_back(itemdata(8, "8. ��ϵ���װ���Լ�״̬"));
	m_items2.push_back(itemdata(9, "9. ��ϵ���װ���¶�"));
	m_items2.push_back(itemdata(10, "10. UTC�������ʱ"));

	m_items2.push_back(itemdata(11, "11. ���µ㾭��"));
	m_items2.push_back(itemdata(12, "12. ���µ�γ��"));
	m_items2.push_back(itemdata(13, "13. ���µ�߶�"));

	m_items2.push_back(itemdata(14, "14. GPS84ϵλ��x����"));
	m_items2.push_back(itemdata(15, "15. GPS84ϵλ��y����"));
	m_items2.push_back(itemdata(16, "16. GPS84ϵλ��z����"));
	m_items2.push_back(itemdata(17, "17. GPS84ϵ�ٶ�x����"));
	m_items2.push_back(itemdata(18, "18. GPS84ϵ�ٶ�y����"));
	m_items2.push_back(itemdata(19, "19. GPS84ϵ�ٶ�z����"));

	m_items2.push_back(itemdata(19, "20. PDOPֵ"));
	m_items2.push_back(itemdata(20, "21. ���ջ�״̬��"));
	m_items2.push_back(itemdata(21, "22. ��λ������"));

	m_items2.push_back(itemdata(22, "23. ����ϵ������"));
	m_items2.push_back(itemdata(23, "24. ����ϵƫ����"));
	m_items2.push_back(itemdata(24, "25. ����ϵ������"));

	m_items2.push_back(itemdata(25, "26. �������ٶȹ���ֵ"));
	m_items2.push_back(itemdata(26, "27. ������ٶȹ���ֵ"));

	m_items2.push_back(itemdata(27, "28. ������Ч�Ա�ʶ��"));
	m_items2.push_back(itemdata(28, "29. ��ˮƽ����״̬��ʶ��"));	

	for (int i = 0; i < m_items2.size(); i++)
	{
		m_listBox2.AddString(m_items2[i].m_name.c_str());
		m_listBox2.SetItemData(i, m_items2[i].m_id);
	}
}

void CDlgDataMon::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}

void CDlgDataMon::InitUI()
{
	m_listBox1.SubclassDlgItem(IDC_LIST_COMPUTER, this);
	m_listBox1.SetCheckStyle(BS_AUTOCHECKBOX);

	m_listBox2.SubclassDlgItem(IDC_LIST_NAV, this);
	m_listBox2.SetCheckStyle(BS_AUTOCHECKBOX);

	SetupList1();
	SetupList2();
}

BOOL CDlgDataMon::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitUI();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDlgDataMon::CheckListAll(CCheckListBox& list, BOOL bCheck)
{
	int count = list.GetCount();
	for (int i = 0; i < count; i++){
		list.SetCheck(i, bCheck);
	}
}

void CDlgDataMon::OnBnClickedBtnSelectall1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CheckListAll(m_listBox1, 1);
}

void CDlgDataMon::OnBnClickedBtnClearall1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CheckListAll(m_listBox1, 0);
}

void CDlgDataMon::OnBnClickedBtnSelectall2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CheckListAll(m_listBox2, 1);
}


void CDlgDataMon::OnBnClickedBtnClearall2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CheckListAll(m_listBox2, 0);
}
