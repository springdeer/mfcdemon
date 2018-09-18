#include "stdafx.h"
#include "PngButton.h"
#include "stdafx.h"
#include "PngButton.h"
#include "resource.h"
#include "gdiplusgraphics.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__;
#endif  

/////////////////////////////////////////////////////////////////////////////  
// CPngButton  


CPngButton::CPngButton()
{
	m_bTracked = false;
	m_bMenuOn = FALSE;

	m_nImgPart = 0;
	m_pImage = NULL;

	m_nState = CTRL_NOFOCUS;
	m_nBtnType = BTN_TYPE_NORMAL;

	m_pImage = new CImage();

	m_pRadioGroup = NULL;

	m_pToolTip = NULL;
}

CPngButton::~CPngButton()
{
	if (m_pImage != NULL)
	{
		delete m_pImage;
		m_pImage = NULL;
	}
}

void CPngButton::SetTooltip(LPCTSTR lpszToolTipText)
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

BOOL CPngButton::PreTranslateMessage(MSG* pMsg)
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

void CPngButton::Init(char* szpath, int nPartNum, UINT nBtnType)
{
	//m_pImage  = ImageFromResource(AfxGetResourceHandle(), nImg, L"PNG");
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

	m_nBtnType  = nBtnType;
	m_nImgPart  = nPartNum;

	if (m_pImage  == NULL)
		return;

	CRect rcButton;

	if (m_nImgPart  == BTN_IMG_1)
		rcButton  = CRect(0, 0, m_pImage->GetWidth(), m_pImage->GetHeight());
	else if(m_nImgPart  == BTN_IMG_3)
		rcButton  = CRect(0, 0, m_pImage->GetWidth() / 3, m_pImage->GetHeight());
	else if (m_nImgPart  == BTN_IMG_4)
		rcButton  = CRect(0, 0, m_pImage->GetWidth() / 4, m_pImage->GetHeight());
	else
		return;
		
	SetWindowPos(NULL, 0, 0, rcButton.Width(), rcButton.Height(), SWP_NOACTIVATE | SWP_NOMOVE);
}

BEGIN_MESSAGE_MAP(CPngButton, CButton)
	//{{AFX_MSG_MAP(CPngButton)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHOver)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPngButton message handlers

void CPngButton::OnPaint()
{
	CButton::OnPaint();
}

void CPngButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (!IsWindowEnabled())
		m_nState = CTRL_DISABLE;

	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	ShowImage(&dc, m_pImage, m_nState);
}

bool CPngButton::ShowImage(CDC* pDC, CImage* pImage, UINT nState)
{
	bool bSuc = false;

	if (pImage != NULL)
	{
		CRect rcButton;

		if (m_nImgPart == BTN_IMG_1)
			rcButton = CRect(0, 0, m_pImage->GetWidth(), m_pImage->GetHeight());
		else if (m_nImgPart == BTN_IMG_3)
		{
			if (nState == CTRL_NOFOCUS)
				rcButton = CRect(0, 0, m_pImage->GetWidth() / 3, m_pImage->GetHeight());
			else if (nState == CTRL_FOCUS)
				rcButton = CRect(m_pImage->GetWidth() / 3, 0, m_pImage->GetWidth() / 3 * 2, m_pImage->GetHeight());
			else if (nState == CTRL_SELECTED)
				rcButton = CRect(m_pImage->GetWidth() / 3 * 2, 0, m_pImage->GetWidth(), m_pImage->GetHeight());
			else
				return false;
		}
		else if (m_nImgPart == BTN_IMG_4)
		{
			if (nState == CTRL_NOFOCUS)
				rcButton = CRect(0, 0, m_pImage->GetWidth() / 4, m_pImage->GetHeight());
			else if (nState == CTRL_FOCUS)
				rcButton = CRect(m_pImage->GetWidth() / 4, 0, m_pImage->GetWidth() / 4 * 2, m_pImage->GetHeight());
			else if (nState == CTRL_SELECTED)
				rcButton = CRect(m_pImage->GetWidth() / 4 * 2, 0, m_pImage->GetWidth() / 4 * 3, m_pImage->GetHeight());
			else if (nState == CTRL_DISABLE)
				rcButton = CRect(m_pImage->GetWidth() / 4 * 3, 0, m_pImage->GetWidth(), m_pImage->GetHeight());
			else
				return false;
		}
		else
			return false;

		//Graphics graph(pDC->GetSafeHdc());
		m_pImage->Draw(pDC->GetSafeHdc(), 0, 0, rcButton.Width(), rcButton.Height(),rcButton.left, rcButton.top, rcButton.Width(), rcButton.Height());
		//graph.DrawImage(pImage, 0, 0, rcButton.left, rcButton.top, rcButton.Width(), rcButton.Height(), UnitPixel);
		//graph.ReleaseHDC(pDC->GetSafeHdc());
		
		bSuc = true;
	}	
	
	return bSuc;
}

