// DlgDataMon.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "DlgDataMon.h"
#include "afxdialogex.h"
#include <string>

using namespace std;

// CDlgDataMon 对话框

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


// CDlgDataMon 消息处理程序

void CDlgDataMon::SetupList1()
{
	m_items1.push_back(itemdata(1, "1. 飞行计时时间"));

	m_items1.push_back(itemdata(2, "2. x1轴加表视速度增量"));
	m_items1.push_back(itemdata(3, "3. y1轴加表视速度增量"));
	m_items1.push_back(itemdata(4, "4. z1轴加表视速度增量"));

	m_items1.push_back(itemdata(5, "5. x1轴陀螺角度增量"));
	m_items1.push_back(itemdata(6, "6. y1轴陀螺角度增量"));
	m_items1.push_back(itemdata(7, "7. z1轴陀螺角度增量"));

	m_items1.push_back(itemdata(8, "8. 组合导航装置自检状态"));
	m_items1.push_back(itemdata(9, "9. UTC天内秒计时"));

	m_items1.push_back(itemdata(10, "10. 弹下点经度"));
	m_items1.push_back(itemdata(11, "11. 弹下点纬度"));
	m_items1.push_back(itemdata(12, "12. 弹下点高度"));

	m_items1.push_back(itemdata(13, "13. GPS84系位置x分量"));
	m_items1.push_back(itemdata(14, "14. GPS84系位置y分量"));
	m_items1.push_back(itemdata(15, "15. GPS84系位置z分量"));
	m_items1.push_back(itemdata(16, "16. GPS84系速度x分量"));
	m_items1.push_back(itemdata(17, "17. GPS84系速度y分量"));
	m_items1.push_back(itemdata(18, "18. GPS84系速度z分量"));

	m_items1.push_back(itemdata(19, "19. PDOP值"));
	m_items1.push_back(itemdata(20, "20. 接收机状态码"));
	m_items1.push_back(itemdata(21, "21. 定位卫星数"));

	m_items1.push_back(itemdata(22, "22. 发射系俯仰角"));
	m_items1.push_back(itemdata(23, "23. 发射系偏航角"));
	m_items1.push_back(itemdata(24, "24. 发射系滚动角"));

	m_items1.push_back(itemdata(25, "25. 重力加速度估算值"));
	m_items1.push_back(itemdata(26, "26. 地球加速度估算值"));

	m_items1.push_back(itemdata(27, "27. 数据有效性标识字"));
	m_items1.push_back(itemdata(28, "28. 不水平计算状态标识字"));

	m_items1.push_back(itemdata(29, "29. +B2电压"));
	m_items1.push_back(itemdata(30, "30. +B3电压"));
	m_items1.push_back(itemdata(31, "31. +B4电压"));
	m_items1.push_back(itemdata(32, "32. +D1电压"));

	m_items1.push_back(itemdata(33, "33. 无线接收机自检状态"));
	m_items1.push_back(itemdata(34, "34. 1#反馈遥测信号"));
	m_items1.push_back(itemdata(35, "35. 2#反馈遥测信号"));
	m_items1.push_back(itemdata(36, "36. 3#反馈遥测信号"));
	m_items1.push_back(itemdata(37, "37. 4#反馈遥测信号"));

	m_items1.push_back(itemdata(38, "38. 舵+15V电源遥测"));
	m_items1.push_back(itemdata(39, "39. 舵-15V电源遥测"));
	m_items1.push_back(itemdata(40, "40. 舵P15V电源遥测"));

	m_items1.push_back(itemdata(41, "41. 电磁阀控制字"));
	m_items1.push_back(itemdata(42, "42. 电磁阀控制字回采"));

	m_items1.push_back(itemdata(43, "43. 时序码1"));
	m_items1.push_back(itemdata(44, "44. 时序码回采1"));
	m_items1.push_back(itemdata(45, "45. 陀螺+5V"));
	m_items1.push_back(itemdata(46, "46. 陀螺-5V"));
	m_items1.push_back(itemdata(47, "47. GPS+5V"));
	m_items1.push_back(itemdata(48, "48. 计算机+5V"));

	m_items1.push_back(itemdata(49, "49. 飞行/模飞状态字"));
	m_items1.push_back(itemdata(50, "50. 飞行阶段状态字"));

	for (int i = 0; i < m_items1.size(); i++)
	{
		m_listBox1.AddString(m_items1[i].m_name.c_str());
		m_listBox1.SetItemData(i, m_items1[i].m_id);
	}

}

