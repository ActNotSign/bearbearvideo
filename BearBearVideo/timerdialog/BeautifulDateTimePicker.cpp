// BeautifulDateTimePicker.cpp : implementation file
//

#include "stdafx.h"
#include "..\BearBearVideo.h"

#include "BeautifulDateTimePicker.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HCURSOR CPickerButton::g_hCursorLink = NULL;
/////////////////////////////////////////////////////////////////////////////
// CBeautifulDateTimePicker

CBeautifulDateTimePicker::CBeautifulDateTimePicker() 
{
	m_background = RGB(255,255,255);
	m_bInCreate = FALSE;
}

CBeautifulDateTimePicker::~CBeautifulDateTimePicker()
{
}


BEGIN_MESSAGE_MAP(CBeautifulDateTimePicker, CDateTimeCtrl)
	//{{AFX_MSG_MAP(CBeautifulDateTimePicker)
	ON_WM_CREATE()
	ON_MESSAGE(DTCEM_HIDE_CALENDAR,OnHideCalendar)
	ON_MESSAGE(DTCEM_BEFORE_CREATE,OnBeforeCreate)
	ON_WM_NCPAINT() 
	ON_WM_NCCALCSIZE()
	ON_MESSAGE(UM_SELCHANGE,OnSelChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBeautifulDateTimePicker message handlers

void CBeautifulDateTimePicker::OnNcCalcSize(BOOL bCalcValidRects,NCCALCSIZE_PARAMS *lpncsp)
{
	lpncsp->rgrc[0].top -= 1;
    lpncsp->rgrc[0].left -= 1;
	lpncsp->rgrc[0].bottom += 1;
	lpncsp->rgrc[0].right += 1;
	CDateTimeCtrl::OnNcCalcSize(bCalcValidRects,lpncsp);	
}

void CBeautifulDateTimePicker::PreSubclassWindow() 
{
	CDateTimeCtrl::PreSubclassWindow();

	if(m_bInCreate)
	{
        return;
	}

    PostMessage(DTCEM_BEFORE_CREATE);

}

void CBeautifulDateTimePicker::OnNcPaint()
{
	if(!::IsWindow(m_hWnd))
	{
		return;
	}

	CDC  *pWinDC = GetWindowDC();
    if(pWinDC)
	{
        DrawNormalFrame();
	}
    ReleaseDC(pWinDC);

}

void CBeautifulDateTimePicker::DrawNormalFrame()
{
	CDC *dc = GetWindowDC();

	CRect clientRect;
	GetWindowRect(&clientRect);
	clientRect.right = clientRect.Width();
	clientRect.bottom = clientRect.Height();
    clientRect.left = 0 ;
    clientRect.top = 0 ;
	

	//�����������߿�ͱ�������ɫ��
	CBrush newBrush,*oldBrush;
	CPen newPen,*oldPen;
	newBrush.CreateStockObject(NULL_BRUSH);
	newPen.CreatePen(0,1,RGB(0,0,0));
	oldBrush = (CBrush *)dc->SelectObject(&newBrush);
	oldPen = (CPen *)dc->SelectObject(&newPen);
	dc->Rectangle(clientRect);

	newPen.DeleteObject();
	newPen.CreatePen(0,2,m_background);
	oldPen = (CPen *)dc->SelectObject(&newPen);
	clientRect.left += 2;
	clientRect.top += 2;
	clientRect.right -= 1;
	clientRect.bottom -= 1;
	dc->Rectangle(clientRect);

	dc->SelectObject(oldPen);
	dc->SelectObject(oldBrush); 
    
   
}


int CBeautifulDateTimePicker::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	m_bInCreate = TRUE; 

	if (CDateTimeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rcPickerButton;
	GetClientRect(rcPickerButton);
    rcPickerButton.left = rcPickerButton.Width() - rcPickerButton.Height() - 2;
	rcPickerButton.bottom = rcPickerButton.bottom + 1;

	m_PickerButton.Create("",WS_CHILD | WS_VISIBLE, rcPickerButton,
		                  this, DTCEM_PICKER_BUTTON_ID
						  );

	CRect rcBeautifulCalendar;
    GetWindowRect(&rcBeautifulCalendar);
  
	rcBeautifulCalendar.right = rcBeautifulCalendar.left + 300;
	rcBeautifulCalendar.bottom = rcBeautifulCalendar.top + 300;

	m_BeautifulCalendarWnd.CreateEx( 0, NULL, NULL, WS_CHILD |
		                            WS_POPUP | WS_BORDER | WS_CLIPSIBLINGS,
									rcBeautifulCalendar, this, 0
									);
//	m_BeautifulCalendarWnd.m_Parent = this;
	
	return 0;
}


/**
 * ����:
 *   �����ڿؼ�����ǰ���¼���Ӧ����ʵ�����ν�Ĵ���ǰ�Ǽٵģ��Ǳ����໯��ʱ�򴥷���.
 *
 **/
LRESULT CBeautifulDateTimePicker::OnBeforeCreate(WPARAM wParam, LPARAM lParam)
{
	//��ȡ��ǰ�ؼ��ĸ�����
	CWnd* pParentWnd = GetParent();
	if(pParentWnd == NULL)
	{
        pParentWnd = GetDesktopWindow();
    }

	//���´��������жϸô����Ƿ��ڻ�ȡ�����״̬
	CWnd* pWndFocus = CWnd::GetFocus();
    BOOL bFocus = (pWndFocus == this);

	//���´����ǻ�ȡ��ǰ�ؼ���STYLE����չSTYLE
	DWORD dwStyle = GetStyle();
    DWORD dwStyleEx = GetExStyle();

	//��ȡ�ÿؼ���Rect
	CRect ClientRect;
	GetWindowRect(&ClientRect);
	pParentWnd->ScreenToClient(&ClientRect);

	//��ȡ�ÿؼ���CTRLID 
	UINT nCtrlID = GetDlgCtrlID();

    //��ȡ��ǰ�ؼ�������
	CFont* pFont = GetFont();

	//��ȡ�ÿؼ�����һ������
    CWnd* pWndBefore = GetNextWindow(GW_HWNDPREV);

    //���𽫱����໯�Ŀؼ��Ĵ���
	DestroyWindow();
	m_hWnd = NULL;

	//�Ѵ�����־�޸ĳ��Ѿ�����
	m_bInCreate = TRUE;

	//��ʼ�����ؼ��Ĵ���
	if(!CWnd::CreateEx(dwStyleEx, DATETIMEPICK_CLASS, NULL, dwStyle,
		ClientRect, pParentWnd, nCtrlID)
	  )
	{
        return S_FALSE;
	}

	//���ÿؼ�������
	if(pFont == NULL)
	{
        pFont = pParentWnd->GetFont();
	}

    SetFont(pFont);


	//����ÿؼ��н��㣬�򴴽����֮���������ý���
    if(bFocus)
	{
        SetFocus();
	}

    //���������ö�����
	SetWindowPos(pWndBefore == NULL ? &CWnd::wndBottom : pWndBefore, 
		          0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE
				 );

	return S_OK;
}

/**
 * ����:
 *   ������Ӧ���Ըÿؼ����ӿؼ����¼�.
 *
 **/
BOOL CBeautifulDateTimePicker::OnCommand(WPARAM wParam, LPARAM lParam) 
{
    
	//��������Ӧ�ұߵ��Ǹ���ť���¼�.
	if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == DTCEM_PICKER_BUTTON_ID)
	{
		 ShowCalendar();
	}
	
	return CDateTimeCtrl::OnCommand(wParam, lParam);
}

