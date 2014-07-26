/***************************************************************************
   �¿�����ЩԴ������ֵ�:
       ���!
       �Ȿ������Ϊһ����ҵPDA��Ʒ��������������,�����ֲ��PC����, �����㷨
   �����ݲ������ô�C++д��,���漰MFC,���еĴ��붼���Զ̽�ʡ�洢�ռ�Ϊ��ҪĿ
   ��.
	   �ܸ��������Щ��������Ȥ,��������⸴�ƺ�ʹ��Щ����,Ψһ��һ��СС��
   Ը��:����ʹ�ú͸��Ƹ�����ʱ,����ע����Щ��������:-)���������Ҳ�Ͱ���,��
   ������ݿ����������������������ҳ������ȥ�ġ�
	   �������ʲô�õ��������Mail���ҡ�

       wangfei@hanwang.com.cn
	   ��
	   wangfei@engineer.com.cn
                                                                 2000��3��
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
#define DTCEM_HIDE_CALENDAR WM_USER + 2 //���������ؼ�.

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
	//�ж�iYear�ǲ�������
    static BOOL IsLeapYear(WORD iYear)
	{return !(iYear%4)&&(iYear%100) || !(iYear%400);}

	//����iYear,iMonth,iDay��Ӧ�����ڼ� 1��1��1�� --- 65535��12��31��
	static WORD WeekDay(WORD iYear, WORD iMonth, WORD iDay);

	//����iYear��iMonth�µ����� 1��1�� --- 65535��12��
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
