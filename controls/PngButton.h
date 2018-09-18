#pragma once

#include "stdafx.h"
#include <atlimage.h>
#include <gdiplusheaders.h>
#include <vector>

using namespace ATL;
using namespace std;

//按钮的状态
enum{
CTRL_NOFOCUS = 0x01,//
CTRL_FOCUS,
CTRL_SELECTED,
CTRL_DISABLE,

};
//图片形式
enum
{
BTN_IMG_1 = 1,//
BTN_IMG_3 = 3,//3分图（1个图片内有3小图，下同）
BTN_IMG_4 = 4,//4分图
};

//按钮类型
enum
{
BTN_TYPE_NORMAL = 0x10,//普通BTN
BTN_TYPE_MENU,//菜单类型的BTN
BTN_TYPE_STATIC,//静态类型的BTN
BTN_TYPE_CHECK,
BTN_TYPE_RADIO,
};

class CRadioGroup;

class CPngButton : public CButton
{
public:
	CPngButton();
	virtual ~CPngButton();
	friend class CRadioGroup;
public:
	void Init(char* szpath, int nPartNum, UINT nBtnType = BTN_TYPE_NORMAL);
	CImage *ImageFromResource(HINSTANCE hInstance, UINT uImgID, LPCTSTR lpType);
	void SetTooltip(LPCTSTR lpszToolTipText);
	
	bool GetSelected(){ return m_nState == CTRL_SELECTED; }
protected:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseHOver(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow();
	void PaintParent();
	BOOL PreTranslateMessage(MSG* pMsg);

	bool ShowImage(CDC* pDC, CImage* pImage, UINT nState);

	void SetRadioGroup(CRadioGroup * pRadioGroup){ m_pRadioGroup = pRadioGroup; }
	void SetPngbtnState(int btnstate,bool bErase = true){ 
		if (m_nState != btnstate){
			m_nState = btnstate;
			if (bErase){ PaintParent();InvalidateRect(NULL);}
		} 
	}
public:
	bool m_bTracked;

private:
	int m_nImgPart;

	CImage * m_pImage;

	UINT m_nState;
	UINT m_nBtnType;
	BOOL m_bMenuOn;     //BTN类型为BTN_TYPE_MENU时，是否处于按下的状态

	CRadioGroup * m_pRadioGroup;
	CToolTipCtrl* m_pToolTip;
};

class CRadioGroup
{
public:
	CRadioGroup(){ m_pSelButton = NULL; }
	~CRadioGroup(){}

	void AddButton(CPngButton* item){
		if (item == NULL) return;

		int count = m_vectButtons.size();

		for (int i = 0; i < count; i++) if (m_vectButtons[i] == item) return;

		item->SetRadioGroup(this);

		m_vectButtons.push_back(item);
	}

	CPngButton* GetCurSel(){ return m_pSelButton; }

	void OnSelected(CPngButton* pBtn){ 
		m_pSelButton = pBtn; 
		m_pSelButton->SetPngbtnState(CTRL_SELECTED);

		for (int i = 0; i < m_vectButtons.size(); i++){
			if (m_vectButtons[i] != pBtn){
				m_vectButtons[i]->SetPngbtnState(CTRL_NOFOCUS);
			}
		}

		m_pSelButton->InvalidateRect(NULL);
	}

	UINT GetSelectedID(){
		if (m_pSelButton == NULL) return 0;

		return m_pSelButton->GetDlgCtrlID();
	}
protected:

private:
	vector<CPngButton*> m_vectButtons;
	CPngButton* m_pSelButton;
};
