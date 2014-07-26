#if !defined(AFX_DARWDIALOG_H__7BB0A424_E496_42D5_8B7D_C6C5946BD3A6__INCLUDED_)
#define AFX_DARWDIALOG_H__7BB0A424_E496_42D5_8B7D_C6C5946BD3A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DarwDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDarwDialog dialog


class CDarwDialog : public CDialog
{
// Construction
protected:
	bool m_IsHasMaxButton;
	bool m_IsHasMinButton;
	bool m_IsHasCloseButton;

	CRect m_rcclose,m_rcmin;
public:
	void Draw();
	CDarwDialog(CWnd* pParent = NULL);   // standard constructor
    CDarwDialog(UINT id, CWnd * parent = NULL);

// Dialog Data
	//{{AFX_DATA(CDarwDialog)

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDarwDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDarwDialog)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DARWDIALOG_H__7BB0A424_E496_42D5_8B7D_C6C5946BD3A6__INCLUDED_)
