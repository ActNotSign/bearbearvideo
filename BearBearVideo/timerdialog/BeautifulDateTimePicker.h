#if !defined(AFX_BEAUTIFULDATETIMEPICKER_H__83D5B3CE_CF60_4416_AA79_55E094DDC67A__INCLUDED_)
#define AFX_BEAUTIFULDATETIMEPICKER_H__83D5B3CE_CF60_4416_AA79_55E094DDC67A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BeautifulDateTimePicker.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBeautifulDateTimePicker window

#define DTCEM_BEFORE_CREATE WM_USER + 1 //建立漂亮的DateTimePicker
                                        //之前的事件.


#define DTCEM_PICKER_BUTTON_ID 1 //给PICKERBUTTON一个ID
#define ID_CALENDAR________ 2

extern "C" WINUSERAPI BOOL WINAPI TrackMouseEvent(LPTRACKMOUSEEVENT lPeventTrack);

#include "Calendar.h"


#if !defined(IDC_HAND)
#define IDC_HAND MAKEINTRESOURCE(32649)
#endif 

class CBeautifulDateTimePicker : public CDateTimeCtrl
{
public:
	
	/**
	 * 以下定义了该日历选择控件的右边的那个选择按钮的类
	 **/
	class CPickerButton : public CButton
	{
	protected:
		void OnMouseIn();
	private:
		static HCURSOR g_hCursorLink;
		bool isOn;
	public:
		CPickerButton();

	    // ClassWizard generated virtual function overrides
        //{{AFX_VIRTUAL(CPickerButton)
        public:
			virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
		protected:
            virtual void PreSubclassWindow();  
		//}}AFX_VIRTUAL
        // Generated message map functions

	protected:
		void DrawNormalFace();
		void DrawHoverFace();
	    //{{AFX_MSG(CBeautifulDateTimePicker::CDateTimeEditCtrlButton)
        afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		afx_msg LRESULT OnMouseOut(WPARAM wParam,   LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()
	};

    

	/**
	 * 以下是定义承载日历控件的窗体
	 **/
	class CBeautifulCalendarWnd : public CWnd
	{
	public:
       //CBeautifulCalendarWnd(); 

		BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName,
		              LPCTSTR lpszWindowName, DWORD dwStyle,
		              const RECT& rect,
		              CWnd* pParentWnd, UINT nID,
		              LPVOID lpParam = NULL
					  );
	// Operations
    public:
	    CBeautifulDateTimePicker * GetDateTimeCtrl();
	    void AlterDatePicker();
	    CCalendar *GetMonthCalCtrl();
        CCalendar m_Calendar;
		
	  // Overrides
		  // ClassWizard generated virtual function overrides
		  //{{AFX_VIRTUAL(CBeautifulDateTimePicker::CBeautifulCalendarWnd)
		  protected:
		   
		  //}}AFX_VIRTUAL

	 protected:
         CWnd* m_pParent;

		 

	 protected:
	    //{{AFX_MSG(CBeautifulDateTimePicker::CBeautifulCalendarWnd)
        afx_msg void OnKillFocus(CWnd* pNewWnd);
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg BOOL OnEraseBkgnd(CDC *pDC);
		afx_msg LRESULT OnHideCanlendar(WPARAM wParam,LPARAM lParam);
		afx_msg LRESULT OnSelChange(WPARAM wParam,LPARAM lParam);
        //}}AFX_MSG
        DECLARE_MESSAGE_MAP()

	};

	


protected:
	BOOL m_bInCreate;
	CPickerButton m_PickerButton; 
	CBeautifulCalendarWnd m_BeautifulCalendarWnd;
    COLORREF m_background; 
protected:
	BOOL ShowCalendar();
	BOOL HideCalendar();
    void DrawNormalFrame();
// Construction
public:
	CBeautifulDateTimePicker();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBeautifulDateTimePicker)
	protected:
	virtual void PreSubclassWindow();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBeautifulDateTimePicker();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBeautifulDateTimePicker)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnBeforeCreate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnHideCalendar(WPARAM wParam,LPARAM lParam);
	afx_msg void OnNcPaint();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects,NCCALCSIZE_PARAMS *lpncsp);
	afx_msg LRESULT OnSelChange(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

typedef CBeautifulDateTimePicker::CBeautifulCalendarWnd CBeautifulCalendarWnd;
typedef CBeautifulDateTimePicker::CPickerButton CPickerButton;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEAUTIFULDATETIMEPICKER_H__83D5B3CE_CF60_4416_AA79_55E094DDC67A__INCLUDED_)
