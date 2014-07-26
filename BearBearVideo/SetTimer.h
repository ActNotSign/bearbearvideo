#if !defined(AFX_SETTIMER_H__DCDBAE16_2FF9_4DB4_9820_33209C43B4B5__INCLUDED_)
#define AFX_SETTIMER_H__DCDBAE16_2FF9_4DB4_9820_33209C43B4B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetTimer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetTimer dialog
#include "timerdialog\BeautifulDateTimePicker.h"
#include "timerdialog\XPGroupBox.h"
#include "NewButton.h"

class CSetTimer : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetTimer)

// Construction
public:
	void DrawDialog();
	CSetTimer();
	~CSetTimer();

// Dialog Data
	//{{AFX_DATA(CSetTimer)
	enum { IDD = IDD_OLE_PROPPAGE_TIMER };
	CNewButton	m_stop;
	CNewButton	m_start;
	CBeautifulDateTimePicker	m_yearstop;
	CBeautifulDateTimePicker	m_years;
	CDateTimeCtrl	m_timers;
	CDateTimeCtrl	m_timerstop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetTimer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetTimer)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTIMER_H__DCDBAE16_2FF9_4DB4_9820_33209C43B4B5__INCLUDED_)