//Image *CPngButton::ImageFromResource(HINSTANCE hInstance, UINT uImgID, LPCTSTR lpType)
//{
//	HRSRC hResInfo = ::FindResource(hInstance, MAKEINTRESOURCE(uImgID), lpType);
//	if (hResInfo == NULL)
//		return NULL; //fail
//	DWORD dwSize;
//	dwSize = SizeofResource(hInstance, hResInfo); //get resource size(bytes)
//	HGLOBAL hResData;
//	hResData = ::LoadResource(hInstance, hResInfo);
//	if (hResData == NULL)
//		return NULL; //fail
//	HGLOBAL hMem;
//	hMem = ::GlobalAlloc(GMEM_MOVEABLE, dwSize);
//	if (hMem == NULL){
//		::FreeResource(hResData);
//		return NULL;
//	}
//	LPVOID lpResData, lpMem;
//	lpResData = ::LockResource(hResData);
//	lpMem = ::GlobalLock(hMem);
//	::CopyMemory(lpMem, lpResData, dwSize); //copy memory
//	::GlobalUnlock(hMem);
//	::FreeResource(hResData); //free memory
//
//	IStream *pStream;
//	HRESULT hr;
//	hr = ::CreateStreamOnHGlobal(hMem, TRUE, &pStream);//create stream object
//	Image *pImage = NULL;
//	if (SUCCEEDED(hr)){
//		pImage = Image::FromStream(pStream);//get GDI+ pointer
//		pStream->Release();
//	}
//	::GlobalFree(hMem);
//	return pImage;
//}

void CPngButton::PreSubclassWindow()
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

BOOL CPngButton::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CPngButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
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

void CPngButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_nBtnType == BTN_TYPE_NORMAL){
		if (m_nState != CTRL_SELECTED)
		{
			m_nState = CTRL_SELECTED;

			if (!m_bMenuOn)
				m_bMenuOn = TRUE;

			PaintParent();
		}
	}
	else if (m_nBtnType == BTN_TYPE_CHECK){
		m_nState = (m_nState == CTRL_SELECTED ? CTRL_FOCUS: CTRL_SELECTED);
		PaintParent();
	}
	else if (m_nBtnType == BTN_TYPE_RADIO && m_pRadioGroup){
		PaintParent();
		m_pRadioGroup->OnSelected(this);
	}
	
	CButton::OnLButtonDown(nFlags, point);
}

void CPngButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_nBtnType == BTN_TYPE_NORMAL){
		if (m_nState != CTRL_FOCUS)
		{
			m_nState = CTRL_FOCUS;
			PaintParent();
		}
	}
	else if (m_nBtnType == BTN_TYPE_CHECK || m_nBtnType == BTN_TYPE_RADIO){
		if (m_nState != CTRL_SELECTED && m_nState != CTRL_FOCUS)
		{
			m_nState = CTRL_FOCUS;
		}
		PaintParent();
	}

	CButton::OnLButtonUp(nFlags, point);
}

LRESULT CPngButton::OnMouseHOver(WPARAM wParam, LPARAM lParam)
{
	//鼠标放上去时
	if (m_nBtnType == BTN_TYPE_NORMAL){
		if (m_nState != CTRL_FOCUS)
		{
			m_nState = CTRL_FOCUS;
			PaintParent();
		}
	}
	else if (m_nBtnType == BTN_TYPE_CHECK || m_nBtnType == BTN_TYPE_RADIO){
		if (m_nState != CTRL_SELECTED && m_nState != CTRL_FOCUS)
		{
			m_nState = CTRL_FOCUS;
		}

		PaintParent();
	}
	

	return 0;
}
LRESULT CPngButton::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	//鼠标移开时
	m_bTracked = false;

	if (m_nBtnType == BTN_TYPE_NORMAL)
		m_nState = CTRL_NOFOCUS;
	else if (m_nBtnType == BTN_TYPE_MENU)
	{
		if (m_bMenuOn)
			m_nState = CTRL_SELECTED;
		else
			m_nState = CTRL_NOFOCUS;
	}

	PaintParent();


	return 0;
}

void CPngButton::PaintParent()
{
	CRect   rect;
	GetWindowRect(&rect);
	GetParent()->ScreenToClient(&rect);
	GetParent()->InvalidateRect(&rect);
}

