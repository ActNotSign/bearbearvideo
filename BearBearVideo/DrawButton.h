#if !defined(AFX_DRAWBUTTON_H__88106171_C349_4582_9B39_1661162891D1__INCLUDED_)
#define AFX_DRAWBUTTON_H__88106171_C349_4582_9B39_1661162891D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DrawButton window

class DrawButton : public CButton
{
// Construction
public:
	DrawButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DrawButton)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL


// Implementation
public:
	void ButtonDeath(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void ButtonMouse();
	void ButtonNormal(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void ButtonPress(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual ~DrawButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(DrawButton)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWBUTTON_H__88106171_C349_4582_9B39_1661162891D1__INCLUDED_)
