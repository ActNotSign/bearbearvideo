#if !defined(AFX_DRAWLISTCTRL_H__A9971284_7374_4B9B_A0C4_AABC43DBC75B__INCLUDED_)
#define AFX_DRAWLISTCTRL_H__A9971284_7374_4B9B_A0C4_AABC43DBC75B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawListCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDrawListCtrl window

class CDrawListCtrl : public CListCtrl
{
// Construction
public:
	CDrawListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDrawListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDrawListCtrl)
	afx_msg void OnNcPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWLISTCTRL_H__A9971284_7374_4B9B_A0C4_AABC43DBC75B__INCLUDED_)
