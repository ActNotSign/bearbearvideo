#if !defined(AFX_BEAUTIFULCANLENDARMONTHCOMBO_H__5FF74C31_3949_4AD3_A492_6B850166405F__INCLUDED_)
#define AFX_BEAUTIFULCANLENDARMONTHCOMBO_H__5FF74C31_3949_4AD3_A492_6B850166405F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// beautifulcanlendarmonthcombo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBeautifulCanlendarMonthCombo window

class CBeautifulCanlendarMonthCombo : public CComboBox
{
// Construction
public:
	CBeautifulCanlendarMonthCombo();
    BOOL Create(DWORD dwStyle,const RECT &rect,CWnd *pParentWnd,UINT nID);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBeautifulCanlendarMonthCombo)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBeautifulCanlendarMonthCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBeautifulCanlendarMonthCombo)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEAUTIFULCANLENDARMONTHCOMBO_H__5FF74C31_3949_4AD3_A492_6B850166405F__INCLUDED_)
