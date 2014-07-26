#if !defined(AFX_DRAWTAB_H__BFBC10CA_C503_4017_AB5A_6DFB0BDC5319__INCLUDED_)
#define AFX_DRAWTAB_H__BFBC10CA_C503_4017_AB5A_6DFB0BDC5319__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DrawTab.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDrawTab dialog
#include "MenuButton.h"
#include "Set.h"
#include "SetLZ.h"
#include "SetWave.h"
#include "SetTimer.h"
#include "Soft.h"
#include "AD.h"

static int m_iwho=0;

class CDrawTab : public CPropertyPage
{
	DECLARE_DYNCREATE(CDrawTab)

// Construction

public:
	//ÊôÐÔÒ³µÄ¾ØÐÎ
	CRect r;

	void ShowDialog();
	void SetDialog();
	CDrawTab();
	~CDrawTab();
//
	CSet m_dset;
//
	CSetLZ m_dlz;
//
	CSetWave m_dwav;
// 
	CSetTimer m_dtimer;
	//
	CSoft m_dSoft;
	//
	CAD m_dad;
// Dialog Data
	//{{AFX_DATA(CDrawTab)
	enum { IDD = IDD_TAB };
	CMenuButton	m_wave;
	CMenuButton	m_soft;
	CMenuButton	m_timer;
	CMenuButton	m_ad;
	CMenuButton	m_lz;
	CMenuButton	m_set;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CDrawTab)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDrawTab)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnLz();
	afx_msg void OnWave();
	afx_msg void OnTimers();
	afx_msg void OnSoft();
	afx_msg void OnAd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWTAB_H__BFBC10CA_C503_4017_AB5A_6DFB0BDC5319__INCLUDED_)