void CDlgDataMon::SetupList2()
{
	m_items2.push_back(itemdata(1, "1. 组合导航计时时间"));

	m_items2.push_back(itemdata(2, "2. x1轴加表视速度增量"));
	m_items2.push_back(itemdata(3, "3. y1轴加表视速度增量"));
	m_items2.push_back(itemdata(4, "4. z1轴加表视速度增量"));

	m_items2.push_back(itemdata(5, "5. x1轴陀螺角度增量"));
	m_items2.push_back(itemdata(6, "6. y1轴陀螺角度增量"));
	m_items2.push_back(itemdata(7, "7. z1轴陀螺角度增量"));

	m_items2.push_back(itemdata(8, "8. 组合导航装置自检状态"));
	m_items2.push_back(itemdata(9, "9. 组合导航装置温度"));
	m_items2.push_back(itemdata(10, "10. UTC天内秒计时"));

	m_items2.push_back(itemdata(11, "11. 弹下点经度"));
	m_items2.push_back(itemdata(12, "12. 弹下点纬度"));
	m_items2.push_back(itemdata(13, "13. 弹下点高度"));

	m_items2.push_back(itemdata(14, "14. GPS84系位置x分量"));
	m_items2.push_back(itemdata(15, "15. GPS84系位置y分量"));
	m_items2.push_back(itemdata(16, "16. GPS84系位置z分量"));
	m_items2.push_back(itemdata(17, "17. GPS84系速度x分量"));
	m_items2.push_back(itemdata(18, "18. GPS84系速度y分量"));
	m_items2.push_back(itemdata(19, "19. GPS84系速度z分量"));

	m_items2.push_back(itemdata(19, "20. PDOP值"));
	m_items2.push_back(itemdata(20, "21. 接收机状态码"));
	m_items2.push_back(itemdata(21, "22. 定位卫星数"));

	m_items2.push_back(itemdata(22, "23. 发射系俯仰角"));
	m_items2.push_back(itemdata(23, "24. 发射系偏航角"));
	m_items2.push_back(itemdata(24, "25. 发射系滚动角"));

	m_items2.push_back(itemdata(25, "26. 重力加速度估算值"));
	m_items2.push_back(itemdata(26, "27. 地球加速度估算值"));

	m_items2.push_back(itemdata(27, "28. 数据有效性标识字"));
	m_items2.push_back(itemdata(28, "29. 不水平计算状态标识字"));	

	for (int i = 0; i < m_items2.size(); i++)
	{
		m_listBox2.AddString(m_items2[i].m_name.c_str());
		m_listBox2.SetItemData(i, m_items2[i].m_id);
	}
}

void CDlgDataMon::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
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

	// TODO:  在此添加额外的初始化
	InitUI();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
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
	// TODO:  在此添加控件通知处理程序代码
	CheckListAll(m_listBox1, 1);
}

void CDlgDataMon::OnBnClickedBtnClearall1()
{
	// TODO:  在此添加控件通知处理程序代码
	CheckListAll(m_listBox1, 0);
}

void CDlgDataMon::OnBnClickedBtnSelectall2()
{
	// TODO:  在此添加控件通知处理程序代码
	CheckListAll(m_listBox2, 1);
}


void CDlgDataMon::OnBnClickedBtnClearall2()
{
	// TODO:  在此添加控件通知处理程序代码
	CheckListAll(m_listBox2, 0);
}
