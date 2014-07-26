#if !defined(AFX_SETWAVE_H__2CE4DB10_1FFC_407F_8CDD_20F7D1A19DBC__INCLUDED_)
#define AFX_SETWAVE_H__2CE4DB10_1FFC_407F_8CDD_20F7D1A19DBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetWave.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetWave dialog
#include "NewButton.h"
#include "MakeVideo.h"

class CSetWave : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetWave)

// Construction
public:
	void DrawDialog();
	CMakeVideo m_video;
	CSetWave();
	~CSetWave();
	HWND m_hWnd;
// Dialog Data
	//{{AFX_DATA(CSetWave)
	enum { IDD = IDD_OLE_PROPPAGE_WAVA };
	CSliderCtrl	m_volumeSize;
	int		m_wSize;
	int		m_cl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetWave)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetWave)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	int GetFreq();
	int GetSampsize();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETWAVE_H__2CE4DB10_1FFC_407F_8CDD_20F7D1A19DBC__INCLUDED_)
