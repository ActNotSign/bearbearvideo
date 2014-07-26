#if !defined(AFX_STATICHTTP_H__128273D5_5A34_4621_BDAA_6B50E89D449F__INCLUDED_)
#define AFX_STATICHTTP_H__128273D5_5A34_4621_BDAA_6B50E89D449F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticHttp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticHttp window

class CStaticHttp : public CStatic
{
// Construction
public:
	CStaticHttp();

// Attributes
public:

// Operations
	HCURSOR m_hLinkCursor;
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticHttp)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	void Dong();
	virtual ~CStaticHttp();

	// Generated message map functions
protected:
	BOOL m_big;
	//{{AFX_MSG(CStaticHttp)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICHTTP_H__128273D5_5A34_4621_BDAA_6B50E89D449F__INCLUDED_)
