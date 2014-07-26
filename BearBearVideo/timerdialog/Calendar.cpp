// Calendar1.cpp : implementation file
//

#include "stdafx.h"
#include "BeautifulDateTimePicker.h"
#include "Calendar.h"
#include ".\calendar.h"

//#include "Calendarfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalendar

const WORD START_YEAR = 0;
const WORD END_YEAR   = 2000;

void CCalendar::l_InitData()
{
	SYSTEMTIME systime;
	::GetSystemTime(&systime);

	m_iYear  = systime.wYear;
	m_iMonth = systime.wMonth;
	m_iDay   = systime.wDay;

	m_dwBackColor      = RGB(255,255,255);
	m_dwForeColor      = RGB(0,0,0);
	m_dwSelColor       = RGB(231,241,245);//RGB(150,150,230);
	m_dwSelForeColor   = RGB(255,0,0);
	m_dwTitleBkColor     = RGB(255,255,255);
	m_dwTitleColor = RGB(128,128,128);

}

CCalendar::CCalendar(WORD iYear, WORD iMonth, WORD iDay)
{
	if(!SetDate(iYear, iMonth, iDay))
	{
	    l_InitData();
	}
}

CCalendar::CCalendar()
{
    l_InitData();	
}

CCalendar::~CCalendar()
{
  DestroyWindow(); 
}


BEGIN_MESSAGE_MAP(CCalendar, CWnd)
	//{{AFX_MSG_MAP(CCalendar)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_NCCALCSIZE()
	ON_WM_SETCURSOR()
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(COMBOX_MONTH, OnEditChangeMonthComboBox)
	ON_CBN_SELCHANGE(COMBOX_YEAR, OnChangeYearComboBox)

	ON_MESSAGE(UM_YEAR_SELCHANGE,OnYearSelChange)
	ON_CBN_DROPDOWN(COMBOX_YEAR, OnDropdownYearCombo)
	//}}AFX_MSG_MAP
	ON_WM_ACTIVATEAPP()
END_MESSAGE_MAP()

#define COL_WIDTH    32
#define ROW_HEIGHT   20
#define TITLE_HEIGHT 20

