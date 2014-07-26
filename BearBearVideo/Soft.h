#if !defined(AFX_SOFT_H__D9B0FACE_8A1D_4438_B2A4_0CC65C3C0B7E__INCLUDED_)
#define AFX_SOFT_H__D9B0FACE_8A1D_4438_B2A4_0CC65C3C0B7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Soft.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSoft dialog
#include "NewButton.h"
#include "Spy.h"


class CSoft : public CDialog
{
// Construction
public:
	void DrawDialog();
	CSoft(CWnd* pParent = NULL);   // standard constructor
	CSpy m_Spy;
// Dialog Data
	//{{AFX_DATA(CSoft)
	enum { IDD = IDD_OLE_PROPPAGE_SOFT };
	CNewButton	m_spy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoft)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSoft)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSpy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOFT_H__D9B0FACE_8A1D_4438_B2A4_0CC65C3C0B7E__INCLUDED_)
