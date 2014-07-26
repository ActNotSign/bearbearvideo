#if !defined(AFX_SHOWWINDOW_H__D0421290_C654_4A68_B942_BF46D3D76494__INCLUDED_)
#define AFX_SHOWWINDOW_H__D0421290_C654_4A68_B942_BF46D3D76494__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowWindow dialog
#include "DarwDialog.h"

class CShowWindow : public CDarwDialog
{
// Construction
public:
	HBITMAP m_b;
	void DrawPic(HBITMAP bitmap);
	CShowWindow(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CShowWindow)
	enum { IDD = IDD_SWINDOW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowWindow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowWindow)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWWINDOW_H__D0421290_C654_4A68_B942_BF46D3D76494__INCLUDED_)
