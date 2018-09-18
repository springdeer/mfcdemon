#include "stdafx.h"
#include "PngStateButton.h"

BEGIN_MESSAGE_MAP(CPngStateButton, CButton)
	//{{AFX_MSG_MAP(CPngButton)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPngStateButton::CPngStateButton()
{
	m_nImgPart = 0;
	m_pImage   = new CImage();
	m_nState   = 0;
	m_pToolTip = NULL;
	m_bAnimate = FALSE;
}

void CPngStateButton::Init(char* szpath, int nPartNum)
{
	HRESULT res = m_pImage->Load(szpath);

	if (FAILED(res)) { delete m_pImage; m_pImage = NULL; }
	else{
		if (m_pImage->GetBPP() == 32) //确认该图像包含Alpha通道
		{
			int w;
			int h;
			for (w = 0; w < m_pImage->GetWidth(); w++)
			{
				for (h = 0; h < m_pImage->GetHeight(); h++)
				{
					byte *pByte = (byte *)m_pImage->GetPixelAddress(w, h);
					pByte[0] = pByte[0] * pByte[3] / 255;
					pByte[1] = pByte[1] * pByte[3] / 255;
					pByte[2] = pByte[2] * pByte[3] / 255;
				}
			}
		}
	}

	m_nImgPart = nPartNum;

	if (m_pImage == NULL || m_nImgPart < 1) return;

	CRect rcButton;

	rcButton = CRect(0, 0, m_pImage->GetWidth() / m_nImgPart, m_pImage->GetHeight());

	SetWindowPos(NULL, 0, 0, rcButton.Width(), rcButton.Height(), SWP_NOACTIVATE | SWP_NOMOVE);
}

void CPngStateButton::PaintParent()
{
	CRect   rect;
	GetWindowRect(&rect);
	GetParent()->ScreenToClient(&rect);
	GetParent()->InvalidateRect(&rect);
}

void CPngStateButton::Animate(bool bAnimate, int interval_ms)
{
	if (m_bAnimate != bAnimate){
		if (!bAnimate){
			if (m_uTimer != NULL)
			{
				KillTimer(m_uTimer), m_uTimer = NULL; 
				ShowState(0);
			}
		}else 
			m_uTimer = SetTimer(eAnimate_timer, interval_ms,NULL);
			
		m_bAnimate = bAnimate;
	}
}

void CPngStateButton::ShowState(int state)
{
	if (state < 0 || state >= m_nImgPart) return;

	if (m_nState != state){
		m_nState = state;

		PaintParent();
		InvalidateRect(NULL);
	}
}

void CPngStateButton::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);

	if (NULL != GetSafeHwnd())
	{
		if (!(GetButtonStyle() & WS_CLIPSIBLINGS))
			SetWindowLong(GetSafeHwnd(), GWL_STYLE, GetWindowLong(GetSafeHwnd(),
			GWL_STYLE) | WS_CLIPSIBLINGS);
	}

	CButton::PreSubclassWindow();
}

void CPngStateButton::OnPaint()
{
	CButton::OnPaint();
}

BOOL CPngStateButton::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CPngStateButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (!IsWindowEnabled())
		m_nState = -1;

	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	ShowImage(&dc, m_pImage, m_nState);
}

bool CPngStateButton::ShowImage(CDC* pDC, CImage* pImage, UINT nState)
{
	bool bSuc = false;

	if (pImage != NULL && m_nState < m_nImgPart && m_nState >= 0)
	{
		CRect rcButton;
		int width = m_pImage->GetWidth() / m_nImgPart;
		rcButton = CRect(width * m_nState, 0, width*(m_nState+1), m_pImage->GetHeight());
		
		m_pImage->Draw(pDC->GetSafeHdc(), 0, 0, rcButton.Width(), rcButton.Height(), rcButton.left, rcButton.top, rcButton.Width(), rcButton.Height());
		
		bSuc = true;
	}

	return bSuc;
}

BOOL CPngStateButton::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MBUTTONUP:
	case WM_MOUSEMOVE:
		if (m_pToolTip&&m_pToolTip->GetSafeHwnd() != NULL)
			m_pToolTip->RelayEvent(pMsg);
		break;
	}

	return CButton::PreTranslateMessage(pMsg);
}


