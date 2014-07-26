#if !defined(AFX_VIDEOSHOW_H__E7CFDA95_9E15_4FE1_B4DB_724B5FD6C95F__INCLUDED_)
#define AFX_VIDEOSHOW_H__E7CFDA95_9E15_4FE1_B4DB_724B5FD6C95F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoShow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVideoShow dialog

#include "DarwDialog.h"

#include "MakeVideo.h"


class CVideoShow : public CDarwDialog
{
// Construction
public:
	HWND GethWnd();
	void Theard();
	CVideoShow(CWnd* pParent = NULL);   // standard constructor


	HWND m_hWndVideo;
	BOOL           m_Captured;         //ÊÇ·ñ¿ªÊ¼²¶×½
	CMakeVideo m_video;

	//
	BOOL isW;
// Dialog Data
	//{{AFX_DATA(CVideoShow)
	enum { IDD = IDD_DIALOG_ViDEOSHOW };
	CStatic	m_panel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoShow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoShow)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancel();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOSHOW_H__E7CFDA95_9E15_4FE1_B4DB_724B5FD6C95F__INCLUDED_)
