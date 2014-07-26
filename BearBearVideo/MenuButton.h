#if !defined(AFX_MENUBUTTON_H__6C034EF4_0222_4E26_9C8D_0D4DFC812570__INCLUDED_)
#define AFX_MENUBUTTON_H__6C034EF4_0222_4E26_9C8D_0D4DFC812570__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MenuButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMenuButton window

class CMenuButton : public CButton
{
// Construction
public:
	CMenuButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMenuButton)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void TabButtonDeath(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void TabButtonNormal(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual ~CMenuButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMenuButton)
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUBUTTON_H__6C034EF4_0222_4E26_9C8D_0D4DFC812570__INCLUDED_)