void CPngStateButton::SetTooltip(LPCTSTR lpszToolTipText)
{
	ENSURE(GetSafeHwnd() != NULL);

	if (lpszToolTipText == NULL && m_pToolTip && m_pToolTip->GetSafeHwnd() != NULL)
	{
			m_pToolTip->Activate(FALSE);
	}
	else
	{
		if (m_pToolTip->GetSafeHwnd() != NULL)
		{
			m_pToolTip->UpdateTipText(lpszToolTipText, this);
		}
		else
		{
			if (CTooltipManager::CreateToolTip(m_pToolTip, this, AFX_TOOLTIP_TYPE_PLANNER/*AFX_TOOLTIP_TYPE_RIBBON*//*AFX_TOOLTIP_TYPE_BUTTON*/))
			{
				m_pToolTip->AddTool(this, lpszToolTipText);
			}
		}

		if (m_pToolTip->GetSafeHwnd() != NULL) m_pToolTip->Activate(TRUE);
		
	}
}

void CPngStateButton::OnTimer(UINT uEventID)
{
	if (uEventID == eAnimate_timer){
		m_nState = ++m_nState % m_nImgPart;

		if (!m_bAnimate){ ShowState(0); }

		PaintParent();

		InvalidateRect(NULL);
	}
}

BEGIN_MESSAGE_MAP(CTextStateButton, CButton)
	//{{AFX_MSG_MAP(CPngButton)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHOver)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

void CTextStateButton::Init(vector<string> states,HFONT font,int style)
{
	m_style = style;
	if (m_style != eTSBS_BUTTON &&m_style != eTSBS_STATIC)  m_style = eTSBS_BUTTON;

 	m_text.assign(states.begin(), states.end());
 	m_font.Attach(font);
	m_nImgPart = m_text.size();

	m_nInteractiveState = CTRL_NOFOCUS;

	string maxstring = "";
	vector<string>::iterator it = m_text.begin();
	for (; it != m_text.end(); it++){
		if ((*it).size() > maxstring.size()) maxstring = *it;
	}

	//CDC * dc = GetDC();

	//CFont*oldFont = dc->SelectObject(&m_font);

	//CSize sz = dc->GetTextExtent(maxstring.c_str());
	//dc->SelectObject(oldFont);

	//m_rcText.SetRect(0, 0, sz.cx, sz.cy);
	//m_rcText.InflateRect(2, 5);
	//m_rcText.OffsetRect(2, 5);
	//SetWindowPos(NULL, 0, 0, m_rcText.Width(), m_rcText.Height(), SWP_NOACTIVATE | SWP_NOMOVE);

}

void CTextStateButton::ShowText(string str)
{
	m_str = str; 

	//CDC * dc = GetDC();

	//CFont*oldFont = dc->SelectObject(&m_font);
	//CSize sz = dc->GetTextExtent(m_str.c_str());
	//dc->SelectObject(oldFont);

	//m_rcText.SetRect(0, 0, sz.cx, sz.cy);
	//m_rcText.InflateRect(2, 5);
	//m_rcText.OffsetRect(2, 5);
	GetClientRect(&m_rcText);

	//SetWindowPos(NULL, 0, 0, m_rcText.Width(), m_rcText.Height(), SWP_NOACTIVATE | SWP_NOMOVE);

	PaintParent(); 
	InvalidateRect(NULL); 
}

void CTextStateButton::ShowState(int state)
{
	if (m_text.size()>0 && (state < 0 || state >= m_nImgPart)) return;

	if (m_nState != state){
		m_nState = state;

		PaintParent();
		InvalidateRect(NULL);
	}
}

void CTextStateButton::SetTextColor(COLORREF clr)
{
	m_clrText = clr;
}

void CTextStateButton::SetTooltip(LPCTSTR lpszToolTipText)
{
	ENSURE(GetSafeHwnd() != NULL);

	if (lpszToolTipText == NULL && m_pToolTip && m_pToolTip->GetSafeHwnd() != NULL)
	{
		m_pToolTip->Activate(FALSE);
	}
	else
	{
		if (m_pToolTip->GetSafeHwnd() != NULL)
		{
			m_pToolTip->UpdateTipText(lpszToolTipText, this);
		}
		else
		{
			if (CTooltipManager::CreateToolTip(m_pToolTip, this, AFX_TOOLTIP_TYPE_PLANNER/*AFX_TOOLTIP_TYPE_RIBBON*//*AFX_TOOLTIP_TYPE_BUTTON*/))
			{
				m_pToolTip->AddTool(this, lpszToolTipText);
			}
		}

		if (m_pToolTip->GetSafeHwnd() != NULL) m_pToolTip->Activate(TRUE);

	}
}