BOOL CCalendar::Create(RECT &rect, CWnd *pParentWnd, UINT nID)
{
	
    CString szClassName = AfxRegisterWndClass(CS_CLASSDC|CS_SAVEBITS|
		                                      CS_HREDRAW|CS_VREDRAW,
                                              0, (HBRUSH)CBrush(RGB(255,255,255)), 0);
   
	rect.right = rect.left + COL_WIDTH*7 +4;
    rect.bottom = rect.top + 2*TITLE_HEIGHT+ROW_HEIGHT*6 +10 ;


	if(!CWnd::CreateEx(WS_EX_CLIENTEDGE, szClassName, _T(""),
		                WS_CHILD|WS_VISIBLE|WS_TABSTOP, rect, 
						pParentWnd, nID, NULL)) 
	{

	    return FALSE;
    }

    UpdateWindow();
     
	 
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CCalendar message handlers
void CCalendar::l_PaintTitle(CPaintDC &dc)
{
   CRect rect ;
   GetClientRect(&rect);

   rect.left ++;   
   rect.top ++;
   rect.top += TITLE_HEIGHT;
   rect.top += 6;
   rect.right --;  
   rect.bottom = rect.top + TITLE_HEIGHT - 3;

   dc.FillRect(&rect, &CBrush(m_dwTitleBkColor));
   

   dc.SetBkColor(m_dwTitleBkColor); 
   dc.SetTextColor(m_dwTitleColor); 

   int startx = rect.left +8;
   dc.SetBkMode(TRANSPARENT);
   dc.SetTextColor(RGB(107,141,162));
   CFont newFont,*oldFont;
   newFont.CreatePointFont(100,"宋体");
   oldFont = (CFont *)dc.SelectObject(&newFont);
   char sztext[][3]={"日","一","二","三","四","五","六"};
   for(int i=0; i <7; i++)
   {
      dc.TextOut(startx, rect.top +2, sztext[i]);
      startx += COL_WIDTH;
   }

   dc.SelectObject(oldFont);

   CPen newPen,*oldPen;
   newPen.CreatePen(0,1,RGB(107,141,162));
   oldPen = (CPen *)dc.SelectObject(&newPen);
   dc.MoveTo(rect.left + 5,rect.bottom);
   dc.LineTo(rect.right - 5,rect.bottom);
   dc.SelectObject(oldPen);
}

void CCalendar::l_PaintOneDay(CPaintDC &dc, CDC &imgdc, WORD &iDay, 
							   WORD &iLunarYear, WORD &iLunarMonth, 
							   WORD &iLunarDay, 
							   LONG startx, LONG starty, BYTE bSecondLeapMonth)
{
	 char text[3];
     sprintf(text, "%2d", iDay);

	 CFont newFont,*oldFont;
     newFont.CreatePointFont(110,"宋体");
     oldFont = (CFont *)dc.SelectObject(&newFont);

     CBeautifulCalendarWnd *pWnd = (CBeautifulCalendarWnd *)GetParent();
     WORD iYear,iMonth;
	 CTime date;
	 CBeautifulDateTimePicker *dateTimePicker =(CBeautifulDateTimePicker *)pWnd->GetDateTimeCtrl();
	 if(dateTimePicker != NULL)
	 {
	     dateTimePicker->GetTime(date);
         iYear = date.GetYear();
         iMonth = date.GetMonth();
	 }

     //TRACE("%d,%d\n",m_iMonth,iMonth);
	 if(iDay++ == m_iDay /* iMonth == m_iMonth && iYear == m_iYear*/)
	 {
		SetRect(&m_sSelRect, startx-1, starty, startx +COL_WIDTH-3,starty + ROW_HEIGHT);
		
		CPen newPen,*oldPen;
		CBrush newBrush,*oldBrush;
		newPen.CreatePen(0,1,RGB(107,141,162));
        newBrush.CreateSolidBrush(m_dwSelColor); 
		oldBrush = (CBrush *)dc.SelectObject(&newBrush);
        oldPen = (CPen *)dc.SelectObject(&newPen);
        dc.Rectangle(m_sSelRect);
		dc.SelectObject(oldPen);
		dc.SelectObject(oldBrush);
		
		dc.SetTextColor(m_dwSelForeColor);
		dc.SetBkMode(TRANSPARENT);
		dc.TextOut(startx + 6, starty +2, text);
		dc.SetBkColor(m_dwBackColor);
		dc.SetTextColor(m_dwForeColor);  		
	 }
	 else
	 {
		dc.TextOut(startx + 6, starty+2, text);
	 }
	 
	 dc.SelectObject(oldFont);
}

void CCalendar::l_PaintDate(CPaintDC &dc)
{
   CDC imgdc;
   imgdc.CreateCompatibleDC(&dc);

   RECT rect;
   GetClientRect(&rect);
   rect.top  +=TITLE_HEIGHT+6;

   dc.SetBkColor(m_dwBackColor);
   dc.SetTextColor(m_dwForeColor);

   WORD day =1;
   WORD iLunarYear, iLunarMonth, iLunarDay;

   for(int i=0; i<6; i++, rect.top += ROW_HEIGHT)
   {
	   long startx = rect.left +2;
	   for(int j=0; j<7; j++,startx += COL_WIDTH)
	   {
		   if(j < WeekDay(m_iYear, m_iMonth, 1) && i==0)
		 	   continue;

		   if(day > MonthDays(m_iYear, m_iMonth))
			   break;
		   
           l_PaintOneDay(dc, imgdc, day, iLunarYear, iLunarMonth,
			   iLunarDay, startx, rect.top + TITLE_HEIGHT, true);
	   }
   }
}

void CCalendar::OnPaint() 
{
    CPaintDC dc(this);

    dc.SetMapMode(0); 

    l_PaintMenuTitle(dc);
    l_PaintTitle(dc);
    l_PaintDate(dc);
    
}

//返回当前的日期
void CCalendar::GetDate(WORD &iYear, WORD &iMonth, WORD &iDay) 
{
	iYear  = m_iYear;
	iMonth = m_iMonth;
	iDay   = m_iDay;
}

BOOL CCalendar::SetDate(WORD iYear, WORD iMonth, WORD iDay)
{
  //if(iYear < START_YEAR || iYear > END_YEAR || iMonth <1 || iMonth >12)
   // 	return FALSE;

	if(iDay <1 || iDay > MonthDays(iYear, iMonth))
		return FALSE;

	m_iYear   = iYear;
	m_iMonth  = iMonth;
	m_iDay    = iDay;

	CString strYear;
	strYear.Format("%d",m_iYear);
	InitYearArray();
	m_YearCombox.SetWindowText(strYear);

	m_MonthComBox.SetCurSel(m_iMonth - 1);

	Invalidate();

	return TRUE;
} 


WORD CCalendar::WeekDay(WORD iYear, WORD iMonth, WORD iDay)
{

   	//数组元素monthday[i]表示第i个月以前的总天数除以7的余数
	WORD monthday[]={0,3,3,6,1,4,6,2,5,0,3,5};
	WORD iDays = (iYear-1)%7 + (iYear-1)/4 - (iYear-1)/100 +(iYear-1)/400;
	iDays += (monthday[iMonth-1] +iDay) ;
	//如果iYear是闰年
    if(IsLeapYear(iYear) && iMonth>2)
		iDays++;
	//返回:0,1,2,3,4,5,6表日、一、二、三、四、五、六
	return iDays%7;
}

BOOL CCalendar::OnCommand(WPARAM wParam, LPARAM lParam)
{
	//如果点了上个月的按钮.
	if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == BTN_UP_MONTH)
	{
		m_iMonth = m_iMonth - 1;
		if(m_iMonth <= 0)
		{
            m_iMonth = 12;
			m_iYear = m_iYear - 1;
		}

		SetDate(m_iYear,m_iMonth,m_iDay);
	
	}

	//如果点了今天这个按钮则执行以下代码
	if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == BTN_TODAY)
	{
        CTime ttime = CTime::GetCurrentTime(); 
		
		SetDate(ttime.GetYear(),ttime.GetMonth(),ttime.GetDay());
	}

	//如果点了下个月的按钮
	if(HIWORD(wParam) == BN_CLICKED && LOWORD(wParam) == BTN_DOWN_MONTH)
	{
		m_iMonth = m_iMonth + 1;
		if(m_iMonth >= 13)
		{
            m_iMonth = 1;
			m_iYear = m_iYear + 1;
		}

		SetDate(m_iYear,m_iMonth,m_iDay);
		//m_MonthComBox.SetCurSel(m_iMonth-1);
	}
	
	return CWnd::OnCommand(wParam,lParam);
}

