#if !defined(AFX_NEWBUTTON_H__30180629_BFC9_4CEA_8F8B_AA1499996E22__INCLUDED_)
#define AFX_NEWBUTTON_H__30180629_BFC9_4CEA_8F8B_AA1499996E22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewButton window

class CNewButton : public CButton
{
// Construction
public:
	CNewButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewButton)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void ButtonPress(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void ButtonMouse(int IDB);
	void ButtonNormal(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual ~CNewButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNewButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWBUTTON_H__30180629_BFC9_4CEA_8F8B_AA1499996E22__INCLUDED_)
