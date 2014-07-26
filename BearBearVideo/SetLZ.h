#if !defined(AFX_SETLZ_H__DE843761_9D9F_4C70_BA72_4FFE7267F3D1__INCLUDED_)
#define AFX_SETLZ_H__DE843761_9D9F_4C70_BA72_4FFE7267F3D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetLZ.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetLZ dialog
#include "NewButton.h"
#include "HideDialog.h"
#include "VideoEncodeDlg.h"

//设置录制的对象
const int FULLSCREES=10;
const int WINDOWS=100;
const int VIDEO=1000;
//处理录制时怎么显示窗口
const int SHOW=10;
const int HDIE=100;
const int MIN=1000;

#include "VideoShow.h"
#include "Spy.h"
class CSetLZ : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetLZ)

// Construction
public:
	//
	CSpy m_spy;

	CRect m_rectCapture; 

	int SetWindowShow(HWND hWnd);
	CRect  MakeWhat();
	void DrawDialog();
	CSetLZ();
	~CSetLZ();
	BOOL m_move;
	//
	BOOL m_video;
	//
	CVideoEncodeDlg m_vs;
	//
	CHideDialog m_hide;
// Dialog Data
	//{{AFX_DATA(CSetLZ)
	enum { IDD = IDD_OLE_PROPPAGE_MB };
	CNewButton	m_look;
	CNewButton	m_set;
	int		m_makeV;
	int		m_show;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetLZ)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetLZ)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnSet();
	afx_msg void OnRadioWin();
	afx_msg void OnRadioVideo();
	afx_msg void OnRadioFull();
	afx_msg void OnLook();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETLZ_H__DE843761_9D9F_4C70_BA72_4FFE7267F3D1__INCLUDED_)