WORD CCalendar::MonthDays(WORD iYear, WORD iMonth)
{
	switch(iMonth)
	{
	case 1:case 3:case 5:case 7:case 8:case 10:case 12:
		return 31;
		break;
	case 4:case 6:case 9:case 11:
		return 30;
		break;
	case 2:
		//如果是闰年
		if(IsLeapYear(iYear))
			return 29;
		else
			return 28;
		break;
	}
	return 0;
}

WORD CCalendar::l_CalcSelectDay(POINT * pt)
{
	RECT rect;
    GetClientRect(&rect);
	WORD iRow = (pt->y - rect.top - TITLE_HEIGHT -26)/ROW_HEIGHT;
	WORD iCol = (pt->x - rect.left )/COL_WIDTH;

	WORD startcol ,endrow, endcol;
	startcol = WeekDay(m_iYear, m_iMonth, 1);
	endcol   = WeekDay(m_iYear, m_iMonth, MonthDays(m_iYear,m_iMonth));

	
	endrow   = (MonthDays(m_iYear, m_iMonth) + startcol -1)/7 ;
    if(iRow == 0 && iCol < startcol || iRow == endrow && iCol > endcol ||  iRow > endrow)
		return 0;
	
	return iRow *7 + iCol + 1 - startcol ;
}

