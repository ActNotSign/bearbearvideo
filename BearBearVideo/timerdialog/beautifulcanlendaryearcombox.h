#if !defined(AFX_BEAUTIFULCANLENDARYEARCOMBOX_H__9C20A3E0_3A5A_435D_8E71_840FC6989DAC__INCLUDED_)
#define AFX_BEAUTIFULCANLENDARYEARCOMBOX_H__9C20A3E0_3A5A_435D_8E71_840FC6989DAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// beautifulcanlendaryearcombox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBeautifulCanlendarYearCombox window

#define UM_YEAR_SELCHANGE (WM_USER+23)

class CBeautifulCanlendarYearCombox : public CComboBox
{ 

protected:
    HWND m_hListBox;
	int m_isDec;//是否是上滚动，如果是上滚,则为1,如果是下滚则为-1，
	            //如果停止滚，则为零。
	CEdit m_FlatEdit;
	int m_CurSel;
// Construction
public:
	CBeautifulCanlendarYearCombox();
    BOOL Create(DWORD dwStyle,const RECT &rect,CWnd *pParentWnd,UINT nID);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBeautifulCanlendarYearCombox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    virtual void MeasureItem(LPMEASUREITEMSTRUCT lpDrawItemStruct);

	//}}AFX_VIRTUAL

// Implementation
public:
	int GetCurSel();
	int SetCurSel(int cursel);
	void StopRoll();
	void BeginRollToFuture();
	void BeginRollBack();
	virtual ~CBeautifulCanlendarYearCombox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBeautifulCanlendarYearCombox)
	afx_msg void OnCancelMode();
	afx_msg void OnSelendcancel();
	afx_msg void OnDropDown();
	afx_msg LRESULT OnCtlColorListBox(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelendok();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEAUTIFULCANLENDARYEARCOMBOX_H__9C20A3E0_3A5A_435D_8E71_840FC6989DAC__INCLUDED_)
