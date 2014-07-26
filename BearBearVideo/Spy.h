#if !defined(AFX_SPY_H__FAEE636F_1A2D_476E_BE23_61938D9563B4__INCLUDED_)
#define AFX_SPY_H__FAEE636F_1A2D_476E_BE23_61938D9563B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Spy.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpy dialog
#include "DarwDialog.h"
#include "NewButton.h"
#include "ShowWindow.h"
#include "MakeVideo.h"

class CSpy : public CDarwDialog
{
// Construction
public:
	BOOL m_C;
	void SetWindowMes();
	void DrawRect(HWND hWnd);
	CStatic m_Static;
	CSpy(CWnd* pParent = NULL);   // standard constructor
	BOOL m_move;
	HWND m_hwndCapture;
	//
	HWND m_h;
	HWND m_h1;
	//
	CRect m_rc;
	CRect m_r;
	//
	CMakeVideo m_pic;
	CShowWindow m_showPic;
	//
	CString m_strl;
// Dialog Data
	//{{AFX_DATA(CSpy)
	enum { IDD = IDD_DIALOG_SPY };
	CNewButton	m_cancel;
	BOOL	m_hide;
	BOOL	m_savepic;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpy)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpy)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCheck();
	afx_msg void OnSavepic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPY_H__FAEE636F_1A2D_476E_BE23_61938D9563B4__INCLUDED_)