void CCalendar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//判断鼠标如果不在该区域则隐藏该日历窗口
	CRect clientRect;
	GetClientRect(&clientRect);
	if(!clientRect.PtInRect(point))
	{
		::PostMessage(GetParent()->m_hWnd, DTCEM_HIDE_CALENDAR, MAKELONG(m_iMonth, m_iYear), m_iDay); 
		ReleaseCapture();
		return;
	}
	
	//以下是处理选择了哪个日期的
	WORD day = l_CalcSelectDay(&point);
	if(day !=0 && day != m_iDay)
	{
		m_iDay = day;
		CBeautifulCalendarWnd *pParent = (CBeautifulCalendarWnd *)GetParent();
		pParent->SendMessage(UM_SELCHANGE, MAKELONG(m_iMonth, m_iDay), m_iYear);
		InvalidateRect(m_sSelRect);
		OnPaint();
		InvalidateRect(m_sSelRect);

    }
	SetFocus(); 
	CWnd::OnLButtonDown(nFlags, point);
}


void CCalendar::OnNcCalcSize(BOOL bCalcValidRects,NCCALCSIZE_PARAMS *lpncsp)
{
	lpncsp->rgrc[0].top -= 2;
    lpncsp->rgrc[0].left -= 2;
	lpncsp->rgrc[0].bottom += 2;
	lpncsp->rgrc[0].right += 2;
	CWnd::OnNcCalcSize(bCalcValidRects,lpncsp);	
}

BOOL CCalendar::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	HCURSOR lhCursor;   
    lhCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);   
    SetCursor(lhCursor); 
	return TRUE;
}


BOOL CCalendar::SizeMinReq(BOOL bRepaint/* = TRUE*/)
{
	GetParent()->SetWindowPos(NULL,0,0,COL_WIDTH*7 +4,
		                      2*TITLE_HEIGHT+ROW_HEIGHT*6 +10,SWP_NOMOVE);
	return TRUE;
}

void CCalendar::l_PaintMenuTitle(CPaintDC &dc)
{
    CRect rect ;
    GetClientRect(&rect);

    rect.left += 2;   
    rect.top += 2;
    rect.right -= 4;  
    rect.bottom = rect.top + TITLE_HEIGHT + 4;

	CBrush newBrush,*oldBrush;
	CPen newPen,*oldPen;
	newPen.CreatePen(0,1,RGB(87,117,159));
    newBrush.CreateSolidBrush(/*RGB(227,236,243)*/RGB(87,117,159));
	oldBrush = (CBrush *)dc.SelectObject(&newBrush);
	oldPen = (CPen *)dc.SelectObject(&newPen);
    dc.Rectangle(&rect);
	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);

}