LRESULT CBeautifulDateTimePicker::OnHideCalendar(WPARAM wParam,LPARAM lParam)
{
	/*
	SYSTEMTIME sysTime; 
//	m_BeautifulCalendarWnd.GetMonthCalCtrl()->GetCurSel(&sysTime); 
 
	//UpdateData(TRUE);
    //SetTime(&sysTime);
    //UpdateData(FALSE);

	
	int y = sysTime.wYear;
    int m = sysTime.wMonth ;
    int d = sysTime.wDay;
    CTime time(y,m,d,0,0,0);
    
    SetTime(&time);


	HideCalendar();
	*/
	return S_OK;
}

LRESULT CBeautifulDateTimePicker::OnSelChange(WPARAM wParam,LPARAM lParam)
{
    int y = lParam;
    //int m = sysTime.wMonth ;
    //int d = sysTime.wDay;
	return S_OK;
}

BOOL CBeautifulDateTimePicker::ShowCalendar()
{
    CRect ClientRect;
	GetWindowRect(&ClientRect);

    COleDateTime oleTime;
    GetTime(oleTime);

	m_BeautifulCalendarWnd.m_Calendar.SetDate(oleTime.GetYear(),oleTime.GetMonth(),oleTime.GetDay());


    m_BeautifulCalendarWnd.SetWindowPos(NULL, ClientRect.left , ClientRect.bottom ,
		                                0, 0, SWP_NOSIZE | SWP_NOZORDER |
									    SWP_NOACTIVATE
									   );

	
	CWnd* pParent = GetParent();
	if (pParent != NULL)
	{
		NMHDR nmhdr;
		nmhdr.code = DTN_DROPDOWN;
		nmhdr.hwndFrom = GetSafeHwnd();
		nmhdr.idFrom = GetDlgCtrlID();
		pParent->SendMessage(WM_NOTIFY, (WPARAM)nmhdr.idFrom, (LPARAM)&nmhdr);
	}


    m_BeautifulCalendarWnd.ShowWindow(SW_SHOW);
    m_BeautifulCalendarWnd.SetFocus();
	m_BeautifulCalendarWnd.m_Calendar.SetCapture();


 
	return TRUE;
}

