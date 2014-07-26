#if !defined(AFX_DRAWTOOLBAR_H__5085FDE3_B362_4B9D_86BB_146457D47BC2__INCLUDED_)
#define AFX_DRAWTOOLBAR_H__5085FDE3_B362_4B9D_86BB_146457D47BC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DrawToolBar window

class DrawToolBar : public CToolBarCtrl
{
// Construction
public:
	DrawToolBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DrawToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~DrawToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(DrawToolBar)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNcPaint();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWTOOLBAR_H__5085FDE3_B362_4B9D_86BB_146457D47BC2__INCLUDED_)