int CCalendar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    m_UpButton.Create("<",WS_CHILD|WS_VISIBLE,CRect(5,5,25,25),this,BTN_UP_MONTH);
	m_DownButton.Create(">",WS_CHILD|WS_VISIBLE,CRect(28,5,48,25),this,BTN_DOWN_MONTH);
    m_MonthComBox.Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST|
		                 WS_VSCROLL,
						 CRect(51,5,115,170),this,
						 COMBOX_MONTH
						 );
    
    m_TodayButton.Create("今天",WS_CHILD|WS_VISIBLE,CRect(183,5,222,25),this,BTN_TODAY);
	
	m_MonthComBox.SetItemHeight(-1,13);
    m_MonthComBox.AddString("一月");
    m_MonthComBox.AddString("二月");
    m_MonthComBox.AddString("三月");
    m_MonthComBox.AddString("四月");
    m_MonthComBox.AddString("五月");
    m_MonthComBox.AddString("六月");
    m_MonthComBox.AddString("七月");
    m_MonthComBox.AddString("八月");
    m_MonthComBox.AddString("九月");
    m_MonthComBox.AddString("十月");
    m_MonthComBox.AddString("十一月");
    m_MonthComBox.AddString("十二月");

	m_MonthComBox.SetCurSel(m_iMonth-1);


	m_YearCombox.Create(WS_CHILD|WS_VISIBLE|CBS_DROPDOWN|
		                WS_VSCROLL,
						CRect(118,5,180,170),this,
						COMBOX_YEAR
						);
    m_YearCombox.SetItemHeight(-1,13);
	m_YearCombox.AddString("-");
	m_YearCombox.AddString("2008");
    m_YearCombox.AddString("2009");
    m_YearCombox.AddString("2009");
    m_YearCombox.AddString("2009");
    m_YearCombox.AddString("2009");
    m_YearCombox.AddString("2009");
	m_YearCombox.AddString("+");
	    

    //SetDate(ttime.GetYear(),ttime.GetMonth(),ttime.GetDay());
	
    

	return CWnd::OnCreate(lpCreateStruct);
}

void CCalendar::OnMouseMove(UINT nFlags, CPoint point) 
{
    CRect rcTitle ;
    GetClientRect(&rcTitle);

	if(rcTitle.PtInRect(point))
	{
		ReleaseCapture();
		SetTimer(10,100,NULL);
	}

    CWnd::OnMouseMove(nFlags,point);
}

void CCalendar::OnTimer(UINT nIDEvent) 
{
    CRect rcTitle ;
    GetClientRect(&rcTitle);

	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);

	if(!rcTitle.PtInRect(point))
	{
        m_YearCombox.HideCaret(); 
		m_MonthComBox.HideCaret();
		SetCapture();
		KillTimer(nIDEvent);
	}
	
	CWnd::OnTimer(nIDEvent);
}

void CCalendar::OnEditChangeMonthComboBox()
{
	int selectIndex = m_MonthComBox.GetCurSel();
    SetDate(m_iYear, selectIndex + 1 , m_iDay);
    Invalidate();
}

void CCalendar::OnChangeYearComboBox()
{
    CString strText;
	m_YearCombox.GetLBText(m_YearCombox.GetCurSel(),strText);
	int iText = atoi(strText);

	m_iYear   = iText;

	CString strYear;
	strYear.Format("%d",m_iYear);
	m_YearCombox.SetWindowText(strYear);
	Invalidate();

}



LRESULT CCalendar::OnYearSelChange(WPARAM wParam,LPARAM lParam)
{
    //m_iYear = wParam;
	return S_OK;
}

void CCalendar::InitYearArray()
{
    WORD yearStart = m_iYear - 3;
	
	if(yearStart <= 1971)
	{
		yearStart = 1971;
	}

	if(yearStart + 2 >= 2045)
	{
        yearStart = 2038;
	}

    for(int i =0; i < 6; i++)
	{
		CString strYear;
		strYear.Format("%d",yearStart + i);
		m_YearCombox.DeleteString(i+1);
		m_YearCombox.InsertString(i+1,strYear);
	}
  
    m_YearCombox.SetCurSel(4);
}

void CCalendar::OnDropdownYearCombo()
{
    InitYearArray();
}

void CCalendar::KillCapture()
{
    KillTimer(10);
	ReleaseCapture();
}

void CCalendar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	//以下是处理选择了哪个日期的
	WORD day = l_CalcSelectDay(&point);
	if(day !=0)
	{
		CBeautifulCalendarWnd *pParent = (CBeautifulCalendarWnd *)GetParent();
        pParent->ShowWindow(SW_HIDE); 
    }
	SetFocus(); 
	CWnd::OnLButtonDown(nFlags, point);
    
}

void CCalendar::OnActivateApp(BOOL bActive, DWORD dwThreadID)
{
    ShowWindow(SW_HIDE);
}
#undef COL_WIDTH
#undef ROW_HEIGHT
#undef TITLE_HEIGHT