BOOL CBeautifulDateTimePicker::HideCalendar()
{
	
	if(::IsWindow(m_BeautifulCalendarWnd.GetSafeHwnd()))
	{
		m_BeautifulCalendarWnd.ShowWindow(SW_HIDE);
	}
	return TRUE;
}


/*********************������ר��ΪCPickerButton�ĺ�����************************/
BEGIN_MESSAGE_MAP(CPickerButton, CButton)
	//{{AFX_MSG_MAP(CPickerButton)
    ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CBeautifulDateTimePicker::CPickerButton::CPickerButton() : isOn(false)
{

}

void CBeautifulDateTimePicker::CPickerButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    DrawNormalFace();

    UINT btState = lpDrawItemStruct->itemState;

	if(isOn == true)
	{
		DrawHoverFace();
	}
    
	if(btState & ODS_DISABLED)
	{
	//	DrawDisabledFace(lpDrawItemStruct);
		return;
	}

	if(btState & ODS_SELECTED)
	{
		DrawHoverFace();
	}
}

void CBeautifulDateTimePicker::CPickerButton::PreSubclassWindow()
{
	ModifyStyle(0,BS_OWNERDRAW);
	SetCursor(AfxGetApp()->LoadCursor(IDC_HAND));
}

LRESULT CBeautifulDateTimePicker::CPickerButton::OnMouseOut(WPARAM   wParam,   LPARAM   lParam)
{
	isOn = false;
    Invalidate();
	return 0;
}

/**
 * ����:
 *   ���øð�ť�����.
 **/
BOOL CBeautifulDateTimePicker::CPickerButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
		if (g_hCursorLink == NULL) {
		static bTriedOnce = FALSE;
		if (!bTriedOnce) {
         CString windir;
         GetWindowsDirectory(windir.GetBuffer(MAX_PATH), MAX_PATH);
         windir.ReleaseBuffer();
         windir += _T("\\winhlp32.exe");
         HMODULE hModule = LoadLibrary(windir);
			if (hModule) {
				g_hCursorLink =
					CopyCursor(::LoadCursor(hModule, MAKEINTRESOURCE(106)));
			}
			FreeLibrary(hModule);
			bTriedOnce = TRUE;
		}
	}
	if (g_hCursorLink) {
		::SetCursor(g_hCursorLink);
		return TRUE;
	}
	return FALSE;
}

void CBeautifulDateTimePicker::CPickerButton::OnMouseIn()
{
	 isOn = true;
	 Invalidate();
	 //DrawItem(&dst);
}

void CBeautifulDateTimePicker::CPickerButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(isOn == false)
	{
        OnMouseIn();
	}
	TRACKMOUSEEVENT tme;
    tme.cbSize = sizeof(TRACKMOUSEEVENT);
	tme.dwFlags = TME_LEAVE;
	tme.dwHoverTime = 0;
	tme.hwndTrack = m_hWnd;
	TrackMouseEvent(&tme);
	CButton::OnMouseMove(nFlags, point);
}


