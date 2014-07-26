/***************************************************************************
   致看到这些源代码的兄弟:
       你好!
       这本来是我为一个商业PDA产品开发的日历程序,最近移植于PC机上, 所以算法
   和数据部分是用纯C++写的,不涉及MFC,所有的代码都是以短节省存储空间为主要目
   的.
	   很高兴你对这些代码有兴趣,你可以随意复制和使用些代码,唯一有一点小小的
   愿望:在你使用和复制给别人时,别忘注明这些代码作者:-)。程序代码也就罢了,后
   面的数据可是我辛辛苦苦从万年历上找出来输进去的。
	   如果你有什么好的意见不妨Mail给我。

       wangfei@hanwang.com.cn
	   或
	   wangfei@engineer.com.cn
                                                                 2000年3月
****************************************************************************/
#if !defined(AFX_CALENDAR1_H__FD9A6DAF_8C3C_493C_AAD4_612134D8F6D4__INCLUDED_)
#define AFX_CALENDAR1_H__FD9A6DAF_8C3C_493C_AAD4_612134D8F6D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Calendar1.h : header file
/////////////////////////////////////////////////////////////////////////////
// CCalendar window
extern const WORD START_YEAR;
extern const WORD END_YEAR;

//define user message select changed
#define UM_SELCHANGE  (WM_USER+222)
#define DTCEM_HIDE_CALENDAR WM_USER + 2 //隐藏日历控件.

#define BTN_UP_MONTH 1
#define BTN_DOWN_MONTH 2
#define COMBOX_MONTH 3
#define COMBOX_YEAR 4
#define BTN_TODAY 5

#include "beautifulcanlendarmonthcombo.h"
#include "beautifulcanlendaryearcombox.h"
 
class CCalendar : public CWnd
{
private:
	WORD    m_iYear, m_iMonth, m_iDay;
	CRect   m_sSelRect;
	CButton m_UpButton;
	CButton m_DownButton;
	CButton m_TodayButton;
	CBeautifulCanlendarMonthCombo m_MonthComBox;
	CBeautifulCanlendarYearCombox m_YearCombox;

public:
	COLORREF m_dwBackColor,  m_dwForeColor;
	COLORREF m_dwSelColor,   m_dwSelForeColor;
	COLORREF m_dwTitleBkColor, m_dwTitleColor;

public:
	CCalendar(WORD iYear, WORD iMonth, WORD iDay);
	CCalendar();
	virtual BOOL Create(RECT &rect, CWnd * pParentWnd, UINT nID);
	BOOL SizeMinReq(BOOL bRepaint = TRUE);

public:
	WORD GetYear(){return m_iYear;}
	WORD GetMonth(){return m_iMonth;}
	WORD GetDay(){return m_iDay;}
	void GetDate(WORD &iYear, WORD &iMonth, WORD &iDay);
	BOOL SetDate(WORD iYear, WORD iMonth, WORD iDay);
 
protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void l_PaintMenuTitle(CPaintDC &dc);
	CButton m_obutToday;
	//{{AFX_MSG(CCalendar)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects,NCCALCSIZE_PARAMS *lpncsp);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEditChangeMonthComboBox();

	afx_msg void OnChangeYearComboBox();
	afx_msg LRESULT OnYearSelChange(WPARAM wParam,LPARAM lParam);
	afx_msg void OnDropdownYearCombo();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);

public:
	//判断iYear是不是闰年
    static BOOL IsLeapYear(WORD iYear)
	{return !(iYear%4)&&(iYear%100) || !(iYear%400);}

	//计算iYear,iMonth,iDay对应是星期几 1年1月1日 --- 65535年12月31日
	static WORD WeekDay(WORD iYear, WORD iMonth, WORD iDay);

	//返回iYear年iMonth月的天数 1年1月 --- 65535年12月
	static WORD MonthDays(WORD iYear, WORD iMonth);

public:
	void KillCapture();
	void InitYearArray();
	virtual ~CCalendar();

private:
	void   l_InitData();

	WORD l_CalcSelectDay(POINT * pt);
	void l_PaintTitle(CPaintDC &dc);
	void l_PaintDate(CPaintDC &dc);
	inline void l_PaintOneDay(CPaintDC &dc, CDC &imgdc, WORD &iDay, 
		                        WORD &iLunarYear,
		                        WORD &iLunarMonth, WORD &iLuanrDay, 
								LONG startx, LONG starty, BYTE bSecondLeapMonth);
public:
	afx_msg void OnActivateApp(BOOL bActive, DWORD dwThreadID);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDAR1_H__FD9A6DAF_8C3C_493C_AAD4_612134D8F6D4__INCLUDED_)
