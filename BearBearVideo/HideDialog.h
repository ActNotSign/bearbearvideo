#if !defined(AFX_HIDEDIALOG_H__FBC7753A_6B4A_4F77_A518_F3209CEA81A3__INCLUDED_)
#define AFX_HIDEDIALOG_H__FBC7753A_6B4A_4F77_A518_F3209CEA81A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HideDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHideDialog dialog

class CHideDialog : public CDialog
{
// Construction
public:
	CHideDialog(CWnd* pParent = NULL);   // standard constructor
	int r,g,b;
	CString str;
	BOOL is;
// Dialog Data
	//{{AFX_DATA(CHideDialog)
	enum { IDD = IDD_OLE_PROPPAGE_HIDE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHideDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHideDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIDEDIALOG_H__FBC7753A_6B4A_4F77_A518_F3209CEA81A3__INCLUDED_)