void CBeautifulDateTimePicker::CPickerButton::DrawNormalFace()
{
	CDC *dc = GetDC();

	CRect clientRect;
	GetClientRect(&clientRect);

	dc->FillSolidRect(clientRect,RGB(255,255,255));

	CBitmap pushButtomBmp;
	pushButtomBmp.LoadBitmap(IDB_PUSH_BUTTON_NORMAL);
	BITMAP bmpInfo;
	pushButtomBmp.GetBitmap(&bmpInfo);

	CDC memoryDC;
	memoryDC.CreateCompatibleDC(dc);
	CBitmap *oldBmp = (CBitmap *)memoryDC.SelectObject(&pushButtomBmp);

	
    /*
	dc->BitBlt(clientRect.left + 2,
		clientRect.top + (clientRect.Height() - bmpInfo.bmHeight)/ 2,
		bmpInfo.bmWidth,
		bmpInfo.bmHeight  ,
		&memoryDC,
		0,
		0,
		SRCCOPY
		);
	*/

    dc->StretchBlt(clientRect.left + 1 ,
		           clientRect.top + 1 ,
                   clientRect.Width() - 2 ,
	               clientRect.Height() - 3 ,
                   &memoryDC,
				   0,
				   0,
				   bmpInfo.bmWidth,
				   bmpInfo.bmHeight,
				   SRCCOPY
		         );
	
	memoryDC.SelectObject(oldBmp);
}


void CBeautifulDateTimePicker::CPickerButton::DrawHoverFace() 
{
    CDC *dc = GetDC();

	CRect clientRect;
	GetClientRect(&clientRect);

	dc->FillSolidRect(clientRect,RGB(255,255,255));

	CBitmap pushButtomBmp;
    pushButtomBmp.LoadBitmap(IDB_PUSH_BUTTON_HOVER);
    BITMAP bmpInfo;
	pushButtomBmp.GetBitmap(&bmpInfo);

	CDC memoryDC;
	memoryDC.CreateCompatibleDC(dc);
    CBitmap *oldBmp = (CBitmap *)memoryDC.SelectObject(&pushButtomBmp);
    
	dc->StretchBlt(clientRect.left + 1 ,
		           clientRect.top + 1 ,
                   clientRect.Width() - 2 ,
	               clientRect.Height() - 3 ,
                   &memoryDC,
				   0,
				   0,
				   bmpInfo.bmWidth,
				   bmpInfo.bmHeight,
				   SRCCOPY
		         );

	memoryDC.SelectObject(oldBmp);

}