void CTextStateButton::PreSubclassWindow()
{
	ModifyStyle(0, BS_OWNERDRAW);

	if (NULL != GetSafeHwnd())
	{
		if (!(GetButtonStyle() & WS_CLIPSIBLINGS))
			SetWindowLong(GetSafeHwnd(), GWL_STYLE, GetWindowLong(GetSafeHwnd(),
			GWL_STYLE) | WS_CLIPSIBLINGS);
	}

	CButton::PreSubclassWindow();
}

void CTextStateButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (!IsWindowEnabled())
		m_nState = -1;

	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	if (m_text.size() != 0)
		ShowImage(&dc, m_nState);
	else
		ShowText(&dc, m_str);
}

void CTextStateButton::PaintParent()
{
	CRect   rect;
	GetWindowRect(&rect);
	GetParent()->ScreenToClient(&rect);
	GetParent()->InvalidateRect(&rect);
}

void CTextStateButton::ShowText(CDC *pDC, string str)
{
	bool bSuc = false;

	pDC->SetBkMode(TRANSPARENT);
	CFont* oldFont = pDC->SelectObject(&m_font);
	COLORREF clr = m_clrText;

	if (m_style == eTSBS_BUTTON){
		if (m_nInteractiveState == CTRL_FOCUS){
			clr += 0x003440;
		}
		else if (m_nInteractiveState == CTRL_SELECTED){
			clr += 0x004000;
		}
	}
	
	pDC->SetTextColor(clr);

	GetClientRect(&m_rcText);
	//pDC->Draw3dRect(&m_rcText, clr, clr);
	pDC->DrawText(str.c_str(), &m_rcText, DT_LEFT |DT_VCENTER|DT_SINGLELINE);
	pDC->SelectObject(oldFont);
	//m_pImage->Draw(pDC->GetSafeHdc(), 0, 0, rcButton.Width(), rcButton.Height(), rcButton.left, rcButton.top, rcButton.Width(), rcButton.Height());

	bSuc = true;

}

bool CTextStateButton::ShowImage(CDC* pDC, UINT nState)
{
	bool bSuc = false;

	if (m_nState < m_nImgPart && m_nState >= 0)
	{
		pDC->SetBkMode(TRANSPARENT);
		CFont* oldFont = pDC->SelectObject(&m_font);
		COLORREF clr = m_clrText;

		if (m_style == eTSBS_BUTTON){
			if (m_nInteractiveState == CTRL_FOCUS){
				clr += 0x003440;
			}
			else if (m_nInteractiveState == CTRL_SELECTED){
				clr += 0x004000;
			}
		}

		GetClientRect(&m_rcText);

		//pDC->Draw3dRect(&m_rcText, RGB(123, 123, 123), RGB(123, 200, 200));
		pDC->SetTextColor(clr);
		//pDC->SetTextColor(m_clrText);
		pDC->DrawText(m_text[nState].c_str(), &m_rcText, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		pDC->SelectObject(oldFont);
		//m_pImage->Draw(pDC->GetSafeHdc(), 0, 0, rcButton.Width(), rcButton.Height(), rcButton.left, rcButton.top, rcButton.Width(), rcButton.Height());

		bSuc = true;
	}

	return bSuc;
}

void CTextStateButton::OnPaint()
{
	CButton::OnPaint();
}

void CTextStateButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (!m_bTracked){
		TRACKMOUSEEVENT tme;
		ZeroMemory(&tme, sizeof(TRACKMOUSEEVENT));
		tme.cbSize = sizeof(TRACKMOUSEEVENT);
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		tme.dwHoverTime = 1;
		tme.hwndTrack = this->GetSafeHwnd();
		if (::_TrackMouseEvent(&tme))
			m_bTracked = true;
	}

	CButton::OnMouseMove(nFlags, point);
}


void CTextStateButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	if (m_nInteractiveState != CTRL_SELECTED)
	{
		m_nInteractiveState = CTRL_SELECTED;

		PaintParent();
		InvalidateRect(NULL);
	}

	CButton::OnLButtonDown(nFlags, point);
}


void CTextStateButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_nInteractiveState != CTRL_FOCUS)
	{
		m_nInteractiveState = CTRL_FOCUS;
		PaintParent();
	}

	CButton::OnLButtonUp(nFlags, point);
}


LRESULT CTextStateButton::OnMouseHOver(WPARAM wParam, LPARAM lParam)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (m_nInteractiveState != CTRL_FOCUS)
	{
		m_nInteractiveState = CTRL_FOCUS;
		PaintParent();
	}

	//CButton::OnMouseHover(nFlags, point);

	return 0;
}


LRESULT CTextStateButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_bTracked = false;
	m_nInteractiveState = CTRL_NOFOCUS;
	PaintParent();

	return 0;
}
