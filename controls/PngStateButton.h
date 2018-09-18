#pragma once
#include "stdafx.h"
#include <atlimage.h>
#include <gdiplusheaders.h>
#include <vector>
#include <string>
#include "PngButton.h"

using namespace std;
class CPngStateButton :public CButton{
public:
	CPngStateButton();
	~CPngStateButton(){}

	void Init(char* szpath, int nPartNum);
	
	void ShowState(int state);

	void SetTooltip(LPCTSTR lpszToolTipText);

	void Animate(bool bAnimate, int interval_ms);

	bool IsAnimating(){ return m_bAnimate&&m_uTimer; }

	DECLARE_MESSAGE_MAP()
protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	void PaintParent();
	bool ShowImage(CDC* pDC,CImage * image, UINT nState);
	BOOL PreTranslateMessage(MSG* pMsg);

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT uEventID);

protected:
	CToolTipCtrl* m_pToolTip;
	enum{eAnimate_timer=101};
private:
	int m_nImgPart;
	CImage * m_pImage;
	int m_nState;
	bool m_bAnimate;
	UINT m_uTimer;
};

class CTextStateButton :public CButton
{
public:
	CTextStateButton(){ m_pToolTip = NULL; m_bTracked = false; m_clrText = RGB(200, 125, 198); }
	~CTextStateButton(){}
	void Init(vector<string> states, HFONT font, int style = eTSBS_BUTTON);
	void ShowText(string str);
	void ShowState(int state);
	void SetTooltip(LPCTSTR lpszToolTipText);
	void SetTextColor(COLORREF clr);
	enum{ eTSBS_BUTTON, eTSBS_STATIC };

	DECLARE_MESSAGE_MAP()
	
protected:
	CToolTipCtrl* m_pToolTip;
protected:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void ShowText(CDC *dc, string str);
	void PaintParent();
	bool ShowImage(CDC* pDC,UINT nState);

	afx_msg BOOL OnEraseBkgnd(CDC* pDC){ return TRUE; }
	afx_msg void OnPaint();
private:
	vector<string> m_text;
	string m_str;
	COLORREF m_clrText;
	int   m_nState;
	int   m_nInteractiveState;
	int   m_nImgPart;
	CFont m_font;
	CRect m_rcText;
	bool  m_bTracked;
	int   m_style;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseHOver(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMouseLeave(WPARAM wParam, LPARAM lParam);
};