/*********************������CBeautifulCalendarWnd���ʵ��**********************/
BEGIN_MESSAGE_MAP(CBeautifulCalendarWnd, CWnd)
	//{{AFX_MSG_MAP(CBeautifulCalendarWnd)
	ON_WM_KILLFOCUS() 
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(DTCEM_HIDE_CALENDAR,OnHideCanlendar)
	ON_MESSAGE(UM_SELCHANGE,OnSelChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
void CBeautifulDateTimePicker::CBeautifulCalendarWnd::OnKillFocus(CWnd* pNewWnd)
{
	//if(GetFocus() != &/*m_BeautifulMonthCalCtrl*/m_Calendar)
	//{
		//this->ShowWindow(SW_HIDE);
	//}
	//this->ShowWindow(SW_HIDE);
	//this->GetParent()->GetParent()->SetFocus();
}

LRESULT CBeautifulDateTimePicker::CBeautifulCalendarWnd::OnSelChange(WPARAM wParam,LPARAM lParam)
{
    WORD year,month,day;
    m_Calendar.GetDate(year,month,day);
	CBeautifulDateTimePicker *pDT = (CBeautifulDateTimePicker *)m_pParent;
    CTime time(year,month,day,0,0,0);
    
    pDT->SetTime(&time);

	m_Calendar.KillCapture();
//	ShowWindow(SW_HIDE);
	return S_OK;
}


LRESULT CBeautifulDateTimePicker::CBeautifulCalendarWnd::OnHideCanlendar(WPARAM wParam,LPARAM lParam)
{
	this->ShowWindow(SW_HIDE);
	return S_OK;
}

BOOL CBeautifulDateTimePicker::CBeautifulCalendarWnd::CreateEx(DWORD dwExStyle, 
										LPCTSTR lpszClassName,
		                                LPCTSTR lpszWindowName,
										DWORD dwStyle,
		                                const RECT& rect,
		                                CWnd* pParentWnd, 
										UINT nID,
		                                LPVOID lpParam 
					                    )
{

     m_pParent = pParentWnd;
     return CWnd::CreateEx(dwExStyle, lpszClassName, 
		                   lpszWindowName, dwStyle,
						   rect, pParentWnd, 
						   nID, lpParam
						   );
}

int CBeautifulDateTimePicker::CBeautifulCalendarWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
  if(CWnd::OnCreate(lpCreateStruct) == -1)
  {
      return -1;
  }

  //�޸ĸô���Ϊ���ߴ���
  if (!(lpCreateStruct->style & WS_POPUP))
    ModifyStyleEx(0, WS_EX_TOOLWINDOW);

  //���������ؼ�
  DWORD dwStyle = WS_VISIBLE | WS_CHILD ;

/*
  VERIFY(m_BeautifulMonthCalCtrl.Create(dwStyle, CPoint(0, 0), this, ID_CALENDAR________));
  m_BeautifulMonthCalCtrl.SizeMinReq();
  m_BeautifulMonthCalCtrl.SetOwner(m_pParent);
  

  //����������Ҫ���Ĵ��巶Χ�������Լ����óɸ�����һ����
  //���Լ�����Ϊ���
 
  CRect rcCal;
  m_BeautifulMonthCalCtrl.GetWindowRect(&rcCal);
  CalcWindowRect(&rcCal);
  SetWindowPos(&wndTopMost, 0, 0, rcCal.Width(), rcCal.Height(), SWP_NOMOVE | SWP_NOACTIVATE);
  m_BeautifulMonthCalCtrl.ShowWindow(SW_SHOW);
 
  
  //m_BeautifulMonthCalCtrl.SetColor(MCSC_TITLEBK, RGB(175,204,232));
  m_BeautifulMonthCalCtrl.SetColor(MCSC_TITLETEXT, RGB(255, 255, 255));
  m_BeautifulMonthCalCtrl.SetColor(MCSC_TEXT, RGB(0,0,0));
  m_BeautifulMonthCalCtrl.SetColor(MCSC_MONTHBK, RGB(239,247,247));
  m_BeautifulMonthCalCtrl.SetColor(MCSC_TEXT,RGB(0,128,0));
  m_BeautifulMonthCalCtrl.SetColor(MCSC_TRAILINGTEXT,RGB(120,128,120));
  */
  m_Calendar.Create(CRect(0,0,100,100),this,ID_CALENDAR________);
  m_Calendar.SizeMinReq();
  
  return 0;
}

BOOL CBeautifulDateTimePicker::CBeautifulCalendarWnd::OnEraseBkgnd(CDC *pDC)
{
	COLORREF bkColor = RGB(227,239,243);
	CRect clientRect;
	GetClientRect(&clientRect);
	pDC->FillSolidRect(&clientRect,bkColor);

	/*
	CDC memoryDC;//IDB_BITMAP_BACK
	CBitmap newBitmap,*oldBitmap;
	memoryDC.CreateCompatibleDC(pDC);
	newBitmap.LoadBitmap(IDB_BITMAP_BACK);
	BITMAP bmpInfo;
	newBitmap.GetBitmap(&bmpInfo);
	oldBitmap = (CBitmap *)memoryDC.SelectObject(&newBitmap);

	pDC->StretchBlt(clientRect.left,
			 clientRect.top,
			 clientRect.Width(),
			 bmpInfo.bmHeight,
			 &memoryDC,
			 0,0,bmpInfo.bmWidth,
			 bmpInfo.bmHeight,
			 SRCCOPY
			 );

	memoryDC.SelectObject(oldBitmap);
	*/

	return TRUE;
}

CCalendar *CBeautifulDateTimePicker::CBeautifulCalendarWnd::GetMonthCalCtrl()
{

    return &m_Calendar;
}





void CBeautifulDateTimePicker::CBeautifulCalendarWnd::AlterDatePicker()
{
	//pDT->Invalidate();
	//this->ShowWindow(SW_HIDE); 
}

CBeautifulDateTimePicker * CBeautifulDateTimePicker::CBeautifulCalendarWnd::GetDateTimeCtrl()
{
	
    return (CBeautifulDateTimePicker *)m_pParent;
}
